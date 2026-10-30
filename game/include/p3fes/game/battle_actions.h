// The big battle state bodies, hand-decompiled from SLUS_216.21 (docs/ANALYSIS/21_battle.md sections 1.2-1.3): the
// btlMain states of the 20-row table 0x693760 and the btlAction states of the 36-row table sBtlActionTbl 0x693410 that
// the battle_task slice left for a dedicated pass. Phase 5 slice `battle_actions`; game/src/battle/battle_actions.cpp,
// pair tests tests/game/test_battle_actions.cpp.
//
// Names: as symbols/functions.json gives them now. The `sub_<addr>` rows carry a proposed name in brackets (ours, from
// the state table row they sit in: row k = {init, update, "NAME"}, obs).
//
// Every function here is register-faithful at each check point, call and return (docs/PHASE5_AGENT_BRIEF.md, the
// wave-6 / wave-7 lessons): each body runs on a Cpu view of the guest context (one variable per GPR, the prologue spills
// written to the guest stack, every scratch register holding the original's value whenever a callee, a check point or
// the caller can see it; callees through their generated entry points with $ra = the original link). The structure
// offsets the bodies use are named below; what each state does is documented at its body in the .cpp.
#pragma once

#include "p3fes/ee_context.h"
#include "p3fes/game/battle_task.h"

namespace p3fes::game {

namespace btl_act {
using namespace btl_task;
// --- gBtl fields used by these bodies (beyond battle_task.h; obs from the instructions) ----------------------------
inline constexpr u32 kFlags2Win = 2;            // gBtl+16 bit 1: the battle ended with the "ENEMY DEAD" pass
inline constexpr u32 kFlagLoading = 0x100000;   // gBtl+12 bit 20: unit models still loading (UNIT_LOAD)
inline constexpr u32 kFlagOver = 0x80;          // gBtl+12 bit 7: battle over (btlMainCheckBattleEnd)
// The per-side btlUnit lists (side 0 party, 1 enemies; heads 8 bytes apart): A at +340 + 8 * side along +2608 (comm_ai /
// battle_task use side 0's), B at +336 + 8 * side along +2612 (UNIT_LOAD walks the enemies', END the party's).
inline constexpr u32 kSideListB = 336;          // u32[2] (stride 8)
inline constexpr u32 kSideListA = 340;          // u32[2] (stride 8) = battle_task's kUnitList for side 0
inline constexpr u32 kUnitNextB = 2612;         // u32: btlUnit next in its B list
inline constexpr u32 kActNextInList = 1192;     // u32: btlAction next in gBtl+332's list
inline constexpr u32 kAdvantage = 26;           // u16: the advantage result of sub_2D50C0 (0 normal, 1 / 2)
inline constexpr u32 kPartyCount = 2980;        // u8: party members created (UNIT_CREATE)
inline constexpr u32 kSetupFlags = 2984;        // u16: the setup block's flags (+0): 4 order shuffle, 8 distress roll
inline constexpr u32 kSetupParty = 2988;        // u32[4]: the setup block's party records (+4; record +4 -> DatUnit)
inline constexpr u32 kSetupEnemies = 3004;      // u32: the setup block's enemy group (+20): +4 six 60-byte DatUnits,
                                                //      +8 the ENCOUNT record index
inline constexpr s32 kGpEnemyTbl = -18648;      // gp slot of the ENEMY table (232-byte records; +34 s16)
inline constexpr s32 kGpEncountTbl = -18504;    // gp slot of the ENCOUNT table (28-byte records; +0 flags)
inline constexpr u32 kUnitModel = 2548;         // u32: btlUnit: its model (sub_316910; 0 = not resident yet)
inline constexpr u32 kCameraTbl = 3108;         // u32[]: the battle camera records (sub_28A540 picks indices)
inline constexpr u32 kResultFlags = 3104;       // u32: bits 0..3 -> flags 4097..4100 after a won battle (END)
// --- btlAction fields beyond battle_task.h --------------------------------------------------------------------------
inline constexpr u32 kActTarget = 56;           // u32[]: the chosen targets (btlActions; the record sub_2D15A0 resets)
inline constexpr u32 kActTargetCount = 106;     // u16: how many
inline constexpr u32 kActSkill = 110;           // u16: the skill / item of the chosen command
inline constexpr u32 kActCandidates = 136;      // u32[]: the target cursor's candidates (sub_2BFCB0 / sub_2BFF60 fill it)
inline constexpr u32 kActCandidateCount = 192;  // u16: how many
inline constexpr u32 kActWait = 1156;           // u16: frames a refused command waits (COMMAND)
inline constexpr u32 kActWaitOn = 1160;         // u32: 1 while that wait runs
inline constexpr u32 kUnitPanelSlot = 168;      // u32: the btlUnit's slot in the battle panel (the target cursor)
// --- SKILL.TBL (44-byte records at *(gp-18680)) -------------------------------------------------------------------
inline constexpr s32 kGpSkillTbl = -18680;
inline constexpr u32 kSkillTarget = 8;          // u8: 1 / 2 = a whole side; +9 / +10 the side arguments of sub_2BFCB0
// --- pad words (the gPads record at 0x7E0940) ---------------------------------------------------------------------
inline constexpr u32 kPadHeld1 = 0x7E094C;      // u16: buttons held (pad 1); bit 3 opens the command menu's help
inline constexpr u32 kPadHeld2 = 0x7E0956;      // u16: the same word of the second record
inline constexpr u32 kPadPressed1 = 0x7E094E;   // u16: buttons newly pressed (pad 1): bit 5 cancel, bit 6 confirm
inline constexpr u32 kPadPressed2 = 0x7E0958;   // u16: the same word of the second record
// --- btl packets (the queued records sub_27ED20 links at gBtl+372; obs from the writers) ----------------------------
inline constexpr u32 kPktWaitKind0 = 0;         // u8: first dependency (4 / 5 / 11: after the packet +8 names)
inline constexpr u32 kPktWaitId0 = 8;           // u64: the id (+88) of the packet waited for
inline constexpr u32 kPktWaitKind1 = 16;        // u8: second dependency; a third at +32 / +40
inline constexpr u32 kPktWaitId1 = 24;          // u64
inline constexpr u32 kPktTime = 72;             // u16: a frame / ordering word (the btlMain states copy their +12 here)
inline constexpr u32 kPktId = 88;               // u64: the packet's own id
inline constexpr u32 kPktOwner = 96;            // u64: the uid of the action the packet belongs to
}  // namespace btl_act

// --- btlMain states (0x693760; $a0 = gBtl + 692, the state record) -----------------------------------------------
// Each takes the state record in $a0 and returns the next state in $v0 (0 = stay) where the original does.

// 0x29C110 UNIT_LOAD update: waits for the genus models (datUnitIsGenusReady) and the queues; then -> START (6).
u32 btlMainUpdateStateUnitLoad(EEContext& ctx, u32 state);
// 0x29CCD0 REVIVAL update: once the current actor's packets have run, the revival item is used up and the battle
// goes back to ACTION (7).
u32 btlMainUpdateStateRevival(EEContext& ctx, u32 state);
// 0x29CE90 WIN init: the victory poses of the surviving party and the victory camera / sound / message packets.
void btlMainInitStateWin(EEContext& ctx, u32 state);
// 0x29BE40 UNIT_LOAD init: the appearance of every btlUnit as chains of dependent packets (load, entry camera, appear
// motion), then the battle start and music packets.
void btlMainInitStateUnitLoad(EEContext& ctx, u32 state);
// 0x29D870 END init: the end-of-battle HP/SP passives (606 full, 605 + 8 %), the result flags 4097..4100, the buffs
// cleared, the party records' +16 byte, every btlAction to EXIT (34).
void btlMainInitStateEnd(EEContext& ctx, u32 state);
// 0x29C700 REVIVAL init: the revival item's scene (camera, effect 439, every party unit revived to full HP/SP with its
// recovery numbers) as chains of dependent packets.
void btlMainInitStateRevival(EEContext& ctx, u32 state);
// 0x29D1F0 CONDITION init: the party's daily condition after the battle (the first character whose condition changes,
// and its scene).
void btlMainInitStateCondition(EEContext& ctx, u32 state);
// 0x29B280 UNIT_CREATE init: the party's and the enemies' btlActions / btlUnits, the formation, the advantage roll
// and the enemies' distress roll.
void btlMainInitStateUnitCreate(EEContext& ctx, u32 state);
// 0x29B760 UNIT_CREATE update: once the queues are empty, the units' home positions, the party's walk-in, the side
// passives' auto-buffs; -> UNIT_LOAD (5).
u32 btlMainUpdateStateUnitCreate(EEContext& ctx, u32 state);

// --- btlAction states (sBtlActionTbl 0x693410; $a0 = the btlAction) ---------------------------------------------------

// 0x28BD10 [btlActionInitStateCommand] COMMAND init: the command menu opens (turn-to packets, menu camera and sound,
// the panel packets, the target record reset).
void sub_28BD10(EEContext& ctx, u32 action);
// 0x28BF80 [btlActionUpdateStateCommand] COMMAND update: one frame of the command menu; -> TARGET (6), READY (12),
// ANALYZE (7) or AI (9) by the menu's result, or a refused command's 24-frame wait.
void sub_28BF80(EEContext& ctx, u32 action);
// 0x28C310 [btlActionInitStateTarget] TARGET init: the candidates (sub_2BFCB0 / sub_2BFF60 by the SKILL.TBL target
// kind), the cursor on the first one or on the whole side.
void sub_28C310(EEContext& ctx, u32 action);
// 0x28C590 [btlActionUpdateStateTarget] TARGET update: one frame of the target cursor; cancel -> COMMAND (5), confirm
// -> READY (12) (an item -> COMMAND 5), or a refusal.
void sub_28C590(EEContext& ctx, u32 action);
// 0x296890 btlActionUpdateStateEscape ESCAPE update: the escape attempt (the party's roll, the runners' walk-off or
// turn-back as dependent packets); -> PACKET (30).
void btlActionUpdateStateEscape(EEContext& ctx, u32 action);
// 0x28EB50 btlActionUpdateStateAttack ATTACK update: the normal attack's swings, reactions, numbers and cameras as
// dependent packets; -> PACKET (30) or BAD DAMAGE (25).
void btlActionUpdateStateAttack(EEContext& ctx, u32 action);
// 0x290BE0 btlActionUpdateStateSkill SKILL update: a skill / item / persona summon played out as dependent packets
// (cast, effect, per-target hits, numbers, cameras, follow-ups); -> PACKET (30) or the state the result asks for.
void btlActionUpdateStateSkill(EEContext& ctx, u32 action);

}  // namespace p3fes::game
