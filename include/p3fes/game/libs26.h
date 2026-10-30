// Phase 5 slice libs26: SCE runtime and CRI leftovers that no probe reaches (0x4C72D8-0x56CB58): the DMAC channel
// helpers, the sceMpeg MPEG-2 extension parsers, the kernel call wrappers (`syscall` stubs: $v1 = the call number,
// negative for the interrupt-context variants), the SIF RPC data / bind / request handlers and their retry alarms,
// the file-I/O RPC wrappers, the IOP heap queries, the TLB set-up and miss handler, the CD/DVD, pad, sound-remote and
// DBC RPC calls, and the ADXF / ROFS directory helpers. Register-ABI bodies started from p3fes_handgen (arguments in
// $a0.., the result in $v0; every statement, charge and check point is the generator's:
// game/include/p3fes/game/hg_cpu.h). Each declaration carries the function's role, read from the instructions (the
// SCE names are symbols/' names; the public SDK's argument names are used in the roles only). The offsets below are
// the ones the bodies use by name; the ROFS #DirLst# list is cri_rofs.h's RofsDirLstHdr / RofsDirLstEnt.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace libs26 {
// A DMAC channel's registers (the channel base in $a0: 0x1000x000)
namespace dmac {
constexpr s32 kChcr = 0;   // control: DIR bit 0, MOD bits 2-3, STR bit 8
constexpr s32 kMadr = 16;  // memory address (-1 = keep: sceDmaSendI / RecvI do not overwrite it)
constexpr s32 kQwc = 32;   // quadword count
constexpr u32 kStadr = 0x1000E060u;  // D_STADR, the stall address (sceDmaPutStallAddr)
}  // namespace dmac
// The IPU registers the sceMpeg extension parsers touch
namespace ipu {
constexpr u32 kCmd = 0x10002000u;   // IPU_CMD: SETIQ 0x50000000 (intra) / 0x58000000 (non-intra)
constexpr u32 kCtrl = 0x10002010u;  // IPU_CTRL: _sequenceExtension clears bit 23 (MP1)
}  // namespace ipu
// The sceMpeg decoder words the extension parsers write (the decoder in $a0)
namespace mpeg {
constexpr s32 kProgressiveSeq = 332;  // _sequenceExtension: progressive_sequence
constexpr s32 kChromaFormat = 336;    // must be 1 (4:2:0)
constexpr s32 kWidth = 308;           // horizontal size, extension bits 12-13 added
constexpr s32 kHeight = 312;          // vertical size, extension bits 12-13 added
constexpr s32 kBitRate = 324;         // bit-rate, extension << 18 added
constexpr s32 kVbvSize = 328;         // vbv buffer size, extension << 10 added
constexpr s32 kMatrixCoeffs = 340;    // _sequenceDisplayExtension: the last colour-description byte
constexpr s32 kDisplayW = 344;
constexpr s32 kDisplayH = 348;
constexpr s32 kPictStruct = 388;      // _pictureDisplayExtension reads: 3 = frame picture
constexpr s32 kTopFirst = 392;        // top_field_first
constexpr s32 kRepeatFirst = 404;     // repeat_first_field
constexpr s32 kFcoH = 412;            // _pictureDisplayExtension: frame-centre offsets, 3 x s32 each
constexpr s32 kFcoV = 424;
constexpr s32 kIpuFlag = 2088;        // _quantMatrixExtension: set to 1 with each SETIQ
constexpr s32 kIpuWord = 2092;        // set to 0x50000000 with each SETIQ (for both matrices)
constexpr s32 kLoadIntraQ = 2128;     // the load_intra_quantiser_matrix flag read
constexpr s32 kLoadNonIntraQ = 2132;  // the load_non_intra_quantiser_matrix flag read
constexpr s32 kSeqExtSeen = 2136;     // _sequenceExtension sets it to 1
}  // namespace mpeg
// A 64-byte SIF RPC packet as the EE answers the IOP with (command 0x80000008 or a DMA)
namespace sifpkt {
constexpr s32 kReqPkt = 20;     // copied from the request
constexpr s32 kReqAddr = 28;    // copied from the request
constexpr s32 kAnswerCmd = 32;  // 0x80000009 (bind), 0x8000000A (call), 0x8000000C (other data)
constexpr s32 kArg0 = 36;
constexpr s32 kArg1 = 40;
constexpr s32 kArg2 = 44;
}  // namespace sifpkt
}  // namespace libs26

// 0x4C72D8. A 4-byte fragment the symbol map names as a function: one `dsra32 $v0, $v0, 0` that runs on into the next
// symbol (0x4C72DC), which this build does not treat as reachable; the body ends there.
void _dispRefImage_0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x4FAC08. sceDmaPutStallAddr(addr): swaps the DMAC stall address register D_STADR (0x1000E060): the old value in
// $v0, `addr` stored.
void sceDmaPutStallAddr(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x4FAD00. sceDmaSendI(ch, addr, qwc): waits for the channel (WaitDma), stores the checked address (CheckAddress) in
// MADR unless MADR holds -1, QWC = qwc, then CHCR = (CHCR & ~0xC) | 0x109 (STR, MOD = 2 interleave, DIR = from
// memory).
void sceDmaSendI(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x4FAD78. sceDmaRecv(ch): waits for the channel, QWC = 0, then CHCR = ((CHCR & ~0xC) | 4) & ~1 | 0x100 (STR, MOD =
// 1 chain, DIR = to memory).
void sceDmaRecv(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x4FAE40. sceDmaRecvI(ch, addr, qwc): as sceDmaSendI with DIR cleared (to memory): CHCR = ((CHCR & ~0xC) | 8) & ~1
// | 0x100.
void sceDmaRecvI(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x4FAEF8. sceDmaWatch(ch, addr, mode, count): mode 1 returns MADR < addr; any other mode passes (ch, addr, count)
// on to WatchDma and returns 0.
void sceDmaWatch(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x4FAFC8. sceDmaRestart(ch, chcr): writes `chcr` to the channel's CHCR and returns the old STR bit (bit 8).
void sceDmaRestart(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x4FF378. MPEG-2 sequence_extension (sceMpeg decoder, $a0 = the decoder): clears IPU_CTRL bit 23, reads 28 bits
// (profile/level, progressive, chroma format, size extensions), requires 4:2:0 ("_chroma_format needs to be 1: 420"),
// reads 16 more bits and checks the profile/level byte against 0x48 / 0x58 / 0x44, then folds the extension bits into
// the picture size and bit-rate words (+308 / +312 / +324 / +328).
void _sequenceExtension(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x4FF4B8. MPEG-2 quant_matrix_extension: for each of the intra / non-intra load flags, waits for the IPU, sends
// SETIQ (0x50000000 / 0x58000000) through IPU_CMD and records the command; the chroma matrices are not supported
// (_sceMpegError).
void _quantMatrixExtension(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x4FF5A0. Reports "_sequenceScalableExtension() is not implemented" (tail call to _sceMpegError).
void _sequenceScalableExtension(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x4FF7A8. Reports "_pictureSpatialScalableExtension is not supported" (tail call to _sceMpegError).
void _pictureSpatialScalableExtension(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x4FFB88. MPEG-2 sequence_display_extension: video format (3 bits), the optional colour description (3 x 8 bits,
// the last kept at +340), display width (14 bits, +344), a marker bit and display height (14 bits, +348).
void _sequenceDisplayExtension(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x4FFC18. MPEG-2 copyright_extension: skips its 1+8+1+7+1+20+1+22+1+22 bits.
void _copyrightExtension(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x4FFCB0. MPEG-2 picture_display_extension: the number of frame-centre offsets (1, 2 or 3 from the progressive /
// picture-structure / repeat-first-field words), then each horizontal and vertical offset (16 bits + marker) into the
// arrays at +412 and +424.
void _pictureDisplayExtension(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x502D40. Kernel call wrapper: $v1 = 0, `syscall`, the kernel's $v0 returned. reserved kernel call 0 (FullReset).
void RFU000_FullReset(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x502D50. Kernel call wrapper: $v1 = 1, `syscall`, the kernel's $v0 returned. ResetEE(mask): reset the EE units
// named in the mask.
void ResetEE(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x502D70. Kernel call wrapper: $v1 = 3, `syscall`, the kernel's $v0 returned. reserved kernel call 3.
void RFU003(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x502D90. Kernel call wrapper: $v1 = 5, `syscall`, the kernel's $v0 returned. reserved kernel call 5.
void RFU005(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x502DC0. Kernel call wrapper: $v1 = 8, `syscall`, the kernel's $v0 returned. reserved kernel call 8.
void RFU008(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x502DD0. Kernel call wrapper: $v1 = 9, `syscall`, the kernel's $v0 returned. reserved kernel call 9.
void RFU009(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x502DE0. Kernel call wrapper: $v1 = 10, `syscall`, the kernel's $v0 returned. AddSbusIntcHandler(cause, handler).
void AddSbusIntcHandler(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x502DF0. Kernel call wrapper: $v1 = 11, `syscall`, the kernel's $v0 returned. RemoveSbusIntcHandler(cause).
void RemoveSbusIntcHandler(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x502E00. Kernel call wrapper: $v1 = 12, `syscall`, the kernel's $v0 returned. Interrupt2Iop(cause): raise an SBUS
// interrupt on the IOP.
void Interrupt2Iop(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x502E30. Kernel call wrapper: $v1 = 15, `syscall`, the kernel's $v0 returned. SetVInterruptHandler(cause,
// handler).
void SetVInterruptHandler(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x502EE0. Kernel call wrapper: $v1 = 252, `syscall`, the kernel's $v0 returned. SetAlarm(ticks, handler, arg): an
// alarm id or a negative error.
void SetAlarm(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x502EF0. Kernel call wrapper: $v1 = 253, `syscall`, the kernel's $v0 returned. ReleaseAlarm(id).
void ReleaseAlarm(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x502F40. Kernel call wrapper: $v1 = -254, `syscall`, the kernel's $v0 returned. iSetAlarm(ticks, handler, arg),
// interrupt context.
void iSetAlarm(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x502F50. Kernel call wrapper: $v1 = -255, `syscall`, the kernel's $v0 returned. iReleaseAlarm(id), interrupt
// context.
void iReleaseAlarm(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x502F90. Kernel call wrapper: $v1 = 35, `syscall`, the kernel's $v0 returned. ExitThread(): end the calling
// thread.
void ExitThread(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x502FC0. Kernel call wrapper: $v1 = -38, `syscall`, the kernel's $v0 returned. iTerminateThread(id), interrupt
// context.
void iTerminateThread(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x502FD0. Kernel call wrapper: $v1 = 39, `syscall`, the kernel's $v0 returned. DisableDispatchThread().
void DisableDispatchThread(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x502FE0. Kernel call wrapper: $v1 = 40, `syscall`, the kernel's $v0 returned. EnableDispatchThread().
void EnableDispatchThread(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503020. Kernel call wrapper: $v1 = -44, `syscall`, the kernel's $v0 returned. iRotateThreadReadyQueue(prio),
// interrupt context.
void _iRotateThreadReadyQueue(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503030. Kernel call wrapper: $v1 = 45, `syscall`, the kernel's $v0 returned. ReleaseWaitThread(id).
void ReleaseWaitThread(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503040. Kernel call wrapper: $v1 = -46, `syscall`, the kernel's $v0 returned. iReleaseWaitThread(id), interrupt
// context.
void iReleaseWaitThread(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x5030B0. Kernel call wrapper: $v1 = 53, `syscall`, the kernel's $v0 returned. CancelWakeupThread(id).
void CancelWakeupThread(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x5030C0. Kernel call wrapper: $v1 = -54, `syscall`, the kernel's $v0 returned. iCancelWakeupThread(id), interrupt
// context.
void iCancelWakeupThread(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503100. Kernel call wrapper: $v1 = -58, `syscall`, the kernel's $v0 returned. iResumeThread(id), interrupt
// context.
void iResumeThread(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503110. Kernel call wrapper: $v1 = 59, `syscall`, the kernel's $v0 returned. JoinThread (kernel call 59).
void JoinThread(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503120. Kernel call wrapper: $v1 = 60, `syscall`, the kernel's $v0 returned. reserved kernel call 60 (the C
// runtime's InitMainThread slot).
void RFU060(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503130. Kernel call wrapper: $v1 = 61, `syscall`, the kernel's $v0 returned. reserved kernel call 61 (the C
// runtime's InitHeap slot).
void RFU061(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503150. Kernel call wrapper: $v1 = 63, `syscall`, the kernel's $v0 returned. reserved kernel call 63.
void RFU063(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x5031C0. Kernel call wrapper: $v1 = -70, `syscall`, the kernel's $v0 returned. iPollSema(id), interrupt context.
void iPollSema(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x5031D0. Kernel call wrapper: $v1 = 71, `syscall`, the kernel's $v0 returned. ReferSemaStatus(id, status).
void ReferSemaStatus(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x5031E0. Kernel call wrapper: $v1 = -72, `syscall`, the kernel's $v0 returned. iReferSemaStatus(id, status),
// interrupt context.
void iReferSemaStatus(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x5031F0. Kernel call wrapper: $v1 = 73, `syscall`, the kernel's $v0 returned. reserved kernel call 73.
void RFU073(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503220. Kernel call wrapper: $v1 = 76, `syscall`, the kernel's $v0 returned. GetGsHParam(...).
void GetGsHParam(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503230. Kernel call wrapper: $v1 = 77, `syscall`, the kernel's $v0 returned. GetGsVParam(...).
void GetGsVParam(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503240. Kernel call wrapper: $v1 = 78, `syscall`, the kernel's $v0 returned. SetGsHParam(...).
void SetGsHParam(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503250. Kernel call wrapper: $v1 = 79, `syscall`, the kernel's $v0 returned. SetGsVParam(...).
void SetGsVParam(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503260. Kernel call wrapper: $v1 = 80, `syscall`, the kernel's $v0 returned. CreateEventFlag (reserved kernel
// call 80).
void RFU080_CreateEventFlag(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503270. Kernel call wrapper: $v1 = 81, `syscall`, the kernel's $v0 returned. DeleteEventFlag (reserved kernel
// call 81).
void RFU081_DeleteEventFlag(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503280. Kernel call wrapper: $v1 = 82, `syscall`, the kernel's $v0 returned. SetEventFlag (reserved kernel call
// 82).
void RFU082_SetEventFlag(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503290. Kernel call wrapper: $v1 = -83, `syscall`, the kernel's $v0 returned. iSetEventFlag (reserved kernel call
// 83), interrupt context.
void RFU083_iSetEventFlag(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x5032A0. Kernel call wrapper: $v1 = 84, `syscall`, the kernel's $v0 returned. ClearEventFlag (reserved kernel call
// 84).
void RFU084_ClearEventFlag(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x5032B0. Kernel call wrapper: $v1 = -85, `syscall`, the kernel's $v0 returned. iClearEventFlag (reserved kernel
// call 85), interrupt context.
void RFU085_iClearEventFlag(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x5032C0. Kernel call wrapper: $v1 = 86, `syscall`, the kernel's $v0 returned. WaitEventFlag (reserved kernel call
// 86).
void RFU086_WaitEvnetFlag(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x5032D0. Kernel call wrapper: $v1 = 87, `syscall`, the kernel's $v0 returned. PollEventFlag (reserved kernel call
// 87).
void RFU087_PollEvnetFlag(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x5032E0. Kernel call wrapper: $v1 = -88, `syscall`, the kernel's $v0 returned. iPollEventFlag (reserved kernel
// call 88), interrupt context.
void RFU088_iPollEvnetFlag(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x5032F0. Kernel call wrapper: $v1 = 89, `syscall`, the kernel's $v0 returned. ReferEventFlagStatus (reserved
// kernel call 89).
void RFU089_ReferEventFlagStatus(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503300. Kernel call wrapper: $v1 = -90, `syscall`, the kernel's $v0 returned. iReferEventFlagStatus (reserved
// kernel call 90), interrupt context.
void RFU090_iReferEventFlagStatus(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503310. Kernel call wrapper: $v1 = 91, `syscall`, the kernel's $v0 returned. reserved kernel call 91.
void RFU091(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503320. Kernel call wrapper: $v1 = 92, `syscall`, the kernel's $v0 returned. EnableIntcHandler(cause).
void EnableIntcHandler(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503330. Kernel call wrapper: $v1 = -92, `syscall`, the kernel's $v0 returned. iEnableIntcHandler(cause),
// interrupt context.
void iEnableIntcHandler(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503340. Kernel call wrapper: $v1 = 93, `syscall`, the kernel's $v0 returned. DisableIntcHandler(cause).
void DisableIntcHandler(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503350. Kernel call wrapper: $v1 = -93, `syscall`, the kernel's $v0 returned. iDisableIntcHandler(cause),
// interrupt context.
void iDisableIntcHandler(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503360. Kernel call wrapper: $v1 = 94, `syscall`, the kernel's $v0 returned. EnableDmacHandler(channel).
void EnableDmacHandler(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503370. Kernel call wrapper: $v1 = -94, `syscall`, the kernel's $v0 returned. iEnableDmacHandler(channel),
// interrupt context.
void iEnableDmacHandler(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503380. Kernel call wrapper: $v1 = 95, `syscall`, the kernel's $v0 returned. DisableDmacHandler(channel).
void DisableDmacHandler(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503390. Kernel call wrapper: $v1 = -95, `syscall`, the kernel's $v0 returned. iDisableDmacHandler(channel),
// interrupt context.
void iDisableDmacHandler(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x5033A0. Kernel call wrapper: $v1 = 96, `syscall`, the kernel's $v0 returned. KSeg0(mode): set the KSEG0 cache
// mode.
void KSeg0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x5033B0. Kernel call wrapper: $v1 = 97, `syscall`, the kernel's $v0 returned. EnableCache(which).
void EnableCache(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x5033C0. Kernel call wrapper: $v1 = 98, `syscall`, the kernel's $v0 returned. DisableCache(which).
void DisableCache(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x5033D0. Kernel call wrapper: $v1 = 99, `syscall`, the kernel's $v0 returned. GetCop0(reg): a COP0 register
// through the kernel.
void GetCop0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x5033F0. Kernel call wrapper: $v1 = 102, `syscall`, the kernel's $v0 returned. CpuConfig(cfg).
void CpuConfig(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503400. Kernel call wrapper: $v1 = -103, `syscall`, the kernel's $v0 returned. iGetCop0(reg), interrupt context.
void iGetCop0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503410. Kernel call wrapper: $v1 = -104, `syscall`, the kernel's $v0 returned. iFlushCache(which), interrupt
// context.
void iFlushCache(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503420. Kernel call wrapper: $v1 = -106, `syscall`, the kernel's $v0 returned. iCpuConfig(cfg), interrupt
// context.
void iCpuConfig(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503440. Kernel call wrapper: $v1 = 108, `syscall`, the kernel's $v0 returned. SetCPUTimerHandler(handler).
void SetCPUTimerHandler(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503450. Kernel call wrapper: $v1 = 109, `syscall`, the kernel's $v0 returned. SetCPUTimer(compare).
void SetCPUTimer(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503460. Kernel call wrapper: $v1 = 110, `syscall`, the kernel's $v0 returned. SetOsdConfigParam2(buf, size,
// offset).
void SetOsdConfigParam2(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503470. Kernel call wrapper: $v1 = 111, `syscall`, the kernel's $v0 returned. GetOsdConfigParam2(buf, size,
// offset).
void GetOsdConfigParam2(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503490. Kernel call wrapper: $v1 = -112, `syscall`, the kernel's $v0 returned. iGsGetIMR(): the GS interrupt
// mask, interrupt context.
void iGsGetIMR(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x5034B0. Kernel call wrapper: $v1 = -113, `syscall`, the kernel's $v0 returned. iGsPutIMR(mask), interrupt
// context.
void iGsPutIMR(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x5034C0. Kernel call wrapper: $v1 = 114, `syscall`, the kernel's $v0 returned. SetPgifHandler(handler).
void SetPgifHandler(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x5034E0. Kernel call wrapper: $v1 = 116, `syscall`, the kernel's $v0 returned. reserved kernel call 116 (the slot
// _sceSetSyscall also uses).
void RFU116(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x5034F0. Kernel call wrapper: $v1 = 117, `syscall`, the kernel's $v0 returned. the kernel's debug print (kernel
// call 117).
void _print(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x503510. Kernel call wrapper: $v1 = -118, `syscall`, the kernel's $v0 returned. isceSifDmaStat(id): a SIF DMA
// transfer's state, interrupt context.
void isceSifDmaStat(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x5035A0. Kernel call wrapper: $v1 = 125, `syscall`, the kernel's $v0 returned. PSMode() (kernel call 125).
void PSMode(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x5035B0. Kernel call wrapper: $v1 = 126, `syscall`, the kernel's $v0 returned. MachineType() (kernel call 126).
void MachineType(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x504140. iSuspendThread(id): asks the kernel for the current thread (kernel call -47); if `id` is not the current
// thread, the kernel suspend (_sce_iSuspendThread). Otherwise, with the dispatcher enabled (0x77F498 == 0) and the id
// below 256, it queues a suspend request (type 2, id) in the 512-entry ring at 0x966108 and signals the request
// semaphore 0x966100; returns the id, or -1.
void iSuspendThread(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x504418. The DelayThread alarm handler: signals the semaphore passed as the alarm argument ($a3), then `sync` +
// `ei`; returns 0.
void _DelayThreadHandler(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x506110. isceSifSetDma(desc, n): the SIF DMA in interrupt context: through sceSifSetDmaInternal (with $a2 = 1)
// when the internal path is armed (0x77F4A8 != 0), else the kernel call _isceSifSetDma.
void isceSifSetDma(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x506C78. The retry alarm of _request_rdata: resends the 64-byte packet ($a3) as SIF command 0x80000008 with its
// three words +36 / +40 / +44; returns 2048 (re-arm) when the send failed, else 0.
void _alarm_rdata(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x506CB8. SIF command handler 0x8000000C (the IOP asks the EE to send it data): takes a free packet (the rpc data's
// second free list when bit 2 of +16 is set), copies the request's ids and source / destination / size into it and
// answers with SIF command 0x80000008; on a failed send it re-arms through iSetTimerAlarm(2048, _alarm_rdata).
void _request_rdata(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x506D88. sceSifGetOtherData(rd, src, dst, size, mode): a packet from the RPC pool, filled with (src, dst, size)
// and sent as SIF command 0x8000000C; without mode bit 0 it blocks on a fresh semaphore until the IOP answers. 0 on
// success, -1 no packet, -2 send failed, -3 no semaphore.
void sceSifGetOtherData(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x506F40. The retry alarm of _request_bind: resends the 64-byte packet ($a3) as SIF command 0x80000008; returns
// 2048 (re-arm) when the send failed, else 0.
void _alarm_bind(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x506F80. SIF command handler 0x80000009 (bind): a free packet with the request's ids, the server found by
// _search_svdata (its pointer and its word +8, or zeros) and command 0x80000008 back to the IOP; on a failed send it
// re-arms through iSetTimerAlarm(2048, _alarm_bind).
void _request_bind(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x507758. Runs one queued RPC request on the EE server: calls the server function (+4) with (fno +36, buffer +8,
// size +12), writes the buffer and the result back from the data cache, then answers the IOP: SIF command 0x8000000A
// by DMA with the result copied to the receive address (retrying with a 0x100000 spin) when +48 is 0, else through
// the command path until it is sent.
void sceSifExecRequest(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x508128. The file-I/O power-off interrupt handler: calls the registered callback (*$a1) with its argument (+4)
// under the file-I/O library's $gp (0x969CC0), then `sync` + `ei`.
void _sceFs_Poff_Intr(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x508440. sceFsSetIopBuf(size, count) (file-I/O RPC 254): checks the size (16 KiB aligned, at most 1 MiB) and count
// (1..32) with no file open; returns the IOP's answer, -16 (files open), -22 (bad argument), -11 (RPC failed) or
// 0xFFFEFFFC (old IOP module).
void sceFsSetIopBuf(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x508580. sceFsSetIopPrio(prio) (file-I/O RPC 253): the IOP file server's thread priority; the same checks and
// errors as sceFsSetIopBuf.
void sceFsSetIopPrio(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x509570. sceIoctl2(fd, cmd, arg, arglen, buf, buflen) (file-I/O RPC 26): the request block filled and sent with a
// fresh semaphore, then waited for; the answer, -22 / -9 for refused arguments, -11 when the RPC fails or is refused.
void sceIoctl2(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x509928. sceMkdir(path, mode) (file-I/O RPC 7): copies at most 1023 characters of the path into the request block
// 0x968500, sends it with a fresh semaphore and waits; the IOP's answer, or -11 (RPC failed or refused).
void sceMkdir(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x509B00. sceFormat(dev, blockdev, arg, arglen) (file-I/O RPC 14): the names and the argument copied into the
// request block 0x968500, sent with a fresh semaphore and waited for; the answer or -11.
void sceFormat(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x509D80. sceAddDrv(drv) (file-I/O RPC 15): the request sent with a fresh semaphore and waited for; the answer or
// -11.
void sceAddDrv(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x509F98. sceDclose(fd) (file-I/O RPC 10): closes a directory handle; the answer or -11.
void sceDclose(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x50A100. sceDread(fd, dirent) (file-I/O RPC 11): one directory entry into `dirent`; the answer or -11.
void sceDread(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x50A258. sceGetstat(path, stat) (file-I/O RPC 12): a file's status into `stat`; the answer or -11.
void sceGetstat(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x50A410. sceChstat(path, stat, mask) (file-I/O RPC 13): changes the masked status fields; the answer or -11.
void sceChstat(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x50A660. sceRename(old, new) (file-I/O RPC 17): both paths copied into the request block, sent and waited for; the
// answer or -11.
void sceRename(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x50AA38. sceMount(fsname, devname, flag, arg, arglen) (file-I/O RPC 20); the answer or -11.
void sceMount(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x50AF18. sceDevctl(dev, cmd, arg, arglen, buf, buflen) (file-I/O RPC, a 2076-byte request): device control with an
// output buffer; the answer, -22 for refused arguments, -11 when the RPC fails.
void sceDevctl(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x50B1C0. sceSymlink(existing, new) (file-I/O RPC 24); the answer or -11.
void sceSymlink(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x50B3B8. sceReadlink(path, buf, size) (file-I/O RPC 25): the link target into `buf`; the answer or -11.
void sceReadlink(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x50B7A8. sceSifLoadIopHeap(path, iop_addr) (IOP heap RPC 3): the path (at most 251 characters) and the address
// into the request 0x969DC0, then the answer word 0x969D40; 0 before the heap RPC is bound (0x77F558 < 0), -1 when
// the call fails.
void sceSifLoadIopHeap(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x50B898. sceSifQueryMemSize() (IOP heap RPC 5): the IOP memory size, 0 before the heap RPC is bound, -1 when the
// call fails.
void sceSifQueryMemSize(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x50B908. sceSifQueryMaxFreeMemSize() (IOP heap RPC 6): the largest free IOP block, 0 before the heap RPC is bound,
// -1 when the call fails.
void sceSifQueryMaxFreeMemSize(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x50CE40. InitTLB32MB(): prints the TLB layout, clears Wired, then writes the three TLB entry tables of the
// descriptor at 0x77FB98 (kernel / default / extended counts and table pointers) through _sce_SetTLBEntry, Exit(1)
// when an index passes 48, sets Wired and fills the rest with invalid entries at 0xE0000000 + 8 KiB steps; returns
// the first free index << 13.
void InitTLB32MB(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x50D040. The TLB-miss exception handler: saves every GPR (128-bit) to the frame 0x96B180, reads Status / Cause /
// EPC / BadVAddr, keeps EPC at 0x96B3A8, points EPC at _xlaunch, clears EXL and `eret`s into it.
void _kTLBException(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x50D140. Where _kTLBException returns to: calls the user TLB handler (0x77F898) on a private stack, makes kernel
// call -84, restores EPC, HI/LO and every GPR from 0x96B180, sets EXL and `eret`s to the faulting instruction.
void _xlaunch(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x50D478. Kernel call wrapper: $v1 = 90, `syscall`, the kernel's $v0 returned. the kernel copy call (kernel call
// 90; the C runtime's copy of the kernel patch path).
void _sceCopy_0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x50D6B0. Kernel call wrapper: $v1 = 116, `syscall`, the kernel's $v0 returned. SetSyscall(n, fn) (kernel call
// 116).
void _sceSetSyscall_1(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x50D6C0. Kernel call wrapper: $v1 = 90, `syscall`, the kernel's $v0 returned. the kernel copy call (kernel call
// 90), second copy.
void _sceCopy_1(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x50D708. Kernel call wrapper: $v1 = 91, `syscall`, the kernel's $v0 returned. GetEntryAddress(n) (kernel call 91).
void _sceGetEntryAddress_0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x50D830. Kernel call wrapper: $v1 = 90, `syscall`, the kernel's $v0 returned. the kernel copy call (kernel call
// 90), third copy.
void _sceCopy_2(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x50D870. Kernel call wrapper: $v1 = 116, `syscall`, the kernel's $v0 returned. SetSyscall(n, fn) (kernel call
// 116), second copy.
void _sceSetSyscall_2(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x50FA48. The CD/DVD library's exit: cancels a pending callback (sceCdCbfunc_num = -1, signal its semaphore),
// deletes the four library semaphores and sends SIF command 0x80000012 with interrupts off.
void cdvd_exit(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x510748. The old sceCdDiskReady(mode) through RPC 0x8000059A: binds the server once (retrying with a spin), sends
// `mode` and returns the drive state word; 6 when the command semaphore is busy (-1 for mode 8).
void sceCdDiskReady_old(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x510D60. sceCdSeek(lsn) (N-command 9 through RPC 5): stores the LSN, arms the callback (number 4) and sends; 1
// when sent, 0 when the drive is not ready or the command was refused.
void sceCdSeek(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x510F88. sceCdBreak() (S-command 30 through RPC 22): sends the break and returns the IOP's answer word, 0 when
// refused.
void sceCdBreak(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x511288. The pad DMA interrupt handler: calls the registered callback (0x782750) with the handler argument's word
// +12 under the pad library's $gp (0x96DF80), then `sync` + `ei`.
void _pad_intr_hdr(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x512710. scePadSetDmaCallback(fn): installs (or with 0 removes) the pad DMA callback, telling the IOP pad server
// through RPC 1 when the state changes; returns the previous callback.
void scePadSetDmaCallback(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x512E48. sceSdRemoteCallbackQuit(): stops the sound-library callback server: four sceSdRemote calls, clears the
// callback table 0x7827A0..0x7827C0, removes the RPC server and its queue and terminates / deletes its thread
// (0x7827C4, then -1); 0, or -1 on any failure.
void sceSdRemoteCallbackQuit(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x51CDD8. sceDbcSearchPortSpecific(req) (DBC RPC 0x8000131D, function 2): sends the request's words +8 / +12 under
// the library semaphore 0x997000 and returns the answer word, -1 on an RPC error.
void sceDbcSearchPortSpecific(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x53B760. ADXF partition load and wait: starts adxf_LoadPartitionNw, then runs ADXM_ExecMain and sub_53B680 until
// sub_53C2A0 reports state 3 (0) or 4 (-1); the start's error as is.
void sub_53B760(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x53C200. Stops the ADXF handle at 0x7853D0 (sub_53D450) when it is open and not idle (adxf_GetStat != 1), then
// tail-calls sub_53C198.
void sub_53C200(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x55FA40. Releases the table of 24-byte records at 0x7A9450 (count 0x7A93F0): each record's three objects
// (sub_564038, the virtual release at vtable +12, sub_564830), then memset; and the IOP block 0x7A93FC when the flag
// 0x7A9404 is 1.
void sub_55FA40(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x560698. Drops one reference (0x7A943C) of the sound / stream system (nothing when the mode word 0x7A93F8 is 1 and
// the record count 0x7A93F0 is not positive); at zero frees its IOP blocks (0x7A940C, 0x7A9444) and the handle
// 0x7ABE90 and runs the five sub-system finalisers.
void sub_560698(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x5646C0. Drops one reference (0x7B1ABC); at zero releases the handle 0x7B1D50 (sub_5598B0), frees the IOP block
// 0x7B1AC4 and tail-calls sub_559B98.
void sub_5646C0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x565B90. ROFS_ChangeDir(path): sub_569810, then tail call ROFS_LoadDir(path, 0, 0).
void ROFS_ChangeDir(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x567750. Reads a volume's root directory: the ISO directory record at +156 of the volume descriptor
// (RFMAI_CopyStructCdDr), its big-endian LBA and size, then RFDIR_GetDirEnt into the list header $a2 with the work
// buffer g_rofs_work+72; -105 when the list stays empty.
void rfmai_readRootDirRec(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x569D90. RFMAI_DescrambleG(hn, nsct, ctx): deciphers `nsct` sectors of a scrambled stream (rfmai_decipherSectors)
// and advances its sector counter (+4); the ROFS error -100 through sub_569730 ("RFMAI_CancelScrambleG") for a null
// handle, negative count, null or unset context.
void RFMAI_DescrambleG(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x56BDC0. Fills a #DirLst# list from ISO directory sectors: the cached list when its LBA and name match; a shared
// list copied; otherwise reads up to two sectors at a time (RFMAI_ReadWG + decipher) and parses records
// (rfdir_getOneDirEnt) until the capacity or the directory size is reached; -100 bad arguments, -109 the list
// overflowed, or the read error.
void rfdir_getDirEnt(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x56C188. Parses an in-memory ISO directory (`nsct` sectors) into a #DirLst# list (count, capacity, entries at
// +24): 0, -109 when it overflowed, -110 when it ran past the buffer.
void RFDIR_SetDirEnt(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x56C5F0. ISO 9660 path-table walk: reads the table a sector at a time, matches each '/' or '\' separated component
// (rfdirStrncmpi) against the records whose parent is the previous match, and returns the directory's LBA (0 not
// found, the read error through sub_569730).
void rfdir_searchPath(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x56C7E8. RFDIR_SearchPath: under the PFS lock (RFPFS_PfsLock / sub_56ABE0), rfdir_searchPath unless the lock call
// failed; its result.
void RFDIR_SearchPath(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x56CA20. A ROFS device-table entry: tail call to ROFS_GetNumTr.
void sub_56CA20(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x56CA38. A ROFS device-table entry: ROFS_ChangeDir, 0 on success and -1 otherwise.
void sub_56CA38(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// 0x56CB58. The "ROFS" device's delete-volume entry: -1 for the device name itself, else ROFS_DelVolume and, on
// success, sub_555D70.
void sub_56CB58(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

}  // namespace p3fes::game
