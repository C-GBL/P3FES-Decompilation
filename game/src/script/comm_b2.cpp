// BF script COMM handlers, sScrCommandTable indices 251-501, second pass (game/include/p3fes/game/comm_b2.h),
// hand-decompiled from SLUS_216.21 (docs/ANALYSIS/18_script_vm.md sections 2.4, 3).
// tests/game/test_comm_b2.cpp runs each against its __recomp body.
//
// Fidelity. Every handler mirrors the recompiled body down to the register file:
// * virtual time (ADR-0013): guest::enter / charge / backedge follow the `ctx.cycles += N` blocks and the check
//   points of the generated body; a block is charged at its start, before the callees it contains run;
// * the frame: `Frame` performs the original prologue and epilogue (`addiu sp; sd ra; sq sN` ... `ld ra; lq sN;
//   addiu sp`), so the spill slots hold what the original stored and the callees' frames land where they did;
//   buffers the original keeps in its frame (sub_2CFEB0's unit list) are written at the same addresses;
// * calls: every callee -- still recompiled or replaced by another slice -- is entered through its generated
//   symbol with $ra = the original link and every register the original set before the `jal` (arguments,
//   compare constants, base pointers in $v0/$v1), as 64-bit values: a callee's entry check point may preempt
//   the thread, and the kernel then stores the whole register file in guest memory;
// * after the last call, the scratch registers the original writes ($v1 from a load, $a0 from an `sltu`, ...)
//   are left as it leaves them.
// K_Assert sub_19D3F0 is `jr $ra` in retail. Guest words addressed through $gp are the constants of comm_b2.h.
//
// Faithfulness audit (2026-10-21, tools/ours/audit): 2 of the 66 functions here are now p3fes_handgen's register-
// faithful bodies (their hand versions differed from the original: faults only 2); each keeps the notes of its
// earlier hand version above it. The others are the hand-written versions this header describes.
#include "p3fes/game/comm_b2.h"

#include "p3fes/ee/core.h"
#include "p3fes/game/guest.h"

#include <initializer_list>
#include "p3fes/game/hg_cpu.h"

namespace p3fes::recomp_gen {
// the COMM-side accessors (replaced: game/src/script/script_ops.cpp)
void fn_scrGetIntPara_0035ed20(p3fes::EEContext&);
void fn_scrSetIntReturnVal_0035f060(p3fes::EEContext&);
void fn_scrGetUserData_0035f160(p3fes::EEContext&);
// battle (still recompiled unless noted)
void fn_sub_2C0E30_002c0e30(p3fes::EEContext&);           // [btlFindUnitById] (id, side mask, status mask)
void fn_sub_2C08C0_002c08c0(p3fes::EEContext&);           // [btlFindUnitByKey] the living unit whose s64 +0 equals key->+48
void fn_sub_301CA0_00301ca0(p3fes::EEContext&);           // battle_rest: [datCalcCheckEffectMask] (unit, mask)
void fn_datCalcIsDead_0030b5a0(p3fes::EEContext&);        // battle_unit
void fn_datCalcRand_002ffbc0(p3fes::EEContext&);          // battle_data
void fn_datCalcGetSkillElement_003082f0(p3fes::EEContext&);  // battle_calc
void fn_sub_29AD20_0029ad20(p3fes::EEContext&);           // [btlGetCurrentActor] battle->+644 or +596
void fn_sub_29AD60_0029ad60(p3fes::EEContext&);           // [btlGetOrderSlot] battle->+596[i] for i < 12
void fn_sub_2EAB70_002eab70(p3fes::EEContext&);
void fn_sub_2EABB0_002eabb0(p3fes::EEContext&);
void fn_sub_2F2450_002f2450(p3fes::EEContext&);
void fn_sub_2F2490_002f2490(p3fes::EEContext&);
void fn_sub_2F2510_002f2510(p3fes::EEContext&);
void fn_sub_2F39B0_002f39b0(p3fes::EEContext&);
void fn_sub_2F6C20_002f6c20(p3fes::EEContext&);
void fn_sub_2EC590_002ec590(p3fes::EEContext&);
void fn_sub_2F5320_002f5320(p3fes::EEContext&);
void fn_sub_2EFD10_002efd10(p3fes::EEContext&);
void fn_sub_2F24D0_002f24d0(p3fes::EEContext&);
void fn_sub_2D1A70_002d1a70(p3fes::EEContext&);
void fn_sub_1FF350_001ff350(p3fes::EEContext&);
void fn_sub_1FF370_001ff370(p3fes::EEContext&);
void fn_sub_1FF390_001ff390(p3fes::EEContext&);
void fn_sub_1FF3B0_001ff3b0(p3fes::EEContext&);
// field / event
void fn_K_FldDungeon_GetFloorKind_001c0040(p3fes::EEContext&);           // field: [GetFloorKind]
void fn_sub_458850_00458850(p3fes::EEContext&);
void fn_sub_45A3B0_0045a3b0(p3fes::EEContext&);
void fn_sub_45A3E0_0045a3e0(p3fes::EEContext&);
void fn_sub_45A400_0045a400(p3fes::EEContext&);
void fn_sub_45A430_0045a430(p3fes::EEContext&);
void fn_sub_45AF40_0045af40(p3fes::EEContext&);
void fn_sub_1099A0_001099a0(p3fes::EEContext&);
void fn_sub_1752B0_001752b0(p3fes::EEContext&);
// g_data: the characters' item slots and persona stock (still recompiled unless noted)
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);           // K_Assert(file, line): `jr $ra` in retail
void fn_sub_16F490_0016f490(p3fes::EEContext&);           // [datCountItems] (owner) the used slots of an owner's list
void fn_sub_16F630_0016f630(p3fes::EEContext&);           // battle_data: [datGetEquipmentItemId] (owner, slot)
void fn_sub_16F810_0016f810(p3fes::EEContext&);           // (owner, slot) a byte of the slot record
void fn_sub_16FDB0_0016fdb0(p3fes::EEContext&);           // (pc, equipment index) -> the slot record
void fn_sub_16FEA0_0016fea0(p3fes::EEContext&);           // (owner, slot, item id) setter
void fn_sub_170A40_00170a40(p3fes::EEContext&);           // (pc, slot) u16 +0 of a character's 4-byte slot pair
void fn_sub_170AB0_00170ab0(p3fes::EEContext&);           // (pc, slot) s16 +2 of it
void fn_sub_170B20_00170b20(p3fes::EEContext&);           // (pc, slot, value) setter of +0
void fn_sub_170B90_00170b90(p3fes::EEContext&);           // (pc, slot, value) setter of +2
void fn_sub_177A40_00177a40(p3fes::EEContext&);           // (pc, slot) the persona slot is used
void fn_sub_177A90_00177a90(p3fes::EEContext&);           // (pc, slot) -> the persona record (asserts pc 2..11, slot < 4)
void fn_sub_177B50_00177b50(p3fes::EEContext&);           // (pc, slot) clear the persona slot
void fn_sub_177CA0_00177ca0(p3fes::EEContext&);           // (pc, equipment index) bit 0 of the equipment flag word
void fn_sub_1831E0_001831e0(p3fes::EEContext&);           // (owner, slot, record) copy an item record into a slot
void fn_datGetEquipmentIdx_0016cb80(p3fes::EEContext&);   // battle_data: (pc, slot)
// party members, persona, social links
void fn_scrGetMessageID_0035f140(p3fes::EEContext&);
void fn_sub_16C970_0016c970(p3fes::EEContext&);           // a party member's status word
void fn_sub_16CF40_0016cf40(p3fes::EEContext&);           // set a party member's HP
void fn_sub_16D9D0_0016d9d0(p3fes::EEContext&);           // clear a party member's status bits
void fn_sub_17B220_0017b220(p3fes::EEContext&);           // clear bit id of the bit array 0x83A8C4
void fn_datCalcClearEffect_00301540(p3fes::EEContext&);   // battle_data: (unit, slot)
void fn_btlGetMeanLevel_002d4cf0(p3fes::EEContext&);           // [btlGetAverageLevel] (side mask, status mask)
void fn_datCalcGetHp_002ffd70(p3fes::EEContext&);         // battle_unit
void fn_datCalcGetMaxHp_002ffdf0(p3fes::EEContext&);      // battle_data
void fn_datCalcChkBadStatus_00300580(p3fes::EEContext&);  // battle_unit
void fn_sub_173BB0_00173bb0(p3fes::EEContext&);           // (pc, stat, delta) persona->u8[+33 + stat] += delta
void fn_sub_172F70_00172f70(p3fes::EEContext&);           // (out) the first social link due by today -> *out, 1
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {

namespace rg = recomp_gen;
namespace co = ee::core;
using namespace comm_b2;
using guest::Fn;

// --- registers --------------------------------------------------------------------------------------------------
u64 R(const EEContext& ctx, unsigned r) { return co::gpr64(ctx, r); }
void S(EEContext& ctx, unsigned r, u64 v) { co::set_gpr64(ctx, r, v); }
u64 sx(u32 v) { return co::sext32(v); }
u64 sx16(u64 v) { return co::sext16(static_cast<u16>(v)); }  // dsll32/dsra32 16
u64 sx8(u64 v) { return co::sext8(static_cast<u8>(v)); }     // dsll32/dsra32 24
u32 lo32(u64 v) { return static_cast<u32>(v); }

// --- guest loads as the EE does them (lw / lb / lh sign-extend, lbu / lhu zero-extend) ----------------------------
u64 lw(const EEContext& ctx, u64 va) { return sx(guest::load<u32>(ctx, lo32(va))); }
u64 lhu(const EEContext& ctx, u64 va) { return guest::load<u16>(ctx, lo32(va)); }
u64 lbu(const EEContext& ctx, u64 va) { return guest::load<u8>(ctx, lo32(va)); }

// A call as the original made it: the argument registers are already set, `jal` at `pc` ($ra = its link), the
// callee through its generated symbol. Returns $v0.
u64 jal(EEContext& ctx, u32 pc, Fn fn) {
    rt::jal(ctx, pc);
    fn(ctx);
    return R(ctx, GPR_V0);
}

// The original frame of `size` bytes with `saved` callee-saved registers s0.. at 16 * k and $ra after them (the
// layout of every handler here): the prologue on construction, the epilogue on destruction, spills included.
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

// The same with an explicit register list (slot k at 16 * k, $ra after them): sub_2D03E0 saves s0..s7 and $fp.
class FrameRegs {
public:
    FrameRegs(EEContext& ctx, s32 size, std::initializer_list<unsigned> regs) noexcept
        : ctx_(ctx), size_(size), n_(static_cast<unsigned>(regs.size())) {
        unsigned k = 0;
        for (unsigned r : regs) regs_[k++] = r;
        rt::addiu(ctx_, GPR_SP, GPR_SP, -size_);
        rt::sd(ctx_, GPR_RA, GPR_SP, static_cast<s32>(16 * n_));
        for (unsigned j = n_; j-- > 0;) rt::sq(ctx_, regs_[j], GPR_SP, static_cast<s32>(16 * j));
    }
    ~FrameRegs() {
        rt::ld(ctx_, GPR_RA, GPR_SP, static_cast<s32>(16 * n_));
        for (unsigned j = n_; j-- > 0;) rt::lq(ctx_, regs_[j], GPR_SP, static_cast<s32>(16 * j));
        rt::addiu(ctx_, GPR_SP, GPR_SP, size_);
    }
    FrameRegs(const FrameRegs&) = delete;
    FrameRegs& operator=(const FrameRegs&) = delete;

private:
    EEContext& ctx_;
    s32 size_;
    unsigned n_;
    unsigned regs_[10] = {};
};

// scrGetIntPara(i) / scrSetIntReturnVal(v) / scrGetUserData() at a call site.
u64 int_para(EEContext& ctx, u32 pc, u64 i) {
    S(ctx, GPR_A0, i);
    return jal(ctx, pc, &rg::fn_scrGetIntPara_0035ed20);
}
void set_int(EEContext& ctx, u32 pc, u64 v) {
    S(ctx, GPR_A0, v);
    jal(ctx, pc, &rg::fn_scrSetIntReturnVal_0035f060);
}
u64 user_data(EEContext& ctx, u32 pc) { return jal(ctx, pc, &rg::fn_scrGetUserData_0035f160); }

u64 battle(const EEContext& ctx) { return lw(ctx, kBattleWork); }

// The handlers that forward one getter's value: frame 16, one block of `cycles`; `wrap` is what the original does
// to $v0 before scrSetIntReturnVal (`sltu a0, zero, v0`, `andi 0xFFFF`, `dsll32/dsra32 16`, a plain move).
enum class Wrap { Move, NonZero, U16, S16 };
u32 forward(EEContext& ctx, u64 cycles, u32 pc_get, Fn getter, u32 pc_set, Wrap wrap) {
    guest::enter(ctx, cycles);
    Frame frame(ctx, 16, 0);
    const u64 v = jal(ctx, pc_get, getter);
    switch (wrap) {
        case Wrap::Move: set_int(ctx, pc_set, v); break;
        case Wrap::NonZero: set_int(ctx, pc_set, v != 0 ? 1u : 0u); break;
        case Wrap::U16: set_int(ctx, pc_set, v & 0xFFFFu); break;
        case Wrap::S16: set_int(ctx, pc_set, sx16(v)); break;
    }
    return 1;
}

}  // namespace

// --- battle: units found by id -----------------------------------------------------------------------------------

namespace {
// The head shared by sub_2CE440 / sub_2CBCD0 / sub_2CBD90 / sub_2CBE50 / sub_2CBF10 (frame 32, s0; calls at
// base + 0x10 / 0x20, the search at + 0x54 for side 0 or + 0x6C for side 1): 16; side (arg0 & 0xFFFF, kept in s0)
// 1 -> 4 (mask 2), else 2: 0 -> 5 (mask 1), else 2 (no search: $v0 = 0). Returns the unit or 0.
u64 find_unit_by_side_arg(EEContext& ctx, u32 base) {
    S(ctx, GPR_S0, int_para(ctx, base + 0x10, 0) & 0xFFFFu);
    const u64 id = int_para(ctx, base + 0x20, 1) & 0xFFFFu;
    const u64 side = R(ctx, GPR_S0) & 0xFFFFu;
    S(ctx, GPR_A0, id);
    S(ctx, GPR_V0, 0);
    S(ctx, GPR_V1, side);
    S(ctx, GPR_A1, 1);
    if (side == 1) {
        guest::charge(ctx, 4);
        S(ctx, GPR_A1, 2);
        S(ctx, GPR_A2, kStatusDown);
        jal(ctx, base + 0x6C, &rg::fn_sub_2C0E30_002c0e30);
    } else {
        guest::charge(ctx, 2);
        if (side == 0) {
            guest::charge(ctx, 5);
            S(ctx, GPR_A2, kStatusDown);
            jal(ctx, base + 0x54, &rg::fn_sub_2C0E30_002c0e30);
        } else {
            guest::charge(ctx, 2);
        }
    }
    return R(ctx, GPR_V0);
}

// sub_2CBCD0 / sub_2CBD90 / sub_2CBE50 / sub_2CBF10: the head, then 2; no unit -> 1 (0), else 5 (the u16 +24 flags
// & mask != 0); 9: scrSetIntReturnVal at base + 0x98.
u32 unit_flag_by_side_arg(EEContext& ctx, u32 base, u32 mask) {
    guest::enter(ctx, 16);
    Frame frame(ctx, 32, 1);
    const u64 unit = find_unit_by_side_arg(ctx, base);
    guest::charge(ctx, 2);
    u64 v0 = 0;
    if (unit == 0) {
        guest::charge(ctx, 1);
    } else {
        guest::charge(ctx, 5);
        v0 = (lhu(ctx, unit + 24) & mask) != 0 ? 1u : 0u;
    }
    S(ctx, GPR_V0, v0);
    guest::charge(ctx, 9);
    set_int(ctx, base + 0x98, v0 != 0 ? 1u : 0u);
    return 1;
}

// sub_2CDA50 / sub_2CDAD0 / sub_2CA900: the search for (arg0 & 0xFFFF, 1 << side, 0x80000); `side` is in $v1 (own
// side, sub_2CDA50) or s0 (sub_2CDAD0 / sub_2CA900). Sets the registers of the call and makes it.
u64 find_unit(EEContext& ctx, u32 pc, u64 id, u64 shift) {
    const u64 bit = co::sllv(1, shift);
    S(ctx, GPR_A0, id & 0xFFFFu);
    S(ctx, GPR_V0, bit);
    S(ctx, GPR_A1, bit & 0xFFFFu);
    S(ctx, GPR_A2, kStatusDown);
    return jal(ctx, pc, &rg::fn_sub_2C0E30_002c0e30);
}

// The tail of sub_2CDA50 / sub_2CDAD0: no unit -> 1 ($a0 = 0), else 3 ($a0 = unit->s32[+32]); 8.
u32 return_unit_word(EEContext& ctx, u64 unit, u32 pc_set) {
    if (unit == 0) {
        guest::charge(ctx, 1);
        S(ctx, GPR_A0, 0);
    } else {
        guest::charge(ctx, 3);
        S(ctx, GPR_A0, lw(ctx, unit + 32));
    }
    guest::charge(ctx, 8);
    jal(ctx, pc_set, &rg::fn_scrSetIntReturnVal_0035f060);
    return 1;
}

// The head of sub_2CDAD0 / sub_2CA900 (frame 32, s0): `first` (9) with scrGetUserData at base + 0xC; the user's
// owner side byte != 0 -> 1 (s0 = 0) else 3 (s0 = 1): the other side; then `second` cycles, arg0 at `pc_arg`.
// Returns arg0.
u64 other_side_head(EEContext& ctx, u32 base, u64 second, u32 pc_arg) {
    const u64 user = user_data(ctx, base + 0xC);
    const u64 side = lbu(ctx, lw(ctx, user + 48) + 162);
    S(ctx, GPR_V0, side);
    if (side != 0) {
        guest::charge(ctx, 1);
        S(ctx, GPR_S0, 0);
    } else {
        guest::charge(ctx, 3);
        S(ctx, GPR_S0, 1);
    }
    guest::charge(ctx, second);
    return int_para(ctx, pc_arg, 0);
}
}  // namespace

u32 sub_2CE440(EEContext& ctx) {
    // [254] 0x2CE440, frame 32 (s0): the head, then 11: return unit->s32[+8] | 0x80000000 (a null unit reads
    // address 8, as retail does); $v1 = the id word, $v0 = 0xFFFFFFFF80000000.
    guest::enter(ctx, 16);
    Frame frame(ctx, 32, 1);
    const u64 unit = find_unit_by_side_arg(ctx, 0x2CE440);
    guest::charge(ctx, 11);
    const u64 id = lw(ctx, unit + 8);
    S(ctx, GPR_V1, id);
    S(ctx, GPR_V0, co::lui(0x8000));
    set_int(ctx, 0x2CE4C0, id | co::lui(0x8000));
    return 1;
}

u32 sub_2CBCD0(EEContext& ctx) { return unit_flag_by_side_arg(ctx, 0x2CBCD0, 0x1800); }  // [431]
u32 sub_2CBD90(EEContext& ctx) { return unit_flag_by_side_arg(ctx, 0x2CBD90, 0x1000); }  // [474]
u32 sub_2CBE50(EEContext& ctx) { return unit_flag_by_side_arg(ctx, 0x2CBE50, 0x0800); }  // [475]
u32 sub_2CBF10(EEContext& ctx) { return unit_flag_by_side_arg(ctx, 0x2CBF10, 0x2000); }  // [476]

u32 sub_2CDA50(EEContext& ctx) {
    // [392] 0x2CDA50, frame 32 (s0 = user): 20, then the tail. The side is the user's own ($v1 = the side byte).
    guest::enter(ctx, 20);
    Frame frame(ctx, 32, 1);
    const u64 user = user_data(ctx, 0x2CDA5C);
    S(ctx, GPR_S0, user);
    const u64 id = int_para(ctx, 0x2CDA6C, 0);
    const u64 side = lbu(ctx, lw(ctx, user + 48) + 162);
    S(ctx, GPR_V1, side);
    return return_unit_word(ctx, find_unit(ctx, 0x2CDA90, id, side), 0x2CDAB0);
}

u32 sub_2CDAD0(EEContext& ctx) {
    // [393] 0x2CDAD0, frame 32 (s0 = the other side): 9; 1 / 3; 12; then the tail.
    guest::enter(ctx, 9);
    Frame frame(ctx, 32, 1);
    const u64 id = other_side_head(ctx, 0x2CDAD0, 12, 0x2CDB08);
    return return_unit_word(ctx, find_unit(ctx, 0x2CDB24, id, R(ctx, GPR_S0)), 0x2CDB44);
}

u32 sub_2CA900(EEContext& ctx) {
    // [348] 0x2CA900, frame 32 (s0 = the other side, then the unit): 9; 1 / 3; 13; no unit -> 1 ($v0 = 0); else 10:
    // sub_301CA0(unit's DatUnit, arg1) == 0 -> 3 ($v0 = 0) else 3 ($v0 = 1); 9: return $v0 != 0.
    guest::enter(ctx, 9);
    Frame frame(ctx, 32, 1);
    const u64 id = other_side_head(ctx, 0x2CA900, 13, 0x2CA938);
    const u64 unit = find_unit(ctx, 0x2CA954, id, R(ctx, GPR_S0));
    S(ctx, GPR_S0, unit);
    u64 v0 = 0;
    if (unit == 0) {
        guest::charge(ctx, 1);
    } else {
        guest::charge(ctx, 10);
        const u64 mask = int_para(ctx, 0x2CA96C, 1);
        const u64 owner = lw(ctx, unit + 48);
        S(ctx, GPR_V1, owner);
        S(ctx, GPR_A0, lw(ctx, owner + 2604));
        S(ctx, GPR_A1, mask);
        const u64 r = jal(ctx, 0x2CA980, &rg::fn_sub_301CA0_00301ca0);
        guest::charge(ctx, 3);
        v0 = r != 0 ? 1u : 0u;
    }
    S(ctx, GPR_V0, v0);
    guest::charge(ctx, 9);
    set_int(ctx, 0x2CA9B0, v0 != 0 ? 1u : 0u);
    return 1;
}

u32 sub_2D12E0(EEContext& ctx) {
    // [445] 0x2D12E0, frame 48 (s0 = the actor, s1 = side): 19; side 1 -> 4 (owner side byte != 1 -> 1: no); else 2:
    // side 0 -> 4 (side byte != 0 -> 3: no), else 2 (any side). Then 3: still yes -> 5 (owner u16 +164 != id -> 1:
    // no); 10: return yes. "yes" lives in $a1, the id in $a0.
    guest::enter(ctx, 19);
    Frame frame(ctx, 48, 2);
    const u64 actor = jal(ctx, 0x2D12F0, &rg::fn_sub_29AD20_0029ad20);
    S(ctx, GPR_S0, actor);
    S(ctx, GPR_S1, int_para(ctx, 0x2D1300, 0) & 0xFFFFu);
    const u64 id = int_para(ctx, 0x2D1310, 1) & 0xFFFFu;
    const u64 side = R(ctx, GPR_S1) & 0xFFFFu;
    S(ctx, GPR_A0, id);
    S(ctx, GPR_A1, 1);
    S(ctx, GPR_V0, side);
    bool yes = true;
    if (side == 1) {
        guest::charge(ctx, 4);
        const u64 s = lbu(ctx, lw(ctx, actor + 48) + 162);
        S(ctx, GPR_V0, s);
        if (s != 1) {
            guest::charge(ctx, 1);
            yes = false;
        }
    } else {
        guest::charge(ctx, 2);
        if (side == 0) {
            guest::charge(ctx, 4);
            const u64 s = lbu(ctx, lw(ctx, actor + 48) + 162);
            S(ctx, GPR_V0, s);
            if (s != 0) {
                guest::charge(ctx, 3);
                yes = false;
            }
        } else {
            guest::charge(ctx, 2);
        }
    }
    guest::charge(ctx, 3);
    S(ctx, GPR_V0, 1);
    if (yes) {
        guest::charge(ctx, 5);
        const u64 owner = lw(ctx, actor + 48);
        const u64 own_id = lhu(ctx, owner + 164);
        S(ctx, GPR_V1, own_id);
        S(ctx, GPR_V0, id);
        if (own_id != id) {
            guest::charge(ctx, 1);
            yes = false;
        }
    }
    S(ctx, GPR_A1, yes ? 1u : 0u);
    guest::charge(ctx, 10);
    set_int(ctx, 0x2D1394, yes ? 1u : 0u);
    return 1;
}

// --- battle: units picked at random / scanned ---------------------------------------------------------------------

// 0x002CFEB0 sub_2CFEB0 -- 272 bytes; frame 0x60: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [268] 0x2CFEB0: 11, the key is the user record + 136.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_2CFEB0_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lhu,
          hg::lq, hg::lui, hg::lw, hg::sd, hg::sll, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002cfeb0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x2CFEC0u, gen::fn_scrGetUserData_0035f160);
    a0 = addiu(v0, 136);
    jal(ctx, 0x2CFECCu, gen::fn_sub_2C08C0_002c08c0);
    if (v0 != 0) {
        // 0x002cfedc
        charge(ctx, 5);
        lw(v1, v0, 48);
        lbu(a0, v1, 162);
        v1 = 1;
        if (a0 != v1) {
            goto L_002cfef0;
        }
        goto L_002cff90;
    }
L_002cfef0:
    charge(ctx, 5);
    s0 = 0;
    lw(v0, gp, -18692);  // 0x7CE3EC
    lw(s1, v0, 332);
    for (;;) {
        // 0x002cff70
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002cff04
        charge(ctx, 4);
        lhu(v1, s1, 26);
        v0 = v1 & 0x1;
        if (v0 != 0) {
            // 0x002cff14
            charge(ctx, 3);
            v0 = v1 & 0x8;
            if (v0 != 0) {
                // 0x002cff20
                charge(ctx, 5);
                lw(a0, s1, 48);
                lbu(v1, a0, 162);
                v0 = 1;
                if (v1 == v0) {
                    // 0x002cff34
                    charge(ctx, 3);
                    lw(a0, a0, 2604);
                    if (a0 != 0) {
                        // 0x002cff40
                        charge(ctx, 5);
                        a1 = 0;
                        jal(ctx, 0x2CFF44u, gen::fn_datCalcIsDead_0030b5a0);
                        if (v0 == 0) {
                            goto L_002cff54;
                        }
                        goto L_002cff6c;
                    }
                L_002cff54:
                    charge(ctx, 6);
                    v0 = s0 & 0xFFFF;
                    v0 = sll(v0, 2);
                    v0 = addu(v0, sp);
                    sw(s1, v0, 48);
                    v0 = addiu(s0, 1);
                    s0 = v0 & 0xFFFF;
                }
            }
        }
    L_002cff6c:
        charge(ctx, 1);
        lw(s1, s1, 1192);
    }
    // 0x002cff78
    charge(ctx, 6);
    a0 = s0 & 0xFFFF;
    jal(ctx, 0x2CFF7Cu, gen::fn_datCalcRand_002ffbc0);
    v0 = sll(v0, 2);
    v0 = addu(v0, sp);
    lw(v0, v0, 48);
L_002cff90:
    charge(ctx, 12);
    lw(v1, v0, 8);
    v0 = lui(0x8000);
    a0 = v1 | v0;
    jal(ctx, 0x2CFF9Cu, gen::fn_scrSetIntReturnVal_0035f060);
    v0 = 1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x002D0150 sub_2D0150 -- 280 bytes; frame 0x60: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [270] 0x2D0150: 13, the key is the battle's current unit (+328) + 136 (scrGetUserData's value is not used).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_2D0150_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lhu,
          hg::lq, hg::lui, hg::lw, hg::sd, hg::sll, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d0150
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x2D0160u, gen::fn_scrGetUserData_0035f160);
    lw(v0, gp, -18692);  // 0x7CE3EC
    lw(v0, v0, 328);
    a0 = addiu(v0, 136);
    jal(ctx, 0x2D0174u, gen::fn_sub_2C08C0_002c08c0);
    if (v0 != 0) {
        // 0x002d0184
        charge(ctx, 5);
        lw(v1, v0, 48);
        lbu(a0, v1, 162);
        v1 = 1;
        if (a0 != v1) {
            goto L_002d0198;
        }
        goto L_002d0238;
    }
L_002d0198:
    charge(ctx, 5);
    s0 = 0;
    lw(v0, gp, -18692);  // 0x7CE3EC
    lw(s1, v0, 332);
    for (;;) {
        // 0x002d0218
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002d01ac
        charge(ctx, 4);
        lhu(v1, s1, 26);
        v0 = v1 & 0x1;
        if (v0 != 0) {
            // 0x002d01bc
            charge(ctx, 3);
            v0 = v1 & 0x8;
            if (v0 != 0) {
                // 0x002d01c8
                charge(ctx, 5);
                lw(a0, s1, 48);
                lbu(v1, a0, 162);
                v0 = 1;
                if (v1 == v0) {
                    // 0x002d01dc
                    charge(ctx, 3);
                    lw(a0, a0, 2604);
                    if (a0 != 0) {
                        // 0x002d01e8
                        charge(ctx, 5);
                        a1 = 0;
                        jal(ctx, 0x2D01ECu, gen::fn_datCalcIsDead_0030b5a0);
                        if (v0 == 0) {
                            goto L_002d01fc;
                        }
                        goto L_002d0214;
                    }
                L_002d01fc:
                    charge(ctx, 6);
                    v0 = s0 & 0xFFFF;
                    v0 = sll(v0, 2);
                    v0 = addu(v0, sp);
                    sw(s1, v0, 48);
                    v0 = addiu(s0, 1);
                    s0 = v0 & 0xFFFF;
                }
            }
        }
    L_002d0214:
        charge(ctx, 1);
        lw(s1, s1, 1192);
    }
    // 0x002d0220
    charge(ctx, 6);
    a0 = s0 & 0xFFFF;
    jal(ctx, 0x2D0224u, gen::fn_datCalcRand_002ffbc0);
    v0 = sll(v0, 2);
    v0 = addu(v0, sp);
    lw(v0, v0, 48);
L_002d0238:
    charge(ctx, 12);
    lw(v1, v0, 8);
    v0 = lui(0x8000);
    a0 = v1 | v0;
    jal(ctx, 0x2D0244u, gen::fn_scrSetIntReturnVal_0035f060);
    v0 = 1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

u32 sub_2CC330(EEContext& ctx) {
    // [478] 0x2CC330, frame 64 (s0 = user, s1 = slot, s2 = found): 12; the test (4, (u16)slot < 12) comes first and
    // checks before every iteration; per slot 5 + sub_29AD60(slot): 0 -> out; 4: == the current unit -> out; 2:
    // == user -> 3 (found, out); else 2 (slot + 1). 11: return found.
    guest::enter(ctx, 12);
    Frame frame(ctx, 64, 3);
    const u64 user = user_data(ctx, 0x2CC344);
    S(ctx, GPR_S0, user);
    S(ctx, GPR_S2, 0);
    S(ctx, GPR_S1, 1);
    for (;;) {
        guest::charge(ctx, 4);
        const u64 more = co::slti(R(ctx, GPR_S1) & 0xFFFFu, 12);
        S(ctx, GPR_V0, more);
        if (more == 0) break;
        guest::backedge(ctx);
        guest::charge(ctx, 5);
        S(ctx, GPR_A0, R(ctx, GPR_S1));
        const u64 unit = jal(ctx, 0x2CC364, &rg::fn_sub_29AD60_0029ad60);
        if (unit == 0) break;
        guest::charge(ctx, 4);
        const u64 current = lw(ctx, battle(ctx) + 328);
        S(ctx, GPR_V1, current);
        if (unit == current) break;
        guest::charge(ctx, 2);
        if (unit == user) {
            guest::charge(ctx, 3);
            S(ctx, GPR_S2, 1);
            break;
        }
        guest::charge(ctx, 2);
        const u64 next = co::add32i(R(ctx, GPR_S1), 1);
        S(ctx, GPR_V0, next);
        S(ctx, GPR_S1, next & 0xFFFFu);
    }
    guest::charge(ctx, 11);
    set_int(ctx, 0x2CC3B4, R(ctx, GPR_S2) != 0 ? 1u : 0u);
    return 1;
}

u32 sub_2CF9F0(EEContext& ctx) {
    // [275] 0x2CF9F0, frame 16: one block of 18.
    guest::enter(ctx, 18);
    Frame frame(ctx, 16, 0);
    const u64 user = user_data(ctx, 0x2CF9F8);
    const u64 owner = lw(ctx, user + 48);
    S(ctx, GPR_V0, owner);
    S(ctx, GPR_A0, lw(ctx, owner + 2604));
    S(ctx, GPR_A1, 0);
    set_int(ctx, 0x2CFA1C, sx16(jal(ctx, 0x2CFA0C, &rg::fn_datCalcGetSkillElement_003082f0)));
    return 1;
}

u32 sub_2CDED0(EEContext& ctx) {
    // [459] 0x2CDED0, frame 32 (s0 = user): one block of 26; returns -1. $v1 = (s16)arg0, $v0 = the owner.
    guest::enter(ctx, 26);
    Frame frame(ctx, 32, 1);
    const u64 user = user_data(ctx, 0x2CDEDC);
    S(ctx, GPR_S0, user);
    const u64 skill = sx16(int_para(ctx, 0x2CDEEC, 0));
    const u64 owner = lw(ctx, user + 48);
    S(ctx, GPR_V1, skill);
    S(ctx, GPR_V0, owner);
    S(ctx, GPR_A1, skill & 0xFFFFu);
    S(ctx, GPR_A0, lw(ctx, owner + 2604));
    set_int(ctx, 0x2CDF18, sx16(jal(ctx, 0x2CDF08, &rg::fn_datCalcGetSkillElement_003082f0)));
    return 0xFFFFFFFFu;
}

// --- battle: stage words and flags ----------------------------------------------------------------------------------

namespace {
// sub_2D06E0 / sub_2D0720: frame 16, one block of 13: setter(); user->u16[+108] = 8 ($v1 = 8).
u32 stage_then_mark(EEContext& ctx, u32 pc_setter, Fn setter, u32 pc_user) {
    guest::enter(ctx, 13);
    Frame frame(ctx, 16, 0);
    jal(ctx, pc_setter, setter);
    const u64 user = user_data(ctx, pc_user);
    S(ctx, GPR_V1, 8);
    guest::store<u16>(ctx, lo32(user) + 108, 8);
    return 1;
}
// sub_2D0B90 / sub_2D0BD0: frame 16, one block of 14: user->u16[+108] = 8 ($v1 = 8); setter(user).
u32 mark_then_stage(EEContext& ctx, u32 pc_user, u32 pc_setter, Fn setter) {
    guest::enter(ctx, 14);
    Frame frame(ctx, 16, 0);
    const u64 user = user_data(ctx, pc_user);
    S(ctx, GPR_A0, user);
    S(ctx, GPR_V1, 8);
    guest::store<u16>(ctx, lo32(user) + 108, 8);
    jal(ctx, pc_setter, setter);
    return 1;
}
}  // namespace

u32 sub_2D06E0(EEContext& ctx) { return stage_then_mark(ctx, 0x2D06E8, &rg::fn_sub_2EAB70_002eab70, 0x2D06F0); }  // [329]
u32 sub_2D0720(EEContext& ctx) { return stage_then_mark(ctx, 0x2D0728, &rg::fn_sub_2EABB0_002eabb0, 0x2D0730); }  // [330]
u32 sub_2D0B90(EEContext& ctx) { return mark_then_stage(ctx, 0x2D0B98, 0x2D0BAC, &rg::fn_sub_2F2450_002f2450); }  // [383]
u32 sub_2D0BD0(EEContext& ctx) { return mark_then_stage(ctx, 0x2D0BD8, 0x2D0BEC, &rg::fn_sub_2F2490_002f2490); }  // [384]

u32 sub_2D0C10(EEContext& ctx) {
    // [453] 0x2D0C10, frame 16: one block of 15.
    guest::enter(ctx, 15);
    Frame frame(ctx, 16, 0);
    S(ctx, GPR_A0, user_data(ctx, 0x2D0C18));
    set_int(ctx, 0x2D0C30, jal(ctx, 0x2D0C24, &rg::fn_sub_2F2510_002f2510));
    return 1;
}

u32 sub_2D0C80(EEContext& ctx) {
    // [452] 0x2D0C80, frame 16: one block of 11 ($v0 = the battle work).
    guest::enter(ctx, 11);
    Frame frame(ctx, 16, 0);
    const u64 b = battle(ctx);
    S(ctx, GPR_V0, b);
    S(ctx, GPR_A0, lw(ctx, b + 328));
    jal(ctx, 0x2D0C90, &rg::fn_sub_2F39B0_002f39b0);
    return 1;
}

namespace {
// The battle stage id: (battle->+3004)->u16[+8], left in $v1.
u64 stage_id(EEContext& ctx) {
    const u64 stage = lhu(ctx, lw(ctx, battle(ctx) + 3004) + 8);
    S(ctx, GPR_V1, stage);
    return stage;
}
}  // namespace

u32 sub_2D0860(EEContext& ctx) {
    // [374] 0x2D0860, frame 16: 8; stage 436 -> 5 (sub_2F6C20); else 3: stage 421 -> 7 (sub_2EC590), else 2; 5.
    // The compare constant is left in $v0.
    guest::enter(ctx, 8);
    Frame frame(ctx, 16, 0);
    const u64 stage = stage_id(ctx);
    S(ctx, GPR_V0, kStage436);
    if (stage == kStage436) {
        guest::charge(ctx, 5);
        set_int(ctx, 0x2D08BC, jal(ctx, 0x2D08B0, &rg::fn_sub_2F6C20_002f6c20) != 0 ? 1u : 0u);
    } else {
        guest::charge(ctx, 3);
        S(ctx, GPR_V0, kStage421);
        if (stage == kStage421) {
            guest::charge(ctx, 7);
            set_int(ctx, 0x2D08A0, jal(ctx, 0x2D0894, &rg::fn_sub_2EC590_002ec590) != 0 ? 1u : 0u);
        } else {
            guest::charge(ctx, 2);
        }
    }
    guest::charge(ctx, 5);
    return 1;
}

u32 sub_2D0970(EEContext& ctx) {
    // [492] 0x2D0970, frame 16: 8; stage 432 -> 7 (return sub_2F5320()), else 3 (return 7); 5.
    guest::enter(ctx, 8);
    Frame frame(ctx, 16, 0);
    const u64 stage = stage_id(ctx);
    S(ctx, GPR_V0, kStage432);
    if (stage == kStage432) {
        guest::charge(ctx, 7);
        set_int(ctx, 0x2D099C, jal(ctx, 0x2D0990, &rg::fn_sub_2F5320_002f5320));
    } else {
        guest::charge(ctx, 3);
        set_int(ctx, 0x2D09B0, 7);
    }
    guest::charge(ctx, 5);
    return 1;
}

u32 sub_2D0AC0(EEContext& ctx) { return forward(ctx, 12, 0x2D0AC8, &rg::fn_sub_2EFD10_002efd10, 0x2D0AD4, Wrap::NonZero); }  // [378]
u32 sub_2D0C50(EEContext& ctx) { return forward(ctx, 12, 0x2D0C58, &rg::fn_sub_2F24D0_002f24d0, 0x2D0C64, Wrap::NonZero); }  // [386]

u32 sub_2D11D0(EEContext& ctx) {
    // [439] 0x2D11D0, frame 16: 7; sub_2D1A70() == 1 -> 4 (battle->+12 |= 0x4000; $v1 = battle, $v0 = the word); 5.
    guest::enter(ctx, 7);
    Frame frame(ctx, 16, 0);
    const u64 r = jal(ctx, 0x2D11D8, &rg::fn_sub_2D1A70_002d1a70);
    S(ctx, GPR_V1, 1);
    if (r == 1) {
        guest::charge(ctx, 4);
        const u64 b = battle(ctx);
        const u64 word = co::ori(lw(ctx, b + 12), 0x4000);
        S(ctx, GPR_V1, b);
        S(ctx, GPR_V0, word);
        guest::store<u32>(ctx, lo32(b) + 12, lo32(word));
    }
    guest::charge(ctx, 5);
    return 1;
}

namespace {
// sub_2D1260 / sub_2D12A0, frame 16: 9: first(); sub_2D1A70() == 1 ($v1 = 1) -> 2: second(); 5.
u32 battle_flag_pair(EEContext& ctx, u32 base, Fn first, Fn second) {
    guest::enter(ctx, 9);
    Frame frame(ctx, 16, 0);
    jal(ctx, base + 0x8, first);
    const u64 r = jal(ctx, base + 0x10, &rg::fn_sub_2D1A70_002d1a70);
    S(ctx, GPR_V1, 1);
    if (r == 1) {
        guest::charge(ctx, 2);
        jal(ctx, base + 0x24, second);
    }
    guest::charge(ctx, 5);
    return 1;
}
}  // namespace

u32 sub_2D1260(EEContext& ctx) { return battle_flag_pair(ctx, 0x2D1260, &rg::fn_sub_1FF3B0_001ff3b0, &rg::fn_sub_1FF370_001ff370); }  // [441]
u32 sub_2D12A0(EEContext& ctx) { return battle_flag_pair(ctx, 0x2D12A0, &rg::fn_sub_1FF390_001ff390, &rg::fn_sub_1FF350_001ff350); }  // [442]

// --- field / event --------------------------------------------------------------------------------------------------

u32 sub_1C5670(EEContext& ctx) { return forward(ctx, 12, 0x1C5678, &rg::fn_K_FldDungeon_GetFloorKind_001c0040, 0x1C5684, Wrap::Move); }  // [372]
u32 sub_1C5460(EEContext& ctx) { return forward(ctx, 13, 0x1C5468, &rg::fn_sub_1099A0_001099a0, 0x1C5478, Wrap::S16); }  // [482]
u32 sub_35FD80(EEContext& ctx) { return forward(ctx, 12, 0x35FD88, &rg::fn_sub_1752B0_001752b0, 0x35FD94, Wrap::U16); }  // [496]

u32 sub_425360(EEContext& ctx) {
    // [382] 0x425360, frame 32 (s0 = i): 6; the test (3, `slti v0, s0, 4`) comes first and checks before every
    // iteration; body 10: record i of kFieldObjTable (448 bytes: (i * 8 - i) << 6) -> sub_458850(its +364); 6.
    guest::enter(ctx, 6);
    Frame frame(ctx, 32, 1);
    S(ctx, GPR_S0, 0);
    for (;;) {
        guest::charge(ctx, 3);
        const u64 i = R(ctx, GPR_S0);
        S(ctx, GPR_V0, co::slti(i, 4));
        if (co::slti(i, 4) == 0) break;
        guest::backedge(ctx);
        guest::charge(ctx, 10);
        const u64 off = co::sll(co::sub32(co::sll(i, 3), i), 6);
        const u64 rec = co::add32(sx(kFieldObjTable), off);
        S(ctx, GPR_V1, off);
        S(ctx, GPR_V0, rec);
        S(ctx, GPR_A0, lw(ctx, rec + 364));
        jal(ctx, 0x425394, &rg::fn_sub_458850_00458850);
        S(ctx, GPR_S0, co::add32i(i, 1));
    }
    guest::charge(ctx, 6);
    return 1;
}

namespace {
// The guard of the kFieldFx handlers: no object ($v0 = 0) -> 3: scrSetIntReturnVal(-1) at `pc`, then go on.
void fx_guard(EEContext& ctx, u32 pc) {
    const u64 fx = lw(ctx, kFieldFx);
    S(ctx, GPR_V0, fx);
    if (fx == 0) {
        guest::charge(ctx, 3);
        set_int(ctx, pc, sx(0xFFFFFFFFu));
    }
}
// sub_425530 / sub_425580, frame 16: 5; the guard; 10: action(); return 0.
u32 fx_action(EEContext& ctx, u32 base, Fn action) {
    guest::enter(ctx, 5);
    Frame frame(ctx, 16, 0);
    fx_guard(ctx, base + 0x18);
    guest::charge(ctx, 10);
    jal(ctx, base + 0x20, action);
    set_int(ctx, base + 0x2C, 0);
    return 1;
}
}  // namespace

u32 sub_4254C0(EEContext& ctx) {
    // [419] 0x4254C0, frame 32 (s0 = result): 7; the guard; 5: sub_45A3B0() == 1 ($v1 = 1) -> 1 (s0 = 1); 9.
    guest::enter(ctx, 7);
    Frame frame(ctx, 32, 1);
    S(ctx, GPR_S0, 0);
    fx_guard(ctx, 0x4254E0);
    guest::charge(ctx, 5);
    const u64 r = jal(ctx, 0x4254E8, &rg::fn_sub_45A3B0_0045a3b0);
    S(ctx, GPR_V1, 1);
    if (r == 1) {
        guest::charge(ctx, 1);
        S(ctx, GPR_S0, 1);
    }
    guest::charge(ctx, 9);
    set_int(ctx, 0x425504, R(ctx, GPR_S0));
    return 1;
}

u32 sub_425530(EEContext& ctx) { return fx_action(ctx, 0x425530, &rg::fn_sub_45A3E0_0045a3e0); }  // [420]
u32 sub_425580(EEContext& ctx) { return fx_action(ctx, 0x425580, &rg::fn_sub_45A400_0045a400); }  // [421]

u32 sub_4255D0(EEContext& ctx) {
    // [422] 0x4255D0, frame 32 (s0 = arg0): 10; the guard; 13: sub_45A430((s8)arg0); return 0.
    guest::enter(ctx, 10);
    Frame frame(ctx, 32, 1);
    S(ctx, GPR_S0, int_para(ctx, 0x4255E0, 0));
    fx_guard(ctx, 0x4255FC);
    guest::charge(ctx, 13);
    S(ctx, GPR_A0, sx8(R(ctx, GPR_S0)));
    jal(ctx, 0x42560C, &rg::fn_sub_45A430_0045a430);
    set_int(ctx, 0x425618, 0);
    return 1;
}

u32 sub_425640(EEContext& ctx) {
    // [423] 0x425640, frame 16: 5; the guard; 10: return sub_45AF40().
    guest::enter(ctx, 5);
    Frame frame(ctx, 16, 0);
    fx_guard(ctx, 0x425658);
    guest::charge(ctx, 10);
    set_int(ctx, 0x42566C, jal(ctx, 0x425660, &rg::fn_sub_45AF40_0045af40));
    return 1;
}

// --- g_data: the characters' item slot pairs (0x833C58 + 868 * pc, 20 x { u16, s16 }) -------------------------------

namespace {
// The guard of the 0x4244E0..0x4249B0 handlers: pc (whole register) in 1..11. 3 cycles for the second test, which
// leaves the `slti` in $at.
bool party_pc(EEContext& ctx, u64 pc) {
    if (static_cast<s64>(pc) <= 0) return false;
    guest::charge(ctx, 3);
    S(ctx, GPR_AT, co::slti(pc, 12));
    return co::slti(pc, 12) != 0;
}
// sub_16F490(pc + 256) as the handlers call it: `addiu v0, pc, 256` and its 16-bit sign extension in $a0.
u64 count_items(EEContext& ctx, u32 pc_call, u64 pc) {
    const u64 owner = co::add32i(pc, 256);
    S(ctx, GPR_V0, owner);
    S(ctx, GPR_A0, sx16(owner));
    return jal(ctx, pc_call, &rg::fn_sub_16F490_0016f490);
}
// sub_170AB0 / sub_170A40(pc, slot) with both arguments narrowed to s16; returns $v0.
u64 slot_pair(EEContext& ctx, u32 pc_call, Fn fn, u64 pc, u64 slot) {
    S(ctx, GPR_A0, sx16(pc));
    S(ctx, GPR_A1, sx16(slot));
    return jal(ctx, pc_call, fn);
}
// The loop test of the 20-slot walks: 3 cycles, `slti v0, slot, 20`, the back-edge check before each body.
bool slot_test(EEContext& ctx, unsigned reg, s32 bound = 20) {
    guest::charge(ctx, 3);
    const u64 more = co::slti(R(ctx, reg), bound);
    S(ctx, GPR_V0, more);
    if (more == 0) return false;
    guest::backedge(ctx);
    return true;
}
void inc(EEContext& ctx, unsigned reg) { S(ctx, reg, co::add32i(R(ctx, reg), 1)); }
}  // namespace

u32 sub_4244E0(EEContext& ctx) {
    // [334] 0x4244E0, frame 64 (s0 = pc, s1 = count, s2 = slot): 11; pc in 1..11 -> 9: count = sub_16F490(pc + 256),
    // then for the 20 slots (body 10, a positive s16 +2 -> 1: count + 1; 1) and 5: return count; else 3: return 0. 8.
    guest::enter(ctx, 11);
    Frame frame(ctx, 64, 3);
    const u64 pc = int_para(ctx, 0x4244F8, 0);
    S(ctx, GPR_S0, pc);
    if (party_pc(ctx, pc)) {
        guest::charge(ctx, 9);
        S(ctx, GPR_S1, count_items(ctx, 0x424524, pc));
        S(ctx, GPR_S2, 0);
        while (slot_test(ctx, GPR_S2)) {
            guest::charge(ctx, 10);
            const u64 v = sx16(slot_pair(ctx, 0x42454C, &rg::fn_sub_170AB0_00170ab0, R(ctx, GPR_S0), R(ctx, GPR_S2)));
            S(ctx, GPR_V0, v);
            if (static_cast<s64>(v) > 0) {
                guest::charge(ctx, 1);
                inc(ctx, GPR_S1);
            }
            guest::charge(ctx, 1);
            inc(ctx, GPR_S2);
        }
        guest::charge(ctx, 5);
        set_int(ctx, 0x42457C, R(ctx, GPR_S1));
    } else {
        guest::charge(ctx, 3);
        set_int(ctx, 0x424590, 0);
    }
    guest::charge(ctx, 8);
    return 1;
}

u32 sub_4245C0(EEContext& ctx) {
    // [335] 0x4245C0, frame 96 (s0 = pc, s1 = result, s2 = slot, s3 = n, s4 = k): 18; pc in 1..11 -> 9: n =
    // sub_16F490(pc + 256); k < n and n > 0 (2) -> 12: return sub_16F630(pc + 256, k) & 0xFFFF; else 3, the walk:
    // each slot with a positive s16 +2 (body 10) -> 2: the n-th such (k == n) -> 7: result = sub_170A40 & 0xFFFF;
    // 1: n + 1; 1: next; 5: return result. pc outside -> 3: return 0. Then 1 and 9 ($v0 = 1 set early on the
    // first path).
    guest::enter(ctx, 18);
    Frame frame(ctx, 96, 5);
    S(ctx, GPR_S1, sx(0xFFFFFFFFu));
    S(ctx, GPR_S0, int_para(ctx, 0x4245E4, 0));
    S(ctx, GPR_S4, int_para(ctx, 0x4245F4, 1));
    const u64 pc = R(ctx, GPR_S0), k = R(ctx, GPR_S4);
    if (party_pc(ctx, pc)) {
        guest::charge(ctx, 9);
        const u64 n = count_items(ctx, 0x424620, pc);
        S(ctx, GPR_S3, n);
        S(ctx, GPR_AT, co::slt(k, n));
        bool direct = false;
        if (co::slt(k, n) != 0) {
            guest::charge(ctx, 2);
            direct = static_cast<s64>(n) > 0;
        }
        if (direct) {
            guest::charge(ctx, 12);
            const u64 owner = co::add32i(pc, 256);
            S(ctx, GPR_V0, owner);
            S(ctx, GPR_A0, sx16(owner));
            S(ctx, GPR_A1, k);
            set_int(ctx, 0x42465C, jal(ctx, 0x424650, &rg::fn_sub_16F630_0016f630) & 0xFFFFu);
            S(ctx, GPR_V0, 1);
            guest::charge(ctx, 9);
            return 1;
        }
        guest::charge(ctx, 3);
        S(ctx, GPR_S2, 0);
        while (slot_test(ctx, GPR_S2)) {
            guest::charge(ctx, 10);
            const u64 v = sx16(slot_pair(ctx, 0x42468C, &rg::fn_sub_170AB0_00170ab0, R(ctx, GPR_S0), R(ctx, GPR_S2)));
            S(ctx, GPR_V0, v);
            if (static_cast<s64>(v) > 0) {
                guest::charge(ctx, 2);
                if (R(ctx, GPR_S4) == R(ctx, GPR_S3)) {
                    guest::charge(ctx, 7);
                    S(ctx, GPR_S1, slot_pair(ctx, 0x4246BC, &rg::fn_sub_170A40_00170a40, R(ctx, GPR_S0), R(ctx, GPR_S2)) & 0xFFFFu);
                }
                guest::charge(ctx, 1);
                inc(ctx, GPR_S3);
            }
            guest::charge(ctx, 1);
            inc(ctx, GPR_S2);
        }
        guest::charge(ctx, 5);
        set_int(ctx, 0x4246E0, R(ctx, GPR_S1));
    } else {
        guest::charge(ctx, 3);
        set_int(ctx, 0x4246F4, 0);
    }
    guest::charge(ctx, 1);
    S(ctx, GPR_V0, 1);
    guest::charge(ctx, 9);
    return 1;
}

u32 sub_424730(EEContext& ctx) {
    // [336] 0x424730, frame 96 (s0 = k, s1 = pc, s2 = slot, s3 = n, s4 = result): 18; pc in 1..11 -> 9: n =
    // sub_16F490(pc + 256); k < n and n > 0 (2) -> 6: return 1; else 3, the walk as in sub_4245C0 with result =
    // (s16)sub_170AB0 (8) for the n-th positive slot; 5: return result. pc outside -> 3: return 0. 1; 9.
    guest::enter(ctx, 18);
    Frame frame(ctx, 96, 5);
    S(ctx, GPR_S4, sx(0xFFFFFFFFu));
    S(ctx, GPR_S1, int_para(ctx, 0x424754, 0));
    S(ctx, GPR_S0, int_para(ctx, 0x424764, 1));
    const u64 pc = R(ctx, GPR_S1), k = R(ctx, GPR_S0);
    if (party_pc(ctx, pc)) {
        guest::charge(ctx, 9);
        const u64 n = count_items(ctx, 0x424790, pc);
        S(ctx, GPR_S3, n);
        S(ctx, GPR_AT, co::slt(k, n));
        bool direct = false;
        if (co::slt(k, n) != 0) {
            guest::charge(ctx, 2);
            direct = static_cast<s64>(n) > 0;
        }
        if (direct) {
            guest::charge(ctx, 6);
            set_int(ctx, 0x4247B4, 1);
            S(ctx, GPR_V0, 1);
            guest::charge(ctx, 9);
            return 1;
        }
        guest::charge(ctx, 3);
        S(ctx, GPR_S2, 0);
        while (slot_test(ctx, GPR_S2)) {
            guest::charge(ctx, 10);
            const u64 v = sx16(slot_pair(ctx, 0x4247E4, &rg::fn_sub_170AB0_00170ab0, R(ctx, GPR_S1), R(ctx, GPR_S2)));
            S(ctx, GPR_V0, v);
            if (static_cast<s64>(v) > 0) {
                guest::charge(ctx, 2);
                if (R(ctx, GPR_S0) == R(ctx, GPR_S3)) {
                    guest::charge(ctx, 8);
                    S(ctx, GPR_S4, sx16(slot_pair(ctx, 0x424814, &rg::fn_sub_170AB0_00170ab0, R(ctx, GPR_S1), R(ctx, GPR_S2))));
                }
                guest::charge(ctx, 1);
                inc(ctx, GPR_S3);
            }
            guest::charge(ctx, 1);
            inc(ctx, GPR_S2);
        }
        guest::charge(ctx, 5);
        set_int(ctx, 0x42483C, R(ctx, GPR_S4));
    } else {
        guest::charge(ctx, 3);
        set_int(ctx, 0x424850, 0);
    }
    guest::charge(ctx, 1);
    S(ctx, GPR_V0, 1);
    guest::charge(ctx, 9);
    return 1;
}

u32 sub_424880(EEContext& ctx) {
    // [338] 0x424880, frame 64 (s0 = pc, s1 = result, s2 = k then the slot): 16; pc in 1..11 -> 8: n =
    // sub_16F490(pc + 256) (kept in $v0); k < n and n > 0 (2) -> 12: return sub_16F810(pc + 256, k) & 0xFF; else 3,
    // the walk (body 10, a positive s16 +2 -> 1: result = 0; 1) and 5: return result (always 0). pc outside -> 3:
    // return 0. 1; 7.
    guest::enter(ctx, 16);
    Frame frame(ctx, 64, 3);
    S(ctx, GPR_S1, 0);
    S(ctx, GPR_S0, int_para(ctx, 0x42489C, 0));
    S(ctx, GPR_S2, int_para(ctx, 0x4248AC, 1));
    const u64 pc = R(ctx, GPR_S0), k = R(ctx, GPR_S2);
    if (party_pc(ctx, pc)) {
        guest::charge(ctx, 8);
        const u64 n = count_items(ctx, 0x4248D8, pc);
        S(ctx, GPR_AT, co::slt(k, n));
        bool direct = false;
        if (co::slt(k, n) != 0) {
            guest::charge(ctx, 2);
            direct = static_cast<s64>(n) > 0;
        }
        if (direct) {
            guest::charge(ctx, 12);
            const u64 owner = co::add32i(pc, 256);
            S(ctx, GPR_V0, owner);
            S(ctx, GPR_A0, sx16(owner));
            S(ctx, GPR_A1, k);
            set_int(ctx, 0x424910, jal(ctx, 0x424904, &rg::fn_sub_16F810_0016f810) & 0xFFu);
            S(ctx, GPR_V0, 1);
            guest::charge(ctx, 7);
            return 1;
        }
        guest::charge(ctx, 3);
        S(ctx, GPR_S2, 0);
        while (slot_test(ctx, GPR_S2)) {
            guest::charge(ctx, 10);
            const u64 v = sx16(slot_pair(ctx, 0x424940, &rg::fn_sub_170AB0_00170ab0, R(ctx, GPR_S0), R(ctx, GPR_S2)));
            S(ctx, GPR_V0, v);
            if (static_cast<s64>(v) > 0) {
                guest::charge(ctx, 1);
                S(ctx, GPR_S1, 0);
            }
            guest::charge(ctx, 1);
            inc(ctx, GPR_S2);
        }
        guest::charge(ctx, 5);
        set_int(ctx, 0x424970, R(ctx, GPR_S1));
    } else {
        guest::charge(ctx, 3);
        set_int(ctx, 0x424984, 0);
    }
    guest::charge(ctx, 1);
    S(ctx, GPR_V0, 1);
    guest::charge(ctx, 7);
    return 1;
}

namespace {
// The three field party slots of sub_4249B0: kFieldTable records 1..3 (word +0, word +12, u16 +352 = the member)
// and the byte flags $gp-17956 / -17952 / -17948 they clear.
constexpr u32 kFieldTable = 0x8717E8u;
constexpr u32 kPartySlotFlag = kGp - 17956;  // 0x7CE6CC, then +4, +8
}  // namespace

u32 sub_4249B0(EEContext& ctx) {
    // [337] 0x4249B0, frame 64 (s0 = pc, s1 = cleared, s2 = slot): 12; pc in 1..11 -> 3, then the 20 slots (body
    // 22): sub_170B20(pc, slot, 0), sub_170B90(pc, slot, 0), sub_16FEA0(pc + 256, slot, 0); then for field slots
    // 1..3: 5 (word +0 != 0) -> 3 (word +12 != 0); 2: both -> 4 (u16 +352 == pc) -> 2: its flag byte = 0, cleared =
    // 1. 4: (s8)cleared == 0 (pc outside included) -> 3: all three flags = 0. 8.
    guest::enter(ctx, 12);
    Frame frame(ctx, 64, 3);
    S(ctx, GPR_S1, 0);
    S(ctx, GPR_S0, int_para(ctx, 0x4249CC, 0));
    const u64 pc = R(ctx, GPR_S0);
    if (party_pc(ctx, pc)) {
        guest::charge(ctx, 3);
        S(ctx, GPR_S2, 0);
        while (slot_test(ctx, GPR_S2)) {
            guest::charge(ctx, 22);
            const u64 slot = R(ctx, GPR_S2);
            S(ctx, GPR_A2, 0);
            slot_pair(ctx, 0x424A0C, &rg::fn_sub_170B20_00170b20, pc, slot);
            S(ctx, GPR_A2, 0);
            slot_pair(ctx, 0x424A28, &rg::fn_sub_170B90_00170b90, pc, slot);
            const u64 owner = co::add32i(pc, 256);
            S(ctx, GPR_V0, owner);
            S(ctx, GPR_A0, sx16(owner));
            S(ctx, GPR_A1, slot);
            S(ctx, GPR_A2, 0);
            jal(ctx, 0x424A44, &rg::fn_sub_16FEA0_0016fea0);
            inc(ctx, GPR_S2);
        }
        for (u32 r = 1; r <= 3; ++r) {
            const u32 rec = kFieldTable + 448 * r;
            guest::charge(ctx, 5);
            u64 v0 = lw(ctx, rec) != 0 ? 1u : 0u;
            if (v0 != 0) {
                guest::charge(ctx, 3);
                v0 = lw(ctx, rec + 12) != 0 ? 1u : 0u;
            }
            S(ctx, GPR_V0, v0);
            guest::charge(ctx, 2);
            if (v0 == 0) continue;
            guest::charge(ctx, 4);
            const u64 member = lhu(ctx, rec + 352);
            S(ctx, GPR_V0, member);
            if (member != pc) continue;
            guest::charge(ctx, 2);
            guest::store<u8>(ctx, kPartySlotFlag + 4 * (r - 1), 0);
            S(ctx, GPR_S1, 1);
        }
    }
    guest::charge(ctx, 4);
    const u64 cleared = sx8(R(ctx, GPR_S1));
    S(ctx, GPR_V0, cleared);
    if (cleared == 0) {
        guest::charge(ctx, 3);
        for (u32 r = 0; r < 3; ++r) guest::store<u8>(ctx, kPartySlotFlag + 4 * r, 0);
    }
    guest::charge(ctx, 8);
    return 1;
}

// --- g_data: Koromaru's persona slots and equipment (pc 9) ---------------------------------------------------------

namespace {
constexpr u64 kPcKoromaru = 9;
constexpr u32 kFileFieldCommand = 0x683660u;  // the K_Assert file argument of the item copies
// sub_177A40(pc, slot) -> persona slot used; the arguments as the original sets them ($a0 = pc constant).
u64 persona_used(EEContext& ctx, u32 pc_call, u64 pc, u64 slot) {
    S(ctx, GPR_A0, pc);
    S(ctx, GPR_A1, slot);
    return jal(ctx, pc_call, &rg::fn_sub_177A40_00177a40);
}
// datGetEquipmentIdx(9, (s16)slot), then sub_177CA0(9, (s16)index); `index_reg` keeps the index when the original
// does (s1 / s4), else $a1 only. Returns sub_177CA0's $v0.
u64 equipment_flag(EEContext& ctx, u32 pc_idx, u32 pc_flag, u64 slot, unsigned index_reg) {
    S(ctx, GPR_A1, sx16(slot));
    S(ctx, GPR_A0, kPcKoromaru);
    const u64 index = sx16(jal(ctx, pc_idx, &rg::fn_datGetEquipmentIdx_0016cb80));
    if (index_reg != GPR_ZERO) S(ctx, index_reg, index);
    S(ctx, GPR_A1, index);
    S(ctx, GPR_A0, kPcKoromaru);
    return jal(ctx, pc_flag, &rg::fn_sub_177CA0_00177ca0);
}
// The first free inventory slot (sub_16F630(-1, slot) & 0xFFFF == 0) in `reg` (test 3 + back-edge, body 7, 1 per
// step; the walk breaks out on a free slot), the K_Assert(file, line) when none of the 20 is free (3, then 5), then
// 6 (or `copy_cycles`): sub_1831E0(-1, (s16)slot, record).
void copy_to_free_slot(EEContext& ctx, unsigned reg, u32 pc_get, u32 pc_assert, u32 line, u64 copy_cycles, u32 pc_copy,
                       u64 record) {
    S(ctx, reg, 0);
    while (slot_test(ctx, reg)) {
        guest::charge(ctx, 7);
        S(ctx, GPR_A0, sx(0xFFFFFFFFu));
        S(ctx, GPR_A1, R(ctx, reg));
        const u64 item = jal(ctx, pc_get, &rg::fn_sub_16F630_0016f630) & 0xFFFFu;
        S(ctx, GPR_V0, item);
        if (item == 0) break;
        guest::charge(ctx, 1);
        inc(ctx, reg);
    }
    guest::charge(ctx, 3);
    const u64 below = co::slti(R(ctx, reg), 20);
    S(ctx, GPR_V0, below);
    if (below == 0) {
        guest::charge(ctx, 5);
        S(ctx, GPR_A0, kFileFieldCommand);
        S(ctx, GPR_A1, line);
        jal(ctx, pc_assert, &rg::fn_sub_19D3F0_0019d3f0);
    }
    guest::charge(ctx, copy_cycles);
    S(ctx, GPR_A1, sx16(R(ctx, reg)));
    S(ctx, GPR_A0, sx(0xFFFFFFFFu));
    S(ctx, GPR_A2, record);
    jal(ctx, pc_copy, &rg::fn_sub_1831E0_001831e0);
}
}  // namespace

u32 sub_1C4F70(EEContext& ctx) {
    // [464] 0x1C4F70, frame 48 (s0 = slot, s1 = count): 8; persona slots 0..3 (test 3 first, body 6, used -> 1:
    // count + 1; 1); 3; equipment slots 0..3 (body 12: the flag of datGetEquipmentIdx(9, slot) -> 1: count + 1; 1);
    // 10: return count.
    guest::enter(ctx, 8);
    Frame frame(ctx, 48, 2);
    S(ctx, GPR_S1, 0);
    S(ctx, GPR_S0, 0);
    while (slot_test(ctx, GPR_S0, 4)) {
        guest::charge(ctx, 6);
        if (persona_used(ctx, 0x1C4F98, kPcKoromaru, R(ctx, GPR_S0)) != 0) {
            guest::charge(ctx, 1);
            inc(ctx, GPR_S1);
        }
        guest::charge(ctx, 1);
        inc(ctx, GPR_S0);
    }
    guest::charge(ctx, 3);
    S(ctx, GPR_S0, 0);
    while (slot_test(ctx, GPR_S0, 4)) {
        guest::charge(ctx, 12);
        if (equipment_flag(ctx, 0x1C4FD4, 0x1C4FE8, R(ctx, GPR_S0), GPR_ZERO) != 0) {
            guest::charge(ctx, 1);
            inc(ctx, GPR_S1);
        }
        guest::charge(ctx, 1);
        inc(ctx, GPR_S0);
    }
    guest::charge(ctx, 10);
    set_int(ctx, 0x1C5010, R(ctx, GPR_S1));
    return 1;
}

u32 sub_1C5040(EEContext& ctx) {
    // [465] 0x1C5040, frame 96 (s0 = n, s1 = result, s2 = k, s3 = record / slot, s4 = slot / index): 17; persona slots
    // (body 6: used -> 2: the k-th used (n == k) -> 5: record = sub_177A90(9, slot); 1: n + 1; 1); 2: a record -> 1:
    // result = its u16 +0; 3; equipment slots (body 13: flagged -> 2: the k-th -> 5: result = sub_16F630(9, index) &
    // 0xFFFF; 1: n + 1; 1); 13: return result.
    guest::enter(ctx, 17);
    Frame frame(ctx, 96, 5);
    S(ctx, GPR_S1, 0);
    S(ctx, GPR_S2, int_para(ctx, 0x1C5064, 0));
    S(ctx, GPR_S3, 0);
    S(ctx, GPR_S0, 0);
    S(ctx, GPR_S4, 0);
    while (slot_test(ctx, GPR_S4, 4)) {
        guest::charge(ctx, 6);
        if (persona_used(ctx, 0x1C508C, kPcKoromaru, R(ctx, GPR_S4)) != 0) {
            guest::charge(ctx, 2);
            if (R(ctx, GPR_S0) == R(ctx, GPR_S2)) {
                guest::charge(ctx, 5);
                S(ctx, GPR_A0, kPcKoromaru);
                S(ctx, GPR_A1, R(ctx, GPR_S4));
                S(ctx, GPR_S3, jal(ctx, 0x1C50AC, &rg::fn_sub_177A90_00177a90));
            }
            guest::charge(ctx, 1);
            inc(ctx, GPR_S0);
        }
        guest::charge(ctx, 1);
        inc(ctx, GPR_S4);
    }
    guest::charge(ctx, 2);
    if (R(ctx, GPR_S3) != 0) {
        guest::charge(ctx, 1);
        S(ctx, GPR_S1, lhu(ctx, R(ctx, GPR_S3)));
    }
    guest::charge(ctx, 3);
    S(ctx, GPR_S3, 0);
    while (slot_test(ctx, GPR_S3, 4)) {
        guest::charge(ctx, 13);
        if (equipment_flag(ctx, 0x1C50F0, 0x1C5108, R(ctx, GPR_S3), GPR_S4) != 0) {
            guest::charge(ctx, 2);
            if (R(ctx, GPR_S0) == R(ctx, GPR_S2)) {
                guest::charge(ctx, 5);
                S(ctx, GPR_A0, kPcKoromaru);
                S(ctx, GPR_A1, R(ctx, GPR_S4));
                S(ctx, GPR_S1, jal(ctx, 0x1C5128, &rg::fn_sub_16F630_0016f630) & 0xFFFFu);
            }
            guest::charge(ctx, 1);
            inc(ctx, GPR_S0);
        }
        guest::charge(ctx, 1);
        inc(ctx, GPR_S3);
    }
    guest::charge(ctx, 13);
    set_int(ctx, 0x1C514C, R(ctx, GPR_S1));
    return 1;
}

u32 sub_1C5180(EEContext& ctx) {
    // [473] 0x1C5180, frame 64 (s0 = slot, s1 / s2 = record and inventory slot): 8; persona slots (body 6: used -> 8:
    // record = sub_177A90(9, slot), copied to the first free inventory slot (K_Assert line 1779 when full); 1); 3;
    // equipment slots (body 13: flagged -> 8: record = sub_16FDB0(9, index), copied the same way (line 1799); 1); 8.
    guest::enter(ctx, 8);
    Frame frame(ctx, 64, 3);
    S(ctx, GPR_S0, 0);
    while (slot_test(ctx, GPR_S0, 4)) {
        guest::charge(ctx, 6);
        if (persona_used(ctx, 0x1C51A8, kPcKoromaru, R(ctx, GPR_S0)) != 0) {
            guest::charge(ctx, 8);
            S(ctx, GPR_A0, kPcKoromaru);
            S(ctx, GPR_A1, R(ctx, GPR_S0));
            S(ctx, GPR_S1, jal(ctx, 0x1C51C0, &rg::fn_sub_177A90_00177a90));
            copy_to_free_slot(ctx, GPR_S2, 0x1C51E0, 0x1C521C, 1779, 6, 0x1C5234, R(ctx, GPR_S1));
        }
        guest::charge(ctx, 1);
        inc(ctx, GPR_S0);
    }
    guest::charge(ctx, 3);
    S(ctx, GPR_S0, 0);
    while (slot_test(ctx, GPR_S0, 4)) {
        guest::charge(ctx, 13);
        if (equipment_flag(ctx, 0x1C5264, 0x1C527C, R(ctx, GPR_S0), GPR_S1) != 0) {
            guest::charge(ctx, 8);
            S(ctx, GPR_A0, kPcKoromaru);
            S(ctx, GPR_A1, R(ctx, GPR_S1));
            S(ctx, GPR_S2, jal(ctx, 0x1C5294, &rg::fn_sub_16FDB0_0016fdb0));
            copy_to_free_slot(ctx, GPR_S1, 0x1C52B4, 0x1C52F0, 1799, 6, 0x1C5308, R(ctx, GPR_S2));
        }
        guest::charge(ctx, 1);
        inc(ctx, GPR_S0);
    }
    guest::charge(ctx, 8);
    return 1;
}

u32 sub_1C4E50(EEContext& ctx) {
    // [342] 0x1C4E50, frame 64 (s0 = slot, s1 = record, s2 = inventory slot): 8; persona slots of pc arg0 (body 9:
    // sub_177A40(arg0 & 0xFFFF, slot) -> 11: record = sub_177A90(arg0 & 0xFFFF, slot), copied to the first free
    // inventory slot (K_Assert line 1682 when full; 13), then sub_177B50(arg0, slot) clears the persona slot; 1); 8.
    // arg0 is read again before each call.
    guest::enter(ctx, 8);
    Frame frame(ctx, 64, 3);
    S(ctx, GPR_S0, 0);
    while (slot_test(ctx, GPR_S0, 4)) {
        guest::charge(ctx, 9);
        const u64 pc = int_para(ctx, 0x1C4E74, 0) & 0xFFFFu;
        if (persona_used(ctx, 0x1C4E84, pc, R(ctx, GPR_S0)) != 0) {
            guest::charge(ctx, 11);
            S(ctx, GPR_A0, int_para(ctx, 0x1C4E98, 0) & 0xFFFFu);
            S(ctx, GPR_A1, R(ctx, GPR_S0));
            S(ctx, GPR_S1, jal(ctx, 0x1C4EA8, &rg::fn_sub_177A90_00177a90));
            copy_to_free_slot(ctx, GPR_S2, 0x1C4EC8, 0x1C4F04, 1682, 13, 0x1C4F1C, R(ctx, GPR_S1));
            S(ctx, GPR_A0, int_para(ctx, 0x1C4F28, 0));
            S(ctx, GPR_A1, R(ctx, GPR_S0));
            jal(ctx, 0x1C4F38, &rg::fn_sub_177B50_00177b50);
        }
        guest::charge(ctx, 1);
        inc(ctx, GPR_S0);
    }
    guest::charge(ctx, 8);
    return 1;
}

// --- party members, battle units, persona, social links ---------------------------------------------------------------

namespace {
constexpr u32 kFileScrCommand = 0x69D530u;  // the K_Assert file argument of the 0x35F / 0x360 handlers
}  // namespace

u32 sub_1C2F20(EEContext& ctx) {
    // [281] 0x1C2F20, frame 32 (s0 = pc): 15; sub_16C970((s16)pc) & 0x80000 ($v1 = the mask) -> 10: HP 1
    // (sub_16CF40) and clear status 0x80000 (sub_16D9D0) [revive a downed party member]; 6.
    guest::enter(ctx, 15);
    Frame frame(ctx, 32, 1);
    S(ctx, GPR_S0, int_para(ctx, 0x1C2F30, 0));
    S(ctx, GPR_A0, sx16(R(ctx, GPR_S0)));
    const u64 status = jal(ctx, 0x1C2F44, &rg::fn_sub_16C970_0016c970) & kStatusDown;
    S(ctx, GPR_V1, kStatusDown);
    S(ctx, GPR_V0, status);
    if (status != 0) {
        guest::charge(ctx, 10);
        S(ctx, GPR_A0, sx16(R(ctx, GPR_S0)));
        S(ctx, GPR_A1, 1);
        jal(ctx, 0x1C2F68, &rg::fn_sub_16CF40_0016cf40);
        S(ctx, GPR_A0, sx16(R(ctx, GPR_S0)));
        S(ctx, GPR_A1, kStatusDown);
        jal(ctx, 0x1C2F7C, &rg::fn_sub_16D9D0_0016d9d0);
    }
    guest::charge(ctx, 6);
    return 1;
}

u32 sub_2CD7F0(EEContext& ctx) {
    // [286] 0x2CD7F0, frame 48 (s0 = arg0 & 0xFFFF, s1 = user): 17; stage != 436 ($v1 = stage, $v0 = 436) -> 4:
    // sub_17B220(owner->u16[+164]); 30: datCalcClearEffect(dat, 13..16), then dat->u16[+4] = arg0.
    guest::enter(ctx, 17);
    Frame frame(ctx, 48, 2);
    S(ctx, GPR_S1, user_data(ctx, 0x2CD800));
    S(ctx, GPR_S0, int_para(ctx, 0x2CD810, 0) & 0xFFFFu);
    const u64 stage = lhu(ctx, lw(ctx, battle(ctx) + 3004) + 8);
    S(ctx, GPR_V1, stage);
    S(ctx, GPR_V0, kStage436);
    const u64 user = R(ctx, GPR_S1);
    if (stage != kStage436) {
        guest::charge(ctx, 4);
        const u64 owner = lw(ctx, user + 48);
        S(ctx, GPR_V0, owner);
        S(ctx, GPR_A0, lhu(ctx, owner + 164));
        jal(ctx, 0x2CD83C, &rg::fn_sub_17B220_0017b220);
    }
    guest::charge(ctx, 30);
    static constexpr u32 kPcs[4] = {0x2CD850, 0x2CD864, 0x2CD878, 0x2CD88C};
    for (u32 i = 0; i < 4; ++i) {
        const u64 owner = lw(ctx, user + 48);
        S(ctx, GPR_V0, owner);
        S(ctx, GPR_A0, lw(ctx, owner + 2604));
        S(ctx, GPR_A1, 13 + i);
        jal(ctx, kPcs[i], &rg::fn_datCalcClearEffect_00301540);
    }
    const u64 dat = lw(ctx, lw(ctx, user + 48) + 2604);
    S(ctx, GPR_V0, dat);
    guest::store<u16>(ctx, lo32(dat) + 4, static_cast<u16>(R(ctx, GPR_S0)));
    return 1;
}

u32 sub_2D03E0(EEContext& ctx) {
    // [343] 0x2D03E0, frame 160 (s0..s7, fp): 32; arg0 = minimum HP (s7), arg1 = percent (fp), arg2 = status mask
    // (s1); the party units (side byte 0, flags 1 | 8; walk test 2 first + the back-edge check, per unit 4 / 3 / 4)
    // -> 2: without 0x80000 in the mask the dead are skipped (6 + datCalcIsDead); 8: hp = datCalcGetHp & 0xFFFF (s3),
    // hp < arg0 (unsigned) skips; 15: max * percent (`mult` into $v0 and LO) < hp * 100 (unsigned) skips; 2: a mask
    // -> 7: datCalcChkBadStatus must hold; 3: hp < the best so far (s2, from 0x0FFFFFFF) -> 2: best = unit (s4);
    // 1: next. 2: a best -> 7: return its id | 0x80000000, else 3: return -1; 14.
    guest::enter(ctx, 32);
    FrameRegs frame(ctx, 160, {GPR_S0, GPR_S1, GPR_S2, GPR_S3, GPR_S4, GPR_S5, GPR_S6, GPR_S7, GPR_FP});
    S(ctx, GPR_S7, int_para(ctx, 0x2D0410, 0));
    S(ctx, GPR_FP, int_para(ctx, 0x2D0420, 1));
    S(ctx, GPR_S1, int_para(ctx, 0x2D0430, 2));
    S(ctx, GPR_S4, 0);
    S(ctx, GPR_S2, co::ori(co::lui(0x0FFF), 0xFFFF));
    S(ctx, GPR_S5, lw(ctx, battle(ctx) + 332));
    S(ctx, GPR_V0, co::lui(0x8));
    S(ctx, GPR_S6, R(ctx, GPR_S1) & co::lui(0x8));
    for (;;) {
        guest::charge(ctx, 2);
        const u64 unit = R(ctx, GPR_S5);
        if (unit == 0) break;
        guest::backedge(ctx);
        bool take = false;
        guest::charge(ctx, 4);
        const u64 flags = lhu(ctx, unit + 26);
        S(ctx, GPR_V1, flags);
        S(ctx, GPR_V0, flags & 1u);
        if ((flags & 1u) != 0) {
            guest::charge(ctx, 3);
            S(ctx, GPR_V0, flags & 8u);
            if ((flags & 8u) != 0) {
                guest::charge(ctx, 4);
                const u64 owner = lw(ctx, unit + 48);
                const u64 side = lbu(ctx, owner + 162);
                S(ctx, GPR_V1, owner);
                S(ctx, GPR_V0, side);
                if (side == 0) {
                    take = true;
                    guest::charge(ctx, 2);
                    if (R(ctx, GPR_S6) == 0) {
                        guest::charge(ctx, 6);
                        S(ctx, GPR_A0, lw(ctx, owner + 2604));
                        S(ctx, GPR_A1, 0);
                        take = jal(ctx, 0x2D049C, &rg::fn_datCalcIsDead_0030b5a0) == 0;
                    }
                }
            }
        }
        if (take) {
            guest::charge(ctx, 8);
            u64 owner = lw(ctx, unit + 48);
            S(ctx, GPR_V0, owner);
            S(ctx, GPR_A0, lw(ctx, owner + 2604));
            S(ctx, GPR_S3, jal(ctx, 0x2D04B4, &rg::fn_datCalcGetHp_002ffd70) & 0xFFFFu);
            S(ctx, GPR_AT, co::sltu(R(ctx, GPR_S3), R(ctx, GPR_S7)));
            take = R(ctx, GPR_AT) == 0;
            if (take) {
                guest::charge(ctx, 15);
                owner = lw(ctx, unit + 48);
                const u64 dat = lw(ctx, owner + 2604);
                S(ctx, GPR_V0, owner);
                S(ctx, GPR_A0, dat);
                S(ctx, GPR_S0, lhu(ctx, dat + 8));
                S(ctx, GPR_A0, jal(ctx, 0x2D04D8, &rg::fn_datCalcGetMaxHp_002ffdf0) & 0xFFFFu);
                const u64 hp = R(ctx, GPR_S0);
                const u64 x5 = co::add32(co::sll(hp, 2), hp);
                const u64 hp100 = co::sll(co::add32(x5, co::sll(x5, 2)), 2);
                S(ctx, GPR_V1, hp100);
                rt::mult(ctx, GPR_V0, GPR_A0, GPR_FP);
                S(ctx, GPR_AT, co::sltu(R(ctx, GPR_V0), hp100));
                take = R(ctx, GPR_AT) == 0;
            }
            if (take) {
                guest::charge(ctx, 2);
                if (R(ctx, GPR_S1) != 0) {
                    guest::charge(ctx, 7);
                    owner = lw(ctx, unit + 48);
                    S(ctx, GPR_V0, owner);
                    S(ctx, GPR_A0, lw(ctx, owner + 2604));
                    S(ctx, GPR_A1, R(ctx, GPR_S1));
                    take = jal(ctx, 0x2D051C, &rg::fn_datCalcChkBadStatus_00300580) != 0;
                }
            }
            if (take) {
                guest::charge(ctx, 3);
                S(ctx, GPR_AT, co::sltu(R(ctx, GPR_S3), R(ctx, GPR_S2)));
                if (R(ctx, GPR_AT) != 0) {
                    guest::charge(ctx, 2);
                    S(ctx, GPR_S4, unit);
                    S(ctx, GPR_S2, R(ctx, GPR_S3));
                }
            }
        }
        guest::charge(ctx, 1);
        S(ctx, GPR_S5, lw(ctx, unit + 1192));
    }
    guest::charge(ctx, 2);
    const u64 best = R(ctx, GPR_S4);
    if (best == 0) {
        guest::charge(ctx, 3);
        set_int(ctx, 0x2D0574, sx(0xFFFFFFFFu));
    } else {
        guest::charge(ctx, 7);
        const u64 id = lw(ctx, best + 8);
        S(ctx, GPR_V1, id);
        S(ctx, GPR_V0, co::lui(0x8000));
        set_int(ctx, 0x2D0560, id | co::lui(0x8000));
    }
    guest::charge(ctx, 14);
    return 1;
}

namespace {
// sub_2CDE10 / sub_2CDE60: (u16)btlGetMeanLevel(1 << side, 0x80000) [the average level of a side, 1 when none];
// returns -1. The side bit sits in $v0, the side in $v1.
u32 average_level(EEContext& ctx, u64 side, u32 pc_avg, u32 pc_set) {
    const u64 bit = co::sllv(1, side);
    S(ctx, GPR_V1, side);
    S(ctx, GPR_V0, bit);
    S(ctx, GPR_A0, bit & 0xFFFFu);
    S(ctx, GPR_A1, kStatusDown);
    set_int(ctx, pc_set, jal(ctx, pc_avg, &rg::fn_btlGetMeanLevel_002d4cf0) & 0xFFFFu);
    return 0xFFFFFFFFu;
}
}  // namespace

u32 sub_2CDE10(EEContext& ctx) {
    // [457] 0x2CDE10, frame 16: one block of 20: the user's own side.
    guest::enter(ctx, 20);
    Frame frame(ctx, 16, 0);
    const u64 user = user_data(ctx, 0x2CDE18);
    return average_level(ctx, lbu(ctx, lw(ctx, user + 48) + 162), 0x2CDE38, 0x2CDE44);
}

u32 sub_2CDE60(EEContext& ctx) {
    // [458] 0x2CDE60, frame 16: 8; side byte != 0 -> 1 (0) else 3 (1): the other side; 15.
    guest::enter(ctx, 8);
    Frame frame(ctx, 16, 0);
    const u64 user = user_data(ctx, 0x2CDE68);
    const u64 side = lbu(ctx, lw(ctx, user + 48) + 162);
    S(ctx, GPR_V0, side);
    u64 other;
    if (side != 0) {
        guest::charge(ctx, 1);
        other = 0;
    } else {
        guest::charge(ctx, 3);
        other = 1;
    }
    guest::charge(ctx, 15);
    return average_level(ctx, other & 0xFFFFu, 0x2CDEA4, 0x2CDEB0);
}

u32 sub_35FC70(EEContext& ctx) {
    // [497] 0x35FC70, frame 48 (s0 = stat, s1 = pc): 15; stat >= 5 -> K_Assert(410) (5); 15: sub_173BB0(pc & 0xFFFF,
    // stat & 0xFFFF, arg2) [add arg2 to a persona stat byte].
    guest::enter(ctx, 15);
    Frame frame(ctx, 48, 2);
    S(ctx, GPR_S1, int_para(ctx, 0x35FC84, 0));
    S(ctx, GPR_S0, int_para(ctx, 0x35FC94, 1));
    S(ctx, GPR_V0, co::slti(R(ctx, GPR_S0), 5));
    if (R(ctx, GPR_V0) == 0) {
        guest::charge(ctx, 5);
        S(ctx, GPR_A0, kFileScrCommand);
        S(ctx, GPR_A1, 410);
        jal(ctx, 0x35FCB8, &rg::fn_sub_19D3F0_0019d3f0);
    }
    guest::charge(ctx, 15);
    const u64 delta = int_para(ctx, 0x35FCC4, 2);
    S(ctx, GPR_A0, R(ctx, GPR_S1) & 0xFFFFu);
    S(ctx, GPR_A1, R(ctx, GPR_S0) & 0xFFFFu);
    S(ctx, GPR_A2, delta);
    jal(ctx, 0x35FCD8, &rg::fn_sub_173BB0_00173bb0);
    return 1;
}

namespace {
constexpr u32 kSocialDue = kGp - 18204;  // 0x7CE5E4: the social link index sub_360090 found
}  // namespace

u32 sub_360090(EEContext& ctx) {
    // [331] 0x360090, frame 32 ($ra at 0, the out word at sp + 28): 6; a negative message id -> K_Assert(573) (5);
    // 6: sub_172F70(&out) == 1 ($a0 = 1) -> 6: kSocialDue = out, return 1; else 3: return 0. 5.
    guest::enter(ctx, 6);
    Frame frame(ctx, 32, 0);
    if (static_cast<s64>(jal(ctx, 0x360098, &rg::fn_scrGetMessageID_0035f140)) < 0) {
        guest::charge(ctx, 5);
        S(ctx, GPR_A0, kFileScrCommand);
        S(ctx, GPR_A1, 573);
        jal(ctx, 0x3600B4, &rg::fn_sub_19D3F0_0019d3f0);
    }
    guest::charge(ctx, 6);
    const u64 out = co::add32i(R(ctx, GPR_SP), 28);
    S(ctx, GPR_A0, out);
    const u64 r = jal(ctx, 0x3600C0, &rg::fn_sub_172F70_00172f70);
    S(ctx, GPR_A0, 1);
    if (r == 1) {
        guest::charge(ctx, 6);
        const u64 index = lw(ctx, out);
        S(ctx, GPR_V0, index);
        guest::store<u32>(ctx, kSocialDue, lo32(index));
        jal(ctx, 0x3600DC, &rg::fn_scrSetIntReturnVal_0035f060);
    } else {
        guest::charge(ctx, 3);
        set_int(ctx, 0x3600F0, 0);
    }
    guest::charge(ctx, 5);
    return 1;
}

// --- battle AI conditions through the condition table (jalr) ---------------------------------------------------------

namespace {
constexpr u32 kAiConditionTbl = kAiConditions;  // 12-byte entries, word +0 = the condition function (subject, argument)

// A call through a function pointer as the original made it: $ra = the link of the `jalr` at `pc`, the target (a
// guest address, left in $v0 where the original loaded it) through rt::lookup_func. Returns $v0.
u64 jalr(EEContext& ctx, u32 pc, u64 target) {
    S(ctx, GPR_V0, target);
    rt::jalr(ctx, GPR_RA, pc);
    rt::lookup_func(lo32(target))(ctx);
    return R(ctx, GPR_V0);
}

// The condition code of the handlers: (param & 0xFFFFFF) | lui(type_hi) in $a0, type = code >> 24 in $v1, the
// argument code & 0xFFFFFF in $a1. Type 0 -> 3 ($v0 = 0); else 10: kAiConditionTbl[type](subject, argument) through
// the jalr at `pc` ($a0 = subject, $v1 = 12 * type). Returns $v0.
u64 ai_condition(EEContext& ctx, u64 subject, u64 param, u32 type_hi, u32 pc) {
    const u64 code = ((param << 40) >> 40) | co::lui(type_hi);
    const u64 type = co::srl(code & co::lui(0xFF00), 24);
    S(ctx, GPR_A0, code);
    S(ctx, GPR_V1, type);
    S(ctx, GPR_A1, (code << 40) >> 40);
    if (type == 0) {
        guest::charge(ctx, 3);
        S(ctx, GPR_V0, 0);
        return 0;
    }
    guest::charge(ctx, 10);
    const u64 off = co::sll(co::add32(co::sll(type, 1), type), 2);
    S(ctx, GPR_A0, subject);
    S(ctx, GPR_V1, off);
    return jalr(ctx, pc, lw(ctx, co::add32(sx(kAiConditionTbl), off)));
}

// sub_2CA480 .. sub_2CAF20 (frame 32, s0 = the other side, then the unit): 9; 1 / 3; 13: the other side's unit with
// id arg0 (sub_2C0E30 at base + 0x54); none -> 1 ($v0 = 0); else 14: arg1, the condition (jalr at base + 0xCC), 2;
// 9: return $v0 != 0 (scrSetIntReturnVal at base + 0xE4).
u32 other_unit_condition(EEContext& ctx, u32 base, u32 type_hi) {
    guest::enter(ctx, 9);
    Frame frame(ctx, 32, 1);
    const u64 id = other_side_head(ctx, base, 13, base + 0x38);
    const u64 unit = find_unit(ctx, base + 0x54, id, R(ctx, GPR_S0));
    S(ctx, GPR_S0, unit);
    if (unit == 0) {
        guest::charge(ctx, 1);
        S(ctx, GPR_V0, 0);
    } else {
        guest::charge(ctx, 14);
        const u64 param = int_para(ctx, base + 0x6C, 1);
        ai_condition(ctx, unit, param, type_hi, base + 0xCC);
        guest::charge(ctx, 2);
    }
    guest::charge(ctx, 9);
    set_int(ctx, base + 0xE4, R(ctx, GPR_V0) != 0 ? 1u : 0u);
    return 1;
}

// sub_2CB030 / sub_2CB0E0 (frame 32, s0 = the other side): 9; 1 / 3; 12: the other side's unit with id arg0; none ->
// 1 ($v0 = 0); else 8: the condition function at `entry` (unit, 0) through the jalr at base + 0x74; 9: return
// $v0 != 0 (base + 0x8C).
u32 other_unit_entry(EEContext& ctx, u32 base, u32 entry) {
    guest::enter(ctx, 9);
    Frame frame(ctx, 32, 1);
    const u64 id = other_side_head(ctx, base, 12, base + 0x38);
    const u64 unit = find_unit(ctx, base + 0x54, id, R(ctx, GPR_S0));
    if (unit == 0) {
        guest::charge(ctx, 1);
        S(ctx, GPR_V0, 0);
    } else {
        guest::charge(ctx, 8);
        S(ctx, GPR_A0, unit);
        S(ctx, GPR_A1, 0);
        jalr(ctx, base + 0x74, lw(ctx, entry));
    }
    guest::charge(ctx, 9);
    set_int(ctx, base + 0x8C, R(ctx, GPR_V0) != 0 ? 1u : 0u);
    return 1;
}

// sub_2CBA00 / sub_2CBA50 / sub_2CBAA0, frame 16: one block of 18: the condition function at `entry` (user, 0)
// through the jalr at base + 0x20; return $v0 != 0 (base + 0x2C).
u32 user_entry(EEContext& ctx, u32 base, u32 entry) {
    guest::enter(ctx, 18);
    Frame frame(ctx, 16, 0);
    S(ctx, GPR_A0, user_data(ctx, base + 0x8));
    S(ctx, GPR_A1, 0);
    set_int(ctx, base + 0x2C, jalr(ctx, base + 0x20, lw(ctx, entry)) != 0 ? 1u : 0u);
    return 1;
}
}  // namespace

u32 sub_2CA480(EEContext& ctx) { return other_unit_condition(ctx, 0x2CA480, 0x0100); }  // [344] type 0x01
u32 sub_2CA590(EEContext& ctx) { return other_unit_condition(ctx, 0x2CA590, 0x0200); }  // [345] type 0x02
u32 sub_2CA6A0(EEContext& ctx) { return other_unit_condition(ctx, 0x2CA6A0, 0x0600); }  // [346] type 0x06
u32 sub_2CA9D0(EEContext& ctx) { return other_unit_condition(ctx, 0x2CA9D0, 0x1600); }  // [349] type 0x16
u32 sub_2CAAE0(EEContext& ctx) { return other_unit_condition(ctx, 0x2CAAE0, 0x1700); }  // [350] type 0x17
u32 sub_2CABF0(EEContext& ctx) { return other_unit_condition(ctx, 0x2CABF0, 0x1800); }  // [351] type 0x18
u32 sub_2CAD00(EEContext& ctx) { return other_unit_condition(ctx, 0x2CAD00, 0x1900); }  // [352] type 0x19
u32 sub_2CAE10(EEContext& ctx) { return other_unit_condition(ctx, 0x2CAE10, 0x2200); }  // [353] type 0x22
u32 sub_2CAF20(EEContext& ctx) { return other_unit_condition(ctx, 0x2CAF20, 0x2500); }  // [354] type 0x25
u32 sub_2CB030(EEContext& ctx) { return other_unit_entry(ctx, 0x2CB030, kAiConditionTbl + 12 * 40); }  // [355] entry 40
u32 sub_2CB0E0(EEContext& ctx) { return other_unit_entry(ctx, 0x2CB0E0, kAiConditionTbl + 12 * 45); }  // [356] entry 45
u32 sub_2CBA00(EEContext& ctx) { return user_entry(ctx, 0x2CBA00, kAiConditionTbl + 12 * 67); }  // [299] entry 67
u32 sub_2CBA50(EEContext& ctx) { return user_entry(ctx, 0x2CBA50, kAiConditionTbl + 12 * 68); }  // [300] entry 68
u32 sub_2CBAA0(EEContext& ctx) { return user_entry(ctx, 0x2CBAA0, kAiConditionTbl + 12 * 69); }  // [301] entry 69

}  // namespace p3fes::game

// --- the recompiled program's entry points (signatures from recomp/generated/functions.h) ---------------------------
namespace p3fes::recomp_gen {

using namespace p3fes::game;

#define P3FES_COMM_B2_SHIM(name, addr) \
    void fn_##name##_##addr(p3fes::EEContext& ctx) { guest::ret32(ctx, name(ctx)); }
P3FES_COMM_B2_SHIM(sub_2CE440, 002ce440)
P3FES_COMM_B2_SHIM(sub_2CBCD0, 002cbcd0)
P3FES_COMM_B2_SHIM(sub_2CBD90, 002cbd90)
P3FES_COMM_B2_SHIM(sub_2CBE50, 002cbe50)
P3FES_COMM_B2_SHIM(sub_2CBF10, 002cbf10)
P3FES_COMM_B2_SHIM(sub_2CDA50, 002cda50)
P3FES_COMM_B2_SHIM(sub_2CDAD0, 002cdad0)
P3FES_COMM_B2_SHIM(sub_2CA900, 002ca900)
P3FES_COMM_B2_SHIM(sub_2D12E0, 002d12e0)
P3FES_COMM_B2_SHIM(sub_2CC330, 002cc330)
P3FES_COMM_B2_SHIM(sub_2CF9F0, 002cf9f0)
P3FES_COMM_B2_SHIM(sub_2CDED0, 002cded0)
P3FES_COMM_B2_SHIM(sub_2D06E0, 002d06e0)
P3FES_COMM_B2_SHIM(sub_2D0720, 002d0720)
P3FES_COMM_B2_SHIM(sub_2D0B90, 002d0b90)
P3FES_COMM_B2_SHIM(sub_2D0BD0, 002d0bd0)
P3FES_COMM_B2_SHIM(sub_2D0C10, 002d0c10)
P3FES_COMM_B2_SHIM(sub_2D0C80, 002d0c80)
P3FES_COMM_B2_SHIM(sub_2D0860, 002d0860)
P3FES_COMM_B2_SHIM(sub_2D0970, 002d0970)
P3FES_COMM_B2_SHIM(sub_2D0AC0, 002d0ac0)
P3FES_COMM_B2_SHIM(sub_2D0C50, 002d0c50)
P3FES_COMM_B2_SHIM(sub_2D11D0, 002d11d0)
P3FES_COMM_B2_SHIM(sub_2D1260, 002d1260)
P3FES_COMM_B2_SHIM(sub_2D12A0, 002d12a0)
P3FES_COMM_B2_SHIM(sub_1C5670, 001c5670)
P3FES_COMM_B2_SHIM(sub_425360, 00425360)
P3FES_COMM_B2_SHIM(sub_4254C0, 004254c0)
P3FES_COMM_B2_SHIM(sub_425530, 00425530)
P3FES_COMM_B2_SHIM(sub_425580, 00425580)
P3FES_COMM_B2_SHIM(sub_4255D0, 004255d0)
P3FES_COMM_B2_SHIM(sub_425640, 00425640)
P3FES_COMM_B2_SHIM(sub_1C5460, 001c5460)
P3FES_COMM_B2_SHIM(sub_35FD80, 0035fd80)
P3FES_COMM_B2_SHIM(sub_4244E0, 004244e0)
P3FES_COMM_B2_SHIM(sub_4245C0, 004245c0)
P3FES_COMM_B2_SHIM(sub_424730, 00424730)
P3FES_COMM_B2_SHIM(sub_424880, 00424880)
P3FES_COMM_B2_SHIM(sub_4249B0, 004249b0)
P3FES_COMM_B2_SHIM(sub_1C4F70, 001c4f70)
P3FES_COMM_B2_SHIM(sub_1C5040, 001c5040)
P3FES_COMM_B2_SHIM(sub_1C5180, 001c5180)
P3FES_COMM_B2_SHIM(sub_1C4E50, 001c4e50)
P3FES_COMM_B2_SHIM(sub_1C2F20, 001c2f20)
P3FES_COMM_B2_SHIM(sub_2CD7F0, 002cd7f0)
P3FES_COMM_B2_SHIM(sub_2D03E0, 002d03e0)
P3FES_COMM_B2_SHIM(sub_2CDE10, 002cde10)
P3FES_COMM_B2_SHIM(sub_2CDE60, 002cde60)
P3FES_COMM_B2_SHIM(sub_35FC70, 0035fc70)
P3FES_COMM_B2_SHIM(sub_360090, 00360090)
P3FES_COMM_B2_SHIM(sub_2CA480, 002ca480)
P3FES_COMM_B2_SHIM(sub_2CA590, 002ca590)
P3FES_COMM_B2_SHIM(sub_2CA6A0, 002ca6a0)
P3FES_COMM_B2_SHIM(sub_2CA9D0, 002ca9d0)
P3FES_COMM_B2_SHIM(sub_2CAAE0, 002caae0)
P3FES_COMM_B2_SHIM(sub_2CABF0, 002cabf0)
P3FES_COMM_B2_SHIM(sub_2CAD00, 002cad00)
P3FES_COMM_B2_SHIM(sub_2CAE10, 002cae10)
P3FES_COMM_B2_SHIM(sub_2CAF20, 002caf20)
P3FES_COMM_B2_SHIM(sub_2CB030, 002cb030)
P3FES_COMM_B2_SHIM(sub_2CB0E0, 002cb0e0)
P3FES_COMM_B2_SHIM(sub_2CBA00, 002cba00)
P3FES_COMM_B2_SHIM(sub_2CBA50, 002cba50)
P3FES_COMM_B2_SHIM(sub_2CBAA0, 002cbaa0)
#undef P3FES_COMM_B2_SHIM

}  // namespace p3fes::recomp_gen
