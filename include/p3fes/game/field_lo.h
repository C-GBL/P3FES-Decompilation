// Field (exploration) layer, second pass, the band below 0x1C0000 (slice `field_lo`; docs/ANALYSIS/26_field.md,
// docs/ANALYSIS/queue_field.txt "open" rows): the collision controller's accessors (k_fldFrame), the scene-id
// predicates and scene-resource flag helpers (the k_scene band over mt_scene.c), the camera's debug-cylinder setters,
// the field root / dungeon / sequence-check accessors (k_field.c, k_dungeon.c, k_sequence.c), the EPL effect-handle
// accessors, the Tartarus grid cell marker of the floor layout generator, and the enemy-think action queue.
//
// Names: functions.json calls every function here `sub_<addr>`; a proposed name is given in brackets (ours, from the
// instructions and the callers named in 26_field.md; not in any delta, not imported). The trailing comment gives what
// the function does; "inf" marks a role inferred from the callers only.
//
// Register footprint: each hand version leaves every GPR / FPR / FCR31 bit the original writes holding the value the
// original leaves there, at every check point (entry, loop back-edges, each call) and at the return; the non-leaf
// ones write the original prologue spills on the guest stack and call through the callees' generated entry points
// with the original $ra (tests/game/test_field_lo.cpp compares the whole register file at every check point).
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace fldlo {

// --- guest addresses -----------------------------------------------------------------------------------------------
inline constexpr s32 kGpSceneIds = -22448;     // gp-0x57B0 -> the scene record 0x95AFC0 {s32 major, s32 minor, mgr, ..}
inline constexpr s32 kGpDungeonTask = -19080;  // gp-0x4A88: the "automatic dungeon" task (NULL outside Tartarus)
inline constexpr s32 kGpBlockCounter = -19092; // gp-0x4A94: the floor generator's placed-block counter (sub_1BB090)
inline constexpr s32 kGpFieldPack = -19348;    // gp-0x4B94: the resident field pack handle (sub_1B0910; inf)
inline constexpr u32 kDungeonSourceFile = 0x6833A0u;  // "k_dungeon.c" (the K_Assert file argument)
inline constexpr u32 kTaskWork = 60;           // KwlnTask +0x3C: the work pointer

// Scene record (mt_scene.c, `*(gp-0x57B0)`): +0 major, +4 minor, +8 resource manager, +24 / +28 words set by
// sub_1A0410 / sub_1A0420 (battle scene set-up and the event viewer).
inline constexpr u32 kSceneMajor = 0, kSceneMinor = 4, kSceneMgr = 8, kSceneWord24 = 24, kSceneWord28 = 28;
// Scene resource: +0 u16 id, +40 flags (bit 1: the flag the field's draw tasks test; sub_1A0150), +248 next in list.
inline constexpr u32 kResFlags = 40, kResNext = 248, kResFlagBit1 = 2;
inline constexpr u32 kResTypeBlock = 12;   // Tartarus blocks (id 0x3000 + 16 z + x)
inline constexpr u32 kResTypeChar = 4;     // MT_Scene_GetResListHead(4)
inline constexpr u32 kResType10 = 10;
inline constexpr u32 kFieldBlocksHidden = 52;  // sField + 52: 0 after sub_1A0040 set the block flag, 1 after it cleared it

// Collision controller work (K_FldFrame_CreateCtlTask 0x1AD660, 52 bytes; 26_field.md 4.2).
inline constexpr u32 kCtlState = 0, kCtlFlags = 4, kCtlRadius = 32, kCtlDistance = 40, kCtlGridX = 44, kCtlGridZ = 48;
inline constexpr u32 kCtlFlagNoCollision = 0x10000000u;  // bit 28: set when the radius is 0.0

// Camera debug-cylinder work (K_Draw_CreateCylinderTask; written by the camera controller 0x1D5220): +0 word,
// +4..+12 f32 position, +16 f32 radius, +20 f32 height.
inline constexpr u32 kCylWord = 0, kCylPos = 4, kCylRadius = 16, kCylHeight = 20;

// Field root work (k_Field_CreateFieldRootTask 0x1BA5F0): +24 / +26 u16 the scene sub-ids.
inline constexpr u32 kRootSubId1 = 24, kRootSubId2 = 26;

// Dungeon work (K_FldDungeon_CreateTask 0x1BFBC0): +12 shutdown request, +52 the dungeon script memory.
inline constexpr u32 kDngShutdown = 12, kDngScrMemory = 52;

// Floor grid (sField + 72 + 256 z + 16 x, 16 x 16 cells of 16 bytes; 26_field.md 6.2) as sub_1BB090 writes it:
// +0 taken, +1 the block's origin cell, +2 s8 block desc +0, +6 the caller's byte, +7 / +8 block width / depth,
// +9 the placed-block counter, +10 block desc +3, +11 the cell's byte of the block desc (+14 + 8 col of row `24 row`).
inline constexpr u32 kGridBase = 72, kGridRow = 256, kGridCell = 16, kGridSize = 16;
inline constexpr u32 kBlockRowStride = 24, kBlockCellStride = 8, kBlockCellByte = 14;

// EPL effect-handle work (sub_1A91B0 creates it; 26_field.md 2.1 +4596..): +0 state, +24 / +28 the default slot,
// +36 [n] handles, +68 [n] words, +100 [n] u16.
inline constexpr u32 kEplState = 0, kEplDefWord = 24, kEplDefHalf = 28, kEplHandles = 36, kEplWords = 68, kEplHalves = 100;

// Enemy-think work (the Y_* enemy-think band 0x44AAF0..): +8 mode, +12 the unit (its +480 = the collision task),
// +24 / +28 words, +32 [47] 24-byte action entries {+0 type, +4..+12 f32 target, +16 f32 value}, count at +28.
inline constexpr u32 kThinkMode = 8, kThinkUnit = 12, kThinkWord24 = 24, kThinkCount = 28, kThinkQueue = 32;
inline constexpr u32 kThinkEntrySize = 24, kThinkQueueMax = 47;
inline constexpr u32 kUnitCollisionTask = 480;
inline constexpr u32 kCtlFlagFrozen = 0x08000000u;  // collision controller flag bit 27

}  // namespace fldlo

// --- the collision controller (k_fldFrame band) ----------------------------------------------------------------------
void sub_1AD870(EEContext& ctx);  // [register ABI] [K_FldFrame_CtlSetFlag] work +4 |= flags
void sub_1AD890(EEContext& ctx);  // [register ABI] [K_FldFrame_CtlClearFlag] work +4 &= ~flags
void K_FldFrame_CtlGetSphereCollisRadius(EEContext& ctx);  // [register ABI] [K_FldFrame_CtlGetSphereCollisRadius] $f0 = work +32 (bits)
void K_FldFrame_CtlSetSphereCollisRadius(EEContext& ctx);  // [register ABI] [K_FldFrame_CtlSetSphereCollisRadius] $f12 -> +32, bit 28 for 0.0
void K_FldFrame_CtlGetXGrid(EEContext& ctx);  // [register ABI] [K_FldFrame_CtlGetXGrid] work +44
void K_FldFrame_CtlGetZGrid(EEContext& ctx);  // [register ABI] [K_FldFrame_CtlGetZGrid] work +48
void sub_1AD930(EEContext& ctx);  // [register ABI] [K_FldFrame_CtlGetMoveDistance] work +40
void sub_1AE470(EEContext& ctx);  // [register ABI] [K_FldFrame_CtlSetState] work +0

// --- scene ids and scene resources (k_scene band) ----------------------------------------------------------------------
u32 sub_1A02C0(EEContext& ctx);             // [K_Scene_IsFixedTartarusFloor] major 51..58 or 71..78
u32 sub_1A01C0(EEContext& ctx);             // [K_Scene_IsTartarus] random floor, fixed floor or major 30..38
u32 sub_1A0310(EEContext& ctx);             // [K_Scene_IsSpecialScene] 8/3, 32/2, 26/51..53, 37/1, 35/1, majors 4 / 5
void sub_1A0410(EEContext& ctx, u32 value); // [K_Scene_SetWord24] scene record +24 (battle scene set-up; inf)
void sub_1A0420(EEContext& ctx, u32 value); // [K_Scene_SetWord28] scene record +28 (event viewer; inf)
void sub_1A0150(EEContext& ctx, u32 id, u64 on);   // [K_Scene_SetResFlag] resource `id` flag bit 1 on (on == 1) / off
void sub_1A0040(EEContext& ctx, u64 on, u64 also_type10);  // [K_Scene_SetBlockFlags] every block (+ type 10) resource
void sub_1A0DC0(EEContext& ctx, u32 id, u64 on);   // [K_Scene_SetResFlagById] the same through the manager's id lookup
u32 sub_19FD40(EEContext& ctx);  // [K_Scene_GetBlockListHead256] block list head + 256 (inf)
u32 sub_19FD70(EEContext& ctx);  // block list head + 272
u32 sub_19FDA0(EEContext& ctx);  // block list head + 288
u32 sub_1A09D0(EEContext& ctx);  // type-4 list head + 256, 0 without
u32 sub_1A0A10(EEContext& ctx);  // type-4 list head + 272, 0 without
u32 sub_1A0A50(EEContext& ctx);  // type-4 list head + 288, 0 without

// --- the camera's debug cylinder (written by K_FldCamera_UpdateFieldCameraControlerTask 0x1D5220) -----------------
void sub_1A48E0(EEContext& ctx);  // [register ABI] [K_Draw_CylinderSetWord] work +0
void sub_1A48F0(EEContext& ctx);  // [register ABI] [K_Draw_CylinderSetPos] work +4..+12 = pos[0..2]
void sub_1A4920(EEContext& ctx);  // [register ABI] [K_Draw_CylinderSetRadius] work +16 = $f12
void sub_1A4930(EEContext& ctx);  // [register ABI] [K_Draw_CylinderSetHeight] work +20 = $f12

// --- field root, dungeon, sequences ----------------------------------------------------------------------------------
void sub_1BAB40(EEContext& ctx);  // [register ABI] [K_Field_GetSubId1] root work +24 (u16)
void sub_1BAB50(EEContext& ctx);  // [register ABI] [K_Field_GetSubId2] root work +26 (u16)
void K_FldDungeon_RequestShutdown(EEContext& ctx);           // [K_FldDungeon_RequestShutdown] dungeon work +12 = 1
u32 K_FldDungeon_GetScrMemory(EEContext& ctx);            // [K_FldDungeon_GetScrMemory] dungeon work +52, 0 without
u32 sub_1B0910(EEContext& ctx);            // [K_Fldrc_GetFieldPack] gp-0x4B94 (inf)
u32 K_Seq_CheckField(EEContext& ctx);            // [K_Seq_CheckField] sequence 2 check: root gone -> sField.root = 0, 1
u32 sub_1B79F0(EEContext& ctx);            // [K_Seq_CheckFieldEvent] sequence 3 check (the same body)
u32 sub_1B7AC0(EEContext& ctx);            // [K_Seq_CheckDungeon] sequence 5 check: dungeon task gone -> slot = 0, 1

// --- EPL effect handles ------------------------------------------------------------------------------------------------
void sub_1A9180(EEContext& ctx);  // [register ABI] [K_Epl_IsStarted] 1 for NULL or work +0 >= 1 (inf)
void sub_1A9390(EEContext& ctx);  // [register ABI] [K_Epl_SetHalf] slot i (u16 +100 if handle) / default +28
void sub_1A93D0(EEContext& ctx);  // [register ABI] [K_Epl_GetWord] slot i (+68) / default +24

// --- the Tartarus floor grid (k_dungeon.c) -------------------------------------------------------------------------------
void sub_1BB090(EEContext& ctx);  // [register ABI] [K_FldDungeon_PlaceBlock] marks a block's cells

// --- the enemy-think action queue (Y_* enemy think) ----------------------------------------------------------------------
void sub_1B0220(EEContext& ctx);  // [register ABI] [K_Think_GetQueueCount] work +28
void sub_1B0240(EEContext& ctx);  // [register ABI] [K_Think_SetWord24] work +24
void sub_1B0260(EEContext& ctx);  // [register ABI] [K_Think_SetMode] work +8; mode 1 freezes the unit's controller
void sub_1AFF70(EEContext& ctx);  // [register ABI] [K_Think_PushWait] type-1 entry (not after another type 1)
void sub_1B0020(EEContext& ctx);  // [register ABI] [K_Think_PushMove] type-2 entry with a target

}  // namespace p3fes::game
