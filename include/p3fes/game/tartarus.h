// The Tartarus field band of the Y map code (slice `tartarus`; docs/ANALYSIS/27_unmapped_bands.md section 8 and the
// slice block of docs/ANALYSIS/queue_bands.txt): the Tartarus mini-map ("y_smap draw proc", 0x4281F0-0x4312AC), the
// stratum title and floor / enemy logic ("ene think proc", "y_ene_dead effect proc", "smap_symbol_dirp",
// 0x447AD0-0x4575D4) and the time-limit display ("y_TimeLimit draw", 0x45A020-0x45A3A4). The field layer's own
// Tartarus code (block culling, the floor generator, the enemy pop scheduler: game/src/field/field_big.cpp) is not here.
//
// Names: the functions.json names (all `sub_<addr>`); a proposed name is given in brackets (ours, from the instructions,
// the callers and the data they touch; symbols/deltas/bands.sym names the task updates). "inf" marks a role inferred
// from the callers only.
//
// Calling convention of the typed entry points: arguments are the WHOLE 64-bit registers $a0.. as the caller left them
// (stored as given), float arguments stay in $f12.. as the caller left them, and the result is left in $v0 / $f0
// exactly as the original leaves it (returned here as the whole $v0). Every hand version is register-faithful: at each
// check point (entry, loop back-edges, every call) and at the return every GPR, HI/LO, FPR, ACC and FCR31 holds the
// original's value, and the prologue spills and stack temporaries land on the original stack bytes
// (tests/game/test_tartarus.cpp compares the whole register file at every check point).
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace tart {

inline constexpr u32 kTaskWork = 60;  // KwlnTask +0x3C: the work pointer

// $gp-relative words (crt0's $gp = 0x7D2CF0).
inline constexpr s32 kGpSmapSprite = -17932;  // gp-0x460C: the sprite file of smap/i_mini_map01.spr (sub_4302B0)
inline constexpr s32 kGpSmapSymbols = -17936; // gp-0x4610: smap/symbol_smap.tmx
inline constexpr s32 kGpSmapLock = -17940;    // gp-0x4614: s8, 1 while the mini-map is locked (sub_42BA30)
inline constexpr s32 kGpStratum = -17924;     // gp-0x4604: the stratum record the 0x425xxx COMM handlers fill (comm_b.h)

// Field units (448-byte records, 26_field.md 6.4): gFldUnitsEc [24], then gFldUnitsPc [4]; +72 the encounter / party
// slot (0 = empty), +84 the unit's scene resource (its collision controller at +480).
inline constexpr u32 kFldUnitsEc = 0x86EDA0u, kFldUnitsPc = 0x8717A0u, kFldUnitSize = 448;
inline constexpr u32 kUnitUsed = 72, kUnitSceneRes = 84, kResController = 480;

// The mini-map work ("y_smap draw proc", Y_SMap_CreateSmapDrawTask / Y_SMap_UpdateSmapDrawTask): +2148 s8 shown, +2149 s8 centre frozen,
// +2152..+2160 f32[3] the frozen centre (the player's position when it was frozen).
inline constexpr u32 kSmapShown = 2148, kSmapFrozen = 2149, kSmapFrozenPos = 2152;

// The stair icon work ("y_staire_disp_proc", Y_SMap_CreateStaireDispTask / Y_SMap_UpdateStaireDispTask): +0 s16 x, +2 s16 y, +8..+20 f32[4] a rectangle
// the map draw reads back (sub_430270), +16 / +20 the sprite's size (written by the update over the rectangle's end),
// +24 s8 shown.
inline constexpr u32 kStairX = 0, kStairY = 2, kStairRect = 8, kStairShown = 24;

}  // namespace tart

// --- the mini-map's leaves (0x429E80..) ------------------------------------------------------------------------------
void sub_429E80(EEContext& ctx, u64 task, u64 shown);   // [Y_SMap_SetShown] smap work +2148 = shown
void sub_429E90(EEContext& ctx, u64 task, u64 frozen);  // [Y_SMap_FreezeCentre] +2149 = frozen, +2152.. = the player's position
u32 sub_429EF0(EEContext& ctx, u64 pc);   // [Y_SMap_PcCellOffsetX] ($f12 = map cell size) -> $f0 (int-truncated)
u32 sub_429FE0(EEContext& ctx, u64 pc);   // [Y_SMap_PcCellOffsetZ] the same on z
u32 sub_42A230(EEContext& ctx, u64 ec);   // [Y_SMap_EcCellOffsetX] an enemy unit's, not truncated
u32 sub_42A310(EEContext& ctx, u64 ec);   // [Y_SMap_EcCellOffsetZ]
u32 sub_42A0D0(EEContext& ctx, u64 pos);  // [Y_SMap_PosCellOffsetX] of a position (truncated)
u32 sub_42A180(EEContext& ctx, u64 pos);  // [Y_SMap_PosCellOffsetZ]
u32 sub_42A3F0(EEContext& ctx, u64 pos);  // [Y_SMap_PosCellOffsetXf] not truncated
u32 sub_42A4A0(EEContext& ctx, u64 pos);  // [Y_SMap_PosCellOffsetZf]
u32 sub_42BA30(EEContext& ctx);           // [Y_SMap_IsLocked] *(s8 *)(gp-0x4614) == 1
void sub_430220(EEContext& ctx, u64 task, u64 xy);  // [Y_Stair_Show] icon at ((s16) xy.x, (s16) xy.y) (two f32 in $a1)
void sub_430270(EEContext& ctx, u64 out, u64 task); // [Y_Stair_GetRect] out[0..3] = work +8..+20
void sub_4302A0(EEContext& ctx, u64 task);          // [Y_Stair_Hide] work +24 = 0
void sub_4311F0(EEContext& ctx, u64 out, u64 x, u64 z);  // [Y_CellToWorld] out = {800 x, 0, 800 z} (x, z unsigned)

// --- the mini-map's drawing helpers (from the "y_smap draw proc" update Y_SMap_UpdateSmapDrawTask) ---------------------------------------
void sub_42ADB0(EEContext& ctx, u64 task);  // [Y_SMap_PlaceLayers] the tmx layers' positions, turned by the map angle
void sub_42B050(EEContext& ctx, u64 task);  // [Y_SMap_DrawPartyMarks] gFldUnitsPc[1..3] as sprite 7, clipped to the map
void sub_42B540(EEContext& ctx, u64 task);  // [Y_SMap_DrawShadowMarks] gFldUnitsEc[0..23] as sprite 11
void sub_42FD80(EEContext& ctx, u64 out, u64 task);  // [Y_SMap_FindStairs] the stair cell (+2992..) and a door next to it
s32 Y_SMap_UpdateStaireDispTask(EEContext& ctx, u64 task);   // [Y_SMap_UpdateStaireDispTask] (bands.sym) draws the stair icon; 0
void sub_430630(EEContext& ctx, u64 task);  // [Y_SMap_CreateFrame] the frame's four corner sprites at work +76..+88
void sub_430780(EEContext& ctx, u64 offset, u64 x, u64 y, u64 frame);  // [Y_SMap_DrawPulse] sprite 13, pulsing
void sub_430A40(EEContext& ctx, u64 row);   // [Y_Field_SeedSparkles] the field root work's five sparkles of a row

// --- the mini-map's set-up and the seen-cells grid (0x95C110, u8 [16][16]) ------------------------------------------------
void sub_42A550(EEContext& ctx, u64 task, u64 pc, u64 x, u64 z);  // [Y_SMap_MarkSeen] cell + open neighbours; the two flags
void sub_42BA50(EEContext& ctx, u64 task);  // [Y_SMap_CreateLayers] one tmx task per layer (+92 + 8 i)
void sub_42BC10(EEContext& ctx, u64 task);  // [Y_SMap_SetUpSymbol] the symbol-direction task + the layers
void sub_42BD80(EEContext& ctx, u64 task);  // [Y_SMap_CreateRoomTmx] one tmx task per room cell of the grid
void sub_42BFD0(EEContext& ctx, u64 task);  // [Y_SMap_CreateSymbol] the symbol-direction task alone

// [Y_SMap_DrawPartyMark] party member pc's mark on cell (x, z) (+2232 / +2236 + 8 pc), status blink
void sub_42C0A0(EEContext& ctx, u64 task, u64 pc, u64 x, u64 z, u64 ox, u64 oz);
void sub_42CD80(EEContext& ctx, u64 task);  // [Y_SMap_DrawSparkles] the five sparkles of each flagged party member
// [Y_SMap_DrawShadowMarks2] the shadows on cell (x, z): blink when touching the player, else a small mark
void sub_42CFC0(EEContext& ctx, u64 task, u64 x, u64 z, u64 ox, u64 oz);
// [Y_SMap_DrawObjectMarks] the 8 field objects (0x86BE00) on cell (x, z) by kind
void sub_42DD90(EEContext& ctx, u64 task, u64 x, u64 z, u64 ox, u64 oz);
// [Y_SMap_DrawChestMarks] the 32 records at 0x86BE80 (+268 position) on cell (x, z), sprite 12
void sub_42EA60(EEContext& ctx, u64 task, u64 x, u64 z, u64 ox, u64 oz);
// [Y_SMap_DrawExitMark] the floor exit at 0x86E684 (while 0x86E580 == 1), sprite 5
void sub_42F440(EEContext& ctx, u64 task, u64 x, u64 z, u64 ox, u64 oz);
// [Y_SMap_UpdateSmapMaskDrawTask] (bands.sym) the four box-fill masks around the map; 0
s32 Y_SMap_UpdateSmapMaskDrawTask(EEContext& ctx, u64 task);
// [Y_TimeLimit_UpdateTimeLimitDrawTask] (bands.sym) the time-limit display's states; -1 when done
s32 Y_TimeLimit_UpdateTimeLimitDrawTask(EEContext& ctx, u64 task);
// [Y_Stratum_ListEntryPos] out = the position of floor-list entry i (an empty scan of the 256 entries kept)
void sub_447F90(EEContext& ctx, u64 out, u64 task, u64 i);
// [Y_Stratum_FindTitleEntry] index of entry i's {block, floor} in the 30-entry table 0x6B4650, else -1
u32 sub_449C90(EEContext& ctx, u64 task, u64 i);
void sub_449D10(EEContext& ctx, u64 task);  // [Y_Stratum_ClearParts] the 56 six-byte s16 triples at work +236 = 0
// [Y_Stratum_DrawPart] sprite index of the work's file +4 at ($f15 scale, $f21 alpha, $f23 / $f13 x / y)
void sub_44A240(EEContext& ctx, u64 task, u64 index);
// [Y_Stratum_DrawPart2] the same from the second sprite file (+232)
void sub_44A330(EEContext& ctx, u64 task, u64 index);
void sub_44A630(EEContext& ctx, u64 task);  // [Y_Stratum_HideParts] alpha 255 on every part handle of the work
// [Y_Stratum_DrawEntry] one floor-list entry: cursor arrows, the floor number, the label
void sub_448060(EEContext& ctx, u64 task, u64 i, u64 xy, u64 block, u64 floor, u64 active);
// [Y_Stratum_DrawEntry2] the same with the work's own current entry (+1179 / +1180), label alpha
void sub_448CF0(EEContext& ctx, u64 task, u64 i, u64 xy, u64 block, u64 floor, u64 active, u64 alpha);
// [Y_Stratum_StepCursor] advances the list cursor (+2366 / scroll +2369) to the next entry of the current floor
void sub_449D60(EEContext& ctx, u64 task);
// [Y_Stratum_DrawSlideA] part 0 slid in over `steps` frames (counter +238); 1 while moving
u32 sub_449FE0(EEContext& ctx, u64 task, u64 steps);
// [Y_Stratum_DrawSlideB] the same for part 1 with the counter +244
u32 sub_44A110(EEContext& ctx, u64 task, u64 steps);
// [Y_Stratum_DrawBlockFade] a block's banner faded in (record +124 + 6 b) by sprDrawSprite4; 1 while fading
u32 sub_44A420(EEContext& ctx, u64 task, u64 block, u64 steps);
// [Y_Fx_PlaceWobbleVertex] one Im2D vertex of a wobbling quad (64-byte vertices), camera-relative
void sub_44A790(EEContext& ctx, u64 rec);
// [Y_Ene_StartContact] the unit's think work: state 5, +5 = 2, +24 = kind
void sub_44E530(EEContext& ctx, u64 unit, u64 kind);
u32 sub_44F060(EEContext& ctx, u64 task, u64 pos);  // [Y_Ene_IsNearPos] 1 when the model is within $f12 of pos
u32 sub_44F120(EEContext& ctx, u64 pos);  // [Y_GridCellX] (int)((pos.x + 400) / 800), the grid column of a position
u32 sub_44F170(EEContext& ctx, u64 pos);  // [Y_GridCellZ] (int)((pos.z + 400) / 800), the grid row
u32 sub_44F1C0(EEContext& ctx, u64 a, u64 b);  // [Y_ArePosNear] 1 when a and b are within $f12
u32 sub_44F270(EEContext& ctx, u64 a, u64 b);  // [Y_PosDistance] $f0 = the distance of a and b
// [Y_Ene_SetAllPaused] every used shadow's think work +64 = paused; sub_1B0260 on its mover
void sub_4532D0(EEContext& ctx, u64 paused);
void sub_4533E0(EEContext& ctx, u64 flag);  // [Y_Ene_SetAllFlag65] every used shadow's think work +65 = flag
u32 sub_453460(EEContext& ctx);  // [Y_Ene_GetGpWord] the s16 at gp-0x45FC
void sub_453470(EEContext& ctx, u64 value);  // [Y_Ene_SetGpWord] the s16 at gp-0x45FC = value
u32 sub_453480(EEContext& ctx);  // [Y_Ene_GetGpByte] the s8 at gp-0x4600
void sub_453490(EEContext& ctx, u64 task);  // [Y_Ene_SetWorkState6] work +0 = 6
// [Y_Ene_PathStepToPlayer] the next cell towards the player (breadth-first over open sides) into the think work
u32 sub_4514A0(EEContext& ctx, u64 ec);
// [Y_Ene_FarRoomCell] the farthest room cell along the diagonals from pos (the Reaper's spawn point), or pos
void sub_452010(EEContext& ctx, u64 pos);
// [Y_Ene_StairDoors] the stair cell's doors: out = the last neighbour door, work +52.. = the matching own door
void sub_452F70(EEContext& ctx, u64 out, u64 task);
// [Y_Ene_UpdateContact] think state 5: the contact steps (+5) up to the battle hand-off
void sub_44DFC0(EEContext& ctx, u64 task);
// [Y_Ene_PickWanderTarget] a random reachable point next to the shadow (8 directions); the direction or -1
u32 sub_44E560(EEContext& ctx, u64 task);
// [Y_Ene_CheckSightChase] 1 when shadow ec starts chasing a party member (it sees it, flag 3173 off)
u32 sub_44F300(EEContext& ctx, u64 ec);
// [Y_Ene_LookForParty] 1 when the shadow spots a living party member (state 3), by behaviour kind
u32 sub_44FAB0(EEContext& ctx, u64 task);
u32 sub_44FFB0(EEContext& ctx, u64 task);  // [Y_Ene_LookForHero] 1 when the shadow spots the hero (state 3)
// [Y_Ene_PathExpand] one step of the path search (the four sides of cell +120 / +121); 2 found, 1 done, 0 none
u32 sub_4534B0(EEContext& ctx, u64 ec);
// [Y_Ene_PathPlan] plans shadow ec's cell path (x, z) -> (tx, tz); 1 when a path was found
u32 sub_453ED0(EEContext& ctx, u64 ec, u64 x, u64 z, u64 pos, u64 tx, u64 tz);
// [Y_Ene_UpdateWander] think state 4 (the "wander" behaviour 1): random strolls until the hero is spotted
void sub_44B7D0(EEContext& ctx, u64 task);
// [Y_Ene_UpdateChase] think state 3 (wander behaviour): the chase sub-states (+3) of a shadow that saw the hero
void sub_44D600(EEContext& ctx, u64 task);
// [Y_Ene_UpdateChaseA] chase sub-states 2..6 of shadow ec (the record gp-0x4A60 + 64 kind)
void sub_4501B0(EEContext& ctx, u64 ec);
// [Y_Ene_UpdateChaseB] the same as sub-states 7..10 (a ground ray over 50 goes on to 9 instead of wandering)
void sub_450B30(EEContext& ctx, u64 ec);
// [Y_Ene_UpdateRoam] think state 4 (roam): wander points (sub_44E560), the walk, the way back by path
void sub_44AF60(EEContext& ctx, u64 task);
// [Y_Ene_PlanToTarget] plan to the stored target cell (+139 / +140), else one step towards the player
void sub_451D70(EEContext& ctx, u64 task);
// [Y_Ene_SwitchTarget] switch the chase to another party member within reach; 1 when switched
u32 sub_4523C0(EEContext& ctx, u64 task, u64 ec);
// [Y_Ene_FollowTarget] re-plan when the target moved more than 1600 from +28..; 1 when re-planned
u32 sub_452A70(EEContext& ctx, u64 ec, u64 pc);
// [Y_Ene_UpdateFixedFloor] the think update on a non-random floor: states 5 / 4 / 3
void sub_454110(EEContext& ctx, u64 task);
// [Y_Ene_UpdateChaseRandom] think state 3 on random floors: the chase sub-states 0..25 by behaviour kind
void sub_44BEB0(EEContext& ctx, u64 task);
s32 Y_Stratum_UpdateEneThinkTask(EEContext& ctx, u64 task);  // [Y_Stratum_UpdateEneThinkTask] (bands.sym) the "ene think proc" update; 0
// [Y_Ene_PathBuildSteps] walks the path records back from the target into the step list +3224 (at most 100)
void sub_453D90(EEContext& ctx, u64 ec);
// [Y_Stratum_UpdateEneDeadEffectTask] (bands.sym) the dead effect: once, an EPL 100 above the point; -1 after
s32 Y_Stratum_UpdateEneDeadEffectTask(EEContext& ctx, u64 task);
// [Y_Ene_SetThinkState] shadow ec's think work: +2 = state, +3 / +4 / +5 = 0
void sub_4543C0(EEContext& ctx, u64 ec, u64 state);
// [Y_Ene_IsGroundOk] 1 when kind 4, or a ground ray at pos (from +400 to -400) hits within 50
u32 sub_454400(EEContext& ctx, u64 pos, u64 ec);
// [Y_Ene_IsInRange] 1 when pos is within the behaviour range (record +0) of the shadow's model
u32 sub_454520(EEContext& ctx, u64 pos, u64 ec);
// [Y_Ene_StepTowardTarget] one range-long step from the model toward the target point; 1 when queued
u32 sub_454620(EEContext& ctx, u64 ec);
// [Y_Ene_StepToward] one range-long step from the model toward pos; 1 when the ground is good (walk queued)
u32 sub_454A70(EEContext& ctx, u64 ec, u64 pos);
// [Y_Ene_IsInsideRoom] 1 when pos lies in a room cell away from walls or through an open side
u32 sub_454D00(EEContext& ctx, u64 pos);
// [Y_Unit_StoreStatus] copies the think states into the units' status bytes (+408..+412) for the map / events
void sub_455B50(EEContext& ctx);
void sub_455CF0(EEContext& ctx);  // [Y_Unit_ClearStatus] clears those status bytes
// [Y_SymbolDirp_SetCentre] "smap_symbol_dirp" work +288 / +292 = ($f12, $f13)
void sub_4561D0(EEContext& ctx, u64 task);
// [Y_SymbolDirp_PlaceCorners] the marker's four corners turned by the axis 0x6B4A78 into work +16 + 64 i
void sub_4561F0(EEContext& ctx, u64 task);
void sub_4563B0(EEContext& ctx, u64 task);  // [Y_SymbolDirp_SetAngle] work +312 = $f12
void sub_4563C0(EEContext& ctx, u64 task, u64 floor);  // [Y_SymbolDirp_SetFloor] work +300 = floor
void sub_4563D0(EEContext& ctx, u64 task, u64 xy);  // [Y_SymbolDirp_SetPos] work +304 / +308 = the two f32 of $a1
void sub_456400(EEContext& ctx, u64 task, u64 value);  // [Y_SymbolDirp_SetFlag] work +328 = value
// [Y_Pc_SetMode0] party member pc's think: mode +4704 = 0, +4631 = 1, +4662 = 0
void sub_456410(EEContext& ctx, u64 pc);
void sub_456450(EEContext& ctx, u64 pc);  // [Y_Pc_SetMode1] mode 1
void sub_456490(EEContext& ctx, u64 pc);  // [Y_Pc_SetMode2] mode 2
void sub_4564E0(EEContext& ctx, u64 pc);  // [Y_Pc_SetMode3] mode 3
void sub_456530(EEContext& ctx, u64 pc);  // [Y_Pc_SetMode4] mode 4
void sub_456580(EEContext& ctx, u64 pc);  // [Y_Pc_SetMode5] mode 5
void sub_4565D0(EEContext& ctx, u64 pc);  // [Y_Pc_SetMode6] mode 6
void sub_456620(EEContext& ctx, u64 pc);  // [Y_Pc_SetMode7] mode 7
// [Y_Pc_StartSkillUse] +4664 = 1, +4663 = 0, +4665 = kind, the s16 +4646 = target
void sub_457340(EEContext& ctx, u64 pc, u64 kind, u64 target);
u32 sub_457390(EEContext& ctx, u64 pc);  // [Y_Pc_GetSkillKind] the s8 +4665
u32 sub_4573D0(EEContext& ctx, u64 pc);  // [Y_Pc_GetSkillTarget] the s8 at +4646
u32 sub_457410(EEContext& ctx);  // [Y_Npc_FindFreeSlot] the first of the 4 NPC units at 0x86E6A0 with +72 == 0, else 0
// [Y_Npc_LoadModel] the NPC slot's model: 1 when ready (or empty), 0 while streaming
u32 sub_457470(EEContext& ctx, u64 slot);
// [Y_Ene_Pursue] shadow ec lunges 400 units past / toward party member pc (sub-state 24 -> 25), SFX
void sub_454F50(EEContext& ctx, u64 ec, u64 pc);
// [Y_Pc_UseSupportSkill] party member pc casts its support skill on member target (once)
void sub_456EA0(EEContext& ctx, u64 unused, u64 pc, u64 target);
// [Y_Pc_UseSelfSkill] every 50 frames party member pc may cast a skill on itself (kind 2)
void sub_456670(EEContext& ctx, u64 unused, u64 pc);
// [Y_Pc_UseSkillOn] every 50 frames party member pc may cast a skill on target (kind 3)
void sub_456A90(EEContext& ctx, u64 unused, u64 pc, u64 target);
// @@DECLS@@
}  // namespace p3fes::game
