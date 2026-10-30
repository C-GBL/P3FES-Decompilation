// Field (exploration) layer leaves, hand-decompiled from SLUS_216.21 (docs/ANALYSIS/26_field.md): the field root's
// accessors, the Tartarus ("automatic dungeon") floor accessors, the random-floor predicate, the point-in-triangle
// and closest-point-on-segment math of the collision / hit tests, the movement request of a collision controller,
// and the encounter ("battle kosaka") unit-list lookups.
//
// Names: the IDA names of functions.json (since master update #4 the names of symbols/deltas/field.sym, with their
// evidence). The trailing comment gives the function's address.
//
// Register footprint: each hand version leaves every GPR / FPR / FCR31.C / ACC the original writes holding the value
// the original leaves there (scratch registers included; tests/game/test_field.cpp compares the whole register file),
// and reads $gp from the register as the original does.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace fld {

// --- guest addresses (26_field.md sections 1-3) ------------------------------------------------------------------
inline constexpr u32 kField = 0x869F60u;            // sField: the field's task table + map grid (4,636 bytes, K_Field_Init 0x1B90F0)
inline constexpr s32 kGpPhase = -19108;             // gp-0x4AA4 = 0x7CE24C: field load phase (0 load, 3 scene ready, 1 setup, 2 running)
inline constexpr s32 kGpDungeonTask = -19080;       // gp-0x4A88 = 0x7CE268: the "automatic dungeon" kwln task (NULL outside Tartarus)
inline constexpr s32 kGpSceneIds = -22448;          // gp-0x57B0 = 0x7CD540: -> the scene record 0x95AFC0 {s32 major, s32 minor, ...}
inline constexpr u32 kBattleKosakaTasks = 0x875A40u;  // u32[3]: the live "battle kosaka" encounter tasks (K_Battle_CreateBattleTask)

inline constexpr u32 kTaskWork = 60;  // KwlnTask +0x3C: the task's work pointer (kwlnTaskGetWorkData)

// Field root work (k_Field_CreateFieldRootTask 0x1BA5F0, 104 bytes): +0 state, +16 u16 major, +18 u16 minor,
// +20 u16 entry, +24 / +26 u16 scene sub-ids.
inline constexpr u32 kRootMajor = 16;
inline constexpr u32 kRootMinor = 18;

// Dungeon work (K_FldDungeon_CreateTask 0x1BFBC0, 64 bytes): +4 floor index, +32 floor table (gFldDngFloorsData
// 0x867F60, 16 bytes per floor), +40 floor kind (sub_1BF340: 0 normal, 1..4 the random floor events).
inline constexpr u32 kDngFloor = 4;
inline constexpr u32 kDngFloorTable = 32;
inline constexpr u32 kDngFloorKind = 40;
inline constexpr u32 kFloorEntrySize = 16;
inline constexpr u32 kExplorableFloorEnd = 400;  // floors 2..399 are explorable; 0/1 entrance, 400+ scripted floors

// Collision controller work (K_FldFrame_CreateCtlTask 0x1AD660, 52 bytes).
inline constexpr u32 kCtlState = 0;        // 1 idle (accepts a move), 0 move pending (applied by the update task), 2 off
inline constexpr u32 kCtlVelocity = 20;    // f32[3]: this frame's displacement (applied in three thirds)
inline constexpr u32 kCtlDistance = 40;    // s32: accumulated (int) speed of the accepted moves
inline constexpr u32 kCtlStateIdle = 1;

// Battle kosaka work (K_Battle_CreateBattleTask 0x1D8B00, 84 bytes): +16 / +20 counts, +24 party field units[4],
// +40 enemy field units[4]; a field unit's +72 is its encounter instance {.., +4 DatUnit* units, +8 u32 encounter id}.
inline constexpr u32 kBkPartyCount = 16;
inline constexpr u32 kBkEnemyCount = 20;
inline constexpr u32 kBkParty = 24;
inline constexpr u32 kBkEnemy = 40;
inline constexpr u32 kFldUnitEncounter = 72;
inline constexpr u32 kEncounterUnits = 4;
inline constexpr u32 kDatUnitSize = 60;
inline constexpr u32 kEncounterUnitSlots = 6;

}  // namespace fld

// --- the field root (k_field.c) ------------------------------------------------------------------------------------
u32 K_Field_Get(EEContext& ctx);            // [K_Field_Get] &sField
s32 K_Fld_GetPhase(EEContext& ctx);            // [K_Fld_GetPhase] the load phase word
void K_Field_GetMajorId(EEContext& ctx);  // [register ABI] [K_Field_GetMajorId] root work +16
void K_Field_GetMinorId(EEContext& ctx);  // [register ABI] [K_Field_GetMinorId] root work +18

// --- the automatic dungeon (k_dungeon.c) ---------------------------------------------------------------------------
s32 K_FldDungeon_GetCurrentFloor(EEContext& ctx);  // [K_FldDungeon_GetCurrentFloor] 0 outside Tartarus
u32 K_FldDungeon_IsCurrentFloorExplorable(EEContext& ctx);  // [K_FldDungeon_IsCurrentFloorExplorable] 2 <= floor < 400
u32 K_FldDungeon_GetCurrentFloorData(EEContext& ctx);  // [K_FldDungeon_GetCurrentFloorData] &floors[floor] or 0
s32 K_FldDungeon_GetFloorKind(EEContext& ctx);  // [K_FldDungeon_GetFloorKind] work +40 or 0

// --- the scene ids (k_sceneDraw.c band) ------------------------------------------------------------------------------
u32 K_Scene_IsRandomFloor(EEContext& ctx);  // [K_Scene_IsRandomFloor] major 21..28 / 41..48 with minor 0

// --- collision math and movement (k_fldFrame band) -------------------------------------------------------------------
void K_FldFrame_IsPointInTriangle(EEContext& ctx);  // [register ABI] [K_FldFrame_IsPointInTriangle]
void K_FldFrame_ClosestPointOnSegment(EEContext& ctx);  // [register ABI] [K_FldFrame_ClosestPointOnSegment] returns out
void K_FldFrame_CtlMoveInDir(EEContext& ctx);  // [register ABI] [K_FldFrame_CtlMoveInDir] speed in $f12

// --- the encounter task (k_battle.c) ----------------------------------------------------------------------------------
void K_Battle_FindTaskOfUnit(EEContext& ctx);  // [register ABI] [K_Battle_FindTaskOfUnit]
void K_Battle_GetNthDatUnit(EEContext& ctx);  // [register ABI] [K_Battle_GetNthDatUnit]
void K_Battle_GetNthFieldUnit(EEContext& ctx);  // [register ABI] [K_Battle_GetNthFieldUnit]

}  // namespace p3fes::game
