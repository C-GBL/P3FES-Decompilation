// Battle data layer, hand-decompiled from SLUS_216.21 (docs/ANALYSIS/21_battle.md sections 1.3, 1.4, 2, 3 and
// 5): the rest of the datUnit.c / datCalc.c unit accessors (genus slots, unit init, level, stats, max HP/SP,
// the buff-slot writers and multipliers, the RNG wrapper), the datScript.c context leaves, the btl root
// flag/packet helpers, the btlAction list and the 12-slot turn-order list, the btlMain / btlAction state-table
// drivers, the party / persona / item record lookups of g_data and datPersona.c, and the three Tartarus
// floor-layout readers of k_encount.c. btlActionUpdateAll 0x299FB0 stays recompiled (it frees actions through
// the RwFree heap hook).
//
// Names: every function carries the name symbols/functions.json gives it now (28 carry IDA names, most from master
// update #3); for the 48 `sub_<addr>` ones the name in brackets is a proposal (ADR-0009: ours, or a tge-pr4 hint only
// where the behaviour was checked against the instructions), not yet in the master.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace btl {

// --- fixed guest addresses (gp = 0x7D2CF0; 21_battle.md sections 1.3, 2 and 3) ---------------------------------
inline constexpr u32 kBtlPtr = 0x7CE3ECu;            // gBtl (gp-0x4904): the battle context
inline constexpr u32 kGenusReady = 0x7CE508u;        // u8, set by sub_2FF2D0 / sub_2FF2F0, read by datUnitIsGenusReady
inline constexpr u32 kGenusReadyA = 0x7CE50Au;       // u16, zeroed with it
inline constexpr u32 kGenusReadyArg = 0x7CE50Cu;     // u16, the argument of sub_2FF2D0
inline constexpr u32 kRandPrev = 0x7CE510u;          // u32, datCalcRand's previous 0..99 roll
inline constexpr u32 kBtlCompareWord = 0x7CE514u;    // u32, compared by sub_3112C0
inline constexpr u32 kAicalc5Ptr = 0x7CE480u;        // u32*: AICALC.TBL section 5: u8 percent[2 tables][2 sides][3 levels] (datCalcGetEffectMultiplier)
inline constexpr u32 kEffectBoostConst = 0x7CAF90u;  // f32 (gp-0x7D60): the factor datCalcGetEffectMultiplier applies to an active attack-type flag
inline constexpr u32 kPersonaNamesPtr = 0x7CE4E4u;   // u32*: MSG.TBL section 3, 17-byte persona names
inline constexpr u32 kPersonaAffinityPtr = 0x7CE424u;  // u32*: UNIT.TBL section 2, u16 affinity[16] per persona id
inline constexpr u32 kEncountSec1Ptr = 0x7CE4B0u;    // u32*: ENCOUNT.TBL section 1 (10-byte rows)
inline constexpr u32 kEncountSec2Ptr = 0x7CE4B4u;    // u32*: ENCOUNT.TBL section 2 (200-byte rows per floor)
inline constexpr u32 kAccessoryTablePtr = 0x7CDFD4u; // u32*: 36-byte accessory item records (ids 3000..3999)

inline constexpr u32 kActionStateTbl = 0x693410u;    // sBtlActionTbl: 36 x {init, update, name}
inline constexpr u32 kMainStateTbl = 0x693760u;      // sBtlMainStateTbl: 20 x {init, update, name}

inline constexpr u32 kDatScriptAttacker = 0x957190u; // gDatScriptAttacker (unit*)
inline constexpr u32 kDatScriptResult = 0x957198u;   // gDatScriptResult
inline constexpr u32 kDatScriptSkill = 0x95719Cu;    // u16 gDatScriptSkill
inline constexpr u32 kDatScriptFlags = 0x9571A4u;    // u16, bit 0 = result valid

inline constexpr u32 kHeroUnit = 0x836224u;          // gGlobalWork + 0x24: the hero's DatUnit
inline constexpr u32 kPartyRecords = 0x834010u;      // party member records, 868 bytes each, pc 2..10 (index pc - 2)
inline constexpr u32 kPartyRecordSize = 868;
inline constexpr u32 kHeroEquipment = 0x83678Cu;     // s16[] equipment slot indices of the hero
inline constexpr u32 kPartyEquipment = 0x83399Cu;    // + 868 * pc: s16[] slot indices of member pc
inline constexpr u32 kHeroPersonaIdx = 0x836BA8u;    // s16: the hero's current persona slot
inline constexpr u32 kHeroPersonaStock = 0x836BACu;  // 52-byte hero persona slots (u16 flags, bit 0 = used)
inline constexpr u32 kPersonaStockFlags = 0x83A45Cu; // u32: progression bits that size the persona stock
inline constexpr u32 kGrowthTable = 0x5DC1B4u;       // 44-byte rows per level: 11 x {u16 hp, u16 sp}

inline constexpr u32 kDatUnitSourceFile = 0x69AA70u;    // "datUnit.c"
inline constexpr u32 kDatScriptSourceFile = 0x69AB78u;  // "datScript.c"
inline constexpr u32 kGDataSourceFile = 0x5E3098u;      // the K_Assert file of datGetUnit (g_data band)
inline constexpr u32 kDatPersonaSourceFile = 0x5E3278u; // "datPersona.c"

}  // namespace btl

// --- datUnit.c: genus slots and the unit record (game/src/battle/battle_data.cpp) ------------------------------
void sub_2FF2D0(EEContext& ctx);  // [register ABI] 0x2FF2D0: genus-ready byte = 1, u16 arg = value
void sub_2FF2F0(EEContext& ctx);                                              // 0x2FF2F0: the same with 0
u32 sub_2FF310(EEContext& ctx);                                               // 0x2FF310: returns 1
u32 datUnitIsGenusReady(EEContext& ctx);                                      // 0x2FF320: ready byte != 0
u32 sub_2FF330(EEContext& ctx);                                               // 0x2FF330: returns 0
void datUnitEcRemoveEnemy(EEContext& ctx);  // [register ABI] 0x2FF660: clear the slot holding `unit`
void datUnitIsGenusDead(EEContext& ctx);  // [register ABI] 0x2FF790: every live slot datCalcIsDead
void datUnitInit(EEContext& ctx);  // [register ABI] 0x2FF890: party (0) / enemy (1) unit; returns 1

// --- datCalc.c --------------------------------------------------------------------------------------------------
void datCalcRand(EEContext& ctx);  // [register ABI] 0x2FFBC0: effMiscRand % n; n == 100: 0..99 with the +-3 re-roll
u32 datCalcGetLevel(EEContext& ctx, u32 unit);                                // 0x2FFCC0: unit +6 (enemy, hero) or the persona's level
void datCalcGetMaxHp(EEContext& ctx);  // [register ABI] 0x2FFDF0: base + skill / equipment bonuses, 999 cap for the party
void datCalcGetMaxSp(EEContext& ctx);  // [register ABI] 0x300100: the same for SP
void datCalcAddHp(EEContext& ctx);  // [register ABI] 0x300410: clamp(hp + delta, 0, max), stored and returned
void datCalcAddSp(EEContext& ctx);  // [register ABI] 0x300480: the same for SP
u32 datCalcHasSkill(EEContext& ctx, u32 unit, u32 skill);                     // 0x3005E0: 8 slots, then the accessory's skill
void sub_300750(EEContext& ctx);  // [register ABI] 0x300750 [datCalcHasEquipmentEffect] any of slots 0..2
u32 datCalcCountEquipmentWithEffect(EEContext& ctx, u32 unit, u32 effect);    // 0x3009A0: how many of slots 0..2 (0 for enemies)
void sub_300B60(EEContext& ctx);  // [register ABI] 0x300B60 [datCalcGetBaseStat] enemy record / persona base, 1..99
void datCalcGetStat(EEContext& ctx);  // [register ABI] 0x300C90: enemy base / persona total, 1..99
void datCalcGetPassiveSkillFlags(EEContext& ctx);  // [register ABI] 0x300D80: bits for skills 547..552, 607, 608
void datCalcSetEffectLevel(EEContext& ctx);  // [register ABI] 0x301030: signed nibble of slot 0..16
void sub_301150(EEContext& ctx);  // [register ABI] 0x301150 [datCalcSetEffectTurns] 4-bit counter
void datCalcAddEffectLevel(EEContext& ctx);  // [register ABI] 0x301230: clamp(level + delta, -1, 1)
void datCalcClearEffect(EEContext& ctx);  // [register ABI] 0x301540: nibble, counter and flag bit of one slot
void datCalcClearAllEffects(EEContext& ctx);  // [register ABI] 0x301690: all 21 slots
void sub_301870(EEContext& ctx);  // [register ABI] 0x301870 [datCalcClearUnk18] unit +0x18 = 0
void datCalcGetEffectMultiplier(EEContext& ctx);  // [register ABI] 0x301880: f32 bits ($f0); leaves $v0/$f1 as compiled

// --- datScript.c ------------------------------------------------------------------------------------------------
u32 sub_311180(EEContext& ctx);                                               // 0x311180: returns 1
void datScriptSetResult(EEContext& ctx);  // [register ABI] 0x311190: gDatScriptResult = value, valid bit
void sub_3111F0_regs(EEContext& ctx);  // [register ABI] 0x3111F0 [datScriptIsNotEnemy] attacker flag bit 2 clear
void sub_311250_regs(EEContext& ctx);  // [register ABI] 0x311250 [datScriptIsPhysicalSkill] SkillRecord flags0 bit 1 of gDatScriptSkill
u32 sub_3112C0(EEContext& ctx, u64 value);                                    // 0x3112C0: word 0x7CE514 == value

// --- btl root: gBtl flags and the packet lists -------------------------------------------------------------------
void btlMainCheckBattleEnd_regs(EEContext& ctx);  // [register ABI] 0x27D380: outcome to gBtl+0x1C, 1 when over
u32 sub_27D880(EEContext& ctx);                                               // 0x27D880 [btlGetTask] gBtl ? gBtl+0xD18 : 0
void sub_27D8B0(EEContext& ctx);                                              // 0x27D8B0: gBtl+0xC |= 0x8000
void sub_27DBE0(EEContext& ctx);  // [register ABI] 0x27DBE0 [btlUpdateSetFlagsPacket] gBtl+0xC |= *packet; 1
void sub_27DC50(EEContext& ctx);  // [register ABI] 0x27DC50 [btlUpdateClearFlagsPacket] gBtl+0xC &= ~*packet; 1
void sub_27E310(EEContext& ctx);  // [register ABI] 0x27E310 [btlPacketFindFirstByKey88] first active packet with (+88 & mask) == key
void sub_27E390(EEContext& ctx);  // [register ABI] 0x27E390 [btlPacketFindFirstByActionUID] the same on +96

// --- btlAction.c / btlMain: the action list, the order list, the state drivers ----------------------------------
void btlActionSetState(EEContext& ctx);  // [register ABI] 0x299D60: returns the init's $v0
void sub_299E30(EEContext& ctx);  // [register ABI] 0x299E30 [btlActionSetActive] +24 |= 1
void sub_299E50(EEContext& ctx);  // [register ABI] 0x299E50 [btlActionClearActive] +24 &= ~1
void sub_299E70(EEContext& ctx);  // [register ABI] 0x299E70 [btlActionSetUnit] +48 = unit, +26 |= 1
void sub_29A1D0(EEContext& ctx);  // [register ABI] 0x29A1D0 [btlActionFindByUnit]
void sub_29A210(EEContext& ctx);  // [register ABI] 0x29A210 [btlActionFindById]
void sub_29A250(EEContext& ctx);  // [register ABI] 0x29A250 [btlListRemove] remove `item`, close the gap
void sub_29A2C0(EEContext& ctx);  // [register ABI] 0x29A2C0 [btlOrderAddAction] first free of the 12 at gBtl+0x254
void sub_29A320(EEContext& ctx);  // [register ABI] 0x29A320 [btlOrderRemoveAction] every occurrence; 1 if any
void sub_29A380(EEContext& ctx);  // [register ABI] 0x29A380 [btlOrderAddAction2] first free of the 12 at gBtl+0x284
void sub_29A3E0(EEContext& ctx);  // [register ABI] 0x29A3E0 [btlActionIsTurnHolder] (inf)
void sub_29A470(EEContext& ctx);  // [register ABI] 0x29A470 [btlOrderMoveToFront]
void sub_29A4F0(EEContext& ctx);  // [register ABI] 0x29A4F0 [btlOrderMoveToBack]
void btlOrderSortByAgility(EEContext& ctx);                                   // 0x29A570: bubble sort by datCalcGetStat(unit, 3)
void sub_29A690(EEContext& ctx);  // [register ABI] 0x29A690 [btlOrderSortBySide]
void btlMainSetState(EEContext& ctx);  // [register ABI] 0x29DE20: returns the init's $v0
u64 btlMainUpdateState(EEContext& ctx);                                       // 0x29DE80: returns the update's $v0

// --- g_data / datPersona.c: party, persona and item records -----------------------------------------------------
s32 datGetEquipmentIdx(EEContext& ctx, u32 pc, u32 slot);                     // 0x16CB80: s16 equipment index of a slot
void sub_16CC00(EEContext& ctx);  // [register ABI] 0x16CC00 [datGetGrowthHp] growth table hp at the unit's level
void sub_16CCB0(EEContext& ctx);  // [register ABI] 0x16CCB0 [datGetGrowthSp]
void datGetUnit(EEContext& ctx);  // [register ABI] 0x16CD60: the hero's or member pc's DatUnit
void sub_16F630(EEContext& ctx);  // [register ABI] 0x16F630 [datGetEquipmentItemId] u16 +0 of a 20-byte equipment entry
u32 sub_16F900(EEContext& ctx, u32 owner, u32 idx);                           // 0x16F900 [datGetEquipmentEffect] u8 +9 of it
// 0x170E40 [datGetAccessoryRecord] (the 36-byte record of ids 3000..3999, else 0) is replaced by the menu/UI
// layer-2 slice as the item-table section-4 lookup: declared in ui2.h, defined in src/ui/ui2.cpp.
void sub_173220(EEContext& ctx);  // [register ABI] 0x173220 [datGetPersonaName] MSG.TBL section 3 + 17 * id
void sub_1732F0(EEContext& ctx);  // [register ABI] 0x1732F0 [datPersonaGetLevel] u8 +4
void sub_173380(EEContext& ctx);  // [register ABI] 0x173380 [datPersonaGetSkillsByPcId] persona + 12
void sub_1733B0(EEContext& ctx);  // [register ABI] 0x1733B0 [datPersonaGetAffinity] UNIT.TBL section 2 word through sub_306D90
void sub_173460(EEContext& ctx);  // [register ABI] 0x173460 [datPersonaGetAffinityByPcId]
void sub_173510(EEContext& ctx);  // [register ABI] 0x173510 [datPersonaGetBaseStat] u8 persona +28 + stat
void sub_1738D0(EEContext& ctx);  // [register ABI] 0x1738D0 [datPersonaGetStat] base + three bonuses, clamped 0..99
void datPersonaGetByPcId(EEContext& ctx);  // [register ABI] 0x174800: the hero's stock slot or member pc's persona
void sub_174A90(EEContext& ctx);  // [register ABI] 0x174A90 [datPersonaGetHeroPersona] 52-byte stock slot or 0
void sub_175410_regs(EEContext& ctx);  // [register ABI] 0x175410 [datPersonaGetStockSize] 4/6/8/9/10/12 by progression bits

// --- k_encount.c: Tartarus floor layout (ENCOUNT.TBL sections 1 and 2) ---------------------------------------------
void sub_1D75F0(EEContext& ctx);  // [register ABI] 0x1D75F0: byte +3 of the floor's layout row
void sub_1D76E0(EEContext& ctx);  // [register ABI] 0x1D76E0: byte +2
void sub_1D77D0(EEContext& ctx);  // [register ABI] 0x1D77D0: byte +4

}  // namespace p3fes::game
