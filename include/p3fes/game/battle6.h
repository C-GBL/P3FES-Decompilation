// The battle code, sixth pass (slice battle6; docs/ANALYSIS/21_battle.md): the still-recompiled functions of
// 0x240000-0x28FFFF, under the relaxed callee rule (a still-recompiled callee is reached through its gen:: entry point).
// Reach first: a first-call counter on the six replay routes (dorm, m1, battle, fusion, shop, climb); the reached
// functions, then their unreached siblings in the same source files. The bodies come from p3fes_handgen (register ABI:
// arguments in $a0.., the result in $v0); five files, one per subsystem:
//   * game/src/battle/battle6_panel.cpp -- the battle panel modules: the command panel's draw and persona marks
//     (bpc_main.c), the message window (bpm_main.c), the item message (bpe_main.c), the bas work, the two battle
//     tutorials (bp_tut.c / bp_tuta.c: they run on the battle route), the bpo banner, the persona status
//     (bp_persona.c), the select marker (bp_select.c);
//   * battle6_shuffle.cpp -- Shuffle Time: its cameras (sfl_camera.c), the pose nodes (gc_pose.c: positions,
//     directions and orientations evaluated as a small dependency graph -- fixed, wandering, summed, timed moves,
//     look-at, products, spins, wobbles), the cards' update and shuffle (sfl_card.c), the card cursor (sfl_cursor.c),
//     the persona-select banner (sfl_psel2.c), the persona status (sfl_persona.c);
//   * battle6_result.cpp -- the result screen: the persona birth's resources, the item stock-over panel, the hero
//     panel, the persona panels, the persona sequence's steps (brp_seq.c), the 'persona grow' screen (brp_root.c),
//     the parameter panel (brp_param.c);
//   * battle6_staffroll.cpp -- the staff roll (ed_scroll.c / ed_res.c / ed_sr.c): oped/ed_sr.bin's script of lines,
//     captions and blank lines scrolled over the ending movie;
//   * battle6_core.cpp -- unit geometry and motion lengths, the per-frame update of every unit (fades, tints, the
//     model matrix, the status aura), the shake / hop / model packets and their callbacks, and the btlAction state
//     updates START, ANALYZE, AUTO (and its init) and SUPPORT (sBtlActionTbl rows 2 / 7 / 9 / 10). START's and START
//     HOME's inits (sub_28AA20 / sub_28B800) stay recompiled: test_battle_task's random actions recurse through
//     btlActionSetState into them without end once they are emitted.
// Names: functions.json's in code, ours in brackets in the comments (ADR-0009); the confirmed record fields go to
// tools/ours/types/deltas/battle6.json.
//
// THE BATTLE STATE A CO-OP SERVER WOULD OWN (additions to battle3.h / battle4.h / battle5.h's lists)
//   * the START state's passive regeneration (btlAction +1156: the HP 2 / 4 / 6 / 8 % and SP 3 / 5 / 7 bits of
//     datCalcGetPassiveSkillFlags, one per turn start) and the SUPPORT state's timed-effect ends (kind 9 drops HP /
//     SP to 1): battle logic, server side; the packets they queue are what clients play. AUTO picks the attack and
//     the first candidate on its own (server side too).
//   * ANALYZE waits for the player's confirm / cancel (its step 3): the server needs that choice as an input, the
//     analysis panel is client side.
//   * the per-frame unit update (sub_286540: fade alpha, tint, model matrix, the status aura's colour) and every panel,
//     tutorial, Shuffle Time, result-screen and staff-roll work are presentation (client side). Shuffle Time's card
//     shuffle and the pose nodes' wander / wobble draw from the libc rand (sub_488F30), not datCalcRand: if the card
//     order ever becomes a game rule for a shared session, the server must own that roll.
//   * gBtl +26 (the advantage) is 0 normal, 1 the party strikes first, 2 the enemies strike first (battle3.h's
//     comment corrected in this slice; checked in the editor's battle sandbox).

#pragma once

#include "p3fes/ee_context.h"
#include "p3fes/game/battle3.h"
#include "p3fes/game/battle4.h"
#include "p3fes/game/battle5.h"

namespace p3fes::game {

namespace b6 {

// --- $gp slots (offset from $gp 0x7D2CF0) ---------------------------------------------------------------------
inline constexpr s32 kGpBasWork = -18884;     // 0x7CE32C the bas work (bas_main.c)
inline constexpr s32 kGpBpTut = -18860;       // 0x7CE344 the battle tutorial (bp_tut.c)
inline constexpr s32 kGpBpTuta = -18856;      // 0x7CE348 the second battle tutorial (bp_tuta.c)
inline constexpr s32 kGpBrItem = -18816;      // 0x7CE370 the item stock-over panel (br_item.c)
inline constexpr s32 kGpBrItemTask = -18812;  // 0x7CE374 the stock-over panel's task
inline constexpr s32 kGpBrpBirth = -18880;    // 0x7CE330 the persona birth work (brp_birth.c)
inline constexpr s32 kGpBrpRes = -18876;      // 0x7CE334 the persona birth resources (brp_res.c)
inline constexpr s32 kGpBrpRoot = -18732;     // 0x7CE3C4 the 'persona grow' screen (brp_root.c)
inline constexpr s32 kGpEdHoldFrames = -26640;// 0x7CC4E0 the hold of the staff roll at the end: 60 frames (alternate episode) or 30 (0x7CC4E0)
inline constexpr s32 kGpEdRes = -18712;       // 0x7CE3D8 the staff roll resources (ed_res.c)
inline constexpr s32 kGpEdScroll = -18716;    // 0x7CE3D4 the staff roll scroll (ed_scroll.c)
inline constexpr s32 kGpEdSr = -18708;        // 0x7CE3DC the staff roll (ed_sr.c)
inline constexpr s32 kGpEdSrTask = -18704;    // 0x7CE3E0 the staff roll's 'edsr' task
inline constexpr s32 kGpGcPose = -18864;      // 0x7CE340 the pose nodes (gc_pose.c)
inline constexpr s32 kGpGlyphScaleX = -18104; // 0x7CE638 the glyph x scale / 128 of frFontBuildGlyphList (font2.h kGpScaleX; <= 0 off)
inline constexpr s32 kGpSeqHelpSkill = -26644;// 0x7CC4DC the skill the forget grid of the persona sequence points at (-1 none; 0x7CC4DC)
inline constexpr s32 kGpSflCamera = -18868;   // 0x7CE33C the Shuffle Time cameras (sfl_camera.c)
inline constexpr s32 kGpSflCard = -18844;     // 0x7CE354 the Shuffle Time cards (sfl_card.c)
inline constexpr s32 kGpSflCursor = -18832;   // 0x7CE360 the Shuffle Time card cursor (sfl_cursor.c)

// --- btlAction additions (b3::act, b4::act4, b5::act5; +1156 is b3 kAoaLeader, a per-state word: START the regeneration bits, ANALYZE its step) ---
namespace act6 {
inline constexpr s32 kNextState = 20;       // u16: the state START / START HOME / ANALYZE / ... hand over to (the
                                            //   resume state)
inline constexpr s32 kEventKind = 1180;     // u16: the event kind of state EVENT (2: the boss rules took the turn)
inline constexpr s32 kEventFn = 1184;       // fn: the event callback of state EVENT (sub_2E4310)
}  // namespace act6

// --- btlUnit additions (b3::unit, b4::unit4, b5::unit5): the fades and tints of btlUnitsUpdate -------------------------
namespace unit6 {
inline constexpr s32 kShowFlags = 0;        // u16: 0x1 / 0x2 fade the unit out, 0x4 fade it in anyway
                                            //   (btlUnitsUpdate)
inline constexpr s32 kColour2 = 52;         // u8[4]: a second RGBA tint; its alpha (+55) is the fade alpha
inline constexpr s32 kFadeAlpha = 55;       // u8: the fade alpha (0..255, steps of 28 per frame)
inline constexpr s32 kColour3 = 60;         // u8[4]: a third RGBA tint
inline constexpr s32 kFadeColour = 64;      // u8[4]: the colour fade's current RGBA
inline constexpr s32 kFadeFrom = 68;        // u8[4]: the colour fade's start (the old +64)
inline constexpr s32 kFadeTo = 72;          // u8[4]: the colour fade's target
inline constexpr s32 kFadeSteps = 76;       // u16: steps left of the colour fade (8 at the start)
inline constexpr s32 kTint = 78;            // u8[4]: the tint the model gets (+48 * +52 * +60 * +64, 1/255 each)
}  // namespace unit6

// --- the model object additions (b5::mdl) ------------------------------------------------------------------------------
namespace mdl6 {
inline constexpr s32 kRenderMode = 232;     // u32: the render state word (0x7381B opaque; copied to the five
                                            //   attachments)
inline constexpr s32 kAttach = 952;         // {u32 model, ...}[5] (12 bytes each): the attached models
inline constexpr s32 kFxSlot = 1016;        // u32: the model effect's slot (sub_31C7E0 starts it, sub_31EBE0 tests
                                            //   it)
}  // namespace mdl6

// --- the bpc work additions (b4::bpc, b5::bpc5) ------------------------------------------------------------------------
namespace bpc6 {
inline constexpr s32 kMarkStates = 27844;   // s32[3]: the three persona marks (0 off, 1 / 2 the first / second status
                                            //   of the pair)
inline constexpr s32 kMarkPlates = 27856;   // quad[3] (256 bytes each): the marks' plates (textures 59..64)
inline constexpr s32 kMarkIcons = 28624;    // quad[3]: the marks' state icons (17 / 18 of texture set 3, or 65)
}  // namespace bpc6

// --- the bas work (*kGpBasWork, bas_main.c) ----------------------------------------------------------------------------
namespace bas {
inline constexpr s32 kFlags = 0;            // u32: 0x1 open
inline constexpr s32 kArg = 4;              // u32: the value it was opened with (sub_1FE580's argument)
}  // namespace bas

// --- the persona birth work (*kGpBrpBirth, brp_birth.c) ----------------------------------------------------------------
namespace birth {
inline constexpr s32 kHeld = 4;             // u32: what is loaded: 0x2 busy, 0x4 the task, 0x8 the model, 0x10 / 0x20
                                            //   / 0x40 / 0x100 the effect objects
inline constexpr s32 kModel = 28;           // the model block (nullsub_66)
inline constexpr s32 kFxObjects = 4036;     // u32[4]: the effect objects (sub_34FCF0 releases them)
inline constexpr s32 kTask = 50528;         // u32: the birth task
}  // namespace birth

// --- the persona birth resources (*kGpBrpRes, brp_res.c) ---------------------------------------------------------------
namespace brpres {
inline constexpr s32 kLoading = 0;          // u32: 0x1 the archive loads, 0x2 the message file loads
inline constexpr s32 kLoaded = 4;           // u32: 0x1 the archive is in, 0x2 the message file, 0x4 the block +36
inline constexpr s32 kArchiveReq = 8;       // u32: the archive's H_Cdvd request
inline constexpr s32 kMessageReq = 12;      // u32: facility/msg/msg_combine.bmd's request
inline constexpr s32 kFiles = 16;           // u32[4]: the archive files 2..5 (RwMalloc copies)
inline constexpr s32 kMessages = 32;        // u32: the message file copy
inline constexpr s32 kBlock = 36;           // u32: a further RwMalloc block
}  // namespace brpres

// --- the battle panel persona status (*b5::kGpBpPersona, bp_persona.c) -------------------------------------------------
namespace bppersona {
inline constexpr s32 kFlags = 0;            // u32: 0x1 open, 0x2 a persona shown
inline constexpr s32 kStatus = 4;           // u32: the status task set (fclMisc_CreatePsStatusTasks)
inline constexpr s32 kPersona = 8;          // u16: the persona shown
}  // namespace bppersona

// --- the Shuffle Time persona status (*b5::kGpSflPersona, sfl_persona.c) -----------------------------------------------
namespace sflpersona {
inline constexpr s32 kFlags = 0;            // u32: 0x1 open, 0x2 a persona shown, 0x8 hiding
inline constexpr s32 kStatus = 4;           // u32: the status task set
inline constexpr s32 kPersona = 8;          // u16: the persona shown
inline constexpr s32 kHideFrame = 12;       // s32: frames of the hide
}  // namespace sflpersona

// --- the result screen persona panel (*b5::kGpBrPersona, br_persona.c) -------------------------------------------------
namespace brpersona {
inline constexpr s32 kStatus = 4;           // u32: the status task set
inline constexpr s32 kPersona = 8;          // u16: the persona shown
}  // namespace brpersona

// --- the result screen persona status (*b5::kGpBrpPersona, brp_persona.c) ----------------------------------------------
namespace brppersona {
inline constexpr s32 kFlags = 0;            // u32: 0x1 open, 0x2 shown, 0x4 page 16
inline constexpr s32 kStatus = 4;           // u32: the status task set
}  // namespace brppersona

// --- the battle select marker (*b5::kGpBpSelect, bp_select.c) ----------------------------------------------------------
namespace bpselect {
inline constexpr s32 kFlags = 0;            // u32: 0x1 open, 0x2 closing
inline constexpr s32 kQuad = 16;            // quad: the marker (texture 58 of set 2)
inline constexpr s32 kFrame = 272;          // s32: frames since it opened / started closing
inline constexpr s32 kPos = 276;            // f32[2]: the screen point
}  // namespace bpselect

// --- the result screen level panel (*b5::kGpBrLvPanel) -----------------------------------------------------------------
namespace lvpnl {
inline constexpr s32 kFlags = 0;            // u32: 0x8 (cleared by sub_2768C0)
}  // namespace lvpnl

// --- the battle tutorial (*kGpBpTut, bp_tut.c) -------------------------------------------------------------------------
namespace tut {
inline constexpr s32 kFlags = 0;            // u32: 0x1 open
inline constexpr s32 kPhase = 4;            // u32: 0 waiting for the first page, 1 running
inline constexpr s32 kKind = 8;             // u32: the tutorial 0..3 (seen flags 4871..4874)
inline constexpr s32 kStep = 12;            // u32: the step of phase 1 (0..7)
inline constexpr s32 kPicture = 16;         // u32: the picture task (sub_110F80)
}  // namespace tut

// --- the second battle tutorial (*kGpBpTuta, bp_tuta.c) ----------------------------------------------------------------
namespace tuta {
inline constexpr s32 kFlags = 0;            // u32: 0x1 open
inline constexpr s32 kPhase = 4;            // u32: 0 waiting, 1 running
inline constexpr s32 kStep = 8;             // u32: the step of phase 1 (0..3)
}  // namespace tuta

// --- the result screen hero panel (*b5::kGpBrHero, br_hero.c) ----------------------------------------------------------
namespace brhero {
inline constexpr s32 kFlags = 0;            // u32: 0x1 open, 0x2 the level went up
inline constexpr s32 kAcademics = 4624;     // s32: the Academics rank - 1 (its plate is texture rank)
inline constexpr s32 kCharm = 4628;         // s32: the Charm rank - 1 (plate rank + 7)
inline constexpr s32 kCourage = 4632;       // s32: the Courage rank - 1 (plate rank + 14)
inline constexpr s32 kLevel = 5664;         // s32: the hero's level
inline constexpr s32 kHp = 5668;            // s32: HP
inline constexpr s32 kMaxHp = 5672;         // s32: max HP
inline constexpr s32 kSp = 5676;            // s32: SP
inline constexpr s32 kMaxSp = 5680;         // s32: max SP
inline constexpr s32 kWord5684 = 5684;      // s32: sub_16C920(1)
inline constexpr s32 kNextExp = 5700;       // s32: the experience to the next level (99,999 at most)
inline constexpr s32 kNameLine = 11088;     // u32: the name's glyph list
inline constexpr s32 kFrame = 14688;        // s32: the frame counter (0..1050, cycling)
}  // namespace brhero

// --- the item stock-over panel (*kGpBrItem, br_item.c) -----------------------------------------------------------------
namespace britem {
inline constexpr s32 kFlags = 0;            // u32: 0x1 open, 0x2 opening
inline constexpr s32 kMode = 4;             // s32: 0 opening, 1 closing
inline constexpr s32 kTextures = 8;         // u32: the texture set
inline constexpr s32 kFrame = 12;           // s32: frames of the opening / closing
}  // namespace britem

// --- the persona-select banner (*b5::kGpSflPsel, sfl_psel2.c) ----------------------------------------------------------
namespace psel6 {
inline constexpr s32 kFlags = 0;            // u32: 0x1 open
inline constexpr s32 kMode = 4;             // s32: 0 opening, 1 closing
inline constexpr s32 kFrame = 8;            // s32: frames of the opening / closing
}  // namespace psel6

// --- the result screen parameter panel (*b5::kGpBrpParam, brp_param.c) -------------------------------------------------
namespace brpparam {
inline constexpr s32 kFlags = 0;            // u32: 0x2 a new skill is shown, 0x10 it blinks
inline constexpr s32 kStatCount = 14128;    // s32: the stat rows shown
inline constexpr s32 kWord14132 = 14132;    // s32
inline constexpr s32 kSkillCount = 14136;   // s32: the skill cells shown (of 8)
inline constexpr s32 kWord14140 = 14140;    // s32
inline constexpr s32 kBlink = 14144;        // f32: the blink phase
inline constexpr s32 kBlinkFrame = 14148;   // s32: the blink frame
inline constexpr s32 kNewSkillLine = 14672; // u32: the new skill's glyph list
}  // namespace brpparam

// --- the 'persona grow' screen (*kGpBrpRoot, brp_root.c) ---------------------------------------------------------------
namespace brproot {
inline constexpr s32 kSeq = 0;              // the persona sequence work (sub_272330)
inline constexpr s32 kFlags = 17664;        // u32: 0x1 running, 0x2 the music plays
inline constexpr s32 kTask = 17668;         // u32: the 'persona grow' task
inline constexpr s32 kDrawTask = 17672;     // u32: the 'persona grow draw' task
}  // namespace brproot

// --- the persona sequence additions (b5::brpseq) -----------------------------------------------------------------------
namespace brpseq6 {
inline constexpr s32 kSkillStep = 24;       // s32: the new-skill substep (0..5)
inline constexpr s32 kEvolveStep = 28;      // s32: the evolution substep (0..5)
inline constexpr s32 kChangeStep = 32;      // s32: the skill change substep (0 / 1)
inline constexpr s32 kShiftPersona = 128;   // u16: the persona the evolution shifts to (sub_1FB560)
inline constexpr s32 kEvolveKind = 164;     // s32: 0 a persona shift, 1 an item
inline constexpr s32 kGridColumn = 440;     // s32: the forget grid cursor's column (0..2)
inline constexpr s32 kGridRow = 444;        // s32: its row (0..3)
}  // namespace brpseq6

// --- a Shuffle Time card (sub_255440(i), sfl_card.c) -------------------------------------------------------------------
namespace card {
inline constexpr s32 kFlags = 0;            // u32: 0x8 stacked, 0x10 / 0x20 moving, 0x80 highlighted, 0x200 fading
inline constexpr s32 kQuat = 40;            // f32[4]: the orientation copied to the model
inline constexpr s32 kPos = 56;             // f32[3]: the position copied to the model
inline constexpr s32 kFadeKind = 4684;      // s32: 0 / 1 re-dirty the nodes, 2 fade out, 3 fade in
inline constexpr s32 kFadeFrame = 4688;     // s32: frames of the fade
inline constexpr s32 kFadeFrames = 4692;    // s32: its length
inline constexpr s32 kSway = 4696;          // s32: the sway frame (0..89)
inline constexpr s32 kGlow = 4700;          // s32: the point light's strength (0..256)
inline constexpr s32 kAlpha = 4704;         // s32: the card's own alpha (0..256)
}  // namespace card

// --- the staff roll script file (oped/ed_sr.bin file 0) ----------------------------------------------------------------
namespace edfile {
inline constexpr s32 kWord0 = 0;            // u32: copied to the script object +0
inline constexpr s32 kCmdOffset = 4;        // u32: the command stream's offset
inline constexpr s32 kCmdSize = 8;          // u32: its size
inline constexpr s32 kStringCount = 12;     // u32: the strings
inline constexpr s32 kLengthOffset = 16;    // u32: the offset of the string lengths (one byte each)
inline constexpr s32 kStringOffset = 20;    // u32: the string data's offset
inline constexpr s32 kStringSize = 24;      // u32: its size
}  // namespace edfile

// --- the staff roll script object (edScriptBuild) ----------------------------------------------------------------------
namespace edscript {
inline constexpr s32 kWord0 = 0;            // u32: the file's word 0
inline constexpr s32 kStringCount = 4;      // u32: the strings
inline constexpr s32 kStrings = 8;          // u32: the string table (char*[])
inline constexpr s32 kStringData = 12;      // u32: the string data
inline constexpr s32 kCommands = 16;        // u32: the command stream (u8: 0 end, 1 line, 2 caption, 3 n blank lines,
                                            //   4 half line)
}  // namespace edscript

// --- a staff roll line slot (144 bytes) --------------------------------------------------------------------------------
namespace edline {
inline constexpr s32 kFlags = 0;            // u32: 0x1 used
inline constexpr s32 kWords = 4;            // {f32 x, u32 glyph list}[16]: the words
inline constexpr s32 kWordCount = 132;      // s32: the words
inline constexpr s32 kY = 140;              // f32: the line's y
}  // namespace edline

// --- the staff roll scroll work (*kGpEdScroll, ed_scroll.c) ------------------------------------------------------------
namespace edscroll {
inline constexpr s32 kFlags = 0;            // u32: 0x1 running, 0x2 the script ended, 0x4 the last line was placed
inline constexpr s32 kLines = 4;            // line[32] (144 bytes each, edline::)
inline constexpr s32 kEndFrame = 4612;      // s32: frames of the end phase
inline constexpr s32 kStringIndex = 4616;   // s32: the next string
inline constexpr s32 kCursor = 4620;        // s32: the command cursor
inline constexpr s32 kWord4624 = 4624;      // u32: 0 at the start
inline constexpr s32 kWord4628 = 4628;      // u32: 0 at the start
inline constexpr s32 kStartY = 4632;        // f32: 448.0 at the start
inline constexpr s32 kNextY = 4636;         // f32: the next line's y
inline constexpr s32 kLastLine = 4640;      // u32: the slot of the last line
inline constexpr s32 kEndPhase = 4644;      // s32: 0 scrolling, 1 easing to the end
inline constexpr s32 kEndY0 = 4648;         // f32: the last line's y when the end phase began
inline constexpr s32 kRgba = 4652;          // u8[4]: the line colour (r, g, b, a)
}  // namespace edscroll

// --- the staff roll resource work (*kGpEdRes, ed_res.c) ----------------------------------------------------------------
namespace edres {
inline constexpr s32 kLoading = 0;          // u32: 0x1 the archive loads
inline constexpr s32 kLoaded = 4;           // u32: 0x1 loaded
inline constexpr s32 kRequest = 8;          // u32: the archive's H_Cdvd request
inline constexpr s32 kScript = 12;          // u32: the script object (edScriptBuild)
}  // namespace edres

// --- the staff roll work (*kGpEdSr, ed_sr.c; 4,696 bytes) --------------------------------------------------------------
namespace edsr {
inline constexpr s32 kFlags = 0;            // u32: 0x1 running
inline constexpr s32 kTask = 4;             // u32: the 'edsr' task
inline constexpr s32 kDrawTask = 8;         // u32: the 'edsr draw' task
inline constexpr s32 kRes = 12;             // the resource work (edres::, 16 bytes)
inline constexpr s32 kScroll = 28;          // the scroll work (edscroll::, 4,656 bytes)
inline constexpr s32 kStep = 4684;          // s32: 0 load, 1 fade in, 2 the movie and the scroll, 3 fade out
inline constexpr s32 kMovieTask = 4688;     // u32: the 'H_SfdPlay' task
inline constexpr s32 kFrame = 4692;         // s32: frames of step 2
}  // namespace edsr

// --- the Shuffle Time camera work (*kGpSflCamera, sfl_camera.c) --------------------------------------------------------
namespace sflcam {
inline constexpr s32 kFlags = 0;            // u32: 0x1 active, 0x2 a camera picked
inline constexpr s32 kHead = 4;             // u32: the first camera record
inline constexpr s32 kTail = 8;             // u32: the last camera record
inline constexpr s32 kPicked = 12;          // u16: the picked camera's id
inline constexpr s32 kRwCamera = 16;        // u32: the RW camera
}  // namespace sflcam

// --- a Shuffle Time camera record --------------------------------------------------------------------------------------
namespace sflcamrec {
inline constexpr s32 kId = 4;               // u16: the camera id
inline constexpr s32 kPrev = 8;             // u32: the previous record
inline constexpr s32 kNext = 12;            // u32: the next record
inline constexpr s32 kQuat = 16;            // f32[4]: the rotation (copied into the RW camera)
inline constexpr s32 kPos = 32;             // f32[3]: the position
inline constexpr s32 kKind = 44;            // s32: 1 the only kind
inline constexpr s32 kFollowPos = 48;       // s32: 1 the position follows the position node
inline constexpr s32 kAnchor = 52;          // u32: the anchor node (child 0 of the position node)
inline constexpr s32 kLookAtOn = 56;        // s32: 1 looks at the look-at node
inline constexpr s32 kLookAt = 60;          // u32: the look-at node
inline constexpr s32 kTime = 64;            // s32: the time (16.16 frames)
inline constexpr s32 kPosNode = 68;         // pose node (100 bytes): the position
inline constexpr s32 kRotNode = 168;        // pose node: the orientation
}  // namespace sflcamrec

// --- an RwCamera -------------------------------------------------------------------------------------------------------
namespace rwcam {
inline constexpr s32 kFrame = 4;            // u32: the camera's frame
}  // namespace rwcam

// --- the gc_pose work (*kGpGcPose, gc_pose.c) --------------------------------------------------------------------------
namespace gcpose {
inline constexpr s32 kHead = 0;             // u32: the first node
inline constexpr s32 kStack = 8;            // u32[128]: the evaluation stack
inline constexpr s32 kDepth = 520;          // s32: entries on the stack
}  // namespace gcpose

// --- a gc_pose node (the words from +36 depend on the kind and the mode) -----------------------------------------------
namespace pose {
inline constexpr s32 kNext = 4;             // u32: the next node
inline constexpr s32 kFlags = 8;            // u32: 0x1 active, 0x2 dirty
inline constexpr s32 kKind = 12;            // s32: 0 a position, 1 a direction, 2 an orientation
inline constexpr s32 kTime = 16;            // s32: the time (16.16 frames)
inline constexpr s32 kValue = 20;           // f32[3] / quaternion f32[4]: the value
inline constexpr s32 kPosMode = 32;         // s32: kind 0: 0 fixed, 1 wander, 2 sum, 3 timed move; kind 1: 1 (its
                                            //   only mode); kind 2: the quaternion's w
inline constexpr s32 kW36 = 36;             // kind 2: the orientation mode (0 fixed, 1 look-at, 2 product, 3 spin, 4
                                            //   wobble); kind 0 wander: f32[3] the start; sum: the children u32[3];
                                            //   move: the curve (0 straight, 1 arc); kind 1: the from node
inline constexpr s32 kW40 = 40;             // kind 0 move: 0x1 running; kind 1: the to node; kind 2 product: the
                                            //   children u32[3]; look-at: the two direction nodes; spin: the curve;
                                            //   wobble: f32[3] the start angles
inline constexpr s32 kW44 = 44;             // kind 0 move: the duration (16.16); kind 2 spin: 0x1 running
inline constexpr s32 kW48 = 48;             // f32[3]: kind 0 move: the acceleration / the end; wander: the spline
                                            //   point; kind 2 spin: the duration
inline constexpr s32 kW60 = 60;             // f32[3]: kind 0 move: the start velocity / the start; wander: the
                                            //   control point
inline constexpr s32 kW72 = 72;             // f32[3]: kind 0 move: the start; wander: the target
inline constexpr s32 kW84 = 84;             // kind 0 move: f32[3] the end; wander: f32 the range, +88 s32 the period
                                            //   (frames), +92 f32 the spline length, +96 f32 the scale
inline constexpr s32 kW88 = 88;             // see kW84; kind 2 wobble: f32[3] the angle ranges
inline constexpr s32 kW92 = 92;             // see kW84
inline constexpr s32 kW96 = 96;             // kind 0 wander: f32 the scale
inline constexpr s32 kW100 = 100;           // kind 2 wobble: s32 the period (frames), +104 f32 the spline length,
                                            //   +108 f32 the scale
inline constexpr s32 kW104 = 104;           // see kW100
inline constexpr s32 kW108 = 108;           // see kW100
}  // namespace pose

// --- the Shuffle Time card cursor (*kGpSflCursor, sfl_cursor.c) --------------------------------------------------------
namespace sflcur {
inline constexpr s32 kFlags = 0;            // u32: 0x1 open, 0x2 a move runs
inline constexpr s32 kFrom = 4;             // f32[3]: the move's start point
inline constexpr s32 kTo = 16;              // f32[3]: its end point
inline constexpr s32 kPos = 28;             // f32[3]: the cursor point
inline constexpr s32 kMoveFrame = 40;       // s32: frames of the move
inline constexpr s32 kPrevSel = 44;         // s32: the previous selection (drawn during a kind-1 move)
inline constexpr s32 kSel = 48;             // s32: the selected card (0..5)
inline constexpr s32 kBlink = 52;           // s32: the blink counter (0..59)
inline constexpr s32 kMarks = 64;           // mark[6] (528 bytes): +0 brightness, +4 glow (0..256), +16 / +272 the
                                            //   two quads
inline constexpr s32 kMoveKind = 3232;      // s32: 0 slide, 1 / 2 / 3 waits (3 closes)
}  // namespace sflcur

// --- a unit packet's data (kinds 258 / 273 / 275 / 276) ----------------------------------------------------------------
namespace pdunit {
inline constexpr s32 kUnit = 0;             // u32: the unit
inline constexpr s32 kArg4 = 4;             // u16: the creator's word (side + 1 for the model effect packet)
inline constexpr s32 kArg6 = 6;             // u16
inline constexpr s32 kFlags = 8;            // u16: 0x10 do not start the effect in the init
inline constexpr s32 kStarted = 12;         // s32: 1 once the effect started
}  // namespace pdunit

// --- the shake packet's data -------------------------------------------------------------------------------------------
namespace pshake {
inline constexpr s32 kUnit = 0;             // u32: the unit
inline constexpr s32 kAmp = 4;              // f32: the amplitude (decays every frame)
inline constexpr s32 kCount = 8;            // u32: frames run (the parity flips the sign)
}  // namespace pshake

// --- the hop packet's data ---------------------------------------------------------------------------------------------
namespace phop {
inline constexpr s32 kStart = 0;            // f32[3]: the start point
inline constexpr s32 kUnit = 12;            // u32: the unit
inline constexpr s32 kFrames = 16;          // u16: the length in frames
inline constexpr s32 kStep = 18;            // u16: frames run
inline constexpr s32 kT = 20;               // f32: the arc parameter (0.5 at the start)
}  // namespace phop

// --- a kwln task -------------------------------------------------------------------------------------------------------
namespace ktask {
inline constexpr s32 kWork = 60;            // u32: the task's work block
}  // namespace ktask

// --- the Shuffle Time card work (*kGpSflCard, sfl_card.c; 75,920 bytes) ------------------------------------------------
namespace sflcard {
inline constexpr s32 kFlags = 0;            // u32: 0x1 open, 0x4 / 0x8 the deal states, 0x10 dealing, 0x20 held at an
                                            //   end, 0x40 an effect runs, 0x80 / 0x100 / 0x800 / 0x1000 effect kinds,
                                            //   0x200 models loading, 0x2000 no pick sound
inline constexpr s32 kCards = 75356;        // u32: the first card (cards linked by +4036)
inline constexpr s32 kStacked = 75364;      // u32[]: the stacked cards (released last first by the shuffle)
inline constexpr s32 kCount = 75388;        // s32: the cards dealt
inline constexpr s32 kFrame = 75392;        // s32: frames open
inline constexpr s32 kStackedCount = 75396; // s32: the stacked cards
inline constexpr s32 kSel = 75692;          // s32: the selected card
inline constexpr s32 kDealFrame = 75700;    // s32: frames of the deal phase
inline constexpr s32 kDealPhase = 75704;    // s32: 0 flying in, 1 turning over
inline constexpr s32 kDealOrder = 75708;    // s32[]: each card's turn in the deal
inline constexpr s32 kRotNode = 75776;      // pose node: the orientation the switch effect gives the new card
inline constexpr s32 kEffect = 75888;       // s32: the effect (1 pick, 2 shuffle, 3 fade in, 4 fade out, 5 switch)
inline constexpr s32 kEffectStep = 75892;   // s32: the pick effect's step
inline constexpr s32 kShuffleStep = 75896;  // s32: the shuffle effect's step (0 fade out, 1 wait, 2 fade in)
inline constexpr s32 kEffectFrame = 75900;  // s32: frames of the effect step
inline constexpr s32 kFade = 75904;         // s32: the cards' fade (0..256)
inline constexpr s32 kNextSel = 75908;      // s32: the card the switch effect selects
inline constexpr s32 kDealSpacing = 75912;  // s32: frames between two cards of the deal
inline constexpr s32 kDealFrames = 75916;   // s32: the length of a card's flight
}  // namespace sflcard

}  // namespace b6

// --- panel: battle6_panel.cpp (register ABI: arguments in $a0.., the result in $v0) ----------
// 0x242C20 [biSlotSetWords] Sets a battle info slot's two words (a0 a slot of the bi work, 3,920 bytes each: b4::bi;
//   sub_1FE650): flag 0x20, +3908 = a1, +3904 = a2.
void sub_242C20(EEContext& ctx);
// 0x243150 [bpcDraw] Draws the battle panel command work (bpc_main.c, *$gp 0x7CE320; K_Assert line 151; bpRoot's draw task).
//   Takes the texture sets 2 / 1 / 5 / 3; while shown (flag 1) or sliding (0x20): the entries' draw lists (sub_245EA0)
//   unless flag 0x100, the 2D render states (RwRenderStateSet 9 / 20 / 8 / 6), then every listed entry (mode 2: one of
//   the entry flags 0x400 / 0x20 / 0x80; modes 0 / 1: its uid in the uid list, or sliding) that is not hidden (0x40):
//   the cursor highlight (texture 44, flag 1), the frame (2), the name plate (texture 55 of set 2 for the enemy panel,
//   4 otherwise), the analysis plate (8, mode 2), the gauge frame (3), the low-HP mark (69, flag 2), the enemy panel's
//   two analysis bars (61 / 57) or the party panel's HP / SP bars (1, and texture 4 of set 5); each quad drawn as two
//   triangles through the Im2D slot 0x96009C with the render state 0x7381B (additive 0x71821 for the highlight /
//   plates). With one listed unit (flag 2, not 0x80): the name line backdrop (texture 0), the plates 67 and the name
//   text (frFontDraw of +27840), the plates 66; with persona marks shown (flag 4): the three marks' plates (59..64 by
//   their states +27844..+27852) and their state icons (texture 17 / 18 of set 3, or 65).
void sub_243150(EEContext& ctx);
// 0x244E80 [bpcSetPersonaMarks] Sets the three persona marks of the battle panel command work (K_Assert line 151) from the
//   cursor unit's DatUnit (sub_1FF430 of uid +16; K_Assert 1008 / 1009: open with one listed unit): for each pair of
//   status bits -- 5 / 10, 64 / 128, 528 / 288 (sub_301CA0) -- the mark state is 1 (the first; K_Assert when both), 2
//   (the second) or 0, stored at +27844 / +27848 / +27852; then each mark's plate (textures 59 / 61 / 63, or 60 / 62 /
//   64 when off) into +27856 / +28112 / +28368 and its icon (17 / 18 of set 3, or 65) into +28624 / +28880 / +29136
//   (sub_21D3B0).
void sub_244E80(EEContext& ctx);
// 0x2459D0 [bpcEntryPrepareAnalysed] Prepares a battle panel command entry (a0) of an analysed enemy for its slide-in: clears
//   +1808 (the slide counter) and flags 0x10 / 0x20, sets 0x200.
void sub_2459D0(EEContext& ctx);
// 0x245CD0 [bpcSetEntryRelations] Sets the relation word of every listed battle panel command entry (K_Assert line 151): of
//   the entries flagged 0x80, the cursor unit's own entry gets 0, an entry whose DatUnit has the cursor unit's id
//   (DatUnit +2) gets 1, any other 2 (+2656 of the 2,624-byte entry). Takes the texture sets 2 / 1 first.
void sub_245CD0(EEContext& ctx);
// 0x248580 [bpmOpenText] Opens the battle panel message window (bpm_main.c, *$gp 0x7CE324; K_Assert line 61) with the text a0
//   / a1: closes the open one first (sub_2491F0), builds the text task (sub_3A52C0(100, 100, -1, 2, 6, a0, a1)) and
//   shows it (sub_248FC0).
void sub_248580(EEContext& ctx);
// 0x249420 [bpeShowItemMessage] Shows the item-get message of the bpe work (bpe_main.c, *$gp 0x7CE328; K_Assert lines 55 /
//   140): the message files 0 / 1 (sub_21C550), the item record (sub_30C0C0) sets its seen flag (4800 + item) and flag
//   4865; the first time (flag 4865 clear) it shows the explanation page (sub_3C94E0, the name sub_1775A0(1),
//   sub_3C9790(0), mode 0), later the short line with the two item names (sub_173220 of a1 / a2) and the count a0
//   (message 0, mode 1); stores a0..a2 at +8 / +10 / +12 and sets flag 1.
void sub_249420(EEContext& ctx);
// 0x24A6E0 [basOpen] Opens the bas work (bas_main.c, *$gp 0x7CE32C; K_Assert line 29) for a0: sub_1FE580(a0), +4 = a0, flag 1.
void sub_24A6E0(EEContext& ctx);
// 0x24A750 [basIsOpen] Nonzero while the bas work is open (flag 1; K_Assert line 29).
void sub_24A750(EEContext& ctx);
// 0x24A7A0 [basClose] Closes the bas work (clears flag 1; K_Assert line 29).
void sub_24A7A0(EEContext& ctx);
// 0x2510D0 [bpTutUpdate] Per-frame update of the battle tutorial (bp_tut.c, *$gp 0x7CE344; K_Assert line 57; bpRoot's task)
//   while open: phase 0 waits for the panel (sub_21C860) and the picture task (sub_1114B0), shows the tutorial's first
//   page (messages 0 / 5 / 11 / 16 by the tutorial kind +8, choice lists 1 / 6 / 12 / 17), step 0, phase 1. Phase 1 is
//   a step machine (+12): 0 / 1 the yes / no choices -- 'no' shows the next page (4 / 10 / 15 / 20) and goes to 2,
//   'yes' repeats (2 / 7 / 13 / 18, kind 1 ends after message 7 at step 3); 2 / 3 close the window and the picture
//   (sub_111500), 3 also the window set -> 4 / 7; 4 when the picture task ended shows the explanation (sub_3C94E0) ->
//   5; 5 closes it, shows message 8 and starts a new picture task (sub_110F80) -> 6; 6 when it is ready starts it
//   (sub_111530) -> 1; 7 when the picture task ended closes (sub_251A20) and clears flag 1.
void sub_2510D0(EEContext& ctx);
// 0x2518B0 [bpTutOpen] Opens the battle tutorial of kind a0 (K_Assert line 57): sets its seen flag 4871 + kind (0..3), the
//   message set (sub_21C7F0), starts the picture task (sub_110F80(0, 0x200040004)) into +16, phase 0, flag 1, +8 = the
//   kind.
void sub_2518B0(EEContext& ctx);
// 0x251A20 [bpTutClose] Closes the battle tutorial's windows (K_Assert line 57): sub_3C77A0, sub_21C930.
void sub_251A20(EEContext& ctx);
// 0x251A80 [bpTutaUpdate] Per-frame update of the second battle tutorial (bp_tuta.c, *$gp 0x7CE348; K_Assert line 49) while
//   open: phase 0 waits for the panel, then shows message 0 (5 for the alternate episode, sub_17D800) with choice list
//   1 -> phase 1. Phase 1 (step +8): 0 / 1 the choices -- 'yes' shows message 4 (7) -> 2, 'no' message 2 (6) with list
//   3 -> 1; 2 closes and, in the alternate episode, shows the explanation page 8 -> 3, else ends; 3 closes and ends
//   (sub_251ED0, flag 1 cleared).
void sub_251A80(EEContext& ctx);
// 0x251ED0 [bpTutaClose] Closes the second battle tutorial's windows (K_Assert line 49): sub_3C77A0, sub_21C930.
void sub_251ED0(EEContext& ctx);
// 0x251F40 [bpoOpen] Opens the bpo banner (bpo_main.c, *$gp 0x7CE34C; K_Assert line 54) of kind a0: the plate (texture 57 for
//   kind 0, 58 for kind 1, of set 1) into its three quads (+16 / +272 / +528), sound request (1, 15, 2, 15), frame 0,
//   flags 1 | 2.
void sub_251F40(EEContext& ctx);
// 0x266F60 [bpPersonaOpen] Opens the battle panel persona status (bp_persona.c, *$gp 0x7CE398; K_Assert line 36) for persona
//   a0: its record (sub_1749A0), a status task set (fclMisc_CreatePsStatusTasks(0, 0, 5, 0)) into +4 showing it
//   (sub_3C9B00), sub_3C9CD0(-1), sub_3C9D00(8), page 1 when the party has two or more members (sub_1756F0) else 0
//   (sub_3C9E00); +8 = the persona, flags 1 | 2.
void sub_266F60(EEContext& ctx);
// 0x267070 [bpPersonaSet] Switches the battle panel persona status to persona a0 (K_Assert line 92: a different one): +8, the
//   record shown (sub_3C9B00), flag 2.
void sub_267070(EEContext& ctx);
// 0x267210 [bpPersonaIsShown] Flag 2 of the battle panel persona status (set when a persona is shown; K_Assert line 36).
void sub_267210(EEContext& ctx);
// 0x27B9F0 [bpSelectOpen] Opens the battle select marker (bp_select.c, *$gp 0x7CE3E4; K_Assert line 39): texture 58 of set 2
//   into its quad (+16), the frame +272 = 0, clears flag 2 (closing), places it (sub_27B6C0), flag 1.
void sub_27B9F0(EEContext& ctx);
// 0x27BA90 [bpSelectClose] Starts closing the battle select marker: frame +272 = 0, flag 2 (K_Assert line 39).
void sub_27BA90(EEContext& ctx);
// 0x27BAE0 [bpSelectSetPos] Moves the battle select marker to the screen point a0 {f32 x, y} (+276 / +280; K_Assert line 39)
//   and places it again while open (sub_27B6C0).
void sub_27BAE0(EEContext& ctx);

// --- shuffle: battle6_shuffle.cpp (register ABI: arguments in $a0.., the result in $v0) ----------
// 0x24D160 [sflCameraTerm] Closes the Shuffle Time camera work (K_Assert lines 59 / 78) and clears its $gp slot 0x7CE33C.
void sub_24D160(EEContext& ctx);
// 0x24D1C0 [sflCameraUpdate] Per-frame update of the Shuffle Time camera work (K_Assert lines 59 / 88: not inside a draw,
//   *0x960070 clear): while active (flag 1) with a camera picked (flag 2) it finds the picked camera record (+12,
//   sflCameraFind), steps it (sflCameraStep) and copies its rotation and position into the RW camera (sflCameraApply).
void sub_24D1C0(EEContext& ctx);
// 0x24D280 [sflCameraSetRwCamera] Sets the Shuffle Time camera work's RW camera (+16 = a0) and marks it active (flag 1;
//   K_Assert line 59).
void sub_24D280(EEContext& ctx);
// 0x24D2E0 [sflCameraAdd] Adds the camera record a1 under the id a0 to the Shuffle Time camera list (K_Assert line 121: the id
//   is new): record +4 the id, appended after the tail (+8 / +12 the links), its time +64 = 0.
void sub_24D2E0(EEContext& ctx);
// 0x24D3B0 [sflCameraExists] Nonzero when the Shuffle Time camera list has a record with the id a0.
void sub_24D3B0(EEContext& ctx);
// 0x24D430 [sflCameraFind] The Shuffle Time camera record with the id a0 (K_Assert line 175 when none; returns 0 then).
void sub_24D430(EEContext& ctx);
// 0x24D4C0 [sflCameraPick] Picks the Shuffle Time camera a0 (K_Assert line 175 when missing): +12 = the id, flag 2; a record
//   of kind 1 restarts its orientation node (+168, sub_24F090), points its position node's first child at the record's
//   anchor (+52, sub_2503F0) and restarts the position node (+68).
void sub_24D4C0(EEContext& ctx);
// 0x24D5E0 [sflCameraStep] Steps a Shuffle Time camera record (a0; K_Assert lines 208 / 252: kind 1 only): time +64 += 1.0
//   (16.16); the position follows the position node (+68 -> +32, flag +48); with a look-at node (+56 / +60) it builds
//   an orthonormal frame looking from the position at the node's point (sub_4C6AC0 / sub_4C69F0, cross products) into
//   the record's matrix (+16, sub_4BDCB0) through a scratch matrix (sub_4C38C0 / sub_4C3880).
void sub_24D5E0(EEContext& ctx);
// 0x24D7D0 [sflCameraApply] Copies a Shuffle Time camera record's rotation into the RW camera's frame (a0 +4): the quaternion
//   a1 +16..+28 becomes the 3x3 matrix (2 / |q|^2 scaling), the translation cleared, the matrix flags 3, then
//   RwFrameUpdateObjects (sub_4CB750).
void sub_24D7D0(EEContext& ctx);
// 0x24D8D0 [sflCameraInitRecord] Initialises a Shuffle Time camera record (a0): kind 1, the position / look-at flags +48 / +56
//   set, its orientation node (+168) as a random-wobble node (sub_24FD20) and its position node (+68) as a sum node
//   (sub_24FD40), both reset (sub_24DA60).
void sub_24D8D0(EEContext& ctx);
// 0x24D940 [sflCameraSetAnchor] Sets a Shuffle Time camera record's anchor node (+52 = a1; K_Assert line 292: kind set).
void sub_24D940(EEContext& ctx);
// 0x24D9A0 [sflCameraSetLookAt] Sets a Shuffle Time camera record's look-at node (+60 = a1; K_Assert line 297).
void sub_24D9A0(EEContext& ctx);
// 0x24DA20 [gcPoseTerm] Closes the gc_pose work (K_Assert line 93) and clears its $gp slot 0x7CE340.
void sub_24DA20(EEContext& ctx);
// 0x24DB90 [gcPoseTickAll] Advances every active gc_pose node by one frame (K_Assert line 93): time += 1.0 (16.16) and dirty
//   (gcPoseAddTime).
void sub_24DB90(EEContext& ctx);
// 0x24DC10 [gcPoseEvalAll] Evaluates every gc_pose node (K_Assert line 93): clears the evaluation stack (+520) and runs
//   gcPoseEval on each node of the list.
void sub_24DC10(EEContext& ctx);
// 0x24DC90 [gcPoseEval] Evaluates a gc_pose node (a0) and the dirty nodes it depends on, depth first on the work's 128-entry
//   stack (+8, count +520; K_Assert lines 230 / 306 / 408 / 452 / 530 on overflow). A gc_pose.c node (100 bytes): +4
//   next, +8 flags (1 active, 2 dirty), +12 kind (0 a position, 1 a direction, 2 an orientation), +16 its time (16.16
//   frames), +20 the value (f32[3], or a quaternion f32[4] for kind 2), +32 the position mode / +36 the orientation
//   mode, then the mode's words. A dirty active node whose inputs are clean computes its value and turns clean:
//   positions -- 0 fixed, 1 a wander (every +88 frames a new random target within +-range/2 (+84, libc rand), a spline
//   toward it (gcPoseWanderSpline), scaled by +96), 2 the sum of up to three child positions, 3 a timed move (+36: 1 a
//   constant-acceleration arc start + v*t + a*t^2/2 in 1/30 s units, 0 a straight lerp start -> end over +44, stopping
//   at the end time); directions (kind 1, mode word +32 = 1) the second position minus the first (+40 minus +36;
//   another nonzero mode asserts, line 425); orientations -- 1 a look-at quaternion from two directions (sub_4BDDE0
//   about the axes, the y axis when parallel), 2 the product of up to three child orientations, 3 a timed spin (+52
//   axis, angle by time), 4 a wobble (random angles over +100 frames times +108, gcPoseWobbleSpline), kind / mode
//   errors assert (lines 381 / 425 / 677 / 683).
void sub_24DC90(EEContext& ctx);
// 0x24F210 [gcPoseSetWander] Sets a wander position node's parameters (K_Assert 779 / 780: kind 0, mode 1): range +84 = f12,
//   period +88 = a1 frames, +92 = f13; marks it dirty.
void sub_24F210(EEContext& ctx);
// 0x24F2C0 [gcPoseSetWanderScale] Sets a wander position node's scale (+96 = f12; K_Assert 795 / 796) and marks it dirty.
void sub_24F2C0(EEContext& ctx);
// 0x24F350 [gcPoseWanderRestart] Restarts a wander position node (K_Assert 809 / 810) with the defaults range 10.0, period
//   180, +92 10.0, scale 1.0: new random start / target (gcPoseWanderPick) and the spline from (0, 0, +92)
//   (gcPoseWanderSpline).
void sub_24F350(EEContext& ctx);
// 0x24F410 [gcPoseWanderPick] Picks a wander position node's current and target points (K_Assert 833 / 834): +36..+44 and
//   +72..+80, each axis range/2 - range * (rand() & 0xFFF) / 4096 (libc rand, sub_488F30).
void sub_24F410(EEContext& ctx);
// 0x24F780 [gcPoseMoveStop] Stops a timed-move position node (K_Assert 853 / 854: kind 0, mode 3): +40 = 0.
void sub_24F780(EEContext& ctx);
// 0x24F7F0 [gcPoseWanderSpline] Builds a wander position node's spline toward its target (a0, a1 = the start tangent f32[3]):
//   +48 = +36 + a1, the normalised chords to and from the target and their cross products give the control point +60 =
//   +72 + (cross) * +92.
void sub_24F7F0(EEContext& ctx);
// 0x24FAA0 [gcPoseGetVector] A position or direction node's value (node + 20; K_Assert line 910 for an orientation).
void sub_24FAA0(EEContext& ctx);
// 0x24FBA0 [gcPoseGetQuat] Copies an orientation node's quaternion (+20..+32) to a1 (K_Assert 934 / 935: kind 2, mode < 5).
void sub_24FBA0(EEContext& ctx);
// 0x24FC40 [gcPoseSetQuat] Sets a fixed orientation node's quaternion from a1 (K_Assert 942 / 953: kind 2, modes 0..3).
void sub_24FC40(EEContext& ctx);
// 0x24FD10 [gcPoseInitFixed] Makes a0 a fixed position node (kind 0, mode 0).
void sub_24FD10(EEContext& ctx);
// 0x24FD20 [gcPoseInitWander] Makes a0 a wander position node (kind 0, mode 1).
void sub_24FD20(EEContext& ctx);
// 0x24FD40 [gcPoseInitSum] Makes a0 a sum position node (kind 0, mode 2) with no children.
void sub_24FD40(EEContext& ctx);
// 0x24FD80 [gcPoseInitMove] Makes a0 a timed-move position node (kind 0, mode 3).
void sub_24FD80(EEContext& ctx);
// 0x24FDC0 [gcPoseInitProduct] Makes a0 a product orientation node (kind 2, mode 2) with no children.
void sub_24FDC0(EEContext& ctx);
// 0x24FE20 [gcPoseInitWobble] Makes a0 a wobble orientation node (kind 2, mode 4).
void sub_24FE20(EEContext& ctx);
// 0x24FE40 [gcPoseWobbleRestart] Restarts a wobble orientation node (K_Assert 1051 / 1052) with the defaults ranges (5.0,
//   15.0, 15.0), period 180, +104 1.0, scale 1.0: new random angles (gcPoseWobblePick) and the spline from (0, 0,
//   +104).
void sub_24FE40(EEContext& ctx);
// 0x24FF10 [gcPoseWobblePick] Picks a wobble orientation node's current and target angles (K_Assert 1076 / 1077): +40..+48 and
//   +76..+84, each range/2 - range * (rand() & 0xFFF) / 4096 with the per-axis ranges +88..+96.
void sub_24FF10(EEContext& ctx);
// 0x250280 [gcPoseWobbleSpline] Builds a wobble orientation node's spline toward its target angles (as gcPoseWanderSpline, one
//   word further on: +52 = +40 + a1, control point +64 from +76, scale +104).
void sub_250280(EEContext& ctx);
// 0x2503F0 [gcPoseSetSumChild] Sets child a1 (0..2) of a sum position node to a2 (K_Assert 1116 / 1117).
void sub_2503F0(EEContext& ctx);
// 0x250480 [gcPoseMoveHalt] Stops a timed-move position node's run flag (+40 bit 1; K_Assert 1126 / 1127).
void sub_250480(EEContext& ctx);
// 0x250500 [gcPoseMoveLinear] Starts a straight timed move of a position node (K_Assert line 1137: mode 3): kind 0 (lerp), the
//   end +48 = a1, the start +60 = the current value, time 0, duration +44 = a2 frames (16.16), running.
void sub_250500(EEContext& ctx);
// 0x2505B0 [gcPoseMoveCurve] Starts a curved timed move (K_Assert 1193 / 1194): kind 1, the start velocity a3 (+60), the end
//   a1 (+84), the start = the current value (+72); the acceleration +48 is solved so that the arc starting with
//   velocity v reaches the end in a2 frames (t = a2 / 30 s, a = 2 (d - v t) / t^2 corrected along the velocity's
//   direction); duration a2 frames, running.
void sub_2505B0(EEContext& ctx);
// 0x2508C0 [gcPoseMoveEaseOut] Starts a decelerating timed move (K_Assert 1238 / 1239): kind 1 from the current value to a1 in
//   a2 frames, arriving at rest: velocity +60 = 2 d / t, acceleration +48 = -2 d / t^2 (t = a2 / 30 s).
void sub_2508C0(EEContext& ctx);
// 0x250A30 [gcPoseMoveEaseIn] Starts an accelerating timed move (K_Assert 1269 / 1270): kind 1 from rest to a1 in a2 frames:
//   velocity 0, acceleration 2 d / t^2.
void sub_250A30(EEContext& ctx);
// 0x250B90 [gcPoseMoveIsRunning] Nonzero while a timed-move position node runs (+40 bit 1; K_Assert line 1298).
void sub_250B90(EEContext& ctx);
// 0x250BE0 [gcPoseSetProductChild] Sets child a1 of a product orientation node to a2 (K_Assert 1327 / 1328).
void sub_250BE0(EEContext& ctx);
// 0x250C70 [gcPoseSpinHalt] Stops a spin orientation node (+44 bit 1; K_Assert 1337 / 1338: kind 2, mode 3).
void sub_250C70(EEContext& ctx);
// 0x250E70 [gcPoseSpinIsRunning] Nonzero while a spin orientation node runs (+44 bit 1; K_Assert 1405 / 1406).
void sub_250E70(EEContext& ctx);
// 0x250EF0 [gcPoseSetWobbleScale] Sets a wobble orientation node's scale (+108 = f12; K_Assert 1416 / 1417) and marks it
//   dirty.
void sub_250EF0(EEContext& ctx);
// 0x250F80 [sflProjectToScreen] Projects the world point a1 to the screen (a0 = f32[2]): the active camera's view matrix
//   (sub_198590 +32, sub_4C6BE0), then x * 640 / w and y * 448 / w.
void sub_250F80(EEContext& ctx);
// 0x251010 [gcPoseAddTime] Adds a1 to a pose node's time (+16) and marks it dirty.
void sub_251010(EEContext& ctx);
// 0x251030 [gcPoseTouch] Marks a pose node dirty (+8 bit 2).
void sub_251030(EEContext& ctx);
// 0x253A40 [sflCardsUpdate] Per-frame update of the Shuffle Time cards (sfl_card.c; K_Assert line 188): clears the 'models
//   loading' flag 0x200 once sub_21A120 says so; while open: counts frames (+75392); flag 0x20 holds while left / right
//   (0x8000 / 0x2000 held) stay down; the deal (flag 0x10): phase +75704 = 0 flies each card in at its own frame
//   (+75708[i] * +75912; the 'i%d c%d' printf, an accelerating move +75916 frames long, sound 1/0/6/2), and once every
//   card landed lays them out (gcPoseMove...) -> phase 1, where they turn over one by one every 3 frames (decelerating
//   moves, sound 6 / 2 when each lands) until none moves; otherwise the cursor: left / right (the pad words 0x7E0952 /
//   0x7E095A) step the selected card (+75692) with wrap-around (sub_25B300 / sub_25B3B0, sound 0) and set flag 0x20 at
//   the ends. Then the effect phases (flag 0x40, +75888): 1 the pick (the chosen card wobbles), 2 the fade out /
//   shuffle (sfl_cardShuffle) / fade in of +75904 over 6 + 5 + 6 frames, 3 a 30-frame fade in, 4 a 16-frame fade out, 5
//   the switch to card +75908 over 30 frames (the other cards fade out) with the orientation from +75776; every card's
//   update (sfl_cardUpdate); and the pick's finish (the chosen card flies to the centre with sound 1/0/6/15 unless flag
//   0x2000; the others spin away).
void sub_253A40(EEContext& ctx);
// 0x2564C0 [sflCardUpdate] Per-frame update of one Shuffle Time card (a0; K_Assert lines 188 / 1603): the flipped cards' sway
//   (a 90 frame cycle, -1000 * sin) into their point lights; a fade (flag 0x200, +4684: 3 in, 2 out over +4692 frames,
//   1 re-dirty the nodes, 0 the linked cards' nodes); the card's position / orientation from its pose nodes (+4044 /
//   +4344, gcPoseGetQuat) into its model (sub_20AC90), or for a stacked card (flag 8) its children's; the point light
//   of a highlighted card (flag 0x80) towards the camera (sub_34FF90..sub_34FD70) with alpha +4700; finally each
//   model's colour alpha = 255 * the cards' fade (+75904) * the card's own (+4704) (sub_20CC80, the glow sub_20D770 for
//   flag 0x80).
void sub_2564C0(EEContext& ctx);
// 0x258B40 [sflCardsShuffle] Shuffles the Shuffle Time cards (K_Assert lines 188 / 1146): releases the stacked cards
//   (sub_258F80), then permutes the slot numbers 0..n-1 (n = +75388) with (rand() & 15) + 1024 random swaps of two
//   different slots (libc rand, sub_488F30), gives each card (by its old slot, +16) its new slot, and sends every card
//   to its new place: x from sub_20C660(slot, n), y 184, projected (sub_20C500 / sub_20C400) and 100 further, a
//   straight move with the wander / wobble restarted.
void sub_258B40(EEContext& ctx);
// 0x25A130 [sflCursorUpdate] Per-frame update of the Shuffle Time card cursor (sfl_cursor.c; K_Assert line 71) while open: the
//   60-frame blink counter (+52); a running move (flag 2) by its kind (+3232): 0 slides the cursor from +4 to +16 over
//   4 frames (into +28), 1 waits 4 frames, 2 waits 16, 3 waits 16 then closes; each of the six card marks (528 bytes
//   from +64): the selected one (+48) brightens (+64 by 25 and +68 by 64 up to 256), the others fade (8 / 12 per
//   frame); then places the quads (sub_25AAD0(256)).
void sub_25A130(EEContext& ctx);
// 0x25A440 [sflCursorDraw] Draws the Shuffle Time card cursor (K_Assert line 71; the draw-1 task): the 2D render states, the
//   frame quads (+3248 / +3504 with texture 4, +3760 with texture 2 of the second set), then per card mark the
//   selection quad (the selected one, and the previous one +44 during a kind-1 move) and the glow quad while its
//   brightness (+64) is nonzero.
void sub_25A440(EEContext& ctx);
// 0x25A7D0 [sflCursorOpen] Opens the Shuffle Time card cursor (K_Assert line 71): flags cleared, the frame quads' UVs from the
//   texture sizes (117 x 32 and 63 x 20 cells), the cursor's start point (sub_258540(0, +28)), every mark's quads at
//   full texture, places them (sub_25AAD0), selection 0, move kind 2, flags 1 | 2.
void sub_25A7D0(EEContext& ctx);
// 0x260A50 [sflPselOpen] Opens the persona-select banner (sfl_psel2.c; K_Assert line 87): the plates 52 / 53 / 54 / 58 of the
//   panel texture set (sub_20EC50) into the quads +1040 / +1296 / +1552 / +1808 with alpha 30 / 30 / 30 / 50
//   (sub_21EA00 / sub_21EAC0), three more alphas 50, resets the frame counters (sub_260C20), places the quads
//   (sfl_pselLayout) and sets flag 1.
void sub_260A50(EEContext& ctx);
// 0x261480 [sflPselLayout] Lays out the persona-select banner for the current frame (K_Assert line 87): by the mode (+4: 0
//   opening, 1 closing) each quad slides and fades over its own frame span (the plates 52..54 over 5 / 6 frames, the
//   band over 8 / 10, ...) toward its place under the plate heights (texture sizes + 109), the band 544 px wide;
//   colours and positions through sub_21D8E0 / sub_21D950 / sub_21D890, the banner's fixed corners (224, 352).
void sub_261480(EEContext& ctx);
// 0x27BC00 [sflPersonaOpen] Opens the Shuffle Time persona status for persona a0 (sfl_persona.c; K_Assert line 41): its record
//   (sub_1749A0, or a fresh 52-byte one built by sub_176680 on the stack when it has none), a status task set
//   (fclMisc_CreatePsStatusTasks(0, 0, 5, 5)) into +4 showing it, sub_3C9CD0(-1), sub_3C9D00(8), page 1; +8 = the
//   persona, flags 1 | 2.
void sub_27BC00(EEContext& ctx);
// 0x27BD10 [sflPersonaSet] Switches the Shuffle Time persona status to persona a0 (K_Assert line 107: a different one), with a
//   stack record when it has none; flag 2.
void sub_27BD10(EEContext& ctx);
// 0x27BDF0 [sflPersonaClose] Closes the Shuffle Time persona status: destroys its task set and clears flag 1 (K_Assert line
//   41).
void sub_27BDF0(EEContext& ctx);
// 0x27BF60 [sflPersonaIsShown] Flag 2 of the Shuffle Time persona status (a persona is shown; K_Assert line 41).
void sub_27BF60(EEContext& ctx);
// 0x27BFB0 [sflPersonaHide] Starts hiding the Shuffle Time persona status: sub_3C9D00(16), frame +12 = 0, flag 8 (K_Assert
//   line 41).
void sub_27BFB0(EEContext& ctx);

// --- result: battle6_result.cpp (register ABI: arguments in $a0.., the result in $v0) ----------
// 0x24AC90 [brpBirthTerm] Closes the persona birth work (brp_birth.c, *$gp 0x7CE330; K_Assert lines 127 / 259: not busy): the
//   texture set (sub_239280), sub_20E030, the resources (brpResTerm), sub_21A1B0, the effect objects of flags 0x10 /
//   0x20 / 0x40 / 0x100 (+4036..+4048, sub_34FCF0), the task (flag 4, +50528, kwlnTaskDestroyWithHierarchy), the model
//   (flag 8, nullsub_66 of +28); frees the work (RwFree slot) and clears the $gp slot.
void sub_24AC90(EEContext& ctx);
// 0x24BA50 [brpResTerm] Closes the persona birth resource work (brp_res.c, *$gp 0x7CE334; K_Assert line 57): frees the four
//   loaded files (+16..+28, flag 1), the message file copy (+32, flag 2) and the block +36 (flag 4) through the RwFree
//   slot, clears the $gp slot.
void sub_24BA50(EEContext& ctx);
// 0x24BB30 [brpResUpdate] Per-frame step of the persona birth resource work (K_Assert lines 57 / 142): once the archive
//   request (+8, flag 1) is loaded it takes its six files -- 0 the texture set (sub_20E800), 1 the model set
//   (sub_21B4A0), 2..5 copied into RwMalloc blocks +16..+28 --, sets loaded flag 1, destroys the request; once the
//   message request (+12, flag 2) is loaded it copies the BMD (request +272 / +280) into +32, sets loaded flag 2 and
//   destroys it.
void sub_24BB30(EEContext& ctx);
// 0x24BF80 [brpResRequestMessages] Requests facility/msg/msg_combine.bmd for the persona birth (K_Assert lines 191 / 192: not
//   loading, not loaded) through H_Cdvd_Request (kind 0) into +12; sets flag 2.
void sub_24BF80(EEContext& ctx);
// 0x25D8A0 [brItemOpen] Lays out the item stock-over panel (br_item.c, *$gp 0x7CE370; K_Assert line 117) for the texture set
//   a0 (+8): the plates 52 / 53 / 54 / 58 into the quads +1040 / +1296 / +1552 / +1808 with alpha 30 / 30 / 30 / 50,
//   three more alphas 50, starts the opening (brItemStartOpen) and sets flag 1.
void sub_25D8A0(EEContext& ctx);
// 0x25D9E0 [brItemStartOpen] Starts the item stock-over panel's opening (K_Assert line 117): frame +12 = 0, mode +4 = 0, flag
//   2.
void sub_25D9E0(EEContext& ctx);
// 0x25DA30 [brItemLayout] Lays out the item stock-over panel for the current frame (K_Assert line 117): advances the frame
//   (+12) of the opening (mode 0, 10 frames, then flag 2 clears) or the closing (mode 1, 10 frames, then flag 1
//   clears); each quad slides and fades over its own span (the plates over 3 / 5 / 6 frames, the band 544 px wide over
//   8 / 10) through sub_21D8E0 / sub_21D950 / sub_21D890, the panel's fixed corners (224, 352).
void sub_25DA30(EEContext& ctx);
// 0x25ED40 [brItemDraw] Draws the item stock-over panel (K_Assert line 117): the backdrop quads (+784, +16), the band (+1808,
//   texture 58) and its shadow (+2064), the frame (+528), the window (+272, its blend by the mode) and the plates 52 /
//   53 / 54 (+1040 / +1296 / +1552) through the Im2D slot, with the render states between.
void sub_25ED40(EEContext& ctx);
// 0x25F4A0 [brItemTaskUpdate] Update callback of the 'stock over bg' task: lays out and draws the panel, returns 0 while it is
//   open (flag 1) and -1 (the task ends) once it closed.
void brItem_UpdateStockOverBgTask(EEContext& ctx);
// 0x25F510 [brItemTaskDestroy] Destroy callback of the 'stock over bg' task: clears the $gp slots 0x7CE370 / 0x7CE374 and
//   frees the task's work (a0 +60) through the RwFree slot (K_Assert line 117).
void sub_25F510(EEContext& ctx);
// 0x262790 [brHeroOpen] Opens the result screen's hero panel (br_hero.c, *$gp 0x7CE37C; K_Assert lines 83 / 137..139): the
//   hero's level (sub_16C7E0), the experience to the next level (sub_16D2F0, capped at 99,999), HP / max HP / SP / max
//   SP (sub_16C4F0..sub_16C670), the Academics / Charm / Courage ranks (datGet*Level - 1) and sub_16C920; flag 2 when
//   the level went up; then the panel's quads (textures 22..29 and the rank plates rank / rank + 7 / rank + 14), the
//   numbers (bpIfontDrawNumber), the HP / SP bars scaled by value / max, the level-up plates (6..10, flag 2), the name
//   line (frFontBuildGlyphList with the glyph x scale 120), the experience plates and number; frame +14688 = 0, flag 1.
void sub_262790(EEContext& ctx);
// 0x263170 [brHeroLayout] Places the result screen's hero panel for the current frame (K_Assert line 83) while open: the frame
//   counter cycles 0..1050 (+14688); every quad's position from its texture cell (sub_21D8E0, the slide-in offsets
//   0x7CB098 / 0x7CB09C), the numbers (sub_238DC0 / sub_238BF0), the name line at (155, 206) with colour 0xFFFFFFCD.
void sub_263170(EEContext& ctx);
// 0x263DB0 [brHeroDraw] Draws the result screen's hero panel (K_Assert line 83) while open: the quads in panel order (textures
//   22..29, the rank plates, the bars, the level-up plates, the numbers sub_239140) and the name line (frFontDraw)
//   through the Im2D slot.
void sub_263DB0(EEContext& ctx);
// 0x264EF0 [brPersonaSet] Switches the result screen's persona panel to persona a0 (br_persona.c, *$gp 0x7CE380; K_Assert
//   lines 39 / 89: a different one): its record shown in the status task set (sub_3C9B00).
void sub_264EF0(EEContext& ctx);
// 0x272810 [brpSeqUpdate] Per-frame update of the result screen's persona sequence (brp_seq.c, *$gp 0x7CE3C0; K_Assert line
//   176) while open, by its step (+16): 0 waits for the model (flag 0x100, sub_276CC0); 1 the level-up message, then
//   the parameter rises (brpSeqNext) or more level-ups; 2 the stat increases one by one (the five rises +90.. by name
//   0x68ED70 with sprintf('%d'), sound 1/0/8/1), then the next step; 3 the new skills (+24: 0 show 'learned' / 1
//   confirm / 2 the 'forget a skill' grid when eight are known (3 x 4 cursor +440 / +444 on the pad's left / right / up
//   / down) / 3 cursor / 4 confirm the forget / 5 next); 4 the skill power-up or change offer (+32, the two names of
//   +160 / +162, messages 14 / 15 / 16, sub_1768E0 / sub_176840); 5 the evolution (+28: the shift to another persona
//   (sub_1FB560, 'shift %d') or an item (sub_1FBA70, 'get item %d'), the fade, the birth screen (sub_24A7F0 /
//   sub_24AB10 / sub_24ABD0)); afterwards the birth step (sub_24ADF0) while flag 0x40.
void sub_272810(EEContext& ctx);
// 0x273C00 [brpSeqStepSkills] Persona sequence: go to the new-skill step (K_Assert line 176): sub_279750, sound (1, 0, 8, 2),
//   substep +24 = 0, step 3.
void sub_273C00(EEContext& ctx);
// 0x273C70 [brpSeqStepEvolve] Persona sequence: go to the power-up offer step (K_Assert lines 176 / 1007): clears flag 0x10,
//   the persona's name (sub_173220 of +4) into the message, message 8 with choice list 9 (type 0), sound (1, 0, 8, 4),
//   substep +28 = 0, step 5.
void sub_273C70(EEContext& ctx);
// 0x273D50 [brpSeqStepChange] Persona sequence: go to the skill change step (K_Assert line 176): the persona's name and the
//   skill name of +160 (the 19-byte skill name rows *0x7CE4EC) into the message, message 13 with choice list 9, clears
//   flag 0x20, substep +32 = 0, step 4.
void sub_273D50(EEContext& ctx);
// 0x274100 [brpSeqNextSkill] Persona sequence: the next new skill (K_Assert line 176): +432 counts; the learn-list views
//   (sub_279120, sub_2792C0, sub_274C00, sub_279840); after the last (+436) the sequence moves on (sub_273800), else
//   the next skill's step (as brpSeqStepSkills).
void sub_274100(EEContext& ctx);
// 0x275440 [brpRootCreate] Creates the 'persona grow' screen (a script command, sub_3D3D20): a 17,680-byte work (RwMalloc)
//   with the persona sequence (+0, sub_272330), the panel works +528 / +608 / +2176 / +2192 (sub_233970, sub_275A70,
//   sub_276910, sub_276D10), the 'persona grow' task (update brpRootTaskUpdate) and its 'persona grow draw' task
//   (priority 6315, brpRootTaskDraw); registers the work at $gp 0x7CE3C4.
void sub_275440(EEContext& ctx);
// 0x275520 [brpRootDestroy] Destroys the 'persona grow' screen (brp_root.c; K_Assert line 70): the persona status, sequence
//   and panels (sub_276C30, sub_272380, sub_233E70, sub_275A80, sub_276920, sub_276D30), both tasks, the work, the $gp
//   slot.
void sub_275520(EEContext& ctx);
// 0x2755D0 [brpRootStart] Starts the 'persona grow' screen for the start block a0 (K_Assert line 70): the panels (sub_275A90,
//   sub_277070), the sequence (sub_272400(a0)), sub_276D90, the ADX SOUND2\EVENT\EVE_530.ADX on channel 3 (sub_10A370),
//   flags 1 | 2.
void sub_2755D0(EEContext& ctx);
// 0x275670 [brpRootIsRunning] Nonzero while the 'persona grow' screen runs (flag 1 of +17664; K_Assert line 70).
void sub_275670(EEContext& ctx);
// 0x2756C0 [brpRootTaskUpdate] Update callback of the 'persona grow' task: the panel updates (sub_234070, sub_275BC0), the
//   persona sequence (brpSeqUpdate), sub_276930, sub_2770F0; the music flag 2 clears once the sequence is done with it
//   (sub_275370 -> sub_2753C0), the running flag 1 once sub_2727C0 says so; returns 0.
void sub_2756C0(EEContext& ctx);
// 0x2757A0 [brpRootTaskDraw] Draw callback of the 'persona grow' task: printf('%x', *0x960070), sub_275CB0, the parameter
//   panel's draw (brpParamDraw); returns 0.
void sub_2757A0(EEContext& ctx);
// 0x2757E0 [brpRootLoadPack] Installs the 'persona grow' screen's resource pack a0 (K_Assert line 201: 3 entries): entry 0
//   (sub_234710 with its size), entries 1 / 2 (sub_234690 0 / 1) by their offsets +8 / +16 / +24.
void sub_2757E0(EEContext& ctx);
// 0x2758E0 [brpRootFillParams] Fills the 'persona grow' screen's parameter panel for persona a1: sub_2769C0, sub_276BA0; its
//   record (sub_1749A0): the skills (sub_176A30 count, sub_173370 list) into sub_2791B0, the next skill to learn
//   (sub_1FB1F0, sub_1FC230 / sub_1FC3C0 -> sub_279330 / sub_279450), the shown count (sub_2794C0), the five stats
//   (sub_173580 -> sub_279510 / sub_279580 / sub_2795F0), sub_276D90.
void sub_2758E0(EEContext& ctx);
// 0x2768C0 [brLvPanelClearFlag8] Clears flag 8 of the result screen level panel (br_lvpnl.c, *$gp 0x7CE3C8; K_Assert line 59).
void sub_2768C0(EEContext& ctx);
// 0x276A80 [brpPersonaShowPage] Shows the result screen persona status page 16 (brp_persona.c, *$gp 0x7CE3CC; K_Assert lines
//   37 / 89: open): sub_3C9D00(16), flag 4.
void sub_276A80(EEContext& ctx);
// 0x276B10 [brpPersonaShowMain] Back to the result screen persona status page 8 (K_Assert lines 37 / 98): sub_3C9D00(8), flag
//   4 cleared.
void sub_276B10(EEContext& ctx);
// 0x276C30 [brpPersonaClose] Closes the result screen persona status (K_Assert lines 37 / 116): sub_3C9D80(2), flag 2 cleared.
void sub_276C30(EEContext& ctx);
// 0x2771F0 [brpParamLayout] Lays out the result screen's parameter panel (brp_param.c, *$gp 0x7CE3D0; K_Assert line 97): the
//   frame quads (textures 21 / 23), the eight skill cells (272 bytes from +16, two columns of four) and their name
//   lines, the new-skill line (flag 2) blinking by the frame (+0x10: 5 / 10 / 20 / 30 frame steps) at (424, 338), the
//   stat bars and numbers (sub_238DC0), the evolution marks (sin pulse), through sub_21D8E0 / sub_21D950 /
//   frFontLineSetPos / frFontLineSetRgba.
void sub_2771F0(EEContext& ctx);
// 0x278550 [brpParamDraw] Draws the result screen's parameter panel (K_Assert line 97): the frame, the skill cells and their
//   names (frFontDraw), the stat bars, numbers (sub_239140) and marks through the Im2D slot.
void sub_278550(EEContext& ctx);

// --- staffroll: battle6_staffroll.cpp (register ABI: arguments in $a0.., the result in $v0) ----------
// 0x279940 [edScriptBuild] Builds the staff roll script object from the loaded ed_sr.bin file 0 (a0 = the file): allocates
//   (RwMalloc slot, hint 0x40000) a 20-byte head + the string table (4 bytes per string, +12 of them) + the string data
//   (file +20 / +24: offset / size) + the command stream (file +4 / +8), each part 4-byte aligned; head +0 the file's
//   word 0, +4 the string count, +8 the table, +12 the strings, +16 the commands; then the table: each string's start,
//   the strings' lengths being the bytes at file +16. Returns the object.
void sub_279940(EEContext& ctx);
// 0x279AC0 [edScriptFree] Frees the staff roll script object (a0) through the RwFree slot 0x96017C.
void sub_279AC0(EEContext& ctx);
// 0x279AF0 [edScriptGetString] The staff roll script's string a1 (head +8 table[a1]).
void sub_279AF0(EEContext& ctx);
// 0x279B10 [edScriptGetCommands] The staff roll script's command stream (head +16).
void sub_279B10(EEContext& ctx);
// 0x279B20 [edScriptGetStringCount] The staff roll script's string count (head +4).
void sub_279B20(EEContext& ctx);
// 0x279B30 [edScrollInit] Initialises the staff roll scroll work (a0, 4,656 bytes inside the ed_sr work) and registers it at
//   $gp 0x7CE3D4: flags 0, the line colour 0xFFFFFFFF, the 32 line slots free; the clear colour white (sub_1985B0 255,
//   255, 255, 255) with flag 2958 set, else dark blue (15, 31, 40, 255).
void sub_279B30(EEContext& ctx);
// 0x279BF0 [edScrollTerm] Closes the staff roll scroll work (K_Assert line 88 when none): frees every used line slot's glyph
//   lists (sub_27A560) and clears the $gp slot.
void sub_279BF0(EEContext& ctx);
// 0x279C90 [edScrollStart] Starts the staff roll scroll: the frame counter, string index and command cursor to 0, the start y
//   (+4632) and the next line's y (+4636) to 448.0 (the screen bottom), places the lines (sub_27A5D0), sets flag 1
//   (running) and the end phase 0.
void sub_279C90(EEContext& ctx);
// 0x279D10 [edScrollIsRunning] Nonzero while the staff roll scroll runs (flag 1).
void sub_279D10(EEContext& ctx);
// 0x279D60 [edScrollUpdate] Per-frame update of the staff roll scroll (K_Assert line 88). While running: when the last line
//   was placed (flag 4) it notes that line's y (+4648), clears the frame counter, enters end phase 1 and sets the clear
//   colour black. The scroll speed is the constant 0x7CAFAC (0x7CAFB4-based for the alternate episode, sub_17D800); the
//   hold time at the end 60 frames (alternate) or 30 (*0x7CC4E0). End phase 1: the last line eases to y = 208 over n =
//   speed / (k / (2 * (y0 - 208))) frames (a decelerating step each frame), holds for the hold time, then fades the
//   line colour's alpha (+4655) from 255 to 0 over 45 frames and stops (flag 1 cleared). Phase 0 scrolls by the speed.
//   Then, until the script ended (flag 2), reads commands while the next line's y minus the step is above 448: 4 a half
//   line (+12 px), 3 n blank lines (+24 * n px), 2 the next line is a caption, 1 a line: a free slot (sub_27A4A0) gets
//   the next string's glyph lists (sub_27A6A0), the last string marks the slot as the last line (+4640, flag 4), y
//   advances 24 px; 0 the script ends; each command printf's its kind ('regist string', 'caption', 'empty line', 'line
//   0') and steps the cursor (sub_27AB80). Finally every used slot moves up by the step (freed once 24 px above the
//   top) and the lines are placed again.
void sub_279D60(EEContext& ctx);
// 0x27A3B0 [edScrollDraw] Draws the staff roll (the 'edsr draw' task's pass; K_Assert line 88): every glyph list of every used
//   line slot through frFontDraw (a0 list, 1, 0) while the scroll runs. (Its caller, functions.json's
//   btlDrawMessagePass, is the staff roll's draw callback.)
void sub_27A3B0(EEContext& ctx);
// 0x27A4A0 [edScrollAllocLine] Takes the first free staff roll line slot (of 32, 144 bytes from +4), marks it used and returns
//   it (K_Assert line 407 when all are used).
void sub_27A4A0(EEContext& ctx);
// 0x27A560 [edScrollFreeLine] Frees a staff roll line slot (a0): each of its +132 glyph lists through sub_3B0170, then clears
//   the used flag.
void sub_27A560(EEContext& ctx);
// 0x27A5D0 [edScrollPlaceLines] Places every used staff roll line: position (x 57.0, the slot's y +140) through sub_27A930 and
//   the work's line colour (+4652) through sub_27AA00.
void sub_27A5D0(EEContext& ctx);
// 0x27A6A0 [edScrollBuildLine] Breaks a staff roll string (a1) into words for a line slot (a0): walks the string to its NUL;
//   each word (ended by a tab, space or the NUL) becomes a glyph list (frFontBuildGlyphList of the strncpy'd word, font
//   6 for a name or font 7 for a caption by a2) stored with its x offset at slot +4 / +8 + 8 * n; the offset advances
//   by the word's width, 40 px per tab and 10 px per space; slot +132 the word count; the default glyph flags 1 / 2 are
//   set / cleared around it.
void sub_27A6A0(EEContext& ctx);
// 0x27A930 [edScrollPlaceLine] Positions a staff roll line slot's glyph lists (a0) at the point a1 {f32 x, y}: each list at
//   (16 * (x + its offset), 8 * y) in the font's fixed-point units, then sub_3B2C60.
void sub_27A930(EEContext& ctx);
// 0x27AA00 [edScrollSetLineRgba] Sets the colour of a staff roll line slot's glyph lists (a0) from the bytes a1[0..3] (packed
//   r << 24 | g << 16 | b << 8 | a) through frFontLineSetRgba.
void sub_27AA00(EEContext& ctx);
// 0x27AAA0 [edScrollPeekCommand] The staff roll command at the script cursor (the command stream's byte at +4620).
void sub_27AAA0(EEContext& ctx);
// 0x27AB10 [edScrollPeekOperand] The staff roll command's operand (the byte after the cursor: the blank line count of command
//   3).
void sub_27AB10(EEContext& ctx);
// 0x27AB80 [edScrollStepCommand] Steps the staff roll command cursor past the current command: 1 / 2 / 4 one byte, 3 two bytes
//   (its operand), 0 stays (the end).
void sub_27AB80(EEContext& ctx);
// 0x27AC60 [edResInit] Initialises the staff roll resource work (a0, 16 bytes) and registers it at $gp 0x7CE3D8: both flag
//   words 0.
void sub_27AC60(EEContext& ctx);
// 0x27AC80 [edResTerm] Closes the staff roll resource work (K_Assert line 49): releases the loaded resources (sub_27AFD0) and
//   clears the $gp slot.
void sub_27AC80(EEContext& ctx);
// 0x27ACE0 [edResUpdate] Per-frame step of the staff roll resource work (K_Assert line 49): once the requested archive is
//   loaded (flag 1, H_Cdvd_IsFileLoaded) it takes its three files -- 0 the script (edScriptBuild), 1 / 2 the fonts 6 /
//   7 copied into RwMalloc blocks and installed with frLoadFontData_Ptr --, sets loaded (+4 flag 1), destroys the
//   request and clears flag 1.
void sub_27ACE0(EEContext& ctx);
// 0x27AE90 [edResRequest] Requests the staff roll archive (K_Assert lines 118 / 119: not loading, not loaded):
//   oped/ed_sr_f.bin for the alternate episode (sub_17D800), else oped/ed_sr.bin, through H_Cdvd_Request (kind 1); sets
//   flag 1.
void sub_27AE90(EEContext& ctx);
// 0x27AF80 [edResIsLoading] Nonzero while the staff roll archive loads (flag 1).
void sub_27AF80(EEContext& ctx);
// 0x27AFD0 [edResRelease] Releases the staff roll resources (K_Assert line 142 when not loaded): the script object, the fonts
//   6 and 7 (sub_3AFC30), clears the loaded flag.
void sub_27AFD0(EEContext& ctx);
// 0x27B070 [edResGetScript] The staff roll script object (resource work +12; K_Assert line 49).
void sub_27B070(EEContext& ctx);
// 0x27B0B0 [edSrUpdate] Per-frame update of the staff roll ('edsr' task, ed_sr.c; K_Assert line 61), while running: step 0
//   waits for the archive, starts the fade-in (sub_1085C0) -> 1; step 1 once the fade is idle (sub_108710) starts the
//   movie and the scroll (sub_27B200) -> 2; step 2 counts frames and, once the scroll stopped and the movie task is
//   gone (kwlnTaskExists), starts the fade-out (sub_108570) -> 3; step 3 clears the running flag once the fade is idle.
//   Every frame the resource step and the scroll update run.
void sub_27B0B0(EEContext& ctx);
// 0x27B200 [edSrStartMovie] Starts the staff roll's movie and scroll: movie 42 for the alternate episode (sub_17D800), else 32
//   with flag 2958 set or 33; starts the scroll (edScrollStart), creates the 'H_SfdPlay' movie task under the edsr task
//   (sub_10BCE0) into +4688, clears the frame counter +4692, step 2.
void sub_27B200(EEContext& ctx);
// 0x27B2B0 [edSrTaskUpdate] The 'edsr' task's update callback: runs edSrUpdate and returns 0 while the staff roll runs, -1
//   (the task ends) once it stopped.
void sub_27B2B0(EEContext& ctx);
// 0x27B3F0 [edSrTaskDestroy] The 'edsr' task's destroy callback: closes the scroll and resource works and frees the task's
//   work (a0 +60) through the RwFree slot.
void sub_27B3F0(EEContext& ctx);
// 0x27B460 [edSrStart] Starts or polls the staff roll (a script command's handler): with no staff roll task (*$gp 0x7CE3E0) it
//   allocates the 4,696-byte work, creates the 'edsr' task (edSrTaskUpdate / edSrTaskDestroy) and its 'edsr draw' child
//   (btlDrawMessagePass), initialises the resource and scroll works inside, requests the archive and sets running;
//   returns 0. Later calls return 0 while the task exists, then clear the slot and return 1.
void sub_27B460(EEContext& ctx);

// --- core: battle6_core.cpp (register ABI: arguments in $a0.., the result in $v0) ----------
// 0x280200 [btlUnitPointFromS16] A point on a unit (a0) from a short vector (a1 = s16[3]): the vector times the unit's scale
//   (+44) turned by the unit's rotation (+28, sub_4BE1E0) plus its position (+4), written to a2 (f32[3]).
void sub_280200(EEContext& ctx);
// 0x283750 [btlUnitMotionFrames] The length in frames of a unit's motion a1 at speed f12: the motion row index comes from the
//   per-side table 0x693290 (26 bytes per side, by motion; side 1 asks sub_2FB860 first and falls back to the table
//   when it answers -1, side 3+ uses row 0); an index beyond the unit's rows (+2520) gives 0, else the row's frames (+4
//   of the 10-byte row at +2540; 0 when negative) / (f12 * row speed% (+2) / 100), truncated to s16.
void sub_283750(EEContext& ctx);
// 0x284470 [btlPktShakeUpdate] Update callback of the unit shake packet (sub_2849A0 creates it; data {unit, f32 amplitude, u32
//   count}): marks the unit changed; once the amplitude is 0.5 or less it zeroes the shake offset (+16), clears motion
//   flag 1 and returns 1 (done); else the offset is the rotated shake axis (0x697870 through the unit's rotation) times
//   amplitude * (0.5 + 0.5 * sub_358030(0)), its sign alternating with the count, the amplitude decays by *0x7CAE10,
//   motion flag 1 is set, the count steps and it returns 0.
void sub_284470(EEContext& ctx);
// 0x284690 [btlPktHopUpdate] Update callback of the unit hop packet (data {f32 start[3], unit +12, u16 frames +16, u16 step
//   +18, f32 t +20}): marks the unit changed; on step 0 notes the start point and t = 0.5; t advances by 1 / (2 *
//   frames); the offset along the rotated axis 0x697870 is max(75, 1.25 * radius * scale) times the arc 2 * (4t(1-t)...
//   - 0.5) and the packet ends (returns 1) once that factor reaches *0x7CAEA4; the position is start + offset unless
//   the unit is pinned (flag 0x400); the step counts.
void sub_284690(EEContext& ctx);
// 0x284D10 [btlPktModelResetUpdate] Update callback of packet kind 258 (sub_284D80): when the unit (data +0) has a model (flag
//   2) it calls sub_318770(model, 0); returns 1 (done at once).
void sub_284D10(EEContext& ctx);
// 0x284D60 [btlPktUnitRelease] End callback shared by the unit packets: releases the unit (data +0) -- its busy count (+160)
//   minus one.
void sub_284D60(EEContext& ctx);
// 0x284D80 [btlPktCreateModelReset] Creates packet kind 258 (8 data bytes) for unit a0 with the word a1 at data +4: init
//   sub_284CF0, update btlPktModelResetUpdate, end btlPktUnitRelease. Returns the packet.
void sub_284D80(EEContext& ctx);
// 0x285DE0 [btlPktUnitHold275] Init callback of packet kind 275: holds the unit (data +0): busy count (+160) plus one.
void sub_285DE0(EEContext& ctx);
// 0x285E00 [btlPktUnitCall275] Update callback of packet kind 275: sub_287490(unit); returns 1.
void sub_285E00(EEContext& ctx);
// 0x285E30 [btlPktUnitRelease275] End callback of packet kind 275: busy count minus one.
void sub_285E30(EEContext& ctx);
// 0x285E50 [btlPktCreate275] Creates packet kind 275 (4 data bytes: the unit a0) with the callbacks 0x285DE0 / 0x285E00 /
//   0x285E30; the boss handlers sub_2EABF0 / sub_2EB2C0 use it.
void sub_285E50(EEContext& ctx);
// 0x285EB0 [btlPktUnitHold276] Init callback of packet kind 276: holds the unit (busy count plus one).
void sub_285EB0(EEContext& ctx);
// 0x285ED0 [btlPktUnitCall276] Update callback of packet kind 276: sub_287510(unit); returns 1.
void sub_285ED0(EEContext& ctx);
// 0x285F00 [btlPktUnitRelease276] End callback of packet kind 276: busy count minus one.
void sub_285F00(EEContext& ctx);
// 0x285F20 [btlPktCreate276] Creates packet kind 276 (the unit a0) with the callbacks 0x285EB0 / 0x285ED0 / 0x285F00
//   (sub_2EABF0 / sub_2EB2C0).
void sub_285F20(EEContext& ctx);
// 0x286380 [btlPktModelFxInit] Init callback of the model effect packet (kind 273): holds the unit; unless the data flags have
//   0x10 it starts the model's effect (sub_31C7E0) when the model's effect slot (+1016) is free, and marks it started
//   (data +12 = 1).
void sub_286380(EEContext& ctx);
// 0x2863F0 [btlPktModelFxUpdate] Update callback of the model effect packet: starts the effect on the first update if the init
//   did not (returns 0), then returns 1 once the model's effect (+1016) finished (sub_31EBE0), else 0.
void sub_2863F0(EEContext& ctx);
// 0x286480 [btlPktModelFxEnd] End callback of the model effect packet: busy count minus one.
void sub_286480(EEContext& ctx);
// 0x2864A0 [btlPktCreateModelFx] Creates the model effect packet (kind 273, 16 data bytes) for unit a0: clears the packet's
//   byte +71 bit 1, callbacks btlPktModelFxInit / Update / End; data {unit, u16 side + 1, u16 a1, u16 a2, started 0};
//   the REINFORCE / SUMMON updates (sub_294D40 / sub_295160) use it.
void sub_2864A0(EEContext& ctx);
// 0x286540 [btlUnitsUpdate] Per-frame update of every battle unit (btlUpdateTask), the four unit lists in turn: the walk /
//   motion steps (sub_280DA0, sub_2826D0), a persona's instance (side 2, sub_1A0E50), the enemies' boss hook (side 1,
//   sub_2FD520). For units with a model: sub_29EE20; the fade alpha (+55) steps 28 toward 255 while shown (not hidden,
//   or flagged 4) and toward 0 otherwise; a colour fade (+76 frames, over 8 steps) moves +64..+66 from +72..+74 toward
//   +68..+70. When something changed (flag 4): the model matrix from the rotation quaternion (+28), the scale (+44) and
//   the position plus the shake offset (+4 / +16) (sub_318A70 / A90 / A30), the tint = the four RGBA bytes +48 * +52 *
//   +60 * +64 (each 1/255, rounded) into +78..+81 (sub_318AD0); an opaque tint (alpha 254+) selects render mode 0x7381B
//   and the model passes 2 / 5 (sub_287CF0), a blended one the transparent passes (sub_287B20, not for personas); the
//   model's render mode (+232) and its five attachments' follow; sub_2D4040; flag 4 clears. Then the model's pending
//   update (+216 bit 4, sub_317730) and the status aura (+2552): a new aura colour (sub_2BBFA0 vs sub_2BBDF0) starts an
//   8-step colour fade, then the aura gets the tint and is updated.
void sub_286540(EEContext& ctx);
// 0x287860 [btlUnitReleaseAttachments] Releases what a unit (a0) carries before it is destroyed (sub_2879F0): sub_287740; with
//   a child unit (+2560) sub_2878D0; the status aura (+2552) through sub_2BBD00 and the effect handle (+2556) through
//   sub_2BB8F0, each cleared.
void sub_287860(EEContext& ctx);
// 0x28B230 [btlActionUpdateStart] btlAction state START, update: unless the battle is over or an effect packet of the kinds
//   1792 / 1284 / 1286 / 769 / 260 still runs: with regeneration bits (+1156) left it plays the lowest one -- 0x1 / 0x2
//   / 0x4 HP 2 / 4 / 6 % (skills 547..549, effect 47), 0x8 / 0x10 / 0x20 SP 3 / 5 / 7 (550..552, effect 48), 0x40 /
//   0x80 HP 8 % (607 / 608, effect 57) -- clears it and queues the skill name (sub_2BD590), the effect of gBtl
//   +3108[effect], the sound (12, 2, 11; 10 for 607 / 608), the heal (sub_2D7E20) and the HP / SP gauges; with none
//   left, as START's init: BAD (11) / START HOME (3) by the unit's status, SUPPORT (10) without one.
void sub_28B230(EEContext& ctx);
// 0x28CA00 [btlActionUpdateAnalyze] btlAction state ANALYZE, update (row 7), a step machine in +1156 (unless effect packet
//   2048 runs): 1 the analysed unit (sub_2DB690 / sub_289030) alive and in the battle: the flags 320 / 321 pick the
//   analysis panel (sub_1FE2E0 / sub_1FE270), the camera on it, fades, sounds, the command menu hidden (gBtl 0x4000) ->
//   2, else -> 4; 2 when the panel is open, its message (sub_2DBB00 / sub_2E2D00) -> 3; 3 on confirm / cancel (pad bits
//   0x40 / 0x20) closes it (sub_1FE350), the menu back -> 5; 4 queues the 'cannot analyse' line (sub_2DB740 kind 10) ->
//   6; 5 waits for the panel to close -> 6; 6 ends: an action flagged 4 hands over to PACKET (30) with gBtl 0x400000 /
//   +24 bits 0xC, else back to the resume state (+20) after sub_1FE4A0 / sub_2BED10; the step resets.
void sub_28CA00(EEContext& ctx);
// 0x28CF20 [btlActionInitAuto] btlAction state AUTO, init (row 9): resets the target list (sub_2D15A0 of +56), fills the
//   target candidates (sub_2BFF60 into +136) and the cursor (sub_2C0970).
void sub_28CF20(EEContext& ctx);
// 0x28CF80 [btlActionUpdateAuto] btlAction state AUTO, update: command kind 1 (attack) with the unit's attack skill
//   (sub_308930), the first candidate as the single target (sub_2C0880 / sub_2C08A0); the hero (side 0, id 1) gets the
//   voice line packet kind 1; gBtl 0x4000000 sets the action's flag 0x4000; flag 2, state READY (12).
void sub_28CF80(EEContext& ctx);
// 0x28D080 [btlActionUpdateSupport] btlAction state SUPPORT, update (row 10; unless effect packet 1286 runs): the first of the
//   unit's timed effects that ran out (sub_302F50, kinds 0..16 by a jump table) is cleared (datCalcClearEffect: 0 / 1
//   together, 2 / 4 together, else its own) and its end message plays (sub_2BD850 with 22 + 2 * kind for the party, one
//   more for an enemy; 70 / 71 and 90..97 for the later kinds) with the voice packet 9; kind 9 also drops HP and SP to
//   1 (a damage packet of 1 - HP / 1 - SP, sub_2D7E20). The state repeats until none is left, then BAD (11) or START
//   HOME (3) by sub_2DC070.
void sub_28D080(EEContext& ctx);

}  // namespace p3fes::game
