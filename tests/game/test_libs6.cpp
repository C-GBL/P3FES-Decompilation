// Pair tests for slice libs6 (game/src/lib/libs6.cpp): every body against its recompiled body through
// tests/game/libs1_util.h's runner (tests/game/handgen_pairs.h: the whole register file and cycles at every check point
// and at the return / stop, all 32 MiB of RAM, the scratchpad, the BIOS window, the bus log; both call logs equal).
//
// The callees the bodies reach that this test build does not emit are stood in here (stand_ins below): the kernel-call
// wrappers (semaphores, threads, DECI2, the TLB / exception vectors), the file layer's _sceCallCode, libpad's DMA
// status, the timer as test_libs1_kernel serves it. The worlds: a random sweep, then the real structures -- an RPC
// client's packet pool and a queue with two servers appended to the dorm snapshot's live queue list, the dorm iob
// table, the timer counter pool with the user-alarm list, the TTY's DECI2 record, the reboot-notify and SIF handler
// tables, and a format of the battle route's memory card on the b_5800 library state -- with host checks of the
// documented rules (ids, list links, error codes).
#include "libs1_util.h"

#include "p3fes/game/libs6.h"
#include "p3fes/game/sce.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iterator>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
using namespace p3fes::game_test::libs1;
namespace libs6 = p3fes::game::libs6;

namespace p3fes::recomp_gen {
void fn__sceMpegDefaultStopDMA_00501128(EEContext&);  // generated body
void fn__sceMpegDefaultStopDMA_00501128__recomp(EEContext&);  // recompiled
void fn__sceMpegDefaultRestartDMA_00501150(EEContext&);  // generated body
void fn__sceMpegDefaultRestartDMA_00501150__recomp(EEContext&);  // recompiled
void fn_write_00503728(EEContext&);  // generated body
void fn_write_00503728__recomp(EEContext&);  // recompiled
void fn_read_005037a8(EEContext&);  // generated body
void fn_read_005037a8__recomp(EEContext&);  // recompiled
void fn_iSyncDCache_00503ad8(EEContext&);  // generated body
void fn_iSyncDCache_00503ad8__recomp(EEContext&);  // recompiled
void fn_iInvalidDCache_00503c18(EEContext&);  // generated body
void fn_iInvalidDCache_00503c18__recomp(EEContext&);  // recompiled
void fn_iEnableIntc_00503de0(EEContext&);  // generated body
void fn_iEnableIntc_00503de0__recomp(EEContext&);  // recompiled
void fn_iDisableIntc_00503e00(EEContext&);  // generated body
void fn_iDisableIntc_00503e00__recomp(EEContext&);  // recompiled
void fn_iEnableDmac_00503e20(EEContext&);  // generated body
void fn_iEnableDmac_00503e20__recomp(EEContext&);  // recompiled
void fn_iDisableDmac_00503e40(EEContext&);  // generated body
void fn_iDisableDmac_00503e40__recomp(EEContext&);  // recompiled
void fn_topThread_00503e60(EEContext&);  // generated body
void fn_topThread_00503e60__recomp(EEContext&);  // recompiled
void fn_InitThread_00503f38(EEContext&);  // generated body
void fn_InitThread_00503f38__recomp(EEContext&);  // recompiled
void fn_iRotateThreadReadyQueue_005040c0(EEContext&);  // generated body
void fn_iRotateThreadReadyQueue_005040c0__recomp(EEContext&);  // recompiled
void fn_sceDeci2Open_00504440(EEContext&);  // generated body
void fn_sceDeci2Open_00504440__recomp(EEContext&);  // recompiled
void fn_sceDeci2Close_00504488(EEContext&);  // generated body
void fn_sceDeci2Close_00504488__recomp(EEContext&);  // recompiled
void fn_sceDeci2ReqSend_005044b0(EEContext&);  // generated body
void fn_sceDeci2ReqSend_005044b0__recomp(EEContext&);  // recompiled
void fn_sceDeci2Poll_005044e0(EEContext&);  // generated body
void fn_sceDeci2Poll_005044e0__recomp(EEContext&);  // recompiled
void fn_sceDeci2GrpOpen_00504508(EEContext&);  // generated body
void fn_sceDeci2GrpOpen_00504508__recomp(EEContext&);  // recompiled
void fn_sceDeci2GrpClose_00504538(EEContext&);  // generated body
void fn_sceDeci2GrpClose_00504538__recomp(EEContext&);  // recompiled
void fn_sceDeci2ExRecv_00504560(EEContext&);  // generated body
void fn_sceDeci2ExRecv_00504560__recomp(EEContext&);  // recompiled
void fn_sceDeci2ExSend_00504598(EEContext&);  // generated body
void fn_sceDeci2ExSend_00504598__recomp(EEContext&);  // recompiled
void fn_sceDeci2ExReqSend_005045d0(EEContext&);  // generated body
void fn_sceDeci2ExReqSend_005045d0__recomp(EEContext&);  // recompiled
void fn_sceDeci2ExLock_00504600(EEContext&);  // generated body
void fn_sceDeci2ExLock_00504600__recomp(EEContext&);  // recompiled
void fn_sceDeci2ExUnLock_00504628(EEContext&);  // generated body
void fn_sceDeci2ExUnLock_00504628__recomp(EEContext&);  // recompiled
void fn_sceTtyHandler_00504720(EEContext&);  // generated body
void fn_sceTtyHandler_00504720__recomp(EEContext&);  // recompiled
void fn_sceTtyWrite_005048b8(EEContext&);  // generated body
void fn_sceTtyWrite_005048b8__recomp(EEContext&);  // recompiled
void fn_sceTtyInit_00504b00(EEContext&);  // generated body
void fn_sceTtyInit_00504b00__recomp(EEContext&);  // recompiled
void fn_sceVprintf_00505dd8(EEContext&);  // generated body
void fn_sceVprintf_00505dd8__recomp(EEContext&);  // recompiled
void fn_kprintf_00505ec8(EEContext&);  // generated body
void fn_kprintf_00505ec8__recomp(EEContext&);  // recompiled
void fn_sub_5063C8_005063c8(EEContext&);  // generated body
void fn_sub_5063C8_005063c8__recomp(EEContext&);  // recompiled
void fn_sceSifSendCmd_005064a8(EEContext&);  // generated body
void fn_sceSifSendCmd_005064a8__recomp(EEContext&);  // recompiled
void fn_sub_506630_00506630(EEContext&);  // generated body
void fn_sub_506630_00506630__recomp(EEContext&);  // recompiled
void fn_sceSifWriteBackDCache_00506670(EEContext&);  // generated body
void fn_sceSifWriteBackDCache_00506670__recomp(EEContext&);  // recompiled
void fn_sub_5067F8_005067f8(EEContext&);  // generated body
void fn_sub_5067F8_005067f8__recomp(EEContext&);  // recompiled
void fn_sceSifExitRpc_00506a48(EEContext&);  // generated body
void fn_sceSifExitRpc_00506a48__recomp(EEContext&);  // recompiled
void fn__sceRpcGetPacket_00506a70(EEContext&);  // generated body
void fn__sceRpcGetPacket_00506a70__recomp(EEContext&);  // recompiled
void fn__sceRpcFreePacket_00506b18(EEContext&);  // generated body
void fn__sceRpcFreePacket_00506b18__recomp(EEContext&);  // recompiled
void fn__sceRpcGetFPacket_00506b38(EEContext&);  // generated body
void fn__sceRpcGetFPacket_00506b38__recomp(EEContext&);  // recompiled
void fn__search_svdata_00506ef0(EEContext&);  // generated body
void fn__search_svdata_00506ef0__recomp(EEContext&);  // recompiled
void fn__request_call_005071a0(EEContext&);  // generated body
void fn__request_call_005071a0__recomp(EEContext&);  // recompiled
void fn_sceSifCheckStatRpc_00507430(EEContext&);  // generated body
void fn_sceSifCheckStatRpc_00507430__recomp(EEContext&);  // recompiled
void fn_sceSifSetRpcQueue_00507470(EEContext&);  // generated body
void fn_sceSifSetRpcQueue_00507470__recomp(EEContext&);  // recompiled
void fn_sceSifRegisterRpc_00507508(EEContext&);  // generated body
void fn_sceSifRegisterRpc_00507508__recomp(EEContext&);  // recompiled
void fn_sceSifRemoveRpc_005075d8(EEContext&);  // generated body
void fn_sceSifRemoveRpc_005075d8__recomp(EEContext&);  // recompiled
void fn_sceSifRemoveRpcQueue_00507670(EEContext&);  // generated body
void fn_sceSifRemoveRpcQueue_00507670__recomp(EEContext&);  // recompiled
void fn_sceSifGetNextRequest_00507700(EEContext&);  // generated body
void fn_sceSifGetNextRequest_00507700__recomp(EEContext&);  // recompiled
void fn__sceFsIobSemaMK_00507960(EEContext&);  // generated body
void fn__sceFsIobSemaMK_00507960__recomp(EEContext&);  // recompiled
void fn_use_iob_cnt_005079d0(EEContext&);  // generated body
void fn_use_iob_cnt_005079d0__recomp(EEContext&);  // recompiled
void fn_new_iob_00507a50(EEContext&);  // generated body
void fn_new_iob_00507a50__recomp(EEContext&);  // recompiled
void fn_get_iob_00507bc8(EEContext&);  // generated body
void fn_get_iob_00507bc8__recomp(EEContext&);  // recompiled
void fn__sceFs_Rcv_Intr_00507c38(EEContext&);  // generated body
void fn__sceFs_Rcv_Intr_00507c38__recomp(EEContext&);  // recompiled
void fn__sceFsSemInit_00507ff0(EEContext&);  // generated body
void fn__sceFsSemInit_00507ff0__recomp(EEContext&);  // recompiled
void fn__sceFsWaitS_00508048(EEContext&);  // generated body
void fn__sceFsWaitS_00508048__recomp(EEContext&);  // recompiled
void fn__sceFsSigSema_00508078(EEContext&);  // generated body
void fn__sceFsSigSema_00508078__recomp(EEContext&);  // recompiled
void fn_scePowerOffHandler_00508088(EEContext&);  // generated body
void fn_scePowerOffHandler_00508088__recomp(EEContext&);  // recompiled
void fn_sceFsReset_00508408(EEContext&);  // generated body
void fn_sceFsReset_00508408__recomp(EEContext&);  // recompiled
void fn_sceRemove_00509908(EEContext&);  // generated body
void fn_sceRemove_00509908__recomp(EEContext&);  // recompiled
void fn_sceRmdir_00509ae0(EEContext&);  // generated body
void fn_sceRmdir_00509ae0__recomp(EEContext&);  // recompiled
void fn_sceDelDrv_00509eb0(EEContext&);  // generated body
void fn_sceDelDrv_00509eb0__recomp(EEContext&);  // recompiled
void fn_sceDopen_00509ed0(EEContext&);  // generated body
void fn_sceDopen_00509ed0__recomp(EEContext&);  // recompiled
void fn_sceChdir_0050a868(EEContext&);  // generated body
void fn_sceChdir_0050a868__recomp(EEContext&);  // recompiled
void fn_sceUmount_0050acb8(EEContext&);  // generated body
void fn_sceUmount_0050acb8__recomp(EEContext&);  // recompiled
void fn_sceSifLoadFileReset_0050bc78(EEContext&);  // generated body
void fn_sceSifLoadFileReset_0050bc78__recomp(EEContext&);  // recompiled
void fn_SetTLBHandler_0050cb28(EEContext&);  // generated body
void fn_SetTLBHandler_0050cb28__recomp(EEContext&);  // recompiled
void fn_SetDebugHandler_0050cb88(EEContext&);  // generated body
void fn_SetDebugHandler_0050cb88__recomp(EEContext&);  // recompiled
void fn_kCopy_0050cc20(EEContext&);  // generated body
void fn_kCopy_0050cc20__recomp(EEContext&);  // recompiled
void fn_InitTLBFunctions_0050cc78(EEContext&);  // generated body
void fn_InitTLBFunctions_0050cc78__recomp(EEContext&);  // recompiled
void fn_SetTLBEntry_0050cd70(EEContext&);  // generated body
void fn_SetTLBEntry_0050cd70__recomp(EEContext&);  // recompiled
void fn_InitTLB_0050ce00(EEContext&);  // generated body
void fn_InitTLB_0050ce00__recomp(EEContext&);  // recompiled
void fn_sub_50D37C_0050d37c(EEContext&);  // generated body
void fn_sub_50D37C_0050d37c__recomp(EEContext&);  // recompiled
void fn_supplement_crt0_0050d408(EEContext&);  // generated body
void fn_supplement_crt0_0050d408__recomp(EEContext&);  // recompiled
void fn_kCopy_0_0050d488(EEContext&);  // generated body
void fn_kCopy_0_0050d488__recomp(EEContext&);  // recompiled
void fn_kFindAddress_0050d4c0(EEContext&);  // generated body
void fn_kFindAddress_0050d4c0__recomp(EEContext&);  // recompiled
void fn_GetSystemCallEntry_0050d510(EEContext&);  // generated body
void fn_GetSystemCallEntry_0050d510__recomp(EEContext&);  // recompiled
void fn_InitSystemCallTableAddress_0050d548(EEContext&);  // generated body
void fn_InitSystemCallTableAddress_0050d548__recomp(EEContext&);  // recompiled
void fn_crt_init_runtime_0050d658(EEContext&);  // generated body
void fn_crt_init_runtime_0050d658__recomp(EEContext&);  // recompiled
void fn_kCopy_1_0050d6d0(EEContext&);  // generated body
void fn_kCopy_1_0050d6d0__recomp(EEContext&);  // recompiled
void fn_PatchIsNeeded_0050d718(EEContext&);  // generated body
void fn_PatchIsNeeded_0050d718__recomp(EEContext&);  // recompiled
void fn_InitExecPS2_0050d780(EEContext&);  // generated body
void fn_InitExecPS2_0050d780__recomp(EEContext&);  // recompiled
void fn_SetArg_0050d880(EEContext&);  // generated body
void fn_SetArg_0050d880__recomp(EEContext&);  // recompiled
void fn_sub_50D998_0050d998(EEContext&);  // generated body
void fn_sub_50D998_0050d998__recomp(EEContext&);  // recompiled
void fn_ExecPS2_0050d9a0(EEContext&);  // generated body
void fn_ExecPS2_0050d9a0__recomp(EEContext&);  // recompiled
void fn_kCopy_3_0050daf0(EEContext&);  // generated body
void fn_kCopy_3_0050daf0__recomp(EEContext&);  // recompiled
void fn_sub_50DE08_0050de08(EEContext&);  // generated body
void fn_sub_50DE08_0050de08__recomp(EEContext&);  // recompiled
void fn_sub_50E648_0050e648(EEContext&);  // generated body
void fn_sub_50E648_0050e648__recomp(EEContext&);  // recompiled
void fn_sub_50E750_0050e750(EEContext&);  // generated body
void fn_sub_50E750_0050e750__recomp(EEContext&);  // recompiled
void fn_sub_50E7F0_0050e7f0(EEContext&);  // generated body
void fn_sub_50E7F0_0050e7f0__recomp(EEContext&);  // recompiled
void fn_sub_50E900_0050e900(EEContext&);  // generated body
void fn_sub_50E900_0050e900__recomp(EEContext&);  // recompiled
void fn_sub_50EA30_0050ea30(EEContext&);  // generated body
void fn_sub_50EA30_0050ea30__recomp(EEContext&);  // recompiled
void fn_sub_50EA80_0050ea80(EEContext&);  // generated body
void fn_sub_50EA80_0050ea80__recomp(EEContext&);  // recompiled
void fn_sub_50EB98_0050eb98(EEContext&);  // generated body
void fn_sub_50EB98_0050eb98__recomp(EEContext&);  // recompiled
void fn_sub_50EC58_0050ec58(EEContext&);  // generated body
void fn_sub_50EC58_0050ec58__recomp(EEContext&);  // recompiled
void fn_sub_50EDB8_0050edb8(EEContext&);  // generated body
void fn_sub_50EDB8_0050edb8__recomp(EEContext&);  // recompiled
void fn_SetTimerAlarm_0050f090(EEContext&);  // generated body
void fn_SetTimerAlarm_0050f090__recomp(EEContext&);  // recompiled
void fn_ReleaseTimerAlarm_0050f2b0(EEContext&);  // generated body
void fn_ReleaseTimerAlarm_0050f2b0__recomp(EEContext&);  // recompiled
void fn_sceSifSetRebootNotifyBuffer_0050f3f8(EEContext&);  // generated body
void fn_sceSifSetRebootNotifyBuffer_0050f3f8__recomp(EEContext&);  // recompiled
void fn_sceSifAddRebootNotifyHandler_0050f478(EEContext&);  // generated body
void fn_sceSifAddRebootNotifyHandler_0050f478__recomp(EEContext&);  // recompiled
void fn_sceSifRemoveRebootNotifyHandler_0050f530(EEContext&);  // generated body
void fn_sceSifRemoveRebootNotifyHandler_0050f530__recomp(EEContext&);  // recompiled
void fn_sceSifExecNotifyHandler_0050f588(EEContext&);  // generated body
void fn_sceSifExecNotifyHandler_0050f588__recomp(EEContext&);  // recompiled
void fn__sceCd_cd_callback_0050f698(EEContext&);  // generated body
void fn__sceCd_cd_callback_0050f698__recomp(EEContext&);  // recompiled
void fn__sceCd_cbLoop_0050f738(EEContext&);  // generated body
void fn__sceCd_cbLoop_0050f738__recomp(EEContext&);  // recompiled
void fn_sceCdInitEeCB_0050f808(EEContext&);  // generated body
void fn_sceCdInitEeCB_0050f808__recomp(EEContext&);  // recompiled
void fn_cmd_sem_init_0050f960(EEContext&);  // generated body
void fn_cmd_sem_init_0050f960__recomp(EEContext&);  // recompiled
void fn_sceCdPOffCallback_0050fae8(EEContext&);  // generated body
void fn_sceCdPOffCallback_0050fae8__recomp(EEContext&);  // recompiled
void fn__sceCd_Poff_Intr_0050fb68(EEContext&);  // generated body
void fn__sceCd_Poff_Intr_0050fb68__recomp(EEContext&);  // recompiled
void fn_PowerOffCB_0050fbc0(EEContext&);  // generated body
void fn_PowerOffCB_0050fbc0__recomp(EEContext&);  // recompiled
void fn__sceCdSC_005103b0(EEContext&);  // generated body
void fn__sceCdSC_005103b0__recomp(EEContext&);  // recompiled
void fn_sceCdChgSys_00511110(EEContext&);  // generated body
void fn_sceCdChgSys_00511110__recomp(EEContext&);  // recompiled
void fn_scePadSetReqState_00511b08(EEContext&);  // generated body
void fn_scePadSetReqState_00511b08__recomp(EEContext&);  // recompiled
void fn_scePadSetActDirect_00512070(EEContext&);  // generated body
void fn_scePadSetActDirect_00512070__recomp(EEContext&);  // recompiled
void fn_sceSdCallBack_005129a0(EEContext&);  // generated body
void fn_sceSdCallBack_005129a0__recomp(EEContext&);  // recompiled
void fn__sdrCB_00512ff0(EEContext&);  // generated body
void fn__sdrCB_00512ff0__recomp(EEContext&);  // recompiled
void fn_sceMc2End_00513290(EEContext&);  // generated body
void fn_sceMc2End_00513290__recomp(EEContext&);  // recompiled
void fn_sceMc2SearchSocket_00513478(EEContext&);  // generated body
void fn_sceMc2SearchSocket_00513478__recomp(EEContext&);  // recompiled
void fn_sceMc2ChangeThreadPriority_00513528(EEContext&);  // generated body
void fn_sceMc2ChangeThreadPriority_00513528__recomp(EEContext&);  // recompiled
void fn_sceMc2iChangeThreadPriority_00513560(EEContext&);  // generated body
void fn_sceMc2iChangeThreadPriority_00513560__recomp(EEContext&);  // recompiled
void fn_sceMc2GetDirAllAsync_005138b8(EEContext&);  // generated body
void fn_sceMc2GetDirAllAsync_005138b8__recomp(EEContext&);  // recompiled
void fn_basic_thread_005145f8(EEContext&);  // generated body
void fn_basic_thread_005145f8__recomp(EEContext&);  // recompiled
void fn__sceMcFatFormat_00516118(EEContext&);  // generated body
void fn__sceMcFatFormat_00516118__recomp(EEContext&);  // recompiled
void fn_SyncDma_0051ad10(EEContext&);  // generated body
void fn_SyncDma_0051ad10__recomp(EEContext&);  // recompiled
void fn_SyncDmaForRead_0051ade0(EEContext&);  // generated body
void fn_SyncDmaForRead_0051ade0__recomp(EEContext&);  // recompiled
void fn__sceMcCoreInit_0051ae68(EEContext&);  // generated body
void fn__sceMcCoreInit_0051ae68__recomp(EEContext&);  // recompiled
void fn__sceMcCoreEnd_0051aef8(EEContext&);  // generated body
void fn__sceMcCoreEnd_0051aef8__recomp(EEContext&);  // recompiled
void fn__sceMcCoreWriteSameData_0051ba88(EEContext&);  // generated body
void fn__sceMcCoreWriteSameData_0051ba88__recomp(EEContext&);  // recompiled
void fn_sceDbcEnd_0051c658(EEContext&);  // generated body
void fn_sceDbcEnd_0051c658__recomp(EEContext&);  // recompiled
void fn_sceDbcGetConnection_0051cad0(EEContext&);  // generated body
void fn_sceDbcGetConnection_0051cad0__recomp(EEContext&);  // recompiled
void fn_sceSkQuit_0051dad8(EEContext&);  // generated body
void fn_sceSkQuit_0051dad8__recomp(EEContext&);  // recompiled
void fn___malloc_lock_005214c8(EEContext&);  // generated body
void fn___malloc_lock_005214c8__recomp(EEContext&);  // recompiled
void fn___malloc_unlock_00521520(EEContext&);  // generated body
void fn___malloc_unlock_00521520__recomp(EEContext&);  // recompiled
void fn__read_r_00522f38(EEContext&);  // generated body
void fn__read_r_00522f38__recomp(EEContext&);  // recompiled
void fn__sbrk_r_00523930(EEContext&);  // generated body
void fn__sbrk_r_00523930__recomp(EEContext&);  // recompiled
void fn__write_r_00528970(EEContext&);  // generated body
void fn__write_r_00528970__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

const Case kCases[] = {
    {"_sceMpegDefaultStopDMA", 0x501128, &recomp_gen::fn__sceMpegDefaultStopDMA_00501128, &recomp_gen::fn__sceMpegDefaultStopDMA_00501128__recomp},
    {"_sceMpegDefaultRestartDMA", 0x501150, &recomp_gen::fn__sceMpegDefaultRestartDMA_00501150, &recomp_gen::fn__sceMpegDefaultRestartDMA_00501150__recomp},
    {"write", 0x503728, &recomp_gen::fn_write_00503728, &recomp_gen::fn_write_00503728__recomp},
    {"read", 0x5037A8, &recomp_gen::fn_read_005037a8, &recomp_gen::fn_read_005037a8__recomp},
    {"iSyncDCache", 0x503AD8, &recomp_gen::fn_iSyncDCache_00503ad8, &recomp_gen::fn_iSyncDCache_00503ad8__recomp},
    {"iInvalidDCache", 0x503C18, &recomp_gen::fn_iInvalidDCache_00503c18, &recomp_gen::fn_iInvalidDCache_00503c18__recomp},
    {"iEnableIntc", 0x503DE0, &recomp_gen::fn_iEnableIntc_00503de0, &recomp_gen::fn_iEnableIntc_00503de0__recomp},
    {"iDisableIntc", 0x503E00, &recomp_gen::fn_iDisableIntc_00503e00, &recomp_gen::fn_iDisableIntc_00503e00__recomp},
    {"iEnableDmac", 0x503E20, &recomp_gen::fn_iEnableDmac_00503e20, &recomp_gen::fn_iEnableDmac_00503e20__recomp},
    {"iDisableDmac", 0x503E40, &recomp_gen::fn_iDisableDmac_00503e40, &recomp_gen::fn_iDisableDmac_00503e40__recomp},
    {"topThread", 0x503E60, &recomp_gen::fn_topThread_00503e60, &recomp_gen::fn_topThread_00503e60__recomp},
    {"InitThread", 0x503F38, &recomp_gen::fn_InitThread_00503f38, &recomp_gen::fn_InitThread_00503f38__recomp},
    {"iRotateThreadReadyQueue", 0x5040C0, &recomp_gen::fn_iRotateThreadReadyQueue_005040c0, &recomp_gen::fn_iRotateThreadReadyQueue_005040c0__recomp},
    {"sceDeci2Open", 0x504440, &recomp_gen::fn_sceDeci2Open_00504440, &recomp_gen::fn_sceDeci2Open_00504440__recomp},
    {"sceDeci2Close", 0x504488, &recomp_gen::fn_sceDeci2Close_00504488, &recomp_gen::fn_sceDeci2Close_00504488__recomp},
    {"sceDeci2ReqSend", 0x5044B0, &recomp_gen::fn_sceDeci2ReqSend_005044b0, &recomp_gen::fn_sceDeci2ReqSend_005044b0__recomp},
    {"sceDeci2Poll", 0x5044E0, &recomp_gen::fn_sceDeci2Poll_005044e0, &recomp_gen::fn_sceDeci2Poll_005044e0__recomp},
    {"sceDeci2GrpOpen", 0x504508, &recomp_gen::fn_sceDeci2GrpOpen_00504508, &recomp_gen::fn_sceDeci2GrpOpen_00504508__recomp},
    {"sceDeci2GrpClose", 0x504538, &recomp_gen::fn_sceDeci2GrpClose_00504538, &recomp_gen::fn_sceDeci2GrpClose_00504538__recomp},
    {"sceDeci2ExRecv", 0x504560, &recomp_gen::fn_sceDeci2ExRecv_00504560, &recomp_gen::fn_sceDeci2ExRecv_00504560__recomp},
    {"sceDeci2ExSend", 0x504598, &recomp_gen::fn_sceDeci2ExSend_00504598, &recomp_gen::fn_sceDeci2ExSend_00504598__recomp},
    {"sceDeci2ExReqSend", 0x5045D0, &recomp_gen::fn_sceDeci2ExReqSend_005045d0, &recomp_gen::fn_sceDeci2ExReqSend_005045d0__recomp},
    {"sceDeci2ExLock", 0x504600, &recomp_gen::fn_sceDeci2ExLock_00504600, &recomp_gen::fn_sceDeci2ExLock_00504600__recomp},
    {"sceDeci2ExUnLock", 0x504628, &recomp_gen::fn_sceDeci2ExUnLock_00504628, &recomp_gen::fn_sceDeci2ExUnLock_00504628__recomp},
    {"sceTtyHandler", 0x504720, &recomp_gen::fn_sceTtyHandler_00504720, &recomp_gen::fn_sceTtyHandler_00504720__recomp},
    {"sceTtyWrite", 0x5048B8, &recomp_gen::fn_sceTtyWrite_005048b8, &recomp_gen::fn_sceTtyWrite_005048b8__recomp},
    {"sceTtyInit", 0x504B00, &recomp_gen::fn_sceTtyInit_00504b00, &recomp_gen::fn_sceTtyInit_00504b00__recomp},
    {"sceVprintf", 0x505DD8, &recomp_gen::fn_sceVprintf_00505dd8, &recomp_gen::fn_sceVprintf_00505dd8__recomp},
    {"kprintf", 0x505EC8, &recomp_gen::fn_kprintf_00505ec8, &recomp_gen::fn_kprintf_00505ec8__recomp},
    {"sub_5063C8", 0x5063C8, &recomp_gen::fn_sub_5063C8_005063c8, &recomp_gen::fn_sub_5063C8_005063c8__recomp},
    {"sceSifSendCmd", 0x5064A8, &recomp_gen::fn_sceSifSendCmd_005064a8, &recomp_gen::fn_sceSifSendCmd_005064a8__recomp},
    {"sub_506630", 0x506630, &recomp_gen::fn_sub_506630_00506630, &recomp_gen::fn_sub_506630_00506630__recomp},
    {"sceSifWriteBackDCache", 0x506670, &recomp_gen::fn_sceSifWriteBackDCache_00506670, &recomp_gen::fn_sceSifWriteBackDCache_00506670__recomp},
    {"sub_5067F8", 0x5067F8, &recomp_gen::fn_sub_5067F8_005067f8, &recomp_gen::fn_sub_5067F8_005067f8__recomp},
    {"sceSifExitRpc", 0x506A48, &recomp_gen::fn_sceSifExitRpc_00506a48, &recomp_gen::fn_sceSifExitRpc_00506a48__recomp},
    {"_sceRpcGetPacket", 0x506A70, &recomp_gen::fn__sceRpcGetPacket_00506a70, &recomp_gen::fn__sceRpcGetPacket_00506a70__recomp},
    {"_sceRpcFreePacket", 0x506B18, &recomp_gen::fn__sceRpcFreePacket_00506b18, &recomp_gen::fn__sceRpcFreePacket_00506b18__recomp},
    {"_sceRpcGetFPacket", 0x506B38, &recomp_gen::fn__sceRpcGetFPacket_00506b38, &recomp_gen::fn__sceRpcGetFPacket_00506b38__recomp},
    {"_search_svdata", 0x506EF0, &recomp_gen::fn__search_svdata_00506ef0, &recomp_gen::fn__search_svdata_00506ef0__recomp},
    {"_request_call", 0x5071A0, &recomp_gen::fn__request_call_005071a0, &recomp_gen::fn__request_call_005071a0__recomp},
    {"sceSifCheckStatRpc", 0x507430, &recomp_gen::fn_sceSifCheckStatRpc_00507430, &recomp_gen::fn_sceSifCheckStatRpc_00507430__recomp},
    {"sceSifSetRpcQueue", 0x507470, &recomp_gen::fn_sceSifSetRpcQueue_00507470, &recomp_gen::fn_sceSifSetRpcQueue_00507470__recomp},
    {"sceSifRegisterRpc", 0x507508, &recomp_gen::fn_sceSifRegisterRpc_00507508, &recomp_gen::fn_sceSifRegisterRpc_00507508__recomp},
    {"sceSifRemoveRpc", 0x5075D8, &recomp_gen::fn_sceSifRemoveRpc_005075d8, &recomp_gen::fn_sceSifRemoveRpc_005075d8__recomp},
    {"sceSifRemoveRpcQueue", 0x507670, &recomp_gen::fn_sceSifRemoveRpcQueue_00507670, &recomp_gen::fn_sceSifRemoveRpcQueue_00507670__recomp},
    {"sceSifGetNextRequest", 0x507700, &recomp_gen::fn_sceSifGetNextRequest_00507700, &recomp_gen::fn_sceSifGetNextRequest_00507700__recomp},
    {"_sceFsIobSemaMK", 0x507960, &recomp_gen::fn__sceFsIobSemaMK_00507960, &recomp_gen::fn__sceFsIobSemaMK_00507960__recomp},
    {"use_iob_cnt", 0x5079D0, &recomp_gen::fn_use_iob_cnt_005079d0, &recomp_gen::fn_use_iob_cnt_005079d0__recomp},
    {"new_iob", 0x507A50, &recomp_gen::fn_new_iob_00507a50, &recomp_gen::fn_new_iob_00507a50__recomp},
    {"get_iob", 0x507BC8, &recomp_gen::fn_get_iob_00507bc8, &recomp_gen::fn_get_iob_00507bc8__recomp},
    {"_sceFs_Rcv_Intr", 0x507C38, &recomp_gen::fn__sceFs_Rcv_Intr_00507c38, &recomp_gen::fn__sceFs_Rcv_Intr_00507c38__recomp},
    {"_sceFsSemInit", 0x507FF0, &recomp_gen::fn__sceFsSemInit_00507ff0, &recomp_gen::fn__sceFsSemInit_00507ff0__recomp},
    {"_sceFsWaitS", 0x508048, &recomp_gen::fn__sceFsWaitS_00508048, &recomp_gen::fn__sceFsWaitS_00508048__recomp},
    {"_sceFsSigSema", 0x508078, &recomp_gen::fn__sceFsSigSema_00508078, &recomp_gen::fn__sceFsSigSema_00508078__recomp},
    {"scePowerOffHandler", 0x508088, &recomp_gen::fn_scePowerOffHandler_00508088, &recomp_gen::fn_scePowerOffHandler_00508088__recomp},
    {"sceFsReset", 0x508408, &recomp_gen::fn_sceFsReset_00508408, &recomp_gen::fn_sceFsReset_00508408__recomp},
    {"sceRemove", 0x509908, &recomp_gen::fn_sceRemove_00509908, &recomp_gen::fn_sceRemove_00509908__recomp},
    {"sceRmdir", 0x509AE0, &recomp_gen::fn_sceRmdir_00509ae0, &recomp_gen::fn_sceRmdir_00509ae0__recomp},
    {"sceDelDrv", 0x509EB0, &recomp_gen::fn_sceDelDrv_00509eb0, &recomp_gen::fn_sceDelDrv_00509eb0__recomp},
    {"sceDopen", 0x509ED0, &recomp_gen::fn_sceDopen_00509ed0, &recomp_gen::fn_sceDopen_00509ed0__recomp},
    {"sceChdir", 0x50A868, &recomp_gen::fn_sceChdir_0050a868, &recomp_gen::fn_sceChdir_0050a868__recomp},
    {"sceUmount", 0x50ACB8, &recomp_gen::fn_sceUmount_0050acb8, &recomp_gen::fn_sceUmount_0050acb8__recomp},
    {"sceSifLoadFileReset", 0x50BC78, &recomp_gen::fn_sceSifLoadFileReset_0050bc78, &recomp_gen::fn_sceSifLoadFileReset_0050bc78__recomp},
    {"SetTLBHandler", 0x50CB28, &recomp_gen::fn_SetTLBHandler_0050cb28, &recomp_gen::fn_SetTLBHandler_0050cb28__recomp},
    {"SetDebugHandler", 0x50CB88, &recomp_gen::fn_SetDebugHandler_0050cb88, &recomp_gen::fn_SetDebugHandler_0050cb88__recomp},
    {"kCopy", 0x50CC20, &recomp_gen::fn_kCopy_0050cc20, &recomp_gen::fn_kCopy_0050cc20__recomp},
    {"InitTLBFunctions", 0x50CC78, &recomp_gen::fn_InitTLBFunctions_0050cc78, &recomp_gen::fn_InitTLBFunctions_0050cc78__recomp},
    {"SetTLBEntry", 0x50CD70, &recomp_gen::fn_SetTLBEntry_0050cd70, &recomp_gen::fn_SetTLBEntry_0050cd70__recomp},
    {"InitTLB", 0x50CE00, &recomp_gen::fn_InitTLB_0050ce00, &recomp_gen::fn_InitTLB_0050ce00__recomp},
    {"sub_50D37C", 0x50D37C, &recomp_gen::fn_sub_50D37C_0050d37c, &recomp_gen::fn_sub_50D37C_0050d37c__recomp},
    {"supplement_crt0", 0x50D408, &recomp_gen::fn_supplement_crt0_0050d408, &recomp_gen::fn_supplement_crt0_0050d408__recomp},
    {"kCopy_0", 0x50D488, &recomp_gen::fn_kCopy_0_0050d488, &recomp_gen::fn_kCopy_0_0050d488__recomp},
    {"kFindAddress", 0x50D4C0, &recomp_gen::fn_kFindAddress_0050d4c0, &recomp_gen::fn_kFindAddress_0050d4c0__recomp},
    {"GetSystemCallEntry", 0x50D510, &recomp_gen::fn_GetSystemCallEntry_0050d510, &recomp_gen::fn_GetSystemCallEntry_0050d510__recomp},
    {"InitSystemCallTableAddress", 0x50D548, &recomp_gen::fn_InitSystemCallTableAddress_0050d548, &recomp_gen::fn_InitSystemCallTableAddress_0050d548__recomp},
    {"crt_init_runtime", 0x50D658, &recomp_gen::fn_crt_init_runtime_0050d658, &recomp_gen::fn_crt_init_runtime_0050d658__recomp},
    {"kCopy_1", 0x50D6D0, &recomp_gen::fn_kCopy_1_0050d6d0, &recomp_gen::fn_kCopy_1_0050d6d0__recomp},
    {"PatchIsNeeded", 0x50D718, &recomp_gen::fn_PatchIsNeeded_0050d718, &recomp_gen::fn_PatchIsNeeded_0050d718__recomp},
    {"InitExecPS2", 0x50D780, &recomp_gen::fn_InitExecPS2_0050d780, &recomp_gen::fn_InitExecPS2_0050d780__recomp},
    {"SetArg", 0x50D880, &recomp_gen::fn_SetArg_0050d880, &recomp_gen::fn_SetArg_0050d880__recomp},
    {"sub_50D998", 0x50D998, &recomp_gen::fn_sub_50D998_0050d998, &recomp_gen::fn_sub_50D998_0050d998__recomp},
    {"ExecPS2", 0x50D9A0, &recomp_gen::fn_ExecPS2_0050d9a0, &recomp_gen::fn_ExecPS2_0050d9a0__recomp},
    {"kCopy_3", 0x50DAF0, &recomp_gen::fn_kCopy_3_0050daf0, &recomp_gen::fn_kCopy_3_0050daf0__recomp},
    {"sub_50DE08", 0x50DE08, &recomp_gen::fn_sub_50DE08_0050de08, &recomp_gen::fn_sub_50DE08_0050de08__recomp},
    {"sub_50E648", 0x50E648, &recomp_gen::fn_sub_50E648_0050e648, &recomp_gen::fn_sub_50E648_0050e648__recomp},
    {"sub_50E750", 0x50E750, &recomp_gen::fn_sub_50E750_0050e750, &recomp_gen::fn_sub_50E750_0050e750__recomp},
    {"sub_50E7F0", 0x50E7F0, &recomp_gen::fn_sub_50E7F0_0050e7f0, &recomp_gen::fn_sub_50E7F0_0050e7f0__recomp},
    {"sub_50E900", 0x50E900, &recomp_gen::fn_sub_50E900_0050e900, &recomp_gen::fn_sub_50E900_0050e900__recomp},
    {"sub_50EA30", 0x50EA30, &recomp_gen::fn_sub_50EA30_0050ea30, &recomp_gen::fn_sub_50EA30_0050ea30__recomp},
    {"sub_50EA80", 0x50EA80, &recomp_gen::fn_sub_50EA80_0050ea80, &recomp_gen::fn_sub_50EA80_0050ea80__recomp},
    {"sub_50EB98", 0x50EB98, &recomp_gen::fn_sub_50EB98_0050eb98, &recomp_gen::fn_sub_50EB98_0050eb98__recomp},
    {"sub_50EC58", 0x50EC58, &recomp_gen::fn_sub_50EC58_0050ec58, &recomp_gen::fn_sub_50EC58_0050ec58__recomp},
    {"sub_50EDB8", 0x50EDB8, &recomp_gen::fn_sub_50EDB8_0050edb8, &recomp_gen::fn_sub_50EDB8_0050edb8__recomp},
    {"SetTimerAlarm", 0x50F090, &recomp_gen::fn_SetTimerAlarm_0050f090, &recomp_gen::fn_SetTimerAlarm_0050f090__recomp},
    {"ReleaseTimerAlarm", 0x50F2B0, &recomp_gen::fn_ReleaseTimerAlarm_0050f2b0, &recomp_gen::fn_ReleaseTimerAlarm_0050f2b0__recomp},
    {"sceSifSetRebootNotifyBuffer", 0x50F3F8, &recomp_gen::fn_sceSifSetRebootNotifyBuffer_0050f3f8, &recomp_gen::fn_sceSifSetRebootNotifyBuffer_0050f3f8__recomp},
    {"sceSifAddRebootNotifyHandler", 0x50F478, &recomp_gen::fn_sceSifAddRebootNotifyHandler_0050f478, &recomp_gen::fn_sceSifAddRebootNotifyHandler_0050f478__recomp},
    {"sceSifRemoveRebootNotifyHandler", 0x50F530, &recomp_gen::fn_sceSifRemoveRebootNotifyHandler_0050f530, &recomp_gen::fn_sceSifRemoveRebootNotifyHandler_0050f530__recomp},
    {"sceSifExecNotifyHandler", 0x50F588, &recomp_gen::fn_sceSifExecNotifyHandler_0050f588, &recomp_gen::fn_sceSifExecNotifyHandler_0050f588__recomp},
    {"_sceCd_cd_callback", 0x50F698, &recomp_gen::fn__sceCd_cd_callback_0050f698, &recomp_gen::fn__sceCd_cd_callback_0050f698__recomp},
    {"_sceCd_cbLoop", 0x50F738, &recomp_gen::fn__sceCd_cbLoop_0050f738, &recomp_gen::fn__sceCd_cbLoop_0050f738__recomp},
    {"sceCdInitEeCB", 0x50F808, &recomp_gen::fn_sceCdInitEeCB_0050f808, &recomp_gen::fn_sceCdInitEeCB_0050f808__recomp},
    {"cmd_sem_init", 0x50F960, &recomp_gen::fn_cmd_sem_init_0050f960, &recomp_gen::fn_cmd_sem_init_0050f960__recomp},
    {"sceCdPOffCallback", 0x50FAE8, &recomp_gen::fn_sceCdPOffCallback_0050fae8, &recomp_gen::fn_sceCdPOffCallback_0050fae8__recomp},
    {"_sceCd_Poff_Intr", 0x50FB68, &recomp_gen::fn__sceCd_Poff_Intr_0050fb68, &recomp_gen::fn__sceCd_Poff_Intr_0050fb68__recomp},
    {"PowerOffCB", 0x50FBC0, &recomp_gen::fn_PowerOffCB_0050fbc0, &recomp_gen::fn_PowerOffCB_0050fbc0__recomp},
    {"_sceCdSC", 0x5103B0, &recomp_gen::fn__sceCdSC_005103b0, &recomp_gen::fn__sceCdSC_005103b0__recomp},
    {"sceCdChgSys", 0x511110, &recomp_gen::fn_sceCdChgSys_00511110, &recomp_gen::fn_sceCdChgSys_00511110__recomp},
    {"scePadSetReqState", 0x511B08, &recomp_gen::fn_scePadSetReqState_00511b08, &recomp_gen::fn_scePadSetReqState_00511b08__recomp},
    {"scePadSetActDirect", 0x512070, &recomp_gen::fn_scePadSetActDirect_00512070, &recomp_gen::fn_scePadSetActDirect_00512070__recomp},
    {"sceSdCallBack", 0x5129A0, &recomp_gen::fn_sceSdCallBack_005129a0, &recomp_gen::fn_sceSdCallBack_005129a0__recomp},
    {"_sdrCB", 0x512FF0, &recomp_gen::fn__sdrCB_00512ff0, &recomp_gen::fn__sdrCB_00512ff0__recomp},
    {"sceMc2End", 0x513290, &recomp_gen::fn_sceMc2End_00513290, &recomp_gen::fn_sceMc2End_00513290__recomp},
    {"sceMc2SearchSocket", 0x513478, &recomp_gen::fn_sceMc2SearchSocket_00513478, &recomp_gen::fn_sceMc2SearchSocket_00513478__recomp},
    {"sceMc2ChangeThreadPriority", 0x513528, &recomp_gen::fn_sceMc2ChangeThreadPriority_00513528, &recomp_gen::fn_sceMc2ChangeThreadPriority_00513528__recomp},
    {"sceMc2iChangeThreadPriority", 0x513560, &recomp_gen::fn_sceMc2iChangeThreadPriority_00513560, &recomp_gen::fn_sceMc2iChangeThreadPriority_00513560__recomp},
    {"sceMc2GetDirAllAsync", 0x5138B8, &recomp_gen::fn_sceMc2GetDirAllAsync_005138b8, &recomp_gen::fn_sceMc2GetDirAllAsync_005138b8__recomp},
    {"basic_thread", 0x5145F8, &recomp_gen::fn_basic_thread_005145f8, &recomp_gen::fn_basic_thread_005145f8__recomp},
    {"_sceMcFatFormat", 0x516118, &recomp_gen::fn__sceMcFatFormat_00516118, &recomp_gen::fn__sceMcFatFormat_00516118__recomp},
    {"SyncDma", 0x51AD10, &recomp_gen::fn_SyncDma_0051ad10, &recomp_gen::fn_SyncDma_0051ad10__recomp},
    {"SyncDmaForRead", 0x51ADE0, &recomp_gen::fn_SyncDmaForRead_0051ade0, &recomp_gen::fn_SyncDmaForRead_0051ade0__recomp},
    {"_sceMcCoreInit", 0x51AE68, &recomp_gen::fn__sceMcCoreInit_0051ae68, &recomp_gen::fn__sceMcCoreInit_0051ae68__recomp},
    {"_sceMcCoreEnd", 0x51AEF8, &recomp_gen::fn__sceMcCoreEnd_0051aef8, &recomp_gen::fn__sceMcCoreEnd_0051aef8__recomp},
    {"_sceMcCoreWriteSameData", 0x51BA88, &recomp_gen::fn__sceMcCoreWriteSameData_0051ba88, &recomp_gen::fn__sceMcCoreWriteSameData_0051ba88__recomp},
    {"sceDbcEnd", 0x51C658, &recomp_gen::fn_sceDbcEnd_0051c658, &recomp_gen::fn_sceDbcEnd_0051c658__recomp},
    {"sceDbcGetConnection", 0x51CAD0, &recomp_gen::fn_sceDbcGetConnection_0051cad0, &recomp_gen::fn_sceDbcGetConnection_0051cad0__recomp},
    {"sceSkQuit", 0x51DAD8, &recomp_gen::fn_sceSkQuit_0051dad8, &recomp_gen::fn_sceSkQuit_0051dad8__recomp},
    {"__malloc_lock", 0x5214C8, &recomp_gen::fn___malloc_lock_005214c8, &recomp_gen::fn___malloc_lock_005214c8__recomp},
    {"__malloc_unlock", 0x521520, &recomp_gen::fn___malloc_unlock_00521520, &recomp_gen::fn___malloc_unlock_00521520__recomp},
    {"_read_r", 0x522F38, &recomp_gen::fn__read_r_00522f38, &recomp_gen::fn__read_r_00522f38__recomp},
    {"_sbrk_r", 0x523930, &recomp_gen::fn__sbrk_r_00523930, &recomp_gen::fn__sbrk_r_00523930__recomp},
    {"_write_r", 0x528970, &recomp_gen::fn__write_r_00528970, &recomp_gen::fn__write_r_00528970__recomp},
};

const Case& C(const char* n) { return by_name(kCases, std::size(kCases), n); }

constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;

// --- the stand-ins: the kernel-call wrappers (syscalls) and the not-emitted library callees the bodies reach -------
constexpr u32 kCreateSema = 0x503160u, kDeleteSema = 0x503170u, kSignalSema = 0x503180u, kiSignalSema = 0x503190u;
constexpr u32 kWaitSema = 0x5031A0u, kDeci2Call = 0x503590u, kCallCode = 0x509758u, kFsInit = 0x508170u;
constexpr u32 kChangePrio = 0x502FF0u, kiWakeup = 0x504028u, kSetVTLB = 0x502E10u, kSetVCommon = 0x502E20u;
constexpr u32 kSetTLBEntryK = 0x50CD60u, kTtyRead = 0x504A30u, kScePrintf = 0x505E48u, kSendCmdK = 0x5064F8u;
constexpr u32 kPadGetDmaStr = 0x511830u, kSendToIop = 0x511478u, kDisableDmac = 0x503D10u, kRemoveDmacHandler = 0x502E90u;
constexpr u32 kReadTimer = 0x50E508u, kSetCompare = 0x50E000u;  // the timer (as test_libs1_kernel stands them in)

// TTY record (sceTtyInit): +0 socket, +12 busy (sceTtyWrite polls until the handler clears it); the packet at +0x3C.
constexpr u32 kTty = 0x966650u, kTtyBusy = 0x96665Cu, kTtyPacket = 0x96668Cu;

void stand_ins(StandInWorld& w) {
    struct Rec {
        u32 va;
        const char* name;
        u64 v0;
    };
    static const Rec kRecorders[] = {
        {kCreateSema, "_sceCreateSema", 9}, {kDeleteSema, "_sceDeleteSema", 0}, {kSignalSema, "_sceSignalSema", 0},
        {kiSignalSema, "_sceiSignalSema", 0}, {kWaitSema, "_sceWaitSema", 0}, {kFsInit, "sceFsInit", 0},
        {kChangePrio, "_sceChangeThreadPriority", 0}, {kiWakeup, "iWakeupThread", 0},
        {kSetVTLB, "_sceSetVTLBRefillHandler", 0}, {kSetVCommon, "_sceSetVCommonHandler", 0},
        {kSetTLBEntryK, "_sce_SetTLBEntry", 0}, {kTtyRead, "sceTtyRead", 0}, {kScePrintf, "scePrintf", 0},
        {kSendCmdK, "_sceSifSendCmd", 1}, {kSendToIop, "_send_to_iop", 1}, {kDisableDmac, "DisableDmac", 0},
        {kRemoveDmacHandler, "_sceRemoveDmacHandler", 0}};
    for (const Rec& r : kRecorders) w.si.install_recorder(r.va, r.name, r.v0);
    w.si.install(kCallCode, "_sceCallCode", [](EEContext& ctx, StandIns&, StandInCall& c) {
        c.v0 = *gptr(ctx, static_cast<u32>(c.args[0])) == 0xEE ? sx(0xFFFFFFFBu) : 3;  // a name starting 0xEE: refused (-5)
    });
    // DECI2: open answers socket 3; a poll (4) is the moment the TTY's send completes (the handler clears busy).
    w.si.install(kDeci2Call, "_sceDeci2Call", [](EEContext& ctx, StandIns&, StandInCall& c) {
        const s32 op = static_cast<s32>(c.args[0]);
        if (op == 4) std::memset(gptr(ctx, kTtyBusy), 0, 4);
        c.v0 = op == 1 ? 3 : 0;
    });
    // libpad: the DMA status block; a caller buffer gets "ready" (1) at +114.
    w.si.install(kPadGetDmaStr, "scePadGetDmaStr", [](EEContext& ctx, StandIns&, StandInCall& c) {
        if (c.args[2] != 0) *gptr(ctx, static_cast<u32>(c.args[2]) + 114) = 1;
        c.v0 = kWorld + 0x8000;
    });
    auto clock = std::make_shared<u64>(0x100000);
    w.si.install(kReadTimer, "sub_50E508 (read the timer)", [clock](EEContext&, StandIns&, StandInCall& c) {
        *clock += 1000;
        c.v0 = *clock;
    });
    w.si.install_recorder(kSetCompare, "sub_50E000 (program the compare)", 0);
}

// The infinite loops (worker threads) meet no stand-ins in the sweep: they stop, identically, at their first callee.
bool loops_forever(const Case& c) {
    const std::string n = c.name;
    return n == "topThread" || n == "_sceCd_cbLoop" || n == "basic_thread";
}

}  // namespace

TEST_CASE("game(libs6): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    std::vector<Case> loops, rest;
    for (const Case& c : kCases) (loops_forever(c) ? loops : rest).push_back(c);
    random_sweep(*m, rest.data(), rest.size(), kWorld, kWorldSize, 32, stand_ins, true);
    random_sweep(*m, loops.data(), loops.size(), kWorld, kWorldSize, 16, {}, true);
}

TEST_CASE("game(libs6): RPC packets, queues and servers") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    u32 seed = 1;
    // a client's packet pool: {next id, pool, count} and four 64-byte packets, #0 and #2 busy
    const u32 rd = kWorld, pool = kWorld + 0x100;
    wzero(*m, kWorld, 0x2000);
    w32(*m, rd, 0);  // the id counter: the first packet gets 1 and the counter jumps to 2
    w32(*m, rd + 4, pool);
    w32(*m, rd + 8, 4);
    w32(*m, pool + 16, 1);
    w32(*m, pool + 128 + 16, 1);
    auto r = pair(*m, C("_sceRpcGetPacket"), {rd}, seed++, "get packet", stand_ins);
    CHECK(v0_of(r) == pool + 64);
    CHECK(r32(*m, pool + 64 + 16) == ((1u << 16) | 5u));
    CHECK(r32(*m, pool + 64 + 20) == pool + 64);
    CHECK(r32(*m, pool + 64 + 24) == 1u);
    CHECK(r32(*m, rd) == 2u);
    r = pair(*m, C("_sceRpcGetPacket"), {rd}, seed++, "get packet 2", stand_ins);
    CHECK(v0_of(r) == pool + 192);
    CHECK(r32(*m, pool + 192 + 24) == 3u);
    CHECK(v0_of(pair(*m, C("_sceRpcGetPacket"), {rd}, seed++, "pool full", stand_ins)) == 0);
    // the call status: in flight while the packet is busy and its id matches
    const u32 cd = kWorld + 0x40;
    w32(*m, cd, pool + 64);
    w32(*m, cd + 4, 1);
    CHECK(v0_of(pair(*m, C("sceSifCheckStatRpc"), {cd}, seed++, "stat busy", stand_ins)) == 1);
    w32(*m, cd + 4, 7);
    CHECK(v0_of(pair(*m, C("sceSifCheckStatRpc"), {cd}, seed++, "stat other id", stand_ins)) == 0);
    w32(*m, cd + 4, 1);
    pair(*m, C("_sceRpcFreePacket"), {pool + 64}, seed++, "free packet", stand_ins);
    CHECK((r32(*m, pool + 64 + 16) & 1u) == 0u);
    CHECK(r32(*m, pool + 64 + 24) == 0u);
    CHECK(v0_of(pair(*m, C("sceSifCheckStatRpc"), {cd}, seed++, "stat freed", stand_ins)) == 0);
    w32(*m, cd, 0);
    CHECK(v0_of(pair(*m, C("sceSifCheckStatRpc"), {cd}, seed++, "stat no packet", stand_ins)) == 0);
    // a server's receive ring: base +20, count +24, index +36 (round robin)
    const u32 sv = kWorld + 0x400;
    w32(*m, sv + 20, pool);
    w32(*m, sv + 24, 3);
    w32(*m, sv + 36, 5);
    CHECK(v0_of(pair(*m, C("_sceRpcGetFPacket"), {sv}, seed++, "fpacket wrap", stand_ins)) == pool + 2 * 64);
    CHECK(r32(*m, sv + 36) == 3u);
    CHECK(v0_of(pair(*m, C("_sceRpcGetFPacket"), {sv}, seed++, "fpacket", stand_ins)) == pool);

    // queues and servers on the dorm snapshot's live list (the sound driver's and the streamer's queues)
    const std::vector<u8> snap = read_snapshot("dorm_replay_4900");
    if (snap.size() != EEMemory::kMainRamSize) {
        MESSAGE("SKIP: snapshot dorm_replay_4900 not found");
        return;
    }
    copy_from_snapshot(*m, snap, 0x968400u, 0x200);
    const u32 head = r32(*m, libs6::kRpcQueueList);
    std::vector<u32> live;
    for (u32 q = head; q != 0 && live.size() < 16; q = r32(*m, q + 20)) {
        live.push_back(q);
        copy_from_snapshot(*m, snap, q, 24);
    }
    const u32 q = kWorld + 0x800, s1 = kWorld + 0x900, s2 = kWorld + 0x980;
    pair(*m, C("sceSifSetRpcQueue"), {q, 0x21}, seed++, "set queue", stand_ins);
    CHECK(r32(*m, q) == 0x21u);
    CHECK(r32(*m, q + 20) == 0u);
    CHECK(r32(*m, live.empty() ? libs6::kRpcQueueList : live.back() + 20) == q);
    // two servers: (sd, cmd, func, buf, cfunc, cbuf, queue in $t0)
    pair(*m, C("sceSifRegisterRpc"), {s1, 0x80000701u, 0x123400u, 0x200000u}, seed++, "register 1", stand_ins,
         hw_in({{GPR_T0, 0}, {GPR_T0 + 1, 0}, {GPR_T0 + 2, q}}));
    pair(*m, C("sceSifRegisterRpc"), {s2, 0x80000702u, 0x123500u, 0x201000u}, seed++, "register 2", stand_ins,
         hw_in({{GPR_T0, 0}, {GPR_T0 + 1, 0}, {GPR_T0 + 2, q}}));
    CHECK(r32(*m, q + 8) == s1);
    CHECK(r32(*m, s1 + 56) == s2);
    CHECK(r32(*m, s2 + 64) == q);
    // the bind look-up walks every queue from the RPC data's list (+40)
    const u32 rpcd = kWorld + 0xA00;
    w32(*m, rpcd + 40, live.empty() ? q : live.front());
    CHECK(v0_of(pair(*m, C("_search_svdata"), {sx(0x80000702u), rpcd}, seed++, "search svdata", stand_ins)) == s2);
    CHECK(v0_of(pair(*m, C("_search_svdata"), {sx(0x80000799u), rpcd}, seed++, "search svdata none", stand_ins)) == 0);
    // a call request queues server 2 and wakes the idle thread; the next request pops it
    const u32 req = kWorld + 0xB00;
    for (u32 i = 4; i < 13; ++i) w32(*m, req + 4 * i, 0x1000 + i);
    w32(*m, req + 52, s2);
    pair(*m, C("_request_call"), {req}, seed++, "request call", stand_ins);
    CHECK(r32(*m, q + 12) == s2);
    CHECK(r32(*m, q + 16) == s2);
    CHECK(r32(*m, s2 + 32) == 0x1005u);
    CHECK(last_log().calls_to(kiWakeup) == 1);
    CHECK(v0_of(pair(*m, C("sceSifGetNextRequest"), {q}, seed++, "next request", stand_ins)) == s2);
    CHECK(r32(*m, q + 4) == 1u);
    CHECK(v0_of(pair(*m, C("sceSifGetNextRequest"), {q}, seed++, "next request empty", stand_ins)) == 0);
    CHECK(r32(*m, q + 4) == 0u);
    // unlink a server, then the queue: the live list is as the snapshot had it
    pair(*m, C("sceSifRemoveRpc"), {s2, q}, seed++, "remove server", stand_ins);
    CHECK(r32(*m, s1 + 56) == 0u);
    pair(*m, C("sceSifRemoveRpc"), {s1, q}, seed++, "remove head server", stand_ins);
    CHECK(r32(*m, q + 8) == 0u);
    pair(*m, C("sceSifRemoveRpcQueue"), {q}, seed++, "remove queue", stand_ins);
    CHECK(r32(*m, libs6::kRpcQueueList) == head);
    if (!live.empty()) CHECK(r32(*m, live.back() + 20) == 0u);
    MESSAGE("pairs " << counts().pairs << ", stopped " << counts().stops);
}

TEST_CASE("game(libs6): the file layer's iob table on the dorm snapshot") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const std::vector<u8> snap = read_snapshot("dorm_replay_4900");
    if (snap.size() != EEMemory::kMainRamSize) {
        MESSAGE("SKIP: snapshot dorm_replay_4900 not found");
        return;
    }
    constexpr u32 kIob = 0x969A00u;
    copy_from_snapshot(*m, snap, kIob, 0x200);
    copy_from_snapshot(*m, snap, 0x77F500u, 0x80);  // the semaphores, the initialised flag
    u32 seed = 200;
    auto used = [&] {
        u32 n = 0;
        for (u32 i = 0; i < 32; ++i) n += r32(*m, kIob + 16 * i + 4) != 0 ? 1 : 0;
        return n;
    };
    CHECK(v0_of(pair(*m, C("use_iob_cnt"), {}, seed++, "count", stand_ins)) == used());
    for (u32 fd : {0u, 1u, 7u, 31u, 32u, 100u}) {
        const auto r = pair(*m, C("get_iob"), {fd}, seed++, "get_iob " + std::to_string(fd), stand_ins);
        CHECK(v0_of(r) == (fd < 32 ? kIob + 16 * fd : 0));
    }
    // new_iob takes the first free slot; a full table answers null
    u32 first = 0;
    while (first < 32 && r32(*m, kIob + 16 * first + 4) != 0) ++first;
    if (first < 32) {
        const auto r = pair(*m, C("new_iob"), {}, seed++, "new_iob", stand_ins);
        CHECK(v0_of(r) == kIob + 16 * first);
        CHECK(r32(*m, kIob + 16 * first + 4) == 0x10000000u);
    }
    for (u32 i = 0; i < 32; ++i)
        if (r32(*m, kIob + 16 * i + 4) == 0) w32(*m, kIob + 16 * i + 4, 0x10000000u);
    CHECK(v0_of(pair(*m, C("new_iob"), {}, seed++, "new_iob full", stand_ins)) == 0);
    CHECK(v0s(pair(*m, C("sceDopen"), {kWorld}, seed++, "dopen full", stand_ins)) == -19);
    // dopen: the IOP descriptor into the iob, the index back; a refused name frees the slot
    copy_from_snapshot(*m, snap, kIob, 0x200);
    w32(*m, kIob + 16 * 30 + 4, 0);
    for (u32 i = 0; i < 30; ++i) w32(*m, kIob + 16 * i + 4, 0x10000000u);
    wstr(*m, kWorld, "mc0:/BASLUS-21621");
    auto r = pair(*m, C("sceDopen"), {kWorld}, seed++, "dopen", stand_ins);
    CHECK(v0_of(r) == 30);
    CHECK(r32(*m, kIob + 16 * 30) == 3u);
    w32(*m, kIob + 16 * 31 + 4, 0);
    w8(*m, kWorld, 0xEE);
    r = pair(*m, C("sceDopen"), {kWorld}, seed++, "dopen refused", stand_ins);
    CHECK(v0s(r) == -5);
    CHECK(r32(*m, kIob + 16 * 31 + 4) == 0u);
    // the semaphores are made once: with both ids set, no kernel call
    w32(*m, libs6::kIobSema, 4);
    w32(*m, libs6::kFioSema, 5);
    pair(*m, C("_sceFsIobSemaMK"), {}, seed++, "iob sema made", stand_ins);
    CHECK(last_log().calls_to(kCreateSema) == 0);
    pair(*m, C("_sceFsWaitS"), {}, seed++, "wait", stand_ins);
    CHECK(last_log().calls_to(kCreateSema) == 0);
    CHECK(last_log().calls_to(kWaitSema) == 1);
    w32(*m, libs6::kIobSema, 0xFFFFFFFFu);
    pair(*m, C("_sceFsIobSemaMK"), {}, seed++, "iob sema", stand_ins);
    CHECK(last_log().calls_to(kCreateSema) == 2);
    CHECK(r32(*m, libs6::kIobSema) == 9u);
    MESSAGE("pairs " << counts().pairs << ", stopped " << counts().stops);
}

TEST_CASE("game(libs6): thread-context timer alarms and the counter wrappers") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    namespace al = p3fes::game::sce::alarm;
    constexpr u32 kRecs = 0x01830000u;  // 8 counter records, 64-byte aligned
    w32(*m, al::kSetUp, 0);
    w32(*m, al::kInUse, 0);
    w32(*m, al::kTagSeq, 0);
    w32(*m, al::kPending, 0);
    w32(*m, al::kHandling, 0);
    w32(*m, al::kCursor, 0);
    for (u32 i = 0; i < 8; ++i) {
        wzero(*m, kRecs + 64 * i, 64);
        w32(*m, kRecs + 64 * i + al::kNext, i < 7 ? kRecs + 64 * (i + 1) : 0);
    }
    w32(*m, al::kFreeList, kRecs);
    const u32 u = 0x01836000u;  // three user-alarm records
    for (u32 i = 0; i < 3; ++i) {
        wzero(*m, u + 16 * i, 16);
        w32(*m, u + 16 * i, i < 2 ? u + 16 * (i + 1) : 0);
    }
    w32(*m, libs6::kAlarmFreeList, u);
    u32 seed = 300;
    CHECK(v0_of(pair(*m, C("SetTimerAlarm"), {1000, 0, 0}, seed++, "no handler", stand_ins)) == sx(0x80000016u));
    std::vector<u32> ids;
    for (u32 i = 0; i < 3; ++i) {
        const auto r = pair(*m, C("SetTimerAlarm"), {sx(1000 * (i + 1)), 0x123450u, 0x40 + i}, seed++, "alarm " + std::to_string(i), stand_ins);
        const u32 id = static_cast<u32>(v0_of(r));
        CHECK((id & 1u) == 1u);
        CHECK((id >> 8 << 4) == u + 16 * i);
        CHECK(r32(*m, u + 16 * i + 8) == 0x123450u);
        CHECK(r32(*m, u + 16 * i + 12) == 0x40 + i);
        const u32 cid = r32(*m, u + 16 * i + 4);
        CHECK(r32(*m, (cid >> 10 << 6) + 40) == 0x50F030u);  // armed with AlarmHandler
        ids.push_back(id);
    }
    CHECK(v0_of(pair(*m, C("SetTimerAlarm"), {1, 0x123450u, 0}, seed++, "none free", stand_ins)) == sx(0x80008005u));
    // the counter wrappers on the first alarm's counter
    const u32 cid = r32(*m, u + 4);
    const u32 crec = cid >> 10 << 6;
    pair(*m, C("sub_50EA30"), {cid}, seed++, "stop counter", stand_ins);
    CHECK((r32(*m, crec + al::kFlags) & 1u) == 0u);
    const u64 total = r64(*m, crec + al::kU64B);
    CHECK(v0_of(pair(*m, C("sub_50EC58"), {cid}, seed++, "counter time", stand_ins)) == total);
    CHECK(v0_of(pair(*m, C("sub_50EA80"), {cid, 777}, seed++, "set count", stand_ins)) == total);
    CHECK(r64(*m, crec + al::kU64B) == 777u);
    CHECK(v0_of(pair(*m, C("sub_50EA80"), {cid ^ 1, 5}, seed++, "set count wrong tag", stand_ins)) == ~0ull);
    CHECK(v0_of(pair(*m, C("sub_50EB98"), {cid}, seed++, "base time stopped", stand_ins)) == 0);
    pair(*m, C("sub_50E900"), {cid}, seed++, "start counter", stand_ins);
    CHECK((r32(*m, crec + al::kFlags) & 1u) == 1u);
    const u32 counters = kWorld, left = kWorld + 4;
    CHECK(v0_of(pair(*m, C("sub_50E7F0"), {counters, left}, seed++, "counters in use", stand_ins)) == 0);
    CHECK(r32(*m, counters) + r32(*m, left) == 128u);
    CHECK(r32(*m, counters) == r32(*m, al::kInUse));
    for (u32 id : ids) {
        CHECK(v0_of(pair(*m, C("ReleaseTimerAlarm"), {id}, seed++, "release", stand_ins)) == 0);
        CHECK(r32(*m, libs6::kAlarmFreeList) == (id >> 8 << 4));
    }
    CHECK(v0_of(pair(*m, C("ReleaseTimerAlarm"), {ids[0] ^ 0x10}, seed++, "release wrong tag", stand_ins)) == sx(0x80008002u));
    // a bare counter: allocate, free
    const u32 c2 = static_cast<u32>(v0_of(pair(*m, C("sub_50E648"), {}, seed++, "alloc counter", stand_ins)));
    CHECK((c2 >> 10 << 6) >= kRecs);
    CHECK(v0_of(pair(*m, C("sub_50E750"), {c2}, seed++, "free counter", stand_ins)) == 0);
    MESSAGE("pairs " << counts().pairs << ", stopped " << counts().stops);
}

TEST_CASE("game(libs6): newlib glue -- the malloc lock, the _r wrappers, the TTY") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    u32 seed = 400;
    constexpr u32 kLockCount = 0x783398u;
    w32(*m, kLockCount, 0);
    w32(*m, libs6::kMallocIntrWasOn, 0);
    pair(*m, C("__malloc_lock"), {}, seed++, "lock", stand_ins);
    const u32 after1 = r32(*m, kLockCount);
    pair(*m, C("__malloc_lock"), {}, seed++, "lock nested", stand_ins);
    CHECK(r32(*m, kLockCount) == 2 * after1);  // both counted, or neither (inside an interrupt)
    pair(*m, C("__malloc_unlock"), {}, seed++, "unlock nested", stand_ins);
    pair(*m, C("__malloc_unlock"), {}, seed++, "unlock", stand_ins);
    CHECK(r32(*m, kLockCount) == 0u);
    // _r wrappers: errno cleared, -1 for a fd the console does not serve, the reent record untouched
    const u32 reent = kWorld;
    w32(*m, reent, 0x55);
    w32(*m, libs6::kErrno, 9);
    CHECK(v0s(pair(*m, C("_write_r"), {reent, 5, kWorld + 0x100, 4}, seed++, "write_r bad fd", stand_ins)) == -1);
    CHECK(r32(*m, libs6::kErrno) == 0u);
    CHECK(r32(*m, reent) == 0x55u);
    CHECK(v0s(pair(*m, C("_read_r"), {reent, 3, kWorld + 0x100, 4}, seed++, "read_r bad fd", stand_ins)) == -1);
    // write to stdout: the TTY opened once (socket 3), "a\nb" sent as "a\r\nb" behind a 12-byte header
    wzero(*m, kTty, 0x180);
    w32(*m, libs6::kTtyReady, 0);
    wstr(*m, kWorld + 0x100, "a\nb");
    auto r = pair(*m, C("_write_r"), {reent, 1, kWorld + 0x100, 3}, seed++, "write_r stdout", stand_ins);
    CHECK(v0_of(r) == 3);
    CHECK(r32(*m, libs6::kTtyReady) == 1u);
    CHECK(r32(*m, kTty) == 3u);
    CHECK(std::memcmp(m->at(kTtyPacket), "a\r\nb", 4) == 0);
    CHECK(r16(*m, kTtyPacket - 12) == 12 + 4);  // the header's length
    CHECK(last_log().calls_to(kDeci2Call) >= 3);  // open, request, poll
    // a second write does not open again; a busy TTY refuses
    r = pair(*m, C("write"), {2, kWorld + 0x100, 1}, seed++, "write stderr", stand_ins);
    CHECK(v0_of(r) == 1);
    w32(*m, kTtyBusy, 1);
    CHECK(v0s(pair(*m, C("sceTtyWrite"), {kWorld + 0x100, 3}, seed++, "tty busy", stand_ins)) == -1);
    w32(*m, kTtyBusy, 0);
    // the handler: event 3 sends the pending bytes and advances, event 4 ends the write
    const u32 ti = kWorld + 0x200;
    wzero(*m, ti, 32);
    w32(*m, ti + 4, 8);             // bytes left
    w32(*m, ti + 16, kWorld + 0x300);
    pair(*m, C("sceTtyHandler"), {3, 0, ti}, seed++, "handler send", stand_ins);
    CHECK(r32(*m, ti + 4) == 8u);    // the stand-in DECI2 sent 0 bytes
    w32(*m, ti + 4, 0);
    w32(*m, ti + 12, 1);
    pair(*m, C("sceTtyHandler"), {4, 0, ti}, seed++, "handler done", stand_ins);
    CHECK(r32(*m, ti + 12) == 0u);
    MESSAGE("pairs " << counts().pairs << ", stopped " << counts().stops);
}

TEST_CASE("game(libs6): SIF tables, handler slots, kernel helpers and the small queries") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    u32 seed = 500;
    // reboot notify: a 4-entry user table, the 32-entry system table
    constexpr u32 kSysNotify = 0x96D7C8u, kUserNotify = 0x780B70u;
    const u32 tab = kWorld + 0x1000;
    w32(*m, kUserNotify, 0x1234);
    w32(*m, kUserNotify + 4, 2);
    std::memset(m->at(tab), 0xAB, 64);
    CHECK(v0_of(pair(*m, C("sceSifSetRebootNotifyBuffer"), {tab, 4}, seed++, "notify buffer", stand_ins)) == 0x1234u);
    CHECK(r32(*m, kUserNotify) == tab);
    CHECK(r32(*m, tab + 60) == 0u);
    CHECK(v0_of(pair(*m, C("sceSifAddRebootNotifyHandler"), {2, 0x5063C8u, 0x77}, seed++, "add user", stand_ins)) == 0);
    CHECK(r32(*m, tab + 32) == 0x5063C8u);
    CHECK(r32(*m, tab + 36) == 0x77u);
    CHECK(v0s(pair(*m, C("sceSifAddRebootNotifyHandler"), {4, 1, 1}, seed++, "add user out of range", stand_ins)) == static_cast<s32>(0x80000069u));
    wzero(*m, kSysNotify, 512);
    CHECK(v0_of(pair(*m, C("sceSifAddRebootNotifyHandler"), {sx(0x8000001Fu), 0x5063C8u, 0x99}, seed++, "add system", stand_ins)) == 0);
    CHECK(r32(*m, kSysNotify + 16 * 31) == 0x5063C8u);
    // exec: the user table calls its one handler (sub_5063C8, a non-leaf body), the empty system slots none
    pair(*m, C("sceSifExecNotifyHandler"), {0, 0x5}, seed++, "exec user", stand_ins);
    pair(*m, C("sceSifExecNotifyHandler"), {1, 0x6}, seed++, "exec system", stand_ins);
    CHECK(v0s(pair(*m, C("sceSifRemoveRebootNotifyHandler"), {7}, seed++, "remove out of range", stand_ins)) == -105);
    CHECK(v0_of(pair(*m, C("sceSifRemoveRebootNotifyHandler"), {2}, seed++, "remove user", stand_ins)) == 0);
    CHECK(r32(*m, tab + 32) == 0u);
    CHECK(v0_of(pair(*m, C("sceSifRemoveRebootNotifyHandler"), {sx(0x8000001Fu)}, seed++, "remove system", stand_ins)) == 0);
    CHECK(r32(*m, kSysNotify + 16 * 31) == 0u);
    // SIF command handler slots (named sceSifSendCmd in symbols/): user table 0x966A6C, system table 0x966A64
    const u32 ut = kWorld + 0x1400, st = kWorld + 0x1600;
    w32(*m, 0x966A6Cu, ut);
    w32(*m, 0x966A64u, st);
    w32(*m, ut + 12 * 3, 0xDEAD);
    w32(*m, st + 12 * 2, 0xBEEF);
    pair(*m, C("sceSifSendCmd"), {3}, seed++, "clear user slot", stand_ins);
    CHECK(r32(*m, ut + 36) == 0u);
    pair(*m, C("sceSifSendCmd"), {sx(0x80000002u)}, seed++, "clear system slot", stand_ins);
    CHECK(r32(*m, st + 24) == 0u);
    // debug handlers: codes 1..13; TLB vectors for 1..3, the common vector for the rest
    CHECK(v0s(pair(*m, C("SetDebugHandler"), {0, 0x111}, seed++, "debug 0", stand_ins)) == -1);
    CHECK(v0s(pair(*m, C("SetDebugHandler"), {14, 0x111}, seed++, "debug 14", stand_ins)) == -1);
    w32(*m, 0x77F8A0u + 8, 0x222);
    CHECK(v0_of(pair(*m, C("SetDebugHandler"), {2, 0x333}, seed++, "debug 2", stand_ins)) == 0x222u);
    CHECK(last_log().calls_to(kSetVTLB) == 1);
    pair(*m, C("SetDebugHandler"), {9, 0x444}, seed++, "debug 9", stand_ins);
    CHECK(last_log().calls_to(kSetVCommon) == 1);
    CHECK(r32(*m, 0x77F8A0u + 36) == 0x444u);
    CHECK(v0s(pair(*m, C("SetTLBEntry"), {12, 0, 0, 0}, seed++, "tlb 12", stand_ins)) == -1);
    pair(*m, C("SetTLBEntry"), {13, 0, 0, 0}, seed++, "tlb 13", stand_ins);
    CHECK(last_log().calls_to(kSetTLBEntryK) == 1);
    CHECK(v0s(pair(*m, C("SetTLBEntry"), {48, 0, 0, 0}, seed++, "tlb 48", stand_ins)) == -1);
    // the kernel-mode helpers on user memory: a word search, the word copies
    const u32 hay = kWorld + 0x2000;
    for (u32 i = 0; i < 16; ++i) w32(*m, hay + 4 * i, 0x100 + i);
    CHECK(v0_of(pair(*m, C("kFindAddress"), {hay, hay + 64, 0x10A}, seed++, "find", stand_ins)) == hay + 40);
    CHECK(v0_of(pair(*m, C("kFindAddress"), {hay, hay + 64, 0x999}, seed++, "find none", stand_ins)) == 0);
    for (const char* k : {"kCopy", "kCopy_0", "kCopy_1", "kCopy_3"}) {
        wzero(*m, hay + 0x100, 64);
        pair(*m, C(k), {hay + 0x100, hay, 30}, seed++, k, stand_ins);
        CHECK(std::memcmp(m->at(hay + 0x100), m->at(hay), 28) == 0);  // whole words only
        CHECK(r32(*m, hay + 0x100 + 28) == 0u);
    }
    // libcdvd's variable query: every code answers 1 (an unknown one stores null)
    for (u32 code : {0x8001u, 0x8002u, 0x8003u, 0x8004u, 0x8011u, 0x8012u, 0x8013u, 0x8014u, 0x8005u}) {
        const auto r = pair(*m, C("_sceCdSC"), {code, kWorld + 0x3000}, seed++, "cdsc", stand_ins);
        CHECK(v0_of(r) == 1u);
    }
    // libmc2 guards: not initialised, then a bad priority, then the worker thread's priority
    w32(*m, libs6::kMc2Ready, 0);
    CHECK(v0s(pair(*m, C("sceMc2End"), {}, seed++, "mc2 end not ready", stand_ins)) == -2130608127);
    CHECK(v0s(pair(*m, C("sceMc2ChangeThreadPriority"), {0}, seed++, "mc2 prio 0", stand_ins)) == -2130640874);
    w32(*m, libs6::kMc2Thread, 0x2A);
    CHECK(v0_of(pair(*m, C("sceMc2ChangeThreadPriority"), {5}, seed++, "mc2 prio", stand_ins)) == 0);
    CHECK(last_log().log.back().args[0] == 0x2Au);
    // libpad: the actuator values go to the port's send buffer when the pad is ready
    constexpr u32 kPadTable = 0x96DD10u;
    const u32 sendbuf = kWorld + 0x3800;
    w32(*m, kPadTable + 4, sendbuf);  // port 0, slot 0: the send buffer
    const u8 act[6] = {1, 0xFF, 0, 0, 0, 0};
    std::memcpy(m->at(kWorld + 0x3900), act, 6);
    CHECK(v0_of(pair(*m, C("scePadSetActDirect"), {0, 0, kWorld + 0x3900}, seed++, "pad act", stand_ins)) == 1);
    CHECK(std::memcmp(m->at(sendbuf + 12), act, 6) == 0);
    CHECK(r32(*m, sendbuf + 8) == 6u);
    MESSAGE("pairs " << counts().pairs << ", stopped " << counts().stops);
}

TEST_CASE("game(libs6): _sceMcFatFormat on the battle route's card") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const std::vector<u8> snap = read_snapshot("b_5800");
    auto card = std::make_shared<std::vector<u8>>(route_card("tartarus.ps2"));
    if (snap.size() != EEMemory::kMainRamSize || card->empty()) {
        MESSAGE("SKIP: snapshot b_5800 or the route card not found");
        return;
    }
    copy_from_snapshot(*m, snap, 0x7827D8u, 0x400);    // the init flag, both superblock copies
    copy_from_snapshot(*m, snap, 0x96F100u, 0x100);
    copy_from_snapshot(*m, snap, 0x97B700u, 0xA900u);  // FAT state, entry buffers, write-cluster cache, core sockets
    auto made = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    const Setup setup = [card, made](StandInWorld& w) {
        stand_ins(w);
        auto c = std::make_shared<Card>();
        c->img = *card;
        made->push_back(c);
        install_card(w, c, 1, 0);
        w.si.install(kGetCardSpec, "_sceMcCoreGetCardSpec", [](EEContext& ctx, StandIns&, StandInCall& call) {
            const u32 spec[4] = {512, 16, 16384, 1};
            std::memcpy(gptr(ctx, static_cast<u32>(call.args[1])), spec, 16);
            call.v0 = 1;
        });
    };
    const auto r = pair(*m, C("_sceMcFatFormat"), {0}, 600, "format", setup);
    REQUIRE(made->size() == 2);
    CHECK((*made)[0]->img == (*made)[1]->img);
    CHECK((*made)[0]->ops == (*made)[1]->ops);
   CHECK(std::memcmp((*made)[1]->img.data(), "Sony PS2 Memory Card Format ", 28) == 0);
    CHECK(v0s(r) == 1);  // formatted
    std::size_t writes = 0;
    for (const auto& op : (*made)[1]->ops) writes += std::get<0>(op) == 'w' ? 1 : 0;
    CHECK(writes > 0);
    MESSAGE("format: v0 " << v0s(r) << ", " << (*made)[1]->ops.size() << " card requests, " << writes << " writes");
}

#else

TEST_CASE("game(libs6): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
