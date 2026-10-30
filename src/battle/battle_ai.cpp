// The AICALC formulas of datScript.c (game/include/p3fes/game/battle_ai.h), hand-decompiled from SLUS_216.21
// (docs/ANALYSIS/21_battle.md section 4): datScriptCalc's dispatch, datScriptGetValue's 35 selectors and the 48
// formula functions. Phase 5: these replace the recompiled bodies listed in game/replaced.txt; tests/game/
// test_battle_ai.cpp runs each against its __recomp body.
//
// Virtual time per ADR-0013 (block costs from recomp/generated/fn_0024_002ff2f0_00315c20.cpp). The formula
// bodies are straight-line within each branch, so every branch is one `charge`. K_Assert (sub_19D3F0) is `jr $ra`
// in retail and is kept through a call for its check point and two cycles; a failed check continues.
//
// Register state a caller can observe is reproduced: $v0 (the compiled code materialises every float literal with
// `lui $v0`, so a formula leaves the last literal or the last callee's $v0 there -- `literal()` below writes it), $f0
// (each function's result register), ACC (MADD.S), the FCR31 condition and the D/I flags of DIV.S/SQRT.S, HI/LO of
// the getter's three DIVs, and the $s0/$s1 the getter writes and restores (datCalcGetElementForStatus returns its
// caller's $s0 on one path, so the getter's $s0 is live across that call). One FPU register crosses a call as an
// input: the getter's assertion paths (selector 0, out of range, GV(19) with a bad mode) return the caller's $f20, and
// the compiled formulas keep an intermediate there -- gv19() puts that value in $f20 for the GV(19) calls. The other
// FPU temporaries ($f1..$f3, $f21) of the formula chains are dead at every return and are not mirrored.
//
// Faithfulness audit (2026-10-21, tools/ours/audit): 50 of the 53 functions here are now p3fes_handgen's register-
// faithful bodies (their hand versions differed from the original: frame/spills 50); each keeps the notes of its
// earlier hand version above it. The others are the hand-written versions this header describes.
//
// Readability pass (read_battle, 2026-10-21): the 50 generated bodies keep every statement, charge, check point and
// call of p3fes_handgen's output in the same order on every path; on top of it the datScriptGetValue calls read
// `get_value(a0, a1, pc, sel::kPower, 0)` (the same three statements; the selectors are named in battle_ai.h), the
// compiled unsigned conversion is `u32_to_float` (battle_view.h, the same two blocks), literals and context words
// are spelled by value or name (`flt(30.0f)`, `hi(ai::kAttacker)`), the branches say which attacker / skill kind
// they handle, and each formula's comment gives its set, slot, formula and a proposed name in brackets.
#include "p3fes/game/battle_ai.h"

#include "p3fes/ee/core.h"
#include "p3fes/ee/fpu.h"
#include "p3fes/ee/hilo.h"
#include "p3fes/game/battle.h"
#include "p3fes/game/guest.h"
#include "p3fes/game/battle_view.h"
#include "p3fes/game/hg_cpu.h"

namespace p3fes::recomp_gen {
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);  // K_Assert(file, line)
void fn_datGetFlag_0016f190(p3fes::EEContext&);  // datGetFlag(id)
void fn_datScriptGetValue_0030fdf0(p3fes::EEContext&);  // (this file)
void fn_datScriptSetResult_00311190(p3fes::EEContext&);  // datScriptSetResult(v): 0x957198 = v, 0x9571A4 |= 1
void fn_sub_3111F0_003111f0(p3fes::EEContext&);  // is the attacker a party member: !(attacker->flags & 4)
void fn_sub_311250_00311250(p3fes::EEContext&);  // is the skill physical: SkillRecord[skill].flags0 & 2
void fn_datCalcGetLevel_002ffcc0(p3fes::EEContext&);  // datCalcGetLevel(unit)
void fn_datCalcGetHp_002ffd70(p3fes::EEContext&);  // datCalcGetHp(unit)
void fn_datCalcGetMaxHp_002ffdf0(p3fes::EEContext&);  // datCalcGetMaxHp(unit)
void fn_datCalcGetMaxSp_00300100(p3fes::EEContext&);  // datCalcGetMaxSp(unit)
void fn_datCalcGetSkillElement_003082f0(p3fes::EEContext&);  // datCalcGetSkillElement(unit, skill)
void fn_datCalcGetAffinity_00306e80(p3fes::EEContext&);  // datCalcGetAffinity(unit, element): low 16 bits = rate
void fn_datCalcGetElementForStatus_00308120(p3fes::EEContext&);  // datCalcGetElementForStatus(skill, status)
void fn_datCalcGetStat_00300c90(p3fes::EEContext&);  // datCalcGetStat(unit, stat)
void fn_datCalcGetWeaponParam_00309080(p3fes::EEContext&);  // datCalcGetWeaponParam(unit, 0 power / 1 accuracy)
void fn_datCalcGetArmorParam_00309250(p3fes::EEContext&);  // datCalcGetArmorParam(unit, 0 / 1)
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

using namespace bview;  // hi / lo / gp_off / flt / k_assert and the record offsets (battle_view.h)

namespace {

using namespace ai;
namespace fpu = ee::fpu;
namespace core = ee::core;

// datScriptGetValue(selector, index) called at `pc`: `addiu a0, $zero, selector; addiu a1, $zero, index;
// jal datScriptGetValue` -- the three statements of every call in the formulas, in their order. The value comes back
// in $f0 (sel:: in battle_ai.h names the selectors).
inline void get_value(hg::Gpr a0, hg::Gpr a1, u32 pc, s32 selector, s32 index) {
    a0 = hg::si(selector);
    a1 = hg::si(index);
    hg::jal(a0.c, pc, ::p3fes::recomp_gen::fn_datScriptGetValue_0030fdf0);
}

// --- the formula shapes (the 48 functions are 17 distinct bodies; tables 1..3 reuse most of them) -----------------
// Every formula: `attacker is a party member` = sub_3111F0() (an enemy attacker takes the other branch), `physical` =
// sub_311250(); the chain of EE single operations on get_value results in the compiled operand order (ADD.S / MUL.S
// chopped, DIV.S, the truncating SQRT.S, ADDA.S + MADD.S through ACC: `adda_s(f1, x); madd_s(d, s, t)` is
// d = (0 + x) + s * t with f1 = 0), then datScriptSetResult((s32)result) (cvt.w.s, mfc1 $a0). Shared building blocks,
// as the slot comments below call them:
//   En2      = GV(kStatT, kEn) + GV(kStatT, kEn), the target's endurance read twice
//   enemyDef = 0.8 * ((0 + (GV(kArmorT1) / 2) / 2) + 2 * GV(kStatT, kEn)), an enemy attacker's view of the defence
//   root(D, stat) = 10 * sqrt(30 * P / (5 * D) * (GV(kStatA, stat) / 5)), P = GV(kPower) (P - 30 for a physical
//              skill where the slot says so); $f20 holds D while P is read (GV(kPower)'s bad-mode path returns it)
//   ratio(k, stat) = (k + GV(kStatA, stat)) / (k + GV(kStatT, stat))

}  // namespace

// 0x0030FDF0 datScriptGetValue -- 4996 bytes; frame 0x40: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// 0x30FDF0 datScriptGetValue(selector, index): datScript.c lines 190..459 (jump table 0x7B90A0). The unit selectors
// read gDatScriptAttacker (odd) / gDatScriptTarget (even) after a K_Assert on NULL. Out-of-range selectors, selector
// 0 and a bad gDatScriptMode for selector 19 assert and return the caller's $f20 (the compiled code never set it).
// Each case computes the value into $f20 (integer results through u32_to_float, the compiled unsigned conversion);
// the shared tail returns it in $f0. sel:: (battle_ai.h) names the selectors; s0 = index throughout.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void datScriptGetValue(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::addu, hg::charge, hg::cvt_s_w, hg::div, hg::div_s, hg::dsll32,
          hg::dsra32, hg::enter, hg::i64, hg::jal, hg::lbu, hg::ld, hg::lh, hg::lhu, hg::lq, hg::lw, hg::lwc1,
          hg::mflo, hg::mov_s, hg::mtc1, hg::sd, hg::si, hg::sll, hg::slt, hg::slti, hg::sltiu, hg::sq, hg::srl,
          hg::subu, hg::swc1, hg::tail;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f20{ctx, 20};
    // 0x0030fdf0: prologue (saves $f20 too); s0 = index; selector < 35?
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s0 = a1;
    at = sltiu(a0, ai::kSelectorCount);
    if (at != 0) {
        // 0x0030fe14: jump through the 35-entry table at 0x7B90A0
        charge(ctx, 7);
        v1 = hi(ai::kGetValueJumpTable);
        v1 = addiu(v1, lo(ai::kGetValueJumpTable));  // &tbl_datScriptGetValue_switch
        v0 = sll(a0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x30FE30u:  // selector 1: datCalcGetLevel(attacker)
            // 0x0030fe30
            charge(ctx, 4);
            v0 = hi(ai::kAttacker);
            lw(v0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
            if (v0 == 0) {
                // 0x0030fe40
                charge(ctx, 5);
                k_assert(a0, a1, 0x30FE4Cu, kDatScriptFile, 190);
            }
            // 0x0030fe54
            charge(ctx, 6);
            v0 = hi(ai::kAttacker);
            lw(a0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
            jal(ctx, 0x30FE5Cu, gen::fn_datCalcGetLevel_002ffcc0);
            u32_to_float(v0, v1, f0, f20);  // 0x0030fe80 / 0x0030fe6c
            // 0x0030fe9c
            charge(ctx, 2);
            break;
        case 0x30FEA4u:  // selector 2: datCalcGetLevel(target)
            // 0x0030fea4
            charge(ctx, 4);
            v0 = hi(ai::kTarget);
            lw(v0, v0, lo(ai::kTarget));  // gDatScriptTarget
            if (v0 == 0) {
                // 0x0030feb4
                charge(ctx, 5);
                k_assert(a0, a1, 0x30FEC0u, kDatScriptFile, 194);
            }
            // 0x0030fec8
            charge(ctx, 6);
            v0 = hi(ai::kTarget);
            lw(a0, v0, lo(ai::kTarget));  // gDatScriptTarget
            jal(ctx, 0x30FED0u, gen::fn_datCalcGetLevel_002ffcc0);
            u32_to_float(v0, v1, f0, f20);  // 0x0030fef4 / 0x0030fee0
            // 0x0030ff10
            charge(ctx, 2);
            break;
        case 0x30FF18u:  // selector 3: datCalcGetHp(attacker)
            // 0x0030ff18
            charge(ctx, 4);
            v0 = hi(ai::kAttacker);
            lw(v0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
            if (v0 == 0) {
                // 0x0030ff28
                charge(ctx, 5);
                k_assert(a0, a1, 0x30FF34u, kDatScriptFile, 198);
            }
            // 0x0030ff3c
            charge(ctx, 6);
            v0 = hi(ai::kAttacker);
            lw(a0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
            jal(ctx, 0x30FF44u, gen::fn_datCalcGetHp_002ffd70);
            u32_to_float(v0, v1, f0, f20);  // 0x0030ff68 / 0x0030ff54
            // 0x0030ff84
            charge(ctx, 2);
            break;
        case 0x30FF8Cu:  // selector 4: datCalcGetHp(target)
            // 0x0030ff8c
            charge(ctx, 4);
            v0 = hi(ai::kTarget);
            lw(v0, v0, lo(ai::kTarget));  // gDatScriptTarget
            if (v0 == 0) {
                // 0x0030ff9c
                charge(ctx, 5);
                k_assert(a0, a1, 0x30FFA8u, kDatScriptFile, 202);
            }
            // 0x0030ffb0
            charge(ctx, 6);
            v0 = hi(ai::kTarget);
            lw(a0, v0, lo(ai::kTarget));  // gDatScriptTarget
            jal(ctx, 0x30FFB8u, gen::fn_datCalcGetHp_002ffd70);
            u32_to_float(v0, v1, f0, f20);  // 0x0030ffdc / 0x0030ffc8
            // 0x0030fff8
            charge(ctx, 2);
            break;
        case 0x310000u:  // selector 5: datCalcGetMaxHp(attacker)
            // 0x00310000
            charge(ctx, 4);
            v0 = hi(ai::kAttacker);
            lw(v0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
            if (v0 == 0) {
                // 0x00310010
                charge(ctx, 5);
                k_assert(a0, a1, 0x31001Cu, kDatScriptFile, 206);
            }
            // 0x00310024
            charge(ctx, 6);
            v0 = hi(ai::kAttacker);
            lw(a0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
            jal(ctx, 0x31002Cu, gen::fn_datCalcGetMaxHp_002ffdf0);
            u32_to_float(v0, v1, f0, f20);  // 0x00310050 / 0x0031003c
            // 0x0031006c
            charge(ctx, 2);
            break;
        case 0x310074u:  // selector 6: datCalcGetMaxHp(target)
            // 0x00310074
            charge(ctx, 4);
            v0 = hi(ai::kTarget);
            lw(v0, v0, lo(ai::kTarget));  // gDatScriptTarget
            if (v0 == 0) {
                // 0x00310084
                charge(ctx, 5);
                k_assert(a0, a1, 0x310090u, kDatScriptFile, 210);
            }
            // 0x00310098
            charge(ctx, 6);
            v0 = hi(ai::kTarget);
            lw(a0, v0, lo(ai::kTarget));  // gDatScriptTarget
            jal(ctx, 0x3100A0u, gen::fn_datCalcGetMaxHp_002ffdf0);
            u32_to_float(v0, v1, f0, f20);  // 0x003100c4 / 0x003100b0
            // 0x003100e0
            charge(ctx, 2);
            break;
        case 0x3100E8u:  // selector 7: attacker->sp
            // 0x003100e8
            charge(ctx, 4);
            v0 = hi(ai::kAttacker);
            lw(v0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
            if (v0 == 0) {
                // 0x003100f8
                charge(ctx, 5);
                k_assert(a0, a1, 0x310104u, kDatScriptFile, 214);
            }
            // 0x0031010c
            charge(ctx, 5);
            v0 = hi(ai::kAttacker);
            lw(v0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
            lhu(v0, v0, dat_unit::kSp);
            u32_to_float(v0, v1, f0, f20);  // 0x00310134 / 0x00310120
            // 0x00310150
            charge(ctx, 2);
            break;
        case 0x310158u:  // selector 8: target->sp
            // 0x00310158
            charge(ctx, 4);
            v0 = hi(ai::kTarget);
            lw(v0, v0, lo(ai::kTarget));  // gDatScriptTarget
            if (v0 == 0) {
                // 0x00310168
                charge(ctx, 5);
                k_assert(a0, a1, 0x310174u, kDatScriptFile, 218);
            }
            // 0x0031017c
            charge(ctx, 5);
            v0 = hi(ai::kTarget);
            lw(v0, v0, lo(ai::kTarget));  // gDatScriptTarget
            lhu(v0, v0, dat_unit::kSp);
            u32_to_float(v0, v1, f0, f20);  // 0x003101a4 / 0x00310190
            // 0x003101c0
            charge(ctx, 2);
            break;
        case 0x3101C8u:  // selector 9: datCalcGetMaxSp(attacker)
            // 0x003101c8
            charge(ctx, 4);
            v0 = hi(ai::kAttacker);
            lw(v0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
            if (v0 == 0) {
                // 0x003101d8
                charge(ctx, 5);
                k_assert(a0, a1, 0x3101E4u, kDatScriptFile, 222);
            }
            // 0x003101ec
            charge(ctx, 6);
            v0 = hi(ai::kAttacker);
            lw(a0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
            jal(ctx, 0x3101F4u, gen::fn_datCalcGetMaxSp_00300100);
            u32_to_float(v0, v1, f0, f20);  // 0x00310218 / 0x00310204
            // 0x00310234
            charge(ctx, 2);
            break;
        case 0x31023Cu:  // selector 10: datCalcGetMaxSp(target)
            // 0x0031023c
            charge(ctx, 4);
            v0 = hi(ai::kTarget);
            lw(v0, v0, lo(ai::kTarget));  // gDatScriptTarget
            if (v0 == 0) {
                // 0x0031024c
                charge(ctx, 5);
                k_assert(a0, a1, 0x310258u, kDatScriptFile, 226);
            }
            // 0x00310260
            charge(ctx, 6);
            v0 = hi(ai::kTarget);
            lw(a0, v0, lo(ai::kTarget));  // gDatScriptTarget
            jal(ctx, 0x310268u, gen::fn_datCalcGetMaxSp_00300100);
            u32_to_float(v0, v1, f0, f20);  // 0x0031028c / 0x00310278
            // 0x003102a8
            charge(ctx, 2);
            break;
        case 0x3102B0u:  // selector 11: the attacker's affinity rate to the skill's element / 100
            // 0x003102b0
            charge(ctx, 4);
            v0 = hi(ai::kAttacker);
            lw(v0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
            if (v0 == 0) {
                // 0x003102c0
                charge(ctx, 5);
                k_assert(a0, a1, 0x3102CCu, kDatScriptFile, 230);
            }
            // 0x003102d4
            charge(ctx, 15);
            v0 = hi(ai::kAttacker);
            lw(a0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
            v0 = hi(ai::kSkill);
            lhu(a1, v0, lo(ai::kSkill));  // gDatScriptSkill
            jal(ctx, 0x3102E4u, gen::fn_datCalcGetSkillElement_003082f0);
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            v0 = hi(ai::kAttacker);
            lw(a0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
            jal(ctx, 0x3102FCu, gen::fn_datCalcGetAffinity_00306e80);
            v0 = v0 & 0xFFFF;
            u32_to_float(v0, v1, f0, f1);  // 0x00310324 / 0x00310310
            // 0x00310340
            charge(ctx, 9);
            v0 = flt(100.0f);
            mtc1(v0, f0);
            div_s(f20, f1, f0);
            break;
        case 0x310364u:  // selector 12: the target's affinity rate to the skill's element / 100
            // 0x00310364
            charge(ctx, 4);
            v0 = hi(ai::kAttacker);
            lw(v0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
            if (v0 == 0) {
                // 0x00310374
                charge(ctx, 5);
                k_assert(a0, a1, 0x310380u, kDatScriptFile, 236);
            }
            // 0x00310388
            charge(ctx, 4);
            v0 = hi(ai::kTarget);
            lw(v0, v0, lo(ai::kTarget));  // gDatScriptTarget
            if (v0 == 0) {
                // 0x00310398
                charge(ctx, 5);
                k_assert(a0, a1, 0x3103A4u, kDatScriptFile, 237);
            }
            // 0x003103ac
            charge(ctx, 15);
            v0 = hi(ai::kAttacker);
            lw(a0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
            v0 = hi(ai::kSkill);
            lhu(a1, v0, lo(ai::kSkill));  // gDatScriptSkill
            jal(ctx, 0x3103BCu, gen::fn_datCalcGetSkillElement_003082f0);
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            v0 = hi(ai::kTarget);
            lw(a0, v0, lo(ai::kTarget));  // gDatScriptTarget
            jal(ctx, 0x3103D4u, gen::fn_datCalcGetAffinity_00306e80);
            v0 = v0 & 0xFFFF;
            u32_to_float(v0, v1, f0, f1);  // 0x003103fc / 0x003103e8
            // 0x00310418
            charge(ctx, 9);
            v0 = flt(100.0f);
            mtc1(v0, f0);
            div_s(f20, f1, f0);
            break;
        case 0x31043Cu:  // selectors 15 / 16: the attacker's / target's affinity rate to the element of status gDatScriptMode / 100
        {
                // 0x0031043c
                charge(ctx, 3);
                v0 = 15;
                if (a0 != v0) {
                    // 0x00310458
                    charge(ctx, 2);
                    v0 = hi(ai::kTarget);
                    lw(s0, v0, lo(ai::kTarget));  // gDatScriptTarget
                } else {
                    // 0x00310448
                    charge(ctx, 4);
                    v0 = hi(ai::kAttacker);
                    lw(s0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
                }
                // 0x00310460
                charge(ctx, 11);
                v0 = hi(ai::kSkill);
                lh(a0, v0, lo(ai::kSkill));  // gDatScriptSkill
                v0 = hi(ai::kMode);
                lw(a1, v0, lo(ai::kMode));  // gDatScriptMode
                jal(ctx, 0x310470u, gen::fn_datCalcGetElementForStatus_00308120);
                s1 = dsll32(v0, 16);
                s1 = dsra32(s1, 16);
                v0 = slti(s1, 19);
                if (v0 == 0) {
                    // 0x0031048c
                    charge(ctx, 5);
                    k_assert(a0, a1, 0x310498u, kDatScriptFile, 252);
                }
                // 0x003104a0: elements 17, 16 and -1 (none) are rate 100, any other the unit's datCalcGetAffinity
                charge(ctx, 3);
                v0 = 17;
                bool neutral = s1 == v0;
                if (!neutral) {
                    // 0x003104ac
                    charge(ctx, 3);
                    v0 = 16;
                    neutral = s1 == v0;
                    if (!neutral) {
                        // 0x003104b8
                        charge(ctx, 3);
                        v0 = si(-1);
                        neutral = s1 == v0;
                    }
                }
                if (neutral) {
                    // 0x003104cc: rate 100
                    charge(ctx, 3);
                    v0 = 100;
                } else {
                    // 0x003104c4, 0x003104d8: datCalcGetAffinity(unit, element)
                    charge(ctx, 2);
                    charge(ctx, 4);
                    a0 = s0;
                    a1 = s1;
                    jal(ctx, 0x3104E0u, gen::fn_datCalcGetAffinity_00306e80);
                }
                // 0x003104e8: f20 = (float)(rate & 0xFFFF) / 100
                charge(ctx, 3);
                v0 = v0 & 0xFFFF;
                u32_to_float(v0, v1, f0, f1);  // 0x00310508 / 0x003104f4
                // 0x00310524
                charge(ctx, 9);
                v0 = flt(100.0f);
                mtc1(v0, f0);
                div_s(f20, f1, f0);
                break;
        }
        case 0x310548u:  // selector 13: datCalcGetStat(attacker, index)
            // 0x00310548
            charge(ctx, 3);
            v0 = slti(s0, 5);
            if (v0 == 0) {
                // 0x00310554
                charge(ctx, 5);
                k_assert(a0, a1, 0x310560u, kDatScriptFile, 272);
            }
            // 0x00310568
            charge(ctx, 4);
            v0 = hi(ai::kAttacker);
            lw(v0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
            if (v0 == 0) {
                // 0x00310578
                charge(ctx, 5);
                k_assert(a0, a1, 0x310584u, kDatScriptFile, 273);
            }
            // 0x0031058c
            charge(ctx, 7);
            a1 = s0 & 0xFFFF;
            v0 = hi(ai::kAttacker);
            lw(a0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
            jal(ctx, 0x310598u, gen::fn_datCalcGetStat_00300c90);
            u32_to_float(v0, v1, f0, f20);  // 0x003105bc / 0x003105a8
            // 0x003105d8
            charge(ctx, 2);
            break;
        case 0x3105E0u:  // selector 14: datCalcGetStat(target, index)
            // 0x003105e0
            charge(ctx, 3);
            v0 = slti(s0, 5);
            if (v0 == 0) {
                // 0x003105ec
                charge(ctx, 5);
                k_assert(a0, a1, 0x3105F8u, kDatScriptFile, 282);
            }
            // 0x00310600
            charge(ctx, 4);
            v0 = hi(ai::kTarget);
            lw(v0, v0, lo(ai::kTarget));  // gDatScriptTarget
            if (v0 == 0) {
                // 0x00310610
                charge(ctx, 5);
                k_assert(a0, a1, 0x31061Cu, kDatScriptFile, 283);
            }
            // 0x00310624
            charge(ctx, 7);
            a1 = s0 & 0xFFFF;
            v0 = hi(ai::kTarget);
            lw(a0, v0, lo(ai::kTarget));  // gDatScriptTarget
            jal(ctx, 0x310630u, gen::fn_datCalcGetStat_00300c90);
            u32_to_float(v0, v1, f0, f20);  // 0x00310654 / 0x00310640
            // 0x00310670
            charge(ctx, 2);
            break;
        case 0x310678u:  // selector 17: accuracy: the weapon's (physical skill) or SkillRecord +14
            // 0x00310678
            charge(ctx, 5);
            v0 = hi(ai::kSkill);
            lhu(v0, v0, lo(ai::kSkill));  // gDatScriptSkill
            v0 = slti(v0, btl::kSkillCount);
            if (v0 == 0) {
                // 0x0031068c
                charge(ctx, 5);
                k_assert(a0, a1, 0x310698u, kDatScriptFile, 287);
            }
            // 0x003106a0
            charge(ctx, 13);
            v0 = hi(ai::kSkill);
            lhu(v1, v0, lo(ai::kSkill));  // gDatScriptSkill
            v0 = sll(v1, 2);
            v0 = addu(v0, v1);
            v0 = sll(v0, 1);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
            v1 = addu(v0, v1);
            lbu(v0, v1, skill_rec::kFlags0);
            v0 = v0 & skill_rec::kFlagPhysical;
            if (v0 == 0) {
                // 0x0031074c
                charge(ctx, 3);
                lbu(v0, v1, skill_rec::kAccuracy);
                u32_to_float(v0, v1, f0, f20);  // 0x0031076c / 0x00310758
                // 0x00310788
                charge(ctx, 2);
            } else {
                // 0x003106d4
                charge(ctx, 4);
                v0 = hi(ai::kAttacker);
                lw(v0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
                if (v0 == 0) {
                    // 0x003106e4
                    charge(ctx, 5);
                    k_assert(a0, a1, 0x3106F0u, kDatScriptFile, 290);
                }
                // 0x003106f8
                charge(ctx, 7);
                v0 = hi(ai::kAttacker);
                lw(a0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
                a1 = 1;
                jal(ctx, 0x310704u, gen::fn_datCalcGetWeaponParam_00309080);
                u32_to_float(v0, v1, f0, f20);  // 0x00310728 / 0x00310714
                // 0x00310744
                charge(ctx, 2);
            }
            break;
        case 0x310790u:  // selector 18: SkillRecord +25, the status infliction rate
            // 0x00310790
            charge(ctx, 5);
            v0 = hi(ai::kSkill);
            lhu(v0, v0, lo(ai::kSkill));  // gDatScriptSkill
            v0 = slti(v0, btl::kSkillCount);
            if (v0 == 0) {
                // 0x003107a4
                charge(ctx, 5);
                k_assert(a0, a1, 0x3107B0u, kDatScriptFile, 297);
            }
            // 0x003107b8
            charge(ctx, 12);
            lw(a0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
            v0 = hi(ai::kSkill);
            lhu(v1, v0, lo(ai::kSkill));  // gDatScriptSkill
            v0 = sll(v1, 2);
            v0 = addu(v0, v1);
            v0 = sll(v0, 1);
            v0 = addu(v0, v1);
            v0 = sll(v0, 2);
            v0 = addu(v0, a0);
            lbu(v0, v0, skill_rec::kStatusRate);
            u32_to_float(v0, v1, f0, f20);  // 0x003107fc / 0x003107e8
            // 0x00310818
            charge(ctx, 2);
            break;
        case 0x310820u:  // selector 19: power: the weapon's (physical skill, kind 16) or SkillRecord +18 / +22 by gDatScriptMode
            // 0x00310820
            charge(ctx, 5);
            v0 = hi(ai::kSkill);
            lhu(v0, v0, lo(ai::kSkill));  // gDatScriptSkill
            v0 = slti(v0, btl::kSkillCount);
            if (v0 == 0) {
                // 0x00310834
                charge(ctx, 5);
                k_assert(a0, a1, 0x310840u, kDatScriptFile, 301);
            }
            // 0x00310848
            charge(ctx, 13);
            v0 = hi(ai::kSkill);
            lhu(v1, v0, lo(ai::kSkill));  // gDatScriptSkill
            v0 = sll(v1, 2);
            v0 = addu(v0, v1);
            v0 = sll(v0, 1);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
            a0 = addu(v0, v1);
            lbu(v0, a0, skill_rec::kFlags0);
            v0 = v0 & skill_rec::kFlagPhysical;
            if (v0 == 0) {
                // 0x0031087c: a magic skill: kind (+17) 16 takes the weapon's power too
                charge(ctx, 4);
                lbu(v1, a0, skill_rec::kHpFormula);
                v0 = 16;
                if (v1 != v0) {
                    // 0x00310904: power by gDatScriptMode: 1 = HP (s16 +18), 2 = SP (s16 +22), else K_Assert and
                    // return the caller's $f20
                    charge(ctx, 5);
                    v0 = hi(ai::kMode);
                    lw(v1, v0, lo(ai::kMode));  // gDatScriptMode
                    v0 = 1;
                    if (v1 != v0) {
                        // 0x00310930
                        charge(ctx, 3);
                        v0 = 2;
                        if (v1 != v0) {
                            // 0x00310954
                            charge(ctx, 7);
                            k_assert(a0, a1, 0x310960u, kDatScriptFile, 316);
                        } else {
                            // 0x0031093c
                            charge(ctx, 6);
                            lh(v0, a0, skill_rec::kSpBase);
                            mtc1(v0, f0);
                            cvt_s_w(f20, f0);
                        }
                    } else {
                        // 0x00310918
                        charge(ctx, 6);
                        lh(v0, a0, skill_rec::kHpBase);
                        mtc1(v0, f0);
                        cvt_s_w(f20, f0);
                    }
                    break;
                }
            }
            // 0x0031088c: a physical skill (or kind 16): datCalcGetWeaponParam(attacker, 0), the weapon's power
            charge(ctx, 4);
            v0 = hi(ai::kAttacker);
            lw(v0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
            if (v0 == 0) {
                // 0x0031089c
                charge(ctx, 5);
                k_assert(a0, a1, 0x3108A8u, kDatScriptFile, 305);
            }
            // 0x003108b0
            charge(ctx, 7);
            v0 = hi(ai::kAttacker);
            lw(a0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
            a1 = 0;
            jal(ctx, 0x3108BCu, gen::fn_datCalcGetWeaponParam_00309080);
            u32_to_float(v0, v1, f0, f20);  // 0x003108e0 / 0x003108cc
            // 0x003108fc
            charge(ctx, 2);
            break;
        case 0x310970u:  // selector 20: SkillRecord +37
            // 0x00310970
            charge(ctx, 5);
            v0 = hi(ai::kSkill);
            lhu(v0, v0, lo(ai::kSkill));  // gDatScriptSkill
            v0 = slti(v0, btl::kSkillCount);
            if (v0 == 0) {
                // 0x00310984
                charge(ctx, 5);
                k_assert(a0, a1, 0x310990u, kDatScriptFile, 321);
            }
            // 0x00310998
            charge(ctx, 12);
            lw(a0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
            v0 = hi(ai::kSkill);
            lhu(v1, v0, lo(ai::kSkill));  // gDatScriptSkill
            v0 = sll(v1, 2);
            v0 = addu(v0, v1);
            v0 = sll(v0, 1);
            v0 = addu(v0, v1);
            v0 = sll(v0, 2);
            v0 = addu(v0, a0);
            lbu(v0, v0, skill_rec::kByte37);
            u32_to_float(v0, v1, f0, f20);  // 0x003109dc / 0x003109c8
            // 0x003109f8
            charge(ctx, 2);
            break;
        case 0x310A00u:  // selector 21: SkillRecord +38
            // 0x00310a00
            charge(ctx, 5);
            v0 = hi(ai::kSkill);
            lhu(v0, v0, lo(ai::kSkill));  // gDatScriptSkill
            v0 = slti(v0, btl::kSkillCount);
            if (v0 == 0) {
                // 0x00310a14
                charge(ctx, 5);
                k_assert(a0, a1, 0x310A20u, kDatScriptFile, 325);
            }
            // 0x00310a28
            charge(ctx, 12);
            lw(a0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
            v0 = hi(ai::kSkill);
            lhu(v1, v0, lo(ai::kSkill));  // gDatScriptSkill
            v0 = sll(v1, 2);
            v0 = addu(v0, v1);
            v0 = sll(v0, 1);
            v0 = addu(v0, v1);
            v0 = sll(v0, 2);
            v0 = addu(v0, a0);
            lbu(v0, v0, skill_rec::kByte38);
            u32_to_float(v0, v1, f0, f20);  // 0x00310a6c / 0x00310a58
            // 0x00310a88
            charge(ctx, 2);
            break;
        case 0x310A90u:  // selector 22: the damage ceiling 31000
            // 0x00310a90
            charge(ctx, 6);
            v0 = 31000;
            mtc1(v0, f0);
            cvt_s_w(f20, f0);
            break;
        case 0x310AA8u:  // selector 23: AICALC0[clamp(lv_a - lv_t, -31, 31) + 31] (+63, the second row, outside a battle)
            // 0x00310aa8
            charge(ctx, 4);
            v0 = hi(ai::kAttacker);
            lw(v0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
            if (v0 == 0) {
                // 0x00310ab8
                charge(ctx, 5);
                k_assert(a0, a1, 0x310AC4u, kDatScriptFile, 332);
            }
            // 0x00310acc
            charge(ctx, 4);
            v0 = hi(ai::kTarget);
            lw(v0, v0, lo(ai::kTarget));  // gDatScriptTarget
            if (v0 == 0) {
                // 0x00310adc
                charge(ctx, 5);
                k_assert(a0, a1, 0x310AE8u, kDatScriptFile, 333);
            }
            // 0x00310af0
            charge(ctx, 22);
            v0 = hi(ai::kAttacker);
            lw(a0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
            jal(ctx, 0x310AF8u, gen::fn_datCalcGetLevel_002ffcc0);
            v0 = v0 & 0xFF;
            s0 = dsll32(v0, 16);
            s0 = dsra32(s0, 16);
            v0 = hi(ai::kTarget);
            lw(a0, v0, lo(ai::kTarget));  // gDatScriptTarget
            jal(ctx, 0x310B14u, gen::fn_datCalcGetLevel_002ffcc0);
            v0 = v0 & 0xFF;
            v1 = dsll32(v0, 16);
            v1 = dsra32(v1, 16);
            v0 = dsll32(s0, 16);
            v0 = dsra32(v0, 16);
            v0 = subu(v0, v1);
            v1 = dsll32(v0, 16);
            v1 = dsra32(v1, 16);
            at = slti(v1, -31);
            if (at == 0) {
                // 0x00310b54
                charge(ctx, 3);
                at = slti(v1, 32);
                if (at == 0) {
                    // 0x00310b60
                    charge(ctx, 1);
                    v1 = 31;
                }
            } else {
                // 0x00310b48
                charge(ctx, 3);
                v1 = si(-31);
            }
            // 0x00310b64
            charge(ctx, 3);
            lw(v0, gp, gp_off(btl::kBtlPtr));  // 0x7CE3EC
            if (v0 == 0) {
                // 0x00310b9c
                charge(ctx, 11);
                v0 = dsll32(v1, 16);
                v0 = dsra32(v0, 16);
                v0 = addiu(v0, kAiCalc0Row2 + 31);  // the second row (63 + 31)
                v0 = dsll32(v0, 16);
                v0 = dsra32(v0, 16);
                v1 = sll(v0, 2);
                lw(v0, gp, gp_off(ai::kAiCalc0Ptr));  // 0x7CE46C
                v0 = addu(v0, v1);
                lwc1(f20, v0, 0);
            } else {
                // 0x00310b70
                charge(ctx, 11);
                v0 = dsll32(v1, 16);
                v0 = dsra32(v0, 16);
                v0 = addiu(v0, 31);  // the in-battle row
                v0 = dsll32(v0, 16);
                v0 = dsra32(v0, 16);
                v1 = sll(v0, 2);
                lw(v0, gp, gp_off(ai::kAiCalc0Ptr));  // 0x7CE46C
                v0 = addu(v0, v1);
                lwc1(f20, v0, 0);
            }
            break;
        case 0x310BC8u:  // selector 24: AICALC1[clamp((lv_a - lv_t -/+ 1) / 3, -6, 6) + 6]
            // 0x00310bc8
            charge(ctx, 4);
            v0 = hi(ai::kAttacker);
            lw(v0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
            if (v0 == 0) {
                // 0x00310bd8
                charge(ctx, 5);
                k_assert(a0, a1, 0x310BE4u, kDatScriptFile, 370);
            }
            // 0x00310bec
            charge(ctx, 4);
            v0 = hi(ai::kTarget);
            lw(v0, v0, lo(ai::kTarget));  // gDatScriptTarget
            if (v0 == 0) {
                // 0x00310bfc
                charge(ctx, 5);
                k_assert(a0, a1, 0x310C08u, kDatScriptFile, 371);
            }
            // 0x00310c10
            charge(ctx, 19);
            v0 = hi(ai::kAttacker);
            lw(a0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
            jal(ctx, 0x310C18u, gen::fn_datCalcGetLevel_002ffcc0);
            v0 = v0 & 0xFF;
            s0 = dsll32(v0, 16);
            s0 = dsra32(s0, 16);
            v0 = hi(ai::kTarget);
            lw(a0, v0, lo(ai::kTarget));  // gDatScriptTarget
            jal(ctx, 0x310C34u, gen::fn_datCalcGetLevel_002ffcc0);
            v0 = v0 & 0xFF;
            v1 = dsll32(v0, 16);
            v1 = dsra32(v1, 16);
            v0 = dsll32(s0, 16);
            v0 = dsra32(v0, 16);
            at = slt(v1, v0);
            if (at == 0) {
                // 0x00310c74
                charge(ctx, 4);
                v0 = subu(v0, v1);
                v0 = addiu(v0, 1);
                a0 = dsll32(v0, 16);
                a0 = dsra32(a0, 16);
            } else {
                // 0x00310c5c
                charge(ctx, 6);
                v0 = subu(v0, v1);
                v0 = addiu(v0, -1);
                a0 = dsll32(v0, 16);
                a0 = dsra32(a0, 16);
            }
            // 0x00310c84
            charge(ctx, 8);
            v0 = 3;
            div(a0, v0);
            mflo(v0);
            a0 = dsll32(v0, 16);
            a0 = dsra32(a0, 16);
            at = slti(a0, -6);
            if (at == 0) {
                // 0x00310cb0
                charge(ctx, 3);
                at = slti(a0, 7);
                if (at == 0) {
                    // 0x00310cbc
                    charge(ctx, 1);
                    a0 = 6;
                }
            } else {
                // 0x00310ca4
                charge(ctx, 3);
                a0 = si(-6);
            }
            // 0x00310cc0
            charge(ctx, 8);
            lw(v1, gp, gp_off(ai::kAiCalc1Ptr));  // 0x7CE470
            v0 = dsll32(a0, 16);
            v0 = dsra32(v0, 16);
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lwc1(f20, v0, 6 * 4);  // AICALC1[d + 6]
            break;
        case 0x310CE0u:  // selector 25: AICALC3[min(Ma / 10, 9)] (s16)
            // 0x00310ce0
            charge(ctx, 4);
            v0 = hi(ai::kAttacker);
            lw(v0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
            if (v0 == 0) {
                // 0x00310cf0
                charge(ctx, 5);
                k_assert(a0, a1, 0x310CFCu, kDatScriptFile, 389);
            }
            // 0x00310d04
            charge(ctx, 16);
            v0 = hi(ai::kAttacker);
            lw(a0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
            a1 = 1;
            jal(ctx, 0x310D10u, gen::fn_datCalcGetStat_00300c90);
            v0 = v0 & 0xFF;
            v1 = dsll32(v0, 16);
            v1 = dsra32(v1, 16);
            v0 = 10;
            div(v1, v0);
            mflo(v0);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
            at = slti(v0, 10);
            if (at == 0) {
                // 0x00310d44
                charge(ctx, 1);
                v0 = 9;
            }
            // 0x00310d48
            charge(ctx, 11);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
            v1 = sll(v0, 1);
            lw(v0, gp, gp_off(ai::kAiCalc3Ptr));  // 0x7CE478
            v0 = addu(v0, v1);
            lh(v0, v0, 0);
            mtc1(v0, f0);
            cvt_s_w(f20, f0);
            break;
        case 0x310D74u:  // selector 26: AICALC4[min(Ma / 5, 20)] (s16)
            // 0x00310d74
            charge(ctx, 4);
            v0 = hi(ai::kAttacker);
            lw(v0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
            if (v0 == 0) {
                // 0x00310d84
                charge(ctx, 5);
                k_assert(a0, a1, 0x310D90u, kDatScriptFile, 397);
            }
            // 0x00310d98
            charge(ctx, 16);
            v0 = hi(ai::kAttacker);
            lw(a0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
            a1 = 1;
            jal(ctx, 0x310DA4u, gen::fn_datCalcGetStat_00300c90);
            v0 = v0 & 0xFF;
            v1 = dsll32(v0, 16);
            v1 = dsra32(v1, 16);
            v0 = 5;
            div(v1, v0);
            mflo(v0);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
            at = slti(v0, 21);
            if (at == 0) {
                // 0x00310dd8
                charge(ctx, 1);
                v0 = 20;
            }
            // 0x00310ddc
            charge(ctx, 11);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
            v1 = sll(v0, 1);
            lw(v0, gp, gp_off(ai::kAiCalc4Ptr));  // 0x7CE47C
            v0 = addu(v0, v1);
            lh(v0, v0, 0);
            mtc1(v0, f0);
            cvt_s_w(f20, f0);
            break;
        case 0x310E08u:  // selector 27: gBtl round + 1
            // 0x00310e08
            charge(ctx, 8);
            lw(v0, gp, gp_off(btl::kBtlPtr));  // 0x7CE3EC
            lhu(v0, v0, btl_root::kRound);
            v0 = addiu(v0, 1);
            mtc1(v0, f0);
            cvt_s_w(f20, f0);
            break;
        case 0x310E28u:  // selector 28: gDatScriptResult as a float
            // 0x00310e28
            charge(ctx, 5);
            v0 = hi(ai::kResult);
            lwc1(f0, v0, lo(ai::kResult));  // gDatScriptResult
            cvt_s_w(f20, f0);
            break;
        case 0x310E3Cu:  // selector 29: datCalcGetArmorParam(attacker, 0)
            // 0x00310e3c
            charge(ctx, 4);
            v0 = hi(ai::kAttacker);
            lw(v0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
            if (v0 == 0) {
                // 0x00310e4c
                charge(ctx, 5);
                k_assert(a0, a1, 0x310E58u, kDatScriptFile, 411);
            }
            // 0x00310e60
            charge(ctx, 7);
            v0 = hi(ai::kAttacker);
            lw(a0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
            a1 = 0;
            jal(ctx, 0x310E6Cu, gen::fn_datCalcGetArmorParam_00309250);
            u32_to_float(v0, v1, f0, f20);  // 0x00310e90 / 0x00310e7c
            // 0x00310eac
            charge(ctx, 2);
            break;
        case 0x310EB4u:  // selector 30: datCalcGetArmorParam(attacker, 1)
            // 0x00310eb4
            charge(ctx, 4);
            v0 = hi(ai::kAttacker);
            lw(v0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
            if (v0 == 0) {
                // 0x00310ec4
                charge(ctx, 5);
                k_assert(a0, a1, 0x310ED0u, kDatScriptFile, 415);
            }
            // 0x00310ed8
            charge(ctx, 7);
            v0 = hi(ai::kAttacker);
            lw(a0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
            a1 = 1;
            jal(ctx, 0x310EE4u, gen::fn_datCalcGetArmorParam_00309250);
            u32_to_float(v0, v1, f0, f20);  // 0x00310f08 / 0x00310ef4
            // 0x00310f24
            charge(ctx, 2);
            break;
        case 0x310F2Cu:  // selector 31: datCalcGetArmorParam(target, 0)
            // 0x00310f2c
            charge(ctx, 4);
            v0 = hi(ai::kTarget);
            lw(v0, v0, lo(ai::kTarget));  // gDatScriptTarget
            if (v0 == 0) {
                // 0x00310f3c
                charge(ctx, 5);
                k_assert(a0, a1, 0x310F48u, kDatScriptFile, 419);
            }
            // 0x00310f50
            charge(ctx, 7);
            v0 = hi(ai::kTarget);
            lw(a0, v0, lo(ai::kTarget));  // gDatScriptTarget
            a1 = 0;
            jal(ctx, 0x310F5Cu, gen::fn_datCalcGetArmorParam_00309250);
            u32_to_float(v0, v1, f0, f20);  // 0x00310f80 / 0x00310f6c
            // 0x00310f9c
            charge(ctx, 2);
            break;
        case 0x310FA4u:  // selector 32: datCalcGetArmorParam(target, 1)
            // 0x00310fa4
            charge(ctx, 4);
            v0 = hi(ai::kTarget);
            lw(v0, v0, lo(ai::kTarget));  // gDatScriptTarget
            if (v0 == 0) {
                // 0x00310fb4
                charge(ctx, 5);
                k_assert(a0, a1, 0x310FC0u, kDatScriptFile, 423);
            }
            // 0x00310fc8
            charge(ctx, 7);
            v0 = hi(ai::kTarget);
            lw(a0, v0, lo(ai::kTarget));  // gDatScriptTarget
            a1 = 1;
            jal(ctx, 0x310FD4u, gen::fn_datCalcGetArmorParam_00309250);
            u32_to_float(v0, v1, f0, f20);  // 0x00310ff8 / 0x00310fe4
            // 0x00311014
            charge(ctx, 2);
            break;
        case 0x31101Cu:  // selector 33: AICALC0[clamp(lv_a - lv_t, -31, 31) + 31], the in-battle row whatever gBtl is
            // 0x0031101c
            charge(ctx, 4);
            v0 = hi(ai::kAttacker);
            lw(v0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
            if (v0 == 0) {
                // 0x0031102c
                charge(ctx, 5);
                k_assert(a0, a1, 0x311038u, kDatScriptFile, 427);
            }
            // 0x00311040
            charge(ctx, 4);
            v0 = hi(ai::kTarget);
            lw(v0, v0, lo(ai::kTarget));  // gDatScriptTarget
            if (v0 == 0) {
                // 0x00311050
                charge(ctx, 5);
                k_assert(a0, a1, 0x31105Cu, kDatScriptFile, 428);
            }
            // 0x00311064
            charge(ctx, 22);
            v0 = hi(ai::kAttacker);
            lw(a0, v0, lo(ai::kAttacker));  // gDatScriptAttacker
            jal(ctx, 0x31106Cu, gen::fn_datCalcGetLevel_002ffcc0);
            v0 = v0 & 0xFF;
            s0 = dsll32(v0, 16);
            s0 = dsra32(s0, 16);
            v0 = hi(ai::kTarget);
            lw(a0, v0, lo(ai::kTarget));  // gDatScriptTarget
            jal(ctx, 0x311088u, gen::fn_datCalcGetLevel_002ffcc0);
            v0 = v0 & 0xFF;
            v1 = dsll32(v0, 16);
            v1 = dsra32(v1, 16);
            v0 = dsll32(s0, 16);
            v0 = dsra32(v0, 16);
            v0 = subu(v0, v1);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
            at = slti(v0, -31);
            if (at == 0) {
                // 0x003110c8
                charge(ctx, 3);
                at = slti(v0, 32);
                if (at == 0) {
                    // 0x003110d4
                    charge(ctx, 1);
                    v0 = 31;
                }
            } else {
                // 0x003110bc
                charge(ctx, 3);
                v0 = si(-31);
            }
            // 0x003110d8
            charge(ctx, 8);
            lw(v1, gp, gp_off(ai::kAiCalc0Ptr));  // 0x7CE46C
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lwc1(f20, v0, 31 * 4);  // AICALC0[d + 31]
            break;
        case 0x3110F8u:  // selector 34: gBtl +0xB9E
            // 0x003110f8
            charge(ctx, 4);
            lw(v0, gp, gp_off(btl::kBtlPtr));  // 0x7CE3EC
            lhu(v0, v0, btl_root::kB9E);
            u32_to_float(v0, v1, f0, f20);  // 0x0031111c / 0x00311108
            // 0x00311138
            charge(ctx, 2);
            break;
        case 0x311140u:  // selector 0: K_Assert (line 459); returns the caller's $f20
            charge(ctx, 5);
            k_assert(a0, a1, 0x31114Cu, kDatScriptFile, 459);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
    } else {
        // 0x00311140: selector >= 35: K_Assert (line 459); returns the caller's $f20
        charge(ctx, 5);
        k_assert(a0, a1, 0x31114Cu, kDatScriptFile, 459);
    }
    // 0x00311154: return f20 in $f0; epilogue (restores the caller's $f20)
    charge(ctx, 8);
    mov_s(f0, f20);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0030FC40 datScriptCalc -- 380 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// datScriptCalc(fn, attacker, target, skill, mode): the context words, the "result set" bit cleared, entry `fn` of
// sDatScriptFuncTbl2 (flag 0x1311) / Tbl3 (flag 0x1319) / Tbl1 called through the dispatch table (lines 139/144/147
// assert fn < 17 and continue), the result bit asserted (line 155), gDatScriptResult returned.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void datScriptCalc(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::jalr, hg::ld, hg::lhu, hg::lq, hg::lw,
          hg::sd, hg::sh, hg::sll, hg::sltiu, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0030fc40: prologue; s0 = fn; the context: skill, attacker, target, mode; flags &= ~result-set
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    v0 = hi(ai::kSkill);
    sh(a3, v0, lo(ai::kSkill));
    v0 = hi(ai::kAttacker);
    sw(a1, v0, lo(ai::kAttacker));
    v0 = hi(ai::kTarget);
    sw(a2, v0, lo(ai::kTarget));
    v0 = hi(ai::kMode);
    sw(t0, v0, lo(ai::kMode));
    v0 = hi(ai::kFlags);
    lhu(v0, v0, lo(ai::kFlags));
    v1 = v0 & 0xFFFE;
    v0 = hi(ai::kFlags);
    sh(v1, v0, lo(ai::kFlags));
    // which table: datGetFlag(0x1311) -> set 2
    a0 = ai::kFlagTable2;
    jal(ctx, 0x30FC88u, gen::fn_datGetFlag_0016f190);
    v1 = 1;
    if (v0 != v1) {
        // 0x0030fce0: datGetFlag(0x1319) -> set 3
        charge(ctx, 6);
        a0 = ai::kFlagTable3;
        jal(ctx, 0x30FCE4u, gen::fn_datGetFlag_0016f190);
        v1 = 1;
        if (v0 != v1) {
            // 0x0030fd3c: set 1: K_Assert(fn < 17)
            charge(ctx, 3);
            v0 = sltiu(s0, ai::kFuncCount);
            if (v0 == 0) {
                // 0x0030fd48
                charge(ctx, 5);
                k_assert(a0, a1, 0x30FD54u, kDatScriptFile, 147);
            }
            // 0x0030fd5c: sDatScriptFuncTbl1[fn]() through jalr
            charge(ctx, 7);
            v1 = sll(s0, 2);
            v0 = hi(ai::kFuncTbl1);
            v0 = addiu(v0, lo(ai::kFuncTbl1));
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            jalr(ctx, 0x30FD70u, v0.u());
        } else {
            // 0x0030fcf8: set 3: K_Assert(fn < 17)
            charge(ctx, 3);
            v0 = sltiu(s0, ai::kFuncCount);
            if (v0 == 0) {
                // 0x0030fd04
                charge(ctx, 5);
                k_assert(a0, a1, 0x30FD10u, kDatScriptFile, 144);
            }
            // 0x0030fd18: sDatScriptFuncTbl3[fn]()
            charge(ctx, 9);
            v1 = sll(s0, 2);
            v0 = hi(ai::kFuncTbl3);
            v0 = addiu(v0, lo(ai::kFuncTbl3));
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            jalr(ctx, 0x30FD2Cu, v0.u());
        }
    } else {
        // 0x0030fc9c: set 2: K_Assert(fn < 17)
        charge(ctx, 3);
        v0 = sltiu(s0, ai::kFuncCount);
        if (v0 == 0) {
            // 0x0030fca8
            charge(ctx, 5);
            k_assert(a0, a1, 0x30FCB4u, kDatScriptFile, 139);
        }
        // 0x0030fcbc: sDatScriptFuncTbl2[fn]()
        charge(ctx, 9);
        v1 = sll(s0, 2);
        v0 = hi(ai::kFuncTbl2);
        v0 = addiu(v0, lo(ai::kFuncTbl2));
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        jalr(ctx, 0x30FCD0u, v0.u());
    }
    // 0x0030fd78: K_Assert(the formula set a result)
    charge(ctx, 5);
    v0 = hi(ai::kFlags);
    lhu(v0, v0, lo(ai::kFlags));
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x0030fd8c
        charge(ctx, 5);
        k_assert(a0, a1, 0x30FD98u, kDatScriptFile, 155);
    }
    // 0x0030fda0: return gDatScriptResult; epilogue
    charge(ctx, 7);
    v0 = hi(ai::kResult);
    lw(v0, v0, lo(ai::kResult));
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// --- the 51 table entries -----------------------------------------------------------------------------------------
void nullsub_62(EEContext& ctx) { guest::enter(ctx, 2); }
void nullsub_63(EEContext& ctx) { guest::enter(ctx, 2); }
void nullsub_64(EEContext& ctx) { guest::enter(ctx, 2); }

// 0x0030C520 sub_30C520 [datScriptAiDamage1] -- 1028 bytes; frame 0x20: ra sp+0x10, f20 sp+0x0
// Set 1 slot 1 (sDatScriptFuncTbl1[1]): Attack damage. Physical skill: party attacker root(En2, St) with P - 30, *
// GV(kAffinityT) * GV(kLevelDiff);
// enemy attacker 0.9 * (root(enemyDef, St) * GV(kAffinityT) * GV(kLevelDiff)). Magic skill: party attacker
// root(En2, St) * GV(kAffinityT) * GV(kLevelDiff); enemy attacker (root(enemyDef, St) * GV(kLevelDiff) * 0.9 - 10)
// * GV(kAffinityT).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30C520(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::adda_s, hg::addiu, hg::charge, hg::cvt_w_s, hg::div_s, hg::enter, hg::jal,
          hg::ld, hg::lwc1, hg::madd_s, hg::mfc1, hg::mov_s, hg::mtc1, hg::mul_s, hg::sd, hg::sqrt_s, hg::sub_s,
          hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20};
    // 0x0030c520: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f20, sp, 0x0);
    jal(ctx, 0x30C52Cu, gen::fn_sub_311250_00311250);  // the skill is physical?
    if (v0 == 0) {
        // 0x0030c71c: a magic skill
        charge(ctx, 4);
        jal(ctx, 0x30C71Cu, gen::fn_sub_3111F0_003111f0);  // the attacker is a party member?
        if (v0 == 0) {
            // 0x0030c7f4: an enemy attacker
            charge(ctx, 67);
            // f20 = enemyDef = 0.8 * ((0 + GV(kArmorT1) / 2 / 2) + 2 * GV(kStatT, kEn))
            get_value(a0, a1, 0x30C7FCu, sel::kArmorT1, 0);
            v0 = flt(2.0f);
            mtc1(v0, f1);
            div_s(f20, f0, f1);
            get_value(a0, a1, 0x30C820u, sel::kStatT, sel::kEn);
            v0 = flt(2.0f);
            mtc1(v0, f3);
            div_s(f2, f20, f3);
            mtc1(zero, f1);
            adda_s(f1, f2);
            madd_s(f1, f3, f0);
            lwc1(f0, gp, gp_off(ai::kLit0_80));  // 0.8
            mul_s(f20, f0, f1);
            // f20 = root(f20, stat) = 10 * sqrt(30 * P / (5 * f20) * (GV(kStatA, stat) / 5)), P = GV(kPower)
            get_value(a0, a1, 0x30C858u, sel::kPower, 0);
            v0 = flt(30.0f);
            mtc1(v0, f1);
            mul_s(f1, f1, f0);
            v0 = flt(5.0f);
            mtc1(v0, f0);
            mul_s(f0, f0, f20);
            div_s(f20, f1, f0);
            get_value(a0, a1, 0x30C890u, sel::kStatA, sel::kSt);
            v0 = flt(5.0f);
            mtc1(v0, f1);
            div_s(f0, f0, f1);
            mul_s(f0, f20, f0);
            sqrt_s(f1, f0);
            v0 = flt(10.0f);
            mtc1(v0, f0);
            mul_s(f20, f0, f1);
            get_value(a0, a1, 0x30C8C8u, sel::kLevelDiff, 0);
            mul_s(f1, f20, f0);
            lwc1(f0, gp, gp_off(ai::kLit0_90));  // 0.9
            mul_s(f1, f1, f0);
            v0 = flt(10.0f);
            mtc1(v0, f0);
            sub_s(f20, f1, f0);
            get_value(a0, a1, 0x30C8F4u, sel::kAffinityT, 0);
            mul_s(f20, f20, f0);
        } else {
            // 0x0030c72c: a party attacker
            charge(ctx, 50);
            // f20 = En2 = GV(kStatT, kEn) + GV(kStatT, kEn)
            get_value(a0, a1, 0x30C734u, sel::kStatT, sel::kEn);
            mov_s(f20, f0);
            get_value(a0, a1, 0x30C748u, sel::kStatT, sel::kEn);
            add_s(f20, f20, f0);
            // f20 = root(f20, stat) = 10 * sqrt(30 * P / (5 * f20) * (GV(kStatA, stat) / 5)), P = GV(kPower)
            get_value(a0, a1, 0x30C75Cu, sel::kPower, 0);
            v0 = flt(30.0f);
            mtc1(v0, f1);
            mul_s(f1, f1, f0);
            v0 = flt(5.0f);
            mtc1(v0, f0);
            mul_s(f0, f0, f20);
            div_s(f20, f1, f0);
            get_value(a0, a1, 0x30C794u, sel::kStatA, sel::kSt);
            v0 = flt(5.0f);
            mtc1(v0, f1);
            div_s(f0, f0, f1);
            mul_s(f0, f20, f0);
            sqrt_s(f1, f0);
            v0 = flt(10.0f);
            mtc1(v0, f0);
            mul_s(f20, f0, f1);
            get_value(a0, a1, 0x30C7CCu, sel::kAffinityT, 0);
            mul_s(f20, f20, f0);
            get_value(a0, a1, 0x30C7E0u, sel::kLevelDiff, 0);
            mul_s(f20, f20, f0);
        }
    } else {
        // 0x0030c53c: a physical skill
        charge(ctx, 4);
        jal(ctx, 0x30C53Cu, gen::fn_sub_3111F0_003111f0);  // the attacker is a party member?
        if (v0 == 0) {
            // 0x0030c618: an enemy attacker
            charge(ctx, 65);
            // f20 = enemyDef = 0.8 * ((0 + GV(kArmorT1) / 2 / 2) + 2 * GV(kStatT, kEn))
            get_value(a0, a1, 0x30C620u, sel::kArmorT1, 0);
            v0 = flt(2.0f);
            mtc1(v0, f1);
            div_s(f20, f0, f1);
            get_value(a0, a1, 0x30C644u, sel::kStatT, sel::kEn);
            v0 = flt(2.0f);
            mtc1(v0, f3);
            div_s(f2, f20, f3);
            mtc1(zero, f1);
            adda_s(f1, f2);
            madd_s(f1, f3, f0);
            lwc1(f0, gp, gp_off(ai::kLit0_80));  // 0.8
            mul_s(f20, f0, f1);
            // f20 = root(f20, stat) = 10 * sqrt(30 * P / (5 * f20) * (GV(kStatA, stat) / 5)), P = GV(kPower)
            get_value(a0, a1, 0x30C67Cu, sel::kPower, 0);
            v0 = flt(30.0f);
            mtc1(v0, f1);
            mul_s(f1, f1, f0);
            v0 = flt(5.0f);
            mtc1(v0, f0);
            mul_s(f0, f0, f20);
            div_s(f20, f1, f0);
            get_value(a0, a1, 0x30C6B4u, sel::kStatA, sel::kSt);
            v0 = flt(5.0f);
            mtc1(v0, f1);
            div_s(f0, f0, f1);
            mul_s(f0, f20, f0);
            sqrt_s(f1, f0);
            v0 = flt(10.0f);
            mtc1(v0, f0);
            mul_s(f20, f0, f1);
            get_value(a0, a1, 0x30C6ECu, sel::kAffinityT, 0);
            mul_s(f20, f20, f0);
            get_value(a0, a1, 0x30C700u, sel::kLevelDiff, 0);
            mul_s(f1, f20, f0);
            lwc1(f0, gp, gp_off(ai::kLit0_90));  // 0.9
            mul_s(f20, f0, f1);
        } else {
            // 0x0030c54c: a party attacker
            charge(ctx, 51);
            // f20 = En2 = GV(kStatT, kEn) + GV(kStatT, kEn)
            get_value(a0, a1, 0x30C554u, sel::kStatT, sel::kEn);
            mov_s(f20, f0);
            get_value(a0, a1, 0x30C568u, sel::kStatT, sel::kEn);
            add_s(f20, f20, f0);
            // f20 = root(f20, stat) = 10 * sqrt(30 * P / (5 * f20) * (GV(kStatA, stat) / 5)), P = GV(kPower)
            get_value(a0, a1, 0x30C57Cu, sel::kPower, 0);
            v0 = flt(30.0f);
            mtc1(v0, f1);
            sub_s(f0, f0, f1);
            mul_s(f1, f1, f0);
            v0 = flt(5.0f);
            mtc1(v0, f0);
            mul_s(f0, f0, f20);
            div_s(f20, f1, f0);
            get_value(a0, a1, 0x30C5B8u, sel::kStatA, sel::kSt);
            v0 = flt(5.0f);
            mtc1(v0, f1);
            div_s(f0, f0, f1);
            mul_s(f0, f20, f0);
            sqrt_s(f1, f0);
            v0 = flt(10.0f);
            mtc1(v0, f0);
            mul_s(f20, f0, f1);
            get_value(a0, a1, 0x30C5F0u, sel::kAffinityT, 0);
            mul_s(f20, f20, f0);
            get_value(a0, a1, 0x30C604u, sel::kLevelDiff, 0);
            mul_s(f20, f20, f0);
        }
    }
    // 0x0030c900: the result; epilogue
    charge(ctx, 9);
    cvt_w_s(f0, f20);
    mfc1(a0, f0);
    jal(ctx, 0x30C908u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030D760 sub_30D760 [datScriptAiDamage2] -- 1044 bytes; frame 0x20: ra sp+0x10, f20 sp+0x0
// Set 2 slot 1 (sDatScriptFuncTbl2[1]): Attack damage. Physical skill: party attacker root(En2, St) with P - 30, *
// GV(kAffinityT) * GV(kLevelDiff), times 1.3;
// enemy attacker 0.6 * (root(enemyDef, St) * GV(kAffinityT) * GV(kLevelDiff)). Magic skill: party attacker
// root(En2, St) * GV(kAffinityT) * GV(kLevelDiff), times 1.3; enemy attacker (root(enemyDef, St) * GV(kLevelDiff) *
// 0.6 - 10)
// * GV(kAffinityT).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30D760(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::adda_s, hg::addiu, hg::charge, hg::cvt_w_s, hg::div_s, hg::enter, hg::jal,
          hg::ld, hg::lwc1, hg::madd_s, hg::mfc1, hg::mov_s, hg::mtc1, hg::mul_s, hg::sd, hg::sqrt_s, hg::sub_s,
          hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20};
    // 0x0030d760: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f20, sp, 0x0);
    jal(ctx, 0x30D76Cu, gen::fn_sub_311250_00311250);  // the skill is physical?
    if (v0 == 0) {
        // 0x0030d964: a magic skill
        charge(ctx, 4);
        jal(ctx, 0x30D964u, gen::fn_sub_3111F0_003111f0);  // the attacker is a party member?
        if (v0 == 0) {
            // 0x0030da44: an enemy attacker
            charge(ctx, 67);
            // f20 = enemyDef = 0.8 * ((0 + GV(kArmorT1) / 2 / 2) + 2 * GV(kStatT, kEn))
            get_value(a0, a1, 0x30DA4Cu, sel::kArmorT1, 0);
            v0 = flt(2.0f);
            mtc1(v0, f1);
            div_s(f20, f0, f1);
            get_value(a0, a1, 0x30DA70u, sel::kStatT, sel::kEn);
            v0 = flt(2.0f);
            mtc1(v0, f3);
            div_s(f2, f20, f3);
            mtc1(zero, f1);
            adda_s(f1, f2);
            madd_s(f1, f3, f0);
            lwc1(f0, gp, gp_off(ai::kLit0_80));  // 0.8
            mul_s(f20, f0, f1);
            // f20 = root(f20, stat) = 10 * sqrt(30 * P / (5 * f20) * (GV(kStatA, stat) / 5)), P = GV(kPower)
            get_value(a0, a1, 0x30DAA8u, sel::kPower, 0);
            v0 = flt(30.0f);
            mtc1(v0, f1);
            mul_s(f1, f1, f0);
            v0 = flt(5.0f);
            mtc1(v0, f0);
            mul_s(f0, f0, f20);
            div_s(f20, f1, f0);
            get_value(a0, a1, 0x30DAE0u, sel::kStatA, sel::kSt);
            v0 = flt(5.0f);
            mtc1(v0, f1);
            div_s(f0, f0, f1);
            mul_s(f0, f20, f0);
            sqrt_s(f1, f0);
            v0 = flt(10.0f);
            mtc1(v0, f0);
            mul_s(f20, f0, f1);
            get_value(a0, a1, 0x30DB18u, sel::kLevelDiff, 0);
            mul_s(f1, f20, f0);
            lwc1(f0, gp, gp_off(ai::kLit0_60));  // 0.6
            mul_s(f1, f1, f0);
            v0 = flt(10.0f);
            mtc1(v0, f0);
            sub_s(f20, f1, f0);
            get_value(a0, a1, 0x30DB44u, sel::kAffinityT, 0);
            mul_s(f20, f20, f0);
        } else {
            // 0x0030d974: a party attacker
            charge(ctx, 52);
            // f20 = En2 = GV(kStatT, kEn) + GV(kStatT, kEn)
            get_value(a0, a1, 0x30D97Cu, sel::kStatT, sel::kEn);
            mov_s(f20, f0);
            get_value(a0, a1, 0x30D990u, sel::kStatT, sel::kEn);
            add_s(f20, f20, f0);
            // f20 = root(f20, stat) = 10 * sqrt(30 * P / (5 * f20) * (GV(kStatA, stat) / 5)), P = GV(kPower)
            get_value(a0, a1, 0x30D9A4u, sel::kPower, 0);
            v0 = flt(30.0f);
            mtc1(v0, f1);
            mul_s(f1, f1, f0);
            v0 = flt(5.0f);
            mtc1(v0, f0);
            mul_s(f0, f0, f20);
            div_s(f20, f1, f0);
            get_value(a0, a1, 0x30D9DCu, sel::kStatA, sel::kSt);
            v0 = flt(5.0f);
            mtc1(v0, f1);
            div_s(f0, f0, f1);
            mul_s(f0, f20, f0);
            sqrt_s(f1, f0);
            v0 = flt(10.0f);
            mtc1(v0, f0);
            mul_s(f20, f0, f1);
            get_value(a0, a1, 0x30DA14u, sel::kAffinityT, 0);
            mul_s(f20, f20, f0);
            get_value(a0, a1, 0x30DA28u, sel::kLevelDiff, 0);
            mul_s(f1, f20, f0);
            lwc1(f0, gp, gp_off(ai::kLit1_30));  // 1.3
            mul_s(f20, f0, f1);
        }
    } else {
        // 0x0030d77c: a physical skill
        charge(ctx, 4);
        jal(ctx, 0x30D77Cu, gen::fn_sub_3111F0_003111f0);  // the attacker is a party member?
        if (v0 == 0) {
            // 0x0030d860: an enemy attacker
            charge(ctx, 65);
            // f20 = enemyDef = 0.8 * ((0 + GV(kArmorT1) / 2 / 2) + 2 * GV(kStatT, kEn))
            get_value(a0, a1, 0x30D868u, sel::kArmorT1, 0);
            v0 = flt(2.0f);
            mtc1(v0, f1);
            div_s(f20, f0, f1);
            get_value(a0, a1, 0x30D88Cu, sel::kStatT, sel::kEn);
            v0 = flt(2.0f);
            mtc1(v0, f3);
            div_s(f2, f20, f3);
            mtc1(zero, f1);
            adda_s(f1, f2);
            madd_s(f1, f3, f0);
            lwc1(f0, gp, gp_off(ai::kLit0_80));  // 0.8
            mul_s(f20, f0, f1);
            // f20 = root(f20, stat) = 10 * sqrt(30 * P / (5 * f20) * (GV(kStatA, stat) / 5)), P = GV(kPower)
            get_value(a0, a1, 0x30D8C4u, sel::kPower, 0);
            v0 = flt(30.0f);
            mtc1(v0, f1);
            mul_s(f1, f1, f0);
            v0 = flt(5.0f);
            mtc1(v0, f0);
            mul_s(f0, f0, f20);
            div_s(f20, f1, f0);
            get_value(a0, a1, 0x30D8FCu, sel::kStatA, sel::kSt);
            v0 = flt(5.0f);
            mtc1(v0, f1);
            div_s(f0, f0, f1);
            mul_s(f0, f20, f0);
            sqrt_s(f1, f0);
            v0 = flt(10.0f);
            mtc1(v0, f0);
            mul_s(f20, f0, f1);
            get_value(a0, a1, 0x30D934u, sel::kAffinityT, 0);
            mul_s(f20, f20, f0);
            get_value(a0, a1, 0x30D948u, sel::kLevelDiff, 0);
            mul_s(f1, f20, f0);
            lwc1(f0, gp, gp_off(ai::kLit0_60));  // 0.6
            mul_s(f20, f0, f1);
        } else {
            // 0x0030d78c: a party attacker
            charge(ctx, 53);
            // f20 = En2 = GV(kStatT, kEn) + GV(kStatT, kEn)
            get_value(a0, a1, 0x30D794u, sel::kStatT, sel::kEn);
            mov_s(f20, f0);
            get_value(a0, a1, 0x30D7A8u, sel::kStatT, sel::kEn);
            add_s(f20, f20, f0);
            // f20 = root(f20, stat) = 10 * sqrt(30 * P / (5 * f20) * (GV(kStatA, stat) / 5)), P = GV(kPower)
            get_value(a0, a1, 0x30D7BCu, sel::kPower, 0);
            v0 = flt(30.0f);
            mtc1(v0, f1);
            sub_s(f0, f0, f1);
            mul_s(f1, f1, f0);
            v0 = flt(5.0f);
            mtc1(v0, f0);
            mul_s(f0, f0, f20);
            div_s(f20, f1, f0);
            get_value(a0, a1, 0x30D7F8u, sel::kStatA, sel::kSt);
            v0 = flt(5.0f);
            mtc1(v0, f1);
            div_s(f0, f0, f1);
            mul_s(f0, f20, f0);
            sqrt_s(f1, f0);
            v0 = flt(10.0f);
            mtc1(v0, f0);
            mul_s(f20, f0, f1);
            get_value(a0, a1, 0x30D830u, sel::kAffinityT, 0);
            mul_s(f20, f20, f0);
            get_value(a0, a1, 0x30D844u, sel::kLevelDiff, 0);
            mul_s(f1, f20, f0);
            lwc1(f0, gp, gp_off(ai::kLit1_30));  // 1.3
            mul_s(f20, f0, f1);
        }
    }
    // 0x0030db50: the result; epilogue
    charge(ctx, 9);
    cvt_w_s(f0, f20);
    mfc1(a0, f0);
    jal(ctx, 0x30DB58u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030EA00 sub_30EA00 [datScriptAiDamage3] -- 1028 bytes; frame 0x20: ra sp+0x10, f20 sp+0x0
// Set 3 slot 1 (sDatScriptFuncTbl3[1]): Attack damage. Physical skill: party attacker root(En2, St) with P - 30, *
// GV(kAffinityT) * GV(kLevelDiff);
// enemy attacker 1.35 * (root(enemyDef, St) * GV(kAffinityT) * GV(kLevelDiff)). Magic skill: party attacker
// root(En2, St) * GV(kAffinityT) * GV(kLevelDiff); enemy attacker (root(enemyDef, St) * GV(kLevelDiff) * 1.35 - 10)
// * GV(kAffinityT).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30EA00(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::adda_s, hg::addiu, hg::charge, hg::cvt_w_s, hg::div_s, hg::enter, hg::jal,
          hg::ld, hg::lwc1, hg::madd_s, hg::mfc1, hg::mov_s, hg::mtc1, hg::mul_s, hg::sd, hg::sqrt_s, hg::sub_s,
          hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20};
    // 0x0030ea00: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f20, sp, 0x0);
    jal(ctx, 0x30EA0Cu, gen::fn_sub_311250_00311250);  // the skill is physical?
    if (v0 == 0) {
        // 0x0030ebfc: a magic skill
        charge(ctx, 4);
        jal(ctx, 0x30EBFCu, gen::fn_sub_3111F0_003111f0);  // the attacker is a party member?
        if (v0 == 0) {
            // 0x0030ecd4: an enemy attacker
            charge(ctx, 67);
            // f20 = enemyDef = 0.8 * ((0 + GV(kArmorT1) / 2 / 2) + 2 * GV(kStatT, kEn))
            get_value(a0, a1, 0x30ECDCu, sel::kArmorT1, 0);
            v0 = flt(2.0f);
            mtc1(v0, f1);
            div_s(f20, f0, f1);
            get_value(a0, a1, 0x30ED00u, sel::kStatT, sel::kEn);
            v0 = flt(2.0f);
            mtc1(v0, f3);
            div_s(f2, f20, f3);
            mtc1(zero, f1);
            adda_s(f1, f2);
            madd_s(f1, f3, f0);
            lwc1(f0, gp, gp_off(ai::kLit0_80));  // 0.8
            mul_s(f20, f0, f1);
            // f20 = root(f20, stat) = 10 * sqrt(30 * P / (5 * f20) * (GV(kStatA, stat) / 5)), P = GV(kPower)
            get_value(a0, a1, 0x30ED38u, sel::kPower, 0);
            v0 = flt(30.0f);
            mtc1(v0, f1);
            mul_s(f1, f1, f0);
            v0 = flt(5.0f);
            mtc1(v0, f0);
            mul_s(f0, f0, f20);
            div_s(f20, f1, f0);
            get_value(a0, a1, 0x30ED70u, sel::kStatA, sel::kSt);
            v0 = flt(5.0f);
            mtc1(v0, f1);
            div_s(f0, f0, f1);
            mul_s(f0, f20, f0);
            sqrt_s(f1, f0);
            v0 = flt(10.0f);
            mtc1(v0, f0);
            mul_s(f20, f0, f1);
            get_value(a0, a1, 0x30EDA8u, sel::kLevelDiff, 0);
            mul_s(f1, f20, f0);
            lwc1(f0, gp, gp_off(ai::kLit1_35));  // 1.35
            mul_s(f1, f1, f0);
            v0 = flt(10.0f);
            mtc1(v0, f0);
            sub_s(f20, f1, f0);
            get_value(a0, a1, 0x30EDD4u, sel::kAffinityT, 0);
            mul_s(f20, f20, f0);
        } else {
            // 0x0030ec0c: a party attacker
            charge(ctx, 50);
            // f20 = En2 = GV(kStatT, kEn) + GV(kStatT, kEn)
            get_value(a0, a1, 0x30EC14u, sel::kStatT, sel::kEn);
            mov_s(f20, f0);
            get_value(a0, a1, 0x30EC28u, sel::kStatT, sel::kEn);
            add_s(f20, f20, f0);
            // f20 = root(f20, stat) = 10 * sqrt(30 * P / (5 * f20) * (GV(kStatA, stat) / 5)), P = GV(kPower)
            get_value(a0, a1, 0x30EC3Cu, sel::kPower, 0);
            v0 = flt(30.0f);
            mtc1(v0, f1);
            mul_s(f1, f1, f0);
            v0 = flt(5.0f);
            mtc1(v0, f0);
            mul_s(f0, f0, f20);
            div_s(f20, f1, f0);
            get_value(a0, a1, 0x30EC74u, sel::kStatA, sel::kSt);
            v0 = flt(5.0f);
            mtc1(v0, f1);
            div_s(f0, f0, f1);
            mul_s(f0, f20, f0);
            sqrt_s(f1, f0);
            v0 = flt(10.0f);
            mtc1(v0, f0);
            mul_s(f20, f0, f1);
            get_value(a0, a1, 0x30ECACu, sel::kAffinityT, 0);
            mul_s(f20, f20, f0);
            get_value(a0, a1, 0x30ECC0u, sel::kLevelDiff, 0);
            mul_s(f20, f20, f0);
        }
    } else {
        // 0x0030ea1c: a physical skill
        charge(ctx, 4);
        jal(ctx, 0x30EA1Cu, gen::fn_sub_3111F0_003111f0);  // the attacker is a party member?
        if (v0 == 0) {
            // 0x0030eaf8: an enemy attacker
            charge(ctx, 65);
            // f20 = enemyDef = 0.8 * ((0 + GV(kArmorT1) / 2 / 2) + 2 * GV(kStatT, kEn))
            get_value(a0, a1, 0x30EB00u, sel::kArmorT1, 0);
            v0 = flt(2.0f);
            mtc1(v0, f1);
            div_s(f20, f0, f1);
            get_value(a0, a1, 0x30EB24u, sel::kStatT, sel::kEn);
            v0 = flt(2.0f);
            mtc1(v0, f3);
            div_s(f2, f20, f3);
            mtc1(zero, f1);
            adda_s(f1, f2);
            madd_s(f1, f3, f0);
            lwc1(f0, gp, gp_off(ai::kLit0_80));  // 0.8
            mul_s(f20, f0, f1);
            // f20 = root(f20, stat) = 10 * sqrt(30 * P / (5 * f20) * (GV(kStatA, stat) / 5)), P = GV(kPower)
            get_value(a0, a1, 0x30EB5Cu, sel::kPower, 0);
            v0 = flt(30.0f);
            mtc1(v0, f1);
            mul_s(f1, f1, f0);
            v0 = flt(5.0f);
            mtc1(v0, f0);
            mul_s(f0, f0, f20);
            div_s(f20, f1, f0);
            get_value(a0, a1, 0x30EB94u, sel::kStatA, sel::kSt);
            v0 = flt(5.0f);
            mtc1(v0, f1);
            div_s(f0, f0, f1);
            mul_s(f0, f20, f0);
            sqrt_s(f1, f0);
            v0 = flt(10.0f);
            mtc1(v0, f0);
            mul_s(f20, f0, f1);
            get_value(a0, a1, 0x30EBCCu, sel::kAffinityT, 0);
            mul_s(f20, f20, f0);
            get_value(a0, a1, 0x30EBE0u, sel::kLevelDiff, 0);
            mul_s(f1, f20, f0);
            lwc1(f0, gp, gp_off(ai::kLit1_35));  // 1.35
            mul_s(f20, f0, f1);
        } else {
            // 0x0030ea2c: a party attacker
            charge(ctx, 51);
            // f20 = En2 = GV(kStatT, kEn) + GV(kStatT, kEn)
            get_value(a0, a1, 0x30EA34u, sel::kStatT, sel::kEn);
            mov_s(f20, f0);
            get_value(a0, a1, 0x30EA48u, sel::kStatT, sel::kEn);
            add_s(f20, f20, f0);
            // f20 = root(f20, stat) = 10 * sqrt(30 * P / (5 * f20) * (GV(kStatA, stat) / 5)), P = GV(kPower)
            get_value(a0, a1, 0x30EA5Cu, sel::kPower, 0);
            v0 = flt(30.0f);
            mtc1(v0, f1);
            sub_s(f0, f0, f1);
            mul_s(f1, f1, f0);
            v0 = flt(5.0f);
            mtc1(v0, f0);
            mul_s(f0, f0, f20);
            div_s(f20, f1, f0);
            get_value(a0, a1, 0x30EA98u, sel::kStatA, sel::kSt);
            v0 = flt(5.0f);
            mtc1(v0, f1);
            div_s(f0, f0, f1);
            mul_s(f0, f20, f0);
            sqrt_s(f1, f0);
            v0 = flt(10.0f);
            mtc1(v0, f0);
            mul_s(f20, f0, f1);
            get_value(a0, a1, 0x30EAD0u, sel::kAffinityT, 0);
            mul_s(f20, f20, f0);
            get_value(a0, a1, 0x30EAE4u, sel::kLevelDiff, 0);
            mul_s(f20, f20, f0);
        }
    }
    // 0x0030ede0: the result; epilogue
    charge(ctx, 9);
    cvt_w_s(f0, f20);
    mfc1(a0, f0);
    jal(ctx, 0x30EDE8u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030C930 sub_30C930 [datScriptAiMaDamage1] -- 604 bytes; frame 0x20: ra sp+0x10, f21 sp+0x4, f20 sp+0x0
// Set 1 slot 2 (sDatScriptFuncTbl1[2]): Ma damage. Party attacker (0 + GV(kMaBonus10)) + root(En2, Ma) *
// GV(kAffinityT) * GV(kLevelDiff);
// enemy attacker (((0 + GV(kMaBonus10)) + root(enemyDef, Ma) * GV(kLevelDiff)) * 0.9 - 10) * GV(kAffinityT).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30C930(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::adda_s, hg::addiu, hg::charge, hg::cvt_w_s, hg::div_s, hg::enter, hg::jal,
          hg::ld, hg::lwc1, hg::madd_s, hg::mfc1, hg::mov_s, hg::mtc1, hg::mul_s, hg::sd, hg::sqrt_s, hg::sub_s,
          hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20}, f21{ctx, 21};
    // 0x0030c930: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    jal(ctx, 0x30C940u, gen::fn_sub_3111F0_003111f0);  // the attacker is a party member?
    if (v0 == 0) {
        // 0x0030ca38: an enemy attacker
        charge(ctx, 75);
        // f20 = enemyDef = 0.8 * ((0 + GV(kArmorT1) / 2 / 2) + 2 * GV(kStatT, kEn))
        get_value(a0, a1, 0x30CA40u, sel::kArmorT1, 0);
        v0 = flt(2.0f);
        mtc1(v0, f1);
        div_s(f20, f0, f1);
        get_value(a0, a1, 0x30CA64u, sel::kStatT, sel::kEn);
        v0 = flt(2.0f);
        mtc1(v0, f3);
        div_s(f2, f20, f3);
        mtc1(zero, f1);
        adda_s(f1, f2);
        madd_s(f1, f3, f0);
        lwc1(f0, gp, gp_off(ai::kLit0_80));  // 0.8
        mul_s(f20, f0, f1);
        // f20 = root(f20, stat) = 10 * sqrt(30 * P / (5 * f20) * (GV(kStatA, stat) / 5)), P = GV(kPower)
        get_value(a0, a1, 0x30CA9Cu, sel::kPower, 0);
        v0 = flt(30.0f);
        mtc1(v0, f1);
        mul_s(f1, f1, f0);
        v0 = flt(5.0f);
        mtc1(v0, f0);
        mul_s(f0, f0, f20);
        div_s(f20, f1, f0);
        get_value(a0, a1, 0x30CAD4u, sel::kStatA, sel::kMa);
        v0 = flt(5.0f);
        mtc1(v0, f1);
        div_s(f0, f0, f1);
        mul_s(f0, f20, f0);
        sqrt_s(f1, f0);
        v0 = flt(10.0f);
        mtc1(v0, f0);
        mul_s(f21, f0, f1);
        get_value(a0, a1, 0x30CB0Cu, sel::kLevelDiff, 0);
        mov_s(f20, f0);
        get_value(a0, a1, 0x30CB20u, sel::kMaBonus10, 0);
        mtc1(zero, f1);
        adda_s(f1, f0);
        madd_s(f1, f21, f20);
        lwc1(f0, gp, gp_off(ai::kLit0_90));  // 0.9
        mul_s(f1, f1, f0);
        v0 = flt(10.0f);
        mtc1(v0, f0);
        sub_s(f20, f1, f0);
        get_value(a0, a1, 0x30CB58u, sel::kAffinityT, 0);
        mul_s(f20, f20, f0);
    } else {
        // 0x0030c950: a party attacker
        charge(ctx, 58);
        // f20 = En2 = GV(kStatT, kEn) + GV(kStatT, kEn)
        get_value(a0, a1, 0x30C958u, sel::kStatT, sel::kEn);
        mov_s(f20, f0);
        get_value(a0, a1, 0x30C96Cu, sel::kStatT, sel::kEn);
        add_s(f20, f20, f0);
        // f20 = root(f20, stat) = 10 * sqrt(30 * P / (5 * f20) * (GV(kStatA, stat) / 5)), P = GV(kPower)
        get_value(a0, a1, 0x30C980u, sel::kPower, 0);
        v0 = flt(30.0f);
        mtc1(v0, f1);
        mul_s(f1, f1, f0);
        v0 = flt(5.0f);
        mtc1(v0, f0);
        mul_s(f0, f0, f20);
        div_s(f20, f1, f0);
        get_value(a0, a1, 0x30C9B8u, sel::kStatA, sel::kMa);
        v0 = flt(5.0f);
        mtc1(v0, f1);
        div_s(f0, f0, f1);
        mul_s(f0, f20, f0);
        sqrt_s(f1, f0);
        v0 = flt(10.0f);
        mtc1(v0, f0);
        mul_s(f21, f0, f1);
        get_value(a0, a1, 0x30C9F0u, sel::kAffinityT, 0);
        mul_s(f21, f21, f0);
        get_value(a0, a1, 0x30CA04u, sel::kLevelDiff, 0);
        mov_s(f20, f0);
        get_value(a0, a1, 0x30CA18u, sel::kMaBonus10, 0);
        mtc1(zero, f1);
        adda_s(f1, f0);
        madd_s(f20, f21, f20);
    }
    // 0x0030cb64: the result; epilogue
    charge(ctx, 10);
    cvt_w_s(f0, f20);
    mfc1(a0, f0);
    jal(ctx, 0x30CB6Cu, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030DB80 sub_30DB80 [datScriptAiMaDamage2] -- 612 bytes; frame 0x20: ra sp+0x10, f21 sp+0x4, f20 sp+0x0
// Set 2 slot 2 (sDatScriptFuncTbl2[2]): Ma damage. Party attacker (0 + GV(kMaBonus10)) + root(En2, Ma) *
// GV(kAffinityT) * GV(kLevelDiff), times 1.3;
// enemy attacker (((0 + GV(kMaBonus10)) + root(enemyDef, Ma) * GV(kLevelDiff)) * 0.6 - 10) * GV(kAffinityT).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30DB80(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::adda_s, hg::addiu, hg::charge, hg::cvt_w_s, hg::div_s, hg::enter, hg::jal,
          hg::ld, hg::lwc1, hg::madd_s, hg::mfc1, hg::mov_s, hg::mtc1, hg::mul_s, hg::sd, hg::sqrt_s, hg::sub_s,
          hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20}, f21{ctx, 21};
    // 0x0030db80: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    jal(ctx, 0x30DB90u, gen::fn_sub_3111F0_003111f0);  // the attacker is a party member?
    if (v0 == 0) {
        // 0x0030dc90: an enemy attacker
        charge(ctx, 75);
        // f20 = enemyDef = 0.8 * ((0 + GV(kArmorT1) / 2 / 2) + 2 * GV(kStatT, kEn))
        get_value(a0, a1, 0x30DC98u, sel::kArmorT1, 0);
        v0 = flt(2.0f);
        mtc1(v0, f1);
        div_s(f20, f0, f1);
        get_value(a0, a1, 0x30DCBCu, sel::kStatT, sel::kEn);
        v0 = flt(2.0f);
        mtc1(v0, f3);
        div_s(f2, f20, f3);
        mtc1(zero, f1);
        adda_s(f1, f2);
        madd_s(f1, f3, f0);
        lwc1(f0, gp, gp_off(ai::kLit0_80));  // 0.8
        mul_s(f20, f0, f1);
        // f20 = root(f20, stat) = 10 * sqrt(30 * P / (5 * f20) * (GV(kStatA, stat) / 5)), P = GV(kPower)
        get_value(a0, a1, 0x30DCF4u, sel::kPower, 0);
        v0 = flt(30.0f);
        mtc1(v0, f1);
        mul_s(f1, f1, f0);
        v0 = flt(5.0f);
        mtc1(v0, f0);
        mul_s(f0, f0, f20);
        div_s(f20, f1, f0);
        get_value(a0, a1, 0x30DD2Cu, sel::kStatA, sel::kMa);
        v0 = flt(5.0f);
        mtc1(v0, f1);
        div_s(f0, f0, f1);
        mul_s(f0, f20, f0);
        sqrt_s(f1, f0);
        v0 = flt(10.0f);
        mtc1(v0, f0);
        mul_s(f21, f0, f1);
        get_value(a0, a1, 0x30DD64u, sel::kLevelDiff, 0);
        mov_s(f20, f0);
        get_value(a0, a1, 0x30DD78u, sel::kMaBonus10, 0);
        mtc1(zero, f1);
        adda_s(f1, f0);
        madd_s(f1, f21, f20);
        lwc1(f0, gp, gp_off(ai::kLit0_60));  // 0.6
        mul_s(f1, f1, f0);
        v0 = flt(10.0f);
        mtc1(v0, f0);
        sub_s(f20, f1, f0);
        get_value(a0, a1, 0x30DDB0u, sel::kAffinityT, 0);
        mul_s(f20, f20, f0);
    } else {
        // 0x0030dba0: a party attacker
        charge(ctx, 60);
        // f20 = En2 = GV(kStatT, kEn) + GV(kStatT, kEn)
        get_value(a0, a1, 0x30DBA8u, sel::kStatT, sel::kEn);
        mov_s(f20, f0);
        get_value(a0, a1, 0x30DBBCu, sel::kStatT, sel::kEn);
        add_s(f20, f20, f0);
        // f20 = root(f20, stat) = 10 * sqrt(30 * P / (5 * f20) * (GV(kStatA, stat) / 5)), P = GV(kPower)
        get_value(a0, a1, 0x30DBD0u, sel::kPower, 0);
        v0 = flt(30.0f);
        mtc1(v0, f1);
        mul_s(f1, f1, f0);
        v0 = flt(5.0f);
        mtc1(v0, f0);
        mul_s(f0, f0, f20);
        div_s(f20, f1, f0);
        get_value(a0, a1, 0x30DC08u, sel::kStatA, sel::kMa);
        v0 = flt(5.0f);
        mtc1(v0, f1);
        div_s(f0, f0, f1);
        mul_s(f0, f20, f0);
        sqrt_s(f1, f0);
        v0 = flt(10.0f);
        mtc1(v0, f0);
        mul_s(f21, f0, f1);
        get_value(a0, a1, 0x30DC40u, sel::kAffinityT, 0);
        mul_s(f21, f21, f0);
        get_value(a0, a1, 0x30DC54u, sel::kLevelDiff, 0);
        mov_s(f20, f0);
        get_value(a0, a1, 0x30DC68u, sel::kMaBonus10, 0);
        mtc1(zero, f1);
        adda_s(f1, f0);
        madd_s(f1, f21, f20);
        lwc1(f0, gp, gp_off(ai::kLit1_30));  // 1.3
        mul_s(f20, f1, f0);
    }
    // 0x0030ddbc: the result; epilogue
    charge(ctx, 10);
    cvt_w_s(f0, f20);
    mfc1(a0, f0);
    jal(ctx, 0x30DDC4u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030EE10 sub_30EE10 [datScriptAiMaDamage3] -- 604 bytes; frame 0x20: ra sp+0x10, f21 sp+0x4, f20 sp+0x0
// Set 3 slot 2 (sDatScriptFuncTbl3[2]): Ma damage. Party attacker (0 + GV(kMaBonus10)) + root(En2, Ma) *
// GV(kAffinityT) * GV(kLevelDiff);
// enemy attacker (((0 + GV(kMaBonus10)) + root(enemyDef, Ma) * GV(kLevelDiff)) * 1.35 - 10) * GV(kAffinityT).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30EE10(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::adda_s, hg::addiu, hg::charge, hg::cvt_w_s, hg::div_s, hg::enter, hg::jal,
          hg::ld, hg::lwc1, hg::madd_s, hg::mfc1, hg::mov_s, hg::mtc1, hg::mul_s, hg::sd, hg::sqrt_s, hg::sub_s,
          hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20}, f21{ctx, 21};
    // 0x0030ee10: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    jal(ctx, 0x30EE20u, gen::fn_sub_3111F0_003111f0);  // the attacker is a party member?
    if (v0 == 0) {
        // 0x0030ef18: an enemy attacker
        charge(ctx, 75);
        // f20 = enemyDef = 0.8 * ((0 + GV(kArmorT1) / 2 / 2) + 2 * GV(kStatT, kEn))
        get_value(a0, a1, 0x30EF20u, sel::kArmorT1, 0);
        v0 = flt(2.0f);
        mtc1(v0, f1);
        div_s(f20, f0, f1);
        get_value(a0, a1, 0x30EF44u, sel::kStatT, sel::kEn);
        v0 = flt(2.0f);
        mtc1(v0, f3);
        div_s(f2, f20, f3);
        mtc1(zero, f1);
        adda_s(f1, f2);
        madd_s(f1, f3, f0);
        lwc1(f0, gp, gp_off(ai::kLit0_80));  // 0.8
        mul_s(f20, f0, f1);
        // f20 = root(f20, stat) = 10 * sqrt(30 * P / (5 * f20) * (GV(kStatA, stat) / 5)), P = GV(kPower)
        get_value(a0, a1, 0x30EF7Cu, sel::kPower, 0);
        v0 = flt(30.0f);
        mtc1(v0, f1);
        mul_s(f1, f1, f0);
        v0 = flt(5.0f);
        mtc1(v0, f0);
        mul_s(f0, f0, f20);
        div_s(f20, f1, f0);
        get_value(a0, a1, 0x30EFB4u, sel::kStatA, sel::kMa);
        v0 = flt(5.0f);
        mtc1(v0, f1);
        div_s(f0, f0, f1);
        mul_s(f0, f20, f0);
        sqrt_s(f1, f0);
        v0 = flt(10.0f);
        mtc1(v0, f0);
        mul_s(f21, f0, f1);
        get_value(a0, a1, 0x30EFECu, sel::kLevelDiff, 0);
        mov_s(f20, f0);
        get_value(a0, a1, 0x30F000u, sel::kMaBonus10, 0);
        mtc1(zero, f1);
        adda_s(f1, f0);
        madd_s(f1, f21, f20);
        lwc1(f0, gp, gp_off(ai::kLit1_35));  // 1.35
        mul_s(f1, f1, f0);
        v0 = flt(10.0f);
        mtc1(v0, f0);
        sub_s(f20, f1, f0);
        get_value(a0, a1, 0x30F038u, sel::kAffinityT, 0);
        mul_s(f20, f20, f0);
    } else {
        // 0x0030ee30: a party attacker
        charge(ctx, 58);
        // f20 = En2 = GV(kStatT, kEn) + GV(kStatT, kEn)
        get_value(a0, a1, 0x30EE38u, sel::kStatT, sel::kEn);
        mov_s(f20, f0);
        get_value(a0, a1, 0x30EE4Cu, sel::kStatT, sel::kEn);
        add_s(f20, f20, f0);
        // f20 = root(f20, stat) = 10 * sqrt(30 * P / (5 * f20) * (GV(kStatA, stat) / 5)), P = GV(kPower)
        get_value(a0, a1, 0x30EE60u, sel::kPower, 0);
        v0 = flt(30.0f);
        mtc1(v0, f1);
        mul_s(f1, f1, f0);
        v0 = flt(5.0f);
        mtc1(v0, f0);
        mul_s(f0, f0, f20);
        div_s(f20, f1, f0);
        get_value(a0, a1, 0x30EE98u, sel::kStatA, sel::kMa);
        v0 = flt(5.0f);
        mtc1(v0, f1);
        div_s(f0, f0, f1);
        mul_s(f0, f20, f0);
        sqrt_s(f1, f0);
        v0 = flt(10.0f);
        mtc1(v0, f0);
        mul_s(f21, f0, f1);
        get_value(a0, a1, 0x30EED0u, sel::kAffinityT, 0);
        mul_s(f21, f21, f0);
        get_value(a0, a1, 0x30EEE4u, sel::kLevelDiff, 0);
        mov_s(f20, f0);
        get_value(a0, a1, 0x30EEF8u, sel::kMaBonus10, 0);
        mtc1(zero, f1);
        adda_s(f1, f0);
        madd_s(f20, f21, f20);
    }
    // 0x0030f044: the result; epilogue
    charge(ctx, 10);
    cvt_w_s(f0, f20);
    mfc1(a0, f0);
    jal(ctx, 0x30F04Cu, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030CB90 sub_30CB90 [datScriptAiPower1] -- 176 bytes; frame 0x20: ra sp+0x10, f21 sp+0x4, f20 sp+0x0
// Set 1 slot 3 (sDatScriptFuncTbl1[3]): Power plus bonus: party attacker GV(kPower) + GV(kMaBonus5); enemy attacker
// (0 + GV(kPower)) + 0.6 *
// GV(kMaBonus5) (0.6 sits in $f20 while GV(kPower) is read).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30CB90(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::adda_s, hg::addiu, hg::charge, hg::cvt_w_s, hg::enter, hg::jal, hg::ld,
          hg::lwc1, hg::madd_s, hg::mfc1, hg::mov_s, hg::mtc1, hg::sd, hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f20{ctx, 20}, f21{ctx, 21};
    // 0x0030cb90: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    jal(ctx, 0x30CBA0u, gen::fn_sub_3111F0_003111f0);  // the attacker is a party member?
    if (v0 == 0) {
        // 0x0030cbe0: an enemy attacker
        charge(ctx, 14);
        get_value(a0, a1, 0x30CBE8u, sel::kMaBonus5, 0);
        mov_s(f21, f0);
        lwc1(f20, gp, gp_off(ai::kLit0_60));  // 0.6
        get_value(a0, a1, 0x30CC00u, sel::kPower, 0);
        mtc1(zero, f1);
        adda_s(f1, f0);
        madd_s(f0, f20, f21);
    } else {
        // 0x0030cbb0: a party attacker
        charge(ctx, 12);
        get_value(a0, a1, 0x30CBB8u, sel::kPower, 0);
        mov_s(f20, f0);
        get_value(a0, a1, 0x30CBCCu, sel::kMaBonus5, 0);
        add_s(f0, f20, f0);
    }
    // 0x0030cc18: the result; epilogue
    charge(ctx, 10);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30CC20u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030DDF0 sub_30DDF0 [datScriptAiPower2] -- 196 bytes; frame 0x20: ra sp+0x10, f21 sp+0x4, f20 sp+0x0
// Set 2 slot 3 (sDatScriptFuncTbl2[3]): Power plus bonus: party attacker 1.5 * (GV(kPower) + GV(kMaBonus5)); enemy
// attacker (0 + GV(kPower)) +
// 0.5 * GV(kMaBonus5).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30DDF0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::adda_s, hg::addiu, hg::charge, hg::cvt_w_s, hg::enter, hg::jal, hg::ld,
          hg::lwc1, hg::madd_s, hg::mfc1, hg::mov_s, hg::mtc1, hg::mul_s, hg::sd, hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f20{ctx, 20}, f21{ctx, 21};
    // 0x0030ddf0: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    jal(ctx, 0x30DE00u, gen::fn_sub_3111F0_003111f0);  // the attacker is a party member?
    if (v0 == 0) {
        // 0x0030de50: an enemy attacker
        charge(ctx, 15);
        get_value(a0, a1, 0x30DE58u, sel::kMaBonus5, 0);
        mov_s(f21, f0);
        v0 = flt(0.5f);
        mtc1(v0, f20);
        get_value(a0, a1, 0x30DE74u, sel::kPower, 0);
        mtc1(zero, f1);
        adda_s(f1, f0);
        madd_s(f0, f20, f21);
    } else {
        // 0x0030de10: a party attacker
        charge(ctx, 16);
        get_value(a0, a1, 0x30DE18u, sel::kPower, 0);
        mov_s(f20, f0);
        get_value(a0, a1, 0x30DE2Cu, sel::kMaBonus5, 0);
        add_s(f1, f20, f0);
        v0 = flt(1.5f);
        mtc1(v0, f0);
        mul_s(f0, f0, f1);
    }
    // 0x0030de8c: the result; epilogue
    charge(ctx, 10);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30DE94u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030F070 sub_30F070 [datScriptAiPower3] -- 176 bytes; frame 0x20: ra sp+0x10, f21 sp+0x4, f20 sp+0x0
// Set 3 slot 3 (sDatScriptFuncTbl3[3]): = set 1 slot 3 (sub_30CB90): GV(kPower) + GV(kMaBonus5), an enemy attacker
// 0.6 * the bonus.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30F070(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::adda_s, hg::addiu, hg::charge, hg::cvt_w_s, hg::enter, hg::jal, hg::ld,
          hg::lwc1, hg::madd_s, hg::mfc1, hg::mov_s, hg::mtc1, hg::sd, hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f20{ctx, 20}, f21{ctx, 21};
    // 0x0030f070: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    jal(ctx, 0x30F080u, gen::fn_sub_3111F0_003111f0);  // the attacker is a party member?
    if (v0 == 0) {
        // 0x0030f0c0: an enemy attacker
        charge(ctx, 14);
        get_value(a0, a1, 0x30F0C8u, sel::kMaBonus5, 0);
        mov_s(f21, f0);
        lwc1(f20, gp, gp_off(ai::kLit0_60));  // 0.6
        get_value(a0, a1, 0x30F0E0u, sel::kPower, 0);
        mtc1(zero, f1);
        adda_s(f1, f0);
        madd_s(f0, f20, f21);
    } else {
        // 0x0030f090: a party attacker
        charge(ctx, 12);
        get_value(a0, a1, 0x30F098u, sel::kPower, 0);
        mov_s(f20, f0);
        get_value(a0, a1, 0x30F0ACu, sel::kMaBonus5, 0);
        add_s(f0, f20, f0);
    }
    // 0x0030f0f8: the result; epilogue
    charge(ctx, 10);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30F100u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030CC40 sub_30CC40 [datScriptAiHitRate1] -- 356 bytes; frame 0x20: ra sp+0x10, f21 sp+0x4, f20 sp+0x0
// Set 1 slot 4 (sDatScriptFuncTbl1[4]): Hit rate: party attacker ratio(200, Ag) * GV(kAccuracy); enemy attacker
// ratio(200, Ag) *
// (200 + GV(kStatA, Ag)) / (200 + GV(kArmorT0) / 2) * GV(kAccuracy).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30CC40(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::charge, hg::cvt_w_s, hg::div_s, hg::enter, hg::jal, hg::ld,
          hg::lwc1, hg::mfc1, hg::mtc1, hg::mul_s, hg::sd, hg::swc1;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f20{ctx, 20}, f21{ctx, 21};
    // 0x0030cc40: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    jal(ctx, 0x30CC50u, gen::fn_sub_3111F0_003111f0);  // the attacker is a party member?
    if (v0 == 0) {
        // 0x0030ccc4: an enemy attacker
        charge(ctx, 46);
        get_value(a0, a1, 0x30CCCCu, sel::kStatA, sel::kAg);
        v0 = flt(200.0f);
        mtc1(v0, f1);
        add_s(f20, f1, f0);
        get_value(a0, a1, 0x30CCECu, sel::kStatT, sel::kAg);
        v0 = flt(200.0f);
        mtc1(v0, f1);
        add_s(f0, f1, f0);
        div_s(f21, f20, f0);
        get_value(a0, a1, 0x30CD14u, sel::kStatA, sel::kAg);
        v0 = flt(200.0f);
        mtc1(v0, f1);
        add_s(f20, f1, f0);
        get_value(a0, a1, 0x30CD34u, sel::kArmorT0, 0);
        v0 = flt(2.0f);
        mtc1(v0, f1);
        div_s(f1, f0, f1);
        v0 = flt(200.0f);
        mtc1(v0, f0);
        add_s(f0, f0, f1);
        div_s(f20, f20, f0);
        get_value(a0, a1, 0x30CD6Cu, sel::kAccuracy, 0);
        mul_s(f1, f21, f20);
        mul_s(f0, f1, f0);
    } else {
        // 0x0030cc60: a party attacker
        charge(ctx, 25);
        get_value(a0, a1, 0x30CC68u, sel::kStatA, sel::kAg);
        v0 = flt(200.0f);
        mtc1(v0, f1);
        add_s(f20, f1, f0);
        get_value(a0, a1, 0x30CC88u, sel::kStatT, sel::kAg);
        v0 = flt(200.0f);
        mtc1(v0, f1);
        add_s(f0, f1, f0);
        div_s(f20, f20, f0);
        get_value(a0, a1, 0x30CCB0u, sel::kAccuracy, 0);
        mul_s(f0, f20, f0);
    }
    // 0x0030cd7c: the result; epilogue
    charge(ctx, 10);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30CD84u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030DEC0 sub_30DEC0 [datScriptAiHitRate2] -- 356 bytes; frame 0x20: ra sp+0x10, f21 sp+0x4, f20 sp+0x0
// Set 2 slot 4 (sDatScriptFuncTbl2[4]): = set 1 slot 4 (sub_30CC40), the hit rate.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30DEC0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::charge, hg::cvt_w_s, hg::div_s, hg::enter, hg::jal, hg::ld,
          hg::lwc1, hg::mfc1, hg::mtc1, hg::mul_s, hg::sd, hg::swc1;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f20{ctx, 20}, f21{ctx, 21};
    // 0x0030dec0: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    jal(ctx, 0x30DED0u, gen::fn_sub_3111F0_003111f0);  // the attacker is a party member?
    if (v0 == 0) {
        // 0x0030df44: an enemy attacker
        charge(ctx, 46);
        get_value(a0, a1, 0x30DF4Cu, sel::kStatA, sel::kAg);
        v0 = flt(200.0f);
        mtc1(v0, f1);
        add_s(f20, f1, f0);
        get_value(a0, a1, 0x30DF6Cu, sel::kStatT, sel::kAg);
        v0 = flt(200.0f);
        mtc1(v0, f1);
        add_s(f0, f1, f0);
        div_s(f21, f20, f0);
        get_value(a0, a1, 0x30DF94u, sel::kStatA, sel::kAg);
        v0 = flt(200.0f);
        mtc1(v0, f1);
        add_s(f20, f1, f0);
        get_value(a0, a1, 0x30DFB4u, sel::kArmorT0, 0);
        v0 = flt(2.0f);
        mtc1(v0, f1);
        div_s(f1, f0, f1);
        v0 = flt(200.0f);
        mtc1(v0, f0);
        add_s(f0, f0, f1);
        div_s(f20, f20, f0);
        get_value(a0, a1, 0x30DFECu, sel::kAccuracy, 0);
        mul_s(f1, f21, f20);
        mul_s(f0, f1, f0);
    } else {
        // 0x0030dee0: a party attacker
        charge(ctx, 25);
        get_value(a0, a1, 0x30DEE8u, sel::kStatA, sel::kAg);
        v0 = flt(200.0f);
        mtc1(v0, f1);
        add_s(f20, f1, f0);
        get_value(a0, a1, 0x30DF08u, sel::kStatT, sel::kAg);
        v0 = flt(200.0f);
        mtc1(v0, f1);
        add_s(f0, f1, f0);
        div_s(f20, f20, f0);
        get_value(a0, a1, 0x30DF30u, sel::kAccuracy, 0);
        mul_s(f0, f20, f0);
    }
    // 0x0030dffc: the result; epilogue
    charge(ctx, 10);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30E004u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030F120 sub_30F120 [datScriptAiHitRate3] -- 356 bytes; frame 0x20: ra sp+0x10, f21 sp+0x4, f20 sp+0x0
// Set 3 slot 4 (sDatScriptFuncTbl3[4]): = set 1 slot 4 (sub_30CC40), the hit rate.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30F120(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::charge, hg::cvt_w_s, hg::div_s, hg::enter, hg::jal, hg::ld,
          hg::lwc1, hg::mfc1, hg::mtc1, hg::mul_s, hg::sd, hg::swc1;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f20{ctx, 20}, f21{ctx, 21};
    // 0x0030f120: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    jal(ctx, 0x30F130u, gen::fn_sub_3111F0_003111f0);  // the attacker is a party member?
    if (v0 == 0) {
        // 0x0030f1a4: an enemy attacker
        charge(ctx, 46);
        get_value(a0, a1, 0x30F1ACu, sel::kStatA, sel::kAg);
        v0 = flt(200.0f);
        mtc1(v0, f1);
        add_s(f20, f1, f0);
        get_value(a0, a1, 0x30F1CCu, sel::kStatT, sel::kAg);
        v0 = flt(200.0f);
        mtc1(v0, f1);
        add_s(f0, f1, f0);
        div_s(f21, f20, f0);
        get_value(a0, a1, 0x30F1F4u, sel::kStatA, sel::kAg);
        v0 = flt(200.0f);
        mtc1(v0, f1);
        add_s(f20, f1, f0);
        get_value(a0, a1, 0x30F214u, sel::kArmorT0, 0);
        v0 = flt(2.0f);
        mtc1(v0, f1);
        div_s(f1, f0, f1);
        v0 = flt(200.0f);
        mtc1(v0, f0);
        add_s(f0, f0, f1);
        div_s(f20, f20, f0);
        get_value(a0, a1, 0x30F24Cu, sel::kAccuracy, 0);
        mul_s(f1, f21, f20);
        mul_s(f0, f1, f0);
    } else {
        // 0x0030f140: a party attacker
        charge(ctx, 25);
        get_value(a0, a1, 0x30F148u, sel::kStatA, sel::kAg);
        v0 = flt(200.0f);
        mtc1(v0, f1);
        add_s(f20, f1, f0);
        get_value(a0, a1, 0x30F168u, sel::kStatT, sel::kAg);
        v0 = flt(200.0f);
        mtc1(v0, f1);
        add_s(f0, f1, f0);
        div_s(f20, f20, f0);
        get_value(a0, a1, 0x30F190u, sel::kAccuracy, 0);
        mul_s(f0, f20, f0);
    }
    // 0x0030f25c: the result; epilogue
    charge(ctx, 10);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30F264u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030CDB0 sub_30CDB0 [datScriptAiLuRate1] -- 264 bytes; frame 0x20: ra sp+0x10, f20 sp+0x0
// Set 1 slot 5 (sDatScriptFuncTbl1[5]): GV(kSkillByte37) * ratio(50, Lu); an enemy attacker's result times 0.8.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30CDB0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::charge, hg::cvt_w_s, hg::div_s, hg::enter, hg::jal, hg::ld,
          hg::lwc1, hg::mfc1, hg::mtc1, hg::mul_s, hg::sd, hg::swc1;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f20{ctx, 20};
    // 0x0030cdb0: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f20, sp, 0x0);
    jal(ctx, 0x30CDBCu, gen::fn_sub_3111F0_003111f0);  // the attacker is a party member?
    if (v0 == 0) {
        // 0x0030ce30: an enemy attacker
        charge(ctx, 25);
        get_value(a0, a1, 0x30CE38u, sel::kStatA, sel::kLu);
        v0 = flt(50.0f);
        mtc1(v0, f1);
        add_s(f20, f1, f0);
        get_value(a0, a1, 0x30CE58u, sel::kStatT, sel::kLu);
        v0 = flt(50.0f);
        mtc1(v0, f1);
        add_s(f0, f1, f0);
        div_s(f20, f20, f0);
        get_value(a0, a1, 0x30CE80u, sel::kSkillByte37, 0);
        mul_s(f1, f0, f20);
        lwc1(f0, gp, gp_off(ai::kLit0_80));  // 0.8
        mul_s(f0, f0, f1);
    } else {
        // 0x0030cdcc: a party attacker
        charge(ctx, 25);
        get_value(a0, a1, 0x30CDD4u, sel::kStatA, sel::kLu);
        v0 = flt(50.0f);
        mtc1(v0, f1);
        add_s(f20, f1, f0);
        get_value(a0, a1, 0x30CDF4u, sel::kStatT, sel::kLu);
        v0 = flt(50.0f);
        mtc1(v0, f1);
        add_s(f0, f1, f0);
        div_s(f20, f20, f0);
        get_value(a0, a1, 0x30CE1Cu, sel::kSkillByte37, 0);
        mul_s(f0, f0, f20);
    }
    // 0x0030ce94: the result; epilogue
    charge(ctx, 9);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30CE9Cu, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030E030 sub_30E030 [datScriptAiLuRate2] -- 272 bytes; frame 0x20: ra sp+0x10, f20 sp+0x0
// Set 2 slot 5 (sDatScriptFuncTbl2[5]): GV(kSkillByte37) * ratio(50, Lu); an enemy attacker's result times 0.5 (a
// lui literal).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30E030(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::charge, hg::cvt_w_s, hg::div_s, hg::enter, hg::jal, hg::ld,
          hg::lwc1, hg::mfc1, hg::mtc1, hg::mul_s, hg::sd, hg::swc1;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f20{ctx, 20};
    // 0x0030e030: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f20, sp, 0x0);
    jal(ctx, 0x30E03Cu, gen::fn_sub_3111F0_003111f0);  // the attacker is a party member?
    if (v0 == 0) {
        // 0x0030e0b0: an enemy attacker
        charge(ctx, 27);
        get_value(a0, a1, 0x30E0B8u, sel::kStatA, sel::kLu);
        v0 = flt(50.0f);
        mtc1(v0, f1);
        add_s(f20, f1, f0);
        get_value(a0, a1, 0x30E0D8u, sel::kStatT, sel::kLu);
        v0 = flt(50.0f);
        mtc1(v0, f1);
        add_s(f0, f1, f0);
        div_s(f20, f20, f0);
        get_value(a0, a1, 0x30E100u, sel::kSkillByte37, 0);
        mul_s(f1, f0, f20);
        v0 = flt(0.5f);
        mtc1(v0, f0);
        mul_s(f0, f0, f1);
    } else {
        // 0x0030e04c: a party attacker
        charge(ctx, 25);
        get_value(a0, a1, 0x30E054u, sel::kStatA, sel::kLu);
        v0 = flt(50.0f);
        mtc1(v0, f1);
        add_s(f20, f1, f0);
        get_value(a0, a1, 0x30E074u, sel::kStatT, sel::kLu);
        v0 = flt(50.0f);
        mtc1(v0, f1);
        add_s(f0, f1, f0);
        div_s(f20, f20, f0);
        get_value(a0, a1, 0x30E09Cu, sel::kSkillByte37, 0);
        mul_s(f0, f0, f20);
    }
    // 0x0030e11c: the result; epilogue
    charge(ctx, 9);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30E124u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030F290 sub_30F290 [datScriptAiLuRate3] -- 264 bytes; frame 0x20: ra sp+0x10, f20 sp+0x0
// Set 3 slot 5 (sDatScriptFuncTbl3[5]): = set 1 slot 5 (sub_30CDB0).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30F290(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::charge, hg::cvt_w_s, hg::div_s, hg::enter, hg::jal, hg::ld,
          hg::lwc1, hg::mfc1, hg::mtc1, hg::mul_s, hg::sd, hg::swc1;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f20{ctx, 20};
    // 0x0030f290: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f20, sp, 0x0);
    jal(ctx, 0x30F29Cu, gen::fn_sub_3111F0_003111f0);  // the attacker is a party member?
    if (v0 == 0) {
        // 0x0030f310: an enemy attacker
        charge(ctx, 25);
        get_value(a0, a1, 0x30F318u, sel::kStatA, sel::kLu);
        v0 = flt(50.0f);
        mtc1(v0, f1);
        add_s(f20, f1, f0);
        get_value(a0, a1, 0x30F338u, sel::kStatT, sel::kLu);
        v0 = flt(50.0f);
        mtc1(v0, f1);
        add_s(f0, f1, f0);
        div_s(f20, f20, f0);
        get_value(a0, a1, 0x30F360u, sel::kSkillByte37, 0);
        mul_s(f1, f0, f20);
        lwc1(f0, gp, gp_off(ai::kLit0_80));  // 0.8
        mul_s(f0, f0, f1);
    } else {
        // 0x0030f2ac: a party attacker
        charge(ctx, 25);
        get_value(a0, a1, 0x30F2B4u, sel::kStatA, sel::kLu);
        v0 = flt(50.0f);
        mtc1(v0, f1);
        add_s(f20, f1, f0);
        get_value(a0, a1, 0x30F2D4u, sel::kStatT, sel::kLu);
        v0 = flt(50.0f);
        mtc1(v0, f1);
        add_s(f0, f1, f0);
        div_s(f20, f20, f0);
        get_value(a0, a1, 0x30F2FCu, sel::kSkillByte37, 0);
        mul_s(f0, f0, f20);
    }
    // 0x0030f374: the result; epilogue
    charge(ctx, 9);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30F37Cu, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030CEC0 sub_30CEC0 [datScriptAiSkillByte38_1] -- 64 bytes; frame 0x10: ra sp+0x0
// Set 1 slot 6 (sDatScriptFuncTbl1[6]): GV(kSkillByte38); the attacker test is made and its result ignored. One block.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30CEC0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::cvt_w_s, hg::enter, hg::jal, hg::ld, hg::mfc1, hg::sd;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x0030cec0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x30CEC8u, gen::fn_sub_3111F0_003111f0);  // the attacker is a party member?
    get_value(a0, a1, 0x30CED8u, sel::kSkillByte38, 0);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30CEE8u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0030E140 sub_30E140 [datScriptAiSkillByte38_2] -- 64 bytes; frame 0x10: ra sp+0x0
// Set 2 slot 6 (sDatScriptFuncTbl2[6]): = set 1 slot 6 (sub_30CEC0).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30E140(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::cvt_w_s, hg::enter, hg::jal, hg::ld, hg::mfc1, hg::sd;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x0030e140
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x30E148u, gen::fn_sub_3111F0_003111f0);  // the attacker is a party member?
    get_value(a0, a1, 0x30E158u, sel::kSkillByte38, 0);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30E168u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0030F3A0 sub_30F3A0 [datScriptAiSkillByte38_3] -- 64 bytes; frame 0x10: ra sp+0x0
// Set 3 slot 6 (sDatScriptFuncTbl3[6]): = set 1 slot 6 (sub_30CEC0).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30F3A0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::cvt_w_s, hg::enter, hg::jal, hg::ld, hg::mfc1, hg::sd;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x0030f3a0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x30F3A8u, gen::fn_sub_3111F0_003111f0);  // the attacker is a party member?
    get_value(a0, a1, 0x30F3B8u, sel::kSkillByte38, 0);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30F3C8u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0030CF00 sub_30CF00 [datScriptAiAgLuRate1] -- 256 bytes; frame 0x20: ra sp+0x10, f21 sp+0x4, f20 sp+0x0
// Set 1 slot 7 (sDatScriptFuncTbl1[7]): 75 * (ratio(100, Ag) * ratio(100, Lu)) + 5 * GV(kBtlB9E) (through MADD). One
// block.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30CF00(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::adda_s, hg::addiu, hg::cvt_w_s, hg::div_s, hg::enter, hg::jal, hg::ld,
          hg::lwc1, hg::madd_s, hg::mfc1, hg::mtc1, hg::mul_s, hg::sd, hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f20{ctx, 20}, f21{ctx, 21};
    // 0x0030cf00: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 64);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    get_value(a0, a1, 0x30CF18u, sel::kStatA, sel::kAg);
    v0 = flt(100.0f);
    mtc1(v0, f1);
    add_s(f20, f1, f0);
    get_value(a0, a1, 0x30CF38u, sel::kStatT, sel::kAg);
    v0 = flt(100.0f);
    mtc1(v0, f1);
    add_s(f0, f1, f0);
    div_s(f21, f20, f0);
    get_value(a0, a1, 0x30CF60u, sel::kStatA, sel::kLu);
    v0 = flt(100.0f);
    mtc1(v0, f1);
    add_s(f20, f1, f0);
    get_value(a0, a1, 0x30CF80u, sel::kStatT, sel::kLu);
    v0 = flt(100.0f);
    mtc1(v0, f1);
    add_s(f0, f1, f0);
    div_s(f0, f20, f0);
    mul_s(f1, f21, f0);
    v0 = flt(75.0f);
    mtc1(v0, f0);
    mul_s(f20, f0, f1);
    get_value(a0, a1, 0x30CFB8u, sel::kBtlB9E, 0);
    v0 = flt(5.0f);
    mtc1(v0, f2);
    mtc1(zero, f1);
    adda_s(f1, f20);
    madd_s(f0, f2, f0);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30CFE0u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030E180 sub_30E180 [datScriptAiAgLuRate2] -- 256 bytes; frame 0x20: ra sp+0x10, f21 sp+0x4, f20 sp+0x0
// Set 2 slot 7 (sDatScriptFuncTbl2[7]): 85 * (ratio(60, Ag) * ratio(30, Lu)) + 5 * GV(kBtlB9E). One block.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30E180(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::adda_s, hg::addiu, hg::cvt_w_s, hg::div_s, hg::enter, hg::jal, hg::ld,
          hg::lwc1, hg::madd_s, hg::mfc1, hg::mtc1, hg::mul_s, hg::sd, hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f20{ctx, 20}, f21{ctx, 21};
    // 0x0030e180: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 64);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    get_value(a0, a1, 0x30E198u, sel::kStatA, sel::kAg);
    v0 = flt(60.0f);
    mtc1(v0, f1);
    add_s(f20, f1, f0);
    get_value(a0, a1, 0x30E1B8u, sel::kStatT, sel::kAg);
    v0 = flt(60.0f);
    mtc1(v0, f1);
    add_s(f0, f1, f0);
    div_s(f21, f20, f0);
    get_value(a0, a1, 0x30E1E0u, sel::kStatA, sel::kLu);
    v0 = flt(30.0f);
    mtc1(v0, f1);
    add_s(f20, f1, f0);
    get_value(a0, a1, 0x30E200u, sel::kStatT, sel::kLu);
    v0 = flt(30.0f);
    mtc1(v0, f1);
    add_s(f0, f1, f0);
    div_s(f0, f20, f0);
    mul_s(f1, f21, f0);
    v0 = flt(85.0f);
    mtc1(v0, f0);
    mul_s(f20, f0, f1);
    get_value(a0, a1, 0x30E238u, sel::kBtlB9E, 0);
    v0 = flt(5.0f);
    mtc1(v0, f2);
    mtc1(zero, f1);
    adda_s(f1, f20);
    madd_s(f0, f2, f0);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30E260u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030F3E0 sub_30F3E0 [datScriptAiAgLuRate3] -- 256 bytes; frame 0x20: ra sp+0x10, f21 sp+0x4, f20 sp+0x0
// Set 3 slot 7 (sDatScriptFuncTbl3[7]): 30 * (ratio(150, Ag) * ratio(150, Lu)) + 5 * GV(kBtlB9E). One block.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30F3E0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::adda_s, hg::addiu, hg::cvt_w_s, hg::div_s, hg::enter, hg::jal, hg::ld,
          hg::lwc1, hg::madd_s, hg::mfc1, hg::mtc1, hg::mul_s, hg::sd, hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f20{ctx, 20}, f21{ctx, 21};
    // 0x0030f3e0: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 64);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    get_value(a0, a1, 0x30F3F8u, sel::kStatA, sel::kAg);
    v0 = flt(150.0f);
    mtc1(v0, f1);
    add_s(f20, f1, f0);
    get_value(a0, a1, 0x30F418u, sel::kStatT, sel::kAg);
    v0 = flt(150.0f);
    mtc1(v0, f1);
    add_s(f0, f1, f0);
    div_s(f21, f20, f0);
    get_value(a0, a1, 0x30F440u, sel::kStatA, sel::kLu);
    v0 = flt(150.0f);
    mtc1(v0, f1);
    add_s(f20, f1, f0);
    get_value(a0, a1, 0x30F460u, sel::kStatT, sel::kLu);
    v0 = flt(150.0f);
    mtc1(v0, f1);
    add_s(f0, f1, f0);
    div_s(f0, f20, f0);
    mul_s(f1, f21, f0);
    v0 = flt(30.0f);
    mtc1(v0, f0);
    mul_s(f20, f0, f1);
    get_value(a0, a1, 0x30F498u, sel::kBtlB9E, 0);
    v0 = flt(5.0f);
    mtc1(v0, f2);
    mtc1(zero, f1);
    adda_s(f1, f20);
    madd_s(f0, f2, f0);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30F4C0u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030D000 sub_30D000 [datScriptAiStatusRate1_8] -- 212 bytes; frame 0x20: ra sp+0x10, f20 sp+0x0
// Set 1 slot 8 (sDatScriptFuncTbl1[8]): Status rate: d = ((0 + 2) + 3 * (GV(kLevelA) - 1)) * GV(kStatusAffinityT); d
// <= 0 gives 1, else 50 * (GV(kStatA, Lu) / d).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30D000(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::adda_s, hg::addiu, hg::c_le_s, hg::charge, hg::cond, hg::cvt_w_s, hg::div_s,
          hg::enter, hg::jal, hg::ld, hg::lwc1, hg::madd_s, hg::mfc1, hg::mtc1, hg::mul_s, hg::sd, hg::sub_s,
          hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20};
    // 0x0030d000: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f20, sp, 0x0);
    get_value(a0, a1, 0x30D014u, sel::kLevelA, 0);
    v0 = flt(1.0f);
    mtc1(v0, f1);
    sub_s(f3, f0, f1);
    v0 = flt(3.0f);
    mtc1(v0, f2);
    v0 = flt(2.0f);
    mtc1(v0, f1);
    mtc1(zero, f0);
    adda_s(f0, f1);
    madd_s(f20, f2, f3);
    get_value(a0, a1, 0x30D054u, sel::kStatusAffinityT, 0);
    mul_s(f20, f20, f0);
    mtc1(zero, f0);
    c_le_s(f20, f0);
    if (cond(ctx)) {
        // 0x0030d0a8
        charge(ctx, 2);
        v0 = flt(1.0f);
        mtc1(v0, f0);
    } else {
        // 0x0030d074
        charge(ctx, 13);
        get_value(a0, a1, 0x30D07Cu, sel::kStatA, sel::kLu);
        div_s(f1, f0, f20);
        v0 = flt(50.0f);
        mtc1(v0, f0);
        mul_s(f0, f0, f1);
    }
    // 0x0030d0b0: the result; epilogue
    charge(ctx, 9);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30D0B8u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030D0E0 sub_30D0E0 [datScriptAiStatusRate1_9] -- 212 bytes; frame 0x20: ra sp+0x10, f20 sp+0x0
// Set 1 slot 9 (sDatScriptFuncTbl1[9]): Status rate: d = ((0 + 2) + 3 * (GV(kLevelA) - 1)) * GV(kStatusAffinityT); d
// <= 0 gives 1, else 50 * (GV(kStatA, Lu) / d).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30D0E0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::adda_s, hg::addiu, hg::c_le_s, hg::charge, hg::cond, hg::cvt_w_s, hg::div_s,
          hg::enter, hg::jal, hg::ld, hg::lwc1, hg::madd_s, hg::mfc1, hg::mtc1, hg::mul_s, hg::sd, hg::sub_s,
          hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20};
    // 0x0030d0e0: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f20, sp, 0x0);
    get_value(a0, a1, 0x30D0F4u, sel::kLevelA, 0);
    v0 = flt(1.0f);
    mtc1(v0, f1);
    sub_s(f3, f0, f1);
    v0 = flt(3.0f);
    mtc1(v0, f2);
    v0 = flt(2.0f);
    mtc1(v0, f1);
    mtc1(zero, f0);
    adda_s(f0, f1);
    madd_s(f20, f2, f3);
    get_value(a0, a1, 0x30D134u, sel::kStatusAffinityT, 0);
    mul_s(f20, f20, f0);
    mtc1(zero, f0);
    c_le_s(f20, f0);
    if (cond(ctx)) {
        // 0x0030d188
        charge(ctx, 2);
        v0 = flt(1.0f);
        mtc1(v0, f0);
    } else {
        // 0x0030d154
        charge(ctx, 13);
        get_value(a0, a1, 0x30D15Cu, sel::kStatA, sel::kLu);
        div_s(f1, f0, f20);
        v0 = flt(50.0f);
        mtc1(v0, f0);
        mul_s(f0, f0, f1);
    }
    // 0x0030d190: the result; epilogue
    charge(ctx, 9);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30D198u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030D1C0 sub_30D1C0 [datScriptAiStatusRate1_10] -- 212 bytes; frame 0x20: ra sp+0x10, f20 sp+0x0
// Set 1 slot 10 (sDatScriptFuncTbl1[10]): Status rate: d = ((0 + 2) + 3 * (GV(kLevelA) - 1)) * GV(kStatusAffinityT);
// d <= 0 gives 1, else 50 * (GV(kStatA, Lu) / d).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30D1C0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::adda_s, hg::addiu, hg::c_le_s, hg::charge, hg::cond, hg::cvt_w_s, hg::div_s,
          hg::enter, hg::jal, hg::ld, hg::lwc1, hg::madd_s, hg::mfc1, hg::mtc1, hg::mul_s, hg::sd, hg::sub_s,
          hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20};
    // 0x0030d1c0: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f20, sp, 0x0);
    get_value(a0, a1, 0x30D1D4u, sel::kLevelA, 0);
    v0 = flt(1.0f);
    mtc1(v0, f1);
    sub_s(f3, f0, f1);
    v0 = flt(3.0f);
    mtc1(v0, f2);
    v0 = flt(2.0f);
    mtc1(v0, f1);
    mtc1(zero, f0);
    adda_s(f0, f1);
    madd_s(f20, f2, f3);
    get_value(a0, a1, 0x30D214u, sel::kStatusAffinityT, 0);
    mul_s(f20, f20, f0);
    mtc1(zero, f0);
    c_le_s(f20, f0);
    if (cond(ctx)) {
        // 0x0030d268
        charge(ctx, 2);
        v0 = flt(1.0f);
        mtc1(v0, f0);
    } else {
        // 0x0030d234
        charge(ctx, 13);
        get_value(a0, a1, 0x30D23Cu, sel::kStatA, sel::kLu);
        div_s(f1, f0, f20);
        v0 = flt(50.0f);
        mtc1(v0, f0);
        mul_s(f0, f0, f1);
    }
    // 0x0030d270: the result; epilogue
    charge(ctx, 9);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30D278u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030D2A0 sub_30D2A0 [datScriptAiStatusRate1_11] -- 212 bytes; frame 0x20: ra sp+0x10, f20 sp+0x0
// Set 1 slot 11 (sDatScriptFuncTbl1[11]): Status rate: d = ((0 + 2) + 3 * (GV(kLevelA) - 1)) * GV(kStatusAffinityT);
// d <= 0 gives 1, else 40 * (GV(kStatA, Lu) / d).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30D2A0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::adda_s, hg::addiu, hg::c_le_s, hg::charge, hg::cond, hg::cvt_w_s, hg::div_s,
          hg::enter, hg::jal, hg::ld, hg::lwc1, hg::madd_s, hg::mfc1, hg::mtc1, hg::mul_s, hg::sd, hg::sub_s,
          hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20};
    // 0x0030d2a0: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f20, sp, 0x0);
    get_value(a0, a1, 0x30D2B4u, sel::kLevelA, 0);
    v0 = flt(1.0f);
    mtc1(v0, f1);
    sub_s(f3, f0, f1);
    v0 = flt(3.0f);
    mtc1(v0, f2);
    v0 = flt(2.0f);
    mtc1(v0, f1);
    mtc1(zero, f0);
    adda_s(f0, f1);
    madd_s(f20, f2, f3);
    get_value(a0, a1, 0x30D2F4u, sel::kStatusAffinityT, 0);
    mul_s(f20, f20, f0);
    mtc1(zero, f0);
    c_le_s(f20, f0);
    if (cond(ctx)) {
        // 0x0030d348
        charge(ctx, 2);
        v0 = flt(1.0f);
        mtc1(v0, f0);
    } else {
        // 0x0030d314
        charge(ctx, 13);
        get_value(a0, a1, 0x30D31Cu, sel::kStatA, sel::kLu);
        div_s(f1, f0, f20);
        v0 = flt(40.0f);
        mtc1(v0, f0);
        mul_s(f0, f0, f1);
    }
    // 0x0030d350: the result; epilogue
    charge(ctx, 9);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30D358u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030D380 sub_30D380 [datScriptAiStatusRate1_12] -- 212 bytes; frame 0x20: ra sp+0x10, f20 sp+0x0
// Set 1 slot 12 (sDatScriptFuncTbl1[12]): Status rate: d = ((0 + 2) + 3 * (GV(kLevelA) - 1)) * GV(kStatusAffinityT);
// d <= 0 gives 1, else 30 * (GV(kStatA, Lu) / d).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30D380(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::adda_s, hg::addiu, hg::c_le_s, hg::charge, hg::cond, hg::cvt_w_s, hg::div_s,
          hg::enter, hg::jal, hg::ld, hg::lwc1, hg::madd_s, hg::mfc1, hg::mtc1, hg::mul_s, hg::sd, hg::sub_s,
          hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20};
    // 0x0030d380: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f20, sp, 0x0);
    get_value(a0, a1, 0x30D394u, sel::kLevelA, 0);
    v0 = flt(1.0f);
    mtc1(v0, f1);
    sub_s(f3, f0, f1);
    v0 = flt(3.0f);
    mtc1(v0, f2);
    v0 = flt(2.0f);
    mtc1(v0, f1);
    mtc1(zero, f0);
    adda_s(f0, f1);
    madd_s(f20, f2, f3);
    get_value(a0, a1, 0x30D3D4u, sel::kStatusAffinityT, 0);
    mul_s(f20, f20, f0);
    mtc1(zero, f0);
    c_le_s(f20, f0);
    if (cond(ctx)) {
        // 0x0030d428
        charge(ctx, 2);
        v0 = flt(1.0f);
        mtc1(v0, f0);
    } else {
        // 0x0030d3f4
        charge(ctx, 13);
        get_value(a0, a1, 0x30D3FCu, sel::kStatA, sel::kLu);
        div_s(f1, f0, f20);
        v0 = flt(30.0f);
        mtc1(v0, f0);
        mul_s(f0, f0, f1);
    }
    // 0x0030d430: the result; epilogue
    charge(ctx, 9);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30D438u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030E280 sub_30E280 [datScriptAiStatusRate2_8] -- 212 bytes; frame 0x20: ra sp+0x10, f20 sp+0x0
// Set 2 slot 8 (sDatScriptFuncTbl2[8]): Status rate: d = ((0 + 2) + 3 * (GV(kLevelA) - 1)) * GV(kStatusAffinityT); d
// <= 0 gives 1, else 50 * (GV(kStatA, Lu) / d).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30E280(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::adda_s, hg::addiu, hg::c_le_s, hg::charge, hg::cond, hg::cvt_w_s, hg::div_s,
          hg::enter, hg::jal, hg::ld, hg::lwc1, hg::madd_s, hg::mfc1, hg::mtc1, hg::mul_s, hg::sd, hg::sub_s,
          hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20};
    // 0x0030e280: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f20, sp, 0x0);
    get_value(a0, a1, 0x30E294u, sel::kLevelA, 0);
    v0 = flt(1.0f);
    mtc1(v0, f1);
    sub_s(f3, f0, f1);
    v0 = flt(3.0f);
    mtc1(v0, f2);
    v0 = flt(2.0f);
    mtc1(v0, f1);
    mtc1(zero, f0);
    adda_s(f0, f1);
    madd_s(f20, f2, f3);
    get_value(a0, a1, 0x30E2D4u, sel::kStatusAffinityT, 0);
    mul_s(f20, f20, f0);
    mtc1(zero, f0);
    c_le_s(f20, f0);
    if (cond(ctx)) {
        // 0x0030e328
        charge(ctx, 2);
        v0 = flt(1.0f);
        mtc1(v0, f0);
    } else {
        // 0x0030e2f4
        charge(ctx, 13);
        get_value(a0, a1, 0x30E2FCu, sel::kStatA, sel::kLu);
        div_s(f1, f0, f20);
        v0 = flt(50.0f);
        mtc1(v0, f0);
        mul_s(f0, f0, f1);
    }
    // 0x0030e330: the result; epilogue
    charge(ctx, 9);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30E338u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030E360 sub_30E360 [datScriptAiStatusRate2_9] -- 212 bytes; frame 0x20: ra sp+0x10, f20 sp+0x0
// Set 2 slot 9 (sDatScriptFuncTbl2[9]): Status rate: d = ((0 + 2) + 3 * (GV(kLevelA) - 1)) * GV(kStatusAffinityT); d
// <= 0 gives 1, else 50 * (GV(kStatA, Lu) / d).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30E360(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::adda_s, hg::addiu, hg::c_le_s, hg::charge, hg::cond, hg::cvt_w_s, hg::div_s,
          hg::enter, hg::jal, hg::ld, hg::lwc1, hg::madd_s, hg::mfc1, hg::mtc1, hg::mul_s, hg::sd, hg::sub_s,
          hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20};
    // 0x0030e360: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f20, sp, 0x0);
    get_value(a0, a1, 0x30E374u, sel::kLevelA, 0);
    v0 = flt(1.0f);
    mtc1(v0, f1);
    sub_s(f3, f0, f1);
    v0 = flt(3.0f);
    mtc1(v0, f2);
    v0 = flt(2.0f);
    mtc1(v0, f1);
    mtc1(zero, f0);
    adda_s(f0, f1);
    madd_s(f20, f2, f3);
    get_value(a0, a1, 0x30E3B4u, sel::kStatusAffinityT, 0);
    mul_s(f20, f20, f0);
    mtc1(zero, f0);
    c_le_s(f20, f0);
    if (cond(ctx)) {
        // 0x0030e408
        charge(ctx, 2);
        v0 = flt(1.0f);
        mtc1(v0, f0);
    } else {
        // 0x0030e3d4
        charge(ctx, 13);
        get_value(a0, a1, 0x30E3DCu, sel::kStatA, sel::kLu);
        div_s(f1, f0, f20);
        v0 = flt(50.0f);
        mtc1(v0, f0);
        mul_s(f0, f0, f1);
    }
    // 0x0030e410: the result; epilogue
    charge(ctx, 9);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30E418u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030E440 sub_30E440 [datScriptAiStatusRate2_10] -- 212 bytes; frame 0x20: ra sp+0x10, f20 sp+0x0
// Set 2 slot 10 (sDatScriptFuncTbl2[10]): Status rate: d = ((0 + 2) + 3 * (GV(kLevelA) - 1)) * GV(kStatusAffinityT);
// d <= 0 gives 1, else 50 * (GV(kStatA, Lu) / d).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30E440(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::adda_s, hg::addiu, hg::c_le_s, hg::charge, hg::cond, hg::cvt_w_s, hg::div_s,
          hg::enter, hg::jal, hg::ld, hg::lwc1, hg::madd_s, hg::mfc1, hg::mtc1, hg::mul_s, hg::sd, hg::sub_s,
          hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20};
    // 0x0030e440: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f20, sp, 0x0);
    get_value(a0, a1, 0x30E454u, sel::kLevelA, 0);
    v0 = flt(1.0f);
    mtc1(v0, f1);
    sub_s(f3, f0, f1);
    v0 = flt(3.0f);
    mtc1(v0, f2);
    v0 = flt(2.0f);
    mtc1(v0, f1);
    mtc1(zero, f0);
    adda_s(f0, f1);
    madd_s(f20, f2, f3);
    get_value(a0, a1, 0x30E494u, sel::kStatusAffinityT, 0);
    mul_s(f20, f20, f0);
    mtc1(zero, f0);
    c_le_s(f20, f0);
    if (cond(ctx)) {
        // 0x0030e4e8
        charge(ctx, 2);
        v0 = flt(1.0f);
        mtc1(v0, f0);
    } else {
        // 0x0030e4b4
        charge(ctx, 13);
        get_value(a0, a1, 0x30E4BCu, sel::kStatA, sel::kLu);
        div_s(f1, f0, f20);
        v0 = flt(50.0f);
        mtc1(v0, f0);
        mul_s(f0, f0, f1);
    }
    // 0x0030e4f0: the result; epilogue
    charge(ctx, 9);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30E4F8u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030E520 sub_30E520 [datScriptAiStatusRate2_11] -- 212 bytes; frame 0x20: ra sp+0x10, f20 sp+0x0
// Set 2 slot 11 (sDatScriptFuncTbl2[11]): Status rate: d = ((0 + 2) + 3 * (GV(kLevelA) - 1)) * GV(kStatusAffinityT);
// d <= 0 gives 1, else 40 * (GV(kStatA, Lu) / d).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30E520(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::adda_s, hg::addiu, hg::c_le_s, hg::charge, hg::cond, hg::cvt_w_s, hg::div_s,
          hg::enter, hg::jal, hg::ld, hg::lwc1, hg::madd_s, hg::mfc1, hg::mtc1, hg::mul_s, hg::sd, hg::sub_s,
          hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20};
    // 0x0030e520: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f20, sp, 0x0);
    get_value(a0, a1, 0x30E534u, sel::kLevelA, 0);
    v0 = flt(1.0f);
    mtc1(v0, f1);
    sub_s(f3, f0, f1);
    v0 = flt(3.0f);
    mtc1(v0, f2);
    v0 = flt(2.0f);
    mtc1(v0, f1);
    mtc1(zero, f0);
    adda_s(f0, f1);
    madd_s(f20, f2, f3);
    get_value(a0, a1, 0x30E574u, sel::kStatusAffinityT, 0);
    mul_s(f20, f20, f0);
    mtc1(zero, f0);
    c_le_s(f20, f0);
    if (cond(ctx)) {
        // 0x0030e5c8
        charge(ctx, 2);
        v0 = flt(1.0f);
        mtc1(v0, f0);
    } else {
        // 0x0030e594
        charge(ctx, 13);
        get_value(a0, a1, 0x30E59Cu, sel::kStatA, sel::kLu);
        div_s(f1, f0, f20);
        v0 = flt(40.0f);
        mtc1(v0, f0);
        mul_s(f0, f0, f1);
    }
    // 0x0030e5d0: the result; epilogue
    charge(ctx, 9);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30E5D8u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030E600 sub_30E600 [datScriptAiStatusRate2_12] -- 212 bytes; frame 0x20: ra sp+0x10, f20 sp+0x0
// Set 2 slot 12 (sDatScriptFuncTbl2[12]): Status rate: d = ((0 + 2) + 3 * (GV(kLevelA) - 1)) * GV(kStatusAffinityT);
// d <= 0 gives 1, else 30 * (GV(kStatA, Lu) / d).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30E600(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::adda_s, hg::addiu, hg::c_le_s, hg::charge, hg::cond, hg::cvt_w_s, hg::div_s,
          hg::enter, hg::jal, hg::ld, hg::lwc1, hg::madd_s, hg::mfc1, hg::mtc1, hg::mul_s, hg::sd, hg::sub_s,
          hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20};
    // 0x0030e600: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f20, sp, 0x0);
    get_value(a0, a1, 0x30E614u, sel::kLevelA, 0);
    v0 = flt(1.0f);
    mtc1(v0, f1);
    sub_s(f3, f0, f1);
    v0 = flt(3.0f);
    mtc1(v0, f2);
    v0 = flt(2.0f);
    mtc1(v0, f1);
    mtc1(zero, f0);
    adda_s(f0, f1);
    madd_s(f20, f2, f3);
    get_value(a0, a1, 0x30E654u, sel::kStatusAffinityT, 0);
    mul_s(f20, f20, f0);
    mtc1(zero, f0);
    c_le_s(f20, f0);
    if (cond(ctx)) {
        // 0x0030e6a8
        charge(ctx, 2);
        v0 = flt(1.0f);
        mtc1(v0, f0);
    } else {
        // 0x0030e674
        charge(ctx, 13);
        get_value(a0, a1, 0x30E67Cu, sel::kStatA, sel::kLu);
        div_s(f1, f0, f20);
        v0 = flt(30.0f);
        mtc1(v0, f0);
        mul_s(f0, f0, f1);
    }
    // 0x0030e6b0: the result; epilogue
    charge(ctx, 9);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30E6B8u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030F4E0 sub_30F4E0 [datScriptAiStatusRate3_8] -- 212 bytes; frame 0x20: ra sp+0x10, f20 sp+0x0
// Set 3 slot 8 (sDatScriptFuncTbl3[8]): Status rate: d = ((0 + 2) + 3 * (GV(kLevelA) - 1)) * GV(kStatusAffinityT); d
// <= 0 gives 1, else 50 * (GV(kStatA, Lu) / d).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30F4E0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::adda_s, hg::addiu, hg::c_le_s, hg::charge, hg::cond, hg::cvt_w_s, hg::div_s,
          hg::enter, hg::jal, hg::ld, hg::lwc1, hg::madd_s, hg::mfc1, hg::mtc1, hg::mul_s, hg::sd, hg::sub_s,
          hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20};
    // 0x0030f4e0: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f20, sp, 0x0);
    get_value(a0, a1, 0x30F4F4u, sel::kLevelA, 0);
    v0 = flt(1.0f);
    mtc1(v0, f1);
    sub_s(f3, f0, f1);
    v0 = flt(3.0f);
    mtc1(v0, f2);
    v0 = flt(2.0f);
    mtc1(v0, f1);
    mtc1(zero, f0);
    adda_s(f0, f1);
    madd_s(f20, f2, f3);
    get_value(a0, a1, 0x30F534u, sel::kStatusAffinityT, 0);
    mul_s(f20, f20, f0);
    mtc1(zero, f0);
    c_le_s(f20, f0);
    if (cond(ctx)) {
        // 0x0030f588
        charge(ctx, 2);
        v0 = flt(1.0f);
        mtc1(v0, f0);
    } else {
        // 0x0030f554
        charge(ctx, 13);
        get_value(a0, a1, 0x30F55Cu, sel::kStatA, sel::kLu);
        div_s(f1, f0, f20);
        v0 = flt(50.0f);
        mtc1(v0, f0);
        mul_s(f0, f0, f1);
    }
    // 0x0030f590: the result; epilogue
    charge(ctx, 9);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30F598u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030F5C0 sub_30F5C0 [datScriptAiStatusRate3_9] -- 212 bytes; frame 0x20: ra sp+0x10, f20 sp+0x0
// Set 3 slot 9 (sDatScriptFuncTbl3[9]): Status rate: d = ((0 + 2) + 3 * (GV(kLevelA) - 1)) * GV(kStatusAffinityT); d
// <= 0 gives 1, else 50 * (GV(kStatA, Lu) / d).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30F5C0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::adda_s, hg::addiu, hg::c_le_s, hg::charge, hg::cond, hg::cvt_w_s, hg::div_s,
          hg::enter, hg::jal, hg::ld, hg::lwc1, hg::madd_s, hg::mfc1, hg::mtc1, hg::mul_s, hg::sd, hg::sub_s,
          hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20};
    // 0x0030f5c0: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f20, sp, 0x0);
    get_value(a0, a1, 0x30F5D4u, sel::kLevelA, 0);
    v0 = flt(1.0f);
    mtc1(v0, f1);
    sub_s(f3, f0, f1);
    v0 = flt(3.0f);
    mtc1(v0, f2);
    v0 = flt(2.0f);
    mtc1(v0, f1);
    mtc1(zero, f0);
    adda_s(f0, f1);
    madd_s(f20, f2, f3);
    get_value(a0, a1, 0x30F614u, sel::kStatusAffinityT, 0);
    mul_s(f20, f20, f0);
    mtc1(zero, f0);
    c_le_s(f20, f0);
    if (cond(ctx)) {
        // 0x0030f668
        charge(ctx, 2);
        v0 = flt(1.0f);
        mtc1(v0, f0);
    } else {
        // 0x0030f634
        charge(ctx, 13);
        get_value(a0, a1, 0x30F63Cu, sel::kStatA, sel::kLu);
        div_s(f1, f0, f20);
        v0 = flt(50.0f);
        mtc1(v0, f0);
        mul_s(f0, f0, f1);
    }
    // 0x0030f670: the result; epilogue
    charge(ctx, 9);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30F678u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030F6A0 sub_30F6A0 [datScriptAiStatusRate3_10] -- 212 bytes; frame 0x20: ra sp+0x10, f20 sp+0x0
// Set 3 slot 10 (sDatScriptFuncTbl3[10]): Status rate: d = ((0 + 2) + 3 * (GV(kLevelA) - 1)) * GV(kStatusAffinityT);
// d <= 0 gives 1, else 50 * (GV(kStatA, Lu) / d).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30F6A0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::adda_s, hg::addiu, hg::c_le_s, hg::charge, hg::cond, hg::cvt_w_s, hg::div_s,
          hg::enter, hg::jal, hg::ld, hg::lwc1, hg::madd_s, hg::mfc1, hg::mtc1, hg::mul_s, hg::sd, hg::sub_s,
          hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20};
    // 0x0030f6a0: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f20, sp, 0x0);
    get_value(a0, a1, 0x30F6B4u, sel::kLevelA, 0);
    v0 = flt(1.0f);
    mtc1(v0, f1);
    sub_s(f3, f0, f1);
    v0 = flt(3.0f);
    mtc1(v0, f2);
    v0 = flt(2.0f);
    mtc1(v0, f1);
    mtc1(zero, f0);
    adda_s(f0, f1);
    madd_s(f20, f2, f3);
    get_value(a0, a1, 0x30F6F4u, sel::kStatusAffinityT, 0);
    mul_s(f20, f20, f0);
    mtc1(zero, f0);
    c_le_s(f20, f0);
    if (cond(ctx)) {
        // 0x0030f748
        charge(ctx, 2);
        v0 = flt(1.0f);
        mtc1(v0, f0);
    } else {
        // 0x0030f714
        charge(ctx, 13);
        get_value(a0, a1, 0x30F71Cu, sel::kStatA, sel::kLu);
        div_s(f1, f0, f20);
        v0 = flt(50.0f);
        mtc1(v0, f0);
        mul_s(f0, f0, f1);
    }
    // 0x0030f750: the result; epilogue
    charge(ctx, 9);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30F758u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030F780 sub_30F780 [datScriptAiStatusRate3_11] -- 212 bytes; frame 0x20: ra sp+0x10, f20 sp+0x0
// Set 3 slot 11 (sDatScriptFuncTbl3[11]): Status rate: d = ((0 + 2) + 3 * (GV(kLevelA) - 1)) * GV(kStatusAffinityT);
// d <= 0 gives 1, else 40 * (GV(kStatA, Lu) / d).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30F780(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::adda_s, hg::addiu, hg::c_le_s, hg::charge, hg::cond, hg::cvt_w_s, hg::div_s,
          hg::enter, hg::jal, hg::ld, hg::lwc1, hg::madd_s, hg::mfc1, hg::mtc1, hg::mul_s, hg::sd, hg::sub_s,
          hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20};
    // 0x0030f780: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f20, sp, 0x0);
    get_value(a0, a1, 0x30F794u, sel::kLevelA, 0);
    v0 = flt(1.0f);
    mtc1(v0, f1);
    sub_s(f3, f0, f1);
    v0 = flt(3.0f);
    mtc1(v0, f2);
    v0 = flt(2.0f);
    mtc1(v0, f1);
    mtc1(zero, f0);
    adda_s(f0, f1);
    madd_s(f20, f2, f3);
    get_value(a0, a1, 0x30F7D4u, sel::kStatusAffinityT, 0);
    mul_s(f20, f20, f0);
    mtc1(zero, f0);
    c_le_s(f20, f0);
    if (cond(ctx)) {
        // 0x0030f828
        charge(ctx, 2);
        v0 = flt(1.0f);
        mtc1(v0, f0);
    } else {
        // 0x0030f7f4
        charge(ctx, 13);
        get_value(a0, a1, 0x30F7FCu, sel::kStatA, sel::kLu);
        div_s(f1, f0, f20);
        v0 = flt(40.0f);
        mtc1(v0, f0);
        mul_s(f0, f0, f1);
    }
    // 0x0030f830: the result; epilogue
    charge(ctx, 9);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30F838u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030F860 sub_30F860 [datScriptAiStatusRate3_12] -- 212 bytes; frame 0x20: ra sp+0x10, f20 sp+0x0
// Set 3 slot 12 (sDatScriptFuncTbl3[12]): Status rate: d = ((0 + 2) + 3 * (GV(kLevelA) - 1)) * GV(kStatusAffinityT);
// d <= 0 gives 1, else 30 * (GV(kStatA, Lu) / d).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30F860(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::adda_s, hg::addiu, hg::c_le_s, hg::charge, hg::cond, hg::cvt_w_s, hg::div_s,
          hg::enter, hg::jal, hg::ld, hg::lwc1, hg::madd_s, hg::mfc1, hg::mtc1, hg::mul_s, hg::sd, hg::sub_s,
          hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20};
    // 0x0030f860: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f20, sp, 0x0);
    get_value(a0, a1, 0x30F874u, sel::kLevelA, 0);
    v0 = flt(1.0f);
    mtc1(v0, f1);
    sub_s(f3, f0, f1);
    v0 = flt(3.0f);
    mtc1(v0, f2);
    v0 = flt(2.0f);
    mtc1(v0, f1);
    mtc1(zero, f0);
    adda_s(f0, f1);
    madd_s(f20, f2, f3);
    get_value(a0, a1, 0x30F8B4u, sel::kStatusAffinityT, 0);
    mul_s(f20, f20, f0);
    mtc1(zero, f0);
    c_le_s(f20, f0);
    if (cond(ctx)) {
        // 0x0030f908
        charge(ctx, 2);
        v0 = flt(1.0f);
        mtc1(v0, f0);
    } else {
        // 0x0030f8d4
        charge(ctx, 13);
        get_value(a0, a1, 0x30F8DCu, sel::kStatA, sel::kLu);
        div_s(f1, f0, f20);
        v0 = flt(30.0f);
        mtc1(v0, f0);
        mul_s(f0, f0, f1);
    }
    // 0x0030f910: the result; epilogue
    charge(ctx, 9);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30F918u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030D460 sub_30D460 [datScriptAiConst100_1_13] -- 52 bytes; frame 0x10: ra sp+0x0
// Set 1 slot 13 (sDatScriptFuncTbl1[13]): The constant 100. One block.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30D460(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::cvt_w_s, hg::enter, hg::jal, hg::ld, hg::mfc1, hg::mtc1, hg::sd;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x0030d460
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = flt(100.0f);
    mtc1(v0, f0);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30D47Cu, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0030D4A0 sub_30D4A0 [datScriptAiConst100_1_14] -- 52 bytes; frame 0x10: ra sp+0x0
// Set 1 slot 14 (sDatScriptFuncTbl1[14]): The constant 100. One block.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30D4A0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::cvt_w_s, hg::enter, hg::jal, hg::ld, hg::mfc1, hg::mtc1, hg::sd;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x0030d4a0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = flt(100.0f);
    mtc1(v0, f0);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30D4BCu, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0030E6E0 sub_30E6E0 [datScriptAiConst100_2_13] -- 52 bytes; frame 0x10: ra sp+0x0
// Set 2 slot 13 (sDatScriptFuncTbl2[13]): The constant 100. One block.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30E6E0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::cvt_w_s, hg::enter, hg::jal, hg::ld, hg::mfc1, hg::mtc1, hg::sd;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x0030e6e0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = flt(100.0f);
    mtc1(v0, f0);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30E6FCu, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0030E720 sub_30E720 [datScriptAiConst100_2_14] -- 52 bytes; frame 0x10: ra sp+0x0
// Set 2 slot 14 (sDatScriptFuncTbl2[14]): The constant 100. One block.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30E720(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::cvt_w_s, hg::enter, hg::jal, hg::ld, hg::mfc1, hg::mtc1, hg::sd;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x0030e720
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = flt(100.0f);
    mtc1(v0, f0);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30E73Cu, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0030F940 sub_30F940 [datScriptAiConst100_3_13] -- 52 bytes; frame 0x10: ra sp+0x0
// Set 3 slot 13 (sDatScriptFuncTbl3[13]): The constant 100. One block.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30F940(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::cvt_w_s, hg::enter, hg::jal, hg::ld, hg::mfc1, hg::mtc1, hg::sd;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x0030f940
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = flt(100.0f);
    mtc1(v0, f0);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30F95Cu, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0030F980 sub_30F980 [datScriptAiConst100_3_14] -- 52 bytes; frame 0x10: ra sp+0x0
// Set 3 slot 14 (sDatScriptFuncTbl3[14]): The constant 100. One block.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30F980(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::cvt_w_s, hg::enter, hg::jal, hg::ld, hg::mfc1, hg::mtc1, hg::sd;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x0030f980
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = flt(100.0f);
    mtc1(v0, f0);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30F99Cu, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0030D4E0 sub_30D4E0 [datScriptAiRoundDamage1] -- 292 bytes; frame 0x20: ra sp+0x10, f20 sp+0x0
// Set 1 slot 15 (sDatScriptFuncTbl1[15]): Round damage: root(En2, St) with P - 30, * GV(kAffinityT) * GV(kLevelDiff)
// * GV(kRound) *
// GV(kLevelDiffBattle) * 0.8. One block.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30D4E0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::cvt_w_s, hg::div_s, hg::enter, hg::jal, hg::ld, hg::lwc1,
          hg::mfc1, hg::mov_s, hg::mtc1, hg::mul_s, hg::sd, hg::sqrt_s, hg::sub_s, hg::swc1;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f20{ctx, 20};
    // 0x0030d4e0: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 73);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f20, sp, 0x0);
    // f20 = En2 = GV(kStatT, kEn) + GV(kStatT, kEn)
    get_value(a0, a1, 0x30D4F4u, sel::kStatT, sel::kEn);
    mov_s(f20, f0);
    get_value(a0, a1, 0x30D508u, sel::kStatT, sel::kEn);
    add_s(f20, f20, f0);
    // f20 = root(f20, stat) = 10 * sqrt(30 * P / (5 * f20) * (GV(kStatA, stat) / 5)), P = GV(kPower)
    get_value(a0, a1, 0x30D51Cu, sel::kPower, 0);
    v0 = flt(30.0f);
    mtc1(v0, f1);
    sub_s(f0, f0, f1);
    mul_s(f1, f1, f0);
    v0 = flt(5.0f);
    mtc1(v0, f0);
    mul_s(f0, f0, f20);
    div_s(f20, f1, f0);
    get_value(a0, a1, 0x30D558u, sel::kStatA, sel::kSt);
    v0 = flt(5.0f);
    mtc1(v0, f1);
    div_s(f0, f0, f1);
    mul_s(f0, f20, f0);
    sqrt_s(f1, f0);
    v0 = flt(10.0f);
    mtc1(v0, f0);
    mul_s(f20, f0, f1);
    get_value(a0, a1, 0x30D590u, sel::kAffinityT, 0);
    mul_s(f20, f20, f0);
    get_value(a0, a1, 0x30D5A4u, sel::kLevelDiff, 0);
    mul_s(f20, f20, f0);
    get_value(a0, a1, 0x30D5B8u, sel::kRound, 0);
    mul_s(f20, f20, f0);
    get_value(a0, a1, 0x30D5CCu, sel::kLevelDiffBattle, 0);
    mul_s(f1, f20, f0);
    lwc1(f0, gp, gp_off(ai::kLit0_80));  // 0.8
    mul_s(f0, f1, f0);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30D5E8u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030E760 sub_30E760 [datScriptAiRoundDamage2] -- 308 bytes; frame 0x20: ra sp+0x10, f20 sp+0x0
// Set 2 slot 15 (sDatScriptFuncTbl2[15]): Round damage as set 1 slot 15 with the level-difference product doubled: 2
// * (root * GV(kAffinityT) *
// GV(kLevelDiff)) * GV(kRound) * GV(kLevelDiffBattle) * 0.8. One block.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30E760(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::cvt_w_s, hg::div_s, hg::enter, hg::jal, hg::ld, hg::lwc1,
          hg::mfc1, hg::mov_s, hg::mtc1, hg::mul_s, hg::sd, hg::sqrt_s, hg::sub_s, hg::swc1;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f20{ctx, 20};
    // 0x0030e760: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 77);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f20, sp, 0x0);
    // f20 = En2 = GV(kStatT, kEn) + GV(kStatT, kEn)
    get_value(a0, a1, 0x30E774u, sel::kStatT, sel::kEn);
    mov_s(f20, f0);
    get_value(a0, a1, 0x30E788u, sel::kStatT, sel::kEn);
    add_s(f20, f20, f0);
    // f20 = root(f20, stat) = 10 * sqrt(30 * P / (5 * f20) * (GV(kStatA, stat) / 5)), P = GV(kPower)
    get_value(a0, a1, 0x30E79Cu, sel::kPower, 0);
    v0 = flt(30.0f);
    mtc1(v0, f1);
    sub_s(f0, f0, f1);
    mul_s(f1, f1, f0);
    v0 = flt(5.0f);
    mtc1(v0, f0);
    mul_s(f0, f0, f20);
    div_s(f20, f1, f0);
    get_value(a0, a1, 0x30E7D8u, sel::kStatA, sel::kSt);
    v0 = flt(5.0f);
    mtc1(v0, f1);
    div_s(f0, f0, f1);
    mul_s(f0, f20, f0);
    sqrt_s(f1, f0);
    v0 = flt(10.0f);
    mtc1(v0, f0);
    mul_s(f20, f0, f1);
    get_value(a0, a1, 0x30E810u, sel::kAffinityT, 0);
    mul_s(f20, f20, f0);
    get_value(a0, a1, 0x30E824u, sel::kLevelDiff, 0);
    mul_s(f1, f20, f0);
    v0 = flt(2.0f);
    mtc1(v0, f0);
    mul_s(f20, f0, f1);
    get_value(a0, a1, 0x30E848u, sel::kRound, 0);
    mul_s(f20, f20, f0);
    get_value(a0, a1, 0x30E85Cu, sel::kLevelDiffBattle, 0);
    mul_s(f1, f20, f0);
    lwc1(f0, gp, gp_off(ai::kLit0_80));  // 0.8
    mul_s(f0, f1, f0);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30E878u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030F9C0 sub_30F9C0 [datScriptAiRoundDamage3] -- 292 bytes; frame 0x20: ra sp+0x10, f20 sp+0x0
// Set 3 slot 15 (sDatScriptFuncTbl3[15]): = set 1 slot 15 (sub_30D4E0).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30F9C0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::cvt_w_s, hg::div_s, hg::enter, hg::jal, hg::ld, hg::lwc1,
          hg::mfc1, hg::mov_s, hg::mtc1, hg::mul_s, hg::sd, hg::sqrt_s, hg::sub_s, hg::swc1;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f20{ctx, 20};
    // 0x0030f9c0: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 73);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f20, sp, 0x0);
    // f20 = En2 = GV(kStatT, kEn) + GV(kStatT, kEn)
    get_value(a0, a1, 0x30F9D4u, sel::kStatT, sel::kEn);
    mov_s(f20, f0);
    get_value(a0, a1, 0x30F9E8u, sel::kStatT, sel::kEn);
    add_s(f20, f20, f0);
    // f20 = root(f20, stat) = 10 * sqrt(30 * P / (5 * f20) * (GV(kStatA, stat) / 5)), P = GV(kPower)
    get_value(a0, a1, 0x30F9FCu, sel::kPower, 0);
    v0 = flt(30.0f);
    mtc1(v0, f1);
    sub_s(f0, f0, f1);
    mul_s(f1, f1, f0);
    v0 = flt(5.0f);
    mtc1(v0, f0);
    mul_s(f0, f0, f20);
    div_s(f20, f1, f0);
    get_value(a0, a1, 0x30FA38u, sel::kStatA, sel::kSt);
    v0 = flt(5.0f);
    mtc1(v0, f1);
    div_s(f0, f0, f1);
    mul_s(f0, f20, f0);
    sqrt_s(f1, f0);
    v0 = flt(10.0f);
    mtc1(v0, f0);
    mul_s(f20, f0, f1);
    get_value(a0, a1, 0x30FA70u, sel::kAffinityT, 0);
    mul_s(f20, f20, f0);
    get_value(a0, a1, 0x30FA84u, sel::kLevelDiff, 0);
    mul_s(f20, f20, f0);
    get_value(a0, a1, 0x30FA98u, sel::kRound, 0);
    mul_s(f20, f20, f0);
    get_value(a0, a1, 0x30FAACu, sel::kLevelDiffBattle, 0);
    mul_s(f1, f20, f0);
    lwc1(f0, gp, gp_off(ai::kLit0_80));  // 0.8
    mul_s(f0, f1, f0);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30FAC8u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030D610 sub_30D610 [datScriptAiStatusAffinity1] -- 316 bytes; frame 0x20: ra sp+0x10, f20 sp+0x0
// Set 1 slot 16 (sDatScriptFuncTbl1[16]): GV(kStatusRate) * GV(kStatusAffinityT) * (100 + GV(kStatA, Lu)) / (100 +
// GV(kStatT, Lu)); an enemy
// attacker's result times 0.8.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30D610(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::charge, hg::cvt_w_s, hg::div_s, hg::enter, hg::jal, hg::ld,
          hg::lwc1, hg::mfc1, hg::mov_s, hg::mtc1, hg::mul_s, hg::sd, hg::swc1;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f20{ctx, 20};
    // 0x0030d610: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f20, sp, 0x0);
    jal(ctx, 0x30D61Cu, gen::fn_sub_3111F0_003111f0);  // the attacker is a party member?
    if (v0 == 0) {
        // 0x0030d6b0: an enemy attacker
        charge(ctx, 30);
        get_value(a0, a1, 0x30D6B8u, sel::kStatusRate, 0);
        mov_s(f20, f0);
        get_value(a0, a1, 0x30D6CCu, sel::kStatusAffinityT, 0);
        mul_s(f20, f20, f0);
        get_value(a0, a1, 0x30D6E0u, sel::kStatA, sel::kLu);
        v0 = flt(100.0f);
        mtc1(v0, f1);
        add_s(f0, f1, f0);
        mul_s(f20, f20, f0);
        get_value(a0, a1, 0x30D704u, sel::kStatT, sel::kLu);
        v0 = flt(100.0f);
        mtc1(v0, f1);
        add_s(f0, f1, f0);
        div_s(f1, f20, f0);
        lwc1(f0, gp, gp_off(ai::kLit0_80));  // 0.8
        mul_s(f0, f0, f1);
    } else {
        // 0x0030d62c: a party attacker
        charge(ctx, 33);
        get_value(a0, a1, 0x30D634u, sel::kStatusRate, 0);
        mov_s(f20, f0);
        get_value(a0, a1, 0x30D648u, sel::kStatusAffinityT, 0);
        mul_s(f20, f20, f0);
        get_value(a0, a1, 0x30D65Cu, sel::kStatA, sel::kLu);
        v0 = flt(100.0f);
        mtc1(v0, f1);
        add_s(f0, f1, f0);
        mul_s(f20, f20, f0);
        get_value(a0, a1, 0x30D680u, sel::kStatT, sel::kLu);
        v0 = flt(100.0f);
        mtc1(v0, f1);
        add_s(f0, f1, f0);
        div_s(f0, f20, f0);
    }
    // 0x0030d728: the result; epilogue
    charge(ctx, 9);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30D730u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030E8A0 sub_30E8A0 [datScriptAiStatusAffinity2] -- 324 bytes; frame 0x20: ra sp+0x10, f20 sp+0x0
// Set 2 slot 16 (sDatScriptFuncTbl2[16]): As set 1 slot 16, an enemy attacker's result times 0.5 (a lui literal).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30E8A0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::charge, hg::cvt_w_s, hg::div_s, hg::enter, hg::jal, hg::ld,
          hg::lwc1, hg::mfc1, hg::mov_s, hg::mtc1, hg::mul_s, hg::sd, hg::swc1;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f20{ctx, 20};
    // 0x0030e8a0: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f20, sp, 0x0);
    jal(ctx, 0x30E8ACu, gen::fn_sub_3111F0_003111f0);  // the attacker is a party member?
    if (v0 == 0) {
        // 0x0030e940: an enemy attacker
        charge(ctx, 32);
        get_value(a0, a1, 0x30E948u, sel::kStatusRate, 0);
        mov_s(f20, f0);
        get_value(a0, a1, 0x30E95Cu, sel::kStatusAffinityT, 0);
        mul_s(f20, f20, f0);
        get_value(a0, a1, 0x30E970u, sel::kStatA, sel::kLu);
        v0 = flt(100.0f);
        mtc1(v0, f1);
        add_s(f0, f1, f0);
        mul_s(f20, f20, f0);
        get_value(a0, a1, 0x30E994u, sel::kStatT, sel::kLu);
        v0 = flt(100.0f);
        mtc1(v0, f1);
        add_s(f0, f1, f0);
        div_s(f1, f20, f0);
        v0 = flt(0.5f);
        mtc1(v0, f0);
        mul_s(f0, f0, f1);
    } else {
        // 0x0030e8bc: a party attacker
        charge(ctx, 33);
        get_value(a0, a1, 0x30E8C4u, sel::kStatusRate, 0);
        mov_s(f20, f0);
        get_value(a0, a1, 0x30E8D8u, sel::kStatusAffinityT, 0);
        mul_s(f20, f20, f0);
        get_value(a0, a1, 0x30E8ECu, sel::kStatA, sel::kLu);
        v0 = flt(100.0f);
        mtc1(v0, f1);
        add_s(f0, f1, f0);
        mul_s(f20, f20, f0);
        get_value(a0, a1, 0x30E910u, sel::kStatT, sel::kLu);
        v0 = flt(100.0f);
        mtc1(v0, f1);
        add_s(f0, f1, f0);
        div_s(f0, f20, f0);
    }
    // 0x0030e9c0: the result; epilogue
    charge(ctx, 9);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30E9C8u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030FAF0 sub_30FAF0 [datScriptAiStatusAffinity3] -- 324 bytes; frame 0x20: ra sp+0x10, f20 sp+0x0
// Set 3 slot 16 (sDatScriptFuncTbl3[16]): As set 1 slot 16, an enemy attacker's result times 1.5 (a lui literal).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills). En2, enemyDef, root(), ratio():
// the building blocks above datScriptGetValue; GV(s, i) = get_value(s, i).
void sub_30FAF0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::charge, hg::cvt_w_s, hg::div_s, hg::enter, hg::jal, hg::ld,
          hg::lwc1, hg::mfc1, hg::mov_s, hg::mtc1, hg::mul_s, hg::sd, hg::swc1;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f20{ctx, 20};
    // 0x0030faf0: prologue (the frame; $ra and the $f20 / $f21 the formula uses saved)
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    swc1(f20, sp, 0x0);
    jal(ctx, 0x30FAFCu, gen::fn_sub_3111F0_003111f0);  // the attacker is a party member?
    if (v0 == 0) {
        // 0x0030fb90: an enemy attacker
        charge(ctx, 32);
        get_value(a0, a1, 0x30FB98u, sel::kStatusRate, 0);
        mov_s(f20, f0);
        get_value(a0, a1, 0x30FBACu, sel::kStatusAffinityT, 0);
        mul_s(f20, f20, f0);
        get_value(a0, a1, 0x30FBC0u, sel::kStatA, sel::kLu);
        v0 = flt(100.0f);
        mtc1(v0, f1);
        add_s(f0, f1, f0);
        mul_s(f20, f20, f0);
        get_value(a0, a1, 0x30FBE4u, sel::kStatT, sel::kLu);
        v0 = flt(100.0f);
        mtc1(v0, f1);
        add_s(f0, f1, f0);
        div_s(f1, f20, f0);
        v0 = flt(1.5f);
        mtc1(v0, f0);
        mul_s(f0, f0, f1);
    } else {
        // 0x0030fb0c: a party attacker
        charge(ctx, 33);
        get_value(a0, a1, 0x30FB14u, sel::kStatusRate, 0);
        mov_s(f20, f0);
        get_value(a0, a1, 0x30FB28u, sel::kStatusAffinityT, 0);
        mul_s(f20, f20, f0);
        get_value(a0, a1, 0x30FB3Cu, sel::kStatA, sel::kLu);
        v0 = flt(100.0f);
        mtc1(v0, f1);
        add_s(f0, f1, f0);
        mul_s(f20, f20, f0);
        get_value(a0, a1, 0x30FB60u, sel::kStatT, sel::kLu);
        v0 = flt(100.0f);
        mtc1(v0, f1);
        add_s(f0, f1, f0);
        div_s(f0, f20, f0);
    }
    // 0x0030fc10: the result; epilogue
    charge(ctx, 9);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    jal(ctx, 0x30FC18u, gen::fn_datScriptSetResult_00311190);  // datScriptSetResult((s32)result)
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}

}  // namespace p3fes::game

// --- the recompiled program's entry points ---------------------------------------------------------------------
namespace p3fes::recomp_gen {
using namespace p3fes::game;
#define P3FES_AI_SHIM(name, addr) \
    void fn_##name##_##addr(p3fes::EEContext& ctx) { name(ctx); }
P3FES_AI_SHIM(nullsub_62, 0030c510)
P3FES_AI_SHIM(nullsub_63, 0030d750)
P3FES_AI_SHIM(nullsub_64, 0030e9f0)
#undef P3FES_AI_SHIM
}  // namespace p3fes::recomp_gen
