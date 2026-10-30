// Phase 5 slice field6: the rest of the field band 0x1B0000-0x1FFFFF (docs/ANALYSIS/26_field.md; the battle-UI part
// docs/ANALYSIS/27_unmapped_bands.md section 3) -- what field3 / field4 / tartarus2 / shuffle / battle_ui3 left:
//
//   game/src/field/field6_fldrc.cpp    k_fldrc.c's loaders: the dungeon scripts, the btl_eff.pac EPLs, the field exit
//                                      ("hit") table, the party units' finish step, the "trans wall CTL" task and its
//                                      "RMD fade CTL" / "atomic fade CTL" helpers (the camera-occluder fades);
//   game/src/field/field6_comm.cpp     k_command.c: 41 field COMM handlers of the script VM (sScrCommandTable);
//   game/src/field/field6_misc.cpp     the field screen filter draw (FILTER.FLD), eff_afpack.c's after-effect packs;
//   game/src/battle/field6_result.cpp  br_root.c / br_data.c (the battle result root, the level-up, persona shifts and
//                                      drops), bp_root.c (the battle panel root), bcm_main.c (the command menu);
//   game/src/battle/field6_shuffle.cpp sfl_root.c / sfl_result.c (Shuffle Time's root task, the deal, the result).
//
// The bodies are p3fes_handgen's: register for register and block for block as the recompiled bodies (frame, spills,
// $ra links, cycle charges, check points; game/include/p3fes/game/hg_cpu.h). The readability pass (role blocks, block
// comments, named offsets) adds no statement and moves none: tests/game/test_field6_*.cpp pair every body with its
// recompiled body, and the slice's check script confirms that the files, comments dropped and names replaced by their
// values, equal the generator's output statement for statement.
//
// Names: functions keep their symbols/functions.json names; a proposed name is given in brackets (ADR-0009: from the
// instructions, the strings, the K_Assert file names, the callers and the snapshots; also symbols/deltas/field6.sym).
//
// ===================================================================================================================
// The field exit ("hit") table: field/table/hMMM_NNN.bin (for the scene editor and the multiplayer server)
// ===================================================================================================================
//
// What it is. Every field has an action table for its hit volumes. The volumes themselves (geometry) are the scene's
// type-13 "field hit" resources built from the HBN file (field/data/fMMM_NNN.HBN, sub_1E5570 / field4); the event task
// (K_FldEvent_UpdateFldEventTask, state 1 / 3) takes the touched hit's id, `id & 0x3FF`, as an index into this table
// (asserting `index < count`, k_event.c 1878) and acts on the record. So collision / trigger data for a server is the
// pair (HBN volumes, this table): the volume says where, the record says what.
//
// Where it comes from. K_Fldrc_RequestFieldHitTableFile(major, minor) is called by the field root (state 4):
//   the field's .pac resident  -> 1, nothing requested: the table is the pack member "h%03d_%03d.bin";
//   else                       -> H_Cdvd_Request("field/table/h%03d_%03d.bin") when H_Cdvd_FileExists says so, else 0.
//   (A "no field" test, major == 0xFFFF -> 0, is in the code but dead: it compares the major masked to 16 bits with
//   -1, "andi s0, a0, 0xFFFF" against "li v0, -1" -- a C u16-versus--1 comparison the compiler kept -- so 0xFFFF asks
//   for "h65535_NNN.bin" like any other major; the test checks both bodies do.)
// On disc every field ships its table inside DATA/FIELD/PACK/FMMM_NNN.PAC as the member hMMM_NNN.bin (208 tables,
// 867 records in this ISO; there is no loose DATA/FIELD/TABLE/H*.BIN). sub_1C7F20(request) then installs it:
//   request == 0               -> 1 (nothing to do);
//   the .pac resident          -> H_Cdvd_CacheFindFile("field/pack/h%03d_%03d.bin" of the scene record's ids) and,
//                                 when found, the copy below from the cache (no H_Cdvd node to destroy); always 1;
//   else                       -> 0 while H_Cdvd_IsFileLoaded(request) is 0; then the copy and H_Cdvd_Destroy; 1.
//   The copy: sub_1C80C0 frees the old table, sField +4420 = size / 44 (divu: a trailing partial record is dropped --
//   PAC members are padded, so 199 of the 208 tables end in 4..28 spare bytes), sField +4424 = RwCalloc(1, size,
//   0x40000) (the slot 0x960184), memcpy of all `size` bytes.
//
// The record (44 bytes, little-endian; namespace hitrec below; f4::exitrec names the same fields for field4's code):
//   +0  s32[3] flags      game flags that must all be set for the record to act (-1 = unused slot; 703 of 867
//                         records have none)
//   +12 u8   kind         1 = the hero must face the side named at +32 (sub_1C6200), 0 = any direction
//   +13 u8   prompt       nonzero = the action waits for the confirm button (pad 0x40) and shows the prompt icon
//                         above the hero (event work +224 = 1); 0 = acts on contact. Values seen 0, 2..7.
//   +14 u16  area name    the area-name index shown on entry (0 = keep the current one; event work +228)
//   +16 u16  procedure    the field script procedure to run (scrCreateTaskFromScriptMemory on the field's BF, sField
//                         +4168 / +4172); 0xFFFF = a door to another field (157 records)
//   +18 u16  next major   the door's destination: sub_1BAAA0(root, major, minor, entry) -> root work +76 / +78 / +80,
//   +20 u16  next minor   then root state 17 = adminiChangeSeq(2, ...). 0 / 0 = a door that only animates (66 of
//                         the 157 doors); 24 script records carry ids too, which the event task does not read
//   +22 u16  next entry
//   +24 u16  door object  the scene object resource to animate (0 = none; 10241.., i.e. 0x2801.. = type 10 objects)
//   +26 s16  door anim    its animation
//   +28 s32  sound        the door sound (-1 = none)
//   +32 s32  side         0 = the hit's first corner, 1..4 = an edge midpoint (where the hero is placed / faces)
//   +36 u32, +40 u32      not read by the event task (0 in 866 / 867 records)
// The test (test_field6_fldrc.cpp) parses every table of the PACs on the host with this layout, installs real tables
// through both sub_1C7F20 bodies and checks count, copy and fields.
//
// ===================================================================================================================
// The other records of this slice (offsets decimal, as the instructions give them)
// ===================================================================================================================
//
// * The H_Cdvd request node (hcdvd.h): +12 state (4 = loaded), +272 the data, +280 its size (namespace node).
// * The trans-wall work (524 bytes, "trans wall CTL" task, sub_1C1F30 / sub_1C0D70 / sub_1C1E20): +0 state (1 = stop:
//   the update returns -1), +4.. a 512-byte scratch, +516 the unit (camera target) whose frame is tested. Each frame
//   the update casts two rays from the camera eye +/- 100 x the camera's right vector towards the target (its sphere
//   centre lifted by radius + 60, sub_1AD940 / K_FldFrame_CtlGetSphereCollisRadius): field objects of scene type 10
//   that block a ray fade out (alpha byte +3 of the model colour, sub_318B00, 255 -> 0 in 5 steps) and come back after
//   12 clear frames (10 steps, 255); the atomics of the type-12 Tartarus blocks fade the same way through their
//   material alpha (+24: 1.0 visible, 0.0 hidden; +32 the fade task, +36 the clear-frame counter). Field 24/50 is
//   excluded. A fade is a 20-byte "RMD fade CTL" / "atomic fade CTL" task {+4 target, +8 steps, +12 the start value}.
// * The party unit gFldUnitsPc 0x8717A0 [4] x 448 bytes (field3_units.cpp): +72 the DatUnit, +80 the model, +84 the
//   scene resource, +360 its placement, +364 think task, +368 mover, +384 the "badstat CTL" task, +414 u16[5] the
//   weapon models' ids, +424 u16 the character id, +432 / +436 / +440 the reserve-script request / copy / size.
// * The screen filter (sub_1D4610): 0x7CE298 the FILTER.FLD data (292-byte entries: +0 the blend mode 0..3, then 7 x
//   8 cells of 36 bytes with four RGBA corners), 0x7CE29C a brightness offset added to every alpha, 0x7CE2A0 the
//   target entry, 0x7CE2A4 the shown entry, 0x7CE2A8 the blend 0..1 (f32), 0x7CE2AC the blend time (frames, f32);
//   0x872240 [7][8] the Im2D quads (256 bytes each: four 64-byte vertices, the colour floats at +32..+44).
// * The after-effect packs (eff_afpack.c): two lists 0x7CE2C8 (tail) / 0x7CE2CC (head), linked by +24 prev / +28
//   next; a pack: +0 flags (2 update once, 4 draw once, 8 every frame), +4 the pack data (+4 s16 the effect count,
//   +32 the owner model), +8 76-byte effect states, +12 {atomic, frame} pairs, +16 32-byte effect controls.
// * The battle result work (br_root.c; 42,912 bytes, RwMalloc; gp-18968 0x7CE2D8; the "battle result" task +60):
//   +0 flags (0x2 Shuffle Time follows, 0x4 a persona learned skills, 0x8 the hero levelled up, 0x20 party members
//   levelled up, 0x40 skip one frame, 0x2000 the result may start, 0x10000 the level-up quad drawn, 0x40000 a
//   level-milestone flag was raised, 0x80000 / 0x100000 one-shot set-ups, 0x200000 the BGM is the result's),
//   +4 resource requests pending (0x1 shuffle ground, 0x2 / 0x4 the result resources), +8 the same, finished,
//   +12 the state (0..12, jump table 0x7B6E10), +16 / +20 / +56 the sub-states of states 8 / 12 / 9, +24..+36 the
//   four draw tasks, +40 the "pressed" latch of state 7, +60 the message window in use (0 none, 1 / 2 / 3),
//   +148 the shuffle root task, +176.. the battle packet's unit list, +188 / +192 the hero's level before / after,
//   +212 u16[] the members that levelled up (count +236), +268 u16[] the drop list (count +276), +280 / +284 units /
//   dead units, +320 u16[] the persona's new skills (count +336), +340 the index shown, +42624 the page to show
//   (0 none, 1 skills, 2 hero level, 3 members), +10832 / +10836 / +10840 exp / money / bonus, +10844 = 100.
// * The battle panel root (bp_root.c; 217,136 bytes; the task in gp-18956 0x7CE2E4): +0 flags, +8 the draw task, then
//   the sub-modules' works at +32, +30688, +48960, +72112, +114816 .. +216848 (each init / destroy pair in bp_root).
// * The command menu (bcm_main.c; gp-18952 0x7CE2E8): +0 flags, +30624 the disabled commands (bit 0 ATTACK, 1 SKILL,
//   2 ITEM, 3 PERSONA, 4 ESCAPE, 5 WAIT, 6 OPERATION -- the printf names), +36 the analyse command (flag 390).
// * Shuffle Time (shuffle.h has the records): the root work gp-18964 (172,576 bytes) +4 flags, +8 the state (jump
//   table 0x7B6E50), +12 / +16 the draw tasks; the result work gp-18960: +0 flags, +4 the result step (jump table
//   0x7B6EF0), +8 the mode (0 one card, 1 several), +92 the 1,648-byte entries.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace f6 {

// (The bodies name these through namespace aliases -- task::, node::, ... -- since f0..f31 are register names there.)
namespace task {
inline constexpr s32 kWork = 60;  // KwlnTask +0x3C: the work pointer every update / destroy callback reads
}  // namespace task

// --- the H_Cdvd request node ----------------------------------------------------------------------------------------
namespace node {
inline constexpr s32 kState = 12;  // 4 = loaded
inline constexpr s32 kData = 272;  // the file bytes (64-byte aligned heap block)
inline constexpr s32 kSize = 280;  // the file size
}  // namespace node

// --- the exit ("hit") record, 44 bytes (field/table/hMMM_NNN.bin; sField +4424 [sField +4420]) ------------------------
namespace hitrec {
inline constexpr s32 kSize = 44;
inline constexpr s32 kFlags = 0;       // s32[3], -1 = unused
inline constexpr s32 kKind = 12;       // u8: 1 = face the side +32
inline constexpr s32 kPrompt = 13;     // u8: nonzero = wait for confirm, show the prompt
inline constexpr s32 kAreaName = 14;   // u16
inline constexpr s32 kProcedure = 16;  // u16: 0xFFFF = a door
inline constexpr s32 kNextMajor = 18;  // u16
inline constexpr s32 kNextMinor = 20;  // u16
inline constexpr s32 kNextEntry = 22;  // u16
inline constexpr s32 kDoorObj = 24;    // u16
inline constexpr s32 kDoorAnim = 26;   // s16
inline constexpr s32 kSound = 28;      // s32
inline constexpr s32 kSide = 32;       // s32 0..4
inline constexpr u32 kDoor = 0xFFFFu;  // kProcedure value of a door
}  // namespace hitrec

// --- the trans-wall work (524 bytes) and its fade tasks (20 bytes) -------------------------------------------------
namespace wall {
inline constexpr s32 kState = 0;     // 1 = stop
inline constexpr s32 kTarget = 516;  // the unit whose frame is the ray target
inline constexpr s32 kSize = 524;
}  // namespace wall
namespace fade {
inline constexpr s32 kTarget = 4;  // the scene object (RMD) or the atomic (block)
inline constexpr s32 kSteps = 8;   // 5 = fade out, 10 = fade back, 1 = restore at once
inline constexpr s32 kStart = 12;  // f32 start value (0, 1.0 or 255.0)
inline constexpr s32 kSize = 20;
}  // namespace fade
// Scene resources as the fades and the COMM handlers use them (MT_Scene, 26_field.md 3.1).
namespace sres {
inline constexpr s32 kId = 0;          // u16: type << 10 | index (0x3FF)
inline constexpr s32 kFlags = 40;      // bit 1 = alive / visible
inline constexpr s32 kNext = 248;      // the next resource of the same type
inline constexpr s32 kModel = 260;     // type 10 (field object, an "RMD"): the model
inline constexpr s32 kFade = 264;      // type 10: the running fade task
inline constexpr s32 kClear = 268;     // type 10: frames without a blocking ray
inline constexpr s32 kCharModel = 296; // types 1 / 3 (characters / NPCs): the model
inline constexpr s32 kBlock = 352;     // type 12 (Tartarus block): the block's atomic table
inline constexpr s32 kFrame = 480;     // types 1 / 3: the frame controller (K_FldFrame_*)
inline constexpr s32 kFrame3 = 488;    // type 3: the NPC's frame controller
inline constexpr s32 kShadow = 492;    // type 3: the blob-shadow model
inline constexpr s32 kShadowObj = 496; // type 3: the shadow object (sub_19C320)
inline constexpr s32 kTypeShift = 10;
}  // namespace sres

// --- gp-relative globals of this slice ($gp = 0x7D2CF0; field4.h f4::gpv has the field root's) ----------------------
namespace gp6 {
inline constexpr s32 kParty = -19064;       // 0x7CE278: the party re-create step of COMM 0x1D6 (0, 1, 2)
inline constexpr s32 kDarkHourTimer = -19072;  // 0x7CE270: COMM 0x1E8's frame counter (90 frames)
inline constexpr s32 kDarkHourState = -19068;  // 0x7CE274: COMM 0x1E7 / 0x1E8: 1 = the transition is running
inline constexpr s32 kChest = -19052;       // 0x7CE284: the special chest's box (COMM 0x0E7)
inline constexpr s32 kShadowModel = -19156; // 0x7CE21C: the blob-shadow model template
inline constexpr s32 kFilterData = -19032;  // 0x7CE298: FILTER.FLD (292-byte entries)
inline constexpr s32 kFilterBright = -19028;   // 0x7CE29C: added to every alpha, clamped 0..255
inline constexpr s32 kFilterTarget = -19024;   // 0x7CE2A0: the entry faded in (0 = no filter)
inline constexpr s32 kFilterShown = -19020;    // 0x7CE2A4: the entry faded from
inline constexpr s32 kFilterBlend = -19016;    // 0x7CE2A8: f32 0..1
inline constexpr s32 kFilterTime = -19012;     // 0x7CE2AC: f32 frames
inline constexpr s32 kFilterScale = -27176;    // 0x7CC2C8: every colour byte x this / 255 unless it is 255
inline constexpr s32 kAfTail = -18984;      // 0x7CE2C8: eff_afpack.c list tail
inline constexpr s32 kAfHead = -18980;      // 0x7CE2CC: eff_afpack.c list head
inline constexpr s32 kBrRoot = -18968;      // 0x7CE2D8: br_root.c work
inline constexpr s32 kSflRoot = -18964;     // 0x7CE2DC: sfl_root.c work
inline constexpr s32 kSflResult = -18960;   // 0x7CE2E0: sfl_result.c work
inline constexpr s32 kBpRoot = -18956;      // 0x7CE2E4: the "battle panel" task
inline constexpr s32 kBcm = -18952;         // 0x7CE2E8: bcm_main.c work
inline constexpr s32 kBrData = -18640;      // 0x7CE420: br_data.c tables (+0 personas 14-byte rows, +16 skill
                                            //   lists, +28 the shift list, +32 the fallback list, +36 the drop list)
}  // namespace gp6

// --- the battle result work (br_root.c) -------------------------------------------------------------------------------
namespace br {
inline constexpr s32 kFlags = 0;
inline constexpr s32 kLoading = 4;
inline constexpr s32 kLoaded = 8;
inline constexpr s32 kState = 12;
inline constexpr s32 kStep8 = 16;
inline constexpr s32 kStep12 = 20;
inline constexpr s32 kStep9 = 56;
inline constexpr s32 kMsgWin = 60;
inline constexpr s32 kShuffle = 148;
inline constexpr s32 kLvBefore = 188;
inline constexpr s32 kLvAfter = 192;
inline constexpr s32 kPage = 42624;
inline constexpr s32 kSize = 42912;
}  // namespace br

// --- the Shuffle Time result work (sfl_result.c, gp 0x7CE2E0; shuffle.h has the entry layout) ----------------------
namespace sflr {
inline constexpr s32 kCount = 13276;       // entries (1,648 bytes each from +92), at most 8
inline constexpr s32 kListA = 13280;       // u16 persona ids (count +13312): the stock-full list
inline constexpr s32 kListB = 13296;       // u16 persona ids (count +13316): the new personas
inline constexpr s32 kCountA = 13312;
inline constexpr s32 kCountB = 13316;
inline constexpr s32 kReward = 13320;      // the reward page's index
inline constexpr s32 kShown = 13324;       // the persona being shown
inline constexpr s32 kPosA = 13328;        // the list A index shown
inline constexpr s32 kPosB = 13332;        // the list B index shown
inline constexpr s32 kKind0Count = 13336;  // arcana entries (indices at +28 [8])
inline constexpr s32 kKind1Count = 13340;  // persona entries (indices at +60 [8])
inline constexpr s32 kScriptRun = 13504;
inline constexpr s32 kScript = 13508;      // the result script (sub_35BD20 of the BF 0x684850)
inline constexpr s32 kFadeDir = 13512;     // 0 fade in, 1 fade out (flag 0x100)
inline constexpr s32 kFadeAlpha = 13516;   // 256 x t
inline constexpr s32 kFadeFrame = 13520;   // 0..30
inline constexpr s32 kMoveMode = 13524;    // the reward card move (flag 0x200)
inline constexpr s32 kMoveA = 13528;
inline constexpr s32 kMoveB = 13532;
inline constexpr s32 kEffect = 13536;      // the reward effect object (sub_1F9C60)
}  // namespace sflr

}  // namespace f6

}  // namespace p3fes::game
