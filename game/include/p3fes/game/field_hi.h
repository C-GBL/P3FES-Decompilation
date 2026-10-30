// The field layer, second pass (Phase 5 slice `field_hi`; docs/ANALYSIS/26_field.md, queue_field.txt rows >= 0x1C0000):
// the dungeon-work accessors next to the first slice's, the field event task's helpers (scene rules, unit pausing,
// the draw-command task, the camp / battle hand-off loops over the field units), the field-unit walks of k_unit.c
// (the four party units gFldUnitsPc 0x8717A0 and the 24 shadows gFldUnitsEc 0x86EDA0, 448 bytes each), the enemy
// pop scheduler's accessors and Reaper timer, the encounter ("battle kosaka") task accessors, the camera / footstep /
// virtual-pad task accessors and the NPC-placement list lookups. game/src/field/field_hi.cpp, pair tests
// tests/game/test_field_hi.cpp.
//
// Names: symbols/functions.json calls every function here `sub_<addr>` and the names stay; a proposed name (ours,
// from the instructions and the callers; not in any delta) is given in brackets. The trailing comment gives the role.
//
// Register footprint: every function leaves each GPR / FPR / FCR31 bit / HI / LO it writes holding the original's
// value at every check point, call and return (scratch registers included: a check point may preempt the thread and
// the kernel then stores the whole register file in guest memory). The non-leaf functions write their prologue
// spills to the guest stack, keep the original values in $s0..$s2, give every callee the original $ra and call it
// through its generated entry point.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace fldhi {

// --- guest addresses (26_field.md sections 2, 6, 7) -------------------------------------------------------------
inline constexpr u32 kPcUnits = 0x8717A0u;        // gFldUnitsPc[4]: the party's field units (the hero is unit 0)
inline constexpr u32 kEcUnits = 0x86EDA0u;        // gFldUnitsEc[24]: the shadows' field units
inline constexpr u32 kUnitSize = 448u;
inline constexpr u32 kPcUnitCount = 4u;
inline constexpr u32 kEcUnitCount = 24u;
inline constexpr u32 kPcModelSlots = 0x871EA0u;   // [4] {u16, u16, u32 model handle}: the party models (sub_1CD870 frees one)
inline constexpr u32 kBattleKosakaTasks = 0x875A40u;  // u32[3]: the live encounter tasks
inline constexpr u32 kLevelGapTable = 0x6836B0u;  // {s16 level, s16 max gap} rows ending at level -1 (sub_1C65E0)

// $gp-relative words (crt0's $gp = 0x7D2CF0).
inline constexpr s32 kGpDungeonTask = -19080;     // 0x7CE268: the "automatic dungeon" task
inline constexpr s32 kGpSceneIds = -22448;        // 0x7CD540: -> the scene record {s32 major, s32 minor, ...}
inline constexpr s32 kGpLiveEcCount = -19044;     // 0x7CE28C (gp-0x4A64): the number of live shadows (26_field.md 6.4)
inline constexpr s32 kGpCameraWord = -27176;      // 0x7CC2C8: written by the camera setter sub_1B5A00
inline constexpr s32 kGpFootstepFrame = -19432;   // 0x7CE108: copied into the footstep work by sub_1DA000
inline constexpr s32 kGpPadTurnSpeed = -19004;    // 0x7CE2B4: f32, sub_1E13C0 (non-positive -> the default below)
inline constexpr s32 kGpPadTurnDefault = -19136;  // 0x7CE230: f32
inline constexpr s32 kGpNpcList = -19000;         // 0x7CE2B8: list head, u16 id at +8, next at +108 (the NPC-placement band)
inline constexpr s32 kGpObjList = -18996;         // 0x7CE2BC: list head, u16 id at +80, next at +88

// Field unit (448 bytes) fields used here.
inline constexpr u32 kUnitActiveFlag = 68;        // set to 1 by sub_1CD8E0 (party units)
inline constexpr u32 kUnitInstance = 72;          // encounter instance (shadow) / DatUnit holder (party); 0 = free slot
inline constexpr u32 kUnitModel = 80;
inline constexpr u32 kUnitResource = 84;          // scene resource; with +72 the unit is "live"
inline constexpr u32 kUnitTask364 = 364;          // a kwln task (sub_1D0270 sets its flag 32)
inline constexpr u32 kUnitTask380 = 380;          // a kwln task (sub_1D1A90 / sub_1D1CE0 clear dead ones)
inline constexpr u32 kUnitLevel = 388;            // s32 (sub_1C65E0 averages the party's)
inline constexpr u32 kUnitModelKind = 396;        // s32 1..5 (sub_1D11B0)
inline constexpr u32 kUnitAnimIds = 414;          // u16[5] (sub_1CE880)

}  // namespace fldhi

// --- the automatic dungeon (k_dungeon.c) ---------------------------------------------------------------------------
s32 K_FldDungeon_GetScrSize(EEContext& ctx);            // [K_FldDungeon_GetScriptSize] dungeon work +56, 0 without the task
u32 sub_1C0070(EEContext& ctx);            // [K_FldDungeon_GetFloorKindScale] $f0 = 2.0 for floor kinds 1 / 3, else 1.0
u32 sub_1C03B0(EEContext& ctx, u64 req);   // [K_FldDungeon_IsRequestDone] 1 for no request, else H_Cdvd_IsFileLoaded != 0
void sub_1C00D0(EEContext& ctx);           // [K_FldDungeon_StopFloorEffect] sub_1A9400(work +44, work +48)
void sub_1C0110(EEContext& ctx);           // [K_FldDungeon_StartFloorEffect] work +48 = sub_1A91B0(work +44, zero vec3)

// --- the field event task helpers (k_event.c) ----------------------------------------------------------------------
void sub_1C2000(EEContext& ctx);  // [register ABI] [K_FldTWall_SetTarget] transparent-wall task work +516
u32 sub_1C6080(EEContext& ctx);            // [K_FldEvent_IsPadScriptAllowed] 0 in the listed scenes, else 1
void sub_1C65E0(EEContext& ctx);  // [register ABI] [K_FldUnit_IsLevelGapOk] flag 3173, or the party-average level rule
u32 K_FldEvent_IsUnitHero(EEContext& ctx, u64 unit);  // [K_FldEvent_IsUnitHero] unit == gFldUnitsPc
void sub_1CD650(EEContext& ctx);  // [register ABI] [K_FldEvent_SetPause] event work +4 (null task ignored)
void sub_1CD670(EEContext& ctx);  // [register ABI] [K_FldEvent_SetWork8] event work +8 (null task ignored)
void sub_1CD690(EEContext& ctx);  // [register ABI] [K_FldEvent_UpdateDrawCmdTask] sub_3B2CB0(320, 224, -1, 0, 0, work[0], 0, 0; 0.0)
void sub_1CD790(EEContext& ctx);  // [register ABI] [K_FldEvent_SetDrawCmdState] draw-command work +0

// --- the field units (k_unit.c) ------------------------------------------------------------------------------------
void sub_1CD870(EEContext& ctx);  // [register ABI] [K_FldUnit_FreePcModel] sub_3174E0 on slot's handle, slot cleared
void sub_1CD8E0(EEContext& ctx);           // [K_FldUnit_InitPcSlots] party units +68 = 1, model slots cleared
u32 sub_1CD940(EEContext& ctx);            // [K_FldUnit_FindFreePc] first party unit with +72 == 0, or 0
void sub_1CE880(EEContext& ctx);           // [K_FldUnit_RefreshPcAnims] sub_319230 for every live unit's 5 anim slots
void sub_1D0270(EEContext& ctx);           // [K_FldUnit_FlagAllTasks] kwln flag 32 on every unit's +364 task
u32 sub_1D0E40(EEContext& ctx);            // [K_FldUnit_GetLiveEcCount] the live shadow count ($gp-19044)
void sub_1D11B0(EEContext& ctx);           // [K_FldUnit_RecreateEcModels] shadow models by +396 kind (sub_316E00)
u32 sub_1D12D0(EEContext& ctx);            // [K_FldUnit_AreEcModelsReady] 0 while a shadow model is loading
void sub_1D1780(EEContext& ctx, u64 skip_hero_if_zero);  // [K_FldUnit_ResetPcs] sub_1D1640(unit, 0), unit 0 only when arg != 0
void sub_1D17F0(EEContext& ctx, u64 arg);  // [K_FldUnit_ResetEcs] sub_1D1640(unit, arg) for the 24 shadows
void sub_1D1860(EEContext& ctx, u64 arg);  // [K_FldUnit_SetPcVisible] sub_19C2F0(resource +484, arg) per live party unit
void sub_1D1910(EEContext& ctx);           // [K_FldUnit_StopPcAnims] sub_1A60D0(0, model, 0), then +380 = 0
void sub_1D19D0(EEContext& ctx);           // [K_FldUnit_StopPcAnims255] +380 = 0, then sub_1A60D0(0, model, 255)
u32 sub_1D1A90(EEContext& ctx);            // [K_FldUnit_ArePcTasksDone] 0 while a party unit's +380 task exists
void sub_1D1B60(EEContext& ctx);           // [K_FldUnit_StopEcAnims] as sub_1D19D0 for the shadows, 0
void sub_1D1C20(EEContext& ctx);           // [K_FldUnit_StopEcAnims255] as sub_1D19D0 for the shadows, 255
u32 sub_1D1CE0(EEContext& ctx);            // [K_FldUnit_AreEcTasksDone] as sub_1D1A90 for the shadows

// --- the enemy pop scheduler (k_unit.c) ----------------------------------------------------------------------------
void sub_1D3790(EEContext& ctx);  // [register ABI] [K_Unit_IsPopSchedulerIdle] scene 14/5, or work state 2
void sub_1D37F0(EEContext& ctx);  // [register ABI] [K_Unit_SetPopSchedulerPause] work +4 (null ignored)
void sub_1D3810(EEContext& ctx);  // [register ABI] [K_Unit_SetPopSchedulerPause2] work +8 (null ignored)
void sub_1D38A0(EEContext& ctx);  // [register ABI] [K_Unit_GetReaperTimeLeft] max(0, +12 - +16 / 30) (divu)

// --- the camera (k_fldCamera.c) ------------------------------------------------------------------------------------
void sub_1D5130(EEContext& ctx, u64 value);  // [K_FldCamera_SetGlobalWord] $gp-27176
void sub_1D5C00(EEContext& ctx);  // [register ABI] [K_FldCamera_GetMode] camera work +8
void sub_1D5E10(EEContext& ctx);  // [register ABI] [K_FldCamera_GetFrameMatrix] (camera work +12) + 64
void sub_1D5F30(EEContext& ctx);  // [register ABI] [K_FldCamera_SetTarget] work +204 = MT_Scene_GetRes(id) for type-1 ids

// --- the encounter task (k_battle.c) -------------------------------------------------------------------------------
void sub_1D8C60(EEContext& ctx, u64 value);  // [K_Battle_SetAllPause] work +8 of every live encounter task
void sub_1D8D50(EEContext& ctx);  // [register ABI] [K_Battle_GetPartyCount] encounter work +16
void sub_1D8D60(EEContext& ctx);  // [register ABI] [K_Battle_GetPartyUnit] encounter work +24 + 4n

// --- footstep / virtual pad / NPC placement ------------------------------------------------------------------------
void sub_1D9FD0(EEContext& ctx);  // [register ABI] [K_Footstep_IsActive] 1 for no task, else work state > 0
void sub_1DA000(EEContext& ctx);  // [register ABI] [K_Footstep_SetUnit] work +4, +12 = $gp-19432
void sub_1DD5E0(EEContext& ctx);  // [register ABI] [K_FldEffect_SetState] work +0
void sub_1DD5F0(EEContext& ctx);  // [register ABI] [K_FldEffect_SetModel] work +548
u32 sub_1E13C0(EEContext& ctx);            // [K_VPad_GetTurnSpeed] $f0 = $gp-19004, or $gp-19136 when <= 0
void sub_1E1820(EEContext& ctx);  // [register ABI] [K_VPad_IsMode1] work +64 == 1
u32 sub_1E1840(EEContext& ctx);            // [K_Npc_GetListHead] &$gp-19000
u32 sub_1E2810(EEContext& ctx, u64 id);    // [K_Npc_FindById] node with u16 +8 == id, or 0
u32 sub_1E29E0(EEContext& ctx, u64 id);    // [K_Obj_FindById] node with u16 +80 == id, or 0

}  // namespace p3fes::game
