// BF script COMM handlers, table indices 0-250 (game/include/p3fes/game/comm_a.h), hand-decompiled from
// SLUS_216.21 (docs/ANALYSIS/18_script_vm.md section 2.4). tests/game/test_script_comm_a.cpp runs each against
// its __recomp body.
//
// Fidelity. Every handler mirrors the recompiled body exactly, down to the guest stack:
// * virtual time (ADR-0013): guest::enter / charge / backedge follow the `ctx.cycles += N` blocks and the check
//   points of the generated body; a block is charged at its start, before the callees it contains run;
// * the frame: `Frame` performs the original prologue and epilogue (`addiu sp; sd ra; sq sN` ... `ld ra; lq sN;
//   addiu sp`), so the spill slots hold what the original stored, and the callees' frames land where they did;
// * calls: every callee -- still recompiled or already replaced -- is entered through its generated symbol with
//   $ra = the original link (`jal` at `pc`) and the argument registers the original set, as 64-bit register values
//   (`move a0, s0` forwards the whole register; `dsll32/dsra32 x, 16` is a sign extension from 16 bits);
// * callee-saved registers: where the original keeps a value in $sN across a call, `keep` puts it there, so a
//   callee that spills $sN writes the same bytes into its frame as in the original.
// Scratch registers left behind after the last call (an address in $v1, an `slt` result in $at) are not
// reproduced: the handlers are referenced only by the COMM table, and CodeFunc_Comm reads $v0 alone after its
// jalr. K_Assert sub_19D3F0 is `jr $ra` in retail: a failed check goes on.
//
// Not replaced from indices 0-250, and why (the pure part of the range is here; the rest):
// * printf / H_Dbprt on a reachable path: scrCommand_PUT 0x35B090 [16], sub_35B0D0 [18], scrCommand_SCR_RUN
//   0x35B280 [23] (+ scrCreateTask -> H_Malloc), sub_3A2B30 [28], sub_35F170 [123], sub_1C37C0 [216], sub_1C3820
//   [217] (the field-object helpers print and reach H_Malloc), sub_3604A0 [234];
// * the MW heap (H_Malloc sub_191AF0 / H_Free, DIntr/EIntr syscalls): scrCommand_SCR_KILL 0x35B390 [24],
//   sub_1C25B0 [13] (newlib malloc via sub_1085C0), sub_1C2010 [33] / sub_1C2340 [120] / sub_1C2160 [118] /
//   sub_424310 [119] / sub_35F7A0 [181] (field/event task creation: kwlnTaskCreate, memset), sub_424370 [188],
//   sub_1C2480 [214], sub_1C3AD0 [231], btlScrCmd_CALL_BATTLE 0x27D5E0 [148] and sub_27D730 [166] (unit creation,
//   scrCreateTaskFromScriptMemory);
// * file loading (H_Cdvd / ADXF / ROFS): sub_1C2580 [126];
// * the sound library (0x4C.... band, IOP RPC): sub_350200 [146]; sub_1C2900 [137], sub_1C2B80 [233] and
//   sub_3971A0 [182] / sub_3973E0 [183] drive 3D objects and models (rendering);
// * the message windows (itfMesManager, frFont glyph building and rendering): scrCommand_MSG 0x3A2150 [0],
//   sub_3A2900 [1], sub_3A2970 [2], sub_3A2660 [3], sub_3A28A0 [6], sub_3A2260 [38], sub_3A2440 [39], sub_3A2C10 [40],
//   sub_35F5B0 [125], sub_35F880 [207], sub_35F680 [221], sub_35F730 [222], sub_35FDB0 [223];
// * rendering / camera / UI panels: sub_40D410 [42], sub_40D490 [43], sub_40D540 [44], sub_38D980 [184],
//   sub_3BD230 [185], sub_1C2550 [122] (a task-driven field effect: jalr through adminiChangeSeq);
// * the battle-AI command family through scrGetUserData (the AI action object), 0x2C7300-0x2CE090 and 0x2D13C0,
//   about 110 handlers in [51..117], [139..144], [149..180], [235..250]: each dispatches through the AI condition /
//   action tables 0x6971B0 (12-byte entries) and 0x6975E0 (8-byte entries) with a jalr whose targets need real
//   AI action objects to test; they are one template and are left for a dedicated pass (docs: 21_battle.md
//   section 4, "the btlAI* COMM set").
// * already replaced by script_vm2: [7..12], [15], [19..22], [25..27], [46]; sub_311180 [49] by battle_data.
//
// Faithfulness audit (2026-10-21, tools/ours/audit): 23 of the 56 functions here are now p3fes_handgen's register-
// faithful bodies (their hand versions differed from the original: $v0 17, scratch GPRs 5, logic 1); each keeps the
// notes of its earlier hand version above it. The others are the hand-written versions this header describes.
#include "p3fes/game/comm_a.h"

#include "p3fes/ee/core.h"
#include "p3fes/game/guest.h"
#include "p3fes/game/script_vm.h"

#include <initializer_list>
#include "p3fes/game/hg_cpu.h"

namespace p3fes::recomp_gen {
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);  // K_Assert(file, line): `jr $ra` in retail
// already replaced (game/src/script/script_ops.cpp)
void fn_scrGetIntPara_0035ed20(p3fes::EEContext&);
void fn_scrSetIntReturnVal_0035f060(p3fes::EEContext&);
void fn_scrSetFloatReturnVal_0035f080(p3fes::EEContext&);
// the game-state callees (still recompiled, or replaced by other slices: the symbol reaches whichever is live)
void fn_sub_108570_00108570(p3fes::EEContext&);
void fn_sub_108670_00108670(p3fes::EEContext&);
void fn_sub_1086A0_001086a0(p3fes::EEContext&);
void fn_sub_108710_00108710(p3fes::EEContext&);
void fn_clndGetCurrentMonth_0017d920(p3fes::EEContext&);
void fn_clndGetCurrentDay_0017da40(p3fes::EEContext&);
void fn_clndGetCurrentWeekDay_0017db00(p3fes::EEContext&);
void fn_datGetTime_0016ef30(p3fes::EEContext&);
void fn_clndIsDateInRange_0017e480(p3fes::EEContext&);
void fn_sub_103C30_00103c30(p3fes::EEContext&);
void fn_sub_103CB0_00103cb0(p3fes::EEContext&);
void fn_K_FldDungeon_GetCurrentFloor_001bff20(p3fes::EEContext&);
void fn_datCalcRestorePartyAll_0030c440(p3fes::EEContext&);
void fn_sub_16C470_0016c470(p3fes::EEContext&);
void fn_sub_16C4F0_0016c4f0(p3fes::EEContext&);
void fn_sub_16C570_0016c570(p3fes::EEContext&);
void fn_sub_16C5F0_0016c5f0(p3fes::EEContext&);
void fn_sub_16C670_0016c670(p3fes::EEContext&);
void fn_sub_16C6F0_0016c6f0(p3fes::EEContext&);
void fn_sub_16C740_0016c740(p3fes::EEContext&);
void fn_sub_16C790_0016c790(p3fes::EEContext&);
void fn_sub_16C7E0_0016c7e0(p3fes::EEContext&);
void fn_sub_16C920_0016c920(p3fes::EEContext&);
void fn_sub_16C970_0016c970(p3fes::EEContext&);
void fn_sub_16C9F0_0016c9f0(p3fes::EEContext&);
void fn_sub_16CA40_0016ca40(p3fes::EEContext&);
void fn_sub_16D6B0_0016d6b0(p3fes::EEContext&);
void fn_datGetEquipmentIdx_0016cb80(p3fes::EEContext&);
void fn_sub_16F630_0016f630(p3fes::EEContext&);
void fn_sub_16DA50_0016da50(p3fes::EEContext&);
void fn_sub_175360_00175360(p3fes::EEContext&);
void fn_sub_174710_00174710(p3fes::EEContext&);
void fn_K_Fld_GetPhase_001b9130(p3fes::EEContext&);
void fn_sub_16E100_0016e100(p3fes::EEContext&);
void fn_sub_16DCE0_0016dce0(p3fes::EEContext&);
void fn_sub_16DBA0_0016dba0(p3fes::EEContext&);
void fn_sub_1717C0_001717c0(p3fes::EEContext&);
void fn_sub_172160_00172160(p3fes::EEContext&);
void fn_sub_172E50_00172e50(p3fes::EEContext&);
void fn_sub_1831E0_001831e0(p3fes::EEContext&);
void fn_sub_170760_00170760(p3fes::EEContext&);
void fn_sub_170860_00170860(p3fes::EEContext&);
void fn_sub_1A0150_001a0150(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {

namespace rg = recomp_gen;
using namespace comm_a;
using guest::Fn;

// --- registers ------------------------------------------------------------------------------------------------
u64 reg(const EEContext& ctx, unsigned r) { return ee::core::gpr64(ctx, r); }
void set_reg(EEContext& ctx, unsigned r, u64 v) { ee::core::set_gpr64(ctx, r, v); }
u64 sx(u32 v) { return ee::core::sext32(v); }
u64 sx16(u64 v) { return static_cast<u64>(static_cast<s64>(static_cast<s16>(static_cast<u16>(v)))); }  // dsll32/dsra32 16
u64 sx8(u64 v) { return static_cast<u64>(static_cast<s64>(static_cast<s8>(static_cast<u8>(v)))); }     // dsll32/dsra32 24

// The original keeps `v` in callee-saved register `r` across the calls that follow.
void keep(EEContext& ctx, unsigned r, u64 v) { set_reg(ctx, r, v); }

// A call as the original made it: arguments in $a0.. (64-bit register values; the other registers stay as they
// are), `jal` at `pc` ($ra = pc + 8), the callee through its generated symbol. Returns $v0.
u64 jal(EEContext& ctx, u32 pc, Fn fn, std::initializer_list<u64> args = {}) {
    unsigned r = GPR_A0;
    for (u64 a : args) set_reg(ctx, r++, a);
    rt::jal(ctx, pc);
    fn(ctx);
    return reg(ctx, GPR_V0);
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
    u32 at(u32 off) const noexcept { return ee::core::gpr32(ctx_, GPR_SP) + off; }

private:
    EEContext& ctx_;
    s32 size_;
    unsigned saved_;
};

// scrGetIntPara(i) / scrSetIntReturnVal(v) at a call site.
u64 int_para(EEContext& ctx, u32 pc, u64 i) { return jal(ctx, pc, &rg::fn_scrGetIntPara_0035ed20, {i}); }
void set_int(EEContext& ctx, u32 pc, u64 v) { jal(ctx, pc, &rg::fn_scrSetIntReturnVal_0035f060, {v}); }
// The K_Assert block: 5 cycles (`lui/addiu a0, file; addiu a1, line; jal`) and the no-op call.
void k_assert(EEContext& ctx, u32 pc, u32 file, u32 line) {
    guest::charge(ctx, 5);
    jal(ctx, pc, &rg::fn_sub_19D3F0_0019d3f0, {sx(file), line});
}

// Guest words.
u32 lwu(const EEContext& ctx, u32 va) { return guest::load<u32>(ctx, va); }

// The handlers that only forward one value to scrSetIntReturnVal: frame 16, one block of `cycles`, the getter
// (no arguments) at `pc_get`, scrSetIntReturnVal(v & mask) at `pc_set`.
u32 return_getter(EEContext& ctx, u32 cycles, u32 pc_get, Fn getter, u32 pc_set, u64 mask) {
    guest::enter(ctx, cycles);
    Frame frame(ctx, 16, 0);
    set_int(ctx, pc_set, jal(ctx, pc_get, getter) & mask);
    return 1;
}
constexpr u64 kAll = ~u64{0};

// The member getters [192..203]: frame 16, one block of 17: scrGetIntPara(0) at base + 0xC, the getter of
// (s16)arg0 at base + 0x1C, scrSetIntReturnVal(result & mask) at base + 0x28.
u32 member_getter(EEContext& ctx, u32 base, Fn getter, u64 mask) {
    guest::enter(ctx, 17);
    Frame frame(ctx, 16, 0);
    const u64 who = int_para(ctx, base + 0xC, 0);
    set_int(ctx, base + 0x28, jal(ctx, base + 0x1C, getter, {sx16(who)}) & mask);
    return 1;
}

// sub_360300 / sub_3603D0: frame 32 (s0). 13: arg0, assert sub_16DCE0((s16)arg0); 6: sub_16E100((s16)arg0);
// zero -> 6, return 0; else 6: test(arg0) == 1 -> 4, return 1; else 3, return 0; then 1. Epilogue 5.
u32 persona_check(EEContext& ctx, u32 base, Fn test, u32 line) {
    guest::enter(ctx, 13);
    Frame frame(ctx, 32, 1);
    const u64 id = int_para(ctx, base + 0x10, 0);
    keep(ctx, GPR_S0, id);
    if (jal(ctx, base + 0x24, &rg::fn_sub_16DCE0_0016dce0, {sx16(id)}) == 0) k_assert(ctx, base + 0x40, kFileScrCommand, line);
    guest::charge(ctx, 6);
    if (jal(ctx, base + 0x50, &rg::fn_sub_16E100_0016e100, {sx16(id)}) == 0) {
        guest::charge(ctx, 6);
        set_int(ctx, base + 0x64, 0);
    } else {
        guest::charge(ctx, 6);
        if (jal(ctx, base + 0x7C, test, {id}) == 1) {
            guest::charge(ctx, 4);
            set_int(ctx, base + 0x90, 1);
        } else {
            guest::charge(ctx, 3);
            set_int(ctx, base + 0xA4, 0);
        }
        guest::charge(ctx, 1);
    }
    guest::charge(ctx, 5);
    return 1;
}

}  // namespace

// --- field / event commands (0x1C2xxx band) ---------------------------------------------------------------------

u32 sub_1C2500(EEContext& ctx) {
    // [121] argc 2. 0x1C2500, frame 32 (s0): one block of 20.
    guest::enter(ctx, 20);
    Frame frame(ctx, 32, 1);
    const u64 id = int_para(ctx, 0x1C2510, 0);
    keep(ctx, GPR_S0, id);
    const u64 on = int_para(ctx, 0x1C2520, 1);
    jal(ctx, 0x1C2530, &rg::fn_sub_1A0150_001a0150, {id & 0xFFFF, on});
    return 1;
}

u32 sub_1C2610(EEContext& ctx) {
    // [14] argc 2. 0x1C2610, frame 48 (s0, s1): 20; arg1 != 0 -> 4 (sub_1086A0); 7.
    guest::enter(ctx, 20);
    Frame frame(ctx, 48, 2);
    const u64 a = int_para(ctx, 0x1C2624, 0);
    keep(ctx, GPR_S1, a);
    const u64 b = int_para(ctx, 0x1C2634, 1);
    keep(ctx, GPR_S0, b);
    jal(ctx, 0x1C2640, &rg::fn_sub_108570_00108570);
    jal(ctx, 0x1C2650, &rg::fn_sub_108670_00108670, {sx16(a)});
    if (b != 0) {
        guest::charge(ctx, 4);
        jal(ctx, 0x1C2668, &rg::fn_sub_1086A0_001086a0, {sx16(b)});
    }
    guest::charge(ctx, 7);
    return 1;
}

u32 sub_1C2690(EEContext& ctx) {
    // [127] argc 0. 0x1C2690, frame 16: one block of 9; `sltu v0, zero, v0` on the whole register.
    guest::enter(ctx, 9);
    Frame frame(ctx, 16, 0);
    return jal(ctx, 0x1C2698, &rg::fn_sub_108710_00108710) != 0 ? 1u : 0u;
}

u32 sub_1C26C0(EEContext& ctx) { return return_getter(ctx, 12, 0x1C26C8, &rg::fn_clndGetCurrentMonth_0017d920, 0x1C26D4, kAll); }    // [128]
u32 sub_1C26F0(EEContext& ctx) { return return_getter(ctx, 12, 0x1C26F8, &rg::fn_clndGetCurrentDay_0017da40, 0x1C2704, kAll); }      // [129]
u32 sub_1C2720(EEContext& ctx) { return return_getter(ctx, 12, 0x1C2728, &rg::fn_clndGetCurrentWeekDay_0017db00, 0x1C2734, kAll); }  // [130]
u32 sub_1C2750(EEContext& ctx) { return return_getter(ctx, 12, 0x1C2758, &rg::fn_datGetTime_0016ef30, 0x1C2764, 0xFF); }             // [131]

u32 sub_1C2780(EEContext& ctx) {
    // [132] argc 4. 0x1C2780, frame 64 (s0..s2): 29; result == 1 -> 4, return 1 (the `li a0, 1` of the compare);
    // else 3, return 0; 8.
    guest::enter(ctx, 29);
    Frame frame(ctx, 64, 3);
    const u64 a = int_para(ctx, 0x1C2798, 0);
    keep(ctx, GPR_S2, a);
    const u64 b = int_para(ctx, 0x1C27A8, 1);
    keep(ctx, GPR_S1, b);
    const u64 c = int_para(ctx, 0x1C27B8, 2);
    keep(ctx, GPR_S0, c);
    const u64 d = int_para(ctx, 0x1C27C8, 3);
    if (jal(ctx, 0x1C27E0, &rg::fn_clndIsDateInRange_0017e480, {a, b, c, d}) == 1) {
        guest::charge(ctx, 4);
        set_int(ctx, 0x1C27F4, 1);
    } else {
        guest::charge(ctx, 3);
        set_int(ctx, 0x1C2808, 0);
    }
    guest::charge(ctx, 8);
    return 1;
}

u32 sub_1C2830(EEContext& ctx) {
    // [135] argc 4. 0x1C2830, frame 64 (s0..s2): one block of 38. sub_103C30 spills s0..s3.
    guest::enter(ctx, 38);
    Frame frame(ctx, 64, 3);
    const u64 a = int_para(ctx, 0x1C2848, 0);
    keep(ctx, GPR_S2, a);
    const u64 b = int_para(ctx, 0x1C2858, 1);
    keep(ctx, GPR_S1, b);
    const u64 c = int_para(ctx, 0x1C2868, 2);
    keep(ctx, GPR_S0, c);
    const u64 d = int_para(ctx, 0x1C2878, 3);
    jal(ctx, 0x1C28A0, &rg::fn_sub_103C30_00103c30, {sx16(a), sx16(b), sx16(c), sx16(d)});
    return 1;
}

u32 sub_1C28D0(EEContext& ctx) {
    // [136] argc 0. 0x1C28D0, frame 16: one block of 9.
    guest::enter(ctx, 9);
    Frame frame(ctx, 16, 0);
    jal(ctx, 0x1C28D8, &rg::fn_sub_103CB0_00103cb0);
    return 1;
}

u32 sub_1C2EA0(EEContext& ctx) { return return_getter(ctx, 12, 0x1C2EA8, &rg::fn_K_FldDungeon_GetCurrentFloor_001bff20, 0x1C2EB4, kAll); }  // [138]

// --- party member / social-stat getters [192..205] --------------------------------------------------------------

u32 sub_1C2ED0(EEContext& ctx) { return member_getter(ctx, 0x1C2ED0, &rg::fn_sub_16C470_0016c470, 0xFF); }    // [192]
u32 sub_1C2FA0(EEContext& ctx) { return member_getter(ctx, 0x1C2FA0, &rg::fn_sub_16C4F0_0016c4f0, 0xFFFF); }  // [193]
u32 sub_1C3050(EEContext& ctx) { return member_getter(ctx, 0x1C3050, &rg::fn_sub_16C5F0_0016c5f0, 0xFFFF); }  // [194]
u32 sub_1C30A0(EEContext& ctx) { return member_getter(ctx, 0x1C30A0, &rg::fn_sub_16C570_0016c570, 0xFFFF); }  // [195]
u32 sub_1C3150(EEContext& ctx) { return member_getter(ctx, 0x1C3150, &rg::fn_sub_16C670_0016c670, 0xFFFF); }  // [196]
u32 sub_1C3370(EEContext& ctx) { return member_getter(ctx, 0x1C3370, &rg::fn_sub_16C9F0_0016c9f0, 0xFFFF); }  // [198]
u32 sub_1C33C0(EEContext& ctx) { return member_getter(ctx, 0x1C33C0, &rg::fn_sub_16CA40_0016ca40, 0xFFFF); }  // [199]
u32 sub_1C3410(EEContext& ctx) { return member_getter(ctx, 0x1C3410, &rg::fn_sub_16C7E0_0016c7e0, kAll); }    // [200]
u32 sub_1C3460(EEContext& ctx) { return member_getter(ctx, 0x1C3460, &rg::fn_sub_16C920_0016c920, 0xFFFF); }  // [201]
u32 sub_1C3540(EEContext& ctx) { return member_getter(ctx, 0x1C3540, &rg::fn_sub_16C970_0016c970, kAll); }    // [203]

// 0x001C31A0 sub_1C31A0 -- 204 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [197] argc 2. 0x1C31A0, frame 32 (s0): 14; the selector against 2 / 1 / 0 (3, 2 more per failed compare);
// sel 2 -> 6, sel 1 / 0 -> 8 (the points getter, result sign-extended from 16 bits); no match -> 2 and the
// `move a0, zero` value; then 8 (scrSetIntReturnVal).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: scratch GPRs):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1C31A0_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld, hg::lq, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001c31a0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x1C31B0u, gen::fn_scrGetIntPara_0035ed20);
    s0 = v0;
    a0 = 1;
    jal(ctx, 0x1C31C0u, gen::fn_scrGetIntPara_0035ed20);
    a0 = 0;
    v1 = 2;
    if (v0 == v1) {
        // 0x001c3234
        charge(ctx, 6);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x1C323Cu, gen::fn_sub_16C790_0016c790);
        a0 = dsll32(v0, 16);
        a0 = dsra32(a0, 16);
    } else {
        // 0x001c31d8
        charge(ctx, 3);
        v1 = 1;
        if (v0 == v1) {
            // 0x001c3214
            charge(ctx, 8);
            a0 = dsll32(s0, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x1C321Cu, gen::fn_sub_16C740_0016c740);
            a0 = dsll32(v0, 16);
            a0 = dsra32(a0, 16);
        } else {
            // 0x001c31e4
            charge(ctx, 2);
            if (v0 == 0) {
                // 0x001c31f4
                charge(ctx, 8);
                a0 = dsll32(s0, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x1C31FCu, gen::fn_sub_16C6F0_0016c6f0);
                a0 = dsll32(v0, 16);
                a0 = dsra32(a0, 16);
            } else {
                // 0x001c31ec
                charge(ctx, 2);
            }
        }
    }
    // 0x001c324c
    charge(ctx, 8);
    jal(ctx, 0x1C324Cu, gen::fn_scrSetIntReturnVal_0035f060);
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001C34B0 sub_1C34B0 -- 132 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [202] argc 2. 0x1C34B0, frame 48 (s0, s1): one block of 33.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: $v0):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1C34B0_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld, hg::lq, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001c34b0
    enter(ctx, 33);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x1C34C4u, gen::fn_scrGetIntPara_0035ed20);
    s1 = v0;
    a0 = 1;
    jal(ctx, 0x1C34D4u, gen::fn_scrGetIntPara_0035ed20);
    s0 = v0;
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x1C34E8u, gen::fn_sub_16C920_0016c920);
    a0 = v0 & 0xFFFF;
    jal(ctx, 0x1C34F4u, gen::fn_scrSetIntReturnVal_0035f060);
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    v0 = dsll32(s0, 16);
    v0 = dsra32(v0, 16);
    a1 = v0 & 0xFFFF;
    jal(ctx, 0x1C3510u, gen::fn_sub_16D6B0_0016d6b0);
    v0 = 1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

u32 sub_1C3690(EEContext& ctx) {
    // [204] argc 2. 0x1C3690, frame 32 (s0): one block of 31.
    guest::enter(ctx, 31);
    Frame frame(ctx, 32, 1);
    const u64 who = int_para(ctx, 0x1C36A0, 0);
    keep(ctx, GPR_S0, who);
    const u64 slot = int_para(ctx, 0x1C36B0, 1);
    const u64 idx = jal(ctx, 0x1C36C8, &rg::fn_datGetEquipmentIdx_0016cb80, {sx16(who), sx16(slot)});
    set_int(ctx, 0x1C36EC, jal(ctx, 0x1C36E0, &rg::fn_sub_16F630_0016f630, {sx16(who), sx16(idx)}) & 0xFFFF);
    return 1;
}

u32 sub_1C3710(EEContext& ctx) {
    // [205] argc 3. 0x1C3710, frame 48 (s0, s1): one block of 30.
    guest::enter(ctx, 30);
    Frame frame(ctx, 48, 2);
    const u64 a = int_para(ctx, 0x1C3724, 0);
    keep(ctx, GPR_S1, a);
    const u64 b = int_para(ctx, 0x1C3734, 1);
    keep(ctx, GPR_S0, b);
    const u64 c = int_para(ctx, 0x1C3744, 2);
    jal(ctx, 0x1C3764, &rg::fn_sub_16DA50_0016da50, {sx16(a), sx16(b), sx16(c)});
    return 1;
}

u32 sub_1C3790(EEContext& ctx) { return return_getter(ctx, 12, 0x1C3798, &rg::fn_K_Fld_GetPhase_001b9130, 0x1C37A4, kAll); }  // [215]

// --- the dungeon floor record [226..232] ------------------------------------------------------------------------

// 0x001C3880 sub_1C3880 -- 44 bytes; frame 0x10: ra sp+0x0
// [226] argc 0. 0x1C3880, frame 16: one block of 11.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: $v0):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1C3880_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lw, hg::sd;
    Gpr v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001c3880
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, -19052);  // 0x7CE284
    lhu(a0, v0, 8);
    jal(ctx, 0x1C3890u, gen::fn_scrSetIntReturnVal_0035f060);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001C38B0 sub_1C38B0 -- 156 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [227] argc 0. 0x1C38B0, frame 32 (s0 = the field record): 9; floor 4021 -> 3 (return 3); 5 (the floor id
// read again); >= 5000 -> 5 (0); else 3: >= 4000 -> 5 (1), else 3 (2); 6. (4021 sets 3 and then 1.)
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: $v0):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1C38B0_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lq, hg::lw, hg::sd, hg::slti,
          hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001c38b0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, gp, -19052);  // 0x7CE284
    lw(v0, s0, 284);
    lhu(v1, v0, 2);
    v0 = 4021;
    if (v1 == v0) {
        // 0x001c38d4
        charge(ctx, 3);
        a0 = 3;
        jal(ctx, 0x1C38D8u, gen::fn_scrSetIntReturnVal_0035f060);
    }
    // 0x001c38e0
    charge(ctx, 5);
    lw(v0, s0, 284);
    lhu(v1, v0, 2);
    v0 = slti(v1, 5000);
    if (v0 != 0) {
        // 0x001c3908
        charge(ctx, 3);
        v0 = slti(v1, 4000);
        if (v0 != 0) {
            // 0x001c3928
            charge(ctx, 3);
            a0 = 2;
            jal(ctx, 0x1C392Cu, gen::fn_scrSetIntReturnVal_0035f060);
        } else {
            // 0x001c3914
            charge(ctx, 5);
            a0 = 1;
            jal(ctx, 0x1C3918u, gen::fn_scrSetIntReturnVal_0035f060);
        }
    } else {
        // 0x001c38f4
        charge(ctx, 5);
        a0 = 0;
        jal(ctx, 0x1C38F8u, gen::fn_scrSetIntReturnVal_0035f060);
    }
    // 0x001c3934 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001C39E0 sub_1C39E0 -- 48 bytes; frame 0x10: ra sp+0x0
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: $v0):
// p3fes_handgen's body, statement for statement the original's.
void sub_1C39E0_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lw, hg::sd;
    Gpr v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001c39e0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, -19052);  // 0x7CE284
    lw(v0, v0, 284);
    lhu(a0, v0, 2);
    jal(ctx, 0x1C39F4u, gen::fn_scrSetIntReturnVal_0035f060);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001C3A70 sub_1C3A70 -- 48 bytes; frame 0x10: ra sp+0x0
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: $v0):
// p3fes_handgen's body, statement for statement the original's.
void sub_1C3A70_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lw, hg::sd;
    Gpr v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001c3a70
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, -19052);  // 0x7CE284
    lw(v0, v0, 284);
    lhu(a0, v0, 2);
    jal(ctx, 0x1C3A84u, gen::fn_scrSetIntReturnVal_0035f060);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001C3AA0 sub_1C3AA0 -- 48 bytes; frame 0x10: ra sp+0x0
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: $v0):
// p3fes_handgen's body, statement for statement the original's.
void sub_1C3AA0_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lw, hg::sd;
    Gpr v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001c3aa0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, -19052);  // 0x7CE284
    lw(v0, v0, 284);
    lbu(a0, v0, 6);
    jal(ctx, 0x1C3AB4u, gen::fn_scrSetIntReturnVal_0035f060);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001C3B00 sub_1C3B00 -- 320 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [232] argc 0. 0x1C3B00, frame 48 (s0 = the field record, s1 = the slot index). 10; floor 4021 -> 5, return
// 1. Else 3; floor < 4000: 3, then the slot search (test 3 first, back-edge check before each body of 7:
// sub_16F630(-1, n) & 0xFFFF == 0 stops it, else 1, ++n) over n < 20; 3, 5 + K_Assert unless n < 20; 11:
// sub_1831E0(-1, (s16)n, field + 288), return 1. Floor >= 4000: 13: v = sub_170760(-1, (s16)floor) & 0xFFFF,
// t = (v + floor u8 +6) & 0xFFFF, clamped to 99 (1 more) when >= 100; 8: sub_170860(-1, (s16)floor u16 +2, t),
// return 1. Epilogue 7.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: $v0):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1C3B00_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal,
          hg::lbu, hg::ld, hg::lh, hg::lhu, hg::lq, hg::lw, hg::sd, hg::si, hg::slti, hg::sq;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001c3b00
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, gp, -19052);  // 0x7CE284
    lw(v0, s0, 284);
    lhu(v1, v0, 2);
    v0 = 4021;
    if (v1 != v0) {
        // 0x001c3b3c
        charge(ctx, 3);
        at = slti(v1, 4000);
        if (at == 0) {
            // 0x001c3bcc
            charge(ctx, 13);
            a1 = dsll32(v1, 16);
            a1 = dsra32(a1, 16);
            a0 = si(-1);
            jal(ctx, 0x1C3BD8u, gen::fn_sub_170760_00170760);
            a0 = v0 & 0xFFFF;
            lw(v1, s0, 284);
            lbu(v0, v1, 6);
            v0 = addu(a0, v0);
            v0 = v0 & 0xFFFF;
            at = slti(v0, 100);
            if (at == 0) {
                // 0x001c3c00
                charge(ctx, 1);
                v0 = 99;
            }
            // 0x001c3c04
            charge(ctx, 8);
            a2 = v0 & 0xFFFF;
            lh(a1, v1, 2);
            a0 = si(-1);
            jal(ctx, 0x1C3C10u, gen::fn_sub_170860_00170860);
            a0 = 1;
            jal(ctx, 0x1C3C1Cu, gen::fn_scrSetIntReturnVal_0035f060);
        } else {
            // 0x001c3b48
            charge(ctx, 3);
            s1 = 0;
            for (;;) {
                // 0x001c3b74
                charge(ctx, 3);
                v0 = slti(s1, 20);
                if (v0 != 0) {
                    backedge(ctx);
                    // 0x001c3b54
                    charge(ctx, 7);
                    a0 = si(-1);
                    a1 = s1;
                    jal(ctx, 0x1C3B5Cu, gen::fn_sub_16F630_0016f630);
                    v0 = v0 & 0xFFFF;
                    if (v0 != 0) {
                        // 0x001c3b70
                        charge(ctx, 1);
                        s1 = addiu(s1, 1);
                        continue;
                    }
                }
                break;
            }
            // 0x001c3b80
            charge(ctx, 3);
            v0 = slti(s1, 20);
            if (v0 == 0) {
                // 0x001c3b8c
                charge(ctx, 5);
                a0 = 0x680000;
                a0 = addiu(a0, 13920);  // "k_command.c"
                a1 = 1061;
                jal(ctx, 0x1C3B98u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x001c3ba0
            charge(ctx, 11);
            a1 = dsll32(s1, 16);
            a1 = dsra32(a1, 16);
            a0 = si(-1);
            a2 = addiu(s0, 288);
            jal(ctx, 0x1C3BB0u, gen::fn_sub_1831E0_001831e0);
            a0 = 1;
            jal(ctx, 0x1C3BBCu, gen::fn_scrSetIntReturnVal_0035f060);
        }
    } else {
        // 0x001c3b28
        charge(ctx, 5);
        a0 = 1;
        jal(ctx, 0x1C3B2Cu, gen::fn_scrSetIntReturnVal_0035f060);
    }
    // 0x001c3c24 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = 1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// --- the party list and the money word (0x16Exxx band) ----------------------------------------------------------

// 0x0016EA80 sub_16EA80 -- 252 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [133] argc 2 (only arg1 is read). 0x16EA80, frame 64 (s0 = found, s1 = index, s2 = slot value). 9; the
// membership loop (test 3 first, back-edge check before each body of 10: slot i == arg1 -> 1 (found); 1) over
// the first three slots; 2: found -> skip; else 5 and the empty-slot loop (test 3 first, back-edge check, body
// 6: slot i != 0 -> 1 and go on; else 7: slot i := arg1, found); 2: still not found -> 5, slot 2 := arg1; 8.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: logic (memory, saved registers)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_16EA80_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lh, hg::lq, hg::sd,
          hg::sh, hg::sll, hg::slti, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016ea80
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0;
    s1 = 0;
    for (;;) {
        // 0x0016ead4
        charge(ctx, 3);
        v0 = slti(s1, 3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0016eaa4
        charge(ctx, 10);
        v1 = sll(s1, 1);
        v0 = 0x830000;
        v0 = addiu(v0, 25088);  // &0x836200
        v0 = addu(v0, v1);
        lh(s2, v0, 17632);
        a0 = 1;
        jal(ctx, 0x16EABCu, gen::fn_scrGetIntPara_0035ed20);
        if (s2 == v0) {
            // 0x0016eacc
            charge(ctx, 1);
            s0 = 1;
        }
        // 0x0016ead0
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x0016eae0
    charge(ctx, 2);
    if (s0 == 0) {
        // 0x0016eae8
        charge(ctx, 5);
        a0 = 0;
        v1 = 0x830000;
        v1 = addiu(v1, 25088);  // &0x836200
        for (;;) {
            // 0x0016eb34
            charge(ctx, 3);
            v0 = slti(a0, 3);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0016eafc
            charge(ctx, 6);
            v0 = sll(a0, 1);
            v0 = addu(v1, v0);
            s1 = addiu(v0, 17632);
            lh(v0, v0, 17632);
            if (v0 == 0) {
                goto L_0016eb14_8;
            }
            // 0x0016eb30
            charge(ctx, 1);
            a0 = addiu(a0, 1);
        }
    }
L_0016eb40:
    charge(ctx, 2);
    if (s0 == 0) {
        // 0x0016eb48
        charge(ctx, 5);
        a0 = 1;
        jal(ctx, 0x16EB4Cu, gen::fn_scrGetIntPara_0035ed20);
        v1 = 0x840000;
        sh(v0, v1, -22812);  // 0x83A6E4
    }
    // 0x0016eb5c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = 1;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_0016eb14_8:
    charge(ctx, 7);
    a0 = 1;
    jal(ctx, 0x16EB18u, gen::fn_scrGetIntPara_0035ed20);
    sh(v0, s1, 0);
    s0 = 1;
    goto L_0016eb40;
}

// 0x0016EC40 sub_16EC40 -- 60 bytes; frame 0x10: ra sp+0x0
// [134] argc 1. 0x16EC40, frame 16: one block of 15.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: scratch GPRs):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_16EC40_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::enter, hg::jal, hg::ld, hg::sd, hg::sh, hg::sll;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016ec40
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x16EC4Cu, gen::fn_scrGetIntPara_0035ed20);
    v1 = sll(v0, 1);
    v0 = 0x840000;
    v0 = addiu(v0, -22816);  // &0x83A6E0
    v0 = addu(v0, v1);
    sh(zero, v0, 0);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0016EC80 sub_16EC80 -- 68 bytes; frame 0x10: ra sp+0x0
// [212] argc 1. 0x16EC80, frame 16: one block of 17.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: $v0):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_16EC80_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::enter, hg::jal, hg::ld, hg::lh, hg::sd, hg::sll;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016ec80
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x16EC8Cu, gen::fn_scrGetIntPara_0035ed20);
    v1 = sll(v0, 1);
    v0 = 0x840000;
    v0 = addiu(v0, -22816);  // &0x83A6E0
    v0 = addu(v0, v1);
    lh(a0, v0, 0);
    jal(ctx, 0x16ECA8u, gen::fn_scrSetIntReturnVal_0035f060);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0016ECD0 sub_16ECD0 -- 248 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [213] argc 1. 0x16ECD0, frame 64 (s0 = index, s1 = slot value, s2 = slot address). 8; the search loop (test
// 3 first, back-edge check before each body of 11: slot i == arg0 -> 3, slot := 0, stop; else 1) over four
// slots; 5; the compaction loop (test 3 first, back-edge check, body 5: slot j != 0 -> 1 and go on; else 4 and
// the shift loop: test 3 first, back-edge check, body 5: slot j := slot j + 1, ++j, over j < 3; then 2, stop);
// 8. The shift loop goes on with the compaction loop's index.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: $v0):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_16ECD0_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lh, hg::lq, hg::sd,
          hg::sh, hg::sll, hg::slti, hg::sq;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016ecd0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0;
    for (;;) {
        // 0x0016ed2c
        charge(ctx, 3);
        v0 = slti(s0, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0016ecf0
        charge(ctx, 11);
        v1 = sll(s0, 1);
        v0 = 0x830000;
        v0 = addiu(v0, 25088);  // &0x836200
        v0 = addu(v0, v1);
        s2 = addiu(v0, 17632);
        lh(s1, v0, 17632);
        a0 = 0;
        jal(ctx, 0x16ED0Cu, gen::fn_scrGetIntPara_0035ed20);
        if (s1 == v0) {
            goto L_0016ed1c_2;
        }
        // 0x0016ed28
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
L_0016ed38:
    charge(ctx, 5);
    a1 = 0;
    v1 = 0x830000;
    v1 = addiu(v1, 25088);  // &0x836200
    for (;;) {
        // 0x0016ed9c
        charge(ctx, 3);
        v0 = slti(a1, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0016ed4c
        charge(ctx, 5);
        v0 = sll(a1, 1);
        v0 = addu(v1, v0);
        lh(v0, v0, 17632);
        if (v0 == 0) {
            goto L_0016ed60_7;
        }
        // 0x0016ed98
        charge(ctx, 1);
        a1 = addiu(a1, 1);
    }
    // 0x0016eda8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = 1;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_0016ed1c_2:
    charge(ctx, 3);
    sh(zero, s2, 0);
    goto L_0016ed38;
L_0016ed60_7:
    charge(ctx, 4);
    a0 = 0x830000;
    a0 = addiu(a0, 25088);  // &0x836200
    for (;;) {
        // 0x0016ed84
        charge(ctx, 3);
        v0 = slti(a1, 3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0016ed70
        charge(ctx, 5);
        v0 = sll(a1, 1);
        v1 = addu(a0, v0);
        lh(v0, v1, 17634);
        sh(v0, v1, 17632);
        a1 = addiu(a1, 1);
    }
    // 0x0016ed90
    charge(ctx, 2);
    // 0x0016eda8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = 1;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0016EDD0 sub_16EDD0 -- 44 bytes; frame 0x10: ra sp+0x0
// [209] argc 0. 0x16EDD0, frame 16: one block of 11.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: $v0):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_16EDD0_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lw, hg::sd;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016edd0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = 0x840000;
    lw(a0, v0, -22820);  // 0x83A6DC
    jal(ctx, 0x16EDE0u, gen::fn_scrSetIntReturnVal_0035f060);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0016EE00 sub_16EE00 -- 136 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [210] argc 1. 0x16EE00, frame 32 (s0 = the sum). 14; sum >= 10,000,000 (signed) -> 2, sum := 9,999,999; 5;
// 5 + K_Assert(1674) unless sum < 10,000,000 unsigned (a negative sum); 8. The sum wraps like addu.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: $v0):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_16EE00_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::slt,
          hg::sltu, hg::sq, hg::sw;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016ee00
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    v0 = 0x840000;
    lw(s0, v0, -22820);  // 0x83A6DC
    a0 = 0;
    jal(ctx, 0x16EE18u, gen::fn_scrGetIntPara_0035ed20);
    s0 = addu(s0, v0);
    at = 0x980000;
    at = at | 0x9680;  // &0x989680
    at = slt(s0, at);
    if (at == 0) {
        // 0x0016ee38
        charge(ctx, 2);
        v0 = 0x980000;
        s0 = v0 | 0x967F;  // &0x98967F
    }
    // 0x0016ee40
    charge(ctx, 5);
    at = 0x980000;
    at = at | 0x9680;  // &0x989680
    at = sltu(s0, at);
    if (at == 0) {
        // 0x0016ee54
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 1674;
        jal(ctx, 0x16EE60u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0016ee68 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = 0x840000;
    sw(s0, v0, -22820);  // 0x83A6DC
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0016EE90 sub_16EE90 -- 144 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [211] argc 1. 0x16EE90, frame 32 (s0 = the money word). 11; money < arg0 (signed) -> 3, result 0; else 4,
// money - arg0 (arg0 read again, subu); 5; 5 + K_Assert(1674) unless the result < 10,000,000 unsigned; 8.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: $v0):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_16EE90_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::slt, hg::sltu,
          hg::sq, hg::subu, hg::sw;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016ee90
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    v0 = 0x840000;
    lw(s0, v0, -22820);  // 0x83A6DC
    a0 = 0;
    jal(ctx, 0x16EEA8u, gen::fn_scrGetIntPara_0035ed20);
    at = slt(s0, v0);
    if (at == 0) {
        // 0x0016eec8
        charge(ctx, 4);
        a0 = 0;
        jal(ctx, 0x16EECCu, gen::fn_scrGetIntPara_0035ed20);
        s0 = subu(s0, v0);
    } else {
        // 0x0016eebc
        charge(ctx, 3);
        s0 = 0;
    }
    // 0x0016eed8
    charge(ctx, 5);
    at = 0x980000;
    at = at | 0x9680;  // &0x989680
    at = sltu(s0, at);
    if (at == 0) {
        // 0x0016eeec
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 1674;
        jal(ctx, 0x16EEF8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0016ef00 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = 0x840000;
    sw(s0, v0, -22820);  // 0x83A6DC
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// --- return-value stubs and the battle/event records ------------------------------------------------------------

u32 sub_3111C0(EEContext& ctx) {
    // [48] argc 0. 0x3111C0, frame 16: one block of 10.
    guest::enter(ctx, 10);
    Frame frame(ctx, 16, 0);
    set_int(ctx, 0x3111CC, 1);
    return 1;
}

u32 sub_30FDC0(EEContext& ctx) {
    // [50] argc 2. 0x30FDC0, frame 16: one block of 10. `mtc1 zero, $f12`; scrSetFloatReturnVal.
    guest::enter(ctx, 10);
    Frame frame(ctx, 16, 0);
    rt::mtc1(ctx, GPR_ZERO, 12);
    jal(ctx, 0x30FDCC, &rg::fn_scrSetFloatReturnVal_0035f080);
    return 1;
}

u32 sub_3112E0(EEContext& ctx) {
    // [147] argc 0. 0x3112E0, frame 16: one block of 9.
    guest::enter(ctx, 9);
    Frame frame(ctx, 16, 0);
    jal(ctx, 0x3112E8, &rg::fn_datCalcRestorePartyAll_0030c440);
    return 1;
}

// 0x00350190 sub_350190 -- 104 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [145] argc 2. 0x350190, frame 32 (s0): one block of 26.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: scratch GPRs):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_350190_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lq, hg::sd, hg::sh, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00350190
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x3501A0u, gen::fn_scrGetIntPara_0035ed20);
    s0 = v0;
    a0 = 1;
    jal(ctx, 0x3501B0u, gen::fn_scrGetIntPara_0035ed20);
    v1 = 0x950000;
    sw(s0, v1, 31680);  // 0x957BC0
    v1 = 0x950000;
    sh(v0, v1, 31684);  // 0x957BC4
    v0 = 0x950000;
    sw(zero, v0, 31688);  // 0x957BC8
    v0 = 0x950000;
    sw(zero, v0, 31692);  // 0x957BCC
    sw(zero, gp, -18300);  // 0x7CE574
    v0 = 1;
    sw(v0, gp, -18296);  // 0x7CE578
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004243D0 sub_4243D0 -- 152 bytes; frame 0x10: ra sp+0x0
// [189] argc 6. 0x4243D0, frame 16: one block of 38. The record pointer is read again after each argument.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: scratch GPRs):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_4243D0_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lw, hg::sb, hg::sd;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004243d0
    enter(ctx, 38);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x4243DCu, gen::fn_scrGetIntPara_0035ed20);
    lw(v1, gp, -17992);  // 0x7CE6A8
    sb(v0, v1, 0);
    a0 = 1;
    jal(ctx, 0x4243F0u, gen::fn_scrGetIntPara_0035ed20);
    lw(v1, gp, -17992);  // 0x7CE6A8
    sb(v0, v1, 1);
    a0 = 2;
    jal(ctx, 0x424404u, gen::fn_scrGetIntPara_0035ed20);
    lw(v1, gp, -17992);  // 0x7CE6A8
    sb(v0, v1, 2);
    a0 = 3;
    jal(ctx, 0x424418u, gen::fn_scrGetIntPara_0035ed20);
    lw(v1, gp, -17992);  // 0x7CE6A8
    sb(v0, v1, 3);
    a0 = 4;
    jal(ctx, 0x42442Cu, gen::fn_scrGetIntPara_0035ed20);
    lw(v1, gp, -17992);  // 0x7CE6A8
    sb(v0, v1, 4);
    a0 = 5;
    jal(ctx, 0x424440u, gen::fn_scrGetIntPara_0035ed20);
    lw(v1, gp, -17992);  // 0x7CE6A8
    sb(v0, v1, 5);
    sb(zero, gp, -17984);  // 0x7CE6B0
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

u32 sub_424470(EEContext& ctx) {
    // [190] argc 0. 0x424470, leaf: one block of 4.
    guest::enter(ctx, 4);
    guest::store<u8>(ctx, kEventCfgDirty, 1);
    return 1;
}

u32 sub_424480(EEContext& ctx) {
    // [191] argc 0. 0x424480, leaf: one block of 6 (`lb; xori 1; sltiu 1`).
    guest::enter(ctx, 6);
    return guest::load<s8>(ctx, lwu(ctx, kEventCfgPtr) + 8) == 1 ? 1u : 0u;
}

// 0x004244A0 sub_4244A0 -- 56 bytes; frame 0x10: ra sp+0x0
// [206] argc 1. 0x4244A0, frame 16: one block of 14.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: scratch GPRs):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_4244A0_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lw, hg::sb, hg::sd;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004244a0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x4244ACu, gen::fn_scrGetIntPara_0035ed20);
    lw(v1, gp, -17992);  // 0x7CE6A8
    sb(v0, v1, 10);
    v0 = 1;
    lw(v1, gp, -17992);  // 0x7CE6A8
    sb(v0, v1, 9);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// --- persona / social-link commands (0x35F/0x360 band) ----------------------------------------------------------

u32 sub_35F1B0(EEContext& ctx) {
    // [124] argc 1. 0x35F1B0, frame 16: 12; result == 1 -> 4, return 1; else 3, return 0; 5.
    guest::enter(ctx, 12);
    Frame frame(ctx, 16, 0);
    const u64 id = int_para(ctx, 0x35F1BC, 0);
    if (jal(ctx, 0x35F1CC, &rg::fn_sub_16E100_0016e100, {sx16(id)}) == 1) {
        guest::charge(ctx, 4);
        set_int(ctx, 0x35F1E0, 1);
    } else {
        guest::charge(ctx, 3);
        set_int(ctx, 0x35F1F4, 0);
    }
    guest::charge(ctx, 5);
    return 1;
}

// 0x0035F210 sub_35F210 -- 336 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [186] argc 0. 0x35F210, frame 96 (s0..s3): 10; the copy of the six candidate ids from .rodata to the frame
// at +80 (three iterations of 9: two halfwords each, the back-edge check between them); 5; best_candidate.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: $v0):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_35F210_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::i64,
          hg::jal, hg::ld, hg::lh, hg::lq, hg::sd, hg::sh, hg::si, hg::sll, hg::slt, hg::slti, hg::sq;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0035f210
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a2 = 0x6A0000;
    a2 = addiu(a2, -10984);  // &0x69D518
    a1 = addiu(sp, 0x50);
    a0 = 3;
    for (;;) {
        // 0x0035f238
        charge(ctx, 9);
        lh(v1, a2, 0);
        lh(v0, a2, 2);
        a2 = addiu(a2, 4);
        a0 = addiu(a0, -1);
        sh(v1, a1, 0);
        sh(v0, a1, 2);
        a1 = addiu(a1, 4);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0035f25c
    charge(ctx, 5);
    s2 = si(-1);
    s1 = s2;
    s3 = 0;
    for (;;) {
        // 0x0035f304
        charge(ctx, 3);
        v0 = slti(s3, 6);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0035f270
        charge(ctx, 8);
        v0 = sll(s3, 1);
        v0 = addu(v0, sp);
        lh(s0, v0, 80);
        a0 = s0;
        jal(ctx, 0x35F280u, gen::fn_sub_16E100_0016e100);
        if (v0 != 0) {
            // 0x0035f290
            charge(ctx, 6);
            a0 = s0;
            jal(ctx, 0x35F294u, gen::fn_sub_1717C0_001717c0);
            v1 = 1;
            if (v0 != v1) {
                // 0x0035f2a8
                charge(ctx, 6);
                a0 = s0;
                jal(ctx, 0x35F2ACu, gen::fn_sub_172160_00172160);
                v1 = 1;
                if (v0 != v1) {
                    // 0x0035f2c0
                    charge(ctx, 9);
                    a0 = dsll32(s0, 16);
                    a0 = dsra32(a0, 16);
                    jal(ctx, 0x35F2C8u, gen::fn_sub_16DBA0_0016dba0);
                    v0 = dsll32(v0, 24);
                    v0 = dsra32(v0, 24);
                    at = slt(s1, v0);
                    if (at != 0) {
                        // 0x0035f2e4
                        charge(ctx, 7);
                        s2 = s3;
                        a0 = dsll32(s0, 16);
                        a0 = dsra32(a0, 16);
                        jal(ctx, 0x35F2F0u, gen::fn_sub_16DBA0_0016dba0);
                        s1 = dsll32(v0, 24);
                        s1 = dsra32(s1, 24);
                    }
                }
            }
        }
        // 0x0035f300
        charge(ctx, 1);
        s3 = addiu(s3, 1);
    }
    // 0x0035f310
    charge(ctx, 3);
    v0 = si(-1);
    if (s2 != v0) {
        // 0x0035f330
        charge(ctx, 3);
        a0 = addiu(s2, 1);
        jal(ctx, 0x35F334u, gen::fn_scrSetIntReturnVal_0035f060);
    } else {
        // 0x0035f31c
        charge(ctx, 5);
        a0 = 0;
        jal(ctx, 0x35F320u, gen::fn_scrSetIntReturnVal_0035f060);
    }
    // 0x0035f33c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = 1;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0035F360 sub_35F360 -- 316 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [187] argc 0. 0x35F360, frame 96 (s0..s3): 19 (the four candidate ids from $gp - 25232 copied to the frame
// at +88, the loop set-up); best_candidate.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: $v0):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_35F360_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld,
          hg::lh, hg::lq, hg::sd, hg::sh, hg::si, hg::sll, hg::slt, hg::slti, hg::sq;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0035f360
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lh(a1, gp, -25232);  // 0x7CCA60
    lh(a0, gp, -25230);  // 0x7CCA62
    lh(v1, gp, -25228);  // 0x7CCA64
    lh(v0, gp, -25226);  // 0x7CCA66
    sh(a1, sp, 0x58);
    sh(a0, sp, 0x5A);
    sh(v1, sp, 0x5C);
    sh(v0, sp, 0x5E);
    s2 = si(-1);
    s1 = s2;
    s3 = 0;
    for (;;) {
        // 0x0035f440
        charge(ctx, 3);
        v0 = slti(s3, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0035f3ac
        charge(ctx, 8);
        v0 = sll(s3, 1);
        v0 = addu(v0, sp);
        lh(s0, v0, 88);
        a0 = s0;
        jal(ctx, 0x35F3BCu, gen::fn_sub_16E100_0016e100);
        if (v0 != 0) {
            // 0x0035f3cc
            charge(ctx, 6);
            a0 = s0;
            jal(ctx, 0x35F3D0u, gen::fn_sub_1717C0_001717c0);
            v1 = 1;
            if (v0 != v1) {
                // 0x0035f3e4
                charge(ctx, 6);
                a0 = s0;
                jal(ctx, 0x35F3E8u, gen::fn_sub_172160_00172160);
                v1 = 1;
                if (v0 != v1) {
                    // 0x0035f3fc
                    charge(ctx, 9);
                    a0 = dsll32(s0, 16);
                    a0 = dsra32(a0, 16);
                    jal(ctx, 0x35F404u, gen::fn_sub_16DBA0_0016dba0);
                    v0 = dsll32(v0, 24);
                    v0 = dsra32(v0, 24);
                    at = slt(s1, v0);
                    if (at != 0) {
                        // 0x0035f420
                        charge(ctx, 7);
                        s2 = s3;
                        a0 = dsll32(s0, 16);
                        a0 = dsra32(a0, 16);
                        jal(ctx, 0x35F42Cu, gen::fn_sub_16DBA0_0016dba0);
                        s1 = dsll32(v0, 24);
                        s1 = dsra32(s1, 24);
                    }
                }
            }
        }
        // 0x0035f43c
        charge(ctx, 1);
        s3 = addiu(s3, 1);
    }
    // 0x0035f44c
    charge(ctx, 3);
    v0 = si(-1);
    if (s2 != v0) {
        // 0x0035f46c
        charge(ctx, 3);
        a0 = addiu(s2, 1);
        jal(ctx, 0x35F470u, gen::fn_scrSetIntReturnVal_0035f060);
    } else {
        // 0x0035f458
        charge(ctx, 5);
        a0 = 0;
        jal(ctx, 0x35F45Cu, gen::fn_scrSetIntReturnVal_0035f060);
    }
    // 0x0035f478 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = 1;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0035FBD0 sub_35FBD0 -- 148 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [208] argc 2. 0x35FBD0, frame 48 (s0, s1): 11; 5 + K_Assert(390) unless arg0 < 5 (signed); 21.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: $v0):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_35FBD0_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld, hg::lq, hg::sd,
          hg::slti, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0035fbd0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x35FBE4u, gen::fn_scrGetIntPara_0035ed20);
    s1 = v0;
    v0 = slti(s1, 5);
    if (v0 == 0) {
        // 0x0035fbfc
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -10960);  // "scrComuCommand.c"
        a1 = 390;
        jal(ctx, 0x35FC08u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0035fc10
    charge(ctx, 21);
    a0 = 1;
    jal(ctx, 0x35FC14u, gen::fn_scrGetIntPara_0035ed20);
    s0 = v0;
    jal(ctx, 0x35FC20u, gen::fn_sub_175360_00175360);
    v0 = dsll32(v0, 16);
    v0 = dsra32(v0, 16);
    a0 = v0 & 0xFFFF;
    a1 = s1 & 0xFFFF;
    a2 = dsll32(s0, 24);
    a2 = dsra32(a2, 24);
    jal(ctx, 0x35FC40u, gen::fn_sub_174710_00174710);
    v0 = 1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0035FF80 sub_35FF80 -- 148 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [224] argc 1. 0x35FF80, frame 32 (s0): 6; 5 + K_Assert(528) when the context pointer is 0; 6; arg0 < 0 ->
// 5 + K_Assert(533); else 3, and 5 + K_Assert(533) unless arg0 < 3; 12.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: $v0):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_35FF80_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::i64, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd,
          hg::sll, hg::slti, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0035ff80
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -18232);  // 0x7CE5B8
    if (v0 == 0) {
        // 0x0035ff98
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -10960);  // "scrComuCommand.c"
        a1 = 528;
        jal(ctx, 0x35FFA4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0035ffac
    charge(ctx, 6);
    a0 = 0;
    jal(ctx, 0x35FFB0u, gen::fn_scrGetIntPara_0035ed20);
    s0 = v0;
    if (i64(s0) >= 0) {
        // 0x0035ffc4
        charge(ctx, 3);
        v0 = slti(s0, 3);
        if (v0 == 0) {
            goto L_0035ffd0;
        }
        goto L_0035ffe4;
    }
L_0035ffd0:
    charge(ctx, 5);
    a0 = 0x6A0000;
    a0 = addiu(a0, -10960);  // "scrComuCommand.c"
    a1 = 533;
    jal(ctx, 0x35FFDCu, gen::fn_sub_19D3F0_0019d3f0);
L_0035ffe4:
    charge(ctx, 12);
    lw(v1, gp, -18232);  // 0x7CE5B8
    v0 = sll(s0, 2);
    v0 = addu(v0, v1);
    lw(a0, v0, 16);
    jal(ctx, 0x35FFF4u, gen::fn_scrSetIntReturnVal_0035f060);
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00360020 sub_360020 -- 104 bytes; frame 0x10: ra sp+0x0
// [225] argc 1. 0x360020, frame 16: 5; 5 + K_Assert(547) when the context pointer is 0; 16.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: $v0):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_360020_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lw, hg::sd, hg::sll;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00360020
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, -18232);  // 0x7CE5B8
    if (v0 == 0) {
        // 0x00360034
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, -10960);  // "scrComuCommand.c"
        a1 = 547;
        jal(ctx, 0x360040u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00360048
    charge(ctx, 16);
    a0 = 0;
    jal(ctx, 0x36004Cu, gen::fn_scrGetIntPara_0035ed20);
    lw(a0, gp, -18232);  // 0x7CE5B8
    v1 = sll(v0, 2);
    v1 = addu(v1, a0);
    lw(a0, gp, -18236);  // 0x7CE5B4
    a1 = v0;
    lw(a2, v1, 16);
    jal(ctx, 0x36006Cu, gen::fn_sub_172E50_00172e50);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

u32 sub_360280(EEContext& ctx) {
    // [218] argc 1. 0x360280, frame 32 (s0): 13; 5 + K_Assert(659) when sub_16DCE0((s16)arg0) == 0; 14.
    guest::enter(ctx, 13);
    Frame frame(ctx, 32, 1);
    const u64 id = int_para(ctx, 0x360290, 0);
    keep(ctx, GPR_S0, id);
    if (jal(ctx, 0x3602A4, &rg::fn_sub_16DCE0_0016dce0, {sx16(id)}) == 0) k_assert(ctx, 0x3602C0, kFileScrCommand, 659);
    guest::charge(ctx, 14);
    set_int(ctx, 0x3602E0, sx8(jal(ctx, 0x3602D0, &rg::fn_sub_16DBA0_0016dba0, {sx16(id)})));
    return 1;
}

u32 sub_360300(EEContext& ctx) { return persona_check(ctx, 0x360300, &rg::fn_sub_1717C0_001717c0, 673); }  // [219]
u32 sub_3603D0(EEContext& ctx) { return persona_check(ctx, 0x3603D0, &rg::fn_sub_172160_00172160, 697); }  // [220]

}  // namespace p3fes::game

// --- the recompiled program's entry points ----------------------------------------------------------------------
namespace p3fes::recomp_gen {

using namespace p3fes::game;

#define P3FES_COMM_A_SHIM(name, addr) \
    void fn_##name##_##addr(p3fes::EEContext& ctx) { guest::ret32(ctx, name(ctx)); }
P3FES_COMM_A_SHIM(sub_1C2500, 001c2500)
P3FES_COMM_A_SHIM(sub_1C2610, 001c2610)
P3FES_COMM_A_SHIM(sub_1C2690, 001c2690)
P3FES_COMM_A_SHIM(sub_1C26C0, 001c26c0)
P3FES_COMM_A_SHIM(sub_1C26F0, 001c26f0)
P3FES_COMM_A_SHIM(sub_1C2720, 001c2720)
P3FES_COMM_A_SHIM(sub_1C2750, 001c2750)
P3FES_COMM_A_SHIM(sub_1C2780, 001c2780)
P3FES_COMM_A_SHIM(sub_1C2830, 001c2830)
P3FES_COMM_A_SHIM(sub_1C28D0, 001c28d0)
P3FES_COMM_A_SHIM(sub_1C2EA0, 001c2ea0)
P3FES_COMM_A_SHIM(sub_3111C0, 003111c0)
P3FES_COMM_A_SHIM(sub_30FDC0, 0030fdc0)
P3FES_COMM_A_SHIM(sub_3112E0, 003112e0)
P3FES_COMM_A_SHIM(sub_424470, 00424470)
P3FES_COMM_A_SHIM(sub_424480, 00424480)
P3FES_COMM_A_SHIM(sub_1C2ED0, 001c2ed0)
P3FES_COMM_A_SHIM(sub_1C2FA0, 001c2fa0)
P3FES_COMM_A_SHIM(sub_1C3050, 001c3050)
P3FES_COMM_A_SHIM(sub_1C30A0, 001c30a0)
P3FES_COMM_A_SHIM(sub_1C3150, 001c3150)
P3FES_COMM_A_SHIM(sub_1C3370, 001c3370)
P3FES_COMM_A_SHIM(sub_1C33C0, 001c33c0)
P3FES_COMM_A_SHIM(sub_1C3410, 001c3410)
P3FES_COMM_A_SHIM(sub_1C3460, 001c3460)
P3FES_COMM_A_SHIM(sub_1C3540, 001c3540)
P3FES_COMM_A_SHIM(sub_1C3690, 001c3690)
P3FES_COMM_A_SHIM(sub_1C3710, 001c3710)
P3FES_COMM_A_SHIM(sub_1C3790, 001c3790)
P3FES_COMM_A_SHIM(sub_35F1B0, 0035f1b0)
P3FES_COMM_A_SHIM(sub_360280, 00360280)
P3FES_COMM_A_SHIM(sub_360300, 00360300)
P3FES_COMM_A_SHIM(sub_3603D0, 003603d0)
#undef P3FES_COMM_A_SHIM

}  // namespace p3fes::recomp_gen
