// The battle code, fourth pass (slice battle4; docs/ANALYSIS/21_battle.md): the still-recompiled functions of the
// battle bands 0x240000-0x311310 that the battle replay and the Tartarus climb reach (measured with a first-call
// probe), whose callees are hand-written (or a K_Assert, a libc / RW-math leaf, a heap / sprintf / H_Cdvd stand-in).
// game/src/battle/battle4.cpp; the bodies come from p3fes_handgen (register ABI: arguments in $a0.., the result in
// $v0), with the record offsets named below (and battle3.h's b3:: records reused) and each function's role given.
// Names: functions.json's in code, ours in brackets in the comments (ADR-0009); the confirmed record fields go to
// tools/ours/types/deltas/battle4.json.
//
// Groups:
//   * the battle panel modules of 0x241910-0x25D710: each source file (bi_main.c, bpc_main.c, bpm_main.c, bp_tut.c,
//     bpo_main.c, bpd_main.c, bp_dialog.c, bp_rush.c -- the K_Assert strings) keeps one work record behind a $gp slot
//     (kGpBiWork..kGpBpRushWork): a register function stores it, an unregister clears it, getters / setters K_Assert
//     that it is set; the battle info markers (16 slots of 3,920 bytes, quads drawn through the Im2D slot 0x96009C),
//     the unit-panel entries of bpc (2,624 bytes each, slide in / out), the message window of bpm, the dialog;
//   * the unit geometry: centre / head / cell-centre points through the unit's rotation (sub_4BE1E0), a group's mean
//     point and extent (sub_280870, the camera shots' framing), the screen projection (sub_2D20A0, 640 x 448 with a
//     guard band), ground-plane distances and the quaternion angle;
//   * the colour fades, the effect instances / handles / effect-object pools, the battle effect archive loader
//     (snd_benc/btleff.bin, 60 handles at gBtl +3108), the skill effect and sound file names;
//   * the boss rules: btlBossSetup (the rule flags, AI rows and AI_EVENT procedures of encounters 416..436 and 456),
//     the boss sound paks, the boss AI event scripts (sub_2FD2E0), the boss reach;
//   * the enemy / party AI of btlAICommand.c: the think step (sub_2C70D0: AI script or AICALC row), the AI scripts
//     ("AI_PC_%03X_%03X"), the 'any unit' condition and its predicates, the element / weakness filters with the
//     analysed-enemy records (gBtl +2656), the target pick, the attack / heal / recovery skill and item pickers;
//   * the grid path finder: a visibility graph over the units' grid boxes (gBtl +716 list, four 304-byte corner nodes
//     each, the field corners +720, start +1936 / goal +2240) searched by lowest cost (sub_2D48C0);
//   * the navigator's opening and status lines, the party voice lines, the victory spoils (experience, drops, the rare
//     and special flags) of a defeated enemy.
//
// THE BATTLE STATE A CO-OP SERVER WOULD OWN (additions to battle3.h's list)
//   * gBtl's spoils block (kExp +3068, kDrops +3040 {u16 item, u32 count}[3], kDropCount +3064, kSpoilFlags +3036,
//     kSpecialDrops +3104): filled when each enemy dies (sub_2D7560) and read by the result screen -- server state.
//   * the boss block (+2836..+2952: rule flags in kFlags / kRules +16, the AI rows, the AI_EVENT procedure indices, the
//     per-kind event bookkeeping +2860 / +2872, kBossMode +2948): set once at the battle start (btlBossSetup) from
//     the encounter id; the event scripts it starts are battle logic (they choose boss actions) and must run on the
//     server.
//   * the analysed-enemy records (+2656, 12 x {s8 side, u16 base id}) behind the AI's "does the party know this
//     weakness" test: shared knowledge, server state.
//   * the AI's command block (an action's +56: targets, count +106, kind +108, skill +110, item +112, the script task
//     +132) and the AI think step: the server decides every enemy (and party-AI) command; the AI scripts run as script
//     tasks under the battle task (kTask +3352).
//   * the path finder's graph (+716 boxes, +720..+2552 nodes / lists) is derived from the unit positions: a server can
//     recompute it, clients only need the resulting walk.
//   * the battle panel works, the voice / navigator lines and the fades are presentation (client side); the navigator
//     and voice pickers draw from the shared random stream (datCalcRand), like battle3's presentation draws.

#pragma once

#include "p3fes/ee_context.h"
#include "p3fes/game/battle3.h"

namespace p3fes::game {

namespace b4 {

// --- $gp slots (offset from $gp 0x7D2CF0) ---------------------------------------------------------------------
inline constexpr s32 kGpBiWork = -18900;      // 0x7CE31C the battle info work (bi_main.c; 16 slots of 3,920 bytes)
inline constexpr s32 kGpBossAiTbl = -18484;   // 0x7CE4BC the boss AI table (1,044-byte rows)
inline constexpr s32 kGpBossScript = -18464;  // 0x7CE4D0 the boss AI script
inline constexpr s32 kGpBpDialogWork = -18824;// 0x7CE368 the battle dialog work (bp_dialog.c)
inline constexpr s32 kGpBpRushWork = -18820;  // 0x7CE36C the battle rush work (bp_rush.c)
inline constexpr s32 kGpBpTutWork = -18860;   // 0x7CE344 the battle tutorial work (bp_tut.c)
inline constexpr s32 kGpBpWork328 = -18888;   // 0x7CE328 a battle panel work (registered by sub_249240)
inline constexpr s32 kGpBpWork32C = -18884;   // 0x7CE32C a battle panel work (registered by sub_24A6C0)
inline constexpr s32 kGpBpWork348 = -18856;   // 0x7CE348 a battle panel work (registered by sub_251A70)
inline constexpr s32 kGpBpcWork = -18896;     // 0x7CE320 the battle panel command work (bpc_main.c)
inline constexpr s32 kGpBpdWork = -18848;     // 0x7CE350 the bpd work (bpd_main.c)
inline constexpr s32 kGpBpmWork = -18892;     // 0x7CE324 the battle panel message work (bpm_main.c)
inline constexpr s32 kGpBpoWork = -18852;     // 0x7CE34C the bpo work (bpo_main.c)
inline constexpr s32 kGpEnemyTbl = -18656;    // 0x7CE410 gBtlEnemyTbl (62-byte rows)
inline constexpr s32 kGpPartyAiScript = -18468;// 0x7CE4CC the party AI script

// --- gBtl additions (battle3.h b3::gbtl has the rest) ------------------------------------------------------------------
namespace gbtl4 {
inline constexpr s32 kRules = 16;           // u32: boss rule bits set by btlBossSetup (0x1 / 0x2 / 0x8 / 0x10 every boss, 0x20 encounter 429, 0x40 encounter 456, 0x80 some bosses)
inline constexpr s32 kTestFlags = 20;       // u32: debug / test bits: 0x1 the skill effect file is battle/BTL_TEST.BED, 0x4000000 the effect files load one by one
inline constexpr s32 kUnitTail1 = 344;      // u32: tail of side 1 (enemies)
inline constexpr s32 kFieldNodes = 720;     // path node[4] (304 bytes each): the field corners of the path graph
inline constexpr s32 kPathStart = 1936;     // path node: the start of a path query (+8 / +12 the point)
inline constexpr s32 kPathGoal = 2240;      // path node: the goal of a path query
inline constexpr s32 kPathOpen = 2544;      // u32: the open list of the path search (nodes linked by +36, cost +32)
inline constexpr s32 kPathClosed = 2548;    // u32: the closed list of the path search
inline constexpr s32 kLastStatusLine = 2608;  // s32: the navigator's last status-report line (not repeated)
inline constexpr s32 kEnemiesLeft = 2612;   // s16: the enemy count the navigator last reported
inline constexpr s32 kAnalysis = 2656;      // {s8 side, u16 enemy base id}[12]: the analysed-enemy records (sub_2E3120)
inline constexpr s32 kBossActEndFn = 2824;  // fn: a pending boss callback run at the action end (sub_2E4330)
inline constexpr s32 kBossActEndArg = 2832; // u32: its argument
inline constexpr s32 kBossBlock = 2836;     // the boss block (116 bytes, cleared by btlBossSetup); +0 the boss sound pak request (sub_2F9710)
inline constexpr s32 kBossAiRows = 2840;    // u32: the boss AI rows (*(0x7CE4BC) + 1,044 * index)
inline constexpr s32 kBossEvtStart = 2844;  // s32: the boss script's AI_EVENT_%03X_BTLSTART procedure (-1 none)
inline constexpr s32 kBossEvtActStart = 2848;  // s32: AI_EVENT_%03X_ACTSTART
inline constexpr s32 kBossEvtActEnd = 2852; // s32: AI_EVENT_%03X_ACTEND
inline constexpr s32 kBossEvtOwner = 2860;  // u32[3]: per event kind, the action serial (+8) the event last ran for
inline constexpr s32 kBossEvtTurn = 2872;   // u32[3]: per event kind, the turns taken (+32) of the action it last ran for
inline constexpr s32 kBossMode = 2948;      // u16: 0, 1 (encounter 456), 2 (encounter 429)
inline constexpr s32 kSetupMembers = 2988;  // u32[4]: the setup block's party genus pointers (+4 the DatUnit)
inline constexpr s32 kSpoilFlags = 3036;    // u32: bit 1 a rare enemy was defeated
inline constexpr s32 kDrops = 3040;         // {u16 item, u32 count}[3] (stride 8): the item drops collected
inline constexpr s32 kDropCount = 3064;     // u32: drop slots used
inline constexpr s32 kExp = 3068;           // u32: the experience collected
inline constexpr s32 kSpecialDrops = 3104;  // u32: bits 1 / 2 / 4 / 8 for the enemies with DatUnit ids 193..196
inline constexpr s32 kFxHandles = 3108;     // u32[60]: the battle effect archive's handles (sub_2BC480)
inline constexpr s32 kFxCommon = 3248;      // u32: the effect handle of the defeat fade (sub_299800)
inline constexpr s32 kFxArchiveReq = 3348;  // u32: the H_Cdvd request of snd_benc/btleff.bin
inline constexpr s32 kTask = 3352;          // u32: the battle task (parent of the script tasks; +32 its priority)
}  // namespace gbtl4

// --- btlAction additions (b3::act) -------------------------------------------------------------------------------------
namespace act4 {
inline constexpr s32 kFidget = 36;          // s32: the idle fidget timer (-1: draw a new wait)
inline constexpr s32 kLastCmdKind = 124;    // u16: the last command's kind (1 attack, 2 skill)
inline constexpr s32 kLastCmdId = 126;      // u16: its skill id
inline constexpr s32 kCmdScript = 104;      // u8: 1 when an AI script decides the command (the command block +48)
inline constexpr s32 kStealItem = 128;      // u16: an item the action stole
inline constexpr s32 kStealChance = 130;    // u8: its drop chance (%)
inline constexpr s32 kCmdTask = 132;        // u32: the AI script task (the command block +76)
inline constexpr s32 kGuardKind = 220;      // u16: nonzero when the guard command has its own motion
}  // namespace act4

// --- btlUnit additions (b3::unit) --------------------------------------------------------------------------------------
namespace unit4 {
inline constexpr s32 kPos = 4;              // f32[3]: the unit position
inline constexpr s32 kShakeOff = 16;        // f32[3]: the shake offset (sub_2849A0)
inline constexpr s32 kRot = 28;             // the rotation the offsets go through (sub_4BE1E0)
inline constexpr s32 kCentreOff = 128;      // f32[3]: the centre offset (times kScale)
inline constexpr s32 kHeight = 140;         // f32: the height (times kScale)
inline constexpr s32 kCellX = 148;          // s16: the grid cell x (25 * x - 1750)
inline constexpr s32 kCellZ = 150;          // s16: the grid cell z
}  // namespace unit4

// --- DatUnit additions (b3::dat) ---------------------------------------------------------------------------------------
namespace dat4 {
inline constexpr s32 kTactic = 16;          // u8: a party member's AI tactic (the second number of AI_PC_%03X_%03X; 10 reset to 1 at death, 9 no voice lines)
}  // namespace dat4

// --- unit packet 271's data block (+0 the unit) ------------------------------------------------------------------------
namespace pdu4 {
inline constexpr s32 kModelMajor = 4;       // u16: the wanted model (major id) of unit packet 271
inline constexpr s32 kModelMinor = 6;       // u16: the wanted model (minor id)
inline constexpr s32 kModelFlags = 8;       // u32: 0x10 do not request the model file
inline constexpr s32 kModelReq = 12;        // u32: the model file request
}  // namespace pdu4

// --- a battle info slot (*kGpBiWork + 3,920 * k, k < 16) ---------------------------------------------------------------
namespace bi {
inline constexpr s32 kFlags = 0;            // u32 (per slot): 0x1 live, 0x2 digits reset, 0x4 draw the under-quads, 0x8 hidden, 0x10 kind set, 0x100 / 0x200 the digit strips
inline constexpr s32 kKind = 4;             // u32 (per slot): 0..3, the marker kind (sub_242320)
inline constexpr s32 kQuads = 16;           // 64-word quads (per slot): the main quad +16, the under-quads +272 / +528
inline constexpr s32 kDigitsTimer = 784;    // u32 (per slot): cleared with the digits
inline constexpr s32 kOwner = 788;          // u32 (per slot): the owner word (sub_242A50 / sub_242AE0)
inline constexpr s32 kDigitsA = 800;        // quad[5] (per slot): the first digit strip
inline constexpr s32 kDigitsB = 2096;       // quad[5] (per slot): the second digit strip
inline constexpr s32 kDigitPosA = 3392;     // the first strip's position / colour record (sub_21EAE0 / sub_21D950 / sub_21EAC0)
inline constexpr s32 kDigitPosB = 3648;     // the second strip's record
inline constexpr s32 kSlotSize = 3920;      // bytes per slot
inline constexpr s32 kSlots = 16;           // slots
}  // namespace bi

// --- the bpc work (*kGpBpcWork) ----------------------------------------------------------------------------------------
namespace bpc {
inline constexpr s32 kFlags = 0;            // u32: 0x1 shown, 0x2 font line open, 0x20 an entry is sliding
inline constexpr s32 kMode = 4;             // u32: 0 / 1 the party and the enemies, 2 the enemy panel
inline constexpr s32 kUidCount = 8;         // s32: entries of kUids (at most 10)
inline constexpr s32 kEntryCount = 12;      // s32: entries of kEntries
inline constexpr s32 kUids = 16;            // u32[10]: the unit uids listed
inline constexpr s32 kEntries = 64;         // entry[kEntryCount] of 2,624 bytes (bpce::)
inline constexpr s32 kFontLine = 27840;     // u32: the font line
inline constexpr s32 kWord29392 = 29392;    // u16
inline constexpr s32 kFrame = 29396;        // s32: 0..59 frame counter
inline constexpr s32 kEntrySize = 2624;     // bytes per entry
inline constexpr s32 kMaxUids = 10;         // entries of kUids
}  // namespace bpc

// --- a bpc entry (bpc::kEntries + 2,624 * k) ---------------------------------------------------------------------------
namespace bpce {
inline constexpr s32 kFlags = 0;            // u32: 0x1 / 0x2 the skill marks, 0x10 sliding in, 0x20 sliding out, 0x40 off screen, 0x80 not analysed, 0x200 a hit flash, 0x400 the first listed unit
inline constexpr s32 kUid = 8;              // u32: the unit uid
inline constexpr s32 kSlide = 1808;         // s32: the slide frame (0..10)
inline constexpr s32 kMarkIndex = 2592;     // s32: which of the three analysis marks is lit (0 the listed unit, 1 the same enemy kind, 2 another)
inline constexpr s32 kMarkTimers = 2596;    // s32[3]: the analysis marks' fade counters (0..10)
inline constexpr s32 kHp = 2608;            // u32: the unit's HP
inline constexpr s32 kMaxHp = 2612;         // u32: its max HP
inline constexpr s32 kScreenPos = 2616;     // f32[2]: the projected centre (y + 20)
}  // namespace bpce

// --- the bpm work (*kGpBpmWork) ----------------------------------------------------------------------------------------
namespace bpm {
inline constexpr s32 kFlags = 0;            // u32: 0x1 open, 0x2
inline constexpr s32 kFontLine = 4;         // u32: the message's font line
inline constexpr s32 kFrame = 8;            // s32
inline constexpr s32 kQuads = 16;           // quads (+16 / +272 texture 67, +528 68, +784 0, +1040 / +1296 66)
}  // namespace bpm

// --- the battle dialog work (*kGpBpDialogWork) -------------------------------------------------------------------------
namespace dlg {
inline constexpr s32 kFlags = 0;            // u32: 0x1 open, 0x2 answered, 0x4 font lines live, 0x8 close requested
inline constexpr s32 kLines = 4;            // u32[3]: the three font lines
inline constexpr s32 kAnswer = 16;          // s32: the answer
inline constexpr s32 kQuads = 32;           // the window quads (+32 / +288 / +544, +816 / +1072)
inline constexpr s32 kTexA = 800;           // s32: the texture of the first quads
inline constexpr s32 kTexB = 804;           // s32: the texture of the third quad
}  // namespace dlg

// --- the bpo work (*kGpBpoWork) ----------------------------------------------------------------------------------------
namespace bpo {
inline constexpr s32 kFlags = 0;            // u32: 0x1 active, 0x2 quads dirty
inline constexpr s32 kFrame = 4;            // s32: 0..30
inline constexpr s32 kKind = 8;             // s32: 0 / 1 (texture 57 / 58)
}  // namespace bpo

// --- the bpd work (*kGpBpdWork) ----------------------------------------------------------------------------------------
namespace bpd {
inline constexpr s32 kFlags = 0;            // u32: 0x1 the markers are shown
}  // namespace bpd

// --- the bp_rush work (*kGpBpRushWork) ---------------------------------------------------------------------------------
namespace rush {
inline constexpr s32 kFlags = 0;            // u32: 0x10 set / cleared by sub_25D6C0 / sub_25D710
}  // namespace rush

// --- a path node of the grid path finder (304 bytes; sub_2D2F50 / sub_2D32B0 / sub_2D48C0) -----------------------------
namespace path {
inline constexpr s32 kPoint = 8;            // f32 x, z: the node's point on the ground plane
inline constexpr s32 kActive = 20;          // f32: > 0 when the node exists
inline constexpr s32 kClearance = 24;       // f32: the clearance it was built with
inline constexpr s32 kCost = 32;            // f32: the search cost
inline constexpr s32 kNextOpen = 36;        // u32: the next node of the open / closed list
inline constexpr s32 kNeighbours = 48;      // u32[32]: the visible nodes, 0 ended
inline constexpr s32 kDistances = 176;      // f32[32]: their distances
inline constexpr s32 kNodeSize = 304;       // bytes per node
inline constexpr s32 kBoxNodes = 8;         // a unit's grid record (btlUnit + 1276): its four corner nodes from +8
inline constexpr s32 kBoxNext = 1228;       // the grid record's link (btlUnit + 2504, b3::unit::kGridNext)
}  // namespace path

}  // namespace b4

// --- the functions (register ABI: arguments in $a0.., the result in $v0) ----------------------------------------
// 0x241910 [biDrawMarkers] Draw of the battle info markers (bi_main.c, work *$gp 0x7CE31C, 16 slots of 3,920 bytes): RW render
//   states (z test / write off, no culling), then for every live slot (flag 1, not 8) with a kind set (flag 0x10) the
//   sprite quads of its kind (0 / 1 / 2 / 3: textures 10/11, 18/19, 28..30, 34; flag 4 adds the two 64-word under-quads
//   at +272 / +528), sub_2BF9B0, then the 5-quad digit strips +800 / +2096 of slots with flag 0x100 / 0x200 (texture
//   46). Quads go through the Im2D slot 0x96009C (two triangles each).
void sub_241910(EEContext& ctx);
// 0x242260 [biAllocSlot] Allocates a free battle info slot (first of the 16 without flag 1; K_Assert line 1411 when none),
//   sets its flags to 1 and returns it.
void sub_242260(EEContext& ctx);
// 0x242320 [biSetSlotKind] Sets a battle info slot's kind (a1 0..3) and builds its quads from the panel texture set
//   (sub_21C3F0(1)): kind 0 textures 11 / 10 x2, 1 textures 19 / 18 x2, 2 textures 30 / 29 / 28, 3 texture 34; flag
//   0x10.
void sub_242320(EEContext& ctx);
// 0x242540 [biResetSlotDigits] Resets a battle info slot's two digit strips (+3392 / +3648: position 0, colour {255, 0, 0,
//   255}, sub_21EAC0), clears +784 and sets flag 2.
void sub_242540(EEContext& ctx);
// 0x242840 [biSetDigits] Writes a number into a strip of digit quads: sprintf("%d"-style format 0x7CC464), asserts it fits a1
//   digits (line 1605), then sub_2428F0 for each digit (256-byte quads).
void sub_242840(EEContext& ctx);
// 0x2428F0 [biSetDigitQuad] Sets one digit quad's texture: panel texture 46 + digit (sub_21CCA0 / sub_21D3B0).
void sub_2428F0(EEContext& ctx);
// 0x242950 [biGetDigitsWidth] Width of a number drawn with the digit font: sprintf of a0, length 1..5 asserted (lines 1638 /
//   1639); returns (len - 1) * 28 + the texture-46 width (+12) as a float in $f0.
void sub_242950(EEContext& ctx);
// 0x242A30 Sets flag 4 of a battle info slot (draw the under-quads).
void sub_242A30(EEContext& ctx);
// 0x242A50 Stores a battle info slot's owner word (+788).
void sub_242A50(EEContext& ctx);
// 0x242A60 [biHasFreeSlot] Whether a battle info slot is free (any of the 16 without flag 1).
void sub_242A60(EEContext& ctx);
// 0x242AE0 [biFindOwner] Whether a live battle info slot belongs to an owner (+788 == a0).
void sub_242AE0(EEContext& ctx);
// 0x242B80 [biGetUnitMarkerPos] Screen position of a unit's marker: the unit with uid a0 (sub_289030), its head point
//   (sub_2806D0), projected (sub_2D20A0); y + 14. 0 when the unit or the projection fails.
void sub_242B80(EEContext& ctx);
// 0x242C40 [bpcRegister] Registers the battle panel command work (bpc_main.c): clears +0 / +8 / +29396 and stores it in $gp
//   slot 0x7CE320.
void sub_242C40(EEContext& ctx);
// 0x242C60 [bpcRelease] Releases the bpc work: its font line (+27840) through sub_3B0170 when flag 2, then clears the slot.
void sub_242C60(EEContext& ctx);
// 0x244120 [bpcAddUnit] Appends a unit uid to the bpc work's list (+16, count +8, at most 10: K_Assert line 593).
void sub_244120(EEContext& ctx);
// 0x244E10 [bpcGetFirstUnit] The first uid of the bpc work's list (+16); asserts flag 2 (line 993).
void sub_244E10(EEContext& ctx);
// 0x2453D0 Stores a halfword at the bpc work's +29392.
void sub_2453D0(EEContext& ctx);
// 0x245420 [bpcBuildEntry] Builds a bpc entry for the unit with uid a1: clears its flags, stores the uid (+8), HP / max HP
//   (+2608 / +2612), the projected centre (+2616, flag 0x40 when off screen, +20 on y), flag 0x400 for the work's first
//   uid; in mode 2 (the enemy panel) the analysis mark 0x80 for enemies not seen yet with the three marker timers
//   +2596; in mode 0 flag 1 when sub_300E90(unit, the work's skill +29392) and flag 2 for a known null / repel / drain
//   affinity to that skill; then the entry's quads (panel textures 1..4, 44, 69, 55 / 57 / 8 / 61).
void sub_245420(EEContext& ctx);
// 0x245910 Starts a bpc entry's slide-in (flag 0x10): reverses a running slide-out (flag 0x20: frame +1808 = 10 - frame,
//   clears 0x20 / 0x200) or restarts it at 0.
void sub_245910(EEContext& ctx);
// 0x245970 Starts a bpc entry's slide-out (flag 0x20), the mirror of sub_245910.
void sub_245970(EEContext& ctx);
// 0x245A00 [bpcBuildEntries] Rebuilds the bpc entries (sub_245420) and their count (+12): mode 2 the enemies in the battle
//   with a placed action, modes 0 / 1 the party then the enemies in the battle (unit flag 8), from the side lists'
//   tails.
void sub_245A00(EEContext& ctx);
// 0x245BF0 [bpcFindEntry] The bpc entry (2,624 bytes from +64) of a unit uid (+8); K_Assert line 1375 when absent.
void sub_245BF0(EEContext& ctx);
// 0x248490 Registers the battle panel message work (bpm_main.c, $gp slot 0x7CE324).
void sub_248490(EEContext& ctx);
// 0x2484A0 Unregisters the bpm work, releasing its font line first when open (flag 1).
void sub_2484A0(EEContext& ctx);
// 0x248620 Update of the bpm message window: width from the font line, slide and alpha.
void sub_248620(EEContext& ctx);
// 0x248BB0 Draw of the bpm message window.
void sub_248BB0(EEContext& ctx);
// 0x248FC0 [bpmOpen] Opens the bpm message: its font line a0 at (1600, 800), white, kept at +4; quads +16 / +272 (texture 67),
//   +528 (68), +784 (0), +1040 / +1296 (66); +8 = 0, flag 1 on, 2 off.
void sub_248FC0(EEContext& ctx);
// 0x249180 [bpmClose] Closes the bpm message (releases the font line, clears flag 1) when open.
void sub_249180(EEContext& ctx);
// 0x2491F0 Releases the bpm message's font line (+4) through sub_3B0170.
void sub_2491F0(EEContext& ctx);
// 0x249240 Registers the battle panel work of $gp slot 0x7CE328.
void sub_249240(EEContext& ctx);
// 0x24A6C0 Registers the battle panel work of $gp slot 0x7CE32C.
void sub_24A6C0(EEContext& ctx);
// 0x24A6D0 Clears $gp slot 0x7CE32C.
void sub_24A6D0(EEContext& ctx);
// 0x251050 Registers the battle tutorial work (bp_tut.c, $gp slot 0x7CE344).
void sub_251050(EEContext& ctx);
// 0x251060 Unregisters the bp_tut work (K_Assert line 73 when still active).
void sub_251060(EEContext& ctx);
// 0x251A70 Registers the battle panel work of $gp slot 0x7CE348.
void sub_251A70(EEContext& ctx);
// 0x251F20 Registers the battle panel work of $gp slot 0x7CE34C (bpo_main.c).
void sub_251F20(EEContext& ctx);
// 0x251F30 Clears $gp slot 0x7CE34C.
void sub_251F30(EEContext& ctx);
// 0x252060 [bpoUpdate] Update of the bpo work: while active (flag 1) counts +4 up to 30 (then clears flag 1) and rebuilds its
//   quads (sub_252340).
void sub_252060(EEContext& ctx);
// 0x252340 [bpoBuildQuads] Builds the bpo (one-more / down banner) quads for the current frame: texture 57 / 58 by +8, the
//   frame count +4 drives the slide and the sinf / cosf wobble, the alpha of +528 from the fade.
void sub_252340(EEContext& ctx);
// 0x252E60 Registers the battle panel work of $gp slot 0x7CE350 (bpd_main.c): clears +0 / +2900.
void sub_252E60(EEContext& ctx);
// 0x252E80 Clears $gp slot 0x7CE350.
void sub_252E80(EEContext& ctx);
// 0x252E90 Sets flag 1 of the bpd work.
void sub_252E90(EEContext& ctx);
// 0x252EE0 Clears flag 1 of the bpd work.
void sub_252EE0(EEContext& ctx);
// 0x252F30 [bpdDraw] Draw of the bpd work: for each enemy unit, its head point (sub_2807A0), projected, and a marker quad
//   (sinf bob) by its bad status.
void sub_252F30(EEContext& ctx);
// 0x25BDF0 Registers the battle dialog work (bp_dialog.c, $gp slot 0x7CE368).
void sub_25BDF0(EEContext& ctx);
// 0x25BE00 Unregisters the bp_dialog work, releasing its font line (+4) when open (flag 1).
void sub_25BE00(EEContext& ctx);
// 0x25C110 Sets flag 8 of the open bp_dialog (K_Assert line 167 when not open).
void sub_25C110(EEContext& ctx);
// 0x25C190 The bp_dialog's flag 2.
void sub_25C190(EEContext& ctx);
// 0x25C1E0 The bp_dialog's word +16 (the answer).
void sub_25C1E0(EEContext& ctx);
// 0x25C9C0 [bpDialogDraw] Draw of the bp_dialog when open: render states, the window quads +32 / +288 (texture +800), +544
//   (texture +804), +816 (89), +1072 (90) and the three font lines +4 / +8 / +12.
void sub_25C9C0(EEContext& ctx);
// 0x25CD30 Releases the bp_dialog's three font lines and clears flag 4.
void sub_25CD30(EEContext& ctx);
// 0x25CEB0 Lines of a font line chain: frFontChainCountLines of the last node (+36 links).
void sub_25CEB0(EEContext& ctx);
// 0x25CF00 Registers the battle rush work (bp_rush.c, $gp slot 0x7CE36C).
void sub_25CF00(EEContext& ctx);
// 0x25CF10 Clears $gp slot 0x7CE36C.
void sub_25CF10(EEContext& ctx);
// 0x25D6C0 Sets flag 0x10 of the bp_rush work.
void sub_25D6C0(EEContext& ctx);
// 0x25D710 Clears flag 0x10 of the bp_rush work.
void sub_25D710(EEContext& ctx);
// 0x25FB60 [brItemGetCellUv] brItem: the UV rectangle of a sprite cell: the cell a1 of the record list (+388, 128-byte cells:
//   +84 / +88 / +92 / +96 the pixel box, +20 the texture index into +260), divided by the texture's width (+12) and
//   height (+16), into a2 = {u0, v0, u1, v1}.
void sub_25FB60(EEContext& ctx);
// 0x280050 [btlUnitGetCellCentre] A unit's centre on its grid cell: the offset +128..+136 scaled by +44 and rotated by the
//   unit matrix (+28, sub_4BE1E0), plus (25 * cell x - 1750, +8, 25 * cell z - 1750) from the s16 cells +148 / +150.
void sub_280050(EEContext& ctx);
// 0x280130 [btlUnitGetBonePoint] A unit's point of a model bone: the s16 offset of row 0 of its point table (sub_288DA0),
//   scaled by +44, rotated by the unit's rotation (+28) and added to its position.
void sub_280130(EEContext& ctx);
// 0x280580 [btlUnitGetCentre] A unit's centre: the model's bone point (sub_318ED0) when it has a model (+152 bit 1) and that
//   succeeds, else the offset +128 scaled and rotated plus the position +4..+12.
void sub_280580(EEContext& ctx);
// 0x2806D0 [btlUnitGetHeadPoint] A unit's head point: the rotated offset plus the position, y raised by height (+140) * scale
//   * the float 0x7CB0CC.
void sub_2806D0(EEContext& ctx);
// 0x2807A0 [btlUnitGetQuarterPoint] As sub_2806D0 with the factor 0.25.
void sub_2807A0(EEContext& ctx);
// 0x280870 [btlUnitGroupBounds] Centre and extent of a group of units: over the side mask a0 (bits 0..3) every unit in the
//   battle (+156 flag 8) without the flags a1, positions summed (cell centres when a5 bit 0); returns the last unit;
//   writes the mean to a2, the highest top (y + height / 2 * scale) to a3, the lowest to a4 when given.
void sub_280870(EEContext& ctx);
// 0x2812D0 [btlUnitGetApproachDistance] Approach distance of a unit's motion towards a target (returned in $f20 / $f0): the
//   motion row (sub_283510) frames +6 * scale, plus the boss reach sub_2FC5D0 when it gives one (else the target's
//   radius +144 * its scale), plus the unit's own offset +136 * scale.
void sub_2812D0(EEContext& ctx);
// 0x283C70 [btlUnitGetAttackHitFrame] Hit frame of an attack motion (4 / 5 / 6 = the three attack hits): enemies only motion
//   4..6 -> column 0 of the enemy MODEL row (+26), party units by weapon type (hero +24 of the weapon row) or party row
//   (+24), Koromaru's table 0x7CC518; 1 for other motions.
void sub_283C70(EEContext& ctx);
// 0x283E40 [btlUnitGetAttackEndFrame] As sub_283C70 for the second column (+28 / +26): the attack's end frame; 0 for other
//   motions.
void sub_283E40(EEContext& ctx);
// 0x284DF0 Hold callback of packet 259: the unit's busy count +1.
void sub_284DF0(EEContext& ctx);
// 0x284F30 Release callback of packet 259: busy -1.
void sub_284F30(EEContext& ctx);
// 0x284F50 [btlUnitPktCreate259] Creates unit packet 259 (16 bytes: unit, u16 a1, f32 f12, u16 a2) with the callbacks
//   sub_284DF0 / sub_284E10 / sub_284F30.
void sub_284F50(EEContext& ctx);
// 0x284FE0 [btlUnitPktHoldModel] Hold callback of unit packet 271: busy +1; keeps the unit's model when it matches the wanted
//   (major, minor) pair (+212 / +214), else frees it (sub_3174E0), then takes a loaded model (sub_316910 / sub_317450:
//   model flags 1 | 2) or requests its file (sub_31D530 name, H_Cdvd_Request, unless data flag 0x10).
void sub_284FE0(EEContext& ctx);
// 0x2890A0 [btlUnitCompareDepth] Comparison of two units by camera distance (a qsort callback): |unit1 - camera| - |unit2 -
//   camera| as an int, positions from the units' frames (+296, sub_318B60) and the camera frame (sub_198590 +4,
//   sub_4CB2F0).
void sub_2890A0(EEContext& ctx);
// 0x289860 [btlActionIdleFidget] The idle fidget timer of an action's unit: a random wait 120..359 frames, then (unit visible,
//   not down / ailing / low HP / dead, motion row < 4) plays motion 16 through sub_284200 and restarts; 1 while it may
//   fidget.
void sub_289860(EEContext& ctx);
// 0x28CE50 [btlActionUpdateStateThink] Action state AI THINK (update): runs the AI wait (sub_2C7250 / sub_2C70D0 on the
//   action's +56 record) and, once decided, marks the action ready (+24 bit 1; bit 0x4000 for a boss attack under the
//   boss rules) and goes to state 12.
void sub_28CE50(EEContext& ctx);
// 0x28D560 Action state init (all-out attack join): sub_2DC5E0, then +1156 = 1, +1160 = 0.
void sub_28D560(EEContext& ctx);
// 0x28E7F0 Action state init: walks to the target unless close (75) or the effect request is pending, then states 15 / 16 / 18
//   by the command kind.
void sub_28E7F0(EEContext& ctx);
// 0x296320 Action state init for the commands 7 / 8 / 11 (guard / analyse / wait): for 7 the guard packets (camera, effect,
//   motion, voice); then the action-done packet and state 25 (one more pending) or 30.
void sub_296320(EEContext& ctx);
// 0x299520 Action state init: dead or the hero's own action -> state 1; else walks back to its place when farther than 75.
void sub_299520(EEContext& ctx);
// 0x299800 Action state (DEAD init): enemy -> spoils (sub_2D7560), the fade-out packets; party -> clears the effects.
void sub_299800(EEContext& ctx);
// 0x29EA50 Address of gBtl +548.
void sub_29EA50(EEContext& ctx);
// 0x29F150 [btlFadeUpdateScale] Update of the colour-fade packet: while the scene runs (gBtl flags 2 and 0x2000000) lerps the
//   two scene colours (sub_19FD40 / sub_19FD70) from the values taken on frame 0 to start * scale (+0..+28) over +96
//   frames; done (1) at the end or when the fades are off.
void sub_29F150(EEContext& ctx);
// 0x29F760 [btlFadeUpdateToBtl] As sub_29F150 towards gBtl's fade colours A / B (+404 / +420) over +32 frames.
void sub_29F760(EEContext& ctx);
// 0x2B1020 Camera shot callback: sub_2B0280(camera, 0, 0).
void sub_2B1020(EEContext& ctx);
// 0x2B4DB0 Camera shot: frames the whole party (sub_280870 of side mask 3) from the fixed direction 0x697880 / 0x697890.
void sub_2B4DB0(EEContext& ctx);
// 0x2B4FD0 Camera shot callback: sub_2B4DB0.
void sub_2B4FD0(EEContext& ctx);
// 0x2B5600 Camera shot callback: the target from sub_2ADD10, applied with sub_2A2170.
void sub_2B5600(EEContext& ctx);
// 0x2B93E0 [btlFxCreateInstance] Creates an effect instance record (RwMalloc 92 + 4 * count): the EFFECT bank a0, entry a1
//   (788-byte rows from +8, count +16), the callbacks a2 / a3, user a4; +16 = -1; entry 1 rolls +20 = datCalcRand(100).
void sub_2B93E0(EEContext& ctx);
// 0x2BAA20 [btlFxPktHoldFile] Hold callback of an effect-file packet: handle use count +1586 + 1 (re-binds on the second use
//   with flag 8), requests the file unless flag 1, marks the handle loading (+1584 bit 0).
void sub_2BAA20(EEContext& ctx);
// 0x2BAAD0 [btlFxPktUpdateFile] Update of the effect-file packet: requests the file if needed; once loaded binds it
//   (sub_2B90D0), destroys the request, marks the handle loaded (bit 1), drops a use and frees the handle (slot
//   0x96017C) on the last one.
void sub_2BAAD0(EEContext& ctx);
// 0x2BB6F0 [btlFxGetBedName] Skill effect file name: "battle/BTL_TEST.BED" in test mode (gBtl +20 bit 0), else "%s%03X.BED"
//   with "skill/" and the skill id.
void sub_2BB6F0(EEContext& ctx);
// 0x2BB7D0 [btlFxAllocObjects] Allocates the effect-object array of a unit: 48 records of 36 bytes (u16 0x200, +4 -1, +8 20)
//   linked at the head of gBtl's effect-object list (+400; +28 prev, +32 next).
void sub_2BB7D0(EEContext& ctx);
// 0x2BBC00 [btlFxAllocGroup] Allocates an effect-object group (24 bytes: +4 a0, +16 / +20 -1) with one effect object linked
//   into gBtl's list.
void sub_2BBC00(EEContext& ctx);
// 0x2BC420 Release callback of the battle effect archive packet: destroys the request (gBtl +3348) unless the test mode bit
//   0x4000000.
void sub_2BC420(EEContext& ctx);
// 0x2BC480 [btlFxLoadArchive] Update of the battle effect archive packet: loads "snd_benc/btleff.bin" (or, in test mode, 60
//   single files read synchronously) and binds its 60 entries as effect handles (sub_2B8F90(2) + sub_2B96E0) at gBtl
//   +3108; sets gBtl flag 0x40000.
void sub_2BC480(EEContext& ctx);
// 0x2BD5F0 Update of the skill-name banner packet: while names are shown (gBtl flag 0x200) shows the skill's name (sub_171110
//   -> sub_1FE9B0) on the first frame, done after 45 frames; at once otherwise.
void sub_2BD5F0(EEContext& ctx);
// 0x2BD6F0 Update of the result pop-up packet: shows the message of table 0x696DCC[+4] once, then waits 45 frames.
void sub_2BD6F0(EEContext& ctx);
// 0x2BED10 Closes the open "battle_command_calc" task's menu: in the test mode (gBtl +20 bit 0x2000000) state 3 -> 6, else the
//   panel close call (sub_1FE430 for an item command 4, else sub_1FDEC0) and state 2.
void sub_2BED10(EEContext& ctx);
// 0x2BF3F0 Creates the "battle_command_calc" / "battle_command_draw" tasks for an action's command menu and sets the panel's
//   menu items by the unit's state (ailments 0x80060 / 0x80274, sub_2C1CE0, action flag 0x400).
void btlCommand_CreateBattleCommandCalcTasks(EEContext& ctx);
// 0x2C0070 The target cursor's camera / pad handling (gPadFlags) over the AI target record.
void sub_2C0070(EEContext& ctx);
// 0x2C1080 [btlAIAnyUnit] AI condition over the battle's combatants: whether any active, placed action of the side mask a2
//   passes the filters a4 (bit 0 downed, bit 1 not shielded against the skill element by the effect states 17 / 18,
//   bits 2-3 a weakness the AI may know: sub_2E3350 / sub_17B260) and the status mask a3, and satisfies the predicate
//   a5 (called through $t2 with the action and a1).
void sub_2C1080(EEContext& ctx);
// 0x2C1710 AI predicate: the action's unit has the bad status a1 (datCalcChkBadStatus).
void sub_2C1710(EEContext& ctx);
// 0x2C17B0 AI condition: any combatant of the given sides with the given status (sub_2C1080 with the predicate sub_2C1710).
void sub_2C17B0(EEContext& ctx);
// 0x2C1F60 AI condition: any combatant weak to the element (sub_2C1080 with the predicate sub_2C1E10).
void sub_2C1F60(EEContext& ctx);
// 0x2C22D0 AI predicate: the action's last command was a skill or attack (+124 kind 1 / 2) with the id a1 (+126).
void sub_2C22D0(EEContext& ctx);
// 0x2C2B20 [btlAICanUseSkill] Whether a unit can use a skill now: not silenced / blocked (status mask 0x80274), knows it, and
//   sub_3086F0 says it is affordable; K_Assert line 1128 for an id >= 624.
void sub_2C2B20(EEContext& ctx);
// 0x2C2BE0 AI condition: any combatant that resists the element (sub_2C1080 with the predicate sub_2C1ED0).
void sub_2C2BE0(EEContext& ctx);
// 0x2C2D00 [btlAIHasSkillOfElement] Whether the unit has a usable skill (sub_2C2B20 rules) of the element a1, the normal
//   attack counting as its own element.
void sub_2C2D00(EEContext& ctx);
// 0x2C2ED0 [btlAIElementUsable] Whether an element may be used against a unit: enemies whose weakness the party has not
//   analysed always pass; else not when shielded (a2 == 1 and effect states 17 / 18), not against a physical-immune
//   enemy (DatUnit flag 0x200) or a party unit with skills 544..546, and only when the affinity has no null / repel /
//   drain bits (0x7000000).
void sub_2C2ED0(EEContext& ctx);
// 0x2C30F0 AI predicate: sub_2C2ED0 with the shield check.
void sub_2C30F0(EEContext& ctx);
// 0x2C3120 AI predicate: sub_2C2ED0 without the shield check.
void sub_2C3120(EEContext& ctx);
// 0x2C3430 [btlAIPickTarget] AI target pick: the candidate list of the action's skill (sub_2BFCB0 / sub_2BFF60 into the record
//   +136; all-target skills take the whole list), filtered like sub_2C1080 plus 'has a usable attack' (sub_2C5030), the
//   status mask a2 and the predicate a5 (!= a4); flag 4 keeps every match, else one at random; none -> the fallback
//   selector sub_2C3770 unless flag 8.
void sub_2C3430(EEContext& ctx);
// 0x2C4C80 [btlAIPickHealSkill] Healing skill closest to filling a unit's HP: over the skill list a2 (a3 entries, filtered by
//   target kind a4 on SkillRecord +8), the one whose datCalcDamage brings HP + heal nearest to max HP (abs); -1 for
//   none.
void sub_2C4C80(EEContext& ctx);
// 0x2C4E50 [btlAIPickHealItem] As sub_2C4C80 over an item list (the item's skill through sub_30BC20): the healing item closest
//   to max HP.
void sub_2C4E50(EEContext& ctx);
// 0x2C5030 [btlAIPickAttackSkill] The attack skills a unit could use on a target: the normal attack when its element passes
//   sub_2C2ED0, then every usable skill (sub_2C2B20 rules) whose element is an attack element (0x1FE; a3 set: not
//   physical) and passes sub_2C2ED0; returns one at random (datCalcRand) or -1.
void sub_2C5030(EEContext& ctx);
// 0x2C5380 [btlAIPickRecoverySkill] Support AI's healing choice for a target: dead -> revive skills, HP <= 60 % with an
//   ailment -> cure skills, HP below max -> heal (sub_2C4C80); the usable skill of that kind, or -1.
void sub_2C5380(EEContext& ctx);
// 0x2C59D0 [btlAIPickRecoveryItem] Party member AI's item choice for a target (party ids 2..10 only): revive / cure / heal
//   items from the item stock (sub_170670 / sub_1706C0, sub_2C4E50), or -1.
void sub_2C59D0(EEContext& ctx);
// 0x2C5FC0 [btlAIPickSkillOfElement] A usable skill of the element a2 against a target (16 = recovery: sub_2C5380), the normal
//   attack included; one at random or -1.
void sub_2C5FC0(EEContext& ctx);
// 0x2C6F50 [btlAIRunScript] Starts an AI script for an action: party units use the procedure "AI_PC_%03X_%03X" (tactic,
//   persona) of the script a2, enemies the index a3; a script task with the action as user data and the unit's name in
//   its message window, a child of the battle task; kept in the AI record +76.
void sub_2C6F50(EEContext& ctx);
// 0x2C70D0 [btlAIThink] AI think: clears the record, then for an enemy with an AI script (AICALC section 15 row +2) or a party
//   member runs the script (sub_2C6F50); otherwise evaluates the AICALC row (sub_2C6BA0 / sub_2C6E30), decodes the
//   command (sub_2C6A00) and calls the target selector of the table 0x6975E0 (falling back to row 0).
void sub_2C70D0(EEContext& ctx);
// 0x2D1570 Clears an action's 80-byte record.
void sub_2D1570(EEContext& ctx);
// 0x2D15A0 Clears an action's target words (+50..+56) and the 6 bytes at +62.
void sub_2D15A0(EEContext& ctx);
// 0x2D1E70 [btlVecDistance] Distance between two points (sub_4C6AC0 of the difference).
void sub_2D1E70(EEContext& ctx);
// 0x2D1ED0 [btlVecDistanceXZ] Distance between two points on the ground plane (y ignored).
void sub_2D1ED0(EEContext& ctx);
// 0x2D1F30 [btlQuatAngle] Angle between two quaternions: 2 acos(|q1 . q2|).
void sub_2D1F30(EEContext& ctx);
// 0x2D1FD0 Ground-plane direction from a1 to a0 normalised (sub_4C6B20); with a3, the point a2 rotated into that frame.
void sub_2D1FD0(EEContext& ctx);
// 0x2D20A0 [btlWorldToScreen] Projects a world point to the screen: camera space (sub_4C6BE0 with the camera matrix sub_198590
//   +32); inside the near / far range (+128 / +132), x = 640 x / z, y = 448 y / z, accepted within [-640, 1280] x
//   [-448, 896].
void sub_2D20A0(EEContext& ctx);
// 0x2D2470 Whether the segment a0-a1 passes within a distance f12 of the point a2 (ground plane).
void sub_2D2470(EEContext& ctx);
// 0x2D25C0 [btlPathSegmentBlocked] Whether the segment between two path nodes is blocked: by an edge of any other unit box's
//   corner node, or by a box containing an end point (boxes from gBtl +716, corners +8 at stride 304, links +1228).
void sub_2D25C0(EEContext& ctx);
// 0x2D2A00 Whether any unit in the battle blocks the line between two units (sub_2D2990 / sub_2D2470).
void sub_2D2A00(EEContext& ctx);
// 0x2D2C10 Whether two nodes see each other across the box edges (sub_2D2EE0 side tests), the target node's own box excepted.
void sub_2D2C10(EEContext& ctx);
// 0x2D2EE0 [btlPathSide] Side of a point relative to a directed edge on the ground plane: -1 left, 1 right / on.
void sub_2D2EE0(EEContext& ctx);
// 0x2D2F50 [btlPathBuildNeighbours] Builds a node's neighbour list: every visible corner node with clearance >= f12, the field
//   corners (gBtl +720), the start (+1936) and goal (+2240) nodes, with their distances (+48 nodes, +176 distances, 0
//   terminated); returns the count.
void sub_2D2F50(EEContext& ctx);
// 0x2D32B0 [btlPathBuildGraph] Builds the path graph: the corner nodes of every unit box (from the grid cells, grown by the
//   clearance) and the field corners, then their neighbour lists.
void sub_2D32B0(EEContext& ctx);
// 0x2D41C0 [btlPathSmooth] Smooths a found path: drops the nodes a straight line can skip (sub_2D2A00) and writes the way
//   points to the path record.
void sub_2D41C0(EEContext& ctx);
// 0x2D4810 [btlPathPopBest] Pops the open-list node with the lowest cost (+32) from gBtl +2544 (linked by +36).
void sub_2D4810(EEContext& ctx);
// 0x2D48C0 [btlPathFind] Path query from a1 to a2 for a unit's walk: direct when nothing blocks (sub_2D2A00), else the graph
//   (sub_2D32B0) and a lowest-cost search from the start node; the result in the path record a0 (+1024 count, +1028
//   done).
void sub_2D48C0(EEContext& ctx);
// 0x2D5DC0 Clears a 28-byte result record and sets its byte +25 to -1.
void sub_2D5DC0(EEContext& ctx);
// 0x2D7560 [btlActionCollectSpoils] Victory book-keeping of a defeated enemy (once per action, flag 0x20): adds its experience
//   (sub_30BC50 * sub_1C0070's factor) to gBtl +3068, collects its item drop (sub_30BDE0, or the action's stolen item
//   +128 with the chance +130) into the three drop slots +3040, the rare flag of the enemy table (bit 0x40 -> gBtl
//   +3036 bit 1), and the four special ids 193..196 -> gBtl +3104 bits.
void sub_2D7560(EEContext& ctx);
// 0x2D7E20 [btlPktCreateDamage] Creates the damage-number packet (kind 1792, 40 bytes: unit, target, 28-byte result, two
//   halfwords) with callbacks sub_2D7970 / sub_2D79A0 / sub_2D7DF0.
void sub_2D7E20(EEContext& ctx);
// 0x2D8390 [btlSupportPickOpeningLine] The navigator's opening line: by the advantage (gBtl +26: 0 normal, 1 enemy strike, 2
//   player strike), a strong enemy (enemy table bit 0x80), a rare one (0x40), the enemy count (< 6) and whether their
//   mean level is 4 or more above the hero's (lines 0..11, 59..81, 81..93), with advantage 1 the +5 variants when an
//   enemy sleeps (status 2); -1 for none or 6+ enemies.
void sub_2D8390(EEContext& ctx);
// 0x2D9BE0 A party unit's voice line of the table row 0x7B7EF0: party ids 1..5 -> 346..350, 7..10 -> 351..354 (no line for 6,
//   the navigator); -1 for enemies and other ids.
void sub_2D9BE0(EEContext& ctx);
// 0x2D9D70 [btlSupportPickStatusLine] The navigator's status report line: collects candidate lines (party low HP 372, ailments
//   399 / 410 / 419 / 428 / 445 / 454, the hero's persona situation 390..392, member 3's charm 437, three or more low
//   HP 381, members absent from the battle with HP <= 30 % 382..389, a rare enemy 397, the count of enemies left
//   393..396, the hero's buffs 438..440), picks one at random (datCalcRand), skips a repeat of the last (+2608), adds
//   the speaker offset; -1 for none or for an enemy turn.
void sub_2D9D70(EEContext& ctx);
// 0x2DD270 Hold callback of the skill sound packet: requests "skill/%03X.se" unless flag 1; +6 = 1.
void sub_2DD270(EEContext& ctx);
// 0x2DD690 [btlPktCreateMessage] Creates the message packet 2309 (the text copied after an 8-byte header: u16 a0, the text
//   pointer) with the update sub_2DD630.
void sub_2DD690(EEContext& ctx);
// 0x2DD8E0 Creates packet 2313 (4 bytes: a0) with the update sub_2DD8B0.
void sub_2DD8E0(EEContext& ctx);
// 0x2DD960 Creates packet 2314 (4 bytes: a0) with the update sub_2DD930.
void sub_2DD960(EEContext& ctx);
// 0x2E0620 [btlVoicePickEventLine] A unit's voice line for an event (a1): the boss enemies 233..240 / 264 / 271 / 272 ... by
//   their own tables (boss 234 by the event 192..211), party members by id and event, some once (datGetFlag /
//   datSetFlag) or at random; -1 for none or without a camera object.
void sub_2E0620(EEContext& ctx);
// 0x2E0F70 [btlVoicePickCountLine] A party member's line on an enemy count (1 / 2 / 3 / 4 / 5 enemies left), by party id; -1
//   for the hero or enemies.
void sub_2E0F70(EEContext& ctx);
// 0x2E12D0 [btlVoicePickAttackLine] A party member's attack line: one of two by a coin flip (datCalcRand(100) < 50), by party
//   id; -1 under the boss rules or for enemies.
void sub_2E12D0(EEContext& ctx);
// 0x2E1BF0 A party member's line of the row 0x7B8810: by party id 2..10 (Koromaru's by sub_17D800).
void sub_2E1BF0(EEContext& ctx);
// 0x2E2410 [btlVoicePickBystanderLine] A random other party member (living, not the hero or the actor, not ailing, not
//   Koromaru's partner id 10) comments: its count line sub_2E0F70; -1 for none.
void sub_2E2410(EEContext& ctx);
// 0x2E2680 [btlVoicePickLine1091] A party member's line by party id with a coin flip (some by the flag 0x697BE4); -1 for
//   enemies, a missing DatUnit or persona state 9.
void sub_2E2680(EEContext& ctx);
// 0x2E3120 [btlAnalysisGetRecord] The analysed-enemy record of a unit: drops the 12 records (gBtl +2656: s8 side, u16 enemy
//   id) whose enemy left the battle, then returns the unit's record, taking a free one when absent.
void sub_2E3120(EEContext& ctx);
// 0x2E32A0 [btlAnalysisLearnElement] Records that the party saw an enemy's affinity to the element of the skill a2 (sub_17B2E0
//   on its analysis record), for enemies only.
void sub_2E32A0(EEContext& ctx);
// 0x2E3350 [btlAnalysisKnowsElement] Whether the party knows an enemy's affinity to an element (1 for party units, the
//   almighty / unknown / physical-7 elements): the analysis record's bits (sub_17B3D0).
void sub_2E3350(EEContext& ctx);
// 0x2E35D0 Creates packet 3072 (6 bytes: two halfwords and 0) with the hold / update callbacks sub_2E3560 / sub_2E35A0.
void sub_2E35D0(EEContext& ctx);
// 0x2E36F0 Creates packet 3073 (8 bytes zeroed) with the update sub_2E3650.
void sub_2E36F0(EEContext& ctx);
// 0x2E37E0 Creates packet 3074 (8 bytes zeroed) with the update sub_2E3740.
void sub_2E37E0(EEContext& ctx);
// 0x2E3C80 Creates packet 3079 (8 bytes zeroed) with the update sub_2E3BE0.
void sub_2E3C80(EEContext& ctx);
// 0x2E4290 Boss AI event: battle start (sub_2FD2E0 kind 0).
void sub_2E4290(EEContext& ctx);
// 0x2E42E0 Boss AI event: action start (sub_2FD2E0 kind 1).
void sub_2E42E0(EEContext& ctx);
// 0x2E4330 Boss AI event: action end -- the pending boss callback (gBtl +2824 with +2832) when set and sub_2FD500 is 0, else
//   sub_2FD2E0 kind 2.
void sub_2E4330(EEContext& ctx);
// 0x2E4430 [btlSkillCheckTargets] Whether a skill finds targets now: for a targeted skill (skill record bit 0x8) the
//   candidates (sub_2BFCB0 with the record's +9 / +10 / +12): none -> 2; target type 6 (+36) without sub_2C1CE0 -> 6;
//   else 0 (also 0 for skills <= 0 or untargeted ones).
void sub_2E4430(EEContext& ctx);
// 0x2F6E00 Boss battle set-up at the battle start: clears the boss block (gBtl +2836, 116 bytes), and for the boss encounters
//   416..436 / 456 sets the boss rule flags (gBtl +12 / +16), the boss AI table (+2840 = section base + 1,044 * index)
//   and the boss mode word (+2948); finds the boss script's AI_EVENT_%03X_BTLSTART / ACTSTART / ACTEND procedures
//   (+2844 / +2848 / +2852).
void btlBossSetup(EEContext& ctx);
// 0x2F9710 [btlBossRequestSound] Hold callback of the boss sound packet: requests the encounter's "snd_benc/boss/eXXX.pak"
//   (416..436, 456) into gBtl +2836.
void sub_2F9710(EEContext& ctx);
// 0x2FC5D0 [btlBossGetReach] Boss reach (in $f0): with the boss rules on, the distance a unit stops at before boss 241 and the
//   other big bosses for attack / skill motions 4 / 5 / 6 / 11 (radius * scale + a per-boss constant); -1.0 when none.
void sub_2FC5D0(EEContext& ctx);
// 0x2FD2E0 [btlBossRunEvent] Starts a boss AI event script (kind a1: 0 battle start, 1 action start, 2 action end) once per
//   action / turn pair: a script task from the boss header with the hero's action as user data, its message window, as
//   a child of the battle task; remembers it in gBtl +2856.
void sub_2FD2E0(EEContext& ctx);
// 0x2FD8A0 Boss rule for encounters 0x1A7..0x1B3: lets the listed boss enemies fidget (sub_289860).
void sub_2FD8A0(EEContext& ctx);
// 0x2FE0B0 Draws a boss gauge ring segment (Im2D through the RW slots).
void sub_2FE0B0(EEContext& ctx);
// 0x2FE780 Draws a boss gauge arc (Im2D, sinf / cosf).
void sub_2FE780(EEContext& ctx);

}  // namespace p3fes::game
