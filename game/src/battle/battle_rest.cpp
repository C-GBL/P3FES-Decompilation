// The rest of the datCalc.c battle band (game/include/p3fes/game/battle_rest.h), hand-decompiled from SLUS_216.21
// (docs/ANALYSIS/21_battle.md section 5). Phase 5 slice `battle_rest`: these replace the recompiled bodies listed in
// game/replaced.txt; tests/game/test_battle_rest.cpp runs each against its __recomp body.
//
// Virtual time per ADR-0013: every guest::enter / charge mirrors a `ctx.cycles += N` block of
// recomp/generated/fn_0024_002ff2f0_00315c20.cpp on the executed path (charged before the block's calls), and
// guest::backedge sits where the recompiled loop checks before jumping back. K_Assert (sub_19D3F0) is `jr $ra` in
// retail: a failed check continues with the same loads and stays a call, for its check point and two cycles.
//
// Register discipline. Most of these run inside the battle's action / turn state functions (the battle gate's
// route reaches them), and their callees -- recompiled, or hand-written in other slices -- run on the guest stack
// below them. So every non-leaf function here does what the original did around its calls:
//   * Frame writes the prologue's spills (`sd ra`, `sq s0..s7`, `swc1 f20`) at the original offsets and the
//     epilogue reloads them, so $sp, the frame bytes and the callee-saved registers are the original's;
//   * the s-registers hold, at every call, the values the original kept in them (S(ctx, sN, ...) where the
//     original assigns them), so the callees' own spills write the original bytes;
//   * every call is a `jal` through the callee's generated entry point with $ra = the original link and the
//     argument registers the original set (and only those: a register the original left alone keeps its value);
//   * the float chains run on the guest FPRs ($f0, $f1, $f20) with the recompiler's own FPU primitives, so the
//     callee of datScriptCalc sees the original $f20 (datScriptGetValue can return it) and FCR31 matches;
//   * $v0 at the return is the original's, also for the void functions (the last value the original left there).
// The other caller-saved registers are left as the callees leave them; the compare temporaries the original keeps
// in $v1/$at/$a0..$a3 after its last call are not reproduced (tests/game/test_battle_rest.cpp counts them).
//
// Faithfulness audit (2026-10-21, tools/ours/audit): 36 of the 38 functions here are now p3fes_handgen's register-
// faithful bodies (their hand versions differed from the original: $v0 28, scratch GPRs 6, callee frames 2); each
// keeps the notes of its earlier hand version above it. The others are the hand-written versions this header
// describes.
//
// Readability pass (read_battle, 2026-10-21): the 36 generated bodies keep every statement, charge, check point and
// call of p3fes_handgen's output in the same order on every path. All of them name what they touch (battle_view.h:
// `k_assert`, `hi()/lo()/gp_off()`, `flt()`, `u32_to_float`, the DatUnit fields on the registers that hold a unit for
// the whole body, the enemy / skill record strides and fields); sub_302F50, sub_306610, sub_3068D0, sub_306BC0,
// sub_3083F0, sub_30AF00, sub_30B130, sub_30B210, sub_30B640, sub_30B9A0, sub_30BDE0, sub_30C0C0, datUnitEcAddEnemy,
// sub_2FFB00, sub_300E90 and sub_306020 (its effect -> skill compare chain as a table walk) are restructured without
// gotos and say what each block does; sub_302380, sub_305970, sub_30A740 and sub_301CA0 (550-730 lines) keep the
// generator's remaining gotos.
#include "p3fes/game/battle_rest.h"

#include "p3fes/ee/core.h"
#include "p3fes/ee/hilo.h"
#include "p3fes/game/battle.h"
#include "p3fes/game/battle_calc.h"
#include "p3fes/game/battle_data.h"
#include "p3fes/game/guest.h"

#include <cstddef>
#include <iterator>
#include "p3fes/game/battle_view.h"
#include "p3fes/game/hg_cpu.h"

namespace p3fes::recomp_gen {
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);               // K_Assert(file, line): jr $ra
void fn_datCalcGetEffectLevel_00300f60(p3fes::EEContext&);    // (unit, slot) -> signed nibble
void fn_datCalcSetEffectLevel_00301030(p3fes::EEContext&);    // (unit, slot, level)
void fn_sub_301150_00301150(p3fes::EEContext&);               // [datCalcSetEffectTurns] (unit, slot, turns)
void fn_datCalcAddEffectLevel_00301230(p3fes::EEContext&);    // (unit, slot, delta)
void fn_datCalcRand_002ffbc0(p3fes::EEContext&);              // (n) -> 0..n-1
void fn_datCalcGetElementForStatus_00308120(p3fes::EEContext&);  // (skill, status bit) -> element row
void fn_datCalcGetAffinity_00306e80(p3fes::EEContext&);       // (unit, element) -> affinity word
void fn_datCalcGetAffinityChecked_0030b4b0(p3fes::EEContext&);  // (unit, element) -> affinity word
void fn_datCalcHasSkill_003005e0(p3fes::EEContext&);          // (unit, skill)
void fn_sub_16C920_0016c920(p3fes::EEContext&);               // a party member's condition (u16)
void fn_datGetFlag_0016f190(p3fes::EEContext&);               // (flag)
void fn_datCalcGetSkillElement_003082f0(p3fes::EEContext&);   // (unit, skill)
void fn_datScriptCalc_0030fc40(p3fes::EEContext&);            // (formula, attacker, target, skill, $t0)
void fn_datCalcIsPhysicalSkill_003088b0(p3fes::EEContext&);   // (skill)
void fn_datGetEquipmentIdx_0016cb80(p3fes::EEContext&);       // (pc, slot)
void fn_sub_16F630_0016f630(p3fes::EEContext&);               // [datGetEquipmentItemId] (owner, idx)
void fn_sub_16F900_0016f900(p3fes::EEContext&);               // [datGetEquipmentEffect] (owner, idx)
void fn_sub_170D60_00170d60(p3fes::EEContext&);               // the 40-byte weapon record of an item id
void fn_sub_170760_00170760(p3fes::EEContext&);               // (pc, 4039): a party member's count of something (inf)
void fn_sub_170E90_00170e90(p3fes::EEContext&);               // an item record (+8 = u16)
void fn_datCalcDamage_00303130(p3fes::EEContext&);            // eight arguments, $t0..$t3
void fn_datCalcGetMaxHp_002ffdf0(p3fes::EEContext&);          // (unit)
void fn_datCalcGetMaxSp_00300100(p3fes::EEContext&);          // (unit)
void fn_sub_17D800_0017d800(p3fes::EEContext&);               // reads gp-19788 (a "no cost" mode word, inf)
void fn_datCalcGetSkillSlotCount_00308ba0(p3fes::EEContext&); // 8
void fn_datCalcGetSkillList_00308bb0(p3fes::EEContext&);      // (unit) -> u16[8]
void fn_sub_300750_00300750(p3fes::EEContext&);               // [datCalcHasEquipmentEffect] (pc, effect)
void fn_datCalcGetHeldWeaponType_00308c60(p3fes::EEContext&); // (unit)
void fn_MT_Misc_BitChk_003951d0(p3fes::EEContext&);           // (bit)
void fn_sub_1752B0_001752b0(p3fes::EEContext&);               // a persona id (inf)
void fn_sub_175410_00175410(p3fes::EEContext&);               // [datPersonaGetStockSize]
void fn_sub_174960_00174960(p3fes::EEContext&);               // stock slot in use (inf)
void fn_sub_174A90_00174a90(p3fes::EEContext&);               // [datPersonaGetHeroPersona] (slot)
void fn_sub_16C5F0_0016c5f0(p3fes::EEContext&);               // a party member's max HP (inf)
void fn_sub_16CF40_0016cf40(p3fes::EEContext&);               // set a party member's HP (inf)
void fn_sub_16C670_0016c670(p3fes::EEContext&);               // a party member's max SP (inf)
void fn_sub_16CF90_0016cf90(p3fes::EEContext&);               // set a party member's SP (inf)
void fn_sub_16D9D0_0016d9d0(p3fes::EEContext&);               // clear a party member's statuses (pc, -1) (inf)
void fn_datCalcGetElementBit_003080c0(p3fes::EEContext&);     // (element) -> 1 << (element + 1)
void fn_datCalcGetEffectState_00301750(p3fes::EEContext&);    // (unit, slot)
void fn_datUnitInit_002ff890(p3fes::EEContext&);              // (unit, kind, id)
void fn_sub_16CA90_0016ca90(p3fes::EEContext&);               // (pc, -1): a party member's turn update (inf)
void fn_sub_16C9F0_0016c9f0(p3fes::EEContext&);               // (pc): a party member's flag word (inf)
void fn_sub_16D6B0_0016d6b0(p3fes::EEContext&);               // (pc, 3): set a party member's condition (inf)
void fn_scrSetFloatReturnVal_0035f080(p3fes::EEContext&);     // ($f12)
void fn_scrSetIntReturnVal_0035f060(p3fes::EEContext&);       // (value)
void fn_datCalcRestorePartyAll_0030c440(p3fes::EEContext&);   // this file
void fn_sub_305970_00305970(p3fes::EEContext&);               // this file
void fn_sub_306020_00306020(p3fes::EEContext&);               // this file
void fn_sub_3083F0_003083f0(p3fes::EEContext&);               // this file
void fn_sub_30AF00_0030af00(p3fes::EEContext&);               // this file
void fn_sub_30C490_0030c490(p3fes::EEContext&);               // this file
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

using namespace bview;  // hi / lo / gp_off / flt / k_assert / u32_to_float and the record offsets (battle_view.h)

namespace {

using namespace btl;
namespace rg = p3fes::recomp_gen;

// --- registers ---------------------------------------------------------------------------------------------------
constexpr unsigned kS0 = 16;
constexpr unsigned kA0 = GPR_A0, kA1 = GPR_A1, kV0 = GPR_V0;

u64 R(const EEContext& ctx, unsigned r) { return ee::core::gpr64(ctx, r); }
void S(EEContext& ctx, unsigned r, u64 v) { ee::core::set_gpr64(ctx, r, v); }
u64 sx16(u64 v) { return static_cast<u64>(static_cast<s64>(static_cast<s16>(static_cast<u16>(v)))); }
u32 a32(u64 v) { return static_cast<u32>(v); }

template <typename T> T ld(const EEContext& ctx, u64 va) { return guest::load<T>(ctx, a32(va)); }
template <typename T> void st(EEContext& ctx, u64 va, T v) { guest::store<T>(ctx, a32(va), v); }

// `jal fn` at `pc` ($ra = pc + 8) through the callee's generated entry point; returns $v0.
u64 jal(EEContext& ctx, u32 pc, guest::Fn fn) {
    rt::jal(ctx, pc);
    fn(ctx);
    return R(ctx, kV0);
}

// The prologue `addiu sp, sp, -size; sd ra, ra_off; sq s<top>..s0 at ra_off - 16, ra_off - 32, ...; [swc1 f20, 0]`
// and, on destruction, its epilogue (the reloads from the guest stack, `addiu sp, sp, size`).
class Frame {
public:
    Frame(EEContext& ctx, u32 size, u32 ra_off, unsigned top_s, bool f20 = false) noexcept
        : ctx_(ctx), size_(size), ra_off_(ra_off), top_s_(top_s), f20_(f20) {
        rt::addiu(ctx_, GPR_SP, GPR_SP, -static_cast<s32>(size_));
        rt::sd(ctx_, GPR_RA, GPR_SP, static_cast<s32>(ra_off_));
        for (unsigned r = top_s_; r >= kS0; --r) rt::sq(ctx_, r, GPR_SP, slot(r));
        if (f20_) rt::swc1(ctx_, 20, GPR_SP, 0);
    }
    ~Frame() {
        rt::ld(ctx_, GPR_RA, GPR_SP, static_cast<s32>(ra_off_));
        for (unsigned r = top_s_; r >= kS0; --r) rt::lq(ctx_, r, GPR_SP, slot(r));
        if (f20_) rt::lwc1(ctx_, 20, GPR_SP, 0);
        rt::addiu(ctx_, GPR_SP, GPR_SP, static_cast<s32>(size_));
    }
    Frame(const Frame&) = delete;
    Frame& operator=(const Frame&) = delete;
    u32 sp() const noexcept { return ee::core::gpr32(ctx_, GPR_SP); }  // the frame base (stack buffers live here)

private:
    s32 slot(unsigned r) const noexcept { return static_cast<s32>(ra_off_ - 16u * (top_s_ - r + 1u)); }
    EEContext& ctx_;
    u32 size_, ra_off_;
    unsigned top_s_;
    bool f20_;
};

// --- FPU (on the guest registers) --------------------------------------------------------------------------------

}  // namespace

// ================================================================================================================
// Buff slots
// ================================================================================================================

// 0x00302380 sub_302380 -- 2248 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [datCalcApplyEffectMask](unit, mask, delta): each mask bit is one buff-slot change. Bits 0..9 are
// +delta / -delta (sign-extended byte) on slots 0..4 in pairs, bits 10/11 +delta on slots 19/20, bit 12 clears the
// raised slots 0..4, bit 13 the lowered slots 0..4 and the raised walls 13..16, bits 14..26 +delta on 5, 6, 17, 18,
// 13..16, 7..11. Every change goes through datCalcAddEffectLevel.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_302380(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::i64, hg::jal, hg::ld, hg::lq,
          hg::lui, hg::lw, hg::sd, hg::si, hg::sq, hg::subu, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00302380: prologue
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    if (s1 != 0) {
        // 0x003023a8
        charge(ctx, 3);
        v1 = s1 & 0x1;
        if (v1 != 0) {
            // 0x003023b4
            charge(ctx, 3);
            a1 = 0;
            jal(ctx, 0x3023B8u, gen::fn_datCalcAddEffectLevel_00301230);
        }
        // 0x003023c0
        charge(ctx, 3);
        v1 = s1 & 0x2;
        if (v1 != 0) {
            // 0x003023cc
            charge(ctx, 9);
            v0 = dsll32(s0, 24);
            v0 = dsra32(v0, 24);
            v0 = subu(0, v0);
            a2 = dsll32(v0, 24);
            a2 = dsra32(a2, 24);
            a0 = s2;
            a1 = 0;
            jal(ctx, 0x3023E8u, gen::fn_datCalcAddEffectLevel_00301230);
        }
        // 0x003023f0
        charge(ctx, 3);
        v1 = s1 & 0x4;
        if (v1 != 0) {
            // 0x003023fc
            charge(ctx, 5);
            a0 = s2;
            a1 = 1;
            a2 = s0;
            jal(ctx, 0x302408u, gen::fn_datCalcAddEffectLevel_00301230);
        }
        // 0x00302410
        charge(ctx, 3);
        v1 = s1 & 0x8;
        if (v1 != 0) {
            // 0x0030241c
            charge(ctx, 9);
            v0 = dsll32(s0, 24);
            v0 = dsra32(v0, 24);
            v0 = subu(0, v0);
            a2 = dsll32(v0, 24);
            a2 = dsra32(a2, 24);
            a0 = s2;
            a1 = 1;
            jal(ctx, 0x302438u, gen::fn_datCalcAddEffectLevel_00301230);
        }
        // 0x00302440
        charge(ctx, 3);
        v1 = s1 & 0x10;
        if (v1 != 0) {
            // 0x0030244c
            charge(ctx, 5);
            a0 = s2;
            a1 = 2;
            a2 = s0;
            jal(ctx, 0x302458u, gen::fn_datCalcAddEffectLevel_00301230);
        }
        // 0x00302460
        charge(ctx, 3);
        v1 = s1 & 0x20;
        if (v1 != 0) {
            // 0x0030246c
            charge(ctx, 9);
            v0 = dsll32(s0, 24);
            v0 = dsra32(v0, 24);
            v0 = subu(0, v0);
            a2 = dsll32(v0, 24);
            a2 = dsra32(a2, 24);
            a0 = s2;
            a1 = 2;
            jal(ctx, 0x302488u, gen::fn_datCalcAddEffectLevel_00301230);
        }
        // 0x00302490
        charge(ctx, 3);
        v1 = s1 & 0x40;
        if (v1 != 0) {
            // 0x0030249c
            charge(ctx, 5);
            a0 = s2;
            a1 = 3;
            a2 = s0;
            jal(ctx, 0x3024A8u, gen::fn_datCalcAddEffectLevel_00301230);
        }
        // 0x003024b0
        charge(ctx, 3);
        v1 = s1 & 0x80;
        if (v1 != 0) {
            // 0x003024bc
            charge(ctx, 9);
            v0 = dsll32(s0, 24);
            v0 = dsra32(v0, 24);
            v0 = subu(0, v0);
            a2 = dsll32(v0, 24);
            a2 = dsra32(a2, 24);
            a0 = s2;
            a1 = 3;
            jal(ctx, 0x3024D8u, gen::fn_datCalcAddEffectLevel_00301230);
        }
        // 0x003024e0
        charge(ctx, 3);
        v1 = s1 & 0x100;
        if (v1 != 0) {
            // 0x003024ec
            charge(ctx, 5);
            a0 = s2;
            a1 = 4;
            a2 = s0;
            jal(ctx, 0x3024F8u, gen::fn_datCalcAddEffectLevel_00301230);
        }
        // 0x00302500
        charge(ctx, 3);
        v1 = s1 & 0x200;
        if (v1 != 0) {
            // 0x0030250c
            charge(ctx, 9);
            v0 = dsll32(s0, 24);
            v0 = dsra32(v0, 24);
            v0 = subu(0, v0);
            a2 = dsll32(v0, 24);
            a2 = dsra32(a2, 24);
            a0 = s2;
            a1 = 4;
            jal(ctx, 0x302528u, gen::fn_datCalcAddEffectLevel_00301230);
        }
        // 0x00302530
        charge(ctx, 3);
        v1 = s1 & 0x400;
        if (v1 != 0) {
            // 0x0030253c
            charge(ctx, 5);
            a0 = s2;
            a1 = 19;
            a2 = s0;
            jal(ctx, 0x302548u, gen::fn_datCalcAddEffectLevel_00301230);
        }
        // 0x00302550
        charge(ctx, 3);
        v1 = s1 & 0x800;
        if (v1 != 0) {
            // 0x0030255c
            charge(ctx, 5);
            a0 = s2;
            a1 = 20;
            a2 = s0;
            jal(ctx, 0x302568u, gen::fn_datCalcAddEffectLevel_00301230);
        }
        // 0x00302570
        charge(ctx, 3);
        v1 = s1 & 0x1000;
        if (v1 != 0) {
            // 0x0030257c
            charge(ctx, 8);
            a0 = s2;
            a1 = 0;
            jal(ctx, 0x302584u, gen::fn_datCalcGetEffectLevel_00300f60);
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
            if (i64(v0) > 0) {
                // 0x0030259c
                charge(ctx, 14);
                a0 = s2;
                a1 = 0;
                a2 = 0;
                jal(ctx, 0x3025A8u, gen::fn_datCalcSetEffectLevel_00301030);
                a0 = s2;
                a1 = 0;
                a2 = 0;
                jal(ctx, 0x3025BCu, gen::fn_sub_301150_00301150);
                lw(v1, s2, dat_unit::kEffectFlags);
                v0 = si(-2);
                v0 = v1 & v0;
                sw(v0, s2, dat_unit::kEffectFlags);
            }
            // 0x003025d4
            charge(ctx, 8);
            a0 = s2;
            a1 = 1;
            jal(ctx, 0x3025DCu, gen::fn_datCalcGetEffectLevel_00300f60);
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
            if (i64(v0) > 0) {
                // 0x003025f4
                charge(ctx, 14);
                a0 = s2;
                a1 = 1;
                a2 = 0;
                jal(ctx, 0x302600u, gen::fn_datCalcSetEffectLevel_00301030);
                a0 = s2;
                a1 = 1;
                a2 = 0;
                jal(ctx, 0x302614u, gen::fn_sub_301150_00301150);
                lw(v1, s2, dat_unit::kEffectFlags);
                v0 = si(-3);
                v0 = v1 & v0;
                sw(v0, s2, dat_unit::kEffectFlags);
            }
            // 0x0030262c
            charge(ctx, 8);
            a0 = s2;
            a1 = 2;
            jal(ctx, 0x302634u, gen::fn_datCalcGetEffectLevel_00300f60);
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
            if (i64(v0) > 0) {
                // 0x0030264c
                charge(ctx, 14);
                a0 = s2;
                a1 = 2;
                a2 = 0;
                jal(ctx, 0x302658u, gen::fn_datCalcSetEffectLevel_00301030);
                a0 = s2;
                a1 = 2;
                a2 = 0;
                jal(ctx, 0x30266Cu, gen::fn_sub_301150_00301150);
                lw(v1, s2, dat_unit::kEffectFlags);
                v0 = si(-5);
                v0 = v1 & v0;
                sw(v0, s2, dat_unit::kEffectFlags);
            }
            // 0x00302684
            charge(ctx, 8);
            a0 = s2;
            a1 = 3;
            jal(ctx, 0x30268Cu, gen::fn_datCalcGetEffectLevel_00300f60);
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
            if (i64(v0) > 0) {
                // 0x003026a4
                charge(ctx, 14);
                a0 = s2;
                a1 = 3;
                a2 = 0;
                jal(ctx, 0x3026B0u, gen::fn_datCalcSetEffectLevel_00301030);
                a0 = s2;
                a1 = 3;
                a2 = 0;
                jal(ctx, 0x3026C4u, gen::fn_sub_301150_00301150);
                lw(v1, s2, dat_unit::kEffectFlags);
                v0 = si(-9);
                v0 = v1 & v0;
                sw(v0, s2, dat_unit::kEffectFlags);
            }
            // 0x003026dc
            charge(ctx, 8);
            a0 = s2;
            a1 = 4;
            jal(ctx, 0x3026E4u, gen::fn_datCalcGetEffectLevel_00300f60);
            v1 = dsll32(v0, 24);
            v1 = dsra32(v1, 24);
            if (i64(v1) > 0) {
                // 0x003026fc
                charge(ctx, 14);
                a0 = s2;
                a1 = 4;
                a2 = 0;
                jal(ctx, 0x302708u, gen::fn_datCalcSetEffectLevel_00301030);
                a0 = s2;
                a1 = 4;
                a2 = 0;
                jal(ctx, 0x30271Cu, gen::fn_sub_301150_00301150);
                lw(a0, s2, dat_unit::kEffectFlags);
                v1 = si(-17);
                v1 = a0 & v1;
                sw(v1, s2, dat_unit::kEffectFlags);
            }
        }
        // 0x00302734
        charge(ctx, 3);
        v1 = s1 & 0x2000;
        if (v1 != 0) {
            // 0x00302740
            charge(ctx, 8);
            a0 = s2;
            a1 = 0;
            jal(ctx, 0x302748u, gen::fn_datCalcGetEffectLevel_00300f60);
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
            if (i64(v0) < 0) {
                // 0x00302760
                charge(ctx, 14);
                a0 = s2;
                a1 = 0;
                a2 = 0;
                jal(ctx, 0x30276Cu, gen::fn_datCalcSetEffectLevel_00301030);
                a0 = s2;
                a1 = 0;
                a2 = 0;
                jal(ctx, 0x302780u, gen::fn_sub_301150_00301150);
                lw(v1, s2, dat_unit::kEffectFlags);
                v0 = si(-2);
                v0 = v1 & v0;
                sw(v0, s2, dat_unit::kEffectFlags);
            }
            // 0x00302798
            charge(ctx, 8);
            a0 = s2;
            a1 = 1;
            jal(ctx, 0x3027A0u, gen::fn_datCalcGetEffectLevel_00300f60);
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
            if (i64(v0) < 0) {
                // 0x003027b8
                charge(ctx, 14);
                a0 = s2;
                a1 = 1;
                a2 = 0;
                jal(ctx, 0x3027C4u, gen::fn_datCalcSetEffectLevel_00301030);
                a0 = s2;
                a1 = 1;
                a2 = 0;
                jal(ctx, 0x3027D8u, gen::fn_sub_301150_00301150);
                lw(v1, s2, dat_unit::kEffectFlags);
                v0 = si(-3);
                v0 = v1 & v0;
                sw(v0, s2, dat_unit::kEffectFlags);
            }
            // 0x003027f0
            charge(ctx, 8);
            a0 = s2;
            a1 = 2;
            jal(ctx, 0x3027F8u, gen::fn_datCalcGetEffectLevel_00300f60);
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
            if (i64(v0) < 0) {
                // 0x00302810
                charge(ctx, 14);
                a0 = s2;
                a1 = 2;
                a2 = 0;
                jal(ctx, 0x30281Cu, gen::fn_datCalcSetEffectLevel_00301030);
                a0 = s2;
                a1 = 2;
                a2 = 0;
                jal(ctx, 0x302830u, gen::fn_sub_301150_00301150);
                lw(v1, s2, dat_unit::kEffectFlags);
                v0 = si(-5);
                v0 = v1 & v0;
                sw(v0, s2, dat_unit::kEffectFlags);
            }
            // 0x00302848
            charge(ctx, 8);
            a0 = s2;
            a1 = 3;
            jal(ctx, 0x302850u, gen::fn_datCalcGetEffectLevel_00300f60);
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
            if (i64(v0) < 0) {
                // 0x00302868
                charge(ctx, 14);
                a0 = s2;
                a1 = 3;
                a2 = 0;
                jal(ctx, 0x302874u, gen::fn_datCalcSetEffectLevel_00301030);
                a0 = s2;
                a1 = 3;
                a2 = 0;
                jal(ctx, 0x302888u, gen::fn_sub_301150_00301150);
                lw(v1, s2, dat_unit::kEffectFlags);
                v0 = si(-9);
                v0 = v1 & v0;
                sw(v0, s2, dat_unit::kEffectFlags);
            }
            // 0x003028a0
            charge(ctx, 8);
            a0 = s2;
            a1 = 4;
            jal(ctx, 0x3028A8u, gen::fn_datCalcGetEffectLevel_00300f60);
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
            if (i64(v0) < 0) {
                // 0x003028c0
                charge(ctx, 14);
                a0 = s2;
                a1 = 4;
                a2 = 0;
                jal(ctx, 0x3028CCu, gen::fn_datCalcSetEffectLevel_00301030);
                a0 = s2;
                a1 = 4;
                a2 = 0;
                jal(ctx, 0x3028E0u, gen::fn_sub_301150_00301150);
                lw(v1, s2, dat_unit::kEffectFlags);
                v0 = si(-17);
                v0 = v1 & v0;
                sw(v0, s2, dat_unit::kEffectFlags);
            }
            // 0x003028f8
            charge(ctx, 8);
            a0 = s2;
            a1 = 13;
            jal(ctx, 0x302900u, gen::fn_datCalcGetEffectLevel_00300f60);
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
            if (i64(v0) > 0) {
                // 0x00302918
                charge(ctx, 14);
                a0 = s2;
                a1 = 13;
                a2 = 0;
                jal(ctx, 0x302924u, gen::fn_datCalcSetEffectLevel_00301030);
                a0 = s2;
                a1 = 13;
                a2 = 0;
                jal(ctx, 0x302938u, gen::fn_sub_301150_00301150);
                lw(v1, s2, dat_unit::kEffectFlags);
                v0 = si(-8193);
                v0 = v1 & v0;
                sw(v0, s2, dat_unit::kEffectFlags);
            }
            // 0x00302950
            charge(ctx, 8);
            a0 = s2;
            a1 = 14;
            jal(ctx, 0x302958u, gen::fn_datCalcGetEffectLevel_00300f60);
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
            if (i64(v0) > 0) {
                // 0x00302970
                charge(ctx, 14);
                a0 = s2;
                a1 = 14;
                a2 = 0;
                jal(ctx, 0x30297Cu, gen::fn_datCalcSetEffectLevel_00301030);
                a0 = s2;
                a1 = 14;
                a2 = 0;
                jal(ctx, 0x302990u, gen::fn_sub_301150_00301150);
                lw(v1, s2, dat_unit::kEffectFlags);
                v0 = si(-16385);
                v0 = v1 & v0;
                sw(v0, s2, dat_unit::kEffectFlags);
            }
            // 0x003029a8
            charge(ctx, 8);
            a0 = s2;
            a1 = 15;
            jal(ctx, 0x3029B0u, gen::fn_datCalcGetEffectLevel_00300f60);
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
            if (i64(v0) > 0) {
                // 0x003029c8
                charge(ctx, 15);
                a0 = s2;
                a1 = 15;
                a2 = 0;
                jal(ctx, 0x3029D4u, gen::fn_datCalcSetEffectLevel_00301030);
                a0 = s2;
                a1 = 15;
                a2 = 0;
                jal(ctx, 0x3029E8u, gen::fn_sub_301150_00301150);
                lw(v1, s2, dat_unit::kEffectFlags);
                v0 = lui(0xFFFF);
                v0 = v0 | 0x7FFF;
                v0 = v1 & v0;
                sw(v0, s2, dat_unit::kEffectFlags);
            }
            // 0x00302a04
            charge(ctx, 8);
            a0 = s2;
            a1 = 16;
            jal(ctx, 0x302A0Cu, gen::fn_datCalcGetEffectLevel_00300f60);
            v1 = dsll32(v0, 24);
            v1 = dsra32(v1, 24);
            if (i64(v1) > 0) {
                // 0x00302a24
                charge(ctx, 15);
                a0 = s2;
                a1 = 16;
                a2 = 0;
                jal(ctx, 0x302A30u, gen::fn_datCalcSetEffectLevel_00301030);
                a0 = s2;
                a1 = 16;
                a2 = 0;
                jal(ctx, 0x302A44u, gen::fn_sub_301150_00301150);
                lw(a0, s2, dat_unit::kEffectFlags);
                v1 = lui(0xFFFE);
                v1 = v1 | 0xFFFF;
                v1 = a0 & v1;
                sw(v1, s2, dat_unit::kEffectFlags);
            }
        }
        // 0x00302a60
        charge(ctx, 3);
        v1 = s1 & 0x4000;
        if (v1 != 0) {
            // 0x00302a6c
            charge(ctx, 5);
            a0 = s2;
            a1 = 5;
            a2 = s0;
            jal(ctx, 0x302A78u, gen::fn_datCalcAddEffectLevel_00301230);
        }
        // 0x00302a80
        charge(ctx, 3);
        v1 = s1 & 0x8000;
        if (v1 != 0) {
            // 0x00302a8c
            charge(ctx, 5);
            a0 = s2;
            a1 = 6;
            a2 = s0;
            jal(ctx, 0x302A98u, gen::fn_datCalcAddEffectLevel_00301230);
        }
        // 0x00302aa0
        charge(ctx, 4);
        v1 = 0x10000;
        v1 = s1 & v1;
        if (v1 != 0) {
            // 0x00302ab0
            charge(ctx, 5);
            a0 = s2;
            a1 = 17;
            a2 = s0;
            jal(ctx, 0x302ABCu, gen::fn_datCalcAddEffectLevel_00301230);
        }
        // 0x00302ac4
        charge(ctx, 4);
        v1 = 0x20000;
        v1 = s1 & v1;
        if (v1 != 0) {
            // 0x00302ad4
            charge(ctx, 5);
            a0 = s2;
            a1 = 18;
            a2 = s0;
            jal(ctx, 0x302AE0u, gen::fn_datCalcAddEffectLevel_00301230);
        }
        // 0x00302ae8
        charge(ctx, 4);
        v1 = 0x40000;
        v1 = s1 & v1;
        if (v1 != 0) {
            // 0x00302af8
            charge(ctx, 5);
            a0 = s2;
            a1 = 13;
            a2 = s0;
            jal(ctx, 0x302B04u, gen::fn_datCalcAddEffectLevel_00301230);
        }
        // 0x00302b0c
        charge(ctx, 4);
        v1 = 0x80000;
        v1 = s1 & v1;
        if (v1 != 0) {
            // 0x00302b1c
            charge(ctx, 5);
            a0 = s2;
            a1 = 14;
            a2 = s0;
            jal(ctx, 0x302B28u, gen::fn_datCalcAddEffectLevel_00301230);
        }
        // 0x00302b30
        charge(ctx, 4);
        v1 = 0x100000;
        v1 = s1 & v1;
        if (v1 != 0) {
            // 0x00302b40
            charge(ctx, 5);
            a0 = s2;
            a1 = 15;
            a2 = s0;
            jal(ctx, 0x302B4Cu, gen::fn_datCalcAddEffectLevel_00301230);
        }
        // 0x00302b54
        charge(ctx, 4);
        v1 = 0x200000;
        v1 = s1 & v1;
        if (v1 != 0) {
            // 0x00302b64
            charge(ctx, 5);
            a0 = s2;
            a1 = 16;
            a2 = s0;
            jal(ctx, 0x302B70u, gen::fn_datCalcAddEffectLevel_00301230);
        }
        // 0x00302b78
        charge(ctx, 4);
        v1 = 0x400000;
        v1 = s1 & v1;
        if (v1 != 0) {
            // 0x00302b88
            charge(ctx, 5);
            a0 = s2;
            a1 = 7;
            a2 = s0;
            jal(ctx, 0x302B94u, gen::fn_datCalcAddEffectLevel_00301230);
        }
        // 0x00302b9c
        charge(ctx, 4);
        v1 = 0x800000;
        v1 = s1 & v1;
        if (v1 != 0) {
            // 0x00302bac
            charge(ctx, 5);
            a0 = s2;
            a1 = 8;
            a2 = s0;
            jal(ctx, 0x302BB8u, gen::fn_datCalcAddEffectLevel_00301230);
        }
        // 0x00302bc0
        charge(ctx, 4);
        v1 = 0x1000000;
        v1 = s1 & v1;
        if (v1 != 0) {
            // 0x00302bd0
            charge(ctx, 5);
            a0 = s2;
            a1 = 9;
            a2 = s0;
            jal(ctx, 0x302BDCu, gen::fn_datCalcAddEffectLevel_00301230);
        }
        // 0x00302be4
        charge(ctx, 4);
        v1 = 0x2000000;
        v1 = s1 & v1;
        if (v1 != 0) {
            // 0x00302bf4
            charge(ctx, 5);
            a0 = s2;
            a1 = 10;
            a2 = s0;
            jal(ctx, 0x302C00u, gen::fn_datCalcAddEffectLevel_00301230);
        }
        // 0x00302c08
        charge(ctx, 4);
        v1 = 0x4000000;
        v1 = s1 & v1;
        if (v1 != 0) {
            // 0x00302c18
            charge(ctx, 5);
            a0 = s2;
            a1 = 11;
            a2 = s0;
            jal(ctx, 0x302C24u, gen::fn_datCalcAddEffectLevel_00301230);
        }
    }
    // 0x00302c2c: epilogue
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00302C50 sub_302C50 -- 236 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [datCalcClearMaskedEffects](unit): every slot whose bit is set in the unit's +0x18 mask loses its level
// and turn counter (slots < 17) and its +0x14 flag bit; then the mask is cleared. Nothing happens for mask 0.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_302C50(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::nor, hg::sd,
          hg::sllv, hg::slti, hg::sltiu, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00302c50: prologue
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(s0, a0, 24);
    if (s0 != 0) {
        // 0x00302c78
        charge(ctx, 3);
        s1 = 0;
        for (;;) {
            // 0x00302d0c
            charge(ctx, 3);
            v1 = sltiu(s1, 21);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00302c84
            charge(ctx, 5);
            v1 = 1;
            v1 = sllv(v1, s1);
            v1 = s0 & v1;
            if (v1 != 0) {
                // 0x00302c98
                charge(ctx, 4);
                s3 = s1 & 0xFF;
                v1 = slti(s3, 21);
                if (v1 == 0) {
                    // 0x00302ca8
                    charge(ctx, 5);
                    k_assert(a0, a1, 0x302CB4u, kDatCalcFile, 1177);
                }
                // 0x00302cbc
                charge(ctx, 3);
                at = slti(s3, 17);
                if (at != 0) {
                    // 0x00302cc8
                    charge(ctx, 10);
                    a1 = s1 & 0xFF;
                    a0 = s2;
                    a2 = 0;
                    jal(ctx, 0x302CD4u, gen::fn_datCalcSetEffectLevel_00301030);
                    a1 = s1 & 0xFF;
                    a0 = s2;
                    a2 = 0;
                    jal(ctx, 0x302CE8u, gen::fn_sub_301150_00301150);
                }
                // 0x00302cf0
                charge(ctx, 6);
                v1 = 1;
                v1 = sllv(v1, s3);
                a0 = nor(v1, 0);
                lw(v1, s2, dat_unit::kEffectFlags);
                v1 = v1 & a0;
                sw(v1, s2, dat_unit::kEffectFlags);
            }
            // 0x00302d08
            charge(ctx, 1);
            s1 = addiu(s1, 1);
        }
        // 0x00302d18
        charge(ctx, 1);
        sw(zero, s2, dat_unit::kUnk18);
    }
    // 0x00302d1c: epilogue
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00302D40 sub_302D40 -- 524 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [datCalcTickEffectTurns](unit): for slots 0..16 with a non-zero level, the 4-bit turn counter goes up by
// one while it is below 15.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_302D40(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::i64,
          hg::jal, hg::lbu, hg::ld, hg::lq, hg::lw, hg::sb, hg::sd, hg::sll, hg::sllv, hg::slti, hg::sltiu, hg::sltu,
          hg::sq, hg::sra;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00302d40: prologue
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = 0;
    for (;;) {
        // 0x00302f18
        charge(ctx, 3);
        v1 = sltiu(s3, 17);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00302d70
        charge(ctx, 4);
        s2 = s3 & 0xFF;
        v1 = slti(s2, 21);
        if (v1 == 0) {
            // 0x00302d80
            charge(ctx, 5);
            k_assert(a0, a1, 0x302D8Cu, kDatCalcFile, 1208);
        }
        // 0x00302d94
        charge(ctx, 3);
        at = slti(s2, 17);
        if (at == 0) {
            // 0x00302dbc
            charge(ctx, 7);
            v1 = 1;
            a0 = sllv(v1, s2);
            lw(v1, s4, dat_unit::kEffectFlags);
            v1 = v1 & a0;
            v1 = sltu(0, v1);
            v1 = dsll32(v1, 24);
            v1 = dsra32(v1, 24);
        } else {
            // 0x00302da0
            charge(ctx, 7);
            a1 = s3 & 0xFF;
            a0 = s4;
            jal(ctx, 0x302DA8u, gen::fn_datCalcGetEffectLevel_00300f60);
            v1 = v0;
        }
        // 0x00302dd8
        charge(ctx, 5);
        s5 = dsll32(v1, 24);
        s5 = dsra32(s5, 24);
        v1 = slti(s2, 21);
        if (v1 == 0) {
            // 0x00302dec
            charge(ctx, 5);
            k_assert(a0, a1, 0x302DF8u, kDatCalcFile, 1057);
        }
        // 0x00302e00
        charge(ctx, 6);
        a0 = s3 & 0xFF;
        s1 = sra(a0, 1);
        v1 = s1 & 0xFFFF;
        s0 = a0 & 0x1;
        if (s0 == 0) {
            // 0x00302e38
            charge(ctx, 6);
            v1 = v1 & 0xFFFF;
            v1 = addu(s4, v1);
            lbu(v1, v1, 41);
            v1 = v1 & 0xF;
            v1 = dsll32(v1, 24);
            v1 = dsra32(v1, 24);
        } else {
            // 0x00302e18
            charge(ctx, 8);
            v1 = v1 & 0xFFFF;
            v1 = addu(s4, v1);
            lbu(v1, v1, 41);
            v1 = sra(v1, 4);
            v1 = dsll32(v1, 24);
            v1 = dsra32(v1, 24);
        }
        // 0x00302e50
        charge(ctx, 6);
        a0 = dsll32(v1, 24);
        a0 = dsra32(a0, 24);
        v1 = dsll32(s5, 24);
        v1 = dsra32(v1, 24);
        if (v1 != 0) {
            // 0x00302e68
            charge(ctx, 5);
            s5 = dsll32(a0, 24);
            s5 = dsra32(s5, 24);
            at = slti(s5, 15);
            if (at != 0) {
                // 0x00302e7c
                charge(ctx, 3);
                v1 = slti(s2, 21);
                if (v1 == 0) {
                    // 0x00302e88
                    charge(ctx, 5);
                    k_assert(a0, a1, 0x302E94u, kDatCalcFile, 1109);
                }
                // 0x00302e9c
                charge(ctx, 5);
                v1 = addiu(s5, 1);
                s2 = dsll32(v1, 24);
                s2 = dsra32(s2, 24);
                if (i64(s2) < 0) {
                    // 0x00302eb0
                    charge(ctx, 5);
                    k_assert(a0, a1, 0x302EBCu, kDatCalcFile, 1110);
                }
                // 0x00302ec4
                charge(ctx, 3);
                v1 = s1 & 0xFFFF;
                if (s0 == 0) {
                    // 0x00302ef8
                    charge(ctx, 7);
                    v1 = v1 & 0xFFFF;
                    a1 = addu(s4, v1);
                    lbu(v1, a1, 41);
                    a0 = v1 & 0xF0;
                    v1 = s2 & 0xF;
                    v1 = a0 | v1;
                    sb(v1, a1, 41);
                } else {
                    // 0x00302ed0
                    charge(ctx, 10);
                    v1 = v1 & 0xFFFF;
                    a1 = addu(s4, v1);
                    lbu(v1, a1, 41);
                    a0 = v1 & 0xF;
                    v1 = s2 & 0xF;
                    v1 = sll(v1, 4);
                    v1 = a0 | v1;
                    sb(v1, a1, 41);
                }
            }
        }
        // 0x00302f14
        charge(ctx, 1);
        s3 = addiu(s3, 1);
    }
    // 0x00302f24
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

// 0x00302F50 sub_302F50 -- 480 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [datCalcFindExpiredEffect](unit): the first slot 0..16 with a non-zero level whose turn counter reached 3 (1 for
// slots 8 and 9; slot 11 never expires), or -1. The level and the counter are read as datCalcGetEffectState and
// the turn getter would (inlined, with their asserts 1208 / 1057).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void sub_302F50(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::i64,
          hg::jal, hg::lbu, hg::ld, hg::lq, hg::lw, hg::sd, hg::si, hg::sllv, hg::slti, hg::sltiu, hg::sltu, hg::sq,
          hg::sra;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    auto epilogue = [&] {  // 0x00303110
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
    };
    // 0x00302f50: prologue; s3 = unit; for (slot = 0; slot < 17; ++slot) (s2 = slot)
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = 0;
    for (;;) {
        // 0x00303100: loop test
        charge(ctx, 3);
        v0 = sltiu(s2, 17);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00302f78: s1 = (u8)slot; K_Assert(slot < 21)
        charge(ctx, 4);
        s1 = s2 & 0xFF;
        v0 = slti(s1, btl::kEffectSlots);
        if (v0 == 0) {
            // 0x00302f88
            charge(ctx, 5);
            k_assert(a0, a1, 0x302F94u, kDatCalcFile, 1208);
        }
        // 0x00302f9c: v0 = the slot's level
        charge(ctx, 3);
        at = slti(s1, 17);
        if (at == 0) {
            // 0x00302fc0: (flags only above 16)
            charge(ctx, 7);
            v0 = 1;
            v1 = sllv(v0, s1);
            lw(v0, s3, dat_unit::kEffectFlags);
            v0 = v0 & v1;
            v0 = sltu(0, v0);
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
        } else {
            // 0x00302fa8: datCalcGetEffectLevel(unit, slot)
            charge(ctx, 6);
            a1 = s2 & 0xFF;
            a0 = s3;
            jal(ctx, 0x302FB0u, gen::fn_datCalcGetEffectLevel_00300f60);
        }
        // 0x00302fdc: s0 = (s8)level; K_Assert(slot < 21)
        charge(ctx, 5);
        s0 = dsll32(v0, 24);
        s0 = dsra32(s0, 24);
        v0 = slti(s1, btl::kEffectSlots);
        if (v0 == 0) {
            // 0x00302ff0
            charge(ctx, 5);
            k_assert(a0, a1, 0x302FFCu, kDatCalcFile, 1057);
        }
        // 0x00303004: v0 = the turn counter: effect_turns[slot / 2], low nibble for an even slot, high for odd
        charge(ctx, 6);
        a0 = s2 & 0xFF;
        v0 = sra(a0, 1);
        v1 = v0 & 0xFFFF;
        v0 = a0 & 0x1;
        if (v0 == 0) {
            // 0x0030303c
            charge(ctx, 6);
            v0 = v1 & 0xFFFF;
            v0 = addu(s3, v0);
            lbu(v0, v0, dat_unit::kEffectTurns);
            v0 = v0 & 0xF;
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
        } else {
            // 0x0030301c
            charge(ctx, 8);
            v0 = v1 & 0xFFFF;
            v0 = addu(s3, v0);
            lbu(v0, v0, dat_unit::kEffectTurns);
            v0 = sra(v0, 4);
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
        }
        // 0x00303054: v1 = (s8)turns; only a slot with a level can expire
        charge(ctx, 6);
        v1 = dsll32(v0, 24);
        v1 = dsra32(v1, 24);
        v0 = dsll32(s0, 24);
        v0 = dsra32(v0, 24);
        if (v0 != 0) {
            // 0x0030306c: slot 11 never expires
            charge(ctx, 3);
            v0 = 11;
            bool expired = false;
            if (s2 != v0) {
                // 0x00303078
                charge(ctx, 3);
                v0 = 9;
                if (s2 == v0) {
                    // 0x003030b8: slot 9 expires after one turn
                    charge(ctx, 4);
                    v0 = dsll32(v1, 24);
                    v0 = dsra32(v0, 24);
                    expired = i64(v0) > 0;
                } else {
                    // 0x00303084
                    charge(ctx, 3);
                    v0 = 8;
                    if (s2 == v0) {
                        // 0x00303098: slot 8 expires after one turn
                        charge(ctx, 4);
                        v0 = dsll32(v1, 24);
                        v0 = dsra32(v0, 24);
                        expired = i64(v0) > 0;
                    } else {
                        // 0x00303090, 0x003030d8: the others after three
                        charge(ctx, 2);
                        charge(ctx, 5);
                        v0 = dsll32(v1, 24);
                        v0 = dsra32(v0, 24);
                        v0 = slti(v0, 3);
                        expired = v0 == 0;
                    }
                }
            }
            if (expired) {
                // 0x003030a8 / 0x003030c8 / 0x003030ec: return (s8)slot
                charge(ctx, 4);
                v0 = dsll32(s2, 24);
                v0 = dsra32(v0, 24);
                epilogue();
                return;
            }
        }
        // 0x003030fc: ++slot
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x0030310c: none: return -1
    charge(ctx, 1);
    v0 = si(-1);
    epilogue();
}

// ================================================================================================================
// Status ailments
// ================================================================================================================

// 0x00305970 sub_305970 -- 1708 bytes; frame 0xD0: ra sp+0x90, s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [datCalcRollStatus](skill, attacker, target): the status bit (one of SKILL +28's 24 bits; a SKILL +24 == 3
// skill picks one of its bits at random into a 24 x u16 buffer on the guest stack) the skill inflicts, or 0. Only
// status skills (+24 == 1 or 3) roll; +36 == 1 skills hit a target in status 8 at once. The target's affinity for
// the status element (null / repel / absorb / 0x27000000, 503 / 504 on elements 4 / 5) or a downed / flag-0x10
// target blocks; the rate is AICALC formula 16 (datScriptCalc) times the multiplier in $f20: affinity / 100, x2 or
// x2.5 (flag 4889) on a party member in condition 4/5, x1.5 at buff slot 7, x1.25 for the attacker's element boost
// skill (element 8..15 -> 599, 600, 592..597, the jump table 0x7B8F70) and 598; clamped to 0..99 against
// datCalcRand(100), or a sure hit when the skill's +25 rate is 100 or more.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void sub_305970(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::cvt_s_w, hg::cvt_w_s,
          hg::div_s, hg::dsll32, hg::dsra32, hg::dsrl32, hg::enter, hg::i64, hg::jal, hg::lbu, hg::ld, hg::lh,
          hg::lhu, hg::lq, hg::lw, hg::lwc1, hg::mfc1, hg::mtc1, hg::mul_s, hg::sd, hg::sh, hg::sll, hg::sllv,
          hg::slt, hg::slti, hg::sltiu, hg::sltu, hg::sq, hg::srl, hg::swc1, hg::tail;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f20{ctx, 20};
    // 0x00305970: prologue
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(ra, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    v0 = s4 & 0xFFFF;
    v0 = slti(v0, 624);
    if (v0 == 0) {
        // 0x003059b8
        charge(ctx, 5);
        k_assert(a0, a1, 0x3059C4u, kDatCalcFile, 2761);
    }
    // 0x003059cc
    charge(ctx, 18);
    v0 = flt(1.0f);
    mtc1(v0, f20);
    s6 = 0;
    v1 = s4 & 0xFFFF;
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    v0 = addu(v0, v1);
    s5 = sll(v0, 2);  // * 44 (SkillRecord)
    lw(v0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
    v1 = addu(s5, v0);
    lw(v0, v1, 28);
    s0 = dsll32(v0, 8);
    s0 = dsrl32(s0, 8);
    lbu(v1, v1, 24);
    v0 = 3;
    if (v1 == v0) {
        // 0x00305a14
        charge(ctx, 5);
        a1 = 0;
        a2 = 0;
        a0 = 1;
        for (;;) {
            // 0x00305a58
            charge(ctx, 4);
            v1 = a2 & 0xFFFF;
            v0 = slti(v1, 24);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00305a28
            charge(ctx, 4);
            v0 = sllv(a0, v1);
            v0 = s0 & v0;
            if (v0 != 0) {
                // 0x00305a38
                charge(ctx, 6);
                v0 = a1 & 0xFFFF;
                v0 = sll(v0, 1);
                v0 = addu(v0, sp);
                sh(a2, v0, 160);
                v0 = addiu(a1, 1);
                a1 = v0 & 0xFFFF;
            }
            // 0x00305a50
            charge(ctx, 2);
            v0 = addiu(a2, 1);
            a2 = v0 & 0xFFFF;
        }
        // 0x00305a68
        charge(ctx, 8);
        a0 = a1 & 0xFFFF;
        jal(ctx, 0x305A6Cu, gen::fn_datCalcRand_002ffbc0);
        v0 = sll(v0, 1);
        v0 = addu(v0, sp);
        lhu(v1, v0, 160);
        v0 = 1;
        s0 = sllv(v0, v1);
    }
    // 0x00305a88
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x00305a90
        charge(ctx, 7);
        lw(a0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
        v0 = addiu(a0, 24);
        v0 = addu(v0, s5);
        lbu(v1, v0, 0);
        v0 = 1;
        if (v1 != v0) {
            // 0x00305aac
            charge(ctx, 3);
            v0 = 3;
            if (v1 != v0) {
                goto L_00305f20;
            }
            goto L_00305ab8;
        }
    L_00305ab8:
        charge(ctx, 5);
        v0 = addu(s5, a0);
        lbu(v1, v0, 36);
        v0 = 1;
        if (v1 != v0) {
            // 0x00305acc
            charge(ctx, 2);
            goto L_00305af4;
        }
        // 0x00305ad4
        charge(ctx, 5);
        lw(v0, s2, dat_unit::kStatus);
        v0 = v0 & 0x8;
        v0 = sltu(0, v0);
        if (v0 == 0) {
        L_00305af4:
            charge(ctx, 17);
            a0 = dsll32(s4, 16);
            a0 = dsra32(a0, 16);
            a1 = s0;
            jal(ctx, 0x305B00u, gen::fn_datCalcGetElementForStatus_00308120);
            s7 = dsll32(v0, 16);
            s7 = dsra32(s7, 16);
            a0 = s2;
            a1 = s7;
            jal(ctx, 0x305B18u, gen::fn_datCalcGetAffinity_00306e80);
            s1 = v0;
            v1 = dsll32(s7, 16);
            v1 = dsra32(v1, 16);
            v0 = 5;
            if (v1 == v0) {
                // 0x00305b74
                charge(ctx, 6);
                a0 = s2;
                a1 = 504;
                jal(ctx, 0x305B7Cu, gen::fn_datCalcHasSkill_003005e0);
                if (v0 != 0) {
                    // 0x00305b8c
                    charge(ctx, 2);
                    v0 = 0x1000000;
                    s1 = s1 | v0;
                }
            } else {
                // 0x00305b38
                charge(ctx, 3);
                v0 = 4;
                if (v1 == v0) {
                    // 0x00305b4c
                    charge(ctx, 6);
                    a0 = s2;
                    a1 = 503;
                    jal(ctx, 0x305B54u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00305b64
                        charge(ctx, 4);
                        v0 = 0x1000000;
                        s1 = s1 | v0;
                    }
                } else {
                    // 0x00305b44
                    charge(ctx, 2);
                }
            }
            // 0x00305b94
            charge(ctx, 4);
            v0 = 0x27000000;
            v0 = s1 & v0;
            if (v0 == 0) {
                // 0x00305bb0
                charge(ctx, 4);
                v1 = 0x100000;
                v0 = s0 & v1;
                if (v0 != 0) {
                    // 0x00305bc0
                    charge(ctx, 5);
                    lw(v0, s2, dat_unit::kStatus);
                    v0 = v0 & v1;
                    v0 = sltu(0, v0);
                    if (v0 == 0) {
                        // 0x00305be0
                        charge(ctx, 4);
                        lhu(v0, s2, dat_unit::kFlags);
                        v0 = v0 & 0x10;
                        if (v0 == 0) {
                            goto L_00305bfc;
                        }
                        // 0x00305bf0
                        charge(ctx, 3);
                        v0 = 0;
                    } else {
                        // 0x00305bd4
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x00305fe8: epilogue
                    charge(ctx, 13);
                    ld(ra, sp, 0x90);
                    lq(s7, sp, 0x80);
                    lq(s6, sp, 0x70);
                    lq(s5, sp, 0x60);
                    lq(s4, sp, 0x50);
                    lq(s3, sp, 0x40);
                    lq(s2, sp, 0x30);
                    lq(s1, sp, 0x20);
                    lq(s0, sp, 0x10);
                    lwc1(f20, sp, 0x0);
                    sp = addiu(sp, 0xD0);
                    return;
                }
            L_00305bfc:
                charge(ctx, 3);
                v0 = s1 & 0xFFFF;
                u32_to_float(v0, v1, f0, f1);  // 0x00305c1c / 0x00305c08
                // 0x00305c38
                charge(ctx, 9);
                v0 = flt(100.0f);
                mtc1(v0, f0);
                div_s(f0, f1, f0);
                mul_s(f20, f20, f0);
                v0 = 0x80000;
                s1 = s0 & v0;
                if (s1 == 0) {
                    // 0x00305c5c
                    charge(ctx, 4);
                    lhu(v0, s2, dat_unit::kFlags);
                    v0 = v0 & dat_unit::kFlagEnemy;
                    if (v0 == 0) {
                        // 0x00305c78
                        charge(ctx, 3);
                        lh(a0, s2, dat_unit::kId);
                        jal(ctx, 0x305C7Cu, gen::fn_sub_16C920_0016c920);
                    } else {
                        // 0x00305c6c
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x00305c84
                    charge(ctx, 4);
                    v1 = v0 & 0xFFFF;
                    v0 = 5;
                    if (v1 != v0) {
                        // 0x00305c94
                        charge(ctx, 4);
                        lhu(v0, s2, dat_unit::kFlags);
                        v0 = v0 & dat_unit::kFlagEnemy;
                        if (v0 == 0) {
                            // 0x00305cb0
                            charge(ctx, 3);
                            lh(a0, s2, dat_unit::kId);
                            jal(ctx, 0x305CB4u, gen::fn_sub_16C920_0016c920);
                        } else {
                            // 0x00305ca4
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x00305cbc
                        charge(ctx, 4);
                        v1 = v0 & 0xFFFF;
                        v0 = 4;
                        if (v1 == v0) {
                            goto L_00305ccc;
                        }
                        goto L_00305d04;
                    }
                L_00305ccc:
                    charge(ctx, 7);
                    a0 = 4889;
                    jal(ctx, 0x305CD0u, gen::fn_datGetFlag_0016f190);
                    v0 = sltu(0, v0);
                    v0 = v0 ^ 0x1;
                    if (v0 == 0) {
                        // 0x00305cf8
                        charge(ctx, 2);
                        v0 = flt(2.5f);
                        mtc1(v0, f0);
                    } else {
                        // 0x00305ce8
                        charge(ctx, 4);
                        v0 = flt(2.0f);
                        mtc1(v0, f0);
                    }
                    // 0x00305d00
                    charge(ctx, 1);
                    mul_s(f20, f20, f0);
                L_00305d04:
                    charge(ctx, 8);
                    a0 = s2;
                    a1 = 7;
                    jal(ctx, 0x305D0Cu, gen::fn_datCalcGetEffectLevel_00300f60);
                    v0 = dsll32(v0, 24);
                    v0 = dsra32(v0, 24);
                    if (i64(v0) > 0) {
                        // 0x00305d24
                        charge(ctx, 4);
                        v0 = flt(1.5f);
                        mtc1(v0, f0);
                        mul_s(f20, f20, f0);
                    }
                }
                // 0x00305d34
                charge(ctx, 10);
                a0 = s3;
                a1 = s4;
                jal(ctx, 0x305D3Cu, gen::fn_datCalcGetSkillElement_003082f0);
                v0 = dsll32(v0, 16);
                v0 = dsra32(v0, 16);
                v0 = addiu(v0, -8);
                at = sltiu(v0, 8);
                if (at != 0) {
                    // 0x00305d5c
                    charge(ctx, 7);
                    v1 = hi(0x7B8F70u);
                    v1 = addiu(v1, lo(0x7B8F70u));  // &0x7B8F70
                    v0 = sll(v0, 2);
                    v0 = addu(v0, v1);
                    lw(v0, v0, 0);
                    switch (v0.u()) {
                    case 0x305D78u:  // table[2]
                        // 0x00305d78
                        charge(ctx, 6);
                        a0 = s3;
                        a1 = 592;
                        jal(ctx, 0x305D80u, gen::fn_datCalcHasSkill_003005e0);
                        if (v0 != 0) {
                            // 0x00305d90
                            charge(ctx, 6);
                            v0 = flt(1.25f);
                            mtc1(v0, f0);
                            mul_s(f20, f20, f0);
                        }
                        break;
                    case 0x305DA8u:  // table[3]
                        // 0x00305da8
                        charge(ctx, 6);
                        a0 = s3;
                        a1 = 593;
                        jal(ctx, 0x305DB0u, gen::fn_datCalcHasSkill_003005e0);
                        if (v0 != 0) {
                            // 0x00305dc0
                            charge(ctx, 6);
                            v0 = flt(1.25f);
                            mtc1(v0, f0);
                            mul_s(f20, f20, f0);
                        }
                        break;
                    case 0x305DD8u:  // table[4]
                        // 0x00305dd8
                        charge(ctx, 6);
                        a0 = s3;
                        a1 = 594;
                        jal(ctx, 0x305DE0u, gen::fn_datCalcHasSkill_003005e0);
                        if (v0 != 0) {
                            // 0x00305df0
                            charge(ctx, 6);
                            v0 = flt(1.25f);
                            mtc1(v0, f0);
                            mul_s(f20, f20, f0);
                        }
                        break;
                    case 0x305E08u:  // table[5]
                        // 0x00305e08
                        charge(ctx, 6);
                        a0 = s3;
                        a1 = 595;
                        jal(ctx, 0x305E10u, gen::fn_datCalcHasSkill_003005e0);
                        if (v0 != 0) {
                            // 0x00305e20
                            charge(ctx, 6);
                            v0 = flt(1.25f);
                            mtc1(v0, f0);
                            mul_s(f20, f20, f0);
                        }
                        break;
                    case 0x305E38u:  // table[6]
                        // 0x00305e38
                        charge(ctx, 6);
                        a0 = s3;
                        a1 = 596;
                        jal(ctx, 0x305E40u, gen::fn_datCalcHasSkill_003005e0);
                        if (v0 != 0) {
                            // 0x00305e50
                            charge(ctx, 6);
                            v0 = flt(1.25f);
                            mtc1(v0, f0);
                            mul_s(f20, f20, f0);
                        }
                        break;
                    case 0x305E68u:  // table[7]
                        // 0x00305e68
                        charge(ctx, 6);
                        a0 = s3;
                        a1 = 597;
                        jal(ctx, 0x305E70u, gen::fn_datCalcHasSkill_003005e0);
                        if (v0 != 0) {
                            // 0x00305e80
                            charge(ctx, 6);
                            v0 = flt(1.25f);
                            mtc1(v0, f0);
                            mul_s(f20, f20, f0);
                        }
                        break;
                    case 0x305E98u:  // table[0]
                        // 0x00305e98
                        charge(ctx, 6);
                        a0 = s3;
                        a1 = 599;
                        jal(ctx, 0x305EA0u, gen::fn_datCalcHasSkill_003005e0);
                        if (v0 != 0) {
                            // 0x00305eb0
                            charge(ctx, 6);
                            v0 = flt(1.25f);
                            mtc1(v0, f0);
                            mul_s(f20, f20, f0);
                        }
                        break;
                    case 0x305EC8u:  // table[1]
                        // 0x00305ec8
                        charge(ctx, 6);
                        a0 = s3;
                        a1 = 600;
                        jal(ctx, 0x305ED0u, gen::fn_datCalcHasSkill_003005e0);
                        if (v0 != 0) {
                            // 0x00305ee0
                            charge(ctx, 4);
                            v0 = flt(1.25f);
                            mtc1(v0, f0);
                            mul_s(f20, f20, f0);
                        }
                        break;
                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                        tail(ctx, v0.u());
                        return;
                    }
                }
                // 0x00305ef0
                charge(ctx, 2);
                if (s1 == 0) {
                    // 0x00305ef8
                    charge(ctx, 6);
                    a0 = s3;
                    a1 = 598;
                    jal(ctx, 0x305F00u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00305f10
                        charge(ctx, 4);
                        v0 = flt(1.25f);
                        mtc1(v0, f0);
                        mul_s(f20, f20, f0);
                    }
                }
                goto L_00305f20;
            }
            // 0x00305ba4
            charge(ctx, 3);
            v0 = 0;
        } else {
            // 0x00305ae8
            charge(ctx, 3);
            v0 = s0;
        }
        // 0x00305fe8: epilogue
        charge(ctx, 13);
        ld(ra, sp, 0x90);
        lq(s7, sp, 0x80);
        lq(s6, sp, 0x70);
        lq(s5, sp, 0x60);
        lq(s4, sp, 0x50);
        lq(s3, sp, 0x40);
        lq(s2, sp, 0x30);
        lq(s1, sp, 0x20);
        lq(s0, sp, 0x10);
        lwc1(f20, sp, 0x0);
        sp = addiu(sp, 0xD0);
        return;
    }
L_00305f20:
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x00305f34
        charge(ctx, 6);
        lw(v0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
        v0 = addu(s5, v0);
        lbu(v0, v0, 25);
        v0 = slti(v0, 100);
        if (v0 != 0) {
            // 0x00305f58
            charge(ctx, 17);
            a0 = 16;
            a1 = s3;
            a2 = s2;
            a3 = s4;
            t0 = s0;
            jal(ctx, 0x305F6Cu, gen::fn_datScriptCalc_0030fc40);
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            mul_s(f0, f0, f20);
            cvt_w_s(f0, f0);
            mfc1(s1, f0);
            at = slti(s1, 100);
            if (at != 0) {
                // 0x00305fa8
                charge(ctx, 2);
                if (i64(s1) < 0) {
                    // 0x00305fb0
                    charge(ctx, 1);
                    s1 = 0;
                }
            } else {
                // 0x00305f9c
                charge(ctx, 3);
                s1 = 99;
            }
            // 0x00305fb4
            charge(ctx, 6);
            a0 = 100;
            jal(ctx, 0x305FB8u, gen::fn_datCalcRand_002ffbc0);
            at = slt(v0, s1);
            if (at != 0) {
                // 0x00305fcc
                charge(ctx, 1);
                s6 = 1;
            }
        } else {
            // 0x00305f4c
            charge(ctx, 3);
            s6 = 1;
        }
        // 0x00305fd0
        charge(ctx, 2);
        if (s6 == 0) {
            // 0x00305fe0
            charge(ctx, 1);
            s0 = 0;
        } else {
            // 0x00305fd8
            charge(ctx, 2);
        }
        // 0x00305fe4
        charge(ctx, 1);
        v0 = s0;
    } else {
        // 0x00305f28
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00305fe8: epilogue
    charge(ctx, 13);
    ld(ra, sp, 0x90);
    lq(s7, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xD0);
}

// 0x00306020 sub_306020 -- 1256 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [datCalcRollWeaponStatus](skill, attacker, target, hit): only for hit == 1. A status skill (SKILL +24 1 or 3) rolls
// sub_305970 itself (an already ailing target keeps only the 0x180000 bits); a physical skill of a party member
// against a healthy target rolls the status of its weapon's effect: effects 49..66 -> skills 160..177, 170..172 ->
// 178..180 (the compiler's compare chain, a table walk below; 59, 60, 61 take the skill from the registers that
// hold 170, 171, 172). Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void sub_306020(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::dsrl32, hg::enter, hg::jal, hg::lbu,
          hg::ld, hg::lh, hg::lhu, hg::lq, hg::lw, hg::sd, hg::sll, hg::slti, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // The effect -> status-skill compare chain, rung by rung as compiled: `reg = effect; beq v0, reg` in a 3-cycle
    // block (the first rung's block also masks v0 and costs 4), and on a match `a0 = skill` (or a0 from the register
    // holding 172 / 171, or a0 still 170), `a1 = attacker; a2 = target; jal sub_305970`.
    enum SkillFrom : u8 { kImm, kFromA2, kFromA1, kKeepA0 };
    struct Rung {
        u8 reg;          // the compare register (GPR number)
        u32 effect;      // the weapon effect
        SkillFrom from;  // how a0 gets the status skill
        u32 skill;       // for kImm
        u32 pc;          // the jal sub_305970 of the match block
        u64 cost;        // the match block's cycles
    };
    static constexpr Rung kRungs[] = {
        {6, 172, kImm, 180, 0x306490u, 7}, {5, 171, kImm, 179, 0x306474u, 7}, {4, 170, kImm, 178, 0x306458u, 7},
        {3, 66, kImm, 177, 0x30643Cu, 7},  {3, 65, kImm, 176, 0x306420u, 7},  {3, 64, kImm, 175, 0x306404u, 7},
        {3, 63, kImm, 174, 0x3063E8u, 7},  {3, 62, kImm, 173, 0x3063CCu, 7},  {3, 61, kFromA2, 0, 0x3063B0u, 7},
        {3, 60, kFromA1, 0, 0x306394u, 7}, {3, 59, kKeepA0, 0, 0x306378u, 6}, {3, 58, kImm, 169, 0x306360u, 7},
        {3, 57, kImm, 168, 0x306344u, 7},  {3, 56, kImm, 167, 0x306328u, 7},  {3, 55, kImm, 166, 0x30630Cu, 7},
        {3, 54, kImm, 165, 0x3062F0u, 7},  {3, 53, kImm, 164, 0x3062D4u, 7},  {3, 52, kImm, 163, 0x3062B8u, 7},
        {3, 51, kImm, 162, 0x30629Cu, 7},  {3, 50, kImm, 161, 0x306280u, 7},  {3, 49, kImm, 160, 0x306264u, 7},
    };
    // 0x00306020: prologue; s3 = skill, s2 = attacker, s1 = target, s0 = hit; K_Assert(skill < 464)
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    s0 = a3;
    v0 = s3 & 0xFFFF;
    v0 = slti(v0, btl::kSkillCount);
    if (v0 == 0) {
        // 0x00306058
        charge(ctx, 5);
        k_assert(a0, a1, 0x306064u, kDatCalcFile, 2965);
    }
    // 0x0030606c: only for hit == 1
    charge(ctx, 4);
    v0 = s0 & 0xFFFF;
    a1 = 1;
    if (v0 == a1) {
        // 0x00306088: v1 = SKILL +24 (the status kind)
        charge(ctx, 11);
        lw(a0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
        v1 = s3 & 0xFFFF;
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);  // * 44 (SkillRecord)
        v0 = addu(v0, a0);
        lbu(v1, v0, 24);
        bool status_skill = v1 == a1;
        if (!status_skill) {
            // 0x003060b4: kind 3 is a status skill too
            charge(ctx, 3);
            v0 = 3;
            status_skill = v1 == v0;
            if (!status_skill) {
                // 0x003060c0: a physical skill?
                charge(ctx, 5);
                a0 = s3;
                jal(ctx, 0x3060C4u, gen::fn_datCalcIsPhysicalSkill_003088b0);
                bool none = true;  // -> 0x003064a0, return 0
                if (v0 != 0) {
                    // 0x003060d4: a healthy target (no low status bits)?
                    charge(ctx, 5);
                    lw(v0, s1, dat_unit::kStatus);
                    v0 = dsll32(v0, 12);
                    v0 = dsrl32(v0, 12);
                    if (v0 == 0) {
                        // 0x003060e8: v0 = the attacker's weapon effect (0 for an enemy)
                        charge(ctx, 4);
                        lhu(v0, s2, dat_unit::kFlags);
                        v0 = v0 & dat_unit::kFlagEnemy;
                        if (v0 == 0) {
                            // 0x00306104: K_Assert(pc < 11); sub_16F900(pc, datGetEquipmentIdx(pc, 0))
                            charge(ctx, 4);
                            lh(s0, s2, dat_unit::kId);
                            v0 = slti(s0, dat_unit::kPartyIds);
                            if (v0 == 0) {
                                // 0x00306114
                                charge(ctx, 5);
                                k_assert(a0, a1, 0x306120u, kDatCalcFile, 697);
                            }
                            // 0x00306128
                            charge(ctx, 10);
                            a0 = s0;
                            a1 = 0;
                            jal(ctx, 0x306130u, gen::fn_datGetEquipmentIdx_0016cb80);
                            a1 = dsll32(v0, 16);
                            a1 = dsra32(a1, 16);
                            a0 = s0;
                            jal(ctx, 0x306144u, gen::fn_sub_16F900_0016f900);
                            v0 = v0 & 0xFF;
                        } else {
                            // 0x003060f8
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x00306150 .. 0x00306244: the compare chain
                        for (std::size_t i = 0; i < std::size(kRungs); ++i) {
                            const Rung& r = kRungs[i];
                            if (i == 0) {
                                charge(ctx, 4);
                                v0 = v0 & 0xFFFF;
                            } else {
                                charge(ctx, 3);
                            }
                            Gpr reg{ctx, r.reg};
                            reg = r.effect;
                            if (v0 == reg) {
                                // the match block: return sub_305970(skill, attacker, target)
                                charge(ctx, r.cost);
                                if (r.from == kImm) {
                                    a0 = r.skill;
                                } else if (r.from == kFromA2) {
                                    a0 = a2;
                                } else if (r.from == kFromA1) {
                                    a0 = a1;
                                }
                                a1 = s2;
                                a2 = s1;
                                jal(ctx, r.pc, gen::fn_sub_305970_00305970);
                                none = false;
                                break;
                            }
                        }
                        if (none) {
                            // 0x00306250: no rung matched
                            charge(ctx, 2);
                        }
                    }
                }
                if (none) {
                    // 0x003064a0: return 0
                    charge(ctx, 3);
                    v0 = 0;
                }
                // 0x003064e8: epilogue
                charge(ctx, 8);
                ld(ra, sp, 0x40);
                lq(s3, sp, 0x30);
                lq(s2, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x50);
                return;
            }
        }
        // 0x003064ac: a status skill: v0 = sub_305970(skill, attacker, target); an ailing target keeps only 0x180000
        charge(ctx, 10);
        a0 = s3;
        a1 = s2;
        a2 = s1;
        jal(ctx, 0x3064B8u, gen::fn_sub_305970_00305970);
        lw(v1, s1, dat_unit::kStatus);
        v1 = dsll32(v1, 12);
        v1 = dsrl32(v1, 12);
        if (v1 != 0) {
            // 0x003064d4
            charge(ctx, 4);
            v1 = 0x180000;
            v1 = v0 & v1;
            if (v1 == 0) {
                // 0x003064e4
                charge(ctx, 1);
                v0 = 0;
            }
        }
    } else {
        // 0x0030607c: not a hit: return 0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003064e8: epilogue
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00306510 sub_306510 -- 252 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [datCalcRollSkillStatus](skill, attacker, target, hit): hit == 1 and a SKILL +24 == 2 skill: sub_305970.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void sub_306510(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lq, hg::lw, hg::sd,
          hg::sll, hg::slti, hg::sq;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00306510: prologue
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    s0 = a3;
    v0 = s3 & 0xFFFF;
    v0 = slti(v0, btl::kSkillCount);
    if (v0 == 0) {
        // 0x00306548
        charge(ctx, 5);
        k_assert(a0, a1, 0x306554u, kDatCalcFile, 3066);
    }
    // 0x0030655c
    charge(ctx, 4);
    v1 = s0 & 0xFFFF;
    v0 = 1;
    if (v1 == v0) {
        // 0x00306578
        charge(ctx, 12);
        v1 = s3 & 0xFFFF;
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 1);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);  // * 44 (SkillRecord)
        lw(v0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
        a0 = addu(v1, v0);
        lbu(v1, a0, 24);
        v0 = 2;
        if (v1 == v0) {
            // 0x003065b4
            charge(ctx, 4);
            lbu(v0, a0, 25);
            at = slti(v0, 100);
            if (at != 0) {
                // 0x003065c4
                charge(ctx, 5);
                k_assert(a0, a1, 0x3065D0u, kDatCalcFile, 3077);
            }
            // 0x003065d8
            charge(ctx, 5);
            a0 = s3;
            a1 = s2;
            a2 = s1;
            jal(ctx, 0x3065E4u, gen::fn_sub_305970_00305970);
        } else {
            // 0x003065a8
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0030656c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003065ec: epilogue
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// ================================================================================================================
// Skill application
// ================================================================================================================

// 0x00306610 sub_306610 -- 700 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [datCalcApplySkill](skill, attacker, target, flags): datCalcDamage for HP and SP, sub_306020 and the status-skill
// roll; the new statuses replace the low 20 bits of the target's word (the high 12 are or'ed, the rolled status
// cleared), SP and HP are added and clamped to 0..max, HP 0 sets the dead bit. Returns 0 only when nothing changed
// (1 also for a missing attacker or target).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void sub_306610(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsrl32, hg::enter, hg::i64, hg::jal, hg::lbu,
          hg::ld, hg::lhu, hg::lq, hg::lui, hg::lw, hg::nor, hg::sd, hg::sh, hg::sll, hg::slt, hg::slti, hg::sq,
          hg::sw;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    auto epilogue = [&] {  // 0x003068a0
        charge(ctx, 11);
        ld(ra, sp, 0x70);
        lq(s6, sp, 0x60);
        lq(s5, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x80);
    };
    // 0x00306610: prologue; s4 = skill, s3 = attacker, s2 = target, s0 = flags, s6 = (u16)skill; K_Assert(skill < 464)
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    s0 = a3;
    s6 = s4 & 0xFFFF;
    v0 = slti(s6, btl::kSkillCount);
    if (v0 == 0) {
        // 0x00306654
        charge(ctx, 5);
        k_assert(a0, a1, 0x306660u, kDatCalcFile, 3106);
    }
    // 0x00306668: an attacker and a target?
    charge(ctx, 2);
    bool both = false;
    if (s3 != 0) {
        // 0x00306670
        charge(ctx, 2);
        both = s2 != 0;
    }
    if (both) {
        // 0x00306678: s1 = the HP change, s0 = the SP change (datCalcDamage), s5 = sub_306020's statuses
        charge(ctx, 34);
        a0 = s4;
        a1 = s3;
        a2 = s2;
        a3 = 1;
        t0 = a3;
        t1 = a3;
        t2 = s0;
        t3 = a3;
        jal(ctx, 0x306698u, gen::fn_datCalcDamage_00303130);
        s1 = v0;
        a0 = s4;
        a1 = s3;
        a2 = s2;
        a3 = 1;
        t0 = a3;
        t1 = a3;
        t2 = s0;
        t3 = 2;
        jal(ctx, 0x3066C4u, gen::fn_datCalcDamage_00303130);
        s0 = v0;
        a0 = s4;
        a1 = s3;
        a2 = s2;
        a3 = 1;
        t0 = a3;
        t1 = 0;
        jal(ctx, 0x3066E8u, gen::fn_sub_306020_00306020);
        s5 = v0;
        v0 = slti(s6, btl::kSkillCount);
        if (v0 == 0) {
            // 0x00306700: the status-skill roll (sub_306510 inlined): K_Assert(skill < 464)
            charge(ctx, 5);
            k_assert(a0, a1, 0x30670Cu, kDatCalcFile, 3066);
        }
        // 0x00306714: a status skill (SKILL +24 == 2)?
        charge(ctx, 12);
        v1 = s4 & 0xFFFF;
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 1);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);  // * 44 (SkillRecord)
        lw(v0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
        a0 = addu(v1, v0);
        lbu(v1, a0, 24);
        v0 = 2;
        if (v1 == v0) {
            // 0x00306750: K_Assert(status rate >= 100), then v0 = sub_305970(skill, attacker, target)
            charge(ctx, 4);
            lbu(v0, a0, skill_rec::kStatusRate);
            at = slti(v0, 100);
            if (at != 0) {
                // 0x00306760
                charge(ctx, 5);
                k_assert(a0, a1, 0x30676Cu, kDatCalcFile, 3077);
            }
            // 0x00306774
            charge(ctx, 5);
            a0 = s4;
            a1 = s3;
            a2 = s2;
            jal(ctx, 0x306780u, gen::fn_sub_305970_00305970);
        } else {
            // 0x00306744
            charge(ctx, 3);
            v0 = 0;
        }
        // 0x00306788: anything to change (HP, SP, statuses, the rolled status)?
        charge(ctx, 2);
        bool changed = s1 != 0;
        if (!changed) {
            // 0x00306790
            charge(ctx, 2);
            changed = s0 != 0;
            if (!changed) {
                // 0x00306798
                charge(ctx, 2);
                changed = s5 != 0;
                if (!changed) {
                    // 0x003067a0
                    charge(ctx, 2);
                    changed = v0 != 0;
                }
            }
        }
        if (!changed) {
            // 0x003067a8: return 0
            charge(ctx, 3);
            v0 = 0;
            epilogue();
            return;
        }
        // 0x003067b4: the low 20 status bits of s5 replace the target's
        charge(ctx, 4);
        a1 = dsll32(s5, 12);
        a1 = dsrl32(a1, 12);
        if (a1 != 0) {
            // 0x003067c4
            charge(ctx, 5);
            lw(a0, s2, dat_unit::kStatus);
            v1 = lui(0xFFF0);
            v1 = a0 & v1;
            v1 = v1 | a1;
            sw(v1, s2, dat_unit::kStatus);
        }
        // 0x003067d8: status |= the high 12 bits of s5, then &= ~the rolled status
        charge(ctx, 10);
        v1 = lui(0xFFF0);
        a0 = s5 & v1;
        lw(v1, s2, dat_unit::kStatus);
        v1 = v1 | a0;
        sw(v1, s2, dat_unit::kStatus);
        v0 = nor(v0, 0);
        v0 = v1 & v0;
        sw(v0, s2, dat_unit::kStatus);
        if (s0 != 0) {
            // 0x00306800: sp = clamp(sp + change, 0, datCalcGetMaxSp(target))
            charge(ctx, 4);
            lhu(v0, s2, dat_unit::kSp);
            s0 = addu(v0, s0);
            if (i64(s0) < 0) {
                // 0x00306810
                charge(ctx, 1);
                s0 = 0;
            }
            // 0x00306814
            charge(ctx, 7);
            a0 = s2;
            jal(ctx, 0x306818u, gen::fn_datCalcGetMaxSp_00300100);
            v0 = v0 & 0xFFFF;
            at = slt(v0, s0);
            if (at != 0) {
                // 0x00306830
                charge(ctx, 1);
                s0 = v0;
            }
            // 0x00306834
            charge(ctx, 1);
            sh(s0, s2, dat_unit::kSp);
        }
        // 0x00306838
        charge(ctx, 2);
        if (s1 != 0) {
            // 0x00306840: hp = clamp(hp + change, 0, datCalcGetMaxHp(target))
            charge(ctx, 4);
            lhu(v0, s2, dat_unit::kHp);
            s0 = addu(v0, s1);
            if (i64(s0) < 0) {
                // 0x00306850
                charge(ctx, 1);
                s0 = 0;
            }
            // 0x00306854
            charge(ctx, 7);
            a0 = s2;
            jal(ctx, 0x306858u, gen::fn_datCalcGetMaxHp_002ffdf0);
            v0 = v0 & 0xFFFF;
            at = slt(v0, s0);
            if (at != 0) {
                // 0x00306870
                charge(ctx, 1);
                s0 = v0;
            }
            // 0x00306874: HP 0: status = (status & 0xFFF00000) | dead
            charge(ctx, 4);
            sh(s0, s2, dat_unit::kHp);
            lhu(v0, s2, dat_unit::kHp);
            if (v0 == 0) {
                // 0x00306884
                charge(ctx, 6);
                lw(v1, s2, dat_unit::kStatus);
                v0 = lui(0xFFF0);
                v1 = v1 & v0;
                v0 = btl::kStatusDead;
                v0 = v1 | v0;
                sw(v0, s2, dat_unit::kStatus);
            }
        }
    }
    // 0x0030689c: return 1
    charge(ctx, 1);
    v0 = 1;
    epilogue();
}

// 0x003068D0 sub_3068D0 -- 740 bytes; frame 0x90: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [datCalcGetSkillEffectMask](skill, attacker, target, flags): what the skill would do, for the AI and the menus: 0
// when it would change something, else bits 1 (HP already full), 2 (SP full), 4 (status already set), 0xFFFF (no
// effect at all, or the target is dead). The units' +0x18 words are cleared.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void sub_3068D0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::i64, hg::jal, hg::lbu, hg::ld, hg::lhu, hg::lq,
          hg::lw, hg::sd, hg::sll, hg::slt, hg::slti, hg::sltu, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    auto epilogue = [&] {  // 0x00306b84
        charge(ctx, 12);
        ld(ra, sp, 0x80);
        lq(s7, sp, 0x70);
        lq(s6, sp, 0x60);
        lq(s5, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x90);
    };
    // 0x003068d0: prologue; s2 = skill, s1 = attacker, s0 = target, s3 = flags, s5 = (u16)skill; K_Assert(skill < 464)
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    s3 = a3;
    s5 = s2 & 0xFFFF;
    v0 = slti(s5, btl::kSkillCount);
    if (v0 == 0) {
        // 0x00306918
        charge(ctx, 5);
        k_assert(a0, a1, 0x306924u, kDatCalcFile, 3175);
    }
    // 0x0030692c: s4 = mask = 0; an attacker and a target?
    charge(ctx, 3);
    s4 = 0;
    bool both = false;
    if (s1 != 0) {
        // 0x00306938
        charge(ctx, 2);
        both = s0 != 0;
    }
    if (!both) {
        // 0x00306b80: return the mask (0)
        charge(ctx, 1);
        v0 = s4;
        epilogue();
        return;
    }
    // 0x00306940: s6 = the HP change, s3 = the SP change, s7 = sub_306020's statuses
    charge(ctx, 34);
    a0 = s2;
    a1 = s1;
    a2 = s0;
    a3 = 1;
    t0 = a3;
    t1 = a3;
    t2 = s3;
    t3 = a3;
    jal(ctx, 0x306960u, gen::fn_datCalcDamage_00303130);
    s6 = v0;
    a0 = s2;
    a1 = s1;
    a2 = s0;
    a3 = 1;
    t0 = a3;
    t1 = a3;
    t2 = s3;
    t3 = 2;
    jal(ctx, 0x30698Cu, gen::fn_datCalcDamage_00303130);
    s3 = v0;
    a0 = s2;
    a1 = s1;
    a2 = s0;
    a3 = 1;
    t0 = a3;
    t1 = 0;
    jal(ctx, 0x3069B0u, gen::fn_sub_306020_00306020);
    s7 = v0;
    v0 = slti(s5, btl::kSkillCount);
    if (v0 == 0) {
        // 0x003069c8: the status-skill roll (sub_306510 inlined): K_Assert(skill < 464)
        charge(ctx, 5);
        k_assert(a0, a1, 0x3069D4u, kDatCalcFile, 3066);
    }
    // 0x003069dc: a status skill (SKILL +24 == 2)?
    charge(ctx, 12);
    v1 = s2 & 0xFFFF;
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    v0 = addu(v0, v1);
    v1 = sll(v0, 2);  // * 44 (SkillRecord)
    lw(v0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
    a0 = addu(v1, v0);
    lbu(v1, a0, 24);
    v0 = 2;
    if (v1 == v0) {
        // 0x00306a18: K_Assert(status rate >= 100), then v0 = sub_305970(skill, attacker, target)
        charge(ctx, 4);
        lbu(v0, a0, skill_rec::kStatusRate);
        at = slti(v0, 100);
        if (at != 0) {
            // 0x00306a28
            charge(ctx, 5);
            k_assert(a0, a1, 0x306A34u, kDatCalcFile, 3077);
        }
        // 0x00306a3c
        charge(ctx, 5);
        a0 = s2;
        a1 = s1;
        a2 = s0;
        jal(ctx, 0x306A48u, gen::fn_sub_305970_00305970);
    } else {
        // 0x00306a0c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00306a50: both units' +0x18 = 0; a1 = the target's status, a0 = it is dead; nothing at all -> 0xFFFF
    charge(ctx, 8);
    sw(zero, s1, dat_unit::kUnk18);
    sw(zero, s0, dat_unit::kUnk18);
    lw(a1, s0, dat_unit::kStatus);
    v1 = btl::kStatusDead;
    v1 = a1 & v1;
    a0 = sltu(0, v1);
    if (s6 == 0) {
        // 0x00306a70
        charge(ctx, 2);
        if (s3 == 0) {
            // 0x00306a78
            charge(ctx, 2);
            if (s7 == 0) {
                // 0x00306a80
                charge(ctx, 2);
                if (v0 == 0) {
                    // 0x00306a88
                    charge(ctx, 1);
                    s4 = s4 | 0xFFFF;
                }
            }
        }
    }
    // 0x00306a8c: a rolled status
    charge(ctx, 2);
    if (v0 != 0) {
        // 0x00306a94: the target's status word has the rolled bit: return 0
        charge(ctx, 4);
        v1 = a1 & v0;
        v1 = sltu(0, v1);
        if (v1 != 0) {
            // 0x00306ab0
            charge(ctx, 3);
            v0 = 0;
            epilogue();
            return;
        }
        // 0x00306aa4: it does not: mask |= 4
        charge(ctx, 3);
        s4 = s4 | 0x4;
        // 0x00306abc: the dead status with bit 4 set: return the mask
        charge(ctx, 4);
        v1 = btl::kStatusDead;
        v0 = v0 & v1;
        if (v0 != 0) {
            // 0x00306acc
            charge(ctx, 3);
            v0 = s4 & 0x4;
            if (v0 != 0) {
                // 0x00306ad8
                charge(ctx, 3);
                v0 = s4;
                epilogue();
                return;
            }
        }
    }
    // 0x00306ae4: a dead target: 0xFFFF
    charge(ctx, 2);
    if (a0 != 0) {
        // 0x00306b74
        charge(ctx, 3);
        v0 = 0xFFFF;
        epilogue();
        return;
    }
    // 0x00306aec: an SP gain: SP already full -> mask |= 2, else return 0
    charge(ctx, 2);
    if (i64(s3) > 0) {
        // 0x00306af4
        charge(ctx, 9);
        lhu(s1, s0, dat_unit::kSp);
        a0 = s0;
        jal(ctx, 0x306AFCu, gen::fn_datCalcGetMaxSp_00300100);
        v1 = v0 & 0xFFFF;
        v0 = s1 & 0xFFFF;
        at = slt(v0, v1);
        if (at != 0) {
            // 0x00306b24
            charge(ctx, 3);
            v0 = 0;
            epilogue();
            return;
        }
        // 0x00306b18
        charge(ctx, 3);
        s4 = s4 | 0x2;
    }
    // 0x00306b30: an HP gain: HP already full -> mask |= 1, else return 0
    charge(ctx, 2);
    if (i64(s6) > 0) {
        // 0x00306b38
        charge(ctx, 9);
        lhu(s1, s0, dat_unit::kHp);
        a0 = s0;
        jal(ctx, 0x306B40u, gen::fn_datCalcGetMaxHp_002ffdf0);
        v1 = v0 & 0xFFFF;
        v0 = s1 & 0xFFFF;
        at = slt(v0, v1);
        if (at != 0) {
            // 0x00306b68
            charge(ctx, 3);
            v0 = 0;
            epilogue();
            return;
        }
        // 0x00306b5c
        charge(ctx, 3);
        s4 = s4 | 0x1;
    }
    // 0x00306b80: return the mask
    charge(ctx, 1);
    v0 = s4;
    epilogue();
}

// 0x00306BC0 sub_306BC0 -- 456 bytes; frame 0x90: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [datCalcSkillResults](skill, attacker, target, flags, hp_out, sp_out, status_out): the HP and SP changes of
// datCalcDamage and the status-skill roll stored through the pointers that are not 0; the units' +0x18 words
// cleared. 0 for a missing attacker or target, else 1.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void sub_306BC0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lq, hg::lw, hg::sd,
          hg::sll, hg::slti, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00306bc0: prologue; s4 = skill, s3 = attacker, s2 = target, s1 = flags, s0 / s5 / s6 = hp / sp / status out;
    // s7 = (u16)skill; K_Assert(skill < 464)
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    s1 = a3;
    s0 = t0;
    s5 = t1;
    s6 = t2;
    s7 = s4 & 0xFFFF;
    v0 = slti(s7, btl::kSkillCount);
    if (v0 == 0) {
        // 0x00306c14
        charge(ctx, 5);
        k_assert(a0, a1, 0x306C20u, kDatCalcFile, 3269);
    }
    // 0x00306c28: an attacker and a target?
    charge(ctx, 2);
    bool both = false;
    if (s3 != 0) {
        // 0x00306c30
        charge(ctx, 2);
        both = s2 != 0;
    }
    if (both) {
        // 0x00306c38: *hp_out = datCalcDamage(skill, attacker, target, 1, 1, 1, flags, 1 (HP))
        charge(ctx, 2);
        if (s0 != 0) {
            // 0x00306c40
            charge(ctx, 11);
            a0 = s4;
            a1 = s3;
            a2 = s2;
            a3 = 1;
            t0 = a3;
            t1 = a3;
            t2 = s1;
            t3 = a3;
            jal(ctx, 0x306C60u, gen::fn_datCalcDamage_00303130);
            sw(v0, s0, 0);
        }
        // 0x00306c6c: *sp_out = datCalcDamage(..., 2 (SP))
        charge(ctx, 2);
        if (s5 != 0) {
            // 0x00306c74
            charge(ctx, 11);
            a0 = s4;
            a1 = s3;
            a2 = s2;
            a3 = 1;
            t0 = a3;
            t1 = a3;
            t2 = s1;
            t3 = 2;
            jal(ctx, 0x306C94u, gen::fn_datCalcDamage_00303130);
            sw(v0, s5, 0);
        }
        // 0x00306ca0: *status_out = the status-skill roll (sub_306510 inlined)
        charge(ctx, 2);
        if (s6 != 0) {
            // 0x00306ca8: K_Assert(skill < 464)
            charge(ctx, 3);
            v0 = slti(s7, btl::kSkillCount);
            if (v0 == 0) {
                // 0x00306cb4
                charge(ctx, 5);
                k_assert(a0, a1, 0x306CC0u, kDatCalcFile, 3066);
            }
            // 0x00306cc8: a status skill (SKILL +24 == 2)?
            charge(ctx, 12);
            v1 = s4 & 0xFFFF;
            v0 = sll(v1, 2);
            v0 = addu(v0, v1);
            v0 = sll(v0, 1);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);  // * 44 (SkillRecord)
            lw(v0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
            a0 = addu(v1, v0);
            lbu(v1, a0, 24);
            v0 = 2;
            if (v1 == v0) {
                // 0x00306d04: K_Assert(status rate +25 >= 100), then sub_305970(skill, attacker, target)
                charge(ctx, 4);
                lbu(v0, a0, skill_rec::kStatusRate);
                at = slti(v0, 100);
                if (at != 0) {
                    // 0x00306d14
                    charge(ctx, 5);
                    k_assert(a0, a1, 0x306D20u, kDatCalcFile, 3077);
                }
                // 0x00306d28
                charge(ctx, 5);
                a0 = s4;
                a1 = s3;
                a2 = s2;
                jal(ctx, 0x306D34u, gen::fn_sub_305970_00305970);
            } else {
                // 0x00306cf8
                charge(ctx, 3);
                v0 = 0;
            }
            // 0x00306d3c
            charge(ctx, 1);
            sw(v0, s6, 0);
        }
        // 0x00306d40: both units' +0x18 = 0; return 1
        charge(ctx, 5);
        sw(zero, s3, dat_unit::kUnk18);
        sw(zero, s2, dat_unit::kUnk18);
        v0 = 1;
    } else {
        // 0x00306d54: return 0
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x00306d58: epilogue
    charge(ctx, 12);
    ld(ra, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_306BC0(EEContext& ctx, u64 skill, u64 attacker, u64 target, u64 flags, u64 hp_out, u64 sp_out, u64 status_out) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(skill));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(attacker));
    ee::core::set_gpr64(ctx, GPR_A2, static_cast<u64>(target));
    ee::core::set_gpr64(ctx, GPR_A3, static_cast<u64>(flags));
    ee::core::set_gpr64(ctx, GPR_T0, static_cast<u64>(hp_out));
    ee::core::set_gpr64(ctx, GPR_T1, static_cast<u64>(sp_out));
    ee::core::set_gpr64(ctx, GPR_T2, static_cast<u64>(status_out));
    sub_306BC0(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x00306D90 sub_306D90 -- 232 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [datCalcDecodeAffinity](boost, word): a UNIT.TBL affinity word (low byte = rate / 5, high byte = flags)
// -> the affinity word of datCalcGetAffinity: flags << 16 | 5 * rate. A zero rate gets the flag's default: weak
// 125 (150 with `boost` under flag 4889), null / repel / absorb 100, resist 50. The `sll` by 16 sign-extends.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_306D90(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lui, hg::sd, hg::sll,
          hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00306d90: prologue
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    v1 = a1 & 0xFFFF;
    v0 = v1 & 0xFF00;
    a0 = sll(v0, 16);
    v0 = lui(0xFFFF);
    v0 = v0 | 0xFF;
    v1 = v1 & v0;
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    s0 = a0 | v0;
    v0 = s0 & 0xFFFF;
    if (v0 == 0) {
        // 0x00306dd4
        charge(ctx, 4);
        v0 = 0x8000000;
        v0 = s0 & v0;
        if (v0 == 0) {
            // 0x00306e2c
            charge(ctx, 4);
            v0 = 0x27000000;
            v0 = s0 & v0;
            if (v0 == 0) {
                // 0x00306e48
                charge(ctx, 4);
                v0 = 0x10000000;
                v0 = s0 & v0;
                if (v0 != 0) {
                    // 0x00306e58
                    charge(ctx, 1);
                    s0 = s0 | 0x32;
                }
            } else {
                // 0x00306e3c
                charge(ctx, 3);
                s0 = s0 | 0x64;
            }
        } else {
            // 0x00306de4
            charge(ctx, 5);
            a0 = 4889;
            jal(ctx, 0x306DE8u, gen::fn_datGetFlag_0016f190);
            if (v0 != 0) {
                // 0x00306e04
                charge(ctx, 3);
                v0 = s1 & 0xFFFF;
                if (v0 != 0) {
                    // 0x00306e1c
                    charge(ctx, 1);
                    v0 = 150;
                } else {
                    // 0x00306e10
                    charge(ctx, 3);
                    v0 = 125;
                }
                // 0x00306e20
                charge(ctx, 3);
                s0 = s0 | v0;
            } else {
                // 0x00306df8
                charge(ctx, 3);
                s0 = s0 | 0x7D;
            }
        }
    }
    // 0x00306e5c: epilogue
    charge(ctx, 7);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// ================================================================================================================
// Costs and the action rolls
// ================================================================================================================

// 0x003083F0 sub_3083F0 -- 712 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [datCalcGetSkillCost](unit, skill): SKILL +3 = 1: HP cost, max HP * (+4) % + (+6), halved with skill 566, at least
// 1; 0 for an enemy. +3 = 2: SP cost, (+4) + (+6), or max SP * (+4) % + (+6) when flags0 bit 4 is set, halved with
// 565, at least 1 unless 0; 0 for an enemy whose EnemyRecord +0 has bit 1. 0 in the no-cost mode (sub_17D800) for a
// unit in status 0x100.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void sub_3083F0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::div, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lhu, hg::lq,
          hg::lw, hg::mflo, hg::mult, hg::sd, hg::sll, hg::slti, hg::sltu, hg::sq, hg::srl, hg::subu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003083f0: prologue; s3 = unit, s2 = skill; K_Assert(skill < 464)
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    v0 = s2 & 0xFFFF;
    v0 = slti(v0, btl::kSkillCount);
    if (v0 == 0) {
        // 0x00308420
        charge(ctx, 5);
        k_assert(a0, a1, 0x30842Cu, kDatCalcFile, 3879);
    }
    // 0x00308434: s1 = cost = 0; the no-cost mode (sub_17D800) and status 0x100: free
    charge(ctx, 5);
    s1 = 0;
    jal(ctx, 0x308438u, gen::fn_sub_17D800_0017d800);
    bool free = false;
    if (v0 != 0) {
        // 0x00308448
        charge(ctx, 5);
        lw(v0, s3, dat_unit::kStatus);
        v0 = v0 & 0x100;
        v0 = sltu(0, v0);
        free = v0 != 0;
    }
    if (free) {
        // 0x0030845c: return 0
        charge(ctx, 3);
        v0 = 0;
    } else {
        // 0x00308468: s0 = skill * 44; the cost kind SKILL +3
        charge(ctx, 12);
        v1 = s2 & 0xFFFF;
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 1);
        v0 = addu(v0, v1);
        s0 = sll(v0, 2);  // * 44 (SkillRecord)
        lw(v0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
        v0 = addu(s0, v0);
        lbu(v1, v0, skill_rec::kByte3);
        v0 = 2;
        if (v1 == v0) {
            // 0x00308568: an SP cost; an enemy whose EnemyRecord flag 0x2 is set pays nothing
            charge(ctx, 4);
            lhu(v0, s3, dat_unit::kFlags);
            v0 = v0 & dat_unit::kFlagEnemy;
            bool free_enemy = false;
            if (v0 != 0) {
                // 0x00308578: K_Assert(id < 336)
                charge(ctx, 4);
                lhu(v0, s3, dat_unit::kId);
                v0 = slti(v0, enemy_rec::kCount);
                if (v0 == 0) {
                    // 0x00308588
                    charge(ctx, 5);
                    k_assert(a0, a1, 0x308594u, kDatCalcFile, 3921);
                }
                // 0x0030859c
                charge(ctx, 10);
                lhu(v1, s3, dat_unit::kId);
                v0 = sll(v1, 5);
                v0 = subu(v0, v1);
                v1 = sll(v0, 1);  // * 62 (EnemyRecord)
                lw(v0, gp, gp_off(btl::kUnitTablePtr));  // gBtlEnemyTbl
                v0 = addu(v0, v1);
                lhu(v0, v0, enemy_rec::kFlags);
                v0 = v0 & 0x2;
                free_enemy = v0 != 0;
            }
            if (free_enemy) {
                // 0x003085c4: return 0
                charge(ctx, 3);
                v0 = 0;
            } else {
                // 0x003085d0: flags0 bit 4: a percentage of max SP
                charge(ctx, 6);
                lw(a0, gp, gp_off(btl::kSkillTablePtr));
                v0 = addu(a0, s0);
                lbu(v0, v0, skill_rec::kFlags0);
                v0 = v0 & 0x10;
                if (v0 != 0) {
                    // 0x00308618: cost = datCalcGetMaxSp(unit) * (+4) / 100 + (+6)
                    charge(ctx, 19);
                    a0 = s3;
                    jal(ctx, 0x30861Cu, gen::fn_datCalcGetMaxSp_00300100);
                    a1 = v0 & 0xFFFF;
                    v1 = s2 & 0xFFFF;
                    v0 = sll(v1, 2);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 1);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);  // * 44 (SkillRecord)
                    lw(v0, gp, gp_off(btl::kSkillTablePtr));
                    a0 = addu(v1, v0);
                    lhu(v0, a0, 4);
                    mult(v1, a1, v0);
                    v0 = 100;
                    div(v1, v0);
                    mflo(v1);
                    lhu(v0, a0, 6);
                    s1 = addu(v1, v0);
                } else {
                    // 0x003085e8: cost = (+4) + (+6)
                    charge(ctx, 12);
                    v1 = s2 & 0xFFFF;
                    v0 = sll(v1, 2);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 1);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);  // * 44 (SkillRecord)
                    v0 = addu(v0, a0);
                    lhu(v1, v0, 4);
                    lhu(v0, v0, 6);
                    s1 = addu(v1, v0);
                }
                // 0x00308664: a non-zero cost: halved with skill 565, at least 1
                charge(ctx, 2);
                if (s1 != 0) {
                    // 0x0030866c
                    charge(ctx, 6);
                    a0 = s3;
                    a1 = 565;
                    jal(ctx, 0x308674u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00308684
                        charge(ctx, 1);
                        s1 = srl(s1, 1);
                    }
                    // 0x00308688
                    charge(ctx, 2);
                    if (s1 == 0) {
                        // 0x00308690
                        charge(ctx, 1);
                        s1 = 1;
                    }
                }
                // 0x00308694: return the cost
                charge(ctx, 1);
                v0 = s1;
            }
        } else {
            // 0x00308498: an HP cost?
            charge(ctx, 3);
            v0 = 1;
            if (v1 != v0) {
                // 0x003084a4, 0x00308694: neither: return 0 (s1)
                charge(ctx, 2);
                charge(ctx, 1);
                v0 = s1;
            } else {
                // 0x003084ac: an HP cost; enemies pay nothing
                charge(ctx, 4);
                lhu(v0, s3, dat_unit::kFlags);
                v0 = v0 & dat_unit::kFlagEnemy;
                if (v0 == 0) {
                    // 0x003084ec: cost = datCalcGetMaxHp(unit) * (+4) / 100 + (+6), halved with skill 566, at least 1
                    charge(ctx, 25);
                    a0 = s3;
                    jal(ctx, 0x3084F0u, gen::fn_datCalcGetMaxHp_002ffdf0);
                    a1 = v0 & 0xFFFF;
                    v1 = s2 & 0xFFFF;
                    v0 = sll(v1, 2);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 1);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);  // * 44 (SkillRecord)
                    lw(v0, gp, gp_off(btl::kSkillTablePtr));
                    a0 = addu(v1, v0);
                    lhu(v0, a0, 4);
                    mult(v1, a1, v0);
                    v0 = 100;
                    div(v1, v0);
                    mflo(v1);
                    lhu(v0, a0, 6);
                    s1 = addu(v1, v0);
                    a0 = s3;
                    a1 = 566;
                    jal(ctx, 0x308540u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x00308550
                        charge(ctx, 1);
                        s1 = srl(s1, 1);
                    }
                    // 0x00308554
                    charge(ctx, 2);
                    if (s1 == 0) {
                        // 0x0030855c
                        charge(ctx, 3);
                        s1 = 1;
                    }
                    // 0x00308694: return the cost
                    charge(ctx, 1);
                    v0 = s1;
                } else {
                    // 0x003084bc: an enemy: K_Assert(id < 336); return 0
                    charge(ctx, 4);
                    lhu(v0, s3, dat_unit::kId);
                    v0 = slti(v0, enemy_rec::kCount);
                    if (v0 == 0) {
                        // 0x003084cc
                        charge(ctx, 5);
                        k_assert(a0, a1, 0x3084D8u, kDatCalcFile, 3896);
                    }
                    // 0x003084e0
                    charge(ctx, 3);
                    v0 = 0;
                }
            }
        }
    }
    // 0x00308698: epilogue
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003086F0 sub_3086F0 -- 368 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [datCalcCheckSkillCost](unit, skill): 0 when the unit can pay the cost of sub_3083F0, 1 for too little HP
// (an HP skill with flags0 bit 0 needs HP above the cost, the others HP at least the cost), 2 for too little SP,
// 3 when 578 / 577 make HP / SP skills free.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void sub_3086F0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lhu, hg::lq, hg::lw,
          hg::sd, hg::sll, hg::slti, hg::sltu, hg::sq;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003086f0: prologue
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s0 = a1;
    s2 = 0;
    v0 = s0 & 0xFFFF;
    v0 = slti(v0, 624);
    if (v0 == 0) {
        // 0x00308724
        charge(ctx, 5);
        k_assert(a0, a1, 0x308730u, kDatCalcFile, 3987);
    }
    // 0x00308738
    charge(ctx, 17);
    a0 = s3;
    a1 = s0;
    jal(ctx, 0x308740u, gen::fn_sub_3083F0_003083f0);
    s1 = v0;
    v1 = s0 & 0xFFFF;
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    v0 = addu(v0, v1);
    s0 = sll(v0, 2);  // * 44 (SkillRecord)
    lw(v0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
    v0 = addu(s0, v0);
    lbu(v1, v0, 3);
    v0 = 2;
    if (v1 == v0) {
        // 0x00308804
        charge(ctx, 6);
        a0 = s3;
        a1 = 577;
        jal(ctx, 0x30880Cu, gen::fn_datCalcHasSkill_003005e0);
        if (v0 == 0) {
            // 0x00308828
            charge(ctx, 4);
            lhu(v0, s3, dat_unit::kSp);
            at = sltu(v0, s1);
            if (at != 0) {
                // 0x00308838
                charge(ctx, 1);
                s2 = 2;
            }
        } else {
            // 0x0030881c
            charge(ctx, 3);
            s2 = 3;
        }
    } else {
        // 0x0030877c
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            // 0x00308790
            charge(ctx, 6);
            a0 = s3;
            a1 = 578;
            jal(ctx, 0x308798u, gen::fn_datCalcHasSkill_003005e0);
            if (v0 == 0) {
                // 0x003087b4
                charge(ctx, 6);
                lw(v0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
                v0 = addu(v0, s0);
                lbu(v0, v0, 0);
                v0 = v0 & 0x1;
                if (v0 != 0) {
                    // 0x003087e8
                    charge(ctx, 4);
                    lhu(v0, s3, dat_unit::kHp);
                    at = sltu(v0, s1);
                    if (at != 0) {
                        // 0x003087f8
                        charge(ctx, 3);
                        s2 = 1;
                    }
                } else {
                    // 0x003087cc
                    charge(ctx, 4);
                    lhu(v0, s3, dat_unit::kHp);
                    at = sltu(s1, v0);
                    if (at == 0) {
                        // 0x003087dc
                        charge(ctx, 3);
                        s2 = 1;
                    }
                }
            } else {
                // 0x003087a8
                charge(ctx, 3);
                s2 = 3;
            }
        } else {
            // 0x00308788
            charge(ctx, 2);
        }
    }
    // 0x0030883c: epilogue
    charge(ctx, 9);
    v0 = s2;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00308A80 sub_308A80 -- 284 bytes; frame 0x50: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [datCalcPickMixRaidSkill](unit): the unit's skills 192..197 among its datCalcGetSkillSlotCount entries (at
// most 16 kept in a u16 buffer on the guest stack), one of them at random, or 0.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_308A80(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lq,
          hg::lw, hg::sd, hg::sh, hg::sll, hg::slt, hg::sltiu, hg::sq, hg::tail;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00308a80: prologue
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    jal(ctx, 0x308A94u, gen::fn_datCalcGetSkillSlotCount_00308ba0);
    s0 = v0 & 0xFFFF;
    a0 = s1;
    jal(ctx, 0x308AA4u, gen::fn_datCalcGetSkillList_00308bb0);
    a0 = 0;
    v1 = 0;
    t1 = s0 & 0xFFFF;
    a3 = hi(0x7B9010u);
    a3 = addiu(a3, lo(0x7B9010u));  // &0x7B9010
    a2 = 1;
    for (;;) {
        // 0x00308b38
        charge(ctx, 4);
        a1 = v1 & 0xFFFF;
        at = slt(a1, t1);
        if (at != 0) {
            // 0x00308b48
            charge(ctx, 4);
            a1 = a0 & 0xFFFF;
            a1 = sltiu(a1, 16);
            if (a1 != 0) {
                backedge(ctx);
                // 0x00308acc
                charge(ctx, 8);
                a1 = v1 & 0xFFFF;
                a1 = sll(a1, 1);
                a1 = addu(v0, a1);
                lhu(t0, a1, 0);
                a1 = addiu(t0, -192);
                at = sltiu(a1, 6);
                if (at == 0) {
                    // 0x00308b0c
                    charge(ctx, 1);
                    a1 = 0;
                } else {
                    // 0x00308aec
                    charge(ctx, 5);
                    a1 = sll(a1, 2);
                    a1 = addu(a1, a3);
                    lw(a1, a1, 0);
                    switch (a1.u()) {
                    case 0x308B00u:  // table[0, 1, 2, 3, 4, 5]
                        break;
                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                        tail(ctx, a1.u());
                        return;
                    }
                    // 0x00308b00
                    charge(ctx, 3);
                    a1 = a2;
                }
                // 0x00308b10
                charge(ctx, 2);
                if (a1 != 0) {
                    // 0x00308b18
                    charge(ctx, 6);
                    a1 = a0 & 0xFFFF;
                    a1 = sll(a1, 1);
                    a1 = addu(a1, sp);
                    sh(t0, a1, 48);
                    a0 = addiu(a0, 1);
                    a0 = a0 & 0xFFFF;
                }
                // 0x00308b30
                charge(ctx, 2);
                v1 = addiu(v1, 1);
                v1 = v1 & 0xFFFF;
                continue;
            }
        }
        break;
    }
    // 0x00308b58
    charge(ctx, 3);
    a0 = a0 & 0xFFFF;
    if (a0 != 0) {
        // 0x00308b70
        charge(ctx, 5);
        jal(ctx, 0x308B70u, gen::fn_datCalcRand_002ffbc0);
        v0 = sll(v0, 1);
        v0 = addu(v0, sp);
        lhu(v0, v0, 48);
    } else {
        // 0x00308b64
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00308b84: epilogue
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0030A740 sub_30A740 -- 1984 bytes; frame 0x90: ra sp+0x80, s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [datCalcRollInstantKill](attacker, target, skill, result): the light / dark instant-kill roll after a hit.
// Results that already decided (4 miss, 2, 256, 1024, 512) give 1; elements -1, 16, 17, 18 give 1. Unless the skill
// is a light / dark one (element bits 1..3, or bit 8 with SKILL +2 == 1) the result is 4 on a weak target, else 1.
// A kill rate (+37) of 0 or a target with flag 0x100 or a weak target ends there too. The rate: 100 for +37 == 100,
// else AICALC formula 5, x0.5 with the target's 561, x2 with the attacker's 562, plus status (+100 for 64 / 8, +40
// for 4, +50 for 2), the attacker's condition 2 (+15), its equipment effects 67..69 (+5/+10/+15) and buff slots
// 5 / 6 (+7/+15), clamped to 0..100: three datCalcRand(100) rolls give 2 (killed); otherwise a physical skill of a party member whose weapon
// class is 2+ rolls 2 x rate (at most 50) for 8.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: callee frames).
void sub_30A740(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::cvt_s_w, hg::cvt_w_s, hg::dsll32, hg::dsra32,
          hg::dsrl32, hg::enter, hg::i64, hg::jal, hg::lb, hg::lbu, hg::ld, hg::lh, hg::lhu, hg::lq, hg::lw,
          hg::lwc1, hg::mfc1, hg::mtc1, hg::mul_s, hg::sd, hg::sll, hg::sllv, hg::slt, hg::slti, hg::sltu, hg::sq,
          hg::subu, hg::swc1;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f20{ctx, 20};
    // 0x0030a740: prologue
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    s1 = a3;
    s0 = s2 & 0xFFFF;
    v0 = slti(s0, btl::kSkillCount);
    if (v0 == 0) {
        // 0x0030a788
        charge(ctx, 5);
        k_assert(a0, a1, 0x30A794u, kDatCalcFile, 5019);
    }
    // 0x0030a79c
    charge(ctx, 4);
    v1 = s1 & 0xFFFF;
    v0 = 4;
    if (v1 != v0) {
        // 0x0030a7ac
        charge(ctx, 3);
        v0 = 2;
        if (v1 == v0) {
            goto L_0030a7e4;
        }
        // 0x0030a7b8
        charge(ctx, 3);
        v0 = 256;
        if (v1 == v0) {
            goto L_0030a7e4;
        }
        // 0x0030a7c4
        charge(ctx, 3);
        v0 = 1024;
        if (v1 == v0) {
            goto L_0030a7e4;
        }
        // 0x0030a7d0
        charge(ctx, 3);
        v0 = 512;
        if (v1 == v0) {
            goto L_0030a7e4;
        }
        // 0x0030a7dc
        charge(ctx, 2);
        // 0x0030a7f0
        charge(ctx, 3);
        a0 = s2 & 0xFFFF;
        if (s4 != 0) {
            // 0x0030a7fc
            charge(ctx, 3);
            at = slti(s0, btl::kSkillCount);
            if (at == 0) {
                goto L_0030a8ac;
            }
            // 0x0030a808
            charge(ctx, 11);
            v0 = sll(a0, 2);
            v0 = addu(v0, a0);
            v0 = sll(v0, 1);
            v0 = addu(v0, a0);
            v1 = sll(v0, 2);  // * 44 (SkillRecord)
            lw(v0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
            v0 = addu(v0, v1);
            lbu(v0, v0, 0);
            v0 = v0 & 0x2;
            if (v0 == 0) {
                goto L_0030a8ac;
            }
            // 0x0030a834
            charge(ctx, 4);
            lhu(v0, s4, dat_unit::kFlags);
            v0 = v0 & dat_unit::kFlagEnemy;
            if (v0 != 0) {
                // 0x0030a844
                charge(ctx, 9);
                lhu(v1, s4, dat_unit::kId);
                v0 = sll(v1, 5);
                v0 = subu(v0, v1);
                v1 = sll(v0, 1);  // * 62 (EnemyRecord)
                lw(v0, gp, gp_off(btl::kUnitTablePtr));  // gBtlEnemyTbl
                v0 = addu(v1, v0);
                lhu(a0, v0, 60);
                goto L_0030a8ac;
            }
            // 0x0030a868
            charge(ctx, 17);
            lh(a0, s4, dat_unit::kId);
            a1 = 0;
            jal(ctx, 0x30A870u, gen::fn_datGetEquipmentIdx_0016cb80);
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            lh(a0, s4, dat_unit::kId);
            jal(ctx, 0x30A884u, gen::fn_sub_16F630_0016f630);
            v0 = v0 & 0xFFFF;
            a0 = dsll32(v0, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x30A898u, gen::fn_sub_170D60_00170d60);
            lh(s1, v0, 30);
            goto L_0030a8c0;
        }
    L_0030a8ac:
        charge(ctx, 5);
        v0 = a0 & 0xFFFF;
        v1 = sll(v0, 1);
        lw(v0, gp, gp_off(btl::kSkillElementTablePtr));  // gBtlSkillElementTbl
        v0 = addu(v0, v1);
        lb(s1, v0, 0);
    L_0030a8c0:
        charge(ctx, 5);
        s5 = dsll32(s1, 16);
        s5 = dsra32(s5, 16);
        v0 = slti(s5, 19);
        if (v0 == 0) {
            // 0x0030a8d4
            charge(ctx, 5);
            k_assert(a0, a1, 0x30A8E0u, kDatCalcFile, 3752);
        }
        // 0x0030a8e8
        charge(ctx, 8);
        v1 = addiu(s5, 1);
        v0 = 1;
        s5 = sllv(v0, v1);
        v1 = 0xE0000;
        v1 = v1 | 0x1;
        v1 = s5 & v1;
        if (v1 == 0) {
            // 0x0030a910
            charge(ctx, 7);
            a0 = s3;
            a1 = s1;
            jal(ctx, 0x30A918u, gen::fn_datCalcGetAffinityChecked_0030b4b0);
            v1 = s5 & 0xE;
            if (v1 == 0) {
                // 0x0030a92c
                charge(ctx, 3);
                v1 = s5 & 0x100;
                if (v1 != 0) {
                    // 0x0030a938
                    charge(ctx, 12);
                    lw(a1, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
                    a0 = s2 & 0xFFFF;
                    v1 = sll(a0, 2);
                    v1 = addu(v1, a0);
                    v1 = sll(v1, 1);
                    v1 = addu(v1, a0);
                    v1 = sll(v1, 2);  // * 44 (SkillRecord)
                    v1 = addu(v1, a1);
                    lbu(a0, v1, 2);
                    v1 = 1;
                    if (a0 == v1) {
                        goto L_0030a990;
                    }
                    goto L_0030a968;
                }
            L_0030a968:
                charge(ctx, 4);
                v1 = 0x8000000;
                v0 = v0 & v1;
                if (v0 == 0) {
                    // 0x0030a984
                    charge(ctx, 3);
                    v0 = 1;
                } else {
                    // 0x0030a978
                    charge(ctx, 3);
                    v0 = 4;
                }
                // 0x0030aed0: epilogue
                charge(ctx, 12);
                ld(ra, sp, 0x80);
                lq(s6, sp, 0x70);
                lq(s5, sp, 0x60);
                lq(s4, sp, 0x50);
                lq(s3, sp, 0x40);
                lq(s2, sp, 0x30);
                lq(s1, sp, 0x20);
                lq(s0, sp, 0x10);
                lwc1(f20, sp, 0x0);
                sp = addiu(sp, 0x90);
                return;
            }
        L_0030a990:
            charge(ctx, 12);
            a0 = s2 & 0xFFFF;
            v1 = sll(a0, 2);
            v1 = addu(v1, a0);
            v1 = sll(v1, 1);
            v1 = addu(v1, a0);
            s5 = sll(v1, 2);  // * 44 (SkillRecord)
            lw(a1, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
            v1 = addiu(a1, 37);
            v1 = addu(v1, s5);
            lbu(a0, v1, 0);
            if (a0 != 0) {
                // 0x0030a9e8
                charge(ctx, 4);
                lhu(v1, s3, dat_unit::kFlags);
                v1 = v1 & 0x100;
                if (v1 == 0) {
                    // 0x0030aa20
                    charge(ctx, 4);
                    v1 = 0x8000000;
                    v0 = v0 & v1;
                    if (v0 == 0) {
                        // 0x0030aa3c
                        charge(ctx, 7);
                        s1 = 0;
                        s6 = 0;
                        v0 = flt(1.0f);
                        mtc1(v0, f20);
                        v0 = 100;
                        if (a0 == v0) {
                            // 0x0030aa58
                            charge(ctx, 2);
                            s1 = v0;
                            s6 = v0;
                        }
                        // 0x0030aa60
                        charge(ctx, 5);
                        v0 = addu(s5, a1);
                        lbu(v1, v0, 2);
                        v0 = 2;
                        if (v1 != v0) {
                            // 0x0030aa74
                            charge(ctx, 3);
                            v0 = 1;
                            if (v1 != v0) {
                                // 0x0030aa80
                                charge(ctx, 2);
                                // 0x0030aeb8
                                charge(ctx, 5);
                                k_assert(a0, a1, 0x30AEC4u, kDatCalcFile, 5246);
                                goto L_0030aecc;
                            }
                            // 0x0030aa88
                            charge(ctx, 2);
                            if (s1 == 0) {
                                // 0x0030aa90
                                charge(ctx, 8);
                                a0 = 5;
                                a1 = s4;
                                a2 = s3;
                                a3 = s2;
                                t0 = 0;
                                jal(ctx, 0x30AAA4u, gen::fn_datScriptCalc_0030fc40);
                                s1 = v0;
                            }
                            // 0x0030aab0
                            charge(ctx, 6);
                            a0 = s3;
                            a1 = 561;
                            jal(ctx, 0x30AAB8u, gen::fn_datCalcHasSkill_003005e0);
                            if (v0 != 0) {
                                // 0x0030aac8
                                charge(ctx, 4);
                                v0 = flt(0.5f);
                                mtc1(v0, f0);
                                mul_s(f20, f20, f0);
                            }
                            // 0x0030aad8
                            charge(ctx, 6);
                            a0 = s4;
                            a1 = 562;
                            jal(ctx, 0x30AAE0u, gen::fn_datCalcHasSkill_003005e0);
                            if (v0 != 0) {
                                // 0x0030aaf0
                                charge(ctx, 4);
                                v0 = flt(2.0f);
                                mtc1(v0, f0);
                                mul_s(f20, f20, f0);
                            }
                            // 0x0030ab00
                            charge(ctx, 13);
                            mtc1(s1, f0);
                            cvt_s_w(f0, f0);
                            mul_s(f0, f0, f20);
                            cvt_w_s(f0, f0);
                            mfc1(s2, f0);
                            s1 = 0;
                            lw(v0, s3, dat_unit::kStatus);
                            v1 = dsll32(v0, 12);
                            v1 = dsrl32(v1, 12);
                            v0 = 64;
                            if (v1 == v0) {
                                // 0x0030ab84
                                charge(ctx, 1);
                                s1 = addiu(s1, 100);
                            } else {
                                // 0x0030ab34
                                charge(ctx, 3);
                                v0 = 8;
                                if (v1 == v0) {
                                    // 0x0030ab78
                                    charge(ctx, 3);
                                    s1 = addiu(s1, 100);
                                } else {
                                    // 0x0030ab40
                                    charge(ctx, 3);
                                    v0 = 4;
                                    if (v1 == v0) {
                                        // 0x0030ab6c
                                        charge(ctx, 3);
                                        s1 = addiu(s1, 40);
                                    } else {
                                        // 0x0030ab4c
                                        charge(ctx, 3);
                                        v0 = 2;
                                        if (v1 == v0) {
                                            // 0x0030ab60
                                            charge(ctx, 3);
                                            s1 = addiu(s1, 50);
                                        } else {
                                            // 0x0030ab58
                                            charge(ctx, 2);
                                        }
                                    }
                                }
                            }
                            // 0x0030ab88
                            charge(ctx, 4);
                            lhu(v0, s4, dat_unit::kFlags);
                            v0 = v0 & dat_unit::kFlagEnemy;
                            if (v0 == 0) {
                                // 0x0030aba4
                                charge(ctx, 3);
                                lh(a0, s4, dat_unit::kId);
                                jal(ctx, 0x30ABA8u, gen::fn_sub_16C920_0016c920);
                            } else {
                                // 0x0030ab98
                                charge(ctx, 3);
                                v0 = 0;
                            }
                            // 0x0030abb0
                            charge(ctx, 4);
                            v1 = v0 & 0xFFFF;
                            v0 = 1;
                            if (v1 != v0) {
                                // 0x0030abc0
                                charge(ctx, 4);
                                lhu(v0, s4, dat_unit::kFlags);
                                v0 = v0 & dat_unit::kFlagEnemy;
                                if (v0 == 0) {
                                    // 0x0030abdc
                                    charge(ctx, 3);
                                    lh(a0, s4, dat_unit::kId);
                                    jal(ctx, 0x30ABE0u, gen::fn_sub_16C920_0016c920);
                                } else {
                                    // 0x0030abd0
                                    charge(ctx, 3);
                                    v0 = 0;
                                }
                                // 0x0030abe8
                                charge(ctx, 4);
                                v1 = v0 & 0xFFFF;
                                v0 = 2;
                                if (v1 == v0) {
                                    // 0x0030abf8
                                    charge(ctx, 1);
                                    s1 = addiu(s1, 15);
                                }
                            }
                            // 0x0030abfc
                            charge(ctx, 3);
                            v0 = slti(s0, btl::kSkillCount);
                            if (v0 == 0) {
                                // 0x0030ac08
                                charge(ctx, 5);
                                k_assert(a0, a1, 0x30AC14u, kDatCalcFile, 4059);
                            }
                            // 0x0030ac1c
                            charge(ctx, 7);
                            lw(v0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
                            v0 = addu(v0, s5);
                            lbu(v0, v0, 0);
                            v0 = v0 & 0x2;
                            v0 = sltu(0, v0);
                            if (v0 != 0) {
                                // 0x0030ac38
                                charge(ctx, 4);
                                lhu(v0, s4, dat_unit::kFlags);
                                v0 = v0 & dat_unit::kFlagEnemy;
                                if (v0 == 0) {
                                    // 0x0030ac54
                                    charge(ctx, 4);
                                    lhu(a0, s4, dat_unit::kId);
                                    a1 = 67;
                                    jal(ctx, 0x30AC5Cu, gen::fn_sub_300750_00300750);
                                } else {
                                    // 0x0030ac48
                                    charge(ctx, 3);
                                    v0 = 0;
                                }
                                // 0x0030ac64
                                charge(ctx, 2);
                                if (v0 != 0) {
                                    // 0x0030ac6c
                                    charge(ctx, 1);
                                    s1 = addiu(s1, 5);
                                }
                                // 0x0030ac70
                                charge(ctx, 4);
                                lhu(v0, s4, dat_unit::kFlags);
                                v0 = v0 & dat_unit::kFlagEnemy;
                                if (v0 == 0) {
                                    // 0x0030ac8c
                                    charge(ctx, 4);
                                    lhu(a0, s4, dat_unit::kId);
                                    a1 = 68;
                                    jal(ctx, 0x30AC94u, gen::fn_sub_300750_00300750);
                                } else {
                                    // 0x0030ac80
                                    charge(ctx, 3);
                                    v0 = 0;
                                }
                                // 0x0030ac9c
                                charge(ctx, 2);
                                if (v0 != 0) {
                                    // 0x0030aca4
                                    charge(ctx, 1);
                                    s1 = addiu(s1, 10);
                                }
                                // 0x0030aca8
                                charge(ctx, 4);
                                lhu(v0, s4, dat_unit::kFlags);
                                v0 = v0 & dat_unit::kFlagEnemy;
                                if (v0 == 0) {
                                    // 0x0030acc4
                                    charge(ctx, 4);
                                    lhu(a0, s4, dat_unit::kId);
                                    a1 = 69;
                                    jal(ctx, 0x30ACCCu, gen::fn_sub_300750_00300750);
                                } else {
                                    // 0x0030acb8
                                    charge(ctx, 3);
                                    v0 = 0;
                                }
                                // 0x0030acd4
                                charge(ctx, 2);
                                if (v0 != 0) {
                                    // 0x0030acdc
                                    charge(ctx, 1);
                                    s1 = addiu(s1, 15);
                                }
                            }
                            // 0x0030ace0
                            charge(ctx, 8);
                            a0 = s4;
                            a1 = 5;
                            jal(ctx, 0x30ACE8u, gen::fn_datCalcGetEffectLevel_00300f60);
                            v0 = dsll32(v0, 24);
                            v0 = dsra32(v0, 24);
                            if (i64(v0) > 0) {
                                // 0x0030ad00
                                charge(ctx, 1);
                                s1 = addiu(s1, 7);
                            }
                            // 0x0030ad04
                            charge(ctx, 8);
                            a0 = s4;
                            a1 = 6;
                            jal(ctx, 0x30AD0Cu, gen::fn_datCalcGetEffectLevel_00300f60);
                            v0 = dsll32(v0, 24);
                            v0 = dsra32(v0, 24);
                            if (i64(v0) > 0) {
                                // 0x0030ad24
                                charge(ctx, 1);
                                s1 = addiu(s1, 15);
                            }
                            // 0x0030ad28
                            charge(ctx, 4);
                            s1 = addu(s2, s1);
                            at = slti(s1, 101);
                            if (at != 0) {
                                // 0x0030ad44
                                charge(ctx, 2);
                                if (i64(s1) < 0) {
                                    // 0x0030ad4c
                                    charge(ctx, 1);
                                    s1 = 0;
                                }
                            } else {
                                // 0x0030ad38
                                charge(ctx, 3);
                                s1 = 100;
                            }
                            // 0x0030ad50
                            charge(ctx, 6);
                            a0 = 100;
                            jal(ctx, 0x30AD54u, gen::fn_datCalcRand_002ffbc0);
                            at = slt(v0, s6);
                            if (at == 0) {
                                // 0x0030ad74
                                charge(ctx, 5);
                                a0 = 100;
                                jal(ctx, 0x30AD78u, gen::fn_datCalcRand_002ffbc0);
                                if (i64(v0) >= 0) {
                                    // 0x0030ad94
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x30AD98u, gen::fn_datCalcRand_002ffbc0);
                                    at = slt(v0, s1);
                                    if (at == 0) {
                                        // 0x0030adb8
                                        charge(ctx, 3);
                                        v0 = slti(s0, btl::kSkillCount);
                                        if (v0 == 0) {
                                            // 0x0030adc4
                                            charge(ctx, 5);
                                            k_assert(a0, a1, 0x30ADD0u, kDatCalcFile, 4059);
                                        }
                                        // 0x0030add8
                                        charge(ctx, 7);
                                        lw(v0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
                                        v0 = addu(v0, s5);
                                        lbu(v0, v0, 0);
                                        v0 = v0 & 0x2;
                                        v0 = sltu(0, v0);
                                        if (v0 == 0) {
                                            goto L_0030aecc;
                                        }
                                        // 0x0030adf4
                                        charge(ctx, 4);
                                        lhu(v0, s4, dat_unit::kFlags);
                                        v0 = v0 & dat_unit::kFlagEnemy;
                                        if (v0 == 0) {
                                            // 0x0030ae10
                                            charge(ctx, 7);
                                            a0 = s4;
                                            jal(ctx, 0x30AE14u, gen::fn_datCalcGetHeldWeaponType_00308c60);
                                            v1 = v0 & 0xFF;
                                            v0 = addiu(gp, -25336);  // &0x7CC9F8
                                            v0 = addu(v0, v1);
                                            lbu(v0, v0, 0);
                                        } else {
                                            // 0x0030ae04
                                            charge(ctx, 3);
                                            v0 = 1;
                                        }
                                        // 0x0030ae2c
                                        charge(ctx, 4);
                                        v0 = v0 & 0xFF;
                                        v0 = slti(v0, 2);
                                        if (v0 != 0) {
                                            goto L_0030aecc;
                                        }
                                        // 0x0030ae3c
                                        charge(ctx, 4);
                                        lhu(v0, s4, dat_unit::kFlags);
                                        v0 = v0 & dat_unit::kFlagEnemy;
                                        if (v0 != 0) {
                                            goto L_0030aecc;
                                        }
                                        // 0x0030ae4c
                                        charge(ctx, 12);
                                        v0 = flt(2.0f);
                                        mtc1(v0, f1);
                                        mtc1(s1, f0);
                                        cvt_s_w(f0, f0);
                                        mul_s(f0, f1, f0);
                                        cvt_w_s(f0, f0);
                                        mfc1(s0, f0);
                                        at = slti(s0, 51);
                                        if (at != 0) {
                                            // 0x0030ae88
                                            charge(ctx, 2);
                                            if (i64(s0) < 0) {
                                                // 0x0030ae90
                                                charge(ctx, 1);
                                                s0 = 0;
                                            }
                                        } else {
                                            // 0x0030ae7c
                                            charge(ctx, 3);
                                            s0 = 50;
                                        }
                                        // 0x0030ae94
                                        charge(ctx, 6);
                                        a0 = 100;
                                        jal(ctx, 0x30AE98u, gen::fn_datCalcRand_002ffbc0);
                                        at = slt(v0, s0);
                                        if (at == 0) {
                                            goto L_0030aecc;
                                        }
                                        // 0x0030aeac
                                        charge(ctx, 3);
                                        v0 = 8;
                                    } else {
                                        // 0x0030adac
                                        charge(ctx, 3);
                                        v0 = 2;
                                    }
                                } else {
                                    // 0x0030ad88
                                    charge(ctx, 3);
                                    v0 = 2;
                                }
                            } else {
                                // 0x0030ad68
                                charge(ctx, 3);
                                v0 = 2;
                            }
                            // 0x0030aed0: epilogue
                            charge(ctx, 12);
                            ld(ra, sp, 0x80);
                            lq(s6, sp, 0x70);
                            lq(s5, sp, 0x60);
                            lq(s4, sp, 0x50);
                            lq(s3, sp, 0x40);
                            lq(s2, sp, 0x30);
                            lq(s1, sp, 0x20);
                            lq(s0, sp, 0x10);
                            lwc1(f20, sp, 0x0);
                            sp = addiu(sp, 0x90);
                            return;
                        }
                    L_0030aecc:
                        charge(ctx, 1);
                        v0 = 1;
                    } else {
                        // 0x0030aa30
                        charge(ctx, 3);
                        v0 = 4;
                    }
                } else {
                    // 0x0030a9f8
                    charge(ctx, 4);
                    v1 = 0x8000000;
                    v0 = v0 & v1;
                    if (v0 == 0) {
                        // 0x0030aa14
                        charge(ctx, 1);
                        v0 = 1;
                    } else {
                        // 0x0030aa08
                        charge(ctx, 3);
                        v0 = 4;
                    }
                    // 0x0030aa18
                    charge(ctx, 2);
                }
            } else {
                // 0x0030a9c0
                charge(ctx, 4);
                v1 = 0x8000000;
                v0 = v0 & v1;
                if (v0 == 0) {
                    // 0x0030a9dc
                    charge(ctx, 1);
                    v0 = 1;
                } else {
                    // 0x0030a9d0
                    charge(ctx, 3);
                    v0 = 4;
                }
                // 0x0030a9e0
                charge(ctx, 2);
            }
        } else {
            // 0x0030a908
            charge(ctx, 2);
        }
        // 0x0030aed0: epilogue
        charge(ctx, 12);
        ld(ra, sp, 0x80);
        lq(s6, sp, 0x70);
        lq(s5, sp, 0x60);
        lq(s4, sp, 0x50);
        lq(s3, sp, 0x40);
        lq(s2, sp, 0x30);
        lq(s1, sp, 0x20);
        lq(s0, sp, 0x10);
        lwc1(f20, sp, 0x0);
        sp = addiu(sp, 0x90);
        return;
    }
L_0030a7e4:
    charge(ctx, 3);
    v0 = 1;
    // 0x0030aed0: epilogue
    charge(ctx, 12);
    ld(ra, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x0030AF00 sub_30AF00 -- 556 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [datCalcCanKnockDown](attacker, target, skill, result): 1 when a hit (result 1) of this skill can knock the target
// down: the target is not down (status 0x100000) and has no flag 0x10, the skill is a knock-down skill (SKILL +17, or
// a status skill +24 == 1 with status bit 0x80000), and its element (the attacker's weapon element for a physical
// skill; datCalcGetSkillElement inlined) is not -1, 16, 17 or 18.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void sub_30AF00(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::lb, hg::lbu,
          hg::ld, hg::lh, hg::lhu, hg::lq, hg::lw, hg::sd, hg::sll, hg::sllv, hg::slti, hg::sltu, hg::sq, hg::subu;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0030af00: prologue; s4 = attacker, s3 = target, s2 = skill, s1 = result; K_Assert(skill < 464)
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    s1 = a3;
    s0 = s2 & 0xFFFF;
    v0 = slti(s0, btl::kSkillCount);
    if (v0 == 0) {
        // 0x0030af3c
        charge(ctx, 5);
        k_assert(a0, a1, 0x30AF48u, kDatCalcFile, 5268);
    }
    // 0x0030af50: the target already down (status 0x100000)?
    charge(ctx, 6);
    lw(v1, s3, dat_unit::kStatus);
    v0 = 0x100000;
    v0 = v1 & v0;
    v0 = sltu(0, v0);
    if (v0 == 0) {
        // 0x0030af74: a hit (result 1)?
        charge(ctx, 4);
        v0 = s1 & 0xFFFF;
        a2 = 1;
        if (v0 == a2) {
            // 0x0030af90: target flag 0x10 (cannot be knocked down)?
            charge(ctx, 4);
            lhu(v0, s3, dat_unit::kFlags);
            v0 = v0 & 0x10;
            if (v0 == 0) {
                // 0x0030afac: v1 = the skill record (a1 = skill * 44, a0 = gBtlSkillTbl); +17 set: a knock-down skill
                charge(ctx, 11);
                v1 = s2 & 0xFFFF;
                v0 = sll(v1, 2);
                v0 = addu(v0, v1);
                v0 = sll(v0, 1);
                v0 = addu(v0, v1);
                a1 = sll(v0, 2);  // * 44 (SkillRecord)
                lw(a0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
                v1 = addu(a1, a0);
                lbu(v0, v1, skill_rec::kHpFormula);
                bool knocks = v0 != 0;
                if (!knocks) {
                    // 0x0030afd8: or a status skill (+24 == 1) ...
                    charge(ctx, 3);
                    lbu(v0, v1, 24);
                    if (v0 == a2) {
                        // 0x0030afe4: ... with status bit 0x80000 (+28)
                        charge(ctx, 5);
                        lw(v1, v1, 28);
                        v0 = 0x80000;
                        v0 = v1 & v0;
                        knocks = v0 != 0;
                    }
                }
                if (knocks) {
                    // 0x0030b004: v0 = the skill's element (datCalcGetSkillElement(attacker, skill) inlined)
                    charge(ctx, 3);
                    v1 = s2 & 0xFFFF;
                    bool table = true;  // the element from SKILL.TBL section 0
                    if (s4 != 0) {
                        // 0x0030b010
                        charge(ctx, 3);
                        at = slti(s0, btl::kSkillCount);
                        if (at != 0) {
                            // 0x0030b01c: physical?
                            charge(ctx, 5);
                            v0 = addu(a0, a1);
                            lbu(v0, v0, skill_rec::kFlags0);
                            v0 = v0 & skill_rec::kFlagPhysical;
                            if (v0 != 0) {
                                // 0x0030b030
                                charge(ctx, 4);
                                lhu(v0, s4, dat_unit::kFlags);
                                v0 = v0 & dat_unit::kFlagEnemy;
                                if (v0 != 0) {
                                    // 0x0030b040: an enemy: its normal-attack skill's element
                                    charge(ctx, 9);
                                    lhu(v1, s4, dat_unit::kId);
                                    v0 = sll(v1, 5);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 1);  // * 62 (EnemyRecord)
                                    lw(v0, gp, gp_off(btl::kUnitTablePtr));  // gBtlEnemyTbl
                                    v0 = addu(v1, v0);
                                    lhu(v1, v0, enemy_rec::kAttackSkill);
                                } else {
                                    // 0x0030b064: a party member: the weapon item's element (+30)
                                    charge(ctx, 17);
                                    lh(a0, s4, dat_unit::kId);
                                    a1 = 0;
                                    jal(ctx, 0x30B06Cu, gen::fn_datGetEquipmentIdx_0016cb80);
                                    a1 = dsll32(v0, 16);
                                    a1 = dsra32(a1, 16);
                                    lh(a0, s4, dat_unit::kId);
                                    jal(ctx, 0x30B080u, gen::fn_sub_16F630_0016f630);
                                    v0 = v0 & 0xFFFF;
                                    a0 = dsll32(v0, 16);
                                    a0 = dsra32(a0, 16);
                                    jal(ctx, 0x30B094u, gen::fn_sub_170D60_00170d60);
                                    lh(v0, v0, 30);
                                    table = false;
                                }
                            }
                        }
                    }
                    if (table) {
                        // 0x0030b0a8: SKILL.TBL section 0[v1] (s8)
                        charge(ctx, 5);
                        v0 = v1 & 0xFFFF;
                        v1 = sll(v0, 1);
                        lw(v0, gp, gp_off(btl::kSkillElementTablePtr));  // gBtlSkillElementTbl
                        v0 = addu(v0, v1);
                        lb(v0, v0, 0);
                    }
                    // 0x0030b0bc: s0 = (s16)element; K_Assert(element < 19)
                    charge(ctx, 5);
                    s0 = dsll32(v0, 16);
                    s0 = dsra32(s0, 16);
                    v0 = slti(s0, 19);
                    if (v0 == 0) {
                        // 0x0030b0d0
                        charge(ctx, 5);
                        k_assert(a0, a1, 0x30B0DCu, kDatCalcFile, 3752);
                    }
                    // 0x0030b0e4: element bit 1 << (e + 1) against -1 / 16..18 (0xE0001): those return 0, else v0 = 1
                    charge(ctx, 8);
                    v1 = addiu(s0, 1);
                    v0 = 1;
                    a0 = sllv(v0, v1);
                    v1 = 0xE0000;
                    v1 = v1 | 0x1;
                    v1 = a0 & v1;
                    if (v1 != 0) {
                        // 0x0030b104
                        charge(ctx, 1);
                        v0 = 0;
                    }
                } else {
                    // 0x0030aff8: not a knock-down skill: 0
                    charge(ctx, 3);
                    v0 = 0;
                }
            } else {
                // 0x0030afa0
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x0030af84
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0030af68
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0030b108: epilogue
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0030B130 sub_30B130 -- 212 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [datCalcCheckKnockDown](attacker, target, skill, result, affinity): sub_30AF00 and an affinity of 2 or 4.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void sub_30B130(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::sd, hg::slti, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0030b130: prologue; s4 = attacker, s3 = target, s2 = skill, s1 = result, s0 = affinity
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    s1 = a3;
    s0 = t0;
    v0 = s2 & 0xFFFF;
    v0 = slti(v0, btl::kSkillCount);
    if (v0 == 0) {
        // 0x0030b170: K_Assert(skill < 464)
        charge(ctx, 5);
        k_assert(a0, a1, 0x30B17Cu, kDatCalcFile, 5314);
    }
    // 0x0030b184: sub_30AF00(attacker, target, skill, result, affinity)
    charge(ctx, 9);
    a0 = s4;
    a1 = s3;
    a2 = s2;
    a3 = s1;
    t0 = s0;
    jal(ctx, 0x30B198u, gen::fn_sub_30AF00_0030af00);
    if (v0 != 0) {
        // 0x0030b1b4: and the affinity is 2 or 4
        charge(ctx, 4);
        v1 = s0 & 0xFFFF;
        v0 = 2;
        bool knocks = v1 == v0;
        if (!knocks) {
            // 0x0030b1c4
            charge(ctx, 3);
            v0 = 4;
            knocks = v1 == v0;
        }
        if (knocks) {
            // 0x0030b1d0: return 1
            charge(ctx, 3);
            v0 = 1;
        } else {
            // 0x0030b1dc: return 0
            charge(ctx, 1);
            v0 = 0;
        }
    } else {
        // 0x0030b1a8: return 0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0030b1e0: epilogue
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0030B210 sub_30B210 -- 672 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [datCalcRollFollowUp](attacker, target, skill, result): after a physical hit with result 4 or 2 on a target that is
// not down, by an attacker without flag 0x20 (party members 2 and 3 never, 1 not with weapon type 6 / 7):
// datCalcRand(100) < 100 for an enemy, else 70, 80 / 50 / 0 with equipment effects 100 / 101 / 102.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void sub_30B210(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lhu, hg::lq, hg::lw,
          hg::sd, hg::sll, hg::slt, hg::slti, hg::sltu, hg::sq;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    auto epilogue = [&] {  // 0x0030b490
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
    };
    // 0x0030b210: prologue; s3 = attacker, s2 = target, s1 = skill, s0 = result; K_Assert(skill < 464)
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    s0 = a3;
    v0 = s1 & 0xFFFF;
    v0 = slti(v0, btl::kSkillCount);
    if (v0 == 0) {
        // 0x0030b248
        charge(ctx, 5);
        k_assert(a0, a1, 0x30B254u, kDatCalcFile, 5365);
    }
    // 0x0030b25c: a physical skill?
    charge(ctx, 12);
    v1 = s1 & 0xFFFF;
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    v0 = addu(v0, v1);
    v1 = sll(v0, 2);  // * 44 (SkillRecord)
    lw(v0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
    v0 = addu(v0, v1);
    lbu(v0, v0, skill_rec::kFlags0);
    v0 = v0 & skill_rec::kFlagPhysical;
    if (v0 != 0) {
        // 0x0030b298: the target not down (status 0x100000)?
        charge(ctx, 6);
        lw(v1, s2, dat_unit::kStatus);
        v0 = 0x100000;
        v0 = v1 & v0;
        v0 = sltu(0, v0);
        if (v0 == 0) {
            // 0x0030b2bc: the attacker without flag 0x20?
            charge(ctx, 4);
            lhu(v1, s3, dat_unit::kFlags);
            v0 = v1 & 0x20;
            if (v0 == 0) {
                // 0x0030b2d8
                charge(ctx, 3);
                v0 = v1 & dat_unit::kFlagEnemy;
                if (v0 == 0) {
                    // 0x0030b2e4: a party member: K_Assert(id < 11)
                    charge(ctx, 4);
                    lhu(v0, s3, dat_unit::kId);
                    v0 = slti(v0, dat_unit::kPartyIds);
                    if (v0 == 0) {
                        // 0x0030b2f4
                        charge(ctx, 5);
                        k_assert(a0, a1, 0x30B300u, kDatCalcFile, 5382);
                    }
                    // 0x0030b308: members 3 and 2 never follow up
                    charge(ctx, 4);
                    lhu(v1, s3, dat_unit::kId);
                    v0 = 3;
                    bool never = v1 == v0;
                    if (!never) {
                        // 0x0030b318
                        charge(ctx, 3);
                        v0 = 2;
                        never = v1 == v0;
                        if (!never) {
                            // 0x0030b324: the hero not with weapon type 6 or 7
                            charge(ctx, 3);
                            v0 = dat_unit::kHero;
                            if (v1 != v0) {
                                // 0x0030b330
                                charge(ctx, 2);
                            } else {
                                // 0x0030b338
                                charge(ctx, 7);
                                a0 = s3;
                                jal(ctx, 0x30B33Cu, gen::fn_datCalcGetHeldWeaponType_00308c60);
                                v1 = v0 & 0xFF;
                                v0 = 6;
                                bool bad_weapon = v1 == v0;
                                if (!bad_weapon) {
                                    // 0x0030b354
                                    charge(ctx, 3);
                                    v0 = 7;
                                    bad_weapon = v1 == v0;
                                }
                                if (bad_weapon) {
                                    // 0x0030b360: return 0
                                    charge(ctx, 3);
                                    v0 = 0;
                                    epilogue();
                                    return;
                                }
                            }
                        }
                    }
                    if (never) {
                        // 0x0030b36c: return 0
                        charge(ctx, 3);
                        v0 = 0;
                        epilogue();
                        return;
                    }
                }
                // 0x0030b378: result 4 or 2?
                charge(ctx, 4);
                v1 = s0 & 0xFFFF;
                v0 = 4;
                bool hit = v1 == v0;
                if (!hit) {
                    // 0x0030b388
                    charge(ctx, 3);
                    v0 = 2;
                    hit = v1 == v0;
                }
                if (!hit) {
                    // 0x0030b394: return 0
                    charge(ctx, 3);
                    v0 = 0;
                    epilogue();
                    return;
                }
                // 0x0030b3a0: s0 = the chance: 100 for an enemy, 70 for a party member ...
                charge(ctx, 4);
                lhu(v0, s3, dat_unit::kFlags);
                v1 = v0 & dat_unit::kFlagEnemy;
                if (v1 == 0) {
                    // 0x0030b3bc
                    charge(ctx, 1);
                    v0 = 70;
                } else {
                    // 0x0030b3b0
                    charge(ctx, 3);
                    v0 = 100;
                }
                // 0x0030b3c0: ... 80 with equipment effect 100 (sub_300750)
                charge(ctx, 3);
                s0 = v0 & 0xFFFF;
                if (v1 == 0) {
                    // 0x0030b3d8
                    charge(ctx, 4);
                    lhu(a0, s3, dat_unit::kId);
                    a1 = 100;
                    jal(ctx, 0x30B3E0u, gen::fn_sub_300750_00300750);
                } else {
                    // 0x0030b3cc
                    charge(ctx, 3);
                    v0 = 0;
                }
                // 0x0030b3e8
                charge(ctx, 2);
                if (v0 != 0) {
                    // 0x0030b3f0
                    charge(ctx, 1);
                    s0 = 80;
                }
                // 0x0030b3f4: ... 50 with effect 101
                charge(ctx, 4);
                lhu(v0, s3, dat_unit::kFlags);
                v0 = v0 & dat_unit::kFlagEnemy;
                if (v0 == 0) {
                    // 0x0030b410
                    charge(ctx, 4);
                    lhu(a0, s3, dat_unit::kId);
                    a1 = 101;
                    jal(ctx, 0x30B418u, gen::fn_sub_300750_00300750);
                } else {
                    // 0x0030b404
                    charge(ctx, 3);
                    v0 = 0;
                }
                // 0x0030b420
                charge(ctx, 2);
                if (v0 != 0) {
                    // 0x0030b428
                    charge(ctx, 1);
                    s0 = 50;
                }
                // 0x0030b42c: ... 0 with effect 102
                charge(ctx, 4);
                lhu(v0, s3, dat_unit::kFlags);
                v0 = v0 & dat_unit::kFlagEnemy;
                if (v0 == 0) {
                    // 0x0030b448
                    charge(ctx, 4);
                    lhu(a0, s3, dat_unit::kId);
                    a1 = 102;
                    jal(ctx, 0x30B450u, gen::fn_sub_300750_00300750);
                } else {
                    // 0x0030b43c
                    charge(ctx, 3);
                    v0 = 0;
                }
                // 0x0030b458
                charge(ctx, 2);
                if (v0 != 0) {
                    // 0x0030b460
                    charge(ctx, 1);
                    s0 = 0;
                }
                // 0x0030b464: return datCalcRand(100) < chance
                charge(ctx, 7);
                a0 = 100;
                jal(ctx, 0x30B468u, gen::fn_datCalcRand_002ffbc0);
                v1 = s0 & 0xFFFF;
                at = slt(v0, v1);
                if (at == 0) {
                    // 0x0030b48c
                    charge(ctx, 1);
                    v0 = 0;
                } else {
                    // 0x0030b480
                    charge(ctx, 3);
                    v0 = 1;
                }
            } else {
                // 0x0030b2cc
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x0030b2b0
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0030b28c
        charge(ctx, 3);
        v0 = 0;
    }
    epilogue();
}

// 0x0030B640 sub_30B640 -- 860 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [datCalcGetCounterSkill](unit, skill): the counter passive that answers this skill, or -1 (0 for a unit with flag
// 0x40). Element 8: 438 for a party member with sub_170760(pc, 4039) > 0, then 580 (10 %), 587 (50 %), 601; element
// 9 the same with 581, 588, 602; then (nothing yet) 572 without flag 0x400, else 571 without flag 8; 609 wins over
// all. The element is the inlined datCalcGetSkillElement.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void sub_30B640(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::lb, hg::lbu,
          hg::ld, hg::lh, hg::lhu, hg::lq, hg::lw, hg::sd, hg::si, hg::sll, hg::slt, hg::slti, hg::sq, hg::subu;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0030b640: prologue; s1 = unit, s0 = counter = -1; flag 0x40: return 0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = si(-1);
    lhu(a0, a0, dat_unit::kFlags);
    v0 = a0 & 0x40;
    if (v0 == 0) {
        // 0x0030b674: v0 = the skill's element (datCalcGetSkillElement(unit, skill) inlined)
        charge(ctx, 3);
        a1 = a1 & 0xFFFF;
        bool table = true;  // the element from SKILL.TBL section 0
        if (s1 != 0) {
            // 0x0030b680
            charge(ctx, 3);
            at = slti(a1, btl::kSkillCount);
            if (at != 0) {
                // 0x0030b68c: physical?
                charge(ctx, 11);
                v0 = sll(a1, 2);
                v0 = addu(v0, a1);
                v0 = sll(v0, 1);
                v0 = addu(v0, a1);
                v1 = sll(v0, 2);  // * 44 (SkillRecord)
                lw(v0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
                v0 = addu(v0, v1);
                lbu(v0, v0, skill_rec::kFlags0);
                v0 = v0 & skill_rec::kFlagPhysical;
                if (v0 != 0) {
                    // 0x0030b6b8
                    charge(ctx, 3);
                    v0 = a0 & dat_unit::kFlagEnemy;
                    if (v0 != 0) {
                        // 0x0030b6c4: an enemy: its normal-attack skill's element
                        charge(ctx, 9);
                        lhu(v1, s1, dat_unit::kId);
                        v0 = sll(v1, 5);
                        v0 = subu(v0, v1);
                        v1 = sll(v0, 1);  // * 62 (EnemyRecord)
                        lw(v0, gp, gp_off(btl::kUnitTablePtr));  // gBtlEnemyTbl
                        v0 = addu(v1, v0);
                        lhu(a1, v0, enemy_rec::kAttackSkill);
                    } else {
                        // 0x0030b6e8: a party member: the weapon item's element (+30)
                        charge(ctx, 17);
                        lh(a0, s1, dat_unit::kId);
                        a1 = 0;
                        jal(ctx, 0x30B6F0u, gen::fn_datGetEquipmentIdx_0016cb80);
                        a1 = dsll32(v0, 16);
                        a1 = dsra32(a1, 16);
                        lh(a0, s1, dat_unit::kId);
                        jal(ctx, 0x30B704u, gen::fn_sub_16F630_0016f630);
                        v0 = v0 & 0xFFFF;
                        a0 = dsll32(v0, 16);
                        a0 = dsra32(a0, 16);
                        jal(ctx, 0x30B718u, gen::fn_sub_170D60_00170d60);
                        lh(v0, v0, 30);
                        table = false;
                    }
                }
            }
        }
        if (table) {
            // 0x0030b72c: SKILL.TBL section 0[a1] (s8)
            charge(ctx, 5);
            v0 = a1 & 0xFFFF;
            v1 = sll(v0, 1);
            lw(v0, gp, gp_off(btl::kSkillElementTablePtr));  // gBtlSkillElementTbl
            v0 = addu(v0, v1);
            lb(v0, v0, 0);
        }
        // 0x0030b740: by element
        charge(ctx, 5);
        v1 = dsll32(v0, 16);
        v1 = dsra32(v1, 16);
        v0 = 8;
        if (v1 != v0) {
            // 0x0030b820
            charge(ctx, 3);
            v0 = 9;
            if (v1 == v0) {
                // 0x0030b82c: element 9: 438 for a party member with sub_170760(pc, 4039) > 0 ...
                charge(ctx, 4);
                lhu(v0, s1, dat_unit::kFlags);
                v0 = v0 & dat_unit::kFlagEnemy;
                if (v0 == 0) {
                    // 0x0030b848
                    charge(ctx, 6);
                    lh(a0, s1, dat_unit::kId);
                    a1 = 4039;
                    jal(ctx, 0x30B850u, gen::fn_sub_170760_00170760);
                    v0 = v0 & 0xFFFF;
                    v0 = slt(0, v0);
                } else {
                    // 0x0030b83c
                    charge(ctx, 3);
                    v0 = 0;
                }
                // 0x0030b860
                charge(ctx, 2);
                if (v0 != 0) {
                    // 0x0030b868
                    charge(ctx, 1);
                    s0 = 438;
                }
                // 0x0030b86c: ... 581 (datCalcRand(100) < 10)
                charge(ctx, 6);
                a0 = s1;
                a1 = 581;
                jal(ctx, 0x30B874u, gen::fn_datCalcHasSkill_003005e0);
                if (v0 != 0) {
                    // 0x0030b884
                    charge(ctx, 6);
                    a0 = 100;
                    jal(ctx, 0x30B888u, gen::fn_datCalcRand_002ffbc0);
                    at = slti(v0, 10);
                    if (at != 0) {
                        // 0x0030b89c
                        charge(ctx, 1);
                        s0 = 581;
                    }
                }
                // 0x0030b8a0: ... 588 (< 50)
                charge(ctx, 6);
                a0 = s1;
                a1 = 588;
                jal(ctx, 0x30B8A8u, gen::fn_datCalcHasSkill_003005e0);
                if (v0 != 0) {
                    // 0x0030b8b8
                    charge(ctx, 6);
                    a0 = 100;
                    jal(ctx, 0x30B8BCu, gen::fn_datCalcRand_002ffbc0);
                    at = slti(v0, 50);
                    if (at != 0) {
                        // 0x0030b8d0
                        charge(ctx, 1);
                        s0 = 588;
                    }
                }
                // 0x0030b8d4: ... 602
                charge(ctx, 6);
                a0 = s1;
                a1 = 602;
                jal(ctx, 0x30B8DCu, gen::fn_datCalcHasSkill_003005e0);
                if (v0 != 0) {
                    // 0x0030b8ec
                    charge(ctx, 1);
                    s0 = 602;
                }
            }
        } else {
            // 0x0030b754: element 8: 438 for a party member with sub_170760(pc, 4039) > 0 ...
            charge(ctx, 4);
            lhu(v0, s1, dat_unit::kFlags);
            v0 = v0 & dat_unit::kFlagEnemy;
            if (v0 == 0) {
                // 0x0030b770
                charge(ctx, 6);
                lh(a0, s1, dat_unit::kId);
                a1 = 4039;
                jal(ctx, 0x30B778u, gen::fn_sub_170760_00170760);
                v0 = v0 & 0xFFFF;
                v0 = slt(0, v0);
            } else {
                // 0x0030b764
                charge(ctx, 3);
                v0 = 0;
            }
            // 0x0030b788
            charge(ctx, 2);
            if (v0 != 0) {
                // 0x0030b790
                charge(ctx, 1);
                s0 = 438;
            }
            // 0x0030b794: ... 580 (datCalcRand(100) < 10)
            charge(ctx, 6);
            a0 = s1;
            a1 = 580;
            jal(ctx, 0x30B79Cu, gen::fn_datCalcHasSkill_003005e0);
            if (v0 != 0) {
                // 0x0030b7ac
                charge(ctx, 6);
                a0 = 100;
                jal(ctx, 0x30B7B0u, gen::fn_datCalcRand_002ffbc0);
                at = slti(v0, 10);
                if (at != 0) {
                    // 0x0030b7c4
                    charge(ctx, 1);
                    s0 = 580;
                }
            }
            // 0x0030b7c8: ... 587 (< 50)
            charge(ctx, 6);
            a0 = s1;
            a1 = 587;
            jal(ctx, 0x30B7D0u, gen::fn_datCalcHasSkill_003005e0);
            if (v0 != 0) {
                // 0x0030b7e0
                charge(ctx, 6);
                a0 = 100;
                jal(ctx, 0x30B7E4u, gen::fn_datCalcRand_002ffbc0);
                at = slti(v0, 50);
                if (at != 0) {
                    // 0x0030b7f8
                    charge(ctx, 1);
                    s0 = 587;
                }
            }
            // 0x0030b7fc: ... 601
            charge(ctx, 6);
            a0 = s1;
            a1 = 601;
            jal(ctx, 0x30B804u, gen::fn_datCalcHasSkill_003005e0);
            if (v0 != 0) {
                // 0x0030b814
                charge(ctx, 3);
                s0 = 601;
            }
        }
        // 0x0030b8f0: nothing yet: 572 without flag 0x400, else 571 without flag 8
        charge(ctx, 5);
        v1 = dsll32(s0, 16);
        v1 = dsra32(v1, 16);
        v0 = si(-1);
        if (v1 == v0) {
            // 0x0030b904
            charge(ctx, 4);
            lhu(v0, s1, dat_unit::kFlags);
            v0 = v0 & 0x400;
            bool try571 = true;
            if (v0 == 0) {
                // 0x0030b914
                charge(ctx, 6);
                a0 = s1;
                a1 = 572;
                jal(ctx, 0x30B91Cu, gen::fn_datCalcHasSkill_003005e0);
                if (v0 != 0) {
                    // 0x0030b92c
                    charge(ctx, 3);
                    s0 = 572;
                    try571 = false;
                }
            }
            if (try571) {
                // 0x0030b938
                charge(ctx, 4);
                lhu(v0, s1, dat_unit::kFlags);
                v0 = v0 & 0x8;
                if (v0 == 0) {
                    // 0x0030b948
                    charge(ctx, 6);
                    a0 = s1;
                    a1 = 571;
                    jal(ctx, 0x30B950u, gen::fn_datCalcHasSkill_003005e0);
                    if (v0 != 0) {
                        // 0x0030b960
                        charge(ctx, 1);
                        s0 = 571;
                    }
                }
            }
        }
        // 0x0030b964: 609 wins over all
        charge(ctx, 6);
        a0 = s1;
        a1 = 609;
        jal(ctx, 0x30B96Cu, gen::fn_datCalcHasSkill_003005e0);
        if (v0 != 0) {
            // 0x0030b97c
            charge(ctx, 1);
            s0 = 609;
        }
        // 0x0030b980: return the counter skill
        charge(ctx, 1);
        v0 = s0;
    } else {
        // 0x0030b668: flag 0x40: return 0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0030b984: epilogue
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0030B9A0 sub_30B9A0 -- 408 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [datCalcGetHitCount](unit, skill, result): a magic skill hits min (+15) .. max (+16) times (min + datCalcRand(max -
// min) when min < max; K_Assert when either is not positive); a physical skill once for an enemy or a weapon of class
// 1, else the class, or 2 for result 8 (1 for other results without bits 1/2).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void sub_30B9A0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::i64, hg::jal, hg::lbu, hg::ld, hg::lhu, hg::lq,
          hg::lw, hg::sd, hg::sll, hg::slt, hg::slti, hg::sq, hg::subu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0030b9a0: prologue; s1 = unit, s2 = skill, s0 = result; K_Assert(skill < 464)
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s2 = a1;
    s0 = a2;
    v0 = s2 & 0xFFFF;
    v0 = slti(v0, btl::kSkillCount);
    if (v0 == 0) {
        // 0x0030b9d0
        charge(ctx, 5);
        k_assert(a0, a1, 0x30B9DCu, kDatCalcFile, 5643);
    }
    // 0x0030b9e4: v1 = the skill record; physical?
    charge(ctx, 12);
    v1 = s2 & 0xFFFF;
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    v0 = addu(v0, v1);
    v1 = sll(v0, 2);  // * 44 (SkillRecord)
    lw(v0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
    v1 = addu(v0, v1);
    lbu(v0, v1, skill_rec::kFlags0);
    v0 = v0 & skill_rec::kFlagPhysical;
    if (v0 == 0) {
        // 0x0030bab8: a magic skill: s1 = min hits (+15), s0 = max hits (+16); K_Assert(both > 0)
        charge(ctx, 4);
        lbu(s1, v1, 15);
        lbu(s0, v1, 16);
        bool ok = false;
        if (i64(s1) > 0) {
            // 0x0030bac8
            charge(ctx, 3);
            v0 = s0 & 0xFF;
            ok = i64(v0) > 0;
        }
        if (!ok) {
            // 0x0030bad4
            charge(ctx, 5);
            k_assert(a0, a1, 0x30BAE0u, kDatCalcFile, 5657);
        }
        // 0x0030bae8
        charge(ctx, 4);
        v1 = s0 & 0xFF;
        v0 = slt(s1, v1);
        if (v0 != 0) {
            // 0x0030bb04: min < max: return (u8)(min + datCalcRand(max - min))
            charge(ctx, 6);
            s0 = s1 & 0xFF;
            a0 = subu(v1, s0);
            jal(ctx, 0x30BB0Cu, gen::fn_datCalcRand_002ffbc0);
            v0 = addu(s0, v0);
            v0 = v0 & 0xFF;
        } else {
            // 0x0030baf8: return min
            charge(ctx, 3);
            v0 = s1;
        }
    } else {
        // 0x0030ba14: a physical skill: an enemy hits once
        charge(ctx, 4);
        lhu(v0, s1, dat_unit::kFlags);
        v0 = v0 & dat_unit::kFlagEnemy;
        if (v0 != 0) {
            // 0x0030baac
            charge(ctx, 3);
            v0 = 1;
        } else {
            // 0x0030ba24: the weapon class (sub_308FD0 inlined)
            charge(ctx, 2);
            if (v0 == 0) {
                // 0x0030ba38: kWeaponClassTable[datCalcGetHeldWeaponType(unit)]
                charge(ctx, 7);
                a0 = s1;
                jal(ctx, 0x30BA3Cu, gen::fn_datCalcGetHeldWeaponType_00308c60);
                v1 = v0 & 0xFF;
                v0 = addiu(gp, gp_off(btl::kWeaponClassTable));
                v0 = addu(v0, v1);
                lbu(v0, v0, 0);
            } else {
                // 0x0030ba2c
                charge(ctx, 3);
                v0 = 1;
            }
            // 0x0030ba54: class 1 hits once; otherwise result bits 1/2 -> the class, result 8 -> 2, else 1
            charge(ctx, 4);
            v0 = v0 & 0xFF;
            a1 = 1;
            if (v0 != a1) {
                // 0x0030ba70
                charge(ctx, 4);
                a0 = s0 & 0xFFFF;
                v1 = a0 & 0x6;
                if (v1 == 0) {
                    // 0x0030ba88
                    charge(ctx, 3);
                    v0 = 8;
                    if (a0 != v0) {
                        // 0x0030baa0
                        charge(ctx, 1);
                        v0 = a1 & 0xFF;
                    } else {
                        // 0x0030ba94
                        charge(ctx, 3);
                        v0 = 2;
                    }
                } else {
                    // 0x0030ba80
                    charge(ctx, 2);
                }
            } else {
                // 0x0030ba64
                charge(ctx, 3);
                v0 = a1 & 0xFF;
            }
            // 0x0030baa4
            charge(ctx, 2);
        }
    }
    // 0x0030bb1c: epilogue
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// ================================================================================================================
// Readers
// ================================================================================================================

// 0x0030BB40 datGetSkillName -- 100 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// datGetSkillName(id): MSG.TBL section 1 + 19 * id (K_Assert id < 624, line 5674).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void datGetSkillName(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sll,
          hg::slti, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0030bb40: prologue
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    v0 = s0 & 0xFFFF;
    v0 = slti(v0, 624);
    if (v0 == 0) {
        // 0x0030bb60
        charge(ctx, 5);
        k_assert(a0, a1, 0x30BB6Cu, kDatCalcFile, 5674);
    }
    // 0x0030bb74: epilogue
    charge(ctx, 12);
    v1 = s0 & 0xFFFF;
    v0 = sll(v1, 3);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    v1 = addu(v0, v1);
    lw(v0, gp, gp_off(btl::kSkillNamesPtr));  // 0x7CE4EC
    v0 = addu(v0, v1);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030BBB0 datGetArcanaName -- 100 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// datGetArcanaName(id): MSG.TBL section 0 + 21 * (u8)id (K_Assert id < 32, line 5688).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void datGetArcanaName(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sll,
          hg::slti, hg::sq, hg::subu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0030bbb0: prologue
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    v0 = s0 & 0xFF;
    v0 = slti(v0, 32);
    if (v0 == 0) {
        // 0x0030bbd0
        charge(ctx, 5);
        k_assert(a0, a1, 0x30BBDCu, kDatCalcFile, 5688);
    }
    // 0x0030bbe4: epilogue
    charge(ctx, 12);
    v1 = s0 & 0xFF;
    v0 = sll(v1, 3);
    v1 = subu(v0, v1);
    v0 = sll(v1, 2);
    v1 = subu(v0, v1);
    lw(v0, gp, gp_off(btl::kArcanaNamesPtr));  // 0x7CE4F0
    v0 = addu(v0, v1);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x30BC20 [datGetItemPrice](item): the u16 at +8 of sub_170E90's record (the id sign-extended).
u64 sub_30BC20(EEContext& ctx, u64 item) {
    guest::enter(ctx, 11);
    Frame f(ctx, 16, 0, kS0 - 1);
    S(ctx, kA0, sx16(item));
    const u64 rec = jal(ctx, 0x30bc30, &rg::fn_sub_170E90_00170e90);
    return ld<u16>(ctx, rec + 8);
}

// 0x0030BC50 sub_30BC50 -- 400 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [datCalcGetEnemyExp](unit): EnemyRecord +32 (u16), x1.3 under flag 3024 and x1.2 under flag 4881 (the
// floats at gp-32364 / gp-32656), each as an unsigned float round trip.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void sub_30BC50(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::addu, hg::c_le_s, hg::charge, hg::cond, hg::cvt_s_w,
          hg::cvt_w_s, hg::enter, hg::i64, hg::jal, hg::ld, hg::lhu, hg::lq, hg::lui, hg::lw, hg::lwc1, hg::mfc1,
          hg::mtc1, hg::mul_s, hg::sd, hg::sll, hg::slti, hg::sq, hg::srl, hg::sub_s, hg::subu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x0030bc50: prologue
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lhu(v0, a0, 2);
    v0 = slti(v0, enemy_rec::kCount);
    if (v0 == 0) {
        // 0x0030bc70
        charge(ctx, 5);
        k_assert(a0, a1, 0x30BC7Cu, kDatCalcFile, 5723);
    }
    // 0x0030bc84
    charge(ctx, 13);
    lhu(v1, s0, 2);
    v0 = sll(v1, 5);
    v0 = subu(v0, v1);
    v1 = sll(v0, 1);  // * 62 (EnemyRecord)
    lw(v0, gp, gp_off(btl::kUnitTablePtr));  // gBtlEnemyTbl
    v0 = addu(v0, v1);
    lhu(s0, v0, 32);
    a0 = 3024;
    jal(ctx, 0x30BCA4u, gen::fn_datGetFlag_0016f190);
    v1 = 1;
    if (v0 == v1) {
        // 0x0030bcb8
        charge(ctx, 2);
        if (i64(s0) < 0) {
            // 0x0030bcd4
            charge(ctx, 7);
            v1 = srl(s0, 1);
            v0 = s0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f0);
            cvt_s_w(f1, f0);
            add_s(f1, f1, f1);
        } else {
            // 0x0030bcc0
            charge(ctx, 5);
            mtc1(s0, f0);
            cvt_s_w(f1, f0);
        }
        // 0x0030bcf0
        charge(ctx, 8);
        lwc1(f0, gp, gp_off(ai::kLit1_30));  // 0x7CAE84
        mul_s(f1, f0, f1);
        v0 = flt(2147483648.0f);
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x0030bd20
            charge(ctx, 5);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(s0, f0);
            v0 = lui(0x8000);
            s0 = s0 | v0;
        } else {
            // 0x0030bd10
            charge(ctx, 4);
            cvt_w_s(f0, f1);
            mfc1(s0, f0);
        }
    }
    // 0x0030bd34
    charge(ctx, 6);
    a0 = 4881;
    jal(ctx, 0x30BD38u, gen::fn_datGetFlag_0016f190);
    v1 = 1;
    if (v0 == v1) {
        // 0x0030bd4c
        charge(ctx, 2);
        if (i64(s0) < 0) {
            // 0x0030bd68
            charge(ctx, 7);
            v1 = srl(s0, 1);
            v0 = s0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f0);
            cvt_s_w(f1, f0);
            add_s(f1, f1, f1);
        } else {
            // 0x0030bd54
            charge(ctx, 5);
            mtc1(s0, f0);
            cvt_s_w(f1, f0);
        }
        // 0x0030bd84
        charge(ctx, 8);
        lwc1(f0, gp, gp_off(0x7CAD60u));  // 0x7CAD60
        mul_s(f1, f0, f1);
        v0 = flt(2147483648.0f);
        mtc1(v0, f0);
        c_le_s(f0, f1);
        if (cond(ctx)) {
            // 0x0030bdb4
            charge(ctx, 5);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(s0, f0);
            v0 = lui(0x8000);
            s0 = s0 | v0;
        } else {
            // 0x0030bda4
            charge(ctx, 4);
            cvt_w_s(f0, f1);
            mfc1(s0, f0);
        }
    }
    // 0x0030bdc8: epilogue
    charge(ctx, 6);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030BDE0 sub_30BDE0 -- 736 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [datCalcRollEnemyDrop](unit, rare_out): an enemy's drop. The rare item (+52, needs flag +50 and datCalcRand(100) <
// +54) sets *rare_out = 1; else one of the four common slots (+34 item, +36 weight; ids 5000+ only while their MT bit
// 5512 - id is clear): datCalcRand(200, or the 66.67 of gp-32136 under flag 3032) < the total weight, then a
// weighted pick by datCalcRand(total). 0 for no drop.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void sub_30BDE0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::c_le_s, hg::charge, hg::cond, hg::cvt_w_s,
          hg::enter, hg::i64, hg::jal, hg::lbu, hg::ld, hg::lhu, hg::lq, hg::lui, hg::lw, hg::lwc1, hg::mfc1,
          hg::mtc1, hg::sd, hg::sll, hg::slt, hg::slti, hg::sq, hg::sub_s, hg::subu, hg::sw;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    auto epilogue = [&] {  // 0x0030c090: return s0
        charge(ctx, 12);
        v0 = s0;
        ld(ra, sp, 0x70);
        lq(s6, sp, 0x60);
        lq(s5, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x80);
    };
    // 0x0030bde0: prologue; s0 = unit, s1 = rare_out; K_Assert(an enemy)
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s1 = a1;
    lhu(v0, a0, dat_unit::kFlags);
    v0 = v0 & dat_unit::kFlagEnemy;
    if (v0 == 0) {
        // 0x0030be1c
        charge(ctx, 5);
        k_assert(a0, a1, 0x30BE28u, kDatCalcFile, 5755);
    }
    // 0x0030be30: K_Assert(id < 336)
    charge(ctx, 4);
    lhu(v0, s0, dat_unit::kId);
    v0 = slti(v0, enemy_rec::kCount);
    if (v0 == 0) {
        // 0x0030be40
        charge(ctx, 5);
        k_assert(a0, a1, 0x30BE4Cu, kDatCalcFile, 5756);
    }
    // 0x0030be54: s3 = the enemy record, s0 = drop = 0; *rare_out = 0
    charge(ctx, 9);
    lhu(v1, s0, dat_unit::kId);
    v0 = sll(v1, 5);
    v0 = subu(v0, v1);
    v1 = sll(v0, 1);  // * 62 (EnemyRecord)
    lw(v0, gp, gp_off(btl::kUnitTablePtr));  // gBtlEnemyTbl
    s3 = addu(v0, v1);
    s0 = 0;
    if (s1 != 0) {
        // 0x0030be78
        charge(ctx, 1);
        sw(zero, s1, 0);
    }
    // 0x0030be7c: the rare drop: an item, its flag set, datCalcRand(100) < chance
    charge(ctx, 3);
    lhu(v0, s3, enemy_rec::kRareItem);
    if (v0 != 0) {
        // 0x0030be88
        charge(ctx, 3);
        lhu(a0, s3, enemy_rec::kRareFlag);
        if (a0 != 0) {
            // 0x0030be94: datGetFlag(flag)
            charge(ctx, 4);
            jal(ctx, 0x30BE94u, gen::fn_datGetFlag_0016f190);
            if (v0 != 0) {
                // 0x0030bea4
                charge(ctx, 8);
                a0 = 100;
                jal(ctx, 0x30BEA8u, gen::fn_datCalcRand_002ffbc0);
                v1 = v0 & 0xFF;
                lbu(v0, s3, enemy_rec::kRareChance);
                at = slt(v1, v0);
                if (at != 0) {
                    // 0x0030bec4: drop = the rare item; *rare_out = 1
                    charge(ctx, 3);
                    lhu(s0, s3, enemy_rec::kRareItem);
                    if (s1 != 0) {
                        // 0x0030bed0
                        charge(ctx, 2);
                        v0 = 1;
                        sw(v0, s1, 0);
                    }
                }
            }
        }
    }
    // 0x0030bed8: no rare drop: the common drops
    charge(ctx, 3);
    v0 = s0 & 0xFFFF;
    if (v0 == 0) {
        // 0x0030bee4: s2 = total weight of the four slots (an item >= 5000 counts only while its MT bit is clear)
        charge(ctx, 4);
        s2 = 0;
        s4 = 0;
        for (;;) {
            // 0x0030bf44: loop test
            charge(ctx, 4);
            v0 = s4 & 0xFFFF;
            v0 = slti(v0, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0030bef4: s1 = record + 4 * i; v1 = drops[i].item
            charge(ctx, 6);
            v0 = s4 & 0xFFFF;
            v0 = sll(v0, 2);
            s1 = addu(s3, v0);
            lhu(v1, s1, enemy_rec::kDrops);
            if (v1 != 0) {
                // 0x0030bf0c
                charge(ctx, 3);
                v0 = slti(v1, 5000);
                bool counts = true;
                if (v0 == 0) {
                    // 0x0030bf18: MT_Misc_BitChk(5512 - item) == 0?
                    charge(ctx, 6);
                    v0 = 5512;
                    a0 = subu(v0, v1);
                    jal(ctx, 0x30BF20u, gen::fn_MT_Misc_BitChk_003951d0);
                    counts = v0 == 0;
                }
                if (counts) {
                    // 0x0030bf30: total += weight
                    charge(ctx, 3);
                    lbu(v0, s1, enemy_rec::kDropWeight);
                    v0 = addu(s2, v0);
                    s2 = v0 & 0xFFFF;
                }
            }
            // 0x0030bf3c: ++i
            charge(ctx, 2);
            v0 = addiu(s4, 1);
            s4 = v0 & 0xFFFF;
        }
        // 0x0030bf54: s1 = the roll range: 200, or under flag 3032 the float at 0x7CAF68 (at least 1)
        charge(ctx, 7);
        s1 = 200;
        a0 = 3032;
        jal(ctx, 0x30BF5Cu, gen::fn_datGetFlag_0016f190);
        v1 = 1;
        if (v0 == v1) {
            // 0x0030bf70: the compiled float -> u32 conversion (2^31 split)
            charge(ctx, 7);
            lwc1(f1, gp, gp_off(0x7CAF68u));
            v0 = flt(2147483648.0f);
            mtc1(v0, f0);
            c_le_s(f0, f1);
            if (cond(ctx)) {
                // 0x0030bfa4
                charge(ctx, 6);
                sub_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFFFF;
            } else {
                // 0x0030bf8c
                charge(ctx, 6);
                cvt_w_s(f0, f1);
                mfc1(v1, f0);
                v1 = v1 & 0xFFFF;
            }
            // 0x0030bfbc
            charge(ctx, 3);
            s1 = v1 & 0xFFFF;
            if (s1 == 0) {
                // 0x0030bfc8
                charge(ctx, 1);
                s1 = 1;
            }
        }
        // 0x0030bfcc: a drop at all: datCalcRand(range) < total
        charge(ctx, 3);
        s4 = s2 & 0xFFFF;
        if (i64(s4) > 0) {
            // 0x0030bfd8
            charge(ctx, 7);
            a0 = s1 & 0xFFFF;
            jal(ctx, 0x30BFDCu, gen::fn_datCalcRand_002ffbc0);
            v0 = v0 & 0xFFFF;
            at = slt(v0, s4);
            if (at != 0) {
                // 0x0030bff4: s2 = pick = datCalcRand(total); s5 = running weight; the slot where it passes pick
                charge(ctx, 8);
                a0 = s4;
                jal(ctx, 0x30BFF8u, gen::fn_datCalcRand_002ffbc0);
                s2 = v0 & 0xFFFF;
                s5 = 0;
                s4 = 0;
                for (;;) {
                    // 0x0030c080: loop test
                    charge(ctx, 4);
                    v0 = s4 & 0xFFFF;
                    v0 = slti(v0, 4);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0030c014: s6 = &drops[i].item
                    charge(ctx, 7);
                    v0 = s4 & 0xFFFF;
                    v0 = sll(v0, 2);
                    s1 = addu(s3, v0);
                    s6 = addiu(s1, enemy_rec::kDrops);
                    lhu(v1, s1, enemy_rec::kDrops);
                    if (v1 != 0) {
                        // 0x0030c030
                        charge(ctx, 3);
                        v0 = slti(v1, 5000);
                        bool counts = true;
                        if (v0 == 0) {
                            // 0x0030c03c: MT_Misc_BitChk(5512 - item) == 0?
                            charge(ctx, 6);
                            v0 = 5512;
                            a0 = subu(v0, v1);
                            jal(ctx, 0x30C044u, gen::fn_MT_Misc_BitChk_003951d0);
                            counts = v0 == 0;
                        }
                        if (counts) {
                            // 0x0030c054: running += weight; pick < running: this slot
                            charge(ctx, 6);
                            lbu(v0, s1, enemy_rec::kDropWeight);
                            v0 = addu(s5, v0);
                            s5 = v0 & 0xFFFF;
                            at = slt(s2, s5);
                            if (at != 0) {
                                // 0x0030c06c: drop = drops[i].item
                                charge(ctx, 3);
                                lhu(s0, s6, 0);
                                epilogue();
                                return;
                            }
                        }
                    }
                    // 0x0030c078: ++i
                    charge(ctx, 2);
                    v0 = addiu(s4, 1);
                    s4 = v0 & 0xFFFF;
                }
            }
        }
    }
    epilogue();
}

// 0x0030C0C0 sub_30C0C0 -- 344 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [datGetSkillSection2ForParty](): outside the no-cost mode (sub_17D800), the first of the 32 SKILL.TBL section-2
// records naming the persona sub_1752B0 returns (in u16 +2 or +4) whose partner (the other field) is held by a stock
// slot (sub_174960 / sub_174A90 +2); 0 when none.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void sub_30C0C0_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld,
          hg::lhu, hg::lq, hg::lw, hg::sd, hg::sll, hg::slt, hg::slti, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    auto epilogue = [&] {  // 0x0030c1ec
        charge(ctx, 11);
        ld(ra, sp, 0x70);
        lq(s6, sp, 0x60);
        lq(s5, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x80);
    };
    // 0x0030c0c0: prologue; the no-cost mode?
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x30C0E4u, gen::fn_sub_17D800_0017d800);
    if (v0 == 0) {
        // 0x0030c100: s1 = the persona (sub_1752B0), s5 = the stock size; for (s4 = 0; s4 < 32; ++s4) over the records
        charge(ctx, 10);
        jal(ctx, 0x30C100u, gen::fn_sub_1752B0_001752b0);
        s0 = v0 & 0xFFFF;
        jal(ctx, 0x30C10Cu, gen::fn_sub_175410_00175410);
        s5 = v0 & 0xFFFF;
        s4 = 0;
        s1 = s0 & 0xFFFF;
        for (;;) {
            // 0x0030c1d8: record loop test
            charge(ctx, 4);
            v0 = s4 & 0xFFFF;
            v0 = slti(v0, 32);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0030c128: v0 = &section2[i] (s0 = i * 6); does +2 name the persona?
            charge(ctx, 9);
            lw(a0, gp, gp_off(btl::kSkillSection2Ptr));
            v1 = s4 & 0xFFFF;
            v0 = sll(v1, 1);
            v0 = addu(v0, v1);
            s0 = sll(v0, 1);
            v0 = addu(a0, s0);
            lhu(v1, v0, 2);
            bool named;
            if (s1 == v1) {
                // 0x0030c14c: yes: v1 = the partner (+4)
                charge(ctx, 3);
                lhu(v1, v0, 4);
                named = true;
            } else {
                // 0x0030c158: or +4 (the partner stays +2 in v1)
                charge(ctx, 3);
                lhu(v0, v0, 4);
                named = s1 == v0;
            }
            if (named) {
                // 0x0030c164: s6 = the partner; for (s3 = 0; s3 < stock size; ++s3) a used slot holding it?
                charge(ctx, 4);
                s3 = 0;
                s6 = v1 & 0xFFFF;
                for (;;) {
                    // 0x0030c1c0: slot loop test
                    charge(ctx, 4);
                    v0 = s3 & 0xFFFF;
                    v0 = slt(v0, s5);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0030c174: sub_174960((s16)slot)
                    charge(ctx, 7);
                    s2 = dsll32(s3, 16);
                    s2 = dsra32(s2, 16);
                    a0 = s2;
                    jal(ctx, 0x30C180u, gen::fn_sub_174960_00174960);
                    if (v0 != 0) {
                        // 0x0030c190: sub_174A90(slot)->id == partner?
                        charge(ctx, 6);
                        a0 = s2;
                        jal(ctx, 0x30C194u, gen::fn_sub_174A90_00174a90);
                        lhu(v0, v0, persona::kId);
                        if (v0 == s6) {
                            // 0x0030c1a8: return &section2[i]
                            charge(ctx, 4);
                            lw(v0, gp, gp_off(btl::kSkillSection2Ptr));
                            v0 = addu(v0, s0);
                            epilogue();
                            return;
                        }
                    }
                    // 0x0030c1b8: ++slot
                    charge(ctx, 2);
                    v0 = addiu(s3, 1);
                    s3 = v0 & 0xFFFF;
                }
            }
            // 0x0030c1d0: ++record
            charge(ctx, 2);
            v0 = addiu(s4, 1);
            s4 = v0 & 0xFFFF;
        }
        // 0x0030c1e8: none: return 0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0030c0f4: the no-cost mode: return 0
        charge(ctx, 3);
        v0 = 0;
    }
    epilogue();
}

// 0x0030C220 sub_30C220 -- 128 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [datGetSkillSection2](id): SKILL.TBL section 2 + 6 * (id - 272) (K_Assert unless 272 <= id < 305).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void sub_30C220(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sll,
          hg::slti, hg::sltu, hg::sq;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0030c220: prologue
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    v1 = 0;
    s0 = a0 & 0xFFFF;
    v0 = slti(s0, 272);
    if (v0 == 0) {
        // 0x0030c240
        charge(ctx, 3);
        at = slti(s0, 305);
        if (at != 0) {
            // 0x0030c24c
            charge(ctx, 1);
            v1 = 1;
        }
    }
    // 0x0030c250
    charge(ctx, 4);
    v1 = sltu(0, v1);
    v0 = 1;
    if (v1 != v0) {
        // 0x0030c260
        charge(ctx, 5);
        k_assert(a0, a1, 0x30C26Cu, kDatCalcFile, 5901);
    }
    // 0x0030c274: epilogue
    charge(ctx, 11);
    v1 = addiu(s0, -272);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v1 = sll(v0, 1);
    lw(v0, gp, gp_off(btl::kSkillSection2Ptr));  // gBtlSkillTbl+0x4
    v0 = addu(v0, v1);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030C2A0 sub_30C2A0 -- 248 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [datCalcRollEscape](unit): AICALC formula 7 (+10 with skill 536), clamped to 50..90 (5..90 under flag
// 4889), against datCalcRand(100).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void sub_30C2A0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::sd, hg::slt, hg::slti, hg::sq;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0030c2a0: prologue
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = 7;
    a1 = s1;
    a2 = s1;
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x30C2C8u, gen::fn_datScriptCalc_0030fc40);
    s0 = v0 & 0xFFFF;
    a0 = s1;
    a1 = 536;
    jal(ctx, 0x30C2DCu, gen::fn_datCalcHasSkill_003005e0);
    if (v0 != 0) {
        // 0x0030c2ec
        charge(ctx, 2);
        v0 = addiu(s0, 10);
        s0 = v0 & 0xFFFF;
    }
    // 0x0030c2f4
    charge(ctx, 5);
    a0 = 4889;
    jal(ctx, 0x30C2F8u, gen::fn_datGetFlag_0016f190);
    if (v0 != 0) {
        // 0x0030c33c
        charge(ctx, 4);
        v0 = s0 & 0xFFFF;
        at = slti(v0, 91);
        if (at != 0) {
            // 0x0030c358
            charge(ctx, 3);
            at = slti(v0, 5);
            if (at != 0) {
                // 0x0030c364
                charge(ctx, 1);
                s0 = 5;
            }
        } else {
            // 0x0030c34c
            charge(ctx, 3);
            s0 = 90;
        }
    } else {
        // 0x0030c308
        charge(ctx, 4);
        v0 = s0 & 0xFFFF;
        at = slti(v0, 91);
        if (at != 0) {
            // 0x0030c324
            charge(ctx, 3);
            at = slti(v0, 50);
            if (at != 0) {
                // 0x0030c330
                charge(ctx, 3);
                s0 = 50;
            }
        } else {
            // 0x0030c318
            charge(ctx, 3);
            s0 = 90;
        }
    }
    // 0x0030c368
    charge(ctx, 12);
    a0 = 100;
    jal(ctx, 0x30C36Cu, gen::fn_datCalcRand_002ffbc0);
    v1 = v0 & 0xFFFF;
    v0 = s0 & 0xFFFF;
    v0 = slt(v1, v0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0030C3A0 sub_30C3A0 -- 156 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [datCalcIsEnemyFlag4](unit): EnemyRecord +0 bit 2 of an enemy unit; 0 for a party member.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void sub_30C3A0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lq, hg::lw, hg::sd,
          hg::sll, hg::slti, hg::sq, hg::subu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0030c3a0: prologue
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lhu(v0, a0, dat_unit::kFlags);
    v0 = v0 & dat_unit::kFlagEnemy;
    if (v0 != 0) {
        // 0x0030c3cc
        charge(ctx, 4);
        lhu(v0, s0, dat_unit::kId);
        v0 = slti(v0, enemy_rec::kCount);
        if (v0 == 0) {
            // 0x0030c3dc
            charge(ctx, 5);
            k_assert(a0, a1, 0x30C3E8u, kDatCalcFile, 5965);
        }
        // 0x0030c3f0
        charge(ctx, 10);
        lhu(v1, s0, dat_unit::kId);
        v0 = sll(v1, 5);
        v0 = subu(v0, v1);
        v1 = sll(v0, 1);  // * 62 (EnemyRecord)
        lw(v0, gp, gp_off(btl::kUnitTablePtr));  // gBtlEnemyTbl
        v0 = addu(v0, v1);
        lhu(v0, v0, enemy_rec::kFlags);
        v0 = v0 & 0x4;  // EnemyRecord flag 0x4
        if (v0 == 0) {
            // 0x0030c424
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x0030c418
            charge(ctx, 3);
            v0 = 1;
        }
    } else {
        // 0x0030c3c0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0030c428: epilogue
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0030C440 datCalcRestorePartyAll -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// datCalcRestorePartyAll(): sub_30C490 for party members 1..10.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void datCalcRestorePartyAll(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::sd, hg::slti, hg::sq;
    Gpr v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0030c440: prologue
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 1;
    for (;;) {
        // 0x0030c46c
        charge(ctx, 4);
        v1 = s0 & 0xFFFF;
        v1 = slti(v1, 11);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0030c458
        charge(ctx, 5);
        a0 = s0;
        jal(ctx, 0x30C45Cu, gen::fn_sub_30C490_0030c490);
        v1 = addiu(s0, 1);
        s0 = v1 & 0xFFFF;
    }
    // 0x0030c47c
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x30C490 [datCalcRestorePartyMember](pc): HP and SP set to the maxima, the statuses cleared (sub_16D9D0(pc, -1)).
void sub_30C490(EEContext& ctx, u64 pc) {
    guest::enter(ctx, 30);
    Frame f(ctx, 32, 16, kS0);
    const u64 id = sx16(pc);
    S(ctx, kS0, id);
    S(ctx, kA0, id);
    const u64 hp = jal(ctx, 0x30c4a8, &rg::fn_sub_16C5F0_0016c5f0);
    S(ctx, kA1, sx16(hp));
    S(ctx, kA0, id);
    jal(ctx, 0x30c4bc, &rg::fn_sub_16CF40_0016cf40);
    S(ctx, kA0, id);
    const u64 sp = jal(ctx, 0x30c4c8, &rg::fn_sub_16C670_0016c670);
    S(ctx, kA1, sx16(sp));
    S(ctx, kA0, id);
    jal(ctx, 0x30c4dc, &rg::fn_sub_16CF90_0016cf90);
    S(ctx, kA0, id);
    S(ctx, kA1, ~u64{0});
    jal(ctx, 0x30c4ec, &rg::fn_sub_16D9D0_0016d9d0);
}

// ================================================================================================================
// The rest of the datUnit.c / datCalc.c / datScript.c band
// ================================================================================================================

// 0x002FF540 datUnitEcAddEnemy -- 284 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// datUnitEcAddEnemy(genus, enemy): the first of the genus's six 60-byte unit slots (genus +4) whose id is 0 becomes
// enemy `enemy` (datUnitInit(slot, 1, enemy)) and the genus count (+2) goes up. K_Assert (datUnit.c 100 / 101 / 117)
// unless the genus is an enemy genus (+0 == 1), has room and a slot was found. Returns the slot (the last one looked
// at when none was free). The loop counter lives in $a0, as compiled.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void datUnitEcAddEnemy(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lq,
          hg::lw, hg::sd, hg::sh, hg::sll, hg::slti, hg::sq, hg::subu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002ff540: prologue; s2 = genus, s1 = enemy; K_Assert(genus->kind == enemy)
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    lhu(v1, a0, genus::kKind);
    v0 = genus::kKindEnemy;
    if (v1 != v0) {
        // 0x002ff570
        charge(ctx, 5);
        k_assert(a0, a1, 0x2FF57Cu, kDatUnitFile, 100);
    }
    // 0x002ff584: K_Assert(genus->count < 6)
    charge(ctx, 4);
    lhu(v0, s2, genus::kCount);
    v0 = slti(v0, genus::kMaxEnemies);
    if (v0 == 0) {
        // 0x002ff594
        charge(ctx, 5);
        k_assert(a0, a1, 0x2FF5A0u, kDatUnitFile, 101);
    }
    // 0x002ff5a8: for (i = 0; i < 6; ++i) (a0 = i; s3 = (u16)i stays for the assert after the loop)
    charge(ctx, 3);
    a0 = 0;
    for (;;) {
        // 0x002ff608: loop test
        charge(ctx, 4);
        s3 = a0 & 0xFFFF;
        v0 = slti(s3, genus::kMaxEnemies);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002ff5b4: s0 = &genus->units[i]; a free slot (id 0)?
        charge(ctx, 9);
        v1 = a0 & 0xFFFF;
        v0 = sll(v1, 4);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        lw(v0, s2, genus::kUnits);
        s0 = addu(v0, v1);
        lhu(v0, s0, dat_unit::kId);
        if (v0 == 0) {
            // 0x002ff5d8: datUnitInit(slot, 1, enemy); ++genus->count
            charge(ctx, 10);
            a0 = s0;
            a1 = genus::kKindEnemy;
            a2 = s1;
            jal(ctx, 0x2FF5E4u, gen::fn_datUnitInit_002ff890);
            lhu(v0, s2, genus::kCount);
            v0 = addiu(v0, 1);
            sh(v0, s2, genus::kCount);
            break;
        }
        // 0x002ff600: ++i
        charge(ctx, 2);
        v0 = addiu(a0, 1);
        a0 = v0 & 0xFFFF;
    }
    // 0x002ff618: K_Assert(a slot was free)
    charge(ctx, 3);
    v0 = slti(s3, genus::kMaxEnemies);
    if (v0 == 0) {
        // 0x002ff624
        charge(ctx, 5);
        k_assert(a0, a1, 0x2FF630u, kDatUnitFile, 117);
    }
    // 0x002ff638: return the slot; epilogue
    charge(ctx, 9);
    v0 = s0;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002FFB00 sub_2FFB00 -- 192 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [datCalcUpdatePartyCondition](record): for a unit-like record whose +0 is 0, the party member at
// (*(record + 4)) + 2: sub_16CA90(pc, -1); when sub_16C9F0(pc) is 0 and the condition is 2, 1 or 0,
// sub_16D6B0(pc, 3); returns the condition (sub_16C920) afterwards, or 0 when +0 is set.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: callee frames).
void sub_2FFB00(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lh, hg::lhu, hg::lq, hg::lw, hg::sd,
          hg::si, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002ffb00: prologue; record +0 set: return 0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lhu(v0, a0, 0);
    if (v0 != 0) {
        // 0x002ffba8
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002ffb18: s0 = pc = (s16)(*(record + 4))->id; sub_16CA90(pc, -1); sub_16C9F0(pc)?
        charge(ctx, 13);
        lw(v0, a0, 4);
        lh(v0, v0, dat_unit::kId);
        s0 = v0;
        a0 = s0;
        a1 = si(-1);
        jal(ctx, 0x2FFB2Cu, gen::fn_sub_16CA90_0016ca90);
        a0 = s0;
        jal(ctx, 0x2FFB38u, gen::fn_sub_16C9F0_0016c9f0);
        v0 = v0 & 0xFFFF;
        if (v0 == 0) {
            // 0x002ffb4c: condition 2, 1 or 0 -> sub_16D6B0(pc, 3)
            charge(ctx, 7);
            a0 = s0;
            jal(ctx, 0x2FFB50u, gen::fn_sub_16C920_0016c920);
            v1 = v0 & 0xFFFF;
            v0 = 2;
            bool set3 = v1 == v0;
            if (!set3) {
                // 0x002ffb68
                charge(ctx, 3);
                v0 = 1;
                set3 = v1 == v0;
                if (!set3) {
                    // 0x002ffb74
                    charge(ctx, 2);
                    set3 = v1 == 0;
                    if (!set3) {
                        // 0x002ffb7c
                        charge(ctx, 2);
                    }
                }
            }
            if (set3) {
                // 0x002ffb84
                charge(ctx, 4);
                a0 = s0;
                a1 = 3;
                jal(ctx, 0x2FFB8Cu, gen::fn_sub_16D6B0_0016d6b0);
            }
        }
        // 0x002ffb94: return sub_16C920(pc)
        charge(ctx, 5);
        a0 = s0;
        jal(ctx, 0x2FFB98u, gen::fn_sub_16C920_0016c920);
    }
    // 0x002ffbac: epilogue
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003005A0 sub_3005A0 -- 64 bytes; frame 0x10: ra sp+0x0
// [datCalcGetCondition](unit): a party member's condition (sub_16C920 of the sign-extended id), 0 for an enemy.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void sub_3005A0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lh, hg::lhu, hg::sd;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003005a0: prologue
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lhu(v0, a0, dat_unit::kFlags);
    v0 = v0 & dat_unit::kFlagEnemy;
    if (v0 == 0) {
        // 0x003005c4
        charge(ctx, 3);
        lh(a0, a0, 2);
        jal(ctx, 0x3005C8u, gen::fn_sub_16C920_0016c920);
    } else {
        // 0x003005b8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003005d0: epilogue
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00300700 sub_300700 -- 80 bytes; frame 0x10: ra sp+0x0
// [datCalcHasCounter](unit, id): sub_170760(pc, id) > 0 for a party member (both sign-extended), 0 for an enemy.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void sub_300700(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld, hg::lh, hg::lhu,
          hg::sd, hg::slt;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00300700: prologue
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lhu(v0, a0, dat_unit::kFlags);
    v0 = v0 & dat_unit::kFlagEnemy;
    if (v0 == 0) {
        // 0x00300724
        charge(ctx, 7);
        lh(a0, a0, 2);
        a1 = dsll32(a1, 16);
        a1 = dsra32(a1, 16);
        jal(ctx, 0x300730u, gen::fn_sub_170760_00170760);
        v0 = v0 & 0xFFFF;
        v0 = slt(0, v0);
    } else {
        // 0x00300718
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00300740: epilogue
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00300870 sub_300870 -- 304 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [datCalcCountEquipmentEffect](pc, effect): how many of party member pc's equipment slots 0..2 carry the
// effect byte (K_Assert pc < 11, line 646).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void sub_300870(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld, hg::lq, hg::sd,
          hg::slti, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00300870: prologue
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s0 = a1;
    v0 = s2 & 0xFFFF;
    v0 = slti(v0, 11);
    if (v0 == 0) {
        // 0x003008a0
        charge(ctx, 5);
        k_assert(a0, a1, 0x3008ACu, kDatCalcFile, 646);
    }
    // 0x003008b4
    charge(ctx, 16);
    s1 = 0;
    s3 = dsll32(s2, 16);
    s3 = dsra32(s3, 16);
    s0 = s0 & 0xFFFF;
    a0 = s3;
    a1 = 0;
    jal(ctx, 0x3008CCu, gen::fn_datGetEquipmentIdx_0016cb80);
    a1 = dsll32(v0, 16);
    a1 = dsra32(a1, 16);
    a0 = s3;
    jal(ctx, 0x3008E0u, gen::fn_sub_16F900_0016f900);
    v0 = v0 & 0xFF;
    if (s0 == v0) {
        // 0x003008f4
        charge(ctx, 2);
        v0 = addiu(s1, 1);
        s1 = v0 & 0xFFFF;
    }
    // 0x003008fc
    charge(ctx, 14);
    s3 = dsll32(s2, 16);
    s3 = dsra32(s3, 16);
    a0 = s3;
    a1 = 1;
    jal(ctx, 0x30090Cu, gen::fn_datGetEquipmentIdx_0016cb80);
    a1 = dsll32(v0, 16);
    a1 = dsra32(a1, 16);
    a0 = s3;
    jal(ctx, 0x300920u, gen::fn_sub_16F900_0016f900);
    v0 = v0 & 0xFF;
    if (s0 == v0) {
        // 0x00300934
        charge(ctx, 2);
        v0 = addiu(s1, 1);
        s1 = v0 & 0xFFFF;
    }
    // 0x0030093c
    charge(ctx, 14);
    s2 = dsll32(s2, 16);
    s2 = dsra32(s2, 16);
    a0 = s2;
    a1 = 2;
    jal(ctx, 0x30094Cu, gen::fn_datGetEquipmentIdx_0016cb80);
    a1 = dsll32(v0, 16);
    a1 = dsra32(a1, 16);
    a0 = s2;
    jal(ctx, 0x300960u, gen::fn_sub_16F900_0016f900);
    v0 = v0 & 0xFF;
    if (s0 == v0) {
        // 0x00300974
        charge(ctx, 2);
        v0 = addiu(s1, 1);
        s1 = v0 & 0xFFFF;
    }
    // 0x0030097c: epilogue
    charge(ctx, 9);
    v0 = s1;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00300E90 sub_300E90 -- 200 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [datCalcIsBlockedByWall](unit, skill): 1 when the unit's wall buff stops the skill's element (taken without a user,
// datCalcGetSkillElement(0, skill)): element bits 1..3 against slot 17, the others (not bit 8, not -1 / 16..18)
// against slot 18. Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void sub_300E90(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::i64, hg::jal, hg::ld, hg::lq,
          hg::sd, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00300e90: prologue; s0 = unit; v0 = datCalcGetElementBit(datCalcGetSkillElement(0, skill))
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 0;
    jal(ctx, 0x300EA4u, gen::fn_datCalcGetSkillElement_003082f0);
    a0 = dsll32(v0, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x300EB4u, gen::fn_datCalcGetElementBit_003080c0);
    v1 = 0xE0000;
    v1 = v1 | 0x1;
    v1 = v0 & v1;
    bool blocked = false;
    if (v1 == 0) {
        // 0x00300ed0: not -1 / 16..18: bits 1..3 -> wall slot 17, others (not bit 8) -> slot 18
        charge(ctx, 3);
        v1 = v0 & 0xE;
        if (v1 == 0) {
            // 0x00300f08
            charge(ctx, 3);
            v0 = v0 & 0x100;
            if (v0 == 0) {
                // 0x00300f14: datCalcGetEffectState(unit, 18) > 0?
                charge(ctx, 8);
                a0 = s0;
                a1 = 18;
                jal(ctx, 0x300F1Cu, gen::fn_datCalcGetEffectState_00301750);
                v0 = dsll32(v0, 24);
                v0 = dsra32(v0, 24);
                if (i64(v0) > 0) {
                    // 0x00300f34: return 1
                    charge(ctx, 3);
                    v0 = 1;
                    blocked = true;
                }
            }
        } else {
            // 0x00300edc: datCalcGetEffectState(unit, 17) > 0?
            charge(ctx, 8);
            a0 = s0;
            a1 = 17;
            jal(ctx, 0x300EE4u, gen::fn_datCalcGetEffectState_00301750);
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
            if (i64(v0) > 0) {
                // 0x00300efc: return 1
                charge(ctx, 3);
                v0 = 1;
                blocked = true;
            }
        }
    }
    if (!blocked) {
        // 0x00300f40: return 0
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x00300f44: epilogue
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00301CA0 sub_301CA0 -- 1752 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [datCalcCheckEffectMask](unit, mask): for the first set bit of a sub_302380 mask, whether its change is
// already in effect: bits 0..9 slot 0..4 raised / lowered, 10 / 11 / 16 / 17 the flag bits 19 / 20 / 17 / 18 of +0x14,
// 14 / 15 / 18..26 slots 5, 6, 13..16, 7..11 set at all; bit 12: 1 when none of slots 0..4 is raised, bit 13: 1 when
// none of 0..4 is lowered and none of the walls 13..16 raised. 0 for mask 0, and K_Assert (line 1442) for a mask
// without any of these bits.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void sub_301CA0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::i64, hg::jal, hg::ld, hg::lq,
          hg::lw, hg::sd, hg::slt, hg::sltu, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00301ca0: prologue
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    if (a1 != 0) {
        // 0x00301cc4
        charge(ctx, 3);
        v0 = a1 & 0x1;
        if (v0 == 0) {
            // 0x00301cf0
            charge(ctx, 3);
            v0 = a1 & 0x2;
            if (v0 == 0) {
                // 0x00301d1c
                charge(ctx, 3);
                v0 = a1 & 0x4;
                if (v0 == 0) {
                    // 0x00301d48
                    charge(ctx, 3);
                    v0 = a1 & 0x8;
                    if (v0 == 0) {
                        // 0x00301d74
                        charge(ctx, 3);
                        v0 = a1 & 0x10;
                        if (v0 == 0) {
                            // 0x00301da0
                            charge(ctx, 3);
                            v0 = a1 & 0x20;
                            if (v0 == 0) {
                                // 0x00301dcc
                                charge(ctx, 3);
                                v0 = a1 & 0x40;
                                if (v0 == 0) {
                                    // 0x00301df8
                                    charge(ctx, 3);
                                    v0 = a1 & 0x80;
                                    if (v0 == 0) {
                                        // 0x00301e24
                                        charge(ctx, 3);
                                        v0 = a1 & 0x100;
                                        if (v0 == 0) {
                                            // 0x00301e50
                                            charge(ctx, 3);
                                            v0 = a1 & 0x200;
                                            if (v0 == 0) {
                                                // 0x00301e7c
                                                charge(ctx, 3);
                                                v0 = a1 & 0x400;
                                                if (v0 == 0) {
                                                    // 0x00301eac
                                                    charge(ctx, 3);
                                                    v0 = a1 & 0x800;
                                                    if (v0 == 0) {
                                                        // 0x00301edc
                                                        charge(ctx, 3);
                                                        v0 = a1 & 0x4000;
                                                        if (v0 == 0) {
                                                            // 0x00301f08
                                                            charge(ctx, 3);
                                                            v0 = a1 & 0x8000;
                                                            if (v0 == 0) {
                                                                // 0x00301f34
                                                                charge(ctx, 4);
                                                                v0 = 0x10000;
                                                                v0 = a1 & v0;
                                                                if (v0 == 0) {
                                                                    // 0x00301f68
                                                                    charge(ctx, 4);
                                                                    v0 = 0x20000;
                                                                    v0 = a1 & v0;
                                                                    if (v0 == 0) {
                                                                        // 0x00301f9c
                                                                        charge(ctx, 4);
                                                                        v0 = 0x40000;
                                                                        v0 = a1 & v0;
                                                                        if (v0 == 0) {
                                                                            // 0x00301fcc
                                                                            charge(ctx, 4);
                                                                            v0 = 0x80000;
                                                                            v0 = a1 & v0;
                                                                            if (v0 == 0) {
                                                                                // 0x00301ffc
                                                                                charge(ctx, 4);
                                                                                v0 = 0x100000;
                                                                                v0 = a1 & v0;
                                                                                if (v0 == 0) {
                                                                                    // 0x0030202c
                                                                                    charge(ctx, 4);
                                                                                    v0 = 0x200000;
                                                                                    v0 = a1 & v0;
                                                                                    if (v0 == 0) {
                                                                                        // 0x0030205c
                                                                                        charge(ctx, 4);
                                                                                        v0 = 0x400000;
                                                                                        v0 = a1 & v0;
                                                                                        if (v0 == 0) {
                                                                                            // 0x0030208c
                                                                                            charge(ctx, 4);
                                                                                            v0 = 0x800000;
                                                                                            v0 = a1 & v0;
                                                                                            if (v0 == 0) {
                                                                                                // 0x003020bc
                                                                                                charge(ctx, 4);
                                                                                                v0 = 0x1000000;
                                                                                                v0 = a1 & v0;
                                                                                                if (v0 == 0) {
                                                                                                    // 0x003020ec
                                                                                                    charge(ctx, 4);
                                                                                                    v0 = 0x2000000;
                                                                                                    v0 = a1 & v0;
                                                                                                    if (v0 == 0) {
                                                                                                        // 0x0030211c
                                                                                                        charge(ctx, 4);
                                                                                                        v0 = 0x4000000;
                                                                                                        v0 = a1 & v0;
                                                                                                        if (v0 == 0) {
                                                                                                            // 0x0030214c
                                                                                                            charge(ctx, 3);
                                                                                                            v0 = a1 & 0x1000;
                                                                                                            if (v0 == 0) {
                                                                                                                // 0x0030220c
                                                                                                                charge(ctx, 3);
                                                                                                                v0 = a1 & 0x2000;
                                                                                                                if (v0 == 0) {
                                                                                                                    // 0x0030234c
                                                                                                                    charge(ctx, 6);
                                                                                                                    k_assert(a0, a1, 0x302358u, kDatCalcFile, 1442);
                                                                                                                    v0 = 0;
                                                                                                                } else {
                                                                                                                    // 0x00302218
                                                                                                                    charge(ctx, 7);
                                                                                                                    a1 = 0;
                                                                                                                    jal(ctx, 0x30221Cu, gen::fn_datCalcGetEffectLevel_00300f60);
                                                                                                                    v0 = dsll32(v0, 24);
                                                                                                                    v0 = dsra32(v0, 24);
                                                                                                                    if (i64(v0) >= 0) {
                                                                                                                        // 0x00302234
                                                                                                                        charge(ctx, 8);
                                                                                                                        a0 = s0;
                                                                                                                        a1 = 1;
                                                                                                                        jal(ctx, 0x30223Cu, gen::fn_datCalcGetEffectLevel_00300f60);
                                                                                                                        v0 = dsll32(v0, 24);
                                                                                                                        v0 = dsra32(v0, 24);
                                                                                                                        if (i64(v0) < 0) {
                                                                                                                            goto L_00302334;
                                                                                                                        }
                                                                                                                        // 0x00302254
                                                                                                                        charge(ctx, 8);
                                                                                                                        a0 = s0;
                                                                                                                        a1 = 2;
                                                                                                                        jal(ctx, 0x30225Cu, gen::fn_datCalcGetEffectLevel_00300f60);
                                                                                                                        v0 = dsll32(v0, 24);
                                                                                                                        v0 = dsra32(v0, 24);
                                                                                                                        if (i64(v0) < 0) {
                                                                                                                            goto L_00302334;
                                                                                                                        }
                                                                                                                        // 0x00302274
                                                                                                                        charge(ctx, 8);
                                                                                                                        a0 = s0;
                                                                                                                        a1 = 3;
                                                                                                                        jal(ctx, 0x30227Cu, gen::fn_datCalcGetEffectLevel_00300f60);
                                                                                                                        v0 = dsll32(v0, 24);
                                                                                                                        v0 = dsra32(v0, 24);
                                                                                                                        if (i64(v0) < 0) {
                                                                                                                            goto L_00302334;
                                                                                                                        }
                                                                                                                        // 0x00302294
                                                                                                                        charge(ctx, 8);
                                                                                                                        a0 = s0;
                                                                                                                        a1 = 4;
                                                                                                                        jal(ctx, 0x30229Cu, gen::fn_datCalcGetEffectLevel_00300f60);
                                                                                                                        v0 = dsll32(v0, 24);
                                                                                                                        v0 = dsra32(v0, 24);
                                                                                                                        if (i64(v0) < 0) {
                                                                                                                            goto L_00302334;
                                                                                                                        }
                                                                                                                        // 0x003022b4
                                                                                                                        charge(ctx, 8);
                                                                                                                        a0 = s0;
                                                                                                                        a1 = 13;
                                                                                                                        jal(ctx, 0x3022BCu, gen::fn_datCalcGetEffectLevel_00300f60);
                                                                                                                        v0 = dsll32(v0, 24);
                                                                                                                        v0 = dsra32(v0, 24);
                                                                                                                        if (i64(v0) > 0) {
                                                                                                                            goto L_00302334;
                                                                                                                        }
                                                                                                                        // 0x003022d4
                                                                                                                        charge(ctx, 8);
                                                                                                                        a0 = s0;
                                                                                                                        a1 = 14;
                                                                                                                        jal(ctx, 0x3022DCu, gen::fn_datCalcGetEffectLevel_00300f60);
                                                                                                                        v0 = dsll32(v0, 24);
                                                                                                                        v0 = dsra32(v0, 24);
                                                                                                                        if (i64(v0) > 0) {
                                                                                                                            goto L_00302334;
                                                                                                                        }
                                                                                                                        // 0x003022f4
                                                                                                                        charge(ctx, 8);
                                                                                                                        a0 = s0;
                                                                                                                        a1 = 15;
                                                                                                                        jal(ctx, 0x3022FCu, gen::fn_datCalcGetEffectLevel_00300f60);
                                                                                                                        v0 = dsll32(v0, 24);
                                                                                                                        v0 = dsra32(v0, 24);
                                                                                                                        if (i64(v0) > 0) {
                                                                                                                            goto L_00302334;
                                                                                                                        }
                                                                                                                        // 0x00302314
                                                                                                                        charge(ctx, 8);
                                                                                                                        a0 = s0;
                                                                                                                        a1 = 16;
                                                                                                                        jal(ctx, 0x30231Cu, gen::fn_datCalcGetEffectLevel_00300f60);
                                                                                                                        v0 = dsll32(v0, 24);
                                                                                                                        v0 = dsra32(v0, 24);
                                                                                                                        if (i64(v0) > 0) {
                                                                                                                            goto L_00302334;
                                                                                                                        }
                                                                                                                        // 0x00302340
                                                                                                                        charge(ctx, 3);
                                                                                                                        v0 = 1;
                                                                                                                        // 0x00302364: epilogue
                                                                                                                        charge(ctx, 5);
                                                                                                                        ld(ra, sp, 0x10);
                                                                                                                        lq(s0, sp, 0x0);
                                                                                                                        sp = addiu(sp, 0x20);
                                                                                                                        return;
                                                                                                                    }
                                                                                                                L_00302334:
                                                                                                                    charge(ctx, 3);
                                                                                                                    v0 = 0;
                                                                                                                }
                                                                                                            } else {
                                                                                                                // 0x00302158
                                                                                                                charge(ctx, 7);
                                                                                                                a1 = 0;
                                                                                                                jal(ctx, 0x30215Cu, gen::fn_datCalcGetEffectLevel_00300f60);
                                                                                                                v0 = dsll32(v0, 24);
                                                                                                                v0 = dsra32(v0, 24);
                                                                                                                if (i64(v0) <= 0) {
                                                                                                                    // 0x00302174
                                                                                                                    charge(ctx, 8);
                                                                                                                    a0 = s0;
                                                                                                                    a1 = 1;
                                                                                                                    jal(ctx, 0x30217Cu, gen::fn_datCalcGetEffectLevel_00300f60);
                                                                                                                    v0 = dsll32(v0, 24);
                                                                                                                    v0 = dsra32(v0, 24);
                                                                                                                    if (i64(v0) > 0) {
                                                                                                                        goto L_003021f4;
                                                                                                                    }
                                                                                                                    // 0x00302194
                                                                                                                    charge(ctx, 8);
                                                                                                                    a0 = s0;
                                                                                                                    a1 = 2;
                                                                                                                    jal(ctx, 0x30219Cu, gen::fn_datCalcGetEffectLevel_00300f60);
                                                                                                                    v0 = dsll32(v0, 24);
                                                                                                                    v0 = dsra32(v0, 24);
                                                                                                                    if (i64(v0) > 0) {
                                                                                                                        goto L_003021f4;
                                                                                                                    }
                                                                                                                    // 0x003021b4
                                                                                                                    charge(ctx, 8);
                                                                                                                    a0 = s0;
                                                                                                                    a1 = 3;
                                                                                                                    jal(ctx, 0x3021BCu, gen::fn_datCalcGetEffectLevel_00300f60);
                                                                                                                    v0 = dsll32(v0, 24);
                                                                                                                    v0 = dsra32(v0, 24);
                                                                                                                    if (i64(v0) > 0) {
                                                                                                                        goto L_003021f4;
                                                                                                                    }
                                                                                                                    // 0x003021d4
                                                                                                                    charge(ctx, 8);
                                                                                                                    a0 = s0;
                                                                                                                    a1 = 4;
                                                                                                                    jal(ctx, 0x3021DCu, gen::fn_datCalcGetEffectLevel_00300f60);
                                                                                                                    v0 = dsll32(v0, 24);
                                                                                                                    v0 = dsra32(v0, 24);
                                                                                                                    if (i64(v0) > 0) {
                                                                                                                        goto L_003021f4;
                                                                                                                    }
                                                                                                                    // 0x00302200
                                                                                                                    charge(ctx, 3);
                                                                                                                    v0 = 1;
                                                                                                                    // 0x00302364: epilogue
                                                                                                                    charge(ctx, 5);
                                                                                                                    ld(ra, sp, 0x10);
                                                                                                                    lq(s0, sp, 0x0);
                                                                                                                    sp = addiu(sp, 0x20);
                                                                                                                    return;
                                                                                                                }
                                                                                                            L_003021f4:
                                                                                                                charge(ctx, 3);
                                                                                                                v0 = 0;
                                                                                                            }
                                                                                                        } else {
                                                                                                            // 0x0030212c
                                                                                                            charge(ctx, 8);
                                                                                                            a1 = 11;
                                                                                                            jal(ctx, 0x302130u, gen::fn_datCalcGetEffectLevel_00300f60);
                                                                                                            v0 = dsll32(v0, 24);
                                                                                                            v0 = dsra32(v0, 24);
                                                                                                            v0 = sltu(0, v0);
                                                                                                        }
                                                                                                    } else {
                                                                                                        // 0x003020fc
                                                                                                        charge(ctx, 8);
                                                                                                        a1 = 10;
                                                                                                        jal(ctx, 0x302100u, gen::fn_datCalcGetEffectLevel_00300f60);
                                                                                                        v0 = dsll32(v0, 24);
                                                                                                        v0 = dsra32(v0, 24);
                                                                                                        v0 = sltu(0, v0);
                                                                                                    }
                                                                                                } else {
                                                                                                    // 0x003020cc
                                                                                                    charge(ctx, 8);
                                                                                                    a1 = 9;
                                                                                                    jal(ctx, 0x3020D0u, gen::fn_datCalcGetEffectLevel_00300f60);
                                                                                                    v0 = dsll32(v0, 24);
                                                                                                    v0 = dsra32(v0, 24);
                                                                                                    v0 = sltu(0, v0);
                                                                                                }
                                                                                            } else {
                                                                                                // 0x0030209c
                                                                                                charge(ctx, 8);
                                                                                                a1 = 8;
                                                                                                jal(ctx, 0x3020A0u, gen::fn_datCalcGetEffectLevel_00300f60);
                                                                                                v0 = dsll32(v0, 24);
                                                                                                v0 = dsra32(v0, 24);
                                                                                                v0 = sltu(0, v0);
                                                                                            }
                                                                                        } else {
                                                                                            // 0x0030206c
                                                                                            charge(ctx, 8);
                                                                                            a1 = 7;
                                                                                            jal(ctx, 0x302070u, gen::fn_datCalcGetEffectLevel_00300f60);
                                                                                            v0 = dsll32(v0, 24);
                                                                                            v0 = dsra32(v0, 24);
                                                                                            v0 = sltu(0, v0);
                                                                                        }
                                                                                    } else {
                                                                                        // 0x0030203c
                                                                                        charge(ctx, 8);
                                                                                        a1 = 16;
                                                                                        jal(ctx, 0x302040u, gen::fn_datCalcGetEffectLevel_00300f60);
                                                                                        v0 = dsll32(v0, 24);
                                                                                        v0 = dsra32(v0, 24);
                                                                                        v0 = sltu(0, v0);
                                                                                    }
                                                                                } else {
                                                                                    // 0x0030200c
                                                                                    charge(ctx, 8);
                                                                                    a1 = 15;
                                                                                    jal(ctx, 0x302010u, gen::fn_datCalcGetEffectLevel_00300f60);
                                                                                    v0 = dsll32(v0, 24);
                                                                                    v0 = dsra32(v0, 24);
                                                                                    v0 = sltu(0, v0);
                                                                                }
                                                                            } else {
                                                                                // 0x00301fdc
                                                                                charge(ctx, 8);
                                                                                a1 = 14;
                                                                                jal(ctx, 0x301FE0u, gen::fn_datCalcGetEffectLevel_00300f60);
                                                                                v0 = dsll32(v0, 24);
                                                                                v0 = dsra32(v0, 24);
                                                                                v0 = sltu(0, v0);
                                                                            }
                                                                        } else {
                                                                            // 0x00301fac
                                                                            charge(ctx, 8);
                                                                            a1 = 13;
                                                                            jal(ctx, 0x301FB0u, gen::fn_datCalcGetEffectLevel_00300f60);
                                                                            v0 = dsll32(v0, 24);
                                                                            v0 = dsra32(v0, 24);
                                                                            v0 = sltu(0, v0);
                                                                        }
                                                                    } else {
                                                                        // 0x00301f78
                                                                        charge(ctx, 9);
                                                                        lw(v1, s0, dat_unit::kEffectFlags);
                                                                        v0 = 0x40000;
                                                                        v0 = v1 & v0;
                                                                        v0 = sltu(0, v0);
                                                                        v0 = dsll32(v0, 24);
                                                                        v0 = dsra32(v0, 24);
                                                                        v0 = sltu(0, v0);
                                                                    }
                                                                } else {
                                                                    // 0x00301f44
                                                                    charge(ctx, 9);
                                                                    lw(v1, s0, dat_unit::kEffectFlags);
                                                                    v0 = 0x20000;
                                                                    v0 = v1 & v0;
                                                                    v0 = sltu(0, v0);
                                                                    v0 = dsll32(v0, 24);
                                                                    v0 = dsra32(v0, 24);
                                                                    v0 = sltu(0, v0);
                                                                }
                                                            } else {
                                                                // 0x00301f14
                                                                charge(ctx, 8);
                                                                a1 = 6;
                                                                jal(ctx, 0x301F18u, gen::fn_datCalcGetEffectLevel_00300f60);
                                                                v0 = dsll32(v0, 24);
                                                                v0 = dsra32(v0, 24);
                                                                v0 = sltu(0, v0);
                                                            }
                                                        } else {
                                                            // 0x00301ee8
                                                            charge(ctx, 8);
                                                            a1 = 5;
                                                            jal(ctx, 0x301EECu, gen::fn_datCalcGetEffectLevel_00300f60);
                                                            v0 = dsll32(v0, 24);
                                                            v0 = dsra32(v0, 24);
                                                            v0 = sltu(0, v0);
                                                        }
                                                    } else {
                                                        // 0x00301eb8
                                                        charge(ctx, 9);
                                                        lw(v1, s0, dat_unit::kEffectFlags);
                                                        v0 = 0x100000;
                                                        v0 = v1 & v0;
                                                        v0 = sltu(0, v0);
                                                        v0 = dsll32(v0, 24);
                                                        v0 = dsra32(v0, 24);
                                                        v0 = sltu(0, v0);
                                                    }
                                                } else {
                                                    // 0x00301e88
                                                    charge(ctx, 9);
                                                    lw(v1, s0, dat_unit::kEffectFlags);
                                                    v0 = 0x80000;
                                                    v0 = v1 & v0;
                                                    v0 = sltu(0, v0);
                                                    v0 = dsll32(v0, 24);
                                                    v0 = dsra32(v0, 24);
                                                    v0 = sltu(0, v0);
                                                }
                                            } else {
                                                // 0x00301e5c
                                                charge(ctx, 8);
                                                a1 = 4;
                                                jal(ctx, 0x301E60u, gen::fn_datCalcGetEffectLevel_00300f60);
                                                v0 = dsll32(v0, 24);
                                                v0 = dsra32(v0, 24);
                                                v0 = slt(v0, 0);
                                            }
                                        } else {
                                            // 0x00301e30
                                            charge(ctx, 8);
                                            a1 = 4;
                                            jal(ctx, 0x301E34u, gen::fn_datCalcGetEffectLevel_00300f60);
                                            v0 = dsll32(v0, 24);
                                            v0 = dsra32(v0, 24);
                                            v0 = slt(0, v0);
                                        }
                                    } else {
                                        // 0x00301e04
                                        charge(ctx, 8);
                                        a1 = 3;
                                        jal(ctx, 0x301E08u, gen::fn_datCalcGetEffectLevel_00300f60);
                                        v0 = dsll32(v0, 24);
                                        v0 = dsra32(v0, 24);
                                        v0 = slt(v0, 0);
                                    }
                                } else {
                                    // 0x00301dd8
                                    charge(ctx, 8);
                                    a1 = 3;
                                    jal(ctx, 0x301DDCu, gen::fn_datCalcGetEffectLevel_00300f60);
                                    v0 = dsll32(v0, 24);
                                    v0 = dsra32(v0, 24);
                                    v0 = slt(0, v0);
                                }
                            } else {
                                // 0x00301dac
                                charge(ctx, 8);
                                a1 = 2;
                                jal(ctx, 0x301DB0u, gen::fn_datCalcGetEffectLevel_00300f60);
                                v0 = dsll32(v0, 24);
                                v0 = dsra32(v0, 24);
                                v0 = slt(v0, 0);
                            }
                        } else {
                            // 0x00301d80
                            charge(ctx, 8);
                            a1 = 2;
                            jal(ctx, 0x301D84u, gen::fn_datCalcGetEffectLevel_00300f60);
                            v0 = dsll32(v0, 24);
                            v0 = dsra32(v0, 24);
                            v0 = slt(0, v0);
                        }
                    } else {
                        // 0x00301d54
                        charge(ctx, 8);
                        a1 = 1;
                        jal(ctx, 0x301D58u, gen::fn_datCalcGetEffectLevel_00300f60);
                        v0 = dsll32(v0, 24);
                        v0 = dsra32(v0, 24);
                        v0 = slt(v0, 0);
                    }
                } else {
                    // 0x00301d28
                    charge(ctx, 8);
                    a1 = 1;
                    jal(ctx, 0x301D2Cu, gen::fn_datCalcGetEffectLevel_00300f60);
                    v0 = dsll32(v0, 24);
                    v0 = dsra32(v0, 24);
                    v0 = slt(0, v0);
                }
            } else {
                // 0x00301cfc
                charge(ctx, 8);
                a1 = 0;
                jal(ctx, 0x301D00u, gen::fn_datCalcGetEffectLevel_00300f60);
                v0 = dsll32(v0, 24);
                v0 = dsra32(v0, 24);
                v0 = slt(v0, 0);
            }
        } else {
            // 0x00301cd0
            charge(ctx, 8);
            a1 = 0;
            jal(ctx, 0x301CD4u, gen::fn_datCalcGetEffectLevel_00300f60);
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
            v0 = slt(0, v0);
        }
    } else {
        // 0x00301cb8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00302364: epilogue
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// The datScript COMM handlers 0x30FDC0 / 0x3111C0 / 0x3112E0 are replaced by the script_comm_a slice
// (game/src/script/comm_a.cpp, COMM indices 50 / 48 / 147); test_battle_rest.cpp still pairs their shims.

}  // namespace p3fes::game

// --- the recompiled program's entry points ---------------------------------------------------------------------
// Arguments are the whole 64-bit registers (the originals move them into s-registers with daddu); results go to
// $v0 as the 64-bit register value the original leaves. The void functions leave $v0 as their bodies left it.
namespace p3fes::recomp_gen {
using namespace p3fes::game;
namespace {
u64 a(const p3fes::EEContext& ctx, unsigned r) { return ee::core::gpr64(ctx, r); }
void v0(p3fes::EEContext& ctx, u64 v) { ee::core::set_gpr64(ctx, GPR_V0, v); }
constexpr unsigned A0 = GPR_A0;
}  // namespace
void fn_sub_30BC20_0030bc20(p3fes::EEContext& ctx) { v0(ctx, sub_30BC20(ctx, a(ctx, A0))); }
void fn_sub_30C490_0030c490(p3fes::EEContext& ctx) { sub_30C490(ctx, a(ctx, A0)); }
}  // namespace p3fes::recomp_gen
