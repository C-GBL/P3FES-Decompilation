// The battle task / state machine layer, hand-decompiled from SLUS_216.21 (docs/ANALYSIS/21_battle.md sections 1.1-1.4):
// btlStart (the battle's entry: the root "battle" task tree and the setup block), the root task's update and destroy
// callbacks, the btlMain states of the 20-row table at 0x693760 (scene
// set, start, the turn loop's end-of-battle bookkeeping, enemy dead, win, condition, lose, fade out, end, result,
// exit, test, revival message), the btlAction states of the 36-row table sBtlActionTbl 0x693410 (stand-by, the
// move / move-home waits, formation change, assist, event callbacks, endure, persona, packet, end, end-home, exit,
// test and the empty init / update slots), btlActionSetStateWithDelay, and their helpers: the packet-list counters
// of the four btl packet queues and the turn-order list readers. Phase 5 slice `battle_task`;
// game/src/battle/battle_task.cpp, pair tests tests/game/test_battle_task.cpp.
//
// Names: as symbols/functions.json gives them now. The `sub_<addr>` rows carry a proposed name in brackets (ours,
// from the instructions and the state-table rows they sit in; not in any delta). The btlAction state names come from
// the name column of sBtlActionTbl (obs): row k = {init, update, "NAME"}.
//
// Every function here is register-faithful at each check point, call and return (docs/PHASE5_AGENT_BRIEF.md, the
// wave-7 lessons): the prologue's spills are written to the guest stack, the s-registers, $ra and every scratch
// register the original writes hold the original's values whenever a callee, a check point or the caller can see
// them, and the indirect calls (`jalr` through the state tables and the action's event callback) run inside the
// original frame with $v0 = the target and $ra = the original link.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace btl_task {
// --- gBtl (`lw rX, -18692(gp)` = *(u32*)0x7CE3EC) fields used here (obs from the instructions) ----------------------
inline constexpr s32 kGBtlGpOffset = -18692;    // gp-relative slot of gBtl
inline constexpr u32 kFlags = 12;               // u32: bit 0 running, 0x80 battle over (btlMainCheckBattleEnd), 0x400 result
                                                // screen wanted, 0x800 started, 0x80000 enemy-dead pass, 0x400000 an action
                                                // asked for the end, 0x800000 revival offered, 0x8000000 field return started
inline constexpr u32 kFlags2 = 16;              // u32: bit 0 start hook (sub_2FF2D0(3) + sub_2FACC0), bit 1 "ENEMY DEAD" ending
inline constexpr u32 kEndFlags = 24;            // u16: |= 6 / |= 0x20 by the END action state
inline constexpr u32 kOutcome = 28;             // u16: 1 win, 2 lose, 3 escape (gBtl+0x1C, btlMainCheckBattleEnd)
inline constexpr u32 kCurrentAction = 328;      // u32: the acting btlAction (its uid at +0)
inline constexpr u32 kActionList = 332;         // u32: head of the btlAction list (0 = none left)
inline constexpr u32 kUnitList = 340;           // u32: head of the btlUnit list (+2604 DatUnit*, +2608 next)
inline constexpr u32 kPacketQueues = 372;       // u32 heads of the 4 btl packet queues, 8 bytes apart (tails at 368 + 8q;
                                                // sub_27ED20 appends at the tail: packet +124 = next, +128 = previous)
inline constexpr u32 kOrderFlags = 584;         // u16: bit 0 order active, bit 3
inline constexpr u32 kOrderCount = 592;         // u32
inline constexpr u32 kOrderList = 596;          // u32[12]: the turn-order list (btlAction*)
inline constexpr u32 kOrderListNext = 644;      // u32[12]: the next round's list, used first when it has a head
inline constexpr u32 kMainState = 692;          // u32: btlMain state (its address is the state functions' $a0)
inline constexpr u32 kMainPending = 696;        // u32: the pending state btlMainUpdateState enters next
inline constexpr u32 kMainFrames = 700;         // u32: frames in the current state
inline constexpr u32 kReinforceFlags = 2566;    // u16: bit 0 cleared by the REINFORCE action state
inline constexpr u32 kRounds = 2970;            // u16: rounds fought (the result divides the total at +3092 by it)
inline constexpr u32 kTestBattle = 2981;        // u8: 1 = started without a setup block (TEST / MC)
inline constexpr u32 kSetupBlock = 2984;        // 52 bytes: btlStart's setup block (+24 / +26 copied to gBtl+580 / +582)
inline constexpr u32 kSetupField = 580;         // u16 x 2: the field / room ids of the setup block
inline constexpr u32 kResult = 3036;            // 68-byte result block handed to the result screen (sub_1F1AE0)
inline constexpr u32 kResultIds = 3072;         // u16[]: ids of the surviving units (inside the block)
inline constexpr u32 kResultAlive = 3080;       // u32: survivors
inline constexpr u32 kResultUnits = 3084;       // u32: units counted
inline constexpr u32 kResultTotal = 3092;       // u32: a battle total, averaged over the rounds
inline constexpr u32 kResultExtra = 3096;       // u32: btlGetEncounterId()
inline constexpr u32 kResultRounds = 3100;      // u32: the rounds
inline constexpr u32 kRootChildTask = 3352;     // u32: a kwln task of the battle tree (destroyed with its hierarchy)
inline constexpr u32 kResultTask = 3368;        // u32: the result-screen handle (sub_1F1AE0 / 1B00 / 1B20 / 1B40 / 1B60 / 1C20)
inline constexpr u32 kEndTask = 3372;           // u32: destroyed by the END state

// --- btlAction (1,200 bytes) / btlUnit fields --------------------------------------------------------------------
inline constexpr u32 kActUid = 0;               // u64
inline constexpr u32 kActState = 12;            // u16
inline constexpr u32 kActNext = 14;             // u16 pending state
inline constexpr u32 kActPrev = 16;             // u16 previous state
inline constexpr u32 kActDelay = 18;            // u16 countdown to the pending state
inline constexpr u32 kActReturn = 20;           // u16 the state to go back to
inline constexpr u32 kActFlags = 24;            // u16
inline constexpr u32 kActFlags2 = 26;           // u16: bit 0 a combatant
inline constexpr u32 kActFrames = 28;           // u32
inline constexpr u32 kActUnit = 48;             // u32: btlUnit*
inline constexpr u32 kActMoveKind = 108;        // u16: 1 attack, 2/3 skill, 9 summon
inline constexpr u32 kActCommand = 1120;        // u16: the command / skill id (571, 572: the endure skills)
inline constexpr u32 kActHome = 1156;           // u32: 1 = walk home (END HOME) / analyze flag
inline constexpr u32 kActEventReturn = 1180;    // u16: the state after the event callback
inline constexpr u32 kActEventFn = 1184;        // u32: the EVENT state's callback (returns 0 when done)
inline constexpr u32 kUnitFlags = 156;          // u32 btlUnit flags: 0x1 dead, 0x8 reinforced, 0x10 endure
inline constexpr u32 kUnitSide = 162;           // u8: 0 party, 1 enemy
inline constexpr u32 kUnitDat = 2604;           // u32: DatUnit*
inline constexpr u32 kUnitNext = 2608;          // u32: next btlUnit

inline constexpr u32 kActionStateTbl = 0x693410u;  // sBtlActionTbl: 36 x {init, update, name}
inline constexpr u32 kMainStateTbl = 0x693760u;    // sBtlMainStateTbl: 20 x {init, update, name}
}  // namespace btl_task

// --- the root task (0x27C000 band) --------------------------------------------------------------------------------
u64 btlStart(EEContext& ctx, u64 setup);           // 0x27D1D0: gBtl, the task tree, the setup block -> INIT (2) / TEST / MC; the root task
u64 sub_27D560(EEContext& ctx);                    // [btlCanRevive] revival offered and sub_2BFC90 -> the actor's DatUnit has effect 4040
u64 btlUpdateTask(EEContext& ctx);                 // 0x27CC30: the "battle" task: per-frame drivers while running, else teardown; 0
void btlDestroyTask(EEContext& ctx);               // 0x27CDF0: sub_27D020 (the battle teardown)
void sub_27CE10(EEContext& ctx);                   // [btlDestroyRootChildren] the named task exists -> destroy gBtl+3352's hierarchy
u64 sub_27E410(EEContext& ctx);                    // [btlPacketCountAll] packets queued in the four queues
u64 sub_27E470(EEContext& ctx, u64 type);          // [btlPacketCountOfType] queued packets whose +64 word is `type`
void sub_27E4D0(EEContext& ctx);                   // [btlPacketMarkAll] every packet with byte +71 bit 0 gets bit 2

// --- btlAction states (sBtlActionTbl 0x693410) ------------------------------------------------------------------
void sub_28A990(EEContext& ctx);                   // [btlActionInitStateNon] empty
void sub_28A9A0(EEContext& ctx);                   // [btlActionUpdateStateNon] empty
void sub_28A9B0(EEContext& ctx);                   // [btlActionInitStateStandBy] empty
void sub_28A9C0(EEContext& ctx);  // [register ABI] [btlActionUpdateStateStandBy] endure -> 22, dead -> 33
void sub_28B9C0(EEContext& ctx);  // [register ABI] [btlActionUpdateStateStartHome] after the walk: home packet, -> return state
void sub_28BCA0(EEContext& ctx);  // [register ABI] [btlActionUpdateStateChangeFormation] no packet left -> START (2)
void sub_28C9F0(EEContext& ctx);  // [register ABI] [btlActionInitStateAnalyze] +1156 = 1
void sub_28D070(EEContext& ctx);                   // [btlActionInitStateSupport] empty
void sub_28DBE0(EEContext& ctx);                   // [btlActionInitStateReady] empty
void sub_28E740(EEContext& ctx);  // [register ABI] [btlActionUpdateStateMoveTarget] after the walk: ATTACK / SKILL / SUMMON / NON
void sub_28EA90(EEContext& ctx);  // [register ABI] [btlActionUpdateStateMoveHome] the same body (MOVE HOME row)
void sub_28EB40(EEContext& ctx);                   // [btlActionInitStateAttack] empty
void sub_290BD0(EEContext& ctx);                   // [btlActionInitStateSkill] empty
void sub_294D10(EEContext& ctx);  // [register ABI] [btlActionInitStateReinforce] unit flag 8, gBtl+2566 bit 0 off
void sub_295150(EEContext& ctx);                   // [btlActionInitStateSummon] empty
void sub_295B20(EEContext& ctx);  // [register ABI] [btlActionUpdateStateAssist] no 1286 / 2048 packets -> flag 0x100, READY (12)
void sub_295B90(EEContext& ctx);                   // [btlActionInitStateEvent] empty
void sub_295BA0(EEContext& ctx);  // [register ABI] [btlActionUpdateStateEvent] the +1184 callback until it returns 0, then +1180
void sub_295BF0(EEContext& ctx);                   // [btlActionInitStateError] empty
void sub_295F00(EEContext& ctx);  // [register ABI] [btlActionInitStateEndure] endure flag off, skill 571/572 marks, no command -> 1
void sub_296310(EEContext& ctx);                   // [btlActionInitStateWait] empty
void sub_296880(EEContext& ctx);                   // [btlActionInitStateEscape] empty
void sub_2976D0(EEContext& ctx);  // [register ABI] [btlActionUpdateStatePersona] no packet left -> party flag 0x400 off, return state
void sub_297750(EEContext& ctx);                   // [btlActionInitStateBadDamage] empty
void sub_2990F0(EEContext& ctx);                   // [btlActionInitStatePacket] empty
void sub_299100(EEContext& ctx);  // [register ABI] [btlActionUpdateStatePacket] no packet left -> END (31)
void sub_299170(EEContext& ctx);  // [register ABI] [btlActionInitStateEnd] end requests to gBtl, the end event or the flag clean-up
void sub_299760(EEContext& ctx);  // [register ABI] [btlActionUpdateStateEndHome] after the walk: home packet when +1156, -> STANDBY
void sub_299AA0(EEContext& ctx);  // [register ABI] [btlActionInitStateExit] a reinforced combatant: flag off, sub_1FDD40
void sub_299D20(EEContext& ctx);                   // [btlActionInitStateTest] empty
void sub_299D30(EEContext& ctx, u64 action);       // [btlActionUpdateStateTest] -> COMMAND (5)
void btlActionSetStateWithDelay(EEContext& ctx);  // [register ABI] 0x299DB0: now, or pending after `delay`

// --- the turn-order list ------------------------------------------------------------------------------------------
u64 sub_29AD20(EEContext& ctx);                    // [btlOrderGetFirst] next round's head, else this round's
u64 sub_29AD50(EEContext& ctx);                    // [btlOrderGetCount] gBtl+592
u64 sub_29AD60(EEContext& ctx, u64 index);         // [btlOrderGetAction] slot `index` (< 12) of the order list, else 0
u64 sub_29ADA0(EEContext& ctx, u64 index);         // [btlOrderGetUnit] that action's btlUnit, or 0
u64 sub_29ADF0(EEContext& ctx, u64 action);        // [btlOrderNextContains] 1 when the next round's list holds `action`
void sub_29B090(EEContext& ctx);                   // [btlOrderReset] the 108-byte order block gBtl+584 zeroed
void sub_29B040(EEContext& ctx);                   // [btlOrderActivate] gBtl+584 |= 8 | 1
void sub_29B070(EEContext& ctx);                   // [btlOrderDeactivate] gBtl+584 &= ~1
void sub_29B0C0(EEContext& ctx);  // [register ABI] [btlActionIsNotFlag4] (action+24 & 4) == 0

// --- btlMain states (0x693760) ------------------------------------------------------------------------------------
void btlMainInitStateNon(EEContext& ctx);          // 0x29B0E0
u64 btlMainUpdateStateNon(EEContext& ctx);         // 0x29B0F0: 0
void btlMainInitStateInit(EEContext& ctx);         // 0x29B100: sound banks, boss setup, sub_17B180(1)
u64 btlMainUpdateStateInit(EEContext& ctx);        // 0x29B160: -> SCENE_SET (3)
void btlMainInitStateSceneSet(EEContext& ctx);     // 0x29B170: sub_29E390 (scene load)
u64 btlMainUpdateStateSceneSet(EEContext& ctx);    // 0x29B190: scene ready, queues empty -> three setup packets, -> UNIT_CREATE (4)
void btlMainInitStateStart(EEContext& ctx);        // 0x29C250
u64 btlMainUpdateStateStart(EEContext& ctx);       // 0x29C290: everything idle -> order active, flag 0x800, -> ACTION (7)
void btlMainInitStateAction(EEContext& ctx);       // 0x29C330
u64 btlMainUpdateStateAction(EEContext& ctx);      // 0x29C340: battle over -> result block, -> 8 / 10 / 11 / 13 / 14
void btlMainInitStateEnemyDead(EEContext& ctx);    // 0x29CDE0: sub_2FB690, flag 0x80000
u64 btlMainUpdateStateEnemyDead(EEContext& ctx);   // 0x29CE20: queues empty -> flag off, -> FADE_OUT (14) or ACTION (7)
void btlMainUpdateStateWin(EEContext& ctx);  // [register ABI] 0x29D0D0: the victory pose (skippable by pad), -> CONDITION (12)
u64 btlMainUpdateStateCondition(EEContext& ctx);   // 0x29D6E0: queues empty -> FADE_OUT (14)
void btlMainInitStateLose(EEContext& ctx);         // 0x29D720
void btlMainUpdateStateLose(EEContext& ctx);  // [register ABI] 0x29D730: 31 frames -> FADE_OUT (14)
void btlMainInitStateFadeOut(EEContext& ctx);      // 0x29D760: flag 0x800 off; lose: the screen fade; else the result fade
u64 btlMainUpdateStateFadeOut(EEContext& ctx);     // 0x29D800: fade done -> END (15)
u64 btlMainUpdateStateEnd(EEContext& ctx);         // 0x29DB60: no actions left -> teardown, -> RESULT (16) or EXIT (17)
void btlMainInitStateResult(EEContext& ctx);       // 0x29DBF0: sub_1F1B60(result task)
u64 btlMainUpdateStateResult(EEContext& ctx);      // 0x29DC20: field return once, result closed -> EXIT (17)
void btlMainInitStateExit(EEContext& ctx);         // 0x29DCF0: mark the packets, field return once
u64 btlMainUpdateStateExit(EEContext& ctx);        // 0x29DD50: everything idle -> sub_2DCF10, running flag off; 0
void btlMainInitStateTest(EEContext& ctx);         // 0x29DDB0
u64 btlMainUpdateStateTest(EEContext& ctx);        // 0x29DDC0: sub_10A4E0(0, 0, 3, 0), sub_2FF260(0), -> INIT (2)
void btlMainInitStateMc(EEContext& ctx);           // 0x29DE00
u64 btlMainUpdateStateMc(EEContext& ctx);          // 0x29DE10: 0
void btlMainSetStateNon(EEContext& ctx);           // 0x29DF40: state NON (1) entered, pending cleared
void btlMainInitStateRevivalMes(EEContext& ctx);   // 0x29C5D0: the revival question window + message packets
u64 btlMainUpdateStateRevivalMes(EEContext& ctx);  // 0x29C680: answer -> REVIVAL (9) or flag off, ACTION (7)

}  // namespace p3fes::game
