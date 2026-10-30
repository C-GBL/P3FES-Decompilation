// The event system, second pass (slice events2; game/src/event/events2.cpp): what the events slice (events.h) left of
// mt_evt*.c in 0x360000-0x3A0000 -- the event editor's process step and its 48-entry menu-action table, the NPC
// reload step, the event-start helpers (the PM unit / key builder sub_3912F0 [evtSetGameData] with its per-type passes,
// the PM scene parser sub_3942F0, the cut-flag reset after a seek), the resource backups, model / camera / path helpers
// and the event save of mt_evtMisc.c / mt_evtLoadSave.c, the polygon-movie draws, and the custom events of
// mt_evtCustomEvent.c (the invitation, present, phone, game-over, card-effect ... tasks a type-41 key starts).
//
// Every body is p3fes_handgen's register-faithful body (register ABI: arguments in $a0.., the result in $v0) with its
// role written above it and the record offsets below named where the base register holds that record for the whole
// function; nothing here changes what runs. Names in brackets are proposals (symbols/deltas/events2.sym); the code
// keeps the symbols/functions.json names. The EvtWork / EvtUnit / EvtKey layouts are events.h's (namespace evt); this
// header adds what the second pass reads.
//
// ===== How a story event is started, stepped and ended (for the scene editor and the multiplayer server) ==========
// Records: EvtWork (2448 B, evt::work, one per playing event), its units (evt::unit, 156 B, sorted by type rank) and
// their keys (evt::key, 84 B, sorted by frame), the parsed PM scene (evt2::scene, at work + kScene), the PM reader task.
//
// START (field root state 0 / 14..16, docs/ANALYSIS/26_field.md section 5.4):
//   1. MT_EvtPMFileReader_CreateTask (0x397EC0) loads "E%3d_%03d.PM1/PM2/PM3"; sub_398140 yields its field ids.
//   2. mtEvtMain_CreateZikkiPlayModeEventViewerTask(parent, reader) (0x36F3B0) allocates and zeroes EvtWork (kSelf),
//      clears the field-resume pair 0x7CE5F0 / 0x7CE5F4 and creates the kwln task "(ZikkiPlayMode)EventViewer"
//      (update 0x36EE30, destroy sub_36F260) -> work.kTask; work.kPmReader = reader.
//   3. First update: sub_36F370 (init), major / minor from the reader's header -> kMajor / kMinor, kEventName,
//      kFlags = kFlagPlayMode (0x8), then sub_393E30 installs the process steps, first sub_36EDD0.
//   4. sub_36DB20 [evtStepSceneRead], kLoadState 0..16: 3 = sub_394270 + sub_3942F0 [pmSceneParse] (PM1 / PM2 / PM3
//      sections into evt2::scene), 4..10 field, NPC models, effect set, 11 = sub_3912F0 [evtSetGameData] (units and
//      keys from the PM2 key rows; frame header -> kFrameCount (+12), kStartFrame (+16), kEndFrame (+20); kFrame =
//      start, kPrevFrame = -1), 16 = BGM, resource backups (sub_3890E0, editor only), scene start. Then sub_36ED30.
// STEP (one call of sub_36E690 [evtStepPlay] per frame; the process returns the next step function):
//   - flag dispatch first: kFlagEnd (0x40000) -> sub_36E260; kFlagReload (0x80) -> sub_36DB20; kFlag10000 ->
//     sub_36E2F0 [evtStepNpcReload] (it returns the step saved in work +2336); kFlagOverlay (0x20000, set by
//     sub_39E1B0 [evtStartCustomEvent] together with kOverlayTask = the custom-event task) -> sub_36E140, which waits
//     until that task has ended, clears the flag and goes back to sub_36E690.
//   - when kFrame != kPrevFrame: sub_366AC0 [evtApplyFrame] fires every key whose frame is reached and whose
//     condition holds (sub_360ED0), kPrevFrame = kFrame.
//   - the timeline advances one frame unless kStopped (1916) holds it (message open kFlagMessage 0x20, effect channels
//     0x200..0x800, fade 0x2000, sub task 0x4000, comu message 0x8000; sub_36D030); a jump request (kJumpRequest = 1,
//     kJumpFrame) is taken at the next advance. A debug seek (sub_362390) closes the message and resets the branch cut
//     flags for the target frame (sub_38C830) before requesting the jump.
//   - pad bit 2 (debug) enters the editor: the step becomes sub_36D5F0 [evtStepEditor] until its menu stack empties.
// END: in play mode the frame reaching kEndFrame (or the skip of events 80-1 / 80-5 after frame 30) sets kFlagEnd;
//   sub_36E260 waits for the fades and returns -1, the process ends, the task is destroyed and its destroy callback
//   sub_36F260 frees the scene (sub_36F000), hands the comu index (+69) back, frees the work. The field root then reads
//   sub_36F480 (free movement after the event: 0x7CE5F0, set by a type-39 key) and sub_36F4C0 (the entrance 0x7CE5F4).
// A server that runs events headless needs exactly: the PM files, EvtWork + units / keys, kFrame / kStopped / kFlags
//   per frame, the custom-event tasks (their answers are player input: choices of sub_39F800 through the message
//   slot), the branch answers (sub_397580) and the event counters / flags the key conditions read.
#pragma once

#include "p3fes/ee_context.h"
#include "p3fes/game/events.h"

namespace p3fes::game::evt2 {

// --- EvtWork fields the second pass names (events.h's evt::work has the rest) -----------------------------------------
namespace work {
inline constexpr s32 kFrameCount = 12;     // s32: frames of the event (PM frame header +8; events.h: kField12); kFrame
                                           //      stays in [0, kFrameCount - 1]
inline constexpr s32 kHeaderCopy = 44;     // u32[9]: the PM frame header copied by sub_3912F0
inline constexpr s32 kMenuX = 32;          // s16: the editor menu's draw position (sub_36D5F0)
inline constexpr s32 kMenuY = 34;          // s16
inline constexpr s32 kEdListBox = 232;     // task*: the open debug list box ("ksk list box", sub_385BD0 ..)
inline constexpr s32 kEdIoItem = 260;      // s32: the settings item / load-save mode (0 save, 1 / 2 load)
inline constexpr s32 kEdListPos = 264;     // s32: list cursor
inline constexpr s32 kEdListTop = 272;     // s32: list scroll (choice = top + pos)
inline constexpr s32 kEdChoice = 280;      // s32: the list choice's result
inline constexpr s32 kEdChoiceCount = 284; // s32
inline constexpr s32 kEdChoiceTitle = 288; // char*
inline constexpr s32 kEdChoiceItems = 292; // char**
inline constexpr s32 kEdColumnKind = 344;  // s32: the selected column (index into the column table 0x69E1A2 row)
inline constexpr s32 kEdChoiceKind = 360;  // s32: which list the choice came from
inline constexpr s32 kEdValue = 364;       // s32: the numeric editor's value
inline constexpr s32 kEdValueMin = 368;    // s32
inline constexpr s32 kEdValueMax = 372;    // s32
inline constexpr s32 kEdValueF = 388;      // f32: the float editor's value
inline constexpr s32 kEdSubChoice = 400;   // s32: the sub-choice of the key menus
inline constexpr s32 kEdParams = 408;      // s32[12] at 408..452: the key parameters being edited (+440.. colour)
inline constexpr s32 kEdResClass = 1632;   // s32: the model class of the resource list
inline constexpr s32 kEdCondition = 1924;  // u16[4]: the condition being edited (flag, value, type, bank)
// The NPC reload of sub_36E2F0 (kFlag10000), a sub-record at 2272:
inline constexpr s32 kNpc = 2272;
}  // namespace work

// --- sub_36E2F0's NPC reload record (work + 2272) ---------------------------------------------------------------------
namespace npc {
inline constexpr s32 kState = 0;           // s32: 0..5
inline constexpr s32 kCount = 4;           // s32: slots
inline constexpr s32 kRowStride = 12;      // slot i at 12 * i: +8 u16 the model kind, +12 u16 the model id (0: none)
inline constexpr s32 kRowKind = 8;
inline constexpr s32 kRowModel = 12;
inline constexpr s32 kUnits = 44;          // EvtUnit*[]: slot i's character unit (resource 900 + i | 0xC00)
inline constexpr s32 kIndex = 56;          // s32: the slot being loaded
inline constexpr s32 kLoad = 60;           // the model load request (sub_316E00 / sub_316F70)
inline constexpr s32 kReturnStep = 64;     // the process step to return to
}  // namespace npc

// --- The parsed PM scene (work + kScene; filled by sub_3942F0 from the PM1 / PM2 / PM3 files) ---------------------
// Each file starts with a header (+16 = number of type rows) and 16-byte type rows at +32: +0 type, +8 count, +12
// offset of the section (from the file start).
namespace scene {
inline constexpr s32 kPm1 = 16;            // PM1 data
inline constexpr s32 kPm1Rows = 20;        // its type rows (PM1 + 32)
inline constexpr s32 kNames = 24;          // type 1 (+28 count): resource name strings (32 bytes each)
inline constexpr s32 kPm1Type2 = 32;       // type 2 .. type 23 sections at +32..+92 (with counts where the row has one)
inline constexpr s32 kMessage = 76;        // type 6 (+80 count): the message (BMD) section
inline constexpr s32 kNameRows = 84;       // type 22 (+88 count): 16-byte name rows (sub_3912F0: one character unit each)
inline constexpr s32 kExtRefs = 96;        // type 27: the external reference table ("gaibu Ref Table")
inline constexpr s32 kPaths = 100;         // PM2 type 26 (+104 count): 304-byte path records (events.h pm::kPaths)
inline constexpr s32 kPm2 = 132;           // PM2 data (events.h pm::kHeader; +20 the format version)
inline constexpr s32 kPm2Rows = 136;       // its type rows
inline constexpr s32 kPm2Type1 = 140;      // type 1 (+144 count)
inline constexpr s32 kFrameHeader = 148;   // type 0: the frame header (+0 start, +4 end, +8 count, +12; byte +32 flags:
                                           //   bit 1 the message window type, bit 3 set by the parser)
inline constexpr s32 kKeys4 = 152;         // type 4, version 4: 16-byte key rows (events.h pm::kKeys4)
inline constexpr s32 kKeys = 156;          // type 4: 60-byte key rows (events.h pm::kKeys)
inline constexpr s32 kPm3 = 160;           // PM3 data (+164 its rows; type 4 -> +168 / +172 count)
inline constexpr s32 kKeyCount = 176;      // the key rows' count (events.h pm::kKeyCount)
inline constexpr s32 kObjects = 260;       // PM2 type 21 (+264 count): attached object table ("object table set ok.")
inline constexpr s32 kRefTable = 300;      // u32[127]: a 508-byte table (class 1)
}  // namespace scene

// --- The key-row view of sub_3912F0 and its passes (both formats) ------------------------------------------------------
namespace row {
inline constexpr s32 kType = 0;            // u16 unit type
inline constexpr s32 kFrame = 2;           // u16
inline constexpr s32 kCond = 12;           // u16[4] at +12..+18 (60-byte rows): flag, value, type, bank
inline constexpr s32 kParams = 20;         // 60-byte rows (version-4 rows: +8)
inline constexpr s32 kSize = 60;
inline constexpr s32 kSize4 = 16;
}  // namespace row

// --- The custom events (sub_39E1B0; one kwln task at a time in work.kOverlayTask, priority 16, parent work.kTask) ---
// Kind = the type-41 key's byte +16. Update = the kwln update (returns -1 when done), destroy frees the file node,
// the message slot and the record (sub_386B70). Most records start {+0 state, +4 work, +8 key, +12 the H_Cdvd node,
// +16 the message slot (mt_evtMessage.c, opened by sub_39EC70 on the .bmd found in the .pak)}.
//   kind  name                         update     destroy    record  file
//    0    CustomEvent HiruSasoi        sub_398530 sub_399830  156 B  event/sys/hirusas.pak (+72 work, +76 key)
//    1    CustomEvent Basho2Sasoi      sub_3998B0 sub_399BE0   60 B  event/sys/basho2sa.pak
//    2    CustomEvent ParamUD          sub_399C40 sub_39A560   92 B  event/sys/paramud.pak
//    3    CustomEvent HolyHogo         sub_39A5C0 sub_39A840   56 B  event/sys/yakuhog.pak
//    4    HanDenwa                     sub_39A8A0 sub_39B830 2268 B  event/sys/handen.pak (RW alloc; +4 the key's u16)
//    5    CustomEvent UwakiHakkaku     sub_39B950 sub_39C090  108 B  event/sys/uwakiha.pak
//    6    CustomEvent Morau Present    sub_39C0F0 sub_39C3E0   68 B  event/sys/moraupre.pak
//    7    CustomEvent Ageru Present    sub_39C440 sub_39CD60  108 B  event/sys/agerupre.pak
//    8    CustomEvent Hiduke Message   sub_39CDC0 sub_39CFB0   56 B  event/sys/hidumes.pak
//    9    CustomEvent Card Effect      sub_39D010 sub_39D190   16 B  (the card-effect task sub_3A2090)
//   10    CustomEvent GameOver         sub_39D550 sub_39D880   64 B  event/sys/gameover.pak
//   11    CustomEvent HavePeru         sub_39D8E0 sub_39DB00   56 B  event/sys/haveperu.pak
//   12    LvupMes HavePeru             sub_39DB60 sub_39DD30   52 B  event/sys/lvup.pak
//   13    CustomEvent Perukoe          sub_39DD90 sub_39E130   68 B  event/sys/perukoe.pak
namespace ce {
inline constexpr s32 kState = 0;           // s32
inline constexpr s32 kWork = 4;            // EvtWork*
inline constexpr s32 kKey = 8;             // EvtKey*: the type-41 key (+16 kind, +20.. parameters)
inline constexpr s32 kCdNode = 12;         // H_Cdvd node of the .pak
inline constexpr s32 kMessage = 16;        // the message slot
inline constexpr u32 kTableVa = 0x7BB020u; // sub_39E1B0's jump table (14 kinds)
}  // namespace ce

// The editor's menu-action table: action(result, previous menu, work) for menus 0..47 (0 / 3 / 12 / 18..22 empty).
inline constexpr u32 kMenuActionTable = 0x69DE40u;
// The unit-type column tables of the key editor: 12-byte rows by unit type (s16 count, then column kinds).
inline constexpr u32 kColumnTable = 0x69E1A0u;
inline constexpr u32 kUnitColumnTable = 0x69E422u;

}  // namespace p3fes::game::evt2

namespace p3fes::game {


void sub_361980(EEContext& ctx);  // 0x361980 [evtEdDeleteKey]
void sub_362390(EEContext& ctx);  // 0x362390 [evtDebugSeek]
void sub_3625E0(EEContext& ctx);  // 0x3625E0 [evtDebugCameraPad]
void sub_3628F0(EEContext& ctx);  // 0x3628F0 [evtEdCameraPad]
void sub_366EA0(EEContext& ctx);  // 0x366EA0 [evtEdActNone]
void sub_366EB0(EEContext& ctx);  // 0x366EB0 [evtEdActCameraKey]
void sub_366F90(EEContext& ctx);  // 0x366F90 [evtEdActCameraMode]
void sub_3670F0(EEContext& ctx);  // 0x3670F0 [evtEdActKeyValue20]
void sub_367190(EEContext& ctx);  // 0x367190 [evtEdActKeyValue20b]
void sub_367230(EEContext& ctx);  // 0x367230 [evtEdActModelKey]
void sub_367390(EEContext& ctx);  // 0x367390 [evtEdActCondition]
void sub_367440(EEContext& ctx);  // 0x367440 [evtEdActPop]
void sub_3674B0(EEContext& ctx);  // 0x3674B0 [evtEdActPosition]
void sub_367A20(EEContext& ctx);  // 0x367A20 [evtEdActPathKey]
void sub_367CB0(EEContext& ctx);  // 0x367CB0 [evtEdActPathPaste]
void sub_367D70(EEContext& ctx);  // 0x367D70 [evtEdActKeyBytes20]
void sub_367E00(EEContext& ctx);  // 0x367E00 [evtEdActKeyMove]
void sub_367EC0(EEContext& ctx);  // 0x367EC0 [evtEdActKeyDirect]
void sub_368020(EEContext& ctx);  // 0x368020 [evtEdActKeyParams16]
void sub_3680E0(EEContext& ctx);  // 0x3680E0 [evtEdActCustomPath]
void sub_3682F0(EEContext& ctx);  // 0x3682F0 [evtEdActKeyHalves16]
void sub_3683A0(EEContext& ctx);  // 0x3683A0 [evtEdActKeyBytes20c]
void sub_368440(EEContext& ctx);  // 0x368440 [evtEdActKeyHalves16b]
void sub_3684D0(EEContext& ctx);  // 0x3684D0 [evtEdActKeyAttach]
void sub_3685C0(EEContext& ctx);  // 0x3685C0 [evtEdActKeyParams16b]
void sub_368680(EEContext& ctx);  // 0x368680 [evtEdActKeyHalves16c]
void sub_368710(EEContext& ctx);  // 0x368710 [evtEdActCameraModelKey]
void sub_3687B0(EEContext& ctx);  // 0x3687B0 [evtEdActKeyHalf20]
void sub_368830(EEContext& ctx);  // 0x368830 [evtEdActKeyParams20]
void sub_3688D0(EEContext& ctx);  // 0x3688D0 [evtEdActKeyPresent]
void sub_3689C0(EEContext& ctx);  // 0x3689C0 [evtEdActPop2]
void sub_368A30(EEContext& ctx);  // 0x368A30 [evtEdActKeyCard]
void sub_368B00(EEContext& ctx);  // 0x368B00 [evtEdActKeyColour]
void sub_368C10(EEContext& ctx);  // 0x368C10 [evtEdActKeyBytes16]
void sub_368CB0(EEContext& ctx);  // 0x368CB0 [evtEdActMessageKey]
void sub_368D70(EEContext& ctx);  // 0x368D70 [evtEdActLoadSave]
void sub_368F20(EEContext& ctx);  // 0x368F20 [evtEdActResource]
void sub_369320(EEContext& ctx);  // 0x369320 [evtEdActValue]
void sub_3698A0(EEContext& ctx);  // 0x3698A0 [evtEdActKeyFrame]
void sub_369A20(EEContext& ctx);  // 0x369A20 [evtEdActKeyMenu]
void sub_36BE10(EEContext& ctx);  // 0x36BE10 [evtEdActObjList]
void sub_36BE60(EEContext& ctx);  // 0x36BE60 [evtEdActChoice]
void sub_36CC30(EEContext& ctx);  // 0x36CC30 [evtEdActSettings]
void sub_36D5F0(EEContext& ctx);  // 0x36D5F0 [evtStepEditor]
void sub_36E2F0(EEContext& ctx);  // 0x36E2F0 [evtStepNpcReload]
void sub_36F680(EEContext& ctx);  // 0x36F680 [evtEdListCursor]
void sub_385990(EEContext& ctx);  // 0x385990 [evtEdShowCursor]
void sub_385BD0(EEContext& ctx);  // 0x385BD0 [evtEdOpenToolA]
void sub_385CD0(EEContext& ctx);  // 0x385CD0 [evtEdOpenToolB]
void sub_385E20(EEContext& ctx);  // 0x385E20 [evtEdOpenFieldPosTool]
void sub_385F00(EEContext& ctx);  // 0x385F00 [evtEdOpenFieldTool9]
void sub_385F90(EEContext& ctx);  // 0x385F90 [evtEdOpenToolC]
void sub_386060(EEContext& ctx);  // 0x386060 [evtEdOpenToolD]
void sub_386130(EEContext& ctx);  // 0x386130 [evtEdOpenToolE]
void sub_386230(EEContext& ctx);  // 0x386230 [evtEdOpenPosTool]
void sub_386310(EEContext& ctx);  // 0x386310 [evtEdOpenToolF]
void sub_3863C0(EEContext& ctx);  // 0x3863C0 [evtEdToolSelection]
void sub_386430(EEContext& ctx);  // 0x386430 [evtEdOpenModelTool]
void sub_3865F0(EEContext& ctx);  // 0x3865F0 [evtEdOpenToolSettings10]
void sub_386680(EEContext& ctx);  // 0x386680 [evtEdOpenTool4]
void sub_386780(EEContext& ctx);  // 0x386780 [evtEdOpenTool3a]
void sub_386860(EEContext& ctx);  // 0x386860 [evtEdOpenTool3b]
void sub_386940(EEContext& ctx);  // 0x386940 [evtEdOpenToolIntFloat]
void sub_386A00(EEContext& ctx);  // 0x386A00 [evtEdOpenToolSettings13]
void sub_386D50(EEContext& ctx);  // 0x386D50 [evtDrawMemoryTotal]
void sub_386E50(EEContext& ctx);  // 0x386E50 [evtDrawSceneModels]
void sub_386F70(EEContext& ctx);  // 0x386F70 [evtDrawQuadA]
void sub_3877C0(EEContext& ctx);  // 0x3877C0 [evtDrawQuadB]
void sub_388000(EEContext& ctx);  // 0x388000 [evtDrawQuadC]
void sub_388A40(EEContext& ctx);  // 0x388A40 [evtDrawFrameQuad]
void sub_388DF0(EEContext& ctx);  // 0x388DF0 [evtRandomJumpPick]
void sub_3890E0(EEContext& ctx);  // 0x3890E0 [evtBackupResources]
void sub_3897F0(EEContext& ctx);  // 0x3897F0 [evtRestoreResources]
void sub_389B50(EEContext& ctx);  // 0x389B50 [evtEdCopyUnitKeys]
void sub_389D80(EEContext& ctx);  // 0x389D80 [evtEdPasteUnitKeys]
void sub_38A260(EEContext& ctx);  // 0x38A260 [evtEdPrintf]
void sub_38A7C0(EEContext& ctx);  // 0x38A7C0 [evtEdCameraOffset]
void sub_38A920(EEContext& ctx);  // 0x38A920 [evtEdBackupModel]
void sub_38AB00(EEContext& ctx);  // 0x38AB00 [evtEdBackupModels]
void sub_38AF70(EEContext& ctx);  // 0x38AF70 [evtEdRestoreModel]
void sub_38B140(EEContext& ctx);  // 0x38B140 [evtEdRestoreModels]
void sub_38B2C0(EEContext& ctx);  // 0x38B2C0 [evtEdApplyModelOffset]
void sub_38B550(EEContext& ctx);  // 0x38B550 [evtEdApplyModelOffsets]
void sub_38B600(EEContext& ctx);  // 0x38B600 [evtEdTransformRow]
void sub_38B6E0(EEContext& ctx);  // 0x38B6E0 [evtEdShiftFrames]
void sub_38B960(EEContext& ctx);  // 0x38B960 [evtEdShiftFrameParams]
void sub_38BC70(EEContext& ctx);  // 0x38BC70 [evtEdShiftJumpTargets]
void sub_38C540(EEContext& ctx);  // 0x38C540 [evtCameraKeyAt]
void sub_38C830(EEContext& ctx);  // 0x38C830 [evtApplyMessageCutFlags]
void sub_38DAD0(EEContext& ctx);  // 0x38DAD0 [evtSaveUnits]
void sub_38E660(EEContext& ctx);  // 0x38E660 [evtSaveFieldObjects]
void sub_38E860(EEContext& ctx);  // 0x38E860 [evtSaveEvent]
void sub_3902C0(EEContext& ctx);  // 0x3902C0 [evtBuildEffectUnits]
void sub_3905F0(EEContext& ctx);  // 0x3905F0 [evtBuildP3EffectUnit]
void sub_390920(EEContext& ctx);  // 0x390920 [evtBuildCustomEventUnit]
void sub_390C90(EEContext& ctx);  // 0x390C90 [evtBuildVisibilityUnit]
void sub_390EF0(EEContext& ctx);  // 0x390EF0 [evtLoadFieldObjectModel]
void sub_391080(EEContext& ctx);  // 0x391080 [evtBuildFieldObjectUnits]
void sub_3912F0(EEContext& ctx);  // 0x3912F0 [evtSetGameData]
void sub_3942F0(EEContext& ctx);  // 0x3942F0 [pmSceneParse]
void sub_395950(EEContext& ctx);  // 0x395950 [evtDrawPolygonMovie]
void sub_395E20(EEContext& ctx);  // 0x395E20 [evtDrawPolygonMovieDebug]
void sub_398530(EEContext& ctx);  // 0x398530 [ceHiruSasoiUpdate]
void sub_399830(EEContext& ctx);  // 0x399830 [ceHiruSasoiDestroy]
void sub_3998B0(EEContext& ctx);  // 0x3998B0 [ceBasho2SasoiUpdate]
void sub_399BE0(EEContext& ctx);  // 0x399BE0 [ceBasho2SasoiDestroy]
void sub_399C40(EEContext& ctx);  // 0x399C40 [ceParamUpUpdate]
void sub_39A560(EEContext& ctx);  // 0x39A560 [ceParamUpDestroy]
void sub_39A5C0(EEContext& ctx);  // 0x39A5C0 [ceHolyHogoUpdate]
void sub_39A840(EEContext& ctx);  // 0x39A840 [ceHolyHogoDestroy]
void sub_39A8A0(EEContext& ctx);  // 0x39A8A0 [ceHanDenwaUpdate]
void sub_39B830(EEContext& ctx);  // 0x39B830 [ceHanDenwaDestroy]
void sub_39B8B0(EEContext& ctx);  // 0x39B8B0 [ceCreateHanDenwaTask]
void sub_39B950(EEContext& ctx);  // 0x39B950 [ceUwakiHakkakuUpdate]
void sub_39C090(EEContext& ctx);  // 0x39C090 [ceUwakiHakkakuDestroy]
void sub_39C0F0(EEContext& ctx);  // 0x39C0F0 [ceMorauPresentUpdate]
void sub_39C3E0(EEContext& ctx);  // 0x39C3E0 [ceMorauPresentDestroy]
void sub_39C440(EEContext& ctx);  // 0x39C440 [ceAgeruPresentUpdate]
void sub_39CD60(EEContext& ctx);  // 0x39CD60 [ceAgeruPresentDestroy]
void sub_39CDC0(EEContext& ctx);  // 0x39CDC0 [ceHidukeMessageUpdate]
void sub_39CFB0(EEContext& ctx);  // 0x39CFB0 [ceHidukeMessageDestroy]
void sub_39D010(EEContext& ctx);  // 0x39D010 [ceCardEffectUpdate]
void sub_39D190(EEContext& ctx);  // 0x39D190 [ceCardEffectDestroy]
void sub_39D1C0(EEContext& ctx);  // 0x39D1C0 [ceGameOverDraw]
void sub_39D550(EEContext& ctx);  // 0x39D550 [ceGameOverUpdate]
void sub_39D880(EEContext& ctx);  // 0x39D880 [ceGameOverDestroy]
void sub_39D8E0(EEContext& ctx);  // 0x39D8E0 [ceHavePersonaUpdate]
void sub_39DB00(EEContext& ctx);  // 0x39DB00 [ceHavePersonaDestroy]
void sub_39DB60(EEContext& ctx);  // 0x39DB60 [ceLvupHavePersonaUpdate]
void sub_39DD30(EEContext& ctx);  // 0x39DD30 [ceLvupHavePersonaDestroy]
void sub_39DD90(EEContext& ctx);  // 0x39DD90 [cePersonaVoiceUpdate]
void sub_39E130(EEContext& ctx);  // 0x39E130 [cePersonaVoiceDestroy]
void sub_39E1B0(EEContext& ctx);  // 0x39E1B0 [evtStartCustomEvent]
void sub_39F850(EEContext& ctx);  // 0x39F850 [ceCardEffectLoadTextures]
void sub_39F950(EEContext& ctx);  // 0x39F950 [ceCardEffectSaveModels]
void sub_39FB10(EEContext& ctx);  // 0x39FB10 [ceCardEffectHideModels]
void sub_39FBD0(EEContext& ctx);  // 0x39FBD0 [ceCardEffectDrawCard]
void sub_39FFC0(EEContext& ctx);  // 0x39FFC0 [ceCardEffectDrawGlow]

}  // namespace p3fes::game
