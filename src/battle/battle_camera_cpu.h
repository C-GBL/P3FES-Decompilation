// The guest machine as the battle_camera bodies see it (private to game/src/battle/battle_camera*.cpp).
//
// Register-faithful by construction (docs/PHASE5_AGENT_BRIEF.md, the wave-6 / wave-7 lessons): each body runs on a Cpu
// view of the guest context -- one variable per GPR (64-bit writes keep bits 64..127 as the EE does; LQ writes all 128),
// the loads and stores and every FPU operation through the runtime's own instructions (so a wild pointer faults, a
// hardware window is served and an FPU result rounds / clamps / sets FCR31 exactly as in the recompiled body), the
// prologue spills and epilogue reloads on the guest stack, and every callee through its generated entry point with
// $ra = the original link (the value the generated body hands rt::jal). A scratch register the original writes holds
// the original's value at every call, check point and return; one it leaves alone keeps what the caller or the last
// callee left there.
//
// Virtual time (ADR-0013): enter(N) is the entry check point plus the first block, charge(N) one `ctx.cycles += N`
// block of the recompiled body on the executed path (charged where the block starts, before its calls), backedge()
// the check the recompiled body makes before a backward jump.
#pragma once

#include "p3fes/ee/core.h"
#include "p3fes/game/battle_camera.h"
#include "p3fes/game/guest.h"
#include "p3fes_recomp_rt.h"

#include "p3fes/game/battle_camera_1.h"
#include "p3fes/game/battle_camera_2.h"
#include "p3fes/game/battle_camera_3.h"
#include "p3fes/game/battle_camera_4.h"
#include "p3fes/game/battle_camera_5.h"

// The generated entry points of every function of the slice (the shims of battle_camera*.cpp): the bodies call each
// other through them, as the original's `jal`s did.
namespace p3fes::recomp_gen {
#define P3FES_BCAM_ENTRY(name, addr) void fn_##name##_##addr(p3fes::EEContext&);
P3FES_BCAM_BODIES(P3FES_BCAM_ENTRY)
P3FES_BCAM_BODIES_1(P3FES_BCAM_ENTRY)
P3FES_BCAM_BODIES_2(P3FES_BCAM_ENTRY)
P3FES_BCAM_BODIES_3(P3FES_BCAM_ENTRY)
P3FES_BCAM_BODIES_4(P3FES_BCAM_ENTRY)
P3FES_BCAM_BODIES_5(P3FES_BCAM_ENTRY)
#undef P3FES_BCAM_ENTRY
}  // namespace p3fes::recomp_gen

namespace p3fes::game::bcam {

namespace core = ee::core;

// --- R5900 integer results (32-bit operations sign-extend into the 64-bit register) ---------------------------------
constexpr u64 li(s32 i) { return core::add32i(0, i); }  // `addiu rX, zero, imm`
constexpr u64 dli(s32 i) { return core::add64i(0, i); } // `daddiu rX, zero, imm`
constexpr u64 addiu(u64 a, s32 i) { return core::add32i(a, i); }
constexpr u64 daddiu(u64 a, s32 i) { return core::add64i(a, i); }
constexpr u64 addu(u64 a, u64 b) { return core::add32(a, b); }
constexpr u64 subu(u64 a, u64 b) { return core::sub32(a, b); }
constexpr u64 daddu(u64 a, u64 b) { return core::add64(a, b); }
constexpr u64 lui(u32 i) { return core::lui(i); }
constexpr u64 sll(u64 a, unsigned n) { return core::sll(a, n); }
constexpr u64 srl(u64 a, unsigned n) { return core::srl(a, n); }
constexpr u64 sra(u64 a, unsigned n) { return core::sra(a, n); }
constexpr u64 sllv(u64 a, u64 n) { return core::sllv(a, n); }
constexpr u64 dsll(u64 a, unsigned n) { return core::dsll(a, n); }
constexpr u64 dsll32(u64 a, unsigned n) { return core::dsll32(a, n); }
constexpr u64 dsra32(u64 a, unsigned n) { return core::dsra32(a, n); }
constexpr u64 dsrl32(u64 a, unsigned n) { return core::dsrl32(a, n); }
constexpr u64 slt(u64 a, u64 b) { return core::slt(a, b); }
constexpr u64 sltu(u64 a, u64 b) { return core::sltu(a, b); }
constexpr u64 slti(u64 a, s32 i) { return core::slti(a, i); }
constexpr u64 sltiu(u64 a, s32 i) { return core::sltiu(a, i); }
constexpr bool ltz(u64 a) { return static_cast<s64>(a) < 0; }
constexpr bool lez(u64 a) { return static_cast<s64>(a) <= 0; }
constexpr bool gtz(u64 a) { return static_cast<s64>(a) > 0; }
constexpr bool gez(u64 a) { return static_cast<s64>(a) >= 0; }

// `lw rX, -18692(gp)`: the gBtl pointer slot, as the bodies read it (through the guest $gp)
inline constexpr s32 kGpBtl = -18692;

// One GPR of the guest context.
struct Gpr {
    EEContext& c;
    const unsigned r;
    operator u64() const noexcept { return static_cast<const volatile u64&>(c.gpr[r].u64[0]); }
    Gpr& operator=(u64 v) noexcept {
        core::set_gpr64(c, r, v);
        return *this;
    }
    Gpr& operator=(const Gpr& o) noexcept { return *this = static_cast<u64>(o); }
};

enum : unsigned { F0, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, F16, F17, F18, F19, F20,
                  F21, F22, F23, F24, F25, F26, F27, F28, F29, F30, F31 };

namespace rg = ::p3fes::recomp_gen;

class Cpu {
public:
    explicit Cpu(EEContext& ctx) noexcept : c(ctx) {}

    EEContext& c;
    Gpr zero{c, 0}, at{c, 1}, v0{c, 2}, v1{c, 3}, a0{c, 4}, a1{c, 5}, a2{c, 6}, a3{c, 7};
    Gpr t0{c, 8}, t1{c, 9}, t2{c, 10}, t3{c, 11}, t4{c, 12}, t5{c, 13}, t6{c, 14}, t7{c, 15};
    Gpr s0{c, 16}, s1{c, 17}, s2{c, 18}, s3{c, 19}, s4{c, 20}, s5{c, 21}, s6{c, 22}, s7{c, 23};
    Gpr t8{c, 24}, t9{c, 25}, gp{c, 28}, sp{c, 29}, s8{c, 30}, ra{c, 31};

    // virtual time (not guest::enter / guest::backedge: those are noexcept, and a test hook may stop a run at a check
    // point)
    void enter(u64 n) {
        rt::check_events(c);
        bump(n);
    }
    void charge(u64 n) noexcept { bump(n); }
    // through a volatile lvalue: MSVC /O2 was seen keeping ctx.cycles in a host register across a small non-inlined
    // helper that charges (render_core3, docs/PHASE5_AGENT_BRIEF.md wave-10 lesson); GPR reads are volatile too
    void bump(u64 n) noexcept {
        volatile u64& t = c.cycles;
        t = t + n;
    }
    void backedge() { rt::check_events(c); }

    // loads / stores: the runtime's instructions (alignment faults, unmapped faults, hardware windows)
    void lb(Gpr& d, const Gpr& b, s32 o) { rt::lb(c, d.r, b.r, o); }
    void lbu(Gpr& d, const Gpr& b, s32 o) { rt::lbu(c, d.r, b.r, o); }
    void lh(Gpr& d, const Gpr& b, s32 o) { rt::lh(c, d.r, b.r, o); }
    void lhu(Gpr& d, const Gpr& b, s32 o) { rt::lhu(c, d.r, b.r, o); }
    void lw(Gpr& d, const Gpr& b, s32 o) { rt::lw(c, d.r, b.r, o); }
    void ld(Gpr& d, const Gpr& b, s32 o) { rt::ld(c, d.r, b.r, o); }
    void lq(Gpr& d, const Gpr& b, s32 o) { rt::lq(c, d.r, b.r, o); }
    void sb(const Gpr& s, const Gpr& b, s32 o) { rt::sb(c, s.r, b.r, o); }
    void sh(const Gpr& s, const Gpr& b, s32 o) { rt::sh(c, s.r, b.r, o); }
    void sw(const Gpr& s, const Gpr& b, s32 o) { rt::sw(c, s.r, b.r, o); }
    void sd(const Gpr& s, const Gpr& b, s32 o) { rt::sd(c, s.r, b.r, o); }
    void sq(const Gpr& s, const Gpr& b, s32 o) { rt::sq(c, s.r, b.r, o); }

    // FPU (the runtime's instruction semantics: EE singles, ACC, FCR31 flags)
    void lwc1(unsigned f, const Gpr& b, s32 o) { rt::lwc1(c, f, b.r, o); }
    void swc1(unsigned f, const Gpr& b, s32 o) { rt::swc1(c, f, b.r, o); }
    void mtc1(const Gpr& g, unsigned f) { rt::mtc1(c, g.r, f); }
    void mfc1(Gpr& g, unsigned f) { rt::mfc1(c, g.r, f); }
    void cvt_s_w(unsigned d, unsigned s) { rt::cvt_s_w(c, d, s); }
    void cvt_w_s(unsigned d, unsigned s) { rt::cvt_w_s(c, d, s); }
    void mov_s(unsigned d, unsigned s) { rt::mov_s(c, d, s); }
    void neg_s(unsigned d, unsigned s) { rt::neg_s(c, d, s); }
    void abs_s(unsigned d, unsigned s) { rt::abs_s(c, d, s); }
    void add_s(unsigned d, unsigned s, unsigned t) { rt::add_s(c, d, s, t); }
    void sub_s(unsigned d, unsigned s, unsigned t) { rt::sub_s(c, d, s, t); }
    void mul_s(unsigned d, unsigned s, unsigned t) { rt::mul_s(c, d, s, t); }
    void div_s(unsigned d, unsigned s, unsigned t) { rt::div_s(c, d, s, t); }
    void adda_s(unsigned s, unsigned t) { rt::adda_s(c, s, t); }
    void mula_s(unsigned s, unsigned t) { rt::mula_s(c, s, t); }
    void madda_s(unsigned s, unsigned t) { rt::madda_s(c, s, t); }
    void madd_s(unsigned d, unsigned s, unsigned t) { rt::madd_s(c, d, s, t); }
    void msub_s(unsigned d, unsigned s, unsigned t) { rt::msub_s(c, d, s, t); }
    void c_eq_s(unsigned s, unsigned t) { rt::c_eq_s(c, s, t); }
    void c_lt_s(unsigned s, unsigned t) { rt::c_lt_s(c, s, t); }
    void c_le_s(unsigned s, unsigned t) { rt::c_le_s(c, s, t); }
    bool cc() const { return rt::cop1_cond(c); }  // the FCR31 C bit (bc1t; !cc() for bc1f)

    // HI/LO
    void div(const Gpr& s, const Gpr& t) { rt::div(c, s.r, t.r); }
    void divu(const Gpr& s, const Gpr& t) { rt::divu(c, s.r, t.r); }
    void mult(const Gpr& d, const Gpr& s, const Gpr& t) { rt::mult(c, d.r, s.r, t.r); }
    void mfhi(Gpr& d) { rt::mfhi(c, d.r); }
    void mflo(Gpr& d) { rt::mflo(c, d.r); }

    // `jal fn` with $ra = the original link
    void jal(u32 link, rt::Fn fn) {
        rt::jal(c, link);
        fn(c);
    }
    // `jalr target` ($ra = the original link): the function at the address the register holds
    void jalr(const Gpr& target, u32 link) {
        const u32 t = static_cast<u32>(target);
        rt::jalr(c, GPR_RA, link);
        rt::lookup_func(t)(c);
    }
    // A `jr` through a jump table whose target is not one of the listed labels: the recompiled body's tail jump.
    void jr_unknown(const Gpr& target) { rt::lookup_func(static_cast<u32>(target))(c); }

    // `lw rX, -18692(gp)`
    void gbtl(Gpr& d) { lw(d, gp, kGpBtl); }

    // A float constant through a GPR: `lui g, hi; mtc1 g, f` (the GPR keeps the upper half, as the original leaves it)
    void lif(Gpr& g, u32 hi, unsigned f) {
        g = lui(hi);
        mtc1(g, f);
    }

    // --- compiled idioms -------------------------------------------------------------------------------------------
    // (float)(u32)x: `bltz x; mtc1 x, fs; cvt.s.w fd, fs` (5 cycles) or, for a negative word, `srl hi, x, 1; andi lo,
    // x, 1; or hi, hi, lo; mtc1 hi, fs; cvt.s.w fd, fs; add.s fd, fd, fd` (7 cycles)
    void u2f(unsigned fd, unsigned fs, const Gpr& x, Gpr& hi, Gpr& lo) {
        if (ltz(x)) {
            charge(7);
            hi = srl(x, 1);
            lo = x & 0x1;
            hi = hi | lo;
            mtc1(hi, fs);
            cvt_s_w(fd, fs);
            add_s(fd, fd, fd);
        } else {
            charge(5);
            mtc1(x, fs);
            cvt_s_w(fd, fs);
        }
    }
    // (u32)f & mask: `lui t, 0x4F00; mtc1 t, $f0; c.le.s $f0, fs` then `cvt.w.s` of f or of f - 2^31 with bit 31 set
    // (6 cycles either way); $f0 is the scratch
    void f2u(Gpr& d, unsigned fs, Gpr& t, u32 mask) {
        lif(t, 0x4f00, F0);
        c_le_s(F0, fs);
        if (cc()) {
            charge(6);
            sub_s(F0, fs, F0);
            cvt_w_s(F0, F0);
            mfc1(d, F0);
            t = lui(0x8000);
            d = d | t;
            d = d & mask;
        } else {
            charge(6);
            cvt_w_s(F0, fs);
            mfc1(d, F0);
            d = d & mask;
        }
    }
    // four floats src+so.. -> dst+dofs.. through $f3, $f2, $f1, $f0 (loads first, as compiled)
    void copy_vec4(const Gpr& src, s32 so, const Gpr& dst, s32 dofs) {
        lwc1(F3, src, so);
        lwc1(F2, src, so + 4);
        lwc1(F1, src, so + 8);
        lwc1(F0, src, so + 12);
        swc1(F3, dst, dofs);
        swc1(F2, dst, dofs + 4);
        swc1(F1, dst, dofs + 8);
        swc1(F0, dst, dofs + 12);
    }
    // three floats through $f2, $f1, $f0
    void copy_vec3(const Gpr& src, s32 so, const Gpr& dst, s32 dofs) {
        lwc1(F2, src, so);
        lwc1(F1, src, so + 4);
        lwc1(F0, src, so + 8);
        swc1(F2, dst, dofs);
        swc1(F1, dst, dofs + 4);
        swc1(F0, dst, dofs + 8);
    }
    // the RGBA word `rgba` through the frame bytes sp+off..off+3 -> four floats (byte * 1/255) at v1+dst: the u2f
    // scratch is a0 / a1; `last` = the cycles of the fourth channel's block (it runs on into the caller's next code)
    void colour_to_floats(const Gpr& rgba, s32 off, s32 dst, u64 last) {
        sw(rgba, sp, off);
        for (int k = 0; k < 4; ++k) {
            lbu(a0, sp, off + k);
            u2f(F1, F0, a0, a1, a0);
            charge(k < 3 ? 6 : last);
            lwc1(F0, gp, btl_cam::kGpInv255);
            mul_s(F0, F0, F1);
            swc1(F0, v1, dst + 4 * k);
        }
    }
    // the SKILL.TBL record of skill (u16) `idx`: `idx &= 0xFFFF; out = ((idx * 5) * 2 + idx) * 4 + base`
    void skill_record(Gpr& out, Gpr& idx, const Gpr& base) {
        idx = idx & 0xffff;
        out = sll(idx, 2);
        out = addu(out, idx);
        out = sll(out, 1);
        out = addu(out, idx);
        out = sll(out, 2);
        out = addu(out, base);
    }
    // a btlUnit's RGBA bytes (+48..+51) to the frame bytes sp+off.. through a1, a0, v1, v0
    void unit_rgba_to_frame(const Gpr& unit, s32 off) {
        lbu(a1, unit, 48);
        lbu(a0, unit, 49);
        lbu(v1, unit, 50);
        lbu(v0, unit, 51);
        sb(a1, sp, off);
        sb(a0, sp, off + 1);
        sb(v1, sp, off + 2);
        sb(v0, sp, off + 3);
    }

#define P3FES_BCAM_BODY(name, addr) void name();
    P3FES_BCAM_BODIES(P3FES_BCAM_BODY)
#undef P3FES_BCAM_BODY
    // shared tails
    void epilogue_2A1710();
    void epilogue_2A1B70();
    void epilogue_2A38F0();
    void epilogue_2A3E80();
    // group-0 helpers (battle_camera.cpp)
    void skill_needs_camera();
    void skill_attr_flags(const Gpr& skill);
    void clamp_axis_2A3590(s32 axis, u32 link, u64 after);
    bool in_span_2A3E80(s32 lo, s32 hi, s32 xo);
    void show_unit_2A3E80(u32 link2, u32 link4, bool also4);
    void unit_pass_2A3E80();
    void copy_key();
};

}  // namespace p3fes::game::bcam
