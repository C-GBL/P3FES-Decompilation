// Phase 5 slice libs2 (game/src/cri/libs2_acss_*.cpp, tests/game/test_libs2.cpp): CRI ACSS, the sound layer the game's
// BGM manager (0x108740 / 0x109180 and their helpers) drives. It sits on top of the players cri2 made readable (ADXT)
// and AIXP, and gives the game sound objects with one or two players (two for cross-fades), volume fades with
// callbacks, AIX track volumes and a server-wide ducking object that lowers the music while a voice plays:
//   * part 1 (0x531998-0x532118): ACSS's SVM lock thunks, the error reporter, the fader ACSFDR (68 bytes: a volume
//     in dB x 10 driven per frame through a level 0..3238200, delay / fade / hold, start and end callbacks);
//   * part 2 (0x532118-0x532788): the back ends ACSSBADX (over an ADXT player) and ACSSBAIX (over an AIXP handle),
//     each a 16-entry method table (0x7C0520 / 0x7C0630) the sound calls through;
//   * part 3 (0x532788-0x5349F8): the sound ACSSND (208 bytes): init from a 40-byte configuration and a work area,
//     the four start requests, stop, pause, volume, fades and cross-fades, the per-frame update;
//   * part 4 (0x5349F8-0x535688): the server ACSSVR (176 bytes, its address at 0x793F44: 16 sound slots, the SVM
//     server entry 'adxcs_exec_svr') and the ducking object ACSVHL (96 bytes);
//   * part 5 (0x54D030-0x54D528): the public entry points -- thunks into parts 1-4 (the server pointer 0x793F44 for
//     the create / destroy / ducking ones).
// Every function is a p3fes_handgen body on the register ABI (arguments in $a0..$t3, the result in $v0) with its
// recompiled entry point fn_<name>_<addr8> as the shim; the bodies are the generator's statements plus comments and the
// named offsets below (each equal to the literal it replaces). Names are symbols/functions.json's (ADR-0009; FLIRT
// leftovers such as atan2l / setenv / valloc are not what these functions are); each declaration says the function's
// role with a proposed name in [brackets] -- our own, or, where the binary's own error text names the function
// ("E2003052903 ACSSND_SetOutVol : Not initialized." and the like), that name; the ACSND_* names of part 5 are ours.
// Worked from the binary only; no CRI SDK material was opened, fetched or quoted.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace libs2 {
// the fader (ACSFDR, 68 bytes; sub_531A28 creates)
namespace fdr {
constexpr u32 kSize = 68;
constexpr s32 kStat = 0;                  // s8: 0 idle, 1 waiting out the delay, 2 fading, 3 holding at the target
constexpr s32 kStep = 4;                  // level change per frame
constexpr s32 kTime = 8;                  // frames since the start
constexpr s32 kEndTime = 12;              // the frame the target was reached
constexpr s32 kDelay = 16;                // frames before the fade starts
constexpr s32 kHold = 20;                 // frames held at the target before the end callback
constexpr s32 kCurve = 24;                // u8: 0 level = 3238200 x 10^(vol / 200), 1 the logarithmic curve
constexpr s32 kVolume = 28;               // the current volume (dB x 10: 0 full, -960 silent)
constexpr s32 kLevel = 32;                // the current level (0..3238200)
constexpr s32 kTarget = 36;               // the target volume
constexpr s32 kPrevTarget = 40;           // the target before the last start (the fade's starting volume)
constexpr s32 kStartCb = 44;              // start callback (function, then two arguments)
constexpr s32 kStartArg1 = 48;
constexpr s32 kStartArg2 = 52;
constexpr s32 kEndCb = 56;                // end callback (function, then two arguments)
constexpr s32 kEndArg1 = 60;
constexpr s32 kEndArg2 = 64;
}  // namespace fdr
// the ADX back end (ACSSBADX, 12 bytes)
namespace bad {
constexpr u32 kSize = 12;
constexpr s32 kVtbl = 0;                  // the method table 0x7C0520 (16 entries)
constexpr s32 kHndl = 4;                  // the ADXT player
constexpr s32 kNch = 8;                   // channels
}  // namespace bad
// the AIX back end (ACSSBAIX, 16 bytes)
namespace bai {
constexpr u32 kSize = 16;
constexpr s32 kVtbl = 0;                  // the method table 0x7C0630 (16 entries)
constexpr s32 kHndl = 4;                  // the AIXP handle
constexpr s32 kNch = 8;                   // channels
constexpr s32 kNumTrack = 12;             // tracks
}  // namespace bai
// a sound's player record (12 bytes, two of them at sound +24)
namespace ply {
constexpr u32 kSize = 12;
constexpr s32 kBackend = 0;               // the back end
constexpr s32 kFade = 4;                  // s8: 0 none, 1 fading out, 2 fading in, 3 volume change
constexpr s32 kAction = 5;                // s8: on the fade end: 0 nothing, 1 start the request, 2 stop, 3 pause
constexpr s32 kFader = 8;                 // the player's fader
}  // namespace ply
// the sound object (ACSSND, 208 bytes; sub_532788 creates, sub_532818 initialises)
namespace snd {
constexpr u32 kSize = 208;
constexpr s32 kBackends = 0;              // [2] the back ends by player
constexpr s32 kCur = 8;                   // the current player's back end
constexpr s32 kPrev = 12;                 // the other player's back end
constexpr s32 kCurIdx = 16;               // the current player
constexpr s32 kPrevIdx = 20;              // the other player
constexpr s32 kPlayers = 24;              // [2] player records (12 bytes: ply)
constexpr s32 kReqType = 48;              // the stored start request: 0 name, 1 partition file, 2 memory, 3 memory index
constexpr s32 kReqName = 52;              // type 0: the name (the sound's buffer)
constexpr s32 kReqPtid = 56;              // type 1: partition
constexpr s32 kReqFlid = 60;              // type 1: file
constexpr s32 kReqMem = 64;               // type 2: address
constexpr s32 kReqMemSize = 68;           // type 2: size
constexpr s32 kReqIdx = 72;               // type 3: index
constexpr s32 kReqEntry = 76;             // type 3: entry
constexpr s32 kInit = 80;                 // 1 once initialised
constexpr s32 kIniting = 84;              // 1 during the init
constexpr s32 kField88 = 88;              // cleared by the reset only
constexpr s32 kCross = 92;                // 1 = two players (cross-fades)
constexpr s32 kPause = 96;                // the pause flag
constexpr s32 kPlaying = 100;             // 1 once a player was started
constexpr s32 kField104 = 104;            // cleared by the reset only
constexpr s32 kAhxWork = 108;             // the AHX work (12,288 bytes per player)
constexpr s32 kNameBuf = 112;             // the 256-byte name buffer
constexpr s32 kField116 = 116;            // cleared by the reset only
constexpr s32 kCprm = 120;                // the 40-byte configuration (cprm)
constexpr s32 kCprmMaxCh = 124;           // configuration: channels
constexpr s32 kCprmSfreq = 128;           // configuration: sample rate
constexpr s32 kCprmNumTrack = 132;        // configuration: AIX tracks
constexpr s32 kCprmNumStm = 136;          // configuration: +16
constexpr s32 kKind = 140;                // s8 (configuration +20): kind 1 is lowered while a kind-2 sound plays
constexpr s32 kCprmCross = 144;           // configuration: two players
constexpr s32 kCprmAix = 148;             // configuration: AIX back ends
constexpr s32 kCprmAhx = 152;             // configuration: AHX buffers
constexpr s32 kCprm36 = 156;              // configuration: the other buffer layout
constexpr s32 kNumPlayer = 160;           // players (1, 2 with cross-fades)
constexpr s32 kBusy = 164;                // s8: a start / stop / fade under way
constexpr s32 kFadeOutTime = 168;         // fade-out frames (30 at reset)
constexpr s32 kFadeInTime = 172;          // fade-in frames
constexpr s32 kVolChgTime = 176;          // volume-change frames
constexpr s32 kCrossOffset = 180;         // cross-fade offset: > 0 delays the fade-in, < 0 the fade-out
constexpr s32 kHoldTime = 184;            // hold frames (60 at reset)
constexpr s32 kOutVol = 188;              // the sound's volume (dB x 10)
constexpr s32 kTrackVol = 192;            // the AIX track volumes (an array in the work)
constexpr s32 kDuck = 196;                // the ducking offset added to every volume
constexpr s32 kDucked = 200;              // 1 while kDuck is set this frame
constexpr s32 kCbFunc = 204;              // the callback: (sound, event)
}  // namespace snd
// the sound server (ACSSVR, 176 bytes; its address at 0x793F44)
namespace svr {
constexpr u32 kSize = 176;
constexpr s32 kSnd = 0;                   // [16] sounds
constexpr s32 kVhl = 64;                  // the ducking object (in this work at +68)
constexpr s32 kVhlWork = 68;              // its 96 bytes
constexpr s32 kInitCnt = 164;             // init count
constexpr s32 kIniting = 168;             // 1 during the first init
constexpr s32 kSvmId = 172;               // an SVM server number released at the finish
}  // namespace svr
// the ducking object (ACSVHL, 96 bytes)
namespace vhl {
constexpr u32 kSize = 96;
constexpr s32 kServer = 0;                // the server
constexpr s32 kFader = 4;                 // its fader (in this work at +8)
constexpr s32 kFaderWork = 8;             // the fader's 68 bytes
constexpr s32 kEnable = 76;               // ducking on
constexpr s32 kStat = 80;                 // s8: 0 idle, 1 lowering, 2 low, 3 restoring
constexpr s32 kDownTime = 84;             // lowering frames
constexpr s32 kUpTime = 88;               // restoring frames
constexpr s32 kDepth = 92;                // how far (dB x 10, positive)
}  // namespace vhl
}  // namespace libs2

// ACSS's copy of the SVM resource lock (type 2): a tail call into SVM. [acss_LockRsc]
void atan2l(EEContext& ctx);  // 0x531998
// ACSS's copy of the SVM resource unlock (type 2). [acss_UnlockRsc]
void cosl(EEContext& ctx);  // 0x5319B0
// ACSS's copy of the SVM lock, type 3: the sound methods that touch both players take it. [acss_Lock]
void coshl(EEContext& ctx);  // 0x5319C8
// ACSS's copy of the SVM unlock, type 3. [acss_Unlock]
void expl(EEContext& ctx);  // 0x5319E0
// ACSS's copy of SVM's test-and-set (a guarded flag set to 1: returns 1 when it was not 1 before). [acss_TestAndSet]
void hypotf(EEContext& ctx);  // 0x5319F8
// Report an ACSS error: the text goes to the ADX error reporter 0x53AE08. [acss_CallErr]
void sub_531A10(EEContext& ctx);  // 0x531A10
// Fader create: in a caller's work of at least 68 bytes (else an error and 0), reset (named by its error text).
//   [ACSFDR_Create]
void sub_531A28(EEContext& ctx);  // 0x531A28
// Fader destroy: the reset, when the fader exists. [ACSFDR_Destroy]
void sub_531A90(EEContext& ctx);  // 0x531A90
// Fader state (+0, s8): 0 idle, 1 waiting out the delay, 2 fading, 3 holding at the target. [ACSFDR_GetStat]
void sub_531AB8(EEContext& ctx);  // 0x531AB8
// Fader frame counter (+8). [ACSFDR_GetTime]
void sub_531AC0(EEContext& ctx);  // 0x531AC0
// Fader volume (+28, dB x 10: 0 full, -960 silent). [ACSFDR_GetVolume]
void sub_531AC8(EEContext& ctx);  // 0x531AC8
// Fader set volume: +28 = the volume, +32 = its level (sub_531F90). [ACSFDR_SetVolume]
void sub_531AD0(EEContext& ctx);  // 0x531AD0
// Fader start (fader, target volume, frames, delay, hold): the old target kept as the previous one, the per-frame
//   level step from the current volume to the target in the given frames (sub_531DD8), delay and hold frames; frames
//   > 0: state 1 (the delay counts first, then the fade); frames <= 0: the volume jumps to the target and state 2
//   (the next update finishes). [ACSFDR_Start]
void sub_531B00(EEContext& ctx);  // 0x531B00
// Fader reverse: swap target and previous target, negate the step; a holding fader fades again (state 2).
//   [ACSFDR_Reverse]
void sub_531BC0(EEContext& ctx);  // 0x531BC0
// Fader per-frame update: count the frame; after the delay call the start callback; step the level (clamped to
//   0..3238200), convert it back to a volume, stop at the target (state 3) and after the hold frames call the end
//   callback and go idle. [ACSFDR_ExecServer]
void sub_531C00(EEContext& ctx);  // 0x531C00
// Fader curve (+24, u8): 0 = level 3238200 x 10^(dB / 200), 1 = the logarithmic alternative. [ACSFDR_SetCurve]
void sub_531D40(EEContext& ctx);  // 0x531D40
// Fader start callback {function, two arguments} at +44. [ACSFDR_SetStartCb]
void sub_531D48(EEContext& ctx);  // 0x531D48
// Fader end callback {function, two arguments} at +56. [ACSFDR_SetEndCb]
void sub_531D58(EEContext& ctx);  // 0x531D58
// Fader reset: idle, every count 0, volume / target / previous target -960, both callbacks cleared. [acsfdr_Reset]
void sub_531D68(EEContext& ctx);  // 0x531D68
// The per-frame level step from one volume (the current one) to another over n frames ((level(to) - level(from)) / n;
//   n <= 0 gives the whole range 3238200 at once). [acsfdr_CalcStep]
void sub_531DD8(EEContext& ctx);  // 0x531DD8
// Level -> volume (dB x 10): 0 -> -960, 3238200 -> 0, else 200 log10(level / 3238200) (curve 0) or the inverse of
//   curve 1, clamped to -960..0. [acsfdr_LevelToVol]
void sub_531E60(EEContext& ctx);  // 0x531E60
// Volume (dB x 10) -> level: 0 -> 3238200, -960 -> 0, else 3238200 x 10^(vol / 200) (curve 0) or 3238200 log10(-vol)
//   / log10(960) (curve 1), clamped to 0..3238200. [acsfdr_VolToLevel]
void sub_531F90(EEContext& ctx);  // 0x531F90
// Call the fader's start callback (+44) with its two arguments; 0 when there is none, else 1. [acsfdr_CallStartCb]
void sub_5320B8(EEContext& ctx);  // 0x5320B8
// Call the fader's end callback (+56) with its two arguments; 0 when there is none, else 1. [acsfdr_CallEndCb]
void sub_5320E8(EEContext& ctx);  // 0x5320E8
// ADX back end create: in a caller's work of at least 12 bytes (else an error and 0), reset (named by its error
//   text). [ACSSBADX_Create]
void sub_532118(EEContext& ctx);  // 0x532118
// ADX back end destroy: the reset, when it exists. [ACSSBADX_Destroy]
void sub_532180(EEContext& ctx);  // 0x532180
// ADX back end method 0, create the player: ADXT_Create (or the 0x547F30 variant when the configuration asks for it)
//   in the work after the 12-byte back end; keeps the channel count; an error and 0 on failure (named by its error
//   text). [ACSSBADX_CreateHndl]
void sub_5321A8(EEContext& ctx);  // 0x5321A8
// ADX back end method 1: destroy the ADXT player. [ACSSBADX_DestroyHndl]
void sub_532230(EEContext& ctx);  // 0x532230
// ADX back end method 2: start a named file (ADXT_StartFname). [ACSSBADX_StartFname]
void sub_532268(EEContext& ctx);  // 0x532268
// ADX back end method 3: start a partition file (ADXT_StartAfs). [ACSSBADX_StartAfs]
void sub_532280(EEContext& ctx);  // 0x532280
// ADX back end method 4: start from memory (0x54B3A0). [ACSSBADX_StartMem]
void sub_532298(EEContext& ctx);  // 0x532298
// ADX back end method 5: start a memory index entry (ADXT_StartMemIdx). [ACSSBADX_StartMemIdx]
void sub_5322B0(EEContext& ctx);  // 0x5322B0
// ADX back end method 6: stop (ADXT_Stop). [ACSSBADX_Stop]
void sub_5322C8(EEContext& ctx);  // 0x5322C8
// ADX back end method 7: pause / resume (ADXT_Pause). [ACSSBADX_Pause]
void sub_5322E0(EEContext& ctx);  // 0x5322E0
// ADX back end method 8: the pause state (ADXT_GetStatPause). [ACSSBADX_GetStatPause]
void sub_5322F8(EEContext& ctx);  // 0x5322F8
// ADX back end method 9: the status, ADXT's 0..6 mapped through the table 0x7C0610 (0 stop, 1 preparing = opening /
//   buffering, 2 playing = playing / decode end, 3 play end, 4 error; above 6 also 4). [ACSSBADX_GetStat]
void sub_532310(EEContext& ctx);  // 0x532310
// ADX back end method 10: set the volume (clamped below at -960). [ACSSBADX_SetOutVol]
void sub_532380(EEContext& ctx);  // 0x532380
// ADX back end method 11: the volume (0x549530). [ACSSBADX_GetOutVol]
void sub_5323A8(EEContext& ctx);  // 0x5323A8
// ADX back end method 12: set a track's volume -- track 0 only. [ACSSBADX_SetTrackVol]
void sub_5323C0(EEContext& ctx);  // 0x5323C0
// ADX back end method 13: a track's volume -- track 0 only, else 0. [ACSSBADX_GetTrackVol]
void sub_5323F0(EEContext& ctx);  // 0x5323F0
// ADX back end method 14: set the loop flag (ADXT_SetLpFlg). [ACSSBADX_SetLpFlg]
void sub_532420(EEContext& ctx);  // 0x532420
// ADX back end method 15: the ADXT handle (+4). [ACSSBADX_GetHndl]
void sub_532438(EEContext& ctx);  // 0x532438
// ADX back end reset: the method table 0x7C0520, no player, no channels. [acssbadx_Reset]
void sub_532440(EEContext& ctx);  // 0x532440
// AIX back end create: in a caller's work of at least 16 bytes (else an error and 0), reset (named by its error
//   text). [ACSSBAIX_Create]
void sub_532458(EEContext& ctx);  // 0x532458
// AIX back end destroy: the reset, when it exists. [ACSSBAIX_Destroy]
void sub_5324C0(EEContext& ctx);  // 0x5324C0
// AIX back end method 0, create the player: an AIXP handle (0x5528B0 or 0x552830 by the configuration) in the work
//   after the 16-byte back end; keeps channels and tracks; an error and 0 on failure. [ACSSBAIX_CreateHndl]
void sub_5324E8(EEContext& ctx);  // 0x5324E8
// AIX back end method 1: destroy the AIXP handle. [ACSSBAIX_DestroyHndl]
void sub_532580(EEContext& ctx);  // 0x532580
// AIX back end method 2: start a named file (0x552EA8). [ACSSBAIX_StartFname]
void sub_5325B8(EEContext& ctx);  // 0x5325B8
// AIX back end method 3: start a partition file (0x552EC8). [ACSSBAIX_StartAfs]
void sub_5325D8(EEContext& ctx);  // 0x5325D8
// AIX back end method 4: start from memory (0x553028). [ACSSBAIX_StartMem]
void sub_5325F0(EEContext& ctx);  // 0x5325F0
// AIX back end method 5: memory index starts are not supported (an error; named by its error text).
//   [ACSSBAIX_StartMemIdx]
void sub_532608(EEContext& ctx);  // 0x532608
// AIX back end method 6: stop (0x5530D0). [ACSSBAIX_Stop]
void sub_532628(EEContext& ctx);  // 0x532628
// AIX back end method 7: pause / resume (0x553590). [ACSSBAIX_Pause]
void sub_532640(EEContext& ctx);  // 0x532640
// AIX back end method 8: the pause state (0x553658, whose error text names it AIXP_GetStatPause).
//   [ACSSBAIX_GetStatPause]
void sub_532658(EEContext& ctx);  // 0x532658
// AIX back end method 9: the status (0x553188, the AIXP handle's +1). [ACSSBAIX_GetStat]
void sub_532670(EEContext& ctx);  // 0x532670
// AIX back end method 10: set the volume of every track (method 12 per track, +12 tracks). [ACSSBAIX_SetOutVol]
void sub_532688(EEContext& ctx);  // 0x532688
// AIX back end method 11: the volume, read from track 0's ADXT player. [ACSSBAIX_GetOutVol]
void sub_5326F0(EEContext& ctx);  // 0x5326F0
// AIX back end method 12: set one track's volume (clamped below at -960; 0x5540E8). [ACSSBAIX_SetTrackVol]
void sub_532718(EEContext& ctx);  // 0x532718
// AIX back end method 13: a track's volume -- always 0. [ACSSBAIX_GetTrackVol]
void sub_532740(EEContext& ctx);  // 0x532740
// AIX back end method 14: set the loop flag (0x5533D8, the AIXP handle's +432). [ACSSBAIX_SetLpFlg]
void sub_532748(EEContext& ctx);  // 0x532748
// AIX back end method 15: the AIXP handle (+4). [ACSSBAIX_GetHndl]
void sub_532760(EEContext& ctx);  // 0x532760
// AIX back end reset: the method table 0x7C0630, no handle, no channels, no tracks. [acssbaix_Reset]
void sub_532768(EEContext& ctx);  // 0x532768
// Sound create: in a caller's work of at least 208 bytes (else an error and 0), reset (named by its error text).
//   [ACSSND_Create]
void sub_532788(EEContext& ctx);  // 0x532788
// Sound destroy: the reset, when it exists. [ACSSND_Destroy]
void sub_5327F0(EEContext& ctx);  // 0x5327F0
// Sound init from a 40-byte configuration and a work area (named by its error text): one or two players (two for
//   cross-fades), each a back end (AIX or ADX) whose player gets the input / PCM buffers the configuration asks for,
//   and a fader; then the AHX buffers, the 256-byte name buffer and the AIX track volumes; 'too small' when the work
//   runs out (everything made so far is finished again). [ACSSND_Init]
void sub_532818(EEContext& ctx);  // 0x532818
// Sound finish: destroy every player's fader, back-end player and back end. [ACSSND_Finish]
void sub_532D30(EEContext& ctx);  // 0x532D30
// Sound initialised flag (+80). [ACSSND_IsInit]
void sub_532E08(EEContext& ctx);  // 0x532E08
// Start a named file (named by its error text): the name copied into the sound's buffer (256), request type 0, then
//   the start. [ACSSND_StartFname]
void sub_532E10(EEContext& ctx);  // 0x532E10
// Start a partition file (request type 1: partition, file; named by its error text). [ACSSND_StartAfs]
void sub_532E70(EEContext& ctx);  // 0x532E70
// Start from memory (request type 2: address, size; named by its error text). [ACSSND_StartMem]
void sub_532EC0(EEContext& ctx);  // 0x532EC0
// Start a memory index entry (request type 3: index, entry; named by its error text). [ACSSND_StartMemIdx]
void sub_532F10(EEContext& ctx);  // 0x532F10
// Stop: fade the current player out (the fade-out frames +168, then stop); when paused stop it at once and silence
//   its fader, and the other player's too in cross-fade mode. [ACSSND_Stop]
void sub_532F60(EEContext& ctx);  // 0x532F60
// Pause / resume every player; the flag kept at +96 (named by its error text). [ACSSND_Pause]
void sub_5330A8(EEContext& ctx);  // 0x5330A8
// The current player's pause state (4 when not initialised; named by its error text). [ACSSND_GetStatPause]
void sub_533160(EEContext& ctx);  // 0x533160
// The current player's status (method 9; 4 when not initialised; named by its error text). [ACSSND_GetStat]
void sub_5331A8(EEContext& ctx);  // 0x5331A8
// The sound's creation parameters (the configuration at +120; 0 when not initialised; named by its error text).
//   [ACSSND_GetCprm]
void sub_5331F0(EEContext& ctx);  // 0x5331F0
// The sound's kind (+140, s8: kind 1 is lowered while a kind-2 sound plays). [ACSSND_GetKind]
void sub_533230(EEContext& ctx);  // 0x533230
// Set the volume (named by its error text): kept at +188; unless the current player is fading in, fade it to the new
//   volume over +176 frames (hold +184). [ACSSND_SetOutVol]
void sub_533238(EEContext& ctx);  // 0x533238
// Set an AIX track's volume (named by its error text): kept in the track array +192 and sent to every player with the
//   sound's volume added. [ACSSND_SetTrackVol]
void sub_533340(EEContext& ctx);  // 0x533340
// The sound's volume (+188). (A FLIRT name.) [ACSSND_GetOutVol]
void _ZNKSt9basic_iosIcSt11char_traitsIcEE10exceptionsEv(EEContext& ctx);  // 0x533450
// Method 14 (loop flag) on every player (named by its error text). [ACSSND_SetLpFlg]
void sub_5334A8(EEContext& ctx);  // 0x5334A8
// Fade-out frames (+168). [ACSSND_GetFadeOutTime]
void sub_533570(EEContext& ctx);  // 0x533570
// Fade-in frames (+172). [ACSSND_GetFadeInTime]
void sub_533578(EEContext& ctx);  // 0x533578
// Volume-change frames (+176). [ACSSND_GetVolChgTime]
void sub_533580(EEContext& ctx);  // 0x533580
// Cross-fade offset (+180). (A FLIRT name.) [ACSSND_GetCrossOffset]
void _ZNKSt9basic_iosIcSt11char_traitsIcEE3tieEv_0(EEContext& ctx);  // 0x533590
// Hold frames (+184). [ACSSND_GetHoldTime]
void sub_5335A0(EEContext& ctx);  // 0x5335A0
// Attach AHX to every player's ADXT (the AHX work at +108, 12,288 bytes each; named by its error text).
//   [ACSSND_AttachAhx]
void sub_5335B0(EEContext& ctx);  // 0x5335B0
// Detach AHX from every player's ADXT (named by its error text). [ACSSND_DetachAhx]
void sub_5336C0(EEContext& ctx);  // 0x5336C0
// The current player's ADXT handle (0 for AIX; named by its error text). [ACSSND_GetActiveAdxt]
void sub_5337A8(EEContext& ctx);  // 0x5337A8
// The next player's ADXT handle (0 for AIX; named by its error text). [ACSSND_GetNextAdxt]
void sub_533808(EEContext& ctx);  // 0x533808
// Player n's ADXT handle (0 for AIX or n out of range; named by its error text). [ACSSND_GetAdxt]
void sub_533880(EEContext& ctx);  // 0x533880
// The number of ADXT players (0 for AIX; named by its error text). [ACSSND_GetNumAdxt]
void sub_533900(EEContext& ctx);  // 0x533900
// The current player's AIXP handle (0 for ADX; named by its error text). [ACSSND_GetActiveAixp]
void sub_533950(EEContext& ctx);  // 0x533950
// The next player's AIXP handle (0 for ADX; named by its error text). [ACSSND_GetNextAixp]
void sub_5339A8(EEContext& ctx);  // 0x5339A8
// Player n's AIXP handle (0 for ADX or n out of range; named by its error text). [ACSSND_GetAixp]
void sub_533A18(EEContext& ctx);  // 0x533A18
// The number of AIXP players (0 for ADX; named by its error text). [ACSSND_GetNumAixp]
void sub_533A88(EEContext& ctx);  // 0x533A88
// Cancel the running fade (named by its error text): fade-in <-> fade-out with the callbacks swapped and the fader
//   reversed; in cross-fade mode the other player is switched back (and reversed too while it still fades).
//   [ACSSND_CancelFading]
void sub_533AC8(EEContext& ctx);  // 0x533AC8
// The busy flag (+164, s8: set while a start / stop / fade is under way). [ACSSND_IsBusy]
void sub_533CA0(EEContext& ctx);  // 0x533CA0
// Add a ducking offset to the sound (+196) and mark it ducked (+200). [acssnd_AddDuck]
void sub_533CA8(EEContext& ctx);  // 0x533CA8
// Clear the ducking offset and mark. [acssnd_ClearDuck]
void sub_533CC0(EEContext& ctx);  // 0x533CC0
// Per-frame sound update: ducked -> re-send every player's volume; else step every fading player's fader and re-send
//   its volume, then the fade bookkeeping; a paused sound whose stop completed is released. [ACSSND_ExecServer]
void sub_533CD0(EEContext& ctx);  // 0x533CD0
// Set every player's fader curve. [ACSSND_SetFadeCurve]
void sub_533E98(EEContext& ctx);  // 0x533E98
// Sound reset: every field cleared; fade-out 30 frames, hold 60. [acssnd_Reset]
void sub_533F10(EEContext& ctx);  // 0x533F10
// The common start (named by its error text): busy; in cross-fade mode switch to the other player, fade the old one
//   out and the new one in (the cross offset +180 delaying one of them); else stop a playing player and fade in; then
//   send the volume and the stored start request (sub_534308). [ACSSND_Start]
void sub_534010(EEContext& ctx);  // 0x534010
// Send the stored start request to the current player (methods 2..5 by the request type; 3 for another type).
//   [acssnd_StartPlayer]
void sub_534308(EEContext& ctx);  // 0x534308
// Begin a fade-in on a player record: from silence to the sound's volume over the fade-in frames (+172) after the
//   given delay, the fader callbacks set, player state 2 with the given next action. [acssnd_FadeIn]
void sub_5343D8(EEContext& ctx);  // 0x5343D8
// Begin a fade-out on a player record: to silence over the fade-out frames (+168) after the given delay, player state
//   1 with the given next action. [acssnd_FadeOut]
void sub_534488(EEContext& ctx);  // 0x534488
// Set the busy flag (+164). [acssnd_SetBusy]
void sub_534530(EEContext& ctx);  // 0x534530
// A player's fade ended: run its next action (1 start the pending request with a fade-in, 2 stop, 3 pause).
//   [acssnd_FadeEnd]
void sub_534538(EEContext& ctx);  // 0x534538
// Switch to the other player (cross-fade): pause off a still-playing current one, current <- next.
//   [acssnd_NextPlayer]
void sub_534678(EEContext& ctx);  // 0x534678
// Switch back to the previous player. [acssnd_PrevPlayer]
void sub_534728(EEContext& ctx);  // 0x534728
// Fade bookkeeping: run the next action of every player whose fader went idle; when all are idle, call the sound's
//   callback (event 6) and clear busy. [acssnd_CheckFade]
void sub_5347C0(EEContext& ctx);  // 0x5347C0
// Send a player's volume: the fader volume plus the sound's volume and ducking (AIX: per track, with the track
//   volumes). [acssnd_SendVolume]
void sub_534888(EEContext& ctx);  // 0x534888
// 1 when every player's fader is idle. [acssnd_IsAllFadeEnd]
void sub_534960(EEContext& ctx);  // 0x534960
// The fader callback: call the sound's callback (+204) with the event number. [acssnd_FaderCb]
void sub_5349C8(EEContext& ctx);  // 0x5349C8
// Server create: in a caller's work of at least 176 bytes (else an error and 0), reset (named by its error text).
//   [ACSSVR_Create]
void sub_5349F8(EEContext& ctx);  // 0x5349F8
// Server destroy: the reset, when it exists. [ACSSVR_Destroy]
void sub_534A60(EEContext& ctx);  // 0x534A60
// Server init (counted; named by its error text): the first call initialises ADXT and AIXP, registers the server
//   function with SVM ('adxcs_exec_svr') and makes the ducking object. [ACSSVR_Init]
void sub_534A88(EEContext& ctx);  // 0x534A88
// Server finish (counted): the last one releases every sound, the ducking object, the SVM entries, AIXP and ADXT;
//   'Too many Finish' below zero. [ACSSVR_Finish]
void sub_534B60(EEContext& ctx);  // 0x534B60
// Finish the server completely (finish while initialised). [ACSSVR_FinishAll]
void sub_534C58(EEContext& ctx);  // 0x534C58
// Create a sound in the first free of the 16 slots, from the work (208 bytes for the sound, the rest for its players)
//   and the configuration (named by its error text). [ACSSVR_CreatSnd]
void sub_534C98(EEContext& ctx);  // 0x534C98
// Destroy a sound: finish it and free its slot. [ACSSVR_DestroySnd]
void sub_534DB0(EEContext& ctx);  // 0x534DB0
// The server function: the ducking object when enabled, then every sound's frame. [ACSSVR_ExecServer]
void sub_535050(EEContext& ctx);  // 0x535050
// One sound's frame: the ducking offset for kind-1 sounds, then the sound update. [acssvr_ExecSnd]
void sub_5350D0(EEContext& ctx);  // 0x5350D0
// The server's ducking object (+64). [ACSSVR_GetVhl]
void sub_535170(EEContext& ctx);  // 0x535170
// Server reset: the 16 slots and the counts cleared. [acssvr_Reset]
void sub_535178(EEContext& ctx);  // 0x535178
// 1 while the server is initialised (count > 0). [ACSSVR_IsInit]
void sub_5351B0(EEContext& ctx);  // 0x5351B0
// The SVM server entry: run the server function. [acssvr_SvrFunc]
void sub_5351C0(EEContext& ctx);  // 0x5351C0
// Ducking object create: in a caller's work of at least 96 bytes (else an error and 0; named by its error text).
//   [ACSVHL_Create]
void sub_5351E8(EEContext& ctx);  // 0x5351E8
// Ducking object destroy: the reset, when it exists. [ACSVHL_Destroy]
void sub_535250(EEContext& ctx);  // 0x535250
// Ducking object init (named by its error text): its fader in the work at +8, started silent. [ACSVHL_Init]
void sub_535278(EEContext& ctx);  // 0x535278
// Ducking object finish: destroy its fader. [ACSVHL_Finish]
void sub_5352F8(EEContext& ctx);  // 0x5352F8
// Ducking enabled flag (+76). [ACSVHL_IsEnable]
void sub_535348(EEContext& ctx);  // 0x535348
// Ducking state (+80, s8: 0 idle, 1 lowering, 2 low, 3 restoring). [ACSVHL_GetStat]
void sub_535350(EEContext& ctx);  // 0x535350
// The ducking volume (its fader's). [ACSVHL_GetVolume]
void sub_535358(EEContext& ctx);  // 0x535358
// Ducking lowering frames (+84). [ACSVHL_GetDownTime]
void sub_535388(EEContext& ctx);  // 0x535388
// Ducking restoring frames (+88). [ACSVHL_GetUpTime]
void sub_535390(EEContext& ctx);  // 0x535390
// Ducking depth (+92, dB x 10). (A FLIRT name.) [ACSVHL_GetDepth]
void rdbuf__CQ24_STLt9basic_ios2ZcZQ24_STLt11char_traits1Zc(EEContext& ctx);  // 0x535398
// Ducking object owner: the server (+0). [ACSVHL_SetServer]
void sub_5353A0(EEContext& ctx);  // 0x5353A0
// Ducking frame: is a kind-2 sound playing (status 1 / 2 and not paused)?  Then lower the volume by the depth (state
//   1 -> 2); when none is, restore it (state 3 -> 0), resuming a half-done fade from where it is; then step the
//   fader. [acsvhl_ExecServer]
void sub_5353A8(EEContext& ctx);  // 0x5353A8
// Ducking object reset: lowering 30 frames, restoring 60, depth 120. [acsvhl_Reset]
void sub_5355B8(EEContext& ctx);  // 0x5355B8
// Set the ducking state (+80). [acsvhl_SetStat]
void sub_535610(EEContext& ctx);  // 0x535610
// Lowering frames left from the current volume (the down frames scaled by volume / -depth). [acsvhl_CalcDownTime]
void sub_535618(EEContext& ctx);  // 0x535618
// Restoring frames left from the current volume (the up frames scaled by volume / -depth). [acsvhl_CalcUpTime]
void sub_535668(EEContext& ctx);  // 0x535668
// Public: create a sound on the server 0x793F44 points at. [ACSND_Create]
void setenv(EEContext& ctx);  // 0x54D030
// Public: destroy a sound. [ACSND_Destroy]
void unsetenv(EEContext& ctx);  // 0x54D060
// Public: the work size a configuration needs (208 for the sound, per player the back end, its buffers and the fader;
//   AHX and AIX track extras). [ACSND_CalcWorkSize]
void valloc(EEContext& ctx);  // 0x54D080
// Public: start a named file. [ACSND_StartFname]
void pvalloc(EEContext& ctx);  // 0x54D0A0
// Public: start a partition file. [ACSND_StartAfs]
void sub_54D0B8(EEContext& ctx);  // 0x54D0B8
// Public: start from memory. [ACSND_StartMem]
void sub_54D0D0(EEContext& ctx);  // 0x54D0D0
// Public: start a memory index entry. [ACSND_StartMemIdx]
void sub_54D0E8(EEContext& ctx);  // 0x54D0E8
// Public: pause / resume. [ACSND_Pause]
void cosl_4(EEContext& ctx);  // 0x54D118
// Public: the pause state. [ACSND_GetStatPause]
void coshl_4(EEContext& ctx);  // 0x54D130
// Public: the creation parameters. [ACSND_GetCprm]
void hypotf_4(EEContext& ctx);  // 0x54D160
// Public: set the kind (+140). [ACSND_SetKind]
void sub_54D178(EEContext& ctx);  // 0x54D178
// Public: the kind. [ACSND_GetKind]
void sub_54D190(EEContext& ctx);  // 0x54D190
// Public: set the volume. [ACSND_SetOutVol]
void sub_54D1A8(EEContext& ctx);  // 0x54D1A8
// Public: the volume. [ACSND_GetOutVol]
void sub_54D1C0(EEContext& ctx);  // 0x54D1C0
// Public: set an AIX track's volume. [ACSND_SetTrackVol]
void sub_54D1D8(EEContext& ctx);  // 0x54D1D8
// Public: an AIX track's volume (0 for ADX or a track out of range). [ACSND_GetTrackVol]
void sub_54D1F0(EEContext& ctx);  // 0x54D1F0
// Public: set the loop flag. [ACSND_SetLpFlg]
void sub_54D208(EEContext& ctx);  // 0x54D208
// Public: set the fade-in frames (+172). [ACSND_SetFadeInTime]
void sub_54D238(EEContext& ctx);  // 0x54D238
// Public: set the volume-change frames (+176). [ACSND_SetVolChgTime]
void sub_54D250(EEContext& ctx);  // 0x54D250
// Public: the fade-out frames. [ACSND_GetFadeOutTime]
void sub_54D268(EEContext& ctx);  // 0x54D268
// Public: the fade-in frames. [ACSND_GetFadeInTime]
void sub_54D280(EEContext& ctx);  // 0x54D280
// Public: the volume-change frames. [ACSND_GetVolChgTime]
void sub_54D298(EEContext& ctx);  // 0x54D298
// Public: set the cross-fade offset (+180). [ACSND_SetCrossOffset]
void sub_54D2B0(EEContext& ctx);  // 0x54D2B0
// Public: the cross-fade offset. [ACSND_GetCrossOffset]
void sub_54D2C8(EEContext& ctx);  // 0x54D2C8
// Public: set the hold frames (+184). [ACSND_SetHoldTime]
void sub_54D2E0(EEContext& ctx);  // 0x54D2E0
// Public: the hold frames. [ACSND_GetHoldTime]
void sub_54D2F8(EEContext& ctx);  // 0x54D2F8
// Public: set the callback (+204). [ACSND_SetCbFunc]
void sub_54D310(EEContext& ctx);  // 0x54D310
// Public: attach AHX. [ACSND_AttachAhx]
void sub_54D328(EEContext& ctx);  // 0x54D328
// Public: detach AHX. [ACSND_DetachAhx]
void sub_54D340(EEContext& ctx);  // 0x54D340
// Public: set the fader curve. [ACSND_SetFadeCurve]
void sub_54D358(EEContext& ctx);  // 0x54D358
// Public: the current ADXT handle. [ACSND_GetActiveAdxt]
void sub_54D378(EEContext& ctx);  // 0x54D378
// Public: the next ADXT handle. [ACSND_GetNextAdxt]
void atan2l_5(EEContext& ctx);  // 0x54D390
// Public: player n's ADXT handle. [ACSND_GetAdxt]
void cosl_5(EEContext& ctx);  // 0x54D3A8
// Public: the number of ADXT players. [ACSND_GetNumAdxt]
void coshl_5(EEContext& ctx);  // 0x54D3C0
// Public: the current AIXP handle. [ACSND_GetActiveAixp]
void expl_5(EEContext& ctx);  // 0x54D3D8
// Public: the next AIXP handle. [ACSND_GetNextAixp]
void hypotf_5(EEContext& ctx);  // 0x54D3F0
// Public: player n's AIXP handle. [ACSND_GetAixp]
void sub_54D408(EEContext& ctx);  // 0x54D408
// Public: the number of AIXP players. [ACSND_GetNumAixp]
void sub_54D420(EEContext& ctx);  // 0x54D420
// Public: cancel the running fade. [ACSND_CancelFading]
void sub_54D438(EEContext& ctx);  // 0x54D438
// Public: the busy flag. [ACSND_IsBusy]
void sub_54D450(EEContext& ctx);  // 0x54D450
// Public: enable ducking (the server's ACSVHL +76 = 1). [ACSVHL_Enable]
void sub_54D468(EEContext& ctx);  // 0x54D468
// Public: disable ducking. [ACSVHL_Disable]
void sub_54D490(EEContext& ctx);  // 0x54D490
// Public: set the ducking lowering frames (+84). [ACSVHL_SetDownTime]
void sub_54D4B8(EEContext& ctx);  // 0x54D4B8
// Public: set the ducking restoring frames (+88). [ACSVHL_SetUpTime]
void sub_54D4F0(EEContext& ctx);  // 0x54D4F0

}  // namespace p3fes::game
