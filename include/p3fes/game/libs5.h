// Phase 5 slice libs5: the CRI Sofdec library band 0x580000-0x5AFFFF -- MWSFD's player layer, SFD's audio transfer,
// small transfer modules and stream-core helpers, SFX's handle pools, SUD's tag reader -- and the do-nothing functions
// of the kernel payload blobs at 0x77F568 / 0x77FBD8 / 0x7803A0. Register-ABI bodies started from p3fes_handgen (every
// statement, charge and check point is the generator's: game/include/p3fes/game/hg_cpu.h): arguments in $a0.., the
// result in $v0. Each declaration carries the function's role and, in brackets, a proposed name -- from the binary's
// own error / banner texts where the function or its module prints one ("mwPlyGetStat", "mwSfdStop", "SFX_Create" ...),
// our own otherwise (ADR-0009: proposals only, not imported). No CRI material was opened. The records below name the
// offsets the bodies use (libs5:: constants in the loads and stores; each equals the literal it replaces).
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace libs5 {
// MWSFD player (MWPLY handle): 684 bytes, 8 of them at 0x7B2FBC (MWSFD work 0x7B2F50 + 108)
namespace ply {
constexpr s32 kSize = 684;
constexpr s32 kUsed = 0;                  // 1 while the handle is in use (the handle check reads it)
constexpr s32 kStat = 4;                  // status: 0 stop, 1 preparing, 2 playing, 3 play end, 4 error
constexpr s32 kCprm = 8;                  // the creation parameters (48 bytes copied from mwPlyCreate's argument)
constexpr s32 kSfd = 60;                  // the SFD handle
constexpr s32 kAdxt = 64;                 // the ADXT player of the file input
constexpr s32 kLsc = 72;                  // the loop-play list (LSC) handle
constexpr s32 kSvrBusy = 92;              // server-busy mark (sub_5861B8)
constexpr s32 kInSvr = 96;                // inside its server call
constexpr s32 kInSfdSvr = 100;            // inside SFD's per-handle server
constexpr s32 kStepRan = 104;             // 1 when the last server call ran the status step
constexpr s32 kLinkFlg = 112;             // byte: link the streams when SFD is ready
constexpr s32 kTermReq = 113;             // byte: termination of SFD's input requested
constexpr s32 kPause = 114;               // byte: paused
constexpr s32 kFrmCnt0 = 124;             // frame counter
constexpr s32 kFrmCnt1 = 128;             // frame counter
constexpr s32 kUnk132 = 132;
constexpr s32 kSfx = 168;                 // the SFX handle
constexpr s32 kAddInfSj = 380;            // the AddInf SJ
constexpr s32 kAddInfBuf = 384;           // the AddInf SJ's buffer
constexpr s32 kAddInfBufSize = 388;       // its size
constexpr s32 kAddInfIdx = 400;           // AddInf record: -1 when empty
constexpr s32 kAddInf1 = 404;
constexpr s32 kAddInf2 = 408;
constexpr s32 kAddInf3 = 412;
constexpr s32 kFname = 420;               // the file name buffer
constexpr s32 kFnameCap = 424;            // its capacity
constexpr s32 kStartPend = 428;           // a file start is pending
constexpr s32 kFileArg0 = 432;            // file request arguments (MWSTM_ReqStart)
constexpr s32 kFileArg1 = 436;
constexpr s32 kFileArg2 = 440;
constexpr s32 kInputSj = 444;             // the input SJ
constexpr s32 kFileSj = 448;              // the file input's SJ
constexpr s32 kReadSize = 456;            // the read size
constexpr s32 kSlave = 640;               // the audio slave record (libs5::slave)
constexpr s32 kSlaveIdx = 672;            // cleared on stop
constexpr s32 kUnk680 = 680;
}  // namespace ply
// MWSFD audio slave (player +640), driven through the interface *0x7B4538
namespace slave {
constexpr s32 kSize = 32;
constexpr s32 kUsed = 0;                  // 1 = in use
constexpr s32 kSj = 12;                   // its SJ
constexpr s32 kIndex = 16;                // stream index (SFD stream 192 + index)
constexpr s32 kHandle = 20;               // the interface's handle
}  // namespace slave
// SFD handle (the stream core object; tail1.h sfd:: has the header-info and parameter parts); at least 14,004 bytes
namespace sfdh {
constexpr s32 kTimeUpd = 68;              // set when the time was updated
constexpr s32 kStat = 72;                 // status (tail1: valid word): 3 ready, 4 playing, 6 play end; negated after an error
constexpr s32 kUnk76 = 76;
constexpr s32 kUnk80 = 80;
constexpr s32 kInBytes0 = 2488;           // 64-bit byte totals of the audio input
constexpr s32 kInBytes1 = 2496;
constexpr s32 kSjBytes0 = 2512;
constexpr s32 kSjBytes1 = 2520;
constexpr s32 kPara = 2572;               // parameter table (4 x id)
constexpr s32 kTimeRec = 3376;            // the time record (time-source callbacks at +0, the time at +652 / +656)
constexpr s32 kTimeBase = 4128;           // the time base
constexpr s32 kStream = 4884;             // stream table, 116 bytes per stream
constexpr s32 kTrn = 7984;                // transfer slots, 68 bytes each (9)
constexpr s32 kTrn0Stream = 8004;         // slot 0's stream
constexpr s32 kTrn3Work = 8196;           // slot 3 (audio) work
constexpr s32 kTrn3InStream = 8204;       // slot 3's input stream
constexpr s32 kTrn3OutStream = 8208;      // slot 3's output stream
constexpr s32 kTrn6InEnd = 8392;          // slot 6
constexpr s32 kTrn6OutEnd = 8396;
constexpr s32 kTrn6Stream = 8408;
constexpr s32 kTrn7InEnd = 8460;          // slot 7
constexpr s32 kTrn7OutEnd = 8464;
constexpr s32 kTrn7Work = 8468;
constexpr s32 kTrn7Stream = 8476;
constexpr s32 kTrn8InEnd = 8528;          // slot 8
constexpr s32 kTrn8OutEnd = 8532;
constexpr s32 kTrn8Work = 8536;
constexpr s32 kTrn8Stream = 8544;
constexpr s32 kAudioWork = 13736;         // the audio transfer's work
constexpr s32 kAudioCfg = 13744;          // its ADXT configuration
constexpr s32 kTrn7WorkRec = 13916;       // slot 7's work (also the audio info record)
constexpr s32 kTrn8WorkRec = 13944;       // slot 8's work
constexpr s32 kHdrObj = 14000;            // the header object
}  // namespace sfdh
}  // namespace libs5

// [mwPlySfdStandby] MWSFD: puts the player's SFD handle (+60) into standby (sub_595988); on failure records -311 as
// the last error (sub_57FC60) and reports 'mwPlySfdStandby'. Returns SFD's result, or -311.
void sub_5800F0(EEContext& ctx);  // 0x5800F0
// [mwPlySfdStart] MWSFD: starts the player's SFD handle (sub_5972B0); on failure records -307 and reports
// 'mwPlySfdStart'. Returns SFD's result, or -307.
void sub_580130(EEContext& ctx);  // 0x580130
// [mw_sfd_start_ex] MWSFD: (re)starts a player's decode. With an SFD handle: resets it (sub_57D518, 'RESET failed'),
// resets the audio slave (sub_585050), runs the AddInf SJ's reset method, re-attaches it to SFD ('can't set
// AddInfSJ'), clears the AddInf record and the header ring; then clears the frame counters, stands SFD by, re-applies
// the pause byte, pauses and starts the audio slave, clears +132 / +680, sets the status to 1 (preparing) and the
// 'term requested' byte +113 to 0. Returns 1.
void sub_580270(EEContext& ctx);  // 0x580270
// [mwPlyClearFrmCnt] MWSFD: clears a player's two frame counters (+124, +128).
void sub_580368(EEContext& ctx);  // 0x580368
// [mwPlyStartFname] MWSFD: start playing a file: handle check, file name check ('fname is NULL'), the input SJ +444 =
// the file SJ +448, stop, start_ex, store the name (sub_580A28), then the empty start hook with (ply, 0, -1).
void sub_580378(EEContext& ctx);  // 0x580378
// [mwSfdStop] MWSFD: stops a player's decode. With an SFD handle: waits the decode server out (sub_586248), clears
// the status and the SFD handle while SFD stops (sub_597368; -308, 'can't stop SFD'), puts the handle back, stops the
// audio slave, clears +672, stops the ADXT file input (+64) and the loop-play list (+72).
void sub_580628(EEContext& ctx);  // 0x580628
// [mwPlyPause] MWSFD: pause on / off. Handle check; when the pause byte +114 or the request is set: if the server is
// locked (sub_57FA98) and +8 is 1, waits the server out when SFD's condition 6 is set (or cannot be read); pauses SFD
// (sub_5957D8; -310, 'can't pause (ON / OFF)'), pauses the audio slave, stores the request in +114.
void sub_580750(EEContext& ctx);  // 0x580750
// [mwPlySetReadSize] MWSFD: the ADXT input's read size from the player's +456 scaled by the double at 0x7C8B50
// (litodp / dpmul / dptoli), handed to sub_5816F0 with +456.
void sub_580900(EEContext& ctx);  // 0x580900
// [mwPlyTermSupplyAtEof] MWSFD: when the ADXT file input (+64) reports status 3 (end of file), terminates SFD's input
// (sub_597968).
void sub_580958(EEContext& ctx);  // 0x580958
// [mwPlySetFname] MWSFD: copies the file name into the buffer +420 (capacity +424): strcpy when it fits, else reports
// 'filename is longer.' and copies the capacity with strncpy (no terminator then).
void sub_5809B0(EEContext& ctx);  // 0x5809B0
// [mwsfdInitSprSwap] MWSFD: the scratchpad-swap settings: enabled (0x7B4528 = 1), no callback (0x7B452C), not swapped
// (0x7B4530), DMA rather than memcpy (0x7B4534 = 0). Returns 1.
void sub_580C80(EEContext& ctx);  // 0x580C80
// [mwsfdSprSwapIn] MWSFD: swaps the scratchpad in, once (0x7B4530 = 1), when enabled: waits DMA channels 8 / 9, saves
// the scratchpad's 16 KiB to 0x99EDC0, loads 0x9A2DC0 into it, waiting each channel. Returns 0x7B0000 when disabled.
void sub_580CB0(EEContext& ctx);  // 0x580CB0
// [mwsfdSprSwapOut] MWSFD: swaps the scratchpad back (0x7B4530 = 0): saves it to 0x9A2DC0 and reloads 0x99EDC0.
void sub_580D40(EEContext& ctx);  // 0x580D40
// [mwsfdSprSwapEnabled] MWSFD: the scratchpad-swap enable word 0x7B4528 (FLIRT misname).
void WTLS_get_table_0(EEContext& ctx);  // 0x580DF0
// [mwsfdCallSprCb] MWSFD: calls the user callback 0x7B452C, when set, with (a0, the swap enable word).
void sub_580E10(EEContext& ctx);  // 0x580E10
// [mwsfdSprWait] MWSFD: waits for DMA channels 8 (fromSPR) and 9 (toSPR) (my_malloc_0 is the channel wait).
void sub_580E78(EEContext& ctx);  // 0x580E78
// [mwsfdSprToMem] MWSFD: scratchpad to memory: the memcpy path (sub_580ED8) when 0x7B4534 is set, else DMA
// (sub_580F10).
void sub_580E98(EEContext& ctx);  // 0x580E98
// [mwsfdMemToSpr] MWSFD: memory to scratchpad: memcpy (sub_580FB8) or DMA (sub_580FE8).
void sub_580F78(EEContext& ctx);  // 0x580F78
// [mwPlyExecAdxSvr] MWSFD: thunk to sub_541008, the ADX server step (SVM lock, the ADX servers, unlock); the game's
// raster task calls it.
void sub_5810F0(EEContext& ctx);  // 0x5810F0
// [mwsfdSprIn] MWSFD: thunk to the scratchpad swap-in sub_580CB0.
void sub_581108(EEContext& ctx);  // 0x581108
// [mwsfdSprOut] MWSFD: thunk to the scratchpad swap-out sub_580D40.
void sub_581120(EEContext& ctx);  // 0x581120
// [mwsfdStartHook] MWSFD: an empty hook mwPlyStartFname calls with (ply, 0, -1) (FLIRT misname).
void __env_lock_11(EEContext& ctx);  // 0x581138
// [mwsfdSvrHook] MWSFD: an empty hook the per-player server step calls last.
void sub_581148(EEContext& ctx);  // 0x581148
// [mwPlyGetSfdHn] MWSFD: the player's SFD handle (+60); 0 and 'handle is invalid' for a bad handle.
void sub_5811D0(EEContext& ctx);  // 0x5811D0
// [mwPlySetSfdPara] MWSFD: SFD set-parameter (sub_599100) on the player's SFD handle (0 for a null player: every
// handle).
void sub_581690(EEContext& ctx);  // 0x581690
// [mwPlySetInputReadSize] MWSFD: hands a read size to the ADXT input (+64, sub_586428) and to the loop-play list
// (sub_5847D0).
void sub_5816F0(EEContext& ctx);  // 0x5816F0
// [mwPlyIsValidHn] MWSFD: the handle check: the player's used word (+0; 1 = in use), 0 for a null pointer.
void sub_581798(EEContext& ctx);  // 0x581798
// [mwPlyGetStat] MWSFD: player status. Bad handle: last error -12, 'mwPlyGetStat: handle is invalid', 0. Else the
// status (+4); while playing (2) it follows SFD's status: 1 (preparing) for 0..3 and 5, 2 (playing) for 4 and 6, 4
// (error) for a negative one.
void sub_581840(EEContext& ctx);  // 0x581840
// [mwsfdInitSfx] MWSFD: SFX init (sub_59F970) and the SFX hook record 0x7B4928 = {sub_5827C0, 0}; returns its
// address.
void sub_582798(EEContext& ctx);  // 0x582798
// [mwsfdGetSfxWorkSize] MWSFD: the SFX handle's work size, 6175 bytes.
void sub_5827F0(EEContext& ctx);  // 0x5827F0
// [mwsfdCreateSfx] MWSFD: thunk to SFX create (sub_59FAA8).
void sub_5827F8(EEContext& ctx);  // 0x5827F8
// [mwsfdDestroySfx] MWSFD: thunk to SFX destroy (sub_59FCC0).
void sub_582810(EEContext& ctx);  // 0x582810
// [mwPlyGetSfxHn] MWSFD: the player's SFX handle (+168).
void sub_582828(EEContext& ctx);  // 0x582828
// [mwPlySetSfxCompo] MWSFD: stores a2 in the player's SFX handle +4 (the composition mode).
void sub_583028(EEContext& ctx);  // 0x583028
// [mwPlyIsCprmMode2] MWSFD: true when the creation parameter's first word (player +8) is 2.
void sub_5833D8(EEContext& ctx);  // 0x5833D8
// [mwsfdNeedAddInfSj] MWSFD: true when a creation parameter block's +32 word is 0 or 257 (an AddInf SJ is wanted).
void sub_5833E8(EEContext& ctx);  // 0x5833E8
// [mwPlyCreateAddInfSj] MWSFD: creates the AddInf SJ when wanted (sub_562388 on the buffer +384 / +388); on failure
// reports 'mwPlyCreate: can't create AddInfSJ' and destroys the player. Returns the SJ or 0.
void sub_583410(EEContext& ctx);  // 0x583410
// [mwPlyDestroyAddInfSj] MWSFD: destroys the AddInf SJ (+380) through its method table (+12).
void sub_583470(EEContext& ctx);  // 0x583470
// [mwPlyAttachAddInfSj] MWSFD: attaches the AddInf SJ (+380) to SFD as stream 2 (sub_59C8E0) unless the creation mode
// is 2; -1 on failure, else 0.
void sub_5834A0(EEContext& ctx);  // 0x5834A0
// [mwPlyResetAddInf] MWSFD: resets the AddInf record (+400 = -1, +404 / +408 / +412 = 0).
void sub_583500(EEContext& ctx);  // 0x583500
// [mwPlyResetAddInfSj] MWSFD: resets the AddInf SJ (+380) through its method table (+20).
void sub_583520(EEContext& ctx);  // 0x583520
// [mwPlyScanAddInf] MWSFD: with an AddInf SJ, scans it for the CRITAGS block (sub_5835F0) and the SFXINF block
// (sub_5837A0).
void sub_5835A8(EEContext& ctx);  // 0x5835A8
// [mwPlyIsLscEnd] MWSFD: true when the loop-play list (sub_55D790) reports status 3.
void sub_5847A8(EEContext& ctx);  // 0x5847A8
// [mwPlySetLscReadSize] MWSFD: forwards a read size to the player's loop-play list (+72, sub_55DA48) when it has one.
void sub_5847D0(EEContext& ctx);  // 0x5847D0
// [mwsfdSlaveStart] MWSFD: starts the audio slave (+640) through the slave interface (*0x7B4538, method +20) with its
// handle (+20) and SJ (+12), when it is active.
void sub_584C80(EEContext& ctx);  // 0x584C80
// [mwsfdSlaveStop] MWSFD: stops the audio slave (interface method +24 on its handle) when it is active.
void sub_584CD8(EEContext& ctx);  // 0x584CD8
// [mwsfdSlavePause] MWSFD: pauses / resumes the audio slave (interface method +36: handle, flag) when it is active.
void sub_584E08(EEContext& ctx);  // 0x584E08
// [mwsfdSlaveReset] MWSFD: resets the player's audio slave: stops it, resets its SJ (method +20) and re-registers the
// SJ as SFD stream 192 + its index (sub_58C228).
void sub_585050(EEContext& ctx);  // 0x585050
// [mwsfdSlaveDestroy] MWSFD: destroys an audio slave: releases the SVM lock 6 (log10l_11), stops it, clears its used
// word, frees its handle (sub_584C38), destroys its SJ (method +12), clears the handle, then sub_584B18.
void sub_585100(EEContext& ctx);  // 0x585100
// [mwsfdGetSlaveIf] MWSFD: the audio slave interface 0x7B4538 (FLIRT misname).
void WTLS_get_table_1(EEContext& ctx);  // 0x5851B0
// [mwsfdSlaveIsActive] MWSFD: true when the slave interface is set, the slave record is in use (+0 = 1) and has a
// handle (+20).
void sub_5851D0(EEContext& ctx);  // 0x5851D0
// [mwsfdInitSvm] MWSFD: SVM init (sub_565550) and the four server ids 0x9A6EC0..0x9A6ECC cleared; $v0 keeps 0x9A0000.
void sub_585210(EEContext& ctx);  // 0x585210
// [mwsfdSetSvmCb2] MWSFD: registers SVM server class 2 (sub_564FE8) and keeps the id at 0x9A6EC4.
void sub_5852F8(EEContext& ctx);  // 0x5852F8
// [mwsfdSetSvmCb6] MWSFD: registers SVM server class 6 (sub_564DD0); id at 0x9A6EC8.
void sub_585360(EEContext& ctx);  // 0x585360
// [mwsfdSetSvmCb5] MWSFD: registers SVM server class 5 (sub_564DD0); id at 0x9A6ECC.
void sub_5853B8(EEContext& ctx);  // 0x5853B8
// [mwsfdSetSprHooks] MWSFD: installs the scratchpad swap hooks: SVM's (sub_565690(atan2l_11, 0)) and the record
// 0x99A0C8 = {cosl_11, 0}; returns 0x99A0C8.
void sub_585410(EEContext& ctx);  // 0x585410
// [mwsfdSprInHook] MWSFD: the scratchpad swap-in hook (thunk to sub_581108; FLIRT misname).
void atan2l_11(EEContext& ctx);  // 0x585468
// [mwsfdSprOutHook] MWSFD: the scratchpad swap-out hook (thunk to sub_581120; FLIRT misname).
void cosl_11(EEContext& ctx);  // 0x585480
// [mwsfdTestAndSet] MWSFD: thunk to SVM's test-and-set (sub_5655E8).
void sub_585578(EEContext& ctx);  // 0x585578
// [mwsfdUnlockSvm6] MWSFD: releases SVM lock 6 (sub_5651B0(6); FLIRT misname).
void log10l_11(EEContext& ctx);  // 0x585628
// [mwsfdWaitSvrHndl] MWSFD: waits while the player's 'in server' word (+96) is set: up to 10 rounds of mark busy, the
// ADX server step, unmark.
void sub_585698(EEContext& ctx);  // 0x585698
// [mwlSfdExecDecSvrPrep] MWSFD: the preparing step (status 1): a pending file start (+428) is retried through
// MWSTM_ReqStart; links the streams (mwPlyStartXX); when SFD reports 4 or 6 the player becomes 2 (playing). Returns 2
// or 4.
void sub_585738(EEContext& ctx);  // 0x585738
// [mwPlyStartXX] MWSFD: links the streams once SFD is ready (status 3): starts SFD, applies the pause byte, links
// (sub_589F70, 'mwPlyStartXX: can't link stream') and resumes the audio slave -- with a slave only when it is ready
// too.
void sub_5857B8(EEContext& ctx);  // 0x5857B8
// [MWSTM_ReqStart] MWSFD: starts the ADXT file input unless it is already playing: the input SJ's reset method, the
// file request (sub_586530), the start (sub_5865A8); -1 with status 4 and 'MWSTM_ReqStart: can't start' on failure,
// else the header probe (sub_57C730) and 1.
void sub_585960(EEContext& ctx);  // 0x585960
// [mwlSfdExecDecSvrPlaying] MWSFD: the playing step (status 2): a requested termination (+113) ends SFD's input once
// the loop list is idle ('mwlSfdExecDecSvrPlaying: can't term'); without loop play, end of file ends the input; SFD
// status 6 makes the player 3 (play end).
void sub_585A20(EEContext& ctx);  // 0x585A20
// [mwPlyExecSvrHndlStep] MWSFD: one player's server step: the status's step (1 preparing, 2 playing; jump table
// 0x7C9D00), the error check, the empty hook. Returns 0.
void sub_585AC8(EEContext& ctx);  // 0x585AC8
// [mwPlyCheckInputError] MWSFD: status 4 (error) when the ADXT input reports an error or the loop-play list ended.
void sub_585B40(EEContext& ctx);  // 0x585B40
// [mwsfdVsyncThunk] MWSFD: thunk to the vsync handler wrapper (r_lock_def_free_3).
void sub_585BA8(EEContext& ctx);  // 0x585BA8
// [mwsfdExecSvrMode1] MWSFD: runs the decode server when the server mode (work +16) is 1; else 0.
void sub_585BC0(EEContext& ctx);  // 0x585BC0
// [mwsfdExecSvrMode0] MWSFD: runs the decode server when the server mode is not 1.
void sub_585C08(EEContext& ctx);  // 0x585C08
// [mwsfdGetSvrMode] MWSFD: the server mode (work +16).
void sub_585C50(EEContext& ctx);  // 0x585C50
// [mwsfdVsyncHandler] MWSFD: the vsync handler wrapper: runs sub_585C90, returns 0 (FLIRT misname).
void r_lock_def_free_3(EEContext& ctx);  // 0x585C70
// [mwsfdVsync] MWSFD: the vsync work: counts 0x7B4540 / 0x7B4544; when MWSFD is initialised, takes the vsync lock
// (work +92), runs SFD's vsync (sub_595BA0) and frees the lock (FLIRT misname).
void r_lock_def_get_free_item_3(EEContext& ctx);  // 0x585C90
// [mwsfdCallPreHook] MWSFD: the decode server's pre hook (work +64 with +68).
void sub_585DA8(EEContext& ctx);  // 0x585DA8
// [mwsfdCallMidHook] MWSFD: the decode server's mid hook (work +72 with +76).
void sub_585DD8(EEContext& ctx);  // 0x585DD8
// [mwsfdCallPostHook] MWSFD: the decode server's post hook (work +80 with +84).
void sub_585E40(EEContext& ctx);  // 0x585E40
// [mwPlyExecSvr] MWSFD: the decode server: under the lock (work +88) runs the pre hook, every player's server (8 x
// 684 from 0x7B2FBC), frees the lock, runs SFD's server (sub_595BE8) and the mid hook; when SFD is idle and no player
// is in a server call, the post hook. Returns SFD's busy flag.
void sub_585E70(EEContext& ctx);  // 0x585E70
// [mwPlyExecSvrHndl] MWSFD: one player's server call: 'NULL handle' for 0; skipped for a free player, a re-entered
// one (+96) or while another server call runs (work +36); marks +96, remembers the player (0x7B4548), runs SFD's
// per-handle server (sub_595C60) with +100 marked, the status step when the status is set (+104), then SFD's post
// step (sub_595BC0).
void sub_585F38(EEContext& ctx);  // 0x585F38
// [mwsfdSetSvrLock] MWSFD: sets the decode-server lock word (work +88).
void sub_5860E8(EEContext& ctx);  // 0x5860E8
// [mwPlySetInSvr] MWSFD: sets the player's 'in server' word (+96).
void sub_586130(EEContext& ctx);  // 0x586130
// [mwPlyGetInSvr] MWSFD: the player's 'in server' word (+96) (FLIRT misname).
void tie__CQ24_STLt9basic_ios2ZcZQ24_STLt11char_traits1Zc(EEContext& ctx);  // 0x586138
// [mwPlySetInSfdSvr] MWSFD: sets the player's 'in SFD server' word (+100).
void sub_586140(EEContext& ctx);  // 0x586140
// [mwsfdSetSvrBusy] MWSFD: sets the server-busy word: the player's +92 (when given) and work +36.
void sub_5861B8(EEContext& ctx);  // 0x5861B8
// [mwsfdGetSvrBusy] MWSFD: the server-busy word (work +36).
void sub_586200(EEContext& ctx);  // 0x586200
// [mwsfdWaitSvr] MWSFD: waits for the decode server: scratchpad in, mark busy, release SVM lock 6, unmark, scratchpad
// out, then wait out the player's server call.
void sub_586248(EEContext& ctx);  // 0x586248
// [mwsfdInitHook] MWSFD: an init hook that returns 0.
void sub_5862F0(EEContext& ctx);  // 0x5862F0
// [sfdAdxtIsError] SFD audio: true when the ADXT player reports status 4 (error) (FLIRT misname).
void r_lock_def_get_free_item_4(EEContext& ctx);  // 0x5863F8
// [sfdAdxtSetReadSize] SFD audio: forwards to ADXT sub_546FA0 when the handle is not null.
void sub_586428(EEContext& ctx);  // 0x586428
// [sfdAdxtCreate] SFD audio: creates an ADXT player (sub_545FC8(a0, 0)).
void sub_5864A8(EEContext& ctx);  // 0x5864A8
// [sfdAdxtDestroy] SFD audio: thunk to ADXT destroy (sub_546058).
void sub_5864C0(EEContext& ctx);  // 0x5864C0
// [sfdAdxtStartFile] SFD audio: (re)starts an ADXT file: stop (sub_546270), the file request (sub_5460E0, five
// arguments), sub_546718(adxt, a4).
void sub_586530(EEContext& ctx);  // 0x586530
// [sfdAdxtStart] SFD audio: thunk to ADXT sub_546498 (the start; -1 on failure).
void sub_5865A8(EEContext& ctx);  // 0x5865A8
// [sfdAdxtStop] SFD audio: ADXT sub_5465A0, then stop (sub_546270) (FLIRT misname).
void R_LOCK_DEF_lock_free_4(EEContext& ctx);  // 0x5865C0
// [sfdAdxtGetStat] SFD audio: thunk to the ADXT status (sub_546368).
void sub_586610(EEContext& ctx);  // 0x586610
// [sfdAudioSetConfig] SFD audio: keeps an ADXT configuration at 0x9A6ED0: words 0, 1 and 3..5, and the two buffer
// sizes (words 2 and 6) rounded up to 32.
void sub_586800(EEContext& ctx);  // 0x586800
// [sfdAudioInit] SFD audio: the module init: ADXT init (sub_53EA90), sub_541CE8, and the configuration 0x9A6ED0
// cleared (7 words). Returns 0.
void sub_586858(EEContext& ctx);  // 0x586858
// [sfdAudioCheckFormat] SFD audio: when the time record's +500 equals +504, reads two ADXT figures (sub_548EB8 /
// sub_548F40) and, both positive, hands them to sub_58A108.
void sub_5868C0(EEContext& ctx);  // 0x5868C0
// [sfdAudioExecServer] SFD audio: the per-frame server (method 2): with parameter 6 set and the output not ended: the
// input step (sub_586A10), end of input, the ADXT status, the format record, the volume, the format check. Returns
// the input step's result.
void sub_586950(EEContext& ctx);  // 0x586950
// [sfdAudioNop] SFD audio: an empty step of the server.
void sub_586A08(EEContext& ctx);  // 0x586A08
// [sfdAudioFeed] SFD audio: the input step: takes the input stream's chunk (sub_5874D8), feeds the work's read
// callback (+60), advances the stream (sub_587520) and accounts the bytes (sub_587540).
void sub_586A10(EEContext& ctx);  // 0x586A10
// [sfdSjGetChunk0] SFD audio: an SJ's get-chunk on channel 0 (method +24).
void sub_586AA0(EEContext& ctx);  // 0x586AA0
// [sfdSjPutChunk] SFD audio: returns a chunk to an SJ: nothing taken -> method +28 back on channel 0; else split it
// (sub_563C28), put the used part on channel 1 (+32) and the rest back on 0 (+28).
void sub_586AD0(EEContext& ctx);  // 0x586AD0
// [sfdAudioReadCb] SFD audio: the ADXT read callback: copies up to min(size, chunk, 102400) bytes from the work's SJ
// to the destination (sub_575410), returns the rest, counts the bytes (work +72) and reports the count.
void sub_586B58(EEContext& ctx);  // 0x586B58
// [sfdAudioCheckEnd] SFD audio: when the output stream is open, the input stream ended and ADXT reports play end,
// marks the output stream ended.
void sub_587268(EEContext& ctx);  // 0x587268
// [sfdAudioIsAdxtEnd] SFD audio: true when the work's ADXT reports status 3.
void sub_587310(EEContext& ctx);  // 0x587310
// [sfdAudioCheckStat] SFD audio: the ADXT status check: raises 0xFF000308 / 0xFF000309 / 0xFF000307 for its error
// codes (parameter 26), resets the time base near play end, marks the output ended on status 5 or an error, and with
// the output ended and no data left stops ADXT.
void sub_587338(EEContext& ctx);  // 0x587338
// [sfdAudioGetInput] SFD audio: the input stream's chunk (sub_589018 on stream +8204) into two words.
void sub_5874D8(EEContext& ctx);  // 0x5874D8
// [sfdAudioAdvanceInput] SFD audio: advances the input stream (sub_5890F0).
void sub_587520(EEContext& ctx);  // 0x587520
// [sfdAudioAccount] SFD audio: adds the stream's and the SJ's byte counts to the 64-bit totals +2488 / +2496 / +2512
// / +2520.
void sub_587540(EEContext& ctx);  // 0x587540
// [sfdAudioIsInputEnd] SFD audio: the input stream's ended flag (stream +8204).
void sub_5875E8(EEContext& ctx);  // 0x5875E8
// [sfdAudioIsOutputEnd] SFD audio: the output stream's ended flag (stream +8208).
void sub_587600(EEContext& ctx);  // 0x587600
// [sfdAudioSetFormat] SFD audio: fills the audio format record once ADXT knows the format: channels, rate, bits,
// used, and the byte rate 9 x channels x rate / 16.
void sub_587638(EEContext& ctx);  // 0x587638
// [sfdAudioApplyVolume] SFD audio: applies the volume parameter to ADXT (sub_5497F8) when it changed (work +68).
void sub_587718(EEContext& ctx);  // 0x587718
// [sfdAudioCreate] SFD audio: create (method 3): with parameter 6 set: the work at +13736, the ADXT part
// (sub_5878D8), the ADXT player (sub_587A90; 0xFF000304), its SJ (sub_562388; 0xFF000305), the info record +13916
// with its five callbacks, the SJ hook-up (sub_5484E0), the time callback.
void sub_587780(EEContext& ctx);  // 0x587780
// [sfdAudioCreateWork] SFD audio: the ADXT part of create: needs a configuration (0xFF000306); copies it into the
// work, the read callback sub_586B58, the time base's settings from parameters 61..66 and 72.
void sub_5878D8(EEContext& ctx);  // 0x5878D8
// [sfdAudioCreateAdxt] SFD audio: the ADXT player: the preset one (0x7B4770) in mode 1, else a new one (sub_547BC0);
// sub_549DE8(h, 0).
void sub_587A90(EEContext& ctx);  // 0x587A90
// [sfdAudioGetPresetAdxt] SFD audio: the preset ADXT player 0x7B4770 (FLIRT misname).
void __errno_13(EEContext& ctx);  // 0x587B00
// [sfdAudioSetTimeCb] SFD audio: installs the time callback sub_587B50 as time source 2 and selects it (parameter 15
// = 2).
void sub_587B10(EEContext& ctx);  // 0x587B10
// [sfdAudioGetTime] SFD audio: the time callback: while playing (status 4) the ADXT time through the time base, kept
// monotonic in the work (+36 / +40).
void sub_587B50(EEContext& ctx);  // 0x587B50
// [sfdAudioReadTime] SFD audio: reads the ADXT status and time and the timer, and runs the time base (sub_59BEF0).
void sub_587C10(EEContext& ctx);  // 0x587C10
// [sfdAudioDestroy] SFD audio: destroy (method 4): keeps the configuration back at 0x9A6ED0, releases or destroys the
// ADXT player, destroys the SJ (+12), the timer hook (sub_5A19C0).
void sub_587CB8(EEContext& ctx);  // 0x587CB8
// [sfdAudioDestroyAdxt] SFD audio: ADXT destroy (sub_548048), returns 0 (FLIRT misname).
void r_lock_def_free_5(EEContext& ctx);  // 0x587D90
// [sfdAudioSetPresetAdxt] SFD audio: keeps an ADXT player as the preset 0x7B4770 (FLIRT misname).
void r_lock_def_get_free_item_5(EEContext& ctx);  // 0x587DB0
// [sfdAudioRequestStop] SFD audio: stop request (method 6): R_LOCK_DEF_lock_new_5(h, 0).
void sub_587DC8(EEContext& ctx);  // 0x587DC8
// [sfdAudioStopAdxt] SFD audio: ADXT stop (sub_548678) on the work's player.
void sub_587DE8(EEContext& ctx);  // 0x587DE8
// [sfdAudioGetFormatRec] SFD audio: the audio format record of the handle's header object (+14000, +3340) when no
// data is pending (work +64 <= 0); else 0.
void sub_588138(EEContext& ctx);  // 0x588138
// [sfdTrn7Init] SFD transfer 0x7C9DD0: init, returns 0.
void sub_5883B8(EEContext& ctx);  // 0x5883B8
// [sfdTrn7ExecServer] SFD transfer 0x7C9DD0 (slot 7): the server: with parameter 6, the input and output end checks.
void sub_5883C8(EEContext& ctx);  // 0x5883C8
// [sfdTrn7CheckInputEnd] SFD transfer slot 7: input end -- unless already ended, when its stream (+8476) ended sets
// +8460; $v0 476 (the slot's offset).
void sub_588438(EEContext& ctx);  // 0x588438
// [sfdTrn7CheckOutputEnd] SFD transfer slot 7: output end -- sets +8464 when the stream's output ended.
void sub_5884A8(EEContext& ctx);  // 0x5884A8
// [sfdTrn7Create] SFD transfer slot 7: create -- with parameter 6, its work is the handle's +13916.
void sub_588518(EEContext& ctx);  // 0x588518
// [sfdTrn7InitWork] SFD transfer slot 7: an empty work init.
void sub_588558(EEContext& ctx);  // 0x588558
// [sfdTrn7Destroy] SFD transfer 0x7C9DD0: destroy, returns 0.
void sub_588560(EEContext& ctx);  // 0x588560
// [sfdTrn7Start] SFD transfer 0x7C9DD0: start -- with parameter 6, method 6 of slot 3 (the audio transfer).
void sub_5885B0(EEContext& ctx);  // 0x5885B0
// [sfdTrn7Stop] SFD transfer 0x7C9DD0: stop -- method 7 of slot 3.
void sub_5885F8(EEContext& ctx);  // 0x5885F8
// [sfdTrn0Init] SFD transfer 0x7C9FB0: init, returns 0.
void sub_58C130(EEContext& ctx);  // 0x58C130
// [sfdTrn0ExecServer] SFD transfer 0x7C9FB0 (slot 0): the server marks its stream (+8004) ended. Returns 0.
void sub_58C140(EEContext& ctx);  // 0x58C140
// [sfdTrn0Create] SFD transfer 0x7C9FB0: create, returns 0.
void sub_58C168(EEContext& ctx);  // 0x58C168
// [sfdTrn0Destroy] SFD transfer 0x7C9FB0: destroy, returns 0.
void sub_58C170(EEContext& ctx);  // 0x58C170
// [sfdTrn8Init] SFD transfer 0x7CA4D8: init, returns 0.
void sub_59C9F0(EEContext& ctx);  // 0x59C9F0
// [sfdTrn8ExecServer] SFD transfer 0x7CA4D8 (slot 8): the server: output end, the (empty) step, input end; returns
// the step's 0.
void sub_59CA00(EEContext& ctx);  // 0x59CA00
// [sfdTrn8CheckOutputEnd] SFD transfer slot 8: output end -- sets +8532 when its stream (+8544) ended and the check
// allows; $v0 544.
void sub_59CA48(EEContext& ctx);  // 0x59CA48
// [sfdTrn8CheckInputEnd] SFD transfer slot 8: input end -- sets +8528.
void sub_59CAD0(EEContext& ctx);  // 0x59CAD0
// [sfdTrn8CanEndInput] SFD transfer slot 8: the input-end check, always 1.
void sub_59CB50(EEContext& ctx);  // 0x59CB50
// [sfdTrn8Step] SFD transfer slot 8: the empty server step, 0.
void sub_59CB58(EEContext& ctx);  // 0x59CB58
// [sfdTrn8Create] SFD transfer slot 8: create -- the work at +13944, its three entries registered (sub_59CB90).
void sub_59CB60(EEContext& ctx);  // 0x59CB60
// [sfdTrn8InitWork] SFD transfer slot 8: clears the work's count and registers three cleared 16-byte entries
// (sub_588F48).
void sub_59CB90(EEContext& ctx);  // 0x59CB90
// [sfdTrn8ClearEntry] SFD transfer slot 8: clears a 16-byte entry.
void sub_59CC08(EEContext& ctx);  // 0x59CC08
// [sfdSetEntry] SFD: stores four words in a 16-byte entry (a1, a2, a3, the stack word).
void sub_59CC30(EEContext& ctx);  // 0x59CC30
// [sfdTrn8Destroy] SFD transfer 0x7CA4D8: destroy, returns 0.
void sub_59CC48(EEContext& ctx);  // 0x59CC48
// [sfdTrn6Init] SFD transfer 0x7CA510: init, returns 0.
void sub_59CCF8(EEContext& ctx);  // 0x59CCF8
// [sfdTrn6ExecServer] SFD transfer 0x7CA510 (slot 6): the server: with parameter 5, output end, the (empty) step,
// input end.
void sub_59CD08(EEContext& ctx);  // 0x59CD08
// [sfdTrn6CheckOutputEnd] SFD transfer slot 6: output end -- sets +8396 when its stream (+8408) ended; $v0 408.
void sub_59CD60(EEContext& ctx);  // 0x59CD60
// [sfdTrn6CheckInputEnd] SFD transfer slot 6: input end -- sets +8392.
void sub_59CE28(EEContext& ctx);  // 0x59CE28
// [sfdTrn6CanEndInput] SFD transfer slot 6: the input-end check, always 1.
void sub_59CEA8(EEContext& ctx);  // 0x59CEA8
// [sfdTrn6Step] SFD transfer slot 6: the empty server step, 0.
void sub_59CEB0(EEContext& ctx);  // 0x59CEB0
// [sfdTrn6Create] SFD transfer 0x7CA510: create, returns 0.
void sub_59CEB8(EEContext& ctx);  // 0x59CEB8
// [sfdTrn6Destroy] SFD transfer 0x7CA510: destroy, returns 0.
void sub_59CEC0(EEContext& ctx);  // 0x59CEC0
// [sfdTrn6GetData] SFD transfer slot 6: get data -- while the handle's status is 3 or 4, from its stream
// (sub_589BE0); else 0 bytes.
void sub_59CF28(EEContext& ctx);  // 0x59CF28
// [sfdTrn6Forward] SFD transfer slot 6: unless its stream is flagged (+4884), forwards to method 12 of the stream's
// transfer; sets +68.
void sub_59CF70(EEContext& ctx);  // 0x59CF70
// [sfdGetPara] SFD: parameter id of a handle (+2572 + 4 x id).
void sub_599408(EEContext& ctx);  // 0x599408
// [sfdGetTrnWork] SFD: a transfer slot's work head: handle check (0xFF000117 for a bad handle), else sub_599730.
void sub_5996B0(EEContext& ctx);  // 0x5996B0
// [sfdGetTrnWorkHead] SFD: slot id's work (+7992 + 68 x id) -- its first word -- to *a2 (0 without a work).
void sub_599730(EEContext& ctx);  // 0x599730
// [sfdInitRec3] SFD: clears a 12-byte record and sets its third word.
void sub_5997F8(EEContext& ctx);  // 0x5997F8
// [sfdInitPicRec] SFD: initialises a 44-byte record: +0 = 0, +4..+35 cleared, +36 = a1, +40 = 1. Returns 1.
void sub_599A30(EEContext& ctx);  // 0x599A30
// [sfdClearRec32] SFD: clears a 32-byte record (seven words and two halfwords).
void sub_599A78(EEContext& ctx);  // 0x599A78
// [sfdExecVsync] SFD: vsync for every handle: counts 0x7B4720; each of the 8 handle slots (0x7B4774) that passes the
// check gets sub_599C08.
void sub_599B80(EEContext& ctx);  // 0x599B80
// [sfdExecVsyncHn] SFD: one handle's vsync: the time advance, and with parameter 71 = 1 the time update.
void sub_599C08(EEContext& ctx);  // 0x599C08
// [sfdAdvanceVsyncTime] SFD: the vsync time advance: +4056 += the step +4060 while playing; +4092 += the step when
// its timer runs.
void sub_599C58(EEContext& ctx);  // 0x599C58
// [sfdIsTimeRunning] SFD: true when the handle plays (status +72 = 4), is not paused (+80) and +2416 is clear.
void sub_599CC8(EEContext& ctx);  // 0x599CC8
// [sfdIsSubTimeRunning] SFD: true when the time record's +716 is set (not -1) and +76 is 4.
void sub_599D00(EEContext& ctx);  // 0x599D00
// [sfdSelectRefTime] SFD: the reference time: +680 with parameter 71 = 1, else +732; stored at +720.
void sub_599D28(EEContext& ctx);  // 0x599D28
// [sfdCheckLag] SFD: raises 0xFF000222 (sub_58BE40) and returns 1 when sub_599E48 reports a lag.
void sub_599E08(EEContext& ctx);  // 0x599E08
// [sfdIsLagging] SFD: with parameters 6 and 51 set, true when parameter 51 < the quotient of sub_599D70's two figures
// (divides; the original traps on a zero divisor).
void sub_599E48(EEContext& ctx);  // 0x599E48
// [sfdGetTimeThunk] SFD: thunk to sub_59A168.
void sub_59A150(EEContext& ctx);  // 0x59A150
// [sfdGetTime] SFD: the current time and unit (time record +652 / +656) to *a1 / *a2; returns 0.
void sub_59A168(EEContext& ctx);  // 0x59A168
// [sfdReadTime] SFD: reads the time through the time source selected by parameter 15 (callback table +3376; default
// sub_59A298) under the SVM lock.
void sub_59A200(EEContext& ctx);  // 0x59A200
// [sfdIsTimeValid] SFD: true when the status is 4, -4, 6 or -6; else time -1 / unit 1 and 0.
void sub_59A458(EEContext& ctx);  // 0x59A458
// [sfdThunk56F4B8] SFD: thunk to sub_56F4B8.
void sub_59A560(EEContext& ctx);  // 0x59A560
// [sfdUpdateTime] SFD: the time update: reads the time; when it changed, re-selects the reference and stores the new
// pair; sets +68. Returns 1.
void sub_59A7E0(EEContext& ctx);  // 0x59A7E0
// [sfdSetTimeSrc] SFD: installs a time-source callback: +3376 [index] = callback.
void sub_59A860(EEContext& ctx);  // 0x59A860
// [sfdDispatchCond] SFD: the condition dispatch: the table 0x7CA2E8 [2 x kind + sub-kind] with 0x7CA2C0 [kind]; an
// empty entry raises 0xFF000221 and gives 0 / 1.
void sub_59A870(EEContext& ctx);  // 0x59A870
// [sfdInitStat] SFD: initialises a statistics record: count 0, minimum INT64_MAX, sum and maximum 0.
void sub_59B490(EEContext& ctx);  // 0x59B490
// [sfdAddStat] SFD: adds a 64-bit sample to a statistics record (sum, minimum, maximum, count).
void sub_59B4B0(EEContext& ctx);  // 0x59B4B0
// [sfdCallAllTrn] SFD: calls method index of every transfer slot (9 x 68 bytes from +7984) that has a method table,
// until one returns non-zero.
void sub_59BB88(EEContext& ctx);  // 0x59BB88
// [sfdCallTrn] SFD: calls method index of transfer slot id (table +7996 + 68 x id) with the caller's arguments; 0
// without a table.
void sub_59BC20(EEContext& ctx);  // 0x59BC20
// [sfdIsTrnInputEnd] SFD: transfer slot id's input-ended flag (+7984 + 68 x id).
void sub_59BC88(EEContext& ctx);  // 0x59BC88
// [sfdIsTrnOutputEnd] SFD: transfer slot id's output-ended flag (+7988 + 68 x id).
void sub_59BCB8(EEContext& ctx);  // 0x59BCB8
// [sfdTbReset] SFD: the time base's reset: clears its 240-byte history (+24) and +20, counts resets (+412).
void sub_59BDD0(EEContext& ctx);  // 0x59BDD0
// [sfdTbSetMode] SFD: sets the time base's mode (+0).
void sub_59BE10(EEContext& ctx);  // 0x59BE10
// [sfdTbSetRatio1] SFD: sets the time base's first ratio pair (+312 / +320).
void sub_59BE18(EEContext& ctx);  // 0x59BE18
// [sfdTbSetRatio2] SFD: sets the second ratio pair (+328 / +336).
void sub_59BE30(EEContext& ctx);  // 0x59BE30
// [sfdTbSetRatio3] SFD: sets the third ratio pair (+344 / +352).
void sub_59BE48(EEContext& ctx);  // 0x59BE48
// [sfdTbSetRatio4] SFD: sets the fourth ratio pair (+360 / +368).
void sub_59BE60(EEContext& ctx);  // 0x59BE60
// [sfdTbSetLimit] SFD: sets the time base's limit (+16) when positive.
void sub_59BE78(EEContext& ctx);  // 0x59BE78
// [SFX_Init] SFX init (counted, 0x7B4918): the banner, the handle pool, SUD's init, the Z pool, sub_59E7A8.
void sub_59F970(EEContext& ctx);  // 0x59F970
// [SFX_GetVersionStr] SFX: the version banner (FLIRT misname).
void sceLibgcc32GetErxEntries_22(EEContext& ctx);  // 0x59F9E0
// [sfx_InitPool] SFX: clears the handle pool 0x7B4920 (1,224 bytes): 8 handles, sub_59FD50(1), sub_56DE28.
void sub_59F9F0(EEContext& ctx);  // 0x59F9F0
// [SFX_Create] SFX create: a free handle, the work size check ('sfx_InitHn: work size is short.'), the work layout,
// the Z handle ('SfxZHn: can't create.') and the alpha handle ('SfxAHn: can't create.'); counts the handle.
void sub_59FAA8(EEContext& ctx);  // 0x59FAA8
// [sfx_FindFreeHn] SFX: the first free handle of the pool (8 x 148 bytes from 0x7B4938), or 0.
void sub_59FBC0(EEContext& ctx);  // 0x59FBC0
// [sfx_InitHn] SFX: lays out a handle: cleared, in use, the work (+80) and size (+84), the work rounded up to 32
// (+56) and its +1024 / +2048 / +3072 areas, defaults.
void sub_59FC10(EEContext& ctx);  // 0x59FC10
// [sfx_IsWorkEnough] SFX: true when the work size is at least 6175 bytes.
void sub_59FCB0(EEContext& ctx);  // 0x59FCB0
// [SFX_Destroy] SFX destroy: frees the handle, its Z and alpha handles, uncounts it.
void sub_59FCC0(EEContext& ctx);  // 0x59FCC0
// [sfx_SetCnvMode] SFX: stores the setting 0x7B4934; $v0 keeps 0x7B0000.
void sub_59FD50(EEContext& ctx);  // 0x59FD50
// [sfx_InitSud] SFX: thunk to SUD's init (sub_5A1108).
void sub_5A0238(EEContext& ctx);  // 0x5A0238
// [sfxz_InitPool] SFX: clears the Z handle pool 0x7B4DE8 (620 bytes): 8 handles.
void sub_5A0268(EEContext& ctx);  // 0x5A0268
// [SFXZ_Create] SFX: a Z handle: the first free one, reset, counted, in use.
void sub_5A02C8(EEContext& ctx);  // 0x5A02C8
// [sfxz_FindFreeHn] SFX: the first free Z handle (8 x 76 bytes from 0x7B4DF4), or 0.
void sub_5A0320(EEContext& ctx);  // 0x5A0320
// [sfxz_ResetHn] SFX: resets a Z handle's fields (+4, +60..+72).
void sub_5A0370(EEContext& ctx);  // 0x5A0370
// [SFXZ_Destroy] SFX: frees a Z handle and uncounts it.
void sub_5A0388(EEContext& ctx);  // 0x5A0388
// [SUD_Init] SUD init (counted, 0x7B5058): keeps the banner's address at 0x9ACBF0.
void sub_5A1108(EEContext& ctx);  // 0x5A1108
// [sudIsTagD] SUD: true for a non-null tag record and a non-negative a1 whose byte +18 is 'D' (strncmp of one
// character with 0x7CABD8).
void sub_5A1340(EEContext& ctx);  // 0x5A1340
// [kpTlbReturn0] Kernel payload 0x77F568 (runs at 0x80075000, never at this address): returns 0.
void sub_77F598(EEContext& ctx);  // 0x77F598
// [kpTlbReturnM1] Kernel payload 0x77F568: returns -1.
void sub_77F5F8(EEContext& ctx);  // 0x77F5F8
// [kpTlbReturnArg] Kernel payload 0x77F568: returns its argument.
void sub_77F65C(EEContext& ctx);  // 0x77F65C
// [kpTlbReturnM1b] Kernel payload 0x77F568: returns -1.
void sub_77F67C(EEContext& ctx);  // 0x77F67C
// [kpTlbReturnArgB] Kernel payload 0x77F568: returns its argument.
void sub_77F6B4(EEContext& ctx);  // 0x77F6B4
// [kpTlbReturnArgC] Kernel payload 0x77F568: returns its argument.
void sub_77F704(EEContext& ctx);  // 0x77F704
// [kpExecPs2Return0] Kernel payload 0x77FBD8 (runs at 0x80074000): returns 0.
void sub_77FF10(EEContext& ctx);  // 0x77FF10
// [kpAlarmReturn0] Kernel payload 0x7803A0 (runs at 0x80076000): returns 0.
void sub_7803D0(EEContext& ctx);  // 0x7803D0
// [kpAlarmReturnArg1] Kernel payload 0x7803A0: returns its second argument.
void sub_7803EC(EEContext& ctx);  // 0x7803EC

}  // namespace p3fes::game
