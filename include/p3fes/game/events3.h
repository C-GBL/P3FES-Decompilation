// The event editor's menu screens (slice events3; game/src/event/events3.cpp): mt_evtMenu.c 0x36FA80-0x385520, the
// leftover debug editor of the story-event player -- the 40 menus of the menu table 0x6A0270 with their list-frame
// header and row callbacks, the key-row printer, the bust-up editor and the bezier path tool -- and five leaves they
// need. events2 (events2.h) took the editor's process step sub_36D5F0 and the action table 0x69DE40 that runs when a
// menu accepts; together they are the whole editor. No route reaches it in retail (pad bit 2 in an event, editor mode).
//
// Every body is p3fes_handgen's register-faithful body (register ABI: arguments in $a0.., the result in $v0) with its
// role written above it and the record offsets named where the base register holds that record for the whole
// function; nothing here changes what runs. Names in brackets are proposals (symbols/deltas/events3.sym); the code
// keeps the symbols/functions.json names. Records: events.h (evt::work / unit / key) and events2.h (evt2::work: the
// editor fields); this header adds what the menus read.
//
// ===== How the editor's menus work (for our own scene editor) =======================================================
// STACK: EvtWork.kMenuStack (+144) holds kMenuDepth 8-byte entries {s16 menu, s16 x, s16 y, s16}. Every frame the
//   editor step walks it and calls sub_385860(menu, level, kMenuX + x, kMenuY + y, work), which notes the level in
//   kMenuFont (+224: the text size, 100 - 10 * level) and calls 0x6A0270[menu](x, y, work). Only the top menu
//   (kMenuId, +212) takes pad input; the others just draw. A menu pushes another by writing the next entry and kMenuId
//   (stack[++depth] = {id, x, y}; kMenuId = id) after filling the edit fields below.
// DRAW: each menu calls sub_36F900 [evtEdDrawList](x, y, w, h, first row, rows, work, header cb, row cb): a frame of
//   w x h 12-pixel cells, the header callback (x, y, work) -> lines used, then the row callback (x, y, row, work) for
//   each visible row; text goes through sub_38A260 [evtEdPrintf] (colour 4 = the cursor, 5 = a cursor of an inactive
//   menu, 14 = labels, 0 = normal).
// INPUT (u16 words, the US build's logical bits): 0x7E094E pressed, 0x7E0952 pressed with auto-repeat, 0x7E094C held;
//   0x1000 up, 0x4000 down, 0x2000 right, 0x8000 left, 0x40 confirm (the screens' "RR"), 0x20 cancel ("RD"), 0x80
//   square ("RL"), 0x10 triangle, 4 / 8 L1 / R1, 1 / 2 L2 / R2, 0x100 select, 0x800 start, 0x200 / 0x400 L3 / R3.
// RESULT: 0 stay; 1 accept -> the editor step runs the menu's action 0x69DE40[menu](result, previous menu, work)
//   (events2: the key setters copy the edit fields into the key under the cursor and pop the menu); -1 back (pop);
//   other values go to the action too (the key list: -2 delete, -4 to the unit settings; lists: the row).
// EDIT FIELDS (EvtWork, evt2::work): kEdUnit (+356) the unit shown, kEdKeyIndex / kEdKeyScroll (+348 / +352) the key
//   cursor (sub_361830 returns that key), kEdValue / Min / Max (+364..+372) the integer editor, kEdValueF (+388, range
//   +392 / +396) the float editor, kEdSubChoice (+400) the row cursor of every key-parameter menu, kEdParams (+408,
//   s32[12]) the key parameters being edited, kEdCondition (+1924, u16[4]) the key's condition.
//
// ===== The menus (id: update / header / row -- title: what it edits; action = 0x69DE40[id], events2) =============
//   1: sub_37ABD0 / - / sub_37A790        settings (17 items: save / load project, start / end / total frame, move all
//                                         frames, field number + edit, PC control, comu index, def table, debug menu,
//                                         SPU sound, load voice, message type, battle blur) -> sub_36CC30
//   2: sub_37A640 / sub_37A4D0 / sub_37A560  the generic choice list (kEdChoiceTitle / Count / Items) -> sub_36BE60
//   3: sub_37A2B0 / sub_37A150 / sub_37A1E0  the file-name keyboard (8 characters at +304, extension +316)
//   4: sub_379F30 / - / sub_379C30        the unit list (picks kEdUnit) -> sub_36BE10
//   5: sub_3798F0 / sub_375F30 / sub_3797B0  the unit's key list (columns of table 0x69E1A0; rows sub_3760A0) ->
//                                         sub_369A20 (the key menu)
//   6 / 7 / 8: sub_375D70 / sub_375900 / sub_375590  frame / integer / float editors -> sub_3698A0 / sub_369320
//   9: sub_375000 / sub_374C90 / sub_374D30  the event number E<major>_<minor> to load -> sub_368D70 (load / save)
//  10: sub_374AF0 / - / sub_3747A0        the resource list of a model class -> sub_368F20
//  11: sub_373590                         the live edit of the cursor key (the bust-up editor sub_372C40) -> sub_367440
//  13: sub_371DD0 / sub_371710 / sub_371790  MESSAGE: L-flag type, message number, branch, tutorial display -> sub_368CB0
//  14: sub_372790 / sub_372260 / sub_3722D0  FLAG COMPARE: the key condition {flag / counter, value, type, bank} ->
//                                         sub_367390 (key +8 / +10 / +12 / +14)
//  15: sub_36FDA0 / - / sub_36FA80        the unit's own settings (columns of table 0x69E420: hold frames, camera
//                                         mode, path mode, index) -> sub_366EA0
//  16: sub_3709D0 / sub_370230 / sub_3702A0  MOTION CHANGE -> sub_366EB0: key +20 u32 {group, motion, loop, interp.},
//                                         +32 u16 offset, +34..+37 u8 the second motion, +38 / +40 / +42 u16
//  17: sub_3715B0 / - / sub_371350        the model pick list (disable / unit all / class 3 + 1 models) -> sub_366F90
//  23: sub_37AFC0 / sub_37ACC0 / sub_37AD30  POS CHANGE -> sub_3670F0: key +20 u32 {type, speed, target model id << 16}
//  24: sub_37B5D0 / sub_37B2E0 / sub_37B350  CONTROL CAMERA -> sub_367190: key +20 u32 {move type, model id << 16},
//                                         +24 u16 view length
//  25: sub_37BE50 / sub_37BA80 / sub_37BAF0  CHANGE ROT: rot Y / X, length (turns the model live) -> sub_367230
//  26: sub_373700                         applies the open debug list-box tool live (lights, model offset, free
//                                         camera) -> sub_3674B0
//  27: sub_37CAF0 / sub_37C2E0 / sub_37C350  DIRECT MOVE: interpolation, move type, speed, loop, ignore stop, auto
//                                         rotation -> sub_367A20
//  28: sub_37D5D0 / sub_37D4D0 / sub_37D540  BEZIER EDIT: the path 0x958700 (sub_37CFE0 adds points) -> sub_367CB0
//  29: sub_37E1B0 / sub_37DF50 / sub_37DFC0  ICON -> sub_367D70: key +21 type, +20 number
//  30: sub_37EAD0 / sub_37E3F0 / sub_37E460  KOMA (bust-up panel) -> sub_367E00: key +28 X, +30 Y, +32 type, +20
//                                         character, +22 face, +24 clothes, +26 kind, +34 table entry
//  31: sub_37F3D0 / sub_37F050 / sub_37F0C0  KUBI (head turn): move / reset, speed -> sub_367EC0
//  32: sub_37FAE0 / sub_37F5E0 / sub_37F650  RANDOM JUMP -> sub_368020: key +16..+19 u8 weights, +24..+30 u16 frames
//  33: sub_380200 / sub_37FF10 / sub_37FF80  CUSTOM EVENT: path, hero resource -> sub_3680E0
//  34: sub_3806F0 / sub_380310 / sub_380380  CONDITION JUMP: a frame per health condition -> sub_3682F0: key +16..+26 u16
//  35: sub_380D70 / sub_3809C0 / sub_380A30  ATTACH MODEL -> sub_3683A0: key +20 type, +21 bank, +22 model index, +24
//                                         attach point (u32)
//  36: sub_381280 / sub_3810A0 / sub_381110  COMU LV RANDOM JUMP -> sub_368440: key +16 / +18 u16 frames
//  37: sub_3819B0 / sub_3814D0 / sub_381540  PARAM UPDOWN: type, stat, 40 / 30 / 20 / 10 % amounts -> sub_3684D0
//  38: sub_3820E0 / sub_381BF0 / sub_381C60  COUNT JUMP: counter, three thresholds, four frames -> sub_3685C0
//  39: sub_382500 / sub_382320 / sub_382390  KYUJITU YAKUSOKU JUMP -> sub_368680: key +16 / +18 u16 frames
//  40: sub_382840 / sub_3826F0 / sub_382760  FUNCTION CURVE (6 curves of 4 values, 0x6A2AF0) -> sub_368710: camera
//                                         model key +48 u8
//  41: sub_382D60 / sub_382C10 / sub_382C80  PRESENT (receive) -> sub_3687B0: key +20 u16 the not-received frame
//  42: sub_383360 / sub_382EC0 / sub_382F30  FIELD OBJ ANIM -> sub_368830: key +20 motion, +21 loop (u8), +22
//                                         interpolation, +24 offset, +26 speed (u16)
//  43: sub_383D80 / sub_383810 / sub_383880  PRESENT AGERU (give): frames by the receiver's joy, motions, type ->
//                                         sub_3688D0
//  44: sub_384370 / sub_384060 / sub_3840D0  DEBUG MENU: comu level / counter / condition -> sub_3689C0
//  45: sub_384780 / sub_3844B0 / sub_384520  CARD EFFECT: type, hero resource, social link -> sub_368A30
//  46: sub_384D30 / sub_3849E0 / sub_384A50  ASIOTO (footsteps of a move key) -> sub_368B00: key +40 use, +41 channel,
//                                         +42 interval, +43 delay (u8)
//  47: sub_385520 / sub_3851F0 / sub_385260  SPU SE -> sub_368C10: key +16 type, +17 channel, +18 set, +19 sequence
// The key offsets are those the events2 setter tests check (test_events2.cpp); the menus fill kEdParams[i] in the
// order of their rows (the functions' comments name each row's field).
#pragma once

#include "p3fes/ee_context.h"
#include "p3fes/game/events.h"
#include "p3fes/game/events2.h"

namespace p3fes::game::evt3 {

// --- EvtWork fields the menus add (events.h / events2.h have the rest) -----------------------------------------------
namespace work {
inline constexpr s32 kFieldMajor = 60;       // s32: the settings' FIELD NO, first number (shown "(%d,%d,%d,%d)")
inline constexpr s32 kFieldMinor = 64;       // s32: second number
inline constexpr s32 kPcControl = 68;        // s8: PC CONTROL (0 / 1: the two names at 0x7CD1A8)
inline constexpr s32 kFieldArg70 = 70;       // u8: FIELD NO, third number
inline constexpr s32 kFieldArg72 = 72;       // s16: FIELD NO, fourth number
inline constexpr s32 kEdListScroll = 264;    // s32: the debug lists' first visible row (sub_36F900's `first`, the
                                             //     scroll* of sub_36F680; events2.h calls this offset kEdListPos)
inline constexpr s32 kEdListCursor = 272;    // s32: their cursor within the window (row = scroll + cursor; events2.h:
                                             //     kEdListTop)
inline constexpr s32 kEdKbdCol = 296;       // s32: the name keyboard's column (0..10)
inline constexpr s32 kEdKbdRow = 300;        // s32: its row (0..3); also the event-number menu's row (0 / 1)
inline constexpr s32 kEdName = 304;          // char[12]: the file name being typed (8 characters)
inline constexpr s32 kEdNameExt = 316;       // char[]: its extension
inline constexpr s32 kEdUnitPos = 336;       // s32: the unit list's cursor
inline constexpr s32 kEdUnitTop = 340;       // s32: its scroll (unit = top + pos)
inline constexpr s32 kEdValueFMin = 392;     // f32: kEdValueF's range
inline constexpr s32 kEdValueFMax = 396;     // f32
inline constexpr s32 kParam0 = 408;          // s32 kParam0..kParam11 = kEdParams[0..11] (events2.h kEdParams)
inline constexpr s32 kParam1 = 412;
inline constexpr s32 kParam2 = 416;
inline constexpr s32 kParam3 = 420;
inline constexpr s32 kParam4 = 424;
inline constexpr s32 kParam5 = 428;
inline constexpr s32 kParam6 = 432;
inline constexpr s32 kParam7 = 436;
inline constexpr s32 kParam8 = 440;
inline constexpr s32 kParam9 = 444;
inline constexpr s32 kParam10 = 448;
inline constexpr s32 kParam11 = 452;
inline constexpr s32 kEdToolModel = 528;     // model*: the model the list-box tool of kind 4 moves (sub_373700)
inline constexpr s32 kEdMsgCursor = 532;     // s32: MESSAGE menu row (0..3)
inline constexpr s32 kEdCondCursor = 536;    // s32: FLAG COMPARE menu row (0..3)
inline constexpr s32 kEdMotionCursor = 540;  // s32: MOTION CHANGE menu row (0..11)
inline constexpr s32 kEdPosCursor = 544;     // s32: POS CHANGE menu row (0..2)
inline constexpr s32 kEdCamCursor = 552;     // s32: CONTROL CAMERA menu row (0..2)
inline constexpr s32 kEdRotSave = 556;       // f32[3]: the model rotation CHANGE ROT restores on cancel
inline constexpr s32 kEdRotModel = 568;      // model*: the model CHANGE ROT turns (+4 position, +16 rotation)
inline constexpr s32 kEdMotionModel = 572;   // model*: the model MOTION CHANGE edits (+296 its animation set)
inline constexpr s32 kEdSpriteCursor = 628;  // s32: the bust-up editor's field (0..8, sub_372C40)
inline constexpr s32 kEdColumnName = 636;    // char*: the key list's free column title (kind 21)
inline constexpr s32 kEdColumnNameWidth = 640;  // s32: its width in cells
inline constexpr s32 kEdFocusUnit = 1920;    // EvtUnit*: the unit the unit list last showed
inline constexpr s32 kEdCurve = 2124;        // f32[4]: the FUNCTION CURVE being shaped
inline constexpr s32 kEdPreviewColour = 2140;// u8[4]: the previewed class-10 resource's colour (sub_318B00)
inline constexpr s32 kEdPreview10 = 2144;    // handle: the class-10 resource previewed by the resource list
inline constexpr s32 kEdPreview11 = 2148;    // handle: the class-11 (effect) resource previewed
}  // namespace work

// --- EvtUnit fields the column menus use -------------------------------------------------------------------------------
namespace unit {
inline constexpr s32 kSetting = 34;          // s8: the unit's setting (events.h kCamMode for cameras; the path mode
                                             //     ZETTAI / SOUTAI or an index for other types: table 0x69E420's kind)
inline constexpr s32 kSettingId = 36;        // u16: camera mode >= 3: the followed model (events.h kCamTarget)
inline constexpr s32 kEditing = 52;          // s32: cleared when the bust-up editor ends (sub_372C40)
}  // namespace unit

// --- one menu-stack entry (EvtWork.kMenuStack + 8 * level) ------------------------------------------------------------
namespace stack {
inline constexpr s32 kMenu = 0;              // s16: the menu id (index into 0x6A0270 / 0x69DE40, < 48)
inline constexpr s32 kX = 2;                 // s16: the draw position, added to kMenuX / kMenuY (12-pixel cells)
inline constexpr s32 kY = 4;                 // s16
inline constexpr s32 kSize = 8;
}  // namespace stack

inline constexpr u32 kMenuTable = 0x6A0270u;     // menu(x, y, work) for ids 0..47 (0 / 12 / 18..22 empty)
inline constexpr u32 kSettingsLabels = 0x69F900u;// char*[17]: menu 1's items
inline constexpr u32 kCurveTable = 0x6A2AF0u;    // f32[6][4]: the function curves (sub_3B55B0 / sub_3B55D0)
inline constexpr u32 kBezierPath = 0x958700u;    // the bezier tool's path (u8 count at +1, 12-byte points from +4)
inline constexpr u32 kEventMajor = 0x7CCA68u;    // s16: menu 9's event number
inline constexpr u32 kEventMinor = 0x7CCA6Cu;    // s16
inline constexpr u32 kPadPressed = 0x7E094Eu;    // u16 (gPadFlags)
inline constexpr u32 kPadRepeat = 0x7E0952u;     // u16: pressed, with auto-repeat
inline constexpr u32 kPadHeld = 0x7E094Cu;       // u16

}  // namespace p3fes::game::evt3

namespace p3fes::game {

void sub_1A4330(EEContext& ctx);  // 0x1A4330 [dbgListBoxFindItem]
void sub_350040(EEContext& ctx);  // 0x350040 [fxCopyWord100]
void sub_3B5460(EEContext& ctx);  // 0x3B5460 [mdlLastOfClass]
void sub_3B55D0(EEContext& ctx);  // 0x3B55D0 [funcCurveSet]
void sub_3B5DA0(EEContext& ctx);  // 0x3B5DA0 [mdlSceneLastOfClass]
void sub_36FA80(EEContext& ctx);  // 0x36FA80 [evtMenuUnitColumnsRow]
void sub_36FDA0(EEContext& ctx);  // 0x36FDA0 [evtMenuUnitColumns]
void sub_370230(EEContext& ctx);  // 0x370230 [evtMenuMotionTitle]
void sub_3702A0(EEContext& ctx);  // 0x3702A0 [evtMenuMotionRow]
void sub_3709D0(EEContext& ctx);  // 0x3709D0 [evtMenuMotion]
void sub_371350(EEContext& ctx);  // 0x371350 [evtMenuModelPickRow]
void sub_3715B0(EEContext& ctx);  // 0x3715B0 [evtMenuModelPick]
void sub_371710(EEContext& ctx);  // 0x371710 [evtMenuMessageTitle]
void sub_371790(EEContext& ctx);  // 0x371790 [evtMenuMessageRow]
void sub_371DD0(EEContext& ctx);  // 0x371DD0 [evtMenuMessage]
void sub_372260(EEContext& ctx);  // 0x372260 [evtMenuConditionTitle]
void sub_3722D0(EEContext& ctx);  // 0x3722D0 [evtMenuConditionRow]
void sub_372790(EEContext& ctx);  // 0x372790 [evtMenuCondition]
void sub_372C40(EEContext& ctx);  // 0x372C40 [evtEdSpriteKeyEdit]
void sub_373590(EEContext& ctx);  // 0x373590 [evtMenuKeyLiveEdit]
void sub_373700(EEContext& ctx);  // 0x373700 [evtMenuToolApply]
void sub_3747A0(EEContext& ctx);  // 0x3747A0 [evtMenuResourceRow]
void sub_374AF0(EEContext& ctx);  // 0x374AF0 [evtMenuResourceList]
void sub_374C90(EEContext& ctx);  // 0x374C90 [evtMenuEventNumberTitle]
void sub_374D30(EEContext& ctx);  // 0x374D30 [evtMenuEventNumberRow]
void sub_375000(EEContext& ctx);  // 0x375000 [evtMenuEventNumber]
void sub_375350(EEContext& ctx);  // 0x375350 [evtMenuFloatValueTitle]
void sub_3753C0(EEContext& ctx);  // 0x3753C0 [evtMenuFloatValueRow]
void sub_375590(EEContext& ctx);  // 0x375590 [evtMenuFloatValue]
void sub_3756E0(EEContext& ctx);  // 0x3756E0 [evtMenuIntValueTitle]
void sub_375750(EEContext& ctx);  // 0x375750 [evtMenuIntValueRow]
void sub_375900(EEContext& ctx);  // 0x375900 [evtMenuIntValue]
void sub_375A40(EEContext& ctx);  // 0x375A40 [evtMenuFrameValueTitle]
void sub_375AB0(EEContext& ctx);  // 0x375AB0 [evtMenuFrameValueRow]
void sub_375D70(EEContext& ctx);  // 0x375D70 [evtMenuFrameValue]
void sub_375F30(EEContext& ctx);  // 0x375F30 [evtMenuKeyListHeader]
void sub_3760A0(EEContext& ctx);  // 0x3760A0 [evtEdDrawKeyRow]
void sub_3797B0(EEContext& ctx);  // 0x3797B0 [evtMenuKeyListRow]
void sub_3798F0(EEContext& ctx);  // 0x3798F0 [evtMenuKeyList]
void sub_379C30(EEContext& ctx);  // 0x379C30 [evtMenuUnitListRow]
void sub_379F30(EEContext& ctx);  // 0x379F30 [evtMenuUnitList]
void sub_37A150(EEContext& ctx);  // 0x37A150 [evtMenuNameEntryTitle]
void sub_37A1E0(EEContext& ctx);  // 0x37A1E0 [evtMenuNameEntryRow]
void sub_37A2B0(EEContext& ctx);  // 0x37A2B0 [evtMenuNameEntry]
void sub_37A4D0(EEContext& ctx);  // 0x37A4D0 [evtMenuChoiceTitle]
void sub_37A560(EEContext& ctx);  // 0x37A560 [evtMenuChoiceRow]
void sub_37A640(EEContext& ctx);  // 0x37A640 [evtMenuChoice]
void sub_37A790(EEContext& ctx);  // 0x37A790 [evtMenuSettingsRow]
void sub_37ABD0(EEContext& ctx);  // 0x37ABD0 [evtMenuSettings]
void sub_37ACC0(EEContext& ctx);  // 0x37ACC0 [evtMenuPosChangeTitle]
void sub_37AD30(EEContext& ctx);  // 0x37AD30 [evtMenuPosChangeRow]
void sub_37AFC0(EEContext& ctx);  // 0x37AFC0 [evtMenuPosChange]
void sub_37B2E0(EEContext& ctx);  // 0x37B2E0 [evtMenuControlCameraTitle]
void sub_37B350(EEContext& ctx);  // 0x37B350 [evtMenuControlCameraRow]
void sub_37B5D0(EEContext& ctx);  // 0x37B5D0 [evtMenuControlCamera]
void sub_37BA80(EEContext& ctx);  // 0x37BA80 [evtMenuRotChangeTitle]
void sub_37BAF0(EEContext& ctx);  // 0x37BAF0 [evtMenuRotChangeRow]
void sub_37BE50(EEContext& ctx);  // 0x37BE50 [evtMenuRotChange]
void sub_37C2E0(EEContext& ctx);  // 0x37C2E0 [evtMenuDirectMoveTitle]
void sub_37C350(EEContext& ctx);  // 0x37C350 [evtMenuDirectMoveRow]
void sub_37CAF0(EEContext& ctx);  // 0x37CAF0 [evtMenuDirectMove]
void sub_37CFE0(EEContext& ctx);  // 0x37CFE0 [evtEdBezierAddPoint]
void sub_37D4D0(EEContext& ctx);  // 0x37D4D0 [evtMenuBezierTitle]
void sub_37D540(EEContext& ctx);  // 0x37D540 [evtMenuBezierRow]
void sub_37D5D0(EEContext& ctx);  // 0x37D5D0 [evtMenuBezier]
void sub_37DF50(EEContext& ctx);  // 0x37DF50 [evtMenuIconTitle]
void sub_37DFC0(EEContext& ctx);  // 0x37DFC0 [evtMenuIconRow]
void sub_37E1B0(EEContext& ctx);  // 0x37E1B0 [evtMenuIcon]
void sub_37E3F0(EEContext& ctx);  // 0x37E3F0 [evtMenuKomaTitle]
void sub_37E460(EEContext& ctx);  // 0x37E460 [evtMenuKomaRow]
void sub_37EAD0(EEContext& ctx);  // 0x37EAD0 [evtMenuKoma]
void sub_37F050(EEContext& ctx);  // 0x37F050 [evtMenuKubiTitle]
void sub_37F0C0(EEContext& ctx);  // 0x37F0C0 [evtMenuKubiRow]
void sub_37F3D0(EEContext& ctx);  // 0x37F3D0 [evtMenuKubi]
void sub_37F5E0(EEContext& ctx);  // 0x37F5E0 [evtMenuRandomJumpTitle]
void sub_37F650(EEContext& ctx);  // 0x37F650 [evtMenuRandomJumpRow]
void sub_37FAE0(EEContext& ctx);  // 0x37FAE0 [evtMenuRandomJump]
void sub_37FF10(EEContext& ctx);  // 0x37FF10 [evtMenuCustomEventTitle]
void sub_37FF80(EEContext& ctx);  // 0x37FF80 [evtMenuCustomEventRow]
void sub_380200(EEContext& ctx);  // 0x380200 [evtMenuCustomEvent]
void sub_380310(EEContext& ctx);  // 0x380310 [evtMenuConditionJumpTitle]
void sub_380380(EEContext& ctx);  // 0x380380 [evtMenuConditionJumpRow]
void sub_3806F0(EEContext& ctx);  // 0x3806F0 [evtMenuConditionJump]
void sub_3809C0(EEContext& ctx);  // 0x3809C0 [evtMenuAttachModelTitle]
void sub_380A30(EEContext& ctx);  // 0x380A30 [evtMenuAttachModelRow]
void sub_380D70(EEContext& ctx);  // 0x380D70 [evtMenuAttachModel]
void sub_3810A0(EEContext& ctx);  // 0x3810A0 [evtMenuComuLvJumpTitle]
void sub_381110(EEContext& ctx);  // 0x381110 [evtMenuComuLvJumpRow]
void sub_381280(EEContext& ctx);  // 0x381280 [evtMenuComuLvJump]
void sub_3814D0(EEContext& ctx);  // 0x3814D0 [evtMenuParamUpDownTitle]
void sub_381540(EEContext& ctx);  // 0x381540 [evtMenuParamUpDownRow]
void sub_3819B0(EEContext& ctx);  // 0x3819B0 [evtMenuParamUpDown]
void sub_381BF0(EEContext& ctx);  // 0x381BF0 [evtMenuCountJumpTitle]
void sub_381C60(EEContext& ctx);  // 0x381C60 [evtMenuCountJumpRow]
void sub_3820E0(EEContext& ctx);  // 0x3820E0 [evtMenuCountJump]
void sub_382320(EEContext& ctx);  // 0x382320 [evtMenuHolidayJumpTitle]
void sub_382390(EEContext& ctx);  // 0x382390 [evtMenuHolidayJumpRow]
void sub_382500(EEContext& ctx);  // 0x382500 [evtMenuHolidayJump]
void sub_3826F0(EEContext& ctx);  // 0x3826F0 [evtMenuFuncCurveTitle]
void sub_382760(EEContext& ctx);  // 0x382760 [evtMenuFuncCurveRow]
void sub_382840(EEContext& ctx);  // 0x382840 [evtMenuFuncCurve]
void sub_382C10(EEContext& ctx);  // 0x382C10 [evtMenuPresentTitle]
void sub_382C80(EEContext& ctx);  // 0x382C80 [evtMenuPresentRow]
void sub_382D60(EEContext& ctx);  // 0x382D60 [evtMenuPresent]
void sub_382EC0(EEContext& ctx);  // 0x382EC0 [evtMenuFieldObjAnimTitle]
void sub_382F30(EEContext& ctx);  // 0x382F30 [evtMenuFieldObjAnimRow]
void sub_383360(EEContext& ctx);  // 0x383360 [evtMenuFieldObjAnim]
void sub_383810(EEContext& ctx);  // 0x383810 [evtMenuPresentGiveTitle]
void sub_383880(EEContext& ctx);  // 0x383880 [evtMenuPresentGiveRow]
void sub_383D80(EEContext& ctx);  // 0x383D80 [evtMenuPresentGive]
void sub_384060(EEContext& ctx);  // 0x384060 [evtMenuDebugTitle]
void sub_3840D0(EEContext& ctx);  // 0x3840D0 [evtMenuDebugRow]
void sub_384370(EEContext& ctx);  // 0x384370 [evtMenuDebug]
void sub_3844B0(EEContext& ctx);  // 0x3844B0 [evtMenuCardEffectTitle]
void sub_384520(EEContext& ctx);  // 0x384520 [evtMenuCardEffectRow]
void sub_384780(EEContext& ctx);  // 0x384780 [evtMenuCardEffect]
void sub_3849E0(EEContext& ctx);  // 0x3849E0 [evtMenuFootstepTitle]
void sub_384A50(EEContext& ctx);  // 0x384A50 [evtMenuFootstepRow]
void sub_384D30(EEContext& ctx);  // 0x384D30 [evtMenuFootstep]
void sub_3851F0(EEContext& ctx);  // 0x3851F0 [evtMenuSpuSeTitle]
void sub_385260(EEContext& ctx);  // 0x385260 [evtMenuSpuSeRow]
void sub_385520(EEContext& ctx);  // 0x385520 [evtMenuSpuSe]

}  // namespace p3fes::game
