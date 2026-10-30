// The datCalc.c hit / damage / affinity layer, hand-decompiled from SLUS_216.21 (docs/ANALYSIS/21_battle.md
// section 5): the three formula functions of a battle action -- the hit check datCalcCheckHit, the HP/SP change
// datCalcDamage and the affinity word datCalcGetAffinity -- and the unit / weapon / skill helpers in
// 0x302000..0x30B600 they need. Phase 5 slice `battle_calc`; game/src/battle/battle_calc.cpp, pair tests
// tests/game/test_battle_calc.cpp.
//
// Names: as symbols/functions.json gives them after IDA master update #3 (2026-10-20). The rows still `sub_<addr>`
// there carry a proposed name in their comment (not in any delta yet). The random source datCalcRand 0x2FFBC0, the
// AICALC dispatcher datScriptCalc 0x30FC40 and the buff multiplier datCalcGetEffectMultiplier 0x301880 stay
// recompiled callees reached through guest::call, so the hand-written and the recompiled bodies consume one RNG
// stream and one formula path.
#pragma once

#include "p3fes/ee_context.h"
#include "p3fes/game/battle.h"

namespace p3fes::game {

namespace btl {

// --- more of the battle tables (21_battle.md section 3.2; $gp = 0x7D2CF0) --------------------------------------
inline constexpr u32 kEnemyAffinityTablePtr = 0x7CE414u;  // u32*: UNIT.TBL section 1 = u16 affinity[16] per enemy (gp-0x48DC)
inline constexpr u32 kAiCalc7TablePtr = 0x7CE48Cu;        // u32*: AICALC.TBL section 7, 32 bytes for weapon ids 0xC0..0xDF (gp-0x4864)
inline constexpr u32 kWeaponClassTable = 0x7CC9F8u;       // u8[]: held-weapon type -> class (gp-0x62F8, .data)
inline constexpr u32 kGp = 0x7D2CF0u;                     // $gp: the base of the gp-relative float constants and table pointers

// The affinity word (datCalcGetAffinity): rate % in the low 16 bits, flags in the high byte.
inline constexpr u32 kAffNull = 0x01000000u;
inline constexpr u32 kAffRepel = 0x02000000u;
inline constexpr u32 kAffAbsorb = 0x04000000u;
inline constexpr u32 kAffWeak = 0x08000000u;
inline constexpr u32 kAffResist = 0x10000000u;

// Result codes of the hit check datCalcCheckHit (21_battle.md section 5.2); datCalcDamage takes them as `result`.
inline constexpr u32 kHit = 1;
inline constexpr u32 kMiss = 4;
inline constexpr u32 kNullified = 256;
inline constexpr u32 kRepelled = 512;  // also the evade result
inline constexpr u32 kDrained = 1024;

}  // namespace btl

// --- unit / weapon / skill helpers (game/src/battle/battle_calc.cpp) --------------------------------------------
s64 datCalcGetSkillElement(EEContext& ctx, u32 unit, u32 skill);     // 0x3082F0: weapon element for a physical skill, else SKILL section 0
void sub_3086C0(EEContext& ctx);  // [register ABI] 0x3086C0 (proposed datCalcGetSkillByte3): SkillRecord +3
void sub_308860(EEContext& ctx);  // [register ABI] 0x308860 (proposed datCalcIsMixRaidSkill): 0xC0 <= id < 0xC6
void sub_308A50(EEContext& ctx);  // [register ABI] 0x308A50 (proposed datCalcIsSkillInBand110): 0x110 <= id < 0x131
u32 datCalcGetSkillSlotCount(EEContext& ctx);                       // 0x308BA0: 8
void datCalcGetSkillList(EEContext& ctx);  // [register ABI] 0x308BB0: EnemyRecord +14 / the persona's skill list
void sub_308930(EEContext& ctx);  // [register ABI] 0x308930 (proposed datCalcGetAttackSkill): the held weapon's attack skill
u32 datCalcGetHeldWeaponType(EEContext& ctx, u32 unit);             // 0x308C60: weapon type 0..7 (0 for enemies)
void sub_308ED0(EEContext& ctx);  // [register ABI] 0x308ED0 (proposed datCalcGetHeldWeaponId): item id of equipment slot 0
void sub_308F80(EEContext& ctx);  // [register ABI] 0x308F80 (proposed datCalcGetWeaponClass): 1 for enemies, else the type's class byte
void sub_308FD0(EEContext& ctx);  // [register ABI] 0x308FD0 (proposed datCalcGetWeaponHitClass)
void sub_3093A0(EEContext& ctx);  // [register ABI] 0x3093A0 (proposed datCalcGetWeaponAiCalcByte): AICALC section 7 [weapon id - 0xC0]
void datCalcGetWeaponParam(EEContext& ctx);  // [register ABI] 0x309080: 0 power, 1 accuracy
void datCalcGetArmorParam(EEContext& ctx);  // [register ABI] 0x309250: 0 defense, 1 evasion (10 for enemies)
u64 datCalcGetAffinityChecked(EEContext& ctx, u32 unit, u32 element);  // 0x30B4B0: -1 -> 0, the neutral rows -> 100, else datCalcGetAffinity
void datCalcIsLowHp(EEContext& ctx);  // [register ABI] 0x30B5E0: 100 * hp / maxhp < 26

// --- the formulas -----------------------------------------------------------------------------------------------
void datCalcGetAffinity(EEContext& ctx);  // [register ABI] 0x306E80: the affinity word
void datCalcCheckHit(EEContext& ctx);  // [register ABI] 0x309490: result code
s32 datCalcDamage(EEContext& ctx, u32 skill, u32 attacker, u32 target, u32 hits, u32 result, u32 kind, u32 flags,
                  u32 hp_or_sp);                                                   // 0x303130: recovery, or -damage

}  // namespace p3fes::game
