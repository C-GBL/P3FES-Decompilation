// Ported from snuri00/ps2-web-recomp @ c0f476e, runtime/include/ps2/vu.hpp (lane/apply/apply_acc, the
// vector ALU, opmula/opmsub, abs/move/mr32, ftoi/itof, clip, div/sqrt/rsqrt, mfir, set_vi),
// runtime/include/ps2/vu_ops.hpp (`flags`: MAC/status computation), runtime/src/cop.cpp (cfc2/ctc2, the
// no-op vu0_wait) and recomp/codegen.cpp (per-instruction emit rules: broadcast/Q/I operand selection,
// qmfc2/qmtc2 interlock, cfc2/ctc2 vi routing, viadd/visub/viand/vior/viaddi, vnop/vwaitq, lqc2/sqc2
// masking), MIT; adapted for p3fes-port (p3fes::ee::vu0 namespace, VU0State with u32 bit-pattern storage,
// EEMemory for LQC2/SQC2, named broadcast/Q/I wrappers, no VU memory or micro-program entry points).
//
// Scope (docs/ANALYSIS/08_instruction_census.md): the binary uses VU0 only as a vector ALU from the EE in
// macro mode: 24 base mnemonics in 47 broadcast forms, no VCALLMS/VCALLMSR, no VU memory ops (VLQI/VSQI/VLQD/
// VSQD/VILWR/VISWR), no BC2* branches, no VCLIP, no VDIV, no VMTIR/VMFIR, no VR* random ops and no integer
// VI ALU ops. VCLIP, VDIV and the integer ops are kept because they are tiny and the recompiler fails closed on
// anything else (ADR-0011 §1).
//
// Verified against PCSX2 2.8.2 with compiled test vectors (tools/ours/eevec, tests/ee/vectors/pcsx2_vectors.json,
// docs/PCSX2.md "EE semantics vectors"); where PCSX2's EE interpreter and recompiler disagree the interpreter is
// the reference. Rules changed by that pass (each with the vector id that drove it):
//  * Macro-mode arithmetic DOES update MAC and STATUS: VADD/VSUB/VMUL/VMADD/VMSUB, their broadcast/Q/I forms,
//    the ACC-writing forms and VOPMULA/VOPMSUB (vu0_3417: vadd -> MAC 0x49, STATUS 0xC3; vu0_3422: dest x only
//    -> MAC 0x8). VMAX/VMINI, VABS/VMOVE/VMR32, VFTOI/VITOF, VCLIP, the integer ops and the transfers do not
//    (vu0_3030, vu0_3419). Upstream only computed the flags for micro-programs.
//  * VDIV/VRSQRT/VSQRT: x/0 sets D (bit 5) + DS (bit 11); 0/0, sqrt of a negative and rsqrt of a negative set I
//    (bit 4) + IS (bit 10); I and D are cleared first, the sticky bits stay (vu0_3280, vu0_3318, vu0_3279,
//    vu0_3294). Upstream set D only, without the sticky bit, and raised nothing for I.
//  * CTC2 to MAC ($17) is ignored: the register is read-only (vu0_3403).
// Kept as documented disagreements with PCSX2 (classes in docs/PCSX2.md):
//  * The arithmetic is the EE FPU model of fpu.h: the exponent-255 binade is kept and overflow / divide-by-zero
//    clamp to +/-0x7FFFFFFF (manual); both PCSX2 engines clamp to IEEE +/-0x7F7FFFFF ("ee-range" vectors). fpu.h's
//    add/sub follow the EE recompiler's 25-binade alignment (lead decision, ADR-0012) while PCSX2's VU path is exact
//    round-toward-zero: vu0_2839 (-2^31 + 1.0), vu0_2873 (1 - 2^-26) are "disagree:add-alignment".
//  * VMAX/VMINI flush and return the first operand on ties; PCSX2 orders -0 below +0 without flushing (vu0_3038).
//  * VRSQRT is computed as one double-precision expression; PCSX2 rounds sqrt(ft) to single first (vu0_3369).
//  * CTC2 CLIP ($18) and CMSAR0 ($27) are masked to 24 / 16 bits here; PCSX2 stores all 32 (vu0_3405, vu0_3411).
//    CTC2 STATUS writes only the sticky bits 6..11 here and in the recompiler; the interpreter writes all 32.
// Still as upstream (not observable in macro mode or not exercised):
//  * Q is written immediately: there is no Q pipeline, so VWAITQ is a no-op. The Q read after VDIV without a
//    VWAITQ already showed the new value in PCSX2 (vu0_3378).
//  * The QMFC2/QMTC2 interlock bit (instruction bit 0) is accepted and ignored.
//  * vf00 is read-only (0, 0, 0, 1.0): `apply` never writes register 0.
//  * CFC2/CTC2 of R ($20, 23-bit, vu0_3406 agrees), TPC ($26, read-only, vu0_3410 agrees) and CMSAR0 ($27).
#pragma once

#include "p3fes/ee/fpu.h"
#include "p3fes/ee_context.h"
#include "p3fes/ee_memory.h"

#include <bit>

namespace p3fes::ee::vu0 {

// `dest` is the instruction's 4-bit field: bit 3 = x, bit 2 = y, bit 1 = z, bit 0 = w. Lane i (x=0 .. w=3)
// is written when its bit is set. (manual)
inline constexpr unsigned kDestX = 8u, kDestY = 4u, kDestZ = 2u, kDestW = 1u, kDestXYZW = 15u, kDestXYZ = 14u;
inline bool lane(unsigned dest, int i) noexcept { return (dest & (8u >> i)) != 0; }

// Broadcast field (`bc`, instruction bits 1:0): which component of ft is splatted. (manual)
inline constexpr unsigned kBcX = 0u, kBcY = 1u, kBcZ = 2u, kBcW = 3u;

// ---------------------------------------------------------------------------------------------------------
// Register access as bit patterns (see fpu.h for why).
// ---------------------------------------------------------------------------------------------------------
inline u32 vf(const VU0State& v, unsigned r, int i) noexcept { return v.vf[r][i]; }
inline void set_vf(VU0State& v, unsigned r, int i, u32 x) noexcept { v.vf[r][i] = x; }
inline u32 acc(const VU0State& v, int i) noexcept { return v.acc[i]; }
inline void set_acc(VU0State& v, int i, u32 x) noexcept { v.acc[i] = x; }
inline u32 q(const VU0State& v) noexcept { return v.q; }
inline void set_q(VU0State& v, u32 x) noexcept { v.q = x; }
inline u32 i_reg(const VU0State& v) noexcept { return v.i; }
inline void set_i(VU0State& v, u32 x) noexcept { v.i = x; }

// Put VU0 back into its power-on state: vf00 = (0, 0, 0, 1.0), everything else zero. VU0State's default
// initialiser already produces this state; `reset` is the explicit re-initialisation.
inline void reset(VU0State& v) noexcept {
    v = VU0State{};
    set_vf(v, 0, 3, fpu::kOne);
}

// Apply `f(i)` to the selected lanes of vf[fd]; vf00 is never written. (manual: dest mask; vf00 read-only)
template <typename F>
inline void apply(VU0State& v, unsigned dest, unsigned fd, F f) noexcept {
    u32 r[4] = {vf(v, fd, 0), vf(v, fd, 1), vf(v, fd, 2), vf(v, fd, 3)};
    for (int i = 0; i < 4; ++i)
        if (lane(dest, i)) r[i] = f(i);
    if (fd) {
        for (int i = 0; i < 4; ++i) set_vf(v, fd, i, r[i]);
    }
}

template <typename F>
inline void apply_acc(VU0State& v, unsigned dest, F f) noexcept {
    u32 r[4] = {acc(v, 0), acc(v, 1), acc(v, 2), acc(v, 3)};
    for (int i = 0; i < 4; ++i)
        if (lane(dest, i)) r[i] = f(i);
    for (int i = 0; i < 4; ++i) set_acc(v, i, r[i]);
}

inline void update_mac_flags(VU0State& v, const u32 result[4], unsigned dest) noexcept;

// The arithmetic forms: write the selected lanes AND update MAC/STATUS from them. (manual; PCSX2 2.8.2 observed:
// vu0_3417, vu0_3422)
template <typename F>
inline void apply_arith(VU0State& v, unsigned dest, unsigned fd, F f) noexcept {
    u32 r[4] = {vf(v, fd, 0), vf(v, fd, 1), vf(v, fd, 2), vf(v, fd, 3)};
    for (int i = 0; i < 4; ++i)
        if (lane(dest, i)) r[i] = f(i);
    update_mac_flags(v, r, dest);
    if (fd) {
        for (int i = 0; i < 4; ++i) set_vf(v, fd, i, r[i]);
    }
}
template <typename F>
inline void apply_acc_arith(VU0State& v, unsigned dest, F f) noexcept {
    u32 r[4] = {acc(v, 0), acc(v, 1), acc(v, 2), acc(v, 3)};
    for (int i = 0; i < 4; ++i)
        if (lane(dest, i)) r[i] = f(i);
    update_mac_flags(v, r, dest);
    for (int i = 0; i < 4; ++i) set_acc(v, i, r[i]);
}

// ---------------------------------------------------------------------------------------------------------
// Vector ALU: fd = fs op ft (per lane) and the broadcast forms fd = fs op splat(t).
// ---------------------------------------------------------------------------------------------------------
inline void add(VU0State& v, unsigned dest, unsigned fd, unsigned fs, unsigned ft) noexcept {
    apply_arith(v, dest, fd, [&](int i) { return fpu::add(vf(v, fs, i), vf(v, ft, i)); });
}
inline void addbc(VU0State& v, unsigned dest, unsigned fd, unsigned fs, u32 t) noexcept {
    apply_arith(v, dest, fd, [&](int i) { return fpu::add(vf(v, fs, i), t); });
}
inline void sub(VU0State& v, unsigned dest, unsigned fd, unsigned fs, unsigned ft) noexcept {
    apply_arith(v, dest, fd, [&](int i) { return fpu::sub(vf(v, fs, i), vf(v, ft, i)); });
}
inline void subbc(VU0State& v, unsigned dest, unsigned fd, unsigned fs, u32 t) noexcept {
    apply_arith(v, dest, fd, [&](int i) { return fpu::sub(vf(v, fs, i), t); });
}
inline void mul(VU0State& v, unsigned dest, unsigned fd, unsigned fs, unsigned ft) noexcept {
    apply_arith(v, dest, fd, [&](int i) { return fpu::mul(vf(v, fs, i), vf(v, ft, i)); });
}
inline void mulbc(VU0State& v, unsigned dest, unsigned fd, unsigned fs, u32 t) noexcept {
    apply_arith(v, dest, fd, [&](int i) { return fpu::mul(vf(v, fs, i), t); });
}
inline void madd(VU0State& v, unsigned dest, unsigned fd, unsigned fs, unsigned ft) noexcept {
    apply_arith(v, dest, fd, [&](int i) { return fpu::add(acc(v, i), fpu::mul(vf(v, fs, i), vf(v, ft, i))); });
}
inline void maddbc(VU0State& v, unsigned dest, unsigned fd, unsigned fs, u32 t) noexcept {
    apply_arith(v, dest, fd, [&](int i) { return fpu::add(acc(v, i), fpu::mul(vf(v, fs, i), t)); });
}
inline void msub(VU0State& v, unsigned dest, unsigned fd, unsigned fs, unsigned ft) noexcept {
    apply_arith(v, dest, fd, [&](int i) { return fpu::sub(acc(v, i), fpu::mul(vf(v, fs, i), vf(v, ft, i))); });
}
inline void msubbc(VU0State& v, unsigned dest, unsigned fd, unsigned fs, u32 t) noexcept {
    apply_arith(v, dest, fd, [&](int i) { return fpu::sub(acc(v, i), fpu::mul(vf(v, fs, i), t)); });
}
inline void max(VU0State& v, unsigned dest, unsigned fd, unsigned fs, unsigned ft) noexcept {
    apply(v, dest, fd, [&](int i) { return fpu::max(vf(v, fs, i), vf(v, ft, i)); });
}
inline void maxbc(VU0State& v, unsigned dest, unsigned fd, unsigned fs, u32 t) noexcept {
    apply(v, dest, fd, [&](int i) { return fpu::max(vf(v, fs, i), t); });
}
inline void mini(VU0State& v, unsigned dest, unsigned fd, unsigned fs, unsigned ft) noexcept {
    apply(v, dest, fd, [&](int i) { return fpu::min(vf(v, fs, i), vf(v, ft, i)); });
}
inline void minibc(VU0State& v, unsigned dest, unsigned fd, unsigned fs, u32 t) noexcept {
    apply(v, dest, fd, [&](int i) { return fpu::min(vf(v, fs, i), t); });
}

// ACC-writing forms (VADDA, VSUBA, VMULA, VMADDA, VMSUBA and their broadcast variants).
inline void adda(VU0State& v, unsigned dest, unsigned fs, unsigned ft) noexcept {
    apply_acc_arith(v, dest, [&](int i) { return fpu::add(vf(v, fs, i), vf(v, ft, i)); });
}
inline void addabc(VU0State& v, unsigned dest, unsigned fs, u32 t) noexcept {
    apply_acc_arith(v, dest, [&](int i) { return fpu::add(vf(v, fs, i), t); });
}
inline void suba(VU0State& v, unsigned dest, unsigned fs, unsigned ft) noexcept {
    apply_acc_arith(v, dest, [&](int i) { return fpu::sub(vf(v, fs, i), vf(v, ft, i)); });
}
inline void subabc(VU0State& v, unsigned dest, unsigned fs, u32 t) noexcept {
    apply_acc_arith(v, dest, [&](int i) { return fpu::sub(vf(v, fs, i), t); });
}
inline void mula(VU0State& v, unsigned dest, unsigned fs, unsigned ft) noexcept {
    apply_acc_arith(v, dest, [&](int i) { return fpu::mul(vf(v, fs, i), vf(v, ft, i)); });
}
inline void mulabc(VU0State& v, unsigned dest, unsigned fs, u32 t) noexcept {
    apply_acc_arith(v, dest, [&](int i) { return fpu::mul(vf(v, fs, i), t); });
}
inline void madda(VU0State& v, unsigned dest, unsigned fs, unsigned ft) noexcept {
    apply_acc_arith(v, dest, [&](int i) { return fpu::add(acc(v, i), fpu::mul(vf(v, fs, i), vf(v, ft, i))); });
}
inline void maddabc(VU0State& v, unsigned dest, unsigned fs, u32 t) noexcept {
    apply_acc_arith(v, dest, [&](int i) { return fpu::add(acc(v, i), fpu::mul(vf(v, fs, i), t)); });
}
inline void msuba(VU0State& v, unsigned dest, unsigned fs, unsigned ft) noexcept {
    apply_acc_arith(v, dest, [&](int i) { return fpu::sub(acc(v, i), fpu::mul(vf(v, fs, i), vf(v, ft, i))); });
}
inline void msubabc(VU0State& v, unsigned dest, unsigned fs, u32 t) noexcept {
    apply_acc_arith(v, dest, [&](int i) { return fpu::sub(acc(v, i), fpu::mul(vf(v, fs, i), t)); });
}

// Named operand selectors matching the assembler forms: `vaddx vf1, vf2, vf3x` -> add_bc(..., kBcX);
// `vaddq` -> add_q; `vaddi` -> add_i. The broadcast value is read before any lane is written.
#define P3FES_VU0_BC_FORMS(base)                                                                              \
    inline void base##_bc(VU0State& v, unsigned dest, unsigned fd, unsigned fs, unsigned ft, unsigned bc) noexcept { \
        base##bc(v, dest, fd, fs, vf(v, ft, static_cast<int>(bc & 3u)));                                     \
    }                                                                                                        \
    inline void base##_q(VU0State& v, unsigned dest, unsigned fd, unsigned fs) noexcept { base##bc(v, dest, fd, fs, q(v)); } \
    inline void base##_i(VU0State& v, unsigned dest, unsigned fd, unsigned fs) noexcept { base##bc(v, dest, fd, fs, i_reg(v)); }
P3FES_VU0_BC_FORMS(add)
P3FES_VU0_BC_FORMS(sub)
P3FES_VU0_BC_FORMS(mul)
P3FES_VU0_BC_FORMS(madd)
P3FES_VU0_BC_FORMS(msub)
P3FES_VU0_BC_FORMS(max)
P3FES_VU0_BC_FORMS(mini)
#undef P3FES_VU0_BC_FORMS

#define P3FES_VU0_ACC_BC_FORMS(base)                                                                          \
    inline void base##_bc(VU0State& v, unsigned dest, unsigned fs, unsigned ft, unsigned bc) noexcept {       \
        base##bc(v, dest, fs, vf(v, ft, static_cast<int>(bc & 3u)));                                         \
    }                                                                                                        \
    inline void base##_q(VU0State& v, unsigned dest, unsigned fs) noexcept { base##bc(v, dest, fs, q(v)); }  \
    inline void base##_i(VU0State& v, unsigned dest, unsigned fs) noexcept { base##bc(v, dest, fs, i_reg(v)); }
P3FES_VU0_ACC_BC_FORMS(adda)
P3FES_VU0_ACC_BC_FORMS(suba)
P3FES_VU0_ACC_BC_FORMS(mula)
P3FES_VU0_ACC_BC_FORMS(madda)
P3FES_VU0_ACC_BC_FORMS(msuba)
#undef P3FES_VU0_ACC_BC_FORMS

// VOPMULA ACC.xyz = fs.yzx * ft.zxy; VOPMSUB fd.xyz = ACC - fs.yzx * ft.zxy (outer product halves). The dest
// field is fixed to xyz by the encoding; w is untouched. (manual)
inline void opmula(VU0State& v, unsigned fs, unsigned ft) noexcept {
    const u32 s[3] = {vf(v, fs, 0), vf(v, fs, 1), vf(v, fs, 2)};
    const u32 t[3] = {vf(v, ft, 0), vf(v, ft, 1), vf(v, ft, 2)};
    const u32 r[4] = {fpu::mul(s[1], t[2]), fpu::mul(s[2], t[0]), fpu::mul(s[0], t[1]), acc(v, 3)};
    update_mac_flags(v, r, kDestXYZ);
    for (int i = 0; i < 3; ++i) set_acc(v, i, r[i]);
}
inline void opmsub(VU0State& v, unsigned fd, unsigned fs, unsigned ft) noexcept {
    const u32 s[3] = {vf(v, fs, 0), vf(v, fs, 1), vf(v, fs, 2)};
    const u32 t[3] = {vf(v, ft, 0), vf(v, ft, 1), vf(v, ft, 2)};
    const u32 r[4] = {fpu::sub(acc(v, 0), fpu::mul(s[1], t[2])), fpu::sub(acc(v, 1), fpu::mul(s[2], t[0])),
                      fpu::sub(acc(v, 2), fpu::mul(s[0], t[1])), vf(v, fd, 3)};
    update_mac_flags(v, r, kDestXYZ);
    if (fd) {
        for (int i = 0; i < 3; ++i) set_vf(v, fd, i, r[i]);
    }
}

// Unary moves: VABS ft = |fs|, VMOVE ft = fs, VMR32 ft = fs rotated right one component (x<-y, y<-z, z<-w,
// w<-x). The destination is the ft field for these. (manual)
inline void abs(VU0State& v, unsigned dest, unsigned ft, unsigned fs) noexcept {
    apply(v, dest, ft, [&](int i) { return vf(v, fs, i) & fpu::kAbs; });
}
inline void move(VU0State& v, unsigned dest, unsigned ft, unsigned fs) noexcept {
    apply(v, dest, ft, [&](int i) { return vf(v, fs, i); });
}
inline void mr32(VU0State& v, unsigned dest, unsigned ft, unsigned fs) noexcept {
    const u32 s[4] = {vf(v, fs, 0), vf(v, fs, 1), vf(v, fs, 2), vf(v, fs, 3)};
    apply(v, dest, ft, [&](int i) { return s[(i + 1) & 3]; });
}

// VFTOI0/4/12/15 and VITOF0/4/12/15: `fraction` is 0, 4, 12 or 15. (manual; saturation as fpu::to_fixed)
inline void ftoi(VU0State& v, unsigned dest, unsigned ft, unsigned fs, int fraction) noexcept {
    apply(v, dest, ft, [&](int i) { return fpu::to_fixed(vf(v, fs, i), fraction); });
}
inline void itof(VU0State& v, unsigned dest, unsigned ft, unsigned fs, int fraction) noexcept {
    apply(v, dest, ft, [&](int i) { return fpu::from_fixed(static_cast<s32>(vf(v, fs, i)), fraction); });
}

// VCLIPw.xyz fs, ft: shift six new judgement bits into the 24-bit CLIP register. Unused by the binary. (manual)
inline void clip(VU0State& v, unsigned fs, unsigned ft) noexcept {
    const s32 w = fpu::key(vf(v, ft, 3) & fpu::kAbs);
    u32 flags = 0;
    for (int i = 0; i < 3; ++i) {
        const s32 x = fpu::key(vf(v, fs, i));
        if (x > w) flags |= 1u << (i * 2);
        if (x < -w) flags |= 2u << (i * 2);
    }
    v.clip = ((v.clip << 6) | flags) & 0xFFFFFFu;
}

// Q-pipe ops. `fsf`/`ftf` are the 2-bit component selectors of the instruction word. I (bit 4) and D (bit 5) are
// cleared, then x/0 sets D + DS (bit 11) and 0/0, sqrt/rsqrt of a negative set I + IS (bit 10); the other sticky
// bits stay. (manual; PCSX2 2.8.2 observed: vu0_3280 -> 0x821, vu0_3318 -> 0x411, vu0_3279, vu0_3294)
inline constexpr u32 kStatusInvalid = 0x10u, kStatusDivideByZero = 0x20u;
inline constexpr u32 kStatusInvalidSticky = 0x400u, kStatusDivideByZeroSticky = 0x800u;
namespace detail {
inline void set_q_result(VU0State& v, fpu::Result r) noexcept {
    set_q(v, r.value);
    u32 status = v.status & ~(kStatusInvalid | kStatusDivideByZero);
    if (r.zero_divide) status |= kStatusDivideByZero | kStatusDivideByZeroSticky;
    if (r.invalid_op) status |= kStatusInvalid | kStatusInvalidSticky;
    v.status = status;
}
} // namespace detail
inline void div(VU0State& v, unsigned fs, unsigned fsf, unsigned ft, unsigned ftf) noexcept {
    detail::set_q_result(v, fpu::div(vf(v, fs, static_cast<int>(fsf & 3u)), vf(v, ft, static_cast<int>(ftf & 3u))));
}
inline void sqrt(VU0State& v, unsigned ft, unsigned ftf) noexcept {
    detail::set_q_result(v, fpu::sqrt_flags(vf(v, ft, static_cast<int>(ftf & 3u))));
}
inline void rsqrt(VU0State& v, unsigned fs, unsigned fsf, unsigned ft, unsigned ftf) noexcept {
    detail::set_q_result(v, fpu::rsqrt(vf(v, fs, static_cast<int>(fsf & 3u)), vf(v, ft, static_cast<int>(ftf & 3u))));
}
// VWAITQ / VNOP: nothing to wait for without a Q pipeline. (upstream)
inline void waitq(VU0State&) noexcept {}
inline void nop(VU0State&) noexcept {}

// Integer register file: vi00 is constant zero. (manual)
inline void set_vi(VU0State& v, unsigned index, u32 value) noexcept {
    if (index) v.vi[index] = static_cast<u16>(value);
}
inline void iadd(VU0State& v, unsigned id, unsigned is, unsigned it) noexcept { set_vi(v, id, static_cast<u32>(v.vi[is]) + v.vi[it]); }
inline void isub(VU0State& v, unsigned id, unsigned is, unsigned it) noexcept { set_vi(v, id, static_cast<u32>(v.vi[is]) - v.vi[it]); }
inline void iand(VU0State& v, unsigned id, unsigned is, unsigned it) noexcept { set_vi(v, id, static_cast<u32>(v.vi[is] & v.vi[it])); }
inline void ior(VU0State& v, unsigned id, unsigned is, unsigned it) noexcept { set_vi(v, id, static_cast<u32>(v.vi[is] | v.vi[it])); }
// VIADDI it, is, imm5 (sign-extended 5-bit immediate). (manual)
inline void iaddi(VU0State& v, unsigned it, unsigned is, s32 imm5) noexcept {
    set_vi(v, it, static_cast<u32>(static_cast<s32>(v.vi[is]) + imm5));
}
// VMFIR: ft lanes = sign-extended vi[is]. Unused by the binary. (manual)
inline void mfir(VU0State& v, unsigned dest, unsigned ft, unsigned is) noexcept {
    const u32 value = static_cast<u32>(static_cast<s32>(static_cast<s16>(v.vi[is])));
    apply(v, dest, ft, [&](int) { return value; });
}

// ---------------------------------------------------------------------------------------------------------
// MAC / STATUS flag computation (upstream's vu_ops.hpp `flags`), applied by every macro-mode arithmetic op above
// (PCSX2 2.8.2 observed: vu0_3417, vu0_3422, vu0_2838 where a -0 result sets S and Z).
//   MAC bits: 3..0 Z (x,y,z,w), 7..4 S, 11..8 U (never set by this model), 15..12 O (|x| == 0x7FFFFFFF).
//   STATUS: bits 0..3 = Z S U O of this result, bits 6..9 = sticky copies; bits 4..5 (I, D) are preserved.
// Lanes outside `dest` contribute nothing and their MAC bits read 0.
// ---------------------------------------------------------------------------------------------------------
inline void update_mac_flags(VU0State& v, const u32 result[4], unsigned dest) noexcept {
    u32 mac = 0;
    for (int i = 0; i < 4; ++i) {
        if (!lane(dest, i)) continue;
        const u32 bit = 3u - static_cast<u32>(i);
        const u32 x = result[i];
        if (!(x & 0x7F800000u)) mac |= 1u << bit;
        if (x & 0x80000000u) mac |= 1u << (bit + 4);
        if ((x & 0x7FFFFFFFu) == 0x7FFFFFFFu) mac |= 1u << (bit + 12);
    }
    v.mac = mac;
    u32 status = v.status & 0xFF0u;
    if (mac & 0x000Fu) status |= 0x1u;
    if (mac & 0x00F0u) status |= 0x2u;
    if (mac & 0x0F00u) status |= 0x4u;
    if (mac & 0xF000u) status |= 0x8u;
    status |= (status & 0xFu) << 6;
    v.status = (status & ~0x30u) | (v.status & 0x30u);
}

// ---------------------------------------------------------------------------------------------------------
// COP2 transfers.
// ---------------------------------------------------------------------------------------------------------
// QMFC2[.I] rt, fs: whole 128-bit vf into a GPR. The interlock flag is accepted and ignored (see header note).
inline u128 qmfc2(const VU0State& v, unsigned fs, [[maybe_unused]] bool interlock = false) noexcept {
    u128 r;
    for (int i = 0; i < 4; ++i) r.u32[i] = vf(v, fs, i);
    return r;
}
// QMTC2[.I] rt, fs: GPR into vf; vf00 is never written. (manual)
inline void qmtc2(VU0State& v, unsigned fs, const u128& rt, [[maybe_unused]] bool interlock = false) noexcept {
    if (fs) {
        for (int i = 0; i < 4; ++i) set_vf(v, fs, i, rt.u32[i]);
    }
}

// Control register numbers used by CFC2/CTC2 (the `fs` field). (manual)
inline constexpr unsigned kCtrlStatus = 16u, kCtrlMac = 17u, kCtrlClip = 18u, kCtrlR = 20u, kCtrlI = 21u, kCtrlQ = 22u,
                          kCtrlTpc = 26u, kCtrlCmsar0 = 27u, kCtrlFbrst = 28u, kCtrlVpuStat = 29u, kCtrlCmsar1 = 31u;

// CFC2 rt, reg: vi00..vi15 read as 16-bit values, then the control registers. Write-only / unmodelled
// registers read 0. The caller sign-extends the 32-bit result into the GPR (MIPS word move). (manual for the
// layout; masks and zero reads: upstream)
inline u32 cfc2(const VU0State& v, unsigned reg) noexcept {
    if (reg < 16) return v.vi[reg];
    switch (reg) {
    case kCtrlStatus: return v.status;
    case kCtrlMac: return v.mac;
    case kCtrlClip: return v.clip;
    case kCtrlR: return v.r;
    case kCtrlI: return i_reg(v);
    case kCtrlQ: return q(v);
    case kCtrlTpc: return v.tpc;
    case kCtrlCmsar0: return v.cmsar0;
    default: return 0; // FBRST, VPU-STAT, CMSAR1: write-only / not modelled (upstream returns 0 too)
    }
}

// CTC2 rt, reg: writes to vi (vi00 ignored) and the writable control registers. STATUS keeps its live bits
// 0..5 and accepts only the sticky bits 6..11 (PCSX2 recompiler observed: vu0_3400; its interpreter writes all
// bits); MAC is read-only; CLIP is 24 bits here (PCSX2 stores 32: vu0_3405). Unbacked registers drop the write.
inline void ctc2(VU0State& v, unsigned reg, u32 value) noexcept {
    if (reg < 16) {
        set_vi(v, reg, value);
        return;
    }
    switch (reg) {
    case kCtrlStatus: v.status = (v.status & 0x3Fu) | (value & 0xFC0u); break;
    case kCtrlMac: break;                               // read-only (PCSX2 2.8.2 observed: vu0_3403)
    case kCtrlClip: v.clip = value & 0xFFFFFFu; break;
    case kCtrlR: v.r = value & 0x7FFFFFu; break;        // 23-bit random seed (upstream mask)
    case kCtrlI: set_i(v, value); break;
    case kCtrlQ: set_q(v, value); break;
    case kCtrlCmsar0: v.cmsar0 = value & 0xFFFFu; break; // upstream mask
    default: break; // TPC (read-only), FBRST, VPU-STAT, CMSAR1 (VU1 kick, not modelled): dropped as upstream
    }
}

// LQC2 ft, off(base) / SQC2: quadword transfers between memory and vf; the EE ignores the low four address
// bits like LQ/SQ. LQC2 into vf00 performs the read and discards it (upstream). (manual)
inline constexpr u32 kQuadwordMask = ~15u;
inline void lqc2(VU0State& v, const EEMemory& mem, unsigned ft, u32 vaddr) noexcept {
    const u128 data = mem.read<u128>(vaddr & kQuadwordMask);
    qmtc2(v, ft, data);
}
inline void sqc2(const VU0State& v, EEMemory& mem, unsigned ft, u32 vaddr) noexcept {
    mem.write<u128>(vaddr & kQuadwordMask, qmfc2(v, ft));
}

} // namespace p3fes::ee::vu0
