// The battle-AI script command handlers (game/include/p3fes/game/comm_ai.h), hand-decompiled from SLUS_216.21
// (docs/ANALYSIS/18_script_vm.md section 2.4, 21_battle.md sections 1.3 and 3.2). tests/game/test_comm_ai.cpp runs
// each against its __recomp body.
//
// Shape. 108 of the 120 handlers are seven templates over the two AI tables (a condition query, a fixed condition, a
// target choice with or without a parameter, a command code, a condition about an ally, a fixed condition about an
// ally); the header's X-macro lists give each instance its table row. The twelve others are written out below.
//
// Virtual time (ADR-0013): guest::enter / charge follow the `ctx.cycles += N` blocks of the generated bodies
// (recomp/generated/fn_0020_002c2740_002cc700.cpp and the next file); a block is charged at its start, before the
// calls it contains. None of these bodies has a loop, so the only check point is the entry one.
//
// Register discipline (wave 7: the kernel saves the whole register file in guest memory when a check point
// preempts, and every callee here -- the AI table functions above all, run through `jalr` -- reaches check points):
//   * Frame performs the original prologue / epilogue (`addiu sp; sd ra; sq sN` ... `ld ra; lq sN; addiu sp`), so
//     the spill slots hold the original bytes and every callee's frame lands where it did;
//   * every call -- jal or jalr -- sets $ra to the original link (rt::jal / rt::jalr at the call's address) and runs
//     the callee through its generated entry point (the table calls through rt::lookup_func, as the jalr did);
//   * between two calls the handler writes exactly the GPRs the original writes, with the original 64-bit values,
//     in $v0/$v1/$a0..$a3/$t0..$t3/$s0..$s2 (the query word's halves, the table offsets 12k / 8k, the side mask);
//     registers the original leaves alone keep what the last callee left. After the last call: $v0 = 1 and the
//     epilogue, as in the original. No handler touches HI/LO or the FPU.
// CodeFunc_Comm reads $v0 alone, but the register file at every check point inside the callees and at the return
// is the original's, so a preemption anywhere below these handlers saves the original bytes.
#include "p3fes/game/comm_ai.h"

#include "p3fes/ee/core.h"
#include "p3fes/game/guest.h"

namespace p3fes::recomp_gen {
// already replaced (game/src/script/script_ops.cpp, battle_*.cpp); the symbol reaches whichever body is live
void fn_scrGetIntPara_0035ed20(p3fes::EEContext&);
void fn_scrSetIntReturnVal_0035f060(p3fes::EEContext&);
void fn_scrGetUserData_0035f160(p3fes::EEContext&);
void fn_sub_29A210_0029a210(p3fes::EEContext&);    // [btlActionFindById] (id)
void fn_sub_30BC20_0030bc20(p3fes::EEContext&);    // (item) -> u16 +8 of the item record
void fn_sub_301CA0_00301ca0(p3fes::EEContext&);    // [datCalcCheckEffectMask] (unit, mask)
void fn_sub_301870_00301870(p3fes::EEContext&);    // (unit): unit +0x18 = 0
void fn_datCalcDamage_00303130(p3fes::EEContext&); // eight arguments, $t0..$t3
void fn_datCalcGetHp_002ffd70(p3fes::EEContext&);  // (unit)
// still recompiled (btlAICommand.c)
void fn_sub_2C6A00_002c6a00(p3fes::EEContext&);    // [btlAISetCommand] (action, action + 56, code)
void fn_sub_2C0E30_002c0e30(p3fes::EEContext&);    // [btlAIFindUnit] (id, side mask, excluded status) -> action
void fn_sub_2C6BA0_002c6ba0(p3fes::EEContext&);    // (action): the index of the first AICALC row whose conditions hold
void fn_sub_2C6E30_002c6e30(p3fes::EEContext&);    // (action, index) -> the AICALC row
void fn_sub_2C08B0_002c08b0(p3fes::EEContext&);    // (dst, src): copy a target record
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {

namespace rg = recomp_gen;
using namespace comm_ai;
using guest::Fn;

// --- registers ------------------------------------------------------------------------------------------------
constexpr unsigned kV0 = GPR_V0, kV1 = GPR_V0 + 1, kA0 = GPR_A0, kA1 = GPR_A1, kA2 = GPR_A2, kA3 = GPR_A3;
constexpr unsigned kT0 = GPR_T0, kT1 = GPR_T0 + 1, kT2 = GPR_T0 + 2, kT3 = GPR_T0 + 3;
constexpr unsigned kS0 = GPR_S0, kS1 = GPR_S0 + 1, kS2 = GPR_S0 + 2;

u64 R(const EEContext& ctx, unsigned r) { return ee::core::gpr64(ctx, r); }
void S(EEContext& ctx, unsigned r, u64 v) { ee::core::set_gpr64(ctx, r, v); }
u64 sx(u32 v) { return ee::core::sext32(v); }
u64 add32i(u64 base, s32 off) { return ee::core::add32i(base, off); }  // addiu
u64 lui(u32 imm) { return ee::core::lui(imm); }
u64 low24(u64 v) { return v & 0xFFFFFFu; }   // dsll32 x, 8 / dsrl32 x, 8
u64 low28(u64 v) { return v & 0xFFFFFFFu; }  // dsll32 x, 4 / dsrl32 x, 4
constexpr u32 kKindHi = 0xFF00u;             // lui x, 0xFF00: the kind-byte mask
u64 srl24(u64 v) { return sx(static_cast<u32>(v) >> 24); }
u64 bit(u64 n) { return sx(1u << (static_cast<u32>(n) & 31u)); }  // sllv x, (1), n

// Guest loads at `base + off` (base a register value, the address computed as addiu does).
u64 lw(const EEContext& ctx, u64 base, s32 off) { return sx(guest::load<u32>(ctx, static_cast<u32>(add32i(base, off)))); }
u64 lhu(const EEContext& ctx, u64 base, s32 off) { return guest::load<u16>(ctx, static_cast<u32>(add32i(base, off))); }
u64 lbu(const EEContext& ctx, u64 base, s32 off) { return guest::load<u8>(ctx, static_cast<u32>(add32i(base, off))); }
void sh(EEContext& ctx, u64 base, s32 off, u64 v) {
    guest::store<u16>(ctx, static_cast<u32>(add32i(base, off)), static_cast<u16>(v));
}

// `jal fn` at `pc` ($ra = pc + 8), the callee through its generated symbol; returns $v0.
u64 jal(EEContext& ctx, u32 pc, Fn fn) {
    rt::jal(ctx, pc);
    fn(ctx);
    return R(ctx, kV0);
}
// `jalr target` at `pc` ($ra = pc + 8), as the recompiled body dispatches it; returns $v0.
u64 jalr(EEContext& ctx, u32 pc, u64 target) {
    rt::jalr(ctx, GPR_RA, pc);
    rt::lookup_func(static_cast<u32>(target))(ctx);
    return R(ctx, kV0);
}

// The original frame of `size` bytes, s0.. at 16 * k and $ra after them (every handler here).
class Frame {
public:
    Frame(EEContext& ctx, s32 size, unsigned saved) noexcept : ctx_(ctx), size_(size), saved_(saved) {
        rt::addiu(ctx_, GPR_SP, GPR_SP, -size_);
        rt::sd(ctx_, GPR_RA, GPR_SP, static_cast<s32>(16 * saved_));
        for (unsigned k = saved_; k-- > 0;) rt::sq(ctx_, GPR_S0 + k, GPR_SP, static_cast<s32>(16 * k));
    }
    ~Frame() {
        rt::ld(ctx_, GPR_RA, GPR_SP, static_cast<s32>(16 * saved_));
        for (unsigned k = saved_; k-- > 0;) rt::lq(ctx_, GPR_S0 + k, GPR_SP, static_cast<s32>(16 * k));
        rt::addiu(ctx_, GPR_SP, GPR_SP, size_);
    }
    Frame(const Frame&) = delete;
    Frame& operator=(const Frame&) = delete;

private:
    EEContext& ctx_;
    s32 size_;
    unsigned saved_;
};

// --- the script side -------------------------------------------------------------------------------------------
u64 int_para(EEContext& ctx, u32 pc, u64 i) {
    S(ctx, kA0, i);
    return jal(ctx, pc, &rg::fn_scrGetIntPara_0035ed20);
}
u64 user_data(EEContext& ctx, u32 pc) { return jal(ctx, pc, &rg::fn_scrGetUserData_0035f160); }
// `sltu a0, zero, v0; jal scrSetIntReturnVal`: the script sees `result != 0`.
void return_bool(EEContext& ctx, u32 pc, u64 result) {
    S(ctx, kA0, result != 0 ? 1u : 0u);
    jal(ctx, pc, &rg::fn_scrSetIntReturnVal_0035f060);
}

// --- the AI tables ---------------------------------------------------------------------------------------------
// A query word: `lui v0, kind << 8; or dst, v1 (= param & 0xFFFFFF), v0`. The or is 64-bit.
u64 make_query(EEContext& ctx, u64 param, u32 kind, unsigned dst) {
    S(ctx, kV1, low24(param));
    S(ctx, kV0, lui(kind << 8));
    S(ctx, dst, R(ctx, kV1) | R(ctx, kV0));
    return R(ctx, dst);
}

// The condition row of a kind held in a register: `sll v0, k, 1; addu v0, v0, k; sll v1, v0, 2; lui/addiu v0,
// kCondTable; addu v0, v0, v1; lw v0, 0(v0); jalr v0` at `pc`. $a0/$a1 are set by the caller.
u64 ask_by_kind(EEContext& ctx, u32 pc, u64 k) {
    S(ctx, kV0, sx((static_cast<u32>(k) << 1) + static_cast<u32>(k)));
    S(ctx, kV1, sx(static_cast<u32>(R(ctx, kV0)) << 2));
    S(ctx, kV0, lw(ctx, sx(kCondTable + static_cast<u32>(R(ctx, kV1))), 0));
    return jalr(ctx, pc, R(ctx, kV0));
}
// A fixed condition row: `move a0, unit; move a1, zero; lui v0, 0x69; lw v0, row(v0); jalr v0` at `pc`.
u64 ask_fixed_row(EEContext& ctx, u32 pc, u64 unit, u32 kind) {
    S(ctx, kA0, unit);
    S(ctx, kA1, 0);
    S(ctx, kV0, lw(ctx, 0, static_cast<s32>(kCondTable + kCondRow * kind)));
    return jalr(ctx, pc, R(ctx, kV0));
}
// The target row of a kind held in a register: `sll v1, k, 3; lui/addiu v0, kTargetTable; addu v0, v0, v1;
// lw v0, 0(v0); jalr v0` at `pc`. $a0/$a1 are set by the caller.
u64 target_by_kind(EEContext& ctx, u32 pc, u64 k) {
    S(ctx, kV1, sx(static_cast<u32>(k) << 3));
    S(ctx, kV0, lw(ctx, sx(kTargetTable + static_cast<u32>(R(ctx, kV1))), 0));
    return jalr(ctx, pc, R(ctx, kV0));
}
// A fixed target row with param 0 at `pc`.
u64 target_fixed_row(EEContext& ctx, u32 pc, u64 action, u32 kind) {
    S(ctx, kA0, action);
    S(ctx, kA1, 0);
    S(ctx, kV0, lw(ctx, 0, static_cast<s32>(kTargetTable + kTargetRow * kind)));
    return jalr(ctx, pc, R(ctx, kV0));
}
// The fallback every selecting handler shares: when the chosen selector found nothing, a 6-cycle block calls the
// default selector (row 0, AI) at `pc`.
void target_or_default(EEContext& ctx, u64 chosen, u32 pc, u64 action) {
    if (chosen != 0) return;
    guest::charge(ctx, 6);
    target_fixed_row(ctx, pc, action, 0);
}

// The unit finder of the ally handlers: `andi a0, id, 0xFFFF; lw v0, 48(me); lbu v1, 162(v0); v0 = 1 << v1;
// andi a1, v0, 0xFFFF; a2 = exclude; jal sub_2C0E30` at `pc`: the action of the unit with that id on the acting
// unit's side, skipping units with a status of `exclude` (dead ones for 0x80000). Returns it, or 0.
u64 find_ally(EEContext& ctx, u32 pc, u64 me, u64 id, u64 exclude) {
    S(ctx, kA0, id & 0xFFFFu);
    S(ctx, kV0, lw(ctx, me, kActUnit));
    S(ctx, kV1, lbu(ctx, R(ctx, kV0), kUnitSide));
    S(ctx, kV0, bit(R(ctx, kV1)));
    S(ctx, kA1, R(ctx, kV0) & 0xFFFFu);
    S(ctx, kA2, exclude);
    return jal(ctx, pc, &rg::fn_sub_2C0E30_002c0e30);
}

// The kind register of a query word whose param half comes from `param` and kind from `kind_reg` (`lui kind_reg;
// or a0, low24(param), kind_reg; and v, a0, 0xFFFFFFFFFF000000; srl k, v, 24; or v1, param, kind_reg; a1 =
// low24(v1)`), the shape of sub_2C9BA0 and sub_2CDF40. Returns the kind; leaves $a0, $a1, $v1 and `k_reg` as the
// original does.
u64 split_query(EEContext& ctx, u64 param, u32 kind, unsigned k_reg) {
    S(ctx, kV1, low24(param));
    S(ctx, kA1, lui(kind << 8));
    S(ctx, kA0, R(ctx, kV1) | R(ctx, kA1));
    S(ctx, kV1, R(ctx, kA0) & lui(kKindHi));
    S(ctx, k_reg, srl24(R(ctx, kV1)));
    S(ctx, kV1, param | R(ctx, kA1));
    S(ctx, kA1, low24(R(ctx, kV1)));
    return R(ctx, k_reg);
}

// --- the templates ---------------------------------------------------------------------------------------------

// ASK [argc 1]: frame 32 (s0). 19: scrGetIntPara(0) at +0x10, s0 = the query word, scrGetUserData at +0x28, the kind
// byte back out of s0 -> nonzero: 10, condition(action, param) through the table at +0x78; zero: 3, result 0. Then
// 9: scrSetIntReturnVal(result != 0) at +0x84.
u32 ask(EEContext& ctx, u32 base, u32 kind) {
    guest::enter(ctx, 19);
    Frame frame(ctx, 32, 1);
    const u64 query = make_query(ctx, int_para(ctx, base + 0x10, 0), kind, kS0);
    const u64 action = user_data(ctx, base + 0x28);
    S(ctx, kV1, srl24(query & lui(kKindHi)));
    S(ctx, kA1, low24(query));
    u64 result = 0;
    if (R(ctx, kV1) != 0) {
        guest::charge(ctx, 10);
        S(ctx, kA0, action);
        result = ask_by_kind(ctx, base + 0x78, R(ctx, kV1));
    } else {
        guest::charge(ctx, 3);
        S(ctx, kV0, 0);
    }
    guest::charge(ctx, 9);
    return_bool(ctx, base + 0x84, result);
    S(ctx, kV0, 1);
    return 1;
}

// ASK_FIXED [argc 0]: frame 16. One block of 18: scrGetUserData at +0x8, condition(action, 0) at +0x20,
// scrSetIntReturnVal(result != 0) at +0x2C.
u32 ask_fixed(EEContext& ctx, u32 base, u32 kind) {
    guest::enter(ctx, 18);
    Frame frame(ctx, 16, 0);
    const u64 action = user_data(ctx, base + 0x8);
    return_bool(ctx, base + 0x2C, ask_fixed_row(ctx, base + 0x20, action, kind));
    S(ctx, kV0, 1);
    return 1;
}

// TARGET_FIXED [argc 0]: frame 32 (s0 = action). 14: scrGetUserData at +0xC, selector(action, 0) at +0x28; nothing
// chosen -> 6: AI at +0x48. Then 6.
u32 target_fixed(EEContext& ctx, u32 base, u32 kind) {
    guest::enter(ctx, 14);
    Frame frame(ctx, 32, 1);
    S(ctx, kS0, user_data(ctx, base + 0xC));
    const u64 action = R(ctx, kS0);
    target_or_default(ctx, target_fixed_row(ctx, base + 0x28, action, kind), base + 0x48, action);
    guest::charge(ctx, 6);
    S(ctx, kV0, 1);
    return 1;
}

// TARGET [argc 1]: frame 48 (s0 = action, s1 = the query word). 29: scrGetIntPara(0) at +0x14, scrGetUserData at
// +0x2C, selector(action, param) through the table at +0x64; nothing chosen -> 6: AI at +0x84. Then 7.
u32 target(EEContext& ctx, u32 base, u32 kind) {
    guest::enter(ctx, 29);
    Frame frame(ctx, 48, 2);
    const u64 query = make_query(ctx, int_para(ctx, base + 0x14, 0), kind, kS1);
    S(ctx, kS0, user_data(ctx, base + 0x2C));
    const u64 action = R(ctx, kS0);
    S(ctx, kA1, low24(query));
    S(ctx, kA0, action);
    S(ctx, kV0, srl24(query & lui(kKindHi)));
    target_or_default(ctx, target_by_kind(ctx, base + 0x64, R(ctx, kV0)), base + 0x84, action);
    guest::charge(ctx, 7);
    S(ctx, kV0, 1);
    return 1;
}

// sub_2C6A00(action, action + 56, code) at `pc`.
void set_command(EEContext& ctx, u32 pc, u64 action, u64 code) {
    S(ctx, kA0, action);
    S(ctx, kA1, add32i(action, kActCommandRec));
    S(ctx, kA2, code);
    jal(ctx, pc, &rg::fn_sub_2C6A00_002c6a00);
}

// COMMAND [argc 0]: frame 16. One block of 14: scrGetUserData at +0x8, sub_2C6A00(action, action + 56, code) at
// +0x1C.
u32 command(EEContext& ctx, u32 base, u32 code) {
    guest::enter(ctx, 14);
    Frame frame(ctx, 16, 0);
    set_command(ctx, base + 0x1C, user_data(ctx, base + 0x8), code);
    S(ctx, kV0, 1);
    return 1;
}

// ASK_ALLY [argc 2]: frame 32 (s0 = action, then the ally). 21: scrGetUserData at +0xC, scrGetIntPara(0) at +0x1C,
// the ally at +0x40 -> none: 1, result 0; found: 14: scrGetIntPara(1) at +0x58, the query in $a0, kind nonzero ->
// 10: condition(ally, param) at +0xB8 (zero -> 3: result 0); 2. Then 9: scrSetIntReturnVal(result != 0) at +0xD0.
u32 ask_ally(EEContext& ctx, u32 base, u32 kind) {
    guest::enter(ctx, 21);
    Frame frame(ctx, 32, 1);
    S(ctx, kS0, user_data(ctx, base + 0xC));
    const u64 id = int_para(ctx, base + 0x1C, 0);
    S(ctx, kS0, find_ally(ctx, base + 0x40, R(ctx, kS0), id, kStatusDead));
    const u64 ally = R(ctx, kS0);
    u64 result = 0;
    if (ally == 0) {
        guest::charge(ctx, 1);
        S(ctx, kV0, 0);
    } else {
        guest::charge(ctx, 14);
        const u64 query = make_query(ctx, int_para(ctx, base + 0x58, 1), kind, kA0);
        S(ctx, kV0, query & lui(kKindHi));
        S(ctx, kV1, srl24(R(ctx, kV0)));
        S(ctx, kA1, low24(query));
        if (R(ctx, kV1) != 0) {
            guest::charge(ctx, 10);
            S(ctx, kA0, ally);
            result = ask_by_kind(ctx, base + 0xB8, R(ctx, kV1));
        } else {
            guest::charge(ctx, 3);
            S(ctx, kV0, 0);
        }
        guest::charge(ctx, 2);
    }
    guest::charge(ctx, 9);
    return_bool(ctx, base + 0xD0, result);
    S(ctx, kV0, 1);
    return 1;
}

// ALLY_FIXED [argc 1]: frame 32 (s0 = action). 20: scrGetUserData at +0xC, scrGetIntPara(0) at +0x1C, the ally at
// +0x40 -> none: 1, result 0; found: 8: condition(ally, 0) at +0x60. Then 9: scrSetIntReturnVal at +0x78.
u32 ally_fixed(EEContext& ctx, u32 base, u32 kind) {
    guest::enter(ctx, 20);
    Frame frame(ctx, 32, 1);
    S(ctx, kS0, user_data(ctx, base + 0xC));
    const u64 id = int_para(ctx, base + 0x1C, 0);
    const u64 ally = find_ally(ctx, base + 0x40, R(ctx, kS0), id, kStatusDead);
    u64 result = 0;
    if (ally == 0) {
        guest::charge(ctx, 1);
        S(ctx, kV0, 0);
    } else {
        guest::charge(ctx, 8);
        result = ask_fixed_row(ctx, base + 0x60, ally, kind);
    }
    guest::charge(ctx, 9);
    return_bool(ctx, base + 0x78, result);
    S(ctx, kV0, 1);
    return 1;
}

// sub_2C7540 / sub_2C75D0: frame 32 (s0 = action). command 9 / skill 341 stored, the arguments at +118 (+120), then
// target MYAI (row 8) with param 0, else AI. `pc_ai` is the MYAI jalr; the AI fallback follows 0x20 later.
u32 skill341(EEContext& ctx, u32 base, u32 first, bool two_args, u32 pc_ai) {
    guest::enter(ctx, first);
    Frame frame(ctx, 32, 1);
    S(ctx, kS0, user_data(ctx, base + 0xC));
    const u64 action = R(ctx, kS0);
    S(ctx, kV1, kSkill341Command);
    sh(ctx, action, kActCommand, R(ctx, kV1));
    S(ctx, kV1, kSkill341);
    sh(ctx, action, kActSkill, R(ctx, kV1));
    sh(ctx, action, kActArg0, int_para(ctx, base + 0x2C, 0));
    if (two_args) sh(ctx, action, kActArg1, int_para(ctx, base + 0x3C, 1));
    target_or_default(ctx, target_fixed_row(ctx, pc_ai, action, 8), pc_ai + 0x20, action);
    guest::charge(ctx, 6);
    S(ctx, kV0, 1);
    return 1;
}

}  // namespace

// --- the template instances ------------------------------------------------------------------------------------
#define P3FES_COMM_AI_ASK_DEF(name, addr8, index, k) \
    u32 name(EEContext& ctx) { return ask(ctx, 0x##addr8, k); }
#define P3FES_COMM_AI_ASK_FIXED_DEF(name, addr8, index, k) \
    u32 name(EEContext& ctx) { return ask_fixed(ctx, 0x##addr8, k); }
#define P3FES_COMM_AI_TARGET_FIXED_DEF(name, addr8, index, k) \
    u32 name(EEContext& ctx) { return target_fixed(ctx, 0x##addr8, k); }
#define P3FES_COMM_AI_TARGET_DEF(name, addr8, index, k) \
    u32 name(EEContext& ctx) { return target(ctx, 0x##addr8, k); }
#define P3FES_COMM_AI_COMMAND_DEF(name, addr8, index, k) \
    u32 name(EEContext& ctx) { return command(ctx, 0x##addr8, k); }
#define P3FES_COMM_AI_ASK_ALLY_DEF(name, addr8, index, k) \
    u32 name(EEContext& ctx) { return ask_ally(ctx, 0x##addr8, k); }
#define P3FES_COMM_AI_ALLY_FIXED_DEF(name, addr8, index, k) \
    u32 name(EEContext& ctx) { return ally_fixed(ctx, 0x##addr8, k); }
P3FES_COMM_AI_ASK(P3FES_COMM_AI_ASK_DEF)
P3FES_COMM_AI_ASK_FIXED(P3FES_COMM_AI_ASK_FIXED_DEF)
P3FES_COMM_AI_TARGET_FIXED(P3FES_COMM_AI_TARGET_FIXED_DEF)
P3FES_COMM_AI_TARGET(P3FES_COMM_AI_TARGET_DEF)
P3FES_COMM_AI_COMMAND(P3FES_COMM_AI_COMMAND_DEF)
P3FES_COMM_AI_ASK_ALLY(P3FES_COMM_AI_ASK_ALLY_DEF)
P3FES_COMM_AI_ALLY_FIXED(P3FES_COMM_AI_ALLY_FIXED_DEF)
#undef P3FES_COMM_AI_ASK_DEF
#undef P3FES_COMM_AI_ASK_FIXED_DEF
#undef P3FES_COMM_AI_TARGET_FIXED_DEF
#undef P3FES_COMM_AI_TARGET_DEF
#undef P3FES_COMM_AI_COMMAND_DEF
#undef P3FES_COMM_AI_ASK_ALLY_DEF
#undef P3FES_COMM_AI_ALLY_FIXED_DEF

// --- the handlers of their own shape ---------------------------------------------------------------------------

// [113] frame 32 (s0 = action). 11: scrGetUserData, scrGetIntPara(0) -> 0: 7, attack; else 2 -> > 0: 7, skill
// (u16)arg0; <= 0: 5, command 7. Then 6.
u32 sub_2C7340(EEContext& ctx) {
    constexpr u32 base = 0x2C7340;
    guest::enter(ctx, 11);
    Frame frame(ctx, 32, 1);
    S(ctx, kS0, user_data(ctx, base + 0xC));
    const u64 action = R(ctx, kS0);
    const u64 arg = int_para(ctx, base + 0x1C, 0);
    if (arg == 0) {
        guest::charge(ctx, 7);
        set_command(ctx, base + 0x38, action, kCmdAttack);
    } else {
        guest::charge(ctx, 2);
        if (static_cast<s64>(arg) > 0) {
            guest::charge(ctx, 7);
            set_command(ctx, base + 0x5C, action, arg & 0xFFFFu);
        } else {
            guest::charge(ctx, 5);
            set_command(ctx, base + 0x78, action, kCmdKind7);
        }
    }
    guest::charge(ctx, 6);
    S(ctx, kV0, 1);
    return 1;
}

u32 sub_2C7540(EEContext& ctx) { return skill341(ctx, 0x2C7540, 22, false, 0x2C7588); }  // [116]
u32 sub_2C75D0(EEContext& ctx) { return skill341(ctx, 0x2C75D0, 26, true, 0x2C7628); }   // [165]

// [117] frame 48 (s0 = action, s1 = the row). One block of 36: the row index (sub_2C6BA0), the row (sub_2C6E30),
// the command of row +2, the target query of row +4 through the table at +0x80; nothing chosen -> 6: AI at +0xA0.
// Then 7.
u32 sub_2D13C0(EEContext& ctx) {
    constexpr u32 base = 0x2D13C0;
    guest::enter(ctx, 36);
    Frame frame(ctx, 48, 2);
    S(ctx, kS0, user_data(ctx, base + 0x10));
    const u64 action = R(ctx, kS0);
    S(ctx, kA0, action);
    const u64 index = jal(ctx, base + 0x20, &rg::fn_sub_2C6BA0_002c6ba0);
    S(ctx, kA1, index & 0xFFFFu);
    S(ctx, kA0, action);
    S(ctx, kS1, jal(ctx, base + 0x30, &rg::fn_sub_2C6E30_002c6e30));
    const u64 row = R(ctx, kS1);
    S(ctx, kA0, action);
    S(ctx, kA1, add32i(action, kActCommandRec));
    S(ctx, kA2, lhu(ctx, row, 2));
    jal(ctx, base + 0x48, &rg::fn_sub_2C6A00_002c6a00);
    S(ctx, kV1, lw(ctx, row, 4));
    const u64 query = R(ctx, kV1);
    S(ctx, kA1, low24(query));
    S(ctx, kA0, action);
    S(ctx, kV0, srl24(query & lui(kKindHi)));
    target_or_default(ctx, target_by_kind(ctx, base + 0x80, R(ctx, kV0)), base + 0xA0, action);
    guest::charge(ctx, 7);
    S(ctx, kV0, 1);
    return 1;
}

// [170] frame 48 (s0 = the status bits arg1, s1 = the side mask). 19: scrGetIntPara(1), scrGetUserData, the side
// mask; bit 19 of arg1 set -> 10: the ally including the dead (exclude 0); else 8: the living ally. 2: none -> 1,
// result 0; found -> 12: query MYBAD (kind 11) with param = arg1, kind nonzero -> 10: condition(ally, param) (zero
// -> 3); 2. Then 10: scrSetIntReturnVal(result != 0).
u32 sub_2C9BA0(EEContext& ctx) {
    constexpr u32 base = 0x2C9BA0;
    guest::enter(ctx, 19);
    Frame frame(ctx, 48, 2);
    S(ctx, kS0, int_para(ctx, base + 0x14, 1));
    const u64 bits = R(ctx, kS0);
    const u64 me = user_data(ctx, base + 0x20);
    S(ctx, kV0, lw(ctx, me, kActUnit));
    S(ctx, kV1, lbu(ctx, R(ctx, kV0), kUnitSide));
    S(ctx, kV0, bit(R(ctx, kV1)));
    S(ctx, kS1, R(ctx, kV0) & 0xFFFFu);
    S(ctx, kV0, bits & lui(0x8u));
    u64 ally;
    if (R(ctx, kV0) != 0) {
        guest::charge(ctx, 10);
        S(ctx, kA0, int_para(ctx, base + 0x50, 0) & 0xFFFFu);
        S(ctx, kA1, R(ctx, kS1));
        S(ctx, kA2, 0);
        ally = jal(ctx, base + 0x64, &rg::fn_sub_2C0E30_002c0e30);
    } else {
        guest::charge(ctx, 8);
        S(ctx, kA0, int_para(ctx, base + 0x78, 0) & 0xFFFFu);
        S(ctx, kA1, R(ctx, kS1));
        S(ctx, kA2, lui(0x8u));
        ally = jal(ctx, base + 0x8C, &rg::fn_sub_2C0E30_002c0e30);
    }
    guest::charge(ctx, 2);
    u64 result = 0;
    if (ally == 0) {
        guest::charge(ctx, 1);
        S(ctx, kV0, 0);
    } else {
        guest::charge(ctx, 12);
        if (split_query(ctx, bits, 11, kA2) != 0) {
            guest::charge(ctx, 10);
            S(ctx, kA0, ally);
            result = ask_by_kind(ctx, base + 0xF8, R(ctx, kA2));
        } else {
            guest::charge(ctx, 3);
            S(ctx, kV0, 0);
        }
        guest::charge(ctx, 2);
    }
    guest::charge(ctx, 10);
    return_bool(ctx, base + 0x110, result);
    S(ctx, kV0, 1);
    return 1;
}

// [171] frame 32 (s0 = action, then the ally). 21: scrGetUserData, scrGetIntPara(0), the living ally -> none: 1,
// result 0; found: 10: scrGetIntPara(1), sub_301CA0(ally's unit, arg1) -> 3: 0 / 1. Then 9.
u32 sub_2C9CE0(EEContext& ctx) {
    constexpr u32 base = 0x2C9CE0;
    guest::enter(ctx, 21);
    Frame frame(ctx, 32, 1);
    S(ctx, kS0, user_data(ctx, base + 0xC));
    const u64 id = int_para(ctx, base + 0x1C, 0);
    S(ctx, kS0, find_ally(ctx, base + 0x40, R(ctx, kS0), id, kStatusDead));
    const u64 ally = R(ctx, kS0);
    u64 result = 0;
    if (ally == 0) {
        guest::charge(ctx, 1);
        S(ctx, kV0, 0);
    } else {
        guest::charge(ctx, 10);
        const u64 mask = int_para(ctx, base + 0x58, 1);
        S(ctx, kV1, lw(ctx, ally, kActUnit));
        S(ctx, kA0, lw(ctx, R(ctx, kV1), kUnitDat));
        S(ctx, kA1, mask);
        const u64 has = jal(ctx, base + 0x6C, &rg::fn_sub_301CA0_00301ca0);
        guest::charge(ctx, 3);
        result = has != 0 ? 1u : 0u;
        S(ctx, kV0, result);
    }
    guest::charge(ctx, 9);
    return_bool(ctx, base + 0x9C, result);
    S(ctx, kV0, 1);
    return 1;
}

// [180] frame 32 (s0 = action). 10: scrGetUserData, the appointed action gBtl +328 -> none: done; else 12: copy its
// target record (sub_2C08B0(action + 136, appointed + 136)), target APPOINT (row 18) with param 0; nothing chosen ->
// 6: AI. Then 6.
u32 sub_2CD4E0(EEContext& ctx) {
    constexpr u32 base = 0x2CD4E0;
    guest::enter(ctx, 10);
    Frame frame(ctx, 32, 1);
    S(ctx, kS0, user_data(ctx, base + 0xC));
    const u64 action = R(ctx, kS0);
    S(ctx, kV0, lw(ctx, R(ctx, GPR_GP), kGBtlGpOffset));
    S(ctx, kV0, lw(ctx, R(ctx, kV0), kGBtlAppointed));
    const u64 appointed = R(ctx, kV0);
    if (appointed != 0) {
        guest::charge(ctx, 12);
        S(ctx, kA0, add32i(action, kActTargetRec));
        S(ctx, kA1, add32i(appointed, kActTargetRec));
        jal(ctx, base + 0x30, &rg::fn_sub_2C08B0_002c08b0);
        target_or_default(ctx, target_fixed_row(ctx, base + 0x48, action, 18), base + 0x68, action);
    }
    guest::charge(ctx, 6);
    S(ctx, kV0, 1);
    return 1;
}

// [235] frame 32 (s0 = action). 11: scrGetUserData, scrGetIntPara(0) -> negative: 5, command 7; else 9: command 3,
// +112 = item, +110 = sub_30BC20(item & 0xFFFF). Then 6.
u32 sub_2C73E0(EEContext& ctx) {
    constexpr u32 base = 0x2C73E0;
    guest::enter(ctx, 11);
    Frame frame(ctx, 32, 1);
    S(ctx, kS0, user_data(ctx, base + 0xC));
    const u64 action = R(ctx, kS0);
    const u64 item = int_para(ctx, base + 0x1C, 0);
    if (static_cast<s64>(item) < 0) {
        guest::charge(ctx, 5);
        set_command(ctx, base + 0x5C, action, kCmdKind7);
    } else {
        guest::charge(ctx, 9);
        S(ctx, kV1, kItemCommand);
        sh(ctx, action, kActCommand, R(ctx, kV1));
        S(ctx, kA0, item & 0xFFFFu);
        sh(ctx, action, kActItem, item);
        sh(ctx, action, kActSkill, jal(ctx, base + 0x3C, &rg::fn_sub_30BC20_0030bc20));
    }
    guest::charge(ctx, 6);
    S(ctx, kV0, 1);
    return 1;
}

// [236] frame 48 (s0 = action, s1 = (u16)arg0). 19: scrGetUserData, scrGetIntPara(0), scrGetIntPara(1); $a1 = 1 (the
// answer so far). side 1 -> 4: the unit's side must be 1 (else 1: a1 = 0); else 2 -> side 0 -> 4: the unit's side must
// be 0 (else 3: a1 = 0); any other side -> 2. 3: a1 still 1 -> 5: the unit id must equal (u16)arg1 (else 1: a1 = 0).
// 10: scrSetIntReturnVal(a1 != 0).
u32 sub_2CB190(EEContext& ctx) {
    constexpr u32 base = 0x2CB190;
    guest::enter(ctx, 19);
    Frame frame(ctx, 48, 2);
    S(ctx, kS0, user_data(ctx, base + 0x10));
    const u64 me = R(ctx, kS0);
    S(ctx, kS1, int_para(ctx, base + 0x20, 0) & 0xFFFFu);
    S(ctx, kA0, int_para(ctx, base + 0x30, 1) & 0xFFFFu);
    S(ctx, kA1, 1);
    S(ctx, kV0, R(ctx, kS1) & 0xFFFFu);
    if (R(ctx, kV0) == 1) {
        guest::charge(ctx, 4);
        S(ctx, kV0, lw(ctx, me, kActUnit));
        S(ctx, kV0, lbu(ctx, R(ctx, kV0), kUnitSide));
        if (R(ctx, kV0) != 1) {
            guest::charge(ctx, 1);
            S(ctx, kA1, 0);
        }
    } else {
        guest::charge(ctx, 2);
        if (R(ctx, kV0) == 0) {
            guest::charge(ctx, 4);
            S(ctx, kV0, lw(ctx, me, kActUnit));
            S(ctx, kV0, lbu(ctx, R(ctx, kV0), kUnitSide));
            if (R(ctx, kV0) != 0) {
                guest::charge(ctx, 3);
                S(ctx, kA1, 0);
            }
        } else {
            guest::charge(ctx, 2);
        }
    }
    guest::charge(ctx, 3);
    S(ctx, kV0, 1);
    if (R(ctx, kA1) == 1) {
        guest::charge(ctx, 5);
        S(ctx, kV0, lw(ctx, me, kActUnit));
        S(ctx, kV1, lhu(ctx, R(ctx, kV0), kUnitId));
        S(ctx, kV0, R(ctx, kA0) & 0xFFFFu);
        if (R(ctx, kV1) != R(ctx, kV0)) {
            guest::charge(ctx, 1);
            S(ctx, kA1, 0);
        }
    }
    guest::charge(ctx, 10);
    return_bool(ctx, base + 0xB4, R(ctx, kA1));
    S(ctx, kV0, 1);
    return 1;
}

// [248] frame 48 (s1 = arg0, s0 = arg1). 28: scrGetIntPara(0), scrGetIntPara(1), the action with id arg0 & 0xFFFFFFF
// (sub_29A210), query MYHP (kind 1) with param = arg1 -> kind nonzero: 10, condition(that action, param) (no null
// check); zero: 3, result 0. Then 10: scrSetIntReturnVal(result != 0).
u32 sub_2CDF40(EEContext& ctx) {
    constexpr u32 base = 0x2CDF40;
    guest::enter(ctx, 28);
    Frame frame(ctx, 48, 2);
    S(ctx, kS1, int_para(ctx, base + 0x14, 0));
    S(ctx, kS0, int_para(ctx, base + 0x24, 1));
    S(ctx, kA0, low28(R(ctx, kS1)));
    const u64 other = jal(ctx, base + 0x38, &rg::fn_sub_29A210_0029a210);
    u64 result = 0;
    if (split_query(ctx, R(ctx, kS0), 1, kA2) != 0) {
        guest::charge(ctx, 10);
        S(ctx, kA0, other);
        result = ask_by_kind(ctx, base + 0x9C, R(ctx, kA2));
    } else {
        guest::charge(ctx, 3);
        S(ctx, kV0, 0);
    }
    guest::charge(ctx, 10);
    return_bool(ctx, base + 0xA8, result);
    S(ctx, kV0, 1);
    return 1;
}

// [249] frame 48 (s0 = arg0, s1 = arg1). One block of 32: the action with id arg0 & 0xFFFFFFF, sub_301CA0(its unit,
// arg1), scrSetIntReturnVal(result != 0) (the original computes the compare twice: $v0 and $a0).
u32 sub_2CE010(EEContext& ctx) {
    constexpr u32 base = 0x2CE010;
    guest::enter(ctx, 32);
    Frame frame(ctx, 48, 2);
    S(ctx, kS0, int_para(ctx, base + 0x14, 0));
    S(ctx, kS1, int_para(ctx, base + 0x24, 1));
    S(ctx, kA0, low28(R(ctx, kS0)));
    const u64 other = jal(ctx, base + 0x38, &rg::fn_sub_29A210_0029a210);
    S(ctx, kV0, lw(ctx, other, kActUnit));
    S(ctx, kA0, lw(ctx, R(ctx, kV0), kUnitDat));
    S(ctx, kA1, R(ctx, kS1));
    const u64 has = jal(ctx, base + 0x4C, &rg::fn_sub_301CA0_00301ca0);
    S(ctx, kV0, has != 0 ? 1u : 0u);
    return_bool(ctx, base + 0x5C, R(ctx, kV0));
    S(ctx, kV0, 1);
    return 1;
}

// [250] frame 64 (s2 = action, s1 = the other action, s0 = the damage). One block of 55: scrGetIntPara(0), the
// action with id arg0 & 0xFFFFFFF, damage = datCalcDamage(skill 0, my unit, its unit, hits 1, result 1, kind 1,
// flags 0, 1) (negative for damage), sub_301870 on both units, then scrSetIntReturnVal(!(its hp + damage > 0)).
u32 sub_2CE090(EEContext& ctx) {
    constexpr u32 base = 0x2CE090;
    guest::enter(ctx, 55);
    Frame frame(ctx, 64, 3);
    S(ctx, kS2, user_data(ctx, base + 0x14));
    const u64 me = R(ctx, kS2);
    S(ctx, kA0, low28(int_para(ctx, base + 0x24, 0)));
    S(ctx, kS1, jal(ctx, base + 0x34, &rg::fn_sub_29A210_0029a210));
    const u64 other = R(ctx, kS1);
    S(ctx, kV1, lw(ctx, me, kActUnit));
    S(ctx, kV0, lw(ctx, other, kActUnit));
    S(ctx, kA0, 0);
    S(ctx, kA1, lw(ctx, R(ctx, kV1), kUnitDat));
    S(ctx, kA2, lw(ctx, R(ctx, kV0), kUnitDat));
    S(ctx, kA3, 1);
    S(ctx, kT0, 1);
    S(ctx, kT1, 1);
    S(ctx, kT2, 0);
    S(ctx, kT3, 1);
    S(ctx, kS0, jal(ctx, base + 0x68, &rg::fn_datCalcDamage_00303130));
    const u64 damage = R(ctx, kS0);
    S(ctx, kV0, lw(ctx, me, kActUnit));
    S(ctx, kA0, lw(ctx, R(ctx, kV0), kUnitDat));
    jal(ctx, base + 0x7C, &rg::fn_sub_301870_00301870);
    S(ctx, kV0, lw(ctx, other, kActUnit));
    S(ctx, kA0, lw(ctx, R(ctx, kV0), kUnitDat));
    jal(ctx, base + 0x8C, &rg::fn_sub_301870_00301870);
    S(ctx, kV0, lw(ctx, other, kActUnit));
    S(ctx, kA0, lw(ctx, R(ctx, kV0), kUnitDat));
    const u64 hp = jal(ctx, base + 0x9C, &rg::fn_datCalcGetHp_002ffd70);
    S(ctx, kV0, ee::core::add32(hp & 0xFFFFu, damage));
    S(ctx, kA0, (static_cast<s64>(R(ctx, kV0)) > 0 ? 1u : 0u) ^ 1u);
    jal(ctx, base + 0xB4, &rg::fn_scrSetIntReturnVal_0035f060);
    S(ctx, kV0, 1);
    return 1;
}

}  // namespace p3fes::game

// --- the recompiled program's entry points ---------------------------------------------------------------------
namespace p3fes::recomp_gen {

using namespace p3fes::game;

#define P3FES_COMM_AI_SHIM(name, addr8, index, k) \
    void fn_##name##_##addr8(p3fes::EEContext& ctx) { guest::ret32(ctx, name(ctx)); }
P3FES_COMM_AI_ASK(P3FES_COMM_AI_SHIM)
P3FES_COMM_AI_ASK_FIXED(P3FES_COMM_AI_SHIM)
P3FES_COMM_AI_TARGET_FIXED(P3FES_COMM_AI_SHIM)
P3FES_COMM_AI_TARGET(P3FES_COMM_AI_SHIM)
P3FES_COMM_AI_COMMAND(P3FES_COMM_AI_SHIM)
P3FES_COMM_AI_ASK_ALLY(P3FES_COMM_AI_SHIM)
P3FES_COMM_AI_ALLY_FIXED(P3FES_COMM_AI_SHIM)
P3FES_COMM_AI_SHIM(sub_2C7340, 002c7340, 113, 0)
P3FES_COMM_AI_SHIM(sub_2C7540, 002c7540, 116, 0)
P3FES_COMM_AI_SHIM(sub_2C75D0, 002c75d0, 165, 0)
P3FES_COMM_AI_SHIM(sub_2D13C0, 002d13c0, 117, 0)
P3FES_COMM_AI_SHIM(sub_2C9BA0, 002c9ba0, 170, 0)
P3FES_COMM_AI_SHIM(sub_2C9CE0, 002c9ce0, 171, 0)
P3FES_COMM_AI_SHIM(sub_2CD4E0, 002cd4e0, 180, 0)
P3FES_COMM_AI_SHIM(sub_2C73E0, 002c73e0, 235, 0)
P3FES_COMM_AI_SHIM(sub_2CB190, 002cb190, 236, 0)
P3FES_COMM_AI_SHIM(sub_2CDF40, 002cdf40, 248, 0)
P3FES_COMM_AI_SHIM(sub_2CE010, 002ce010, 249, 0)
P3FES_COMM_AI_SHIM(sub_2CE090, 002ce090, 250, 0)
#undef P3FES_COMM_AI_SHIM

}  // namespace p3fes::recomp_gen
