// Menu / UI layer 3 (slice ui3), hand-decompiled from SLUS_216.21 (docs/ANALYSIS/20_menu_ui.md sections 2-3): the camp
// (pause) menu -- its root state machine H_Camp_UpdateDrawTask, the main list H_Camp_UpdateRootDrawTask and the list's
// open / close helpers, the two side-portrait ("kani") tasks' screen switches, the pose / panel draw dispatchers of the
// status, persona, social-link and item screens, the small work-record accessors of the screens and of the script
// commands that open them -- and the date / time HUD: the HUD slide H_DayPartsPos_UpdateTask, the HUD draw task
// H_DayPartsDraw_UpdateTask, the date setters H_DayPartsDraw_SetDate / sub_1848F0 and the calendar's small task
// accessors. Phase 5 slice `ui3`; game/src/ui/ui3.cpp, pair tests tests/game/test_ui3.cpp.
//
// Names: as symbols/functions.json gives them now. The `sub_<addr>` rows carry a proposed name in brackets (ours, from
// the instructions, the callers and the task / file strings; not in any delta). Globals addressed through $gp are given
// as absolute addresses ($gp = 0x7D2CF0, crt0) with their gp offset.
//
// Every function here is register-faithful at each check point, call and return (docs/PHASE5_AGENT_BRIEF.md, the
// wave-6 / wave-7 lessons): the prologue spills are written to the guest stack, $s / $ra and every scratch register
// the original writes hold the original's values whenever a callee, a check point or the caller can see them, the
// indirect calls (the RW render-state device pointers of H_DayPartsDraw_UpdateTask, the camera callbacks behind
// RwCameraBegin/EndUpdate) run inside the original frame with the original $ra, and the floating-point steps run
// through the runtime's EE FPU operations in the compiled order.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace ui3 {
// --- camp globals (h_camp.c; $gp-relative words) -----------------------------------------------------------------
inline constexpr u32 kCampCursor = 0x7CDF44u;       // gp-19884: the main list's remembered cursor (the last screen opened)
inline constexpr u32 kCampSetupTask = 0x7CDF48u;    // gp-19880: H_Camp_CreateCampSprSetupFileTask's task (state 3 = loaded)
inline constexpr u32 kCampHighlight = 0x7CDF4Cu;    // gp-19876: the list highlight record (its y at +800)
inline constexpr u32 kCampFlashTask = 0x7CDF50u;    // gp-19872: the flash-control task (copy of the root work +44)
inline constexpr u32 kCampPcKani = 0x7CDF54u;       // gp-19868: the protagonist side-portrait task (sub_122660)
inline constexpr u32 kCampPersonaKani = 0x7CDF58u;  // gp-19864: the persona side-portrait task (sub_123000)
inline constexpr u32 kCampRootTask = 0x7CDF5Cu;     // gp-19860: the main list task (H_Camp_CreateRootDrawTask)
inline constexpr u32 kScreenTaskA = 0x7CDF84u;      // gp-19820: a camp screen task opened by a script command (sub_168040 / 168100)
inline constexpr u32 kScreenTaskB = 0x7CDF80u;      // gp-19824: the same for sub_169330
inline constexpr u32 kClndTaskA = 0x7CE000u;        // gp-19696: a calendar task polled by sub_1885F0
inline constexpr u32 kClndTaskB = 0x7CE004u;        // gp-19692: polled by sub_188BE0
inline constexpr u32 kCampSlotTable = 0x833B70u;    // u32[14]: cleared at boot (kwlnInitMain) and by the event-menu code
inline constexpr u32 kCampSlotCount = 14u;

// --- H_Camp_UpdateDrawTask's work (the "H_CampDraw" task) --------------------------------------------------------
inline constexpr u32 kCampState = 0;        // u32: the 21-state machine (jump table 0x7B5420)
inline constexpr u32 kCampEquipTask = 4;    // u32: the Equip / Status screen task
inline constexpr u32 kCampScreenTask = 12;  // u32: the Persona / S.Link / System / Item / Skill screen task
inline constexpr u32 kCampFlash = 44;       // u32: the flash-control task (sub_11F1B0)
inline constexpr u32 kCampReturned = 56;    // u32: 1 = back from a screen that sets it
inline constexpr u32 kCampReopen = 60;      // u32: 1 = the main list exists (state 2 reopens it)
inline constexpr u32 kCampJumpTable = 0x7B5420u;

// --- H_Camp_UpdateRootDrawTask's work (the "H_CampRootDraw" task) ------------------------------------------------
inline constexpr u32 kRootState = 0;        // u32: the 11-state machine (jump table 0x7B5480)
inline constexpr u32 kRootFrames = 4;       // u32: animation frame counter
inline constexpr u32 kRootOpenMode = 8;     // u32: 0 = slide in (sub_11C550), 1 = fade in (sub_11CC80)
inline constexpr u32 kRootSelection = 12;   // u32: -1 none yet, -2 cancelled, else the chosen index
inline constexpr u32 kRootCursor = 16;      // u32: 0..6 (Skill, Item, Persona, Equip, Status, S.Link, System)
inline constexpr u32 kRootMoveFlash = 20;   // u32: 5 after every cursor move (the highlight flash)
inline constexpr u32 kRootOpenTimer = 32;   // u32: 200 when the open animation starts
inline constexpr u32 kRootMoved = 28;       // u32: 1 after a cursor move
inline constexpr u32 kRootFlash = 36;       // u32: the flash-control task
inline constexpr u32 kRootInput = 40;       // u32: input enabled (cleared by a move, re-armed by the draw)
inline constexpr u32 kRootJumpTable = 0x7B5480u;
inline constexpr u32 kRootCursorLast = 6;
inline constexpr u32 kRootSocialLink = 5;   // skipped when sub_17D800() (The Answer: no social links)

// --- pad words (20_menu_ui.md section 4.1) --------------------------------------------------------------------------
inline constexpr u32 kPadButtons = 0x7E094Cu;    // bits 0x20 cancel / 0x40 confirm of the camp list
inline constexpr u32 kPadHeld = 0x7E094Eu;       // gPadFlags
inline constexpr u32 kPadPressed = 0x7E0952u;
inline constexpr u32 kPadRepeatHeld = 0x7E0958u;
inline constexpr u32 kPadRepeat = 0x7E095Au;
inline constexpr u32 kPadUp = 0x1000u;           // toward index 0
inline constexpr u32 kPadDown = 0x4000u;         // toward index 6

// --- the side-portrait ("kani") tasks: work +0 state, +12 the screen index they show -------------------------------
inline constexpr u32 kKaniState = 0;
inline constexpr u32 kKaniScreen = 12;
inline constexpr u32 kPcKaniOuterTable = 0x7B5860u;       // sub_121DE0: 17 rows by the new screen
inline constexpr u32 kPersonaKaniOuterTable = 0x7B5A60u;  // sub_122710: 17 rows by the new screen

// --- the date / time HUD ("H_DayPartsDraw" work, 0x1A0 bytes; "H_DayPartsPos" work, 0x24 bytes) --------------------
inline constexpr u32 kHudXOffset = 0x7CDFF8u;    // gp-19704: float, the x offset every HUD draw adds
inline constexpr u32 kHudMoonFile = 0x7CDFF0u;   // gp-19712: the camp/i_moon_00.spr handle
inline constexpr u32 kHudState = 0;      // u32: the 9-state machine (jump table 0x7B6600)
inline constexpr u32 kHudEnabled = 4;    // u32: drawn while set (states >= 2 do nothing while it is 0)
inline constexpr u32 kHudVisible = 8;    // u32
inline constexpr u32 kHudSlide = 12;     // u32: 640 when a change animation starts
inline constexpr u32 kHudDirty = 20;     // u32
inline constexpr u32 kHudMonth = 24;     // s32 shown month
inline constexpr u32 kHudDay = 28;       // s32 shown day
inline constexpr u32 kHudPart = 32;      // s32 shown day part
inline constexpr u32 kHudFade = 40;      // s32: 0..60 fade counter
inline constexpr u32 kHudFrame = 44;     // s32: frame counter mod 360
inline constexpr u32 kHudOldMonth = 48, kHudOldDay = 52, kHudOldPart = 56;  // before the change
inline constexpr u32 kHudNewMonth = 64, kHudNewDay = 68, kHudNewPart = 72;  // after the change
inline constexpr u32 kHudExtra = 80;     // H_DayPartsDraw_DrawHud's out record
inline constexpr u32 kHudSprFile = 408;  // the sprite file handle
inline constexpr u32 kHudChild = 412;    // the date / time change animation task
inline constexpr u32 kHudJumpTable = 0x7B6600u;
inline constexpr s32 kHudFlagCampOpen = 0x1407;   // datSetFlag(0x1407, 1) by the camp menu's state 1
inline constexpr s32 kHudFlagHidden = 0x141D;
inline constexpr s32 kHudFlagChanging = 0x1410;   // a date / time change is pending
inline constexpr s32 kHudFlagDrawing = 0x1421;    // cleared each drawn frame, set during a change animation
inline constexpr s32 kFlagLeaveAfterItem = 0x1417;
inline constexpr s32 kFlagDateTablesHidden = 335;  // sub_1848F0: show the new date without an animation
}  // namespace ui3

// --- h_camp.c: the camp menu root and its list -----------------------------------------------------------------------
void sub_119A20(EEContext& ctx);                      // [H_Camp_ClearSlotTable] zero the 14 words at 0x833B70
void sub_119A60(EEContext& ctx);  // [register ABI] [H_Camp_GetSlot] 0x833B70[index]
void sub_119A80(EEContext& ctx);  // [register ABI] [H_Camp_SetSlot] 0x833B70[index] = value
void H_Camp_UpdateDrawTask(EEContext& ctx);  // [register ABI] 0x11A050: the 21-state camp root; 0 / -1 when closed
void H_Camp_UpdateRootDrawTask(EEContext& ctx);  // [register ABI] 0x11B420: the main list (11 states); 0 / -1 when closed
void sub_11B9B0(EEContext& ctx);  // [register ABI] [H_Camp_RootClose] close fade (sub_11D3A0), state 7, 22 frames
void sub_11BA00(EEContext& ctx);  // [register ABI] [H_Camp_RootHide] hide for a screen (sub_11D3A0), state 8, 22 frames
void sub_11BA50(EEContext& ctx);  // [register ABI] [H_Camp_RootReopen] fade back in (sub_11CC80), state 5, no selection
void sub_11E370(EEContext& ctx);  // [register ABI] [H_Camp_FlashIsDone] flash-control work +16

// --- the side-portrait tasks -----------------------------------------------------------------------------------------
void sub_121DE0(EEContext& ctx);  // [register ABI] [H_Camp_PcKaniSetScreen] pose transition by (old, new) screen; 1
void sub_122710(EEContext& ctx);  // [register ABI] [H_Camp_PersonaKaniSetScreen] the same for the persona; 1
void sub_123640(EEContext& ctx);                      // [H_Camp_PcKaniDrawPose] mode $a3: 0 sub_124370, 1 sub_124B30
void sub_124E00(EEContext& ctx);                      // [H_Camp_PersonaKaniDrawPose] mode $a3: 0 sub_125740, 1 sub_125B40
void sub_127AB0(EEContext& ctx);  // [register ABI] [state = 5]
void sub_127AD0(EEContext& ctx);  // [register ABI] [state = 7]
void sub_127AF0(EEContext& ctx);  // [register ABI] [work +28]
void sub_127FF0(EEContext& ctx);  // [register ABI] [alpha +12 = 255, state = 3]
void sub_128010(EEContext& ctx);  // [register ABI] [+16 = 0, state = 4]
void sub_128030(EEContext& ctx);  // [register ABI] [work +20]
void sub_128140(EEContext& ctx);                      // [H_Camp_StatusDrawPanel] kind $a2: 0..3 -> sub_129B30 / 12A560 / 12AC60 / 12B300

// --- persona / social-link / item screens ----------------------------------------------------------------------------
void sub_133B40(EEContext& ctx);  // [register ABI] [low byte of work +12 = value]
void sub_133B70(EEContext& ctx);  // [register ABI] [work +12]
void sub_136820(EEContext& ctx);                      // [H_Camp_ComuDrawPanel] kind $t1: 0..2 -> sub_137580 / 1380E0 / 1387B0
void sub_138E80(EEContext& ctx);                      // [H_Camp_ComuDrawCard] kind $t2: 0..1 -> sub_139FC0 / 13AFD0
void sub_13BCB0(EEContext& ctx);  // [register ABI] [H_Camp_ItemTableGet] 0x5D80E4[row * 10 + col]

// --- skill screen and the script commands that open the camp screens -------------------------------------------------
void sub_166C00(EEContext& ctx);  // [register ABI] [work +12 when state == 8, else 0]
void sub_166C30(EEContext& ctx);  // [register ABI] [state = 4]
void sub_166C50(EEContext& ctx);  // [register ABI] [state = 6]
void sub_167EF0(EEContext& ctx);  // [register ABI] [alpha +12 = 255, state = 3]
void sub_167F10(EEContext& ctx);  // [register ABI] [+16 = 0, state = 4]
void sub_167F30(EEContext& ctx);  // [register ABI] [work +20]
u64 sub_1681D0(EEContext& ctx);                       // [COMM: the gp-19820 screen task finished -> forget it, 1]
void sub_1685B0(EEContext& ctx);  // [register ABI] [work state == 2]
void sub_1685D0(EEContext& ctx);  // [register ABI] [work +8]
u64 sub_169420(EEContext& ctx);                       // [COMM: the gp-19824 screen task finished -> forget it, 1]

// --- the date / time HUD and the calendar's task accessors -----------------------------------------------------------
void H_DayPartsPos_UpdateTask(EEContext& ctx);  // [register ABI] 0x1832C0: slide the HUD x between 0 and 400 over 10 frames; 0
void H_DayPartsDraw_UpdateTask(EEContext& ctx);  // [register ABI] 0x183410: the 9-state HUD draw task; 0
void H_DayPartsDraw_DrawHud(EEContext& ctx);  // 0x1842C0: one HUD frame ($a0 task, $a1..$a3 month / day / part, $t0 fade,
                                              // $t1 frame, $t2 &extra) incl. the "Next N" full-moon countdown
void sub_1848F0(EEContext& ctx);  // [register ABI] [H_DayPartsDraw_ChangeDate] pick the change animation
void H_DayPartsDraw_SetDate(EEContext& ctx);  // [register ABI] 0x184C80: show the current date, no animation
void sub_187EA0(EEContext& ctx);  // [register ABI] [state = 3] (the field root's moon icon)
void sub_188420(EEContext& ctx);  // [register ABI] [work +4 / +8 / +12 = a, b, c]
u64 sub_188640(EEContext& ctx);                       // [0]
u64 sub_188660(EEContext& ctx);                       // [0]
u64 sub_1885F0(EEContext& ctx);                       // [COMM: the gp-19696 task finished -> forget it, 1]
u64 sub_188BE0(EEContext& ctx);                       // [COMM: the gp-19692 task finished -> forget it, 1]

}  // namespace p3fes::game
