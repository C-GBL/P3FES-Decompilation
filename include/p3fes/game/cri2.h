// Phase 5 slice cri2: the CRI middleware, second pass (game/src/cri/cri2_*.cpp, tests/game/test_cri2.cpp), under the
// relaxed callee rule: these bodies may call still-recompiled functions (the drivers) through their gen:: entry points;
// only a function whose OWN body touches hardware, makes a syscall, talks to the IOP or calls ADXF / ROFS / sceCd
// directly stays recompiled. What is here:
//   * ADXT, the ADX stream player (0x547BC0-0x54CA08): handle create / destroy, the start requests (file name, file id
//     of a partition, memory index, a caller's stream joint), stop, the per-handle state machine and the server that
//     runs every handle, time / status / volume / pan accessors;
//   * ADXSJD, the ADX sound-joint decoder (0x541D48-0x5433A8): the 16 decoder handles that pull ADX blocks from an input
//     stream joint and push PCM into one output joint per channel (the header stage, the decode stage, loop / trap
//     points, the accessors the player reads);
//   * the cvFs request layer (0x555B10-0x557A28): device registration and lookup over the 32-slot device table, the
//     file handles, and every request (open / close / seek / tell / read / write / status / sizes / directories /
//     volumes / options) dispatched through the device's interface table;
//   * libmpeg's pure parts (0x4FB168-0x501408): the motion-compensation reference fetch (_getAllRefs / _getRef0 and the
//     16 interpolation kernels _rix_* / _ri0_*), the skipped-macroblock rule, the add-and-clamp of a residual, the
//     sequence buffer layout, the GOP / picture header parsers and the extension / user-data walker, the picture loop
//     of sceMpegGetPicture, the reference rotation and the display hand-off.
// Every function is a p3fes_handgen body on the register ABI (arguments in $a0..$t3, more on the caller's stack from
// $sp + 0 in 8-byte slots, the result in $v0) with its recompiled entry point fn_<name>_<addr8> as the shim. Names are
// symbols/functions.json's (ADR-0009; most are sub_* or FLIRT leftovers such as get_bufs_2 / __env_unlock_0); each
// declaration says the function's role, with a proposed name in [brackets] -- our own, from the instructions and the
// binary's own strings (the error texts name many of them); not imported. Worked from the binary and the public format
// descriptions only (ADX; ISO/IEC 13818-2 video syntax; the MPEG program stream); no CRI or Sony SDK material.
//
// Not taken: docs/INTEGRATION_LOG.md, section "cri2".
#pragma once

#include "p3fes/ee_context.h"
#include "p3fes/game/cri1.h"

namespace p3fes::game {

namespace cri2 {

// --- ADXT: the stream player handle (16 x 200 bytes at 0x787570; sub_547C18 creates, sub_548078 destroys) -----------
namespace adxt {
constexpr u32 kPool = 0x787570u;
constexpr u32 kCount = 16;
constexpr u32 kSize = 200;
constexpr s32 kUsed = 0x00;        // u8: 1 while taken
constexpr s32 kStat = 0x01;        // s8: 0 stopped, 1 opening (header), 2 buffering, 3 playing, 4 decode end, 5 play end, 6 error
constexpr s32 kSource = 0x02;      // u8: 0 file name, 1 partition file id, 2 memory index entry, 3 caller's stream joint, 4 the list streamer
constexpr s32 kMaxCh = 0x03;       // s8: channels the handle was created for (1 / 2)
constexpr s32 kSjd = 0x04;         // the ADXSJD decoder handle
constexpr s32 kStm = 0x08;         // the ADXSTM file streamer (0 for memory / joint sources)
constexpr s32 kRna = 0x0C;         // the PS2RNA output handle
constexpr s32 kSjf = 0x10;         // the SJRBF over the input buffer (the file ring)
constexpr s32 kSji = 0x14;         // the input stream joint the decoder reads (the ring, a memory joint or the caller's)
constexpr s32 kSjo = 0x18;         // [2] the output joints (one per channel, over the PCM buffer)
constexpr s32 kIbuf = 0x20;        // the input buffer (after the PCM buffers in the work area)
constexpr s32 kIbufSize = 0x24;    // its size (whole 2 KiB sectors)
constexpr s32 kIbufXsize = 0x28;   // the extra area after it (36)
constexpr s32 kObuf = 0x2C;        // the PCM buffer (the work area, 64-byte aligned)
constexpr s32 kObufSize = 0x30;    // samples per channel (0x2000)
constexpr s32 kObufDist = 0x34;    // the distance between the channels' buffers in samples (8288)
constexpr s32 kSvrFreq = 0x38;     // the server frequency (calls per second; 0x793B1C at create)
constexpr s32 kMaxSct = 0x3C;      // s16: sectors the input buffer holds
constexpr s32 kMinSct = 0x3E;      // s16: the refill threshold (85 % of kMaxSct)
constexpr s32 kOutVol = 0x40;      // s16: the output volume
constexpr s32 kOutPan = 0x42;      // s16[2]: the per-channel pan (-128 = automatic)
constexpr s32 kMaxDec = 0x48;      // samples the decoder may produce per server call
constexpr s32 kLoopSkip = 0x50;    // bytes of the first loop sector before the loop start
constexpr s32 kErrCode = 0x60;     // s16: -1 after a read / open error
constexpr s32 kLoopFlag = 0x6C;    // u8: 1 = loop (default)
constexpr s32 kFlag6D = 0x6D;      // u8: set by sub_549E28
constexpr s32 kHold = 0x70;        // s8: non-zero holds the start after buffering
constexpr s32 kStarted = 0x71;     // u8: output started
constexpr s32 kPause = 0x72;       // s8: paused
constexpr s32 kAmp = 0x74;         // an attached object the start / stop / destroy paths notify (sub_5358E0 / sub_535A80 / sub_535888)
constexpr s32 kSjoExtra = 0x78;    // [2] more joints released with the handle
constexpr s32 kSjoExtra2 = 0x80;   // [2]
constexpr s32 kTimeOfs = 0x88;     // added to the play time (samples)
constexpr s32 kReadLimit = 0x8C;   // the streamer's read limit (sectors; 0x7FFFFFFF at start)
constexpr s32 kLoopStartSmp = 0x90;  // -1 at start
constexpr s32 kLsc = 0x94;         // the list streamer (source 4)
constexpr s32 kTrapFlag = 0x98;    // u8: mirrored into the decoder (+156)
constexpr s32 kPauseTime = 0x9C;   // the play time when paused
constexpr s32 kVsyncAtPause = 0xA0;  // 0x787568 (the vsync count) at the start / pause
constexpr s32 kTimeSmp = 0xA4;     // samples played before the last loop
constexpr s32 kFlushedSmp = 0xA8;  // silence samples written after the decode end
constexpr s32 kOpenReq = 0xAC;     // u8: 1 = (re)open the source on the next server call
constexpr s32 kPanMode = 0xAD;     // u8: 1 = the header's pan applies (sub_5497A0)
constexpr s32 kFnameBuf = 0xB0;    // the file-name buffer (after the input buffer's extra area)
constexpr s32 kReqFname = 0xB4;    // the open request: name, partition id, first sector, sector count
constexpr s32 kReqPtid = 0xB8;
constexpr s32 kReqOfst = 0xBC;
constexpr s32 kReqNsct = 0xC0;
constexpr s32 kStopSmp = 0xC4;     // the sample the decoder stops at when looping is off
constexpr u32 kPanAuto = 0x787560u;    // non-zero: no automatic stereo pan
constexpr u32 kVsync = 0x787568u;      // the vsync counter the time functions read
constexpr u32 kStmBufSize = 0x793B10u; // the streamer's buffer argument at open
constexpr u32 kTimeLock = 0x793B14u;
constexpr u32 kSvrState = 0x793B18u;   // the server's progress: 0 idle, 1 entered, 2 handles, 3 output
constexpr u32 kDefSvrFreq = 0x793B1Cu;
constexpr u32 kCurSvrFreq = 0x793B20u;
constexpr u32 kHookDestroy0 = 0x793B24u;  // optional callbacks the destroy path calls (sub_547FD0 / FF8 / 548020)
constexpr u32 kHookDestroy1 = 0x793B28u;
constexpr u32 kHookStop = 0x793B2Cu;      // called by the stop path with the handle
constexpr u32 kHookDestroy2 = 0x793B30u;
constexpr u32 kTimeUnit = 0x793B60u;      // the time unit the pause path scales by
constexpr u32 kHookStart = 0x793B68u;     // called when a stream starts (handle, rate, channels, samples)
constexpr u32 kDbgNch = 0x793B6Cu;        // last values the playing state looked at (diagnostics)
constexpr u32 kDbgData = 0x793B70u;
constexpr u32 kDbgQueue = 0x793B74u;
}  // namespace adxt

// --- ADXSJD: the sound-joint decoder handle (16 x 168 bytes at 0x78FF98) --------------------------------------------
namespace adxsjd {
constexpr u32 kPool = 0x78FF98u;
constexpr u32 kCount = 16;
constexpr u32 kSize = 168;
constexpr u32 kInitCount = 0x78FF90u;
constexpr u32 kHeaderHook = 0x78FF94u;  // called after a header was decoded (decoder, its +20)
constexpr s32 kUsed = 0x00;        // u8
constexpr s32 kStat = 0x01;        // s8: 0 stopped, 1 header, 2 decoding, 3 decode end, 4 error
constexpr s32 kNch = 0x02;         // s8
constexpr s32 kAhx = 0x03;         // s8: 1 = the decoder reported format 4
constexpr s32 kAdxb = 0x04;        // the ADXB decoder (0x537890 creates it)
constexpr s32 kSji = 0x08;         // the input joint
constexpr s32 kSjo = 0x0C;         // [2] the output joints
constexpr s32 kInChunk = 0x14;     // {data, size}: the input chunk being decoded
constexpr s32 kOutChunk = 0x1C;    // [2] {data, size}: the output chunks
constexpr s32 kDecSmpl = 0x2C;     // samples decoded since the start
constexpr s32 kDecByte = 0x30;     // input bytes consumed since the start
constexpr s32 kDecSmplTotal = 0x34;  // samples decoded (the trap compares this)
constexpr s32 kMaxDec = 0x38;      // samples per call (0x7FFFFFFF at reset)
constexpr s32 kTrapSmp = 0x3C;     // the trap sample (-1 = none)
constexpr s32 kTrapCnt = 0x40;     // samples counted towards the trap
constexpr s32 kTrapByte = 0x44;
constexpr s32 kTrapFn = 0x48;      // the trap callback and its object
constexpr s32 kTrapObj = 0x4C;
constexpr s32 kFltFn = 0x50;       // the PCM filter callback (channel, data, size) and its object
constexpr s32 kFltObj = 0x54;
constexpr s32 kHdrCopy = 0x58;     // up to 64 header bytes kept for format 2
constexpr s32 kHdrLen = 0x98;      // the header length the decoder reported
constexpr s32 kTrapFlag = 0x9C;    // the player's +152
constexpr s32 kPend0 = 0xA0;       // work the server does under the SVM lock before / after decoding
constexpr s32 kPend1 = 0xA4;
}  // namespace adxsjd

// --- the ADXB decoder record fields the ADXSJD accessors read (the decoder itself is ADXB's) -------------------------
namespace adxb {
constexpr s32 kStat = 0x01;        // s8
constexpr s32 kBlkSmpl = 0x10;     // samples per block
constexpr s32 kRate = 0x14;        // sample rate
constexpr s32 kLoopType = 0x24;    // s16: > 0 = the header has a loop
constexpr s32 kLoopStartSmp = 0x28;
constexpr s32 kLoopStartOfs = 0x2C;
constexpr s32 kLoopEndSmp = 0x30;
constexpr s32 kLoopEndOfs = 0x34;
constexpr s32 kFormat = 0x98;      // s16: the stream kind (0 / 1 / 2 ...; 10, 11, 12, 15, 20 are the AHX / WAV kinds)
constexpr s32 kBits = 0x9C;        // s16: with kFormat, the sample width the time functions use
}  // namespace adxb

// --- cvFs: the device interface (a table of entry points per device) and the file handle --------------------------
namespace cvfs {
using namespace cri1::cvfs;  // kDevices (32 x {interface, name[12]}), kHandles, kDefDev, kErrFn
constexpr u32 kHandleCount = 40;      // cvFsHandleTable: 40 x {interface, device file}
constexpr u32 kAddDevNameBuf = 0x997868u;  // the scratch copy of a path while "DEV:" is prefixed
// interface entries (byte offsets into the device's table)
constexpr s32 kIfExecServer = 0x00;
constexpr s32 kIfEntryErrFn = 0x04;
constexpr s32 kIfGetFileSize = 0x08;
constexpr s32 kIfGetFreeSize = 0x0C;
constexpr s32 kIfOpen = 0x10;
constexpr s32 kIfClose = 0x14;
constexpr s32 kIfSeek = 0x18;
constexpr s32 kIfTell = 0x1C;
constexpr s32 kIfReqRd = 0x20;
constexpr s32 kIfReqWr = 0x24;
constexpr s32 kIfStopTr = 0x28;
constexpr s32 kIfGetStat = 0x2C;
constexpr s32 kIfGetSctLen = 0x30;
constexpr s32 kIfSetSctLen = 0x34;
constexpr s32 kIfGetNumTr = 0x38;
constexpr s32 kIfChangeDir = 0x3C;
constexpr s32 kIfIsExistFile = 0x40;
constexpr s32 kIfGetNumFiles = 0x44;
constexpr s32 kIfLoadDirInfo = 0x48;
constexpr s32 kIfGetMaxByteRate = 0x4C;
constexpr s32 kIfMakeDir = 0x50;
constexpr s32 kIfRemoveDir = 0x54;
constexpr s32 kIfDeleteFile = 0x58;
constexpr s32 kIfGetFileSizeEx = 0x5C;
constexpr s32 kIfOptFn1 = 0x60;       // (arg, code, a, b): the option requests below
constexpr s32 kIfOptFn2 = 0x64;
// file handle {interface, device file}
constexpr s32 kHIf = 0x00;
constexpr s32 kHFile = 0x04;
// OptFn1 codes the layer sends
constexpr s32 kOptSetCurVolume = 1, kOptAddVolume = 2, kOptDelVolume = 3, kOptGetNumFiles = 4, kOptGetVolumeInfo = 5,
              kOptSetDefVol = 6, kOptNeedDevName = 100, kOptGetNumTr64Hi = 200, kOptGetNumTr64Lo = 201,
              kOptGetFileSize64Hi = 202, kOptGetFileSize64Lo = 203, kOptGetFreeSize64Hi = 204,
              kOptGetFreeSize64Lo = 205, kOptGetFsys64 = 299, kOptGetFileSizeByHn = 300;
constexpr u32 kSrdObj = 0x7A08B0u;    // the SRD object sub_557A28 clears (56 bytes)
}  // namespace cvfs

// --- libmpeg: the decoder state (the record sceMpeg's +64 points at; offsets of the fields these bodies use) ---------
namespace mpeg {
constexpr s32 kInner = 0x40;        // sceMpeg handle +64: the decoder state below
constexpr s32 kEnd = 0x000;         // 1 once the stream ended / flushed
constexpr s32 kFrameNo = 0x004;
constexpr s32 kOutState = 0x008;    // 0 nothing shown, 1 first frame, 2 frames shown
constexpr s32 kSkipI = 0x0A8;       // the decode-or-skip limits per picture type (I / P / B)
constexpr s32 kSkipP = 0x0AC;
constexpr s32 kSkipB = 0x0B0;
constexpr s32 kCntI = 0x0B4;        // pictures of each type seen since the last I picture
constexpr s32 kCntP = 0x0B8;
constexpr s32 kCntB = 0x0BC;
constexpr s32 kShownFrame = 0x0C0;
constexpr s32 kPicStructWanted = 0x0E8;
constexpr s32 kImageBuf = 0x0EC;    // the caller's image buffer (64-byte aligned)
constexpr s32 kBrokenLinkPend = 0x0FC;
constexpr s32 kRefBuf0 = 0x10C;     // the three reference frame buffers
constexpr s32 kRefBuf1 = 0x110;
constexpr s32 kRefBuf2 = 0x114;
constexpr s32 kAlloc = 0x118;       // the work-area allocator
constexpr s32 kDecFrame = 0x128;    // frames decoded
constexpr s32 kFieldParity = 0x130; // 1 after the first field of a field pair
constexpr s32 kHsize = 0x134;       // sequence header: horizontal / vertical size
constexpr s32 kVsize = 0x138;
constexpr s32 kMbWidth = 0x13C;
constexpr s32 kMbHeight = 0x140;
constexpr s32 kProgSeq = 0x14C;     // sequence extension: progressive_sequence (1 in the MPEG-1 defaults)
constexpr s32 kSeqExt150 = 0x150;   // further sequence-extension words the MPEG-1 defaults set (1 / 5)
constexpr s32 kSeqExt154 = 0x154;
constexpr s32 kPicType = 0x160;     // picture header: picture_coding_type (1 I, 2 P, 3 B)
constexpr s32 kFullPelFwd = 0x164;
constexpr s32 kFwdFcode = 0x168;
constexpr s32 kFullPelBwd = 0x16C;
constexpr s32 kBwdFcode = 0x170;
constexpr s32 kPicStruct = 0x184;   // picture coding extension: picture_structure (1 top, 2 bottom, 3 frame)
constexpr s32 kPicExt18C = 0x18C;   // further picture-coding-extension words the MPEG-1 defaults set to 1
constexpr s32 kPicExt198 = 0x198;
constexpr s32 kClosedGop = 0x1B4;   // GOP header: closed_gop / broken_link
constexpr s32 kBrokenLink = 0x1B8;
constexpr s32 kTempRef = 0x1BC;     // the picture's temporal reference, made absolute
constexpr s32 kSkipped = 0x1C0;
constexpr s32 kRefFwd = 0x1C8;      // the reference descriptors: forward / backward / current, frame and the two fields
constexpr s32 kRefBwd = 0x1CC;
constexpr s32 kRefCur = 0x1D0;
constexpr s32 kRefDone = 0x28;      // a descriptor's word +40: 1 once the picture in it is complete
constexpr s32 kPicDone = 0x834;     // 1 once a picture was handed to the display
constexpr s32 kPts = 0x838;         // u64 PTS / DTS of the picture
constexpr s32 kDts = 0x840;
constexpr s32 kMpeg2 = 0x858;       // a sequence extension was seen (MPEG-2)
constexpr s32 kGopBase = 0x85C;     // temporal-reference bases: this GOP / the highest so far / first picture flag
constexpr s32 kGopMax = 0x860;
constexpr s32 kGopFirst = 0x864;
constexpr s32 kOutInfo = 0x868;
constexpr s32 kAbort = 0x878;       // sceMpegGetPictureAbort's flag
constexpr s32 kBufType = 0x87C;     // the reference buffers' address space (0 uncached, 1 cached)
// the start codes the parsers meet (ISO/IEC 13818-2)
constexpr u32 kUserData = 0x1B2, kExtension = 0x1B5;
}  // namespace mpeg

}  // namespace cri2

// --- ADXSJD: the sound-joint decoder ----------------------------------------------------------------------------------
void sub_541D48(EEContext& ctx);  // 0x541D48 ADXSJD init: the first call clears the 16 handles. [ADXSJD_Init]
void sub_541DE8(EEContext& ctx);  // 0x541DE8 reset a decoder handle's counters (trap -1, max 0x7FFFFFFF). [adxsjd_ResetCounters]
void sub_541E28(EEContext& ctx);  // 0x541E28 create a decoder handle on an input joint and N output joints (creates the ADXB decoder). [ADXSJD_Create]
void sub_541FA8(EEContext& ctx);  // 0x541FA8 destroy a decoder handle (and its ADXB decoder). [ADXSJD_Destroy]
void sub_542008(EEContext& ctx);  // 0x542008 a decoder handle's state. [ADXSJD_GetStat]
void sub_542010(EEContext& ctx);  // 0x542010 set the input joint (also into the ADXB decoder). [ADXSJD_SetInSj]
void sub_542060(EEContext& ctx);  // 0x542060 set the samples per call (the ADXB decoder gets it and /1536). [ADXSJD_SetMaxDecSmpl]
void sub_5420A0(EEContext& ctx);  // 0x5420A0 tell the ADXB decoder the input ended. [ADXSJD_TermSupply]
void sub_5420D0(EEContext& ctx);  // 0x5420D0 start: reset the counters, state 1 (header). [ADXSJD_Start]
void sub_542100(EEContext& ctx);  // 0x542100 stop: stop the ADXB decoder, state 0. [ADXSJD_Stop]
void sub_542130(EEContext& ctx);  // 0x542130 the header stage: skip zero padding, hand the header to ADXB, keep it for format 2, state 2 or 4. [adxsjd_DecodeHeader]
void sub_542438(EEContext& ctx);  // 0x542438 the ADXB decoder's output callback: free room per channel, samples allowed before the trap. [adxsjd_GetWrInfo]
void sub_542558(EEContext& ctx);  // 0x542558 the decode stage's input side: the trap, an AHX resync, feed ADXB the input chunk. [adxsjd_DecodeExec]
void sub_5428C0(EEContext& ctx);  // 0x5428C0 the decode stage's output side: put the consumed input back, the PCM chunks forward, run the filter. [adxsjd_DecodeEnd]
void sub_542B18(EEContext& ctx);  // 0x542B18 one decode step (exec ADXB, then collect; the AHX / WAV kinds finish in sub_542A88). [adxsjd_ExecDecode]
void sub_542BC8(EEContext& ctx);  // 0x542BC8 run one decoder handle (pending work under the SVM lock, header or decode stage). [ADXSJD_ExecHndl]
void sub_542F00(EEContext& ctx);  // 0x542F00 run every used decoder handle. [ADXSJD_ExecServer]
void sub_542F60(EEContext& ctx);  // 0x542F60 input bytes consumed. [ADXSJD_GetDecDtLen]
void sub_542F68(EEContext& ctx);  // 0x542F68 samples decoded. [ADXSJD_GetDecNumSmpl]
void sub_542F88(EEContext& ctx);  // 0x542F88 set the decoded-samples total (+52). [ADXSJD_SetDecNumSmpl]
void sub_5430A8(EEContext& ctx);  // 0x5430A8 set the trap callback and its object. [ADXSJD_EntryTrapFunc]
void sub_5430B8(EEContext& ctx);  // 0x5430B8 set the trap sample. [ADXSJD_SetTrapNumSmpl]
void sub_5430C8(EEContext& ctx);  // 0x5430C8 set the trap count. [ADXSJD_SetTrapCnt]
void sub_5430D8(EEContext& ctx);  // 0x5430D8 set the trap byte count. [ADXSJD_SetTrapDtLen]
void sub_5430E8(EEContext& ctx);  // 0x5430E8 the ADXB decoder's format. [ADXSJD_GetFormat]
void sub_543100(EEContext& ctx);  // 0x543100 the sample rate. [ADXSJD_GetSfreq]
void sub_543118(EEContext& ctx);  // 0x543118 the channel count. [ADXSJD_GetNumChan]
void sub_543130(EEContext& ctx);  // 0x543130 bits per sample for the time functions: 16, or 4 / 8 for the AHX kinds. [ADXSJD_GetOutBps]
void sub_543148(EEContext& ctx);  // 0x543148 samples per block. [ADXSJD_GetBlkSmpl]
void sub_543178(EEContext& ctx);  // 0x543178 the total samples of the stream. [ADXSJD_GetTotalNumSmpl]
void sub_5431A8(EEContext& ctx);  // 0x5431A8 the loop type (> 0 = looped). [ADXSJD_GetLpInsNsmpl]
void sub_5431D8(EEContext& ctx);  // 0x5431D8 the loop start sample. [ADXSJD_GetLpStartPos]
void sub_5431F0(EEContext& ctx);  // 0x5431F0 the loop start offset (0 for a null handle or decoder). [ADXSJD_GetLpStartOfst]
void sub_543220(EEContext& ctx);  // 0x543220 the loop end sample. [ADXSJD_GetLpEndPos]
void sub_543238(EEContext& ctx);  // 0x543238 the loop end offset. [ADXSJD_GetLpEndOfst]
void sub_543268(EEContext& ctx);  // 0x543268 the header's volume while decoding (0 otherwise). [ADXSJD_GetDefOutVol]
void sub_5432C0(EEContext& ctx);  // 0x5432C0 the header's pan of a channel while decoding (-128 otherwise). [ADXSJD_GetDefPan]
void sub_5433A8(EEContext& ctx);  // 0x5433A8 seek the ADXB decoder to the loop start. [ADXSJD_SetLpStart]

// --- ADXT: the stream player ----------------------------------------------------------------------------------------
void sub_547BC0(EEContext& ctx);  // 0x547BC0 create (locked). [ADXT_Create]
void sub_547C18(EEContext& ctx);  // 0x547C18 create a player: take a free handle, lay the work area out (PCM buffers, input ring, name buffer), create the ring joint, the streamer, the output joints, the decoder, the output and the list streamer. [adxt_Create]
void sub_547FD0(EEContext& ctx);  // 0x547FD0 call the optional destroy hook 0x793B24. [adxt_CallDestroyHook0]
void sub_547FF8(EEContext& ctx);  // 0x547FF8 call the optional destroy hook 0x793B28 with the handle. [adxt_CallDestroyHook1]
void sub_548020(EEContext& ctx);  // 0x548020 call the optional destroy hook 0x793B30 with the handle. [adxt_CallDestroyHook2]
void sub_548048(EEContext& ctx);  // 0x548048 destroy (locked). [ADXT_Destroy]
void sub_548078(EEContext& ctx);  // 0x548078 destroy a player: stop it, release the output, decoder, streamer, list streamer and joints, clear the 200 bytes. [adxt_Destroy]
void sub_548318(EEContext& ctx);  // 0x548318 the common start: reset the output joints, give the decoder its input, start it, state 1. [adxt_StartSj0]
void sub_548410(EEContext& ctx);  // 0x548410 open the file stream: buffer limits, stop / seek / start the streamer, then the common start. [adxt_StartStm]
void sub_5484E0(EEContext& ctx);  // 0x5484E0 start on a caller's joint (locked). [ADXT_StartSj]
void sub_548520(EEContext& ctx);  // 0x548520 start on a caller's stream joint (source 3). [adxt_StartSj]
void sub_5485D8(EEContext& ctx);  // 0x5485D8 the common stop: output off, decoder stop, release a memory source's joint, state 0. [adxt_StopWithoutLsc]
void sub_548678(EEContext& ctx);  // 0x548678 stop (locked). [ADXT_Stop]
void sub_5486A8(EEContext& ctx);  // 0x5486A8 stop: the stop hook, the streamer, the list streamer for source 4, then the common stop. [adxt_Stop]
void sub_548768(EEContext& ctx);  // 0x548768 status (locked). [ADXT_GetStat (one of the copies)]
void sub_5487A0(EEContext& ctx);  // 0x5487A0 a player's state (-1 for a null handle). [adxt_GetStat]
void sub_5489A0(EEContext& ctx);  // 0x5489A0 the play time as (samples, rate): from the output while playing, the total at the end. [adxt_GetTimeSfreq]
void sub_548AE8(EEContext& ctx);  // 0x548AE8 the play time (locked; the body is sceInsockBind_2, a FLIRT name). [ADXT_GetTime]
void sub_548EB8(EEContext& ctx);  // 0x548EB8 total samples (locked). [ADXT_GetNumSmpl]
void sub_548EF0(EEContext& ctx);  // 0x548EF0 the stream's total samples once the header is known. [adxt_GetNumSmpl]
void sub_548F40(EEContext& ctx);  // 0x548F40 sample rate (locked). [ADXT_GetSfreq]
void sub_548F78(EEContext& ctx);  // 0x548F78 the stream's sample rate once the header is known. [adxt_GetSfreq]
void sub_5491B0(EEContext& ctx);  // 0x5491B0 set a channel's pan (the header's pan added; -128 = automatic: +-15 for stereo). [adxt_SetOutPan]
void sub_549480(EEContext& ctx);  // 0x549480 set the volume (locked). [ADXT_SetOutVol]
void sub_5494C0(EEContext& ctx);  // 0x5494C0 set the volume (the header's volume added). [adxt_SetOutVol]
void sub_5497A0(EEContext& ctx);  // 0x5497A0 store the pan mode byte (+173). [adxt_SetPanMode]
void sub_5497B0(EEContext& ctx);  // 0x5497B0 set the default server frequency (locked). [ADXT_SetDefSvrFreq]
void sub_5497E0(EEContext& ctx);  // 0x5497E0 set the default and current server frequency. [adxt_SetDefSvrFreq]
void sub_5497F8(EEContext& ctx);  // 0x5497F8 set a player's server frequency (locked). [ADXT_SetSvrFreq]
void sub_549838(EEContext& ctx);  // 0x549838 set a player's server frequency (and the current one). [adxt_SetSvrFreq]
void sub_549BB0(EEContext& ctx);  // 0x549BB0 samples waiting in a channel's output joint. [adxt_GetNumSmplObuf]
void sub_549DE8(EEContext& ctx);  // 0x549DE8 store byte +109 (locked). [ADXT_SetFlag6D]
void sub_549E28(EEContext& ctx);  // 0x549E28 store byte +109. [adxt_SetFlag6D]
void sub_549EA0(EEContext& ctx);  // 0x549EA0 the server (locked). [ADXT_ExecServer]
void sub_549EC8(EEContext& ctx);  // 0x549EC8 the server: once (re-entry guarded), run the decoders, every used player, then the output twice at low frequencies. [adxt_ExecServer]
void sub_549FF8(EEContext& ctx);  // 0x549FF8 the error code (locked). [ADXT_GetErrCode]
void sub_54A030(EEContext& ctx);  // 0x54A030 a player's error code (+96). [adxt_GetErrCode]
void sub_54A138(EEContext& ctx);  // 0x54A138 set the loop flag (locked). [ADXT_SetLpFlg]
void sub_54A178(EEContext& ctx);  // 0x54A178 set the loop flag; the stop sample becomes the end of the current loop pass. [adxt_SetLpFlg]
void sub_54A3C0(EEContext& ctx);  // 0x54A3C0 pause / resume (locked). [ADXT_Pause]
void get_bufs_2(EEContext& ctx);  // 0x54A400 pause / resume: the output's pause and the play time at the pause (a FLIRT name). [adxt_Pause]
void sub_54A530(EEContext& ctx);  // 0x54A530 the pause state (locked). [ADXT_GetStatPause]
void sub_54A568(EEContext& ctx);  // 0x54A568 a player's pause state (+114). [adxt_GetStatPause]
void __env_unlock_0(EEContext& ctx);  // 0x54A638 an empty stub the opening state calls (`jr $ra`; a FLIRT name). [adxt_GetHdrPan (stub)]
void sub_54A968(EEContext& ctx);  // 0x54A968 set the trap flag (+152, and into the decoder). [adxt_SetTrapFlag]
void sub_54B088(EEContext& ctx);  // 0x54B088 start a partition file (locked). [ADXT_StartAfs]
void sub_54B0D8(EEContext& ctx);  // 0x54B0D8 start file N of a partition (source 1): the file's range from ADXF, else error state 6. [adxt_StartAfs]
void sub_54B230(EEContext& ctx);  // 0x54B230 start a named file range (source 0): copy the name, request the open. [adxt_StartFnameRange]
void sub_54B2E8(EEContext& ctx);  // 0x54B2E8 start a named file (locked). [ADXT_StartFname]
void sub_54B328(EEContext& ctx);  // 0x54B328 start a named file: the whole range (0, 0xFFFFF sectors). [adxt_StartFname]
void sub_54B4D0(EEContext& ctx);  // 0x54B4D0 start a memory index entry (locked). [ADXT_StartMemIdx]
void sub_54B520(EEContext& ctx);  // 0x54B520 start entry N of a memory index (big-endian count and offsets): an SJMEM joint over it (source 2). [adxt_StartMemIdx]
void sub_54B690(EEContext& ctx);  // 0x54B690 the loop trap installer: decode up to the loop end, trap there into sub_54B748. [adxt_SetLoopTrap]
void sub_54B988(EEContext& ctx);  // 0x54B988 apply the pans (one or both channels). [adxt_SetOutPanAll]
void sub_54B9F0(EEContext& ctx);  // 0x54B9F0 the trap at the end of a stream with a trailer: resync on the next header (AHX) and restart the decoder seamlessly. [adxt_TrapEntry]
void sub_54BCD8(EEContext& ctx);  // 0x54BCD8 state 1: open the source, wait for the header, set the output (rate, channels, volume, pans), install the loop or end trap, state 2. [adxt_ExecPrep]
void sub_54C100(EEContext& ctx);  // 0x54C100 state 2: wait until enough PCM is queued, start the output (unless held), state 3. [adxt_ExecBuffering]
void sub_54C288(EEContext& ctx);  // 0x54C288 state 3: the loop-off stop sample, then the decode end once every output joint is nearly empty, state 4. [adxt_ExecPlaying]
void sub_54C370(EEContext& ctx);  // 0x54C370 state 4: pad the output with silence until it has played out, then stop the output, state 5. [adxt_ExecDecEnd]
void sub_54C578(EEContext& ctx);  // 0x54C578 state 5: nothing (`jr $ra`). [adxt_ExecPlayEnd]
void sub_54C8C0(EEContext& ctx);  // 0x54C8C0 the error check: a failed streamer or list streamer puts the player in state 6 (error -1). [adxt_ExecErrChk]
void sub_54C940(EEContext& ctx);  // 0x54C940 the end-of-input check: tell the decoder when a file / memory source has delivered everything. [adxt_ExecTermSupply]
void sub_54C9D8(EEContext& ctx);  // 0x54C9D8 run one player (locked). [ADXT_ExecHndl]
void sub_54CA08(EEContext& ctx);  // 0x54CA08 run one player: its state's step, then the end-of-input and error checks. [adxt_ExecHndl]
void sub_539818(EEContext& ctx);  // 0x539818 the ADX libraries' SVM lock (type 1 through sub_564978). [adxcrs_Lock]
void sub_539830(EEContext& ctx);  // 0x539830 the matching unlock (sub_564990). [adxcrs_Unlock]

// --- cvFs: devices and requests -------------------------------------------------------------------------------------
void cvFsAddDev(EEContext& ctx);  // 0x555B10 register a device (name, interface getter); give it the error callback. ["cvFsAddDev"]
void cvfs_addDevice(EEContext& ctx);  // 0x555BA0 add a device to the first free slot unless the name is taken (upper-cased name). [cvfs_addDevice]
void cvfs_getDevice(EEContext& ctx);  // 0x555C78 the interface of the device whose name starts with the given one (strncmp over 32 slots), or 0. [cvfs_getDevice]
void sub_555D70(EEContext& ctx);  // 0x555D70 remove a device: clear the first byte of its name. [cvFsDelDev]
void sub_555E48(EEContext& ctx);  // 0x555E48 set the default device (upper-cased; must be registered; "" clears it). [cvFsSetDefDev]
void sub_555F10(EEContext& ctx);  // 0x555F10 is a device of that name registered (1 / 0). [cvfs_isExistDev]
void cvfs_variousProc(EEContext& ctx);  // 0x555FA0 resolve a split path: the named device, else the default device (the path then keeps its "DEV:" part). [cvfs_variousProc]
void cvFsOpen(EEContext& ctx);  // 0x556048 open a file: split "DEV:file", take a handle, resolve the device, call its Open. ["cvFsOpen"]
void sub_556170(EEContext& ctx);  // 0x556170 the first free file handle of the 40. [cvfs_allocHandle]
void sub_5561D8(EEContext& ctx);  // 0x5561D8 release a file handle. [cvfs_freeHandle]
void cvFsClose(EEContext& ctx);  // 0x556398 close: the device's Close, release the handle. ["cvFsClose"]
void cvFsTell(EEContext& ctx);  // 0x556410 the device's Tell. ["cvFsTell"]
void cvFsSeek(EEContext& ctx);  // 0x556478 the device's Seek. ["cvFsSeek"]
void cvFsReqRd(EEContext& ctx);  // 0x5564E0 the device's read request. ["cvFsReqRd"]
void sub_556548(EEContext& ctx);  // 0x556548 the device's write request. [cvFsReqWr]
void sub_5565B0(EEContext& ctx);  // 0x5565B0 the device's transfer stop. [cvFsStopTr]
void cvFsExecServer(EEContext& ctx);  // 0x556608 every registered device's server. ["cvFsExecServer"]
void cvFsGetStat(EEContext& ctx);  // 0x556668 the device's status (3 = error for a bad handle). ["cvFsGetStat"]
void cvFsGetFileSize(EEContext& ctx);  // 0x5566D0 a file's size through its device. ["cvFsGetFileSize"]
void sub_556790(EEContext& ctx);  // 0x556790 a file's size, second form (interface +92). [cvFsGetFileSizeEx]
void sub_556860(EEContext& ctx);  // 0x556860 a file's size by handle (OptFn1 code 300; 0x7FFFFFFF without OptFn1). [cvFsGetFileSizeByHndl]
void sub_5568C0(EEContext& ctx);  // 0x5568C0 a device's free size (the default device when none named). [cvFsGetFreeSize]
void sub_556A00(EEContext& ctx);  // 0x556A00 the device's sector length. [cvFsGetSctLen]
void sub_556A68(EEContext& ctx);  // 0x556A68 set the device's sector length. [cvFsSetSctLen]
void sub_556AC0(EEContext& ctx);  // 0x556AC0 the device's transferred count. [cvFsGetNumTr]
void sub_556B28(EEContext& ctx);  // 0x556B28 change directory through the device. [cvFsChangeDir]
void sub_556BE8(EEContext& ctx);  // 0x556BE8 does a file exist (through the device). [cvFsIsExistFile]
void sub_556C90(EEContext& ctx);  // 0x556C90 the number of files on a device (its GetNumFiles, or OptFn1 code 4 for a device that wants its name). [cvFsGetNumFiles]
void sub_556DA0(EEContext& ctx);  // 0x556DA0 load directory information through the device. [cvFsLoadDirInfo]
void sub_556E78(EEContext& ctx);  // 0x556E78 the device's maximum byte rate. [cvFsGetMaxByteRate]
void sub_556ED0(EEContext& ctx);  // 0x556ED0 make a directory through the device. [cvFsMakeDir]
void sub_556F90(EEContext& ctx);  // 0x556F90 remove a directory through the device. [cvFsRemoveDir]
void sub_557050(EEContext& ctx);  // 0x557050 delete a file through the device. [cvFsDeleteFile]
void sub_557110(EEContext& ctx);  // 0x557110 the device name of a file handle (the slot whose interface matches). [cvFsGetDevName]
void sub_557198(EEContext& ctx);  // 0x557198 set the cvFs error callback and its object (0 clears both). [cvFsEntryErrFunc]
void sub_5571C0(EEContext& ctx);  // 0x5571C0 the device's OptFn1 with the handle's file. [cvFsOptFn1]
void sub_557228(EEContext& ctx);  // 0x557228 the device's OptFn2 with the handle's file. [cvFsOptFn2]
void cvFsSetCurVolume(EEContext& ctx);  // 0x557290 select a device's current volume (OptFn1 code 1). ["cvFsSetCurVolume"]
void sub_557350(EEContext& ctx);  // 0x557350 returns 0 (`jr $ra` + clear). [cvfs_nop]
void cvFsAddVolumeEx(EEContext& ctx);  // 0x557358 add a volume to a device (OptFn1 code 2: image handle, name, mode). ["cvFsAddVolumeEx"]
void sub_557460(EEContext& ctx);  // 0x557460 remove a volume (OptFn1 code 3). [cvFsDelVolume]
void sub_557520(EEContext& ctx);  // 0x557520 volume information (OptFn1 code 5). [cvFsGetVolumeInfo]
void cvFsSetDefVol(EEContext& ctx);  // 0x5575F0 set a device's default volume (OptFn1 code 6). ["cvFsSetDefVol"]
void cvfs_isNeedDevName(EEContext& ctx);  // 0x5576B0 does the device want "DEV:" in its paths (OptFn1 code 100). [cvfs_isNeedDevName]
void cvfs_addDevName(EEContext& ctx);  // 0x557700 prefix "DEV:" (sprintf "%s:%s") when the device wants it. [cvfs_addDevName]
void sub_557798(EEContext& ctx);  // 0x557798 is the device registered (1 / 0). [cvFsIsAvailableDev]
void sub_5577B8(EEContext& ctx);  // 0x5577B8 the 64-bit transferred count (OptFn1 codes 200 / 201). [cvFsGetNumTr64]
void sub_557850(EEContext& ctx);  // 0x557850 the 64-bit file size (OptFn1 codes 202 / 203). [cvFsGetFileSize64]
void sub_557908(EEContext& ctx);  // 0x557908 the 64-bit free size (OptFn1 codes 204 / 205). [cvFsGetFreeSize64]
void sub_5579C8(EEContext& ctx);  // 0x5579C8 the file system's 64-bit flag (OptFn1 code 299). [cvFsGetFsys64Info]
void sub_557A28(EEContext& ctx);  // 0x557A28 clear the SRD object (56 bytes at 0x7A08B0). [srd_Clear]

// --- libmpeg: motion compensation, headers, the picture loop --------------------------------------------------------
void _getAllRefs(EEContext& ctx);  // 0x4FB168 set up every reference fetch of a macroblock: frame / field / dual-prime prediction, forward and backward (motion_type per picture structure). [_getAllRefs]
void _getRef0(EEContext& ctx);  // 0x4FBAC0 set up one reference fetch: the source macroblock addresses for a vector, the rows before / after the macroblock boundary, the luma and chroma kernels by half-pel bits and averaging. [_getRef0]
void _skipMB0(EEContext& ctx);  // 0x4FD8A8 a skipped macroblock: reset vectors in P pictures, keep the motion type; not allowed in I pictures. [_skipMB0]
void _copyAddRefImage(EEContext& ctx);  // 0x4FD968 add a 16-bit residual to the 8-bit prediction, clamp 0..255, pack (MMI). [_copyAddRefImage]
void _rix_000(EEContext& ctx);  // 0x4FDC98 luma fetch, full-pel, no averaging (16-bit out, MMI). [_rix_000]
void _ri0_000(EEContext& ctx);  // 0x4FDD10 chroma fetch, full-pel, no averaging. [_ri0_000]
void _rix_001(EEContext& ctx);  // 0x4FDDA8 luma fetch, vertical half-pel. [_rix_001]
void _ri0_001(EEContext& ctx);  // 0x4FDE60 chroma fetch, vertical half-pel. [_ri0_001]
void _rix_010(EEContext& ctx);  // 0x4FDF30 luma fetch, horizontal half-pel. [_rix_010]
void _ri0_010(EEContext& ctx);  // 0x4FDFE0 chroma fetch, horizontal half-pel. [_ri0_010]
void _rix_011(EEContext& ctx);  // 0x4FE098 luma fetch, both half-pel. [_rix_011]
void _ri0_011(EEContext& ctx);  // 0x4FE190 chroma fetch, both half-pel. [_ri0_011]
void _rix_100(EEContext& ctx);  // 0x4FE290 luma fetch averaged with the prediction already there (bidirectional), full-pel. [_rix_100]
void _ri0_100(EEContext& ctx);  // 0x4FE330 chroma, averaged, full-pel. [_ri0_100]
void _rix_101(EEContext& ctx);  // 0x4FE3E0 luma, averaged, vertical half-pel. [_rix_101]
void _ri0_101(EEContext& ctx);  // 0x4FE4C0 chroma, averaged, vertical half-pel. [_ri0_101]
void _rix_110(EEContext& ctx);  // 0x4FE5A8 luma, averaged, horizontal half-pel. [_rix_110]
void _ri0_110(EEContext& ctx);  // 0x4FE680 chroma, averaged, horizontal half-pel. [_ri0_110]
void _rix_111(EEContext& ctx);  // 0x4FE750 luma, averaged, both half-pel. [_rix_111]
void _ri0_111(EEContext& ctx);  // 0x4FE870 chroma, averaged, both half-pel. [_ri0_111]
void _initSeq(EEContext& ctx);  // 0x4FEBC8 a new sequence: MPEG-1 defaults, macroblock counts, (re)allocate the three reference frames on a size change, the 12 reference descriptors. [_initSeq]
void _groupOfPicturesHeader(EEContext& ctx);  // 0x4FF190 parse a GOP header (time code, closed_gop, broken_link); new temporal-reference base. [_groupOfPicturesHeader]
void _pictureHeader(EEContext& ctx);  // 0x4FF230 parse a picture header (temporal_reference, picture_coding_type, vbv_delay, the f-codes, extra info) and make the temporal reference absolute. [_pictureHeader]
void _extensionAndUserData(EEContext& ctx);  // 0x4FF7C8 walk the extensions (to the 11 handlers of 0x7BD7E8 by extension id) and user data up to the next start code. [_extensionAndUserData]
void flushBuf32(EEContext& ctx);  // 0x4FFB30 drop 32 bits (a start code). [flushBuf32]
void _getpic(EEContext& ctx);  // 0x500278 the picture loop of sceMpegGetPicture: next header, decode or skip by picture type, until a picture is shown or the stream ends. [_getpic]
void _updateRefImage(EEContext& ctx);  // 0x500430 rotate the reference frames for the next picture and decide whether it can be decoded (its references complete); copy the picture's parameters into the current descriptor. [_updateRefImage]
void _decodeOrSkipFrame(EEContext& ctx);  // 0x5006E8 decode a frame picture (or skip it past the type's limit through the skip callback), then the output. [_decodeOrSkipFrame]
void _decodeOrSkip(EEContext& ctx);  // 0x500E00 frame or field picture. [_decodeOrSkip]
void _decPicture(EEContext& ctx);  // 0x500F98 decode the picture data into the current descriptor (mark it complete). [_decPicture]
void _dispRefImage(EEContext& ctx);  // 0x501408 hand a complete reference picture to the display: PTS, the picture-info word, the colour conversion or the 8-bit copy. [_dispRefImage]

}  // namespace p3fes::game
