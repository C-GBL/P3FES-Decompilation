// The big draw bodies earlier slices left for their size (Phase 5 slice `big_draws`): the title screen's three
// per-frame draws from op_title.c / op_menu.c / op_wait.c (the `title` slice, game/src/ui/title.cpp, has the rest of
// those files) and the date / time HUD's three digit helpers that H_DayPartsDraw_DrawHud calls every field frame (the
// `ui3` slice, game/src/ui/ui3.cpp, has the HUD task). game/src/ui/big_draws.cpp, pair tests
// tests/game/test_big_draws.cpp.
//
// Names: as symbols/functions.json gives them now (all sub_*); a bracketed name is our proposal (from the K_Assert file
// string, the callers and what the body does). The work layouts of the title modules are in title.h / title.cpp; the
// fields these draws use are named below.
//
// Every function here is register-faithful at each check point, call and return (docs/PHASE5_AGENT_BRIEF.md, the
// wave-6 / wave-7 lessons): the bodies run on big_draws::Cpu, one variable per guest register, with the runtime's own
// load / store / FPU instruction semantics; the prologue spills go to the guest stack; every scratch register holds the
// original's value whenever a callee, a check point or the caller can see it; the callees run through their generated
// entry points with $ra = the original link.
#pragma once

#include "p3fes/ee/core.h"
#include "p3fes/ee_context.h"
#include "p3fes_recomp_rt.h"

namespace p3fes::recomp_gen {
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);  // K_Assert(file, line): `jr ra` in retail
void fn_sinf_0052e878(p3fes::EEContext&);         // libm sinf($f12) -> $f0
void fn_cosf_0052e6d8(p3fes::EEContext&);         // libm cosf($f12) -> $f0
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace big_draws {

// --- globals ($gp = 0x7D2CF0) ------------------------------------------------------------------------------------
inline constexpr s32 kGpOpTitle = -18756;     // op_title.c work (title.h kGpOpTitle)
inline constexpr s32 kGpOpMenu = -18748;      // op_menu.c work
inline constexpr s32 kGpOpWait = -18744;      // op_wait.c work
inline constexpr s32 kGpHudBlink = -19708;    // s32: the HUD's moon-glow counter 0..40 (sub_183840)
inline constexpr u32 kFileOpTitle = 0x68ED00u;  // "op_title.c"
inline constexpr u32 kFileOpMenu = 0x68ED20u;   // "op_menu.c"
inline constexpr u32 kFileOpWait = 0x68ED30u;   // "op_wait.c"
inline constexpr u32 kMoonPhaseTable = 0x5E38D0u;  // u8[]: the moon phase (0..29) of each day since the start
inline constexpr u32 kHudMoonJump = 0x7B6630u;     // sub_183840's jump table: moon phase 0..29 -> the phase icon
inline constexpr u32 kHudWeekdayJump = 0x7B66B0u;  // sub_183BE0's: weekday 0..6 -> the weekday glyph
inline constexpr u32 kHudPartJump = 0x7B66D0u;     // sub_183F60's: day part 0..8 -> the part's name

namespace detail {

namespace core = ee::core;

// --- R5900 integer results (32-bit operations sign-extend into the 64-bit register) ------------------------------
constexpr u64 si(s32 v) { return static_cast<u64>(static_cast<s64>(v)); }  // a negative immediate (`li rX, -n`)
constexpr u64 addu(u64 a, u64 b) { return core::add32(a, b); }
constexpr u64 addiu(u64 a, s32 i) { return core::add32i(a, i); }
constexpr u64 subu(u64 a, u64 b) { return core::sub32(a, b); }
constexpr u64 daddu(u64 a, u64 b) { return core::add64(a, b); }
constexpr u64 lui(u32 i) { return core::lui(i); }
constexpr u64 sll(u64 a, unsigned n) { return core::sll(a, n); }
constexpr u64 srl(u64 a, unsigned n) { return core::srl(a, n); }
constexpr u64 sra(u64 a, unsigned n) { return core::sra(a, n); }
constexpr u64 dsll32(u64 a, unsigned n) { return core::dsll32(a, n); }
constexpr u64 dsra32(u64 a, unsigned n) { return core::dsra32(a, n); }
constexpr u64 slt(u64 a, u64 b) { return core::slt(a, b); }
constexpr u64 sltu(u64 a, u64 b) { return core::sltu(a, b); }
constexpr u64 slti(u64 a, s32 i) { return core::slti(a, i); }
constexpr u64 sltiu(u64 a, s32 i) { return core::sltiu(a, i); }
constexpr u64 nor(u64 a, u64 b) { return core::nor64(a, b); }
// The branch tests on whole 64-bit registers (bltz / bgez).
constexpr bool ltz(u64 a) { return static_cast<s64>(a) < 0; }
constexpr bool gez(u64 a) { return static_cast<s64>(a) >= 0; }

// One GPR of the guest context (a 64-bit write keeps bits 64..127, as the EE does). Reads go through a volatile
// lvalue, and so does virtual time below (render_core3's lesson, docs/PHASE5_AGENT_BRIEF.md wave 10: MSVC /O2 was
// seen keeping ctx.cycles in a host register across a call to a small helper that charges): a volatile access is a
// compiler barrier under /volatile:ms and keeps every access real under clang-cl, so no guest state is cached across
// a helper.
struct Gpr {
    EEContext& c;
    const unsigned r;
    operator u64() const noexcept { return static_cast<const volatile u64&>(c.gpr[r].u64[0]); }
    u32 u() const noexcept { return static_cast<const volatile u32&>(c.gpr[r].u32[0]); }
    Gpr& operator=(u64 v) noexcept {
        core::set_gpr64(c, r, v);
        return *this;
    }
    Gpr& operator=(const Gpr& o) noexcept { return *this = static_cast<u64>(o); }
};

// FPR numbers.
enum : unsigned {
    F0, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15,
    F16, F17, F18, F19, F20, F21, F22, F23, F24, F25, F26, F27, F28, F29, F30, F31
};

// The guest machine as the bodies see it.
class Cpu {
public:
    explicit Cpu(EEContext& ctx) noexcept : c(ctx) {}

    EEContext& c;
    Gpr zero{c, 0}, at{c, 1}, v0{c, 2}, v1{c, 3}, a0{c, 4}, a1{c, 5}, a2{c, 6}, a3{c, 7};
    Gpr t0{c, 8}, t1{c, 9}, t2{c, 10}, t3{c, 11}, t4{c, 12}, t5{c, 13}, t6{c, 14}, t7{c, 15};
    Gpr s0{c, 16}, s1{c, 17}, s2{c, 18}, s3{c, 19}, s4{c, 20}, s5{c, 21}, s6{c, 22}, s7{c, 23};
    Gpr t8{c, 24}, t9{c, 25}, gp{c, 28}, sp{c, 29}, fp{c, 30}, ra{c, 31};

    // virtual time (ADR-0013); a check point may raise a fatal event that unwinds through the body
    void enter(u64 n) {
        rt::check_events(c);
        charge(n);
    }
    void charge(u64 n) noexcept {
        volatile u64& t = c.cycles;
        t = t + n;
    }
    void backedge() { rt::check_events(c); }

    // Loads and stores in the instruction's own form, `lw(rt, base, imm)` = `lw rt, imm(base)`, with the runtime's
    // semantics (the RAM / scratchpad / BIOS windows, the hardware bus, the address-error / unmapped faults of the
    // recompiled body: a bad pointer stops both versions at the same instruction with the same registers).
    void lw(Gpr& d, const Gpr& b, s32 i) { rt::lw(c, d.r, b.r, i); }
    void lbu(Gpr& d, const Gpr& b, s32 i) { rt::lbu(c, d.r, b.r, i); }
    void ld(Gpr& d, const Gpr& b, s32 i) { rt::ld(c, d.r, b.r, i); }
    void lq(Gpr& d, const Gpr& b, s32 i) { rt::lq(c, d.r, b.r, i); }
    void sw(const Gpr& t, const Gpr& b, s32 i) { rt::sw(c, t.r, b.r, i); }
    void sb(const Gpr& t, const Gpr& b, s32 i) { rt::sb(c, t.r, b.r, i); }
    void sd(const Gpr& t, const Gpr& b, s32 i) { rt::sd(c, t.r, b.r, i); }
    void sq(const Gpr& t, const Gpr& b, s32 i) { rt::sq(c, t.r, b.r, i); }

    // FPU (the runtime's instruction semantics: EE singles, ACC, FCR31 flags)
    void lwc1(unsigned f, const Gpr& b, s32 i) { rt::lwc1(c, f, b.r, i); }
    void swc1(unsigned f, const Gpr& b, s32 i) { rt::swc1(c, f, b.r, i); }
    void mtc1(const Gpr& g, unsigned f) noexcept { rt::mtc1(c, g.r, f); }
    void mfc1(Gpr& g, unsigned f) noexcept { rt::mfc1(c, g.r, f); }
    void mov_s(unsigned d, unsigned s) noexcept { rt::mov_s(c, d, s); }
    void cvt_s_w(unsigned d, unsigned s) noexcept { rt::cvt_s_w(c, d, s); }
    void cvt_w_s(unsigned d, unsigned s) noexcept { rt::cvt_w_s(c, d, s); }
    void add_s(unsigned d, unsigned s, unsigned t) noexcept { rt::add_s(c, d, s, t); }
    void sub_s(unsigned d, unsigned s, unsigned t) noexcept { rt::sub_s(c, d, s, t); }
    void mul_s(unsigned d, unsigned s, unsigned t) noexcept { rt::mul_s(c, d, s, t); }
    void div_s(unsigned d, unsigned s, unsigned t) noexcept { rt::div_s(c, d, s, t); }
    void adda_s(unsigned s, unsigned t) noexcept { rt::adda_s(c, s, t); }
    void mula_s(unsigned s, unsigned t) noexcept { rt::mula_s(c, s, t); }
    void madd_s(unsigned d, unsigned s, unsigned t) noexcept { rt::madd_s(c, d, s, t); }
    void msub_s(unsigned d, unsigned s, unsigned t) noexcept { rt::msub_s(c, d, s, t); }
    void c_le_s(unsigned s, unsigned t) noexcept { rt::c_le_s(c, s, t); }
    bool cop1_cond() const noexcept { return rt::cop1_cond(c); }

    // HI/LO
    void div(const Gpr& s, const Gpr& t) noexcept { rt::div(c, s.r, t.r); }
    void mflo(Gpr& d) noexcept { rt::mflo(c, d.r); }
    void mfhi(Gpr& d) noexcept { rt::mfhi(c, d.r); }

    // `jal fn` at pc ($ra = pc + 8; the delay slot's instruction is written before the call)
    void jal(u32 pc, rt::Fn fn) {
        rt::jal(c, pc);
        fn(c);
    }
    // A `jr` through a jump table whose target is none of the table's labels: the recompiled body's tail jump.
    void tail(u32 target) { rt::lookup_func(target)(c); }
    // `lui a0, hi(file); addiu a0, a0, lo(file); li a1, line; jal K_Assert` (sub_19D3F0, `jr ra` in retail: the failed
    // check continues; the block's cycles are the caller's).
    void kassert(u32 pc, u32 file, u32 line) {
        a0 = lui((file + 0x8000u) >> 16);
        a0 = addiu(a0, static_cast<s16>(file & 0xFFFFu));
        a1 = line;
        jal(pc, &::p3fes::recomp_gen::fn_sub_19D3F0_0019d3f0);
    }

    // --- idioms the compiler repeats verbatim (each is the exact instruction sequence of every place it stands for) ---
    // `(u8)(u32)f` of $f`fs` into `r`: below 2^31 a plain cvt.w.s; from 2^31 up, cvt.w.s(f - 2^31) | 0x80000000. The two
    // arms are 6-instruction blocks; $f0 and `tmp` ($v0 unless given) keep what the taken arm left.
    void f2u8(Gpr& r, unsigned fs, Gpr& tmp) {
        tmp = lui(0x4F00);  // 2147483648.0
        mtc1(tmp, F0);
        c_le_s(F0, fs);
        if (!cop1_cond()) {
            charge(6);
            cvt_w_s(F0, fs);
            mfc1(r, F0);
            r = r & 0xFF;
        } else {
            charge(6);
            sub_s(F0, fs, F0);
            cvt_w_s(F0, F0);
            mfc1(r, F0);
            tmp = lui(0x8000);
            r = r | tmp;
            r = r & 0xFF;
        }
    }
    void f2u8(Gpr& r, unsigned fs) { f2u8(r, fs, v0); }
    // A white RGBA on the frame at sp + `rgba` (r = g = b = 255) and its alpha byte (u8)(255 * $f`fa`) left in $v1
    // (the caller stores it at sp + rgba + 3).
    void white_alpha(s32 rgba, unsigned fa) {
        v0 = 255;
        sb(v0, sp, rgba);
        sb(v0, sp, rgba + 1);
        sb(v0, sp, rgba + 2);
        v0 = lui(0x437F);  // 255.0
        mtc1(v0, F0);
        mul_s(F1, F0, fa);
        f2u8(v1, F1);
    }
    // One compiled loop over the four corners {x, y} of the quad on the frame at sp + `base` (the caller zeroed $v1, the
    // corner; $v0 its address): x op= $f`fx`, y op= $f`fy`. The test block costs 3 and checks first, the body 10.
    enum class QuadOp { Sub, Mul, Add };
    void quad_pass(s32 base, QuadOp op, unsigned fx, unsigned fy) {
        for (;;) {
            charge(3);
            v0 = slti(v1, 4);
            if (v0 == 0) break;
            backedge();
            charge(10);
            v0 = sll(v1, 3);
            v0 = addu(v0, sp);
            v0 = addiu(v0, base);
            for (const s32 k : {0, 4}) {
                lwc1(F0, v0, k);
                const unsigned f = k == 0 ? fx : fy;
                if (op == QuadOp::Sub) sub_s(F0, F0, f);
                else if (op == QuadOp::Mul) mul_s(F0, F0, f);
                else add_s(F0, F0, f);
                swc1(F0, v0, k);
            }
            v1 = addiu(v1, 1);
        }
    }
    // The compiled rotation of the four corners at sp + `base` by the angle $f`ang` (the caller zeroed $s2, the corner;
    // $s0 / $s5 its x / y): x' = x cos - y sin, y' = y cos + x sin through sinf / cosf twice per corner (jal at `link`,
    // +0x14, +0x2C, +0x40; the scratch FPRs `sn` = sin, `cd` = the other coordinate, `out` = x' as compiled). The test
    // block costs 3 and checks first, the body 29.
    void rotate_quad(s32 base, u32 link, unsigned ang, unsigned sn, unsigned cd, unsigned out) {
        for (;;) {
            charge(3);
            v0 = slti(s2, 4);
            if (v0 == 0) break;
            backedge();
            charge(29);
            v0 = sll(s2, 3);
            v0 = addu(v0, sp);
            s0 = addiu(v0, base);
            s5 = addiu(s0, 4);
            mov_s(F12, ang);
            jal(link, kSinf);
            mov_s(sn, F0);
            lwc1(cd, s5, 0);
            mov_s(F12, ang);
            jal(link + 0x14, kCosf);
            lwc1(F1, s0, 0);
            mula_s(F1, F0);
            msub_s(out, cd, sn);
            mov_s(F12, ang);
            jal(link + 0x2C, kSinf);
            mov_s(sn, F0);
            lwc1(cd, s0, 0);
            mov_s(F12, ang);
            jal(link + 0x40, kCosf);
            lwc1(F1, s5, 0);
            mula_s(F1, F0);
            madd_s(F0, cd, sn);
            swc1(out, s0, 0);
            swc1(F0, s5, 0);
            s2 = addiu(s2, 1);
        }
    }
    // The four corners at sp + 128 scaled about the screen centre (320, 224) by ($f22, $f21): minus the centre, times
    // the scale, plus the centre ($f2 / $f1 hold the centre, loaded twice as compiled).
    void scale_quad_about_centre() {
        const auto centre = [this] {
            v0 = lui(0x43A0);  // 320.0
            mtc1(v0, F2);
            v0 = lui(0x4360);  // 224.0
            mtc1(v0, F1);
        };
        v1 = 0;
        centre();
        quad_pass(128, QuadOp::Sub, F2, F1);
        charge(3);
        v1 = 0;
        quad_pass(128, QuadOp::Mul, F22, F21);
        charge(7);
        v1 = 0;
        centre();
        quad_pass(128, QuadOp::Add, F2, F1);
    }
    static constexpr rt::Fn kSinf = &::p3fes::recomp_gen::fn_sinf_0052e878;
    static constexpr rt::Fn kCosf = &::p3fes::recomp_gen::fn_cosf_0052e6d8;

    // --- the bodies (named as the functions they are; documented at their definitions) ---
    void sub_183840();
    void sub_183BE0();
    void sub_183F60();
    void sub_267430();
    void sub_26A2C0();
    void sub_26EED0();
};

}  // namespace detail
}  // namespace big_draws

// --- the date / time HUD (the ui3 slice's H_DayPartsDraw_DrawHud calls these; $a0 = the HUD sprite file, $f12 = the
// slide offset x, $f13 = 0, $a1 = the colour / alpha byte, $a2 / $a3 = month / day) --------------------------------
void sub_183840(EEContext& ctx);  // [H_DayPartsDraw_DrawMoon] the moon disc, the phase icon, the glow, the phase label
void sub_183BE0(EEContext& ctx);  // [H_DayPartsDraw_DrawDate] month / day digits, the weekday glyph in its colour
void sub_183F60(EEContext& ctx);  // [H_DayPartsDraw_DrawDayPart] the day-part name ($t0 = the part, 0..8)
// --- the title screen (op_root's per-frame module calls, title.cpp sub_265030) ---------------------------------------
void sub_267430(EEContext& ctx);  // [opTitle_Draw] the title logo and its settling animation, the particles
void sub_26A2C0(EEContext& ctx);  // opMenuUpdate: the title menu's items (fade, cursor, selection flash)
void sub_26EED0(EEContext& ctx);  // [opWait_Draw] the "press start" screen

}  // namespace p3fes::game
