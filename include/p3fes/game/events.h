// The story-event player (slice events; game/src/event/events.cpp): mt_evtMain.c's event viewer task -- the
// "(ZikkiPlayMode)EventViewer" kwln task that K_Field_UpdateFieldRootTask creates to play a story event / cutscene in
// the field --, its per-frame key interpreter (cut "units" with frame-sorted "keys": actors, camera, messages, sound,
// fades, effects, branches), the scene setup that turns a PM event file into units and keys (mt_evtLoadSave.c /
// mt_evtMisc.c), and the scrComuCommand.c COMM handlers the comm_a / comm_b2 slices left. docs/ANALYSIS/27_unmapped_bands.md
// section 7 maps the band; the layouts below were read from the instructions of these functions and checked against
// a live event in a dorm-route snapshot (extracted/_ours/events_dorm_2100: event E401_002, frame 30 of 0..60,
// 38 units sorted by type rank, keys sorted by frame; tests/game/test_events.cpp).
//
// Every body is p3fes_handgen's register-faithful body (register ABI: arguments in $a0.., the result in $v0) made
// readable: the offsets below name what the original reads and writes; nothing here changes what runs.
// Names in brackets are proposals (symbols/deltas/events.sym); the code keeps the symbols/functions.json names.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game::evt {

// $gp of SLUS_216.21 (the gp-relative globals below are `lw rt, off($gp)`).
inline constexpr u32 kGp = 0x7D2CF0u;

// --- EvtWork: the event viewer's work record, 0x990 (2448) bytes ---------------------------------------------------
// Allocated zeroed by mtEvtMain_CreateZikkiPlayModeEventViewerTask through sub_386AE0 (the RW allocator, memory
// class 0); +0 points at itself; the kwln task's process work (dds3GetProcessWorkData) and every step function's
// `*(process + 60)`.
namespace work {
inline constexpr s32 kSelf = 0;          // u32: the record's own address (freed through it by sub_36F260)
inline constexpr s32 kFlags = 4;         // u32: kFlag* below
inline constexpr s32 kScene = 8;         // u32: the scene built from the PM file (sub_394270): +16 data base, +64 / +68
                                         //      resource table / count (16-byte rows), +148 header, +288 sound bank
inline constexpr s32 kField12 = 12;      // u32: 540 after a reset (sub_361070)
inline constexpr s32 kStartFrame = 16;   // s32: the first frame (units reset their actors when frame == start)
inline constexpr s32 kEndFrame = 20;     // s32: the last frame (539 after a reset; the PM header's value when played)
inline constexpr s32 kFrame = 24;        // s32: the current frame
inline constexpr s32 kPrevFrame = 28;    // s32: the frame the keys were last applied for (sub_36E690)
inline constexpr s32 kJumpRequest = 36;  // s32: 1 = jump to kJumpFrame at the next advance (branch / jump keys)
inline constexpr s32 kJumpFrame = 40;    // s32
inline constexpr s32 kComuIndex = 69;    // s8: the social link of a comu event (1..8; sub_36F260 hands it back)
inline constexpr s32 kMode = 76;         // u8: bit 0 voice / movie file, bit 2 fade to the field on exit, bit 3 comu
inline constexpr s32 kNameCount = 80;    // s32: entries of kNames
inline constexpr s32 kNames = 84;        // char[n][32]: resource names (sub_361FE0 adds; one name in practice)
inline constexpr s32 kUnitCount = 128;   // s32
inline constexpr s32 kUnitHead = 132;    // EvtUnit*: units sorted by the type rank table 0x69D590 (sub_361B60)
inline constexpr s32 kUnitTail = 136;    // EvtUnit*
inline constexpr s32 kMetrics = 140;     // s32: 1 = draw the metrics / memory overlay (sub_386D50), toggled by a pad bit
inline constexpr s32 kMenuStack = 144;   // {u16 menu, u16, u16, u16}[]: the editor's menu stack (sub_36F5F0 / sub_36F640)
inline constexpr s32 kMenuDepth = 208;   // s32
inline constexpr s32 kMenuId = 212;      // s32: the editor menu on top
inline constexpr s32 kMenuFn = 216;      // s32: the menu function index of sub_385860
inline constexpr s32 kMenuArg = 220;     // s32
inline constexpr s32 kMenuFont = 224;    // s32: the editor's text size argument (sub_38A220)
inline constexpr s32 kLightOn = 236;     // s32[6] at 236..256: light units 13/14/15/16/17/23 active this frame
inline constexpr s32 kEdKeyIndex = 348;  // s32: editor cursor (sub_361830)
inline constexpr s32 kEdKeyScroll = 352; // s32
inline constexpr s32 kEdUnit = 356;      // EvtUnit*: the unit the editor shows
inline constexpr s32 kEdField364 = 364;  // s32: editor sub-mode (sub_36D320)
inline constexpr s32 kEdColumn = 616;    // s32: editor column (sub_36FA40)
inline constexpr s32 kEventName = 324;   // char[]: "E%3d_%03d" (major, minor)
inline constexpr s32 kBranchPos = 614;   // s16: the branch slot of the last branch message (0..9, -1)
inline constexpr s32 kLight27On = 632;   // s32: light unit 27 active this frame
inline constexpr s32 kSeCount = 684;     // s32: sound-bank entries to release (sub_38D720)
inline constexpr s32 kSeIds = 688;       // s32[]
inline constexpr s32 kCamUnit = 804;     // model*: the event camera (resource 0x1E58)
inline constexpr s32 kCamSaves = 808;    // {u32[68]}[3]: camera snapshots (sub_38A590), 272 bytes each
inline constexpr s32 kCamSave2 = 1352;   // the third one (sub_38A620)
inline constexpr s32 kCamSelSaved = 1624;// s32: the camera selection to restore (sub_38A730)
inline constexpr s32 kCamSel = 1628;     // s32: 0 = event camera 0x1E58, 1 = 0x1E59 (sub_38A0C0)
inline constexpr s32 kEffectSet = 1808;  // u32: the effect set of the scene (sub_3964C0)
inline constexpr s32 kStopped = 1916;    // s32: 1 while something holds the timeline (sub_36D030)
inline constexpr s32 kMessage = 2092;    // the embedded message handle (sub_39EEE0 / sub_39F350 / sub_39F410 take &work[2092])
inline constexpr s32 kFieldCam = 2160;   // float[4][4] + {u32[16]}: the field camera saved by sub_38F0F0
inline constexpr s32 kFieldScale = 2256; // f32: sub_1A4600's value at load (copied into the camera model +256)
inline constexpr s32 kFadeUnitArg = 2260;// u16
inline constexpr s32 kWaitTask = 2264;   // task*: waited for in load state 13
inline constexpr s32 kFading = 2268;     // s32: 1 while a fade key's fade is up (cleared with sub_1071B0)
inline constexpr s32 kSubTask = 2340;    // task*: the task a type-29 key started (sub_10BC20)
inline constexpr s32 kField2344 = 2344;  // u32: copied from 0x7CDEAC at the first update (sub_36F370)
inline constexpr s32 kTask = 2348;       // task*: the viewer's own kwln task (parent of the tasks it creates)
inline constexpr s32 kPmTask = 2352;     // task*: the PM reader being waited for (sub_36D500)
inline constexpr s32 kPmReader = 2356;   // task*: the PM file reader (MT_EvtPMFileReader, sub_397F80 / sub_3980E0)
inline constexpr s32 kOverlayTask = 2360;// task*: cleared with flag 0x20000 (sub_36E140)
inline constexpr s32 kVoiceTask = 2364;  // task*: the voice / movie loader of load state 14 (sub_10A770)
inline constexpr s32 kCursorShown = 2368;// u8
inline constexpr s32 kCursors = 2372;    // task*[7]: H_Cursor tasks (sub_3858C0)
inline constexpr s32 kLoadState = 2400;  // s32: sub_36DB20's state 0..16
inline constexpr s32 kLoadArg = 2404;    // s32: the PM reader's 4th argument
inline constexpr s32 kMajor = 2408;      // s32: event major number (sub_386E10 / sub_386E20)
inline constexpr s32 kMinor = 2412;      // s32: event minor number (sub_386E30 / sub_386E40)
inline constexpr s32 kNpcLoads = 2420;   // s32: models still to load in states 6 / 7
inline constexpr s32 kLoadResult = 2424; // s32: sub_36DB20's result in its last state
inline constexpr s32 kResCount = 2428;   // s32: entries of kResources
inline constexpr s32 kResources = 2432;  // u32*: resource backups (sub_388FF0 frees them)
inline constexpr u32 kSize = 2448;

// kFlags bits
inline constexpr u32 kFlagPaused = 0x1;       // the timeline does not advance (editor; set by a reset)
inline constexpr u32 kFlagFilter = 0x2;       // a type-7 key is on (sub_3BCBF0; off through sub_3BCC80); inf: a screen filter
inline constexpr u32 kFlagShake = 0x4;        // a type-8 key's two values are non-zero; inf: a screen shake
inline constexpr u32 kFlagPlayMode = 0x8;     // "zikki" (actual-machine) play mode: the retail player
inline constexpr u32 kFlagNoSound = 0x10;     // skips the sound / adx keys and the message keys
inline constexpr u32 kFlagMessage = 0x20;     // waiting for a message to close
inline constexpr u32 kFlagReload = 0x80;      // reload the scene (back to sub_36DB20)
inline constexpr u32 kFlagPmWait = 0x100;
inline constexpr u32 kFlagFx0 = 0x200;        // effect channels 0..2 busy (type-36 keys)
inline constexpr u32 kFlagFx1 = 0x400;
inline constexpr u32 kFlagFx2 = 0x800;
inline constexpr u32 kFlag1000 = 0x1000;      // waiting for sub_3CF630
inline constexpr u32 kFlagFadeWait = 0x2000;  // waiting for a fade (sub_108710)
inline constexpr u32 kFlagSubTask = 0x4000;   // kSubTask running
inline constexpr u32 kFlagComuMessage = 0x8000;// a comu message (sub_3C9790) is up
inline constexpr u32 kFlag10000 = 0x10000;    // go to sub_36E2F0
inline constexpr u32 kFlagOverlay = 0x20000;  // go to sub_36E140
inline constexpr u32 kFlagEnd = 0x40000;      // the event ends: go to sub_36E260
}  // namespace work

// --- EvtUnit: one cut unit (track), 0x9C (156) bytes (sub_361CA0) ---------------------------------------------------
// Types seen: 1 character (model), 4 message, 5 adx sound, 6 fade, 7 filter, 8 shake, 10 camera (param = slot 0..2),
// 13..17 / 23 / 27 lights, 19 sound, 28 / 29 sub tasks, 33 camera model, 34 / 38 / 40 jumps, 35 sound volume, 36 effect
// (param = channel), 37 p3 effects, 39 "keyfree", 41..46 / 50 comu / dialogue events, 47 / 49 model show / visibility,
// 48 field object (param 0..7).
namespace unit {
inline constexpr s32 kType = 0;          // s32
inline constexpr s32 kParam = 4;         // s32: slot / channel / index within the type
inline constexpr s32 kName = 8;          // s32: kNames index, -1
inline constexpr s32 kResId = 12;        // u16: the model's resource id (top 6 bits: the model kind)
inline constexpr s32 kHold = 32;         // s16: frames a key stays current after its own frame (sub_366AC0)
inline constexpr s32 kCamMode = 34;      // s8: camera units: 0 none, 1 fixed, 2 key-driven, 3 follow a model
inline constexpr s32 kCamTarget = 36;    // u16: the followed model's resource id
inline constexpr s32 kModel = 56;        // model*: the actor (sub_3B5D10 record)
inline constexpr s32 kPos = 60;          // f32[3]: the actor's position at the start frame
inline constexpr s32 kRot = 72;          // f32[3]: its rotation
inline constexpr s32 kColor = 84;        // u8[4]
inline constexpr s32 kModelFlags = 88;   // u32: the model's +40 flags at setup (bit 1: shown)
inline constexpr s32 kPathMove = 100;    // s32: 1 while a path move keeps the actor's direction
inline constexpr s32 kKeyCount = 104;    // s32
inline constexpr s32 kKeyHead = 108;     // EvtKey*: keys sorted by frame (sub_361140)
inline constexpr s32 kKeyTail = 112;     // EvtKey*
inline constexpr s32 kSlotKeys = 116;    // EvtKey*[4]: the motion key current in each animation slot (sub_366660)
inline constexpr s32 kNext = 148;        // EvtUnit*
inline constexpr s32 kPrev = 152;        // EvtUnit*
inline constexpr u32 kSize = 156;
}  // namespace unit

// --- EvtKey: one key of a unit, 0x54 (84) bytes (sub_361350) --------------------------------------------------------
namespace key {
inline constexpr s32 kFrame = 0;         // u16: the frame it fires on
inline constexpr s32 kLength = 2;        // u16: duration (moves, fades, comu windows)
inline constexpr s32 kName = 4;          // s32: kNames index, -1
inline constexpr s32 kCondFlag = 8;      // s16: condition (sub_360ED0): flag / counter number
inline constexpr s32 kCondValue = 10;    // s16: expected bit (type 2) or counter value (type 1)
inline constexpr s32 kCondType = 12;     // s8: 0 always, 1 counter == value (sub_38D6F0), 2 flag bit (MT_Misc_BitChk)
inline constexpr s32 kCondBank = 14;     // u8: flag bank of type 2: 0 +0, 1 +1024, 2 +4096 (3+ never true)
inline constexpr s32 kCmd = 16;          // u8 / s16 / ...: first parameter (the sub-command of unit keys)
inline constexpr s32 kArg20 = 20;        // parameters 20.. (per type)
inline constexpr s32 kOwnerType = 56;    // s32: the unit's type, copied at creation
inline constexpr s32 kPath = 64;         // u8[304]*: the path of a path-move key (sub_38D790)
inline constexpr s32 kExtra = 72;        // void*: camera keys' 48-byte record (sub_38C540)
inline constexpr s32 kNext = 76;         // EvtKey*
inline constexpr s32 kPrev = 80;         // EvtKey*
inline constexpr u32 kSize = 84;
}  // namespace key

// --- The PM scene description the loaders walk (the reader's data, a1 of sub_38F440 / sub_38F8C0) -----------------
namespace pm {
inline constexpr s32 kPaths = 100;       // u8[304][]: path records
inline constexpr s32 kHeader = 132;      // u32*: header; +20 = the format version (4: 16-byte key rows)
inline constexpr s32 kKeys4 = 152;       // version-4 key rows, 16 bytes: u16 unit type, u16 frame, u16 length, u16, params at +8
inline constexpr s32 kKeys = 156;        // key rows, 60 bytes: u16 unit type, u16 frame, u16 length, ..., u16 unit id at +8,
                                         // s16 condition[4] at +12, params at +20
inline constexpr s32 kKeyCount = 176;    // s32
}  // namespace pm

// --- gp-relative globals of mt_evtMain.c / scrComuCommand.c (0x7CE5AC..0x7CE614) ------------------------------------
inline constexpr s32 kGpComuMsgTask = -18228;   // 0x7CE5BC: the message task of COMM 0x360990
inline constexpr s32 kGpRevMailTask = -18224;   // 0x7CE5C0: comu_CreateRevMailSeqTask's task (COMM 0x360A40)
inline constexpr s32 kGpComuTask3 = -18220;     // 0x7CE5C4: sub_39B8B0's task (COMM 0x360B00)
inline constexpr s32 kGpSkillCursor = -18216;   // 0x7CE5C8: index into the skill list of COMM 0x360CF0 / 0x360D40
inline constexpr s32 kGpSkillList = -18212;     // 0x7CE5CC: u16* list (sub_3BEE80)
inline constexpr s32 kGpSkillCount = -18208;    // 0x7CE5D0: its length
inline constexpr s32 kGpComuIndex = -18204;     // 0x7CE5D4: the social link of COMM 0x360110
inline constexpr s32 kGpMetricsOn = -18200;     // 0x7CE5D8: work+140 == 1, mirrored each frame
inline constexpr s32 kGpPmWaitCount = -18188;   // 0x7CE5E4: frames waited for the PM reader (sub_36D500)
inline constexpr s32 kGpNpcLoad = -18184;       // 0x7CE5E8: the model load request of states 6 / 7
inline constexpr s32 kGpNpcModel = -18180;      // 0x7CE5EC: u16 the loaded model
inline constexpr s32 kGpKeyFree = -18176;       // 0x7CE5F0: 1 = the field resumes free movement after the event
inline constexpr s32 kGpStartPos = -18172;      // 0x7CE5F4: the entrance the field places the party at

}  // namespace p3fes::game::evt

namespace p3fes::game {


void sub_360110(EEContext& ctx);  // 0x360110 (register ABI: arguments in $a0.., the result in $v0)
void sub_3604A0(EEContext& ctx);  // 0x3604A0 (register ABI: arguments in $a0.., the result in $v0)
void sub_360570(EEContext& ctx);  // 0x360570 (register ABI: arguments in $a0.., the result in $v0)
void sub_360640(EEContext& ctx);  // 0x360640 (register ABI: arguments in $a0.., the result in $v0)
void sub_3606F0(EEContext& ctx);  // 0x3606F0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3607A0(EEContext& ctx);  // 0x3607A0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3608E0(EEContext& ctx);  // 0x3608E0 (register ABI: arguments in $a0.., the result in $v0)
void sub_360990(EEContext& ctx);  // 0x360990 (register ABI: arguments in $a0.., the result in $v0)
void sub_360A40(EEContext& ctx);  // 0x360A40 (register ABI: arguments in $a0.., the result in $v0)
void sub_360AB0(EEContext& ctx);  // 0x360AB0 (register ABI: arguments in $a0.., the result in $v0)
void sub_360B00(EEContext& ctx);  // 0x360B00 (register ABI: arguments in $a0.., the result in $v0)
void sub_360B70(EEContext& ctx);  // 0x360B70 (register ABI: arguments in $a0.., the result in $v0)
void sub_360C50(EEContext& ctx);  // 0x360C50 (register ABI: arguments in $a0.., the result in $v0)
void sub_360CF0(EEContext& ctx);  // 0x360CF0 (register ABI: arguments in $a0.., the result in $v0)
void sub_360D40(EEContext& ctx);  // 0x360D40 (register ABI: arguments in $a0.., the result in $v0)
void sub_360ED0(EEContext& ctx);  // 0x360ED0 (register ABI: arguments in $a0.., the result in $v0)
void sub_361050(EEContext& ctx);  // 0x361050 (register ABI: arguments in $a0.., the result in $v0)
void sub_361070(EEContext& ctx);  // 0x361070 (register ABI: arguments in $a0.., the result in $v0)
void sub_361140(EEContext& ctx);  // 0x361140 (register ABI: arguments in $a0.., the result in $v0)
void sub_361200(EEContext& ctx);  // 0x361200 (register ABI: arguments in $a0.., the result in $v0)
void sub_361270(EEContext& ctx);  // 0x361270 (register ABI: arguments in $a0.., the result in $v0)
void sub_361350(EEContext& ctx);  // 0x361350 (register ABI: arguments in $a0.., the result in $v0)
void sub_361830(EEContext& ctx);  // 0x361830 (register ABI: arguments in $a0.., the result in $v0)
void sub_361890(EEContext& ctx);  // 0x361890 (register ABI: arguments in $a0.., the result in $v0)
void sub_361B60(EEContext& ctx);  // 0x361B60 (register ABI: arguments in $a0.., the result in $v0)
void sub_361C30(EEContext& ctx);  // 0x361C30 (register ABI: arguments in $a0.., the result in $v0)
void sub_361CA0(EEContext& ctx);  // 0x361CA0 (register ABI: arguments in $a0.., the result in $v0)
void sub_361D60(EEContext& ctx);  // 0x361D60 (register ABI: arguments in $a0.., the result in $v0)
void sub_361DD0(EEContext& ctx);  // 0x361DD0 (register ABI: arguments in $a0.., the result in $v0)
void sub_361EE0(EEContext& ctx);  // 0x361EE0 (register ABI: arguments in $a0.., the result in $v0)
void sub_361F20(EEContext& ctx);  // 0x361F20 (register ABI: arguments in $a0.., the result in $v0)
void sub_361F60(EEContext& ctx);  // 0x361F60 (register ABI: arguments in $a0.., the result in $v0)
void sub_361FE0(EEContext& ctx);  // 0x361FE0 (register ABI: arguments in $a0.., the result in $v0)
void nullsub_114(EEContext& ctx);  // 0x362100 (register ABI: arguments in $a0.., the result in $v0)
void nullsub_115(EEContext& ctx);  // 0x362110 (register ABI: arguments in $a0.., the result in $v0)
void sub_362120(EEContext& ctx);  // 0x362120 (register ABI: arguments in $a0.., the result in $v0)
void sub_362240(EEContext& ctx);  // 0x362240 (register ABI: arguments in $a0.., the result in $v0)
void sub_362290(EEContext& ctx);  // 0x362290 (register ABI: arguments in $a0.., the result in $v0)
void sub_362310(EEContext& ctx);  // 0x362310 (register ABI: arguments in $a0.., the result in $v0)
void sub_362F20(EEContext& ctx);  // 0x362F20 (register ABI: arguments in $a0.., the result in $v0)
void sub_362FA0(EEContext& ctx);  // 0x362FA0 (register ABI: arguments in $a0.., the result in $v0)
void sub_362FF0(EEContext& ctx);  // 0x362FF0 (register ABI: arguments in $a0.., the result in $v0)
void sub_363030(EEContext& ctx);  // 0x363030 (register ABI: arguments in $a0.., the result in $v0)
void sub_3638E0(EEContext& ctx);  // 0x3638E0 (register ABI: arguments in $a0.., the result in $v0)
void sub_364470(EEContext& ctx);  // 0x364470 (register ABI: arguments in $a0.., the result in $v0)
void sub_3645C0(EEContext& ctx);  // 0x3645C0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3646D0(EEContext& ctx);  // 0x3646D0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3648E0(EEContext& ctx);  // 0x3648E0 (register ABI: arguments in $a0.., the result in $v0)
void sub_364A30(EEContext& ctx);  // 0x364A30 (register ABI: arguments in $a0.., the result in $v0)
void sub_364B10(EEContext& ctx);  // 0x364B10 (register ABI: arguments in $a0.., the result in $v0)
void sub_364E40(EEContext& ctx);  // 0x364E40 (register ABI: arguments in $a0.., the result in $v0)
void sub_3650C0(EEContext& ctx);  // 0x3650C0 (register ABI: arguments in $a0.., the result in $v0)
void sub_365250(EEContext& ctx);  // 0x365250 (register ABI: arguments in $a0.., the result in $v0)
void sub_365360(EEContext& ctx);  // 0x365360 (register ABI: arguments in $a0.., the result in $v0)
void sub_365430(EEContext& ctx);  // 0x365430 (register ABI: arguments in $a0.., the result in $v0)
void sub_3655F0(EEContext& ctx);  // 0x3655F0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3657E0(EEContext& ctx);  // 0x3657E0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3658B0(EEContext& ctx);  // 0x3658B0 (register ABI: arguments in $a0.., the result in $v0)
void sub_365A40(EEContext& ctx);  // 0x365A40 (register ABI: arguments in $a0.., the result in $v0)
void sub_365B70(EEContext& ctx);  // 0x365B70 (register ABI: arguments in $a0.., the result in $v0)
void sub_365CD0(EEContext& ctx);  // 0x365CD0 (register ABI: arguments in $a0.., the result in $v0)
void sub_365F80(EEContext& ctx);  // 0x365F80 (register ABI: arguments in $a0.., the result in $v0)
void sub_366210(EEContext& ctx);  // 0x366210 (register ABI: arguments in $a0.., the result in $v0)
void sub_366330(EEContext& ctx);  // 0x366330 (register ABI: arguments in $a0.., the result in $v0)
void sub_3663F0(EEContext& ctx);  // 0x3663F0 (register ABI: arguments in $a0.., the result in $v0)
void sub_366540(EEContext& ctx);  // 0x366540 (register ABI: arguments in $a0.., the result in $v0)
void sub_366660(EEContext& ctx);  // 0x366660 (register ABI: arguments in $a0.., the result in $v0)
void sub_366970(EEContext& ctx);  // 0x366970 (register ABI: arguments in $a0.., the result in $v0)
void sub_366AC0(EEContext& ctx);  // 0x366AC0 (register ABI: arguments in $a0.., the result in $v0)
void sub_36D030(EEContext& ctx);  // 0x36D030 (register ABI: arguments in $a0.., the result in $v0)
void sub_36D320(EEContext& ctx);  // 0x36D320 (register ABI: arguments in $a0.., the result in $v0)
void sub_36D470(EEContext& ctx);  // 0x36D470 (register ABI: arguments in $a0.., the result in $v0)
void sub_36D500(EEContext& ctx);  // 0x36D500 (register ABI: arguments in $a0.., the result in $v0)
void sub_36DA10(EEContext& ctx);  // 0x36DA10 (register ABI: arguments in $a0.., the result in $v0)
void sub_36DB20(EEContext& ctx);  // 0x36DB20 (register ABI: arguments in $a0.., the result in $v0)
void sub_36E140(EEContext& ctx);  // 0x36E140 (register ABI: arguments in $a0.., the result in $v0)
void sub_36E260(EEContext& ctx);  // 0x36E260 (register ABI: arguments in $a0.., the result in $v0)
void sub_36E690(EEContext& ctx);  // 0x36E690 (register ABI: arguments in $a0.., the result in $v0)
void sub_36ED30(EEContext& ctx);  // 0x36ED30 (register ABI: arguments in $a0.., the result in $v0)
void sub_36EDD0(EEContext& ctx);  // 0x36EDD0 (register ABI: arguments in $a0.., the result in $v0)
void mtEvtMain_UpdateZikkiPlayModeEventViewerTask(EEContext& ctx);  // 0x36EE30 (register ABI: arguments in $a0.., the result in $v0)
void sub_36EFB0(EEContext& ctx);  // 0x36EFB0 (register ABI: arguments in $a0.., the result in $v0)
void sub_36F000(EEContext& ctx);  // 0x36F000 (register ABI: arguments in $a0.., the result in $v0)
void sub_36F260(EEContext& ctx);  // 0x36F260 (register ABI: arguments in $a0.., the result in $v0)
void sub_36F370(EEContext& ctx);  // 0x36F370 (register ABI: arguments in $a0.., the result in $v0)
void mtEvtMain_CreateZikkiPlayModeEventViewerTask(EEContext& ctx);  // 0x36F3B0 (register ABI: arguments in $a0.., the result in $v0)
void sub_36F480(EEContext& ctx);  // 0x36F480 (register ABI: arguments in $a0.., the result in $v0)
void sub_36F490(EEContext& ctx);  // 0x36F490 (register ABI: arguments in $a0.., the result in $v0)
void sub_36F4C0(EEContext& ctx);  // 0x36F4C0 (register ABI: arguments in $a0.., the result in $v0)
void sub_36F4D0(EEContext& ctx);  // 0x36F4D0 (register ABI: arguments in $a0.., the result in $v0)
void sub_36F500(EEContext& ctx);  // 0x36F500 (register ABI: arguments in $a0.., the result in $v0)
void sub_36F5F0(EEContext& ctx);  // 0x36F5F0 (register ABI: arguments in $a0.., the result in $v0)
void sub_36F640(EEContext& ctx);  // 0x36F640 (register ABI: arguments in $a0.., the result in $v0)
void sub_36F900(EEContext& ctx);  // 0x36F900 (register ABI: arguments in $a0.., the result in $v0)
void sub_36FA40(EEContext& ctx);  // 0x36FA40 (register ABI: arguments in $a0.., the result in $v0)
void sub_385860(EEContext& ctx);  // 0x385860 (register ABI: arguments in $a0.., the result in $v0)
void sub_3858C0(EEContext& ctx);  // 0x3858C0 (register ABI: arguments in $a0.., the result in $v0)
void sub_385B20(EEContext& ctx);  // 0x385B20 (register ABI: arguments in $a0.., the result in $v0)
void nullsub_26(EEContext& ctx);  // 0x385B90 (register ABI: arguments in $a0.., the result in $v0)
void sub_385BA0(EEContext& ctx);  // 0x385BA0 (register ABI: arguments in $a0.., the result in $v0)
void sub_386110(EEContext& ctx);  // 0x386110 (register ABI: arguments in $a0.., the result in $v0)
void sub_386210(EEContext& ctx);  // 0x386210 (register ABI: arguments in $a0.., the result in $v0)
void sub_386390(EEContext& ctx);  // 0x386390 (register ABI: arguments in $a0.., the result in $v0)
void sub_386AA0(EEContext& ctx);  // 0x386AA0 (register ABI: arguments in $a0.., the result in $v0)
void sub_386AE0(EEContext& ctx);  // 0x386AE0 (register ABI: arguments in $a0.., the result in $v0)
void sub_386B70(EEContext& ctx);  // 0x386B70 (register ABI: arguments in $a0.., the result in $v0)
void sub_386C40(EEContext& ctx);  // 0x386C40 (register ABI: arguments in $a0.., the result in $v0)
void sub_386CD0(EEContext& ctx);  // 0x386CD0 (register ABI: arguments in $a0.., the result in $v0)
void sub_386E10(EEContext& ctx);  // 0x386E10 (register ABI: arguments in $a0.., the result in $v0)
void sub_386E20(EEContext& ctx);  // 0x386E20 (register ABI: arguments in $a0.., the result in $v0)
void sub_386E30(EEContext& ctx);  // 0x386E30 (register ABI: arguments in $a0.., the result in $v0)
void sub_386E40(EEContext& ctx);  // 0x386E40 (register ABI: arguments in $a0.., the result in $v0)
void sub_388FF0(EEContext& ctx);  // 0x388FF0 (register ABI: arguments in $a0.., the result in $v0)
void sub_389F40(EEContext& ctx);  // 0x389F40 (register ABI: arguments in $a0.., the result in $v0)
void sub_38A0B0(EEContext& ctx);  // 0x38A0B0 (register ABI: arguments in $a0.., the result in $v0)
void sub_38A0C0(EEContext& ctx);  // 0x38A0C0 (register ABI: arguments in $a0.., the result in $v0)
void sub_38A140(EEContext& ctx);  // 0x38A140 (register ABI: arguments in $a0.., the result in $v0)
void sub_38A180(EEContext& ctx);  // 0x38A180 (register ABI: arguments in $a0.., the result in $v0)
void sub_38A220(EEContext& ctx);  // 0x38A220 (register ABI: arguments in $a0.., the result in $v0)
void sub_38A480(EEContext& ctx);  // 0x38A480 (register ABI: arguments in $a0.., the result in $v0)
void sub_38A4B0(EEContext& ctx);  // 0x38A4B0 (register ABI: arguments in $a0.., the result in $v0)
void sub_38A590(EEContext& ctx);  // 0x38A590 (register ABI: arguments in $a0.., the result in $v0)
void sub_38A620(EEContext& ctx);  // 0x38A620 (register ABI: arguments in $a0.., the result in $v0)
void sub_38A6C0(EEContext& ctx);  // 0x38A6C0 (register ABI: arguments in $a0.., the result in $v0)
void sub_38A730(EEContext& ctx);  // 0x38A730 (register ABI: arguments in $a0.., the result in $v0)
void sub_38A900(EEContext& ctx);  // 0x38A900 (register ABI: arguments in $a0.., the result in $v0)
void sub_38C460(EEContext& ctx);  // 0x38C460 (register ABI: arguments in $a0.., the result in $v0)
void sub_38CA00(EEContext& ctx);  // 0x38CA00 (register ABI: arguments in $a0.., the result in $v0)
void sub_38CA80(EEContext& ctx);  // 0x38CA80 (register ABI: arguments in $a0.., the result in $v0)
void sub_38CC10(EEContext& ctx);  // 0x38CC10 (register ABI: arguments in $a0.., the result in $v0)
void sub_38D560(EEContext& ctx);  // 0x38D560 (register ABI: arguments in $a0.., the result in $v0)
void sub_38D6B0(EEContext& ctx);  // 0x38D6B0 (register ABI: arguments in $a0.., the result in $v0)
void sub_38D6F0(EEContext& ctx);  // 0x38D6F0 (register ABI: arguments in $a0.., the result in $v0)
void sub_38D720(EEContext& ctx);  // 0x38D720 (register ABI: arguments in $a0.., the result in $v0)
void sub_38D790(EEContext& ctx);  // 0x38D790 (register ABI: arguments in $a0.., the result in $v0)
void sub_38D840(EEContext& ctx);  // 0x38D840 (register ABI: arguments in $a0.., the result in $v0)
void sub_38D910(EEContext& ctx);  // 0x38D910 (register ABI: arguments in $a0.., the result in $v0)
void sub_38D980(EEContext& ctx);  // 0x38D980 (register ABI: arguments in $a0.., the result in $v0)
void sub_38DA10(EEContext& ctx);  // 0x38DA10 (register ABI: arguments in $a0.., the result in $v0)
void sub_38F0F0(EEContext& ctx);  // 0x38F0F0 (register ABI: arguments in $a0.., the result in $v0)
void sub_38F440(EEContext& ctx);  // 0x38F440 (register ABI: arguments in $a0.., the result in $v0)
void sub_38F8C0(EEContext& ctx);  // 0x38F8C0 (register ABI: arguments in $a0.., the result in $v0)
void sub_38FA10(EEContext& ctx);  // 0x38FA10 (register ABI: arguments in $a0.., the result in $v0)
void sub_38FFB0(EEContext& ctx);  // 0x38FFB0 (register ABI: arguments in $a0.., the result in $v0)

}  // namespace p3fes::game
