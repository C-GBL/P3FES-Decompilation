// The battle code, seventh pass (slice battle7; docs/ANALYSIS/21_battle.md): siblings of the still-recompiled
// functions of 0x290000-0x2FFFFF that the replay routes reach, with the relaxed callee rule (a still-recompiled callee is
// reached through its gen:: entry point). game/src/battle/battle7_{ai,voice,cutin,action,camera}.cpp; the bodies come
// from p3fes_handgen (register ABI: arguments in $a0.., the result in $v0), with the record offsets named below
// (battle3.h's b3::, battle4.h's b4:: and battle5.h's b5:: records reused) and each function's role given. Names:
// functions.json's in code, ours in brackets in the comments (ADR-0009); the AI rows' bracketed names are built from
// the condition / target tables' own strings. Confirmed record fields: tools/ours/types/deltas/battle7.json.
//
// Reach (a temporary first-call probe, six routes: dorm, m1, battle, fusion, shop, the full climb): 19 of the 371
// still-recompiled functions of the band ran, 15 of them stood in by other slices' tests; taken from the reached set:
// sub_298610 (ROUNDUP), sub_2DEFE0 (a voice picker), sub_2E2920 / sub_2E2A60 (the voice bank and line packets, 1,358
// calls); the rest are their unreached siblings in the same files (the AI rows run only for enemies without an AI
// script, which no route meets).
//
// Groups:
//   * ai: the AI conditions (table 0x6971B0, 12-byte rows {fn, name, flag}: MYHP .. MYHOJO) and target selectors
//     (0x6975E0, 8-byte rows {fn, name}: AI .. NOTHOJO) -- most of them sub_2C1080 [btlAIAnyUnit] / sub_2C3430
//     [btlAIPickTarget] with a side mask, a status mask, filters and a predicate; the predicates (affinity bits:
//     0x1000000 null, 0x2000000 repel, 0x4000000 drain, 0x8000000 weak); the weighted target pick, the healing-item
//     pick, the command decode for units without a script, two AI COMM handlers, the AI script packets;
//   * voice: the party voice pickers (0x697C10, by situation; each returns the acting member's line or -1), the
//     navigator line pickers (0x6978F0), the voice bank / voice line packets, the sound and motion packets, the support
//     events and the analysed-enemy navigator line;
//   * cutin: the cut-in / special effect packets and the action-end boss hook;
//   * action: ROUNDUP (the all-out attack), the help window, the command panel's help lines, the camera script
//     commands, kill / revive, poison damage, the ailment lines, the boss archive files, a unit's cell position;
//   * camera: camera shot callbacks (boss shots, target shots).
//
// THE BATTLE STATE A CO-OP SERVER WOULD OWN (additions to battle3.h / battle4.h / battle5.h's lists)
//   * the AI decisions: the conditions only read the battle state (HP, statuses, affinities, levels, turn counts), but
//     the selectors and the command decode draw from datCalcRand -- a server has to run them (or ship the drawn target)
//     so that every client sees the same target.
//   * kill / revive (sub_2D7890) and the poison damage (sub_2DC670) change DatUnits: server logic.
//   * the voice / navigator lines, the cut-ins, the help window and the camera shots are presentation; the voice and
//     navigator pickers draw from the shared random stream or sub_357FD0, so clients must agree on which of them run.

#pragma once

#include "p3fes/ee_context.h"
#include "p3fes/game/battle3.h"
#include "p3fes/game/battle4.h"
#include "p3fes/game/battle5.h"

namespace p3fes::game {

namespace b7 {

// AI table geometry (the condition / target tables of btlAICommand.c; comm_ai.h has the same numbers)
inline constexpr u32 kAiCondTable = 0x6971B0u;    // {u32 fn, u32 name, u32 flag}[72]
inline constexpr u32 kAiTargetTable = 0x6975E0u;  // {u32 fn, u32 name}[37]
inline constexpr u32 kVoicePickers = 0x697C10u;   // fn(action, arg, arg) -> line or -1, by situation (27 rows)
inline constexpr u32 kNaviPickers = 0x6978F0u;    // fn(action) -> line or -1 (32 rows)
inline constexpr u32 kAffinityNull = 0x1000000u, kAffinityRepel = 0x2000000u, kAffinityDrain = 0x4000000u,
                     kAffinityWeak = 0x8000000u;

// --- gBtl additions (b3::gbtl, b4::gbtl4, b5::gbtl5 have the rest) -----------------------------------------------------
namespace gbtl7 {
inline constexpr s32 kCamera = 32;          // the battle camera work (sub_2A2290 / sub_2A3110 take gBtl + 32; the camera shot callbacks aim it)
inline constexpr s32 kCamMode = 266;        // u16: the target camera mode (0 / 1: sub_2B1060 / sub_2B17A0)
inline constexpr s32 kSupportUid = 2568;    // u32: the uid of the unit the support event watches (sub_2DB650)
inline constexpr s32 kVoiceReady = 2806;    // u16: bit 0 the party voice bank is loaded (sub_2E2920) -- the voice line packets wait for it
inline constexpr s32 kVoiceBuf = 2812;      // u32: the party voice bank buffer (RwMalloc 0x40000, alignment 2764)
inline constexpr s32 kBossActEndHook = 2828;  // fn(arg) -> u32: the pending boss hook sub_2E43A0 runs at an action end (cleared when it returns 0)
inline constexpr s32 kCamLastTarget = 2932; // u32: the target action the last boss camera shot framed (sub_2E76A0)
inline constexpr s32 kCamSideShot = 2936;   // u16: 1 the boss camera took the side shot (sub_2E70B0)
inline constexpr s32 kHelpWindow = 2976;    // u32: the battle help window (sub_3A4220 / sub_1FEA10 write its text)
}  // namespace gbtl7

// --- a camera shot (the shot callbacks' $a0) ---------------------------------------------------------------------------
namespace shot {
inline constexpr s32 kPoint = 156;          // f32[3]: the shot's look-at point
inline constexpr s32 kAction = 224;         // u32: the btlAction the shot follows
inline constexpr s32 kTarget = 256;         // u32: the target action the shot was set up for
inline constexpr s32 kCalls = 268;          // u16: frames / calls of the shot's update
inline constexpr s32 kTargetCopy = 284;     // u32: the action's first target, copied at the shot start (sub_2B1BC0)
inline constexpr s32 kMotionUnit = 288;     // u32: a unit whose motion the shot plays (sub_2E87B0)
inline constexpr s32 kMotion = 292;         // u16: that motion
}  // namespace shot

// --- a unit's model object additions (btlUnit + 2548; b5::mdl) ---------------------------------------------------------
namespace mdl7 {
inline constexpr s32 kMotionPlayer = 1016;  // the motion player sub_31F6D0 plays a motion on (the motion packet sub_2DD7D0)
inline constexpr s32 kVoiceFlags = 1022;    // u16: bit 0x20 set while the unit's voice line plays (the voice line packet sub_2E2A60)
}  // namespace mdl7

}  // namespace b7

// --- group ai (battle7_ai.cpp; register ABI: arguments in $a0.., the result in $v0) --------------------
// 0x2C08B0 [btlAIRecCopyUid] Copies the chosen candidate's uid (u64 +48) of one AI target record into another.
void sub_2C08B0(EEContext& ctx);
// 0x2C08C0 [btlAIRecFindAction] The live combatant (active, placed, not dead -- or without a DatUnit) whose uid equals the AI
//   record's chosen uid (+48), walking gBtl's action list; 0 when none.
void sub_2C08C0(EEContext& ctx);
// 0x2C0A50 Points the AI target record of the action of uid a1's unit at the action of uid a1: finds the unit (sub_289030),
//   its action (sub_29A1D0) and copies the action's uid into the record +184 of the first action.
void sub_2C0A50(EEContext& ctx);
// 0x2C1360 [btlAIPredHpAbove] AI predicate: the action's unit has at least a1 percent of its max HP (max HP * a1 <= 100 * HP)
//   -- the predicate of ENHP_O.
void sub_2C1360(EEContext& ctx);
// 0x2C1440 [btlAICond_FRHP] AI condition 3 FRHP: whether any living combatant of the acting unit's side satisfies: its HP is
//   at most param percent of its max HP (100 * HP <= max HP * param) -- btlAIAnyUnit (sub_2C1080) with the status mask
//   0x80000, filters 0 and the predicate sub_2C12F0.
void sub_2C1440(EEContext& ctx);
// 0x2C1490 [btlAICond_ENHP] AI condition 4 ENHP: whether any living combatant of the other side satisfies: its HP is at most
//   param percent of its max HP (100 * HP <= max HP * param) -- btlAIAnyUnit (sub_2C1080) with the status mask 0x80000,
//   filters 0 and the predicate sub_2C12F0.
void sub_2C1490(EEContext& ctx);
// 0x2C14F0 [btlAICond_ENHP_O] AI condition 5 ENHP_O: whether any living combatant of the other side satisfies: its HP is at
//   least param percent of its max HP (max HP * param <= 100 * HP) -- btlAIAnyUnit (sub_2C1080) with the status mask
//   0x80000, filters 0 and the predicate sub_2C1360.
void sub_2C14F0(EEContext& ctx);
// 0x2C1550 [btlAICond_MYLV_O] AI condition 6 MYLV_O: the acting unit's level (datCalcGetLevel) is at least the parameter.
void sub_2C1550(EEContext& ctx);
// 0x2C15E0 [btlAICond_ENLV_O] AI condition 8 ENLV_O: the mean level of the other side's living units (btlGetMeanLevel, status
//   mask 0x80000) is at least the parameter.
void sub_2C15E0(EEContext& ctx);
// 0x2C1740 [btlAICond_FRBAD] AI condition 12 FRBAD: whether a combatant of the acting unit's side has the bad status param --
//   sub_2C1080 with the predicate sub_2C1710 and the status mask 0x80000 (living units only), or 0 when the param
//   itself asks for the dead status 0x80000.
void sub_2C1740(EEContext& ctx);
// 0x2C1850 [btlAICond_ENBAD_ALL] AI condition 14 ENBAD_ALL: every living combatant of the other side has the bad status param
//   (the walk stops at the first one without it; true when it reaches the end).
void sub_2C1850(EEContext& ctx);
// 0x2C1960 [btlAICond_FRID] AI condition 15 FRID: an ally (same side, not the acting action, not dead) has the unit id param.
void sub_2C1960(EEContext& ctx);
// 0x2C1A30 [btlAICond_ENID] AI condition 16 ENID: a living unit of the other side has the unit id param.
void sub_2C1A30(EEContext& ctx);
// 0x2C1B10 [btlAICond_FRHOJO] AI condition 17 FRHOJO: a living ally (not the acting action) has the support effect param
//   (sub_301CA0).
void sub_2C1B10(EEContext& ctx);
// 0x2C1BF0 [btlAICond_ENHOJO] AI condition 18 ENHOJO: a living unit of the other side has the support effect param
//   (sub_301CA0).
void sub_2C1BF0(EEContext& ctx);
// 0x2C1D80 [btlAICond_SUMMON] AI condition 20 SUMMON: always false (returns 0).
void sub_2C1D80(EEContext& ctx);
// 0x2C1E50 [btlAICond_MYKYUSYU] AI predicate (condition 23 MYKYUSYU): the action's unit drains the element a1 (affinity bit
//   0x4000000).
void sub_2C1E50(EEContext& ctx);
// 0x2C1E90 [btlAICond_MYMUKOU] AI predicate (condition 24 MYMUKOU): the action's unit nullifies the element a1 (affinity bit
//   0x1000000).
void sub_2C1E90(EEContext& ctx);
// 0x2C1F10 [btlAICond_FRHANSYA] AI condition 26 FRHANSYA: whether any living combatant of the acting unit's side satisfies: it
//   repels the element param (affinity bit 0x2000000) -- btlAIAnyUnit (sub_2C1080) with the status mask 0x80000,
//   filters 0 and the predicate sub_2C1E10.
void sub_2C1F10(EEContext& ctx);
// 0x2C1FC0 [btlAICond_FRKYUSYU] AI condition 28 FRKYUSYU: whether any living combatant of the acting unit's side satisfies: it
//   drains the element param (affinity bit 0x4000000) -- btlAIAnyUnit (sub_2C1080) with the status mask 0x80000,
//   filters 0 and the predicate sub_2C1E50.
void sub_2C1FC0(EEContext& ctx);
// 0x2C2010 [btlAICond_ENKYUSYU] AI condition 29 ENKYUSYU: whether any living combatant of the other side satisfies: it drains
//   the element param (affinity bit 0x4000000) -- btlAIAnyUnit (sub_2C1080) with the status mask 0x80000, filters 0 and
//   the predicate sub_2C1E50.
void sub_2C2010(EEContext& ctx);
// 0x2C2070 [btlAICond_FRMUKOU] AI condition 30 FRMUKOU: whether any living combatant of the acting unit's side satisfies: it
//   nullifies the element param (affinity bit 0x1000000) -- btlAIAnyUnit (sub_2C1080) with the status mask 0x80000,
//   filters 0 and the predicate sub_2C1E90.
void sub_2C2070(EEContext& ctx);
// 0x2C20C0 [btlAICond_ENMUKOU] AI condition 31 ENMUKOU: whether any living combatant of the other side satisfies: it nullifies
//   the element param (affinity bit 0x1000000) -- btlAIAnyUnit (sub_2C1080) with the status mask 0x80000, filters 0 and
//   the predicate sub_2C1E90.
void sub_2C20C0(EEContext& ctx);
// 0x2C2120 [btlAICond_FRWEAK] AI condition 32 FRWEAK: whether any living combatant of the acting unit's side satisfies: it is
//   weak to the element param (affinity bit 0x8000000) -- btlAIAnyUnit (sub_2C1080) with the status mask 0x80000,
//   filters 0 and the predicate sub_2C1ED0.
void sub_2C2120(EEContext& ctx);
// 0x2C2170 [btlAICond_ENWEAK] AI condition 33 ENWEAK: whether any living combatant of the other side satisfies: it is weak to
//   the element param (affinity bit 0x8000000) -- btlAIAnyUnit (sub_2C1080) with the status mask 0x80000, filters 0 and
//   the predicate sub_2C1ED0.
void sub_2C2170(EEContext& ctx);
// 0x2C21D0 [btlAICond_MYUSEATTR] AI predicate (condition 34 MYUSEATTR): the element of the action's last skill (+126,
//   datCalcGetSkillElement) is a1.
void sub_2C21D0(EEContext& ctx);
// 0x2C2220 [btlAICond_FRUSEATTR] AI condition 35 FRUSEATTR: whether any living combatant of the acting unit's side satisfies:
//   the element of its last skill (+126) is param -- btlAIAnyUnit (sub_2C1080) with the status mask 0x80000, filters 0
//   and the predicate sub_2C21D0.
void sub_2C2220(EEContext& ctx);
// 0x2C2270 [btlAICond_ENUSEATTR] AI condition 36 ENUSEATTR: whether any living combatant of the other side satisfies: the
//   element of its last skill (+126) is param -- btlAIAnyUnit (sub_2C1080) with the status mask 0x80000, filters 0 and
//   the predicate sub_2C21D0.
void sub_2C2270(EEContext& ctx);
// 0x2C2310 [btlAICond_FRUSESKIL] AI condition 38 FRUSESKIL: whether any living combatant of the acting unit's side satisfies:
//   its last command was an attack / skill (+124 kind 1 / 2) with the id param -- btlAIAnyUnit (sub_2C1080) with the
//   status mask 0x80000, filters 0 and the predicate sub_2C22D0.
void sub_2C2310(EEContext& ctx);
// 0x2C2360 [btlAICond_ENUSESKIL] AI condition 39 ENUSESKIL: whether any living combatant of the other side satisfies: its last
//   command was an attack / skill (+124 kind 1 / 2) with the id param -- btlAIAnyUnit (sub_2C1080) with the status mask
//   0x80000, filters 0 and the predicate sub_2C22D0.
void sub_2C2360(EEContext& ctx);
// 0x2C23C0 [btlAICond_MYGROUP] AI predicate (condition 40 MYGROUP): the action's last skill (+126) targets a group or all
//   (sub_2BFF60 returns 1 or 2).
void sub_2C23C0(EEContext& ctx);
// 0x2C2420 [btlAICond_FRGROUP] AI condition 41 FRGROUP: whether any living combatant of the acting unit's side satisfies: its
//   last skill targets a group (sub_2BFF60 kind 1 or 2) -- btlAIAnyUnit (sub_2C1080) with the status mask 0x80000,
//   filters 0 and the predicate sub_2C23C0.
void sub_2C2420(EEContext& ctx);
// 0x2C2470 [btlAICond_ENGROUP] AI condition 42 ENGROUP: whether any living combatant of the other side satisfies: its last
//   skill targets a group (sub_2BFF60 kind 1 or 2) -- btlAIAnyUnit (sub_2C1080) with the status mask 0x80000, filters 0
//   and the predicate sub_2C23C0.
void sub_2C2470(EEContext& ctx);
// 0x2C24F0 [btlAICond_TURN_O] AI condition 44 TURN_O: the acting unit has taken at least param turns (+32).
void sub_2C24F0(EEContext& ctx);
// 0x2C2510 [btlAICond_MYHREC] AI condition 45 MYHREC: the acting unit knows a usable recovery skill: any skill of its list
//   (below 0x1D0) for which sub_308860 holds.
void sub_2C2510(EEContext& ctx);
// 0x2C25D0 [btlAICond_MORE] AI condition 46 MORE: the action has a "one more" this turn (+40 nonzero).
void sub_2C25D0(EEContext& ctx);
// 0x2C25E0 [btlAICond_FRHANSYA_ST] AI condition 47 FRHANSYA_ST: whether any living, standing (not down) combatant of the
//   acting unit's side satisfies: it repels the element param (affinity bit 0x2000000) -- btlAIAnyUnit (sub_2C1080)
//   with the status mask 0x180000, filters 0 and the predicate sub_2C1E10.
void sub_2C25E0(EEContext& ctx);
// 0x2C2630 [btlAICond_ENHANSYA_ST] AI condition 48 ENHANSYA_ST: whether any living, standing (not down) combatant of the other
//   side satisfies: it repels the element param (affinity bit 0x2000000) -- btlAIAnyUnit (sub_2C1080) with the status
//   mask 0x180000, filters 0 and the predicate sub_2C1E10.
void sub_2C2630(EEContext& ctx);
// 0x2C2690 [btlAICond_FRKYUSYU_ST] AI condition 49 FRKYUSYU_ST: whether any living, standing (not down) combatant of the
//   acting unit's side satisfies: it drains the element param (affinity bit 0x4000000) -- btlAIAnyUnit (sub_2C1080)
//   with the status mask 0x180000, filters 0 and the predicate sub_2C1E50.
void sub_2C2690(EEContext& ctx);
// 0x2C26E0 [btlAICond_ENKYUSYU_ST] AI condition 50 ENKYUSYU_ST: whether any living, standing (not down) combatant of the other
//   side satisfies: it drains the element param (affinity bit 0x4000000) -- btlAIAnyUnit (sub_2C1080) with the status
//   mask 0x180000, filters 0 and the predicate sub_2C1E50.
void sub_2C26E0(EEContext& ctx);
// 0x2C2740 [btlAICond_FRMUKOU_ST] AI condition 51 FRMUKOU_ST: whether any living, standing (not down) combatant of the acting
//   unit's side satisfies: it nullifies the element param (affinity bit 0x1000000) -- btlAIAnyUnit (sub_2C1080) with
//   the status mask 0x180000, filters 0 and the predicate sub_2C1E90.
void sub_2C2740(EEContext& ctx);
// 0x2C2790 [btlAICond_ENMUKOU_ST] AI condition 52 ENMUKOU_ST: whether any living, standing (not down) combatant of the other
//   side satisfies: it nullifies the element param (affinity bit 0x1000000) -- btlAIAnyUnit (sub_2C1080) with the
//   status mask 0x180000, filters 0 and the predicate sub_2C1E90.
void sub_2C2790(EEContext& ctx);
// 0x2C27F0 [btlAICond_FRWEAK_ST] AI condition 53 FRWEAK_ST: whether any living, standing (not down) combatant of the acting
//   unit's side satisfies: it is weak to the element param (affinity bit 0x8000000) -- btlAIAnyUnit (sub_2C1080) with
//   the status mask 0x180000, filters 0 and the predicate sub_2C1ED0.
void sub_2C27F0(EEContext& ctx);
// 0x2C2840 [btlAICond_ENWEAK_ST] AI condition 54 ENWEAK_ST: whether any living, standing (not down) combatant of the other
//   side satisfies: it is weak to the element param (affinity bit 0x8000000) -- btlAIAnyUnit (sub_2C1080) with the
//   status mask 0x180000, filters 0 and the predicate sub_2C1ED0.
void sub_2C2840(EEContext& ctx);
// 0x2C28A0 [btlAICond_MYID] AI predicate (condition 55 MYID): the action's unit id is a1.
void sub_2C28A0(EEContext& ctx);
// 0x2C28C0 [btlAICond_FRALLHP] AI condition 56 FRALLHP: the living units of the acting unit's side have, summed, at most param
//   percent of their summed max HP (sum max HP * param >= 100 * sum HP).
void sub_2C28C0(EEContext& ctx);
// 0x2C29E0 [btlAICond_ENALLHP] AI condition 57 ENALLHP: as FRALLHP over the other side.
void sub_2C29E0(EEContext& ctx);
// 0x2C2C40 [btlAICond_ENWEAK_ST_PAI] AI condition 60 ENWEAK_ST_PAI: whether any living, standing (not down) combatant of the
//   other side satisfies: it is weak to the element param (affinity bit 0x8000000) (not shielded against the element;
//   an enemy whose affinities the party has not analysed is skipped) -- btlAIAnyUnit (sub_2C1080) with the status mask
//   0x180000, filters 6 and the predicate sub_2C1ED0.
void sub_2C2C40(EEContext& ctx);
// 0x2C2CA0 [btlAICond_ENWEAK_DW_PAI] AI condition 61 ENWEAK_DW_PAI: whether any living combatant of the other side satisfies:
//   it is weak to the element param (affinity bit 0x8000000) (downed units only; not shielded against the element; an
//   enemy whose affinities the party has not analysed is skipped) -- btlAIAnyUnit (sub_2C1080) with the status mask
//   0x80000, filters 7 and the predicate sub_2C1ED0.
void sub_2C2CA0(EEContext& ctx);
// 0x2C3150 [btlAICond_ENNOMAL] AI condition 64 ENNOMAL: whether any living combatant of the other side satisfies: the element
//   param may be used on it, the shields counted (sub_2C2ED0) (not shielded against the element; an enemy whose
//   affinities are not analysed counts as a match) -- btlAIAnyUnit (sub_2C1080) with the status mask 0x80000, filters
//   10 and the predicate sub_2C30F0.
void sub_2C3150(EEContext& ctx);
// 0x2C31B0 [btlAICond_ENNOMAL_ST] AI condition 65 ENNOMAL_ST: whether any living, standing (not down) combatant of the other
//   side satisfies: the element param may be used on it, the shields counted (sub_2C2ED0) (not shielded against the
//   element; an enemy whose affinities are not analysed counts as a match) -- btlAIAnyUnit (sub_2C1080) with the status
//   mask 0x180000, filters 10 and the predicate sub_2C30F0.
void sub_2C31B0(EEContext& ctx);
// 0x2C3210 [btlAICond_ENNOMAL_DW] AI condition 66 ENNOMAL_DW: whether any living combatant of the other side satisfies: the
//   element param may be used on it, the shields counted (sub_2C2ED0) (downed units only; not shielded against the
//   element; an enemy whose affinities are not analysed counts as a match) -- btlAIAnyUnit (sub_2C1080) with the status
//   mask 0x80000, filters 11 and the predicate sub_2C30F0.
void sub_2C3210(EEContext& ctx);
// 0x2C3270 [btlAICond_ANALYZE] AI condition 67 ANALYZE: the acting unit is an enemy whose affinities the party has analysed
//   (sub_17B260 on its id).
void sub_2C3270(EEContext& ctx);
// 0x2C32C0 [btlAICond_DOWN] AI condition 68 DOWN: the acting unit's DatUnit flag 0x10 is clear.
void sub_2C32C0(EEContext& ctx);
// 0x2C32E0 [btlAICond_SLIP] AI condition 69 SLIP: the acting unit's DatUnit flag 0x20 is clear.
void sub_2C32E0(EEContext& ctx);
// 0x2C3BE0 [btlAITarget_HPMIN] AI target selector 1 HPMIN: an all-target skill takes the whole candidate list; otherwise the
//   candidate with the lowest HP (DatUnit +8).
void sub_2C3BE0(EEContext& ctx);
// 0x2C3CE0 [btlAITarget_LVMIN] AI target selector 2 LVMIN: an all-target skill takes the whole list; otherwise the candidate
//   with the lowest level (datCalcGetLevel).
void sub_2C3CE0(EEContext& ctx);
// 0x2C3E10 [btlAITarget_MPMAX] AI target selector 3 MPMAX: never selects (returns 0: the caller falls back to row 0).
void sub_2C3E10(EEContext& ctx);
// 0x2C3E20 [btlAITarget_BAD] AI target selector 4 BAD: from the candidates of the action's skill, the units -- those for which
//   it holds: it has the bad status param (datCalcChkBadStatus); one at random, the default selector (row 0,
//   sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 0, compare value 0, predicate
//   sub_2C1710.
void sub_2C3E20(EEContext& ctx);
// 0x2C3E60 [btlAITarget_NOTBAD] AI target selector 5 NOTBAD: from the candidates of the action's skill, the units -- those for
//   which it does NOT hold: it has the bad status param (datCalcChkBadStatus); one at random, the default selector (row
//   0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 0, compare value 1, predicate
//   sub_2C1710.
void sub_2C3E60(EEContext& ctx);
// 0x2C3EA0 [btlAITarget_ID] AI target selector 6 ID: from the candidates of the action's skill, the units -- those for which
//   it holds: its unit id is param; one at random, the default selector (row 0, sub_2C3770) when none --
//   btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 0, compare value 0, predicate sub_2C28A0.
void sub_2C3EA0(EEContext& ctx);
// 0x2C3EE0 [btlAITarget_MINE] AI target selector 7 MINE: the acting action targets itself (one target).
void sub_2C3EE0(EEContext& ctx);
// 0x2C3F00 [btlAITarget_MYAI] AI target selector 8 MYAI: a random living ally other than the acting action (itself when it has
//   none).
void sub_2C3F00(EEContext& ctx);
// 0x2C4000 [btlAITarget_HANSYA] AI target selector 9 HANSYA: from the candidates of the action's skill, the units -- those for
//   which it holds: it repels the element param (affinity bit 0x2000000); one at random, the default selector (row 0,
//   sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 0, compare value 0, predicate
//   sub_2C1E10.
void sub_2C4000(EEContext& ctx);
// 0x2C4040 [btlAITarget_KYUSYU] AI target selector 10 KYUSYU: from the candidates of the action's skill, the units -- those
//   for which it holds: it drains the element param (affinity bit 0x4000000); one at random, the default selector (row
//   0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 0, compare value 0, predicate
//   sub_2C1E50.
void sub_2C4040(EEContext& ctx);
// 0x2C4080 [btlAITarget_MUKOU] AI target selector 11 MUKOU: from the candidates of the action's skill, the units -- those for
//   which it holds: it nullifies the element param (affinity bit 0x1000000); one at random, the default selector (row
//   0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 0, compare value 0, predicate
//   sub_2C1E90.
void sub_2C4080(EEContext& ctx);
// 0x2C40C0 [btlAITarget_WEAK] AI target selector 12 WEAK: from the candidates of the action's skill, the units -- those for
//   which it holds: it is weak to the element param (affinity bit 0x8000000); one at random, the default selector (row
//   0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 0, compare value 0, predicate
//   sub_2C1ED0.
void sub_2C40C0(EEContext& ctx);
// 0x2C4100 [btlAITarget_NOTHANSYA] AI target selector 13 NOTHANSYA: from the candidates of the action's skill, the units --
//   those for which it does NOT hold: it repels the element param (affinity bit 0x2000000); one at random, the default
//   selector (row 0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 0, compare value
//   1, predicate sub_2C1E10.
void sub_2C4100(EEContext& ctx);
// 0x2C4140 [btlAITarget_NOTKYUSYU] AI target selector 14 NOTKYUSYU: from the candidates of the action's skill, the units --
//   those for which it does NOT hold: it drains the element param (affinity bit 0x4000000); one at random, the default
//   selector (row 0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 0, compare value
//   1, predicate sub_2C1E50.
void sub_2C4140(EEContext& ctx);
// 0x2C4180 [btlAITarget_NOTMUKOU] AI target selector 15 NOTMUKOU: from the candidates of the action's skill, the units --
//   those for which it does NOT hold: it nullifies the element param (affinity bit 0x1000000); one at random, the
//   default selector (row 0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 0,
//   compare value 1, predicate sub_2C1E90.
void sub_2C4180(EEContext& ctx);
// 0x2C41C0 [btlAITarget_NOTWEAK] AI target selector 16 NOTWEAK: from the candidates of the action's skill, the units -- those
//   for which it does NOT hold: it is weak to the element param (affinity bit 0x8000000); one at random, the default
//   selector (row 0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 0, compare value
//   1, predicate sub_2C1ED0.
void sub_2C41C0(EEContext& ctx);
// 0x2C4200 [btlAITarget_AI_REV] AI target selector 17 AI_REV: the candidate list of the reversed target side (sub_2BFF60 with
//   1); a group skill takes it whole, else one at random (datCalcRand).
void sub_2C4200(EEContext& ctx);
// 0x2C42C0 [btlAITarget_APPOINT] AI target selector 18 APPOINT: a group skill takes the whole list; else the candidate the
//   record already points at (sub_2C0970 / sub_2C0880), or the default selector (sub_2C3770).
void sub_2C42C0(EEContext& ctx);
// 0x2C43A0 [btlAITarget_DOWN] AI target selector 19 DOWN: from the candidates of the action's skill, the units -- those for
//   which it holds: it has the bad status param (datCalcChkBadStatus); one at random, the default selector (row 0,
//   sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 0, compare value 0, predicate
//   sub_2C1710.
void sub_2C43A0(EEContext& ctx);
// 0x2C43E0 [btlAITarget_STAND] AI target selector 20 STAND: from the candidates of the action's skill, the units -- those for
//   which it does NOT hold: it has the bad status param (datCalcChkBadStatus); one at random, the default selector (row
//   0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 0, compare value 1, predicate
//   sub_2C1710.
void sub_2C43E0(EEContext& ctx);
// 0x2C4420 [btlAITarget_HANSYA_ST] AI target selector 21 HANSYA_ST: from the candidates of the action's skill, the standing
//   (status 0x100000 excluded) units -- those for which it holds: it repels the element param (affinity bit 0x2000000);
//   one at random, the default selector (row 0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask
//   0x100000, flags 0, compare value 0, predicate sub_2C1E10.
void sub_2C4420(EEContext& ctx);
// 0x2C4460 [btlAITarget_KYUSYU_ST] AI target selector 22 KYUSYU_ST: from the candidates of the action's skill, the standing
//   (status 0x100000 excluded) units -- those for which it holds: it drains the element param (affinity bit 0x4000000);
//   one at random, the default selector (row 0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask
//   0x100000, flags 0, compare value 0, predicate sub_2C1E50.
void sub_2C4460(EEContext& ctx);
// 0x2C44A0 [btlAITarget_MUKOU_ST] AI target selector 23 MUKOU_ST: from the candidates of the action's skill, the standing
//   (status 0x100000 excluded) units -- those for which it holds: it nullifies the element param (affinity bit
//   0x1000000); one at random, the default selector (row 0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with
//   status mask 0x100000, flags 0, compare value 0, predicate sub_2C1E90.
void sub_2C44A0(EEContext& ctx);
// 0x2C44E0 [btlAITarget_WEAK_ST] AI target selector 24 WEAK_ST: from the candidates of the action's skill, the standing
//   (status 0x100000 excluded) units -- those for which it holds: it is weak to the element param (affinity bit
//   0x8000000); one at random, the default selector (row 0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with
//   status mask 0x100000, flags 0, compare value 0, predicate sub_2C1ED0.
void sub_2C44E0(EEContext& ctx);
// 0x2C4520 [btlAITarget_NOTHANSYA_ST] AI target selector 25 NOTHANSYA_ST: from the candidates of the action's skill, the
//   standing (status 0x100000 excluded) units -- those for which it does NOT hold: it repels the element param
//   (affinity bit 0x2000000); one at random, the default selector (row 0, sub_2C3770) when none -- btlAIPickTarget
//   (sub_2C3430) with status mask 0x100000, flags 0, compare value 1, predicate sub_2C1E10.
void sub_2C4520(EEContext& ctx);
// 0x2C4560 [btlAITarget_NOTKYUSYU_ST] AI target selector 26 NOTKYUSYU_ST: from the candidates of the action's skill, the
//   standing (status 0x100000 excluded) units -- those for which it does NOT hold: it drains the element param
//   (affinity bit 0x4000000); one at random, the default selector (row 0, sub_2C3770) when none -- btlAIPickTarget
//   (sub_2C3430) with status mask 0x100000, flags 0, compare value 1, predicate sub_2C1E50.
void sub_2C4560(EEContext& ctx);
// 0x2C45A0 [btlAITarget_NOTMUKOU_ST] AI target selector 27 NOTMUKOU_ST: from the candidates of the action's skill, the
//   standing (status 0x100000 excluded) units -- those for which it does NOT hold: it nullifies the element param
//   (affinity bit 0x1000000); one at random, the default selector (row 0, sub_2C3770) when none -- btlAIPickTarget
//   (sub_2C3430) with status mask 0x100000, flags 0, compare value 1, predicate sub_2C1E90.
void sub_2C45A0(EEContext& ctx);
// 0x2C45E0 [btlAITarget_NOTWEAK_ST] AI target selector 28 NOTWEAK_ST: from the candidates of the action's skill, the standing
//   (status 0x100000 excluded) units -- those for which it does NOT hold: it is weak to the element param (affinity bit
//   0x8000000); one at random, the default selector (row 0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with
//   status mask 0x100000, flags 0, compare value 1, predicate sub_2C1ED0.
void sub_2C45E0(EEContext& ctx);
// 0x2C4620 [btlAITarget_HANSYA_DW] AI target selector 29 HANSYA_DW: from the candidates of the action's skill, the downed
//   units -- those for which it holds: it repels the element param (affinity bit 0x2000000); one at random, the default
//   selector (row 0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 1, compare value
//   0, predicate sub_2C1E10.
void sub_2C4620(EEContext& ctx);
// 0x2C4660 [btlAITarget_KYUSYU_DW] AI target selector 30 KYUSYU_DW: from the candidates of the action's skill, the downed
//   units -- those for which it holds: it drains the element param (affinity bit 0x4000000); one at random, the default
//   selector (row 0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 1, compare value
//   0, predicate sub_2C1E50.
void sub_2C4660(EEContext& ctx);
// 0x2C46A0 [btlAITarget_MUKOU_DW] AI target selector 31 MUKOU_DW: from the candidates of the action's skill, the downed units
//   -- those for which it holds: it nullifies the element param (affinity bit 0x1000000); one at random, the default
//   selector (row 0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 1, compare value
//   0, predicate sub_2C1E90.
void sub_2C46A0(EEContext& ctx);
// 0x2C46E0 [btlAITarget_WEAK_DW] AI target selector 32 WEAK_DW: from the candidates of the action's skill, the downed units --
//   those for which it holds: it is weak to the element param (affinity bit 0x8000000); one at random, the default
//   selector (row 0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 1, compare value
//   0, predicate sub_2C1ED0.
void sub_2C46E0(EEContext& ctx);
// 0x2C4720 [btlAITarget_NOTID] AI target selector 33 NOTID: from the candidates of the action's skill, the units -- those for
//   which it does NOT hold: its unit id is param; one at random, the default selector (row 0, sub_2C3770) when none --
//   btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 0, compare value 1, predicate sub_2C28A0.
void sub_2C4720(EEContext& ctx);
// 0x2C4760 [btlAITarget_RND] AI target selector 34 RND: a group skill takes the whole candidate list; else one candidate at
//   random.
void sub_2C4760(EEContext& ctx);
// 0x2C4820 [btlAITarget_HOJO] AI target selector 35 HOJO: from the candidates of the action's skill, the units -- those for
//   which it holds: it has a support effect (sub_301CA0); one at random, the default selector (row 0, sub_2C3770) when
//   none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 0, compare value 0, predicate sub_2C3400.
void sub_2C4820(EEContext& ctx);
// 0x2C4860 [btlAITarget_NOTHOJO] AI target selector 36 NOTHOJO: from the candidates of the action's skill, the units -- those
//   for which it does NOT hold: it has a support effect (sub_301CA0); one at random, the default selector (row 0,
//   sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 0, compare value 1, predicate
//   sub_2C3400.
void sub_2C4860(EEContext& ctx);
// 0x2C4A90 [btlAIPickHealItemNear] AI healing pick over an item list: the item (its skill through sub_30BC20, below 0x1D0, of
//   the target kind a4 by SkillRecord +8) whose heal (datCalcDamage) brings the target's HP nearest its max -- an
//   overshoot is preferred to a shortfall only when nothing lands below; then sub_301870 on both DatUnits.
void sub_2C4A90(EEContext& ctx);
// 0x2C65D0 [btlAIPickWeightedTarget] AI target weighting: one target -> it; else each candidate is scored by its missing HP
//   percent plus a bonus per ailment (64 / 32 / 2: +20, 16 / 4: +30, 8: +50), the list is bubble-sorted by score
//   (descending) and one is drawn with the weights of the table 0x696FB0 (datCalcRand over their sum).
void sub_2C65D0(EEContext& ctx);
// 0x2C74E0 AI script command (COMM): stores the script's first parameter in the action +220 and sets the command 0x8002 (kind
//   7) through sub_2C6A00; returns 1.
void sub_2C74E0(EEContext& ctx);
// 0x2D08E0 AI script command (COMM): sets the action's unit argument (sub_288F80 with parameter 0) and the command of
//   parameter 1 through sub_2C6A00; returns 1.
void sub_2D08E0(EEContext& ctx);
// 0x2D1660 [btlAIDecodeCommand] AI command decode for a non-scripted unit: clears the command record, picks a row by the query
//   word a2 (0x200 / 64 / 32 / 16: fixed rows at 0x7CC958..; 8: the support table 0x6977D0 by a row the hero /
//   sub_697294 picks; 1: the table 0x697730 by the HP / ailment conditions of rows 0x6973CC / 0x69721C) and draws one
//   of its five weighted entries; then sets the command (sub_2C6A00) and calls the entry's target selector of 0x6975E0
//   (row 0 when it finds nothing).
void sub_2D1660(EEContext& ctx);
// 0x2D1C20 [btlAIScriptPktUpdate] AI script packet update: the first call starts the AI script (sub_2C6F50) for the action and
//   marks it running (+104); later calls return 1 once the script task has ended (kwlnTaskExists) and clear the
//   record's script state.
void sub_2D1C20(EEContext& ctx);
// 0x2D1D00 [btlAIScriptPktCreate] Creates an AI script packet (kind 3328, 16 data bytes, update sub_2D1C20): the action, the
//   script by kind (1: *0x7CE4CC, 2: *0x7CE4D0) and its procedure named a2 (scrFindPrcdIdxByName).
void sub_2D1D00(EEContext& ctx);

// --- group voice (battle7_voice.cpp; register ABI: arguments in $a0.., the result in $v0) --------------------
// 0x2D86C0 [btlNaviLineMember] Navigator line picker 3 (table 0x6978F0): the line 96..103 of the acting party member (unit ids
//   2..5, 7..10); -1 for others.
void sub_2D86C0(EEContext& ctx);
// 0x2D8850 [btlNaviLineMember2] Navigator line picker 6 (table 0x6978F0): the acting party member's line 113..128, the odd one
//   of its pair when sub_2DB480 says so.
void sub_2D8850(EEContext& ctx);
// 0x2DB2A0 [btlSupportArm] Arms the support event a0 (gBtl +2564 bit): event 0 / 1 wait 2..4 / 2..3 turns (datCalcRand), event
//   2 3..4 or 4..5 turns by the flags 320 / 321; resets its counter (+2552 + 4a0) and sets its limit (+2554 + 4a0);
//   event 0 also clears the member +2576.
void sub_2DB2A0(EEContext& ctx);
// 0x2DB650 [btlSupportWatch] Remembers the unit the support event watches: its uid (+2568) and, through sub_289030, its unit
//   id (+2572).
void sub_2DB650(EEContext& ctx);
// 0x2DB7D0 Support line packet update: btlSupportRequestLine(data +0, data +4); returns 1.
void sub_2DB7D0(EEContext& ctx);
// 0x2DB800 [btlSupportLinePktCreate] Creates the support line packet of sub_2DB7D0 (kind 2049, 8 data bytes).
void sub_2DB800(EEContext& ctx);
// 0x2DBAC0 [btlNaviStop] Stops the navigator line: sub_3C8F40 / sub_3C8FA0, then clears the pending word (+2584) and the
//   playing bit (+2582 bit 0).
void sub_2DBAC0(EEContext& ctx);
// 0x2DBB00 [btlNaviAnalysisLine] Navigator line for an analysed enemy: -1 in the FES boss fights 433..435 or for an enemy
//   marked silent (gBtlEnemyTbl +30 bit 0x20); else from the 18-byte element rows (0x697980 with flag 321, else
//   0x697A50): its weaknesses' lines (one of them, or 521 / 980 for two or more), else its null / repel / drain lines,
//   else the generic row (encounter 417 takes each row's first line). K_Assert for an id >= 0x150.
void sub_2DBB00(EEContext& ctx);
// 0x2DD180 Sound packet start callback: sub_10A0E0(0, id at data +0).
void sub_2DD180(EEContext& ctx);
// 0x2DD1B0 Sound packet update: sub_10A4E0(0, data +0, +2, +4); returns 1.
void sub_2DD1B0(EEContext& ctx);
// 0x2DD1F0 Creates the sound packet of sub_2DD180 / sub_2DD1B0 (kind 2305, 6 data bytes) for three shorts.
void sub_2DD1F0(EEContext& ctx);
// 0x2DD720 Sound packet update: sub_10A240(data +0, +4, +8); returns 1.
void sub_2DD720(EEContext& ctx);
// 0x2DD760 Creates the sound packet of sub_2DD720 (kind 2311, 12 data bytes).
void sub_2DD760(EEContext& ctx);
// 0x2DD7D0 Motion packet update: when the unit's model is loaded (+152 bit 1) plays the motion (sub_31F6D0 on the model +1016)
//   with the three shorts of the data; returns 1.
void sub_2DD7D0(EEContext& ctx);
// 0x2DD830 Creates the motion packet of sub_2DD7D0 (kind 2312, 12 data bytes).
void sub_2DD830(EEContext& ctx);
// 0x2DDDC0 [btlVoicePick1] Party voice picker 1 (table 0x697C10): with flag 388 set, the acting member's line (146, 219 / 220
//   by the flag *0x697BE4, 328, 401, 474, 547, 620 / 1117, 685); -1 otherwise. returns -1 for a non-party unit; the
//   party members 2..10 each have their own line (unit id 9 two, by sub_17D800).
void sub_2DDDC0(EEContext& ctx);
// 0x2DDF10 [btlVoicePick2] Party voice picker 2 (table 0x697C10): the acting member's line 147, 221 / 222, 329, 402, 475, 548,
//   621 / 1118, 686. returns -1 for a non-party unit; the party members 2..10 each have their own line (unit id 9 two,
//   by sub_17D800).
void sub_2DDF10(EEContext& ctx);
// 0x2DE030 [btlVoicePick3] Party voice picker 3 (table 0x697C10): the next row of the same scheme (148, 223 / 224, 330, ...).
//   returns -1 for a non-party unit; the party members 2..10 each have their own line (unit id 9 two, by sub_17D800).
void sub_2DE030(EEContext& ctx);
// 0x2DEFE0 [btlVoicePickAboutMember] Party voice picker 9 (table 0x697C10): a line about another member: -1 while bank 4 plays
//   (sub_10A500) or the speaker is not a living party member; else a random living, ailment-free member other than the
//   hero is drawn and the line is looked up by speaker x subject (each pair two lines, 50 % each; unit 9 by
//   sub_17D800).
void sub_2DEFE0(EEContext& ctx);
// 0x2E0350 [btlVoicePick10] Party voice picker 10 (table 0x697C10): one of the acting member's two lines, 50 % each (215 /
//   216, 309 / 310, 397 / 398, ...; unit 9: 1187 with sub_17D800 after one draw).
void sub_2E0350(EEContext& ctx);
// 0x2E0540 [btlVoicePick11] Party voice picker 11 (table 0x697C10): the acting member's line 217, 326, 399, 472, 545, 618, 683
//   / 1202; -1 for unit 10 and the others.
void sub_2E0540(EEContext& ctx);
// 0x2E1CD0 [btlVoicePick17] Party voice picker 17 (table 0x697C10): the line 155, 235 / 236, 337, 410, 483, 556, 629 / 1126,
//   694. returns -1 for a non-party unit; the party members 2..10 each have their own line (unit id 9 two, by
//   sub_17D800).
void sub_2E1CD0(EEContext& ctx);
// 0x2E1DF0 [btlVoicePick18] Party voice picker 18 (table 0x697C10): the next row of the same scheme. returns -1 for a
//   non-party unit; the party members 2..10 each have their own line (unit id 9 two, by sub_17D800).
void sub_2E1DF0(EEContext& ctx);
// 0x2E1F10 [btlVoicePick19] Party voice picker 19 (table 0x697C10): the next row of the same scheme. returns -1 for a
//   non-party unit; the party members 2..10 each have their own line (unit id 9 two, by sub_17D800).
void sub_2E1F10(EEContext& ctx);
// 0x2E2030 [btlVoicePick20] Party voice picker 20 (table 0x697C10): the line 149, 225, 331, 404, 477, 550, 623 / 1120, 688.
void sub_2E2030(EEContext& ctx);
// 0x2E2110 [btlVoicePick21] Party voice picker 21 (table 0x697C10): a party unit's line by sub_357FD0(0) -- with sub_17D800
//   one of 1188..1195 (value & 7), else one of 311..319 (value % 9); -1 for an enemy.
void sub_2E2110(EEContext& ctx);
// 0x2E22A0 [btlVoicePick22] Party voice picker 22 (table 0x697C10): as picker 21 with the next line ranges.
void sub_2E22A0(EEContext& ctx);
// 0x2E2920 [btlVoiceBankLoadPkt] Party voice bank load packet update: the first call (unless the voices are off, *0x7CE4FC)
//   allocates the 256 KiB bank buffer (RwMalloc, gBtl +2812) and requests bank +2808's 450 voices (sub_10A770); then
//   returns 1 once the request is done (sub_10A720) and sets the ready bit gBtl +2806.
void sub_2E2920(EEContext& ctx);
// 0x2E2A60 [btlVoiceLinePkt] Party voice line packet update: without the ready bank (gBtl +2806 bit 0) or a live speaker it is
//   done; the first call asks the picker of the situation (+4, table 0x697C10) for the line and plays it on channel 4
//   (sub_10A2E0); while channel 4 plays (sub_10A500) it keeps the speaker's model mouth flag (model +1022 bit 0x20)
//   set, cleared when the line ends.
void sub_2E2A60(EEContext& ctx);
// 0x2E2C70 Sound packet update: plays the id at data +0 on bank gBtl +2808, channel 4 (sub_10A2E0); returns 1.
void sub_2E2C70(EEContext& ctx);
// 0x2E2CB0 Creates a sound packet (kind 2562, 2 data bytes, update sub_2E2C70) for the id a0.
void sub_2E2CB0(EEContext& ctx);
// 0x2E2D00 Plays the id a0 on the special voice track (gBtl +2818), channel 2 (sub_10A2E0).
void sub_2E2D00(EEContext& ctx);
// 0x2E2D40 Stops channel 2 (sub_10A100(2, 0, 8)).
void sub_2E2D40(EEContext& ctx);
// 0x2E3010 Sound packet update: the first call plays {bank, channel, id} (sub_10A2E0); with flag bit 0 (+6) it waits until the
//   channel stops (sub_10A500) -- returns 1 when done.
void sub_2E3010(EEContext& ctx);
// 0x2E30A0 Creates the sound packet of sub_2E3010 (kind 2564, 12 data bytes) for {bank, channel, id, flags}.
void sub_2E30A0(EEContext& ctx);

// --- group cutin (battle7_cutin.cpp; register ABI: arguments in $a0.., the result in $v0) --------------------
// 0x2E3D50 Cut-in packet start: plays the cut-in sub_18B620 under the battle task (gBtl +3352) and keeps its handle in gBtl
//   +3360.
void sub_2E3D50(EEContext& ctx);
// 0x2E3DB0 Cut-in packet update: done when sub_18B360 reports the cut-in finished (1).
void sub_2E3DB0(EEContext& ctx);
// 0x2E3DE0 [btlCutInPktCreate] Creates the cut-in packet (kind 3081, 8 data bytes; callbacks sub_2E3D50 / sub_2E3DB0; flags
//   0x11 cleared).
void sub_2E3DE0(EEContext& ctx);
// 0x2E3E60 Cut-in close packet update: the first call starts the close (sub_18B380); then waits until the cut-in task is in
//   state 2 and sub_18B5F0 reports 30 frames, and clears gBtl +3360.
void sub_2E3E60(EEContext& ctx);
// 0x2E3F20 [btlCutInClosePktCreate] Creates the cut-in close packet (kind 3082; update sub_2E3E60).
void sub_2E3F20(EEContext& ctx);
// 0x2E3F70 Special effect packet start: sub_18EFB0 under the battle task for the id at data +0; handle in gBtl +3360.
void sub_2E3F70(EEContext& ctx);
// 0x2E3FB0 Special effect packet update: done when sub_18F060 reports 1.
void sub_2E3FB0(EEContext& ctx);
// 0x2E3FE0 [btlSpecialFxPktCreate] Creates the special effect packet (kind 3083; callbacks sub_2E3F70 / sub_2E3FB0) for the id
//   a0.
void sub_2E3FE0(EEContext& ctx);
// 0x2E4040 Special effect hold packet update: the first call starts the hold (sub_18F080); then done once sub_18F0C0 says so;
//   counts the frames at data +0.
void sub_2E4040(EEContext& ctx);
// 0x2E40D0 Creates the hold packet of sub_2E4040 (kind 3084).
void sub_2E40D0(EEContext& ctx);
// 0x2E4120 Special effect end packet update: the first call ends the effect (sub_18F0E0) and reads its length (sub_18F0B0)
//   into the frame counter; done when the counter reaches sub_18F0A0; clears gBtl +3360.
void sub_2E4120(EEContext& ctx);
// 0x2E41D0 Creates the end packet of sub_2E4120 (kind 3085).
void sub_2E41D0(EEContext& ctx);
// 0x2E4310 Boss event wait: sub_2FD4A0 (whether the boss event task has ended).
void sub_2E4310(EEContext& ctx);
// 0x2E43A0 [btlBossActEndHook] Action-end boss hook: unless a boss event runs (sub_2FD500), calls the pending hook gBtl +2828
//   with its argument (+2832) and clears the hook words once it returns 0; then, when nothing is pending, the boss
//   event wait (sub_2FD4A0). Returns nonzero while something is pending.
void sub_2E43A0(EEContext& ctx);

// --- group action (battle7_action.cpp; register ABI: arguments in $a0.., the result in $v0) --------------------
// 0x298610 [btlActionUpdateStateRoundup] btlAction state 29 ROUNDUP (sBtlActionTbl, update): the all-out attack -- the
//   participants (gBtl +2952) dash in, the dust-cloud packets with the "BOKO.ADX" sound, the colour fades and effect
//   packets of the skill, the hit packets on every target, the damage and the end; then the next state.
void sub_298610(EEContext& ctx);
// 0x2BCCD0 [btlHelpShow] Writes the battle help window (gBtl +2976): the unit's name by side (2 persona sub_173220, 1 enemy
//   row *0x7CE4E8 + 19 id, 0 party sub_1778B0; sub_3A4220) and the text a1 (below 0x1000 a message id sub_1FEA10, else
//   the item row *0x7CE4EC + 19 (a1 - 0x1000), sub_1FE9B0).
void sub_2BCCD0(EEContext& ctx);
// 0x2BD7E0 Help window packet update: shows the text once (sub_2BCCD0), then holds 46 frames.
void sub_2BD7E0(EEContext& ctx);
// 0x2BEDD0 [btlCommandMenuClose] Closes the command menu for a turn end: with gBtl +20 bit 0x2000000 a menu in state 3 goes to
//   6; otherwise the menu is closed (an item menu (+108 = 4) by sub_1FE430, or sub_1FE3B0 with the unit's uid without
//   the bit; else sub_1FDEC0) and set to state 2.
void sub_2BEDD0(EEContext& ctx);
// 0x2BF690 [btlCommandHelpLine] The command panel's help line for a menu row: 12 / 6 (sub_2C1CE0 says the unit cannot) -> 215,
//   5 -> 214, 1..3 by the unit's ailments (0x20 -> 205, 0x40 -> 206, row 2 also 4 -> 208, row 3 on encounter 429 ->
//   209); written by sub_1FEA10.
void sub_2BF690(EEContext& ctx);
// 0x2BF850 The command panel row 1's help callback: sub_2BF690(1).
void sub_2BF850(EEContext& ctx);
// 0x2BF880 The command panel row 2's help callback: sub_2BF690(2).
void sub_2BF880(EEContext& ctx);
// 0x2BF8B0 The command panel row 3's help callback: sub_2BF690(3).
void sub_2BF8B0(EEContext& ctx);
// 0x2BF8E0 The command panel row 5's help callback: sub_2BF690(5).
void sub_2BF8E0(EEContext& ctx);
// 0x2BF910 The command panel row 6's help callback: sub_2BF690(6).
void sub_2BF910(EEContext& ctx);
// 0x2BF940 The command panel row 12's help callback: sub_2BF690(12).
void sub_2BF940(EEContext& ctx);
// 0x2D0D70 Battle script command (COMM): the hero's camera reset -- queues sub_28A780's packets, a camera packet
//   (sub_2B8D60(3, 4095)) and the shot 37 on the hero (sub_2A3B40); returns 1.
void sub_2D0D70(EEContext& ctx);
// 0x2D0DE0 Battle script command (COMM): as sub_2D0D70 with an explicit camera move (sub_2A3D70) from the script's six float
//   parameters (position, target).
void sub_2D0DE0(EEContext& ctx);
// 0x2D1030 Battle script command (COMM): as sub_2D0D70 with the camera move to the fixed points 0x957140..0x957170.
void sub_2D1030(EEContext& ctx);
// 0x2D10F0 Battle script command (COMM): a navigator wait packet (sub_2DB890) and a support line packet (sub_2DB800(32,
//   parameter 0)), both with the delay parameter 1.
void sub_2D10F0(EEContext& ctx);
// 0x2D1180 Battle script command (COMM): a navigator wait packet (sub_2DB890) with the delay parameter 0.
void sub_2D1180(EEContext& ctx);
// 0x2D19B0 Starts the battle music once (gBtl flag 0x2000): sub_10A4E0(0, 15, 0, 3) and sub_1FF310.
void sub_2D19B0(EEContext& ctx);
// 0x2D21E0 A camera spring step: moves a value toward a target over half the remaining distance (f12 the step), returns 1.0
//   when arrived, else 0.5 (floats as the original computes them).
void sub_2D21E0(EEContext& ctx);
// 0x2D5CF0 Whether a party unit wears the accessory 1054 (Junpei / Yukari only: DatUnit id 4 or 2, equipment slot 1,
//   sub_16F630).
void sub_2D5CF0(EEContext& ctx);
// 0x2D7890 [btlUnitSetDead] Kills or revives an action's unit: revive (a1 = 1) sets HP 1 (not for skill 438 at +1120), clears
//   the dead status and sets the revived flag; otherwise HP 0, every status cleared, dead set, the died flag set and
//   the revived flag cleared. sub_2FA510 first.
void sub_2D7890(EEContext& ctx);
// 0x2DC670 [btlPoisonDamage] The poison damage of a turn: for the ailment 128, -(max HP / 500) for a party unit; an enemy by
//   its table flags (0x400 / 0x800 / 0x1000 / 0x2000: -50 / -100 / -150 / -200, else -(max HP * 100 / 333)); never
//   kills (1 - HP when it would).
void sub_2DC670(EEContext& ctx);
// 0x2DC830 [btlAilmentTurnLine] The ailment message of a turn start: by the ailment and the command kind (+108) a line 6..20,
//   +1 for an enemy; -1 for none.
void sub_2DC830(EEContext& ctx);
// 0x2DCA60 [btlAilmentLine] The ailment message of a "bad" state: the line 40..56 by the ailment (1..512), +1 for an enemy; -1
//   for none.
void sub_2DCA60(EEContext& ctx);
// 0x2F87E0 [btlBossArchiveFile] The file a0 of the boss archive (gBtl +2836; H_Cdvd_ArchiveGetFile).
void sub_2F87E0(EEContext& ctx);
// 0x2F8810 [btlBossArchiveFile0] The file 0 of the boss archive (gBtl +2836).
void sub_2F8810(EEContext& ctx);
// 0x2FD160 Encounter 428's hook: an enemy action with the effect state 11 returns the boss work word gBtl +2884; else 0.
void sub_2FD160(EEContext& ctx);
// 0x2FDDB0 [btlUnitCellPos] A unit's cell position: x = 25 * cell x (+148) - 1750, y = the unit's y, z = 25 * cell z (+150) -
//   1750 + (200 + radius * scale) (the R5900 multiply-add of the original).
void sub_2FDDB0(EEContext& ctx);

// --- group camera (battle7_camera.cpp; register ABI: arguments in $a0.., the result in $v0) --------------------
// 0x2ADC30 Camera shot callback: sub_2AD880(shot, 10.0, 2.0, 0.0, 250.0) (f12..f15).
void sub_2ADC30(EEContext& ctx);
// 0x2ADC80 Camera shot callback: sub_2AD880(shot, 15.0, 2.0, 0.25, 400.0) (f12..f15).
void sub_2ADC80(EEContext& ctx);
// 0x2ADCD0 Camera shot callback: sub_2A8D20(shot, 1).
void sub_2ADCD0(EEContext& ctx);
// 0x2B2880 Camera shot update: while the shot's action still has its one target (the shot's +256) and is active, sub_2B21F0
//   (first call flagged) and the call counter +268.
void sub_2B2880(EEContext& ctx);
// 0x2B32C0 Camera shot: aims the camera at the shot point (+156) from the position sub_2B2EB0 computes (sub_2A2290 /
//   sub_2A3110).
void sub_2B32C0(EEContext& ctx);
// 0x2E4A30 Camera shot callback: does nothing.
void sub_2E4A30(EEContext& ctx);
// 0x2E5040 Camera shot callback: sub_2A5F40.
void sub_2E5040(EEContext& ctx);
// 0x2E71C0 Boss camera shot update: while the action is active and the side shot was taken (gBtl +2936), sub_2B0210.
void sub_2E71C0(EEContext& ctx);
// 0x2E7320 Camera shot callback: does nothing.
void sub_2E7320(EEContext& ctx);
// 0x2E7680 Camera shot callback: sub_2B2060.
void sub_2E7680(EEContext& ctx);
// 0x2E76A0 Boss camera shot start: remembers the action's first target (gBtl +2932); unless the unit is analysed (sub_30C3A0),
//   sub_2B2800.
void sub_2E76A0(EEContext& ctx);
// 0x2E7710 Boss camera shot update: for an analysed unit (sub_30C3A0) the target shot sub_2E6A20 while the one target is still
//   the remembered one; else sub_2B2880.
void sub_2E7710(EEContext& ctx);
// 0x2E77C0 Boss camera shot start for an enemy action: sub_2E70B0.
void sub_2E77C0(EEContext& ctx);
// 0x2E7810 Boss camera shot update for an enemy action: sub_2B0210 once the side shot was taken (gBtl +2936).
void sub_2E7810(EEContext& ctx);
// 0x2E7880 Camera shot callback: does nothing.
void sub_2E7880(EEContext& ctx);
// 0x2E87B0 Camera shot update: plays the shot's motion (+292) on its unit (+288, sub_2880E0) once sub_2A3750 says so.
void sub_2E87B0(EEContext& ctx);
// 0x2E8C80 Camera shot callback: does nothing.
void sub_2E8C80(EEContext& ctx);
// 0x2E8C90 Boss camera shot: the camera's point from the boss AI row (gBtl +2840 +892 / +904, sub_2A4690), handed to
//   sub_2A2170 (gBtl +32) and sub_2A44B0 (the shot point).
void sub_2E8C90(EEContext& ctx);
// 0x2E8D20 Camera shot callback: sub_2B4F40.
void sub_2E8D20(EEContext& ctx);
// 0x2E8D40 Camera shot callback: sub_2B4DB0.
void sub_2E8D40(EEContext& ctx);
// 0x2E8D70 Boss camera shot: from the shot point (+156) to the boss AI row's point (+868 / +880), sub_2A2290 / sub_2A3110.
void sub_2E8D70(EEContext& ctx);
// 0x2E9060 Boss camera shot: the fixed position / target pair 0x699244 / 0x69925C (sub_2A4690 rows), sub_2A2290 / sub_2A3110
//   on the battle camera.
void sub_2E9060(EEContext& ctx);

}  // namespace p3fes::game
