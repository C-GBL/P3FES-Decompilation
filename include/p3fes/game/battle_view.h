// Named views for the register-level battle bodies (p3fes_handgen, game/include/p3fes/game/hg_cpu.h): the guest
// addresses and record offsets that battle_data.cpp, battle_ai.cpp, battle_calc.cpp and battle_rest.cpp read, so a
// body says `lhu(v0, a0, dat_unit::kFlags)` instead of `lhu(v0, a0, 0)`. Written by the read_battle readability pass
// (2026-10-21); header only. Nothing here changes what a body runs: the constants are the values the instructions
// hold, and the two helpers (k_assert, u32_to_float) run exactly the statements, in order, that they stand for.
//
// Every offset comes from the instructions of the functions that use it, cross-checked against the proposed layouts of
// the type recovery (game/include/p3fes/game/types/unit.h, battle_state.h; docs/ANALYSIS/28_types.md) and the project
// headers (battle.h DatUnit / SkillRecord, battle_task.h gBtl / btlAction). Names are ours (ADR-0009); the confirmed
// ones are fed back through tools/ours/types/deltas/read_battle.json.
#pragma once

#include "p3fes/ee/core.h"
#include "p3fes/ee_context.h"
#include "p3fes/game/battle.h"       // btl:: table pointers, DatUnit / SkillRecord
#include "p3fes/game/battle_ai.h"    // ai:: the datScript context and AICALC pointers, the .lit4 constants
#include "p3fes/game/battle_data.h"  // btl:: the fixed addresses of the data layer
#include "p3fes/game/battle_calc.h"  // btl:: the affinity / AICALC7 tables, the affinity flags
#include "p3fes/game/battle_rest.h"  // btl:: the name tables, SKILL.TBL section 2
#include "p3fes/game/hg_cpu.h"

#include <bit>

namespace p3fes::recomp_gen {
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);  // K_Assert(file, line): `jr $ra` in retail
}  // namespace p3fes::recomp_gen

namespace p3fes::game::bview {

// --- addressing: spell the address a `lui`/`addiu` pair or a `$gp` offset forms ------------------------------------
inline constexpr u32 kGp = 0x7D2CF0u;  // $gp of the whole program
// `lw rt, gp_off(va)(gp)`: the signed 16-bit offset of `va` from $gp.
constexpr s32 gp_off(u32 va) noexcept { return static_cast<s32>(va - kGp); }
// `lui rt, hi(va)` + `addiu/lw rt, lo(va)(rt)`: the carry-adjusted upper half (as lui writes it: sign-extended) and the
// signed lower half. hi(0x69AA70) = 0x6A0000, lo(0x69AA70) = -21904.
constexpr u64 hi(u32 va) noexcept { return ee::core::lui((va + 0x8000u) >> 16); }
constexpr s32 lo(u32 va) noexcept { return static_cast<s16>(static_cast<u16>(va & 0xFFFFu)); }
static_assert(hi(0x69AA70u) == 0x6A0000u && lo(0x69AA70u) == -21904);
// `lui rt, hi16` of an EE single literal (the compiled code builds every such float with lui + mtc1): the register value
// lui writes for `f` (whose low 16 bits are zero). flt(2.0f) = 0x40000000.
constexpr u64 flt(float f) noexcept { return ee::core::sext32(std::bit_cast<u32>(f)); }
static_assert(flt(2.0f) == 0x40000000u && flt(0.5f) == 0x3F000000u && flt(2147483648.0f) == 0x4F000000u);

// --- K_Assert file arguments (the "<file>.c" strings) ---------------------------------------------------------------
inline constexpr u32 kDatUnitFile = btl::kDatUnitSourceFile;        // 0x69AA70 "datUnit.c"
inline constexpr u32 kDatCalcFile = btl::kDatCalcSourceFile;        // 0x69AA80 "datCalc.c"
inline constexpr u32 kDatScriptFile = btl::kDatScriptSourceFile;    // 0x69AB78 "datScript.c"
inline constexpr u32 kGDataFile = btl::kGDataSourceFile;            // 0x5E3098 "g_data.c"
inline constexpr u32 kDatPersonaFile = btl::kDatPersonaSourceFile;  // 0x5E3278 "datPersona.c"

// K_Assert(file, line) called at `pc`: the original's `lui a0, hi(file); addiu a0, a0, lo(file); addiu a1, $zero, line;
// jal K_Assert` -- the same statements in the same order, one block (its `charge` stays at the call site). K_Assert is
// `jr $ra` in retail, so a failed check continues on the path after it with the same registers.
inline void k_assert(hg::Gpr a0, hg::Gpr a1, u32 pc, u32 file, s32 line) {
    a0 = hi(file);
    a0 = hg::addiu(a0, lo(file));
    a1 = hg::si(line);
    hg::jal(a0.c, pc, ::p3fes::recomp_gen::fn_sub_19D3F0_0019d3f0);
}

// fd = (float)(u32)v0, the compiled unsigned conversion: when bit 63 of $v0 is set (a negative s64 test: `bltz v0`)
// halve it keeping the low bit, convert, double; else convert. The original's two blocks with their charges (7 / 5),
// statement for statement; $v1 and $f0 are written as the original writes them.
inline void u32_to_float(hg::Gpr v0, hg::Gpr v1, hg::Fpr f0, hg::Fpr fd) {
    if (hg::i64(v0) < 0) {
        hg::charge(v0.c, 7);
        v1 = hg::srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        hg::mtc1(v1, f0);
        hg::cvt_s_w(fd, f0);
        hg::add_s(fd, fd, fd);
    } else {
        hg::charge(v0.c, 5);
        hg::mtc1(v0, f0);
        hg::cvt_s_w(fd, f0);
    }
}

// --- DatUnit: the 60-byte battle unit record (battle.h DatUnit; types/unit.h) -----------------------------------------
namespace dat_unit {
inline constexpr s32 kFlags = 0x00;        // u16: bit 0 initialised, bit 2 enemy, bits 4/5/7/8 copied from the enemy record, bit 9 evade skill
inline constexpr s32 kId = 0x02;           // u16: party member 1..10 or enemy 0..335
inline constexpr s32 kBaseId = 0x04;       // u16: the id as created
inline constexpr s32 kLevel = 0x06;        // u8: enemy (and hero) level
inline constexpr s32 kHp = 0x08;           // u16
inline constexpr s32 kSp = 0x0A;           // u16
inline constexpr s32 kStatus = 0x0C;       // u32: the bad-status word
inline constexpr s32 kEffectFlags = 0x14;  // u32: bit i = buff slot i active
inline constexpr s32 kUnk18 = 0x18;        // u32: zeroed by sub_301870
inline constexpr s32 kEffectLevel = 0x1C;  // u8[9]: slots 0..16 as signed nibbles (even slot low nibble, odd high)
inline constexpr s32 kEffectTurns = 0x29;  // u8[9]: the matching 4-bit turn counters
inline constexpr s32 kMessageId = 0x38;    // u16: the result message the calc picked
inline constexpr u32 kSize = 60;
inline constexpr u32 kFlagInit = 0x1;    // set by datUnitInit
inline constexpr u32 kFlagEnemy = 0x4;   // a UNIT.TBL enemy rather than a party member
inline constexpr u32 kFlagEvade = 0x200; // one of the eight enemy skills is 544..546
inline constexpr s32 kHero = 1;          // party id of the hero (his level is unit +6, his persona the stock slot)
inline constexpr s32 kPartyIds = 11;     // party ids are < 11 (asserted)
}  // namespace dat_unit

// --- the enemy genus of datUnitEc* (docs/ANALYSIS/21_battle.md section 2.1) ------------------------------------------
namespace genus {
inline constexpr s32 kKind = 0;   // u16: 0 party, 1 enemy
inline constexpr s32 kCount = 2;  // u16: live units (at most 6 for an enemy genus)
inline constexpr s32 kUnits = 4;  // u32: DatUnit[6] (60-byte stride) for an enemy genus, the one DatUnit* for a party genus
inline constexpr s32 kKindEnemy = 1;
inline constexpr s32 kMaxEnemies = 6;
}  // namespace genus

// --- UNIT.TBL section 0: the 62-byte enemy record (gBtlEnemyTbl, btl::kUnitTablePtr) ----------------------------------
namespace enemy_rec {
inline constexpr s32 kFlags = 0;   // u16: 0x8 / 0x10 / 0x100 / 0x200 -> unit flags 0x10 / 0x20 / 0x80 / 0x100
inline constexpr s32 kLevel = 3;   // u8
inline constexpr s32 kHp = 4;      // u16: max HP
inline constexpr s32 kSp = 6;      // u16: max SP
inline constexpr s32 kStats = 8;   // u8[5]: St, Ma, En, Ag, Lu
inline constexpr s32 kSkills = 14; // u16[8]
inline constexpr s32 kExp = 32;             // u16: the experience it gives (sub_30BC50)
inline constexpr s32 kDrops = 34;           // 4 x {u16 item, u8 weight, u8}: the common drops (sub_30BDE0)
inline constexpr s32 kDropWeight = 36;      // the weight byte of drop 0 (+4 per drop)
inline constexpr s32 kRareFlag = 50;        // u16: the event flag the rare drop needs
inline constexpr s32 kRareItem = 52;        // u16: the rare drop
inline constexpr s32 kRareChance = 54;      // u8: its chance in percent
inline constexpr s32 kAttackAccuracy = 56;  // u8: the normal attack's accuracy (datCalcGetWeaponParam 1)
inline constexpr s32 kAttackPower = 58;     // u16: the normal attack's power (datCalcGetWeaponParam 0)
inline constexpr s32 kAttackSkill = 60;     // u16: the normal-attack skill id
inline constexpr u32 kSize = 62;
inline constexpr s32 kCount = 336;
}  // namespace enemy_rec

// --- the 52-byte persona record (types/unit.h Persona; datPersonaGetByPcId) -----------------------------------------
namespace persona {
inline constexpr s32 kFlags = 0;       // u16: bit 0 used (a hero stock slot)
inline constexpr s32 kId = 2;          // u16: persona id < 256 (MSG.TBL names, UNIT.TBL section 2 affinities)
inline constexpr s32 kLevel = 4;       // u8
inline constexpr s32 kSkills = 12;     // u16[8]
inline constexpr s32 kBaseStats = 28;  // u8[5]: St, Ma, En, Ag, Lu
inline constexpr u32 kSize = 52;
inline constexpr s32 kIdCount = 256;
inline constexpr s32 kNameSize = 17;   // MSG.TBL section 3 name stride
inline constexpr s32 kAffinityRow = 32;  // UNIT.TBL section 2: u16 affinity[16] per persona id
}  // namespace persona

// --- party member records (868 bytes, pc 2..10 at btl::kPartyRecords + 868 * (pc - 2); the hero's parts elsewhere) ---
namespace party {
inline constexpr u32 kGlobalWork = 0x836200u;  // gGlobalWork: the hero's DatUnit at +0x24, his persona stock at +0x9AC
inline constexpr s32 kHeroStockOff = 0x9AC;    // btl::kHeroPersonaStock - kGlobalWork
inline constexpr s32 kUnit = 4;                 // DatUnit (60 bytes) inside the record
inline constexpr s32 kPersona = 220;            // Persona (52 bytes) inside the record
inline constexpr u32 kRecordSize = 868;
inline constexpr u32 kEquipEntries = 0x8339A4u;  // + 868 * pc: 20-byte equipment entries of member pc
inline constexpr u32 kEquipEntriesHi = 0x7FD6C8u; // + 868 * owner for owners >= 256
inline constexpr u32 kEquipEntriesShared = 0x833E80u;  // owner -1: 20-byte entries
inline constexpr u32 kHeroEquipEntriesPtr = 0x836794u;  // u32*: the hero's (owner 1) 20-byte entries
inline constexpr s32 kEquipEntrySize = 20;
inline constexpr s32 kEquipItemId = 0;   // u16 in an equipment entry
inline constexpr s32 kEquipEffect = 9;   // u8 in an equipment entry
inline constexpr s32 kGrowthRow = 44;    // btl::kGrowthTable: per level 11 x {u16 hp, u16 sp}, pc at 4 * pc
inline constexpr s32 kGrowthSp = 2;
}  // namespace party

// --- ENCOUNT.TBL (k_encount.c): section 1 = 10-byte rows by index, section 2 = 200-byte rows by floor ---------------
namespace encount {
inline constexpr s32 kSec1Row = 10;
inline constexpr s32 kSec2Row = 200;
inline constexpr s32 kSec2FirstFloor = 30;  // section 2 row 0 is floor 30 (the readers index floor * 200 - 6000)
inline constexpr s32 kSec2Bias = -kSec2FirstFloor * kSec2Row;
}  // namespace encount

// --- SKILL.TBL section 1: the 44-byte skill record (battle.h SkillRecord; gBtlSkillTbl, btl::kSkillTablePtr) ----------
namespace skill_rec {
inline constexpr s32 kFlags0 = 0;           // u8: bit 1 physical
inline constexpr s32 kKind = 2;             // u8: 1 HP effect, 2 SP effect
inline constexpr s32 kByte3 = 3;            // u8: read by sub_3086C0
inline constexpr s32 kAccuracy = 14;        // u8: a magic skill's accuracy (datScriptGetValue selector 17)
inline constexpr s32 kHpFormula = 17;       // u8: the HP formula; 16 = the power is the weapon's (selector 19)
inline constexpr s32 kHpBase = 18;          // s16: the power when gDatScriptMode is 1 (HP)
inline constexpr s32 kSpBase = 22;          // s16: the power when gDatScriptMode is 2 (SP)
inline constexpr s32 kStatusRate = 25;      // u8: the status infliction rate (selector 18)
inline constexpr s32 kByte37 = 37;          // u8: selector 20
inline constexpr s32 kByte38 = 38;          // u8: selector 21
inline constexpr u32 kFlagPhysical = 0x2;
inline constexpr u32 kSize = 44;
}  // namespace skill_rec

// --- gBtl (*(u32*)0x7CE3EC; battle_task.h btl_task:: has the full list) ---------------------------------------------
namespace btl_root {
inline constexpr s32 kFlags = 12;          // u32: 0x8000 set by sub_27D8B0; the packet flag words or / clear into it
inline constexpr s32 kOutcome = 28;        // u16: 1 win, 2 lose, 3 escape (btlMainCheckBattleEnd)
inline constexpr s32 kActionList = 332;    // u32: head of the btlAction list
inline constexpr s32 kPacketQueues = 372;  // u32[4] heads, 8 bytes apart (sub_27E310 / sub_27E390 walk all four)
inline constexpr s32 kPacketQueueCount = 4;
inline constexpr s32 kOrderList = 596;     // u32[12]: the turn-order list (btlAction*)
inline constexpr s32 kOrderListNext = 644; // u32[12]: the next round's list
inline constexpr s32 kMainState = 692;     // u32: btlMain state
inline constexpr s32 kMainPending = 696;   // u32
inline constexpr s32 kMainFrames = 700;    // u32
inline constexpr s32 kRound = 2968;        // u16: the round counter (datScriptGetValue selector 27 reads round + 1)
inline constexpr s32 kB9E = 2974;          // u16: datScriptGetValue selector 34
inline constexpr s32 kOrderSlots = 12;
}  // namespace btl_root

// --- btlAction (battle_task.h btl_task::kAct*) ------------------------------------------------------------------------
namespace action {
inline constexpr s32 kUid = 0;          // u64
inline constexpr s32 kSerial = 8;       // s32: the id sub_29A210 looks for
inline constexpr s32 kState = 12;       // u16
inline constexpr s32 kPrevState = 16;   // u16: the state before the last btlActionSetState
inline constexpr s32 kFlags = 24;       // u16: bit 0 active (sub_299E30 / sub_299E50), bit 2, bit 5 out of the battle-end count
inline constexpr s32 kFlags2 = 26;      // u16: bit 0 a combatant (sub_299E70)
inline constexpr s32 kFrames = 28;      // u32: frames in the current state
inline constexpr s32 kByte40 = 40;      // u8: set -> sub_29A3E0 says "turn holder"
inline constexpr s32 kByte41 = 41;      // u8: likewise
inline constexpr s32 kUnit = 48;        // u32: btlUnit*
inline constexpr s32 kNextInList = 1192; // u32: next btlAction of gBtl's list
}  // namespace action

// --- btlUnit (battle_task.h btl_task::kUnit*) ------------------------------------------------------------------------
namespace btl_unit {
inline constexpr s32 kFlags = 156;   // u32: 0x1 dead
inline constexpr s32 kSide = 162;    // u8: 0 party, 1 enemy
inline constexpr s32 kDat = 2604;    // u32: DatUnit*
}  // namespace btl_unit

// --- btl packets (gBtl's queues; types: BtlPacket) -------------------------------------------------------------------
namespace packet {
inline constexpr s32 kFlags = 71;     // u8: 0x20 active (the finders skip a packet without it)
inline constexpr u32 kFlagActive = 0x20;
inline constexpr s32 kId = 88;        // u64: the key sub_27E310 masks
inline constexpr s32 kOwner = 96;     // u64: the action uid sub_27E390 compares
inline constexpr s32 kNext = 124;     // u32
}  // namespace packet

}  // namespace p3fes::game::bview
