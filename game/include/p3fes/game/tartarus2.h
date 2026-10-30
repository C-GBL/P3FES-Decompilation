// Slice tartarus2: Tartarus, second pass -- the rest of the Y band 0x421770-0x45A3A4
// (docs/ANALYSIS/27_unmapped_bands.md section 8): the mini-map task, the party members' think ("npc think proc"),
// the treasure-free task, the stratum-parts task (Y_StParts_UpdateStratumPartsTask), the enemy band's task creators,
// the Kyoto NPCs and the time-limit creator. Every function is register-ABI (`void name(EEContext&)`: arguments in
// $a0.. / $f12.., result in $v0 / $f0) and register-faithful (p3fes_handgen bodies). namespace tart2 names the
// record offsets the bodies use (the values are the instructions' offsets; names ours, from the instructions --
// ADR-0009). Left recompiled in the band: Y_Misc_GetT0Count 0x4241D0 (reads the EE timer register T0_COUNT in its
// own body) and sub_434F70 [Y_Npc_ResetGlobals] (test_field3_kosaka.cpp stands it in with a recorder and counts its
// calls; a replaced callee cannot be stood in).
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace tart2 {

// --- shared: tasks, field units, the Tartarus grid -----------------------------------------------------------------
// Field units are 448-byte records: gFldUnitsEc 0x86EDA0 [24 shadows], the NPC units 0x86E6A0 [4], gFldUnitsPc
// 0x8717A0 [4, 0 = the hero]. A random floor's grid is 16 x 16 cells of 16 bytes at K_Field_Get() + 72 + 256 z + 16
// x (docs/ANALYSIS/26_field.md section 6.2); the bodies add (z << 8) + 16 x to K_Field_Get()'s result and read the
// cell at these offsets.
inline constexpr s32 kTaskWork = 60;  // ptr: KwlnTask +0x3C, the task's work block
inline constexpr s32 kUnitUsed = 72;  // ptr: field unit +72, the DatUnit / slot (0 = empty)
inline constexpr s32 kUnitSceneRes = 84;  // ptr: field unit +84, the unit's scene resource
// ptr: field unit +364, its think task (party: "npc think proc"; shadows: "ene think proc")
inline constexpr s32 kUnitThinkTask = 364;
// ptr: scene resource +480, its collision controller (K_FldFrame_CtlGetXGrid / ZGrid)
inline constexpr s32 kResController = 480;
inline constexpr s32 kGridCellKind = 74;  // u8: K_Field_Get() + 72 + 256 z + 16 x + 2, the cell's kind
inline constexpr s32 kGridCellWidth = 79;  // u8: cell +7 (FldGridCell "block width")
inline constexpr s32 kGridCellSides = 83;  // u8: cell +11, the open sides (bits 1 / 2 / 4 / 8)

// --- party think work ("npc think proc", 4708 bytes) ---------------------------------------------------------------
// One per party member 1..3 on Tartarus floors (and the fields that use the party AI): calloc-ed by
// Y_Npc_CreateNpcThinkTask, the work of the member's "npc think proc" task (gFldUnitsPc[pc] + 364 -> +60; the table
// 0x87190C). The party tactic is the s8 at 0x7CE6BC (gp-0x4634): 0 follow, 1 explore alone, 2 a third order handled
// like 0 (sub_434D30 / sub_434E60 set 1 / 0). The bytes 0x7CE6E8..0x7CE6EA (gp-0x4608): byte pc - 1 (= 0x7CE6E7 +
// pc) is member pc's place 1..3 in the hero's column (0 = not in it). The words 0x7CE6CC + 4 (pc - 1) are per-member
// flags (set when the member opened a chest, cleared by the mode-0 script).
// u8: cleared at creation; the path search (sub_433DE0) writes 32 when the walk cell is (0, 0)
inline constexpr s32 kNpcByte0 = 0;
// s8: the think mode: 0 place on the hero's cell, 1 follow the hero (sub_435C00), 2 explore alone (sub_438010), 5 a
// field skirmish with a shadow (sub_439520), 6 down (dead / out); set by sub_43C7A0
inline constexpr s32 kNpcMode = 1;
inline constexpr s32 kNpcPc = 4;  // s32: the member's party slot (1..3) in gFldUnitsPc
// ptr: the hero's scene resource (sub_3B5D10 [MT_Scene_GetRes](1024)); +296 its model
inline constexpr s32 kNpcHeroRes = 8;
// ptr: the member's own scene resource (sub_3B5D10 [MT_Scene_GetRes](0x400 | pc)); +296 its model
inline constexpr s32 kNpcOwnRes = 12;
// ptr: the member's field unit (gFldUnitsPc + 448 pc): +80 its model, +84 its scene resource, +368 its mover
inline constexpr s32 kNpcUnit = 36;
// ptr: the treasure record the member walks to (sub_1C7270; +268 its position, +284 its item record)
inline constexpr s32 kNpcChest = 40;
inline constexpr s32 kNpcTreasureTask = 44;  // ptr: the "treasure free proc" task opened for that chest
inline constexpr s32 kNpcCellPosX = 208;  // f32: the current cell's world position (800 x, -, 800 z)
inline constexpr s32 kNpcCellPosY = 212;  // f32
inline constexpr s32 kNpcCellPosZ = 216;  // f32
inline constexpr s32 kNpcCellX = 220;  // s8: the current cell (sub_44F120 of +208)
inline constexpr s32 kNpcCellZ = 221;  // s8
inline constexpr s32 kNpcWalkPosX = 224;  // f32: the point being walked to
inline constexpr s32 kNpcWalkPosY = 228;  // f32
inline constexpr s32 kNpcWalkPosZ = 232;  // f32
inline constexpr s32 kNpcStepPosX = 236;  // f32: the next step's point (the door of the next cell, sub_1BF220)
inline constexpr s32 kNpcStepPosY = 240;  // f32
inline constexpr s32 kNpcStepPosZ = 244;  // f32
inline constexpr s32 kNpcWalkX = 248;  // u8: the cell being entered / searched from
inline constexpr s32 kNpcWalkZ = 249;  // u8
inline constexpr s32 kNpcTimer = 252;  // s32: cleared on every arrival
inline constexpr s32 kNpcStepDir = 256;  // s8: the direction chosen for the next step (1 -z, 2 -x, 3 +z, 4 +x; 0 none)
// s8: the wall-following rule 0..3 (per member at first: pc 1 -> 0, 2 -> 1, 3 -> 2; flipped when a cell repeats)
inline constexpr s32 kNpcHand = 257;
inline constexpr s32 kNpcFacing = 258;  // s8: the facing direction 1..4 (as kNpcStepDir)
inline constexpr s32 kNpcGoalX = 259;  // u8: the path search's goal cell
inline constexpr s32 kNpcGoalZ = 260;  // u8
inline constexpr s32 kNpcStartX = 261;  // u8: the path search's start cell
inline constexpr s32 kNpcStartZ = 262;  // u8
inline constexpr s32 kNpcByte263 = 263;  // u8: cleared at creation
inline constexpr s32 kNpcVisits = 265;  // u8[16][16]: visits per cell (+265 + 16 z + x) while exploring
// s32: the path search's queue length / the step count; the hand-flip counter of sub_4332F0
inline constexpr s32 kNpcCount = 524;
// struct[256] of 8 bytes {s16 x, z, from x, from z}: the breadth-first search's cells (+528 + 8 (16 z + x))
inline constexpr s32 kNpcPathCells = 528;
inline constexpr s32 kNpcQueue = 2576;  // s32[256]: the search queue (cell indices 16 z + x)
inline constexpr s32 kNpcSteps = 3600;  // struct[100] of 4 bytes {s16 x, z}: the path, goal first (sub_4343D0)
inline constexpr s32 kNpcExploring = 4628;  // u8: 1 while the party tactic is "explore" (mode 2), 0 for "follow"
// u8: 1 = the think is held (another member's event runs; sub_4350E0 / sub_435060)
inline constexpr s32 kNpcHeld = 4629;
// u8: copy of the byte 0x7CDB10 (sub_435370): when set a shadow contact only counts when it already fights
inline constexpr s32 kNpcAvoidFights = 4630;
inline constexpr s32 kNpcModeChange = 4631;  // u8: 1 = run the member's mode-change script (sub_43A2F0; tartarus.h)
inline constexpr s32 kNpcFightState = 4632;  // s8: the skirmish states of mode 5 (sub_439520)
inline constexpr s32 kNpcFightEnemy = 4633;  // s8: the shadow index (gFldUnitsEc) of the skirmish
inline constexpr s32 kNpcFightLevel = 4634;  // u8: sub_16C470 of the member's persona at the start of the skirmish
inline constexpr s32 kNpcExploreState = 4640;  // s8: the sub-states of mode 2 (sub_438010)
inline constexpr s32 kNpcByte4641 = 4641;  // u8: cleared with the mode
inline constexpr s32 kNpcBusy = 4642;  // u8: 1 while walking to a chest / fighting (no new chest)
inline constexpr s32 kNpcFollowState = 4643;  // s8: the sub-states of mode 1 (sub_435C00)
inline constexpr s32 kNpcByte4644 = 4644;  // u8: cleared with the mode
inline constexpr s32 kNpcSkillTarget = 4646;  // s16: the target member of a support skill (tartarus.h)
inline constexpr s32 kNpcHidePosX = 4648;  // f32: the cover point (a type-18 scene resource) of follow states 13 / 14
inline constexpr s32 kNpcHidePosY = 4652;  // f32
inline constexpr s32 kNpcHidePosZ = 4656;  // f32
inline constexpr s32 kNpcHideIndex = 4660;  // u8: the index of that resource in its list
// u8: 1 when the follow path was planned through the nearest kind-8 cell (sub_437E80)
inline constexpr s32 kNpcViaStairs = 4661;
inline constexpr s32 kNpcModeScriptState = 4662;  // s8: mode-change script state 0..2 (sub_43A2F0)
inline constexpr s32 kNpcSkillState = 4663;  // s8: skill-use state 0..2 (sub_43A960)
inline constexpr s32 kNpcSkillUse = 4664;  // u8: 1 while a skill use runs (tartarus.h)
inline constexpr s32 kNpcSkillKind = 4665;  // s8: the skill kind (tartarus.h)
inline constexpr s32 kNpcByte4667 = 4667;  // u8: cleared at creation
inline constexpr s32 kNpcSupport = 4692;  // u8: 1 while walking to a member to use a support skill (sub_43BF50)
inline constexpr s32 kNpcSupportState = 4693;  // s8: its states 0..2
// ptr: the "battle kosaka" task of the skirmish (K_Battle_CreateBattleTask / K_Battle_FindTaskOfUnit)
inline constexpr s32 kNpcFightTask = 4696;
inline constexpr s32 kNpcScriptTask = 4700;  // ptr: the mode-change script task
// s8: the mode the player ordered (tartarus.h: "mode"); 0..2 run the default script and resume
inline constexpr s32 kNpcModeOrder = 4704;

// --- treasure-free work ("treasure free proc", 12 bytes) -----------------------------------------------------------
// The work of the "treasure free proc" task (Y_Npc_CreateTreasureFreeTask): opens a chest a party member reached.
inline constexpr s32 kNpcTfState = 0;  // s8: 0 start, 1 wait for the chest model's animation, 2 done (-1), 3 idle
// ptr: the chest's scene resource (sub_3B5D10 [MT_Scene_GetRes] of the record's u16 +8)
inline constexpr s32 kNpcTfRes = 4;
inline constexpr s32 kNpcTfChest = 8;  // ptr: the treasure record (from the creator's $a0)

// --- stratum-parts work ("y_StratumParts_proc", 2396 bytes) --------------------------------------------------------
// The work of the stratum-parts task (Y_Stratum_CreateStratumPartsTask): the Tartarus "stratum" screen -- the floor
// list of the terminals the party reached, block by block, drawn over a wobbling background, with a cursor; picking
// an entry runs its procedure of field/script/village.bf (the entrance's script). K_FldDungeon_UpdateTask shows it
// on the block-entry floors (the stratum title); the area map's COMM handlers sub_425020 / sub_4252D0 open it too.
// The stratum record (gp-0x4604 = 0x7CE6EC, calloc(1, 200) by sub_449ED0, freed by sub_449FA0): +4 + 4 i {s8 block,
// -, s16 floor} x 30 list entries, +160 the entry count, +162 s16 the current floor, +164 s8 the current block, +165
// a "done" flag the map form waits for, +166 + b the six blocks' states (2 at first, 1 = new, 0 = shown), +172 a
// layout flag (64 pixels), +173 the number of blocks open.
inline constexpr s32 kSpState = 0;  // s8: the update's state 0..48 (jump table 0x7BC480)
// u32: the sprite file of stratum_dat entry 0 (entry 2 in the short form), sprCreateHandleFromData
inline constexpr s32 kSpSprites = 4;
// ptr[56]: the part sprites (+8 + 4 i) built from the 6-byte rows 0x6B46D0 {s8 sprite, s16 x, s16 y}
inline constexpr s32 kSpParts = 8;
inline constexpr s32 kSpSprites2 = 232;  // u32: the sprite file of stratum_dat entry 1
inline constexpr s32 kSpSlideA = 238;  // s16: the slide counter of part 0 (sub_449FE0)
inline constexpr s32 kSpSlideB = 244;  // s16: the slide counter of part 1 (sub_44A110)
inline constexpr s32 kSpScriptTask = 572;  // ptr: the village.bf script task
inline constexpr s32 kSpScriptFile = 576;  // u32: the H_Cdvd node of field/script/village.bf
inline constexpr s32 kSpScriptSize = 580;  // s32: its size (node +280)
inline constexpr s32 kSpScriptCopy = 584;  // ptr: the script copied into a calloc block (freed by the destroy callback)
inline constexpr s32 kSpDataFile = 588;  // u32: the H_Cdvd node of stratum/stratum_dat (an archive: entries 0..2)
// u8: the creator's $a1: 0 = the short form (no block list: entry 2 only), else the block list
inline constexpr s32 kSpMode = 592;
// u8: the creator's $a2: 1 = opened by the area map's COMM handlers (no village.bf, the stratum record kept)
inline constexpr s32 kSpFromMap = 593;
inline constexpr s32 kSpEndWait = 594;  // u8: frames waited in state 48 (20)
inline constexpr s32 kSpCount595 = 595;  // u8: a count of the blocks shown
inline constexpr s32 kSpCount596 = 596;  // u8: a count of the blocks shown
inline constexpr s32 kSpTiles = 628;  // ptr[6]: the textures of stratum/tile1..6.tmx (sub_10C3A0)
inline constexpr s32 kSpTileTasks = 652;  // ptr[6]: their tmx display tasks (sub_427A10)
inline constexpr s32 kSpTilePos = 716;  // f32[6][2]: their positions
// u32[13]: the texture requests (sub_10C1A0) of tile1..6, tile1u..5u, bg1, f_tar1
inline constexpr s32 kSpTexRequests = 896;
inline constexpr s32 kSpTilesU = 968;  // ptr[5]: the textures of stratum/tile1u..5u.tmx
inline constexpr s32 kSpTileUTasks = 988;  // ptr[5]: their display tasks (sub_427830)
// ptr: the texture of stratum/bg1.tmx (also the raster of the wobble quad, sub_44A990)
inline constexpr s32 kSpBackground = 1060;
inline constexpr s32 kSpTitleTex = 1064;  // ptr: the texture of stratum/f_tar1.tmx
inline constexpr s32 kSpBgTask = 1068;  // ptr: the display task of bg1
inline constexpr s32 kSpTitleTask = 1072;  // ptr: the display task of f_tar1
// ptr: the Im2D indexed triangle list (sub_269690(1, 24, 16)) of the background wobble
inline constexpr s32 kSpTriList = 1148;
inline constexpr s32 kSpWobbleFrame = 1152;  // s32: the wobble frame 0..179
inline constexpr s32 kSpCursorA = 2152;  // ptr: a cursor sprite (0x6B47AE)
inline constexpr s32 kSpCursorB = 2156;  // ptr: a cursor sprite (0x6B481A)
inline constexpr s32 kSpCursor = 2366;  // s8: the cursor row of the floor list
inline constexpr s32 kSpRows = 2367;  // s8: rows shown (at most 6)
inline constexpr s32 kSpEntries = 2368;  // s8: the list's entry count (the stratum record +160)
inline constexpr s32 kSpScroll = 2369;  // s8: the list's scroll

// --- stratum record (gp-0x4604 = 0x7CE6EC, 200 bytes; sub_449ED0) --------------------------------------------------
inline constexpr s32 kStRecEntryBlock = 4;  // s8: list entry i (+4 + 4 i, 30 entries): its block
inline constexpr s32 kStRecEntryFloor = 6;  // s16: list entry i: its floor
inline constexpr s32 kStRecCount = 160;  // s8: list entries in use
inline constexpr s32 kStRecFloor = 162;  // s16: the current floor (1 at first)
inline constexpr s32 kStRecBlock = 164;  // s8: the current block (1 at first)
inline constexpr s32 kStRecDone = 165;  // u8: set when the map form may close
inline constexpr s32 kStRecBlockStates = 166;  // u8[6]: per block: 2 at first, 1 newly opened, 0 shown
inline constexpr s32 kStRecLayout = 172;  // u8: a layout flag (shifts the list 64 pixels)
inline constexpr s32 kStRecBlocksOpen = 173;  // s8: blocks open (1..6)

// --- mini-map work ("y_smap draw proc", 2996 bytes) ----------------------------------------------------------------
// The work of the Tartarus mini-map task, allocated by Y_SMap_CreateSmapDrawTask (calloc-like 0x960184, freed by its
// destroy callback sub_429C60). Positions of marks are screen pixels: per axis the map corner (+2140 / +2144) + the
// hero's (or the frozen centre's) offset inside its cell - the unit's offset (sub_429EF0 / sub_42A230 / sub_42A3F0
// with $f12 = the cell size +2857) + size / 4 + 2 (- 2 size for shadows, chests and the exit). The unnamed bytes the
// creator sets: +2558 / +2559 = 0, +2826 = 1 (no reader known).
// s8: the update's state 0..19 (the jump table 0x7BC340; see Y_SMap_UpdateSmapDrawTask)
inline constexpr s32 kSmapWorkState = 0;
// u32: H_Cdvd file handle 0 (+4 + 4 i, 9 slots): a smap/sMMM_NNN.tmx request (sub_42AA40), polled and destroyed by
// state 16; states 3..11 destroy it too
inline constexpr s32 kSmapWorkFile0 = 4;
// u32: H_Cdvd file handle 1 (+4 + 4 i, 9 slots): a smap/sMMM_NNN.tmx request (sub_42AA40), polled and destroyed by
// state 16; states 3..11 destroy it too
inline constexpr s32 kSmapWorkFile1 = 8;
// u32: H_Cdvd file handle 2 (+4 + 4 i, 9 slots): a smap/sMMM_NNN.tmx request (sub_42AA40), polled and destroyed by
// state 16; states 3..11 destroy it too
inline constexpr s32 kSmapWorkFile2 = 12;
// u32: H_Cdvd file handle 3 (+4 + 4 i, 9 slots): a smap/sMMM_NNN.tmx request (sub_42AA40), polled and destroyed by
// state 16; states 3..11 destroy it too
inline constexpr s32 kSmapWorkFile3 = 16;
// u32: H_Cdvd file handle 4 (+4 + 4 i, 9 slots): a smap/sMMM_NNN.tmx request (sub_42AA40), polled and destroyed by
// state 16; states 3..11 destroy it too
inline constexpr s32 kSmapWorkFile4 = 20;
// u32: H_Cdvd file handle 5 (+4 + 4 i, 9 slots): a smap/sMMM_NNN.tmx request (sub_42AA40), polled and destroyed by
// state 16; states 3..11 destroy it too
inline constexpr s32 kSmapWorkFile5 = 24;
// u32: H_Cdvd file handle 6 (+4 + 4 i, 9 slots): a smap/sMMM_NNN.tmx request (sub_42AA40), polled and destroyed by
// state 16; states 3..11 destroy it too
inline constexpr s32 kSmapWorkFile6 = 28;
// u32: H_Cdvd file handle 7 (+4 + 4 i, 9 slots): a smap/sMMM_NNN.tmx request (sub_42AA40), polled and destroyed by
// state 16; states 3..11 destroy it too
inline constexpr s32 kSmapWorkFile7 = 32;
// u32: H_Cdvd file handle 8 (+4 + 4 i, 9 slots): a smap/sMMM_NNN.tmx request (sub_42AA40), polled and destroyed by
// state 16; states 3..11 destroy it too
inline constexpr s32 kSmapWorkFile8 = 36;
// ptr: texture 0 (+40 + 4 i, 9 slots): loaded by name by sub_42AC60 (or by the texture poll of states 3..11);
// released by sub_429C60 (sub_4D0F00)
inline constexpr s32 kSmapWorkTex0 = 40;
// ptr: texture 1 (+40 + 4 i, 9 slots): loaded by name by sub_42AC60 (or by the texture poll of states 3..11);
// released by sub_429C60 (sub_4D0F00)
inline constexpr s32 kSmapWorkTex1 = 44;
// ptr: texture 2 (+40 + 4 i, 9 slots): loaded by name by sub_42AC60 (or by the texture poll of states 3..11);
// released by sub_429C60 (sub_4D0F00)
inline constexpr s32 kSmapWorkTex2 = 48;
// ptr: texture 3 (+40 + 4 i, 9 slots): loaded by name by sub_42AC60 (or by the texture poll of states 3..11);
// released by sub_429C60 (sub_4D0F00)
inline constexpr s32 kSmapWorkTex3 = 52;
// ptr: texture 4 (+40 + 4 i, 9 slots): loaded by name by sub_42AC60 (or by the texture poll of states 3..11);
// released by sub_429C60 (sub_4D0F00)
inline constexpr s32 kSmapWorkTex4 = 56;
// ptr: texture 5 (+40 + 4 i, 9 slots): loaded by name by sub_42AC60 (or by the texture poll of states 3..11);
// released by sub_429C60 (sub_4D0F00)
inline constexpr s32 kSmapWorkTex5 = 60;
// ptr: texture 6 (+40 + 4 i, 9 slots): loaded by name by sub_42AC60 (or by the texture poll of states 3..11);
// released by sub_429C60 (sub_4D0F00)
inline constexpr s32 kSmapWorkTex6 = 64;
// ptr: texture 7 (+40 + 4 i, 9 slots): loaded by name by sub_42AC60 (or by the texture poll of states 3..11);
// released by sub_429C60 (sub_4D0F00)
inline constexpr s32 kSmapWorkTex7 = 68;
// ptr: texture 8 (+40 + 4 i, 9 slots): loaded by name by sub_42AC60 (or by the texture poll of states 3..11);
// released by sub_429C60 (sub_4D0F00)
inline constexpr s32 kSmapWorkTex8 = 72;
// ptr[4]: the map frame's four corner sprite handles (+76 + 4 i, sub_430630; released by sub_429C60 through
// sub_115980)
inline constexpr s32 kSmapWorkCorners = 76;
// ptr[16][16]: tmx task per grid cell at +92 + 128 z + 8 x (random floor, sub_42BD80); on a fixed map the layer
// tasks at +92 + 8 i (sub_42BA50)
inline constexpr s32 kSmapWorkCellTasks = 92;
// f32: the map's screen corner x (from the creator's $a1, two f32); +2140..+2147 is also read as one unaligned
// 64-bit pair (ldr / ldl)
inline constexpr s32 kSmapWorkCornerX = 2140;
inline constexpr s32 kSmapWorkCornerY = 2144;  // f32: the map's screen corner y
// byte 7 of the corner pair: the ldl half of the unaligned 64-bit read of +2140..+2147 (the pair passed whole in
// $a1)
inline constexpr s32 kSmapWorkCornerEnd = 2147;
// s8: 1 = the map is shown (sub_429E80 [Y_SMap_SetShown]; tartarus.h tart::kSmapShown)
inline constexpr s32 kSmapWorkShown = 2148;
// s8: 1 = the map is centred on the frozen position, not the hero (sub_429E90; tart::kSmapFrozen)
inline constexpr s32 kSmapWorkFrozen = 2149;
// f32[3]: the frozen centre, the hero's position when it was frozen (tart::kSmapFrozenPos)
inline constexpr s32 kSmapWorkFrozenPos = 2152;
// u32: texture request 0 (+2164 + 4 i) polled by state 3 through sub_10C3A0 (no path of the update enters state 3:
// inf. a leftover)
inline constexpr s32 kSmapWorkTexReq0 = 2164;
// u32: texture request 1 (+2164 + 4 i) polled by state 4 through sub_10C3A0 (no path of the update enters state 3:
// inf. a leftover)
inline constexpr s32 kSmapWorkTexReq1 = 2168;
// u32: texture request 2 (+2164 + 4 i) polled by state 5 through sub_10C3A0 (no path of the update enters state 3:
// inf. a leftover)
inline constexpr s32 kSmapWorkTexReq2 = 2172;
// u32: texture request 3 (+2164 + 4 i) polled by state 6 through sub_10C3A0 (no path of the update enters state 3:
// inf. a leftover)
inline constexpr s32 kSmapWorkTexReq3 = 2176;
// u32: texture request 4 (+2164 + 4 i) polled by state 7 through sub_10C3A0 (no path of the update enters state 3:
// inf. a leftover)
inline constexpr s32 kSmapWorkTexReq4 = 2180;
// u32: texture request 5 (+2164 + 4 i) polled by state 8 through sub_10C3A0 (no path of the update enters state 3:
// inf. a leftover)
inline constexpr s32 kSmapWorkTexReq5 = 2184;
// u32: texture request 6 (+2164 + 4 i) polled by state 9 through sub_10C3A0 (no path of the update enters state 3:
// inf. a leftover)
inline constexpr s32 kSmapWorkTexReq6 = 2188;
// u32: texture request 7 (+2164 + 4 i) polled by state 10 through sub_10C3A0 (no path of the update enters state 3:
// inf. a leftover)
inline constexpr s32 kSmapWorkTexReq7 = 2192;
// u32: texture request 8 (+2164 + 4 i) polled by state 11 through sub_10C3A0 (no path of the update enters state 3:
// inf. a leftover)
inline constexpr s32 kSmapWorkTexReq8 = 2196;
// ptr: the "smap_symbol_dirp" task (the hero's direction arrow, sub_42BFD0 / sub_42BC10); sub_456400(task, on) shows
// / hides it
inline constexpr s32 kSmapWorkSymbolTask = 2200;
// f32: the symbol task's box x = corner x + the box sub_423FE0 centres in the 126 x 126 map
inline constexpr s32 kSmapWorkSymbolX = 2204;
inline constexpr s32 kSmapWorkSymbolY = 2208;  // f32: the symbol task's box y
// f32: party member 1's mark x (+2232 + 8 pc; indexed here by work + 8 m for member m + 1); also the sparkles' base
// (sub_42CD80)
inline constexpr s32 kSmapWorkPcMark1X = 2240;
inline constexpr s32 kSmapWorkPcMark1Y = 2244;  // f32: party member 1's mark y (+2236 + 8 pc)
// s16[3]: the bad-status blink phase of party members 1..3 (+2352 + 2 pc, sub_42C0A0); cleared by the creator
inline constexpr s32 kSmapWorkPcBlink1 = 2354;
// s8: 1 = party member 1's mark lay inside the map this frame (+2359 + pc, set by sub_42C0A0, read by sub_42CD80);
// cleared each update
inline constexpr s32 kSmapWorkPcDrawn1 = 2360;
inline constexpr s32 kSmapWorkPcDrawn2 = 2361;  // s8: the same for party member 2
inline constexpr s32 kSmapWorkPcDrawn3 = 2362;  // s8: the same for party member 3
inline constexpr s32 kSmapWorkEcMarkX = 2364;  // f32: shadow i's mark x (+2364 + 8 i, i < 24; sub_42CFC0)
inline constexpr s32 kSmapWorkEcMarkY = 2368;  // f32: shadow i's mark y (+2368 + 8 i)
// s16: the blink phase of a shadow touching the hero (0..20, sub_42CFC0); cleared by the creator
inline constexpr s32 kSmapWorkEcBlink = 2556;
inline constexpr s32 kSmapWorkChestMarkX = 2560;  // f32: treasure record i's mark x (+2560 + 8 i, i < 32)
inline constexpr s32 kSmapWorkChestMarkY = 2564;  // f32: treasure record i's mark y (+2564 + 8 i)
// f32: the floor exit's mark x (the position at 0x86E684, while 0x86E580 == 1)
inline constexpr s32 kSmapWorkExitMarkX = 2816;
inline constexpr s32 kSmapWorkExitMarkY = 2820;  // f32: the floor exit's mark y
// s8: the floor exit's grid cell x (sub_44F120); the hero on it sets the flag gp-0x4628 (0x7CE6C8)
inline constexpr s32 kSmapWorkExitCellX = 2824;
inline constexpr s32 kSmapWorkExitCellZ = 2825;  // s8: the floor exit's grid cell z (sub_44F170)
// s8: the grid cell x of the door position next to the stairs (sub_42FD80's out); the hero on it sets the
// stairs-found flag gp-0x462C (0x7CE6C4)
inline constexpr s32 kSmapWorkStairDoorX = 2827;
inline constexpr s32 kSmapWorkStairDoorZ = 2828;  // s8: that cell's z
// f32[2]: the stair cell's world x / z (800 x, 800 z; written by sub_42FD80, +2836 = z)
inline constexpr s32 kSmapWorkStairPos = 2832;
// ptr: the stair icon task (Y_SMap_CreateStaireDispTask, "y_staire_disp_proc")
inline constexpr s32 kSmapWorkStairTask = 2844;
// ptr: the map's background box-fill task (Y_LMap_CreateBoxfillTasks(task, corner, 2), 126 x 126)
inline constexpr s32 kSmapWorkBoxfill = 2848;
inline constexpr s32 kSmapWorkMaskTask = 2852;  // ptr: the "y_smap mask draw " task (Y_SMap_CreateSmapMaskDrawTask)
// s8: the map's view in cells (7: the update walks (7 + 4)^2 cells around the hero)
inline constexpr s32 kSmapWorkViewCells = 2856;
inline constexpr s32 kSmapWorkCellPx = 2857;  // s8: a cell's size in pixels (126 / 7 = 18)
inline constexpr s32 kSmapWorkLayerCount = 2858;  // s8: the fixed map's file / layer count (sub_42AA40's result)
// s16[10]: layout-table entry index of file / layer k (+2940 + 2 k, -1 = none; sub_42AA40)
inline constexpr s32 kSmapWorkLayerEntry = 2940;
// s16: the layout-table entry of the current scene (major, minor), -1 = none (also read as s8 for the symbol task's
// floor)
inline constexpr s32 kSmapWorkSceneEntry = 2960;

// --- mini-map tmx task work ("y_tmx_disp_proc" of a room cell / layer) ---------------------------------------------
// The work of a "y_tmx_disp_proc" task (Y_LMap_CreateTmxDispTask / sub_427BF0): one per room cell on a random floor
// (work +92 + 128 z + 8 x) or one per layer of a fixed map (+92 + 8 i). The update reaches it as *(task + 60).
inline constexpr s32 kSmapTmxColR = 272;  // u8: vertex colour k red (+272 + 4 k, k < 4)
inline constexpr s32 kSmapTmxColG = 273;  // u8: vertex colour k green (+273 + 4 k)
inline constexpr s32 kSmapTmxColB = 274;  // u8: vertex colour k blue (+274 + 4 k)
// u8: vertex colour k alpha (+275 + 4 k): 255 for a seen room, 0 hides a room not yet seen
inline constexpr s32 kSmapTmxColA = 275;
inline constexpr s32 kSmapTmxX = 308;  // f32: the tmx's screen x
inline constexpr s32 kSmapTmxY = 312;  // f32: the tmx's screen y
inline constexpr s32 kSmapTmxHidden = 336;  // s8: 1 = not drawn, 0 = drawn

// --- sprite handle (sprCreateHandle) -------------------------------------------------------------------------------
// A 2D sprite handle (sprCreateHandle) of the mini-map's sprite file (gp-0x460C, smap/i_mini_map01.spr): the frame
// corners at work +76..+88.
// u8: sprite handle +24: 0 = drawn, 255 = hidden (tartarus_smap.cpp calls it the alpha; it works as a transparency)
inline constexpr s32 kSmapSprFade = 24;

// --- Tartarus grid cell (16 bytes, K_Field_Get() + 72 + 256 z + 16 x) ----------------------------------------------
// The random floor's grid; the update forms K_Field_Get() + (z << 8) + 16 x and reads these offsets.
inline constexpr s32 kSmapCellFloor = 72;  // u8: cell +0, 1 = a floor cell (26_field.md 6.2)
// u8: cell +1, must also be 1 for a room / stair cell on the map (meaning not established)
inline constexpr s32 kSmapCellB1 = 73;

// --- field units (448 bytes) ---------------------------------------------------------------------------------------
// gFldUnitsPc 0x8717A0 [4]: the update's party loop indexes gFldUnitsPc[m] (m = 0..2) and reads the next unit's +72
// / +84.
// ptr: gFldUnitsPc + 448 m + 520 = gFldUnitsPc[m + 1] +72 (party member m + 1's DatUnit, 0 = empty)
inline constexpr s32 kSmapPc1Used = 520;
// ptr: gFldUnitsPc + 448 m + 532 = gFldUnitsPc[m + 1] +84 (its scene resource)
inline constexpr s32 kSmapPc1SceneRes = 532;

// --- treasure records (0x86BE80, 32 x 312 bytes) -------------------------------------------------------------------
// 32 records of 312 bytes at 0x86BE80 (the treasure boxes the map marks, sub_42EA60).
inline constexpr s32 kSmapChestPos = 268;  // f32[3]: a treasure record's position (record +0 non-zero = used)

// --- fixed-map layout table (gp-0x4A40 = 0x7CE2B0) -----------------------------------------------------------------
// *(gp-0x4A40) (0x7CE2B0) -> an array of 964-byte records indexed by scene major - 31: s32 count, then up to 24
// entries of 40 bytes from +4. The code addresses entry i as rec + 40 i, so its fields read at +4 (group), +8
// (major), +10 (minor).
inline constexpr s32 kSmapLayoutCount = 0;  // s32: layout record +0, the number of 40-byte entries
// s32: entry +4 (from rec + 40 i): the entry's map group; every entry of one group is one map sheet
inline constexpr s32 kSmapLayoutGroup = 4;
inline constexpr s32 kSmapLayoutMajor = 8;  // u16: entry +8: the scene major
inline constexpr s32 kSmapLayoutMinor = 10;  // u16: entry +10: the scene minor (also the file name's second number)

// --- mini-map mask work ("y_smap mask draw ", 128 bytes) -----------------------------------------------------------
// The work of the "y_smap mask draw " task (Y_SMap_CreateSmapMaskDrawTask / Y_SMap_UpdateSmapMaskDrawTask 0x430BB0;
// freed by sub_4310E0): four box-fill tasks that mask the screen around the map.
inline constexpr s32 kSmapMaskState = 0;  // s8: the mask task's state (0 = create the four box-fill masks)
inline constexpr s32 kSmapMaskCornerX = 20;  // f32: the map corner x
inline constexpr s32 kSmapMaskCornerY = 24;  // f32: the map corner y
inline constexpr s32 kSmapMaskHalfCells = 124;  // s8: the map view in cells / 2 (7 / 2 = 3, rounded toward zero)
// s8: 0 = the random-floor layout (states 2 / 12), 1 = the fixed-map layout (state 17)
inline constexpr s32 kSmapMaskLayout = 125;

// --- shadow think work ("ene think proc", 4248 bytes; the creator's fields) ----------------------------------------
inline constexpr s32 kEneByte0 = 0;  // u8: cleared
inline constexpr s32 kEneUnit = 1;  // s8: the shadow's index in gFldUnitsEc
inline constexpr s32 kEneState = 2;  // s8: the think state (4 roam; 3 for kind 4; or the state kept in the unit +410)
inline constexpr s32 kEneSubState = 3;  // s8: the state's sub-state (17 / 1 when a chase is resumed)
inline constexpr s32 kEneSubState2 = 4;  // s8
inline constexpr s32 kEneSubState3 = 5;  // s8
inline constexpr s32 kEneByte7 = 7;  // u8: cleared when a kind-3 chase resumes
inline constexpr s32 kEneKind4Word = 16;  // u32: sub_1AAA20(task, unit) for kind-4 shadows
inline constexpr s32 kEneBehaviour = 24;  // s8: the behaviour kind (unit +408)
inline constexpr s32 kEneStairPosX = 40;  // f32: kind 4: the stair door point (sub_452F70)
inline constexpr s32 kEneStairPosY = 44;  // f32
inline constexpr s32 kEneStairPosZ = 48;  // f32
inline constexpr s32 kEnePaused = 64;  // u8: 1 = paused (unit +412 == 1; sub_4532D0)
inline constexpr s32 kEneTargetX = 139;  // u8: the stored target cell (unit +409 low nibble)
inline constexpr s32 kEneTargetZ = 140;  // u8: (unit +409 high nibble)

// --- enemy-dead effect work ("y_ene_dead effect proc", 16 bytes) ---------------------------------------------------
inline constexpr s32 kEneDeadState = 0;  // s8: 0 = the EPL not started yet
inline constexpr s32 kEneDeadPosX = 4;  // f32: the dead shadow's position (its controller, sub_1AD940)
inline constexpr s32 kEneDeadPosY = 8;  // f32
inline constexpr s32 kEneDeadPosZ = 12;  // f32

// --- symbol-direction work ("smap_symbol_dirp", 336 bytes) ---------------------------------------------------------
inline constexpr s32 kEneDirpState = 0;  // s8: 0 start, 1 get the hero's resource, 2 draw
inline constexpr s32 kEneDirpFile = 4;  // u32: an H_Cdvd file (destroyed by sub_456050)
inline constexpr s32 kEneDirpTexture = 8;  // ptr: a texture (destroyed by sub_456050 through sub_4D0F00)
// Im2D vertices [4] of 64 bytes (screen z +8, recip z +24, colours +32..+44 relative to v5 + 64 i)
inline constexpr s32 kEneDirpVerts = 16;
inline constexpr s32 kEneDirpArg1 = 280;  // u32: the creator's $a1
inline constexpr s32 kEneDirpArg2 = 284;  // u32: the creator's $a2
inline constexpr s32 kEneDirpCentreX = 288;  // f32: the marker centre ($f12; sub_4561D0)
inline constexpr s32 kEneDirpCentreY = 292;  // f32 ($f13)
inline constexpr s32 kEneDirpDepth = 296;  // f32: subtracted from the near screen z ($f14)
inline constexpr s32 kEneDirpFloor = 300;  // s32 (sub_4563C0)
inline constexpr s32 kEneDirpPosX = 304;  // f32 (sub_4563D0)
inline constexpr s32 kEneDirpPosY = 308;  // f32
inline constexpr s32 kEneDirpAngle = 312;  // f32 (sub_4563B0)
inline constexpr s32 kEneDirpU = 316;  // f32: 0.75, the texture u of the far corners
inline constexpr s32 kEneDirpV = 320;  // f32: 0.75, the texture v
inline constexpr s32 kEneDirpHeroRes = 324;  // ptr: the hero's scene resource (sub_3B5D10 [MT_Scene_GetRes](1024))
inline constexpr s32 kEneDirpShown = 328;  // u8: draw only when set (sub_456400)

// --- Kyoto NPC think work ("Kyoto_NpcThink proc", 1204 bytes) ------------------------------------------------------
// "Kyoto" is functions.json's name for this subsystem (the field root creates "Kyoto_NpcModeRead proc"): four NPCs
// built on party models (datUnitCreatePc 2, 4, 6, 3) in the NPC unit slots 0x86E6A0 walk waypoint routes (scene
// resources 0x3C00 | n / 0x4000 | n); one that comes within reach of a party member (sub_458CB0) stops everything
// and runs a catch sequence and script; after their laps a lap script runs. The table 0x6B4AB0 (28 bytes per NPC)
// holds the frame counts of the "y wait task" steps; 0x7BC610 (10 words per NPC, -1 ended) the waypoints where an
// NPC pauses.
// s8: 0 idle, 1 start, 2 walk the route, 3 wait for all, 4 / 5 the lap script (sub_458850 sets 1)
inline constexpr s32 kKyotoState = 0;
inline constexpr s32 kKyotoRoute = 1;  // s8: the creator's $a2 (0..2)
inline constexpr s32 kKyotoIndex = 2;  // s8: the NPC slot 0..3 (0x86E6A0 + 448 i)
inline constexpr s32 kKyotoWaypoint = 4;  // s16: the next waypoint (scene resource 0x3C00 / 0x4000 | n)
inline constexpr s32 kKyotoLap = 6;  // s8: laps done (sub_458B00)
inline constexpr s32 kKyotoCatch = 7;  // s8: 0 patrol, 1 caught a party member, 2..8 the catch sequence (8 = done)
inline constexpr s32 kKyotoPaused = 8;  // u8: 1 = paused (sub_4589D0)
inline constexpr s32 kKyotoScriptTask = 12;  // ptr: the lap / catch script task
inline constexpr s32 kKyotoWaitTask = 16;  // ptr: the current "y wait task"
inline constexpr s32 kKyotoWaiting = 20;  // u8: 1 while pausing at a waypoint (the table 0x7BC610)
inline constexpr s32 kKyotoWaitFrames = 22;  // s16: frames paused (60 max)
inline constexpr s32 kKyotoSteps = 24;  // s16: waypoints reached
inline constexpr s32 kKyotoSavedPosX = 28;  // f32: the position saved when caught
inline constexpr s32 kKyotoSavedPosY = 32;  // f32
inline constexpr s32 kKyotoSavedPosZ = 36;  // f32
inline constexpr s32 kKyotoMoveCount = 40;  // s16: the mover steps saved (24-byte records from +44)
inline constexpr s32 kKyotoHomePosX = 48;  // f32: the NPC's return point
inline constexpr s32 kKyotoHomePosY = 52;  // f32
inline constexpr s32 kKyotoHomePosZ = 56;  // f32
inline constexpr s32 kKyotoMarkerA = 1196;  // ptr: a field marker task (sub_1A5320, colour {255, 0, 0, 128})
inline constexpr s32 kKyotoMarkerB = 1200;  // ptr: the second (colour {0, 255, 0, 128})

// --- wait task work ("y wait task", 12 bytes) ----------------------------------------------------------------------
inline constexpr s32 kWaitFrames = 0;  // s16: frames to wait
inline constexpr s32 kWaitCount = 2;  // s16: frames waited
inline constexpr s32 kWaitProc = 4;  // s16: a field-script procedure run at the end (0 none)
inline constexpr s32 kWaitScript = 8;  // ptr: that script task

// --- time-limit work ("y_TimeLimit draw", 96 bytes; the creator's fields) ------------------------------------------
inline constexpr s32 kTlByte4 = 4;  // u8: cleared
inline constexpr s32 kTlByte5 = 5;  // u8: cleared
inline constexpr s32 kTlByte66 = 66;  // u8: cleared
inline constexpr s32 kTlByte67 = 67;  // u8: cleared
inline constexpr s32 kTlWord68 = 68;  // s16: cleared
inline constexpr s32 kTlWord72 = 72;  // u32: cleared
inline constexpr s32 kTlByte76 = 76;  // u8: 1
inline constexpr s32 kTlSeconds = 80;  // u32: the time limit in seconds ($a1)
inline constexpr s32 kTlMinTens = 84;  // u8: (seconds / 60) / 10
inline constexpr s32 kTlMinOnes = 85;  // u8: (seconds / 60) % 10
inline constexpr s32 kTlSecTens = 86;  // u8: (seconds % 60) / 10
inline constexpr s32 kTlSecOnes = 87;  // u8: (seconds % 60) % 10
inline constexpr s32 kTlByte92 = 92;  // u8: cleared
inline constexpr s32 kTlByte93 = 93;  // u8: cleared

}  // namespace tart2


void Y_SMap_UpdateSmapDrawTask(EEContext& ctx);  // 0x4281F0 "y_smap draw proc" update: the mini-map's 20-state load / draw machine; 0 or -1
void sub_429C60(EEContext& ctx);  // 0x429C60 mini-map destroy callback: textures +40.., corner sprites +76.., then free the work
void Y_SMap_CreateSmapDrawTask(EEContext& ctx);  // 0x429D40 creates "y_smap draw proc" (2996-byte work) at corner $a1 on map scenes; the task or 0
void sub_42AA40(EEContext& ctx);  // 0x42AA40 requests the smap/s%03d_%03d.tmx files of the scene's map group; their count (s8)
void sub_42AC60(EEContext& ctx);  // 0x42AC60 loads the fixed map's textures smap/s%03d_%03d into work +40 + 4 k
void sub_4302B0(EEContext& ctx);  // 0x4302B0 boot load: smap/i_mini_map01.spr, smap0..8.tmx (0x95C0E0..), symbol/smap_p.tmx
void Y_SMap_CreateSmapMaskDrawTask(EEContext& ctx);  // 0x431110 creates "y_smap mask draw " (128-byte work: corner, cells / 2, layout); the task or 0
void Y_Npc_UpdateNpcThinkTask(EEContext& ctx);  // 0x4312B0 the "npc think proc" update: one party member's AI per frame; 0
void sub_431630(EEContext& ctx);  // 0x431630 the "npc think proc" destroy callback: clears the column place, frees the work
void Y_Npc_CreateNpcThinkTask(EEContext& ctx);  // 0x431670 creates party member pc's "npc think proc" task and its 4708-byte work
void sub_431880(EEContext& ctx);  // 0x431880 explore: counts a visit to the current cell; 1 when it is time to look around
void sub_431AA0(EEContext& ctx);  // 0x431AA0 explore: wall-following step for rule 0: the next direction from the open sides
void sub_432050(EEContext& ctx);  // 0x432050 explore: wall-following step for rule 1: the next direction from the open sides
void sub_432600(EEContext& ctx);  // 0x432600 explore: wall-following step for rule 2: the next direction from the open sides
void sub_432BB0(EEContext& ctx);  // 0x432BB0 explore: wall-following step for rule 3: the next direction from the open sides
void sub_433160(EEContext& ctx);  // 0x433160 explore: the first open side whose neighbour was never visited (4, 2, 1, 3 order); 0 none
void sub_4332F0(EEContext& ctx);  // 0x4332F0 explore: flips the wall-following rule 0 <-> 1 after 9 steps inside one room
void sub_4333D0(EEContext& ctx);  // 0x4333D0 explore: flips the wall-following rule 2 <-> 3 after 9 steps inside one room
void sub_4334D0(EEContext& ctx);  // 0x4334D0 explore: marks the other cells of a 2x2 block as visited with the current one
void sub_433810(EEContext& ctx);  // 0x433810 the 2x2 block origin cell (16 z + x) of cell (x, z), else 0
void sub_4339D0(EEContext& ctx);  // 0x4339D0 explore: turns towards the least visited open side; returns its direction
void sub_433DE0(EEContext& ctx);  // 0x433DE0 path search: expands the next queued cell (breadth-first); 2 goal reached, 1 start is (0,0), 0
void sub_4343D0(EEContext& ctx);  // 0x4343D0 path search: walks the path records back from the goal into the step list (at most 100)
void sub_4344F0(EEContext& ctx);  // 0x4344F0 follow: the side-step target beside the hero by the member's column place (20 / -40 / 60)
void sub_434770(EEContext& ctx);  // 0x434770 follow: walks towards a point in the hero's column; 1 when the member is close enough
void sub_434920(EEContext& ctx);  // 0x434920 follow: the same as sub_434770 for the hero, with the column offsets 150 / +-80
void sub_434C90(EEContext& ctx);  // 0x434C90 gives party member a1 the first free place in the hero's column (0x7CE6E8..)
void sub_434D30(EEContext& ctx);  // 0x434D30 the "explore" order: every live member to mode 2, tactic 0x7CE6BC = 1, the column cleared
void sub_434E60(EEContext& ctx);  // 0x434E60 the "follow" order: every live member to mode 1, tactic 0x7CE6BC = 0
void sub_434F60(EEContext& ctx);  // 0x434F60 sets the s8 0x7CE6C0 (gp-0x4630): the follow formation switch
void sub_435060(EEContext& ctx);  // 0x435060 sets kNpcHeld of every live member 1..3
void sub_4350E0(EEContext& ctx);  // 0x4350E0 holds / releases every live member except a0, pausing their movers and idle animations
void sub_435260(EEContext& ctx);  // 0x435260 party member a0's kNpcHeld (1 when its unit is not live)
void sub_4352E0(EEContext& ctx);  // 0x4352E0 1 when any live member 1..3 is held
void sub_435370(EEContext& ctx);  // 0x435370 sets kNpcAvoidFights of every live member and the byte 0x7CDB10
void sub_4353F0(EEContext& ctx);  // 0x4353F0 a field unit's think mode: party (+1) or shadow (+2) by the unit's kind
void sub_435440(EEContext& ctx);  // 0x435440 counts the live members within reach of member a0 whose HP is under the maximum
void sub_435660(EEContext& ctx);  // 0x435660 the first member (or the hero) near a0 in follow mode with status bit 0x80; -1 none
void sub_435810(EEContext& ctx);  // 0x435810 the following member with skill 202 / 203 and the most SP; -1 none
void sub_4359F0(EEContext& ctx);  // 0x4359F0 path search from (x, z) to (gx, gz): runs the expansion, builds the steps; 1 found
void sub_435C00(EEContext& ctx);  // 0x435C00 think mode 1 (follow the hero): support skills, then the follow sub-states +4643
void sub_437E00(EEContext& ctx);  // 0x437E00 calls sub_456410 (mode setter 0) for party member a0
void sub_437E20(EEContext& ctx);  // 0x437E20 1 when party member a0 is not in follow states 7..12 (the column)
void sub_437E80(EEContext& ctx);  // 0x437E80 the nearest cell of kind 8 to party member a1, as a door point
void sub_438010(EEContext& ctx);  // 0x438010 think mode 2 (explore alone): fights, chests, wall following, sub-states +4640
void sub_439400(EEContext& ctx);  // 0x439400 explore: a chest in reach of member a0 -> kNpcBusy = 1, explore state 6
void sub_439520(EEContext& ctx);  // 0x439520 think mode 5 (a skirmish with a shadow): the sub-states +4632
void sub_439F60(EEContext& ctx);  // 0x439F60 1 when a shadow touches member a1 (and, with kNpcAvoidFights, already fights)
void sub_43A0B0(EEContext& ctx);  // 0x43A0B0 1 when a shadow touches the hero near member a1 (follow mode)
void sub_43A1A0(EEContext& ctx);  // 0x43A1A0 puts member a0 into a skirmish with shadow a1 (mode 5, state 5)
void sub_43A230(EEContext& ctx);  // 0x43A230 1 when member a0 is in a skirmish waiting for its battle (states 3 / 6)
void sub_43A2F0(EEContext& ctx);  // 0x43A2F0 the mode-change script: runs the member's script, pauses the floor, resumes after
void sub_43A960(EEContext& ctx);  // 0x43A960 skill use states: 0 -> 1 -> 2 -> done (kNpcSkillUse 0, kind / target -1)
void sub_43A9D0(EEContext& ctx);  // 0x43A9D0 heals member a1 with member a0's healing skills (0xC0..0xC5); a result code
void sub_43B980(EEContext& ctx);  // 0x43B980 the cure skill (202 / 203) member a0 would use on a1; -1 none
void sub_43BC20(EEContext& ctx);  // 0x43BC20 the number of ailment bits (1 2 4 8 0x20 0x40 0x80) of member a0's status
void sub_43BDA0(EEContext& ctx);  // 0x43BDA0 the revive skill (204 / 205) member a0 casts on a1; -1 none
void sub_43BF50(EEContext& ctx);  // 0x43BF50 support walk: to member +4646, cast the support skill, back to follow / explore
void sub_43C180(EEContext& ctx);  // 0x43C180 the member in reach of a0 with skill 205 and the most SP; 0 none
void sub_43C340(EEContext& ctx);  // 0x43C340 the member in reach of a0 with skill 204 and the most SP; 0 none
void Y_Npc_UpdateTreasureFreeTask(EEContext& ctx);  // 0x43C500 the "treasure free proc" update: plays the chest's opening, frees it; -1
void sub_43C660(EEContext& ctx);  // 0x43C660 the "treasure free proc" destroy callback: frees the work
void Y_Npc_CreateTreasureFreeTask(EEContext& ctx);  // 0x43C690 creates "treasure free proc" for treasure record a0 (12-byte work)
void sub_43C730(EEContext& ctx);  // 0x43C730 1 when member a0 has no mode-change, skill use or support walk pending
void sub_43C7A0(EEContext& ctx);  // 0x43C7A0 sets member a0's think mode to a1 and clears its sub-states
void sub_43C7F0(EEContext& ctx);  // 0x43C7F0 a party / NPC unit's think mode (6 when not live; 0 for the hero)
void sub_43C910(EEContext& ctx);  // 0x43C910 a party / NPC unit's current HP (the hero's from sub_16C5F0(1))
void Y_StParts_UpdateStratumPartsTask(EEContext& ctx);  // 0x43CA30 the "y_StratumParts_proc" update: the stratum screen's 49 states; -1 when done
void sub_447AD0(EEContext& ctx);  // 0x447AD0 the "y_StratumParts_proc" destroy callback: textures, sprites, script, record, the work
void Y_Stratum_CreateStratumPartsTask(EEContext& ctx);  // 0x447E70 creates "y_StratumParts_proc" (2396-byte work; a1 mode, a2 from the map); sets flag 5149
void sub_449ED0(EEContext& ctx);  // 0x449ED0 allocates the stratum record (gp-0x4604, 200 bytes) with its defaults
void sub_449FA0(EEContext& ctx);  // 0x449FA0 frees the stratum record (gp-0x4604) when set
void sub_44A990(EEContext& ctx);  // 0x44A990 draws the stratum background's wobbling triangle list (frame counter mod 180)
void sub_44ACF0(EEContext& ctx);  // 0x44ACF0 the "ene think proc" destroy callback: frees the work
void Y_Stratum_CreateEneThinkTask(EEContext& ctx);  // 0x44AD20 creates shadow a1's "ene think proc" task (4248-byte work)
void sub_454290(EEContext& ctx);  // 0x454290 the "y_ene_dead effect proc" destroy callback: frees the work
void Y_Stratum_CreateEneDeadEffectTask(EEContext& ctx);  // 0x4542C0 creates "y_ene_dead effect proc" at shadow a0's position; removes the shadow
void sub_455E00(EEContext& ctx);  // 0x455E00 the "smap_symbol_dirp" update: draws the direction marker quad (Im2D); 0
void sub_456050(EEContext& ctx);  // 0x456050 the "smap_symbol_dirp" destroy callback: its file and texture, then the work
void Y_Stratum_CreateSmapSymbolDirpTask(EEContext& ctx);  // 0x4560D0 creates the "smap_symbol_dirp" task (336-byte work) under parent a0
void Y_Kyoto_UpdateKyotoNpcModeReadTask(EEContext& ctx);  // 0x4575E0 loads the four Kyoto NPCs one by one, then creates their think tasks; -1 done
void sub_457980(EEContext& ctx);  // 0x457980 the "Kyoto_NpcModeRead proc" destroy callback: frees the work
void Y_Kyoto_CreateKyotoNpcModeReadTask(EEContext& ctx);  // 0x4579B0 creates "Kyoto_NpcModeRead proc" (1-byte work) under parent a0
void Y_Kyoto_UpdateKyotoNpcThinkTask(EEContext& ctx);  // 0x457A40 one Kyoto NPC per frame: the catch sequence (+7) or the route walk (+0); 0
void sub_458600(EEContext& ctx);  // 0x458600 the "Kyoto_NpcThink proc" destroy callback: frees the work
void Y_Kyoto_CreateKyotoNpcThinkTask(EEContext& ctx);  // 0x458630 creates NPC a1's "Kyoto_NpcThink proc" (route a2) with two markers
void sub_458850(EEContext& ctx);  // 0x458850 Kyoto NPC task a0: state 1 (start walking)
void sub_458870(EEContext& ctx);  // 0x458870 Kyoto NPC task a0: catch state 1
void sub_458890(EEContext& ctx);  // 0x458890 pauses every Kyoto NPC (mover and think)
void sub_458920(EEContext& ctx);  // 0x458920 Kyoto NPC task a0: catch state 0
void sub_458930(EEContext& ctx);  // 0x458930 resumes every Kyoto NPC (the mover unless its catch is done)
void sub_4589D0(EEContext& ctx);  // 0x4589D0 Kyoto NPC task a0: kKyotoPaused = a1
void sub_4589E0(EEContext& ctx);  // 0x4589E0 1 when every Kyoto NPC's mover is idle and none is caught
void sub_458A80(EEContext& ctx);  // 0x458A80 1 when waypoint a1 is a pause point of NPC a0 (table 0x7BC610)
void sub_458B00(EEContext& ctx);  // 0x458B00 every Kyoto NPC: one more lap, walk again
void sub_458B60(EEContext& ctx);  // 0x458B60 every Kyoto NPC: state 6
void sub_458BB0(EEContext& ctx);  // 0x458BB0 destroys the Kyoto NPC units (DatUnit, model, resource, tasks)
void sub_458CB0(EEContext& ctx);  // 0x458CB0 checks NPC a1 against the party; on contact starts the catch; 1 when caught
void sub_459790(EEContext& ctx);  // 0x459790 catch step 8: waits, then restores the NPCs and the field (second half of the catch)
void sub_459D60(EEContext& ctx);  // 0x459D60 destroys the two marker tasks of every Kyoto NPC
void sub_459E00(EEContext& ctx);  // 0x459E00 1 when every Kyoto NPC except a0 finished its catch (+7 == 8)
void Y_Kyoto_UpdateWaitTask(EEContext& ctx);  // 0x459E80 the "y wait task" update: counts frames, then runs its procedure; -1
void sub_459F30(EEContext& ctx);  // 0x459F30 the "y wait task" destroy callback: frees the work
void Y_Kyoto_CreateWaitTask(EEContext& ctx);  // 0x459F60 creates a "y wait task" of a1 frames running procedure a2 after
void sub_45A220(EEContext& ctx);  // 0x45A220 the "y_TimeLimit draw" destroy callback: its sprite, the work, the gp slot
void Y_TimeLimit_CreateTimeLimitDrawTask(EEContext& ctx);  // 0x45A280 creates "y_TimeLimit draw" for a1 seconds (mm:ss digits)

}  // namespace p3fes::game
