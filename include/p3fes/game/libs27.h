// Slice libs27 (game/src/lib/libs27.cpp): the remaining SDK client entry points (SIF loadfile / heap RPC, the TLB and
// scratchpad syscall wrappers, LoadExecPS2 / ExecOSD, the timer-1 helpers, the CD / pad / DBC / sound RPC clients, the
// DTX server thread), two ADXF lock wrappers and the ROFS mount-level calls (rofs_mai.c). Register-ABI bodies:
// arguments in $a0.., the result in $v0.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace libs27 {
// SIF clients (the bodies' globals, read from the instructions).
constexpr u32 kHeapBound = 0x77F558u;     // s32: < 0 while the IOP heap RPC client is not bound
constexpr u32 kHeapReply = 0x969D40u;     // the heap RPC's 4-byte reply
constexpr u32 kHeapArg = 0x969D80u;       // the heap RPC's argument word
constexpr u32 kLfBuf = 0x969EC0u;         // the loadfile RPC's 512-byte send / receive buffer
constexpr s32 kLfErrBind = -0x10000;      // _lf_bind failed
constexpr s32 kLfErrRpc = -0x10001;       // sceSifCallRpc failed
constexpr s32 kLfErrType = -0x10002;      // sceSif{Get,Set}IopAddr: bad access type
constexpr s32 kLfErrVersion = -0x10004;   // _lf_version: the IOP side is too old
// Timer 1 (the kernel library's timer helpers).
constexpr u32 kT1Count = 0x10001000u;     // T1_COUNT
constexpr u32 kT1Mode = 0x10001010u;      // T1_MODE: bits 0-1 clock source, bit 7 overflow flag, bit 11 overflow pending
constexpr u32 kTimerAlloc = 0x780B50u;    // s32: < 0 when the timer is not allocated
constexpr u32 kTimerOverflows = 0x780B48u;  // u64: the overflow count (the high part of the 64-bit count)
constexpr u64 kTimerErrNotAlloc = 0xFFFFFFFF80008001ull;  // sub_50DEC0's result when not allocated
// CD, pad, DBC.
constexpr u32 kCdCallback = 0x96DA00u;    // the CD completion callback; +4 its $gp
constexpr u32 kPadOpen = 0x782748u;       // nonzero while scePadInit's RPC is open
constexpr u32 kPadPorts = 0x96DD20u;      // port records: + 112 port + 28 slot, first word = open
constexpr u32 kPadRpcBuf = 0x96DF00u;     // the pad RPC buffer: +0 function, +4 port, +8 slot, +12 reply / param
constexpr u32 kSdDma = 0x96DFC0u;         // sceSdTransToIOP's SIF DMA record (src, dst, size, attr)
constexpr u32 kDbcSema = 0x997000u;       // the DBC semaphore id
constexpr u32 kDbcRpcBuf = 0x996840u;     // the DBC RPC buffer (144 bytes)
constexpr u32 kDbcStateLive = 0x996F40u;  // the socket-state table the IOP writes (64 bytes)
constexpr u32 kDbcState = 0x996FC0u;      // the copy sceDbcGetDepNumber reads (one word per socket)
constexpr s32 kDbcErrNotConnected = -12;
// ROFS (rofs_mai.c): the error codes the bodies report through sub_569730.
constexpr s32 kRofsErrParam = -100;
constexpr s32 kRofsErrNoHandle = -102;
constexpr s32 kRofsErrDevName = -103;
constexpr s32 kRofsErrVolume = -105;
constexpr s32 kRofsErrNotDir = -106;
constexpr s32 kRofsErrNoEntry = -107;
constexpr s32 kRofsErrDirrec = -111;
constexpr u32 kRofsWorkHnCount = 4;       // s32: handle slots in the ROFS work area
constexpr u32 kRofsWorkHandles = 36;      // the handle array's address (60-byte handles)
constexpr u32 kRofsWorkErrCb = 64;        // the error callback (and +68 its object)
constexpr u32 kRofsHnSize = 60;
constexpr u32 kRofsHnVolume = 28;         // the handle's RofsVolume*
constexpr u32 kRofsHnActive = 52;         // s16: 0 free, 1 open
constexpr u32 kRofsVolDirrec = 44;        // 8 bytes ROFS_CheckDirrecFile compares
}  // namespace libs27

void sceSifQueryTotalFreeMemSize(EEContext& ctx);  // 0x50B978 (register ABI: arguments in $a0.., the result in $v0)
void sceSifQueryBlockTopAddress(EEContext& ctx);  // 0x50B9E8 (register ABI: arguments in $a0.., the result in $v0)
void sceSifQueryBlockSize(EEContext& ctx);  // 0x50BA68 (register ABI: arguments in $a0.., the result in $v0)
void sceSifStopModule(EEContext& ctx);  // 0x50BEB8 (register ABI: arguments in $a0.., the result in $v0)
void sceSifUnloadModule(EEContext& ctx);  // 0x50C0C0 (register ABI: arguments in $a0.., the result in $v0)
void sceSifSearchModuleByName(EEContext& ctx);  // 0x50C150 (register ABI: arguments in $a0.., the result in $v0)
void sceSifSearchModuleByAddress(EEContext& ctx);  // 0x50C1F0 (register ABI: arguments in $a0.., the result in $v0)
void sceSifLoadModuleBuffer(EEContext& ctx);  // 0x50C280 (register ABI: arguments in $a0.., the result in $v0)
void sceSifLoadStartModuleBuffer(EEContext& ctx);  // 0x50C2A0 (register ABI: arguments in $a0.., the result in $v0)
void sceSifLoadStartModule(EEContext& ctx);  // 0x50C508 (register ABI: arguments in $a0.., the result in $v0)
void sceSifLoadElfPart(EEContext& ctx);  // 0x50C630 (register ABI: arguments in $a0.., the result in $v0)
void sceSifLoadElf(EEContext& ctx);  // 0x50C650 (register ABI: arguments in $a0.., the result in $v0)
void sceSifGetIopAddr(EEContext& ctx);  // 0x50C678 (register ABI: arguments in $a0.., the result in $v0)
void sceSifSetIopAddr(EEContext& ctx);  // 0x50C768 (register ABI: arguments in $a0.., the result in $v0)
void sceSifIsAliveIop(EEContext& ctx);  // 0x50C9A0 (register ABI: arguments in $a0.., the result in $v0)
void PutTLBEntry(EEContext& ctx);  // 0x50CD40 (register ABI: arguments in $a0.., the result in $v0)
void iPutTLBEntry(EEContext& ctx);  // 0x50CD50 (register ABI: arguments in $a0.., the result in $v0)
void iSetTLBEntry(EEContext& ctx);  // 0x50CDA0 (register ABI: arguments in $a0.., the result in $v0)
void GetTLBEntry(EEContext& ctx);  // 0x50CDB0 (register ABI: arguments in $a0.., the result in $v0)
void iGetTLBEntry(EEContext& ctx);  // 0x50CDC0 (register ABI: arguments in $a0.., the result in $v0)
void ProbeTLBEntry(EEContext& ctx);  // 0x50CDD0 (register ABI: arguments in $a0.., the result in $v0)
void iProbeTLBEntry(EEContext& ctx);  // 0x50CDE0 (register ABI: arguments in $a0.., the result in $v0)
void ExpandScratchPad(EEContext& ctx);  // 0x50CDF0 (register ABI: arguments in $a0.., the result in $v0)
void LoadExecPS2(EEContext& ctx);  // 0x50DA10 (register ABI: arguments in $a0.., the result in $v0)
void ExecOSD(EEContext& ctx);  // 0x50DA80 (register ABI: arguments in $a0.., the result in $v0)
void sub_50DEC0(EEContext& ctx);  // 0x50DEC0 (register ABI: arguments in $a0.., the result in $v0)
void sub_50DF80(EEContext& ctx);  // 0x50DF80 (register ABI: arguments in $a0.., the result in $v0)
void sub_50E558(EEContext& ctx);  // 0x50E558 (register ABI: arguments in $a0.., the result in $v0)
void sceCdCallback(EEContext& ctx);  // 0x50F630 (register ABI: arguments in $a0.., the result in $v0)
void sceCdSearchFile(EEContext& ctx);  // 0x50FF38 (register ABI: arguments in $a0.., the result in $v0)
void sceCdGetDiskType(EEContext& ctx);  // 0x510EC8 (register ABI: arguments in $a0.., the result in $v0)
void scePadEnd(EEContext& ctx);  // 0x5113C8 (register ABI: arguments in $a0.., the result in $v0)
void scePadPortClose(EEContext& ctx);  // 0x511778 (register ABI: arguments in $a0.., the result in $v0)
void scePadSetVrefParam(EEContext& ctx);  // 0x5124A0 (register ABI: arguments in $a0.., the result in $v0)
void scePadGetPortMax(EEContext& ctx);  // 0x512570 (register ABI: arguments in $a0.., the result in $v0)
void scePadGetSlotMax(EEContext& ctx);  // 0x5125D8 (register ABI: arguments in $a0.., the result in $v0)
void scePadSetWarningLevel(EEContext& ctx);  // 0x5126A8 (register ABI: arguments in $a0.., the result in $v0)
void sceSdTransToIOP(EEContext& ctx);  // 0x512918 (register ABI: arguments in $a0.., the result in $v0)
void sceDbcGetIopDmabuff(EEContext& ctx);  // 0x51C6A0 (register ABI: arguments in $a0.., the result in $v0)
void sceDbcGetDepNumber(EEContext& ctx);  // 0x51C960 (register ABI: arguments in $a0.., the result in $v0)
void sceDbcInitSocket(EEContext& ctx);  // 0x51CBC8 (register ABI: arguments in $a0.., the result in $v0)
void sceDbcResetSocket(EEContext& ctx);  // 0x51CC78 (register ABI: arguments in $a0.., the result in $v0)
void sceDbcGetDeviceStatus(EEContext& ctx);  // 0x51CD28 (register ABI: arguments in $a0.., the result in $v0)
void sceDbcSRData(EEContext& ctx);  // 0x51CE98 (register ABI: arguments in $a0.., the result in $v0)
void sceDbcSendData(EEContext& ctx);  // 0x51D028 (register ABI: arguments in $a0.., the result in $v0)
void sceDbcSendData2(EEContext& ctx);  // 0x51D158 (register ABI: arguments in $a0.., the result in $v0)
void sceDbcReceiveData(EEContext& ctx);  // 0x51D460 (register ABI: arguments in $a0.., the result in $v0)
void sceSkSsQuit(EEContext& ctx);  // 0x51DAE0 (register ABI: arguments in $a0.., the result in $v0)
void sub_53D198(EEContext& ctx);  // 0x53D198 (register ABI: arguments in $a0.., the result in $v0)
void sub_53DF50(EEContext& ctx);  // 0x53DF50 (register ABI: arguments in $a0.., the result in $v0)
void sub_547998(EEContext& ctx);  // 0x547998 (register ABI: arguments in $a0.., the result in $v0)
void dtx_svr_proc(EEContext& ctx);  // 0x559508 (register ABI: arguments in $a0.., the result in $v0)
void RFMAI_UnMountG(EEContext& ctx);  // 0x5680D8 (register ABI: arguments in $a0.., the result in $v0)
void RFMAI_OpenRangeG(EEContext& ctx);  // 0x5685B8 (register ABI: arguments in $a0.., the result in $v0)
void RFMAI_LoadDirG(EEContext& ctx);  // 0x568E38 (register ABI: arguments in $a0.., the result in $v0)
void RFMAI_SetIsoDirG(EEContext& ctx);  // 0x569230 (register ABI: arguments in $a0.., the result in $v0)
void RFMAI_IsExistFile(EEContext& ctx);  // 0x5692E0 (register ABI: arguments in $a0.., the result in $v0)
void sub_569390(EEContext& ctx);  // 0x569390 (register ABI: arguments in $a0.., the result in $v0)
void sub_569420(EEContext& ctx);  // 0x569420 (register ABI: arguments in $a0.., the result in $v0)
void sub_5698B0(EEContext& ctx);  // 0x5698B0 (register ABI: arguments in $a0.., the result in $v0)
void RFMAI_GetScrambleInfG(EEContext& ctx);  // 0x569C28 (register ABI: arguments in $a0.., the result in $v0)
void ROFS_CheckDirrecFile(EEContext& ctx);  // 0x569EC0 (register ABI: arguments in $a0.., the result in $v0)
void sub_56C9A0(EEContext& ctx);  // 0x56C9A0 (register ABI: arguments in $a0.., the result in $v0)

}  // namespace p3fes::game
