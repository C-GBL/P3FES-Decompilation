// Battle data leaves, hand-decompiled from SLUS_216.21 (docs/ANALYSIS/21_battle.md): the datCalc.c
// accessors over the 60-byte battle unit record (HP/SP, the bad-status word, the buff nibbles) and the
// SKILL.TBL lookups behind the damage/affinity formulas.
//
// Names: the IDA names of symbols/p3fes.sym, set on the master 2026-10-20 from symbols/deltas/battle.sym
// (before that every function here was `sub_<addr>`): verified tge-pr4 promotions for the HP/SP,
// bad-status and datCalcIsDead leaves (ADR-0009), our own names for the buff getters and the SKILL.TBL
// lookups. The trailing comment gives the function's address.
#pragma once

#include "p3fes/ee_context.h"

#include <cstddef>

namespace p3fes::game {

namespace btl {

// --- the battle tables (battle/*.TBL, loaded by btlTableLoadAll 0x27DE40 into the arena 0x875D00; 21_battle.md section 3) ---
inline constexpr u32 kSkillElementTablePtr = 0x7CE3F4u;  // u32*: SKILL.TBL section 0 = { s8 element, u8 } per skill (gp-0x48FC)
inline constexpr u32 kSkillTablePtr = 0x7CE3F8u;         // u32*: SKILL.TBL section 1 = SkillRecord[464] (gp-0x48F8)
inline constexpr u32 kUnitTablePtr = 0x7CE410u;          // u32*: UNIT.TBL section 0 = EnemyRecord[336] (gp-0x48E0)
inline constexpr u32 kSkillCount = 0x1D0u;               // 464 skills (datCalc.c asserts id < 0x1D0)
inline constexpr u32 kEnemyCount = 0x150u;               // 336 enemies (asserts id < 0x150)
inline constexpr u32 kSkillRecordSize = 44;
inline constexpr u32 kEnemyRecordSize = 62;
inline constexpr u32 kDatCalcSourceFile = 0x69AA80u;     // "datCalc.c" (the K_Assert file argument)

// --- the bad-status word (unit +0xC; 21_battle.md section 2.2) -------------------------------------------
inline constexpr u32 kStatusLowMask = 0x000FFFFFu;   // the 20 status bits datCalcGetBadStatusNoDown keeps
inline constexpr u32 kStatusHighMask = 0xFFF00000u;  // the 12 "down"-class bits datCalcSetBadStatus ors in
inline constexpr u32 kStatusDead = 0x00080000u;      // datCalcIsDead: bit 19

inline constexpr u32 kUnitFlagEnemy = 0x4u;          // unit +0 bit 2: an enemy (UNIT.TBL record) rather than a party member
inline constexpr u32 kEffectSlots = 21;              // buff/debuff slots: 0..16 are 4-bit levels, 17..20 bits of +0x14
}  // namespace btl

// The battle unit record (datUnit.c; 60 bytes = the stride of datUnitCreateEc's enemy array; 21_battle.md
// section 2.2). Only the fields the leaves below touch are typed.
struct DatUnit {  // 60 bytes
    u16 flags;         // +0x00 bit0 initialised, bit2 enemy, bit4/5/7/8 copied from the enemy table flags, bit9 has an evade skill
    u16 id;            // +0x02 party member 1..10 or enemy 0..335 (unit flag bit 2)
    u16 base_id;       // +0x04 the id as created
    u8 level;          // +0x06 enemy level (a party member's level lives in the persona)
    u8 pad07;          // +0x07
    u16 hp;            // +0x08 datCalcGetHp / SetHp (capped at 999 for party members)
    u16 sp;            // +0x0A datCalcGetSp / SetSp
    u32 status;        // +0x0C bad-status word: 20 status bits + 12 high bits, bit 19 = dead
    u32 unk10;         // +0x10
    u32 effect_flags;  // +0x14 bit i = buff slot i active (slots 17..20 are flags only)
    u32 unk18;         // +0x18 zeroed by sub_301870
    u8 effect_level[9];   // +0x1C slots 0..16 as signed 4-bit nibbles (-7..7; even slot low nibble, odd high)
    u8 pad25[4];          // +0x25
    u8 effect_turns[9];   // +0x29 the matching 4-bit turn counters
    u8 pad32[6];          // +0x32
    u16 message_id;       // +0x38 the result message the calc picked (e.g. 4639 = critical)
    u8 pad3A[2];          // +0x3A
};
static_assert(sizeof(DatUnit) == 60);
static_assert(offsetof(DatUnit, hp) == 0x8 && offsetof(DatUnit, sp) == 0xA && offsetof(DatUnit, status) == 0xC &&
              offsetof(DatUnit, effect_flags) == 0x14 && offsetof(DatUnit, effect_level) == 0x1C &&
              offsetof(DatUnit, effect_turns) == 0x29 && offsetof(DatUnit, message_id) == 0x38);

// One SKILL.TBL section-1 record (44 bytes; 21_battle.md section 3.2). The bytes the leaves read.
struct SkillRecord {  // 44 bytes
    u8 flags0;         // +0 bit1 = physical (the attacker's weapon element and the AICALC attack formula apply)
    u8 flags1;         // +1 bit0 = usable from the field menu (datCalcIsSkillUsableOnField)
    u8 kind;           // +2 1 = HP effect, 2 = SP effect (selects the AICALC formula table)
    u8 byte3;          // +3
    u8 rest[40];
};
static_assert(sizeof(SkillRecord) == 44);

// --- HP / SP (game/src/battle/battle_unit.cpp) ----------------------------------------------------------------
void datCalcGetHp(EEContext& ctx);  // [register ABI] 0x2FFD70: u16 at +8
void datCalcGetSp(EEContext& ctx);  // [register ABI] 0x2FFD80: u16 at +0xA
void datCalcSetHp(EEContext& ctx);  // [register ABI] 0x2FFD90: +8 = hp, capped at 999 unless the unit is an enemy
void datCalcSetSp(EEContext& ctx);  // [register ABI] 0x2FFDC0: +0xA, same cap

// --- the bad-status word (battle_unit.cpp) ------------------------------------------------------------------
void datCalcGetBadStatus(EEContext& ctx);  // [register ABI] 0x300550: the word
void datCalcGetBadStatusNoDown(EEContext& ctx);  // [register ABI] 0x300530: its low 20 bits
void datCalcSetBadStatus(EEContext& ctx);  // [register ABI] 0x3004F0: replace the low 20 bits when given, or in the high 12; returns the word
void datCalcClearBadStatus(EEContext& ctx);  // [register ABI] 0x300560: word &= ~bits; returns the word
void datCalcChkBadStatus(EEContext& ctx);  // [register ABI] 0x300580: (word & bits) != 0
void datCalcIsDead(EEContext& ctx);  // [register ABI] 0x30B5A0: the dead bit, or hp + delta <= 0

// --- buff / debuff slots (battle_unit.cpp) ------------------------------------------------------------------
s32 datCalcGetEffectLevel(EEContext& ctx, u32 unit, u32 slot);                 // 0x300F60: signed nibble of slot 0..16 (-7..7)
void datCalcGetEffectState(EEContext& ctx);  // [register ABI] 0x301750: the nibble for slots < 17, else bit `slot` of +0x14

// --- SKILL.TBL lookups (game/src/battle/battle_skill.cpp) --------------------------------------------------------
void datCalcIsSkillUsableOnField(EEContext& ctx);  // [register ABI] 0x300AF0: id < 464, not physical, flags1 bit 0
u32 datCalcIsPhysicalSkill(EEContext& ctx, u32 skill_id);                      // 0x3088B0: flags0 bit 1 (K_Assert on id >= 464)
void datCalcGetElementBit(EEContext& ctx);  // [register ABI] 0x3080C0: 1 << (element + 1) (K_Assert on element >= 19)
void datCalcGetElementForStatus(EEContext& ctx);  // [register ABI] 0x308120: skill element 8 wins, else the status bit -> element table

}  // namespace p3fes::game
