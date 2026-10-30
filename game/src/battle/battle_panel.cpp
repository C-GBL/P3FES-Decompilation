// The battle status panels (game/include/p3fes/game/battle_panel.h), hand-decompiled from SLUS_216.21
// (docs/ANALYSIS/27_unmapped_bands.md section 3). tests/game/test_battle_panel.cpp runs each function against its
// __recomp body.
//
// Fidelity. Every function mirrors the recompiled body down to the register file:
// * virtual time (ADR-0013): guest::enter / charge / backedge follow the `ctx.cycles += N` blocks and the check points
//   of the generated body. A block is charged at its start, before the calls it contains. The loops here are of two
//   kinds: test-first (the compiled code jumps to the test; the first test runs without a check, every later one is
//   followed by the back-edge check when it loops: `for (;;) { charge(test); if (!cond) break; backedge(); ... }`) and
//   body-first (the stack clears of sub_21CD00 / sub_21CEC0: `for (;;) { charge(body); ...; if (!cond) break;
//   backedge(); }`);
// * registers: the register transfers are the rt:: operations of the instructions they stand for (`move` is `daddu
//   rd, rs, zero`, `li` is `addiu rd, zero, imm`, the s16 idiom is `dsll32 + dsra32 16`, the unsigned-to-float idiom
//   is the `bltz` / `srl; andi; or; cvt.s.w; add.s` pair), in the original order, so every GPR holds the original
//   64-bit (128-bit) value and every FPR the original bits at every check point, call and return. A check point may
//   preempt the thread and the kernel then stores the whole register file in guest memory, so none of these is
//   "dead";
// * frames: `Frame` performs the original prologue and epilogue (`addiu sp; sd ra; sq sN ... sq s0; swc1 f2N ... f20`
//   ... and back), so the spill slots hold what the original stored, the locals the callees fill (sub_1FC720's two
//   result blocks, sub_1FCE20 / sub_1FD350's candidate arrays and sub_17BE10 out-words, sub_21E380's uv rect) sit
//   where they did, and the callees' frames land where they did;
// * calls: every callee is entered through its generated symbol with $ra = the original link (`rt::jal` at the
//   call's address), so whichever body is live runs (the retail `jr $ra` K_Assert sub_19D3F0 too: its bad-input paths
//   continue as the original's do);
// * jump tables: the five `jr` switches read their target from the table in guest memory (as `lw; jr` does) and
//   dispatch on it; a target outside the table's labels goes to rt::lookup_func like the generated body, without the
//   epilogue (a `jr` leaves the function).
#include "p3fes/game/battle_panel.h"

#include "p3fes/ee/core.h"
#include "p3fes/game/guest.h"

namespace p3fes::recomp_gen {
void fn_abs_0051e0e0(p3fes::EEContext&);
void fn_atan2f_0052ea18(p3fes::EEContext&);
void fn_cosf_0052e6d8(p3fes::EEContext&);
void fn_datCalcGetHp_002ffd70(p3fes::EEContext&);
void fn_datCalcGetMaxHp_002ffdf0(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_nullsub_11_0021c7e0(p3fes::EEContext&);
void fn_sinf_0052e878(p3fes::EEContext&);
void fn_sub_16C4F0_0016c4f0(p3fes::EEContext&);
void fn_sub_16C570_0016c570(p3fes::EEContext&);
void fn_sub_16CF40_0016cf40(p3fes::EEContext&);
void fn_sub_16CF90_0016cf90(p3fes::EEContext&);
void fn_sub_170670_00170670(p3fes::EEContext&);
void fn_sub_1706C0_001706c0(p3fes::EEContext&);
void fn_sub_170710_00170710(p3fes::EEContext&);
void fn_sub_170E90_00170e90(p3fes::EEContext&);
void fn_sub_173300_00173300(p3fes::EEContext&);
void fn_sub_17B4E0_0017b4e0(p3fes::EEContext&);
void fn_sub_17B500_0017b500(p3fes::EEContext&);
void fn_sub_17B5B0_0017b5b0(p3fes::EEContext&);
void fn_sub_17B660_0017b660(p3fes::EEContext&);
void fn_sub_17B860_0017b860(p3fes::EEContext&);
void fn_sub_17BE10_0017be10(p3fes::EEContext&);
void fn_sub_17C070_0017c070(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_198590_00198590(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_1F9E90_001f9e90(p3fes::EEContext&);
void fn_sub_1FC980_001fc980(p3fes::EEContext&);
void fn_sub_1FCB30_001fcb30(p3fes::EEContext&);
void fn_sub_1FCCC0_001fccc0(p3fes::EEContext&);
void fn_sub_1FCE20_001fce20(p3fes::EEContext&);
void fn_sub_1FD350_001fd350(p3fes::EEContext&);
void fn_sub_1FDC00_001fdc00(p3fes::EEContext&);
void fn_sub_1FF890_001ff890(p3fes::EEContext&);
void fn_sub_1FFC60_001ffc60(p3fes::EEContext&);
void fn_sub_1FFF40_001fff40(p3fes::EEContext&);
void fn_sub_2016B0_002016b0(p3fes::EEContext&);
void fn_sub_201B50_00201b50(p3fes::EEContext&);
void fn_sub_201C30_00201c30(p3fes::EEContext&);
void fn_sub_201D10_00201d10(p3fes::EEContext&);
void fn_sub_201E00_00201e00(p3fes::EEContext&);
void fn_sub_2053C0_002053c0(p3fes::EEContext&);
void fn_sub_205410_00205410(p3fes::EEContext&);
void fn_sub_2054C0_002054c0(p3fes::EEContext&);
void fn_sub_205500_00205500(p3fes::EEContext&);
void fn_sub_205550_00205550(p3fes::EEContext&);
void fn_sub_2055A0_002055a0(p3fes::EEContext&);
void fn_sub_2079C0_002079c0(p3fes::EEContext&);
void fn_sub_207A10_00207a10(p3fes::EEContext&);
void fn_sub_207A60_00207a60(p3fes::EEContext&);
void fn_sub_207AB0_00207ab0(p3fes::EEContext&);
void fn_sub_207B00_00207b00(p3fes::EEContext&);
void fn_sub_207B50_00207b50(p3fes::EEContext&);
void fn_sub_207BA0_00207ba0(p3fes::EEContext&);
void fn_sub_207BF0_00207bf0(p3fes::EEContext&);
void fn_sub_207C40_00207c40(p3fes::EEContext&);
void fn_sub_207C90_00207c90(p3fes::EEContext&);
void fn_sub_207CE0_00207ce0(p3fes::EEContext&);
void fn_sub_207D30_00207d30(p3fes::EEContext&);
void fn_sub_207D80_00207d80(p3fes::EEContext&);
void fn_sub_207DD0_00207dd0(p3fes::EEContext&);
void fn_sub_207F70_00207f70(p3fes::EEContext&);
void fn_sub_207FC0_00207fc0(p3fes::EEContext&);
void fn_sub_208010_00208010(p3fes::EEContext&);
void fn_sub_208050_00208050(p3fes::EEContext&);
void fn_sub_208130_00208130(p3fes::EEContext&);
void fn_sub_2085E0_002085e0(p3fes::EEContext&);
void fn_sub_208630_00208630(p3fes::EEContext&);
void fn_sub_208680_00208680(p3fes::EEContext&);
void fn_sub_2086D0_002086d0(p3fes::EEContext&);
void fn_sub_208720_00208720(p3fes::EEContext&);
void fn_sub_208B30_00208b30(p3fes::EEContext&);
void fn_sub_2094F0_002094f0(p3fes::EEContext&);
void fn_sub_209540_00209540(p3fes::EEContext&);
void fn_sub_2095A0_002095a0(p3fes::EEContext&);
void fn_sub_20EDF0_0020edf0(p3fes::EEContext&);
void fn_sub_20F260_0020f260(p3fes::EEContext&);
void fn_sub_20F3B0_0020f3b0(p3fes::EEContext&);
void fn_sub_20F570_0020f570(p3fes::EEContext&);
void fn_sub_20F9A0_0020f9a0(p3fes::EEContext&);
void fn_sub_20FC40_0020fc40(p3fes::EEContext&);
void fn_sub_20FC90_0020fc90(p3fes::EEContext&);
void fn_sub_20FCE0_0020fce0(p3fes::EEContext&);
void fn_sub_20FD30_0020fd30(p3fes::EEContext&);
void fn_sub_20FD80_0020fd80(p3fes::EEContext&);
void fn_sub_20FDD0_0020fdd0(p3fes::EEContext&);
void fn_sub_20FE30_0020fe30(p3fes::EEContext&);
void fn_sub_210D60_00210d60(p3fes::EEContext&);
void fn_sub_210D90_00210d90(p3fes::EEContext&);
void fn_sub_213E80_00213e80(p3fes::EEContext&);
void fn_sub_215A30_00215a30(p3fes::EEContext&);
void fn_sub_215A40_00215a40(p3fes::EEContext&);
void fn_sub_21B830_0021b830(p3fes::EEContext&);
void fn_sub_21B8B0_0021b8b0(p3fes::EEContext&);
void fn_sub_21B940_0021b940(p3fes::EEContext&);
void fn_sub_21BAB0_0021bab0(p3fes::EEContext&);
void fn_sub_21BB00_0021bb00(p3fes::EEContext&);
void fn_sub_21BB50_0021bb50(p3fes::EEContext&);
void fn_sub_21BCB0_0021bcb0(p3fes::EEContext&);
void fn_sub_21CD00_0021cd00(p3fes::EEContext&);
void fn_sub_21CEC0_0021cec0(p3fes::EEContext&);
void fn_sub_23F540_0023f540(p3fes::EEContext&);
void fn_sub_241910_00241910(p3fes::EEContext&);
void fn_sub_242260_00242260(p3fes::EEContext&);
void fn_sub_242320_00242320(p3fes::EEContext&);
void fn_sub_242540_00242540(p3fes::EEContext&);
void fn_sub_242600_00242600(p3fes::EEContext&);
void fn_sub_242720_00242720(p3fes::EEContext&);
void fn_sub_242A30_00242a30(p3fes::EEContext&);
void fn_sub_242A50_00242a50(p3fes::EEContext&);
void fn_sub_242A60_00242a60(p3fes::EEContext&);
void fn_sub_242AE0_00242ae0(p3fes::EEContext&);
void fn_sub_242B80_00242b80(p3fes::EEContext&);
void fn_sub_242C20_00242c20(p3fes::EEContext&);
void fn_sub_242CC0_00242cc0(p3fes::EEContext&);
void fn_sub_243150_00243150(p3fes::EEContext&);
void fn_sub_244120_00244120(p3fes::EEContext&);
void fn_sub_2441B0_002441b0(p3fes::EEContext&);
void fn_sub_2449D0_002449d0(p3fes::EEContext&);
void fn_sub_244A00_00244a00(p3fes::EEContext&);
void fn_sub_244A40_00244a40(p3fes::EEContext&);
void fn_sub_244E10_00244e10(p3fes::EEContext&);
void fn_sub_2453D0_002453d0(p3fes::EEContext&);
void fn_sub_245E00_00245e00(p3fes::EEContext&);
void fn_sub_245E50_00245e50(p3fes::EEContext&);
void fn_sub_248500_00248500(p3fes::EEContext&);
void fn_sub_248580_00248580(p3fes::EEContext&);
void fn_sub_248620_00248620(p3fes::EEContext&);
void fn_sub_248BB0_00248bb0(p3fes::EEContext&);
void fn_sub_249130_00249130(p3fes::EEContext&);
void fn_sub_249180_00249180(p3fes::EEContext&);
void fn_sub_2492B0_002492b0(p3fes::EEContext&);
void fn_sub_249420_00249420(p3fes::EEContext&);
void fn_sub_249600_00249600(p3fes::EEContext&);
void fn_sub_24A7A0_0024a7a0(p3fes::EEContext&);
void fn_sub_24C110_0024c110(p3fes::EEContext&);
void fn_sub_24CCA0_0024cca0(p3fes::EEContext&);
void fn_sub_24CF00_0024cf00(p3fes::EEContext&);
void fn_sub_24D0C0_0024d0c0(p3fes::EEContext&);
void fn_sub_2510D0_002510d0(p3fes::EEContext&);
void fn_sub_251A80_00251a80(p3fes::EEContext&);
void fn_sub_251F40_00251f40(p3fes::EEContext&);
void fn_sub_252060_00252060(p3fes::EEContext&);
void fn_sub_2520F0_002520f0(p3fes::EEContext&);
void fn_sub_252E90_00252e90(p3fes::EEContext&);
void fn_sub_252EE0_00252ee0(p3fes::EEContext&);
void fn_sub_252F30_00252f30(p3fes::EEContext&);
void fn_sub_2532B0_002532b0(p3fes::EEContext&);
void fn_sub_253410_00253410(p3fes::EEContext&);
void fn_sub_25BE60_0025be60(p3fes::EEContext&);
void fn_sub_25C110_0025c110(p3fes::EEContext&);
void fn_sub_25C190_0025c190(p3fes::EEContext&);
void fn_sub_25C1E0_0025c1e0(p3fes::EEContext&);
void fn_sub_25C220_0025c220(p3fes::EEContext&);
void fn_sub_25C9C0_0025c9c0(p3fes::EEContext&);
void fn_sub_25D020_0025d020(p3fes::EEContext&);
void fn_sub_25D470_0025d470(p3fes::EEContext&);
void fn_sub_25D760_0025d760(p3fes::EEContext&);
void fn_sub_25D7B0_0025d7b0(p3fes::EEContext&);
void fn_sub_25D800_0025d800(p3fes::EEContext&);
void fn_sub_25D850_0025d850(p3fes::EEContext&);
void fn_sub_267180_00267180(p3fes::EEContext&);
void fn_sub_27B610_0027b610(p3fes::EEContext&);
void fn_sub_27B880_0027b880(p3fes::EEContext&);
void fn_sub_27B9F0_0027b9f0(p3fes::EEContext&);
void fn_sub_27BA90_0027ba90(p3fes::EEContext&);
void fn_sub_27BAE0_0027bae0(p3fes::EEContext&);
void fn_sub_289030_00289030(p3fes::EEContext&);
void fn_sub_30BC50_0030bc50(p3fes::EEContext&);
void fn_sub_30C0C0_0030c0c0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {

namespace rg = recomp_gen;
using guest::Fn;
using rt::Reg;

// --- registers ------------------------------------------------------------------------------------------------
constexpr Reg ZR = GPR_ZERO, AT = GPR_AT, V0 = GPR_V0, V1 = GPR_V1, A0 = GPR_A0, A1 = GPR_A1, A2 = GPR_A2, A3 = GPR_A3;
constexpr Reg T0 = GPR_T0, T1 = GPR_T0 + 1, T2 = GPR_T0 + 2;
constexpr Reg S0 = GPR_S0, S1 = GPR_S0 + 1, S2 = GPR_S0 + 2, S3 = GPR_S0 + 3, S4 = GPR_S0 + 4, S5 = GPR_S0 + 5;
constexpr Reg S6 = GPR_S0 + 6, S7 = GPR_S0 + 7;
constexpr Reg GP = GPR_GP, SP = GPR_SP, FP = GPR_FP, RA = GPR_RA;
// FPR numbers ($f12 / $f13 are the float arguments, $f0 the float result, $f20.. callee-saved)
constexpr Reg F0 = 0, F1 = 1, F2 = 2, F3 = 3, F4 = 4, F5 = 5, F12 = 12, F13 = 13;
constexpr Reg F20 = 20, F21 = 21, F22 = 22, F23 = 23, F24 = 24;

// The K_Assert file strings (lui a0, 0x68; addiu a0, a0, lo).
constexpr s32 kPbMain = 19808;  // 0x684D60 "pb_main.c"
constexpr s32 kBpRoot = 20024;  // 0x684E38 "bp_root.c"
constexpr s32 kBpMisc = 20040;  // 0x684E48 "bp_misc.c"

// The instruction idioms of these bodies, as the instructions themselves.
void move(EEContext& c, Reg d, Reg s) { rt::daddu(c, d, s, ZR); }
void li(EEContext& c, Reg d, s32 v) { rt::addiu(c, d, ZR, v); }
void u16_of(EEContext& c, Reg d, Reg s) { rt::andi(c, d, s, 0xFFFFu); }
void s16_of(EEContext& c, Reg d, Reg s) {  // dsll32 / dsra32 16
    rt::dsll32(c, d, s, 16);
    rt::dsra32(c, d, d, 16);
}
bool eq(EEContext& c, Reg a, Reg b) { return rt::cmp_eq(c, a, b); }
bool nz(EEContext& c, Reg a) { return rt::cmp_ne(c, a, ZR); }
void charge(EEContext& c, u64 n) { guest::charge(c, n); }

// `jal fn` at `pc`: $ra = the generated link value, the callee through its generated symbol.
void call(EEContext& c, u32 pc, Fn fn) {
    rt::jal(c, pc);
    fn(c);
}

// K_Assert(file, line) (`jr $ra` in retail): `lui a0, 0x68; addiu a0, a0, file; addiu a1, zero, line; jal`.
void kassert(EEContext& c, s32 file, s32 line, u32 pc) {
    rt::lui(c, A0, 0x68u);
    rt::addiu(c, A0, A0, file);
    li(c, A1, line);
    call(c, pc, rg::fn_sub_19D3F0_0019d3f0);
}

// `lw t, -18956(gp); lw d, 60(t)`: the panel work of the "battle panel" task.
void panel_work(EEContext& c, Reg t, Reg d) {
    rt::lw(c, t, GP, bpanel::kGpPanelTask);
    rt::lw(c, d, t, 60);
}

// `lui at, 1; ori at, at, 0x19b0; addu d, base, at`: the command panel record (panel work + 0x119B0).
void cmd_record(EEContext& c, Reg d, Reg base) {
    rt::lui(c, AT, 0x1u);
    rt::ori(c, AT, AT, 0x19B0u);
    rt::addu(c, d, base, AT);
}

// The unsigned-to-float idiom on the value in `v` (the compiler's u32 -> float: `bltz v` picks the halving path):
// v >= 0: `mtc1 v, ftmp; cvt.s.w fd, ftmp` (a block of 5); else `srl t, v, 1; andi a, v, 1; or t, t, a; mtc1 t, ftmp;
// cvt.s.w fd, ftmp; add.s fd, fd, fd` (a block of 7).
void u2f(EEContext& c, Reg v, Reg t, Reg a, Reg ftmp, Reg fd) {
    if (rt::cmp_ltz(c, v)) {
        charge(c, 7);
        rt::srl(c, t, v, 1);
        rt::andi(c, a, v, 0x1u);
        rt::or_(c, t, t, a);
        rt::mtc1(c, t, ftmp);
        rt::cvt_s_w(c, fd, ftmp);
        rt::add_s(c, fd, fd, fd);
    } else {
        charge(c, 5);
        rt::mtc1(c, v, ftmp);
        rt::cvt_s_w(c, fd, ftmp);
    }
}

// One vertex's four colour bytes src[off..off+3] -> floats dst[d..d+12]: the caller has done `lbu v, off(src)` (in its
// block); each conversion is followed by a block of 4 (`swc1 f0, d+4i(dst); lbu v, off+i+1(src)`), the last
// conversion's store opens the caller's next block.
void colours(EEContext& c, Reg v, Reg t, Reg src, s32 off, Reg dst, s32 d) {
    u2f(c, v, t, v, F0, F0);
    for (s32 i = 1; i < 4; ++i) {
        charge(c, 4);
        rt::swc1(c, F0, dst, d + 4 * (i - 1));
        rt::lbu(c, v, src, off + i);
        u2f(c, v, t, v, F0, F0);
    }
}

// The original frame: `addiu sp, sp, -size; sd ra, ra(sp)`, then s(n-1)..s0 at s_base + 16 * k (k = 8 is $fp) and
// $f20+(nf-1)..$f20 at 4 * k; the destructor is the epilogue in the same order (`ld ra; lq ...; lwc1 ...; addiu sp`).
class Frame {
public:
    Frame(EEContext& c, s32 size, s32 ra, unsigned n = 0, s32 s_base = 0, unsigned nf = 0)
        : c_(c), size_(size), ra_(ra), n_(n), base_(s_base), nf_(nf) {
        rt::addiu(c_, SP, SP, -size_);
        rt::sd(c_, RA, SP, ra_);
        for (unsigned k = n_; k-- > 0;) rt::sq(c_, sreg(k), SP, base_ + 16 * static_cast<s32>(k));
        for (unsigned k = nf_; k-- > 0;) rt::swc1(c_, F20 + k, SP, 4 * static_cast<s32>(k));
    }
    ~Frame() {
        if (dismissed_) return;
        rt::ld(c_, RA, SP, ra_);
        for (unsigned k = n_; k-- > 0;) rt::lq(c_, sreg(k), SP, base_ + 16 * static_cast<s32>(k));
        for (unsigned k = nf_; k-- > 0;) rt::lwc1(c_, F20 + k, SP, 4 * static_cast<s32>(k));
        rt::addiu(c_, SP, SP, size_);
    }
    // A `jr` to a target outside the switch's labels leaves the function without its epilogue.
    void dismiss() { dismissed_ = true; }
    Frame(const Frame&) = delete;
    Frame& operator=(const Frame&) = delete;

private:
    static Reg sreg(unsigned k) { return k == 8 ? FP : S0 + k; }
    EEContext& c_;
    s32 size_, ra_;
    unsigned n_;
    s32 base_;
    unsigned nf_;
    bool dismissed_ = false;
};

// The 16-byte wrappers: `addiu sp, sp, -16; sd ra, 0(sp); jal fn; ld ra, 0(sp); jr ra; addiu sp, sp, 16` (one block
// of 8).
void wrap(EEContext& c, u32 link, Fn fn) {
    guest::enter(c, 8);
    Frame f(c, 16, 0);
    call(c, link, fn);
}

// A `jr` switch: `lw r, 0(r)` already loaded the target; returns it (the caller dispatches on it).
u32 jr_target(EEContext& c, Reg r) { return rt::reg32(c, r); }

}  // namespace

// === pb_main.c: the persona / party picks of the panel (0x1FC720-0x1FD628) ===========================================

void sub_1FC720(EEContext& ctx) {
    // a0 = a unit: which panel the party pick shows. The two candidate scans sub_1FC980 / sub_1FCB30 (retail printf
    // users, left recompiled) fill the frame's two result blocks (+96 / +124 and +48 / +120); the first test compares
    // the incoming $v1 with ($v1 / 3) and the HP test uses the incoming $s0 (30 * s0 / 100 against s0): the original
    // reads both registers before writing them.
    guest::enter(ctx, 11);
    Frame f(ctx, 128, 32, 2, 0);
    move(ctx, S1, A0);
    li(ctx, V0, 3);
    rt::div(ctx, V1, V0);
    rt::mflo(ctx, V0);
    rt::slt(ctx, AT, V0, V1);
    if (nz(ctx, AT)) {
        charge(ctx, 3);
        move(ctx, V0, ZR);
    } else {
        charge(ctx, 5);
        rt::lhu(ctx, V0, S1, 0);
        rt::nor(ctx, V0, V0, ZR);
        rt::andi(ctx, V0, V0, 0x4u);
        if (!nz(ctx, V0)) {
            charge(ctx, 5);
            kassert(ctx, kPbMain, 170, 0x1fc778u);
        }
        charge(ctx, 19);
        move(ctx, A0, S1);
        rt::addiu(ctx, A1, SP, 96);
        rt::addiu(ctx, A2, SP, 124);
        call(ctx, 0x1fc78cu, rg::fn_sub_1FC980_001fc980);
        move(ctx, A0, S1);
        rt::addiu(ctx, A1, SP, 48);
        rt::addiu(ctx, A2, SP, 120);
        call(ctx, 0x1fc7a0u, rg::fn_sub_1FCB30_001fcb30);
        rt::sll(ctx, V0, S0, 4);
        rt::subu(ctx, V0, V0, S0);
        rt::sll(ctx, V1, V0, 1);
        li(ctx, V0, 100);
        rt::div(ctx, V1, V0);
        rt::mflo(ctx, V0);
        rt::slt(ctx, AT, V0, S0);
        auto pick_b = [&](u32 link) {  // sub_1FD350(unit, block +48, count +120)
            charge(ctx, 7);
            move(ctx, A0, S1);
            rt::addiu(ctx, A1, SP, 48);
            call(ctx, link, rg::fn_sub_1FD350_001fd350);
            li(ctx, V0, 1);
        };
        bool done = false;
        if (!nz(ctx, AT)) {
            charge(ctx, 3);
            rt::lw(ctx, A2, SP, 120);
            if (nz(ctx, A2)) {
                pick_b(0x1fc7e0u);
                done = true;
            }
        }
        if (!done) {
            charge(ctx, 3);
            rt::lw(ctx, A2, SP, 124);
            if (nz(ctx, A2)) {  // sub_1FCE20(unit, block +96, count +124)
                charge(ctx, 7);
                move(ctx, A0, S1);
                rt::addiu(ctx, A1, SP, 96);
                call(ctx, 0x1fc808u, rg::fn_sub_1FCE20_001fce20);
                li(ctx, V0, 1);
                done = true;
            }
        }
        if (!done) {
            charge(ctx, 3);
            rt::slt(ctx, V0, S0, V0);
            if (!nz(ctx, V0)) {
                charge(ctx, 3);
                rt::lw(ctx, A2, SP, 120);
                if (nz(ctx, A2)) {
                    pick_b(0x1fc83cu);
                    done = true;
                }
            }
        }
        if (!done) {
            charge(ctx, 1);
            move(ctx, V0, ZR);
        }
    }
    charge(ctx, 6);
}

void sub_1FC870(EEContext& ctx) {
    // (a0, a1): a value of the record a1 (sub_30BC50) scaled by the factor table 0x684D70[clamp(a1->level(+6) -
    // sub_173300(a0->id(+2)), -10, 10) + 10], at most 1.0f, truncated; handed to sub_1F9E90(a0->id, value) and returned.
    guest::enter(ctx, 12);
    Frame f(ctx, 64, 48, 2, 16, 1);
    move(ctx, S0, A0);
    move(ctx, S1, A1);
    move(ctx, A0, S1);
    call(ctx, 0x1fc890u, rg::fn_sub_30BC50_0030bc50);
    u2f(ctx, V0, V1, V0, F0, F20);
    charge(ctx, 9);
    rt::lhu(ctx, A0, S0, 2);
    call(ctx, 0x1fc8d4u, rg::fn_sub_173300_00173300);
    rt::andi(ctx, V1, V0, 0xFFu);
    rt::lbu(ctx, V0, S1, 6);
    rt::subu(ctx, V0, V0, V1);
    rt::slti(ctx, AT, V0, -10);
    if (nz(ctx, AT)) {
        charge(ctx, 1);
        li(ctx, V0, -10);
    }
    charge(ctx, 3);
    rt::slti(ctx, AT, V0, 11);
    if (!nz(ctx, AT)) {
        charge(ctx, 1);
        li(ctx, V0, 10);
    }
    charge(ctx, 13);
    rt::addiu(ctx, V0, V0, 10);
    rt::sll(ctx, V1, V0, 2);
    rt::lui(ctx, V0, 0x68u);
    rt::addiu(ctx, V0, V0, 19824);
    rt::addu(ctx, V0, V0, V1);
    rt::lwc1(ctx, F0, V0, 0);
    rt::mul_s(ctx, F20, F20, F0);
    rt::lui(ctx, V0, 0x3F80u);
    rt::mtc1(ctx, V0, F0);
    rt::c_lt_s(ctx, F20, F0);
    if (rt::cop1_cond(ctx)) {
        charge(ctx, 1);
        rt::mov_s(ctx, F20, F0);
    }
    charge(ctx, 14);
    rt::cvt_w_s(ctx, F0, F20);
    rt::mfc1(ctx, S1, F0);
    rt::lhu(ctx, A0, S0, 2);
    move(ctx, A1, S1);
    call(ctx, 0x1fc950u, rg::fn_sub_1F9E90_001f9e90);
    move(ctx, V0, S1);
}

void sub_1FCCC0(EEContext& ctx) {
    // (a0, a1, a2 = an entry id): sub_17B860(a1->id, a0->id, sub_170E90(a2)->+8, 1), then the first of the 12 slots k
    // of a0 with sub_1706C0(a0->id, k) != 0 and sub_170670(a0->id, k) == a2 (K_Assert when none: k = 12 goes on), and
    // sub_170710(a0->id, k, sub_1706C0(a0->id, k) - 1).
    guest::enter(ctx, 19);
    Frame f(ctx, 80, 64, 4, 0);
    move(ctx, S2, A0);
    move(ctx, S3, A1);
    move(ctx, S1, A2);
    s16_of(ctx, A0, S1);
    call(ctx, 0x1fccecu, rg::fn_sub_170E90_00170e90);
    rt::lhu(ctx, S0, V0, 8);
    move(ctx, A0, S0);
    call(ctx, 0x1fccfcu, rg::fn_sub_17B4E0_0017b4e0);
    if (!nz(ctx, V0)) {
        charge(ctx, 5);
        kassert(ctx, kPbMain, 570, 0x1fcd18u);
    }
    charge(ctx, 9);
    rt::lh(ctx, A0, S3, 2);
    rt::lh(ctx, A1, S2, 2);
    move(ctx, A2, S0);
    li(ctx, A3, 1);
    call(ctx, 0x1fcd30u, rg::fn_sub_17B860_0017b860);
    move(ctx, S0, ZR);
    for (;;) {
        charge(ctx, 3);
        rt::slti(ctx, V0, S0, 12);
        if (!nz(ctx, V0)) break;
        guest::backedge(ctx);
        charge(ctx, 9);
        rt::lh(ctx, A0, S2, 2);
        s16_of(ctx, A1, S0);
        call(ctx, 0x1fcd50u, rg::fn_sub_1706C0_001706c0);
        s16_of(ctx, V0, V0);
        if (nz(ctx, V0)) {
            charge(ctx, 8);
            rt::lh(ctx, A0, S2, 2);
            s16_of(ctx, A1, S0);
            call(ctx, 0x1fcd74u, rg::fn_sub_170670_00170670);
            u16_of(ctx, V0, V0);
            if (eq(ctx, S1, V0)) break;
        }
        charge(ctx, 1);
        rt::addiu(ctx, S0, S0, 1);
    }
    charge(ctx, 3);
    rt::slti(ctx, V0, S0, 12);
    if (!nz(ctx, V0)) {
        charge(ctx, 5);
        kassert(ctx, kPbMain, 585, 0x1fcdb0u);
    }
    charge(ctx, 23);
    rt::lh(ctx, A0, S2, 2);
    s16_of(ctx, A1, S0);
    call(ctx, 0x1fcdc4u, rg::fn_sub_1706C0_001706c0);
    s16_of(ctx, V0, V0);
    rt::lh(ctx, A0, S2, 2);
    s16_of(ctx, A1, S0);
    rt::addiu(ctx, V0, V0, -1);
    s16_of(ctx, A2, V0);
    call(ctx, 0x1fcdecu, rg::fn_sub_170710_00170710);
}

namespace {

// sub_1FCE20's tail after `andi a0, v0, 0xffff; li v1, 2` (kind = sub_17B500): kind 2 -> sub_16CF90(id,
// sub_16C570(id) - s0), kind 1 -> sub_16CF40(id, sub_16C4F0(id) - s0) ($s5 the unit, $s0 the sub_17B5B0 result).
// `cost2`: the kind-2 block (10 when it falls through, 12 when it ends in a branch).
void pick_kind_tail(EEContext& c, u32 l1, u32 l2, u32 l3, u32 l4, u64 cost2) {
    if (eq(c, A0, V1)) {
        charge(c, cost2);
        rt::lh(c, A0, S5, 2);
        call(c, l3, rg::fn_sub_16C570_0016c570);
        u16_of(c, V0, V0);
        rt::subu(c, V0, V0, S0);
        rt::lh(c, A0, S5, 2);
        s16_of(c, A1, V0);
        call(c, l4, rg::fn_sub_16CF90_0016cf90);
        return;
    }
    charge(c, 3);
    li(c, V1, 1);
    if (eq(c, A0, V1)) {
        charge(c, 12);
        rt::lh(c, A0, S5, 2);
        call(c, l1, rg::fn_sub_16C4F0_0016c4f0);
        u16_of(c, V0, V0);
        rt::subu(c, V0, V0, S0);
        rt::lh(c, A0, S5, 2);
        s16_of(c, A1, V0);
        call(c, l2, rg::fn_sub_16CF40_0016cf40);
        return;
    }
    charge(c, 2);
}

// sub_1FCE20's pick of entry `e` (the register `er`, or the u16 at 160(sp) when `er` is ZR): the K_Assert on
// sub_17B660, sub_17B5B0 -> $s0, sub_17B860(id, id, e, 0), the kind sub_17B500 and its tail; `links` are the nine
// call / K_Assert links of the copy in use.
void pick_entry(EEContext& c, Reg er, const u32 (&links)[9], u64 cost2) {
    auto load_e = [&](Reg d) {
        if (er == ZR) rt::lhu(c, d, SP, 160);
        else move(c, d, er);
    };
    charge(c, 6);
    rt::lh(c, A0, S5, 2);
    load_e(A1);
    call(c, links[0], rg::fn_sub_17B660_0017b660);
    if (nz(c, V0)) {
        charge(c, 5);
        kassert(c, kPbMain, 533, links[1]);
    }
    charge(c, 20);
    rt::lh(c, A0, S5, 2);
    load_e(A1);
    call(c, links[2], rg::fn_sub_17B5B0_0017b5b0);
    move(c, S0, V0);
    rt::lh(c, V0, S5, 2);
    move(c, A0, V0);
    move(c, A1, A0);
    load_e(A2);
    move(c, A3, ZR);
    call(c, links[3], rg::fn_sub_17B860_0017b860);
    rt::lh(c, A0, S5, 2);
    load_e(A1);
    call(c, links[4], rg::fn_sub_17B500_0017b500);
    u16_of(c, A0, V0);
    li(c, V1, 2);
    pick_kind_tail(c, links[5], links[6], links[7], links[8], cost2);
}

}  // namespace

void sub_1FCE20(EEContext& ctx) {
    // (a0 = a unit, a1 = u16 entry ids, a2 = their count): one entry -> pick it; else split the entries by
    // sub_17C070 into two lists (+160 / +176 of the frame), score the second list by the HP after sub_17BE10 (+192),
    // take the entry with the smallest |score|; with HP >= 80% of max and a first-list entry, the first-list head wins.
    guest::enter(ctx, 16);
    Frame f(ctx, 240, 144, 9, 0);
    move(ctx, S5, A0);
    move(ctx, S7, A1);
    move(ctx, S4, A2);
    if (!nz(ctx, S4)) {
        charge(ctx, 5);
        kassert(ctx, kPbMain, 667, 0x1fce6cu);
    }
    charge(ctx, 3);
    li(ctx, V0, 1);
    if (eq(ctx, S4, V0)) {
        charge(ctx, 7);
        rt::lhu(ctx, S1, S7, 0);
        rt::lh(ctx, A0, S5, 2);
        move(ctx, A1, S1);
        call(ctx, 0x1fce8cu, rg::fn_sub_17B660_0017b660);
        if (nz(ctx, V0)) {
            charge(ctx, 5);
            kassert(ctx, kPbMain, 533, 0x1fcea8u);
        }
        charge(ctx, 20);
        rt::lh(ctx, A0, S5, 2);
        move(ctx, A1, S1);
        call(ctx, 0x1fceb8u, rg::fn_sub_17B5B0_0017b5b0);
        move(ctx, S0, V0);
        rt::lh(ctx, V0, S5, 2);
        move(ctx, A0, V0);
        move(ctx, A1, A0);
        move(ctx, A2, S1);
        move(ctx, A3, ZR);
        call(ctx, 0x1fced8u, rg::fn_sub_17B860_0017b860);
        rt::lh(ctx, A0, S5, 2);
        move(ctx, A1, S1);
        call(ctx, 0x1fcee8u, rg::fn_sub_17B500_0017b500);
        u16_of(ctx, A0, V0);
        li(ctx, V1, 2);
        pick_kind_tail(ctx, 0x1fcf18u, 0x1fcf34u, 0x1fcf48u, 0x1fcf64u, 10);
        charge(ctx, 2);
    } else {
        charge(ctx, 13);
        move(ctx, A0, S5);
        call(ctx, 0x1fcf78u, rg::fn_datCalcGetHp_002ffd70);
        u16_of(ctx, FP, V0);
        move(ctx, A0, S5);
        call(ctx, 0x1fcf88u, rg::fn_datCalcGetMaxHp_002ffdf0);
        u16_of(ctx, S0, V0);
        move(ctx, S2, ZR);
        move(ctx, S1, ZR);
        move(ctx, S3, ZR);
        for (;;) {
            charge(ctx, 3);
            rt::slt(ctx, V0, S3, S4);
            if (!nz(ctx, V0)) break;
            guest::backedge(ctx);
            charge(ctx, 8);
            rt::sll(ctx, V0, S3, 1);
            rt::addu(ctx, V0, S7, V0);
            rt::lhu(ctx, S6, V0, 0);
            move(ctx, A0, S6);
            call(ctx, 0x1fcfb8u, rg::fn_sub_17C070_0017c070);
            if (nz(ctx, V0)) {
                charge(ctx, 6);
                rt::sll(ctx, V0, S1, 1);
                rt::addu(ctx, V0, V0, SP);
                rt::sh(ctx, S6, V0, 160);
                rt::addiu(ctx, S1, S1, 1);
            } else {
                charge(ctx, 4);
                rt::sll(ctx, V0, S2, 1);
                rt::addu(ctx, V0, V0, SP);
                rt::sh(ctx, S6, V0, 176);
                rt::addiu(ctx, S2, S2, 1);
            }
            charge(ctx, 1);
            rt::addiu(ctx, S3, S3, 1);
        }
        charge(ctx, 3);
        move(ctx, S3, ZR);
        for (;;) {
            charge(ctx, 3);
            rt::slt(ctx, V0, S3, S2);
            if (!nz(ctx, V0)) break;
            guest::backedge(ctx);
            charge(ctx, 19);
            rt::sll(ctx, V0, S3, 1);
            rt::addu(ctx, V0, V0, SP);
            rt::lhu(ctx, A2, V0, 176);
            rt::lh(ctx, V0, S5, 2);
            move(ctx, A0, V0);
            move(ctx, A1, A0);
            move(ctx, A3, ZR);
            rt::addiu(ctx, T0, SP, 236);
            rt::addiu(ctx, T1, SP, 232);
            rt::addiu(ctx, T2, SP, 228);
            call(ctx, 0x1fd034u, rg::fn_sub_17BE10_0017be10);
            rt::lw(ctx, V0, SP, 236);
            rt::addu(ctx, V0, FP, V0);
            rt::subu(ctx, V1, V0, S0);
            rt::sll(ctx, V0, S3, 2);
            rt::addu(ctx, V0, V0, SP);
            rt::sw(ctx, V1, V0, 192);
            rt::addiu(ctx, S3, S3, 1);
        }
        charge(ctx, 8);
        rt::lw(ctx, A0, SP, 192);
        call(ctx, 0x1fd068u, rg::fn_abs_0051e0e0);
        move(ctx, S6, V0);
        move(ctx, S4, ZR);
        li(ctx, S3, 1);
        for (;;) {
            charge(ctx, 3);
            rt::slt(ctx, V0, S3, S2);
            if (!nz(ctx, V0)) break;
            guest::backedge(ctx);
            charge(ctx, 10);
            rt::sll(ctx, V0, S3, 2);
            rt::addu(ctx, V0, V0, SP);
            rt::addiu(ctx, V0, V0, 192);
            rt::lw(ctx, S7, V0, 0);
            move(ctx, A0, S7);
            call(ctx, 0x1fd098u, rg::fn_abs_0051e0e0);
            rt::slt(ctx, AT, V0, S6);
            if (nz(ctx, AT)) {
                charge(ctx, 5);
                move(ctx, S4, S3);
                move(ctx, A0, S7);
                call(ctx, 0x1fd0b4u, rg::fn_abs_0051e0e0);
                move(ctx, S6, V0);
            }
            charge(ctx, 1);
            rt::addiu(ctx, S3, S3, 1);
        }
        charge(ctx, 26);
        rt::sll(ctx, V0, S4, 1);
        rt::addu(ctx, V0, V0, SP);
        rt::addiu(ctx, V0, V0, 176);
        rt::lhu(ctx, S2, V0, 0);
        rt::lh(ctx, V0, S5, 2);
        move(ctx, A0, V0);
        move(ctx, A1, A0);
        move(ctx, A2, S2);
        move(ctx, A3, ZR);
        rt::addiu(ctx, T0, SP, 236);
        rt::addiu(ctx, T1, SP, 232);
        rt::addiu(ctx, T2, SP, 228);
        call(ctx, 0x1fd100u, rg::fn_sub_17BE10_0017be10);
        rt::lw(ctx, V0, SP, 236);
        rt::addu(ctx, A0, V0, FP);
        rt::sw(ctx, A0, SP, 236);
        rt::sll(ctx, V0, S0, 2);
        rt::addu(ctx, V0, V0, S0);
        rt::sll(ctx, V1, V0, 4);
        li(ctx, V0, 100);
        rt::div(ctx, V1, V0);
        rt::mflo(ctx, V0);
        rt::slt(ctx, AT, V0, A0);
        bool second = nz(ctx, AT);
        if (!second) {
            charge(ctx, 2);
            second = !nz(ctx, S1);
        }
        if (!second) {
            static constexpr u32 kFirst[9] = {0x1fd148u, 0x1fd164u, 0x1fd174u, 0x1fd194u, 0x1fd1a4u,
                                              0x1fd1d4u, 0x1fd1f0u, 0x1fd204u, 0x1fd220u};
            pick_entry(ctx, ZR, kFirst, 12);
        } else {
            static constexpr u32 kSecond[9] = {0x1fd238u, 0x1fd254u, 0x1fd264u, 0x1fd284u, 0x1fd294u,
                                               0x1fd2c4u, 0x1fd2e0u, 0x1fd2f4u, 0x1fd310u};
            pick_entry(ctx, S2, kSecond, 10);
        }
    }
    charge(ctx, 13);
}

void sub_1FD350(EEContext& ctx) {
    // (a0 = a unit, a1 = s32 entry ids, a2 = their count): sub_1FCE20's sibling over sub_170E90 entries; the chosen
    // entry goes to sub_1FCCC0(unit, unit, entry).
    guest::enter(ctx, 16);
    Frame f(ctx, 288, 144, 9, 0);
    move(ctx, S5, A0);
    move(ctx, S4, A1);
    move(ctx, S3, A2);
    if (!nz(ctx, S3)) {
        charge(ctx, 5);
        kassert(ctx, kPbMain, 762, 0x1fd39cu);
    }
    charge(ctx, 3);
    li(ctx, V0, 1);
    if (eq(ctx, S3, V0)) {
        charge(ctx, 7);
        move(ctx, A0, S5);
        move(ctx, A1, S5);
        rt::lw(ctx, A2, S4, 0);
        call(ctx, 0x1fd3bcu, rg::fn_sub_1FCCC0_001fccc0);
    } else {
        charge(ctx, 14);
        move(ctx, A0, S5);
        call(ctx, 0x1fd3d0u, rg::fn_datCalcGetHp_002ffd70);
        u16_of(ctx, V0, V0);
        rt::sq(ctx, V0, SP, 160);
        move(ctx, A0, S5);
        call(ctx, 0x1fd3e4u, rg::fn_datCalcGetMaxHp_002ffdf0);
        u16_of(ctx, S6, V0);
        move(ctx, S1, ZR);
        move(ctx, S0, ZR);
        move(ctx, S2, ZR);
        for (;;) {
            charge(ctx, 3);
            rt::slt(ctx, V0, S2, S3);
            if (!nz(ctx, V0)) break;
            guest::backedge(ctx);
            charge(ctx, 12);
            rt::sll(ctx, V0, S2, 2);
            rt::addu(ctx, V0, S4, V0);
            rt::lw(ctx, S7, V0, 0);
            s16_of(ctx, A0, S7);
            call(ctx, 0x1fd418u, rg::fn_sub_170E90_00170e90);
            rt::lhu(ctx, A0, V0, 8);
            call(ctx, 0x1fd424u, rg::fn_sub_17C070_0017c070);
            if (nz(ctx, V0)) {
                charge(ctx, 6);
                rt::sll(ctx, V0, S0, 2);
                rt::addu(ctx, V0, V0, SP);
                rt::sw(ctx, S7, V0, 176);
                rt::addiu(ctx, S0, S0, 1);
            } else {
                charge(ctx, 4);
                rt::sll(ctx, V0, S1, 2);
                rt::addu(ctx, V0, V0, SP);
                rt::sw(ctx, S7, V0, 208);
                rt::addiu(ctx, S1, S1, 1);
            }
            charge(ctx, 1);
            rt::addiu(ctx, S2, S2, 1);
        }
        charge(ctx, 3);
        move(ctx, S2, ZR);
        for (;;) {
            charge(ctx, 3);
            rt::slt(ctx, V0, S2, S1);
            if (!nz(ctx, V0)) break;
            guest::backedge(ctx);
            charge(ctx, 22);
            rt::sll(ctx, S3, S2, 2);
            rt::addu(ctx, V0, S4, S3);
            rt::lh(ctx, A0, V0, 0);
            call(ctx, 0x1fd484u, rg::fn_sub_170E90_00170e90);
            rt::lhu(ctx, A2, V0, 8);
            rt::lh(ctx, V0, S5, 2);
            move(ctx, A0, V0);
            move(ctx, A1, A0);
            li(ctx, A3, 1);
            rt::addiu(ctx, T0, SP, 284);
            rt::addiu(ctx, T1, SP, 280);
            rt::addiu(ctx, T2, SP, 276);
            call(ctx, 0x1fd4acu, rg::fn_sub_17BE10_0017be10);
            rt::lw(ctx, V1, SP, 284);
            rt::lq(ctx, V0, SP, 160);
            rt::addu(ctx, V0, V0, V1);
            rt::subu(ctx, V1, V0, S6);
            rt::addu(ctx, V0, S3, SP);
            rt::sw(ctx, V1, V0, 240);
            rt::addiu(ctx, S2, S2, 1);
        }
        charge(ctx, 8);
        rt::lw(ctx, A0, SP, 240);
        call(ctx, 0x1fd4e0u, rg::fn_abs_0051e0e0);
        move(ctx, S7, V0);
        move(ctx, S3, ZR);
        li(ctx, S2, 1);
        for (;;) {
            charge(ctx, 3);
            rt::slt(ctx, V0, S2, S1);
            if (!nz(ctx, V0)) break;
            guest::backedge(ctx);
            charge(ctx, 10);
            rt::sll(ctx, V0, S2, 2);
            rt::addu(ctx, V0, V0, SP);
            rt::addiu(ctx, V0, V0, 240);
            rt::lw(ctx, FP, V0, 0);
            move(ctx, A0, FP);
            call(ctx, 0x1fd510u, rg::fn_abs_0051e0e0);
            rt::slt(ctx, AT, V0, S7);
            if (nz(ctx, AT)) {
                charge(ctx, 5);
                move(ctx, S3, S2);
                move(ctx, A0, FP);
                call(ctx, 0x1fd52cu, rg::fn_abs_0051e0e0);
                move(ctx, S7, V0);
            }
            charge(ctx, 1);
            rt::addiu(ctx, S2, S2, 1);
        }
        charge(ctx, 28);
        rt::sll(ctx, S1, S3, 2);
        rt::addu(ctx, V0, S4, S1);
        rt::lh(ctx, A0, V0, 0);
        call(ctx, 0x1fd554u, rg::fn_sub_170E90_00170e90);
        rt::lhu(ctx, A2, V0, 8);
        rt::lh(ctx, V0, S5, 2);
        move(ctx, A0, V0);
        move(ctx, A1, A0);
        li(ctx, A3, 1);
        rt::addiu(ctx, T0, SP, 284);
        rt::addiu(ctx, T1, SP, 280);
        rt::addiu(ctx, T2, SP, 276);
        call(ctx, 0x1fd57cu, rg::fn_sub_17BE10_0017be10);
        rt::lw(ctx, V1, SP, 284);
        rt::lq(ctx, V0, SP, 160);
        rt::addu(ctx, A0, V1, V0);
        rt::sw(ctx, A0, SP, 284);
        rt::sll(ctx, V0, S6, 2);
        rt::addu(ctx, V0, V0, S6);
        rt::sll(ctx, V1, V0, 4);
        li(ctx, V0, 100);
        rt::div(ctx, V1, V0);
        rt::mflo(ctx, V0);
        rt::slt(ctx, AT, V0, A0);
        bool second = nz(ctx, AT);
        if (!second) {
            charge(ctx, 2);
            second = !nz(ctx, S0);
        }
        if (!second) {
            charge(ctx, 7);
            move(ctx, A0, S5);
            move(ctx, A1, S5);
            rt::lw(ctx, A2, SP, 176);
            call(ctx, 0x1fd5ccu, rg::fn_sub_1FCCC0_001fccc0);
        } else {
            charge(ctx, 6);
            rt::addu(ctx, V0, S1, SP);
            move(ctx, A0, S5);
            move(ctx, A1, S5);
            rt::lw(ctx, A2, V0, 208);
            call(ctx, 0x1fd5ecu, rg::fn_sub_1FCCC0_001fccc0);
        }
    }
    charge(ctx, 13);
}

// === bp_root.c: the panel tasks and the panel mode word (0x1FD890-0x1FF428) ==========================================

void bpRoot_UpdateBattlePanelTask(EEContext& ctx) {
    // [bpRoot_UpdateBattlePanelTask] a0 = the "battle panel" task, its work at +60: the per-frame panel layers
    // (sub_21BCB0 / sub_24C110 / sub_25D020), the opening sequence (0x400: until sub_21BAB0 says done, then sub_253410
    // and the bit cleared; returns 0 while it runs), nothing more while gBtl +12 has 0x80 without 0x800, else the
    // command panel record (sub_210D90 ...), the command menu (0x4: sub_1FFF40, and once sub_2053C0 says picked,
    // sub_201B50 and 0x8 set), the tutorial (0x8000 until sub_24D0C0), the persona change (0x1000 until sub_249600),
    // the list states (0x10000 / 0x20000: sub_245E50 when sub_249130 is done). Returns 0.
    guest::enter(ctx, 14);
    Frame f(ctx, 32, 16, 1, 0);
    [&] {
        rt::lw(ctx, S0, A0, 60);
        call(ctx, 0x1fd8a0u, rg::fn_sub_21BCB0_0021bcb0);
        call(ctx, 0x1fd8a8u, rg::fn_sub_24C110_0024c110);
        call(ctx, 0x1fd8b0u, rg::fn_sub_25D020_0025d020);
        rt::lw(ctx, V0, S0, 0);
        rt::andi(ctx, V0, V0, 0x400u);
        if (nz(ctx, V0)) {
            charge(ctx, 4);
            call(ctx, 0x1fd8c8u, rg::fn_sub_21BAB0_0021bab0);
            if (nz(ctx, V0)) {
                charge(ctx, 3);
                move(ctx, V0, ZR);
                return;
            }
            charge(ctx, 8);
            call(ctx, 0x1fd8d8u, rg::fn_sub_253410_00253410);
            rt::lw(ctx, V1, S0, 0);
            li(ctx, V0, -1025);
            rt::and_(ctx, V0, V1, V0);
            rt::sw(ctx, V0, S0, 0);
        }
        charge(ctx, 5);
        rt::lw(ctx, V0, GP, bpanel::kGpGBtl);
        rt::lw(ctx, V1, V0, 12);
        rt::andi(ctx, V0, V1, 0x80u);
        if (nz(ctx, V0)) {
            charge(ctx, 3);
            rt::andi(ctx, V0, V1, 0x800u);
            if (!nz(ctx, V0)) {
                charge(ctx, 3);
                move(ctx, V0, ZR);
                return;
            }
        }
        charge(ctx, 13);
        cmd_record(ctx, A0, S0);
        call(ctx, 0x1fd93cu, rg::fn_sub_210D90_00210d90);
        call(ctx, 0x1fd944u, rg::fn_sub_2510D0_002510d0);
        call(ctx, 0x1fd94cu, rg::fn_sub_251A80_00251a80);
        rt::lw(ctx, V0, S0, 0);
        rt::andi(ctx, V0, V0, 0x4u);
        if (nz(ctx, V0)) {
            charge(ctx, 6);
            call(ctx, 0x1fd964u, rg::fn_sub_1FFF40_001fff40);
            call(ctx, 0x1fd96cu, rg::fn_sub_2053C0_002053c0);
            if (nz(ctx, V0)) {
                charge(ctx, 5);
                rt::lw(ctx, V0, S0, 0);
                rt::nor(ctx, V0, V0, ZR);
                rt::andi(ctx, V0, V0, 0x8u);
                if (nz(ctx, V0)) {
                    charge(ctx, 5);
                    call(ctx, 0x1fd990u, rg::fn_sub_201B50_00201b50);
                    rt::lw(ctx, V0, S0, 0);
                    rt::ori(ctx, V0, V0, 0x8u);
                    rt::sw(ctx, V0, S0, 0);
                }
            }
        }
        charge(ctx, 6);
        call(ctx, 0x1fd9a4u, rg::fn_sub_20EDF0_0020edf0);
        rt::lw(ctx, V0, S0, 0);
        rt::andi(ctx, V0, V0, 0x8000u);
        if (nz(ctx, V0)) {
            charge(ctx, 4);
            call(ctx, 0x1fd9bcu, rg::fn_sub_24D0C0_0024d0c0);
            if (!nz(ctx, V0)) {
                charge(ctx, 7);
                call(ctx, 0x1fd9ccu, rg::fn_nullsub_11_0021c7e0);
                rt::lw(ctx, V1, S0, 0);
                rt::lui(ctx, V0, 0xFFFFu);
                rt::ori(ctx, V0, V0, 0x7FFFu);
                rt::and_(ctx, V0, V1, V0);
                rt::sw(ctx, V0, S0, 0);
            }
        }
        charge(ctx, 8);
        call(ctx, 0x1fd9e8u, rg::fn_sub_252060_00252060);
        call(ctx, 0x1fd9f0u, rg::fn_sub_2492B0_002492b0);
        rt::lw(ctx, V0, S0, 0);
        rt::andi(ctx, V0, V0, 0x1000u);
        if (nz(ctx, V0)) {
            charge(ctx, 4);
            call(ctx, 0x1fda08u, rg::fn_sub_249600_00249600);
            if (!nz(ctx, V0)) {
                charge(ctx, 4);
                rt::lw(ctx, V1, S0, 0);
                li(ctx, V0, -4097);
                rt::and_(ctx, V0, V1, V0);
                rt::sw(ctx, V0, S0, 0);
            }
        }
        charge(ctx, 15);
        call(ctx, 0x1fda28u, rg::fn_sub_248620_00248620);
        call(ctx, 0x1fda30u, rg::fn_sub_242CC0_00242cc0);
        call(ctx, 0x1fda38u, rg::fn_sub_25C220_0025c220);
        call(ctx, 0x1fda40u, rg::fn_sub_267180_00267180);
        call(ctx, 0x1fda48u, rg::fn_sub_27B610_0027b610);
        rt::lw(ctx, V1, S0, 0);
        rt::lui(ctx, V0, 0x1u);
        rt::and_(ctx, V0, V1, V0);
        if (nz(ctx, V0)) {
            charge(ctx, 4);
            call(ctx, 0x1fda64u, rg::fn_sub_249130_00249130);
            if (!nz(ctx, V0)) {
                charge(ctx, 5);
                rt::lw(ctx, V1, S0, 0);
                rt::lui(ctx, V0, 0x2u);
                rt::and_(ctx, V0, V1, V0);
                if (nz(ctx, V0)) {
                    charge(ctx, 7);
                    call(ctx, 0x1fda88u, rg::fn_sub_245E50_00245e50);
                    rt::lw(ctx, V1, S0, 0);
                    rt::lui(ctx, V0, 0xFFFDu);
                    rt::ori(ctx, V0, V0, 0xFFFFu);
                    rt::and_(ctx, V0, V1, V0);
                    rt::sw(ctx, V0, S0, 0);
                }
            }
        }
        charge(ctx, 1);
        move(ctx, V0, ZR);
    }();
    charge(ctx, 5);
}

void bpRoot_UpdateBattlePanelDrawTask(EEContext& ctx) {
    // [bpRoot_UpdateBattlePanelDrawTask] a0 = the "battle panel draw" task, the panel work at +60: nothing while gBtl
    // +12 has 0x80 without 0x800, else the panel drawers in their fixed order (the command panel record sub_213E80,
    // the menu layers, sub_2016B0 while 0x4 is set without 0x20, sub_243150 unless 0x40000). Returns 0.
    guest::enter(ctx, 9);
    Frame f(ctx, 32, 16, 1, 0);
    [&] {
        rt::lw(ctx, S0, A0, 60);
        rt::lw(ctx, V0, GP, bpanel::kGpGBtl);
        rt::lw(ctx, V1, V0, 12);
        rt::andi(ctx, V0, V1, 0x80u);
        if (nz(ctx, V0)) {
            charge(ctx, 3);
            rt::andi(ctx, V0, V1, 0x800u);
            if (!nz(ctx, V0)) {
                charge(ctx, 3);
                move(ctx, V0, ZR);
                return;
            }
        }
        charge(ctx, 21);
        cmd_record(ctx, A0, S0);
        call(ctx, 0x1fdb08u, rg::fn_sub_213E80_00213e80);
        call(ctx, 0x1fdb10u, rg::fn_sub_252F30_00252f30);
        call(ctx, 0x1fdb18u, rg::fn_sub_209540_00209540);
        call(ctx, 0x1fdb20u, rg::fn_sub_23F540_0023f540);
        call(ctx, 0x1fdb28u, rg::fn_sub_24CCA0_0024cca0);
        call(ctx, 0x1fdb30u, rg::fn_sub_2095A0_002095a0);
        call(ctx, 0x1fdb38u, rg::fn_sub_2532B0_002532b0);
        rt::lw(ctx, V1, S0, 0);
        rt::andi(ctx, V0, V1, 0x4u);
        if (nz(ctx, V0)) {
            charge(ctx, 4);
            rt::nor(ctx, V0, V1, ZR);
            rt::andi(ctx, V0, V0, 0x20u);
            if (nz(ctx, V0)) {
                charge(ctx, 2);
                call(ctx, 0x1fdb60u, rg::fn_sub_2016B0_002016b0);
            }
        }
        charge(ctx, 8);
        call(ctx, 0x1fdb68u, rg::fn_sub_20F260_0020f260);
        rt::lw(ctx, V0, S0, 0);
        rt::nor(ctx, V1, V0, ZR);
        rt::lui(ctx, V0, 0x4u);
        rt::and_(ctx, V0, V1, V0);
        if (nz(ctx, V0)) {
            charge(ctx, 2);
            call(ctx, 0x1fdb88u, rg::fn_sub_243150_00243150);
        }
        charge(ctx, 13);
        call(ctx, 0x1fdb90u, rg::fn_sub_241910_00241910);
        call(ctx, 0x1fdb98u, rg::fn_sub_248BB0_00248bb0);
        call(ctx, 0x1fdba0u, rg::fn_sub_2520F0_002520f0);
        call(ctx, 0x1fdba8u, rg::fn_sub_25C9C0_0025c9c0);
        call(ctx, 0x1fdbb0u, rg::fn_sub_25D470_0025d470);
        call(ctx, 0x1fdbb8u, rg::fn_sub_27B880_0027b880);
        move(ctx, V0, ZR);
    }();
    charge(ctx, 5);
}

void sub_1FDD60(EEContext& ctx) {
    // Open the command menu: sub_1FF890, then mode |= 0x4.
    guest::enter(ctx, 15);
    Frame f(ctx, 32, 16, 1, 0);
    panel_work(ctx, V0, S0);
    call(ctx, 0x1fdd74u, rg::fn_sub_1FF890_001ff890);
    rt::lw(ctx, V1, S0, 0);
    rt::ori(ctx, V1, V1, 0x4u);
    rt::sw(ctx, V1, S0, 0);
}

void sub_1FDDA0(EEContext& ctx) {
    // Close the command menu: sub_1FFC60, then mode &= ~0x4 and &= ~0x8 (two stores).
    guest::enter(ctx, 19);
    Frame f(ctx, 32, 16, 1, 0);
    panel_work(ctx, V0, S0);
    call(ctx, 0x1fddb4u, rg::fn_sub_1FFC60_001ffc60);
    rt::lw(ctx, A0, S0, 0);
    li(ctx, V1, -5);
    rt::and_(ctx, A0, A0, V1);
    rt::sw(ctx, A0, S0, 0);
    li(ctx, V1, -9);
    rt::and_(ctx, V1, A0, V1);
    rt::sw(ctx, V1, S0, 0);
}

void sub_1FDDF0(EEContext& ctx) {
    // Is a command decided? (mode 0x4 required, else K_Assert and 0): 0x200 or 0x2000 -> 1 (each asserts 0x8 is
    // clear), else mode & 0x8.
    guest::enter(ctx, 8);
    Frame f(ctx, 16, 0);
    panel_work(ctx, V0, V0);
    rt::lw(ctx, V1, V0, 0);
    rt::andi(ctx, V0, V1, 0x4u);
    if (!nz(ctx, V0)) {
        charge(ctx, 6);
        kassert(ctx, kBpRoot, 467, 0x1fdea0u);
        move(ctx, V0, ZR);
    } else {
        charge(ctx, 3);
        rt::andi(ctx, V0, V1, 0x200u);
        auto decided = [&](s32 line, u32 link) {
            charge(ctx, 4);
            rt::nor(ctx, V0, V1, ZR);
            rt::andi(ctx, V0, V0, 0x8u);
            if (!nz(ctx, V0)) {
                charge(ctx, 5);
                kassert(ctx, kBpRoot, line, link);
            }
            charge(ctx, 3);
            li(ctx, V0, 1);
        };
        if (nz(ctx, V0)) {
            decided(452, 0x1fde38u);
        } else {
            charge(ctx, 3);
            rt::andi(ctx, V0, V1, 0x2000u);
            if (nz(ctx, V0)) {
                decided(457, 0x1fde74u);
            } else {
                charge(ctx, 3);
                rt::andi(ctx, V0, V1, 0x8u);
            }
        }
    }
    charge(ctx, 4);
}

void sub_1FDEC0(EEContext& ctx) {
    // Re-open the command choice: sub_201D10, sub_205410, mode &= ~0x8.
    guest::enter(ctx, 18);
    Frame f(ctx, 32, 16, 1, 0);
    panel_work(ctx, V0, S0);
    call(ctx, 0x1fded4u, rg::fn_sub_201D10_00201d10);
    call(ctx, 0x1fdedcu, rg::fn_sub_205410_00205410);
    rt::lw(ctx, A0, S0, 0);
    li(ctx, V1, -9);
    rt::and_(ctx, V1, A0, V1);
    rt::sw(ctx, V1, S0, 0);
}

void sub_1FDF10(EEContext& ctx) {
    // a0 = the command record { +0 flags, +4 kind, +8 / +10 / +12 u16 arguments, +16 }: cleared flags, then by the
    // panel: 0x2000 -> kind 10 (+16 = work +16); 0x200 -> kind 4 with work +12 == 1 -> flag 2, +10 = 324; == 0 ->
    // flag 1, +10 = 0; else K_Assert; else sub_207F70 -> 13, sub_207FC0 -> 7, else the menu's state sub_2054C0 through
    // the table 0x7B7230 (0 -> 1, 1 -> 2 with +10 = sub_205500, 2 -> 3 with +8 = sub_205550, 3 -> K_Assert, 4 -> 5 with
    // +12 = sub_2055A0, 5 -> 6, 6 -> 7, >= 7 -> K_Assert).
    guest::enter(ctx, 11);
    Frame f(ctx, 48, 32, 2, 0);
    move(ctx, S1, A0);
    panel_work(ctx, V1, S0);
    rt::lw(ctx, V1, S0, 0);
    rt::andi(ctx, V1, V1, 0x4u);
    if (!nz(ctx, V1)) {
        charge(ctx, 5);
        kassert(ctx, kBpRoot, 489, 0x1fdf48u);
    }
    charge(ctx, 5);
    rt::sw(ctx, ZR, S1, 0);
    rt::lw(ctx, A0, S0, 0);
    rt::andi(ctx, V1, A0, 0x2000u);
    if (nz(ctx, V1)) {
        charge(ctx, 6);
        li(ctx, V1, 10);
        rt::sw(ctx, V1, S1, 4);
        rt::lw(ctx, V1, S0, 16);
        rt::sw(ctx, V1, S1, 16);
    } else {
        charge(ctx, 3);
        rt::andi(ctx, V1, A0, 0x200u);
        if (nz(ctx, V1)) {
            charge(ctx, 6);
            li(ctx, V1, 4);
            rt::sw(ctx, V1, S1, 4);
            rt::lw(ctx, A0, S0, 12);
            li(ctx, V1, 1);
            if (eq(ctx, A0, V1)) {
                charge(ctx, 7);
                rt::lw(ctx, V1, S1, 0);
                rt::ori(ctx, V1, V1, 0x2u);
                rt::sw(ctx, V1, S1, 0);
                li(ctx, V1, 324);
                rt::sh(ctx, V1, S1, 10);
            } else {
                charge(ctx, 2);
                if (!nz(ctx, A0)) {
                    charge(ctx, 6);
                    rt::lw(ctx, V1, S1, 0);
                    rt::ori(ctx, V1, V1, 0x1u);
                    rt::sw(ctx, V1, S1, 0);
                    rt::sh(ctx, ZR, S1, 10);
                } else {
                    charge(ctx, 2);
                    charge(ctx, 7);
                    kassert(ctx, kBpRoot, 512, 0x1fdff0u);
                }
            }
        } else {
            charge(ctx, 4);
            call(ctx, 0x1fe000u, rg::fn_sub_207F70_00207f70);
            if (nz(ctx, V0)) {
                charge(ctx, 4);
                li(ctx, V1, 13);
                rt::sw(ctx, V1, S1, 4);
            } else {
                charge(ctx, 4);
                call(ctx, 0x1fe020u, rg::fn_sub_207FC0_00207fc0);
                if (nz(ctx, V0)) {
                    charge(ctx, 4);
                    li(ctx, V1, 7);
                    rt::sw(ctx, V1, S1, 4);
                } else {
                    charge(ctx, 5);
                    call(ctx, 0x1fe040u, rg::fn_sub_2054C0_002054c0);
                    rt::sltiu(ctx, AT, V0, 7);
                    u32 target = 0x1fe0f4u;  // `sltiu; beqz at` -> the K_Assert case
                    if (nz(ctx, AT)) {
                        charge(ctx, 7);
                        rt::lui(ctx, A0, 0x7Bu);
                        rt::addiu(ctx, A0, A0, 29232);
                        rt::sll(ctx, V1, V0, 2);
                        rt::addu(ctx, V1, V1, A0);
                        rt::lw(ctx, V1, V1, 0);
                        target = jr_target(ctx, V1);
                    }
                    auto kind = [&](s32 k) {
                        li(ctx, V1, k);
                        rt::sw(ctx, V1, S1, 4);
                    };
                    auto kind_arg = [&](s32 k, u32 link, Fn fn, s32 off) {
                        li(ctx, V0, k);
                        rt::sw(ctx, V0, S1, 4);
                        call(ctx, link, fn);
                        rt::sh(ctx, V0, S1, off);
                    };
                    switch (target) {
                    case 0x1fe070u: charge(ctx, 4); kind(1); break;
                    case 0x1fe080u: charge(ctx, 7); kind_arg(2, 0x1fe088u, rg::fn_sub_205500_00205500, 10); break;
                    case 0x1fe09cu: charge(ctx, 7); kind_arg(3, 0x1fe0a4u, rg::fn_sub_205550_00205550, 8); break;
                    case 0x1fe0b8u: charge(ctx, 7); kind_arg(5, 0x1fe0c0u, rg::fn_sub_2055A0_002055a0, 12); break;
                    case 0x1fe0d4u: charge(ctx, 4); kind(6); break;
                    case 0x1fe0e4u: charge(ctx, 4); kind(7); break;
                    case 0x1fe0f4u:
                        charge(ctx, 5);
                        kassert(ctx, kBpRoot, 553, 0x1fe100u);
                        break;
                    default:
                        f.dismiss();
                        rt::lookup_func(target)(ctx);
                        return;
                    }
                }
            }
        }
    }
    charge(ctx, 6);
}

void sub_1FE120(EEContext& ctx) {
    // Enter the analyse / shuffle layer: with the menu open (0x4) sub_201C30, mode |= 0x40000, sub_20FC40,
    // sub_2085E0; always sub_208B30 and mode |= 0x10.
    guest::enter(ctx, 9);
    Frame f(ctx, 32, 16, 1, 0);
    panel_work(ctx, V0, S0);
    rt::lw(ctx, V0, S0, 0);
    rt::andi(ctx, V0, V0, 0x4u);
    if (nz(ctx, V0)) {
        charge(ctx, 10);
        call(ctx, 0x1fe144u, rg::fn_sub_201C30_00201c30);
        rt::lw(ctx, V1, S0, 0);
        rt::lui(ctx, V0, 0x4u);
        rt::or_(ctx, V0, V1, V0);
        rt::sw(ctx, V0, S0, 0);
        call(ctx, 0x1fe15cu, rg::fn_sub_20FC40_0020fc40);
        call(ctx, 0x1fe164u, rg::fn_sub_2085E0_002085e0);
    }
    charge(ctx, 10);
    call(ctx, 0x1fe16cu, rg::fn_sub_208B30_00208b30);
    rt::lw(ctx, V1, S0, 0);
    rt::ori(ctx, V1, V1, 0x10u);
    rt::sw(ctx, V1, S0, 0);
}

void sub_1FE1A0(EEContext& ctx) {
    // Leave it: with the menu open sub_201E00, mode &= ~0x40000, sub_20FC90, sub_208630; always sub_2094F0 and
    // mode &= ~0x10.
    guest::enter(ctx, 9);
    Frame f(ctx, 32, 16, 1, 0);
    panel_work(ctx, V0, S0);
    rt::lw(ctx, V0, S0, 0);
    rt::andi(ctx, V0, V0, 0x4u);
    if (nz(ctx, V0)) {
        charge(ctx, 11);
        call(ctx, 0x1fe1c4u, rg::fn_sub_201E00_00201e00);
        rt::lw(ctx, V1, S0, 0);
        rt::lui(ctx, V0, 0xFFFBu);
        rt::ori(ctx, V0, V0, 0xFFFFu);
        rt::and_(ctx, V0, V1, V0);
        rt::sw(ctx, V0, S0, 0);
        call(ctx, 0x1fe1e0u, rg::fn_sub_20FC90_0020fc90);
        call(ctx, 0x1fe1e8u, rg::fn_sub_208630_00208630);
    }
    charge(ctx, 11);
    call(ctx, 0x1fe1f0u, rg::fn_sub_2094F0_002094f0);
    rt::lw(ctx, A0, S0, 0);
    li(ctx, V1, -17);
    rt::and_(ctx, V1, A0, V1);
    rt::sw(ctx, V1, S0, 0);
}

void sub_1FE220(EEContext& ctx) {
    // sub_208720() != 0 || (mode & 0x10000) != 0.
    guest::enter(ctx, 10);
    Frame f(ctx, 32, 16, 1, 0);
    panel_work(ctx, V0, S0);
    call(ctx, 0x1fe234u, rg::fn_sub_208720_00208720);
    rt::sltu(ctx, V0, ZR, V0);
    if (!nz(ctx, V0)) {
        charge(ctx, 4);
        rt::lw(ctx, V1, S0, 0);
        rt::lui(ctx, V0, 0x1u);
        rt::and_(ctx, V0, V1, V0);
        rt::sltu(ctx, V0, ZR, V0);
    }
    charge(ctx, 5);
}

namespace {
// sub_1FE270 / sub_1FE2E0: open a target list of side `side` for the argument a0: sub_20FCE0, sub_208680,
// sub_20FE30(record, side, a0), mode |= 0x100.
void open_target_list(EEContext& c, s32 side, const u32 (&links)[3]) {
    guest::enter(c, 27);
    Frame f(c, 48, 32, 2, 0);
    move(c, S1, A0);
    panel_work(c, V0, S0);
    call(c, links[0], rg::fn_sub_20FCE0_0020fce0);
    call(c, links[1], rg::fn_sub_208680_00208680);
    cmd_record(c, A0, S0);
    if (side == 0) move(c, A1, ZR);
    else li(c, A1, side);
    move(c, A2, S1);
    call(c, links[2], rg::fn_sub_20FE30_0020fe30);
    rt::lw(c, V1, S0, 0);
    rt::ori(c, V1, V1, 0x100u);
    rt::sw(c, V1, S0, 0);
}
}  // namespace

void sub_1FE270(EEContext& ctx) {
    static constexpr u32 kLinks[3] = {0x1fe28cu, 0x1fe294u, 0x1fe2b0u};
    open_target_list(ctx, 0, kLinks);
}

void sub_1FE2E0(EEContext& ctx) {
    static constexpr u32 kLinks[3] = {0x1fe2fcu, 0x1fe304u, 0x1fe320u};
    open_target_list(ctx, 1, kLinks);
}

void sub_1FE350(EEContext& ctx) {
    // Close the target list: sub_20FD30, sub_2086D0, sub_210D60(record), mode &= ~0x100.
    guest::enter(ctx, 23);
    Frame f(ctx, 32, 16, 1, 0);
    panel_work(ctx, V0, S0);
    call(ctx, 0x1fe364u, rg::fn_sub_20FD30_0020fd30);
    call(ctx, 0x1fe36cu, rg::fn_sub_2086D0_002086d0);
    cmd_record(ctx, A0, S0);
    call(ctx, 0x1fe380u, rg::fn_sub_210D60_00210d60);
    rt::lw(ctx, A0, S0, 0);
    li(ctx, V1, -257);
    rt::and_(ctx, V1, A0, V1);
    rt::sw(ctx, V1, S0, 0);
}

void sub_1FE3B0(EEContext& ctx) {
    // Drop the fixed command (0x200 asserted) and hand a0 to sub_21B8B0.
    guest::enter(ctx, 11);
    Frame f(ctx, 48, 32, 2, 0);
    move(ctx, S1, A0);
    panel_work(ctx, V0, S0);
    rt::lw(ctx, V0, S0, 0);
    rt::andi(ctx, V0, V0, 0x200u);
    if (!nz(ctx, V0)) {
        charge(ctx, 5);
        kassert(ctx, kBpRoot, 652, 0x1fe3e8u);
    }
    charge(ctx, 13);
    rt::lw(ctx, V1, S0, 0);
    li(ctx, V0, -513);
    rt::and_(ctx, V0, V1, V0);
    rt::sw(ctx, V0, S0, 0);
    move(ctx, A0, S1);
    call(ctx, 0x1fe404u, rg::fn_sub_21B8B0_0021b8b0);
}

namespace {
// sub_1FE430 / sub_1FE4A0: assert `bit`, clear it, call `fn`.
void drop_bit(EEContext& c, u32 bit, s32 mask, s32 line, u32 assert_link, u32 link, Fn fn) {
    guest::enter(c, 9);
    Frame f(c, 32, 16, 1, 0);
    panel_work(c, V0, S0);
    rt::lw(c, V0, S0, 0);
    rt::andi(c, V0, V0, bit);
    if (!nz(c, V0)) {
        charge(c, 5);
        kassert(c, kBpRoot, line, assert_link);
    }
    charge(c, 11);
    rt::lw(c, V1, S0, 0);
    li(c, V0, mask);
    rt::and_(c, V0, V1, V0);
    rt::sw(c, V0, S0, 0);
    call(c, link, fn);
}

// sub_1FE510 / sub_1FE580: with the menu open (asserted), mode |= `bit` and the work word `off` = a0.
void set_bit_arg(EEContext& c, u32 bit, s32 off, s32 line, u32 assert_link) {
    guest::enter(c, 11);
    Frame f(c, 48, 32, 2, 0);
    move(c, S0, A0);
    panel_work(c, V1, S1);
    rt::lw(c, V1, S1, 0);
    rt::andi(c, V1, V1, 0x4u);
    if (!nz(c, V1)) {
        charge(c, 5);
        kassert(c, kBpRoot, line, assert_link);
    }
    charge(c, 10);
    rt::lw(c, V1, S1, 0);
    rt::ori(c, V1, V1, bit);
    rt::sw(c, V1, S1, 0);
    rt::sw(c, S0, S1, off);
}
}  // namespace

void sub_1FE430(EEContext& ctx) { drop_bit(ctx, 0x200u, -513, 666, 0x1fe460u, 0x1fe478u, rg::fn_sub_21B830_0021b830); }

void sub_1FE4A0(EEContext& ctx) { drop_bit(ctx, 0x2000u, -8193, 680, 0x1fe4d0u, 0x1fe4e8u, rg::fn_sub_24A7A0_0024a7a0); }

void sub_1FE510(EEContext& ctx) { set_bit_arg(ctx, 0x200u, 12, 689, 0x1fe548u); }

void sub_1FE580(EEContext& ctx) { set_bit_arg(ctx, 0x2000u, 16, 698, 0x1fe5b8u); }

void sub_1FE5F0(EEContext& ctx) {
    // Start the opening sequence: sub_21B940, mode |= 0x400.
    guest::enter(ctx, 15);
    Frame f(ctx, 32, 16, 1, 0);
    panel_work(ctx, V0, S0);
    call(ctx, 0x1fe604u, rg::fn_sub_21B940_0021b940);
    rt::lw(ctx, V1, S0, 0);
    rt::ori(ctx, V1, V1, 0x400u);
    rt::sw(ctx, V1, S0, 0);
}

void sub_1FE630(EEContext& ctx) {
    // mode & 0x400 (the opening sequence runs).
    guest::enter(ctx, 6);
    panel_work(ctx, V0, V0);
    rt::lw(ctx, V0, V0, 0);
    rt::andi(ctx, V0, V0, 0x400u);
}

void sub_1FE650(EEContext& ctx) {
    // a0 = a request { +0, +4, +8 flags, +16 u16 id / word, +20 count, +24 }: K_Assert unless sub_289030(+16); when
    // sub_242A60 says a slot is free, take it (sub_242260) and set it up: the first of flags 1 / 2 / 4 / 8 picks the
    // mode 0 / 1 / 3 / 2 (sub_242320), sub_242A50(+16), 0x10 -> sub_242600(+0), 0x20 -> sub_242720(+4), 0x40 ->
    // sub_242A30, count >= 2 -> sub_242C20(+24), then sub_242540.
    guest::enter(ctx, 10);
    Frame f(ctx, 48, 32, 2, 0);
    move(ctx, S1, A0);
    rt::lhu(ctx, A0, A0, 16);
    call(ctx, 0x1fe668u, rg::fn_sub_289030_00289030);
    if (!nz(ctx, V0)) {
        charge(ctx, 5);
        kassert(ctx, kBpRoot, 725, 0x1fe684u);
    }
    charge(ctx, 4);
    call(ctx, 0x1fe68cu, rg::fn_sub_242A60_00242a60);
    if (nz(ctx, V0)) {
        charge(ctx, 7);
        call(ctx, 0x1fe69cu, rg::fn_sub_242260_00242260);
        move(ctx, S0, V0);
        rt::lw(ctx, V1, S1, 8);
        rt::andi(ctx, V0, V1, 0x1u);
        auto mode = [&](u64 cost, s32 m, u32 link) {
            charge(ctx, cost);
            move(ctx, A0, S0);
            if (m == 0) move(ctx, A1, ZR);
            else li(ctx, A1, m);
            call(ctx, link, rg::fn_sub_242320_00242320);
        };
        if (nz(ctx, V0)) {
            mode(6, 0, 0x1fe6c0u);
        } else {
            charge(ctx, 3);
            rt::andi(ctx, V0, V1, 0x2u);
            if (nz(ctx, V0)) {
                mode(6, 1, 0x1fe6e4u);
            } else {
                charge(ctx, 3);
                rt::andi(ctx, V0, V1, 0x4u);
                if (nz(ctx, V0)) {
                    mode(6, 3, 0x1fe708u);
                } else {
                    charge(ctx, 3);
                    rt::andi(ctx, V0, V1, 0x8u);
                    if (nz(ctx, V0)) mode(4, 2, 0x1fe72cu);
                }
            }
        }
        charge(ctx, 8);
        move(ctx, A0, S0);
        rt::lw(ctx, A1, S1, 16);
        call(ctx, 0x1fe73cu, rg::fn_sub_242A50_00242a50);
        rt::lw(ctx, V0, S1, 8);
        rt::andi(ctx, V0, V0, 0x10u);
        if (nz(ctx, V0)) {
            charge(ctx, 4);
            move(ctx, A0, S0);
            rt::lw(ctx, A1, S1, 0);
            call(ctx, 0x1fe75cu, rg::fn_sub_242600_00242600);
        }
        charge(ctx, 4);
        rt::lw(ctx, V0, S1, 8);
        rt::andi(ctx, V0, V0, 0x20u);
        if (nz(ctx, V0)) {
            charge(ctx, 4);
            move(ctx, A0, S0);
            rt::lw(ctx, A1, S1, 4);
            call(ctx, 0x1fe77cu, rg::fn_sub_242720_00242720);
        }
        charge(ctx, 4);
        rt::lw(ctx, V0, S1, 8);
        rt::andi(ctx, V0, V0, 0x40u);
        if (nz(ctx, V0)) {
            charge(ctx, 3);
            move(ctx, A0, S0);
            call(ctx, 0x1fe798u, rg::fn_sub_242A30_00242a30);
        }
        charge(ctx, 4);
        rt::lw(ctx, A2, S1, 20);
        rt::slti(ctx, AT, A2, 2);
        if (!nz(ctx, AT)) {
            charge(ctx, 4);
            move(ctx, A0, S0);
            rt::lw(ctx, A1, S1, 24);
            call(ctx, 0x1fe7b8u, rg::fn_sub_242C20_00242c20);
        }
        charge(ctx, 3);
        move(ctx, A0, S0);
        call(ctx, 0x1fe7c4u, rg::fn_sub_242540_00242540);
    }
    charge(ctx, 6);
}

void sub_1FE810(EEContext& ctx) {
    // Open the item list for a0 (-1: all, sub_2453D0(0) + sub_2441B0(1); else sub_2453D0(u16 a0) + sub_2441B0(0)),
    // mode |= 0x10000; for the items 335 / 324 also sub_208680.
    guest::enter(ctx, 10);
    Frame f(ctx, 48, 32, 2, 0);
    move(ctx, S1, A0);
    panel_work(ctx, V0, S0);
    li(ctx, V0, -1);
    if (eq(ctx, S1, V0)) {
        charge(ctx, 12);
        move(ctx, A0, ZR);
        call(ctx, 0x1fe83cu, rg::fn_sub_2453D0_002453d0);
        li(ctx, A0, 1);
        call(ctx, 0x1fe848u, rg::fn_sub_2441B0_002441b0);
    } else {
        charge(ctx, 10);
        u16_of(ctx, A0, S1);
        call(ctx, 0x1fe86cu, rg::fn_sub_2453D0_002453d0);
        move(ctx, A0, ZR);
        call(ctx, 0x1fe878u, rg::fn_sub_2441B0_002441b0);
    }
    rt::lw(ctx, A0, S0, 0);
    rt::lui(ctx, V1, 0x1u);
    rt::or_(ctx, V1, A0, V1);
    rt::sw(ctx, V1, S0, 0);
    charge(ctx, 3);
    li(ctx, V1, 335);
    bool hit = eq(ctx, S1, V1);
    if (!hit) {
        charge(ctx, 3);
        li(ctx, V1, 324);
        hit = eq(ctx, S1, V1);
    }
    if (hit) {
        charge(ctx, 2);
        call(ctx, 0x1fe8a8u, rg::fn_sub_208680_00208680);
    }
    charge(ctx, 6);
}

namespace {
// sub_1FE8D0 / sub_1FE920: `fn`, sub_2086D0, mode &= ~0x10000.
void close_list(EEContext& c, u32 link, Fn fn, u32 link2) {
    guest::enter(c, 19);
    Frame f(c, 32, 16, 1, 0);
    panel_work(c, V0, S0);
    call(c, link, fn);
    call(c, link2, rg::fn_sub_2086D0_002086d0);
    rt::lw(c, A0, S0, 0);
    rt::lui(c, V1, 0xFFFEu);
    rt::ori(c, V1, V1, 0xFFFFu);
    rt::and_(c, V1, A0, V1);
    rt::sw(c, V1, S0, 0);
}

// sub_1FE9B0 / sub_1FEA10: `fn`; with mode 0x10000, sub_245E00 and mode |= 0x20000.
void list_step(EEContext& c, u32 link, Fn fn, u32 link2) {
    guest::enter(c, 12);
    Frame f(c, 32, 16, 1, 0);
    panel_work(c, V0, S0);
    call(c, link, fn);
    rt::lw(c, A0, S0, 0);
    rt::lui(c, V1, 0x1u);
    rt::and_(c, V1, A0, V1);
    if (nz(c, V1)) {
        charge(c, 6);
        call(c, link2, rg::fn_sub_245E00_00245e00);
        rt::lw(c, A0, S0, 0);
        rt::lui(c, V1, 0x2u);
        rt::or_(c, V1, A0, V1);
        rt::sw(c, V1, S0, 0);
    }
    charge(c, 5);
}
}  // namespace

void sub_1FE8D0(EEContext& ctx) { close_list(ctx, 0x1fe8e4u, rg::fn_sub_2449D0_002449d0, 0x1fe8ecu); }

void sub_1FE920(EEContext& ctx) { close_list(ctx, 0x1fe934u, rg::fn_sub_244A00_00244a00, 0x1fe93cu); }

void sub_1FE9B0(EEContext& ctx) { list_step(ctx, 0x1fe9c4u, rg::fn_sub_248500_00248500, 0x1fe9e0u); }

void sub_1FEA10(EEContext& ctx) { list_step(ctx, 0x1fea24u, rg::fn_sub_248580_00248580, 0x1fea40u); }

void sub_1FEAB0(EEContext& ctx) {
    // Open the persona-change window for the current unit: r = sub_30C0C0() (asserted), sub_249420(r->+0, +2, +4),
    // mode |= 0x1000.
    guest::enter(ctx, 11);
    Frame f(ctx, 48, 32, 2, 0);
    panel_work(ctx, V0, S1);
    call(ctx, 0x1feac8u, rg::fn_sub_30C0C0_0030c0c0);
    move(ctx, S0, V0);
    if (!nz(ctx, S0)) {
        charge(ctx, 5);
        kassert(ctx, kBpRoot, 881, 0x1feae8u);
    }
    charge(ctx, 14);
    rt::lhu(ctx, A0, S0, 0);
    rt::lhu(ctx, A1, S0, 2);
    rt::lhu(ctx, A2, S0, 4);
    call(ctx, 0x1feafcu, rg::fn_sub_249420_00249420);
    rt::lw(ctx, V1, S1, 0);
    rt::ori(ctx, V1, V1, 0x1000u);
    rt::sw(ctx, V1, S1, 0);
}

void sub_1FEB30(EEContext& ctx) {
    // mode & 0x1000 (the persona-change window is open).
    guest::enter(ctx, 6);
    panel_work(ctx, V0, V0);
    rt::lw(ctx, V0, V0, 0);
    rt::andi(ctx, V0, V0, 0x1000u);
}

namespace {
// sub_1FEB70 / sub_1FEBB0: `fn`(the command panel record).
void on_record(EEContext& c, u32 link, Fn fn) {
    guest::enter(c, 13);
    Frame f(c, 16, 0);
    panel_work(c, V0, V0);
    cmd_record(c, A0, V0);
    call(c, link, fn);
}
}  // namespace

void sub_1FEB70(EEContext& ctx) { on_record(ctx, 0x1feb8cu, rg::fn_sub_215A30_00215a30); }

void sub_1FEBB0(EEContext& ctx) { on_record(ctx, 0x1febccu, rg::fn_sub_215A40_00215a40); }

void sub_1FEBF0(EEContext& ctx) {
    // Queue the tutorial a0: work +0x33310 = a0, mode |= 0x4000, sub_21BB00.
    guest::enter(ctx, 16);
    Frame f(ctx, 16, 0);
    panel_work(ctx, V0, V1);
    rt::lui(ctx, V0, 0x3u);
    rt::addu(ctx, V0, V1, V0);
    rt::sw(ctx, A0, V0, 13072);
    rt::lw(ctx, V0, V1, 0);
    rt::ori(ctx, V0, V0, 0x4000u);
    rt::sw(ctx, V0, V1, 0);
    call(ctx, 0x1fec18u, rg::fn_sub_21BB00_0021bb00);
}

void sub_1FEC50(EEContext& ctx) {
    // Start the queued tutorial (0x4000 asserted): sub_24CF00(work +0x33310), mode |= 0x8000.
    guest::enter(ctx, 9);
    Frame f(ctx, 32, 16, 1, 0);
    panel_work(ctx, V0, S0);
    rt::lw(ctx, V0, S0, 0);
    rt::andi(ctx, V0, V0, 0x4000u);
    if (!nz(ctx, V0)) {
        charge(ctx, 5);
        kassert(ctx, kBpRoot, 940, 0x1fec80u);
    }
    charge(ctx, 13);
    rt::lui(ctx, V0, 0x3u);
    rt::addu(ctx, V0, S0, V0);
    rt::lw(ctx, A0, V0, 13072);
    call(ctx, 0x1fec94u, rg::fn_sub_24CF00_0024cf00);
    rt::lw(ctx, V1, S0, 0);
    rt::ori(ctx, V1, V1, 0x8000u);
    rt::sw(ctx, V1, S0, 0);
}

void sub_1FEEC0(EEContext& ctx) {
    // sub_208010() || sub_208050() || sub_208130(), as 0 / 1.
    guest::enter(ctx, 7);
    Frame f(ctx, 16, 0);
    call(ctx, 0x1feec8u, rg::fn_sub_208010_00208010);
    rt::sltu(ctx, V0, ZR, V0);
    if (!nz(ctx, V0)) {
        charge(ctx, 3);
        call(ctx, 0x1feedcu, rg::fn_sub_208050_00208050);
        rt::sltu(ctx, V0, ZR, V0);
    }
    charge(ctx, 2);
    if (!nz(ctx, V0)) {
        charge(ctx, 3);
        call(ctx, 0x1feef0u, rg::fn_sub_208130_00208130);
        rt::sltu(ctx, V0, ZR, V0);
    }
    charge(ctx, 4);
}

namespace {
// sub_1FEF90 / sub_1FF160: three message ids for case u16 a0 (0..10) through the jump table (0x7B7250 / 0x7B7280:
// cases 2, 3, 4, 5, 7, 8, 9, 10 have a triple, cases 0, 1, 6 and >= 11 reach the K_Assert label, which passes $s0..$s2
// as they came), handed to sub_25BE60(s2, s1, s0).
struct NavCase {
    u32 label;
    s32 a, b, c;      // the triple (alt: the second triple when the case tests a flag / the scenario)
    s32 alt = 0;       // 0: none; 1: datGetFlag(223) picks the first line (230 / 231); 2: sub_17D800 picks the triple
    s32 a2 = 0, b2 = 0, c2 = 0;
};

void nav_lines(EEContext& c, u32 tbl_lo, const NavCase* cases, std::size_t n, u32 assert_label, s32 line,
               u32 assert_link, u32 final_link) {
    guest::enter(c, 9);
    Frame f(c, 64, 48, 3, 0);
    u16_of(c, V0, A0);
    rt::sltiu(c, AT, V0, 11);
    u32 target = assert_label;
    if (nz(c, AT)) {
        charge(c, 7);
        rt::lui(c, V1, 0x7Bu);
        rt::addiu(c, V1, V1, static_cast<s32>(tbl_lo));
        rt::sll(c, V0, V0, 2);
        rt::addu(c, V0, V0, V1);
        rt::lw(c, V0, V0, 0);
        target = jr_target(c, V0);
    }
    auto triple = [&](s32 a, s32 b, s32 d) {
        li(c, S2, a);
        li(c, S1, b);
        li(c, S0, d);
    };
    bool found = false;
    if (target == assert_label) {
        charge(c, 5);
        kassert(c, kBpRoot, line, assert_link);
        found = true;
    }
    for (std::size_t i = 0; i < n && !found; ++i) {
        const NavCase& k = cases[i];
        if (k.label != target) continue;
        found = true;
        if (k.alt == 0) {
            charge(c, 5);
            triple(k.a, k.b, k.c);
        } else if (k.alt == 1) {  // `li a0, 223; jal datGetFlag`: line 1 is 230 when clear, 231 when set
            charge(c, 5);
            li(c, A0, 223);
            call(c, k.label + 4u, rg::fn_datGetFlag_0016f190);
            if (!nz(c, V0)) {
                charge(c, 3);
                li(c, S2, k.a);
            } else {
                charge(c, 1);
                li(c, S2, k.a2);
            }
            charge(c, 4);
            li(c, S1, k.b);
            li(c, S0, k.c);
        } else {  // `jal sub_17D800` (the scenario): the first triple for The Journey, the second for The Answer
            charge(c, 4);
            call(c, k.label, rg::fn_sub_17D800_0017d800);
            charge(c, 5);
            if (!nz(c, V0)) triple(k.a, k.b, k.c);
            else triple(k.a2, k.b2, k.c2);
        }
    }
    if (!found) {
        f.dismiss();
        rt::lookup_func(target)(c);
        return;
    }
    charge(c, 12);
    move(c, A0, S2);
    move(c, A1, S1);
    move(c, A2, S0);
    call(c, final_link, rg::fn_sub_25BE60_0025be60);
}
}  // namespace

void sub_1FEF90(EEContext& ctx) {
    static const NavCase kCases[] = {
        {0x1fefd0u, 227, 228, 229},
        {0x1fefe4u, 230, 232, 233, 1, 231},
        {0x1ff018u, 234, 235, 236},
        {0x1ff02cu, 237, 238, 239},
        {0x1ff040u, 240, 241, 242},
        {0x1ff054u, 243, 244, 245},
        {0x1ff068u, 246, 247, 248, 2, 252, 253, 254},
        {0x1ff0a0u, 249, 250, 251},
    };
    nav_lines(ctx, 29264, kCases, std::size(kCases), 0x1ff0b4u, 1128, 0x1ff0c0u, 0x1ff0d4u);
}

void sub_1FF160(EEContext& ctx) {
    static const NavCase kCases[] = {
        {0x1ff1a0u, 255, 256, 257},
        {0x1ff1b4u, 258, 259, 260},
        {0x1ff1c8u, 261, 262, 263},
        {0x1ff1dcu, 264, 265, 266},
        {0x1ff1f0u, 267, 268, 269},
        {0x1ff204u, 270, 271, 272},
        {0x1ff218u, 273, 274, 275, 2, 279, 280, 281},
        {0x1ff250u, 276, 277, 278},
    };
    nav_lines(ctx, 29312, kCases, std::size(kCases), 0x1ff264u, 1214, 0x1ff270u, 0x1ff284u);
}

// The 16-byte wrappers of bp_root.c (each forwards its arguments to one callee).
#define P3FES_BP_WRAPPERS(X)                                   \
    X(sub_1FDBE0, 0x1fdbe8u, fn_sub_1FDC00_001fdc00)           \
    X(sub_1FDD20, 0x1fdd28u, fn_sub_20F3B0_0020f3b0)           \
    X(sub_1FDD40, 0x1fdd48u, fn_sub_20F570_0020f570)           \
    X(sub_1FE7F0, 0x1fe7f8u, fn_sub_244120_00244120)           \
    X(sub_1FE970, 0x1fe978u, fn_sub_244A40_00244a40)           \
    X(sub_1FE990, 0x1fe998u, fn_sub_244E10_00244e10)           \
    X(sub_1FEA70, 0x1fea78u, fn_sub_249180_00249180)           \
    X(sub_1FEA90, 0x1fea98u, fn_sub_208010_00208010)           \
    X(sub_1FEB50, 0x1feb58u, fn_sub_242AE0_00242ae0)           \
    X(sub_1FEC30, 0x1fec38u, fn_sub_21BB50_0021bb50)           \
    X(sub_1FECC0, 0x1fecc8u, fn_sub_24D0C0_0024d0c0)           \
    X(sub_1FECE0, 0x1fece8u, fn_sub_2079C0_002079c0)           \
    X(sub_1FED00, 0x1fed08u, fn_sub_207BF0_00207bf0)           \
    X(sub_1FED20, 0x1fed28u, fn_sub_207A10_00207a10)           \
    X(sub_1FED40, 0x1fed48u, fn_sub_207C40_00207c40)           \
    X(sub_1FED60, 0x1fed68u, fn_sub_207A60_00207a60)           \
    X(sub_1FED80, 0x1fed88u, fn_sub_207C90_00207c90)           \
    X(sub_1FEDA0, 0x1feda8u, fn_sub_207AB0_00207ab0)           \
    X(sub_1FEDC0, 0x1fedc8u, fn_sub_207CE0_00207ce0)           \
    X(sub_1FEDE0, 0x1fede8u, fn_sub_207B00_00207b00)           \
    X(sub_1FEE00, 0x1fee08u, fn_sub_207D30_00207d30)           \
    X(sub_1FEE20, 0x1fee28u, fn_sub_207B50_00207b50)           \
    X(sub_1FEE40, 0x1fee48u, fn_sub_207D80_00207d80)           \
    X(sub_1FEE60, 0x1fee68u, fn_sub_207BA0_00207ba0)           \
    X(sub_1FEE80, 0x1fee88u, fn_sub_207DD0_00207dd0)           \
    X(sub_1FEEA0, 0x1feea8u, fn_sub_20F9A0_0020f9a0)           \
    X(sub_1FEF10, 0x1fef18u, fn_sub_242B80_00242b80)           \
    X(sub_1FEF30, 0x1fef38u, fn_sub_251F40_00251f40)           \
    X(sub_1FEF50, 0x1fef58u, fn_sub_252E90_00252e90)           \
    X(sub_1FEF70, 0x1fef78u, fn_sub_252EE0_00252ee0)           \
    X(sub_1FF100, 0x1ff108u, fn_sub_25C190_0025c190)           \
    X(sub_1FF120, 0x1ff128u, fn_sub_25C1E0_0025c1e0)           \
    X(sub_1FF140, 0x1ff148u, fn_sub_25C110_0025c110)           \
    X(sub_1FF2B0, 0x1ff2b8u, fn_sub_25C190_0025c190)           \
    X(sub_1FF2D0, 0x1ff2d8u, fn_sub_25C1E0_0025c1e0)           \
    X(sub_1FF2F0, 0x1ff2f8u, fn_sub_25C110_0025c110)           \
    X(sub_1FF310, 0x1ff318u, fn_sub_25D800_0025d800)           \
    X(sub_1FF330, 0x1ff338u, fn_sub_25D850_0025d850)           \
    X(sub_1FF350, 0x1ff358u, fn_sub_25D760_0025d760)           \
    X(sub_1FF370, 0x1ff378u, fn_sub_25D7B0_0025d7b0)           \
    X(sub_1FF390, 0x1ff398u, fn_sub_20FD80_0020fd80)           \
    X(sub_1FF3B0, 0x1ff3b8u, fn_sub_20FDD0_0020fdd0)           \
    X(sub_1FF3D0, 0x1ff3d8u, fn_sub_27B9F0_0027b9f0)           \
    X(sub_1FF3F0, 0x1ff3f8u, fn_sub_27BA90_0027ba90)           \
    X(sub_1FF410, 0x1ff418u, fn_sub_27BAE0_0027bae0)

#define P3FES_BP_WRAP_DEF(name, link, callee) \
    void name(EEContext& ctx) { wrap(ctx, link, rg::callee); }
P3FES_BP_WRAPPERS(P3FES_BP_WRAP_DEF)
#undef P3FES_BP_WRAP_DEF

// === bp_misc.c: the battle's unit lists (0x1FF430-0x1FF888) ========================================================

namespace {
// `lw r, 156(u); nor r, r, zero; andi r, r, 8`: nonzero when the unit is not on the field (bit 3 clear).
bool off_field(EEContext& c, Reg r, Reg u) {
    rt::lw(c, r, u, 156);
    rt::nor(c, r, r, ZR);
    rt::andi(c, r, r, 0x8u);
    return nz(c, r);
}
// `lw r, -18692(gp)` asserted non-null (the gBtl of bp_misc.c's functions).
void gbtl_asserted(EEContext& c, Reg r, s32 line, u32 link) {
    rt::lw(c, r, GP, bpanel::kGpGBtl);
    if (!nz(c, r)) {
        charge(c, 5);
        kassert(c, kBpMisc, line, link);
    }
}
}  // namespace

void sub_1FF430(EEContext& ctx) {
    // The unit on the field whose slot (+168) is a0, searched in gBtl's four unit lists (+336 + 8k); K_Assert and 0
    // when none.
    guest::enter(ctx, 8);
    Frame f(ctx, 48, 32, 2, 0);
    move(ctx, S1, A0);
    gbtl_asserted(ctx, S0, 47, 0x1ff45cu);
    const bool found = [&] {
        charge(ctx, 3);
        move(ctx, A0, ZR);
        for (;;) {
            charge(ctx, 3);
            rt::slti(ctx, V0, A0, 4);
            if (!nz(ctx, V0)) return false;
            guest::backedge(ctx);
            charge(ctx, 5);
            rt::sll(ctx, V0, A0, 3);
            rt::addu(ctx, V0, S0, V0);
            rt::lw(ctx, V0, V0, 336);
            for (;;) {
                charge(ctx, 2);
                if (!nz(ctx, V0)) break;
                guest::backedge(ctx);
                charge(ctx, 5);
                if (!off_field(ctx, V1, V0)) {
                    charge(ctx, 3);
                    rt::lw(ctx, V1, V0, 168);
                    if (eq(ctx, V1, S1)) {
                        charge(ctx, 2);
                        return true;
                    }
                }
                charge(ctx, 1);
                rt::lw(ctx, V0, V0, 2612);
            }
            charge(ctx, 1);
            rt::addiu(ctx, A0, A0, 1);
        }
    }();
    if (!found) {
        charge(ctx, 6);
        kassert(ctx, kBpMisc, 61, 0x1ff4d4u);
        move(ctx, V0, ZR);
    }
    charge(ctx, 6);
}

void sub_1FF500(EEContext& ctx) {
    // The party unit on the field (gBtl +336) whose id (+164) is a0; K_Assert and 0 when none.
    guest::enter(ctx, 8);
    Frame f(ctx, 48, 32, 2, 0);
    move(ctx, S0, A0);
    gbtl_asserted(ctx, S1, 71, 0x1ff52cu);
    charge(ctx, 3);
    rt::lw(ctx, V0, S1, 336);
    const bool found = [&] {
        for (;;) {
            charge(ctx, 2);
            if (!nz(ctx, V0)) return false;
            guest::backedge(ctx);
            charge(ctx, 5);
            if (!off_field(ctx, V1, V0)) {
                charge(ctx, 3);
                rt::lhu(ctx, V1, V0, 164);
                if (eq(ctx, V1, S0)) {
                    charge(ctx, 2);
                    return true;
                }
            }
            charge(ctx, 1);
            rt::lw(ctx, V0, V0, 2612);
        }
    }();
    if (!found) {
        charge(ctx, 6);
        kassert(ctx, kBpMisc, 82, 0x1ff580u);
        move(ctx, V0, ZR);
    }
    charge(ctx, 6);
}

void sub_1FF5B0(EEContext& ctx) {
    // The number of party units on the field (gBtl +336).
    guest::enter(ctx, 6);
    Frame f(ctx, 32, 16, 1, 0);
    gbtl_asserted(ctx, S0, 93, 0x1ff5d4u);
    charge(ctx, 4);
    move(ctx, V0, ZR);
    rt::lw(ctx, A0, S0, 336);
    for (;;) {
        charge(ctx, 2);
        if (!nz(ctx, A0)) break;
        guest::backedge(ctx);
        charge(ctx, 5);
        if (!off_field(ctx, V1, A0)) {
            charge(ctx, 1);
            rt::addiu(ctx, V0, V0, 1);
        }
        charge(ctx, 1);
        rt::lw(ctx, A0, A0, 2612);
    }
    charge(ctx, 5);
}

void sub_1FF630(EEContext& ctx) {
    // The id (+164) of the a0-th party unit on the field counted from the end of the list (sub_1FF5B0 inlined: count -
    // 1 first, down to a0); K_Assert and 0 when none.
    guest::enter(ctx, 9);
    Frame f(ctx, 64, 48, 3, 0);
    move(ctx, S1, A0);
    gbtl_asserted(ctx, S0, 136, 0x1ff660u);
    charge(ctx, 3);
    gbtl_asserted(ctx, S2, 93, 0x1ff680u);
    charge(ctx, 4);
    move(ctx, V1, ZR);
    rt::lw(ctx, A0, S2, 336);
    for (;;) {
        charge(ctx, 2);
        if (!nz(ctx, A0)) break;
        guest::backedge(ctx);
        charge(ctx, 5);
        if (!off_field(ctx, V0, A0)) {
            charge(ctx, 1);
            rt::addiu(ctx, V1, V1, 1);
        }
        charge(ctx, 1);
        rt::lw(ctx, A0, A0, 2612);
    }
    charge(ctx, 4);
    rt::addiu(ctx, V1, V1, -1);
    rt::lw(ctx, A0, S0, 336);
    const bool found = [&] {
        for (;;) {
            charge(ctx, 2);
            if (!nz(ctx, A0)) return false;
            guest::backedge(ctx);
            charge(ctx, 5);
            if (!off_field(ctx, V0, A0)) {
                charge(ctx, 2);
                if (eq(ctx, V1, S1)) {
                    charge(ctx, 3);
                    rt::lhu(ctx, V0, A0, 164);
                    return true;
                }
                charge(ctx, 1);
                rt::addiu(ctx, V1, V1, -1);
            }
            charge(ctx, 1);
            rt::lw(ctx, A0, A0, 2612);
        }
    }();
    if (!found) {
        charge(ctx, 6);
        kassert(ctx, kBpMisc, 153, 0x1ff710u);
        move(ctx, V0, ZR);
    }
    charge(ctx, 7);
}

void sub_1FF740(EEContext& ctx) {
    // The panel layout from the story flags: flag 4887 -> 2; else flag 321 -> 0 (asserting flag 320 is clear); else
    // flag 320 -> 1, otherwise 2.
    guest::enter(ctx, 7);
    Frame f(ctx, 16, 0);
    li(ctx, A0, 4887);
    call(ctx, 0x1ff74cu, rg::fn_datGetFlag_0016f190);
    if (nz(ctx, V0)) {
        charge(ctx, 3);
        li(ctx, V0, 2);
    } else {
        charge(ctx, 5);
        li(ctx, A0, 321);
        call(ctx, 0x1ff76cu, rg::fn_datGetFlag_0016f190);
        if (nz(ctx, V0)) {
            charge(ctx, 5);
            li(ctx, A0, 320);
            call(ctx, 0x1ff780u, rg::fn_datGetFlag_0016f190);
            if (nz(ctx, V0)) {
                charge(ctx, 5);
                kassert(ctx, kBpMisc, 225, 0x1ff79cu);
            }
            charge(ctx, 3);
            move(ctx, V0, ZR);
        } else {
            charge(ctx, 5);
            li(ctx, A0, 320);
            call(ctx, 0x1ff7b4u, rg::fn_datGetFlag_0016f190);
            if (nz(ctx, V0)) {
                charge(ctx, 3);
                li(ctx, V0, 1);
            } else {
                charge(ctx, 1);
                li(ctx, V0, 2);
            }
        }
    }
    charge(ctx, 4);
}

void sub_1FF7F0(EEContext& ctx) {
    // 1 when a party unit on the field has the DatUnit id (+2604 -> u16 +2) a0, else 0.
    guest::enter(ctx, 8);
    Frame f(ctx, 48, 32, 2, 0);
    move(ctx, S0, A0);
    gbtl_asserted(ctx, S1, 241, 0x1ff81cu);
    charge(ctx, 3);
    rt::lw(ctx, V1, S1, 336);
    const bool found = [&] {
        for (;;) {
            charge(ctx, 2);
            if (!nz(ctx, V1)) return false;
            guest::backedge(ctx);
            charge(ctx, 5);
            if (!off_field(ctx, V0, V1)) {
                charge(ctx, 4);
                rt::lw(ctx, V0, V1, 2604);
                rt::lhu(ctx, V0, V0, 2);
                if (eq(ctx, V0, S0)) {
                    charge(ctx, 3);
                    li(ctx, V0, 1);
                    return true;
                }
            }
            charge(ctx, 1);
            rt::lw(ctx, V1, V1, 2612);
        }
    }();
    if (!found) {
        charge(ctx, 1);
        move(ctx, V0, ZR);
    }
    charge(ctx, 6);
}

// === the 2D sprite helpers (0x21C9F0-0x21EC38) =======================================================================

void sub_21CCA0(EEContext& ctx) {
    // a0 ? a0->entries(+4) + 44 * a1 : 0 (the a1-th 44-byte sprite record of a set).
    guest::enter(ctx, 2);
    if (!nz(ctx, A0)) {
        charge(ctx, 3);
        move(ctx, V0, ZR);
    } else {
        charge(ctx, 7);
        rt::sll(ctx, V0, A1, 2);
        rt::addu(ctx, V0, V0, A1);
        rt::sll(ctx, V0, V0, 1);
        rt::addu(ctx, V0, V0, A1);
        rt::sll(ctx, V1, V0, 2);
        rt::lw(ctx, V0, A0, 4);
        rt::addu(ctx, V0, V0, V1);
    }
    charge(ctx, 2);
}

void sub_21CCE0(EEContext& ctx) {
    // The page record of a sprite: a0->set(+0)->pages(+8)[a0->page(+8)].
    guest::enter(ctx, 8);
    rt::lw(ctx, A1, A0, 0);
    rt::lw(ctx, V0, A0, 8);
    rt::sll(ctx, V1, V0, 2);
    rt::lw(ctx, V0, A1, 8);
    rt::addu(ctx, V0, V0, V1);
    rt::lw(ctx, V0, V0, 0);
}

namespace {
// The 8-byte clear of a local the compiler emitted as a byte loop: `addiu p, sp, off; li n, 8; beqz p; 1: sb zero,
// 0(p); addiu p, p, 1; addiu n, n, -1; bnez n, 1b` (a body-first loop of 7 per byte).
void clear8(EEContext& c, Reg p, Reg n, s32 off) {
    rt::addiu(c, p, SP, off);
    li(c, n, 8);
    if (!nz(c, p)) return;
    for (;;) {
        charge(c, 7);
        rt::sb(c, ZR, p, 0);
        rt::addiu(c, p, p, 1);
        rt::addiu(c, n, n, -1);
        if (!nz(c, n)) break;
        guest::backedge(c);
    }
}

// The texel rectangle of the sprite a0 as floats in the 16-byte frame: (u, u + w) at sp+8 / sp+12 (`p` the pointer
// register of the clears, `t` the scratch); the caller's block costs are around it.
void texel_u(EEContext& c, Reg p, Reg t) {
    rt::lw(c, p, A0, 20);
    rt::mtc1(c, p, F0);
    rt::cvt_s_w(c, F0, F0);
    rt::swc1(c, F0, SP, 8);
    rt::lw(c, t, A0, 12);
    rt::addu(c, t, p, t);
    rt::mtc1(c, t, F0);
    rt::cvt_s_w(c, F0, F0);
    rt::swc1(c, F0, SP, 12);
}
// (v, v + h) at sp+0 / sp+4.
void texel_v(EEContext& c, Reg p, Reg t) {
    rt::lw(c, p, A0, 24);
    rt::mtc1(c, p, F0);
    rt::cvt_s_w(c, F0, F0);
    rt::swc1(c, F0, SP, 0);
    rt::lw(c, t, A0, 16);
    rt::addu(c, t, p, t);
    rt::mtc1(c, t, F0);
    rt::cvt_s_w(c, F0, F0);
    rt::swc1(c, F0, SP, 4);
}

// out[d0] = sp[first] / dim, out[d1] = sp[second] / dim (`mtc1 dim, f0; cvt.s.w f1, f0; lwc1 f0; div.s; swc1` x2).
void uv_pair(EEContext& c, Reg dim, s32 first, s32 second, s32 d0, s32 d1) {
    rt::mtc1(c, dim, F0);
    rt::cvt_s_w(c, F1, F0);
    rt::lwc1(c, F0, SP, first);
    rt::div_s(c, F0, F0, F1);
    rt::swc1(c, F0, A1, d0);
    rt::lwc1(c, F0, SP, second);
    rt::div_s(c, F0, F0, F1);
    rt::swc1(c, F0, A1, d1);
}

// One axis of sub_21CEC0: the anchor mode in `mode` (0 = edge to edge, 1 = half a texel in from the low edge, 2 = from
// the high edge), the page size `dim`, the flip bit `bit` of a0 +4 tested through `flag`; the texel pair at sp+lo /
// sp+hi, the outputs a1 +d0 / +d1; `k` the compare constant register, `one1` / `one2` the registers of 1.0f in modes
// 1 / 2.
struct Axis {
    Reg mode, k, dim, flag, one1, one2;
    u32 bit;
    s32 lo, hi, d0, d1;
};

void uv_axis(EEContext& c, const Axis& x) {
    auto flip = [&] {  // `lw flag, 4(a0); nor; andi bit`: nonzero when not flipped
        charge(c, 5);
        rt::lw(c, x.flag, A0, 4);
        rt::nor(c, x.flag, x.flag, ZR);
        rt::andi(c, x.flag, x.flag, x.bit);
        return nz(c, x.flag);
    };
    auto mode1 = [&](s32 from, bool add) {
        charge(c, 16);
        rt::mtc1(c, x.dim, F0);
        rt::cvt_s_w(c, F2, F0);
        rt::lwc1(c, F1, SP, from);
        rt::div_s(c, F0, F1, F2);
        rt::swc1(c, F0, A1, x.d0);
        rt::lui(c, x.one1, 0x3F80u);
        rt::mtc1(c, x.one1, F0);
        if (add) rt::add_s(c, F0, F0, F1);
        else rt::sub_s(c, F0, F1, F0);
        rt::div_s(c, F0, F0, F2);
        rt::swc1(c, F0, A1, x.d1);
    };
    charge(c, 3);
    li(c, x.k, 2);
    if (eq(c, x.mode, x.k)) {
        if (flip()) {
            charge(c, 16);
            rt::lwc1(c, F3, SP, x.hi);
            rt::lui(c, x.one2, 0x3F80u);
            rt::mtc1(c, x.one2, F0);
            rt::sub_s(c, F2, F3, F0);
        } else {
            charge(c, 11);
            rt::lui(c, x.one2, 0x3F80u);
            rt::mtc1(c, x.one2, F0);
            rt::lwc1(c, F3, SP, x.lo);
            rt::add_s(c, F2, F0, F3);
        }
        rt::mtc1(c, x.dim, F0);
        rt::cvt_s_w(c, F1, F0);
        rt::div_s(c, F0, F2, F1);
        rt::swc1(c, F0, A1, x.d0);
        rt::div_s(c, F0, F3, F1);
        rt::swc1(c, F0, A1, x.d1);
        return;
    }
    charge(c, 3);
    li(c, x.k, 1);
    if (eq(c, x.mode, x.k)) {
        if (flip()) mode1(x.lo, true);
        else mode1(x.hi, false);
        return;
    }
    charge(c, 2);
    if (eq(c, x.mode, ZR)) {
        const bool straight = flip();
        charge(c, 13);
        if (straight) uv_pair(c, x.dim, x.lo, x.hi, x.d0, x.d1);
        else uv_pair(c, x.dim, x.hi, x.lo, x.d0, x.d1);
        return;
    }
    charge(c, 2);
}
}  // namespace

void sub_21CD00(EEContext& ctx) {
    // a0 = a sprite, a1 = float uv[4] (u0 v0 u1 v1): the texel rectangle divided by the page size (page +12 / +16),
    // u / v swapped by the flip bits of +4.
    guest::enter(ctx, 11);
    rt::addiu(ctx, SP, SP, -16);
    rt::lw(ctx, A3, A0, 0);
    rt::lw(ctx, V1, A0, 8);
    rt::sll(ctx, A2, V1, 2);
    rt::lw(ctx, V1, A3, 8);
    rt::addu(ctx, V1, V1, A2);
    rt::lw(ctx, T0, V1, 0);
    clear8(ctx, A2, V1, 8);
    charge(ctx, 15);
    texel_u(ctx, A2, V1);
    clear8(ctx, A2, V1, 0);
    charge(ctx, 18);
    texel_v(ctx, A2, V1);
    rt::lw(ctx, A3, T0, 12);
    rt::lw(ctx, A2, T0, 16);
    rt::lw(ctx, V1, A0, 4);
    rt::nor(ctx, V1, V1, ZR);
    rt::andi(ctx, V1, V1, 0x1u);
    if (nz(ctx, V1)) {
        charge(ctx, 13);
        uv_pair(ctx, A3, 8, 12, 0, 8);
    } else {
        charge(ctx, 9);
        uv_pair(ctx, A3, 12, 8, 0, 8);
    }
    charge(ctx, 5);
    rt::lw(ctx, V1, A0, 4);
    rt::nor(ctx, V1, V1, ZR);
    rt::andi(ctx, V1, V1, 0x2u);
    if (nz(ctx, V1)) {
        charge(ctx, 13);
        uv_pair(ctx, A2, 0, 4, 4, 12);
    } else {
        charge(ctx, 9);
        uv_pair(ctx, A2, 4, 0, 4, 12);
    }
    charge(ctx, 3);
    rt::addiu(ctx, SP, SP, 16);
}

void sub_21CEC0(EEContext& ctx) {
    // sub_21CD00 with the anchor mode a2 (0..7) through the table 0x7B75F0: the (u, v) modes 0 (0,1) 1 (2,0) 2 (0,2)
    // 3 (1,0) 4 (2,1) 5 (2,2) 6 (2,1) 7 (1,1); a2 >= 8 keeps the incoming $t0 as the u mode and a2 as the v mode.
    guest::enter(ctx, 11);
    rt::addiu(ctx, SP, SP, -16);
    rt::lw(ctx, T1, A0, 0);
    rt::lw(ctx, V1, A0, 8);
    rt::sll(ctx, A3, V1, 2);
    rt::lw(ctx, V1, T1, 8);
    rt::addu(ctx, V1, V1, A3);
    rt::lw(ctx, T1, V1, 0);
    clear8(ctx, A3, V1, 8);
    charge(ctx, 15);
    texel_u(ctx, A3, V1);
    clear8(ctx, A3, V1, 0);
    charge(ctx, 16);
    texel_v(ctx, A3, V1);
    rt::lw(ctx, A3, T1, 12);
    rt::lw(ctx, V1, T1, 16);
    rt::sltiu(ctx, AT, A2, 8);
    if (nz(ctx, AT)) {
        charge(ctx, 7);
        rt::lui(ctx, T2, 0x7Bu);
        rt::addiu(ctx, T2, T2, 30192);
        rt::sll(ctx, T1, A2, 2);
        rt::addu(ctx, T1, T1, T2);
        rt::lw(ctx, T1, T1, 0);
        const u32 target = jr_target(ctx, T1);
        auto set = [&](u64 cost, s32 u, s32 v, bool v_copies_u) {
            charge(ctx, cost);
            if (u == 0) move(ctx, T0, ZR);
            else li(ctx, T0, u);
            if (v_copies_u) move(ctx, A2, T0);
            else if (v == 0) move(ctx, A2, ZR);
            else li(ctx, A2, v);
        };
        switch (target) {
        case 0x21cfbcu: set(4, 0, 1, false); break;
        case 0x21cfccu: set(4, 2, 0, false); break;
        case 0x21cfdcu: set(4, 0, 2, false); break;
        case 0x21cfecu: set(4, 1, 0, false); break;
        case 0x21cffcu: set(4, 2, 1, false); break;
        case 0x21d00cu: set(4, 2, 2, true); break;
        case 0x21d01cu: set(4, 2, 1, false); break;
        case 0x21d02cu: set(2, 1, 1, true); break;
        default:
            rt::lookup_func(target)(ctx);
            return;
        }
    }
    uv_axis(ctx, Axis{T0, T1, A3, T0, A3, T0, 0x1u, 8, 12, 0, 8});
    uv_axis(ctx, Axis{A2, A3, V1, A0, V1, A0, 0x2u, 0, 4, 4, 12});
    charge(ctx, 3);
    rt::addiu(ctx, SP, SP, 16);
}

namespace {
// The vertex header of the sprite strips: x / y from the frame's uv rect (sp + ux / sp + vy), z = 1/zfar ($f20),
// depth word *(float*)0x960088 (through $v1) at +8; `vtx` the vertex's offset in the strip ($s1).
void vertex_head(EEContext& c, s32 vtx, s32 ux, s32 vy) {
    rt::lwc1(c, F0, SP, ux);
    rt::swc1(c, F0, S1, vtx + 16);
    rt::lwc1(c, F0, SP, vy);
    rt::swc1(c, F0, S1, vtx + 20);
    rt::swc1(c, F20, S1, vtx + 24);
}
}  // namespace

void sub_21D3B0(EEContext& ctx) {
    // a0 = a 4-vertex strip (64-byte vertices), a1 = a sprite: uv by sub_21CD00 into the frame (+64), z = 1 / the
    // main camera's zfar (sub_198590 +128), the depth word, and each vertex's RGBA from the sprite's bytes +28..+43.
    guest::enter(ctx, 30);
    Frame f(ctx, 80, 48, 2, 16, 1);
    move(ctx, S1, A0);
    move(ctx, S0, A1);
    call(ctx, 0x21d3ccu, rg::fn_sub_198590_00198590);
    rt::lui(ctx, V1, 0x3F80u);
    rt::mtc1(ctx, V1, F1);
    rt::lwc1(ctx, F0, V0, 128);
    rt::div_s(ctx, F20, F1, F0);
    move(ctx, A0, S0);
    rt::addiu(ctx, A1, SP, 64);
    call(ctx, 0x21d3f0u, rg::fn_sub_21CD00_0021cd00);
    vertex_head(ctx, 0, 64, 68);
    rt::lui(ctx, V1, 0x96u);
    rt::addiu(ctx, V1, V1, 136);
    rt::lwc1(ctx, F0, V1, 0);
    rt::swc1(ctx, F0, S1, 8);
    rt::lbu(ctx, A0, S0, 28);
    colours(ctx, A0, A1, S0, 28, S1, 32);
    charge(ctx, 11);
    rt::swc1(ctx, F0, S1, 44);
    vertex_head(ctx, 64, 72, 68);
    rt::lwc1(ctx, F0, V1, 0);
    rt::swc1(ctx, F0, S1, 72);
    rt::lbu(ctx, A0, S0, 32);
    colours(ctx, A0, A1, S0, 32, S1, 96);
    charge(ctx, 11);
    rt::swc1(ctx, F0, S1, 108);
    vertex_head(ctx, 128, 72, 76);
    rt::lwc1(ctx, F0, V1, 0);
    rt::swc1(ctx, F0, S1, 136);
    rt::lbu(ctx, A0, S0, 36);
    colours(ctx, A0, A1, S0, 36, S1, 160);
    charge(ctx, 11);
    rt::swc1(ctx, F0, S1, 172);
    vertex_head(ctx, 192, 64, 76);
    rt::lwc1(ctx, F0, V1, 0);
    rt::swc1(ctx, F0, S1, 200);
    rt::lbu(ctx, V1, S0, 40);
    colours(ctx, V1, A0, S0, 40, S1, 224);
    charge(ctx, 8);
    rt::swc1(ctx, F0, S1, 236);
}

void sub_21D890(EEContext& ctx) {
    // The four (x, y) pairs of a1 (float[8]) into the strip a0's vertices (+0 / +64 / +128 / +192).
    guest::enter(ctx, 18);
    static constexpr s32 kDst[8] = {0, 4, 64, 68, 128, 132, 192, 196};
    for (s32 i = 0; i < 8; ++i) {
        rt::lwc1(ctx, F0, A1, 4 * i);
        rt::swc1(ctx, F0, A0, kDst[i]);
    }
}

void sub_21D8E0(EEContext& ctx) {
    // The rectangle a1 = {x, y, w, h} as the strip a0's four (x, y) pairs.
    guest::enter(ctx, 26);
    rt::lwc1(ctx, F0, A1, 0);
    rt::swc1(ctx, F0, A0, 0);
    rt::lwc1(ctx, F0, A1, 4);
    rt::swc1(ctx, F0, A0, 4);
    rt::lwc1(ctx, F1, A1, 0);
    rt::lwc1(ctx, F0, A1, 8);
    rt::add_s(ctx, F0, F1, F0);
    rt::swc1(ctx, F0, A0, 64);
    rt::lwc1(ctx, F0, A1, 4);
    rt::swc1(ctx, F0, A0, 68);
    rt::lwc1(ctx, F1, A1, 0);
    rt::lwc1(ctx, F0, A1, 8);
    rt::add_s(ctx, F0, F1, F0);
    rt::swc1(ctx, F0, A0, 128);
    rt::lwc1(ctx, F1, A1, 4);
    rt::lwc1(ctx, F0, A1, 12);
    rt::add_s(ctx, F0, F1, F0);
    rt::swc1(ctx, F0, A0, 132);
    rt::lwc1(ctx, F0, A1, 0);
    rt::swc1(ctx, F0, A0, 192);
    rt::lwc1(ctx, F1, A1, 4);
    rt::lwc1(ctx, F0, A1, 12);
    rt::add_s(ctx, F0, F1, F0);
    rt::swc1(ctx, F0, A0, 196);
}

namespace {
// sub_21D950 / sub_21DD60: 16 colour bytes a1[src[i]] -> floats a0[+32.. per vertex]; the entry block (3) loads the
// first byte, each conversion is followed by a block of 4 (store, next byte), the last by a block of 3; the last
// conversion's scratch is $a1 (the pointer is dead by then), the others use $a2.
void colours16(EEContext& c, const s32 (&src)[16]) {
    static constexpr s32 kDst[16] = {32, 36, 40, 44, 96, 100, 104, 108, 160, 164, 168, 172, 224, 228, 232, 236};
    guest::enter(c, 3);
    rt::lbu(c, V1, A1, src[0]);
    for (int i = 0; i < 16; ++i) {
        u2f(c, V1, i == 15 ? A1 : A2, V1, F0, F0);
        if (i < 15) {
            charge(c, 4);
            rt::swc1(c, F0, A0, kDst[i]);
            rt::lbu(c, V1, A1, src[i + 1]);
        } else {
            charge(c, 3);
            rt::swc1(c, F0, A0, kDst[i]);
        }
    }
}
}  // namespace

void sub_21D950(EEContext& ctx) {
    // One RGBA (a1, 4 bytes) as the colour floats of all four vertices of the strip a0.
    static constexpr s32 kSrc[16] = {0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3};
    colours16(ctx, kSrc);
}

void sub_21DD60(EEContext& ctx) {
    // Four RGBAs (a1, 16 bytes) as the colour floats of the strip a0's four vertices.
    static constexpr s32 kSrc[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    colours16(ctx, kSrc);
}

void sub_21E170(EEContext& ctx) {
    // a0 = a strip, a1 = the centre (x, y), a2 = a direction (dx, dy), a3 = the size (w, h): the quad (+-w/2, +-h/2)
    // rotated by t = atan2f($f12 = dx / |d|, $f13 = -dy / |d|) (x' = x cos t - y sin t, y' = y cos t + x sin t), moved
    // to the centre, as the strip's four (x, y) pairs. The corners live in the frame at +128..+156.
    guest::enter(ctx, 51);
    Frame f(ctx, 160, 112, 5, 32, 5);
    move(ctx, S2, A0);
    move(ctx, S1, A1);
    move(ctx, S0, A3);
    rt::lwc1(ctx, F2, A2, 4);
    rt::lwc1(ctx, F1, A2, 0);
    rt::mula_s(ctx, F2, F2);
    rt::madd_s(ctx, F0, F1, F1);
    rt::sqrt_s(ctx, F0, F0);
    rt::div_s(ctx, F12, F1, F0);
    rt::div_s(ctx, F0, F2, F0);
    rt::neg_s(ctx, F13, F0);
    call(ctx, 0x21e1d8u, rg::fn_atan2f_0052ea18);
    rt::mov_s(ctx, F20, F0);
    rt::lwc1(ctx, F5, S0, 0);
    rt::neg_s(ctx, F0, F5);
    rt::lui(ctx, V1, 0x4000u);
    rt::mtc1(ctx, V1, F4);
    rt::div_s(ctx, F3, F0, F4);
    rt::swc1(ctx, F3, SP, 128);
    rt::lwc1(ctx, F2, S0, 4);
    rt::neg_s(ctx, F0, F2);
    rt::div_s(ctx, F1, F0, F4);
    rt::swc1(ctx, F1, SP, 132);
    rt::div_s(ctx, F0, F5, F4);
    rt::swc1(ctx, F0, SP, 136);
    rt::swc1(ctx, F1, SP, 140);
    rt::swc1(ctx, F0, SP, 144);
    rt::div_s(ctx, F0, F2, F4);
    rt::swc1(ctx, F0, SP, 148);
    rt::swc1(ctx, F3, SP, 152);
    rt::swc1(ctx, F0, SP, 156);
    move(ctx, S0, ZR);
    for (;;) {
        charge(ctx, 3);
        rt::slti(ctx, V1, S0, 4);
        if (!nz(ctx, V1)) break;
        guest::backedge(ctx);
        charge(ctx, 27);
        rt::sll(ctx, V0, S0, 3);
        rt::addu(ctx, V0, V0, SP);
        rt::addiu(ctx, S4, V0, 128);
        rt::addiu(ctx, S3, S4, 4);
        rt::lwc1(ctx, F24, S4, 4);
        rt::lwc1(ctx, F23, S4, 0);
        rt::mov_s(ctx, F12, F20);
        call(ctx, 0x21e258u, rg::fn_sinf_0052e878);
        rt::mov_s(ctx, F21, F0);
        rt::mov_s(ctx, F12, F20);
        call(ctx, 0x21e268u, rg::fn_cosf_0052e6d8);
        rt::mula_s(ctx, F23, F0);
        rt::msub_s(ctx, F22, F24, F21);
        rt::mov_s(ctx, F12, F20);
        call(ctx, 0x21e27cu, rg::fn_sinf_0052e878);
        rt::mov_s(ctx, F21, F0);
        rt::mov_s(ctx, F12, F20);
        call(ctx, 0x21e28cu, rg::fn_cosf_0052e6d8);
        rt::mula_s(ctx, F24, F0);
        rt::madd_s(ctx, F0, F23, F21);
        rt::swc1(ctx, F22, S4, 0);
        rt::swc1(ctx, F0, S3, 0);
        rt::addiu(ctx, S0, S0, 1);
    }
    charge(ctx, 5);
    move(ctx, A0, ZR);
    rt::lwc1(ctx, F2, S1, 0);
    rt::lwc1(ctx, F1, S1, 4);
    for (;;) {
        charge(ctx, 3);
        rt::slti(ctx, V1, A0, 4);
        if (!nz(ctx, V1)) break;
        guest::backedge(ctx);
        charge(ctx, 10);
        rt::sll(ctx, V1, A0, 3);
        rt::addu(ctx, V1, V1, SP);
        rt::addiu(ctx, V1, V1, 128);
        rt::lwc1(ctx, F0, V1, 0);
        rt::add_s(ctx, F0, F0, F2);
        rt::swc1(ctx, F0, V1, 0);
        rt::lwc1(ctx, F0, V1, 4);
        rt::add_s(ctx, F0, F0, F1);
        rt::swc1(ctx, F0, V1, 4);
        rt::addiu(ctx, A0, A0, 1);
    }
    charge(ctx, 30);
    static constexpr s32 kDst[8] = {0, 4, 64, 68, 128, 132, 192, 196};
    for (s32 i = 0; i < 8; ++i) {
        rt::lwc1(ctx, F0, SP, 128 + 4 * i);
        rt::swc1(ctx, F0, S2, kDst[i]);
    }
}

void sub_21E380(EEContext& ctx) {
    // sub_21D3B0 with an anchor mode a2 (the uv by sub_21CEC0(a1, frame +144, a2)) whose table 0x7B7610 also picks
    // which colour bytes of the sprite (+28 / +32 / +36 / +40) feed which vertex ($s5 / $s4 / $s3 / $s2); a2 >= 8 skips
    // the uv and keeps $s2..$s5 as they came.
    guest::enter(ctx, 24);
    Frame f(ctx, 160, 128, 7, 16, 1);
    move(ctx, S1, A0);
    move(ctx, S0, A1);
    move(ctx, S6, A2);
    call(ctx, 0x21e3b4u, rg::fn_sub_198590_00198590);
    rt::lui(ctx, V1, 0x3F80u);
    rt::mtc1(ctx, V1, F1);
    rt::lwc1(ctx, F0, V0, 128);
    rt::div_s(ctx, F20, F1, F0);
    rt::sltiu(ctx, AT, S6, 8);
    if (nz(ctx, AT)) {
        charge(ctx, 7);
        rt::lui(ctx, A0, 0x7Bu);
        rt::addiu(ctx, A0, A0, 30224);
        rt::sll(ctx, V1, S6, 2);
        rt::addu(ctx, V1, V1, A0);
        rt::lw(ctx, V1, V1, 0);
        const u32 target = jr_target(ctx, V1);
        // The case: sub_21CEC0(a1, sp + 144, mode), then the four colour sources (offsets from the sprite; `pair`:
        // s5 = s0 + o5, s4 = s0 + o4 or = s5, s3 = s0 + o3 or = s4 / s5, s2 = s5 or s3), as the case's instructions.
        auto uv = [&](u64 cost, s32 mode, u32 link) {
            charge(ctx, cost);
            move(ctx, A0, S0);
            rt::addiu(ctx, A1, SP, 144);
            if (mode == 0) move(ctx, A2, ZR);
            else li(ctx, A2, mode);
            call(ctx, link, rg::fn_sub_21CEC0_0021cec0);
        };
        switch (target) {
        case 0x21e3fcu:
            uv(11, 0, 0x21e408u);
            rt::addiu(ctx, S5, S0, 28);
            rt::addiu(ctx, S4, S0, 32);
            move(ctx, S3, S4);
            move(ctx, S2, S5);
            break;
        case 0x21e428u:
            uv(11, 1, 0x21e434u);
            rt::addiu(ctx, S5, S0, 32);
            move(ctx, S4, S5);
            rt::addiu(ctx, S3, S0, 36);
            move(ctx, S2, S3);
            break;
        case 0x21e454u:
            uv(11, 2, 0x21e460u);
            rt::addiu(ctx, S5, S0, 40);
            rt::addiu(ctx, S4, S0, 36);
            move(ctx, S3, S4);
            move(ctx, S2, S5);
            break;
        case 0x21e480u:
            uv(11, 3, 0x21e48cu);
            rt::addiu(ctx, S5, S0, 28);
            move(ctx, S4, S5);
            rt::addiu(ctx, S3, S0, 40);
            move(ctx, S2, S3);
            break;
        case 0x21e4acu:
        case 0x21e4d8u:
        case 0x21e504u:
        case 0x21e530u: {  // one colour for all four vertices: +32 / +36 / +40 / +28
            const bool last = target == 0x21e530u;
            const s32 mode = target == 0x21e4acu ? 4 : target == 0x21e4d8u ? 5 : target == 0x21e504u ? 6 : 7;
            const s32 off = mode == 4 ? 32 : mode == 5 ? 36 : mode == 6 ? 40 : 28;
            uv(last ? 9 : 11, mode, target + 0xCu);
            rt::addiu(ctx, S5, S0, off);
            move(ctx, S4, S5);
            move(ctx, S3, S5);
            move(ctx, S2, S5);
            break;
        }
        default:
            f.dismiss();
            rt::lookup_func(target)(ctx);
            return;
        }
    }
    charge(ctx, 12);
    rt::lwc1(ctx, F0, SP, 144);
    rt::swc1(ctx, F0, S1, 16);
    rt::lwc1(ctx, F0, SP, 148);
    rt::swc1(ctx, F0, S1, 20);
    rt::swc1(ctx, F20, S1, 24);
    rt::lui(ctx, V1, 0x96u);
    rt::addiu(ctx, V1, V1, 136);
    rt::lwc1(ctx, F0, V1, 0);
    rt::swc1(ctx, F0, S1, 8);
    rt::lbu(ctx, A0, S5, 0);
    colours(ctx, A0, A1, S5, 0, S1, 32);
    charge(ctx, 11);
    rt::swc1(ctx, F0, S1, 44);
    vertex_head(ctx, 64, 152, 148);
    rt::lwc1(ctx, F0, V1, 0);
    rt::swc1(ctx, F0, S1, 72);
    rt::lbu(ctx, A0, S4, 0);
    colours(ctx, A0, A1, S4, 0, S1, 96);
    charge(ctx, 11);
    rt::swc1(ctx, F0, S1, 108);
    vertex_head(ctx, 128, 152, 156);
    rt::lwc1(ctx, F0, V1, 0);
    rt::swc1(ctx, F0, S1, 136);
    rt::lbu(ctx, A0, S3, 0);
    colours(ctx, A0, A1, S3, 0, S1, 160);
    charge(ctx, 11);
    rt::swc1(ctx, F0, S1, 172);
    vertex_head(ctx, 192, 144, 156);
    rt::lwc1(ctx, F0, V1, 0);
    rt::swc1(ctx, F0, S1, 200);
    rt::lbu(ctx, V1, S2, 0);
    colours(ctx, V1, A0, S2, 0, S1, 224);
    charge(ctx, 13);
    rt::swc1(ctx, F0, S1, 236);
}

void sub_21EA00(EEContext& ctx) {
    // The view depth of the 16-bit screen z a0 (u32, converted unsigned): with n = the main camera's +128 and f = its
    // +132, $f0 = (-65535 f n) / (-65535 f - (z - 65535)(f - n)) (the mula / msub chain).
    guest::enter(ctx, 18);
    Frame f(ctx, 48, 32, 1, 16, 1);
    move(ctx, S0, A0);
    call(ctx, 0x21ea14u, rg::fn_sub_198590_00198590);
    rt::lwc1(ctx, F20, V0, 128);
    call(ctx, 0x21ea20u, rg::fn_sub_198590_00198590);
    rt::lwc1(ctx, F3, V0, 132);
    rt::ori(ctx, V0, ZR, 0xFFFFu);
    rt::mtc1(ctx, V0, F0);
    rt::cvt_s_w(ctx, F0, F0);
    rt::neg_s(ctx, F2, F0);
    u2f(ctx, S0, V1, V0, F0, F1);
    charge(ctx, 17);
    rt::ori(ctx, V0, ZR, 0xFFFFu);
    rt::mtc1(ctx, V0, F0);
    rt::cvt_s_w(ctx, F0, F0);
    rt::sub_s(ctx, F1, F1, F0);
    rt::sub_s(ctx, F0, F3, F20);
    rt::mula_s(ctx, F2, F3);
    rt::msub_s(ctx, F1, F1, F0);
    rt::mul_s(ctx, F0, F2, F20);
    rt::mul_s(ctx, F0, F3, F0);
    rt::div_s(ctx, F0, F0, F1);
}

void sub_21EAC0(EEContext& ctx) {
    // The z float $f12 into the strip a0's four vertices (+8 / +72 / +136 / +200).
    guest::enter(ctx, 6);
    rt::swc1(ctx, F12, A0, 8);
    rt::swc1(ctx, F12, A0, 72);
    rt::swc1(ctx, F12, A0, 136);
    rt::swc1(ctx, F12, A0, 200);
}

void sub_21EAE0(EEContext& ctx) {
    // The uv rect a1 = {u0, v0, u1, v1} into the strip a0's texture coordinates, q = 1 / the camera's zfar.
    guest::enter(ctx, 38);
    Frame f(ctx, 48, 32, 2, 0);
    move(ctx, S1, A0);
    move(ctx, S0, A1);
    call(ctx, 0x21eaf8u, rg::fn_sub_198590_00198590);
    rt::lui(ctx, V1, 0x3F80u);
    rt::mtc1(ctx, V1, F1);
    rt::lwc1(ctx, F0, V0, 128);
    rt::div_s(ctx, F1, F1, F0);
    static constexpr s32 kU[4] = {0, 8, 8, 0};
    static constexpr s32 kV[4] = {4, 4, 12, 12};
    for (s32 k = 0; k < 4; ++k) {
        rt::lwc1(ctx, F0, S0, kU[k]);
        rt::swc1(ctx, F0, S1, 64 * k + 16);
        rt::lwc1(ctx, F0, S0, kV[k]);
        rt::swc1(ctx, F0, S1, 64 * k + 20);
        rt::swc1(ctx, F1, S1, 64 * k + 24);
    }
}

void sub_21EB80(EEContext& ctx) {
    // The uv rect a1 = {u, v, du, dv} (origin + size) into the strip a0's texture coordinates, q = 1 / zfar.
    guest::enter(ctx, 46);
    Frame f(ctx, 48, 32, 2, 0);
    move(ctx, S1, A0);
    move(ctx, S0, A1);
    call(ctx, 0x21eb98u, rg::fn_sub_198590_00198590);
    rt::lui(ctx, V1, 0x3F80u);
    rt::mtc1(ctx, V1, F1);
    rt::lwc1(ctx, F0, V0, 128);
    rt::div_s(ctx, F2, F1, F0);
    rt::lwc1(ctx, F0, S0, 0);
    rt::swc1(ctx, F0, S1, 16);
    rt::lwc1(ctx, F0, S0, 4);
    rt::swc1(ctx, F0, S1, 20);
    rt::swc1(ctx, F2, S1, 24);
    rt::lwc1(ctx, F1, S0, 0);
    rt::lwc1(ctx, F0, S0, 8);
    rt::add_s(ctx, F0, F1, F0);
    rt::swc1(ctx, F0, S1, 80);
    rt::lwc1(ctx, F0, S0, 4);
    rt::swc1(ctx, F0, S1, 84);
    rt::swc1(ctx, F2, S1, 88);
    rt::lwc1(ctx, F1, S0, 0);
    rt::lwc1(ctx, F0, S0, 8);
    rt::add_s(ctx, F0, F1, F0);
    rt::swc1(ctx, F0, S1, 144);
    rt::lwc1(ctx, F1, S0, 4);
    rt::lwc1(ctx, F0, S0, 12);
    rt::add_s(ctx, F0, F1, F0);
    rt::swc1(ctx, F0, S1, 148);
    rt::swc1(ctx, F2, S1, 152);
    rt::lwc1(ctx, F0, S0, 0);
    rt::swc1(ctx, F0, S1, 208);
    rt::lwc1(ctx, F1, S0, 4);
    rt::lwc1(ctx, F0, S0, 12);
    rt::add_s(ctx, F0, F1, F0);
    rt::swc1(ctx, F0, S1, 212);
    rt::swc1(ctx, F2, S1, 216);
}

}  // namespace p3fes::game

// --- the recompiled program's entry points ---------------------------------------------------------------------------
namespace p3fes::recomp_gen {

#define P3FES_BATTLE_PANEL_SHIM(name, addr8) \
    void fn_##name##_##addr8(p3fes::EEContext& ctx) { p3fes::game::name(ctx); }
P3FES_BATTLE_PANEL_FUNCS(P3FES_BATTLE_PANEL_SHIM)
#undef P3FES_BATTLE_PANEL_SHIM

}  // namespace p3fes::recomp_gen
