// The datCalc.c hit / damage / affinity layer (game/include/p3fes/game/battle_calc.h), hand-decompiled from
// SLUS_216.21 (docs/ANALYSIS/21_battle.md section 5). Phase 5 slice `battle_calc`: these replace the recompiled
// bodies listed in game/replaced.txt; tests/game/test_battle_calc.cpp runs each against its __recomp body.
//
// Virtual time per ADR-0013: every guest::enter/charge mirrors a `ctx.cycles += N` block of
// recomp/generated/fn_0024_002ff2f0_00315c20.cpp on the executed path, charged before the block's calls as the
// generated code does (an event that fires inside a callee sees the same cycle count). K_Assert (sub_19D3F0) is
// `jr $ra` in retail: a failed range check falls through to the same loads, and the call stays a guest::call for
// its check point and its two cycles. Every callee that is still recompiled -- datCalcRand among them -- is
// reached through guest::call; the ones replaced in this file are called directly.
//
// Register-width rules kept from the compiled code: unit ids are loaded with `lhu` and handed to the party-side
// callees either unsigned (lhu) or sign-extended (lh, `dsll32/dsra32 16`) exactly as each call site does; the
// affinity word is a 64-bit register value (the party path returns whatever sub_173460 left in $v0, and the
// masks are sign-extended `lui` constants), so it is kept as u64.
//
// Faithfulness audit (2026-10-21, tools/ours/audit): 18 of the 19 functions here are now p3fes_handgen's register-
// faithful bodies (their hand versions differed from the original: frame/spills 15, scratch GPRs 3); each keeps the
// notes of its earlier hand version above it. The others are the hand-written versions this header describes.
//
// Readability pass (read_battle, 2026-10-21): the 18 generated bodies keep every statement, charge, check point and
// call of p3fes_handgen's output in the same order on every path. All of them name what they touch (battle_view.h:
// `k_assert`, `hi()/lo()/gp_off()` for addresses, `flt()` for float literals, `u32_to_float`, the DatUnit fields on the
// registers that hold a unit for the whole body, the enemy / skill record strides and fields, the affinity flags);
// datCalcGetSkillElement, datCalcGetHeldWeaponType (its mask ladder as a table walk), sub_3093A0,
// datCalcGetWeaponParam and datCalcGetArmorParam are restructured without gotos. The three formula functions
// (datCalcGetAffinity, datCalcCheckHit, datCalcDamage: 1,700-3,500 lines each) keep the generator's remaining gotos.
#include "p3fes/game/battle_calc.h"

#include "p3fes/ee/core.h"
#include "p3fes/ee/fpu.h"
#include "p3fes/game/guest.h"
#include "p3fes/game/battle_view.h"
#include "p3fes/game/hg_cpu.h"

// Callees of the register-faithful bodies (p3fes_handgen), through their recomp_gen entry points.
namespace p3fes::recomp_gen {
void fn_datCalcGetEffectLevel_00300f60(p3fes::EEContext&);
void fn_datCalcIsPhysicalSkill_003088b0(p3fes::EEContext&);
void fn_datCalcGetAffinityChecked_0030b4b0(p3fes::EEContext&);
void fn_datCalcGetAffinity_00306e80(p3fes::EEContext&);
void fn_datCalcGetHeldWeaponType_00308c60(p3fes::EEContext&);
void fn_datCalcGetSkillElement_003082f0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::recomp_gen {
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);  // K_Assert(file, line): jr $ra
void fn_datGetEquipmentIdx_0016cb80(p3fes::EEContext&);  // datGetEquipmentIdx(pc, slot)
void fn_sub_16F630_0016f630(p3fes::EEContext&);  // the item id in an equipment slot (pc, idx)
void fn_sub_170D60_00170d60(p3fes::EEContext&);  // the 40-byte weapon record of an item id
void fn_sub_173380_00173380(p3fes::EEContext&);  // datPersonaGetSkillsByPcId
void fn_sub_173460_00173460(p3fes::EEContext&);  // a party member's affinity word for an element (through the persona)
void fn_sub_16F9F0_0016f9f0(p3fes::EEContext&);  // weapon power
void fn_sub_16FAE0_0016fae0(p3fes::EEContext&);  // weapon accuracy
void fn_sub_16FCC0_0016fcc0(p3fes::EEContext&);  // armour defense
void fn_sub_16FBD0_0016fbd0(p3fes::EEContext&);  // armour evasion
void fn_datCalcGetMaxHp_002ffdf0(p3fes::EEContext&);  // datCalcGetMaxHp
void fn_datGetFlag_0016f190(p3fes::EEContext&);  // datGetFlag
void fn_datCalcHasSkill_003005e0(p3fes::EEContext&);  // datCalcHasSkill(unit, skill)
void fn_sub_300750_00300750(p3fes::EEContext&);  // a party member's equipment slots 0..2 carry an effect
void fn_sub_300870_00300870(p3fes::EEContext&);  // a party member's accessory carries an effect
void fn_sub_16C920_0016c920(p3fes::EEContext&);  // a party member's condition (u16; 4/5 and 1/2 matter here)
void fn_datCalcGetEffectMultiplier_00301880(p3fes::EEContext&);  // buff multiplier (unit, kind, skill) -> $f0
void fn_datCalcRand_002ffbc0(p3fes::EEContext&);  // datCalcRand(n)
void fn_sub_17D800_0017d800(p3fes::EEContext&);  // reads gp-19788 (result unused by datCalcCheckHit)
void fn_datScriptCalc_0030fc40(p3fes::EEContext&);  // datScriptCalc(formula, attacker, target, skill, $t0)
void fn_datCalcGetMaxSp_00300100(p3fes::EEContext&);  // datCalcGetMaxSp
void fn_clndGetCurrentMoonPhase_00181b10(p3fes::EEContext&);  // the moon phase 0..29
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

using namespace bview;  // hi / lo / gp_off / flt / k_assert / u32_to_float and the record offsets (battle_view.h)

namespace {

using namespace btl;

}  // namespace

// ================================================================================================================
// Unit / weapon helpers
// ================================================================================================================

// 0x003082F0 datCalcGetSkillElement -- 244 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// datCalcGetSkillElement(unit, skill): the element row of a skill (SKILL.TBL section 0, s8). For a physical skill
// used by a unit the weapon decides: an enemy's normal-attack skill (EnemyRecord +60) is looked up instead, a party
// member's element is the s16 at +30 of the held weapon's item record (sub_170D60).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void datCalcGetSkillElement(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::lb, hg::lbu,
          hg::ld, hg::lh, hg::lhu, hg::lq, hg::lw, hg::sd, hg::sll, hg::slti, hg::sq, hg::subu;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    auto epilogue = [&] {  // 0x003083d0
        charge(ctx, 5);
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
    };
    // 0x003082f0: prologue; s0 = unit, a0 = (u16)skill
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = a1 & 0xFFFF;
    if (s0 != 0) {
        // 0x0030830c: a unit and a valid skill id ...
        charge(ctx, 3);
        at = slti(a0, btl::kSkillCount);
        if (at != 0) {
            // 0x00308318: ... and a physical skill: the weapon decides
            charge(ctx, 11);
            v0 = sll(a0, 2);
            v0 = addu(v0, a0);
            v0 = sll(v0, 1);
            v0 = addu(v0, a0);
            v1 = sll(v0, 2);  // * 44 (SkillRecord)
            lw(v0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
            v0 = addu(v0, v1);
            lbu(v0, v0, skill_rec::kFlags0);
            v0 = v0 & skill_rec::kFlagPhysical;
            if (v0 != 0) {
                // 0x00308344
                charge(ctx, 4);
                lhu(v0, s0, dat_unit::kFlags);
                v0 = v0 & dat_unit::kFlagEnemy;
                if (v0 != 0) {
                    // 0x00308354: an enemy: a0 = its normal-attack skill (EnemyRecord +60)
                    charge(ctx, 9);
                    lhu(v1, s0, dat_unit::kId);
                    v0 = sll(v1, 5);
                    v0 = subu(v0, v1);
                    v1 = sll(v0, 1);  // * 62 (EnemyRecord)
                    lw(v0, gp, gp_off(btl::kUnitTablePtr));  // gBtlEnemyTbl
                    v0 = addu(v1, v0);
                    lhu(a0, v0, enemy_rec::kAttackSkill);
                } else {
                    // 0x00308378: a party member: return the held weapon's element, (s16)item +30 of sub_170D60(
                    // sub_16F630(id, datGetEquipmentIdx(id, 0)))
                    charge(ctx, 17);
                    lh(a0, s0, dat_unit::kId);
                    a1 = 0;
                    jal(ctx, 0x308380u, gen::fn_datGetEquipmentIdx_0016cb80);
                    a1 = dsll32(v0, 16);
                    a1 = dsra32(a1, 16);
                    lh(a0, s0, dat_unit::kId);
                    jal(ctx, 0x308394u, gen::fn_sub_16F630_0016f630);
                    v0 = v0 & 0xFFFF;
                    a0 = dsll32(v0, 16);
                    a0 = dsra32(a0, 16);
                    jal(ctx, 0x3083A8u, gen::fn_sub_170D60_00170d60);
                    lh(v0, v0, 30);
                    epilogue();
                    return;
                }
            }
        }
    }
    // 0x003083bc: return SKILL.TBL section 0[skill * 2] (s8)
    charge(ctx, 5);
    v0 = a0 & 0xFFFF;
    v1 = sll(v0, 1);
    lw(v0, gp, gp_off(btl::kSkillElementTablePtr));  // gBtlSkillElementTbl
    v0 = addu(v0, v1);
    lb(v0, v0, 0);
    epilogue();
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
s64 datCalcGetSkillElement(EEContext& ctx, u32 unit, u32 skill) {
    ee::core::set_gpr64(ctx, GPR_A0, ee::core::sext32(static_cast<u32>(unit)));
    ee::core::set_gpr64(ctx, GPR_A1, ee::core::sext32(static_cast<u32>(skill)));
    datCalcGetSkillElement(ctx);
    return static_cast<s64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x003086C0 sub_3086C0 -- 44 bytes; leaf frame (no stack)
// (proposed datCalcGetSkillByte3)(unused, skill): SkillRecord +3 (no range check).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_3086C0(EEContext& ctx) {
    using hg::Gpr, hg::addu, hg::enter, hg::lbu, hg::lw, hg::sll;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x003086c0: entry
    enter(ctx, 11);  // entry check point + this block's cycles
    lw(a0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
    v1 = a1 & 0xFFFF;
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);  // * 44 (SkillRecord)
    v0 = addu(v0, a0);
    lbu(v0, v0, skill_rec::kByte3);
}

// 0x00308860 sub_308860 -- 72 bytes; leaf frame (no stack)
// (proposed datCalcIsMixRaidSkill)(id): 0xC0 <= id < 0xC6 (a six-entry jump table, every entry -> 1).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_308860(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::lw, hg::sll, hg::sltiu, hg::tail;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00308860: entry
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = a0 & 0xFFFF;
    v0 = addiu(v0, -192);
    at = sltiu(v0, 6);
    if (at == 0) {
        // 0x0030889c
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00308874
        charge(ctx, 7);
        v1 = hi(0x7B8FD0u);
        v1 = addiu(v1, lo(0x7B8FD0u));  // &0x7B8FD0
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x308890u:  // table[0, 1, 2, 3, 4, 5]
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x00308890
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x003088a0: epilogue
    charge(ctx, 2);
}

// 0x00308A50 sub_308A50 -- 48 bytes; leaf frame (no stack)
// (proposed datCalcIsSkillInBand110)(id): 0x110 <= id < 0x131.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_308A50(EEContext& ctx) {
    using hg::Gpr, hg::charge, hg::enter, hg::slti, hg::sltu;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00308a50: entry
    enter(ctx, 5);  // entry check point + this block's cycles
    a1 = 0;
    v1 = a0 & 0xFFFF;
    v0 = slti(v1, 272);
    if (v0 == 0) {
        // 0x00308a64
        charge(ctx, 3);
        at = slti(v1, 305);
        if (at != 0) {
            // 0x00308a70
            charge(ctx, 1);
            a1 = 1;
        }
    }
    // 0x00308a74: epilogue
    charge(ctx, 3);
    v0 = sltu(0, a1);
}

// 0x308BA0 datCalcGetSkillSlotCount(): 8.
u32 datCalcGetSkillSlotCount(EEContext& ctx) {
    guest::enter(ctx, 3);
    return 8;
}

// 0x00308BB0 datCalcGetSkillList -- 172 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// datCalcGetSkillList(unit): the address of the eight skill ids -- EnemyRecord +14 for an enemy
// (K_Assert line 4180 on id >= 336), datPersonaGetSkillsByPcId(id) for a party member (line 4177 on id >= 11).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void datCalcGetSkillList(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lq, hg::lw, hg::sd,
          hg::sll, hg::slti, hg::sq, hg::subu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00308bb0: prologue
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lhu(v0, a0, dat_unit::kFlags);
    v0 = v0 & dat_unit::kFlagEnemy;
    if (v0 != 0) {
        // 0x00308c08
        charge(ctx, 4);
        lhu(v0, s0, dat_unit::kId);
        v0 = slti(v0, enemy_rec::kCount);
        if (v0 == 0) {
            // 0x00308c18
            charge(ctx, 5);
            k_assert(a0, a1, 0x308C24u, kDatCalcFile, 4180);
        }
        // 0x00308c2c
        charge(ctx, 7);
        lhu(v1, s0, dat_unit::kId);
        v0 = sll(v1, 5);
        v0 = subu(v0, v1);
        v1 = sll(v0, 1);  // * 62 (EnemyRecord)
        lw(v0, gp, gp_off(btl::kUnitTablePtr));  // gBtlEnemyTbl
        v0 = addu(v0, v1);
        v0 = addiu(v0, enemy_rec::kSkills);
    } else {
        // 0x00308bd0
        charge(ctx, 4);
        lhu(v0, s0, dat_unit::kId);
        v0 = slti(v0, dat_unit::kPartyIds);
        if (v0 == 0) {
            // 0x00308be0
            charge(ctx, 5);
            k_assert(a0, a1, 0x308BECu, kDatCalcFile, 4177);
        }
        // 0x00308bf4
        charge(ctx, 5);
        lhu(a0, s0, dat_unit::kId);
        jal(ctx, 0x308BF8u, gen::fn_sub_173380_00173380);
    }
    // 0x00308c48: epilogue
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00308930 sub_308930 -- 276 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// (proposed datCalcGetAttackSkill)(unit): an enemy's normal-attack skill (EnemyRecord +60); for a party
// member the weapon type at item +30 (u16) selects one of the six attack skills 346..351 (0 for type 0 or > 6).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void sub_308930(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld, hg::lh,
          hg::lhu, hg::lq, hg::lw, hg::sd, hg::sll, hg::sltiu, hg::sq, hg::subu, hg::tail;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00308930: prologue
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lhu(v0, a0, dat_unit::kFlags);
    v0 = v0 & dat_unit::kFlagEnemy;
    if (v0 == 0) {
        // 0x00308974
        charge(ctx, 18);
        lh(a0, s0, dat_unit::kId);
        a1 = 0;
        jal(ctx, 0x30897Cu, gen::fn_datGetEquipmentIdx_0016cb80);
        a1 = dsll32(v0, 16);
        a1 = dsra32(a1, 16);
        lh(a0, s0, dat_unit::kId);
        jal(ctx, 0x308990u, gen::fn_sub_16F630_0016f630);
        v0 = v0 & 0xFFFF;
        a0 = dsll32(v0, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x3089A4u, gen::fn_sub_170D60_00170d60);
        lhu(v0, v0, 30);
        at = sltiu(v0, 7);
        if (at == 0) {
            // 0x00308a2c
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x003089bc
            charge(ctx, 7);
            v1 = hi(0x7B8FF0u);
            v1 = addiu(v1, lo(0x7B8FF0u));  // &0x7B8FF0
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x3089D8u:  // table[0]
                // 0x003089d8
                charge(ctx, 3);
                v0 = 0;
                break;
            case 0x3089E4u:  // table[1]
                // 0x003089e4
                charge(ctx, 3);
                v0 = 351;
                break;
            case 0x3089F0u:  // table[2]
                // 0x003089f0
                charge(ctx, 3);
                v0 = 350;
                break;
            case 0x3089FCu:  // table[3]
                // 0x003089fc
                charge(ctx, 3);
                v0 = 349;
                break;
            case 0x308A08u:  // table[5]
                // 0x00308a08
                charge(ctx, 3);
                v0 = 348;
                break;
            case 0x308A14u:  // table[6]
                // 0x00308a14
                charge(ctx, 3);
                v0 = 347;
                break;
            case 0x308A20u:  // table[4]
                // 0x00308a20
                charge(ctx, 3);
                v0 = 346;
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
        }
    } else {
        // 0x00308950
        charge(ctx, 9);
        lhu(v1, s0, dat_unit::kId);
        v0 = sll(v1, 5);
        v0 = subu(v0, v1);
        v1 = sll(v0, 1);  // * 62 (EnemyRecord)
        lw(v0, gp, gp_off(btl::kUnitTablePtr));  // gBtlEnemyTbl
        v0 = addu(v1, v0);
        lhu(v0, v0, enemy_rec::kAttackSkill);
    }
    // 0x00308a30: epilogue
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00308C60 datCalcGetHeldWeaponType -- 612 bytes; frame 0x10: ra sp+0x0
// datCalcGetHeldWeaponType(unit): 0 for an enemy; for party members 2..10 a constant per character (jump table
// 0x7B9030), for the hero (who can hold every type) the weapon record's +4 type mask, tested in pairs (0x8000/0x80 ->
// 5, 0x4000/0x40 -> 7, 0x2000/0x20 -> 3, 0x1000/0x10 -> 2, 0x800/0x8 -> 4, 0x400/0x4 -> 6, 0x200/0x2 -> 0, 0x100/0x1 ->
// 1; anything else K_Assert line 4237 and 0). Id 0 and ids >= 11: line 4259, 0.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void datCalcGetHeldWeaponType(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld, hg::lhu,
          hg::lw, hg::sd, hg::sll, hg::sltiu, hg::tail;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // The hero's type-mask pairs in the order the compiled ladder tests them: `v0 = big; beq v1, v0` then
    // `v0 = small; beq v1, v0`, each test after the first in its own 3-cycle block.
    struct MaskPair {
        u32 big, small;
        u32 type;
    };
    static constexpr MaskPair kPairs[] = {{0x8000, 0x80, 5}, {0x4000, 0x40, 7}, {0x2000, 0x20, 3}, {0x1000, 0x10, 2},
                                          {0x800, 0x8, 4},   {0x400, 0x4, 6},   {0x200, 0x2, 0},   {0x100, 0x1, 1}};
    // 0x00308c60: prologue; an enemy?
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lhu(v0, a0, dat_unit::kFlags);
    v0 = v0 & dat_unit::kFlagEnemy;
    if (v0 == 0) {
        // 0x00308c84: a party member: dispatch on id 0..10 (jump table 0x7B9030)
        charge(ctx, 4);
        lhu(v0, a0, dat_unit::kId);
        at = sltiu(v0, dat_unit::kPartyIds);
        bool bad_id = at == 0;
        if (!bad_id) {
            // 0x00308c94
            charge(ctx, 7);
            v1 = hi(0x7B9030u);
            v1 = addiu(v1, lo(0x7B9030u));  // &0x7B9030
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x308CB0u: {  // table[1]: the hero
                // 0x00308cb0: v1 = the type mask (+4) of sub_170D60(sub_16F630(1, datGetEquipmentIdx(1, 0)))
                charge(ctx, 18);
                a0 = dat_unit::kHero;
                a1 = 0;
                jal(ctx, 0x308CB8u, gen::fn_datGetEquipmentIdx_0016cb80);
                a1 = dsll32(v0, 16);
                a1 = dsra32(a1, 16);
                a0 = dat_unit::kHero;
                jal(ctx, 0x308CCCu, gen::fn_sub_16F630_0016f630);
                v0 = v0 & 0xFFFF;
                a0 = dsll32(v0, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x308CE0u, gen::fn_sub_170D60_00170d60);
                lw(v1, v0, 4);
                // 0x00308cf0..0x00308da0: the mask ladder
                int found = -1;
                for (int i = 0; i < 8; ++i) {
                    if (i > 0) {
                        charge(ctx, 3);
                    }
                    v0 = kPairs[i].big;
                    if (v1 == v0) {
                        found = i;
                        break;
                    }
                    charge(ctx, 3);
                    v0 = kPairs[i].small;
                    if (v1 == v0) {
                        found = i;
                        break;
                    }
                }
                if (found >= 0) {
                    // 0x00308e08 .. 0x00308db4: the pair's type
                    charge(ctx, 3);
                    v0 = kPairs[found].type;
                } else {
                    // 0x00308dac, 0x00308e14, 0x00308eb0: no single type: K_Assert, 0
                    charge(ctx, 2);
                    charge(ctx, 7);
                    k_assert(a0, a1, 0x308E20u, kDatCalcFile, 4237);
                    charge(ctx, 1);
                    v0 = 0;
                }
                break;
            }
            case 0x308E30u:  // table[2]
                // 0x00308e30
                charge(ctx, 3);
                v0 = 6;
                break;
            case 0x308E3Cu:  // table[3]
                // 0x00308e3c
                charge(ctx, 3);
                v0 = 7;
                break;
            case 0x308E48u:  // table[4]
                // 0x00308e48
                charge(ctx, 3);
                v0 = 0;
                break;
            case 0x308E54u:  // table[5]
                // 0x00308e54
                charge(ctx, 3);
                v0 = 1;
                break;
            case 0x308E60u:  // table[6]
                // 0x00308e60
                charge(ctx, 3);
                v0 = 0;
                break;
            case 0x308E6Cu:  // table[7]
                // 0x00308e6c
                charge(ctx, 3);
                v0 = 3;
                break;
            case 0x308E78u:  // table[8]
                // 0x00308e78
                charge(ctx, 3);
                v0 = 4;
                break;
            case 0x308E84u:  // table[9]
                // 0x00308e84
                charge(ctx, 3);
                v0 = 2;
                break;
            case 0x308E90u:  // table[10]
                // 0x00308e90
                charge(ctx, 3);
                v0 = 5;
                break;
            case 0x308E9Cu:  // table[0]: id 0
                bad_id = true;
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
        }
        if (bad_id) {
            // 0x00308e9c, 0x00308eb0: id 0 or >= 11: K_Assert, 0
            charge(ctx, 5);
            k_assert(a0, a1, 0x308EA8u, kDatCalcFile, 4259);
            charge(ctx, 1);
            v0 = 0;
        }
    } else {
        // 0x00308c78: an enemy: 0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00308eb4: epilogue
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u32 datCalcGetHeldWeaponType(EEContext& ctx, u32 unit) {
    ee::core::set_gpr64(ctx, GPR_A0, ee::core::sext32(static_cast<u32>(unit)));
    datCalcGetHeldWeaponType(ctx);
    return static_cast<u32>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x00308ED0 sub_308ED0 -- 176 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// (proposed datCalcGetHeldWeaponId)(unit): 0 for an enemy; for a party member the item id in equipment
// slot 0 (u16; K_Assert line 4280 on id >= 11 and line 4285 on an item id >= 255).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void sub_308ED0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld, hg::lh, hg::lhu,
          hg::lq, hg::sd, hg::slti, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00308ed0: prologue
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lhu(v0, a0, dat_unit::kFlags);
    v0 = v0 & dat_unit::kFlagEnemy;
    if (v0 == 0) {
        // 0x00308efc
        charge(ctx, 4);
        lhu(v0, s0, dat_unit::kId);
        v0 = slti(v0, dat_unit::kPartyIds);
        if (v0 == 0) {
            // 0x00308f0c
            charge(ctx, 5);
            k_assert(a0, a1, 0x308F18u, kDatCalcFile, 4280);
        }
        // 0x00308f20
        charge(ctx, 13);
        lh(a0, s0, dat_unit::kId);
        a1 = 0;
        jal(ctx, 0x308F28u, gen::fn_datGetEquipmentIdx_0016cb80);
        a1 = dsll32(v0, 16);
        a1 = dsra32(a1, 16);
        lh(a0, s0, dat_unit::kId);
        jal(ctx, 0x308F3Cu, gen::fn_sub_16F630_0016f630);
        s0 = v0 & 0xFFFF;
        v0 = slti(s0, 255);
        if (v0 == 0) {
            // 0x00308f54
            charge(ctx, 5);
            k_assert(a0, a1, 0x308F60u, kDatCalcFile, 4285);
        }
        // 0x00308f68
        charge(ctx, 1);
        v0 = s0;
    } else {
        // 0x00308ef0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00308f6c: epilogue
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00308F80 sub_308F80 -- 76 bytes; frame 0x10: ra sp+0x0
// (proposed datCalcGetWeaponClass)(unit): 1 for an enemy, else the byte of 0x7CC9F8 indexed by the held
// weapon type.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void sub_308F80(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lhu, hg::sd;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00308f80: prologue
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lhu(v0, a0, dat_unit::kFlags);
    v0 = v0 & dat_unit::kFlagEnemy;
    if (v0 == 0) {
        // 0x00308fa4
        charge(ctx, 6);
        jal(ctx, 0x308FA4u, gen::fn_datCalcGetHeldWeaponType_00308c60);
        v1 = v0 & 0xFF;
        v0 = addiu(gp, gp_off(btl::kWeaponClassTable));
        v0 = addu(v0, v1);
        lbu(v0, v0, 0);
    } else {
        // 0x00308f98
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x00308fbc: epilogue
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00308FD0 sub_308FD0 -- 164 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// (proposed datCalcGetWeaponHitClass)(unit, mode): the weapon class as in sub_308F80 (1 for an enemy);
// class 1 stays 1; otherwise a mode with bit 1 or 2 set returns the class, mode 8 returns 2 and any other mode 1.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void sub_308FD0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lhu, hg::lq, hg::sd,
          hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00308fd0: prologue
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    lhu(v0, a0, dat_unit::kFlags);
    v0 = v0 & dat_unit::kFlagEnemy;
    if (v0 == 0) {
        // 0x00308ffc
        charge(ctx, 6);
        jal(ctx, 0x308FFCu, gen::fn_datCalcGetHeldWeaponType_00308c60);
        v1 = v0 & 0xFF;
        v0 = addiu(gp, gp_off(btl::kWeaponClassTable));
        v0 = addu(v0, v1);
        lbu(a1, v0, 0);
    } else {
        // 0x00308ff0
        charge(ctx, 3);
        a1 = 1;
    }
    // 0x00309014
    charge(ctx, 4);
    v1 = a1 & 0xFF;
    v0 = 1;
    if (v1 != v0) {
        // 0x0030902c
        charge(ctx, 4);
        a0 = s0 & 0xFFFF;
        v1 = a0 & 0x6;
        if (v1 == 0) {
            // 0x00309048
            charge(ctx, 3);
            v1 = 8;
            if (a0 == v1) {
                // 0x00309054
                charge(ctx, 3);
                v0 = 2;
            }
        } else {
            // 0x0030903c
            charge(ctx, 3);
            v0 = a1;
        }
    } else {
        // 0x00309024
        charge(ctx, 2);
    }
    // 0x00309060: epilogue
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003093A0 sub_3093A0 [datCalcGetWeaponAiCalcByte] -- 236 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_3093A0(unit): AICALC.TBL section 7 [weapon id - 0xC0] for the held weapon (an enemy counts as id 0; K_Assert
// line 4447 outside 0xC0..0xDF, the read still happens). Register-faithful (p3fes_handgen body; audit 2026-10-21: own
// frame / spills).
void sub_3093A0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::lbu, hg::ld,
          hg::lh, hg::lhu, hg::lq, hg::lw, hg::sd, hg::slti, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003093a0: prologue; v0 = the held weapon's item id (sub_308ED0 inlined)
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lhu(v0, a0, dat_unit::kFlags);
    v0 = v0 & dat_unit::kFlagEnemy;
    if (v0 == 0) {
        // 0x003093cc: a party member: K_Assert(id < 11)
        charge(ctx, 4);
        lhu(v0, s0, dat_unit::kId);
        v0 = slti(v0, dat_unit::kPartyIds);
        if (v0 == 0) {
            // 0x003093dc
            charge(ctx, 5);
            k_assert(a0, a1, 0x3093E8u, kDatCalcFile, 4280);
        }
        // 0x003093f0: s0 = (u16)sub_16F630(id, datGetEquipmentIdx(id, 0)); K_Assert(s0 < 255)
        charge(ctx, 13);
        lh(a0, s0, dat_unit::kId);
        a1 = 0;
        jal(ctx, 0x3093F8u, gen::fn_datGetEquipmentIdx_0016cb80);
        a1 = dsll32(v0, 16);
        a1 = dsra32(a1, 16);
        lh(a0, s0, dat_unit::kId);
        jal(ctx, 0x30940Cu, gen::fn_sub_16F630_0016f630);
        s0 = v0 & 0xFFFF;
        v0 = slti(s0, 255);
        if (v0 == 0) {
            // 0x00309424
            charge(ctx, 5);
            k_assert(a0, a1, 0x309430u, kDatCalcFile, 4285);
        }
        // 0x00309438
        charge(ctx, 1);
        v0 = s0 & 0xFFFF;
    } else {
        // 0x003093c0: an enemy: id 0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0030943c: s0 = id; K_Assert(0xC0 <= id < 0xE0)
    charge(ctx, 4);
    s0 = v0 & 0xFFFF;
    v0 = slti(s0, 192);
    bool in_band = false;
    if (v0 == 0) {
        // 0x0030944c
        charge(ctx, 3);
        v0 = slti(s0, 224);
        in_band = v0 != 0;
    }
    if (!in_band) {
        // 0x00309458
        charge(ctx, 5);
        k_assert(a0, a1, 0x309464u, kDatCalcFile, 4447);
    }
    // 0x0030946c: return AICALC7[id - 0xC0]; epilogue
    charge(ctx, 8);
    lw(v0, gp, gp_off(btl::kAiCalc7TablePtr));  // 0x7CE48C
    v0 = addu(s0, v0);
    lbu(v0, v0, -192);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00309080 datCalcGetWeaponParam -- 452 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// datCalcGetWeaponParam(unit, which): which 0 = power, 1 = accuracy. An enemy reads its normal attack from
// EnemyRecord +58 (u16 power) / +56 (u8 accuracy) -- K_Assert line 4358 on id >= 336 and line 4360 when the record's
// attack skill (+60) is not physical; a party member asks the weapon (sub_16F9F0 / sub_16FAE0 with the slot-0
// equipment index). Any other `which`: K_Assert line 4370 / 4383 and 0.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void datCalcGetWeaponParam(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::lbu, hg::ld,
          hg::lhu, hg::lq, hg::lw, hg::sd, hg::sll, hg::slti, hg::sq, hg::subu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00309080: prologue; s1 = which
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    lhu(v0, a0, dat_unit::kFlags);
    v0 = v0 & dat_unit::kFlagEnemy;
    if (v0 == 0) {
        // 0x00309188: a party member: K_Assert(id < 11)
        charge(ctx, 4);
        lhu(s0, a0, dat_unit::kId);
        v0 = slti(s0, dat_unit::kPartyIds);
        if (v0 == 0) {
            // 0x00309198
            charge(ctx, 5);
            k_assert(a0, a1, 0x3091A4u, kDatCalcFile, 4374);
        }
        // 0x003091ac: a1 = datGetEquipmentIdx(id, 0), the weapon slot
        charge(ctx, 12);
        s0 = dsll32(s0, 16);
        s0 = dsra32(s0, 16);
        a0 = s0;
        a1 = 0;
        jal(ctx, 0x3091BCu, gen::fn_datGetEquipmentIdx_0016cb80);
        a1 = dsll32(v0, 16);
        a1 = dsra32(a1, 16);
        v1 = s1 & 0xFF;
        v0 = 1;
        if (v1 == v0) {
            // 0x00309200: accuracy: sub_16FAE0(id, idx)
            charge(ctx, 5);
            a0 = s0;
            jal(ctx, 0x309204u, gen::fn_sub_16FAE0_0016fae0);
        } else {
            // 0x003091dc
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x003091ec: power: sub_16F9F0(id, idx)
                charge(ctx, 5);
                a0 = s0;
                jal(ctx, 0x3091F0u, gen::fn_sub_16F9F0_0016f9f0);
            } else {
                // 0x003091e4, 0x00309214, 0x00309228: another `which`: K_Assert, 0
                charge(ctx, 2);
                charge(ctx, 5);
                k_assert(a0, a1, 0x309220u, kDatCalcFile, 4383);
                charge(ctx, 1);
                v0 = 0;
            }
        }
    } else {
        // 0x003090a4: an enemy: K_Assert(id < 336)
        charge(ctx, 4);
        lhu(s0, a0, dat_unit::kId);
        v0 = slti(s0, enemy_rec::kCount);
        if (v0 == 0) {
            // 0x003090b4
            charge(ctx, 5);
            k_assert(a0, a1, 0x3090C0u, kDatCalcFile, 4358);
        }
        // 0x003090c8: s0 = id * 62; K_Assert(the record's attack skill is physical)
        charge(ctx, 18);
        v1 = s0 & 0xFFFF;
        v0 = sll(v1, 5);
        v0 = subu(v0, v1);
        s0 = sll(v0, 1);  // * 62 (EnemyRecord)
        lw(v0, gp, gp_off(btl::kUnitTablePtr));  // gBtlEnemyTbl
        v0 = addu(s0, v0);
        lhu(v1, v0, enemy_rec::kAttackSkill);
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 1);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);  // * 44 (SkillRecord)
        lw(v0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
        v0 = addu(v0, v1);
        lbu(v0, v0, skill_rec::kFlags0);
        v0 = v0 & skill_rec::kFlagPhysical;
        if (v0 == 0) {
            // 0x00309110
            charge(ctx, 5);
            k_assert(a0, a1, 0x30911Cu, kDatCalcFile, 4360);
        }
        // 0x00309124
        charge(ctx, 4);
        v1 = s1 & 0xFF;
        v0 = 1;
        if (v1 == v0) {
            // 0x00309158: accuracy: EnemyRecord +56 (u8)
            charge(ctx, 5);
            lw(v0, gp, gp_off(btl::kUnitTablePtr));
            v0 = addu(s0, v0);
            lbu(v0, v0, enemy_rec::kAttackAccuracy);
        } else {
            // 0x00309134
            charge(ctx, 2);
            if (v1 != 0) {
                // 0x0030913c, 0x0030916c, 0x00309228: another `which`: K_Assert, 0
                charge(ctx, 2);
                charge(ctx, 7);
                k_assert(a0, a1, 0x309178u, kDatCalcFile, 4370);
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x00309144: power: EnemyRecord +58 (u16)
                charge(ctx, 5);
                lw(v0, gp, gp_off(btl::kUnitTablePtr));
                v0 = addu(s0, v0);
                lhu(v0, v0, enemy_rec::kAttackPower);
            }
        }
    }
    // 0x0030922c: epilogue
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00309250 datCalcGetArmorParam -- 336 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// datCalcGetArmorParam(unit, which): which 0 = defense, 1 = evasion; 10 for an enemy. A party member asks the armour:
// defense sub_16FCC0 with the equipment index of slot 2, evasion sub_16FBD0 with slot 1 (the compiled code reuses
// the `which` register as the slot argument). Any other `which`: K_Assert 4413 / 4427, 0.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void datCalcGetArmorParam(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lq,
          hg::sd, hg::slti, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00309250: prologue; s1 = which
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    lhu(v0, a0, dat_unit::kFlags);
    v0 = v0 & dat_unit::kFlagEnemy;
    if (v0 == 0) {
        // 0x003092c8: a party member: K_Assert(id < 11)
        charge(ctx, 4);
        lhu(s0, a0, dat_unit::kId);
        v0 = slti(s0, dat_unit::kPartyIds);
        if (v0 == 0) {
            // 0x003092d8
            charge(ctx, 5);
            k_assert(a0, a1, 0x3092E4u, kDatCalcFile, 4417);
        }
        // 0x003092ec
        charge(ctx, 4);
        v0 = s1 & 0xFF;
        a1 = 1;
        if (v0 == a1) {
            // 0x00309340: evasion: sub_16FBD0(id, datGetEquipmentIdx(id, 1)) (a1 = 1 is the slot)
            charge(ctx, 12);
            s0 = dsll32(s0, 16);
            s0 = dsra32(s0, 16);
            a0 = s0;
            jal(ctx, 0x30934Cu, gen::fn_datGetEquipmentIdx_0016cb80);
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            a0 = s0;
            jal(ctx, 0x309360u, gen::fn_sub_16FBD0_0016fbd0);
        } else {
            // 0x003092fc
            charge(ctx, 2);
            if (v0 == 0) {
                // 0x0030930c: defense: sub_16FCC0(id, datGetEquipmentIdx(id, 2))
                charge(ctx, 13);
                s0 = dsll32(s0, 16);
                s0 = dsra32(s0, 16);
                a0 = s0;
                a1 = 2;
                jal(ctx, 0x30931Cu, gen::fn_datGetEquipmentIdx_0016cb80);
                a1 = dsll32(v0, 16);
                a1 = dsra32(a1, 16);
                a0 = s0;
                jal(ctx, 0x309330u, gen::fn_sub_16FCC0_0016fcc0);
            } else {
                // 0x00309304, 0x00309370, 0x00309384: another `which`: K_Assert, 0
                charge(ctx, 2);
                charge(ctx, 5);
                k_assert(a0, a1, 0x30937Cu, kDatCalcFile, 4427);
                charge(ctx, 1);
                v0 = 0;
            }
        }
    } else {
        // 0x00309274: an enemy: 10 for both
        charge(ctx, 4);
        v1 = s1 & 0xFF;
        v0 = 1;
        if (v1 == v0) {
            // 0x003092a0
            charge(ctx, 3);
            v0 = 10;
        } else {
            // 0x00309284
            charge(ctx, 2);
            if (v1 != 0) {
                // 0x0030928c, 0x003092ac, 0x00309384: another `which`: K_Assert, 0
                charge(ctx, 2);
                charge(ctx, 7);
                k_assert(a0, a1, 0x3092B8u, kDatCalcFile, 4413);
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x00309294
                charge(ctx, 3);
                v0 = 10;
            }
        }
    }
    // 0x00309388: epilogue
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0030B4B0 datCalcGetAffinityChecked -- 232 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// datCalcGetAffinityChecked(unit, element): -1 -> 0, the neutral rows 16..18 -> 100, else
// datCalcGetAffinity (K_Assert lines 5451 and 3752 for element >= 19; the element bit is 1 << (e + 1) mod 32).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void datCalcGetAffinityChecked(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld, hg::lq, hg::sd, hg::si,
          hg::sllv, hg::slti, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0030b4b0: prologue
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    s2 = dsll32(s0, 16);
    s2 = dsra32(s2, 16);
    v0 = si(-1);
    if (s2 != v0) {
        // 0x0030b4ec
        charge(ctx, 3);
        v0 = slti(s2, 19);
        if (v0 == 0) {
            // 0x0030b4f8
            charge(ctx, 5);
            k_assert(a0, a1, 0x30B504u, kDatCalcFile, 5451);
        }
        // 0x0030b50c
        charge(ctx, 3);
        v0 = slti(s2, 19);
        if (v0 == 0) {
            // 0x0030b518
            charge(ctx, 5);
            k_assert(a0, a1, 0x30B524u, kDatCalcFile, 3752);
        }
        // 0x0030b52c
        charge(ctx, 6);
        v1 = addiu(s2, 1);
        v0 = 1;
        v1 = sllv(v0, v1);
        v0 = v1 & 0x1;
        if (v0 == 0) {
            // 0x0030b550
            charge(ctx, 4);
            v0 = 0xE0000;
            v0 = v1 & v0;
            if (v0 == 0) {
                // 0x0030b56c
                charge(ctx, 4);
                a0 = s1;
                a1 = s0;
                jal(ctx, 0x30B574u, gen::fn_datCalcGetAffinity_00306e80);
            } else {
                // 0x0030b560
                charge(ctx, 3);
                v0 = 100;
            }
        } else {
            // 0x0030b544
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0030b4e0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0030b57c: epilogue
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 datCalcGetAffinityChecked(EEContext& ctx, u32 unit, u32 element) {
    ee::core::set_gpr64(ctx, GPR_A0, ee::core::sext32(static_cast<u32>(unit)));
    ee::core::set_gpr64(ctx, GPR_A1, ee::core::sext32(static_cast<u32>(element)));
    datCalcGetAffinityChecked(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x0030B5E0 datCalcIsLowHp -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// datCalcIsLowHp(unit): 100 * hp / datCalcGetMaxHp(unit) < 26 (EE `div`; a zero maximum gives LO = -1).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void datCalcIsLowHp(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::div, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lq, hg::mflo, hg::sd,
          hg::sll, hg::slti, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0030b5e0: prologue
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lhu(s0, a0, dat_unit::kHp);
    jal(ctx, 0x30B5F0u, gen::fn_datCalcGetMaxHp_002ffdf0);
    a0 = v0 & 0xFFFF;
    v1 = s0 & 0xFFFF;
    v0 = sll(v1, 2);
    v1 = addu(v0, v1);
    v0 = sll(v1, 2);
    v0 = addu(v1, v0);
    v0 = sll(v0, 2);
    div(v0, a0);
    mflo(v0);
    v0 = slti(v0, 26);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// ================================================================================================================
// 0x306E80 datCalcGetAffinity(unit, element)
// ================================================================================================================

// 0x00306E80 datCalcGetAffinity -- 4664 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// The affinity word of `unit` for element row `element` (s16): the neutral rows 16..18 are 100, -1 is 0. An
// enemy's word comes from UNIT.TBL section 1 (u16 [base_id][element]: rate = 5 x low byte, high byte -> bits
// 24..31); a zero rate is made explicit from the flags (weak 125, or 150 with flag 4889; null/repel/absorb 100;
// resist 50). A party member's word comes from the persona (sub_173460). Then, by row: the passive skills collect
// resist / null / repel / absorb bits, the walls of buff slots 13..16 a "wall" flag, and the equipment effects
// 73..99 a "plain rate" flag (which also takes 82..84 for the rows 0..2 and 97..99 for the rows 3..6). Skill 507
// adds null for every row but 7. The bits are then merged into the word: the plain-rate flag removes weakness, a
// skill bit replaces the weaker flags and sets its rate (resist 50, the others 100) unless a stronger flag is
// there, a wall clears null/repel/absorb/resist and sets 100. K_Assert lines 3371 (no unit), 3372 (row out of
// range) and 3383 (enemy id >= 336) are no-ops; the reads go ahead.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void datCalcGetAffinity(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::i64, hg::jal, hg::ld,
          hg::lhu, hg::lq, hg::lui, hg::lw, hg::sd, hg::si, hg::sll, hg::slti, hg::sltiu, hg::sq, hg::tail;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00306e80: prologue
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = 0;
    s5 = 0;
    s1 = 0;
    s0 = dsll32(s3, 16);
    s0 = dsra32(s0, 16);
    v0 = 18;
    if (s0 != v0) {
        // 0x00306ec8
        charge(ctx, 3);
        v0 = 17;
        if (s0 == v0) {
            goto L_00306f00;
        }
        // 0x00306ed4
        charge(ctx, 3);
        v0 = 16;
        if (s0 == v0) {
            goto L_00306f00;
        }
        // 0x00306ee0
        charge(ctx, 3);
        v0 = si(-1);
        if (s0 == v0) {
            // 0x00306ef4
            charge(ctx, 3);
            v0 = 0;
        } else {
            // 0x00306eec
            charge(ctx, 2);
            // 0x00306f0c
            charge(ctx, 2);
            if (s4 == 0) {
                // 0x00306f14
                charge(ctx, 5);
                k_assert(a0, a1, 0x306F20u, kDatCalcFile, 3371);
            }
            // 0x00306f28
            charge(ctx, 3);
            at = slti(s0, 19);
            if (at != 0) {
                // 0x00306f34
                charge(ctx, 2);
                if (i64(s0) < 0) {
                    goto L_00306f3c;
                }
                goto L_00306f50;
            }
        L_00306f3c:
            charge(ctx, 5);
            k_assert(a0, a1, 0x306F48u, kDatCalcFile, 3372);
        L_00306f50:
            charge(ctx, 4);
            lhu(v0, s4, dat_unit::kFlags);
            v0 = v0 & dat_unit::kFlagEnemy;
            if (v0 != 0) {
                // 0x00306f7c
                charge(ctx, 4);
                lhu(v0, s4, dat_unit::kBaseId);
                v0 = slti(v0, enemy_rec::kCount);
                if (v0 == 0) {
                    // 0x00306f8c
                    charge(ctx, 5);
                    k_assert(a0, a1, 0x306F98u, kDatCalcFile, 3383);
                }
                // 0x00306fa0
                charge(ctx, 18);
                lhu(v0, s4, dat_unit::kBaseId);
                v1 = sll(v0, 5);
                lw(v0, gp, gp_off(btl::kEnemyAffinityTablePtr));  // gBtlEnemyAffinityTbl
                v1 = addu(v0, v1);
                v0 = sll(s0, 1);
                v0 = addu(v1, v0);
                lhu(v1, v0, 0);
                v0 = v1 & 0xFF00;
                a0 = sll(v0, 16);
                v0 = lui(0xFFFF);
                v0 = v0 | 0xFF;
                v1 = v1 & v0;
                v0 = sll(v1, 2);
                v0 = addu(v0, v1);
                s3 = a0 | v0;
                v0 = s3 & 0xFFFF;
                if (v0 == 0) {
                    // 0x00306fe8
                    charge(ctx, 4);
                    v0 = btl::kAffWeak;
                    v0 = s3 & v0;
                    if (v0 == 0) {
                        // 0x00307024
                        charge(ctx, 4);
                        v0 = 0x27000000;
                        v0 = s3 & v0;
                        if (v0 == 0) {
                            // 0x00307040
                            charge(ctx, 4);
                            v0 = btl::kAffResist;
                            v0 = s3 & v0;
                            if (v0 != 0) {
                                // 0x00307050
                                charge(ctx, 1);
                                s3 = s3 | 0x32;
                            }
                        } else {
                            // 0x00307034
                            charge(ctx, 3);
                            s3 = s3 | 0x64;
                        }
                    } else {
                        // 0x00306ff8
                        charge(ctx, 5);
                        a0 = ai::kFlagTable3;  // datGetFlag(0x1319): weak is 150
                        jal(ctx, 0x306FFCu, gen::fn_datGetFlag_0016f190);
                        if (v0 != 0) {
                            // 0x00307018
                            charge(ctx, 3);
                            s3 = s3 | 0x96;
                        } else {
                            // 0x0030700c
                            charge(ctx, 3);
                            s3 = s3 | 0x7D;
                        }
                    }
                }
            } else {
                // 0x00306f60
                charge(ctx, 7);
                a1 = s3 & 0xFFFF;
                lhu(a0, s4, dat_unit::kId);
                jal(ctx, 0x306F68u, gen::fn_sub_173460_00173460);
                s3 = v0;
            }
            // 0x00307054
            charge(ctx, 3);
            v0 = 2;
            if (s0 != v0) {
                // 0x00307060
                charge(ctx, 3);
                v0 = 1;
                if (s0 == v0) {
                    goto L_0030707c;
                }
                // 0x0030706c
                charge(ctx, 2);
                if (s0 == 0) {
                    goto L_0030707c;
                }
                // 0x00307074
                charge(ctx, 2);
                goto L_0030711c;
            }
        L_0030707c:
            charge(ctx, 4);
            lhu(v0, s4, dat_unit::kFlags);
            v0 = v0 & dat_unit::kFlagEnemy;
            if (v0 == 0) {
                // 0x00307098
                charge(ctx, 4);
                lhu(a0, s4, dat_unit::kId);
                a1 = 82;
                jal(ctx, 0x3070A0u, gen::fn_sub_300750_00300750);
            } else {
                // 0x0030708c
                charge(ctx, 3);
                v0 = 0;
            }
            // 0x003070a8
            charge(ctx, 2);
            if (v0 == 0) {
                // 0x003070b0
                charge(ctx, 4);
                lhu(v0, s4, dat_unit::kFlags);
                v0 = v0 & dat_unit::kFlagEnemy;
                if (v0 == 0) {
                    // 0x003070cc
                    charge(ctx, 4);
                    lhu(a0, s4, dat_unit::kId);
                    a1 = 83;
                    jal(ctx, 0x3070D4u, gen::fn_sub_300750_00300750);
                } else {
                    // 0x003070c0
                    charge(ctx, 3);
                    v0 = 0;
                }
                // 0x003070dc
                charge(ctx, 2);
                if (v0 != 0) {
                    goto L_00307118;
                }
                // 0x003070e4
                charge(ctx, 4);
                lhu(v0, s4, dat_unit::kFlags);
                v0 = v0 & dat_unit::kFlagEnemy;
                if (v0 == 0) {
                    // 0x00307100
                    charge(ctx, 4);
                    lhu(a0, s4, dat_unit::kId);
                    a1 = 84;
                    jal(ctx, 0x307108u, gen::fn_sub_300750_00300750);
                } else {
                    // 0x003070f4
                    charge(ctx, 3);
                    v0 = 0;
                }
                // 0x00307110
                charge(ctx, 2);
                if (v0 != 0) {
                    goto L_00307118;
                }
                goto L_0030711c;
            }
        L_00307118:
            charge(ctx, 1);
            s1 = 1;
        L_0030711c:
            charge(ctx, 3);
            v0 = 6;
            if (s0 != v0) {
                // 0x00307128
                charge(ctx, 3);
                v0 = 5;
                if (s0 == v0) {
                    goto L_00307154;
                }
                // 0x00307134
                charge(ctx, 3);
                v0 = 4;
                if (s0 == v0) {
                    goto L_00307154;
                }
                // 0x00307140
                charge(ctx, 3);
                v0 = 3;
                if (s0 == v0) {
                    goto L_00307154;
                }
                // 0x0030714c
                charge(ctx, 2);
                goto L_003071f4;
            }
        L_00307154:
            charge(ctx, 4);
            lhu(v0, s4, dat_unit::kFlags);
            v0 = v0 & dat_unit::kFlagEnemy;
            if (v0 == 0) {
                // 0x00307170
                charge(ctx, 4);
                lhu(a0, s4, dat_unit::kId);
                a1 = 97;
                jal(ctx, 0x307178u, gen::fn_sub_300750_00300750);
            } else {
                // 0x00307164
                charge(ctx, 3);
                v0 = 0;
            }
            // 0x00307180
            charge(ctx, 2);
            if (v0 == 0) {
                // 0x00307188
                charge(ctx, 4);
                lhu(v0, s4, dat_unit::kFlags);
                v0 = v0 & dat_unit::kFlagEnemy;
                if (v0 == 0) {
                    // 0x003071a4
                    charge(ctx, 4);
                    lhu(a0, s4, dat_unit::kId);
                    a1 = 98;
                    jal(ctx, 0x3071ACu, gen::fn_sub_300750_00300750);
                } else {
                    // 0x00307198
                    charge(ctx, 3);
                    v0 = 0;
                }
                // 0x003071b4
                charge(ctx, 2);
                if (v0 != 0) {
                    goto L_003071f0;
                }
                // 0x003071bc
                charge(ctx, 4);
                lhu(v0, s4, dat_unit::kFlags);
                v0 = v0 & dat_unit::kFlagEnemy;
                if (v0 == 0) {
                    // 0x003071d8
                    charge(ctx, 4);
                    lhu(a0, s4, dat_unit::kId);
                    a1 = 99;
                    jal(ctx, 0x3071E0u, gen::fn_sub_300750_00300750);
                } else {
                    // 0x003071cc
                    charge(ctx, 3);
                    v0 = 0;
                }
                // 0x003071e8
                charge(ctx, 2);
                if (v0 != 0) {
                    goto L_003071f0;
                }
                goto L_003071f4;
            }
        L_003071f0:
            charge(ctx, 1);
            s1 = 1;
        L_003071f4:
            charge(ctx, 3);
            at = sltiu(s0, 16);
            if (at != 0) {
                // 0x00307200
                charge(ctx, 7);
                v1 = hi(0x7B8F90u);
                v1 = addiu(v1, lo(0x7B8F90u));  // &0x7B8F90
                v0 = sll(s0, 2);
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                switch (v0.u()) {
                case 0x30721Cu:  // table[0]
                    // 0x0030721c
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 464;
                    jal(ctx, 0x307224u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00307234
                        charge(ctx, 2);
                        v0 = btl::kAffResist;
                        s2 = s2 | v0;
                    }
                    // 0x0030723c
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 465;
                    jal(ctx, 0x307244u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00307254
                        charge(ctx, 2);
                        v0 = btl::kAffNull;
                        s2 = s2 | v0;
                    }
                    // 0x0030725c
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 466;
                    jal(ctx, 0x307264u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00307274
                        charge(ctx, 2);
                        v0 = btl::kAffRepel;
                        s2 = s2 | v0;
                    }
                    // 0x0030727c
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 467;
                    jal(ctx, 0x307284u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00307294
                        charge(ctx, 2);
                        v0 = btl::kAffAbsorb;
                        s2 = s2 | v0;
                    }
                    // 0x0030729c
                    charge(ctx, 4);
                    lhu(v0, s4, dat_unit::kFlags);
                    v0 = v0 & dat_unit::kFlagEnemy;
                    if (v0 == 0) {
                        // 0x003072b8
                        charge(ctx, 4);
                        lhu(a0, s4, dat_unit::kId);
                        a1 = 76;
                        jal(ctx, 0x3072C0u, gen::fn_sub_300750_00300750);
                    } else {
                        // 0x003072ac
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x003072c8
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x003072d0
                        charge(ctx, 4);
                        lhu(v0, s4, dat_unit::kFlags);
                        v0 = v0 & dat_unit::kFlagEnemy;
                        if (v0 == 0) {
                            // 0x003072ec
                            charge(ctx, 4);
                            lhu(a0, s4, dat_unit::kId);
                            a1 = 77;
                            jal(ctx, 0x3072F4u, gen::fn_sub_300750_00300750);
                        } else {
                            // 0x003072e0
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x003072fc
                        charge(ctx, 2);
                        if (v0 != 0) {
                            goto L_00307338;
                        }
                        // 0x00307304
                        charge(ctx, 4);
                        lhu(v0, s4, dat_unit::kFlags);
                        v0 = v0 & dat_unit::kFlagEnemy;
                        if (v0 == 0) {
                            // 0x00307320
                            charge(ctx, 4);
                            lhu(a0, s4, dat_unit::kId);
                            a1 = 78;
                            jal(ctx, 0x307328u, gen::fn_sub_300750_00300750);
                        } else {
                            // 0x00307314
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x00307330
                        charge(ctx, 2);
                        if (v0 != 0) {
                            goto L_00307338;
                        }
                        break;
                    }
                L_00307338:
                    charge(ctx, 3);
                    s1 = 1;
                    break;
                case 0x307344u:  // table[1]
                    // 0x00307344
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 468;
                    jal(ctx, 0x30734Cu, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x0030735c
                        charge(ctx, 2);
                        v0 = btl::kAffResist;
                        s2 = s2 | v0;
                    }
                    // 0x00307364
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 469;
                    jal(ctx, 0x30736Cu, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x0030737c
                        charge(ctx, 2);
                        v0 = btl::kAffNull;
                        s2 = s2 | v0;
                    }
                    // 0x00307384
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 470;
                    jal(ctx, 0x30738Cu, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x0030739c
                        charge(ctx, 2);
                        v0 = btl::kAffRepel;
                        s2 = s2 | v0;
                    }
                    // 0x003073a4
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 471;
                    jal(ctx, 0x3073ACu, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x003073bc
                        charge(ctx, 2);
                        v0 = btl::kAffAbsorb;
                        s2 = s2 | v0;
                    }
                    // 0x003073c4
                    charge(ctx, 4);
                    lhu(v0, s4, dat_unit::kFlags);
                    v0 = v0 & dat_unit::kFlagEnemy;
                    if (v0 == 0) {
                        // 0x003073e0
                        charge(ctx, 4);
                        lhu(a0, s4, dat_unit::kId);
                        a1 = 73;
                        jal(ctx, 0x3073E8u, gen::fn_sub_300750_00300750);
                    } else {
                        // 0x003073d4
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x003073f0
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x003073f8
                        charge(ctx, 4);
                        lhu(v0, s4, dat_unit::kFlags);
                        v0 = v0 & dat_unit::kFlagEnemy;
                        if (v0 == 0) {
                            // 0x00307414
                            charge(ctx, 4);
                            lhu(a0, s4, dat_unit::kId);
                            a1 = 74;
                            jal(ctx, 0x30741Cu, gen::fn_sub_300750_00300750);
                        } else {
                            // 0x00307408
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x00307424
                        charge(ctx, 2);
                        if (v0 != 0) {
                            goto L_00307460;
                        }
                        // 0x0030742c
                        charge(ctx, 4);
                        lhu(v0, s4, dat_unit::kFlags);
                        v0 = v0 & dat_unit::kFlagEnemy;
                        if (v0 == 0) {
                            // 0x00307448
                            charge(ctx, 4);
                            lhu(a0, s4, dat_unit::kId);
                            a1 = 75;
                            jal(ctx, 0x307450u, gen::fn_sub_300750_00300750);
                        } else {
                            // 0x0030743c
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x00307458
                        charge(ctx, 2);
                        if (v0 != 0) {
                            goto L_00307460;
                        }
                        break;
                    }
                L_00307460:
                    charge(ctx, 3);
                    s1 = 1;
                    break;
                case 0x30746Cu:  // table[2]
                    // 0x0030746c
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 472;
                    jal(ctx, 0x307474u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00307484
                        charge(ctx, 2);
                        v0 = btl::kAffResist;
                        s2 = s2 | v0;
                    }
                    // 0x0030748c
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 473;
                    jal(ctx, 0x307494u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x003074a4
                        charge(ctx, 2);
                        v0 = btl::kAffNull;
                        s2 = s2 | v0;
                    }
                    // 0x003074ac
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 474;
                    jal(ctx, 0x3074B4u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x003074c4
                        charge(ctx, 2);
                        v0 = btl::kAffRepel;
                        s2 = s2 | v0;
                    }
                    // 0x003074cc
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 475;
                    jal(ctx, 0x3074D4u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x003074e4
                        charge(ctx, 2);
                        v0 = btl::kAffAbsorb;
                        s2 = s2 | v0;
                    }
                    // 0x003074ec
                    charge(ctx, 4);
                    lhu(v0, s4, dat_unit::kFlags);
                    v0 = v0 & dat_unit::kFlagEnemy;
                    if (v0 == 0) {
                        // 0x00307508
                        charge(ctx, 4);
                        lhu(a0, s4, dat_unit::kId);
                        a1 = 79;
                        jal(ctx, 0x307510u, gen::fn_sub_300750_00300750);
                    } else {
                        // 0x003074fc
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x00307518
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x00307520
                        charge(ctx, 4);
                        lhu(v0, s4, dat_unit::kFlags);
                        v0 = v0 & dat_unit::kFlagEnemy;
                        if (v0 == 0) {
                            // 0x0030753c
                            charge(ctx, 4);
                            lhu(a0, s4, dat_unit::kId);
                            a1 = 80;
                            jal(ctx, 0x307544u, gen::fn_sub_300750_00300750);
                        } else {
                            // 0x00307530
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x0030754c
                        charge(ctx, 2);
                        if (v0 != 0) {
                            goto L_00307588;
                        }
                        // 0x00307554
                        charge(ctx, 4);
                        lhu(v0, s4, dat_unit::kFlags);
                        v0 = v0 & dat_unit::kFlagEnemy;
                        if (v0 == 0) {
                            // 0x00307570
                            charge(ctx, 4);
                            lhu(a0, s4, dat_unit::kId);
                            a1 = 81;
                            jal(ctx, 0x307578u, gen::fn_sub_300750_00300750);
                        } else {
                            // 0x00307564
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x00307580
                        charge(ctx, 2);
                        if (v0 != 0) {
                            goto L_00307588;
                        }
                        break;
                    }
                L_00307588:
                    charge(ctx, 3);
                    s1 = 1;
                    break;
                case 0x307594u:  // table[3]
                    // 0x00307594
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 476;
                    jal(ctx, 0x30759Cu, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x003075ac
                        charge(ctx, 2);
                        v0 = btl::kAffResist;
                        s2 = s2 | v0;
                    }
                    // 0x003075b4
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 477;
                    jal(ctx, 0x3075BCu, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x003075cc
                        charge(ctx, 2);
                        v0 = btl::kAffNull;
                        s2 = s2 | v0;
                    }
                    // 0x003075d4
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 478;
                    jal(ctx, 0x3075DCu, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x003075ec
                        charge(ctx, 2);
                        v0 = btl::kAffRepel;
                        s2 = s2 | v0;
                    }
                    // 0x003075f4
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 479;
                    jal(ctx, 0x3075FCu, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x0030760c
                        charge(ctx, 2);
                        v0 = btl::kAffAbsorb;
                        s2 = s2 | v0;
                    }
                    // 0x00307614
                    charge(ctx, 8);
                    a0 = s4;
                    a1 = 13;
                    jal(ctx, 0x30761Cu, gen::fn_datCalcGetEffectLevel_00300f60);
                    v0 = dsll32(v0, 24);
                    v0 = dsra32(v0, 24);
                    if (i64(v0) > 0) {
                        // 0x00307634
                        charge(ctx, 1);
                        s5 = 1;
                    }
                    // 0x00307638
                    charge(ctx, 4);
                    lhu(v0, s4, dat_unit::kFlags);
                    v0 = v0 & dat_unit::kFlagEnemy;
                    if (v0 == 0) {
                        // 0x00307654
                        charge(ctx, 4);
                        lhu(a0, s4, dat_unit::kId);
                        a1 = 85;
                        jal(ctx, 0x30765Cu, gen::fn_sub_300750_00300750);
                    } else {
                        // 0x00307648
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x00307664
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x0030766c
                        charge(ctx, 4);
                        lhu(v0, s4, dat_unit::kFlags);
                        v0 = v0 & dat_unit::kFlagEnemy;
                        if (v0 == 0) {
                            // 0x00307688
                            charge(ctx, 4);
                            lhu(a0, s4, dat_unit::kId);
                            a1 = 86;
                            jal(ctx, 0x307690u, gen::fn_sub_300750_00300750);
                        } else {
                            // 0x0030767c
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x00307698
                        charge(ctx, 2);
                        if (v0 != 0) {
                            goto L_003076d4;
                        }
                        // 0x003076a0
                        charge(ctx, 4);
                        lhu(v0, s4, dat_unit::kFlags);
                        v0 = v0 & dat_unit::kFlagEnemy;
                        if (v0 == 0) {
                            // 0x003076bc
                            charge(ctx, 4);
                            lhu(a0, s4, dat_unit::kId);
                            a1 = 87;
                            jal(ctx, 0x3076C4u, gen::fn_sub_300750_00300750);
                        } else {
                            // 0x003076b0
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x003076cc
                        charge(ctx, 2);
                        if (v0 != 0) {
                            goto L_003076d4;
                        }
                        break;
                    }
                L_003076d4:
                    charge(ctx, 3);
                    s1 = 1;
                    break;
                case 0x3076E0u:  // table[4]
                    // 0x003076e0
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 480;
                    jal(ctx, 0x3076E8u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x003076f8
                        charge(ctx, 2);
                        v0 = btl::kAffResist;
                        s2 = s2 | v0;
                    }
                    // 0x00307700
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 481;
                    jal(ctx, 0x307708u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00307718
                        charge(ctx, 2);
                        v0 = btl::kAffNull;
                        s2 = s2 | v0;
                    }
                    // 0x00307720
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 482;
                    jal(ctx, 0x307728u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00307738
                        charge(ctx, 2);
                        v0 = btl::kAffRepel;
                        s2 = s2 | v0;
                    }
                    // 0x00307740
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 483;
                    jal(ctx, 0x307748u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00307758
                        charge(ctx, 2);
                        v0 = btl::kAffAbsorb;
                        s2 = s2 | v0;
                    }
                    // 0x00307760
                    charge(ctx, 8);
                    a0 = s4;
                    a1 = 14;
                    jal(ctx, 0x307768u, gen::fn_datCalcGetEffectLevel_00300f60);
                    v0 = dsll32(v0, 24);
                    v0 = dsra32(v0, 24);
                    if (i64(v0) > 0) {
                        // 0x00307780
                        charge(ctx, 1);
                        s5 = 1;
                    }
                    // 0x00307784
                    charge(ctx, 4);
                    lhu(v0, s4, dat_unit::kFlags);
                    v0 = v0 & dat_unit::kFlagEnemy;
                    if (v0 == 0) {
                        // 0x003077a0
                        charge(ctx, 4);
                        lhu(a0, s4, dat_unit::kId);
                        a1 = 88;
                        jal(ctx, 0x3077A8u, gen::fn_sub_300750_00300750);
                    } else {
                        // 0x00307794
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x003077b0
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x003077b8
                        charge(ctx, 4);
                        lhu(v0, s4, dat_unit::kFlags);
                        v0 = v0 & dat_unit::kFlagEnemy;
                        if (v0 == 0) {
                            // 0x003077d4
                            charge(ctx, 4);
                            lhu(a0, s4, dat_unit::kId);
                            a1 = 89;
                            jal(ctx, 0x3077DCu, gen::fn_sub_300750_00300750);
                        } else {
                            // 0x003077c8
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x003077e4
                        charge(ctx, 2);
                        if (v0 != 0) {
                            goto L_00307820;
                        }
                        // 0x003077ec
                        charge(ctx, 4);
                        lhu(v0, s4, dat_unit::kFlags);
                        v0 = v0 & dat_unit::kFlagEnemy;
                        if (v0 == 0) {
                            // 0x00307808
                            charge(ctx, 4);
                            lhu(a0, s4, dat_unit::kId);
                            a1 = 90;
                            jal(ctx, 0x307810u, gen::fn_sub_300750_00300750);
                        } else {
                            // 0x003077fc
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x00307818
                        charge(ctx, 2);
                        if (v0 != 0) {
                            goto L_00307820;
                        }
                        break;
                    }
                L_00307820:
                    charge(ctx, 3);
                    s1 = 1;
                    break;
                case 0x30782Cu:  // table[5]
                    // 0x0030782c
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 484;
                    jal(ctx, 0x307834u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00307844
                        charge(ctx, 2);
                        v0 = btl::kAffResist;
                        s2 = s2 | v0;
                    }
                    // 0x0030784c
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 485;
                    jal(ctx, 0x307854u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00307864
                        charge(ctx, 2);
                        v0 = btl::kAffNull;
                        s2 = s2 | v0;
                    }
                    // 0x0030786c
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 486;
                    jal(ctx, 0x307874u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00307884
                        charge(ctx, 2);
                        v0 = btl::kAffRepel;
                        s2 = s2 | v0;
                    }
                    // 0x0030788c
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 487;
                    jal(ctx, 0x307894u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x003078a4
                        charge(ctx, 2);
                        v0 = btl::kAffAbsorb;
                        s2 = s2 | v0;
                    }
                    // 0x003078ac
                    charge(ctx, 8);
                    a0 = s4;
                    a1 = 16;
                    jal(ctx, 0x3078B4u, gen::fn_datCalcGetEffectLevel_00300f60);
                    v0 = dsll32(v0, 24);
                    v0 = dsra32(v0, 24);
                    if (i64(v0) > 0) {
                        // 0x003078cc
                        charge(ctx, 1);
                        s5 = 1;
                    }
                    // 0x003078d0
                    charge(ctx, 4);
                    lhu(v0, s4, dat_unit::kFlags);
                    v0 = v0 & dat_unit::kFlagEnemy;
                    if (v0 == 0) {
                        // 0x003078ec
                        charge(ctx, 4);
                        lhu(a0, s4, dat_unit::kId);
                        a1 = 94;
                        jal(ctx, 0x3078F4u, gen::fn_sub_300750_00300750);
                    } else {
                        // 0x003078e0
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x003078fc
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x00307904
                        charge(ctx, 4);
                        lhu(v0, s4, dat_unit::kFlags);
                        v0 = v0 & dat_unit::kFlagEnemy;
                        if (v0 == 0) {
                            // 0x00307920
                            charge(ctx, 4);
                            lhu(a0, s4, dat_unit::kId);
                            a1 = 95;
                            jal(ctx, 0x307928u, gen::fn_sub_300750_00300750);
                        } else {
                            // 0x00307914
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x00307930
                        charge(ctx, 2);
                        if (v0 != 0) {
                            goto L_0030796c;
                        }
                        // 0x00307938
                        charge(ctx, 4);
                        lhu(v0, s4, dat_unit::kFlags);
                        v0 = v0 & dat_unit::kFlagEnemy;
                        if (v0 == 0) {
                            // 0x00307954
                            charge(ctx, 4);
                            lhu(a0, s4, dat_unit::kId);
                            a1 = 96;
                            jal(ctx, 0x30795Cu, gen::fn_sub_300750_00300750);
                        } else {
                            // 0x00307948
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x00307964
                        charge(ctx, 2);
                        if (v0 != 0) {
                            goto L_0030796c;
                        }
                        break;
                    }
                L_0030796c:
                    charge(ctx, 3);
                    s1 = 1;
                    break;
                case 0x307978u:  // table[6]
                    // 0x00307978
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 488;
                    jal(ctx, 0x307980u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00307990
                        charge(ctx, 2);
                        v0 = btl::kAffResist;
                        s2 = s2 | v0;
                    }
                    // 0x00307998
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 489;
                    jal(ctx, 0x3079A0u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x003079b0
                        charge(ctx, 2);
                        v0 = btl::kAffNull;
                        s2 = s2 | v0;
                    }
                    // 0x003079b8
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 490;
                    jal(ctx, 0x3079C0u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x003079d0
                        charge(ctx, 2);
                        v0 = btl::kAffRepel;
                        s2 = s2 | v0;
                    }
                    // 0x003079d8
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 491;
                    jal(ctx, 0x3079E0u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x003079f0
                        charge(ctx, 2);
                        v0 = btl::kAffAbsorb;
                        s2 = s2 | v0;
                    }
                    // 0x003079f8
                    charge(ctx, 8);
                    a0 = s4;
                    a1 = 15;
                    jal(ctx, 0x307A00u, gen::fn_datCalcGetEffectLevel_00300f60);
                    v0 = dsll32(v0, 24);
                    v0 = dsra32(v0, 24);
                    if (i64(v0) > 0) {
                        // 0x00307a18
                        charge(ctx, 1);
                        s5 = 1;
                    }
                    // 0x00307a1c
                    charge(ctx, 4);
                    lhu(v0, s4, dat_unit::kFlags);
                    v0 = v0 & dat_unit::kFlagEnemy;
                    if (v0 == 0) {
                        // 0x00307a38
                        charge(ctx, 4);
                        lhu(a0, s4, dat_unit::kId);
                        a1 = 91;
                        jal(ctx, 0x307A40u, gen::fn_sub_300750_00300750);
                    } else {
                        // 0x00307a2c
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x00307a48
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x00307a50
                        charge(ctx, 4);
                        lhu(v0, s4, dat_unit::kFlags);
                        v0 = v0 & dat_unit::kFlagEnemy;
                        if (v0 == 0) {
                            // 0x00307a6c
                            charge(ctx, 4);
                            lhu(a0, s4, dat_unit::kId);
                            a1 = 92;
                            jal(ctx, 0x307A74u, gen::fn_sub_300750_00300750);
                        } else {
                            // 0x00307a60
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x00307a7c
                        charge(ctx, 2);
                        if (v0 != 0) {
                            goto L_00307ab8;
                        }
                        // 0x00307a84
                        charge(ctx, 4);
                        lhu(v0, s4, dat_unit::kFlags);
                        v0 = v0 & dat_unit::kFlagEnemy;
                        if (v0 == 0) {
                            // 0x00307aa0
                            charge(ctx, 4);
                            lhu(a0, s4, dat_unit::kId);
                            a1 = 93;
                            jal(ctx, 0x307AA8u, gen::fn_sub_300750_00300750);
                        } else {
                            // 0x00307a94
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x00307ab0
                        charge(ctx, 2);
                        if (v0 != 0) {
                            goto L_00307ab8;
                        }
                        break;
                    }
                L_00307ab8:
                    charge(ctx, 3);
                    s1 = 1;
                    break;
                case 0x307AC4u:  // table[8]
                    // 0x00307ac4
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 492;
                    jal(ctx, 0x307ACCu, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00307adc
                        charge(ctx, 2);
                        v0 = btl::kAffResist;
                        s2 = s2 | v0;
                    }
                    // 0x00307ae4
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 493;
                    jal(ctx, 0x307AECu, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00307afc
                        charge(ctx, 2);
                        v0 = btl::kAffNull;
                        s2 = s2 | v0;
                    }
                    // 0x00307b04
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 494;
                    jal(ctx, 0x307B0Cu, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00307b1c
                        charge(ctx, 4);
                        v0 = btl::kAffRepel;
                        s2 = s2 | v0;
                    }
                    break;
                case 0x307B2Cu:  // table[9]
                    // 0x00307b2c
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 495;
                    jal(ctx, 0x307B34u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00307b44
                        charge(ctx, 2);
                        v0 = btl::kAffResist;
                        s2 = s2 | v0;
                    }
                    // 0x00307b4c
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 496;
                    jal(ctx, 0x307B54u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00307b64
                        charge(ctx, 2);
                        v0 = btl::kAffNull;
                        s2 = s2 | v0;
                    }
                    // 0x00307b6c
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 497;
                    jal(ctx, 0x307B74u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00307b84
                        charge(ctx, 4);
                        v0 = btl::kAffRepel;
                        s2 = s2 | v0;
                    }
                    break;
                case 0x307B94u:  // table[10]
                    // 0x00307b94
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 612;
                    jal(ctx, 0x307B9Cu, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 == 0) {
                        // 0x00307bac
                        charge(ctx, 4);
                        lhu(v0, s4, dat_unit::kFlags);
                        v0 = v0 & dat_unit::kFlagEnemy;
                        if (v0 == 0) {
                            // 0x00307bc8
                            charge(ctx, 4);
                            lhu(a0, s4, dat_unit::kId);
                            a1 = 183;
                            jal(ctx, 0x307BD0u, gen::fn_sub_300870_00300870);
                        } else {
                            // 0x00307bbc
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x00307bd8
                        charge(ctx, 3);
                        v0 = v0 & 0xFFFF;
                        if (v0 != 0) {
                            goto L_00307be4;
                        }
                        goto L_00307bec;
                    }
                L_00307be4:
                    charge(ctx, 2);
                    v0 = btl::kAffResist;
                    s2 = s2 | v0;
                L_00307bec:
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 498;
                    jal(ctx, 0x307BF4u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00307c04
                        charge(ctx, 2);
                        v0 = btl::kAffNull;
                        s2 = s2 | v0;
                    }
                    // 0x00307c0c
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 506;
                    jal(ctx, 0x307C14u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00307c24
                        charge(ctx, 4);
                        v0 = btl::kAffNull;
                        s2 = s2 | v0;
                    }
                    break;
                case 0x307C34u:  // table[11]
                    // 0x00307c34
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 619;
                    jal(ctx, 0x307C3Cu, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 == 0) {
                        // 0x00307c4c
                        charge(ctx, 4);
                        lhu(v0, s4, dat_unit::kFlags);
                        v0 = v0 & dat_unit::kFlagEnemy;
                        if (v0 == 0) {
                            // 0x00307c68
                            charge(ctx, 4);
                            lhu(a0, s4, dat_unit::kId);
                            a1 = 188;
                            jal(ctx, 0x307C70u, gen::fn_sub_300870_00300870);
                        } else {
                            // 0x00307c5c
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x00307c78
                        charge(ctx, 3);
                        v0 = v0 & 0xFFFF;
                        if (v0 != 0) {
                            goto L_00307c84;
                        }
                        goto L_00307c8c;
                    }
                L_00307c84:
                    charge(ctx, 2);
                    v0 = btl::kAffResist;
                    s2 = s2 | v0;
                L_00307c8c:
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 505;
                    jal(ctx, 0x307C94u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00307ca4
                        charge(ctx, 4);
                        v0 = btl::kAffNull;
                        s2 = s2 | v0;
                    }
                    break;
                case 0x307CB4u:  // table[12]
                    // 0x00307cb4
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 613;
                    jal(ctx, 0x307CBCu, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 == 0) {
                        // 0x00307ccc
                        charge(ctx, 4);
                        lhu(v0, s4, dat_unit::kFlags);
                        v0 = v0 & dat_unit::kFlagEnemy;
                        if (v0 == 0) {
                            // 0x00307ce8
                            charge(ctx, 4);
                            lhu(a0, s4, dat_unit::kId);
                            a1 = 184;
                            jal(ctx, 0x307CF0u, gen::fn_sub_300870_00300870);
                        } else {
                            // 0x00307cdc
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x00307cf8
                        charge(ctx, 3);
                        v0 = v0 & 0xFFFF;
                        if (v0 != 0) {
                            goto L_00307d04;
                        }
                        goto L_00307d0c;
                    }
                L_00307d04:
                    charge(ctx, 2);
                    v0 = btl::kAffResist;
                    s2 = s2 | v0;
                L_00307d0c:
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 499;
                    jal(ctx, 0x307D14u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00307d24
                        charge(ctx, 2);
                        v0 = btl::kAffNull;
                        s2 = s2 | v0;
                    }
                    // 0x00307d2c
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 506;
                    jal(ctx, 0x307D34u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00307d44
                        charge(ctx, 4);
                        v0 = btl::kAffNull;
                        s2 = s2 | v0;
                    }
                    break;
                case 0x307D54u:  // table[13]
                    // 0x00307d54
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 614;
                    jal(ctx, 0x307D5Cu, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 == 0) {
                        // 0x00307d6c
                        charge(ctx, 4);
                        lhu(v0, s4, dat_unit::kFlags);
                        v0 = v0 & dat_unit::kFlagEnemy;
                        if (v0 == 0) {
                            // 0x00307d88
                            charge(ctx, 4);
                            lhu(a0, s4, dat_unit::kId);
                            a1 = 185;
                            jal(ctx, 0x307D90u, gen::fn_sub_300870_00300870);
                        } else {
                            // 0x00307d7c
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x00307d98
                        charge(ctx, 3);
                        v0 = v0 & 0xFFFF;
                        if (v0 != 0) {
                            goto L_00307da4;
                        }
                        goto L_00307dac;
                    }
                L_00307da4:
                    charge(ctx, 2);
                    v0 = btl::kAffResist;
                    s2 = s2 | v0;
                L_00307dac:
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 500;
                    jal(ctx, 0x307DB4u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00307dc4
                        charge(ctx, 2);
                        v0 = btl::kAffNull;
                        s2 = s2 | v0;
                    }
                    // 0x00307dcc
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 506;
                    jal(ctx, 0x307DD4u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00307de4
                        charge(ctx, 4);
                        v0 = btl::kAffNull;
                        s2 = s2 | v0;
                    }
                    break;
                case 0x307DF4u:  // table[14]
                    // 0x00307df4
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 615;
                    jal(ctx, 0x307DFCu, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 == 0) {
                        // 0x00307e0c
                        charge(ctx, 4);
                        lhu(v0, s4, dat_unit::kFlags);
                        v0 = v0 & dat_unit::kFlagEnemy;
                        if (v0 == 0) {
                            // 0x00307e28
                            charge(ctx, 4);
                            lhu(a0, s4, dat_unit::kId);
                            a1 = 186;
                            jal(ctx, 0x307E30u, gen::fn_sub_300870_00300870);
                        } else {
                            // 0x00307e1c
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x00307e38
                        charge(ctx, 3);
                        v0 = v0 & 0xFFFF;
                        if (v0 != 0) {
                            goto L_00307e44;
                        }
                        goto L_00307e4c;
                    }
                L_00307e44:
                    charge(ctx, 2);
                    v0 = btl::kAffResist;
                    s2 = s2 | v0;
                L_00307e4c:
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 501;
                    jal(ctx, 0x307E54u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00307e64
                        charge(ctx, 2);
                        v0 = btl::kAffNull;
                        s2 = s2 | v0;
                    }
                    // 0x00307e6c
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 506;
                    jal(ctx, 0x307E74u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00307e84
                        charge(ctx, 4);
                        v0 = btl::kAffNull;
                        s2 = s2 | v0;
                    }
                    break;
                case 0x307E94u:  // table[15]
                    // 0x00307e94
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 616;
                    jal(ctx, 0x307E9Cu, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 == 0) {
                        // 0x00307eac
                        charge(ctx, 4);
                        lhu(v0, s4, dat_unit::kFlags);
                        v0 = v0 & dat_unit::kFlagEnemy;
                        if (v0 == 0) {
                            // 0x00307ec8
                            charge(ctx, 4);
                            lhu(a0, s4, dat_unit::kId);
                            a1 = 187;
                            jal(ctx, 0x307ED0u, gen::fn_sub_300870_00300870);
                        } else {
                            // 0x00307ebc
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x00307ed8
                        charge(ctx, 3);
                        v0 = v0 & 0xFFFF;
                        if (v0 != 0) {
                            goto L_00307ee4;
                        }
                        goto L_00307eec;
                    }
                L_00307ee4:
                    charge(ctx, 2);
                    v0 = btl::kAffResist;
                    s2 = s2 | v0;
                L_00307eec:
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 502;
                    jal(ctx, 0x307EF4u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00307f04
                        charge(ctx, 2);
                        v0 = btl::kAffNull;
                        s2 = s2 | v0;
                    }
                    // 0x00307f0c
                    charge(ctx, 6);
                    a0 = s4;
                    a1 = 506;
                    jal(ctx, 0x307F14u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00307f24
                        charge(ctx, 2);
                        v0 = btl::kAffNull;
                        s2 = s2 | v0;
                    }
                    break;
                case 0x307F2Cu:  // table[7]
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v0.u());
                    return;
                }
            }
            // 0x00307f2c
            charge(ctx, 3);
            v0 = 7;
            if (s0 != v0) {
                // 0x00307f38
                charge(ctx, 6);
                a0 = s4;
                a1 = 507;
                jal(ctx, 0x307F40u, gen::fn_datCalcHasSkill_003005e0);
                if (v0 != 0) {
                    // 0x00307f50
                    charge(ctx, 2);
                    v0 = btl::kAffNull;
                    s2 = s2 | v0;
                }
            }
            // 0x00307f58
            charge(ctx, 3);
            v0 = 1;
            if (s1 == v0) {
                // 0x00307f64
                charge(ctx, 4);
                v0 = btl::kAffWeak;
                v0 = s3 & v0;
                if (v0 != 0) {
                    // 0x00307f74
                    charge(ctx, 3);
                    v0 = lui(0xF7FF);
                    v0 = s3 & v0;
                    s3 = v0 | 0x64;
                }
            }
            // 0x00307f80
            charge(ctx, 2);
            if (s2 != 0) {
                // 0x00307f88
                charge(ctx, 4);
                v1 = btl::kAffResist;
                v0 = s2 & v1;
                if (v0 != 0) {
                    // 0x00307f98
                    charge(ctx, 4);
                    v0 = 0x7000000;
                    v0 = s3 & v0;
                    if (v0 == 0) {
                        // 0x00307fa8
                        charge(ctx, 7);
                        v0 = lui(0xF7FF);
                        v0 = v0 | 0xFFFF;
                        v0 = s3 & v0;
                        v1 = v0 | v1;
                        v0 = lui(0xFFFF);
                        v0 = v1 & v0;
                        s3 = v0 | 0x32;
                    }
                }
                // 0x00307fc4
                charge(ctx, 4);
                v1 = btl::kAffNull;
                v0 = s2 & v1;
                if (v0 != 0) {
                    // 0x00307fd4
                    charge(ctx, 4);
                    v0 = 0x6000000;
                    v0 = s3 & v0;
                    if (v0 == 0) {
                        // 0x00307fe4
                        charge(ctx, 7);
                        v0 = lui(0xE7FF);
                        v0 = v0 | 0xFFFF;
                        v0 = s3 & v0;
                        v1 = v0 | v1;
                        v0 = lui(0xFFFF);
                        v0 = v1 & v0;
                        s3 = v0 | 0x64;
                    }
                }
                // 0x00308000
                charge(ctx, 4);
                v1 = btl::kAffRepel;
                v0 = s2 & v1;
                if (v0 != 0) {
                    // 0x00308010
                    charge(ctx, 4);
                    v0 = btl::kAffAbsorb;
                    v0 = s3 & v0;
                    if (v0 == 0) {
                        // 0x00308020
                        charge(ctx, 7);
                        v0 = lui(0xE6FF);
                        v0 = v0 | 0xFFFF;
                        v0 = s3 & v0;
                        v1 = v0 | v1;
                        v0 = lui(0xFFFF);
                        v0 = v1 & v0;
                        s3 = v0 | 0x64;
                    }
                }
                // 0x0030803c
                charge(ctx, 4);
                v1 = btl::kAffAbsorb;
                v0 = s2 & v1;
                if (v0 != 0) {
                    // 0x0030804c
                    charge(ctx, 7);
                    v0 = lui(0xE4FF);
                    v0 = v0 | 0xFFFF;
                    v0 = s3 & v0;
                    v1 = v0 | v1;
                    v0 = lui(0xFFFF);
                    v0 = v1 & v0;
                    s3 = v0 | 0x64;
                }
            }
            // 0x00308068
            charge(ctx, 2);
            if (s5 != 0) {
                // 0x00308070
                charge(ctx, 4);
                v0 = 0x17000000;
                v0 = s3 & v0;
                if (v0 != 0) {
                    // 0x00308080
                    charge(ctx, 3);
                    v0 = lui(0xE8FF);
                    v0 = s3 & v0;
                    s3 = v0 | 0x64;
                }
            }
            // 0x0030808c
            charge(ctx, 1);
            v0 = s3;
        }
        // 0x00308090: epilogue
        charge(ctx, 10);
        ld(ra, sp, 0x60);
        lq(s5, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x70);
        return;
    }
L_00306f00:
    charge(ctx, 3);
    v0 = 100;
    // 0x00308090: epilogue
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// ================================================================================================================
// 0x309490 datCalcCheckHit(attacker, target, skill, flags)
// ================================================================================================================

namespace {

namespace fpu = ee::fpu;

}  // namespace

// 0x00309490 datCalcCheckHit -- 4784 bytes; frame 0xC0: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// The hit check of one action (21_battle.md section 5.2): 1 hit, 4 miss, 256 nullified, 512 repelled / evaded,
// 1024 drained. In order: an instant-death skill (SkillRecord +36 == 1) hits iff the target has status bit 3;
// for every element row but none and 16..18 the target's dodge flags (+0x14 bit 17 physical / bit 18 magic, which
// also set the matching bit of +0x18), its evade skills 546/545/544 (or accessories 179/178/177) for physical rows
// unless `flags` bit 1, buff slots 11 / 8 / 9 and the repel / absorb / null affinity flags; then the accuracy
// (SkillRecord +14: 0 misses, >= 100 hits; target status 0x100000, flag 0x80 or exactly one of 512/2/64/32 hits)
// and the rate formula. K_Assert lines 4469 (skill >= 464) and 3752 (row >= 19) are no-ops.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void datCalcCheckHit(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::c_eq_s, hg::charge, hg::cond, hg::cvt_s_w, hg::cvt_w_s,
          hg::dsll32, hg::dsra32, hg::dsrl32, hg::enter, hg::i64, hg::jal, hg::lb, hg::lbu, hg::ld, hg::lh, hg::lhu,
          hg::lq, hg::lw, hg::lwc1, hg::mfc1, hg::mov_s, hg::mtc1, hg::mul_s, hg::sd, hg::sh, hg::sll, hg::sllv,
          hg::slt, hg::slti, hg::sltiu, hg::sltu, hg::sq, hg::subu, hg::sw, hg::swc1, hg::tail;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    // 0x00309490: prologue
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0xA0);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s5 = a2;
    sw(a3, sp, 0xBC);
    s0 = s5 & 0xFFFF;
    v0 = slti(s0, btl::kSkillCount);
    if (v0 == 0) {
        // 0x003094ec
        charge(ctx, 5);
        k_assert(a0, a1, 0x3094F8u, kDatCalcFile, 4469);
    }
    // 0x00309500
    charge(ctx, 12);
    a1 = s5 & 0xFFFF;
    v0 = sll(a1, 2);
    v0 = addu(v0, a1);
    v0 = sll(v0, 1);
    v0 = addu(v0, a1);
    fp = sll(v0, 2);  // * 44 (SkillRecord)
    lw(v0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
    a0 = addu(fp, v0);
    lbu(v1, a0, 36);
    v0 = 1;
    if (v1 == v0) {
        // 0x00309538
        charge(ctx, 5);
        lw(v1, s3, dat_unit::kStatus);
        v1 = v1 & 0x8;
        v1 = sltu(0, v1);
        if (v1 == 0) {
            // 0x00309554
            charge(ctx, 3);
            v0 = 4;
        } else {
            // 0x0030954c
            charge(ctx, 2);
        }
    } else {
        // 0x00309530
        charge(ctx, 2);
        // 0x00309560
        charge(ctx, 2);
        if (s4 != 0) {
            // 0x00309568
            charge(ctx, 3);
            at = slti(s0, btl::kSkillCount);
            if (at == 0) {
                goto L_003095fc;
            }
            // 0x00309574
            charge(ctx, 4);
            lbu(v0, a0, 0);
            v0 = v0 & 0x2;
            if (v0 == 0) {
                goto L_003095fc;
            }
            // 0x00309584
            charge(ctx, 4);
            lhu(v0, s4, dat_unit::kFlags);
            v0 = v0 & dat_unit::kFlagEnemy;
            if (v0 != 0) {
                // 0x00309594
                charge(ctx, 9);
                lhu(v1, s4, 2);
                v0 = sll(v1, 5);
                v0 = subu(v0, v1);
                v1 = sll(v0, 1);  // * 62 (EnemyRecord)
                lw(v0, gp, gp_off(btl::kUnitTablePtr));  // gBtlEnemyTbl
                v0 = addu(v1, v0);
                lhu(a1, v0, 60);
                goto L_003095fc;
            }
            // 0x003095b8
            charge(ctx, 17);
            lh(a0, s4, 2);
            a1 = 0;
            jal(ctx, 0x3095C0u, gen::fn_datGetEquipmentIdx_0016cb80);
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            lh(a0, s4, 2);
            jal(ctx, 0x3095D4u, gen::fn_sub_16F630_0016f630);
            v0 = v0 & 0xFFFF;
            a0 = dsll32(v0, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x3095E8u, gen::fn_sub_170D60_00170d60);
            lh(s7, v0, 30);
            goto L_00309610;
        }
    L_003095fc:
        charge(ctx, 5);
        v0 = a1 & 0xFFFF;
        v1 = sll(v0, 1);
        lw(v0, gp, gp_off(btl::kSkillElementTablePtr));  // gBtlSkillElementTbl
        v0 = addu(v0, v1);
        lb(s7, v0, 0);
    L_00309610:
        charge(ctx, 5);
        s0 = dsll32(s7, 16);
        s0 = dsra32(s0, 16);
        v0 = slti(s0, 19);
        if (v0 == 0) {
            // 0x00309624
            charge(ctx, 5);
            k_assert(a0, a1, 0x309630u, kDatCalcFile, 3752);
        }
        // 0x00309638
        charge(ctx, 8);
        v1 = addiu(s0, 1);
        v0 = 1;
        s6 = sllv(v0, v1);
        v0 = 0xE0000;
        v0 = v0 | 0x1;
        v0 = s6 & v0;
        if (v0 == 0) {
            // 0x00309658
            charge(ctx, 3);
            v0 = s6 & 0xE;
            if (v0 == 0) {
                // 0x00309800
                charge(ctx, 3);
                v0 = s6 & 0x100;
                if (v0 != 0) {
                L_00309844:
                    charge(ctx, 8);
                    a0 = s3;
                    a1 = 11;
                    jal(ctx, 0x30984Cu, gen::fn_datCalcGetEffectLevel_00300f60);
                    v0 = dsll32(v0, 24);
                    v0 = dsra32(v0, 24);
                    if (i64(v0) <= 0) {
                        // 0x00309870
                        charge(ctx, 8);
                        a0 = s3;
                        a1 = 8;
                        jal(ctx, 0x309878u, gen::fn_datCalcGetEffectLevel_00300f60);
                        v0 = dsll32(v0, 24);
                        v0 = dsra32(v0, 24);
                        if (i64(v0) <= 0) {
                            // 0x0030989c
                            charge(ctx, 8);
                            a0 = s3;
                            a1 = 9;
                            jal(ctx, 0x3098A4u, gen::fn_datCalcGetEffectLevel_00300f60);
                            v0 = dsll32(v0, 24);
                            v0 = dsra32(v0, 24);
                            if (i64(v0) <= 0) {
                                // 0x003098c8
                                charge(ctx, 8);
                                a0 = s3;
                                a1 = s7;
                                jal(ctx, 0x3098D0u, gen::fn_datCalcGetAffinityChecked_0030b4b0);
                                v1 = 0x2000000;
                                v1 = v0 & v1;
                                if (v1 == 0) {
                                    // 0x003098f4
                                    charge(ctx, 4);
                                    v1 = 0x4000000;
                                    v1 = v0 & v1;
                                    if (v1 == 0) {
                                        // 0x00309910
                                        charge(ctx, 4);
                                        v1 = 0x1000000;
                                        v0 = v0 & v1;
                                        if (v0 == 0) {
                                            goto L_0030992c;
                                        }
                                        // 0x00309920
                                        charge(ctx, 3);
                                        v0 = 256;
                                    } else {
                                        // 0x00309904
                                        charge(ctx, 3);
                                        v0 = 1024;
                                    }
                                } else {
                                    // 0x003098e8
                                    charge(ctx, 3);
                                    v0 = 512;
                                }
                            } else {
                                // 0x003098bc
                                charge(ctx, 3);
                                v0 = 256;
                            }
                        } else {
                            // 0x00309890
                            charge(ctx, 3);
                            v0 = 256;
                        }
                    } else {
                        // 0x00309864
                        charge(ctx, 3);
                        v0 = 512;
                    }
                } else {
                    // 0x0030980c
                    charge(ctx, 8);
                    lw(v0, s3, dat_unit::kEffectFlags);
                    v1 = 0x40000;
                    v0 = v0 & v1;
                    v0 = sltu(0, v0);
                    v0 = dsll32(v0, 24);
                    v0 = dsra32(v0, 24);
                    if (i64(v0) <= 0) {
                        goto L_00309844;
                    }
                    // 0x0030982c
                    charge(ctx, 6);
                    lw(v0, s3, dat_unit::kUnk18);
                    v0 = v0 | v1;
                    sw(v0, s3, dat_unit::kUnk18);
                    v0 = 512;
                }
            } else {
                // 0x00309664
                charge(ctx, 8);
                lw(v0, s3, dat_unit::kEffectFlags);
                v1 = 0x20000;
                v0 = v0 & v1;
                v0 = sltu(0, v0);
                v0 = dsll32(v0, 24);
                v0 = dsra32(v0, 24);
                if (i64(v0) <= 0) {
                    // 0x0030969c
                    charge(ctx, 4);
                    lw(v0, sp, 0xBC);
                    v0 = v0 & 0x2;
                    if (v0 != 0) {
                        goto L_00309844;
                    }
                    // 0x003096ac
                    charge(ctx, 7);
                    s2 = 0;
                    a0 = s3;
                    a1 = 546;
                    jal(ctx, 0x3096B8u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 == 0) {
                        // 0x003096c8
                        charge(ctx, 4);
                        lhu(v0, s3, dat_unit::kFlags);
                        v0 = v0 & dat_unit::kFlagEnemy;
                        if (v0 == 0) {
                            // 0x003096e4
                            charge(ctx, 4);
                            lhu(a0, s3, dat_unit::kId);
                            a1 = 179;
                            jal(ctx, 0x3096ECu, gen::fn_sub_300870_00300870);
                        } else {
                            // 0x003096d8
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x003096f4
                        charge(ctx, 3);
                        v0 = v0 & 0xFFFF;
                        if (v0 != 0) {
                            goto L_00309700;
                        }
                        // 0x00309710
                        charge(ctx, 6);
                        a0 = s3;
                        a1 = 545;
                        jal(ctx, 0x309718u, gen::fn_datCalcHasSkill_003005e0);
                        if (v0 == 0) {
                            // 0x00309728
                            charge(ctx, 4);
                            lhu(v0, s3, dat_unit::kFlags);
                            v0 = v0 & dat_unit::kFlagEnemy;
                            if (v0 == 0) {
                                // 0x00309744
                                charge(ctx, 4);
                                lhu(a0, s3, dat_unit::kId);
                                a1 = 178;
                                jal(ctx, 0x30974Cu, gen::fn_sub_300870_00300870);
                            } else {
                                // 0x00309738
                                charge(ctx, 3);
                                v0 = 0;
                            }
                            // 0x00309754
                            charge(ctx, 3);
                            v0 = v0 & 0xFFFF;
                            if (v0 != 0) {
                                goto L_00309760;
                            }
                            // 0x00309770
                            charge(ctx, 6);
                            a0 = s3;
                            a1 = 544;
                            jal(ctx, 0x309778u, gen::fn_datCalcHasSkill_003005e0);
                            if (v0 == 0) {
                                // 0x00309788
                                charge(ctx, 4);
                                lhu(v0, s3, dat_unit::kFlags);
                                v0 = v0 & dat_unit::kFlagEnemy;
                                if (v0 == 0) {
                                    // 0x003097a4
                                    charge(ctx, 4);
                                    lhu(a0, s3, dat_unit::kId);
                                    a1 = 177;
                                    jal(ctx, 0x3097ACu, gen::fn_sub_300870_00300870);
                                } else {
                                    // 0x00309798
                                    charge(ctx, 3);
                                    v0 = 0;
                                }
                                // 0x003097b4
                                charge(ctx, 3);
                                v0 = v0 & 0xFFFF;
                                if (v0 != 0) {
                                    goto L_003097c0;
                                }
                                goto L_003097c8;
                            }
                        L_003097c0:
                            charge(ctx, 2);
                            s2 = 10;
                            s1 = 4640;
                            goto L_003097c8;
                        }
                    L_00309760:
                        charge(ctx, 4);
                        s2 = 15;
                        s1 = 4641;
                        goto L_003097c8;
                    }
                L_00309700:
                    charge(ctx, 4);
                    s2 = 20;
                    s1 = 4642;
                L_003097c8:
                    charge(ctx, 4);
                    s2 = dsll32(s2, 16);
                    s2 = dsra32(s2, 16);
                    if (s2 == 0) {
                        goto L_00309844;
                    }
                    // 0x003097d8
                    charge(ctx, 6);
                    a0 = 100;
                    jal(ctx, 0x3097DCu, gen::fn_datCalcRand_002ffbc0);
                    at = slt(v0, s2);
                    if (at == 0) {
                        goto L_00309844;
                    }
                    // 0x003097f0
                    charge(ctx, 4);
                    sh(s1, s3, dat_unit::kMessageId);
                    v0 = 512;
                } else {
                    // 0x00309684
                    charge(ctx, 6);
                    lw(v0, s3, dat_unit::kUnk18);
                    v0 = v0 | v1;
                    sw(v0, s3, dat_unit::kUnk18);
                    v0 = 512;
                }
            }
            // 0x0030a6fc: epilogue
            charge(ctx, 17);
            ld(ra, sp, 0xA0);
            lq(fp, sp, 0x90);
            lq(s7, sp, 0x80);
            lq(s6, sp, 0x70);
            lq(s5, sp, 0x60);
            lq(s4, sp, 0x50);
            lq(s3, sp, 0x40);
            lq(s2, sp, 0x30);
            lq(s1, sp, 0x20);
            lq(s0, sp, 0x10);
            lwc1(f23, sp, 0xC);
            lwc1(f22, sp, 0x8);
            lwc1(f21, sp, 0x4);
            lwc1(f20, sp, 0x0);
            sp = addiu(sp, 0xC0);
            return;
        }
    L_0030992c:
        charge(ctx, 6);
        lw(v0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
        v0 = addiu(v0, 14);
        v0 = addu(v0, fp);
        lbu(a0, v0, 0);
        if (a0 != 0) {
            // 0x00309950
            charge(ctx, 6);
            lw(v1, s3, dat_unit::kStatus);
            v0 = 0x100000;
            v0 = v1 & v0;
            v0 = sltu(0, v0);
            if (v0 == 0) {
                // 0x00309974
                charge(ctx, 3);
                v0 = slti(a0, 100);
                if (v0 != 0) {
                    // 0x0030998c
                    charge(ctx, 4);
                    lhu(v0, s3, dat_unit::kFlags);
                    v0 = v0 & 0x80;
                    if (v0 == 0) {
                        // 0x003099a8
                        charge(ctx, 5);
                        v1 = dsll32(v1, 12);
                        v1 = dsrl32(v1, 12);
                        v0 = 512;
                        if (v1 != v0) {
                            // 0x003099bc
                            charge(ctx, 3);
                            v0 = 2;
                            if (v1 == v0) {
                                goto L_003099e8;
                            }
                            // 0x003099c8
                            charge(ctx, 3);
                            v0 = 64;
                            if (v1 == v0) {
                                goto L_003099e8;
                            }
                            // 0x003099d4
                            charge(ctx, 3);
                            v0 = 32;
                            if (v1 == v0) {
                                goto L_003099e8;
                            }
                            // 0x003099e0
                            charge(ctx, 2);
                            // 0x003099f4
                            charge(ctx, 22);
                            a0 = s4;
                            a1 = 4;
                            a2 = s5;
                            jal(ctx, 0x309A00u, gen::fn_datCalcGetEffectMultiplier_00301880);
                            mov_s(f22, f0);
                            a0 = s3;
                            a1 = 2;
                            a2 = s5;
                            jal(ctx, 0x309A18u, gen::fn_datCalcGetEffectMultiplier_00301880);
                            mov_s(f23, f0);
                            v0 = flt(1.0f);
                            mtc1(v0, f21);
                            mov_s(f20, f21);
                            s2 = 0;
                            s1 = 0;
                            lhu(v0, s4, dat_unit::kFlags);
                            v0 = v0 & dat_unit::kFlagEnemy;
                            if (v0 == 0) {
                                // 0x00309a58
                                charge(ctx, 3);
                                lh(a0, s4, 2);
                                jal(ctx, 0x309A5Cu, gen::fn_sub_16C920_0016c920);
                            } else {
                                // 0x00309a4c
                                charge(ctx, 3);
                                v0 = 0;
                            }
                            // 0x00309a64
                            charge(ctx, 4);
                            v1 = v0 & 0xFFFF;
                            v0 = 5;
                            if (v1 != v0) {
                                // 0x00309a74
                                charge(ctx, 4);
                                lhu(v0, s4, dat_unit::kFlags);
                                v0 = v0 & dat_unit::kFlagEnemy;
                                if (v0 == 0) {
                                    // 0x00309a90
                                    charge(ctx, 3);
                                    lh(a0, s4, 2);
                                    jal(ctx, 0x309A94u, gen::fn_sub_16C920_0016c920);
                                } else {
                                    // 0x00309a84
                                    charge(ctx, 3);
                                    v0 = 0;
                                }
                                // 0x00309a9c
                                charge(ctx, 4);
                                v1 = v0 & 0xFFFF;
                                v0 = 4;
                                if (v1 == v0) {
                                    goto L_00309aac;
                                }
                                goto L_00309ae0;
                            }
                        L_00309aac:
                            charge(ctx, 7);
                            a0 = 4889;
                            jal(ctx, 0x309AB0u, gen::fn_datGetFlag_0016f190);
                            v0 = sltu(0, v0);
                            v0 = v0 ^ 0x1;
                            if (v0 == 0) {
                                // 0x00309ad8
                                charge(ctx, 1);
                                lwc1(f0, gp, gp_off(0x7CAD78u));  // 0x7CAD78
                            } else {
                                // 0x00309ac8
                                charge(ctx, 4);
                                v0 = flt(0.5f);
                                mtc1(v0, f0);
                            }
                            // 0x00309adc
                            charge(ctx, 1);
                            mul_s(f21, f21, f0);
                        L_00309ae0:
                            charge(ctx, 4);
                            lhu(v0, s3, dat_unit::kFlags);
                            v0 = v0 & dat_unit::kFlagEnemy;
                            if (v0 == 0) {
                                // 0x00309afc
                                charge(ctx, 3);
                                lh(a0, s3, dat_unit::kId);
                                jal(ctx, 0x309B00u, gen::fn_sub_16C920_0016c920);
                            } else {
                                // 0x00309af0
                                charge(ctx, 3);
                                v0 = 0;
                            }
                            // 0x00309b08
                            charge(ctx, 4);
                            v1 = v0 & 0xFFFF;
                            v0 = 5;
                            if (v1 != v0) {
                                // 0x00309b18
                                charge(ctx, 4);
                                lhu(v0, s3, dat_unit::kFlags);
                                v0 = v0 & dat_unit::kFlagEnemy;
                                if (v0 == 0) {
                                    // 0x00309b34
                                    charge(ctx, 3);
                                    lh(a0, s3, dat_unit::kId);
                                    jal(ctx, 0x309B38u, gen::fn_sub_16C920_0016c920);
                                } else {
                                    // 0x00309b28
                                    charge(ctx, 3);
                                    v0 = 0;
                                }
                                // 0x00309b40
                                charge(ctx, 4);
                                v1 = v0 & 0xFFFF;
                                v0 = 4;
                                if (v1 == v0) {
                                    goto L_00309b50;
                                }
                                // 0x00309b8c
                                charge(ctx, 4);
                                lhu(v0, s3, dat_unit::kFlags);
                                v0 = v0 & dat_unit::kFlagEnemy;
                                if (v0 == 0) {
                                    // 0x00309ba8
                                    charge(ctx, 3);
                                    lh(a0, s3, dat_unit::kId);
                                    jal(ctx, 0x309BACu, gen::fn_sub_16C920_0016c920);
                                } else {
                                    // 0x00309b9c
                                    charge(ctx, 3);
                                    v0 = 0;
                                }
                                // 0x00309bb4
                                charge(ctx, 4);
                                v1 = v0 & 0xFFFF;
                                v0 = 1;
                                if (v1 != v0) {
                                    // 0x00309bc4
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x00309be0
                                        charge(ctx, 3);
                                        lh(a0, s3, dat_unit::kId);
                                        jal(ctx, 0x309BE4u, gen::fn_sub_16C920_0016c920);
                                    } else {
                                        // 0x00309bd4
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x00309bec
                                    charge(ctx, 4);
                                    v1 = v0 & 0xFFFF;
                                    v0 = 2;
                                    if (v1 == v0) {
                                        // 0x00309bfc
                                        charge(ctx, 2);
                                        lwc1(f0, gp, gp_off(ai::kLit0_90));  // 0x7CAF8C
                                        mul_s(f21, f21, f0);
                                    }
                                }
                                goto L_00309c04;
                            }
                        L_00309b50:
                            charge(ctx, 7);
                            a0 = 4889;
                            jal(ctx, 0x309B54u, gen::fn_datGetFlag_0016f190);
                            v0 = sltu(0, v0);
                            v0 = v0 ^ 0x1;
                            if (v0 == 0) {
                                // 0x00309b7c
                                charge(ctx, 1);
                                lwc1(f0, gp, gp_off(0x7CAF98u));  // 0x7CAF98
                            } else {
                                // 0x00309b6c
                                charge(ctx, 4);
                                v0 = flt(2.0f);
                                mtc1(v0, f0);
                            }
                            // 0x00309b80
                            charge(ctx, 3);
                            mul_s(f21, f21, f0);
                        L_00309c04:
                            charge(ctx, 4);
                            lw(v0, sp, 0xBC);
                            v0 = v0 & 0x2;
                            if (v0 == 0) {
                                // 0x00309c14
                                charge(ctx, 3);
                                at = sltiu(s0, 7);
                                if (at != 0) {
                                    // 0x00309c20
                                    charge(ctx, 7);
                                    v1 = hi(0x7B9080u);
                                    v1 = addiu(v1, lo(0x7B9080u));  // &0x7B9080
                                    v0 = sll(s0, 2);
                                    v0 = addu(v0, v1);
                                    lw(v0, v0, 0);
                                    switch (v0.u()) {
                                    case 0x309C3Cu:  // table[0]
                                        // 0x00309c3c
                                        charge(ctx, 6);
                                        a0 = s3;
                                        a1 = 509;
                                        jal(ctx, 0x309C44u, gen::fn_datCalcHasSkill_003005e0);
                                        if (v0 == 0) {
                                            // 0x00309c68
                                            charge(ctx, 6);
                                            a0 = s3;
                                            a1 = 508;
                                            jal(ctx, 0x309C70u, gen::fn_datCalcHasSkill_003005e0);
                                            if (v0 != 0) {
                                                // 0x00309c80
                                                charge(ctx, 5);
                                                lwc1(f0, gp, gp_off(ai::kLit0_85));  // 0x7CAD94
                                                mul_s(f20, f20, f0);
                                                s1 = 4604;
                                            }
                                        } else {
                                            // 0x00309c54
                                            charge(ctx, 5);
                                            lwc1(f0, gp, gp_off(ai::kLit0_60));  // 0x7CADB4
                                            mul_s(f20, f20, f0);
                                            s1 = 4605;
                                        }
                                        break;
                                    case 0x309C94u:  // table[1]
                                        // 0x00309c94
                                        charge(ctx, 6);
                                        a0 = s3;
                                        a1 = 511;
                                        jal(ctx, 0x309C9Cu, gen::fn_datCalcHasSkill_003005e0);
                                        if (v0 == 0) {
                                            // 0x00309cc0
                                            charge(ctx, 6);
                                            a0 = s3;
                                            a1 = 510;
                                            jal(ctx, 0x309CC8u, gen::fn_datCalcHasSkill_003005e0);
                                            if (v0 != 0) {
                                                // 0x00309cd8
                                                charge(ctx, 5);
                                                lwc1(f0, gp, gp_off(ai::kLit0_85));  // 0x7CAD94
                                                mul_s(f20, f20, f0);
                                                s1 = 4606;
                                            }
                                        } else {
                                            // 0x00309cac
                                            charge(ctx, 5);
                                            lwc1(f0, gp, gp_off(ai::kLit0_60));  // 0x7CADB4
                                            mul_s(f20, f20, f0);
                                            s1 = 4607;
                                        }
                                        break;
                                    case 0x309CECu:  // table[2]
                                        // 0x00309cec
                                        charge(ctx, 6);
                                        a0 = s3;
                                        a1 = 513;
                                        jal(ctx, 0x309CF4u, gen::fn_datCalcHasSkill_003005e0);
                                        if (v0 == 0) {
                                            // 0x00309d18
                                            charge(ctx, 6);
                                            a0 = s3;
                                            a1 = 512;
                                            jal(ctx, 0x309D20u, gen::fn_datCalcHasSkill_003005e0);
                                            if (v0 != 0) {
                                                // 0x00309d30
                                                charge(ctx, 5);
                                                lwc1(f0, gp, gp_off(ai::kLit0_85));  // 0x7CAD94
                                                mul_s(f20, f20, f0);
                                                s1 = 4608;
                                            }
                                        } else {
                                            // 0x00309d04
                                            charge(ctx, 5);
                                            lwc1(f0, gp, gp_off(ai::kLit0_60));  // 0x7CADB4
                                            mul_s(f20, f20, f0);
                                            s1 = 4609;
                                        }
                                        break;
                                    case 0x309D44u:  // table[3]
                                        // 0x00309d44
                                        charge(ctx, 6);
                                        a0 = s3;
                                        a1 = 515;
                                        jal(ctx, 0x309D4Cu, gen::fn_datCalcHasSkill_003005e0);
                                        if (v0 == 0) {
                                            // 0x00309d70
                                            charge(ctx, 6);
                                            a0 = s3;
                                            a1 = 514;
                                            jal(ctx, 0x309D78u, gen::fn_datCalcHasSkill_003005e0);
                                            if (v0 != 0) {
                                                // 0x00309d88
                                                charge(ctx, 5);
                                                lwc1(f0, gp, gp_off(ai::kLit0_85));  // 0x7CAD94
                                                mul_s(f20, f20, f0);
                                                s1 = 4610;
                                            }
                                        } else {
                                            // 0x00309d5c
                                            charge(ctx, 5);
                                            lwc1(f0, gp, gp_off(ai::kLit0_60));  // 0x7CADB4
                                            mul_s(f20, f20, f0);
                                            s1 = 4611;
                                        }
                                        break;
                                    case 0x309D9Cu:  // table[4]
                                        // 0x00309d9c
                                        charge(ctx, 6);
                                        a0 = s3;
                                        a1 = 517;
                                        jal(ctx, 0x309DA4u, gen::fn_datCalcHasSkill_003005e0);
                                        if (v0 == 0) {
                                            // 0x00309dc8
                                            charge(ctx, 6);
                                            a0 = s3;
                                            a1 = 516;
                                            jal(ctx, 0x309DD0u, gen::fn_datCalcHasSkill_003005e0);
                                            if (v0 != 0) {
                                                // 0x00309de0
                                                charge(ctx, 5);
                                                lwc1(f0, gp, gp_off(ai::kLit0_85));  // 0x7CAD94
                                                mul_s(f20, f20, f0);
                                                s1 = 4612;
                                            }
                                        } else {
                                            // 0x00309db4
                                            charge(ctx, 5);
                                            lwc1(f0, gp, gp_off(ai::kLit0_60));  // 0x7CADB4
                                            mul_s(f20, f20, f0);
                                            s1 = 4613;
                                        }
                                        break;
                                    case 0x309DF4u:  // table[6]
                                        // 0x00309df4
                                        charge(ctx, 6);
                                        a0 = s3;
                                        a1 = 519;
                                        jal(ctx, 0x309DFCu, gen::fn_datCalcHasSkill_003005e0);
                                        if (v0 == 0) {
                                            // 0x00309e20
                                            charge(ctx, 6);
                                            a0 = s3;
                                            a1 = 518;
                                            jal(ctx, 0x309E28u, gen::fn_datCalcHasSkill_003005e0);
                                            if (v0 != 0) {
                                                // 0x00309e38
                                                charge(ctx, 5);
                                                lwc1(f0, gp, gp_off(ai::kLit0_85));  // 0x7CAD94
                                                mul_s(f20, f20, f0);
                                                s1 = 4614;
                                            }
                                        } else {
                                            // 0x00309e0c
                                            charge(ctx, 5);
                                            lwc1(f0, gp, gp_off(ai::kLit0_60));  // 0x7CADB4
                                            mul_s(f20, f20, f0);
                                            s1 = 4615;
                                        }
                                        break;
                                    case 0x309E4Cu:  // table[5]
                                        // 0x00309e4c
                                        charge(ctx, 6);
                                        a0 = s3;
                                        a1 = 521;
                                        jal(ctx, 0x309E54u, gen::fn_datCalcHasSkill_003005e0);
                                        if (v0 == 0) {
                                            // 0x00309e78
                                            charge(ctx, 6);
                                            a0 = s3;
                                            a1 = 520;
                                            jal(ctx, 0x309E80u, gen::fn_datCalcHasSkill_003005e0);
                                            if (v0 != 0) {
                                                // 0x00309e90
                                                charge(ctx, 3);
                                                lwc1(f0, gp, gp_off(ai::kLit0_85));  // 0x7CAD94
                                                mul_s(f20, f20, f0);
                                                s1 = 4616;
                                            }
                                        } else {
                                            // 0x00309e64
                                            charge(ctx, 5);
                                            lwc1(f0, gp, gp_off(ai::kLit0_60));  // 0x7CADB4
                                            mul_s(f20, f20, f0);
                                            s1 = 4617;
                                        }
                                        break;
                                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                                        tail(ctx, v0.u());
                                        return;
                                    }
                                }
                                // 0x00309e9c
                                charge(ctx, 6);
                                v0 = flt(1.0f);
                                mtc1(v0, f0);
                                c_eq_s(f0, f20);
                                if (cond(ctx)) {
                                    // 0x00309eb4
                                    charge(ctx, 3);
                                    v0 = s6 & 0xE;
                                    if (v0 != 0) {
                                        // 0x00309ec0
                                        charge(ctx, 6);
                                        a0 = s3;
                                        a1 = 526;
                                        jal(ctx, 0x309EC8u, gen::fn_datCalcHasSkill_003005e0);
                                        if (v0 != 0) {
                                            // 0x00309ed8
                                            charge(ctx, 3);
                                            lwc1(f0, gp, gp_off(ai::kLit0_85));  // 0x7CAD94
                                            mul_s(f20, f20, f0);
                                            s1 = 4622;
                                        }
                                    }
                                    // 0x00309ee4
                                    charge(ctx, 3);
                                    v0 = s6 & 0x6F0;
                                    if (v0 != 0) {
                                        // 0x00309ef0
                                        charge(ctx, 6);
                                        a0 = s3;
                                        a1 = 527;
                                        jal(ctx, 0x309EF8u, gen::fn_datCalcHasSkill_003005e0);
                                        if (v0 != 0) {
                                            // 0x00309f08
                                            charge(ctx, 3);
                                            lwc1(f0, gp, gp_off(ai::kLit0_85));  // 0x7CAD94
                                            mul_s(f20, f20, f0);
                                            s1 = 4623;
                                        }
                                    }
                                }
                                // 0x00309f14
                                charge(ctx, 6);
                                a0 = s3;
                                a1 = 564;
                                jal(ctx, 0x309F1Cu, gen::fn_datCalcHasSkill_003005e0);
                                if (v0 == 0) {
                                    // 0x00309f38
                                    charge(ctx, 6);
                                    a0 = s3;
                                    a1 = 563;
                                    jal(ctx, 0x309F40u, gen::fn_datCalcHasSkill_003005e0);
                                    if (v0 != 0) {
                                        // 0x00309f50
                                        charge(ctx, 4);
                                        v0 = flt(0.5f);
                                        mtc1(v0, f0);
                                        mul_s(f20, f20, f0);
                                    }
                                    // 0x00309f60
                                    charge(ctx, 8);
                                    a0 = s3;
                                    a1 = 10;
                                    jal(ctx, 0x309F68u, gen::fn_datCalcGetEffectLevel_00300f60);
                                    v0 = dsll32(v0, 24);
                                    v0 = dsra32(v0, 24);
                                    if (i64(v0) > 0) {
                                        // 0x00309f80
                                        charge(ctx, 2);
                                        lwc1(f0, gp, gp_off(ai::kLit0_70));  // 0x7CADD0
                                        mul_s(f20, f20, f0);
                                    }
                                    // 0x00309f88
                                    charge(ctx, 5);
                                    lw(v0, s3, dat_unit::kStatus);
                                    v0 = v0 & 0x100;
                                    v0 = sltu(0, v0);
                                    if (v0 != 0) {
                                        // 0x00309f9c
                                        charge(ctx, 6);
                                        jal(ctx, 0x309F9Cu, gen::fn_sub_17D800_0017d800);
                                        v0 = flt(0.5f);
                                        mtc1(v0, f0);
                                        mul_s(f21, f21, f0);
                                    }
                                    goto L_00309fb4;
                                }
                                // 0x00309f2c
                                charge(ctx, 3);
                                v0 = 1;
                                // 0x0030a6fc: epilogue
                                charge(ctx, 17);
                                ld(ra, sp, 0xA0);
                                lq(fp, sp, 0x90);
                                lq(s7, sp, 0x80);
                                lq(s6, sp, 0x70);
                                lq(s5, sp, 0x60);
                                lq(s4, sp, 0x50);
                                lq(s3, sp, 0x40);
                                lq(s2, sp, 0x30);
                                lq(s1, sp, 0x20);
                                lq(s0, sp, 0x10);
                                lwc1(f23, sp, 0xC);
                                lwc1(f22, sp, 0x8);
                                lwc1(f21, sp, 0x4);
                                lwc1(f20, sp, 0x0);
                                sp = addiu(sp, 0xC0);
                                return;
                            }
                        L_00309fb4:
                            charge(ctx, 12);
                            a0 = 4;
                            a1 = s4;
                            a2 = s3;
                            a3 = s5;
                            t0 = 0;
                            jal(ctx, 0x309FC8u, gen::fn_datScriptCalc_0030fc40);
                            s4 = v0;
                            lhu(v0, s3, dat_unit::kFlags);
                            v1 = v0 & dat_unit::kFlagEnemy;
                            if (v1 == 0) {
                                // 0x00309fe4
                                charge(ctx, 3);
                                v0 = 2;
                                if (s0 != v0) {
                                    // 0x00309ff0
                                    charge(ctx, 3);
                                    v0 = 1;
                                    if (s0 == v0) {
                                        goto L_0030a00c;
                                    }
                                    // 0x00309ffc
                                    charge(ctx, 2);
                                    if (s0 == 0) {
                                        goto L_0030a00c;
                                    }
                                    // 0x0030a004
                                    charge(ctx, 2);
                                    goto L_0030a0ac;
                                }
                            L_0030a00c:
                                charge(ctx, 2);
                                if (v1 == 0) {
                                    // 0x0030a020
                                    charge(ctx, 4);
                                    lhu(a0, s3, dat_unit::kId);
                                    a1 = 112;
                                    jal(ctx, 0x30A028u, gen::fn_sub_300750_00300750);
                                } else {
                                    // 0x0030a014
                                    charge(ctx, 3);
                                    v0 = 0;
                                }
                                // 0x0030a030
                                charge(ctx, 2);
                                if (v0 != 0) {
                                    // 0x0030a038
                                    charge(ctx, 1);
                                    s2 = addiu(s2, 5);
                                }
                                // 0x0030a03c
                                charge(ctx, 4);
                                lhu(v0, s3, dat_unit::kFlags);
                                v0 = v0 & dat_unit::kFlagEnemy;
                                if (v0 == 0) {
                                    // 0x0030a058
                                    charge(ctx, 4);
                                    lhu(a0, s3, dat_unit::kId);
                                    a1 = 113;
                                    jal(ctx, 0x30A060u, gen::fn_sub_300750_00300750);
                                } else {
                                    // 0x0030a04c
                                    charge(ctx, 3);
                                    v0 = 0;
                                }
                                // 0x0030a068
                                charge(ctx, 2);
                                if (v0 != 0) {
                                    // 0x0030a070
                                    charge(ctx, 1);
                                    s2 = addiu(s2, 10);
                                }
                                // 0x0030a074
                                charge(ctx, 4);
                                lhu(v0, s3, dat_unit::kFlags);
                                v0 = v0 & dat_unit::kFlagEnemy;
                                if (v0 == 0) {
                                    // 0x0030a090
                                    charge(ctx, 4);
                                    lhu(a0, s3, dat_unit::kId);
                                    a1 = 114;
                                    jal(ctx, 0x30A098u, gen::fn_sub_300750_00300750);
                                } else {
                                    // 0x0030a084
                                    charge(ctx, 3);
                                    v0 = 0;
                                }
                                // 0x0030a0a0
                                charge(ctx, 2);
                                if (v0 != 0) {
                                    // 0x0030a0a8
                                    charge(ctx, 1);
                                    s2 = addiu(s2, 15);
                                }
                            L_0030a0ac:
                                charge(ctx, 3);
                                v0 = 6;
                                if (s0 != v0) {
                                    // 0x0030a0b8
                                    charge(ctx, 3);
                                    v0 = 5;
                                    if (s0 == v0) {
                                        goto L_0030a0e4;
                                    }
                                    // 0x0030a0c4
                                    charge(ctx, 3);
                                    v0 = 4;
                                    if (s0 == v0) {
                                        goto L_0030a0e4;
                                    }
                                    // 0x0030a0d0
                                    charge(ctx, 3);
                                    v0 = 3;
                                    if (s0 == v0) {
                                        goto L_0030a0e4;
                                    }
                                    // 0x0030a0dc
                                    charge(ctx, 2);
                                    goto L_0030a18c;
                                }
                            L_0030a0e4:
                                charge(ctx, 4);
                                lhu(v0, s3, dat_unit::kFlags);
                                v0 = v0 & dat_unit::kFlagEnemy;
                                if (v0 == 0) {
                                    // 0x0030a100
                                    charge(ctx, 4);
                                    lhu(a0, s3, dat_unit::kId);
                                    a1 = 127;
                                    jal(ctx, 0x30A108u, gen::fn_sub_300750_00300750);
                                } else {
                                    // 0x0030a0f4
                                    charge(ctx, 3);
                                    v0 = 0;
                                }
                                // 0x0030a110
                                charge(ctx, 2);
                                if (v0 != 0) {
                                    // 0x0030a118
                                    charge(ctx, 1);
                                    s2 = addiu(s2, 5);
                                }
                                // 0x0030a11c
                                charge(ctx, 4);
                                lhu(v0, s3, dat_unit::kFlags);
                                v0 = v0 & dat_unit::kFlagEnemy;
                                if (v0 == 0) {
                                    // 0x0030a138
                                    charge(ctx, 4);
                                    lhu(a0, s3, dat_unit::kId);
                                    a1 = 128;
                                    jal(ctx, 0x30A140u, gen::fn_sub_300750_00300750);
                                } else {
                                    // 0x0030a12c
                                    charge(ctx, 3);
                                    v0 = 0;
                                }
                                // 0x0030a148
                                charge(ctx, 2);
                                if (v0 != 0) {
                                    // 0x0030a150
                                    charge(ctx, 1);
                                    s2 = addiu(s2, 10);
                                }
                                // 0x0030a154
                                charge(ctx, 4);
                                lhu(v0, s3, dat_unit::kFlags);
                                v0 = v0 & dat_unit::kFlagEnemy;
                                if (v0 == 0) {
                                    // 0x0030a170
                                    charge(ctx, 4);
                                    lhu(a0, s3, dat_unit::kId);
                                    a1 = 129;
                                    jal(ctx, 0x30A178u, gen::fn_sub_300750_00300750);
                                } else {
                                    // 0x0030a164
                                    charge(ctx, 3);
                                    v0 = 0;
                                }
                                // 0x0030a180
                                charge(ctx, 2);
                                if (v0 != 0) {
                                    // 0x0030a188
                                    charge(ctx, 1);
                                    s2 = addiu(s2, 15);
                                }
                            L_0030a18c:
                                charge(ctx, 3);
                                at = sltiu(s0, 7);
                                if (at != 0) {
                                    // 0x0030a198
                                    charge(ctx, 7);
                                    v1 = hi(0x7B9060u);
                                    v1 = addiu(v1, lo(0x7B9060u));  // &0x7B9060
                                    v0 = sll(s0, 2);
                                    v0 = addu(v0, v1);
                                    lw(v0, v0, 0);
                                    switch (v0.u()) {
                                    case 0x30A1B4u:  // table[0]
                                        // 0x0030a1b4
                                        charge(ctx, 4);
                                        lhu(v0, s3, dat_unit::kFlags);
                                        v0 = v0 & dat_unit::kFlagEnemy;
                                        if (v0 == 0) {
                                            // 0x0030a1d0
                                            charge(ctx, 4);
                                            lhu(a0, s3, dat_unit::kId);
                                            a1 = 106;
                                            jal(ctx, 0x30A1D8u, gen::fn_sub_300750_00300750);
                                        } else {
                                            // 0x0030a1c4
                                            charge(ctx, 3);
                                            v0 = 0;
                                        }
                                        // 0x0030a1e0
                                        charge(ctx, 2);
                                        if (v0 != 0) {
                                            // 0x0030a1e8
                                            charge(ctx, 1);
                                            s2 = addiu(s2, 5);
                                        }
                                        // 0x0030a1ec
                                        charge(ctx, 4);
                                        lhu(v0, s3, dat_unit::kFlags);
                                        v0 = v0 & dat_unit::kFlagEnemy;
                                        if (v0 == 0) {
                                            // 0x0030a208
                                            charge(ctx, 4);
                                            lhu(a0, s3, dat_unit::kId);
                                            a1 = 107;
                                            jal(ctx, 0x30A210u, gen::fn_sub_300750_00300750);
                                        } else {
                                            // 0x0030a1fc
                                            charge(ctx, 3);
                                            v0 = 0;
                                        }
                                        // 0x0030a218
                                        charge(ctx, 2);
                                        if (v0 != 0) {
                                            // 0x0030a220
                                            charge(ctx, 1);
                                            s2 = addiu(s2, 10);
                                        }
                                        // 0x0030a224
                                        charge(ctx, 4);
                                        lhu(v0, s3, dat_unit::kFlags);
                                        v0 = v0 & dat_unit::kFlagEnemy;
                                        if (v0 == 0) {
                                            // 0x0030a240
                                            charge(ctx, 4);
                                            lhu(a0, s3, dat_unit::kId);
                                            a1 = 108;
                                            jal(ctx, 0x30A248u, gen::fn_sub_300750_00300750);
                                        } else {
                                            // 0x0030a234
                                            charge(ctx, 3);
                                            v0 = 0;
                                        }
                                        // 0x0030a250
                                        charge(ctx, 2);
                                        if (v0 != 0) {
                                            // 0x0030a258
                                            charge(ctx, 3);
                                            s2 = addiu(s2, 15);
                                        }
                                        break;
                                    case 0x30A264u:  // table[1]
                                        // 0x0030a264
                                        charge(ctx, 4);
                                        lhu(v0, s3, dat_unit::kFlags);
                                        v0 = v0 & dat_unit::kFlagEnemy;
                                        if (v0 == 0) {
                                            // 0x0030a280
                                            charge(ctx, 4);
                                            lhu(a0, s3, dat_unit::kId);
                                            a1 = 103;
                                            jal(ctx, 0x30A288u, gen::fn_sub_300750_00300750);
                                        } else {
                                            // 0x0030a274
                                            charge(ctx, 3);
                                            v0 = 0;
                                        }
                                        // 0x0030a290
                                        charge(ctx, 2);
                                        if (v0 != 0) {
                                            // 0x0030a298
                                            charge(ctx, 1);
                                            s2 = addiu(s2, 5);
                                        }
                                        // 0x0030a29c
                                        charge(ctx, 4);
                                        lhu(v0, s3, dat_unit::kFlags);
                                        v0 = v0 & dat_unit::kFlagEnemy;
                                        if (v0 == 0) {
                                            // 0x0030a2b8
                                            charge(ctx, 4);
                                            lhu(a0, s3, dat_unit::kId);
                                            a1 = 104;
                                            jal(ctx, 0x30A2C0u, gen::fn_sub_300750_00300750);
                                        } else {
                                            // 0x0030a2ac
                                            charge(ctx, 3);
                                            v0 = 0;
                                        }
                                        // 0x0030a2c8
                                        charge(ctx, 2);
                                        if (v0 != 0) {
                                            // 0x0030a2d0
                                            charge(ctx, 1);
                                            s2 = addiu(s2, 10);
                                        }
                                        // 0x0030a2d4
                                        charge(ctx, 4);
                                        lhu(v0, s3, dat_unit::kFlags);
                                        v0 = v0 & dat_unit::kFlagEnemy;
                                        if (v0 == 0) {
                                            // 0x0030a2f0
                                            charge(ctx, 4);
                                            lhu(a0, s3, dat_unit::kId);
                                            a1 = 105;
                                            jal(ctx, 0x30A2F8u, gen::fn_sub_300750_00300750);
                                        } else {
                                            // 0x0030a2e4
                                            charge(ctx, 3);
                                            v0 = 0;
                                        }
                                        // 0x0030a300
                                        charge(ctx, 2);
                                        if (v0 != 0) {
                                            // 0x0030a308
                                            charge(ctx, 3);
                                            s2 = addiu(s2, 15);
                                        }
                                        break;
                                    case 0x30A314u:  // table[2]
                                        // 0x0030a314
                                        charge(ctx, 4);
                                        lhu(v0, s3, dat_unit::kFlags);
                                        v0 = v0 & dat_unit::kFlagEnemy;
                                        if (v0 == 0) {
                                            // 0x0030a330
                                            charge(ctx, 4);
                                            lhu(a0, s3, dat_unit::kId);
                                            a1 = 109;
                                            jal(ctx, 0x30A338u, gen::fn_sub_300750_00300750);
                                        } else {
                                            // 0x0030a324
                                            charge(ctx, 3);
                                            v0 = 0;
                                        }
                                        // 0x0030a340
                                        charge(ctx, 2);
                                        if (v0 != 0) {
                                            // 0x0030a348
                                            charge(ctx, 1);
                                            s2 = addiu(s2, 5);
                                        }
                                        // 0x0030a34c
                                        charge(ctx, 4);
                                        lhu(v0, s3, dat_unit::kFlags);
                                        v0 = v0 & dat_unit::kFlagEnemy;
                                        if (v0 == 0) {
                                            // 0x0030a368
                                            charge(ctx, 4);
                                            lhu(a0, s3, dat_unit::kId);
                                            a1 = 110;
                                            jal(ctx, 0x30A370u, gen::fn_sub_300750_00300750);
                                        } else {
                                            // 0x0030a35c
                                            charge(ctx, 3);
                                            v0 = 0;
                                        }
                                        // 0x0030a378
                                        charge(ctx, 2);
                                        if (v0 != 0) {
                                            // 0x0030a380
                                            charge(ctx, 1);
                                            s2 = addiu(s2, 10);
                                        }
                                        // 0x0030a384
                                        charge(ctx, 4);
                                        lhu(v0, s3, dat_unit::kFlags);
                                        v0 = v0 & dat_unit::kFlagEnemy;
                                        if (v0 == 0) {
                                            // 0x0030a3a0
                                            charge(ctx, 4);
                                            lhu(a0, s3, dat_unit::kId);
                                            a1 = 111;
                                            jal(ctx, 0x30A3A8u, gen::fn_sub_300750_00300750);
                                        } else {
                                            // 0x0030a394
                                            charge(ctx, 3);
                                            v0 = 0;
                                        }
                                        // 0x0030a3b0
                                        charge(ctx, 2);
                                        if (v0 != 0) {
                                            // 0x0030a3b8
                                            charge(ctx, 3);
                                            s2 = addiu(s2, 15);
                                        }
                                        break;
                                    case 0x30A3C4u:  // table[3]
                                        // 0x0030a3c4
                                        charge(ctx, 4);
                                        lhu(v0, s3, dat_unit::kFlags);
                                        v0 = v0 & dat_unit::kFlagEnemy;
                                        if (v0 == 0) {
                                            // 0x0030a3e0
                                            charge(ctx, 4);
                                            lhu(a0, s3, dat_unit::kId);
                                            a1 = 115;
                                            jal(ctx, 0x30A3E8u, gen::fn_sub_300750_00300750);
                                        } else {
                                            // 0x0030a3d4
                                            charge(ctx, 3);
                                            v0 = 0;
                                        }
                                        // 0x0030a3f0
                                        charge(ctx, 2);
                                        if (v0 != 0) {
                                            // 0x0030a3f8
                                            charge(ctx, 1);
                                            s2 = addiu(s2, 5);
                                        }
                                        // 0x0030a3fc
                                        charge(ctx, 4);
                                        lhu(v0, s3, dat_unit::kFlags);
                                        v0 = v0 & dat_unit::kFlagEnemy;
                                        if (v0 == 0) {
                                            // 0x0030a418
                                            charge(ctx, 4);
                                            lhu(a0, s3, dat_unit::kId);
                                            a1 = 116;
                                            jal(ctx, 0x30A420u, gen::fn_sub_300750_00300750);
                                        } else {
                                            // 0x0030a40c
                                            charge(ctx, 3);
                                            v0 = 0;
                                        }
                                        // 0x0030a428
                                        charge(ctx, 2);
                                        if (v0 != 0) {
                                            // 0x0030a430
                                            charge(ctx, 1);
                                            s2 = addiu(s2, 10);
                                        }
                                        // 0x0030a434
                                        charge(ctx, 4);
                                        lhu(v0, s3, dat_unit::kFlags);
                                        v0 = v0 & dat_unit::kFlagEnemy;
                                        if (v0 == 0) {
                                            // 0x0030a450
                                            charge(ctx, 4);
                                            lhu(a0, s3, dat_unit::kId);
                                            a1 = 117;
                                            jal(ctx, 0x30A458u, gen::fn_sub_300750_00300750);
                                        } else {
                                            // 0x0030a444
                                            charge(ctx, 3);
                                            v0 = 0;
                                        }
                                        // 0x0030a460
                                        charge(ctx, 2);
                                        if (v0 != 0) {
                                            // 0x0030a468
                                            charge(ctx, 3);
                                            s2 = addiu(s2, 15);
                                        }
                                        break;
                                    case 0x30A474u:  // table[4]
                                        // 0x0030a474
                                        charge(ctx, 4);
                                        lhu(v0, s3, dat_unit::kFlags);
                                        v0 = v0 & dat_unit::kFlagEnemy;
                                        if (v0 == 0) {
                                            // 0x0030a490
                                            charge(ctx, 4);
                                            lhu(a0, s3, dat_unit::kId);
                                            a1 = 118;
                                            jal(ctx, 0x30A498u, gen::fn_sub_300750_00300750);
                                        } else {
                                            // 0x0030a484
                                            charge(ctx, 3);
                                            v0 = 0;
                                        }
                                        // 0x0030a4a0
                                        charge(ctx, 2);
                                        if (v0 != 0) {
                                            // 0x0030a4a8
                                            charge(ctx, 1);
                                            s2 = addiu(s2, 5);
                                        }
                                        // 0x0030a4ac
                                        charge(ctx, 4);
                                        lhu(v0, s3, dat_unit::kFlags);
                                        v0 = v0 & dat_unit::kFlagEnemy;
                                        if (v0 == 0) {
                                            // 0x0030a4c8
                                            charge(ctx, 4);
                                            lhu(a0, s3, dat_unit::kId);
                                            a1 = 119;
                                            jal(ctx, 0x30A4D0u, gen::fn_sub_300750_00300750);
                                        } else {
                                            // 0x0030a4bc
                                            charge(ctx, 3);
                                            v0 = 0;
                                        }
                                        // 0x0030a4d8
                                        charge(ctx, 2);
                                        if (v0 != 0) {
                                            // 0x0030a4e0
                                            charge(ctx, 1);
                                            s2 = addiu(s2, 10);
                                        }
                                        // 0x0030a4e4
                                        charge(ctx, 4);
                                        lhu(v0, s3, dat_unit::kFlags);
                                        v0 = v0 & dat_unit::kFlagEnemy;
                                        if (v0 == 0) {
                                            // 0x0030a500
                                            charge(ctx, 4);
                                            lhu(a0, s3, dat_unit::kId);
                                            a1 = 120;
                                            jal(ctx, 0x30A508u, gen::fn_sub_300750_00300750);
                                        } else {
                                            // 0x0030a4f4
                                            charge(ctx, 3);
                                            v0 = 0;
                                        }
                                        // 0x0030a510
                                        charge(ctx, 2);
                                        if (v0 != 0) {
                                            // 0x0030a518
                                            charge(ctx, 3);
                                            s2 = addiu(s2, 15);
                                        }
                                        break;
                                    case 0x30A524u:  // table[5]
                                        // 0x0030a524
                                        charge(ctx, 4);
                                        lhu(v0, s3, dat_unit::kFlags);
                                        v0 = v0 & dat_unit::kFlagEnemy;
                                        if (v0 == 0) {
                                            // 0x0030a540
                                            charge(ctx, 4);
                                            lhu(a0, s3, dat_unit::kId);
                                            a1 = 124;
                                            jal(ctx, 0x30A548u, gen::fn_sub_300750_00300750);
                                        } else {
                                            // 0x0030a534
                                            charge(ctx, 3);
                                            v0 = 0;
                                        }
                                        // 0x0030a550
                                        charge(ctx, 2);
                                        if (v0 != 0) {
                                            // 0x0030a558
                                            charge(ctx, 1);
                                            s2 = addiu(s2, 5);
                                        }
                                        // 0x0030a55c
                                        charge(ctx, 4);
                                        lhu(v0, s3, dat_unit::kFlags);
                                        v0 = v0 & dat_unit::kFlagEnemy;
                                        if (v0 == 0) {
                                            // 0x0030a578
                                            charge(ctx, 4);
                                            lhu(a0, s3, dat_unit::kId);
                                            a1 = 125;
                                            jal(ctx, 0x30A580u, gen::fn_sub_300750_00300750);
                                        } else {
                                            // 0x0030a56c
                                            charge(ctx, 3);
                                            v0 = 0;
                                        }
                                        // 0x0030a588
                                        charge(ctx, 2);
                                        if (v0 != 0) {
                                            // 0x0030a590
                                            charge(ctx, 1);
                                            s2 = addiu(s2, 10);
                                        }
                                        // 0x0030a594
                                        charge(ctx, 4);
                                        lhu(v0, s3, dat_unit::kFlags);
                                        v0 = v0 & dat_unit::kFlagEnemy;
                                        if (v0 == 0) {
                                            // 0x0030a5b0
                                            charge(ctx, 4);
                                            lhu(a0, s3, dat_unit::kId);
                                            a1 = 126;
                                            jal(ctx, 0x30A5B8u, gen::fn_sub_300750_00300750);
                                        } else {
                                            // 0x0030a5a4
                                            charge(ctx, 3);
                                            v0 = 0;
                                        }
                                        // 0x0030a5c0
                                        charge(ctx, 2);
                                        if (v0 != 0) {
                                            // 0x0030a5c8
                                            charge(ctx, 3);
                                            s2 = addiu(s2, 15);
                                        }
                                        break;
                                    case 0x30A5D4u:  // table[6]
                                        // 0x0030a5d4
                                        charge(ctx, 4);
                                        lhu(v0, s3, dat_unit::kFlags);
                                        v0 = v0 & dat_unit::kFlagEnemy;
                                        if (v0 == 0) {
                                            // 0x0030a5f0
                                            charge(ctx, 4);
                                            lhu(a0, s3, dat_unit::kId);
                                            a1 = 121;
                                            jal(ctx, 0x30A5F8u, gen::fn_sub_300750_00300750);
                                        } else {
                                            // 0x0030a5e4
                                            charge(ctx, 3);
                                            v0 = 0;
                                        }
                                        // 0x0030a600
                                        charge(ctx, 2);
                                        if (v0 != 0) {
                                            // 0x0030a608
                                            charge(ctx, 1);
                                            s2 = addiu(s2, 5);
                                        }
                                        // 0x0030a60c
                                        charge(ctx, 4);
                                        lhu(v0, s3, dat_unit::kFlags);
                                        v0 = v0 & dat_unit::kFlagEnemy;
                                        if (v0 == 0) {
                                            // 0x0030a628
                                            charge(ctx, 4);
                                            lhu(a0, s3, dat_unit::kId);
                                            a1 = 122;
                                            jal(ctx, 0x30A630u, gen::fn_sub_300750_00300750);
                                        } else {
                                            // 0x0030a61c
                                            charge(ctx, 3);
                                            v0 = 0;
                                        }
                                        // 0x0030a638
                                        charge(ctx, 2);
                                        if (v0 != 0) {
                                            // 0x0030a640
                                            charge(ctx, 1);
                                            s2 = addiu(s2, 10);
                                        }
                                        // 0x0030a644
                                        charge(ctx, 4);
                                        lhu(v0, s3, dat_unit::kFlags);
                                        v0 = v0 & dat_unit::kFlagEnemy;
                                        if (v0 == 0) {
                                            // 0x0030a660
                                            charge(ctx, 4);
                                            lhu(a0, s3, dat_unit::kId);
                                            a1 = 123;
                                            jal(ctx, 0x30A668u, gen::fn_sub_300750_00300750);
                                        } else {
                                            // 0x0030a654
                                            charge(ctx, 3);
                                            v0 = 0;
                                        }
                                        // 0x0030a670
                                        charge(ctx, 2);
                                        if (v0 != 0) {
                                            // 0x0030a678
                                            charge(ctx, 1);
                                            s2 = addiu(s2, 15);
                                        }
                                        break;
                                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                                        tail(ctx, v0.u());
                                        return;
                                    }
                                }
                            }
                            // 0x0030a67c
                            charge(ctx, 14);
                            mtc1(s4, f0);
                            cvt_s_w(f0, f0);
                            mul_s(f0, f0, f22);
                            mul_s(f0, f23, f0);
                            mul_s(f0, f21, f0);
                            mul_s(f0, f20, f0);
                            cvt_w_s(f0, f0);
                            mfc1(v0, f0);
                            s0 = subu(v0, s2);
                            at = slti(s0, 100);
                            if (at != 0) {
                                // 0x0030a6c0
                                charge(ctx, 3);
                                at = slti(s0, 50);
                                if (at != 0) {
                                    // 0x0030a6cc
                                    charge(ctx, 1);
                                    s0 = 50;
                                }
                            } else {
                                // 0x0030a6b4
                                charge(ctx, 3);
                                s0 = 99;
                            }
                            // 0x0030a6d0
                            charge(ctx, 6);
                            a0 = 100;
                            jal(ctx, 0x30A6D4u, gen::fn_datCalcRand_002ffbc0);
                            v0 = slt(v0, s0);
                            if (v0 != 0) {
                                // 0x0030a6f8
                                charge(ctx, 1);
                                v0 = 1;
                            } else {
                                // 0x0030a6e8
                                charge(ctx, 4);
                                sh(s1, s3, dat_unit::kMessageId);
                                v0 = 4;
                            }
                            // 0x0030a6fc: epilogue
                            charge(ctx, 17);
                            ld(ra, sp, 0xA0);
                            lq(fp, sp, 0x90);
                            lq(s7, sp, 0x80);
                            lq(s6, sp, 0x70);
                            lq(s5, sp, 0x60);
                            lq(s4, sp, 0x50);
                            lq(s3, sp, 0x40);
                            lq(s2, sp, 0x30);
                            lq(s1, sp, 0x20);
                            lq(s0, sp, 0x10);
                            lwc1(f23, sp, 0xC);
                            lwc1(f22, sp, 0x8);
                            lwc1(f21, sp, 0x4);
                            lwc1(f20, sp, 0x0);
                            sp = addiu(sp, 0xC0);
                            return;
                        }
                    L_003099e8:
                        charge(ctx, 3);
                        v0 = 1;
                    } else {
                        // 0x0030999c
                        charge(ctx, 3);
                        v0 = 1;
                    }
                } else {
                    // 0x00309980
                    charge(ctx, 3);
                    v0 = 1;
                }
            } else {
                // 0x00309968
                charge(ctx, 3);
                v0 = 1;
            }
        } else {
            // 0x00309944
            charge(ctx, 3);
            v0 = 4;
        }
    }
    // 0x0030a6fc: epilogue
    charge(ctx, 17);
    ld(ra, sp, 0xA0);
    lq(fp, sp, 0x90);
    lq(s7, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xC0);
}

// ================================================================================================================
// 0x303130 datCalcDamage(skill, attacker, target, hits, result, kind, flags, hp_or_sp)
// ================================================================================================================

// 0x00303130 datCalcDamage -- 10304 bytes; frame 0x110: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// The HP (hp_or_sp 1) or SP (2) change one skill makes (21_battle.md section 5.2): the base value by the skill's
// formula (SkillRecord +17/+20 with base +18/+22, the target's current and maximum value), then for the formula
// kinds the multiplier chains (unless `flags` bit 0), and the hit result: 1024 turns damage into recovery, 4 / 2 /
// 256 zero both. Returns the recovery, or -damage. An hp_or_sp other than 1/2 (K_Assert line 1763) leaves the
// formula to whatever the frame slot holds and the base / bonus to the caller's $s6 / $s5, as the compiled code
// does. K_Assert lines 1731/1732 (skill >= 624 / 464), 1808/1881/1960/2071 (SkillRecord +2 neither 1 nor 2), 1936
// (formula >= 17), 2131/2203 (enemy id >= 336) and 2158/2163 (moon phase >= 30) are no-ops.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void datCalcDamage(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::addu, hg::charge, hg::cvt_s_w, hg::cvt_w_s, hg::div, hg::div_s,
          hg::divu, hg::dsll32, hg::dsra32, hg::enter, hg::i64, hg::jal, hg::lbu, hg::ld, hg::lh, hg::lhu, hg::lq,
          hg::lw, hg::lwc1, hg::mfc1, hg::mflo, hg::mov_s, hg::mtc1, hg::mul_s, hg::mult, hg::sb, hg::sd, hg::sh,
          hg::sll, hg::slt, hg::slti, hg::sltiu, hg::sltu, hg::sq, hg::srl, hg::subu, hg::sw, hg::swc1, hg::tail;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    // 0x00303130: prologue
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x110);
    sd(ra, sp, 0xA0);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    sh(a3, sp, 0x10E);
    sh(t0, sp, 0x10C);
    sh(t1, sp, 0x10A);
    sw(t2, sp, 0x104);
    sb(t3, sp, 0x103);
    s0 = s4 & 0xFFFF;
    if (i64(s0) >= 0) {
        // 0x00303198
        charge(ctx, 3);
        v0 = slti(s0, 624);
        if (v0 == 0) {
            goto L_003031a4;
        }
        goto L_003031b8;
    }
L_003031a4:
    charge(ctx, 5);
    k_assert(a0, a1, 0x3031B0u, kDatCalcFile, 1731);
L_003031b8:
    charge(ctx, 3);
    v0 = slti(s0, btl::kSkillCount);
    if (v0 == 0) {
        // 0x003031c4
        charge(ctx, 5);
        k_assert(a0, a1, 0x3031D0u, kDatCalcFile, 1732);
    }
    // 0x003031d8
    charge(ctx, 16);
    v0 = flt(1.0f);
    mtc1(v0, f23);
    mov_s(f22, f23);
    mov_s(f21, f23);
    mov_s(f20, f23);
    s1 = 0;
    s0 = 0;
    fp = 0;
    sh(zero, sp, 0xE0);
    s7 = 1;
    lbu(v0, sp, 0x103);
    v1 = v0;
    v0 = 2;
    if (v1 == v0) {
        // 0x00303274
        charge(ctx, 19);
        v1 = s4 & 0xFFFF;
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 1);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);  // * 44 (SkillRecord)
        lw(v0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
        v0 = addu(v1, v0);
        lh(s6, v0, 22);
        lbu(v0, v0, 20);
        sh(v0, sp, 0xF0);
        s5 = 0;
        lhu(fp, s2, dat_unit::kSp);
        a0 = s2;
        jal(ctx, 0x3032ACu, gen::fn_datCalcGetMaxSp_00300100);
        sh(v0, sp, 0xE0);
    } else {
        // 0x00303218
        charge(ctx, 2);
        if (v1 == s7) {
            // 0x00303228
            charge(ctx, 19);
            v1 = s4 & 0xFFFF;
            v0 = sll(v1, 2);
            v0 = addu(v0, v1);
            v0 = sll(v0, 1);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);  // * 44 (SkillRecord)
            lw(v0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
            v0 = addu(v1, v0);
            lh(s6, v0, 18);
            lbu(v0, v0, 17);
            sh(v0, sp, 0xF0);
            s5 = 0;
            lhu(fp, s2, dat_unit::kHp);
            a0 = s2;
            jal(ctx, 0x303260u, gen::fn_datCalcGetMaxHp_002ffdf0);
            sh(v0, sp, 0xE0);
        } else {
            // 0x00303220
            charge(ctx, 2);
            // 0x003032c0
            charge(ctx, 5);
            k_assert(a0, a1, 0x3032CCu, kDatCalcFile, 1763);
        }
    }
    // 0x003032d4
    charge(ctx, 6);
    lhu(v0, sp, 0xF0);
    // daddu v0: a 64-bit move to itself (no effect)
    sq(v0, sp, 0xD0);
    at = sltiu(v0, 17);
    if (at == 0) {
        // 0x00303754
        charge(ctx, 5);
        k_assert(a0, a1, 0x303760u, kDatCalcFile, 1936);
    } else {
        // 0x003032ec
        charge(ctx, 7);
        v1 = hi(0x7B8F20u);
        v1 = addiu(v1, lo(0x7B8F20u));  // "h70"
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x303308u:  // table[5]
            // 0x00303308
            charge(ctx, 7);
            v1 = dsll32(s6, 16);
            v1 = dsra32(v1, 16);
            v0 = dsll32(s5, 16);
            v0 = dsra32(v0, 16);
            s1 = addu(v1, v0);
            break;
        case 0x303324u:  // table[15]
            // 0x00303324
            charge(ctx, 9);
            a0 = dsll32(s6, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x30332Cu, gen::fn_datCalcRand_002ffbc0);
            v1 = dsll32(s5, 16);
            v1 = dsra32(v1, 16);
            s1 = addu(v0, v1);
            break;
        case 0x303348u:  // table[9]
            // 0x00303348
            charge(ctx, 12);
            v1 = fp & 0xFFFF;
            v0 = dsll32(s6, 16);
            v0 = dsra32(v0, 16);
            mult(v1, v1, v0);
            v0 = 100;
            div(v1, v0);
            mflo(v1);
            v0 = dsll32(s5, 16);
            v0 = dsra32(v0, 16);
            s1 = addu(v1, v0);
            if (i64(s1) <= 0) {
                // 0x00303378
                charge(ctx, 3);
                s1 = 1;
            }
            break;
        case 0x303384u:  // table[11]
            // 0x00303384
            charge(ctx, 13);
            lhu(v0, sp, 0xE0);
            v1 = v0;
            v0 = dsll32(s6, 16);
            v0 = dsra32(v0, 16);
            mult(v1, v1, v0);
            v0 = 100;
            div(v1, v0);
            mflo(v1);
            v0 = dsll32(s5, 16);
            v0 = dsra32(v0, 16);
            s1 = addu(v1, v0);
            if (i64(s1) <= 0) {
                // 0x003033b8
                charge(ctx, 3);
                s1 = 1;
            }
            break;
        case 0x3033C4u:  // table[2]
            // 0x003033c4
            charge(ctx, 12);
            lw(a0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
            v1 = s4 & 0xFFFF;
            v0 = sll(v1, 2);
            v0 = addu(v0, v1);
            v0 = sll(v0, 1);
            v0 = addu(v0, v1);
            v0 = sll(v0, 2);  // * 44 (SkillRecord)
            v0 = addu(v0, a0);
            lbu(v1, v0, 2);
            v0 = 2;
            if (v1 == v0) {
                // 0x00303430
                charge(ctx, 11);
                lbu(v0, sp, 0x103);
                t0 = v0;
                a0 = 3;
                a1 = s3;
                a2 = s2;
                a3 = s4;
                jal(ctx, 0x303448u, gen::fn_datScriptCalc_0030fc40);
                s1 = v0;
            } else {
                // 0x003033f4
                charge(ctx, 3);
                a0 = 1;
                if (v1 == a0) {
                    // 0x00303408
                    charge(ctx, 10);
                    lbu(v0, sp, 0x103);
                    t0 = v0;
                    a1 = s3;
                    a2 = s2;
                    a3 = s4;
                    jal(ctx, 0x30341Cu, gen::fn_datScriptCalc_0030fc40);
                    s1 = v0;
                } else {
                    // 0x00303400
                    charge(ctx, 2);
                    // 0x0030345c
                    charge(ctx, 5);
                    k_assert(a0, a1, 0x303468u, kDatCalcFile, 1808);
                }
            }
            // 0x00303470
            charge(ctx, 5);
            v0 = dsll32(s5, 16);
            v0 = dsra32(v0, 16);
            s1 = addu(s1, v0);
            if (i64(s1) <= 0) {
                // 0x00303484
                charge(ctx, 1);
                s1 = 1;
            }
            // 0x00303488
            charge(ctx, 3);
            s7 = 0;
            break;
        case 0x303494u:  // table[7]
            // 0x00303494
            charge(ctx, 6);
            v1 = 50;
            v0 = dsll32(s5, 16);
            v0 = dsra32(v0, 16);
            s1 = addu(v1, v0);
            if (i64(s1) <= 0) {
                // 0x003034ac
                charge(ctx, 1);
                s1 = 1;
            }
            // 0x003034b0
            charge(ctx, 3);
            s7 = 0;
            break;
        case 0x3034BCu:  // table[4, 13]
            // 0x003034bc
            charge(ctx, 9);
            v1 = dsll32(s6, 16);
            v1 = dsra32(v1, 16);
            v0 = dsll32(s5, 16);
            v0 = dsra32(v0, 16);
            s0 = addu(v1, v0);
            v1 = 13;
            lq(v0, sp, 0xD0);
            if (v0 == v1) {
                // 0x003034e0
                charge(ctx, 4);
                v0 = fp & 0xFFFF;
                at = slt(v0, s0);
                if (at != 0) {
                    // 0x003034f0
                    charge(ctx, 3);
                    s0 = v0;
                }
            }
            break;
        case 0x3034FCu:  // table[8]
            // 0x003034fc
            charge(ctx, 12);
            a0 = dsll32(s6, 16);
            a0 = dsra32(a0, 16);
            v0 = fp & 0xFFFF;
            mult(v1, v0, a0);
            v0 = 100;
            div(v1, v0);
            mflo(v1);
            v0 = dsll32(s5, 16);
            v0 = dsra32(v0, 16);
            s0 = addu(v1, v0);
            if (i64(s0) <= 0) {
                // 0x0030352c
                charge(ctx, 2);
                if (i64(a0) > 0) {
                    // 0x00303534
                    charge(ctx, 3);
                    s0 = 1;
                }
            }
            break;
        case 0x303540u:  // table[10]
            // 0x00303540
            charge(ctx, 13);
            a0 = dsll32(s6, 16);
            a0 = dsra32(a0, 16);
            lhu(v0, sp, 0xE0);
            // daddu v0: a 64-bit move to itself (no effect)
            mult(v1, v0, a0);
            v0 = 100;
            div(v1, v0);
            mflo(v1);
            v0 = dsll32(s5, 16);
            v0 = dsra32(v0, 16);
            s0 = addu(v1, v0);
            if (i64(s0) <= 0) {
                // 0x00303574
                charge(ctx, 2);
                if (i64(a0) > 0) {
                    // 0x0030357c
                    charge(ctx, 3);
                    s0 = 1;
                }
            }
            break;
        case 0x303588u:  // table[1, 12, 14]
            // 0x00303588
            charge(ctx, 12);
            lw(a0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
            v1 = s4 & 0xFFFF;
            v0 = sll(v1, 2);
            v0 = addu(v0, v1);
            v0 = sll(v0, 1);
            v0 = addu(v0, v1);
            v0 = sll(v0, 2);  // * 44 (SkillRecord)
            v0 = addu(v0, a0);
            lbu(v0, v0, 2);
            a0 = 2;
            if (v0 == a0) {
                // 0x003035f4
                charge(ctx, 10);
                lbu(v0, sp, 0x103);
                t0 = v0;
                a1 = s3;
                a2 = s2;
                a3 = s4;
                jal(ctx, 0x303608u, gen::fn_datScriptCalc_0030fc40);
                s0 = v0;
            } else {
                // 0x003035b8
                charge(ctx, 3);
                a0 = 1;
                if (v0 == a0) {
                    // 0x003035cc
                    charge(ctx, 10);
                    lbu(v0, sp, 0x103);
                    t0 = v0;
                    a1 = s3;
                    a2 = s2;
                    a3 = s4;
                    jal(ctx, 0x3035E0u, gen::fn_datScriptCalc_0030fc40);
                    s0 = v0;
                } else {
                    // 0x003035c4
                    charge(ctx, 2);
                    // 0x0030361c
                    charge(ctx, 5);
                    k_assert(a0, a1, 0x303628u, kDatCalcFile, 1881);
                }
            }
            // 0x00303630
            charge(ctx, 7);
            v0 = dsll32(s5, 16);
            v0 = dsra32(v0, 16);
            s0 = addu(s0, v0);
            v1 = 13;
            lq(v0, sp, 0xD0);
            if (v0 != v1) {
                // 0x0030364c
                charge(ctx, 3);
                v1 = 12;
                if (v0 == v1) {
                    goto L_00303660;
                }
                // 0x00303658
                charge(ctx, 2);
                goto L_00303674;
            }
        L_00303660:
            charge(ctx, 4);
            v0 = fp & 0xFFFF;
            at = slt(v0, s0);
            if (at != 0) {
                // 0x00303670
                charge(ctx, 1);
                s0 = v0;
            }
        L_00303674:
            charge(ctx, 4);
            v1 = 14;
            lq(v0, sp, 0xD0);
            if (v0 == v1) {
                // 0x00303684
                charge(ctx, 5);
                lhu(v0, sp, 0x10E);
                // daddu v0: a 64-bit move to itself (no effect)
                at = slti(v0, 2);
                if (at == 0) {
                    // 0x00303698
                    charge(ctx, 2);
                    div(s0, v0);
                    mflo(s0);
                }
            }
            // 0x003036a0
            charge(ctx, 2);
            if (i64(s0) <= 0) {
                // 0x003036a8
                charge(ctx, 1);
                s0 = 1;
            }
            // 0x003036ac
            charge(ctx, 3);
            s7 = 0;
            break;
        case 0x3036B8u:  // table[6]
            // 0x003036b8
            charge(ctx, 6);
            v1 = 50;
            v0 = dsll32(s5, 16);
            v0 = dsra32(v0, 16);
            s0 = addu(v1, v0);
            if (i64(s0) <= 0) {
                // 0x003036d0
                charge(ctx, 1);
                s0 = 1;
            }
            // 0x003036d4
            charge(ctx, 3);
            s7 = 0;
            break;
        case 0x3036E0u:  // table[3]
            // 0x003036e0
            charge(ctx, 9);
            v1 = dsll32(s5, 16);
            v1 = dsra32(v1, 16);
            v0 = dsll32(s6, 16);
            v0 = dsra32(v0, 16);
            v1 = addu(v0, v1);
            v0 = fp & 0xFFFF;
            at = slt(v1, v0);
            if (at != 0) {
                // 0x00303704
                charge(ctx, 3);
                s0 = subu(v0, v1);
            }
            break;
        case 0x303710u:  // table[16]
            // 0x00303710
            charge(ctx, 13);
            lbu(v0, sp, 0x103);
            t0 = v0;
            a0 = 15;
            a1 = s3;
            a2 = s2;
            a3 = s4;
            jal(ctx, 0x303728u, gen::fn_datScriptCalc_0030fc40);
            v1 = dsll32(s5, 16);
            v1 = dsra32(v1, 16);
            s0 = addu(v0, v1);
            if (i64(s0) <= 0) {
                // 0x00303744
                charge(ctx, 1);
                s0 = 1;
            }
            // 0x00303748
            charge(ctx, 3);
            s7 = 0;
            break;
        case 0x303768u:  // table[0]
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
    }
    // 0x00303768
    charge(ctx, 2);
    if (s7 == 0) {
        // 0x00303770
        charge(ctx, 2);
        if (i64(s0) > 0) {
            // 0x00303778
            charge(ctx, 4);
            lw(v0, sp, 0x104);
            v0 = v0 & 0x1;
            if (v0 == 0) {
                // 0x00303788
                charge(ctx, 18);
                a0 = s3;
                a1 = s4;
                jal(ctx, 0x303790u, gen::fn_datCalcGetSkillElement_003082f0);
                s5 = dsll32(v0, 16);
                s5 = dsra32(s5, 16);
                v1 = s4 & 0xFFFF;
                v0 = sll(v1, 2);
                v0 = addu(v0, v1);
                v0 = sll(v0, 1);
                v0 = addu(v0, v1);
                s6 = sll(v0, 2);  // * 44 (SkillRecord)
                lw(v0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
                v0 = addu(s6, v0);
                lbu(v1, v0, 2);
                v0 = 2;
                if (v1 == v0) {
                    // 0x0030382c
                    charge(ctx, 18);
                    a0 = s3;
                    a1 = 1;
                    a2 = s4;
                    jal(ctx, 0x303838u, gen::fn_datCalcGetEffectMultiplier_00301880);
                    mov_s(f23, f0);
                    a0 = s2;
                    a1 = 3;
                    a2 = s4;
                    jal(ctx, 0x303850u, gen::fn_datCalcGetEffectMultiplier_00301880);
                    mov_s(f22, f0);
                    lw(v1, s3, dat_unit::kUnk18);
                    v0 = 0x100000;
                    v0 = v1 | v0;
                    sw(v0, s3, dat_unit::kUnk18);
                } else {
                    // 0x003037d0
                    charge(ctx, 3);
                    v0 = 1;
                    if (v1 == v0) {
                        // 0x003037e4
                        charge(ctx, 18);
                        a0 = s3;
                        a1 = 0;
                        a2 = s4;
                        jal(ctx, 0x3037F0u, gen::fn_datCalcGetEffectMultiplier_00301880);
                        mov_s(f23, f0);
                        a0 = s2;
                        a1 = 3;
                        a2 = s4;
                        jal(ctx, 0x303808u, gen::fn_datCalcGetEffectMultiplier_00301880);
                        mov_s(f22, f0);
                        lw(v1, s3, dat_unit::kUnk18);
                        v0 = 0x80000;
                        v0 = v1 | v0;
                        sw(v0, s3, dat_unit::kUnk18);
                    } else {
                        // 0x003037dc
                        charge(ctx, 2);
                        // 0x00303874
                        charge(ctx, 5);
                        k_assert(a0, a1, 0x303880u, kDatCalcFile, 1960);
                    }
                }
                // 0x00303888
                charge(ctx, 5);
                s5 = dsll32(s5, 16);
                s5 = dsra32(s5, 16);
                v0 = 6;
                if (s5 == v0) {
                    // 0x00303a78
                    charge(ctx, 6);
                    a0 = s3;
                    a1 = 534;
                    jal(ctx, 0x303A80u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 == 0) {
                        // 0x00303a90
                        charge(ctx, 4);
                        lhu(v0, s3, dat_unit::kFlags);
                        v0 = v0 & dat_unit::kFlagEnemy;
                        if (v0 == 0) {
                            // 0x00303aac
                            charge(ctx, 4);
                            lhu(a0, s3, dat_unit::kId);
                            a1 = 176;
                            jal(ctx, 0x303AB4u, gen::fn_sub_300870_00300870);
                        } else {
                            // 0x00303aa0
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x00303abc
                        charge(ctx, 3);
                        v0 = v0 & 0xFFFF;
                        if (v0 != 0) {
                            goto L_00303ac8;
                        }
                        goto L_00303ad8;
                    }
                L_00303ac8:
                    charge(ctx, 4);
                    v0 = flt(1.25f);
                    mtc1(v0, f0);
                    mul_s(f20, f20, f0);
                L_00303ad8:
                    charge(ctx, 6);
                    a0 = s3;
                    a1 = 535;
                    jal(ctx, 0x303AE0u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00303af0
                        charge(ctx, 4);
                        v0 = flt(1.5f);
                        mtc1(v0, f0);
                        mul_s(f20, f20, f0);
                    }
                } else {
                    // 0x0030389c
                    charge(ctx, 3);
                    v0 = 5;
                    if (s5 == v0) {
                        // 0x003039e8
                        charge(ctx, 6);
                        a0 = s3;
                        a1 = 532;
                        jal(ctx, 0x3039F0u, gen::fn_datCalcHasSkill_003005e0);
                        if (v0 == 0) {
                            // 0x00303a00
                            charge(ctx, 4);
                            lhu(v0, s3, dat_unit::kFlags);
                            v0 = v0 & dat_unit::kFlagEnemy;
                            if (v0 == 0) {
                                // 0x00303a1c
                                charge(ctx, 4);
                                lhu(a0, s3, dat_unit::kId);
                                a1 = 175;
                                jal(ctx, 0x303A24u, gen::fn_sub_300870_00300870);
                            } else {
                                // 0x00303a10
                                charge(ctx, 3);
                                v0 = 0;
                            }
                            // 0x00303a2c
                            charge(ctx, 3);
                            v0 = v0 & 0xFFFF;
                            if (v0 != 0) {
                                goto L_00303a38;
                            }
                            goto L_00303a48;
                        }
                    L_00303a38:
                        charge(ctx, 4);
                        v0 = flt(1.25f);
                        mtc1(v0, f0);
                        mul_s(f20, f20, f0);
                    L_00303a48:
                        charge(ctx, 6);
                        a0 = s3;
                        a1 = 533;
                        jal(ctx, 0x303A50u, gen::fn_datCalcHasSkill_003005e0);
                        if (v0 != 0) {
                            // 0x00303a60
                            charge(ctx, 6);
                            v0 = flt(1.5f);
                            mtc1(v0, f0);
                            mul_s(f20, f20, f0);
                        }
                    } else {
                        // 0x003038a8
                        charge(ctx, 3);
                        v0 = 4;
                        if (s5 == v0) {
                            // 0x00303958
                            charge(ctx, 6);
                            a0 = s3;
                            a1 = 530;
                            jal(ctx, 0x303960u, gen::fn_datCalcHasSkill_003005e0);
                            if (v0 == 0) {
                                // 0x00303970
                                charge(ctx, 4);
                                lhu(v0, s3, dat_unit::kFlags);
                                v0 = v0 & dat_unit::kFlagEnemy;
                                if (v0 == 0) {
                                    // 0x0030398c
                                    charge(ctx, 4);
                                    lhu(a0, s3, dat_unit::kId);
                                    a1 = 174;
                                    jal(ctx, 0x303994u, gen::fn_sub_300870_00300870);
                                } else {
                                    // 0x00303980
                                    charge(ctx, 3);
                                    v0 = 0;
                                }
                                // 0x0030399c
                                charge(ctx, 3);
                                v0 = v0 & 0xFFFF;
                                if (v0 != 0) {
                                    goto L_003039a8;
                                }
                                goto L_003039b8;
                            }
                        L_003039a8:
                            charge(ctx, 4);
                            v0 = flt(1.25f);
                            mtc1(v0, f0);
                            mul_s(f20, f20, f0);
                        L_003039b8:
                            charge(ctx, 6);
                            a0 = s3;
                            a1 = 531;
                            jal(ctx, 0x3039C0u, gen::fn_datCalcHasSkill_003005e0);
                            if (v0 != 0) {
                                // 0x003039d0
                                charge(ctx, 6);
                                v0 = flt(1.5f);
                                mtc1(v0, f0);
                                mul_s(f20, f20, f0);
                            }
                        } else {
                            // 0x003038b4
                            charge(ctx, 3);
                            v0 = 3;
                            if (s5 == v0) {
                                // 0x003038c8
                                charge(ctx, 6);
                                a0 = s3;
                                a1 = 528;
                                jal(ctx, 0x3038D0u, gen::fn_datCalcHasSkill_003005e0);
                                if (v0 == 0) {
                                    // 0x003038e0
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x003038fc
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 173;
                                        jal(ctx, 0x303904u, gen::fn_sub_300870_00300870);
                                    } else {
                                        // 0x003038f0
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x0030390c
                                    charge(ctx, 3);
                                    v0 = v0 & 0xFFFF;
                                    if (v0 != 0) {
                                        goto L_00303918;
                                    }
                                    goto L_00303928;
                                }
                            L_00303918:
                                charge(ctx, 4);
                                v0 = flt(1.25f);
                                mtc1(v0, f0);
                                mul_s(f20, f20, f0);
                            L_00303928:
                                charge(ctx, 6);
                                a0 = s3;
                                a1 = 529;
                                jal(ctx, 0x303930u, gen::fn_datCalcHasSkill_003005e0);
                                if (v0 != 0) {
                                    // 0x00303940
                                    charge(ctx, 6);
                                    v0 = flt(1.5f);
                                    mtc1(v0, f0);
                                    mul_s(f20, f20, f0);
                                }
                            } else {
                                // 0x003038c0
                                charge(ctx, 2);
                            }
                        }
                    }
                }
                // 0x00303b00
                charge(ctx, 5);
                lw(v0, s3, dat_unit::kStatus);
                v0 = v0 & 0x10;
                v0 = sltu(0, v0);
                if (v0 != 0) {
                    // 0x00303b14
                    charge(ctx, 6);
                    a0 = s3;
                    a1 = 543;
                    jal(ctx, 0x303B1Cu, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00303b2c
                        charge(ctx, 6);
                        v0 = 4639;
                        sh(v0, s3, dat_unit::kMessageId);
                        v0 = flt(2.0f);
                        mtc1(v0, f0);
                        mul_s(f20, f20, f0);
                    }
                }
                // 0x00303b44
                charge(ctx, 5);
                a0 = s4;
                jal(ctx, 0x303B48u, gen::fn_datCalcIsPhysicalSkill_003088b0);
                if (v0 != 0) {
                    // 0x00303b58
                    charge(ctx, 4);
                    lhu(v0, s3, dat_unit::kFlags);
                    v0 = v0 & dat_unit::kFlagEnemy;
                    if (v0 == 0) {
                        // 0x00303b68
                        charge(ctx, 7);
                        a0 = s3;
                        jal(ctx, 0x303B6Cu, gen::fn_datCalcGetHeldWeaponType_00308c60);
                        v0 = v0 & 0xFF;
                        at = sltiu(v0, 8);
                        if (at != 0) {
                            // 0x00303b84
                            charge(ctx, 7);
                            v1 = hi(0x7B8F00u);
                            v1 = addiu(v1, lo(0x7B8F00u));  // &0x7B8F00
                            v0 = sll(v0, 2);
                            v0 = addu(v0, v1);
                            lw(v0, v0, 0);
                            switch (v0.u()) {
                            case 0x303BA0u:  // table[0]
                                // 0x00303ba0
                                charge(ctx, 6);
                                a0 = s3;
                                a1 = 584;
                                jal(ctx, 0x303BA8u, gen::fn_datCalcHasSkill_003005e0);
                                if (v0 != 0) {
                                    // 0x00303bb8
                                    charge(ctx, 6);
                                    v0 = flt(1.25f);
                                    mtc1(v0, f0);
                                    mul_s(f20, f20, f0);
                                }
                                break;
                            case 0x303BD0u:  // table[1]
                                // 0x00303bd0
                                charge(ctx, 6);
                                a0 = s3;
                                a1 = 585;
                                jal(ctx, 0x303BD8u, gen::fn_datCalcHasSkill_003005e0);
                                if (v0 != 0) {
                                    // 0x00303be8
                                    charge(ctx, 6);
                                    v0 = flt(1.25f);
                                    mtc1(v0, f0);
                                    mul_s(f20, f20, f0);
                                }
                                break;
                            case 0x303C00u:  // table[2]
                                // 0x00303c00
                                charge(ctx, 6);
                                a0 = s3;
                                a1 = 573;
                                jal(ctx, 0x303C08u, gen::fn_datCalcHasSkill_003005e0);
                                if (v0 != 0) {
                                    // 0x00303c18
                                    charge(ctx, 6);
                                    v0 = flt(1.25f);
                                    mtc1(v0, f0);
                                    mul_s(f20, f20, f0);
                                }
                                break;
                            case 0x303C30u:  // table[3]
                                // 0x00303c30
                                charge(ctx, 6);
                                a0 = s3;
                                a1 = 586;
                                jal(ctx, 0x303C38u, gen::fn_datCalcHasSkill_003005e0);
                                if (v0 != 0) {
                                    // 0x00303c48
                                    charge(ctx, 6);
                                    v0 = flt(1.25f);
                                    mtc1(v0, f0);
                                    mul_s(f20, f20, f0);
                                }
                                break;
                            case 0x303C60u:  // table[4]
                                // 0x00303c60
                                charge(ctx, 6);
                                a0 = s3;
                                a1 = 582;
                                jal(ctx, 0x303C68u, gen::fn_datCalcHasSkill_003005e0);
                                if (v0 != 0) {
                                    // 0x00303c78
                                    charge(ctx, 6);
                                    v0 = flt(1.25f);
                                    mtc1(v0, f0);
                                    mul_s(f20, f20, f0);
                                }
                                break;
                            case 0x303C90u:  // table[6]
                                // 0x00303c90
                                charge(ctx, 6);
                                a0 = s3;
                                a1 = 583;
                                jal(ctx, 0x303C98u, gen::fn_datCalcHasSkill_003005e0);
                                if (v0 != 0) {
                                    // 0x00303ca8
                                    charge(ctx, 4);
                                    v0 = flt(1.25f);
                                    mtc1(v0, f0);
                                    mul_s(f20, f20, f0);
                                }
                                break;
                            case 0x303CB8u:  // table[5, 7]
                                break;
                            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                                tail(ctx, v0.u());
                                return;
                            }
                        }
                    }
                }
                // 0x00303cb8
                charge(ctx, 5);
                a0 = s4;
                jal(ctx, 0x303CBCu, gen::fn_datCalcIsPhysicalSkill_003088b0);
                if (v0 == 0) {
                    // 0x00303ccc
                    charge(ctx, 6);
                    lw(v0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
                    v0 = addu(s6, v0);
                    lbu(v1, v0, 2);
                    v0 = 2;
                    if (v1 == v0) {
                        // 0x00303d28
                        charge(ctx, 6);
                        a0 = s3;
                        a1 = 574;
                        jal(ctx, 0x303D30u, gen::fn_datCalcHasSkill_003005e0);
                        if (v0 != 0) {
                            // 0x00303d40
                            charge(ctx, 6);
                            v0 = flt(1.25f);
                            mtc1(v0, f0);
                            mul_s(f20, f20, f0);
                        }
                    } else {
                        // 0x00303ce4
                        charge(ctx, 3);
                        v0 = 1;
                        if (v1 == v0) {
                            // 0x00303cf8
                            charge(ctx, 6);
                            a0 = s3;
                            a1 = 575;
                            jal(ctx, 0x303D00u, gen::fn_datCalcHasSkill_003005e0);
                            if (v0 != 0) {
                                // 0x00303d10
                                charge(ctx, 6);
                                v0 = flt(1.25f);
                                mtc1(v0, f0);
                                mul_s(f20, f20, f0);
                            }
                        } else {
                            // 0x00303cf0
                            charge(ctx, 2);
                            // 0x00303d58
                            charge(ctx, 5);
                            k_assert(a0, a1, 0x303D64u, kDatCalcFile, 2071);
                        }
                    }
                }
                // 0x00303d6c
                charge(ctx, 6);
                a0 = s2;
                a1 = 564;
                jal(ctx, 0x303D74u, gen::fn_datCalcHasSkill_003005e0);
                if (v0 != 0) {
                    // 0x00303d84
                    charge(ctx, 4);
                    v0 = flt(0.5f);
                    mtc1(v0, f0);
                    mul_s(f20, f20, f0);
                }
                // 0x00303d94
                charge(ctx, 5);
                lw(v0, s3, dat_unit::kStatus);
                v0 = v0 & 0x100;
                v0 = sltu(0, v0);
                if (v0 != 0) {
                    // 0x00303da8
                    charge(ctx, 6);
                    jal(ctx, 0x303DA8u, gen::fn_sub_17D800_0017d800);
                    v0 = flt(1.5f);
                    mtc1(v0, f0);
                    mul_s(f21, f21, f0);
                }
                // 0x00303dc0
                charge(ctx, 5);
                lhu(v0, sp, 0x10A);
                fp = v0;
                v0 = 2;
                if (fp == v0) {
                    // 0x00303dd4
                    charge(ctx, 4);
                    lhu(v0, s3, dat_unit::kFlags);
                    v0 = v0 & dat_unit::kFlagEnemy;
                    if (v0 != 0) {
                        // 0x00303e00
                        charge(ctx, 7);
                        a0 = 4889;
                        jal(ctx, 0x303E04u, gen::fn_datGetFlag_0016f190);
                        v0 = sltu(0, v0);
                        v0 = v0 ^ 0x1;
                        if (v0 == 0) {
                            // 0x00303e28
                            charge(ctx, 1);
                            lwc1(f0, gp, gp_off(0x7CAF98u));  // 0x7CAF98
                        } else {
                            // 0x00303e1c
                            charge(ctx, 3);
                            lwc1(f0, gp, gp_off(0x7CAF94u));  // 0x7CAF94
                        }
                        // 0x00303e2c
                        charge(ctx, 1);
                        mul_s(f23, f23, f0);
                    } else {
                        // 0x00303de4
                        charge(ctx, 7);
                        a0 = 4889;
                        jal(ctx, 0x303DE8u, gen::fn_datGetFlag_0016f190);
                        lwc1(f0, gp, gp_off(0x7CAF94u));  // 0x7CAF94
                        mul_s(f23, f23, f0);
                    }
                }
                // 0x00303e30
                charge(ctx, 3);
                v0 = 8;
                if (fp == v0) {
                    // 0x00303e3c
                    charge(ctx, 7);
                    a0 = 4889;
                    jal(ctx, 0x303E40u, gen::fn_datGetFlag_0016f190);
                    v0 = flt(1.5f);
                    mtc1(v0, f0);
                    mul_s(f23, f23, f0);
                }
                // 0x00303e58
                charge(ctx, 5);
                lw(v0, s3, dat_unit::kStatus);
                v0 = v0 & 0x10;
                v0 = sltu(0, v0);
                if (v0 != 0) {
                    // 0x00303e6c
                    charge(ctx, 4);
                    v0 = flt(1.5f);
                    mtc1(v0, f0);
                    mul_s(f21, f21, f0);
                }
                // 0x00303e7c
                charge(ctx, 5);
                lw(v1, s2, dat_unit::kStatus);
                v0 = v1 & 0x10;
                v0 = sltu(0, v0);
                if (v0 != 0) {
                    // 0x00303e90
                    charge(ctx, 4);
                    v0 = flt(3.0f);
                    mtc1(v0, f0);
                    mul_s(f21, f21, f0);
                }
                // 0x00303ea0
                charge(ctx, 4);
                v0 = v1 & 0x2;
                v0 = sltu(0, v0);
                if (v0 != 0) {
                    // 0x00303eb0
                    charge(ctx, 7);
                    a0 = 4889;
                    jal(ctx, 0x303EB4u, gen::fn_datGetFlag_0016f190);
                    v0 = sltu(0, v0);
                    v0 = v0 ^ 0x1;
                    if (v0 == 0) {
                        // 0x00303ed8
                        charge(ctx, 2);
                        v0 = flt(1.5f);
                        mtc1(v0, f0);
                    } else {
                        // 0x00303ecc
                        charge(ctx, 3);
                        lwc1(f0, gp, gp_off(0x7CAD60u));  // 0x7CAD60
                    }
                    // 0x00303ee0
                    charge(ctx, 1);
                    mul_s(f21, f21, f0);
                }
                // 0x00303ee4
                charge(ctx, 5);
                lw(v1, s2, dat_unit::kStatus);
                v0 = v1 & 0x200;
                v0 = sltu(0, v0);
                if (v0 != 0) {
                    // 0x00303ef8
                    charge(ctx, 4);
                    v0 = flt(3.0f);
                    mtc1(v0, f0);
                    mul_s(f21, f21, f0);
                }
                // 0x00303f08
                charge(ctx, 5);
                v0 = 0x100000;
                v0 = v1 & v0;
                v0 = sltu(0, v0);
                if (v0 != 0) {
                    // 0x00303f1c
                    charge(ctx, 7);
                    a0 = 4889;
                    jal(ctx, 0x303F20u, gen::fn_datGetFlag_0016f190);
                    v0 = sltu(0, v0);
                    v0 = v0 ^ 0x1;
                    if (v0 == 0) {
                        // 0x00303f44
                        charge(ctx, 1);
                        lwc1(f0, gp, gp_off(0x7CAF9Cu));  // 0x7CAF9C
                    } else {
                        // 0x00303f38
                        charge(ctx, 3);
                        lwc1(f0, gp, gp_off(0x7CAD60u));  // 0x7CAD60
                    }
                    // 0x00303f48
                    charge(ctx, 1);
                    mul_s(f21, f21, f0);
                }
                // 0x00303f4c
                charge(ctx, 5);
                lw(v0, s2, dat_unit::kStatus);
                v0 = v0 & 0x100;
                v0 = sltu(0, v0);
                if (v0 != 0) {
                    // 0x00303f60
                    charge(ctx, 6);
                    jal(ctx, 0x303F60u, gen::fn_sub_17D800_0017d800);
                    v0 = flt(0.5f);
                    mtc1(v0, f0);
                    mul_s(f21, f21, f0);
                }
                // 0x00303f78
                charge(ctx, 4);
                lhu(v0, s3, dat_unit::kFlags);
                v0 = v0 & dat_unit::kFlagEnemy;
                if (v0 != 0) {
                    // 0x00303f88
                    charge(ctx, 4);
                    lhu(v0, s3, dat_unit::kId);
                    v0 = slti(v0, enemy_rec::kCount);
                    if (v0 == 0) {
                        // 0x00303f98
                        charge(ctx, 5);
                        k_assert(a0, a1, 0x303FA4u, kDatCalcFile, 2131);
                    }
                    // 0x00303fac
                    charge(ctx, 10);
                    lhu(v1, s3, dat_unit::kId);
                    v0 = sll(v1, 5);
                    v0 = subu(v0, v1);
                    v1 = sll(v0, 1);  // * 62 (EnemyRecord)
                    lw(v0, gp, gp_off(btl::kUnitTablePtr));  // gBtlEnemyTbl
                    v0 = addu(v0, v1);
                    lhu(v0, v0, 0);
                    v0 = v0 & 0x20;
                    if (v0 != 0) {
                        // 0x00303fd4
                        charge(ctx, 4);
                        v0 = flt(0.75f);
                        mtc1(v0, f0);
                        mul_s(f23, f23, f0);
                    }
                }
                // 0x00303fe4
                charge(ctx, 4);
                lhu(v0, s3, dat_unit::kFlags);
                v0 = v0 & dat_unit::kFlagEnemy;
                if (v0 == 0) {
                    // 0x00304000
                    charge(ctx, 3);
                    lh(a0, s3, dat_unit::kId);
                    jal(ctx, 0x304004u, gen::fn_sub_16C920_0016c920);
                } else {
                    // 0x00303ff4
                    charge(ctx, 3);
                    v0 = 0;
                }
                // 0x0030400c
                charge(ctx, 4);
                v1 = v0 & 0xFFFF;
                v0 = 3;
                if (v1 != v0) {
                    // 0x00304054
                    charge(ctx, 4);
                    lhu(v0, s3, dat_unit::kFlags);
                    v0 = v0 & dat_unit::kFlagEnemy;
                    if (v0 == 0) {
                        // 0x00304070
                        charge(ctx, 3);
                        lh(a0, s3, dat_unit::kId);
                        jal(ctx, 0x304074u, gen::fn_sub_16C920_0016c920);
                    } else {
                        // 0x00304064
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x0030407c
                    charge(ctx, 4);
                    v1 = v0 & 0xFFFF;
                    v0 = 5;
                    if (v1 == v0) {
                        // 0x0030408c
                        charge(ctx, 7);
                        a0 = 4889;
                        jal(ctx, 0x304090u, gen::fn_datGetFlag_0016f190);
                        v0 = sltu(0, v0);
                        v0 = v0 ^ 0x1;
                        if (v0 == 0) {
                            // 0x003040b4
                            charge(ctx, 2);
                            v0 = flt(0.5f);
                            mtc1(v0, f0);
                        } else {
                            // 0x003040a8
                            charge(ctx, 3);
                            lwc1(f0, gp, gp_off(ai::kLit0_80));  // 0x7CAD74
                        }
                        // 0x003040bc
                        charge(ctx, 1);
                        mul_s(f21, f21, f0);
                    }
                } else {
                    // 0x0030401c
                    charge(ctx, 7);
                    a0 = 4889;
                    jal(ctx, 0x304020u, gen::fn_datGetFlag_0016f190);
                    v0 = sltu(0, v0);
                    v0 = v0 ^ 0x1;
                    if (v0 == 0) {
                        // 0x00304044
                        charge(ctx, 1);
                        lwc1(f0, gp, gp_off(ai::kLit0_70));  // 0x7CADD0
                    } else {
                        // 0x00304038
                        charge(ctx, 3);
                        lwc1(f0, gp, gp_off(ai::kLit0_80));  // 0x7CAD74
                    }
                    // 0x00304048
                    charge(ctx, 3);
                    mul_s(f21, f21, f0);
                }
                // 0x003040c0
                charge(ctx, 4);
                lhu(v0, s2, dat_unit::kFlags);
                v0 = v0 & dat_unit::kFlagEnemy;
                if (v0 == 0) {
                    // 0x003040dc
                    charge(ctx, 3);
                    lh(a0, s2, dat_unit::kId);
                    jal(ctx, 0x3040E0u, gen::fn_sub_16C920_0016c920);
                } else {
                    // 0x003040d0
                    charge(ctx, 3);
                    v0 = 0;
                }
                // 0x003040e8
                charge(ctx, 4);
                v1 = v0 & 0xFFFF;
                v0 = 3;
                if (v1 != v0) {
                    // 0x00304134
                    charge(ctx, 4);
                    lhu(v0, s2, dat_unit::kFlags);
                    v0 = v0 & dat_unit::kFlagEnemy;
                    if (v0 == 0) {
                        // 0x00304150
                        charge(ctx, 3);
                        lh(a0, s2, dat_unit::kId);
                        jal(ctx, 0x304154u, gen::fn_sub_16C920_0016c920);
                    } else {
                        // 0x00304144
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x0030415c
                    charge(ctx, 4);
                    v1 = v0 & 0xFFFF;
                    v0 = 5;
                    if (v1 == v0) {
                        // 0x0030416c
                        charge(ctx, 7);
                        a0 = 4889;
                        jal(ctx, 0x304170u, gen::fn_datGetFlag_0016f190);
                        v0 = sltu(0, v0);
                        v0 = v0 ^ 0x1;
                        if (v0 == 0) {
                            // 0x00304198
                            charge(ctx, 2);
                            v0 = flt(2.0f);
                            mtc1(v0, f0);
                        } else {
                            // 0x00304188
                            charge(ctx, 4);
                            v0 = flt(1.5f);
                            mtc1(v0, f0);
                        }
                        // 0x003041a0
                        charge(ctx, 1);
                        mul_s(f21, f21, f0);
                    }
                } else {
                    // 0x003040f8
                    charge(ctx, 7);
                    a0 = 4889;
                    jal(ctx, 0x3040FCu, gen::fn_datGetFlag_0016f190);
                    v0 = sltu(0, v0);
                    v0 = v0 ^ 0x1;
                    if (v0 == 0) {
                        // 0x00304124
                        charge(ctx, 1);
                        lwc1(f0, gp, gp_off(0x7CAF94u));  // 0x7CAF94
                    } else {
                        // 0x00304114
                        charge(ctx, 4);
                        v0 = flt(1.5f);
                        mtc1(v0, f0);
                    }
                    // 0x00304128
                    charge(ctx, 3);
                    mul_s(f21, f21, f0);
                }
                // 0x003041a4
                charge(ctx, 6);
                lw(v0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
                v0 = addu(s6, v0);
                lbu(v0, v0, 36);
                at = sltiu(v0, 9);
                if (at != 0) {
                    // 0x003041bc
                    charge(ctx, 7);
                    v1 = hi(0x7B8ED0u);
                    v1 = addiu(v1, lo(0x7B8ED0u));  // "xD0"
                    v0 = sll(v0, 2);
                    v0 = addu(v0, v1);
                    lw(v0, v0, 0);
                    switch (v0.u()) {
                    case 0x3041D8u:  // table[2]
                        // 0x003041d8
                        charge(ctx, 7);
                        jal(ctx, 0x3041D8u, gen::fn_clndGetCurrentMoonPhase_00181b10);
                        v0 = v0 & 0xFF;
                        sq(v0, sp, 0xC0);
                        v0 = slti(v0, 30);
                        if (v0 == 0) {
                            // 0x003041f4
                            charge(ctx, 5);
                            k_assert(a0, a1, 0x304200u, kDatCalcFile, 2158);
                        }
                        // 0x00304208
                        charge(ctx, 8);
                        lq(v0, sp, 0xC0);
                        v0 = v0 & 0xFFFF;
                        v1 = sll(v0, 1);
                        lw(v0, gp, gp_off(0x7CE494u));  // 0x7CE494
                        v0 = addu(v0, v1);
                        lhu(v0, v0, 0);
                        u32_to_float(v0, v1, f0, f1);  // 0x0030423c / 0x00304228
                        // 0x00304258
                        charge(ctx, 9);
                        v0 = flt(100.0f);
                        mtc1(v0, f0);
                        div_s(f0, f1, f0);
                        mul_s(f23, f23, f0);
                        break;
                    case 0x30427Cu:  // table[3]
                        // 0x0030427c
                        charge(ctx, 7);
                        jal(ctx, 0x30427Cu, gen::fn_clndGetCurrentMoonPhase_00181b10);
                        v0 = v0 & 0xFF;
                        sq(v0, sp, 0xB0);
                        v0 = slti(v0, 30);
                        if (v0 == 0) {
                            // 0x00304298
                            charge(ctx, 5);
                            k_assert(a0, a1, 0x3042A4u, kDatCalcFile, 2163);
                        }
                        // 0x003042ac
                        charge(ctx, 8);
                        lq(v0, sp, 0xB0);
                        v0 = v0 & 0xFFFF;
                        v1 = sll(v0, 1);
                        lw(v0, gp, gp_off(0x7CE498u));  // 0x7CE498
                        v0 = addu(v0, v1);
                        lhu(v0, v0, 0);
                        u32_to_float(v0, v1, f0, f1);  // 0x003042e0 / 0x003042cc
                        // 0x003042fc
                        charge(ctx, 9);
                        v0 = flt(100.0f);
                        mtc1(v0, f0);
                        div_s(f0, f1, f0);
                        mul_s(f23, f23, f0);
                        break;
                    case 0x304320u:  // table[4]
                        // 0x00304320
                        charge(ctx, 4);
                        lhu(v0, s3, dat_unit::kFlags);
                        v0 = v0 & dat_unit::kFlagEnemy;
                        if (v0 == 0) {
                            // 0x0030433c
                            charge(ctx, 3);
                            lh(a0, s3, dat_unit::kId);
                            jal(ctx, 0x304340u, gen::fn_sub_16C920_0016c920);
                        } else {
                            // 0x00304330
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x00304348
                        charge(ctx, 4);
                        v1 = v0 & 0xFFFF;
                        v0 = 1;
                        if (v1 != v0) {
                            // 0x00304370
                            charge(ctx, 3);
                            v0 = 2;
                            if (v1 == v0) {
                                // 0x0030437c
                                charge(ctx, 6);
                                v0 = flt(2.0f);
                                mtc1(v0, f0);
                                mul_s(f23, f23, f0);
                            }
                        } else {
                            // 0x00304358
                            charge(ctx, 6);
                            v0 = flt(1.5f);
                            mtc1(v0, f0);
                            mul_s(f23, f23, f0);
                        }
                        break;
                    case 0x304394u:  // table[5]
                        // 0x00304394
                        charge(ctx, 4);
                        lhu(v0, s3, dat_unit::kFlags);
                        v0 = v0 & dat_unit::kFlagEnemy;
                        if (v0 == 0) {
                            // 0x003043b0
                            charge(ctx, 3);
                            lh(a0, s3, dat_unit::kId);
                            jal(ctx, 0x3043B4u, gen::fn_sub_16C920_0016c920);
                        } else {
                            // 0x003043a4
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x003043bc
                        charge(ctx, 4);
                        v1 = v0 & 0xFFFF;
                        v0 = 3;
                        if (v1 != v0) {
                            // 0x003043e4
                            charge(ctx, 3);
                            v0 = 4;
                            if (v1 != v0) {
                                // 0x00304408
                                charge(ctx, 3);
                                v0 = 5;
                                if (v1 == v0) {
                                    // 0x00304414
                                    charge(ctx, 4);
                                    lwc1(f0, gp, gp_off(0x7CAF98u));  // 0x7CAF98
                                    mul_s(f23, f23, f0);
                                }
                            } else {
                                // 0x003043f0
                                charge(ctx, 6);
                                v0 = flt(1.875f);
                                mtc1(v0, f0);
                                mul_s(f23, f23, f0);
                            }
                        } else {
                            // 0x003043cc
                            charge(ctx, 6);
                            v0 = flt(1.5f);
                            mtc1(v0, f0);
                            mul_s(f23, f23, f0);
                        }
                        break;
                    case 0x304424u:  // table[7]
                        // 0x00304424
                        charge(ctx, 5);
                        lw(v0, s2, dat_unit::kStatus);
                        v0 = v0 & 0x1;
                        v0 = sltu(0, v0);
                        if (v0 != 0) {
                            // 0x00304438
                            charge(ctx, 6);
                            v0 = flt(2.0f);
                            mtc1(v0, f0);
                            mul_s(f23, f23, f0);
                        }
                        break;
                    case 0x304450u:  // table[8]
                        // 0x00304450
                        charge(ctx, 6);
                        lw(v1, s2, dat_unit::kStatus);
                        v0 = 0x100000;
                        v0 = v1 & v0;
                        v0 = sltu(0, v0);
                        if (v0 != 0) {
                            // 0x00304468
                            charge(ctx, 4);
                            v0 = flt(2.0f);
                            mtc1(v0, f0);
                            mul_s(f23, f23, f0);
                        }
                        break;
                    case 0x304478u:  // table[0, 1, 6]
                        break;
                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                        tail(ctx, v0.u());
                        return;
                    }
                }
                // 0x00304478
                charge(ctx, 5);
                a0 = s4;
                jal(ctx, 0x30447Cu, gen::fn_datCalcIsPhysicalSkill_003088b0);
                if (v0 != 0) {
                    // 0x0030448c
                    charge(ctx, 4);
                    lhu(v0, s2, dat_unit::kFlags);
                    v0 = v0 & dat_unit::kFlagEnemy;
                    if (v0 != 0) {
                        // 0x0030449c
                        charge(ctx, 4);
                        lhu(v0, s3, dat_unit::kFlags);
                        v0 = v0 & dat_unit::kFlagEnemy;
                        if (v0 == 0) {
                            // 0x003044ac
                            charge(ctx, 4);
                            lhu(v0, s2, dat_unit::kId);
                            v0 = slti(v0, enemy_rec::kCount);
                            if (v0 == 0) {
                                // 0x003044bc
                                charge(ctx, 5);
                                k_assert(a0, a1, 0x3044C8u, kDatCalcFile, 2203);
                            }
                            // 0x003044d0
                            charge(ctx, 10);
                            lhu(v1, s2, dat_unit::kId);
                            v0 = sll(v1, 5);
                            v0 = subu(v0, v1);
                            v1 = sll(v0, 1);  // * 62 (EnemyRecord)
                            lw(v0, gp, gp_off(btl::kUnitTablePtr));  // gBtlEnemyTbl
                            v0 = addu(v1, v0);
                            lbu(v0, v0, 2);
                            at = sltiu(v0, 15);
                            if (at != 0) {
                                // 0x003044f8
                                charge(ctx, 7);
                                v1 = hi(0x7B8E90u);
                                v1 = addiu(v1, lo(0x7B8E90u));  // &0x7B8E90
                                v0 = sll(v0, 2);
                                v0 = addu(v0, v1);
                                lw(v0, v0, 0);
                                switch (v0.u()) {
                                case 0x304514u:  // table[2]
                                    // 0x00304514
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x00304530
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 36;
                                        jal(ctx, 0x304538u, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x00304524
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x00304540
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x00304548
                                        charge(ctx, 4);
                                        v0 = flt(1.25f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    // 0x00304558
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x00304574
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 144;
                                        jal(ctx, 0x30457Cu, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x00304568
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x00304584
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x0030458c
                                        charge(ctx, 4);
                                        v0 = flt(1.5f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    // 0x0030459c
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x003045b8
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 145;
                                        jal(ctx, 0x3045C0u, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x003045ac
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x003045c8
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x003045d0
                                        charge(ctx, 6);
                                        v0 = flt(1.75f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    break;
                                case 0x3045E8u:  // table[3]
                                    // 0x003045e8
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x00304604
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 37;
                                        jal(ctx, 0x30460Cu, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x003045f8
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x00304614
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x0030461c
                                        charge(ctx, 4);
                                        v0 = flt(1.25f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    // 0x0030462c
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x00304648
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 146;
                                        jal(ctx, 0x304650u, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x0030463c
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x00304658
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x00304660
                                        charge(ctx, 4);
                                        v0 = flt(1.5f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    // 0x00304670
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x0030468c
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 147;
                                        jal(ctx, 0x304694u, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x00304680
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x0030469c
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x003046a4
                                        charge(ctx, 6);
                                        v0 = flt(1.75f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    break;
                                case 0x3046BCu:  // table[4]
                                    // 0x003046bc
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x003046d8
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 38;
                                        jal(ctx, 0x3046E0u, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x003046cc
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x003046e8
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x003046f0
                                        charge(ctx, 4);
                                        v0 = flt(1.25f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    // 0x00304700
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x0030471c
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 148;
                                        jal(ctx, 0x304724u, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x00304710
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x0030472c
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x00304734
                                        charge(ctx, 4);
                                        v0 = flt(1.5f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    // 0x00304744
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x00304760
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 149;
                                        jal(ctx, 0x304768u, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x00304754
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x00304770
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x00304778
                                        charge(ctx, 6);
                                        v0 = flt(1.75f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    break;
                                case 0x304790u:  // table[5]
                                    // 0x00304790
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x003047ac
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 39;
                                        jal(ctx, 0x3047B4u, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x003047a0
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x003047bc
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x003047c4
                                        charge(ctx, 4);
                                        v0 = flt(1.25f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    // 0x003047d4
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x003047f0
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 150;
                                        jal(ctx, 0x3047F8u, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x003047e4
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x00304800
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x00304808
                                        charge(ctx, 4);
                                        v0 = flt(1.5f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    // 0x00304818
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x00304834
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 151;
                                        jal(ctx, 0x30483Cu, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x00304828
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x00304844
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x0030484c
                                        charge(ctx, 6);
                                        v0 = flt(1.75f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    break;
                                case 0x304864u:  // table[6]
                                    // 0x00304864
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x00304880
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 40;
                                        jal(ctx, 0x304888u, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x00304874
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x00304890
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x00304898
                                        charge(ctx, 4);
                                        v0 = flt(1.25f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    // 0x003048a8
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x003048c4
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 152;
                                        jal(ctx, 0x3048CCu, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x003048b8
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x003048d4
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x003048dc
                                        charge(ctx, 4);
                                        v0 = flt(1.5f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    // 0x003048ec
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x00304908
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 153;
                                        jal(ctx, 0x304910u, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x003048fc
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x00304918
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x00304920
                                        charge(ctx, 6);
                                        v0 = flt(1.75f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    break;
                                case 0x304938u:  // table[7]
                                    // 0x00304938
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x00304954
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 41;
                                        jal(ctx, 0x30495Cu, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x00304948
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x00304964
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x0030496c
                                        charge(ctx, 4);
                                        v0 = flt(1.25f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    // 0x0030497c
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x00304998
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 154;
                                        jal(ctx, 0x3049A0u, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x0030498c
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x003049a8
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x003049b0
                                        charge(ctx, 4);
                                        v0 = flt(1.5f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    // 0x003049c0
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x003049dc
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 155;
                                        jal(ctx, 0x3049E4u, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x003049d0
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x003049ec
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x003049f4
                                        charge(ctx, 6);
                                        v0 = flt(1.75f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    break;
                                case 0x304A0Cu:  // table[8]
                                    // 0x00304a0c
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x00304a28
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 42;
                                        jal(ctx, 0x304A30u, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x00304a1c
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x00304a38
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x00304a40
                                        charge(ctx, 4);
                                        v0 = flt(1.25f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    // 0x00304a50
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x00304a6c
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 156;
                                        jal(ctx, 0x304A74u, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x00304a60
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x00304a7c
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x00304a84
                                        charge(ctx, 4);
                                        v0 = flt(1.5f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    // 0x00304a94
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x00304ab0
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 157;
                                        jal(ctx, 0x304AB8u, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x00304aa4
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x00304ac0
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x00304ac8
                                        charge(ctx, 6);
                                        v0 = flt(1.75f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    break;
                                case 0x304AE0u:  // table[9]
                                    // 0x00304ae0
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x00304afc
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 43;
                                        jal(ctx, 0x304B04u, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x00304af0
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x00304b0c
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x00304b14
                                        charge(ctx, 4);
                                        v0 = flt(1.25f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    // 0x00304b24
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x00304b40
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 158;
                                        jal(ctx, 0x304B48u, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x00304b34
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x00304b50
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x00304b58
                                        charge(ctx, 4);
                                        v0 = flt(1.5f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    // 0x00304b68
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x00304b84
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 159;
                                        jal(ctx, 0x304B8Cu, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x00304b78
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x00304b94
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x00304b9c
                                        charge(ctx, 6);
                                        v0 = flt(1.75f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    break;
                                case 0x304BB4u:  // table[10]
                                    // 0x00304bb4
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x00304bd0
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 44;
                                        jal(ctx, 0x304BD8u, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x00304bc4
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x00304be0
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x00304be8
                                        charge(ctx, 4);
                                        v0 = flt(1.25f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    // 0x00304bf8
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x00304c14
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 160;
                                        jal(ctx, 0x304C1Cu, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x00304c08
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x00304c24
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x00304c2c
                                        charge(ctx, 4);
                                        v0 = flt(1.5f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    // 0x00304c3c
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x00304c58
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 161;
                                        jal(ctx, 0x304C60u, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x00304c4c
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x00304c68
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x00304c70
                                        charge(ctx, 6);
                                        v0 = flt(1.75f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    break;
                                case 0x304C88u:  // table[11]
                                    // 0x00304c88
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x00304ca4
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 45;
                                        jal(ctx, 0x304CACu, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x00304c98
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x00304cb4
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x00304cbc
                                        charge(ctx, 4);
                                        v0 = flt(1.25f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    // 0x00304ccc
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x00304ce8
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 162;
                                        jal(ctx, 0x304CF0u, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x00304cdc
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x00304cf8
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x00304d00
                                        charge(ctx, 4);
                                        v0 = flt(1.5f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    // 0x00304d10
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x00304d2c
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 163;
                                        jal(ctx, 0x304D34u, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x00304d20
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x00304d3c
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x00304d44
                                        charge(ctx, 6);
                                        v0 = flt(1.75f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    break;
                                case 0x304D5Cu:  // table[12]
                                    // 0x00304d5c
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x00304d78
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 46;
                                        jal(ctx, 0x304D80u, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x00304d6c
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x00304d88
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x00304d90
                                        charge(ctx, 4);
                                        v0 = flt(1.25f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    // 0x00304da0
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x00304dbc
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 164;
                                        jal(ctx, 0x304DC4u, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x00304db0
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x00304dcc
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x00304dd4
                                        charge(ctx, 4);
                                        v0 = flt(1.5f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    // 0x00304de4
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x00304e00
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 165;
                                        jal(ctx, 0x304E08u, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x00304df4
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x00304e10
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x00304e18
                                        charge(ctx, 6);
                                        v0 = flt(1.75f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    break;
                                case 0x304E30u:  // table[13]
                                    // 0x00304e30
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x00304e4c
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 47;
                                        jal(ctx, 0x304E54u, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x00304e40
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x00304e5c
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x00304e64
                                        charge(ctx, 4);
                                        v0 = flt(1.25f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    // 0x00304e74
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x00304e90
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 166;
                                        jal(ctx, 0x304E98u, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x00304e84
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x00304ea0
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x00304ea8
                                        charge(ctx, 4);
                                        v0 = flt(1.5f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    // 0x00304eb8
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x00304ed4
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 167;
                                        jal(ctx, 0x304EDCu, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x00304ec8
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x00304ee4
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x00304eec
                                        charge(ctx, 6);
                                        v0 = flt(1.75f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    break;
                                case 0x304F04u:  // table[14]
                                    // 0x00304f04
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x00304f20
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 48;
                                        jal(ctx, 0x304F28u, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x00304f14
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x00304f30
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x00304f38
                                        charge(ctx, 4);
                                        v0 = flt(1.25f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    // 0x00304f48
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x00304f64
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 168;
                                        jal(ctx, 0x304F6Cu, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x00304f58
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x00304f74
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x00304f7c
                                        charge(ctx, 4);
                                        v0 = flt(1.5f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    // 0x00304f8c
                                    charge(ctx, 4);
                                    lhu(v0, s3, dat_unit::kFlags);
                                    v0 = v0 & dat_unit::kFlagEnemy;
                                    if (v0 == 0) {
                                        // 0x00304fa8
                                        charge(ctx, 4);
                                        lhu(a0, s3, dat_unit::kId);
                                        a1 = 169;
                                        jal(ctx, 0x304FB0u, gen::fn_sub_300750_00300750);
                                    } else {
                                        // 0x00304f9c
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                    // 0x00304fb8
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x00304fc0
                                        charge(ctx, 4);
                                        v0 = flt(1.75f);
                                        mtc1(v0, f0);
                                        mul_s(f23, f23, f0);
                                    }
                                    break;
                                case 0x304FD0u:  // table[0, 1]
                                    break;
                                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                                    tail(ctx, v0.u());
                                    return;
                                }
                            }
                        }
                    }
                }
                // 0x00304fd0
                charge(ctx, 4);
                lhu(v0, s2, dat_unit::kFlags);
                v1 = v0 & dat_unit::kFlagEnemy;
                if (v1 == 0) {
                    // 0x00304fe0
                    charge(ctx, 3);
                    v0 = 2;
                    if (s5 != v0) {
                        // 0x00304fec
                        charge(ctx, 3);
                        v0 = 1;
                        if (s5 == v0) {
                            goto L_00305008;
                        }
                        // 0x00304ff8
                        charge(ctx, 2);
                        if (s5 == 0) {
                            goto L_00305008;
                        }
                        // 0x00305000
                        charge(ctx, 2);
                        goto L_003050b4;
                    }
                L_00305008:
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x0030501c
                        charge(ctx, 4);
                        lhu(a0, s2, dat_unit::kId);
                        a1 = 82;
                        jal(ctx, 0x305024u, gen::fn_sub_300750_00300750);
                    } else {
                        // 0x00305010
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x0030502c
                    charge(ctx, 2);
                    if (v0 != 0) {
                        // 0x00305034
                        charge(ctx, 2);
                        lwc1(f0, gp, gp_off(ai::kLit0_90));  // 0x7CAF8C
                        mul_s(f23, f23, f0);
                    }
                    // 0x0030503c
                    charge(ctx, 4);
                    lhu(v0, s2, dat_unit::kFlags);
                    v0 = v0 & dat_unit::kFlagEnemy;
                    if (v0 == 0) {
                        // 0x00305058
                        charge(ctx, 4);
                        lhu(a0, s2, dat_unit::kId);
                        a1 = 83;
                        jal(ctx, 0x305060u, gen::fn_sub_300750_00300750);
                    } else {
                        // 0x0030504c
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x00305068
                    charge(ctx, 2);
                    if (v0 != 0) {
                        // 0x00305070
                        charge(ctx, 2);
                        lwc1(f0, gp, gp_off(ai::kLit0_80));  // 0x7CAD74
                        mul_s(f23, f23, f0);
                    }
                    // 0x00305078
                    charge(ctx, 4);
                    lhu(v0, s2, dat_unit::kFlags);
                    v0 = v0 & dat_unit::kFlagEnemy;
                    if (v0 == 0) {
                        // 0x00305094
                        charge(ctx, 4);
                        lhu(a0, s2, dat_unit::kId);
                        a1 = 84;
                        jal(ctx, 0x30509Cu, gen::fn_sub_300750_00300750);
                    } else {
                        // 0x00305088
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x003050a4
                    charge(ctx, 2);
                    if (v0 != 0) {
                        // 0x003050ac
                        charge(ctx, 2);
                        lwc1(f0, gp, gp_off(ai::kLit0_70));  // 0x7CADD0
                        mul_s(f23, f23, f0);
                    }
                L_003050b4:
                    charge(ctx, 3);
                    v0 = 6;
                    if (s5 != v0) {
                        // 0x003050c0
                        charge(ctx, 3);
                        v0 = 5;
                        if (s5 == v0) {
                            goto L_003050ec;
                        }
                        // 0x003050cc
                        charge(ctx, 3);
                        v0 = 4;
                        if (s5 == v0) {
                            goto L_003050ec;
                        }
                        // 0x003050d8
                        charge(ctx, 3);
                        v0 = 3;
                        if (s5 == v0) {
                            goto L_003050ec;
                        }
                        // 0x003050e4
                        charge(ctx, 2);
                        goto L_003051a0;
                    }
                L_003050ec:
                    charge(ctx, 4);
                    lhu(v0, s2, dat_unit::kFlags);
                    v0 = v0 & dat_unit::kFlagEnemy;
                    if (v0 == 0) {
                        // 0x00305108
                        charge(ctx, 4);
                        lhu(a0, s2, dat_unit::kId);
                        a1 = 97;
                        jal(ctx, 0x305110u, gen::fn_sub_300750_00300750);
                    } else {
                        // 0x003050fc
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x00305118
                    charge(ctx, 2);
                    if (v0 != 0) {
                        // 0x00305120
                        charge(ctx, 2);
                        lwc1(f0, gp, gp_off(ai::kLit0_90));  // 0x7CAF8C
                        mul_s(f23, f23, f0);
                    }
                    // 0x00305128
                    charge(ctx, 4);
                    lhu(v0, s2, dat_unit::kFlags);
                    v0 = v0 & dat_unit::kFlagEnemy;
                    if (v0 == 0) {
                        // 0x00305144
                        charge(ctx, 4);
                        lhu(a0, s2, dat_unit::kId);
                        a1 = 98;
                        jal(ctx, 0x30514Cu, gen::fn_sub_300750_00300750);
                    } else {
                        // 0x00305138
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x00305154
                    charge(ctx, 2);
                    if (v0 != 0) {
                        // 0x0030515c
                        charge(ctx, 2);
                        lwc1(f0, gp, gp_off(ai::kLit0_80));  // 0x7CAD74
                        mul_s(f23, f23, f0);
                    }
                    // 0x00305164
                    charge(ctx, 4);
                    lhu(v0, s2, dat_unit::kFlags);
                    v0 = v0 & dat_unit::kFlagEnemy;
                    if (v0 == 0) {
                        // 0x00305180
                        charge(ctx, 4);
                        lhu(a0, s2, dat_unit::kId);
                        a1 = 99;
                        jal(ctx, 0x305188u, gen::fn_sub_300750_00300750);
                    } else {
                        // 0x00305174
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x00305190
                    charge(ctx, 2);
                    if (v0 != 0) {
                        // 0x00305198
                        charge(ctx, 2);
                        lwc1(f0, gp, gp_off(ai::kLit0_70));  // 0x7CADD0
                        mul_s(f23, f23, f0);
                    }
                L_003051a0:
                    charge(ctx, 3);
                    at = sltiu(s5, 7);
                    if (at != 0) {
                        // 0x003051ac
                        charge(ctx, 7);
                        v1 = hi(0x7B8E70u);
                        v1 = addiu(v1, lo(0x7B8E70u));  // &0x7B8E70
                        v0 = sll(s5, 2);
                        v0 = addu(v0, v1);
                        lw(v0, v0, 0);
                        switch (v0.u()) {
                        case 0x3051C8u:  // table[0]
                            // 0x003051c8
                            charge(ctx, 4);
                            lhu(v0, s2, dat_unit::kFlags);
                            v0 = v0 & dat_unit::kFlagEnemy;
                            if (v0 == 0) {
                                // 0x003051e4
                                charge(ctx, 4);
                                lhu(a0, s2, dat_unit::kId);
                                a1 = 76;
                                jal(ctx, 0x3051ECu, gen::fn_sub_300750_00300750);
                            } else {
                                // 0x003051d8
                                charge(ctx, 3);
                                v0 = 0;
                            }
                            // 0x003051f4
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x003051fc
                                charge(ctx, 2);
                                lwc1(f0, gp, gp_off(ai::kLit0_90));  // 0x7CAF8C
                                mul_s(f23, f23, f0);
                            }
                            // 0x00305204
                            charge(ctx, 4);
                            lhu(v0, s2, dat_unit::kFlags);
                            v0 = v0 & dat_unit::kFlagEnemy;
                            if (v0 == 0) {
                                // 0x00305220
                                charge(ctx, 4);
                                lhu(a0, s2, dat_unit::kId);
                                a1 = 77;
                                jal(ctx, 0x305228u, gen::fn_sub_300750_00300750);
                            } else {
                                // 0x00305214
                                charge(ctx, 3);
                                v0 = 0;
                            }
                            // 0x00305230
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x00305238
                                charge(ctx, 2);
                                lwc1(f0, gp, gp_off(ai::kLit0_80));  // 0x7CAD74
                                mul_s(f23, f23, f0);
                            }
                            // 0x00305240
                            charge(ctx, 4);
                            lhu(v0, s2, dat_unit::kFlags);
                            v0 = v0 & dat_unit::kFlagEnemy;
                            if (v0 == 0) {
                                // 0x0030525c
                                charge(ctx, 4);
                                lhu(a0, s2, dat_unit::kId);
                                a1 = 78;
                                jal(ctx, 0x305264u, gen::fn_sub_300750_00300750);
                            } else {
                                // 0x00305250
                                charge(ctx, 3);
                                v0 = 0;
                            }
                            // 0x0030526c
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x00305274
                                charge(ctx, 4);
                                lwc1(f0, gp, gp_off(ai::kLit0_70));  // 0x7CADD0
                                mul_s(f23, f23, f0);
                            }
                            break;
                        case 0x305284u:  // table[1]
                            // 0x00305284
                            charge(ctx, 4);
                            lhu(v0, s2, dat_unit::kFlags);
                            v0 = v0 & dat_unit::kFlagEnemy;
                            if (v0 == 0) {
                                // 0x003052a0
                                charge(ctx, 4);
                                lhu(a0, s2, dat_unit::kId);
                                a1 = 73;
                                jal(ctx, 0x3052A8u, gen::fn_sub_300750_00300750);
                            } else {
                                // 0x00305294
                                charge(ctx, 3);
                                v0 = 0;
                            }
                            // 0x003052b0
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x003052b8
                                charge(ctx, 2);
                                lwc1(f0, gp, gp_off(ai::kLit0_90));  // 0x7CAF8C
                                mul_s(f23, f23, f0);
                            }
                            // 0x003052c0
                            charge(ctx, 4);
                            lhu(v0, s2, dat_unit::kFlags);
                            v0 = v0 & dat_unit::kFlagEnemy;
                            if (v0 == 0) {
                                // 0x003052dc
                                charge(ctx, 4);
                                lhu(a0, s2, dat_unit::kId);
                                a1 = 74;
                                jal(ctx, 0x3052E4u, gen::fn_sub_300750_00300750);
                            } else {
                                // 0x003052d0
                                charge(ctx, 3);
                                v0 = 0;
                            }
                            // 0x003052ec
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x003052f4
                                charge(ctx, 2);
                                lwc1(f0, gp, gp_off(ai::kLit0_80));  // 0x7CAD74
                                mul_s(f23, f23, f0);
                            }
                            // 0x003052fc
                            charge(ctx, 4);
                            lhu(v0, s2, dat_unit::kFlags);
                            v0 = v0 & dat_unit::kFlagEnemy;
                            if (v0 == 0) {
                                // 0x00305318
                                charge(ctx, 4);
                                lhu(a0, s2, dat_unit::kId);
                                a1 = 75;
                                jal(ctx, 0x305320u, gen::fn_sub_300750_00300750);
                            } else {
                                // 0x0030530c
                                charge(ctx, 3);
                                v0 = 0;
                            }
                            // 0x00305328
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x00305330
                                charge(ctx, 4);
                                lwc1(f0, gp, gp_off(ai::kLit0_70));  // 0x7CADD0
                                mul_s(f23, f23, f0);
                            }
                            break;
                        case 0x305340u:  // table[2]
                            // 0x00305340
                            charge(ctx, 4);
                            lhu(v0, s2, dat_unit::kFlags);
                            v0 = v0 & dat_unit::kFlagEnemy;
                            if (v0 == 0) {
                                // 0x0030535c
                                charge(ctx, 4);
                                lhu(a0, s2, dat_unit::kId);
                                a1 = 79;
                                jal(ctx, 0x305364u, gen::fn_sub_300750_00300750);
                            } else {
                                // 0x00305350
                                charge(ctx, 3);
                                v0 = 0;
                            }
                            // 0x0030536c
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x00305374
                                charge(ctx, 2);
                                lwc1(f0, gp, gp_off(ai::kLit0_90));  // 0x7CAF8C
                                mul_s(f23, f23, f0);
                            }
                            // 0x0030537c
                            charge(ctx, 4);
                            lhu(v0, s2, dat_unit::kFlags);
                            v0 = v0 & dat_unit::kFlagEnemy;
                            if (v0 == 0) {
                                // 0x00305398
                                charge(ctx, 4);
                                lhu(a0, s2, dat_unit::kId);
                                a1 = 80;
                                jal(ctx, 0x3053A0u, gen::fn_sub_300750_00300750);
                            } else {
                                // 0x0030538c
                                charge(ctx, 3);
                                v0 = 0;
                            }
                            // 0x003053a8
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x003053b0
                                charge(ctx, 2);
                                lwc1(f0, gp, gp_off(ai::kLit0_80));  // 0x7CAD74
                                mul_s(f23, f23, f0);
                            }
                            // 0x003053b8
                            charge(ctx, 4);
                            lhu(v0, s2, dat_unit::kFlags);
                            v0 = v0 & dat_unit::kFlagEnemy;
                            if (v0 == 0) {
                                // 0x003053d4
                                charge(ctx, 4);
                                lhu(a0, s2, dat_unit::kId);
                                a1 = 81;
                                jal(ctx, 0x3053DCu, gen::fn_sub_300750_00300750);
                            } else {
                                // 0x003053c8
                                charge(ctx, 3);
                                v0 = 0;
                            }
                            // 0x003053e4
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x003053ec
                                charge(ctx, 4);
                                lwc1(f0, gp, gp_off(ai::kLit0_70));  // 0x7CADD0
                                mul_s(f23, f23, f0);
                            }
                            break;
                        case 0x3053FCu:  // table[3]
                            // 0x003053fc
                            charge(ctx, 4);
                            lhu(v0, s2, dat_unit::kFlags);
                            v0 = v0 & dat_unit::kFlagEnemy;
                            if (v0 == 0) {
                                // 0x00305418
                                charge(ctx, 4);
                                lhu(a0, s2, dat_unit::kId);
                                a1 = 85;
                                jal(ctx, 0x305420u, gen::fn_sub_300750_00300750);
                            } else {
                                // 0x0030540c
                                charge(ctx, 3);
                                v0 = 0;
                            }
                            // 0x00305428
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x00305430
                                charge(ctx, 2);
                                lwc1(f0, gp, gp_off(ai::kLit0_90));  // 0x7CAF8C
                                mul_s(f23, f23, f0);
                            }
                            // 0x00305438
                            charge(ctx, 4);
                            lhu(v0, s2, dat_unit::kFlags);
                            v0 = v0 & dat_unit::kFlagEnemy;
                            if (v0 == 0) {
                                // 0x00305454
                                charge(ctx, 4);
                                lhu(a0, s2, dat_unit::kId);
                                a1 = 86;
                                jal(ctx, 0x30545Cu, gen::fn_sub_300750_00300750);
                            } else {
                                // 0x00305448
                                charge(ctx, 3);
                                v0 = 0;
                            }
                            // 0x00305464
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x0030546c
                                charge(ctx, 2);
                                lwc1(f0, gp, gp_off(ai::kLit0_80));  // 0x7CAD74
                                mul_s(f23, f23, f0);
                            }
                            // 0x00305474
                            charge(ctx, 4);
                            lhu(v0, s2, dat_unit::kFlags);
                            v0 = v0 & dat_unit::kFlagEnemy;
                            if (v0 == 0) {
                                // 0x00305490
                                charge(ctx, 4);
                                lhu(a0, s2, dat_unit::kId);
                                a1 = 87;
                                jal(ctx, 0x305498u, gen::fn_sub_300750_00300750);
                            } else {
                                // 0x00305484
                                charge(ctx, 3);
                                v0 = 0;
                            }
                            // 0x003054a0
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x003054a8
                                charge(ctx, 4);
                                lwc1(f0, gp, gp_off(ai::kLit0_70));  // 0x7CADD0
                                mul_s(f23, f23, f0);
                            }
                            break;
                        case 0x3054B8u:  // table[4]
                            // 0x003054b8
                            charge(ctx, 4);
                            lhu(v0, s2, dat_unit::kFlags);
                            v0 = v0 & dat_unit::kFlagEnemy;
                            if (v0 == 0) {
                                // 0x003054d4
                                charge(ctx, 4);
                                lhu(a0, s2, dat_unit::kId);
                                a1 = 88;
                                jal(ctx, 0x3054DCu, gen::fn_sub_300750_00300750);
                            } else {
                                // 0x003054c8
                                charge(ctx, 3);
                                v0 = 0;
                            }
                            // 0x003054e4
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x003054ec
                                charge(ctx, 2);
                                lwc1(f0, gp, gp_off(ai::kLit0_90));  // 0x7CAF8C
                                mul_s(f23, f23, f0);
                            }
                            // 0x003054f4
                            charge(ctx, 4);
                            lhu(v0, s2, dat_unit::kFlags);
                            v0 = v0 & dat_unit::kFlagEnemy;
                            if (v0 == 0) {
                                // 0x00305510
                                charge(ctx, 4);
                                lhu(a0, s2, dat_unit::kId);
                                a1 = 89;
                                jal(ctx, 0x305518u, gen::fn_sub_300750_00300750);
                            } else {
                                // 0x00305504
                                charge(ctx, 3);
                                v0 = 0;
                            }
                            // 0x00305520
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x00305528
                                charge(ctx, 2);
                                lwc1(f0, gp, gp_off(ai::kLit0_80));  // 0x7CAD74
                                mul_s(f23, f23, f0);
                            }
                            // 0x00305530
                            charge(ctx, 4);
                            lhu(v0, s2, dat_unit::kFlags);
                            v0 = v0 & dat_unit::kFlagEnemy;
                            if (v0 == 0) {
                                // 0x0030554c
                                charge(ctx, 4);
                                lhu(a0, s2, dat_unit::kId);
                                a1 = 90;
                                jal(ctx, 0x305554u, gen::fn_sub_300750_00300750);
                            } else {
                                // 0x00305540
                                charge(ctx, 3);
                                v0 = 0;
                            }
                            // 0x0030555c
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x00305564
                                charge(ctx, 4);
                                lwc1(f0, gp, gp_off(ai::kLit0_70));  // 0x7CADD0
                                mul_s(f23, f23, f0);
                            }
                            break;
                        case 0x305574u:  // table[5]
                            // 0x00305574
                            charge(ctx, 4);
                            lhu(v0, s2, dat_unit::kFlags);
                            v0 = v0 & dat_unit::kFlagEnemy;
                            if (v0 == 0) {
                                // 0x00305590
                                charge(ctx, 4);
                                lhu(a0, s2, dat_unit::kId);
                                a1 = 94;
                                jal(ctx, 0x305598u, gen::fn_sub_300750_00300750);
                            } else {
                                // 0x00305584
                                charge(ctx, 3);
                                v0 = 0;
                            }
                            // 0x003055a0
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x003055a8
                                charge(ctx, 2);
                                lwc1(f0, gp, gp_off(ai::kLit0_90));  // 0x7CAF8C
                                mul_s(f23, f23, f0);
                            }
                            // 0x003055b0
                            charge(ctx, 4);
                            lhu(v0, s2, dat_unit::kFlags);
                            v0 = v0 & dat_unit::kFlagEnemy;
                            if (v0 == 0) {
                                // 0x003055cc
                                charge(ctx, 4);
                                lhu(a0, s2, dat_unit::kId);
                                a1 = 95;
                                jal(ctx, 0x3055D4u, gen::fn_sub_300750_00300750);
                            } else {
                                // 0x003055c0
                                charge(ctx, 3);
                                v0 = 0;
                            }
                            // 0x003055dc
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x003055e4
                                charge(ctx, 2);
                                lwc1(f0, gp, gp_off(ai::kLit0_80));  // 0x7CAD74
                                mul_s(f23, f23, f0);
                            }
                            // 0x003055ec
                            charge(ctx, 4);
                            lhu(v0, s2, dat_unit::kFlags);
                            v0 = v0 & dat_unit::kFlagEnemy;
                            if (v0 == 0) {
                                // 0x00305608
                                charge(ctx, 4);
                                lhu(a0, s2, dat_unit::kId);
                                a1 = 96;
                                jal(ctx, 0x305610u, gen::fn_sub_300750_00300750);
                            } else {
                                // 0x003055fc
                                charge(ctx, 3);
                                v0 = 0;
                            }
                            // 0x00305618
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x00305620
                                charge(ctx, 4);
                                lwc1(f0, gp, gp_off(ai::kLit0_70));  // 0x7CADD0
                                mul_s(f23, f23, f0);
                            }
                            break;
                        case 0x305630u:  // table[6]
                            // 0x00305630
                            charge(ctx, 4);
                            lhu(v0, s2, dat_unit::kFlags);
                            v0 = v0 & dat_unit::kFlagEnemy;
                            if (v0 == 0) {
                                // 0x0030564c
                                charge(ctx, 4);
                                lhu(a0, s2, dat_unit::kId);
                                a1 = 91;
                                jal(ctx, 0x305654u, gen::fn_sub_300750_00300750);
                            } else {
                                // 0x00305640
                                charge(ctx, 3);
                                v0 = 0;
                            }
                            // 0x0030565c
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x00305664
                                charge(ctx, 2);
                                lwc1(f0, gp, gp_off(ai::kLit0_90));  // 0x7CAF8C
                                mul_s(f23, f23, f0);
                            }
                            // 0x0030566c
                            charge(ctx, 4);
                            lhu(v0, s2, dat_unit::kFlags);
                            v0 = v0 & dat_unit::kFlagEnemy;
                            if (v0 == 0) {
                                // 0x00305688
                                charge(ctx, 4);
                                lhu(a0, s2, dat_unit::kId);
                                a1 = 92;
                                jal(ctx, 0x305690u, gen::fn_sub_300750_00300750);
                            } else {
                                // 0x0030567c
                                charge(ctx, 3);
                                v0 = 0;
                            }
                            // 0x00305698
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x003056a0
                                charge(ctx, 2);
                                lwc1(f0, gp, gp_off(ai::kLit0_80));  // 0x7CAD74
                                mul_s(f23, f23, f0);
                            }
                            // 0x003056a8
                            charge(ctx, 4);
                            lhu(v0, s2, dat_unit::kFlags);
                            v0 = v0 & dat_unit::kFlagEnemy;
                            if (v0 == 0) {
                                // 0x003056c4
                                charge(ctx, 4);
                                lhu(a0, s2, dat_unit::kId);
                                a1 = 93;
                                jal(ctx, 0x3056CCu, gen::fn_sub_300750_00300750);
                            } else {
                                // 0x003056b8
                                charge(ctx, 3);
                                v0 = 0;
                            }
                            // 0x003056d4
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x003056dc
                                charge(ctx, 2);
                                lwc1(f0, gp, gp_off(ai::kLit0_70));  // 0x7CADD0
                                mul_s(f23, f23, f0);
                            }
                            break;
                        default:  // not one of the table's targets: the dispatch table, as the recompiled body
                            tail(ctx, v0.u());
                            return;
                        }
                    }
                }
                // 0x003056e4
                charge(ctx, 12);
                mtc1(s0, f0);
                cvt_s_w(f0, f0);
                mul_s(f0, f0, f23);
                mul_s(f0, f22, f0);
                mul_s(f0, f21, f0);
                mul_s(f0, f20, f0);
                cvt_w_s(f0, f0);
                mfc1(s0, f0);
                v0 = 16;
                if (fp != v0) {
                    // 0x00305720
                    charge(ctx, 3);
                    at = slti(s0, 31001);
                    if (at != 0) {
                        // 0x00305738
                        charge(ctx, 7);
                        lw(v0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
                        v0 = addiu(v0, 40);
                        v0 = addu(v0, s6);
                        lhu(v0, v0, 0);
                        at = slt(s0, v0);
                        if (at != 0) {
                            // 0x00305754
                            charge(ctx, 1);
                            s0 = v0;
                        }
                    } else {
                        // 0x0030572c
                        charge(ctx, 3);
                        s0 = 31000;
                    }
                    // 0x00305758
                    charge(ctx, 8);
                    a0 = 11;
                    jal(ctx, 0x30575Cu, gen::fn_datCalcRand_002ffbc0);
                    v0 = addiu(v0, 95);
                    mult(v1, s0, v0);
                    v0 = 100;
                    divu(v1, v0);
                    mflo(s0);
                } else {
                    // 0x00305714
                    charge(ctx, 3);
                    s0 = 500;
                }
                // 0x00305778
                charge(ctx, 2);
                if (i64(s0) <= 0) {
                    // 0x00305780
                    charge(ctx, 1);
                    s0 = 1;
                }
            }
        }
    }
    // 0x00305784
    charge(ctx, 2);
    if (s7 == 0) {
        // 0x0030578c
        charge(ctx, 2);
        if (i64(s1) > 0) {
            // 0x00305794
            charge(ctx, 4);
            lw(v0, sp, 0x104);
            v0 = v0 & 0x1;
            if (v0 == 0) {
                // 0x003057a4
                charge(ctx, 4);
                lhu(v0, s2, dat_unit::kFlags);
                v0 = v0 & dat_unit::kFlagEnemy;
                if (v0 == 0) {
                    // 0x003057c0
                    charge(ctx, 3);
                    lh(a0, s2, dat_unit::kId);
                    jal(ctx, 0x3057C4u, gen::fn_sub_16C920_0016c920);
                } else {
                    // 0x003057b4
                    charge(ctx, 3);
                    v0 = 0;
                }
                // 0x003057cc
                charge(ctx, 4);
                v1 = v0 & 0xFFFF;
                v0 = 5;
                if (v1 == v0) {
                    // 0x003057dc
                    charge(ctx, 7);
                    a0 = 4889;
                    jal(ctx, 0x3057E0u, gen::fn_datGetFlag_0016f190);
                    v0 = flt(0.5f);
                    mtc1(v0, f0);
                    mul_s(f21, f21, f0);
                }
                // 0x003057f8
                charge(ctx, 6);
                a0 = s3;
                a1 = 570;
                jal(ctx, 0x305800u, gen::fn_datCalcHasSkill_003005e0);
                if (v0 != 0) {
                    // 0x00305810
                    charge(ctx, 4);
                    v0 = flt(2.0f);
                    mtc1(v0, f0);
                    mul_s(f20, f20, f0);
                }
                // 0x00305820
                charge(ctx, 13);
                mtc1(s1, f0);
                cvt_s_w(f0, f0);
                mul_s(f0, f0, f23);
                mul_s(f0, f22, f0);
                mul_s(f0, f21, f0);
                mul_s(f0, f20, f0);
                cvt_w_s(f0, f0);
                mfc1(s1, f0);
                at = slti(s1, 31001);
                if (at != 0) {
                    // 0x00305860
                    charge(ctx, 13);
                    v1 = s4 & 0xFFFF;
                    v0 = sll(v1, 2);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 1);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);  // * 44 (SkillRecord)
                    lw(v0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
                    v0 = addiu(v0, 40);
                    v0 = addu(v0, v1);
                    lhu(v0, v0, 0);
                    at = slt(s1, v0);
                    if (at != 0) {
                        // 0x00305894
                        charge(ctx, 1);
                        s1 = v0;
                    }
                } else {
                    // 0x00305854
                    charge(ctx, 3);
                    s1 = 31000;
                }
                // 0x00305898
                charge(ctx, 10);
                a0 = 11;
                jal(ctx, 0x30589Cu, gen::fn_datCalcRand_002ffbc0);
                v0 = addiu(v0, 95);
                mult(v1, s1, v0);
                v0 = 100;
                divu(v1, v0);
                mflo(s1);
                if (i64(s1) <= 0) {
                    // 0x003058c0
                    charge(ctx, 1);
                    s1 = 1;
                }
            }
        }
    }
    // 0x003058c4
    charge(ctx, 5);
    lhu(v0, sp, 0x10C);
    v1 = v0;
    v0 = 1024;
    if (v1 == v0) {
        // 0x003058d8
        charge(ctx, 2);
        if (i64(s0) > 0) {
            // 0x003058e0
            charge(ctx, 2);
            s1 = s0;
            s0 = 0;
        }
    }
    // 0x003058e8
    charge(ctx, 3);
    v0 = 4;
    if (v1 != v0) {
        // 0x003058f4
        charge(ctx, 3);
        v0 = 2;
        if (v1 == v0) {
            goto L_00305914;
        }
        // 0x00305900
        charge(ctx, 3);
        v0 = 256;
        if (v1 == v0) {
            goto L_00305914;
        }
        // 0x0030590c
        charge(ctx, 2);
        goto L_0030591c;
    }
L_00305914:
    charge(ctx, 2);
    s1 = 0;
    s0 = 0;
L_0030591c:
    charge(ctx, 2);
    if (i64(s0) > 0) {
        // 0x00305924
        charge(ctx, 1);
        s1 = subu(0, s0);
    }
    // 0x00305928: epilogue
    charge(ctx, 18);
    v0 = s1;
    ld(ra, sp, 0xA0);
    lq(fp, sp, 0x90);
    lq(s7, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x110);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
s32 datCalcDamage(EEContext& ctx, u32 skill, u32 attacker, u32 target, u32 hits, u32 result, u32 kind, u32 flags, u32 hp_or_sp) {
    ee::core::set_gpr64(ctx, GPR_A0, ee::core::sext32(static_cast<u32>(skill)));
    ee::core::set_gpr64(ctx, GPR_A1, ee::core::sext32(static_cast<u32>(attacker)));
    ee::core::set_gpr64(ctx, GPR_A2, ee::core::sext32(static_cast<u32>(target)));
    ee::core::set_gpr64(ctx, GPR_A3, ee::core::sext32(static_cast<u32>(hits)));
    ee::core::set_gpr64(ctx, GPR_T0, ee::core::sext32(static_cast<u32>(result)));
    ee::core::set_gpr64(ctx, GPR_T1, ee::core::sext32(static_cast<u32>(kind)));
    ee::core::set_gpr64(ctx, GPR_T2, ee::core::sext32(static_cast<u32>(flags)));
    ee::core::set_gpr64(ctx, GPR_T3, ee::core::sext32(static_cast<u32>(hp_or_sp)));
    datCalcDamage(ctx);
    return static_cast<s32>(ee::core::gpr64(ctx, GPR_V0));
}

}  // namespace p3fes::game

// --- the recompiled program's entry points ---------------------------------------------------------------------
// Results that are register values of a callee (a pointer, a persona word) or sign-extended loads go to $v0 as
// the full 64-bit value; the others are small integers.
namespace p3fes::recomp_gen {
using namespace p3fes::game;
void fn_datCalcGetSkillSlotCount_00308ba0(p3fes::EEContext& ctx) { guest::ret32(ctx, datCalcGetSkillSlotCount(ctx)); }
// datCalcDamage takes eight arguments: $a0..$a3 and $t0..$t3.
}  // namespace p3fes::recomp_gen
