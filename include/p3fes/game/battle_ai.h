// Battle AICALC formulas (datScript.c), hand-decompiled from SLUS_216.21 (docs/ANALYSIS/21_battle.md section 4):
// the formula dispatcher datScriptCalc, the 35-selector value getter datScriptGetValue, the 48 formula functions of
// the three 17-entry tables sDatScriptFuncTbl1..3 and their three entry-0 nullsubs.
//
// Names: datScriptCalc and datScriptGetValue are the master's names (datScriptCalc since IDA master update #3);
// the formula entries are still `sub_<addr>` / `nullsub_<n>` there, so the game/ function keeps that name and the
// comment gives its table, slot and what it computes. Helpers already in battle.h (btl::kSkillTablePtr, the
// DatUnit / SkillRecord layouts) are reused, not repeated.
//
// Every formula is a short chain of EE single-precision operations on datScriptGetValue results. The chains are
// written with the p3fes/ee/fpu.h primitives in the compiled operand order (the EE's chopped add/mul, DIV.S rounding
// to nearest, the truncating SQRT.S, MADD.S through ACC), so the result is bit-identical to the recompiled body.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace ai {

// --- the evaluation context of datScriptCalc (21_battle.md section 4) ------------------------------------------
inline constexpr u32 kAttacker = 0x957190u;  // u32 DatUnit*: gDatScriptAttacker
inline constexpr u32 kTarget = 0x957194u;    // u32 DatUnit*: gDatScriptTarget
inline constexpr u32 kResult = 0x957198u;    // s32: gDatScriptResult (written by datScriptSetResult 0x311190)
inline constexpr u32 kSkill = 0x95719Cu;     // u16: gDatScriptSkill
inline constexpr u32 kMode = 0x9571A0u;      // s32: gDatScriptMode (1 = HP, 2 = SP for selector 19; a status bit for 15/16)
inline constexpr u32 kFlags = 0x9571A4u;     // u16: bit 0 = a result was set

inline constexpr u32 kFuncTbl1 = 0x69AA90u;  // sDatScriptFuncTbl1: the default set
inline constexpr u32 kFuncTbl2 = 0x69AAE0u;  // sDatScriptFuncTbl2: chosen when datGetFlag(0x1311)
inline constexpr u32 kFuncTbl3 = 0x69AB30u;  // sDatScriptFuncTbl3: chosen when datGetFlag(0x1319)
inline constexpr u32 kFuncCount = 17;        // entries per table (asserted, not enforced: K_Assert is `jr $ra`)
inline constexpr s32 kFlagTable2 = 0x1311;
inline constexpr s32 kFlagTable3 = 0x1319;

inline constexpr u32 kGetValueJumpTable = 0x7B90A0u;  // datScriptGetValue's 35 case labels
inline constexpr u32 kSelectorCount = 35;

// The selectors of datScriptGetValue(selector, index) (its case labels; the formulas pass them as `a0`). A = the
// attacker (gDatScriptAttacker), T = the target; `index` is a stat for 13 / 14 (St 0, Ma 1, En 2, Ag 3, Lu 4), else 0.
namespace sel {
inline constexpr s32 kLevelA = 1, kLevelT = 2;           // datCalcGetLevel
inline constexpr s32 kHpA = 3, kHpT = 4;                 // datCalcGetHp
inline constexpr s32 kMaxHpA = 5, kMaxHpT = 6;           // datCalcGetMaxHp
inline constexpr s32 kSpA = 7, kSpT = 8;                 // unit +0xA
inline constexpr s32 kMaxSpA = 9, kMaxSpT = 10;          // datCalcGetMaxSp
inline constexpr s32 kAffinityA = 11, kAffinityT = 12;   // affinity rate to the skill's element / 100
inline constexpr s32 kStatA = 13, kStatT = 14;           // datCalcGetStat(unit, index)
inline constexpr s32 kStatusAffinityA = 15, kStatusAffinityT = 16;  // affinity rate to the element of status gDatScriptMode / 100
inline constexpr s32 kAccuracy = 17;                     // the weapon's (physical) or SkillRecord +14
inline constexpr s32 kStatusRate = 18;                   // SkillRecord +25, the status infliction rate
inline constexpr s32 kPower = 19;                        // the weapon's (physical) or SkillRecord +18 / +22 by gDatScriptMode
inline constexpr s32 kSkillByte37 = 20;                  // SkillRecord +37
inline constexpr s32 kSkillByte38 = 21;                  // SkillRecord +38
inline constexpr s32 kDamageCap = 22;                    // 31000
inline constexpr s32 kLevelDiff = 23;                    // AICALC0 by level difference (second row outside a battle)
inline constexpr s32 kLevelDiff3 = 24;                   // AICALC1 by level difference / 3
inline constexpr s32 kMaBonus10 = 25;                    // AICALC3[Ma / 10]
inline constexpr s32 kMaBonus5 = 26;                     // AICALC4[Ma / 5]
inline constexpr s32 kRound = 27;                        // gBtl round + 1
inline constexpr s32 kResult = 28;                       // gDatScriptResult
inline constexpr s32 kArmorA0 = 29, kArmorA1 = 30;       // datCalcGetArmorParam(attacker, 0 / 1)
inline constexpr s32 kArmorT0 = 31, kArmorT1 = 32;       // datCalcGetArmorParam(target, 0 / 1)
inline constexpr s32 kLevelDiffBattle = 33;              // AICALC0 by level difference, the in-battle row always
inline constexpr s32 kBtlB9E = 34;                       // gBtl +0xB9E
inline constexpr s32 kSt = 0, kMa = 1, kEn = 2, kAg = 3, kLu = 4;  // the stat indices of 13 / 14
}  // namespace sel
inline constexpr u32 kDatScriptSourceFile = 0x69AB78u;  // "datScript.c" (the K_Assert file argument)

// --- gp-relative words the getter reads ($gp = 0x7D2CF0) --------------------------------------------------------
inline constexpr u32 kBtlPtr = 0x7CE3ECu;      // gp-18692: gBtl (NULL outside a battle); +0xB98 u16 round, +0xB9E u16
// gp-18680 is btl::kSkillTablePtr (battle.h): SKILL.TBL section 1 = SkillRecord[464].
inline constexpr u32 kAiCalc0Ptr = 0x7CE46Cu;  // gp-18564: AICALC.TBL section 0, 126 floats (level difference; selectors 23/33)
inline constexpr s32 kAiCalc0Row2 = 63;        // section 0 = two rows of 63 floats; the second is used outside a battle
inline constexpr u32 kAiCalc1Ptr = 0x7CE470u;  // gp-18560: section 1, 13 floats (level difference / 3; selector 24)
inline constexpr u32 kAiCalc3Ptr = 0x7CE478u;  // gp-18552: section 3, 10 x s16 (Ma / 10; selector 25)
inline constexpr u32 kAiCalc4Ptr = 0x7CE47Cu;  // gp-18548: section 4, 20 x s16 (Ma / 5, index clamped at 20; selector 26)

// --- the float literals of the formulas (.lit4, read-only: no store in the binary addresses them) --------------
// The "per-difficulty" constants are literals shared by the three sets; a set differs by which literal it reads.
inline constexpr u32 kLit0_80 = 0x7CAD74u;  // gp-32636: 0.8  (0x3F4CCCCD) enemy-attacker defence scale; all sets
inline constexpr u32 kLit1_35 = 0x7CAD8Cu;  // gp-32612: 1.35 (0x3FACCCCD) enemy-attacker damage scale, set 3
inline constexpr u32 kLit0_85 = 0x7CAD94u;  // gp-32604: 0.85 (0x3F59999A) datCalcCheckHit hit-rate multiplier (not read here)
inline constexpr u32 kLit0_60 = 0x7CADB4u;  // gp-32572: 0.6  (0x3F19999A) enemy heal scale (sets 1, 3), enemy damage scale (set 2)
inline constexpr u32 kLit0_70 = 0x7CADD0u;  // gp-32544: 0.7  (0x3F333333) datCalcCheckHit buff-slot-10 multiplier (not read here)
inline constexpr u32 kLit1_30 = 0x7CAE84u;  // gp-32364: 1.3  (0x3FA66666) party-attacker damage scale, set 2
inline constexpr u32 kLit0_90 = 0x7CAF8Cu;  // gp-32100: 0.9  (0x3F666666) enemy-attacker damage scale, set 1

}  // namespace ai

// --- the dispatcher and the value getter ---------------------------------------------------------------------
// datScriptCalc(fn, attacker, target, skill, mode): sets the context, runs entry `fn` of the table the
// two flags pick, returns gDatScriptResult (also left in $v0). `fn` is the full 64-bit $a0 (sltiu compares it so).
void datScriptCalc(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// datScriptGetValue(selector, index): the EE single (bit pattern) of input `selector`, also left in $f0.
void datScriptGetValue(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// --- the formula functions (each stores its integer result through datScriptSetResult; no arguments) ----------------
// Set 1 = sDatScriptFuncTbl1, 2 = Tbl2 (flag 0x1311), 3 = Tbl3 (flag 0x1319). Slot numbers are the table index.
void nullsub_62(EEContext& ctx);  // set 1 slot 0
void sub_30C520(EEContext& ctx);  // set 1 slot 1: attack damage (St, 2 En or enemy defence, power, affinity, level difference)
void sub_30C930(EEContext& ctx);  // set 1 slot 2: Ma damage plus AICALC3[Ma / 10]
void sub_30CB90(EEContext& ctx);  // set 1 slot 3: power + AICALC4[Ma / 5] (enemy: x 0.6)
void sub_30CC40(EEContext& ctx);  // set 1 slot 4: hit rate (200 + Ag ratios, target evasion for an enemy attacker)
void sub_30CDB0(EEContext& ctx);  // set 1 slot 5: (50 + Lu) ratio x SkillRecord+37
void sub_30CEC0(EEContext& ctx);  // set 1 slot 6: SkillRecord+38
void sub_30CF00(EEContext& ctx);  // set 1 slot 7: 75 x Ag and Lu ratios + 5 x gBtl+0xB9E
void sub_30D000(EEContext& ctx);  // set 1 slot 8:  Lu / ((2 + 3 (level - 1)) x status affinity) x 50
void sub_30D0E0(EEContext& ctx);  // set 1 slot 9:  same, x 50
void sub_30D1C0(EEContext& ctx);  // set 1 slot 10: same, x 50
void sub_30D2A0(EEContext& ctx);  // set 1 slot 11: same, x 40
void sub_30D380(EEContext& ctx);  // set 1 slot 12: same, x 30
void sub_30D460(EEContext& ctx);  // set 1 slot 13: 100
void sub_30D4A0(EEContext& ctx);  // set 1 slot 14: 100
void sub_30D4E0(EEContext& ctx);  // set 1 slot 15: physical attack x round x level difference x 0.8
void sub_30D610(EEContext& ctx);  // set 1 slot 16: SkillRecord+25 x status affinity x (100 + Lu) ratio (enemy: x 0.8)
void nullsub_63(EEContext& ctx);  // set 2 slot 0
void sub_30D760(EEContext& ctx);  // set 2 slot 1 (party x 1.3, enemy x 0.6)
void sub_30DB80(EEContext& ctx);  // set 2 slot 2 (party x 1.3, enemy x 0.6)
void sub_30DDF0(EEContext& ctx);  // set 2 slot 3 (party x 1.5, enemy x 0.5)
void sub_30DEC0(EEContext& ctx);  // set 2 slot 4 = set 1 slot 4
void sub_30E030(EEContext& ctx);  // set 2 slot 5 (enemy x 0.5)
void sub_30E140(EEContext& ctx);  // set 2 slot 6 = set 1 slot 6
void sub_30E180(EEContext& ctx);  // set 2 slot 7 (60 / 30 offsets, x 85)
void sub_30E280(EEContext& ctx);  // set 2 slots 8..12 = set 1 slots 8..12
void sub_30E360(EEContext& ctx);
void sub_30E440(EEContext& ctx);
void sub_30E520(EEContext& ctx);
void sub_30E600(EEContext& ctx);
void sub_30E6E0(EEContext& ctx);  // set 2 slot 13: 100
void sub_30E720(EEContext& ctx);  // set 2 slot 14: 100
void sub_30E760(EEContext& ctx);  // set 2 slot 15 (x 2 after the level difference)
void sub_30E8A0(EEContext& ctx);  // set 2 slot 16 (enemy x 0.5)
void nullsub_64(EEContext& ctx);  // set 3 slot 0
void sub_30EA00(EEContext& ctx);  // set 3 slot 1 (enemy x 1.35)
void sub_30EE10(EEContext& ctx);  // set 3 slot 2 (enemy x 1.35)
void sub_30F070(EEContext& ctx);  // set 3 slot 3 = set 1 slot 3
void sub_30F120(EEContext& ctx);  // set 3 slot 4 = set 1 slot 4
void sub_30F290(EEContext& ctx);  // set 3 slot 5 = set 1 slot 5
void sub_30F3A0(EEContext& ctx);  // set 3 slot 6 = set 1 slot 6
void sub_30F3E0(EEContext& ctx);  // set 3 slot 7 (150 offsets, x 30)
void sub_30F4E0(EEContext& ctx);  // set 3 slots 8..12 = set 1 slots 8..12
void sub_30F5C0(EEContext& ctx);
void sub_30F6A0(EEContext& ctx);
void sub_30F780(EEContext& ctx);
void sub_30F860(EEContext& ctx);
void sub_30F940(EEContext& ctx);  // set 3 slot 13: 100
void sub_30F980(EEContext& ctx);  // set 3 slot 14: 100
void sub_30F9C0(EEContext& ctx);  // set 3 slot 15 = set 1 slot 15
void sub_30FAF0(EEContext& ctx);  // set 3 slot 16 (enemy x 1.5)

}  // namespace p3fes::game
