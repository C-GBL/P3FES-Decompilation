// Slice libs3: the library code of 0x520000-0x52FFFF and 0x570000-0x57FFFF -- newlib's stdio core, mprec / strtod,
// qsort and the heap internals, __ieee754_pow / __ieee754_rem_pio2, and CRI Sofdec's M2V / MPS / MPV / MWSFD
// helpers (game/src/libc/libs3_*.cpp, game/src/lib/libs3_*.cpp, tests/game/test_libs3.cpp). Every function is a
// p3fes_handgen body on the register ABI (arguments in $a0..$t3 / $f12.., the result in $v0 / $f0) with its
// recompiled entry point fn_<name>_<addr8> as the shim; names are symbols/functions.json's (ADR-0009), a
// [proposed name] where the name is a sub_ or a FLIRT false match.
#pragma once

#include "p3fes/ee_context.h"
#include "p3fes/game/libc.h"
#include "p3fes/game/tail1.h"

namespace p3fes::game {

// --- newlib's stdio core (game/src/libc/libs3_stdio.cpp)
void _getpid_r(EEContext& ctx);  // 0x520048 [__sfvwrite]
void _execve_r(EEContext& ctx);  // 0x520580 [_lseek_r]
void _fork_r(EEContext& ctx);  // 0x5205D8 [__smakebuf]
void _printf_r(EEContext& ctx);  // 0x522568
void lflush(EEContext& ctx);  // 0x523550
void _sprintf_r(EEContext& ctx);  // 0x523A58
void sscanf(EEContext& ctx);  // 0x523B40
void _sscanf_r(EEContext& ctx);  // 0x523BC8
void __sread(EEContext& ctx);  // 0x523C60
void __sseek(EEContext& ctx);  // 0x523D40
void __sclose(EEContext& ctx);  // 0x523DA8
void __submore(EEContext& ctx);  // 0x525EC8
void ungetc(EEContext& ctx);  // 0x525FB0
void __sprint(EEContext& ctx);  // 0x526140
void __sbprintf(EEContext& ctx);  // 0x526188
void cvt(EEContext& ctx);  // 0x527810
void vfscanf(EEContext& ctx);  // 0x527A88
void __svfscanf(EEContext& ctx);  // 0x527B00
void _vfscanf_r(EEContext& ctx);  // 0x527B30
void __svfscanf_r(EEContext& ctx);  // 0x527B48
void _vsprintf_r(EEContext& ctx);  // 0x528920
void __swsetup(EEContext& ctx);  // 0x5289D0

// --- qsort and newlib's heap internals (game/src/libc/libs3_stdlib.cpp)
void malloc_extend_top(EEContext& ctx);  // 0x520768
void _malloc_r(EEContext& ctx);  // 0x5209C0
void qsort(EEContext& ctx);  // 0x5225F8
void _realloc_r(EEContext& ctx);  // 0x522FC0

// --- newlib's mprec Bigint arithmetic and strtod (game/src/libc/libs3_mprec.cpp)
void _Balloc(EEContext& ctx);  // 0x521578
void _multadd(EEContext& ctx);  // 0x521650
void _s2b(EEContext& ctx);  // 0x521758
void _i2b(EEContext& ctx);  // 0x5219C8
void _multiply(EEContext& ctx);  // 0x521A00
void _pow5mult(EEContext& ctx);  // 0x521C08
void _lshift(EEContext& ctx);  // 0x521D10
void __mdiff(EEContext& ctx);  // 0x521ED8
void _d2b(EEContext& ctx);  // 0x5222C0
void _strtod_r(EEContext& ctx);  // 0x524AA8
void strtod(EEContext& ctx);  // 0x5258F8
void strtodf(EEContext& ctx);  // 0x525920

// --- libm: __ieee754_pow, __ieee754_rem_pio2 (game/src/libc/libs3_libm.cpp)
void __ieee754_pow(EEContext& ctx);  // 0x5296F0
void __ieee754_rem_pio2(EEContext& ctx);  // 0x52A3F0

// --- CRI Sofdec M2V (game/src/lib/libs3_m2v.cpp)
void sub_574CA8(EEContext& ctx);  // 0x574CA8 [m2vSetupEntryTable]
void sceLibgcc32GetErxEntries_16(EEContext& ctx);  // 0x574E50 [m2vGetVersionStr]
void sub_574E60(EEContext& ctx);  // 0x574E60 [m2vIsMpeg2]
void sub_574F10(EEContext& ctx);  // 0x574F10 [m2vInit]
void sub_574FE8(EEContext& ctx);  // 0x574FE8 [m2vSetupPool]
void sub_575088(EEContext& ctx);  // 0x575088 [m2vResetParams]
void sub_575138(EEContext& ctx);  // 0x575138 [m2vFinish]
void sub_575140(EEContext& ctx);  // 0x575140 [m2vCreate]
void sub_575178(EEContext& ctx);  // 0x575178 [m2vFindFreeHandle]
void sub_5751C8(EEContext& ctx);  // 0x5751C8 [m2vInitHandle]
void sub_575288(EEContext& ctx);  // 0x575288 [m2vDestroy]
void sub_5752D8(EEContext& ctx);  // 0x5752D8
void sub_5752E0(EEContext& ctx);  // 0x5752E0 [m2vSetCallback]
void sub_575390(EEContext& ctx);  // 0x575390 [m2vSetCallbackAll]
void sub_575428(EEContext& ctx);  // 0x575428
void sub_575440(EEContext& ctx);  // 0x575440
void sub_575458(EEContext& ctx);  // 0x575458
void atan2l_10(EEContext& ctx);  // 0x575470
void cosl_10(EEContext& ctx);  // 0x575488
void coshl_10(EEContext& ctx);  // 0x5754A0
void expl_10(EEContext& ctx);  // 0x5754B8

// --- CRI Sofdec MPS (game/src/lib/libs3_mps.cpp)
void sub_5756A0(EEContext& ctx);  // 0x5756A0 [criWordCopy]
void __env_lock_3(EEContext& ctx);  // 0x575948 [mpsInitHookA]
void sub_575958(EEContext& ctx);  // 0x575958 [mpsSetMode]
void sub_5759B0(EEContext& ctx);  // 0x5759B0 [mpsSetCallbackA]
void sub_575A00(EEContext& ctx);  // 0x575A00 [mpsSetCallbackB]
void sub_575A50(EEContext& ctx);  // 0x575A50 [mpsSetPesCallback]
void sub_575AA0(EEContext& ctx);  // 0x575AA0 [mpsDemux]
void sub_575B48(EEContext& ctx);  // 0x575B48 [mpsParse]
void sub_575C68(EEContext& ctx);  // 0x575C68 [mpsParsePacket]
void sub_575D70(EEContext& ctx);  // 0x575D70 [mpsReadPackHeader]
void sub_5761D8(EEContext& ctx);  // 0x5761D8 [mpsReadSystemHeader]
void sub_576A48(EEContext& ctx);  // 0x576A48 [mpsReadPesHeader]
void sub_5776B0(EEContext& ctx);  // 0x5776B0 [mpsStartCodeClass]
void sub_577720(EEContext& ctx);  // 0x577720 [mpsIsMpeg1Pack]
void sub_577780(EEContext& ctx);  // 0x577780 [mpsFindStartCode]
void __env_lock_4(EEContext& ctx);  // 0x5777E8 [mpsInitHookB]
void sub_5777F8(EEContext& ctx);  // 0x5777F8 [mpsGetPackInfo]
void sub_577860(EEContext& ctx);  // 0x577860 [mpsGetStreamInfo]
void sub_577910(EEContext& ctx);  // 0x577910 [mpsGetSystemInfo]
void sub_5779A8(EEContext& ctx);  // 0x5779A8 [mpsGetPesInfo]
void sub_577A38(EEContext& ctx);  // 0x577A38 [mpsInit]
void sub_577AB0(EEContext& ctx);  // 0x577AB0 [mpsSetupWork]
void sub_577DD8(EEContext& ctx);  // 0x577DD8 [mpsCreate]
void sub_577E68(EEContext& ctx);  // 0x577E68 [mpsInitHandle]

// --- CRI Sofdec MPV (game/src/lib/libs3_mpv.cpp)
void sub_578F10(EEContext& ctx);  // 0x578F10 [mpvDecodeHdrMem0]
void sub_579080(EEContext& ctx);  // 0x579080 [mpvSeekPicture]
void sub_579450(EEContext& ctx);  // 0x579450 [mpvDecodeHeaders]
void sub_5796D0(EEContext& ctx);  // 0x5796D0 [mpvDecodeHdrMem]
void sub_579818(EEContext& ctx);  // 0x579818 [mpvReadSequenceHeader]
void sub_579ED8(EEContext& ctx);  // 0x579ED8 [mpvReadGopHeader]
void sub_57A158(EEContext& ctx);  // 0x57A158 [mpvReadPictureHeader]
void sub_57A740(EEContext& ctx);  // 0x57A740 [mpvSkipExtension]
void sub_57A800(EEContext& ctx);  // 0x57A800 [mpvReadUserData]
void sub_57A8F0(EEContext& ctx);  // 0x57A8F0 [mpvCopyUserData]
void sub_57AAB8(EEContext& ctx);  // 0x57AAB8 [mpvParseUserTags]
void sub_57ABC0(EEContext& ctx);  // 0x57ABC0 [mpvNextStartCode]
void sub_57ADC0(EEContext& ctx);  // 0x57ADC0 [mpvSeekStartCode]
void sub_57AEE8(EEContext& ctx);  // 0x57AEE8
void sub_57AEF0(EEContext& ctx);  // 0x57AEF0
void sceLibgcc32GetErxEntries_18(EEContext& ctx);  // 0x57AEF8 [mpvGetVersionStr]
void sub_57AF08(EEContext& ctx);  // 0x57AF08 [mpvIsMpeg1]
void sub_57AFA0(EEContext& ctx);  // 0x57AFA0 [mpvInit]
void sub_57B078(EEContext& ctx);  // 0x57B078 [mpvCheckBuild]
void sub_57B0F0(EEContext& ctx);  // 0x57B0F0
void sub_57B0F8(EEContext& ctx);  // 0x57B0F8
void sub_57B100(EEContext& ctx);  // 0x57B100 [mpvMapAddressA]
void sub_57B118(EEContext& ctx);  // 0x57B118
void sub_57B120(EEContext& ctx);  // 0x57B120 [mpvMapAddressB]
void sub_57B138(EEContext& ctx);  // 0x57B138
void sub_57B140(EEContext& ctx);  // 0x57B140 [mpvToKseg0]
void sub_57B158(EEContext& ctx);  // 0x57B158 [mpvSetupClipTable]
void sub_57B1A8(EEContext& ctx);  // 0x57B1A8 [mpvBuildClipTable]
void sub_57B230(EEContext& ctx);  // 0x57B230 [mpvFreeAllHandles]
void sub_57B278(EEContext& ctx);  // 0x57B278 [mpvAttachTables]
void sub_57B2B0(EEContext& ctx);  // 0x57B2B0
void sub_57B2B8(EEContext& ctx);  // 0x57B2B8 [mpvSetupPool]
void sub_57B368(EEContext& ctx);  // 0x57B368 [mpvResetSequence]
void sub_57B418(EEContext& ctx);  // 0x57B418 [mpvFinish]
void sub_57B440(EEContext& ctx);  // 0x57B440 [mpvCreate]
void sub_57B498(EEContext& ctx);  // 0x57B498 [mpvFindFreeHandle]
void sub_57B4E8(EEContext& ctx);  // 0x57B4E8 [mpvInitHandle]
void sub_57B5B0(EEContext& ctx);  // 0x57B5B0 [mpvGetPair]
void sub_57B5C8(EEContext& ctx);  // 0x57B5C8 [mpvDestroy]
void __env_lock_5(EEContext& ctx);  // 0x57B630 [mpvLockHook]
void __env_unlock_5(EEContext& ctx);  // 0x57B638 [mpvUnlockHook]
void sub_57B640(EEContext& ctx);  // 0x57B640 [mpvNullCallback]
void sub_57B648(EEContext& ctx);  // 0x57B648 [mpvSetCallback]
void sub_57B710(EEContext& ctx);  // 0x57B710 [mpvSetCallbackAll]
void sub_57B760(EEContext& ctx);  // 0x57B760 [mpvGetCallback]
void sub_57B818(EEContext& ctx);  // 0x57B818
void sub_57B830(EEContext& ctx);  // 0x57B830 [mpvLinkM2v]
void sub_57B860(EEContext& ctx);  // 0x57B860
void sub_57B878(EEContext& ctx);  // 0x57B878
void sub_57B890(EEContext& ctx);  // 0x57B890
void sub_57B8A8(EEContext& ctx);  // 0x57B8A8
void sub_57B8D0(EEContext& ctx);  // 0x57B8D0 [mpvDecodeHeadersM2v]
void sub_57B998(EEContext& ctx);  // 0x57B998 [mpvFetchM2vState]
void sub_57BAD8(EEContext& ctx);  // 0x57BAD8
void sub_57BAF0(EEContext& ctx);  // 0x57BAF0 [criMulDiv]
void sub_57BB60(EEContext& ctx);  // 0x57BB60 [criMulDivRound]
void sub_57BC10(EEContext& ctx);  // 0x57BC10 [criMulDivRound2]
void sub_57BCB8(EEContext& ctx);  // 0x57BCB8
void sub_57BCD8(EEContext& ctx);  // 0x57BCD8 [criCallHook]
void sub_57BD10(EEContext& ctx);  // 0x57BD10 [criKeyRetain]
void sub_57BD30(EEContext& ctx);  // 0x57BD30 [criKeyRelease]
void sub_57BD50(EEContext& ctx);  // 0x57BD50 [criKeyFromString]
void sub_57BF08(EEContext& ctx);  // 0x57BF08 [criKeyDefault]
void sub_57BF78(EEContext& ctx);  // 0x57BF78 [criKeyStep]
void sub_57BF98(EEContext& ctx);  // 0x57BF98 [criKeyTableInit]
void sub_57BFB8(EEContext& ctx);  // 0x57BFB8 [criKeyTableReset]
void sub_57BFC0(EEContext& ctx);  // 0x57BFC0 [criKeyTableFill]
void sub_57C188(EEContext& ctx);  // 0x57C188 [criDescramble]
void sub_57C210(EEContext& ctx);  // 0x57C210 [criDescrambleBlock]
void sub_57C270(EEContext& ctx);  // 0x57C270 [criIsPackStart]
void sub_57C2B0(EEContext& ctx);  // 0x57C2B0 [mwsfdCalcBufferSizes]
void sub_57C398(EEContext& ctx);  // 0x57C398 [mwsfdCalcPictureSizes]
void sub_57C3E8(EEContext& ctx);  // 0x57C3E8 [mwsfdCalcFrameSizes]

// --- CRI Sofdec MWSFD (game/src/lib/libs3_mwsfd.cpp)
void sub_57C4E8(EEContext& ctx);  // 0x57C4E8 [mwsfdBufferFormat]
void sub_57C538(EEContext& ctx);  // 0x57C538 [mwsfdCalcFixedSizes]
void sub_57C568(EEContext& ctx);  // 0x57C568 [mwsfdCalcHeaderSize]
void sub_57C570(EEContext& ctx);  // 0x57C570 [mwsfdCalcWorkSize]
void sub_57C628(EEContext& ctx);  // 0x57C628 [mwsfdCalcSfdWorkSize]
void sub_57C680(EEContext& ctx);  // 0x57C680 [mwsfdCalcPlayerWorkSize]
void sub_57C6E0(EEContext& ctx);  // 0x57C6E0 [mwsfdSetFramePool]
void sub_57C800(EEContext& ctx);  // 0x57C800 [mwsfdAllocFrames]
void sub_57C910(EEContext& ctx);  // 0x57C910 [mwsfdAllocPictures]
void sub_57CA78(EEContext& ctx);  // 0x57CA78 [mwsfdSetupPlayerWork]
void sub_57D1D0(EEContext& ctx);  // 0x57D1D0 [mwsfdIsMono]
void sub_57D208(EEContext& ctx);  // 0x57D208 [mwsfdSetUsrDatBufInternal]
void sub_57D220(EEContext& ctx);  // 0x57D220 [mwsfdSetUsrDatBuf]
void sub_57D308(EEContext& ctx);  // 0x57D308 [mwsfdSetUserDataBuffer]
void sub_57D380(EEContext& ctx);  // 0x57D380 [mwsfdDestroySfd]
void sub_57D3C8(EEContext& ctx);  // 0x57D3C8 [mwsfdSetSfdParams]
void sub_57D5B0(EEContext& ctx);  // 0x57D5B0 [mwsfdSetupAudio]
void sub_57D5D8(EEContext& ctx);  // 0x57D5D8 [mwPlyCreate]
void sub_57D960(EEContext& ctx);  // 0x57D960 [mwsfdCheckAllocator]
void sub_57D9B0(EEContext& ctx);  // 0x57D9B0 [mwsfdInitAllocator]
void sub_57DA08(EEContext& ctx);  // 0x57DA08 [mwsfdCheckCprm]
void sub_57DA90(EEContext& ctx);  // 0x57DA90 [mwsfdAllocSfxWork]
void sub_57DC80(EEContext& ctx);  // 0x57DC80 [mwsfdSetOption]
void sub_57DC90(EEContext& ctx);  // 0x57DC90 [mwPlyGetHdrInf]
void sub_57DF60(EEContext& ctx);  // 0x57DF60 [mwsfdAudioCode]
void sub_57DFB0(EEContext& ctx);  // 0x57DFB0 [mwsfdRateOk]
void sub_57E028(EEContext& ctx);  // 0x57E028 [mwsfdSetAllocator]
void sub_57E070(EEContext& ctx);  // 0x57E070 [mwsfdAlloc]
void sub_57E110(EEContext& ctx);  // 0x57E110 [mwsfdAllocFromWork]
void sub_57E148(EEContext& ctx);  // 0x57E148 [mwsfdAllocFromMalloc]
void sub_57E180(EEContext& ctx);  // 0x57E180 [mwsfdFree]
void sub_57E1D0(EEContext& ctx);  // 0x57E1D0
void sub_57E1D8(EEContext& ctx);  // 0x57E1D8 [mwsfdFreeToMalloc]
void sub_57E210(EEContext& ctx);  // 0x57E210 [mwsfdFreeAll]
void sub_57E270(EEContext& ctx);  // 0x57E270 [mwsfdCountAlloc]
void sub_57E290(EEContext& ctx);  // 0x57E290 [mwsfdAllocCount]
void sub_57E298(EEContext& ctx);  // 0x57E298 [mwsfdSetKey]
void sub_57E320(EEContext& ctx);  // 0x57E320 [mwsfdSetDescrambleHook]
void sub_57E360(EEContext& ctx);  // 0x57E360 [mwsfdDescrambleHook]
void sub_57E378(EEContext& ctx);  // 0x57E378 [mwsfdSetFrameSync]
void sub_57E3D0(EEContext& ctx);  // 0x57E3D0 [mwPlyGetFrmSync]
void sub_57E428(EEContext& ctx);  // 0x57E428 [mwPlyGetFrm]
void sub_57E530(EEContext& ctx);  // 0x57E530 [mwsfdGetCurrentFrame]
void sub_57E698(EEContext& ctx);  // 0x57E698 [mwsfdCheckFrameApi]
void sub_57E6E0(EEContext& ctx);  // 0x57E6E0 [mwsfdNoteFrameTime]
void sub_57E730(EEContext& ctx);  // 0x57E730 [mwsfdFillFrameInfo]
void sub_57E910(EEContext& ctx);  // 0x57E910 [mwsfdFrameUserData]
void sub_57E9A8(EEContext& ctx);  // 0x57E9A8 [mwsfdTimeToMs]
void sub_57E9D8(EEContext& ctx);  // 0x57E9D8 [mwsfdPicStruct]
void sub_57EA18(EEContext& ctx);  // 0x57EA18 [mwsfdPicType]
void sub_57EA80(EEContext& ctx);  // 0x57EA80 [mwsfdFrameConcat]
void sub_57EB38(EEContext& ctx);  // 0x57EB38 [mwsfdNoteFrame]
void sub_57EB80(EEContext& ctx);  // 0x57EB80 [mwsfdFrameTagValues]
void sub_57EC00(EEContext& ctx);  // 0x57EC00 [mwsfdGetPictureInfo]
void sub_57EC38(EEContext& ctx);  // 0x57EC38 [mwsfdConvertPicture]
void sub_57ED00(EEContext& ctx);  // 0x57ED00
void sub_57ED40(EEContext& ctx);  // 0x57ED40
void sub_57EDA8(EEContext& ctx);  // 0x57EDA8 [mwsfdCopyPictureInfo]
void sub_57EDD8(EEContext& ctx);  // 0x57EDD8 [mwsfdReleaseFrame]
void sub_57EE50(EEContext& ctx);  // 0x57EE50 [mwsfdReleaseCurrentFrame]
void sub_57EF08(EEContext& ctx);  // 0x57EF08 [mwsfdIsFrameLate]
void sub_57EF78(EEContext& ctx);  // 0x57EF78 [mwsfdGetUserData]
void sub_57F050(EEContext& ctx);  // 0x57F050
void sub_57F058(EEContext& ctx);  // 0x57F058 [mwsfdSkippedFrames]
void sub_57F0A8(EEContext& ctx);  // 0x57F0A8 [mwsfdRingSysWord]
void sub_57F600(EEContext& ctx);  // 0x57F600 [mwsfdSkippedDecodes]
void sub_57F670(EEContext& ctx);  // 0x57F670 [mwsfdFindStream]
void sub_57F6F8(EEContext& ctx);  // 0x57F6F8 [mwsfdStreamWord]
void sub_57F750(EEContext& ctx);  // 0x57F750 [mwsfdSfdErrorCb]
void sub_57F768(EEContext& ctx);  // 0x57F768 [mwsfdInit]
void sub_57F920(EEContext& ctx);  // 0x57F920 [mwsfdCreateServerThreads]
void sub_57F980(EEContext& ctx);  // 0x57F980 [mwsfdInitWork]
void sub_57FA28(EEContext& ctx);  // 0x57FA28 [mwsfdSetUserDataSwitch]
void sub_57FA50(EEContext& ctx);  // 0x57FA50 [mwsfdUsrDatSw]
void sub_57FA70(EEContext& ctx);  // 0x57FA70 [mwsfdSetWork60]
void sub_57FAB8(EEContext& ctx);  // 0x57FAB8 [mwsfdSetFps]
void sub_57FAF0(EEContext& ctx);  // 0x57FAF0 [mwsfdReinit]
void sub_57FC90(EEContext& ctx);  // 0x57FC90 [mwsfdLastErrorCode]
void sub_57FCB0(EEContext& ctx);  // 0x57FCB0 [mwsfdInitSfd]
void r_lock_def_free_2(EEContext& ctx);  // 0x57FD58 [mwsfdFinishSfd]
void r_lock_def_get_free_item_2(EEContext& ctx);  // 0x57FD78 [mwsfdSfdErrorHandler]

// ---------------------------------------------------------------------------------------------------------------------
// Named offsets of the records these bodies touch, read from the instructions (no newlib or CRI source was opened,
// ADR-0010; names are ours, ADR-0009). The bodies use them in place of the numbers they equal: the slice's normaliser
// swaps every name back for its value and proves each body token-equal to p3fes_handgen's. The FILE record's first
// fields are libc::file (libc.h); the CRI handle states and error records are tail1:: (tail1.h).
namespace libs3 {

constexpr u32 kSysErrno = 0x9ACC20u;  // the system call layer's errno word (_execve_r = _lseek_r copies it to the _reent)

// newlib's struct _reent: the fields beyond libc::reent
namespace reent {
constexpr s32 kStdout = 8;      // FILE* (_printf_r prints here)
constexpr s32 kInitDone = 56;   // s32: __sinit ran for this _reent (stdio set up)
constexpr s32 kCleanup = 60;    // u32: the cleanup function (_cleanup_r, registered by __smakebuf)
constexpr s32 kP5s = 72;        // u32: mprec's cached 5^4 Bigint list (_pow5mult)
constexpr s32 kGlue = 472;      // the FILE glue list head: libs3::glue
}  // namespace reent

// A block of FILEs in the glue list (_fwalk)
namespace glue {
constexpr s32 kNext = 0;   // u32: the next block
constexpr s32 kCount = 4;  // s32: FILEs in this block
constexpr s32 kFiles = 8;  // u32: the first FILE (88 bytes each)
}  // namespace glue

// newlib's FILE: the fields beyond libc::file (the read / write side of stdio)
namespace file {
constexpr s32 kUbBase = 48;    // u32: the ungetc buffer (FILE + kUbuf while it is the built-in 3 bytes)
constexpr s32 kUbSize = 52;    // s32: its size
constexpr s32 kUp = 56;        // u32: the read position saved while the ungetc buffer is in use
constexpr s32 kUr = 60;        // s32: the read count saved with it
constexpr s32 kUbuf = 64;      // 3 bytes: the built-in ungetc buffer
constexpr s32 kNbuf = 67;      // 1 byte: the buffer of an unbuffered FILE
constexpr s32 kBlkSize = 76;   // s32: the buffer size __smakebuf chose
constexpr s32 kOffset = 80;    // s32: the file offset (valid while flag kFlagOffset is set)
constexpr s32 kSize = 88;      // bytes per FILE
// flag bits (libc::file::kFlags), as the bodies test them
constexpr u32 kFlagLineBuf = 0x1;    // line buffered
constexpr u32 kFlagUnbuf = 0x2;      // unbuffered (the one-byte buffer kNbuf)
constexpr u32 kFlagRead = 0x4;       // reading
constexpr u32 kFlagWrite = 0x8;      // writing
constexpr u32 kFlagReadWrite = 0x10; // opened for both
constexpr u32 kFlagEof = 0x20;
constexpr u32 kFlagError = 0x40;
constexpr u32 kFlagMallocBuf = 0x80; // the buffer came from malloc
constexpr u32 kFlagAppend = 0x100;   // seek to the end before each write (__swrite)
constexpr u32 kFlagString = 0x200;   // a string FILE (sprintf / sscanf)
constexpr u32 kFlagOffset = 0x1000;  // kOffset is valid
}  // namespace file

// CRI M2V (the decoder above the IPU): a pool of 1,696-byte handles
namespace m2v {
constexpr u32 kEntryFlag = 0x7B2928u;   // s32: 1 once the entry table below is filled
constexpr u32 kEntries = 0x7B292Cu;     // u32[20]: the module's entry points (sub_574CA8)
constexpr u32 kBanner = 0x99B258u;      // u32: the version banner, stored at init
constexpr u32 kDefaultCbs = 0x99B260u;  // u32[16]: the default callbacks (the first 8 copied into each handle)
constexpr u32 kPoolCount = 0x99B2A0u;   // s32
constexpr u32 kPoolBase = 0x99B2A4u;    // u32
constexpr u32 kLastHandle = 0x99B2A8u;  // u32: the handle sub_5753E8 last checked
constexpr s32 kHandleStride = 1696;
constexpr s32 kState = 0;               // s32: 1 free, 2 valid
constexpr s32 kCallbacks = 24;          // u32[8]
constexpr s32 kParams = 88;             // the decode-parameter block (sub_575088)
constexpr s32 kStateFree = 1;
constexpr s32 kStateValid = 2;
}  // namespace m2v

// CRI MPS (the program-stream demultiplexer): the handle fields beyond tail1::mps
namespace mps {
constexpr s32 kMode = 16;           // s32 (sub_575958; 2 after init)
constexpr s32 kPack = 24;           // 16 bytes: the pack-header record
constexpr s32 kSystem = 40;         // 32 bytes: the system-header record
constexpr s32 kStreamInfo = 72;     // 3 x 32 bytes: the filed system-header records
constexpr s32 kPes = 168;           // 40 bytes: the PES-header record
constexpr s32 kPesStreamId = 184;   // u8: the stream id of the last PES header
constexpr s32 kParser = 212;        // u32: the parser (sub_575B48), called through jalr
constexpr s32 kCbA = 228;           // {fn, arg} callback A (sub_5759B0)
constexpr s32 kCbB = 236;           // {fn, arg} callback B (sub_575A00)
constexpr s32 kPesCb = 244;         // {fn, arg}: called after each PES header with the stream id
constexpr u32 kClassPack = 0x10000;      // sub_5776B0: 00 00 01 BA
constexpr u32 kClassSystem = 0x20000;    // 00 00 01 BB
constexpr u32 kClassPes = 0x40000;       // 00 00 01 BC..FF
constexpr u32 kClassEnd = 0x80000;       // 00 00 01 B9
}  // namespace mps

// CRI MPV (the video layer): the pool and handle fields beyond tail1::mpv
namespace mpv {
constexpr u32 kDefaultCbs = 0x99B2C0u;  // u32[16]: the default callbacks (copied from 0x7C7A70 at init)
constexpr u32 kShared = 0x99B310u;      // u32: the shared work area (7,136 bytes): pool base + (n + 1) * 1,056
constexpr u32 kAfterPool = 0x99B30Cu;   // u32: pool base + n * 1,056, the record after the last handle
constexpr u32 kPoolCount = 0x99B314u;   // s32
constexpr u32 kPoolBase = 0x99B318u;    // u32
constexpr u32 kClipTable = 0x7B2A10u;   // u8[1024]: 384 x 0, 0..255, 384 x 255 (sub_57B1A8)
constexpr u32 kClipZero = 0x7B2A04u;    // u32: the table's zero point (table + 384)
constexpr s32 kHandleStride = 1056;
constexpr s32 kCallbacks = 400;         // u32[16]
constexpr s32 kSeq = 464;               // the sequence block (tail1::mpv::kSeqBlock; sub_57B368)
constexpr s32 kM2v = 944;               // u32: the handle's decoder-side (M2V) handle
constexpr s32 kHdrState = 948;          // s32: the header just read (1 sequence, 2 group, 3 picture)
constexpr s32 kStateFree = 1;
}  // namespace mpv

// CRI MWSFD (the movie player): the work record (tail1::mwsfd::kWork) and a player record
namespace mwsfd {
constexpr s32 kWorkMalloc = 40;     // u32: the malloc callback (sub_57E028)
constexpr s32 kWorkFree = 44;       // u32: the free callback
constexpr s32 kWorkAllocObj = 48;   // u32: their first argument
constexpr s32 kWorkUsrDatSw = 56;   // s32: user data on / off (sub_57FA28 / sub_57FA50)
constexpr s32 kWork60 = 60;         // s32 (sub_57FA70 / sub_57FA98)
constexpr s32 kWorkLastError = 104; // s32: the last error code (sub_57FC60)
constexpr s32 kWorkPlayers = 108;   // 8 player records of 684 bytes
constexpr s32 kPlayerStride = 684;
// a player record
constexpr s32 kFrmSync = 84;        // s32: frame sync on / off (sub_57E378 / sub_57E3D0)
constexpr s32 kSkipped = 132;       // s32: frames dropped (sub_57F058)
constexpr s32 kUsrDatInt = 352;     // {buffer, size, count}: the internal user-data record
constexpr s32 kUsrDatExt = 364;     // {buffer, size, count}: the user's record (sub_57D308)
constexpr s32 kUsrDatCur = 376;     // u32: the record in use
constexpr s32 kWorkUse = 492;       // s32: the player runs on user work (else on the malloc callback)
constexpr s32 kWorkSize = 496;      // s32
constexpr s32 kWorkCur = 500;       // u32: the next free byte
constexpr s32 kWorkUsed = 504;      // s32
constexpr s32 kAllocCount = 508;    // s32: live allocations (at most 32)
constexpr s32 kAllocTable = 512;    // u32[32]
constexpr s32 kKeyTable = 676;      // u32: the header key table (sub_57BFC0)
constexpr s32 kFrameApi = 680;      // s32: 1 / 2, the get / release frame API in use (sub_57E698)
constexpr s32 kMaxAllocs = 32;
}  // namespace mwsfd

}  // namespace libs3

}  // namespace p3fes::game
