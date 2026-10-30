// Slice libs6: 132 small SDK-library functions the game links (0x501128-0x528970), mostly EE runtime plumbing:
// libkernel (start-up crt_init_runtime and its kernel patches through kCopy* syscalls, the top thread, DECI2 and the
// TTY over it, kprintf, the timer-counter and alarm wrappers, TLB / debug handlers), libsif (command handler slots,
// the D-cache write-back, RPC packets, queues and servers, reboot notify), the sceFs file layer (iob table,
// semaphores, the RPC receive interrupt), libcdvd's callback thread and power-off hook, two libpad setters, the sound
// driver's callbacks, libmc2's worker thread, _sceMcFatFormat and core / libdbc helpers, and newlib's reentrancy glue
// (__malloc_lock / unlock, _read_r / _write_r / _sbrk_r).
//
// Every body is p3fes_handgen's (register for register and block for block as the recompiled body: frame, spills,
// $ra links, cycle charges, check points); the readability pass adds a role comment per function, the SDK name a
// misnamed or unnamed function really is in [brackets] (symbols/deltas/libs6.sym), and the named globals of
// game/include/p3fes/game/libs6.h.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs6.h"

namespace p3fes::recomp_gen {
void fn_DIntr_0050d3a0(p3fes::EEContext&);
void fn_DisableDmac_00503d10(p3fes::EEContext&);
void fn_DisableIntc_00503c40(p3fes::EEContext&);
void fn_EIntr_0050d3f0(p3fes::EEContext&);
void fn_ExecPS2_0050d9a0(p3fes::EEContext&);
void fn_GetSystemCallEntry_0050d510(p3fes::EEContext&);
void fn_InitAlarm_0050db38(p3fes::EEContext&);
void fn_InitExecPS2_0050d780(p3fes::EEContext&);
void fn_InitSystemCallTableAddress_0050d548(p3fes::EEContext&);
void fn_InitTLB32MB_0050ce40(p3fes::EEContext&);
void fn_InitTLBFunctions_0050cc78(p3fes::EEContext&);
void fn_InitTLB_0050ce00(p3fes::EEContext&);
void fn_InitThread_00503f38(p3fes::EEContext&);
void fn_InitTimer_0050dcb0(p3fes::EEContext&);
void fn_InvalidDCache_00503b98(p3fes::EEContext&);
void fn_PatchIsNeeded_0050d718(p3fes::EEContext&);
void fn_PowerOffCB_0050fbc0(p3fes::EEContext&);
void fn_QueryIntrContext_00503c30(p3fes::EEContext&);
void fn_QueueInit_00504678(p3fes::EEContext&);
void fn_QueuePeekWriteDone_005046a0(p3fes::EEContext&);
void fn_ReleaseTimerAlarm_0050f2b0(p3fes::EEContext&);
void fn_SetArg_0050d880(p3fes::EEContext&);
void fn_SetDebugHandler_0050cb88(p3fes::EEContext&);
void fn_SetTLBEntry_0050cd70(p3fes::EEContext&);
void fn_SetTLBHandler_0050cb28(p3fes::EEContext&);
void fn_SetTimerAlarm_0050f090(p3fes::EEContext&);
void fn_StartThread_005042a0(p3fes::EEContext&);
void fn_StartTimerSystemTime_0050def0(p3fes::EEContext&);
void fn_SyncDCache_00503a58(p3fes::EEContext&);
void fn_SyncDmaForRead_0051ade0(p3fes::EEContext&);
void fn_SyncDma_0051ad10(p3fes::EEContext&);
void fn___malloc_lock_005214c8(p3fes::EEContext&);
void fn___malloc_unlock_00521520(p3fes::EEContext&);
void fn__read_r_00522f38(p3fes::EEContext&);
void fn__request_call_005071a0(p3fes::EEContext&);
void fn__sbrk_r_00523930(p3fes::EEContext&);
void fn__sceCallCode_00509758(p3fes::EEContext&);
void fn__sceCdSC_005103b0(p3fes::EEContext&);
void fn__sceCd_Poff_Intr_0050fb68(p3fes::EEContext&);
void fn__sceCd_cbLoop_0050f738(p3fes::EEContext&);
void fn__sceCd_cd_callback_0050f698(p3fes::EEContext&);
void fn__sceChangeThreadPriority_00502ff0(p3fes::EEContext&);
void fn__sceCopy_0050cc10(p3fes::EEContext&);
void fn__sceCopy_0_0050d478(p3fes::EEContext&);
void fn__sceCopy_1_0050d6c0(p3fes::EEContext&);
void fn__sceCopy_2_0050d830(p3fes::EEContext&);
void fn__sceCreateSema_00503160(p3fes::EEContext&);
void fn__sceCreateThread_00502f60(p3fes::EEContext&);
void fn__sceDeci2Call_00503590(p3fes::EEContext&);
void fn__sceDeleteSema_00503170(p3fes::EEContext&);
void fn__sceDeleteThread_00502f70(p3fes::EEContext&);
void fn__sceExitDeleteThread_00502fa0(p3fes::EEContext&);
void fn__sceFindAddress_0050d500(p3fes::EEContext&);
void fn__sceFlushCache_005033e0(p3fes::EEContext&);
void fn__sceFsIobSemaMK_00507960(p3fes::EEContext&);
void fn__sceFsSemInit_00507ff0(p3fes::EEContext&);
void fn__sceFsSigSema_00508078(p3fes::EEContext&);
void fn__sceFsWaitS_00508048(p3fes::EEContext&);
void fn__sceFs_Rcv_Intr_00507c38(p3fes::EEContext&);
void fn__sceGetEntryAddress_0050cc58(p3fes::EEContext&);
void fn__sceGetEntryAddress_0_0050d708(p3fes::EEContext&);
void fn__sceGetMemorySize_005035c0(p3fes::EEContext&);
void fn__sceGetOsdConfigParam_00503210(p3fes::EEContext&);
void fn__sceGetThreadId_00503050(p3fes::EEContext&);
void fn__sceIDC_00503af0(p3fes::EEContext&);
void fn__sceMcCoreChangeSocketTypeDbc2Mc_0051c2e8(p3fes::EEContext&);
void fn__sceMcCoreEnd_0051aef8(p3fes::EEContext&);
void fn__sceMcCoreGetConnection_0051c0c0(p3fes::EEContext&);
void fn__sceMcCoreInit_0051ae68(p3fes::EEContext&);
void fn__sceMcCoreReadClock_0051b5f0(p3fes::EEContext&);
void fn__sceMcCoreSetWriteBackHole_0051af70(p3fes::EEContext&);
void fn__sceMcCoreWriteSameData_0051ba88(p3fes::EEContext&);
void fn__sceMcFatChDir_00519728(p3fes::EEContext&);
void fn__sceMcFatCreateFile_00517cd8(p3fes::EEContext&);
void fn__sceMcFatDeleteFile_005194f8(p3fes::EEContext&);
void fn__sceMcFatFlushFatCache_00515588(p3fes::EEContext&);
void fn__sceMcFatFormat_00516118(p3fes::EEContext&);
void fn__sceMcFatGetDir_00519850(p3fes::EEContext&);
void fn__sceMcFatGetEntSpace_0051a078(p3fes::EEContext&);
void fn__sceMcFatGetFreeClust_00515910(p3fes::EEContext&);
void fn__sceMcFatGetInfo_00515d80(p3fes::EEContext&);
void fn__sceMcFatReadFastFile_00518470(p3fes::EEContext&);
void fn__sceMcFatReadFile_00518268(p3fes::EEContext&);
void fn__sceMcFatRename_00519ef8(p3fes::EEContext&);
void fn__sceMcFatSearchFile_00517be8(p3fes::EEContext&);
void fn__sceMcFatSetAttr_00519d70(p3fes::EEContext&);
void fn__sceMcFatUnFormat_00516a48(p3fes::EEContext&);
void fn__sceMcFatWriteFastFile_00518e70(p3fes::EEContext&);
void fn__sceMcFatWriteFatData_005157e0(p3fes::EEContext&);
void fn__sceMcFatWriteFile_005187c0(p3fes::EEContext&);
void fn__sceMcpFlushCache_0051a498(p3fes::EEContext&);
void fn__sceMcpGetCardSpec_0051a180(p3fes::EEContext&);
void fn__sceMcpIsSpeckOutBlock_0051ab08(p3fes::EEContext&);
void fn__sceMcpIsSpeckOutClust_0051ab50(p3fes::EEContext&);
void fn__sceMcpMakeSpecoutBlock_0051ab98(p3fes::EEContext&);
void fn__sceMcpReadSysInfo_0051a1e0(p3fes::EEContext&);
void fn__sceMcpWriteClust_0051a458(p3fes::EEContext&);
void fn__sceMcpWriteSysInfo_0051a2f8(p3fes::EEContext&);
void fn__sceMcpWriteUserClust_0051aa90(p3fes::EEContext&);
void fn__sceMpegDefaultRestartDMA_00501150(p3fes::EEContext&);
void fn__sceMpegDefaultStopDMA_00501128(p3fes::EEContext&);
void fn__sceRemoveDmacHandler_00502e90(p3fes::EEContext&);
void fn__sceRemoveIntcHandler_00502e60(p3fes::EEContext&);
void fn__sceRotateThreadReadyQueue_00503010(p3fes::EEContext&);
void fn__sceRpcFreePacket_00506b18(p3fes::EEContext&);
void fn__sceRpcGetFPacket_00506b38(p3fes::EEContext&);
void fn__sceRpcGetPacket_00506a70(p3fes::EEContext&);
void fn__sceSDC_005039b0(p3fes::EEContext&);
void fn__sceSetOsdConfigParam_00503200(p3fes::EEContext&);
void fn__sceSetSyscall_0050cc68(p3fes::EEContext&);
void fn__sceSetSyscall_0_0050d648(p3fes::EEContext&);
void fn__sceSetSyscall_1_0050d6b0(p3fes::EEContext&);
void fn__sceSetSyscall_2_0050d870(p3fes::EEContext&);
void fn__sceSetVCommonHandler_00502e20(p3fes::EEContext&);
void fn__sceSetVTLBRefillHandler_00502e10(p3fes::EEContext&);
void fn__sceSignalSema_00503180(p3fes::EEContext&);
void fn__sceSnprintf_00504f48(p3fes::EEContext&);
void fn__sceSuspendThread_005030d0(p3fes::EEContext&);
void fn__sceTerminateThread_00502fb0(p3fes::EEContext&);
void fn__sceWaitSema_005031a0(p3fes::EEContext&);
void fn__sceWakeupThread_00503090(p3fes::EEContext&);
void fn__sce_ExecPS2_00502db0(p3fes::EEContext&);
void fn__sce_InitTLB_005035d0(p3fes::EEContext&);
void fn__sce_SetTLBEntry_0050cd60(p3fes::EEContext&);
void fn__sce_iDisableDmac_00502f30(p3fes::EEContext&);
void fn__sce_iDisableIntc_00502f10(p3fes::EEContext&);
void fn__sce_iEnableDmac_00502f20(p3fes::EEContext&);
void fn__sce_iEnableIntc_00502f00(p3fes::EEContext&);
void fn__sceiChangeThreadPriority_00503000(p3fes::EEContext&);
void fn__sceiSignalSema_00503190(p3fes::EEContext&);
void fn__sdrCB_00512ff0(p3fes::EEContext&);
void fn__search_svdata_00506ef0(p3fes::EEContext&);
void fn__send_to_iop_00511478(p3fes::EEContext&);
void fn__write_r_00528970(p3fes::EEContext&);
void fn_basic_thread_005145f8(p3fes::EEContext&);
void fn_cmd_sem_init_0050f960(p3fes::EEContext&);
void fn_crt_init_runtime_0050d658(p3fes::EEContext&);
void fn_get_iob_00507bc8(p3fes::EEContext&);
void fn_iDisableDmac_00503e40(p3fes::EEContext&);
void fn_iDisableIntc_00503e00(p3fes::EEContext&);
void fn_iEnableDmac_00503e20(p3fes::EEContext&);
void fn_iEnableIntc_00503de0(p3fes::EEContext&);
void fn_iInvalidDCache_00503c18(p3fes::EEContext&);
void fn_iRotateThreadReadyQueue_005040c0(p3fes::EEContext&);
void fn_iSyncDCache_00503ad8(p3fes::EEContext&);
void fn_iWakeupThread_00504028(p3fes::EEContext&);
void fn_kCopy_0050cc20(p3fes::EEContext&);
void fn_kCopy_0_0050d488(p3fes::EEContext&);
void fn_kCopy_1_0050d6d0(p3fes::EEContext&);
void fn_kCopy_3_0050daf0(p3fes::EEContext&);
void fn_kFindAddress_0050d4c0(p3fes::EEContext&);
void fn_kprintf_00505ec8(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_new_iob_00507a50(p3fes::EEContext&);
void fn_read_005037a8(p3fes::EEContext&);
void fn_sbrk_00503860(p3fes::EEContext&);
void fn_sceCdChgSys_00511110(p3fes::EEContext&);
void fn_sceCdInitEeCB_0050f808(p3fes::EEContext&);
void fn_sceCdPOffCallback_0050fae8(p3fes::EEContext&);
void fn_sceChdir_0050a868(p3fes::EEContext&);
void fn_sceDbcDeleteSocket_0051c8a0(p3fes::EEContext&);
void fn_sceDbcEnd_0051c658(p3fes::EEContext&);
void fn_sceDbcGetConnection_0051cad0(p3fes::EEContext&);
void fn_sceDbcSearchPortSpecific_0051cdd8(p3fes::EEContext&);
void fn_sceDbcSendData3_0051d308(p3fes::EEContext&);
void fn_sceDeci2Close_00504488(p3fes::EEContext&);
void fn_sceDeci2ExLock_00504600(p3fes::EEContext&);
void fn_sceDeci2ExRecv_00504560(p3fes::EEContext&);
void fn_sceDeci2ExReqSend_005045d0(p3fes::EEContext&);
void fn_sceDeci2ExSend_00504598(p3fes::EEContext&);
void fn_sceDeci2ExUnLock_00504628(p3fes::EEContext&);
void fn_sceDeci2GrpClose_00504538(p3fes::EEContext&);
void fn_sceDeci2GrpOpen_00504508(p3fes::EEContext&);
void fn_sceDeci2Open_00504440(p3fes::EEContext&);
void fn_sceDeci2Poll_005044e0(p3fes::EEContext&);
void fn_sceDeci2ReqSend_005044b0(p3fes::EEContext&);
void fn_sceDelDrv_00509eb0(p3fes::EEContext&);
void fn_sceDopen_00509ed0(p3fes::EEContext&);
void fn_sceFsInit_00508170(p3fes::EEContext&);
void fn_sceFsReset_00508408(p3fes::EEContext&);
void fn_sceIpuRestartDMA_005028d8(p3fes::EEContext&);
void fn_sceIpuStopDMA_005027f0(p3fes::EEContext&);
void fn_sceMc2ChangeThreadPriority_00513528(p3fes::EEContext&);
void fn_sceMc2End_00513290(p3fes::EEContext&);
void fn_sceMc2GetDirAllAsync_005138b8(p3fes::EEContext&);
void fn_sceMc2SearchSocket_00513478(p3fes::EEContext&);
void fn_sceMc2Sync_00514928(p3fes::EEContext&);
void fn_sceMc2iChangeThreadPriority_00513560(p3fes::EEContext&);
void fn_scePadGetDmaStr_00511830(p3fes::EEContext&);
void fn_scePadSetActDirect_00512070(p3fes::EEContext&);
void fn_scePadSetReqState_00511b08(p3fes::EEContext&);
void fn_scePowerOffHandler_00508088(p3fes::EEContext&);
void fn_scePrintf_00505e48(p3fes::EEContext&);
void fn_sceRemove_00509908(p3fes::EEContext&);
void fn_sceRmdir_00509ae0(p3fes::EEContext&);
void fn_sceSdCallBack_005129a0(p3fes::EEContext&);
void fn_sceSifAddRebootNotifyHandler_0050f478(p3fes::EEContext&);
void fn_sceSifCheckStatRpc_00507430(p3fes::EEContext&);
void fn_sceSifExecNotifyHandler_0050f588(p3fes::EEContext&);
void fn_sceSifExitRpc_00506a48(p3fes::EEContext&);
void fn_sceSifGetNextRequest_00507700(p3fes::EEContext&);
void fn_sceSifLoadFileReset_0050bc78(p3fes::EEContext&);
void fn_sceSifRegisterRpc_00507508(p3fes::EEContext&);
void fn_sceSifRemoveRebootNotifyHandler_0050f530(p3fes::EEContext&);
void fn_sceSifRemoveRpcQueue_00507670(p3fes::EEContext&);
void fn_sceSifRemoveRpc_005075d8(p3fes::EEContext&);
void fn_sceSifSendCmd_005064a8(p3fes::EEContext&);
void fn_sceSifSetRebootNotifyBuffer_0050f3f8(p3fes::EEContext&);
void fn_sceSifSetRpcQueue_00507470(p3fes::EEContext&);
void fn_sceSifWriteBackDCache_00506670(p3fes::EEContext&);
void fn_sceSkQuit_0051dad8(p3fes::EEContext&);
void fn_sceTtyHandler_00504720(p3fes::EEContext&);
void fn_sceTtyInit_00504b00(p3fes::EEContext&);
void fn_sceTtyRead_00504a30(p3fes::EEContext&);
void fn_sceTtyWrite_005048b8(p3fes::EEContext&);
void fn_sceUmount_0050acb8(p3fes::EEContext&);
void fn_sceVprintf_00505dd8(p3fes::EEContext&);
void fn_strcat_00523e68(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);
void fn_strncmp_00524670(p3fes::EEContext&);
void fn_sub_5063C8_005063c8(p3fes::EEContext&);
void fn_sub_506430_00506430(p3fes::EEContext&);
void fn_sub_5064F8_005064f8(p3fes::EEContext&);
void fn_sub_506630_00506630(p3fes::EEContext&);
void fn_sub_5067F8_005067f8(p3fes::EEContext&);
void fn_sub_50D37C_0050d37c(p3fes::EEContext&);
void fn_sub_50D998_0050d998(p3fes::EEContext&);
void fn_sub_50DC80_0050dc80(p3fes::EEContext&);
void fn_sub_50DC90_0050dc90(p3fes::EEContext&);
void fn_sub_50DE08_0050de08(p3fes::EEContext&);
void fn_sub_50E508_0050e508(p3fes::EEContext&);
void fn_sub_50E5D8_0050e5d8(p3fes::EEContext&);
void fn_sub_50E648_0050e648(p3fes::EEContext&);
void fn_sub_50E690_0050e690(p3fes::EEContext&);
void fn_sub_50E750_0050e750(p3fes::EEContext&);
void fn_sub_50E7A0_0050e7a0(p3fes::EEContext&);
void fn_sub_50E7F0_0050e7f0(p3fes::EEContext&);
void fn_sub_50E850_0050e850(p3fes::EEContext&);
void fn_sub_50E900_0050e900(p3fes::EEContext&);
void fn_sub_50E950_0050e950(p3fes::EEContext&);
void fn_sub_50EA30_0050ea30(p3fes::EEContext&);
void fn_sub_50EA80_0050ea80(p3fes::EEContext&);
void fn_sub_50EB50_0050eb50(p3fes::EEContext&);
void fn_sub_50EB98_0050eb98(p3fes::EEContext&);
void fn_sub_50EBE8_0050ebe8(p3fes::EEContext&);
void fn_sub_50EC58_0050ec58(p3fes::EEContext&);
void fn_sub_50ECA8_0050eca8(p3fes::EEContext&);
void fn_sub_50EDB8_0050edb8(p3fes::EEContext&);
void fn_supplement_crt0_0050d408(p3fes::EEContext&);
void fn_topThread_00503e60(p3fes::EEContext&);
void fn_use_iob_cnt_005079d0(p3fes::EEContext&);
void fn_write_00503728(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x00501128 _sceMpegDefaultStopDMA -- 36 bytes; frame 0x10: ra sp+0x0
// libmpeg's default stop-DMA callback: sceIpuStopDMA on the decoder's IPU state ($a0->+64, +104); returns 1.
void _sceMpegDefaultStopDMA(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00501128
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 64);
    a0 = addiu(a0, 104);
    jal(ctx, 0x501134u, gen::fn_sceIpuStopDMA_005027f0);
    ld(ra, sp, 0x0);
    v0 = 1;
    sp = addiu(sp, 0x10);
}

// 0x00501150 _sceMpegDefaultRestartDMA -- 36 bytes; frame 0x10: ra sp+0x0
// libmpeg's default restart-DMA callback: sceIpuRestartDMA on the same IPU state; returns 1.
void _sceMpegDefaultRestartDMA(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00501150
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 64);
    a0 = addiu(a0, 104);
    jal(ctx, 0x50115Cu, gen::fn_sceIpuRestartDMA_005028d8);
    ld(ra, sp, 0x0);
    v0 = 1;
    sp = addiu(sp, 0x10);
}

// 0x00503728 write -- 124 bytes; frame 0x40: s2 sp+0x20, s1 sp+0x10, ra sp+0x30, s0 sp+0x0
// newlib write() for the console: fd 1 or 2 go to sceTtyWrite (sceTtyInit once, flag 0x77F490); any other fd -1.
void write(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00503728
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    a0 = addiu(a0, -1);
    sd(s2, sp, 0x20);
    a0 = sltiu(a0, 2);
    sd(s1, sp, 0x10);
    s2 = a2;
    sd(ra, sp, 0x30);
    s1 = a1;
    sd(s0, sp, 0x0);
    if (a0 != 0) {
        // 0x00503750
        charge(ctx, 4);
        s0 = 0x780000;
        lw(v0, s0, libs6::lo(libs6::kTtyReady));  // 0x77F490
        a0 = s1;
        if (v0 == 0) {
            // 0x00503760
            charge(ctx, 4);
            jal(ctx, 0x503760u, gen::fn_sceTtyInit_00504b00);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = 1;
            if (cc) {
                goto L_00503788;
            }
            // 0x00503770
            charge(ctx, 2);
            sw(v0, s0, -2928);
            a0 = s1;
            goto L_00503778;
        }
    L_00503778:
        charge(ctx, 4);
        a1 = s2;
        jal(ctx, 0x503778u, gen::fn_sceTtyWrite_005048b8);
        ld(ra, sp, 0x30);
        // 0x00503790 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s2, sp, 0x20);
        ld(s1, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_00503788:
    charge(ctx, 2);
    v0 = si(-1);
    ld(ra, sp, 0x30);
    // 0x00503790 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x005037A8 read -- 116 bytes; frame 0x40: s2 sp+0x20, s1 sp+0x10, ra sp+0x30, s0 sp+0x0
// newlib read() for the console: fd 0 goes to sceTtyRead (sceTtyInit once, flag 0x77F490); any other fd -1.
void read(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005037a8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x10);
    s2 = a2;
    sd(ra, sp, 0x30);
    s1 = a1;
    sd(s0, sp, 0x0);
    if (a0 == 0) {
        // 0x005037c8
        charge(ctx, 4);
        s0 = 0x780000;
        lw(v0, s0, libs6::lo(libs6::kTtyReady));  // 0x77F490
        a0 = s1;
        if (v0 == 0) {
            // 0x005037d8
            charge(ctx, 4);
            jal(ctx, 0x5037D8u, gen::fn_sceTtyInit_00504b00);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = 1;
            if (cc) {
                goto L_00503800;
            }
            // 0x005037e8
            charge(ctx, 2);
            sw(v0, s0, -2928);
            a0 = s1;
            goto L_005037f0;
        }
    L_005037f0:
        charge(ctx, 4);
        a1 = s2;
        jal(ctx, 0x5037F0u, gen::fn_sceTtyRead_00504a30);
        ld(ra, sp, 0x30);
        // 0x00503808 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s2, sp, 0x20);
        ld(s1, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_00503800:
    charge(ctx, 2);
    v0 = si(-1);
    ld(ra, sp, 0x30);
    // 0x00503808 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00503AD8 iSyncDCache -- 20 bytes; leaf frame (no stack)
// Interrupt-context data cache write-back: both bounds aligned down to 64 bytes, then the _sceSDC loop.
void iSyncDCache(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00503ad8
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = lui(0xFFFF);
    v0 = v0 | 0xFFC0;
    a1 = a1 & v0;
    a0 = a0 & v0;
    gen::fn__sceSDC_005039b0(ctx);  // tail call
}

// 0x00503C18 iInvalidDCache -- 20 bytes; leaf frame (no stack)
// Interrupt-context data cache invalidate: both bounds aligned down to 64 bytes, then the _sceIDC loop.
void iInvalidDCache(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00503c18
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = lui(0xFFFF);
    v0 = v0 | 0xFFC0;
    a1 = a1 & v0;
    a0 = a0 & v0;
    gen::fn__sceIDC_00503af0(ctx);  // tail call
}

// 0x00503DE0 iEnableIntc -- 32 bytes; frame 0x10: ra sp+0x0
// Interrupt-context INTC enable (the kernel call, then a sync).
void iEnableIntc(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00503de0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x503DE8u, gen::fn__sce_iEnableIntc_00502f00);
    sync(ctx, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00503E00 iDisableIntc -- 32 bytes; frame 0x10: ra sp+0x0
// Interrupt-context INTC disable (the kernel call, then a sync).
void iDisableIntc(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00503e00
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x503E08u, gen::fn__sce_iDisableIntc_00502f10);
    sync(ctx, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00503E20 iEnableDmac -- 32 bytes; frame 0x10: ra sp+0x0
// Interrupt-context DMAC enable (the kernel call, then a sync).
void iEnableDmac(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00503e20
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x503E28u, gen::fn__sce_iEnableDmac_00502f20);
    sync(ctx, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00503E40 iDisableDmac -- 32 bytes; frame 0x10: ra sp+0x0
// Interrupt-context DMAC disable (the kernel call, then a sync).
void iDisableDmac(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00503e40
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x503E48u, gen::fn__sce_iDisableDmac_00502f30);
    sync(ctx, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00503E60 topThread -- 216 bytes; frame 0x80: s1 sp+0x10, s6 sp+0x60, s5 sp+0x50, s4 sp+0x40, s3 sp+0x30, s2 sp+0x20, s0 sp+0x0, ra sp+0x70
// libkernel's helper thread: waits on its semaphore, pops a 2-byte request (kind, thread id) from the 512-entry
// ring at $a0 and runs it: 1 rotate the ready queue, 0 wake up, 2 suspend; another kind prints the internal-error
// message. Never returns.
void topThread(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00503e60
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(s1, sp, 0x10);
    s1 = a0;
    sd(s6, sp, 0x60);
    sd(s5, sp, 0x50);
    s6 = 0x960000;
    sd(s4, sp, 0x40);
    s5 = 0x7C0000;
    sd(s3, sp, 0x30);
    s4 = 1;
    sd(s2, sp, 0x20);
    s3 = 2;
    sd(s0, sp, 0x0);
    s2 = addiu(s1, 8);
    sd(ra, sp, 0x70);
    s0 = addiu(s1, 9);
    for (;;) {
        // 0x00503ea0
        charge(ctx, 12);
        link(ctx, 0x503EA0u);  // $ra first: the delay slot below depends on it
        lw(a0, s6, 24832);
        call(ctx, gen::fn__sceWaitSema_005031a0);
        lw(v1, s1, 0);
        v1 = v1 & 0x1FF;
        a0 = addiu(v1, 1);
        v1 = sll(v1, 1);
        sw(a0, s1, 0);
        v0 = addu(s2, v1);
        a2 = addu(s0, v1);
        lbu(v0, v0, 0);
        a1 = slti(v0, 2);
        if (v0 == s4) {
            // 0x00503f08
            charge(ctx, 4);
            link(ctx, 0x503F08u);  // $ra first: the delay slot below depends on it
            lbu(a0, a2, 0);
            call(ctx, gen::fn__sceRotateThreadReadyQueue_00503010);
            backedge(ctx);
            continue;
        }
        // 0x00503ed0
        charge(ctx, 2);
        a0 = addiu(s5, -9632);
        if (a1 != 0) {
            // 0x00503ed8
            charge(ctx, 2);
            v1 = a2;
            if (v0 != 0) {
                // 0x00503ee0
                charge(ctx, 2);
                goto L_00503f28;
            }
            // 0x00503ef8
            charge(ctx, 4);
            link(ctx, 0x503EF8u);  // $ra first: the delay slot below depends on it
            lbu(a0, v1, 0);
            call(ctx, gen::fn__sceWakeupThread_00503090);
            backedge(ctx);
            continue;
        }
        // 0x00503ee8
        charge(ctx, 2);
        v1 = addu(s0, v1);
        if (v0 == s3) {
            // 0x00503f18
            charge(ctx, 4);
            link(ctx, 0x503F18u);  // $ra first: the delay slot below depends on it
            lbu(a0, v1, 0);
            call(ctx, gen::fn__sceSuspendThread_005030d0);
            backedge(ctx);
            continue;
        }
        // 0x00503ef0
        charge(ctx, 2);
    L_00503f28:
        charge(ctx, 4);
        jal(ctx, 0x503F28u, gen::fn_kprintf_00505ec8);
        backedge(ctx);
    }
}

// 0x00503F38 InitThread -- 236 bytes; frame 0x90: s0 sp+0x50, ra sp+0x80, s2 sp+0x70, s1 sp+0x60
// Create and start the top thread once ("SceKerneltopThread", priority 0, 1 KiB stack at 0x965D00) with its
// semaphore and request ring at 0x966108, then raise the caller to priority 1; returns the thread id or -1.
void InitThread(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00503f38
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(s0, sp, 0x50);
    s0 = 0x780000;
    sd(ra, sp, 0x80);
    lw(v0, s0, libs6::lo(libs6::kTopThreadId));  // 0x77F498
    sd(s2, sp, 0x70);
    sd(s1, sp, 0x60);
    if (i64(v0) <= 0) {
        // 0x00503f58
        charge(ctx, 11);
        v0 = 0x7C0000;
        v1 = 255;
        s1 = addiu(v0, -9592);  // "SceKerneltopThread"
        sw(v1, sp, 0x34);
        sw(zero, sp, 0x38);
        a0 = addiu(sp, 0x30);
        sw(s1, sp, 0x44);
        s2 = 0x960000;
        jal(ctx, 0x503F74u, gen::fn__sceCreateSema_00503160);
        sw(v0, s2, libs6::lo(libs6::kTopThreadSema));  // 0x966100
        if (i64(v0) < 0) {
            goto L_00503fd4;
        }
        // 0x00503f84
        charge(ctx, 18);
        v0 = 0x500000;
        v1 = 0x960000;
        a1 = 0x7D0000;
        v0 = addiu(v0, 15968);  // &topThread
        v1 = addiu(v1, 23808);  // &0x965D00
        a1 = addiu(a1, 11504);  // &gp_base
        a2 = 1024;
        sw(v0, sp, 0x4);
        sw(v1, sp, 0x8);
        a0 = sp;
        sw(a2, sp, 0xC);
        sw(a1, sp, 0x10);
        sw(s1, sp, 0x20);
        link(ctx, 0x503FB8u);  // $ra first: the delay slot below depends on it
        sw(zero, sp, 0x14);
        call(ctx, gen::fn__sceCreateThread_00502f60);
        a0 = v0;
        sw(a0, s0, -2920);
        if (i64(a0) < 0) {
            // 0x00503fcc
            charge(ctx, 2);
            link(ctx, 0x503FCCu);  // $ra first: the delay slot below depends on it
            lw(a0, s2, 24832);
            call(ctx, gen::fn__sceDeleteSema_00503170);
            goto L_00503fd4;
        }
        // 0x00503fdc
        charge(ctx, 12);
        v0 = 0x960000;
        v1 = addiu(v0, 24840);  // &0x966108
        sw(zero, v0, 24840);  // 0x966108
        a1 = v1;
        link(ctx, 0x503FECu);  // $ra first: the delay slot below depends on it
        sw(zero, v1, 4);
        call(ctx, gen::fn_StartThread_005042a0);
        jal(ctx, 0x503FF4u, gen::fn__sceGetThreadId_00503050);
        a0 = v0;
        a1 = 1;
        jal(ctx, 0x504000u, gen::fn__sceChangeThreadPriority_00502ff0);
        lw(v0, s0, -2920);
        // 0x0050400c (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x80);
        ld(s2, sp, 0x70);
        ld(s1, sp, 0x60);
        ld(s0, sp, 0x50);
        sp = addiu(sp, 0x90);
        return;
    }
L_00503fd4:
    charge(ctx, 2);
    v0 = si(-1);
    // 0x0050400c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x80);
    ld(s2, sp, 0x70);
    ld(s1, sp, 0x60);
    ld(s0, sp, 0x50);
    sp = addiu(sp, 0x90);
}

// 0x005040C0 iRotateThreadReadyQueue -- 124 bytes; frame 0x20: s0 sp+0x0, ra sp+0x10
// Interrupt-context ready-queue rotation: queues request (1, priority) to the top thread and signals it; priority
// must be < 128 and the thread must exist (else -1).
void iRotateThreadReadyQueue(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005040c0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    v0 = sltiu(s0, 128);
    sd(ra, sp, 0x10);
    if (v0 != 0) {
        // 0x005040d8
        charge(ctx, 4);
        v0 = 0x780000;
        lw(v1, v0, libs6::lo(libs6::kTopThreadId));  // 0x77F498
        cc = v1 != 0;  // the condition, before the delay slot changes it
        v1 = 0x960000;
        if (!cc) {
            goto L_005040e8;
        }
        // 0x005040f0
        charge(ctx, 15);
        a1 = 0x960000;
        v1 = addiu(v1, 24840);
        lw(a0, a1, libs6::lo(libs6::kTopThreadSema));  // 0x966100
        lw(v0, v1, 4);
        a3 = 1;
        v0 = v0 & 0x1FF;
        a2 = sll(v0, 1);
        v0 = addiu(v0, 1);
        a1 = addu(v1, a2);
        sw(v0, v1, 4);
        sb(a3, a1, 8);
        v1 = a1;
        link(ctx, 0x504120u);  // $ra first: the delay slot below depends on it
        sb(s0, v1, 9);
        call(ctx, gen::fn__sceiSignalSema_00503190);
        v0 = s0;
        // 0x0050412c (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
L_005040e8:
    charge(ctx, 2);
    v0 = si(-1);
    // 0x0050412c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00504440 sceDeci2Open -- 68 bytes; frame 0x20: ra sp+0x10
// DECI2 open: (protocol, opaque, handler) plus the reply area 0x20966510 (uncached) through _sceDeci2Call 1.
void sceDeci2Open(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00504440
    enter(ctx, 17);  // entry check point + this block's cycles
    v0 = 0x960000;
    sp = addiu(sp, -0x20);
    v1 = 0x20000000;
    v0 = addiu(v0, 25872);  // &0x966510
    a0 = a0 & 0xFFFF;
    v0 = v0 | v1;
    sw(a1, sp, 0x4);
    sw(a0, sp, 0x0);
    a1 = sp;
    sd(ra, sp, 0x10);
    a0 = 1;
    sw(a2, sp, 0x8);
    link(ctx, 0x504470u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0xC);
    call(ctx, gen::fn__sceDeci2Call_00503590);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00504488 sceDeci2Close -- 36 bytes; frame 0x20: ra sp+0x10
// DECI2 close (socket) through _sceDeci2Call 2.
void sceDeci2Close(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00504488
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sw(a0, sp, 0x0);
    a1 = sp;
    sd(ra, sp, 0x10);
    a0 = 2;
    jal(ctx, 0x504498u, gen::fn__sceDeci2Call_00503590);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x005044B0 sceDeci2ReqSend -- 48 bytes; frame 0x20: ra sp+0x10
// DECI2 send request (socket, destination byte) through _sceDeci2Call 3.
void sceDeci2ReqSend(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005044b0
    enter(ctx, 12);  // entry check point + this block's cycles
    a1 = sll(a1, 24);
    sp = addiu(sp, -0x20);
    a1 = sra(a1, 24);
    sw(a0, sp, 0x0);
    sw(a1, sp, 0x4);
    a0 = 3;
    sd(ra, sp, 0x10);
    a1 = sp;
    jal(ctx, 0x5044CCu, gen::fn__sceDeci2Call_00503590);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x005044E0 sceDeci2Poll -- 36 bytes; frame 0x20: ra sp+0x10
// DECI2 poll (socket) through _sceDeci2Call 4.
void sceDeci2Poll(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005044e0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sw(a0, sp, 0x0);
    a1 = sp;
    sd(ra, sp, 0x10);
    a0 = 4;
    jal(ctx, 0x5044F0u, gen::fn__sceDeci2Call_00503590);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00504508 sceDeci2GrpOpen -- 48 bytes; frame 0x30: ra sp+0x20
// DECI2 group open (group byte, opaque, handler) through _sceDeci2Call 32.
void sceDeci2GrpOpen(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00504508
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    a0 = a0 & 0xFF;
    sw(a1, sp, 0x4);
    sw(a0, sp, 0x0);
    a1 = sp;
    sd(ra, sp, 0x20);
    a0 = 32;
    link(ctx, 0x504524u);  // $ra first: the delay slot below depends on it
    sw(a2, sp, 0x8);
    call(ctx, gen::fn__sceDeci2Call_00503590);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00504538 sceDeci2GrpClose -- 36 bytes; frame 0x20: ra sp+0x10
// DECI2 group close through _sceDeci2Call 33.
void sceDeci2GrpClose(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00504538
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sw(a0, sp, 0x0);
    a1 = sp;
    sd(ra, sp, 0x10);
    a0 = 33;
    jal(ctx, 0x504548u, gen::fn__sceDeci2Call_00503590);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00504560 sceDeci2ExRecv -- 52 bytes; frame 0x20: ra sp+0x10
// DECI2 receive into a buffer (socket, address, 16-bit length) through _sceDeci2Call -5.
void sceDeci2ExRecv(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00504560
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = a1;
    a2 = a2 & 0xFFFF;
    sw(a0, sp, 0x0);
    sd(ra, sp, 0x10);
    a1 = sp;
    sw(v0, sp, 0x4);
    a0 = si(-5);
    link(ctx, 0x504580u);  // $ra first: the delay slot below depends on it
    sw(a2, sp, 0x8);
    call(ctx, gen::fn__sceDeci2Call_00503590);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00504598 sceDeci2ExSend -- 52 bytes; frame 0x20: ra sp+0x10
// DECI2 send from a buffer (socket, address, 16-bit length) through _sceDeci2Call -6.
void sceDeci2ExSend(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00504598
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = a1;
    a2 = a2 & 0xFFFF;
    sw(a0, sp, 0x0);
    sd(ra, sp, 0x10);
    a1 = sp;
    sw(v0, sp, 0x4);
    a0 = si(-6);
    link(ctx, 0x5045B8u);  // $ra first: the delay slot below depends on it
    sw(a2, sp, 0x8);
    call(ctx, gen::fn__sceDeci2Call_00503590);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x005045D0 sceDeci2ExReqSend -- 48 bytes; frame 0x20: ra sp+0x10
// DECI2 send request, extended form, through _sceDeci2Call -7.
void sceDeci2ExReqSend(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005045d0
    enter(ctx, 12);  // entry check point + this block's cycles
    a1 = sll(a1, 24);
    sp = addiu(sp, -0x20);
    a1 = sra(a1, 24);
    sw(a0, sp, 0x0);
    sw(a1, sp, 0x4);
    a0 = si(-7);
    sd(ra, sp, 0x10);
    a1 = sp;
    jal(ctx, 0x5045ECu, gen::fn__sceDeci2Call_00503590);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00504600 sceDeci2ExLock -- 36 bytes; frame 0x20: ra sp+0x10
// DECI2 lock (socket) through _sceDeci2Call -8.
void sceDeci2ExLock(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00504600
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sw(a0, sp, 0x0);
    a1 = sp;
    sd(ra, sp, 0x10);
    a0 = si(-8);
    jal(ctx, 0x504610u, gen::fn__sceDeci2Call_00503590);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00504628 sceDeci2ExUnLock -- 36 bytes; frame 0x20: ra sp+0x10
// DECI2 unlock (socket) through _sceDeci2Call -9.
void sceDeci2ExUnLock(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00504628
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sw(a0, sp, 0x0);
    a1 = sp;
    sd(ra, sp, 0x10);
    a0 = si(-9);
    jal(ctx, 0x504638u, gen::fn__sceDeci2Call_00503590);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00504720 sceTtyHandler -- 404 bytes; frame 0x40: s1 sp+0x10, s0 sp+0x0, ra sp+0x30, s2 sp+0x20
// The TTY's DECI2 event handler ($a0 event, $a1 length, $a2 the tty record): 1/2 receive (a header chunk, then the
// payload bytes pushed into the read queue), 3 send the pending write and advance it, 4 the send is done (clears
// the busy flag; prints when bytes are left).
void sceTtyHandler(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00504720
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 3;
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    s1 = a2;
    sd(ra, sp, 0x30);
    s0 = a1;
    sd(s2, sp, 0x20);
    if (a0 == v0) {
        // 0x0050482c
        charge(ctx, 8);
        lw(a2, s1, 4);
        lw(a0, s1, 0);
        lw(a1, s1, 16);
        a2 = a2 & 0xFFFF;
        jal(ctx, 0x504838u, gen::fn_sceDeci2ExSend_00504598);
        a1 = v0;
        if (i64(a1) >= 0) {
            lw(v0, s1, 16);
            // 0x00504860
            charge(ctx, 7);
            lw(v1, s1, 4);
            v0 = addu(v0, a1);
            v1 = subu(v1, a1);
            sw(v0, s1, 16);
            sw(v1, s1, 4);
            ld(ra, sp, 0x30);
        } else {
            // 0x0050484c
            charge(ctx, 5);
            a0 = 0x7C0000;
            a0 = addiu(a0, -9480);  // "TTY: send err %d\n"
            jal(ctx, 0x504850u, gen::fn_kprintf_00505ec8);
        L_00504898:
            charge(ctx, 2);
            sw(zero, s1, 12);
            ld(ra, sp, 0x30);
        }
    L_005048a0:
        charge(ctx, 1);
        ld(s2, sp, 0x20);
    } else {
        // 0x00504744
        charge(ctx, 3);
        v0 = slti(a0, 4);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = 4;
        if (cc) {
            // 0x00504760
            charge(ctx, 2);
            ld(ra, sp, 0x30);
            if (i64(a0) > 0) {
                // 0x00504768
                charge(ctx, 2);
                if (s0 == 0) {
                    lw(s2, s1, 20);
                    // 0x005047d0
                    charge(ctx, 5);
                    s0 = 12;
                    lhu(v0, s2, 0);
                    v0 = slt(s0, v0);
                    v1 = s2;
                    if (v0 != 0) {
                        // 0x005047e4
                        charge(ctx, 2);
                        lw(a0, s1, 24);
                        for (;;) {
                            // 0x005047f4
                            charge(ctx, 11);
                            v0 = addu(v1, s0);
                            lbu(v1, v0, 0);
                            s0 = addiu(s0, 1);
                            lw(v0, a0, 12);
                            sb(v1, v0, 0);
                            link(ctx, 0x504808u);  // $ra first: the delay slot below depends on it
                            lw(a0, s1, 24);
                            call(ctx, gen::fn_QueuePeekWriteDone_005046a0);
                            lhu(v0, s2, 0);
                            v0 = slt(s0, v0);
                            if (v0 == 0) {
                                break;
                            }
                            lw(v1, s1, 20);
                            backedge(ctx);
                            // 0x005047f0
                            charge(ctx, 1);
                            lw(a0, s1, 24);
                        }
                    }
                    // 0x00504820
                    charge(ctx, 3);
                    sw(zero, s1, 8);
                    ld(ra, sp, 0x30);
                } else {
                    // 0x00504770
                    charge(ctx, 5);
                    lw(v0, s1, 8);
                    v0 = addu(v0, s0);
                    v0 = sltiu(v0, 321);
                    a0 = 0x7C0000;
                    if (v0 == 0) {
                        // 0x00504784
                        charge(ctx, 2);
                        a0 = addiu(a0, -9544);
                        jal(ctx, 0x504784u, gen::fn_kprintf_00505ec8);
                    }
                    // 0x0050478c
                    charge(ctx, 9);
                    lw(v0, s1, 8);
                    a2 = s0 & 0xFFFF;
                    lw(a1, s1, 20);
                    lw(a0, s1, 0);
                    a1 = addu(a1, v0);
                    jal(ctx, 0x50479Cu, gen::fn_sceDeci2ExRecv_00504560);
                    s0 = v0;
                    if (i64(s0) < 0) {
                        // 0x005047b0
                        charge(ctx, 3);
                        a0 = 0x7C0000;
                        a0 = addiu(a0, -9504);  // "TTY: receive error"
                        jal(ctx, 0x5047B4u, gen::fn_kprintf_00505ec8);
                    }
                    // 0x005047bc
                    charge(ctx, 5);
                    lw(v0, s1, 8);
                    v0 = addu(v0, s0);
                    sw(v0, s1, 8);
                    ld(ra, sp, 0x30);
                }
            }
            goto L_005048a0;
        }
        // 0x00504750
        charge(ctx, 2);
        ld(ra, sp, 0x30);
        if (a0 == v0) {
            // 0x0050487c
            charge(ctx, 3);
            lw(v0, s1, 4);
            if (v0 != 0) {
                // 0x00504888
                charge(ctx, 4);
                a0 = 0x7C0000;
                lw(a1, s1, 4);
                a0 = addiu(a0, -9456);  // "TTY: err ti->wlen=%08x\n"
                jal(ctx, 0x504890u, gen::fn_kprintf_00505ec8);
            }
            goto L_00504898;
        }
        // 0x00504758
        charge(ctx, 2);
        ld(s2, sp, 0x20);
    }
    // 0x005048a4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x005048B8 sceTtyWrite -- 372 bytes; frame 0x80: s5 sp+0x50, s4 sp+0x40, s3 sp+0x30, s2 sp+0x20, s1 sp+0x10, s0 sp+0x0, ra sp+0x70, s6 sp+0x60
// Write to the TTY: interrupts off, copies up to 256 bytes into the uncached packet at 0x2096668C (LF becomes CR
// LF), sends the request and polls until the handler clears the busy flag; returns the bytes taken, or -1 when busy
// or the send fails.
void sceTtyWrite(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005048b8
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(s5, sp, 0x50);
    sd(s4, sp, 0x40);
    s5 = 0x960000;
    sd(s3, sp, 0x30);
    s4 = 0;
    sd(s2, sp, 0x20);
    s3 = addiu(s5, 26192);  // &0x966650
    sd(s1, sp, 0x10);
    s2 = a1;
    sd(s0, sp, 0x0);
    s1 = 0;
    sd(ra, sp, 0x70);
    s0 = a0;
    sd(s6, sp, 0x60);
    lw(v0, s3, 12);  // 0x96665C
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = si(-1);
    if (!cc) {
        // 0x00504900
        charge(ctx, 14);
        jal(ctx, 0x504900u, gen::fn_DIntr_0050d3a0);
        s6 = v0;
        a0 = 0x20000000;
        v0 = 0x960000;
        v1 = 1;
        v0 = addiu(v0, 26240);  // &0x966680
        sw(v1, s3, 12);
        a2 = v0 | a0;
        t0 = si(-1);
        sw(a2, s3, 16);
        a3 = 10;
        a1 = 13;
        a0 = addiu(a2, 12);
        for (;;) {
            // 0x00504938
            charge(ctx, 3);
            s2 = addiu(s2, -1);
            if (s2 != t0) {
                // 0x00504944
                charge(ctx, 3);
                lb(v0, s0, 0);
                lbu(v1, s0, 0);
                if (v0 == a3) {
                    // 0x00504950
                    charge(ctx, 5);
                    sb(a1, a0, 0);
                    s1 = addiu(s1, 1);
                    v0 = slti(s1, 256);
                    a0 = addiu(a0, 1);
                    if (v0 == 0) {
                        goto L_00504984;
                    }
                    // 0x00504964
                    charge(ctx, 1);
                    lbu(v1, s0, 0);
                    goto L_00504968;
                }
            L_00504968:
                charge(ctx, 7);
                sb(v1, a0, 0);
                s1 = addiu(s1, 1);
                s0 = addiu(s0, 1);
                a0 = addiu(a0, 1);
                v0 = slti(s1, 256);
                s4 = addiu(s4, 1);
                if (v0 == 0) {
                    goto L_00504984;
                }
                backedge(ctx);
                continue;
            }
            s0 = addiu(s5, 26192);
            break;
        }
    L_00504988:
        charge(ctx, 9);
        v0 = addiu(s1, 12);
        sw(v0, s0, 4);
        lw(v1, s0, 4);
        lb(a1, a2, 7);
        lw(a0, s5, 26192);
        link(ctx, 0x50499Cu);  // $ra first: the delay slot below depends on it
        sh(v1, a2, 0);
        call(ctx, gen::fn_sceDeci2ReqSend_005044b0);
        if (i64(v0) >= 0) {
            // 0x005049c8
            charge(ctx, 3);
            lw(v0, s0, 12);
            s1 = s5;
            if (v0 != 0) {
                // 0x005049d4
                charge(ctx, 1);
                for (;;) {
                    // 0x005049d8
                    charge(ctx, 6);
                    lw(a0, s1, 26192);
                    jal(ctx, 0x5049DCu, gen::fn_sceDeci2Poll_005044e0);
                    lw(v0, s0, 12);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x005049f0
            charge(ctx, 2);
            v0 = s4;
            if (s6 != 0) {
                // 0x005049f8
                charge(ctx, 3);
                jal(ctx, 0x5049F8u, gen::fn_EIntr_0050d3f0);
                v0 = s4;
            }
        } else {
            // 0x005049ac
            charge(ctx, 3);
            sw(zero, s0, 12);
            v0 = si(-1);
            if (s6 != 0) {
                // 0x005049b8
                charge(ctx, 4);
                jal(ctx, 0x5049B8u, gen::fn_EIntr_0050d3f0);
                v0 = si(-1);
            }
        }
    }
    // 0x00504a04 (the shared epilogue, written out on this path)
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
L_00504984:
    charge(ctx, 1);
    s0 = addiu(s5, 26192);
    goto L_00504988;
}

// 0x00504B00 sceTtyInit -- 188 bytes; frame 0x30: s1 sp+0x10, s0 sp+0x0, ra sp+0x20
// Open the TTY's DECI2 socket (protocol 0x210, handler sceTtyHandler), clear its record, build the packet header
// (0x210, 'E', 'H') and make the 256-byte read queue; 1, or 0 when the open fails.
void sceTtyInit(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00504b00
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    a0 = 0;
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x20);
    s0 = 0x960000;
    jal(ctx, 0x504B14u, gen::fn__sceFlushCache_005033e0);
    s1 = addiu(s0, 26192);  // &0x966650
    a2 = 0x500000;
    a0 = 528;
    a2 = addiu(a2, 18208);  // &sceTtyHandler
    a1 = s1;
    jal(ctx, 0x504B2Cu, gen::fn_sceDeci2Open_00504440);
    sw(v0, s0, 26192);  // 0x966650
    lw(v0, s0, 26192);  // 0x966650
    a0 = 0x960000;
    if (i64(v0) >= 0) {
        // 0x00504b4c
        charge(ctx, 23);
        v0 = 0x960000;
        sw(zero, s1, 12);
        v1 = 0x20000000;
        a0 = addiu(a0, 26560);
        v0 = addiu(v0, 26240);  // &0x966680
        v0 = v0 | v1;
        sw(zero, s1, 4);
        a0 = a0 | v1;
        sw(zero, s1, 8);
        sw(a0, s1, 20);
        a2 = 528;
        sw(v0, s1, 16);
        a1 = 69;
        v1 = 72;
        a0 = 256;
        sh(a2, v0, 4);
        sb(a1, v0, 6);
        sb(v1, v0, 7);
        sw(zero, v0, 8);
        link(ctx, 0x504B98u);  // $ra first: the delay slot below depends on it
        sh(zero, v0, 2);
        call(ctx, gen::fn_QueueInit_00504678);
        sw(v0, s1, 24);
        v0 = 1;
    } else {
        // 0x00504b44
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00504ba8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00505DD8 sceVprintf -- 112 bytes; frame 0x50: s2 sp+0x30, s1 sp+0x20, s0 sp+0x10, ra sp+0x40
// Kernel vprintf: interrupts off, _sceSnprintf to the printf_char sink, interrupts back on when they were.
void sceVprintf(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00505dd8
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s2, sp, 0x30);
    sd(s1, sp, 0x20);
    s2 = a1;
    sd(s0, sp, 0x10);
    s1 = a0;
    sd(ra, sp, 0x40);
    link(ctx, 0x505DF4u);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0x0);
    call(ctx, gen::fn_DIntr_0050d3a0);
    a0 = 0x500000;
    a2 = lui(0xFFFF);
    s0 = v0;
    a0 = addiu(a0, 23736);  // &printf_char
    a3 = s1;
    t0 = s2;
    a1 = sp;
    a2 = a2 | 0xFFFF;
    jal(ctx, 0x505E18u, gen::fn__sceSnprintf_00504f48);
    ld(ra, sp, 0x40);
    if (s0 != 0) {
        // 0x00505e28
        charge(ctx, 3);
        jal(ctx, 0x505E28u, gen::fn_EIntr_0050d3f0);
        ld(ra, sp, 0x40);
    }
    // 0x00505e34 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s2, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x50);
}

// 0x00505EC8 kprintf -- 128 bytes; frame 0xC0: s0 sp+0x10, s1 sp+0x20, ra sp+0x30
// Kernel printf (varargs spilled to the frame): interrupts off, _sceSnprintf to the kprintf_char sink, interrupts
// back on when they were.
void kprintf(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00505ec8
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(s0, sp, 0x10);
    sd(s1, sp, 0x20);
    s0 = a0;
    sd(ra, sp, 0x30);
    sd(a1, sp, 0x88);
    sd(a2, sp, 0x90);
    sd(a3, sp, 0x98);
    sd(t0, sp, 0xA0);
    sd(t1, sp, 0xA8);
    sd(t2, sp, 0xB0);
    sd(t3, sp, 0xB8);
    link(ctx, 0x505EF8u);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0x0);
    call(ctx, gen::fn_DIntr_0050d3a0);
    a0 = 0x500000;
    a2 = lui(0xFFFF);
    s1 = v0;
    a0 = addiu(a0, 23776);  // &kprintf_char
    a3 = s0;
    a1 = sp;
    a2 = a2 | 0xFFFF;
    t0 = addiu(sp, 0x88);
    jal(ctx, 0x505F1Cu, gen::fn__sceSnprintf_00504f48);
    ld(ra, sp, 0x30);
    if (s1 != 0) {
        // 0x00505f2c
        charge(ctx, 3);
        jal(ctx, 0x505F2Cu, gen::fn_EIntr_0050d3f0);
        ld(ra, sp, 0x30);
    }
    // 0x00505f38 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0xC0);
}

// 0x005063C8 sub_5063C8 -- 52 bytes; frame 0x10: ra sp+0x0
// SIF command layer shutdown: disables DMAC channel 5 (SIF0), removes its handler, clears the initialised flag
// 0x77F4A8. [sceSifExitCmd]
void sub_5063C8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005063c8
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 5;
    jal(ctx, 0x5063D0u, gen::fn_DisableDmac_00503d10);
    v1 = 0x960000;
    a0 = 5;
    link(ctx, 0x5063E0u);  // $ra first: the delay slot below depends on it
    lw(a1, v1, 27220);
    call(ctx, gen::fn__sceRemoveDmacHandler_00502e90);
    v1 = 0x780000;
    ld(ra, sp, 0x0);
    sw(zero, v1, -2904);  // 0x77F4A8
    sp = addiu(sp, 0x10);
}

// 0x005064A8 sceSifSendCmd -- 76 bytes; leaf frame (no stack)
// Clears a SIF command handler slot: a non-negative id indexes the user table, a negative one (bit 31 off) the
// system table; 12-byte entries. Named sceSifSendCmd in symbols/, the body is the SDK's [sceSifRemoveCmdHandler].
void sceSifSendCmd(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x005064a8
    enter(ctx, 3);  // entry check point + this block's cycles
    a2 = a0;
    v0 = 12;
    if (i64(a2) >= 0) {
        // 0x005064dc
        charge(ctx, 6);
        a0 = 0x960000;
        mult(v0, a2, v0);
        lw(v1, a0, 27244);  // 0x966A6C
        v0 = addu(v0, v1);
        sw(zero, v0, 0);
        return;
    }
    // 0x005064b4
    charge(ctx, 10);
    v0 = 0x7FFF0000;
    a1 = 12;
    v0 = v0 | 0xFFFF;
    v1 = 0x960000;
    v0 = a2 & v0;
    lw(a0, v1, 27236);  // 0x966A64
    mult(v0, v0, a1);
    v0 = addu(v0, a0);
    sw(zero, v0, 0);
}

// 0x00506630 sub_506630 -- 60 bytes; frame 0x10: ra sp+0x0
// Send a SIF command in thread context: _sceSifSendCmd with mode 0 (the arguments shifted up). [sceSifSendCmd]
void sub_506630(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00506630
    enter(ctx, 15);  // entry check point + this block's cycles
    v0 = a2;
    v1 = a3;
    t3 = t0;
    sp = addiu(sp, -0x10);
    t2 = t1;
    a2 = a1;
    sd(ra, sp, 0x0);
    a3 = v0;
    t0 = v1;
    t1 = t3;
    a1 = 0;
    jal(ctx, 0x506658u, gen::fn_sub_5064F8_005064f8);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00506670 sceSifWriteBackDCache -- 60 bytes; frame 0x10: ra sp+0x0
// Send a SIF command in interrupt context: _sceSifSendCmd with mode 1. Named sceSifWriteBackDCache in symbols/, the
// body is the SDK's [isceSifSendCmd].
void sceSifWriteBackDCache(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00506670
    enter(ctx, 15);  // entry check point + this block's cycles
    v0 = a2;
    v1 = a3;
    t3 = t0;
    sp = addiu(sp, -0x10);
    t2 = t1;
    a2 = a1;
    sd(ra, sp, 0x0);
    a3 = v0;
    t0 = v1;
    t1 = t3;
    a1 = 1;
    jal(ctx, 0x506698u, gen::fn_sub_5064F8_005064f8);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005067F8 sub_5067F8 -- 172 bytes; leaf frame (no stack)
// Write back and invalidate the data cache over [$a0, $a0 + $a1): 64-byte lines, the odd lines first, then eight
// per pass. [sceSifWriteBackDCache]
void sub_5067F8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t9{ctx, 25};
    // 0x005067f8
    enter(ctx, 4);  // entry check point + this block's cycles
    t9 = lui(0xFFFF);
    t9 = t9 | 0xFFC0;
    t2 = addu(a0, a1);
    if (i64(a1) > 0) {
        // 0x00506808
        charge(ctx, 9);
        t0 = a0 & t9;
        t2 = addiu(t2, -1);
        t1 = t2 & t9;
        t2 = subu(t1, t0);
        t3 = srl(t2, 6);
        t3 = addiu(t3, 1);
        t1 = t3 & 0x7;
        t2 = srl(t3, 3);
        if (t1 != 0) {
            for (;;) {
                // 0x0050682c
                charge(ctx, 7);
                sync(ctx, 0);
                cache(ctx, 24, t0, 0);
                sync(ctx, 0);
                t1 = addiu(t1, -1);
                t0 = addiu(t0, 64);
                if (i64(t1) <= 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x00506848
        charge(ctx, 1);
        if (t2 == 0) {
            charge(ctx, 1);
            t2 = addiu(t2, -1);
        } else {
            for (;;) {
                // 0x0050684c
                charge(ctx, 1);
                t2 = addiu(t2, -1);
                // 0x00506850
                charge(ctx, 19);
                sync(ctx, 0);
                cache(ctx, 24, t0, 0);
                sync(ctx, 0);
                cache(ctx, 24, t0, 64);
                sync(ctx, 0);
                cache(ctx, 24, t0, 128);
                sync(ctx, 0);
                cache(ctx, 24, t0, 192);
                sync(ctx, 0);
                cache(ctx, 24, t0, 256);
                sync(ctx, 0);
                cache(ctx, 24, t0, 320);
                sync(ctx, 0);
                cache(ctx, 24, t0, 384);
                sync(ctx, 0);
                cache(ctx, 24, t0, 448);
                sync(ctx, 0);
                t0 = addiu(t0, 512);
                if (i64(t2) <= 0) {
                    break;
                }
                backedge(ctx);
            }
        }
    }
    // 0x0050689c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00506A48 sceSifExitRpc -- 36 bytes; frame 0x10: ra sp+0x0
// SIF RPC shutdown: the command layer's exit, then the RPC initialised flag 0x77F4B0 cleared.
void sceSifExitRpc(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00506a48
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x506A50u, gen::fn_sub_5063C8_005063c8);
    v0 = 0x780000;
    ld(ra, sp, 0x0);
    sw(zero, v0, -2896);  // 0x77F4B0
    sp = addiu(sp, 0x10);
}

// 0x00506A70 _sceRpcGetPacket -- 168 bytes; frame 0x30: s1 sp+0x10, s0 sp+0x0, ra sp+0x20
// Take a free 64-byte RPC packet from the client's pool ($a0: next id, pool, count): marks it busy with its index,
// stamps the next packet id; null when all are busy. Interrupts off.
void _sceRpcGetPacket(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00506a70
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x20);
    s1 = a0;
    jal(ctx, 0x506A80u, gen::fn_DIntr_0050d3a0);
    lw(a0, s1, 8);
    v1 = 0;
    lw(s0, s1, 4);
    if (i64(a0) > 0) {
        // 0x00506a98
        charge(ctx, 2);
        a1 = 1;
        for (;;) {
            // 0x00506aa0
            charge(ctx, 4);
            lw(v0, s0, 16);
            v0 = v0 & 0x1;
            if (v0 == 0) {
                goto L_00506ab0_3;
            }
            v1 = addiu(v1, 1);
            // 0x00506aec
            charge(ctx, 3);
            v0 = slt(v1, a0);
            s0 = addiu(s0, 64);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00506af8
    charge(ctx, 3);
    jal(ctx, 0x506AF8u, gen::fn_EIntr_0050d3f0);
    v0 = 0;
    // 0x00506b04 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
    return;
L_00506ab0_3:
    charge(ctx, 7);
    v0 = sll(v1, 16);
    v0 = v0 | 0x5;
    sw(v0, s0, 16);
    lw(v0, s1, 0);
    v1 = addiu(v0, 1);
    sw(v1, s1, 0);
    if (v1 == a1) {
        // 0x00506acc
        charge(ctx, 3);
        v0 = addiu(v0, 2);
        v1 = 1;
        sw(v0, s1, 0);
    }
    // 0x00506ad8
    charge(ctx, 5);
    sw(s0, s0, 20);
    link(ctx, 0x506ADCu);  // $ra first: the delay slot below depends on it
    sw(v1, s0, 24);
    call(ctx, gen::fn_EIntr_0050d3f0);
    v0 = s0;
    // 0x00506b04 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00506B18 _sceRpcFreePacket -- 28 bytes; leaf frame (no stack)
// Release an RPC packet: clears its id and the busy bit.
void _sceRpcFreePacket(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00506b18
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(v1, a0, 16);
    v0 = lui(0xFFFF);
    v0 = v0 | 0xFFFE;
    sw(zero, a0, 24);
    v1 = v1 & v0;
    sw(v1, a0, 16);
}

// 0x00506B38 _sceRpcGetFPacket -- 48 bytes; leaf frame (no stack)
// The next packet of a server's receive ring (round robin over its count).
void _sceRpcGetFPacket(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00506b38
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(a1, a0, 36);
    lw(v1, a0, 24);
    div(a1, v1);
    if (v1 == 0) {
        brk(ctx, 0x506B48u, 0x7u);
    }
    // 0x00506b4c
    charge(ctx, 7);
    lw(a1, a0, 20);
    mfhi(v0);
    v1 = addiu(v0, 1);
    v0 = sll(v0, 6);
    sw(v1, a0, 36);
    v0 = addu(a1, v0);
}

// 0x00506EF0 _search_svdata -- 76 bytes; leaf frame (no stack)
// Find the RPC server bound to a command id: walks the queues from the request's queue and each queue's server
// list.
void _search_svdata(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00506ef0
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(a1, a1, 40);
    if (a1 == 0) {
        // 0x00506f34 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = 0;
        return;
    }
    // 0x00506efc
    charge(ctx, 1);
    lw(v1, a1, 8);
    for (;;) {
        // 0x00506f00
        charge(ctx, 2);
        if (v1 == 0) {
            lw(a1, a1, 20);
        } else {
            // 0x00506f08
            charge(ctx, 2);
            lw(v0, v1, 0);
            for (;;) {
                // 0x00506f10
                charge(ctx, 2);
                if (v0 == a0) {
                    goto L_00506f18_5;
                }
                lw(v1, v1, 56);
                // 0x00506f20
                charge(ctx, 2);
                if (v1 == 0) {
                    break;
                }
                lw(v0, v1, 0);
                backedge(ctx);
            }
            // 0x00506f28
            charge(ctx, 1);
            lw(a1, a1, 20);
        }
        // 0x00506f2c
        charge(ctx, 2);
        if (a1 == 0) {
            break;
        }
        lw(v1, a1, 8);
        backedge(ctx);
    }
    // 0x00506f34 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = 0;
    return;
L_00506f18_5:
    charge(ctx, 2);
    v0 = v1;
}

// 0x005071A0 _request_call -- 140 bytes; leaf frame (no stack)
// SIF RPC call request handler: appends the server to its queue's pending list, copies the request (function,
// buffers, sizes, client packet) into the server record, wakes the queue's thread when it is idle.
void _request_call(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x005071a0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(a1, a0, 52);
    lw(a2, a1, 64);
    lw(v0, a2, 12);
    if (v0 != 0) {
        lw(v0, a2, 16);
        // 0x005071bc
        charge(ctx, 1);
        sw(a1, v0, 60);
    } else {
        // 0x005071b4
        charge(ctx, 2);
        sw(a1, a2, 12);
    }
    // 0x005071c0
    charge(ctx, 20);
    sw(a1, a2, 16);
    lw(v0, a0, 20);
    lw(v1, a0, 28);
    sw(v0, a1, 32);
    sw(v1, a1, 28);
    lw(v0, a0, 32);
    sw(v0, a1, 36);
    lw(v1, a0, 36);
    sw(v1, a1, 12);
    lw(v0, a0, 40);
    sw(v0, a1, 40);
    lw(v1, a0, 44);
    sw(v1, a1, 44);
    lw(v0, a0, 48);
    sw(v0, a1, 48);
    lw(v1, a0, 16);
    sw(v1, a1, 52);
    lw(a0, a2, 0);
    if (i64(a0) < 0) {
        // 0x00507224 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x00507210
    charge(ctx, 3);
    lw(v0, a2, 4);
    if (v0 != 0) {
        // 0x00507224 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x0050721c
    charge(ctx, 2);
    gen::fn_iWakeupThread_00504028(ctx);  // tail call
}

// 0x00507430 sceSifCheckStatRpc -- 60 bytes; leaf frame (no stack)
// 1 while the client's call is in flight: the packet exists, its id still matches and it is busy.
void sceSifCheckStatRpc(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00507430
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(a1, a0, 0);
    if (a1 == 0) {
        // 0x0050745c (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = 0;
        return;
    }
    // 0x0050743c
    charge(ctx, 4);
    lw(v1, a0, 4);
    lw(v0, a1, 24);
    if (v1 != v0) {
        // 0x0050745c (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = 0;
        return;
    }
    // 0x0050744c
    charge(ctx, 4);
    lw(v0, a1, 16);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        // 0x00507464
        charge(ctx, 2);
        v0 = 1;
        return;
    }
    // 0x0050745c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = 0;
}

// 0x00507470 sceSifSetRpcQueue -- 148 bytes; frame 0x30: s1 sp+0x10, s0 sp+0x0, ra sp+0x20
// Initialise an RPC queue for a thread and append it to the global queue list (0x9684A8). Interrupts off.
void sceSifSetRpcQueue(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00507470
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    s1 = a0;
    sd(ra, sp, 0x20);
    s0 = a1;
    jal(ctx, 0x507484u, gen::fn_DIntr_0050d3a0);
    v1 = 0x970000;
    sw(s0, s1, 0);
    v1 = addiu(v1, -31616);  // &0x968480
    sw(zero, s1, 4);
    lw(v0, v1, 40);  // 0x9684A8
    sw(zero, s1, 8);
    sw(zero, s1, 12);
    sw(zero, s1, 16);
    sw(zero, s1, 20);
    if (v0 != 0) {
        // 0x005074bc
        charge(ctx, 4);
        a0 = v0;
        lw(v1, a0, 20);
        if (v1 == 0) {
            sw(s1, a0, 20);
        } else {
            // 0x005074cc
            charge(ctx, 1);
            for (;;) {
                // 0x005074d0
                charge(ctx, 7);
                a0 = v1;
                lw(v0, a0, 20);
                v1 = v0;
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x005074ec
            charge(ctx, 1);
            sw(s1, a0, 20);
        }
    } else {
        // 0x005074b4
        charge(ctx, 2);
        sw(s1, v1, 40);
    }
    // 0x005074f0
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
    gen::fn_EIntr_0050d3f0(ctx);  // tail call
}

// 0x00507508 sceSifRegisterRpc -- 208 bytes; frame 0x80: s6 sp+0x60, s5 sp+0x50, s4 sp+0x40, s3 sp+0x30, s2 sp+0x20, s1 sp+0x10, s0 sp+0x0, ra sp+0x70
// Register an RPC server (command, function, buffer, callbacks) and append it to the queue's server list.
// Interrupts off.
void sceSifRegisterRpc(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00507508
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(s6, sp, 0x60);
    sd(s5, sp, 0x50);
    s6 = t2;
    sd(s4, sp, 0x40);
    s5 = a0;
    sd(s3, sp, 0x30);
    s4 = t1;
    sd(s2, sp, 0x20);
    s3 = t0;
    sd(s1, sp, 0x10);
    s2 = a3;
    sd(s0, sp, 0x0);
    s1 = a2;
    sd(ra, sp, 0x70);
    s0 = a1;
    jal(ctx, 0x507544u, gen::fn_DIntr_0050d3a0);
    sw(zero, s5, 60);
    sw(zero, s5, 56);
    sw(s0, s5, 0);
    lw(v0, s6, 8);
    sw(s1, s5, 4);
    sw(s2, s5, 8);
    sw(s3, s5, 16);
    sw(s4, s5, 20);
    sw(s6, s5, 64);
    if (v0 != 0) {
        // 0x0050757c
        charge(ctx, 4);
        a0 = v0;
        lw(v1, a0, 56);
        if (v1 == 0) {
            sw(s5, a0, 56);
        } else {
            // 0x0050758c
            charge(ctx, 1);
            for (;;) {
                // 0x00507590
                charge(ctx, 7);
                a0 = v1;
                lw(v0, a0, 56);
                v1 = v0;
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x005075ac
            charge(ctx, 1);
            sw(s5, a0, 56);
        }
    } else {
        // 0x00507574
        charge(ctx, 2);
        sw(s5, s6, 8);
    }
    // 0x005075b0
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
    gen::fn_EIntr_0050d3f0(ctx);  // tail call
}

// 0x005075D8 sceSifRemoveRpc -- 148 bytes; frame 0x40: s2 sp+0x20, s1 sp+0x10, s0 sp+0x0, ra sp+0x30
// Unlink a server from its queue's list; returns the node it was found after (or the head). Interrupts off.
void sceSifRemoveRpc(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005075d8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x10);
    s2 = a1;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x30);
    s1 = a0;
    jal(ctx, 0x5075F0u, gen::fn_DIntr_0050d3a0);
    lw(s0, s2, 8);
    if (s0 != s1) {
        // 0x00507610
        charge(ctx, 2);
        if (s0 != 0) {
            // 0x00507618
            charge(ctx, 3);
            lw(v1, s0, 56);
            if (v1 == s1) {
                lw(v0, s1, 56);
            } else {
                // 0x00507624
                charge(ctx, 1);
                for (;;) {
                    // 0x00507628
                    charge(ctx, 3);
                    s0 = v1;
                    if (s0 == 0) {
                        break;
                    }
                    // 0x00507634
                    charge(ctx, 3);
                    lw(v0, s0, 56);
                    v1 = v0;
                    if (v0 == s1) {
                        goto L_00507640_7;
                    }
                    backedge(ctx);
                }
                goto L_00507648;
            }
        L_00507644:
            charge(ctx, 1);
            sw(v0, s0, 56);
        }
    } else {
        // 0x00507604
        charge(ctx, 3);
        lw(v0, s0, 56);
        sw(v0, s2, 8);
    }
L_00507648:
    charge(ctx, 9);
    jal(ctx, 0x507648u, gen::fn_EIntr_0050d3f0);
    v0 = s0;
    ld(ra, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_00507640_7:
    charge(ctx, 1);
    lw(v0, s1, 56);
    goto L_00507644;
}

// 0x00507670 sceSifRemoveRpcQueue -- 144 bytes; frame 0x30: s1 sp+0x10, s0 sp+0x0, ra sp+0x20
// Unlink a queue from the global queue list. Interrupts off.
void sceSifRemoveRpcQueue(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00507670
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x20);
    s1 = a0;
    jal(ctx, 0x507680u, gen::fn_DIntr_0050d3a0);
    v1 = 0x970000;
    v1 = addiu(v1, -31616);  // &0x968480
    lw(s0, v1, 40);  // 0x9684A8
    if (s0 != s1) {
        // 0x005076a8
        charge(ctx, 2);
        if (s0 != 0) {
            // 0x005076b0
            charge(ctx, 3);
            lw(v1, s0, 20);
            if (v1 == s1) {
                lw(v0, s1, 20);
            } else {
                // 0x005076bc
                charge(ctx, 1);
                for (;;) {
                    // 0x005076c0
                    charge(ctx, 3);
                    s0 = v1;
                    if (s0 == 0) {
                        break;
                    }
                    // 0x005076cc
                    charge(ctx, 3);
                    lw(v0, s0, 20);
                    v1 = v0;
                    if (v0 == s1) {
                        goto L_005076d8_7;
                    }
                    backedge(ctx);
                }
                goto L_005076e0;
            }
        L_005076dc:
            charge(ctx, 1);
            sw(v0, s0, 20);
        }
    } else {
        // 0x0050769c
        charge(ctx, 3);
        lw(v0, s0, 20);
        sw(v0, v1, 40);
    }
L_005076e0:
    charge(ctx, 8);
    jal(ctx, 0x5076E0u, gen::fn_EIntr_0050d3f0);
    v0 = s0;
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
    return;
L_005076d8_7:
    charge(ctx, 1);
    lw(v0, s1, 20);
    goto L_005076dc;
}

// 0x00507700 sceSifGetNextRequest -- 88 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x10, ra sp+0x20
// Pop the queue's next pending server (marks the queue active, or idle when empty). Interrupts off.
void sceSifGetNextRequest(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00507700
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x10);
    sd(ra, sp, 0x20);
    s0 = a0;
    jal(ctx, 0x507710u, gen::fn_DIntr_0050d3a0);
    lw(s1, s0, 12);
    if (s1 != 0) {
        lw(v1, s1, 60);
        // 0x0050772c
        charge(ctx, 3);
        v0 = 1;
        sw(v0, s0, 4);
        sw(v1, s0, 12);
    } else {
        // 0x00507724
        charge(ctx, 2);
        sw(zero, s0, 4);
    }
    // 0x00507738
    charge(ctx, 8);
    jal(ctx, 0x507738u, gen::fn_EIntr_0050d3f0);
    v0 = s1;
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00507960 _sceFsIobSemaMK -- 112 bytes; frame 0x40: s0 sp+0x20, ra sp+0x30
// Create the stdio iob semaphores once ("SceStdioIobSema", "SceStdioQueSema").
void _sceFsIobSemaMK(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00507960
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v1 = si(-1);
    sd(s0, sp, 0x20);
    s0 = 0x780000;
    sd(ra, sp, 0x30);
    lw(v0, s0, libs6::lo(libs6::kIobSema));  // 0x77F548
    ld(ra, sp, 0x30);
    if (v0 == v1) {
        // 0x00507980
        charge(ctx, 17);
        v0 = 0x7C0000;
        v1 = 1;
        v0 = addiu(v0, -8896);  // "SceStdioIobSema"
        sw(v1, sp, 0x4);
        sw(v0, sp, 0x14);
        a0 = sp;
        link(ctx, 0x507998u);  // $ra first: the delay slot below depends on it
        sw(v1, sp, 0x8);
        call(ctx, gen::fn__sceCreateSema_00503160);
        v1 = 0x7C0000;
        sw(v0, s0, -2744);
        v1 = addiu(v1, -8880);  // "SceStdioQueSema"
        a0 = sp;
        link(ctx, 0x5079B0u);  // $ra first: the delay slot below depends on it
        sw(v1, sp, 0x14);
        call(ctx, gen::fn__sceCreateSema_00503160);
        v1 = 0x780000;
        sw(v0, v1, -2740);  // 0x77F54C
        ld(ra, sp, 0x30);
    }
    // 0x005079c4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(s0, sp, 0x20);
    sp = addiu(sp, 0x40);
}

// 0x005079D0 use_iob_cnt -- 124 bytes; frame 0x30: s1 sp+0x10, s0 sp+0x0, ra sp+0x20
// Count the open file slots (32 16-byte iob records at 0x969A00), under the iob semaphore.
void use_iob_cnt(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005079d0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    s1 = 0x780000;
    sd(ra, sp, 0x20);
    s0 = 0;
    jal(ctx, 0x5079E4u, gen::fn__sceFsIobSemaMK_00507960);
    link(ctx, 0x5079ECu);  // $ra first: the delay slot below depends on it
    lw(a0, s1, libs6::lo(libs6::kIobSema));  // 0x77F548
    call(ctx, gen::fn__sceWaitSema_005031a0);
    v1 = 0x970000;
    a1 = addiu(v1, -26112);  // &0x969A00
    v1 = addiu(a1, 512);  // &0x969C00
    v0 = sltu(a1, v1);
    a2 = v1;
    if (v0 != 0) {
        // 0x00507a0c
        charge(ctx, 1);
        for (;;) {
            // 0x00507a10
            charge(ctx, 7);
            lw(a0, a1, 4);
            v1 = addiu(s0, 1);
            a1 = addiu(a1, 16);
            if (a0 != 0) s0 = v1;
            v0 = sltu(a1, a2);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00507a2c
    charge(ctx, 8);
    link(ctx, 0x507A2Cu);  // $ra first: the delay slot below depends on it
    lw(a0, s1, -2744);
    call(ctx, gen::fn__sceSignalSema_00503180);
    v0 = s0;
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00507A50 new_iob -- 136 bytes; frame 0x30: s1 sp+0x10, s0 sp+0x0, ra sp+0x20
// Take a free iob record (marks it 0x10000000 in use), under the iob semaphore; null when full.
void new_iob(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00507a50
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x20);
    s1 = 0x780000;
    jal(ctx, 0x507A60u, gen::fn__sceFsIobSemaMK_00507960);
    link(ctx, 0x507A68u);  // $ra first: the delay slot below depends on it
    lw(a0, s1, libs6::lo(libs6::kIobSema));  // 0x77F548
    call(ctx, gen::fn__sceWaitSema_005031a0);
    v1 = 0x970000;
    s0 = addiu(v1, -26112);  // &0x969A00
    v1 = addiu(s0, 512);  // &0x969C00
    v0 = sltu(s0, v1);
    a1 = 0x10000000;
    if (v0 != 0) {
        // 0x00507a88
        charge(ctx, 2);
        lw(v0, s0, 4);
        for (;;) {
            // 0x00507a90
            charge(ctx, 2);
            if (v0 == 0) {
                goto L_00507a98_3;
            }
            s0 = addiu(s0, 16);
            // 0x00507aac
            charge(ctx, 3);
            v0 = sltu(s0, v1);
            if (v0 == 0) {
                break;
            }
            lw(v0, s0, 4);
            backedge(ctx);
        }
    }
    // 0x00507ab8
    charge(ctx, 3);
    link(ctx, 0x507AB8u);  // $ra first: the delay slot below depends on it
    lw(a0, s1, -2744);
    call(ctx, gen::fn__sceSignalSema_00503180);
    v0 = 0;
    // 0x00507ac4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
    return;
L_00507a98_3:
    charge(ctx, 5);
    lw(a0, s1, -2744);
    link(ctx, 0x507A9Cu);  // $ra first: the delay slot below depends on it
    sw(a1, s0, 4);
    call(ctx, gen::fn__sceSignalSema_00503180);
    v0 = s0;
    // 0x00507ac4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00507BC8 get_iob -- 108 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x10, ra sp+0x20
// The iob record of a descriptor (< 32), or null; takes and releases the iob semaphore.
void get_iob(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00507bc8
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x10);
    s0 = a0;
    sd(ra, sp, 0x20);
    s1 = 0x780000;
    jal(ctx, 0x507BDCu, gen::fn__sceFsIobSemaMK_00507960);
    link(ctx, 0x507BE4u);  // $ra first: the delay slot below depends on it
    lw(a0, s1, libs6::lo(libs6::kIobSema));  // 0x77F548
    call(ctx, gen::fn__sceWaitSema_005031a0);
    v1 = sltiu(s0, 32);
    v0 = 0x970000;
    if (v1 != 0) {
        // 0x00507c08
        charge(ctx, 6);
        s0 = sll(s0, 4);
        v0 = addiu(v0, -26112);
        lw(a0, s1, -2744);
        s0 = addu(s0, v0);
        jal(ctx, 0x507C14u, gen::fn__sceSignalSema_00503180);
        v0 = s0;
    } else {
        // 0x00507bf8
        charge(ctx, 4);
        link(ctx, 0x507BF8u);  // $ra first: the delay slot below depends on it
        lw(a0, s1, -2744);
        call(ctx, gen::fn__sceSignalSema_00503180);
        v0 = 0;
    }
    // 0x00507c20 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00507C38 _sceFs_Rcv_Intr -- 948 bytes; frame 0x40: ra sp+0x30, s0 sp+0x20
// File I/O RPC receive interrupt: picks the reply slot (0x969180 + 1088 * slot, uncached), copies the result data
// back per command (2 read's unaligned edges, 11 getstat / 12 dread records, 23/25/26 strings up to 1 KiB) and
// signals the waiter; a negative result clears the matching descriptor from the 32-entry table at 0x77F4B8.
void _sceFs_Rcv_Intr(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00507c38
    enter(ctx, 7);  // entry check point + this block's cycles
    v0 = 0x780000;
    sp = addiu(sp, -0x40);
    lw(v1, v0, -2752);  // 0x77F540
    a1 = 0;
    sd(ra, sp, 0x30);
    sd(s0, sp, 0x20);
    if (v1 != 0) {
        // 0x00507c54
        charge(ctx, 1);
        lw(a1, a0, 12);
    }
    // 0x00507c58
    charge(ctx, 28);
    v1 = 1088;
    v0 = 0x780000;
    mult(v1, a1, v1);
    a0 = 0x970000;
    sw(a1, v0, -2760);  // 0x77F538
    a0 = addiu(a0, -28288);  // &0x969180
    a1 = 0x20000000;
    v1 = addu(v1, a0);
    s0 = v1 | a1;
    lwl(v0, s0, 3);
    lwr(v0, s0, 0);
    swl(v0, sp, 0x3);
    swr(v0, sp, 0x0);
    lwl(a2, s0, 7);
    lwr(a2, s0, 4);
    swl(a2, sp, 0x7);
    swr(a2, sp, 0x4);
    lwl(v1, s0, 11);
    lwr(v1, s0, 8);
    swl(v1, sp, 0xB);
    swr(v1, sp, 0x8);
    lwl(a3, s0, 15);
    lwr(a3, s0, 12);
    swl(a3, sp, 0xF);
    swr(a3, sp, 0xC);
    lw(v0, sp, 0x0);
    lw(a0, sp, 0x8);
    if (i64(v0) >= 0) {
        // 0x00507cc8
        charge(ctx, 3);
        a1 = addiu(s0, 16);
        link(ctx, 0x507CCCu);  // $ra first: the delay slot below depends on it
        lw(a2, sp, 0xC);
        call(ctx, gen::fn_memcpy_00521250);
    }
    // 0x00507cd4
    charge(ctx, 5);
    lw(v0, sp, 0x4);
    a0 = addiu(v0, -2);
    v1 = sltiu(a0, 25);
    v0 = 0x7C0000;
    if (v1 != 0) {
        // 0x00507ce8
        charge(ctx, 6);
        v1 = sll(a0, 2);
        v0 = addiu(v0, -8864);
        v1 = addu(v1, v0);
        lw(a0, v1, 0);
        switch (a0.u()) {
        case 0x507D00u:  // table[0]
            // 0x00507d00
            charge(ctx, 3);
            lw(v1, s0, 20);
            a3 = addiu(s0, 20);
            if (i64(v1) > 0) {
                // 0x00507d0c
                charge(ctx, 5);
                lw(t0, a3, 8);
                v0 = 0x20000000;
                a2 = 0;
                t2 = t0 | v0;
                if (i64(v1) > 0) {
                    // 0x00507d20
                    charge(ctx, 2);
                    t1 = addiu(s0, 36);
                    v0 = addu(t1, a2);
                    for (;;) {
                        // 0x00507d28
                        charge(ctx, 10);
                        a1 = addu(t2, a2);
                        lbu(v1, v0, 0);
                        a0 = addu(t0, a2);
                        a2 = addiu(a2, 1);
                        sb(v1, a1, 0);
                        sb(v1, a0, 0);
                        lw(v0, a3, 0);
                        v0 = slt(a2, v0);
                        cc = v0 != 0;  // the condition, before the delay slot changes it
                        v0 = addu(t1, a2);
                        if (!cc) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
            }
            // 0x00507d50
            charge(ctx, 3);
            lw(v1, a3, 4);
            v0 = 0x20000000;
            if (i64(v1) <= 0) {
            L_00507f68:
                charge(ctx, 1);
                lw(a0, sp, 0x0);
            } else {
                // 0x00507d5c
                charge(ctx, 4);
                lw(t0, a3, 12);
                a2 = 0;
                t2 = t0 | v0;
                if (i64(v1) <= 0) {
                    goto L_00507f68;
                }
                // 0x00507d6c
                charge(ctx, 3);
                t1 = addiu(a3, 80);
                v0 = addu(t1, a2);
                for (;;) {
                    // 0x00507d78
                    charge(ctx, 10);
                    a1 = addu(t2, a2);
                    lbu(v1, v0, 0);
                    a0 = addu(t0, a2);
                    a2 = addiu(a2, 1);
                    sb(v1, a1, 0);
                    sb(v1, a0, 0);
                    lw(v0, a3, 4);
                    v0 = slt(a2, v0);
                    cc = v0 != 0;  // the condition, before the delay slot changes it
                    v0 = addu(t1, a2);
                    if (!cc) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00507da0
                charge(ctx, 2);
                lw(a0, sp, 0x0);
            }
            break;
        case 0x507DA8u:  // table[9]
            // 0x00507da8
            charge(ctx, 4);
            lw(v0, sp, 0x8);
            lw(v1, v0, 0);
            lw(a0, sp, 0x0);
            if (i64(v1) > 0) {
                // 0x00507db8
                charge(ctx, 10);
                lwl(a0, s0, 23);
                lwr(a0, s0, 20);
                swl(a0, sp, 0x13);
                swr(a0, sp, 0x10);
                a0 = addiu(s0, 24);
                lw(a2, sp, 0x10);
                v0 = a0 | a2;
                v0 = v0 & 0x7;
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = addiu(s0, 344);
                if (cc) {
                    for (;;) {
                        // 0x00507e3c
                        charge(ctx, 13);
                        ld(t0, a0, 0);
                        ld(v1, a0, 8);
                        ld(a1, a0, 16);
                        ld(a3, a0, 24);
                        sd(t0, a2, 0);
                        sd(v1, a2, 8);
                        sd(a1, a2, 16);
                        sd(a3, a2, 24);
                        a0 = addiu(a0, 32);
                        a2 = addiu(a2, 32);
                        if (a0 == v0) {
                            break;
                        }
                        backedge(ctx);
                    }
                } else {
                    for (;;) {
                        // 0x00507de0
                        charge(ctx, 21);
                        ldl(t0, a0, 7);
                        ldr(t0, a0, 0);
                        ldl(v1, a0, 15);
                        ldr(v1, a0, 8);
                        ldl(a1, a0, 23);
                        ldr(a1, a0, 16);
                        ldl(a3, a0, 31);
                        ldr(a3, a0, 24);
                        sdl(t0, a2, 7);
                        sdr(t0, a2, 0);
                        sdl(v1, a2, 15);
                        sdr(v1, a2, 8);
                        sdl(a1, a2, 23);
                        sdr(a1, a2, 16);
                        sdl(a3, a2, 31);
                        sdr(a3, a2, 24);
                        a0 = addiu(a0, 32);
                        a2 = addiu(a2, 32);
                        if (a0 == v0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00507e34
                    charge(ctx, 2);
                }
                // 0x00507e70
                charge(ctx, 5);
                lwl(t0, a0, 3);
                lwr(t0, a0, 0);
                swl(t0, a2, 3);
                swr(t0, a2, 0);
                goto L_00507f68;
            }
            break;
        case 0x507E84u:  // table[10]
            // 0x00507e84
            charge(ctx, 39);
            lwl(a2, s0, 23);
            lwr(a2, s0, 20);
            swl(a2, sp, 0x13);
            swr(a2, sp, 0x10);
            lw(v0, sp, 0x10);
            ldl(v1, s0, 31);
            ldr(v1, s0, 24);
            ldl(a0, s0, 39);
            ldr(a0, s0, 32);
            ldl(a1, s0, 47);
            ldr(a1, s0, 40);
            ldl(a2, s0, 55);
            ldr(a2, s0, 48);
            sdl(v1, v0, 7);
            sdr(v1, v0, 0);
            sdl(a0, v0, 15);
            sdr(a0, v0, 8);
            sdl(a1, v0, 23);
            sdr(a1, v0, 16);
            sdl(a2, v0, 31);
            sdr(a2, v0, 24);
            ldl(v1, s0, 63);
            ldr(v1, s0, 56);
            ldl(a0, s0, 71);
            ldr(a0, s0, 64);
            ldl(a1, s0, 79);
            ldr(a1, s0, 72);
            ldl(a2, s0, 87);
            ldr(a2, s0, 80);
            sdl(v1, v0, 39);
            sdr(v1, v0, 32);
            sdl(a0, v0, 47);
            sdr(a0, v0, 40);
            sdl(a1, v0, 55);
            sdr(a1, v0, 48);
            sdl(a2, v0, 63);
            sdr(a2, v0, 56);
            lw(a0, sp, 0x0);
            break;
        case 0x507F20u:  // table[21, 23, 24]
            // 0x00507f20
            charge(ctx, 12);
            lwl(a3, s0, 23);
            lwr(a3, s0, 20);
            swl(a3, sp, 0x13);
            swr(a3, sp, 0x10);
            lwl(a0, s0, 27);
            lwr(a0, s0, 24);
            swl(a0, sp, 0x17);
            swr(a0, sp, 0x14);
            lw(a2, sp, 0x14);
            v0 = sltiu(a2, 1025);
            lw(a0, sp, 0x10);
            if (v0 == 0) {
                // 0x00507f50
                charge(ctx, 4);
                v0 = 1024;
                a2 = 1024;
                sw(v0, sp, 0x14);
                lw(a0, sp, 0x10);
            }
            // 0x00507f60
            charge(ctx, 2);
            a1 = addiu(s0, 28);
            jal(ctx, 0x507F60u, gen::fn_memcpy_00521250);
            goto L_00507f68;
        case 0x507F68u:  // table[1, 2, 3, 4, 5, 6, 7, 8, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 22]
            goto L_00507f68;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, a0.u());
            return;
        }
        goto L_00507f6c;
    }
    goto L_00507f68;
L_00507f6c:
    charge(ctx, 2);
    a3 = 0x780000;
    if (i64(a0) >= 0) {
        // 0x00507fd4
        charge(ctx, 2);
        jal(ctx, 0x507FD4u, gen::fn__sceiSignalSema_00503190);
    L_00507fdc:
        charge(ctx, 1);
        ld(ra, sp, 0x30);
    } else {
        // 0x00507f74
        charge(ctx, 6);
        v0 = subu(0, a0);
        lw(v1, a3, -2888);
        a1 = v0;
        sw(v0, sp, 0x0);
        a2 = 0;
        if (v1 != a1) {
            // 0x00507fa0
            charge(ctx, 1);
            a2 = addiu(a2, 1);
            for (;;) {
                // 0x00507fa4
                charge(ctx, 3);
                v0 = slti(a2, 32);
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = addiu(a3, -2888);
                if (cc) {
                    goto L_00507fdc;
                }
                // 0x00507fb0
                charge(ctx, 5);
                v1 = sll(a2, 2);
                v1 = addu(v1, v0);
                lw(a0, v1, 0);
                a2 = addiu(a2, 1);
                if (a0 == a1) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00507fc4
            charge(ctx, 4);
            v0 = si(-1);
            sw(v0, v1, 0);
            ld(ra, sp, 0x30);
        } else {
            // 0x00507f8c
            charge(ctx, 4);
            v0 = si(-1);
            sw(v0, a3, -2888);
            ld(ra, sp, 0x30);
        }
    }
    // 0x00507fe0 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(s0, sp, 0x20);
    sp = addiu(sp, 0x40);
}

// 0x00507FF0 _sceFsSemInit -- 84 bytes; frame 0x40: s0 sp+0x20, ra sp+0x30
// Create the file I/O semaphore once ("SceStdioFioSema").
void _sceFsSemInit(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00507ff0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v1 = si(-1);
    sd(s0, sp, 0x20);
    s0 = 0x780000;
    sd(ra, sp, 0x30);
    lw(v0, s0, libs6::lo(libs6::kFioSema));  // 0x77F544
    ld(ra, sp, 0x30);
    if (v0 == v1) {
        // 0x00508010
        charge(ctx, 10);
        v0 = 0x7C0000;
        v1 = 1;
        v0 = addiu(v0, -8760);  // "SceStdioFioSema"
        sw(v1, sp, 0x4);
        sw(v0, sp, 0x14);
        a0 = sp;
        link(ctx, 0x508028u);  // $ra first: the delay slot below depends on it
        sw(v1, sp, 0x8);
        call(ctx, gen::fn__sceCreateSema_00503160);
        sw(v0, s0, -2748);
        ld(ra, sp, 0x30);
    }
    // 0x00508038 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(s0, sp, 0x20);
    sp = addiu(sp, 0x40);
}

// 0x00508048 _sceFsWaitS -- 44 bytes; frame 0x10: ra sp+0x0
// Take the file I/O semaphore (created on first use); returns 0.
void _sceFsWaitS(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00508048
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x508050u, gen::fn__sceFsSemInit_00507ff0);
    v0 = 0x780000;
    link(ctx, 0x50805Cu);  // $ra first: the delay slot below depends on it
    lw(a0, v0, -2748);
    call(ctx, gen::fn__sceWaitSema_005031a0);
    ld(ra, sp, 0x0);
    v0 = 0;
    sp = addiu(sp, 0x10);
}

// 0x00508078 _sceFsSigSema -- 12 bytes; leaf frame (no stack)
// Release the file I/O semaphore.
void _sceFsSigSema(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00508078
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x780000;
    lw(a0, v0, libs6::lo(libs6::kFioSema));  // 0x77F544
    gen::fn__sceSignalSema_00503180(ctx);  // tail call
}

// 0x00508088 scePowerOffHandler -- 160 bytes; frame 0x60: s3 sp+0x30, s2 sp+0x20, s4 sp+0x40, s0 sp+0x0, ra sp+0x50, s1 sp+0x10
// Install the power-off handler (function, argument, the caller's $gp) under the file semaphore; returns the
// previous function.
void scePowerOffHandler(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00508088
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(s3, sp, 0x30);
    sd(s2, sp, 0x20);
    s3 = a0;
    sd(s4, sp, 0x40);
    s2 = a1;
    sd(s0, sp, 0x0);
    a0 = 27;
    sd(ra, sp, 0x50);
    s0 = 0x970000;
    sd(s1, sp, 0x10);
    s4 = addiu(s0, -25472);  // &0x969C80
    jal(ctx, 0x5080B4u, gen::fn__sceFsWaitS_00508048);
    v0 = 0x780000;
    lw(v1, v0, -2756);  // 0x77F53C
    if (v1 == 0) {
        // 0x005080cc
        charge(ctx, 2);
        jal(ctx, 0x5080CCu, gen::fn_sceFsInit_00508170);
    }
    // 0x005080d4
    charge(ctx, 8);
    jal(ctx, 0x5080D4u, gen::fn_DIntr_0050d3a0);
    lw(s1, s0, -25472);
    v1 = 0x970000;
    sw(s2, s4, 4);
    sw(s3, s0, -25472);
    sw(gp, v1, -25408);  // 0x969CC0
    if (v0 != 0) {
        // 0x005080f4
        charge(ctx, 2);
        jal(ctx, 0x5080F4u, gen::fn_EIntr_0050d3f0);
    }
    // 0x005080fc
    charge(ctx, 11);
    jal(ctx, 0x5080FCu, gen::fn__sceFsSigSema_00508078);
    v0 = s1;
    ld(ra, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00508408 sceFsReset -- 52 bytes; frame 0x10: ra sp+0x0
// Mark the file layer uninitialised and clear its state block.
void sceFsReset(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00508408
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x780000;
    a0 = 0x970000;
    sd(ra, sp, 0x0);
    sw(zero, v0, -2756);  // 0x77F53C
    a0 = addiu(a0, -25560);  // &0x969C28
    a1 = 0;
    a2 = 4;
    jal(ctx, 0x508424u, gen::fn_memset_00521408);
    ld(ra, sp, 0x0);
    v0 = 0;
    sp = addiu(sp, 0x10);
}

// 0x00509908 sceRemove -- 28 bytes; frame 0x10: ra sp+0x0
// remove(name): _sceCallCode 6.
void sceRemove(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00509908
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a1 = 6;
    jal(ctx, 0x509910u, gen::fn__sceCallCode_00509758);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00509AE0 sceRmdir -- 28 bytes; frame 0x10: ra sp+0x0
// rmdir(name): _sceCallCode 8.
void sceRmdir(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00509ae0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a1 = 8;
    jal(ctx, 0x509AE8u, gen::fn__sceCallCode_00509758);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00509EB0 sceDelDrv -- 28 bytes; frame 0x10: ra sp+0x0
// Delete a device driver: _sceCallCode 16.
void sceDelDrv(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00509eb0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a1 = 16;
    jal(ctx, 0x509EB8u, gen::fn__sceCallCode_00509758);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00509ED0 sceDopen -- 200 bytes; frame 0x40: s0 sp+0x0, ra sp+0x30, s2 sp+0x20, s1 sp+0x10
// Open a directory: a new iob, _sceCallCode 9; on success the IOP descriptor goes in the iob and the result is its
// index, on failure the iob is freed. -19 when no iob is free.
void sceDopen(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00509ed0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x30);
    sd(s2, sp, 0x20);
    a0 = 9;
    link(ctx, 0x509EE8u);  // $ra first: the delay slot below depends on it
    sd(s1, sp, 0x10);
    call(ctx, gen::fn__sceFsWaitS_00508048);
    v1 = 0x780000;
    lw(v0, v1, -2756);  // 0x77F53C
    if (v0 == 0) {
        // 0x00509f00
        charge(ctx, 2);
        jal(ctx, 0x509F00u, gen::fn_sceFsInit_00508170);
    }
    // 0x00509f08
    charge(ctx, 7);
    jal(ctx, 0x509F08u, gen::fn__sceFsSigSema_00508078);
    jal(ctx, 0x509F10u, gen::fn_new_iob_00507a50);
    s2 = v0;
    a0 = s0;
    if (s2 != 0) {
        // 0x00509f2c
        charge(ctx, 5);
        a1 = 9;
        jal(ctx, 0x509F2Cu, gen::fn__sceCallCode_00509758);
        s1 = v0;
        s0 = 0x780000;
        if (i64(s1) >= 0) {
            // 0x00509f54
            charge(ctx, 8);
            link(ctx, 0x509F54u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, -2744);
            call(ctx, gen::fn__sceWaitSema_005031a0);
            v1 = 0x970000;
            sw(s1, s2, 0);
            v1 = addiu(v1, -26112);  // &0x969A00
            lw(a0, s0, -2744);
            v1 = subu(s2, v1);
            s1 = sra(v1, 4);
        } else {
            // 0x00509f40
            charge(ctx, 5);
            link(ctx, 0x509F40u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, -2744);
            call(ctx, gen::fn__sceWaitSema_005031a0);
            sw(zero, s2, 4);
            lw(a0, s0, -2744);
        }
        // 0x00509f74
        charge(ctx, 3);
        jal(ctx, 0x509F74u, gen::fn__sceSignalSema_00503180);
        v0 = s1;
    } else {
        // 0x00509f24
        charge(ctx, 2);
        v0 = si(-19);
    }
    // 0x00509f80 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0050A868 sceChdir -- 28 bytes; frame 0x10: ra sp+0x0
// chdir(name): _sceCallCode 18.
void sceChdir(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050a868
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a1 = 18;
    jal(ctx, 0x50A870u, gen::fn__sceCallCode_00509758);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0050ACB8 sceUmount -- 28 bytes; frame 0x10: ra sp+0x0
// Unmount: _sceCallCode 21.
void sceUmount(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050acb8
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a1 = 21;
    jal(ctx, 0x50ACC0u, gen::fn__sceCallCode_00509758);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0050BC78 sceSifLoadFileReset -- 56 bytes; frame 0x10: ra sp+0x0
// Forget the module loader's binding (0x77F560 = -1) and clear its client data.
void sceSifLoadFileReset(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050bc78
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x780000;
    v1 = si(-1);
    a0 = 0x970000;
    sd(ra, sp, 0x0);
    a0 = addiu(a0, -24344);  // &0x96A0E8
    sw(v1, v0, -2720);  // 0x77F560
    a1 = 0;
    a2 = 4;
    jal(ctx, 0x50BC98u, gen::fn_memset_00521408);
    ld(ra, sp, 0x0);
    v0 = 0;
    sp = addiu(sp, 0x10);
}

// 0x0050CB28 SetTLBHandler -- 96 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x10, ra sp+0x20
// Install a TLB exception handler: stores it, points the TLB modified / refill (load, store) vectors 1-3 at
// _kTLBException.
void SetTLBHandler(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050cb28
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x780000;
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x10);
    s0 = 0x510000;
    s0 = addiu(s0, -12224);  // &_kTLBException
    s1 = a0;
    sw(s1, v0, -1896);  // 0x77F898
    a1 = s0;
    sd(ra, sp, 0x20);
    a0 = 1;
    jal(ctx, 0x50CB50u, gen::fn__sceSetVTLBRefillHandler_00502e10);
    a1 = s0;
    a0 = 2;
    jal(ctx, 0x50CB5Cu, gen::fn__sceSetVTLBRefillHandler_00502e10);
    a1 = s0;
    a0 = 3;
    jal(ctx, 0x50CB68u, gen::fn__sceSetVTLBRefillHandler_00502e10);
    v0 = s1;
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0050CB88 SetDebugHandler -- 132 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0
// Install a debug handler for exception codes 1..13: stores it in the table at 0x77F8A0 and points the vector at
// _kDebugException (TLB vectors for 1-3, common for the rest); returns the old one.
void SetDebugHandler(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050cb88
    enter(ctx, 7);  // entry check point + this block's cycles
    a2 = a0;
    sp = addiu(sp, -0x20);
    a0 = addiu(a2, -1);
    sd(ra, sp, 0x10);
    v0 = sltiu(a0, 13);
    sd(s0, sp, 0x0);
    if (v0 != 0) {
        // 0x0050cbb0
        charge(ctx, 8);
        v0 = 0x780000;
        v1 = sll(a2, 2);
        v0 = addiu(v0, -1888);  // &0x77F8A0
        a0 = sltiu(a0, 3);
        v1 = addu(v1, v0);
        lw(s0, v1, 0);
        sw(a1, v1, 0);
        if (a0 == 0) {
            // 0x0050cbe8
            charge(ctx, 5);
            a1 = 0x510000;
            a0 = a2;
            a1 = addiu(a1, -11648);  // &_kDebugException
            jal(ctx, 0x50CBF0u, gen::fn__sceSetVCommonHandler_00502e20);
            v0 = s0;
        } else {
            // 0x0050cbd0
            charge(ctx, 6);
            a1 = 0x510000;
            a0 = a2;
            a1 = addiu(a1, -11648);  // &_kDebugException
            jal(ctx, 0x50CBD8u, gen::fn__sceSetVTLBRefillHandler_00502e10);
            v0 = s0;
        }
    } else {
        // 0x0050cba4
        charge(ctx, 3);
        v0 = lui(0xFFFF);
        v0 = v0 | 0xFFFF;
    }
    // 0x0050cbfc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0050CC20 kCopy -- 56 bytes; leaf frame (no stack)
// Kernel-mode word copy (dst, src, bytes): the syscall body used to patch kernel memory; returns 0.
void kCopy(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0050cc20
    enter(ctx, 3);  // entry check point + this block's cycles
    a2 = srl(a2, 2);
    a3 = 0;
    if (a2 != 0) {
        // 0x0050cc2c
        charge(ctx, 1);
        for (;;) {
            // 0x0050cc30
            charge(ctx, 8);
            lw(v1, a1, 0);
            a3 = addiu(a3, 1);
            a1 = addiu(a1, 4);
            v0 = sltu(a3, a2);
            sw(v1, a0, 0);
            a0 = addiu(a0, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0050cc50 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = 0;
}

// 0x0050CC78 InitTLBFunctions -- 196 bytes; frame 0x40: s2 sp+0x20, s1 sp+0x10, s0 sp+0x0, ra sp+0x30
// Install the TLB kernel patch: kCopy as syscall 0x5A, the payload copied to 0x80075000, the caches flushed, then
// the patch table's syscalls; keeps the kernel's syscall table base.
void InitTLBFunctions(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050cc78
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 0x780000;
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x10);
    s2 = 3;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x30);
    s0 = addiu(v0, -1816);  // &tbl_kpatch_tlb
    lw(a0, v0, -1816);  // tbl_kpatch_tlb
    s1 = addiu(s0, 24);  // &tbl_kpatch_tlb+0x18
    link(ctx, 0x50CCA0u);  // $ra first: the delay slot below depends on it
    lw(a1, s0, 4);  // tbl_kpatch_tlb+0x4
    call(ctx, gen::fn__sceSetSyscall_0050cc68);
    a1 = 0x780000;
    a0 = lui(0x8007);
    a2 = 816;
    a1 = addiu(a1, -2712);  // &0x77F568
    a0 = a0 | 0x5000;
    jal(ctx, 0x50CCB8u, gen::fn__sceCopy_0050cc10);
    a0 = 0;
    jal(ctx, 0x50CCC0u, gen::fn__sceFlushCache_005033e0);
    a0 = 2;
    jal(ctx, 0x50CCC8u, gen::fn__sceFlushCache_005033e0);
    lw(a0, s0, 8);  // tbl_kpatch_tlb+0x8
    link(ctx, 0x50CCD4u);  // $ra first: the delay slot below depends on it
    lw(a1, s0, 12);  // tbl_kpatch_tlb+0xC
    call(ctx, gen::fn__sceSetSyscall_0050cc68);
    lw(a0, s0, 16);  // tbl_kpatch_tlb+0x10
    link(ctx, 0x50CCE0u);  // $ra first: the delay slot below depends on it
    lw(a1, s0, 20);  // tbl_kpatch_tlb+0x14
    call(ctx, gen::fn__sceSetSyscall_0050cc68);
    lw(a0, s1, 0);  // tbl_kpatch_tlb+0x18
    for (;;) {
        // 0x0050ccf0
        charge(ctx, 9);
        s2 = addiu(s2, 1);
        jal(ctx, 0x50CCF0u, gen::fn__sceGetEntryAddress_0050cc58);
        lw(a0, s1, 0);
        a1 = v0;
        s1 = addiu(s1, 8);
        jal(ctx, 0x50CD00u, gen::fn__sceSetSyscall_0050cc68);
        v0 = sltiu(s2, 8);
        if (v0 == 0) {
            break;
        }
        lw(a0, s1, 0);
        backedge(ctx);
    }
    // 0x0050cd14
    charge(ctx, 10);
    a0 = 3;
    jal(ctx, 0x50CD14u, gen::fn__sceGetEntryAddress_0050cc58);
    v1 = 0x780000;
    ld(ra, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sw(v0, v1, -1824);  // g_kernel_syscall_table_base
    sp = addiu(sp, 0x40);
}

// 0x0050CD70 SetTLBEntry -- 48 bytes; frame 0x10: ra sp+0x0
// Set a TLB entry: index 13..47 only (else -1).
void SetTLBEntry(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050cd70
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = addiu(a0, -13);
    v0 = sltiu(v0, 35);
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0050cd8c
        charge(ctx, 2);
        jal(ctx, 0x50CD8Cu, gen::fn__sce_SetTLBEntry_0050cd60);
    } else {
        // 0x0050cd84
        charge(ctx, 2);
        v0 = si(-1);
    }
    // 0x0050cd94 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0050CE00 InitTLB -- 64 bytes; frame 0x10: ra sp+0x0
// Reinitialise the TLB: the 32 MiB layout when the memory size is 32 MiB, else the kernel's.
void InitTLB(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050ce00
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x50CE08u, gen::fn__sceGetMemorySize_005035c0);
    v1 = 0x2000000;
    if (v0 != v1) {
        // 0x0050ce2c
        charge(ctx, 3);
        jal(ctx, 0x50CE2Cu, gen::fn__sce_InitTLB_005035d0);
        ld(ra, sp, 0x0);
    } else {
        // 0x0050ce1c
        charge(ctx, 4);
        jal(ctx, 0x50CE1Cu, gen::fn_InitTLB32MB_0050ce40);
        ld(ra, sp, 0x0);
    }
    // 0x0050ce38 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x0050D37C sub_50D37C -- 32 bytes; frame 0x4E80
// Debug exception dispatch: calls the handler of the cause's exception code (table at 0x77F8A0), then breaks.
// [kDebugExceptionDispatch]
void sub_50D37C(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a1{ctx, 5}, sp{ctx, 29};
    // 0x0050d37c
    enter(ctx, 8);  // entry check point + this block's cycles
    v0 = a1 & 0x7C;
    at = 0x780000;
    at = addu(at, v0);
    lw(at, at, -1888);
    sp = 0x970000;
    sp = addiu(sp, -0x4E80);
    jalr(ctx, 0x50D390u, at.u());
    brk(ctx, 0x50D398u, 0xFFFFFu);
    rt::unreachable(0x50D39Cu);
}

// 0x0050D408 supplement_crt0 -- 96 bytes; frame 0x50: ra sp+0x40
// Create libc's two semaphores ("SceKernelLibc", "SceKernelLibcEh").
void supplement_crt0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050d408
    enter(ctx, 24);  // entry check point + this block's cycles
    v0 = 0x7C0000;
    a1 = 0x7C0000;
    sp = addiu(sp, -0x50);
    v1 = 1;
    v0 = addiu(v0, -8016);  // "SceKernelLibc"
    a1 = addiu(a1, -8000);  // "SceKernelLibcEh"
    sd(ra, sp, 0x40);
    a0 = sp;
    sw(v0, sp, 0x14);
    sw(v1, sp, 0x28);
    sw(a1, sp, 0x34);
    sw(v1, sp, 0x4);
    sw(v1, sp, 0x8);
    link(ctx, 0x50D43Cu);  // $ra first: the delay slot below depends on it
    sw(v1, sp, 0x24);
    call(ctx, gen::fn__sceCreateSema_00503160);
    v1 = 0x780000;
    a0 = addiu(sp, 0x20);
    link(ctx, 0x50D44Cu);  // $ra first: the delay slot below depends on it
    sw(v0, v1, -1072);
    call(ctx, gen::fn__sceCreateSema_00503160);
    v1 = 0x780000;
    ld(ra, sp, 0x40);
    sw(v0, v1, -1068);  // 0x77FBD4
    sp = addiu(sp, 0x50);
}

// 0x0050D488 kCopy_0 -- 56 bytes; leaf frame (no stack)
// Kernel-mode word copy, the copy used by the syscall table search.
void kCopy_0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0050d488
    enter(ctx, 3);  // entry check point + this block's cycles
    a2 = srl(a2, 2);
    a3 = 0;
    if (a2 != 0) {
        // 0x0050d494
        charge(ctx, 1);
        for (;;) {
            // 0x0050d498
            charge(ctx, 8);
            lw(v1, a1, 0);
            a3 = addiu(a3, 1);
            a1 = addiu(a1, 4);
            v0 = sltu(a3, a2);
            sw(v1, a0, 0);
            a0 = addiu(a0, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0050d4b8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = 0;
}

// 0x0050D4C0 kFindAddress -- 64 bytes; leaf frame (no stack)
// Kernel-mode search for a word in [$a0, $a1); returns its address or 0.
void kFindAddress(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050d4c0
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, 0);
    cc = v0 == a2;  // the condition, before the delay slot changes it
    v0 = sltu(a0, a1);
    if (!cc) {
        // 0x0050d4cc
        charge(ctx, 2);
        if (v0 == 0) {
            if (v0 == 0) a0 = 0;
        } else {
            // 0x0050d4d4
            charge(ctx, 1);
            a0 = addiu(a0, 4);
            for (;;) {
                // 0x0050d4d8
                charge(ctx, 3);
                lw(v0, a0, 0);
                cc = v0 == a2;  // the condition, before the delay slot changes it
                v0 = sltu(a0, a1);
                if (cc) {
                    goto L_0050d4f4;
                }
                // 0x0050d4e4
                charge(ctx, 2);
                if (v0 == 0) {
                    break;
                }
                a0 = addiu(a0, 4);
                backedge(ctx);
            }
            // 0x0050d4ec
            charge(ctx, 2);
            if (v0 == 0) a0 = 0;
        }
        // 0x0050d4f8 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = a0;
        return;
    }
L_0050d4f4:
    charge(ctx, 1);
    if (v0 == 0) a0 = 0;
    // 0x0050d4f8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = a0;
}

// 0x0050D510 GetSystemCallEntry -- 52 bytes; frame 0x20: ra sp+0x10
// Read the kernel's syscall table entry n (a kernel-mode copy from the found table).
void GetSystemCallEntry(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050d510
    enter(ctx, 13);  // entry check point + this block's cycles
    v0 = 0x780000;
    sp = addiu(sp, -0x20);
    lw(a1, v0, -1096);  // g_kernel_found_address
    v1 = sll(a0, 2);
    sd(ra, sp, 0x10);
    a0 = sp;
    a2 = 4;
    a1 = addu(a1, v1);
    jal(ctx, 0x50D52Cu, gen::fn__sceCopy_0_0050d478);
    lw(v0, sp, 0x0);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0050D548 InitSystemCallTableAddress -- 252 bytes; frame 0x80: s5 sp+0x50, s4 sp+0x40, s3 sp+0x30, s2 sp+0x20, s1 sp+0x10, s0 sp+0x0, ra sp+0x70, s6 sp+0x60
// Locate the kernel's syscall table: installs the find / copy syscalls, then searches kernel memory for both and
// lines the two results up (0x77FBB8).
void InitSystemCallTableAddress(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050d548
    enter(ctx, 33);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    v0 = 0x780000;
    sd(s5, sp, 0x50);
    sd(s4, sp, 0x40);
    s5 = 0x510000;
    sd(s3, sp, 0x30);
    s4 = 0x510000;
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x70);
    s0 = addiu(v0, -1088);  // &tbl_kpatch_syscalltable
    sd(s6, sp, 0x60);
    lw(a0, v0, -1088);  // tbl_kpatch_syscalltable
    link(ctx, 0x50D580u);  // $ra first: the delay slot below depends on it
    lw(a1, s0, 4);  // tbl_kpatch_syscalltable+0x4
    call(ctx, gen::fn__sceSetSyscall_0_0050d648);
    lw(a1, s0, 12);  // tbl_kpatch_syscalltable+0xC
    link(ctx, 0x50D58Cu);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 8);  // tbl_kpatch_syscalltable+0x8
    call(ctx, gen::fn__sceSetSyscall_0_0050d648);
    a0 = lui(0x8000);
    a1 = lui(0x8008);
    a2 = addiu(s5, -11072);  // &kFindAddress
    jal(ctx, 0x50D59Cu, gen::fn__sceFindAddress_0050d500);
    s3 = v0;
    a0 = lui(0x8000);
    a1 = lui(0x8008);
    a2 = addiu(s4, -11128);  // &kCopy_0
    jal(ctx, 0x50D5B0u, gen::fn__sceFindAddress_0050d500);
    s1 = addiu(s3, -524);
    s2 = v0;
    s0 = addiu(s2, -360);
    s6 = 0x780000;
    if (s1 == s0) {
        // 0x0050d618
        charge(ctx, 1);
        sw(s1, s6, -1096);
    } else {
        // 0x0050d5cc
        charge(ctx, 1);
        v0 = sltu(s1, s0);
        for (;;) {
            // 0x0050d5d0
            charge(ctx, 2);
            a0 = addiu(s3, 4);
            if (v0 == 0) {
                // 0x0050d5f0
                charge(ctx, 6);
                a0 = addiu(s2, 4);
                a1 = lui(0x8008);
                a2 = addiu(s4, -11128);
                jal(ctx, 0x50D5F8u, gen::fn__sceFindAddress_0050d500);
                s2 = v0;
                s0 = addiu(s2, -360);
            } else {
                // 0x0050d5d8
                charge(ctx, 6);
                a1 = lui(0x8008);
                a2 = addiu(s5, -11072);
                jal(ctx, 0x50D5DCu, gen::fn__sceFindAddress_0050d500);
                s3 = v0;
                s1 = addiu(s3, -524);
            }
            // 0x0050d608
            charge(ctx, 2);
            v0 = sltu(s1, s0);
            if (s1 == s0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0050d610
        charge(ctx, 2);
        sw(s1, s6, -1096);
    }
    // 0x0050d61c (the shared epilogue, written out on this path)
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

// 0x0050D658 crt_init_runtime -- 120 bytes, 2 chunks; frame 0x10: ra sp+0x0
// libkernel's runtime start-up: libc semaphores, the syscall table, alarms, timer 2 and the system time, the top
// thread, the ExecPS2 and TLB patches, then the reboot-notify state cleared.
void crt_init_runtime(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050d658
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x50D660u, gen::fn_supplement_crt0_0050d408);
    jal(ctx, 0x50D668u, gen::fn_InitSystemCallTableAddress_0050d548);
    jal(ctx, 0x50D670u, gen::fn_InitAlarm_0050db38);
    a0 = 2;
    jal(ctx, 0x50D678u, gen::fn_InitTimer_0050dcb0);
    jal(ctx, 0x50D680u, gen::fn_StartTimerSystemTime_0050def0);
    jal(ctx, 0x50D688u, gen::fn_InitThread_00503f38);
    jal(ctx, 0x50D690u, gen::fn_InitExecPS2_0050d780);
    jal(ctx, 0x50D698u, gen::fn_InitTLBFunctions_0050cc78);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x0050f3d0
    charge(ctx, 9);
    v0 = 0x780000;
    v1 = 0x780000;
    a0 = 0x970000;
    sw(zero, v0, 2928);  // 0x780B70
    sw(zero, v1, 2932);  // 0x780B74
    a0 = addiu(a0, -10296);  // &0x96D7C8
    a1 = 0;
    a2 = 512;
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x0050D6D0 kCopy_1 -- 56 bytes; leaf frame (no stack)
// Kernel-mode word copy, the ExecPS2 patch's.
void kCopy_1(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0050d6d0
    enter(ctx, 3);  // entry check point + this block's cycles
    a2 = srl(a2, 2);
    a3 = 0;
    if (a2 != 0) {
        // 0x0050d6dc
        charge(ctx, 1);
        for (;;) {
            // 0x0050d6e0
            charge(ctx, 8);
            lw(v1, a1, 0);
            a3 = addiu(a3, 1);
            a1 = addiu(a1, 4);
            v0 = sltu(a3, a2);
            sw(v1, a0, 0);
            a0 = addiu(a0, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0050d700 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = 0;
}

// 0x0050D718 PatchIsNeeded -- 104 bytes; frame 0x30: s0 sp+0x10, ra sp+0x20
// 1 when the kernel needs the ExecPS2 patch: writes the OSD config bits 13-15 as 1, reads them back (0 on an old
// kernel) and restores the config.
void PatchIsNeeded(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050d718
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    sd(ra, sp, 0x20);
    a0 = sp;
    jal(ctx, 0x50D724u, gen::fn__sceGetOsdConfigParam_00503210);
    lw(v1, sp, 0x0);
    v0 = lui(0xFFFF);
    v0 = v0 | 0x1FFF;
    s0 = addiu(sp, 0x4);
    v1 = v1 & v0;
    a0 = s0;
    v1 = v1 | 0x2000;
    link(ctx, 0x50D748u);  // $ra first: the delay slot below depends on it
    sw(v1, sp, 0x4);
    call(ctx, gen::fn__sceSetOsdConfigParam_00503200);
    a0 = s0;
    jal(ctx, 0x50D750u, gen::fn__sceGetOsdConfigParam_00503210);
    a0 = sp;
    jal(ctx, 0x50D758u, gen::fn__sceSetOsdConfigParam_00503200);
    lw(v0, sp, 0x4);
    ld(ra, sp, 0x20);
    v0 = srl(v0, 13);
    ld(s0, sp, 0x10);
    v0 = v0 & 0x7;
    v0 = sltiu(v0, 1);
    sp = addiu(sp, 0x30);
}

// 0x0050D780 InitExecPS2 -- 172 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20, s1 sp+0x10, s0 sp+0x0
// Install the ExecPS2 kernel patch when it is needed: the payload to 0x80074000, caches flushed, the patch table's
// syscalls set.
void InitExecPS2(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050d780
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x10);
    link(ctx, 0x50D790u);  // $ra first: the delay slot below depends on it
    sd(s0, sp, 0x0);
    call(ctx, gen::fn_PatchIsNeeded_0050d718);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 0x780000;
    if (!cc) {
        // 0x0050d7a0
        charge(ctx, 20);
        s2 = 2;
        s0 = addiu(v0, 896);
        lw(a0, v0, 896);
        lw(a1, s0, 4);
        s1 = addiu(s0, 16);
        jal(ctx, 0x50D7B0u, gen::fn__sceSetSyscall_1_0050d6b0);
        a1 = 0x780000;
        a0 = lui(0x8007);
        a2 = 1960;
        a1 = addiu(a1, -1064);  // &kpayload_execps2_80074000
        a0 = a0 | 0x4000;
        jal(ctx, 0x50D7C8u, gen::fn__sceCopy_1_0050d6c0);
        a0 = 0;
        jal(ctx, 0x50D7D0u, gen::fn__sceFlushCache_005033e0);
        a0 = 2;
        jal(ctx, 0x50D7D8u, gen::fn__sceFlushCache_005033e0);
        lw(a0, s0, 8);
        link(ctx, 0x50D7E4u);  // $ra first: the delay slot below depends on it
        lw(a1, s0, 12);
        call(ctx, gen::fn__sceSetSyscall_1_0050d6b0);
        lw(a0, s1, 0);
        for (;;) {
            // 0x0050d7f0
            charge(ctx, 9);
            s2 = addiu(s2, 1);
            jal(ctx, 0x50D7F0u, gen::fn__sceGetEntryAddress_0_0050d708);
            lw(a0, s1, 0);
            a1 = v0;
            s1 = addiu(s1, 8);
            jal(ctx, 0x50D800u, gen::fn__sceSetSyscall_1_0050d6b0);
            v0 = sltiu(s2, 3);
            if (v0 == 0) {
                break;
            }
            lw(a0, s1, 0);
            backedge(ctx);
        }
    }
    // 0x0050d814 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0050D880 SetArg -- 280 bytes; frame 0x80: s3 sp+0x40, s5 sp+0x60, s4 sp+0x50, s2 sp+0x30, s1 sp+0x20, s0 sp+0x10, ra sp+0x70
// Copy ExecPS2's argument strings into the kernel's argument area (the program name then up to 15 arguments, each
// through a kernel-mode copy); returns the area.
void SetArg(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050d880
    enter(ctx, 40);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    v0 = 0x780000;
    sd(s3, sp, 0x40);
    v1 = 0x780000;
    lw(s3, v0, -1824);  // g_kernel_syscall_table_base
    a3 = addiu(v1, 920);  // &tbl_kpatch_setarg_syscall
    sd(s5, sp, 0x60);
    sd(s4, sp, 0x50);
    v0 = addiu(s3, 64);
    sd(s2, sp, 0x30);
    s5 = v0;
    sd(s1, sp, 0x20);
    s2 = a1;
    sd(s0, sp, 0x10);
    s4 = a2;
    sd(ra, sp, 0x70);
    s0 = a0;
    lw(a0, v1, 920);  // tbl_kpatch_setarg_syscall
    lw(a1, a3, 4);  // 0x78039C
    link(ctx, 0x50D8CCu);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x0);
    call(ctx, gen::fn__sceSetSyscall_2_0050d870);
    v1 = slti(s2, 16);
    v0 = 15;
    a0 = s3;
    if (v1 == 0) s2 = v0;
    a1 = sp;
    a2 = 4;
    jal(ctx, 0x50D8E8u, gen::fn__sceCopy_2_0050d830);
    s3 = addiu(s3, 4);
    a0 = s0;
    jal(ctx, 0x50D8F4u, gen::fn_strlen_00524388);
    s1 = addiu(v0, 1);
    lw(a0, sp, 0x0);
    a1 = s0;
    a2 = s1;
    jal(ctx, 0x50D908u, gen::fn__sceCopy_2_0050d830);
    lw(v1, sp, 0x0);
    v1 = addu(v1, s1);
    sw(v1, sp, 0x0);
    if (i64(s2) > 0) {
        // 0x0050d920
        charge(ctx, 2);
        s0 = s4;
        for (;;) {
            // 0x0050d928
            charge(ctx, 18);
            a0 = s3;
            a1 = sp;
            a2 = 4;
            s3 = addiu(s3, 4);
            jal(ctx, 0x50D934u, gen::fn__sceCopy_2_0050d830);
            s2 = addiu(s2, -1);
            link(ctx, 0x50D940u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 0);
            call(ctx, gen::fn_strlen_00524388);
            s1 = addiu(v0, 1);
            lw(a1, s0, 0);
            lw(a0, sp, 0x0);
            a2 = s1;
            s0 = addiu(s0, 4);
            jal(ctx, 0x50D958u, gen::fn__sceCopy_2_0050d830);
            lw(v1, sp, 0x0);
            v1 = addu(v1, s1);
            sw(v1, sp, 0x0);
            if (s2 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0050d970 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    v0 = s5;
    ld(ra, sp, 0x70);
    ld(s5, sp, 0x60);
    ld(s4, sp, 0x50);
    ld(s3, sp, 0x40);
    ld(s2, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x80);
}

// 0x0050D998 sub_50D998 -- 8 bytes; leaf frame (no stack)
// Thunk to InitTLB (the exec paths call it before leaving the program). [ResetTLB]
void sub_50D998(EEContext& ctx) {
    using namespace hg;
    // 0x0050d998
    enter(ctx, 2);  // entry check point + this block's cycles
    gen::fn_InitTLB_0050ce00(ctx);  // tail call
}

// 0x0050D9A0 ExecPS2 -- 112 bytes; frame 0x40: s1 sp+0x10, s2 sp+0x20, s0 sp+0x0, ra sp+0x30
// Execute a loaded program: arguments into the kernel area, the TLB reset, then the ExecPS2 syscall.
void ExecPS2(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050d9a0
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s1, sp, 0x10);
    s1 = a0;
    sd(s2, sp, 0x20);
    sd(s0, sp, 0x0);
    s2 = a1;
    s0 = a2;
    a0 = 0x7C0000;
    a1 = s0;
    sd(ra, sp, 0x30);
    a0 = addiu(a0, -7984);  // &0x7BE0D0
    a2 = a3;
    jal(ctx, 0x50D9CCu, gen::fn_SetArg_0050d880);
    jal(ctx, 0x50D9D4u, gen::fn_sub_50D998_0050d998);
    v0 = 0x780000;
    a0 = s1;
    lw(a3, v0, -1824);  // g_kernel_syscall_table_base
    a1 = s2;
    a2 = s0;
    a3 = addiu(a3, 4);
    jal(ctx, 0x50D9F0u, gen::fn__sce_ExecPS2_00502db0);
    ld(ra, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0050DAF0 kCopy_3 -- 56 bytes; leaf frame (no stack)
// Kernel-mode word copy, a fourth copy of kCopy.
void kCopy_3(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0050daf0
    enter(ctx, 3);  // entry check point + this block's cycles
    a2 = srl(a2, 2);
    a3 = 0;
    if (a2 != 0) {
        // 0x0050dafc
        charge(ctx, 1);
        for (;;) {
            // 0x0050db00
            charge(ctx, 8);
            lw(v1, a1, 0);
            a3 = addiu(a3, 1);
            a1 = addiu(a1, 4);
            v0 = sltu(a3, a2);
            sw(v1, a0, 0);
            a0 = addiu(a0, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0050db20 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = 0;
}

// 0x0050DE08 sub_50DE08 -- 184 bytes; frame 0x40: s2 sp+0x20, s0 sp+0x0, ra sp+0x30, s1 sp+0x10
// Shut the system timer down: when it is set up and no counter is in use, removes the timer 2 interrupt handler,
// disables it and stops the counter. [EndTimer]
void sub_50DE08(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050de08
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s2, sp, 0x20);
    sd(s0, sp, 0x0);
    s2 = 0x780000;
    sd(ra, sp, 0x30);
    s0 = addiu(s2, 2888);  // &0x780B48
    sd(s1, sp, 0x10);
    lw(v0, s0, 8);  // 0x780B50
    if (i64(v0) >= 0) {
        // 0x0050de3c
        charge(ctx, 3);
        lw(v0, s0, 16);
        if (v0 == 0) {
            // 0x0050de54
            charge(ctx, 8);
            jal(ctx, 0x50DE54u, gen::fn_DIntr_0050d3a0);
            lw(a1, s0, 8);
            s1 = v0;
            a0 = 11;
            jal(ctx, 0x50DE64u, gen::fn__sceRemoveIntcHandler_00502e60);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = si(-1);
            if (!cc) {
                // 0x0050de74
                charge(ctx, 7);
                a0 = 11;
                jal(ctx, 0x50DE74u, gen::fn_DisableIntc_00503c40);
                a0 = 3072;
                jal(ctx, 0x50DE7Cu, gen::fn_sub_50DC90_0050dc90);
                a0 = 0;
                jal(ctx, 0x50DE84u, gen::fn_sub_50DC80_0050dc80);
                v0 = si(-1);
            }
            // 0x0050de90
            charge(ctx, 3);
            sd(zero, s2, 2888);
            sw(v0, s0, 8);
            if (s1 != 0) {
                // 0x0050de9c
                charge(ctx, 2);
                jal(ctx, 0x50DE9Cu, gen::fn_EIntr_0050d3f0);
            }
            // 0x0050dea4
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x0050de48
            charge(ctx, 3);
            v0 = lui(0x8000);
            v0 = v0 | 0x10;
        }
    } else {
        // 0x0050de30
        charge(ctx, 3);
        v0 = lui(0x8000);
        v0 = v0 | 0x8001;
    }
    // 0x0050dea8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0050E648 sub_50E648 -- 72 bytes; frame 0x30: s1 sp+0x10, s0 sp+0x0, ra sp+0x20
// Allocate a timer counter with interrupts off (the i-form inside). [AllocTimerCounter]
void sub_50E648(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050e648
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x20);
    jal(ctx, 0x50E658u, gen::fn_DIntr_0050d3a0);
    s0 = v0;
    jal(ctx, 0x50E660u, gen::fn_sub_50E5D8_0050e5d8);
    s1 = v0;
    if (s0 != 0) {
        // 0x0050e670
        charge(ctx, 2);
        jal(ctx, 0x50E670u, gen::fn_EIntr_0050d3f0);
    }
    // 0x0050e678 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s1;
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0050E750 sub_50E750 -- 76 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x10, ra sp+0x20
// Free a timer counter with interrupts off. [FreeTimerCounter]
void sub_50E750(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050e750
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x10);
    sd(ra, sp, 0x20);
    s0 = a0;
    jal(ctx, 0x50E760u, gen::fn_DIntr_0050d3a0);
    a0 = s0;
    s1 = v0;
    jal(ctx, 0x50E76Cu, gen::fn_sub_50E690_0050e690);
    s0 = v0;
    if (s1 != 0) {
        // 0x0050e77c
        charge(ctx, 2);
        jal(ctx, 0x50E77Cu, gen::fn_EIntr_0050d3f0);
    }
    // 0x0050e784 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s0;
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0050E7F0 sub_50E7F0 -- 92 bytes; frame 0x40: s1 sp+0x10, s0 sp+0x0, s2 sp+0x20, ra sp+0x30
// A timer counter query with interrupts off (two arguments, sub_50E7A0 inside). [GetTimerUsedUnusedCounters]
void sub_50E7F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050e7f0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    s1 = a1;
    sd(s2, sp, 0x20);
    sd(ra, sp, 0x30);
    s0 = a0;
    jal(ctx, 0x50E808u, gen::fn_DIntr_0050d3a0);
    a0 = s0;
    s2 = v0;
    a1 = s1;
    jal(ctx, 0x50E818u, gen::fn_sub_50E7A0_0050e7a0);
    s0 = v0;
    if (s2 != 0) {
        // 0x0050e828
        charge(ctx, 2);
        jal(ctx, 0x50E828u, gen::fn_EIntr_0050d3f0);
    }
    // 0x0050e830 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = s0;
    ld(ra, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0050E900 sub_50E900 -- 76 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x10, ra sp+0x20
// Start a timer counter with interrupts off. [StartTimerCounter]
void sub_50E900(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050e900
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x10);
    sd(ra, sp, 0x20);
    s0 = a0;
    jal(ctx, 0x50E910u, gen::fn_DIntr_0050d3a0);
    a0 = s0;
    s1 = v0;
    jal(ctx, 0x50E91Cu, gen::fn_sub_50E850_0050e850);
    s0 = v0;
    if (s1 != 0) {
        // 0x0050e92c
        charge(ctx, 2);
        jal(ctx, 0x50E92Cu, gen::fn_EIntr_0050d3f0);
    }
    // 0x0050e934 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s0;
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0050EA30 sub_50EA30 -- 76 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x10, ra sp+0x20
// Stop a timer counter with interrupts off. [StopTimerCounter]
void sub_50EA30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050ea30
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x10);
    sd(ra, sp, 0x20);
    s0 = a0;
    jal(ctx, 0x50EA40u, gen::fn_DIntr_0050d3a0);
    a0 = s0;
    s1 = v0;
    jal(ctx, 0x50EA4Cu, gen::fn_sub_50E950_0050e950);
    s0 = v0;
    if (s1 != 0) {
        // 0x0050ea5c
        charge(ctx, 2);
        jal(ctx, 0x50EA5Cu, gen::fn_EIntr_0050d3f0);
    }
    // 0x0050ea64 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s0;
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0050EA80 sub_50EA80 -- 204 bytes; frame 0x50: s1 sp+0x10, s2 sp+0x20, s0 sp+0x0, s3 sp+0x30, ra sp+0x40
// Set a timer counter's accumulated time: returns the old total (the running stretch included, the start
// re-stamped) or -1 for a bad id. Interrupts off. [SetTimerCount]
void sub_50EA80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050ea80
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s1, sp, 0x10);
    s1 = a0;
    sd(s2, sp, 0x20);
    sd(s0, sp, 0x0);
    v0 = srl(s1, 10);
    sd(s3, sp, 0x30);
    s2 = a1;
    sd(ra, sp, 0x40);
    s0 = sll(v0, 6);
    jal(ctx, 0x50EAA4u, gen::fn_DIntr_0050d3a0);
    s3 = v0;
    if (i64(s1) >= 0) {
        // 0x0050eab4
        charge(ctx, 4);
        lw(v1, s0, 8);
        v0 = s1 & 0x3FF;
        cc = v0 != v1;  // the condition, before the delay slot changes it
        v0 = 0x780000;
        if (cc) {
            goto L_0050ead4;
        }
        // 0x0050eac4
        charge(ctx, 4);
        v0 = addiu(v0, 2888);
        lw(v1, v0, 28);
        if (v1 == s1) {
            goto L_0050ead4;
        }
        lw(v0, s0, 12);
        // 0x0050eaec
        charge(ctx, 3);
        v0 = v0 & 0x1;
        ld(s1, s0, 24);
        if (v0 == 0) {
            // 0x0050eb18
            charge(ctx, 1);
            sd(s2, s0, 24);
        } else {
            // 0x0050eaf8
            charge(ctx, 8);
            jal(ctx, 0x50EAF8u, gen::fn_sub_50E508_0050e508);
            ld(v1, s0, 16);
            sd(s2, s0, 24);
            v1 = v0 - v1;
            sd(v0, s0, 16);
            s1 = s1 + v1;
        }
        // 0x0050eb1c
        charge(ctx, 2);
        v0 = s1;
        if (s3 != 0) {
            // 0x0050eb24
            charge(ctx, 3);
            jal(ctx, 0x50EB24u, gen::fn_EIntr_0050d3f0);
            v0 = s1;
        }
        // 0x0050eb30 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x40);
        ld(s3, sp, 0x30);
        ld(s2, sp, 0x20);
        ld(s1, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_0050ead4:
    charge(ctx, 2);
    v0 = si(-1);
    if (s3 != 0) {
        // 0x0050eadc
        charge(ctx, 4);
        jal(ctx, 0x50EADCu, gen::fn_EIntr_0050d3f0);
        v0 = si(-1);
    }
    // 0x0050eb30 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0050EB98 sub_50EB98 -- 76 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x10, ra sp+0x20
// A timer counter's base time with interrupts off (sub_50EB50 inside). [GetTimerBaseTime]
void sub_50EB98(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050eb98
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x10);
    sd(ra, sp, 0x20);
    s0 = a0;
    jal(ctx, 0x50EBA8u, gen::fn_DIntr_0050d3a0);
    a0 = s0;
    s1 = v0;
    jal(ctx, 0x50EBB4u, gen::fn_sub_50EB50_0050eb50);
    s0 = v0;
    if (s1 != 0) {
        // 0x0050ebc4
        charge(ctx, 2);
        jal(ctx, 0x50EBC4u, gen::fn_EIntr_0050d3f0);
    }
    // 0x0050ebcc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s0;
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0050EC58 sub_50EC58 -- 76 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x10, ra sp+0x20
// A timer counter's total time with interrupts off. [GetTimerCount]
void sub_50EC58(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050ec58
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x10);
    sd(ra, sp, 0x20);
    s0 = a0;
    jal(ctx, 0x50EC68u, gen::fn_DIntr_0050d3a0);
    a0 = s0;
    s1 = v0;
    jal(ctx, 0x50EC74u, gen::fn_sub_50EBE8_0050ebe8);
    s0 = v0;
    if (s1 != 0) {
        // 0x0050ec84
        charge(ctx, 2);
        jal(ctx, 0x50EC84u, gen::fn_EIntr_0050d3f0);
    }
    // 0x0050ec8c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s0;
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0050EDB8 sub_50EDB8 -- 124 bytes; frame 0x60: s3 sp+0x30, s2 sp+0x20, s1 sp+0x10, s0 sp+0x0, s4 sp+0x40, ra sp+0x50
// Arm a timer counter's handler with interrupts off. [SetTimerHandler]
void sub_50EDB8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050edb8
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(s3, sp, 0x30);
    sd(s2, sp, 0x20);
    s3 = a3;
    sd(s1, sp, 0x10);
    s2 = a2;
    sd(s0, sp, 0x0);
    s1 = a1;
    sd(s4, sp, 0x40);
    sd(ra, sp, 0x50);
    s0 = a0;
    jal(ctx, 0x50EDE0u, gen::fn_DIntr_0050d3a0);
    a0 = s0;
    s4 = v0;
    a1 = s1;
    a2 = s2;
    a3 = s3;
    jal(ctx, 0x50EDF8u, gen::fn_sub_50ECA8_0050eca8);
    s0 = v0;
    if (s4 != 0) {
        // 0x0050ee08
        charge(ctx, 2);
        jal(ctx, 0x50EE08u, gen::fn_EIntr_0050d3f0);
    }
    // 0x0050ee10 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = s0;
    ld(ra, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0050F090 SetTimerAlarm -- 300 bytes; frame 0x80: s6 sp+0x60, s5 sp+0x50, s4 sp+0x40, ra sp+0x70, s3 sp+0x30, s2 sp+0x20, s1 sp+0x10, s0 sp+0x0
// Thread-context alarm: an alarm record from the free list (0x96D7C0), a counter allocated, armed with AlarmHandler
// and started; returns record << 4 | tag | 1, or an error code.
void SetTimerAlarm(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050f090
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(s6, sp, 0x60);
    sd(s5, sp, 0x50);
    s6 = a0;
    sd(s4, sp, 0x40);
    s5 = a2;
    sd(ra, sp, 0x70);
    s4 = a1;
    sd(s3, sp, 0x30);
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    if (s4 != 0) {
        // 0x0050f0d0
        charge(ctx, 5);
        s2 = 0x970000;
        jal(ctx, 0x50F0D0u, gen::fn_DIntr_0050d3a0);
        lw(s0, s2, libs6::lo(libs6::kAlarmFreeList));  // 0x96D7C0
        s3 = v0;
        if (s0 != 0) {
            // 0x0050f0e4
            charge(ctx, 2);
            lw(v0, s0, 0);
            sw(v0, s2, -10304);
        }
        // 0x0050f0ec
        charge(ctx, 2);
        if (s0 != 0) {
            // 0x0050f110
            charge(ctx, 5);
            jal(ctx, 0x50F110u, gen::fn_sub_50E648_0050e648);
            s1 = v0;
            if (i64(s1) >= 0) {
                sw(s4, s0, 8);
                // 0x0050f14c
                charge(ctx, 12);
                a2 = 0x510000;
                sw(s5, s0, 12);
                a2 = addiu(a2, -4048);  // &AlarmHandler
                sw(s1, s0, 4);
                a1 = s6;
                a0 = s1;
                a3 = s0;
                jal(ctx, 0x50F164u, gen::fn_sub_50EDB8_0050edb8);
                a0 = s1;
                jal(ctx, 0x50F16Cu, gen::fn_sub_50E900_0050e900);
                v0 = sll(s0, 4);
                if (s3 != 0) {
                    // 0x0050f17c
                    charge(ctx, 3);
                    jal(ctx, 0x50F17Cu, gen::fn_EIntr_0050d3f0);
                    v0 = sll(s0, 4);
                }
                // 0x0050f188
                charge(ctx, 3);
                v1 = s1 & 0xFE;
                v0 = v0 | v1;
                v0 = v0 | 0x1;
            } else {
                // 0x0050f124
                charge(ctx, 6);
                lw(v0, s2, -10304);
                sw(s0, s2, -10304);
                sw(v0, s0, 0);
                sw(zero, s0, 4);
                v0 = s1;
                if (s3 != 0) {
                    // 0x0050f13c
                    charge(ctx, 4);
                    jal(ctx, 0x50F13Cu, gen::fn_EIntr_0050d3f0);
                    v0 = s1;
                }
            }
        } else {
            // 0x0050f0f4
            charge(ctx, 2);
            if (s3 != 0) {
                // 0x0050f0fc
                charge(ctx, 2);
                jal(ctx, 0x50F0FCu, gen::fn_EIntr_0050d3f0);
            }
            // 0x0050f104
            charge(ctx, 3);
            v0 = lui(0x8000);
            v0 = v0 | 0x8005;
        }
    } else {
        // 0x0050f0c4
        charge(ctx, 3);
        v0 = lui(0x8000);
        v0 = v0 | 0x16;
    }
    // 0x0050f194 (the shared epilogue, written out on this path)
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

// 0x0050F2B0 ReleaseTimerAlarm -- 168 bytes; frame 0x40: s0 sp+0x0, s1 sp+0x10, s2 sp+0x20, ra sp+0x30
// Release an alarm: checks the tag, frees its counter and returns the record to the free list.
void ReleaseTimerAlarm(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050f2b0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x10);
    v0 = srl(s0, 8);
    sd(s2, sp, 0x20);
    sd(ra, sp, 0x30);
    s1 = sll(v0, 4);
    jal(ctx, 0x50F2CCu, gen::fn_DIntr_0050d3a0);
    s2 = v0;
    if (i64(s0) >= 0) {
        // 0x0050f2dc
        charge(ctx, 5);
        lw(v0, s1, 4);
        v0 = s0 ^ v0;
        v0 = v0 & 0xFF;
        if (v0 != 0) {
            goto L_0050f2f0;
        }
        // 0x0050f30c
        charge(ctx, 10);
        lw(a0, s1, 4);
        jal(ctx, 0x50F310u, gen::fn_sub_50E750_0050e750);
        v1 = 0x970000;
        lw(v0, v1, libs6::lo(libs6::kAlarmFreeList));  // 0x96D7C0
        sw(s1, v1, libs6::lo(libs6::kAlarmFreeList));  // 0x96D7C0
        sw(v0, s1, 0);
        sw(zero, s1, 4);
        v0 = 0;
        if (s2 != 0) {
            // 0x0050f334
            charge(ctx, 3);
            jal(ctx, 0x50F334u, gen::fn_EIntr_0050d3f0);
            v0 = 0;
        }
        // 0x0050f340 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x30);
        ld(s2, sp, 0x20);
        ld(s1, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_0050f2f0:
    charge(ctx, 2);
    if (s2 != 0) {
        // 0x0050f2f8
        charge(ctx, 2);
        jal(ctx, 0x50F2F8u, gen::fn_EIntr_0050d3f0);
    }
    // 0x0050f300
    charge(ctx, 3);
    v0 = lui(0x8000);
    v0 = v0 | 0x8002;
    // 0x0050f340 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0050F3F8 sceSifSetRebootNotifyBuffer -- 124 bytes; frame 0x50: s1 sp+0x10, s0 sp+0x0, s3 sp+0x30, s2 sp+0x20, ra sp+0x40
// Install the user reboot-notify table (address, count; cleared); returns the old one.
void sceSifSetRebootNotifyBuffer(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050f3f8
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    s1 = a1;
    sd(s3, sp, 0x30);
    sd(s2, sp, 0x20);
    sd(ra, sp, 0x40);
    s0 = a0;
    jal(ctx, 0x50F414u, gen::fn_DIntr_0050d3a0);
    v1 = 0x780000;
    a1 = 0x780000;
    lw(s3, v1, 2928);  // 0x780B70
    s2 = v0;
    sw(s1, a1, 2932);  // 0x780B74
    a0 = s0;
    sw(s0, v1, 2928);  // 0x780B70
    a2 = sll(s1, 4);
    a1 = 0;
    jal(ctx, 0x50F43Cu, gen::fn_memset_00521408);
    v0 = s3;
    if (s2 != 0) {
        // 0x0050f44c
        charge(ctx, 3);
        jal(ctx, 0x50F44Cu, gen::fn_EIntr_0050d3f0);
        v0 = s3;
    }
    // 0x0050f458 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0050F478 sceSifAddRebootNotifyHandler -- 184 bytes; frame 0x50: s3 sp+0x30, s2 sp+0x20, s0 sp+0x0, ra sp+0x40, s1 sp+0x10
// Set a reboot-notify entry (function, argument, the caller's $gp): a non-negative index in the user table, a
// negative one in the 32-entry system table.
void sceSifAddRebootNotifyHandler(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050f478
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s3, sp, 0x30);
    sd(s2, sp, 0x20);
    s3 = a2;
    sd(s0, sp, 0x0);
    s2 = a1;
    sd(ra, sp, 0x40);
    s0 = a0;
    sd(s1, sp, 0x10);
    if (i64(s0) >= 0) {
        // 0x0050f4bc
        charge(ctx, 4);
        v0 = 0x780000;
        v1 = 0x780000;
        lw(s1, v0, 2928);  // 0x780B70
        lw(v0, v1, 2932);  // 0x780B74
    } else {
        // 0x0050f4a0
        charge(ctx, 7);
        v0 = 0x7FFF0000;
        v1 = 0x970000;
        v0 = v0 | 0xFFFF;
        s1 = addiu(v1, -10296);  // &0x96D7C8
        s0 = s0 & v0;
        v0 = 32;
    }
    // 0x0050f4cc
    charge(ctx, 3);
    v0 = sltu(s0, v0);
    if (v0 != 0) {
        // 0x0050f4e4
        charge(ctx, 9);
        jal(ctx, 0x50F4E4u, gen::fn_DIntr_0050d3a0);
        v1 = sll(s0, 4);
        v1 = addu(v1, s1);
        sw(s2, v1, 0);
        sw(s3, v1, 4);
        a0 = gp;
        sw(a0, v1, 8);
        if (v0 != 0) {
            // 0x0050f508
            charge(ctx, 2);
            jal(ctx, 0x50F508u, gen::fn_EIntr_0050d3f0);
        }
        // 0x0050f510
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0050f4d8
        charge(ctx, 3);
        v0 = lui(0x8000);
        v0 = v0 | 0x69;
    }
    // 0x0050f514 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0050F530 sceSifRemoveRebootNotifyHandler -- 84 bytes; leaf frame (no stack)
// Clear a reboot-notify entry (same index rule); -105 when out of range.
void sceSifRemoveRebootNotifyHandler(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0050f530
    enter(ctx, 2);  // entry check point + this block's cycles
    if (i64(a0) >= 0) {
        v0 = 0x780000;
        // 0x0050f554
        charge(ctx, 3);
        v1 = 0x780000;
        lw(a1, v0, 2928);
        lw(v0, v1, 2932);  // 0x780B74
    } else {
        // 0x0050f538
        charge(ctx, 7);
        v0 = 0x7FFF0000;
        v1 = 0x970000;
        v0 = v0 | 0xFFFF;
        a1 = addiu(v1, -10296);  // &0x96D7C8
        a0 = a0 & v0;
        v0 = 32;
    }
    // 0x0050f560
    charge(ctx, 3);
    v0 = sltu(a0, v0);
    v1 = sll(a0, 4);
    if (v0 == 0) {
        // 0x0050f56c
        charge(ctx, 2);
        v0 = si(-105);
        return;
    }
    // 0x0050f574
    charge(ctx, 4);
    v0 = 0;
    v1 = addu(v1, a1);
    sw(zero, v1, 0);
}

// 0x0050F588 sceSifExecNotifyHandler -- 168 bytes; frame 0x50: s3 sp+0x30, ra sp+0x40, s2 sp+0x20, s1 sp+0x10, s0 sp+0x0
// Call every reboot-notify handler of the system ($a0 != 0) or user table with ($a1, its argument) and its $gp.
void sceSifExecNotifyHandler(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0050f588
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s3, sp, 0x30);
    sd(ra, sp, 0x40);
    s3 = a1;
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    if (a0 == 0) {
        // 0x0050f5b8
        charge(ctx, 4);
        v0 = 0x780000;
        v1 = 0x780000;
        lw(v0, v0, 2928);  // 0x780B70
        lw(v1, v1, 2932);  // 0x780B74
    } else {
        // 0x0050f5a8
        charge(ctx, 4);
        v0 = 0x970000;
        v1 = 32;
        v0 = addiu(v0, -10296);  // &0x96D7C8
    }
    // 0x0050f5c8
    charge(ctx, 3);
    s2 = gp;
    s0 = v0;
    if (i64(v1) > 0) {
        // 0x0050f5d4
        charge(ctx, 1);
        s1 = v1;
        for (;;) {
            // 0x0050f5d8
            charge(ctx, 3);
            lw(v0, s0, 0);
            if (v0 == 0) {
                s1 = addiu(s1, -1);
            } else {
                // 0x0050f5e4
                charge(ctx, 8);
                lw(v0, s0, 8);
                v1 = gp;
                gp = v0;
                lw(a2, s0, 0);
                a0 = s3;
                jt = a2.u();  // the target, read before the delay slot
                link(ctx, 0x50F5F8u);  // $ra = the return address
                lw(a1, s0, 4);
                call_ptr(ctx, jt);
                s1 = addiu(s1, -1);
            }
            // 0x0050f604
            charge(ctx, 2);
            s0 = addiu(s0, 16);
            if (s1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0050f60c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = gp;
    gp = s2;
    ld(ra, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0050F698 _sceCd_cd_callback -- 160 bytes; frame 0x20: s0 sp+0x0, ra sp+0x10
// CD/DVD command-end interrupt: records the function number; 11 just clears the state, others signal the N-command
// semaphore and the callback thread's semaphore when a callback is set.
void _sceCd_cd_callback(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050f698
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 11;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s0 = 0x780000;
    lw(v1, a0, 0);
    a0 = 0x780000;
    sw(v1, s0, 3040);  // sceCdCbfunc_num
    lw(v0, s0, 3040);  // sceCdCbfunc_num
    sw(v0, a0, 3044);  // 0x780BE4
    lw(v1, s0, 3040);  // sceCdCbfunc_num
    v0 = 0x780000;
    if (v1 != a1) {
        // 0x0050f6e0
        charge(ctx, 7);
        lw(a0, v0, 2984);
        jal(ctx, 0x50F6E4u, gen::fn__sceiSignalSema_00503190);
        v1 = 0x780000;
        lw(v0, v1, 2964);  // 0x780B94
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 0x970000;
        if (!cc) {
            // 0x0050f6fc
            charge(ctx, 3);
            lw(v1, v0, -9728);
            v0 = 0x780000;
            if (v1 == 0) {
                goto L_0050f71c;
            }
            // 0x0050f708
            charge(ctx, 5);
            lw(a0, v0, 2976);
            jal(ctx, 0x50F70Cu, gen::fn__sceiSignalSema_00503190);
            goto L_0050f724;
        }
    L_0050f71c:
        charge(ctx, 2);
        v0 = 0x780000;
        sw(zero, v0, 2996);  // sceCd_c_cb_sem
    L_0050f724:
        charge(ctx, 2);
        sw(zero, s0, 3040);
        ld(ra, sp, 0x10);
    } else {
        // 0x0050f6cc
        charge(ctx, 5);
        sw(zero, s0, 3040);
        v0 = 0x780000;
        sw(zero, v0, 2996);  // sceCd_c_cb_sem
        ld(ra, sp, 0x10);
    }
    // 0x0050f72c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0050F738 _sceCd_cbLoop -- 208 bytes; frame 0xA0: fp sp+0x80, s7 sp+0x70, s6 sp+0x60, s5 sp+0x50, s4 sp+0x40, s3 sp+0x30, s2 sp+0x20, s1 sp+0x10, ra sp+0x90, s0 sp+0x0
// The CD/DVD callback thread: waits on its semaphore, calls the user callback with the finished function number; -1
// exits and deletes the thread.
void _sceCd_cbLoop(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050f738
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(fp, sp, 0x80);
    sd(s7, sp, 0x70);
    fp = 0x970000;
    sd(s6, sp, 0x60);
    s7 = 0x780000;
    sd(s5, sp, 0x50);
    s6 = 0x7C0000;
    sd(s4, sp, 0x40);
    s5 = 0x970000;
    sd(s3, sp, 0x30);
    s4 = 0x780000;
    sd(s2, sp, 0x20);
    s3 = 0x780000;
    sd(s1, sp, 0x10);
    s2 = 0x970000;
    sd(ra, sp, 0x90);
    s1 = 0x780000;
    sd(s0, sp, 0x0);
    v0 = 0x780000;
    for (;;) {
        // 0x0050f788
        charge(ctx, 6);
        link(ctx, 0x50F788u);  // $ra first: the delay slot below depends on it
        lw(a0, v0, 2976);
        call(ctx, gen::fn__sceWaitSema_005031a0);
        lw(v1, s4, 3040);
        v0 = si(-1);
        cc = v1 != v0;  // the condition, before the delay slot changes it
        lw(v0, s7, 2960);
        if (!cc) {
            // 0x0050f7a0
            charge(ctx, 7);
            sw(zero, s3, 2996);
            v0 = 0x780000;
            sw(zero, s4, 3040);
            sw(zero, v0, 2964);  // 0x780B94
            link(ctx, 0x50F7B0u);  // $ra first: the delay slot below depends on it
            sw(zero, fp, -0x25EC);
            call(ctx, gen::fn__sceExitDeleteThread_00502fa0);
            lw(v0, s7, 2960);
        }
        // 0x0050f7bc
        charge(ctx, 2);
        a0 = addiu(s6, -7976);
        if (i64(v0) > 0) {
            // 0x0050f7c4
            charge(ctx, 3);
            lw(a1, s2, -9728);
            link(ctx, 0x50F7C8u);  // $ra first: the delay slot below depends on it
            lw(a2, s1, 3044);
            call(ctx, gen::fn_scePrintf_00505e48);
        }
        // 0x0050f7d0
        charge(ctx, 3);
        lw(v1, s2, -9728);
        if (v1 != 0) {
            // 0x0050f7dc
            charge(ctx, 3);
            lw(v0, s1, 3044);
            if (v0 == 0) {
                goto L_0050f7fc;
            }
            // 0x0050f7e8
            charge(ctx, 5);
            s0 = gp;
            lw(gp, s5, -9724);
            jt = v1.u();  // the target, read before the delay slot
            link(ctx, 0x50F7F0u);  // $ra = the return address
            lw(a0, s1, 3044);
            call_ptr(ctx, jt);
            gp = s0;
            goto L_0050f7fc;
        }
    L_0050f7fc:
        charge(ctx, 3);
        sw(zero, s3, 2996);
        v0 = 0x780000;
        backedge(ctx);
    }
}

// 0x0050F808 sceCdInitEeCB -- 156 bytes; frame 0x30: s1 sp+0x10, s0 sp+0x0, ra sp+0x20
// Start the CD/DVD callback thread once ("SceCdCallbackThread", the caller's priority, stack and size); when it
// exists, only changes its priority.
void sceCdInitEeCB(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050f808
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    a3 = a0;
    sd(s1, sp, 0x10);
    t0 = a1;
    s1 = 0x780000;
    sd(s0, sp, 0x0);
    lw(a0, s1, 2964);  // 0x780B94
    s0 = 1;
    sd(ra, sp, 0x20);
    if (a0 != 0) {
        // 0x0050f880
        charge(ctx, 4);
        a1 = a3;
        s0 = 0;
        jal(ctx, 0x50F884u, gen::fn__sceChangeThreadPriority_00502ff0);
        v0 = s0;
    } else {
        // 0x0050f830
        charge(ctx, 20);
        v0 = 0x970000;
        v1 = 0x510000;
        a1 = 0x7C0000;
        v0 = addiu(v0, -9704);  // &0x96DA18
        v1 = addiu(v1, -2248);  // &_sceCd_cbLoop
        a1 = addiu(a1, -7936);  // "SceCdCallbackThread"
        sw(a2, v0, 12);  // 0x96DA24
        a0 = v0;
        sw(v1, v0, 4);  // 0x96DA1C
        sw(t0, v0, 8);  // 0x96DA20
        sw(a3, v0, 20);  // 0x96DA2C
        sw(a1, v0, 32);  // 0x96DA38
        link(ctx, 0x50F860u);  // $ra first: the delay slot below depends on it
        sw(zero, v0, 16);
        call(ctx, gen::fn__sceCreateThread_00502f60);
        a1 = 0;
        sw(v0, s1, 2964);
        a0 = v0;
        jal(ctx, 0x50F870u, gen::fn_StartThread_005042a0);
        v0 = s0;
    }
    // 0x0050f890 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0050F960 cmd_sem_init -- 228 bytes; frame 0x60: s1 sp+0x30, ra sp+0x50, s2 sp+0x40, s0 sp+0x20
// Create the CD/DVD semaphores when any is missing (N-command, S-command, R-command, callback).
void cmd_sem_init(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050f960
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v1 = si(-1);
    sd(s1, sp, 0x30);
    s1 = 0x780000;
    sd(ra, sp, 0x50);
    lw(v0, s1, 2984);  // sceCd_ncmd_semid
    sd(s2, sp, 0x40);
    sd(s0, sp, 0x20);
    if (v0 == v1) {
        // 0x0050f9a8
        charge(ctx, 1);
        s0 = 0x780000;
    L_0050f9ac:
        charge(ctx, 2);
        s2 = 0x780000;
        v0 = 0x7C0000;
    L_0050f9b4:
        charge(ctx, 31);
        v1 = 1;
        v0 = addiu(v0, -7912);
        sw(v1, sp, 0x4);
        sw(v0, sp, 0x14);
        a0 = sp;
        link(ctx, 0x50F9C8u);  // $ra first: the delay slot below depends on it
        sw(v1, sp, 0x8);
        call(ctx, gen::fn__sceCreateSema_00503160);
        v1 = 0x7C0000;
        sw(v0, s1, 2984);
        v1 = addiu(v1, -7896);  // "SceCdScmdSema"
        a0 = sp;
        link(ctx, 0x50F9E0u);  // $ra first: the delay slot below depends on it
        sw(v1, sp, 0x14);
        call(ctx, gen::fn__sceCreateSema_00503160);
        v1 = 0x7C0000;
        sw(v0, s0, 2988);
        v1 = addiu(v1, -7880);  // "SceCdRcmdSema"
        a0 = sp;
        link(ctx, 0x50F9F8u);  // $ra first: the delay slot below depends on it
        sw(v1, sp, 0x14);
        call(ctx, gen::fn__sceCreateSema_00503160);
        v1 = 0x7C0000;
        sw(v0, s2, 2992);
        v1 = addiu(v1, -7864);  // "SceCdCallbackSema"
        a0 = sp;
        sw(v1, sp, 0x14);
        link(ctx, 0x50FA14u);  // $ra first: the delay slot below depends on it
        sw(zero, sp, 0x8);
        call(ctx, gen::fn__sceCreateSema_00503160);
        v1 = 0x780000;
        sw(v0, v1, 2976);  // 0x780BA0
        v0 = 0x780000;
        sw(zero, v0, 2996);  // sceCd_c_cb_sem
        ld(ra, sp, 0x50);
    } else {
        // 0x0050f984
        charge(ctx, 4);
        s0 = 0x780000;
        lw(v0, s0, 2988);  // 0x780BAC
        s2 = 0x780000;
        if (v0 == v1) {
            goto L_0050f9ac;
        }
        // 0x0050f994
        charge(ctx, 3);
        lw(v0, s2, 2992);
        ld(ra, sp, 0x50);
        if (v0 == v1) {
            // 0x0050f9a0
            charge(ctx, 2);
            v0 = 0x7C0000;
            goto L_0050f9b4;
        }
    }
    // 0x0050fa30 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s2, sp, 0x40);
    ld(s1, sp, 0x30);
    ld(s0, sp, 0x20);
    sp = addiu(sp, 0x60);
}

// 0x0050FAE8 sceCdPOffCallback -- 128 bytes; frame 0x40: s2 sp+0x20, s0 sp+0x0, ra sp+0x30, s1 sp+0x10
// Install the CD power-off callback (function, argument, $gp); registers the SIF handler first when needed; returns
// the old function.
void sceCdPOffCallback(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050fae8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 0x780000;
    sd(s2, sp, 0x20);
    sd(s0, sp, 0x0);
    s2 = a0;
    lw(v1, v0, 3016);  // 0x780BC8
    s0 = a1;
    sd(ra, sp, 0x30);
    sd(s1, sp, 0x10);
    if (i64(v1) < 0) {
        // 0x0050fb10
        charge(ctx, 2);
        jal(ctx, 0x50FB10u, gen::fn_PowerOffCB_0050fbc0);
    }
    // 0x0050fb18
    charge(ctx, 11);
    jal(ctx, 0x50FB18u, gen::fn_DIntr_0050d3a0);
    a1 = 0x970000;
    a0 = 0x970000;
    lw(s1, a1, -9720);  // 0x96DA08
    v1 = 0x970000;
    sw(s0, a0, -9712);  // 0x96DA10
    sw(s2, a1, -9720);  // 0x96DA08
    sw(gp, v1, -9716);  // 0x96DA0C
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = s1;
    if (!cc) {
        // 0x0050fb44
        charge(ctx, 3);
        jal(ctx, 0x50FB44u, gen::fn_EIntr_0050d3f0);
        v0 = s1;
    }
    // 0x0050fb50 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0050FB68 _sceCd_Poff_Intr -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0
// SIF power-off command handler: calls the user's power-off callback unless it is being installed.
void _sceCd_Poff_Intr(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0050fb68
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x970000;
    sp = addiu(sp, -0x20);
    lw(a1, v0, -9720);  // 0x96DA08
    sd(ra, sp, 0x10);
    sd(s0, sp, 0x0);
    if (a1 != 0) {
        // 0x0050fb80
        charge(ctx, 4);
        v0 = 0x780000;
        lw(v1, v0, 2980);  // 0x780BA4
        ld(ra, sp, 0x10);
        if (v1 == 0) {
            // 0x0050fb90
            charge(ctx, 7);
            v0 = 0x970000;
            s0 = gp;
            lw(gp, v0, -9716);  // 0x96DA0C
            v1 = 0x970000;
            jt = a1.u();  // the target, read before the delay slot
            link(ctx, 0x50FBA0u);  // $ra = the return address
            lw(a0, v1, -9712);
            call_ptr(ctx, jt);
            gp = s0;
            goto L_0050fbac;
        }
        // 0x0050fbb0 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
L_0050fbac:
    charge(ctx, 1);
    ld(ra, sp, 0x10);
    // 0x0050fbb0 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0050FBC0 PowerOffCB -- 120 bytes; frame 0x40: s2 sp+0x20, s1 sp+0x10, s0 sp+0x0, ra sp+0x30
// Register the CD power-off SIF command handler (system command 0x80000012) with interrupts off.
void PowerOffCB(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050fbc0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x10);
    s2 = 1;
    s1 = 0x780000;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x30);
    link(ctx, 0x50FBDCu);  // $ra first: the delay slot below depends on it
    sw(s2, s1, 2980);  // 0x780BA4
    call(ctx, gen::fn_DIntr_0050d3a0);
    a1 = 0x510000;
    a0 = lui(0x8000);
    s0 = v0;
    a1 = addiu(a1, -1176);  // &_sceCd_Poff_Intr
    a0 = a0 | 0x12;
    a2 = 0;
    jal(ctx, 0x50FBF8u, gen::fn_sub_506430_00506430);
    v0 = 0x780000;
    if (s0 != 0) {
        // 0x0050fc08
        charge(ctx, 3);
        jal(ctx, 0x50FC08u, gen::fn_EIntr_0050d3f0);
        v0 = 0x780000;
    }
    // 0x0050fc14 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    sw(zero, s1, 2980);
    sw(s2, v0, 3016);
    ld(ra, sp, 0x30);
    v0 = 1;
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x005103B0 _sceCdSC -- 176 bytes; leaf frame (no stack)
// libcdvd's internal query: stores the address of an internal variable selected by code 0x8001-0x8014.
void _sceCdSC(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005103b0
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x8001;
    cc = a0 == v0;  // the condition, before the delay slot changes it
    v0 = 0x780000;
    if (cc) {
        // 0x00510450
        charge(ctx, 1);
        lw(v0, v0, 2984);
    L_00510454:
        charge(ctx, 1);
        sw(v0, a1, 0);
    } else {
        // 0x005103bc
        charge(ctx, 3);
        v0 = 0x8003;
        cc = a0 == v0;  // the condition, before the delay slot changes it
        v0 = 0x780000;
        if (cc) {
            // 0x00510448
            charge(ctx, 2);
            v0 = addiu(v0, 3072);
            goto L_00510454;
        }
        // 0x005103c8
        charge(ctx, 3);
        v0 = 0x8002;
        cc = a0 == v0;  // the condition, before the delay slot changes it
        v0 = 0x780000;
        if (cc) {
            // 0x00510440
            charge(ctx, 2);
            v0 = addiu(v0, 3200);
            goto L_00510454;
        }
        // 0x005103d4
        charge(ctx, 3);
        v0 = 0x8004;
        cc = a0 == v0;  // the condition, before the delay slot changes it
        v0 = 0x780000;
        if (cc) {
            // 0x00510438
            charge(ctx, 2);
            v0 = addiu(v0, 7504);
            goto L_00510454;
        }
        // 0x005103e0
        charge(ctx, 3);
        v0 = 0x8011;
        cc = a0 == v0;  // the condition, before the delay slot changes it
        v0 = 0x8013;
        if (!cc) {
            // 0x005103ec
            charge(ctx, 2);
            cc = a0 == v0;  // the condition, before the delay slot changes it
            v0 = 0x780000;
            if (cc) {
                // 0x00510420
                charge(ctx, 2);
                v0 = addiu(v0, 7552);
            } else {
                // 0x005103f4
                charge(ctx, 3);
                v0 = 0x8012;
                cc = a0 == v0;  // the condition, before the delay slot changes it
                v0 = 0x780000;
                if (cc) {
                    // 0x00510418
                    charge(ctx, 2);
                    v0 = addiu(v0, 8640);
                } else {
                    // 0x00510400
                    charge(ctx, 3);
                    v0 = 0x8014;
                    if (a0 != v0) {
                        v0 = 0;
                    } else {
                        // 0x0051040c
                        charge(ctx, 3);
                        v0 = 0x780000;
                        v0 = addiu(v0, 9984);  // &0x782700
                    }
                }
            }
            goto L_00510454;
        }
        // 0x00510428
        charge(ctx, 4);
        v0 = 0x780000;
        lw(v0, v0, 2988);  // 0x780BAC
        sw(v0, a1, 0);
    }
    // 0x00510458 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = 1;
}

// 0x00511110 sceCdChgSys -- 36 bytes; frame 0x10: ra sp+0x0
// Unsupported in this library: prints the illegal-call message, returns 2.
void sceCdChgSys(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00511110
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 0x7C0000;
    sd(ra, sp, 0x0);
    a0 = addiu(a0, -7376);  // "sceCdChgSys: Illegal_function_call\n"
    jal(ctx, 0x51111Cu, gen::fn_scePrintf_00505e48);
    ld(ra, sp, 0x0);
    v0 = 2;
    sp = addiu(sp, 0x10);
}

// 0x00511B08 scePadSetReqState -- 180 bytes; frame 0x50: s1 sp+0x10, s2 sp+0x20, s3 sp+0x30, ra sp+0x40, s0 sp+0x0
// Set a pad's request state byte (DMA area +113) and write the area back, when the port/slot is open (table
// 0x96DD10, 112 bytes per port, 28 per slot).
void scePadSetReqState(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00511b08
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v1 = 112;
    sd(s1, sp, 0x10);
    v0 = 0x970000;
    sd(s2, sp, 0x20);
    s1 = a0;
    s2 = a1;
    a0 = 28;
    mult1(v1, s1, v1);
    mult(a0, s2, a0);
    sd(s3, sp, 0x30);
    v0 = addiu(v0, -8944);  // &0x96DD10
    sd(ra, sp, 0x40);
    sd(s0, sp, 0x0);
    a0 = addu(a0, v1);
    v0 = addu(v0, a0);
    lw(v1, v0, 16);
    s3 = a2;
    if (v1 == 0) {
        // 0x00511b54
        charge(ctx, 2);
        v0 = 0;
        goto L_00511ba0;
    }
    // 0x00511b5c
    charge(ctx, 14);
    jal(ctx, 0x511B5Cu, gen::fn_DIntr_0050d3a0);
    a2 = 0;
    s0 = v0;
    a0 = s1;
    a1 = s2;
    jal(ctx, 0x511B70u, gen::fn_scePadGetDmaStr_00511830);
    a0 = v0;
    sb(s3, v0, 113);
    a1 = addiu(a0, 127);
    jal(ctx, 0x511B80u, gen::fn_SyncDCache_00503a58);
    v0 = 1;
    ld(ra, sp, 0x40);
    if (s0 == v0) {
        // 0x00511b94
        charge(ctx, 3);
        jal(ctx, 0x511B94u, gen::fn_EIntr_0050d3f0);
        v0 = 1;
    L_00511ba0:
        charge(ctx, 1);
        ld(ra, sp, 0x40);
    }
    // 0x00511ba4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00512070 scePadSetActDirect -- 200 bytes; frame 0xC0: s2 sp+0xA0, s1 sp+0x90, s0 sp+0x80, ra sp+0xB0
// Set the actuator values of a pad: when its DMA status says ready, copies 6 bytes into the port's send buffer and
// sends it to the IOP; 1 on success.
void scePadSetActDirect(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00512070
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(s2, sp, 0xA0);
    sd(s1, sp, 0x90);
    s2 = a1;
    sd(s0, sp, 0x80);
    s1 = a0;
    s0 = a2;
    sd(ra, sp, 0xB0);
    a2 = sp;
    jal(ctx, 0x512090u, gen::fn_scePadGetDmaStr_00511830);
    lbu(v1, sp, 0x72);
    v0 = 1;
    cc = v1 != v0;  // the condition, before the delay slot changes it
    v0 = 0;
    if (!cc) {
        // 0x005120a8
        charge(ctx, 12);
        v1 = 28;
        a0 = 112;
        mult(v1, s2, v1);
        mult1(a0, s1, a0);
        v0 = 0x970000;
        a1 = 0;
        v0 = addiu(v0, -8944);  // &0x96DD10
        v1 = addu(v1, a0);
        v0 = addu(v0, v1);
        lw(a2, v0, 4);
        a3 = addiu(a2, 12);
        for (;;) {
            // 0x005120d8
            charge(ctx, 8);
            v0 = addu(s0, a1);
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
        // 0x005120f8
        charge(ctx, 10);
        s0 = 1;
        v0 = 6;
        sw(s0, a2, 4);
        a0 = s1;
        sw(v0, a2, 8);
        a1 = s2;
        jal(ctx, 0x51210Cu, gen::fn__send_to_iop_00511478);
        v0 = v0 ^ 0x1;
        if (v0 != 0) s0 = 0;
        v0 = s0;
    }
    // 0x00512120 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0xB0);
    ld(s2, sp, 0xA0);
    ld(s1, sp, 0x90);
    ld(s0, sp, 0x80);
    sp = addiu(sp, 0xC0);
}

// 0x005129A0 sceSdCallBack -- 28 bytes; leaf frame (no stack)
// Install the sound driver's callback (and the caller's $gp); returns the previous one.
void sceSdCallBack(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x005129a0
    enter(ctx, 7);  // entry check point + this block's cycles
    v1 = 0x780000;
    lw(v0, v1, 10120);  // 0x782788
    sw(a0, v1, 10120);  // 0x782788
    a0 = gp;
    v1 = 0x780000;
    sw(a0, v1, 10124);  // 0x78278C
}

// 0x00512FF0 _sdrCB -- 248 bytes; frame 0x30: s1 sp+0x10, ra sp+0x20, s0 sp+0x0
// Sound driver remote callback: bit 0x100 calls the core 0 DMA end handler, 0x200 core 1, 0x400 the IRQ handler,
// each with its argument.
void _sdrCB(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00512ff0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x10);
    sd(ra, sp, 0x20);
    s1 = a1;
    sd(s0, sp, 0x0);
    lw(v1, s1, 0);
    v0 = v1 & 0x100;
    a1 = 0x780000;
    if (v0 != 0) {
        // 0x00513014
        charge(ctx, 3);
        lw(v0, a1, 10144);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 0x780000;
        if (!cc) {
            // 0x00513020
            charge(ctx, 11);
            lw(v1, v0, 10168);
            s0 = gp;
            gp = v1;
            a0 = 0x780000;
            lw(v0, a1, 10144);
            lw(a1, a0, 10156);  // 0x7827AC
            a0 = 0;
            jalr(ctx, 0x513038u, v0.u());
            v1 = gp;
            gp = s0;
            lw(v1, s1, 0);
        }
    }
    // 0x0051304c
    charge(ctx, 3);
    v0 = v1 & 0x200;
    a1 = 0x780000;
    if (v0 != 0) {
        // 0x00513058
        charge(ctx, 3);
        lw(v0, a1, 10148);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 0x780000;
        if (!cc) {
            // 0x00513064
            charge(ctx, 11);
            lw(v1, v0, 10172);
            s0 = gp;
            gp = v1;
            a0 = 0x780000;
            lw(v0, a1, 10148);
            lw(a1, a0, 10160);  // 0x7827B0
            a0 = 1;
            jalr(ctx, 0x51307Cu, v0.u());
            v1 = gp;
            gp = s0;
            lw(v1, s1, 0);
        }
    }
    // 0x00513090
    charge(ctx, 3);
    v0 = v1 & 0x400;
    a0 = 0x780000;
    if (v0 != 0) {
        // 0x0051309c
        charge(ctx, 3);
        lw(v0, a0, 10152);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 0x780000;
        if (!cc) {
            // 0x005130a8
            charge(ctx, 10);
            lw(v1, v0, 10176);
            s0 = gp;
            gp = v1;
            a2 = 0x780000;
            lw(v0, a0, 10152);
            lw(a0, s1, 4);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x5130C0u);  // $ra = the return address
            lw(a1, a2, 10164);
            call_ptr(ctx, jt);
            v1 = gp;
            gp = s0;
        }
    }
    // 0x005130d0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    v0 = 0;
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00513290 sceMc2End -- 216 bytes; frame 0x30: s1 sp+0x10, ra sp+0x20, s0 sp+0x0
// Shut libmc2 down: waits for a pending command, terminates and deletes the worker thread, deletes the three
// semaphores, ends the core.
void sceMc2End(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00513290
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x10);
    s1 = 0x780000;
    sd(ra, sp, 0x20);
    lw(v0, s1, libs6::lo(libs6::kMc2Ready));  // 0x7827D8
    sd(s0, sp, 0x0);
    if (v0 != 0) {
        // 0x005132b8
        charge(ctx, 4);
        v0 = 0x970000;
        lw(v1, v0, libs6::lo(libs6::kMc2Command));  // 0x96F144
        a0 = 0;
        if (v1 != 0) {
            // 0x005132c8
            charge(ctx, 2);
            a1 = 0;
            jal(ctx, 0x5132C8u, gen::fn_sceMc2Sync_00514928);
        }
        // 0x005132d0
        charge(ctx, 4);
        s0 = 0x970000;
        lw(a0, s0, libs6::lo(libs6::kMc2Thread));  // 0x96F660
        if (i64(a0) < 0) {
            s0 = addiu(s0, -2464);  // &0x96F660
        } else {
            // 0x005132e0
            charge(ctx, 4);
            jal(ctx, 0x5132E0u, gen::fn__sceTerminateThread_00502fb0);
            a0 = 0x7C0000;
            if (i64(v0) < 0) {
                // 0x005132f0
                charge(ctx, 2);
                a0 = addiu(a0, -6840);
                jal(ctx, 0x5132F0u, gen::fn_scePrintf_00505e48);
            }
            // 0x005132f8
            charge(ctx, 3);
            link(ctx, 0x5132F8u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, -2464);
            call(ctx, gen::fn__sceDeleteThread_00502f70);
            s0 = addiu(s0, -2464);
        }
        // 0x00513304
        charge(ctx, 3);
        lw(a0, s0, 4);
        if (i64(a0) < 0) {
            lw(a0, s0, 8);
        } else {
            // 0x00513310
            charge(ctx, 3);
            jal(ctx, 0x513310u, gen::fn__sceDeleteSema_00503170);
            lw(a0, s0, 8);
        }
        // 0x0051331c
        charge(ctx, 2);
        v0 = 0x970000;
        if (i64(a0) >= 0) {
            // 0x00513324
            charge(ctx, 3);
            jal(ctx, 0x513324u, gen::fn__sceDeleteSema_00503170);
            v0 = 0x970000;
        }
        // 0x00513330
        charge(ctx, 3);
        lw(a0, v0, -2452);
        if (i64(a0) >= 0) {
            // 0x0051333c
            charge(ctx, 2);
            jal(ctx, 0x51333Cu, gen::fn__sceDeleteSema_00503170);
        }
        // 0x00513344
        charge(ctx, 4);
        jal(ctx, 0x513344u, gen::fn__sceMcCoreEnd_0051aef8);
        sw(zero, s1, 10200);
        v0 = 0;
    } else {
        // 0x005132ac
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x8001;
    }
    // 0x00513354 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00513478 sceMc2SearchSocket -- 172 bytes; frame 0x70: s2 sp+0x50, s0 sp+0x30, ra sp+0x60, s1 sp+0x40
// Find the memory card socket of a port/slot (sceDbcSearchPortSpecific) under the API semaphore; an error when not
// initialised, busy or not found.
void sceMc2SearchSocket(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00513478
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    v0 = 0x780000;
    sd(s2, sp, 0x50);
    sd(s0, sp, 0x30);
    s2 = a1;
    lw(v1, v0, libs6::lo(libs6::kMc2Ready));  // 0x7827D8
    s0 = a0;
    sd(ra, sp, 0x60);
    sd(s1, sp, 0x40);
    if (v1 != 0) {
        // 0x005134ac
        charge(ctx, 4);
        v0 = 0x970000;
        lw(v1, v0, libs6::lo(libs6::kMc2Command));  // 0x96F144
        s1 = 0x970000;
        if (v1 == 0) {
            // 0x005134c8
            charge(ctx, 9);
            link(ctx, 0x5134C8u);  // $ra first: the delay slot below depends on it
            lw(a0, s1, -2452);
            call(ctx, gen::fn__sceWaitSema_005031a0);
            sw(s0, sp, 0x8);
            a0 = sp;
            link(ctx, 0x5134D8u);  // $ra first: the delay slot below depends on it
            sw(s2, sp, 0xC);
            call(ctx, gen::fn_sceDbcSearchPortSpecific_0051cdd8);
            s0 = v0;
            if (i64(s0) >= 0) {
                // 0x00513500
                charge(ctx, 3);
                link(ctx, 0x513500u);  // $ra first: the delay slot below depends on it
                lw(a0, s1, -2452);
                call(ctx, gen::fn__sceSignalSema_00503180);
                v0 = s0;
            } else {
                // 0x005134ec
                charge(ctx, 5);
                link(ctx, 0x5134ECu);  // $ra first: the delay slot below depends on it
                lw(a0, s1, -2452);
                call(ctx, gen::fn__sceSignalSema_00503180);
                v0 = lui(0x8101);
                v0 = v0 | 0x8002;
            }
        } else {
            // 0x005134bc
            charge(ctx, 3);
            v0 = lui(0x8101);
            v0 = v0 | 0x10;
        }
    } else {
        // 0x005134a0
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x8001;
    }
    // 0x0051350c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x60);
    ld(s2, sp, 0x50);
    ld(s1, sp, 0x40);
    ld(s0, sp, 0x30);
    sp = addiu(sp, 0x70);
}

// 0x00513528 sceMc2ChangeThreadPriority -- 56 bytes; frame 0x10: ra sp+0x0
// Change the worker thread's priority (> 0).
void sceMc2ChangeThreadPriority(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00513528
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (i64(a0) > 0) {
        // 0x00513540
        charge(ctx, 5);
        v0 = 0x970000;
        a1 = a0;
        link(ctx, 0x513548u);  // $ra first: the delay slot below depends on it
        lw(a0, v0, -2464);
        call(ctx, gen::fn__sceChangeThreadPriority_00502ff0);
        v0 = 0;
    } else {
        // 0x00513534
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x16;
    }
    // 0x00513554 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00513560 sceMc2iChangeThreadPriority -- 56 bytes; frame 0x10: ra sp+0x0
// Change the worker thread's priority from interrupt context (> 0).
void sceMc2iChangeThreadPriority(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00513560
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (i64(a0) > 0) {
        // 0x00513578
        charge(ctx, 5);
        v0 = 0x970000;
        a1 = a0;
        link(ctx, 0x513580u);  // $ra first: the delay slot below depends on it
        lw(a0, v0, -2464);
        call(ctx, gen::fn__sceiChangeThreadPriority_00503000);
        v0 = 0;
    } else {
        // 0x0051356c
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x16;
    }
    // 0x0051358c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005138B8 sceMc2GetDirAllAsync -- 176 bytes; frame 0x30: s0 sp+0x0, ra sp+0x20, s1 sp+0x10
// Queue a whole-directory read (command 100) on the socket and wake the worker.
void sceMc2GetDirAllAsync(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005138b8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v1 = 0x780000;
    sd(s0, sp, 0x0);
    lw(v0, v1, libs6::lo(libs6::kMc2Ready));  // 0x7827D8
    s0 = a0;
    sd(ra, sp, 0x20);
    sd(s1, sp, 0x10);
    if (v0 != 0) {
        // 0x005138e4
        charge(ctx, 5);
        a0 = s0;
        jal(ctx, 0x5138E4u, gen::fn__sceMcCoreChangeSocketTypeDbc2Mc_0051c2e8);
        s0 = v0;
        s1 = 0x970000;
        if (i64(s0) >= 0) {
            // 0x00513904
            charge(ctx, 7);
            link(ctx, 0x513904u);  // $ra first: the delay slot below depends on it
            lw(a0, s1, -2452);
            call(ctx, gen::fn__sceWaitSema_005031a0);
            a2 = 0x970000;
            a1 = addiu(a2, -3776);  // &0x96F140
            lw(v0, a1, 4);  // 0x96F144
            if (v0 == 0) {
                v0 = 0x970000;
                // 0x00513934
                charge(ctx, 8);
                v1 = 100;
                lw(a0, v0, -2460);
                sw(s0, a2, -3776);
                link(ctx, 0x513940u);  // $ra first: the delay slot below depends on it
                sw(v1, a1, 4);
                call(ctx, gen::fn__sceSignalSema_00503180);
                link(ctx, 0x513948u);  // $ra first: the delay slot below depends on it
                lw(a0, s1, -2452);
                call(ctx, gen::fn__sceSignalSema_00503180);
                v0 = 0;
            } else {
                // 0x00513920
                charge(ctx, 5);
                link(ctx, 0x513920u);  // $ra first: the delay slot below depends on it
                lw(a0, s1, -2452);
                call(ctx, gen::fn__sceSignalSema_00503180);
                v0 = lui(0x8101);
                v0 = v0 | 0x10;
            }
        } else {
            // 0x005138f8
            charge(ctx, 3);
            v0 = lui(0x8101);
            v0 = v0 | 0x8002;
        }
    } else {
        // 0x005138d8
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x8001;
    }
    // 0x00513954 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x005145F8 basic_thread -- 608 bytes; frame 0x50: s3 sp+0x30, s2 sp+0x20, s1 sp+0x10, ra sp+0x40, s0 sp+0x0
// libmc2's worker thread: waits for a command, runs the matching _sceMcFat* call with the request's arguments (2
// info, 3 format, 4 unformat, 5/6 read/write, 7/11 create, 8 delete, 9 rename, 10 getdir, 12 chdir, 13 setattr, 14
// search, 15 entry space, 32/33 fast read/write), stores the result and signals the done semaphore.
void basic_thread(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005145f8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s3, sp, 0x30);
    sd(s2, sp, 0x20);
    s3 = 0x7C0000;
    sd(s1, sp, 0x10);
    s2 = 0x970000;
    sd(ra, sp, 0x40);
    s1 = 0x970000;
    sd(s0, sp, 0x0);
    v0 = addiu(s2, -2464);  // &0x96F660
    for (;;) {
        // 0x00514620
        charge(ctx, 8);
        link(ctx, 0x514620u);  // $ra first: the delay slot below depends on it
        lw(a0, v0, 4);
        call(ctx, gen::fn__sceWaitSema_005031a0);
        v1 = addiu(s1, -3776);
        lw(v0, v1, 4);
        v0 = addiu(v0, -2);
        v1 = sltiu(v0, 32);
        v0 = sll(v0, 2);
        if (v1 != 0) {
            // 0x00514640
            charge(ctx, 5);
            v1 = addiu(s3, -6800);
            v0 = addu(v0, v1);
            lw(a0, v0, 0);
            switch (a0.u()) {
            case 0x514654u:  // table[0]
                // 0x00514654
                charge(ctx, 6);
                s0 = addiu(s1, -3776);
                lw(a0, s1, -3776);
                link(ctx, 0x51465Cu);  // $ra first: the delay slot below depends on it
                lw(a1, s0, 12);
                call(ctx, gen::fn__sceMcFatGetInfo_00515d80);
                sw(v0, s0, 8);
            L_00514820:
                charge(ctx, 6);
                a0 = addiu(s1, -3776);
                v0 = lui(0x8101);
                lw(v1, a0, 8);
                v0 = v0 | 0x9FFF;
                cc = v1 != v0;  // the condition, before the delay slot changes it
                v0 = addiu(s2, -2464);
                if (!cc) {
                    // 0x00514838
                    charge(ctx, 4);
                    v0 = lui(0x8101);
                    v0 = v0 | 0x2;
                    sw(v0, a0, 8);
                    v0 = addiu(s2, -2464);
                }
                // 0x00514848
                charge(ctx, 4);
                link(ctx, 0x514848u);  // $ra first: the delay slot below depends on it
                lw(a0, v0, 8);
                call(ctx, gen::fn__sceSignalSema_00503180);
                v0 = addiu(s2, -2464);
                backedge(ctx);
                continue;
            case 0x51466Cu:  // table[3]
                // 0x0051466c
                charge(ctx, 9);
                s0 = addiu(s1, -3776);
                lw(a0, s1, -3776);
                lw(a2, s0, 12);
                a1 = addiu(s0, 1052);
                lw(a3, s0, 16);
                link(ctx, 0x514680u);  // $ra first: the delay slot below depends on it
                lw(t0, s0, 20);
                call(ctx, gen::fn__sceMcFatReadFile_00518268);
                sw(v0, s0, 8);
                goto L_00514820;
            case 0x514690u:  // table[30]
                // 0x00514690
                charge(ctx, 9);
                s0 = addiu(s1, -3776);
                lw(a0, s1, -3776);
                lw(a2, s0, 12);
                a1 = addiu(s0, 1052);
                lw(a3, s0, 16);
                link(ctx, 0x5146A4u);  // $ra first: the delay slot below depends on it
                lw(t0, s0, 20);
                call(ctx, gen::fn__sceMcFatReadFastFile_00518470);
                sw(v0, s0, 8);
                goto L_00514820;
            case 0x5146B4u:  // table[31]
                // 0x005146b4
                charge(ctx, 9);
                s0 = addiu(s1, -3776);
                lw(a0, s1, -3776);
                lw(a2, s0, 12);
                a1 = addiu(s0, 1052);
                lw(a3, s0, 16);
                link(ctx, 0x5146C8u);  // $ra first: the delay slot below depends on it
                lw(t0, s0, 20);
                call(ctx, gen::fn__sceMcFatWriteFastFile_00518e70);
                sw(v0, s0, 8);
                goto L_00514820;
            case 0x5146D8u:  // table[4]
                // 0x005146d8
                charge(ctx, 9);
                s0 = addiu(s1, -3776);
                lw(a0, s1, -3776);
                lw(a2, s0, 12);
                a1 = addiu(s0, 1052);
                lw(a3, s0, 16);
                link(ctx, 0x5146ECu);  // $ra first: the delay slot below depends on it
                lw(t0, s0, 20);
                call(ctx, gen::fn__sceMcFatWriteFile_005187c0);
                sw(v0, s0, 8);
                goto L_00514820;
            case 0x5146FCu:  // table[1]
                // 0x005146fc
                charge(ctx, 5);
                lw(a0, s1, -3776);
                s0 = addiu(s1, -3776);
                jal(ctx, 0x514700u, gen::fn__sceMcFatFormat_00516118);
                sw(v0, s0, 8);
                goto L_00514820;
            case 0x514710u:  // table[5]
                // 0x00514710
                charge(ctx, 7);
                s0 = addiu(s1, -3776);
                lw(a0, s1, -3776);
                lw(a2, s0, 12);
                a1 = addiu(s0, 1052);
                jal(ctx, 0x51471Cu, gen::fn__sceMcFatCreateFile_00517cd8);
                sw(v0, s0, 8);
                goto L_00514820;
            case 0x51472Cu:  // table[6]
                // 0x0051472c
                charge(ctx, 6);
                s0 = addiu(s1, -3776);
                lw(a0, s1, -3776);
                a1 = addiu(s0, 1052);
                jal(ctx, 0x514734u, gen::fn__sceMcFatDeleteFile_005194f8);
                sw(v0, s0, 8);
                goto L_00514820;
            case 0x514744u:  // table[9]
                // 0x00514744
                charge(ctx, 7);
                s0 = addiu(s1, -3776);
                lw(a0, s1, -3776);
                lw(a2, s0, 12);
                a1 = addiu(s0, 1052);
                jal(ctx, 0x514750u, gen::fn__sceMcFatCreateFile_00517cd8);
                sw(v0, s0, 8);
                goto L_00514820;
            case 0x514760u:  // table[10]
                // 0x00514760
                charge(ctx, 7);
                s0 = addiu(s1, -3776);
                lw(a0, s1, -3776);
                lw(a2, s0, 12);
                a1 = addiu(s0, 1052);
                jal(ctx, 0x51476Cu, gen::fn__sceMcFatChDir_00519728);
                sw(v0, s0, 8);
                goto L_00514820;
            case 0x51477Cu:  // table[8]
                // 0x0051477c
                charge(ctx, 10);
                s0 = addiu(s1, -3776);
                lw(a0, s1, -3776);
                lw(a2, s0, 12);
                a1 = addiu(s0, 1052);
                lw(a3, s0, 16);
                lw(t0, s0, 20);
                link(ctx, 0x514794u);  // $ra first: the delay slot below depends on it
                lw(t1, s0, 24);
                call(ctx, gen::fn__sceMcFatGetDir_00519850);
                sw(v0, s0, 8);
                goto L_00514820;
            case 0x5147A4u:  // table[11]
                // 0x005147a4
                charge(ctx, 7);
                s0 = addiu(s1, -3776);
                lw(a0, s1, -3776);
                lhu(a2, s0, 12);
                a1 = addiu(s0, 1052);
                jal(ctx, 0x5147B0u, gen::fn__sceMcFatSetAttr_00519d70);
                sw(v0, s0, 8);
                goto L_00514820;
            case 0x5147C0u:  // table[7]
                // 0x005147c0
                charge(ctx, 7);
                s0 = addiu(s1, -3776);
                lw(a0, s1, -3776);
                a1 = addiu(s0, 1052);
                a2 = addiu(s0, 1180);
                jal(ctx, 0x5147CCu, gen::fn__sceMcFatRename_00519ef8);
                sw(v0, s0, 8);
                goto L_00514820;
            case 0x5147DCu:  // table[2]
                // 0x005147dc
                charge(ctx, 5);
                lw(a0, s1, -3776);
                s0 = addiu(s1, -3776);
                jal(ctx, 0x5147E0u, gen::fn__sceMcFatUnFormat_00516a48);
                sw(v0, s0, 8);
                goto L_00514820;
            case 0x5147F0u:  // table[12]
                // 0x005147f0
                charge(ctx, 7);
                s0 = addiu(s1, -3776);
                lw(a0, s1, -3776);
                lw(a2, s0, 12);
                a1 = addiu(s0, 1052);
                jal(ctx, 0x5147FCu, gen::fn__sceMcFatSearchFile_00517be8);
                sw(v0, s0, 8);
                goto L_00514820;
            case 0x51480Cu:  // table[13]
                // 0x0051480c
                charge(ctx, 5);
                s0 = addiu(s1, -3776);
                lw(a0, s1, -3776);
                a1 = addiu(s0, 1052);
                jal(ctx, 0x514814u, gen::fn__sceMcFatGetEntSpace_0051a078);
                sw(v0, s0, 8);
                goto L_00514820;
            case 0x514820u:  // table[14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29]
                goto L_00514820;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, a0.u());
                return;
            }
        }
        goto L_00514820;
    }
}

// 0x00516118 _sceMcFatFormat -- 2348 bytes; frame 0xE0: s6 sp+0xA0, s2 sp+0x60, ra sp+0xD0, fp sp+0xC0, s7 sp+0xB0, s5 sp+0x90, s4 sp+0x80, s3 sp+0x70, s1 sp+0x50, s0 sp+0x40
// Format a memory card: reads the card spec and system info (bad-block list rebuilt when the superblock is not
// "Sony PS2 Memory Card Format"), fills the superblock ("1.2.0.0"), places the indirect FAT, the FAT and the root
// directory around the bad blocks, writes them and flushes.
void _sceMcFatFormat(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00516118
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
    v1 = 388;
    sd(s6, sp, 0xA0);
    v0 = 0x780000;
    s6 = a0;
    sd(s2, sp, 0x60);
    mult(v1, s6, v1);
    v0 = addiu(v0, 10208);  // &0x7827E0
    sd(ra, sp, 0xD0);
    sd(fp, sp, 0xC0);
    sd(s7, sp, 0xB0);
    sd(s5, sp, 0x90);
    s2 = addu(v1, v0);
    sd(s4, sp, 0x80);
    sd(s3, sp, 0x70);
    sd(s1, sp, 0x50);
    link(ctx, 0x516158u);  // $ra first: the delay slot below depends on it
    sd(s0, sp, 0x40);
    call(ctx, gen::fn__sceMcCoreGetConnection_0051c0c0);
    v1 = 2200;
    if (v0 == 0) {
        // 0x00516168
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x13;
        goto L_00516a14;
    }
    // 0x00516174
    charge(ctx, 25);
    a0 = 0x980000;
    mult(v1, s6, v1);
    v0 = addiu(a0, -18552);  // &0x97B788
    t1 = si(-1);
    t2 = addiu(v0, 2056);  // &0x97BF90
    t3 = 0x7C0000;
    a0 = s6;
    a2 = addu(v0, v1);
    sw(zero, a2, 2196);
    a3 = a2;
    sw(t1, a3, 2048);
    t0 = a2;
    v0 = a2;
    sw(t1, t0, 2052);
    v1 = addu(v1, t2);
    sw(zero, v0, 2192);
    t1 = addiu(t3, -6648);  // &0x7BE608
    lb(a2, t1, 0);  // 0x7BE608
    lb(a3, t1, 1);  // 0x7BE609
    sb(a2, v1, 0);
    sb(a3, v1, 1);
    a1 = sp;
    jal(ctx, 0x5161C8u, gen::fn__sceMcpGetCardSpec_0051a180);
    if (v0 != 0) {
        // 0x005161d8
        charge(ctx, 4);
        a0 = s6;
        jal(ctx, 0x5161D8u, gen::fn__sceMcpReadSysInfo_0051a1e0);
        s0 = 0x7C0000;
        if (v0 == 0) {
            goto L_005169c4;
        }
        // 0x005161e8
        charge(ctx, 6);
        a0 = s2;
        a1 = addiu(s0, -6640);
        a2 = 27;
        jal(ctx, 0x5161F0u, gen::fn_strncmp_00524670);
        a2 = addiu(s2, 208);
        if (v0 != 0) {
            // 0x00516200
            charge(ctx, 4);
            v1 = lui(0xFFFF);
            v1 = v1 | 0xFFFF;
            s3 = 31;
            v0 = addiu(s2, 332);
            for (;;) {
                // 0x00516210
                charge(ctx, 7);
                sw(v1, v0, 0);
                s3 = addiu(s3, -1);
                v0 = addiu(v0, -4);
                if (i64(s3) < 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0051622c
            charge(ctx, 5);
            a0 = s6;
            a1 = sp;
            jal(ctx, 0x516230u, gen::fn__sceMcpMakeSpecoutBlock_0051ab98);
            if (v0 == 0) {
                goto L_005169c4;
            }
            goto L_00516240;
        }
    L_00516240:
        charge(ctx, 33);
        a0 = s2;
        a1 = 0;
        a2 = 40;
        jal(ctx, 0x516248u, gen::fn_memset_00521408);
        a1 = 0x7C0000;
        a0 = s2;
        a3 = addiu(s0, -6640);
        ldl(v0, a3, 7);
        ldr(v0, a3, 0);
        ldl(v1, a3, 15);
        ldr(v1, a3, 8);
        ldl(a2, a3, 23);
        ldr(a2, a3, 16);
        sdl(v0, s2, 7);
        sdr(v0, s2, 0);
        sdl(v1, s2, 15);
        sdr(v1, s2, 8);
        sdl(a2, s2, 23);
        sdr(a2, s2, 16);
        lw(v0, a3, 24);
        sw(v0, s2, 24);
        a1 = addiu(a1, -6608);  // " 1.2.0.0"
        jal(ctx, 0x516294u, gen::fn_strcat_00523e68);
        lw(v1, sp, 0x0);
        a0 = 1024;
        lhu(v0, sp, 0x0);
        a1 = 0xFF00;
        div(a0, v1);
        t2 = 2;
        sh(v0, s2, 40);
        t0 = 43;
        if (v1 == 0) {
            brk(ctx, 0x5162C0u, 0x7u);
        }
        // 0x005162c4
        charge(ctx, 40);
        t1 = 256;
        lw(v1, sp, 0x8);
        a2 = si(-1);
        lhu(v0, sp, 0x4);
        sh(a1, s2, 46);
        sh(v0, s2, 44);
        mflo(a3);
        sh(a3, s2, 42);
        v0 = a3 & 0xFFFF;
        div(v1, v0);
        sw(a0, s2, 340);
        lhu(a1, s2, 42);
        lhu(a0, s2, 44);
        sb(t2, s2, 336);
        sb(t0, s2, 337);
        sw(t1, s2, 344);
        sw(zero, s2, 60);
        sw(zero, s2, 72);
        sw(zero, s2, 76);
        sw(zero, s2, 368);
        mflo(a3);
        divu(a0, a1);
        sw(a3, s2, 48);
        lw(v0, sp, 0x4);
        sw(a2, s2, 384);
        sw(zero, s2, 356);
        sw(zero, s2, 360);
        sw(zero, s2, 364);
        sw(a2, s2, 372);
        sw(a2, s2, 376);
        sw(a2, s2, 380);
        mflo(a0);
        div(v1, v0);
        sw(a0, s2, 348);
        mflo(v1);
        v1 = addiu(v1, -1);
        sw(v1, s2, 64);
        v0 = addiu(s2, 80);
        sw(v0, sp, 0x34);
        for (;;) {
            // 0x00516370
            charge(ctx, 5);
            lw(a1, s2, 64);
            a0 = s6;
            jal(ctx, 0x516374u, gen::fn__sceMcpIsSpeckOutBlock_0051ab08);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            lw(v0, s2, 64);
            if (!cc) {
                break;
            }
            backedge(ctx);
            // 0x00516368
            charge(ctx, 2);
            v0 = addiu(v0, -1);
            sw(v0, s2, 64);
        }
        // 0x00516384
        charge(ctx, 1);
        for (;;) {
            // 0x00516388
            charge(ctx, 8);
            v0 = addiu(v0, -1);
            sw(v0, s2, 68);
            lw(a1, s2, 68);
            a0 = s6;
            jal(ctx, 0x516394u, gen::fn__sceMcpIsSpeckOutBlock_0051ab08);
            s1 = v0;
            if (s1 == 0) {
                break;
            }
            lw(v0, s2, 68);
            backedge(ctx);
        }
        // 0x005163a8
        charge(ctx, 30);
        lw(a1, s2, 68);
        a0 = s6;
        link(ctx, 0x5163B0u);  // $ra first: the delay slot below depends on it
        lw(a2, s2, 64);
        call(ctx, gen::fn__sceMcCoreSetWriteBackHole_0051af70);
        lw(v1, s2, 48);
        a3 = si(-1);
        lw(a1, sp, 0x0);
        v1 = sll(v1, 2);
        lw(a2, sp, 0x4);
        a0 = addiu(v1, -1);
        v0 = slt(a3, a0);
        v1 = addiu(v1, 1022);
        if (v0 != 0) v1 = a0;
        mult(a2, a2, a1);
        v1 = sra(v1, 10);
        s4 = addiu(v1, 1);
        v0 = sll(s4, 2);
        a1 = addiu(v0, -1);
        v1 = addiu(a2, 1023);
        a0 = slt(a3, a1);
        v0 = addiu(v0, 1022);
        if (a0 != 0) v0 = a1;
        a3 = slt(a3, a2);
        if (a3 != 0) v1 = a2;
        v0 = sra(v0, 10);
        a1 = sra(v1, 10);
        s5 = addiu(v0, 1);
        v1 = slti(s5, 33);
        s0 = a1;
        if (v1 == 0) {
            // 0x00516420
            charge(ctx, 2);
            s5 = 32;
            s4 = 8192;
        }
        // 0x00516428
        charge(ctx, 7);
        lw(a0, sp, 0x34);
        a1 = 0;
        a2 = 128;
        jal(ctx, 0x516430u, gen::fn_memset_00521408);
        v0 = slt(s1, s5);
        s3 = 0;
        if (v0 == 0) {
            // 0x00516494
            charge(ctx, 2);
            s7 = addiu(s4, -1);
            v0 = 2200;
        } else {
            // 0x00516444
            charge(ctx, 1);
            s7 = addiu(s4, -1);
            for (;;) {
                // 0x00516448
                charge(ctx, 2);
                s4 = addiu(s3, 1);
                s3 = sll(s3, 2);
                for (;;) {
                    // 0x00516450
                    charge(ctx, 8);
                    a1 = s0;
                    a0 = s6;
                    jal(ctx, 0x516454u, gen::fn__sceMcpIsSpeckOutClust_0051ab50);
                    s1 = v0;
                    v1 = addiu(s0, 1);
                    v0 = s1 ^ 0x1;
                    if (v0 == 0) s0 = v1;
                    if (s1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00516470
                charge(ctx, 7);
                lw(v1, sp, 0x34);
                v0 = addu(v1, s3);
                s3 = s4;
                sw(s0, v0, 0);
                v1 = slt(s3, s5);
                s0 = addiu(s0, 1);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0051648c
            charge(ctx, 2);
            v0 = 2200;
        }
        // 0x0051649c
        charge(ctx, 9);
        v1 = 0x980000;
        mult(v0, s6, v0);
        v1 = addiu(v1, -18552);  // &0x97B788
        fp = 0;
        s4 = 0;
        a0 = si(-1);
        s3 = 255;
        v0 = addu(v0, v1);
        v0 = addiu(v0, 1020);
        for (;;) {
            // 0x005164c0
            charge(ctx, 7);
            sw(a0, v0, 0);
            s3 = addiu(s3, -1);
            v0 = addiu(v0, -4);
            if (i64(s3) < 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x005164dc
        charge(ctx, 9);
        v0 = 2200;
        v1 = 0x980000;
        mult(v0, s6, v0);
        v1 = addiu(v1, -18552);  // &0x97B788
        a0 = si(-1);
        s3 = 255;
        v0 = addu(v0, v1);
        v0 = addiu(v0, 2044);
        for (;;) {
            // 0x00516500
            charge(ctx, 7);
            sw(a0, v0, 0);
            s3 = addiu(s3, -1);
            v0 = addiu(v0, -4);
            if (i64(s3) < 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0051651c
        charge(ctx, 3);
        s3 = s7;
        if (i64(s3) < 0) {
            lhu(a0, s2, 42);
        } else {
            // 0x00516528
            charge(ctx, 2);
            s7 = 0x980000;
            for (;;) {
                // 0x00516530
                charge(ctx, 5);
                a0 = s6;
                a1 = s0;
                jal(ctx, 0x516534u, gen::fn__sceMcpIsSpeckOutClust_0051ab50);
                if (v0 != 0) {
                    s0 = addiu(s0, 1);
                    backedge(ctx);
                    continue;
                }
                // 0x00516544
                charge(ctx, 10);
                v0 = 2200;
                s5 = addiu(s7, -17528);
                mult(s1, s6, v0);
                a0 = s6;
                a2 = s0;
                a3 = 1;
                a1 = addu(s1, s5);
                jal(ctx, 0x51655Cu, gen::fn__sceMcpWriteClust_0051a458);
                a1 = addiu(s5, -1024);
                if (v0 == 0) {
                    goto L_005169c4;
                }
                // 0x0051656c
                charge(ctx, 7);
                v0 = sll(s4, 2);
                v0 = addu(v0, s1);
                s4 = addiu(s4, 1);
                v0 = addu(v0, a1);
                v1 = slti(s4, 256);
                sw(s0, v0, 0);
                if (v1 != 0) {
                    // 0x00516588
                    charge(ctx, 2);
                    a2 = addiu(s0, 1);
                    if (s3 == 0) {
                        goto L_00516590;
                    }
                    // 0x005165f4
                    charge(ctx, 1);
                    v0 = addiu(s3, -1);
                L_005165f8:
                    charge(ctx, 3);
                    s3 = v0;
                    s0 = a2;
                    if (i64(s3) < 0) {
                        break;
                    }
                    backedge(ctx);
                    continue;
                }
            L_00516590:
                charge(ctx, 12);
                lw(a0, sp, 0x34);
                v0 = sll(fp, 2);
                s1 = addu(s1, a1);
                fp = addiu(fp, 0x1);
                v0 = addu(a0, v0);
                a1 = s1;
                lw(a2, v0, 0);
                a0 = s6;
                a3 = 1;
                jal(ctx, 0x5165B0u, gen::fn__sceMcpWriteClust_0051a458);
                a2 = addiu(s0, 1);
                if (v0 == 0) {
                    goto L_005169c4;
                }
                // 0x005165c0
                charge(ctx, 4);
                v0 = addiu(s3, -1);
                a1 = addiu(s1, 1020);
                v1 = si(-1);
                s4 = 255;
                for (;;) {
                    // 0x005165d0
                    charge(ctx, 7);
                    sw(v1, a1, 0);
                    s4 = addiu(s4, -1);
                    a1 = addiu(a1, -4);
                    if (i64(s4) < 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x005165ec
                charge(ctx, 2);
                s4 = 0;
                goto L_005165f8;
            }
            // 0x00516604
            charge(ctx, 1);
            lhu(a0, s2, 42);
        }
        // 0x00516608
        charge(ctx, 5);
        a1 = 1000;
        sw(s0, s2, 52);
        s3 = 0;
        if (a0 == 0) {
            brk(ctx, 0x516618u, 0x7u);
        }
        // 0x0051661c
        charge(ctx, 14);
        lhu(a2, s2, 44);
        lw(v0, s2, 68);
        s1 = 0;
        lw(v1, s2, 48);
        mult(v0, v0, a2);
        div1(v1, a1);
        div(v0, a0);
        mflo1(v1);
        mflo(v0);
        mult(v1, v1, a1);
        v0 = subu(v0, s0);
        sw(v0, s2, 56);
        s5 = addiu(v1, 1);
        if (i64(v0) > 0) {
            // 0x00516654
            charge(ctx, 1);
            s4 = addiu(sp, 0x30);
            for (;;) {
                // 0x00516658
                charge(ctx, 2);
                a0 = s6;
                if (s1 == s5) {
                    // 0x00516660
                    charge(ctx, 3);
                    lw(v0, s2, 52);
                    v0 = subu(s0, v0);
                    sw(v0, s2, 368);
                }
                // 0x0051666c
                charge(ctx, 5);
                a1 = s0;
                jal(ctx, 0x51666Cu, gen::fn__sceMcpIsSpeckOutClust_0051ab50);
                v1 = 1;
                a0 = s6;
                if (v0 == v1) {
                    // 0x00516680
                    charge(ctx, 7);
                    a1 = s3;
                    a2 = si(-3);
                    a3 = s4;
                    jal(ctx, 0x516688u, gen::fn__sceMcFatWriteFatData_005157e0);
                    lw(v0, sp, 0x30);
                    ld(ra, sp, 0xD0);
                    if (v0 == 0) {
                        goto L_005166d0;
                    }
                    goto L_0051669c_47;
                }
                // 0x005166a4
                charge(ctx, 2);
                if (s1 == 0) {
                    sw(s0, s2, 52);
                }
                // 0x005166ac
                charge(ctx, 9);
                a2 = 0x7FFF0000;
                a0 = s6;
                a1 = s3;
                a2 = a2 | 0xFFFF;
                a3 = s4;
                jal(ctx, 0x5166BCu, gen::fn__sceMcFatWriteFatData_005157e0);
                lw(v0, sp, 0x30);
                s1 = addiu(s1, 1);
                if (v0 != 0) {
                    goto L_00516a14;
                }
            L_005166d0:
                charge(ctx, 5);
                lw(v0, s2, 56);
                s3 = addiu(s3, 1);
                v0 = slt(s3, v0);
                s0 = addiu(s0, 1);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x005166e4
        charge(ctx, 3);
        v0 = slt(s1, s5);
        s3 = addiu(sp, 0x30);
        if (v0 == 0) {
            // 0x005166f0
            charge(ctx, 8);
            lhu(a2, s2, 44);
            lw(v0, s2, 68);
            a0 = s6;
            lhu(v1, s2, 42);
            a1 = s3;
            mult(v0, v0, a2);
            if (v1 == 0) {
                brk(ctx, 0x51670Cu, 0x7u);
            }
            // 0x00516710
            charge(ctx, 9);
            lw(a2, s2, 52);
            div(v0, v1);
            mflo(v0);
            v0 = subu(v0, a2);
            link(ctx, 0x516720u);  // $ra first: the delay slot below depends on it
            sw(v0, s2, 56);
            call(ctx, gen::fn__sceMcFatGetFreeClust_00515910);
            lw(v1, sp, 0x30);
            s0 = v0;
            if (v1 != 0) {
                // 0x00516734
                charge(ctx, 2);
                v0 = v1;
                goto L_00516a14;
            }
            // 0x0051673c
            charge(ctx, 2);
            a1 = s0;
            if (s0 != 0) {
                // 0x00516744
                charge(ctx, 3);
                a0 = 0x7C0000;
                a0 = addiu(a0, -6592);  // "libmc2: Fatal Error [%08x]\n"
                jal(ctx, 0x516748u, gen::fn_scePrintf_00505e48);
                goto L_00516750;
            }
            // 0x0051675c
            charge(ctx, 135);
            s2 = 0x980000;
            a0 = s6;
            a1 = addiu(sp, 0x10);
            s0 = addiu(s2, -14144);  // &0x97C8C0
            jal(ctx, 0x516768u, gen::fn__sceMcCoreReadClock_0051b5f0);
            s1 = 10;
            a0 = s0;
            a1 = 0;
            a2 = 512;
            jal(ctx, 0x51677Cu, gen::fn_memset_00521408);
            lbu(v1, sp, 0x17);
            t6 = 0x8427;
            lbu(t5, sp, 0x16);
            t7 = 2;
            lbu(t0, sp, 0x15);
            v0 = srl(v1, 4);
            lbu(a2, sp, 0x13);
            t1 = srl(t5, 4);
            lbu(a1, sp, 0x12);
            t2 = srl(t0, 4);
            lbu(a0, sp, 0x11);
            t3 = srl(a2, 4);
            t4 = srl(a1, 4);
            mult(v0, v0, s1);
            a3 = srl(a0, 4);
            mult(t1, t1, s1);
            mult1(t2, t2, s1);
            v1 = v1 & 0xF;
            mult(t3, t3, s1);
            a0 = a0 & 0xF;
            mult1(t4, t4, s1);
            v0 = addu(v0, v1);
            mult(a3, a3, s1);
            t0 = t0 & 0xF;
            a2 = a2 & 0xF;
            a1 = a1 & 0xF;
            t5 = t5 & 0xF;
            sh(t6, s2, -14144);  // 0x97C8C0
            v0 = addiu(v0, 2000);
            t1 = addu(t1, t5);
            a3 = addu(a3, a0);
            t2 = addu(t2, t0);
            t3 = addu(t3, a2);
            t4 = addu(t4, a1);
            sw(t7, s0, 4);  // 0x97C8C4
            v1 = 0x7C0000;
            sh(v0, s0, 14);  // 0x97C8CE
            a1 = 0;
            sb(t1, s0, 13);  // 0x97C8CD
            a2 = 512;
            sb(t2, s0, 12);  // 0x97C8CC
            sb(t3, s0, 11);  // 0x97C8CB
            sb(t4, s0, 10);  // 0x97C8CA
            sb(a3, s0, 9);  // 0x97C8C9
            sh(zero, s0, 2);  // 0x97C8C2
            sb(zero, s0, 8);  // 0x97C8C8
            sw(zero, s0, 16);  // 0x97C8D0
            sw(zero, s0, 20);  // 0x97C8D4
            ldl(v0, s0, 15);  // 0x97C8CF
            ldr(v0, s0, 8);  // 0x97C8C8
            sdl(v0, s0, 31);  // 0x97C8DF
            sdr(v0, s0, 24);  // 0x97C8D8
            sw(zero, s0, 32);  // 0x97C8E0
            a3 = addiu(v1, -6672);  // &0x7BE5F0
            lb(t1, a3, 0);  // 0x7BE5F0
            lb(v0, a3, 1);  // 0x7BE5F1
            sb(t1, s0, 64);  // 0x97C900
            sb(v0, s0, 65);  // 0x97C901
            s0 = addiu(s0, 512);  // &0x97CAC0
            a0 = s0;
            jal(ctx, 0x516870u, gen::fn_memset_00521408);
            lbu(v1, sp, 0x17);
            t6 = 0xA426;
            lbu(t5, sp, 0x16);
            t7 = 0x7C0000;
            lbu(t3, sp, 0x15);
            v0 = srl(v1, 4);
            lbu(t1, sp, 0x13);
            a2 = srl(t5, 4);
            lbu(a1, sp, 0x12);
            a3 = srl(t3, 4);
            lbu(a0, sp, 0x11);
            t2 = srl(t1, 4);
            t4 = srl(a1, 4);
            mult(v0, v0, s1);
            t0 = srl(a0, 4);
            mult(a2, a2, s1);
            mult1(a3, a3, s1);
            v1 = v1 & 0xF;
            mult(t0, t0, s1);
            t1 = t1 & 0xF;
            mult1(t2, t2, s1);
            v0 = addu(v0, v1);
            mult(t4, t4, s1);
            a1 = a1 & 0xF;
            a0 = a0 & 0xF;
            t5 = t5 & 0xF;
            t3 = t3 & 0xF;
            t0 = addu(t0, a0);
            t2 = addu(t2, t1);
            v0 = addiu(v0, 2000);
            a2 = addu(a2, t5);
            a3 = addu(a3, t3);
            t4 = addu(t4, a1);
            sb(a2, s0, 13);  // 0x97CACD
            sb(a3, s0, 12);  // 0x97CACC
            a1 = addiu(s2, -14144);  // &0x97C8C0
            sh(t6, s0, 0);  // 0x97CAC0
            a0 = s6;
            sh(v0, s0, 14);  // 0x97CACE
            a2 = 0;
            sb(t2, s0, 11);  // 0x97CACB
            sb(t4, s0, 10);  // 0x97CACA
            sb(t0, s0, 9);  // 0x97CAC9
            sw(zero, s0, 4);  // 0x97CAC4
            sh(zero, s0, 2);  // 0x97CAC2
            sb(zero, s0, 8);  // 0x97CAC8
            sw(zero, s0, 16);  // 0x97CAD0
            sw(zero, s0, 20);  // 0x97CAD4
            ldl(t0, s0, 15);  // 0x97CACF
            ldr(t0, s0, 8);  // 0x97CAC8
            sdl(t0, s0, 31);  // 0x97CADF
            sdr(t0, s0, 24);  // 0x97CAD8
            sw(zero, s0, 32);  // 0x97CAE0
            v1 = addiu(t7, -6664);  // ".."
            lb(t0, v1, 0);  // 0x7BE5F8
            lb(t1, v1, 1);  // 0x7BE5F9
            lb(v0, v1, 2);  // 0x7BE5FA
            sb(t0, s0, 64);  // 0x97CB00
            sb(t1, s0, 65);  // 0x97CB01
            sb(v0, s0, 66);  // 0x97CB02
            a3 = 1;
            jal(ctx, 0x516968u, gen::fn__sceMcpWriteUserClust_0051aa90);
            a3 = s3;
            if (v0 == 0) {
                goto L_005169c4;
            }
            // 0x00516978
            charge(ctx, 7);
            a0 = s6;
            a1 = 0;
            a2 = si(-1);
            jal(ctx, 0x516980u, gen::fn__sceMcFatWriteFatData_005157e0);
            lw(v0, sp, 0x30);
            ld(ra, sp, 0xD0);
            if (v0 == 0) {
                // 0x00516994
                charge(ctx, 4);
                a0 = s6;
                jal(ctx, 0x516994u, gen::fn__sceMcpFlushCache_0051a498);
                if (v0 == 0) {
                    goto L_005169c4;
                }
                // 0x005169a4
                charge(ctx, 4);
                a0 = s6;
                jal(ctx, 0x5169A4u, gen::fn__sceMcFatFlushFatCache_00515588);
                if (v0 == 0) {
                    goto L_005169c4;
                }
                // 0x005169b4
                charge(ctx, 4);
                a0 = s6;
                jal(ctx, 0x5169B4u, gen::fn__sceMcpWriteSysInfo_0051a2f8);
                if (v0 == 0) {
                    goto L_005169c4;
                }
                v0 = 2200;
                // 0x005169d0
                charge(ctx, 14);
                a0 = 0x980000;
                mult(v0, s6, v0);
                v1 = addiu(a0, -18552);  // &0x97B788
                a2 = 1;
                a0 = s6;
                a1 = 0;
                v1 = addu(v1, v0);
                link(ctx, 0x5169ECu);  // $ra first: the delay slot below depends on it
                sw(a2, v1, 2184);
                call(ctx, gen::fn__sceMcFatGetInfo_00515d80);
                v1 = lui(0x8101);
                a0 = v0;
                v1 = v1 | 0x9003;
                sw(v0, sp, 0x30);
                if (a0 == v1) {
                    // 0x00516a08
                    charge(ctx, 2);
                    sw(zero, sp, 0x30);
                    a0 = 0;
                }
                // 0x00516a10
                charge(ctx, 1);
                v0 = a0;
            L_00516a14:
                charge(ctx, 1);
                ld(ra, sp, 0xD0);
            }
            goto L_00516a18;
        }
    L_00516750:
        charge(ctx, 3);
        v0 = lui(0x8101);
        v0 = v0 | 0x9001;
        goto L_00516a14;
    }
L_005169c4:
    charge(ctx, 3);
    v0 = lui(0x8101);
    v0 = v0 | 0x6F;
    goto L_00516a14;
L_0051669c_47:
    charge(ctx, 2);
    ld(fp, sp, 0xC0);
    // 0x00516a1c (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(s7, sp, 0xB0);
    ld(s6, sp, 0xA0);
    ld(s5, sp, 0x90);
    ld(s4, sp, 0x80);
    ld(s3, sp, 0x70);
    ld(s2, sp, 0x60);
    ld(s1, sp, 0x50);
    ld(s0, sp, 0x40);
    sp = addiu(sp, 0xE0);
    return;
L_00516a18:
    charge(ctx, 1);
    ld(fp, sp, 0xC0);
    // 0x00516a1c (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(s7, sp, 0xB0);
    ld(s6, sp, 0xA0);
    ld(s5, sp, 0x90);
    ld(s4, sp, 0x80);
    ld(s3, sp, 0x70);
    ld(s2, sp, 0x60);
    ld(s1, sp, 0x50);
    ld(s0, sp, 0x40);
    sp = addiu(sp, 0xE0);
}

// 0x0051AD10 SyncDma -- 204 bytes; frame 0x60: s2 sp+0x20, s0 sp+0x0, s4 sp+0x40, s3 sp+0x30, s1 sp+0x10, ra sp+0x50
// Wait for the memory card core's SIF reply and pick the newer of the two reply buffers (by sequence).
void SyncDma(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0051ad10
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v0 = 0x980000;
    sd(s2, sp, 0x20);
    s2 = 0x780000;
    sd(s0, sp, 0x0);
    lw(a0, v0, 21760);  // 0x985500
    s0 = 0x980000;
    sd(s4, sp, 0x40);
    sd(s3, sp, 0x30);
    s4 = s2;
    sd(s1, sp, 0x10);
    sd(ra, sp, 0x50);
    s1 = addiu(s0, 21952);  // &0x9855C0
    sw(zero, s2, 10984);  // 0x782AE8
    s3 = addiu(s1, 128);  // &0x985640
    jal(ctx, 0x51AD48u, gen::fn__sceWaitSema_005031a0);
    a0 = s1;
    a1 = addiu(s1, 255);  // &0x9856BF
    jal(ctx, 0x51AD54u, gen::fn_InvalidDCache_00503b98);
    lw(v1, s0, 21952);  // 0x9855C0
    lw(v0, s2, 10984);  // 0x782AE8
    v0 = slt(v0, v1);
    if (v0 == 0) {
        lw(v1, s3, 0);  // 0x985640
    } else {
        // 0x0051ad70
        charge(ctx, 4);
        lw(v0, s1, 128);
        v0 = slt(v0, v1);
        if (v0 == 0) {
            lw(v1, s3, 0);
            goto L_0051ad88;
        }
        // 0x0051ad80
        charge(ctx, 2);
        sw(v1, s2, 10984);
    L_0051adb8:
        charge(ctx, 1);
        v0 = s1;
        // 0x0051adbc (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x50);
        ld(s4, sp, 0x40);
        ld(s3, sp, 0x30);
        ld(s2, sp, 0x20);
        ld(s1, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x60);
        return;
    }
L_0051ad88:
    charge(ctx, 4);
    lw(v0, s4, 10984);
    v0 = slt(v0, v1);
    if (v0 == 0) {
        sw(zero, s1, 8);
        goto L_0051adb8;
    }
    // 0x0051ad98
    charge(ctx, 4);
    lw(v0, s1, 0);
    v0 = slt(v0, v1);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 0x980000;
    if (cc) {
        // 0x0051adb4
        charge(ctx, 1);
        sw(zero, s1, 8);
        goto L_0051adb8;
    }
    // 0x0051ada8
    charge(ctx, 3);
    sw(v1, s2, 10984);
    v0 = addiu(v0, 22080);
    // 0x0051adbc (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0051ADE0 SyncDmaForRead -- 84 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x10, ra sp+0x20
// Wait for the memory card core's read reply; returns the reply buffer.
void SyncDmaForRead(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051ade0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x980000;
    sd(s0, sp, 0x0);
    lw(a0, v0, 21760);  // 0x985500
    s0 = 0x980000;
    sd(s1, sp, 0x10);
    sd(ra, sp, 0x20);
    s1 = addiu(s0, 21952);  // &0x9855C0
    jal(ctx, 0x51ADFCu, gen::fn__sceWaitSema_005031a0);
    a0 = s1;
    a1 = addiu(s1, 127);  // &0x98563F
    jal(ctx, 0x51AE08u, gen::fn_InvalidDCache_00503b98);
    lw(v0, s0, 21952);  // 0x9855C0
    if (i64(v0) <= 0) {
        sw(zero, s1, 8);  // 0x9855C8
    }
    // 0x0051ae1c
    charge(ctx, 6);
    v0 = s1;
    ld(ra, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0051AE68 _sceMcCoreInit -- 144 bytes; frame 0x30: ra sp+0x20
// Create the core's reply semaphore ("sceMc2_sema_subs") and reset the two socket records.
void _sceMcCoreInit(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051ae68
    enter(ctx, 15);  // entry check point + this block's cycles
    v0 = 0x7C0000;
    sp = addiu(sp, -0x30);
    v1 = 0x780000;
    v0 = addiu(v0, -6552);  // "sceMc2_sema_subs"
    a1 = 127;
    sd(ra, sp, 0x20);
    sw(zero, v1, 10984);  // 0x782AE8
    a0 = sp;
    sw(a1, sp, 0x4);
    sw(v0, sp, 0x14);
    link(ctx, 0x51AE90u);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0x8);
    call(ctx, gen::fn__sceCreateSema_00503160);
    v1 = 0x980000;
    sw(v0, v1, 21760);  // 0x985500
    if (i64(v0) >= 0) {
        // 0x0051aeac
        charge(ctx, 7);
        v0 = 0x980000;
        a3 = 512;
        v1 = addiu(v0, 21768);  // &0x985508
        a2 = 16;
        a1 = addiu(v1, 72);  // &0x985550
        a0 = 16384;
        for (;;) {
            // 0x0051aec8
            charge(ctx, 8);
            sw(zero, v1, 0);
            sw(a3, v1, 8);
            sw(a2, v1, 12);
            sw(a0, v1, 16);
            v1 = addiu(v1, 36);
            v0 = slt(v1, a1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0051aee8
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x0051aea4
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0051aeec (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0051AEF8 _sceMcCoreEnd -- 116 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10, s0 sp+0x0
// Delete the reply semaphore and the two sockets' DBC connections.
void _sceMcCoreEnd(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051aef8
    enter(ctx, 7);  // entry check point + this block's cycles
    v0 = 0x980000;
    sp = addiu(sp, -0x30);
    lw(a0, v0, 21760);  // 0x985500
    sd(ra, sp, 0x20);
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    if (i64(a0) >= 0) {
        // 0x0051af14
        charge(ctx, 2);
        jal(ctx, 0x51AF14u, gen::fn__sceDeleteSema_00503170);
    }
    // 0x0051af1c
    charge(ctx, 5);
    v0 = 0x980000;
    s0 = addiu(v0, 21768);  // &0x985508
    s1 = addiu(s0, 72);  // &0x985550
    lw(v0, s0, 0);  // 0x985508
    for (;;) {
        // 0x0051af30
        charge(ctx, 2);
        if (v0 == 0) {
            s0 = addiu(s0, 36);
        } else {
            // 0x0051af38
            charge(ctx, 4);
            link(ctx, 0x51AF38u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 4);
            call(ctx, gen::fn_sceDbcDeleteSocket_0051c8a0);
            sw(zero, s0, 0);
            s0 = addiu(s0, 36);
        }
        // 0x0051af48
        charge(ctx, 3);
        v0 = slt(s0, s1);
        if (v0 == 0) {
            break;
        }
        lw(v0, s0, 0);
        backedge(ctx);
    }
    // 0x0051af54
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    v0 = 1;
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0051BA88 _sceMcCoreWriteSameData -- 332 bytes; frame 0x90: s0 sp+0x10, s1 sp+0x20, s6 sp+0x70, s4 sp+0x50, s2 sp+0x30, ra sp+0x80, s5 sp+0x60, s3 sp+0x40
// Fill a card range with one value: builds the write-same request for the socket, sends it (retrying) and waits for
// the reply; returns the count on success.
void _sceMcCoreWriteSameData(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051ba88
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    v0 = 36;
    sd(s0, sp, 0x10);
    v1 = 0x980000;
    mult(s0, a0, v0);
    sd(s1, sp, 0x20);
    s1 = addiu(v1, 21768);  // &0x985508
    sd(s6, sp, 0x70);
    sd(s4, sp, 0x50);
    v0 = addiu(s1, 4);  // &0x98550C
    sd(s2, sp, 0x30);
    s4 = a1;
    sd(ra, sp, 0x80);
    s2 = addu(s0, v0);
    sd(s5, sp, 0x60);
    s6 = a2;
    sd(s3, sp, 0x40);
    link(ctx, 0x51BACCu);  // $ra first: the delay slot below depends on it
    lw(a0, s2, 0);
    call(ctx, gen::fn_sceDbcGetConnection_0051cad0);
    v1 = 3;
    a1 = addu(s1, s0);
    if (v0 != v1) {
        // 0x0051bae8
        charge(ctx, 36);
        s3 = 0x980000;
        v0 = a1;
        a3 = 48;
        v1 = v0;
        a0 = v0;
        lw(t0, v1, 12);
        s0 = 0x980000;
        lw(t1, a0, 16);
        s0 = addiu(s0, 21952);  // &0x9855C0
        lw(v1, a1, 20);
        a0 = s0;
        lw(a2, v0, 8);
        a1 = 0;
        sw(s4, s3, 21888);  // 0x985580
        v0 = addiu(s3, 21888);  // &0x985580
        sw(a2, v0, 8);  // 0x985588
        s1 = 0x780000;
        sw(v1, v0, 36);  // 0x9855A4
        a2 = 256;
        sw(t0, v0, 12);  // 0x98558C
        s5 = 0x520000;
        sw(t1, v0, 16);  // 0x985590
        s4 = 1;
        sw(a3, sp, 0x0);
        sw(s6, v0, 4);  // 0x985584
        sw(zero, v0, 20);  // 0x985594
        sw(zero, v0, 24);  // 0x985598
        sw(zero, v0, 28);  // 0x98559C
        link(ctx, 0x51BB58u);  // $ra first: the delay slot below depends on it
        sw(zero, v0, 32);
        call(ctx, gen::fn_memset_00521408);
        a0 = s0;
        a1 = addiu(a0, 255);  // &0x9856BF
        jal(ctx, 0x51BB64u, gen::fn_SyncDCache_00503a58);
        v0 = 11;
        sw(v0, s1, 10988);  // 0x782AEC
        lw(a0, s2, 0);
        for (;;) {
            // 0x0051bb78
            charge(ctx, 7);
            a2 = sp;
            lw(a1, s1, 10988);
            a3 = addiu(s3, 21888);
            t0 = addiu(s5, -20936);
            jal(ctx, 0x51BB84u, gen::fn_sceDbcSendData3_0051d308);
            if (v0 == s4) {
                break;
            }
            lw(a0, s2, 0);
            backedge(ctx);
        }
        // 0x0051bb94
        charge(ctx, 6);
        jal(ctx, 0x51BB94u, gen::fn_SyncDma_0051ad10);
        lw(v1, v0, 8);
        v0 = 0;
        v1 = v1 ^ 0x1;
        if (v1 == 0) v0 = s6;
    } else {
        // 0x0051bae0
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0051bbac (the shared epilogue, written out on this path)
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

// 0x0051C658 sceDbcEnd -- 72 bytes; frame 0x10: ra sp+0x0
// End libdbc: deletes its semaphore when initialised.
void sceDbcEnd(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051c658
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = 0x780000;
    sp = addiu(sp, -0x10);
    lw(v0, v1, 11008);  // 0x782B00
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0051c674
        charge(ctx, 5);
        v0 = 0x990000;
        sw(zero, v1, 11008);
        lw(a0, v0, 28672);  // 0x997000
        v0 = 1;
        if (i64(a0) >= 0) {
            // 0x0051c688
            charge(ctx, 3);
            jal(ctx, 0x51C688u, gen::fn__sceDeleteSema_00503170);
            v0 = 1;
        }
    } else {
        // 0x0051c66c
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0051c694 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0051CAD0 sceDbcGetConnection -- 244 bytes; frame 0x40: s2 sp+0x20, s0 sp+0x0, s1 sp+0x10, ra sp+0x30
// A socket's connection state from the IOP-written table (copied under interrupts off): 1 connected, 3 otherwise.
void sceDbcGetConnection(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051cad0
    enter(ctx, 61);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s2, sp, 0x20);
    sd(s0, sp, 0x0);
    s2 = 0x990000;
    s0 = a0;
    sd(s1, sp, 0x10);
    a0 = addiu(s2, 28480);  // &0x996F40
    sd(ra, sp, 0x30);
    a1 = addiu(a0, 128);  // &0x996FC0
    jal(ctx, 0x51CAF0u, gen::fn_SyncDCache_00503a58);
    s0 = sll(s0, 2);
    jal(ctx, 0x51CAF8u, gen::fn_DIntr_0050d3a0);
    v1 = 0x990000;
    a2 = addiu(s2, 28480);  // &0x996F40
    a1 = addiu(v1, 28608);  // &0x996FC0
    ldl(v0, a2, 7);  // 0x996F47
    ldr(v0, a2, 0);  // 0x996F40
    ldl(a0, a2, 15);  // 0x996F4F
    ldr(a0, a2, 8);  // 0x996F48
    sdl(v0, a1, 7);  // 0x996FC7
    sdr(v0, a1, 0);  // 0x996FC0
    sdl(a0, a1, 15);  // 0x996FCF
    sdr(a0, a1, 8);  // 0x996FC8
    ldl(v0, a2, 23);  // 0x996F57
    ldr(v0, a2, 16);  // 0x996F50
    ldl(a0, a2, 31);  // 0x996F5F
    ldr(a0, a2, 24);  // 0x996F58
    sdl(v0, a1, 23);  // 0x996FD7
    sdr(v0, a1, 16);  // 0x996FD0
    sdl(a0, a1, 31);  // 0x996FDF
    sdr(a0, a1, 24);  // 0x996FD8
    ldl(v0, a2, 39);  // 0x996F67
    ldr(v0, a2, 32);  // 0x996F60
    ldl(a0, a2, 47);  // 0x996F6F
    ldr(a0, a2, 40);  // 0x996F68
    sdl(v0, a1, 39);  // 0x996FE7
    sdr(v0, a1, 32);  // 0x996FE0
    sdl(a0, a1, 47);  // 0x996FEF
    sdr(a0, a1, 40);  // 0x996FE8
    ldl(v0, a2, 55);  // 0x996F77
    ldr(v0, a2, 48);  // 0x996F70
    ldl(a0, a2, 63);  // 0x996F7F
    ldr(a0, a2, 56);  // 0x996F78
    sdl(v0, a1, 55);  // 0x996FF7
    sdr(v0, a1, 48);  // 0x996FF0
    sdl(a0, a1, 63);  // 0x996FFF
    sdr(a0, a1, 56);  // 0x996FF8
    s1 = addiu(v1, 28608);  // &0x996FC0
    jal(ctx, 0x51CB8Cu, gen::fn_EIntr_0050d3f0);
    a0 = 1;
    s0 = addu(s0, s1);
    v0 = 3;
    lw(v1, s0, 0);
    ld(ra, sp, 0x30);
    v1 = v1 ^ 0x1;
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    if (v1 == 0) v0 = a0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0051DAD8 sceSkQuit -- 8 bytes; leaf frame (no stack)
// Sound kernel quit stub: returns 0.
void sceSkQuit(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0051dad8
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x005214C8 __malloc_lock -- 88 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// newlib malloc lock: outside interrupts, nests a count and disables interrupts on the first lock.
void __malloc_lock(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, t7{ctx, 15}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005214c8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    jal(ctx, 0x5214D4u, gen::fn_QueryIntrContext_00503c30);
    t7 = 1;
    s0 = 0x780000;
    if (v0 != t7) {
        // 0x005214e8
        charge(ctx, 3);
        lw(t7, s0, 13208);
        cc = t7 != 0;  // the condition, before the delay slot changes it
        t7 = addiu(t7, 1);
        if (!cc) {
            // 0x005214f4
            charge(ctx, 6);
            jal(ctx, 0x5214F4u, gen::fn_DIntr_0050d3a0);
            t7 = 0x780000;
            sw(v0, t7, libs6::lo(libs6::kMallocIntrWasOn));  // 0x78339C
            lw(t7, s0, 13208);
            t7 = addiu(t7, 1);
        }
        // 0x0052150c
        charge(ctx, 1);
        sw(t7, s0, 13208);
    }
    // 0x00521510 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00521520 __malloc_unlock -- 84 bytes; frame 0x10: ra sp+0x0
// newlib malloc unlock: outside interrupts, re-enables interrupts when the count drops to 0.
void __malloc_unlock(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, t6{ctx, 14}, t7{ctx, 15}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00521520
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x521528u, gen::fn_QueryIntrContext_00503c30);
    t7 = 1;
    t6 = 0x780000;
    if (v0 != t7) {
        // 0x0052153c
        charge(ctx, 4);
        lw(t7, t6, 13208);
        t7 = addiu(t7, -1);
        sw(t7, t6, 13208);
        if (t7 != 0) {
            goto L_00521568;
        }
        // 0x0052154c
        charge(ctx, 4);
        t6 = 0x780000;
        lw(t7, t6, libs6::lo(libs6::kMallocIntrWasOn));  // 0x78339C
        ld(ra, sp, 0x0);
        if (t7 == 0) {
            // 0x0052156c (the shared epilogue, written out on this path)
            charge(ctx, 2);
            sp = addiu(sp, 0x10);
            return;
        }
        // 0x0052155c
        charge(ctx, 3);
        sw(zero, t6, 13212);
        sp = addiu(sp, 0x10);
        gen::fn_EIntr_0050d3f0(ctx);  // tail call
        return;
    }
L_00521568:
    charge(ctx, 1);
    ld(ra, sp, 0x0);
    // 0x0052156c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x00522F38 _read_r -- 92 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// Reentrant read: clears errno, calls read, copies errno into the reent record on -1.
void _read_r(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00522f38
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    sd(s0, sp, 0x0);
    s1 = a0;
    sd(ra, sp, 0x10);
    a0 = a1;
    s0 = 0x9B0000;
    a1 = a2;
    sw(zero, s0, libs6::lo(libs6::kErrno));  // 0x9ACC20
    a2 = a3;
    jal(ctx, 0x522F5Cu, gen::fn_read_005037a8);
    t7 = v0;
    t6 = si(-1);
    v0 = t7;
    if (t7 == t6) {
        // 0x00522f74
        charge(ctx, 3);
        lw(t7, s0, -13280);
        if (t7 != 0) {
            sw(t7, s1, 0);
        }
    }
    // 0x00522f80 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00523930 _sbrk_r -- 80 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Reentrant sbrk: clears errno, calls sbrk, copies errno into the reent record on -1.
void _sbrk_r(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00523930
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s0 = 0x9B0000;
    sd(ra, sp, 0x10);
    s1 = a0;
    sw(zero, s0, libs6::lo(libs6::kErrno));  // 0x9ACC20
    a0 = a1;
    jal(ctx, 0x52394Cu, gen::fn_sbrk_00503860);
    t7 = si(-1);
    if (v0 != t7) {
        ld(s0, sp, 0x0);
    } else {
        // 0x00523960
        charge(ctx, 3);
        lw(t7, s0, -13280);
        if (t7 != 0) {
            sw(t7, s1, 0);
        }
        // 0x0052396c
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    }
    // 0x00523970 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00528970 _write_r -- 92 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// Reentrant write: clears errno, calls write, copies errno into the reent record on -1.
void _write_r(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00528970
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    sd(s0, sp, 0x0);
    s1 = a0;
    sd(ra, sp, 0x10);
    a0 = a1;
    s0 = 0x9B0000;
    a1 = a2;
    sw(zero, s0, libs6::lo(libs6::kErrno));  // 0x9ACC20
    a2 = a3;
    jal(ctx, 0x528994u, gen::fn_write_00503728);
    t7 = v0;
    t6 = si(-1);
    v0 = t7;
    if (t7 == t6) {
        // 0x005289ac
        charge(ctx, 3);
        lw(t7, s0, -13280);
        if (t7 != 0) {
            sw(t7, s1, 0);
        }
    }
    // 0x005289b8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

}  // namespace p3fes::game
