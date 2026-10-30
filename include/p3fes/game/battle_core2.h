// The core battle band 0x270000-0x2D0000, second pass (slice battle_core2; docs/ANALYSIS/21_battle.md sections 1.1-1.4,
// 3.1): the "admini" sequence driver (admini.c), the btl root (btlCreate / btlDestroy, the draw tasks, the
// CALL_BATTLE / WAIT_BATTLE commands), the .TBL loader, the btl packet queue (allocate, queue, run, free), the btlUnit
// accessors and the unit packets, unit / combatant / btlAction creation, btlActionUpdateAll and the turn-order code.
// game/src/battle/battle_core2.cpp; the bodies come from p3fes_handgen (register ABI: arguments in $a0.., the result
// in $v0), made readable with the layouts below. Names: functions.json names in code; ours in brackets in the comments
// and in tools/ours/types/deltas/battle_core2.json (ADR-0009).
//
// The layouts (all offsets decimal, as the instructions give them; "obs" from the functions of this slice):
//   gBtl          *(u32*)0x7CE3EC ($gp - 18692), 3,440 bytes (btlCreate);
//   btl packet    sub_27EC10: 144 bytes + its data; two start and two end conditions, a phase machine run by
//                 sub_27EE00 over four queues (gBtl+372 + 8q heads, +368 + 8q tails);
//   btlUnit       btlUnitCreate: 2,616 bytes, in four side lists (gBtl+340 + 8s heads, +336 + 8s tails);
//   btlAction     btlActionCreate: 1,200 bytes, in the list gBtl+332 (pushed at the head);
//   admini work   sub_27C8F0: 36 bytes, the work of the "admini" task: the running / requested sequence, an
//                 eight-slot history ring and the parameter block of sSequenceList 0x68F020 (12-byte rows
//                 {call(restoring, block), exit() -> s32, check() -> done}).
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace bcore {

// --- $gp slots -------------------------------------------------------------------------------------------------------
inline constexpr s32 kGpBtl = -18692;              // 0x7CE3EC gBtl
inline constexpr s32 kGpSflPersona = -18696;       // 0x7CE3E8 the shuffle persona work (sfl_persona.c)
inline constexpr s32 kGpGameOverLatch = -18688;    // 0x7CE3F0 1 once WAIT_BATTLE started the game-over script
inline constexpr s32 kGpModelWeapon = -18664;      // 0x7CE408 MODEL.TBL section 0: 296-byte records by weapon type
inline constexpr s32 kGpModelParty = -18660;       // 0x7CE40C MODEL.TBL section 1: 266-byte records by party id
inline constexpr s32 kGpModelEnemy = -18648;       // 0x7CE418 MODEL.TBL section 2: 232-byte records by enemy id
inline constexpr s32 kGpModelPersona = -18628;     // 0x7CE42C MODEL.TBL section 3: 88-byte records by persona id
inline constexpr s32 kGpAiPartyRange = -18528;     // 0x7CE490 AICALC.TBL section 9: u16 {min, max} per party member
inline constexpr s32 kGpEncountTbl = -18504;       // 0x7CE4A8 gEncountTbl (ENCOUNT.TBL section 0, 28-byte records)
inline constexpr s32 kGpEffect3 = -18476;          // 0x7CE4C4 EFFECT.TBL section 3
inline constexpr s32 kGpEffect4 = -18472;          // 0x7CE4C8 EFFECT.TBL section 4
inline constexpr s32 kGpTblArenaOff = -18460;      // 0x7CE4D4 bytes used in the table arena 0x875D00
inline constexpr s32 kGpTblRequest = -18456;       // 0x7CE4D8 the H_Cdvd request of the table file being loaded
inline constexpr s32 kGpTblReloadIdx = -18452;     // 0x7CE4DC the next row of 0x692D40 an async load takes
inline constexpr s32 kGpMsgText = -18448;          // 0x7CE4E0 MSG.TBL section 4 (the message manager's text)
inline constexpr s32 kGpUidCounter = -26592;       // 0x7CC510 u64: btlGetUID's counter (sub_27CB80)
inline constexpr s32 kGpModelIdCounter = -26584;   // 0x7CC518 u16: the battle model id counter, 256..511
inline constexpr s32 kGpUnitSerial = -26580;       // 0x7CC51C u32: btlUnit serial counter
inline constexpr s32 kGpActionSerial = -26560;     // 0x7CC530 u32: btlAction serial counter
inline constexpr s32 kGpPartyRangeScale = -32656;  // 0x7CAD60 f32 (sub_27D8D0)
inline constexpr s32 kGpPartyOrderWeights = -26344;  // 0x7CC608 u8[]: the party members' lottery weights (sub_29A750)
inline constexpr u32 kTableArena = 0x875D00u;      // the battle table arena
inline constexpr u32 kTableFiles = 0x692D40u;      // the eight 168-byte rows {name, name_F, {dst, size} x 20}
inline constexpr u32 kTableFileRow = 168;
inline constexpr u32 kSequenceList = 0x68F020u;    // sSequenceList: 12-byte rows {call, exit, check}
inline constexpr u32 kActionStateTbl = 0x693410u;  // sBtlActionTbl: 36 x {init, update, name}
inline constexpr u32 kCondJumpTable = 0x7B7AC0u;   // sub_27E530's 12 cases (kind - 1)
inline constexpr u32 kRwMallocSlot = 0x960178u;    // RwMalloc(size, hint)
inline constexpr u32 kRwFreeSlot = 0x96017Cu;      // RwFree(p)

// --- gBtl (3,440 bytes) ------------------------------------------------------------------------------------------------
inline constexpr s32 kBtlSize = 3440;
inline constexpr s32 kBtlFlags = 12;            // u32: 0x2 scene active, 0x8 an ended action moves to the order's end,
                                                //   0x2000 auto battle, 0x8000 the battle owns the setup's genus,
                                                //   0x80000 the turn order paused; btlCreate ORs 0x481077C
inline constexpr s32 kBtlPlayerAction = 328;    // u32: the player-controlled btlAction (the hero)
inline constexpr s32 kBtlActionList = 332;      // u32: head of the btlAction list (+1192 next, +1188 prev)
inline constexpr s32 kBtlUnitTail = 336;        // u32[4] (stride 8): tail of each side's btlUnit list
inline constexpr s32 kBtlUnitHead = 340;        // u32[4] (stride 8): head (+2608 next, +2612 prev)
inline constexpr s32 kBtlPktTail = 368;         // u32[4] (stride 8): tail of each packet queue
inline constexpr s32 kBtlPktHead = 372;         // u32[4] (stride 8): head (+124 next, +128 prev)
inline constexpr s32 kBtlSceneVecA = 452;       // f32[4]: copied to the scene object +256 each frame (sub_29E420)
inline constexpr s32 kBtlSceneVecB = 468;       // f32[4]: copied to the scene object +272
inline constexpr s32 kBtlSceneField = 580;      // u16: the setup's field id (MT_Scene_Load)
inline constexpr s32 kBtlSceneRoom = 582;       // u16: the setup's room id
inline constexpr s32 kBtlOrderFlags = 584;      // u16: bit 0 order active, bit 1 / 2 reshuffle the enemies / the party,
                                                //   bit 3 the next turn may start
inline constexpr s32 kBtlOrderTurns = 588;      // u32: turns started
inline constexpr s32 kBtlOrderActor = 592;      // u32: the action sub_29A4F0 moves to the end of the order
inline constexpr s32 kBtlOrderList = 596;       // u32[12]: the turn order (btlAction*)
inline constexpr s32 kBtlOrderNext = 644;       // u32[12]: actions queued for the next round (flags bit 2)
inline constexpr s32 kBtlMesMng = 2976;         // u32: the message manager handle (itfMesMngInitialize)
inline constexpr s32 kBtlSetupParty = 2988;     // u32[4]: the setup block's party genus (+4 of the block)
inline constexpr s32 kBtlSetupEnemies = 3004;   // u32: the setup block's enemy genus (+20)
inline constexpr s32 kBtlSetupReinforce = 3012; // u32[3] (stride 8): reinforcement genus
inline constexpr s32 kBtlRootTask = 3352;       // u32: the "battle" task tree (sub_27D880)
inline constexpr s32 kBtlResultTask = 3368;     // u32: the result screen (sub_1F1C20 closes it)

// --- btl packet (sub_27EC10: 144 bytes + data) -------------------------------------------------------------------------
inline constexpr s32 kPktHeader = 144;
inline constexpr s32 kPktStart = 0;             // 2 x 16-byte condition that starts the packet (both must hold)
inline constexpr s32 kPktEnd = 32;              // 2 x 16-byte condition that ends it
inline constexpr s32 kCondKind = 0;             //   u8: 1 always, 2 age >= arg, 3..12 other packets (sub_27E530)
inline constexpr s32 kCondArg = 8;              //   u64
inline constexpr s32 kPktKind = 64;             // u32 (compared as u16 by the kind conditions)
inline constexpr s32 kPktQueue = 68;            // u8: 0..3
inline constexpr s32 kPktPhase = 69;            // u8: 0 wait start, 1 start delay, 2 running, 3 wait end, 4 end delay
inline constexpr s32 kPktPaused = 70;           // u8: non-zero = skipped by sub_27EE00
inline constexpr s32 kPktFlags = 71;            // u8: 0x01 / 0x10 / 0x20 live (set at allocation), 0x08 queued,
                                                //   0x04 kill
inline constexpr s32 kPktStartDelay = 72;       // s16: frames between "started" and running
inline constexpr s32 kPktEndDelay = 74;         // s16: frames between "ended" and freed
inline constexpr s32 kPktAge = 76;              // u32: frames since queued
inline constexpr s32 kPktRunFrames = 80;        // u32: frames the update callback ran without finishing
inline constexpr s32 kPktId = 88;               // u64: btlGetUID at queue time
inline constexpr s32 kPktOwner = 96;            // u64: the owner's id (conditions 6..8, 12)
inline constexpr s32 kPktOnQueue = 104;         // fn(data): at queue time (the unit packets hold their unit)
inline constexpr s32 kPktUpdate = 108;          // fn(data) -> non-zero when done
inline constexpr s32 kPktOnEnd = 112;           // fn(data): before the packet is freed
inline constexpr s32 kPktQuery = 116;           // fn(data, gBtl, arg) -> bool (conditions 11 / 12)
inline constexpr s32 kPktData = 120;            // u32: the data block (packet + 144 when the size is > 0)
inline constexpr s32 kPktNext = 124;            // u32
inline constexpr s32 kPktPrev = 128;            // u32
inline constexpr u8 kPktLive = 0x31;
inline constexpr u8 kPktQueued = 0x08;
inline constexpr u8 kPktKill = 0x04;

// packet data blocks (by creator)
inline constexpr s32 kPdUnit = 0;               // the unit a unit packet holds (busy counter +160)
inline constexpr s32 kPdUnit2 = 4;              // the second unit of sub_282650's packet
inline constexpr s32 kPdUnit12 = 12;            // the unit of sub_284900's packet
inline constexpr s32 kPdUnit36 = 36;            // the unit of sub_281E80's packet
inline constexpr s32 kXfPos = 4;                // sub_27FE90 (kind 283): f32[3] position (mask bit 0)
inline constexpr s32 kXfRot = 16;               //   f32[4] rotation (mask bit 1)
inline constexpr s32 kXfColour = 32;            //   u8[4] colour (mask bit 2)
inline constexpr s32 kXfMask = 36;              //   u16
inline constexpr s32 kMoMotion = 4;             // sub_284200 (kind 256): s16 motion
inline constexpr s32 kMoMode = 6;               //   u16
inline constexpr s32 kMoSpeed = 8;              //   f32
inline constexpr s32 kMoFlags = 12;             //   u16
inline constexpr s32 kCallFn = 0;               // sub_27F410 (kind 0xFF01): fn(arg) -> done
inline constexpr s32 kCallArg = 4;
inline constexpr s32 kMvTarget = 4;             // sub_2819D0 (kind 266, move): f32[3] target
inline constexpr s32 kMvFrames = 16;            //   s32 frames
inline constexpr s32 kMvSpeed = 32;             //   f32
inline constexpr s32 kLkFrames = 16;            // sub_281E80 (kind 267): s32 frames
inline constexpr s32 kLkF28 = 28;               //   f32 ($f13)
inline constexpr s32 kLkF32 = 32;               //   f32 ($f12)
inline constexpr s32 kP268Arg = 24;             // sub_282130 (kind 268): u32 a0
inline constexpr s32 kP268Value = 28;           //   u16 a1
inline constexpr s32 kP268Counter = 30;         //   u16 0
inline constexpr s32 kTnDir = 4;                // sub_2822B0 (kind 269, turn): f32[3]
inline constexpr s32 kTnFrames = 16;            //   s32 frames
inline constexpr s32 kFcArg = 8;                // sub_282650 (kind 270): the third word
inline constexpr s32 kIdMode = 4;               // sub_2843E0 (kind 260, idle motion): u16 mode
inline constexpr s32 kSpSpeed = 4;              // sub_284600 (kind 263): f32 motion speed
inline constexpr s32 kP264Arg = 16;             // sub_284900 (kind 264): u16 a1
inline constexpr s32 kP264Counter = 18;         //   u16 0

// the low halves of three addresses the code builds with lui (0x960000 + lo, 0x950000 + lo, 0x690000 + lo)
inline constexpr s32 kRwMallocLo = 376;         // 0x960178 RwMalloc slot
inline constexpr s32 kRwFreeLo = 380;           // 0x96017C RwFree slot
inline constexpr s32 kZeroVecLo = 29056;        // 0x957180 the zero vector (f32[3])
inline constexpr s32 kActionStateTblLo = 13328; // 0x693410 sBtlActionTbl

// --- btlUnit (btlUnitCreate: 2,616 bytes) ------------------------------------------------------------------------------
inline constexpr s32 kUnSize_ = 2616;
inline constexpr s32 kUnShowFlags = 0;          // u16 (sub_27F770 / sub_27F790)
inline constexpr s32 kUnPos = 4;                // f32[3]
inline constexpr s32 kUnHome = 16;              // f32[3] (zero at creation)
inline constexpr s32 kUnRot = 28;               // f32[4] quaternion (0, 0, 0, 1 at creation)
inline constexpr s32 kUnScale = 44;             // f32
inline constexpr s32 kUnColour = 48;            // u8[4] RGBA (0xFF at creation)
inline constexpr s32 kUnColourBase = 52;        // u8[4]
inline constexpr s32 kUnColourFrom = 60;        // u8[4]
inline constexpr s32 kUnColourTo = 64;          // u8[4]
inline constexpr s32 kUnColourTime = 76;        // u16
inline constexpr s32 kUnLight = 84;             // f32[3] (zero at creation)
inline constexpr s32 kUn112 = 112;              // u32 x 3 cleared at creation, f32 +124 = 0.5
inline constexpr s32 kUn116 = 116;
inline constexpr s32 kUn120 = 120;
inline constexpr s32 kUn124 = 124;
inline constexpr s32 kUnCentre = 128;           // f32[3]: centre offset (0, height / 2, 0 at creation; record words)
inline constexpr s32 kUnHeight = 140;           // f32 (150 at creation)
inline constexpr s32 kUnSize = 144;             // f32 (50 at creation; radius = size * scale)
inline constexpr s32 kUnGridX = 148;            // s16: position x = 25 * grid x - 1750 (sub_27F7C0)
inline constexpr s32 kUnGridZ = 150;            // s16
inline constexpr s32 kUnDirty = 152;            // u32: 0x2 has a model, 0x4 transform changed
inline constexpr s32 kUnFlags = 156;            // u32: 0x1 dead, 0x2 no model, 0x8 a combatant, 0x20 / 0x40 / 0x80 /
                                                //   0x200 party, 0x1000 model hidden, 0x2000 rotation locked
inline constexpr s32 kUnBusy = 160;             // u16: packets holding the unit
inline constexpr s32 kUnSide = 162;             // u8: 0 party, 1 enemy, 2 persona
inline constexpr s32 kUnId = 164;               // u16: party / enemy / persona id
inline constexpr s32 kUnSerial = 168;           // u32
inline constexpr s32 kUnMoveFlags = 200;        // u16: bit 0 moving, bit 1 turning
inline constexpr s32 kUn204 = 204;              // f32 (27 at creation)
inline constexpr s32 kUnHalfWidth = 1268;       // f32 (4 for the party, 7 otherwise)
inline constexpr s32 kUnMotion = 2510;          // s16: the current motion (valid with a model)
inline constexpr s32 kUnMotionSpeed = 2516;     // f32 (1 at creation)
inline constexpr s32 kUnMotionCount = 2520;     // u16: motions in the model record's table (26 / 23 / 19 / 6)
inline constexpr s32 kUnIdleMotion = 2528;      // s16
inline constexpr s32 kUnIdleSpeed = 2532;       // f32: the idle motion's speed (sub_284350)
inline constexpr s32 kUnIdleFlags = 2536;       // s8: the idle motion's flags
inline constexpr s32 kUnModelRec = 2540;        // u32: the model record's motion table
inline constexpr s32 kUnFormSlot = 2544;        // s8 (-1 at creation)
inline constexpr s32 kUnModelId = 2546;         // u16 (0 = none)
inline constexpr s32 kUnModel = 2548;           // u32: the model (sub_318770 / sub_318990)
inline constexpr s32 kUnBedA = 2552;            // u32: sub_2BBC00(unit)
inline constexpr s32 kUnBedB = 2556;            // u32: sub_2BB7D0()
inline constexpr s32 kUnPersona = 2560;         // u32: the persona sub-unit (side 2)
inline constexpr s32 kUnEffects = 2564;         // sub_2BCDE0's record
inline constexpr s32 kUnDat = 2604;             // u32: DatUnit*
inline constexpr s32 kUnNext = 2608;            // u32
inline constexpr s32 kUnPrev = 2612;            // u32
inline constexpr s32 kDatId = 2;                // DatUnit: u16 id

// --- btlAction (btlActionCreate: 1,200 bytes) ------------------------------------------------------------------------
inline constexpr s32 kActSize = 1200;
inline constexpr s32 kActUid = 0;               // u64: btlGetUID
inline constexpr s32 kActSerial = 8;            // u32
inline constexpr s32 kActState = 12;            // u16: row of sBtlActionTbl
inline constexpr s32 kActNextState = 14;        // u16: pending state (0 = none)
inline constexpr s32 kActPrevState = 16;        // u16
inline constexpr s32 kActDelay = 18;            // u16: frames before the pending state is entered
inline constexpr s32 kActReturn = 20;           // u16: the state a turn starts with (5 Command, 8 AI, 9 Auto)
inline constexpr s32 kActResume = 22;           // u16: the state a next-round action resumes
inline constexpr s32 kActFlags = 24;            // u16: bit 0 active, bit 2 queued for the next round
inline constexpr s32 kActFlags2 = 26;           // u16: bit 0 has a unit, 1 remove, 2 frozen, 3 combatant, 4 party
inline constexpr s32 kActFrames = 28;           // u32: += 2 per update
inline constexpr s32 kAct36 = 36;               // s32 (-1 at creation)
inline constexpr s32 kActUnit = 48;             // u32: btlUnit*
inline constexpr s32 kActRand = 54;             // u16: datCalcRand(60) at creation
inline constexpr s32 kActTarget = 56;           // the target record (sub_2D1570)
inline constexpr s32 kActLinkPrev = 1188;       // u32
inline constexpr s32 kActLinkNext = 1192;       // u32

// --- the admini task's work (36 bytes) -------------------------------------------------------------------------------
inline constexpr s32 kAdmFlags = 0;             // u32: 0x1 change pending, 0x2 sequence done, 0x4 leave a return
                                                //   point, 0x8 keep the ring index, 0x10000 restoring
inline constexpr s32 kAdmFrames = 4;            // u32: frames in the sequence
inline constexpr s32 kAdmSeq = 8;               // s8: the running sequence (-1 none)
inline constexpr s32 kAdmNextSeq = 9;           // s8: the requested sequence (-1 none)
inline constexpr s32 kAdmRing = 10;             // u8: history ring index 0..7
inline constexpr s32 kAdmRingSeq = 12;          // s8[8]: the sequences of the history ring
inline constexpr s32 kAdmRingFlags = 20;        // u8[8]: bit 0 = a return point
inline constexpr s32 kAdmParam = 28;            // u32: the parameter block (RwMalloc)
inline constexpr s32 kAdmParamSize = 32;        // u8
inline constexpr s32 kAdmDelay = 33;            // u8: frames before the requested sequence's call

// --- table rows, file requests, encounters -----------------------------------------------------------------------------
inline constexpr s32 kTblName = 0;              // u32 char*
inline constexpr s32 kTblNameF = 4;             // u32 char*: The Answer's file
inline constexpr s32 kTblDst = 8;               // {u32* dst, u32 size} x up to 20, ended by dst == 0
inline constexpr s32 kCdvdData = 272;           // H_Cdvd request: the loaded file's data
inline constexpr s32 kEncField = 18;            // ENCOUNT record: u16 field id
inline constexpr s32 kEncRoom = 20;             // u16 room id

}  // namespace bcore

// The 133 functions (register ABI; each also has its recomp_gen::fn_<name>_<addr8> shim).
void sub_27C020(EEContext& ctx);  // 0x27C020
void adminiChangeSeq(EEContext& ctx);  // 0x27C080
void sub_27C220(EEContext& ctx);  // 0x27C220
void sub_27C2B0(EEContext& ctx);  // 0x27C2B0
void sub_27C330(EEContext& ctx);  // 0x27C330
void adminiUpdateTask_Call(EEContext& ctx);  // 0x27C3B0
void sub_27C5A0(EEContext& ctx);  // 0x27C5A0
void sub_27C650(EEContext& ctx);  // 0x27C650
void sub_27C840(EEContext& ctx);  // 0x27C840
void sub_27C8F0(EEContext& ctx);  // 0x27C8F0
void sub_27C9E0(EEContext& ctx);  // 0x27C9E0
void sub_27CA10(EEContext& ctx);  // 0x27CA10
void sub_27CA40(EEContext& ctx);  // 0x27CA40
void adminiSeqCallBtl(EEContext& ctx);  // 0x27CA70
void adminiSeqExitBtl(EEContext& ctx);  // 0x27CAA0
void sub_27CAE0(EEContext& ctx);  // 0x27CAE0
void sub_27CB10(EEContext& ctx);  // 0x27CB10
void sub_27CB40(EEContext& ctx);  // 0x27CB40
void sub_27CB50(EEContext& ctx);  // 0x27CB50
void sub_27CB80(EEContext& ctx);  // 0x27CB80
void sub_27CBD0(EEContext& ctx);  // 0x27CBD0
void btlUpdateDraw3DFrontTask(EEContext& ctx);  // 0x27CD70
void btlUpdateDraw2DTask(EEContext& ctx);  // 0x27CDA0
void sub_27CE50(EEContext& ctx);  // 0x27CE50
void btlCreate(EEContext& ctx);  // 0x27CED0
void sub_27D020(EEContext& ctx);  // 0x27D020
void btlScrCmd_CALL_BATTLE(EEContext& ctx);  // 0x27D5E0
void sub_27D730(EEContext& ctx);  // 0x27D730
void sub_27D810(EEContext& ctx);  // 0x27D810
void sub_27D8D0(EEContext& ctx);  // 0x27D8D0
void sub_27DC00(EEContext& ctx);  // 0x27DC00
void sub_27DC80(EEContext& ctx);  // 0x27DC80
void btlTableLoad(EEContext& ctx);  // 0x27DCD0
void btlTableLoadAll(EEContext& ctx);  // 0x27DE40
void btlTablePatchForAnswer(EEContext& ctx);  // 0x27DF20
void btlTableInit(EEContext& ctx);  // 0x27E180
void btlUpdateTableReloadTask(EEContext& ctx);  // 0x27E1D0
void sub_27E270(EEContext& ctx);  // 0x27E270
void sub_27E2C0(EEContext& ctx);  // 0x27E2C0
void sub_27E530(EEContext& ctx);  // 0x27E530
void sub_27EC10(EEContext& ctx);  // 0x27EC10
void sub_27ED20(EEContext& ctx);  // 0x27ED20
void nullsub_12(EEContext& ctx);  // 0x27EDF0
void sub_27EE00(EEContext& ctx);  // 0x27EE00
void sub_27F160(EEContext& ctx);  // 0x27F160
void sub_27F1C0(EEContext& ctx);  // 0x27F1C0
void sub_27F2E0(EEContext& ctx);  // 0x27F2E0
void sub_27F2F0(EEContext& ctx);  // 0x27F2F0
void sub_27F3E0(EEContext& ctx);  // 0x27F3E0
void sub_27F410(EEContext& ctx);  // 0x27F410
void sub_27F530(EEContext& ctx);  // 0x27F530
void sub_27F650(EEContext& ctx);  // 0x27F650
void sub_27F680(EEContext& ctx);  // 0x27F680
void sub_27F6D0(EEContext& ctx);  // 0x27F6D0
void sub_27F710(EEContext& ctx);  // 0x27F710
void sub_27F730(EEContext& ctx);  // 0x27F730
void sub_27F770(EEContext& ctx);  // 0x27F770
void sub_27F790(EEContext& ctx);  // 0x27F790
void sub_27F7C0(EEContext& ctx);  // 0x27F7C0
void sub_27F930(EEContext& ctx);  // 0x27F930
void sub_27FC80(EEContext& ctx);  // 0x27FC80
void sub_27FCF0(EEContext& ctx);  // 0x27FCF0
void sub_27FD70(EEContext& ctx);  // 0x27FD70
void sub_27FD90(EEContext& ctx);  // 0x27FD90
void sub_27FE70(EEContext& ctx);  // 0x27FE70
void sub_27FE90(EEContext& ctx);  // 0x27FE90
void sub_27FFB0(EEContext& ctx);  // 0x27FFB0
void sub_281270(EEContext& ctx);  // 0x281270
void sub_281290(EEContext& ctx);  // 0x281290
void sub_2812B0(EEContext& ctx);  // 0x2812B0
void sub_2813D0(EEContext& ctx);  // 0x2813D0
void sub_2819B0(EEContext& ctx);  // 0x2819B0
void sub_2819D0(EEContext& ctx);  // 0x2819D0
void sub_281AB0(EEContext& ctx);  // 0x281AB0
void sub_281E60(EEContext& ctx);  // 0x281E60
void sub_281E80(EEContext& ctx);  // 0x281E80
void sub_282130(EEContext& ctx);  // 0x282130
void sub_282190(EEContext& ctx);  // 0x282190
void sub_282290(EEContext& ctx);  // 0x282290
void sub_2822B0(EEContext& ctx);  // 0x2822B0
void sub_282380(EEContext& ctx);  // 0x282380
void sub_282620(EEContext& ctx);  // 0x282620
void sub_282650(EEContext& ctx);  // 0x282650
void sub_282C30(EEContext& ctx);  // 0x282C30
void sub_282C60(EEContext& ctx);  // 0x282C60
void sub_282CD0(EEContext& ctx);  // 0x282CD0
void sub_283510(EEContext& ctx);  // 0x283510
void sub_283BA0(EEContext& ctx);  // 0x283BA0
void sub_283C00(EEContext& ctx);  // 0x283C00
void sub_283C50(EEContext& ctx);  // 0x283C50
void sub_283FE0(EEContext& ctx);  // 0x283FE0
void sub_284170(EEContext& ctx);  // 0x284170
void sub_284190(EEContext& ctx);  // 0x284190
void sub_2841E0(EEContext& ctx);  // 0x2841E0
void sub_284200(EEContext& ctx);  // 0x284200
void sub_284330(EEContext& ctx);  // 0x284330
void sub_284350(EEContext& ctx);  // 0x284350
void sub_2843C0(EEContext& ctx);  // 0x2843C0
void sub_2843E0(EEContext& ctx);  // 0x2843E0
void sub_284450(EEContext& ctx);  // 0x284450
void sub_2845E0(EEContext& ctx);  // 0x2845E0
void sub_284600(EEContext& ctx);  // 0x284600
void sub_284670(EEContext& ctx);  // 0x284670
void sub_2848E0(EEContext& ctx);  // 0x2848E0
void sub_284900(EEContext& ctx);  // 0x284900
void sub_284980(EEContext& ctx);  // 0x284980
void sub_284B50(EEContext& ctx);  // 0x284B50
void sub_284B70(EEContext& ctx);  // 0x284B70
void sub_284BE0(EEContext& ctx);  // 0x284BE0
void sub_284C70(EEContext& ctx);  // 0x284C70
void sub_284C90(EEContext& ctx);  // 0x284C90
void sub_284CF0(EEContext& ctx);  // 0x284CF0
void sub_287400(EEContext& ctx);  // 0x287400
void sub_287490(EEContext& ctx);  // 0x287490
void sub_287510(EEContext& ctx);  // 0x287510
void sub_287580(EEContext& ctx);  // 0x287580
void btlUnitCreate(EEContext& ctx);  // 0x2875A0
void sub_2889C0(EEContext& ctx);  // 0x2889C0
void sub_288F80(EEContext& ctx);  // 0x288F80
void sub_289650(EEContext& ctx);  // 0x289650
void btlActionCreate(EEContext& ctx);  // 0x299E90
void btlActionUpdateAll(EEContext& ctx);  // 0x299FB0
void sub_29A140(EEContext& ctx);  // 0x29A140
void sub_29A750(EEContext& ctx);  // 0x29A750
void sub_29ABE0(EEContext& ctx);  // 0x29ABE0
void sub_29AC70(EEContext& ctx);  // 0x29AC70
void sub_29AE40(EEContext& ctx);  // 0x29AE40
void nullsub_13(EEContext& ctx);  // 0x29DFB0
void sub_29E370(EEContext& ctx);  // 0x29E370
void sub_29E390(EEContext& ctx);  // 0x29E390
void sub_29E3C0(EEContext& ctx);  // 0x29E3C0
void sub_29E400(EEContext& ctx);  // 0x29E400
void sub_29E420(EEContext& ctx);  // 0x29E420

}  // namespace p3fes::game
