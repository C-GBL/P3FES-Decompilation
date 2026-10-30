// Slice sce1: the pure parts of the Sony runtime libraries linked into the ELF (game/src/sce/, tests/game/test_sce1.cpp)
// -- libgraph's environment builders, libdma's helpers, libkernel's newlib glue / tty queue / small printf / SIF tables /
// alarm pool / version checks, libmc2's path helpers, two libdbc leaves. Every function is a p3fes_handgen body on the
// register ABI (arguments in $a0..$t3 / $f12.., the result in $v0 / $f0) with its recompiled entry point
// fn_<name>_<addr8> as the shim. Names are symbols/functions.json's (ADR-0009); [proposed] roles stand next to sub_ names.
//
// The Sony SDK is proprietary: nothing here comes from its sources or headers. The layouts below are read from the
// instructions; the GS register fields are those of the public GS register documentation (privileged registers PMODE /
// SMODE2 / DISPFB / DISPLAY / BGCOLOR, general registers FRAME / ZBUF / XYOFFSET / SCISSOR / TEST ..., the GIF tag and
// the VIF codes). tools/ours/types/deltas/sce1.json carries the same records for p3fes_types.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace sce {

// libgraph's mode record, returned by sceGsGetGParam (0x77F280; rw_leaves.h kGsGParam)
namespace gparam {
constexpr u32 kAddr = 0x0077F280u;
constexpr s32 kInterlace = 0x0;  // s16: 0 progressive, 1 interlaced (SMODE2.INT)
constexpr s32 kOmode = 0x2;      // s16: the video mode -- 2 NTSC, 3 PAL, 0x50 480p (the SetGsCrt mode numbers)
constexpr s32 kFfmode = 0x4;     // s16: 0 field, 1 frame (SMODE2.FFMD)
}  // namespace gparam

// sceGsSetDefDispEnv's display environment: five 64-bit privileged-register images (40 bytes)
namespace disp {
constexpr s32 kPmode = 0x00;
constexpr s32 kSmode2 = 0x08;
constexpr s32 kDispfb = 0x10;   // FBP 0-8, FBW 9-14, PSM 15-19, DBX 32-42, DBY 43-53
constexpr s32 kDisplay = 0x18;  // DX 0-11, DY 12-22, MAGH 23-26, MAGV 27-28, DW 32-43, DH 44-54
constexpr s32 kBgcolor = 0x20;
constexpr u32 kSize = 0x28;
constexpr u64 kPmodeValue = 0x66;  // EN2, CRTMD = 1, MMOD, AMOD
}  // namespace disp

// sceGsSetDefDrawEnv / sceGsSetDefDrawEnv2's draw environment: 8 A+D pairs {data, register address} (128 bytes)
namespace draw {
constexpr s32 kFrame = 0x00;       // FRAME_1 0x4C / FRAME_2 0x4D: FBP 0-8, FBW 16-21, PSM 24-29, FBMSK 32-63
constexpr s32 kZbuf = 0x10;        // ZBUF_1 0x4E / ZBUF_2 0x4F: ZBP 0-8, PSM 24-27, ZMSK 32
constexpr s32 kXyoffset = 0x20;    // XYOFFSET_1 0x18 / _2 0x19: OFX 0-15, OFY 32-47 (12.4 fixed point)
constexpr s32 kScissor = 0x30;     // SCISSOR_1 0x40 / _2 0x41: SCAX0 0-10, SCAX1 16-26, SCAY0 32-42, SCAY1 48-58
constexpr s32 kPrmodecont = 0x40;  // PRMODECONT 0x1A: AC bit 0
constexpr s32 kColclamp = 0x50;    // COLCLAMP 0x46: CLAMP bit 0
constexpr s32 kDthe = 0x60;        // DTHE 0x45: DTHE bit 0
constexpr s32 kTest = 0x70;        // TEST_1 0x47 / TEST_2 0x48: ZTE 16, ZTST 17-18
constexpr s32 kAddrOff = 0x08;     // each pair's register-address doubleword follows its data
constexpr u32 kSize = 0x80;
constexpr u32 kPairs = 8;          // the functions' return value
}  // namespace draw

// sceGsSetDefStoreImage's GS -> memory transfer packet (112 bytes): 4 VIF codes, a GIF tag, 6 A+D pairs
namespace store {
constexpr s32 kVifNop = 0x00;
constexpr s32 kVifMskpath3 = 0x04;  // 0x06008000
constexpr s32 kVifFlusha = 0x08;    // 0x13000000
constexpr s32 kVifDirect = 0x0C;    // 0x50000006: DIRECT, 6 qwords
constexpr s32 kGifTag = 0x10;       // NLOOP 5, EOP, NREG 1; REGS (+0x18) = 0xE (A+D)
constexpr s32 kBitbltbuf = 0x20;    // 0x50: SBP 0-13, SBW 16-21, SPSM 24-29
constexpr s32 kTrxpos = 0x30;       // 0x51: SSAX 0-10, SSAY 16-26
constexpr s32 kTrxreg = 0x40;       // 0x52: RRW 0-11, RRH 32-43
constexpr s32 kFinish = 0x50;       // 0x61
constexpr s32 kTrxdir = 0x60;       // 0x53: XDIR 1 = local -> host
constexpr u32 kSize = 0x70;
constexpr u32 kQwords = 7;          // the function's return value
}  // namespace store

// libdma's environment shadow (sceDmaGetEnv copies 20 bytes)
constexpr u32 kDmaEnvShadow = 0x00965AC8u;

// libkernel's tty input ring (QueueInit / QueuePeek*Done; the instance at 0x966540, pointer at 0x966668)
namespace ttyq {
constexpr u32 kInstance = 0x00966540u;
constexpr u32 kPointer = 0x00966668u;
constexpr s32 kCapacity = 0x0;
constexpr s32 kCount = 0x4;
constexpr s32 kReadPtr = 0x8;
constexpr s32 kWritePtr = 0xC;
constexpr s32 kData = 0x10;
}  // namespace ttyq
constexpr u32 kTtyInitFlag = 0x0077F490u;   // sceResetttyinit clears it
constexpr u32 kDeci2Line = 0x00966900u;     // deci2Putchar's 128-byte line buffer
constexpr u32 kDeci2LineFill = 0x0077F4A0u;

// libkernel's SIF software registers and command data block
constexpr u32 kSifSregs = 0x00966C00u;
constexpr u32 kSifCmdData = 0x00966A58u;
constexpr u32 kSifSysTable = 0x00966A64u;   // pointer, then its size at +4
constexpr u32 kSifUserTable = 0x00966A6Cu;  // pointer, then its size at +4

// libkernel's timer alarms: 64-byte records, ids = record << 4 | tag (the tag 10 bits, odd)
namespace alarm {
constexpr s32 kNext = 0x00;
constexpr s32 kPrev = 0x04;
constexpr s32 kTag = 0x08;
constexpr s32 kFlags = 0x0C;   // bit 0: has a time left ([+16] - [+24]); bit 1: on the pending list
constexpr s32 kU64A = 0x10;    // the three u64s of the ordering key [+32] + [+16] - [+24]
constexpr s32 kU64B = 0x18;
constexpr s32 kU64C = 0x20;
constexpr u32 kTimerBlock = 0x00780B48u;
constexpr u32 kSetUp = 0x00780B50u;     // < 0 until the timer is initialised
constexpr u32 kTagSeq = 0x00780B54u;
constexpr u32 kInUse = 0x00780B58u;
constexpr u32 kFreeList = 0x00780B5Cu;
constexpr u32 kPending = 0x00780B60u;
constexpr u32 kHandling = 0x00780B64u;
constexpr u32 kCursor = 0x00780B68u;
constexpr u32 kUserFree = 0x0096D7C0u;   // the user-alarm free list head (16-byte records 0x96D3C0..0x96D7B0)
constexpr u32 kUserFirst = 0x0096D3C0u;
constexpr u32 kUserLast = 0x0096D7B0u;
}  // namespace alarm
constexpr u32 kBusClock = 147456000u;  // the EE bus clock in Hz (the time conversions)

}  // namespace sce

// --- libgraph / libdma (game/src/sce/sce_graph.cpp) -------------------------------------------------------------------
void checkModelVersion(EEContext& ctx);  // 0x4F90B8
void sceGsSetDefDispEnv(EEContext& ctx);  // 0x4F9168
void sceGszbufaddr(EEContext& ctx);  // 0x4F95A0
void sceGsSetDefDrawEnv(EEContext& ctx);  // 0x4F9668
void sceGsSetDefStoreImage(EEContext& ctx);  // 0x4F9CE8
void sceGsSetDefDrawEnv2(EEContext& ctx);  // 0x4FA558
void CheckAddress(EEContext& ctx);  // 0x4FA890
void memclr(EEContext& ctx);  // 0x4FA8B8
void sceDmaGetEnv(EEContext& ctx);  // 0x4FABD0

// --- libkernel: newlib glue, SIF tables, alarms, version checks; libdbc (game/src/sce/sce_kernel.cpp) ------------------
void open(EEContext& ctx);  // 0x503820
void close(EEContext& ctx);  // 0x503848
void ioctl(EEContext& ctx);  // 0x503850
void lseek(EEContext& ctx);  // 0x503858
void isatty(EEContext& ctx);  // 0x503910
void fstat(EEContext& ctx);  // 0x503918
void getpid(EEContext& ctx);  // 0x503930
void kill(EEContext& ctx);  // 0x503938
void stat(EEContext& ctx);  // 0x503960
void unlink(EEContext& ctx);  // 0x503988
void sceResetttyinit(EEContext& ctx);  // 0x5035E0
void _set_sreg(EEContext& ctx);  // 0x505F48
void _change_addr(EEContext& ctx);  // 0x505F68
void sceSifGetSreg(EEContext& ctx);  // 0x505F78
void sceSifSetSreg(EEContext& ctx);  // 0x505F90
void sceSifGetDataTable(EEContext& ctx);  // 0x505FB0
void sub_506400(EEContext& ctx);  // 0x506400 [set the user command table]
void sub_506418(EEContext& ctx);  // 0x506418 [set the system command table]
void sub_506430(EEContext& ctx);  // 0x506430 [add a command handler]
void _fs_version(EEContext& ctx);  // 0x508378
void _lf_version(EEContext& ctx);  // 0x50BBE8
void __sceKernlGetEhSemaId(EEContext& ctx);  // 0x50D468
void sub_50D840(EEContext& ctx);  // 0x50D840 [byte copy]
void nullsub_131(EEContext& ctx);  // 0x50DC78
void sub_50E190(EEContext& ctx);  // 0x50E190 [insert an alarm]
void sub_50E218(EEContext& ctx);  // 0x50E218 [unlink an alarm]
void sub_50E5D8(EEContext& ctx);  // 0x50E5D8 [allocate an alarm]
void sub_50E690(EEContext& ctx);  // 0x50E690 [free an alarm]
void sub_50E7A0(EEContext& ctx);  // 0x50E7A0 [alarm pool status]
void sub_50EB50(EEContext& ctx);  // 0x50EB50 [alarm time left]
void sub_50EE38(EEContext& ctx);  // 0x50EE38 [cycles -> seconds + microseconds]
void sub_50EEE0(EEContext& ctx);  // 0x50EEE0 [seconds + microseconds -> cycles]
void sub_50EF50(EEContext& ctx);  // 0x50EF50 [bus clock / count, float]
void sub_50EFA8(EEContext& ctx);  // 0x50EFA8 [bus clock / rate, u64]
void _InitAlarm(EEContext& ctx);  // 0x50EFE0
void AlarmHandler(EEContext& ctx);  // 0x50F030
void _get_free_slot(EEContext& ctx);  // 0x51C0F8
void DPRINT(EEContext& ctx);  // 0x51D588

// --- libkernel: tty queue, character sinks, sceSnprintf (game/src/sce/sce_printf.cpp) ---------------------------------
void QueueInit(EEContext& ctx);  // 0x504678
void QueuePeekWriteDone(EEContext& ctx);  // 0x5046A0
void QueuePeekReadDone(EEContext& ctx);  // 0x5046E0
void sceTtyRead(EEContext& ctx);  // 0x504A30
void deci2Putchar(EEContext& ctx);  // 0x504BF8
void serialPutchar(EEContext& ctx);  // 0x504CA8
void ftoi(EEContext& ctx);  // 0x504CE0
void printfloat(EEContext& ctx);  // 0x504D70
void _sceSnprintf(EEContext& ctx);  // 0x504F48
void snprintf_char(EEContext& ctx);  // 0x505C60
void printf_char(EEContext& ctx);  // 0x505CB8
void kprintf_char(EEContext& ctx);  // 0x505CE0
void _sceSnprintf_pf(EEContext& ctx);  // 0x505D08
void sceVsnprintf(EEContext& ctx);  // 0x505D58
void sceSnprintf(EEContext& ctx);  // 0x505D90

// --- libmc2: path and file-name helpers (game/src/sce/sce_mc2path.cpp) ------------------------------------------------
void instr(EEContext& ctx);  // 0x514D50
void isCorrNameSize(EEContext& ctx);  // 0x514DB0
void isCorrFname(EEContext& ctx);  // 0x514E20
void isPathCurParent(EEContext& ctx);  // 0x514E78
void isWildFit(EEContext& ctx);  // 0x514F30
void _strtok(EEContext& ctx);  // 0x5150B0
void _get_dir_nest(EEContext& ctx);  // 0x5151D0
void _make_path(EEContext& ctx);  // 0x515218

}  // namespace p3fes::game
