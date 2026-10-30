// The field layer, third pass, part "kosaka" (Phase 5 slice `field3`; docs/ANALYSIS/26_field.md sections 4.1, 7.2):
// the "battle kosaka" encounter task of k_battle.c (a field-side skirmish between field units: create, update,
// destroy, join, the live-task table 0x875A40), the navigator's "supporter proc" of k_support.c (support comments run
// as BF scripts every 901 frames: dead, low-HP, ailing and wounded party members, the Reaper warning) with its three
// party filters, and the player's virtual pad task ("player pad proc": the pad -> hero move / turn / idle animations,
// the camera turns) with its creators and its "rotate pc" / "set free camera proc" companions.
// game/src/field/field3_kosaka.cpp (p3fes_handgen bodies made readable), pair tests tests/game/test_field3_kosaka.cpp.
//
// Names: symbols/functions.json's names stay (`sub_<addr>` for most); a proposed name (ours, from the instructions,
// strings and callers) is given in brackets. Every body is register- and frame-faithful (the hg_cpu register view):
// arguments in $a0.., the result in $v0, every GPR / FPR / HI / LO / ACC / FCR31 bit as the original at every check
// point, call and return.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace f3ks {

inline constexpr s32 kTaskWork = 60;  // KwlnTask +60: the task's work block

// --- the "battle kosaka" work (84 bytes, RwHeapCalloc'd by K_Battle_CreateBattleTask) ---------------------------
inline constexpr u32 kKsWorkSize = 84;
inline constexpr s32 kKsState = 0;          // 0 set-up, 1 fighting, 2 over (the update then returns -1)
inline constexpr s32 kKsSlot = 4;           // index of this task in kKsTasks
inline constexpr s32 kKsPause = 8;          // 1 = paused (sub_1D8C60 sets it on every live task)
inline constexpr s32 kKsEffect = 12;        // the skirmish effect instance (sub_1A91B0 on sField +4608)
inline constexpr s32 kKsPartyCount = 16;    // party field units in kKsParty
inline constexpr s32 kKsEnemyCount = 20;    // enemy field units in kKsEnemies
inline constexpr s32 kKsParty = 24;         // FldUnit*[4]
inline constexpr s32 kKsEnemies = 40;       // FldUnit*[4]
inline constexpr s32 kKsTurnTimer = 56;     // frames since the last turn
inline constexpr s32 kKsTurnPeriod = 60;    // frames per turn: 120 before the first, then at most 22
inline constexpr s32 kKsReaper = 64;        // 1 when the enemy is encounter 506 (the Reaper): the party never acts
inline constexpr s32 kKsBattlerCount = 68;  // kKsPartyBattlers + kKsEnemyBattlers
inline constexpr s32 kKsPartyBattlers = 72; // = kKsPartyCount (one DatUnit per party unit)
inline constexpr s32 kKsEnemyBattlers = 76; // sum of the enemies' encounter instances' u16 +2 (DatUnit count)
inline constexpr s32 kKsActor = 80;         // the battler whose turn it is (a K_Battle_GetNthDatUnit index)
inline constexpr u32 kKsTasks = 0x875A40u;  // u32[3]: the live encounter tasks (fldhi::kBattleKosakaTasks)
inline constexpr u32 kKsTaskCount = 3;
inline constexpr u32 kEncReaper = 506;      // encounter id of the Reaper (encounter instance u16 +8)
inline constexpr u32 kKsFirstTurnDelay = 120;

// --- field units (448 bytes; gFldUnitsPc 0x8717A0 [4], gFldUnitsEc 0x86EDA0 [24]) -----------------------------
inline constexpr u32 kPcUnits = 0x8717A0u;
inline constexpr u32 kEcUnits = 0x86EDA0u;
inline constexpr u32 kUnitSize = 448;
inline constexpr s32 kUnitInstance = 72;    // encounter instance (enemy) / DatUnit holder (party); 0 = free
inline constexpr s32 kUnitModel = 80;
inline constexpr s32 kUnitResource = 84;    // scene resource; with +72 the unit is live
inline constexpr s32 kUnitTask368 = 368;    // the unit's think / move task (handed to sub_1B00C0 when it is held)
inline constexpr s32 kUnitLevel = 388;      // s32: the level the party panel last showed
inline constexpr s32 kUnitId = 424;         // u16: the party member / persona id (party panel, g_data readers)
inline constexpr s32 kUnitScrMem = 436;     // the unit's script memory and size (the level-up script)
inline constexpr s32 kUnitScrSize = 440;
inline constexpr s32 kResController = 480;  // scene resource +480: its collision controller task
inline constexpr s32 kInstEnemyCount = 2;   // encounter instance u16 +2: its DatUnits
inline constexpr s32 kInstEncounter = 8;    // encounter instance u16 +8: the encounter id
inline constexpr s32 kDatUnitHp = 8;        // DatUnit u16 +8 (types/unit.h)

// --- sField 0x869F60 (K_Field_Get) -------------------------------------------------------------------------------
inline constexpr s32 kFieldPadTask = 12;     // the virtual pad task
inline constexpr s32 kFieldEventTask = 8;    // the field event task
inline constexpr s32 kFieldCamera = 4;       // the camera controller task
inline constexpr s32 kFieldPopTask = 36;     // the enemy pop scheduler task
inline constexpr s32 kFieldPartyPanel = 40;  // the party panel task (sub_18BEE0(panel, id, mode))
inline constexpr s32 kFieldEplSkirmish = 4608;  // EPL effect object: the skirmish dome (sub_1A91B0 / 1A9390 / 1A9400)
inline constexpr s32 kFieldEplDeath = 4612;     // EPL effect object: an enemy's death flash
inline constexpr s32 kFieldEplHit = 4620;       // EPL effect object: a hit flash

// --- model matrices (sub_318B60 returns the model's RwMatrix) and RwMatrix --------------------------------------
inline constexpr s32 kMtxRight = 0, kMtxFlags = 12, kMtxUp = 16, kMtxAt = 32, kMtxPos = 48;

// --- the supporter work (336 bytes, "supporter proc") -------------------------------------------------------------
inline constexpr u32 kSupWorkSize = 336;
inline constexpr s32 kSupState = 0;         // 0 start, 1 running, 3 waiting for its scripts, 4 over (returns -1)
inline constexpr s32 kSupPause = 4;         // 1 = paused
inline constexpr s32 kSupReaperSaid = 8;    // the "Reaper is here" comment (procedure 2) was given
inline constexpr s32 kSupStamp = 12;        // g_kwlnFrameCounterB at the last round
inline constexpr s32 kSupTasks = 16;        // u32[16]: the script tasks
inline constexpr s32 kSupLists = 80;        // [16] x 16 bytes {u32 count, u32 ids[3]}: the scripts' user data
inline constexpr u32 kSupSlots = 16;
inline constexpr u32 kSupPeriod = 901;      // frames between rounds (sltiu 0x385)
inline constexpr s32 kGpFrameCounterB = -19432;  // 0x7CE108 g_kwlnFrameCounterB
inline constexpr s32 kGpSupportScript = -19152;  // 0x7CE220: the navigator's script memory (procedures 0..6)
inline constexpr s32 kGpLowHpRatio = -31856;     // 0x7CB080: 0.3
inline constexpr s32 kGpWoundedRatio = -32572;   // 0x7CADB4: 0.6

// --- the player pad work (144 bytes, "player pad proc") ---------------------------------------------------------
inline constexpr u32 kPadWorkSize = 144;
inline constexpr s32 kPadState = 0;         // 0 start, 1 running, 2 wait for kPadWaitTask, 5 over (returns -1)
inline constexpr s32 kPadRotateTask = 80;   // the "rotate pc" task (sub_1E14E0)
inline constexpr s32 kPadController = 84;   // the hero's collision controller task
inline constexpr s32 kPadModel = 88;        // the hero's model
inline constexpr s32 kPadLockEvent = 92;    // 1 = input off (sub_1E1300, the field event task)
inline constexpr s32 kPadLockNpc = 96;      // 1 = input off (sub_1E1360, the NPC / map code)
inline constexpr s32 kPadAnimSet = 108;     // the current animation was started
inline constexpr s32 kPadAnim = 112;        // the current move animation id (walk / run)
inline constexpr s32 kPadCamYaw = 116;      // f32 degrees: the camera heading the turn tasks aim at
inline constexpr s32 kPadIdle = 120;        // frames standing still (60 -> the idle animation, 361 -> the tired one)
inline constexpr s32 kPadAnimDebounce = 124;  // frames the new move animation was requested
inline constexpr s32 kPadStill = 128;       // frames without input (4 before the idle count starts)
inline constexpr s32 kPadCamTask = 132;     // the camera rotation task (sub_1D6270 / sub_1D6630)
inline constexpr s32 kPadWaitTask = 136;    // a task state 2 waits for
inline constexpr u32 kPadHeld = 0x7E094Cu;  // u16 the held pad buttons
inline constexpr u32 kPadPressed = 0x7E094Eu;  // u16 gPadFlags: the newly pressed buttons
inline constexpr u32 kPadStickLX = 0x7E095Eu;  // u8 sticks, 128 = centre: left x, left y, right x, right y
inline constexpr u32 kPadStickLY = 0x7E095Fu;
inline constexpr u32 kPadStickRX = 0x7E0960u;
inline constexpr u32 kPadStickRY = 0x7E0961u;
inline constexpr s32 kGpPadSpeed = -19004;  // 0x7CE2B4 f32: the hero's speed this frame (0 / 13 / sin-scaled)

}  // namespace f3ks

// --- the "battle kosaka" encounter task (k_battle.c) ----------------------------------------------------------------
void K_FldCamera_UpdateBattleKosakaTask(EEContext& ctx);   // 0x1D7D40 [K_Battle_UpdateBattleTask] (task) -> 0 / -1: set-up, timed turns
void K_FldCamera_DestroyBattleKosakaTask(EEContext& ctx);  // 0x1D89B0 [K_Battle_DestroyBattleTask] (task): item drop, panel, slot freed
void K_Battle_CreateBattleTask(EEContext& ctx);  // 0x1D8B00 (parent, party unit, enemy unit) -> task or 0
void sub_1D8CB0(EEContext& ctx);  // 0x1D8CB0 [K_Battle_InitTasks] clears 0x875A40[3], then sub_434F70
void sub_1D8CF0(EEContext& ctx);  // 0x1D8CF0 [K_Battle_DestroyAllTasks] kwlnTaskDestroyWithHierarchy on each live task
void sub_1D8E60(EEContext& ctx);  // 0x1D8E60 [K_Battle_JoinUnits] (task, party unit, enemy unit) -> 1 if one joined

// --- the navigator's supporter proc (k_support.c) ------------------------------------------------------------------
void sub_1D9310(EEContext& ctx);  // 0x1D9310 [K_Support_ListLowHp] (list) -> 1: members 1..3 alive with HP / max < 0.3
void sub_1D94D0(EEContext& ctx);  // 0x1D94D0 [K_Support_ListAiling] (list) -> 1: members 1..3 with status bit 7, HP / max >= 0.3
void sub_1D96A0(EEContext& ctx);  // 0x1D96A0 [K_Support_ListWounded] (list) -> 1: members 1..3 with 0.3 <= HP / max < 0.6
void sub_1D9860(EEContext& ctx);  // 0x1D9860 [K_Support_UpdateTask] (task) -> 0 / -1: the comment rounds
void sub_1D9EE0(EEContext& ctx);  // 0x1D9EE0 [K_Support_DestroyTask] (task): RwFree(work)
void sub_1D9F10(EEContext& ctx);  // 0x1D9F10 [K_Support_CreateTask] (parent) -> task, or 0 outside Tartarus / on major 33

// --- the virtual pad ("player pad proc") ------------------------------------------------------------------------------
void sub_1E04E0(EEContext& ctx);  // 0x1E04E0 [K_FreeCamera_DestroyTask] (task): RwFree(work)
void sub_1E0510(EEContext& ctx);  // 0x1E0510 [K_FreeCamera_CreateTask] (parent, arg -> work +80) -> task or 0
void sub_1E05B0(EEContext& ctx);  // 0x1E05B0 [K_VPad_UpdateTask] (task) -> 0 / -1: pad -> hero move, turn, idle
void sub_1E1200(EEContext& ctx);  // 0x1E1200 [K_VPad_DestroyTask] (task): RwFree(work)
void sub_1E1230(EEContext& ctx);  // 0x1E1230 [K_VPad_CreateTask] (parent, controller, model) -> task or 0
void sub_1E1300(EEContext& ctx);  // 0x1E1300 [K_VPad_SetEventLock] (task, on): work +92, back to the stand animation
void sub_1E1360(EEContext& ctx);  // 0x1E1360 [K_VPad_SetNpcLock] (task, on): work +96, back to the stand animation
void sub_1E14B0(EEContext& ctx);  // 0x1E14B0 [K_VPad_DestroyRotateTask] (task): RwFree(work)
void sub_1E14E0(EEContext& ctx);  // 0x1E14E0 [K_VPad_CreateRotateTask] (parent, controller, model) -> "rotate pc" task or 0

}  // namespace p3fes::game
