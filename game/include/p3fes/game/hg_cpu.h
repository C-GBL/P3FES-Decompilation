// The register view of the bodies p3fes_handgen writes (recomp/README.md "p3fes_handgen", docs/PHASE5_AGENT_BRIEF.md
// "Using p3fes_handgen"). Shared by every slice that starts from a generated body; header only.
//
// Faithful by construction: every operation here is one call into the runtime's own instruction semantics -- the
// rt:: op the recompiled body itself calls (recomp/include/p3fes_recomp_rt.h), or for the integer ALU the very
// ee::core rule that rt:: op applies (p3fes_recomp_rt_inline.h: rt::addiu(ctx, rt, rs, imm) is
// set_gpr64(rt, core::add32i(gpr64(rs), imm)), which `t = addiu(s, imm)` below is too). So a body written on this view
// keeps every guest register, HI/LO, FPR, ACC, FCR31 and VU0 register where the original keeps it, at every check
// point, call and return (the wave-7 lesson: the kernel saves the WHOLE register file at a preemption); loads and
// stores take the runtime's fast and slow paths (alignment and mapping faults, the hardware bus, the BIOS window;
// the wave-10 lesson); virtual time is the generated body's (ADR-0013).
//
// Registers are proxies naming one GPR (FPR, VU0 vf) of the context: reads and writes go through volatile lvalues, and
// so does virtual time (charge): MSVC /O2 was seen keeping ctx.cycles or a register in a host register across a call to
// a small helper that charges (the wave-10 render_core3 lesson); a volatile access is a compiler barrier under
// /volatile:ms and keeps every access real under clang-cl. A body declares the proxies it uses:
//
//     Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
//     enter(ctx, 5);              // entry check point + the first block's cycles
//     sp = addiu(sp, -0x10);      // addiu sp, sp, -16
//     sd(ra, sp, 0x8);            // sd ra, 8(sp)
//     jal(ctx, 0x56985Cu, gen::fn_strlen_00524388);   // $ra = 0x569864, then the callee's entry point
//
// Writes keep bits 64..127 (the EE rule for 64-bit results; core::set_gpr64) and drop writes to $zero.
#pragma once

#include "p3fes/ee/core.h"
#include "p3fes_recomp_rt.h"

#include <cstdint>

namespace p3fes::game::hg {

namespace core = ::p3fes::ee::core;
using Fn = rt::Fn;

// --- registers ---------------------------------------------------------------------------------------------------

struct Gpr {
    EEContext& c;
    unsigned r;
    operator u64() const noexcept { return static_cast<const volatile u64&>(c.gpr[r].u64[0]); }
    u32 u() const noexcept { return static_cast<u32>(static_cast<u64>(*this)); }  // the low word (an address)
    s32 s() const noexcept { return static_cast<s32>(u()); }
    Gpr& operator=(u64 v) noexcept {
        if (r != 0) static_cast<volatile u64&>(c.gpr[r].u64[0]) = v;
        return *this;
    }
    Gpr(EEContext& ctx, unsigned reg) noexcept : c(ctx), r(reg) {}
    Gpr(const Gpr&) = default;
    Gpr& operator=(const Gpr& o) noexcept { return *this = static_cast<u64>(o); }
};

struct Fpr {  // COP1 register (EE single); the value is rt's business, the proxy only names it
    EEContext& c;
    unsigned r;
};

struct Vf {  // VU0 vf register
    EEContext& c;
    unsigned r;
};

// --- integer results (R5900 rules, ee::core; 32-bit operations sign-extend into the 64-bit register) -------------

constexpr u64 si(s32 v) noexcept { return static_cast<u64>(static_cast<s64>(v)); }  // `addiu rt, $zero, imm` (imm < 0)
constexpr u32 w(u64 v) noexcept { return static_cast<u32>(v); }
constexpr s64 i64(u64 v) noexcept { return static_cast<s64>(v); }                   // blez / bgtz / bltz / bgez tests
constexpr u64 addu(u64 s, u64 t) noexcept { return core::add32(s, t); }             // also add (the trap is not modelled)
constexpr u64 subu(u64 s, u64 t) noexcept { return core::sub32(s, t); }             // also sub
constexpr u64 addiu(u64 s, s32 i) noexcept { return core::add32i(s, i); }           // also addi
constexpr u64 daddiu(u64 s, s32 i) noexcept { return core::add64i(s, i); }
constexpr u64 nor(u64 s, u64 t) noexcept { return core::nor64(s, t); }
constexpr u64 lui(u32 i) noexcept { return core::lui(i); }
constexpr u64 slt(u64 s, u64 t) noexcept { return core::slt(s, t); }
constexpr u64 sltu(u64 s, u64 t) noexcept { return core::sltu(s, t); }
constexpr u64 slti(u64 s, s32 i) noexcept { return core::slti(s, i); }
constexpr u64 sltiu(u64 s, s32 i) noexcept { return core::sltiu(s, i); }
constexpr u64 sll(u64 t, unsigned n) noexcept { return core::sll(t, n); }
constexpr u64 srl(u64 t, unsigned n) noexcept { return core::srl(t, n); }
constexpr u64 sra(u64 t, unsigned n) noexcept { return core::sra(t, n); }
constexpr u64 dsll(u64 t, unsigned n) noexcept { return core::dsll(t, n); }
constexpr u64 dsrl(u64 t, unsigned n) noexcept { return core::dsrl(t, n); }
constexpr u64 dsra(u64 t, unsigned n) noexcept { return core::dsra(t, n); }
constexpr u64 dsll32(u64 t, unsigned n) noexcept { return core::dsll32(t, n); }
constexpr u64 dsrl32(u64 t, unsigned n) noexcept { return core::dsrl32(t, n); }
constexpr u64 dsra32(u64 t, unsigned n) noexcept { return core::dsra32(t, n); }
constexpr u64 sllv(u64 t, u64 s) noexcept { return core::sllv(t, s); }
constexpr u64 srlv(u64 t, u64 s) noexcept { return core::srlv(t, s); }
constexpr u64 srav(u64 t, u64 s) noexcept { return core::srav(t, s); }
constexpr u64 dsllv(u64 t, u64 s) noexcept { return core::dsllv(t, s); }
constexpr u64 dsrlv(u64 t, u64 s) noexcept { return core::dsrlv(t, s); }
// daddu / dsubu are `s + t` / `s - t` and and / or / xor are `s & t` / `s | t` / `s ^ t` on the 64-bit values
// (core::add64 / sub64 / and64 / or64 / xor64); andi / ori / xori take the zero-extended immediate (`s & 0xFF`).

// --- virtual time, check points, calls (ADR-0013; the generated body's `ctx.cycles += N` and rt::check_events) ----

inline void charge(EEContext& c, u64 n) noexcept {
    volatile u64& t = c.cycles;
    t = t + n;
}
// Not noexcept: a check point may raise a fatal event that unwinds through the body.
inline void check_events(EEContext& c) { rt::check_events(c); }
inline void enter(EEContext& c, u64 n) {  // the entry check point and the first block
    rt::check_events(c);
    charge(c, n);
}
inline void backedge(EEContext& c) { rt::check_events(c); }  // before a backward jump, after its delay slot

// `jal fn` at pc: $ra = pc + 8, then the callee's entry point (recomp_gen::fn_*: hand-written or recompiled).
inline void jal(EEContext& c, u32 pc, Fn fn) {
    rt::jal(c, pc);
    fn(c);
}
inline void link(EEContext& c, u32 pc) { rt::jal(c, pc); }  // the link alone (a delay slot that must run after it)
inline void call(EEContext& c, Fn fn) { fn(c); }
// `jalr target` at pc ($ra = pc + 8) through the dispatch table; `rd` = the link register when it is not $ra.
inline void jalr(EEContext& c, u32 pc, u32 target) {
    rt::jalr(c, GPR_RA, pc);
    rt::lookup_func(target)(c);
}
inline void jalr_rd(EEContext& c, unsigned rd, u32 pc, u32 target) {
    if (rd != 0) rt::jalr(c, rd, pc);
    rt::lookup_func(target)(c);
}
inline void call_ptr(EEContext& c, u32 target) { rt::lookup_func(target)(c); }
// `jr $rN` without a table, or a jump table's out-of-table entry: the target's entry point (the caller then returns).
inline void tail(EEContext& c, u32 target) { rt::lookup_func(target)(c); }

// --- branch conditions that are not plain compares ------------------------------------------------------------------
inline bool cond(EEContext& c) { return rt::cop1_cond(c); }  // FCR31 C (bc1t; !cond for bc1f)
inline bool cop0_cond(EEContext& c) { return rt::cop0_cond(c); }

// --- loads and stores in the instruction's form: `lw(rt, base, imm)` = `lw rt, imm(base)` -------------------------
#define P3FES_HG_MEM(name) \
    inline void name(Gpr t, Gpr b, s32 i) { rt::name(t.c, t.r, b.r, i); }
P3FES_HG_MEM(lb) P3FES_HG_MEM(lbu) P3FES_HG_MEM(lh) P3FES_HG_MEM(lhu) P3FES_HG_MEM(lw) P3FES_HG_MEM(lwu)
P3FES_HG_MEM(lwl) P3FES_HG_MEM(lwr) P3FES_HG_MEM(ld) P3FES_HG_MEM(ldl) P3FES_HG_MEM(ldr) P3FES_HG_MEM(lq)
P3FES_HG_MEM(sb) P3FES_HG_MEM(sh) P3FES_HG_MEM(sw) P3FES_HG_MEM(swl) P3FES_HG_MEM(swr) P3FES_HG_MEM(sd)
P3FES_HG_MEM(sdl) P3FES_HG_MEM(sdr) P3FES_HG_MEM(sq)
#undef P3FES_HG_MEM
inline void lwc1(Fpr f, Gpr b, s32 i) { rt::lwc1(f.c, f.r, b.r, i); }
inline void swc1(Fpr f, Gpr b, s32 i) { rt::swc1(f.c, f.r, b.r, i); }
inline void lqc2(Vf f, Gpr b, s32 i) { rt::lqc2(f.c, f.r, b.r, i); }
inline void sqc2(Vf f, Gpr b, s32 i) { rt::sqc2(f.c, f.r, b.r, i); }
inline void cache(EEContext& c, unsigned op, Gpr b, s32 i) { rt::cache(c, op, b.r, i); }

// --- HI/LO, MMI, the multiply / divide units (statement forms: they write more than one register) -----------------
#define P3FES_HG_RRR(name) \
    inline void name(Gpr d, Gpr s, Gpr t) { rt::name(d.c, d.r, s.r, t.r); }
P3FES_HG_RRR(mult) P3FES_HG_RRR(multu) P3FES_HG_RRR(madd) P3FES_HG_RRR(maddu) P3FES_HG_RRR(mult1)
P3FES_HG_RRR(multu1) P3FES_HG_RRR(maddu1) P3FES_HG_RRR(phmadh)
P3FES_HG_RRR(paddh) P3FES_HG_RRR(paddub) P3FES_HG_RRR(padduw) P3FES_HG_RRR(paddw) P3FES_HG_RRR(pand)
P3FES_HG_RRR(pcgth) P3FES_HG_RRR(pcpyld) P3FES_HG_RRR(pcpyud) P3FES_HG_RRR(pextlb) P3FES_HG_RRR(pextlh)
P3FES_HG_RRR(pextlw) P3FES_HG_RRR(pextub) P3FES_HG_RRR(pextuw) P3FES_HG_RRR(pmaxh) P3FES_HG_RRR(pminh)
P3FES_HG_RRR(pnor) P3FES_HG_RRR(por) P3FES_HG_RRR(ppacb) P3FES_HG_RRR(ppach) P3FES_HG_RRR(ppacw)
P3FES_HG_RRR(psubb) P3FES_HG_RRR(psubw) P3FES_HG_RRR(pxor) P3FES_HG_RRR(qfsrv)
#undef P3FES_HG_RRR
inline void div(Gpr s, Gpr t) { rt::div(s.c, s.r, t.r); }
inline void divu(Gpr s, Gpr t) { rt::divu(s.c, s.r, t.r); }
inline void div1(Gpr s, Gpr t) { rt::div1(s.c, s.r, t.r); }
inline void mfhi(Gpr d) { rt::mfhi(d.c, d.r); }
inline void mflo(Gpr d) { rt::mflo(d.c, d.r); }
inline void mfhi1(Gpr d) { rt::mfhi1(d.c, d.r); }
inline void mflo1(Gpr d) { rt::mflo1(d.c, d.r); }
inline void mfsa(Gpr d) { rt::mfsa(d.c, d.r); }
inline void mthi(Gpr s) { rt::mthi(s.c, s.r); }
inline void mtlo(Gpr s) { rt::mtlo(s.c, s.r); }
inline void mthi1(Gpr s) { rt::mthi1(s.c, s.r); }
inline void mtlo1(Gpr s) { rt::mtlo1(s.c, s.r); }
inline void mtsa(Gpr s) { rt::mtsa(s.c, s.r); }
inline void mtsab(Gpr s, s32 i) { rt::mtsab(s.c, s.r, i); }
inline void mtsah(Gpr s, s32 i) { rt::mtsah(s.c, s.r, i); }
inline void pmfhl(Gpr d, unsigned fmt) { rt::pmfhl(d.c, d.r, fmt); }
inline void pcpyh(Gpr d, Gpr t) { rt::pcpyh(d.c, d.r, t.r); }
inline void pexew(Gpr d, Gpr t) { rt::pexew(d.c, d.r, t.r); }
inline void prot3w(Gpr d, Gpr t) { rt::prot3w(d.c, d.r, t.r); }
inline void psllh(Gpr d, Gpr t, unsigned sa) { rt::psllh(d.c, d.r, t.r, sa); }
inline void psrah(Gpr d, Gpr t, unsigned sa) { rt::psrah(d.c, d.r, t.r, sa); }
inline void psraw(Gpr d, Gpr t, unsigned sa) { rt::psraw(d.c, d.r, t.r, sa); }
inline void psrlh(Gpr d, Gpr t, unsigned sa) { rt::psrlh(d.c, d.r, t.r, sa); }

// --- COP0 / system -----------------------------------------------------------------------------------------------
inline void mfc0(Gpr t, unsigned reg) { rt::mfc0(t.c, t.r, reg); }
inline void mtc0(Gpr t, unsigned reg) { rt::mtc0(t.c, t.r, reg); }
inline void sync(EEContext& c, unsigned stype) { rt::sync(c, stype); }
inline void ei(EEContext& c) { rt::ei(c); }
inline void di(EEContext& c) { rt::di(c); }
inline void syscall(EEContext& c, u32 pc) { rt::syscall(c, pc); }
inline void brk(EEContext& c, u32 pc, u32 code) { rt::trap(c, pc, rt::Trap::Break, code); }

// --- COP1 (EE singles, ACC, FCR31 flags) ---------------------------------------------------------------------------
#define P3FES_HG_F3(name) \
    inline void name(Fpr d, Fpr s, Fpr t) { rt::name(d.c, d.r, s.r, t.r); }
P3FES_HG_F3(add_s) P3FES_HG_F3(sub_s) P3FES_HG_F3(mul_s) P3FES_HG_F3(div_s) P3FES_HG_F3(madd_s) P3FES_HG_F3(msub_s)
#undef P3FES_HG_F3
#define P3FES_HG_F2(name) \
    inline void name(Fpr a, Fpr b) { rt::name(a.c, a.r, b.r); }
P3FES_HG_F2(adda_s) P3FES_HG_F2(suba_s) P3FES_HG_F2(mula_s) P3FES_HG_F2(madda_s) P3FES_HG_F2(msuba_s)
P3FES_HG_F2(c_eq_s) P3FES_HG_F2(c_le_s) P3FES_HG_F2(c_lt_s)
P3FES_HG_F2(abs_s) P3FES_HG_F2(mov_s) P3FES_HG_F2(neg_s) P3FES_HG_F2(cvt_s_w) P3FES_HG_F2(cvt_w_s)
P3FES_HG_F2(sqrt_s)  // (fd, ft): the EE reads the ft field
#undef P3FES_HG_F2
inline void mfc1(Gpr t, Fpr f) { rt::mfc1(t.c, t.r, f.r); }
inline void mtc1(Gpr t, Fpr f) { rt::mtc1(t.c, t.r, f.r); }
inline void ctc1(Gpr t, unsigned fs) { rt::ctc1(t.c, t.r, fs); }

// --- COP2 transfers and VU0 macro mode (dest = the xyzw mask: x 8, y 4, z 2, w 1; bc: 0 x, 1 y, 2 z, 3 w) -------
inline void qmfc2(Gpr t, Vf f, bool interlock) { rt::qmfc2(t.c, t.r, f.r, interlock); }
inline void qmtc2(Gpr t, Vf f, bool interlock) { rt::qmtc2(t.c, t.r, f.r, interlock); }
inline void cfc2(Gpr t, unsigned vi, bool interlock) { rt::cfc2(t.c, t.r, vi, interlock); }
inline void ctc2(Gpr t, unsigned vi, bool interlock) { rt::ctc2(t.c, t.r, vi, interlock); }
#define P3FES_HG_V3(name)                                                                              \
    inline void name(unsigned dest, Vf d, Vf s, Vf t) { rt::name(d.c, dest, d.r, s.r, t.r); }          \
    inline void name##_bc(unsigned dest, Vf d, Vf s, Vf t, unsigned bc) { rt::name##_bc(d.c, dest, d.r, s.r, t.r, bc); }
P3FES_HG_V3(vadd) P3FES_HG_V3(vsub) P3FES_HG_V3(vmul) P3FES_HG_V3(vmadd) P3FES_HG_V3(vmsub)
#undef P3FES_HG_V3
inline void vmax(unsigned dest, Vf d, Vf s, Vf t) { rt::vmax(d.c, dest, d.r, s.r, t.r); }
inline void vmini(unsigned dest, Vf d, Vf s, Vf t) { rt::vmini(d.c, dest, d.r, s.r, t.r); }
inline void vopmsub(unsigned dest, Vf d, Vf s, Vf t) { rt::vopmsub(d.c, dest, d.r, s.r, t.r); }
#define P3FES_HG_V2(name)                                                                              \
    inline void name(unsigned dest, Vf s, Vf t) { rt::name(s.c, dest, s.r, t.r); }                     \
    inline void name##_bc(unsigned dest, Vf s, Vf t, unsigned bc) { rt::name##_bc(s.c, dest, s.r, t.r, bc); }
P3FES_HG_V2(vadda) P3FES_HG_V2(vmadda) P3FES_HG_V2(vmsuba) P3FES_HG_V2(vmula)
#undef P3FES_HG_V2
inline void vopmula(unsigned dest, Vf s, Vf t) { rt::vopmula(s.c, dest, s.r, t.r); }
inline void vaddi(unsigned dest, Vf d, Vf s) { rt::vaddi(d.c, dest, d.r, s.r); }
inline void vmuli(unsigned dest, Vf d, Vf s) { rt::vmuli(d.c, dest, d.r, s.r); }
inline void vmulq(unsigned dest, Vf d, Vf s) { rt::vmulq(d.c, dest, d.r, s.r); }
inline void vabs(unsigned dest, Vf t, Vf s) { rt::vabs(t.c, dest, t.r, s.r); }
inline void vmove(unsigned dest, Vf t, Vf s) { rt::vmove(t.c, dest, t.r, s.r); }
inline void vftoi0(unsigned dest, Vf t, Vf s) { rt::vftoi0(t.c, dest, t.r, s.r); }
inline void vitof0(unsigned dest, Vf t, Vf s) { rt::vitof0(t.c, dest, t.r, s.r); }
inline void vsqrt(Vf t, unsigned ftf) { rt::vsqrt(t.c, t.r, ftf); }
inline void vrsqrt(Vf s, unsigned fsf, Vf t, unsigned ftf) { rt::vrsqrt(s.c, s.r, fsf, t.r, ftf); }
inline void vnop(EEContext& c) { rt::vnop(c); }
inline void vwaitq(EEContext& c) { rt::vwaitq(c); }

}  // namespace p3fes::game::hg
