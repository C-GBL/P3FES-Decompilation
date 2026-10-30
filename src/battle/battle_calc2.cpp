// The battle data / calculation band, second pass (game/include/p3fes/game/battle_calc2.h), hand-decompiled from
// SLUS_216.21 (docs/ANALYSIS/21_battle.md sections 1-3). tests/game/test_battle_calc2.cpp runs each function against
// its __recomp body.
//
// Fidelity. Every function mirrors the recompiled body down to the register file:
// * virtual time (ADR-0013): guest::enter / charge / backedge follow the `ctx.cycles += N` blocks and the check points
//   of the generated body. A block is charged at its start, before the calls it contains. The loops here are
//   test-first (the compiled code jumps to the test): the first test runs without a check, every later test is
//   followed by the back-edge check when it loops (`for (;;) { charge(test); if (!cond) break; backedge(); ... }`);
// * registers: the register transfers are the rt:: operations of the instructions they stand for (`move` is `daddu
//   rd, rs, zero`, `li` is `addiu rd, zero, imm`, the u16 / s16 idioms are `andi 0xFFFF` / `dsll32 + dsra32 16`), in
//   the original order, so every GPR holds the original 64-bit (128-bit) value at every check point, call and return
//   -- the loop counters, the bounds, $at of `slti`, the table offsets. A check point may preempt the thread and the
//   kernel then stores the whole register file in guest memory, so none of these is "dead";
// * frames: `Frame` performs the original prologue and epilogue (`addiu sp; sd ra; sq sN ... sq s0` ... `ld ra; lq sN
//   ... lq s0; addiu sp`), so the spill slots hold what the original stored and the callees' frames land where they
//   did;
// * calls: every callee (all of them replaced by earlier slices: datCalcChkBadStatus, datCalcGetLevel, datCalcRand,
//   sub_17D800, datCalcGetBadStatus, datCalcIsDead, sub_302380, datCalcClearEffect, datCalcGetEffectState, and the
//   retail `jr $ra` K_Assert sub_19D3F0) is entered through its generated symbol with $ra = the original link
//   (`rt::jal` at the call's address), so whichever body is live runs.
// Guest words addressed through $gp (gBtl, the .TBL section pointers) are read through the $gp register, as the
// original does.
#include "p3fes/game/battle_calc2.h"

#include "p3fes/ee/core.h"
#include "p3fes/game/guest.h"

#include <cstddef>
#include <iterator>

namespace p3fes::recomp_gen {
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);          // K_Assert (`jr $ra` in retail)
void fn_datCalcRand_002ffbc0(p3fes::EEContext&);         // battle_data
void fn_datCalcGetLevel_002ffcc0(p3fes::EEContext&);     // battle_data
void fn_datCalcGetBadStatus_00300550(p3fes::EEContext&); // battle (battle_unit.cpp)
void fn_datCalcChkBadStatus_00300580(p3fes::EEContext&); // battle (battle_unit.cpp)
void fn_datCalcClearEffect_00301540(p3fes::EEContext&);  // battle_data
void fn_datCalcGetEffectState_00301750(p3fes::EEContext&);  // battle (battle_unit.cpp)
void fn_datCalcIsDead_0030b5a0(p3fes::EEContext&);       // battle (battle_unit.cpp)
void fn_sub_302380_00302380(p3fes::EEContext&);          // battle_rest: (unit, bits, on) the effect-flag word +0x14
void fn_sub_17D800_0017d800(p3fes::EEContext&);          // ui: the hero's state test the support checks first
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {

namespace rg = recomp_gen;
using namespace bc2;
using guest::Fn;
using rt::Reg;

// --- registers ------------------------------------------------------------------------------------------------
constexpr Reg ZR = GPR_ZERO, AT = GPR_AT, V0 = GPR_V0, V1 = GPR_V1, A0 = GPR_A0, A1 = GPR_A1, A2 = GPR_A2, A3 = GPR_A3;
constexpr Reg T0 = GPR_T0, T1 = GPR_T0 + 1, T2 = GPR_T0 + 2, T3 = GPR_T0 + 3;
constexpr Reg S0 = GPR_S0, S1 = GPR_S0 + 1, S2 = GPR_S0 + 2, S3 = GPR_S0 + 3, S4 = GPR_S0 + 4, S5 = GPR_S0 + 5;
constexpr Reg GP = GPR_GP, SP = GPR_SP, RA = GPR_RA;

// The instruction idioms of these bodies, as the instructions themselves.
void move(EEContext& ctx, Reg d, Reg s) { rt::daddu(ctx, d, s, ZR); }
void li(EEContext& ctx, Reg d, s32 v) { rt::addiu(ctx, d, ZR, v); }
void u16_of(EEContext& ctx, Reg d, Reg s) { rt::andi(ctx, d, s, 0xFFFFu); }
void s16_of(EEContext& ctx, Reg d, Reg s) {  // dsll32 / dsra32 16
    rt::dsll32(ctx, d, s, 16);
    rt::dsra32(ctx, d, d, 16);
}
void s8_of(EEContext& ctx, Reg d, Reg s) {  // dsll32 / dsra32 24
    rt::dsll32(ctx, d, s, 24);
    rt::dsra32(ctx, d, d, 24);
}
void gbtl(EEContext& ctx, Reg d) { rt::lw(ctx, d, GP, kGpGBtl); }  // lw d, -18692(gp): gBtl
// `lui d, %hi(addr); addiu d, d, %lo(addr)`
void la(EEContext& ctx, Reg d, u32 addr) {
    rt::lui(ctx, d, (addr + 0x8000u) >> 16);
    rt::addiu(ctx, d, d, static_cast<s16>(addr & 0xFFFFu));
}
bool eq(EEContext& ctx, Reg a, Reg b) { return rt::cmp_eq(ctx, a, b); }
bool ne(EEContext& ctx, Reg a, Reg b) { return rt::cmp_ne(ctx, a, b); }
bool nz(EEContext& ctx, Reg a) { return rt::cmp_ne(ctx, a, ZR); }

// `jal fn` at `pc`: $ra = pc + 8, the callee through its generated symbol.
void call(EEContext& ctx, u32 pc, Fn fn) {
    rt::jal(ctx, pc);
    fn(ctx);
}

// The original frame of 16 * (saved + 1) bytes: s0.. at 16 * k, $ra after them.
class Frame {
public:
    Frame(EEContext& ctx, unsigned saved) noexcept : ctx_(ctx), saved_(saved) {
        rt::addiu(ctx_, SP, SP, -static_cast<s32>(16 * (saved_ + 1)));
        rt::sd(ctx_, RA, SP, static_cast<s32>(16 * saved_));
        for (unsigned k = saved_; k-- > 0;) rt::sq(ctx_, S0 + k, SP, static_cast<s32>(16 * k));
    }
    ~Frame() {
        rt::ld(ctx_, RA, SP, static_cast<s32>(16 * saved_));
        for (unsigned k = saved_; k-- > 0;) rt::lq(ctx_, S0 + k, SP, static_cast<s32>(16 * k));
        rt::addiu(ctx_, SP, SP, static_cast<s32>(16 * (saved_ + 1)));
    }
    Frame(const Frame&) = delete;
    Frame& operator=(const Frame&) = delete;

private:
    EEContext& ctx_;
    unsigned saved_;
};

// --- shared shapes ------------------------------------------------------------------------------------------------
// `lw rd, 3004(gbtl); lhu rd2, 8(rd)`: the encounter id of the battle setup block, in `id`; `gb` keeps gBtl.
void encounter_id(EEContext& ctx, Reg gb, Reg tmp, Reg id) {
    gbtl(ctx, gb);
    rt::lw(ctx, tmp, gb, 3004);
    rt::lhu(ctx, id, tmp, 8);
}

// The +160 counter of `*p +48` (`lw v1, 0(p); lw a?, 48(v1); lhu v1, 160(a?); addiu v1, v1, d; sh v1, 160(a?)`).
void bump_counter(EEContext& ctx, Reg p, s32 off, Reg obj, s32 d) {
    rt::lw(ctx, V1, p, off);
    rt::lw(ctx, obj, V1, 48);
    rt::lhu(ctx, V1, obj, 160);
    rt::addiu(ctx, V1, V1, d);
    rt::sh(ctx, V1, obj, 160);
}

// A target action of `a` (btlAction): `andi r, k, 0xFFFF; sll r, r, 2; addu r, a, r; lw dst, 56(r)` (btlTarget a +56).
void target_entry(EEContext& ctx, Reg r, Reg k, Reg a, Reg dst) {
    u16_of(ctx, r, k);
    rt::sll(ctx, r, r, 2);
    rt::addu(ctx, r, a, r);
    rt::lw(ctx, dst, r, 56);
}

// The 28-byte result j of a target action: `andi x, j, 0xFFFF; sll r, x, 3; subu r, r, x; sll r, r, 2; addu dst,
// rec, r` (registers as the caller names them).
void result_entry(EEContext& ctx, Reg x, Reg r, Reg j, Reg rec, Reg dst) {
    u16_of(ctx, x, j);
    rt::sll(ctx, r, x, 3);
    rt::subu(ctx, r, r, x);
    rt::sll(ctx, r, r, 2);
    rt::addu(ctx, dst, rec, r);
}

// `addiu t, k, 1; andi k, t, 0xFFFF` (a u16 loop counter step through `t`).
void step16(EEContext& ctx, Reg k, Reg t) {
    rt::addiu(ctx, t, k, 1);
    u16_of(ctx, k, t);
}

// The u16 loop test `andi t, k, 0xFFFF; slt t, t, bound` (bound a register).
bool below16(EEContext& ctx, Reg t, Reg k, Reg bound) {
    u16_of(ctx, t, k);
    rt::slt(ctx, t, t, bound);
    return nz(ctx, t);
}

}  // namespace

// === btlTarget / btlEfficacy ========================================================================================

void sub_2D15E0(EEContext& ctx) {
    // The selection pair +52/+54 saved to +68/+70.
    guest::enter(ctx, 6);
    rt::lhu(ctx, V1, A0, 52);
    rt::sh(ctx, V1, A0, 68);
    rt::lhu(ctx, V1, A0, 54);
    rt::sh(ctx, V1, A0, 70);
}

void btlTargetGetSideMask(EEContext& ctx) {
    // mask = 0; for (k = 0; k < t->count (u16 +50); k++) mask |= 1 << t->entry[k]->unit(+48)->side(+162); u16.
    guest::enter(ctx, 6);
    move(ctx, V0, ZR);
    move(ctx, A3, ZR);
    rt::lhu(ctx, A2, A0, 50);
    li(ctx, A1, 1);
    for (;;) {
        guest::charge(ctx, 4);
        if (!below16(ctx, V1, A3, A2)) break;
        guest::backedge(ctx);
        guest::charge(ctx, 12);
        u16_of(ctx, V1, A3);
        rt::sll(ctx, V1, V1, 2);
        rt::addu(ctx, V1, A0, V1);
        rt::lw(ctx, V1, V1, 0);
        rt::lw(ctx, V1, V1, 48);
        rt::lbu(ctx, V1, V1, 162);
        rt::sllv(ctx, V1, A1, V1);
        u16_of(ctx, V1, V1);
        rt::or_(ctx, V0, V0, V1);
        u16_of(ctx, V0, V0);
        step16(ctx, A3, V1);
    }
    guest::charge(ctx, 2);
}

void sub_2D3FE0(EEContext& ctx) {
    // a0 = a node with a flag word +156 and the links +2500 (prev) / +2504 (next) of a list whose nodes link at
    // +1224 / +1228 and whose head is gBtl +716: when bit 2 is set, clear it and unlink.
    guest::enter(ctx, 4);
    rt::lw(ctx, A1, A0, 156);
    rt::andi(ctx, V1, A1, 0x4u);
    if (eq(ctx, V1, ZR)) {
        guest::charge(ctx, 2);
        return;
    }
    guest::charge(ctx, 6);
    li(ctx, V1, -5);
    rt::and_(ctx, V1, A1, V1);
    rt::sw(ctx, V1, A0, 156);
    rt::lw(ctx, A1, A0, 2504);
    if (!eq(ctx, A1, ZR)) {
        guest::charge(ctx, 2);
        rt::lw(ctx, V1, A0, 2500);
        rt::sw(ctx, V1, A1, 1224);  // next->prev = prev
    }
    guest::charge(ctx, 3);
    rt::lw(ctx, A1, A0, 2500);
    if (!eq(ctx, A1, ZR)) {
        guest::charge(ctx, 4);
        rt::lw(ctx, V1, A0, 2504);
        rt::sw(ctx, V1, A1, 1228);  // prev->next = next
    } else {
        guest::charge(ctx, 3);
        rt::lw(ctx, A0, A0, 2504);
        gbtl(ctx, V1);
        rt::sw(ctx, A0, V1, 716);  // head = next
    }
    guest::charge(ctx, 2);
}

void sub_2D4800(EEContext& ctx) {
    guest::enter(ctx, 4);
    rt::sh(ctx, ZR, A0, 1024);
    rt::sh(ctx, ZR, A0, 1026);
}

void sub_2D4CC0(EEContext& ctx) {
    // EFFECT.TBL section 0 ($gp - 18672, 464 x 28 bytes by skill id): byte 0 of record (u16) a0, or 1 when it is 0.
    guest::enter(ctx, 9);
    u16_of(ctx, V1, A0);
    rt::sll(ctx, V0, V1, 3);
    rt::subu(ctx, V0, V0, V1);
    rt::sll(ctx, V1, V0, 2);
    rt::lw(ctx, V0, GP, kGpTbl400);
    rt::addu(ctx, V0, V0, V1);
    rt::lbu(ctx, V0, V0, 0);
    if (!nz(ctx, V0)) {
        guest::charge(ctx, 1);
        li(ctx, V0, 1);
    }
    guest::charge(ctx, 2);
}

void btlGetMeanLevel(EEContext& ctx) {
    // (u16 side mask, status): over the btlAction list (gBtl +332, next +1192), the active ones (+26 bit 0) whose unit
    // (+48) is on a side of the mask and (status == 0 or !datCalcChkBadStatus(DatUnit, status)): sum the u8 levels
    // (datCalcGetLevel) and count; returns sum / count (u16, the EE `div`), 1 when no unit or the mean is 0.
    guest::enter(ctx, 16);
    Frame frame(ctx, 6);
    move(ctx, S0, A1);
    move(ctx, S4, ZR);
    move(ctx, S3, ZR);
    gbtl(ctx, V0);
    rt::lw(ctx, S5, V0, 332);
    u16_of(ctx, S2, A0);
    for (;;) {
        guest::charge(ctx, 2);
        if (!nz(ctx, S5)) break;
        guest::backedge(ctx);
        guest::charge(ctx, 4);
        rt::lhu(ctx, V0, S5, 26);
        rt::andi(ctx, V0, V0, 0x1u);
        if (!eq(ctx, V0, ZR)) {
            guest::charge(ctx, 7);
            rt::lw(ctx, S1, S5, 48);
            rt::lbu(ctx, V1, S1, 162);
            li(ctx, V0, 1);
            rt::sllv(ctx, V0, V0, V1);
            rt::and_(ctx, V0, S2, V0);
            if (!eq(ctx, V0, ZR)) {
                guest::charge(ctx, 2);
                bool counted = true;
                if (!eq(ctx, S0, ZR)) {
                    guest::charge(ctx, 6);
                    rt::lw(ctx, A0, S1, 2604);
                    move(ctx, A1, S0);
                    call(ctx, 0x2D4D6C, &rg::fn_datCalcChkBadStatus_00300580);
                    counted = !nz(ctx, V0);
                }
                if (counted) {
                    guest::charge(ctx, 8);
                    rt::lw(ctx, A0, S1, 2604);
                    call(ctx, 0x2D4D80, &rg::fn_datCalcGetLevel_002ffcc0);
                    rt::andi(ctx, V0, V0, 0xFFu);
                    rt::addu(ctx, V0, S4, V0);
                    u16_of(ctx, S4, V0);
                    step16(ctx, S3, V0);
                }
            }
        }
        guest::charge(ctx, 1);
        rt::lw(ctx, S5, S5, 1192);
    }
    guest::charge(ctx, 3);
    u16_of(ctx, V1, S3);
    if (!nz(ctx, V1)) {
        guest::charge(ctx, 3);
        li(ctx, V0, 1);
    } else {
        guest::charge(ctx, 6);
        u16_of(ctx, V0, S4);
        rt::div(ctx, V0, V1);
        rt::mflo(ctx, V0);
        u16_of(ctx, V0, V0);
        if (!nz(ctx, V0)) {
            guest::charge(ctx, 3);
            li(ctx, V0, 1);
        }
    }
    guest::charge(ctx, 10);
}

void btlCountActiveUnits(EEContext& ctx) {
    // (u16 side mask, status): the count of actions with +26 bits 0 and 3 whose unit is on a side of the mask and
    // !datCalcChkBadStatus(DatUnit, status) (status is always tested here).
    guest::enter(ctx, 13);
    Frame frame(ctx, 4);
    move(ctx, S3, A1);
    move(ctx, S1, ZR);
    gbtl(ctx, V0);
    rt::lw(ctx, S2, V0, 332);
    u16_of(ctx, S0, A0);
    for (;;) {
        guest::charge(ctx, 2);
        if (!nz(ctx, S2)) break;
        guest::backedge(ctx);
        guest::charge(ctx, 4);
        rt::lhu(ctx, V1, S2, 26);
        rt::andi(ctx, V0, V1, 0x1u);
        if (!eq(ctx, V0, ZR)) {
            guest::charge(ctx, 3);
            rt::andi(ctx, V0, V1, 0x8u);
            if (!eq(ctx, V0, ZR)) {
                guest::charge(ctx, 7);
                rt::lw(ctx, A0, S2, 48);
                rt::lbu(ctx, V1, A0, 162);
                li(ctx, V0, 1);
                rt::sllv(ctx, V0, V0, V1);
                rt::and_(ctx, V0, S0, V0);
                if (!eq(ctx, V0, ZR)) {
                    guest::charge(ctx, 6);
                    rt::lw(ctx, A0, A0, 2604);
                    move(ctx, A1, S3);
                    call(ctx, 0x2D4E84, &rg::fn_datCalcChkBadStatus_00300580);
                    if (!nz(ctx, V0)) {
                        guest::charge(ctx, 2);
                        step16(ctx, S1, V0);
                    }
                }
            }
        }
        guest::charge(ctx, 1);
        rt::lw(ctx, S2, S2, 1192);
    }
    guest::charge(ctx, 9);
    move(ctx, V0, S1);
}

void btlGetEncounterId(EEContext& ctx) {
    guest::enter(ctx, 5);
    gbtl(ctx, V0);
    rt::lw(ctx, V0, V0, 3004);
    rt::lhu(ctx, V0, V0, 8);
}

void sub_2D5B50(EEContext& ctx) {
    // (skill, compared as the whole register): 331 -> 13; 330 / 329 / 328 / 327 -> 12; else -1.
    guest::enter(ctx, 3);
    li(ctx, V0, 331);
    if (eq(ctx, A0, V0)) {
        guest::charge(ctx, 3);
        li(ctx, V0, 13);
        guest::charge(ctx, 2);
        return;
    }
    for (s32 id = 330; id >= 327; --id) {
        guest::charge(ctx, 3);
        li(ctx, V0, id);
        if (eq(ctx, A0, V0)) {
            guest::charge(ctx, 3);
            li(ctx, V0, 12);
            guest::charge(ctx, 2);
            return;
        }
    }
    guest::charge(ctx, 2);
    guest::charge(ctx, 1);
    li(ctx, V0, -1);
    guest::charge(ctx, 2);
}

void sub_2D5BC0(EEContext& ctx) {
    // One of the five skills 327..331 at random.
    guest::enter(ctx, 10);
    Frame frame(ctx, 0);
    li(ctx, A0, 5);
    call(ctx, 0x2D5BCC, &rg::fn_datCalcRand_002ffbc0);
    rt::addiu(ctx, V0, V0, 327);
}

namespace {
// sub_2D5BF0 / sub_2D5C70: (btlUnit u): sub_17D800() && u DatUnit (+2604) && its id (u16 +2) == `id` && side 0.
void unit_is_pc_on_side0(EEContext& ctx, u32 call_pc, s32 id) {
    guest::enter(ctx, 8);
    Frame frame(ctx, 1);
    move(ctx, S0, A0);
    call(ctx, call_pc, &rg::fn_sub_17D800_0017d800);
    if (!nz(ctx, V0)) {
        guest::charge(ctx, 3);
        move(ctx, V0, ZR);
    } else {
        guest::charge(ctx, 3);
        rt::lw(ctx, V0, S0, 2604);
        if (!nz(ctx, V0)) {
            guest::charge(ctx, 3);
            move(ctx, V0, ZR);
        } else {
            guest::charge(ctx, 4);
            rt::lhu(ctx, V1, V0, 2);
            li(ctx, V0, id);
            if (!eq(ctx, V1, V0)) {
                guest::charge(ctx, 3);
                move(ctx, V0, ZR);
            } else {
                guest::charge(ctx, 3);
                rt::lbu(ctx, V0, S0, 162);
                rt::xor_(ctx, V0, V0, ZR);
                rt::sltiu(ctx, V0, V0, 1);
            }
        }
    }
    guest::charge(ctx, 5);
}
}  // namespace

void sub_2D5BF0(EEContext& ctx) { unit_is_pc_on_side0(ctx, 0x2D5C00, 1); }
void sub_2D5C70(EEContext& ctx) { unit_is_pc_on_side0(ctx, 0x2D5C80, 9); }

void sub_2D5E00(EEContext& ctx) {
    guest::enter(ctx, 3);
    rt::sh(ctx, ZR, A0, 20);
}

void sub_2D5E10(EEContext& ctx) {
    // (btlAction a): any target action (a +56, count u16 a +106) with a result (+224 + 28 j, count byte +200) whose
    // u16 +250 has bit 2 -> 1, else 0.
    guest::enter(ctx, 4);
    move(ctx, T1, ZR);
    rt::lhu(ctx, A3, A0, 106);
    for (;;) {
        guest::charge(ctx, 4);
        if (!below16(ctx, V0, T1, A3)) break;
        guest::backedge(ctx);
        guest::charge(ctx, 8);
        target_entry(ctx, V0, T1, A0, A2);
        move(ctx, T0, ZR);
        rt::lbu(ctx, A1, A2, 200);
        for (;;) {
            guest::charge(ctx, 4);
            if (!below16(ctx, V0, T0, A1)) break;
            guest::backedge(ctx);
            guest::charge(ctx, 9);
            result_entry(ctx, V1, V0, T0, A2, V0);
            rt::lhu(ctx, V0, V0, 250);
            rt::andi(ctx, V0, V0, 0x4u);
            if (!eq(ctx, V0, ZR)) {
                guest::charge(ctx, 3);
                li(ctx, V0, 1);
                guest::charge(ctx, 2);
                return;
            }
            guest::charge(ctx, 2);
            step16(ctx, T0, V0);
        }
        guest::charge(ctx, 2);
        step16(ctx, T1, V0);
    }
    guest::charge(ctx, 1);
    move(ctx, V0, ZR);
    guest::charge(ctx, 2);
}

namespace {
// sub_2D5EB0 / sub_2D6090: any target result whose word at `off` has `bit_hi << 16`.
void any_result_bit(EEContext& ctx, s32 off, u32 bit_hi) {
    guest::enter(ctx, 5);
    move(ctx, T2, ZR);
    rt::lhu(ctx, T0, A0, 106);
    rt::lui(ctx, V1, bit_hi);
    for (;;) {
        guest::charge(ctx, 4);
        if (!below16(ctx, V0, T2, T0)) break;
        guest::backedge(ctx);
        guest::charge(ctx, 8);
        target_entry(ctx, V0, T2, A0, A3);
        move(ctx, T1, ZR);
        rt::lbu(ctx, A2, A3, 200);
        for (;;) {
            guest::charge(ctx, 4);
            if (!below16(ctx, V0, T1, A2)) break;
            guest::backedge(ctx);
            guest::charge(ctx, 9);
            result_entry(ctx, A1, V0, T1, A3, V0);
            rt::lw(ctx, V0, V0, off);
            rt::and_(ctx, V0, V0, V1);
            if (!eq(ctx, V0, ZR)) {
                guest::charge(ctx, 3);
                li(ctx, V0, 1);
                guest::charge(ctx, 2);
                return;
            }
            guest::charge(ctx, 2);
            step16(ctx, T1, V0);
        }
        guest::charge(ctx, 2);
        step16(ctx, T2, V0);
    }
    guest::charge(ctx, 1);
    move(ctx, V0, ZR);
    guest::charge(ctx, 2);
}
}  // namespace

void sub_2D5EB0(EEContext& ctx) { any_result_bit(ctx, 232, 0x10u); }  // result word +232 bit 20

void sub_2D5F50(EEContext& ctx) {
    // (btlAction a): any target action with a non-zero word +212 -> 1, else 0.
    guest::enter(ctx, 4);
    move(ctx, A1, ZR);
    rt::lhu(ctx, V1, A0, 106);
    for (;;) {
        guest::charge(ctx, 4);
        if (!below16(ctx, V0, A1, V1)) break;
        guest::backedge(ctx);
        guest::charge(ctx, 7);
        target_entry(ctx, V0, A1, A0, V0);
        rt::lw(ctx, V0, V0, 212);
        if (!eq(ctx, V0, ZR)) {
            guest::charge(ctx, 3);
            li(ctx, V0, 1);
            guest::charge(ctx, 2);
            return;
        }
        guest::charge(ctx, 2);
        step16(ctx, A1, V0);
    }
    guest::charge(ctx, 1);
    move(ctx, V0, ZR);
    guest::charge(ctx, 2);
}

void sub_2D5FB0(EEContext& ctx) {
    // (btlAction a): over the target actions other than a itself: one on another side -> 0; else (while the answer is
    // still 0) any result with +224 > 0 or +236 != 0 makes the answer 1 (all results of that target are still read).
    guest::enter(ctx, 6);
    move(ctx, V0, ZR);
    move(ctx, A1, ZR);
    rt::lhu(ctx, V1, A0, 106);
    li(ctx, A3, 1);
    for (;;) {
        guest::charge(ctx, 4);
        u16_of(ctx, A2, A1);
        rt::slt(ctx, A2, A2, V1);
        if (!nz(ctx, A2)) break;
        guest::backedge(ctx);
        guest::charge(ctx, 6);
        u16_of(ctx, A2, A1);
        rt::sll(ctx, A2, A2, 2);
        rt::addu(ctx, A2, A0, A2);
        rt::lw(ctx, T2, A2, 56);
        if (!eq(ctx, T2, A0)) {
            guest::charge(ctx, 6);
            rt::lw(ctx, A2, A0, 48);
            rt::lbu(ctx, T0, A2, 162);
            rt::lw(ctx, A2, T2, 48);
            rt::lbu(ctx, A2, A2, 162);
            if (!eq(ctx, T0, A2)) {
                guest::charge(ctx, 3);
                move(ctx, V0, ZR);
                guest::charge(ctx, 2);
                return;
            }
            guest::charge(ctx, 2);
            if (!nz(ctx, V0)) {
                guest::charge(ctx, 4);
                move(ctx, T3, ZR);
                rt::lbu(ctx, T1, T2, 200);
                for (;;) {
                    guest::charge(ctx, 4);
                    u16_of(ctx, A2, T3);
                    rt::slt(ctx, A2, A2, T1);
                    if (!nz(ctx, A2)) break;
                    guest::backedge(ctx);
                    guest::charge(ctx, 8);
                    u16_of(ctx, T0, T3);
                    rt::sll(ctx, A2, T0, 3);
                    rt::subu(ctx, A2, A2, T0);
                    rt::sll(ctx, A2, A2, 2);
                    rt::addu(ctx, T0, T2, A2);
                    rt::lw(ctx, A2, T0, 224);
                    if (!rt::cmp_lez(ctx, A2)) {
                        guest::charge(ctx, 1);
                        move(ctx, V0, A3);
                    }
                    guest::charge(ctx, 3);
                    rt::lw(ctx, A2, T0, 236);
                    if (!eq(ctx, A2, ZR)) {
                        guest::charge(ctx, 1);
                        move(ctx, V0, A3);
                    }
                    guest::charge(ctx, 2);
                    rt::addiu(ctx, A2, T3, 1);
                    u16_of(ctx, T3, A2);
                }
            }
        }
        guest::charge(ctx, 2);
        rt::addiu(ctx, A1, A1, 1);
        u16_of(ctx, A1, A1);
    }
    guest::charge(ctx, 2);
}

void sub_2D6090(EEContext& ctx) { any_result_bit(ctx, 236, 0x8u); }  // result word +236 bit 19

void sub_2D6130(EEContext& ctx) {
    // (btlAction a): over the target actions: +212 != 0 or u16 +204 & 0x500 -> 0; else (while the answer is 0) a result
    // with +224 < 0 makes the answer 1 and ends that target's results.
    guest::enter(ctx, 6);
    move(ctx, V0, ZR);
    move(ctx, A1, ZR);
    rt::lhu(ctx, V1, A0, 106);
    li(ctx, A3, 1);
    for (;;) {
        guest::charge(ctx, 4);
        u16_of(ctx, A2, A1);
        rt::slt(ctx, A2, A2, V1);
        if (!nz(ctx, A2)) break;
        guest::backedge(ctx);
        guest::charge(ctx, 7);
        u16_of(ctx, A2, A1);
        rt::sll(ctx, A2, A2, 2);
        rt::addu(ctx, A2, A0, A2);
        rt::lw(ctx, T2, A2, 56);
        rt::lw(ctx, A2, T2, 212);
        if (!eq(ctx, A2, ZR)) {
            guest::charge(ctx, 3);
            move(ctx, V0, ZR);
            guest::charge(ctx, 2);
            return;
        }
        guest::charge(ctx, 4);
        rt::lhu(ctx, A2, T2, 204);
        rt::andi(ctx, A2, A2, 0x500u);
        if (!eq(ctx, A2, ZR)) {
            guest::charge(ctx, 3);
            move(ctx, V0, ZR);
            guest::charge(ctx, 2);
            return;
        }
        guest::charge(ctx, 2);
        if (!nz(ctx, V0)) {
            guest::charge(ctx, 4);
            rt::lbu(ctx, T1, T2, 200);
            move(ctx, T3, ZR);
            for (;;) {
                guest::charge(ctx, 4);
                u16_of(ctx, A2, T3);
                rt::slt(ctx, A2, A2, T1);
                if (!nz(ctx, A2)) break;
                guest::backedge(ctx);
                guest::charge(ctx, 8);
                u16_of(ctx, T0, T3);
                rt::sll(ctx, A2, T0, 3);
                rt::subu(ctx, A2, A2, T0);
                rt::sll(ctx, A2, A2, 2);
                rt::addu(ctx, A2, T2, A2);
                rt::lw(ctx, A2, A2, 224);
                if (!rt::cmp_gez(ctx, A2)) {
                    guest::charge(ctx, 3);
                    move(ctx, V0, A3);
                    break;
                }
                guest::charge(ctx, 2);
                rt::addiu(ctx, A2, T3, 1);
                u16_of(ctx, T3, A2);
            }
        }
        guest::charge(ctx, 2);
        rt::addiu(ctx, A1, A1, 1);
        u16_of(ctx, A1, A1);
    }
    guest::charge(ctx, 2);
}

void sub_2D6210(EEContext& ctx) {
    // (btlAction a): any target action with +212 != 0 or u16 +204 & 0x500 -> 1, else 0.
    guest::enter(ctx, 4);
    move(ctx, A2, ZR);
    rt::lhu(ctx, A1, A0, 106);
    for (;;) {
        guest::charge(ctx, 4);
        if (!below16(ctx, V0, A2, A1)) break;
        guest::backedge(ctx);
        guest::charge(ctx, 7);
        target_entry(ctx, V0, A2, A0, V1);
        rt::lw(ctx, V0, V1, 212);
        if (!eq(ctx, V0, ZR)) {
            guest::charge(ctx, 3);
            li(ctx, V0, 1);
            guest::charge(ctx, 2);
            return;
        }
        guest::charge(ctx, 4);
        rt::lhu(ctx, V0, V1, 204);
        rt::andi(ctx, V0, V0, 0x500u);
        if (!eq(ctx, V0, ZR)) {
            guest::charge(ctx, 3);
            li(ctx, V0, 1);
            guest::charge(ctx, 2);
            return;
        }
        guest::charge(ctx, 2);
        step16(ctx, A2, V0);
    }
    guest::charge(ctx, 1);
    move(ctx, V0, ZR);
    guest::charge(ctx, 2);
}

void sub_2D62D0(EEContext& ctx) {
    // (btlAction a): fewer than 2 targets -> 0; an active target (+26 bit 0) whose unit is on another side than a's
    // -> 0; else 1.
    guest::enter(ctx, 6);
    rt::lw(ctx, V0, A0, 48);
    rt::lbu(ctx, V0, V0, 162);
    rt::lhu(ctx, A2, A0, 106);
    rt::slti(ctx, AT, A2, 2);
    if (!eq(ctx, AT, ZR)) {
        guest::charge(ctx, 3);
        move(ctx, V0, ZR);
        guest::charge(ctx, 2);
        return;
    }
    guest::charge(ctx, 4);
    move(ctx, A3, ZR);
    rt::andi(ctx, A1, V0, 0xFFu);
    for (;;) {
        guest::charge(ctx, 4);
        if (!below16(ctx, V0, A3, A2)) break;
        guest::backedge(ctx);
        guest::charge(ctx, 8);
        target_entry(ctx, V0, A3, A0, V1);
        rt::lhu(ctx, V0, V1, 26);
        rt::andi(ctx, V0, V0, 0x1u);
        if (!eq(ctx, V0, ZR)) {
            guest::charge(ctx, 4);
            rt::lw(ctx, V0, V1, 48);
            rt::lbu(ctx, V0, V0, 162);
            if (!eq(ctx, V0, A1)) {
                guest::charge(ctx, 3);
                move(ctx, V0, ZR);
                guest::charge(ctx, 2);
                return;
            }
        }
        guest::charge(ctx, 2);
        step16(ctx, A3, V0);
    }
    guest::charge(ctx, 1);
    li(ctx, V0, 1);
    guest::charge(ctx, 2);
}

namespace {
// `lw a?, -18680(gp)` + the 44-byte SkillRecord of (s16) `id_src` (`dsll32/dsra32 16; 11 * 4 * id`): its address in
// V0 and the s16 id in V1.
void skill_record(EEContext& ctx, Reg tbl, Reg id_src, bool tbl_first) {
    if (tbl_first) rt::lw(ctx, tbl, GP, kGpTbl3F8);
    s16_of(ctx, V1, id_src);
    if (!tbl_first) rt::lw(ctx, tbl, GP, kGpTbl3F8);
    rt::sll(ctx, V0, V1, 2);
    rt::addu(ctx, V0, V0, V1);
    rt::sll(ctx, V0, V0, 1);
    rt::addu(ctx, V0, V0, V1);
    rt::sll(ctx, V0, V0, 2);
    rt::addu(ctx, V0, V0, tbl);
}
}  // namespace

void datCalcIsHpSkill(EEContext& ctx) {
    // ((s16) skill): SkillRecord kind (byte +2) == 1 (an HP skill).
    guest::enter(ctx, 14);
    skill_record(ctx, A1, A0, true);
    rt::lbu(ctx, V0, V0, 2);
    rt::xori(ctx, V0, V0, 0x1u);
    rt::sltiu(ctx, V0, V0, 1);
}

void sub_2D63B0(EEContext& ctx) {
    // (btlUnit u, (s16) skill, flag): kind == 1 (an HP skill) and flag and MODEL.TBL section 3 ($gp - 18628, 88-byte
    // records by u's id u16 +164) has bit 4 of u16 +0 clear and EFFECT.TBL section 0 record skill has bit 0 of u16 +2.
    guest::enter(ctx, 13);
    skill_record(ctx, A1, A1, false);
    rt::lbu(ctx, A1, V0, 2);
    li(ctx, V0, 1);
    if (!eq(ctx, A1, V0)) {
        guest::charge(ctx, 3);
        move(ctx, V0, ZR);
        guest::charge(ctx, 2);
        return;
    }
    guest::charge(ctx, 2);
    if (!eq(ctx, A2, ZR)) {
        guest::charge(ctx, 12);
        rt::lhu(ctx, A1, A0, 164);
        rt::sll(ctx, A0, A1, 2);
        rt::addu(ctx, A0, A0, A1);
        rt::sll(ctx, A0, A0, 1);
        rt::addu(ctx, A0, A0, A1);
        rt::sll(ctx, A1, A0, 3);
        rt::lw(ctx, A0, GP, kGpTbl42C);
        rt::addu(ctx, A0, A0, A1);
        rt::lhu(ctx, A0, A0, 0);
        rt::andi(ctx, A0, A0, 0x10u);
        if (eq(ctx, A0, ZR)) {
            guest::charge(ctx, 9);
            rt::lw(ctx, A1, GP, kGpTbl400);
            rt::sll(ctx, A0, V1, 3);
            rt::subu(ctx, V1, A0, V1);
            rt::sll(ctx, V1, V1, 2);
            rt::addu(ctx, V1, V1, A1);
            rt::lhu(ctx, V1, V1, 2);
            rt::andi(ctx, V1, V1, 0x1u);
            if (!eq(ctx, V1, ZR)) {
                guest::charge(ctx, 2);
                return;  // $v0 = 1
            }
        }
    }
    guest::charge(ctx, 1);
    move(ctx, V0, ZR);
    guest::charge(ctx, 2);
}

// === the per-unit counters ==========================================================================================

void sub_2D7970(EEContext& ctx) {
    guest::enter(ctx, 12);
    bump_counter(ctx, A0, 0, A1, 1);
    bump_counter(ctx, A0, 4, A0, 1);
}

void sub_2D7DF0(EEContext& ctx) {
    guest::enter(ctx, 12);
    bump_counter(ctx, A0, 0, A1, -1);
    bump_counter(ctx, A0, 4, A0, -1);
}

void sub_2D7EF0(EEContext& ctx) {
    guest::enter(ctx, 7);
    bump_counter(ctx, A0, 0, A0, 1);
}

void sub_2D7F10(EEContext& ctx) {
    // p = a0: byte p +4 bit 1 -> (*p) +40 = 0; bit 0 -> (*p) +40 += 1; else when (*p) +40 > 0: +40 = max(+40, 1) - 1.
    // Returns 1.
    guest::enter(ctx, 4);
    rt::lbu(ctx, V1, A0, 4);
    rt::andi(ctx, V0, V1, 0x2u);
    if (!eq(ctx, V0, ZR)) {
        guest::charge(ctx, 4);
        rt::lw(ctx, V0, A0, 0);
        rt::sb(ctx, ZR, V0, 40);
    } else {
        guest::charge(ctx, 3);
        rt::andi(ctx, V0, V1, 0x1u);
        if (!eq(ctx, V0, ZR)) {
            guest::charge(ctx, 6);
            rt::lw(ctx, V1, A0, 0);
            rt::lbu(ctx, V0, V1, 40);
            rt::addiu(ctx, V0, V0, 1);
            rt::sb(ctx, V0, V1, 40);
        } else {
            guest::charge(ctx, 5);
            rt::lw(ctx, V0, A0, 0);
            rt::addiu(ctx, V1, V0, 40);
            rt::lbu(ctx, V0, V0, 40);
            if (!rt::cmp_lez(ctx, V0)) {
                guest::charge(ctx, 3);
                rt::slti(ctx, AT, V0, 2);
                if (eq(ctx, AT, ZR)) {
                    guest::charge(ctx, 1);
                    rt::daddiu(ctx, V0, ZR, 1);
                }
                guest::charge(ctx, 3);
                rt::andi(ctx, V0, V0, 0xFFu);
                rt::addiu(ctx, V0, V0, -1);
                rt::sb(ctx, V0, V1, 0);
            }
        }
    }
    guest::charge(ctx, 3);
    li(ctx, V0, 1);
}

void sub_2D7F90(EEContext& ctx) {
    guest::enter(ctx, 7);
    bump_counter(ctx, A0, 0, A0, -1);
}

void sub_2D8020(EEContext& ctx) {
    guest::enter(ctx, 7);
    bump_counter(ctx, A0, 0, A0, 1);
}

void sub_2D8070(EEContext& ctx) {
    guest::enter(ctx, 7);
    bump_counter(ctx, A0, 0, A0, -1);
}

void sub_2D80F0(EEContext& ctx) {
    guest::enter(ctx, 7);
    bump_counter(ctx, A0, 0, A0, 1);
}

void sub_2D8310(EEContext& ctx) {
    guest::enter(ctx, 7);
    bump_counter(ctx, A0, 0, A0, -1);
}

// === support (navigator) line pickers: rows of 0x6978F0 ============================================================

namespace {
// `addiu v0, zero, value` as the whole body after the entry block of `cycles` (the constant rows).
void constant_row(EEContext& ctx, s32 value) {
    guest::enter(ctx, 3);
    li(ctx, V0, value);
}
// The encounter-417 rows: `id == 417 ? hit : miss`.
void encounter417_row(EEContext& ctx, s32 hit, s32 miss) {
    guest::enter(ctx, 6);
    encounter_id(ctx, V0, V0, V1);
    li(ctx, V0, 417);
    if (eq(ctx, V1, V0)) {
        guest::charge(ctx, 3);
        li(ctx, V0, hit);
    } else {
        guest::charge(ctx, 2);
        guest::charge(ctx, 1);
        li(ctx, V0, miss);
    }
    guest::charge(ctx, 2);
}
}  // namespace

void sub_2D8680(EEContext& ctx) {
    // (a0, a1): a1 == 1 -> -1; a1 == 0 -> 95; else -1 (the whole registers are compared).
    guest::enter(ctx, 3);
    li(ctx, V0, 1);
    if (eq(ctx, A1, V0)) {
        guest::charge(ctx, 3);
        li(ctx, V0, -1);
    } else {
        guest::charge(ctx, 2);
        if (eq(ctx, A1, ZR)) {
            guest::charge(ctx, 3);
            li(ctx, V0, 95);
        } else {
            guest::charge(ctx, 2);
            guest::charge(ctx, 1);
            li(ctx, V0, -1);
        }
    }
    guest::charge(ctx, 2);
}

void sub_2D8A80(EEContext& ctx) { encounter417_row(ctx, 136, 135); }
void sub_2D8AC0(EEContext& ctx) { encounter417_row(ctx, 132, 131); }
void sub_2D8B00(EEContext& ctx) { constant_row(ctx, 143); }
void sub_2D8B10(EEContext& ctx) { constant_row(ctx, 182); }
void sub_2D8B20(EEContext& ctx) { constant_row(ctx, 177); }
void sub_2D8B30(EEContext& ctx) { constant_row(ctx, 178); }
void sub_2D8DB0(EEContext& ctx) { constant_row(ctx, -1); }

void sub_2D8EF0(EEContext& ctx) {
    // (btlAction a): a is gBtl's current action (+328) -> 234; else a's unit is an enemy -> 235; else -1.
    guest::enter(ctx, 4);
    gbtl(ctx, V0);
    rt::lw(ctx, V0, V0, 328);
    if (!ne(ctx, V0, A0)) {
        guest::charge(ctx, 3);
        li(ctx, V0, 234);
    } else {
        guest::charge(ctx, 5);
        rt::lw(ctx, V0, A0, 48);
        rt::lbu(ctx, V1, V0, 162);
        li(ctx, V0, 1);
        if (!ne(ctx, V1, V0)) {
            guest::charge(ctx, 3);
            li(ctx, V0, 235);
        } else {
            guest::charge(ctx, 1);
            li(ctx, V0, -1);
        }
    }
    guest::charge(ctx, 2);
}

void sub_2D8F40(EEContext& ctx) {
    // (btlAction a): a is gBtl's current action -> 398, else -1.
    guest::enter(ctx, 4);
    gbtl(ctx, V0);
    rt::lw(ctx, V0, V0, 328);
    if (!ne(ctx, V0, A0)) {
        guest::charge(ctx, 3);
        li(ctx, V0, 398);
    } else {
        guest::charge(ctx, 1);
        li(ctx, V0, -1);
    }
    guest::charge(ctx, 2);
}

void sub_2D9AA0(EEContext& ctx) {
    // (btlAction a, flags): a party unit and gBtl's current action: flags bit 1 -> 336, bit 2 -> 335; else -1.
    guest::enter(ctx, 4);
    rt::lw(ctx, V0, A0, 48);
    rt::lbu(ctx, V0, V0, 162);
    if (!eq(ctx, V0, ZR)) {
        guest::charge(ctx, 3);
        li(ctx, V0, -1);
    } else {
        guest::charge(ctx, 4);
        gbtl(ctx, V0);
        rt::lw(ctx, V0, V0, 328);
        if (!eq(ctx, V0, A0)) {
            guest::charge(ctx, 3);
            li(ctx, V0, -1);
        } else {
            guest::charge(ctx, 3);
            rt::andi(ctx, V0, A1, 0x2u);
            if (!eq(ctx, V0, ZR)) {
                guest::charge(ctx, 3);
                li(ctx, V0, 336);
            } else {
                guest::charge(ctx, 3);
                rt::andi(ctx, V0, A1, 0x4u);
                if (!eq(ctx, V0, ZR)) {
                    guest::charge(ctx, 3);
                    li(ctx, V0, 335);
                } else {
                    guest::charge(ctx, 1);
                    li(ctx, V0, -1);
                }
            }
        }
    }
    guest::charge(ctx, 2);
}

void sub_2D9D60(EEContext& ctx) { constant_row(ctx, -1); }

// === the support state in gBtl ======================================================================================

void btlSupportClearFlag(EEContext& ctx) {
    // (u16 n): gBtl +2564 &= ~(1 << n) (u16).
    guest::enter(ctx, 11);
    u16_of(ctx, A0, A0);
    li(ctx, V1, 1);
    rt::sllv(ctx, V1, V1, A0);
    rt::nor(ctx, V1, V1, ZR);
    u16_of(ctx, A1, V1);
    gbtl(ctx, A0);
    rt::lhu(ctx, V1, A0, 2564);
    rt::and_(ctx, V1, V1, A1);
    rt::sh(ctx, V1, A0, 2564);
}

void btlSupportTestFlag(EEContext& ctx) {
    // (u16 n): gBtl +2564 bit n != 0.
    guest::enter(ctx, 9);
    gbtl(ctx, V0);
    rt::lhu(ctx, A1, V0, 2564);
    u16_of(ctx, V1, A0);
    li(ctx, V0, 1);
    rt::sllv(ctx, V0, V0, V1);
    rt::and_(ctx, V0, A1, V0);
    rt::sltu(ctx, V0, ZR, V0);
}

void sub_2DB690(EEContext& ctx) {
    guest::enter(ctx, 4);
    gbtl(ctx, V0);
    rt::lw(ctx, V0, V0, 2568);
}

void btlSupportRequestLine(EEContext& ctx) {
    // (u16 line, id): when a line is playing (+2582 bit 0) for this id (+2592 or +2600 == id) -> 1; else queue it:
    // +2604 = line (u16), +2600 = id, +2584 = 1; returns 1.
    guest::enter(ctx, 5);
    gbtl(ctx, V1);
    rt::lhu(ctx, V0, V1, 2582);
    rt::andi(ctx, V0, V0, 0x1u);
    if (!eq(ctx, V0, ZR)) {
        guest::charge(ctx, 3);
        rt::lw(ctx, V0, V1, 2592);
        if (!ne(ctx, V0, A1)) {
            guest::charge(ctx, 3);
            li(ctx, V0, 1);
            guest::charge(ctx, 2);
            return;
        }
        guest::charge(ctx, 3);
        rt::lw(ctx, V0, V1, 2600);
        if (!ne(ctx, V0, A1)) {
            guest::charge(ctx, 3);
            li(ctx, V0, 1);
            guest::charge(ctx, 2);
            return;
        }
    }
    guest::charge(ctx, 6);
    rt::sh(ctx, A0, V1, 2604);
    gbtl(ctx, V0);
    rt::sw(ctx, A1, V0, 2600);
    li(ctx, V0, 1);
    gbtl(ctx, V1);
    rt::sh(ctx, V0, V1, 2584);
    guest::charge(ctx, 2);
}

void btlSupportIsBusy(EEContext& ctx) {
    guest::enter(ctx, 6);
    gbtl(ctx, V0);
    rt::lhu(ctx, V0, V0, 2582);
    rt::andi(ctx, V0, V0, 0x1u);
    rt::sltu(ctx, V0, ZR, V0);
}

void sub_2DC130(EEContext& ctx) {
    // (btlAction a): a +24 bit 2 -> 0; else datCalcChkBadStatus(a's DatUnit, 0x80) != 0.
    guest::enter(ctx, 8);
    Frame frame(ctx, 0);
    rt::lw(ctx, V0, A0, 48);
    rt::lw(ctx, V1, V0, 2604);
    rt::lhu(ctx, V0, A0, 24);
    rt::andi(ctx, V0, V0, 0x4u);
    if (!eq(ctx, V0, ZR)) {
        guest::charge(ctx, 3);
        move(ctx, V0, ZR);
    } else {
        guest::charge(ctx, 5);
        move(ctx, A0, V1);
        li(ctx, A1, 128);
        call(ctx, 0x2DC164, &rg::fn_datCalcChkBadStatus_00300580);
        rt::sltu(ctx, V0, ZR, V0);
    }
    guest::charge(ctx, 4);
}

void sub_2DC550(EEContext& ctx) {
    // (btlAction a, bits): bits != 0: for k < 24, a bit of `bits` that the DatUnit's status word lacks clears the
    // counter byte a +1122 + k.
    guest::enter(ctx, 8);
    Frame frame(ctx, 2);
    move(ctx, S1, A0);
    move(ctx, S0, A1);
    if (!eq(ctx, S0, ZR)) {
        guest::charge(ctx, 8);
        rt::lw(ctx, V0, S1, 48);
        rt::lw(ctx, A0, V0, 2604);
        call(ctx, 0x2DC578, &rg::fn_datCalcGetBadStatus_00300550);
        move(ctx, A2, ZR);
        li(ctx, A1, 1);
        for (;;) {
            guest::charge(ctx, 3);
            rt::sltiu(ctx, V1, A2, 24);
            if (!nz(ctx, V1)) break;
            guest::backedge(ctx);
            guest::charge(ctx, 4);
            rt::sllv(ctx, A0, A1, A2);
            rt::and_(ctx, V1, S0, A0);
            if (!eq(ctx, V1, ZR)) {
                guest::charge(ctx, 3);
                rt::and_(ctx, V1, V0, A0);
                if (eq(ctx, V1, ZR)) {
                    guest::charge(ctx, 2);
                    rt::addu(ctx, V1, S1, A2);
                    rt::sb(ctx, ZR, V1, 1122);
                }
            }
            guest::charge(ctx, 1);
            rt::addiu(ctx, A2, A2, 1);
        }
    }
    guest::charge(ctx, 6);
}

void sub_2DC5E0(EEContext& ctx) {
    // (btlAction a): for k < 24, a bit of the DatUnit's status word counts the byte a +1122 + k up (below 255).
    guest::enter(ctx, 12);
    Frame frame(ctx, 1);
    move(ctx, S0, A0);
    rt::lw(ctx, V0, A0, 48);
    rt::lw(ctx, A0, V0, 2604);
    call(ctx, 0x2DC5F8, &rg::fn_datCalcGetBadStatus_00300550);
    move(ctx, A2, ZR);
    li(ctx, A1, 1);
    for (;;) {
        guest::charge(ctx, 3);
        rt::sltiu(ctx, V1, A2, 24);
        if (!nz(ctx, V1)) break;
        guest::backedge(ctx);
        guest::charge(ctx, 4);
        rt::sllv(ctx, V1, A1, A2);
        rt::and_(ctx, V1, V0, V1);
        if (!eq(ctx, V1, ZR)) {
            guest::charge(ctx, 6);
            rt::addu(ctx, V1, S0, A2);
            rt::addiu(ctx, A0, V1, 1122);
            rt::lbu(ctx, V1, V1, 1122);
            rt::slti(ctx, AT, V1, 255);
            if (!eq(ctx, AT, ZR)) {
                guest::charge(ctx, 2);
                rt::addiu(ctx, V1, V1, 1);
                rt::sb(ctx, V1, A0, 0);
            }
        }
        guest::charge(ctx, 1);
        rt::addiu(ctx, A2, A2, 1);
    }
    guest::charge(ctx, 5);
}

void btlSupportResetTimers(EEContext& ctx) {
    // The support timers' reset: gBtl +2704 = 5 (u16), +2706 = -1 (s8), slot k (k < 16, six bytes at +2708):
    // {s16 -1, s16 -1, s8 3}.
    guest::enter(ctx, 10);
    li(ctx, A0, 5);
    gbtl(ctx, V1);
    rt::sh(ctx, A0, V1, 2704);
    li(ctx, A2, -1);
    gbtl(ctx, V1);
    rt::sb(ctx, A2, V1, 2706);
    move(ctx, A3, ZR);
    li(ctx, A0, 3);
    for (;;) {
        guest::charge(ctx, 4);
        u16_of(ctx, V1, A3);
        rt::slti(ctx, V1, V1, 16);
        if (!nz(ctx, V1)) break;
        guest::backedge(ctx);
        guest::charge(ctx, 15);
        u16_of(ctx, A1, A3);
        rt::sll(ctx, V1, A1, 1);
        rt::addu(ctx, V1, V1, A1);
        rt::sll(ctx, A1, V1, 1);
        gbtl(ctx, V1);
        rt::addu(ctx, V1, V1, A1);
        rt::sh(ctx, A2, V1, 2708);
        gbtl(ctx, V1);
        rt::addu(ctx, V1, V1, A1);
        rt::sh(ctx, A2, V1, 2710);
        gbtl(ctx, V1);
        rt::addu(ctx, V1, V1, A1);
        rt::sb(ctx, A0, V1, 2712);
        step16(ctx, A3, V1);
    }
    guest::charge(ctx, 2);
}

void btlSupportTickTimers(EEContext& ctx) {
    // The support timers' tick: the s8 +2706 and each slot's s8 +2712 count up while >= 0; reaching 3 or more resets +2706 to
    // -1 and a slot to {-1, -1, -1}.
    guest::enter(ctx, 5);
    gbtl(ctx, V1);
    rt::addiu(ctx, A0, V1, 2706);
    rt::lb(ctx, V1, V1, 2706);
    if (!rt::cmp_ltz(ctx, V1)) {
        guest::charge(ctx, 7);
        rt::addiu(ctx, V1, V1, 1);
        rt::sb(ctx, V1, A0, 0);
        s8_of(ctx, V1, V1);
        rt::slti(ctx, V1, V1, 3);
        if (eq(ctx, V1, ZR)) {
            guest::charge(ctx, 3);
            li(ctx, A0, -1);
            gbtl(ctx, V1);
            rt::sb(ctx, A0, V1, 2706);
        }
    }
    guest::charge(ctx, 4);
    move(ctx, T0, ZR);
    li(ctx, A0, -1);
    for (;;) {
        guest::charge(ctx, 4);
        u16_of(ctx, V1, T0);
        rt::slti(ctx, V1, V1, 16);
        if (!nz(ctx, V1)) break;
        guest::backedge(ctx);
        guest::charge(ctx, 10);
        gbtl(ctx, A3);
        u16_of(ctx, A1, T0);
        rt::sll(ctx, V1, A1, 1);
        rt::addu(ctx, V1, V1, A1);
        rt::sll(ctx, A2, V1, 1);
        rt::addu(ctx, V1, A3, A2);
        rt::addiu(ctx, A1, V1, 2712);
        rt::lb(ctx, V1, V1, 2712);
        if (!rt::cmp_ltz(ctx, V1)) {
            guest::charge(ctx, 7);
            rt::addiu(ctx, V1, V1, 1);
            rt::sb(ctx, V1, A1, 0);
            s8_of(ctx, V1, V1);
            rt::slti(ctx, V1, V1, 3);
            if (eq(ctx, V1, ZR)) {
                guest::charge(ctx, 9);
                gbtl(ctx, V1);
                rt::addu(ctx, V1, V1, A2);
                rt::sh(ctx, A0, V1, 2708);
                gbtl(ctx, V1);
                rt::addu(ctx, V1, V1, A2);
                rt::sh(ctx, A0, V1, 2710);
                gbtl(ctx, V1);
                rt::addu(ctx, V1, V1, A2);
                rt::sb(ctx, A0, V1, 2712);
            }
        }
        guest::charge(ctx, 2);
        step16(ctx, T0, V1);
    }
    guest::charge(ctx, 2);
}

void nullsub_19(EEContext& ctx) { guest::enter(ctx, 2); }

namespace {
// sub_2DD8B0 / sub_2DD930: (u32* p): when (*p) +152 has bit 1, its model record (+2548) gets +1022 |= 0x20 / &=
// ~0x20; returns 1.
void model_flag20(EEContext& ctx, bool on) {
    guest::enter(ctx, 5);
    rt::lw(ctx, V1, A0, 0);
    rt::lw(ctx, V0, V1, 152);
    rt::andi(ctx, V0, V0, 0x2u);
    if (!eq(ctx, V0, ZR)) {
        guest::charge(ctx, 4);
        rt::lw(ctx, V1, V1, 2548);
        rt::lhu(ctx, V0, V1, 1022);
        if (on)
            rt::ori(ctx, V0, V0, 0x20u);
        else
            rt::andi(ctx, V0, V0, 0xFFDFu);
        rt::sh(ctx, V0, V1, 1022);
    }
    guest::charge(ctx, 3);
    li(ctx, V0, 1);
}
}  // namespace

void sub_2DD8B0(EEContext& ctx) { model_flag20(ctx, true); }
void sub_2DD930(EEContext& ctx) { model_flag20(ctx, false); }

// === boss rules =====================================================================================================

void sub_2E2630(EEContext& ctx) {
    // (btlAction a): a's unit is enemy 294 -> 828, else -1.
    guest::enter(ctx, 5);
    rt::lw(ctx, A0, A0, 48);
    rt::lbu(ctx, V1, A0, 162);
    li(ctx, V0, 1);
    bool hit = false;
    if (!ne(ctx, V1, V0)) {
        guest::charge(ctx, 4);
        rt::lhu(ctx, V1, A0, 164);
        li(ctx, V0, 294);
        hit = eq(ctx, V1, V0);
        if (!hit) guest::charge(ctx, 2);
    }
    if (hit) {
        guest::charge(ctx, 3);
        li(ctx, V0, 828);
    } else {
        guest::charge(ctx, 1);
        li(ctx, V0, -1);
    }
    guest::charge(ctx, 2);
}

void nullsub_20(EEContext& ctx) { guest::enter(ctx, 2); }

void sub_2E33F0(EEContext& ctx) {
    // (btlAction a): a party unit -> its (s16) id; an enemy: the id chain below (the compare constant stays in $v0, so
    // 234 and 233 return themselves), other ids -> -1.
    struct Case {
        s32 id;
        s32 cycles;  // the cost of the case block
        s32 result;  // kKeep: the compare constant already in $v0
    };
    constexpr s32 kKeep = 0x7FFFFFFF;
    static constexpr Case kCases[] = {
        {240, 3, 4}, {239, 3, 2}, {238, 3, 10}, {237, 3, 5}, {236, 3, 8}, {235, 3, 7}, {234, 2, kKeep},
        {233, 2, kKeep}, {294, 3, 103}, {264, 3, 17}, {271, 3, 16}, {268, 3, 16}, {272, 3, 15}, {267, 3, 15},
    };
    guest::enter(ctx, 5);
    rt::lw(ctx, A0, A0, 48);
    rt::lbu(ctx, V1, A0, 162);
    li(ctx, V0, 1);
    if (ne(ctx, V1, V0)) {
        guest::charge(ctx, 1);
        rt::lh(ctx, V0, A0, 164);
        guest::charge(ctx, 2);
        return;
    }
    guest::charge(ctx, 4);
    rt::lhu(ctx, V1, A0, 164);
    for (std::size_t i = 0; i < std::size(kCases); ++i) {
        if (i != 0) guest::charge(ctx, 3);
        li(ctx, V0, kCases[i].id);
        if (eq(ctx, V1, V0)) {
            guest::charge(ctx, static_cast<u64>(kCases[i].cycles));
            if (kCases[i].result != kKeep) li(ctx, V0, kCases[i].result);
            guest::charge(ctx, 2);
            return;
        }
    }
    guest::charge(ctx, 2);
    guest::charge(ctx, 3);
    li(ctx, V0, -1);
    guest::charge(ctx, 2);
}

void sub_2E4220(EEContext& ctx) {
    guest::enter(ctx, 8);
    gbtl(ctx, V1);
    rt::sw(ctx, A0, V1, 2824);
    gbtl(ctx, V1);
    rt::sw(ctx, A1, V1, 2828);
    gbtl(ctx, V1);
    rt::sw(ctx, A2, V1, 2832);
}

void sub_2E4240(EEContext& ctx) {
    guest::enter(ctx, 4);
    gbtl(ctx, V1);
    rt::sw(ctx, A0, V1, 2832);
}

void sub_2E4250(EEContext& ctx) {
    guest::enter(ctx, 4);
    gbtl(ctx, V1);
    rt::lw(ctx, V0, V1, 2824);
    bool any = nz(ctx, V0);
    if (!any) {
        guest::charge(ctx, 3);
        rt::lw(ctx, V0, V1, 2828);
        any = nz(ctx, V0);
    }
    if (any) {
        guest::charge(ctx, 3);
        li(ctx, V0, 1);
    } else {
        guest::charge(ctx, 1);
        move(ctx, V0, ZR);
    }
    guest::charge(ctx, 2);
}

void sub_2EC4B0(EEContext& ctx) {
    // (btlUnit u): enemy 263 with +152 bit 1: its model record's byte +1053 fades up by 32 to 255 while gBtl +2892,
    // else down by 32 to 0.
    guest::enter(ctx, 4);
    rt::lbu(ctx, A1, A0, 162);
    li(ctx, V1, 1);
    if (ne(ctx, A1, V1)) {
        guest::charge(ctx, 2);
        return;
    }
    guest::charge(ctx, 4);
    rt::lhu(ctx, A1, A0, 164);
    li(ctx, V1, 263);
    if (ne(ctx, A1, V1)) {
        guest::charge(ctx, 2);
        return;
    }
    guest::charge(ctx, 4);
    rt::lw(ctx, V1, A0, 152);
    rt::andi(ctx, V1, V1, 0x2u);
    if (eq(ctx, V1, ZR)) {
        guest::charge(ctx, 2);
        return;
    }
    guest::charge(ctx, 4);
    gbtl(ctx, V1);
    rt::lw(ctx, V1, V1, 2892);
    if (!eq(ctx, V1, ZR)) {
        guest::charge(ctx, 6);
        rt::lw(ctx, V1, A0, 2548);
        rt::addiu(ctx, A0, V1, 1053);
        rt::lbu(ctx, V1, V1, 1053);
        rt::slti(ctx, AT, V1, 223);
        if (!eq(ctx, AT, ZR)) {
            guest::charge(ctx, 4);
            rt::addiu(ctx, V1, V1, 32);
            rt::sb(ctx, V1, A0, 0);
        } else {
            guest::charge(ctx, 4);
            li(ctx, V1, 255);
            rt::sb(ctx, V1, A0, 0);
        }
    } else {
        guest::charge(ctx, 6);
        rt::lw(ctx, V1, A0, 2548);
        rt::addiu(ctx, A0, V1, 1053);
        rt::lbu(ctx, V1, V1, 1053);
        rt::slti(ctx, AT, V1, 33);
        if (eq(ctx, AT, ZR)) {
            guest::charge(ctx, 4);
            rt::addiu(ctx, V1, V1, -32);
            rt::sb(ctx, V1, A0, 0);
        } else {
            guest::charge(ctx, 1);
            rt::sb(ctx, ZR, A0, 0);
        }
    }
    guest::charge(ctx, 2);
}

namespace {
// The encounter-specific word getters: `encounter == id ? gBtl[off] : 0` (sub_2EC590, sub_2F6C20).
void encounter_word(EEContext& ctx, s32 id, s32 off) {
    guest::enter(ctx, 6);
    encounter_id(ctx, A0, V0, V1);
    li(ctx, V0, id);
    if (!ne(ctx, V1, V0)) {
        guest::charge(ctx, 3);
        rt::lw(ctx, V0, A0, off);
    } else {
        guest::charge(ctx, 1);
        move(ctx, V0, ZR);
    }
    guest::charge(ctx, 2);
}
}  // namespace

void sub_2EC560(EEContext& ctx) {
    // (x): encounter 421 -> gBtl +2884 = 1, +2888 = x.
    guest::enter(ctx, 6);
    encounter_id(ctx, A2, V1, A1);
    li(ctx, V1, 421);
    if (!ne(ctx, A1, V1)) {
        guest::charge(ctx, 4);
        li(ctx, V1, 1);
        rt::sw(ctx, V1, A2, 2884);
        gbtl(ctx, V1);
        rt::sw(ctx, A0, V1, 2888);
    }
    guest::charge(ctx, 2);
}

void sub_2EC590(EEContext& ctx) { encounter_word(ctx, 421, 2884); }

void sub_2ECAC0(EEContext& ctx) {
    // The first btlUnit of the list gBtl +344 (next +2612) with id 266: !datCalcIsDead(its DatUnit, 0); none -> 0.
    guest::enter(ctx, 7);
    Frame frame(ctx, 0);
    gbtl(ctx, V0);
    rt::lw(ctx, A0, V0, 344);
    li(ctx, V0, 266);
    for (;;) {
        guest::charge(ctx, 2);
        if (!nz(ctx, A0)) break;
        guest::backedge(ctx);
        guest::charge(ctx, 3);
        rt::lhu(ctx, V1, A0, 164);
        if (!ne(ctx, V1, V0)) {
            guest::charge(ctx, 8);
            rt::lw(ctx, A0, A0, 2604);
            move(ctx, A1, ZR);
            call(ctx, 0x2ECAF0, &rg::fn_datCalcIsDead_0030b5a0);
            rt::xor_(ctx, V0, V0, ZR);
            rt::sltiu(ctx, V0, V0, 1);
            guest::charge(ctx, 4);
            return;
        }
        guest::charge(ctx, 1);
        rt::lw(ctx, A0, A0, 2612);
    }
    guest::charge(ctx, 1);
    move(ctx, V0, ZR);
    guest::charge(ctx, 4);
}

void sub_2ED350(EEContext& ctx) {
    guest::enter(ctx, 4);
    gbtl(ctx, V1);
    rt::sh(ctx, ZR, V1, 2904);
}

void sub_2EFD10(EEContext& ctx) {
    guest::enter(ctx, 4);
    gbtl(ctx, V0);
    rt::lw(ctx, V0, V0, 2900);
}

void sub_2F23D0(EEContext& ctx) {
    // (btlUnit u): sub_302380(u's DatUnit, 0x4000000, 1) [effect flag bit 26 on]; gBtl +2896 = 1; returns 1.
    guest::enter(ctx, 14);
    Frame frame(ctx, 0);
    rt::lw(ctx, A0, A0, 2604);
    rt::lui(ctx, A1, 0x400u);
    li(ctx, A2, 1);
    call(ctx, 0x2F23E4, &rg::fn_sub_302380_00302380);
    li(ctx, V0, 1);
    gbtl(ctx, V1);
    rt::sw(ctx, V0, V1, 2896);
}

void sub_2F2410(EEContext& ctx) {
    // (btlUnit u): datCalcClearEffect(u's DatUnit, 11); gBtl +2896 = 0; returns 1.
    guest::enter(ctx, 13);
    Frame frame(ctx, 0);
    rt::lw(ctx, A0, A0, 2604);
    li(ctx, A1, 11);
    call(ctx, 0x2F2420, &rg::fn_datCalcClearEffect_00301540);
    gbtl(ctx, V0);
    rt::sw(ctx, ZR, V0, 2896);
    li(ctx, V0, 1);
}

void sub_2F24D0(EEContext& ctx) {
    // (s8) datCalcGetEffectState(the first btlUnit's DatUnit, 11) > 0.
    guest::enter(ctx, 15);
    Frame frame(ctx, 0);
    gbtl(ctx, V0);
    rt::lw(ctx, V0, V0, 344);
    rt::lw(ctx, A0, V0, 2604);
    li(ctx, A1, 11);
    call(ctx, 0x2F24E8, &rg::fn_datCalcGetEffectState_00301750);
    s8_of(ctx, V0, V0);
    rt::slt(ctx, V0, ZR, V0);
}

void sub_2F2510(EEContext& ctx) {
    // (p): v = p +32; v < gBtl +2892 -> gBtl +2892 = v, return 0; else return v - gBtl +2892.
    guest::enter(ctx, 7);
    gbtl(ctx, V0);
    rt::addiu(ctx, A2, V0, 2892);
    rt::lw(ctx, A1, V0, 2892);
    rt::lw(ctx, V1, A0, 32);
    rt::slt(ctx, V0, V1, A1);
    if (!nz(ctx, V0)) {
        guest::charge(ctx, 3);
        rt::subu(ctx, V0, V1, A1);
    } else {
        guest::charge(ctx, 2);
        rt::sw(ctx, V1, A2, 0);
        move(ctx, V0, ZR);
    }
    guest::charge(ctx, 2);
}

void sub_2F4480(EEContext& ctx) {
    guest::enter(ctx, 3);
    move(ctx, V0, ZR);
}

void sub_2F5320(EEContext& ctx) {
    guest::enter(ctx, 4);
    gbtl(ctx, V0);
    rt::lw(ctx, V0, V0, 2904);
}

void btlBossResetCounters(EEContext& ctx) {
    // The boss counters' reset: gBtl +2896 = 0, +2900 = 40 (u16), +2902 = 0, +2904 = 0; returns 1.
    guest::enter(ctx, 12);
    gbtl(ctx, V0);
    rt::sw(ctx, ZR, V0, 2896);
    li(ctx, V1, 40);
    gbtl(ctx, V0);
    rt::sh(ctx, V1, V0, 2900);
    gbtl(ctx, V0);
    rt::sh(ctx, ZR, V0, 2902);
    gbtl(ctx, V0);
    rt::sh(ctx, ZR, V0, 2904);
    li(ctx, V0, 1);
}

void sub_2F6BF0(EEContext& ctx) {
    // (x): encounter 436 -> gBtl +2888 = 0, +2892 = x.
    guest::enter(ctx, 6);
    encounter_id(ctx, A2, V1, A1);
    li(ctx, V1, 436);
    if (!ne(ctx, A1, V1)) {
        guest::charge(ctx, 3);
        rt::sw(ctx, ZR, A2, 2888);
        gbtl(ctx, V1);
        rt::sw(ctx, A0, V1, 2892);
    }
    guest::charge(ctx, 2);
}

void sub_2F6C20(EEContext& ctx) { encounter_word(ctx, 436, 2888); }

void sub_2F8840(EEContext& ctx) {
    // (u16 k): gBtl +16 bit 4: the row k (20 bytes) of block (s16) gBtl +2948 (800 bytes each) of the table 0x699280
    // when its word 0 or word 1 is non-zero (the row's address), else 0; without the bit 0.
    guest::enter(ctx, 5);
    gbtl(ctx, V1);
    rt::lw(ctx, V0, V1, 16);
    rt::andi(ctx, V0, V0, 0x10u);
    if (!nz(ctx, V0)) {
        guest::charge(ctx, 3);
        move(ctx, V0, ZR);
        guest::charge(ctx, 2);
        return;
    }
    guest::charge(ctx, 17);
    rt::lh(ctx, V1, V1, 2948);
    rt::sll(ctx, V0, V1, 2);
    rt::addu(ctx, V1, V0, V1);
    rt::sll(ctx, V0, V1, 2);
    rt::addu(ctx, V0, V1, V0);
    rt::sll(ctx, V1, V0, 5);
    la(ctx, V0, 0x699280u);
    rt::addu(ctx, A1, V0, V1);
    u16_of(ctx, V1, A0);
    rt::sll(ctx, V0, V1, 2);
    rt::addu(ctx, V0, V0, V1);
    rt::sll(ctx, V0, V0, 2);
    rt::addu(ctx, V0, V0, A1);
    rt::lw(ctx, V1, V0, 0);
    if (eq(ctx, V1, ZR)) {
        guest::charge(ctx, 3);
        rt::lw(ctx, V1, V0, 4);
        if (eq(ctx, V1, ZR)) {
            guest::charge(ctx, 1);
            move(ctx, V0, ZR);
        }
    }
    guest::charge(ctx, 2);
}

void sub_2F8EA0(EEContext& ctx) {
    guest::enter(ctx, 3);
    move(ctx, V0, ZR);
}

void sub_2F8EB0(EEContext& ctx) {
    // (btlUnit u, (s16) skill): encounter 430: u is enemy 294: the skill's element (SKILL.TBL section 0, s8 at
    // 2 * skill; K_Assert skill < 464, line 417 of btlBossElizabeth.c) 0 / 1 / 2 -> 4 / 5 / 6, other -> -1; u another
    // unit -> -1 (all through the u16 -> s16 idiom); other encounters -> -1.
    guest::enter(ctx, 9);
    Frame frame(ctx, 1);
    encounter_id(ctx, V0, V0, V1);
    li(ctx, V0, 430);
    if (!eq(ctx, V1, V0)) {
        guest::charge(ctx, 2);
        guest::charge(ctx, 1);
        li(ctx, V0, -1);
        guest::charge(ctx, 5);
        return;
    }
    guest::charge(ctx, 4);
    rt::lbu(ctx, V1, A0, 162);
    li(ctx, V0, 1);
    if (!eq(ctx, V1, V0)) {
        guest::charge(ctx, 4);
        rt::ori(ctx, V0, ZR, 0xFFFFu);
        u16_of(ctx, V0, V0);
    } else {
        guest::charge(ctx, 4);
        rt::lhu(ctx, V1, A0, 164);
        li(ctx, V0, 294);
        if (!eq(ctx, V1, V0)) {
            guest::charge(ctx, 4);
            rt::ori(ctx, V0, ZR, 0xFFFFu);
            u16_of(ctx, V0, V0);
        } else {
            guest::charge(ctx, 5);
            s16_of(ctx, S0, A1);
            rt::slti(ctx, V0, S0, 464);
            if (!nz(ctx, V0)) {
                guest::charge(ctx, 5);
                la(ctx, A0, 0x69A4B0u);  // "btlBossElizabeth.c"
                li(ctx, A1, 417);
                call(ctx, 0x2F8F3C, &rg::fn_sub_19D3F0_0019d3f0);
            }
            guest::charge(ctx, 7);
            rt::sll(ctx, V1, S0, 1);
            rt::lw(ctx, V0, GP, kGpSkillElemTbl);
            rt::addu(ctx, V0, V0, V1);
            rt::lb(ctx, V1, V0, 0);
            li(ctx, V0, 2);
            if (eq(ctx, V1, V0)) {
                guest::charge(ctx, 3);
                rt::daddiu(ctx, V0, ZR, 6);
            } else {
                guest::charge(ctx, 3);
                li(ctx, V0, 1);
                if (eq(ctx, V1, V0)) {
                    guest::charge(ctx, 3);
                    rt::daddiu(ctx, V0, ZR, 5);
                } else {
                    guest::charge(ctx, 2);
                    if (eq(ctx, V1, ZR)) {
                        guest::charge(ctx, 3);
                        rt::daddiu(ctx, V0, ZR, 4);
                    } else {
                        guest::charge(ctx, 2);
                        guest::charge(ctx, 2);
                        rt::ori(ctx, V0, ZR, 0xFFFFu);
                        u16_of(ctx, V0, V0);
                    }
                }
            }
        }
    }
    guest::charge(ctx, 4);
    s16_of(ctx, V0, V0);
    guest::charge(ctx, 5);
}

void sub_2F9560(EEContext& ctx) {
    // (btlUnit u, u16* p): encounter 421 and u enemy 263: p[1] == 23 -> 0, else (gBtl +2884 ? 12 : -1);
    // encounter 424 and u enemy 269: p[1] == 25 -> 0; every other case -1.
    guest::enter(ctx, 6);
    encounter_id(ctx, T0, V0, A3);
    li(ctx, V0, 424);
    if (eq(ctx, A3, V0)) {
        guest::charge(ctx, 4);
        rt::lbu(ctx, V1, A0, 162);
        li(ctx, V0, 1);
        if (!eq(ctx, V1, V0)) {
            guest::charge(ctx, 3);
            li(ctx, V0, -1);
        } else {
            guest::charge(ctx, 4);
            rt::lhu(ctx, V1, A0, 164);
            li(ctx, V0, 269);
            if (!eq(ctx, V1, V0)) {
                guest::charge(ctx, 3);
                li(ctx, V0, -1);
            } else {
                guest::charge(ctx, 4);
                rt::lhu(ctx, V1, A1, 2);
                li(ctx, V0, 25);
                if (ne(ctx, V1, V0)) {
                    guest::charge(ctx, 1);
                    li(ctx, V0, -1);
                } else {
                    guest::charge(ctx, 3);
                    move(ctx, V0, ZR);
                }
            }
        }
        guest::charge(ctx, 2);
        guest::charge(ctx, 2);
        return;
    }
    guest::charge(ctx, 3);
    li(ctx, A2, 421);
    if (!eq(ctx, A3, A2)) {
        guest::charge(ctx, 2);
        guest::charge(ctx, 1);
        li(ctx, V0, -1);
        guest::charge(ctx, 2);
        return;
    }
    guest::charge(ctx, 4);
    rt::lbu(ctx, V1, A0, 162);
    li(ctx, V0, 1);
    if (!eq(ctx, V1, V0)) {
        guest::charge(ctx, 3);
        li(ctx, V0, -1);
    } else {
        guest::charge(ctx, 4);
        rt::lhu(ctx, V1, A0, 164);
        li(ctx, V0, 263);
        if (!eq(ctx, V1, V0)) {
            guest::charge(ctx, 3);
            li(ctx, V0, -1);
        } else {
            guest::charge(ctx, 4);
            rt::lhu(ctx, V1, A1, 2);
            li(ctx, V0, 23);
            if (!ne(ctx, V1, V0)) {
                guest::charge(ctx, 3);
                move(ctx, V0, ZR);
            } else {
                guest::charge(ctx, 2);
                if (!ne(ctx, A3, A2)) {
                    guest::charge(ctx, 3);
                    rt::lw(ctx, V0, T0, 2884);
                } else {
                    guest::charge(ctx, 1);
                    move(ctx, V0, ZR);
                }
                guest::charge(ctx, 2);
                if (eq(ctx, V0, ZR)) {
                    guest::charge(ctx, 1);
                    li(ctx, V0, -1);
                } else {
                    guest::charge(ctx, 3);
                    li(ctx, V0, 12);
                }
            }
        }
    }
    guest::charge(ctx, 2);
    guest::charge(ctx, 2);
}

void sub_2F9690(EEContext& ctx) {
    // (btlUnit u): encounters 431..435 and u an enemy -> 0, else -1.
    guest::enter(ctx, 6);
    encounter_id(ctx, V0, V0, V1);
    bool boss = false;
    for (s32 id = 435; id >= 431; --id) {
        if (id != 435) guest::charge(ctx, 3);
        li(ctx, V0, id);
        if (eq(ctx, V1, V0)) {
            boss = true;
            break;
        }
    }
    if (boss) {
        guest::charge(ctx, 4);
        rt::lbu(ctx, V1, A0, 162);
        li(ctx, V0, 1);
        if (!ne(ctx, V1, V0)) {
            guest::charge(ctx, 3);
            move(ctx, V0, ZR);
            guest::charge(ctx, 2);
            return;
        }
    } else {
        guest::charge(ctx, 2);
    }
    guest::charge(ctx, 1);
    li(ctx, V0, -1);
    guest::charge(ctx, 2);
}

void sub_2FC410(EEContext& ctx) {
    // (btlUnit u): encounter 424, u enemy 269 and gBtl +2900 == 1 -> 0x69A0E8; encounter 436, u enemy 241 and gBtl
    // +2888 == 1 -> 0x69A5A8 (two boss data records); else 0.
    guest::enter(ctx, 6);
    encounter_id(ctx, A3, V0, A2);
    li(ctx, A1, 436);
    if (eq(ctx, A2, A1)) {
        guest::charge(ctx, 4);
        rt::lbu(ctx, V1, A0, 162);
        li(ctx, V0, 1);
        if (!eq(ctx, V1, V0)) {
            guest::charge(ctx, 3);
            move(ctx, V0, ZR);
        } else {
            guest::charge(ctx, 4);
            rt::lhu(ctx, V1, A0, 164);
            li(ctx, V0, 241);
            if (!eq(ctx, V1, V0)) {
                guest::charge(ctx, 3);
                move(ctx, V0, ZR);
            } else {
                guest::charge(ctx, 2);
                if (!ne(ctx, A2, A1)) {
                    guest::charge(ctx, 3);
                    rt::lw(ctx, V1, A3, 2888);
                } else {
                    guest::charge(ctx, 1);
                    move(ctx, V1, ZR);
                }
                guest::charge(ctx, 3);
                li(ctx, V0, 1);
                if (!ne(ctx, V1, V0)) {
                    guest::charge(ctx, 4);
                    la(ctx, V0, 0x69A5A8u);
                } else {
                    guest::charge(ctx, 1);
                    move(ctx, V0, ZR);
                }
            }
        }
        guest::charge(ctx, 2);
        guest::charge(ctx, 2);
        return;
    }
    guest::charge(ctx, 3);
    li(ctx, V0, 424);
    if (!eq(ctx, A2, V0)) {
        guest::charge(ctx, 2);
        guest::charge(ctx, 1);
        move(ctx, V0, ZR);
        guest::charge(ctx, 2);
        return;
    }
    guest::charge(ctx, 4);
    rt::lbu(ctx, V0, A0, 162);
    li(ctx, A1, 1);
    if (!eq(ctx, V0, A1)) {
        guest::charge(ctx, 3);
        move(ctx, V0, ZR);
    } else {
        guest::charge(ctx, 4);
        rt::lhu(ctx, V1, A0, 164);
        li(ctx, V0, 269);
        if (!eq(ctx, V1, V0)) {
            guest::charge(ctx, 3);
            move(ctx, V0, ZR);
        } else {
            guest::charge(ctx, 3);
            rt::lw(ctx, V0, A3, 2900);
            if (!ne(ctx, V0, A1)) {
                guest::charge(ctx, 4);
                la(ctx, V0, 0x69A0E8u);
            } else {
                guest::charge(ctx, 1);
                move(ctx, V0, ZR);
            }
        }
    }
    guest::charge(ctx, 2);
    guest::charge(ctx, 2);
}

namespace {
// sub_2FCF50 / sub_2FD060, one encounter's half: (btlAction a) active (+26 bit 0) and its unit the enemy `enemy` ->
// gBtl[off] (gBtl in A1), else 0. `direct_miss`: the id test branches straight to the miss block (sub_2FD060)
// instead of through a 2-cycle jump (sub_2FCF50).
void active_enemy_word(EEContext& ctx, s32 enemy, s32 off, bool direct_miss) {
    guest::charge(ctx, 4);
    rt::lhu(ctx, V0, A0, 26);
    rt::andi(ctx, V0, V0, 0x1u);
    if (!nz(ctx, V0)) {
        guest::charge(ctx, 3);
        move(ctx, V0, ZR);
    } else {
        guest::charge(ctx, 5);
        rt::lw(ctx, A0, A0, 48);
        rt::lbu(ctx, V1, A0, 162);
        li(ctx, V0, 1);
        if (!eq(ctx, V1, V0)) {
            guest::charge(ctx, 3);
            move(ctx, V0, ZR);
        } else {
            guest::charge(ctx, 4);
            rt::lhu(ctx, V1, A0, 164);
            li(ctx, V0, enemy);
            if (eq(ctx, V1, V0)) {
                guest::charge(ctx, 3);
                rt::lw(ctx, V0, A1, off);
            } else {
                if (!direct_miss) guest::charge(ctx, 2);
                guest::charge(ctx, 1);
                move(ctx, V0, ZR);
            }
        }
    }
    guest::charge(ctx, 2);
}

// The two-encounter shape of sub_2FCF50 / sub_2FD060.
void boss_pair_word(EEContext& ctx, s32 enc_a, s32 enemy_a, s32 enc_b, s32 enemy_b, s32 off, bool direct_miss) {
    guest::enter(ctx, 6);
    encounter_id(ctx, A1, V0, V1);
    li(ctx, V0, enc_a);
    if (eq(ctx, V1, V0)) {
        active_enemy_word(ctx, enemy_a, off, direct_miss);
        guest::charge(ctx, 2);
        return;
    }
    guest::charge(ctx, 3);
    li(ctx, V0, enc_b);
    if (eq(ctx, V1, V0)) {
        active_enemy_word(ctx, enemy_b, off, direct_miss);
        guest::charge(ctx, 2);
        return;
    }
    guest::charge(ctx, 2);
    guest::charge(ctx, 1);
    move(ctx, V0, ZR);
    guest::charge(ctx, 2);
}
}  // namespace

void sub_2FCF50(EEContext& ctx) { boss_pair_word(ctx, 432, 234, 430, 294, 2896, false); }
void sub_2FD060(EEContext& ctx) { boss_pair_word(ctx, 436, 241, 429, 274, 2884, true); }

void sub_2FD500(EEContext& ctx) {
    guest::enter(ctx, 5);
    gbtl(ctx, V0);
    rt::lw(ctx, V0, V0, 2856);
    rt::sltu(ctx, V0, ZR, V0);
}

void sub_2FD7C0(EEContext& ctx) {
    // No setup block -> 0; encounter 429 or 456 -> 0; else 1.
    guest::enter(ctx, 4);
    gbtl(ctx, V0);
    rt::lw(ctx, V0, V0, 3004);
    if (!nz(ctx, V0)) {
        guest::charge(ctx, 3);
        move(ctx, V0, ZR);
        guest::charge(ctx, 2);
        return;
    }
    guest::charge(ctx, 4);
    rt::lhu(ctx, V1, V0, 8);
    li(ctx, V0, 429);
    bool hit = eq(ctx, V1, V0);
    if (!hit) {
        guest::charge(ctx, 3);
        li(ctx, V0, 456);
        hit = eq(ctx, V1, V0);
    }
    if (hit) {
        guest::charge(ctx, 3);
        move(ctx, V0, ZR);
    } else {
        guest::charge(ctx, 2);
        guest::charge(ctx, 1);
        li(ctx, V0, 1);
    }
    guest::charge(ctx, 2);
}

namespace {
// `lw v0, gBtl; lw v1, 12(v0); lui v0, 0x20; and v0, v1, v0`: gBtl +12 bit 21 in $v0.
void gbtl_bit21(EEContext& ctx) {
    gbtl(ctx, V0);
    rt::lw(ctx, V1, V0, 12);
    rt::lui(ctx, V0, 0x20u);
    rt::and_(ctx, V0, V1, V0);
}
void not_bit21(EEContext& ctx) {
    guest::enter(ctx, 8);
    gbtl_bit21(ctx);
    rt::sltu(ctx, V0, ZR, V0);
    rt::xori(ctx, V0, V0, 0x1u);
}
}  // namespace

void sub_2FDB70(EEContext& ctx) { not_bit21(ctx); }
void sub_2FDB90(EEContext& ctx) { not_bit21(ctx); }

void sub_2FDCB0(EEContext& ctx) {
    // (btlUnit u): gBtl +12 bit 21 ? u is an enemy : 0.
    guest::enter(ctx, 6);
    gbtl_bit21(ctx);
    if (!nz(ctx, V0)) {
        guest::charge(ctx, 3);
        move(ctx, V0, ZR);
    } else {
        guest::charge(ctx, 3);
        rt::lbu(ctx, V0, A0, 162);
        rt::xori(ctx, V0, V0, 0x1u);
        rt::sltiu(ctx, V0, V0, 1);
    }
    guest::charge(ctx, 2);
}

void sub_2FDCF0(EEContext& ctx) {
    // (btlUnit u, v): gBtl +12 bit 21 and u and v both enemies -> 0, else 1.
    guest::enter(ctx, 6);
    gbtl_bit21(ctx);
    bool both = false;
    if (nz(ctx, V0)) {
        guest::charge(ctx, 4);
        rt::lbu(ctx, V1, A0, 162);
        li(ctx, V0, 1);
        if (!ne(ctx, V1, V0)) {
            guest::charge(ctx, 3);
            rt::lbu(ctx, V0, A1, 162);
            both = !ne(ctx, V1, V0);
        }
    }
    if (both) {
        guest::charge(ctx, 3);
        move(ctx, V0, ZR);
    } else {
        guest::charge(ctx, 1);
        li(ctx, V0, 1);
    }
    guest::charge(ctx, 2);
}

void sub_2FDD40(EEContext& ctx) {
    // (btlUnit u, v): gBtl +12 bit 21, u not an enemy and u != v -> u and v on the same side; else 0.
    guest::enter(ctx, 6);
    gbtl_bit21(ctx);
    if (!nz(ctx, V0)) {
        guest::charge(ctx, 3);
        move(ctx, V0, ZR);
    } else {
        guest::charge(ctx, 4);
        rt::lbu(ctx, V1, A0, 162);
        li(ctx, V0, 1);
        if (!ne(ctx, V1, V0)) {
            guest::charge(ctx, 3);
            move(ctx, V0, ZR);
        } else {
            guest::charge(ctx, 2);
            if (!ne(ctx, A0, A1)) {
                guest::charge(ctx, 3);
                move(ctx, V0, ZR);
            } else {
                guest::charge(ctx, 3);
                rt::lbu(ctx, V0, A1, 162);
                rt::xor_(ctx, V0, V1, V0);
                rt::sltiu(ctx, V0, V0, 1);
            }
        }
    }
    guest::charge(ctx, 2);
}

void sub_2FDED0(EEContext& ctx) {
    // ((s16) id): encounter 436 only: gBtl +2908 = id for 294 / 296 / 295 / 293, else -1; then 296 / 295 / 293 return
    // the address of btlBossResetCounters (a callback for the caller), other ids 0; other encounters 0.
    guest::enter(ctx, 6);
    encounter_id(ctx, A1, V0, V1);
    li(ctx, V0, 436);
    if (!eq(ctx, V1, V0)) {
        guest::charge(ctx, 2);
        guest::charge(ctx, 1);
        move(ctx, V0, ZR);
        guest::charge(ctx, 2);
        return;
    }
    guest::charge(ctx, 5);
    s16_of(ctx, V1, A0);
    static constexpr s32 kStore[] = {294, 296, 295, 293};
    bool known = false;
    for (std::size_t i = 0; i < std::size(kStore); ++i) {
        if (i != 0) guest::charge(ctx, 3);
        li(ctx, V0, kStore[i]);
        if (eq(ctx, V1, V0)) {
            known = true;
            break;
        }
    }
    if (known) {
        guest::charge(ctx, 3);
        rt::sw(ctx, V1, A1, 2908);
    } else {
        guest::charge(ctx, 2);
        guest::charge(ctx, 2);
        li(ctx, V0, -1);
        rt::sw(ctx, V0, A1, 2908);
    }
    static constexpr s32 kCallback[] = {296, 295, 293};
    bool callback = false;
    for (std::size_t i = 0; i < std::size(kCallback); ++i) {
        guest::charge(ctx, 3);
        li(ctx, V0, kCallback[i]);
        if (eq(ctx, V1, V0)) {
            callback = true;
            break;
        }
    }
    if (callback) {
        guest::charge(ctx, 4);
        la(ctx, V0, 0x2F6BC0u);
    } else {
        guest::charge(ctx, 2);
        guest::charge(ctx, 1);
        move(ctx, V0, ZR);
    }
    guest::charge(ctx, 2);
    guest::charge(ctx, 2);
}

void sub_2FDFA0(EEContext& ctx) {
    // Encounter 436 -> 0, else 1.
    guest::enter(ctx, 6);
    encounter_id(ctx, V0, V0, V1);
    li(ctx, V0, 436);
    if (eq(ctx, V1, V0)) {
        guest::charge(ctx, 3);
        move(ctx, V0, ZR);
    } else {
        guest::charge(ctx, 2);
        guest::charge(ctx, 1);
        li(ctx, V0, 1);
    }
    guest::charge(ctx, 2);
}

void nullsub_52(EEContext& ctx) { guest::enter(ctx, 2); }
void nullsub_53(EEContext& ctx) { guest::enter(ctx, 2); }

}  // namespace p3fes::game

// --- the recompiled program's entry points (signatures from recomp/generated/functions.h) ---------------------------
namespace p3fes::recomp_gen {

#define P3FES_BATTLE_CALC2_SHIM(name, addr8) \
    void fn_##name##_##addr8(p3fes::EEContext& ctx) { p3fes::game::name(ctx); }
P3FES_BATTLE_CALC2_FUNCS(P3FES_BATTLE_CALC2_SHIM)
#undef P3FES_BATTLE_CALC2_SHIM

}  // namespace p3fes::recomp_gen
