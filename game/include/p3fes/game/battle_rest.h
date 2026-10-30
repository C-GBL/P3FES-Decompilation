// The rest of the datCalc.c battle band, hand-decompiled from SLUS_216.21 (docs/ANALYSIS/21_battle.md section 5):
// the buff-slot maintenance a turn runs (apply a mask of +-level changes, clear the masked slots, tick the turn
// counters, find an expiring slot), the status-ailment roll and its three users, the skill-application
// wrappers around datCalcDamage, the skill cost and its affordability check, the instant-kill / knock-down /
// follow-up / counter / hit-count rolls of an action, and the readers next to them (skill and arcana names,
// the SKILL.TBL section-2 records, the enemy exp / drop rolls, the escape roll, the party restore). Phase 5
// slice `battle_rest`; game/src/battle/battle_rest.cpp, pair tests tests/game/test_battle_rest.cpp.
//
// Names: as symbols/functions.json gives them now. The `sub_<addr>` rows carry a proposed name in brackets
// (ours, from the instructions; not in any delta). Every function here keeps the original register discipline at
// its calls: the prologue's spills are written to the guest stack, the s-registers hold
// what the original kept there and $ra gets the original link (battle_rest.cpp's header comment).
#pragma once

#include "p3fes/ee_context.h"
#include "p3fes/game/battle.h"

namespace p3fes::game {

namespace btl {
inline constexpr u32 kSkillNamesPtr = 0x7CE4ECu;      // u32*: MSG.TBL section 1 = char[19] per skill (gp-0x4804)
inline constexpr u32 kArcanaNamesPtr = 0x7CE4F0u;     // u32*: MSG.TBL section 0 = char[21] per arcana (gp-0x4800)
inline constexpr u32 kSkillSection2Ptr = 0x7CE3FCu;   // u32*: SKILL.TBL section 2 = 6-byte records for skills 272..304 (gp-0x48F4)
inline constexpr u32 kSkillCountWithItems = 624;      // skill ids asserted < 0x270 by the name / status code
}  // namespace btl

// --- buff slots (game/src/battle/battle_rest.cpp) -------------------------------------------------------------
void sub_302380(EEContext& ctx);  // [register ABI] [datCalcApplyEffectMask] +-delta per mask bit, bits 12/13 clear slots
void sub_302C50(EEContext& ctx);  // [register ABI] [datCalcClearMaskedEffects] slots of the +0x18 mask, then mask = 0
void sub_302D40(EEContext& ctx);  // [register ABI] [datCalcTickEffectTurns] turn counter + 1 for every set slot < 15
void sub_302F50(EEContext& ctx);  // [register ABI] [datCalcFindExpiredEffect] first slot whose counter ran out, or -1

// --- status ailments --------------------------------------------------------------------------------------------
void sub_305970(EEContext& ctx);  // [register ABI] [datCalcRollStatus] the inflicted status bit, or 0
void sub_306020(EEContext& ctx);  // [register ABI] [datCalcRollWeaponStatus] the skill's or the weapon effect's status
void sub_306510(EEContext& ctx);  // [register ABI] [datCalcRollSkillStatus] status skills (SKILL +24 == 2) only

// --- skill application ------------------------------------------------------------------------------------------
void sub_306610(EEContext& ctx);  // [register ABI] [datCalcApplySkill] HP/SP change + statuses stored; 1
void sub_3068D0(EEContext& ctx);  // [register ABI] [datCalcGetSkillEffectMask] what the skill would do (bits / 0xFFFF)
u64 sub_306BC0(EEContext& ctx, u64 skill, u64 attacker, u64 target, u64 flags, u64 hp_out, u64 sp_out,
               u64 status_out);                                                   // [datCalcSkillResults] the three results to pointers; 1
void sub_306D90(EEContext& ctx);  // [register ABI] [datCalcDecodeAffinity] UNIT.TBL word -> affinity word

// --- costs and the action rolls ---------------------------------------------------------------------------------
void sub_3083F0(EEContext& ctx);  // [register ABI] [datCalcGetSkillCost] HP or SP cost (halved by 566 / 565)
void sub_3086F0(EEContext& ctx);  // [register ABI] [datCalcCheckSkillCost] 0 payable, 1 HP, 2 SP, 3 free
void sub_308A80(EEContext& ctx);  // [register ABI] [datCalcPickMixRaidSkill] a random skill 192..197 of the list, or 0
void sub_30A740(EEContext& ctx);  // [register ABI] [datCalcRollInstantKill] 1 / 2 kill / 4 weak / 8
void sub_30AF00(EEContext& ctx);  // [register ABI] [datCalcCanKnockDown] 1 when a hit can knock down
void sub_30B130(EEContext& ctx);  // [register ABI] [datCalcCheckKnockDown]
void sub_30B210(EEContext& ctx);  // [register ABI] [datCalcRollFollowUp] the 70 / 100 % roll
void sub_30B640(EEContext& ctx);  // [register ABI] [datCalcGetCounterSkill] the counter passive that fires, or -1
void sub_30B9A0(EEContext& ctx);  // [register ABI] [datCalcGetHitCount] hits of a skill

// --- readers ----------------------------------------------------------------------------------------------------
void datGetSkillName(EEContext& ctx);  // [register ABI] 0x30BB40: MSG.TBL section 1 + 19 * id (K_Assert id < 624)
void datGetArcanaName(EEContext& ctx);  // [register ABI] 0x30BBB0: MSG.TBL section 0 + 21 * id (K_Assert id < 32)
u64 sub_30BC20(EEContext& ctx, u64 item);          // [datGetItemPrice] u16 +8 of sub_170E90's record
void sub_30BC50(EEContext& ctx);  // [register ABI] [datCalcGetEnemyExp] EnemyRecord +32, scaled under flags 3024 / 4881
void sub_30BDE0(EEContext& ctx);  // [register ABI] [datCalcRollEnemyDrop] the dropped item id, or 0
void sub_30C0C0_regs(EEContext& ctx);  // [register ABI] [datGetSkillSection2ForParty] the section-2 record a stock persona matches, or 0
void sub_30C220(EEContext& ctx);  // [register ABI] [datGetSkillSection2] SKILL.TBL section 2 + 6 * (id - 272)
void sub_30C2A0(EEContext& ctx);  // [register ABI] [datCalcRollEscape] rand(100) < the clamped escape rate
void sub_30C3A0(EEContext& ctx);  // [register ABI] [datCalcIsEnemyFlag4] EnemyRecord +0 bit 2 for an enemy, else 0
void datCalcRestorePartyAll(EEContext& ctx);       // 0x30C440: sub_30C490 for pc 1..10
void sub_30C490(EEContext& ctx, u64 pc);           // [datCalcRestorePartyMember] full HP and SP, statuses cleared

// --- the rest of the datUnit.c / datCalc.c / datScript.c band ------------------------------------------------------
void datUnitEcAddEnemy(EEContext& ctx);  // [register ABI] 0x2FF540: datUnitInit into the first free of 6 slots
void sub_2FFB00(EEContext& ctx);  // [register ABI] [datCalcUpdatePartyCondition] a party record's condition after the turn
void sub_3005A0(EEContext& ctx);  // [register ABI] [datCalcGetCondition] sub_16C920 for a party member, 0 for an enemy
void sub_300700(EEContext& ctx);  // [register ABI] [datCalcHasCounter] sub_170760(pc, id) > 0 for a party member
void sub_300870(EEContext& ctx);  // [register ABI] [datCalcCountEquipmentEffect] equipment slots 0..2 with this effect
void sub_300E90(EEContext& ctx);  // [register ABI] [datCalcIsBlockedByWall] the skill's element hits a wall buff (17 / 18)
void sub_301CA0(EEContext& ctx);  // [register ABI] [datCalcCheckEffectMask] the first mask bit of sub_302380 already applied
// 0x30FDC0 / 0x3111C0 / 0x3112E0 (datScript COMM handlers) are defined by the script_comm_a slice (comm_a.h).

}  // namespace p3fes::game
