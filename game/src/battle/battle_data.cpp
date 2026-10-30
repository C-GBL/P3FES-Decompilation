// The battle data layer (game/include/p3fes/game/battle_data.h), hand-decompiled from SLUS_216.21
// (docs/ANALYSIS/21_battle.md sections 1.3, 1.4, 2, 3 and 5): datUnit.c genus slots and unit init, the datCalc.c
// level / stat / max-HP/SP / buff-slot / RNG functions, the datScript.c context leaves, the btl root flag and
// packet helpers, the btlAction and turn-order lists, the btlMain / btlAction state-table drivers, the
// g_data / datPersona.c record lookups and the k_encount.c floor-layout readers. Phase 5: each replaces
// the recompiled body listed in game/replaced.txt; tests/game/test_battle_data.cpp runs each against its
// __recomp body.
//
// Virtual time per ADR-0013: guest::enter / charge / backedge mirror the `ctx.cycles += N` blocks and the
// back-edge checks of the generated bodies (recomp/generated/fn_*.cpp) on the executed path; a charge sits
// at the start of its block, before any call the block makes, so callees see the same cycle counter.
// K_Assert (sub_19D3F0) is `jr $ra` in retail: a failed check continues with the same loads and stays a
// guest::call for its check point and two cycles. Calls to functions that are still recompiled go through
// their generated entry points with the argument registers the original sets; indirect calls (`jalr`)
// put the target in $v0 first, as the original's `lw v0, ...; jalr v0` does, so a void callee leaves the
// same $v0.
//
// Faithfulness audit (2026-10-21, tools/ours/audit): 68 of the 75 functions here are now p3fes_handgen's register-
// faithful bodies (their hand versions differed from the original: frame/spills 35, scratch GPRs 18, $v0 9, faults
// only 4, callee frames 2); each keeps the notes of its earlier hand version above it. The others are the hand-
// written versions this header describes.
//
// Readability pass (read_battle, 2026-10-21): the 68 generated bodies keep every statement, charge, check point and
// call of p3fes_handgen's output in the same order on every path; on top of it they name what they touch (record
// offsets and guest addresses from battle_view.h: `lhu(v0, a0, dat_unit::kFlags)`, `lw(v1, gp, gp_off(btl::kUnitTablePtr))`,
// `k_assert(a0, a1, pc, kDatCalcFile, line)` for the four-statement K_Assert call), say what each block does, and
// replace the generator's gotos by if / else / break where every path keeps its statements (a shared epilogue becomes
// one `epilogue` lambda). Each function's comment gives its role and, for a `sub_` name, a proposed name in brackets.
#include "p3fes/game/battle_data.h"

#include "p3fes/ee/core.h"
#include "p3fes/ee/fpu.h"
#include "p3fes/ee/hilo.h"
#include "p3fes/game/battle.h"
#include "p3fes/game/guest.h"
#include "p3fes/game/ui2.h"

#include <cstddef>
#include "p3fes/game/battle_view.h"
#include "p3fes/game/hg_cpu.h"

// Callees of the register-faithful bodies (p3fes_handgen), through their recomp_gen entry points.
namespace p3fes::recomp_gen {
void fn_datCalcGetEffectLevel_00300f60(p3fes::EEContext&);
void fn_datCalcIsDead_0030b5a0(p3fes::EEContext&);
void fn_sub_170E40_00170e40(p3fes::EEContext&);
void fn_datCalcClearEffect_00301540(p3fes::EEContext&);
void fn_datCalcCountEquipmentWithEffect_003009a0(p3fes::EEContext&);
void fn_datCalcGetLevel_002ffcc0(p3fes::EEContext&);
void fn_datCalcGetMaxHp_002ffdf0(p3fes::EEContext&);
void fn_datCalcGetMaxSp_00300100(p3fes::EEContext&);
void fn_datCalcHasSkill_003005e0(p3fes::EEContext&);
void fn_datCalcSetEffectLevel_00301030(p3fes::EEContext&);
void fn_datGetEquipmentIdx_0016cb80(p3fes::EEContext&);
void fn_datPersonaGetByPcId_00174800(p3fes::EEContext&);
void fn_sub_16CC00_0016cc00(p3fes::EEContext&);
void fn_sub_16CCB0_0016ccb0(p3fes::EEContext&);
void fn_sub_16F630_0016f630(p3fes::EEContext&);
void fn_sub_16F900_0016f900(p3fes::EEContext&);
void fn_sub_1732F0_001732f0(p3fes::EEContext&);
void fn_sub_173510_00173510(p3fes::EEContext&);
void fn_sub_1738D0_001738d0(p3fes::EEContext&);
void fn_sub_174A90_00174a90(p3fes::EEContext&);
void fn_sub_175410_00175410(p3fes::EEContext&);
void fn_sub_29A250_0029a250(p3fes::EEContext&);
void fn_sub_300B60_00300b60(p3fes::EEContext&);
void fn_sub_301150_00301150(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::recomp_gen {
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);  // K_Assert(file, line)
void fn_sub_357FD0_00357fd0(p3fes::EEContext&);  // effMiscRand(0)
void fn_datCalcGetSkillSlotCount_00308ba0(p3fes::EEContext&);  // datCalcGetSkillSlotCount (8)
void fn_datCalcGetSkillList_00308bb0(p3fes::EEContext&);  // datCalcGetSkillList(unit)
void fn_sub_306D90_00306d90(p3fes::EEContext&);  // the affinity word decoder (a0 = 0, a1 = word)
void fn_sub_173B00_00173b00(p3fes::EEContext&);  // persona stat bonus 1 (datPersonaGetBonusStat)
void fn_sub_173C00_00173c00(p3fes::EEContext&);  // persona stat bonus 2
void fn_sub_173C60_00173c60(p3fes::EEContext&);  // persona stat bonus 3 (equipment)
void fn_sub_2BFC90_002bfc90(p3fes::EEContext&);  // party-present check of btlMainCheckBattleEnd
void fn_sub_2FD660_002fd660(p3fes::EEContext&);  // the boss end rule
void fn_datCalcGetStat_00300c90(p3fes::EEContext&);  // datCalcGetStat (this file; called through its entry for $v0)
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

using namespace bview;  // hi / lo / gp_off / flt / k_assert and the record offsets (battle_view.h)

namespace {

using namespace btl;

// The three state drivers (btlActionSetState, btlMainSetState, btlMainUpdateState) call big recompiled state
// functions through `jalr`, so their 16-byte frame is live while those run: `addiu sp, sp, -16; sd ra, 0(sp)`
// on entry, `ld ra, 0(sp); addiu sp, sp, 16` on return. Without it the state functions' frames sit 16 bytes
// higher than in the original and whatever they read from stack bytes they did not write (stale locals) comes
// from other addresses: the battle route's heap picked up such bytes shifted by one 16-byte record.
class DriverFrame {
public:
    explicit DriverFrame(EEContext& ctx) noexcept : ctx_(ctx) {
        rt::addiu(ctx_, GPR_SP, GPR_SP, -16);
        rt::sd(ctx_, GPR_RA, GPR_SP, 0);
    }
    ~DriverFrame() {
        rt::ld(ctx_, GPR_RA, GPR_SP, 0);
        rt::addiu(ctx_, GPR_SP, GPR_SP, 16);
    }
    DriverFrame(const DriverFrame&) = delete;
    DriverFrame& operator=(const DriverFrame&) = delete;

private:
    EEContext& ctx_;
};
// `sll v1, s, 1; addu v0, v1, s; sll v1, v0, 2; lui/addiu/addu v0, table; lw v0, field(v0); jalr v0` at `pc`:
// $v1 = 12 * s (32-bit, sign-extended), $v0 = the entry, $ra = its link (`pc` as the generated body passes it to
// rt::jalr); $a0 is whatever the caller set. Returns $v0.
u64 jalr_state(EEContext& ctx, u32 pc, u32 table_field, u32 s) {
    const u32 s12 = 12u * s;
    const u32 target = guest::load<u32>(ctx, table_field + s12);
    ee::core::set_gpr64(ctx, GPR_V1, ee::core::sext32(s12));
    ee::core::set_gpr64(ctx, GPR_V0, ee::core::sext32(target));
    rt::jalr(ctx, GPR_RA, pc);
    rt::lookup_func(target)(ctx);
    return ee::core::gpr64(ctx, GPR_V0);
}

u64 sx64(u32 v) { return ee::core::sext32(v); }

u32 gbtl(const EEContext& ctx) { return guest::load<u32>(ctx, kBtlPtr); }

// --- btlUnit fields read here (the 3D unit object behind action +48) --------------------------------------------
// --- gBtl fields ------------------------------------------------------------------------------------------------
constexpr u32 kBtlMainState = 692, kBtlMainPending = 696, kBtlMainFrames = 700, kBtlTask = 3352;

}  // namespace

// =================================================================================================================
// datUnit.c
// =================================================================================================================

// 0x002FF2D0 sub_2FF2D0 [datUnitSetGenusReady] -- 24 bytes; leaf frame (no stack)
// sub_2FF2D0(value): the genus-ready byte 0x7CE508 = 1, u16 0x7CE50A = 0, u16 0x7CE50C = value (btlMainInitStateStart
// passes 3). Leaves $v0 alone. Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_2FF2D0(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::sb, hg::sh;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    enter(ctx, 6);  // entry check point + the only block
    sh(zero, gp, gp_off(btl::kGenusReadyA));
    sh(a0, gp, gp_off(btl::kGenusReadyArg));  // = value
    v1 = 1;
    sb(v1, gp, gp_off(btl::kGenusReady));     // = 1
}

// 0x002FF2F0 sub_2FF2F0 [datUnitSetGenusReadyZero] -- 24 bytes; leaf frame (no stack)
// sub_2FF2F0(): sub_2FF2D0 with value 0. Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_2FF2F0(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::sb, hg::sh;
    Gpr zero{ctx, 0}, v1{ctx, 3}, gp{ctx, 28};
    enter(ctx, 6);  // entry check point + the only block
    sh(zero, gp, gp_off(btl::kGenusReadyA));
    sh(zero, gp, gp_off(btl::kGenusReadyArg));  // = 0
    v1 = 1;
    sb(v1, gp, gp_off(btl::kGenusReady));       // = 1
}

u32 sub_2FF310(EEContext& ctx) {  // 0x2FF310: returns 1
    guest::enter(ctx, 3);
    return 1;
}

u32 datUnitIsGenusReady(EEContext& ctx) {  // 0x2FF320 datUnitIsGenusReady: the ready byte is set
    guest::enter(ctx, 4);
    return guest::load<u8>(ctx, kGenusReady) != 0 ? 1u : 0u;
}

u32 sub_2FF330(EEContext& ctx) {  // 0x2FF330: returns 0
    guest::enter(ctx, 3);
    return 0;
}

// 0x002FF660 datUnitEcRemoveEnemy -- 244 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// 0x2FF660 datUnitEcRemoveEnemy(genus, unit): asserts an enemy genus (kind 1) with at most 6 units, finds
// the slot whose address is `unit` (genus +4 points at 6 x 60-byte units), zeroes its id and decrements the
// count; asserts (line 147) when no slot matched. Leaves $v0 alone.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void datUnitEcRemoveEnemy(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::ld, hg::lhu, hg::lq, hg::lw, hg::sd,
          hg::sh, hg::sll, hg::slti, hg::sq, hg::subu;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002ff660: prologue; s1 = genus, s0 = unit
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lhu(a0, a0, genus::kKind);
    v1 = genus::kKindEnemy;
    if (a0 != v1) {
        // 0x002ff688: K_Assert(genus->kind == enemy)
        charge(ctx, 5);
        k_assert(a0, a1, 0x2FF694u, kDatUnitFile, 134);
    }
    // 0x002ff69c
    charge(ctx, 4);
    lhu(v1, s1, genus::kCount);
    at = slti(v1, genus::kMaxEnemies + 1);
    if (at == 0) {
        // 0x002ff6ac: K_Assert(genus->count <= 6)
        charge(ctx, 5);
        k_assert(a0, a1, 0x2FF6B8u, kDatUnitFile, 135);
    }
    // 0x002ff6c0: for (i = 0; i < 6; ++i) find the slot whose address is `unit` (a2 = i, u16)
    charge(ctx, 3);
    a2 = 0;
    for (;;) {
        // 0x002ff70c: loop test; a0 = i stays live for the assert after the loop
        charge(ctx, 4);
        a0 = a2 & 0xFFFF;
        v1 = slti(a0, genus::kMaxEnemies);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002ff6cc: v1 = &genus->units[i] (60-byte stride: (i * 15) << 2)
        charge(ctx, 8);
        a1 = a2 & 0xFFFF;
        v1 = sll(a1, 4);
        v1 = subu(v1, a1);
        a1 = sll(v1, 2);
        lw(v1, s1, genus::kUnits);
        v1 = addu(v1, a1);
        if (s0 == v1) {
            // 0x002ff6ec: found: units[i].id = 0, --genus->count
            charge(ctx, 6);
            sh(zero, v1, dat_unit::kId);
            lhu(v1, s1, genus::kCount);
            v1 = addiu(v1, -1);
            sh(v1, s1, genus::kCount);
            break;
        }
        // 0x002ff704: ++i
        charge(ctx, 2);
        v1 = addiu(a2, 1);
        a2 = v1 & 0xFFFF;
    }
    // 0x002ff71c: K_Assert(i < 6): `unit` was in the genus
    charge(ctx, 3);
    v1 = slti(a0, genus::kMaxEnemies);
    if (v1 == 0) {
        // 0x002ff728
        charge(ctx, 5);
        k_assert(a0, a1, 0x2FF734u, kDatUnitFile, 147);
    }
    // 0x002ff73c: epilogue
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002FF790 datUnitIsGenusDead -- 244 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// 0x2FF790 datUnitIsGenusDead(genus): an enemy genus is dead when every slot with a non-zero id is
// datCalcIsDead; a party genus (asserted count 1) when its one unit is.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void datUnitIsGenusDead(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lq,
          hg::lw, hg::sd, hg::sll, hg::slti, hg::sq, hg::subu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    auto epilogue = [&] {  // 0x002ff86c
        charge(ctx, 6);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
    };
    // 0x002ff790: prologue; s1 = genus
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lhu(v0, a0, genus::kKind);
    v1 = genus::kKindEnemy;
    if (v0 == v1) {
        // 0x002ff7b4: enemy genus: for (i = 0; i < 6; ++i) a slot with an id that is not dead -> 0 (s0 = i, u16)
        charge(ctx, 3);
        s0 = 0;
        for (;;) {
            // 0x002ff80c: loop test
            charge(ctx, 4);
            v0 = s0 & 0xFFFF;
            v0 = slti(v0, genus::kMaxEnemies);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002ff7c0: a0 = &genus->units[i]; is its id set?
            charge(ctx, 9);
            lw(a0, s1, genus::kUnits);
            v1 = s0 & 0xFFFF;
            v0 = sll(v1, 4);
            v0 = subu(v0, v1);
            v0 = sll(v0, 2);
            a0 = addu(a0, v0);
            lhu(v0, a0, dat_unit::kId);
            if (v0 != 0) {
                // 0x002ff7e4: datCalcIsDead(unit, 0)
                charge(ctx, 5);
                a1 = 0;
                jal(ctx, 0x2FF7E8u, gen::fn_datCalcIsDead_0030b5a0);
                if (v0 == 0) {
                    // 0x002ff7f8: a live unit: return 0
                    charge(ctx, 3);
                    v0 = 0;
                    epilogue();
                    return;
                }
            }
            // 0x002ff804: ++i
            charge(ctx, 2);
            v0 = addiu(s0, 1);
            s0 = v0 & 0xFFFF;
        }
        // 0x002ff81c, 0x002ff868: every slot empty or dead: return 1
        charge(ctx, 2);
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x002ff824: party genus: K_Assert(count == 1), then its one unit
        charge(ctx, 3);
        lhu(v0, s1, genus::kCount);
        if (v0 != v1) {
            // 0x002ff830
            charge(ctx, 5);
            k_assert(a0, a1, 0x2FF83Cu, kDatUnitFile, 185);
        }
        // 0x002ff844: datCalcIsDead(genus->units, 0)
        charge(ctx, 6);
        lw(a0, s1, genus::kUnits);
        a1 = 0;
        jal(ctx, 0x2FF84Cu, gen::fn_datCalcIsDead_0030b5a0);
        if (v0 != 0) {
            // 0x002ff868: return 1
            charge(ctx, 1);
            v0 = 1;
        } else {
            // 0x002ff85c: return 0
            charge(ctx, 3);
            v0 = 0;
        }
    }
    epilogue();
}

// 0x002FF890 datUnitInit -- 624 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// datUnitInit(unit, kind, id): kind 0 = party member (clears the enemy flag and the two copied flags), kind 1 = enemy
// from UNIT.TBL section 0 (level, max HP/SP as current, status 0, flags 0x10/0x20/0x80/0x100 from record flags
// 0x8/0x10/0x100/0x200, 0x200 when one of the eight skills is 544/545/546); any other kind asserts (line 253). Then
// all 21 buff slots are cleared, id and base id stored and flag bit 0 set; returns 1.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void datUnitInit(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lhu,
          hg::lq, hg::lw, hg::sb, hg::sd, hg::sh, hg::sll, hg::slti, hg::sltiu, hg::sq, hg::subu, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002ff890: prologue; s1 = unit, s0 = id, v1 = kind (u8)
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a2;
    v1 = a1 & 0xFF;
    v0 = 1;
    if (v1 == v0) {
        // 0x002ff91c: kind 1, an enemy: K_Assert(id < 336)
        charge(ctx, 4);
        v0 = s0 & 0xFFFF;
        v0 = slti(v0, enemy_rec::kCount);
        if (v0 == 0) {
            // 0x002ff92c
            charge(ctx, 5);
            k_assert(a0, a1, 0x2FF938u, kDatUnitFile, 217);
        }
        // 0x002ff940: flags = enemy; level, hp, sp from the record; status = 0 (v0 = id * 62, the record offset)
        charge(ctx, 25);
        v0 = dat_unit::kFlagEnemy;
        sh(v0, s1, dat_unit::kFlags);
        v1 = s0 & 0xFFFF;
        v0 = sll(v1, 5);
        v0 = subu(v0, v1);
        v0 = sll(v0, 1);
        lw(v1, gp, gp_off(btl::kUnitTablePtr));  // gBtlEnemyTbl
        v1 = addu(v0, v1);
        lbu(v1, v1, enemy_rec::kLevel);
        sb(v1, s1, dat_unit::kLevel);
        lw(v1, gp, gp_off(btl::kUnitTablePtr));
        v1 = addu(v0, v1);
        lhu(v1, v1, enemy_rec::kHp);
        sh(v1, s1, dat_unit::kHp);
        lw(v1, gp, gp_off(btl::kUnitTablePtr));
        v1 = addu(v0, v1);
        lhu(v1, v1, enemy_rec::kSp);
        sh(v1, s1, dat_unit::kSp);
        sw(zero, s1, dat_unit::kStatus);
        // record flag 0x8 -> unit flag 0x10
        lw(v1, gp, gp_off(btl::kUnitTablePtr));
        v1 = addu(v1, v0);
        lhu(v1, v1, enemy_rec::kFlags);
        v1 = v1 & 0x8;
        if (v1 != 0) {
            // 0x002ff9a4
            charge(ctx, 3);
            lhu(v1, s1, dat_unit::kFlags);
            v1 = v1 | 0x10;
            sh(v1, s1, dat_unit::kFlags);
        }
        // 0x002ff9b0: record flag 0x10 -> unit flag 0x20
        charge(ctx, 6);
        lw(v1, gp, gp_off(btl::kUnitTablePtr));
        v1 = addu(v1, v0);
        lhu(v1, v1, enemy_rec::kFlags);
        v1 = v1 & 0x10;
        if (v1 != 0) {
            // 0x002ff9c8
            charge(ctx, 3);
            lhu(v1, s1, dat_unit::kFlags);
            v1 = v1 | 0x20;
            sh(v1, s1, dat_unit::kFlags);
        }
        // 0x002ff9d4: record flag 0x100 -> unit flag 0x80
        charge(ctx, 6);
        lw(v1, gp, gp_off(btl::kUnitTablePtr));
        v1 = addu(v1, v0);
        lhu(v1, v1, enemy_rec::kFlags);
        v1 = v1 & 0x100;
        if (v1 != 0) {
            // 0x002ff9ec
            charge(ctx, 3);
            lhu(v1, s1, dat_unit::kFlags);
            v1 = v1 | 0x80;
            sh(v1, s1, dat_unit::kFlags);
        }
        // 0x002ff9f8: record flag 0x200 -> unit flag 0x100
        charge(ctx, 6);
        lw(v1, gp, gp_off(btl::kUnitTablePtr));
        v1 = addu(v1, v0);
        lhu(v1, v1, enemy_rec::kFlags);
        v1 = v1 & 0x200;
        if (v1 != 0) {
            // 0x002ffa10
            charge(ctx, 3);
            lhu(v1, s1, dat_unit::kFlags);
            v1 = v1 | 0x100;
            sh(v1, s1, dat_unit::kFlags);
        }
        // 0x002ffa1c: for (i = 0; i < 8; ++i) skill 544, 545 or 546 -> unit flag 0x200 (t0 = i)
        charge(ctx, 6);
        t0 = 0;
        a0 = 544;
        a1 = 545;
        a2 = 546;
        for (;;) {
            // 0x002ffa78: loop test
            charge(ctx, 3);
            v1 = sltiu(t0, 8);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002ffa34: v1 = record->skills[i]; compared with 546, then 545, then 544
            charge(ctx, 7);
            lw(v1, gp, gp_off(btl::kUnitTablePtr));
            a3 = addu(v0, v1);
            v1 = sll(t0, 1);
            v1 = addu(a3, v1);
            lhu(v1, v1, enemy_rec::kSkills);
            bool evade = v1 == a2;
            if (!evade) {
                // 0x002ffa50
                charge(ctx, 2);
                evade = v1 == a1;
                if (!evade) {
                    // 0x002ffa58
                    charge(ctx, 2);
                    evade = v1 == a0;
                    if (!evade) {
                        // 0x002ffa60
                        charge(ctx, 2);
                    }
                }
            }
            if (evade) {
                // 0x002ffa68: flags |= 0x200
                charge(ctx, 3);
                lhu(v1, s1, dat_unit::kFlags);
                v1 = v1 | dat_unit::kFlagEvade;
                sh(v1, s1, dat_unit::kFlags);
            }
            // 0x002ffa74: ++i
            charge(ctx, 1);
            t0 = addiu(t0, 1);
        }
        // 0x002ffa84
        charge(ctx, 2);
    } else {
        // 0x002ff8bc
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x002ff8cc: kind 0, a party member: K_Assert(id < 11)
            charge(ctx, 4);
            v0 = s0 & 0xFFFF;
            v0 = slti(v0, dat_unit::kPartyIds);
            if (v0 == 0) {
                // 0x002ff8dc
                charge(ctx, 5);
                k_assert(a0, a1, 0x2FF8E8u, kDatUnitFile, 211);
            }
            // 0x002ff8f0: flags &= ~0x4, ~0x10, ~0x20
            charge(ctx, 11);
            lhu(v0, s1, dat_unit::kFlags);
            v0 = v0 & 0xFFFB;
            sh(v0, s1, dat_unit::kFlags);
            lhu(v0, s1, dat_unit::kFlags);
            v0 = v0 & 0xFFEF;
            sh(v0, s1, dat_unit::kFlags);
            lhu(v0, s1, dat_unit::kFlags);
            v0 = v0 & 0xFFDF;
            sh(v0, s1, dat_unit::kFlags);
        } else {
            // 0x002ff8c4, 0x002ffa8c: any other kind: K_Assert(0)
            charge(ctx, 2);
            charge(ctx, 5);
            k_assert(a0, a1, 0x2FFA98u, kDatUnitFile, 253);
        }
    }
    // 0x002ffaa0: for (slot = 0; slot < 21; ++slot) datCalcClearEffect(unit, slot) (s2 = slot)
    charge(ctx, 3);
    s2 = 0;
    for (;;) {
        // 0x002ffac0: loop test
        charge(ctx, 3);
        v0 = sltiu(s2, btl::kEffectSlots);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002ffaac
        charge(ctx, 5);
        a1 = s2 & 0xFF;
        a0 = s1;
        jal(ctx, 0x2FFAB4u, gen::fn_datCalcClearEffect_00301540);
        s2 = addiu(s2, 1);
    }
    // 0x002ffacc: id = base id = id, flags |= initialised; return 1; epilogue
    charge(ctx, 13);
    sh(s0, s1, dat_unit::kId);
    sh(s0, s1, dat_unit::kBaseId);
    lhu(v0, s1, dat_unit::kFlags);
    v0 = v0 | dat_unit::kFlagInit;
    sh(v0, s1, dat_unit::kFlags);
    v0 = 1;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// =================================================================================================================
// datCalc.c
// =================================================================================================================

// 0x002FFBC0 datCalcRand -- 248 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// datCalcRand(n): n == 100 rolls 0..99 from two 12-bit effMiscRand draws ((a + b) & 0xFFF) / 41 and re-rolls once
// when the roll is within 3 of the previous one (0x7CE510; both compares unsigned, so a roll below 3 never re-rolls on
// the low side); otherwise effMiscRand(0) % n through divu (K_Assert line 26 on n == 0, the EE's divide-by-zero HI
// then). Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void datCalcRand(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::divu, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::mfhi,
          hg::mflo, hg::sd, hg::sltu, hg::sq, hg::sw;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002ffbc0: prologue; s0 = n
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    if (s0 == 0) {
        // 0x002ffbd8: K_Assert(n != 0)
        charge(ctx, 5);
        k_assert(a0, a1, 0x2FFBE4u, kDatCalcFile, 26);
    }
    // 0x002ffbec
    charge(ctx, 3);
    v0 = 100;
    if (s0 != v0) {
        // 0x002ffc90: effMiscRand(0) % n
        charge(ctx, 5);
        a0 = 0;
        jal(ctx, 0x2FFC94u, gen::fn_sub_357FD0_00357fd0);
        divu(v0, s0);
        mfhi(v0);
    } else {
        // 0x002ffbf8: roll = (((rand & 0xFFF) + (rand & 0xFFF)) & 0xFFF) / 41; a0 = the previous roll
        charge(ctx, 18);
        a0 = 0;
        jal(ctx, 0x2FFBFCu, gen::fn_sub_357FD0_00357fd0);
        s0 = v0 & 0xFFF;
        a0 = 0;
        jal(ctx, 0x2FFC0Cu, gen::fn_sub_357FD0_00357fd0);
        v0 = v0 & 0xFFF;
        v0 = addu(s0, v0);
        v1 = v0 & 0xFFF;
        v0 = 41;
        divu(v1, v0);
        mflo(v0);
        lw(a0, gp, gp_off(btl::kRandPrev));
        v1 = addiu(v0, -3);
        v1 = sltu(a0, v1);
        if (v1 == 0) {
            // 0x002ffc40: prev >= roll - 3: is prev <= roll + 3 too?
            charge(ctx, 4);
            v1 = addiu(v0, 3);
            at = sltu(v1, a0);
            if (at == 0) {
                // 0x002ffc50: too close to the previous roll: roll again, the same way
                charge(ctx, 13);
                a0 = 0;
                jal(ctx, 0x2FFC54u, gen::fn_sub_357FD0_00357fd0);
                s0 = v0 & 0xFFF;
                a0 = 0;
                jal(ctx, 0x2FFC64u, gen::fn_sub_357FD0_00357fd0);
                v0 = v0 & 0xFFF;
                v0 = addu(s0, v0);
                v1 = v0 & 0xFFF;
                v0 = 41;
                divu(v1, v0);
                mflo(v0);
            }
        }
        // 0x002ffc84: remember the roll
        charge(ctx, 3);
        sw(v0, gp, gp_off(btl::kRandPrev));
    }
    // 0x002ffca4: epilogue (returns $v0)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002FFCC0 datCalcGetLevel -- 172 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// datCalcGetLevel(unit): unit +6 for enemies and the hero, else the level of the member's persona; asserts a persona
// (line 66) and a non-zero level (line 70). Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame).
void datCalcGetLevel(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::i64, hg::jal, hg::lbu, hg::ld, hg::lhu, hg::lq, hg::sd,
          hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002ffcc0: prologue; is the unit an enemy?
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lhu(v0, a0, dat_unit::kFlags);
    v0 = v0 & dat_unit::kFlagEnemy;
    bool own_level = v0 != 0;
    if (!own_level) {
        // 0x002ffcdc: a party member: the hero (id 1) keeps his level in the unit
        charge(ctx, 4);
        lhu(v1, a0, dat_unit::kId);
        v0 = dat_unit::kHero;
        own_level = v1 == v0;
        if (!own_level) {
            // 0x002ffcf8: s0 = datPersonaGetByPcId(id); K_Assert(s0)
            charge(ctx, 6);
            a0 = v1;
            jal(ctx, 0x2FFCFCu, gen::fn_datPersonaGetByPcId_00174800);
            s0 = v0;
            if (s0 == 0) {
                // 0x002ffd10
                charge(ctx, 5);
                k_assert(a0, a1, 0x2FFD1Cu, kDatCalcFile, 66);
            }
            // 0x002ffd24: s0 = (u8)sub_1732F0(persona), the persona's level
            charge(ctx, 4);
            a0 = s0;
            jal(ctx, 0x2FFD28u, gen::fn_sub_1732F0_001732f0);
            s0 = v0 & 0xFF;
        }
    }
    if (own_level) {
        // 0x002ffcec: an enemy or the hero: s0 = unit->level
        charge(ctx, 3);
        lbu(s0, a0, dat_unit::kLevel);
    }
    // 0x002ffd34: K_Assert(level > 0)
    charge(ctx, 3);
    v0 = s0 & 0xFF;
    if (i64(v0) <= 0) {
        // 0x002ffd40
        charge(ctx, 5);
        k_assert(a0, a1, 0x2FFD4Cu, kDatCalcFile, 70);
    }
    // 0x002ffd54: return the level; epilogue
    charge(ctx, 6);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u32 datCalcGetLevel(EEContext& ctx, u32 unit) {
    ee::core::set_gpr64(ctx, GPR_A0, ee::core::sext32(static_cast<u32>(unit)));
    datCalcGetLevel(ctx);
    return static_cast<u32>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x002FFDF0 datCalcGetMaxHp -- 784 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// datCalcGetMaxHp(unit): the base (enemy: EnemyRecord +4; party member: sub_16CC00, the growth table's HP at the
// unit's level) plus the passive skills (537 +10 %, 538 +20 %, 539 +30 %, 620 +50 %, 567 +100 %, 568 -50 %, each
// base * k / 100 with integer division) plus the equipment effects (26..30: +10/20/30/40/50 per carrying slot, 142:
// +100); a party member's total is capped at 999. Returns the u16. Asserts the id (party < 11 line 172, enemy < 336
// line 169). Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void datCalcGetMaxHp(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::div, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld,
          hg::lhu, hg::lq, hg::lw, hg::mflo, hg::sd, hg::sll, hg::slti, hg::sq, hg::subu;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002ffdf0: prologue; s1 = unit, s2 = bonus = 0, s0 = id
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s2 = 0;
    lhu(s0, a0, dat_unit::kId);
    lhu(v0, a0, dat_unit::kFlags);
    v0 = v0 & dat_unit::kFlagEnemy;
    if (v0 == 0) {
        // 0x002ffe68: party member: K_Assert(id < 11)
        charge(ctx, 4);
        v0 = s0 & 0xFFFF;
        v0 = slti(v0, dat_unit::kPartyIds);
        if (v0 == 0) {
            // 0x002ffe78
            charge(ctx, 5);
            k_assert(a0, a1, 0x2FFE84u, kDatCalcFile, 172);
        }
        // 0x002ffe8c: base = (u16)sub_16CC00((s16)id)
        charge(ctx, 5);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x2FFE94u, gen::fn_sub_16CC00_0016cc00);
        v0 = v0 & 0xFFFF;
    } else {
        // 0x002ffe20: enemy: K_Assert(id < 336)
        charge(ctx, 4);
        v0 = s0 & 0xFFFF;
        v0 = slti(v0, enemy_rec::kCount);
        if (v0 == 0) {
            // 0x002ffe30
            charge(ctx, 5);
            k_assert(a0, a1, 0x2FFE3Cu, kDatCalcFile, 169);
        }
        // 0x002ffe44: base = gBtlEnemyTbl[id].hp (62-byte records)
        charge(ctx, 9);
        lw(a0, gp, gp_off(btl::kUnitTablePtr));  // gBtlEnemyTbl
        v1 = s0 & 0xFFFF;
        v0 = sll(v1, 5);
        v0 = subu(v0, v1);
        v0 = sll(v0, 1);
        v0 = addu(v0, a0);
        lhu(v0, v0, enemy_rec::kHp);
    }
    // 0x002ffea0: s0 = base; skill 537: bonus += base * 10 / 100
    charge(ctx, 7);
    s0 = v0 & 0xFFFF;
    a0 = s1;
    a1 = 537;
    jal(ctx, 0x2FFEACu, gen::fn_datCalcHasSkill_003005e0);
    if (v0 != 0) {
        // 0x002ffebc
        charge(ctx, 7);
        v0 = sll(s0, 2);
        v0 = addu(v0, s0);
        v1 = sll(v0, 1);
        v0 = 100;
        div(v1, v0);
        mflo(v0);
        s2 = addu(s2, v0);
    }
    // 0x002ffed8: skill 538: bonus += base * 20 / 100
    charge(ctx, 6);
    a0 = s1;
    a1 = 538;
    jal(ctx, 0x2FFEE0u, gen::fn_datCalcHasSkill_003005e0);
    if (v0 != 0) {
        // 0x002ffef0
        charge(ctx, 7);
        v0 = sll(s0, 2);
        v0 = addu(v0, s0);
        v1 = sll(v0, 2);
        v0 = 100;
        div(v1, v0);
        mflo(v0);
        s2 = addu(s2, v0);
    }
    // 0x002fff0c: skill 539: bonus += base * 30 / 100
    charge(ctx, 6);
    a0 = s1;
    a1 = 539;
    jal(ctx, 0x2FFF14u, gen::fn_datCalcHasSkill_003005e0);
    if (v0 != 0) {
        // 0x002fff24
        charge(ctx, 7);
        v0 = sll(s0, 4);
        v0 = subu(v0, s0);
        v1 = sll(v0, 1);
        v0 = 100;
        div(v1, v0);
        mflo(v0);
        s2 = addu(s2, v0);
    }
    // 0x002fff40: skill 620: bonus += base * 50 / 100
    charge(ctx, 6);
    a0 = s1;
    a1 = 620;
    jal(ctx, 0x2FFF48u, gen::fn_datCalcHasSkill_003005e0);
    if (v0 != 0) {
        // 0x002fff58
        charge(ctx, 9);
        v0 = sll(s0, 2);
        v1 = addu(v0, s0);
        v0 = sll(v1, 2);
        v0 = addu(v1, v0);
        v1 = sll(v0, 1);
        v0 = 100;
        div(v1, v0);
        mflo(v0);
        s2 = addu(s2, v0);
    }
    // 0x002fff7c: skill 567: bonus += base
    charge(ctx, 6);
    a0 = s1;
    a1 = 567;
    jal(ctx, 0x2FFF84u, gen::fn_datCalcHasSkill_003005e0);
    if (v0 != 0) {
        // 0x002fff94
        charge(ctx, 1);
        s2 = addu(s2, s0);
    }
    // 0x002fff98: skill 568: bonus -= base * 50 / 100
    charge(ctx, 6);
    a0 = s1;
    a1 = 568;
    jal(ctx, 0x2FFFA0u, gen::fn_datCalcHasSkill_003005e0);
    if (v0 != 0) {
        // 0x002fffb0
        charge(ctx, 9);
        v0 = sll(s0, 2);
        v1 = addu(v0, s0);
        v0 = sll(v1, 2);
        v0 = addu(v1, v0);
        v1 = sll(v0, 1);
        v0 = 100;
        div(v1, v0);
        mflo(v0);
        s2 = subu(s2, v0);
    }
    // 0x002fffd4: equipment: bonus += 10 * count(26) + 20 * count(27) + 30 * count(28) + 40 * count(29)
    // + 50 * count(30) + 100 * count(142); v1 = base + bonus
    charge(ctx, 63);
    a0 = s1;
    a1 = 26;
    jal(ctx, 0x2FFFDCu, gen::fn_datCalcCountEquipmentWithEffect_003009a0);
    v1 = v0 & 0xFFFF;
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    s2 = addu(s2, v0);
    a0 = s1;
    a1 = 27;
    jal(ctx, 0x300000u, gen::fn_datCalcCountEquipmentWithEffect_003009a0);
    v1 = v0 & 0xFFFF;
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    s2 = addu(s2, v0);
    a0 = s1;
    a1 = 28;
    jal(ctx, 0x300024u, gen::fn_datCalcCountEquipmentWithEffect_003009a0);
    v1 = v0 & 0xFFFF;
    v0 = sll(v1, 4);
    v0 = subu(v0, v1);
    v0 = sll(v0, 1);
    s2 = addu(s2, v0);
    a0 = s1;
    a1 = 29;
    jal(ctx, 0x300048u, gen::fn_datCalcCountEquipmentWithEffect_003009a0);
    v1 = v0 & 0xFFFF;
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 3);
    s2 = addu(s2, v0);
    a0 = s1;
    a1 = 30;
    jal(ctx, 0x30006Cu, gen::fn_datCalcCountEquipmentWithEffect_003009a0);
    v1 = v0 & 0xFFFF;
    v0 = sll(v1, 2);
    v1 = addu(v0, v1);
    v0 = sll(v1, 2);
    v0 = addu(v1, v0);
    v0 = sll(v0, 1);
    s2 = addu(s2, v0);
    a0 = s1;
    a1 = 142;
    jal(ctx, 0x300098u, gen::fn_datCalcCountEquipmentWithEffect_003009a0);
    v1 = v0 & 0xFFFF;
    v0 = sll(v1, 2);
    v1 = addu(v0, v1);
    v0 = sll(v1, 2);
    v0 = addu(v1, v0);
    v0 = sll(v0, 2);
    v0 = addu(s2, v0);
    v1 = addu(s0, v0);
    lhu(v0, s1, dat_unit::kFlags);
    v0 = v0 & dat_unit::kFlagEnemy;
    if (v0 == 0) {
        // 0x003000d0: a party member's max HP is capped at 999
        charge(ctx, 3);
        at = slti(v1, 1000);
        if (at == 0) {
            // 0x003000dc
            charge(ctx, 1);
            v1 = 999;
        }
    }
    // 0x003000e0: return (u16)total; epilogue
    charge(ctx, 8);
    v0 = v1 & 0xFFFF;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00300100 datCalcGetMaxSp -- 784 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// datCalcGetMaxSp(unit): datCalcGetMaxHp's shape for SP: base from EnemyRecord +6 or sub_16CCB0 (the growth table's
// SP), passive skills 540 +10 %, 541 +20 %, 542 +30 %, 621 +50 %, 567 -50 %, 568 +100 % (567 / 568 swap their roles
// against max HP), equipment effects 31..35 (+10..50 per slot) and 143 (+100), 999 cap for a party member. Asserts
// lines 198 / 195. Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void datCalcGetMaxSp(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::div, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld,
          hg::lhu, hg::lq, hg::lw, hg::mflo, hg::sd, hg::sll, hg::slti, hg::sq, hg::subu;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00300100: prologue; s1 = unit, s2 = bonus = 0, s0 = id
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s2 = 0;
    lhu(s0, a0, dat_unit::kId);
    lhu(v0, a0, dat_unit::kFlags);
    v0 = v0 & dat_unit::kFlagEnemy;
    if (v0 == 0) {
        // 0x00300178: party member: K_Assert(id < 11)
        charge(ctx, 4);
        v0 = s0 & 0xFFFF;
        v0 = slti(v0, dat_unit::kPartyIds);
        if (v0 == 0) {
            // 0x00300188
            charge(ctx, 5);
            k_assert(a0, a1, 0x300194u, kDatCalcFile, 198);
        }
        // 0x0030019c: base = (u16)sub_16CCB0((s16)id)
        charge(ctx, 5);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x3001A4u, gen::fn_sub_16CCB0_0016ccb0);
        v0 = v0 & 0xFFFF;
    } else {
        // 0x00300130: enemy: K_Assert(id < 336)
        charge(ctx, 4);
        v0 = s0 & 0xFFFF;
        v0 = slti(v0, enemy_rec::kCount);
        if (v0 == 0) {
            // 0x00300140
            charge(ctx, 5);
            k_assert(a0, a1, 0x30014Cu, kDatCalcFile, 195);
        }
        // 0x00300154: base = gBtlEnemyTbl[id].sp
        charge(ctx, 9);
        lw(a0, gp, gp_off(btl::kUnitTablePtr));  // gBtlEnemyTbl
        v1 = s0 & 0xFFFF;
        v0 = sll(v1, 5);
        v0 = subu(v0, v1);
        v0 = sll(v0, 1);
        v0 = addu(v0, a0);
        lhu(v0, v0, enemy_rec::kSp);
    }
    // 0x003001b0: s0 = base; skill 540: bonus += base * 10 / 100
    charge(ctx, 7);
    s0 = v0 & 0xFFFF;
    a0 = s1;
    a1 = 540;
    jal(ctx, 0x3001BCu, gen::fn_datCalcHasSkill_003005e0);
    if (v0 != 0) {
        // 0x003001cc
        charge(ctx, 7);
        v0 = sll(s0, 2);
        v0 = addu(v0, s0);
        v1 = sll(v0, 1);
        v0 = 100;
        div(v1, v0);
        mflo(v0);
        s2 = addu(s2, v0);
    }
    // 0x003001e8: skill 541: bonus += base * 20 / 100
    charge(ctx, 6);
    a0 = s1;
    a1 = 541;
    jal(ctx, 0x3001F0u, gen::fn_datCalcHasSkill_003005e0);
    if (v0 != 0) {
        // 0x00300200
        charge(ctx, 7);
        v0 = sll(s0, 2);
        v0 = addu(v0, s0);
        v1 = sll(v0, 2);
        v0 = 100;
        div(v1, v0);
        mflo(v0);
        s2 = addu(s2, v0);
    }
    // 0x0030021c: skill 542: bonus += base * 30 / 100
    charge(ctx, 6);
    a0 = s1;
    a1 = 542;
    jal(ctx, 0x300224u, gen::fn_datCalcHasSkill_003005e0);
    if (v0 != 0) {
        // 0x00300234
        charge(ctx, 7);
        v0 = sll(s0, 4);
        v0 = subu(v0, s0);
        v1 = sll(v0, 1);
        v0 = 100;
        div(v1, v0);
        mflo(v0);
        s2 = addu(s2, v0);
    }
    // 0x00300250: skill 621: bonus += base * 50 / 100
    charge(ctx, 6);
    a0 = s1;
    a1 = 621;
    jal(ctx, 0x300258u, gen::fn_datCalcHasSkill_003005e0);
    if (v0 != 0) {
        // 0x00300268
        charge(ctx, 9);
        v0 = sll(s0, 2);
        v1 = addu(v0, s0);
        v0 = sll(v1, 2);
        v0 = addu(v1, v0);
        v1 = sll(v0, 1);
        v0 = 100;
        div(v1, v0);
        mflo(v0);
        s2 = addu(s2, v0);
    }
    // 0x0030028c: skill 567: bonus -= base * 50 / 100
    charge(ctx, 6);
    a0 = s1;
    a1 = 567;
    jal(ctx, 0x300294u, gen::fn_datCalcHasSkill_003005e0);
    if (v0 != 0) {
        // 0x003002a4
        charge(ctx, 9);
        v0 = sll(s0, 2);
        v1 = addu(v0, s0);
        v0 = sll(v1, 2);
        v0 = addu(v1, v0);
        v1 = sll(v0, 1);
        v0 = 100;
        div(v1, v0);
        mflo(v0);
        s2 = subu(s2, v0);
    }
    // 0x003002c8: skill 568: bonus += base
    charge(ctx, 6);
    a0 = s1;
    a1 = 568;
    jal(ctx, 0x3002D0u, gen::fn_datCalcHasSkill_003005e0);
    if (v0 != 0) {
        // 0x003002e0
        charge(ctx, 1);
        s2 = addu(s2, s0);
    }
    // 0x003002e4: equipment: bonus += 10 * count(31) + 20 * count(32) + 30 * count(33) + 40 * count(34)
    // + 50 * count(35) + 100 * count(143); v1 = base + bonus
    charge(ctx, 63);
    a0 = s1;
    a1 = 31;
    jal(ctx, 0x3002ECu, gen::fn_datCalcCountEquipmentWithEffect_003009a0);
    v1 = v0 & 0xFFFF;
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    s2 = addu(s2, v0);
    a0 = s1;
    a1 = 32;
    jal(ctx, 0x300310u, gen::fn_datCalcCountEquipmentWithEffect_003009a0);
    v1 = v0 & 0xFFFF;
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    s2 = addu(s2, v0);
    a0 = s1;
    a1 = 33;
    jal(ctx, 0x300334u, gen::fn_datCalcCountEquipmentWithEffect_003009a0);
    v1 = v0 & 0xFFFF;
    v0 = sll(v1, 4);
    v0 = subu(v0, v1);
    v0 = sll(v0, 1);
    s2 = addu(s2, v0);
    a0 = s1;
    a1 = 34;
    jal(ctx, 0x300358u, gen::fn_datCalcCountEquipmentWithEffect_003009a0);
    v1 = v0 & 0xFFFF;
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 3);
    s2 = addu(s2, v0);
    a0 = s1;
    a1 = 35;
    jal(ctx, 0x30037Cu, gen::fn_datCalcCountEquipmentWithEffect_003009a0);
    v1 = v0 & 0xFFFF;
    v0 = sll(v1, 2);
    v1 = addu(v0, v1);
    v0 = sll(v1, 2);
    v0 = addu(v1, v0);
    v0 = sll(v0, 1);
    s2 = addu(s2, v0);
    a0 = s1;
    a1 = 143;
    jal(ctx, 0x3003A8u, gen::fn_datCalcCountEquipmentWithEffect_003009a0);
    v1 = v0 & 0xFFFF;
    v0 = sll(v1, 2);
    v1 = addu(v0, v1);
    v0 = sll(v1, 2);
    v0 = addu(v1, v0);
    v0 = sll(v0, 2);
    v0 = addu(s2, v0);
    v1 = addu(s0, v0);
    lhu(v0, s1, dat_unit::kFlags);
    v0 = v0 & dat_unit::kFlagEnemy;
    if (v0 == 0) {
        // 0x003003e0: a party member's max SP is capped at 999
        charge(ctx, 3);
        at = slti(v1, 1000);
        if (at == 0) {
            // 0x003003ec
            charge(ctx, 1);
            v1 = 999;
        }
    }
    // 0x003003f0: return (u16)total; epilogue
    charge(ctx, 8);
    v0 = v1 & 0xFFFF;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00300410 datCalcAddHp -- 104 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// datCalcAddHp(unit, delta): hp = clamp(hp + delta, 0, datCalcGetMaxHp(unit)), stored as u16 and returned.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void datCalcAddHp(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::i64, hg::jal, hg::ld, hg::lhu, hg::lq, hg::sd,
          hg::sh, hg::slt, hg::sq;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00300410: prologue; s1 = unit, s0 = hp + delta
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lhu(v0, a0, dat_unit::kHp);
    s0 = addu(v0, a1);
    if (i64(s0) < 0) {
        // 0x00300434: not below 0
        charge(ctx, 1);
        s0 = 0;
    }
    // 0x00300438: not above datCalcGetMaxHp(unit)
    charge(ctx, 7);
    a0 = s1;
    jal(ctx, 0x30043Cu, gen::fn_datCalcGetMaxHp_002ffdf0);
    v0 = v0 & 0xFFFF;
    at = slt(v0, s0);
    if (at != 0) {
        // 0x00300454
        charge(ctx, 1);
        s0 = v0;
    }
    // 0x00300458: unit->hp = s0; return (u16)s0; epilogue
    charge(ctx, 8);
    v0 = s0 & 0xFFFF;
    sh(s0, s1, dat_unit::kHp);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00300480 datCalcAddSp -- 104 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// datCalcAddSp(unit, delta): sp = clamp(sp + delta, 0, datCalcGetMaxSp(unit)), stored as u16 and returned.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void datCalcAddSp(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::i64, hg::jal, hg::ld, hg::lhu, hg::lq, hg::sd,
          hg::sh, hg::slt, hg::sq;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00300480: prologue; s1 = unit, s0 = sp + delta
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lhu(v0, a0, dat_unit::kSp);
    s0 = addu(v0, a1);
    if (i64(s0) < 0) {
        // 0x003004a4: not below 0
        charge(ctx, 1);
        s0 = 0;
    }
    // 0x003004a8: not above datCalcGetMaxSp(unit)
    charge(ctx, 7);
    a0 = s1;
    jal(ctx, 0x3004ACu, gen::fn_datCalcGetMaxSp_00300100);
    v0 = v0 & 0xFFFF;
    at = slt(v0, s0);
    if (at != 0) {
        // 0x003004c4
        charge(ctx, 1);
        s0 = v0;
    }
    // 0x003004c8: unit->sp = s0; return (u16)s0; epilogue
    charge(ctx, 8);
    v0 = s0 & 0xFFFF;
    sh(s0, s1, dat_unit::kSp);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003005E0 datCalcHasSkill -- 284 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// datCalcHasSkill(unit, skill): one of the unit's skill slots (datCalcGetSkillSlotCount = 8 of them, list from
// datCalcGetSkillList), or for a party member the skill granted by the accessory in equipment slot 3 (item record
// +28 of sub_170E40). Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void datCalcHasSkill(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::i64,
          hg::jal, hg::ld, hg::lh, hg::lhu, hg::lq, hg::lw, hg::sd, hg::sll, hg::slt, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    auto epilogue = [&] {  // 0x003006e0
        charge(ctx, 7);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
    };
    // 0x003005e0: prologue; s1 = unit, s0 = skill; s2 = slot count, v0 = the skill list
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    jal(ctx, 0x3005FCu, gen::fn_datCalcGetSkillSlotCount_00308ba0);
    s2 = v0 & 0xFFFF;
    a0 = s1;
    jal(ctx, 0x30060Cu, gen::fn_datCalcGetSkillList_00308bb0);
    // for (i = 0; i < count; ++i) list[i] == skill -> 1 (a1 = i, a0 = count)
    a1 = 0;
    s0 = s0 & 0xFFFF;
    a0 = s2 & 0xFFFF;
    for (;;) {
        // 0x00300654: loop test
        charge(ctx, 4);
        v1 = a1 & 0xFFFF;
        v1 = slt(v1, a0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00300628: v1 = list[i]
        charge(ctx, 6);
        v1 = a1 & 0xFFFF;
        v1 = sll(v1, 1);
        v1 = addu(v0, v1);
        lhu(v1, v1, 0);
        if (s0 == v1) {
            // 0x00300640: found: return 1
            charge(ctx, 3);
            v0 = 1;
            epilogue();
            return;
        }
        // 0x0030064c: ++i
        charge(ctx, 2);
        v1 = addiu(a1, 1);
        a1 = v1 & 0xFFFF;
    }
    // 0x00300664: not in the list; enemies have no accessory
    charge(ctx, 4);
    lhu(v0, s1, dat_unit::kFlags);
    v0 = v0 & dat_unit::kFlagEnemy;
    if (v0 == 0) {
        // 0x00300674: a party member: s1 = (s16)id; a1 = datGetEquipmentIdx(id, 3) (the accessory slot)
        charge(ctx, 10);
        lh(v0, s1, dat_unit::kId);
        s1 = v0;
        a0 = s1;
        a1 = 3;
        jal(ctx, 0x300684u, gen::fn_datGetEquipmentIdx_0016cb80);
        a1 = dsll32(v0, 16);
        a1 = dsra32(a1, 16);
        if (i64(a1) >= 0) {
            // 0x0030069c: v0 = sub_170E40((s16)sub_16F630(id, idx)), the accessory record of the equipped item
            charge(ctx, 10);
            a0 = s1;
            jal(ctx, 0x3006A0u, gen::fn_sub_16F630_0016f630);
            v0 = v0 & 0xFFFF;
            a0 = dsll32(v0, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x3006B4u, gen::fn_sub_170E40_00170e40);
            if (v0 != 0) {
                // 0x003006c4: does the accessory grant the skill (record +28)?
                charge(ctx, 3);
                lw(v0, v0, 28);
                if (v0 == s0) {
                    // 0x003006d0: return 1
                    charge(ctx, 3);
                    v0 = 1;
                    epilogue();
                    return;
                }
            }
        }
    }
    // 0x003006dc: return 0
    charge(ctx, 1);
    v0 = 0;
    epilogue();
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u32 datCalcHasSkill(EEContext& ctx, u32 unit, u32 skill) {
    ee::core::set_gpr64(ctx, GPR_A0, ee::core::sext32(static_cast<u32>(unit)));
    ee::core::set_gpr64(ctx, GPR_A1, ee::core::sext32(static_cast<u32>(skill)));
    datCalcHasSkill(ctx);
    return static_cast<u32>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x00300750 sub_300750 [datCalcHasEquipmentEffect] -- 280 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_300750(pc, effect): the weapon, armour or boots (equipment slots 0..2) of party member `pc` carry `effect`
// (sub_16F900, the item's effect byte); asserts pc < 11 (line 601). Register-faithful (p3fes_handgen body; audit
// 2026-10-21: own frame / spills).
void sub_300750(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld, hg::lq, hg::sd,
          hg::slti, hg::sltiu, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00300750: prologue; s0 = pc, s1 = effect
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s1 = a1;
    v0 = s0 & 0xFFFF;
    v0 = slti(v0, dat_unit::kPartyIds);
    if (v0 == 0) {
        // 0x0030077c: K_Assert(pc < 11)
        charge(ctx, 5);
        k_assert(a0, a1, 0x300788u, kDatCalcFile, 601);
    }
    // 0x00300790: slot 0: (u8)sub_16F900(pc, datGetEquipmentIdx(pc, 0)) == effect?
    charge(ctx, 15);
    s2 = dsll32(s0, 16);
    s2 = dsra32(s2, 16);
    s1 = s1 & 0xFFFF;
    a0 = s2;
    a1 = 0;
    jal(ctx, 0x3007A4u, gen::fn_datGetEquipmentIdx_0016cb80);
    a1 = dsll32(v0, 16);
    a1 = dsra32(a1, 16);
    a0 = s2;
    jal(ctx, 0x3007B8u, gen::fn_sub_16F900_0016f900);
    v0 = v0 & 0xFF;
    if (s1 != v0) {
        // 0x003007d8: slot 1
        charge(ctx, 12);
        a0 = s2;
        a1 = 1;
        jal(ctx, 0x3007E0u, gen::fn_datGetEquipmentIdx_0016cb80);
        a1 = dsll32(v0, 16);
        a1 = dsra32(a1, 16);
        a0 = s2;
        jal(ctx, 0x3007F4u, gen::fn_sub_16F900_0016f900);
        v0 = v0 & 0xFF;
        if (s1 != v0) {
            // 0x00300814: slot 2: return its effect == effect
            charge(ctx, 14);
            s0 = dsll32(s0, 16);
            s0 = dsra32(s0, 16);
            a0 = s0;
            a1 = 2;
            jal(ctx, 0x300824u, gen::fn_datGetEquipmentIdx_0016cb80);
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            a0 = s0;
            jal(ctx, 0x300838u, gen::fn_sub_16F900_0016f900);
            v0 = v0 & 0xFF;
            v0 = s1 ^ v0;
            v0 = sltiu(v0, 1);
        } else {
            // 0x00300808: slot 1 matches: return 1
            charge(ctx, 3);
            v0 = 1;
        }
    } else {
        // 0x003007cc: slot 0 matches: return 1
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x0030084c: epilogue
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003009A0 datCalcCountEquipmentWithEffect -- 328 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// datCalcCountEquipmentWithEffect(unit, effect): 0 for enemies, else how many of the member's equipment slots 0..2
// carry `effect` (asserts id < 11, line 646). Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame).
void datCalcCountEquipmentWithEffect(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lq,
          hg::sd, hg::slti, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003009a0: prologue; s0 = effect
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    lhu(v0, a0, dat_unit::kFlags);
    v0 = v0 & dat_unit::kFlagEnemy;
    if (v0 == 0) {
        // 0x003009d8: a party member: s1 = id; K_Assert(id < 11)
        charge(ctx, 4);
        lhu(s1, a0, dat_unit::kId);
        v0 = slti(s1, dat_unit::kPartyIds);
        if (v0 == 0) {
            // 0x003009e8
            charge(ctx, 5);
            k_assert(a0, a1, 0x3009F4u, kDatCalcFile, 646);
        }
        // 0x003009fc: s2 = count = 0; slot 0: (u8)sub_16F900(id, datGetEquipmentIdx(id, 0)) == effect?
        charge(ctx, 16);
        s2 = 0;
        s3 = dsll32(s1, 16);
        s3 = dsra32(s3, 16);
        s0 = s0 & 0xFFFF;
        a0 = s3;
        a1 = 0;
        jal(ctx, 0x300A14u, gen::fn_datGetEquipmentIdx_0016cb80);
        a1 = dsll32(v0, 16);
        a1 = dsra32(a1, 16);
        a0 = s3;
        jal(ctx, 0x300A28u, gen::fn_sub_16F900_0016f900);
        v0 = v0 & 0xFF;
        if (s0 == v0) {
            // 0x00300a3c: ++count
            charge(ctx, 2);
            v0 = addiu(s2, 1);
            s2 = v0 & 0xFFFF;
        }
        // 0x00300a44: slot 1
        charge(ctx, 14);
        s3 = dsll32(s1, 16);
        s3 = dsra32(s3, 16);
        a0 = s3;
        a1 = 1;
        jal(ctx, 0x300A54u, gen::fn_datGetEquipmentIdx_0016cb80);
        a1 = dsll32(v0, 16);
        a1 = dsra32(a1, 16);
        a0 = s3;
        jal(ctx, 0x300A68u, gen::fn_sub_16F900_0016f900);
        v0 = v0 & 0xFF;
        if (s0 == v0) {
            // 0x00300a7c: ++count
            charge(ctx, 2);
            v0 = addiu(s2, 1);
            s2 = v0 & 0xFFFF;
        }
        // 0x00300a84: slot 2
        charge(ctx, 14);
        s1 = dsll32(s1, 16);
        s1 = dsra32(s1, 16);
        a0 = s1;
        a1 = 2;
        jal(ctx, 0x300A94u, gen::fn_datGetEquipmentIdx_0016cb80);
        a1 = dsll32(v0, 16);
        a1 = dsra32(a1, 16);
        a0 = s1;
        jal(ctx, 0x300AA8u, gen::fn_sub_16F900_0016f900);
        v0 = v0 & 0xFF;
        if (s0 == v0) {
            // 0x00300abc: ++count
            charge(ctx, 2);
            v0 = addiu(s2, 1);
            s2 = v0 & 0xFFFF;
        }
        // 0x00300ac4: return count
        charge(ctx, 1);
        v0 = s2;
    } else {
        // 0x003009cc: an enemy: return 0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00300ac8: epilogue
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u32 datCalcCountEquipmentWithEffect(EEContext& ctx, u32 unit, u32 effect) {
    ee::core::set_gpr64(ctx, GPR_A0, ee::core::sext32(static_cast<u32>(unit)));
    ee::core::set_gpr64(ctx, GPR_A1, ee::core::sext32(static_cast<u32>(effect)));
    datCalcCountEquipmentWithEffect(ctx);
    return static_cast<u32>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x00300B60 sub_300B60 [datCalcGetBaseStat] -- 296 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_300B60(unit, stat): an enemy's EnemyRecord +8 + stat, a party member's sub_173510 (the persona's base stat),
// clamped to 1..99. Asserts stat < 5 (line 737), enemy id < 336 (744), pc < 11 (747). Register-faithful (p3fes_handgen
// body; audit 2026-10-21: own frame / spills).
void sub_300B60(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::i64, hg::jal, hg::lbu, hg::ld, hg::lhu, hg::lq,
          hg::lw, hg::sd, hg::sll, hg::slti, hg::sq, hg::subu;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00300b60: prologue; s2 = unit, s1 = stat
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    v0 = s1 & 0xFFFF;
    // K_Assert(0 <= stat && stat < 5)
    bool stat_ok = false;
    if (i64(v0) >= 0) {
        // 0x00300b88
        charge(ctx, 3);
        v0 = slti(v0, 5);
        stat_ok = v0 != 0;
    }
    if (!stat_ok) {
        // 0x00300b94
        charge(ctx, 5);
        k_assert(a0, a1, 0x300BA0u, kDatCalcFile, 737);
    }
    // 0x00300ba8: s0 = id; enemy or party member?
    charge(ctx, 5);
    lhu(s0, s2, dat_unit::kId);
    lhu(v0, s2, dat_unit::kFlags);
    v0 = v0 & dat_unit::kFlagEnemy;
    if (v0 == 0) {
        // 0x00300c0c: party member: K_Assert(id < 11)
        charge(ctx, 4);
        v0 = s0 & 0xFFFF;
        v0 = slti(v0, dat_unit::kPartyIds);
        if (v0 == 0) {
            // 0x00300c1c
            charge(ctx, 5);
            k_assert(a0, a1, 0x300C28u, kDatCalcFile, 747);
        }
        // 0x00300c30: (u8)sub_173510(id, stat)
        charge(ctx, 5);
        a0 = s0;
        a1 = s1;
        jal(ctx, 0x300C38u, gen::fn_sub_173510_00173510);
        v0 = v0 & 0xFF;
    } else {
        // 0x00300bbc: enemy: K_Assert(id < 336)
        charge(ctx, 4);
        v0 = s0 & 0xFFFF;
        v0 = slti(v0, enemy_rec::kCount);
        if (v0 == 0) {
            // 0x00300bcc
            charge(ctx, 5);
            k_assert(a0, a1, 0x300BD8u, kDatCalcFile, 744);
        }
        // 0x00300be0: gBtlEnemyTbl[id].stats[stat]
        charge(ctx, 11);
        lw(a0, gp, gp_off(btl::kUnitTablePtr));  // gBtlEnemyTbl
        v1 = s0 & 0xFFFF;
        v0 = sll(v1, 5);
        v0 = subu(v0, v1);
        v0 = sll(v0, 1);
        v1 = addu(v0, a0);
        v0 = s1 & 0xFFFF;
        v0 = addu(v0, v1);
        lbu(v0, v0, enemy_rec::kStats);
    }
    // 0x00300c44: clamp to 1..99
    charge(ctx, 3);
    v1 = v0 & 0xFF;
    if (i64(v1) > 0) {
        // 0x00300c5c
        charge(ctx, 3);
        at = slti(v1, 100);
        if (at == 0) {
            // 0x00300c68
            charge(ctx, 1);
            v0 = 99;
        }
    } else {
        // 0x00300c50
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x00300c6c: epilogue
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00300C90 datCalcGetStat -- 232 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// datCalcGetStat(unit, stat): an enemy's sub_300B60, a party member's sub_1738D0 (persona base + bonuses), clamped to
// 1..99. Asserts stat < 5 (line 772) and pc < 11 (779). Register-faithful (p3fes_handgen body; audit 2026-10-21: own
// frame / spills).
void datCalcGetStat(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::i64, hg::jal, hg::ld, hg::lhu, hg::lq, hg::sd, hg::slti,
          hg::sq;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00300c90: prologue; s1 = unit, s0 = stat
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    v0 = s0 & 0xFFFF;
    // K_Assert(0 <= stat && stat < 5)
    bool stat_ok = false;
    if (i64(v0) >= 0) {
        // 0x00300cb4
        charge(ctx, 3);
        v0 = slti(v0, 5);
        stat_ok = v0 != 0;
    }
    if (!stat_ok) {
        // 0x00300cc0
        charge(ctx, 5);
        k_assert(a0, a1, 0x300CCCu, kDatCalcFile, 772);
    }
    // 0x00300cd4: enemy or party member?
    charge(ctx, 4);
    lhu(v0, s1, dat_unit::kFlags);
    v0 = v0 & dat_unit::kFlagEnemy;
    if (v0 == 0) {
        // 0x00300d00: party member: K_Assert(id < 11)
        charge(ctx, 4);
        lhu(v0, s1, dat_unit::kId);
        v0 = slti(v0, dat_unit::kPartyIds);
        if (v0 == 0) {
            // 0x00300d10
            charge(ctx, 5);
            k_assert(a0, a1, 0x300D1Cu, kDatCalcFile, 779);
        }
        // 0x00300d24: (u8)sub_1738D0(id, stat)
        charge(ctx, 5);
        lhu(a0, s1, dat_unit::kId);
        a1 = s0;
        jal(ctx, 0x300D2Cu, gen::fn_sub_1738D0_001738d0);
        v0 = v0 & 0xFF;
    } else {
        // 0x00300ce4: enemy: (u8)sub_300B60(unit, stat)
        charge(ctx, 7);
        a0 = s1;
        a1 = s0;
        jal(ctx, 0x300CECu, gen::fn_sub_300B60_00300b60);
        v0 = v0 & 0xFF;
    }
    // 0x00300d38: clamp to 1..99
    charge(ctx, 3);
    v1 = v0 & 0xFF;
    if (i64(v1) > 0) {
        // 0x00300d50
        charge(ctx, 3);
        at = slti(v1, 100);
        if (at == 0) {
            // 0x00300d5c
            charge(ctx, 1);
            v0 = 99;
        }
    } else {
        // 0x00300d44
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x00300d60: epilogue
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00300D80 datCalcGetPassiveSkillFlags -- 272 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// datCalcGetPassiveSkillFlags(unit): bit i set for each of the skills 547..552, 607, 608 the unit has
// (datCalcHasSkill). Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void datCalcGetPassiveSkillFlags(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00300d80: prologue; s1 = unit, s0 = flags = 0; skill 547 -> bit 0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = 0;
    a1 = 547;
    jal(ctx, 0x300D9Cu, gen::fn_datCalcHasSkill_003005e0);
    if (v0 != 0) {
        // 0x00300dac
        charge(ctx, 1);
        s0 = s0 | 0x1;
    }
    // 0x00300db0: skill 548 -> bit 1
    charge(ctx, 6);
    a0 = s1;
    a1 = 548;
    jal(ctx, 0x300DB8u, gen::fn_datCalcHasSkill_003005e0);
    if (v0 != 0) {
        // 0x00300dc8
        charge(ctx, 1);
        s0 = s0 | 0x2;
    }
    // 0x00300dcc: skill 549 -> bit 2
    charge(ctx, 6);
    a0 = s1;
    a1 = 549;
    jal(ctx, 0x300DD4u, gen::fn_datCalcHasSkill_003005e0);
    if (v0 != 0) {
        // 0x00300de4
        charge(ctx, 1);
        s0 = s0 | 0x4;
    }
    // 0x00300de8: skill 550 -> bit 3
    charge(ctx, 6);
    a0 = s1;
    a1 = 550;
    jal(ctx, 0x300DF0u, gen::fn_datCalcHasSkill_003005e0);
    if (v0 != 0) {
        // 0x00300e00
        charge(ctx, 1);
        s0 = s0 | 0x8;
    }
    // 0x00300e04: skill 551 -> bit 4
    charge(ctx, 6);
    a0 = s1;
    a1 = 551;
    jal(ctx, 0x300E0Cu, gen::fn_datCalcHasSkill_003005e0);
    if (v0 != 0) {
        // 0x00300e1c
        charge(ctx, 1);
        s0 = s0 | 0x10;
    }
    // 0x00300e20: skill 552 -> bit 5
    charge(ctx, 6);
    a0 = s1;
    a1 = 552;
    jal(ctx, 0x300E28u, gen::fn_datCalcHasSkill_003005e0);
    if (v0 != 0) {
        // 0x00300e38
        charge(ctx, 1);
        s0 = s0 | 0x20;
    }
    // 0x00300e3c: skill 607 -> bit 6
    charge(ctx, 6);
    a0 = s1;
    a1 = 607;
    jal(ctx, 0x300E44u, gen::fn_datCalcHasSkill_003005e0);
    if (v0 != 0) {
        // 0x00300e54
        charge(ctx, 1);
        s0 = s0 | 0x40;
    }
    // 0x00300e58: skill 608 -> bit 7
    charge(ctx, 6);
    a0 = s1;
    a1 = 608;
    jal(ctx, 0x300E60u, gen::fn_datCalcHasSkill_003005e0);
    if (v0 != 0) {
        // 0x00300e70
        charge(ctx, 1);
        s0 = s0 | 0x80;
    }
    // 0x00300e74: return flags; epilogue
    charge(ctx, 7);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00301030 datCalcSetEffectLevel -- 276 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// datCalcSetEffectLevel(unit, slot, level): the signed nibble of slot 0..16 in unit +0x1C + slot / 2 (even slot low
// nibble, odd slot high), -7..7 stored as level, or level + 15 when negative. Asserts slot < 21 (line 1080) and
// -8 < level < 8 (1081). Leaves $v0 alone. Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame).
void datCalcSetEffectLevel(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::i64, hg::lbu, hg::ld,
          hg::lq, hg::sb, hg::sd, hg::sll, hg::slti, hg::sq, hg::sra;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00301030: prologue; s2 = unit, s1 = level, s0 = slot (u8)
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a2;
    s0 = a1 & 0xFF;
    v1 = slti(s0, btl::kEffectSlots);
    if (v1 == 0) {
        // 0x00301060: K_Assert(slot < 21)
        charge(ctx, 5);
        k_assert(a0, a1, 0x30106Cu, kDatCalcFile, 1080);
    }
    // 0x00301074: s3 = (s8)level; K_Assert(-7 <= level && level < 8)
    charge(ctx, 5);
    s3 = dsll32(s1, 24);
    s3 = dsra32(s3, 24);
    at = slti(s3, 8);
    bool level_ok = false;
    if (at != 0) {
        // 0x00301088
        charge(ctx, 3);
        at = slti(s3, -7);
        level_ok = at == 0;
    }
    if (!level_ok) {
        // 0x00301094
        charge(ctx, 5);
        k_assert(a0, a1, 0x3010A0u, kDatCalcFile, 1081);
    }
    // 0x003010a8: a0 = slot / 2 (the byte); a negative level is stored as level + 15
    charge(ctx, 4);
    v1 = sra(s0, 1);
    a0 = v1 & 0xFFFF;
    if (i64(s3) < 0) {
        // 0x003010b8
        charge(ctx, 3);
        v1 = addiu(s3, 15);
        s1 = dsll32(v1, 24);
        s1 = dsra32(s1, 24);
    }
    // 0x003010c4: even slot -> low nibble, odd slot -> high nibble of effect_level[slot / 2]
    charge(ctx, 3);
    v1 = s0 & 0x1;
    if (v1 == 0) {
        // 0x00301100: byte = (byte & 0xF0) | (level & 0xF)
        charge(ctx, 9);
        v1 = a0 & 0xFFFF;
        a1 = addu(v1, s2);
        lbu(v1, a1, dat_unit::kEffectLevel);
        a0 = v1 & 0xF0;
        v1 = dsll32(s1, 24);
        v1 = dsra32(v1, 24);
        v1 = v1 & 0xF;
        v1 = a0 | v1;
        sb(v1, a1, dat_unit::kEffectLevel);
    } else {
        // 0x003010d0: byte = (byte & 0x0F) | (level & 0xF) << 4
        charge(ctx, 12);
        v1 = a0 & 0xFFFF;
        a1 = addu(v1, s2);
        lbu(v1, a1, dat_unit::kEffectLevel);
        a0 = v1 & 0xF;
        v1 = dsll32(s1, 24);
        v1 = dsra32(v1, 24);
        v1 = v1 & 0xF;
        v1 = sll(v1, 4);
        v1 = a0 | v1;
        sb(v1, a1, dat_unit::kEffectLevel);
    }
    // 0x00301124: epilogue
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00301150 sub_301150 [datCalcSetEffectTurns] -- 224 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_301150(unit, slot, turns): the 4-bit turn counter of the slot in unit +0x29 + slot / 2 (even slot low nibble,
// odd high). Asserts slot < 21 (line 1109) and turns >= 0 (1110). Leaves $v0 alone. Register-faithful (p3fes_handgen
// body; audit 2026-10-21: own frame / spills).
void sub_301150(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::i64, hg::lbu, hg::ld,
          hg::lq, hg::sb, hg::sd, hg::sll, hg::slti, hg::sq, hg::sra;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00301150: prologue; s1 = unit, s2 = slot, s0 = turns
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s2 = a1;
    s0 = a2;
    v1 = s2 & 0xFF;
    v1 = slti(v1, btl::kEffectSlots);
    if (v1 == 0) {
        // 0x00301180: K_Assert(slot < 21)
        charge(ctx, 5);
        k_assert(a0, a1, 0x30118Cu, kDatCalcFile, 1109);
    }
    // 0x00301194: s0 = (s8)turns; K_Assert(turns >= 0)
    charge(ctx, 4);
    s0 = dsll32(s0, 24);
    s0 = dsra32(s0, 24);
    if (i64(s0) < 0) {
        // 0x003011a4
        charge(ctx, 5);
        k_assert(a0, a1, 0x3011B0u, kDatCalcFile, 1110);
    }
    // 0x003011b8: a0 = slot / 2; even slot -> low nibble, odd -> high nibble of effect_turns[slot / 2]
    charge(ctx, 6);
    a1 = s2 & 0xFF;
    v1 = sra(a1, 1);
    a0 = v1 & 0xFFFF;
    v1 = a1 & 0x1;
    if (v1 == 0) {
        // 0x003011f8: byte = (byte & 0xF0) | (turns & 0xF)
        charge(ctx, 7);
        v1 = a0 & 0xFFFF;
        a1 = addu(v1, s1);
        lbu(v1, a1, dat_unit::kEffectTurns);
        a0 = v1 & 0xF0;
        v1 = s0 & 0xF;
        v1 = a0 | v1;
        sb(v1, a1, dat_unit::kEffectTurns);
    } else {
        // 0x003011d0: byte = (byte & 0x0F) | (turns & 0xF) << 4
        charge(ctx, 10);
        v1 = a0 & 0xFFFF;
        a1 = addu(v1, s1);
        lbu(v1, a1, dat_unit::kEffectTurns);
        a0 = v1 & 0xF;
        v1 = s0 & 0xF;
        v1 = sll(v1, 4);
        v1 = a0 | v1;
        sb(v1, a1, dat_unit::kEffectTurns);
    }
    // 0x00301214: epilogue
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00301230 datCalcAddEffectLevel -- 784 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// datCalcAddEffectLevel(unit, slot, delta): for slots 0..16 the new level is clamp(level + delta, -1, 1) (one step of
// buff or debuff, a second one of the other kind cancels), stored (datCalcSetEffectLevel inlined, its asserts 1080 /
// 1081 included), its +0x14 bit set when non-zero and cleared when zero, and the slot's turn counter reset
// (sub_301150 inlined, assert 1109); delta 0 only returns the level. Slots 17..20 only set their bit and return 0.
// Asserts slot < 21 (1133, and the inlined datCalcGetEffectLevel's 1030). Returns the (s8) level.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void datCalcAddEffectLevel(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::i64, hg::lbu, hg::ld,
          hg::lq, hg::lw, hg::nor, hg::sb, hg::sd, hg::si, hg::sll, hg::sllv, hg::slti, hg::sq, hg::sra, hg::sw;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00301230: prologue; s5 = unit, s1 = slot, s0 = delta, s2 = (u8)slot
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    s1 = a1;
    s0 = a2;
    s2 = s1 & 0xFF;
    v0 = slti(s2, btl::kEffectSlots);
    if (v0 == 0) {
        // 0x00301270: K_Assert(slot < 21)
        charge(ctx, 5);
        k_assert(a0, a1, 0x30127Cu, kDatCalcFile, 1133);
    }
    // 0x00301284: s4 = new level = 0
    charge(ctx, 4);
    s4 = 0;
    at = slti(s2, 17);
    if (at == 0) {
        // 0x003014f8: slots 17..20 are flags only: effect_flags |= 1 << slot
        charge(ctx, 5);
        v0 = 1;
        v1 = sllv(v0, s2);
        lw(v0, s5, dat_unit::kEffectFlags);
        v0 = v0 | v1;
        sw(v0, s5, dat_unit::kEffectFlags);
        // 0x0030150c: return (s8)new level (0)
        charge(ctx, 2);
        v0 = dsll32(s4, 24);
        v0 = dsra32(v0, 24);
    } else {
        // 0x00301294: read the current level (datCalcGetEffectLevel inlined): K_Assert(slot < 21)
        charge(ctx, 3);
        v0 = slti(s2, btl::kEffectSlots);
        if (v0 == 0) {
            // 0x003012a0
            charge(ctx, 5);
            k_assert(a0, a1, 0x3012ACu, kDatCalcFile, 1030);
        }
        // 0x003012b4: s1 = slot / 2 (the byte), s6 = slot & 1 (the nibble)
        charge(ctx, 6);
        v1 = s1 & 0xFF;
        s1 = sra(v1, 1);
        v0 = s1 & 0xFFFF;
        s6 = v1 & 0x1;
        if (s6 == 0) {
            // 0x003012ec: even slot: the low nibble
            charge(ctx, 6);
            v0 = v0 & 0xFFFF;
            v0 = addu(v0, s5);
            lbu(v0, v0, dat_unit::kEffectLevel);
            v0 = v0 & 0xF;
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
        } else {
            // 0x003012cc: odd slot: the high nibble
            charge(ctx, 8);
            v0 = v0 & 0xFFFF;
            v0 = addu(v0, s5);
            lbu(v0, v0, dat_unit::kEffectLevel);
            v0 = sra(v0, 4);
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
        }
        // 0x00301304: a nibble of 8..15 is the negative level nibble - 15
        charge(ctx, 5);
        v0 = dsll32(v0, 24);
        v0 = dsra32(v0, 24);
        at = slti(v0, 8);
        if (at == 0) {
            // 0x00301318
            charge(ctx, 3);
            v0 = addiu(v0, -15);
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
        }
        // 0x00301324: v1 = (s8)level, v0 = (s8)delta
        charge(ctx, 6);
        v1 = dsll32(v0, 24);
        v1 = dsra32(v1, 24);
        v0 = dsll32(s0, 24);
        v0 = dsra32(v0, 24);
        if (v0 != 0) {
            // 0x0030134c: s4 = clamp((s16)(level + delta), -1, 1)
            charge(ctx, 6);
            v0 = addu(v1, v0);
            s4 = dsll32(v0, 16);
            s4 = dsra32(s4, 16);
            at = slti(s4, 2);
            if (at != 0) {
                // 0x00301370
                charge(ctx, 3);
                at = slti(s4, -1);
                if (at != 0) {
                    // 0x0030137c
                    charge(ctx, 1);
                    s4 = si(-1);
                }
            } else {
                // 0x00301364
                charge(ctx, 3);
                s4 = 1;
            }
            // 0x00301380: store it (datCalcSetEffectLevel inlined): s3 = (s8)new level; K_Assert(slot < 21)
            charge(ctx, 5);
            s3 = dsll32(s4, 24);
            s3 = dsra32(s3, 24);
            v0 = slti(s2, btl::kEffectSlots);
            if (v0 == 0) {
                // 0x00301394
                charge(ctx, 5);
                k_assert(a0, a1, 0x3013A0u, kDatCalcFile, 1080);
            }
            // 0x003013a8: K_Assert(-7 <= level && level < 8)
            charge(ctx, 5);
            s0 = dsll32(s3, 24);
            s0 = dsra32(s0, 24);
            at = slti(s0, 8);
            bool level_ok = false;
            if (at != 0) {
                // 0x003013bc
                charge(ctx, 3);
                at = slti(s0, -7);
                level_ok = at == 0;
            }
            if (!level_ok) {
                // 0x003013c8
                charge(ctx, 5);
                k_assert(a0, a1, 0x3013D4u, kDatCalcFile, 1081);
            }
            // 0x003013dc: a negative level is stored as level + 15
            charge(ctx, 3);
            v1 = s1 & 0xFFFF;
            if (i64(s0) < 0) {
                // 0x003013e8
                charge(ctx, 3);
                v0 = addiu(s0, 15);
                s3 = dsll32(v0, 24);
                s3 = dsra32(s3, 24);
            }
            // 0x003013f4
            charge(ctx, 2);
            if (s6 == 0) {
                // 0x0030142c: even slot: byte = (byte & 0xF0) | (level & 0xF)
                charge(ctx, 9);
                v0 = v1 & 0xFFFF;
                a0 = addu(v0, s5);
                lbu(v0, a0, dat_unit::kEffectLevel);
                v1 = v0 & 0xF0;
                v0 = dsll32(s3, 24);
                v0 = dsra32(v0, 24);
                v0 = v0 & 0xF;
                v0 = v1 | v0;
                sb(v0, a0, dat_unit::kEffectLevel);
            } else {
                // 0x003013fc: odd slot: byte = (byte & 0x0F) | (level & 0xF) << 4
                charge(ctx, 12);
                v0 = v1 & 0xFFFF;
                a0 = addu(v0, s5);
                lbu(v0, a0, dat_unit::kEffectLevel);
                v1 = v0 & 0xF;
                v0 = dsll32(s3, 24);
                v0 = dsra32(v0, 24);
                v0 = v0 & 0xF;
                v0 = sll(v0, 4);
                v0 = v1 | v0;
                sb(v0, a0, dat_unit::kEffectLevel);
            }
            // 0x00301450: the slot's flag bit follows the level
            charge(ctx, 4);
            v0 = dsll32(s4, 16);
            v0 = dsra32(v0, 16);
            if (v0 != 0) {
                // 0x00301480: effect_flags |= 1 << slot
                charge(ctx, 5);
                v0 = 1;
                v1 = sllv(v0, s2);
                lw(v0, s5, dat_unit::kEffectFlags);
                v0 = v0 | v1;
                sw(v0, s5, dat_unit::kEffectFlags);
            } else {
                // 0x00301460: effect_flags &= ~(1 << slot)
                charge(ctx, 8);
                v0 = 1;
                v0 = sllv(v0, s2);
                v1 = nor(v0, 0);
                lw(v0, s5, dat_unit::kEffectFlags);
                v0 = v0 & v1;
                sw(v0, s5, dat_unit::kEffectFlags);
            }
            // 0x00301494: reset the turn counter (sub_301150 inlined with 0): K_Assert(slot < 21)
            charge(ctx, 3);
            v0 = slti(s2, btl::kEffectSlots);
            if (v0 == 0) {
                // 0x003014a0
                charge(ctx, 5);
                k_assert(a0, a1, 0x3014ACu, kDatCalcFile, 1109);
            }
            // 0x003014b4
            charge(ctx, 3);
            v0 = s1 & 0xFFFF;
            if (s6 == 0) {
                // 0x003014dc: even slot: low nibble = 0
                charge(ctx, 7);
                v0 = v0 & 0xFFFF;
                v1 = addu(v0, s5);
                lbu(v0, v1, dat_unit::kEffectTurns);
                v0 = v0 & 0xF0;
                sb(v0, v1, dat_unit::kEffectTurns);
            } else {
                // 0x003014c0: odd slot: high nibble = 0
                charge(ctx, 7);
                v0 = v0 & 0xFFFF;
                v1 = addu(v0, s5);
                lbu(v0, v1, dat_unit::kEffectTurns);
                v0 = v0 & 0xF;
                sb(v0, v1, dat_unit::kEffectTurns);
            }
            // 0x0030150c: return (s8)new level
            charge(ctx, 2);
            v0 = dsll32(s4, 24);
            v0 = dsra32(v0, 24);
        } else {
            // 0x0030133c: delta 0: return (s8)level unchanged
            charge(ctx, 4);
            v0 = dsll32(v1, 24);
            v0 = dsra32(v0, 24);
        }
    }
    // 0x00301514: epilogue
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
}

// 0x00301540 datCalcClearEffect -- 324 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// datCalcClearEffect(unit, slot): the level nibble and the turn nibble (slots 0..16; datCalcSetEffectLevel and
// sub_301150 inlined with 0, their asserts 1080 / 1109 included) and the +0x14 bit. Asserts slot < 21 (1177).
// Leaves $v0 alone. Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void datCalcClearEffect(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::lbu, hg::ld, hg::lq, hg::lw, hg::nor, hg::sb,
          hg::sd, hg::sllv, hg::slti, hg::sq, hg::sra, hg::sw;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00301540: prologue; s3 = unit, s2 = (u8)slot
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1 & 0xFF;
    v1 = slti(s2, btl::kEffectSlots);
    if (v1 == 0) {
        // 0x0030156c: K_Assert(slot < 21)
        charge(ctx, 5);
        k_assert(a0, a1, 0x301578u, kDatCalcFile, 1177);
    }
    // 0x00301580
    charge(ctx, 3);
    at = slti(s2, 17);
    if (at != 0) {
        // 0x0030158c: a levelled slot: clear the level nibble; K_Assert(slot < 21)
        charge(ctx, 3);
        v1 = slti(s2, btl::kEffectSlots);
        if (v1 == 0) {
            // 0x00301598
            charge(ctx, 5);
            k_assert(a0, a1, 0x3015A4u, kDatCalcFile, 1080);
        }
        // 0x003015ac: s1 = slot / 2, s0 = slot & 1
        charge(ctx, 5);
        s1 = sra(s2, 1);
        v1 = s1 & 0xFFFF;
        s0 = s2 & 0x1;
        if (s0 == 0) {
            // 0x003015dc: even slot: low nibble = 0
            charge(ctx, 5);
            v1 = v1 & 0xFFFF;
            a0 = addu(v1, s3);
            lbu(v1, a0, dat_unit::kEffectLevel);
            v1 = v1 & 0xF0;
            sb(v1, a0, dat_unit::kEffectLevel);
        } else {
            // 0x003015c0: odd slot: high nibble = 0
            charge(ctx, 7);
            v1 = v1 & 0xFFFF;
            a0 = addu(v1, s3);
            lbu(v1, a0, dat_unit::kEffectLevel);
            v1 = v1 & 0xF;
            sb(v1, a0, dat_unit::kEffectLevel);
        }
        // 0x003015f0: clear the turn nibble; K_Assert(slot < 21)
        charge(ctx, 3);
        v1 = slti(s2, btl::kEffectSlots);
        if (v1 == 0) {
            // 0x003015fc
            charge(ctx, 5);
            k_assert(a0, a1, 0x301608u, kDatCalcFile, 1109);
        }
        // 0x00301610
        charge(ctx, 3);
        v1 = s1 & 0xFFFF;
        if (s0 == 0) {
            // 0x00301638: even slot: low nibble = 0
            charge(ctx, 5);
            v1 = v1 & 0xFFFF;
            a0 = addu(v1, s3);
            lbu(v1, a0, dat_unit::kEffectTurns);
            v1 = v1 & 0xF0;
            sb(v1, a0, dat_unit::kEffectTurns);
        } else {
            // 0x0030161c: odd slot: high nibble = 0
            charge(ctx, 7);
            v1 = v1 & 0xFFFF;
            a0 = addu(v1, s3);
            lbu(v1, a0, dat_unit::kEffectTurns);
            v1 = v1 & 0xF;
            sb(v1, a0, dat_unit::kEffectTurns);
        }
    }
    // 0x0030164c: effect_flags &= ~(1 << slot); epilogue
    charge(ctx, 14);
    v1 = 1;
    v1 = sllv(v1, s2);
    a0 = nor(v1, 0);
    lw(v1, s3, dat_unit::kEffectFlags);
    v1 = v1 & a0;
    sw(v1, s3, dat_unit::kEffectFlags);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00301690 datCalcClearAllEffects -- 192 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// datCalcClearAllEffects(unit): for each of the 21 slots, datCalcClearEffect inlined: datCalcSetEffectLevel(unit,
// slot, 0) and sub_301150(unit, slot, 0) for slots 0..16, then the flag bit. Leaves $v0 alone (neither callee writes
// it). Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void datCalcClearAllEffects(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::nor, hg::sd,
          hg::sllv, hg::slti, hg::sltiu, hg::sq, hg::sw;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00301690: prologue; s1 = unit; for (slot = 0; slot < 21; ++slot) (s0 = slot)
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = 0;
    for (;;) {
        // 0x00301728: loop test
        charge(ctx, 3);
        v1 = sltiu(s0, btl::kEffectSlots);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003016b4: s2 = (u8)slot; K_Assert(slot < 21)
        charge(ctx, 4);
        s2 = s0 & 0xFF;
        v1 = slti(s2, btl::kEffectSlots);
        if (v1 == 0) {
            // 0x003016c4
            charge(ctx, 5);
            k_assert(a0, a1, 0x3016D0u, kDatCalcFile, 1177);
        }
        // 0x003016d8
        charge(ctx, 3);
        at = slti(s2, 17);
        if (at != 0) {
            // 0x003016e4: a levelled slot: level 0, turns 0
            charge(ctx, 10);
            a1 = s0 & 0xFF;
            a0 = s1;
            a2 = 0;
            jal(ctx, 0x3016F0u, gen::fn_datCalcSetEffectLevel_00301030);
            a1 = s0 & 0xFF;
            a0 = s1;
            a2 = 0;
            jal(ctx, 0x301704u, gen::fn_sub_301150_00301150);
        }
        // 0x0030170c: effect_flags &= ~(1 << slot); ++slot
        charge(ctx, 7);
        v1 = 1;
        v1 = sllv(v1, s2);
        a0 = nor(v1, 0);
        lw(v1, s1, dat_unit::kEffectFlags);
        v1 = v1 & a0;
        sw(v1, s1, dat_unit::kEffectFlags);
        s0 = addiu(s0, 1);
    }
    // 0x00301734: epilogue
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00301870 sub_301870 [datCalcClearUnk18] -- 12 bytes; leaf frame (no stack)
// sub_301870(unit): unit +0x18 = 0 (the AI's per-turn word; 10 call sites in btlAICommand.c).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: differed only on inputs the original faults on).
void sub_301870(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::sw;
    Gpr zero{ctx, 0}, a0{ctx, 4};
    enter(ctx, 3);  // entry check point + the only block
    sw(zero, a0, dat_unit::kUnk18);
}

// 0x00301880 datCalcGetEffectMultiplier -- 1048 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// datCalcGetEffectMultiplier(unit, slot) -> f32 in $f0: the damage multiplier of the buff in slot 0..4 at its current
// level -1..1, from AICALC.TBL section 5 (u8 percentages, row = 3 * enemy: [row + level + 1] for slots 0/1 (attack,
// times the gp-0x7D60 factor when the unit's attack-type flag 0x80000 / 0x100000 is set), [row + 1 - level] for slot 3
// (defence), [row + 7 - level] for slot 2 and [row + 7 + level] for slot 4); slots 19/20 give that factor when active;
// every other slot 1.0. The level comes from datCalcGetEffectLevel (slots < 17) or the flag bit. Asserts slot < 21
// (1256, 1208) and -1 <= level <= 1 (1260). The compiled code leaves $v0 (the last compared constant, the flag bit or
// 100.0f's pattern) and $f1 (the converted percentage, or the factor) behind.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void datCalcGetEffectMultiplier(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::addu, hg::charge, hg::cvt_s_w, hg::div_s, hg::dsll32,
          hg::dsra32, hg::enter, hg::i64, hg::jal, hg::lbu, hg::ld, hg::lhu, hg::lq, hg::lw, hg::lwc1, hg::mtc1,
          hg::mul_s, hg::sd, hg::sll, hg::sllv, hg::slti, hg::sltu, hg::sq, hg::srl, hg::subu;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x00301880: prologue; s2 = unit, s0 = slot, s1 = (u8)slot; K_Assert(slot < 21) twice (two inlined checks)
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s0 = a1;
    s1 = s0 & 0xFF;
    v0 = slti(s1, btl::kEffectSlots);
    if (v0 == 0) {
        // 0x003018ac
        charge(ctx, 5);
        k_assert(a0, a1, 0x3018B8u, kDatCalcFile, 1256);
    }
    // 0x003018c0
    charge(ctx, 3);
    v0 = slti(s1, btl::kEffectSlots);
    if (v0 == 0) {
        // 0x003018cc
        charge(ctx, 5);
        k_assert(a0, a1, 0x3018D8u, kDatCalcFile, 1208);
    }
    // 0x003018e0: v0 = the slot's level
    charge(ctx, 3);
    at = slti(s1, 17);
    if (at == 0) {
        // 0x00301904: slots 17..20: (s8)((effect_flags >> slot) & 1)
        charge(ctx, 7);
        v0 = 1;
        v1 = sllv(v0, s1);
        lw(v0, s2, dat_unit::kEffectFlags);
        v0 = v0 & v1;
        v0 = sltu(0, v0);
        v0 = dsll32(v0, 24);
        v0 = dsra32(v0, 24);
    } else {
        // 0x003018ec: datCalcGetEffectLevel(unit, slot)
        charge(ctx, 6);
        a0 = s2;
        a1 = s0;
        jal(ctx, 0x3018F4u, gen::fn_datCalcGetEffectLevel_00300f60);
    }
    // 0x00301920: s0 = (s8)level; K_Assert(-1 <= level && level <= 1)
    charge(ctx, 5);
    s0 = dsll32(v0, 24);
    s0 = dsra32(s0, 24);
    v0 = slti(s0, -1);
    bool level_ok = false;
    if (v0 == 0) {
        // 0x00301934
        charge(ctx, 3);
        at = slti(s0, 2);
        level_ok = at != 0;
    }
    if (!level_ok) {
        // 0x00301940
        charge(ctx, 5);
        k_assert(a0, a1, 0x30194Cu, kDatCalcFile, 1260);
    }
    // 0x00301954: v1 = is the unit an enemy (0 / 1, the table row); $f0 = 1.0 (the default); dispatch on the slot
    charge(ctx, 9);
    lhu(v0, s2, dat_unit::kFlags);
    v0 = v0 & dat_unit::kFlagEnemy;
    v0 = sltu(0, v0);
    v1 = v0 & 0xFFFF;
    v0 = flt(1.0f);
    mtc1(v0, f0);
    v0 = 20;
    if (s1 == v0) {
        // 0x00301c70: slot 20: the boost factor when active
        charge(ctx, 2);
        if (i64(s0) > 0) {
            // 0x00301c78
            charge(ctx, 1);
            lwc1(f0, gp, gp_off(btl::kEffectBoostConst));
        }
    } else {
        // 0x00301978
        charge(ctx, 3);
        v0 = 19;
        if (s1 == v0) {
            // 0x00301c5c: slot 19: the boost factor when active
            charge(ctx, 2);
            if (i64(s0) > 0) {
                // 0x00301c64
                charge(ctx, 3);
                lwc1(f0, gp, gp_off(btl::kEffectBoostConst));
            }
        } else {
            // 0x00301984
            charge(ctx, 3);
            v0 = 4;
            if (s1 == v0) {
                // 0x00301be4: slot 4: AICALC5[3 * enemy + 7 + level] / 100
                charge(ctx, 9);
                lw(a0, gp, gp_off(btl::kAicalc5Ptr));
                v1 = v1 & 0xFFFF;
                v0 = sll(v1, 1);
                v0 = addu(v0, v1);
                v0 = addu(v0, a0);
                v0 = addu(s0, v0);
                lbu(v0, v0, 7);
                u32_to_float(v0, v1, f0, f1);  // 0x00301c1c / 0x00301c08
                // 0x00301c38
                charge(ctx, 9);
                v0 = flt(100.0f);
                mtc1(v0, f0);
                div_s(f0, f1, f0);
            } else {
                // 0x00301990
                charge(ctx, 3);
                v0 = 3;
                if (s1 == v0) {
                    // 0x00301b68: slot 3 (defence): AICALC5[3 * enemy + 1 - level] / 100
                    charge(ctx, 10);
                    lw(a0, gp, gp_off(btl::kAicalc5Ptr));
                    v1 = v1 & 0xFFFF;
                    v0 = sll(v1, 1);
                    v0 = addu(v0, v1);
                    v0 = addu(v0, a0);
                    v0 = addiu(v0, 1);
                    v0 = subu(v0, s0);
                    lbu(v0, v0, 0);
                    u32_to_float(v0, v1, f0, f1);  // 0x00301ba4 / 0x00301b90
                    // 0x00301bc0
                    charge(ctx, 9);
                    v0 = flt(100.0f);
                    mtc1(v0, f0);
                    div_s(f0, f1, f0);
                } else {
                    // 0x0030199c
                    charge(ctx, 3);
                    v0 = 2;
                    if (s1 == v0) {
                        // 0x00301aec: slot 2: AICALC5[3 * enemy + 7 - level] / 100
                        charge(ctx, 10);
                        lw(a0, gp, gp_off(btl::kAicalc5Ptr));
                        v1 = v1 & 0xFFFF;
                        v0 = sll(v1, 1);
                        v0 = addu(v0, v1);
                        v0 = addu(v0, a0);
                        v0 = addiu(v0, 7);
                        v0 = subu(v0, s0);
                        lbu(v0, v0, 0);
                        u32_to_float(v0, v1, f0, f1);  // 0x00301b28 / 0x00301b14
                        // 0x00301b44
                        charge(ctx, 9);
                        v0 = flt(100.0f);
                        mtc1(v0, f0);
                        div_s(f0, f1, f0);
                    } else {
                        // 0x003019a8
                        charge(ctx, 3);
                        v0 = 1;
                        if (s1 == v0) {
                            // 0x00301a58: slot 1 (attack): AICALC5[3 * enemy + 1 + level] / 100
                            charge(ctx, 9);
                            lw(a0, gp, gp_off(btl::kAicalc5Ptr));
                            v1 = v1 & 0xFFFF;
                            v0 = sll(v1, 1);
                            v0 = addu(v0, v1);
                            v0 = addu(v0, a0);
                            v0 = addu(s0, v0);
                            lbu(v0, v0, 1);
                            u32_to_float(v0, v1, f0, f1);  // 0x00301a90 / 0x00301a7c
                            // 0x00301aac: ... times the boost factor when effect flag 0x100000 is set
                            charge(ctx, 12);
                            v0 = flt(100.0f);
                            mtc1(v0, f0);
                            div_s(f0, f1, f0);
                            lw(v1, s2, dat_unit::kEffectFlags);
                            v0 = 0x100000;
                            v0 = v1 & v0;
                            v0 = sltu(0, v0);
                            v0 = dsll32(v0, 24);
                            v0 = dsra32(v0, 24);
                            if (i64(v0) > 0) {
                                // 0x00301adc
                                charge(ctx, 4);
                                lwc1(f1, gp, gp_off(btl::kEffectBoostConst));
                                mul_s(f0, f0, f1);
                            }
                        } else {
                            // 0x003019b4
                            charge(ctx, 2);
                            if (s1 == 0) {
                                // 0x003019c4: slot 0 (attack): AICALC5[3 * enemy + 1 + level] / 100
                                charge(ctx, 9);
                                lw(a0, gp, gp_off(btl::kAicalc5Ptr));
                                v1 = v1 & 0xFFFF;
                                v0 = sll(v1, 1);
                                v0 = addu(v0, v1);
                                v0 = addu(v0, a0);
                                v0 = addu(s0, v0);
                                lbu(v0, v0, 1);
                                u32_to_float(v0, v1, f0, f1);  // 0x003019fc / 0x003019e8
                                // 0x00301a18: ... times the boost factor when effect flag 0x80000 is set
                                charge(ctx, 12);
                                v0 = flt(100.0f);
                                mtc1(v0, f0);
                                div_s(f0, f1, f0);
                                lw(v1, s2, dat_unit::kEffectFlags);
                                v0 = 0x80000;
                                v0 = v1 & v0;
                                v0 = sltu(0, v0);
                                v0 = dsll32(v0, 24);
                                v0 = dsra32(v0, 24);
                                if (i64(v0) > 0) {
                                    // 0x00301a48
                                    charge(ctx, 4);
                                    lwc1(f1, gp, gp_off(btl::kEffectBoostConst));
                                    mul_s(f0, f0, f1);
                                }
                            } else {
                                // 0x003019bc: any other slot: 1.0
                                charge(ctx, 2);
                            }
                        }
                    }
                }
            }
        }
    }
    // 0x00301c7c: epilogue (the result in $f0)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// =================================================================================================================
// datScript.c
// =================================================================================================================

u32 sub_311180(EEContext& ctx) {  // 0x311180: returns 1
    guest::enter(ctx, 3);
    return 1;
}

// 0x00311190 datScriptSetResult -- 36 bytes; leaf frame (no stack)
// datScriptSetResult(value): gDatScriptResult = value, result-valid bit (0x9571A4 bit 0) set. Leaves $v0 alone.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void datScriptSetResult(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lhu, hg::sh, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    enter(ctx, 9);  // entry check point + the only block
    v1 = hi(ai::kFlags);
    lhu(v1, v1, lo(ai::kFlags));
    a1 = v1 | 0x1;  // flags |= result valid
    v1 = hi(ai::kFlags);
    sh(a1, v1, lo(ai::kFlags));
    v1 = hi(ai::kResult);
    sw(a0, v1, lo(ai::kResult));  // gDatScriptResult = value
}

// 0x003111F0 sub_3111F0 [datScriptIsNotEnemy] -- 84 bytes; frame 0x10: ra sp+0x0
// sub_3111F0(): the datScript attacker is a party member: !(gDatScriptAttacker->flags & enemy) (asserts an attacker,
// line 517). Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void sub_3111F0_regs(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::ld, hg::lhu, hg::lw, hg::sd, hg::sltu;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003111f0: prologue; K_Assert(gDatScriptAttacker)
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = hi(ai::kAttacker);
    lw(v0, v0, lo(ai::kAttacker));
    if (v0 == 0) {
        // 0x00311208
        charge(ctx, 5);
        k_assert(a0, a1, 0x311214u, kDatScriptFile, 517);
    }
    // 0x0031121c: return (attacker->flags & enemy) == 0; epilogue
    charge(ctx, 10);
    v0 = hi(ai::kAttacker);
    lw(v0, v0, lo(ai::kAttacker));
    lhu(v0, v0, dat_unit::kFlags);
    v0 = v0 & dat_unit::kFlagEnemy;
    v0 = sltu(0, v0);
    v0 = v0 ^ 0x1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00311250 sub_311250 [datScriptIsPhysicalSkill] -- 112 bytes; frame 0x10: ra sp+0x0
// sub_311250(): SkillRecord[gDatScriptSkill].flags0 bit 1, the skill is physical (asserts skill < 464, line 546).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void sub_311250_regs(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::lbu, hg::ld, hg::lhu, hg::lw, hg::sd, hg::sll,
          hg::slti, hg::sltu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00311250: prologue; K_Assert(gDatScriptSkill < 464)
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = hi(ai::kSkill);
    lhu(v0, v0, lo(ai::kSkill));
    v0 = slti(v0, btl::kSkillCount);
    if (v0 == 0) {
        // 0x0031126c
        charge(ctx, 5);
        k_assert(a0, a1, 0x311278u, kDatScriptFile, 546);
    }
    // 0x00311280: return (gBtlSkillTbl[skill].flags0 & 2) != 0 (44-byte records: ((skill * 5) * 2 + skill) << 2);
    // epilogue
    charge(ctx, 16);
    v0 = hi(ai::kSkill);
    lhu(v1, v0, lo(ai::kSkill));
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    v0 = addu(v0, v1);
    v1 = sll(v0, 2);
    lw(v0, gp, gp_off(btl::kSkillTablePtr));  // gBtlSkillTbl
    v0 = addu(v0, v1);
    lbu(v0, v0, skill_rec::kFlags0);
    v0 = v0 & skill_rec::kFlagPhysical;
    v0 = sltu(0, v0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x3112C0(value): the word at 0x7CE514 (sign-extended) equals the 64-bit argument.
u32 sub_3112C0(EEContext& ctx, u64 value) {
    guest::enter(ctx, 5);
    return sx64(guest::load<u32>(ctx, kBtlCompareWord)) == value ? 1u : 0u;
}

// =================================================================================================================
// btl root (gBtl flags, outcome, packets)
// =================================================================================================================

// 0x0027D380 btlMainCheckBattleEnd -- 468 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// btlMainCheckBattleEnd(): outcome gBtl+0x1C = 0 at entry; over the active actions (+26 bit 0, not +24 bit 5) it
// counts dead units (datCalcIsDead), standing enemies (btlUnit +162 == 1) and standing party members (+162 == 0).
// Outcome 2 (lose) when sub_2BFC90() is 0, the hero (id 1) is dead, or no party member stands and some unit died; 3
// when no party member stands and nobody died; 1 (win) when the boss rule sub_2FD660() says so or no enemy stands.
// Returns 1 when the battle is over, 0 to go on (21_battle.md section 1.4).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void btlMainCheckBattleEnd_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lhu, hg::lq, hg::lw,
          hg::sd, hg::sh, hg::sq;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027d380: prologue; gBtl->outcome = 0; s3 = party standing, s2 = enemies standing, s1 = dead = 0,
    // s5 = hero alive = 1; is the party present (sub_2BFC90)?
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, gp_off(btl::kBtlPtr));  // gBtl
    sh(zero, v0, btl_root::kOutcome);
    s3 = 0;
    s2 = 0;
    s1 = 0;
    s5 = 1;
    jal(ctx, 0x27D3B8u, gen::fn_sub_2BFC90_002bfc90);
    if (v0 != 0) {
        // 0x0027d3e0: for (s4 = gBtl->action_list; s4; s4 = s4->next)
        charge(ctx, 4);
        lw(v0, gp, gp_off(btl::kBtlPtr));
        lw(s4, v0, btl_root::kActionList);
        for (;;) {
            // 0x0027d490: loop test
            charge(ctx, 2);
            if (s4 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0027d3f0: a combatant (flags2 bit 0) ...
            charge(ctx, 4);
            lhu(v0, s4, action::kFlags2);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                // 0x0027d400: ... not flagged 0x20 ...
                charge(ctx, 4);
                lhu(v0, s4, action::kFlags);
                v0 = v0 & 0x20;
                if (v0 == 0) {
                    // 0x0027d410: s0 = its btlUnit; datCalcIsDead(unit->dat, 0)?
                    charge(ctx, 7);
                    lw(s0, s4, action::kUnit);
                    lw(a0, s0, btl_unit::kDat);
                    a1 = 0;
                    jal(ctx, 0x27D41Cu, gen::fn_datCalcIsDead_0030b5a0);
                    if (v0 == 0) {
                        // 0x0027d45c: standing: count it by side
                        charge(ctx, 4);
                        lbu(v1, s0, btl_unit::kSide);
                        v0 = 1;
                        if (v1 == v0) {
                            // 0x0027d488: an enemy
                            charge(ctx, 1);
                            s2 = addiu(s2, 1);
                        } else {
                            // 0x0027d46c
                            charge(ctx, 2);
                            if (v1 == 0) {
                                // 0x0027d47c: a party member
                                charge(ctx, 3);
                                s3 = addiu(s3, 1);
                            } else {
                                // 0x0027d474
                                charge(ctx, 2);
                            }
                        }
                    } else {
                        // 0x0027d42c: dead: a dead party member with id 1 is the hero
                        charge(ctx, 3);
                        lbu(v0, s0, btl_unit::kSide);
                        if (v0 == 0) {
                            // 0x0027d438
                            charge(ctx, 5);
                            lw(v0, s0, btl_unit::kDat);
                            lhu(v1, v0, dat_unit::kId);
                            v0 = dat_unit::kHero;
                            if (v1 == v0) {
                                // 0x0027d44c: hero alive = 0
                                charge(ctx, 1);
                                s5 = 0;
                            }
                        }
                        // 0x0027d450: ++dead
                        charge(ctx, 3);
                        s1 = addiu(s1, 1);
                    }
                }
            }
            // 0x0027d48c: next action
            charge(ctx, 1);
            lw(s4, s4, action::kNextInList);
        }
        // 0x0027d498: lost when the hero is dead, or nobody of the party stands and somebody died
        charge(ctx, 2);
        bool lose = s5 == 0;
        if (!lose) {
            // 0x0027d4a0
            charge(ctx, 2);
            if (s3 == 0) {
                // 0x0027d4a8
                charge(ctx, 2);
                lose = s1 != 0;
            }
        }
        if (!lose) {
            // 0x0027d4c8
            charge(ctx, 2);
            if (s3 != 0) {
                // 0x0027d4e8: the party stands: the boss rule sub_2FD660(), else no enemy left -> outcome 1
                charge(ctx, 4);
                jal(ctx, 0x27D4E8u, gen::fn_sub_2FD660_002fd660);
                if (v0 == 0) {
                    // 0x0027d50c
                    charge(ctx, 2);
                    if (s2 != 0) {
                        // 0x0027d528: enemies stand: go on (return 0)
                        charge(ctx, 1);
                        v0 = 0;
                    } else {
                        // 0x0027d514: outcome 1 (win); return 1
                        charge(ctx, 5);
                        v0 = 1;
                        lw(v1, gp, gp_off(btl::kBtlPtr));
                        sh(v0, v1, btl_root::kOutcome);
                    }
                } else {
                    // 0x0027d4f8: the boss rule ends it: outcome 1; return 1
                    charge(ctx, 5);
                    v0 = 1;
                    lw(v1, gp, gp_off(btl::kBtlPtr));
                    sh(v0, v1, btl_root::kOutcome);
                }
            } else {
                // 0x0027d4d0: nobody of the party stands and nobody died: outcome 3; return 1
                charge(ctx, 6);
                v1 = 3;
                lw(v0, gp, gp_off(btl::kBtlPtr));
                sh(v1, v0, btl_root::kOutcome);
                v0 = 1;
            }
        } else {
            // 0x0027d4b0: outcome 2 (lose); return 1
            charge(ctx, 6);
            v1 = 2;
            lw(v0, gp, gp_off(btl::kBtlPtr));
            sh(v1, v0, btl_root::kOutcome);
            v0 = 1;
        }
    } else {
        // 0x0027d3c8: no party: outcome 2; return s5 (1)
        charge(ctx, 6);
        v1 = 2;
        lw(v0, gp, gp_off(btl::kBtlPtr));
        sh(v1, v0, btl_root::kOutcome);
        v0 = s5;
    }
    // 0x0027d52c: epilogue
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

// 0x27D880 [btlGetTask]: the root "battle" task (gBtl + 0xD18), or 0 outside a battle.
u32 sub_27D880(EEContext& ctx) {
    guest::enter(ctx, 3);
    const u32 g = gbtl(ctx);
    u32 r;
    if (g == 0) {
        guest::charge(ctx, 1);
        r = 0;
    } else {
        guest::charge(ctx, 3);
        r = guest::load<u32>(ctx, g + kBtlTask);
    }
    guest::charge(ctx, 2);
    return r;
}

// 0x0027D8B0 sub_27D8B0 [btlSetFlag8000] -- 24 bytes; leaf frame (no stack)
// sub_27D8B0(): gBtl->flags |= 0x8000. Leaves $v0 alone. Register-faithful (p3fes_handgen body; audit 2026-10-21:
// scratch GPRs).
void sub_27D8B0(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    enter(ctx, 6);  // entry check point + the only block
    lw(a0, gp, gp_off(btl::kBtlPtr));  // gBtl
    lw(v1, a0, btl_root::kFlags);
    v1 = v1 | 0x8000;
    sw(v1, a0, btl_root::kFlags);
}

// 0x0027DBE0 sub_27DBE0 [btlUpdateSetFlagsPacket] -- 32 bytes; leaf frame (no stack)
// sub_27DBE0(payload): gBtl->flags |= payload word 0; returns 1 (the packet is done). Register-faithful
// (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_27DBE0(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    enter(ctx, 8);  // entry check point + the only block
    lw(a1, gp, gp_off(btl::kBtlPtr));  // gBtl
    lw(v1, a1, btl_root::kFlags);
    lw(v0, a0, 0);
    v0 = v1 | v0;
    sw(v0, a1, btl_root::kFlags);
    v0 = 1;
}

// 0x0027DC50 sub_27DC50 [btlUpdateClearFlagsPacket] -- 36 bytes; leaf frame (no stack)
// sub_27DC50(payload): gBtl->flags &= ~payload word 0; returns 1. Register-faithful (p3fes_handgen body; audit
// 2026-10-21: scratch GPRs).
void sub_27DC50(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::nor, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    enter(ctx, 9);  // entry check point + the only block
    lw(a1, gp, gp_off(btl::kBtlPtr));  // gBtl
    lw(v0, a0, 0);
    v1 = nor(v0, 0);
    lw(v0, a1, btl_root::kFlags);
    v0 = v0 & v1;
    sw(v0, a1, btl_root::kFlags);
    v0 = 1;
}

// 0x0027E310 sub_27E310 [btlPacketFindByKey] -- 116 bytes; leaf frame (no stack)
// sub_27E310(key, mask): the first active packet (flags +71 bit 5) of gBtl's four queues whose 64-bit id (+88) & mask
// == key, or 0. Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void sub_27E310(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lbu, hg::ld, hg::lw, hg::sll,
          hg::sltiu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28};
    // 0x0027e310: a2 = gBtl; for (q = 0; q < 4; ++q) (a3 = q)
    enter(ctx, 4);  // entry check point + this block's cycles
    a3 = 0;
    lw(a2, gp, gp_off(btl::kBtlPtr));  // gBtl
    for (;;) {
        // 0x0027e36c: outer loop test
        charge(ctx, 3);
        v0 = sltiu(a3, btl_root::kPacketQueueCount);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0027e320: for (v0 = gBtl->queues[q]; v0; v0 = v0->next)
        charge(ctx, 5);
        v0 = sll(a3, 3);
        v0 = addu(a2, v0);
        lw(v0, v0, btl_root::kPacketQueues);
        for (;;) {
            // 0x0027e360: inner loop test
            charge(ctx, 2);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0027e334: (id & mask) == key?
            charge(ctx, 4);
            ld(v1, v0, packet::kId);
            v1 = v1 & a1;
            if (a0 == v1) {
                // 0x0027e344: and active?
                charge(ctx, 4);
                lbu(v1, v0, packet::kFlags);
                v1 = v1 & packet::kFlagActive;
                if (v1 != 0) {
                    // 0x0027e354, 0x0027e37c: found: return the packet ($v0)
                    charge(ctx, 2);
                    charge(ctx, 2);
                    return;
                }
            }
            // 0x0027e35c: next packet
            charge(ctx, 1);
            lw(v0, v0, packet::kNext);
        }
        // 0x0027e368: ++q
        charge(ctx, 1);
        a3 = addiu(a3, 1);
    }
    // 0x0027e378, 0x0027e37c: none: return 0
    charge(ctx, 1);
    v0 = 0;
    charge(ctx, 2);
}

// 0x0027E390 sub_27E390 [btlPacketFindByOwner] -- 116 bytes; leaf frame (no stack)
// sub_27E390(uid, mask): sub_27E310 on the owner field: the first active packet whose 64-bit owner (+96, an action
// uid) & mask == uid, or 0. Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void sub_27E390(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lbu, hg::ld, hg::lw, hg::sll,
          hg::sltiu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28};
    // 0x0027e390: a2 = gBtl; for (q = 0; q < 4; ++q) (a3 = q)
    enter(ctx, 4);  // entry check point + this block's cycles
    a3 = 0;
    lw(a2, gp, gp_off(btl::kBtlPtr));  // gBtl
    for (;;) {
        // 0x0027e3ec: outer loop test
        charge(ctx, 3);
        v0 = sltiu(a3, btl_root::kPacketQueueCount);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0027e3a0: for (v0 = gBtl->queues[q]; v0; v0 = v0->next)
        charge(ctx, 5);
        v0 = sll(a3, 3);
        v0 = addu(a2, v0);
        lw(v0, v0, btl_root::kPacketQueues);
        for (;;) {
            // 0x0027e3e0: inner loop test
            charge(ctx, 2);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0027e3b4: (owner & mask) == uid?
            charge(ctx, 4);
            ld(v1, v0, packet::kOwner);
            v1 = v1 & a1;
            if (a0 == v1) {
                // 0x0027e3c4: and active?
                charge(ctx, 4);
                lbu(v1, v0, packet::kFlags);
                v1 = v1 & packet::kFlagActive;
                if (v1 != 0) {
                    // 0x0027e3d4, 0x0027e3fc: found: return the packet ($v0)
                    charge(ctx, 2);
                    charge(ctx, 2);
                    return;
                }
            }
            // 0x0027e3dc: next packet
            charge(ctx, 1);
            lw(v0, v0, packet::kNext);
        }
        // 0x0027e3e8: ++q
        charge(ctx, 1);
        a3 = addiu(a3, 1);
    }
    // 0x0027e3f8, 0x0027e3fc: none: return 0
    charge(ctx, 1);
    v0 = 0;
    charge(ctx, 2);
}

// =================================================================================================================
// btlAction.c / btlMain: lists and state drivers
// =================================================================================================================

// 0x00299D60 btlActionSetState -- 80 bytes; frame 0x10: ra sp+0x0
// btlActionSetState(action, state): previous = state field, state = s, frames = 0, then sBtlActionTbl[s].init(action)
// through jalr (inside the original's 16-byte frame, $a0/$a1 passed on as they came in). Returns the init's $v0.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: differed only on inputs the original faults on).
void btlActionSetState(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::enter, hg::jalr, hg::ld, hg::lhu, hg::lw, hg::sd, hg::sh, hg::sll, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    enter(ctx, 20);  // entry check point + the only block
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lhu(v0, a0, action::kState);
    sh(v0, a0, action::kPrevState);  // prev = state
    sh(a1, a0, action::kState);      // state = s
    sw(zero, a0, action::kFrames);   // frames = 0
    // v0 = sBtlActionTbl[s].init (12-byte {init, update, name} rows)
    v1 = a1 & 0xFFFF;
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v1 = sll(v0, 2);
    v0 = hi(btl::kActionStateTbl);
    v0 = addiu(v0, lo(btl::kActionStateTbl));  // &sBtlActionTbl
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    jalr(ctx, 0x299D98u, v0.u());  // init(action, s)
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00299E30 sub_299E30 [btlActionSetActive] -- 20 bytes; leaf frame (no stack)
// sub_299E30(action): action->flags |= 1. Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_299E30(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lhu, hg::sh;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    enter(ctx, 5);  // entry check point + the only block
    lhu(v1, a0, action::kFlags);
    v1 = v1 | 0x1;
    sh(v1, a0, action::kFlags);
}

// 0x00299E50 sub_299E50 [btlActionClearActive] -- 20 bytes; leaf frame (no stack)
// sub_299E50(action): action->flags &= ~1. Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_299E50(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lhu, hg::sh;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    enter(ctx, 5);  // entry check point + the only block
    lhu(v1, a0, action::kFlags);
    v1 = v1 & 0xFFFE;
    sh(v1, a0, action::kFlags);
}

// 0x00299E70 sub_299E70 [btlActionSetUnit] -- 24 bytes; leaf frame (no stack)
// sub_299E70(action, unit): action->unit = unit, action->flags2 |= 1 (a combatant). Register-faithful (p3fes_handgen
// body; audit 2026-10-21: scratch GPRs).
void sub_299E70(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lhu, hg::sh, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    enter(ctx, 6);  // entry check point + the only block
    sw(a1, a0, action::kUnit);
    lhu(v1, a0, action::kFlags2);
    v1 = v1 | 0x1;
    sh(v1, a0, action::kFlags2);
}

// 0x0029A1D0 sub_29A1D0 [btlActionFindByUnit] -- 60 bytes; leaf frame (no stack)
// sub_29A1D0(unit): the first action of gBtl's list whose unit (+48) is `unit`, or 0. Register-faithful (p3fes_handgen
// body; audit 2026-10-21: $v0).
void sub_29A1D0(EEContext& ctx) {
    using hg::Gpr, hg::backedge, hg::charge, hg::enter, hg::lw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x0029a1d0: for (v0 = gBtl->action_list; v0; v0 = v0->next)
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, gp, gp_off(btl::kBtlPtr));  // gBtl
    lw(v0, v0, btl_root::kActionList);
    for (;;) {
        // 0x0029a1f8: loop test
        charge(ctx, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0029a1e0
        charge(ctx, 3);
        lw(v1, v0, action::kUnit);
        if (v1 == a0) {
            // 0x0029a1ec, 0x0029a204: found: return the action ($v0)
            charge(ctx, 2);
            charge(ctx, 2);
            return;
        }
        // 0x0029a1f4: next
        charge(ctx, 1);
        lw(v0, v0, action::kNextInList);
    }
    // 0x0029a200, 0x0029a204: none: return 0
    charge(ctx, 1);
    v0 = 0;
    charge(ctx, 2);
}

// 0x0029A210 sub_29A210 [btlActionFindBySerial] -- 60 bytes; leaf frame (no stack)
// sub_29A210(serial): the first action of gBtl's list whose serial (+8) is `serial`, or 0. Register-faithful
// (p3fes_handgen body; audit 2026-10-21: $v0).
void sub_29A210(EEContext& ctx) {
    using hg::Gpr, hg::backedge, hg::charge, hg::enter, hg::lw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x0029a210: for (v0 = gBtl->action_list; v0; v0 = v0->next)
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, gp, gp_off(btl::kBtlPtr));  // gBtl
    lw(v0, v0, btl_root::kActionList);
    for (;;) {
        // 0x0029a238: loop test
        charge(ctx, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0029a220
        charge(ctx, 3);
        lw(v1, v0, action::kSerial);
        if (v1 == a0) {
            // 0x0029a22c, 0x0029a244: found: return the action ($v0)
            charge(ctx, 2);
            charge(ctx, 2);
            return;
        }
        // 0x0029a234: next
        charge(ctx, 1);
        lw(v0, v0, action::kNextInList);
    }
    // 0x0029a240, 0x0029a244: none: return 0
    charge(ctx, 1);
    v0 = 0;
    charge(ctx, 2);
}

// 0x0029A250 sub_29A250 [btlListRemove] -- 112 bytes; leaf frame (no stack)
// sub_29A250(list, count, item): remove the first `item` of the `count` words and shift the rest down, zeroing the
// last; returns 1, or 0 when absent. The compares are 64-bit (sltu on the registers as passed).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void sub_29A250(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::sltu, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0029a250: for (i = 0; i < count && *list != item; ++i, ++list) (v1 = i, a0 = list)
    enter(ctx, 3);  // entry check point + this block's cycles
    v1 = 0;
    for (;;) {
        // 0x0029a270: i < count?
        charge(ctx, 3);
        v0 = sltu(v1, a1);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0029a25c: *list == item?
        charge(ctx, 3);
        lw(v0, a0, 0);
        if (v0 == a2) {
            break;
        }
        // 0x0029a268
        charge(ctx, 2);
        a0 = addiu(a0, 4);
        v1 = addiu(v1, 1);
    }
    // 0x0029a27c
    charge(ctx, 2);
    if (v1 != a1) {
        // found: for (; i < count - 1; ++i, ++list) list[0] = list[1]
        for (;;) {
            // 0x0029a2a0: loop test
            charge(ctx, 4);
            v0 = addiu(a1, -1);
            v0 = sltu(v1, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0029a290
            charge(ctx, 4);
            lw(v0, a0, 4);
            sw(v0, a0, 0);
            a0 = addiu(a0, 4);
            v1 = addiu(v1, 1);
        }
        // 0x0029a2b0: the last word = 0; return 1
        charge(ctx, 2);
        sw(zero, a0, 0);
        v0 = 1;
    } else {
        // 0x0029a284: absent: return 0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0029a2b8: return
    charge(ctx, 2);
}

// 0x0029A2C0 sub_29A2C0 [btlOrderAddAction] -- 92 bytes; leaf frame (no stack)
// sub_29A2C0(action): put `action` in the first free (zero) slot of the 12-slot order list gBtl+0x254; returns 1, or 0
// when the list is full. Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void sub_29A2C0(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::sltiu, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x0029a2c0: a1 = &gBtl->order[0]; for (i = 0; i < 12 && *a1; ++i, ++a1) (v1 = i)
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, gp, gp_off(btl::kBtlPtr));  // gBtl
    a1 = addiu(v0, btl_root::kOrderList);
    v1 = 0;
    for (;;) {
        // 0x0029a2e8: i < 12?
        charge(ctx, 3);
        v0 = sltiu(v1, btl_root::kOrderSlots);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0029a2d4: a free slot?
        charge(ctx, 3);
        lw(v0, a1, 0);
        if (v0 == 0) {
            break;
        }
        // 0x0029a2e0
        charge(ctx, 2);
        a1 = addiu(a1, 4);
        v1 = addiu(v1, 1);
    }
    // 0x0029a2f4
    charge(ctx, 3);
    v0 = btl_root::kOrderSlots;
    if (v1 != v0) {
        // 0x0029a30c: *a1 = action; return 1
        charge(ctx, 2);
        sw(a0, a1, 0);
        v0 = 1;
    } else {
        // 0x0029a300: full: return 0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0029a314: return
    charge(ctx, 2);
}

// 0x0029A380 sub_29A380 [btlOrderAddActionNext] -- 92 bytes; leaf frame (no stack)
// sub_29A380(action): sub_29A2C0 on the next round's order list gBtl+0x284. Register-faithful (p3fes_handgen body;
// audit 2026-10-21: $v0).
void sub_29A380(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::sltiu, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x0029a380: a1 = &gBtl->order_next[0]; for (i = 0; i < 12 && *a1; ++i, ++a1) (v1 = i)
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, gp, gp_off(btl::kBtlPtr));  // gBtl
    a1 = addiu(v0, btl_root::kOrderListNext);
    v1 = 0;
    for (;;) {
        // 0x0029a3a8: i < 12?
        charge(ctx, 3);
        v0 = sltiu(v1, btl_root::kOrderSlots);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0029a394: a free slot?
        charge(ctx, 3);
        lw(v0, a1, 0);
        if (v0 == 0) {
            break;
        }
        // 0x0029a3a0
        charge(ctx, 2);
        a1 = addiu(a1, 4);
        v1 = addiu(v1, 1);
    }
    // 0x0029a3b4
    charge(ctx, 3);
    v0 = btl_root::kOrderSlots;
    if (v1 != v0) {
        // 0x0029a3cc: *a1 = action; return 1
        charge(ctx, 2);
        sw(a0, a1, 0);
        v0 = 1;
    } else {
        // 0x0029a3c0: full: return 0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0029a3d4: return
    charge(ctx, 2);
}

// 0x0029A320 sub_29A320 [btlOrderRemoveAction] -- 84 bytes; frame 0x10: ra sp+0x0
// sub_29A320(action): sub_29A250(&gBtl->order[0], 12, action) until it finds none; returns 1 if any was removed.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void sub_29A320(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lw, hg::sd;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0029a320: prologue; a2 = action, t0 = &gBtl->order[0], a3 = removed = 0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = a0;
    lw(v0, gp, gp_off(btl::kBtlPtr));  // gBtl
    t0 = addiu(v0, btl_root::kOrderList);
    a3 = 0;
    for (;;) {
        // 0x0029a344: sub_29A250(list, 12, action) == 1?
        charge(ctx, 7);
        a0 = t0;
        a1 = btl_root::kOrderSlots;
        jal(ctx, 0x29A34Cu, gen::fn_sub_29A250_0029a250);
        v1 = 1;
        if (v0 != v1) {
            break;
        }
        backedge(ctx);
        // 0x0029a340: removed = 1
        charge(ctx, 1);
        a3 = 1;
    }
    // 0x0029a360: return removed; epilogue
    charge(ctx, 5);
    v0 = a3;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0029A3E0 sub_29A3E0 [btlActionIsTurnHolder] -- 136 bytes; leaf frame (no stack)
// sub_29A3E0(action): 1 when action bytes +40 or +41 are set, or gBtl flag bit 3 is clear, or (unless action flag
// bit 2) it heads the next round's list gBtl+0x284; otherwise whether it is slot 1 of the order list (gBtl+0x258).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_29A3E0(EEContext& ctx) {
    using hg::Gpr, hg::charge, hg::enter, hg::lbu, hg::lhu, hg::lw, hg::sltiu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x0029a3e0: action byte +40 set -> 1
    enter(ctx, 3);  // entry check point + this block's cycles
    lbu(v0, a0, action::kByte40);
    bool yes = v0 != 0;
    if (!yes) {
        // 0x0029a3ec: action byte +41 set -> 1
        charge(ctx, 3);
        lbu(v0, a0, action::kByte41);
        yes = v0 != 0;
    }
    if (yes) {
        // 0x0029a3f8: return 1
        charge(ctx, 3);
        v0 = 1;
    } else {
        // 0x0029a404: v1 = gBtl; flag bit 3 clear -> 1
        charge(ctx, 5);
        lw(v1, gp, gp_off(btl::kBtlPtr));  // gBtl
        lw(v0, v1, btl_root::kFlags);
        v0 = v0 & 0x8;
        if (v0 != 0) {
            // 0x0029a424: unless action flag bit 2: the head of the next round's list -> 1
            charge(ctx, 4);
            lhu(v0, a0, action::kFlags);
            v0 = v0 & 0x4;
            bool head = false;
            if (v0 == 0) {
                // 0x0029a434
                charge(ctx, 3);
                lw(v0, v1, btl_root::kOrderListNext);
                if (v0 != 0) {
                    // 0x0029a440
                    charge(ctx, 2);
                    head = v0 == a0;
                }
            }
            if (head) {
                // 0x0029a448: return 1
                charge(ctx, 3);
                v0 = 1;
            } else {
                // 0x0029a454: return gBtl->order[1] == action
                charge(ctx, 3);
                lw(v0, v1, btl_root::kOrderList + 4);
                v0 = v0 ^ a0;
                v0 = sltiu(v0, 1);
            }
        } else {
            // 0x0029a418: return 1
            charge(ctx, 3);
            v0 = 1;
        }
    }
    // 0x0029a460: return
    charge(ctx, 2);
}

// 0x0029A470 sub_29A470 [btlOrderMoveToFront] -- 120 bytes; leaf frame (no stack)
// sub_29A470(action): move `action` to slot 0 of the order list, shifting the ones before it up; returns 1, or 0 when
// absent. Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void sub_29A470(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::i64, hg::lw, hg::sltiu, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x0029a470: a1 = &gBtl->order[0]; for (i = 0; i < 12 && *a1 != action; ++i, ++a1) (v1 = i)
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, gp, gp_off(btl::kBtlPtr));  // gBtl
    a1 = addiu(v0, btl_root::kOrderList);
    v1 = 0;
    for (;;) {
        // 0x0029a498: i < 12?
        charge(ctx, 3);
        v0 = sltiu(v1, btl_root::kOrderSlots);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0029a484: the action?
        charge(ctx, 3);
        lw(v0, a1, 0);
        if (v0 == a0) {
            break;
        }
        // 0x0029a490
        charge(ctx, 2);
        a1 = addiu(a1, 4);
        v1 = addiu(v1, 1);
    }
    // 0x0029a4a4
    charge(ctx, 3);
    v0 = btl_root::kOrderSlots;
    if (v1 != v0) {
        // found: for (; i > 0; --i, --a1) a1[0] = a1[-1]
        for (;;) {
            // 0x0029a4cc: loop test
            charge(ctx, 3);
            if (i64(v1) <= 0) {
                break;
            }
            backedge(ctx);
            // 0x0029a4bc
            charge(ctx, 4);
            lw(v0, a1, -4);
            sw(v0, a1, 0);
            a1 = addiu(a1, -4);
            v1 = addiu(v1, -1);
        }
        // 0x0029a4d8: order[0] = action; return 1
        charge(ctx, 2);
        sw(a0, a1, 0);
        v0 = 1;
    } else {
        // 0x0029a4b0: absent: return 0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0029a4e0: return
    charge(ctx, 2);
}

// 0x0029A4F0 sub_29A4F0 [btlOrderMoveToBack] -- 128 bytes; leaf frame (no stack)
// sub_29A4F0(action): move `action` behind the last occupied slot, shifting the later ones down; returns 1, or 0 when
// absent. Register-faithful (p3fes_handgen body; audit 2026-10-21: $v0).
void sub_29A4F0(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::sltiu, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x0029a4f0: a1 = &gBtl->order[0]; for (i = 0; i < 12 && *a1 != action; ++i, ++a1) (v1 = i)
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, gp, gp_off(btl::kBtlPtr));  // gBtl
    a1 = addiu(v0, btl_root::kOrderList);
    v1 = 0;
    for (;;) {
        // 0x0029a518: i < 12?
        charge(ctx, 3);
        v0 = sltiu(v1, btl_root::kOrderSlots);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0029a504: the action?
        charge(ctx, 3);
        lw(v0, a1, 0);
        if (v0 == a0) {
            break;
        }
        // 0x0029a510
        charge(ctx, 2);
        a1 = addiu(a1, 4);
        v1 = addiu(v1, 1);
    }
    // 0x0029a524
    charge(ctx, 3);
    v0 = btl_root::kOrderSlots;
    if (v1 != v0) {
        // found: for (; i < 11 && a1[1]; ++i, ++a1) a1[0] = a1[1]
        for (;;) {
            // 0x0029a554: i < 11?
            charge(ctx, 3);
            v0 = sltiu(v1, btl_root::kOrderSlots - 1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0029a53c: the next slot occupied?
            charge(ctx, 3);
            lw(v0, a1, 4);
            if (v0 == 0) {
                break;
            }
            // 0x0029a548
            charge(ctx, 3);
            sw(v0, a1, 0);
            a1 = addiu(a1, 4);
            v1 = addiu(v1, 1);
        }
        // 0x0029a560: *a1 = action; return 1
        charge(ctx, 2);
        sw(a0, a1, 0);
        v0 = 1;
    } else {
        // 0x0029a530: absent: return 0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0029a568: return
    charge(ctx, 2);
}

// 0x0029A570 btlOrderSortByAgility -- 288 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// btlOrderSortByAgility(): bubble sort of the occupied prefix of the order list, descending datCalcGetStat(unit, 3)
// (Agility) of each action's DatUnit; stable for equal values. An empty list makes the pass bound wrap (count - 1
// unsigned) as in the original. $v0 ends as the last datCalcGetStat left it.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void btlOrderSortByAgility(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::slt,
          hg::sltiu, hg::sltu, hg::sq, hg::sw;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0029a570: prologue; s4 = count = the index of the first free slot of gBtl->order[12]
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, gp_off(btl::kBtlPtr));  // gBtl
    a0 = addiu(v1, btl_root::kOrderList);
    s4 = 0;
    for (;;) {
        // 0x0029a5bc: count < 12?
        charge(ctx, 3);
        v1 = sltiu(s4, btl_root::kOrderSlots);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0029a5a8: occupied?
        charge(ctx, 3);
        lw(v1, a0, 0);
        if (v1 == 0) {
            break;
        }
        // 0x0029a5b4
        charge(ctx, 2);
        a0 = addiu(a0, 4);
        s4 = addiu(s4, 1);
    }
    // do { one bubble pass } while (swapped)
    for (;;) {
        // 0x0029a5c8: s5 = swapped = 0; s3 = &order[0]; for (s2 = 0; s2 < count - 1; ++s2, ++s3)
        charge(ctx, 6);
        s5 = 0;
        lw(v1, gp, gp_off(btl::kBtlPtr));
        s3 = addiu(v1, btl_root::kOrderList);
        s2 = 0;
        for (;;) {
            // 0x0029a64c: pass loop test (unsigned)
            charge(ctx, 4);
            v1 = addiu(s4, -1);
            v1 = sltu(s2, v1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0029a5e0: s1 = order[i], s0 = order[i + 1]
            charge(ctx, 4);
            lw(s1, s3, 0);
            lw(s0, s3, 4);
            if (s1 != 0) {
                // 0x0029a5f0
                charge(ctx, 2);
                if (s0 != 0) {
                    // 0x0029a5f8: Ag(s1) < Ag(s0) -> swap (datCalcGetStat(action->unit->dat, 3), u8)
                    charge(ctx, 16);
                    lw(v0, s1, action::kUnit);
                    lw(a0, v0, btl_unit::kDat);
                    a1 = 3;
                    jal(ctx, 0x29A604u, gen::fn_datCalcGetStat_00300c90);
                    s6 = v0 & 0xFF;
                    lw(v0, s0, action::kUnit);
                    lw(a0, v0, btl_unit::kDat);
                    a1 = 3;
                    jal(ctx, 0x29A61Cu, gen::fn_datCalcGetStat_00300c90);
                    a0 = v0 & 0xFF;
                    v1 = s6 & 0xFFFF;
                    at = slt(v1, a0);
                    if (at != 0) {
                        // 0x0029a638: swap; swapped = 1
                        charge(ctx, 3);
                        sw(s0, s3, 0);
                        sw(s1, s3, 4);
                        s5 = 1;
                    }
                }
            }
            // 0x0029a644: next pair
            charge(ctx, 2);
            s2 = addiu(s2, 1);
            s3 = addiu(s3, 4);
        }
        // 0x0029a65c: until a pass swaps nothing
        charge(ctx, 2);
        if (s5 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0029a664: epilogue
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
}

// 0x0029A690 sub_29A690 [btlOrderSortBySide] -- 192 bytes; leaf frame (no stack)
// sub_29A690(side): bubble passes over the first count - 1 pairs of the order list, swapping neighbours of different
// sides (btlUnit +162) whose first is not `side`, until a pass swaps nothing: units of `side` move to the front, the
// others keep their order. Leaves $v0 alone. Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_29A690(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::lbu, hg::lw, hg::sltiu, hg::sltu, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, gp{ctx, 28};
    // 0x0029a690: a2 = count = the index of the first free slot of gBtl->order[12]
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, gp, gp_off(btl::kBtlPtr));  // gBtl
    a1 = addiu(v1, btl_root::kOrderList);
    a2 = 0;
    for (;;) {
        // 0x0029a6b8: count < 12?
        charge(ctx, 3);
        v1 = sltiu(a2, btl_root::kOrderSlots);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0029a6a4: occupied?
        charge(ctx, 3);
        lw(v1, a1, 0);
        if (v1 == 0) {
            break;
        }
        // 0x0029a6b0
        charge(ctx, 2);
        a1 = addiu(a1, 4);
        a2 = addiu(a2, 1);
    }
    // 0x0029a6c4: t3 = (u16)side, a1 = 1, a0 = count - 1 (the pass bound, unsigned)
    charge(ctx, 3);
    t3 = a0 & 0xFFFF;
    a1 = 1;
    a0 = addiu(a2, -1);
    // do { one pass } while (swapped)
    for (;;) {
        // 0x0029a6d0: t4 = swapped = 0; t2 = &order[0]; for (t1 = 0; t1 < count - 1; ++t1, ++t2)
        charge(ctx, 6);
        t4 = 0;
        lw(v1, gp, gp_off(btl::kBtlPtr));
        t2 = addiu(v1, btl_root::kOrderList);
        t1 = 0;
        for (;;) {
            // 0x0029a734: pass loop test
            charge(ctx, 3);
            v1 = sltu(t1, a0);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0029a6e8: t0 = order[i], a3 = order[i + 1]
            charge(ctx, 4);
            lw(t0, t2, 0);
            lw(a3, t2, 4);
            if (t0 != 0) {
                // 0x0029a6f8
                charge(ctx, 2);
                if (a3 != 0) {
                    // 0x0029a700: a2 / v1 = the two actions' unit sides
                    charge(ctx, 6);
                    lw(v1, t0, action::kUnit);
                    lbu(a2, v1, btl_unit::kSide);
                    lw(v1, a3, action::kUnit);
                    lbu(v1, v1, btl_unit::kSide);
                    if (a2 != v1) {
                        // 0x0029a718: different sides, the first not `side`: swap
                        charge(ctx, 2);
                        if (a2 != t3) {
                            // 0x0029a720: swapped = 1
                            charge(ctx, 3);
                            sw(a3, t2, 0);
                            sw(t0, t2, 4);
                            t4 = a1;
                        }
                    }
                }
            }
            // 0x0029a72c: next pair
            charge(ctx, 2);
            t1 = addiu(t1, 1);
            t2 = addiu(t2, 4);
        }
        // 0x0029a740: until a pass swaps nothing
        charge(ctx, 2);
        if (t4 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0029a748: return
    charge(ctx, 2);
}

// 0x0029DE20 btlMainSetState -- 88 bytes; frame 0x10: ra sp+0x0
// btlMainSetState(state): gBtl->main_state = state, ->main_frames = 0, then sBtlMainStateTbl[state].init(&gBtl->
// main_state) through jalr, inside the original's 16-byte frame. Returns the init's $v0.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: differed only on inputs the original faults on).
void btlMainSetState(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::enter, hg::jalr, hg::ld, hg::lw, hg::sd, hg::sll, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    enter(ctx, 22);  // entry check point + the only block
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, gp_off(btl::kBtlPtr));  // gBtl
    sw(a0, v0, btl_root::kMainState);
    lw(v0, gp, gp_off(btl::kBtlPtr));
    sw(zero, v0, btl_root::kMainFrames);
    lw(v0, gp, gp_off(btl::kBtlPtr));
    a0 = addiu(v0, btl_root::kMainState);  // the init's argument: &gBtl->main_state
    // v0 = sBtlMainStateTbl[state].init (12-byte {init, update, name} rows)
    lw(v1, v0, btl_root::kMainState);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v1 = sll(v0, 2);
    v0 = hi(btl::kMainStateTbl);
    v0 = addiu(v0, lo(btl::kMainStateTbl));  // &sBtlMainStateTbl
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    jalr(ctx, 0x29DE60u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x29DE80 btlMainUpdateState: enter a pending state (+0x2B8) first, run the update, a non-zero result
// becomes the pending state, frames += 1. Returns the update's $v0; like the original it leaves $a0 = gBtl and
// $v1 = the new frame count. Both calls run inside the original's 16-byte frame (DriverFrame).
u64 btlMainUpdateState(EEContext& ctx) {
    guest::enter(ctx, 6);
    const DriverFrame frame(ctx);
    const u32 pend = guest::load<u32>(ctx, gbtl(ctx) + kBtlMainPending);
    if (pend != 0) {
        guest::charge(ctx, 17);
        guest::store<u32>(ctx, gbtl(ctx) + kBtlMainState, pend);
        guest::store<u32>(ctx, gbtl(ctx) + kBtlMainFrames, 0);
        const u32 g = gbtl(ctx);
        ee::core::set_gpr64(ctx, GPR_A0, sx64(g + kBtlMainState));
        jalr_state(ctx, 0x29DECCu, kMainStateTbl, guest::load<u32>(ctx, g + kBtlMainState));
        guest::store<u32>(ctx, gbtl(ctx) + kBtlMainPending, 0);
    }
    guest::charge(ctx, 14);
    const u32 g = gbtl(ctx);
    ee::core::set_gpr64(ctx, GPR_A0, sx64(g + kBtlMainState));
    const u64 r = jalr_state(ctx, 0x29DF04u, kMainStateTbl + 4, guest::load<u32>(ctx, g + kBtlMainState));
    if (r != 0) {
        guest::charge(ctx, 2);
        guest::store<u32>(ctx, gbtl(ctx) + kBtlMainPending, static_cast<u32>(r));
    }
    guest::charge(ctx, 8);
    const u32 g2 = gbtl(ctx);
    const u32 frames = guest::load<u32>(ctx, g2 + kBtlMainFrames) + 1u;
    ee::core::set_gpr64(ctx, GPR_A0, sx64(g2));
    ee::core::set_gpr64(ctx, GPR_V1, sx64(frames));
    guest::store<u32>(ctx, g2 + kBtlMainFrames, frames);
    return r;
}

// =================================================================================================================
// g_data / datPersona.c: party, persona and item records
// =================================================================================================================

// 0x0016CB80 datGetEquipmentIdx -- 116 bytes; leaf frame (no stack)
// datGetEquipmentIdx(pc, slot): the s16 equipment index of `slot` (hero: btl::kHeroEquipment[slot]; member pc:
// btl::kPartyEquipment + 868 * pc). Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void datGetEquipmentIdx(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::lh, hg::sll, hg::subu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0016cb80: v1 = (s16)pc; the hero?
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);
    v0 = dat_unit::kHero;
    if (v1 != v0) {
        // 0x0016cbb8: member: ((s16 *)(kPartyEquipment + 868 * pc))[(s16)slot] (868 = ((pc * 31) * 7) << 2)
        charge(ctx, 13);
        v0 = sll(v1, 5);
        v1 = subu(v0, v1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        v0 = hi(btl::kPartyEquipment);
        v0 = addiu(v0, lo(btl::kPartyEquipment));
        v1 = addu(v0, v1);
        v0 = dsll32(a1, 16);
        v0 = dsra32(v0, 16);
        v0 = sll(v0, 1);
        v0 = addu(v0, v1);
        lh(v0, v0, 0);
    } else {
        // 0x0016cb94: hero: kHeroEquipment[(s16)slot]
        charge(ctx, 9);
        v0 = dsll32(a1, 16);
        v0 = dsra32(v0, 16);
        v1 = sll(v0, 1);
        v0 = hi(btl::kHeroEquipment);
        v0 = addiu(v0, lo(btl::kHeroEquipment));
        v0 = addu(v0, v1);
        lh(v0, v0, 0);
    }
    // 0x0016cbec: return
    charge(ctx, 2);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
s32 datGetEquipmentIdx(EEContext& ctx, u32 pc, u32 slot) {
    ee::core::set_gpr64(ctx, GPR_A0, ee::core::sext32(static_cast<u32>(pc)));
    ee::core::set_gpr64(ctx, GPR_A1, ee::core::sext32(static_cast<u32>(slot)));
    datGetEquipmentIdx(ctx);
    return static_cast<s32>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x0016CC00 sub_16CC00 [datGetGrowthHp] -- 172 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_16CC00(pc): the growth table's HP for member `pc` at its level: kGrowthTable[level][pc].hp (44-byte rows of
// 11 x {u16 hp, u16 sp}); the level is datCalcGetLevel of the hero's unit or the member's record +4.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void sub_16CC00(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld, hg::lhu,
          hg::lq, hg::sd, hg::sll, hg::sq, hg::subu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016cc00: prologue; s0 = (s16)pc; the hero?
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = dsll32(a0, 16);
    s0 = dsra32(s0, 16);
    v0 = dat_unit::kHero;
    if (s0 != v0) {
        // 0x0016cc38: datCalcGetLevel(&kPartyRecords[pc - 2].unit)
        charge(ctx, 12);
        v1 = addiu(s0, -2);
        v0 = sll(v1, 5);
        v1 = subu(v0, v1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        v0 = hi(btl::kPartyRecords);
        v0 = addiu(v0, lo(btl::kPartyRecords));
        v0 = addu(v0, v1);
        a0 = addiu(v0, party::kUnit);
        jal(ctx, 0x16CC60u, gen::fn_datCalcGetLevel_002ffcc0);
    } else {
        // 0x0016cc20: datCalcGetLevel(&hero unit)
        charge(ctx, 6);
        a0 = hi(btl::kHeroUnit);
        a0 = addiu(a0, lo(btl::kHeroUnit));
        jal(ctx, 0x16CC28u, gen::fn_datCalcGetLevel_002ffcc0);
    }
    // 0x0016cc68: return kGrowthTable[(u8)level * 44 + pc * 4].hp; epilogue
    charge(ctx, 17);
    v1 = v0 & 0xFF;
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    v0 = addu(v0, v1);
    v1 = sll(v0, 2);
    v0 = hi(btl::kGrowthTable);
    v0 = addiu(v0, lo(btl::kGrowthTable));
    v1 = addu(v0, v1);
    v0 = sll(s0, 2);
    v0 = addu(v0, v1);
    lhu(v0, v0, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0016CCB0 sub_16CCB0 [datGetGrowthSp] -- 172 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_16CCB0(pc): sub_16CC00 for SP: kGrowthTable[level][pc].sp. Register-faithful (p3fes_handgen body; audit
// 2026-10-21: own frame / spills).
void sub_16CCB0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld, hg::lhu,
          hg::lq, hg::sd, hg::sll, hg::sq, hg::subu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016ccb0: prologue; s0 = (s16)pc; the hero?
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = dsll32(a0, 16);
    s0 = dsra32(s0, 16);
    v0 = dat_unit::kHero;
    if (s0 != v0) {
        // 0x0016cce8: datCalcGetLevel(&kPartyRecords[pc - 2].unit)
        charge(ctx, 12);
        v1 = addiu(s0, -2);
        v0 = sll(v1, 5);
        v1 = subu(v0, v1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        v0 = hi(btl::kPartyRecords);
        v0 = addiu(v0, lo(btl::kPartyRecords));
        v0 = addu(v0, v1);
        a0 = addiu(v0, party::kUnit);
        jal(ctx, 0x16CD10u, gen::fn_datCalcGetLevel_002ffcc0);
    } else {
        // 0x0016ccd0: datCalcGetLevel(&hero unit)
        charge(ctx, 6);
        a0 = hi(btl::kHeroUnit);
        a0 = addiu(a0, lo(btl::kHeroUnit));
        jal(ctx, 0x16CCD8u, gen::fn_datCalcGetLevel_002ffcc0);
    }
    // 0x0016cd18: return kGrowthTable[(u8)level * 44 + pc * 4].sp; epilogue
    charge(ctx, 17);
    v1 = v0 & 0xFF;
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    v0 = addu(v0, v1);
    v1 = sll(v0, 2);
    v0 = hi(btl::kGrowthTable + party::kGrowthSp);
    v0 = addiu(v0, lo(btl::kGrowthTable + party::kGrowthSp));
    v1 = addu(v0, v1);
    v0 = sll(s0, 2);
    v0 = addu(v0, v1);
    lhu(v0, v0, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0016CD60 datGetUnit -- 140 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// datGetUnit(pc): the hero's DatUnit or member pc's (record + 4); asserts pc < 11 (line 737).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void datGetUnit(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::ld, hg::lq, hg::sd, hg::sll,
          hg::slti, hg::sq, hg::subu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016cd60: prologue; s0 = (s16)pc; the hero?
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = dsll32(a0, 16);
    s0 = dsra32(s0, 16);
    v0 = dat_unit::kHero;
    if (s0 != v0) {
        // 0x0016cd90: K_Assert(pc < 11)
        charge(ctx, 3);
        v0 = slti(s0, dat_unit::kPartyIds);
        if (v0 == 0) {
            // 0x0016cd9c
            charge(ctx, 5);
            k_assert(a0, a1, 0x16CDA8u, kGDataFile, 737);
        }
        // 0x0016cdb0: return &kPartyRecords[pc - 2].unit
        charge(ctx, 10);
        v1 = addiu(s0, -2);
        v0 = sll(v1, 5);
        v1 = subu(v0, v1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        v0 = hi(btl::kPartyRecords);
        v0 = addiu(v0, lo(btl::kPartyRecords));
        v0 = addu(v0, v1);
        v0 = addiu(v0, party::kUnit);
    } else {
        // 0x0016cd80: return the hero's unit
        charge(ctx, 4);
        v0 = hi(btl::kHeroUnit);
        v0 = addiu(v0, lo(btl::kHeroUnit));
    }
    // 0x0016cdd8: epilogue
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0016F630 sub_16F630 [datGetEquipmentItemId] -- 236 bytes; leaf frame (no stack)
// sub_16F630(owner, idx): the u16 item id (+0) of the 20-byte equipment entry `idx` of `owner`: owner -1 the table at
// 0x833E80, 1 (the hero) the entries *0x836794 points at, < 256 the member's entries at 0x8339A4 + 868 * owner, else
// 0x7FD6C8 + 868 * owner. Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_16F630(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::lhu, hg::lw, hg::si,
          hg::sll, hg::slti, hg::subu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0016f630: v1 = (s16)owner
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);
    v0 = si(-1);
    if (v1 != v0) {
        // 0x0016f668
        charge(ctx, 3);
        v0 = dat_unit::kHero;
        if (v1 != v0) {
            // 0x0016f698
            charge(ctx, 3);
            v0 = slti(v1, 256);
            if (v0 != 0) {
                // 0x0016f6e0: owner < 256: kEquipEntries + 868 * owner + 20 * idx
                charge(ctx, 13);
                v0 = sll(v1, 5);
                v1 = subu(v0, v1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 2);
                v0 = hi(party::kEquipEntries);
                v0 = addiu(v0, lo(party::kEquipEntries));
                v1 = addu(v0, v1);
                v0 = sll(a1, 2);
                v0 = addu(v0, a1);
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lhu(v0, v0, party::kEquipItemId);
            } else {
                // 0x0016f6a4: owner >= 256: kEquipEntriesHi + 868 * owner + 20 * idx
                charge(ctx, 15);
                v0 = sll(v1, 5);
                v1 = subu(v0, v1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 2);
                v0 = hi(party::kEquipEntriesHi);
                v0 = addiu(v0, lo(party::kEquipEntriesHi));
                v1 = addu(v0, v1);
                v0 = sll(a1, 2);
                v0 = addu(v0, a1);
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lhu(v0, v0, party::kEquipItemId);
            }
        } else {
            // 0x0016f674: the hero: (*kHeroEquipEntriesPtr)[idx]
            charge(ctx, 9);
            v0 = sll(a1, 2);
            v0 = addu(v0, a1);
            v1 = sll(v0, 2);
            v0 = hi(party::kHeroEquipEntriesPtr);
            lw(v0, v0, lo(party::kHeroEquipEntriesPtr));
            v0 = addu(v0, v1);
            lhu(v0, v0, party::kEquipItemId);
        }
    } else {
        // 0x0016f644: owner -1: kEquipEntriesShared[idx]
        charge(ctx, 9);
        v0 = sll(a1, 2);
        v0 = addu(v0, a1);
        v1 = sll(v0, 2);
        v0 = hi(party::kEquipEntriesShared);
        v0 = addiu(v0, lo(party::kEquipEntriesShared));
        v0 = addu(v0, v1);
        lhu(v0, v0, party::kEquipItemId);
    }
    // 0x0016f714: return
    charge(ctx, 2);
}

// 0x0016F900 sub_16F900 [datGetEquipmentEffect] -- 236 bytes; leaf frame (no stack)
// sub_16F900(owner, idx): sub_16F630's lookup for the u8 effect (+9) of the entry; the compiler folds +9 into the
// table addresses (the hero's path keeps it in the load). Register-faithful (p3fes_handgen body; audit 2026-10-21:
// scratch GPRs).
void sub_16F900(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::lbu, hg::lw, hg::si,
          hg::sll, hg::slti, hg::subu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0016f900: v1 = (s16)owner
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);
    v0 = si(-1);
    if (v1 != v0) {
        // 0x0016f938
        charge(ctx, 3);
        v0 = dat_unit::kHero;
        if (v1 != v0) {
            // 0x0016f968
            charge(ctx, 3);
            v0 = slti(v1, 256);
            if (v0 != 0) {
                // 0x0016f9b0: owner < 256: (kEquipEntries + 9) + 868 * owner + 20 * idx
                charge(ctx, 13);
                v0 = sll(v1, 5);
                v1 = subu(v0, v1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 2);
                v0 = hi(party::kEquipEntries + party::kEquipEffect);
                v0 = addiu(v0, lo(party::kEquipEntries + party::kEquipEffect));
                v1 = addu(v0, v1);
                v0 = sll(a1, 2);
                v0 = addu(v0, a1);
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lbu(v0, v0, 0);
            } else {
                // 0x0016f974: owner >= 256: (kEquipEntriesHi + 9) + 868 * owner + 20 * idx
                charge(ctx, 15);
                v0 = sll(v1, 5);
                v1 = subu(v0, v1);
                v0 = sll(v1, 3);
                v0 = subu(v0, v1);
                v1 = sll(v0, 2);
                v0 = hi(party::kEquipEntriesHi + party::kEquipEffect);
                v0 = addiu(v0, lo(party::kEquipEntriesHi + party::kEquipEffect));
                v1 = addu(v0, v1);
                v0 = sll(a1, 2);
                v0 = addu(v0, a1);
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lbu(v0, v0, 0);
            }
        } else {
            // 0x0016f944: the hero: (*kHeroEquipEntriesPtr)[idx].effect
            charge(ctx, 9);
            v0 = hi(party::kHeroEquipEntriesPtr);
            lw(v1, v0, lo(party::kHeroEquipEntriesPtr));
            v0 = sll(a1, 2);
            v0 = addu(v0, a1);
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lbu(v0, v0, party::kEquipEffect);
        }
    } else {
        // 0x0016f914: owner -1: kEquipEntriesShared[idx].effect
        charge(ctx, 9);
        v0 = sll(a1, 2);
        v0 = addu(v0, a1);
        v1 = sll(v0, 2);
        v0 = hi(party::kEquipEntriesShared + party::kEquipEffect);
        v0 = addiu(v0, lo(party::kEquipEntriesShared + party::kEquipEffect));
        v0 = addu(v0, v1);
        lbu(v0, v0, 0);
    }
    // 0x0016f9e4: return
    charge(ctx, 2);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u32 sub_16F900(EEContext& ctx, u32 owner, u32 idx) {
    ee::core::set_gpr64(ctx, GPR_A0, ee::core::sext32(static_cast<u32>(owner)));
    ee::core::set_gpr64(ctx, GPR_A1, ee::core::sext32(static_cast<u32>(idx)));
    sub_16F900(ctx);
    return static_cast<u32>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x00173220 sub_173220 [datGetPersonaName] -- 92 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_173220(id): MSG.TBL section 3 + 17 * id, the persona's name (asserts id < 256, line 24).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void sub_173220(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::ld, hg::lq, hg::lw, hg::sd, hg::sll, hg::slti,
          hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00173220: prologue; s0 = id; K_Assert(id < 256)
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    v0 = s0 & 0xFFFF;
    v0 = slti(v0, persona::kIdCount);
    if (v0 == 0) {
        // 0x00173240
        charge(ctx, 5);
        k_assert(a0, a1, 0x17324Cu, kDatPersonaFile, 24);
    }
    // 0x00173254: return names + (id << 4) + id; epilogue
    charge(ctx, 10);
    v1 = s0 & 0xFFFF;
    v0 = sll(v1, 4);
    v1 = addu(v0, v1);
    lw(v0, gp, gp_off(btl::kPersonaNamesPtr));
    v0 = addu(v0, v1);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001732F0 sub_1732F0 [datPersonaGetLevel] -- 12 bytes; leaf frame (no stack)
// sub_1732F0(persona): persona->level (u8 +4). Register-faithful (p3fes_handgen body; audit 2026-10-21: differed
// only on inputs the original faults on).
void sub_1732F0(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lbu;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    enter(ctx, 3);  // entry check point + the only block
    lbu(v0, a0, persona::kLevel);
}

// 0x00173380 sub_173380 [datPersonaGetSkillsByPcId] -- 36 bytes; frame 0x10: ra sp+0x0
// sub_173380(pc): datPersonaGetByPcId(pc) + 12, the persona's u16 skill list. Register-faithful (p3fes_handgen body;
// audit 2026-10-21: own frame / spills).
void sub_173380(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::sd;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    enter(ctx, 9);  // entry check point + the only block
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x173388u, gen::fn_datPersonaGetByPcId_00174800);
    v0 = addiu(v0, persona::kSkills);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001733B0 sub_1733B0 [datPersonaGetAffinity] -- 164 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1733B0(persona, element): sub_306D90(0, UNIT.TBL section 2[persona->id][element]), the decoded affinity word;
// the callee's $v0 is returned as it left it. Asserts id < 256 (line 277) and element < 16 (278).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: callee frames).
void sub_1733B0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lq, hg::lw, hg::sd,
          hg::sll, hg::slti, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001733b0: prologue; s1 = persona, s0 = element; K_Assert(persona->id < 256)
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lhu(v0, a0, persona::kId);
    v0 = slti(v0, persona::kIdCount);
    if (v0 == 0) {
        // 0x001733d8
        charge(ctx, 5);
        k_assert(a0, a1, 0x1733E4u, kDatPersonaFile, 277);
    }
    // 0x001733ec: K_Assert(element < 16)
    charge(ctx, 4);
    v0 = s0 & 0xFFFF;
    v0 = slti(v0, 16);
    if (v0 == 0) {
        // 0x001733fc
        charge(ctx, 5);
        k_assert(a0, a1, 0x173408u, kDatPersonaFile, 278);
    }
    // 0x00173410: return sub_306D90(0, affinities[id * 16 + element]); epilogue
    charge(ctx, 17);
    lhu(v0, s1, persona::kId);
    v1 = sll(v0, 5);
    lw(v0, gp, gp_off(btl::kPersonaAffinityPtr));
    v1 = addu(v0, v1);
    v0 = s0 & 0xFFFF;
    v0 = sll(v0, 1);
    v0 = addu(v1, v0);
    a0 = 0;
    lhu(a1, v0, 0);
    jal(ctx, 0x173434u, gen::fn_sub_306D90_00306d90);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00173460 sub_173460 [datPersonaGetAffinityByPcId] -- 172 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_173460(pc, element): sub_1733B0 on datPersonaGetByPcId(pc) (inlined, the same asserts).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: callee frames).
void sub_173460(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lq, hg::lw, hg::sd,
          hg::sll, hg::slti, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00173460: prologue; s1 = element; s0 = datPersonaGetByPcId(pc); K_Assert(persona->id < 256)
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    jal(ctx, 0x173474u, gen::fn_datPersonaGetByPcId_00174800);
    s0 = v0;
    lhu(v0, v0, persona::kId);
    v0 = slti(v0, persona::kIdCount);
    if (v0 == 0) {
        // 0x00173490
        charge(ctx, 5);
        k_assert(a0, a1, 0x17349Cu, kDatPersonaFile, 277);
    }
    // 0x001734a4: K_Assert(element < 16)
    charge(ctx, 4);
    v0 = s1 & 0xFFFF;
    v0 = slti(v0, 16);
    if (v0 == 0) {
        // 0x001734b4
        charge(ctx, 5);
        k_assert(a0, a1, 0x1734C0u, kDatPersonaFile, 278);
    }
    // 0x001734c8: return sub_306D90(0, affinities[id * 16 + element]); epilogue
    charge(ctx, 17);
    lhu(v0, s0, persona::kId);
    v1 = sll(v0, 5);
    lw(v0, gp, gp_off(btl::kPersonaAffinityPtr));
    v1 = addu(v0, v1);
    v0 = s1 & 0xFFFF;
    v0 = sll(v0, 1);
    v0 = addu(v1, v0);
    a0 = 0;
    lhu(a1, v0, 0);
    jal(ctx, 0x1734ECu, gen::fn_sub_306D90_00306d90);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00173510 sub_173510 [datPersonaGetBaseStat] -- 104 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_173510(pc, stat): the u8 base stat persona->base_stats[stat] (+28) of datPersonaGetByPcId(pc) (asserts stat < 5,
// line 316). Register-faithful (p3fes_handgen body; audit 2026-10-21: own frame / spills).
void sub_173510(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lq, hg::sd, hg::slti,
          hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00173510: prologue; s1 = stat; s0 = datPersonaGetByPcId(pc); K_Assert(stat < 5)
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    jal(ctx, 0x173524u, gen::fn_datPersonaGetByPcId_00174800);
    s0 = v0;
    v0 = s1 & 0xFFFF;
    v0 = slti(v0, 5);
    if (v0 == 0) {
        // 0x00173540
        charge(ctx, 5);
        k_assert(a0, a1, 0x17354Cu, kDatPersonaFile, 316);
    }
    // 0x00173554: return persona->base_stats[stat]; epilogue
    charge(ctx, 9);
    v0 = s1 & 0xFFFF;
    v0 = addu(v0, s0);
    lbu(v0, v0, persona::kBaseStats);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001738D0 sub_1738D0 [datPersonaGetStat] -- 292 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1738D0(pc, stat): base + sub_173B00 + sub_173C00 + sub_173C60 (the three bonuses, each s8) of the persona of
// `pc`, summed as s16 and clamped to 0..99 (asserts stat < 5, line 316). Register-faithful (p3fes_handgen body; audit
// 2026-10-21: own frame / spills).
void sub_1738D0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::i64, hg::jal, hg::lbu,
          hg::ld, hg::lq, hg::sd, hg::slti, hg::sq;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001738d0: prologue; s2 = stat; s1 = datPersonaGetByPcId(pc); K_Assert(stat < 5)
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a1;
    jal(ctx, 0x1738F0u, gen::fn_datPersonaGetByPcId_00174800);
    s1 = v0;
    v0 = s2 & 0xFFFF;
    v0 = slti(v0, 5);
    if (v0 == 0) {
        // 0x0017390c
        charge(ctx, 5);
        k_assert(a0, a1, 0x173918u, kDatPersonaFile, 316);
    }
    // 0x00173920: s4 = base_stats[stat]; s3, s0, a0 = the three bonuses (s8); v0 = (s16)(sum)
    charge(ctx, 37);
    v0 = s2 & 0xFFFF;
    v0 = addu(v0, s1);
    lbu(v0, v0, persona::kBaseStats);
    s4 = dsll32(v0, 16);
    s4 = dsra32(s4, 16);
    a0 = s1;
    a1 = s2;
    jal(ctx, 0x17393Cu, gen::fn_sub_173B00_00173b00);
    s3 = dsll32(v0, 24);
    s3 = dsra32(s3, 24);
    a0 = s1;
    a1 = s2;
    jal(ctx, 0x173954u, gen::fn_sub_173C00_00173c00);
    s0 = dsll32(v0, 24);
    s0 = dsra32(s0, 24);
    a0 = s1;
    a1 = s2;
    jal(ctx, 0x17396Cu, gen::fn_sub_173C60_00173c60);
    a0 = dsll32(v0, 24);
    a0 = dsra32(a0, 24);
    v1 = dsll32(s4, 16);
    v1 = dsra32(v1, 16);
    v0 = dsll32(s3, 16);
    v0 = dsra32(v0, 16);
    v1 = addu(v1, v0);
    v0 = dsll32(s0, 16);
    v0 = dsra32(v0, 16);
    v0 = addu(v0, v1);
    v0 = addu(a0, v0);
    v0 = dsll32(v0, 16);
    v0 = dsra32(v0, 16);
    // clamp to 0..99
    at = slti(v0, 100);
    if (at != 0) {
        // 0x001739c0
        charge(ctx, 2);
        if (i64(v0) < 0) {
            // 0x001739c8
            charge(ctx, 1);
            v0 = 0;
        }
    } else {
        // 0x001739b4
        charge(ctx, 3);
        v0 = 99;
    }
    // 0x001739cc: return (u8); epilogue
    charge(ctx, 10);
    v0 = v0 & 0xFF;
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00174800 datPersonaGetByPcId -- 180 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// datPersonaGetByPcId(pc): the hero's current stock slot (sub_174A90 of the s16 at 0x836BA8) or member pc's persona
// (record + 220); asserts pc < 11 (779) and a non-null result (783). Register-faithful (p3fes_handgen body; audit
// 2026-10-21: own frame / spills).
void datPersonaGetByPcId(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lh, hg::lq, hg::sd, hg::sll,
          hg::slti, hg::sq, hg::subu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00174800: prologue; s0 = (u16)pc; the hero?
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0 & 0xFFFF;
    v0 = dat_unit::kHero;
    if (s0 != v0) {
        // 0x00174838: member: K_Assert(pc < 11)
        charge(ctx, 3);
        v0 = slti(s0, dat_unit::kPartyIds);
        if (v0 == 0) {
            // 0x00174844
            charge(ctx, 5);
            k_assert(a0, a1, 0x174850u, kDatPersonaFile, 779);
        }
        // 0x00174858: s0 = &kPartyRecords[pc - 2].persona
        charge(ctx, 10);
        v1 = addiu(s0, -2);
        v0 = sll(v1, 5);
        v1 = subu(v0, v1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 2);
        v0 = hi(btl::kPartyRecords);
        v0 = addiu(v0, lo(btl::kPartyRecords));
        v0 = addu(v0, v1);
        s0 = addiu(v0, party::kPersona);
    } else {
        // 0x0017481c: hero: s0 = sub_174A90(hero persona index)
        charge(ctx, 7);
        v0 = hi(btl::kHeroPersonaIdx);
        lh(a0, v0, lo(btl::kHeroPersonaIdx));
        jal(ctx, 0x174824u, gen::fn_sub_174A90_00174a90);
        s0 = v0;
    }
    // 0x00174880: K_Assert(persona)
    charge(ctx, 2);
    if (s0 == 0) {
        // 0x00174888
        charge(ctx, 5);
        k_assert(a0, a1, 0x174894u, kDatPersonaFile, 783);
    }
    // 0x0017489c: return it; epilogue
    charge(ctx, 6);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00174A90 sub_174A90 [datPersonaGetHeroPersona] -- 168 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_174A90(slot): the 52-byte hero stock slot (0x836BAC + 52 slot) when its flag bit 0 is set, else 0; asserts
// 0 <= slot < sub_175410() (the stock size, line 848). Register-faithful (p3fes_handgen body; audit 2026-10-21: own
// frame / spills).
void sub_174A90(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::i64, hg::jal, hg::ld,
          hg::lhu, hg::lq, hg::sd, hg::sll, hg::slt, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00174a90: prologue; s0 = (s16)slot; K_Assert(0 <= slot && slot < stock size)
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = dsll32(a0, 16);
    s0 = dsra32(s0, 16);
    bool slot_ok = false;
    if (i64(s0) >= 0) {
        // 0x00174aac
        charge(ctx, 6);
        jal(ctx, 0x174AACu, gen::fn_sub_175410_00175410);
        v0 = v0 & 0xFFFF;
        v0 = slt(s0, v0);
        slot_ok = v0 != 0;
    }
    if (!slot_ok) {
        // 0x00174ac4
        charge(ctx, 5);
        k_assert(a0, a1, 0x174AD0u, kDatPersonaFile, 848);
    }
    // 0x00174ad8: v1 = slot * 52 (((slot * 3) * 4 + slot) * 4); is the stock slot used?
    charge(ctx, 12);
    v0 = sll(s0, 1);
    v0 = addu(v0, s0);
    v0 = sll(v0, 2);
    v0 = addu(v0, s0);
    v1 = sll(v0, 2);
    v0 = hi(btl::kHeroPersonaStock);
    v0 = addiu(v0, lo(btl::kHeroPersonaStock));
    v0 = addu(v0, v1);
    lhu(v0, v0, persona::kFlags);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        // 0x00174b14: return &gGlobalWork[0x9AC + slot * 52] (= kHeroPersonaStock + 52 slot)
        charge(ctx, 4);
        v0 = hi(party::kGlobalWork);
        v0 = addiu(v0, lo(party::kGlobalWork));
        v0 = addu(v0, v1);
        v0 = addiu(v0, party::kHeroStockOff);
    } else {
        // 0x00174b08: an empty slot: return 0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00174b24: epilogue
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00175410 sub_175410 [datPersonaGetStockSize] -- 140 bytes; leaf frame (no stack)
// sub_175410(): the hero's persona stock size by the first set bit of 4, 2, 1, 0x2000, 0x1000 of the progression word
// 0x83A45C: 12 / 10 / 9 / 8 / 6, else 4. Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_175410_regs(EEContext& ctx) {
    using hg::Gpr, hg::charge, hg::enter, hg::lw;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x00175410: v1 = the progression bits
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = hi(btl::kPersonaStockFlags);
    lw(v1, v0, lo(btl::kPersonaStockFlags));
    v0 = v1 & 0x4;
    if (v0 == 0) {
        // 0x00175430
        charge(ctx, 3);
        v0 = v1 & 0x2;
        if (v0 == 0) {
            // 0x00175448
            charge(ctx, 3);
            v0 = v1 & 0x1;
            if (v0 == 0) {
                // 0x00175460
                charge(ctx, 3);
                v0 = v1 & 0x2000;
                if (v0 == 0) {
                    // 0x00175478
                    charge(ctx, 3);
                    v0 = v1 & 0x1000;
                    if (v0 == 0) {
                        // 0x00175490: none: 4
                        charge(ctx, 1);
                        v0 = 4;
                    } else {
                        // 0x00175484: 0x1000: 6
                        charge(ctx, 3);
                        v0 = 6;
                    }
                } else {
                    // 0x0017546c: 0x2000: 8
                    charge(ctx, 3);
                    v0 = 8;
                }
            } else {
                // 0x00175454: 0x1: 9
                charge(ctx, 3);
                v0 = 9;
            }
        } else {
            // 0x0017543c: 0x2: 10
            charge(ctx, 3);
            v0 = 10;
        }
    } else {
        // 0x00175424: 0x4: 12
        charge(ctx, 3);
        v0 = 12;
    }
    // 0x00175494: return
    charge(ctx, 2);
}

// =================================================================================================================
// k_encount.c: the Tartarus floor layout (ENCOUNT.TBL sections 1 and 2)
// =================================================================================================================

// 0x001D75F0 sub_1D75F0 [encountGetFloorByte3] -- 228 bytes; leaf frame (no stack)
// sub_1D75F0(floor, flag, idx): byte +3 of a Tartarus floor-layout row: ENCOUNT.TBL section 1 row `idx` (10-byte rows) on
// floors 20..28 and 40..48 when `flag` is 0, and on floors 51..58 and 71..78; section 2 row `floor - 30` (200-byte
// rows) on floors 30..39; otherwise 0. Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_1D75F0(EEContext& ctx) {
    using hg::Gpr, hg::addu, hg::charge, hg::enter, hg::lbu, hg::lw, hg::sll, hg::slti;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28};
    // 0x001d75f0: v0 = 0 (the default), a3 = (u16)floor; section 1 on floors 20..28 with flag 0?
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0;
    a3 = a0 & 0xFFFF;
    bool sec1 = false;
    v1 = slti(a3, 20);
    if (v1 == 0) {
        // 0x001d7604
        charge(ctx, 3);
        at = slti(a3, 29);
        if (at != 0) {
            // 0x001d7610
            charge(ctx, 3);
            v1 = a1 & 0xFFFF;
            sec1 = v1 == 0;
        }
    }
    if (!sec1) {
        // 0x001d761c: floors 40..48 with flag 0?
        charge(ctx, 3);
        v1 = slti(a3, 40);
        if (v1 == 0) {
            // 0x001d7628
            charge(ctx, 3);
            at = slti(a3, 49);
            if (at != 0) {
                // 0x001d7634
                charge(ctx, 3);
                v1 = a1 & 0xFFFF;
                sec1 = v1 == 0;
            }
        }
    }
    if (!sec1) {
        // 0x001d7640: floors 51..58?
        charge(ctx, 3);
        v1 = slti(a3, 51);
        if (v1 == 0) {
            // 0x001d764c
            charge(ctx, 3);
            at = slti(a3, 59);
            sec1 = at != 0;
        }
    }
    if (!sec1) {
        // 0x001d7658: floors 71..78?
        charge(ctx, 3);
        v1 = slti(a3, 71);
        if (v1 == 0) {
            // 0x001d7664
            charge(ctx, 3);
            at = slti(a3, 79);
            sec1 = at != 0;
        }
    }
    if (sec1) {
        // 0x001d7670: return section1[idx * 10 + 3]
        charge(ctx, 9);
        lw(a0, gp, gp_off(btl::kEncountSec1Ptr));
        v1 = a2 & 0xFFFF;
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 1);
        v0 = addu(v0, a0);
        lbu(v0, v0, 3);
    } else {
        // 0x001d7694: floors 30..39: return section2[(floor - 30) * 200 + 3]
        charge(ctx, 3);
        v1 = slti(a3, encount::kSec2FirstFloor);
        if (v1 == 0) {
            // 0x001d76a0
            charge(ctx, 3);
            at = slti(a3, 40);
            if (at != 0) {
                // 0x001d76ac: floor * 200 = ((floor * 5) * 5) << 3
                charge(ctx, 8);
                lw(a0, gp, gp_off(btl::kEncountSec2Ptr));
                v0 = sll(a3, 2);
                v1 = addu(v0, a3);
                v0 = sll(v1, 2);
                v0 = addu(v1, v0);
                v0 = sll(v0, 3);
                v0 = addu(v0, a0);
                lbu(v0, v0, encount::kSec2Bias + 3);
            }
        }
    }
    // 0x001d76cc: return
    charge(ctx, 2);
}

// 0x001D76E0 sub_1D76E0 [encountGetFloorByte2] -- 228 bytes; leaf frame (no stack)
// sub_1D76E0(floor, flag, idx): byte +2 of a Tartarus floor-layout row: ENCOUNT.TBL section 1 row `idx` (10-byte rows) on
// floors 20..28 and 40..48 when `flag` is 0, and on floors 51..58 and 71..78; section 2 row `floor - 30` (200-byte
// rows) on floors 30..39; otherwise 0. Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_1D76E0(EEContext& ctx) {
    using hg::Gpr, hg::addu, hg::charge, hg::enter, hg::lbu, hg::lw, hg::sll, hg::slti;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28};
    // 0x001d76e0: v0 = 0 (the default), a3 = (u16)floor; section 1 on floors 20..28 with flag 0?
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0;
    a3 = a0 & 0xFFFF;
    bool sec1 = false;
    v1 = slti(a3, 20);
    if (v1 == 0) {
        // 0x001d76f4
        charge(ctx, 3);
        at = slti(a3, 29);
        if (at != 0) {
            // 0x001d7700
            charge(ctx, 3);
            v1 = a1 & 0xFFFF;
            sec1 = v1 == 0;
        }
    }
    if (!sec1) {
        // 0x001d770c: floors 40..48 with flag 0?
        charge(ctx, 3);
        v1 = slti(a3, 40);
        if (v1 == 0) {
            // 0x001d7718
            charge(ctx, 3);
            at = slti(a3, 49);
            if (at != 0) {
                // 0x001d7724
                charge(ctx, 3);
                v1 = a1 & 0xFFFF;
                sec1 = v1 == 0;
            }
        }
    }
    if (!sec1) {
        // 0x001d7730: floors 51..58?
        charge(ctx, 3);
        v1 = slti(a3, 51);
        if (v1 == 0) {
            // 0x001d773c
            charge(ctx, 3);
            at = slti(a3, 59);
            sec1 = at != 0;
        }
    }
    if (!sec1) {
        // 0x001d7748: floors 71..78?
        charge(ctx, 3);
        v1 = slti(a3, 71);
        if (v1 == 0) {
            // 0x001d7754
            charge(ctx, 3);
            at = slti(a3, 79);
            sec1 = at != 0;
        }
    }
    if (sec1) {
        // 0x001d7760: return section1[idx * 10 + 2]
        charge(ctx, 9);
        lw(a0, gp, gp_off(btl::kEncountSec1Ptr));
        v1 = a2 & 0xFFFF;
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 1);
        v0 = addu(v0, a0);
        lbu(v0, v0, 2);
    } else {
        // 0x001d7784: floors 30..39: return section2[(floor - 30) * 200 + 2]
        charge(ctx, 3);
        v1 = slti(a3, encount::kSec2FirstFloor);
        if (v1 == 0) {
            // 0x001d7790
            charge(ctx, 3);
            at = slti(a3, 40);
            if (at != 0) {
                // 0x001d779c: floor * 200 = ((floor * 5) * 5) << 3
                charge(ctx, 8);
                lw(a0, gp, gp_off(btl::kEncountSec2Ptr));
                v0 = sll(a3, 2);
                v1 = addu(v0, a3);
                v0 = sll(v1, 2);
                v0 = addu(v1, v0);
                v0 = sll(v0, 3);
                v0 = addu(v0, a0);
                lbu(v0, v0, encount::kSec2Bias + 2);
            }
        }
    }
    // 0x001d77bc: return
    charge(ctx, 2);
}

// 0x001D77D0 sub_1D77D0 [encountGetFloorByte4] -- 228 bytes; leaf frame (no stack)
// sub_1D77D0(floor, flag, idx): byte +4 of a Tartarus floor-layout row: ENCOUNT.TBL section 1 row `idx` (10-byte rows) on
// floors 20..28 and 40..48 when `flag` is 0, and on floors 51..58 and 71..78; section 2 row `floor - 30` (200-byte
// rows) on floors 30..39; otherwise 0. Register-faithful (p3fes_handgen body; audit 2026-10-21: scratch GPRs).
void sub_1D77D0(EEContext& ctx) {
    using hg::Gpr, hg::addu, hg::charge, hg::enter, hg::lbu, hg::lw, hg::sll, hg::slti;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28};
    // 0x001d77d0: v0 = 0 (the default), a3 = (u16)floor; section 1 on floors 20..28 with flag 0?
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0;
    a3 = a0 & 0xFFFF;
    bool sec1 = false;
    v1 = slti(a3, 20);
    if (v1 == 0) {
        // 0x001d77e4
        charge(ctx, 3);
        at = slti(a3, 29);
        if (at != 0) {
            // 0x001d77f0
            charge(ctx, 3);
            v1 = a1 & 0xFFFF;
            sec1 = v1 == 0;
        }
    }
    if (!sec1) {
        // 0x001d77fc: floors 40..48 with flag 0?
        charge(ctx, 3);
        v1 = slti(a3, 40);
        if (v1 == 0) {
            // 0x001d7808
            charge(ctx, 3);
            at = slti(a3, 49);
            if (at != 0) {
                // 0x001d7814
                charge(ctx, 3);
                v1 = a1 & 0xFFFF;
                sec1 = v1 == 0;
            }
        }
    }
    if (!sec1) {
        // 0x001d7820: floors 51..58?
        charge(ctx, 3);
        v1 = slti(a3, 51);
        if (v1 == 0) {
            // 0x001d782c
            charge(ctx, 3);
            at = slti(a3, 59);
            sec1 = at != 0;
        }
    }
    if (!sec1) {
        // 0x001d7838: floors 71..78?
        charge(ctx, 3);
        v1 = slti(a3, 71);
        if (v1 == 0) {
            // 0x001d7844
            charge(ctx, 3);
            at = slti(a3, 79);
            sec1 = at != 0;
        }
    }
    if (sec1) {
        // 0x001d7850: return section1[idx * 10 + 4]
        charge(ctx, 9);
        lw(a0, gp, gp_off(btl::kEncountSec1Ptr));
        v1 = a2 & 0xFFFF;
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 1);
        v0 = addu(v0, a0);
        lbu(v0, v0, 4);
    } else {
        // 0x001d7874: floors 30..39: return section2[(floor - 30) * 200 + 4]
        charge(ctx, 3);
        v1 = slti(a3, encount::kSec2FirstFloor);
        if (v1 == 0) {
            // 0x001d7880
            charge(ctx, 3);
            at = slti(a3, 40);
            if (at != 0) {
                // 0x001d788c: floor * 200 = ((floor * 5) * 5) << 3
                charge(ctx, 8);
                lw(a0, gp, gp_off(btl::kEncountSec2Ptr));
                v0 = sll(a3, 2);
                v1 = addu(v0, a3);
                v0 = sll(v1, 2);
                v0 = addu(v1, v0);
                v0 = sll(v0, 3);
                v0 = addu(v0, a0);
                lbu(v0, v0, encount::kSec2Bias + 4);
            }
        }
    }
    // 0x001d78ac: return
    charge(ctx, 2);
}

}  // namespace p3fes::game

// --- the recompiled program's entry points ---------------------------------------------------------------------
// Void functions leave $v0 alone (or as their callees left it), as the originals do; 64-bit arguments are read
// whole where the original compares the registers as passed.
namespace p3fes::recomp_gen {
using namespace p3fes::game;
namespace {
u64 a64(const p3fes::EEContext& ctx, unsigned i) { return ee::core::gpr64(ctx, GPR_A0 + i); }
void r32(p3fes::EEContext& ctx, u32 v) { guest::ret32(ctx, v); }
void r64(p3fes::EEContext& ctx, u64 v) { ee::core::set_gpr64(ctx, GPR_V0, v); }
}  // namespace
void fn_sub_2FF310_002ff310(p3fes::EEContext& ctx) { r32(ctx, sub_2FF310(ctx)); }
void fn_datUnitIsGenusReady_002ff320(p3fes::EEContext& ctx) { r32(ctx, datUnitIsGenusReady(ctx)); }
void fn_sub_2FF330_002ff330(p3fes::EEContext& ctx) { r32(ctx, sub_2FF330(ctx)); }
void fn_sub_311180_00311180(p3fes::EEContext& ctx) { r32(ctx, sub_311180(ctx)); }
void fn_sub_3112C0_003112c0(p3fes::EEContext& ctx) { r32(ctx, sub_3112C0(ctx, a64(ctx, 0))); }
void fn_sub_27D880_0027d880(p3fes::EEContext& ctx) { r32(ctx, sub_27D880(ctx)); }
void fn_btlMainUpdateState_0029de80(p3fes::EEContext& ctx) { r64(ctx, btlMainUpdateState(ctx)); }
}  // namespace p3fes::recomp_gen
