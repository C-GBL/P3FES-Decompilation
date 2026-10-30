// BF script COMM handlers, third pass (game/include/p3fes/game/comm_c.h), hand-decompiled from SLUS_216.21
// (docs/ANALYSIS/18_script_vm.md sections 2.4, 3; 21_battle.md section 3.2). tests/game/test_comm_c.cpp runs each
// against its __recomp body.
//
// Fidelity. Every handler mirrors the recompiled body down to the register file:
// * virtual time (ADR-0013): guest::enter / charge / backedge follow the `ctx.cycles += N` blocks and the check points
//   of the generated body (a block is charged at its start, before the calls it contains; the loops here test first,
//   so the back-edge check comes before every body after the first test);
// * the frame: `Frame` performs the original prologue and epilogue (`addiu sp; sd ra; sq sN` ... `ld ra; lq sN;
//   addiu sp`), so the spill slots hold what the original stored, the callees' frames land where they did and the
//   lists the originals keep in their frames (sub_2CEB20, sub_2CEC30, sub_2CED60, sub_2CF070, sub_2CF1D0) sit at the
//   original addresses;
// * registers: the register transfers are written with the rt:: operations of the instructions they stand for
//   (`low24` is `dsll32 / dsrl32 8`, `move` is `daddu rd, rs, zero` ...), in the original order, so every GPR holds
//   the original 64-bit value at every call, check point and return -- the condition / selector query words and
//   their halves, the table offsets 12k / 8k, the side masks, $at of `sltu` / `slti`, the candidate filters' six
//   arguments in $a0..$t1. A callee's entry check point may preempt the thread, and the kernel then stores the whole
//   register file in guest memory, so none of these is "dead";
// * calls: every callee -- still recompiled or replaced by another slice -- is entered through its generated symbol
//   with $ra = the original link (rt::jal / rt::jalr at the call's address); the table calls (`jalr $v0`) run their
//   target through rt::lookup_func as the recompiled body does.
// Guest words addressed through $gp are read through the $gp register, as the original does.
#include "p3fes/game/comm_c.h"

#include "p3fes/ee/core.h"
#include "p3fes/game/guest.h"

namespace p3fes::recomp_gen {
// the COMM-side accessors (replaced: game/src/script/script_ops.cpp)
void fn_scrGetIntPara_0035ed20(p3fes::EEContext&);
void fn_scrSetIntReturnVal_0035f060(p3fes::EEContext&);
void fn_scrGetUserData_0035f160(p3fes::EEContext&);
// battle AI (btlAICommand.c, still recompiled unless noted)
void fn_sub_29A210_0029a210(p3fes::EEContext&);   // battle_data: [btlActionFindById] (id)
void fn_sub_2C0E30_002c0e30(p3fes::EEContext&);   // [btlAIFindUnit] (id, side mask, excluded status)
void fn_sub_2C0F40_002c0f40(p3fes::EEContext&);   // [btlAICountUnits] (action, param, status, sides, want, predicate, out list)
void fn_sub_2C3430_002c3430(p3fes::EEContext&);   // [btlAIFilterTargets] (action, param, status, flags, want, predicate)
void fn_sub_2BFF60_002bff60(p3fes::EEContext&);   // (action, list, skill, 0): the skill's candidate count
void fn_sub_2BFCB0_002bfcb0(p3fes::EEContext&);   // (action, out, 2, 0, 0): the other side's units into out (count at +0x38)
void fn_sub_2C5FC0_002c5fc0(p3fes::EEContext&);   // (action, action, s16, x)
void fn_sub_2C6300_002c6300(p3fes::EEContext&);   // (action, action, s16, x)
void fn_sub_2C5030_002c5030(p3fes::EEContext&);   // (action, action, x, y)
void fn_sub_2C65D0_002c65d0(p3fes::EEContext&);   // (action) -> a candidate
void fn_sub_2C6A00_002c6a00(p3fes::EEContext&);   // [btlAISetCommand] (action, action + 56, code)
// battle data (replaced by the battle slices; the symbol reaches whichever body is live)
void fn_datCalcRand_002ffbc0(p3fes::EEContext&);
void fn_datCalcGetHp_002ffd70(p3fes::EEContext&);
void fn_datCalcGetLevel_002ffcc0(p3fes::EEContext&);
void fn_datCalcIsDead_0030b5a0(p3fes::EEContext&);
void fn_datCalcGetBadStatusNoDown_00300530(p3fes::EEContext&);
void fn_datCalcGetSkillElement_003082f0(p3fes::EEContext&);
void fn_datCalcGetAffinityChecked_0030b4b0(p3fes::EEContext&);
void fn_datCalcGetSkillSlotCount_00308ba0(p3fes::EEContext&);
void fn_datCalcGetSkillList_00308bb0(p3fes::EEContext&);
// battle stage functions (still recompiled)
void fn_sub_2EFC90_002efc90(p3fes::EEContext&);
void fn_sub_2EFCD0_002efcd0(p3fes::EEContext&);
void fn_sub_2EC560_002ec560(p3fes::EEContext&);
void fn_sub_2F6BF0_002f6bf0(p3fes::EEContext&);
void fn_sub_2ECB30_002ecb30(p3fes::EEContext&);
void fn_sub_2F5030_002f5030(p3fes::EEContext&);
// field / g_data
void fn_K_Field_Get_001b9120(p3fes::EEContext&);  // field: &sField
void fn_sub_434E60_00434e60(p3fes::EEContext&);
void fn_sub_434D30_00434d30(p3fes::EEContext&);
void fn_sub_435370_00435370(p3fes::EEContext&);
void fn_sub_429E80_00429e80(p3fes::EEContext&);   // (object, b): object->+0x3C->u8 +0x864 = b
void fn_sub_3C8EC0_003c8ec0(p3fes::EEContext&);
void fn_sub_43A230_0043a230(p3fes::EEContext&);
void fn_sub_173380_00173380(p3fes::EEContext&);   // (pc) -> the persona's 8 skill ids [datPersonaGetSkillsByPcId]
void fn_sub_1717B0_001717b0(p3fes::EEContext&);
void fn_sub_173040_00173040(p3fes::EEContext&);
void fn_sub_27D8D0_0027d8d0(p3fes::EEContext&);
// message windows (scrGetMessageID: script_ops; itfMesMngSetChoiceMask: msg2)
void fn_scrGetMessageID_0035f140(p3fes::EEContext&);
void fn_itfMesMngSetChoiceMask_003a3ba0(p3fes::EEContext&);
void fn_sub_3A4A70_003a4a70(p3fes::EEContext&);   // (handle, key, value): set or add a {s16, s16} pair
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {

namespace rg = recomp_gen;
using namespace comm_c;
using guest::Fn;
using rt::Reg;

// --- registers ------------------------------------------------------------------------------------------------
constexpr Reg ZR = GPR_ZERO, AT = GPR_AT, V0 = GPR_V0, V1 = GPR_V1, A0 = GPR_A0, A1 = GPR_A1, A2 = GPR_A2, A3 = GPR_A3;
constexpr Reg T0 = GPR_T0, T1 = GPR_T0 + 1, T2 = GPR_T0 + 2;  // the EABI's a4..a6
constexpr Reg S0 = GPR_S0, S1 = GPR_S0 + 1, S2 = GPR_S0 + 2, S3 = GPR_S0 + 3, S4 = GPR_S0 + 4, S5 = GPR_S0 + 5,
              S6 = GPR_S0 + 6;
constexpr Reg GP = GPR_GP, SP = GPR_SP, RA = GPR_RA;

u64 R(const EEContext& ctx, Reg r) { return ee::core::gpr64(ctx, r); }
s64 Rs(const EEContext& ctx, Reg r) { return static_cast<s64>(R(ctx, r)); }

// The instruction idioms of these bodies, as the instructions themselves.
void move(EEContext& ctx, Reg d, Reg s) { rt::daddu(ctx, d, s, ZR); }
void li(EEContext& ctx, Reg d, s32 v) { rt::addiu(ctx, d, ZR, v); }
void la(EEContext& ctx, Reg d, u32 addr) {  // lui d, %hi; addiu d, d, %lo
    rt::lui(ctx, d, (addr + 0x8000u) >> 16);
    rt::addiu(ctx, d, d, static_cast<s16>(addr & 0xFFFFu));
}
void li_hi_lo(EEContext& ctx, Reg d, u32 v) {  // lui d, hi; ori d, d, lo
    rt::lui(ctx, d, v >> 16);
    rt::ori(ctx, d, d, v & 0xFFFFu);
}
void low24(EEContext& ctx, Reg d, Reg s) {  // dsll32 / dsrl32 8: the param field of a query word
    rt::dsll32(ctx, d, s, 8);
    rt::dsrl32(ctx, d, d, 8);
}
void low28(EEContext& ctx, Reg d, Reg s) {  // dsll32 / dsrl32 4: the action id of btlActionFindById
    rt::dsll32(ctx, d, s, 4);
    rt::dsrl32(ctx, d, d, 4);
}
void sext16(EEContext& ctx, Reg d, Reg s) {  // dsll32 / dsra32 16
    rt::dsll32(ctx, d, s, 16);
    rt::dsra32(ctx, d, d, 16);
}
void sext8(EEContext& ctx, Reg d, Reg s) {  // dsll32 / dsra32 24
    rt::dsll32(ctx, d, s, 24);
    rt::dsra32(ctx, d, d, 24);
}

// `jal fn` at `pc`: $ra = pc + 8, the callee through its generated symbol.
void call(EEContext& ctx, u32 pc, Fn fn) {
    rt::jal(ctx, pc);
    fn(ctx);
}
// `jalr $v0` at `pc`, as the recompiled body dispatches it.
void call_v0(EEContext& ctx, u32 pc) {
    const u32 target = rt::reg32(ctx, V0);
    rt::jalr(ctx, RA, pc);
    rt::lookup_func(target)(ctx);
}

// The original frame of `size` bytes, s0.. at 16 * k and $ra after them (every handler here).
class Frame {
public:
    Frame(EEContext& ctx, s32 size, unsigned saved) noexcept : ctx_(ctx), size_(size), saved_(saved) {
        rt::addiu(ctx_, SP, SP, -size_);
        rt::sd(ctx_, RA, SP, static_cast<s32>(16 * saved_));
        for (unsigned k = saved_; k-- > 0;) rt::sq(ctx_, S0 + k, SP, static_cast<s32>(16 * k));
    }
    ~Frame() {
        rt::ld(ctx_, RA, SP, static_cast<s32>(16 * saved_));
        for (unsigned k = saved_; k-- > 0;) rt::lq(ctx_, S0 + k, SP, static_cast<s32>(16 * k));
        rt::addiu(ctx_, SP, SP, size_);
    }
    Frame(const Frame&) = delete;
    Frame& operator=(const Frame&) = delete;

private:
    EEContext& ctx_;
    s32 size_;
    unsigned saved_;
};

// --- the script side ---------------------------------------------------------------------------------------------
// scrGetIntPara(i) at `pc` (`li a0, i` / `move a0, zero`; the result in $v0).
void int_para(EEContext& ctx, u32 pc, s32 i) {
    li(ctx, A0, i);
    call(ctx, pc, &rg::fn_scrGetIntPara_0035ed20);
}
void user_data(EEContext& ctx, u32 pc) { call(ctx, pc, &rg::fn_scrGetUserData_0035f160); }
// scrSetIntReturnVal($a0) at `pc`.
void set_result(EEContext& ctx, u32 pc) { call(ctx, pc, &rg::fn_scrSetIntReturnVal_0035f060); }
// `sltu a0, zero, v0; jal scrSetIntReturnVal`: the script sees `$v0 != 0`.
void set_result_bool(EEContext& ctx, u32 pc) {
    rt::sltu(ctx, A0, ZR, V0);
    set_result(ctx, pc);
}
// `lw v1, 8(x); lui v0, 0x8000; or a0, v1, v0`: the unit id word of action `x` as the scripts take it.
void unit_id_arg(EEContext& ctx, Reg x) {
    rt::lw(ctx, V1, x, 8);
    rt::lui(ctx, V0, 0x8000u);
    rt::or_(ctx, A0, V1, V0);
}

// --- the AI tables ------------------------------------------------------------------------------------------------
// The condition row of the kind in `k`: `sll v0, k, 1; addu v0, v0, k; sll v1, v0, 2; la v0, kCondTable; addu v0,
// v0, v1; lw v0, 0(v0); jalr v0` at `pc` ($a0 = the subject and $a1 = the param are set by the caller).
void cond_row_call(EEContext& ctx, Reg k, u32 pc) {
    rt::sll(ctx, V0, k, 1);
    rt::addu(ctx, V0, V0, k);
    rt::sll(ctx, V1, V0, 2);
    la(ctx, V0, kCondTable);
    rt::addu(ctx, V0, V0, V1);
    rt::lw(ctx, V0, V0, 0);
    call_v0(ctx, pc);
}
// The selector row of the kind in $v0: `sll v1, v0, 3; la v0, kTargetTable; addu v0, v0, v1; lw v0, 0(v0); jalr v0`.
void selector_row_call(EEContext& ctx, u32 pc) {
    rt::sll(ctx, V1, V0, 3);
    la(ctx, V0, kTargetTable);
    rt::addu(ctx, V0, V0, V1);
    rt::lw(ctx, V0, V0, 0);
    call_v0(ctx, pc);
}
// A fixed row: `lui v0, %hi(row); lw v0, %lo(row)(v0); jalr v0`.
void fixed_row_call(EEContext& ctx, u32 row, u32 pc) {
    rt::lui(ctx, V0, (row + 0x8000u) >> 16);
    rt::lw(ctx, V0, V0, static_cast<s16>(row & 0xFFFFu));
    call_v0(ctx, pc);
}
// `move a0, s; move a1, zero`, then the fixed row.
void fixed_row_call_on(EEContext& ctx, Reg subject, u32 row, u32 pc) {
    move(ctx, A0, subject);
    move(ctx, A1, ZR);
    fixed_row_call(ctx, row, pc);
}
// The fallback of the selecting handlers: if the selector found nothing ($v0 == 0), 6: row 0 (AI) on the same action
// (`jalr` at `pc`).
void fallback_to_ai(EEContext& ctx, Reg action, u32 pc) {
    if (R(ctx, V0) == 0) {
        guest::charge(ctx, 6);
        fixed_row_call_on(ctx, action, kTargetTable, pc);
    }
}

// The condition query of the handlers that build it with the kind in $a2 (sub_2CA7B0, sub_2CE2B0): from the param
// in `p`: v1 = p & 0xFFFFFF; a1 = kind << 24 (`lui a1, kind_hi`); a0 = v1 | a1 (the query); v1 = a0 & 0xFF000000;
// a2 = v1 >> 24 (the kind byte); v1 = p | a1; a1 = v1 & 0xFFFFFF (the param the condition gets).
void query_kind_in_a2(EEContext& ctx, Reg p, u32 kind_hi) {
    low24(ctx, V1, p);
    rt::lui(ctx, A1, kind_hi);
    rt::or_(ctx, A0, V1, A1);
    rt::lui(ctx, V1, 0xFF00u);
    rt::and_(ctx, V1, A0, V1);
    rt::srl(ctx, A2, V1, 24);
    rt::or_(ctx, V1, p, A1);
    low24(ctx, A1, V1);
}
// The same with the kind in $v1 (sub_2CBBA0, sub_2CC0A0, sub_2CC240): v1 = p & 0xFFFFFF; v0 = kind << 24; a0 = v1 |
// v0; v0 = a0 & 0xFF000000; v1 = v0 >> 24; a1 = a0 & 0xFFFFFF.
void query_kind_in_v1(EEContext& ctx, Reg p, u32 kind_hi) {
    low24(ctx, V1, p);
    rt::lui(ctx, V0, kind_hi);
    rt::or_(ctx, A0, V1, V0);
    rt::lui(ctx, V0, 0xFF00u);
    rt::and_(ctx, V0, A0, V0);
    rt::srl(ctx, V1, V0, 24);
    low24(ctx, A1, A0);
}
// The kind test of the condition handlers: kind != 0 -> 10: the row on `subject` (jalr at `pc`); else 3: $v0 = 0
// (the kinds are constants, so the second branch is dead, but kept).
void ask(EEContext& ctx, Reg kind, Reg subject, u32 pc) {
    if (R(ctx, kind) != 0) {
        guest::charge(ctx, 10);
        move(ctx, A0, subject);
        cond_row_call(ctx, kind, pc);
    } else {
        guest::charge(ctx, 3);
        move(ctx, V0, ZR);
    }
}

// sub_2C0E30 for the side in `side_reg` given as a script argument (sub_2CBBA0 / sub_2CBFD0): `li a1, 1`, then side 1
// -> `found1` cycles: mask 2; else 2: side 0 -> `found0` cycles: mask 1 (a1 is still 1); else 2: no search. $a0 = id,
// $a2 = 0x80000 for the search. pc1 / pc0 are the two calls.
void find_by_side_arg(EEContext& ctx, Reg side_reg, u64 found1, u32 pc1, u64 found0, u32 pc0, bool keep_in_s0) {
    li(ctx, A1, 1);
    if (R(ctx, side_reg) == R(ctx, A1)) {
        guest::charge(ctx, found1);
        li(ctx, A1, 2);
        rt::lui(ctx, A2, 8);
        call(ctx, pc1, &rg::fn_sub_2C0E30_002c0e30);
        if (keep_in_s0) move(ctx, S0, V0);
    } else {
        guest::charge(ctx, 2);
        if (R(ctx, side_reg) == 0) {
            guest::charge(ctx, found0);
            rt::lui(ctx, A2, 8);
            call(ctx, pc0, &rg::fn_sub_2C0E30_002c0e30);
            if (keep_in_s0) move(ctx, S0, V0);
        } else {
            guest::charge(ctx, 2);
        }
    }
}

// sub_2C0E30 for id arg0 on the acting unit's own side (sub_2CC0A0 / sub_2CC240): `andi a0, v0, 0xFFFF; lw v0, 48(s0);
// lbu v1, 162(v0); li v0, 1; sllv v0, v0, v1; andi a1, v0, 0xFFFF; lui a2, 8; jal` at `pc`; the unit into s0.
void find_own_side(EEContext& ctx, u32 pc) {
    rt::andi(ctx, A0, V0, 0xFFFFu);
    rt::lw(ctx, V0, S0, 0x30);
    rt::lbu(ctx, V1, V0, 0xA2);
    li(ctx, V0, 1);
    rt::sllv(ctx, V0, V0, V1);
    rt::andi(ctx, A1, V0, 0xFFFFu);
    rt::lui(ctx, A2, 8);
    call(ctx, pc, &rg::fn_sub_2C0E30_002c0e30);
    move(ctx, S0, V0);
}

}  // namespace

// === AI conditions ===================================================================================================

u32 sub_2CA7B0(EEContext& ctx) {
    // [347, 2] frame 48 (s0 = arg1, s1 = the other side's mask): 14; the user's side byte != 0 -> 1 (v1 = 0) else 3
    // (v1 = 1); 7: arg1 & 0x80000 -> 10 (the search includes dead units: a2 = 0) else 8 (a2 = 0x80000); 2: no unit
    // -> 1 ($v0 = 0) else 12: condition 0x0B (MYBAD) with arg1 on the unit, 2; 10: return $v0 != 0.
    guest::enter(ctx, 14);
    Frame frame(ctx, 48, 2);
    int_para(ctx, 0x2CA7C4, 1);
    move(ctx, S0, V0);
    user_data(ctx, 0x2CA7D0);
    rt::lw(ctx, V0, V0, 0x30);
    rt::lbu(ctx, V0, V0, 0xA2);
    if (R(ctx, V0) != 0) {
        guest::charge(ctx, 1);
        move(ctx, V1, ZR);
    } else {
        guest::charge(ctx, 3);
        li(ctx, V1, 1);
    }
    guest::charge(ctx, 7);
    li(ctx, V0, 1);
    rt::sllv(ctx, V0, V0, V1);
    rt::andi(ctx, S1, V0, 0xFFFFu);
    rt::lui(ctx, V0, 8);
    rt::and_(ctx, V0, S0, V0);
    const bool include_dead = R(ctx, V0) != 0;
    guest::charge(ctx, include_dead ? 10 : 8);
    int_para(ctx, include_dead ? 0x2CA818 : 0x2CA840, 0);
    rt::andi(ctx, A0, V0, 0xFFFFu);
    move(ctx, A1, S1);
    if (include_dead)
        move(ctx, A2, ZR);
    else
        rt::lui(ctx, A2, 8);
    call(ctx, include_dead ? 0x2CA82C : 0x2CA854, &rg::fn_sub_2C0E30_002c0e30);
    guest::charge(ctx, 2);
    if (R(ctx, V0) == 0) {
        guest::charge(ctx, 1);
        move(ctx, V0, ZR);
    } else {
        guest::charge(ctx, 12);
        query_kind_in_a2(ctx, S0, 0x0B00);
        ask(ctx, A2, V0, 0x2CA8C0);
        guest::charge(ctx, 2);
    }
    guest::charge(ctx, 10);
    set_result_bool(ctx, 0x2CA8D8);
    return 1;
}

u32 sub_2CE2B0(EEContext& ctx) {
    // [328, 2] frame 48 (s1 = arg0, s0 = arg1): 28: the action with id arg0 (btlActionFindById), condition 0x3F with
    // arg1 on it (no null check); 10: return $v0 != 0.
    guest::enter(ctx, 28);
    Frame frame(ctx, 48, 2);
    int_para(ctx, 0x2CE2C4, 0);
    move(ctx, S1, V0);
    int_para(ctx, 0x2CE2D4, 1);
    move(ctx, S0, V0);
    low28(ctx, A0, S1);
    call(ctx, 0x2CE2E8, &rg::fn_sub_29A210_0029a210);
    query_kind_in_a2(ctx, S0, 0x3F00);
    ask(ctx, A2, V0, 0x2CE34C);
    guest::charge(ctx, 10);
    set_result_bool(ctx, 0x2CE358);
    return 1;
}

namespace {
// sub_2CBAF0 / sub_2CC190 (frame 32, s0 = the query): 19: s0 = (arg0 & 0xFFFFFF) | kind << 24, the user; v1 = the
// kind byte, a1 = s0 & 0xFFFFFF; the condition on the user (jalr at base + 0x78); 9: return $v0 != 0.
u32 user_condition(EEContext& ctx, u32 base, u32 kind_hi) {
    guest::enter(ctx, 19);
    Frame frame(ctx, 32, 1);
    int_para(ctx, base + 0x10, 0);
    low24(ctx, V1, V0);
    rt::lui(ctx, V0, kind_hi);
    rt::or_(ctx, S0, V1, V0);
    user_data(ctx, base + 0x28);
    rt::lui(ctx, V1, 0xFF00u);
    rt::and_(ctx, V1, S0, V1);
    rt::srl(ctx, V1, V1, 24);
    low24(ctx, A1, S0);
    ask(ctx, V1, V0, base + 0x78);
    guest::charge(ctx, 9);
    set_result_bool(ctx, base + 0x84);
    return 1;
}
}  // namespace

u32 sub_2CBAF0(EEContext& ctx) { return user_condition(ctx, 0x2CBAF0, 0x4600); }  // [404] kind 0x46
u32 sub_2CC190(EEContext& ctx) { return user_condition(ctx, 0x2CC190, 0x4700); }  // [455] kind 0x47

u32 sub_2CBBA0(EEContext& ctx) {
    // [430, 3] frame 48 (s1 = side, s0 = the unit): 17; the unit of side arg0 with id arg1 (5 / 2 + 6 / 2 + 2); 2: none
    // -> 1 ($v0 = 0) else 14: condition 0x19 with arg2 on it, 2; 10: return $v0 != 0.
    guest::enter(ctx, 17);
    Frame frame(ctx, 48, 2);
    int_para(ctx, 0x2CBBB4, 0);
    rt::andi(ctx, S1, V0, 0xFFFFu);
    int_para(ctx, 0x2CBBC4, 1);
    rt::andi(ctx, A0, V0, 0xFFFFu);
    move(ctx, S0, ZR);
    rt::andi(ctx, V0, S1, 0xFFFFu);
    find_by_side_arg(ctx, V0, 5, 0x2CBC14, 6, 0x2CBBF8, true);
    guest::charge(ctx, 2);
    if (R(ctx, S0) == 0) {
        guest::charge(ctx, 1);
        move(ctx, V0, ZR);
    } else {
        guest::charge(ctx, 14);
        int_para(ctx, 0x2CBC2C, 2);
        query_kind_in_v1(ctx, V0, 0x1900);
        ask(ctx, V1, S0, 0x2CBC8C);
        guest::charge(ctx, 2);
    }
    guest::charge(ctx, 10);
    set_result_bool(ctx, 0x2CBCA4);
    return 1;
}

u32 sub_2CBFD0(EEContext& ctx) {
    // [446, 2] frame 32 (s0 = side): 16; the unit of side arg0 with id arg1 (4 / 2 + 5 / 2 + 2; $v0 = 0 when there is
    // no search); 2: none -> 1 ($v0 = 0) else 8: condition row 67 (unit, 0); 9: return $v0 != 0.
    guest::enter(ctx, 16);
    Frame frame(ctx, 32, 1);
    int_para(ctx, 0x2CBFE0, 0);
    rt::andi(ctx, S0, V0, 0xFFFFu);
    int_para(ctx, 0x2CBFF0, 1);
    rt::andi(ctx, A0, V0, 0xFFFFu);
    move(ctx, V0, ZR);
    rt::andi(ctx, V1, S0, 0xFFFFu);
    find_by_side_arg(ctx, V1, 4, 0x2CC03C, 5, 0x2CC024, false);
    guest::charge(ctx, 2);
    if (R(ctx, V0) == 0) {
        guest::charge(ctx, 1);
        move(ctx, V0, ZR);
    } else {
        guest::charge(ctx, 8);
        fixed_row_call_on(ctx, V0, kCondRow67, 0x2CC05C);
    }
    guest::charge(ctx, 9);
    set_result_bool(ctx, 0x2CC074);
    return 1;
}

namespace {
// sub_2CC0A0 / sub_2CC240 (frame 32, s0 = the user, then the unit): 21: own side's unit with id arg0; none -> 1
// ($v0 = 0) else 14: condition `kind` with arg1 on it (jalr at base + 0xB8), 2; 9: return $v0 != 0.
u32 own_unit_condition(EEContext& ctx, u32 base, u32 kind_hi) {
    guest::enter(ctx, 21);
    Frame frame(ctx, 32, 1);
    user_data(ctx, base + 0xC);
    move(ctx, S0, V0);
    int_para(ctx, base + 0x1C, 0);
    find_own_side(ctx, base + 0x40);
    if (R(ctx, S0) == 0) {
        guest::charge(ctx, 1);
        move(ctx, V0, ZR);
    } else {
        guest::charge(ctx, 14);
        int_para(ctx, base + 0x58, 1);
        query_kind_in_v1(ctx, V0, kind_hi);
        ask(ctx, V1, S0, base + 0xB8);
        guest::charge(ctx, 2);
    }
    guest::charge(ctx, 9);
    set_result_bool(ctx, base + 0xD0);
    return 1;
}
}  // namespace

u32 sub_2CC0A0(EEContext& ctx) { return own_unit_condition(ctx, 0x2CC0A0, 0x3A00); }  // [454] kind 0x3A
u32 sub_2CC240(EEContext& ctx) { return own_unit_condition(ctx, 0x2CC240, 0x3E00); }  // [463] kind 0x3E

// === AI target choices ===============================================================================================

namespace {
// sub_2CD570 / sub_2CD690 / sub_2CD740 (frame 48, s1 = the query, s0 = the user): 29: s1 = (arg0 & 0xFFFFFF) |
// kind << 24; the selector of its kind (user, param) through the jalr at base + 0x64; none -> 6: row 0 (jalr at base
// + 0x84); 7.
u32 select_target(EEContext& ctx, u32 base, u32 kind_hi) {
    guest::enter(ctx, 29);
    Frame frame(ctx, 48, 2);
    int_para(ctx, base + 0x14, 0);
    low24(ctx, V1, V0);
    rt::lui(ctx, V0, kind_hi);
    rt::or_(ctx, S1, V1, V0);
    user_data(ctx, base + 0x2C);
    move(ctx, S0, V0);
    low24(ctx, A1, S1);
    move(ctx, A0, S0);
    rt::lui(ctx, V0, 0xFF00u);
    rt::and_(ctx, V0, S1, V0);
    rt::srl(ctx, V0, V0, 24);
    selector_row_call(ctx, base + 0x64);
    fallback_to_ai(ctx, S0, base + 0x84);
    guest::charge(ctx, 7);
    return 1;
}
}  // namespace

u32 sub_2CD570(EEContext& ctx) { return select_target(ctx, 0x2CD570, 0x2100); }  // [317] kind 0x21
u32 sub_2CD690(EEContext& ctx) { return select_target(ctx, 0x2CD690, 0x2300); }  // [443] kind 0x23
u32 sub_2CD740(EEContext& ctx) { return select_target(ctx, 0x2CD740, 0x2400); }  // [444] kind 0x24

u32 sub_2CD620(EEContext& ctx) {
    // [319, 0] frame 32 (s0 = the user): 14: selector row 34 (user, 0); none -> 6: row 0; 6.
    guest::enter(ctx, 14);
    Frame frame(ctx, 32, 1);
    user_data(ctx, 0x2CD62C);
    move(ctx, S0, V0);
    fixed_row_call_on(ctx, S0, kSelRow34, 0x2CD648);
    fallback_to_ai(ctx, S0, 0x2CD668);
    guest::charge(ctx, 6);
    return 1;
}

u32 sub_2CE380(EEContext& ctx) {
    // [253, 1] frame 32 (s0 = the user): 15: sub_2BFF60(user, 0, skill u16 +0x6E, 0) & 0xFFFF; zero -> 12: the target is
    // the action with id arg0 (+0x38 = it, u16 +0x6A = 1); else 8: row 0 (user, 0), none -> 6: row 0 again; 6.
    guest::enter(ctx, 15);
    Frame frame(ctx, 32, 1);
    user_data(ctx, 0x2CE38C);
    move(ctx, S0, V0);
    move(ctx, A0, S0);
    move(ctx, A1, ZR);
    rt::lhu(ctx, A2, V0, 0x6E);
    move(ctx, A3, ZR);
    call(ctx, 0x2CE3A8, &rg::fn_sub_2BFF60_002bff60);
    rt::andi(ctx, V0, V0, 0xFFFFu);
    if (R(ctx, V0) != 0) {
        guest::charge(ctx, 8);
        fixed_row_call_on(ctx, S0, kTargetTable, 0x2CE3FC);
        fallback_to_ai(ctx, S0, 0x2CE41C);
    } else {
        guest::charge(ctx, 12);
        int_para(ctx, 0x2CE3C0, 0);
        low28(ctx, A0, V0);
        call(ctx, 0x2CE3D0, &rg::fn_sub_29A210_0029a210);
        rt::sw(ctx, V0, S0, 0x38);
        li(ctx, V0, 1);
        rt::sh(ctx, V0, S0, 0x6A);
    }
    guest::charge(ctx, 6);
    return 1;
}

u32 sub_2D05C0(EEContext& ctx) {
    // [323, 4] frame 32 (s0 = the user): 14: skill u16 +0x6E = arg0; 0x133 -> 7: command 8, sub_2EFCD0(user); else 3:
    // 0x68 -> 7: command 8, sub_2EFC90(user); else 3: 0x132 -> the same; else 2 + 2: command 9. 20: +0x76/+0x78/+0x7A
    // = arg1..arg3; selector MYAI (user, 0), none -> 6: row 0; 6.
    guest::enter(ctx, 14);
    Frame frame(ctx, 32, 1);
    user_data(ctx, 0x2D05CC);
    move(ctx, S0, V0);
    int_para(ctx, 0x2D05DC, 0);
    rt::sh(ctx, V0, S0, 0x6E);
    rt::lhu(ctx, V1, S0, 0x6E);
    li(ctx, V0, 0x133);
    bool fc90 = false, fcd0 = false;
    if (R(ctx, V1) == R(ctx, V0)) {
        fcd0 = true;
    } else {
        guest::charge(ctx, 3);
        li(ctx, V0, 0x68);
        if (R(ctx, V1) == R(ctx, V0)) {
            fc90 = true;
        } else {
            guest::charge(ctx, 3);
            li(ctx, V0, 0x132);
            if (R(ctx, V1) == R(ctx, V0)) {
                fc90 = true;
            } else {
                guest::charge(ctx, 2 + 2);
                li(ctx, V0, 9);
                rt::sh(ctx, V0, S0, 0x6C);
            }
        }
    }
    if (fc90 || fcd0) {
        guest::charge(ctx, 7);
        li(ctx, V0, 8);
        rt::sh(ctx, V0, S0, 0x6C);
        move(ctx, A0, S0);
        if (fcd0)
            call(ctx, 0x2D0640, &rg::fn_sub_2EFCD0_002efcd0);
        else
            call(ctx, 0x2D0624, &rg::fn_sub_2EFC90_002efc90);
    }
    guest::charge(ctx, 20);
    int_para(ctx, 0x2D065C, 1);
    rt::sh(ctx, V0, S0, 0x76);
    int_para(ctx, 0x2D066C, 2);
    rt::sh(ctx, V0, S0, 0x78);
    int_para(ctx, 0x2D067C, 3);
    rt::sh(ctx, V0, S0, 0x7A);
    fixed_row_call_on(ctx, S0, kSelMyAi, 0x2D0698);
    fallback_to_ai(ctx, S0, 0x2D06B8);
    guest::charge(ctx, 6);
    return 1;
}

u32 sub_2D0760(EEContext& ctx) {
    // [373, 1] frame 48 (s1 = the user, s0 = arg0): 17: the battle stage (gBtl->+0xBBC->u16 +8); 0x1B4 -> 8:
    // sub_2C6A00(user, user + 56, 0x126), sub_2F6BF0(arg0); else 3: 0x1A5 -> 10: sub_2C6A00(..., 0x16B),
    // sub_2EC560(arg0); else 2. 8: selector MYAI (user, 0), none -> 6: row 0; 7.
    guest::enter(ctx, 17);
    Frame frame(ctx, 48, 2);
    user_data(ctx, 0x2D0770);
    move(ctx, S1, V0);
    int_para(ctx, 0x2D0780, 0);
    move(ctx, S0, V0);
    rt::lw(ctx, V0, GP, -0x4904);
    rt::lw(ctx, V0, V0, 0xBBC);
    rt::lhu(ctx, V1, V0, 8);
    li(ctx, V0, 0x1B4);
    auto command = [&](u32 pc_set, s32 skill, u32 pc_stage, Fn stage) {
        move(ctx, A0, S1);
        rt::addiu(ctx, A1, S1, 0x38);
        li(ctx, A2, skill);
        call(ctx, pc_set, &rg::fn_sub_2C6A00_002c6a00);
        move(ctx, A0, S0);
        call(ctx, pc_stage, stage);
    };
    if (R(ctx, V1) == R(ctx, V0)) {
        guest::charge(ctx, 8);
        command(0x2D07EC, 0x126, 0x2D07F8, &rg::fn_sub_2F6BF0_002f6bf0);
    } else {
        guest::charge(ctx, 3);
        li(ctx, V0, 0x1A5);
        if (R(ctx, V1) == R(ctx, V0)) {
            guest::charge(ctx, 10);
            command(0x2D07C4, 0x16B, 0x2D07D0, &rg::fn_sub_2EC560_002ec560);
        } else {
            guest::charge(ctx, 2);
        }
    }
    guest::charge(ctx, 8);
    fixed_row_call_on(ctx, S1, kSelMyAi, 0x2D0810);
    fallback_to_ai(ctx, S1, 0x2D0830);
    guest::charge(ctx, 7);
    return 1;
}

u32 sub_2D0AF0(EEContext& ctx) {
    // [380, 1] frame 32 (s0 = the user): 16: sub_2ECB30(user, (s16)arg0); non-zero -> 10: command 8 (+0x6C), selector
    // MYAI (user, 0), none -> 6: row 0; 6.
    guest::enter(ctx, 16);
    Frame frame(ctx, 32, 1);
    user_data(ctx, 0x2D0AFC);
    move(ctx, S0, V0);
    int_para(ctx, 0x2D0B0C, 0);
    sext16(ctx, A1, V0);
    move(ctx, A0, S0);
    call(ctx, 0x2D0B20, &rg::fn_sub_2ECB30_002ecb30);
    if (R(ctx, V0) != 0) {
        guest::charge(ctx, 10);
        li(ctx, V0, 8);
        rt::sh(ctx, V0, S0, 0x6C);
        fixed_row_call_on(ctx, S0, kSelMyAi, 0x2D0B48);
        fallback_to_ai(ctx, S0, 0x2D0B68);
    }
    guest::charge(ctx, 6);
    return 1;
}

// === AI target pickers ===============================================================================================

namespace {
// sub_2CE170 / sub_2CE210 (frame 64, s2 = the user, s1 = arg0, s0 = arg1): one block of 39: fn(user, the action with
// id arg0, (s16)arg1, 0); return `~$v0 != 0` (`nor v0, v0, zero; sltu a0, zero, v0`).
u32 pair_query(EEContext& ctx, u32 base, Fn fn) {
    guest::enter(ctx, 39);
    Frame frame(ctx, 64, 3);
    user_data(ctx, base + 0x14);
    move(ctx, S2, V0);
    int_para(ctx, base + 0x24, 0);
    move(ctx, S1, V0);
    int_para(ctx, base + 0x34, 1);
    move(ctx, S0, V0);
    low28(ctx, A0, S1);
    call(ctx, base + 0x48, &rg::fn_sub_29A210_0029a210);
    sext16(ctx, A2, S0);
    move(ctx, A0, S2);
    move(ctx, A1, V0);
    move(ctx, A3, ZR);
    call(ctx, base + 0x64, fn);
    rt::nor(ctx, V0, V0, ZR);
    set_result_bool(ctx, base + 0x74);
    return 1;
}

// sub_2CF7E0 / sub_2CF890 (frame 80, s3 = the user, s1 = arg0, s0 = arg1, s2 = arg2): one block of 44: return
// fn(user, the action with id arg0, (s16)arg1, arg2).
u32 triple_query(EEContext& ctx, u32 base, Fn fn) {
    guest::enter(ctx, 44);
    Frame frame(ctx, 80, 4);
    user_data(ctx, base + 0x18);
    move(ctx, S3, V0);
    int_para(ctx, base + 0x28, 0);
    move(ctx, S1, V0);
    int_para(ctx, base + 0x38, 1);
    move(ctx, S0, V0);
    int_para(ctx, base + 0x48, 2);
    move(ctx, S2, V0);
    low28(ctx, A0, S1);
    call(ctx, base + 0x5C, &rg::fn_sub_29A210_0029a210);
    sext16(ctx, A2, S0);
    move(ctx, A0, S3);
    move(ctx, A1, V0);
    move(ctx, A3, S2);
    call(ctx, base + 0x78, fn);
    move(ctx, A0, V0);
    set_result(ctx, base + 0x84);
    return 1;
}
}  // namespace

u32 sub_2CE170(EEContext& ctx) { return pair_query(ctx, 0x2CE170, &rg::fn_sub_2C5FC0_002c5fc0); }    // [251]
u32 sub_2CE210(EEContext& ctx) { return pair_query(ctx, 0x2CE210, &rg::fn_sub_2C6300_002c6300); }    // [252]
u32 sub_2CF7E0(EEContext& ctx) { return triple_query(ctx, 0x2CF7E0, &rg::fn_sub_2C5FC0_002c5fc0); }  // [265]
u32 sub_2CF890(EEContext& ctx) { return triple_query(ctx, 0x2CF890, &rg::fn_sub_2C6300_002c6300); }  // [266]

u32 sub_2CF940(EEContext& ctx) {
    // [267, 3] frame 80 (s3 = the user, s0 = arg0, s2 = arg1, s1 = arg2): one block of 43: return sub_2C5030(user, the
    // action with id arg0, arg1, arg2).
    guest::enter(ctx, 43);
    Frame frame(ctx, 80, 4);
    user_data(ctx, 0x2CF958);
    move(ctx, S3, V0);
    int_para(ctx, 0x2CF968, 0);
    move(ctx, S0, V0);
    int_para(ctx, 0x2CF978, 1);
    move(ctx, S2, V0);
    int_para(ctx, 0x2CF988, 2);
    move(ctx, S1, V0);
    low28(ctx, A0, S0);
    call(ctx, 0x2CF99C, &rg::fn_sub_29A210_0029a210);
    move(ctx, A0, S3);
    move(ctx, A1, V0);
    move(ctx, A2, S2);
    move(ctx, A3, S1);
    call(ctx, 0x2CF9B4, &rg::fn_sub_2C5030_002c5030);
    move(ctx, A0, V0);
    set_result(ctx, 0x2CF9C0);
    return 1;
}

namespace {
// The candidate filter's arguments as the handlers set them: a0 = the user (in `user`), a1 = the param ($v0), a2 =
// `status` (`lui a2, 0x10` or `move a2, zero`), a3 = `flags` (`li`), t0 = `want` (`move t0, zero` / `li t0, 1`),
// t1 = `pred`; then `jal sub_2C3430` at `pc` and `li v1, 1`. Returns whether it found candidates ($v0 == 1).
bool filter_targets(EEContext& ctx, Reg user, u32 status_hi, s32 flags, s32 want, u32 pred, u32 pc) {
    move(ctx, A0, user);
    move(ctx, A1, V0);
    if (status_hi != 0)
        rt::lui(ctx, A2, status_hi);
    else
        move(ctx, A2, ZR);
    li(ctx, A3, flags);
    if (want != 0)
        li(ctx, T0, want);
    else
        move(ctx, T0, ZR);
    la(ctx, T1, pred);
    call(ctx, pc, &rg::fn_sub_2C3430_002c3430);
    li(ctx, V1, 1);
    return R(ctx, V0) == R(ctx, V1);
}

// `li a0, -1; jal scrSetIntReturnVal` at `pc` (3 cycles): no target.
void no_target(EEContext& ctx, u32 pc) {
    guest::charge(ctx, 3);
    li(ctx, A0, -1);
    set_result(ctx, pc);
}

// The candidate-list element `index` of the user in `user`: `sll v0, i, 2; addu v0, user, v0` (then `lw x, 0x38(v0)`).
void candidate_slot(EEContext& ctx, Reg user, Reg index) {
    rt::sll(ctx, V0, index, 2);
    rt::addu(ctx, V0, user, V0);
}

// sub_2CE6C0 .. sub_2CEA40 (frame 32, s0 = the user): 21: the candidates (status, flags, pred); none -> no target; one
// -> 8: its id; else 12: datCalcRand(count) picks one; 6.
u32 random_candidate(EEContext& ctx, u32 base, u32 status_hi, s32 flags, u32 pred) {
    guest::enter(ctx, 21);
    Frame frame(ctx, 32, 1);
    user_data(ctx, base + 0xC);
    move(ctx, S0, V0);
    int_para(ctx, base + 0x1C, 0);
    if (!filter_targets(ctx, S0, status_hi, flags, 0, pred, base + 0x40)) {
        no_target(ctx, base + 0xB4);
    } else {
        guest::charge(ctx, 3);
        rt::lhu(ctx, A0, S0, 0x6A);
        if (R(ctx, A0) != R(ctx, V1)) {
            guest::charge(ctx, 12);
            call(ctx, base + 0x80, &rg::fn_datCalcRand_002ffbc0);
            rt::sll(ctx, V0, V0, 2);
            rt::addu(ctx, V0, V0, S0);
            rt::lw(ctx, V0, V0, 0x38);
            unit_id_arg(ctx, V0);
            set_result(ctx, base + 0xA0);
        } else {
            guest::charge(ctx, 8);
            rt::lw(ctx, V0, S0, 0x38);
            unit_id_arg(ctx, V0);
            set_result(ctx, base + 0x70);
        }
    }
    guest::charge(ctx, 6);
    return 1;
}

// sub_2CF450 .. sub_2CFD80 (frame 96: s4 = the user, s3 = the best, s0 = its HP, s1 = i, s2 = the candidate): 25:
// the candidates; none -> no target; one -> 3: it; else 6, then the walk: test 4 (i < count), back-edge check, body
// 11: HP = datCalcGetHp(...) & 0xFFFF; HP < best -> 2: take it; 1: ++i. 7: its id; 10.
u32 lowest_hp_candidate(EEContext& ctx, u32 base, u32 status_hi, s32 flags, u32 pred) {
    guest::enter(ctx, 25);
    Frame frame(ctx, 96, 5);
    user_data(ctx, base + 0x1C);
    move(ctx, S4, V0);
    int_para(ctx, base + 0x2C, 0);
    if (!filter_targets(ctx, S4, status_hi, flags, 0, pred, base + 0x50)) {
        no_target(ctx, base + 0xFC);
    } else {
        guest::charge(ctx, 3);
        rt::lhu(ctx, V0, S4, 0x6A);
        if (R(ctx, V0) != R(ctx, V1)) {
            guest::charge(ctx, 6);
            move(ctx, S3, ZR);
            li_hi_lo(ctx, S0, 0x0FFFFFFFu);
            move(ctx, S1, ZR);
            for (;;) {
                guest::charge(ctx, 4);
                rt::lhu(ctx, V0, S4, 0x6A);
                rt::sltu(ctx, V0, S1, V0);
                if (R(ctx, V0) == 0) break;
                guest::backedge(ctx);
                guest::charge(ctx, 11);
                candidate_slot(ctx, S4, S1);
                rt::lw(ctx, S2, V0, 0x38);
                rt::lw(ctx, V0, S2, 0x30);
                rt::lw(ctx, A0, V0, 0xA2C);
                call(ctx, base + 0xA8, &rg::fn_datCalcGetHp_002ffd70);
                rt::andi(ctx, V0, V0, 0xFFFFu);
                rt::sltu(ctx, AT, V0, S0);
                if (R(ctx, AT) != 0) {
                    guest::charge(ctx, 2);
                    move(ctx, S3, S2);
                    move(ctx, S0, V0);
                }
                guest::charge(ctx, 1);
                rt::addiu(ctx, S1, S1, 1);
            }
        } else {
            guest::charge(ctx, 3);
            rt::lw(ctx, S3, S4, 0x38);
        }
        guest::charge(ctx, 7);
        unit_id_arg(ctx, S3);
        set_result(ctx, base + 0xE8);
    }
    guest::charge(ctx, 10);
    return 1;
}
}  // namespace

u32 sub_2CE6C0(EEContext& ctx) { return random_candidate(ctx, 0x2CE6C0, 0x10, 0x2E, 0x2C1ED0); }   // [257]
u32 sub_2CE7A0(EEContext& ctx) { return random_candidate(ctx, 0x2CE7A0, 0, 0x2F, 0x2C1ED0); }      // [258]
u32 sub_2CE880(EEContext& ctx) { return random_candidate(ctx, 0x2CE880, 0, 0x2C, 0x2C30F0); }      // [272]
u32 sub_2CE960(EEContext& ctx) { return random_candidate(ctx, 0x2CE960, 0x10, 0x2C, 0x2C30F0); }   // [273]
u32 sub_2CEA40(EEContext& ctx) { return random_candidate(ctx, 0x2CEA40, 0, 0x2D, 0x2C30F0); }      // [274]
u32 sub_2CF450(EEContext& ctx) { return lowest_hp_candidate(ctx, 0x2CF450, 0, 0x2E, 0x2C1ED0); }    // [259]
u32 sub_2CF580(EEContext& ctx) { return lowest_hp_candidate(ctx, 0x2CF580, 0x10, 0x2E, 0x2C1ED0); } // [260]
u32 sub_2CF6B0(EEContext& ctx) { return lowest_hp_candidate(ctx, 0x2CF6B0, 0, 0x2F, 0x2C1ED0); }    // [261]
u32 sub_2CFB20(EEContext& ctx) { return lowest_hp_candidate(ctx, 0x2CFB20, 0, 0x2C, 0x2C30F0); }    // [262]
u32 sub_2CFC50(EEContext& ctx) { return lowest_hp_candidate(ctx, 0x2CFC50, 0x10, 0x2C, 0x2C30F0); } // [263]
u32 sub_2CFD80(EEContext& ctx) { return lowest_hp_candidate(ctx, 0x2CFD80, 0, 0x2D, 0x2C30F0); }    // [264]

u32 sub_2CE5C0(EEContext& ctx) {
    // [256, 1] frame 48 (s1 = the user, s0 = arg0): 23: the candidates (0, 0x2E, sub_2C1ED0); none -> no target; one ->
    // 8: its id; else 3: arg0 & 0xE -> 5: sub_2C65D0(user) else 5: a random one; 7: its id; 7.
    guest::enter(ctx, 23);
    Frame frame(ctx, 48, 2);
    user_data(ctx, 0x2CE5D0);
    move(ctx, S1, V0);
    int_para(ctx, 0x2CE5E0, 0);
    move(ctx, S0, V0);
    if (!filter_targets(ctx, S1, 0, 0x2E, 0, 0x2C1ED0, 0x2CE608)) {
        no_target(ctx, 0x2CE69C);
    } else {
        guest::charge(ctx, 3);
        rt::lhu(ctx, A0, S1, 0x6A);
        if (R(ctx, A0) != R(ctx, V1)) {
            guest::charge(ctx, 3);
            rt::andi(ctx, V0, S0, 0xE);
            guest::charge(ctx, 5);
            if (R(ctx, V0) == 0) {
                call(ctx, 0x2CE668, &rg::fn_datCalcRand_002ffbc0);
                rt::sll(ctx, V0, V0, 2);
                rt::addu(ctx, V0, V0, S1);
                rt::lw(ctx, V0, V0, 0x38);
            } else {
                move(ctx, A0, S1);
                call(ctx, 0x2CE658, &rg::fn_sub_2C65D0_002c65d0);
            }
            guest::charge(ctx, 7);
            unit_id_arg(ctx, V0);
            set_result(ctx, 0x2CE688);
        } else {
            guest::charge(ctx, 8);
            rt::lw(ctx, V0, S1, 0x38);
            unit_id_arg(ctx, V0);
            set_result(ctx, 0x2CE638);
        }
    }
    guest::charge(ctx, 7);
    return 1;
}

u32 sub_2CEF10(EEContext& ctx) {
    // [460, 1] frame 128 (s5 = the user, s3 = the best, s6 = its level, s0 = its HP, s2 = i, s4 = the candidate, s1 =
    // its level): 27: the candidates (0, 0x2C, sub_2C30F0); none -> no target; one -> 3: it; else 6 and the walk (test
    // 4, back-edge check): body 11: level < best level -> 1 (skip); else 8: HP > best HP -> 2: take it; 1: best level =
    // level; 1: ++i. 7: its id; 12; returns -1.
    guest::enter(ctx, 27);
    Frame frame(ctx, 128, 7);
    user_data(ctx, 0x2CEF34);
    move(ctx, S5, V0);
    int_para(ctx, 0x2CEF44, 0);
    if (!filter_targets(ctx, S5, 0, 0x2C, 0, 0x2C30F0, 0x2CEF68)) {
        no_target(ctx, 0x2CF038);
    } else {
        guest::charge(ctx, 3);
        rt::lhu(ctx, V0, S5, 0x6A);
        if (R(ctx, V0) != R(ctx, V1)) {
            guest::charge(ctx, 6);
            move(ctx, S3, ZR);
            move(ctx, S6, ZR);
            move(ctx, S0, ZR);
            move(ctx, S2, ZR);
            for (;;) {
                guest::charge(ctx, 4);
                rt::lhu(ctx, V0, S5, 0x6A);
                rt::sltu(ctx, V0, S2, V0);
                if (R(ctx, V0) == 0) break;
                guest::backedge(ctx);
                guest::charge(ctx, 11);
                candidate_slot(ctx, S5, S2);
                rt::lw(ctx, S4, V0, 0x38);
                rt::lw(ctx, V0, S4, 0x30);
                rt::lw(ctx, A0, V0, 0xA2C);
                call(ctx, 0x2CEFC0, &rg::fn_datCalcGetLevel_002ffcc0);
                rt::andi(ctx, S1, V0, 0xFF);
                rt::sltu(ctx, V0, S1, S6);
                if (R(ctx, V0) == 0) {
                    guest::charge(ctx, 8);
                    rt::lw(ctx, V0, S4, 0x30);
                    rt::lw(ctx, A0, V0, 0xA2C);
                    call(ctx, 0x2CEFE0, &rg::fn_datCalcGetHp_002ffd70);
                    rt::andi(ctx, V0, V0, 0xFFFFu);
                    rt::sltu(ctx, AT, S0, V0);
                    if (R(ctx, AT) != 0) {
                        guest::charge(ctx, 2);
                        move(ctx, S3, S4);
                        move(ctx, S0, V0);
                    }
                    guest::charge(ctx, 1);
                    move(ctx, S6, S1);
                }
                guest::charge(ctx, 1);
                rt::addiu(ctx, S2, S2, 1);
            }
        } else {
            guest::charge(ctx, 3);
            rt::lw(ctx, S3, S5, 0x38);
        }
        guest::charge(ctx, 7);
        unit_id_arg(ctx, S3);
        set_result(ctx, 0x2CF024);
    }
    guest::charge(ctx, 12);
    return 0xFFFFFFFFu;
}

namespace {
// `li v1, 0xFFEFFFFF; and v0, v0, v1`: a bad status other than bit 20 (sub_2CF070 / sub_2CF340).
void bad_status_but_bit20(EEContext& ctx) {
    li_hi_lo(ctx, V1, 0xFFEFFFFFu);
    rt::and_(ctx, V0, V0, V1);
}
}  // namespace

u32 sub_2CF070(EEContext& ctx) {
    // [461, 1] frame 128 (s3 = the user, s1 = n, s2 = i, s0 = the candidate; the list at sp + 0x50): 24: the candidates
    // (0, 0x2C, sub_2C30F0); none -> no target; else 4 and the walk (test 5, back-edge check): body 13: no bad status
    // (datCalcGetBadStatusNoDown & ~0x100000 == 0) -> 6: list[n++] = it; 2: ++i. 3: n == 0 -> 5: -1; else 12: a random
    // one's id. 9; returns -1.
    guest::enter(ctx, 24);
    Frame frame(ctx, 128, 4);
    user_data(ctx, 0x2CF088);
    move(ctx, S3, V0);
    int_para(ctx, 0x2CF098, 0);
    if (!filter_targets(ctx, S3, 0, 0x2C, 0, 0x2C30F0, 0x2CF0BC)) {
        no_target(ctx, 0x2CF19C);
    } else {
        guest::charge(ctx, 4);
        move(ctx, S1, ZR);
        move(ctx, S2, ZR);
        for (;;) {
            guest::charge(ctx, 5);
            rt::andi(ctx, V1, S2, 0xFFFFu);
            rt::lhu(ctx, V0, S3, 0x6A);
            rt::slt(ctx, V0, V1, V0);
            if (R(ctx, V0) == 0) break;
            guest::backedge(ctx);
            guest::charge(ctx, 13);
            rt::andi(ctx, V0, S2, 0xFFFFu);
            rt::sll(ctx, V0, V0, 2);
            rt::addu(ctx, V0, S3, V0);
            rt::lw(ctx, S0, V0, 0x38);
            rt::lw(ctx, V0, S0, 0x30);
            rt::lw(ctx, A0, V0, 0xA2C);
            call(ctx, 0x2CF0F8, &rg::fn_datCalcGetBadStatusNoDown_00300530);
            bad_status_but_bit20(ctx);
            if (R(ctx, V0) == 0) {
                guest::charge(ctx, 6);
                rt::andi(ctx, V0, S1, 0xFFFFu);
                rt::sll(ctx, V0, V0, 2);
                rt::addu(ctx, V0, V0, SP);
                rt::sw(ctx, S0, V0, 0x50);
                rt::addiu(ctx, V0, S1, 1);
                rt::andi(ctx, S1, V0, 0xFFFFu);
            }
            guest::charge(ctx, 2);
            rt::addiu(ctx, V0, S2, 1);
            rt::andi(ctx, S2, V0, 0xFFFFu);
        }
        guest::charge(ctx, 3);
        rt::andi(ctx, A0, S1, 0xFFFFu);
        if (R(ctx, A0) != 0) {
            guest::charge(ctx, 12);
            call(ctx, 0x2CF168, &rg::fn_datCalcRand_002ffbc0);
            rt::sll(ctx, V0, V0, 2);
            rt::addu(ctx, V0, V0, SP);
            rt::lw(ctx, V0, V0, 0x50);
            unit_id_arg(ctx, V0);
            set_result(ctx, 0x2CF188);
        } else {
            guest::charge(ctx, 5);
            li(ctx, A0, -1);
            set_result(ctx, 0x2CF158);
        }
    }
    guest::charge(ctx, 9);
    return 0xFFFFFFFFu;
}

u32 sub_2CF1D0(EEContext& ctx) {
    // [462, 1] frame 144 (s4 = the user, s1 = n, s2 = the best level, s3 = i, s0 = the candidate; the list at sp +
    // 0x60): 25: the candidates (0, 0x2C, sub_2C3120, want 1); none -> no target; one -> 3: it; else 5 and the walk
    // (test 4, back-edge check): body 11: level < best -> 1; else 2: level == best -> 8: list[n++] = it; else 3: best =
    // level, list = { it }; 1: ++i. 6: a random one of the list; 7: its id; 10; returns -1.
    guest::enter(ctx, 25);
    Frame frame(ctx, 144, 5);
    user_data(ctx, 0x2CF1EC);
    move(ctx, S4, V0);
    int_para(ctx, 0x2CF1FC, 0);
    if (!filter_targets(ctx, S4, 0, 0x2C, 1, 0x2C3120, 0x2CF220)) {
        no_target(ctx, 0x2CF30C);
    } else {
        guest::charge(ctx, 3);
        rt::lhu(ctx, V0, S4, 0x6A);
        if (R(ctx, V0) != R(ctx, V1)) {
            guest::charge(ctx, 5);
            move(ctx, S1, ZR);
            move(ctx, S2, ZR);
            move(ctx, S3, ZR);
            for (;;) {
                guest::charge(ctx, 4);
                rt::lhu(ctx, V0, S4, 0x6A);
                rt::sltu(ctx, V0, S3, V0);
                if (R(ctx, V0) == 0) break;
                guest::backedge(ctx);
                guest::charge(ctx, 11);
                candidate_slot(ctx, S4, S3);
                rt::lw(ctx, S0, V0, 0x38);
                rt::lw(ctx, V0, S0, 0x30);
                rt::lw(ctx, A0, V0, 0xA2C);
                call(ctx, 0x2CF274, &rg::fn_datCalcGetLevel_002ffcc0);
                rt::andi(ctx, V1, V0, 0xFF);
                rt::sltu(ctx, V0, V1, S2);
                if (R(ctx, V0) == 0) {
                    guest::charge(ctx, 2);
                    if (R(ctx, V1) == R(ctx, S2)) {
                        guest::charge(ctx, 8);
                        rt::andi(ctx, V0, S1, 0xFFFFu);
                        rt::sll(ctx, V0, V0, 2);
                        rt::addu(ctx, V0, V0, SP);
                        rt::sw(ctx, S0, V0, 0x60);
                        rt::addiu(ctx, V0, S1, 1);
                        rt::andi(ctx, S1, V0, 0xFFFFu);
                    } else {
                        guest::charge(ctx, 3);
                        move(ctx, S2, V1);
                        rt::sw(ctx, S0, SP, 0x60);
                        li(ctx, S1, 1);
                    }
                }
                guest::charge(ctx, 1);
                rt::addiu(ctx, S3, S3, 1);
            }
            guest::charge(ctx, 6);
            rt::andi(ctx, A0, S1, 0xFFFFu);
            call(ctx, 0x2CF2D8, &rg::fn_datCalcRand_002ffbc0);
            rt::sll(ctx, V0, V0, 2);
            rt::addu(ctx, V0, V0, SP);
            rt::lw(ctx, V0, V0, 0x60);
        } else {
            guest::charge(ctx, 3);
            rt::lw(ctx, V0, S4, 0x38);
        }
        guest::charge(ctx, 7);
        unit_id_arg(ctx, V0);
        set_result(ctx, 0x2CF2F8);
    }
    guest::charge(ctx, 10);
    return 0xFFFFFFFFu;
}

u32 sub_2CF340(EEContext& ctx) {
    // [485, 1] frame 64 (s2 = the user, s0 = n, s1 = i): 23: the candidates (0, 0x2C, sub_2C30F0); none -> 3: return 0;
    // else 4 and the walk (test 5, back-edge check): body 13: no bad status (as sub_2CF070) -> 2: ++n; 2: ++i. 5:
    // return n. 8; returns -1.
    guest::enter(ctx, 23);
    Frame frame(ctx, 64, 3);
    user_data(ctx, 0x2CF354);
    move(ctx, S2, V0);
    int_para(ctx, 0x2CF364, 0);
    if (!filter_targets(ctx, S2, 0, 0x2C, 0, 0x2C30F0, 0x2CF388)) {
        guest::charge(ctx, 3);
        move(ctx, A0, ZR);
        set_result(ctx, 0x2CF41C);
    } else {
        guest::charge(ctx, 4);
        move(ctx, S0, ZR);
        move(ctx, S1, ZR);
        for (;;) {
            guest::charge(ctx, 5);
            rt::andi(ctx, V1, S1, 0xFFFFu);
            rt::lhu(ctx, V0, S2, 0x6A);
            rt::slt(ctx, V0, V1, V0);
            if (R(ctx, V0) == 0) break;
            guest::backedge(ctx);
            guest::charge(ctx, 13);
            rt::andi(ctx, V0, S1, 0xFFFFu);
            rt::sll(ctx, V0, V0, 2);
            rt::addu(ctx, V0, S2, V0);
            rt::lw(ctx, V0, V0, 0x38);
            rt::lw(ctx, V0, V0, 0x30);
            rt::lw(ctx, A0, V0, 0xA2C);
            call(ctx, 0x2CF3C4, &rg::fn_datCalcGetBadStatusNoDown_00300530);
            bad_status_but_bit20(ctx);
            if (R(ctx, V0) == 0) {
                guest::charge(ctx, 2);
                rt::addiu(ctx, V0, S0, 1);
                rt::andi(ctx, S0, V0, 0xFFFFu);
            }
            guest::charge(ctx, 2);
            rt::addiu(ctx, V0, S1, 1);
            rt::andi(ctx, S1, V0, 0xFFFFu);
        }
        guest::charge(ctx, 5);
        rt::andi(ctx, A0, S0, 0xFFFFu);
        set_result(ctx, 0x2CF408);
    }
    guest::charge(ctx, 8);
    return 0xFFFFFFFFu;
}

u32 sub_2D0270(EEContext& ctx) {
    // [271, 0] frame 128 (s6 = the user, s4 = the walked action, s5 = its unit then its HP, s2/s0 = the best accepted
    // and its HP, s3/s1 = the best of all and its HP): 21: walk gBtl's action list from +0x14C (test 2, back-edge
    // check; +0x4A8 = next, 1): active (u16 +0x1A bits 1 and 8: 4 / 3), an enemy (5), not dead (6), HP (7) below the
    // accepted best and sub_2C5030(user, it, 0, 0) >= 0 (8) -> 2: take it; HP below the overall best (3) -> 2: take
    // it. 2: an accepted one -> 7: its id; else 5: the overall best's id; 12.
    guest::enter(ctx, 21);
    Frame frame(ctx, 128, 7);
    user_data(ctx, 0x2D0294);
    move(ctx, S6, V0);
    move(ctx, S3, ZR);
    li_hi_lo(ctx, S1, 0x0FFFFFFFu);
    move(ctx, S2, ZR);
    move(ctx, S0, S1);
    rt::lw(ctx, V0, GP, -0x4904);
    rt::lw(ctx, S4, V0, 0x14C);
    for (;;) {
        guest::charge(ctx, 2);
        if (R(ctx, S4) == 0) break;
        guest::backedge(ctx);
        guest::charge(ctx, 4);
        rt::lhu(ctx, V1, S4, 0x1A);
        rt::andi(ctx, V0, V1, 1);
        if (R(ctx, V0) != 0) {
            guest::charge(ctx, 3);
            rt::andi(ctx, V0, V1, 8);
            if (R(ctx, V0) != 0) {
                guest::charge(ctx, 5);
                rt::lw(ctx, S5, S4, 0x30);
                rt::lbu(ctx, V1, S5, 0xA2);
                li(ctx, V0, 1);
                if (R(ctx, V1) == R(ctx, V0)) {
                    guest::charge(ctx, 6);
                    rt::lw(ctx, A0, S5, 0xA2C);
                    move(ctx, A1, ZR);
                    call(ctx, 0x2D02FC, &rg::fn_datCalcIsDead_0030b5a0);
                    if (R(ctx, V0) == 0) {
                        guest::charge(ctx, 7);
                        rt::lw(ctx, A0, S5, 0xA2C);
                        call(ctx, 0x2D0310, &rg::fn_datCalcGetHp_002ffd70);
                        rt::andi(ctx, S5, V0, 0xFFFFu);
                        rt::sltu(ctx, AT, S5, S0);
                        if (R(ctx, AT) != 0) {
                            guest::charge(ctx, 8);
                            move(ctx, A0, S6);
                            move(ctx, A1, S4);
                            move(ctx, A2, ZR);
                            move(ctx, A3, ZR);
                            call(ctx, 0x2D0338, &rg::fn_sub_2C5030_002c5030);
                            if (Rs(ctx, V0) >= 0) {
                                guest::charge(ctx, 2);
                                move(ctx, S2, S4);
                                move(ctx, S0, S5);
                            }
                        }
                        guest::charge(ctx, 3);
                        rt::sltu(ctx, AT, S5, S1);
                        if (R(ctx, AT) != 0) {
                            guest::charge(ctx, 2);
                            move(ctx, S3, S4);
                            move(ctx, S1, S5);
                        }
                    }
                }
            }
        }
        guest::charge(ctx, 1);
        rt::lw(ctx, S4, S4, 0x4A8);
    }
    guest::charge(ctx, 2);
    if (R(ctx, S2) == 0) {
        guest::charge(ctx, 5);
        unit_id_arg(ctx, S3);
        set_result(ctx, 0x2D03A0);
    } else {
        guest::charge(ctx, 7);
        unit_id_arg(ctx, S2);
        set_result(ctx, 0x2D0384);
    }
    guest::charge(ctx, 12);
    return 1;
}

namespace {
// The unit counter's arguments as sub_2CDB70 .. sub_2CEC30 set them: a0 = the user (s0), a1 = the param ($v0), a2 =
// 0x80000, a3 = `sides` (`li`), t0 = `want` (`move t0, zero` / `move t0, a3` / `li t0, 1`), t1 = `pred`, t2 = `list`
// (`move t2, zero` or `addiu t2, sp, off`); then `jal sub_2C0F40` at `pc`.
enum class Want { Zero, FromA3, One };
void count_units(EEContext& ctx, s32 sides, Want want, u32 pred, s32 list_off, u32 pc) {
    move(ctx, A0, S0);
    move(ctx, A1, V0);
    rt::lui(ctx, A2, 8);
    li(ctx, A3, sides);
    switch (want) {
        case Want::Zero: move(ctx, T0, ZR); break;
        case Want::FromA3: move(ctx, T0, A3); break;
        case Want::One: li(ctx, T0, 1); break;
    }
    la(ctx, T1, pred);
    if (list_off != 0)
        rt::addiu(ctx, T2, SP, list_off);
    else
        move(ctx, T2, ZR);
    call(ctx, pc, &rg::fn_sub_2C0F40_002c0f40);
}

// sub_2CDB70 .. sub_2CDDA0 (frame 32, s0 = the user): one block of 28: return (u16)sub_2C0F40(user, arg0, ...).
u32 unit_count(EEContext& ctx, u32 base, s32 sides, Want want, u32 pred) {
    guest::enter(ctx, 28);
    Frame frame(ctx, 32, 1);
    user_data(ctx, base + 0xC);
    move(ctx, S0, V0);
    int_para(ctx, base + 0x1C, 0);
    count_units(ctx, sides, want, pred, 0, base + 0x44);
    rt::andi(ctx, A0, V0, 0xFFFFu);
    set_result(ctx, base + 0x50);
    return 1;
}
}  // namespace

u32 sub_2CDB70(EEContext& ctx) { return unit_count(ctx, 0x2CDB70, 1, Want::Zero, 0x2C3400); }    // [405]
u32 sub_2CDBE0(EEContext& ctx) { return unit_count(ctx, 0x2CDBE0, 1, Want::FromA3, 0x2C3400); }  // [406]
u32 sub_2CDC50(EEContext& ctx) { return unit_count(ctx, 0x2CDC50, 1, Want::Zero, 0x2C1710); }    // [407]
u32 sub_2CDCC0(EEContext& ctx) { return unit_count(ctx, 0x2CDCC0, 2, Want::Zero, 0x2C3400); }    // [408]
u32 sub_2CDD30(EEContext& ctx) { return unit_count(ctx, 0x2CDD30, 2, Want::One, 0x2C3400); }     // [409]
u32 sub_2CDDA0(EEContext& ctx) { return unit_count(ctx, 0x2CDDA0, 1, Want::Zero, 0x2C12F0); }    // [456]

u32 sub_2CEB20(EEContext& ctx) {
    // [410, 1] frame 80 (s0 = the user; the list at sp + 0x20): 22: n = sub_2C0F40(user, arg0, 0x80000, 1, 1,
    // sub_2C3400, list) & 0xFFFF; n <= 0 -> no target; else 4 (a3 = i, a1 = gBtl) and the walk (test 4, back-edge
    // check): body 7: list[i] == gBtl->+0x148 -> stop; 2: ++i. 2: found -> 1: that action; else 8: a random one; 7: its
    // id; 6.
    guest::enter(ctx, 22);
    Frame frame(ctx, 80, 1);
    user_data(ctx, 0x2CEB2C);
    move(ctx, S0, V0);
    int_para(ctx, 0x2CEB3C, 0);
    count_units(ctx, 1, Want::FromA3, 0x2C3400, 0x20, 0x2CEB64);
    rt::andi(ctx, A2, V0, 0xFFFFu);
    if (Rs(ctx, A2) <= 0) {
        no_target(ctx, 0x2CEC08);
    } else {
        guest::charge(ctx, 4);
        move(ctx, A3, ZR);
        rt::lw(ctx, A1, GP, -0x4904);
        for (;;) {
            guest::charge(ctx, 4);
            rt::andi(ctx, V1, A3, 0xFFFFu);
            rt::slt(ctx, V0, V1, A2);
            if (R(ctx, V0) == 0) break;
            guest::backedge(ctx);
            guest::charge(ctx, 7);
            rt::lw(ctx, A0, A1, 0x148);
            rt::andi(ctx, V0, A3, 0xFFFFu);
            rt::sll(ctx, V0, V0, 2);
            rt::addu(ctx, V0, V0, SP);
            rt::lw(ctx, V0, V0, 0x20);
            if (R(ctx, A0) == R(ctx, V0)) break;
            guest::charge(ctx, 2);
            rt::addiu(ctx, V0, A3, 1);
            rt::andi(ctx, A3, V0, 0xFFFFu);
        }
        guest::charge(ctx, 2);
        if (R(ctx, V1) != R(ctx, A2)) {
            guest::charge(ctx, 1);
            rt::lw(ctx, V0, A1, 0x148);
        } else {
            guest::charge(ctx, 8);
            rt::andi(ctx, A0, A2, 0xFFFFu);
            call(ctx, 0x2CEBC8, &rg::fn_datCalcRand_002ffbc0);
            rt::sll(ctx, V0, V0, 2);
            rt::addu(ctx, V0, V0, SP);
            rt::lw(ctx, V0, V0, 0x20);
        }
        guest::charge(ctx, 7);
        unit_id_arg(ctx, V0);
        set_result(ctx, 0x2CEBF4);
    }
    guest::charge(ctx, 6);
    return 1;
}

u32 sub_2CEC30(EEContext& ctx) {
    // [411, 1] frame 128 (s0 = the user, then the list slot; s1 = n, s2 = i, s3 = the chosen; the list at sp + 0x50):
    // 25: n = sub_2C0F40(user, arg0, 0x80000, 2, 1, sub_2C3400, list) & 0xFFFF; n <= 0 -> no target; else 4 and the
    // walk (test 4, back-edge check): body 12: level > 0 -> 1: chosen = it; 2: ++i. 2: none chosen -> 6: a random one;
    // 7: its id; 9.
    guest::enter(ctx, 25);
    Frame frame(ctx, 128, 4);
    user_data(ctx, 0x2CEC48);
    move(ctx, S0, V0);
    int_para(ctx, 0x2CEC58, 0);
    count_units(ctx, 2, Want::One, 0x2C3400, 0x50, 0x2CEC80);
    rt::andi(ctx, S1, V0, 0xFFFFu);
    if (Rs(ctx, S1) <= 0) {
        no_target(ctx, 0x2CED30);
    } else {
        guest::charge(ctx, 4);
        move(ctx, S3, ZR);
        move(ctx, S2, ZR);
        for (;;) {
            guest::charge(ctx, 4);
            rt::andi(ctx, V0, S2, 0xFFFFu);
            rt::slt(ctx, V0, V0, S1);
            if (R(ctx, V0) == 0) break;
            guest::backedge(ctx);
            guest::charge(ctx, 12);
            rt::andi(ctx, V0, S2, 0xFFFFu);
            rt::sll(ctx, V0, V0, 2);
            rt::addu(ctx, V0, V0, SP);
            rt::addiu(ctx, S0, V0, 0x50);
            rt::lw(ctx, V0, S0, 0);
            rt::lw(ctx, V0, V0, 0x30);
            rt::lw(ctx, A0, V0, 0xA2C);
            call(ctx, 0x2CECC0, &rg::fn_datCalcGetLevel_002ffcc0);
            rt::andi(ctx, V0, V0, 0xFF);
            if (Rs(ctx, V0) > 0) {
                guest::charge(ctx, 1);
                rt::lw(ctx, S3, S0, 0);
            }
            guest::charge(ctx, 2);
            rt::addiu(ctx, V0, S2, 1);
            rt::andi(ctx, S2, V0, 0xFFFFu);
        }
        guest::charge(ctx, 2);
        if (R(ctx, S3) == 0) {
            guest::charge(ctx, 6);
            rt::andi(ctx, A0, S1, 0xFFFFu);
            call(ctx, 0x2CECFC, &rg::fn_datCalcRand_002ffbc0);
            rt::sll(ctx, V0, V0, 2);
            rt::addu(ctx, V0, V0, SP);
            rt::lw(ctx, S3, V0, 0x50);
        }
        guest::charge(ctx, 7);
        unit_id_arg(ctx, S3);
        set_result(ctx, 0x2CED1C);
    }
    guest::charge(ctx, 9);
    return 1;
}

u32 sub_2CED60(EEContext& ctx) {
    // [412, 0] frame 208 (s1 = the other side, s3 = i, s0 = the unit, s4 = the best level, s2 = n; the units at sp +
    // 0x90 with their count at sp + 0xC8, the best ones at sp + 0x60): 14; the user's side byte != 0 -> 1 (side 0)
    // else 3 (side 1); 13: sub_2BFCB0(user, units, 2, 0, 0); the walk (test 5, back-edge check): body 8: active (bit 1;
    // 3: bit 8), on that side (4), not dead (6), level (7) == best -> 8: best[n++] = it; else 3: level > best -> 3: best
    // = level, best[] = { it }; 2: ++i. 3: n <= 0 -> 3: -1; else 12: a random best one's id; 10.
    guest::enter(ctx, 14);
    Frame frame(ctx, 208, 5);
    user_data(ctx, 0x2CED7C);
    move(ctx, A0, V0);
    rt::lw(ctx, V0, V0, 0x30);
    rt::lbu(ctx, V0, V0, 0xA2);
    if (R(ctx, V0) != 0) {
        guest::charge(ctx, 1);
        move(ctx, V0, ZR);
    } else {
        guest::charge(ctx, 3);
        li(ctx, V0, 1);
    }
    guest::charge(ctx, 13);
    rt::andi(ctx, S0, V0, 0xFFFFu);
    rt::addiu(ctx, A1, SP, 0x90);
    li(ctx, A2, 2);
    move(ctx, A3, ZR);
    move(ctx, T0, ZR);
    call(ctx, 0x2CEDBC, &rg::fn_sub_2BFCB0_002bfcb0);
    move(ctx, S4, ZR);
    move(ctx, S2, ZR);
    move(ctx, S3, ZR);
    rt::andi(ctx, S1, S0, 0xFFFFu);
    for (;;) {
        guest::charge(ctx, 5);
        rt::andi(ctx, V1, S3, 0xFFFFu);
        rt::lhu(ctx, V0, SP, 0xC8);
        rt::slt(ctx, V0, V1, V0);
        if (R(ctx, V0) == 0) break;
        guest::backedge(ctx);
        guest::charge(ctx, 8);
        rt::andi(ctx, V0, S3, 0xFFFFu);
        rt::sll(ctx, V0, V0, 2);
        rt::addu(ctx, V0, V0, SP);
        rt::lw(ctx, S0, V0, 0x90);
        rt::lhu(ctx, V1, S0, 0x1A);
        rt::andi(ctx, V0, V1, 1);
        if (R(ctx, V0) != 0) {
            guest::charge(ctx, 3);
            rt::andi(ctx, V0, V1, 8);
            if (R(ctx, V0) != 0) {
                guest::charge(ctx, 4);
                rt::lw(ctx, V1, S0, 0x30);
                rt::lbu(ctx, V0, V1, 0xA2);
                if (R(ctx, V0) == R(ctx, S1)) {
                    guest::charge(ctx, 6);
                    rt::lw(ctx, A0, V1, 0xA2C);
                    move(ctx, A1, ZR);
                    call(ctx, 0x2CEE20, &rg::fn_datCalcIsDead_0030b5a0);
                    if (R(ctx, V0) == 0) {
                        guest::charge(ctx, 7);
                        rt::lw(ctx, V0, S0, 0x30);
                        rt::lw(ctx, A0, V0, 0xA2C);
                        call(ctx, 0x2CEE38, &rg::fn_datCalcGetLevel_002ffcc0);
                        rt::andi(ctx, V0, V0, 0xFF);
                        if (R(ctx, V0) == R(ctx, S4)) {
                            guest::charge(ctx, 8);
                            rt::andi(ctx, V0, S2, 0xFFFFu);
                            rt::sll(ctx, V0, V0, 2);
                            rt::addu(ctx, V0, V0, SP);
                            rt::sw(ctx, S0, V0, 0x60);
                            rt::addiu(ctx, V0, S2, 1);
                            rt::andi(ctx, S2, V0, 0xFFFFu);
                        } else {
                            guest::charge(ctx, 3);
                            rt::sltu(ctx, AT, S4, V0);
                            if (R(ctx, AT) != 0) {
                                guest::charge(ctx, 3);
                                move(ctx, S4, V0);
                                rt::sw(ctx, S0, SP, 0x60);
                                li(ctx, S2, 1);
                            }
                        }
                    }
                }
            }
        }
        guest::charge(ctx, 2);
        rt::addiu(ctx, V0, S3, 1);
        rt::andi(ctx, S3, V0, 0xFFFFu);
    }
    guest::charge(ctx, 3);
    rt::andi(ctx, A0, S2, 0xFFFFu);
    if (Rs(ctx, A0) <= 0) {
        no_target(ctx, 0x2CEEE0);
    } else {
        guest::charge(ctx, 12);
        call(ctx, 0x2CEEAC, &rg::fn_datCalcRand_002ffbc0);
        rt::sll(ctx, V0, V0, 2);
        rt::addu(ctx, V0, V0, SP);
        rt::lw(ctx, V0, V0, 0x60);
        unit_id_arg(ctx, V0);
        set_result(ctx, 0x2CEECC);
    }
    guest::charge(ctx, 10);
    return 1;
}

u32 sub_2CFFC0(EEContext& ctx) {
    // [269, 1] frame 112 (s0 = the user, then the element; s4 = the action with id arg0; s3 = the user's unit; s2 = the
    // skill count; s1 = the skill list; s5 = i): 35: the element of skill 0 (the attack) and that action's affinity to
    // it; bit 0x8000000 (weak) -> 7: return the element. Else 11: the skill list, and the walk (test 3, back-edge
    // check): body 5: skill 0 -> 1; 3: skill >= 0x1D0 -> 1; 14: its element is a weakness -> 7: return it; 1: ++i. 4:
    // return -1. 10.
    guest::enter(ctx, 35);
    Frame frame(ctx, 112, 6);
    user_data(ctx, 0x2CFFE0);
    move(ctx, S0, V0);
    int_para(ctx, 0x2CFFF0, 0);
    low28(ctx, A0, V0);
    call(ctx, 0x2D0000, &rg::fn_sub_29A210_0029a210);
    move(ctx, S4, V0);
    rt::lw(ctx, S3, S0, 0x30);
    rt::lw(ctx, A0, S3, 0xA2C);
    move(ctx, A1, ZR);
    // The element of the skill in $a1 and the affinity of the found action's unit to it, `& 0x8000000` in $v0.
    auto weakness = [&](u32 pc_element, u32 pc_affinity) {
        call(ctx, pc_element, &rg::fn_datCalcGetSkillElement_003082f0);
        sext16(ctx, S0, V0);
        rt::lw(ctx, V0, S4, 0x30);
        rt::lw(ctx, A0, V0, 0xA2C);
        move(ctx, A1, S0);
        call(ctx, pc_affinity, &rg::fn_datCalcGetAffinityChecked_0030b4b0);
        rt::lui(ctx, V1, 0x800);
        rt::and_(ctx, V0, V0, V1);
    };
    weakness(0x2D0018, 0x2D0034);
    if (R(ctx, V0) != 0) {
        guest::charge(ctx, 7);
        sext16(ctx, A0, S0);
        set_result(ctx, 0x2D0054);
    } else {
        guest::charge(ctx, 11);
        rt::lw(ctx, A0, S3, 0xA2C);
        call(ctx, 0x2D006C, &rg::fn_datCalcGetSkillSlotCount_00308ba0);
        rt::andi(ctx, S2, V0, 0xFFFFu);
        rt::lw(ctx, A0, S3, 0xA2C);
        call(ctx, 0x2D007C, &rg::fn_datCalcGetSkillList_00308bb0);
        move(ctx, S1, V0);
        move(ctx, S5, ZR);
        bool found = false;
        for (;;) {
            guest::charge(ctx, 3);
            rt::sltu(ctx, V0, S5, S2);
            if (R(ctx, V0) == 0) break;
            guest::backedge(ctx);
            guest::charge(ctx, 5);
            rt::sll(ctx, V0, S5, 1);
            rt::addu(ctx, V0, S1, V0);
            rt::lhu(ctx, A1, V0, 0);
            if (R(ctx, A1) != 0) {
                guest::charge(ctx, 3);
                rt::slti(ctx, AT, A1, 0x1D0);
                if (R(ctx, AT) != 0) {
                    guest::charge(ctx, 14);
                    rt::lw(ctx, A0, S3, 0xA2C);
                    weakness(0x2D00B8, 0x2D00D4);
                    if (R(ctx, V0) != 0) {
                        guest::charge(ctx, 7);
                        sext16(ctx, A0, S0);
                        set_result(ctx, 0x2D00F4);
                        found = true;
                        break;
                    }
                }
            }
            guest::charge(ctx, 1);
            rt::addiu(ctx, S5, S5, 1);
        }
        if (!found) {
            guest::charge(ctx, 4);
            li(ctx, A0, -1);
            set_result(ctx, 0x2D011C);
        }
    }
    guest::charge(ctx, 10);
    return 1;
}

u32 sub_2D09D0(EEContext& ctx) {
    // [479, 0] frame 32 (s0 = the user): 12: battle stage 0x1B0 -> 3: sub_2F5030(user); 8: command 5 (u16 +0x6C).
    guest::enter(ctx, 12);
    Frame frame(ctx, 32, 1);
    user_data(ctx, 0x2D09DC);
    move(ctx, S0, V0);
    rt::lw(ctx, V0, GP, -0x4904);
    rt::lw(ctx, V0, V0, 0xBBC);
    rt::lhu(ctx, V1, V0, 8);
    li(ctx, V0, 0x1B0);
    if (R(ctx, V1) == R(ctx, V0)) {
        guest::charge(ctx, 3);
        move(ctx, A0, S0);
        call(ctx, 0x2D0A04, &rg::fn_sub_2F5030_002f5030);
    }
    guest::charge(ctx, 8);
    li(ctx, V0, 5);
    rt::sh(ctx, V0, S0, 0x6C);
    return 1;
}

// === field / g_data ==================================================================================================

u32 sub_1C3EB0(EEContext& ctx) {
    // [287, 1] frame 32 (s0 = arg0): 9; arg0 == 0 -> 4: sub_434E60() else 2: sub_434D30(); 9: return arg0.
    guest::enter(ctx, 9);
    Frame frame(ctx, 32, 1);
    int_para(ctx, 0x1C3EC0, 0);
    move(ctx, S0, V0);
    if (R(ctx, S0) != 0) {
        guest::charge(ctx, 2);
        call(ctx, 0x1C3EE4, &rg::fn_sub_434D30_00434d30);
    } else {
        guest::charge(ctx, 4);
        call(ctx, 0x1C3ED4, &rg::fn_sub_434E60_00434e60);
    }
    guest::charge(ctx, 9);
    move(ctx, A0, S0);
    set_result(ctx, 0x1C3EF0);
    return 1;
}

u32 sub_1C3F10(EEContext& ctx) {
    // [288, 1] frame 32 (s0 = arg0): one block of 20: sub_435370((s8)arg0); return arg0.
    guest::enter(ctx, 20);
    Frame frame(ctx, 32, 1);
    int_para(ctx, 0x1C3F20, 0);
    move(ctx, S0, V0);
    sext8(ctx, A0, S0);
    call(ctx, 0x1C3F34, &rg::fn_sub_435370_00435370);
    move(ctx, A0, S0);
    set_result(ctx, 0x1C3F40);
    return 1;
}

u32 sub_1C3DF0(EEContext& ctx) {
    // [291, 1] frame 32 (s0 = 1 on the arg0 == 0 path): 8; arg0 != 0 -> 5: the field object (sField +0x18) exists -> 6:
    // sub_429E80(it, 1); 3: sField +0x14 = 0. arg0 == 0 -> 5: the object exists -> 6: sub_429E80(it, 0); 6: +0x14 = 1.
    // 6.
    guest::enter(ctx, 8);
    Frame frame(ctx, 32, 1);
    int_para(ctx, 0x1C3E00, 0);
    const bool on = R(ctx, V0) != 0;
    guest::charge(ctx, 5);
    call(ctx, on ? 0x1C3E54 : 0x1C3E10, &rg::fn_K_Field_Get_001b9120);
    rt::lw(ctx, V0, V0, 0x18);
    if (R(ctx, V0) != 0) {
        guest::charge(ctx, 6);
        call(ctx, on ? 0x1C3E68 : 0x1C3E24, &rg::fn_K_Field_Get_001b9120);
        rt::lw(ctx, A0, V0, 0x18);
        li(ctx, A1, on ? 1 : 0);
        call(ctx, on ? 0x1C3E78 : 0x1C3E34, &rg::fn_sub_429E80_00429e80);
    }
    if (on) {
        guest::charge(ctx, 3);
        call(ctx, 0x1C3E80, &rg::fn_K_Field_Get_001b9120);
        rt::sw(ctx, ZR, V0, 0x14);
    } else {
        guest::charge(ctx, 6);
        li(ctx, S0, 1);
        call(ctx, 0x1C3E40, &rg::fn_K_Field_Get_001b9120);
        rt::sw(ctx, S0, V0, 0x14);
    }
    guest::charge(ctx, 6);
    return 1;
}

u32 sub_1C3D60(EEContext& ctx) {
    // [315, 2] frame 32 (s0 = arg0): one block of 21: return sub_3C8EC0(arg0, arg1) == 0 (`xor v0, v0, zero; sltiu v0,
    // v0, 1`): the script waits while the record exists.
    guest::enter(ctx, 21);
    Frame frame(ctx, 32, 1);
    int_para(ctx, 0x1C3D70, 0);
    move(ctx, S0, V0);
    int_para(ctx, 0x1C3D80, 1);
    move(ctx, A0, S0);
    move(ctx, A1, V0);
    call(ctx, 0x1C3D90, &rg::fn_sub_3C8EC0_003c8ec0);
    rt::xor_(ctx, V0, V0, ZR);
    rt::sltiu(ctx, V0, V0, 1);
    return static_cast<u32>(R(ctx, V0));
}

u32 sub_1C5600(EEContext& ctx) {
    // [371, 1] frame 16: 12: sub_43A230((s8)(arg0 + 1)); zero -> 5: return 0; else 3: return 1. 5.
    guest::enter(ctx, 12);
    Frame frame(ctx, 16, 0);
    int_para(ctx, 0x1C560C, 0);
    rt::addiu(ctx, V0, V0, 1);
    sext8(ctx, A0, V0);
    call(ctx, 0x1C5620, &rg::fn_sub_43A230_0043a230);
    if (R(ctx, V0) != 0) {
        guest::charge(ctx, 3);
        li(ctx, A0, 1);
        set_result(ctx, 0x1C5648);
    } else {
        guest::charge(ctx, 5);
        move(ctx, A0, ZR);
        set_result(ctx, 0x1C5634);
    }
    guest::charge(ctx, 5);
    return 1;
}

u32 sub_1C57B0(EEContext& ctx) {
    // [395, 2] frame 80 (s1 = the answer, s0 = the skill ids, s2 = i, s3 = the id): 17: the 8 skill ids of pc arg0's
    // persona (sub_173380); the walk (test 3: i < 8, back-edge check): body 5: id 0 -> 1; 5: id == arg1 (64-bit compare
    // with scrGetIntPara(1), read again for each non-zero id) -> 3: answer 1, stop; 1: ++i. 12: return the answer.
    guest::enter(ctx, 17);
    Frame frame(ctx, 80, 4);
    move(ctx, S1, ZR);
    int_para(ctx, 0x1C57D0, 0);
    rt::andi(ctx, A0, V0, 0xFFFFu);
    call(ctx, 0x1C57DC, &rg::fn_sub_173380_00173380);
    move(ctx, S0, V0);
    move(ctx, S2, ZR);
    for (;;) {
        guest::charge(ctx, 3);
        rt::slti(ctx, V0, S2, 8);
        if (R(ctx, V0) == 0) break;
        guest::backedge(ctx);
        guest::charge(ctx, 5);
        rt::sll(ctx, V0, S2, 1);
        rt::addu(ctx, V0, S0, V0);
        rt::lhu(ctx, S3, V0, 0);
        if (R(ctx, S3) != 0) {
            guest::charge(ctx, 5);
            int_para(ctx, 0x1C580C, 1);
            if (R(ctx, S3) == R(ctx, V0)) {
                guest::charge(ctx, 3);
                li(ctx, S1, 1);
                break;
            }
        }
        guest::charge(ctx, 1);
        rt::addiu(ctx, S2, S2, 1);
    }
    guest::charge(ctx, 12);
    move(ctx, A0, S1);
    set_result(ctx, 0x1C583C);
    return 1;
}

u32 sub_360250(EEContext& ctx) {
    // [333, 0] frame 16: one block of 12: sub_1717B0(); sub_173040(*($gp - 0x471C)).
    guest::enter(ctx, 12);
    Frame frame(ctx, 16, 0);
    call(ctx, 0x360258, &rg::fn_sub_1717B0_001717b0);
    rt::lw(ctx, A0, GP, -0x471C);
    call(ctx, 0x360264, &rg::fn_sub_173040_00173040);
    return 1;
}

u32 sub_1C5EB0(EEContext& ctx) {
    // [498, 0] frame 16: one block of 9: sub_27D8D0().
    guest::enter(ctx, 9);
    Frame frame(ctx, 16, 0);
    call(ctx, 0x1C5EB8, &rg::fn_sub_27D8D0_0027d8d0);
    return 1;
}

// === message windows =================================================================================================

u32 sub_3A28A0(EEContext& ctx) {
    // [6, 1] frame 32 (s0 = the message handle): 8: scrGetMessageID(); < 0 -> 3 (nothing); else 8:
    // itfMesMngSetChoiceMask(handle, arg0). 5.
    guest::enter(ctx, 8);
    Frame frame(ctx, 32, 1);
    call(ctx, 0x3A28AC, &rg::fn_scrGetMessageID_0035f140);
    move(ctx, S0, V0);
    if (Rs(ctx, S0) < 0) {
        guest::charge(ctx, 3);
    } else {
        guest::charge(ctx, 8);
        int_para(ctx, 0x3A28D0, 0);
        move(ctx, A0, S0);
        move(ctx, A1, V0);
        call(ctx, 0x3A28E0, &rg::fn_itfMesMngSetChoiceMask_003a3ba0);
    }
    guest::charge(ctx, 5);
    return 1;
}

u32 sub_3A2C10(EEContext& ctx) {
    // [40, 2] frame 48 (s1 = the message handle, s0 = arg0): 9: scrGetMessageID(); < 0 -> 3 (nothing); else 13:
    // sub_3A4A70(handle, arg0, arg1). 6.
    guest::enter(ctx, 9);
    Frame frame(ctx, 48, 2);
    call(ctx, 0x3A2C20, &rg::fn_scrGetMessageID_0035f140);
    move(ctx, S1, V0);
    if (Rs(ctx, S1) < 0) {
        guest::charge(ctx, 3);
    } else {
        guest::charge(ctx, 13);
        int_para(ctx, 0x3A2C44, 0);
        move(ctx, S0, V0);
        int_para(ctx, 0x3A2C54, 1);
        move(ctx, A0, S1);
        move(ctx, A1, S0);
        move(ctx, A2, V0);
        call(ctx, 0x3A2C68, &rg::fn_sub_3A4A70_003a4a70);
    }
    guest::charge(ctx, 6);
    return 1;
}

}  // namespace p3fes::game

// --- the recompiled program's entry points (signatures from recomp/generated/functions.h) ---------------------------
namespace p3fes::recomp_gen {

using namespace p3fes::game;

#define P3FES_COMM_C_SHIM(name, addr8, index, argc) \
    void fn_##name##_##addr8(p3fes::EEContext& ctx) { guest::ret32(ctx, name(ctx)); }
P3FES_COMM_C_HANDLERS(P3FES_COMM_C_SHIM)
#undef P3FES_COMM_C_SHIM

}  // namespace p3fes::recomp_gen
