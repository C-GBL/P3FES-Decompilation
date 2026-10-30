// The battle core and enemy AI, third pass (slice battle3; docs/ANALYSIS/21_battle.md): 162 functions of the battle
// bands 0x27BBA0-0x311310 that the battle replay (the first battle) and the Tartarus climb run and whose callees are all
// hand-written. game/src/battle/battle3.cpp; the bodies come from p3fes_handgen (register ABI: arguments in $a0.., the
// result in $v0), with the record offsets below named and each function's role given. Names: functions.json's in code,
// ours in brackets in the comments (ADR-0009); the confirmed record fields go to tools/ours/types/deltas/battle3.json.
//
// Groups: the unit packets (look at a point / a unit, stop looking, tint fades, show / hide parts, aura off, move,
// the motion helpers), the fade / effect handles, the camera hooks, the all-out attack (sub_28A200 check, the
// ROUNDUP_MES state sub_298060), the CHANGE FORMATION / PERSONA / DEAD action states, the advantage roll (sub_2D50C0), the
// escape roll (sub_2D4ED0), the ailment skip / recovery rolls (sub_2DC070 / sub_2DC180), the action cost (sub_2D8110),
// the battle grid (sub_2D2280..sub_2D4040), the support (navigator) and voice line pickers, the boss rules (motion
// remap, event scheduler, work words), and the enemy AI: the unit finder sub_2C0E30, the counter sub_2C0F40, eleven
// conditions of the table 0x6971B0 (MYHP MYMP FRLV_O FRCNT ENCNT SENSEI MYHANSYA MYWEAK TURN ENOVERLV MYHOJO -- the
// table's own strings), the fallback target selector AI (row 0 of 0x6975E0, sub_2C3770), the best-skill pick
// sub_2C48A0, the command decoder sub_2C6A00 and the AICALC section-15 row evaluation sub_2C6BA0 / sub_2C6E30.
//
// THE BATTLE STATE A CO-OP SERVER WOULD OWN (from these functions and the earlier battle slices; offsets decimal)
//   * gBtl, *(u32*)0x7CE3EC ($gp - 18692), 3,440 bytes: kFlags (+12: 0x80 battle over, 0x800 packets may start,
//     0x200000 boss rules, 0x400000 effect requests pending), kAdvantage (+26), kOutcome (+28), the btlMain state
//     machine (+692 state, +696 pending, +700 frames; sBtlMainStateTbl 0x693760), the hero's action (+328), the
//     btlAction list (+332, +1192 next), the four side lists of btlUnits (heads +340 + 8s, tails +336 + 8s), the turn
//     order (+584 flags, +588 turns started, +592 the actor moved to the end, +596 order[12] sorted by Agility, +644
//     next round[12]), the all-out attack list (+2952 u32[4], +2968 count), the two escape counters (+2970 / +2972),
//     the boss work words (+2884..+2900), the setup block (+2984: flags; +3004 the enemy genus, its +8 the encounter
//     id; +3012 reinforcements). The packet queues (+368 / +372 + 8q) are presentation, but the turn flow waits on
//     them (btlMainUpdateStateStart, sub_27E390 "no packet of this owner left"): a server must either run them or
//     replace each wait by an explicit "clients done" barrier.
//   * btlAction (1,200 bytes, one per combatant): kUid (+0, packet owner ids), the action state machine (+12 state,
//     +14 next, +16 previous, +18 delay, +28 frames; sBtlActionTbl 0x693410, 36 states), kFlags / kFlags2 (+24 / +26),
//     turns taken (+32), the one-more chain (+40), the unit (+48), the target actions (+56 u32[12], +106 count), the
//     command (+108 kind, +110 skill, +112 item), the AI target record (+136: candidates u32[12], +184 chosen uid,
//     +192 count, +194 index), the ailment turn counters (+1122 u8[24], one per status bit), the all-out fields
//     (+1156..+1172).
//   * btlUnit (2,616 bytes): side (+162), id (+164), uid (+168), flags (+156), the DatUnit (+2604); the model, motion,
//     look, tint and grid fields (+44..+2560) are client-side presentation.
//   * DatUnit (60 bytes): HP +8, SP +10, status +12, effect flags +20, the buff nibbles +28 / counters +41. Party
//     units live in gGlobalWork (hero 0x836224, members 0x834010 + 868 * (pc - 2) + 4) and outlast the battle; an
//     enemy genus is RwMalloc'd (6 units at +12).
//   * The random source: datCalcRand 0x2FFBC0 -> effMiscRand(0) 0x357FD0, a 4-word shift register behind the pointer
//     *(u32*)0x957BF0; n == 100 re-rolls once within +-3 of the previous roll (0x7CE510). The AI draws from it for its
//     target picks (sub_2C3770: datCalcRand(count), datCalcRand(100) against the weights 0x696FA0), its AICALC row
//     entries (sub_2C6E30), and the rolls of this slice (advantage, escape, ailment skip / recovery, shadow variants
//     sub_2D5570) -- but so do presentation paths (sub_282BC0's random idle frame, the camera shots sub_2A79F0 /
//     sub_2A95D0 / sub_2AA2B0 / sub_2AB330, 40-odd effect functions in 0x32xxxx). The stream is therefore NOT a pure
//     function of the battle logic: a server owning the RNG must give the presentation draws their own generator, and
//     then no longer reproduces the original's sequence (a determinism decision for the multiplayer ADR).

#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace b3 {

// --- $gp slots (offset from $gp 0x7D2CF0) ---------------------------------------------------------------------
inline constexpr s32 kGpAiBossRows = -18644;    // 0x7CE41C AICALC.TBL section 15: 164-byte AI rows by enemy id (sub_2C6BA0 / sub_2C6E30)
inline constexpr s32 kGpAiEscape = -18536;      // 0x7CE488 AICALC.TBL section 6: escape chance rows (9 by round + 6 by attempt)
inline constexpr s32 kGpAoaCamera = -31904;     // 0x7CB050 f32[12]: the all-out attack camera (3x3 rotation, translation; sub_298060)
inline constexpr s32 kGpBtl = -18692;           // 0x7CE3EC gBtl
inline constexpr s32 kGpByteToUnit = -32232;    // 0x7CAF08 f32 1/255
inline constexpr s32 kGpEffectSec5 = -18480;    // 0x7CE4C0 EFFECT.TBL section 5: 31 x 12-byte boss rows (sub_2FC520)
inline constexpr s32 kGpEffectTbl = -18672;     // 0x7CE400 EFFECT.TBL section 0: 28-byte skill effect rows
inline constexpr s32 kGpEncountTbl = -18504;    // 0x7CE4A8 gEncountTbl
inline constexpr s32 kGpEnemyNames = -18440;    // 0x7CE4E8 MSG.TBL section 2
inline constexpr s32 kGpF02 = -32588;           // 0x7CADA4 f32 0.2: sub_319090's argument in sub_287CF0 feature 3
inline constexpr s32 kGpF03a = -32628;          // 0x7CAD7C f32 0.3: sub_319090's argument in sub_288780
inline constexpr s32 kGpF03b = -31856;          // 0x7CB080 f32 0.3: sub_319090's argument in sub_288190 / sub_288430
inline constexpr s32 kGpF04 = -32632;           // 0x7CAD78 f32 0.4: model +924 / +928 of sub_287B20 feature 1
inline constexpr s32 kGpF07 = -32544;           // 0x7CADD0 f32 0.7: an argument in sub_28BA50
inline constexpr s32 kGpModelEnemy = -18648;    // 0x7CE418 MODEL.TBL section 2 (232-byte rows by enemy id)
inline constexpr s32 kGpModelParty = -18660;    // 0x7CE40C MODEL.TBL section 1 (266-byte rows by party id)
inline constexpr s32 kGpModelPersona = -18628;  // 0x7CE42C MODEL.TBL section 3 (88-byte rows by persona id)
inline constexpr s32 kGpModelWeapon = -18664;   // 0x7CE408 MODEL.TBL section 0 (296-byte rows by weapon type)
inline constexpr s32 kGpSkillNames = -18436;    // 0x7CE4EC MSG.TBL section 1: 19-byte skill names
inline constexpr s32 kGpSkillTbl = -18680;      // 0x7CE3F8 gBtlSkillTbl

// --- gBtl (*(u32*)0x7CE3EC, 3,440 bytes; battle_core2.h bcore:: has the creation-side fields) --------------------------
namespace gbtl {
inline constexpr s32 kFlags = 12;           // u32: 0x2 scene active, 0x80 the battle is over, 0x200 names shown, 0x800 packets may start, 0x4000 the command calc task closed by a turn end, 0x200000 boss rules, 0x400000 kFxRequest pending, 0x2000000 colour fades run
inline constexpr s32 kFxRequest = 24;       // u16: bits 0x01..0x20 = the six packets sub_28A780 queues once (then cleared with kFlags 0x400000)
inline constexpr s32 kAdvantage = 26;       // u16: the advantage roll's result (sub_2D50C0): 0 normal, 1 the party strikes first, 2 the enemies strike first (verified in the editor's battle sandbox; this comment had 1 and 2 swapped before battle6)
inline constexpr s32 kOutcome = 28;         // u16: 1 win, 2 lose, 3 escape (btlMainCheckBattleEnd)
inline constexpr s32 kCameraState = 260;    // u16: the battle camera's current state (28 / 29 / 34 / 35 / 2 tested by the camera hooks)
inline constexpr s32 kPlayerAction = 328;   // u32: the hero's btlAction
inline constexpr s32 kActionList = 332;     // u32: head of the btlAction list (+1192 next)
inline constexpr s32 kUnitTail0 = 336;      // u32: tail of side 0's btlUnit list (+2612 prev); sides at stride 8
inline constexpr s32 kUnitHead0 = 340;      // u32: head of side 0 (party) btlUnits (+2608 next); side s at +340 + 8s
inline constexpr s32 kUnitHead1 = 348;      // u32: head of side 1 (enemies)
inline constexpr s32 kUnitHead2 = 356;      // u32: head of side 2 (personas / summons)
inline constexpr s32 kUnitHead3 = 364;      // u32: head of side 3
inline constexpr s32 kPktHead0 = 372;       // u32: head of packet queue 0 (queues at stride 8)
inline constexpr s32 kFxObjList = 400;      // u32: head of the effect-object list (+32 next, +28 prev)
inline constexpr s32 kFadeColA = 404;       // f32[4]: colour A of the screen fades (sub_29EA60 / sub_29F760), RGBA 0..1
inline constexpr s32 kFadeColB = 420;       // f32[4]: colour B
inline constexpr s32 kSceneVecA = 452;      // f32[4]: copied to the scene object +256 each frame (battle_core2 sub_29E420)
inline constexpr s32 kFadeColC = 500;       // f32[4]: colour C (sub_29EC80)
inline constexpr s32 kFadeColD = 516;       // f32[4]: colour D
inline constexpr s32 kOrderFlags = 584;     // u16: bit 0 the turn order runs, bit 1 / 2 reshuffle enemies / party, bit 3 the next turn may start
inline constexpr s32 kOrderTurns = 588;     // u32: turns started
inline constexpr s32 kOrderActor = 592;     // u32: the action moved to the end of the order
inline constexpr s32 kOrderList = 596;      // u32[12]: the turn order (btlAction*), sorted by Agility
inline constexpr s32 kOrderNext = 644;      // u32[12]: actions queued for the next round
inline constexpr s32 kMainState = 692;      // u32: btlMain state (sBtlMainStateTbl 0x693760)
inline constexpr s32 kMainPending = 696;    // u32: the state entered next frame
inline constexpr s32 kMainFrames = 700;     // u32: frames in the state
inline constexpr s32 kGridList = 716;       // u32: the last unit grid record (btlUnit + 1276) linked by sub_2D3E00
inline constexpr s32 kBossTask = 2856;      // u32: a boss event task (sub_2FD4A0 clears it once kwlnTaskExists says it ended)
inline constexpr s32 kBossWork0 = 2884;     // u32: boss work word 0 (encounters 0x1A5 / 0x1A7..0x1B3: a pending action, a phase)
inline constexpr s32 kBossWork1 = 2888;     // u32 (u16 for encounter 429): boss work word 1
inline constexpr s32 kBossWork2 = 2892;     // u32: boss work word 2
inline constexpr s32 kBossWork3 = 2896;     // u32 (u16 count for encounter 424): boss work word 3
inline constexpr s32 kBossWork4 = 2900;     // u32: boss work word 4
inline constexpr s32 kAllOutList = 2952;    // u32[4]: the party actions that join the all-out attack (sub_28A200)
inline constexpr s32 kAllOutCount = 2968;   // u16: entries in kAllOutList (datScriptGetValue selector 27 reads this word + 1)
inline constexpr s32 kEscRowA = 2970;       // u16: a counter: 0 = no escape and the opening support line (108); else the row of the first escape table
inline constexpr s32 kEscRowB = 2972;       // u16: a counter: the row of the second escape table
inline constexpr s32 kSetupFlags = 2984;    // u16: the setup block's flags (+0): bit 0 player strike, bit 1 enemy strike, bit 2 no roll, bit 3
inline constexpr s32 kSetupEnemies = 3004;  // u32: the enemy genus (setup +20; genus +8 = the encounter id)
inline constexpr s32 kReinforce = 3012;     // u32[3] (stride 8): reinforcement genus
inline constexpr s32 kSceneTask = 3344;     // u32: the battle scene (sub_2BB2F0's first argument)
inline constexpr s32 kCmdCalcTask = 3356;   // u32: the "battle_command_calc" task (cleared when it closes)
inline constexpr s32 kEventTask = 3364;     // u32: the event task sub_2E3CD0 destroys
}  // namespace gbtl

// --- btlAction (1,200 bytes, btlActionCreate) --------------------------------------------------------------------------
namespace act {
inline constexpr s32 kUid = 0;              // u64: btlGetUID at creation (packet owner ids)
inline constexpr s32 kSerial = 8;           // s32
inline constexpr s32 kState = 12;           // u16: the sBtlActionTbl state
inline constexpr s32 kPrevState = 16;       // u16
inline constexpr s32 kResumeState = 22;     // u16: the state the turn resumes in (sub_298060 sets 29)
inline constexpr s32 kFlags = 24;           // u16: bit 0 active, bit 3 all-out leader
inline constexpr s32 kFlags2 = 26;          // u16: bit 0 a combatant, bit 3 placed, bit 6 voiced once (sub_2D8F70)
inline constexpr s32 kFrames = 28;          // u32: frames in the state
inline constexpr s32 kTurnsTaken = 32;      // s32: turns this unit acted (>= 3 -> the tired voice rows)
inline constexpr s32 kOneMore = 40;         // u8: the "one more" chain count of this turn
inline constexpr s32 kUnit = 48;            // u32: btlUnit*
inline constexpr s32 kTargets = 56;         // u32[12]: the target btlActions
inline constexpr s32 kTargetCount = 106;    // u16
inline constexpr s32 kCmdKind = 108;        // u16: 1 attack, 2 skill, 3 item, 9 ...
inline constexpr s32 kCmdSkill = 110;       // u16: the skill id
inline constexpr s32 kCmdItem = 112;        // u16: the item id
inline constexpr s32 kTargetRec = 136;      // the AI target record (airec::): u32[12] candidate actions
inline constexpr s32 kTargetRecUid = 184;   // u64: the record's chosen uid (+136 + 48)
inline constexpr s32 kTargetRecCount = 192; // u16: candidates (+136 + 56)
inline constexpr s32 kTargetRecIndex = 194; // u16: the current candidate (+136 + 58)
inline constexpr s32 kAilmentTurns = 1122;  // u8[24]: turns each bad-status bit has lasted (sub_2DC180)
inline constexpr s32 kAoaLeader = 1156;     // u32: the action that called the all-out attack
inline constexpr s32 kAoaPhase = 1160;      // u32: 0 start, 1 running
inline constexpr s32 kAoaDone = 1164;       // u32
inline constexpr s32 kAoaTimer = 1168;      // s16: frames to the dust cloud cue (-1 once played)
inline constexpr s32 kAoaLinked = 1172;     // u32: the action the player turn hands over to
inline constexpr s32 kPrev = 1188;          // u32
inline constexpr s32 kNext = 1192;          // u32: next btlAction of gBtl's list
}  // namespace act

// --- btlUnit (2,616 bytes, btlUnitCreate) ------------------------------------------------------------------------------
namespace unit {
inline constexpr s32 kScale = 44;           // f32: the model scale (with +144 the grid radius)
inline constexpr s32 kColour = 48;          // u32: RGBA tint (sub_285880 fades it)
inline constexpr s32 kRadius = 144;         // f32
inline constexpr s32 kModelFlags = 152;     // u32: bit 1 has a model, bit 2 colour changed
inline constexpr s32 kFlags = 156;          // u32: 0x1 hidden, 0x4 on the grid, 0x8 in the battle, 0x20, 0x40 boss-rule unit, 0x80, 0x200, 0x800 shadow
inline constexpr s32 kBusy = 160;           // u16: packets holding the unit
inline constexpr s32 kSide = 162;           // u8: 0 party, 1 enemy, 2 persona
inline constexpr s32 kId = 164;             // u16: party id 1..10 / enemy id
inline constexpr s32 kUid = 168;            // u32: the unit uid (AI target records)
inline constexpr s32 kPersonaPose = 172;    // u8: set by sub_2880E0 for side-2 units
inline constexpr s32 kLookMode = 176;       // u16: 0 none, 1 a point, 2 a unit
inline constexpr s32 kLookUid = 180;        // u32: the unit looked at (mode 2)
inline constexpr s32 kLookPos = 184;        // f32[3]: the point looked at (mode 1)
inline constexpr s32 kWalkSpeed = 196;      // u32: the move packet's speed word (sub_2821B0)
inline constexpr s32 kWalkFlags = 200;      // u16: bit 1 walking (cleared when the target is reached)
inline constexpr s32 kWalkTarget = 208;     // f32[3]: the walk target
inline constexpr s32 kWalkTimer = 232;      // u32: zeroed when a walk starts
inline constexpr s32 kWalkStep = 1272;      // u32: zeroed when a walk starts
inline constexpr s32 kGridX = 1276;         // s16: grid cell x (25-unit cells from -1750)
inline constexpr s32 kGridZ = 1278;         // s16: grid cell z
inline constexpr s32 kGridSize = 1280;      // f32: scale * radius when placed
inline constexpr s32 kGridMark = 2500;      // u32
inline constexpr s32 kGridNext = 2504;      // u32: the previous kGridList record
inline constexpr s32 kMotion = 2510;        // u16: the current motion
inline constexpr s32 kMotionCount = 2520;   // u16: rows in kMotionTbl
inline constexpr s32 kMotionWant = 2528;    // s16
inline constexpr s32 kMotionTbl = 2540;     // u32: 10-byte motion rows {s16 frames, s16 speed %, ..., s16 +8}
inline constexpr s32 kShadow = 2546;        // u16
inline constexpr s32 kModel = 2548;         // u32: the model object
inline constexpr s32 kAura = 2556;          // u32
inline constexpr s32 kCamObj = 2560;        // u32
inline constexpr s32 kDat = 2604;           // u32: DatUnit*
inline constexpr s32 kNext = 2608;          // u32
inline constexpr s32 kPrev = 2612;          // u32
}  // namespace unit

// --- DatUnit (60 bytes; battle_view.h dat_unit:: has the full list) ----------------------------------------------------
namespace dat {
inline constexpr s32 kFlags = 0;            // u16: bit 2 enemy
inline constexpr s32 kId = 2;               // u16
inline constexpr s32 kBaseId = 4;           // u16
inline constexpr s32 kLevel = 6;            // u8
inline constexpr s32 kHp = 8;               // u16
inline constexpr s32 kSp = 10;              // u16
inline constexpr s32 kStatus = 12;          // u32
inline constexpr s32 kEffectFlags = 20;     // u32
}  // namespace dat

// --- btl packet (144-byte header + data; sub_27EC10) -------------------------------------------------------------------
namespace pkt {
inline constexpr s32 kKind = 64;            // u32
inline constexpr s32 kQueue = 68;           // u8
inline constexpr s32 kPhase = 69;           // u8
inline constexpr s32 kPaused = 70;          // u8
inline constexpr s32 kFlags = 71;           // u8: 0x01 / 0x10 / 0x20 live bits (cleared by some creators), 0x08 queued, 0x04 kill
inline constexpr s32 kStartDelay = 72;      // s16
inline constexpr s32 kEndDelay = 74;        // s16
inline constexpr s32 kId = 88;              // u64
inline constexpr s32 kOwner = 96;           // u64: the owning action's uid
inline constexpr s32 kOnQueue = 104;        // fn(data)
inline constexpr s32 kUpdate = 108;         // fn(data) -> done
inline constexpr s32 kOnEnd = 112;          // fn(data)
inline constexpr s32 kQuery = 116;          // fn
inline constexpr s32 kData = 120;           // u32: the data block
inline constexpr s32 kNext = 124;           // u32
inline constexpr s32 kPrev = 128;           // u32
}  // namespace pkt

// --- the AI target record (an action's +136; sub_2BFF60 fills it) ------------------------------------------------------
namespace airec {
inline constexpr s32 kCands = 0;            // u32[12]: the candidate btlActions
inline constexpr s32 kUid = 48;             // u64: the chosen candidate's action uid
inline constexpr s32 kCount = 56;           // u16: candidates
inline constexpr s32 kIndex = 58;           // u16: the current candidate
}  // namespace airec

}  // namespace b3

// --- the functions (register ABI: arguments in $a0.., the result in $v0) ----------------------------------------
// 0x2821B0 [btlUnitPktUpdateMove] Update of the unit move packet: on the first frame (counter +20 == 0) takes the target point
//   (the unit's own position through sub_27F7C0 when flag 0x20 is set), writes it to the unit's walk target
//   (+208..+216), clears +1272 / +232, copies the speed word (+16) to +196 and sets the walking bit (+200 bit 1); done
//   once the unit cleared that bit.
void sub_2821B0(EEContext& ctx);
// 0x282BC0 [btlUnitRandomizeIdleFrame] Puts a unit at a random frame of its current motion: frames = sub_2838D0(unit,
//   sub_282C30(unit)), then sub_283C00(unit, datCalcRand(frames)).
void sub_282BC0(EEContext& ctx);
// 0x2835E0 [btlUnitGetMotionFrames] Length in frames of a unit's motion at a playback speed: the motion row is the side's row
//   of the table 0x693290 (26 per side), or for enemies the boss remap sub_2FB860 when it gives one; frames =
//   row.frames / (speed * row.speed% / 100) as s16, 0 when the row is beyond the unit's motion table.
void sub_2835E0(EEContext& ctx);
// 0x2838D0 [btlUnitGetMotionClipFrames] As sub_2835E0 but from the model's own clip length (sub_318910): 0 when the unit has
//   no model; the clip length divided by speed * row.speed% / 100, or the clip length when the row is beyond the table.
void sub_2838D0(EEContext& ctx);
// 0x283A70 [btlUnitGetMotionBlend] The blend word (+8) of a unit's motion row (same row choice as sub_2835E0); 6 without a
//   model or a row.
void sub_283A70(EEContext& ctx);
// 0x284040 [btlSkillGetCastClass] Cast-motion class of a skill: 1 for no skill / an id >= 464 / almighty or recovery elements;
//   for HP skills the EFFECT.TBL row's flags (+2): 0x200 -> 0, bit 0 with a3 set -> 2, else 1; other skills 3.
void sub_284040(EEContext& ctx);
// 0x284C00 [btlUnitPktUpdateWaitMotion] Update callback: a party / enemy unit's wanted motion (+2528) equals its current one
//   (+2510 when it has a model, else 0).
void sub_284C00(EEContext& ctx);
// 0x285670 Release callback of packet 271: the unit's busy count -1.
void sub_285670(EEContext& ctx);
// 0x285690 [btlUnitPktCreate271] Creates unit packet 271 (16 bytes: unit, u16 side + 1, u16 a1, u16 a2; clears live bit 0)
//   with the hold / update / release callbacks sub_284FE0 / sub_2850F0 / sub_285670.
void sub_285690(EEContext& ctx);
// 0x285730 Hold callback of packet 272: busy +1.
void sub_285730(EEContext& ctx);
// 0x2857D0 Release callback of packet 272: busy -1.
void sub_2857D0(EEContext& ctx);
// 0x2857F0 [btlUnitPktCreate272] Creates unit packet 272 (4 bytes: unit; clears live bit 0), callbacks sub_285730 / sub_285750
//   / sub_2857D0.
void sub_2857F0(EEContext& ctx);
// 0x285860 Hold callback of the tint fade packet 274: busy +1.
void sub_285860(EEContext& ctx);
// 0x285880 [btlUnitPktUpdateTintFade] Update of the tint fade packet 274: on frame 0 takes the start colour (the unit's +48,
//   with the alpha / colour forced by flags +17), then each frame lerps the colour part and the alpha part separately
//   (VU0, byte <-> float through 1/255) towards the target (+8) over the durations +12 / +14 by mode +16 (1 colour
//   after alpha, 2 alpha after colour, 3 / 4 together), writes the unit's tint, sets model flag 0x4; done after the
//   longer duration.
void sub_285880(EEContext& ctx);
// 0x285D10 Release callback of packet 274: busy -1.
void sub_285D10(EEContext& ctx);
// 0x285D30 [btlUnitPktCreateTintFade] Creates the tint fade packet 274 (20 bytes: unit, target RGBA, s16 durations, u8 mode,
//   u8 flags).
void sub_285D30(EEContext& ctx);
// 0x285F80 Hold callback of packet 277: busy +1.
void sub_285F80(EEContext& ctx);
// 0x285FA0 [btlUnitPktUpdateShowParts] Update of packet 277: shows the unit's five model attachments (clears bit 1 of
//   attachment +216 where sub_319770 agrees). Done at once.
void sub_285FA0(EEContext& ctx);
// 0x286090 Release callback of packet 277: busy -1.
void sub_286090(EEContext& ctx);
// 0x2860B0 [btlUnitPktCreateShowParts] Creates packet 277 (4 bytes: unit).
void sub_2860B0(EEContext& ctx);
// 0x286110 Hold callback of packet 278: busy +1.
void sub_286110(EEContext& ctx);
// 0x286130 [btlUnitPktUpdateHideParts] Update of packet 278: hides the five model attachments (sets bit 1 of +216). Done at
//   once.
void sub_286130(EEContext& ctx);
// 0x286220 Release callback of packet 278: busy -1.
void sub_286220(EEContext& ctx);
// 0x286240 [btlUnitPktCreateHideParts] Creates packet 278 (4 bytes: unit).
void sub_286240(EEContext& ctx);
// 0x2862A0 Hold callback of packet 282: busy +1.
void sub_2862A0(EEContext& ctx);
// 0x2862C0 [btlUnitPktUpdateAuraOff] Update of packet 282: removes the unit's aura effect (sub_2BBBC0) when it has one
//   (+2556). Done at once.
void sub_2862C0(EEContext& ctx);
// 0x286300 Release callback of packet 282: busy -1.
void sub_286300(EEContext& ctx);
// 0x286320 [btlUnitPktCreateAuraOff] Creates packet 282 (4 bytes: unit).
void sub_286320(EEContext& ctx);
// 0x287B20 [btlUnitModelFeatureOn] Switches a model feature on (unit with a model only): 1 the outline (sub_319010, widths 0.4
//   / 1.0), 2 sub_319050, 3 the model flags 0x1000 | 0x2000 and ~0x800, 4 model +1022 bit 4, 5 the shadow (sub_1A0DC0)
//   for a placed unit that has one.
void sub_287B20(EEContext& ctx);
// 0x287CF0 [btlUnitModelFeatureOff] Switches the same features off (3 also clears the look mode +176).
void sub_287CF0(EEContext& ctx);
// 0x2880E0 Sets the pose byte (+172) of a persona unit (side 2); nothing for a null unit or another side.
void sub_2880E0(EEContext& ctx);
// 0x288170 Hold callback of the look-at-point packet 279 (the unit may be null).
void sub_288170(EEContext& ctx);
// 0x288190 [btlUnitPktUpdateLookAtPoint] Update of packet 279: makes the unit (or, with flag bit 0, every placed party unit)
//   look at the point (+4): look mode 1, +184 = the point, feature 3 on; resets the head-turn limits first. Done at
//   once.
void sub_288190(EEContext& ctx);
// 0x288340 Release callback of packet 279.
void sub_288340(EEContext& ctx);
// 0x288360 [btlUnitPktCreateLookAtPoint] Creates the look-at-point packet 279 (20 bytes: unit, the point, u16 flags).
void sub_288360(EEContext& ctx);
// 0x288400 Hold callback of the look-at-unit packet 280: busy +1 on both units (the first may be null).
void sub_288400(EEContext& ctx);
// 0x288430 [btlUnitPktUpdateLookAtUnit] Update of packet 280: makes the unit (or the party side with flag bit 0 and / or the
//   enemy side with bit 1) look at the target unit: look mode 2, +180 = the target's uid, feature 3 on. Done at once.
void sub_288430(EEContext& ctx);
// 0x2886B0 Release callback of packet 280: busy -1 on both units.
void sub_2886B0(EEContext& ctx);
// 0x2886E0 [btlUnitPktCreateLookAtUnit] Creates the look-at-unit packet 280 (12 bytes).
void sub_2886E0(EEContext& ctx);
// 0x288760 Hold callback of the stop-looking packet 281.
void sub_288760(EEContext& ctx);
// 0x288780 [btlUnitPktUpdateLookEnd] Update of packet 281: ends the look (features off, look mode 0) for the unit or for the
//   sides its flags name. Done at once.
void sub_288780(EEContext& ctx);
// 0x288930 Release callback of packet 281.
void sub_288930(EEContext& ctx);
// 0x288950 [btlUnitPktCreateLookEnd] Creates the stop-looking packet 281 (8 bytes).
void sub_288950(EEContext& ctx);
// 0x288DA0 [btlUnitGetModelRow] The unit's MODEL.TBL row: persona -> section 3 row + 2; enemy -> the boss override sub_2FC410,
//   else section 2 (+10 for kind 9); the hero -> section 0 by held weapon type; other party members -> section 1 (+10
//   for kind 9).
void sub_288DA0(EEContext& ctx);
// 0x288FE0 [btlUnitFindById] Finds the btlUnit of a side with a unit id (0 when none).
void sub_288FE0(EEContext& ctx);
// 0x289030 [btlUnitFindByUid] Finds the btlUnit with a uid on any of the four sides (0 when none).
void sub_289030(EEContext& ctx);
// 0x2899E0 [btlActionResetIdleLooks] Re-aims the idle party: every combatant whose unit is placed, visible (sub_282C60), not
//   busy (sub_281270), not down, without ailments, not at low HP and alive, in state 1 / 5 / 6 and not the given
//   action, looks at its own position (a look-at-point packet on queue 1).
void sub_2899E0(EEContext& ctx);
// 0x289F40 [btlActionNeedsApproach] Whether the action's attacker runs up to its target: not for multi-target commands
//   (sub_2BFF60); physical skills unless an enemy whose model row says ranged (+34 == 1); HP skills whose EFFECT row
//   has bit 0, again unless ranged (+38).
void sub_289F40(EEContext& ctx);
// 0x28A0F0 [btlActionIsRanged] Whether the attacker attacks from range: enemies by their model row (+34 == 1); party members 2
//   and 3 (bow, guns), sub_2D5BF0, or the hero holding weapon type 6 / 7.
void sub_28A0F0(EEContext& ctx);
// 0x28A200 [btlCheckAllOutAttack] The all-out attack check: the hero alive and free of the blocking ailments (0x100261), the
//   acting unit not a dead enemy, every living enemy knocked down (0x100000); collects the other able party members
//   into gBtl's all-out list. 1 when at least one enemy is down and someone joins.
void sub_28A200(EEContext& ctx);
// 0x28A3E0 [btlActionHasOneMore] Whether a hit knocked a target down ("one more"): enemy attacker -> a result's flag +250 bit
//   2; party attacker -> a result's status word +232 bit 0x100000, over every target and result.
void sub_28A3E0(EEContext& ctx);
// 0x28A540 [btlActionGetAttackMotions] The four motion ids of an attack: defaults {0, 1, 7, 9}; physical skills of party
//   member 3 / sub_2D5BF0 units by the weapon class sub_3093A0 (1 -> 14.., 2 -> 15.., 3 -> 16..); other physical skills
//   by element (slash / fire 2.., pierce / wind 4..).
void sub_28A540(EEContext& ctx);
// 0x28A780 [btlActionFlushFxRequests] Flushes gBtl's pending effect requests (kFxRequest, when kFlags 0x400000): queues, owned
//   by the action, the look reset (0x20), camera 3 / 4095 (0x02), a stop-looking packet per living combatant (0x01),
//   the effect packets of 0x10 / 0x08 and the camera 31 (0x04); then clears the request.
void sub_28A780(EEContext& ctx);
// 0x28BA50 [btlActionInitStateChangeFormation] btlAction state CHANGE FORMATION, init: flushes the requests, queues the
//   formation camera, the opening line, a walk for every able party unit, the enemy reactions (a death motion or a look
//   at the actor) and camera 35, all chained to the camera packet.
void sub_28BA50(EEContext& ctx);
// 0x297480 [btlActionInitStatePersona] btlAction state PERSONA, init: flushes the requests, summons the persona (sub_2BD780),
//   the camera 26, the user's motion, the cut-in line, the persona card for party members (sub_175130 / sub_288F80),
//   the summon effect, the sound and the card flash; requests the 0x04 camera at the end.
void sub_297480(EEContext& ctx);
// 0x297A50 Packet callback of the all-out attack: the action's done word (+1164).
void sub_297A50(EEContext& ctx);
// 0x298060 [btlActionUpdateStateRoundUpMes] btlAction state ROUNDUP_MES (the all-out attack), update: phase 0 queues the
//   portraits of the joining members, the event, the line, the sound and the dust-cloud camera (matrix 0x7CB050); phase
//   1 counts down to the cloud cue; when the packets end, either hands the turn to the hero (state 29 through
//   sub_29A380) or plays the finish, then marks the action done; a finished battle sets kFlags 0x4000 and closes the
//   command task.
void sub_298060(EEContext& ctx);
// 0x299990 [btlActionUpdateStateDead] btlAction state DEAD, update: a dead enemy leaves (state 34) unless it is a boss-rule
//   unit (flag 0x40); a unit that is alive again (revived) is shown, re-queued (sub_29A2C0) and returns to state 1.
void sub_299990(EEContext& ctx);
// 0x29EA20 &gBtl->kFadeColA.
void sub_29EA20(EEContext& ctx);
// 0x29EA30 &gBtl->kSceneVecA.
void sub_29EA30(EEContext& ctx);
// 0x29EA40 &gBtl->kFadeColC.
void sub_29EA40(EEContext& ctx);
// 0x29EA60 [btlEffectGetFadeColours] The two fade colours of a skill's EFFECT row (+8 / +12): a word with alpha bits is used
//   as is, otherwise gBtl's colour A / B converted to bytes (x 255 + 0.5).
void sub_29EA60(EEContext& ctx);
// 0x29EC00 EFFECT row +4 with the alpha forced to 0xFF when it has alpha bits, else -1.
void sub_29EC00(EEContext& ctx);
// 0x29EC50 EFFECT row +24.
void sub_29EC50(EEContext& ctx);
// 0x29EC80 [btlEffectGetFadeColours2] As sub_29EA60 for the row's +16 / +20 and colours C / D.
void sub_29EC80(EEContext& ctx);
// 0x29F4B0 [btlFxPktCreateFade] Creates the fade packet 1536 (104 bytes: two colours as floats x 1/255, the frame count at
//   +96), update sub_29F150.
void sub_29F4B0(EEContext& ctx);
// 0x29FA50 [btlFxPktCreateFadeBack] Creates the fade-back packet 1537 (40 bytes, frames at +32), update sub_29F760.
void sub_29FA50(EEContext& ctx);
// 0x2A5EE0 Camera hook: sub_2A54F0(a0, camera state == 29, 40, 70).
void sub_2A5EE0(EEContext& ctx);
// 0x2AC540 [btlCameraStartActionShot] Camera: picks the shot of an action (sub_2A7830 -> +272), notes whether the unit's
//   camera object accepts it (sub_2FDBB0 -> +276) and runs the shot's set-up (sub_2A8150 / sub_2A95D0 / sub_2AA2B0 /
//   sub_2AB330 / sub_2A79F0); state 25 disables both blends.
void sub_2AC540(EEContext& ctx);
// 0x2AF850 [btlCameraFollowTarget] Camera: follows the AI target record's current candidate (sub_2C0880): when it changed,
//   re-aims with or without a blend by the camera state.
void sub_2AF850(EEContext& ctx);
// 0x2B8F90 [btlFxHandleCreate] Allocates a 1,592-byte effect handle (RwMalloc, hint 0x40000): flags 8 for mode 2 else 0,
//   reference count 1.
void sub_2B8F90(EEContext& ctx);
// 0x2B9030 [btlFxHandleRelease] Drops a reference of an effect handle: at 1 with flag 8 stops it (sub_2B9220); at 0 frees it
//   (stops it first with flag 2).
void sub_2B9030(EEContext& ctx);
// 0x2BB8F0 [btlFxObjFreeArray] Frees an array of 48 effect objects: each stopped (sub_2BB580), unlinked from gBtl's
//   effect-object list and freed; then the array.
void sub_2BB8F0(EEContext& ctx);
// 0x2BBD00 [btlFxObjFreeGroup] Frees an effect object group: the object (+8, unlinked and freed), its handle (+12, released),
//   then the group.
void sub_2BBD00(EEContext& ctx);
// 0x2BD4F0 [btlFxPktUpdateSkillName] Update of the skill-name banner packet: with names shown (kFlags 0x200) shows the skill's
//   name on the first frame (sub_1FE9B0, MSG.TBL section 1) and runs 45 frames.
void sub_2BD4F0(EEContext& ctx);
// 0x2BD8E0 [btlFxPktUpdateResultPopup] Update of the result pop-up packet: builds the pop-up flags (miss / evade / weak /
//   resist / critical / down / support kinds from the result words and the skill's element and class) and calls
//   sub_1FE650 once; then waits for the panel (sub_1FEB50) while packets may start.
void sub_2BD8E0(EEContext& ctx);
// 0x2BF370 [btlCommandCalcTaskDestroy] Destroy callback of the "battle_command_calc" task: closes the panel; a finished battle
//   sets kFlags 0x4000 and closes the command task; frees the work and clears gBtl->kCmdCalcTask.
void sub_2BF370(EEContext& ctx);
// 0x2C0880 [btlAITargetGetCurrent] The current candidate of an AI target record (record[record +58]).
void sub_2C0880(EEContext& ctx);
// 0x2C08A0 [btlAITargetSetUid] Stores the chosen uid (u64) in an AI target record (+48).
void sub_2C08A0(EEContext& ctx);
// 0x2C0970 [btlAITargetSelectByUid] Selects the candidate whose action uid equals the record's stored uid (+48): index -> +58,
//   1; else index 0, 0.
void sub_2C0970(EEContext& ctx);
// 0x2C09F0 [btlAITargetGetSideMask] The side mask of an AI target record's candidates (1 << unit side, or-ed).
void sub_2C09F0(EEContext& ctx);
// 0x2C0AC0 [btlAITargetPickSupport] Auto-target for a support skill (records with two or more candidates, commands 1..3, a
//   single-target skill): a cure skill (+24 == 2) picks the first candidate with its status (+28), a buff the first
//   without its effect (+32); HP formulas 2/5/9/11/15 the lowest HP; SP formulas the lowest SP.
void sub_2C0AC0(EEContext& ctx);
// 0x2C0E30 [btlAIFindUnit] The AI unit finder: the first combatant action whose unit is on a side of the mask, alive when the
//   status mask holds 0x80000, without the masked statuses, with the unit id.
void sub_2C0E30(EEContext& ctx);
// 0x2C0F40 [btlAICountUnits] Counts the candidates (collected by sub_2BFCB0) that are combatants, free of the status mask and
//   for which the condition fn(candidate, param) differs from 'expect'; stores them when an output array is given.
void sub_2C0F40(EEContext& ctx);
// 0x2C12F0 [btlAICondMyHp] AI condition MYHP (row 1): 100 * HP <= max HP * param.
void sub_2C12F0(EEContext& ctx);
// 0x2C13D0 [btlAICondMySp] AI condition MYMP (row 2): 100 * SP <= max SP * param.
void sub_2C13D0(EEContext& ctx);
// 0x2C1590 [btlAICondAllyLevelOver] AI condition FRLV_O (row 7): the mean level of the acting unit's side (living units) >=
//   param.
void sub_2C1590(EEContext& ctx);
// 0x2C1650 [btlAICondAllyCount] AI condition FRCNT (row 9): living units on the acting unit's side <= param.
void sub_2C1650(EEContext& ctx);
// 0x2C16A0 [btlAICondEnemyCount] AI condition ENCNT (row 10): living units on the other side <= param.
void sub_2C16A0(EEContext& ctx);
// 0x2C1D90 [btlAICondFirstStrike] AI condition SENSEI (row 21, first strike): the unit has not acted yet and its side won the
//   advantage roll (+26 == 2 enemies / 1 party).
void sub_2C1D90(EEContext& ctx);
// 0x2C1E10 [btlAICondMyRepel] AI condition MYHANSYA (row 22): the unit repels the element (affinity bit 0x2000000).
void sub_2C1E10(EEContext& ctx);
// 0x2C1ED0 [btlAICondMyWeak] AI condition MYWEAK (row 25): the unit is weak to the element (affinity bit 0x8000000).
void sub_2C1ED0(EEContext& ctx);
// 0x2C24D0 [btlAICondTurn] AI condition TURN (row 43): turns taken (+32) <= param.
void sub_2C24D0(EEContext& ctx);
// 0x2C3300 [btlAICondEnemyOverLevel] AI condition ENOVERLV (row 70): some opposing combatant is at least param levels above
//   the acting unit.
void sub_2C3300(EEContext& ctx);
// 0x2C3400 [btlAICondMyEffect] AI condition MYHOJO (row 71): the unit has an active effect of the mask (sub_301CA0).
void sub_2C3400(EEContext& ctx);
// 0x2C3770 [btlAITargetPickDefault] AI target selector AI (row 0, the fallback): all candidates for a multi-target skill; the
//   only one; otherwise a random one -- or, for the damage formulas against party members with fewer than five
//   candidates, a pick weighted towards the lowest HP ratio (the weights 0x696FA0 by candidate count, the list
//   bubble-sorted by HP / max HP).
void sub_2C3770(EEContext& ctx);
// 0x2C48A0 [btlAIPickBestSkill] Of a skill list, the skill (0 entries skipped) whose damage (HP + datCalcDamage(skill, me, it,
//   1, 1, 1, 0, 1)) leaves the target with the least HP; the first kill beats any survivor and a kill with less
//   overkill beats an earlier kill; -1 when none. Kind 0 keeps only all-target skills (SkillRecord +8 == 1), kind 1
//   only single-target ones (+8 == 0), others every skill. Then sub_301870 on both units.
void sub_2C48A0(EEContext& ctx);
// 0x2C6A00 [btlAISetCommand] Decodes an AI command code into the command record (+52 command, +54 skill, +62 argument): 0x8000
//   attack (the weapon's attack skill, command 1), 0x8001 / 0x8006 / 0x8007 / 0x8008 the commands 6 / 11 / 8 / 12,
//   0x8002 command 7, 0x8005 nothing, 0x8004 a random Mix-Raid skill (command 2), 0x1xxx command 9 with skill 341 and
//   argument xxx, 0x2xxx command 7 with action +220 = xxx, any other code the skill itself (command 2).
void sub_2C6A00(EEContext& ctx);
// 0x2C6BA0 [btlAIEvalRow] The unit's AICALC section-15 row (164 bytes per enemy id): for set 0 then set 1, three conditions
//   (query words kind << 24 | parameter through the table 0x6971B0; kind 0 = false) and eight answer bytes for the
//   combinations c0&c1&c2, c0&c1, c0&c2, c1&c2, c0, c1, c2, always; the first true combination whose answer is not 8
//   gives the answer, 0 when none.
void sub_2C6BA0(EEContext& ctx);
// 0x2C6E30 [btlAIPickRowEntry] Weighted random pick among the five 8-byte entries of a row's set (weights at +44): the entry,
//   or the default 0x7CC740 when all weights are 0.
void sub_2C6E30(EEContext& ctx);
// 0x2C7250 Whether an AI script wait is active (+48 or a task at +76).
void sub_2C7250(EEContext& ctx);
// 0x2C7280 Polls the AI script wait: 1 when there is none or its task ended (then clears it).
void sub_2C7280(EEContext& ctx);
// 0x2D0D00 AI command: flushes the hero's requests and queues the camera 3 / 4095 and the hero's camera 28.
void sub_2D0D00(EEContext& ctx);
// 0x2D1A70 1 when the battle is not over (kFlags 0x80 clear) and sub_2FD7C0 holds.
void sub_2D1A70(EEContext& ctx);
// 0x2D2280 [btlGridFromPos] A world position to the battle grid: cell = round((x + 1750) / 25) for x and z (out pointers
//   optional).
void sub_2D2280(EEContext& ctx);
// 0x2D2340 [btlGridSetCorners] Writes a unit's four grid corner points from its cell and its size in cells (rounded up).
void sub_2D2340(EEContext& ctx);
// 0x2D2990 [btlGridSide] Side of a point against a segment on the grid plane: the sign of the 2D cross product (-1 / 0 / 1).
void sub_2D2990(EEContext& ctx);
// 0x2D3E00 [btlGridPlaceUnit] Places a unit on the grid: its cell from its position, the corners, optionally the cell centre,
//   the size; links its grid record into gBtl's list.
void sub_2D3E00(EEContext& ctx);
// 0x2D4040 [btlGridUpdateUnit] Re-places a placed unit when its cell or size changed: 1 when it moved.
void sub_2D4040(EEContext& ctx);
// 0x2D4ED0 [btlEscapeRoll] The escape roll: encounter 469 escapes only when no entry of the sub_1756F0 / sub_174A90 list has
//   id 76, 468 always; otherwise nothing while gBtl kEscRowA is 0, then ENCOUNT flag 2 never / 4 always, the hero's own
//   turn always, else datCalcRand(100) < AICALC section 6 [kEscRowA - 1 (max 8)] + [9 + kEscRowB - 1 (max 5)] (a zero
//   kEscRowB adds nothing).
void sub_2D4ED0(EEContext& ctx);
// 0x2D50C0 [btlAdvantageRoll] The advantage roll at the battle start (stored in gBtl kAdvantage): 0 normal, 1 the party
//   strikes first, 2 the enemies strike first. Encounter 506 with flag 4889 -> 2; ENCOUNT flags 0x8 -> 0, 0x10 -> 2, 0x800 -> 1; setup flag 4 ->
//   0; setup flag 1: c = 20 * party mean level / enemy mean level (halved when a party unit has skill 560), 2 with flag
//   4889, else datCalcRand(100) < c ? 0 : 2; setup flag 2: 0 without flag 4889 or with setup flag 8, else c = 20 *
//   enemy mean / party mean and datCalcRand(100) <= c ? 2 : 0; neither flag -> 1.
void sub_2D50C0(EEContext& ctx);
// 0x2D5570 [btlEnemyPickVariant] A Tartarus shadow's variant: enemy 277 becomes one of eight (256..262, 265) at random, 274
//   becomes 290 with 5 %; -1 otherwise.
void sub_2D5570(EEContext& ctx);
// 0x2D56A0 [btlEnemyGetVoiceSet] Enemy id -> its sound / voice set (a compare ladder; 0 for none).
void sub_2D56A0(EEContext& ctx);
// 0x2D6290 1 when sub_2BFF60 returns 0 (a single-target command).
void sub_2D6290(EEContext& ctx);
// 0x2D6460 [btlResultGetReaction] The hit-reaction kind of a result: miss / dodge (-2), down 8, dead 2, knocked down 10, a
//   guard (22 / -4), a weak hit (22 / -3), a counter (18 / 2), the boss reaction 19.
void sub_2D6460(EEContext& ctx);
// 0x2D7FB0 Creates packet 1793 (8 bytes: the action, a byte).
void sub_2D7FB0(EEContext& ctx);
// 0x2D8040 Update of packet 1795: sub_302C50 on the action's DatUnit. Done at once.
void sub_2D8040(EEContext& ctx);
// 0x2D8090 Creates packet 1795 (4 bytes: the action).
void sub_2D8090(EEContext& ctx);
// 0x2D8110 [btlActionPktUpdatePayCost] Update of the cost packet 1794: an item command uses up the item (the hero's stock or
//   the member's 12 slots); a skill pays its cost (sub_3083F0) from SP or HP by the skill's cost kind (+3). Done at
//   once.
void sub_2D8110(EEContext& ctx);
// 0x2D8330 [btlActionPktCreatePayCost] Creates the cost packet 1794 (4 bytes: the action).
void sub_2D8330(EEContext& ctx);
// 0x2D8B40 [btlSupportLineHeroTurn] Support line picker 15 (the hero's turn): flags 4960..4962 lines, line 108 while gBtl
//   kEscRowA is 0, else by HP (> 70 %, 31..70 %, <= 30 %) and the navigator flag sub_2DDC10(6).
void sub_2D8B40(EEContext& ctx);
// 0x2D8F70 [btlSupportLineChain] Support line picker 22 (a member's one-more chain): by party id, the chain count (+40) and
//   the living enemies; marks the action voiced (+26 bit 6).
void sub_2D8F70(EEContext& ctx);
// 0x2D9CA0 [btlSupportLineMember] Support line picker 27: a line per party id 2..10 (355..369).
void sub_2D9CA0(EEContext& ctx);
// 0x2DB480 [btlSupportGetPartyState] Party state for the support lines: 0 a live reinforcement without flag bit 0, 2 all live
//   reinforcements flagged, 3 a dead party member missing from the battle, else 1.
void sub_2DB480(EEContext& ctx);
// 0x2DB740 [btlSupportPktCreateLine] Creates the support line packet 2048 (24 bytes), update sub_2DB6A0.
void sub_2DB740(EEContext& ctx);
// 0x2DB890 Creates packet 2050 (no data), update sub_2DB860.
void sub_2DB890(EEContext& ctx);
// 0x2DBFE0 Creates packet 2051 (8 bytes: the mode, 2 in The Answer).
void sub_2DBFE0(EEContext& ctx);
// 0x2DC070 [btlAilmentSkipsTurn] Whether an ailment costs the unit its turn: down (0x100000) -> 1; the ailments 0x37F ->
//   datCalcRand(100) < 100 (50 when the low status bits are exactly 8).
void sub_2DC070(EEContext& ctx);
// 0x2DC180 [btlAilmentRecoverRoll] The ailment recovery roll: for each status bit a chance (datScriptCalc formulas 8..14, or
//   none) and a turn limit (halved by skill 610, 1 with 611); returns the bits that recover this turn (limit reached or
//   the roll won).
void sub_2DC180(EEContext& ctx);
// 0x2DD100 [btlSoundPktCreate2306] Creates the sound packet 2306 (6 bytes: three ids).
void sub_2DD100(EEContext& ctx);
// 0x2DD4A0 [btlSoundPktCreate2307] Creates the sound packet 2307 (16 bytes).
void sub_2DD4A0(EEContext& ctx);
// 0x2DD5E0 [btlSoundPktCreate2308] Creates the sound packet 2308 (2 bytes).
void sub_2DD5E0(EEContext& ctx);
// 0x2DDC10 [btlVoiceGetMemberFlag] The party member's voice flag (table 0x697BD8 by id >= 2; -1 none) through datGetFlag.
void sub_2DDC10(EEContext& ctx);
// 0x2DDC80 [btlVoiceIsFirstLineDue] Whether a party member's first-battle line is still due (flags 4951..4958 clear).
void sub_2DDC80(EEContext& ctx);
// 0x2DE150 [btlVoiceLineA] Voice line of a party member (flag 388 required), by id.
void sub_2DE150(EEContext& ctx);
// 0x2DE3C0 [btlVoiceLineB] Voice line of a party member, by id.
void sub_2DE3C0(EEContext& ctx);
// 0x2DE4E0 [btlVoiceLineTurn] Voice line of a party member's turn by HP (> 70 %, 31..70 %, <= 30 %; tired after 3 turns) and
//   the member's flag.
void sub_2DE4E0(EEContext& ctx);
// 0x2E2A10 Creates the sound packet 2560 (8 bytes).
void sub_2E2A10(EEContext& ctx);
// 0x2E2BE0 [btlSoundPktCreateCue] Creates the sound packet 2561 (24 bytes: action, cue, two words, a short).
void sub_2E2BE0(EEContext& ctx);
// 0x2E2EC0 Creates the sound packet 2563 (12 bytes).
void sub_2E2EC0(EEContext& ctx);
// 0x2E38A0 Creates the event packet 3075 (2 bytes).
void sub_2E38A0(EEContext& ctx);
// 0x2E3990 Creates the event packet 3076 (8 bytes).
void sub_2E3990(EEContext& ctx);
// 0x2E3A90 Creates the event packet 3077 (8 bytes).
void sub_2E3A90(EEContext& ctx);
// 0x2E3B50 Creates the event packet 3078 (16 bytes: three party ids, the all-out portraits).
void sub_2E3B50(EEContext& ctx);
// 0x2E3CD0 Update of packet 3080: destroys gBtl's event task. Done at once.
void sub_2E3CD0(EEContext& ctx);
// 0x2E3D10 Creates packet 3080 (no data).
void sub_2E3D10(EEContext& ctx);
// 0x2E42C0 Returns sub_2FD4A0().
void sub_2E42C0(EEContext& ctx);
// 0x2E4520 [btlAIStatusSkillCheck] Whether a status skill is worth casting on the action's targets: 3 / 5 when every target
//   already has every effect bit, 4 when sub_3068D0 gives every target a value, else 0.
void sub_2E4520(EEContext& ctx);
// 0x2E4720 Small id map: 2..6 -> 200..204, 7 -> 217, else 0.
void sub_2E4720(EEContext& ctx);
// 0x2E47A0 As sub_2E4520 without the formula pass: 3 / 7 when every target already has the effect, else 0.
void sub_2E47A0(EEContext& ctx);
// 0x2E4910 As sub_2E47A0 for the acting unit itself.
void sub_2E4910(EEContext& ctx);
// 0x2F6C50 [btlBossGetIndex] Boss enemy id -> boss index 0..30 (-1 for none).
void sub_2F6C50(EEContext& ctx);
// 0x2F9BC0 Creates packet 3584 (no data), callbacks sub_2F9710 / sub_2F9B60.
void sub_2F9BC0(EEContext& ctx);
// 0x2FA510 [btlBossScheduleEvent] Boss event scheduler: for the boss encounters 417..436, starts the boss's scripted sequence
//   (sub_2E4220 with a pair of callbacks) at the right moment of a boss unit's turn.
void sub_2FA510(EEContext& ctx);
// 0x2FB860 [btlBossRemapMotion] Boss motion remap: for the boss encounters 0x1A0..0x1B4 a boss unit's motion through its table
//   (some by the boss work words or effect / HP state); -1 when not remapped.
void sub_2FB860(EEContext& ctx);
// 0x2FC520 [btlBossGetEffectRow] A boss unit's EFFECT.TBL section-5 row (+2), 0 for others and indices 20 / 21.
void sub_2FC520(EEContext& ctx);
// 0x2FCAA0 [btlBossGetWork] Copies the boss work words (gBtl +2884..+2892) for a boss unit of encounters 0x1A7..0x1B3; 1 when
//   copied.
void sub_2FCAA0(EEContext& ctx);
// 0x2FD220 Encounter 421 rule: sub_30AF00 between the two units and a pending boss action without a phase.
void sub_2FD220(EEContext& ctx);
// 0x2FD4A0 [btlBossTaskAlive] Whether gBtl's boss task still exists (clears it when it ended).
void sub_2FD4A0(EEContext& ctx);
// 0x2FD820 Encounter 429: the panel set-up calls (sub_1FECE0 / sub_1FEE20 from the fourth phase on).
void sub_2FD820(EEContext& ctx);
// 0x2FDBB0 Whether a persona model accepts the action's shot (boss rules on: model row flags 1 / 0x20 with sub_2D63B0 /
//   sub_2D6290).
void sub_2FDBB0(EEContext& ctx);
// 0x2FDFE0 Encounter 436 rule: a single-target magic HP skill aimed at boss 241.
void sub_2FDFE0(EEContext& ctx);

}  // namespace p3fes::game
