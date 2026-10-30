// The register view the Tartarus slice's bodies are written on (slice `tartarus`, game/src/field/tartarus_*.cpp).
//
// These functions run under the field root, the event task, the dungeon / stratum tasks and the enemy-think tasks; any
// check point may preempt the thread, and the kernel then writes the WHOLE register file to the guest stack (brief,
// wave 7). So every body keeps each value in the register the original keeps it in: one proxy per GPR (`v0 = lw(s0,
// 24)`), the FPU, HI/LO and the multiply / divide unit through the runtime's own instruction semantics (rt::*), loads
// and stores through the runtime's own accessors (rt::lw .. rt::sq: the same fast path and the same slow path for
// addresses outside RAM). Scratch registers, HI/LO, the FPRs, ACC and FCR31 therefore hold the original's values at
// every check point and at the return; within one block (no check point inside) a body may order independent
// statements as reads best, across blocks the order is the original's.
//
// Virtual time (ADR-0013): enter / charge / backedge mirror the `ctx.cycles += N` blocks and the back-edge checks of
// the recompiled body (recomp/generated/fn_0039 / fn_0040 / fn_0041); a block containing a `jal` is charged whole
// before the call, as the generated code does. Callees are entered through their generated entry points with $ra =
// the original link (`jal(pc, fn)` writes pc + 8).
#pragma once

#include "p3fes/ee/core.h"
#include "p3fes/game/guest.h"
#include "p3fes_recomp_rt.h"

#include <cstdint>

namespace p3fes::game::tartarus {

namespace core = ee::core;

// --- R5900 integer results (32-bit operations sign-extend into the 64-bit register) ------------------------------------
constexpr u64 si(s32 v) { return static_cast<u64>(static_cast<s64>(v)); }  // `addiu rd, $zero, imm`
constexpr u64 addu(u64 a, u64 b) { return core::add32(a, b); }
constexpr u64 addiu(u64 a, s32 i) { return core::add32i(a, i); }
constexpr u64 subu(u64 a, u64 b) { return core::sub32(a, b); }
constexpr u64 daddu(u64 a, u64 b) { return core::add64(a, b); }
constexpr u64 daddiu(u64 a, s32 i) { return core::add64i(a, i); }
constexpr u64 dsubu(u64 a, u64 b) { return core::sub64(a, b); }
constexpr u64 nor(u64 a, u64 b) { return core::nor64(a, b); }
constexpr u64 lui(u32 i) { return core::lui(i); }
constexpr u64 sll(u64 a, unsigned n) { return core::sll(a, n); }
constexpr u64 srl(u64 a, unsigned n) { return core::srl(a, n); }
constexpr u64 sra(u64 a, unsigned n) { return core::sra(a, n); }
constexpr u64 sllv(u64 a, u64 n) { return core::sllv(a, n); }
constexpr u64 srlv(u64 a, u64 n) { return core::srlv(a, n); }
constexpr u64 srav(u64 a, u64 n) { return core::srav(a, n); }
constexpr u64 dsll(u64 a, unsigned n) { return core::dsll(a, n); }
constexpr u64 dsrl(u64 a, unsigned n) { return core::dsrl(a, n); }
constexpr u64 dsra(u64 a, unsigned n) { return core::dsra(a, n); }
constexpr u64 dsll32(u64 a, unsigned n) { return core::dsll32(a, n); }
constexpr u64 dsrl32(u64 a, unsigned n) { return core::dsrl32(a, n); }
constexpr u64 dsra32(u64 a, unsigned n) { return core::dsra32(a, n); }
constexpr u64 slt(u64 a, u64 b) { return core::slt(a, b); }
constexpr u64 sltu(u64 a, u64 b) { return core::sltu(a, b); }
constexpr u64 slti(u64 a, s32 i) { return core::slti(a, i); }
constexpr u64 sltiu(u64 a, s32 i) { return core::sltiu(a, i); }
constexpr bool ltz(u64 a) { return static_cast<s64>(a) < 0; }
constexpr bool lez(u64 a) { return static_cast<s64>(a) <= 0; }
constexpr bool gtz(u64 a) { return static_cast<s64>(a) > 0; }
constexpr bool gez(u64 a) { return static_cast<s64>(a) >= 0; }
constexpr u32 w(u64 v) { return static_cast<u32>(v); }

using LoadFn = void (*)(EEContext&, rt::Reg, rt::Reg, std::int32_t);

// A load waiting for its destination register: `v0 = lw(s0, 24)` runs rt::lw(ctx, 2, 16, 24).
struct Load {
    LoadFn fn;
    rt::Reg base;
    s32 off;
};

// One GPR of the guest context (64-bit writes keep bits 64..127, as the EE does).
struct Gpr {
    EEContext* c;
    unsigned r;
    operator u64() const noexcept { return c->gpr[r].u64[0]; }
    Gpr& operator=(u64 v) noexcept {
        core::set_gpr64(*c, r, v);
        return *this;
    }
    Gpr& operator=(const Gpr& o) noexcept { return *this = static_cast<u64>(o); }
    Gpr& operator=(const Load& l) {
        l.fn(*c, r, l.base, l.off);
        return *this;
    }
};

// The guest machine as the bodies see it. IDA's register names: r8..r11 = $a4..$a7, r12..r15 = $t4..$t7.
class Cpu {
public:
    explicit Cpu(EEContext& ctx) noexcept : c(ctx) {}

    EEContext& c;
    Gpr zero{&c, 0}, at{&c, 1}, v0{&c, 2}, v1{&c, 3}, a0{&c, 4}, a1{&c, 5}, a2{&c, 6}, a3{&c, 7};
    Gpr a4{&c, 8}, a5{&c, 9}, a6{&c, 10}, a7{&c, 11}, t4{&c, 12}, t5{&c, 13}, t6{&c, 14}, t7{&c, 15};
    Gpr s0{&c, 16}, s1{&c, 17}, s2{&c, 18}, s3{&c, 19}, s4{&c, 20}, s5{&c, 21}, s6{&c, 22}, s7{&c, 23};
    Gpr t8{&c, 24}, t9{&c, 25}, gp{&c, 28}, sp{&c, 29}, fp{&c, 30}, ra{&c, 31};

    // virtual time
    void enter(u64 n) { guest::enter(c, n); }  // not noexcept: a check point may raise a fatal event
    void charge(u64 n) noexcept { guest::charge(c, n); }
    void backedge() { guest::backedge(c); }

    // loads (assigned to a register) and stores at base + off, through the runtime's accessors
    static Load lb(const Gpr& b, s32 o) noexcept { return {&rt::lb, b.r, o}; }
    static Load lbu(const Gpr& b, s32 o) noexcept { return {&rt::lbu, b.r, o}; }
    static Load lh(const Gpr& b, s32 o) noexcept { return {&rt::lh, b.r, o}; }
    static Load lhu(const Gpr& b, s32 o) noexcept { return {&rt::lhu, b.r, o}; }
    static Load lw(const Gpr& b, s32 o) noexcept { return {&rt::lw, b.r, o}; }
    static Load lwu(const Gpr& b, s32 o) noexcept { return {&rt::lwu, b.r, o}; }
    static Load ld(const Gpr& b, s32 o) noexcept { return {&rt::ld, b.r, o}; }
    void sb(const Gpr& b, s32 o, const Gpr& v) { rt::sb(c, v.r, b.r, o); }
    void sh(const Gpr& b, s32 o, const Gpr& v) { rt::sh(c, v.r, b.r, o); }
    void sw(const Gpr& b, s32 o, const Gpr& v) { rt::sw(c, v.r, b.r, o); }
    void sd(const Gpr& b, s32 o, const Gpr& v) { rt::sd(c, v.r, b.r, o); }
    // the 128-bit register moves and the unaligned doubleword halves (register first, as the instructions read)
    void sq(const Gpr& v, const Gpr& b, s32 o) { rt::sq(c, v.r, b.r, o); }
    void lq(const Gpr& v, const Gpr& b, s32 o) { rt::lq(c, v.r, b.r, o); }
    void ldl(const Gpr& v, const Gpr& b, s32 o) { rt::ldl(c, v.r, b.r, o); }
    void ldr(const Gpr& v, const Gpr& b, s32 o) { rt::ldr(c, v.r, b.r, o); }
    void sdl(const Gpr& v, const Gpr& b, s32 o) { rt::sdl(c, v.r, b.r, o); }
    void sdr(const Gpr& v, const Gpr& b, s32 o) { rt::sdr(c, v.r, b.r, o); }

    // FPU (EE singles, FCR31 flags, ACC)
    void lwc1(unsigned f, const Gpr& b, s32 o) { rt::lwc1(c, f, b.r, o); }
    void swc1(unsigned f, const Gpr& b, s32 o) { rt::swc1(c, f, b.r, o); }
    void mtc1(const Gpr& g, unsigned f) { rt::mtc1(c, g.r, f); }
    void mfc1(const Gpr& g, unsigned f) { rt::mfc1(c, g.r, f); }
    void cvt_s_w(unsigned d, unsigned s) { rt::cvt_s_w(c, d, s); }
    void cvt_w_s(unsigned d, unsigned s) { rt::cvt_w_s(c, d, s); }
    void add_s(unsigned d, unsigned s, unsigned t) { rt::add_s(c, d, s, t); }
    void sub_s(unsigned d, unsigned s, unsigned t) { rt::sub_s(c, d, s, t); }
    void mul_s(unsigned d, unsigned s, unsigned t) { rt::mul_s(c, d, s, t); }
    void div_s(unsigned d, unsigned s, unsigned t) { rt::div_s(c, d, s, t); }
    void madd_s(unsigned d, unsigned s, unsigned t) { rt::madd_s(c, d, s, t); }
    void msub_s(unsigned d, unsigned s, unsigned t) { rt::msub_s(c, d, s, t); }
    void adda_s(unsigned s, unsigned t) { rt::adda_s(c, s, t); }
    void suba_s(unsigned s, unsigned t) { rt::suba_s(c, s, t); }
    void mula_s(unsigned s, unsigned t) { rt::mula_s(c, s, t); }
    void madda_s(unsigned s, unsigned t) { rt::madda_s(c, s, t); }
    void msuba_s(unsigned s, unsigned t) { rt::msuba_s(c, s, t); }
    void mov_s(unsigned d, unsigned s) { rt::mov_s(c, d, s); }
    void neg_s(unsigned d, unsigned s) { rt::neg_s(c, d, s); }
    void abs_s(unsigned d, unsigned s) { rt::abs_s(c, d, s); }
    void sqrt_s(unsigned d, unsigned t) { rt::sqrt_s(c, d, t); }
    void c_le_s(unsigned s, unsigned t) { rt::c_le_s(c, s, t); }
    void c_lt_s(unsigned s, unsigned t) { rt::c_lt_s(c, s, t); }
    void c_eq_s(unsigned s, unsigned t) { rt::c_eq_s(c, s, t); }
    bool cond() const { return rt::cop1_cond(c); }

    // HI/LO (the EE three-operand multiply: rd = LO) and the MMI byte add
    void mult(const Gpr& d, const Gpr& s, const Gpr& t) { rt::mult(c, d.r, s.r, t.r); }
    void multu(const Gpr& d, const Gpr& s, const Gpr& t) { rt::multu(c, d.r, s.r, t.r); }
    void div(const Gpr& s, const Gpr& t) { rt::div(c, s.r, t.r); }
    void divu(const Gpr& s, const Gpr& t) { rt::divu(c, s.r, t.r); }
    void mfhi(const Gpr& d) { rt::mfhi(c, d.r); }
    void mflo(const Gpr& d) { rt::mflo(c, d.r); }
    void paddub(const Gpr& d, const Gpr& s, const Gpr& t) { rt::paddub(c, d.r, s.r, t.r); }

    // `jal fn` at pc ($ra = pc + 8) through the callee's generated entry point
    void jal(u32 pc, rt::Fn fn) {
        rt::jal(c, pc);
        fn(c);
    }
    // `jr` through a jump table to an address that is not one of the function's own cases (never in retail data)
    void dispatch(const Gpr& r) { rt::lookup_func(w(r))(c); }
};

// The typed entry points' argument / result plumbing (game/include/p3fes/game/tartarus.h).
inline void set_args(EEContext& ctx, std::initializer_list<u64> args) {
    unsigned r = GPR_A0;
    for (u64 a : args) core::set_gpr64(ctx, r++, a);
}
inline u64 v0_of(const EEContext& ctx) { return core::gpr64(ctx, GPR_V0); }

}  // namespace p3fes::game::tartarus
