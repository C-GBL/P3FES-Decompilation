// Pair tests for slice libs26 (game/src/cri/libs26.cpp): every body against its recompiled body, compared by
// tests/game/handgen_pairs.h (the whole register file and cycle count at every check point and at the return / stop, all
// 32 MiB of RAM, the scratchpad, the BIOS window and the bus log). Worlds: random worlds; the kernel call wrappers with
// their call numbers checked; DMAC channels and D_STADR as scripted hardware registers; the sceMpeg extension parsers
// on MPEG-2 extension bit fields (the IPU bit reader and the error reporter stood in, as test_cri2 does); ISO 9660
// directory sectors and #DirLst# lists (the ELF's own tables) for the ROFS directory helpers; and every body over the
// RAM of the replay snapshots (the real SIF / file-I/O / CD / pad / ADXF / ROFS globals). A callee this build does not
// emit stops both runs at the same call; no test asserts such a stop.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/cri_rofs.h"
#include "p3fes/game/libs26.h"

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
void fn__dispRefImage_0_004c72d8(EEContext&);  // generated body
void fn__dispRefImage_0_004c72d8__recomp(EEContext&);  // recompiled
void fn_sceDmaPutStallAddr_004fac08(EEContext&);  // generated body
void fn_sceDmaPutStallAddr_004fac08__recomp(EEContext&);  // recompiled
void fn_sceDmaSendI_004fad00(EEContext&);  // generated body
void fn_sceDmaSendI_004fad00__recomp(EEContext&);  // recompiled
void fn_sceDmaRecv_004fad78(EEContext&);  // generated body
void fn_sceDmaRecv_004fad78__recomp(EEContext&);  // recompiled
void fn_sceDmaRecvI_004fae40(EEContext&);  // generated body
void fn_sceDmaRecvI_004fae40__recomp(EEContext&);  // recompiled
void fn_sceDmaWatch_004faef8(EEContext&);  // generated body
void fn_sceDmaWatch_004faef8__recomp(EEContext&);  // recompiled
void fn_sceDmaRestart_004fafc8(EEContext&);  // generated body
void fn_sceDmaRestart_004fafc8__recomp(EEContext&);  // recompiled
void fn__sequenceExtension_004ff378(EEContext&);  // generated body
void fn__sequenceExtension_004ff378__recomp(EEContext&);  // recompiled
void fn__quantMatrixExtension_004ff4b8(EEContext&);  // generated body
void fn__quantMatrixExtension_004ff4b8__recomp(EEContext&);  // recompiled
void fn__sequenceScalableExtension_004ff5a0(EEContext&);  // generated body
void fn__sequenceScalableExtension_004ff5a0__recomp(EEContext&);  // recompiled
void fn__pictureSpatialScalableExtension_004ff7a8(EEContext&);  // generated body
void fn__pictureSpatialScalableExtension_004ff7a8__recomp(EEContext&);  // recompiled
void fn__sequenceDisplayExtension_004ffb88(EEContext&);  // generated body
void fn__sequenceDisplayExtension_004ffb88__recomp(EEContext&);  // recompiled
void fn__copyrightExtension_004ffc18(EEContext&);  // generated body
void fn__copyrightExtension_004ffc18__recomp(EEContext&);  // recompiled
void fn__pictureDisplayExtension_004ffcb0(EEContext&);  // generated body
void fn__pictureDisplayExtension_004ffcb0__recomp(EEContext&);  // recompiled
void fn_RFU000_FullReset_00502d40(EEContext&);  // generated body
void fn_RFU000_FullReset_00502d40__recomp(EEContext&);  // recompiled
void fn_ResetEE_00502d50(EEContext&);  // generated body
void fn_ResetEE_00502d50__recomp(EEContext&);  // recompiled
void fn_RFU003_00502d70(EEContext&);  // generated body
void fn_RFU003_00502d70__recomp(EEContext&);  // recompiled
void fn_RFU005_00502d90(EEContext&);  // generated body
void fn_RFU005_00502d90__recomp(EEContext&);  // recompiled
void fn_RFU008_00502dc0(EEContext&);  // generated body
void fn_RFU008_00502dc0__recomp(EEContext&);  // recompiled
void fn_RFU009_00502dd0(EEContext&);  // generated body
void fn_RFU009_00502dd0__recomp(EEContext&);  // recompiled
void fn_AddSbusIntcHandler_00502de0(EEContext&);  // generated body
void fn_AddSbusIntcHandler_00502de0__recomp(EEContext&);  // recompiled
void fn_RemoveSbusIntcHandler_00502df0(EEContext&);  // generated body
void fn_RemoveSbusIntcHandler_00502df0__recomp(EEContext&);  // recompiled
void fn_Interrupt2Iop_00502e00(EEContext&);  // generated body
void fn_Interrupt2Iop_00502e00__recomp(EEContext&);  // recompiled
void fn_SetVInterruptHandler_00502e30(EEContext&);  // generated body
void fn_SetVInterruptHandler_00502e30__recomp(EEContext&);  // recompiled
void fn_SetAlarm_00502ee0(EEContext&);  // generated body
void fn_SetAlarm_00502ee0__recomp(EEContext&);  // recompiled
void fn_ReleaseAlarm_00502ef0(EEContext&);  // generated body
void fn_ReleaseAlarm_00502ef0__recomp(EEContext&);  // recompiled
void fn_iSetAlarm_00502f40(EEContext&);  // generated body
void fn_iSetAlarm_00502f40__recomp(EEContext&);  // recompiled
void fn_iReleaseAlarm_00502f50(EEContext&);  // generated body
void fn_iReleaseAlarm_00502f50__recomp(EEContext&);  // recompiled
void fn_ExitThread_00502f90(EEContext&);  // generated body
void fn_ExitThread_00502f90__recomp(EEContext&);  // recompiled
void fn_iTerminateThread_00502fc0(EEContext&);  // generated body
void fn_iTerminateThread_00502fc0__recomp(EEContext&);  // recompiled
void fn_DisableDispatchThread_00502fd0(EEContext&);  // generated body
void fn_DisableDispatchThread_00502fd0__recomp(EEContext&);  // recompiled
void fn_EnableDispatchThread_00502fe0(EEContext&);  // generated body
void fn_EnableDispatchThread_00502fe0__recomp(EEContext&);  // recompiled
void fn__iRotateThreadReadyQueue_00503020(EEContext&);  // generated body
void fn__iRotateThreadReadyQueue_00503020__recomp(EEContext&);  // recompiled
void fn_ReleaseWaitThread_00503030(EEContext&);  // generated body
void fn_ReleaseWaitThread_00503030__recomp(EEContext&);  // recompiled
void fn_iReleaseWaitThread_00503040(EEContext&);  // generated body
void fn_iReleaseWaitThread_00503040__recomp(EEContext&);  // recompiled
void fn_CancelWakeupThread_005030b0(EEContext&);  // generated body
void fn_CancelWakeupThread_005030b0__recomp(EEContext&);  // recompiled
void fn_iCancelWakeupThread_005030c0(EEContext&);  // generated body
void fn_iCancelWakeupThread_005030c0__recomp(EEContext&);  // recompiled
void fn_iResumeThread_00503100(EEContext&);  // generated body
void fn_iResumeThread_00503100__recomp(EEContext&);  // recompiled
void fn_JoinThread_00503110(EEContext&);  // generated body
void fn_JoinThread_00503110__recomp(EEContext&);  // recompiled
void fn_RFU060_00503120(EEContext&);  // generated body
void fn_RFU060_00503120__recomp(EEContext&);  // recompiled
void fn_RFU061_00503130(EEContext&);  // generated body
void fn_RFU061_00503130__recomp(EEContext&);  // recompiled
void fn_RFU063_00503150(EEContext&);  // generated body
void fn_RFU063_00503150__recomp(EEContext&);  // recompiled
void fn_iPollSema_005031c0(EEContext&);  // generated body
void fn_iPollSema_005031c0__recomp(EEContext&);  // recompiled
void fn_ReferSemaStatus_005031d0(EEContext&);  // generated body
void fn_ReferSemaStatus_005031d0__recomp(EEContext&);  // recompiled
void fn_iReferSemaStatus_005031e0(EEContext&);  // generated body
void fn_iReferSemaStatus_005031e0__recomp(EEContext&);  // recompiled
void fn_RFU073_005031f0(EEContext&);  // generated body
void fn_RFU073_005031f0__recomp(EEContext&);  // recompiled
void fn_GetGsHParam_00503220(EEContext&);  // generated body
void fn_GetGsHParam_00503220__recomp(EEContext&);  // recompiled
void fn_GetGsVParam_00503230(EEContext&);  // generated body
void fn_GetGsVParam_00503230__recomp(EEContext&);  // recompiled
void fn_SetGsHParam_00503240(EEContext&);  // generated body
void fn_SetGsHParam_00503240__recomp(EEContext&);  // recompiled
void fn_SetGsVParam_00503250(EEContext&);  // generated body
void fn_SetGsVParam_00503250__recomp(EEContext&);  // recompiled
void fn_RFU080_CreateEventFlag_00503260(EEContext&);  // generated body
void fn_RFU080_CreateEventFlag_00503260__recomp(EEContext&);  // recompiled
void fn_RFU081_DeleteEventFlag_00503270(EEContext&);  // generated body
void fn_RFU081_DeleteEventFlag_00503270__recomp(EEContext&);  // recompiled
void fn_RFU082_SetEventFlag_00503280(EEContext&);  // generated body
void fn_RFU082_SetEventFlag_00503280__recomp(EEContext&);  // recompiled
void fn_RFU083_iSetEventFlag_00503290(EEContext&);  // generated body
void fn_RFU083_iSetEventFlag_00503290__recomp(EEContext&);  // recompiled
void fn_RFU084_ClearEventFlag_005032a0(EEContext&);  // generated body
void fn_RFU084_ClearEventFlag_005032a0__recomp(EEContext&);  // recompiled
void fn_RFU085_iClearEventFlag_005032b0(EEContext&);  // generated body
void fn_RFU085_iClearEventFlag_005032b0__recomp(EEContext&);  // recompiled
void fn_RFU086_WaitEvnetFlag_005032c0(EEContext&);  // generated body
void fn_RFU086_WaitEvnetFlag_005032c0__recomp(EEContext&);  // recompiled
void fn_RFU087_PollEvnetFlag_005032d0(EEContext&);  // generated body
void fn_RFU087_PollEvnetFlag_005032d0__recomp(EEContext&);  // recompiled
void fn_RFU088_iPollEvnetFlag_005032e0(EEContext&);  // generated body
void fn_RFU088_iPollEvnetFlag_005032e0__recomp(EEContext&);  // recompiled
void fn_RFU089_ReferEventFlagStatus_005032f0(EEContext&);  // generated body
void fn_RFU089_ReferEventFlagStatus_005032f0__recomp(EEContext&);  // recompiled
void fn_RFU090_iReferEventFlagStatus_00503300(EEContext&);  // generated body
void fn_RFU090_iReferEventFlagStatus_00503300__recomp(EEContext&);  // recompiled
void fn_RFU091_00503310(EEContext&);  // generated body
void fn_RFU091_00503310__recomp(EEContext&);  // recompiled
void fn_EnableIntcHandler_00503320(EEContext&);  // generated body
void fn_EnableIntcHandler_00503320__recomp(EEContext&);  // recompiled
void fn_iEnableIntcHandler_00503330(EEContext&);  // generated body
void fn_iEnableIntcHandler_00503330__recomp(EEContext&);  // recompiled
void fn_DisableIntcHandler_00503340(EEContext&);  // generated body
void fn_DisableIntcHandler_00503340__recomp(EEContext&);  // recompiled
void fn_iDisableIntcHandler_00503350(EEContext&);  // generated body
void fn_iDisableIntcHandler_00503350__recomp(EEContext&);  // recompiled
void fn_EnableDmacHandler_00503360(EEContext&);  // generated body
void fn_EnableDmacHandler_00503360__recomp(EEContext&);  // recompiled
void fn_iEnableDmacHandler_00503370(EEContext&);  // generated body
void fn_iEnableDmacHandler_00503370__recomp(EEContext&);  // recompiled
void fn_DisableDmacHandler_00503380(EEContext&);  // generated body
void fn_DisableDmacHandler_00503380__recomp(EEContext&);  // recompiled
void fn_iDisableDmacHandler_00503390(EEContext&);  // generated body
void fn_iDisableDmacHandler_00503390__recomp(EEContext&);  // recompiled
void fn_KSeg0_005033a0(EEContext&);  // generated body
void fn_KSeg0_005033a0__recomp(EEContext&);  // recompiled
void fn_EnableCache_005033b0(EEContext&);  // generated body
void fn_EnableCache_005033b0__recomp(EEContext&);  // recompiled
void fn_DisableCache_005033c0(EEContext&);  // generated body
void fn_DisableCache_005033c0__recomp(EEContext&);  // recompiled
void fn_GetCop0_005033d0(EEContext&);  // generated body
void fn_GetCop0_005033d0__recomp(EEContext&);  // recompiled
void fn_CpuConfig_005033f0(EEContext&);  // generated body
void fn_CpuConfig_005033f0__recomp(EEContext&);  // recompiled
void fn_iGetCop0_00503400(EEContext&);  // generated body
void fn_iGetCop0_00503400__recomp(EEContext&);  // recompiled
void fn_iFlushCache_00503410(EEContext&);  // generated body
void fn_iFlushCache_00503410__recomp(EEContext&);  // recompiled
void fn_iCpuConfig_00503420(EEContext&);  // generated body
void fn_iCpuConfig_00503420__recomp(EEContext&);  // recompiled
void fn_SetCPUTimerHandler_00503440(EEContext&);  // generated body
void fn_SetCPUTimerHandler_00503440__recomp(EEContext&);  // recompiled
void fn_SetCPUTimer_00503450(EEContext&);  // generated body
void fn_SetCPUTimer_00503450__recomp(EEContext&);  // recompiled
void fn_SetOsdConfigParam2_00503460(EEContext&);  // generated body
void fn_SetOsdConfigParam2_00503460__recomp(EEContext&);  // recompiled
void fn_GetOsdConfigParam2_00503470(EEContext&);  // generated body
void fn_GetOsdConfigParam2_00503470__recomp(EEContext&);  // recompiled
void fn_iGsGetIMR_00503490(EEContext&);  // generated body
void fn_iGsGetIMR_00503490__recomp(EEContext&);  // recompiled
void fn_iGsPutIMR_005034b0(EEContext&);  // generated body
void fn_iGsPutIMR_005034b0__recomp(EEContext&);  // recompiled
void fn_SetPgifHandler_005034c0(EEContext&);  // generated body
void fn_SetPgifHandler_005034c0__recomp(EEContext&);  // recompiled
void fn_RFU116_005034e0(EEContext&);  // generated body
void fn_RFU116_005034e0__recomp(EEContext&);  // recompiled
void fn__print_005034f0(EEContext&);  // generated body
void fn__print_005034f0__recomp(EEContext&);  // recompiled
void fn_isceSifDmaStat_00503510(EEContext&);  // generated body
void fn_isceSifDmaStat_00503510__recomp(EEContext&);  // recompiled
void fn_PSMode_005035a0(EEContext&);  // generated body
void fn_PSMode_005035a0__recomp(EEContext&);  // recompiled
void fn_MachineType_005035b0(EEContext&);  // generated body
void fn_MachineType_005035b0__recomp(EEContext&);  // recompiled
void fn_iSuspendThread_00504140(EEContext&);  // generated body
void fn_iSuspendThread_00504140__recomp(EEContext&);  // recompiled
void fn__DelayThreadHandler_00504418(EEContext&);  // generated body
void fn__DelayThreadHandler_00504418__recomp(EEContext&);  // recompiled
void fn_isceSifSetDma_00506110(EEContext&);  // generated body
void fn_isceSifSetDma_00506110__recomp(EEContext&);  // recompiled
void fn__alarm_rdata_00506c78(EEContext&);  // generated body
void fn__alarm_rdata_00506c78__recomp(EEContext&);  // recompiled
void fn__request_rdata_00506cb8(EEContext&);  // generated body
void fn__request_rdata_00506cb8__recomp(EEContext&);  // recompiled
void fn_sceSifGetOtherData_00506d88(EEContext&);  // generated body
void fn_sceSifGetOtherData_00506d88__recomp(EEContext&);  // recompiled
void fn__alarm_bind_00506f40(EEContext&);  // generated body
void fn__alarm_bind_00506f40__recomp(EEContext&);  // recompiled
void fn__request_bind_00506f80(EEContext&);  // generated body
void fn__request_bind_00506f80__recomp(EEContext&);  // recompiled
void fn_sceSifExecRequest_00507758(EEContext&);  // generated body
void fn_sceSifExecRequest_00507758__recomp(EEContext&);  // recompiled
void fn__sceFs_Poff_Intr_00508128(EEContext&);  // generated body
void fn__sceFs_Poff_Intr_00508128__recomp(EEContext&);  // recompiled
void fn_sceFsSetIopBuf_00508440(EEContext&);  // generated body
void fn_sceFsSetIopBuf_00508440__recomp(EEContext&);  // recompiled
void fn_sceFsSetIopPrio_00508580(EEContext&);  // generated body
void fn_sceFsSetIopPrio_00508580__recomp(EEContext&);  // recompiled
void fn_sceIoctl2_00509570(EEContext&);  // generated body
void fn_sceIoctl2_00509570__recomp(EEContext&);  // recompiled
void fn_sceMkdir_00509928(EEContext&);  // generated body
void fn_sceMkdir_00509928__recomp(EEContext&);  // recompiled
void fn_sceFormat_00509b00(EEContext&);  // generated body
void fn_sceFormat_00509b00__recomp(EEContext&);  // recompiled
void fn_sceAddDrv_00509d80(EEContext&);  // generated body
void fn_sceAddDrv_00509d80__recomp(EEContext&);  // recompiled
void fn_sceDclose_00509f98(EEContext&);  // generated body
void fn_sceDclose_00509f98__recomp(EEContext&);  // recompiled
void fn_sceDread_0050a100(EEContext&);  // generated body
void fn_sceDread_0050a100__recomp(EEContext&);  // recompiled
void fn_sceGetstat_0050a258(EEContext&);  // generated body
void fn_sceGetstat_0050a258__recomp(EEContext&);  // recompiled
void fn_sceChstat_0050a410(EEContext&);  // generated body
void fn_sceChstat_0050a410__recomp(EEContext&);  // recompiled
void fn_sceRename_0050a660(EEContext&);  // generated body
void fn_sceRename_0050a660__recomp(EEContext&);  // recompiled
void fn_sceMount_0050aa38(EEContext&);  // generated body
void fn_sceMount_0050aa38__recomp(EEContext&);  // recompiled
void fn_sceDevctl_0050af18(EEContext&);  // generated body
void fn_sceDevctl_0050af18__recomp(EEContext&);  // recompiled
void fn_sceSymlink_0050b1c0(EEContext&);  // generated body
void fn_sceSymlink_0050b1c0__recomp(EEContext&);  // recompiled
void fn_sceReadlink_0050b3b8(EEContext&);  // generated body
void fn_sceReadlink_0050b3b8__recomp(EEContext&);  // recompiled
void fn_sceSifLoadIopHeap_0050b7a8(EEContext&);  // generated body
void fn_sceSifLoadIopHeap_0050b7a8__recomp(EEContext&);  // recompiled
void fn_sceSifQueryMemSize_0050b898(EEContext&);  // generated body
void fn_sceSifQueryMemSize_0050b898__recomp(EEContext&);  // recompiled
void fn_sceSifQueryMaxFreeMemSize_0050b908(EEContext&);  // generated body
void fn_sceSifQueryMaxFreeMemSize_0050b908__recomp(EEContext&);  // recompiled
void fn_InitTLB32MB_0050ce40(EEContext&);  // generated body
void fn_InitTLB32MB_0050ce40__recomp(EEContext&);  // recompiled
void fn__kTLBException_0050d040(EEContext&);  // generated body
void fn__kTLBException_0050d040__recomp(EEContext&);  // recompiled
void fn__xlaunch_0050d140(EEContext&);  // generated body
void fn__xlaunch_0050d140__recomp(EEContext&);  // recompiled
void fn__sceCopy_0_0050d478(EEContext&);  // generated body
void fn__sceCopy_0_0050d478__recomp(EEContext&);  // recompiled
void fn__sceSetSyscall_1_0050d6b0(EEContext&);  // generated body
void fn__sceSetSyscall_1_0050d6b0__recomp(EEContext&);  // recompiled
void fn__sceCopy_1_0050d6c0(EEContext&);  // generated body
void fn__sceCopy_1_0050d6c0__recomp(EEContext&);  // recompiled
void fn__sceGetEntryAddress_0_0050d708(EEContext&);  // generated body
void fn__sceGetEntryAddress_0_0050d708__recomp(EEContext&);  // recompiled
void fn__sceCopy_2_0050d830(EEContext&);  // generated body
void fn__sceCopy_2_0050d830__recomp(EEContext&);  // recompiled
void fn__sceSetSyscall_2_0050d870(EEContext&);  // generated body
void fn__sceSetSyscall_2_0050d870__recomp(EEContext&);  // recompiled
void fn_cdvd_exit_0050fa48(EEContext&);  // generated body
void fn_cdvd_exit_0050fa48__recomp(EEContext&);  // recompiled
void fn_sceCdDiskReady_old_00510748(EEContext&);  // generated body
void fn_sceCdDiskReady_old_00510748__recomp(EEContext&);  // recompiled
void fn_sceCdSeek_00510d60(EEContext&);  // generated body
void fn_sceCdSeek_00510d60__recomp(EEContext&);  // recompiled
void fn_sceCdBreak_00510f88(EEContext&);  // generated body
void fn_sceCdBreak_00510f88__recomp(EEContext&);  // recompiled
void fn__pad_intr_hdr_00511288(EEContext&);  // generated body
void fn__pad_intr_hdr_00511288__recomp(EEContext&);  // recompiled
void fn_scePadSetDmaCallback_00512710(EEContext&);  // generated body
void fn_scePadSetDmaCallback_00512710__recomp(EEContext&);  // recompiled
void fn_sceSdRemoteCallbackQuit_00512e48(EEContext&);  // generated body
void fn_sceSdRemoteCallbackQuit_00512e48__recomp(EEContext&);  // recompiled
void fn_sceDbcSearchPortSpecific_0051cdd8(EEContext&);  // generated body
void fn_sceDbcSearchPortSpecific_0051cdd8__recomp(EEContext&);  // recompiled
void fn_sub_53B760_0053b760(EEContext&);  // generated body
void fn_sub_53B760_0053b760__recomp(EEContext&);  // recompiled
void fn_sub_53C200_0053c200(EEContext&);  // generated body
void fn_sub_53C200_0053c200__recomp(EEContext&);  // recompiled
void fn_sub_55FA40_0055fa40(EEContext&);  // generated body
void fn_sub_55FA40_0055fa40__recomp(EEContext&);  // recompiled
void fn_sub_560698_00560698(EEContext&);  // generated body
void fn_sub_560698_00560698__recomp(EEContext&);  // recompiled
void fn_sub_5646C0_005646c0(EEContext&);  // generated body
void fn_sub_5646C0_005646c0__recomp(EEContext&);  // recompiled
void fn_ROFS_ChangeDir_00565b90(EEContext&);  // generated body
void fn_ROFS_ChangeDir_00565b90__recomp(EEContext&);  // recompiled
void fn_rfmai_readRootDirRec_00567750(EEContext&);  // generated body
void fn_rfmai_readRootDirRec_00567750__recomp(EEContext&);  // recompiled
void fn_RFMAI_DescrambleG_00569d90(EEContext&);  // generated body
void fn_RFMAI_DescrambleG_00569d90__recomp(EEContext&);  // recompiled
void fn_rfdir_getDirEnt_0056bdc0(EEContext&);  // generated body
void fn_rfdir_getDirEnt_0056bdc0__recomp(EEContext&);  // recompiled
void fn_RFDIR_SetDirEnt_0056c188(EEContext&);  // generated body
void fn_RFDIR_SetDirEnt_0056c188__recomp(EEContext&);  // recompiled
void fn_rfdir_searchPath_0056c5f0(EEContext&);  // generated body
void fn_rfdir_searchPath_0056c5f0__recomp(EEContext&);  // recompiled
void fn_RFDIR_SearchPath_0056c7e8(EEContext&);  // generated body
void fn_RFDIR_SearchPath_0056c7e8__recomp(EEContext&);  // recompiled
void fn_sub_56CA20_0056ca20(EEContext&);  // generated body
void fn_sub_56CA20_0056ca20__recomp(EEContext&);  // recompiled
void fn_sub_56CA38_0056ca38(EEContext&);  // generated body
void fn_sub_56CA38_0056ca38__recomp(EEContext&);  // recompiled
void fn_sub_56CB58_0056cb58(EEContext&);  // generated body
void fn_sub_56CB58_0056cb58__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"_dispRefImage_0", 0x4C72D8, &recomp_gen::fn__dispRefImage_0_004c72d8, &recomp_gen::fn__dispRefImage_0_004c72d8__recomp},
    {"sceDmaPutStallAddr", 0x4FAC08, &recomp_gen::fn_sceDmaPutStallAddr_004fac08, &recomp_gen::fn_sceDmaPutStallAddr_004fac08__recomp},
    {"sceDmaSendI", 0x4FAD00, &recomp_gen::fn_sceDmaSendI_004fad00, &recomp_gen::fn_sceDmaSendI_004fad00__recomp},
    {"sceDmaRecv", 0x4FAD78, &recomp_gen::fn_sceDmaRecv_004fad78, &recomp_gen::fn_sceDmaRecv_004fad78__recomp},
    {"sceDmaRecvI", 0x4FAE40, &recomp_gen::fn_sceDmaRecvI_004fae40, &recomp_gen::fn_sceDmaRecvI_004fae40__recomp},
    {"sceDmaWatch", 0x4FAEF8, &recomp_gen::fn_sceDmaWatch_004faef8, &recomp_gen::fn_sceDmaWatch_004faef8__recomp},
    {"sceDmaRestart", 0x4FAFC8, &recomp_gen::fn_sceDmaRestart_004fafc8, &recomp_gen::fn_sceDmaRestart_004fafc8__recomp},
    {"_sequenceExtension", 0x4FF378, &recomp_gen::fn__sequenceExtension_004ff378, &recomp_gen::fn__sequenceExtension_004ff378__recomp},
    {"_quantMatrixExtension", 0x4FF4B8, &recomp_gen::fn__quantMatrixExtension_004ff4b8, &recomp_gen::fn__quantMatrixExtension_004ff4b8__recomp},
    {"_sequenceScalableExtension", 0x4FF5A0, &recomp_gen::fn__sequenceScalableExtension_004ff5a0, &recomp_gen::fn__sequenceScalableExtension_004ff5a0__recomp},
    {"_pictureSpatialScalableExtension", 0x4FF7A8, &recomp_gen::fn__pictureSpatialScalableExtension_004ff7a8, &recomp_gen::fn__pictureSpatialScalableExtension_004ff7a8__recomp},
    {"_sequenceDisplayExtension", 0x4FFB88, &recomp_gen::fn__sequenceDisplayExtension_004ffb88, &recomp_gen::fn__sequenceDisplayExtension_004ffb88__recomp},
    {"_copyrightExtension", 0x4FFC18, &recomp_gen::fn__copyrightExtension_004ffc18, &recomp_gen::fn__copyrightExtension_004ffc18__recomp},
    {"_pictureDisplayExtension", 0x4FFCB0, &recomp_gen::fn__pictureDisplayExtension_004ffcb0, &recomp_gen::fn__pictureDisplayExtension_004ffcb0__recomp},
    {"RFU000_FullReset", 0x502D40, &recomp_gen::fn_RFU000_FullReset_00502d40, &recomp_gen::fn_RFU000_FullReset_00502d40__recomp},
    {"ResetEE", 0x502D50, &recomp_gen::fn_ResetEE_00502d50, &recomp_gen::fn_ResetEE_00502d50__recomp},
    {"RFU003", 0x502D70, &recomp_gen::fn_RFU003_00502d70, &recomp_gen::fn_RFU003_00502d70__recomp},
    {"RFU005", 0x502D90, &recomp_gen::fn_RFU005_00502d90, &recomp_gen::fn_RFU005_00502d90__recomp},
    {"RFU008", 0x502DC0, &recomp_gen::fn_RFU008_00502dc0, &recomp_gen::fn_RFU008_00502dc0__recomp},
    {"RFU009", 0x502DD0, &recomp_gen::fn_RFU009_00502dd0, &recomp_gen::fn_RFU009_00502dd0__recomp},
    {"AddSbusIntcHandler", 0x502DE0, &recomp_gen::fn_AddSbusIntcHandler_00502de0, &recomp_gen::fn_AddSbusIntcHandler_00502de0__recomp},
    {"RemoveSbusIntcHandler", 0x502DF0, &recomp_gen::fn_RemoveSbusIntcHandler_00502df0, &recomp_gen::fn_RemoveSbusIntcHandler_00502df0__recomp},
    {"Interrupt2Iop", 0x502E00, &recomp_gen::fn_Interrupt2Iop_00502e00, &recomp_gen::fn_Interrupt2Iop_00502e00__recomp},
    {"SetVInterruptHandler", 0x502E30, &recomp_gen::fn_SetVInterruptHandler_00502e30, &recomp_gen::fn_SetVInterruptHandler_00502e30__recomp},
    {"SetAlarm", 0x502EE0, &recomp_gen::fn_SetAlarm_00502ee0, &recomp_gen::fn_SetAlarm_00502ee0__recomp},
    {"ReleaseAlarm", 0x502EF0, &recomp_gen::fn_ReleaseAlarm_00502ef0, &recomp_gen::fn_ReleaseAlarm_00502ef0__recomp},
    {"iSetAlarm", 0x502F40, &recomp_gen::fn_iSetAlarm_00502f40, &recomp_gen::fn_iSetAlarm_00502f40__recomp},
    {"iReleaseAlarm", 0x502F50, &recomp_gen::fn_iReleaseAlarm_00502f50, &recomp_gen::fn_iReleaseAlarm_00502f50__recomp},
    {"ExitThread", 0x502F90, &recomp_gen::fn_ExitThread_00502f90, &recomp_gen::fn_ExitThread_00502f90__recomp},
    {"iTerminateThread", 0x502FC0, &recomp_gen::fn_iTerminateThread_00502fc0, &recomp_gen::fn_iTerminateThread_00502fc0__recomp},
    {"DisableDispatchThread", 0x502FD0, &recomp_gen::fn_DisableDispatchThread_00502fd0, &recomp_gen::fn_DisableDispatchThread_00502fd0__recomp},
    {"EnableDispatchThread", 0x502FE0, &recomp_gen::fn_EnableDispatchThread_00502fe0, &recomp_gen::fn_EnableDispatchThread_00502fe0__recomp},
    {"_iRotateThreadReadyQueue", 0x503020, &recomp_gen::fn__iRotateThreadReadyQueue_00503020, &recomp_gen::fn__iRotateThreadReadyQueue_00503020__recomp},
    {"ReleaseWaitThread", 0x503030, &recomp_gen::fn_ReleaseWaitThread_00503030, &recomp_gen::fn_ReleaseWaitThread_00503030__recomp},
    {"iReleaseWaitThread", 0x503040, &recomp_gen::fn_iReleaseWaitThread_00503040, &recomp_gen::fn_iReleaseWaitThread_00503040__recomp},
    {"CancelWakeupThread", 0x5030B0, &recomp_gen::fn_CancelWakeupThread_005030b0, &recomp_gen::fn_CancelWakeupThread_005030b0__recomp},
    {"iCancelWakeupThread", 0x5030C0, &recomp_gen::fn_iCancelWakeupThread_005030c0, &recomp_gen::fn_iCancelWakeupThread_005030c0__recomp},
    {"iResumeThread", 0x503100, &recomp_gen::fn_iResumeThread_00503100, &recomp_gen::fn_iResumeThread_00503100__recomp},
    {"JoinThread", 0x503110, &recomp_gen::fn_JoinThread_00503110, &recomp_gen::fn_JoinThread_00503110__recomp},
    {"RFU060", 0x503120, &recomp_gen::fn_RFU060_00503120, &recomp_gen::fn_RFU060_00503120__recomp},
    {"RFU061", 0x503130, &recomp_gen::fn_RFU061_00503130, &recomp_gen::fn_RFU061_00503130__recomp},
    {"RFU063", 0x503150, &recomp_gen::fn_RFU063_00503150, &recomp_gen::fn_RFU063_00503150__recomp},
    {"iPollSema", 0x5031C0, &recomp_gen::fn_iPollSema_005031c0, &recomp_gen::fn_iPollSema_005031c0__recomp},
    {"ReferSemaStatus", 0x5031D0, &recomp_gen::fn_ReferSemaStatus_005031d0, &recomp_gen::fn_ReferSemaStatus_005031d0__recomp},
    {"iReferSemaStatus", 0x5031E0, &recomp_gen::fn_iReferSemaStatus_005031e0, &recomp_gen::fn_iReferSemaStatus_005031e0__recomp},
    {"RFU073", 0x5031F0, &recomp_gen::fn_RFU073_005031f0, &recomp_gen::fn_RFU073_005031f0__recomp},
    {"GetGsHParam", 0x503220, &recomp_gen::fn_GetGsHParam_00503220, &recomp_gen::fn_GetGsHParam_00503220__recomp},
    {"GetGsVParam", 0x503230, &recomp_gen::fn_GetGsVParam_00503230, &recomp_gen::fn_GetGsVParam_00503230__recomp},
    {"SetGsHParam", 0x503240, &recomp_gen::fn_SetGsHParam_00503240, &recomp_gen::fn_SetGsHParam_00503240__recomp},
    {"SetGsVParam", 0x503250, &recomp_gen::fn_SetGsVParam_00503250, &recomp_gen::fn_SetGsVParam_00503250__recomp},
    {"RFU080_CreateEventFlag", 0x503260, &recomp_gen::fn_RFU080_CreateEventFlag_00503260, &recomp_gen::fn_RFU080_CreateEventFlag_00503260__recomp},
    {"RFU081_DeleteEventFlag", 0x503270, &recomp_gen::fn_RFU081_DeleteEventFlag_00503270, &recomp_gen::fn_RFU081_DeleteEventFlag_00503270__recomp},
    {"RFU082_SetEventFlag", 0x503280, &recomp_gen::fn_RFU082_SetEventFlag_00503280, &recomp_gen::fn_RFU082_SetEventFlag_00503280__recomp},
    {"RFU083_iSetEventFlag", 0x503290, &recomp_gen::fn_RFU083_iSetEventFlag_00503290, &recomp_gen::fn_RFU083_iSetEventFlag_00503290__recomp},
    {"RFU084_ClearEventFlag", 0x5032A0, &recomp_gen::fn_RFU084_ClearEventFlag_005032a0, &recomp_gen::fn_RFU084_ClearEventFlag_005032a0__recomp},
    {"RFU085_iClearEventFlag", 0x5032B0, &recomp_gen::fn_RFU085_iClearEventFlag_005032b0, &recomp_gen::fn_RFU085_iClearEventFlag_005032b0__recomp},
    {"RFU086_WaitEvnetFlag", 0x5032C0, &recomp_gen::fn_RFU086_WaitEvnetFlag_005032c0, &recomp_gen::fn_RFU086_WaitEvnetFlag_005032c0__recomp},
    {"RFU087_PollEvnetFlag", 0x5032D0, &recomp_gen::fn_RFU087_PollEvnetFlag_005032d0, &recomp_gen::fn_RFU087_PollEvnetFlag_005032d0__recomp},
    {"RFU088_iPollEvnetFlag", 0x5032E0, &recomp_gen::fn_RFU088_iPollEvnetFlag_005032e0, &recomp_gen::fn_RFU088_iPollEvnetFlag_005032e0__recomp},
    {"RFU089_ReferEventFlagStatus", 0x5032F0, &recomp_gen::fn_RFU089_ReferEventFlagStatus_005032f0, &recomp_gen::fn_RFU089_ReferEventFlagStatus_005032f0__recomp},
    {"RFU090_iReferEventFlagStatus", 0x503300, &recomp_gen::fn_RFU090_iReferEventFlagStatus_00503300, &recomp_gen::fn_RFU090_iReferEventFlagStatus_00503300__recomp},
    {"RFU091", 0x503310, &recomp_gen::fn_RFU091_00503310, &recomp_gen::fn_RFU091_00503310__recomp},
    {"EnableIntcHandler", 0x503320, &recomp_gen::fn_EnableIntcHandler_00503320, &recomp_gen::fn_EnableIntcHandler_00503320__recomp},
    {"iEnableIntcHandler", 0x503330, &recomp_gen::fn_iEnableIntcHandler_00503330, &recomp_gen::fn_iEnableIntcHandler_00503330__recomp},
    {"DisableIntcHandler", 0x503340, &recomp_gen::fn_DisableIntcHandler_00503340, &recomp_gen::fn_DisableIntcHandler_00503340__recomp},
    {"iDisableIntcHandler", 0x503350, &recomp_gen::fn_iDisableIntcHandler_00503350, &recomp_gen::fn_iDisableIntcHandler_00503350__recomp},
    {"EnableDmacHandler", 0x503360, &recomp_gen::fn_EnableDmacHandler_00503360, &recomp_gen::fn_EnableDmacHandler_00503360__recomp},
    {"iEnableDmacHandler", 0x503370, &recomp_gen::fn_iEnableDmacHandler_00503370, &recomp_gen::fn_iEnableDmacHandler_00503370__recomp},
    {"DisableDmacHandler", 0x503380, &recomp_gen::fn_DisableDmacHandler_00503380, &recomp_gen::fn_DisableDmacHandler_00503380__recomp},
    {"iDisableDmacHandler", 0x503390, &recomp_gen::fn_iDisableDmacHandler_00503390, &recomp_gen::fn_iDisableDmacHandler_00503390__recomp},
    {"KSeg0", 0x5033A0, &recomp_gen::fn_KSeg0_005033a0, &recomp_gen::fn_KSeg0_005033a0__recomp},
    {"EnableCache", 0x5033B0, &recomp_gen::fn_EnableCache_005033b0, &recomp_gen::fn_EnableCache_005033b0__recomp},
    {"DisableCache", 0x5033C0, &recomp_gen::fn_DisableCache_005033c0, &recomp_gen::fn_DisableCache_005033c0__recomp},
    {"GetCop0", 0x5033D0, &recomp_gen::fn_GetCop0_005033d0, &recomp_gen::fn_GetCop0_005033d0__recomp},
    {"CpuConfig", 0x5033F0, &recomp_gen::fn_CpuConfig_005033f0, &recomp_gen::fn_CpuConfig_005033f0__recomp},
    {"iGetCop0", 0x503400, &recomp_gen::fn_iGetCop0_00503400, &recomp_gen::fn_iGetCop0_00503400__recomp},
    {"iFlushCache", 0x503410, &recomp_gen::fn_iFlushCache_00503410, &recomp_gen::fn_iFlushCache_00503410__recomp},
    {"iCpuConfig", 0x503420, &recomp_gen::fn_iCpuConfig_00503420, &recomp_gen::fn_iCpuConfig_00503420__recomp},
    {"SetCPUTimerHandler", 0x503440, &recomp_gen::fn_SetCPUTimerHandler_00503440, &recomp_gen::fn_SetCPUTimerHandler_00503440__recomp},
    {"SetCPUTimer", 0x503450, &recomp_gen::fn_SetCPUTimer_00503450, &recomp_gen::fn_SetCPUTimer_00503450__recomp},
    {"SetOsdConfigParam2", 0x503460, &recomp_gen::fn_SetOsdConfigParam2_00503460, &recomp_gen::fn_SetOsdConfigParam2_00503460__recomp},
    {"GetOsdConfigParam2", 0x503470, &recomp_gen::fn_GetOsdConfigParam2_00503470, &recomp_gen::fn_GetOsdConfigParam2_00503470__recomp},
    {"iGsGetIMR", 0x503490, &recomp_gen::fn_iGsGetIMR_00503490, &recomp_gen::fn_iGsGetIMR_00503490__recomp},
    {"iGsPutIMR", 0x5034B0, &recomp_gen::fn_iGsPutIMR_005034b0, &recomp_gen::fn_iGsPutIMR_005034b0__recomp},
    {"SetPgifHandler", 0x5034C0, &recomp_gen::fn_SetPgifHandler_005034c0, &recomp_gen::fn_SetPgifHandler_005034c0__recomp},
    {"RFU116", 0x5034E0, &recomp_gen::fn_RFU116_005034e0, &recomp_gen::fn_RFU116_005034e0__recomp},
    {"_print", 0x5034F0, &recomp_gen::fn__print_005034f0, &recomp_gen::fn__print_005034f0__recomp},
    {"isceSifDmaStat", 0x503510, &recomp_gen::fn_isceSifDmaStat_00503510, &recomp_gen::fn_isceSifDmaStat_00503510__recomp},
    {"PSMode", 0x5035A0, &recomp_gen::fn_PSMode_005035a0, &recomp_gen::fn_PSMode_005035a0__recomp},
    {"MachineType", 0x5035B0, &recomp_gen::fn_MachineType_005035b0, &recomp_gen::fn_MachineType_005035b0__recomp},
    {"iSuspendThread", 0x504140, &recomp_gen::fn_iSuspendThread_00504140, &recomp_gen::fn_iSuspendThread_00504140__recomp},
    {"_DelayThreadHandler", 0x504418, &recomp_gen::fn__DelayThreadHandler_00504418, &recomp_gen::fn__DelayThreadHandler_00504418__recomp},
    {"isceSifSetDma", 0x506110, &recomp_gen::fn_isceSifSetDma_00506110, &recomp_gen::fn_isceSifSetDma_00506110__recomp},
    {"_alarm_rdata", 0x506C78, &recomp_gen::fn__alarm_rdata_00506c78, &recomp_gen::fn__alarm_rdata_00506c78__recomp},
    {"_request_rdata", 0x506CB8, &recomp_gen::fn__request_rdata_00506cb8, &recomp_gen::fn__request_rdata_00506cb8__recomp},
    {"sceSifGetOtherData", 0x506D88, &recomp_gen::fn_sceSifGetOtherData_00506d88, &recomp_gen::fn_sceSifGetOtherData_00506d88__recomp},
    {"_alarm_bind", 0x506F40, &recomp_gen::fn__alarm_bind_00506f40, &recomp_gen::fn__alarm_bind_00506f40__recomp},
    {"_request_bind", 0x506F80, &recomp_gen::fn__request_bind_00506f80, &recomp_gen::fn__request_bind_00506f80__recomp},
    {"sceSifExecRequest", 0x507758, &recomp_gen::fn_sceSifExecRequest_00507758, &recomp_gen::fn_sceSifExecRequest_00507758__recomp},
    {"_sceFs_Poff_Intr", 0x508128, &recomp_gen::fn__sceFs_Poff_Intr_00508128, &recomp_gen::fn__sceFs_Poff_Intr_00508128__recomp},
    {"sceFsSetIopBuf", 0x508440, &recomp_gen::fn_sceFsSetIopBuf_00508440, &recomp_gen::fn_sceFsSetIopBuf_00508440__recomp},
    {"sceFsSetIopPrio", 0x508580, &recomp_gen::fn_sceFsSetIopPrio_00508580, &recomp_gen::fn_sceFsSetIopPrio_00508580__recomp},
    {"sceIoctl2", 0x509570, &recomp_gen::fn_sceIoctl2_00509570, &recomp_gen::fn_sceIoctl2_00509570__recomp},
    {"sceMkdir", 0x509928, &recomp_gen::fn_sceMkdir_00509928, &recomp_gen::fn_sceMkdir_00509928__recomp},
    {"sceFormat", 0x509B00, &recomp_gen::fn_sceFormat_00509b00, &recomp_gen::fn_sceFormat_00509b00__recomp},
    {"sceAddDrv", 0x509D80, &recomp_gen::fn_sceAddDrv_00509d80, &recomp_gen::fn_sceAddDrv_00509d80__recomp},
    {"sceDclose", 0x509F98, &recomp_gen::fn_sceDclose_00509f98, &recomp_gen::fn_sceDclose_00509f98__recomp},
    {"sceDread", 0x50A100, &recomp_gen::fn_sceDread_0050a100, &recomp_gen::fn_sceDread_0050a100__recomp},
    {"sceGetstat", 0x50A258, &recomp_gen::fn_sceGetstat_0050a258, &recomp_gen::fn_sceGetstat_0050a258__recomp},
    {"sceChstat", 0x50A410, &recomp_gen::fn_sceChstat_0050a410, &recomp_gen::fn_sceChstat_0050a410__recomp},
    {"sceRename", 0x50A660, &recomp_gen::fn_sceRename_0050a660, &recomp_gen::fn_sceRename_0050a660__recomp},
    {"sceMount", 0x50AA38, &recomp_gen::fn_sceMount_0050aa38, &recomp_gen::fn_sceMount_0050aa38__recomp},
    {"sceDevctl", 0x50AF18, &recomp_gen::fn_sceDevctl_0050af18, &recomp_gen::fn_sceDevctl_0050af18__recomp},
    {"sceSymlink", 0x50B1C0, &recomp_gen::fn_sceSymlink_0050b1c0, &recomp_gen::fn_sceSymlink_0050b1c0__recomp},
    {"sceReadlink", 0x50B3B8, &recomp_gen::fn_sceReadlink_0050b3b8, &recomp_gen::fn_sceReadlink_0050b3b8__recomp},
    {"sceSifLoadIopHeap", 0x50B7A8, &recomp_gen::fn_sceSifLoadIopHeap_0050b7a8, &recomp_gen::fn_sceSifLoadIopHeap_0050b7a8__recomp},
    {"sceSifQueryMemSize", 0x50B898, &recomp_gen::fn_sceSifQueryMemSize_0050b898, &recomp_gen::fn_sceSifQueryMemSize_0050b898__recomp},
    {"sceSifQueryMaxFreeMemSize", 0x50B908, &recomp_gen::fn_sceSifQueryMaxFreeMemSize_0050b908, &recomp_gen::fn_sceSifQueryMaxFreeMemSize_0050b908__recomp},
    {"InitTLB32MB", 0x50CE40, &recomp_gen::fn_InitTLB32MB_0050ce40, &recomp_gen::fn_InitTLB32MB_0050ce40__recomp},
    {"_kTLBException", 0x50D040, &recomp_gen::fn__kTLBException_0050d040, &recomp_gen::fn__kTLBException_0050d040__recomp},
    {"_xlaunch", 0x50D140, &recomp_gen::fn__xlaunch_0050d140, &recomp_gen::fn__xlaunch_0050d140__recomp},
    {"_sceCopy_0", 0x50D478, &recomp_gen::fn__sceCopy_0_0050d478, &recomp_gen::fn__sceCopy_0_0050d478__recomp},
    {"_sceSetSyscall_1", 0x50D6B0, &recomp_gen::fn__sceSetSyscall_1_0050d6b0, &recomp_gen::fn__sceSetSyscall_1_0050d6b0__recomp},
    {"_sceCopy_1", 0x50D6C0, &recomp_gen::fn__sceCopy_1_0050d6c0, &recomp_gen::fn__sceCopy_1_0050d6c0__recomp},
    {"_sceGetEntryAddress_0", 0x50D708, &recomp_gen::fn__sceGetEntryAddress_0_0050d708, &recomp_gen::fn__sceGetEntryAddress_0_0050d708__recomp},
    {"_sceCopy_2", 0x50D830, &recomp_gen::fn__sceCopy_2_0050d830, &recomp_gen::fn__sceCopy_2_0050d830__recomp},
    {"_sceSetSyscall_2", 0x50D870, &recomp_gen::fn__sceSetSyscall_2_0050d870, &recomp_gen::fn__sceSetSyscall_2_0050d870__recomp},
    {"cdvd_exit", 0x50FA48, &recomp_gen::fn_cdvd_exit_0050fa48, &recomp_gen::fn_cdvd_exit_0050fa48__recomp},
    {"sceCdDiskReady_old", 0x510748, &recomp_gen::fn_sceCdDiskReady_old_00510748, &recomp_gen::fn_sceCdDiskReady_old_00510748__recomp},
    {"sceCdSeek", 0x510D60, &recomp_gen::fn_sceCdSeek_00510d60, &recomp_gen::fn_sceCdSeek_00510d60__recomp},
    {"sceCdBreak", 0x510F88, &recomp_gen::fn_sceCdBreak_00510f88, &recomp_gen::fn_sceCdBreak_00510f88__recomp},
    {"_pad_intr_hdr", 0x511288, &recomp_gen::fn__pad_intr_hdr_00511288, &recomp_gen::fn__pad_intr_hdr_00511288__recomp},
    {"scePadSetDmaCallback", 0x512710, &recomp_gen::fn_scePadSetDmaCallback_00512710, &recomp_gen::fn_scePadSetDmaCallback_00512710__recomp},
    {"sceSdRemoteCallbackQuit", 0x512E48, &recomp_gen::fn_sceSdRemoteCallbackQuit_00512e48, &recomp_gen::fn_sceSdRemoteCallbackQuit_00512e48__recomp},
    {"sceDbcSearchPortSpecific", 0x51CDD8, &recomp_gen::fn_sceDbcSearchPortSpecific_0051cdd8, &recomp_gen::fn_sceDbcSearchPortSpecific_0051cdd8__recomp},
    {"sub_53B760", 0x53B760, &recomp_gen::fn_sub_53B760_0053b760, &recomp_gen::fn_sub_53B760_0053b760__recomp},
    {"sub_53C200", 0x53C200, &recomp_gen::fn_sub_53C200_0053c200, &recomp_gen::fn_sub_53C200_0053c200__recomp},
    {"sub_55FA40", 0x55FA40, &recomp_gen::fn_sub_55FA40_0055fa40, &recomp_gen::fn_sub_55FA40_0055fa40__recomp},
    {"sub_560698", 0x560698, &recomp_gen::fn_sub_560698_00560698, &recomp_gen::fn_sub_560698_00560698__recomp},
    {"sub_5646C0", 0x5646C0, &recomp_gen::fn_sub_5646C0_005646c0, &recomp_gen::fn_sub_5646C0_005646c0__recomp},
    {"ROFS_ChangeDir", 0x565B90, &recomp_gen::fn_ROFS_ChangeDir_00565b90, &recomp_gen::fn_ROFS_ChangeDir_00565b90__recomp},
    {"rfmai_readRootDirRec", 0x567750, &recomp_gen::fn_rfmai_readRootDirRec_00567750, &recomp_gen::fn_rfmai_readRootDirRec_00567750__recomp},
    {"RFMAI_DescrambleG", 0x569D90, &recomp_gen::fn_RFMAI_DescrambleG_00569d90, &recomp_gen::fn_RFMAI_DescrambleG_00569d90__recomp},
    {"rfdir_getDirEnt", 0x56BDC0, &recomp_gen::fn_rfdir_getDirEnt_0056bdc0, &recomp_gen::fn_rfdir_getDirEnt_0056bdc0__recomp},
    {"RFDIR_SetDirEnt", 0x56C188, &recomp_gen::fn_RFDIR_SetDirEnt_0056c188, &recomp_gen::fn_RFDIR_SetDirEnt_0056c188__recomp},
    {"rfdir_searchPath", 0x56C5F0, &recomp_gen::fn_rfdir_searchPath_0056c5f0, &recomp_gen::fn_rfdir_searchPath_0056c5f0__recomp},
    {"RFDIR_SearchPath", 0x56C7E8, &recomp_gen::fn_RFDIR_SearchPath_0056c7e8, &recomp_gen::fn_RFDIR_SearchPath_0056c7e8__recomp},
    {"sub_56CA20", 0x56CA20, &recomp_gen::fn_sub_56CA20_0056ca20, &recomp_gen::fn_sub_56CA20_0056ca20__recomp},
    {"sub_56CA38", 0x56CA38, &recomp_gen::fn_sub_56CA38_0056ca38, &recomp_gen::fn_sub_56CA38_0056ca38__recomp},
    {"sub_56CB58", 0x56CB58, &recomp_gen::fn_sub_56CB58_0056cb58, &recomp_gen::fn_sub_56CB58_0056cb58__recomp},
};

// Random worlds: 64 KiB of free RAM above the harness's arena.
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

}  // namespace

TEST_CASE("game(libs26): every body equals its recompiled body on random worlds") {
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

namespace L26 = p3fes::game::libs26;
using p3fes::game::rofs_dir_entry;

void w8(Machine& m, u32 va, u8 v) { *m.at(va) = v; }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
u32 r32(Machine& m, u32 va) {
    u32 v = 0;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
void wstr(Machine& m, u32 va, const char* s) { std::memcpy(m.at(va), s, std::strlen(s) + 1); }
std::string rstr(Machine& m, u32 va) { return std::string(reinterpret_cast<const char*>(m.at(va))); }
u64 v0_of(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }

const Case& find_case(const char* name) {
    for (const Case& c : kCases)
        if (std::string(c.name) == name) return c;
    FAIL("no case " << name);
    return kCases[0];
}

// A pair with a stand-in world around each body (`setup` builds both alike); both call logs must be equal. The worlds
// stay alive in `last` for the rule checks (the recompiled run's log in last[1]).
std::unique_ptr<StandInWorld> g_world[2];
Fn g_fn[2];
void thunk0(EEContext& ctx) {
    StandInsScope s(g_world[0]->si);
    g_fn[0](ctx);
}
void thunk1(EEContext& ctx) {
    StandInsScope s(g_world[1]->si);
    g_fn[1](ctx);
}
HwCheck full_hw() {
    HwCheck hw;
    hw.gpr_mask = kAllGprs;
    hw.compare_checkpoint_regs = true;
    hw.compare_dead_stack = true;
    hw.compare_hilo = true;
    return hw;
}
hgp::Run spair(Machine& m, const Case& c, const Args& args, u32 seed, HwCheck hw, const WorldSetup& setup) {
    for (auto& w : g_world) {
        w = std::make_unique<StandInWorld>();
        if (setup) setup(*w);
    }
    g_fn[0] = c.hand;
    g_fn[1] = c.recomp;
    const hgp::Run r = hgp::pair(m, &thunk0, &thunk1, args, seed, c.name, hw);
    expect_same_log(g_world[0]->si, g_world[1]->si, c.name);
    return r;
}
std::size_t calls_to(u32 va) {
    return static_cast<std::size_t>(std::count_if(g_world[1]->si.log.begin(), g_world[1]->si.log.end(), [va](const StandInCall& k) { return k.va == va; }));
}

// --- kernel call wrappers -------------------------------------------------------------------------------------------
struct Sys {
    const char* name;
    s32 number;
};
const Sys kSys[] = {
    {"RFU000_FullReset", 0}, {"ResetEE", 1}, {"RFU003", 3}, {"RFU005", 5}, {"RFU008", 8}, {"RFU009", 9},
    {"AddSbusIntcHandler", 10}, {"RemoveSbusIntcHandler", 11}, {"Interrupt2Iop", 12}, {"SetVInterruptHandler", 15},
    {"SetAlarm", 252}, {"ReleaseAlarm", 253}, {"iSetAlarm", -254}, {"iReleaseAlarm", -255}, {"ExitThread", 35},
    {"iTerminateThread", -38}, {"DisableDispatchThread", 39}, {"EnableDispatchThread", 40},
    {"_iRotateThreadReadyQueue", -44}, {"ReleaseWaitThread", 45}, {"iReleaseWaitThread", -46},
    {"CancelWakeupThread", 53}, {"iCancelWakeupThread", -54}, {"iResumeThread", -58}, {"JoinThread", 59},
    {"RFU060", 60}, {"RFU061", 61}, {"RFU063", 63}, {"iPollSema", -70}, {"ReferSemaStatus", 71},
    {"iReferSemaStatus", -72}, {"RFU073", 73}, {"GetGsHParam", 76}, {"GetGsVParam", 77}, {"SetGsHParam", 78},
    {"SetGsVParam", 79}, {"RFU080_CreateEventFlag", 80}, {"RFU081_DeleteEventFlag", 81}, {"RFU082_SetEventFlag", 82},
    {"RFU083_iSetEventFlag", -83}, {"RFU084_ClearEventFlag", 84}, {"RFU085_iClearEventFlag", -85},
    {"RFU086_WaitEvnetFlag", 86}, {"RFU087_PollEvnetFlag", 87}, {"RFU088_iPollEvnetFlag", -88},
    {"RFU089_ReferEventFlagStatus", 89}, {"RFU090_iReferEventFlagStatus", -90}, {"RFU091", 91},
    {"EnableIntcHandler", 92}, {"iEnableIntcHandler", -92}, {"DisableIntcHandler", 93}, {"iDisableIntcHandler", -93},
    {"EnableDmacHandler", 94}, {"iEnableDmacHandler", -94}, {"DisableDmacHandler", 95}, {"iDisableDmacHandler", -95},
    {"KSeg0", 96}, {"EnableCache", 97}, {"DisableCache", 98}, {"GetCop0", 99}, {"CpuConfig", 102}, {"iGetCop0", -103},
    {"iFlushCache", -104}, {"iCpuConfig", -106}, {"SetCPUTimerHandler", 108}, {"SetCPUTimer", 109},
    {"SetOsdConfigParam2", 110}, {"GetOsdConfigParam2", 111}, {"iGsGetIMR", -112}, {"iGsPutIMR", -113},
    {"SetPgifHandler", 114}, {"RFU116", 116}, {"_print", 117}, {"isceSifDmaStat", -118}, {"PSMode", 125},
    {"MachineType", 126}, {"_sceCopy_0", 90}, {"_sceSetSyscall_1", 116}, {"_sceCopy_1", 90},
    {"_sceGetEntryAddress_0", 91}, {"_sceCopy_2", 90}, {"_sceSetSyscall_2", 116},
};

// --- the IPU bit reader stood in (a host reader over the bits written below) ---------------------------------------
constexpr u32 kNextBit = 0x4FD658u;    // _sceMpegNextBit(dec, n): the next n bits
constexpr u32 kMpegError = 0x502668u;  // _sceMpegError(dec, text)
struct Bits {
    std::vector<u8> bits;
    void put(u32 v, u32 n) {
        for (u32 k = n; k-- > 0;) bits.push_back(static_cast<u8>((v >> k) & 1u));
    }
};
WorldSetup bit_world(std::shared_ptr<const Bits> b) {
    return [b](StandInWorld& w) {
        auto pos = std::make_shared<std::size_t>(0);
        w.si.install(kNextBit, "_sceMpegNextBit", [b, pos](EEContext&, StandIns&, StandInCall& c) {
            u32 v = 0;
            for (u32 k = 0; k < static_cast<u32>(c.args[1] & 31u); ++k, ++*pos) v = (v << 1) | (*pos < b->bits.size() ? b->bits[*pos] : 0u);
            c.v0 = v;
        }, 4);
        w.si.install(kMpegError, "_sceMpegError", [](EEContext& ctx, StandIns&, StandInCall& c) {
            const u32 va = static_cast<u32>(c.args[1]);
            for (u32 a = va; va >= 0x00100000u && a < 0x01FF0000u && c.text.size() < 255; ++a) {
                const char ch = static_cast<char>(ctx.memory->read<u8>(a));
                if (ch == 0) break;
                c.text += ch;
            }
        }, 3);
    };
}

// The decoder record of the extension parsers (the words they read; everything else zero).
constexpr u32 kDec = 0x01820000u;
constexpr u32 kDecSize = 0x1000u;

// --- DMAC channels (scripted hardware registers) --------------------------------------------------------------------
const u32 kChannels[] = {0x10008000u, 0x10009000u, 0x1000A000u, 0x1000B000u, 0x1000B400u,
                         0x1000C000u, 0x1000C400u, 0x1000C800u, 0x1000D000u, 0x1000D400u};

}  // namespace

TEST_CASE("game(libs26): kernel call wrappers, DMAC channels and D_STADR") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    // Every wrapper makes exactly one kernel call with its number in $v1 and returns the kernel's $v0 (the harness's
    // kernel answers 0x600DF00D).
    for (const Sys& s : kSys) {
        const Case& c = find_case(s.name);
        for (u32 seed = 1; seed <= 4; ++seed) {
            std::mt19937 rng{seed * 31u + c.addr};
            const Args args{sx(kWorld + 0x100u * (rng() % 64)), rng() % 64, sx(rng()), 0};
            const hgp::Run r = spair(*m, c, args, seed, full_hw(), {});
            INFO(s.name);
            CHECK(r.syscalls == 1);
            CHECK(r.end.gpr[GPR_V1].u64[0] == static_cast<u64>(static_cast<s64>(s.number)));
            CHECK(v0_of(r) == 0x600DF00Du);
        }
    }
    // The DMAC helpers on every channel, CHCR / MADR / QWC drawn per pair (MADR -1 a third of the time).
    const char* kDma[] = {"sceDmaSendI", "sceDmaRecv", "sceDmaRecvI", "sceDmaWatch", "sceDmaRestart", "sceDmaPutStallAddr"};
    int checked = 0;
    for (const char* name : kDma) {
        const Case& c = find_case(name);
        for (const u32 ch : kChannels) {
            for (u32 seed = 1; seed <= 4; ++seed) {
                std::mt19937 rng{seed * 977u + ch + c.addr};
                HwCheck hw = full_hw();
                const u32 chcr = rng();
                const u32 madr = rng() % 3 == 0 ? 0xFFFFFFFFu : (kWorld + ((rng() % kWorldSize) & ~15u));
                const u32 stadr = rng();
                hw.regs[ch + L26::dmac::kChcr] = chcr;
                hw.regs[ch + L26::dmac::kMadr] = madr;
                hw.regs[ch + L26::dmac::kQwc] = rng() % 0x10000u;
                hw.regs[L26::dmac::kStadr] = stadr;
                const u32 addr = kWorld + ((rng() % kWorldSize) & ~15u);
                const u32 arg2 = seed % 2 ? 1u : rng() % 0x100u;  // sceDmaWatch: mode 1 half the time
                const Args args{sx(ch), sx(addr), arg2, rng() % 0x100u};
                const hgp::Run r = spair(*m, c, args, seed, hw, {});
                INFO(name << " channel " << std::hex << ch);
                const std::string n = name;
                if (n == "sceDmaRestart") {
                    // the old STR bit; the new CHCR stored
                    CHECK(v0_of(r) == ((chcr >> 8) & 1u));
                    REQUIRE(!r.bus.empty());
                    CHECK(r.bus.back().write);
                    CHECK(r.bus.back().pa == ch);
                    CHECK(static_cast<u32>(r.bus.back().lo) == addr);
                    ++checked;
                } else if (n == "sceDmaPutStallAddr") {
                    CHECK(v0_of(r) == sx(stadr));
                    REQUIRE(!r.bus.empty());
                    CHECK(r.bus.back().write);
                    CHECK(r.bus.back().pa == L26::dmac::kStadr);
                    CHECK(static_cast<u32>(r.bus.back().lo) == ch);
                    ++checked;
                } else if (n == "sceDmaWatch" && arg2 == 1) {
                    CHECK(v0_of(r) == (sx(madr) < sx(addr) ? 1u : 0u));  // MADR < addr (64-bit unsigned, as sltu)
                    ++checked;
                }
            }
        }
    }
    MESSAGE("kernel wrappers " << sizeof kSys / sizeof kSys[0] << ", DMAC rule checks " << checked);
}

TEST_CASE("game(libs26): the sceMpeg extension parsers on MPEG-2 extension bit fields") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const auto clear = [&] { std::memset(m->at(kDec), 0, kDecSize); };
    HwCheck hw = full_hw();
    hw.regs[L26::ipu::kCtrl] = 0xFFFFFFFFu;
    // sequence_extension: profile_and_level (8), progressive (1), chroma_format (2), size extensions (2 + 2), bit-rate
    // extension (12), marker (1); then vbv extension (8), low_delay (1), frame-rate extensions (2 + 5).
    const u32 kLevels[] = {0x48u, 0x58u, 0x44u, 0x14u, 0x4Au};
    for (u32 seed = 1; seed <= 40; ++seed) {
        std::mt19937 rng{seed * 613u};
        const u32 pl = kLevels[rng() % 5], prog = rng() % 2, chroma = seed % 4 == 0 ? 1u + rng() % 3 : 1u;
        const u32 hx = rng() % 4, vx = rng() % 4, brx = rng() % 4096, vbvx = rng() % 256;
        auto b = std::make_shared<Bits>();
        b->put(pl, 8), b->put(prog, 1), b->put(chroma, 2), b->put(hx, 2), b->put(vx, 2), b->put(brx, 12), b->put(1, 1);
        b->put(vbvx, 8), b->put(rng() % 2, 1), b->put(rng() % 4, 2), b->put(rng() % 32, 5);
        clear();
        const u32 w0 = rng() % 0x2000u, h0 = rng() % 0x2000u, br0 = rng() % 0x40000u, vbv0 = rng() % 0x400u;
        w32(*m, kDec + L26::mpeg::kWidth, w0), w32(*m, kDec + L26::mpeg::kHeight, h0);
        w32(*m, kDec + L26::mpeg::kBitRate, br0), w32(*m, kDec + L26::mpeg::kVbvSize, vbv0);
        const hgp::Run r = spair(*m, find_case("_sequenceExtension"), Args{sx(kDec), 0, 0, 0}, seed, hw, bit_world(b));
        INFO("profile/level " << pl << " chroma " << chroma);
        CHECK(r32(*m, kDec + L26::mpeg::kSeqExtSeen) == 1u);
        CHECK(r32(*m, kDec + L26::mpeg::kChromaFormat) == chroma);
        CHECK(r32(*m, kDec + L26::mpeg::kProgressiveSeq) == prog);
        CHECK(r32(*m, kDec + L26::mpeg::kWidth) == ((w0 & 0xFFFu) | (hx << 12)));
        CHECK(r32(*m, kDec + L26::mpeg::kHeight) == ((h0 & 0xFFFu) | (vx << 12)));
        CHECK(r32(*m, kDec + L26::mpeg::kBitRate) == br0 + (brx << 18));
        CHECK(r32(*m, kDec + L26::mpeg::kVbvSize) == vbv0 + (vbvx << 10));
        const bool level_ok = pl == 0x48u || pl == 0x58u || pl == 0x44u;
        CHECK(calls_to(kMpegError) == (chroma != 1 ? 1u : 0u) + (level_ok ? 0u : 1u));
        if (chroma != 1) CHECK(g_world[1]->si.log[1].text == "_chroma_format needs to be 1: 420");
        // IPU_CTRL: bit 23 cleared, the rest kept
        bool ctrl = false;
        for (const auto& a : r.bus)
            if (a.write && a.pa == L26::ipu::kCtrl) ctrl = static_cast<u32>(a.lo) == 0xFF7FFFFFu;
        CHECK(ctrl);
    }
    // sequence_display_extension: video_format (3), colour_description (1) [+ 3 x 8], display sizes (14, marker, 14).
    for (u32 seed = 1; seed <= 24; ++seed) {
        std::mt19937 rng{seed * 241u};
        const u32 desc = seed % 2, mc = rng() % 256, dw = rng() % 16384, dh = rng() % 16384;
        auto b = std::make_shared<Bits>();
        b->put(rng() % 8, 3), b->put(desc, 1);
        if (desc) b->put(rng() % 256, 8), b->put(rng() % 256, 8), b->put(mc, 8);
        b->put(dw, 14), b->put(1, 1), b->put(dh, 14);
        clear();
        spair(*m, find_case("_sequenceDisplayExtension"), Args{sx(kDec), 0, 0, 0}, seed, hw, bit_world(b));
        CHECK(r32(*m, kDec + L26::mpeg::kMatrixCoeffs) == (desc ? mc : 0u));
        CHECK(r32(*m, kDec + L26::mpeg::kDisplayW) == dw);
        CHECK(r32(*m, kDec + L26::mpeg::kDisplayH) == dh);
        CHECK(calls_to(kNextBit) == (desc ? 7u : 4u) + 1u);
    }
    // copyright_extension: ten fields, 84 bits.
    {
        auto b = std::make_shared<Bits>();
        clear();
        spair(*m, find_case("_copyrightExtension"), Args{sx(kDec), 0, 0, 0}, 1, hw, bit_world(b));
        u32 bits = 0;
        for (const auto& k : g_world[1]->si.log) bits += static_cast<u32>(k.args[1]);
        CHECK(calls_to(kNextBit) == 10u);
        CHECK(bits == 84u);
    }
    // picture_display_extension: 1..3 frame-centre offsets from the picture coding words.
    for (u32 seed = 1; seed <= 32; ++seed) {
        std::mt19937 rng{seed * 97u};
        const u32 prog = (seed >> 0) & 1u, ps = (seed >> 1) % 2 ? 3u : 1u + rng() % 2, tff = (seed >> 2) & 1u, rff = (seed >> 3) & 1u;
        const u32 n = prog ? (rff ? (tff ? 3u : 2u) : 1u) : (ps == 3u ? (rff ? 3u : 2u) : 1u);
        std::vector<u32> h, v;
        auto b = std::make_shared<Bits>();
        for (u32 i = 0; i < n; ++i) {
            h.push_back(rng() % 65536), v.push_back(rng() % 65536);
            b->put(h.back(), 16), b->put(1, 1), b->put(v.back(), 16), b->put(1, 1);
        }
        clear();
        w32(*m, kDec + L26::mpeg::kProgressiveSeq, prog), w32(*m, kDec + L26::mpeg::kPictStruct, ps);
        w32(*m, kDec + L26::mpeg::kTopFirst, tff), w32(*m, kDec + L26::mpeg::kRepeatFirst, rff);
        spair(*m, find_case("_pictureDisplayExtension"), Args{sx(kDec), 0, 0, 0}, seed, hw, bit_world(b));
        INFO("progressive " << prog << " structure " << ps << " tff " << tff << " rff " << rff);
        CHECK(calls_to(kNextBit) == 4u * n);
        for (u32 i = 0; i < n; ++i) {
            CHECK(r32(*m, kDec + L26::mpeg::kFcoH + 4 * i) == h[i]);
            CHECK(r32(*m, kDec + L26::mpeg::kFcoV + 4 * i) == v[i]);
        }
    }
    // quant_matrix_extension without matrices to load (a load goes on to _waitIpuIdle_0, another slice's): the two
    // flags kept, one error per chroma matrix flag.
    for (u32 seed = 1; seed <= 8; ++seed) {
        auto b = std::make_shared<Bits>();
        const u32 ci = seed & 1u, cn = (seed >> 1) & 1u;
        b->put(0, 1), b->put(0, 1), b->put(ci, 1), b->put(cn, 1);
        clear();
        w32(*m, kDec + L26::mpeg::kLoadIntraQ, 7), w32(*m, kDec + L26::mpeg::kLoadNonIntraQ, 7);
        spair(*m, find_case("_quantMatrixExtension"), Args{sx(kDec), 0, 0, 0}, seed, hw, bit_world(b));
        CHECK(r32(*m, kDec + L26::mpeg::kLoadIntraQ) == 0u);
        CHECK(r32(*m, kDec + L26::mpeg::kLoadNonIntraQ) == 0u);
        CHECK(calls_to(kMpegError) == ci + cn);
    }
    // ... and with random flags (the pairs may stop at _waitIpuIdle_0).
    for (u32 seed = 1; seed <= 16; ++seed) {
        std::mt19937 rng{seed * 5u};
        auto b = std::make_shared<Bits>();
        b->put(rng() % 16, 4);
        clear();
        spair(*m, find_case("_quantMatrixExtension"), Args{sx(kDec), 0, 0, 0}, seed, hw, bit_world(b));
    }
    // The two unsupported extensions report their text.
    for (const char* n : {"_sequenceScalableExtension", "_pictureSpatialScalableExtension"}) {
        auto b = std::make_shared<Bits>();
        spair(*m, find_case(n), Args{sx(kDec), 0, 0, 0}, 1, hw, bit_world(b));
        CHECK(calls_to(kMpegError) == 1u);
        CHECK(g_world[1]->si.log[0].text.find(n) == 0u);
    }
}

namespace {

// --- ISO 9660 directory sectors and #DirLst# lists -----------------------------------------------------------------
constexpr u32 kIso = 0x01830000u;    // directory sectors
constexpr u32 kList = 0x01838000u;   // a #DirLst# list (RofsDirLstHdr + up to 2,000 entries)
constexpr u32 kVol = 0x01860000u;    // the record rfdir_getDirEnt reads (+16 the volume's list, +22 its name)

void both_endian32(Machine& m, u32 va, u32 v) {
    w32(m, va, v);
    const u32 be = (v >> 24) | ((v >> 8) & 0xFF00u) | ((v << 8) & 0xFF0000u) | (v << 24);
    w32(m, va + 4, be);
}
// One directory record (ECMA-119 9.1): length, extended attribute length, extent LBA and data length (both-endian),
// date (7 bytes), flags, unit size, gap, volume sequence (both-endian 16), name length, name, pad to even.
u32 put_record(Machine& m, u32 at, const std::string& name, u32 lba, u32 size, bool dir) {
    const u32 len = (33u + static_cast<u32>(name.size()) + 1u) & ~1u;
    std::memset(m.at(at), 0, len);
    w8(m, at, static_cast<u8>(len));
    both_endian32(m, at + 2, lba);
    both_endian32(m, at + 10, size);
    for (u32 i = 0; i < 7; ++i) w8(m, at + 18 + i, static_cast<u8>(100 + i));
    w8(m, at + 25, dir ? 2 : 0);
    w16(m, at + 28, 1), w8(m, at + 31, 0), w8(m, at + 30, 1);
    w8(m, at + 32, static_cast<u8>(name.size()));
    std::memcpy(m.at(at + 33), name.data(), name.size());
    return len;
}
// A directory of `files` entries ("." and ".." included) over `nsct` sectors; records never straddle a sector.
u32 build_dir(Machine& m, u32 files, u32 nsct, std::mt19937& rng) {
    std::memset(m.at(kIso), 0, 0x800u * nsct);
    u32 at = kIso, n = 0;
    for (u32 i = 0; i < files; ++i) {
        std::string name = i == 0 ? std::string(1, '\0') : i == 1 ? std::string(1, '\1') : "F" + std::to_string(i) + ".BIN;1";
        const bool dir = i < 2 || rng() % 5 == 0;
        if (dir && i >= 2) name = "D" + std::to_string(i);
        const u32 len = (33u + static_cast<u32>(name.size()) + 1u) & ~1u;
        if (((at - kIso) & 0x7FFu) + len > 0x800u) at = (at + 0x800u) & ~0x7FFu;
        if (at + len > kIso + 0x800u * nsct) break;
        at += put_record(m, at, name, 1000u + i, i == 0 ? 0x800u * nsct : 0x800u * (1 + rng() % 9), dir);
        ++n;
    }
    return n;
}
void list_header(Machine& m, u32 va, u32 count, u32 cap, u32 lba) {
    std::memset(m.at(va), 0, 24 + 48 * cap);
    w32(m, va + 0, count), w32(m, va + 4, cap), w32(m, va + 8, lba);
}

}  // namespace

TEST_CASE("game(libs26): ROFS directory lists from ISO 9660 sectors and the ELF's #DirLst# tables") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    HwCheck hw = full_hw();
    // RFDIR_SetDirEnt(sectors, nsct, list): every record parsed while the list has room; -109 when it overflows.
    int overflow = 0, fits = 0;
    for (u32 seed = 1; seed <= 48; ++seed) {
        std::mt19937 rng{seed * 1031u};
        const u32 nsct = 1 + rng() % 2;
        const u32 n = build_dir(*m, 2 + rng() % 60, nsct, rng);
        const u32 cap = seed % 3 == 0 ? 1 + rng() % n : n + rng() % 8;
        list_header(*m, kList, 0xAAAAu, cap, 0x5555u);
        const hgp::Run r = spair(*m, find_case("RFDIR_SetDirEnt"), Args{sx(kIso), nsct, sx(kList), 0}, seed, hw, {});
        INFO("records " << n << " capacity " << cap << " sectors " << nsct);
        CHECK(r32(*m, kList + 8) == 0u);
        if (cap >= n) {
            CHECK(v0_of(r) == 0u);
            CHECK(r32(*m, kList) == n);
            ++fits;
        } else {
            CHECK(v0_of(r) == sx(static_cast<u32>(-109)));
            CHECK(r32(*m, kList) == cap);
            ++overflow;
        }
        CHECK(r32(*m, rofs_dir_entry(kList, 0) + 8) == 1000u);  // "."'s extent
    }
    // rfdir_getDirEnt(vol, buf, lba, list, size): the list already holds that directory -> 0, untouched; the volume's
    // own list holds it -> copied (as many entries as the list takes; -109 when it does not take them all).
    std::vector<u32> tables;  // the #DirLst# tables of the ELF (the marker at +12)
    for (u32 va = 0x00100000u; va + 8 < 0x00A00000u && tables.size() < 24; va += 4)
        if (std::memcmp(m->at(va), "#DirLst#", 8) == 0 && va >= 0x00100000u + 12 && r32(*m, va - 12) >= 2u &&
            r32(*m, va - 12) < 300u)  // (a 589-entry copy runs past the harness's run budget)
            tables.push_back(va - 12);
    REQUIRE(!tables.empty());
    for (u32 seed = 1; seed <= 24; ++seed) {
        std::mt19937 rng{seed * 7u};
        const u32 src = tables[seed % tables.size()];
        const u32 count = r32(*m, src), lba = r32(*m, src + 8);
        std::memset(m->at(kVol), 0, 0x100);
        w32(*m, kVol + 16, src);
        wstr(*m, kVol + 22, "DATA");
        const u32 cap = seed % 3 == 0 ? 1 + rng() % count : count + rng() % 4;
        list_header(*m, kList, 0, cap, seed % 4 == 0 ? lba : lba + 1);
        wstr(*m, kList + 12, seed % 8 == 0 ? "DATA" : "OTHER");
        HwCheck h5 = hw;
        h5.gpr_in[GPR_T0] = 0x800u;
        const hgp::Run r = spair(*m, find_case("rfdir_getDirEnt"), Args{sx(kVol), sx(kIso), lba, sx(kList)}, seed, h5, {});
        INFO("table " << std::hex << src << std::dec << " count " << count << " capacity " << cap << " seed " << seed
                      << (r.stopped ? " stopped: " + r.what + " at " + std::to_string(r.stop_pc) : std::string()));
        if (seed % 8 == 0) {  // cached: nothing written
            CHECK(v0_of(r) == 0u);
            CHECK(r32(*m, kList) == 0u);
        } else {
            CHECK(r32(*m, kList + 8) == lba);
            CHECK(rstr(*m, kList + 12) == "DATA");
            CHECK(r32(*m, kList) == std::min(count, cap));
            CHECK(v0_of(r) == (cap < count ? sx(static_cast<u32>(-109)) : 0u));
            CHECK(std::memcmp(m->at(rofs_dir_entry(kList, 0)), m->at(rofs_dir_entry(src, 0)), 48 * std::min(count, cap)) == 0);
        }
    }
    // The device-table entries: the "ROFS" device itself cannot be deleted.
    wstr(*m, kVol, "ROFS");
    CHECK(v0_of(spair(*m, find_case("sub_56CB58"), Args{sx(kVol), 0, 0, 0}, 1, hw, {})) == sx(0xFFFFFFFFu));
    for (u32 seed = 1; seed <= 8; ++seed) {
        wstr(*m, kVol, seed % 2 ? "\\DATA" : "\\NODIR");
        const hgp::Run r = spair(*m, find_case("sub_56CA38"), Args{sx(kVol), 0, 0, 0}, seed, hw, {});
        if (!r.stopped) CHECK((v0_of(r) == 0u || v0_of(r) == sx(0xFFFFFFFFu)));  // ROFS_ChangeDir's result mapped
    }
    MESSAGE("SetDirEnt: " << fits << " fitted, " << overflow << " overflowed; " << tables.size() << " #DirLst# tables");
}

namespace {

// The kernel semaphore calls, sceFsInit, scePrintf, Exit, _sce_SetTLBEntry and kputchar stood in (other tests stand them in
// already; no current packet claims them): the file-I/O wrappers then run up to their RPC, the TLB set-up to its end.
constexpr u32 kCreateSema = 0x503160u, kDeleteSema = 0x503170u, kSignalSema = 0x503180u, kiSignalSema = 0x503190u,
              kWaitSema = 0x5031A0u, kFsInit = 0x508170u, kScePrintf = 0x505E48u, kExit = 0x50DA58u,
              kSetTlbEntry = 0x50CD60u;
void install_kernel(StandInWorld& w) {
    install_standard(w);
    // These are kernel call stubs (`syscall` and return): the kernel keeps the temporaries, and InitTLB32MB counts in
    // $t9 across _sce_SetTLBEntry, so no post-call scratch pattern.
    w.si.clobber_scratch = false;
    w.si.install_recorder(kCreateSema, "_sceCreateSema", 7, 4);
    w.si.install_recorder(kDeleteSema, "_sceDeleteSema", 7, 4);
    w.si.install_recorder(kSignalSema, "_sceSignalSema", 7, 4);
    w.si.install_recorder(kiSignalSema, "_sceiSignalSema", 7, 4);
    w.si.install_recorder(kWaitSema, "_sceWaitSema", 7, 4);
    w.si.install_recorder(kFsInit, "sceFsInit", 0, 4);
    w.si.install_recorder(kScePrintf, "scePrintf", 0, 4);
    w.si.install_recorder(kExit, "Exit", 0, 4);
    w.si.install_recorder(kSetTlbEntry, "_sce_SetTLBEntry", 0, 4);
    w.si.install_recorder(0x504BC0u, "kputchar", 0, 4);  // kprintf's output (test_sce1 stands it in too)
}
constexpr u32 kTlbDesc = 0x77FB98u;  // InitTLB32MB's descriptor: kernel / default / extended counts, +12 written, tables +16..

}  // namespace

TEST_CASE("game(libs26): file-I/O wrappers, the TLB set-up and the semaphore paths with the kernel calls stood in") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    // InitTLB32MB: the three tables written entry by entry (index 0, 1, ...), then invalid entries up to 47; the
    // first free index << 13 returned, kernel + default kept at +12; Exit(1) for each table that would pass 48.
    int exits = 0;
    for (u32 seed = 1; seed <= 24; ++seed) {
        std::mt19937 rng{seed * 389u};
        const u32 k = rng() % 20, d = rng() % 20, e = seed % 3 ? rng() % 10 : 0u;  // at most 47 in all
        w32(*m, kTlbDesc, k), w32(*m, kTlbDesc + 4, d), w32(*m, kTlbDesc + 8, e);
        for (u32 t = 0; t < 3; ++t) {
            const u32 tab = kWorld + 0x1000u * t;
            w32(*m, kTlbDesc + 16 + 4 * t, tab);
            for (u32 i = 0; i < 64; ++i)
                for (u32 j = 0; j < 4; ++j) w32(*m, tab + 16 * i + 4 * j, rng());
        }
        const hgp::Run r = spair(*m, find_case("InitTLB32MB"), Args{0, 0, 0, 0}, seed, full_hw(), install_kernel);
        INFO("kernel " << k << " default " << d << " extended " << e
                       << (r.stopped ? " stopped: " + r.what + " at " + std::to_string(r.stop_pc) : std::string()));
        const u32 used = k + d + e;
        CHECK(calls_to(kExit) == 0u);
        CHECK(calls_to(kSetTlbEntry) == 48u);  // the tables, then invalid entries up to index 47
        CHECK(v0_of(r) == sx(used << 13));
        CHECK(r32(*m, kTlbDesc + 12) == k + d);
        u32 i = 0;
        for (const auto& c : g_world[1]->si.log)
            if (c.va == kSetTlbEntry) CHECK(static_cast<u32>(c.args[0]) == i++);
        exits += static_cast<int>(calls_to(kExit));
    }
    // _DelayThreadHandler signals the semaphore it was given ($a3) and returns 0.
    for (u32 seed = 1; seed <= 8; ++seed) {
        const hgp::Run r = spair(*m, find_case("_DelayThreadHandler"), Args{0, 0, 0, 40 + seed}, seed, full_hw(), install_kernel);
        CHECK(v0_of(r) == 0u);
        REQUIRE(calls_to(kiSignalSema) == 1u);
        CHECK(g_world[1]->si.log.back().args[0] == 40 + seed);
    }
    // The file-I/O wrappers and the other semaphore users over the snapshots' library globals, with paths for the
    // path arguments; the runs go on to their RPC (sceFsSifCallRpc / sceSifCallRpc, other slices') and stop there.
    const char* kFs[] = {"sceFsSetIopBuf", "sceFsSetIopPrio", "sceIoctl2", "sceMkdir", "sceFormat", "sceAddDrv",
                         "sceDclose", "sceDread", "sceGetstat", "sceChstat", "sceRename", "sceMount", "sceDevctl",
                         "sceSymlink", "sceReadlink", "sceSifGetOtherData", "cdvd_exit", "sceCdDiskReady_old",
                         "sceCdSeek", "sceCdBreak", "sceDbcSearchPortSpecific", "iSuspendThread", "sceSifLoadIopHeap",
                         "sceSifQueryMemSize", "sceSifQueryMaxFreeMemSize"};
    const char* kPaths[] = {"host0:", "mc0:/BASLUS-21621P3F/data.bin", "pfs0:/a/very/long/path/that/goes/on", "cdrom0:"};
    const std::vector<u8> snap = read_snapshot("b_5800");
    int pairs = 0;
    for (const char* name : kFs) {
        for (u32 seed = 1; seed <= 12; ++seed) {
            if (snap.size() == EEMemory::kMainRamSize) std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
            std::mt19937 rng{seed * 61u};
            for (u32 i = 0; i < 4; ++i) wstr(*m, kWorld + 0x400u * i, kPaths[i]);
            std::string long_path(1100, 'x');  // longer than the 1,024-byte request buffer
            wstr(*m, kWorld + 0x2000u, long_path.c_str());
            const auto arg = [&]() -> u64 {
                const u32 k = rng() % 6;
                if (k < 3) return sx(kWorld + 0x400u * (rng() % 4));
                if (k < 4) return sx(kWorld + 0x2000u);
                if (k < 5) return 0x4000u * (rng() % 80);  // sceFsSetIopBuf: 16 KiB steps up to and past 1 MiB
                return rng() % 40;
            };
            HwCheck hw = full_hw();
            hw.gpr_in[GPR_T0] = arg();
            hw.gpr_in[GPR_T1] = arg();
            spair(*m, find_case(name), Args{arg(), arg(), arg(), arg()}, seed, hw, install_kernel);
            ++pairs;
        }
    }
    MESSAGE("InitTLB32MB: " << exits << " exits; semaphore / file-I/O pairs " << pairs);
}

// Every body over the RAM of the replay snapshots: the real SIF RPC / file-I/O / CD / pad / sound / DBC / ADXF / ROFS
// globals, with arguments drawn from a world of strings and records and from the snapshot's own pointers.
TEST_CASE("game(libs26): every body equals its recompiled body on the replay snapshots") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* only = std::getenv("P3FES_HG_ONLY");
    const char* kSnaps[] = {"dorm_replay_4900", "b_5800", "climb_ref_17000"};
    const char* kPaths[] = {"cdrom0:\\DATA.CVM;1", "host0:save/dir", "mc0:/BASLUS-21621P3F", "pfs0:", "ROFS", "\\BTL"};
    for (const char* dir : kSnaps) {
        const std::vector<u8> snap = read_snapshot(dir);
        if (snap.size() != EEMemory::kMainRamSize) {
            MESSAGE("SKIP: snapshot " << dir << " not found");
            continue;
        }
        int pairs = 0;
        for (const Case& c : kCases) {
            if (only && std::string(only) != c.name) continue;
            for (u32 seed = 1; seed <= 4; ++seed) {
                std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
                std::mt19937 rng{seed * 104729u + c.addr};
                hgp::random_world(*m, kWorld, kWorldSize, rng);
                for (u32 i = 0; i < 6; ++i) wstr(*m, kWorld + 0x100u * i, kPaths[i]);
                const auto arg = [&]() -> u64 {
                    const u32 k = rng() % 8;
                    if (k < 2) return sx(kWorld + 0x100u * (rng() % 6));  // a path
                    if (k < 4) return hgp::random_arg(rng, kWorld, kWorldSize);
                    if (k < 6) return rng() % 64;
                    u32 p = 0;  // a pointer the snapshot holds
                    std::memcpy(&p, snap.data() + ((0x780000u + (rng() % 0x40000u)) & ~3u), 4);
                    return sx(p);
                };
                HwCheck hw = full_hw();
                hw.gpr_in[GPR_T0] = arg();
                hw.gpr_in[GPR_T1] = arg();
                const Args args{arg(), arg(), arg(), arg()};
                spair(*m, c, args, seed, hw, install_standard);
                ++pairs;
            }
        }
        const std::string note = std::string(dir) + ": " + std::to_string(pairs) + " pairs";
        MESSAGE(note);
    }
}

#else

TEST_CASE("game(libs26): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
