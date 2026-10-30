// Phase 5 slice libs9: the CRI middleware's small pieces, third pass (game/src/cri/libs9.cpp,
// tests/game/test_libs9.cpp), under the relaxed callee rule (callees that stay recompiled are called through their
// gen:: entry points). What is here (150 functions, 0x540D70-0x54FE58):
//   * ADXM's thread layer: the thread setup / shutdown with the priority record, the guarded file-system server tick,
//     the mode switch, the debug-print level and its printf, small PS2RNA output accessors;
//   * the ADX encoder (8 x 760-byte handles at 0x790A38): init / finish, create / destroy, configuration, start / stop,
//     the server and its stages, the header writer (0x8000 signature, loops, AINF / CINF chunks, the copyright string)
//     and the footer (0x8001);
//   * ADXSTM / ADXT accessors (the 200-byte ADXT handle of cri2.h): the decoder / streamer / joint getters, the refill
//     threshold, buffered time, the pause clock, the silence pre-fill, the restart, the locked wrappers;
//   * the MPEG-audio (Layer II) decoder used by the movie player: handle table, frame sync and header parse, the bit
//     allocation / scale-factor / sample readers, the granule loop and the MMI synthesis kernels.
// Every function is a p3fes_handgen body on the register ABI (arguments in $a0..$t3, the result in $v0) with its
// recompiled entry point fn_<name>_<addr8> as the shim. Names are symbols/functions.json's (ADR-0009); each declaration
// says the function's role, with a proposed name in [brackets] where the role is clear (symbols/deltas/libs9.sym).
// Worked from the binary and the public ADX / ISO 11172-3 format descriptions only; no CRI or Sony SDK material.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace libs9 {

// --- the ADX encoder handle (8 x 760 bytes at 0x790A38; sub_545208 creates, sub_5453D8 destroys) ----------------------
namespace adxenc {
constexpr u32 kPool = 0x790A38u;
constexpr u32 kCount = 8;
constexpr u32 kSize = 760;
constexpr s32 kUsed = 0;         // u8: 1 while taken
constexpr s32 kState = 1;        // s8: 1 header stage, 2 data stage, 3 done
constexpr s32 kNchIn = 2;        // u8: channel joints given at create
constexpr s32 kEnd = 3;          // u8: stop requested (the footer follows)
constexpr s32 kSjIn = 4;         // [2] the PCM input joints, one per channel
constexpr s32 kSjOut = 12;       // the ADX output joint
constexpr s32 kCnt40 = 40;       // cleared at create / start
constexpr s32 kOutBytes = 44;    // bytes written to the output joint
constexpr s32 kSmplDone = 48;    // samples encoded
constexpr s32 kLimit = 60;       // the sample count the data stage stops at (= kTotal when configured)
constexpr s32 kWorkSize = 68;    // the work buffers' size (32)
constexpr s32 kHdrOfs = 72;      // the header offset (the data start - 4; 284 when configured)
constexpr s32 kEncoding = 76;    // 3 = ADX
constexpr s32 kBlockSize = 80;   // 18 bytes
constexpr s32 kBits = 84;        // 4
constexpr s32 kNch = 88;         // channels
constexpr s32 kRate = 92;        // the sample rate (44100 by default)
constexpr s32 kTotal = 96;       // total samples
constexpr s32 kHighpass = 100;   // the high-pass cut-off (500)
constexpr s32 kAlignSmpl = 104;  // loop alignment samples (the start pre-fills 2 * this many bytes of silence)
constexpr s32 kLoopCnt = 108;    // loops (0 or 1)
constexpr s32 kLoop = 112;       // the loop record: 4 words written after (index, 1)
constexpr s32 kWork = 128;       // [2] per-channel predictor work (sub_543BF0)
constexpr s32 kHist = 712;       // s16[4]: the predictor history written to the header
constexpr s32 kFlag720 = 720;    // s16: non-zero sets header flag 8
constexpr s32 kAinf = 726;       // u8: 1 = write the AINF chunk
constexpr s32 kAinfData = 727;   // u8[16]
constexpr s32 kAinfVol = 744;    // s16: the volume (0 at create)
constexpr s32 kAinfPanL = 746;   // s16 (-128 at create)
constexpr s32 kAinfPanR = 748;   // s16 (-128 at create)
constexpr s32 kCinf = 750;       // s8: 1 = write the CINF chunk
constexpr s32 kCinfData = 752;   // its bytes
constexpr s32 kCinfSize = 756;   // their count
}  // namespace adxenc

// --- the MPEG-audio decoder handle (16 slots at 0x797598; sub_54E180 creates over a caller's work area) -----------------
namespace mpa {
constexpr u32 kTable = 0x797598u;
constexpr s32 kSamples = 0;      // the sample buffer (the work area + 35, 32-byte aligned)
constexpr s32 kReady = 420;      // u8
constexpr s32 kSlot = 422;       // s8: its slot in the table
constexpr s32 kGranule = 424;    // granules decoded in this frame (12 = done)
constexpr s32 kBitRd = 428;      // the bit reader
constexpr s32 kSynth = 432;      // the synthesis work (sub_551AD8)
constexpr s32 kInfo = 484;       // the info block from the in-stream header
constexpr s32 kInfoNch = 488;    // channels (kInfo + 4)
constexpr s32 kKey = 2592;       // u16[4]: the stream key
}  // namespace mpa

}  // namespace libs9

// 0x540D70: Returns the word 0x788680 (FLIRT's __errno is a shape match: a one-word getter).
void __errno_0(EEContext& ctx);
// 0x541040: Tail-calls sub_541008 with the caller's arguments.
void sub_541040(EEContext& ctx);
// 0x541058: The file-system server tick, re-entry guarded: when the busy word 0x788758 is 0 it sets it, runs
// sub_549EA0 (the ADXT server) and ADXT_UpdateFsStat, then clears it; returns 0. [adxm_ExecFsSvr]
void sub_541058(EEContext& ctx);
// 0x5410A0: ADXM_SetupThrd with a parameter record built on the stack from a 4-word caller record ($a0: priorities at
// +0..+12; the copy holds +8 + 1 and a fixed 25), or with null when $a0 is null.
void sub_5410A0(EEContext& ctx);
// 0x541100: Tail-calls sub_540768 (the thread-layer shutdown, owned by another slice).
void sub_541100(EEContext& ctx);
// 0x541118: The guarded server tick under the ADXM lock: sub_540D40 (lock); if the busy word 0x788758 is set, unlock
// and return; else set it, unlock, run the ADXT server and ADXT_UpdateFsStat, clear it.
void sub_541118(EEContext& ctx);
// 0x541180: Tail-calls sub_564978.
void sub_541180(EEContext& ctx);
// 0x541198: Tail-calls sub_564990.
void sub_541198(EEContext& ctx);
// 0x5411B0: ADXM_SetupThrdEx: the first call (use count 0x788644 == 0) installs the vsync / idle hooks, copies the
// caller's 12-word thread-priority record (or the defaults 1, 8, 15, 16, 18, 24, 25, 26) into 0x788650.., records the
// main thread id (0x7886E8) and its priority (0x78FF78), creates the safe / vsync / file-system / idle threads and
// raises the main thread to the configured priority; every call bumps the use count and returns it.
void ADXM_SetupThrdEx(EEContext& ctx);
// 0x5413A0: The ADXM shutdown: the last release (use count 0x788644 drops to 0) destroys the seven ADXM threads,
// restores the main thread's priority, removes the hooks and clears 0x788648. [ADXM_ShutdownThrd]
void sub_5413A0(EEContext& ctx);
// 0x541450: Registers a callback ($a0, $a1) in slot 1 of sub_564FD0's table (kind 0).
void sub_541450(EEContext& ctx);
// 0x541478: Registers a callback ($a0, $a1) in slot 7 of sub_564FD0's table (kind 0).
void sub_541478(EEContext& ctx);
// 0x5414A0: Calls sub_5651B0(7): the slot-7 query.
void sub_5414A0(EEContext& ctx);
// 0x5414B8: Stores the four arguments into the record 0x997038 (+0..+12) and returns its address.
void sub_5414B8(EEContext& ctx);
// 0x541540: Selects the ADXM thread mode ($a0, kept in 0x78FF7C): mode 1 returns 1 at once; modes 0 and 2 set up the
// threads with $a1's record and return 1; any other mode returns 0. sub_53F630 gets sub_541610's value first.
void sub_541540(EEContext& ctx);
// 0x5415C0: The counterpart of sub_541540: modes 0 / 2 shut the threads down, mode 1 does nothing, others report 0;
// sub_53F630(-1) runs last.
void sub_5415C0(EEContext& ctx);
// 0x541628: Returns the debug-print level word 0x78FF80.
void __errno_1(EEContext& ctx);
// 0x541638: Sets the debug-print level ($a0 into 0x78FF80 and 0x7A2A78) around WTLS_set_table.
void sub_541638(EEContext& ctx);
// 0x541668: A printf-style debug print: spills the variadic register arguments ($a1..$t3, $f12..$f19) to the frame,
// formats into a 128-byte stack buffer with vsprintf and prints with scePrintf unless the level word 0x78FF80 is 2.
void sub_541668(EEContext& ctx);
// 0x5417F8: Channel $a1's stream joint (handle +12 -> +8 + 4 * $a1 -> +8), asked for its line-1 data size through its
// interface (+36): the result halved (bytes -> 16-bit samples).
void sub_5417F8(EEContext& ctx);
// 0x541838: As sub_5417F8 for line 0 (free space).
void sub_541838(EEContext& ctx);
// 0x541878: Channel $a1's output (+4 of its record) through sub_564218(.., 1), halved.
void sub_541878(EEContext& ctx);
// 0x5418B0: As sub_541878 with line 0.
void sub_5418B0(EEContext& ctx);
// 0x5418E8: Tail-calls sub_560240.
void sub_5418E8(EEContext& ctx);
// 0x541900: Tail-calls sub_5603D8.
void sub_541900(EEContext& ctx);
// 0x541918: Tail-calls sub_560448.
void sub_541918(EEContext& ctx);
// 0x541930: Sets byte +84 of the output record ($a0 +12) to $a1 when it differs, unless mode 0x7A93F8 is 1 with
// 0x7A93F0 <= 0; $a1 == 1 is taken only when 0x7A9420 is set; the tail lives in the second chunk at 0x5604B0.
void sub_541930(EEContext& ctx);
// 0x541948: Sets byte +86 of the output record ($a0 +12) to $a1 when it differs and the mode word 0x7A9438 is 2 (gated
// as sub_541930); second chunk at 0x560500.
void sub_541948(EEContext& ctx);
// 0x541960: Returns the signed byte +87 of the output record ($a0 +12); second chunk at 0x560550.
void sub_541960(EEContext& ctx);
// 0x544900: The ADX encoder's footer: pads the output to the sector-aligned total (when the handle's +108 loop count
// is set) and writes the 0x8001 end marker, the padding length and that many zero bytes through sub_5438C0 (the
// stream-joint write); returns the bytes written or 0 when the joint lacks room. [adxenc_WriteFooter]
void sub_544900(EEContext& ctx);
// 0x544A00: The ADX encoder's header writer: checks the output joint holds the header (+72 + 4 bytes), then writes the
// 0x8000 signature, the header offset (+72), encoding (+76), block size (+80), bits (+84), channels (+88), sample rate
// (+92), total samples (+96), high-pass frequency (+100), version 4, the flags, the history words (+712..+718), the
// loop records (+104 / +108, 20 bytes each: +112..+124), the optional AINF (0x41494E46, +726..+748) and CINF
// (0x43494E46, +750..+756) chunks, zero padding and the copyright string at 0x790A30; returns the header size or 0 on
// any short write. [adxenc_WriteHdr]
void sub_544A00(EEContext& ctx);
// 0x545158: The ADX encoder's init: the first call (count 0x790A28 == 0) runs sub_543430 and clears the 8 x 760-byte
// handle pool 0x790A38; returns the incremented count. [ADXENC_Init]
void sub_545158(EEContext& ctx);
// 0x5451B0: The ADX encoder's finish: the last call runs sub_543450 and clears the handle pool. [ADXENC_Finish]
void sub_5451B0(EEContext& ctx);
// 0x545208: The ADX encoder's create: takes the first free handle of the 8-entry pool (0 when none), stores the
// channel count ($a0), the channel joints ($a1[0..n]) and the output joint ($a2), and fills the defaults (44100 Hz,
// block 18, 4 bits, encoding 3, high-pass 500, no loops, pan -128) and two work buffers from sub_543BF0.
// [ADXENC_Create]
void sub_545208(EEContext& ctx);
// 0x5453D8: The ADX encoder's destroy: under the CRI lock, frees the two work buffers (+128 / +132) through sub_543C90
// and marks the handle free. [ADXENC_Destroy]
void sub_5453D8(EEContext& ctx);
// 0x545448: The ADX encoder's start: for each channel joint, takes 2 * (+104) bytes of line 0, clears them and puts
// them back as data (spins forever when the joint gives less), then resets the counters (+40 / +44 / +48), the state
// (+1 = 1) and the end flag (+3). [ADXENC_Start]
void sub_545448(EEContext& ctx);
// 0x545570: The ADX encoder's stop request: sets the end flag (+3) and returns 1.
void sub_545570(EEContext& ctx);
// 0x545580: Stores $a1 as the encoder's sample rate (+92).
void sub_545580(EEContext& ctx);
// 0x545590: Stores $a1 as the encoder's channel count (+88).
void sub_545590(EEContext& ctx);
// 0x545610: Stores $a1 as the encoder's total sample count (+96) and the encode limit (+60).
void sub_545610(EEContext& ctx);
// 0x545838: Configures an encoder: channels ($a1), sample rate ($a2), total samples ($a3), and the header offset 284
// (+72).
void sub_545838(EEContext& ctx);
// 0x545948: The encoder's header stage: takes each channel's first sample (the predictor history at +712 / +716),
// writes the header (sub_544A00), adds its size to the output count (+44), primes each channel's predictor (sub_543CD8
// with the high-pass and rate) and moves to state 2.
void sub_545948(EEContext& ctx);
// 0x545AB8: The encoder's data stage: encodes blocks (sub_544850) until none is ready, counting the output (+44); at
// the sample limit (+48 >= +60) sets the end flag; with the end flag set writes the footer and moves to state 3.
void sub_545AB8(EEContext& ctx);
// 0x545B50: Runs one encoder by its state: 1 = header stage, 2 = data stage; returns 2 otherwise.
void sub_545B50(EEContext& ctx);
// 0x545B90: The ADX encoder server: runs every in-use handle of the pool (8 entries, 760 bytes apart).
// [ADXENC_ExecServer]
void sub_545B90(EEContext& ctx);
// 0x545CC8: The ADXSTM finish: the last release (count 0x792BB8) clears the 3840-byte streamer pool 0x792BD8.
void sub_545CC8(EEContext& ctx);
// 0x546770: Bumps ADXSTM's read counter 0x792BD4 and returns it.
void sub_546770(EEContext& ctx);
// 0x546EC0: Stores sub_546410($a0) into *$a1 and returns 1.
void sub_546EC0(EEContext& ctx);
// 0x546EF0: The locked form of sub_546F48 (under the ADXSTM lock coshl_2 / sub_545C40): returns its result.
void sub_546EF0(EEContext& ctx);
// 0x546F48: A streamer's file position: *$a1 = +28, *$a2 = +24; returns 1.
void sub_546F48(EEContext& ctx);
// 0x546F98: Returns word +4 of the streamer.
void sub_546F98(EEContext& ctx);
// 0x5470E8: The locked form of sub_547120 (the file size under the ADXSTM lock).
void sub_5470E8(EEContext& ctx);
// 0x547120: Tail-calls cvFsGetFileSize.
void sub_547120(EEContext& ctx);
// 0x5471B8: Returns the signed byte +68 of the streamer.
void sub_5471B8(EEContext& ctx);
// 0x547248: The file size in 2 KiB sectors, rounded up, into *$a1 (cvFsGetFileSize); returns 1.
void sub_547248(EEContext& ctx);
// 0x5472E8: The file size in bytes into *$a1 (cvFsGetFileSize); returns 1.
void sub_5472E8(EEContext& ctx);
// 0x547418: Sets a streamer's request size: +20 = $a1 sectors, +16 = $a1 << 11 bytes.
void sub_547418(EEContext& ctx);
// 0x547468: Sets word +12 of the streamer to $a1, then tail-calls sub_5463A8 (ADXSTM_SetBufSize).
void sub_547468(EEContext& ctx);
// 0x5474B8: Stores $a0 in ADXSTM's word 0x792BD0.
void sub_5474B8(EEContext& ctx);
// 0x547500: Returns ADXSTM's word 0x792BD0.
void __errno_2(EEContext& ctx);
// 0x547548: Returns word +76 of the record at +8 of $a0.
void sub_547548(EEContext& ctx);
// 0x547590: Returns the signed byte +2 (the status) of a streamer.
void sub_547590(EEContext& ctx);
// 0x547598: The locked form of sub_5475C8.
void sub_547598(EEContext& ctx);
// 0x5475C8: Waits for a streamer: when it has a file (+80) and no read is pending (+8 == 0), sets +69 and runs
// ADXSTMF_ExecHndl whenever the try-lock cosl_2(0x792BCC) succeeds, until the handle clears +69.
void sub_5475C8(EEContext& ctx);
// 0x547650: An error callback adapter: passes $a1 (the message) to ADXERR_CallErrFunc1.
void sub_547650(EEContext& ctx);
// 0x547A58: Tail-calls sub_541D18.
void log10l_3(EEContext& ctx);
// 0x547AA8: Tail-calls sub_541D30.
void sub_547AA8(EEContext& ctx);
// 0x547F78: Creates an ADXT handle over a caller's work area with its first 1 KiB as the header buffer: sub_547C18(2,
// $a0 + 1024, $a1 - 1024), then (when created) sub_55F390(handle, $a0, 1024).
void sub_547F78(EEContext& ctx);
// 0x548250: Runs sub_548278 under the CRI lock (sub_539848 / sub_539850).
void sub_548250(EEContext& ctx);
// 0x548300: Tail-calls sub_548278.
void sub_548300(EEContext& ctx);
// 0x5485A8: Runs sub_5485D8($a0) under the CRI lock.
void sub_5485A8(EEContext& ctx);
// 0x548800: Sets ADXT's time mode ($a0 into 0x793B14) and, for modes 1 and 2, the vsync rate 0x793B60 (5994 / 5000:
// NTSC / PAL hundredths of Hz).
void sub_548800(EEContext& ctx);
// 0x548888: An ADXT handle's play time: for states 3 / 4 from sub_541AA8(+12) (the output), for state 5 from the
// decoder (sub_543178 samples, scaled by 16 / sub_543130, and sub_543100 the rate), else 0 / 1; the time offset (+136)
// is added to *$a1.
void sub_548888(EEContext& ctx);
// 0x548AD0: Bumps the counter 0x793B34 and returns it.
void sub_548AD0(EEContext& ctx);
// 0x548E68: The play time in hundredths: sceInsockBind_2 (the time getter) into a stack pair, then (samples / rate) *
// 100 as an integer.
void sub_548E68(EEContext& ctx);
// 0x549088: An ADXT accessor (error E02080822): null reports and gives -1; status < 2 gives 0; else sub_543380(the
// decoder).
void sub_549088(EEContext& ctx);
// 0x549110: An ADXT accessor (error E02080821): as sub_549088 with sub_543388.
void sub_549110(EEContext& ctx);
// 0x5492C8: Runs sub_549310($a0, $a1) under the CRI lock and returns its result.
void sub_5492C8(EEContext& ctx);
// 0x549568: Returns an ADXT handle's output volume (+64, s16); null reports E02080824 and gives 0.
void sub_549568(EEContext& ctx);
// 0x5495D0: Calls sub_543268 on the handle's decoder (+4).
void sub_5495D0(EEContext& ctx);
// 0x549638: Calls sub_5432C0 on the handle's decoder (+4).
void sub_549638(EEContext& ctx);
// 0x549690: Calls sub_543328 on the handle's decoder (+4).
void sub_549690(EEContext& ctx);
// 0x5496E0: Probes $a0's header with sub_53A138 into the scratch record 0x997048 (2048 bytes); returns 0x997048 when
// the header is valid, else 0.
void sub_5496E0(EEContext& ctx);
// 0x5497A8: Returns an ADXT handle's pan mode byte (+173).
void sub_5497A8(EEContext& ctx);
// 0x5498D0: Sets an ADXT handle's refill threshold from a time ($f12 seconds * $a2 Hz / 32 samples per block * 18
// bytes * $a1 channels, in sectors, capped at the buffer's sectors +60) into +62 and passes it to the streamer
// (sub_546FA0); null reports E02080838.
void sub_5498D0(EEContext& ctx);
// 0x5499B0: Resets the refill threshold (+62) to 85 % of the buffer's sectors and passes it to the streamer; null
// reports E03111501.
void sub_5499B0(EEContext& ctx);
// 0x549A70: Sets the refill threshold (+62) to $a1 sectors and passes it to the streamer; null reports E02080839.
void sub_549A70(EEContext& ctx);
// 0x549B08: The input buffer's data in sectors: the input joint's (+20) line-1 size >> 11, 0 without a joint; null
// reports E02080834 and gives -1.
void sub_549B08(EEContext& ctx);
// 0x549C58: The buffered play time in seconds (float): with the handle's state (adxt_GetStat) >= 2 and an input joint,
// (32 * (data / (18 * channels))) / rate; null reports E02080835 and gives -1.0.
void sub_549C58(EEContext& ctx);
// 0x549D78: Whether the input buffer holds at least the refill threshold (+62 sectors); null reports E02080836 and
// gives -1.
void sub_549D78(EEContext& ctx);
// 0x549E68: Whether the handle's status is 5 (play end); null reports E02080802 and gives -1.
void sub_549E68(EEContext& ctx);
// 0x549FE0: Tail-calls sub_549EC8.
void sub_549FE0(EEContext& ctx);
// 0x54A090: Clears the handle's error fields (+96, +100, +104, +106); null reports E02080844.
void sub_54A090(EEContext& ctx);
// 0x54A108: Returns the handle's word +76; null reports E02080829 and gives -1.
void sub_54A108(EEContext& ctx);
// 0x54A2B8: Returns the handle's input joint (+20); null reports E02080833 and gives 0.
void sub_54A2B8(EEContext& ctx);
// 0x54A328: Sets the handle's hold flag (+112) to $a1; null reports E02080830.
void sub_54A328(EEContext& ctx);
// 0x54A390: Returns the handle's started flag (+113); null reports E02080831 and gives -1.
void sub_54A390(EEContext& ctx);
// 0x54A5C8: Tail-calls sub_541C88.
void sub_54A5C8(EEContext& ctx);
// 0x54A618: Tail-calls sub_541CA0.
void sub_54A618(EEContext& ctx);
// 0x54A678: Returns the handle's streamer (+8).
void sub_54A678(EEContext& ctx);
// 0x54A6B0: Calls sub_5420A0 on the handle's decoder (+4).
void sub_54A6B0(EEContext& ctx);
// 0x54A710: Runs sub_54A758($a0, $a1) under the CRI lock and returns its result.
void sub_54A710(EEContext& ctx);
// 0x54A758: Pauses an ADXT handle's clock: when the pause byte (+114) is set, pauses the output (sub_541C60), runs the
// server, reads the play time with the time lock 0x793B14 forced to 0, and stores it as vsyncs (time / rate *
// 0x793B60, kept unsigned past 2^31) in +156 with the vsync count 0x787568 in +160.
void sub_54A758(EEContext& ctx);
// 0x54A878: Returns the handle's time offset (+136).
void sub_54A878(EEContext& ctx);
// 0x54A880: Stores $a1 as the handle's time offset under the CRI lock.
void sub_54A880(EEContext& ctx);
// 0x54A8C0: Stores $a1 as the handle's time offset (+136).
void sub_54A8C0(EEContext& ctx);
// 0x54A910: Calls sub_543038 on the handle's decoder (+4).
void sub_54A910(EEContext& ctx);
// 0x54A9D8: Returns the handle's trap flag byte (+152).
void sub_54A9D8(EEContext& ctx);
// 0x54AA30: Stores $a1 / $a2 in the decoder's (+4) words +80 / +84; second chunk at 0x543098.
void sub_54AA30(EEContext& ctx);
// 0x54AA80: sub_542F68 on the decoder (+4); null reports E02080818 and gives -1.
void sub_54AA80(EEContext& ctx);
// 0x54AAF0: sub_542F60 on the decoder (+4); null reports E04041901 and gives -1.
void sub_54AAF0(EEContext& ctx);
// 0x54AB78: sub_542F70 on the decoder (+4); null reports E04041902.
void sub_54AB78(EEContext& ctx);
// 0x54ABA8: Reads an ADX header's sample count: a buffer ($a0, $a1 bytes) starting with the big-endian 0x8000
// signature is parsed by sub_539AE0; on success *$a2 = the parsed s16 and 1, else 0.
void sub_54ABA8(EEContext& ctx);
// 0x54AC80: Runs sub_54ACD8 under the CRI lock and returns its result.
void sub_54AC80(EEContext& ctx);
// 0x54ACD8: Pre-fills an ADXT handle's input joint with silent ADX blocks: two passes over line 0 of the input joint
// (+20), each taking whole 18 * channels-byte frames, clearing them, stamping them through sub_563C28 and putting them
// back as data; returns the samples written (32 per frame).
void sub_54ACD8(EEContext& ctx);
// 0x54AF38: Runs sub_54AF78 under the CRI lock.
void sub_54AF38(EEContext& ctx);
// 0x54AF78: sub_542FA8 on the decoder (+4); null reports E02080860.
void sub_54AF78(EEContext& ctx);
// 0x54AFD8: Tail-calls sub_542FC0.
void sub_54AFD8(EEContext& ctx);
// 0x54B028: Returns the handle's output (+12).
void sub_54B028(EEContext& ctx);
// 0x54B070: Calls sub_543020 on the handle's decoder (+4).
void sub_54B070(EEContext& ctx);
// 0x54B388: Calls sub_54B3F0($a0, $a1, 0x40000000).
void sub_54B388(EEContext& ctx);
// 0x54C580: Restarts an ADXT handle from its input: under the CRI lock the output's transfer and play switches off
// (cosl_1 / coshl_1 on +12) and the decoder stopped (sub_542100); with a streamer (+8) it is stopped (sub_546638) and
// the input joint (+20) reset through its interface (+20); then, locked again, every output joint (+24.., +3 of them)
// reset, the streamer re-armed (sub_5463A8(stm, 0), sub_546498) and the common start sub_548318(handle, input joint).
void sub_54C580(EEContext& ctx);
// 0x54CB08: The streamer of an ADXT handle (+8, else the list streamer's +40 via +148) passed to sub_547558; 0 when
// none.
void sub_54CB08(EEContext& ctx);
// 0x54D88C: Returns $a1.
void sub_54D88C(EEContext& ctx);
// 0x54DAD8: MPEG audio: counts the call (0x796F54) and refills the bit reader (sub_54D898) when its fill (+12) is
// below $a1; returns whether it then holds $a1.
void sub_54DAD8(EEContext& ctx);
// 0x54DD08: MPEG audio: seeks the next frame sync -- byte-aligns the bit reader, then shifts in 4 bits at a time until
// the 12-bit 0xFFF sync (masked by 0x796F88) gives 1 or the 0x8001000C marker gives 2; -1 at the end of data.
void sub_54DD08(EEContext& ctx);
// 0x54E048: Hashes the stream key: on first use initialises the table (sub_54DE50), then sub_54DE90("CRI-MW", 6, $a0,
// $a1, $a2); returns 0.
void sub_54E048(EEContext& ctx);
// 0x54E0D8: The MPEG-audio decoder's init: the first call runs sub_551990 and clears the 16-entry handle table
// 0x797598; returns the incremented use count 0x797568.
void sub_54E0D8(EEContext& ctx);
// 0x54E130: The MPEG-audio decoder's finish: the last call clears the handle table and runs sub_551A88.
void sub_54E130(EEContext& ctx);
// 0x54E180: The MPEG-audio decoder's create: takes a free slot of the 16-entry table, clears the caller's work area
// ($a0, $a1 bytes), records its slot (+422), creates the synthesis work (sub_551AD8 at +2600, 4116 bytes; +432),
// aligns the sample buffer (+0) to 32 bytes and marks it ready (+420).
void sub_54E180(EEContext& ctx);
// 0x54E260: The MPEG-audio decoder's destroy: releases the synthesis work (+432), clears the 2600-byte handle and
// frees its table slot.
void sub_54E260(EEContext& ctx);
// 0x54E388: Calls sub_54E2C0 and stores $a1 as the decoder's bit reader (+428).
void sub_54E388(EEContext& ctx);
// 0x54E3C0: Reads the decoder's in-stream CRI header: copies bytes from the bit reader into 0x997108.. while
// sub_53E520 parses it (4 bytes, then the full length), then fills the decoder's info block (+484..+536) and its key
// (+536: cleared, copied from +2592, or hashed by sub_54E048).
void sub_54E3C0(EEContext& ctx);
// 0x54E648: Whether the decoder has produced all 12 granules (+424 == 12).
void sub_54E648(EEContext& ctx);
// 0x54E658: Decodes one MPEG-audio granule group: dequantises (sub_54F028), then synthesises 3 x 32 samples for the
// left channel and, in stereo, the right (sub_551BF0), timing each stage with sub_551978 into 0x7975D8..0x7975EC;
// returns 96, or 0 when all 12 granules are done.
void sub_54E658(EEContext& ctx);
// 0x54E838: Sets the decoder's key from a string: sub_54DE90(the string, its length, +2594, +2596, +2598) and clears
// +2592.
void sub_54E838(EEContext& ctx);
// 0x54E9A0: Parses an MPEG-audio frame header from the bit reader into $a1[0..11] (id, layer as 4 - code, CRC present,
// bitrate index, rate index, padding, private, mode, mode extension, copyright, original, emphasis); returns -1 unless
// the mode is 3 with extension 0 (mono), else 0.
void sub_54E9A0(EEContext& ctx);
// 0x54EAB8: The Layer II allocation table: *$a2 = the table 0x793F50, returns its sub-band count 0x793F48; second
// chunk at 0x54DDC8.
void sub_54EAB8(EEContext& ctx);
// 0x54EAD8: Fills the frame's decode parameters: channels (1 for mode 3, else 2), the sub-band limit and the
// allocation table (sub_54EAB8 for Layer II, else 32), the joint-stereo bound (0x797538) and the frame size
// (0x7973B0).
void sub_54EAD8(EEContext& ctx);
// 0x54EBC0: Reads the Layer II bit allocation: per sub-band below the bound one code per channel, joint sub-bands one
// code shared, the rest 0 (32 sub-bands, 128-byte channel stride).
void sub_54EBC0(EEContext& ctx);
// 0x54ED48: Reads the scale-factor selection and the scale factors of every allocated sub-band.
void sub_54ED48(EEContext& ctx);
// 0x54F028: Reads and dequantises the Layer II samples (grouped and ungrouped codes) of one granule group into the
// sample buffer.
void sub_54F028(EEContext& ctx);
// 0x54F730: Destroys an MPEG-audio stream's decoder under the ADXM lock: sub_548678, then when the handle (+4 -> +4)
// holds a decoder (+180), stops (sub_552080) and destroys it (sub_551F80), clears the slot and runs sub_551DA0.
void sub_54F730(EEContext& ctx);
// 0x54F7A0: Stores $a1 into word +44 of $a0; second chunk at 0x552618.
void atan2l_6(EEContext& ctx);
// 0x54F7B8: Sets word +8 of $a0 to 1 and returns 1; second chunk at 0x552620.
void cosl_6(EEContext& ctx);
// 0x54F7D0: An MPEG-audio stream's server step under the ADXM lock: restarts a stopped decoder, starts it in state 1,
// and in state 2 runs sub_5523B8 (+188) times, accounts the produced samples (+136 / +144) and the position (+148),
// and stops at the decoder's end (status 3).
void coshl_6(EEContext& ctx);
// 0x54F8C8: The synthesis matrixing, MMI form: each output is the dot product of the 32 s16 sub-band samples ($a0)
// with a 32-coefficient row ($a1, 64 bytes apart; phmadh over 4 quadwords, folded and >> 12), written to the 64-entry
// vector ($a2) forwards and mirrored (negated - 1 in the first half, as is in the second).
void sub_54F8C8(EEContext& ctx);
// 0x54FA78: The synthesis window: 32 outputs, each 16 taps of the vector buffer ($a0, alternating 96 / 32 sample
// strides) times the window ($a1), the second-pipeline mult1 interleaved; written to $a2.
void sub_54FA78(EEContext& ctx);
// 0x54FC68: The synthesis window, the shape of sub_54FA78 for another buffer phase.
void sub_54FC68(EEContext& ctx);
// 0x54FE58: The synthesis window, the shape of sub_54FA78 for another buffer phase.
void sub_54FE58(EEContext& ctx);

}  // namespace p3fes::game
