// Phase 5 slice field4: the field layer, fourth pass (docs/ANALYSIS/26_field.md) -- the code that loads and runs a
// field scene and places its people: the field loaders of k_fldrc.c (packs, model / world streams, field objects,
// ENV lighting, the NPC tables and placement files), the sequence entries of k_sequence.c, the field root of
// k_field.c, the automatic dungeon and the Tartarus floor generator of k_dungeon.c, the field event task of k_event.c,
// and the NPC-placement / field-effect band 0x1DC6F0-0x1E8000 (the field icons, the party-member movement rules, the
// developers' built-in NPC placement editor and its FBN writer, the field-script loader, the after-image helpers).
// The bodies (game/src/field/field4_root.cpp, field4_dungeon.cpp, field4_event.cpp, field4_npc.cpp) are
// p3fes_handgen's: register for register and block for block as the recompiled bodies (frame, spills, $ra links, cycle
// charges, check points); their roles, the record offsets below and the branch meanings are named on top
// (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen").
//
// Names: the functions keep their symbols/functions.json names; a proposed name is given in brackets in the comments
// (ADR-0009: from the instructions, the strings, the callers and the snapshots; not imported). The offsets below are
// read from this slice's instructions and checked on the replay snapshots (climb_ref_17000: Tartarus floor 5 = the
// fixed floor 51/4, the dungeon task alive; dorm_replay_4900: the dorm 7/2; shop_ref_4100 / fusion_vr_5000: 8/4,
// 8/3; b_5800: the battle from Tartarus floor 400). tools/ours/types/deltas/field4.json feeds them to type recovery.
//
// ===================================================================================================================
// What the field keeps where (for the scene editor and the multiplayer server)
// ===================================================================================================================
//
// * The sequence packet. A field is entered through the admini sequences (26_field.md 1): sequence 2 =
//   K_Seq_CallField(packet {u16 major, minor, entry, sub1, sub2}), 3 = an event PM file, 5 = K_Seq_CallDungeon
//   (packet {s32 floor, s32 entry}). Everything below is rebuilt from that packet and the game state; a door is
//   "destroy this root, call sequence 2 with the next ids" (sub_1BAAA0 -> root state 17).
//
// * The field root task ("field root", sField.root) and its 104-byte work (namespace root): the state, the ids
//   (+16 major, +18 minor, +20 entry, +24 / +26 the scene sub-ids), the load requests, and +76.. the next field's ids.
//   The load phase word 0x7CE24C (K_Fld_GetPhase): 0 loading, 3 scene loaded, 1 setting up, 2 running.
//
// * sField 0x869F60, 4,636 bytes (namespace fld; K_Field_Init clears all of it, k_Field_CreateFieldRootTask the first
//   4,424): the field's task table (+0 root .. +44 area panel), +56 the flags (bit 31 = a dungeon floor), the
//   generator header +60..+67, the 16 x 16 Tartarus grid +72..+4167, the field script +4168, the resource loader's
//   step and pack queue +4184.., the NPC placement slots +4288.., the exit table +4420, the NPC script / messages /
//   schedule table +4428.., the field resource list +4456 / +4460 (up to 9 records: the field's world and objects,
//   or the nine Tartarus block models), and the shared EPL / object handles +4588...
//
// * The scene record 0x95AFC0 (MT_Scene, gp-0x57B0 holds the pointer): +0 s32 major, +4 s32 minor (-1 = none), +8 the
//   resource manager, +12 flags, +16 the ENV request, +20 s16 the NPC placement set (the FBN's third number), +22 s16
//   the ENV sub-id. The scene's resources (MT_Scene_GetRes / GetResListHead, 26_field.md 3.1) are what the editor
//   places: type 1 characters, 3 objects / NPCs (id 0xC00 | n, the FBN NPC records), 8 positions (the FBN position
//   records), 10 / 11 field-object models / EPLs, 12 Tartarus blocks (0x3000 + 16 z + x), 13 field hits, 15 enemies,
//   16..18 the block markers (enemy spawns, treasure, exits of a block, sub_1BB300).
//
// * NPC placement = the FBN files "field/data/fMMM_NNN_SSS.FBN" (SSS = scene +20; from the .pac "field/pack/..."
//   when it is resident): header {u32 magic 0x12345678, u32 version 0x00010001, u32 npc count, u32 npc record size
//   112, u32 position count, u32 position record size 96}, then the records (namespace fbn). sub_1E2E50 reads the
//   header and requests the models, sub_1E3940 creates the NPC resources at their matrices; the NPC schedule table
//   "nMMM_NNN.bin" (sField +4440) and the social-link table comutbl.bin (0x7CE240) can replace a placeholder model
//   {4, 0xFFFF} with the scheduled one for today. The original's own editor (sub_1E2370 "field editor": FREE CAMERA
//   MODE / NPC / NPC LIST / POS / POS LIST / SAVEFILE) snapshots the scene into the same records (sub_1E2430) and
//   serialises them in that exact layout (sub_1E2BD0): an FBN writer is a byte-compatible target for our editor.
//
// * Tartarus. The dungeon task ("automatic dungeon", slot 0x7CE268; namespace dng) holds the floor index +4 and the
//   entry +8; the floor table gFldDngFloorsData 0x867F60 (DUNGEONAT.BIN, 500 x 16 bytes; namespace dngfloor) gives the
//   floor's {major, minor, ..., min cells +6, max cells +7, flags +8, block script +12, EPL +13}. The field root of
//   a floor is created by the dungeon task with flags = entry.flags | 0x80000000 and the cell bounds -> sField +56,
//   +66, +67. Fixed floors (majors 51..58 / 71..78) copy their grid from "field/map/fMMM_NNN.MAP" (+4 .. +4100).
//   Random floors (majors 21..28 / 41..48, minor 0) are GENERATED at load time by sub_1BD450(blockSet = major - 20,
//   or - 40 in The Answer): its inputs are
//     - the block set (1..8) and The Answer flag (sub_17D800: 0x7CDFA4), which pick the block-pattern tables
//       (0x67F720 / 0x681560 the 8 patterns per set, 0x67FA26 / 0x681866 the start pattern; 430 halves per set);
//     - the cell-count bounds sField +66 (min) / +67 (max) from the floor entry;
//     - the RANDOM SOURCE: every draw is sub_488F30 = RpRandom (RenderWare's additive generator: a 31-word table in
//       the RwEngine plugin space at RwEngineInstance 0x960070 + the plugin offset 0x7CE778, {base, ptr1, ptr2, end};
//       ptr1 += *ptr2 and returns the sum >> 1). It is seeded ONCE per boot by kwlnMain with RpRandomSeed(Timer 0
//       count, the hardware register 0x10000000) and then advanced by every caller (63 functions: battle, shadows,
//       treasure, camera...), so the floor depends on the whole history of draws since boot. There is no per-floor
//       seed. Retries: the generator restarts until the start cell is a stairs block (kind 4), the floor has min..max
//       cells and at least two kind-4 cells; a run of more than 10,000 placements aborts the attempt (0x7CE260 /
//       0x7CE264).
//   A server that wants every client to see the same floor must therefore either (a) own the generation: put RpRandom
//   in a known state (RpRandomSeed(s) before sub_1BD450, s chosen by the server) and run the same code on every
//   client -- the generator touches nothing but sField +60..+67 / +72..+4167 and the RpRandom state, so equal inputs
//   give byte-equal grids (test_field4_dungeon.cpp checks that the hand-written and recompiled generators agree on
//   real snapshots and that a seed reproduces its grid) -- or (b) send the result: the 4,096-byte grid plus the
//   header bytes +60..+65 are the whole layout (the block builder sub_1BD8C0 / sub_1BB300 derives everything else from
//   them and the block models). The shadows and treasure that follow (sub_1D0720, sub_1D1FA0, K_Encount_PickEncounter)
//   draw from the same RpRandom, so (a) also needs the same draw order afterwards, (b) needs them sent too.
//
// * The field event task (sField +8, K_FldEvent_UpdateFldEventTask; namespace evt): exploring is its state 1; a
//   shadow contact builds the 52-byte battle packet at +40 and calls btlStart directly (26_field.md 7.1).
// ===================================================================================================================
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace f4 {

inline constexpr s32 kTaskWork = 60;  // KwlnTask +0x3C: the work pointer (every task update / destroy here)

// --- sField 0x869F60 (K_Field_Get), sField-relative offsets ----------------------------------------------------------
inline constexpr u32 kSField = 0x869F60u;
namespace fld {
inline constexpr s32 kRoot = 0;            // the "field root" task
inline constexpr s32 kCamera = 4;          // camera controller (K_FldCamera_CreateFieldCameraControlerTask)
inline constexpr s32 kEventTask = 8;       // the field event task (K_FldEvent_CreateTasks)
inline constexpr s32 kVirtualPad = 12;     // virtual pad (sub_1E1230)
inline constexpr s32 kEplDelay = 16;       // EPL delay task (sub_1A96C0)
inline constexpr s32 kSmap = 24;           // mini-map (Y_SMap_CreateSmapDrawTask)
inline constexpr s32 kWalls = 28;          // transparent-wall control (sub_1C1F30)
inline constexpr s32 kFootstep = 32;       // footstep supporter (sub_1D9F10)
inline constexpr s32 kEnemySched = 36;     // enemy pop scheduler (sub_1D36F0)
inline constexpr s32 kPartyPanel = 40;     // party panel (sub_18BFF0)
inline constexpr s32 kAreaPanel = 44;      // area-name panel (sub_18E820, majors < 200)
inline constexpr s32 kFlags = 56;          // u32: bit 31 = a dungeon floor (the dungeon task's entry.flags | bit 31)
inline constexpr s32 kStartX = 60;         // u8: the generator's start cell x (the stairs block)
inline constexpr s32 kStartZ = 61;         // u8: .. z
inline constexpr s32 kSeedX = 62;          // u8: the first placed block's cell x (2..12)
inline constexpr s32 kSeedZ = 63;          // u8: .. z
inline constexpr s32 kStartRot = 64;       // u8: the start block's quarter turns
inline constexpr s32 kSeedRot = 65;        // u8: the first block's quarter turns
inline constexpr s32 kMinCells = 66;       // u8: the floor's minimum cell count (floor entry +6; 6 outside Tartarus)
inline constexpr s32 kMaxCells = 67;       // u8: .. maximum (floor entry +7; 128 outside Tartarus)
inline constexpr s32 kArg68 = 68;          // s16: k_Field_CreateFieldRootTask's s10 (floor entry +4)
inline constexpr s32 kGrid = 72;           // the 16 x 16 grid, 256 bytes a row (z), 16 a cell (x): namespace cell
inline constexpr s32 kFieldScript = 4168;  // the field's BF script copy ("fMMM.bf", sub_1E7290)
inline constexpr s32 kFieldScriptSize = 4172;
inline constexpr s32 kLoadStep = 4184;     // sub_1B10F0's step (999 = done)
inline constexpr s32 kPackCount = 4188;    // the pack queue: count, then {u16 major, u16 minor} pairs
inline constexpr s32 kPackMajor = 4192;
inline constexpr s32 kPackMinor = 4194;
inline constexpr s32 kNpcCount = 4288;     // the NPC placement slots being created (sub_1E2E50 / sub_1E3940)
inline constexpr s32 kNpcModels = 4292;    // u32 model handles [count]
inline constexpr s32 kNpcSlots = 4296;     // 36-byte slots [count]: namespace npcslot
inline constexpr s32 kMapFile = 4300;      // the fixed floor's MAP request / the block models' grid source
inline constexpr s32 kBattleTasks = 4308;  // [4] tasks destroyed before a battle / the camp menu (event states 1 / 14)
inline constexpr s32 kBattleTasks2 = 4324; // [24] more of them (each checked)
inline constexpr s32 kExitCount = 4420;    // the 44-byte exit records (sub_1C7F20)
inline constexpr s32 kExits = 4424;
inline constexpr s32 kNpcScript = 4428;    // "nsMMM_NNN.bf" copy and size
inline constexpr s32 kNpcScriptSize = 4432;
inline constexpr s32 kNpcMessages = 4436;  // "nmMMM_NNN.bmd" copy
inline constexpr s32 kNpcTable = 4440;     // "nMMM_NNN.bin" copy: u32 count, then 32-byte schedule entries (+32)
inline constexpr s32 kNpcTableCount = 4444;
inline constexpr s32 kNpcTableEntries = 4448;
inline constexpr s32 kNpcTableLists = 4452;
inline constexpr s32 kResCount = 4456;     // the field resource records (namespace res), up to 9
inline constexpr s32 kRes = 4460;
inline constexpr s32 kFloorObj1 = 4588;    // the shared floor object models fobj001 / fobj002 (Tartarus)
inline constexpr s32 kFloorObj2 = 4592;
inline constexpr s32 kBtlEpl = 4596;       // ten EPL handles of btl_eff.pac (sub_1C0440), in this order:
inline constexpr s32 kEplPoison = 4600;    //   ENCONT_N (the encounter flash), F_MOUDOK, F_SAISEI, F_DAMEJI, F_SIBOU,
inline constexpr s32 kEplRegen = 4604;     //   F_HAKEN, F_KAIF..; The Answer adds three more (4624 / 4628 / 4632)
inline constexpr s32 kEplDamage = 4608;
inline constexpr s32 kEplDeath = 4612;
inline constexpr s32 kEplHaken = 4616;
inline constexpr s32 kEplHeal = 4620;
inline constexpr s32 kEplAnswer1 = 4624;
inline constexpr s32 kEplAnswer2 = 4628;   // the ambush flash in The Answer (event state 6)
inline constexpr s32 kEplAnswer3 = 4632;
inline constexpr s32 kSize = 4636;
}  // namespace fld

// --- one grid cell (sField + kGrid + 256 z + 16 x) --------------------------------------------------------------------
namespace cell {
inline constexpr s32 kRow = 256, kSize = 16;
inline constexpr s32 kState = 0;    // u8: 0 free, 1 a floor cell, 2 the border / reserved (the generator's ring)
inline constexpr s32 kHead = 1;     // u8: 1 on a block's origin cell
inline constexpr s32 kKind = 2;     // u8: the block kind = the index of its model in the resource list (+4460):
                                    //     0..7 = block models 1..8, 8 = model 18 (the 2 x 2 room); 4 = stairs
inline constexpr s32 kResId = 4;    // u16: the cell's block scene resource (0x3000 + 16 z + x of the origin)
inline constexpr s32 kRot = 6;      // u8: the block's quarter turns (the tag of sub_1BB090)
inline constexpr s32 kWidth = 7;    // u8: the block's width / depth in cells
inline constexpr s32 kDepth = 8;
inline constexpr s32 kOrder = 9;    // u8: the placement counter gp-0x4A94 when the block was placed
inline constexpr s32 kHeight = 10;  // s8: the block's level (x 300 units)
inline constexpr s32 kDoors = 11;   // u8: bits 4..7 = open toward z-1, x-1, z+1, x+1; the low nibble the same sides
inline constexpr s32 kLink = 12;    // s32: the cell's exit / marker id (block markers type 18, sub_1BB300; -1 none)
}  // namespace cell
// The same fields as sField-relative offsets of cell (0, 0): the bodies add 256 z + 16 x to &sField.
namespace gcell {
inline constexpr s32 kState = 72, kHead = 73, kKind = 74, kResId = 76, kRot = 78, kWidth = 79, kDepth = 80;
inline constexpr s32 kHeight = 82, kDoors = 83, kLink = 84;
inline constexpr s32 kLastRow = 3912;  // cell (0, 15) +0: the generator's bottom border row
inline constexpr s32 kLastCol = 312;   // cell (15, 0) +0: .. the right border column
}  // namespace gcell

// --- the field root's work (104 bytes, task +60) -------------------------------------------------------------------
namespace root {
inline constexpr s32 kState = 0;          // K_Field_UpdateFieldRootTask's state 0..18
inline constexpr s32 kHold = 4;           // 1 = hold the set-up (sub_1BAA50; the dungeon's stratum title)
inline constexpr s32 kShutdown = 8;       // K_Field_SetShouldShutdown: state 13 -> 18
inline constexpr s32 kEvent = 12;         // the event PM file id (sequence 3)
inline constexpr s32 kMajor = 16;         // u16 (K_Field_GetMajorId)
inline constexpr s32 kMinor = 18;         // u16 (K_Field_GetMinorId)
inline constexpr s32 kEntry = 20;         // u16: the entry point the party appears at (sub_1D03F0)
inline constexpr s32 kSub1 = 24;          // s16: the scene sub-id (sub_3B58C0)
inline constexpr s32 kSub2 = 26;          // s16: the time-of-day variant (sub_3B5980; 0 = sub_1B6EB0 picks)
inline constexpr s32 kHitRequest = 36;    // the hit-table request (K_Fldrc_RequestFieldHitTableFile)
inline constexpr s32 kScriptRequest = 40; // the field script request (sub_1E7200)
inline constexpr s32 kBlockScript = 44;   // the dungeon block script request (sub_1C0330)
inline constexpr s32 kPmReader = 56;      // the event PM file reader task (sequence 3)
inline constexpr s32 kEventViewer = 60;   // the event viewer task
inline constexpr s32 kScriptTask = 64;    // the running field script task
inline constexpr s32 kNowLoading = 68;    // the "NOW LOADING" task (sub_187E20)
inline constexpr s32 kNpcMode = 72;       // field 14/5's Kyoto NPC-mode task
inline constexpr s32 kNextMajor = 76;     // the next field's sequence-2 packet (28 bytes from +76)
inline constexpr s32 kNextMinor = 78;
inline constexpr s32 kNextEntry = 80;
inline constexpr s32 kNextSub1 = 82;
inline constexpr s32 kNextSub2 = 84;
inline constexpr s32 kSize = 104;
}  // namespace root

// --- the automatic dungeon's work (64 bytes; the task in 0x7CE268) -------------------------------------------------
namespace dng {
inline constexpr s32 kState = 0;       // K_FldDungeon_UpdateTask's state 0..9
inline constexpr s32 kFloor = 4;       // the floor index into gFldDngFloorsData
inline constexpr s32 kEntry = 8;       // the entry point
inline constexpr s32 kShutdown = 12;   // K_FldDungeon_RequestShutdown: state 3 -> 9
inline constexpr s32 kScript = 20;     // the dungeon script request (sub_1C0190)
inline constexpr s32 kRoot = 24;       // the floor's field root
inline constexpr s32 kStratum = 28;    // the stratum title task (Y_Stratum_CreateStratumPartsTask)
inline constexpr s32 kFloorTable = 32; // = gFldDngFloorsData
inline constexpr s32 kFlags = 36;      // the next root's flags (entry.flags | bit 31 when the block set changes)
inline constexpr s32 kKind = 40;       // the floor kind (sub_1BF340; K_FldDungeon_GetFloorKind)
inline constexpr s32 kEpl = 44;        // the floor's EPL "DNG%02d.EPL" and its instance
inline constexpr s32 kEplObj = 48;
inline constexpr s32 kScrMemory = 52;  // the dungeon script copy and size (K_FldDungeon_GetScrMemory / Size)
inline constexpr s32 kScrSize = 56;
inline constexpr s32 kSize = 64;
}  // namespace dng
// The floor table entry (gFldDngFloorsData 0x867F60 + 16 floor; DUNGEONAT.BIN byte for byte).
namespace dngfloor {
inline constexpr u32 kTable = 0x867F60u;
inline constexpr s32 kSize = 16, kMajor = 0, kMinor = 2, kArg4 = 4, kMinCells = 6, kMaxCells = 7, kFlags = 8;
inline constexpr s32 kBlockScript = 12, kEpl = 13;
}  // namespace dngfloor
// The block-entry floors (the stratum title runs first), dword_6833C0[6]: 2, 17, 65, 115, 165, 215.
inline constexpr u32 kBlockEntryFloors = 0x6833C0u;

// --- the field resource record (2,636 bytes, RwMalloc; sub_1B2860) -------------------------------------------------
namespace res {
inline constexpr s32 kFlags = 0;      // bit 0 = a world (collision world inserted in the main world), bit 1 = a
                                      // clone (Tartarus block), bit 29 = no collision mesh
inline constexpr s32 kMajor = 4;      // u16 / u16: the ids parsed from the file name (0xFFFF when not fMMM_NNN)
inline constexpr s32 kMinor = 6;
inline constexpr s32 kCollision = 8;  // the collision world / clump
inline constexpr s32 kWorld = 12;     // the draw world (or the collision clump's atomic list)
inline constexpr s32 kShadow = 16;    // the "per3ShadowCollis" world / clump
inline constexpr s32 kClumpCount = 20;
inline constexpr s32 kClumps = 24;    // [32] draw clumps
inline constexpr s32 kAtomLists = 152;// [32] their atomic lists (sub_1A7570)
inline constexpr s32 kObjCount = 280; // the field objects (24-byte entries, namespace fobj)
inline constexpr s32 kObjs = 284;
inline constexpr s32 kUvAnim = 2588;  // the UV animation dictionary
inline constexpr s32 kScale = 2592;   // 3 floats (the ENV's per-field scale; 1.0 at load)
inline constexpr s32 kHitRequest = 2616;  // the HBN hit file request / its copy
inline constexpr s32 kHitData = 2620;
inline constexpr s32 kFile = 2624;    // the file record (292 bytes: path, +128 the H_Cdvd node, +140 / +144 the
                                      // world requests, +152 / +156 the clump requests, +288 texture dictionary)
inline constexpr s32 kFbnRequest = 2628;  // the NPC placement FBN request / its header
inline constexpr s32 kFbnData = 2632;
inline constexpr s32 kSize = 2636;
}  // namespace res
namespace fobj {
inline constexpr s32 kSize = 24, kType = 0, kFlags = 2, kResId = 4, kFrame = 8, kModel = 12, kEpl = 16, kEplFile = 20;
}  // namespace fobj

// --- FBN NPC placement records (field/data/fMMM_NNN_SSS.FBN; sub_1E2E50 / sub_1E3940 / sub_1E2430 / sub_1E2BD0) ----
namespace fbn {
inline constexpr u32 kMagic = 0x12345678u, kVersion = 0x00010001u;
inline constexpr s32 kHdrMagic = 0, kHdrVersion = 4, kHdrNpcCount = 8, kHdrNpcSize = 12, kHdrPosCount = 16;
inline constexpr s32 kHdrPosSize = 20, kHdrSize = 24;
// NPC record (112 bytes): +0 (runtime) the model handle, +4 u16 model major, +6 u16 model minor ({4, 0xFFFF} = a
// placeholder the schedule tables fill), +8 u16 the resource id (type 3: 0xC00 | n), +10 u8 the controller byte
// (-> resource +480), +11 u8 bit 0 = visible (-> resource +40 bit 31), +12 f32 collision radius, +16 s32 (-> resource
// +484), +32 RwMatrix (64 bytes; the position at +80), +96 u8 resource kind (v1.1; 3 before), +97 u8 (-> resource
// +482), +100 f32 (sub_19C490 / sub_19C320: the shadow size), +104 / +108 the editor's list links.
inline constexpr s32 kNpcSize = 112, kNpcModel = 0, kNpcMajor = 4, kNpcMinor = 6, kNpcResId = 8, kNpcCtl = 10;
inline constexpr s32 kNpcFlags = 11, kNpcRadius = 12, kNpcParam = 16, kNpcMatrix = 32, kNpcPos = 80;
inline constexpr s32 kNpcKind = 96, kNpcByte97 = 97, kNpcShadow = 100, kNpcPrev = 104, kNpcNext = 108;
// Position record (96 bytes): +0 (runtime) the editor's marker task, +16 RwMatrix (the position at +64), +80 u16 the
// resource id (type 8), +84 / +88 the editor's list links.
inline constexpr s32 kPosSize = 96, kPosTask = 0, kPosMatrix = 16, kPosPos = 64, kPosResId = 80, kPosPrev = 84;
inline constexpr s32 kPosNext = 88;
}  // namespace fbn
// The NPC placement slot (36 bytes, sField +4296 [n]): +0 kind (0 the FBN model, 1 a schedule-table entry, 2 a
// social-link entry), +4 the table record, +8 the FBN record index, +16 the social-link list index, +20 / +28 blocks.
namespace npcslot {
inline constexpr s32 kSize = 36, kKind = 0, kRecord = 4, kFbnIndex = 8, kComuIndex = 16, kBlock20 = 20, kBlock28 = 28;
}  // namespace npcslot

// --- the scene record 0x95AFC0 (MT_Scene; *(gp-0x57B0)) -----------------------------------------------------------
namespace scene {
inline constexpr s32 kMajor = 0;    // s32 (-1 = no scene)
inline constexpr s32 kMinor = 4;    // s32
inline constexpr s32 kResMgr = 8;   // the resource manager (resrcMngCreate); the field editor needs it non-zero
inline constexpr s32 kFlags = 12;   // bit 31: take the ids from the first field resource; bit 2: reload the ENV
inline constexpr s32 kEnv = 16;     // the ENV request (sub_1B6100), then the camera file (sub_1D6B10)
inline constexpr s32 kNpcSet = 20;  // s16: the NPC placement set, the FBN's third number
inline constexpr s32 kEnvSub = 22;  // s16: the ENV sub-id
}  // namespace scene

// --- gp-relative globals ($gp = 0x7D2CF0) -------------------------------------------------------------------------
namespace gpv {
inline constexpr s32 kPacRequest = -19348;     // 0x7CE15C: the field's .pac request (the pack cache)
inline constexpr s32 kFpcRequest = -19344;     // 0x7CE160: the field's .fpc (model pack) request
inline constexpr s32 kLoadTime = -19340;       // 0x7CE164: the frame counter at the load start / the load time
inline constexpr s32 kFrameCounter = -20036;   // 0x7CDEAC: the frame counter
inline constexpr s32 kSceneRecord = -22448;    // 0x7CD540: -> the scene record 0x95AFC0
inline constexpr s32 kPhase = -19108;          // 0x7CE24C: the load phase (K_Fld_GetPhase)
inline constexpr s32 kDungeonTask = -19080;    // 0x7CE268: the automatic dungeon task
inline constexpr s32 kDungeonReload = -19076;  // 0x7CE26C: 1 = unload the scene with the root (K_Field_Destroy..)
inline constexpr s32 kFloorObj0 = -19056;      // 0x7CE280: the block object model fobj000
inline constexpr s32 kGenPlaced = -19092;      // 0x7CE25C: blocks placed in this attempt (cell +9; sub_1BB090)
inline constexpr s32 kGenSteps = -19088;       // 0x7CE260: placements in this attempt (abort above 10,000)
inline constexpr s32 kGenFailed = -19084;      // 0x7CE264: 1 = the attempt failed, generate again
inline constexpr s32 kBtlEffPack = -19096;     // 0x7CE258: the btl_eff.pac request
}  // namespace gpv

// --- the field event task's work (K_FldEvent_UpdateFldEventTask; task +60) ------------------------------------------
namespace evt {
inline constexpr s32 kState = 0;       // the 33-state switch (jump table 0x7B6BD0)
inline constexpr s32 kMode = 12;       // the event id / exit record index (state 3: 44 * (+12 & 0x3FF))
inline constexpr s32 kTarget = 36;     // the contacted enemy / the nearest interactable unit
inline constexpr s32 kPacket = 40;     // the 52-byte battle packet (sub_1C7830)
inline constexpr s32 kBattle = 100;    // the battle task (btlStart)
inline constexpr s32 kPauseA = 4;      // 1 = exploring paused (state 1 does nothing)
inline constexpr s32 kPauseB = 8;
inline constexpr s32 kGameOver = 16;   // the game-over latch
inline constexpr s32 kHero = 20;       // the hero's character scene resource (id 1024)
inline constexpr s32 kDoorObj = 24;    // the door object resource of the exit being used
inline constexpr s32 kNpc = 28;        // the NPC being talked to (sub_1C74C0)
inline constexpr s32 kNpcPose = 32;    // its pose before the talk
inline constexpr s32 kDrawCmd = 92;    // the draw-command task (sub_1CD710)
inline constexpr s32 kScript = 96;     // the running script task
inline constexpr s32 kCamp = 104;      // the camp menu task (H_Camp_CreateDrawTask)
inline constexpr s32 kPrompt = 224;    // 1 = show the prompt icon above the hero
inline constexpr s32 kAreaName = 228;  // the area name shown by the last field hit
inline constexpr s32 kWeapon = 236;    // the held weapon type
inline constexpr s32 kWeaponItem = 240;// the weapon item id (camp menu: model reload test)
inline constexpr s32 kCameraMode = 244;// the camera mode saved during the swing
inline constexpr s32 kCountdown = 248; // count-down A (0 -> sub_4533E0(0))
inline constexpr s32 kTalkCooldown = 252;
inline constexpr s32 kSwing = 256;     // the swing record (0x7CE294 + 24 weapon type)
}  // namespace evt
// The exit / field-hit record (44 bytes, sField +4424 [n]; field/table/hMMM_NNN.bin).
namespace exitrec {
inline constexpr s32 kSize = 44;
inline constexpr s32 kFlags = 0;        // [3] s32 flag ids that must all be set (-1 = none)
inline constexpr s32 kKind = 12;        // u8: 1 = the hero must face the side +32 (sub_1C6200)
inline constexpr s32 kConfirm = 13;     // u8: 1 = needs the confirm button (and shows the prompt)
inline constexpr s32 kAreaName = 14;    // u16: the area name index (0 = keep)
inline constexpr s32 kProcedure = 16;   // u16: the field script procedure; 0xFFFF = a door to another field
inline constexpr s32 kNextMajor = 18;   // u16 / u16 / u16: the door's next field
inline constexpr s32 kNextMinor = 20;
inline constexpr s32 kNextEntry = 22;
inline constexpr s32 kDoorObj = 24;     // u16: the door object to animate (0 = none)
inline constexpr s32 kDoorAnim = 26;    // s16: its animation
inline constexpr s32 kSound = 28;       // s32: the door sound (-1 = none)
inline constexpr s32 kSide = 32;        // s32: 0 the hit's first corner, 1..4 an edge midpoint
}  // namespace exitrec

}  // namespace f4

// --- the register-ABI bodies (arguments in $a0.., the result in $v0) ------------------------------------------------

void sub_1B00C0(EEContext& ctx);  // 0x1B00C0
void sub_1B02C0(EEContext& ctx);  // 0x1B02C0
void sub_1B0710(EEContext& ctx);  // 0x1B0710
void sub_1B07D0(EEContext& ctx);  // 0x1B07D0
void sub_1B0840(EEContext& ctx);  // 0x1B0840
void sub_1B0870(EEContext& ctx);  // 0x1B0870
void sub_1B08D0(EEContext& ctx);  // 0x1B08D0
void sub_1B0920(EEContext& ctx);  // 0x1B0920
void sub_1B0950(EEContext& ctx);  // 0x1B0950
void sub_1B09B0(EEContext& ctx);  // 0x1B09B0
void sub_1B09F0(EEContext& ctx);  // 0x1B09F0
void sub_1B0A20(EEContext& ctx);  // 0x1B0A20
void sub_1B10F0(EEContext& ctx);  // 0x1B10F0
void sub_1B2780(EEContext& ctx);  // 0x1B2780
void sub_1B2860(EEContext& ctx);  // 0x1B2860
void sub_1B2B30(EEContext& ctx);  // 0x1B2B30
void sub_1B2B90(EEContext& ctx);  // 0x1B2B90
void sub_1B2F00(EEContext& ctx);  // 0x1B2F00
void sub_1B32F0(EEContext& ctx);  // 0x1B32F0
void sub_1B3480(EEContext& ctx);  // 0x1B3480
void sub_1B39E0(EEContext& ctx);  // 0x1B39E0
void sub_1B3C90(EEContext& ctx);  // 0x1B3C90
void sub_1B4E00(EEContext& ctx);  // 0x1B4E00
void sub_1B5200(EEContext& ctx);  // 0x1B5200
void sub_1B5380(EEContext& ctx);  // 0x1B5380
void sub_1B5610(EEContext& ctx);  // 0x1B5610
void sub_1B56F0(EEContext& ctx);  // 0x1B56F0
void sub_1B5850(EEContext& ctx);  // 0x1B5850
void sub_1B5880(EEContext& ctx);  // 0x1B5880
void sub_1B58B0(EEContext& ctx);  // 0x1B58B0
void sub_1B5950(EEContext& ctx);  // 0x1B5950
void sub_1B5990(EEContext& ctx);  // 0x1B5990
void sub_1B59C0(EEContext& ctx);  // 0x1B59C0
void sub_1B5A00(EEContext& ctx);  // 0x1B5A00
void sub_1B5A30(EEContext& ctx);  // 0x1B5A30
void sub_1B5AE0(EEContext& ctx);  // 0x1B5AE0
void sub_1B5B50(EEContext& ctx);  // 0x1B5B50
void sub_1B5DF0(EEContext& ctx);  // 0x1B5DF0
void sub_1B5E30(EEContext& ctx);  // 0x1B5E30
void sub_1B5E60(EEContext& ctx);  // 0x1B5E60
void sub_1B5E90(EEContext& ctx);  // 0x1B5E90
void sub_1B6060(EEContext& ctx);  // 0x1B6060
void sub_1B60A0(EEContext& ctx);  // 0x1B60A0
void sub_1B60D0(EEContext& ctx);  // 0x1B60D0
void sub_1B6100(EEContext& ctx);  // 0x1B6100
void sub_1B61F0(EEContext& ctx);  // 0x1B61F0
void sub_1B75E0(EEContext& ctx);  // 0x1B75E0
void sub_1B76B0(EEContext& ctx);  // 0x1B76B0
void sub_1B7700(EEContext& ctx);  // 0x1B7700
void K_Seq_CallField(EEContext& ctx);  // 0x1B77B0
void K_Seq_ExitField(EEContext& ctx);  // 0x1B7850
void K_Seq_CallFieldEvent(EEContext& ctx);  // 0x1B7900
void K_Seq_ExitFieldEvent(EEContext& ctx);  // 0x1B79A0
void K_Seq_CallDungeon(EEContext& ctx);  // 0x1B7A50
void K_Seq_ExitDungeon(EEContext& ctx);  // 0x1B7A90
void K_Data_LoadFldMainScript(EEContext& ctx);  // 0x1B7B10
void sub_1B7BB0(EEContext& ctx);  // 0x1B7BB0
void sub_1B7C40(EEContext& ctx);  // 0x1B7C40
void sub_1B7D00(EEContext& ctx);  // 0x1B7D00
void sub_1B7D60(EEContext& ctx);  // 0x1B7D60
void sub_1B7DC0(EEContext& ctx);  // 0x1B7DC0
void sub_1B7E30(EEContext& ctx);  // 0x1B7E30
void sub_1B7E60(EEContext& ctx);  // 0x1B7E60
void sub_1B8000(EEContext& ctx);  // 0x1B8000
void sub_1B8030(EEContext& ctx);  // 0x1B8030
void sub_1B80C0(EEContext& ctx);  // 0x1B80C0
void sub_1B8160(EEContext& ctx);  // 0x1B8160
void sub_1B81F0(EEContext& ctx);  // 0x1B81F0
void sub_1B83F0(EEContext& ctx);  // 0x1B83F0
void sub_1B85A0(EEContext& ctx);  // 0x1B85A0
void sub_1B8600(EEContext& ctx);  // 0x1B8600
void sub_1B8680(EEContext& ctx);  // 0x1B8680
void sub_1B8710(EEContext& ctx);  // 0x1B8710
void sub_1B8870(EEContext& ctx);  // 0x1B8870
void sub_1B88D0(EEContext& ctx);  // 0x1B88D0
void sub_1B8960(EEContext& ctx);  // 0x1B8960
void sub_1B8AE0(EEContext& ctx);  // 0x1B8AE0
void sub_1B8B40(EEContext& ctx);  // 0x1B8B40
void sub_1B8C40(EEContext& ctx);  // 0x1B8C40
void sub_1B8CF0(EEContext& ctx);  // 0x1B8CF0
void sub_1B8D60(EEContext& ctx);  // 0x1B8D60
void sub_1B8DB0(EEContext& ctx);  // 0x1B8DB0
void sub_1B8FD0(EEContext& ctx);  // 0x1B8FD0
void K_Field_Init(EEContext& ctx);  // 0x1B90F0
void sub_1B9140(EEContext& ctx);  // 0x1B9140
void K_Field_UpdateFieldRootTask(EEContext& ctx);  // 0x1B9480
void K_Field_DestroyFieldRootTask(EEContext& ctx);  // 0x1BA3D0
void k_Field_CreateFieldRootTask(EEContext& ctx);  // 0x1BA5F0
void K_Field_SetShouldShutdown(EEContext& ctx);  // 0x1BA880
void sub_1BA8D0(EEContext& ctx);  // 0x1BA8D0
void sub_1BAA50(EEContext& ctx);  // 0x1BAA50
void sub_1BAAA0(EEContext& ctx);  // 0x1BAAA0
void sub_1BB300(EEContext& ctx);  // 0x1BB300
void sub_1BCAC0(EEContext& ctx);  // 0x1BCAC0
void sub_1BD450(EEContext& ctx);  // 0x1BD450
void sub_1BD8C0(EEContext& ctx);  // 0x1BD8C0
void sub_1BF220(EEContext& ctx);  // 0x1BF220
void sub_1BF340(EEContext& ctx);  // 0x1BF340
void K_FldDungeon_UpdateTask(EEContext& ctx);  // 0x1BF570
void sub_1BFAF0(EEContext& ctx);  // 0x1BFAF0
void K_FldDungeon_CreateTask(EEContext& ctx);  // 0x1BFBC0
void sub_1BFCC0(EEContext& ctx);  // 0x1BFCC0
void K_FldEvent_UpdateFldEventTask(EEContext& ctx);  // 0x1C8620
void sub_1DC6F0(EEContext& ctx);  // 0x1DC6F0
void sub_1DC8E0(EEContext& ctx);  // 0x1DC8E0
void sub_1DC910(EEContext& ctx);  // 0x1DC910
void sub_1DCA10(EEContext& ctx);  // 0x1DCA10
void sub_1DCB60(EEContext& ctx);  // 0x1DCB60
void sub_1DD430(EEContext& ctx);  // 0x1DD430
void sub_1DD460(EEContext& ctx);  // 0x1DD460
void sub_1DD530(EEContext& ctx);  // 0x1DD530
void sub_1DD600(EEContext& ctx);  // 0x1DD600
void sub_1DD8E0(EEContext& ctx);  // 0x1DD8E0
void sub_1DDB30(EEContext& ctx);  // 0x1DDB30
void sub_1DDCA0(EEContext& ctx);  // 0x1DDCA0
void sub_1DDD30(EEContext& ctx);  // 0x1DDD30
void sub_1DDE00(EEContext& ctx);  // 0x1DDE00
void sub_1DE630(EEContext& ctx);  // 0x1DE630
void sub_1DED40(EEContext& ctx);  // 0x1DED40
void sub_1DF450(EEContext& ctx);  // 0x1DF450
void sub_1DFA70(EEContext& ctx);  // 0x1DFA70
void sub_1E1850(EEContext& ctx);  // 0x1E1850
void sub_1E2300(EEContext& ctx);  // 0x1E2300
void sub_1E2370(EEContext& ctx);  // 0x1E2370
void sub_1E2430(EEContext& ctx);  // 0x1E2430
void sub_1E2850(EEContext& ctx);  // 0x1E2850
void sub_1E28A0(EEContext& ctx);  // 0x1E28A0
void sub_1E2930(EEContext& ctx);  // 0x1E2930
void sub_1E2A20(EEContext& ctx);  // 0x1E2A20
void sub_1E2A70(EEContext& ctx);  // 0x1E2A70
void sub_1E2B10(EEContext& ctx);  // 0x1E2B10
void sub_1E2BD0(EEContext& ctx);  // 0x1E2BD0
void sub_1E2DA0(EEContext& ctx);  // 0x1E2DA0
void sub_1E2E50(EEContext& ctx);  // 0x1E2E50
void sub_1E3940(EEContext& ctx);  // 0x1E3940
void sub_1E3F10(EEContext& ctx);  // 0x1E3F10
void sub_1E4B10(EEContext& ctx);  // 0x1E4B10
void sub_1E4B40(EEContext& ctx);  // 0x1E4B40
void sub_1E4BC0(EEContext& ctx);  // 0x1E4BC0
void sub_1E5820(EEContext& ctx);  // 0x1E5820
void sub_1E5850(EEContext& ctx);  // 0x1E5850
void sub_1E58D0(EEContext& ctx);  // 0x1E58D0
void sub_1E6000(EEContext& ctx);  // 0x1E6000
void sub_1E6030(EEContext& ctx);  // 0x1E6030
void sub_1E60B0(EEContext& ctx);  // 0x1E60B0
void sub_1E6A40(EEContext& ctx);  // 0x1E6A40
void sub_1E6A70(EEContext& ctx);  // 0x1E6A70
void sub_1E6AF0(EEContext& ctx);  // 0x1E6AF0
void sub_1E6CB0(EEContext& ctx);  // 0x1E6CB0
void sub_1E6D50(EEContext& ctx);  // 0x1E6D50
void sub_1E6EA0(EEContext& ctx);  // 0x1E6EA0
void sub_1E7200(EEContext& ctx);  // 0x1E7200
void sub_1E7290(EEContext& ctx);  // 0x1E7290
void sub_1E7410(EEContext& ctx);  // 0x1E7410
void sub_1E7470(EEContext& ctx);  // 0x1E7470
void sub_1E74E0(EEContext& ctx);  // 0x1E74E0
void sub_1E7520(EEContext& ctx);  // 0x1E7520
void sub_1E7540(EEContext& ctx);  // 0x1E7540
void sub_1E75B0(EEContext& ctx);  // 0x1E75B0
void sub_1E7720(EEContext& ctx);  // 0x1E7720
void sub_1E78C0(EEContext& ctx);  // 0x1E78C0
void sub_1E7A60(EEContext& ctx);  // 0x1E7A60
void sub_1E7AA0(EEContext& ctx);  // 0x1E7AA0
void sub_1E7B10(EEContext& ctx);  // 0x1E7B10
void sub_1E7C20(EEContext& ctx);  // 0x1E7C20
void sub_1E7CE0(EEContext& ctx);  // 0x1E7CE0
void sub_1E7DE0(EEContext& ctx);  // 0x1E7DE0
void sub_1E7E30(EEContext& ctx);  // 0x1E7E30
void sub_1E7F90(EEContext& ctx);  // 0x1E7F90

}  // namespace p3fes::game
