// The field layer's larger functions (slice `field_big`; docs/ANALYSIS/26_field.md, docs/ANALYSIS/queue_field.txt open
// class-a rows that the field_lo / field_hi slices left for size), plus the small leaves they left without a route
// caller: the per-frame Tartarus block visibility pass, the floor generator's block rotation and fitting, the field's
// BGM / ambience / time-of-day scene variant choice, the transparent-wall fade callbacks, and leaf accessors.
//
// Names: the functions.json names (`sub_<addr>` for all but the four exported K_* names); a proposed name is given in
// brackets (ours, from the instructions, the callers and the data they touch; not in any delta, not imported). "inf" marks a role inferred from
// the callers only.
//
// Calling convention of the hand versions: arguments are the WHOLE 64-bit registers $a0.. as the caller left them (the
// shims pass them through unchanged), and the result is also left in $v0 / $f0 exactly as the original leaves it.
// Every hand version is register-faithful: at each check point (entry, loop back-edges, every call) and at the return
// every GPR, HI/LO, FPR and FCR31 holds the original's value, and the prologue spills land on the original stack bytes
// (tests/game/test_field_big.cpp compares the whole register file at every check point).
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace fldbig {

inline constexpr u32 kTaskWork = 60;  // KwlnTask +0x3C: the work pointer

// sField (0x869F60, K_Field_Get): the 16 x 16 Tartarus grid at +72, 16-byte cells (26_field.md 6.2); the u16 at cell
// +4 names the cell's block resource (type 12, id 0x3000 + 16 z + x; 0 = none).
inline constexpr u32 kGridBase = 72, kGridRow = 256, kGridCell = 16, kGridCellRes = 4;
// The grid cell (x, z) the player's controller was last seen in (sub_1BD950 writes, K_FldFrame_CtlGetXGrid / ZGrid).
inline constexpr s32 kGpPlayerCellX = -19104, kGpPlayerCellZ = -19100;  // gp-0x4AA0 / gp-0x4A9C
inline constexpr s32 kGpSceneIds = -22448;                              // gp-0x57B0 -> {s32 major, s32 minor, ..}
inline constexpr s32 kGpFieldBgmSuppressed = -19180;                    // gp-0x4AEC: 1 = keep the current BGM (inf)

// Scene resource: +40 flags (bit 1 = the draw flag the field draw tasks test; sub_1A0150 sets it), +248 next in the type list, +256 the
// resource it follows (types 10 / 11: the block it belongs to), +480 the collision controller of a character (type 1).
inline constexpr u32 kResFlags = 40, kResNext = 248, kResParent = 256, kResController = 480;
inline constexpr u32 kResDrawFlag = 2;

// Field units (448-byte records, 26_field.md 6.4): gFldUnitsEc [24], then gFldUnitsPc [4].
inline constexpr u32 kFldUnitsEc = 0x86EDA0u, kFldUnitsPc = 0x8717A0u, kFldUnitSize = 448, kFldUnitsEcCount = 24;
inline constexpr u32 kUnitEncounter = 72, kUnitSceneRes = 84;

// The floor generator's block descriptor (sub_1BCAC0 / sub_1BAB60): +1 width, +2 depth (in cells), +4 [3][3] cell
// kinds, +14 [3][3] cells of 8 bytes {u8 door mask: low nibble = the cell's open sides, high nibble = the walls;
// ..} copied from the kind table 0x67F600.
inline constexpr u32 kBlkWidth = 1, kBlkDepth = 2, kBlkKinds = 4, kBlkCells = 14, kBlkCellSize = 8, kBlkRowSize = 24;
inline constexpr u32 kBlockKindTable = 0x67F600u;

// The transparent-wall fade work (K_FldDungeon's wall control 0x1C0D40.., 16 bytes): +0 state (0 fading, 1 done),
// +4 the target (sub_1C0880: an object whose f32 +24 fades; sub_1C0960: a wall resource, model at +260), +8 frames left,
// +12 f32 the end value.
inline constexpr u32 kFadeState = 0, kFadeTarget = 4, kFadeFrames = 8, kFadeEnd = 12;

}  // namespace fldbig

// --- leaves without a route caller ---------------------------------------------------------------------------------------
void sub_19C2F0(EEContext& ctx, u64 task, u64 value);  // [K_Task_SetWork4] work +4 = value (sub_1D1860)
u32 sub_19C300(EEContext& ctx, u64 task);              // [K_Task_GetWork10] work +10 (u16)
void sub_19C310(EEContext& ctx, u64 task, u64 value);  // [K_Task_SetWork10] work +10 = (u16) value
u32 sub_19C490(EEContext& ctx, u64 task);              // [K_Task_GetWork76Float] $f0 = *(work +76) or 0.0
void sub_1A4770(EEContext& ctx, u64 task, u64 on);     // [K_Draw_PointSetEnabled] work +0 (camera debug point)
void sub_1A4780(EEContext& ctx, u64 task, u64 pos);    // [K_Draw_PointSetPos] work +4..+12 = pos[0..2]
void sub_1A47B0(EEContext& ctx, u64 task, u64 rgba);   // [K_Draw_PointSetColor] work +16..+19 = rgba[0..3]
u32 sub_1B01B0(EEContext& ctx, u64 task, u64 i);       // [K_Think_GetQueueEntry] work + 32 + 24 i
void sub_1B01D0(EEContext& ctx, u64 task, u64 i, u64 src);  // [K_Think_SetQueueEntry] 24 bytes of src -> entry i
void sub_1B0230(EEContext& ctx, u64 task, u64 value);  // [K_Think_SetQueueCount] work +28
void sub_1B0250(EEContext& ctx, u64 task, u64 value);  // [K_Think_SetWord1204] work +1204 (the Y_* think states)

// --- the transparent-wall fade callbacks (called through the wall control's jalr table) ---------------------------------
s32 sub_1C0880(EEContext& ctx, u64 task);  // [K_FldDungeon_UpdateFadeValue] one linear step of the target's f32 +24
s32 sub_1C0960(EEContext& ctx, u64 task);  // [K_FldDungeon_UpdateWallFade] one step of a wall model's alpha + materials

// --- the Tartarus floor generator (k_dungeon.c) ----------------------------------------------------------------------------
void sub_1BAB60(EEContext& ctx, u64 block, u64 turn);  // [K_FldDungeon_RotateBlock] block by 1 << k quarter turns
u32 sub_1BC630(EEContext& ctx, u64 block, u64 px, u64 pz);  // [K_FldDungeon_FitBlock] a free origin covering (x, z) whose doors meet

// --- the per-frame block culling (from the opaque field draw task) -------------------------------------------------------
void sub_1BD950(EEContext& ctx);  // [K_FldDungeon_CullBlocks] draw only the blocks in the camera's view wedge

// --- the collision controller (k_fldFrame band) ----------------------------------------------------------------------------
void sub_1AD940(EEContext& ctx, u64 out, u64 task);   // [K_FldFrame_CtlGetPos] out = the model position (0 without)
void sub_1ADD40(EEContext& ctx, u64 task);            // [K_FldFrame_CtlUpdateGrid] work +44 / +48 = the 800-unit cell
void sub_1ADFF0(EEContext& ctx, u64 task, u64 axis);  // [K_FldFrame_CtlTurn] turn the model in place by $f12
u32 K_FldFrame_HandleCollis(EEContext& ctx, u64 pos, u64 step, u64 id);  // the collision mesh (grid block), then the test

// --- the enemy pop scheduler's helpers (k_unit.c) ------------------------------------------------------------------------
void sub_1D38D0(EEContext& ctx, u64 task, u64 per_cell);  // [K_Unit_LimitReaperTime] limit = min(limit, per_cell * cells)
s32 sub_1D3830(EEContext& ctx, u64 task);                 // [K_Unit_GetReaperWarning] -1 / 1 (< 60 left) / 2 (time up)
s32 K_Unit_UpdateEnemyPopSchedulerTask(EEContext& ctx, u64 task);  // states 0 populate / 1 wait / 2 respawn + Reaper

// --- small event / camera / virtual-pad helpers ---------------------------------------------------------------------------
u32 sub_1C7130(EEContext& ctx, u64 unit);  // [K_FldEvent_IsUnitNearHero] sub_1C7160(unit, hero, $f12)
u32 sub_1D5140(EEContext& ctx, u64 task);  // [K_FldCamera_GetNearestPoint] the camera point nearest the player
s32 sub_1E13F0(EEContext& ctx, u64 task);  // [K_VPad_UpdateRotateTask] turn the hero step by step, then notify
u32 sub_1E1590(EEContext& ctx, u64 task, u64 src);  // [K_VPad_StartTurn] the shorter way between $f12 / $f13, > 45 deg

// --- field hits (scene resources of type 13) and shadow spawning -----------------------------------------------------------
u32 K_FldEvent_FindFldHitAt(EEContext& ctx, u64 point, u64 res);  // the hit quad under a point (+-100), 0xFFFF for none
u32 K_FldEvent_IsUnitNearFldHit(EEContext& ctx, u64 unit);        // the unit over a hit quad (random floors only)
u32 sub_1D0720(EEContext& ctx, u64 n);  // [K_Unit_SpawnShadows] up to n shadows (Thebel 51/1: encounter 466 + i)

// --- the field root's choices on entering a field (k_field.c) --------------------------------------------------------------
u32 sub_1B6EB0(EEContext& ctx, u64 major, u64 minor);  // [K_Field_GetSceneVariant] scene sub-id by time of day / season
void sub_1A9850(EEContext& ctx);  // [K_Field_PlayBgm] the field's BGM by Tartarus floor / scene / season / flags
void sub_1AA1B0(EEContext& ctx);  // [K_Field_PlayAmbience] ENV_*.ADX on sound channel 4 by scene / time / season

}  // namespace p3fes::game
