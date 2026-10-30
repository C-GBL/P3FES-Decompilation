// Phase 5 slice libs26: SCE runtime and CRI leftovers from 0x4C72D8-0x56CB58 that reach no probe: the DMAC
// channel helpers, the sceMpeg MPEG-2 extension parsers, the kernel call wrappers (syscall stubs), the SIF RPC
// data / bind / request handlers, the file-I/O RPC wrappers (sceMkdir .. sceReadlink), the IOP heap queries, the
// TLB set-up and miss handler, the CD/DVD, pad, sound-remote and DBC RPC calls, and the ADXF / ROFS directory
// helpers. Every body is p3fes_handgen's, register for register and block for block as the recompiled body
// (frame, spills, $ra links, cycle charges and check points: game/include/p3fes/game/hg_cpu.h); the line above each
// body gives its role, read from the instructions, and libs26.h names the records' offsets.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs26.h"

namespace p3fes::recomp_gen {
void fn_ADXM_ExecMain_00540ec0(p3fes::EEContext&);
void fn_AddSbusIntcHandler_00502de0(p3fes::EEContext&);
void fn_CancelWakeupThread_005030b0(p3fes::EEContext&);
void fn_CheckAddress_004fa890(p3fes::EEContext&);
void fn_CpuConfig_005033f0(p3fes::EEContext&);
void fn_DIntr_0050d3a0(p3fes::EEContext&);
void fn_DPRINT_0051d588(p3fes::EEContext&);
void fn_DisableCache_005033c0(p3fes::EEContext&);
void fn_DisableDispatchThread_00502fd0(p3fes::EEContext&);
void fn_DisableDmacHandler_00503380(p3fes::EEContext&);
void fn_DisableIntcHandler_00503340(p3fes::EEContext&);
void fn_EIntr_0050d3f0(p3fes::EEContext&);
void fn_EnableCache_005033b0(p3fes::EEContext&);
void fn_EnableDispatchThread_00502fe0(p3fes::EEContext&);
void fn_EnableDmacHandler_00503360(p3fes::EEContext&);
void fn_EnableIntcHandler_00503320(p3fes::EEContext&);
void fn_ExitThread_00502f90(p3fes::EEContext&);
void fn_Exit_0050da58(p3fes::EEContext&);
void fn_GetCop0_005033d0(p3fes::EEContext&);
void fn_GetGsHParam_00503220(p3fes::EEContext&);
void fn_GetGsVParam_00503230(p3fes::EEContext&);
void fn_GetOsdConfigParam2_00503470(p3fes::EEContext&);
void fn_InitTLB32MB_0050ce40(p3fes::EEContext&);
void fn_Interrupt2Iop_00502e00(p3fes::EEContext&);
void fn_JoinThread_00503110(p3fes::EEContext&);
void fn_KSeg0_005033a0(p3fes::EEContext&);
void fn_MachineType_005035b0(p3fes::EEContext&);
void fn_PSMode_005035a0(p3fes::EEContext&);
void fn_RFDIR_GetDirEnt_0056c0f8(p3fes::EEContext&);
void fn_RFDIR_SearchPath_0056c7e8(p3fes::EEContext&);
void fn_RFDIR_SetDirEnt_0056c188(p3fes::EEContext&);
void fn_RFMAI_CopyStructCdDr_0056a348(p3fes::EEContext&);
void fn_RFMAI_CopyStructCdPt_0056a468(p3fes::EEContext&);
void fn_RFMAI_DescrambleG_00569d90(p3fes::EEContext&);
void fn_RFMAI_ReadWG_00569538(p3fes::EEContext&);
void fn_RFPFS_PfsLock_0056ab90(p3fes::EEContext&);
void fn_RFU000_FullReset_00502d40(p3fes::EEContext&);
void fn_RFU003_00502d70(p3fes::EEContext&);
void fn_RFU005_00502d90(p3fes::EEContext&);
void fn_RFU008_00502dc0(p3fes::EEContext&);
void fn_RFU009_00502dd0(p3fes::EEContext&);
void fn_RFU060_00503120(p3fes::EEContext&);
void fn_RFU061_00503130(p3fes::EEContext&);
void fn_RFU063_00503150(p3fes::EEContext&);
void fn_RFU073_005031f0(p3fes::EEContext&);
void fn_RFU080_CreateEventFlag_00503260(p3fes::EEContext&);
void fn_RFU081_DeleteEventFlag_00503270(p3fes::EEContext&);
void fn_RFU082_SetEventFlag_00503280(p3fes::EEContext&);
void fn_RFU083_iSetEventFlag_00503290(p3fes::EEContext&);
void fn_RFU084_ClearEventFlag_005032a0(p3fes::EEContext&);
void fn_RFU085_iClearEventFlag_005032b0(p3fes::EEContext&);
void fn_RFU086_WaitEvnetFlag_005032c0(p3fes::EEContext&);
void fn_RFU087_PollEvnetFlag_005032d0(p3fes::EEContext&);
void fn_RFU088_iPollEvnetFlag_005032e0(p3fes::EEContext&);
void fn_RFU089_ReferEventFlagStatus_005032f0(p3fes::EEContext&);
void fn_RFU090_iReferEventFlagStatus_00503300(p3fes::EEContext&);
void fn_RFU091_00503310(p3fes::EEContext&);
void fn_RFU116_005034e0(p3fes::EEContext&);
void fn_ROFS_ChangeDir_00565b90(p3fes::EEContext&);
void fn_ROFS_DelVolume_00566488(p3fes::EEContext&);
void fn_ROFS_GetNumTr_00566050(p3fes::EEContext&);
void fn_ROFS_LoadDir_00566a58(p3fes::EEContext&);
void fn_ReferSemaStatus_005031d0(p3fes::EEContext&);
void fn_ReleaseAlarm_00502ef0(p3fes::EEContext&);
void fn_ReleaseWaitThread_00503030(p3fes::EEContext&);
void fn_RemoveSbusIntcHandler_00502df0(p3fes::EEContext&);
void fn_ResetEE_00502d50(p3fes::EEContext&);
void fn_SetAlarm_00502ee0(p3fes::EEContext&);
void fn_SetCPUTimerHandler_00503440(p3fes::EEContext&);
void fn_SetCPUTimer_00503450(p3fes::EEContext&);
void fn_SetGsHParam_00503240(p3fes::EEContext&);
void fn_SetGsVParam_00503250(p3fes::EEContext&);
void fn_SetOsdConfigParam2_00503460(p3fes::EEContext&);
void fn_SetPgifHandler_005034c0(p3fes::EEContext&);
void fn_SetVInterruptHandler_00502e30(p3fes::EEContext&);
void fn_WaitDma_004fa798(p3fes::EEContext&);
void fn_WatchDma_004fa808(p3fes::EEContext&);
void fn__DelayThreadHandler_00504418(p3fes::EEContext&);
void fn__alarm_bind_00506f40(p3fes::EEContext&);
void fn__alarm_rdata_00506c78(p3fes::EEContext&);
void fn__copyrightExtension_004ffc18(p3fes::EEContext&);
void fn__dispRefImage_0_004c72d8(p3fes::EEContext&);
void fn__fs_version_00508378(p3fes::EEContext&);
void fn__iRotateThreadReadyQueue_00503020(p3fes::EEContext&);
void fn__isceSifSetDma_00503530(p3fes::EEContext&);
void fn__kTLBException_0050d040(p3fes::EEContext&);
void fn__pad_intr_hdr_00511288(p3fes::EEContext&);
void fn__pictureDisplayExtension_004ffcb0(p3fes::EEContext&);
void fn__pictureSpatialScalableExtension_004ff7a8(p3fes::EEContext&);
void fn__print_005034f0(p3fes::EEContext&);
void fn__quantMatrixExtension_004ff4b8(p3fes::EEContext&);
void fn__request_bind_00506f80(p3fes::EEContext&);
void fn__request_rdata_00506cb8(p3fes::EEContext&);
void fn__sceCd_ncmd_prechk_0050ff58(p3fes::EEContext&);
void fn__sceCd_scmd_prechk_00510258(p3fes::EEContext&);
void fn__sceCopy_0_0050d478(p3fes::EEContext&);
void fn__sceCopy_1_0050d6c0(p3fes::EEContext&);
void fn__sceCopy_2_0050d830(p3fes::EEContext&);
void fn__sceCreateSema_00503160(p3fes::EEContext&);
void fn__sceDeleteSema_00503170(p3fes::EEContext&);
void fn__sceDeleteThread_00502f70(p3fes::EEContext&);
void fn__sceFsSigSema_00508078(p3fes::EEContext&);
void fn__sceFsWaitS_00508048(p3fes::EEContext&);
void fn__sceFs_Poff_Intr_00508128(p3fes::EEContext&);
void fn__sceGetEntryAddress_0_0050d708(p3fes::EEContext&);
void fn__sceMpegError_00502668(p3fes::EEContext&);
void fn__sceMpegNextBit_004fd658(p3fes::EEContext&);
void fn__scePollSema_005031b0(p3fes::EEContext&);
void fn__sceRpcFreePacket_00506b18(p3fes::EEContext&);
void fn__sceRpcGetFPacket2_00506b68(p3fes::EEContext&);
void fn__sceRpcGetFPacket_00506b38(p3fes::EEContext&);
void fn__sceRpcGetPacket_00506a70(p3fes::EEContext&);
void fn__sceSetSyscall_1_0050d6b0(p3fes::EEContext&);
void fn__sceSetSyscall_2_0050d870(p3fes::EEContext&);
void fn__sceSignalSema_00503180(p3fes::EEContext&);
void fn__sceTerminateThread_00502fb0(p3fes::EEContext&);
void fn__sceWaitSema_005031a0(p3fes::EEContext&);
void fn__sce_SetTLBEntry_0050cd60(p3fes::EEContext&);
void fn__sce_iSuspendThread_005030e0(p3fes::EEContext&);
void fn__sceiSignalSema_00503190(p3fes::EEContext&);
void fn__search_svdata_00506ef0(p3fes::EEContext&);
void fn__sequenceDisplayExtension_004ffb88(p3fes::EEContext&);
void fn__sequenceExtension_004ff378(p3fes::EEContext&);
void fn__sequenceScalableExtension_004ff5a0(p3fes::EEContext&);
void fn__waitIpuIdle_0_004ff998(p3fes::EEContext&);
void fn__xlaunch_0050d140(p3fes::EEContext&);
void fn_adxf_GetStat_0053dbc8(p3fes::EEContext&);
void fn_adxf_LoadPartitionNw_0053b8d0(p3fes::EEContext&);
void fn_cdvd_exit_0050fa48(p3fes::EEContext&);
void fn_cmd_sem_init_0050f960(p3fes::EEContext&);
void fn_get_iob_00507bc8(p3fes::EEContext&);
void fn_iCancelWakeupThread_005030c0(p3fes::EEContext&);
void fn_iCpuConfig_00503420(p3fes::EEContext&);
void fn_iDisableDmacHandler_00503390(p3fes::EEContext&);
void fn_iDisableIntcHandler_00503350(p3fes::EEContext&);
void fn_iEnableDmacHandler_00503370(p3fes::EEContext&);
void fn_iEnableIntcHandler_00503330(p3fes::EEContext&);
void fn_iFlushCache_00503410(p3fes::EEContext&);
void fn_iGetCop0_00503400(p3fes::EEContext&);
void fn_iGsGetIMR_00503490(p3fes::EEContext&);
void fn_iGsPutIMR_005034b0(p3fes::EEContext&);
void fn_iPollSema_005031c0(p3fes::EEContext&);
void fn_iReferSemaStatus_005031e0(p3fes::EEContext&);
void fn_iReleaseAlarm_00502f50(p3fes::EEContext&);
void fn_iReleaseWaitThread_00503040(p3fes::EEContext&);
void fn_iResumeThread_00503100(p3fes::EEContext&);
void fn_iSetAlarm_00502f40(p3fes::EEContext&);
void fn_iSetTimerAlarm_0050f1c0(p3fes::EEContext&);
void fn_iSuspendThread_00504140(p3fes::EEContext&);
void fn_iTerminateThread_00502fc0(p3fes::EEContext&);
void fn_isceSifDmaStat_00503510(p3fes::EEContext&);
void fn_isceSifSetDma_00506110(p3fes::EEContext&);
void fn_kprintf_00505ec8(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_rfdirStrncmpi_0056b9a8(p3fes::EEContext&);
void fn_rfdir_getDirEnt_0056bdc0(p3fes::EEContext&);
void fn_rfdir_getOneDirEnt_0056bcb0(p3fes::EEContext&);
void fn_rfdir_getTokenSize_0056bba0(p3fes::EEContext&);
void fn_rfdir_searchPath_0056c5f0(p3fes::EEContext&);
void fn_rfmai_decipherSectors_00569c00(p3fes::EEContext&);
void fn_rfmai_readRootDirRec_00567750(p3fes::EEContext&);
void fn_sceAddDrv_00509d80(p3fes::EEContext&);
void fn_sceCdBreak_00510f88(p3fes::EEContext&);
void fn_sceCdDiskReady_old_00510748(p3fes::EEContext&);
void fn_sceCdNcmdDiskReady_005100b0(p3fes::EEContext&);
void fn_sceCdSeek_00510d60(p3fes::EEContext&);
void fn_sceCdSyncS_005101e8(p3fes::EEContext&);
void fn_sceChstat_0050a410(p3fes::EEContext&);
void fn_sceDbcSearchPortSpecific_0051cdd8(p3fes::EEContext&);
void fn_sceDclose_00509f98(p3fes::EEContext&);
void fn_sceDevctl_0050af18(p3fes::EEContext&);
void fn_sceDmaPutStallAddr_004fac08(p3fes::EEContext&);
void fn_sceDmaRecvI_004fae40(p3fes::EEContext&);
void fn_sceDmaRecv_004fad78(p3fes::EEContext&);
void fn_sceDmaRestart_004fafc8(p3fes::EEContext&);
void fn_sceDmaSendI_004fad00(p3fes::EEContext&);
void fn_sceDmaWatch_004faef8(p3fes::EEContext&);
void fn_sceDread_0050a100(p3fes::EEContext&);
void fn_sceFormat_00509b00(p3fes::EEContext&);
void fn_sceFsInit_00508170(p3fes::EEContext&);
void fn_sceFsSetIopBuf_00508440(p3fes::EEContext&);
void fn_sceFsSetIopPrio_00508580(p3fes::EEContext&);
void fn_sceFsSifCallRpc_00507ad8(p3fes::EEContext&);
void fn_sceGetstat_0050a258(p3fes::EEContext&);
void fn_sceIoctl2_00509570(p3fes::EEContext&);
void fn_sceMkdir_00509928(p3fes::EEContext&);
void fn_sceMount_0050aa38(p3fes::EEContext&);
void fn_scePadSetDmaCallback_00512710(p3fes::EEContext&);
void fn_scePrintf_00505e48(p3fes::EEContext&);
void fn_sceReadlink_0050b3b8(p3fes::EEContext&);
void fn_sceRename_0050a660(p3fes::EEContext&);
void fn_sceSdRemoteCallbackQuit_00512e48(p3fes::EEContext&);
void fn_sceSdRemote_005129c0(p3fes::EEContext&);
void fn_sceSifBindRpc_00507050(p3fes::EEContext&);
void fn_sceSifCallRpc_00507230(p3fes::EEContext&);
void fn_sceSifExecRequest_00507758(p3fes::EEContext&);
void fn_sceSifFreeIopHeap_0050b788(p3fes::EEContext&);
void fn_sceSifGetOtherData_00506d88(p3fes::EEContext&);
void fn_sceSifInitRpc_005068a8(p3fes::EEContext&);
void fn_sceSifLoadIopHeap_0050b7a8(p3fes::EEContext&);
void fn_sceSifQueryMaxFreeMemSize_0050b908(p3fes::EEContext&);
void fn_sceSifQueryMemSize_0050b898(p3fes::EEContext&);
void fn_sceSifRemoveRpcQueue_00507670(p3fes::EEContext&);
void fn_sceSifRemoveRpc_005075d8(p3fes::EEContext&);
void fn_sceSifSendCmd_005064a8(p3fes::EEContext&);
void fn_sceSifSetDmaInternal_00505fc0(p3fes::EEContext&);
void fn_sceSifSetDma_00506088(p3fes::EEContext&);
void fn_sceSifWriteBackDCache_00506670(p3fes::EEContext&);
void fn_sceSymlink_0050b1c0(p3fes::EEContext&);
void fn_strcmp_00524128(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_sub_506630_00506630(p3fes::EEContext&);
void fn_sub_5067F8_005067f8(p3fes::EEContext&);
void fn_sub_53B680_0053b680(p3fes::EEContext&);
void fn_sub_53B760_0053b760(p3fes::EEContext&);
void fn_sub_53C198_0053c198(p3fes::EEContext&);
void fn_sub_53C200_0053c200(p3fes::EEContext&);
void fn_sub_53C2A0_0053c2a0(p3fes::EEContext&);
void fn_sub_53D450_0053d450(p3fes::EEContext&);
void fn_sub_555D70_00555d70(p3fes::EEContext&);
void fn_sub_5598B0_005598b0(p3fes::EEContext&);
void fn_sub_559B98_00559b98(p3fes::EEContext&);
void fn_sub_55FA40_0055fa40(p3fes::EEContext&);
void fn_sub_560378_00560378(p3fes::EEContext&);
void fn_sub_560698_00560698(p3fes::EEContext&);
void fn_sub_564038_00564038(p3fes::EEContext&);
void fn_sub_564320_00564320(p3fes::EEContext&);
void fn_sub_5646C0_005646c0(p3fes::EEContext&);
void fn_sub_564830_00564830(p3fes::EEContext&);
void fn_sub_569730_00569730(p3fes::EEContext&);
void fn_sub_569810_00569810(p3fes::EEContext&);
void fn_sub_56A040_0056a040(p3fes::EEContext&);
void fn_sub_56ABE0_0056abe0(p3fes::EEContext&);
void fn_sub_56CA20_0056ca20(p3fes::EEContext&);
void fn_sub_56CA38_0056ca38(p3fes::EEContext&);
void fn_sub_56CB58_0056cb58(p3fes::EEContext&);
void fn_use_iob_cnt_005079d0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x004C72D8 _dispRefImage_0 -- 4 bytes; leaf frame (no stack)
// A 4-byte fragment the symbol map names as a function: one `dsra32 $v0, $v0, 0` that runs on into the next symbol
// (0x4C72DC), which this build does not treat as reachable; the body ends there.
void _dispRefImage_0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x004c72d8
    enter(ctx, 1);  // entry check point + this block's cycles
    v0 = dsra32(v0, 0);
    rt::unreachable(0x4C72DCu);
}

// 0x004FAC08 sceDmaPutStallAddr -- 20 bytes; leaf frame (no stack)
// sceDmaPutStallAddr(addr): swaps the DMAC stall address register D_STADR (0x1000E060): the old value in $v0, `addr`
// stored.
void sceDmaPutStallAddr(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x004fac08
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = 0x10000000;
    v1 = v1 | 0xE060;
    lw(v0, v1, 0);  // 0x1000E060 D_STADR (dmac::kStadr)
    sw(a0, v1, 0);  // 0x1000E060 D_STADR (dmac::kStadr)
}

// 0x004FAD00 sceDmaSendI -- 116 bytes; frame 0x40: s0 sp+0x0, s2 sp+0x20, s1 sp+0x10, ra sp+0x30
// sceDmaSendI(ch, addr, qwc): waits for the channel (WaitDma), stores the checked address (CheckAddress) in MADR
// unless MADR holds -1, QWC = qwc, then CHCR = (CHCR & ~0xC) | 0x109 (STR, MOD = 2 interleave, DIR = from memory).
void sceDmaSendI(EEContext& ctx) {
    using namespace hg;
    using namespace libs26;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004fad00
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x10);
    s2 = a2;
    sd(ra, sp, 0x30);
    a0 = a1;
    jal(ctx, 0x4FAD1Cu, gen::fn_CheckAddress_004fa890);
    s1 = v0;
    a0 = s0;
    jal(ctx, 0x4FAD28u, gen::fn_WaitDma_004fa798);
    v0 = lui(0xFFFF);
    lw(v1, s0, dmac::kMadr);
    v0 = v0 | 0xFFFF;
    if (v1 != v0) {
        sw(s1, s0, dmac::kMadr);
    }
    // 0x004fad44
    charge(ctx, 12);
    lw(v0, s0, dmac::kChcr);
    v1 = si(-13);
    sw(s2, s0, dmac::kQwc);
    v0 = v0 & v1;
    ld(ra, sp, 0x30);
    v0 = v0 | 0x109;
    ld(s2, sp, 0x20);
    sw(v0, s0, dmac::kChcr);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x004FAD78 sceDmaRecv -- 72 bytes; frame 0x20: s0 sp+0x0, ra sp+0x10
// sceDmaRecv(ch): waits for the channel, QWC = 0, then CHCR = ((CHCR & ~0xC) | 4) & ~1 | 0x100 (STR, MOD = 1 chain,
// DIR = to memory).
void sceDmaRecv(EEContext& ctx) {
    using namespace hg;
    using namespace libs26;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004fad78
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s0 = a0;
    jal(ctx, 0x4FAD84u, gen::fn_WaitDma_004fa798);
    lw(v0, s0, dmac::kChcr);
    v1 = si(-13);
    a0 = si(-2);
    sw(zero, s0, dmac::kQwc);
    v0 = v0 & v1;
    ld(ra, sp, 0x10);
    v0 = v0 | 0x4;
    v0 = v0 & a0;
    v0 = v0 | 0x100;
    sw(v0, s0, dmac::kChcr);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004FAE40 sceDmaRecvI -- 128 bytes; frame 0x40: s0 sp+0x0, s2 sp+0x20, s1 sp+0x10, ra sp+0x30
// sceDmaRecvI(ch, addr, qwc): as sceDmaSendI with DIR cleared (to memory): CHCR = ((CHCR & ~0xC) | 8) & ~1 | 0x100.
void sceDmaRecvI(EEContext& ctx) {
    using namespace hg;
    using namespace libs26;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004fae40
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x10);
    s2 = a2;
    sd(ra, sp, 0x30);
    a0 = a1;
    jal(ctx, 0x4FAE5Cu, gen::fn_CheckAddress_004fa890);
    s1 = v0;
    a0 = s0;
    jal(ctx, 0x4FAE68u, gen::fn_WaitDma_004fa798);
    v0 = lui(0xFFFF);
    lw(v1, s0, dmac::kMadr);
    v0 = v0 | 0xFFFF;
    if (v1 != v0) {
        sw(s1, s0, dmac::kMadr);
    }
    // 0x004fae84
    charge(ctx, 15);
    lw(v0, s0, dmac::kChcr);
    v1 = si(-13);
    a0 = si(-2);
    sw(s2, s0, dmac::kQwc);
    v0 = v0 & v1;
    ld(ra, sp, 0x30);
    v0 = v0 | 0x8;
    ld(s2, sp, 0x20);
    v0 = v0 & a0;
    ld(s1, sp, 0x10);
    v0 = v0 | 0x100;
    sw(v0, s0, dmac::kChcr);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x004FAEF8 sceDmaWatch -- 52 bytes; frame 0x10: ra sp+0x0
// sceDmaWatch(ch, addr, mode, count): mode 1 returns MADR < addr; any other mode passes (ch, addr, count) on to
// WatchDma and returns 0.
void sceDmaWatch(EEContext& ctx) {
    using namespace hg;
    using namespace libs26;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004faef8
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 1;
    sd(ra, sp, 0x0);
    if (a2 != v0) {
        // 0x004faf14
        charge(ctx, 3);
        a2 = a3;
        jal(ctx, 0x4FAF14u, gen::fn_WatchDma_004fa808);
        v0 = 0;
    } else {
        // 0x004faf08
        charge(ctx, 3);
        lw(v0, a0, dmac::kMadr);
        v0 = sltu(v0, a1);
    }
    // 0x004faf20 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x004FAFC8 sceDmaRestart -- 20 bytes; leaf frame (no stack)
// sceDmaRestart(ch, chcr): writes `chcr` to the channel's CHCR and returns the old STR bit (bit 8).
void sceDmaRestart(EEContext& ctx) {
    using namespace hg;
    using namespace libs26;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x004fafc8
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, a0, dmac::kChcr);
    sw(a1, a0, dmac::kChcr);
    v0 = srl(v0, 8);
    v0 = v0 & 0x1;
}

// 0x004FF378 _sequenceExtension -- 320 bytes; frame 0x70: s1 sp+0x10, s0 sp+0x0, s5 sp+0x50, s4 sp+0x40, s3 sp+0x30, s2 sp+0x20, ra sp+0x60
// MPEG-2 sequence_extension (sceMpeg decoder, $a0 = the decoder): clears IPU_CTRL bit 23, reads 28 bits
// (profile/level, progressive, chroma format, size extensions), requires 4:2:0 ("_chroma_format needs to be 1: 420"),
// reads 16 more bits and checks the profile/level byte against 0x48 / 0x58 / 0x44, then folds the extension bits into
// the picture size and bit-rate words (+308 / +312 / +324 / +328).
void _sequenceExtension(EEContext& ctx) {
    using namespace hg;
    using namespace libs26;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x004ff378
    enter(ctx, 31);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    a2 = 0x10000000;
    sd(s1, sp, 0x10);
    a2 = a2 | 0x2010;
    sd(s0, sp, 0x0);
    s1 = a0;
    sd(s5, sp, 0x50);
    s0 = 1;
    sd(s4, sp, 0x40);
    v0 = lui(0xFF7F);
    sd(s3, sp, 0x30);
    v0 = v0 | 0xFFFF;
    sd(s2, sp, 0x20);
    sd(ra, sp, 0x60);
    a1 = 28;
    sw(s0, s1, mpeg::kSeqExtSeen);
    lw(v1, a2, 0);  // 0x10002010 IPU_CTRL (ipu::kCtrl)
    v1 = v1 & v0;
    link(ctx, 0x4FF3C0u);  // $ra first: the delay slot below depends on it
    sw(v1, a2, 0);
    call(ctx, gen::fn__sceMpegNextBit_004fd658);
    s2 = v0;
    v1 = srl(s2, 1);
    v0 = srl(s2, 17);
    s5 = v1 & 0xFFF;
    v0 = v0 & 0x3;
    a0 = srl(s2, 13);
    v1 = srl(s2, 15);
    s4 = a0 & 0x3;
    s3 = v1 & 0x3;
    sw(v0, s1, mpeg::kChromaFormat);
    if (v0 != s0) {
        // 0x004ff3f4
        charge(ctx, 4);
        a1 = 0x7C0000;
        a0 = s1;
        a1 = addiu(a1, -10608);  // "_chroma_format needs to be 1: 420"
        jal(ctx, 0x4FF3FCu, gen::fn__sceMpegError_00502668);
    }
    // 0x004ff404
    charge(ctx, 11);
    v0 = srl(s2, 19);
    a0 = s1;
    v0 = v0 & 0x1;
    a1 = 16;
    sw(v0, s1, mpeg::kProgressiveSeq);
    s0 = srl(s2, 20);
    jal(ctx, 0x4FF418u, gen::fn__sceMpegNextBit_004fd658);
    s2 = srl(v0, 8);
    v0 = 72;
    cc = s0 == v0;  // the condition, before the delay slot changes it
    v0 = 88;
    if (!cc) {
        // 0x004ff430
        charge(ctx, 2);
        cc = s0 == v0;  // the condition, before the delay slot changes it
        v0 = 68;
        if (!cc) {
            // 0x004ff438
            charge(ctx, 2);
            a1 = 0x7C0000;
            if (s0 != v0) {
                // 0x004ff440
                charge(ctx, 3);
                a0 = s1;
                a1 = addiu(a1, -10568);
                jal(ctx, 0x4FF444u, gen::fn__sceMpegError_00502668);
            }
        }
    }
    // 0x004ff44c
    charge(ctx, 27);
    lw(a0, s1, mpeg::kWidth);
    t0 = sll(s5, 18);
    lw(v1, s1, mpeg::kHeight);
    t1 = sll(s2, 10);
    lw(a2, s1, mpeg::kBitRate);
    a3 = sll(s3, 12);
    lw(v0, s1, mpeg::kVbvSize);
    a1 = sll(s4, 12);
    a0 = a0 & 0xFFF;
    v1 = v1 & 0xFFF;
    a3 = a3 | a0;
    a1 = a1 | v1;
    a2 = addu(a2, t0);
    v0 = addu(v0, t1);
    sw(v0, s1, mpeg::kVbvSize);
    sw(a3, s1, mpeg::kWidth);
    sw(a1, s1, mpeg::kHeight);
    sw(a2, s1, mpeg::kBitRate);
    ld(ra, sp, 0x60);
    ld(s5, sp, 0x50);
    ld(s4, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x004FF4B8 _quantMatrixExtension -- 232 bytes; frame 0x20: s0 sp+0x0, ra sp+0x10
// MPEG-2 quant_matrix_extension: for each of the intra / non-intra load flags, waits for the IPU, sends SETIQ
// (0x50000000 / 0x58000000) through IPU_CMD and records the command; the chroma matrices are not supported
// (_sceMpegError).
void _quantMatrixExtension(EEContext& ctx) {
    using namespace hg;
    using namespace libs26;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ff4b8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 1;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s0 = a0;
    jal(ctx, 0x4FF4C8u, gen::fn__sceMpegNextBit_004fd658);
    sw(v0, s0, mpeg::kLoadIntraQ);
    if (v0 != 0) {
        // 0x004ff4d8
        charge(ctx, 11);
        a0 = s0;
        jal(ctx, 0x4FF4D8u, gen::fn__waitIpuIdle_0_004ff998);
        v0 = 0x10000000;
        v1 = 0x50000000;
        v0 = v0 | 0x2000;
        a1 = 1;
        sw(v1, v0, 0);  // 0x10002000 IPU_CMD (ipu::kCmd): SETIQ
        a0 = s0;
        sw(v1, s0, mpeg::kIpuWord);
        link(ctx, 0x4FF4FCu);  // $ra first: the delay slot below depends on it
        sw(a1, s0, mpeg::kIpuFlag);
        call(ctx, gen::fn__waitIpuIdle_0_004ff998);
    }
    // 0x004ff504
    charge(ctx, 5);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x4FF508u, gen::fn__sceMpegNextBit_004fd658);
    sw(v0, s0, mpeg::kLoadNonIntraQ);
    if (v0 != 0) {
        // 0x004ff518
        charge(ctx, 12);
        a0 = s0;
        jal(ctx, 0x4FF518u, gen::fn__waitIpuIdle_0_004ff998);
        v0 = 0x10000000;
        v1 = 0x58000000;
        v0 = v0 | 0x2000;
        a0 = 0x50000000;
        sw(v1, v0, 0);  // 0x10002000 IPU_CMD (ipu::kCmd): SETIQ
        a1 = 1;
        sw(a0, s0, mpeg::kIpuWord);
        a0 = s0;
        link(ctx, 0x4FF540u);  // $ra first: the delay slot below depends on it
        sw(a1, s0, mpeg::kIpuFlag);
        call(ctx, gen::fn__waitIpuIdle_0_004ff998);
    }
    // 0x004ff548
    charge(ctx, 5);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x4FF54Cu, gen::fn__sceMpegNextBit_004fd658);
    a1 = 0x7C0000;
    if (v0 != 0) {
        // 0x004ff55c
        charge(ctx, 3);
        a0 = s0;
        a1 = addiu(a1, -10536);
        jal(ctx, 0x4FF560u, gen::fn__sceMpegError_00502668);
    }
    // 0x004ff568
    charge(ctx, 5);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x4FF56Cu, gen::fn__sceMpegNextBit_004fd658);
    ld(ra, sp, 0x10);
    if (v0 == 0) {
        // 0x004ff594
        charge(ctx, 3);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x004ff57c
    charge(ctx, 6);
    a0 = s0;
    a1 = 0x7C0000;
    a1 = addiu(a1, -10496);  // "load_chroma_non_intra_quantizer_matrix == 1"
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
    gen::fn__sceMpegError_00502668(ctx);  // tail call
}

// 0x004FF5A0 _sequenceScalableExtension -- 12 bytes; leaf frame (no stack)
// Reports "_sequenceScalableExtension() is not implemented" (tail call to _sceMpegError).
void _sequenceScalableExtension(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5};
    // 0x004ff5a0
    enter(ctx, 3);  // entry check point + this block's cycles
    a1 = 0x7C0000;
    a1 = addiu(a1, -10448);  // "_sequenceScalableExtension() is not implemented"
    gen::fn__sceMpegError_00502668(ctx);  // tail call
}

// 0x004FF7A8 _pictureSpatialScalableExtension -- 12 bytes; leaf frame (no stack)
// Reports "_pictureSpatialScalableExtension is not supported" (tail call to _sceMpegError).
void _pictureSpatialScalableExtension(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5};
    // 0x004ff7a8
    enter(ctx, 3);  // entry check point + this block's cycles
    a1 = 0x7C0000;
    a1 = addiu(a1, -10376);  // "_pictureSpatialScalableExtension is not supported"
    gen::fn__sceMpegError_00502668(ctx);  // tail call
}

// 0x004FFB88 _sequenceDisplayExtension -- 140 bytes; frame 0x20: s0 sp+0x0, ra sp+0x10
// MPEG-2 sequence_display_extension: video format (3 bits), the optional colour description (3 x 8 bits, the last
// kept at +340), display width (14 bits, +344), a marker bit and display height (14 bits, +348).
void _sequenceDisplayExtension(EEContext& ctx) {
    using namespace hg;
    using namespace libs26;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ffb88
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 3;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s0 = a0;
    jal(ctx, 0x4FFB98u, gen::fn__sceMpegNextBit_004fd658);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x4FFBA4u, gen::fn__sceMpegNextBit_004fd658);
    a0 = s0;
    if (v0 != 0) {
        // 0x004ffbb4
        charge(ctx, 9);
        a1 = 8;
        jal(ctx, 0x4FFBB4u, gen::fn__sceMpegNextBit_004fd658);
        a0 = s0;
        a1 = 8;
        jal(ctx, 0x4FFBC0u, gen::fn__sceMpegNextBit_004fd658);
        a0 = s0;
        a1 = 8;
        jal(ctx, 0x4FFBCCu, gen::fn__sceMpegNextBit_004fd658);
        sw(v0, s0, mpeg::kMatrixCoeffs);
    }
    // 0x004ffbd8
    charge(ctx, 15);
    a0 = s0;
    a1 = 14;
    jal(ctx, 0x4FFBDCu, gen::fn__sceMpegNextBit_004fd658);
    sw(v0, s0, mpeg::kDisplayW);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x4FFBECu, gen::fn__sceMpegNextBit_004fd658);
    a0 = s0;
    a1 = 14;
    jal(ctx, 0x4FFBF8u, gen::fn__sceMpegNextBit_004fd658);
    sw(v0, s0, mpeg::kDisplayH);
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004FFC18 _copyrightExtension -- 148 bytes; frame 0x20: s0 sp+0x0, ra sp+0x10
// MPEG-2 copyright_extension: skips its 1+8+1+7+1+20+1+22+1+22 bits.
void _copyrightExtension(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ffc18
    enter(ctx, 37);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 1;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s0 = a0;
    jal(ctx, 0x4FFC28u, gen::fn__sceMpegNextBit_004fd658);
    a0 = s0;
    a1 = 8;
    jal(ctx, 0x4FFC34u, gen::fn__sceMpegNextBit_004fd658);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x4FFC40u, gen::fn__sceMpegNextBit_004fd658);
    a0 = s0;
    a1 = 7;
    jal(ctx, 0x4FFC4Cu, gen::fn__sceMpegNextBit_004fd658);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x4FFC58u, gen::fn__sceMpegNextBit_004fd658);
    a0 = s0;
    a1 = 20;
    jal(ctx, 0x4FFC64u, gen::fn__sceMpegNextBit_004fd658);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x4FFC70u, gen::fn__sceMpegNextBit_004fd658);
    a0 = s0;
    a1 = 22;
    jal(ctx, 0x4FFC7Cu, gen::fn__sceMpegNextBit_004fd658);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x4FFC88u, gen::fn__sceMpegNextBit_004fd658);
    a0 = s0;
    a1 = 22;
    jal(ctx, 0x4FFC94u, gen::fn__sceMpegNextBit_004fd658);
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004FFCB0 _pictureDisplayExtension -- 244 bytes; frame 0x70: s1 sp+0x10, ra sp+0x60, s5 sp+0x50, s4 sp+0x40, s3 sp+0x30, s2 sp+0x20, s0 sp+0x0
// MPEG-2 picture_display_extension: the number of frame-centre offsets (1, 2 or 3 from the progressive /
// picture-structure / repeat-first-field words), then each horizontal and vertical offset (16 bits + marker) into the
// arrays at +412 and +424.
void _pictureDisplayExtension(EEContext& ctx) {
    using namespace hg;
    using namespace libs26;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ffcb0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(s1, sp, 0x10);
    sd(ra, sp, 0x60);
    s1 = a0;
    sd(s5, sp, 0x50);
    sd(s4, sp, 0x40);
    sd(s3, sp, 0x30);
    sd(s2, sp, 0x20);
    sd(s0, sp, 0x0);
    lw(v0, s1, mpeg::kProgressiveSeq);
    if (v0 == 0) {
        lw(v1, s1, mpeg::kPictStruct);
        // 0x004ffcfc
        charge(ctx, 3);
        v0 = 3;
        if (v1 == v0) {
            lw(v0, s1, mpeg::kRepeatFirst);
            // 0x004ffd10
            charge(ctx, 2);
            s3 = 2;
            if (v0 != 0) s3 = v1;
        } else {
        L_004ffd08:
            charge(ctx, 2);
            s3 = 1;
        }
    } else {
        // 0x004ffce0
        charge(ctx, 3);
        lw(v0, s1, mpeg::kRepeatFirst);
        s3 = 2;
        if (v0 == 0) {
            goto L_004ffd08;
        }
        // 0x004ffcec
        charge(ctx, 4);
        lw(v1, s1, mpeg::kTopFirst);
        v0 = 3;
        if (v1 != 0) s3 = v0;
    }
    // 0x004ffd18
    charge(ctx, 2);
    s2 = 0;
    if (i64(s3) > 0) {
        // 0x004ffd20
        charge(ctx, 4);
        s5 = addiu(s1, 412);
        s4 = addiu(s1, 424);
        a0 = s1;
        for (;;) {
            // 0x004ffd30
            charge(ctx, 20);
            a1 = 16;
            jal(ctx, 0x4FFD30u, gen::fn__sceMpegNextBit_004fd658);
            s0 = sll(s2, 2);
            v1 = addu(s5, s0);
            a0 = s1;
            sw(v0, v1, 0);
            a1 = 1;
            jal(ctx, 0x4FFD48u, gen::fn__sceMpegNextBit_004fd658);
            s2 = addiu(s2, 1);
            a0 = s1;
            a1 = 16;
            jal(ctx, 0x4FFD58u, gen::fn__sceMpegNextBit_004fd658);
            s0 = addu(s4, s0);
            a0 = s1;
            sw(v0, s0, 0);
            a1 = 1;
            jal(ctx, 0x4FFD6Cu, gen::fn__sceMpegNextBit_004fd658);
            v1 = slt(s2, s3);
            a0 = s1;
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004ffd80 (the shared epilogue, written out on this path)
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

// 0x00502D40 RFU000_FullReset -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 0, `syscall`, the kernel's $v0 returned. reserved kernel call 0 (FullReset).
void RFU000_FullReset(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502d40
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 0;
    syscall(ctx, 0x502D44u);
}

// 0x00502D50 ResetEE -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 1, `syscall`, the kernel's $v0 returned. ResetEE(mask): reset the EE units named in the
// mask.
void ResetEE(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502d50
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 1;
    syscall(ctx, 0x502D54u);
}

// 0x00502D70 RFU003 -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 3, `syscall`, the kernel's $v0 returned. reserved kernel call 3.
void RFU003(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502d70
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 3;
    syscall(ctx, 0x502D74u);
}

// 0x00502D90 RFU005 -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 5, `syscall`, the kernel's $v0 returned. reserved kernel call 5.
void RFU005(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502d90
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 5;
    syscall(ctx, 0x502D94u);
}

// 0x00502DC0 RFU008 -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 8, `syscall`, the kernel's $v0 returned. reserved kernel call 8.
void RFU008(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502dc0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 8;
    syscall(ctx, 0x502DC4u);
}

// 0x00502DD0 RFU009 -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 9, `syscall`, the kernel's $v0 returned. reserved kernel call 9.
void RFU009(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502dd0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 9;
    syscall(ctx, 0x502DD4u);
}

// 0x00502DE0 AddSbusIntcHandler -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 10, `syscall`, the kernel's $v0 returned. AddSbusIntcHandler(cause, handler).
void AddSbusIntcHandler(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502de0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 10;
    syscall(ctx, 0x502DE4u);
}

// 0x00502DF0 RemoveSbusIntcHandler -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 11, `syscall`, the kernel's $v0 returned. RemoveSbusIntcHandler(cause).
void RemoveSbusIntcHandler(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502df0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 11;
    syscall(ctx, 0x502DF4u);
}

// 0x00502E00 Interrupt2Iop -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 12, `syscall`, the kernel's $v0 returned. Interrupt2Iop(cause): raise an SBUS interrupt
// on the IOP.
void Interrupt2Iop(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502e00
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 12;
    syscall(ctx, 0x502E04u);
}

// 0x00502E30 SetVInterruptHandler -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 15, `syscall`, the kernel's $v0 returned. SetVInterruptHandler(cause, handler).
void SetVInterruptHandler(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502e30
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 15;
    syscall(ctx, 0x502E34u);
}

// 0x00502EE0 SetAlarm -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 252, `syscall`, the kernel's $v0 returned. SetAlarm(ticks, handler, arg): an alarm id or
// a negative error.
void SetAlarm(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502ee0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 252;
    syscall(ctx, 0x502EE4u);
}

// 0x00502EF0 ReleaseAlarm -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 253, `syscall`, the kernel's $v0 returned. ReleaseAlarm(id).
void ReleaseAlarm(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502ef0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 253;
    syscall(ctx, 0x502EF4u);
}

// 0x00502F40 iSetAlarm -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = -254, `syscall`, the kernel's $v0 returned. iSetAlarm(ticks, handler, arg), interrupt
// context.
void iSetAlarm(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502f40
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = si(-254);
    syscall(ctx, 0x502F44u);
}

// 0x00502F50 iReleaseAlarm -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = -255, `syscall`, the kernel's $v0 returned. iReleaseAlarm(id), interrupt context.
void iReleaseAlarm(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502f50
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = si(-255);
    syscall(ctx, 0x502F54u);
}

// 0x00502F90 ExitThread -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 35, `syscall`, the kernel's $v0 returned. ExitThread(): end the calling thread.
void ExitThread(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502f90
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 35;
    syscall(ctx, 0x502F94u);
}

// 0x00502FC0 iTerminateThread -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = -38, `syscall`, the kernel's $v0 returned. iTerminateThread(id), interrupt context.
void iTerminateThread(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502fc0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = si(-38);
    syscall(ctx, 0x502FC4u);
}

// 0x00502FD0 DisableDispatchThread -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 39, `syscall`, the kernel's $v0 returned. DisableDispatchThread().
void DisableDispatchThread(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502fd0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 39;
    syscall(ctx, 0x502FD4u);
}

// 0x00502FE0 EnableDispatchThread -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 40, `syscall`, the kernel's $v0 returned. EnableDispatchThread().
void EnableDispatchThread(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00502fe0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 40;
    syscall(ctx, 0x502FE4u);
}

// 0x00503020 _iRotateThreadReadyQueue -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = -44, `syscall`, the kernel's $v0 returned. iRotateThreadReadyQueue(prio), interrupt
// context.
void _iRotateThreadReadyQueue(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503020
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = si(-44);
    syscall(ctx, 0x503024u);
}

// 0x00503030 ReleaseWaitThread -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 45, `syscall`, the kernel's $v0 returned. ReleaseWaitThread(id).
void ReleaseWaitThread(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503030
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 45;
    syscall(ctx, 0x503034u);
}

// 0x00503040 iReleaseWaitThread -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = -46, `syscall`, the kernel's $v0 returned. iReleaseWaitThread(id), interrupt context.
void iReleaseWaitThread(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503040
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = si(-46);
    syscall(ctx, 0x503044u);
}

// 0x005030B0 CancelWakeupThread -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 53, `syscall`, the kernel's $v0 returned. CancelWakeupThread(id).
void CancelWakeupThread(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x005030b0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 53;
    syscall(ctx, 0x5030B4u);
}

// 0x005030C0 iCancelWakeupThread -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = -54, `syscall`, the kernel's $v0 returned. iCancelWakeupThread(id), interrupt context.
void iCancelWakeupThread(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x005030c0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = si(-54);
    syscall(ctx, 0x5030C4u);
}

// 0x00503100 iResumeThread -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = -58, `syscall`, the kernel's $v0 returned. iResumeThread(id), interrupt context.
void iResumeThread(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503100
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = si(-58);
    syscall(ctx, 0x503104u);
}

// 0x00503110 JoinThread -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 59, `syscall`, the kernel's $v0 returned. JoinThread (kernel call 59).
void JoinThread(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503110
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 59;
    syscall(ctx, 0x503114u);
}

// 0x00503120 RFU060 -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 60, `syscall`, the kernel's $v0 returned. reserved kernel call 60 (the C runtime's
// InitMainThread slot).
void RFU060(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503120
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 60;
    syscall(ctx, 0x503124u);
}

// 0x00503130 RFU061 -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 61, `syscall`, the kernel's $v0 returned. reserved kernel call 61 (the C runtime's
// InitHeap slot).
void RFU061(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503130
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 61;
    syscall(ctx, 0x503134u);
}

// 0x00503150 RFU063 -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 63, `syscall`, the kernel's $v0 returned. reserved kernel call 63.
void RFU063(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503150
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 63;
    syscall(ctx, 0x503154u);
}

// 0x005031C0 iPollSema -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = -70, `syscall`, the kernel's $v0 returned. iPollSema(id), interrupt context.
void iPollSema(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x005031c0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = si(-70);
    syscall(ctx, 0x5031C4u);
}

// 0x005031D0 ReferSemaStatus -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 71, `syscall`, the kernel's $v0 returned. ReferSemaStatus(id, status).
void ReferSemaStatus(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x005031d0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 71;
    syscall(ctx, 0x5031D4u);
}

// 0x005031E0 iReferSemaStatus -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = -72, `syscall`, the kernel's $v0 returned. iReferSemaStatus(id, status), interrupt
// context.
void iReferSemaStatus(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x005031e0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = si(-72);
    syscall(ctx, 0x5031E4u);
}

// 0x005031F0 RFU073 -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 73, `syscall`, the kernel's $v0 returned. reserved kernel call 73.
void RFU073(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x005031f0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 73;
    syscall(ctx, 0x5031F4u);
}

// 0x00503220 GetGsHParam -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 76, `syscall`, the kernel's $v0 returned. GetGsHParam(...).
void GetGsHParam(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503220
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 76;
    syscall(ctx, 0x503224u);
}

// 0x00503230 GetGsVParam -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 77, `syscall`, the kernel's $v0 returned. GetGsVParam(...).
void GetGsVParam(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503230
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 77;
    syscall(ctx, 0x503234u);
}

// 0x00503240 SetGsHParam -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 78, `syscall`, the kernel's $v0 returned. SetGsHParam(...).
void SetGsHParam(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503240
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 78;
    syscall(ctx, 0x503244u);
}

// 0x00503250 SetGsVParam -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 79, `syscall`, the kernel's $v0 returned. SetGsVParam(...).
void SetGsVParam(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503250
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 79;
    syscall(ctx, 0x503254u);
}

// 0x00503260 RFU080_CreateEventFlag -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 80, `syscall`, the kernel's $v0 returned. CreateEventFlag (reserved kernel call 80).
void RFU080_CreateEventFlag(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503260
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 80;
    syscall(ctx, 0x503264u);
}

// 0x00503270 RFU081_DeleteEventFlag -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 81, `syscall`, the kernel's $v0 returned. DeleteEventFlag (reserved kernel call 81).
void RFU081_DeleteEventFlag(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503270
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 81;
    syscall(ctx, 0x503274u);
}

// 0x00503280 RFU082_SetEventFlag -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 82, `syscall`, the kernel's $v0 returned. SetEventFlag (reserved kernel call 82).
void RFU082_SetEventFlag(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503280
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 82;
    syscall(ctx, 0x503284u);
}

// 0x00503290 RFU083_iSetEventFlag -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = -83, `syscall`, the kernel's $v0 returned. iSetEventFlag (reserved kernel call 83),
// interrupt context.
void RFU083_iSetEventFlag(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503290
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = si(-83);
    syscall(ctx, 0x503294u);
}

// 0x005032A0 RFU084_ClearEventFlag -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 84, `syscall`, the kernel's $v0 returned. ClearEventFlag (reserved kernel call 84).
void RFU084_ClearEventFlag(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x005032a0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 84;
    syscall(ctx, 0x5032A4u);
}

// 0x005032B0 RFU085_iClearEventFlag -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = -85, `syscall`, the kernel's $v0 returned. iClearEventFlag (reserved kernel call 85),
// interrupt context.
void RFU085_iClearEventFlag(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x005032b0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = si(-85);
    syscall(ctx, 0x5032B4u);
}

// 0x005032C0 RFU086_WaitEvnetFlag -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 86, `syscall`, the kernel's $v0 returned. WaitEventFlag (reserved kernel call 86).
void RFU086_WaitEvnetFlag(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x005032c0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 86;
    syscall(ctx, 0x5032C4u);
}

// 0x005032D0 RFU087_PollEvnetFlag -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 87, `syscall`, the kernel's $v0 returned. PollEventFlag (reserved kernel call 87).
void RFU087_PollEvnetFlag(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x005032d0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 87;
    syscall(ctx, 0x5032D4u);
}

// 0x005032E0 RFU088_iPollEvnetFlag -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = -88, `syscall`, the kernel's $v0 returned. iPollEventFlag (reserved kernel call 88),
// interrupt context.
void RFU088_iPollEvnetFlag(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x005032e0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = si(-88);
    syscall(ctx, 0x5032E4u);
}

// 0x005032F0 RFU089_ReferEventFlagStatus -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 89, `syscall`, the kernel's $v0 returned. ReferEventFlagStatus (reserved kernel call
// 89).
void RFU089_ReferEventFlagStatus(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x005032f0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 89;
    syscall(ctx, 0x5032F4u);
}

// 0x00503300 RFU090_iReferEventFlagStatus -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = -90, `syscall`, the kernel's $v0 returned. iReferEventFlagStatus (reserved kernel call
// 90), interrupt context.
void RFU090_iReferEventFlagStatus(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503300
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = si(-90);
    syscall(ctx, 0x503304u);
}

// 0x00503310 RFU091 -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 91, `syscall`, the kernel's $v0 returned. reserved kernel call 91.
void RFU091(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503310
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 91;
    syscall(ctx, 0x503314u);
}

// 0x00503320 EnableIntcHandler -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 92, `syscall`, the kernel's $v0 returned. EnableIntcHandler(cause).
void EnableIntcHandler(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503320
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 92;
    syscall(ctx, 0x503324u);
}

// 0x00503330 iEnableIntcHandler -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = -92, `syscall`, the kernel's $v0 returned. iEnableIntcHandler(cause), interrupt context.
void iEnableIntcHandler(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503330
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = si(-92);
    syscall(ctx, 0x503334u);
}

// 0x00503340 DisableIntcHandler -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 93, `syscall`, the kernel's $v0 returned. DisableIntcHandler(cause).
void DisableIntcHandler(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503340
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 93;
    syscall(ctx, 0x503344u);
}

// 0x00503350 iDisableIntcHandler -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = -93, `syscall`, the kernel's $v0 returned. iDisableIntcHandler(cause), interrupt
// context.
void iDisableIntcHandler(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503350
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = si(-93);
    syscall(ctx, 0x503354u);
}

// 0x00503360 EnableDmacHandler -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 94, `syscall`, the kernel's $v0 returned. EnableDmacHandler(channel).
void EnableDmacHandler(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503360
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 94;
    syscall(ctx, 0x503364u);
}

// 0x00503370 iEnableDmacHandler -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = -94, `syscall`, the kernel's $v0 returned. iEnableDmacHandler(channel), interrupt
// context.
void iEnableDmacHandler(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503370
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = si(-94);
    syscall(ctx, 0x503374u);
}

// 0x00503380 DisableDmacHandler -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 95, `syscall`, the kernel's $v0 returned. DisableDmacHandler(channel).
void DisableDmacHandler(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503380
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 95;
    syscall(ctx, 0x503384u);
}

// 0x00503390 iDisableDmacHandler -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = -95, `syscall`, the kernel's $v0 returned. iDisableDmacHandler(channel), interrupt
// context.
void iDisableDmacHandler(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503390
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = si(-95);
    syscall(ctx, 0x503394u);
}

// 0x005033A0 KSeg0 -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 96, `syscall`, the kernel's $v0 returned. KSeg0(mode): set the KSEG0 cache mode.
void KSeg0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x005033a0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 96;
    syscall(ctx, 0x5033A4u);
}

// 0x005033B0 EnableCache -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 97, `syscall`, the kernel's $v0 returned. EnableCache(which).
void EnableCache(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x005033b0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 97;
    syscall(ctx, 0x5033B4u);
}

// 0x005033C0 DisableCache -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 98, `syscall`, the kernel's $v0 returned. DisableCache(which).
void DisableCache(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x005033c0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 98;
    syscall(ctx, 0x5033C4u);
}

// 0x005033D0 GetCop0 -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 99, `syscall`, the kernel's $v0 returned. GetCop0(reg): a COP0 register through the
// kernel.
void GetCop0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x005033d0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 99;
    syscall(ctx, 0x5033D4u);
}

// 0x005033F0 CpuConfig -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 102, `syscall`, the kernel's $v0 returned. CpuConfig(cfg).
void CpuConfig(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x005033f0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 102;
    syscall(ctx, 0x5033F4u);
}

// 0x00503400 iGetCop0 -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = -103, `syscall`, the kernel's $v0 returned. iGetCop0(reg), interrupt context.
void iGetCop0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503400
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = si(-103);
    syscall(ctx, 0x503404u);
}

// 0x00503410 iFlushCache -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = -104, `syscall`, the kernel's $v0 returned. iFlushCache(which), interrupt context.
void iFlushCache(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503410
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = si(-104);
    syscall(ctx, 0x503414u);
}

// 0x00503420 iCpuConfig -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = -106, `syscall`, the kernel's $v0 returned. iCpuConfig(cfg), interrupt context.
void iCpuConfig(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503420
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = si(-106);
    syscall(ctx, 0x503424u);
}

// 0x00503440 SetCPUTimerHandler -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 108, `syscall`, the kernel's $v0 returned. SetCPUTimerHandler(handler).
void SetCPUTimerHandler(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503440
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 108;
    syscall(ctx, 0x503444u);
}

// 0x00503450 SetCPUTimer -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 109, `syscall`, the kernel's $v0 returned. SetCPUTimer(compare).
void SetCPUTimer(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503450
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 109;
    syscall(ctx, 0x503454u);
}

// 0x00503460 SetOsdConfigParam2 -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 110, `syscall`, the kernel's $v0 returned. SetOsdConfigParam2(buf, size, offset).
void SetOsdConfigParam2(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503460
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 110;
    syscall(ctx, 0x503464u);
}

// 0x00503470 GetOsdConfigParam2 -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 111, `syscall`, the kernel's $v0 returned. GetOsdConfigParam2(buf, size, offset).
void GetOsdConfigParam2(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503470
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 111;
    syscall(ctx, 0x503474u);
}

// 0x00503490 iGsGetIMR -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = -112, `syscall`, the kernel's $v0 returned. iGsGetIMR(): the GS interrupt mask,
// interrupt context.
void iGsGetIMR(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503490
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = si(-112);
    syscall(ctx, 0x503494u);
}

// 0x005034B0 iGsPutIMR -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = -113, `syscall`, the kernel's $v0 returned. iGsPutIMR(mask), interrupt context.
void iGsPutIMR(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x005034b0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = si(-113);
    syscall(ctx, 0x5034B4u);
}

// 0x005034C0 SetPgifHandler -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 114, `syscall`, the kernel's $v0 returned. SetPgifHandler(handler).
void SetPgifHandler(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x005034c0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 114;
    syscall(ctx, 0x5034C4u);
}

// 0x005034E0 RFU116 -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 116, `syscall`, the kernel's $v0 returned. reserved kernel call 116 (the slot
// _sceSetSyscall also uses).
void RFU116(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x005034e0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 116;
    syscall(ctx, 0x5034E4u);
}

// 0x005034F0 _print -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 117, `syscall`, the kernel's $v0 returned. the kernel's debug print (kernel call 117).
void _print(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x005034f0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 117;
    syscall(ctx, 0x5034F4u);
}

// 0x00503510 isceSifDmaStat -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = -118, `syscall`, the kernel's $v0 returned. isceSifDmaStat(id): a SIF DMA transfer's
// state, interrupt context.
void isceSifDmaStat(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x00503510
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = si(-118);
    syscall(ctx, 0x503514u);
}

// 0x005035A0 PSMode -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 125, `syscall`, the kernel's $v0 returned. PSMode() (kernel call 125).
void PSMode(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x005035a0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 125;
    syscall(ctx, 0x5035A4u);
}

// 0x005035B0 MachineType -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 126, `syscall`, the kernel's $v0 returned. MachineType() (kernel call 126).
void MachineType(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x005035b0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 126;
    syscall(ctx, 0x5035B4u);
}

// 0x00504140 iSuspendThread -- 152 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0
// iSuspendThread(id): asks the kernel for the current thread (kernel call -47); if `id` is not the current thread,
// the kernel suspend (_sce_iSuspendThread). Otherwise, with the dispatcher enabled (0x77F498 == 0) and the id below
// 256, it queues a suspend request (type 2, id) in the 512-entry ring at 0x966108 and signals the request semaphore
// 0x966100; returns the id, or -1.
void iSuspendThread(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00504140
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sd(s0, sp, 0x0);
    v1 = si(-47);
    syscall(ctx, 0x504150u);
    s0 = v0;
    v0 = sltiu(s0, 256);
    if (s0 == a0) {
        // 0x00504170
        charge(ctx, 2);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 0x780000;
        if (!cc) {
            // 0x00504178
            charge(ctx, 3);
            lw(v1, v0, -2920);
            cc = v1 != 0;  // the condition, before the delay slot changes it
            v1 = 0x960000;
            if (!cc) {
                goto L_00504184;
            }
            // 0x0050418c
            charge(ctx, 15);
            a1 = 0x960000;
            v1 = addiu(v1, 24840);
            lw(a0, a1, 24832);  // 0x966100
            lw(v0, v1, 4);
            a3 = 2;
            v0 = v0 & 0x1FF;
            a2 = sll(v0, 1);
            v0 = addiu(v0, 1);
            a1 = addu(v1, a2);
            sw(v0, v1, 4);
            sb(a3, a1, 8);
            v1 = a1;
            link(ctx, 0x5041BCu);  // $ra first: the delay slot below depends on it
            sb(s0, v1, 9);
            call(ctx, gen::fn__sceiSignalSema_00503190);
            v0 = s0;
            goto L_005041c8;
        }
    L_00504184:
        charge(ctx, 2);
        v0 = si(-1);
    L_005041c8:
        charge(ctx, 1);
        ld(ra, sp, 0x10);
    } else {
        // 0x00504160
        charge(ctx, 4);
        jal(ctx, 0x504160u, gen::fn__sce_iSuspendThread_005030e0);
        ld(ra, sp, 0x10);
    }
    // 0x005041cc (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00504418 _DelayThreadHandler -- 40 bytes; frame 0x10: ra sp+0x0
// The DelayThread alarm handler: signals the semaphore passed as the alarm argument ($a3), then `sync` + `ei`;
// returns 0.
void _DelayThreadHandler(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00504418
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = a3;
    jal(ctx, 0x504420u, gen::fn__sceiSignalSema_00503190);
    sync(ctx, 0);
    ei(ctx);
    ld(ra, sp, 0x0);
    v0 = 0;
    sp = addiu(sp, 0x10);
}

// 0x00506110 isceSifSetDma -- 56 bytes; frame 0x10: ra sp+0x0
// isceSifSetDma(desc, n): the SIF DMA in interrupt context: through sceSifSetDmaInternal (with $a2 = 1) when the
// internal path is armed (0x77F4A8 != 0), else the kernel call _isceSifSetDma.
void isceSifSetDma(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00506110
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x780000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, -2904);  // 0x77F4A8
    sd(ra, sp, 0x0);
    if (v1 == 0) {
        // 0x00506134
        charge(ctx, 3);
        jal(ctx, 0x506134u, gen::fn__isceSifSetDma_00503530);
        ld(ra, sp, 0x0);
    } else {
        // 0x00506124
        charge(ctx, 4);
        a2 = 1;
        jal(ctx, 0x506124u, gen::fn_sceSifSetDmaInternal_00505fc0);
        ld(ra, sp, 0x0);
    }
    // 0x00506140 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x00506C78 _alarm_rdata -- 64 bytes; frame 0x10: ra sp+0x0
// The retry alarm of _request_rdata: resends the 64-byte packet ($a3) as SIF command 0x80000008 with its three words
// +36 / +40 / +44; returns 2048 (re-arm) when the send failed, else 0.
void _alarm_rdata(EEContext& ctx) {
    using namespace hg;
    using namespace libs26;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00506c78
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = a3;
    sd(ra, sp, 0x0);
    a0 = lui(0x8000);
    a0 = a0 | 0x8;
    a2 = 64;
    lw(a3, a1, sifpkt::kArg0);
    lw(t0, a1, sifpkt::kArg1);
    link(ctx, 0x506C98u);  // $ra first: the delay slot below depends on it
    lw(t1, a1, sifpkt::kArg2);
    call(ctx, gen::fn_sceSifWriteBackDCache_00506670);
    v1 = 2048;
    ld(ra, sp, 0x0);
    if (v0 != 0) v1 = 0;
    v0 = v1;
    sp = addiu(sp, 0x10);
}

// 0x00506CB8 _request_rdata -- 208 bytes; frame 0x30: s1 sp+0x10, ra sp+0x20, s0 sp+0x0
// SIF command handler 0x8000000C (the IOP asks the EE to send it data): takes a free packet (the rpc data's second
// free list when bit 2 of +16 is set), copies the request's ids and source / destination / size into it and answers
// with SIF command 0x80000008; on a failed send it re-arms through iSetTimerAlarm(2048, _alarm_rdata).
void _request_rdata(EEContext& ctx) {
    using namespace hg;
    using namespace libs26;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00506cb8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x10);
    s1 = a0;
    sd(ra, sp, 0x20);
    sd(s0, sp, 0x0);
    a0 = a1;
    lw(a1, s1, 16);
    v0 = a1 & 0x4;
    if (v0 == 0) {
        // 0x00506cf0
        charge(ctx, 3);
        jal(ctx, 0x506CF0u, gen::fn__sceRpcGetFPacket_00506b38);
        s0 = v0;
    } else {
        // 0x00506ce0
        charge(ctx, 4);
        a1 = srl(a1, 16);
        jal(ctx, 0x506CE0u, gen::fn__sceRpcGetFPacket2_00506b68);
        s0 = v0;
    }
    // 0x00506cfc
    charge(ctx, 23);
    lw(v1, s1, 20);
    v0 = lui(0x8000);
    lw(a1, s1, 28);
    v0 = v0 | 0xC;
    sw(v1, s0, sifpkt::kReqPkt);
    a0 = lui(0x8000);
    sw(a1, s0, sifpkt::kReqAddr);
    a0 = a0 | 0x8;
    sw(v0, s0, sifpkt::kAnswerCmd);
    a1 = s0;
    a2 = 64;
    lw(v0, s1, 32);
    sw(v0, s0, sifpkt::kArg0);
    lw(v1, s1, 36);
    sw(v1, s0, sifpkt::kArg1);
    lw(v0, s1, 40);
    sw(v0, s0, sifpkt::kArg2);
    lw(t1, s1, 40);
    lw(a3, s1, 32);
    link(ctx, 0x506D48u);  // $ra first: the delay slot below depends on it
    lw(t0, s1, 36);
    call(ctx, gen::fn_sceSifWriteBackDCache_00506670);
    ld(ra, sp, 0x20);
    if (v0 != 0) {
        // 0x00506d78
        charge(ctx, 4);
        ld(s1, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
    // 0x00506d58
    charge(ctx, 8);
    a2 = s0;
    a1 = 0x500000;
    a1 = addiu(a1, 27768);  // &_alarm_rdata
    ld(s1, sp, 0x10);
    a0 = 2048;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
    gen::fn_iSetTimerAlarm_0050f1c0(ctx);  // tail call
}

// 0x00506D88 sceSifGetOtherData -- 356 bytes; frame 0x90: s1 sp+0x30, s5 sp+0x70, s4 sp+0x60, s3 sp+0x50, s2 sp+0x40, s0 sp+0x20, ra sp+0x80
// sceSifGetOtherData(rd, src, dst, size, mode): a packet from the RPC pool, filled with (src, dst, size) and sent as
// SIF command 0x8000000C; without mode bit 0 it blocks on a fresh semaphore until the IOP answers. 0 on success, -1
// no packet, -2 send failed, -3 no semaphore.
void sceSifGetOtherData(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00506d88
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(s1, sp, 0x30);
    s1 = a0;
    sd(s5, sp, 0x70);
    sd(s4, sp, 0x60);
    a0 = 0x970000;
    sd(s3, sp, 0x50);
    s4 = a2;
    sd(s2, sp, 0x40);
    s3 = a1;
    sd(s0, sp, 0x20);
    s5 = a3;
    sd(ra, sp, 0x80);
    s2 = t0;
    a0 = addiu(a0, -31616);  // &0x968480
    jal(ctx, 0x506DC0u, gen::fn__sceRpcGetPacket_00506a70);
    s0 = v0;
    v0 = si(-1);
    if (s0 != 0) {
        // 0x00506dd4
        charge(ctx, 10);
        lw(v0, s0, 24);
        v1 = s2 & 0x1;
        sw(s0, s1, 0);
        sw(v0, s1, 4);
        sw(s3, s0, 32);
        sw(s4, s0, 36);
        sw(s5, s0, 40);
        sw(s0, s0, 20);
        sw(s1, s0, 28);
        if (v1 != 0) {
            // 0x00506e8c
            charge(ctx, 12);
            v0 = si(-1);
            a0 = lui(0x8000);
            sw(v0, s1, 8);
            a0 = a0 | 0xC;
            a1 = s0;
            a2 = 64;
            a3 = 0;
            t0 = 0;
            t1 = 0;
            jal(ctx, 0x506EACu, gen::fn_sub_506630_00506630);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = 0;
            if (!cc) {
                // 0x00506ebc
                charge(ctx, 3);
                a0 = s0;
                jal(ctx, 0x506EBCu, gen::fn__sceRpcFreePacket_00506b18);
                v0 = si(-2);
            }
        } else {
            // 0x00506dfc
            charge(ctx, 10);
            v0 = 0x7C0000;
            v1 = 1;
            v0 = addiu(v0, -8944);  // "SceSifrpcGod"
            sw(v1, sp, 0x4);
            sw(v0, sp, 0x14);
            a0 = sp;
            link(ctx, 0x506E14u);  // $ra first: the delay slot below depends on it
            sw(zero, sp, 0x8);
            call(ctx, gen::fn__sceCreateSema_00503160);
            sw(v0, s1, 8);
            if (i64(v0) >= 0) {
                // 0x00506e34
                charge(ctx, 10);
                a0 = lui(0x8000);
                a1 = s0;
                a0 = a0 | 0xC;
                a2 = 64;
                a3 = 0;
                t0 = 0;
                t1 = 0;
                jal(ctx, 0x506E4Cu, gen::fn_sub_506630_00506630);
                if (v0 != 0) {
                    // 0x00506e74
                    charge(ctx, 6);
                    link(ctx, 0x506E74u);  // $ra first: the delay slot below depends on it
                    lw(a0, s1, 8);
                    call(ctx, gen::fn__sceWaitSema_005031a0);
                    link(ctx, 0x506E7Cu);  // $ra first: the delay slot below depends on it
                    lw(a0, s1, 8);
                    call(ctx, gen::fn__sceDeleteSema_00503170);
                    v0 = 0;
                } else {
                    // 0x00506e5c
                    charge(ctx, 6);
                    a0 = s0;
                    jal(ctx, 0x506E5Cu, gen::fn__sceRpcFreePacket_00506b18);
                    link(ctx, 0x506E64u);  // $ra first: the delay slot below depends on it
                    lw(a0, s1, 8);
                    call(ctx, gen::fn__sceDeleteSema_00503170);
                    v0 = si(-2);
                }
            } else {
                // 0x00506e24
                charge(ctx, 4);
                a0 = s0;
                jal(ctx, 0x506E24u, gen::fn__sceRpcFreePacket_00506b18);
                v0 = si(-3);
            }
        }
    }
    // 0x00506ec8 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x80);
    ld(s5, sp, 0x70);
    ld(s4, sp, 0x60);
    ld(s3, sp, 0x50);
    ld(s2, sp, 0x40);
    ld(s1, sp, 0x30);
    ld(s0, sp, 0x20);
    sp = addiu(sp, 0x90);
}

// 0x00506F40 _alarm_bind -- 64 bytes; frame 0x10: ra sp+0x0
// The retry alarm of _request_bind: resends the 64-byte packet ($a3) as SIF command 0x80000008; returns 2048 (re-arm)
// when the send failed, else 0.
void _alarm_bind(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00506f40
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = a3;
    a0 = lui(0x8000);
    sd(ra, sp, 0x0);
    a0 = a0 | 0x8;
    a2 = 64;
    a3 = 0;
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x506F60u, gen::fn_sceSifWriteBackDCache_00506670);
    v1 = 2048;
    ld(ra, sp, 0x0);
    if (v0 != 0) v1 = 0;
    v0 = v1;
    sp = addiu(sp, 0x10);
}

// 0x00506F80 _request_bind -- 204 bytes; frame 0x40: s1 sp+0x10, s0 sp+0x0, s2 sp+0x20, ra sp+0x30
// SIF command handler 0x80000009 (bind): a free packet with the request's ids, the server found by _search_svdata
// (its pointer and its word +8, or zeros) and command 0x80000008 back to the IOP; on a failed send it re-arms through
// iSetTimerAlarm(2048, _alarm_bind).
void _request_bind(EEContext& ctx) {
    using namespace hg;
    using namespace libs26;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00506f80
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    s1 = a1;
    s0 = a0;
    sd(s2, sp, 0x20);
    sd(ra, sp, 0x30);
    a0 = s1;
    jal(ctx, 0x506F9Cu, gen::fn__sceRpcGetFPacket_00506b38);
    s2 = v0;
    lw(a0, s0, 28);
    lw(v1, s0, 20);
    v0 = lui(0x8000);
    v0 = v0 | 0x9;
    sw(a0, s2, sifpkt::kReqAddr);
    sw(v1, s2, sifpkt::kReqPkt);
    a1 = s1;
    sw(v0, s2, sifpkt::kAnswerCmd);
    link(ctx, 0x506FC8u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 32);
    call(ctx, gen::fn__search_svdata_00506ef0);
    if (v0 != 0) {
        sw(v0, s2, sifpkt::kArg0);
        // 0x00506fe4
        charge(ctx, 2);
        lw(v0, v0, 8);
        sw(v0, s2, sifpkt::kArg1);
    } else {
        // 0x00506fd8
        charge(ctx, 3);
        sw(zero, s2, sifpkt::kArg0);
        sw(zero, s2, sifpkt::kArg1);
    }
    // 0x00506fec
    charge(ctx, 10);
    a0 = lui(0x8000);
    a1 = s2;
    a0 = a0 | 0x8;
    a2 = 64;
    a3 = 0;
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x507004u, gen::fn_sceSifWriteBackDCache_00506670);
    ld(ra, sp, 0x30);
    if (v0 != 0) {
        // 0x00507038
        charge(ctx, 5);
        ld(s2, sp, 0x20);
        ld(s1, sp, 0x10);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
    // 0x00507014
    charge(ctx, 9);
    a2 = s2;
    a1 = 0x500000;
    a1 = addiu(a1, 28480);  // &_alarm_bind
    ld(s2, sp, 0x20);
    a0 = 2048;
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    gen::fn_iSetTimerAlarm_0050f1c0(ctx);  // tail call
}

// 0x00507758 sceSifExecRequest -- 452 bytes; frame 0x80: s4 sp+0x60, s2 sp+0x40, s1 sp+0x30, ra sp+0x70, s3 sp+0x50, s0 sp+0x20
// Runs one queued RPC request on the EE server: calls the server function (+4) with (fno +36, buffer +8, size +12),
// writes the buffer and the result back from the data cache, then answers the IOP: SIF command 0x8000000A by DMA with
// the result copied to the receive address (retrying with a 0x100000 spin) when +48 is 0, else through the command
// path until it is sent.
void sceSifExecRequest(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00507758
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(s4, sp, 0x60);
    sd(s2, sp, 0x40);
    s4 = 0;
    sd(s1, sp, 0x30);
    sd(ra, sp, 0x70);
    s1 = a0;
    sd(s3, sp, 0x50);
    sd(s0, sp, 0x20);
    lw(v0, s1, 4);
    lw(a0, s1, 36);
    lw(a1, s1, 8);
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x507788u);  // $ra = the return address
    lw(a2, s1, 12);
    call_ptr(ctx, jt);
    s2 = v0;
    if (s2 != 0) {
        lw(s4, s1, 44);
    }
    // 0x0050779c
    charge(ctx, 3);
    lw(a1, s1, 12);
    if (i64(a1) > 0) {
        // 0x005077a8
        charge(ctx, 2);
        link(ctx, 0x5077A8u);  // $ra first: the delay slot below depends on it
        lw(a0, s1, 8);
        call(ctx, gen::fn_sub_5067F8_005067f8);
    }
    // 0x005077b0
    charge(ctx, 2);
    a0 = s2;
    if (i64(s4) > 0) {
        // 0x005077b8
        charge(ctx, 2);
        a1 = s4;
        jal(ctx, 0x5077B8u, gen::fn_sub_5067F8_005067f8);
    }
    // 0x005077c0
    charge(ctx, 6);
    jal(ctx, 0x5077C0u, gen::fn_DIntr_0050d3a0);
    lw(a1, s1, 52);
    v0 = a1 & 0x4;
    a1 = srl(a1, 16);
    if (v0 == 0) {
        // 0x005077ec
        charge(ctx, 4);
        a0 = 0x970000;
        a0 = addiu(a0, -31616);  // &0x968480
        jal(ctx, 0x5077F0u, gen::fn__sceRpcGetFPacket_00506b38);
        s0 = v0;
    } else {
        // 0x005077d8
        charge(ctx, 5);
        a0 = 0x970000;
        a0 = addiu(a0, -31616);  // &0x968480
        jal(ctx, 0x5077DCu, gen::fn__sceRpcGetFPacket2_00506b68);
        s0 = v0;
    }
    // 0x005077fc
    charge(ctx, 10);
    jal(ctx, 0x5077FCu, gen::fn_EIntr_0050d3f0);
    v1 = lui(0x8000);
    lw(a0, s1, 28);
    v1 = v1 | 0xA;
    sw(v1, s0, 32);
    sw(a0, s0, 28);
    lw(v0, s1, 48);
    if (v0 == 0) {
        sw(zero, s0, 24);
        // 0x00507858
        charge(ctx, 3);
        s3 = 0;
        sw(zero, s0, 16);
        if (i64(s4) > 0) {
            // 0x00507864
            charge(ctx, 6);
            lw(v0, s1, 40);
            s3 = 1;
            sw(s2, sp, 0x0);
            sw(v0, sp, 0x4);
            sw(s4, sp, 0x8);
            sw(zero, sp, 0xC);
        }
        // 0x0050787c
        charge(ctx, 17);
        a1 = sll(s3, 4);
        lw(a0, s1, 32);
        v1 = addu(sp, a1);
        v0 = addiu(sp, 0x4);
        sw(s0, v1, 0);
        v0 = addu(v0, a1);
        sw(a0, v0, 0);
        v1 = addiu(sp, 0x8);
        v1 = addu(v1, a1);
        a0 = 64;
        v0 = addiu(sp, 0xC);
        sw(a0, v1, 0);
        v0 = addu(v0, a1);
        s3 = addiu(s3, 1);
        sw(zero, v0, 0);
        a0 = sp;
        for (;;) {
            // 0x005078c0
            charge(ctx, 4);
            a1 = s3;
            jal(ctx, 0x5078C0u, gen::fn_sceSifSetDma_00506088);
            ld(ra, sp, 0x70);
            if (v0 != 0) {
                break;
            }
            // 0x005078d0
            charge(ctx, 2);
            v1 = 0x100000;
            a0 = si(-1);
            for (;;) {
                // 0x005078d8
                charge(ctx, 7);
                v1 = addiu(v1, -1);
                if (v1 == a0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x005078f4
            charge(ctx, 2);
            if (v0 != 0) {
                goto L_005078fc_19;
            }
            a0 = sp;
            backedge(ctx);
        }
    L_00507900:
        charge(ctx, 1);
        ld(s4, sp, 0x60);
    } else {
        // 0x00507824
        charge(ctx, 1);
        for (;;) {
            // 0x00507828
            charge(ctx, 10);
            a0 = lui(0x8000);
            lw(t0, s1, 40);
            a0 = a0 | 0x8;
            a1 = s0;
            a2 = 64;
            a3 = s2;
            t1 = s4;
            jal(ctx, 0x507840u, gen::fn_sub_506630_00506630);
            ld(ra, sp, 0x70);
            if (v0 != 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00507850
        charge(ctx, 2);
        ld(s4, sp, 0x60);
    }
    // 0x00507904 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s3, sp, 0x50);
    ld(s2, sp, 0x40);
    ld(s1, sp, 0x30);
    ld(s0, sp, 0x20);
    sp = addiu(sp, 0x80);
    return;
L_005078fc_19:
    charge(ctx, 1);
    ld(ra, sp, 0x70);
    goto L_00507900;
}

// 0x00508128 _sceFs_Poff_Intr -- 68 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0
// The file-I/O power-off interrupt handler: calls the registered callback (*$a1) with its argument (+4) under the
// file-I/O library's $gp (0x969CC0), then `sync` + `ei`.
void _sceFs_Poff_Intr(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00508128
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    lw(v1, a1, 0);
    sd(ra, sp, 0x10);
    sd(s0, sp, 0x0);
    if (v1 != 0) {
        // 0x0050813c
        charge(ctx, 6);
        v0 = 0x970000;
        s0 = gp;
        lw(gp, v0, -25408);  // 0x969CC0
        jt = v1.u();  // the target, read before the delay slot
        link(ctx, 0x508148u);  // $ra = the return address
        lw(a0, a1, 4);
        call_ptr(ctx, jt);
        gp = s0;
    }
    // 0x00508154 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    sync(ctx, 0);
    ei(ctx);
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00508440 sceFsSetIopBuf -- 320 bytes; frame 0x50: s0 sp+0x10, s1 sp+0x20, ra sp+0x40, s2 sp+0x30
// sceFsSetIopBuf(size, count) (file-I/O RPC 254): checks the size (16 KiB aligned, at most 1 MiB) and count (1..32)
// with no file open; returns the IOP's answer, -16 (files open), -22 (bad argument), -11 (RPC failed) or 0xFFFEFFFC
// (old IOP module).
void sceFsSetIopBuf(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00508440
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s0, sp, 0x10);
    sd(s1, sp, 0x20);
    s0 = a0;
    sd(ra, sp, 0x40);
    s1 = a1;
    sd(s2, sp, 0x30);
    a0 = 254;
    jal(ctx, 0x50845Cu, gen::fn__sceFsWaitS_00508048);
    v1 = 0x780000;
    lw(v0, v1, -2756);  // 0x77F53C
    if (v0 == 0) {
        // 0x00508474
        charge(ctx, 2);
        jal(ctx, 0x508474u, gen::fn_sceFsInit_00508170);
    }
    // 0x0050847c
    charge(ctx, 4);
    jal(ctx, 0x50847Cu, gen::fn__fs_version_00508378);
    if (v0 == 0) {
        // 0x005084a0
        charge(ctx, 4);
        jal(ctx, 0x5084A0u, gen::fn_use_iob_cnt_005079d0);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = s0 & 0x3FFF;
        if (cc) {
            // 0x005084c0
            charge(ctx, 2);
            if (v0 == 0) {
                // 0x005084c8
                charge(ctx, 2);
                v0 = 0xF0000;
                if (s0 == 0) {
                    goto L_005084f0;
                }
                // 0x005084d0
                charge(ctx, 4);
                v0 = v0 | 0xFFFF;
                v0 = sltu(v0, s0);
                if (v0 != 0) {
                    goto L_005084f0;
                }
                // 0x005084e0
                charge(ctx, 2);
                v0 = sltiu(s1, 33);
                if (s1 == 0) {
                    goto L_005084f0;
                }
                // 0x005084e8
                charge(ctx, 2);
                v1 = 0x970000;
                if (v0 == 0) {
                    goto L_005084f0;
                }
                // 0x00508500
                charge(ctx, 18);
                v0 = 0x970000;
                a3 = addiu(v1, -31488);
                sw(s0, v1, -31488);
                sw(s1, a3, 4);
                s2 = addiu(v0, -28352);  // &0x969140
                a0 = 0x970000;
                sw(zero, sp, 0x0);
                a0 = addiu(a0, -25600);  // &0x969C00
                sw(zero, sp, 0x8);
                a1 = 254;
                a2 = 0;
                t0 = 8;
                t1 = s2;
                t2 = 4;
                t3 = 0;
                jal(ctx, 0x508538u, gen::fn_sceFsSifCallRpc_00507ad8);
                cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
                v0 = 0x20000000;
                if (cc) {
                    // 0x00508558
                    charge(ctx, 4);
                    v0 = s2 | v0;
                    link(ctx, 0x50855Cu);  // $ra first: the delay slot below depends on it
                    lw(s0, v0, 0);
                    call(ctx, gen::fn__sceFsSigSema_00508078);
                    v0 = s0;
                } else {
                    // 0x00508548
                    charge(ctx, 4);
                    jal(ctx, 0x508548u, gen::fn__sceFsSigSema_00508078);
                    v0 = si(-11);
                }
                // 0x00508568 (the shared epilogue, written out on this path)
                charge(ctx, 6);
                ld(ra, sp, 0x40);
                ld(s2, sp, 0x30);
                ld(s1, sp, 0x20);
                ld(s0, sp, 0x10);
                sp = addiu(sp, 0x50);
                return;
            }
        L_005084f0:
            charge(ctx, 4);
            jal(ctx, 0x5084F0u, gen::fn__sceFsSigSema_00508078);
            v0 = si(-22);
        } else {
            // 0x005084b0
            charge(ctx, 4);
            jal(ctx, 0x5084B0u, gen::fn__sceFsSigSema_00508078);
            v0 = si(-16);
        }
    } else {
        // 0x0050848c
        charge(ctx, 5);
        jal(ctx, 0x50848Cu, gen::fn__sceFsSigSema_00508078);
        v0 = lui(0xFFFE);
        v0 = v0 | 0xFFFC;
    }
    // 0x00508568 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x40);
    ld(s2, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x50);
}

// 0x00508580 sceFsSetIopPrio -- 240 bytes; frame 0x40: s0 sp+0x10, ra sp+0x30, s1 sp+0x20
// sceFsSetIopPrio(prio) (file-I/O RPC 253): the IOP file server's thread priority; the same checks and errors as
// sceFsSetIopBuf.
void sceFsSetIopPrio(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00508580
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(ra, sp, 0x30);
    sd(s1, sp, 0x20);
    a0 = 253;
    jal(ctx, 0x508594u, gen::fn__sceFsWaitS_00508048);
    v1 = 0x780000;
    lw(v0, v1, -2756);  // 0x77F53C
    if (v0 == 0) {
        // 0x005085ac
        charge(ctx, 2);
        jal(ctx, 0x5085ACu, gen::fn_sceFsInit_00508170);
    }
    // 0x005085b4
    charge(ctx, 4);
    jal(ctx, 0x5085B4u, gen::fn__fs_version_00508378);
    if (v0 == 0) {
        // 0x005085d8
        charge(ctx, 4);
        jal(ctx, 0x5085D8u, gen::fn_use_iob_cnt_005079d0);
        a3 = 0x970000;
        if (v0 == 0) {
            // 0x005085f8
            charge(ctx, 17);
            v0 = 0x970000;
            s1 = addiu(v0, -28352);  // &0x969140
            a0 = 0x970000;
            sw(s0, a3, -31488);
            a0 = addiu(a0, -25600);  // &0x969C00
            a3 = addiu(a3, -31488);
            sw(zero, sp, 0x0);
            sw(zero, sp, 0x8);
            a1 = 253;
            a2 = 0;
            t0 = 8;
            t1 = s1;
            t2 = 4;
            t3 = 0;
            jal(ctx, 0x50862Cu, gen::fn_sceFsSifCallRpc_00507ad8);
            cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
            v0 = 0x20000000;
            if (cc) {
                // 0x0050864c
                charge(ctx, 4);
                v0 = s1 | v0;
                link(ctx, 0x508650u);  // $ra first: the delay slot below depends on it
                lw(s0, v0, 0);
                call(ctx, gen::fn__sceFsSigSema_00508078);
                v0 = s0;
            } else {
                // 0x0050863c
                charge(ctx, 4);
                jal(ctx, 0x50863Cu, gen::fn__sceFsSigSema_00508078);
                v0 = si(-11);
            }
        } else {
            // 0x005085e8
            charge(ctx, 4);
            jal(ctx, 0x5085E8u, gen::fn__sceFsSigSema_00508078);
            v0 = si(-16);
        }
    } else {
        // 0x005085c4
        charge(ctx, 5);
        jal(ctx, 0x5085C4u, gen::fn__sceFsSigSema_00508078);
        v0 = lui(0xFFFE);
        v0 = v0 | 0xFFFC;
    }
    // 0x0050865c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x40);
}

// 0x00509570 sceIoctl2 -- 488 bytes; frame 0xD0: s7 sp+0xB0, s5 sp+0x90, s4 sp+0x80, s3 sp+0x70, s0 sp+0x40, s6 sp+0xA0, s2 sp+0x60, s1 sp+0x50, ra sp+0xC0
// sceIoctl2(fd, cmd, arg, arglen, buf, buflen) (file-I/O RPC 26): the request block filled and sent with a fresh
// semaphore, then waited for; the answer, -22 / -9 for refused arguments, -11 when the RPC fails or is refused.
void sceIoctl2(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00509570
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(s7, sp, 0xB0);
    sd(s5, sp, 0x90);
    s7 = t0;
    sd(s4, sp, 0x80);
    s5 = a1;
    sd(s3, sp, 0x70);
    s4 = t1;
    sd(s0, sp, 0x40);
    s3 = a3;
    sd(s6, sp, 0xA0);
    s0 = a2;
    sd(s2, sp, 0x60);
    s6 = 0x970000;
    sd(s1, sp, 0x50);
    sd(ra, sp, 0xC0);
    s1 = addiu(s6, -31488);  // &0x968500
    jal(ctx, 0x5095B0u, gen::fn_get_iob_00507bc8);
    s2 = v0;
    a0 = 26;
    jal(ctx, 0x5095BCu, gen::fn__sceFsWaitS_00508048);
    v0 = 0x780000;
    lw(v1, v0, -2756);  // 0x77F53C
    if (v1 == 0) {
        // 0x005095d4
        charge(ctx, 2);
        jal(ctx, 0x5095D4u, gen::fn_sceFsInit_00508170);
    }
    // 0x005095dc
    charge(ctx, 2);
    if (s2 != 0) {
        // 0x005095e4
        charge(ctx, 3);
        lw(v0, s2, 4);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = sltiu(s3, 1025);
        if (!cc) {
            goto L_005095f0;
        }
        // 0x00509600
        charge(ctx, 2);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = sltiu(s4, 1025);
        if (!cc) {
            // 0x00509608
            charge(ctx, 2);
            if (v0 == 0) {
                goto L_00509610;
            }
            // 0x00509620
            charge(ctx, 2);
            a1 = s0;
            if (s0 != 0) {
                // 0x00509630
                charge(ctx, 3);
                a0 = addiu(s1, 20);
                a2 = s3;
                jal(ctx, 0x509634u, gen::fn_memcpy_00521250);
            } else {
                // 0x00509628
                charge(ctx, 2);
                sw(zero, s1, 1052);
            }
            // 0x0050963c
            charge(ctx, 40);
            lw(v1, s2, 0);
            v0 = 0x7C0000;
            sw(s5, s1, 16);
            v0 = addiu(v0, -8592);  // "SceStdioIoctl2Sema"
            sw(v1, s1, 12);
            a1 = 1;
            sw(s3, s1, 1052);
            a0 = addiu(sp, 0x10);
            sw(a1, sp, 0x14);
            s0 = addiu(s6, -31488);
            sw(v0, sp, 0x24);
            link(ctx, 0x509668u);  // $ra first: the delay slot below depends on it
            sw(zero, sp, 0x18);
            call(ctx, gen::fn__sceCreateSema_00503160);
            s2 = v0;
            v1 = 4;
            v0 = addiu(sp, 0x30);
            sw(s4, s1, 1048);
            sw(v0, s1, 4);
            a0 = s0;
            sw(v1, s1, 8);
            a1 = 1056;
            sw(s7, s1, 1044);
            link(ctx, 0x509694u);  // $ra first: the delay slot below depends on it
            sw(s2, s1, 0);
            call(ctx, gen::fn_sub_5067F8_005067f8);
            v0 = 0x970000;
            a0 = 0x970000;
            s1 = addiu(v0, -28352);  // &0x969140
            a0 = addiu(a0, -25600);  // &0x969C00
            a3 = s0;
            sw(zero, sp, 0x0);
            sw(zero, sp, 0x8);
            a1 = 26;
            a2 = 0;
            t0 = 1056;
            t1 = s1;
            t2 = 4;
            t3 = 0;
            jal(ctx, 0x5096CCu, gen::fn_sceFsSifCallRpc_00507ad8);
            cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
            v0 = 0x20000000;
            if (cc) {
                // 0x005096f4
                charge(ctx, 5);
                v0 = s1 | v0;
                link(ctx, 0x5096F8u);  // $ra first: the delay slot below depends on it
                lw(s0, v0, 0);
                call(ctx, gen::fn__sceFsSigSema_00508078);
                if (s0 != 0) {
                    // 0x00509718
                    charge(ctx, 5);
                    a0 = s2;
                    jal(ctx, 0x509718u, gen::fn__sceWaitSema_005031a0);
                    a0 = s2;
                    jal(ctx, 0x509720u, gen::fn__sceDeleteSema_00503170);
                    lw(v0, sp, 0x30);
                } else {
                    // 0x00509708
                    charge(ctx, 4);
                    a0 = s2;
                    jal(ctx, 0x509708u, gen::fn__sceDeleteSema_00503170);
                    v0 = si(-11);
                }
            } else {
                // 0x005096dc
                charge(ctx, 6);
                a0 = s2;
                jal(ctx, 0x5096DCu, gen::fn__sceDeleteSema_00503170);
                jal(ctx, 0x5096E4u, gen::fn__sceFsSigSema_00508078);
                v0 = si(-11);
            }
            // 0x0050972c (the shared epilogue, written out on this path)
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
            return;
        }
    L_00509610:
        charge(ctx, 4);
        jal(ctx, 0x509610u, gen::fn__sceFsSigSema_00508078);
        v0 = si(-22);
        // 0x0050972c (the shared epilogue, written out on this path)
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
        return;
    }
L_005095f0:
    charge(ctx, 4);
    jal(ctx, 0x5095F0u, gen::fn__sceFsSigSema_00508078);
    v0 = si(-9);
    // 0x0050972c (the shared epilogue, written out on this path)
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

// 0x00509928 sceMkdir -- 440 bytes; frame 0xD0: s1 sp+0x50, s6 sp+0xA0, s7 sp+0xB0, s2 sp+0x60, ra sp+0xC0, s5 sp+0x90, s4 sp+0x80, s3 sp+0x70, s0 sp+0x40
// sceMkdir(path, mode) (file-I/O RPC 7): copies at most 1023 characters of the path into the request block 0x968500,
// sends it with a fresh semaphore and waits; the IOP's answer, or -11 (RPC failed or refused).
void sceMkdir(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00509928
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(s1, sp, 0x50);
    sd(s6, sp, 0xA0);
    s1 = a0;
    sd(s7, sp, 0xB0);
    s6 = a1;
    sd(s2, sp, 0x60);
    a0 = 7;
    sd(ra, sp, 0xC0);
    s7 = 0x970000;
    sd(s5, sp, 0x90);
    s2 = addiu(s7, -31488);  // &0x968500
    sd(s4, sp, 0x80);
    sd(s3, sp, 0x70);
    link(ctx, 0x509960u);  // $ra first: the delay slot below depends on it
    sd(s0, sp, 0x40);
    call(ctx, gen::fn__sceFsWaitS_00508048);
    v0 = 0x780000;
    lw(v1, v0, -2756);  // 0x77F53C
    if (v1 != 0) {
        lbu(v0, s1, 0);
    } else {
        // 0x00509978
        charge(ctx, 3);
        jal(ctx, 0x509978u, gen::fn_sceFsInit_00508170);
        lbu(v0, s1, 0);
    }
    // 0x00509984
    charge(ctx, 4);
    s0 = 0;
    v1 = sll(v0, 24);
    sb(v0, s2, 16);
    if (v1 == 0) {
        // 0x005099d4
        charge(ctx, 4);
        a1 = 0x7C0000;
        s3 = addiu(sp, 0x30);
        s5 = 0x970000;
        s4 = 0x970000;
    L_005099e4:
        charge(ctx, 1);
        v0 = 1024;
    } else {
        // 0x00509994
        charge(ctx, 5);
        a1 = 0x7C0000;
        s3 = addiu(sp, 0x30);
        s5 = 0x970000;
        s4 = 0x970000;
        s0 = addiu(s0, 1);
        for (;;) {
            // 0x005099a8
            charge(ctx, 3);
            v0 = slti(s0, 1024);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = addu(s1, s0);
            if (cc) {
                goto L_005099e4;
            }
            // 0x005099b4
            charge(ctx, 6);
            a0 = addu(s2, s0);
            lbu(v1, v0, 0);
            sb(v1, a0, 16);
            v1 = sll(v1, 24);
            if (v1 == 0) {
                break;
            }
            s0 = addiu(s0, 1);
            backedge(ctx);
        }
        // 0x005099cc
        charge(ctx, 2);
        v0 = 1024;
    }
    // 0x005099e8
    charge(ctx, 2);
    if (s0 != v0) {
        sw(s6, s2, 12);
    } else {
        // 0x005099f0
        charge(ctx, 3);
        sb(zero, s2, 1039);
        s0 = 1023;
        sw(s6, s2, 12);
    }
    // 0x005099fc
    charge(ctx, 26);
    v1 = addiu(a1, -8544);
    v0 = 1;
    a0 = addiu(sp, 0x10);
    sw(v0, sp, 0x14);
    s4 = addiu(s4, -28352);
    sw(v1, sp, 0x24);
    link(ctx, 0x509A14u);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0x18);
    call(ctx, gen::fn__sceCreateSema_00503160);
    s1 = v0;
    sw(s3, s2, 4);
    v0 = 4;
    sw(s1, s2, 0);
    sw(v0, s2, 8);
    a0 = addiu(s5, -25600);
    a3 = addiu(s7, -31488);
    t0 = addiu(s0, 17);
    sw(zero, sp, 0x0);
    a1 = 7;
    sw(zero, sp, 0x8);
    a2 = 0;
    t1 = s4;
    t2 = 4;
    t3 = 0;
    jal(ctx, 0x509A54u, gen::fn_sceFsSifCallRpc_00507ad8);
    cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
    v0 = 0x20000000;
    if (cc) {
        // 0x00509a7c
        charge(ctx, 5);
        v0 = s4 | v0;
        link(ctx, 0x509A80u);  // $ra first: the delay slot below depends on it
        lw(s0, v0, 0);
        call(ctx, gen::fn__sceFsSigSema_00508078);
        if (s0 != 0) {
            // 0x00509aa0
            charge(ctx, 5);
            a0 = s1;
            jal(ctx, 0x509AA0u, gen::fn__sceWaitSema_005031a0);
            a0 = s1;
            jal(ctx, 0x509AA8u, gen::fn__sceDeleteSema_00503170);
            lw(v0, sp, 0x30);
        } else {
            // 0x00509a90
            charge(ctx, 4);
            a0 = s1;
            jal(ctx, 0x509A90u, gen::fn__sceDeleteSema_00503170);
            v0 = si(-11);
        }
    } else {
        // 0x00509a64
        charge(ctx, 6);
        a0 = s1;
        jal(ctx, 0x509A64u, gen::fn__sceDeleteSema_00503170);
        jal(ctx, 0x509A6Cu, gen::fn__sceFsSigSema_00508078);
        v0 = si(-11);
    }
    // 0x00509ab4 (the shared epilogue, written out on this path)
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

// 0x00509B00 sceFormat -- 640 bytes; frame 0xD0: s0 sp+0x40, s6 sp+0xA0, s2 sp+0x60, s1 sp+0x50, s7 sp+0xB0, s3 sp+0x70, ra sp+0xC0, s5 sp+0x90, s4 sp+0x80
// sceFormat(dev, blockdev, arg, arglen) (file-I/O RPC 14): the names and the argument copied into the request block
// 0x968500, sent with a fresh semaphore and waited for; the answer or -11.
void sceFormat(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00509b00
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(s0, sp, 0x40);
    sd(s6, sp, 0xA0);
    s0 = a0;
    sd(s2, sp, 0x60);
    s6 = a2;
    sd(s1, sp, 0x50);
    s2 = a1;
    sd(s7, sp, 0xB0);
    s1 = a3;
    sd(s3, sp, 0x70);
    a0 = 14;
    sd(ra, sp, 0xC0);
    s7 = 0x970000;
    sd(s5, sp, 0x90);
    s3 = addiu(s7, -31488);  // &0x968500
    link(ctx, 0x509B40u);  // $ra first: the delay slot below depends on it
    sd(s4, sp, 0x80);
    call(ctx, gen::fn__sceFsWaitS_00508048);
    v0 = 0x780000;
    lw(v1, v0, -2756);  // 0x77F53C
    if (v1 != 0) {
        lbu(v0, s0, 0);
    } else {
        // 0x00509b58
        charge(ctx, 3);
        jal(ctx, 0x509B58u, gen::fn_sceFsInit_00508170);
        lbu(v0, s0, 0);
    }
    // 0x00509b64
    charge(ctx, 4);
    a1 = 0;
    v1 = sll(v0, 24);
    sb(v0, s3, 12);
    if (v1 == 0) {
        // 0x00509bac
        charge(ctx, 1);
        a3 = slti(s1, 1025);
    L_00509bb0:
        charge(ctx, 1);
        v0 = 1024;
    } else {
        // 0x00509b74
        charge(ctx, 3);
        a3 = slti(s1, 1025);
        a1 = addiu(a1, 1);
        for (;;) {
            // 0x00509b80
            charge(ctx, 3);
            v0 = slti(a1, 1024);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = addu(s0, a1);
            if (cc) {
                goto L_00509bb0;
            }
            // 0x00509b8c
            charge(ctx, 6);
            a0 = addu(s3, a1);
            lbu(v1, v0, 0);
            sb(v1, a0, 12);
            v1 = sll(v1, 24);
            if (v1 == 0) {
                break;
            }
            a1 = addiu(a1, 1);
            backedge(ctx);
        }
        // 0x00509ba4
        charge(ctx, 2);
        v0 = 1024;
    }
    // 0x00509bb4
    charge(ctx, 2);
    if (a1 == v0) {
        sb(zero, s3, 1035);
    }
    // 0x00509bbc
    charge(ctx, 2);
    if (s2 != 0) {
        lbu(v0, s2, 0);
        // 0x00509bcc
        charge(ctx, 4);
        a1 = 0;
        v1 = sll(v0, 24);
        sb(v0, s3, 1036);
        if (v1 != 0) {
            // 0x00509bdc
            charge(ctx, 3);
            a2 = addiu(s3, 1036);
            a1 = addiu(a1, 1);
            for (;;) {
                // 0x00509be8
                charge(ctx, 3);
                v0 = slti(a1, 1024);
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = addu(s2, a1);
                if (!cc) {
                    // 0x00509bf4
                    charge(ctx, 6);
                    a0 = addu(a2, a1);
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
        // 0x00509c0c
        charge(ctx, 3);
        v0 = 1024;
        if (a1 == v0) {
            sb(zero, s3, 2059);
        }
    } else {
        // 0x00509bc4
        charge(ctx, 2);
        sb(zero, s3, 1036);
    }
    // 0x00509c18
    charge(ctx, 2);
    if (a3 != 0) {
        // 0x00509c30
        charge(ctx, 2);
        a1 = 0;
        if (i64(s1) <= 0) {
            // 0x00509c78
            charge(ctx, 5);
            a3 = 0x7C0000;
            s2 = addiu(sp, 0x30);
            s5 = 0x970000;
            s4 = 0x970000;
            sw(s1, s3, 3084);
        } else {
            // 0x00509c38
            charge(ctx, 6);
            a2 = addiu(s3, 2060);
            a3 = 0x7C0000;
            s2 = addiu(sp, 0x30);
            s5 = 0x970000;
            s4 = 0x970000;
            for (;;) {
                // 0x00509c50
                charge(ctx, 8);
                v0 = addu(s6, a1);
                a0 = addu(a2, a1);
                lbu(v1, v0, 0);
                a1 = addiu(a1, 1);
                v0 = slt(a1, s1);
                sb(v1, a0, 0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00509c70
            charge(ctx, 2);
            sw(s1, s3, 3084);
        }
        // 0x00509c8c
        charge(ctx, 30);
        v1 = addiu(a3, -8520);
        v0 = 1;
        a0 = addiu(sp, 0x10);
        sw(v0, sp, 0x14);
        s0 = addiu(s7, -31488);
        sw(v1, sp, 0x24);
        s4 = addiu(s4, -28352);
        link(ctx, 0x509CA8u);  // $ra first: the delay slot below depends on it
        sw(zero, sp, 0x18);
        call(ctx, gen::fn__sceCreateSema_00503160);
        s1 = v0;
        a0 = s0;
        v0 = 4;
        sw(s2, s3, 4);
        sw(v0, s3, 8);
        a1 = 3088;
        link(ctx, 0x509CC8u);  // $ra first: the delay slot below depends on it
        sw(s1, s3, 0);
        call(ctx, gen::fn_sub_5067F8_005067f8);
        a0 = addiu(s5, -25600);
        a3 = s0;
        sw(zero, sp, 0x0);
        a1 = 14;
        sw(zero, sp, 0x8);
        a2 = 0;
        t0 = 3088;
        t1 = s4;
        t2 = 4;
        t3 = 0;
        jal(ctx, 0x509CF4u, gen::fn_sceFsSifCallRpc_00507ad8);
        cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
        v0 = 0x20000000;
        if (cc) {
            // 0x00509d1c
            charge(ctx, 5);
            v0 = s4 | v0;
            link(ctx, 0x509D20u);  // $ra first: the delay slot below depends on it
            lw(s0, v0, 0);
            call(ctx, gen::fn__sceFsSigSema_00508078);
            if (s0 != 0) {
                // 0x00509d40
                charge(ctx, 5);
                a0 = s1;
                jal(ctx, 0x509D40u, gen::fn__sceWaitSema_005031a0);
                a0 = s1;
                jal(ctx, 0x509D48u, gen::fn__sceDeleteSema_00503170);
                lw(v0, sp, 0x30);
            } else {
                // 0x00509d30
                charge(ctx, 4);
                a0 = s1;
                jal(ctx, 0x509D30u, gen::fn__sceDeleteSema_00503170);
                v0 = si(-11);
            }
        } else {
            // 0x00509d04
            charge(ctx, 6);
            a0 = s1;
            jal(ctx, 0x509D04u, gen::fn__sceDeleteSema_00503170);
            jal(ctx, 0x509D0Cu, gen::fn__sceFsSigSema_00508078);
            v0 = si(-11);
        }
    } else {
        // 0x00509c20
        charge(ctx, 4);
        jal(ctx, 0x509C20u, gen::fn__sceFsSigSema_00508078);
        v0 = si(-7);
    }
    // 0x00509d54 (the shared epilogue, written out on this path)
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

// 0x00509D80 sceAddDrv -- 300 bytes; frame 0x90: s1 sp+0x50, s3 sp+0x70, s0 sp+0x40, ra sp+0x80, s2 sp+0x60
// sceAddDrv(drv) (file-I/O RPC 15): the request sent with a fresh semaphore and waited for; the answer or -11.
void sceAddDrv(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00509d80
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(s1, sp, 0x50);
    s1 = a0;
    sd(s3, sp, 0x70);
    sd(s0, sp, 0x40);
    a0 = 15;
    sd(ra, sp, 0x80);
    s3 = 0x970000;
    sd(s2, sp, 0x60);
    s0 = addiu(s3, -31488);  // &0x968500
    jal(ctx, 0x509DA4u, gen::fn__sceFsWaitS_00508048);
    v1 = 0x780000;
    lw(v0, v1, -2756);  // 0x77F53C
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = 0x7C0000;
    if (!cc) {
        // 0x00509dbc
        charge(ctx, 3);
        jal(ctx, 0x509DBCu, gen::fn_sceFsInit_00508170);
        v0 = 0x7C0000;
    }
    // 0x00509dc8
    charge(ctx, 30);
    sw(s1, s0, 12);
    v1 = 1;
    v0 = addiu(v0, -8496);
    sw(v1, sp, 0x14);
    a0 = addiu(sp, 0x10);
    sw(v0, sp, 0x24);
    link(ctx, 0x509DE0u);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0x18);
    call(ctx, gen::fn__sceCreateSema_00503160);
    s1 = v0;
    v1 = addiu(sp, 0x30);
    v0 = 0x970000;
    sw(s1, s3, -31488);
    s2 = addiu(v0, -28352);  // &0x969140
    sw(v1, s0, 4);
    v0 = 4;
    a0 = 0x970000;
    sw(v0, s0, 8);
    a0 = addiu(a0, -25600);  // &0x969C00
    a3 = s0;
    a1 = 15;
    sw(zero, sp, 0x0);
    a2 = 0;
    sw(zero, sp, 0x8);
    t0 = 16;
    t1 = s2;
    t2 = 4;
    t3 = 0;
    jal(ctx, 0x509E30u, gen::fn_sceFsSifCallRpc_00507ad8);
    cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
    v0 = 0x20000000;
    if (cc) {
        // 0x00509e58
        charge(ctx, 5);
        v0 = s2 | v0;
        link(ctx, 0x509E5Cu);  // $ra first: the delay slot below depends on it
        lw(s0, v0, 0);
        call(ctx, gen::fn__sceFsSigSema_00508078);
        if (s0 != 0) {
            // 0x00509e7c
            charge(ctx, 5);
            a0 = s1;
            jal(ctx, 0x509E7Cu, gen::fn__sceWaitSema_005031a0);
            a0 = s1;
            jal(ctx, 0x509E84u, gen::fn__sceDeleteSema_00503170);
            lw(v0, sp, 0x30);
        } else {
            // 0x00509e6c
            charge(ctx, 4);
            a0 = s1;
            jal(ctx, 0x509E6Cu, gen::fn__sceDeleteSema_00503170);
            v0 = si(-11);
        }
    } else {
        // 0x00509e40
        charge(ctx, 6);
        a0 = s1;
        jal(ctx, 0x509E40u, gen::fn__sceDeleteSema_00503170);
        jal(ctx, 0x509E48u, gen::fn__sceFsSigSema_00508078);
        v0 = si(-11);
    }
    // 0x00509e90 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x80);
    ld(s3, sp, 0x70);
    ld(s2, sp, 0x60);
    ld(s1, sp, 0x50);
    ld(s0, sp, 0x40);
    sp = addiu(sp, 0x90);
}

// 0x00509F98 sceDclose -- 356 bytes; frame 0xA0: s4 sp+0x80, s2 sp+0x60, s0 sp+0x40, ra sp+0x90, s3 sp+0x70, s1 sp+0x50
// sceDclose(fd) (file-I/O RPC 10): closes a directory handle; the answer or -11.
void sceDclose(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00509f98
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(s4, sp, 0x80);
    sd(s2, sp, 0x60);
    s4 = 0x970000;
    sd(s0, sp, 0x40);
    s2 = addiu(s4, -31488);  // &0x968500
    sd(ra, sp, 0x90);
    sd(s3, sp, 0x70);
    link(ctx, 0x509FB8u);  // $ra first: the delay slot below depends on it
    sd(s1, sp, 0x50);
    call(ctx, gen::fn_get_iob_00507bc8);
    s0 = v0;
    a0 = 10;
    jal(ctx, 0x509FC4u, gen::fn__sceFsWaitS_00508048);
    v1 = 0x780000;
    lw(v0, v1, -2756);  // 0x77F53C
    if (v0 != 0) {
        // 0x00509fdc
        charge(ctx, 2);
        if (s0 == 0) {
            goto L_00509ff0;
        }
        // 0x00509fe4
        charge(ctx, 3);
        lw(v0, s0, 4);
        if (v0 == 0) {
            goto L_00509ff0;
        }
        lw(a0, s0, 0);
        // 0x0050a000
        charge(ctx, 31);
        v0 = 0x7C0000;
        v0 = addiu(v0, -8472);  // "SceStdioDcloseSema"
        v1 = 1;
        sw(a0, s2, 12);
        a0 = addiu(sp, 0x10);
        sw(v1, sp, 0x14);
        sw(v0, sp, 0x24);
        link(ctx, 0x50A01Cu);  // $ra first: the delay slot below depends on it
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
        a1 = 10;
        sw(zero, sp, 0x0);
        a2 = 0;
        sw(zero, sp, 0x8);
        t0 = 20;
        t1 = s3;
        t2 = 4;
        t3 = 0;
        jal(ctx, 0x50A06Cu, gen::fn_sceFsSifCallRpc_00507ad8);
        if (i64(v0) >= 0) {
            sw(zero, s0, 4);
            // 0x0050a094
            charge(ctx, 6);
            v0 = 0x20000000;
            v0 = s3 | v0;
            link(ctx, 0x50A09Cu);  // $ra first: the delay slot below depends on it
            lw(s0, v0, 0);
            call(ctx, gen::fn__sceFsSigSema_00508078);
            if (s0 != 0) {
                // 0x0050a0bc
                charge(ctx, 8);
                a0 = s1;
                jal(ctx, 0x50A0BCu, gen::fn__sceWaitSema_005031a0);
                a0 = s1;
                jal(ctx, 0x50A0C4u, gen::fn__sceDeleteSema_00503170);
                lw(v0, sp, 0x30);
                v1 = si(-1);
                v1 = slt(v1, v0);
                if (v1 != 0) v0 = 0;
            } else {
                // 0x0050a0ac
                charge(ctx, 4);
                a0 = s1;
                jal(ctx, 0x50A0ACu, gen::fn__sceDeleteSema_00503170);
                v0 = si(-11);
            }
        } else {
            // 0x0050a07c
            charge(ctx, 6);
            a0 = s1;
            jal(ctx, 0x50A07Cu, gen::fn__sceDeleteSema_00503170);
            jal(ctx, 0x50A084u, gen::fn__sceFsSigSema_00508078);
            v0 = si(-11);
        }
        // 0x0050a0dc (the shared epilogue, written out on this path)
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
L_00509ff0:
    charge(ctx, 4);
    jal(ctx, 0x509FF0u, gen::fn__sceFsSigSema_00508078);
    v0 = si(-9);
    // 0x0050a0dc (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x90);
    ld(s4, sp, 0x80);
    ld(s3, sp, 0x70);
    ld(s2, sp, 0x60);
    ld(s1, sp, 0x50);
    ld(s0, sp, 0x40);
    sp = addiu(sp, 0xA0);
}

// 0x0050A100 sceDread -- 340 bytes; frame 0x90: s1 sp+0x50, s3 sp+0x70, s2 sp+0x60, s0 sp+0x40, ra sp+0x80
// sceDread(fd, dirent) (file-I/O RPC 11): one directory entry into `dirent`; the answer or -11.
void sceDread(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050a100
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(s1, sp, 0x50);
    sd(s3, sp, 0x70);
    s1 = a1;
    sd(s2, sp, 0x60);
    s3 = 0x970000;
    sd(s0, sp, 0x40);
    sd(ra, sp, 0x80);
    s2 = addiu(s3, -31488);  // &0x968500
    jal(ctx, 0x50A120u, gen::fn_get_iob_00507bc8);
    s0 = v0;
    a0 = 11;
    jal(ctx, 0x50A12Cu, gen::fn__sceFsWaitS_00508048);
    v0 = 0x780000;
    lw(v1, v0, -2756);  // 0x77F53C
    if (v1 != 0) {
        // 0x0050a144
        charge(ctx, 2);
        if (s0 == 0) {
            goto L_0050a158;
        }
        // 0x0050a14c
        charge(ctx, 3);
        lw(v0, s0, 4);
        if (v0 == 0) {
            goto L_0050a158;
        }
        lw(v1, s0, 0);
        // 0x0050a168
        charge(ctx, 32);
        v0 = 0x7C0000;
        sw(s1, s2, 16);
        v0 = addiu(v0, -8448);  // "SceStdioDreadSema"
        sw(v1, s2, 12);
        a1 = 1;
        a0 = addiu(sp, 0x10);
        sw(a1, sp, 0x14);
        sw(v0, sp, 0x24);
        link(ctx, 0x50A188u);  // $ra first: the delay slot below depends on it
        sw(zero, sp, 0x18);
        call(ctx, gen::fn__sceCreateSema_00503160);
        s1 = v0;
        v1 = addiu(sp, 0x30);
        v0 = 0x970000;
        sw(s1, s3, -31488);
        s0 = addiu(v0, -28352);  // &0x969140
        sw(v1, s2, 4);
        v0 = 4;
        a0 = 0x970000;
        sw(v0, s2, 8);
        a0 = addiu(a0, -25600);  // &0x969C00
        a3 = s2;
        a1 = 11;
        sw(zero, sp, 0x0);
        a2 = 0;
        sw(zero, sp, 0x8);
        t0 = 32;
        t1 = s0;
        t2 = 4;
        t3 = 0;
        jal(ctx, 0x50A1D8u, gen::fn_sceFsSifCallRpc_00507ad8);
        cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
        v0 = 0x20000000;
        if (cc) {
            // 0x0050a200
            charge(ctx, 5);
            v0 = s0 | v0;
            link(ctx, 0x50A204u);  // $ra first: the delay slot below depends on it
            lw(s0, v0, 0);
            call(ctx, gen::fn__sceFsSigSema_00508078);
            if (s0 != 0) {
                // 0x0050a224
                charge(ctx, 5);
                a0 = s1;
                jal(ctx, 0x50A224u, gen::fn__sceWaitSema_005031a0);
                a0 = s1;
                jal(ctx, 0x50A22Cu, gen::fn__sceDeleteSema_00503170);
                lw(v0, sp, 0x30);
            } else {
                // 0x0050a214
                charge(ctx, 4);
                a0 = s1;
                jal(ctx, 0x50A214u, gen::fn__sceDeleteSema_00503170);
                v0 = si(-11);
            }
        } else {
            // 0x0050a1e8
            charge(ctx, 6);
            a0 = s1;
            jal(ctx, 0x50A1E8u, gen::fn__sceWaitSema_005031a0);
            jal(ctx, 0x50A1F0u, gen::fn__sceFsSigSema_00508078);
            v0 = si(-11);
        }
        // 0x0050a238 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x80);
        ld(s3, sp, 0x70);
        ld(s2, sp, 0x60);
        ld(s1, sp, 0x50);
        ld(s0, sp, 0x40);
        sp = addiu(sp, 0x90);
        return;
    }
L_0050a158:
    charge(ctx, 4);
    jal(ctx, 0x50A158u, gen::fn__sceFsSigSema_00508078);
    v0 = si(-9);
    // 0x0050a238 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x80);
    ld(s3, sp, 0x70);
    ld(s2, sp, 0x60);
    ld(s1, sp, 0x50);
    ld(s0, sp, 0x40);
    sp = addiu(sp, 0x90);
}

// 0x0050A258 sceGetstat -- 436 bytes; frame 0xD0: s1 sp+0x50, s6 sp+0xA0, s7 sp+0xB0, s2 sp+0x60, ra sp+0xC0, s5 sp+0x90, s4 sp+0x80, s3 sp+0x70, s0 sp+0x40
// sceGetstat(path, stat) (file-I/O RPC 12): a file's status into `stat`; the answer or -11.
void sceGetstat(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050a258
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(s1, sp, 0x50);
    sd(s6, sp, 0xA0);
    s1 = a0;
    sd(s7, sp, 0xB0);
    s6 = a1;
    sd(s2, sp, 0x60);
    a0 = 12;
    sd(ra, sp, 0xC0);
    s7 = 0x970000;
    sd(s5, sp, 0x90);
    s2 = addiu(s7, -31488);  // &0x968500
    sd(s4, sp, 0x80);
    sd(s3, sp, 0x70);
    link(ctx, 0x50A290u);  // $ra first: the delay slot below depends on it
    sd(s0, sp, 0x40);
    call(ctx, gen::fn__sceFsWaitS_00508048);
    v0 = 0x780000;
    lw(v1, v0, -2756);  // 0x77F53C
    if (v1 != 0) {
        lbu(v0, s1, 0);
    } else {
        // 0x0050a2a8
        charge(ctx, 3);
        jal(ctx, 0x50A2A8u, gen::fn_sceFsInit_00508170);
        lbu(v0, s1, 0);
    }
    // 0x0050a2b4
    charge(ctx, 4);
    s0 = 0;
    v1 = v0;
    sb(v0, s2, 16);
    if (v1 == 0) {
        // 0x0050a300
        charge(ctx, 4);
        a1 = 0x7C0000;
        s3 = addiu(sp, 0x30);
        s5 = 0x970000;
        s4 = 0x970000;
    L_0050a310:
        charge(ctx, 1);
        v0 = 1024;
    } else {
        // 0x0050a2c4
        charge(ctx, 5);
        a1 = 0x7C0000;
        s3 = addiu(sp, 0x30);
        s5 = 0x970000;
        s4 = 0x970000;
        for (;;) {
            // 0x0050a2d8
            charge(ctx, 4);
            s0 = addiu(s0, 1);
            v0 = slti(s0, 1024);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = addu(s1, s0);
            if (cc) {
                goto L_0050a310;
            }
            // 0x0050a2e8
            charge(ctx, 4);
            a0 = addu(s2, s0);
            lbu(v1, v0, 0);
            sb(v1, a0, 16);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0050a2f8
        charge(ctx, 2);
        v0 = 1024;
    }
    // 0x0050a314
    charge(ctx, 2);
    if (s0 != v0) {
        sw(s6, s2, 12);
    } else {
        // 0x0050a31c
        charge(ctx, 3);
        sb(zero, s2, 1039);
        s0 = 1023;
        sw(s6, s2, 12);
    }
    // 0x0050a328
    charge(ctx, 26);
    v1 = addiu(a1, -8424);
    v0 = 1;
    a0 = addiu(sp, 0x10);
    sw(v0, sp, 0x14);
    s4 = addiu(s4, -28352);
    sw(v1, sp, 0x24);
    link(ctx, 0x50A340u);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0x18);
    call(ctx, gen::fn__sceCreateSema_00503160);
    s1 = v0;
    sw(s3, s2, 4);
    v0 = 4;
    sw(s1, s2, 0);
    sw(v0, s2, 8);
    a0 = addiu(s5, -25600);
    a3 = addiu(s7, -31488);
    t0 = addiu(s0, 17);
    sw(zero, sp, 0x0);
    a1 = 12;
    sw(zero, sp, 0x8);
    a2 = 0;
    t1 = s4;
    t2 = 4;
    t3 = 0;
    jal(ctx, 0x50A380u, gen::fn_sceFsSifCallRpc_00507ad8);
    cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
    v0 = 0x20000000;
    if (cc) {
        // 0x0050a3a8
        charge(ctx, 5);
        v0 = s4 | v0;
        link(ctx, 0x50A3ACu);  // $ra first: the delay slot below depends on it
        lw(s0, v0, 0);
        call(ctx, gen::fn__sceFsSigSema_00508078);
        if (s0 != 0) {
            // 0x0050a3cc
            charge(ctx, 5);
            a0 = s1;
            jal(ctx, 0x50A3CCu, gen::fn__sceWaitSema_005031a0);
            a0 = s1;
            jal(ctx, 0x50A3D4u, gen::fn__sceDeleteSema_00503170);
            lw(v0, sp, 0x30);
        } else {
            // 0x0050a3bc
            charge(ctx, 4);
            a0 = s1;
            jal(ctx, 0x50A3BCu, gen::fn__sceDeleteSema_00503170);
            v0 = si(-11);
        }
    } else {
        // 0x0050a390
        charge(ctx, 6);
        a0 = s1;
        jal(ctx, 0x50A390u, gen::fn__sceDeleteSema_00503170);
        jal(ctx, 0x50A398u, gen::fn__sceFsSigSema_00508078);
        v0 = si(-11);
    }
    // 0x0050a3e0 (the shared epilogue, written out on this path)
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

// 0x0050A410 sceChstat -- 588 bytes; frame 0xE0: s2 sp+0x60, s7 sp+0xB0, s0 sp+0x40, fp sp+0xC0, s3 sp+0x70, ra sp+0xD0, s6 sp+0xA0, s5 sp+0x90, s4 sp+0x80, s1 sp+0x50
// sceChstat(path, stat, mask) (file-I/O RPC 13): changes the masked status fields; the answer or -11.
void sceChstat(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050a410
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
    sd(s2, sp, 0x60);
    sd(s7, sp, 0xB0);
    s2 = a0;
    sd(s0, sp, 0x40);
    s7 = a2;
    sd(fp, sp, 0xC0);
    s0 = a1;
    sd(s3, sp, 0x70);
    a0 = 13;
    sd(ra, sp, 0xD0);
    fp = 0x970000;
    sd(s6, sp, 0xA0);
    s3 = addiu(fp, -0x7B00);
    sd(s5, sp, 0x90);
    sd(s4, sp, 0x80);
    link(ctx, 0x50A450u);  // $ra first: the delay slot below depends on it
    sd(s1, sp, 0x50);
    call(ctx, gen::fn__sceFsWaitS_00508048);
    v1 = 0x780000;
    lw(v0, v1, -2756);  // 0x77F53C
    if (v0 != 0) {
        lbu(v0, s2, 0);
    } else {
        // 0x0050a468
        charge(ctx, 3);
        jal(ctx, 0x50A468u, gen::fn_sceFsInit_00508170);
        lbu(v0, s2, 0);
    }
    // 0x0050a474
    charge(ctx, 4);
    s1 = 0;
    v1 = v0;
    sb(v0, s3, 80);
    if (v1 == 0) {
        // 0x0050a4c0
        charge(ctx, 4);
        a1 = 0x7C0000;
        s4 = addiu(sp, 0x30);
        s6 = 0x970000;
        s5 = 0x970000;
    L_0050a4d0:
        charge(ctx, 1);
        v0 = 1024;
    } else {
        // 0x0050a484
        charge(ctx, 5);
        a1 = 0x7C0000;
        s4 = addiu(sp, 0x30);
        s6 = 0x970000;
        s5 = 0x970000;
        for (;;) {
            // 0x0050a498
            charge(ctx, 4);
            s1 = addiu(s1, 1);
            v0 = slti(s1, 1024);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = addu(s2, s1);
            if (cc) {
                goto L_0050a4d0;
            }
            // 0x0050a4a8
            charge(ctx, 4);
            a0 = addu(s3, s1);
            lbu(v1, v0, 0);
            sb(v1, a0, 80);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0050a4b8
        charge(ctx, 2);
        v0 = 1024;
    }
    // 0x0050a4d4
    charge(ctx, 2);
    v1 = addiu(a1, -8400);
    if (s1 == v0) {
        // 0x0050a4dc
        charge(ctx, 2);
        sb(zero, s3, 1103);
        s1 = 1023;
    }
    // 0x0050a4e4
    charge(ctx, 62);
    v0 = 1;
    ldl(a0, s0, 7);
    ldr(a0, s0, 0);
    ldl(a1, s0, 15);
    ldr(a1, s0, 8);
    ldl(a2, s0, 23);
    ldr(a2, s0, 16);
    ldl(a3, s0, 31);
    ldr(a3, s0, 24);
    sdl(a0, s3, 23);
    sdr(a0, s3, 16);
    sdl(a1, s3, 31);
    sdr(a1, s3, 24);
    sdl(a2, s3, 39);
    sdr(a2, s3, 32);
    sdl(a3, s3, 47);
    sdr(a3, s3, 40);
    ldl(a0, s0, 39);
    ldr(a0, s0, 32);
    ldl(a1, s0, 47);
    ldr(a1, s0, 40);
    ldl(a2, s0, 55);
    ldr(a2, s0, 48);
    ldl(a3, s0, 63);
    ldr(a3, s0, 56);
    sdl(a0, s3, 55);
    sdr(a0, s3, 48);
    sdl(a1, s3, 63);
    sdr(a1, s3, 56);
    sdl(a2, s3, 71);
    sdr(a2, s3, 64);
    sdl(a3, s3, 79);
    sdr(a3, s3, 72);
    s5 = addiu(s5, -28352);
    sw(s7, s3, 12);
    a0 = addiu(sp, 0x10);
    sw(v0, sp, 0x14);
    s0 = addiu(fp, -0x7B00);
    sw(v1, sp, 0x24);
    link(ctx, 0x50A580u);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0x18);
    call(ctx, gen::fn__sceCreateSema_00503160);
    s2 = v0;
    a0 = s0;
    v0 = 4;
    sw(s4, s3, 4);
    sw(v0, s3, 8);
    a1 = 1104;
    link(ctx, 0x50A5A0u);  // $ra first: the delay slot below depends on it
    sw(s2, s3, 0);
    call(ctx, gen::fn_sub_5067F8_005067f8);
    a0 = addiu(s6, -25600);
    a3 = s0;
    t0 = addiu(s1, 81);
    sw(zero, sp, 0x0);
    sw(zero, sp, 0x8);
    a1 = 13;
    a2 = 0;
    t1 = s5;
    t2 = 4;
    t3 = 0;
    jal(ctx, 0x50A5CCu, gen::fn_sceFsSifCallRpc_00507ad8);
    cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
    v0 = 0x20000000;
    if (cc) {
        // 0x0050a5f4
        charge(ctx, 5);
        v0 = s5 | v0;
        link(ctx, 0x50A5F8u);  // $ra first: the delay slot below depends on it
        lw(s0, v0, 0);
        call(ctx, gen::fn__sceFsSigSema_00508078);
        if (s0 != 0) {
            // 0x0050a618
            charge(ctx, 5);
            a0 = s2;
            jal(ctx, 0x50A618u, gen::fn__sceWaitSema_005031a0);
            a0 = s2;
            jal(ctx, 0x50A620u, gen::fn__sceDeleteSema_00503170);
            lw(v0, sp, 0x30);
        } else {
            // 0x0050a608
            charge(ctx, 4);
            a0 = s2;
            jal(ctx, 0x50A608u, gen::fn__sceDeleteSema_00503170);
            v0 = si(-11);
        }
    } else {
        // 0x0050a5dc
        charge(ctx, 6);
        a0 = s2;
        jal(ctx, 0x50A5DCu, gen::fn__sceDeleteSema_00503170);
        jal(ctx, 0x50A5E4u, gen::fn__sceFsSigSema_00508078);
        v0 = si(-11);
    }
    // 0x0050a62c (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xE0);
}

// 0x0050A660 sceRename -- 520 bytes; frame 0xC0: s1 sp+0x50, s0 sp+0x40, s6 sp+0xA0, s2 sp+0x60, ra sp+0xB0, s5 sp+0x90, s4 sp+0x80, s3 sp+0x70
// sceRename(old, new) (file-I/O RPC 17): both paths copied into the request block, sent and waited for; the answer or
// -11.
void sceRename(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050a660
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(s1, sp, 0x50);
    sd(s0, sp, 0x40);
    s1 = a0;
    sd(s6, sp, 0xA0);
    s0 = a1;
    sd(s2, sp, 0x60);
    a0 = 17;
    sd(ra, sp, 0xB0);
    s6 = 0x970000;
    sd(s5, sp, 0x90);
    s2 = addiu(s6, -31488);  // &0x968500
    sd(s4, sp, 0x80);
    link(ctx, 0x50A694u);  // $ra first: the delay slot below depends on it
    sd(s3, sp, 0x70);
    call(ctx, gen::fn__sceFsWaitS_00508048);
    v0 = 0x780000;
    lw(v1, v0, -2756);  // 0x77F53C
    if (v1 != 0) {
        lbu(v0, s1, 0);
    } else {
        // 0x0050a6ac
        charge(ctx, 3);
        jal(ctx, 0x50A6ACu, gen::fn_sceFsInit_00508170);
        lbu(v0, s1, 0);
    }
    // 0x0050a6b8
    charge(ctx, 4);
    a1 = 0;
    v1 = sll(v0, 24);
    sb(v0, s2, 12);
    if (v1 == 0) {
        // 0x0050a70c
        charge(ctx, 4);
        a3 = 0x7C0000;
        s3 = addiu(sp, 0x30);
        s5 = 0x970000;
        s4 = 0x970000;
    L_0050a71c:
        charge(ctx, 1);
        v0 = 1024;
    } else {
        // 0x0050a6c8
        charge(ctx, 6);
        a3 = 0x7C0000;
        s3 = addiu(sp, 0x30);
        s5 = 0x970000;
        s4 = 0x970000;
        a1 = addiu(a1, 1);
        for (;;) {
            // 0x0050a6e0
            charge(ctx, 3);
            v0 = slti(a1, 1024);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = addu(s1, a1);
            if (cc) {
                goto L_0050a71c;
            }
            // 0x0050a6ec
            charge(ctx, 6);
            a0 = addu(s2, a1);
            lbu(v1, v0, 0);
            sb(v1, a0, 12);
            v1 = sll(v1, 24);
            if (v1 == 0) {
                break;
            }
            a1 = addiu(a1, 1);
            backedge(ctx);
        }
        // 0x0050a704
        charge(ctx, 2);
        v0 = 1024;
    }
    // 0x0050a720
    charge(ctx, 2);
    if (a1 == v0) {
        sb(zero, s2, 1035);
    }
    // 0x0050a728
    charge(ctx, 5);
    lbu(v0, s0, 0);
    a1 = 0;
    v1 = sll(v0, 24);
    sb(v0, s2, 1036);
    if (v1 != 0) {
        // 0x0050a73c
        charge(ctx, 3);
        a2 = addiu(s2, 1036);
        a1 = addiu(a1, 1);
        for (;;) {
            // 0x0050a748
            charge(ctx, 3);
            v0 = slti(a1, 1024);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = addu(s0, a1);
            if (!cc) {
                // 0x0050a754
                charge(ctx, 6);
                a0 = addu(a2, a1);
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
    // 0x0050a76c
    charge(ctx, 3);
    v0 = 1024;
    if (a1 == v0) {
        sb(zero, s2, 2059);
    }
    // 0x0050a778
    charge(ctx, 30);
    v1 = addiu(a3, -8376);
    v0 = 1;
    sw(v0, sp, 0x14);
    a0 = addiu(sp, 0x10);
    sw(v1, sp, 0x24);
    s0 = addiu(s6, -31488);
    sw(zero, sp, 0x18);
    s4 = addiu(s4, -28352);
    jal(ctx, 0x50A794u, gen::fn__sceCreateSema_00503160);
    s1 = v0;
    a0 = s0;
    v0 = 4;
    sw(s3, s2, 4);
    sw(v0, s2, 8);
    a1 = 2060;
    link(ctx, 0x50A7B4u);  // $ra first: the delay slot below depends on it
    sw(s1, s2, 0);
    call(ctx, gen::fn_sub_5067F8_005067f8);
    a0 = addiu(s5, -25600);
    a3 = s0;
    sw(zero, sp, 0x0);
    a1 = 17;
    sw(zero, sp, 0x8);
    a2 = 0;
    t0 = 2060;
    t1 = s4;
    t2 = 4;
    t3 = 0;
    jal(ctx, 0x50A7E0u, gen::fn_sceFsSifCallRpc_00507ad8);
    cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
    v0 = 0x20000000;
    if (cc) {
        // 0x0050a808
        charge(ctx, 5);
        v0 = s4 | v0;
        link(ctx, 0x50A80Cu);  // $ra first: the delay slot below depends on it
        lw(s0, v0, 0);
        call(ctx, gen::fn__sceFsSigSema_00508078);
        if (s0 != 0) {
            // 0x0050a82c
            charge(ctx, 5);
            a0 = s1;
            jal(ctx, 0x50A82Cu, gen::fn__sceWaitSema_005031a0);
            a0 = s1;
            jal(ctx, 0x50A834u, gen::fn__sceDeleteSema_00503170);
            lw(v0, sp, 0x30);
        } else {
            // 0x0050a81c
            charge(ctx, 4);
            a0 = s1;
            jal(ctx, 0x50A81Cu, gen::fn__sceDeleteSema_00503170);
            v0 = si(-11);
        }
    } else {
        // 0x0050a7f0
        charge(ctx, 6);
        a0 = s1;
        jal(ctx, 0x50A7F0u, gen::fn__sceDeleteSema_00503170);
        jal(ctx, 0x50A7F8u, gen::fn__sceFsSigSema_00508078);
        v0 = si(-11);
    }
    // 0x0050a840 (the shared epilogue, written out on this path)
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
}

// 0x0050AA38 sceMount -- 640 bytes; frame 0xE0: s0 sp+0x40, s7 sp+0xB0, s6 sp+0xA0, s3 sp+0x70, s1 sp+0x50, fp sp+0xC0, s2 sp+0x60, ra sp+0xD0, s5 sp+0x90, s4 sp+0x80
// sceMount(fsname, devname, flag, arg, arglen) (file-I/O RPC 20); the answer or -11.
void sceMount(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050aa38
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
    sd(s0, sp, 0x40);
    sd(s7, sp, 0xB0);
    s0 = a0;
    sd(s6, sp, 0xA0);
    s7 = a2;
    sd(s3, sp, 0x70);
    s6 = a3;
    sd(s1, sp, 0x50);
    s3 = a1;
    sd(fp, sp, 0xC0);
    s1 = t0;
    sd(s2, sp, 0x60);
    a0 = 20;
    sd(ra, sp, 0xD0);
    fp = 0x970000;
    sd(s5, sp, 0x90);
    s2 = addiu(fp, -0x7B00);
    link(ctx, 0x50AA80u);  // $ra first: the delay slot below depends on it
    sd(s4, sp, 0x80);
    call(ctx, gen::fn__sceFsWaitS_00508048);
    v1 = 0x780000;
    lw(v0, v1, -2756);  // 0x77F53C
    if (v0 != 0) {
        lbu(v0, s0, 0);
    } else {
        // 0x0050aa98
        charge(ctx, 3);
        jal(ctx, 0x50AA98u, gen::fn_sceFsInit_00508170);
        lbu(v0, s0, 0);
    }
    // 0x0050aaa4
    charge(ctx, 4);
    a1 = 0;
    v1 = sll(v0, 24);
    sb(v0, s2, 12);
    if (v1 == 0) {
        // 0x0050aaec
        charge(ctx, 1);
        a3 = slti(s1, 1025);
    L_0050aaf0:
        charge(ctx, 1);
        v0 = 1024;
    } else {
        // 0x0050aab4
        charge(ctx, 3);
        a3 = slti(s1, 1025);
        a1 = addiu(a1, 1);
        for (;;) {
            // 0x0050aac0
            charge(ctx, 3);
            v0 = slti(a1, 1024);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = addu(s0, a1);
            if (cc) {
                goto L_0050aaf0;
            }
            // 0x0050aacc
            charge(ctx, 6);
            a0 = addu(s2, a1);
            lbu(v1, v0, 0);
            sb(v1, a0, 12);
            v1 = sll(v1, 24);
            if (v1 == 0) {
                break;
            }
            a1 = addiu(a1, 1);
            backedge(ctx);
        }
        // 0x0050aae4
        charge(ctx, 2);
        v0 = 1024;
    }
    // 0x0050aaf4
    charge(ctx, 2);
    if (a1 == v0) {
        sb(zero, s2, 1035);
    }
    // 0x0050aafc
    charge(ctx, 5);
    lbu(v0, s3, 0);
    a1 = 0;
    v1 = sll(v0, 24);
    sb(v0, s2, 1036);
    if (v1 != 0) {
        // 0x0050ab10
        charge(ctx, 2);
        a2 = addiu(s2, 1036);
        a1 = addiu(a1, 1);
        for (;;) {
            // 0x0050ab18
            charge(ctx, 3);
            v0 = slti(a1, 1024);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = addu(s3, a1);
            if (!cc) {
                // 0x0050ab24
                charge(ctx, 6);
                a0 = addu(a2, a1);
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
    // 0x0050ab3c
    charge(ctx, 3);
    v0 = 1024;
    if (a1 == v0) {
        sb(zero, s2, 2059);
    }
    // 0x0050ab48
    charge(ctx, 2);
    if (a3 != 0) {
        // 0x0050ab60
        charge(ctx, 2);
        a1 = 0;
        if (i64(s1) <= 0) {
            // 0x0050aba8
            charge(ctx, 5);
            a3 = 0x7C0000;
            s3 = addiu(sp, 0x30);
            s5 = 0x970000;
            s4 = 0x970000;
            sw(s1, s2, 3088);
        } else {
            // 0x0050ab68
            charge(ctx, 6);
            a2 = addiu(s2, 2060);
            a3 = 0x7C0000;
            s3 = addiu(sp, 0x30);
            s5 = 0x970000;
            s4 = 0x970000;
            for (;;) {
                // 0x0050ab80
                charge(ctx, 8);
                v0 = addu(s6, a1);
                a0 = addu(a2, a1);
                lbu(v1, v0, 0);
                a1 = addiu(a1, 1);
                v0 = slt(a1, s1);
                sb(v1, a0, 0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0050aba0
            charge(ctx, 2);
            sw(s1, s2, 3088);
        }
        // 0x0050abbc
        charge(ctx, 31);
        v1 = addiu(a3, -8328);
        sw(s7, s2, 3084);
        v0 = 1;
        a0 = addiu(sp, 0x10);
        sw(v0, sp, 0x14);
        sw(v1, sp, 0x24);
        s0 = addiu(fp, -0x7B00);
        sw(zero, sp, 0x18);
        s4 = addiu(s4, -28352);
        jal(ctx, 0x50ABDCu, gen::fn__sceCreateSema_00503160);
        s1 = v0;
        a0 = s0;
        v0 = 4;
        sw(s3, s2, 4);
        sw(v0, s2, 8);
        a1 = 3092;
        link(ctx, 0x50ABFCu);  // $ra first: the delay slot below depends on it
        sw(s1, s2, 0);
        call(ctx, gen::fn_sub_5067F8_005067f8);
        a0 = addiu(s5, -25600);
        a3 = s0;
        sw(zero, sp, 0x0);
        a1 = 20;
        sw(zero, sp, 0x8);
        a2 = 0;
        t0 = 3092;
        t1 = s4;
        t2 = 4;
        t3 = 0;
        jal(ctx, 0x50AC28u, gen::fn_sceFsSifCallRpc_00507ad8);
        cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
        v0 = 0x20000000;
        if (cc) {
            // 0x0050ac50
            charge(ctx, 5);
            v0 = s4 | v0;
            link(ctx, 0x50AC54u);  // $ra first: the delay slot below depends on it
            lw(s0, v0, 0);
            call(ctx, gen::fn__sceFsSigSema_00508078);
            if (s0 != 0) {
                // 0x0050ac74
                charge(ctx, 5);
                a0 = s1;
                jal(ctx, 0x50AC74u, gen::fn__sceWaitSema_005031a0);
                a0 = s1;
                jal(ctx, 0x50AC7Cu, gen::fn__sceDeleteSema_00503170);
                lw(v0, sp, 0x30);
            } else {
                // 0x0050ac64
                charge(ctx, 4);
                a0 = s1;
                jal(ctx, 0x50AC64u, gen::fn__sceDeleteSema_00503170);
                v0 = si(-11);
            }
        } else {
            // 0x0050ac38
            charge(ctx, 6);
            a0 = s1;
            jal(ctx, 0x50AC38u, gen::fn__sceDeleteSema_00503170);
            jal(ctx, 0x50AC40u, gen::fn__sceFsSigSema_00508078);
            v0 = si(-11);
        }
    } else {
        // 0x0050ab50
        charge(ctx, 4);
        jal(ctx, 0x50AB50u, gen::fn__sceFsSigSema_00508078);
        v0 = si(-7);
    }
    // 0x0050ac88 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xE0);
}

// 0x0050AF18 sceDevctl -- 680 bytes; frame 0xE0: s3 sp+0x70, fp sp+0xC0, s5 sp+0x90, s2 sp+0x60, s0 sp+0x40, s1 sp+0x50, ra sp+0xD0, s7 sp+0xB0, s6 sp+0xA0, s4 sp+0x80
// sceDevctl(dev, cmd, arg, arglen, buf, buflen) (file-I/O RPC, a 2076-byte request): device control with an output
// buffer; the answer, -22 for refused arguments, -11 when the RPC fails.
void sceDevctl(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050af18
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
    sd(s3, sp, 0x70);
    sd(fp, sp, 0xC0);
    s3 = a0;
    sd(s5, sp, 0x90);
    fp = t1;
    sd(s2, sp, 0x60);
    s5 = a1;
    sd(s0, sp, 0x40);
    s2 = a2;
    sd(s1, sp, 0x50);
    s0 = a3;
    sd(ra, sp, 0xD0);
    a0 = 23;
    sd(s7, sp, 0xB0);
    sd(s6, sp, 0xA0);
    sd(s4, sp, 0x80);
    link(ctx, 0x50AF5Cu);  // $ra first: the delay slot below depends on it
    sw(t0, sp, 0x34);
    call(ctx, gen::fn__sceFsWaitS_00508048);
    v0 = 0x970000;
    s1 = addiu(v0, -31488);  // &0x968500
    v0 = 0x780000;
    lw(v1, v0, -2756);  // 0x77F53C
    if (v1 != 0) {
        lbu(v0, s3, 0);
    } else {
        // 0x0050af7c
        charge(ctx, 3);
        jal(ctx, 0x50AF7Cu, gen::fn_sceFsInit_00508170);
        lbu(v0, s3, 0);
    }
    // 0x0050af88
    charge(ctx, 4);
    a1 = 0;
    v1 = sll(v0, 24);
    sb(v0, s1, 12);
    if (v1 == 0) {
        // 0x0050afcc
        charge(ctx, 1);
        a2 = sltiu(s0, 1025);
    L_0050afd0:
        charge(ctx, 1);
        v0 = 1024;
    } else {
        // 0x0050af98
        charge(ctx, 2);
        a2 = sltiu(s0, 1025);
        a1 = addiu(a1, 1);
        for (;;) {
            // 0x0050afa0
            charge(ctx, 3);
            v0 = slti(a1, 1024);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = addu(s3, a1);
            if (cc) {
                goto L_0050afd0;
            }
            // 0x0050afac
            charge(ctx, 6);
            a0 = addu(s1, a1);
            lbu(v1, v0, 0);
            sb(v1, a0, 12);
            v1 = sll(v1, 24);
            if (v1 == 0) {
                break;
            }
            a1 = addiu(a1, 1);
            backedge(ctx);
        }
        // 0x0050afc4
        charge(ctx, 2);
        v0 = 1024;
    }
    // 0x0050afd4
    charge(ctx, 2);
    if (a1 == v0) {
        sb(zero, s1, 1035);
    }
    // 0x0050afdc
    charge(ctx, 2);
    v0 = sltiu(fp, 1025);
    if (a2 != 0) {
        // 0x0050afe4
        charge(ctx, 2);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 17921;
        if (cc) {
            goto L_0050b018;
        }
        // 0x0050afec
        charge(ctx, 2);
        if (s5 == v0) {
            // 0x0050aff4
            charge(ctx, 3);
            lw(v0, s2, 4);
            if (v0 != 0) {
                lw(v0, s2, 12);
                // 0x0050b010
                charge(ctx, 2);
                if (v0 != 0) {
                    goto L_0050b028;
                }
                goto L_0050b018;
            }
            // 0x0050b000
            charge(ctx, 4);
            jal(ctx, 0x50B000u, gen::fn__sceFsSigSema_00508078);
            v0 = 0;
            // 0x0050b190 (the shared epilogue, written out on this path)
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
            sp = addiu(sp, 0xE0);
            return;
        }
    L_0050b028:
        charge(ctx, 2);
        a1 = 0;
        if (s0 == 0) {
            // 0x0050b070
            charge(ctx, 5);
            a3 = 0x7C0000;
            s3 = addiu(sp, 0x30);
            s7 = 0x970000;
            s6 = 0x970000;
            sw(s0, s1, 2064);
        } else {
            // 0x0050b030
            charge(ctx, 6);
            a2 = addiu(s1, 1036);
            a3 = 0x7C0000;
            s3 = addiu(sp, 0x30);
            s7 = 0x970000;
            s6 = 0x970000;
            for (;;) {
                // 0x0050b048
                charge(ctx, 8);
                v0 = addu(s2, a1);
                a0 = addu(a2, a1);
                lbu(v1, v0, 0);
                a1 = addiu(a1, 1);
                v0 = sltu(a1, s0);
                sb(v1, a0, 0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0050b068
            charge(ctx, 2);
            sw(s0, s1, 2064);
        }
        // 0x0050b084
        charge(ctx, 18);
        v1 = addiu(a3, -8280);
        v0 = 1;
        sw(v1, sp, 0x24);
        sw(v0, sp, 0x14);
        a0 = addiu(sp, 0x10);
        sw(s5, s1, 2060);
        link(ctx, 0x50B09Cu);  // $ra first: the delay slot below depends on it
        sw(zero, sp, 0x18);
        call(ctx, gen::fn__sceCreateSema_00503160);
        s4 = v0;
        sw(fp, s1, 2072);
        v0 = 4;
        sw(s3, s1, 4);
        sw(v0, s1, 8);
        v1 = 17921;
        lw(v0, sp, 0x34);
        sw(s4, s1, 0);
        sw(v0, s1, 2068);
        if (s5 != v1) {
            // 0x0050b0f0
            charge(ctx, 2);
            s1 = 23;
            v0 = 0x970000;
        } else {
            // 0x0050b0cc
            charge(ctx, 9);
            lw(a1, s2, 12);
            s1 = 28;
            lw(v0, s2, 4);
            mult(zero, v0, a1);
            mflo(a1);
            link(ctx, 0x50B0E0u);  // $ra first: the delay slot below depends on it
            lw(a0, s2, 8);
            call(ctx, gen::fn_sub_5067F8_005067f8);
            v0 = 0x970000;
        }
        // 0x0050b0f8
        charge(ctx, 18);
        a1 = 2076;
        s0 = addiu(v0, -31488);
        s2 = addiu(s6, -28352);
        a0 = s0;
        jal(ctx, 0x50B104u, gen::fn_sub_5067F8_005067f8);
        a0 = addiu(s7, -25600);
        a1 = s1;
        a3 = s0;
        sw(zero, sp, 0x0);
        sw(zero, sp, 0x8);
        a2 = 0;
        t0 = 2076;
        t1 = s2;
        t2 = 4;
        t3 = 0;
        jal(ctx, 0x50B130u, gen::fn_sceFsSifCallRpc_00507ad8);
        cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
        v0 = 0x20000000;
        if (cc) {
            // 0x0050b158
            charge(ctx, 5);
            v0 = s2 | v0;
            link(ctx, 0x50B15Cu);  // $ra first: the delay slot below depends on it
            lw(s0, v0, 0);
            call(ctx, gen::fn__sceFsSigSema_00508078);
            if (s0 != 0) {
                // 0x0050b17c
                charge(ctx, 5);
                a0 = s4;
                jal(ctx, 0x50B17Cu, gen::fn__sceWaitSema_005031a0);
                a0 = s4;
                jal(ctx, 0x50B184u, gen::fn__sceDeleteSema_00503170);
                lw(v0, sp, 0x30);
            } else {
                // 0x0050b16c
                charge(ctx, 4);
                a0 = s4;
                jal(ctx, 0x50B16Cu, gen::fn__sceDeleteSema_00503170);
                v0 = si(-11);
            }
        } else {
            // 0x0050b140
            charge(ctx, 6);
            a0 = s4;
            jal(ctx, 0x50B140u, gen::fn__sceDeleteSema_00503170);
            jal(ctx, 0x50B148u, gen::fn__sceFsSigSema_00508078);
            v0 = si(-11);
        }
        // 0x0050b190 (the shared epilogue, written out on this path)
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
        sp = addiu(sp, 0xE0);
        return;
    }
L_0050b018:
    charge(ctx, 4);
    jal(ctx, 0x50B018u, gen::fn__sceFsSigSema_00508078);
    v0 = si(-22);
    // 0x0050b190 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xE0);
}

// 0x0050B1C0 sceSymlink -- 504 bytes; frame 0xC0: s0 sp+0x40, s1 sp+0x50, s6 sp+0xA0, s2 sp+0x60, ra sp+0xB0, s5 sp+0x90, s4 sp+0x80, s3 sp+0x70
// sceSymlink(existing, new) (file-I/O RPC 24); the answer or -11.
void sceSymlink(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050b1c0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(s0, sp, 0x40);
    sd(s1, sp, 0x50);
    s0 = a0;
    sd(s6, sp, 0xA0);
    s1 = a1;
    sd(s2, sp, 0x60);
    a0 = 17;
    sd(ra, sp, 0xB0);
    s6 = 0x970000;
    sd(s5, sp, 0x90);
    s2 = addiu(s6, -31488);  // &0x968500
    sd(s4, sp, 0x80);
    link(ctx, 0x50B1F4u);  // $ra first: the delay slot below depends on it
    sd(s3, sp, 0x70);
    call(ctx, gen::fn__sceFsWaitS_00508048);
    v0 = 0x780000;
    lw(v1, v0, -2756);  // 0x77F53C
    if (v1 != 0) {
        lbu(v0, s0, 0);
    } else {
        // 0x0050b20c
        charge(ctx, 3);
        jal(ctx, 0x50B20Cu, gen::fn_sceFsInit_00508170);
        lbu(v0, s0, 0);
    }
    // 0x0050b218
    charge(ctx, 4);
    a1 = 0;
    v1 = sll(v0, 24);
    sb(v0, s2, 12);
    if (v1 == 0) {
        // 0x0050b26c
        charge(ctx, 4);
        a3 = 0x7C0000;
        s3 = addiu(sp, 0x30);
        s5 = 0x970000;
        s4 = 0x970000;
    L_0050b27c:
        charge(ctx, 1);
        v0 = 1024;
    } else {
        // 0x0050b228
        charge(ctx, 6);
        a3 = 0x7C0000;
        s3 = addiu(sp, 0x30);
        s5 = 0x970000;
        s4 = 0x970000;
        a1 = addiu(a1, 1);
        for (;;) {
            // 0x0050b240
            charge(ctx, 3);
            v0 = slti(a1, 1024);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = addu(s0, a1);
            if (cc) {
                goto L_0050b27c;
            }
            // 0x0050b24c
            charge(ctx, 6);
            a0 = addu(s2, a1);
            lbu(v1, v0, 0);
            sb(v1, a0, 12);
            v1 = sll(v1, 24);
            if (v1 == 0) {
                break;
            }
            a1 = addiu(a1, 1);
            backedge(ctx);
        }
        // 0x0050b264
        charge(ctx, 2);
        v0 = 1024;
    }
    // 0x0050b280
    charge(ctx, 2);
    if (a1 == v0) {
        sb(zero, s2, 1035);
    }
    // 0x0050b288
    charge(ctx, 5);
    lbu(v0, s1, 0);
    a1 = 0;
    v1 = sll(v0, 24);
    sb(v0, s2, 1036);
    if (v1 != 0) {
        // 0x0050b29c
        charge(ctx, 3);
        a2 = addiu(s2, 1036);
        a1 = addiu(a1, 1);
        for (;;) {
            // 0x0050b2a8
            charge(ctx, 3);
            v0 = slti(a1, 1024);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = addu(s1, a1);
            if (!cc) {
                // 0x0050b2b4
                charge(ctx, 6);
                a0 = addu(a2, a1);
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
    // 0x0050b2cc
    charge(ctx, 3);
    v0 = 1024;
    if (a1 == v0) {
        sb(zero, s2, 2059);
    }
    // 0x0050b2d8
    charge(ctx, 26);
    v0 = addiu(a3, -8256);
    v1 = 1;
    sw(v1, sp, 0x14);
    a0 = addiu(sp, 0x10);
    sw(v0, sp, 0x24);
    s0 = addiu(s4, -28352);
    link(ctx, 0x50B2F0u);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0x18);
    call(ctx, gen::fn__sceCreateSema_00503160);
    s1 = v0;
    sw(s3, s2, 4);
    v0 = 4;
    sw(s1, s2, 0);
    sw(v0, s2, 8);
    a0 = addiu(s5, -25600);
    a3 = addiu(s6, -31488);
    a1 = 24;
    sw(zero, sp, 0x0);
    a2 = 0;
    sw(zero, sp, 0x8);
    t0 = 2060;
    t1 = s0;
    t2 = 4;
    t3 = 0;
    jal(ctx, 0x50B330u, gen::fn_sceFsSifCallRpc_00507ad8);
    cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
    v0 = 0x20000000;
    if (cc) {
        // 0x0050b358
        charge(ctx, 5);
        v0 = s0 | v0;
        link(ctx, 0x50B35Cu);  // $ra first: the delay slot below depends on it
        lw(s0, v0, 0);
        call(ctx, gen::fn__sceFsSigSema_00508078);
        if (s0 != 0) {
            // 0x0050b37c
            charge(ctx, 5);
            a0 = s1;
            jal(ctx, 0x50B37Cu, gen::fn__sceWaitSema_005031a0);
            a0 = s1;
            jal(ctx, 0x50B384u, gen::fn__sceDeleteSema_00503170);
            lw(v0, sp, 0x30);
        } else {
            // 0x0050b36c
            charge(ctx, 4);
            a0 = s1;
            jal(ctx, 0x50B36Cu, gen::fn__sceDeleteSema_00503170);
            v0 = si(-11);
        }
    } else {
        // 0x0050b340
        charge(ctx, 6);
        a0 = s1;
        jal(ctx, 0x50B340u, gen::fn__sceDeleteSema_00503170);
        jal(ctx, 0x50B348u, gen::fn__sceFsSigSema_00508078);
        v0 = si(-11);
    }
    // 0x0050b390 (the shared epilogue, written out on this path)
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
}

// 0x0050B3B8 sceReadlink -- 480 bytes; frame 0xE0: s1 sp+0x50, s5 sp+0x90, s0 sp+0x40, fp sp+0xC0, s2 sp+0x60, ra sp+0xD0, s7 sp+0xB0, s6 sp+0xA0, s4 sp+0x80, s3 sp+0x70
// sceReadlink(path, buf, size) (file-I/O RPC 25): the link target into `buf`; the answer or -11.
void sceReadlink(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050b3b8
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
    sd(s1, sp, 0x50);
    sd(s5, sp, 0x90);
    s1 = a0;
    sd(s0, sp, 0x40);
    s5 = a1;
    sd(fp, sp, 0xC0);
    s0 = a2;
    sd(s2, sp, 0x60);
    a0 = 17;
    sd(ra, sp, 0xD0);
    fp = 0x970000;
    sd(s7, sp, 0xB0);
    s2 = addiu(fp, -0x7B00);
    sd(s6, sp, 0xA0);
    sd(s4, sp, 0x80);
    link(ctx, 0x50B3F8u);  // $ra first: the delay slot below depends on it
    sd(s3, sp, 0x70);
    call(ctx, gen::fn__sceFsWaitS_00508048);
    v1 = 0x780000;
    lw(v0, v1, -2756);  // 0x77F53C
    if (v0 != 0) {
        lbu(v0, s1, 0);
    } else {
        // 0x0050b410
        charge(ctx, 3);
        jal(ctx, 0x50B410u, gen::fn_sceFsInit_00508170);
        lbu(v0, s1, 0);
    }
    // 0x0050b41c
    charge(ctx, 4);
    a1 = 0;
    v1 = sll(v0, 24);
    sb(v0, s2, 20);
    if (v1 == 0) {
        // 0x0050b474
        charge(ctx, 5);
        a2 = sltiu(s0, 1024);
        s6 = 0x7C0000;
        s3 = addiu(sp, 0x30);
        s7 = 0x970000;
        s4 = 0x970000;
    L_0050b488:
        charge(ctx, 1);
        v0 = 1024;
    } else {
        // 0x0050b42c
        charge(ctx, 7);
        a2 = sltiu(s0, 1024);
        s6 = 0x7C0000;
        s3 = addiu(sp, 0x30);
        s7 = 0x970000;
        s4 = 0x970000;
        a1 = addiu(a1, 1);
        for (;;) {
            // 0x0050b448
            charge(ctx, 3);
            v0 = slti(a1, 1024);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = addu(s1, a1);
            if (cc) {
                goto L_0050b488;
            }
            // 0x0050b454
            charge(ctx, 6);
            a0 = addu(s2, a1);
            lbu(v1, v0, 0);
            sb(v1, a0, 20);
            v1 = sll(v1, 24);
            if (v1 == 0) {
                break;
            }
            a1 = addiu(a1, 1);
            backedge(ctx);
        }
        // 0x0050b46c
        charge(ctx, 2);
        v0 = 1024;
    }
    // 0x0050b48c
    charge(ctx, 2);
    if (a1 == v0) {
        sb(zero, s2, 1043);
    }
    // 0x0050b494
    charge(ctx, 33);
    v0 = 1023;
    a0 = s5;
    if (a2 == 0) s0 = v0;
    sw(s5, s2, 16);
    a1 = s0;
    link(ctx, 0x50B4A8u);  // $ra first: the delay slot below depends on it
    sw(s0, s2, 12);
    call(ctx, gen::fn_sub_5067F8_005067f8);
    s0 = addiu(s4, -28352);
    v1 = addiu(s6, -8232);
    v0 = 1;
    sw(v0, sp, 0x14);
    a0 = addiu(sp, 0x10);
    sw(v1, sp, 0x24);
    link(ctx, 0x50B4C8u);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0x18);
    call(ctx, gen::fn__sceCreateSema_00503160);
    s1 = v0;
    sw(s3, s2, 4);
    v0 = 4;
    sw(s1, s2, 0);
    sw(v0, s2, 8);
    a0 = addiu(s7, -25600);
    a3 = addiu(fp, -0x7B00);
    a1 = 25;
    sw(zero, sp, 0x0);
    a2 = 0;
    sw(zero, sp, 0x8);
    t0 = 2060;
    t1 = s0;
    t2 = 4;
    t3 = 0;
    jal(ctx, 0x50B508u, gen::fn_sceFsSifCallRpc_00507ad8);
    cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
    v0 = 0x20000000;
    if (cc) {
        // 0x0050b530
        charge(ctx, 5);
        v0 = s0 | v0;
        link(ctx, 0x50B534u);  // $ra first: the delay slot below depends on it
        lw(s0, v0, 0);
        call(ctx, gen::fn__sceFsSigSema_00508078);
        if (s0 != 0) {
            // 0x0050b554
            charge(ctx, 5);
            a0 = s1;
            jal(ctx, 0x50B554u, gen::fn__sceWaitSema_005031a0);
            a0 = s1;
            jal(ctx, 0x50B55Cu, gen::fn__sceDeleteSema_00503170);
            lw(v0, sp, 0x30);
        } else {
            // 0x0050b544
            charge(ctx, 4);
            a0 = s1;
            jal(ctx, 0x50B544u, gen::fn__sceDeleteSema_00503170);
            v0 = si(-11);
        }
    } else {
        // 0x0050b518
        charge(ctx, 6);
        a0 = s1;
        jal(ctx, 0x50B518u, gen::fn__sceDeleteSema_00503170);
        jal(ctx, 0x50B520u, gen::fn__sceFsSigSema_00508078);
        v0 = si(-11);
    }
    // 0x0050b568 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xE0);
}

// 0x0050B7A8 sceSifLoadIopHeap -- 240 bytes; frame 0x30: ra sp+0x20, s0 sp+0x10
// sceSifLoadIopHeap(path, iop_addr) (IOP heap RPC 3): the path (at most 251 characters) and the address into the
// request 0x969DC0, then the answer word 0x969D40; 0 before the heap RPC is bound (0x77F558 < 0), -1 when the call
// fails.
void sceSifLoadIopHeap(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050b7a8
    enter(ctx, 7);  // entry check point + this block's cycles
    v0 = 0x780000;
    sp = addiu(sp, -0x30);
    lw(v1, v0, -2728);  // 0x77F558
    a2 = a0;
    sd(ra, sp, 0x20);
    sd(s0, sp, 0x10);
    if (i64(v1) >= 0) {
        // 0x0050b7cc
        charge(ctx, 7);
        lbu(v0, a2, 0);
        a3 = 0x970000;
        v1 = addiu(a3, -25152);  // &0x969DC0
        sb(v0, v1, 4);  // 0x969DC4
        v0 = sll(v0, 24);
        t0 = 0;
        if (v0 == 0) {
            // 0x0050b828
            charge(ctx, 2);
            t1 = 0x970000;
            s0 = 0x970000;
        L_0050b830:
            charge(ctx, 1);
            v0 = 252;
        } else {
            // 0x0050b7e8
            charge(ctx, 4);
            t1 = 0x970000;
            s0 = 0x970000;
            t0 = addiu(t0, 1);
            for (;;) {
                // 0x0050b7f8
                charge(ctx, 3);
                v0 = slti(t0, 252);
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = addu(a2, t0);
                if (cc) {
                    goto L_0050b830;
                }
                // 0x0050b804
                charge(ctx, 7);
                v1 = addiu(a3, -25152);
                lbu(a0, v0, 0);
                v1 = addu(v1, t0);
                sb(a0, v1, 4);
                a0 = sll(a0, 24);
                if (a0 == 0) {
                    break;
                }
                t0 = addiu(t0, 1);
                backedge(ctx);
            }
            // 0x0050b820
            charge(ctx, 2);
            v0 = 252;
        }
        // 0x0050b834
        charge(ctx, 2);
        if (t0 != v0) {
            sw(a1, a3, -25152);
        } else {
            // 0x0050b83c
            charge(ctx, 4);
            v0 = addiu(a3, -25152);
            t0 = 251;
            sb(zero, v0, 255);
            sw(a1, a3, -25152);
        }
        // 0x0050b84c
        charge(ctx, 14);
        v0 = addiu(a3, -25152);
        a0 = addiu(t1, -25344);
        sb(zero, v0, 255);
        a3 = v0;
        t0 = addiu(t0, 5);
        sw(zero, sp, 0x0);
        a1 = 3;
        a2 = 0;
        t1 = addiu(s0, -25280);
        t2 = 4;
        t3 = 0;
        jal(ctx, 0x50B874u, gen::fn_sceSifCallRpc_00507230);
        cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
        lw(v0, s0, -25280);
        if (!cc) {
            // 0x0050b884
            charge(ctx, 1);
            v0 = si(-1);
        }
    } else {
        // 0x0050b7c4
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0050b888 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x30);
}

// 0x0050B898 sceSifQueryMemSize -- 112 bytes; frame 0x30: ra sp+0x20, s0 sp+0x10
// sceSifQueryMemSize() (IOP heap RPC 5): the IOP memory size, 0 before the heap RPC is bound, -1 when the call fails.
void sceSifQueryMemSize(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050b898
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x780000;
    sp = addiu(sp, -0x30);
    lw(v1, v0, -2728);  // 0x77F558
    sd(ra, sp, 0x20);
    sd(s0, sp, 0x10);
    if (i64(v1) >= 0) {
        // 0x0050b8b8
        charge(ctx, 14);
        a0 = 0x970000;
        s0 = 0x970000;
        a0 = addiu(a0, -25344);  // &heap_rpc_cd
        sw(zero, sp, 0x0);
        a1 = 5;
        a2 = 0;
        a3 = 0;
        t0 = 0;
        t1 = addiu(s0, -25280);  // &0x969D40
        t2 = 4;
        t3 = 0;
        jal(ctx, 0x50B8E0u, gen::fn_sceSifCallRpc_00507230);
        if (i64(v0) >= 0) {
            lw(v0, s0, -25280);  // 0x969D40
        } else {
            // 0x0050b8f0
            charge(ctx, 2);
            v0 = lui(0xFFFF);
            v0 = v0 | 0xFFFF;
        }
    } else {
        // 0x0050b8b0
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0050b8f8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x30);
}

// 0x0050B908 sceSifQueryMaxFreeMemSize -- 112 bytes; frame 0x30: ra sp+0x20, s0 sp+0x10
// sceSifQueryMaxFreeMemSize() (IOP heap RPC 6): the largest free IOP block, 0 before the heap RPC is bound, -1 when
// the call fails.
void sceSifQueryMaxFreeMemSize(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050b908
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x780000;
    sp = addiu(sp, -0x30);
    lw(v1, v0, -2728);  // 0x77F558
    sd(ra, sp, 0x20);
    sd(s0, sp, 0x10);
    if (i64(v1) >= 0) {
        // 0x0050b928
        charge(ctx, 14);
        a0 = 0x970000;
        s0 = 0x970000;
        a0 = addiu(a0, -25344);  // &heap_rpc_cd
        sw(zero, sp, 0x0);
        a1 = 6;
        a2 = 0;
        a3 = 0;
        t0 = 0;
        t1 = addiu(s0, -25280);  // &0x969D40
        t2 = 4;
        t3 = 0;
        jal(ctx, 0x50B950u, gen::fn_sceSifCallRpc_00507230);
        if (i64(v0) >= 0) {
            lw(v0, s0, -25280);  // 0x969D40
        } else {
            // 0x0050b960
            charge(ctx, 2);
            v0 = lui(0xFFFF);
            v0 = v0 | 0xFFFF;
        }
    } else {
        // 0x0050b920
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0050b968 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x30);
}

// 0x0050CE40 InitTLB32MB -- 500 bytes; frame 0x40: s2 sp+0x20, s1 sp+0x10, s0 sp+0x0, ra sp+0x30
// InitTLB32MB(): prints the TLB layout, clears Wired, then writes the three TLB entry tables of the descriptor at
// 0x77FB98 (kernel / default / extended counts and table pointers) through _sce_SetTLBEntry, Exit(1) when an index
// passes 48, sets Wired and fills the rest with invalid entries at 0xE0000000 + 8 KiB steps; returns the first free
// index << 13.
void InitTLB32MB(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, t9{ctx, 25}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0050ce40
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    a0 = 0x7C0000;
    sd(s2, sp, 0x20);
    a0 = addiu(a0, -8144);  // "# TLB spad=0 kernel=1:%d default=%d:%d extended=%d:%d\n"
    sd(s1, sp, 0x10);
    s2 = 0x780000;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x30);
    s0 = addiu(s2, -1128);  // &0x77FB98
    lw(a1, s2, -1128);  // 0x77FB98
    lw(a3, s0, 4);  // 0x77FB9C
    lw(t1, s0, 8);  // 0x77FBA0
    a2 = a1;
    a3 = addu(a1, a3);
    t1 = addu(a3, t1);
    t0 = a3;
    a1 = addiu(a1, -1);
    t1 = addiu(t1, -1);
    a3 = addiu(a3, -1);
    jal(ctx, 0x50CE88u, gen::fn_kprintf_00505ec8);
    mtc0(zero, 6);
    sync(ctx, 16);
    lw(s1, s2, -1128);  // 0x77FB98
    v0 = slti(s1, 49);
    t9 = 0;
    if (v0 == 0) {
        // 0x0050cea8
        charge(ctx, 5);
        a0 = 0x7C0000;
        a0 = addiu(a0, -8088);  // "# TLB over flow (1)"
        jal(ctx, 0x50CEACu, gen::fn_kprintf_00505ec8);
        a0 = 1;
        jal(ctx, 0x50CEB4u, gen::fn_Exit_0050da58);
    }
    // 0x0050cebc
    charge(ctx, 3);
    v0 = slt(t9, s1);
    lw(s0, s0, 16);
    if (v0 != 0) {
        // 0x0050cec8
        charge(ctx, 2);
        lw(a1, s0, 0);
        for (;;) {
            // 0x0050ced0
            charge(ctx, 10);
            a0 = t9;
            lw(a2, s0, 4);
            lw(a3, s0, 8);
            lw(t0, s0, 12);
            s0 = addiu(s0, 16);
            jal(ctx, 0x50CEE0u, gen::fn__sce_SetTLBEntry_0050cd60);
            t9 = addiu(t9, 1);
            v0 = slt(t9, s1);
            if (v0 == 0) {
                break;
            }
            lw(a1, s0, 0);
            backedge(ctx);
        }
    }
    // 0x0050cef8
    charge(ctx, 6);
    s0 = addiu(s2, -1128);
    lw(v0, s0, 4);
    s1 = addu(t9, v0);
    v1 = slti(s1, 49);
    v0 = slt(t9, s1);
    if (v1 == 0) {
        // 0x0050cf10
        charge(ctx, 6);
        a0 = 0x7C0000;
        a0 = addiu(a0, -8064);  // "# TLB over flow (2)"
        jal(ctx, 0x50CF14u, gen::fn_kprintf_00505ec8);
        a0 = 1;
        jal(ctx, 0x50CF1Cu, gen::fn_Exit_0050da58);
        v0 = slt(t9, s1);
    }
    // 0x0050cf28
    charge(ctx, 2);
    lw(s0, s0, 20);
    if (v0 != 0) {
        // 0x0050cf30
        charge(ctx, 2);
        lw(a1, s0, 0);
        for (;;) {
            // 0x0050cf38
            charge(ctx, 10);
            a0 = t9;
            lw(a2, s0, 4);
            lw(a3, s0, 8);
            lw(t0, s0, 12);
            s0 = addiu(s0, 16);
            jal(ctx, 0x50CF48u, gen::fn__sce_SetTLBEntry_0050cd60);
            t9 = addiu(t9, 1);
            v0 = slt(t9, s1);
            if (v0 == 0) {
                break;
            }
            lw(a1, s0, 0);
            backedge(ctx);
        }
    }
    // 0x0050cf60
    charge(ctx, 7);
    s0 = addiu(s2, -1128);
    sw(t9, s0, 12);
    mtc0(t9, 6);
    sync(ctx, 16);
    lw(v0, s0, 8);
    if (i64(v0) <= 0) {
        s0 = t9;
    } else {
        // 0x0050cf7c
        charge(ctx, 4);
        s1 = addu(t9, v0);
        v0 = slti(s1, 49);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = slt(t9, s1);
        if (!cc) {
            // 0x0050cf8c
            charge(ctx, 6);
            a0 = 0x7C0000;
            a0 = addiu(a0, -8040);  // "# TLB over flow (3)"
            jal(ctx, 0x50CF90u, gen::fn_kprintf_00505ec8);
            a0 = 1;
            jal(ctx, 0x50CF98u, gen::fn_Exit_0050da58);
            v0 = slt(t9, s1);
        }
        // 0x0050cfa4
        charge(ctx, 2);
        lw(s0, s0, 24);
        if (v0 != 0) {
            // 0x0050cfac
            charge(ctx, 1);
            lw(a1, s0, 0);
            for (;;) {
                // 0x0050cfb0
                charge(ctx, 10);
                a0 = t9;
                lw(a2, s0, 4);
                lw(a3, s0, 8);
                lw(t0, s0, 12);
                s0 = addiu(s0, 16);
                jal(ctx, 0x50CFC0u, gen::fn__sce_SetTLBEntry_0050cd60);
                t9 = addiu(t9, 1);
                v0 = slt(t9, s1);
                if (v0 == 0) {
                    break;
                }
                lw(a1, s0, 0);
                backedge(ctx);
            }
        }
        // 0x0050cfd8
        charge(ctx, 1);
        s0 = t9;
    }
    // 0x0050cfdc
    charge(ctx, 3);
    v0 = slti(s0, 48);
    t9 = sll(t9, 13);
    if (v0 != 0) {
        // 0x0050cfe8
        charge(ctx, 2);
        v0 = lui(0xE000);
        s1 = addu(t9, v0);
        for (;;) {
            // 0x0050cff0
            charge(ctx, 10);
            a0 = s0;
            a2 = s1;
            a1 = 0;
            a3 = 0;
            t0 = 0;
            s0 = addiu(s0, 1);
            jal(ctx, 0x50D004u, gen::fn__sce_SetTLBEntry_0050cd60);
            v0 = slti(s0, 48);
            s1 = addiu(s1, 8192);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0050d018 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    v0 = t9;
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0050D040 _kTLBException -- 256 bytes; leaf frame (no stack)
// The TLB-miss exception handler: saves every GPR (128-bit) to the frame 0x96B180, reads Status / Cause / EPC /
// BadVAddr, keeps EPC at 0x96B3A8, points EPC at _xlaunch, clears EXL and `eret`s into it.
void _kTLBException(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, k0{ctx, 26}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x0050d040
    enter(ctx, 64);  // entry check point + this block's cycles
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
    t0 = 0x970000;
    t0 = addiu(t0, -20096);  // &0x96B180
    at = 0x970000;
    sw(a2, at, -19544);  // 0x96B3A8
    at = 0x510000;
    at = addiu(at, -11968);  // &_xlaunch
    mtc0(at, 14);
    sync(ctx, 16);
    mfc0(at, 12);
    v0 = si(-2);
    at = at & v0;
    mtc0(at, 12);
    sync(ctx, 16);
    rt::eret(ctx, 0x50D13Cu);
}

// 0x0050D140 _xlaunch -- 308 bytes; frame 0x4E80
// Where _kTLBException returns to: calls the user TLB handler (0x77F898) on a private stack, makes kernel call -84,
// restores EPC, HI/LO and every GPR from 0x96B180, sets EXL and `eret`s to the faulting instruction.
void _xlaunch(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, k0{ctx, 26}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x0050d140
    enter(ctx, 77);  // entry check point + this block's cycles
    at = 0x780000;
    lw(at, at, -1896);  // 0x77F898
    sp = 0x970000;
    sp = addiu(sp, -0x4E80);
    jalr(ctx, 0x50D14Cu, at.u());
    v1 = si(-84);
    syscall(ctx, 0x50D158u);
    mfc0(at, 12);
    k0 = si(-28);
    at = at & k0;
    mtc0(at, 12);
    sync(ctx, 16);
    v0 = 0x970000;
    lw(v0, v0, -19544);  // 0x96B3A8
    mtc0(v0, 14);
    sync(ctx, 16);
    v0 = 0x970000;
    ld(v0, v0, -19584);  // 0x96B380
    mthi(v0);
    v0 = 0x970000;
    ld(v0, v0, -19576);  // 0x96B388
    mthi1(v0);
    v0 = 0x970000;
    ld(v0, v0, -19568);  // 0x96B390
    mtlo(v0);
    v0 = 0x970000;
    ld(v0, v0, -19560);  // 0x96B398
    mtlo1(v0);
    v0 = 0x970000;
    ld(v0, v0, -19552);  // 0x96B3A0
    mtsa(v0);
    sync(ctx, 16);
    k0 = 0x970000;
    k0 = addiu(k0, -20096);  // &0x96B180
    lq(at, k0, 16);  // 0x96B190
    lq(v0, k0, 32);  // 0x96B1A0
    lq(v1, k0, 48);  // 0x96B1B0
    lq(a0, k0, 64);  // 0x96B1C0
    lq(a1, k0, 80);  // 0x96B1D0
    lq(a2, k0, 96);  // 0x96B1E0
    lq(a3, k0, 112);  // 0x96B1F0
    lq(t0, k0, 128);  // 0x96B200
    lq(t1, k0, 144);  // 0x96B210
    lq(t2, k0, 160);  // 0x96B220
    lq(t3, k0, 176);  // 0x96B230
    lq(t4, k0, 192);  // 0x96B240
    lq(t5, k0, 208);  // 0x96B250
    lq(t6, k0, 224);  // 0x96B260
    lq(t7, k0, 240);  // 0x96B270
    lq(s0, k0, 256);  // 0x96B280
    lq(s1, k0, 272);  // 0x96B290
    lq(s2, k0, 288);  // 0x96B2A0
    lq(s3, k0, 304);  // 0x96B2B0
    lq(s4, k0, 320);  // 0x96B2C0
    lq(s5, k0, 336);  // 0x96B2D0
    lq(s6, k0, 352);  // 0x96B2E0
    lq(s7, k0, 368);  // 0x96B2F0
    lq(t8, k0, 384);  // 0x96B300
    lq(t9, k0, 400);  // 0x96B310
    lq(gp, k0, 448);  // 0x96B340
    lq(sp, k0, 464);  // 0x96B350
    lq(fp, k0, 480);  // 0x96B360
    lq(ra, k0, 496);  // 0x96B370
    mfc0(k0, 12);
    k0 = k0 | 0x13;
    mtc0(k0, 12);
    sync(ctx, 16);
    rt::eret(ctx, 0x50D270u);
}

// 0x0050D478 _sceCopy_0 -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 90, `syscall`, the kernel's $v0 returned. the kernel copy call (kernel call 90; the C
// runtime's copy of the kernel patch path).
void _sceCopy_0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x0050d478
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 90;
    syscall(ctx, 0x50D47Cu);
}

// 0x0050D6B0 _sceSetSyscall_1 -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 116, `syscall`, the kernel's $v0 returned. SetSyscall(n, fn) (kernel call 116).
void _sceSetSyscall_1(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x0050d6b0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 116;
    syscall(ctx, 0x50D6B4u);
}

// 0x0050D6C0 _sceCopy_1 -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 90, `syscall`, the kernel's $v0 returned. the kernel copy call (kernel call 90), second
// copy.
void _sceCopy_1(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x0050d6c0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 90;
    syscall(ctx, 0x50D6C4u);
}

// 0x0050D708 _sceGetEntryAddress_0 -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 91, `syscall`, the kernel's $v0 returned. GetEntryAddress(n) (kernel call 91).
void _sceGetEntryAddress_0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x0050d708
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 91;
    syscall(ctx, 0x50D70Cu);
}

// 0x0050D830 _sceCopy_2 -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 90, `syscall`, the kernel's $v0 returned. the kernel copy call (kernel call 90), third
// copy.
void _sceCopy_2(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x0050d830
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 90;
    syscall(ctx, 0x50D834u);
}

// 0x0050D870 _sceSetSyscall_2 -- 16 bytes; leaf frame (no stack)
// Kernel call wrapper: $v1 = 116, `syscall`, the kernel's $v0 returned. SetSyscall(n, fn) (kernel call 116), second
// copy.
void _sceSetSyscall_2(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3};
    // 0x0050d870
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 116;
    syscall(ctx, 0x50D874u);
}

// 0x0050FA48 cdvd_exit -- 160 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0
// The CD/DVD library's exit: cancels a pending callback (sceCdCbfunc_num = -1, signal its semaphore), deletes the
// four library semaphores and sends SIF command 0x80000012 with interrupts off.
void cdvd_exit(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0050fa48
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x780000;
    sp = addiu(sp, -0x20);
    lw(v1, v0, 2964);  // 0x780B94
    sd(ra, sp, 0x10);
    sd(s0, sp, 0x0);
    if (v1 == 0) {
        // 0x0050fa80
        charge(ctx, 2);
        s0 = 0x780000;
        v0 = 0x780000;
    } else {
        // 0x0050fa60
        charge(ctx, 8);
        v1 = 0x780000;
        v0 = si(-1);
        sw(v0, v1, 3040);  // sceCdCbfunc_num
        s0 = 0x780000;
        link(ctx, 0x50FA70u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 2976);  // 0x780BA0
        call(ctx, gen::fn__sceSignalSema_00503180);
        v0 = 0x780000;
    }
    // 0x0050fa88
    charge(ctx, 18);
    link(ctx, 0x50FA88u);  // $ra first: the delay slot below depends on it
    lw(a0, v0, 2984);
    call(ctx, gen::fn__sceDeleteSema_00503170);
    v1 = 0x780000;
    link(ctx, 0x50FA94u);  // $ra first: the delay slot below depends on it
    lw(a0, v1, 2988);
    call(ctx, gen::fn__sceDeleteSema_00503170);
    v1 = 0x780000;
    link(ctx, 0x50FAA0u);  // $ra first: the delay slot below depends on it
    lw(a0, v1, 2992);
    call(ctx, gen::fn__sceDeleteSema_00503170);
    link(ctx, 0x50FAA8u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 2976);
    call(ctx, gen::fn__sceDeleteSema_00503170);
    jal(ctx, 0x50FAB0u, gen::fn_DIntr_0050d3a0);
    a0 = lui(0x8000);
    s0 = v0;
    a0 = a0 | 0x12;
    jal(ctx, 0x50FAC0u, gen::fn_sceSifSendCmd_005064a8);
    ld(ra, sp, 0x10);
    if (s0 == 0) {
        // 0x0050fadc
        charge(ctx, 3);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0050fad0
    charge(ctx, 3);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
    gen::fn_EIntr_0050d3f0(ctx);  // tail call
}

// 0x00510748 sceCdDiskReady_old -- 536 bytes; frame 0xA0: s6 sp+0x70, s2 sp+0x30, ra sp+0x90, s7 sp+0x80, s5 sp+0x60, s4 sp+0x50, s3 sp+0x40, s1 sp+0x20, s0 sp+0x10
// The old sceCdDiskReady(mode) through RPC 0x8000059A: binds the server once (retrying with a spin), sends `mode` and
// returns the drive state word; 6 when the command semaphore is busy (-1 for mode 8).
void sceCdDiskReady_old(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00510748
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(s6, sp, 0x70);
    s6 = 0x780000;
    sd(s2, sp, 0x30);
    lw(v0, s6, 2960);  // 0x780B90
    s2 = a0;
    sd(ra, sp, 0x90);
    sd(s7, sp, 0x80);
    sd(s5, sp, 0x60);
    sd(s4, sp, 0x50);
    sd(s3, sp, 0x40);
    sd(s1, sp, 0x20);
    sd(s0, sp, 0x10);
    if (i64(v0) > 0) {
        // 0x00510780
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, -7520);  // "OLD DiskReady Call\n"
        jal(ctx, 0x510784u, gen::fn_scePrintf_00505e48);
    }
    // 0x0051078c
    charge(ctx, 6);
    jal(ctx, 0x51078Cu, gen::fn_DIntr_0050d3a0);
    a0 = 0x780000;
    v1 = 1;
    sw(v1, a0, 3008);  // 0x780BC0
    if (v0 != 0) {
        // 0x005107a4
        charge(ctx, 2);
        jal(ctx, 0x5107A4u, gen::fn_EIntr_0050d3f0);
    }
    // 0x005107ac
    charge(ctx, 8);
    s3 = 0x780000;
    jal(ctx, 0x5107ACu, gen::fn_cmd_sem_init_0050f960);
    lw(a0, s3, 2988);  // 0x780BAC
    jal(ctx, 0x5107B8u, gen::fn__scePollSema_005031b0);
    lw(v1, s3, 2988);  // 0x780BAC
    cc = v1 != v0;  // the condition, before the delay slot changes it
    v0 = 6;
    if (!cc) {
        // 0x005107cc
        charge(ctx, 4);
        a0 = 1;
        jal(ctx, 0x5107CCu, gen::fn_sceCdSyncS_005101e8);
        a0 = 0;
        if (v0 == 0) {
            // 0x005107dc
            charge(ctx, 5);
            s1 = 0x780000;
            jal(ctx, 0x5107DCu, gen::fn_sceSifInitRpc_005068a8);
            lw(v0, s1, 3024);  // 0x780BD0
            s5 = 0x970000;
            if (i64(v0) >= 0) {
                // 0x0051089c
                charge(ctx, 2);
                s4 = 0x970000;
                s7 = 0x780000;
            } else {
                // 0x005107f0
                charge(ctx, 3);
                s4 = 0x970000;
                s7 = 0x780000;
                for (;;) {
                    // 0x00510824
                    charge(ctx, 1);
                    s0 = addiu(s5, -9136);
                    for (;;) {
                        // 0x00510828
                        charge(ctx, 7);
                        a1 = lui(0x8000);
                        a0 = s0;
                        a1 = a1 | 0x59A;
                        a2 = 0;
                        jal(ctx, 0x510834u, gen::fn_sceSifBindRpc_00507050);
                        if (i64(v0) < 0) {
                            // 0x00510844
                            charge(ctx, 3);
                            lw(v0, s6, 2960);
                            cc = i64(v0) <= 0;  // the condition, before the delay slot changes it
                            v0 = 0x100000;
                            if (!cc) {
                                // 0x00510850
                                charge(ctx, 4);
                                a0 = 0x7C0000;
                                a0 = addiu(a0, -7496);  // "Libcdvd bind err CdDiskReady\n"
                                jal(ctx, 0x510854u, gen::fn_scePrintf_00505e48);
                                v0 = 0x100000;
                            }
                            // 0x00510860
                            charge(ctx, 2);
                            v1 = si(-1);
                            for (;;) {
                                // 0x00510868
                                charge(ctx, 7);
                                v0 = addiu(v0, -1);
                                if (v0 == v1) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x00510884
                            charge(ctx, 2);
                            s0 = addiu(s5, -9136);
                            backedge(ctx);
                            continue;
                        }
                        lw(v0, s0, 36);
                        break;
                    }
                    // 0x0051088c
                    charge(ctx, 2);
                    cc = v0 == 0;  // the condition, before the delay slot changes it
                    v0 = 0x100000;
                    if (!cc) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00510800
                    charge(ctx, 2);
                    v1 = si(-1);
                    for (;;) {
                        // 0x00510808
                        charge(ctx, 7);
                        v0 = addiu(v0, -1);
                        if (v0 == v1) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x00510894
                charge(ctx, 2);
                sw(zero, s1, 3024);
            }
            // 0x005108a4
            charge(ctx, 18);
            s0 = addiu(s4, -9072);
            sw(s2, s4, -9072);
            a0 = s0;
            a1 = 4;
            jal(ctx, 0x5108B0u, gen::fn_sub_5067F8_005067f8);
            s1 = addiu(s7, 7552);
            a0 = addiu(s5, -9136);
            a3 = s0;
            sw(zero, sp, 0x0);
            a1 = 0;
            a2 = 0;
            t0 = 4;
            t1 = s1;
            t2 = 4;
            t3 = 0;
            jal(ctx, 0x5108DCu, gen::fn_sceSifCallRpc_00507230);
            if (i64(v0) < 0) {
                goto L_005108ec;
            }
            lw(v0, s6, 2960);
            // 0x0051090c
            charge(ctx, 2);
            a0 = 0x7C0000;
            if (i64(v0) > 0) {
                // 0x00510914
                charge(ctx, 2);
                a0 = addiu(a0, -7464);
                jal(ctx, 0x510914u, gen::fn_scePrintf_00505e48);
            }
            // 0x0051091c
            charge(ctx, 6);
            v0 = 0x20000000;
            lw(a0, s3, 2988);
            v0 = s1 | v0;
            link(ctx, 0x510928u);  // $ra first: the delay slot below depends on it
            lw(s0, v0, 0);
            call(ctx, gen::fn__sceSignalSema_00503180);
            v0 = s0;
            // 0x00510934 (the shared epilogue, written out on this path)
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
    L_005108ec:
        charge(ctx, 8);
        lw(a0, s3, 2988);
        jal(ctx, 0x5108F0u, gen::fn__sceSignalSema_00503180);
        a0 = s2 ^ 0x8;
        v1 = si(-1);
        v0 = 6;
        if (a0 == 0) v0 = v1;
    }
    // 0x00510934 (the shared epilogue, written out on this path)
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

// 0x00510D60 sceCdSeek -- 204 bytes; frame 0x50: s0 sp+0x10, s2 sp+0x30, s1 sp+0x20, ra sp+0x40
// sceCdSeek(lsn) (N-command 9 through RPC 5): stores the LSN, arms the callback (number 4) and sends; 1 when sent, 0
// when the drive is not ready or the command was refused.
void sceCdSeek(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00510d60
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s0, sp, 0x10);
    sd(s2, sp, 0x30);
    s0 = a0;
    sd(s1, sp, 0x20);
    sd(ra, sp, 0x40);
    s1 = 0x780000;
    jal(ctx, 0x510D78u, gen::fn_sceCdNcmdDiskReady_005100b0);
    v1 = 6;
    s2 = addiu(s1, 3200);  // &sceCd_ncmdsdata
    if (v0 != v1) {
        // 0x00510d8c
        charge(ctx, 4);
        a0 = 9;
        jal(ctx, 0x510D8Cu, gen::fn__sceCd_ncmd_prechk_0050ff58);
        a0 = s2;
        if (v0 == 0) {
            goto L_00510e10;
        }
        // 0x00510d9c
        charge(ctx, 24);
        sw(s0, s1, 3200);
        a1 = 4;
        s0 = 0x780000;
        jal(ctx, 0x510DA4u, gen::fn_sub_5067F8_005067f8);
        s1 = 0x780000;
        a1 = addiu(s0, 3040);  // &sceCdCbfunc_num
        v0 = 4;
        sw(v0, s0, 3040);  // sceCdCbfunc_num
        v1 = 1;
        a0 = 0x780000;
        t3 = 0x510000;
        sw(a1, sp, 0x0);
        a0 = addiu(a0, 7504);  // &0x781D50
        sw(v1, s1, 2996);  // sceCd_c_cb_sem
        a3 = s2;
        t3 = addiu(t3, -2408);  // &_sceCd_cd_callback
        a1 = 5;
        a2 = 1;
        t0 = 4;
        t1 = 0;
        t2 = 0;
        jal(ctx, 0x510DECu, gen::fn_sceSifCallRpc_00507230);
        if (i64(v0) < 0) {
            // 0x00510dfc
            charge(ctx, 5);
            sw(zero, s0, 3040);
            v0 = 0x780000;
            sw(zero, s1, 2996);
            link(ctx, 0x510E08u);  // $ra first: the delay slot below depends on it
            lw(a0, v0, 2984);
            call(ctx, gen::fn__sceSignalSema_00503180);
            goto L_00510e10;
        }
        v0 = 1;
        // 0x00510e14 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x40);
        ld(s2, sp, 0x30);
        ld(s1, sp, 0x20);
        ld(s0, sp, 0x10);
        sp = addiu(sp, 0x50);
        return;
    }
L_00510e10:
    charge(ctx, 1);
    v0 = 0;
    // 0x00510e14 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x40);
    ld(s2, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x50);
}

// 0x00510F88 sceCdBreak -- 184 bytes; frame 0x40: ra sp+0x30, s1 sp+0x20, s0 sp+0x10
// sceCdBreak() (S-command 30 through RPC 22): sends the break and returns the IOP's answer word, 0 when refused.
void sceCdBreak(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00510f88
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    a0 = 30;
    sd(ra, sp, 0x30);
    sd(s1, sp, 0x20);
    link(ctx, 0x510F98u);  // $ra first: the delay slot below depends on it
    sd(s0, sp, 0x10);
    call(ctx, gen::fn__sceCd_scmd_prechk_00510258);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = 0x780000;
    if (cc) {
        // 0x00510fb0
        charge(ctx, 17);
        s0 = 0x780000;
        s1 = addiu(v0, 7552);
        v1 = 8;
        a0 = 0x780000;
        sw(v1, s0, 3040);  // sceCdCbfunc_num
        a0 = addiu(a0, 9984);  // &0x782700
        sw(zero, sp, 0x0);
        a1 = 22;
        a2 = 0;
        a3 = 0;
        t0 = 0;
        t1 = s1;
        t2 = 4;
        t3 = 0;
        jal(ctx, 0x510FE4u, gen::fn_sceSifCallRpc_00507230);
        cc = i64(v0) >= 0;  // the condition, before the delay slot changes it
        v0 = 0x780000;
        if (cc) {
            // 0x0051100c
            charge(ctx, 8);
            sw(zero, s0, 3040);
            v1 = 0x780000;
            v0 = 0x20000000;
            v0 = s1 | v0;
            lw(a0, v1, 2988);  // 0x780BAC
            link(ctx, 0x511020u);  // $ra first: the delay slot below depends on it
            lw(s0, v0, 0);
            call(ctx, gen::fn__sceSignalSema_00503180);
            v0 = s0;
        } else {
            // 0x00510ff4
            charge(ctx, 6);
            lw(a0, v0, 2988);
            jal(ctx, 0x510FF8u, gen::fn__sceSignalSema_00503180);
            sw(zero, s0, 3040);
            v0 = 0;
        }
    } else {
        // 0x00510fa8
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0051102c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x40);
}

// 0x00511288 _pad_intr_hdr -- 72 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0
// The pad DMA interrupt handler: calls the registered callback (0x782750) with the handler argument's word +12 under
// the pad library's $gp (0x96DF80), then `sync` + `ei`.
void _pad_intr_hdr(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00511288
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x780000;
    sp = addiu(sp, -0x20);
    lw(v1, v0, 10064);  // 0x782750
    sd(ra, sp, 0x10);
    sd(s0, sp, 0x0);
    if (v1 != 0) {
        // 0x005112a0
        charge(ctx, 6);
        v0 = 0x970000;
        s0 = gp;
        lw(gp, v0, -8320);  // 0x96DF80
        jt = v1.u();  // the target, read before the delay slot
        link(ctx, 0x5112ACu);  // $ra = the return address
        lw(a0, a0, 12);
        call_ptr(ctx, jt);
        gp = s0;
    }
    // 0x005112b8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    sync(ctx, 0);
    ei(ctx);
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00512710 scePadSetDmaCallback -- 292 bytes; frame 0x80: s2 sp+0x30, s4 sp+0x50, s1 sp+0x20, ra sp+0x70, s5 sp+0x60, s3 sp+0x40, s0 sp+0x10
// scePadSetDmaCallback(fn): installs (or with 0 removes) the pad DMA callback, telling the IOP pad server through RPC
// 1 when the state changes; returns the previous callback.
void scePadSetDmaCallback(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00512710
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(s2, sp, 0x30);
    sd(s4, sp, 0x50);
    s2 = 0x780000;
    sd(s1, sp, 0x20);
    s4 = a0;
    sd(ra, sp, 0x70);
    sd(s5, sp, 0x60);
    sd(s3, sp, 0x40);
    sd(s0, sp, 0x10);
    lw(s1, s2, 10064);  // 0x782750
    if (s4 != 0) {
        // 0x00512794
        charge(ctx, 2);
        s5 = 0x970000;
        if (s1 == 0) {
            // 0x0051279c
            charge(ctx, 9);
            v0 = 0x970000;
            v1 = 24;
            sw(v1, v0, -8448);  // pad_rpc_buf
            s0 = addiu(v0, -8448);  // &pad_rpc_buf
            v1 = 1;
            s3 = 0x970000;
            sw(v1, s0, 4);  // pad_rpc_buf+0x4
            sw(zero, sp, 0x0);
            for (;;) {
                // 0x005127c0
                charge(ctx, 11);
                a0 = addiu(s3, -9024);
                a1 = 1;
                a2 = 0;
                a3 = s0;
                t0 = 128;
                t1 = s0;
                t2 = 128;
                t3 = 0;
                jal(ctx, 0x5127DCu, gen::fn_sceSifCallRpc_00507230);
                if (i64(v0) >= 0) {
                    break;
                }
                sw(zero, sp, 0x0);
                backedge(ctx);
            }
        }
        // 0x005127ec
        charge(ctx, 6);
        jal(ctx, 0x5127ECu, gen::fn_DIntr_0050d3a0);
        sw(gp, s5, -8320);
        v1 = 1;
        sw(s4, s2, 10064);
        if (v0 == v1) {
            // 0x00512804
            charge(ctx, 2);
            jal(ctx, 0x512804u, gen::fn_EIntr_0050d3f0);
        }
        // 0x0051280c
        charge(ctx, 1);
        v0 = s1;
    } else {
        // 0x00512740
        charge(ctx, 8);
        v1 = 0x970000;
        v0 = 24;
        sw(v0, v1, -8448);  // pad_rpc_buf
        s0 = addiu(v1, -8448);  // &pad_rpc_buf
        sw(zero, s2, 10064);
        s3 = 0x970000;
        sw(zero, s0, 4);  // pad_rpc_buf+0x4
        sw(zero, sp, 0x0);
        for (;;) {
            // 0x00512760
            charge(ctx, 11);
            a0 = addiu(s3, -9024);
            a1 = 1;
            a2 = 0;
            a3 = s0;
            t0 = 128;
            t1 = s0;
            t2 = 128;
            t3 = 0;
            jal(ctx, 0x51277Cu, gen::fn_sceSifCallRpc_00507230);
            if (i64(v0) >= 0) {
                break;
            }
            sw(zero, sp, 0x0);
            backedge(ctx);
        }
        // 0x0051278c
        charge(ctx, 2);
        v0 = s1;
    }
    // 0x00512810 (the shared epilogue, written out on this path)
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

// 0x00512E48 sceSdRemoteCallbackQuit -- 312 bytes; frame 0x50: s3 sp+0x30, ra sp+0x40, s2 sp+0x20, s1 sp+0x10, s0 sp+0x0
// sceSdRemoteCallbackQuit(): stops the sound-library callback server: four sceSdRemote calls, clears the callback
// table 0x7827A0..0x7827C0, removes the RPC server and its queue and terminates / deletes its thread (0x7827C4, then
// -1); 0, or -1 on any failure.
void sceSdRemoteCallbackQuit(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00512e48
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s3, sp, 0x30);
    s3 = 0x780000;
    sd(ra, sp, 0x40);
    lw(v0, s3, 10180);  // 0x7827C4
    sd(s2, sp, 0x20);
    sd(s1, sp, 0x10);
    sd(s0, sp, 0x0);
    if (i64(v0) >= 0) {
        // 0x00512e74
        charge(ctx, 60);
        a0 = 1;
        a1 = 0x8170;
        a2 = 0;
        a3 = 0;
        jal(ctx, 0x512E80u, gen::fn_sceSdRemote_005129c0);
        s1 = si(-1);
        a0 = 1;
        a1 = 0x8160;
        a2 = 0;
        a3 = 0;
        t0 = 0;
        s0 = 0;
        jal(ctx, 0x512EA0u, gen::fn_sceSdRemote_005129c0);
        a0 = 1;
        a1 = 0x8160;
        a2 = 1;
        a3 = 0;
        t0 = 0;
        jal(ctx, 0x512EB8u, gen::fn_sceSdRemote_005129c0);
        a0 = 1;
        a1 = 0xE630;
        jal(ctx, 0x512EC4u, gen::fn_sceSdRemote_005129c0);
        s2 = 0x970000;
        v0 = 0x780000;
        s2 = addiu(s2, -3904);  // &0x96F0C0
        v1 = 0x780000;
        a2 = 0x780000;
        a3 = 0x780000;
        t0 = 0x780000;
        t1 = 0x780000;
        t2 = 0x780000;
        t3 = 0x780000;
        t4 = 0x780000;
        a0 = 0x970000;
        sw(zero, v0, 10144);  // 0x7827A0
        a0 = addiu(a0, -3880);  // &0x96F0D8
        sw(zero, v1, 10148);  // 0x7827A4
        a1 = s2;
        sw(zero, a2, 10152);  // 0x7827A8
        sw(zero, a3, 10156);  // 0x7827AC
        sw(zero, t0, 10160);  // 0x7827B0
        sw(zero, t1, 10164);  // 0x7827B4
        sw(zero, t2, 10168);  // 0x7827B8
        sw(zero, t3, 10172);  // 0x7827BC
        link(ctx, 0x512F24u);  // $ra first: the delay slot below depends on it
        sw(zero, t4, 10176);
        call(ctx, gen::fn_sceSifRemoveRpc_005075d8);
        if (v0 == 0) s0 = s1;
        a0 = s2;
        jal(ctx, 0x512F30u, gen::fn_sceSifRemoveRpcQueue_00507670);
        lw(a0, s3, 10180);
        if (v0 == 0) s0 = s1;
        jal(ctx, 0x512F3Cu, gen::fn__sceTerminateThread_00502fb0);
        v0 = slt(s1, v0);
        lw(a0, s3, 10180);
        if (v0 == 0) s0 = s1;
        jal(ctx, 0x512F4Cu, gen::fn__sceDeleteThread_00502f70);
        v0 = slt(s1, v0);
        sw(s1, s3, 10180);
        if (v0 != 0) s1 = s0;
        v0 = s1;
    } else {
        // 0x00512e6c
        charge(ctx, 2);
        v0 = si(-1);
    }
    // 0x00512f64 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    ld(s3, sp, 0x30);
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x10);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0051CDD8 sceDbcSearchPortSpecific -- 192 bytes; frame 0x50: s2 sp+0x30, s0 sp+0x10, s1 sp+0x20, ra sp+0x40
// sceDbcSearchPortSpecific(req) (DBC RPC 0x8000131D, function 2): sends the request's words +8 / +12 under the
// library semaphore 0x997000 and returns the answer word, -1 on an RPC error.
void sceDbcSearchPortSpecific(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0051cdd8
    enter(ctx, 32);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s2, sp, 0x30);
    sd(s0, sp, 0x10);
    s2 = 0x990000;
    s0 = a0;
    sd(s1, sp, 0x20);
    lw(a0, s2, 28672);  // 0x997000
    sd(ra, sp, 0x40);
    jal(ctx, 0x51CDF8u, gen::fn__sceWaitSema_005031a0);
    v1 = 0x990000;
    v0 = 2;
    s1 = addiu(v1, 26688);  // &0x996840
    a0 = 0x990000;
    sw(v0, s1, 8);  // 0x996848
    a1 = lui(0x8000);
    sw(zero, sp, 0x0);
    a0 = addiu(a0, 26432);  // &0x996740
    a1 = a1 | 0x131D;
    a2 = 0;
    lw(v0, s0, 8);
    a3 = s1;
    t0 = 144;
    t1 = s1;
    sw(v0, s1, 16);  // 0x996850
    t2 = 144;
    t3 = 0;
    lw(v0, s0, 12);
    link(ctx, 0x51CE48u);  // $ra first: the delay slot below depends on it
    sw(v0, s1, 20);  // 0x996854
    call(ctx, gen::fn_sceSifCallRpc_00507230);
    lw(a0, s2, 28672);  // 0x997000
    if (i64(v0) >= 0) {
        // 0x0051ce74
        charge(ctx, 3);
        link(ctx, 0x51CE74u);  // $ra first: the delay slot below depends on it
        lw(s0, s1, 4);
        call(ctx, gen::fn__sceSignalSema_00503180);
        v0 = s0;
    } else {
        // 0x0051ce58
        charge(ctx, 7);
        a0 = 0x7C0000;
        a0 = addiu(a0, -6144);  // "sceDbcGetDeviceStatus: rpc error\n"
        jal(ctx, 0x51CE5Cu, gen::fn_DPRINT_0051d588);
        link(ctx, 0x51CE64u);  // $ra first: the delay slot below depends on it
        lw(a0, s2, 28672);
        call(ctx, gen::fn__sceSignalSema_00503180);
        v0 = si(-1);
    }
    // 0x0051ce80 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x40);
    ld(s2, sp, 0x30);
    ld(s1, sp, 0x20);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x50);
}

// 0x0053B760 sub_53B760 -- 260 bytes; frame 0x10: ra sp+0x0
// ADXF partition load and wait: starts adxf_LoadPartitionNw, then runs ADXM_ExecMain and sub_53B680 until sub_53C2A0
// reports state 3 (0) or 4 (-1); the start's error as is.
void sub_53B760(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053b760
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a3 = a2;
    sd(ra, sp, 0x0);
    a2 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x0053b7e8
    charge(ctx, 11);
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = 4;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = 3;
    jal(ctx, 0x53B804u, gen::fn_adxf_LoadPartitionNw_0053b8d0);
    if (i64(v0) >= 0) {
        for (;;) {
            // 0x0053b830
            charge(ctx, 4);
            a0 = s0;
            jal(ctx, 0x53B830u, gen::fn_sub_53C2A0_0053c2a0);
            v1 = 0;
            if (v0 != s2) {
                // 0x0053b840
                charge(ctx, 2);
                v1 = si(-1);
                if (v0 != s1) {
                    backedge(ctx);
                    // 0x0053b820
                    charge(ctx, 4);
                    jal(ctx, 0x53B820u, gen::fn_ADXM_ExecMain_00540ec0);
                    jal(ctx, 0x53B828u, gen::fn_sub_53B680_0053b680);
                    continue;
                }
            }
            break;
        }
        // 0x0053b848
        charge(ctx, 2);
        v0 = v1;
        ld(s0, sp, 0x0);
    } else {
        // 0x0053b814
        charge(ctx, 2);
        ld(s0, sp, 0x0);
    }
    // 0x0053b850 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0053C200 sub_53C200 -- 104 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Stops the ADXF handle at 0x7853D0 (sub_53D450) when it is open and not idle (adxf_GetStat != 1), then tail-calls
// sub_53C198.
void sub_53C200(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0053c200
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x780000;
    sd(s0, sp, 0x0);
    s0 = addiu(v0, 21456);  // &0x7853D0
    sd(ra, sp, 0x8);
    lw(a0, s0, 0);  // 0x7853D0
    v0 = 0x780000;
    if (a0 == 0) {
        // 0x0053c258
        charge(ctx, 1);
        ld(s0, sp, 0x0);
        // 0x0053c25c (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0053c220
    charge(ctx, 3);
    lw(v1, v0, 21460);
    if (i64(v1) < 0) {
        ld(s0, sp, 0x0);
        // 0x0053c25c (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0053c22c
    charge(ctx, 5);
    jal(ctx, 0x53C22Cu, gen::fn_adxf_GetStat_0053dbc8);
    v1 = 1;
    if (v0 == v1) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0053c240
        charge(ctx, 3);
        link(ctx, 0x53C240u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 0);
        call(ctx, gen::fn_sub_53D450_0053d450);
        ld(s0, sp, 0x0);
    }
    // 0x0053c24c
    charge(ctx, 3);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_53C198_0053c198(ctx);  // tail call
}

// 0x0055FA40 sub_55FA40 -- 224 bytes; frame 0x20: s2 sp+0x10, s1 sp+0x8, s0 sp+0x0, ra sp+0x18
// Releases the table of 24-byte records at 0x7A9450 (count 0x7A93F0): each record's three objects (sub_564038, the
// virtual release at vtable +12, sub_564830), then memset; and the IOP block 0x7A93FC when the flag 0x7A9404 is 1.
void sub_55FA40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0055fa40
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s2, sp, 0x10);
    s2 = 0x7B0000;
    lw(v0, s2, -27664);  // 0x7A93F0
    sd(s1, sp, 0x8);
    s1 = 0;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x18);
    if (i64(v0) > 0) {
        // 0x0055fa64
        charge(ctx, 3);
        v0 = 0x7B0000;
        s0 = addiu(v0, -27568);  // &0x7A9450
        lw(v0, s0, 4);  // 0x7A9454
        for (;;) {
            // 0x0055fa70
            charge(ctx, 2);
            a0 = v0;
            if (v0 != 0) {
                // 0x0055fa78
                charge(ctx, 2);
                jal(ctx, 0x55FA78u, gen::fn_sub_564038_00564038);
            }
            // 0x0055fa80
            charge(ctx, 3);
            lw(v0, s0, 8);
            a0 = v0;
            if (v0 != 0) {
                // 0x0055fa8c
                charge(ctx, 4);
                lw(v0, v0, 0);
                lw(v1, v0, 12);
                jalr(ctx, 0x55FA94u, v1.u());
            }
            // 0x0055fa9c
            charge(ctx, 3);
            lw(a0, s0, 12);
            if (a0 == 0) {
                a0 = s0;
            } else {
                // 0x0055faa8
                charge(ctx, 3);
                jal(ctx, 0x55FAA8u, gen::fn_sub_564830_00564830);
                a0 = s0;
            }
            // 0x0055fab4
            charge(ctx, 9);
            s0 = addiu(s0, 24);
            a1 = 0;
            a2 = 24;
            jal(ctx, 0x55FABCu, gen::fn_memset_00521408);
            lw(v1, s2, -27664);
            s1 = addiu(s1, 1);
            v1 = slt(s1, v1);
            if (v1 == 0) {
                break;
            }
            lw(v0, s0, 4);
            backedge(ctx);
        }
    }
    // 0x0055fad8
    charge(ctx, 6);
    v0 = 0x7B0000;
    a0 = 1;
    s1 = addiu(v0, -27644);  // &0x7A9404
    lb(v1, s1, 0);  // 0x7A9404
    ld(s0, sp, 0x0);
    if (v1 == a0) {
        // 0x0055faf0
        charge(ctx, 7);
        s0 = 0x7B0000;
        s0 = addiu(s0, -27652);  // &0x7A93FC
        link(ctx, 0x55FAF8u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 0);  // 0x7A93FC
        call(ctx, gen::fn_sceSifFreeIopHeap_0050b788);
        sw(zero, s0, 0);  // 0x7A93FC
        sb(zero, s1, 0);
        ld(s0, sp, 0x0);
    }
    // 0x0055fb0c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00560698 sub_560698 -- 188 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Drops one reference (0x7A943C) of the sound / stream system (nothing when the mode word 0x7A93F8 is 1 and the record
// count 0x7A93F0 is not positive); at zero frees its IOP blocks (0x7A940C, 0x7A9444) and the handle 0x7ABE90 and runs
// the five sub-system finalisers.
void sub_560698(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00560698
    enter(ctx, 8);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x20);
    lw(v1, v0, -27656);  // 0x7A93F8
    a0 = 1;
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    if (v1 == a0) {
        // 0x005606b8
        charge(ctx, 4);
        v0 = 0x7B0000;
        lw(v1, v0, -27664);  // 0x7A93F0
        ld(s0, sp, 0x0);
        if (i64(v1) > 0) {
            goto L_005606c8;
        }
        // 0x00560744 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
L_005606c8:
    charge(ctx, 6);
    v1 = 0x7B0000;
    v1 = addiu(v1, -27588);  // &0x7A943C
    lw(v0, v1, 0);  // 0x7A943C
    v0 = addiu(v0, -1);
    sw(v0, v1, 0);  // 0x7A943C
    if (v0 == 0) {
        // 0x005606e0
        charge(ctx, 24);
        s0 = 0x7B0000;
        s1 = 0x7B0000;
        s0 = addiu(s0, -27636);  // &0x7A940C
        s1 = addiu(s1, -16752);  // &0x7ABE90
        link(ctx, 0x5606F0u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 0);  // 0x7A940C
        call(ctx, gen::fn_sceSifFreeIopHeap_0050b788);
        sw(zero, s0, 0);  // 0x7A940C
        s0 = 0x7B0000;
        lw(a0, s1, 0);  // 0x7ABE90
        s0 = addiu(s0, -27580);  // &0x7A9444
        jal(ctx, 0x560704u, gen::fn_sub_5598B0_005598b0);
        sw(zero, s1, 0);  // 0x7ABE90
        link(ctx, 0x560710u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 0);  // 0x7A9444
        call(ctx, gen::fn_sceSifFreeIopHeap_0050b788);
        link(ctx, 0x560718u);  // $ra first: the delay slot below depends on it
        sw(zero, s0, 0);  // 0x7A9444
        call(ctx, gen::fn_sub_55FA40_0055fa40);
        jal(ctx, 0x560720u, gen::fn_sub_560378_00560378);
        jal(ctx, 0x560728u, gen::fn_sub_559B98_00559b98);
        jal(ctx, 0x560730u, gen::fn_sub_5646C0_005646c0);
        jal(ctx, 0x560738u, gen::fn_sub_564320_00564320);
    }
    // 0x00560740
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x00560744 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x005646C0 sub_5646C0 -- 120 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Drops one reference (0x7B1ABC); at zero releases the handle 0x7B1D50 (sub_5598B0), frees the IOP block 0x7B1AC4 and
// tail-calls sub_559B98.
void sub_5646C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005646c0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 0x7B0000;
    sd(s0, sp, 0x0);
    v1 = addiu(v1, 6844);  // &0x7B1ABC
    sd(ra, sp, 0x8);
    lw(v0, v1, 0);  // 0x7B1ABC
    v0 = addiu(v0, -1);
    sw(v0, v1, 0);  // 0x7B1ABC
    if (v0 != 0) {
        // 0x00564728
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x005646e4
    charge(ctx, 10);
    s0 = 0x7B0000;
    s0 = addiu(s0, 7504);  // &0x7B1D50
    link(ctx, 0x5646ECu);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 0);  // 0x7B1D50
    call(ctx, gen::fn_sub_5598B0_005598b0);
    sw(zero, s0, 0);  // 0x7B1D50
    v0 = 0x7B0000;
    s0 = addiu(v0, 6852);  // &0x7B1AC4
    lw(v1, s0, 0);  // 0x7B1AC4
    a0 = v1;
    if (v1 != 0) {
        // 0x0056470c
        charge(ctx, 3);
        jal(ctx, 0x56470Cu, gen::fn_sceSifFreeIopHeap_0050b788);
        sw(zero, s0, 0);
    }
    // 0x00564718
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_559B98_00559b98(ctx);  // tail call
}

// 0x00565B90 ROFS_ChangeDir -- 48 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ROFS_ChangeDir(path): sub_569810, then tail call ROFS_LoadDir(path, 0, 0).
void ROFS_ChangeDir(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00565b90
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x565B9Cu, gen::fn_sub_569810_00569810);
    ld(ra, sp, 0x8);
    a0 = s0;
    ld(s0, sp, 0x0);
    a1 = 0;
    a2 = 0;
    sp = addiu(sp, 0x10);
    gen::fn_ROFS_LoadDir_00566a58(ctx);  // tail call
}

// 0x00567750 rfmai_readRootDirRec -- 192 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Reads a volume's root directory: the ISO directory record at +156 of the volume descriptor (RFMAI_CopyStructCdDr),
// its big-endian LBA and size, then RFDIR_GetDirEnt into the list header $a2 with the work buffer g_rofs_work+72;
// -105 when the list stays empty.
void rfmai_readRootDirRec(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00567750
    enter(ctx, 41);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    a0 = addiu(a1, 156);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a2;
    jal(ctx, 0x567768u, gen::fn_RFMAI_CopyStructCdDr_0056a348);
    t0 = 0x7B0000;
    lw(t2, v0, 16);
    a0 = s0;
    lw(v1, v0, 8);
    lbu(t1, v0, 8);
    a1 = srl(t2, 8);
    lbu(a3, v0, 16);
    v0 = srl(v1, 8);
    sw(zero, s1, 8);
    a2 = srl(v1, 8);
    v0 = v0 & 0xFF;
    a1 = a1 & 0xFF;
    lw(t3, t0, 9984);  // g_rofs_work
    t0 = srl(t2, 8);
    a1 = sll(a1, 16);
    t1 = sll(t1, 24);
    a2 = a2 & 0xFF00;
    v0 = sll(v0, 16);
    a3 = sll(a3, 24);
    t0 = t0 & 0xFF00;
    v1 = srl(v1, 24);
    t2 = srl(t2, 24);
    a3 = a3 | t2;
    t0 = t0 | a1;
    t1 = t1 | v1;
    a2 = a2 | v0;
    lw(a1, t3, 72);
    t0 = a3 | t0;
    a2 = t1 | a2;
    a3 = s1;
    jal(ctx, 0x5677E4u, gen::fn_RFDIR_GetDirEnt_0056c0f8);
    ld(s0, sp, 0x0);
    if (v0 == 0) {
        // 0x005677f4
        charge(ctx, 3);
        lw(v1, s1, 0);
        v0 = si(-105);
        if (v1 != 0) v0 = 0;
    }
    // 0x00567800 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00569D90 RFMAI_DescrambleG -- 300 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// RFMAI_DescrambleG(hn, nsct, ctx): deciphers `nsct` sectors of a scrambled stream (rfmai_decipherSectors) and
// advances its sector counter (+4); the ROFS error -100 through sub_569730 ("RFMAI_CancelScrambleG") for a null
// handle, negative count, null or unset context.
void RFMAI_DescrambleG(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00569d90
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = a0;
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    a1 = 2468;
    if (v1 == 0) {
        // 0x00569db4
        charge(ctx, 11);
        a0 = 0x7C0000;
        a2 = 0x7C0000;
        ld(s0, sp, 0x0);
        a0 = addiu(a0, 29352);  // "../../rofs_mai.c"
        ld(s1, sp, 0x8);
        a2 = addiu(a2, 30128);  // "RFMAI_CancelScrambleG"
        ld(ra, sp, 0x10);
        a3 = 0;
        t0 = si(-100);
        sp = addiu(sp, 0x20);
        gen::fn_sub_569730_00569730(ctx);  // tail call
        return;
    }
    // 0x00569de0
    charge(ctx, 2);
    a0 = 0x7C0000;
    if (i64(s1) < 0) {
        // 0x00569de8
        charge(ctx, 11);
        a2 = 0x7C0000;
        ld(s0, sp, 0x0);
        a0 = addiu(a0, 29352);
        ld(s1, sp, 0x8);
        a2 = addiu(a2, 30128);  // "RFMAI_CancelScrambleG"
        ld(ra, sp, 0x10);
        a1 = 2471;
        a3 = 0;
        t0 = si(-100);
        sp = addiu(sp, 0x20);
        gen::fn_sub_569730_00569730(ctx);  // tail call
        return;
    }
    // 0x00569e18
    charge(ctx, 2);
    if (s0 == 0) {
        // 0x00569e20
        charge(ctx, 12);
        a0 = 0x7C0000;
        a2 = 0x7C0000;
        ld(s0, sp, 0x0);
        a0 = addiu(a0, 29352);  // "../../rofs_mai.c"
        ld(s1, sp, 0x8);
        a2 = addiu(a2, 30128);  // "RFMAI_CancelScrambleG"
        ld(ra, sp, 0x10);
        a1 = 2474;
        a3 = 0;
        t0 = si(-100);
        sp = addiu(sp, 0x20);
        gen::fn_sub_569730_00569730(ctx);  // tail call
        return;
    }
    lw(v0, s0, 0);
    // 0x00569e50
    charge(ctx, 2);
    a0 = v0;
    if (v0 != 0) {
        // 0x00569e88
        charge(ctx, 13);
        lw(a3, s0, 4);
        a1 = v1;
        a2 = s1;
        jal(ctx, 0x569E90u, gen::fn_rfmai_decipherSectors_00569c00);
        lw(v1, s0, 4);
        ld(ra, sp, 0x10);
        v0 = 0;
        v1 = addu(v1, s1);
        ld(s1, sp, 0x8);
        sw(v1, s0, 4);
        ld(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00569e58
    charge(ctx, 12);
    a0 = 0x7C0000;
    a2 = 0x7C0000;
    ld(s0, sp, 0x0);
    a0 = addiu(a0, 29352);  // "../../rofs_mai.c"
    ld(s1, sp, 0x8);
    a2 = addiu(a2, 30128);  // "RFMAI_CancelScrambleG"
    ld(ra, sp, 0x10);
    a1 = 2477;
    a3 = 0;
    t0 = si(-100);
    sp = addiu(sp, 0x20);
    gen::fn_sub_569730_00569730(ctx);  // tail call
}

// 0x0056BDC0 rfdir_getDirEnt -- 820 bytes; frame 0x60: s4 sp+0x30, s5 sp+0x38, fp sp+0x50, s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, s6 sp+0x40, s7 sp+0x48, ra sp+0x58
// Fills a #DirLst# list from ISO directory sectors: the cached list when its LBA and name match; a shared list
// copied; otherwise reads up to two sectors at a time (RFMAI_ReadWG + decipher) and parses records
// (rfdir_getOneDirEnt) until the capacity or the directory size is reached; -100 bad arguments, -109 the list
// overflowed, or the read error.
void rfdir_getDirEnt(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0056bdc0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(s4, sp, 0x30);
    s4 = t0;
    sd(s5, sp, 0x38);
    s5 = a1;
    sd(fp, sp, 0x50);
    fp = a3;
    sd(s0, sp, 0x10);
    sd(s1, sp, 0x18);
    sd(s2, sp, 0x20);
    sd(s3, sp, 0x28);
    sd(s6, sp, 0x40);
    sd(s7, sp, 0x48);
    sd(ra, sp, 0x58);
    sw(a0, sp, 0x4);
    sw(a2, sp, 0x8);
    if (a0 != 0) {
        // 0x0056be04
        charge(ctx, 2);
        a0 = 0x7C0000;
        if (s5 == 0) {
        L_0056be18:
            charge(ctx, 9);
            a2 = 0x7C0000;
            a0 = addiu(a0, 30488);
            a2 = addiu(a2, 30512);  // "getDirEnt"
            a1 = 327;
            a3 = 0;
            t0 = si(-100);
            jal(ctx, 0x56BE2Cu, gen::fn_sub_569730_00569730);
            v0 = si(-100);
        L_0056c0c4:
            charge(ctx, 1);
            ld(s0, sp, 0x10);
        } else {
            // 0x0056be0c
            charge(ctx, 2);
            if (fp == 0) {
                goto L_0056be14;
            }
            lw(v0, fp, 0x8);
            // 0x0056be40
            charge(ctx, 3);
            lw(v1, sp, 0x8);
            if (v0 != v1) {
                lw(v1, sp, 0x4);
                // 0x0056be78
                charge(ctx, 3);
                s1 = addiu(fp, 0xC);
                s0 = addiu(v1, 22);
                lw(v0, sp, 0x4);
            L_0056be84:
                charge(ctx, 5);
                lw(v1, sp, 0x8);
                lw(s2, v0, 16);
                lw(v0, s2, 8);
                if (v0 == v1) {
                    // 0x0056be98
                    charge(ctx, 9);
                    sw(v1, fp, 0x8);
                    a0 = s1;
                    a1 = s0;
                    jal(ctx, 0x56BEA0u, gen::fn_strcpy_00524270);
                    lw(v1, s2, 0);
                    lw(a2, fp, 0x4);
                    v0 = slt(a2, v1);
                    if (v0 == 0) {
                        s3 = v1;
                        // 0x0056bec8
                        charge(ctx, 1);
                        s7 = 0;
                    } else {
                        // 0x0056bebc
                        charge(ctx, 3);
                        s3 = a2;
                        s7 = si(-109);
                    }
                    // 0x0056becc
                    charge(ctx, 9);
                    a2 = sll(s3, 1);
                    a1 = addiu(s2, 24);
                    a2 = addu(a2, s3);
                    a0 = addiu(fp, 0x18);
                    a2 = sll(a2, 4);
                    jal(ctx, 0x56BEDCu, gen::fn_memcpy_00521250);
                    sw(s3, fp, 0x0);
                    v0 = s7;
                    goto L_0056c0c4;
                }
                lw(v0, sp, 0x8);
                // 0x0056bef0
                charge(ctx, 10);
                a1 = s0;
                a0 = s1;
                s3 = 0;
                sw(v0, fp, 0x8);
                s6 = addiu(fp, 0x18);
                s0 = s5;
                jal(ctx, 0x56BF04u, gen::fn_strcpy_00524270);
                lw(v1, fp, 0x4);
                sw(v1, sp, 0xC);
                if (i64(s4) > 0) {
                    for (;;) {
                        // 0x0056bf18
                        charge(ctx, 15);
                        v1 = dsll32(s4, 0);
                        v1 = dsra32(v1, 0);
                        s1 = 2;
                        v1 = addiu(v1, 2047);
                        lw(a0, sp, 0x4);
                        v1 = srl(v1, 11);
                        lw(a1, sp, 0x8);
                        v0 = slti(v1, 2);
                        a3 = s5;
                        if (v0 != 0) s1 = v1;
                        a2 = s1;
                        jal(ctx, 0x56BF40u, gen::fn_RFMAI_ReadWG_00569538);
                        s7 = v0;
                        lw(a0, sp, 0x4);
                        if (s7 != s1) {
                            goto L_0056bf54_16;
                        }
                        // 0x0056bf80
                        charge(ctx, 8);
                        a2 = s7;
                        lw(a3, sp, 0x8);
                        a1 = s5;
                        s0 = s5;
                        jal(ctx, 0x56BF8Cu, gen::fn_rfmai_decipherSectors_00569c00);
                        lw(v0, sp, 0xC);
                        s2 = slt(s3, v0);
                        for (;;) {
                            // 0x0056bfd0
                            charge(ctx, 2);
                            a0 = s0;
                            if (s2 == 0) {
                                goto L_0056c050;
                            }
                            // 0x0056bfd8
                            charge(ctx, 15);
                            a1 = s6;
                            jal(ctx, 0x56BFD8u, gen::fn_rfdir_getOneDirEnt_0056bcb0);
                            v1 = subu(s0, s5);
                            v1 = addiu(v1, 2048);
                            s7 = v0;
                            v0 = si(-2048);
                            a0 = sll(s1, 11);
                            a1 = v1 & v0;
                            v0 = si(-1);
                            v1 = dsll32(a1, 0);
                            a2 = addu(s5, a0);
                            v1 = dsrl32(v1, 0);
                            a0 = a2;
                            v1 = s4 - v1;
                            if (i64(s7) <= 0) {
                                // 0x0056c014
                                charge(ctx, 2);
                                if (s7 != v0) {
                                    break;
                                }
                                // 0x0056c01c
                                charge(ctx, 4);
                                s0 = addu(s5, a1);
                                v0 = sltu(s0, a0);
                                if (v0 == 0) {
                                    break;
                                }
                                // 0x0056c02c
                                charge(ctx, 2);
                                if (i64(v1) <= 0) {
                                    break;
                                }
                                backedge(ctx);
                                continue;
                            }
                            backedge(ctx);
                            // 0x0056bfa0
                            charge(ctx, 2);
                            s0 = addu(s0, s7);
                            if (s3 == 0) {
                                // 0x0056bfa8
                                charge(ctx, 4);
                                lwu(v0, s6, 0);
                                lw(v1, s6, 0);
                                v0 = v0 ^ s4;
                                if (v0 != 0) s4 = v1;
                            }
                            // 0x0056bfb8
                            charge(ctx, 6);
                            lw(v1, sp, 0xC);
                            s3 = addiu(s3, 1);
                            v0 = sltu(s0, a2);
                            s2 = slt(s3, v1);
                            s6 = addiu(s6, 48);
                            if (v0 == 0) {
                                break;
                            }
                        }
                        // 0x0056c034
                        charge(ctx, 2);
                        v0 = sll(s1, 11);
                        if (s2 == 0) {
                            break;
                        }
                        // 0x0056c03c
                        charge(ctx, 5);
                        lw(v1, sp, 0x8);
                        s4 = s4 - v0;
                        v1 = addu(v1, s1);
                        sw(v1, sp, 0x8);
                        if (i64(s4) <= 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
            L_0056c050:
                charge(ctx, 4);
                sw(s3, fp, 0x0);
                lw(v0, sp, 0xC);
                cc = s3 != v0;  // the condition, before the delay slot changes it
                v0 = 0;
                if (!cc) {
                    // 0x0056c060
                    charge(ctx, 2);
                    v0 = 2048;
                    if (s4 == 0) {
                        // 0x0056c0c0
                        charge(ctx, 1);
                        v0 = 0;
                    } else {
                        // 0x0056c068
                        charge(ctx, 2);
                        if (s4 != v0) {
                            sw(zero, fp, 0x8);
                        } else {
                            // 0x0056c070
                            charge(ctx, 4);
                            v0 = addiu(s5, 2048);
                            v0 = sltu(s0, v0);
                            cc = v0 == 0;  // the condition, before the delay slot changes it
                            v0 = 0;
                            if (!cc) {
                                // 0x0056c080
                                charge(ctx, 3);
                                lb(v0, s0, 0);
                                if (v0 != 0) {
                                    // 0x0056c08c
                                    charge(ctx, 1);
                                    sw(zero, fp, 0x8);
                                    goto L_0056c090;
                                }
                                v0 = 0;
                            }
                            goto L_0056c0c4;
                        }
                    L_0056c090:
                        charge(ctx, 2);
                        v0 = si(-109);
                    }
                }
                goto L_0056c0c4;
            }
            // 0x0056be4c
            charge(ctx, 8);
            lw(v0, sp, 0x4);
            s1 = addiu(fp, 0xC);
            a0 = s1;
            s0 = addiu(v0, 22);
            a1 = s0;
            jal(ctx, 0x56BE5Cu, gen::fn_strcmp_00524128);
            if (v0 != 0) {
                lw(v0, sp, 0x4);
                goto L_0056be84;
            }
            // 0x0056be6c
            charge(ctx, 2);
            ld(s0, sp, 0x10);
        }
        // 0x0056c0c8 (the shared epilogue, written out on this path)
        charge(ctx, 11);
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
L_0056be14:
    charge(ctx, 1);
    a0 = 0x7C0000;
    goto L_0056be18;
L_0056bf54_16:
    charge(ctx, 9);
    sw(zero, fp, 0x8);
    a0 = 0;
    a1 = 2;
    a2 = sp;
    jal(ctx, 0x56BF60u, gen::fn_sub_56A040_0056a040);
    v1 = 1;
    lw(v0, sp, 0x0);
    cc = v0 == v1;  // the condition, before the delay slot changes it
    v0 = s7;
    if (cc) {
        // 0x0056c098
        charge(ctx, 10);
        a0 = 0x7C0000;
        a2 = 0x7C0000;
        a0 = addiu(a0, 30488);  // "../../rofs_dir.c"
        a2 = addiu(a2, 30512);  // "getDirEnt"
        t0 = s7;
        a1 = 391;
        a3 = 0;
        jal(ctx, 0x56C0B0u, gen::fn_sub_569730_00569730);
        ld(s0, sp, 0x10);
    } else {
        // 0x0056bf78
        charge(ctx, 2);
        ld(s0, sp, 0x10);
    }
    // 0x0056c0c8 (the shared epilogue, written out on this path)
    charge(ctx, 11);
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

// 0x0056C188 RFDIR_SetDirEnt -- 340 bytes; frame 0x50: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s4 sp+0x20, s5 sp+0x28, s7 sp+0x38, fp sp+0x40, s3 sp+0x18, s6 sp+0x30, ra sp+0x48
// Parses an in-memory ISO directory (`nsct` sectors) into a #DirLst# list (count, capacity, entries at +24): 0, -109
// when it overflowed, -110 when it ran past the buffer.
void RFDIR_SetDirEnt(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x0056c188
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s0 = s1;
    sd(s4, sp, 0x20);
    s4 = 0;
    sd(s5, sp, 0x28);
    s5 = 2048;
    sd(s7, sp, 0x38);
    s7 = a2;
    sd(fp, sp, 0x40);
    fp = sll(a1, 11);
    sd(s3, sp, 0x18);
    s2 = addiu(s7, 24);
    sd(s6, sp, 0x30);
    a0 = s2;
    sd(ra, sp, 0x48);
    a1 = 0;
    sw(zero, s7, 8);
    lw(s6, s7, 4);
    a2 = sll(s6, 1);
    a2 = addu(a2, s6);
    a2 = sll(a2, 4);
    jal(ctx, 0x56C1E8u, gen::fn_memset_00521408);
    s3 = slt(s4, s6);
    for (;;) {
        // 0x0056c21c
        charge(ctx, 2);
        v0 = addu(s1, fp);
        if (s3 != 0) {
            // 0x0056c224
            charge(ctx, 3);
            v0 = sltu(v0, s0);
            a0 = s0;
            if (v0 == 0) {
                // 0x0056c230
                charge(ctx, 10);
                a1 = s2;
                jal(ctx, 0x56C230u, gen::fn_rfdir_getOneDirEnt_0056bcb0);
                v1 = si(-2048);
                a0 = v0;
                v0 = subu(s0, s1);
                v0 = addiu(v0, 2048);
                a1 = v0 & v1;
                v1 = addu(s1, s5);
                v0 = si(-1);
                if (i64(a0) > 0) {
                    backedge(ctx);
                    // 0x0056c1f8
                    charge(ctx, 2);
                    if (s4 == 0) {
                        lw(s5, s2, 0);
                    }
                    // 0x0056c200
                    charge(ctx, 6);
                    s0 = addu(s0, a0);
                    v0 = addu(s1, s5);
                    v0 = sltu(s0, v0);
                    s4 = addiu(s4, 1);
                    s2 = addiu(s2, 48);
                    if (v0 != 0) {
                        // 0x0056c218
                        charge(ctx, 1);
                        s3 = slt(s4, s6);
                        continue;
                    }
                } else {
                    // 0x0056c258
                    charge(ctx, 2);
                    if (a0 == v0) {
                        // 0x0056c260
                        charge(ctx, 4);
                        s0 = addu(s1, a1);
                        v0 = sltu(s0, v1);
                        if (v0 != 0) {
                            // 0x0056c270
                            charge(ctx, 2);
                            if (s5 != a1) {
                                backedge(ctx);
                                continue;
                            }
                        }
                    }
                }
            }
        }
        break;
    }
    // 0x0056c278
    charge(ctx, 2);
    sw(s4, s7, 0);
    if (s4 == s6) {
        // 0x0056c280
        charge(ctx, 4);
        v0 = addu(s1, s5);
        v0 = sltu(s0, v0);
        v1 = addu(s1, fp);
        if (v0 == 0) {
        L_0056c2a0:
            charge(ctx, 3);
            v0 = si(-110);
            v1 = sltu(v1, s0);
            if (v1 == 0) v0 = 0;
        } else {
            // 0x0056c290
            charge(ctx, 3);
            lb(v1, s0, 0);
            v0 = si(-109);
            if (v1 == 0) {
                goto L_0056c29c;
            }
        }
        // 0x0056c2ac (the shared epilogue, written out on this path)
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
    }
L_0056c29c:
    charge(ctx, 1);
    v1 = addu(s1, fp);
    goto L_0056c2a0;
}

// 0x0056C5F0 rfdir_searchPath -- 500 bytes; frame 0x60: s3 sp+0x28, s1 sp+0x18, s0 sp+0x10, ra sp+0x58, s2 sp+0x20, s4 sp+0x30, s5 sp+0x38, s6 sp+0x40, s7 sp+0x48, fp sp+0x50
// ISO 9660 path-table walk: reads the table a sector at a time, matches each '/' or '\' separated component
// (rfdirStrncmpi) against the records whose parent is the previous match, and returns the directory's LBA (0 not
// found, the read error through sub_569730).
void rfdir_searchPath(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x0056c5f0
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v0 = 1;
    sd(s3, sp, 0x28);
    s3 = a1;
    sd(s1, sp, 0x18);
    s1 = addiu(s3, 2048);
    sd(s0, sp, 0x10);
    sd(ra, sp, 0x58);
    sw(a3, sp, 0x0);
    sw(v0, sp, 0x4);
    sw(zero, sp, 0x8);
    sd(s2, sp, 0x20);
    s2 = addiu(t0, 1);
    sd(s4, sp, 0x30);
    s4 = a2;
    sd(s5, sp, 0x38);
    s5 = 1;
    sd(s6, sp, 0x40);
    s6 = s1;
    sd(s7, sp, 0x48);
    s7 = a0;
    sd(fp, sp, 0x50);
    fp = 0;
    for (;;) {
        // 0x0056c650
        charge(ctx, 3);
        v0 = sltu(s1, s6);
        a2 = subu(s3, s1);
        if (v0 != 0) {
            // 0x0056c65c
            charge(ctx, 8);
            lbu(v0, s1, 0);
            v1 = v0 & 0x1;
            v0 = addu(v0, v1);
            v0 = addu(s1, v0);
            v0 = addiu(v0, 8);
            v0 = sltu(v0, s6);
            if (v0 == 0) {
                goto L_0056c67c;
            }
        L_0056c6f0:
            charge(ctx, 7);
            a0 = s1;
            jal(ctx, 0x56C6F0u, gen::fn_RFMAI_CopyStructCdPt_0056a468);
            s0 = v0;
            lw(a0, sp, 0x4);
            lhu(v0, s0, 8);
            if (v0 != a0) {
                lbu(a2, s0, 0);
            } else {
                // 0x0056c70c
                charge(ctx, 3);
                a1 = 1;
                if (s5 == a1) {
                    sw(s5, sp, 0x4);
                } else {
                    // 0x0056c718
                    charge(ctx, 3);
                    lbu(a2, s0, 0);
                    lw(a0, sp, 0x8);
                    if (a2 == fp) {
                        // 0x0056c724
                        charge(ctx, 5);
                        a0 = addiu(s0, 10);
                        a1 = s2;
                        jal(ctx, 0x56C728u, gen::fn_rfdirStrncmpi_0056b9a8);
                        if (v0 == 0) {
                            lbu(a2, s0, 0);
                            goto L_0056c778;
                        }
                        // 0x0056c738
                        charge(ctx, 1);
                        sw(s5, sp, 0x4);
                        goto L_0056c73c;
                    }
                L_0056c77c:
                    charge(ctx, 13);
                    v0 = a2 & 0x1;
                    v0 = v0 & 0xFF;
                    lw(a1, sp, 0x0);
                    v1 = addu(a0, a2);
                    s5 = addiu(s5, 1);
                    v1 = addu(v1, v0);
                    v0 = addu(a2, v0);
                    v1 = addiu(v1, 8);
                    v0 = addu(s1, v0);
                    sw(v1, sp, 0x8);
                    v1 = slt(v1, a1);
                    s1 = addiu(v0, 8);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    continue;
                }
            L_0056c73c:
                charge(ctx, 4);
                s2 = addu(s2, fp);
                lb(v0, s2, 0);
                v1 = addiu(s2, 1);
                if (v0 == 0) {
                    goto L_0056c74c_12;
                }
                // 0x0056c758
                charge(ctx, 8);
                v0 = s5 ^ 0x1;
                if (v0 != 0) s2 = v1;
                v0 = 0x7C0000;
                a1 = addiu(v0, 30560);  // "/\\"
                a0 = s2;
                jal(ctx, 0x56C768u, gen::fn_rfdir_getTokenSize_0056bba0);
                lbu(a2, s0, 0);
                fp = v0;
                goto L_0056c778;
            }
        L_0056c778:
            charge(ctx, 1);
            lw(a0, sp, 0x8);
            goto L_0056c77c;
        }
    L_0056c67c:
        charge(ctx, 13);
        a1 = s1;
        a2 = addiu(a2, 2048);
        s0 = subu(s3, a2);
        a0 = s0;
        jal(ctx, 0x56C688u, gen::fn_memcpy_00521250);
        a0 = s7;
        a1 = s4;
        a2 = 1;
        a3 = s3;
        jal(ctx, 0x56C69Cu, gen::fn_RFMAI_ReadWG_00569538);
        v1 = 1;
        if (v0 != v1) {
            goto L_0056c6b0_4;
        }
        a3 = s4;
        // 0x0056c6d8
        charge(ctx, 6);
        s4 = addiu(s4, 1);
        a0 = s7;
        a1 = s3;
        a2 = 1;
        s1 = s0;
        jal(ctx, 0x56C6E8u, gen::fn_rfmai_decipherSectors_00569c00);
        goto L_0056c6f0;
    }
    // 0x0056c7b0
    charge(ctx, 1);
    v0 = 0;
L_0056c7b4:
    charge(ctx, 1);
    ld(s0, sp, 0x10);
    // 0x0056c7b8 (the shared epilogue, written out on this path)
    charge(ctx, 11);
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
L_0056c6b0_4:
    charge(ctx, 10);
    a1 = 0x7C0000;
    v1 = 0x7C0000;
    a0 = addiu(a1, 30488);  // "../../rofs_dir.c"
    a1 = 806;
    a2 = addiu(v1, 30544);  // "RFMAI_ReadWG"
    t0 = v0;
    a3 = 0;
    jal(ctx, 0x56C6C8u, gen::fn_sub_569730_00569730);
    ld(s0, sp, 0x10);
    // 0x0056c7b8 (the shared epilogue, written out on this path)
    charge(ctx, 11);
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
L_0056c74c_12:
    charge(ctx, 2);
    lw(v0, s0, 4);
    goto L_0056c7b4;
}

// 0x0056C7E8 RFDIR_SearchPath -- 144 bytes; frame 0x40: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, ra sp+0x30
// RFDIR_SearchPath: under the PFS lock (RFPFS_PfsLock / sub_56ABE0), rfdir_searchPath unless the lock call failed;
// its result.
void RFDIR_SearchPath(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056c7e8
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
    jal(ctx, 0x56C818u, gen::fn_RFPFS_PfsLock_0056ab90);
    s5 = v0;
    a0 = s0;
    a1 = s1;
    a2 = s2;
    a3 = s3;
    t0 = s4;
    if (s5 == 0) {
        // 0x0056c83c
        charge(ctx, 3);
        jal(ctx, 0x56C83Cu, gen::fn_rfdir_searchPath_0056c5f0);
        s5 = v0;
    }
    // 0x0056c848
    charge(ctx, 12);
    jal(ctx, 0x56C848u, gen::fn_sub_56ABE0_0056abe0);
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

// 0x0056CA20 sub_56CA20 -- 20 bytes; frame 0x10: ra sp+0x0
// A ROFS device-table entry: tail call to ROFS_GetNumTr.
void sub_56CA20(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0056ca20
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_ROFS_GetNumTr_00566050(ctx);  // tail call
}

// 0x0056CA38 sub_56CA38 -- 40 bytes; frame 0x10: ra sp+0x0
// A ROFS device-table entry: ROFS_ChangeDir, 0 on success and -1 otherwise.
void sub_56CA38(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056ca38
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x56CA40u, gen::fn_ROFS_ChangeDir_00565b90);
    v1 = si(-1);
    ld(ra, sp, 0x0);
    if (v0 == 0) v1 = 0;
    v0 = v1;
    sp = addiu(sp, 0x10);
}

// 0x0056CB58 sub_56CB58 -- 92 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// The "ROFS" device's delete-volume entry: -1 for the device name itself, else ROFS_DelVolume and, on success,
// sub_555D70.
void sub_56CB58(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056cb58
    enter(ctx, 9);  // entry check point + this block's cycles
    a1 = 0x7C0000;
    sp = addiu(sp, -0x10);
    a1 = addiu(a1, 30616);  // "ROFS"
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x56CB6Cu, gen::fn_strcmp_00524128);
    a0 = s0;
    if (v0 == 0) {
        // 0x0056cb7c
        charge(ctx, 2);
        v0 = si(-1);
        goto L_0056cba4;
    }
    // 0x0056cb88
    charge(ctx, 4);
    jal(ctx, 0x56CB88u, gen::fn_ROFS_DelVolume_00566488);
    if (v0 != 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0056cb98
        charge(ctx, 3);
        a0 = s0;
        jal(ctx, 0x56CB98u, gen::fn_sub_555D70_00555d70);
        v0 = 0;
    L_0056cba4:
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    }
    // 0x0056cba8 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

}  // namespace p3fes::game
