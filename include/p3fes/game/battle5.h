// The battle code, fifth pass (slice battle5; docs/ANALYSIS/21_battle.md): the still-recompiled functions of the
// bands 0x240000-0x2FFFFF that the battle replay and the Tartarus climb reach (battle4's first-call probe; the replay
// is deterministic, so its reach is the same on this main), with the relaxed callee rule: a still-recompiled callee is
// reached through its gen:: entry point. game/src/battle/battle5.cpp; the bodies come from p3fes_handgen (register
// ABI: arguments in $a0.., the result in $v0), with the record offsets named below (battle3.h's b3:: and battle4.h's
// b4:: records reused) and each function's role given. Names: functions.json's in code, ours in brackets in the
// comments (ADR-0009); the confirmed record fields go to tools/ours/types/deltas/battle5.json.
//
// Groups:
//   * the battle panel modules: the command panel's update / open / close / cursor (bpc_main.c), the message window
//     (bpm), the bpe item message, the battle list cursor (bp_list.c), the bai panel, the yes / no dialog
//     (bp_dialog.c), the one-more banner (bp_rush.c), the persona panel (bp_persona.c), the common resources
//     (battle/panel/bs_init.bin), the shuffle-time count-down / persona-select / persona panels;
//   * the op screens (op_root / op_res / op_title / op_menu / op_wait / op_fade.c): the op root task, its
//     resources, draws, the wait screen's ripple vertex callbacks and the fade; the indexed grid mesh;
//   * the result screen: the hero / persona / level panels, the persona sequence of brp_seq.c (level-up, new skills,
//     the skill power-up / change roll, evolution) and the parameter panel of brp_param.c; the sprite-sheet quads;
//   * the units: effect / centre / cell points through the facing rotation, the walk step along a path, the idle and
//     wait motions, model load / release, unit destruction, the per-unit light, the party's idle glances;
//   * the packet callbacks: place at a unit, turn toward, play motion, load / drop the model, apply damage, the
//     navigator lines, the sound requests, the special voice, the cut-in and special-effect players;
//   * the action states: turn start (status effects, rising from down), command chosen, the all-out attack, end of
//     action, removal; the skill resolution (hit check, affinity, hit count, damage per hit, the result block);
//   * the formation pick and placement (btlFormation.c), the camera update and shots, the light copies and fades;
//   * the navigator and support lines (request, update, the turn-end support events), the battle music, the voice
//     line pickers, the fusion-skill AI pick, the analysis view, the boss rules by encounter (fixed placements, unit
//     set-up, reaction motions, win conditions, per-frame updates), the screen flash.
//
// THE BATTLE STATE A CO-OP SERVER WOULD OWN (additions to battle3.h / battle4.h's lists)
//   * the action result block (btlAction +200..+222) and the 28-byte hit records (+224..): written by the skill
//     resolution (sub_2D6620) from the hit / affinity / damage formulas and the random stream; the damage packets
//     (sub_2D79A0) apply them to the DatUnits -- server logic; clients only play the packets.
//   * the formation (gBtl +2616 / +2618, the slot words +2620 / +2636, the units' slot byte +2544 and cells): set
//     once at the battle start (sub_2B71E0) from the formation table -- server state.
//   * the support events (gBtl +2552..+2576) and the kill counters (+2970 / +2972, +3088 / +3092): battle logic.
//   * the navigator line state (+2580..+2614), the camera (+188..+252), the lights (+404..+576), the cut-in handle
//     (+3360) and every panel / result-screen work are presentation (client side); the navigator / voice pickers and
//     the idle glances draw from the shared random stream (datCalcRand), like battle3's presentation draws, so a
//     server and its clients must agree on which of them run.
//   * the result screen's persona sequence rolls the skill power-up / change with sub_488F30 (the libc rand), not
//     datCalcRand: a server would have to own that roll.

#pragma once

#include "p3fes/ee_context.h"
#include "p3fes/game/battle3.h"
#include "p3fes/game/battle4.h"

namespace p3fes::game {

namespace b5 {

// --- $gp slots (offset from $gp 0x7D2CF0) ---------------------------------------------------------------------
inline constexpr s32 kGpBaiWork = -18872;     // 0x7CE338 the bai work (bai_main.c)
inline constexpr s32 kGpBpPersona = -18776;   // 0x7CE398 the battle panel persona work (bp_persona.c)
inline constexpr s32 kGpBpSelect = -18700;    // 0x7CE3E4 the battle select work (bp_select.c)
inline constexpr s32 kGpBpSheet0 = -18768;    // 0x7CE3A0 the battle panel sprite sheet 0 (bs_init.bin file 0)
inline constexpr s32 kGpBpSheet1 = -18764;    // 0x7CE3A4 the battle panel sprite sheet 1 (bs_init.bin file 1)
inline constexpr s32 kGpBpTextures = -18760;  // 0x7CE3A8 the battle panel texture set (bs_init.bin file 2)
inline constexpr s32 kGpBrHero = -18804;      // 0x7CE37C the result screen hero panel (br_hero.c)
inline constexpr s32 kGpBrLvPanel = -18728;   // 0x7CE3C8 the result screen level panel (br_lvpnl.c)
inline constexpr s32 kGpBrPersona = -18800;   // 0x7CE380 the result screen persona panel (br_persona.c)
inline constexpr s32 kGpBrpParam = -18720;    // 0x7CE3D0 the result screen parameter panel (brp_param.c)
inline constexpr s32 kGpBrpPersona = -18724;  // 0x7CE3CC the result screen persona status (brp_persona.c)
inline constexpr s32 kGpBrpSeq = -18736;      // 0x7CE3C0 the result screen persona sequence (brp_seq.c)
inline constexpr s32 kGpFlashState = -18408;  // 0x7CE508 the screen flash words (+0 state, +2 frames, +4 hold)
inline constexpr s32 kGpLightRgba = -18424;   // 0x7CE4F8 the light colour scale word (RGBA)
inline constexpr s32 kGpOpFade = -18740;      // 0x7CE3BC the op fade work (op_fade.c)
inline constexpr s32 kGpOpMenu = -18748;      // 0x7CE3B4 the op menu work (op_menu.c)
inline constexpr s32 kGpOpRes = -18780;       // 0x7CE394 the op resource work (op_res.c)
inline constexpr s32 kGpOpRoot = -18792;      // 0x7CE388 the op root work (op_root.c)
inline constexpr s32 kGpOpTitle = -18756;     // 0x7CE3AC the op title work (op_title.c)
inline constexpr s32 kGpOpWait = -18744;      // 0x7CE3B8 the op wait work (op_wait.c)
inline constexpr s32 kGpPersonaLearn = -18632;// 0x7CE428 the persona learn table (70-byte rows: +6 the 16 learn entries)
inline constexpr s32 kGpPersonaTbl = -18640;  // 0x7CE420 the persona base table (14-byte rows: +3 the base level)
inline constexpr s32 kGpReactRows = -18508;   // 0x7CE4A4 the enemy reaction skills (8-byte rows for the enemies 149..156)
inline constexpr s32 kGpSflCount = -18828;    // 0x7CE364 the shuffle count-down work (sfl_count.c)
inline constexpr s32 kGpSflPersona = -18696;  // 0x7CE3E8 the shuffle persona panel (sfl_persona.c)
inline constexpr s32 kGpSflPsel = -18808;     // 0x7CE378 the persona-select work (sfl_psel2.c)
inline constexpr s32 kGpSkillUpgrades = -18616;// 0x7CE438 the skill upgrade pairs {u16 from, u16 to}, 0 ended
inline constexpr s32 kGpVoicesOff = -18416;   // 0x7CE500 nonzero: the special voices are off
inline constexpr s32 kGpWeaponHitRates = -18540;// 0x7CE484 the hit-count rates (3 bytes per weapon type, percent)

// --- gBtl additions (b3::gbtl, b4::gbtl4 have the rest) ----------------------------------------------------------------
namespace gbtl5 {
inline constexpr s32 kCamPos = 188;         // f32[3]: the battle camera position (btlCameraUpdate)
inline constexpr s32 kCamRot = 200;         // f32[4]: the battle camera rotation quaternion
inline constexpr s32 kCamShot = 240;        // u16: the camera shot id (the shot table sub_2F8840 / the default rows 0x6939F0)
inline constexpr s32 kCamHold = 244;        // u32: 0x1 the camera is held, 0x2 the shake runs
inline constexpr s32 kCamFrames = 248;      // s32: frames the shot ran
inline constexpr s32 kCamWait = 252;        // s32: frames before the shot callback runs
inline constexpr s32 kLightRot = 436;       // f32[4]: the light rotation quaternion (sub_19FDA0's, made a matrix by btlLightFadeStep)
inline constexpr s32 kSceneVecB = 468;      // f32[4]: the scene light B (sub_1A0A10; b3 kSceneVecA is +452)
inline constexpr s32 kSceneRot = 484;       // f32[4]: the scene light rotation (sub_1A0A50)
inline constexpr s32 kLightColA = 548;      // f32[4]: light colour A (the scene light, 1/255 units)
inline constexpr s32 kLightColB = 564;      // f32[4]: light colour B
inline constexpr s32 kSupportCount = 2552;  // u16[3] (stride 4): the support events' turn counters
inline constexpr s32 kSupportLimit = 2554;  // u16[3] (stride 4): their turn limits
inline constexpr s32 kSupportEvents = 2564; // u16: the support events armed (1 a member to call in, 2 / 4 navigator states)
inline constexpr s32 kSupportDone = 2566;   // u16: bit 1 the member was called in
inline constexpr s32 kSupportEnemy = 2572;  // u16: the enemy id event 4 watches
inline constexpr s32 kSupportMember = 2576; // u32: the setup member picked for event 1
inline constexpr s32 kNaviVoice = 2580;     // u16: the navigator's voice set (4, 6 for navigator 1)
inline constexpr s32 kNaviFlags = 2582;     // u16: bit 1 a navigator line is playing
inline constexpr s32 kNaviPending = 2584;   // u16: 1 a line waits for its delay, 2 starts next frame
inline constexpr s32 kNaviFile = 2588;      // u32: the navigator message file request (+272 its message table, 12-byte rows)
inline constexpr s32 kNaviPlayingMsg = 2592;  // u32: the message entry playing
inline constexpr s32 kNaviPlayingLine = 2596;  // s16: the line playing
inline constexpr s32 kNaviMsg = 2600;       // u32: the requested message entry
inline constexpr s32 kNaviLine = 2604;      // s16: the requested line
inline constexpr s32 kNaviDelay = 2614;     // s16: frames before the pending line starts
inline constexpr s32 kFormation = 2616;     // s16: the formation (0..23, -1 a fixed boss placement)
inline constexpr s32 kFormationEnemies = 2618;  // u16: the enemies active when the formation was set
inline constexpr s32 kPartySlots = 2620;    // u32[4]: the party formation slots used
inline constexpr s32 kEnemySlots = 2636;    // u32[5]: the enemy formation slots used
inline constexpr s32 kStepSound = 2704;     // u16: the next footstep sound (5..8)
inline constexpr s32 kStepSoundIdle = 2706; // s8: -1 when the next footstep may play
inline constexpr s32 kSoundMemo = 2708;     // {s16 id, s16 arg, u8}[] (stride 6, by bank): the sound each bank played last
inline constexpr s32 kSoundBank = 2808;     // u16: the bank of sub_2DDBA0's requests
inline constexpr s32 kVoiceFlags = 2816;    // u16: bit 1 the special voice finished
inline constexpr s32 kVoiceTrack = 2818;    // u16: the special voice track (4 / 5)
inline constexpr s32 kVoiceArg = 2820;      // u32: its argument
inline constexpr s32 kKillMaxLevel = 3088;  // s32: the highest level of the enemies defeated
inline constexpr s32 kKillLevels = 3092;    // s32: the levels of the enemies defeated, summed
inline constexpr s32 kCutIn = 3360;         // u32: the cut-in / special effect handle (sub_1166A0 / sub_116E20)
}  // namespace gbtl5

// --- btlAction additions (b3::act, b4::act4) ---------------------------------------------------------------------------
namespace act5 {
inline constexpr s32 kWakeTimer = 41;       // u8: turns before a sleeping unit may wake (2 + datCalcRand(1) after a sleep of 0x10)
inline constexpr s32 kGlanceStep = 52;      // u16: the idle glances taken (odd / even picks the side)
inline constexpr s32 kGlanceWait = 54;      // u16: frames to the next idle glance (60 + datCalcRand(180))
inline constexpr s32 kCmdSkillOrig = 114;   // u16: the skill chosen before a replacement (sub_2D5570)
inline constexpr s32 kResHits = 200;        // u8: hits landed (the result block +200..+222, cleared per resolution)
inline constexpr s32 kResRank = 201;        // u8: the hit rank
inline constexpr s32 kResSummary = 202;     // u8: 1 every target knocked down, 2 a miss / weak / reflect
inline constexpr s32 kResHit = 204;         // u16: the hit check result (1 hit, 2 / 4 miss, 256 / 1024 weak / critical, 512 reflected)
inline constexpr s32 kResAffinity = 206;    // u16: the affinity result
inline constexpr s32 kResDead = 208;        // u32: the target died
inline constexpr s32 kResReflected = 212;   // u32: the skill was reflected onto the user
inline constexpr s32 kResFailed = 216;      // u32: the skill failed (not enough SP / HP, a sealed enemy)
inline constexpr s32 kResVoice = 220;       // u16: the voice / message line of the result
inline constexpr s32 kResMotion = 222;      // s16: the motion of the result (-1 none yet)
inline constexpr s32 kHitRecs = 224;        // 28-byte hit records: +0 HP damage, +4 SP damage, +8 statuses, +12 status 2, +16 extra, +20 / +22 |HP| / |SP|, +24 result, +25 element, +26 flags
inline constexpr s32 kReviveSkill = 1120;   // u16: the skill that revived the unit (438 leaves HP at 0)
inline constexpr s32 kAoaFinish = 1176;     // u32: the all-out attack's finishing blow ran
inline constexpr s32 kHitRecSize = 28;      // bytes per hit record
}  // namespace act5

// --- btlUnit additions (b3::unit, b4::unit4; three of them rename b3 fields by what these bodies do) -------------------
namespace unit5 {
inline constexpr s32 kLightPos = 84;        // f32[3]: the light point (btlUnitUpdateLight)
inline constexpr s32 kLightCol = 112;       // f32[4]: the light colour
inline constexpr s32 kMoveFlags = 196;      // u32: the move flags (0x1 jump to the end, 0x2 turn at once; b3 calls it kWalkSpeed)
inline constexpr s32 kWalkSpeed = 204;      // f32: the walk speed per frame
inline constexpr s32 kStopDist = 232;       // f32: the distance short of the path's end to stop at (b3 kWalkTimer)
inline constexpr s32 kPathPoints = 244;     // {f32 x, z}[]: the walk path (from +244)
inline constexpr s32 kPathCount = 1260;     // u16: path points
inline constexpr s32 kPathNext = 1262;      // u16: the next path point
inline constexpr s32 kMotionFlags = 2508;   // u16: 0x2 / 0x4 hold, 0x8 pinned
inline constexpr s32 kIdleKind = 2512;      // u16: 0 wait, 3 stop at the end, 4..7 the motions 13 / 15 / 24 / 25
inline constexpr s32 kLoopFrom = 2522;      // s16: the loop start frame
inline constexpr s32 kLoopCount = 2524;     // s16: loops left
inline constexpr s32 kMotionPending = 2530; // u16: the motion queued after the wait motion
inline constexpr s32 kMotionSpeed = 2532;   // f32: the motion speed (0.5 / 1 / 2 / 3)
inline constexpr s32 kMotionBlend = 2536;   // s8: the blend kind (1 / 2)
inline constexpr s32 kSlot = 2544;          // s8: the formation slot (-1 none)
inline constexpr s32 kInstHandle = 2546;    // u16: the model instance handle (b3 kShadow; bits 10..19 its kind)
inline constexpr s32 kFxHandleA = 2552;     // u32: an effect handle (sub_2BBD00 releases it)
inline constexpr s32 kChild = 2560;         // u32: a child unit destroyed with this one (b3 kCamObj)
}  // namespace unit5

// --- a unit's model object (btlUnit + 2548) ----------------------------------------------------------------------------
namespace mdl {
inline constexpr s32 kFlags = 216;          // u16: 0x100 / 0x200 / 0x400 / 0x800 the attach options
inline constexpr s32 kReady = 238;          // u8: 1 when the model is ready
inline constexpr s32 kFrame = 264;          // f32: the motion frame
inline constexpr s32 kLightFlags = 904;     // u8: 0x2 / 0x4 / 0x8 / 0x10 the light / fade options
inline constexpr s32 kColour = 936;         // u8[3]: the colour offset
inline constexpr s32 kLightA = 940;         // f32
inline constexpr s32 kLightB = 944;         // f32
inline constexpr s32 kAlpha = 1053;         // u8: the model alpha
}  // namespace mdl

// --- the damage packet's data block (sub_2D79A0) -----------------------------------------------------------------------
namespace pdd {
inline constexpr s32 kSource = 0;           // u32: the source action
inline constexpr s32 kAction = 4;           // u32: the action hit
inline constexpr s32 kHp = 8;               // s32: HP to add
inline constexpr s32 kSp = 12;              // s32: SP to add
inline constexpr s32 kSetStatus = 16;       // u32: statuses to set
inline constexpr s32 kClearStatus = 20;     // u32: statuses to clear
inline constexpr s32 kExtra = 24;           // u32: sub_302380 flag
inline constexpr s32 kFlags = 34;           // u16: 0x8 a kill to count twice, 0x10 a revival
inline constexpr s32 kFlags2 = 38;          // u16: 0x2 / 0x4 the action flags 0x1000 / 0x800
}  // namespace pdd

// --- a sprite sheet (sub_21EC40's result) ------------------------------------------------------------------------------
namespace sheet {
inline constexpr s32 kTextures = 260;       // u32[]: the texture table (by a cell's +20)
inline constexpr s32 kCells = 388;          // u32: the cells (128 bytes: +20 texture, +24 flip bits, +84 / +88 / +92 / +96 the texel box, +100..+112 the corner colours)
inline constexpr s32 kCellSize = 128;       // bytes per cell
}  // namespace sheet

// --- a battle list cursor record (bp_list.c) ---------------------------------------------------------------------------
namespace blist {
inline constexpr s32 kFlags = 0;            // u32: 0x1 moved this frame, 0x2 at an end, 0x4 sounds on
inline constexpr s32 kTop = 4;              // s32: the first row shown
inline constexpr s32 kRows = 8;             // s32: rows shown
inline constexpr s32 kCursor = 12;          // s32: the cursor
inline constexpr s32 kCount = 16;           // s32: items
inline constexpr s32 kSounds = 20;          // u8[4][8]: the move sounds {kind, b1, b2, b3}
}  // namespace blist

// --- the bpe work (*kGpBpWork328, bpe_main.c) --------------------------------------------------------------------------
namespace bpe {
inline constexpr s32 kFlags = 0;            // u32: 0x1 a message is open
inline constexpr s32 kState = 4;            // s32: 0 the first message, 1 the second
inline constexpr s32 kNumber = 8;           // u16: the number shown
inline constexpr s32 kItemA = 10;           // u16: the first item name
inline constexpr s32 kItemB = 12;           // u16: the second item name
}  // namespace bpe

// --- the bp_rush work additions (b4::rush) -----------------------------------------------------------------------------
namespace rush5 {
inline constexpr s32 kBanner = 16;          // quad: the banner (texture 0)
inline constexpr s32 kStars = 272;          // quad[7] (256 bytes each): the stars (texture 1)
inline constexpr s32 kFade = 2064;          // s32: the banner fade (0..16)
inline constexpr s32 kGlow = 2068;          // s32: the star glow (0..10)
inline constexpr s32 kStarFrame = 2072;     // s32: the star frame (0..9)
}  // namespace rush5

// --- the battle dialog work additions (b4::dlg) ------------------------------------------------------------------------
namespace dlg5 {
inline constexpr s32 kFadeIn = 20;          // s32: frames of the fade-in (0..8)
inline constexpr s32 kCloseFrames = 24;     // s32: frames since the close request (4 ends it)
}  // namespace dlg5

// --- the op fade work (*kGpOpFade, op_fade.c) --------------------------------------------------------------------------
namespace opfade {
inline constexpr s32 kFlags = 0;            // u32: 0x1 running
inline constexpr s32 kMode = 4;             // s32: 0 none, 1 in, 2 out
inline constexpr s32 kLength = 8;           // s32: frames
inline constexpr s32 kFrame = 12;           // s32
inline constexpr s32 kQuad = 16;            // quad: the full-screen quad
inline constexpr s32 kColour = 272;         // u8[4]: RGBA
}  // namespace opfade

// --- the result screen persona sequence work (*kGpBrpSeq, brp_seq.c) ---------------------------------------------------
namespace brpseq {
inline constexpr s32 kFlags = 0;            // u32: 0x1 running, 0x4 / 0x8 a change pending, 0x10 evolves, 0x20 a skill upgrade, 0x80 the window open, 0x100 the panel up
inline constexpr s32 kPersona = 4;          // u16: the persona id
inline constexpr s32 kOwner = 8;            // u32: the owner word (bit 1 no evolution)
inline constexpr s32 kStep = 16;            // s32: the sequence step (1 level up, 2 new skills, 3 skill changes, 4 evolution, 5 done)
inline constexpr s32 kFrame = 20;           // s32: frames in the step (cleared when a message opens)
inline constexpr s32 kStatFrame = 36;       // s32: frames of the stat raise message
inline constexpr s32 kFirstStat = 40;       // s32: the first raised stat (5 none)
inline constexpr s32 kLastStat = 44;        // s32: the last raised stat
inline constexpr s32 kRecord = 48;          // u32: the persona record
inline constexpr s32 kLearnRow = 52;        // u32: the persona table row (+6: 16 learn entries {u8 level, s8 kind, u16 id})
inline constexpr s32 kStats = 56;           // u8[]: the stats before (+0 the level gain, +90..+94 the five raises)
inline constexpr s32 kSkills = 96;          // u16[]: the skills before
inline constexpr s32 kSkillCount = 116;     // s32
inline constexpr s32 kLearnNext = 120;      // s32: the next learn entry
inline constexpr s32 kLearnCount = 124;     // s32: learn entries reached by this level-up
inline constexpr s32 kChangeSkill = 132;    // s16: the skill of the pending change (flag 8)
inline constexpr s32 kChangeItem = 136;     // the item record of a pending kind 0..3 change (sub_1830C0)
inline constexpr s32 kUpgradeKind = 156;    // u32: 0 a power-up, 1 a change
inline constexpr s32 kUpgradeFrom = 160;    // u16
inline constexpr s32 kUpgradeTo = 162;      // u16
inline constexpr s32 kWord432 = 432;        // u32
inline constexpr s32 kNewSkillCount = 436;  // u32
inline constexpr s32 kNewSkills = 448;      // s32: count of the 8-byte entries from +452 {u16 skill, u32 level}
}  // namespace brpseq

// --- the op wait screen work (*kGpOpWait, op_wait.c) -------------------------------------------------------------------
namespace opwait {
inline constexpr s32 kFlags = 0;            // u32: 0x1 shown, 0x4 the intro runs, 0x8
inline constexpr s32 kState = 4;            // s32
inline constexpr s32 kFrame = 8;            // s32
inline constexpr s32 kFrame2 = 40;          // s32
inline constexpr s32 kMeshA = 4464;         // u32: the first ripple mesh
inline constexpr s32 kMeshB = 4468;         // u32: the second ripple mesh
inline constexpr s32 kFade = 4472;          // f32: the screen fade
}  // namespace opwait

// --- DatUnit additions (b3::dat, b4::dat4) -----------------------------------------------------------------------------
namespace dat5 {
inline constexpr s32 kVoice = 56;           // u16: the voice / message line the last hit left (cleared by the skill resolution)
}  // namespace dat5

// --- unit packet data additions (b4::pdu4) -----------------------------------------------------------------------------
namespace pdu5 {
inline constexpr s32 kUnit = 0;             // u32: the unit
}  // namespace pdu5

// --- the bpc work additions (b4::bpc) ----------------------------------------------------------------------------------
namespace bpc5 {
inline constexpr s32 kCursorPos = 29404;    // f32[2]: the screen point of the unit the cursor left (bpcMoveCursor)
}  // namespace bpc5

}  // namespace b5

// --- the functions (register ABI: arguments in $a0.., the result in $v0) ----------------------------------------
// 0x242CC0 [bpcUpdate] Per-frame update of the battle panel command work (bpc_main.c, *$gp 0x7CE320; K_Assert line 151): loads
//   the panel texture sets 2 / 1 / 5 / 3; while shown (flag 1) or sliding (0x20) it steps the 0..59 frame counter
//   (+29396), then for every entry (+12 of them, 2,624 bytes from +64) that is listed -- mode 2 (the enemy panel): any
//   of the entry flags 0x400 / 0x20 / 0x80; modes 0 / 1: its uid in the uid list, or sliding out -- steps the slide
//   counter (+1808: slide in / out to 10, the hit flash to 4, then the flag clears), in mode 2 with flag 0x80 fades the
//   three analysis marks (the lit one +2592 up to 10, the others down; K_Assert lines 255 / 256 on the index), copies
//   the unit's HP / max HP (+2608 / +2612), projects its centre (sub_280580, sub_2D20A0) into +2616 (flag 0x40 when off
//   screen) and adds 20 to y. Afterwards clears the work's flag 0x20 when no entry slides and, still shown, builds the
//   entries' draw (sub_245EA0).
void sub_242CC0(EEContext& ctx);
// 0x2441B0 [bpcOpen] Opens the battle panel command work for a turn (K_Assert: not open, uid count > 0; printf of the mode):
//   clears flags 0x4 / 0x8 / 0x10 / 0x20 / 0x2 / 0x100 (0x2 again for a single listed unit), mode 2 for the panel words
//   335 / 324 (+29392) else a0; with persona 6 (sub_1FF740 == 1, datPersonaGetByPcId) the skills 335 / 336 set flags
//   0x4 / 0x8. With one listed unit it builds the name line (an enemy's name from the 19-byte name table *0x7CE4E8, a
//   party member's from sub_1775A0) and the panel quads (textures 67 / 68 / 0 / 66 x2 at +26304..+27584); then the
//   per-member persona marks (sub_20F7D0 / sub_20FA80), the entry rebuild sub_245A00 and the slide-in of the listed
//   entries (sub_245910); sets flag 1.
void sub_2441B0(EEContext& ctx);
// 0x244770 [bpcClose] Closes the battle panel command work: frees the name line (+27840, flag 2), the members' persona marks
//   (sub_20F8B0 / sub_20FB60), starts every listed entry's slide-out (sub_245970; mode 2 clears flag 0x20 of the
//   entries without 0x480), clears flags 1 / 2 and the uid count, sets flag 0x20 (sliding).
void sub_244770(EEContext& ctx);
// 0x244A00 [bpcCloseWithSound] Close with a sound: sound request (0, 0, 0, 2) through sub_10A4E0, then bpcClose.
void sub_244A00(EEContext& ctx);
// 0x244A40 [bpcMoveCursor] Moves the battle panel's cursor to the unit with uid a0 (K_Assert: flag 2, line 881; the target is
//   a party member, line 891): swaps the persona marks of the old and new unit, slides the old entry out, keeps the old
//   cursor's screen point (+29404 / +29408, flag 0x10), moves the 0x400 'first' flag to the new entry, slides it in
//   (sub_2459D0 for analysed enemies in mode 2), rebuilds the name line and plays sound (0, 0, 0, 0).
void sub_244A40(EEContext& ctx);
// 0x248500 [bpmShowMessage] Shows a message in the battle panel message window (bpm_main.c, *$gp 0x7CE324): closes the open
//   one (sub_2491F0), builds the text's glyph list (sub_248F40) and opens it (sub_248FC0).
void sub_248500(EEContext& ctx);
// 0x248F40 [bpmBuildLine] Builds a glyph list for a battle panel text: default glyph flag 1 set and 2 cleared around
//   frFontBuildGlyphList(a0, 2, 6, 0, 0); returns the list.
void sub_248F40(EEContext& ctx);
// 0x249250 [bpeRelease] Releases the bpe work (bpe_main.c, *$gp 0x7CE328; K_Assert line 55): closes its message (sub_3C77A0)
//   when open (flag 1) and clears the slot.
void sub_249250(EEContext& ctx);
// 0x2492B0 [bpeUpdate] Per-frame update of the bpe message (bpe_main.c): while open, state 0 waits for the message window
//   (sub_3C7990 / sub_3C7850) to finish, then closes it and requests the next message (the item names of the words +10
//   / +12 through sub_173220, the number +8 with 5 digits; msgWinRequestMessage) and goes to state 1; state 1 closes
//   the window when done and clears flag 1.
void sub_2492B0(EEContext& ctx);
// 0x249690 Releases a model object's attachment: when +1540 bit 1, sub_4CAF80 on the attachment's +4 and sub_474630 on the
//   attachment (+1536).
void sub_249690(EEContext& ctx);
// 0x24A230 Copies an RGBA colour (4 bytes) into an object's +1556.
void sub_24A230(EEContext& ctx);
// 0x24A260 [bpListUpdate] Cursor step of a battle list (bp_list.c; K_Assert: the work's 'moved' flag 1 is clear): reads the
//   pad (the repeat words 0x7E0952 / 0x7E095A, the held words 0x7E094C / 0x7E0956): down / up move the cursor (+12)
//   with wrap-around and scroll the window (+4 top, +8 rows, +16 items), R2 / L2 (bits 2 / 1) page down / up; each move
//   plays the list's sound for that move (sub_24A630), sets flag 1 (moved) and flag 2 at either end.
void sub_24A260(EEContext& ctx);
// 0x24A630 [bpListPlaySound] Plays a battle list's move sound: when the list's sound flag (4) is set, the move's 4-byte entry
//   +20 + 4 * a1 picks a sound request (kind 1: sub_10A4E0 with the entry's bytes; kind 0: sub_10A4E0(0, b1, b2, b3)).
void sub_24A630(EEContext& ctx);
// 0x24CCA0 [baiDraw] Draw of the bai panel (bai_main.c, *$gp 0x7CE338; K_Assert line 55): when shown (+4 bit 1), RW render
//   states, the background quads +16 / +784 and the two textured quads +272 / +528 through the Im2D slot 0x96009C
//   (texture sub_21C790 of the work's +0).
void sub_24CCA0(EEContext& ctx);
// 0x25B690 [sflCountUpdate] Per-frame update of the shuffle-time count-down (sfl_count.c, *$gp 0x7CE364; K_Assert line 43):
//   steps the frame counter (+4; done at 180, or 20 frames after flag 2), then for each of the three numbers (textures
//   sub_20E610(i)) scales its quad about (319, 279) as it appears (frames 90 + 30 * (2 - i)), fades it in over 10
//   frames and out after 15, sets its colours and plays the tick sound (1, 1, 6, 5) on its first frame.
void sub_25B690(EEContext& ctx);
// 0x25C220 [bpDialogUpdate] Per-frame update of the battle yes / no dialog (bp_dialog.c, *$gp 0x7CE368; K_Assert line 60):
//   after 8 frames of fade-in, the pad bits 0x40 / 0x20 of gPadFlags answer 0 / 1 (flag 2, sound 1 / 2); a close
//   request (flag 8) finishes after 4 frames (sub_25CD30); lays out the question and the two answers (centred on 252
//   from the font lines' widths), the window quads (textures +800 / +804, 89 / 90) and their fades.
void sub_25C220(EEContext& ctx);
// 0x25CF20 [bpRushOpen] Opens the one-more banner (bp_rush.c, *$gp 0x7CE36C; K_Assert line 50): the banner quad (texture 0 of
//   sub_267390's set) and the seven star quads (texture 1), the three counters cleared, flags 1 | 4, layout sub_25D130.
void sub_25CF20(EEContext& ctx);
// 0x25D020 [bpRushUpdate] Per-frame update of the one-more banner: while open, the star frame (+2072) cycles 0..9, the fade
//   (+2064) counts to 16 (back to 0 while flag 0x10 / 0x20), the star glow (+2068) to 10 while flag 0x40; then the
//   layout sub_25D130.
void sub_25D020(EEContext& ctx);
// 0x25D130 [bpRushLayout] Layout of the one-more banner: the banner quad at (41, 379) with alpha 255 * fade / 16, the seven
//   stars on a circle (cosf / sinf of the star frame, centre (35, 366) plus offsets) with the glow alpha.
void sub_25D130(EEContext& ctx);
// 0x25D470 [bpRushDraw] Draw of the one-more banner: while open, RW render states, the seven star quads (texture 1) and the
//   banner quad (texture 0) through the Im2D slot 0x96009C.
void sub_25D470(EEContext& ctx);
// 0x25F5D0 [sprSheetFillQuad] Fills an Im2D quad (4 vertices of 64 bytes) for cell a2 of a sprite sheet (+388, 128-byte
//   cells): the screen rectangle from sub_25FB60, near-screen z and 1 / camera z (sub_198590 +128), the four corner
//   colours (+100.. of the cell) scaled from 0..128 to 0..255.
void sub_25F5D0(EEContext& ctx);
// 0x25FC50 [sprSheetFillEdgeQuad] Fills an Im2D quad for one of the eight edge / corner pieces a3 of a sprite sheet cell (the
//   frame of a window): the rectangle from sub_260430, the corner colours picked from the cell's four (+100..+112) per
//   piece (a jump table), scaled to 0..255.
void sub_25FC50(EEContext& ctx);
// 0x260430 [sprSheetEdgeUv] Texture rectangle of one of the eight frame pieces a3 of a sprite sheet cell: the cell's texel box
//   (+84 / +92 x, +88 / +96 y) over its texture's size (the sheet's texture table +260 by the cell's +20), with the
//   half-texel inset per side and the cell's flip bits (+24: 1 mirror x, 2 mirror y); out u0, v0, u1, v1.
void sub_260430(EEContext& ctx);
// 0x260D20 [sflPselUpdate] Per-frame update of the persona-select panel (sfl_psel2.c, *$gp 0x7CE378; K_Assert line 87): while
//   open, the fade counter (+8) of either state (+4 0 / 1) counts to 10, then flag 2 clears; layout sub_261480.
void sub_260D20(EEContext& ctx);
// 0x260E00 [sflPselDraw] Draw of the persona-select panel: while open, RW render states and its quads (+784 / +16 background,
//   +1808 texture 58, +2064, +528, +272 by state, the card textures 52 / 53 / 54 at +1040 / +1296 / +1552) through the
//   Im2D slot 0x96009C.
void sub_260E00(EEContext& ctx);
// 0x262730 [brHeroRelease] Releases the result screen's hero panel (br_hero.c, *$gp 0x7CE37C; K_Assert line 83): closes it
//   (sub_2630E0) when open and clears the slot.
void sub_262730(EEContext& ctx);
// 0x2630E0 [brHeroClose] Closes the result screen's hero panel (K_Assert: open, line 410): frees its font line (+11088) and
//   clears flag 1.
void sub_2630E0(EEContext& ctx);
// 0x264DD0 [brPersonaRelease] Releases the result screen's persona panel (br_persona.c, *$gp 0x7CE380; K_Assert line 39):
//   closes it (sub_264F90) when open and clears the slot.
void sub_264DD0(EEContext& ctx);
// 0x264E30 [brPersonaOpen] Opens the result screen's persona panel for persona a0: stores the id (+8), creates the persona
//   status tasks (fclMisc_CreatePsStatusTasks) for the persona record (sub_1749A0), sets their persona / mode
//   (sub_3C9B00, sub_3C9CD0(-1), sub_3C9D00(8)) and flag 1.
void sub_264E30(EEContext& ctx);
// 0x264F90 [brPersonaClose] Closes the result screen's persona panel: destroys the status task tree (+4) and clears flag 1.
void sub_264F90(EEContext& ctx);
// 0x264FF0 [brPersonaGetTask] Returns the result screen's persona status task (+4).
void sub_264FF0(EEContext& ctx);
// 0x265C20 [opRootCreate] Creates the op root task (op_root.c): a 17,712-byte work (H_Malloc) behind a task of priority 10
//   (opRoot_UpdateOpTask, destructor sub_265EF0) with an 'op draw' child task, the sub-works' set-up (+32 / +128 / +416
//   / +4592 / +9072 opMenuSetWork / +17408), the screen fade (0, 0, 0, 255), the work into $gp slot 0x7CE388 (K_Assert
//   line 154), a clear colour {0, 0, 0, 255} (sub_272220 / sub_272290), the sound set-up (sub_1085C0, sub_108670(5),
//   sub_1086A0(10)), sub_266CB0 and flag 1. Returns the task.
void sub_265C20(EEContext& ctx);
// 0x265EF0 [opRootDestroy] Destructor of the op root task: the sub-works' releases, clears $gp slot 0x7CE388 and frees the
//   task's work (+60, H_Free).
void sub_265EF0(EEContext& ctx);
// 0x266710 [opResUpdate] Per-frame step of the op resource loader (op_res.c, *$gp 0x7CE394; K_Assert line 68): when the main
//   archive (+8, flag 1) is loaded, its 15 files become the texture set +68 (file 0, sub_21C9F0) and the sprite sheets
//   +12..+64 (sub_21EC40), flag 1 of +4 is set and the request destroyed; likewise the second archive (+72, flag 2)
//   gives +76 / +80.
void sub_266710(EEContext& ctx);
// 0x266EB0 [bpPersonaRegister] Registers the battle panel persona work (bp_persona.c, *$gp 0x7CE398; K_Assert: free, line 43):
//   clears its flags and stores it.
void sub_266EB0(EEContext& ctx);
// 0x266F00 [bpPersonaRelease] Releases the battle panel persona work: closes it (sub_267120) when open and clears the slot.
void sub_266F00(EEContext& ctx);
// 0x267180 [bpPersonaUpdate] Per-frame update of the battle panel persona work: while open and waiting (flag 2), clears flag 2
//   once its status task (+4) reports done (sub_3C9AB0).
void sub_267180(EEContext& ctx);
// 0x267260 [bpLoadCommonResources] Loads the battle panel's common resources: battle/panel/bs_init.bin (H_Cdvd_Request +
//   ReadSync), its files 0 / 1 as sprite sheets into $gp 0x7CE3A0 / 0x7CE3A4 and file 2 as a texture set into 0x7CE3A8;
//   destroys the request.
void sub_267260(EEContext& ctx);
// 0x267370 [bpGetCommonSheet] Returns battle panel sprite sheet a0 (0 / 1 / 2 of the words 0x7CE3A0..).
void sub_267370(EEContext& ctx);
// 0x267390 [bpGetCommonTextures] Returns the battle panel's common texture set ($gp 0x7CE3A8).
void sub_267390(EEContext& ctx);
// 0x268E20 [opTitleDraw] Draw of the op title panel (op_title.c, *$gp 0x7CE3AC; K_Assert line 142): while shown, RW render
//   states and its quads (textures 14 / 13 / 37 / 36 of the op texture set sub_266C50(0)), then for each of the nine
//   items with flag 1 (288-byte items from +1552) the highlight quad +528 (texture 17) and the item quad (texture 15)
//   through the Im2D slot 0x96009C.
void sub_268E20(EEContext& ctx);
// 0x269690 [im2dMeshCreateGrid] Allocates an indexed triangle mesh for a grid of a1 x a2 cells (RwMalloc slot 0x960178, hint
//   0x40000): kind 0 a plain grid ((a1 + 1) * (a2 + 1) vertices, 6 * a1 * a2 indices), kind 1 a staggered grid (odd
//   rows shifted half a cell, an extra triangle per row end); the header {vertices, indices, columns, rows, vertex
//   count, index count, kind} is followed by 64-byte vertices and the u16 indices.
void sub_269690(EEContext& ctx);
// 0x26C710 [opMenuDrawFrame] Draw of the op menu frame (op_menu.c, *$gp 0x7CE3B4; K_Assert line 135): while shown, RW render
//   states and its ten quads (op sheets 0..5 through sub_266BF0, one untextured triangle +2592) through the Im2D slot.
void sub_26C710(EEContext& ctx);
// 0x26CC90 [opMenuDrawItems] Draw of the op menu items: while shown, the title quad (texture 21) and, with flag 0x20 (the full
//   menu), the four items' three layers (textures 0 / 2 / 4 / 25, 6 / 7 / 8 / 27, 1 / 3 / 5 / 26; 784-byte items from
//   +2832) and the cursor (texture 34 + state +6736 at +5968 / +6224); otherwise the two short items (textures 28 / 30
//   and 29 / 31 from +6768).
void sub_26CC90(EEContext& ctx);
// 0x26E000 [opWaitDraw] Draw of the op wait screen (op_wait.c, *$gp 0x7CE3B8; K_Assert line 219): while shown, the background
//   quads (op sheets 6 / 7 / 8), the three logo layers (sheets 9..11 from +3664), the two bars (sheet 12), the two
//   indexed meshes +4464 / +4468 (drawIm2DIndexedTriList, sheet 13) and the texture-set quads 19 / 38 / 10 / 16 at
//   +2368..+3392.
void sub_26E000(EEContext& ctx);
// 0x271230 [opWaitRippleVertex] Vertex callback of the op wait screen's first mesh: moves vertex +16 of the mesh (+0) by a
//   ripple around (540, 348) -- the distance and angle (atan2f) of its screen point (640 x, 448 y of the mesh's u / v),
//   the screen's wave tables (sub_269C80 / sub_269CA0) -- and sets its texture coordinates, 1 / camera z and an alpha
//   of 255 times the fade (+4472 of the work +12).
void sub_271230(EEContext& ctx);
// 0x2716D0 [opWaitRippleVertex2] Vertex callback of the op wait screen's second mesh: the same ripple with the other wave
//   constants; colour 255 * the wave in r / g / b and alpha 204 * the wave times the fade.
void sub_2716D0(EEContext& ctx);
// 0x271C10 [opWaitSkipIntro] Skips the op wait screen's intro (K_Assert: flag 4, line 2046; state 0, line 2047): moves its
//   frame counters (+8 / +40) on to 220 and clears flag 8.
void sub_271C10(EEContext& ctx);
// 0x271CD0 [opFadeInit] Registers the op fade work ($gp 0x7CE3BC): a full-screen quad (0, 0, 640, 448) at +16, mode / frame /
//   length 0, colour {0, 0, 0, 255} (+272).
void sub_271CD0(EEContext& ctx);
// 0x271D70 [opFadeRelease] Releases the op fade work (op_fade.c; K_Assert line 31).
void sub_271D70(EEContext& ctx);
// 0x271DB0 [opFadeStartIn] Starts a fade in of the op fade work (mode 1, frame 0, flag 1).
void sub_271DB0(EEContext& ctx);
// 0x271E10 [opFadeStartOut] Starts a fade out of the op fade work (mode 2, frame 0, flag 1).
void sub_271E10(EEContext& ctx);
// 0x271E70 [opFadeIsActive] Whether the op fade is running (flag 1).
void sub_271E70(EEContext& ctx);
// 0x271EC0 [opFadeUpdate] Per-frame step of the op fade: counts the frame to the length (then clears flag 1) and sets the
//   quad's colour, alpha = colour alpha times t (mode 1), 1 - t (mode 2) or 0 (mode 0); t = frame / length (1 when the
//   length is 0).
void sub_271EC0(EEContext& ctx);
// 0x2721D0 [opFadeSetLength] Sets the op fade's length (+8) and mode 0.
void sub_2721D0(EEContext& ctx);
// 0x272220 [opFadeSetColour] Sets the op fade's colour (+272, 4 bytes).
void sub_272220(EEContext& ctx);
// 0x272290 [opFadeSetIn] Ends the op fade faded in (mode 1, frame = length).
void sub_272290(EEContext& ctx);
// 0x2722E0 [opFadeSetOut] Ends the op fade faded out (mode 2, frame = length).
void sub_2722E0(EEContext& ctx);
// 0x272380 [brpSeqRelease] Releases the result screen's persona sequence work (brp_seq.c, *$gp 0x7CE3C0; K_Assert lines 176 /
//   200): closes its message window (sub_3C77A0) when it holds one (flag 0x80) and clears the slot.
void sub_272380(EEContext& ctx);
// 0x272400 [brpSeqStart] Starts the result screen's persona sequence for one persona (K_Assert: not running / no 0x2 / 0x10 /
//   0x20, lines 214..217): copies the persona id and owner (+4 / +8 from a0), opens the message window once (flag
//   0x80), takes the persona record (sub_1749A0; K_Assert line 232 when not valid), its stats (+56), the persona table
//   row (*0x7CE428 + 70 * id), its skills (+96, count +116), the experience bar (sub_1FB4B0 from the level over the
//   base level), the stat raise list (sub_274F00), the level-up flag 0x10 (sub_2741F0), the first and last raised stat
//   (+40 / +44 of the five stat bytes +90), the new skills (+448 count, 8-byte entries from +452: skill, level), the
//   first stat step (sub_279660) and the step list (sub_274C00); flags 0x100 | 1.
void sub_272400(EEContext& ctx);
// 0x2727C0 [brpSeqIsRunning] Whether the result screen's persona sequence is running (flag 1).
void sub_2727C0(EEContext& ctx);
// 0x273800 [brpSeqNextStep] Next step of the result screen's persona sequence (brp_seq.c): from the step +16, skips the steps
//   that do not apply -- 2 the new skills (sub_273C00 when +436 is set), 3 the skill changes (sub_2743A0 applies the
//   learned skills, sub_274590 rolls a skill power-up; sub_273D50 when flag 0x20), 4 the level-up evolution (sub_273C70
//   when flag 0x10); any other step K_Asserts (lines 923 / 927) -- and at step 5 applies the pending change
//   (sub_273A10) and finishes (sub_273980).
void sub_273800(EEContext& ctx);
// 0x273A10 [brpSeqApplyChange] Applies the pending skill change of the persona sequence: with flag 8, the skill +132 of a kind
//   4 (sub_171250) raises the counter sub_170760(1, skill) by one (at most 99, sub_170860), kinds 0..3 add the item
//   record +136 (sub_1830C0); clears flag 8; with flag 4 sub_274030.
void sub_273A10(EEContext& ctx);
// 0x273B30 [brpSeqShowStatRaise] Shows the stat raise message of the persona sequence: the raised stat's name (the table
//   0x68ED70 by the stat index +40) and its new value ("%d" of the stat byte +90 + index) into message slots 0 / 1,
//   message 1, sound (1, 0, 8, 1); +36 = 0, step 2.
void sub_273B30(EEContext& ctx);
// 0x273E90 [brpSeqSyncSkills] Applies the learned skills of the persona sequence to the persona record: every skill the record
//   now has that the saved list (+96, count +116) lacks is added (sub_1768E0), every saved skill the record lacks is
//   removed (sub_176840).
void sub_273E90(EEContext& ctx);
// 0x2741F0 [brpSeqCanEvolve] Whether the persona of the sequence evolves now: no when the owner word (+8) has bit 1 or the
//   persona flags lack 4; with persona flag 8, no when the counters sub_1756F0 / sub_175410 are equal (K_Assert line
//   1140 when the first is larger); otherwise no when sub_16F490(1) is 300. Yes when an entry of the persona's learn
//   list (the table row +6, 16 entries {u8 level, s8 kind, u16 id}) of kind 4 has a level at most the persona's level
//   over its base level.
void sub_2741F0(EEContext& ctx);
// 0x2743A0 Persona sequence step wrapper of brpSeqSyncSkills (K_Assert line 176).
void sub_2743A0(EEContext& ctx);
// 0x2743E0 [brpSeqCollectSkills] Collects the persona's skills after the level-up: the record's skills (sub_173370 /
//   sub_176A30) plus the learn-list skills (kind 1) from the next entry (+120) on (K_Assert lines 1212 / 1220 / 1228
//   for kinds 2 / 3 and an overflow of 16); out the list and its count.
void sub_2743E0(EEContext& ctx);
// 0x274590 [brpSeqRollSkillUpgrade] Rolls the result screen's skill power-up / change ("skill power up change check", printf
//   trace): only when the protagonist's level (sub_16C470(1)) is over 10 and a roll (sub_488F30 % 100) is under 12; a
//   second roll picks power-up or change first: a power-up replaces a learned skill by its upgrade from the table
//   *0x7CE438 ({u16 from, u16 to} pairs, 0 ended) that the persona does not have yet; a change replaces a learned skill
//   by a random other skill of the same rank + 1 (the 624-byte rank table sub_3D5C90). The choice goes to +160 (old) /
//   +162 (new) / +156 (0 power-up, 1 change) with flag 0x20.
void sub_274590(EEContext& ctx);
// 0x274C00 [brpSeqFillPanel] Fills the persona sequence's parameter panel: the skill names (sub_2791B0 for each saved skill),
//   the evolution / next-skill lines when there are any (sub_274D40..sub_279450), the experience line, and per stat (5)
//   its value and raise (sub_173580, sub_279510 / sub_279580 / sub_2795F0).
void sub_274C00(EEContext& ctx);
// 0x274F00 [brpSeqCountNewSkills] Counts the new skills the persona learns at this level-up: the learn-list entries from +120
//   (+124 of them) of kind 1 whose skill the persona does not have (kind 4 skipped, others K_Assert line 1554).
void sub_274F00(EEContext& ctx);
// 0x275050 [brpSeqGetNewSkill] Returns the learn-list entry of the persona sequence's a0-th new skill (K_Assert a0 < +448,
//   line 1592; lines 1604 / 1627 for a bad kind or the end of the list).
void sub_275050(EEContext& ctx);
// 0x2751E0 [brpSeqCountPendingSkills] Counts the skills still to learn after this level-up: learn-list entries of kind 1 above
//   the persona's level over its base level and its level gain (+56), not known yet (K_Assert line 1670 for other
//   kinds).
void sub_2751E0(EEContext& ctx);
// 0x275370 [brpSeqIsPanelUp] Whether the persona sequence's panel is up (flag 0x100).
void sub_275370(EEContext& ctx);
// 0x2753C0 [brpSeqShowLevelUp] Shows the persona sequence's level-up message: opens the level panel (sub_2767E0), the
//   persona's name into message slot 0, message 0; +20 = 0, step 1.
void sub_2753C0(EEContext& ctx);
// 0x275A80 [brLvPanelUnregister] Clears the result screen's level panel slot ($gp 0x7CE3C8).
void sub_275A80(EEContext& ctx);
// 0x275CB0 [brLvPanelDraw] Draw of the result screen's level panel (br_lvpnl.c, *$gp 0x7CE3C8; K_Assert line 59): while shown
//   and not hidden (flag 8), RW render states and its quads (textures 11, 0, 2, 1, 3 of sub_234630(0)) through the Im2D
//   slot.
void sub_275CB0(EEContext& ctx);
// 0x2767E0 [brLvPanelOpen] Opens the result screen's level panel: mode +1556 (1 when flag 4 was set, else 0 and flag 4), frame
//   +1552 = 0, flag 2.
void sub_2767E0(EEContext& ctx);
// 0x276920 [brpPersonaUnregister] Clears the result screen's persona status slot ($gp 0x7CE3CC).
void sub_276920(EEContext& ctx);
// 0x276930 [brpPersonaUpdate] Per-frame update of the result screen's persona status (brp_persona.c, *$gp 0x7CE3CC): while
//   open and waiting (flag 8), clears flag 8 once the status task (+4) is done (sub_3C9AB0).
void sub_276930(EEContext& ctx);
// 0x2769C0 [brpPersonaOpen] Opens the result screen's persona status on task a0 for persona a1: the persona record
//   (sub_1749A0) into the task (sub_3C9BA0), mode 8 and -1 (sub_3C9D00 / sub_3C9CD0), the id (+8) and task (+4), flags
//   8 | 1.
void sub_2769C0(EEContext& ctx);
// 0x276BA0 [brpPersonaClose] Closes the result screen's persona status (K_Assert open, line 107): task mode 2 and flag 2.
void sub_276BA0(EEContext& ctx);
// 0x276D30 [brpParamRelease] Releases the result screen's parameter panel (brp_param.c, *$gp 0x7CE3D0; K_Assert line 97):
//   closes it (sub_277070) when open and clears the slot.
void sub_276D30(EEContext& ctx);
// 0x276D90 [brpParamOpen] Opens the result screen's parameter panel (K_Assert not open, line 132): the window quads from
//   sprite sheets 8 / 10 (sub_119A60; sub_25F5D0 / sub_25FC50 cells 18..27), the five stat rows (1,824 bytes from
//   +2192: frame cells, the stat number in the digit font), the texture quads 1 / 0 / 0 of sub_234630(1), the level
//   number (+14132 at +14160), counters cleared, the layout sub_2771F0; flags: 0x41 cleared then 1 set.
void sub_276D90(EEContext& ctx);
// 0x277070 [brpParamClose] Closes the result screen's parameter panel: frees its skill name lines (sub_279120, +14136 of them)
//   and the extra line (sub_2792C0, flag 2), clears flag 1.
void sub_277070(EEContext& ctx);
// 0x2770F0 [brpParamUpdate] Per-frame update of the result screen's parameter panel: while open, the slide (+14140) counts to
//   20 with flag 4 (then flags 4 / 8 clear), the blink frame (+14144) cycles 0..9, the flash (+14148) counts to 30 with
//   flag 0x10; layout sub_2771F0.
void sub_2770F0(EEContext& ctx);
// 0x279120 [brpParamFreeSkillLines] Frees the parameter panel's skill name lines (272-byte rows from +272, +14136 of them) and
//   zeroes the count.
void sub_279120(EEContext& ctx);
// 0x2791B0 [brpParamAddSkillLine] Adds a skill name line to the result screen's parameter panel: the skill's name (19-byte
//   rows of *0x7CE4EC) as a glyph list at (1600, 800) (sub_3B2C60) into the next 272-byte row (+16 + 272 * count, the
//   line at +256); count +14136 + 1.
void sub_2791B0(EEContext& ctx);
// 0x2792C0 [brpParamFreeExtraLine] Frees the parameter panel's extra line (+14672) when flag 2 and clears flag 2.
void sub_2792C0(EEContext& ctx);
// 0x279330 [brpParamSetExtraLine] Sets the parameter panel's extra line (K_Assert: not set, line 992): the skill's name as a
//   glyph list at (1600, 800) into +14672, flag 2.
void sub_279330(EEContext& ctx);
// 0x279660 [brpParamMarkStatRaise] Sets flag 8 of the result screen's parameter panel (the stat raise is pending).
void sub_279660(EEContext& ctx);
// 0x27B5B0 [bpSelectRegister] Registers the battle select work ($gp 0x7CE3E4): flags 0, the two scale words +276 / +280 =
//   100.0.
void sub_27B5B0(EEContext& ctx);
// 0x27B5D0 [bpSelectRelease] Releases the battle select work (bp_select.c; K_Assert line 39).
void sub_27B5D0(EEContext& ctx);
// 0x27BBA0 [sflPersonaRelease] Releases the shuffle-time persona panel (sfl_persona.c, *$gp 0x7CE3E8; K_Assert line 41):
//   closes it (sub_27BDF0) when open and clears the slot.
void sub_27BBA0(EEContext& ctx);
// 0x27BE50 [sflPersonaUpdate] Per-frame update of the shuffle-time persona panel: while open, once the status task (+4) is
//   done (sub_3C9AB0) flag 2 becomes flag 4 (counter +12 = 0); flags 4 and 8 each run the counter to 5 and clear.
void sub_27BE50(EEContext& ctx);
// 0x27F940 [btlUnitGetEffectPoint] Point and rotation of a unit's weapon / hit point a6 (a7 the point kind): kind 2 (a ranged
//   point): the target unit a2's centre (sub_2802D0), its distance from a0's hit point (sub_2812D0) + 50 along the
//   facing from a1 to it (sub_2D1DE0, the forward / side axes 0x6978A0 / 0x697870) with the model's offset (88-byte
//   rows of *0x7CE42C by the unit's model +164, times the scale +44), y 0; other kinds: the unit a1's rotation (+28)
//   and its position lowered by half its height plus the model's point a7 (6-byte offsets at +12) through the rotation
//   (sub_4BE1E0). Out point a4 / rotation a5 (either may be 0).
void sub_27F940(EEContext& ctx);
// 0x2802D0 [btlUnitGetCentreFacing] Centre of unit a0 seen from unit a1: the facing from a1 to a0 (sub_2D1DE0) applied to a0's
//   centre offset (+128, times the scale +44) plus a0's position.
void sub_2802D0(EEContext& ctx);
// 0x280390 [btlUnitGetModelPointFacing] Point 9 of unit a0's model (sub_288DA0(a0, 9), times the scale) through the facing
//   from a1 to a0, plus a0's position.
void sub_280390(EEContext& ctx);
// 0x280480 [btlUnitGetCellCentreFacing] Centre of unit a0's grid cell seen from unit a1: the facing rotation of a0's centre
//   offset (times the scale) added to the cell's centre (25 * cell - 1750 for x / z, the position's y).
void sub_280480(EEContext& ctx);
// 0x280DA0 [btlUnitWalkStep] Walk step of a unit along its path: while walking (+200 flags 1 | 0x10) it advances over the path
//   points (+244.., 8-byte x / z, +1260 count, +1262 next) by its speed (+204), stopping short by +232 at the end (or
//   jumping there with +196 bit 1), writes the new position (+4..+12, dirty flag 4 of +152), the next index and the
//   look-at point (+208); then, while turning (+200 bit 2, not with +156 bit 0x2000), turns its rotation (+28) toward
//   the look-at point (atan2f, sub_4BDDE0 about the y axis 0x697880), at once when the angle is under the limit
//   0x7CB0B8 or +196 bit 2. Returns 0.
void sub_280DA0(EEContext& ctx);
// 0x281AD0 [btlPktPlaceAtUnit] Packet callback: places an effect packet at its unit (the data block's +36) on its first frame
//   (+24 == 0) -- with the unit's +156 bit 0x2000 (a fixed unit) its centre or model point 0 (flag 0x40 of +16) through
//   the unit's own rotation, pushed forward by +28 along its facing (0x697890), then +28 cleared; otherwise the same
//   point through the facing toward the packet's other unit (+0) -- into +4..+12; then the common step sub_2813F0.
void sub_281AD0(EEContext& ctx);
// 0x2823B0 [btlPktTurnToward] Packet callback: turns a unit (+0) toward a target (+4: a unit, or with +8 bit 0x20 its cell
//   centre) on the first frame -- with +8 bit 2 at once (atan2f, sub_4BDDE0 about y; not for a fixed unit, +156 bit
//   0x2000) and the motion refresh sub_288110, else by setting the look-at point (+208; sub_27F7C0 for a cell) and the
//   turn flags (+196 |= +8, +200 bit 2). Counts frames in +12 while turning; returns 1 when done.
void sub_2823B0(EEContext& ctx);
// 0x2826D0 [btlUnitIdleMotion] Idle motion step of a unit with a live model (+152 bit 2): plays the model (sub_3189F0) unless
//   a loop count (+2522 / +2524, flag 4 of +2508) holds it; when idle and not pinned (flag 8), restarts the wait motion
//   (+2528, blend +2536) or motion 1 when it walks; then per idle kind (+2512): 0 a wait motion change (sub_2F9560, the
//   pending motion +2530, the 10-byte motion rows +2540 for waits 17 / 13 / 3), 3 stop at the motion's end, 4 / 5 / 6 /
//   7 the motions 13 / 15 / 24 / 25 once the model is ready (+238 == 1). Clears flag 8.
void sub_2826D0(EEContext& ctx);
// 0x2831C0 [btlUnitPickWaitMotion] Picks a unit's wait motion from its state: 17 at low HP (when the model has it, sub_318620
//   / sub_3186E0), 3 with any bad status of 0xFFEFF, 9 with 0x100000, 18 when dead and +156 bit 0x20 (if the model has
//   it); the blend kind (2 for 18, else 1), the pending motion (+2530, 0 for 18), the motion speed (+2532: 2.0 or 3.0
//   for the status 0x100 by sub_17D800, 0.5 for 0x20, else 1.0); a party / enemy unit (+162 0 / 1) already in its wait
//   motion switches to the new one (sub_282D40, a1 the frames).
void sub_2831C0(EEContext& ctx);
// 0x284E10 [btlPktPlayMotion] Packet callback: restarts the unit's (+0) current motion (+2510) with the data block's u16 +4
//   (frames) and +12 (blend) through sub_282D40, the model layer 4 and play state held around it (sub_287CF0 /
//   sub_287B20, sub_318990 / sub_318770) while the model is live; returns 1.
void sub_284E10(EEContext& ctx);
// 0x2850F0 [btlPktLoadModel] Packet callback: loads a unit's model (+0 the unit, u16 +4 / +6 the model major / minor, +8
//   flags, +12 the file request): takes it from the model cache (sub_316910 / sub_317450) or requests the file
//   (sub_31D530 path, H_Cdvd_Request); once loaded builds the model (sub_316C70; sub_31C1D0 for major 1) and, when
//   ready (sub_316F70), with flag 4 attaches it by the unit kind (+162: 2 a persona -- flags of sub_17C0E0, 1 an enemy
//   -- the 232-byte enemy model rows *0x7CE418, 0 a party member) and its motion handle (+2546); then the model-live
//   flags (+152: 1 off, 2 on), the flag-requested extras (8: +51 = 0, 1 / 2 sub_287B20, 0x100 the colour, 0x40
//   sub_2D3E00, 0x20 the wait motion at a random frame), destroys the request. Returns 1 when done.
void sub_2850F0(EEContext& ctx);
// 0x285750 [btlPktDropModel] Packet callback: drops a unit's model -- the motion handle (+2546, sub_3B7090) or the model
//   (sub_3174E0) -- clears +2548 and the model-live flag 2, sub_287510; returns 1.
void sub_285750(EEContext& ctx);
// 0x287740 [btlUnitReleaseModel] Releases a unit's model: with a motion handle (+2546; its kind (handle >> 10) & 0x3FF) the
//   handle (sub_3B7090), the model's four layers off (sub_287CF0 4 / 1 / 2 / 3), its colour reset (sub_318AD0 with
//   0x7CC970), one more play step, and the model itself for kind 1 unless kept (+152 bit 8); otherwise only the model
//   (sub_3174E0); clears +2548 and the model-live flag 2.
void sub_287740(EEContext& ctx);
// 0x2878D0 [btlUnitDestroy] Destroys a battle unit: releases its model (sub_287740), its child unit (+2560, recursively), its
//   two effect handles (+2552 sub_2BBD00, +2556 sub_2BB8F0), its grid record (sub_2D3FE0) and its slot (+2544 >= 0,
//   sub_2B7000); unlinks it from its side's list (+2608 / +2612, the list heads gBtl +336 / +340 + 8 * side) and frees
//   it (RwFree slot 0x96017C).
void sub_2878D0(EEContext& ctx);
// 0x289B50 [btlPartyIdleGlances] The party's idle glances: for each active action (+26 bit 1) -- enemies through sub_2FD8A0 --
//   a party member with +156 bit 8 that is idle (sub_282C60), not moving (sub_281270), healthy (no bad status 0x100000
//   / 0xFFFFF, not low HP, alive) and in state 1 / 5 / 6 while the battle allows it (gBtl +12 bit 0x10000) counts its
//   glance timer (+54) down; at 0 (and not the acting a0, not model 4) it looks around: a point 5..15 (sub_358030)
//   degrees off its facing at its look distance, a turn packet (sub_2819D0, 8) and a look-back packet (sub_2822B0, kind
//   4), and a new wait of 60 + datCalcRand(180) frames.
void sub_289B50(EEContext& ctx);
// 0x28CDA0 [btlActionCheckTactic] Action step: a party member whose tactic (DatUnit +16) is 7 (the 'act freely' AI) loses it
//   when the command check sub_2C08C0 fails -- tactic 1 and voice packet 11 (sub_2E2BE0) -- then the command block's
//   update sub_2D15A0 (+56).
void sub_28CDA0(EEContext& ctx);
// 0x28D5A0 [btlActionStateTurnStart] Action state 'start of turn' (unless the events 1286 / 261 run, sub_27E470): the turn's
//   status upkeep (sub_28A780); a unit not down (0x100000) or already rising (+1160) runs its status effects
//   (sub_2DC180: the packets 9 / 22 / the status damage sub_2D7E20 / the tactic reset 0x200 / the recovery sub_2DCA60)
//   or, when a status blocks the turn (+1156, the statuses 0x279: sub_2D1660, the HP / SP recovery sub_2DC830, voice
//   30), goes to state 12 (a sleep of 0x10 also sets the wake counter +41 = 2 + datCalcRand(1)) or waits 1 frame in
//   state 3; otherwise state 25 / 30 (sub_2DC130). A downed unit rises: with skill 3 (sub_3005A0) a 30 % (10 % with
//   flag 4889) chance to stay down (voice 162 / 163 and 21), else the rise packets (10 / 8 / the status clear 0x100000
//   / sub_284C90 / voice 20); then the turn-start packets and +1156 = 0, +1160 = 1.
void sub_28D5A0(EEContext& ctx);
// 0x28DBF0 [btlActionStateCommand] Action state 'command chosen' (unless event 1286 runs): waits while a target (the command
//   block's +106 targets at +56) other than itself is still acting; then releases the targets (sub_2D15E0 unless +24
//   bit 4) and by the command kind (+108): 1 / 2 / 3 / 9 apply the action (sub_2D6620) and go to state 30 (a skill of
//   type 10, gBtlSkillTbl 44-byte rows +36), 21 (a pending +216), 13 or 14 (sub_289F40); 5 state 24; 6 state 26 (27 for
//   an enemy or model 1); 7 / 8 / 11 state 23; 10 state 7; 12 state 27; others K_Assert line 2796. Flag 8 of +24 = an
//   attack command that sub_28A3E0 accepts.
void sub_28DBF0(EEContext& ctx);
// 0x297A60 [btlActionStateAllOutStart] Action state 'all-out attack' set-up: the leader -- the acting party member, or an
//   enemy's first target, when listed among the all-out members (gBtl +2952, +2968 of them), else a random member
//   (datCalcRand) -- its voice / cut-in packet (sub_2E38A0 by its model +164); the navigator's line (gBtl +328:
//   sub_2886E0 / sub_288950); for a party leader with a pending one-more (gBtl +2616 != -1, more than half the enemies
//   active, not the current id sub_2B7060) the rush packets (sub_2B8F40, a run packet 24 for every member not down /
//   dead), otherwise the camera packets (sub_2B8D60 2 / 1; a walk-in when the member is over 75 units from its spot);
//   during a rush (gBtl +12 bit 0x400000 with +24 bit 2) every active member's packet sub_2843E0; then the attack
//   packets (sub_2A1DB0, sub_2A3B40 6), clears the rush bits, sub_2D1A70 == 1 clears gBtl +12 bit 0x4000 (sub_1FF350);
//   +1156 = the leader, +1160 / +1164 = 0, +1168 = 18.
void sub_297A60(EEContext& ctx);
// 0x2984E0 [btlActionAllOutHit] Action step of the all-out attack: command kind 2 with skill 319 + the member count (gBtl
//   +2968), targets from sub_2BFF60 copied into the command block, applies it (sub_2D6620); when no target is left
//   alive (+208 of each) the finishing skill 331 + count and +1176 = 1.
void sub_2984E0(EEContext& ctx);
// 0x299270 [btlActionStateEnd] Action state 'end of action' (not once the battle ended, gBtl +12 bit 0x80): with an extra turn
//   (+24 bit 8 and sub_28A200) goes to state 28 unless the events 1284 / 1286 run; otherwise counts the turn (+32, not
//   for +24 bits 0x8004), checks the battle end (btlMainCheckBattleEnd -> gBtl bit 0x80), runs the turn-end upkeep
//   (sub_29ABE0; the down / dizzy counters +40 / +41 with sub_29AC70, sub_302D40 and sub_2DAE30); then a dead unit at
//   the battle end gets its spoils (sub_2D7560) and state 1, an escaping unit (+24 bit 0x20: sub_29A320; an enemy is
//   marked 0x80000 with HP 0) state 34, else state 32.
void sub_299270(EEContext& ctx);
// 0x299B00 [btlActionStateRemove] Action state 'remove': an action whose unit is active and not held (+160 == 0) removes it --
//   a dead enemy from the encounter (datUnitEcRemoveEnemy on gBtl +3004), an escaping party member's setup record (gBtl
//   +2988 [4] / +3012 [3]: flag 1 of +10 cleared), its bad statuses but 0x80080 (datCalcClearBadStatus) and effects,
//   the tactic 10 reset to 1 -- destroys the unit (sub_2878D0), clears the active flag, sub_1FDD40; then sub_299E50,
//   sub_2A3A90 and flag 2 of +26 (removed).
void sub_299B00(EEContext& ctx);
// 0x29DFC0 [btlSceneCopyLights] Copies the scene's lights into gBtl: the ambient / directional colours and directions
//   (sub_19FD40 / sub_19FD70 / sub_19FDA0 -> +404 / +420 / +436 matrix; sub_1A09D0 / sub_1A0A10 / sub_1A0A50 -> +452 /
//   +468 / +484, copied to +500), the two RGBA scale words 0x7CC970 / 0x7CE4F8 as floats (times the constant at
//   0x7CAF08) into +548 / +564, the camera (sub_198590, sub_4C9D70) and gBtl +12 |= 0x2000002.
void sub_29DFC0(EEContext& ctx);
// 0x29EE20 [btlUnitUpdateLight] Per-frame light of a unit's model (gBtl +12 bit 2, a motion handle +2546): a persona (+162 ==
//   2) gets the fixed light 0x693850 / 0x693860 and the y-rotation matrix; a party member / enemy gets a light pointing
//   from its light point (+84, at least 5 above its centre) to its centre (sub_27FFB0), the orthonormal frame built
//   with cross products (the up axis 0x697880) and its light colour (+112) into the handle's light (sub_1A07F0 /
//   sub_1A08E0).
void sub_29EE20(EEContext& ctx);
// 0x29FAA0 [btlLightFadeStep] Light fade step of a scene light change (gBtl +12 bits 2 and 0x2000000; a0 the fade record): on
//   the first frame (+100 == 0) saves gBtl's current light colours (+548 / +452 / +468) as the start, writes the light
//   matrix from gBtl's quaternion (+436, the global light 0x957270, valid word 0x9572D0) and, unless +104 bit 4, sets
//   every live model's light flags (+904 |= 0x16; +937 / +938 = 0 / 6 with +104 bit 1, else 80 / 4; +940 / +944); then
//   blends the colours from the start to the target (+0 / +32 / +64) over +96 frames (t = +100 / +96) into gBtl and the
//   scene (sub_19F8F0). Returns 1 when done (or not lit).
void sub_29FAA0(EEContext& ctx);
// 0x2A46E0 [btlCameraUpdate] Per-frame battle camera step (from btlUpdateTask): unless held (gBtl +244 bit 1), after the wait
//   (+252) runs the shot's callback (the shot table sub_2F8840 or the default rows 0x6939F0, 20 bytes by the shot id
//   +240) on the camera block (+32) and sub_2A31B0, counting frames (+248); builds the camera matrix from its
//   quaternion (+200..+212) and position (+188..+196) into the RW camera (sub_198590, sub_4CB7F0, sub_1A4580); with
//   +244 bit 2 the shake sub_2A4330.
void sub_2A46E0(EEContext& ctx);
// 0x2A4C70 [btlCamShotShoulder] Camera shot 'over the shoulder' of the acting unit (the shot's action +224): eye behind /
//   beside the unit's centre by its size (+144 * scale; 2.5 or 1.5 times over the tangent of the view angle), looking
//   at the target point (sub_2A4470 of +156), the look rotation (sub_2A4690) limited to the shot's turn angle a1 (times
//   the constant at 0x7CAE1C; a too-wide turn ends the shot -- sub_2B6460, sub_351BB0(8) -- except for the shot kinds 2
//   / 35 / 31 / 29 / 28) by a slerp (sub_4BE310 and a sine series), the heights kept at 100 or more; sets the camera
//   (sub_2A2290) and its frame (sub_2A3110).
void sub_2A4C70(EEContext& ctx);
// 0x2A5430 Camera shot callback: the shoulder shot (sub_2A4C70).
void sub_2A5430(EEContext& ctx);
// 0x2AD680 [btlCamShotPickVariant] Camera shot callback: picks the shot variant (sub_2A7830 into +272) -- 1 the shoulder shot,
//   2 / 4 sub_2AC920, 3 / 5 sub_2ACF90, 6 sub_2A79F0 (each with 1).
void sub_2AD680(EEContext& ctx);
// 0x2AE150 [btlCamShotFollow] Camera shot callback: computes the eye / target (sub_2ADD10; avoiding the units except for the
//   shot kinds 35 / 2 / 34 / 29 of gBtl +260); when that fails ends the shot (sub_351BB0(8), sub_2A3E80 mode 64,
//   sub_2A2170 toward the target), else sets the camera (sub_2A2290, sub_2A3110).
void sub_2AE150(EEContext& ctx);
// 0x2B2060 [btlCamShotSingleTarget] Camera shot callback for a single-target action (the shot's action +224 with one target
//   +256 that is its first, still active): steps the scripted path (sub_2B6BD0 / sub_2B64D0 on +236) and, at the path's
//   key kind (sub_2B6CD0 +28), either holds (kind 1: mode 129 when +276, +272 = 1) or looks at the target (sub_2A3E80
//   mode 3 after a hold or 51; at the target's position unless it is dead), +272 = 0.
void sub_2B2060(EEContext& ctx);
// 0x2B58F0 [btlCamShotNavigator] Camera shot callback 'navigator view': frames the whole party (sub_280870 of side 3 into a
//   centre) and the navigator's unit (gBtl +328's unit, sub_280050), the eye a quarter of the way along and back by the
//   view angle's tangent and turned about the axis 0x697870 (sub_4C31B0 / sub_4C6C60), the look rotation sub_2A4690;
//   mode 64 (sub_2A3E80), both points through sub_2A3590, then the camera (sub_2A2290, sub_2A3110).
void sub_2B58F0(EEContext& ctx);
// 0x2B64D0 [btlCamPathStep] Steps a scripted camera path between two units (a1: the units +0 / +4, the key table +16 with its
//   count at +0 and 60-byte keys from +4, the key +10, its frame +12, flags +14): while running (sub_2B6BD0) and both
//   units have models (sub_29A1D0), each key past its length takes the next one: the eye and target offsets (mirrored
//   in x with flag 2) through the facing between the units (sub_2D1DE0; their centres with flag 0x10) relative to the
//   first unit (key kind 1), or toward the second unit's head / big-body point (kind 2, sub_2FC520 / sub_280200 /
//   sub_280130; height clamped to 100..250 / 150 by flags 8 / 4), the roll (key +56), then the camera (sub_2A2290,
//   sub_2A3110); past the last key clears flag 1. Returns 1 while it runs.
void sub_2B64D0(EEContext& ctx);
// 0x2B7060 [btlFormationPick] Picks the battle formation for the current units (btlFormation.c): -1 when the encounter is
//   fixed (sub_2FA240 == 1); counts the enemies by size (sub_2B6DE0: small / medium / large), K_Abort with
//   "FORM:%X[L:%d M:%d S:%d]" (sprintf) when too many large / medium ones; then the first of the 24 formations
//   (224-byte rows of 0x694F10) whose limits (+216 small, +218 medium, +220 large) hold them all, else 23.
void sub_2B7060(EEContext& ctx);
// 0x2B71E0 [btlFormationPlaceUnits] Places the units on the battle field by formation (btlFormation.c): gBtl +2616 = -1;
//   unless the encounter is fixed (sub_2FA240 == 1) checks the enemy sizes (K_Abort "FORM:%X[L:%d M:%d S:%d]" when too
//   many large / medium) and picks the formation (sub_2B6F70); then clears the slot words (gBtl +2620, 9 words), puts
//   the party (side 0 list +336: the navigator's unit in slot 0, the others in the next party slots with a flag byte)
//   and each living enemy (side 1 list +344: the free enemy slot whose size limits +112 / +116 fit it best) on their
//   formation cells (24-byte slots, sub_2D2280 to grid cells, the cell centres 25 * cell - 1750, sub_27F650), marks the
//   used slots (+2620 party / +2636 enemies) and the units' slot bytes (+2544); turns the party (list +340) toward the
//   enemies' centre (sub_280870) and the enemies (list +348) toward the navigator (sub_27F680); stores the formation
//   (+2616) and the active enemy count (+2618).
void sub_2B71E0(EEContext& ctx);
// 0x2C6300 [btlAiPickFusionSkill] AI pick of a fusion-spell (combination) skill for a party member (btlAICommand.c): kind 16
//   goes to the skill picker sub_2C59D0; otherwise only party members 2..10 qualify: each of the member's 12
//   social-link / fusion slots (sub_170670) holding a skill 0xFA1..0x107F whose base skill (sub_30BC20, < 0x1D0) has
//   the element a2 (datCalcGetSkillElement), is usable (sub_1706C0 > 0) and passes the element filter (sub_2C2ED0) is a
//   candidate; the target pick sub_2C4A90 over the candidates (run twice when a3 is 0 and the first fails -- or once
//   more after a failure with a3 == 1). Returns the skill or -1.
void sub_2C6300(EEContext& ctx);
// 0x2D1210 Battle event callback: when the event check sub_2D1A70 says 1, clears gBtl +12 bit 0x4000 and closes the analysis
//   view (sub_2D1A10); returns 1.
void sub_2D1210(EEContext& ctx);
// 0x2D1A10 [btlCloseAnalysisView] Closes the battle's analysis view: when gBtl +12 has bit 0x2000, clears it, plays sound (0,
//   15, 0, 4) and sub_1FF330.
void sub_2D1A10(EEContext& ctx);
// 0x2D1AC0 [btlAnalysisViewPad] Pad check for the analysis view (from btlUpdateTask): not after the battle end (gBtl +12 bit
//   0x80) and only when allowed (sub_2FD7C0) and enabled (bit 0x4000): with the view open (0x2000) the pad bits 0x10 /
//   0x20 (gPadFlags or 0x7E0958) close it (sound 4, sub_1FF330); closed, bit 0x10 opens it (sound 3, sub_1FF310).
void sub_2D1AC0(EEContext& ctx);
// 0x2D1DE0 [btlFacingRotation] Facing rotation from point a1 to point a2 on the ground plane: a quaternion about the y axis
//   (0x697880, sub_4BDDE0) by atan2f of the x / z difference (when the points differ).
void sub_2D1DE0(EEContext& ctx);
// 0x2D6620 [btlActionResolveSkill] Resolves an action's skill on its targets (the hit and damage pass): the skill (+110; a
//   replacement from sub_2D5570 is stored back, the original in +114, the AI record redone by sub_2C3770), item use
//   (kind 3 with an item) as flag 1; clears the action's and every target's result block (+200..+222); a magic skill
//   the user cannot cast (sub_3086F0 1 / 2: not enough SP / HP, voice 58 / 59 or 60 / 61) or an enemy under status 4
//   (voice 62 / 63) fails (+216 = 1). Otherwise the user moves to the end of its own target list and for each target:
//   the hit check (datCalcCheckHit; 512 = reflected: checked again on the user, +212 = 1), the affinity result
//   (sub_30A740, or 1 / 16 for a reflection by effect state 11), the hit count (a physical skill: 1 hit, the weapon
//   rate row *0x7CE484 + 3 * weapon type + rank - 1 in percent from sub_308FD0; magic: sub_30B9A0), the knock-down /
//   critical / guard checks (sub_30B130 / sub_30B210 / sub_2FD220), the status results (sub_306020 / sub_306510), then
//   per hit the HP and SP damage (datCalcDamage kinds 1 / 2, HP times the weapon rate), their absolute values for the
//   drain types 12 / 13, the extra damage (skill +32 on a plain hit not blocked by sub_2E4910), the element, the hit
//   flags (+250: 0x80 / 0x20 skill types 9 / 6, 0x200 skill 294, 0x100 skills 293 / 295 / 296, 0x40 skill flag 1, 8
//   skill type 0x10, 1 / 2 a down, 4 a critical, 0x10 a revival) and the per-hit result (sub_2D6460) in the 28-byte hit
//   records from +224, until the target dies; the analysis record (sub_2E32A0) on a reflection or 0x500 result; the
//   voice line (sub_2D56A0 or the units' +56). Ends with the action's motion (+222, sub_2D5B50), the one-more voice
//   (sub_2E47A0 / sub_2E4720) and the summary flags +202 (1 every target knocked down, 2 a miss / weak / reflect).
void sub_2D6620(EEContext& ctx);
// 0x2D79A0 [btlPktApplyDamage] Packet callback: applies a damage packet to its unit (+4 the action; +8 HP, +12 SP, +16
//   statuses to set, +20 to clear, +24 the extra flag, +34 / +38 flags): the action flags 0x1000 / 0x800 / 0x2000; with
//   gBtl +12 bit 0x10 adds HP / SP (datCalcAddHp / AddSp; a party member's hurt voice sub_1FEEA0), with bit 0x20 the
//   status change (sub_2DC550, set / clear); sub_302380 for the extra flag. A unit that just died: an enemy counts the
//   kills (gBtl +2970, +2972 for flag 8, the levels +3092 and the highest +3088); sub_2FA510; a revival (flag 0x10: HP
//   1 unless skill 438, status 0x80000 cleared, +156 bit 0x10) or death (HP 0, all statuses but 0x80000, +156 bit 1);
//   the navigator's death line (sub_103C30, voice 19) or line 27; else the low-HP (26) / status 0x200 (28) lines; then
//   sub_2FAA50 and the wait motion (sub_2831C0, 6 frames). Returns 1.
void sub_2D79A0(EEContext& ctx);
// 0x2DAA20 [btlNaviRequestLine] Requests a navigator (support) line a1 about action a0 (a2 / a3 its arguments, t0 flags): only
//   with the navigator ready (gBtl +12 bit 0x1000000), none pending (+2584), not silenced (flag 4887) and, unless
//   forced (flags 6), no line playing (+2582 bit 1); not for an encounter that mutes it (gEncountTbl 28-byte rows, bit
//   0x400; line 31 always passes), nor a repeat of the playing line (+2596 / +2604); the line's picker (0x6978F0[line])
//   chooses a message (>= 0), skipped when the message table (+2588's +272, 12-byte rows) marks it heard (encounter bit
//   0x1000) or, with sub_17D800, a boss line of encounters 433..435; flag 2 cuts the playing line first (sub_2DBA80,
//   delay +2614 = 2). Returns btlSupportRequestLine's result, 1 when skipped, 0 when one is pending.
void sub_2DAA20(EEContext& ctx);
// 0x2DAD00 [btlNaviUpdate] Per-frame step of the navigator lines (btlUpdateTask through sub_2DB960): a pending line (+2584: 1
//   waits the delay +2614, 2 starts) opens its message file (+2588's table entry +2600, sub_3C8DD0), picks one of its
//   messages at random (itfMesMngGetBmdMessageCount, datCalcRand) and plays it (sub_3C8DE0 with the voice +2580), notes
//   it as playing (+2592 / +2596, +2582 bit 1, +2584 = 0); clears the playing bit when the window is done (sub_3C8EA0).
void sub_2DAD00(EEContext& ctx);
// 0x2DAE30 [btlSupportTurnEnd] Turn-end check of the support events (gBtl +2564 bits 1 / 2 / 4, counters +2552 [3] against
//   +2554): a0 counts the turn; event 4 (an enemy to watch) re-targets when its unit died (the enemy of kind +2572,
//   sub_2DB650) or expires; event 1 (a member to rescue) picks a random living setup member not yet out (gBtl +3012
//   [3], datUnitIsGenusDead) and says line 7; when a counter runs out and the navigator is free (sub_29ADF0): event 4 /
//   2 set the navigator's state 7 / 19 (sub_29A380), event 1 brings the member in (sub_289650, state 17, sub_2DB2A0)
//   unless sub_2DB480 says no.
void sub_2DAE30(EEContext& ctx);
// 0x2DB6A0 [btlPktNaviLine] Packet callback: requests its navigator line once (+20 the result of sub_2DAA20 with +0 / +4 / +8
//   / +12 / +16) and returns it, 0 while a 'wait' line (flag 1) is still pending or playing.
void sub_2DB6A0(EEContext& ctx);
// 0x2DB860 Packet callback: stops the navigator line (sub_2DBA80); returns 1.
void sub_2DB860(EEContext& ctx);
// 0x2DB960 Per-frame navigator step wrapper (btlNaviUpdate).
void sub_2DB960(EEContext& ctx);
// 0x2DBA80 [btlNaviStop] Stops the navigator line: the window and voice (sub_3C8F40 / sub_3C8F70), nothing pending, the
//   playing bit cleared.
void sub_2DBA80(EEContext& ctx);
// 0x2DBEB0 [btlPktNaviLoad] Packet callback: loads the navigator's message file (+4 the navigator index 0 / 1; +6 the step):
//   step 0 picks the voice set (4, or 6 for navigator 1, into gBtl +2580), steps 0 / 1 request the file (the path table
//   0x697B90 by navigator) into +2588 and go to step 2; step 2 waits for it; step 3 opens the voice bank (sub_3C8DA0
//   with 1 | 1 << voice set) -> step 4; then gBtl +12 |= 0x1000000 (navigator ready). Returns 1 when done.
void sub_2DBEB0(EEContext& ctx);
// 0x2DCD30 [btlPlayBattleMusic] Starts the battle music (from btlMainUpdateStateUnitCreate, when gBtl +12 bit 0x40): by the
//   encounter's music kind (gEncountTbl +22): 2..6 the tracks 27..31, 7 / 8 the tracks 113 / 114, otherwise 106 with
//   sub_17D800 or the normal battle track 2 (sub_1099D0(track, 1)).
void sub_2DCD30(EEContext& ctx);
// 0x2DCED0 [btlPlaySe] Plays sound a0 through sub_108FD0 when the battle has sound (gBtl +12 bit 0x40).
void sub_2DCED0(EEContext& ctx);
// 0x2DCF10 [btlStopSounds] Stops the battle sound channels 2..4 (sub_109F60) and sub_108F70, when the battle has sound.
void sub_2DCF10(EEContext& ctx);
// 0x2DCF80 Sound request sub_10A100(a0, 0, a1).
void sub_2DCF80(EEContext& ctx);
// 0x2DD020 [btlPktPlaySound] Packet callback: plays a sound {u16 bank, id, arg} unless it is the one the bank last played
//   (gBtl +2708 + 6 * bank), then notes it; returns 1.
void sub_2DD020(EEContext& ctx);
// 0x2DD2F0 [btlPktSkillSound] Packet callback: loads and plays a skill's sound bank: requests "skill/%03X.se" (sprintf) once
//   (+8); step 1 waits for the file, frees the channels 4..9 of bank 2 (sub_10A0E0), passes its three files to the
//   sound driver (sub_109AE0) and goes to step 2, counting frames (+0); step 2 destroys the request when the driver is
//   done (sub_109DF0). Returns 1 then.
void sub_2DD2F0(EEContext& ctx);
// 0x2DD510 [btlPktStepSound] Packet callback: the battle's footstep / hit sounds -- kind 1 plays the next of the sounds 5..8
//   (gBtl +2704; when +2706 is -1), kind 0 plays sound 4 (bank 2); returns 1.
void sub_2DD510(EEContext& ctx);
// 0x2DD630 [btlPktPlayNamedSound] Packet callback: plays a named sound file "SOUND2\BATTLE\" + the name (+4) on channel +0
//   (sub_10A370); returns 1.
void sub_2DD630(EEContext& ctx);
// 0x2DDBA0 Sound request sub_10A2E0(gBtl +2808, 4, a0).
void sub_2DDBA0(EEContext& ctx);
// 0x2DDBE0 Sound request sub_10A100(4, 0, 8) (played by btlMainUpdateStateWin and sub_28CA00).
void sub_2DDBE0(EEContext& ctx);
// 0x2DE2A0 [btlVoiceLineC] Voice line of a party member for one event: by the member's model (+164) 2 -> 176, 3 -> 259 (260
//   with the flag of 0x697BE4), 4 -> 358, 5 -> 431, 7 -> 523, 8 -> 563, 9 -> 642 (1139 with sub_17D800); enemies and
//   the others -1.
void sub_2DE2A0(EEContext& ctx);
// 0x2DED60 [btlVoiceLineD] Voice line of a party member for another event: by model 2 -> 164 / 165, 3 -> 245 / 246, 4 -> 346 /
//   347, 5 -> 419 / 420, 7 -> 492 / 493, 8 -> 565 / 566 (the second with that member's flag 0x697BE0..0x697BF8), 9 ->
//   634 (1130 with sub_17D800; its flag 0x697BFC is read but unused); enemies and the others -1.
void sub_2DED60(EEContext& ctx);
// 0x2E1500 [btlVoiceLineSituation] Voice line of a party member for one of ten situations a1 (0..9): the rows 203..212 (model
//   2), 297..306 (3), 385..394 (4), 458..467 (5), 531..540 (7), 604..613 (8), 669..678 / 1174..1183 (9, by sub_17D800),
//   with the situations 5 / 6 and 7 / 8 / 9 not in order (5 -> +6, 6 -> +5, 7 -> +9, 8 -> +7, 9 -> +8); enemies, other
//   models and situations -1.
void sub_2E1500(EEContext& ctx);
// 0x2E2560 [btlVoiceLineHit] Voice line for a party member's hit, unless voice channel 4 is busy (sub_10A500(4) == 1): model 3
//   -> 310, model 2 -> 215 or 216 (datCalcRand(100) < 50); else -1.
void sub_2E2560(EEContext& ctx);
// 0x2E2D70 [btlPktSpecialVoice] Packet callback: plays the battle's special voice track once (+4): 451, or 452 when +8 is set
//   (gBtl +2818 = 4 / 5), through sub_10A770 on the battle task unless voices are off (0x7CE500); then waits for it
//   (sub_10A720, done flag gBtl +2816 bit 1). Returns 1 when done.
void sub_2E2D70(EEContext& ctx);
// 0x2E3560 [btlPktCutInStart] Packet callback: starts a cut-in (sub_1166A0 on the battle task with the data block's two ids)
//   and keeps its handle in gBtl +3360.
void sub_2E3560(EEContext& ctx);
// 0x2E35A0 [btlPktCutInReady] Packet callback: whether the cut-in is ready (sub_116760 == 1).
void sub_2E35A0(EEContext& ctx);
// 0x2E3650 [btlPktCutInPlay] Packet callback: plays the cut-in's first part (sub_116780 once), then counts frames (+0) until
//   27 frames before its end (sub_1167C0(.., 0)); returns 1 then.
void sub_2E3650(EEContext& ctx);
// 0x2E3740 [btlPktCutInEnd] Packet callback: plays the cut-in's second part (sub_1167A0 once) and counts frames to its length
//   (sub_1167C0(.., 1)); then drops the handle and returns 1.
void sub_2E3740(EEContext& ctx);
// 0x2E3830 [btlPktSpecialFxStart] Packet callback: starts a special effect (sub_116E20 on the battle task with the data
//   block's id) into gBtl +3360.
void sub_2E3830(EEContext& ctx);
// 0x2E3870 [btlPktSpecialFxReady] Packet callback: whether the special effect is ready (sub_116ED0 == 1).
void sub_2E3870(EEContext& ctx);
// 0x2E3900 [btlPktSpecialFxPlay] Packet callback: plays the special effect (sub_116EF0 once) and counts frames until it
//   reports done (sub_116F30); returns 1 then.
void sub_2E3900(EEContext& ctx);
// 0x2E39E0 [btlPktSpecialFxEnd] Packet callback: ends the special effect (sub_116F50 once; the counter starts at sub_116F20)
//   and counts to its end (sub_116F10); then drops the handle and returns 1.
void sub_2E39E0(EEContext& ctx);
// 0x2E3B20 [btlPktFx2Ready] Packet callback: whether the second effect (gBtl +3364) is ready (sub_119380 == 1).
void sub_2E3B20(EEContext& ctx);
// 0x2E3BE0 [btlPktFx2Play] Packet callback: plays the second effect (sub_1193A0 once) and counts frames until 12 before its
//   end (sub_1193C0); then drops the handle (+3364) and returns 1.
void sub_2E3BE0(EEContext& ctx);
// 0x2F8FD0 [btlBossReactMotion] Boss reaction motion for a skill used on / by a unit: by the encounter -- 436 the boss 241 on
//   the skills 293..296 -> 0; 424 the boss 269 on skill 308 -> 7 (21 once gBtl +2900 is set); 422 the boss 266 on the
//   skills 115 / 117 / 119 / 127 / 128 / 131 / 141 / 142 / 144 -> 24; 421 the boss 263 on 363 / 364 -> 23 / 25; 419 the
//   boss 260 on an HP skill (datCalcIsHpSkill) -> 24; 418 the boss 259 on 355 -> 23; 417 the bosses 257 / 258 on 368 ->
//   23; any other encounter: the enemies 149..156 look the skill up in their 4-entry row of *0x7CE4A4 (8-byte rows by
//   id - 149) -> 4 / 7 / 23 / 24, else 7. Only enemies (+162 == 1); -1 otherwise.
void sub_2F8FD0(EEContext& ctx);
// 0x2F9B60 [btlBossSoundPakWait] Battle state step: when the boss sound pak was requested (gBtl +2836), waits for it
//   (H_Cdvd_IsFileLoaded) and hands it over (sub_2F7DC0); returns 1 when done.
void sub_2F9B60(EEContext& ctx);
// 0x2F9C10 [btlBossUnitSetup] Per-unit boss set-up when a unit enters (from sub_289650), by the encounter 0x1A0..0x1B4: marks
//   the boss enemy of each fight (ids 256 / 257-258 / 259 / 260 / 263 / 265-266 / 278-280 / 269 / 264 / 271 / 272 /
//   273) with the unit flags 0x100 | 0x40 | 0x400 (or the DatUnit flag 0x40 | 0x100, or 0x80 with the action's flag
//   0x10 and the motion 208..210 through sub_288F80), or runs the encounter's own set-up (0x1A4 sub_2EA780, 0x1A7
//   sub_2EEB70, 0x1AD..0x1B4 sub_2F3670..sub_2F5980). Returns 1 for most, 0 for 0x1A9..0x1AB, 0x1AF..0x1B4 and the
//   others.
void sub_2F9C10(EEContext& ctx);
// 0x2FA240 [btlBossPlaceUnits] Runs the fixed placement of a boss encounter (416..436, 456: each its own set-up
//   sub_2E9170..sub_2F5A70; 433..435 share sub_2F5490) and returns 1; 0 for the other encounters (formation placement).
void sub_2FA240(EEContext& ctx);
// 0x2FAA50 [btlBossAfterDamage] After a damage packet: encounter 436 -> sub_2F5BF0, 421 -> sub_2EC190.
void sub_2FAA50(EEContext& ctx);
// 0x2FAAB0 [btlBossAfterUnitLoad] Boss set-up after the units load (from btlMainUpdateStateUnitLoad): 436 the enemies 242 are
//   reset (grid record, wait motion, sub_287510, moved to 0x957180); 428 / 421 the bosses 273 / 263 get the model flag
//   8 (+904) and alpha 0 (+1053), gBtl +2896 / +2892 cleared; 424 sub_2EF5A0; 420 sub_2EAA40.
void sub_2FAAB0(EEContext& ctx);
// 0x2FD520 [btlBossUnitUpdate] Per-frame boss update of a unit (from sub_286540): 436 sub_2F5D80; 428 an enemy with a live
//   model fades its alpha (+1053) up or down by 32 by gBtl +2896; 424 sub_2EFB40; 422 sub_2EC990; 421 sub_2EC4B0.
void sub_2FD520(EEContext& ctx);
// 0x2FD660 [btlBossCheckWin] Boss win condition (from btlMainCheckBattleEnd): 436 won when no enemy 241 lives, 420 when no
//   enemy 261 / 262 lives, 424 sub_2EF9D0, 416 sub_2E97E0; 0 for the others.
void sub_2FD660(EEContext& ctx);
// 0x2FDE40 [btlBossActionCheck] Boss check during an action (gBtl +12 bit 0x200000 only): encounter 426 -> sub_2F1B60, 423 ->
//   sub_2EEE20, else 0.
void sub_2FDE40(EEContext& ctx);
// 0x2FED10 [btlScreenFlash] Script callback: the battle's screen flash (the state byte of +60): 1 runs the flash (20 frames,
//   gBtl words 0x7CE50A / 0x7CE50C; RW render states, sub_3294D0 / sub_358460 / sub_2FE780 / sub_329550 / the
//   full-screen quads sub_2FE0B0 with alphas 255 * (1 - t^5) and 160 * (1 - t^2)) then state 3; 2 the steady tint
//   (alpha 16 or 24 by +6, then 5); 3 waits for the sound (sub_108710; sub_1085C0, returns -1). Saves and restores the
//   seven render states of 0x69AA50.
void sub_2FED10(EEContext& ctx);

}  // namespace p3fes::game
