// The effect layers: the after effects (eff_after.c / eff_afpack.c, 0x1E8330-0x1EF000) and the effect manager's
// layer lists, keyframe tracks and mesh builders (0x320060-0x324158). fx_layers.h has the data flow and the layouts.
//
// Cycle model (ADR-0013): every charge() below is one `ctx.cycles += N` block of the recompiled body (a block runs
// from a label or the instruction after a branch's delay slot to the next branch and its delay slot, nops counted;
// a `jal` does not end a block, so a block that calls is charged in full before the call). backedge() sits where the
// recompiled body has a check point on a backward branch: the loops, and the backward jumps of the compiler's block
// layout. Loops whose test block comes first (`b test; body: ...; test: ...; bnez body`) are written as
// `for (;;) { test; if (!cond) break; backedge(); body; }`, loops tested at the bottom as `do ... while`.
//
// Registers: register-faithful. The kernel saves the whole register file at every check point that preempts, the
// callees' prologues spill registers, and callers read what a callee left behind (docs/PHASE5_AGENT_BRIEF.md, waves 6
// and 7). So each body runs on a Cpu view of the guest context: one variable per GPR (32-bit operations
// sign-extend into the 64-bit register; 64-bit writes keep bits 64..127 as the EE does; lq writes all 128 bits), the
// FPU, HI/LO and MMI operations through the runtime's own instruction semantics, the prologue spills and epilogue
// reloads on the guest stack, `$ra` set by every call as `jal` / `jalr` set it. Data flow and structure offsets are
// named in the comments and in fx_layers.h.
#include "p3fes/game/fx_layers.h"
#include "p3fes/game/hg_cpu.h"

#include "p3fes_recomp_rt.h"

#include <cstring>
#include <initializer_list>

namespace p3fes::recomp_gen {
// still-recompiled callees
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);   // K_Assert (`jr $ra` in retail)
void fn_strcmp_00524128(p3fes::EEContext&);
void fn_sub_4916D0_004916d0(p3fes::EEContext&);   // clump: for every atomic (callback, data); stops on 0
void fn_sub_48EE80_0048ee80(p3fes::EEContext&);   // material user data: count of named arrays
void fn_sub_48EED0_0048eed0(p3fes::EEContext&);   // material user data: array i (16-byte records)
void fn_name__C9type_info_0_0048ef10(p3fes::EEContext&);  // user-data array +0: its name
void fn_sub_48EF20_0048ef20(p3fes::EEContext&);   // user-data array +4: its format (3 = strings)
void fn_sub_48EF30_0048ef30(p3fes::EEContext&);   // user-data array +8: its element count
void fn_sub_48EF80_0048ef80(p3fes::EEContext&);   // user-data array: string element i
void fn_uttmxCreateRaster_0010e880(p3fes::EEContext&);
void fn_sub_4D0E40_004d0e40(p3fes::EEContext&);   // texture from a raster
void fn_sub_4D0F00_004d0f00(p3fes::EEContext&);   // texture destroy
void fn_sub_494D50_00494d50(p3fes::EEContext&);   // material: set texture
void fn_sub_350110_00350110(p3fes::EEContext&);   // effect program step (EPL band)
void fn_sub_347D60_00347d60(p3fes::EEContext&);   // effect objects step (EPL band)
void fn_sub_198560_00198560(p3fes::EEContext&);   // the field camera's RwCamera
void fn_sub_198580_00198580(p3fes::EEContext&);   // the field camera record
void fn_sub_4944B0_004944b0(p3fes::EEContext&);   // camera: set a 2-D vector parameter
void fn_sub_4CB7F0_004cb7f0(p3fes::EEContext&);   // RwFrameTransform(frame, matrix, combine)
void fn_sub_3230F0_003230f0(p3fes::EEContext&);   // effect mesh: create (vertices, triangles, flags) -- heap
void fn_sub_3234F0_003234f0(p3fes::EEContext&);   // effect mesh: create (flag 2 variant) -- heap
void fn_sub_323C20_00323c20(p3fes::EEContext&);   // effect mesh: create with materials -- heap
void fn_sub_493210_00493210(p3fes::EEContext&);   // RpGeometry triangle: set vertex indices
void fn_sub_493230_00493230(p3fes::EEContext&);   // RpGeometry triangle: set material
void fn_geometryLock_00493370(p3fes::EEContext&);   // RpGeometry lock
void fn_sub_4933D0_004933d0(p3fes::EEContext&);   // RpGeometry unlock
void fn_sub_3296A0_003296a0(p3fes::EEContext&);   // matrix from a rotation record (EPL band)
void fn_sub_4C33D0_004c33d0(p3fes::EEContext&);   // RwMatrixScale(matrix, vector, combine)
void fn_sub_4C35D0_004c35d0(p3fes::EEContext&);   // RwMatrixTranslate(matrix, vector, combine)
void fn_sub_4C2F30_004c2f30(p3fes::EEContext&);   // RwMatrixMultiply(dst, a, b)
void fn_sub_321360_00321360(p3fes::EEContext&);   // effect manager: draw one layer bank
void fn_sub_4C6AC0_004c6ac0(p3fes::EEContext&);   // RwV3dLength(v) -> $f0
void fn_sub_4C69F0_004c69f0(p3fes::EEContext&);   // RwV3dNormalize(dst, src)
void fn_sub_4C6BE0_004c6be0(p3fes::EEContext&);   // RwV3dTransformPoints(dst, src, matrix) (one point)
void fn_sub_4C38C0_004c38c0(p3fes::EEContext&);   // RwMatrixCreate -- heap
void fn_sub_4C3880_004c3880(p3fes::EEContext&);   // RwMatrixDestroy -- heap
void fn_sub_4C32A0_004c32a0(p3fes::EEContext&);   // RwMatrixInvert(dst, src)
void fn_sub_318D10_00318d10(p3fes::EEContext&);   // model: a bone's world matrix (model, bone, out)
void fn_sub_318B60_00318b60(p3fes::EEContext&);   // model: its root matrix
void fn_sub_493710_00493710(p3fes::EEContext&);   // RpGeometryCreate(vertices, triangles, flags) -- heap
void fn_sub_198590_00198590(p3fes::EEContext&);   // the field camera's RwCamera (current)
void fn_sub_1E7F90_001e7f90(p3fes::EEContext&);   // (queue_field) trail arc length at a sample
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_sub_1EE2E0_001ee2e0(p3fes::EEContext&);   // after effect: allocate -- heap
void fn_sub_1EEB90_001eeb90(p3fes::EEContext&);   // after effect: build its trails -- heap
void fn_sub_1EF340_001ef340(p3fes::EEContext&);   // after effect pack: release -- heap
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace fx {
namespace {

namespace core = ee::core;
namespace gen = ::p3fes::recomp_gen;

// --- R5900 integer results (32-bit operations sign-extend into the 64-bit register) ----------------------
constexpr u64 si(s32 v) { return static_cast<u64>(static_cast<s64>(v)); }  // `li` of a negative immediate
constexpr u64 addu(u64 a, u64 b) { return core::add32(a, b); }
constexpr u64 addiu(u64 a, s32 i) { return core::add32i(a, i); }
constexpr u64 subu(u64 a, u64 b) { return core::sub32(a, b); }
constexpr u64 negu(u64 a) { return core::sub32(0, a); }
constexpr u64 lui(u32 i) { return core::lui(i); }
constexpr u64 sll(u64 a, unsigned n) { return core::sll(a, n); }
constexpr u64 srl(u64 a, unsigned n) { return core::srl(a, n); }
constexpr u64 sra(u64 a, unsigned n) { return core::sra(a, n); }
constexpr u64 andi(u64 a, u32 i) { return core::andi(a, i); }
constexpr u64 ori(u64 a, u32 i) { return core::ori(a, i); }
constexpr u64 xori(u64 a, u32 i) { return core::xori(a, i); }
constexpr u64 and_(u64 a, u64 b) { return a & b; }
constexpr u64 or_(u64 a, u64 b) { return a | b; }
constexpr u64 nor(u64 a, u64 b) { return ~(a | b); }
constexpr u64 slt(u64 a, u64 b) { return core::slt(a, b); }
constexpr u64 sltu(u64 a, u64 b) { return core::sltu(a, b); }
constexpr u64 slti(u64 a, s32 i) { return core::slti(a, i); }
constexpr u64 sltiu(u64 a, s32 i) { return core::sltiu(a, i); }
constexpr bool bgtz(u64 a) { return core::bgtz(a); }
constexpr bool bgez(u64 a) { return core::bgez(a); }
constexpr bool bltz(u64 a) { return core::bltz(a); }
constexpr u32 w(u64 v) { return static_cast<u32>(v); }

// One GPR of the guest context. Reads go through a volatile lvalue, and so does virtual time below (the wave-10
// lesson of core3.cpp: MSVC /O2 was seen caching guest state in host registers across a small helper that charges).
struct Gpr {
    EEContext& c;
    const unsigned r;
    operator u64() const noexcept { return static_cast<const volatile u64&>(c.gpr[r].u64[0]); }
    Gpr& operator=(u64 v) noexcept {
        core::set_gpr64(c, r, v);
        return *this;
    }
    Gpr& operator=(const Gpr& o) noexcept { return *this = static_cast<u64>(o); }  // `move` (daddu rd, rs, $zero)
};

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
    Gpr t8{c, 24}, t9{c, 25}, gp{c, 28}, sp{c, 29}, s8{c, 30}, ra{c, 31};

    // virtual time (not noexcept: a check point's fatal event must unwind through the bodies)
    void enter(u64 n) {
        rt::check_events(c);
        charge(n);
    }
    void charge(u64 n) noexcept {
        volatile u64& t = c.cycles;
        t = t + n;
    }
    void backedge() { rt::check_events(c); }

    // loads / stores (32-bit effective addresses; lq / sq force a quadword boundary). The recompiled body stops (rt's
    // memory fault) at an unaligned or unmapped address where guest::load / guest::store would read 0 or drop the
    // write: such an access goes through the same rt operation first, with $zero as its register (the wave-10
    // lesson, as title.cpp), so both bodies stop alike.
    // `op`: which instruction faults (its name is part of the stop the runtime reports): 'u' unsigned / plain load or
    // store, 's' the sign-extending load (lh / lb), 'f' the FPU load / store (lwc1 / swc1 on $f0, which the fault
    // leaves unwritten).
    template <typename T>
    void same_fault(u32 va, bool write, char op = 'u') const {
        const bool aligned = (va & (sizeof(T) - 1u)) == 0;
        if (aligned && c.memory && c.memory->resolve(va, static_cast<u32>(sizeof(T)))) return;
        if (aligned && EEMemory::is_hw(va)) return;
        const s32 imm = static_cast<s32>(va);
        if constexpr (sizeof(T) == 1) write ? rt::sb(c, 0, 0, imm) : op == 's' ? rt::lb(c, 0, 0, imm) : rt::lbu(c, 0, 0, imm);
        else if constexpr (sizeof(T) == 2) write ? rt::sh(c, 0, 0, imm) : op == 's' ? rt::lh(c, 0, 0, imm) : rt::lhu(c, 0, 0, imm);
        else if constexpr (sizeof(T) == 4) {
            if (op == 'f') write ? rt::swc1(c, 0, 0, imm) : rt::lwc1(c, 0, 0, imm);
            else write ? rt::sw(c, 0, 0, imm) : rt::lw(c, 0, 0, imm);
        } else if constexpr (sizeof(T) == 8) write ? rt::sd(c, 0, 0, imm) : rt::ld(c, 0, 0, imm);
        else write ? rt::sq(c, 0, 0, imm) : rt::lq(c, 0, 0, imm);
    }
    template <typename T>
    T load(u64 a, char op = 'u') const {
        same_fault<T>(w(a), false, op);
        return guest::load<T>(c, w(a));
    }
    template <typename T>
    void store(u64 a, const T& v, char op = 'u') {
        same_fault<T>(w(a), true, op);
        guest::store<T>(c, w(a), v);
    }
    u64 lw(u64 a) const { return core::sext32(load<u32>(a)); }
    u64 lh(u64 a) const { return core::sext16(load<u16>(a, 's')); }
    u64 lhu(u64 a) const { return load<u16>(a); }
    u64 lb(u64 a) const { return core::sext8(load<u8>(a, 's')); }
    u64 lbu(u64 a) const { return load<u8>(a); }
    u64 ld(u64 a) const { return load<u64>(a); }
    void lq(Gpr& d, u64 a) { core::set_gpr128(c, d.r, load<u128>(w(a) & ~15u)); }
    void sw(u64 a, u64 v) { store<u32>(a, w(v)); }
    void sh(u64 a, u64 v) { store<u16>(a, static_cast<u16>(v)); }
    void sb(u64 a, u64 v) { store<u8>(a, static_cast<u8>(v)); }
    void sd(u64 a, u64 v) { store<u64>(a, v); }
    void sq(u64 a, const Gpr& v) { store<u128>(w(a) & ~15u, c.gpr[v.r]); }
    u64 gpa(s32 off) const noexcept { return addiu(gp, off); }  // a $gp-relative address

    // FPU (the runtime's instruction semantics: EE singles, ACC, FCR31 flags)
    void lwc1(unsigned f, u64 a) { c.fpr[f] = load<u32>(a, 'f'); }
    void swc1(unsigned f, u64 a) { store<u32>(a, c.fpr[f], 'f'); }
    void mtc1(const Gpr& g, unsigned f) noexcept { rt::mtc1(c, g.r, f); }
    void mfc1(Gpr& g, unsigned f) noexcept { rt::mfc1(c, g.r, f); }
    void mov_s(unsigned d, unsigned s) noexcept { rt::mov_s(c, d, s); }
    void neg_s(unsigned d, unsigned s) noexcept { rt::neg_s(c, d, s); }
    void abs_s(unsigned d, unsigned s) noexcept { rt::abs_s(c, d, s); }
    void cvt_s_w(unsigned d, unsigned s) noexcept { rt::cvt_s_w(c, d, s); }
    void cvt_w_s(unsigned d, unsigned s) noexcept { rt::cvt_w_s(c, d, s); }
    void add_s(unsigned d, unsigned s, unsigned t) noexcept { rt::add_s(c, d, s, t); }
    void sub_s(unsigned d, unsigned s, unsigned t) noexcept { rt::sub_s(c, d, s, t); }
    void mul_s(unsigned d, unsigned s, unsigned t) noexcept { rt::mul_s(c, d, s, t); }
    void div_s(unsigned d, unsigned s, unsigned t) noexcept { rt::div_s(c, d, s, t); }
    void sqrt_s(unsigned d, unsigned t) noexcept { rt::sqrt_s(c, d, t); }
    void adda_s(unsigned s, unsigned t) noexcept { rt::adda_s(c, s, t); }
    void mula_s(unsigned s, unsigned t) noexcept { rt::mula_s(c, s, t); }
    void madda_s(unsigned s, unsigned t) noexcept { rt::madda_s(c, s, t); }
    void msuba_s(unsigned s, unsigned t) noexcept { rt::msuba_s(c, s, t); }
    void madd_s(unsigned d, unsigned s, unsigned t) noexcept { rt::madd_s(c, d, s, t); }
    void msub_s(unsigned d, unsigned s, unsigned t) noexcept { rt::msub_s(c, d, s, t); }
    void c_eq_s(unsigned s, unsigned t) noexcept { rt::c_eq_s(c, s, t); }
    void c_lt_s(unsigned s, unsigned t) noexcept { rt::c_lt_s(c, s, t); }
    void c_le_s(unsigned s, unsigned t) noexcept { rt::c_le_s(c, s, t); }
    bool bc1t() const noexcept { return rt::cop1_cond(c); }

    // HI/LO (EE three-operand multiplies write rd too; `divu $zero, rs, rt`)
    void mult(Gpr& d, const Gpr& s, const Gpr& t) noexcept { rt::mult(c, d.r, s.r, t.r); }
    void mult1(Gpr& d, const Gpr& s, const Gpr& t) noexcept { rt::mult1(c, d.r, s.r, t.r); }
    void divu(const Gpr& s, const Gpr& t) noexcept { rt::divu(c, s.r, t.r); }
    void div(const Gpr& s, const Gpr& t) noexcept { rt::div(c, s.r, t.r); }
    void mfhi(Gpr& d) noexcept { rt::mfhi(c, d.r); }
    void mflo(Gpr& d) noexcept { rt::mflo(c, d.r); }

    // calls: `jal fn` / `jalr reg` at pc ($ra = pc + 8; the delay slot's instruction runs before the call)
    void jal(u32 pc, rt::Fn fn) {
        rt::jal(c, pc);
        fn(c);
    }
    void jalr(u32 pc, u64 target) {
        const u32 t = w(target);
        rt::jalr(c, GPR_RA, pc);
        rt::lookup_func(t)(c);
    }
    // a call to another body of this file, as `jal` (same as dispatching through its generated entry point)
    template <typename F>
    void jal_here(u32 pc, F body) {
        rt::jal(c, pc);
        (this->*body)();
    }

    // --- recurring FPU sequences of the after-effect bodies (each the exact compiled instruction order) ---
    // v = *src (three words through $f2, $f1, $f0: all loads, then all stores)
    void copy3(u64 dst, u64 src) {
        lwc1(F2, src + 0);
        lwc1(F1, src + 4);
        lwc1(F0, src + 8);
        swc1(F2, dst + 0);
        swc1(F1, dst + 4);
        swc1(F0, dst + 8);
    }
    // dst[k] = p[k] - q[k] for k = k0..2, per component through $f1 / $f0
    void diff3(u64 dst, u64 p, u64 q, unsigned k0 = 0) {
        for (unsigned k = k0; k < 3; ++k) {
            lwc1(F1, p + 4 * k);
            lwc1(F0, q + 4 * k);
            sub_s(F0, F1, F0);
            swc1(F0, dst + 4 * k);
        }
    }
    // dst[k] -= q[k], per component ($f1 = q[k], $f0 = dst[k])
    void subfrom3(u64 dst, u64 q) {
        for (unsigned k = 0; k < 3; ++k) {
            lwc1(F1, q + 4 * k);
            lwc1(F0, dst + 4 * k);
            sub_s(F0, F0, F1);
            swc1(F0, dst + 4 * k);
        }
    }
    // out = a x b with the compiled register plan ($f6 b.y, $f5 a.z, $f4 b.z, $f3 a.y, $f2 a.x, $f1 b.x, ACC)
    void cross(u64 out, u64 a, u64 b) {
        lwc1(F6, b + 4);
        lwc1(F5, a + 8);
        lwc1(F4, b + 8);
        lwc1(F3, a + 4);
        mula_s(F3, F4);
        msub_s(F0, F5, F6);
        swc1(F0, out + 0);
        lwc1(F2, a + 0);
        lwc1(F1, b + 0);
        mula_s(F5, F1);
        msub_s(F0, F2, F4);
        swc1(F0, out + 4);
        mula_s(F2, F6);
        msub_s(F0, F3, F1);
        swc1(F0, out + 8);
    }
    // one component of a cross product, the other plan: *dst = f1 * f0 - f3 * f2 (loads $f3, $f2, $f1, $f0)
    void cross_c(u64 dst, u64 o3, u64 o2, u64 o1, u64 o0) {
        lwc1(F3, o3);
        lwc1(F2, o2);
        lwc1(F1, o1);
        lwc1(F0, o0);
        mula_s(F1, F0);
        msub_s(F0, F3, F2);
        swc1(F0, dst);
    }
    // the compiler's unsigned-to-float idiom on $v1 (a `lbu`, so the halving path never runs): $f`fd`
    void ubyte_to_float(unsigned fd, unsigned ftmp) {
        if (!bltz(v1)) {
            charge(5);
            mtc1(v1, ftmp);
            cvt_s_w(fd, ftmp);
        } else {
            charge(7);
            a0 = srl(v1, 1);
            v1 = andi(v1, 0x1);
            a0 = or_(a0, v1);
            mtc1(a0, ftmp);
            cvt_s_w(fd, ftmp);
            add_s(fd, fd, fd);
        }
    }
    // the float-to-unsigned idiom after `c.le.s 2^31, $f`fval`` ($f`fthr` = 2^31): $a0 = (u8)value
    void float_to_ubyte(unsigned fval, unsigned fthr) {
        if (!bc1t()) {
            charge(6);
            cvt_w_s(fthr, fval);
            mfc1(a0, fthr);
            a0 = andi(a0, 0xff);
        } else {
            charge(6);
            sub_s(fthr, fval, fthr);
            cvt_w_s(fthr, fthr);
            mfc1(a0, fthr);
            v1 = lui(0x8000);
            a0 = or_(a0, v1);
            a0 = andi(a0, 0xff);
        }
    }
    // K_Assert(0x6844F8 "eff_after.c", line) as compiled: `lui a0; addiu a0; li a1; jal` in a 5-instruction block
    void assert_after(u32 pc, s32 line) {
        charge(5);
        a0 = lui(0x68);
        a0 = addiu(a0, 17656);
        a1 = static_cast<u64>(line);
        jal(pc, gen::fn_sub_19D3F0_0019d3f0);
    }

    // --- after effects (eff_after.c / eff_afpack.c) ---
    void sub_1E8330();
    void sub_1E8360();
    void ribbon_side(bool next, const u32 (&pcs)[4]);       // the shared body of sub_1E8360
    void sub_1E88F0();
    void segment_normal(bool next, const u32 (&pcs)[5]);    // the shared body of sub_1E88F0
    void sub_1ECD90();
    void sub_1ECEC0();
    void sub_1ED080();
    void sub_1ED0B0();
    void sub_1ED0D0();
    void sub_1ED0F0();
    void sub_1ED8A0();
    void sub_1ED9E0();
    void nullsub_10();
    void sub_1EEFC0();
    void sub_1EF000();
    void sub_1EBA50();
    void sub_1EBA80();
    void sub_1EDA90();
    void sub_1EDED0();
    void sub_1EE230();
    void sub_1EEE40();
    void sub_1EB920();
    void sub_1EDA00();
    void sub_1EE1D0();
    void sub_1EDBE0();
    void sub_1E8E80();
    void sub_1EBD80();
    void sub_1E9AF0();

    // --- the recurring steps of sub_1EBD80 (frame: sp+128 the term, sp+144 the sum) ---
    // term *= f; sum += term (both through $f3..$f0 as compiled)
    void scale_acc(unsigned f) {
        lwc1(F0, sp + 128);
        mul_s(F3, F0, f);
        swc1(F3, sp + 128);
        lwc1(F0, sp + 132);
        mul_s(F2, F0, f);
        swc1(F2, sp + 132);
        lwc1(F0, sp + 136);
        mul_s(F1, F0, f);
        swc1(F1, sp + 136);
        lwc1(F0, sp + 144);
        add_s(F0, F0, F3);
        swc1(F0, sp + 144);
        lwc1(F0, sp + 148);
        add_s(F0, F0, F2);
        swc1(F0, sp + 148);
        lwc1(F0, sp + 152);
        add_s(F0, F0, F1);
        swc1(F0, sp + 152);
    }
    // sum *= f
    void scale_sum(unsigned f) {
        for (unsigned k = 0; k < 3; ++k) {
            lwc1(F0, sp + 144 + 4 * k);
            mul_s(F0, F0, f);
            swc1(F0, sp + 144 + 4 * k);
        }
    }
    // term = norm(rail[$a0 / 12] - rail[$a2 / 12]) with $a1 the rail array (the address arithmetic as compiled)
    void rail_diff_tail(u32 pc_norm) {
        v0 = addu(a1, a0);
        lwc1(F1, v0 + 0);
        v0 = addu(a1, a2);
        lwc1(F0, v0 + 0);
        sub_s(F0, F1, F0);
        swc1(F0, sp + 128);
        for (unsigned k = 1; k < 3; ++k) {
            v1 = addiu(a1, static_cast<s32>(4 * k));
            v0 = addu(v1, a0);
            lwc1(F1, v0 + 0);
            v0 = addu(v1, a2);
            lwc1(F0, v0 + 0);
            sub_s(F0, F1, F0);
            swc1(F0, sp + 128 + 4 * k);
        }
        a0 = addiu(sp, 128);
        a1 = a0;
        jal(pc_norm, gen::fn_sub_4C69F0_004c69f0);
    }
    // term = the direction from sample s to the next newer one on the rail (0 for the newest); `at` = count < 2
    // from the caller's block (K_Assert line 337)
    void dir_newer(const Gpr& s, s32 rail, u32 pc_assert, u32 pc_norm) {
        if (at != 0) assert_after(pc_assert, 337);
        charge(2);
        if (s == 0) {
            charge(5);
            sw(sp + 128, zero);
            sw(sp + 132, zero);
            sw(sp + 136, zero);
            return;
        }
        charge(5);
        v1 = lw(s2 + 12);
        v0 = addiu(v1, -1);
        a0 = subu(v0, s);
        if (!bgez(a0)) {
            charge(2);
            v0 = lw(s2 + 8);
            a0 = addu(a0, v0);
        }
        charge(3);
        v1 = subu(v1, s);
        if (!bgez(v1)) {
            charge(2);
            v0 = lw(s2 + 8);
            v1 = addu(v1, v0);
        }
        charge(31);
        v0 = sll(a0, 1);
        v0 = addu(v0, a0);
        a2 = sll(v0, 2);
        a1 = lw(s2 + rail);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        a0 = sll(v0, 2);
        rail_diff_tail(pc_norm);
    }
    // term = the direction from the next older sample to sample s (0 for the oldest); K_Assert line 314
    void dir_older(const Gpr& s, s32 rail, u32 pc_assert, u32 pc_norm) {
        if (at != 0) assert_after(pc_assert, 314);
        charge(4);
        a0 = lw(s2 + 8);
        v0 = addiu(a0, -1);
        if (s == v0) {
            charge(5);
            sw(sp + 128, zero);
            sw(sp + 132, zero);
            sw(sp + 136, zero);
            return;
        }
        charge(5);
        v1 = lw(s2 + 12);
        v0 = addiu(v1, -1);
        a3 = subu(v0, s);
        if (!bgez(a3)) {
            charge(1);
            a3 = addu(a3, a0);
        }
        charge(5);
        v0 = si(-2);
        v0 = subu(v0, s);
        v1 = addu(v0, v1);
        if (!bgez(v1)) {
            charge(1);
            v1 = addu(v1, a0);
        }
        charge(31);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        a2 = sll(v0, 2);
        a1 = lw(s2 + rail);
        v0 = sll(a3, 1);
        v0 = addu(v0, a3);
        a0 = sll(v0, 2);
        rail_diff_tail(pc_norm);
    }
    // the slot of sample $s1 into $v1 (the [36] blocks end with it)
    void slot_s1_v1() {
        v0 = lw(s2 + 12);
        v0 = addiu(v0, -1);
        v1 = subu(v0, s1);
    }

    // --- the recurring steps of sub_1E9AF0 (frame: sp+224 P0, +236 P1, +248 P2, +260 P3 of the segment's cubic,
    // +408 the segment index and +412 t from sub_1E7F90) ---
    // dst[k] = p[k] + q[k] (through $f`fp` / $f0)
    void sum3(u64 dst, u64 p, u64 q, unsigned fp) {
        for (unsigned k = 0; k < 3; ++k) {
            lwc1(fp, p + 4 * k);
            lwc1(F0, q + 4 * k);
            add_s(F0, fp, F0);
            swc1(F0, dst + 4 * k);
        }
    }
    // dst[k] += q[k] (through $f2 / $f0)
    void addto3(u64 dst, u64 q) {
        for (unsigned k = 0; k < 3; ++k) {
            lwc1(F2, q + 4 * k);
            lwc1(F0, dst + 4 * k);
            add_s(F0, F0, F2);
            swc1(F0, dst + 4 * k);
        }
    }
    // dst[k] *= f
    void scale3(u64 dst, unsigned f) {
        for (unsigned k = 0; k < 3; ++k) {
            lwc1(F0, dst + 4 * k);
            mul_s(F0, F0, f);
            swc1(F0, dst + 4 * k);
        }
    }
    // a ribbon's middle row: v = (v[-24] + v[-12] + v[+12] + v[+24]) * $f1 (0.25)
    void smooth(u64 p) {
        sum3(p, p - 24, p - 12, F2);
        addto3(p, p + 12);
        addto3(p, p + 24);
        scale3(p, F1);
    }
    // The control points of segment $a0 (the new segment index; `cache` takes it): P0 = rail[a], P1 = P0 - start
    // handle (+24 of the handle record), P2 = rail[b] + end handle (+28), P3 = rail[b], with a / b the slots of the
    // segment's two samples. The rail array is (+16 of) the frame's spilled record (shape 0) or of `rail_rec`.
    void load_segment(Gpr& cache, bool rail_on_frame, const Gpr& rail_rec, const Gpr& handles) {
        charge(6);
        cache = a0;
        v0 = lw(s5 + 12);
        v1 = addiu(v0, -1);
        a3 = subu(v1, a0);
        if (!bgez(a3)) {
            charge(2);
            v0 = lw(s5 + 8);
            a3 = addu(a3, v0);
        }
        charge(4);
        v0 = addiu(a0, 1);
        a2 = subu(v1, v0);
        if (!bgez(a2)) {
            charge(2);
            v0 = lw(s5 + 8);
            a2 = addu(a2, v0);
        }
        if (rail_on_frame) {
            charge(50);
            lq(v0, sp + 192);
            a1 = lw(v0 + 16);
        } else {
            charge(49);
            a1 = lw(rail_rec + 16);
        }
        v0 = sll(a3, 1);
        v0 = addu(v0, a3);
        a0 = sll(v0, 2);
        v1 = addu(a1, a0);
        copy3(sp + 224, v1);
        v0 = lw(handles + 24);
        v0 = addu(v0, a0);
        diff3(sp + 236, v1, v0);
        v0 = lw(handles + 28);
        v1 = addu(v0, a0);
        v0 = sll(a2, 1);
        v0 = addu(v0, a2);
        v0 = sll(v0, 2);
        v0 = addu(a1, v0);
        sum3(sp + 248, v0, v1, F1);
        copy3(sp + 260, v0);
    }
    // the cubic Bezier at t of the frame's P0..P3, three components into out (u = 1 - t; ACC chain); `t`, `u`
    // already loaded; the register plan as compiled for each caller; `reload` re-reads t per component
    void bezier3(u64 out, unsigned t, unsigned u, unsigned q3, unsigned q2, unsigned q0, unsigned w, bool reload) {
        lwc1(F0, sp + 260);
        mul_s(F0, F0, t);
        mul_s(q3, t, F0);
        v0 = lui(0x4040);
        mtc1(v0, F0);  // 3.0
        for (unsigned k = 0; k < 3; ++k) {
            if (k > 0) {
                if (reload) lwc1(t, sp + 412);
                lwc1(w, sp + 260 + 4 * k);
                mul_s(w, w, t);
                mul_s(q3, t, w);  // P3 t^2 (then * t below)
            }
            lwc1(w, sp + 248 + 4 * k);
            mul_s(w, F0, w);
            mul_s(w, w, t);
            mul_s(q2, t, w);  // 3 P2 t^2
            lwc1(w, sp + 224 + 4 * k);
            mul_s(w, w, u);
            mul_s(q0, u, w);  // P0 u^2
            lwc1(w, sp + 236 + 4 * k);
            const unsigned r = k < 2 ? w : F0;
            mul_s(r, F0, w);
            mul_s(r, r, t);
            mul_s(r, u, r);  // 3 P1 t u
            mula_s(u, r);
            madda_s(u, q0);
            madda_s(u, q2);
            madd_s(r, t, q3);
            swc1(r, out + 4 * k);
        }
    }
    // the camera-facing side of a ribbon point P: e = norm(camera - P) ($s1 the camera position; P.y / P.z kept in
    // $f`fy` / $f`fz`), d = norm(prev - P) (or P - prev when `reverse`), n = norm(e x d); $f1 = |e . d| (sp+392..)
    void billboard_dir(u64 p, u64 prev, unsigned fy, unsigned fz, bool reverse, u32 pc1, u32 pc2, u32 pc3) {
        lwc1(F1, s1 + 0);
        lwc1(F0, p + 0);
        sub_s(F0, F1, F0);
        swc1(F0, sp + 392);
        lwc1(fy, p + 4);
        lwc1(F0, s1 + 4);
        sub_s(F0, F0, fy);
        swc1(F0, sp + 396);
        lwc1(fz, p + 8);
        lwc1(F0, s1 + 8);
        sub_s(F0, F0, fz);
        swc1(F0, sp + 400);
        a0 = addiu(sp, 392);
        a1 = a0;
        jal(pc1, gen::fn_sub_4C69F0_004c69f0);
        if (!reverse) {
            lwc1(F1, prev + 0);
            lwc1(F0, p + 0);
            sub_s(F0, F1, F0);
            swc1(F0, sp + 344);
            lwc1(F0, prev + 4);
            sub_s(F0, F0, fy);
            swc1(F0, sp + 348);
            lwc1(F0, prev + 8);
            sub_s(F0, F0, fz);
            swc1(F0, sp + 352);
        } else {
            lwc1(F1, p + 0);
            lwc1(F0, prev + 0);
            sub_s(F0, F1, F0);
            swc1(F0, sp + 344);
            lwc1(F0, prev + 4);
            sub_s(F0, fy, F0);
            swc1(F0, sp + 348);
            lwc1(F0, prev + 8);
            sub_s(F0, fz, F0);
            swc1(F0, sp + 352);
        }
        a0 = addiu(sp, 344);
        a1 = a0;
        jal(pc2, gen::fn_sub_4C69F0_004c69f0);
        cross(sp + 328, sp + 392, sp + 344);
        a0 = addiu(sp, 328);
        a1 = a0;
        jal(pc3, gen::fn_sub_4C69F0_004c69f0);
        lwc1(F5, sp + 400);
        lwc1(F4, sp + 352);
        lwc1(F3, sp + 392);
        lwc1(F2, sp + 344);
        lwc1(F1, sp + 396);
        lwc1(F0, sp + 348);
        mula_s(F1, F0);
        mtc1(zero, F0);
        madda_s(F3, F2);
        madd_s(F1, F5, F4);
        c_lt_s(F1, F0);
        if (bc1t()) {
            charge(4);
            v0 = lui(0xbf80);
            mtc1(v0, F0);  // -1.0
            mul_s(F1, F1, F0);
        }
    }
    // the two edge vertices of a ribbon point: n *= half width ($f24) * (1 - |e . d|^3); out = P + n, out + 12 = P - n
    void billboard_emit(u64 p, u64 out) {
        mul_s(F0, F1, F1);
        mul_s(F1, F1, F0);
        v0 = lui(0x3f80);
        mtc1(v0, F0);
        sub_s(F0, F0, F1);
        mul_s(F2, F24, F0);
        lwc1(F0, sp + 328);
        mul_s(F1, F0, F2);
        swc1(F1, sp + 328);
        lwc1(F0, sp + 332);
        mul_s(F0, F0, F2);
        swc1(F0, sp + 332);
        lwc1(F0, sp + 336);
        mul_s(F0, F0, F2);
        swc1(F0, sp + 336);
        lwc1(F3, p + 0);
        add_s(F0, F3, F1);
        swc1(F0, out + 0);
        lwc1(F2, p + 4);
        lwc1(F0, sp + 332);
        add_s(F0, F2, F0);
        swc1(F0, out + 4);
        lwc1(F1, p + 8);
        lwc1(F0, sp + 336);
        add_s(F0, F1, F0);
        swc1(F0, out + 8);
        lwc1(F0, sp + 328);
        sub_s(F0, F3, F0);
        swc1(F0, out + 12);
        lwc1(F0, sp + 332);
        sub_s(F0, F2, F0);
        swc1(F0, out + 16);
        lwc1(F0, sp + 336);
        sub_s(F0, F1, F0);
        swc1(F0, out + 20);
    }
    // the parts of sub_1E9AF0
    void af_colours();
    void af_short();
    void af_shape0();
    void af_shape1();
    void af_shape2();

    // unaligned word loads (lwr / lwl on $v1, the runtime's semantics)
    void lwr_v1(const Gpr& base, s32 off) { rt::lwr(c, v1.r, base.r, off); }
    void lwl_v1(const Gpr& base, s32 off) { rt::lwl(c, v1.r, base.r, off); }
    // the script's 32-bit operand at $s1 + 2 to sp+76 (two halves when it is not word aligned)
    void read_operand() {
        charge(5);
        v1 = addiu(s1, 2);
        v1 = srl(v1, 1);
        v1 = andi(v1, 0x1);
        if (v1 != 0) {
            charge(7);
            a0 = addiu(sp, 76);
            v1 = lhu(s1 + 2);
            sh(a0 + 0, v1);
            v1 = lhu(s1 + 4);
            sh(a0 + 2, v1);
        } else {
            charge(3);
            lwr_v1(s1, 2);
            lwl_v1(s1, 5);
            sw(sp + 76, v1);
        }
    }

    // --- effect manager: the per-effect keyframe tracks (table 0x69BB10) and the layer lists ---
    void sub_320060();
    void nullsub_106();
    void sub_320080();
    void sub_320380();
    void sub_3204A0();
    void sub_320640();
    void sub_320770();
    void sub_320810();
    void sub_320BA0();
    void sub_320CF0();
    void sub_320DA0();
    void sub_320DE0();
    void sub_320F70();
    void sub_321050();
    void sub_321070();
    void sub_3210A0();
    void sub_3210C0();
    void sub_321120();
    void sub_321130();
    void link_bank(u32 table, s32 link, bool at_least_5);  // sub_321140 .. sub_3212E0
    void sub_321320();
    void effMng_UpdateEffectProgramTask();
    void layer_task(u32 pc, u64 layer, bool zero_v0);       // effMng_UpdateEffect3dTask / effMng_UpdateEffect2dTask / sub_321FE0
    void sub_321F10();
    void sub_3226B0();
    void sub_322AB0();
    void sub_322D10();
    void sub_322D40();
    void sub_322DA0();
    void sub_322FB0();
    void sub_322FD0();
    void grid_mesh(bool closed);                            // sub_323240 / sub_3233A0
    void sub_323640();
    void sub_323860();
    void sub_323880();
    void sub_3238D0();
    void sub_323920();
    void sub_323A30();
    void sub_323B90();
    void sub_323BF0();
    void band_mesh(bool closed);                            // sub_323E10 / sub_323FB0
};

// =========================================================================================================
// After effects: the trail ring and its geometry helpers (eff_after.c)
// =========================================================================================================

// sub_1E8330 [ring slot of the k-th newest sample]: ring {+8 capacity, +12 head}: (head - 1 - k), wrapped once.
void Cpu::sub_1E8330() {
    enter(5);
    v0 = lw(a0 + 12);
    v0 = addiu(v0, -1);
    v0 = subu(v0, a1);
    if (!bgez(v0)) {
        charge(2);
        v1 = lw(a0 + 8);
        v0 = addu(v0, v1);
    }
    charge(2);
}

// The body shared by both halves of sub_1E88F0, after the slot pointers: $s3 / $s2 the sample's two rails (ring +16
// / +20 at its slot), $s4 / $s1 the neighbour's. edge = |s3 - s4|, rail = |s2 - s1|; u = norm(s2 - s3), w = norm(s1
// - s4); n = norm(u x w) (the newest sample: w x u) -> out; then out = u x n when the edge is longer than the rail,
// else n x u (all with RwV3dLength sub_4C6AC0 / RwV3dNormalize sub_4C69F0 on the frame at sp+112..152).
void Cpu::segment_normal(bool next, const u32 (&pcs)[5]) {
    diff3(sp + 144, s3, s4);
    a0 = addiu(sp, 144);
    jal(pcs[0], gen::fn_sub_4C6AC0_004c6ac0);
    mov_s(F21, F0);
    diff3(sp + 144, s2, s1);
    a0 = addiu(sp, 144);
    jal(pcs[1], gen::fn_sub_4C6AC0_004c6ac0);
    mov_s(F20, F0);
    diff3(sp + 144, s2, s3);
    a0 = addiu(sp, 144);
    a1 = a0;
    jal(pcs[2], gen::fn_sub_4C69F0_004c69f0);
    diff3(sp + 128, s1, s4);
    a0 = addiu(sp, 128);
    a1 = a0;
    jal(pcs[3], gen::fn_sub_4C69F0_004c69f0);
    if (next)
        cross(sp + 112, sp + 128, sp + 144);
    else
        cross(sp + 112, sp + 144, sp + 128);
    a0 = addiu(sp, 112);
    a1 = a0;
    jal(pcs[4], gen::fn_sub_4C69F0_004c69f0);
    copy3(s0, sp + 112);
    c_le_s(F21, F20);
    if (!bc1t()) {
        charge(23);
        cross_c(s0 + 0, sp + 152, sp + 116, sp + 148, sp + 120);
        cross_c(s0 + 4, sp + 144, sp + 120, sp + 152, sp + 112);
        cross_c(s0 + 8, sp + 148, sp + 112, sp + 144, sp + 116);
    } else {
        charge(next ? 21 : 23);
        cross_c(s0 + 0, sp + 120, sp + 148, sp + 116, sp + 152);
        cross_c(s0 + 4, sp + 112, sp + 152, sp + 120, sp + 144);
        cross_c(s0 + 8, sp + 116, sp + 144, sp + 112, sp + 148);
    }
}

// sub_1E88F0 [the ribbon's side vector at a sample]: $a0 the ring (+8 capacity, at least 2 (K_Assert line 250),
// +12 head, +16 / +20 the two rails of 12-byte points), $a1 the sample (0 = newest), $a2 the output. The neighbour
// is the next older sample, or the next newer one for the oldest (capacity - 1).
void Cpu::sub_1E88F0() {
    enter(16);
    sp = addiu(sp, -160);
    sd(sp + 96, ra);
    sq(sp + 80, s4);
    sq(sp + 64, s3);
    sq(sp + 48, s2);
    sq(sp + 32, s1);
    sq(sp + 16, s0);
    swc1(F21, sp + 4);
    swc1(F20, sp + 0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    v0 = lw(a0 + 8);
    at = slti(v0, 2);
    if (at != 0) assert_after(0x1e893cu, 250);
    charge(4);
    v0 = lw(s2 + 8);
    v1 = addiu(v0, -1);
    if (s1 == v1) {  // the oldest sample: the neighbour is the newer one
        charge(5);
        a2 = lw(s2 + 12);
        v1 = addiu(a2, -1);
        a0 = subu(v1, s1);
        if (!bgez(a0)) {
            charge(1);
            a0 = addu(a0, v0);
        }
        charge(10);
        v1 = sll(a0, 1);
        v1 = addu(v1, a0);
        a1 = sll(v1, 2);
        a0 = lw(s2 + 16);
        s3 = addu(a0, a1);
        v1 = lw(s2 + 20);
        s2 = addu(v1, a1);
        a1 = subu(a2, s1);
        if (!bgez(a1)) {
            charge(1);
            a1 = addu(a1, v0);
        }
        charge(97);
        v0 = sll(a1, 1);
        v0 = addu(v0, a1);
        v0 = sll(v0, 2);
        s4 = addu(a0, v0);
        s1 = addu(v1, v0);
        segment_normal(false, {0x1e89e0u, 0x1e8a20u, 0x1e8a64u, 0x1e8aa4u, 0x1e8af0u});
    } else {
        charge(5);
        a2 = lw(s2 + 12);
        v1 = addiu(a2, -1);
        a0 = subu(v1, s1);
        if (!bgez(a0)) {
            charge(1);
            a0 = addu(a0, v0);
        }
        charge(12);
        v1 = sll(a0, 1);
        v1 = addu(v1, a0);
        v1 = sll(v1, 2);
        a1 = lw(s2 + 16);
        s3 = addu(a1, v1);
        a0 = lw(s2 + 20);
        s2 = addu(a0, v1);
        v1 = si(-2);
        v1 = subu(v1, s1);
        v1 = addu(v1, a2);
        if (!bgez(v1)) {
            charge(1);
            v1 = addu(v1, v0);
        }
        charge(97);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        s4 = addu(a1, v0);
        s1 = addu(a0, v0);
        segment_normal(true, {0x1e8c68u, 0x1e8ca8u, 0x1e8cecu, 0x1e8d2cu, 0x1e8d78u});
    }
    charge(11);
    ra = ld(sp + 96);
    lq(s4, sp + 80);
    lq(s3, sp + 64);
    lq(s2, sp + 48);
    lq(s1, sp + 32);
    lq(s0, sp + 16);
    lwc1(F21, sp + 4);
    lwc1(F20, sp + 0);
    sp = addiu(sp, 160);
}

// The body shared by both halves of sub_1E8360, after the two slot indices ($s5 the sample's, $s0 the neighbour's):
// the side vector (sub_1E88F0) at sp+128; the four rail points of the two samples at sp+112..124 (rail $a2 & 1 and
// the other one); u = norm(other rail - this rail) at the sample, w = norm(this rail of the neighbour - this rail);
// n = norm(u x w); for side 1 / 0 the out-of-plane vector (w x n / n x u, swapped for the newest sample), scaled by
// its dot product with the side vector and normalised into $s1 (side 2.. leave the frame's sp+144 as it is).
void Cpu::ribbon_side(bool next, const u32 (&pcs)[4]) {
    a0 = s4;
    a1 = s3;
    a2 = addiu(sp, 128);
    jal_here(pcs[0], &Cpu::sub_1E88F0);
    v0 = sll(s5, 1);
    v0 = addu(v0, s5);
    v1 = sll(v0, 2);
    t0 = andi(s2, 0x1);  // this rail
    s5 = sll(t0, 2);
    v0 = addu(s5, s4);
    a3 = lw(v0 + 16);
    a2 = addu(a3, v1);
    sw(sp + 112, a2);
    v0 = addiu(s2, 1);
    s3 = andi(v0, 0x1);  // the other rail
    a1 = sll(s3, 2);
    v0 = addu(a1, s4);
    a0 = lw(v0 + 16);
    v0 = addu(a0, v1);
    sw(sp + 116, v0);
    v0 = sll(s0, 1);
    v0 = addu(v0, s0);
    v1 = sll(v0, 2);
    v0 = addu(a3, v1);
    sw(sp + 120, v0);
    v0 = addu(a0, v1);
    sw(sp + 124, v0);
    v0 = sll(t0, 3);
    v0 = addu(v0, sp);
    v0 = addiu(v0, 112);
    v0 = addu(v0, a1);
    v0 = lw(v0 + 0);
    diff3(sp + 192, v0, a2);
    a0 = addiu(sp, 192);
    a1 = a0;
    jal(pcs[1], gen::fn_sub_4C69F0_004c69f0);
    v0 = sll(s3, 3);
    v0 = addu(v0, sp);
    v0 = addiu(v0, 112);
    v0 = addu(v0, s5);
    v1 = lw(v0 + 0);
    lwc1(F1, v1 + 0);
    v0 = lw(sp + 112);
    lwc1(F0, v0 + 0);
    sub_s(F0, F1, F0);
    swc1(F0, sp + 176);
    diff3(sp + 176, v1, v0, 1);
    a0 = addiu(sp, 176);
    a1 = a0;
    jal(pcs[2], gen::fn_sub_4C69F0_004c69f0);
    cross(sp + 160, sp + 192, sp + 176);
    a0 = addiu(sp, 160);
    a1 = a0;
    jal(pcs[3], gen::fn_sub_4C69F0_004c69f0);
    v0 = 1;
    if (s2 == v0) {
        charge(15);
        cross(sp + 144, sp + (next ? 160 : 176), sp + (next ? 176 : 160));
    } else {
        charge(2);
        if (s2 == 0) {
            charge(17);
            cross(sp + 144, sp + (next ? 192 : 160), sp + (next ? 160 : 192));
        } else {
            charge(2);
        }
    }
    charge(next ? 19 : 21);
    lwc1(F5, sp + 152);
    lwc1(F4, sp + 136);
    lwc1(F3, sp + 144);
    lwc1(F1, sp + 128);
    lwc1(F2, sp + 148);
    lwc1(F0, sp + 132);
    mula_s(F2, F0);
    madda_s(F3, F1);
    madd_s(F1, F5, F4);  // dot(v, side)
    mul_s(F0, F3, F1);
    swc1(F0, sp + 144);
    mul_s(F0, F2, F1);
    swc1(F0, sp + 148);
    mul_s(F0, F5, F1);
    swc1(F0, sp + 152);
    a0 = s1;
    a1 = addiu(sp, 144);
    jal(next ? 0x1e88bcu : 0x1e8634u, gen::fn_sub_4C69F0_004c69f0);
}

// sub_1E8360 [the ribbon's out-of-plane vector at a sample]: $a0 the ring (capacity >= 2, K_Assert line 173), $a1
// the sample, $a2 the rail / side selector, $a3 the output.
void Cpu::sub_1E8360() {
    enter(16);
    sp = addiu(sp, -208);
    sd(sp + 96, ra);
    sq(sp + 80, s5);
    sq(sp + 64, s4);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp + 0, s0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    s1 = a3;
    v0 = lw(a0 + 8);
    at = slti(v0, 2);
    if (at != 0) assert_after(0x1e83acu, 173);
    charge(4);
    a0 = lw(s4 + 8);
    v0 = addiu(a0, -1);
    if (s3 == v0) {
        charge(5);
        v1 = lw(s4 + 12);
        v0 = addiu(v1, -1);
        s5 = subu(v0, s3);
        if (!bgez(s5)) {
            charge(1);
            s5 = addu(s5, a0);
        }
        charge(3);
        s0 = subu(v1, s3);
        if (!bgez(s0)) {
            charge(1);
            s0 = addu(s0, a0);
        }
        charge(93);
        ribbon_side(false, {0x1e83f8u, 0x1e84a8u, 0x1e8500u, 0x1e854cu});
    } else {
        charge(5);
        v1 = lw(s4 + 12);
        v0 = addiu(v1, -1);
        s5 = subu(v0, s3);
        if (!bgez(s5)) {
            charge(1);
            s5 = addu(s5, a0);
        }
        charge(5);
        v0 = si(-2);
        v0 = subu(v0, s3);
        s0 = addu(v0, v1);
        if (!bgez(s0)) {
            charge(1);
            s0 = addu(s0, a0);
        }
        charge(93);
        ribbon_side(true, {0x1e8680u, 0x1e8730u, 0x1e8788u, 0x1e87d4u});
    }
    charge(10);
    ra = ld(sp + 96);
    lq(s5, sp + 80);
    lq(s4, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp + 0);
    sp = addiu(sp, 208);
}

// sub_1ECD90 [segment length on a rail]: $a0 the ring, $a1 the sample (not the oldest: K_Assert line 1787), $a2 the
// rail (+16 + 4 * rail): |p[sample + 1] - p[sample]| (RwV3dLength on the frame at sp+64) in $f0.
void Cpu::sub_1ECD90() {
    enter(12);
    sp = addiu(sp, -80);
    sd(sp + 48, ra);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp + 0, s0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    v0 = lw(a0 + 8);
    v0 = addiu(v0, -1);
    if (s1 == v0) assert_after(0x1ecdccu, 1787);
    charge(6);
    v0 = si(-2);
    v1 = subu(v0, s1);
    v0 = lw(s2 + 12);
    v1 = addu(v1, v0);
    if (!bgez(v1)) {
        charge(2);
        v0 = lw(s2 + 8);
        v1 = addu(v1, v0);
    }
    charge(18);
    v0 = sll(s0, 2);
    a0 = addu(v0, s2);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v1 = sll(v0, 2);
    v0 = lw(a0 + 16);
    v0 = addu(v0, v1);
    copy3(sp + 64, v0);
    v0 = lw(s2 + 12);
    v0 = addiu(v0, -1);
    v1 = subu(v0, s1);
    if (!bgez(v1)) {
        charge(2);
        v0 = lw(s2 + 8);
        v1 = addu(v1, v0);
    }
    charge(29);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v1 = sll(v0, 2);
    v0 = sll(s0, 2);
    v0 = addu(v0, s2);
    v0 = lw(v0 + 16);
    v0 = addu(v0, v1);
    subfrom3(sp + 64, v0);
    a0 = addiu(sp, 64);
    jal(0x1ece94u, gen::fn_sub_4C6AC0_004c6ac0);
    ra = ld(sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp + 0);
    sp = addiu(sp, 80);
}

// sub_1ECEC0 [bend at a sample]: $a0 the ring, $a1 the sample (not the oldest: K_Assert line 1804). The rail-to-rail
// directions u = norm(r1 - r0) at the sample and at the next older one; $f0 = (1 - u . u') / 2.
void Cpu::sub_1ECEC0() {
    enter(10);
    sp = addiu(sp, -80);
    sd(sp + 32, ra);
    sq(sp + 16, s1);
    sq(sp + 0, s0);
    s1 = a0;
    s0 = a1;
    v0 = lw(a0 + 8);
    v0 = addiu(v0, -1);
    if (s0 == v0) assert_after(0x1ecef4u, 1804);
    charge(5);
    v0 = lw(s1 + 12);
    v0 = addiu(v0, -1);
    v1 = subu(v0, s0);
    if (!bgez(v1)) {
        charge(2);
        v0 = lw(s1 + 8);
        v1 = addu(v1, v0);
    }
    charge(35);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v1 = sll(v0, 2);
    v0 = lw(s1 + 20);
    v0 = addu(v0, v1);
    a0 = addiu(sp, 64);
    copy3(sp + 64, v0);
    v0 = lw(s1 + 16);
    v0 = addu(v0, v1);
    subfrom3(sp + 64, v0);
    a1 = a0;
    jal(0x1ecf84u, gen::fn_sub_4C69F0_004c69f0);
    v0 = si(-2);
    v1 = subu(v0, s0);
    v0 = lw(s1 + 12);
    v1 = addu(v1, v0);
    if (!bgez(v1)) {
        charge(2);
        v0 = lw(s1 + 8);
        v1 = addu(v1, v0);
    }
    charge(52);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v1 = sll(v0, 2);
    v0 = lw(s1 + 20);
    v0 = addu(v0, v1);
    a0 = addiu(sp, 48);
    copy3(sp + 48, v0);
    v0 = lw(s1 + 16);
    v0 = addu(v0, v1);
    subfrom3(sp + 48, v0);
    a1 = a0;
    jal(0x1ed018u, gen::fn_sub_4C69F0_004c69f0);
    lwc1(F5, sp + 72);
    lwc1(F4, sp + 56);
    lwc1(F3, sp + 64);
    lwc1(F2, sp + 48);
    lwc1(F1, sp + 68);
    lwc1(F0, sp + 52);
    mula_s(F1, F0);
    madda_s(F3, F2);
    madd_s(F1, F5, F4);
    v0 = lui(0x3f80);
    mtc1(v0, F0);
    sub_s(F1, F0, F1);
    v0 = lui(0x4000);
    mtc1(v0, F0);
    div_s(F0, F1, F0);
    ra = ld(sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp + 0);
    sp = addiu(sp, 80);
}

// sub_1ED080 [start the fade]: +56 = 0, +64 = +60 (the clock), +68 = $f12 (the duration), flag 1 on.
void Cpu::sub_1ED080() {
    enter(9);
    sw(a0 + 56, zero);
    lwc1(F0, a0 + 60);
    swc1(F0, a0 + 64);
    swc1(F12, a0 + 68);
    v1 = lw(a0 + 4);
    v1 = ori(v1, 0x1);
    sw(a0 + 4, v1);
}

// sub_1ED0B0 [reset the timing record]: +4 flags, +60 clock, +8, +12 = 0.
void Cpu::sub_1ED0B0() {
    enter(6);
    sw(a0 + 4, zero);
    sw(a0 + 60, zero);
    sw(a0 + 8, zero);
    sw(a0 + 12, zero);
}

// sub_1ED0D0 [advance the clock]: +60 += *$a1.
void Cpu::sub_1ED0D0() {
    enter(6);
    lwc1(F1, a0 + 60);
    lwc1(F0, a1 + 0);
    add_s(F0, F1, F0);
    swc1(F0, a0 + 60);
}

// sub_1ED0F0 [the colour of a key pair at t]: $a0 the timing record (+0 -> +4 the 8-byte key list, +4 flags, +60
// clock, +64 fade start, +68 fade length), $a1 the key, $a2 the output RGBA, $f12 = t. The two colours at key +8 /
// +12 (pointers kept in the zeroed 8-byte frame slot sp+8); per channel c = a * (1 - t) + b * t (ACC chain), times
// the fade factor (flag 1: clamp(1 - (clock - start) / length, 0..), zero length: 0 before the start, 1 after;
// a negative length keeps the caller's $f0), converted with the compiler's unsigned idioms.
void Cpu::sub_1ED0F0() {
    enter(5);
    sp = addiu(sp, -16);
    a3 = addiu(sp, 8);
    v1 = 8;
    if (a3 != 0) {
        do {
            charge(7);
            sb(a3 + 0, zero);
            a3 = addiu(a3, 1);
            v1 = addiu(v1, -1);
            if (v1 == 0) break;
            backedge();
        } while (true);
    }
    charge(16);
    a1 = sll(a1, 3);
    v1 = lw(a0 + 0);
    v1 = lw(v1 + 4);
    a1 = addu(v1, a1);
    v1 = addiu(a1, 8);
    sw(sp + 8, v1);  // colour a
    a1 = addiu(a1, 12);
    sw(sp + 12, a1);  // colour b
    v1 = lui(0x3f80);
    mtc1(v1, F5);
    sub_s(F1, F5, F12);  // 1 - t
    v1 = lw(a0 + 4);
    v1 = andi(v1, 0x1);
    if (v1 != 0) {
        charge(6);
        lwc1(F4, a0 + 68);
        mtc1(zero, F3);
        c_le_s(F4, F3);
        if (!bc1t()) {
            charge(9);
            lwc1(F2, a0 + 60);
            lwc1(F0, a0 + 64);
            sub_s(F0, F2, F0);
            div_s(F0, F0, F4);
            sub_s(F0, F5, F0);
            c_lt_s(F0, F3);
            if (bc1t()) {
                charge(3);
                mov_s(F0, F3);
            }
        } else {
            charge(3);
            c_eq_s(F3, F4);
            if (bc1t()) {
                charge(5);
                lwc1(F2, a0 + 60);
                lwc1(F0, a0 + 64);
                c_lt_s(F2, F0);
                if (!bc1t()) {
                    charge(3);
                    mov_s(F0, F3);
                } else {
                    charge(1);
                    mov_s(F0, F5);
                }
            }
        }
        charge(4);
        v1 = lw(sp + 12);
        v1 = lbu(v1 + 0);
        for (unsigned k = 0; k < 4; ++k) {
            ubyte_to_float(F3, F2);  // b
            charge(4);
            v1 = lw(sp + 8);
            v1 = lbu(v1 + k);
            ubyte_to_float(F2, F2);  // a
            charge(9);
            mula_s(F1, F2);
            if (k < 3) {
                madd_s(F2, F12, F3);
                mul_s(F3, F0, F2);
                v1 = lui(0x4f00);
                mtc1(v1, F2);  // 2^31
                c_le_s(F2, F3);
                float_to_ubyte(F3, F2);
                charge(5);
                sb(a2 + k, a0);
                v1 = lw(sp + 12);
                v1 = lbu(v1 + k + 1);
            } else {
                madd_s(F1, F12, F3);
                mul_s(F1, F0, F1);
                v1 = lui(0x4f00);
                mtc1(v1, F0);
                c_le_s(F0, F1);
                float_to_ubyte(F1, F0);
                charge(3);
                sb(a2 + 3, a0);
            }
        }
    } else {
        charge(3);
        v1 = lbu(a1 + 0);
        for (unsigned k = 0; k < 4; ++k) {
            ubyte_to_float(F2, F0);  // b
            charge(4);
            v1 = lw(sp + 8);
            v1 = lbu(v1 + k);
            ubyte_to_float(F0, F0);  // a
            charge(8);
            mula_s(F1, F0);
            if (k < 3) {
                madd_s(F2, F12, F2);
                v1 = lui(0x4f00);
                mtc1(v1, F0);
                c_le_s(F0, F2);
                float_to_ubyte(F2, F0);
                charge(5);
                sb(a2 + k, a0);
                v1 = lw(sp + 12);
                v1 = lbu(v1 + k + 1);
            } else {
                madd_s(F1, F12, F2);
                v1 = lui(0x4f00);
                mtc1(v1, F0);
                c_le_s(F0, F1);
                float_to_ubyte(F1, F0);
                charge(1);
                sb(a2 + 3, a0);
            }
        }
    }
    charge(3);
    sp = addiu(sp, 16);
}

// sub_1ED8A0 [clear the trail geometry]: $a0 the after effect (+72 s16 shape: 0 strip -> 2n + 1 vertices, 1 / 2
// -> 3n + 6; other shapes keep the caller's $a3 as the count), $a1 the geometry: the prelit colours (+48) and the
// vertices of the morph target (+92 -> +20) zeroed, its bounding sphere {0, 0, 0, 1e9} (through the frame).
void Cpu::sub_1ED8A0() {
    enter(5);
    sp = addiu(sp, -16);
    a2 = lh(a0 + 72);
    v1 = 2;
    if (a2 == v1) {
        charge(5);
        v1 = lw(a0 + 0);
        a0 = lw(v1 + 12);
        v1 = sll(a0, 1);
        v1 = addu(v1, a0);
        a3 = addiu(v1, 6);
    } else {
        charge(3);
        v1 = 1;
        if (a2 == v1) {
            charge(7);
            v1 = lw(a0 + 0);
            a0 = lw(v1 + 12);
            v1 = sll(a0, 1);
            v1 = addu(v1, a0);
            a3 = addiu(v1, 6);
        } else {
            charge(2);
            if (a2 == 0) {
                charge(6);
                v1 = lw(a0 + 0);
                v1 = lw(v1 + 12);
                v1 = sll(v1, 1);
                a3 = addiu(v1, 1);
            } else {
                charge(2);
            }
        }
    }
    charge(4);
    a0 = lw(a1 + 48);
    a2 = 0;
    for (;;) {
        charge(3);
        v1 = slt(a2, a3);
        if (v1 == 0) break;
        backedge();
        charge(6);
        sb(a0 + 0, zero);
        sb(a0 + 1, zero);
        sb(a0 + 2, zero);
        sb(a0 + 3, zero);
        a2 = addiu(a2, 1);
        a0 = addiu(a0, 4);
    }
    charge(5);
    v1 = lw(a1 + 92);
    a2 = lw(v1 + 20);
    a0 = 0;
    for (;;) {
        charge(3);
        v1 = slt(a0, a3);
        if (v1 == 0) break;
        backedge();
        charge(5);
        sw(a2 + 0, zero);
        sw(a2 + 4, zero);
        sw(a2 + 8, zero);
        a0 = addiu(a0, 1);
        a2 = addiu(a2, 12);
    }
    charge(21);
    sw(sp + 0, zero);
    sw(sp + 4, zero);
    sw(sp + 8, zero);
    v1 = lui(0x3b9a);
    v1 = ori(v1, 0xca00);  // 1000000000
    mtc1(v1, F0);
    cvt_s_w(F0, F0);
    swc1(F0, sp + 12);
    v1 = lw(a1 + 92);
    lwc1(F3, sp + 0);
    lwc1(F2, sp + 4);
    lwc1(F1, sp + 8);
    lwc1(F0, sp + 12);
    swc1(F3, v1 + 4);
    swc1(F2, v1 + 8);
    swc1(F1, v1 + 12);
    swc1(F0, v1 + 16);
    sp = addiu(sp, 16);
}

// sub_1ED9E0 [a key list has keys]: (u16 at $a0 +4 -> +0) != 0.
void Cpu::sub_1ED9E0() {
    enter(5);
    v0 = lw(a0 + 4);
    v0 = lhu(v0 + 0);
    v0 = sltu(zero, v0);
}

// nullsub_10: nothing.
void Cpu::nullsub_10() { enter(2); }

// sub_1EEFC0 [append an after effect to the live list]: head gp-18980, tail gp-18984, links +24 prev / +28 next.
void Cpu::sub_1EEFC0() {
    enter(3);
    v1 = lw(gpa(-18984));
    if (v1 == 0) {
        charge(6);
        sw(a0 + 24, zero);
        sw(a0 + 28, zero);
        sw(gpa(-18980), a0);
        sw(gpa(-18984), a0);
    } else {
        charge(5);
        sw(a0 + 24, v1);
        sw(a0 + 28, zero);
        v1 = lw(gpa(-18984));
        sw(v1 + 28, a0);
        sw(gpa(-18984), a0);
    }
    charge(2);
}

// sub_1EF000 [an after effect is live and not hidden]: in the list from gp-18980 and flag 8 (+0) clear.
void Cpu::sub_1EF000() {
    enter(3);
    v0 = lw(gpa(-18980));
    for (;;) {
        charge(5);
        if (v0 == 0) break;
        backedge();
        charge(2);
        if (v0 == a0) break;
        charge(1);
        v0 = lw(v0 + 28);
    }
    charge(2);
    if (v0 != 0) {
        charge(4);
        v0 = lw(a0 + 0);
        v0 = andi(v0, 0x8);
        v0 = sltu(zero, v0);
        v0 = xori(v0, 0x1);
    } else {
        charge(3);
        v0 = 0;
    }
    charge(2);
}

// =========================================================================================================
// After effects: the per-trail scripts and the object update (eff_after.c)
// =========================================================================================================

// sub_1EBA50 [restart a trail script]: state {+0 flags, +4 pc, +8 the script start, +16 the ring}: pc = start,
// flags = 0, and the ring's timing record reset (sub_1ED0B0).
void Cpu::sub_1EBA50() {
    enter(12);
    sp = addiu(sp, -16);
    sd(sp + 0, ra);
    v0 = lw(a0 + 8);
    sw(a0 + 4, v0);
    sw(a0 + 0, zero);
    a0 = lw(a0 + 16);
    jal_here(0x1eba68u, &Cpu::sub_1ED0B0);
    ra = ld(sp + 0);
    sp = addiu(sp, 16);
}

// sub_1EBA80 [run a trail script until it waits]: the 16-bit opcodes at the state's pc (+4) --
//   0x0000 end (stop here); 0x0001 wait n frames (u32 operand: flag 1 + counter +20, the pc moves on when the
//   counter reaches n); 0x0100 / 0x0101 trail on / off (flag 2); 0x0102 clear the ring's +8 / +12 (count, head);
//   0x0200 start the fade over (+28 frames) / 30 s unless a fade time (+24) is set (sub_1ED080); 0x0201 u16 operand
//   -> +24; 0x0202 u32 operand -> +28; 0x0400 kill (flag 8). An unknown opcode leaves the pc as it is and loops.
// The u32 operands are read through the frame slot sp+76 (two halves when not word aligned).
void Cpu::sub_1EBA80() {
    enter(8);
    sp = addiu(sp, -80);
    sd(sp + 48, ra);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp + 0, s0);
    s2 = a0;
    s1 = lw(a0 + 4);  // pc
    s0 = 0;           // stop
    do {
        charge(4);
        a0 = lhu(s1 + 0);
        v1 = 1024;
        if (a0 == v1) {  // kill
            charge(4);
            v1 = lw(s2 + 0);
            v1 = ori(v1, 0x8);
            sw(s2 + 0, v1);
            s1 = addiu(s1, 2);
        } else {
            charge(3);
            v1 = 514;
            if (a0 == v1) {  // fade frames
                read_operand();
                charge(5);
                v1 = lw(sp + 76);
                sw(s2 + 28, v1);
                s1 = addiu(s1, 6);
            } else {
                charge(3);
                v1 = 513;
                if (a0 == v1) {  // fade time
                    charge(5);
                    v1 = lhu(s1 + 2);
                    sh(s2 + 24, v1);
                    s1 = addiu(s1, 4);
                } else {
                    charge(3);
                    v1 = 512;
                    if (a0 == v1) {  // start the fade
                        charge(3);
                        v1 = lhu(s2 + 24);
                        if (v1 != 0) {
                            charge(2);
                        } else {
                            charge(3);
                            a0 = lw(s2 + 28);
                            if (a0 != 0) {
                                charge(2);
                                if (!bltz(a0)) {
                                    charge(5);
                                    mtc1(a0, F0);
                                    cvt_s_w(F1, F0);
                                } else {
                                    charge(7);
                                    v1 = srl(a0, 1);
                                    v0 = andi(a0, 0x1);
                                    v1 = or_(v1, v0);
                                    mtc1(v1, F0);
                                    cvt_s_w(F1, F0);
                                    add_s(F1, F1, F1);
                                }
                                charge(9);
                                v0 = lui(0x41f0);
                                mtc1(v0, F0);  // 30.0
                                div_s(F12, F1, F0);
                                a0 = lw(s2 + 16);
                                jal_here(0x1ebcc8u, &Cpu::sub_1ED080);
                            }
                        }
                        charge(3);
                        s1 = addiu(s1, 2);
                    } else {
                        charge(3);
                        v1 = 258;
                        if (a0 == v1) {  // clear the ring
                            charge(6);
                            v1 = lw(s2 + 16);
                            sw(v1 + 8, zero);
                            sw(v1 + 12, zero);
                            s1 = addiu(s1, 2);
                        } else {
                            charge(3);
                            v1 = 257;
                            if (a0 == v1) {  // trail off
                                charge(7);
                                a0 = lw(s2 + 0);
                                v1 = si(-3);
                                v1 = and_(a0, v1);
                                sw(s2 + 0, v1);
                                s1 = addiu(s1, 2);
                            } else {
                                charge(3);
                                v1 = 256;
                                if (a0 == v1) {  // trail on
                                    charge(6);
                                    v1 = lw(s2 + 0);
                                    v1 = ori(v1, 0x2);
                                    sw(s2 + 0, v1);
                                    s1 = addiu(s1, 2);
                                } else {
                                    charge(3);
                                    v1 = 1;
                                    if (a0 == v1) {  // wait
                                        charge(5);
                                        v1 = lw(s2 + 0);
                                        v1 = nor(v1, zero);
                                        v1 = andi(v1, 0x1);
                                        if (v1 != 0) {  // first frame of the wait
                                            read_operand();
                                            charge(6);
                                            v1 = lw(s2 + 0);
                                            v1 = ori(v1, 0x1);
                                            sw(s2 + 0, v1);
                                            sw(s2 + 20, zero);
                                        } else {
                                            charge(3);
                                            v1 = lw(s2 + 20);
                                            v1 = addiu(v1, 1);
                                            sw(s2 + 20, v1);
                                        }
                                        read_operand();
                                        charge(6);
                                        s0 = 1;
                                        a0 = lw(s2 + 20);
                                        v1 = lw(sp + 76);
                                        v1 = sltu(a0, v1);
                                        if (v1 == 0) {
                                            charge(8);
                                            s1 = addiu(s1, 6);
                                            a0 = lw(s2 + 0);
                                            v1 = si(-2);
                                            v1 = and_(a0, v1);
                                            sw(s2 + 0, v1);
                                            s0 = 0;
                                        }
                                    } else {
                                        charge(2);
                                        if (a0 == 0) {  // end
                                            charge(3);
                                            s0 = v1;
                                        } else {
                                            charge(2);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        charge(4);
        v1 = sltu(zero, s0);
        v1 = xori(v1, 0x1);
        if (v1 == 0) break;
        backedge();
    } while (true);
    charge(8);
    sw(s2 + 4, s1);
    ra = ld(sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp + 0);
    sp = addiu(sp, 80);
}

// sub_1EDA90 [take the trails' anchor points from the model's bones]: for a live after effect, per trail the two
// bones of the descriptor's pair (+24, 8 bytes: two bone ids) of the model (+32) give two world matrices
// (sub_318D10 into two RwMatrix from sub_4C38C0); their positions (+48) become the trail's point pair (+20, 24
// bytes); flag 2 on; the matrices freed (sub_4C3880).
void Cpu::sub_1EDA90() {
    enter(12);
    sp = addiu(sp, -96);
    sd(sp + 80, ra);
    sq(sp + 64, s4);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp + 0, s0);
    s4 = a0;
    jal_here(0x1edab0u, &Cpu::sub_1EF000);
    if (v0 != 0) {
        charge(9);
        jal(0x1edac0u, gen::fn_sub_4C38C0_004c38c0);
        s2 = v0;
        jal(0x1edaccu, gen::fn_sub_4C38C0_004c38c0);
        s1 = v0;
        s3 = 0;
        for (;;) {
            charge(5);
            v0 = lw(s4 + 4);
            v0 = lh(v0 + 4);
            v0 = slt(s3, v0);
            if (v0 == 0) break;
            backedge();
            charge(37);
            v1 = lw(s4 + 4);
            s0 = sll(s3, 3);
            v0 = lw(v1 + 24);
            v0 = addu(v0, s0);
            a0 = lw(v1 + 32);
            a1 = lw(v0 + 0);
            a2 = s2;
            jal(0x1edb00u, gen::fn_sub_318D10_00318d10);
            v1 = lw(s4 + 4);
            v0 = lw(v1 + 24);
            v0 = addu(v0, s0);
            a0 = lw(v1 + 32);
            a1 = lw(v0 + 4);
            a2 = s1;
            jal(0x1edb20u, gen::fn_sub_318D10_00318d10);
            v0 = sll(s3, 1);
            v0 = addu(v0, s3);
            v1 = sll(v0, 3);
            v0 = lw(s4 + 20);
            v0 = addu(v0, v1);
            copy3(v0 + 0, s2 + 48);
            v0 = lw(s4 + 20);
            v0 = addu(v0, v1);
            copy3(v0 + 12, s1 + 48);
            s3 = addiu(s3, 1);
        }
        charge(9);
        v0 = lw(s4 + 0);
        v0 = ori(v0, 0x2);
        sw(s4 + 0, v0);
        a0 = s2;
        jal(0x1edb9cu, gen::fn_sub_4C3880_004c3880);
        a0 = s1;
        jal(0x1edba8u, gen::fn_sub_4C3880_004c3880);
    }
    charge(9);
    ra = ld(sp + 80);
    lq(s4, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp + 0);
    sp = addiu(sp, 96);
}

// sub_1EDED0 [request a draw]: a live after effect gets flag 4.
void Cpu::sub_1EDED0() {
    enter(8);
    sp = addiu(sp, -32);
    sd(sp + 16, ra);
    sq(sp + 0, s0);
    s0 = a0;
    jal_here(0x1edee0u, &Cpu::sub_1EF000);
    if (v0 != 0) {
        charge(3);
        v1 = lw(s0 + 0);
        v1 = ori(v1, 0x4);
        sw(s0 + 0, v1);
    }
    charge(5);
    ra = ld(sp + 16);
    lq(s0, sp + 0);
    sp = addiu(sp, 32);
}

// sub_1EE230 [set the colour]: a live after effect whose RGBA (+32..+35) differs from *$a1 takes it, flag 0x10.
void Cpu::sub_1EE230() {
    enter(10);
    sp = addiu(sp, -48);
    sd(sp + 32, ra);
    sq(sp + 16, s1);
    sq(sp + 0, s0);
    s1 = a0;
    s0 = a1;
    jal_here(0x1ee248u, &Cpu::sub_1EF000);
    if (v0 != 0) {
        bool differs = false;
        for (unsigned k = 0; k < 4 && !differs; ++k) {
            charge(4);
            a0 = lbu(s1 + 32 + k);
            v1 = lbu(s0 + k);
            differs = a0 != v1;
        }
        if (differs) {
            charge(11);
            a2 = lbu(s0 + 0);
            a1 = lbu(s0 + 1);
            a0 = lbu(s0 + 2);
            v1 = lbu(s0 + 3);
            sb(s1 + 32, a2);
            sb(s1 + 33, a1);
            sb(s1 + 34, a0);
            sb(s1 + 35, v1);
            v1 = lw(s1 + 0);
            v1 = ori(v1, 0x10);
            sw(s1 + 0, v1);
        }
    }
    charge(6);
    ra = ld(sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp + 0);
    sp = addiu(sp, 48);
}

// sub_1EEE40 [start an after effect's scripts]: per trail: the state (+16, 32 bytes) gets its script (descriptor
// +28 [i]) and its ring (+8, 76 bytes), restarts (sub_1EBA50); flag 1 on; then every script runs to its first
// wait (sub_1EBA80).
void Cpu::sub_1EEE40() {
    enter(8);
    sp = addiu(sp, -64);
    sd(sp + 32, ra);
    sq(sp + 16, s1);
    sq(sp + 0, s0);
    s1 = a0;
    s0 = 0;
    for (;;) {
        charge(5);
        a1 = lw(s1 + 4);
        v1 = lh(a1 + 4);
        v1 = slt(s0, v1);
        if (v1 == 0) break;
        backedge();
        charge(19);
        v1 = sll(s0, 5);
        v0 = lw(s1 + 16);
        a0 = addu(v0, v1);
        v1 = sll(s0, 2);
        v0 = lw(a1 + 28);
        v0 = addu(v0, v1);
        v0 = lw(v0 + 0);
        sw(a0 + 8, v0);
        v0 = sll(s0, 3);
        v0 = addu(v0, s0);
        v0 = sll(v0, 1);
        v0 = addu(v0, s0);
        v1 = sll(v0, 2);  // i * 76
        v0 = lw(s1 + 8);
        v0 = addu(v0, v1);
        sw(a0 + 16, v0);
        jal_here(0x1eeea0u, &Cpu::sub_1EBA50);
        s0 = addiu(s0, 1);
    }
    charge(6);
    v1 = lw(s1 + 0);
    v1 = ori(v1, 0x1);
    sw(s1 + 0, v1);
    s0 = 0;
    for (;;) {
        charge(5);
        v1 = lw(s1 + 4);
        v1 = lh(v1 + 4);
        v1 = slt(s0, v1);
        if (v1 == 0) break;
        backedge();
        charge(7);
        v1 = sll(s0, 5);
        v0 = lw(s1 + 16);
        a0 = addu(v0, v1);
        a1 = addiu(sp, 60);
        jal_here(0x1eeee8u, &Cpu::sub_1EBA80);
        s0 = addiu(s0, 1);
    }
    charge(6);
    ra = ld(sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp + 0);
    sp = addiu(sp, 64);
}

// sub_1EB920 [push a sample]: the ring's next slot (+12 head) takes the two rail points ($a1, $a2); the count (+8)
// grows to the descriptor's capacity (+0 -> +8); head = (head + 1) % capacity (`div`: HI/LO as left). Then the
// geometry: count 2 -> sub_1EBD80(ring, 0); 1 -> nothing; 0 -> K_Assert line 1470; more -> sub_1EBD80(ring, 1)
// and sub_1EBD80(ring, 0).
void Cpu::sub_1EB920() {
    enter(30);
    sp = addiu(sp, -32);
    sd(sp + 16, ra);
    sq(sp + 0, s0);
    s0 = a0;
    a3 = lw(a0 + 12);
    v1 = sll(a3, 1);
    v1 = addu(v1, a3);
    a3 = sll(v1, 2);
    v1 = lw(a0 + 16);
    v1 = addu(v1, a3);
    copy3(v1, a1);
    v1 = lw(a0 + 20);
    v1 = addu(v1, a3);
    copy3(v1, a2);
    a1 = lw(a0 + 8);
    v1 = lw(a0 + 0);
    v1 = lw(v1 + 8);
    at = slt(a1, v1);
    if (at != 0) {
        charge(2);
        v1 = addiu(a1, 1);
        sw(s0 + 8, v1);
    }
    charge(12);
    v1 = lw(s0 + 12);
    a0 = addiu(v1, 1);
    sw(s0 + 12, a0);
    v1 = lw(s0 + 0);
    v1 = lw(v1 + 8);
    div(a0, v1);
    mfhi(v1);
    sw(s0 + 12, v1);
    a0 = lw(s0 + 8);
    v1 = 2;
    if (a0 == v1) {
        charge(6);
        a0 = s0;
        a1 = 0;
        jal_here(0x1eba10u, &Cpu::sub_1EBD80);
    } else {
        charge(3);
        a1 = 1;
        if (a0 != a1) {
            charge(2);
            if (a0 == 0) {
                charge(7);
                a0 = lui(0x68);
                a0 = addiu(a0, 17656);
                a1 = 1470;
                jal(0x1eb9f8u, gen::fn_sub_19D3F0_0019d3f0);
            } else {
                charge(2);
                charge(7);
                a0 = s0;
                jal_here(0x1eba24u, &Cpu::sub_1EBD80);
                a0 = s0;
                a1 = 0;
                jal_here(0x1eba34u, &Cpu::sub_1EBD80);
            }
        }
    }
    charge(5);
    ra = ld(sp + 16);
    lq(s0, sp + 0);
    sp = addiu(sp, 32);
}

// sub_1EDA00 [create an after effect]: none while flag 0x1400 is set (returns 0); else allocate it (sub_1EE2E0,
// heap) from the pack $a0 with the colour word $a1 at +32, build its trails (sub_1EEB90, heap), link it (sub_1EEFC0)
// and start its scripts (sub_1EEE40). Returns it.
void Cpu::sub_1EDA00() {
    enter(11);
    sp = addiu(sp, -48);
    sd(sp + 32, ra);
    sq(sp + 16, s1);
    sq(sp + 0, s0);
    s1 = a0;
    s0 = a1;
    a0 = 5120;
    jal(0x1eda1cu, gen::fn_datGetFlag_0016f190);
    if (v0 != 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(15);
        a0 = s1;
        jal(0x1eda3cu, gen::fn_sub_1EE2E0_001ee2e0);
        a0 = v0;
        sw(v0 + 32, s0);
        jal(0x1eda4cu, gen::fn_sub_1EEB90_001eeb90);
        s0 = v0;
        a0 = s0;
        jal_here(0x1eda5cu, &Cpu::sub_1EEFC0);
        a0 = s0;
        jal_here(0x1eda68u, &Cpu::sub_1EEE40);
        v0 = s0;
    }
    charge(6);
    ra = ld(sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp + 0);
    sp = addiu(sp, 48);
}

// sub_1EE1D0 [kill an after effect]: a live one gets flag 8 and its pack (descriptor +32) is released (sub_1EF340).
void Cpu::sub_1EE1D0() {
    enter(8);
    sp = addiu(sp, -32);
    sd(sp + 16, ra);
    sq(sp + 0, s0);
    s0 = a0;
    jal_here(0x1ee1e0u, &Cpu::sub_1EF000);
    if (v0 != 0) {
        charge(7);
        v0 = lw(s0 + 0);
        v0 = ori(v0, 0x8);
        sw(s0 + 0, v0);
        v0 = lw(s0 + 4);
        a0 = lw(v0 + 32);
        jal(0x1ee204u, gen::fn_sub_1EF340_001ef340);
    }
    charge(5);
    ra = ld(sp + 16);
    lq(s0, sp + 0);
    sp = addiu(sp, 32);
}

// sub_1EDBE0 [update an after effect, once per frame]: the model's frame step (+4 -> +32 -> +244, a float) decides
// whether time runs. Per trail: when it does, the script runs (sub_1EBA80); a live trail (object not killed, state
// flag 2) pushes a sample -- the anchor pair (+20) as it is (state flag 8) or through the model's inverse root
// matrix (or its +144 matrix when the model's +216 bit 15 is set; sub_4C32A0, sub_4C6BE0 on the frame at sp+96 /
// sp+108). Then the ring's clock advances by the frame step (gp-32540) or 0, a changed colour (flag 0x10; alpha 255
// becomes 254) goes to the trail's material colour (+12 [i] +4 -> +4), and the trail geometry is rebuilt
// (sub_1E9AF0 with the trail atomic's geometry, +12 [i] +0 -> +24, on the frame at sp+140).
void Cpu::sub_1EDBE0() {
    enter(17);
    sp = addiu(sp, -144);
    sd(sp + 80, ra);
    sq(sp + 64, s4);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp + 0, s0);
    s2 = a0;
    s0 = 0;
    v1 = lw(a0 + 4);
    v1 = lw(v1 + 32);
    lwc1(F1, v1 + 244);
    mtc1(zero, F0);
    c_eq_s(F0, F1);
    if (!bc1t()) {
        charge(1);
        s0 = 1;  // time runs
    }
    charge(3);
    s1 = 0;
    for (;;) {
        charge(5);
        v1 = lw(s2 + 4);
        v1 = lh(v1 + 4);
        v1 = slt(s1, v1);
        if (v1 == 0) break;
        backedge();
        charge(2);
        if (s0 != 0) {
            charge(11);
            s3 = sll(s1, 5);
            v0 = lw(s2 + 16);
            a0 = addu(v0, s3);
            a1 = addiu(sp, 136);
            jal_here(0x1edc4cu, &Cpu::sub_1EBA80);
            v0 = lw(s2 + 0);
            v0 = nor(v0, zero);
            v0 = andi(v0, 0x8);
            if (v0 != 0) {
                charge(6);
                v0 = lw(s2 + 16);
                v0 = addu(v0, s3);
                v1 = lw(v0 + 0);
                v0 = andi(v1, 0x2);
                if (v0 != 0) {
                    charge(3);
                    v0 = andi(v1, 0x8);
                    if (v0 != 0) {
                        charge(17);
                        v0 = sll(s1, 1);
                        v0 = addu(v0, s1);
                        v1 = sll(v0, 3);
                        v0 = lw(s2 + 20);
                        a1 = addu(v0, v1);
                        v0 = sll(s1, 3);
                        v0 = addu(v0, s1);
                        v0 = sll(v0, 1);
                        v0 = addu(v0, s1);
                        v1 = sll(v0, 2);
                        v0 = lw(s2 + 8);
                        a0 = addu(v0, v1);
                        a2 = addiu(a1, 12);
                        jal_here(0x1edcc0u, &Cpu::sub_1EB920);
                    } else {
                        charge(10);
                        jal(0x1edcd0u, gen::fn_sub_4C38C0_004c38c0);
                        s4 = v0;
                        v0 = lw(s2 + 4);
                        v1 = lw(v0 + 32);
                        v0 = lhu(v1 + 216);
                        v0 = nor(v0, zero);
                        v0 = andi(v0, 0x8000);
                        if (v0 != 0) {
                            charge(9);
                            a0 = v1;
                            jal(0x1edcfcu, gen::fn_sub_318B60_00318b60);
                            a0 = s4;
                            a1 = v0;
                            jal(0x1edd0cu, gen::fn_sub_4C32A0_004c32a0);
                        } else {
                            charge(4);
                            a0 = s4;
                            a1 = addiu(v1, 144);
                            jal(0x1edd24u, gen::fn_sub_4C32A0_004c32a0);
                        }
                        charge(30);
                        v0 = sll(s1, 1);
                        v0 = addu(v0, s1);
                        s3 = sll(v0, 3);
                        v0 = lw(s2 + 20);
                        a1 = addu(v0, s3);
                        a0 = addiu(sp, 96);
                        a2 = s4;
                        jal(0x1edd48u, gen::fn_sub_4C6BE0_004c6be0);
                        v0 = lw(s2 + 20);
                        v0 = addu(v0, s3);
                        a0 = addiu(sp, 108);
                        a1 = addiu(v0, 12);
                        a2 = s4;
                        jal(0x1edd64u, gen::fn_sub_4C6BE0_004c6be0);
                        v0 = sll(s1, 3);
                        v0 = addu(v0, s1);
                        v0 = sll(v0, 1);
                        v0 = addu(v0, s1);
                        v1 = sll(v0, 2);
                        v0 = lw(s2 + 8);
                        a0 = addu(v0, v1);
                        a1 = addiu(sp, 96);
                        a2 = addiu(sp, 108);
                        jal_here(0x1edd90u, &Cpu::sub_1EB920);
                        a0 = s4;
                        jal(0x1edd9cu, gen::fn_sub_4C3880_004c3880);
                    }
                }
            }
        }
        charge(2);
        if (s0 != 0) {
            charge(4);
            lwc1(F0, gpa(-32540));
            swc1(F0, sp + 132);
        } else {
            charge(1);
            sw(sp + 132, zero);
        }
        charge(4);
        v0 = lw(s2 + 0);
        v0 = andi(v0, 0x10);
        if (v0 != 0) {
            charge(12);
            a1 = lbu(s2 + 32);
            a0 = lbu(s2 + 33);
            v1 = lbu(s2 + 34);
            v0 = lbu(s2 + 35);
            sb(sp + 128, a1);
            sb(sp + 129, a0);
            sb(sp + 130, v1);
            sb(sp + 131, v0);
            v1 = lbu(sp + 131);
            v0 = 255;
            if (v1 == v0) {
                charge(2);
                v0 = 254;
                sb(sp + 131, v0);
            }
            charge(12);
            v1 = sll(s1, 3);
            v0 = lw(s2 + 12);
            v0 = addu(v0, v1);
            a2 = lw(v0 + 4);
            a1 = lbu(sp + 128);
            a0 = lbu(sp + 129);
            v1 = lbu(sp + 130);
            v0 = lbu(sp + 131);
            sb(a2 + 4, a1);
            sb(a2 + 5, a0);
            sb(a2 + 6, v1);
            sb(a2 + 7, v0);
        }
        charge(22);
        v0 = sll(s1, 3);
        v0 = addu(v0, s1);
        v0 = sll(v0, 1);
        v0 = addu(v0, s1);
        s3 = sll(v0, 2);
        v0 = lw(s2 + 8);
        a0 = addu(v0, s3);
        a1 = addiu(sp, 132);
        jal_here(0x1ede58u, &Cpu::sub_1ED0D0);
        v1 = sll(s1, 3);
        v0 = lw(s2 + 12);
        v0 = addu(v0, v1);
        v0 = lw(v0 + 0);
        v0 = lw(v0 + 24);
        sw(sp + 140, v0);
        v0 = lw(s2 + 8);
        a0 = addu(v0, s3);
        a1 = addiu(sp, 140);
        jal_here(0x1ede84u, &Cpu::sub_1E9AF0);
        s1 = addiu(s1, 1);
    }
    charge(9);
    ra = ld(sp + 80);
    lq(s4, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp + 0);
    sp = addiu(sp, 144);
}

// =========================================================================================================
// After effects: the trail geometry (eff_after.c)
// =========================================================================================================

// sub_1E8E80 [create a trail's geometry]: $a0 the ring (+0 the descriptor: +4 -> flags word (bit 0 textured), +12 n
// segments; +72 s16 shape), $a1 the material. RpGeometryCreate(vertices, triangles, flags 74 | textured 4): shape 0
// a strip of 2n + 1 vertices / 2n - 1 triangles, shapes 1 / 2 a ribbon of 3n + 6 vertices / 4n + 4 triangles
// (sub_493210 per triangle, the 16-bit index arithmetic as compiled, the counters spilled whole on the frame).
// Every triangle gets the material (sub_493230). Prelit colours: shape 0 from the colour keys (sub_1ED0F0, key 0 /
// key 1 at t = i / (n - 1), the first rail offset by half a step), shapes 1 / 2 zero. Textured: UVs (shape 0 u = i
// / (n - 1) on rail 0 (half a step on), 1.0 last; rail 1 v = 1.0; shapes 1 / 2 the ribbon's caps and the middle row at
// v = 0.5). The morph target's bounding sphere {0, 0, 0, 1e9} through the frame. Returns the geometry.
void Cpu::sub_1E8E80() {
    enter(20);
    sp = addiu(sp, -256);
    sd(sp + 144, ra);
    sq(sp + 128, s8);
    sq(sp + 112, s7);
    sq(sp + 96, s6);
    sq(sp + 80, s5);
    sq(sp + 64, s4);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp + 0, s0);
    s5 = a0;
    sw(sp + 236, a1);
    a2 = 74;
    v0 = lw(a0 + 0);
    v0 = lw(v0 + 4);
    v0 = lw(v0 + 0);
    v0 = andi(v0, 0x1);
    if (v0 != 0) {
        charge(1);
        a2 = ori(a2, 0x4);
    }
    charge(6);
    s7 = 0;  // triangles
    s2 = 0;  // vertices
    v1 = lh(s5 + 72);
    v0 = 2;
    if (v1 == v0) {
        charge(7);
        v0 = lw(s5 + 0);
        v1 = lw(v0 + 12);
        v0 = sll(v1, 2);
        s7 = addiu(v0, 4);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        s2 = addiu(v0, 6);
    } else {
        charge(3);
        v0 = 1;
        if (v1 == v0) {
            charge(9);
            v0 = lw(s5 + 0);
            v1 = lw(v0 + 12);
            v0 = sll(v1, 2);
            s7 = addiu(v0, 4);
            v0 = sll(v1, 1);
            v0 = addu(v0, v1);
            s2 = addiu(v0, 6);
        } else {
            charge(2);
            if (v1 == 0) {
                charge(9);
                v0 = lw(s5 + 0);
                v1 = lw(v0 + 12);
                v0 = addiu(v1, -1);
                v0 = sll(v0, 1);
                s7 = addiu(v0, 1);
                v0 = sll(v1, 1);
                s2 = addiu(v0, 1);
            } else {
                charge(2);
            }
        }
    }
    charge(10);
    a0 = s2;
    a1 = s7;
    jal(0x1e8f74u, gen::fn_sub_493710_00493710);
    s4 = v0;
    s3 = lw(v0 + 44);  // the triangles
    v1 = lh(s5 + 72);
    t0 = 2;
    unsigned shape = 3;  // 3: no triangles written
    if (v1 == t0) {
        shape = 2;
    } else {
        charge(3);
        v0 = 1;
        if (v1 == v0) {
            shape = 1;
        } else {
            charge(2);
            if (v1 == 0)
                shape = 0;
            else
                charge(2);
        }
    }
    if (shape == 0) {
        charge(3);
        s1 = 0;
        for (;;) {
            charge(6);
            v0 = lw(s5 + 0);
            v0 = lw(v0 + 12);
            v0 = addiu(v0, -1);
            v0 = slt(s1, v0);
            if (v0 == 0) break;
            backedge();
            charge(20);
            s0 = sll(s1, 1);
            s6 = addiu(s0, 2);
            s8 = addiu(s0, 1);
            a2 = andi(s0, 0xffff);
            a3 = andi(s8, 0xffff);
            t0 = andi(s6, 0xffff);
            a0 = s4;
            a1 = s3;
            jal(0x1e8fdcu, gen::fn_sub_493210_00493210);
            a2 = andi(s8, 0xffff);
            v0 = addiu(s0, 3);
            a3 = andi(v0, 0xffff);
            t0 = andi(s6, 0xffff);
            a0 = s4;
            a1 = addiu(s3, 8);
            jal(0x1e8ffcu, gen::fn_sub_493210_00493210);
            s3 = addiu(s3, 16);
            s1 = addiu(s1, 1);
        }
        charge(12);
        v1 = sll(s1, 1);
        a2 = andi(v1, 0xffff);
        v0 = addiu(v1, 1);
        a3 = andi(v0, 0xffff);
        v0 = addiu(v1, 2);
        t0 = andi(v0, 0xffff);
        a0 = s4;
        a1 = s3;
        jal(0x1e9044u, gen::fn_sub_493210_00493210);
    } else if (shape == 1 || shape == 2) {
        const bool two = shape == 2;
        const u32 slot_a = two ? 176 : 208, slot_b = two ? 160 : 192;
        charge(18);
        a0 = s4;
        a1 = s3;
        a2 = 0;
        a3 = 3;
        jal(two ? 0x1e91b8u : 0x1e9064u, gen::fn_sub_493210_00493210);
        a0 = s4;
        a1 = addiu(s3, 8);
        a2 = 2;
        a3 = 4;
        t0 = 1;
        jal(two ? 0x1e91d4u : 0x1e9080u, gen::fn_sub_493210_00493210);
        s3 = addiu(s3, 16);
        s1 = 2;  // daddiu s1, $zero, 2
        s8 = 0;
        for (;;) {
            charge(5);
            v0 = lw(s5 + 0);
            v0 = lw(v0 + 12);
            v0 = slt(s8, v0);
            if (v0 == 0) break;
            backedge();
            charge(42);
            s0 = andi(s1, 0xffff);
            s6 = addiu(s0, 3);
            v0 = addiu(s0, 1);
            sq(sp + slot_a, v0);
            a3 = andi(v0, 0xffff);
            t0 = andi(s6, 0xffff);
            a0 = s4;
            a1 = s3;
            a2 = s1;
            jal(two ? 0x1e9214u : 0x1e90c0u, gen::fn_sub_493210_00493210);
            v0 = addiu(s0, 2);
            sq(sp + slot_b, v0);
            a3 = andi(s6, 0xffff);
            t0 = andi(v0, 0xffff);
            a0 = s4;
            a1 = addiu(s3, 8);
            a2 = s1;
            jal(two ? 0x1e9238u : 0x1e90e4u, gen::fn_sub_493210_00493210);
            lq(v0, sp + slot_a);
            a2 = andi(v0, 0xffff);
            v0 = addiu(s0, 4);
            a3 = andi(v0, 0xffff);
            t0 = andi(s6, 0xffff);
            a0 = s4;
            a1 = addiu(s3, 16);
            jal(two ? 0x1e925cu : 0x1e9108u, gen::fn_sub_493210_00493210);
            lq(v0, sp + slot_b);
            a2 = andi(v0, 0xffff);
            a3 = andi(s6, 0xffff);
            v0 = addiu(s0, 5);
            t0 = andi(v0, 0xffff);
            a0 = s4;
            a1 = addiu(s3, 24);
            jal(two ? 0x1e9280u : 0x1e912cu, gen::fn_sub_493210_00493210);
            s3 = addiu(s3, 32);
            v0 = addiu(s1, 3);
            s1 = andi(v0, 0xffff);
            s8 = addiu(s8, 1);
        }
        charge(two ? 18 : 20);
        s0 = andi(s1, 0xffff);
        s6 = addiu(s0, 3);
        v0 = addiu(s0, 1);
        a3 = andi(v0, 0xffff);
        t0 = andi(s6, 0xffff);
        a0 = s4;
        a1 = s3;
        a2 = s1;
        jal(two ? 0x1e92ccu : 0x1e9178u, gen::fn_sub_493210_00493210);
        a3 = andi(s6, 0xffff);
        v0 = addiu(s0, 2);
        t0 = andi(v0, 0xffff);
        a0 = s4;
        a1 = addiu(s3, 8);
        a2 = s1;
        jal(two ? 0x1e92ecu : 0x1e9198u, gen::fn_sub_493210_00493210);
    }
    // every triangle gets the material
    charge(4);
    s1 = lw(s4 + 44);
    s0 = 0;
    for (;;) {
        charge(3);
        v0 = slt(s0, s7);
        if (v0 == 0) break;
        backedge();
        charge(7);
        a0 = s4;
        a1 = s1;
        a2 = lw(sp + 236);
        jal(0x1e9310u, gen::fn_sub_493230_00493230);
        s0 = addiu(s0, 1);
        s1 = addiu(s1, 8);
    }
    // prelit colours
    charge(4);
    v1 = lh(s5 + 72);
    v0 = 2;
    if (v1 == v0) {
        charge(4);
        v1 = lw(s4 + 48);
        a0 = 0;
        for (;;) {
            charge(3);
            v0 = slt(a0, s2);
            if (v0 == 0) break;
            backedge();
            charge(6);
            sb(v1 + 0, zero);
            sb(v1 + 1, zero);
            sb(v1 + 2, zero);
            sb(v1 + 3, zero);
            a0 = addiu(a0, 1);
            v1 = addiu(v1, 4);
        }
    } else {
        charge(3);
        v0 = 1;
        if (v1 == v0) {
            charge(4);
            v1 = lw(s4 + 48);
            a0 = 0;
            for (;;) {
                charge(3);
                v0 = slt(a0, s2);
                if (v0 == 0) break;
                backedge();
                charge(6);
                sb(v1 + 0, zero);
                sb(v1 + 1, zero);
                sb(v1 + 2, zero);
                sb(v1 + 3, zero);
                a0 = addiu(a0, 1);
                v1 = addiu(v1, 4);
            }
            charge(2);
        } else {
            charge(2);
            if (v1 == 0) {
                charge(4);
                s1 = lw(s4 + 48);
                s0 = 0;
                for (;;) {
                    charge(5);
                    v0 = lw(s5 + 0);
                    v1 = lw(v0 + 12);
                    v0 = slt(s0, v1);
                    if (v0 == 0) break;
                    backedge();
                    charge(2);
                    if (s0 == 0) {
                        charge(13);
                        mtc1(s0, F0);
                        cvt_s_w(F1, F0);
                        v0 = addiu(v1, -1);
                        mtc1(v0, F0);
                        cvt_s_w(F0, F0);
                        div_s(F12, F1, F0);
                    } else {
                        charge(12);
                        mtc1(s0, F0);
                        cvt_s_w(F1, F0);
                        v0 = lui(0x3f00);
                        mtc1(v0, F0);  // 0.5
                        sub_s(F1, F1, F0);
                        v0 = addiu(v1, -1);
                        mtc1(v0, F0);
                        cvt_s_w(F0, F0);
                        div_s(F12, F1, F0);
                    }
                    charge(7);
                    a0 = s5;
                    a1 = 0;
                    a2 = s1;
                    jal_here(0x1e93e0u, &Cpu::sub_1ED0F0);
                    s0 = addiu(s0, 1);
                    s1 = addiu(s1, 8);
                }
                charge(12);
                v0 = lui(0x3f80);
                mtc1(v0, F12);
                a0 = s5;
                a1 = 0;
                a2 = s1;
                jal_here(0x1e9418u, &Cpu::sub_1ED0F0);
                v0 = lw(s4 + 48);
                s0 = addiu(v0, 4);
                s1 = 0;
                for (;;) {
                    charge(5);
                    v0 = lw(s5 + 0);
                    v1 = lw(v0 + 12);
                    v0 = slt(s1, v1);
                    if (v0 == 0) break;
                    backedge();
                    charge(15);
                    mtc1(s1, F0);
                    cvt_s_w(F1, F0);
                    v0 = addiu(v1, -1);
                    mtc1(v0, F0);
                    cvt_s_w(F0, F0);
                    div_s(F12, F1, F0);
                    a0 = s5;
                    a1 = 1;
                    a2 = s0;
                    jal_here(0x1e9460u, &Cpu::sub_1ED0F0);
                    s1 = addiu(s1, 1);
                    s0 = addiu(s0, 8);
                }
                charge(2);
            } else {
                charge(2);
            }
        }
    }
    // texture coordinates
    charge(6);
    a0 = lw(s5 + 0);
    v0 = lw(a0 + 4);
    v0 = lw(v0 + 0);
    v0 = andi(v0, 0x1);
    if (v0 != 0) {
        charge(4);
        v1 = lh(s5 + 72);
        v0 = 2;
        const bool two = v1 == v0;
        bool ribbon = two;
        if (!two) {
            charge(3);
            v0 = 1;
            if (v1 == v0) {
                ribbon = true;
            } else {
                charge(2);
                if (v1 == 0) {
                    charge(4);
                    s1 = lw(s4 + 52);
                    s0 = 0;
                    for (;;) {
                        charge(5);
                        v0 = lw(s5 + 0);
                        v1 = lw(v0 + 12);
                        v0 = slt(s0, v1);
                        if (v0 == 0) break;
                        backedge();
                        charge(3);
                        v0 = addiu(v1, -1);
                        if (!bgtz(v0)) assert_after(0x1e9568u, 553);
                        charge(2);
                        if (s0 == 0) {
                            charge(15);
                            v0 = lw(s5 + 0);
                            v0 = lw(v0 + 12);
                            v0 = addiu(v0, -1);
                            mtc1(v0, F0);
                            cvt_s_w(F1, F0);
                            mtc1(s0, F0);
                            cvt_s_w(F0, F0);
                            div_s(F0, F0, F1);
                            swc1(F0, s1 + 0);
                        } else {
                            charge(15);
                            v0 = lw(s5 + 0);
                            v0 = lw(v0 + 12);
                            v0 = addiu(v0, -1);
                            mtc1(v0, F0);
                            cvt_s_w(F2, F0);
                            mtc1(s0, F0);
                            cvt_s_w(F1, F0);
                            v0 = lui(0x3f00);
                            mtc1(v0, F0);
                            sub_s(F0, F1, F0);
                            div_s(F0, F0, F2);
                            swc1(F0, s1 + 0);
                        }
                        charge(3);
                        sw(s1 + 4, zero);
                        s0 = addiu(s0, 1);
                        s1 = addiu(s1, 16);
                    }
                    charge(8);
                    v0 = lui(0x3f80);
                    sw(s1 + 0, v0);
                    sw(s1 + 4, zero);
                    v0 = lw(s4 + 52);
                    s0 = addiu(v0, 8);
                    s1 = 0;
                    for (;;) {
                        charge(5);
                        v0 = lw(s5 + 0);
                        v1 = lw(v0 + 12);
                        v0 = slt(s1, v1);
                        if (v0 == 0) break;
                        backedge();
                        charge(3);
                        v0 = addiu(v1, -1);
                        if (!bgtz(v0)) assert_after(0x1e9648u, 567);
                        charge(15);
                        v0 = lw(s5 + 0);
                        v0 = lw(v0 + 12);
                        v0 = addiu(v0, -1);
                        mtc1(v0, F0);
                        cvt_s_w(F1, F0);
                        mtc1(s1, F0);
                        cvt_s_w(F0, F0);
                        div_s(F0, F0, F1);
                        swc1(F0, s0 + 0);
                        v0 = lui(0x3f80);
                        sw(s0 + 4, v0);
                        s1 = addiu(s1, 1);
                        s0 = addiu(s0, 16);
                    }
                    charge(2);
                } else {
                    charge(2);
                }
            }
        }
        if (ribbon) {
            // caps: the first vertex pair and the last three vertices; the edge rows from 0.5 / (n + 0.5) in steps
            // of 1 / (n + 0.5), the middle row at v = 0.5
            const unsigned fa = two ? F4 : F0;  // the middle-row u
            const unsigned fb = two ? F0 : F1;  // the edge-row u
            charge(35);
            a1 = lw(s4 + 52);
            v1 = lw(a0 + 12);
            v0 = sll(v1, 1);
            v0 = addu(v0, v1);
            v0 = addiu(v0, 6);
            a0 = lui(0x3f00);
            mtc1(a0, F2);  // 0.5
            mtc1(v1, F0);
            cvt_s_w(F0, F0);
            add_s(F1, F2, F0);  // n + 0.5
            sw(a1 + 0, zero);
            sw(a1 + 4, zero);
            sw(a1 + 8, zero);
            v1 = lui(0x3f80);
            mtc1(v1, F0);
            sw(a1 + 12, v1);
            sw(a1 + 16, zero);
            sw(a1 + 20, a0);
            v0 = sll(v0, 3);
            v0 = addu(v0, a1);
            sw(v0 - 24, v1);
            sw(v0 - 20, zero);
            sw(v0 - 16, v1);
            sw(v0 - 12, v1);
            sw(v0 - 8, v1);
            sw(v0 - 4, a0);
            div_s(fa, F0, F1);
            mov_s(F3, fa);  // the step
            div_s(fb, F2, F1);
            Gpr& ptr = two ? a0 : a2;
            Gpr& cnt = two ? a2 : a0;
            ptr = addiu(a1, 24);
            cnt = 0;
            for (;;) {
                charge(5);
                v0 = lw(s5 + 0);
                v0 = lw(v0 + 12);
                v0 = slt(cnt, v0);
                if (v0 == 0) break;
                backedge();
                charge(7);
                swc1(fb, ptr + 0);
                sw(ptr + 4, zero);
                swc1(fb, ptr + 8);
                sw(ptr + 12, v1);
                ptr = addiu(ptr, 24);
                cnt = addiu(cnt, 1);
                add_s(fb, fb, F3);
            }
            charge(5);
            a0 = addiu(a1, 40);
            a1 = 0;
            v1 = lui(0x3f00);
            for (;;) {
                charge(5);
                v0 = lw(s5 + 0);
                v0 = lw(v0 + 12);
                v0 = slt(a1, v0);
                if (v0 == 0) break;
                backedge();
                charge(5);
                swc1(fa, a0 + 0);
                sw(a0 + 4, v1);
                a1 = addiu(a1, 1);
                add_s(fa, fa, F3);
                a0 = addiu(a0, 24);
            }
            if (!two) charge(2);
        }
    }
    charge(32);
    sw(sp + 240, zero);
    sw(sp + 244, zero);
    sw(sp + 248, zero);
    v0 = lui(0x3b9a);
    v0 = ori(v0, 0xca00);
    mtc1(v0, F0);
    cvt_s_w(F0, F0);
    swc1(F0, sp + 252);
    v0 = lw(s4 + 92);
    lwc1(F3, sp + 240);
    lwc1(F2, sp + 244);
    lwc1(F1, sp + 248);
    lwc1(F0, sp + 252);
    swc1(F3, v0 + 4);
    swc1(F2, v0 + 8);
    swc1(F1, v0 + 12);
    swc1(F0, v0 + 16);
    v0 = s4;
    ra = ld(sp + 144);
    lq(s8, sp + 128);
    lq(s7, sp + 112);
    lq(s6, sp + 96);
    lq(s5, sp + 80);
    lq(s4, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp + 0);
    sp = addiu(sp, 256);
}

// sub_1EBD80 [the Bezier handles of a trail segment]: $a0 the ring (+0 -> +0 the curve parameters: +0 / +4 / +8 /
// +12 / +16 / +20 / +24 weights, +28..+40 the per-side length / bend factors), $a1 the sample. For each rail and each
// end of the segment (sample, sample + 1) a handle = norm(w_side * side vector (sub_1E8360) + w_in * dir to the newer
// sample + w_out * dir from the older one) * (length factor * |segment| (sub_1ECD90) + bend factor * bend
// (sub_1ECEC0)), stored at the sample's slot of the ring's +24 / +32 (start, rails 0 / 1) and +28 / +36 (end). The
// side whose segment is shorter takes the first factor pair (frame sp+112..124). Two samples, or the newest of
// three, use the end weights (+12 / +16, +20 / +24).
void Cpu::sub_1EBD80() {
    enter(39);
    sp = addiu(sp, -160);
    sd(sp + 96, ra);
    sq(sp + 80, s3);
    sq(sp + 64, s2);
    sq(sp + 48, s1);
    sq(sp + 32, s0);
    swc1(F27, sp + 28);
    swc1(F26, sp + 24);
    swc1(F25, sp + 20);
    swc1(F24, sp + 16);
    swc1(F23, sp + 12);
    swc1(F22, sp + 8);
    swc1(F21, sp + 4);
    swc1(F20, sp + 0);
    s2 = a0;
    s1 = a1;
    v0 = lw(a0 + 0);
    v0 = lw(v0 + 0);  // the curve parameters
    lwc1(F0, v0 + 28);
    swc1(F0, sp + 120);
    lwc1(F0, v0 + 36);
    swc1(F0, sp + 112);
    lwc1(F0, v0 + 32);
    swc1(F0, sp + 124);
    lwc1(F0, v0 + 40);
    swc1(F0, sp + 116);
    a2 = 0;
    jal_here(0x1ebdecu, &Cpu::sub_1ECD90);
    mov_s(F20, F0);
    a0 = s2;
    a1 = s1;
    a2 = 1;
    jal_here(0x1ebe04u, &Cpu::sub_1ECD90);
    c_le_s(F20, F0);
    v0 = 1;
    if (bc1t()) {
        charge(1);
        v0 = 0;
    }
    charge(5);
    s0 = xori(v0, 0x1);  // the side of the shorter segment
    v1 = lw(s2 + 8);
    v0 = 2;
    if (v1 == v0) {
        charge(7);
        v0 = lw(s2 + 0);
        v0 = lw(v0 + 0);
        lwc1(F27, v0 + 12);
        lwc1(F21, v0 + 16);
        mtc1(zero, F22);
    } else {
        charge(2);
        if (s1 == 0) {
            charge(7);
            v0 = lw(s2 + 0);
            v0 = lw(v0 + 0);
            lwc1(F27, v0 + 12);
            lwc1(F21, v0 + 16);
            mtc1(zero, F22);
        } else {
            charge(5);
            v0 = lw(s2 + 0);
            v0 = lw(v0 + 0);
            lwc1(F27, v0 + 0);
            lwc1(F21, v0 + 8);
            lwc1(F22, v0 + 4);
        }
    }
    // --- the start handle on rail 0 ---
    charge(51);
    sw(sp + 144, zero);
    sw(sp + 148, zero);
    sw(sp + 152, zero);
    v0 = andi(s0, 0x1);
    s3 = sll(v0, 2);
    v0 = addu(s3, sp);
    v0 = addiu(v0, 120);
    lwc1(F26, v0 + 0);
    a0 = s2;
    a1 = s1;
    a2 = 0;
    jal_here(0x1ebeb4u, &Cpu::sub_1ECD90);
    mul_s(F20, F26, F0);
    v0 = addu(s3, sp);
    v0 = addiu(v0, 112);
    lwc1(F23, v0 + 0);
    a0 = s2;
    a1 = s1;
    jal_here(0x1ebed4u, &Cpu::sub_1ECEC0);
    mul_s(F0, F23, F0);
    add_s(F20, F20, F0);  // the handle length
    a0 = s2;
    a1 = s1;
    a2 = 0;
    a3 = addiu(sp, 128);
    jal_here(0x1ebef4u, &Cpu::sub_1E8360);
    scale_acc(F27);
    v0 = lw(s2 + 8);
    at = slti(v0, 2);
    dir_newer(s1, 16, 0x1ebf60u, 0x1ec028u);
    charge(22);
    scale_acc(F22);
    v0 = lw(s2 + 8);
    at = slti(v0, 2);
    dir_older(s1, 16, 0x1ec094u, 0x1ec164u);
    charge(36);
    scale_acc(F21);
    a0 = addiu(sp, 144);
    a1 = a0;
    jal(0x1ec1bcu, gen::fn_sub_4C69F0_004c69f0);
    scale_sum(F20);
    slot_s1_v1();
    if (!bgez(v1)) {
        charge(2);
        v0 = lw(s2 + 8);
        v1 = addu(v1, v0);
    }
    // --- the start handle on rail 1 ---
    charge(63);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v1 = sll(v0, 2);
    v0 = lw(s2 + 24);
    v0 = addu(v0, v1);
    copy3(v0, sp + 144);
    sw(sp + 144, zero);
    sw(sp + 148, zero);
    sw(sp + 152, zero);
    v0 = addiu(s0, 1);
    v0 = andi(v0, 0x1);
    s0 = sll(v0, 2);
    v0 = addu(s0, sp);
    v0 = addiu(v0, 120);
    lwc1(F25, v0 + 0);
    a0 = s2;
    a1 = s1;
    a2 = 1;
    jal_here(0x1ec260u, &Cpu::sub_1ECD90);
    mul_s(F20, F25, F0);
    v0 = addu(s0, sp);
    v0 = addiu(v0, 112);
    lwc1(F24, v0 + 0);
    a0 = s2;
    a1 = s1;
    jal_here(0x1ec280u, &Cpu::sub_1ECEC0);
    mul_s(F0, F24, F0);
    add_s(F20, F20, F0);
    a0 = s2;
    a1 = s1;
    a2 = 1;
    a3 = addiu(sp, 128);
    jal_here(0x1ec2a0u, &Cpu::sub_1E8360);
    scale_acc(F27);
    v0 = lw(s2 + 8);
    at = slti(v0, 2);
    dir_newer(s1, 20, 0x1ec30cu, 0x1ec3d4u);
    charge(22);
    scale_acc(F22);
    v0 = lw(s2 + 8);
    at = slti(v0, 2);
    dir_older(s1, 20, 0x1ec440u, 0x1ec510u);
    charge(36);
    scale_acc(F21);
    a0 = addiu(sp, 144);
    a1 = a0;
    jal(0x1ec568u, gen::fn_sub_4C69F0_004c69f0);
    scale_sum(F20);
    slot_s1_v1();
    if (!bgez(v1)) {
        charge(2);
        v0 = lw(s2 + 8);
        v1 = addu(v1, v0);
    }
    charge(15);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v1 = sll(v0, 2);
    v0 = lw(s2 + 32);
    v0 = addu(v0, v1);
    copy3(v0, sp + 144);
    v1 = lw(s2 + 8);
    v0 = 2;
    bool end_weights = v1 == v0;
    if (!end_weights) {
        charge(3);
        v0 = 3;
        if (v1 == v0) {
            charge(3);
            v0 = 1;
            end_weights = s1 == v0;
        }
    }
    if (end_weights) {
        charge(7);
        v0 = lw(s2 + 0);
        v0 = lw(v0 + 0);
        lwc1(F22, v0 + 20);
        mtc1(zero, F21);
        lwc1(F20, v0 + 24);
    } else {
        charge(5);
        v0 = lw(s2 + 0);
        v0 = lw(v0 + 0);
        lwc1(F22, v0 + 0);
        lwc1(F21, v0 + 8);
        lwc1(F20, v0 + 4);
    }
    // --- the end handle on rail 0 (sample + 1) ---
    charge(44);
    sw(sp + 144, zero);
    sw(sp + 148, zero);
    sw(sp + 152, zero);
    s0 = addiu(s1, 1);
    a0 = s2;
    a1 = s1;
    a2 = 0;
    jal_here(0x1ec650u, &Cpu::sub_1ECD90);
    mul_s(F26, F26, F0);
    a0 = s2;
    a1 = s1;
    jal_here(0x1ec664u, &Cpu::sub_1ECEC0);
    mul_s(F0, F23, F0);
    add_s(F23, F26, F0);
    a0 = s2;
    a1 = s0;
    a2 = 0;
    a3 = addiu(sp, 128);
    jal_here(0x1ec684u, &Cpu::sub_1E8360);
    scale_acc(F22);
    v0 = lw(s2 + 8);
    at = slti(v0, 2);
    dir_newer(s0, 16, 0x1ec6f0u, 0x1ec7b8u);
    charge(22);
    scale_acc(F20);
    v0 = lw(s2 + 8);
    at = slti(v0, 2);
    dir_older(s0, 16, 0x1ec824u, 0x1ec8f4u);
    charge(36);
    scale_acc(F21);
    a0 = addiu(sp, 144);
    a1 = a0;
    jal(0x1ec94cu, gen::fn_sub_4C69F0_004c69f0);
    scale_sum(F23);
    slot_s1_v1();
    if (!bgez(v1)) {
        charge(2);
        v0 = lw(s2 + 8);
        v1 = addu(v1, v0);
    }
    // --- the end handle on rail 1 ---
    charge(55);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v1 = sll(v0, 2);
    v0 = lw(s2 + 28);
    v0 = addu(v0, v1);
    copy3(v0, sp + 144);
    sw(sp + 144, zero);
    sw(sp + 148, zero);
    sw(sp + 152, zero);
    s0 = addiu(s1, 1);
    a0 = s2;
    a1 = s1;
    a2 = 1;
    jal_here(0x1ec9dcu, &Cpu::sub_1ECD90);
    mul_s(F23, F25, F0);
    a0 = s2;
    a1 = s1;
    jal_here(0x1ec9f0u, &Cpu::sub_1ECEC0);
    mul_s(F0, F24, F0);
    add_s(F23, F23, F0);
    a0 = s2;
    a1 = s0;
    a2 = 1;
    a3 = addiu(sp, 128);
    jal_here(0x1eca10u, &Cpu::sub_1E8360);
    scale_acc(F22);
    v0 = lw(s2 + 8);
    at = slti(v0, 2);
    dir_newer(s0, 20, 0x1eca7cu, 0x1ecb44u);
    charge(22);
    scale_acc(F20);
    v0 = lw(s2 + 8);
    at = slti(v0, 2);
    dir_older(s0, 20, 0x1ecbb0u, 0x1ecc80u);
    charge(36);
    scale_acc(F21);
    a0 = addiu(sp, 144);
    a1 = a0;
    jal(0x1eccd8u, gen::fn_sub_4C69F0_004c69f0);
    scale_sum(F23);
    v1 = lw(s2 + 12);
    v1 = addiu(v1, -1);
    a0 = subu(v1, s1);
    if (!bgez(a0)) {
        charge(2);
        v1 = lw(s2 + 8);
        a0 = addu(a0, v1);
    }
    charge(27);
    v1 = sll(a0, 1);
    v1 = addu(v1, a0);
    a0 = sll(v1, 2);
    v1 = lw(s2 + 36);
    v1 = addu(v1, a0);
    copy3(v1, sp + 144);
    ra = ld(sp + 96);
    lq(s3, sp + 80);
    lq(s2, sp + 64);
    lq(s1, sp + 48);
    lq(s0, sp + 32);
    lwc1(F27, sp + 28);
    lwc1(F26, sp + 24);
    lwc1(F25, sp + 20);
    lwc1(F24, sp + 16);
    lwc1(F23, sp + 12);
    lwc1(F22, sp + 8);
    lwc1(F21, sp + 4);
    lwc1(F20, sp + 0);
    sp = addiu(sp, 160);
}

// sub_1E9AF0 [rebuild a trail's geometry from its samples]: $a0 the ring, $a1 &geometry (on the caller's frame). The
// geometry locked (geometryLock, flags 26). Colours first when the ring's flag 1 is set or flag 2 clear (then flag 2
// on): shape 0 per rail from the colour keys (sub_1ED0F0, t = i / (n - 1), rail 0 half a step on, the last vertex of
// rail 0 at t = 1); shapes 1 / 2 the caps and both edge rows, the middle row their average. Then the vertices: fewer
// than two samples zero them; else each vertex row comes from the cubic Bezier of the segment the arc-length sampler
// (sub_1E7F90) picks for it (control points from the ring's rails and handle arrays, cached per segment): shape 0
// the two rails as a strip; shape 1 the two rails plus the middle row (their average, then smoothed along the
// ribbon by 1/4 weights); shape 2 a camera-facing ribbon around rail 0 (half width = curve +20 / 2, narrowed by
// |view . tangent|^3, the camera position from sub_198590). Unlock (sub_4933D0), the geometry's +12 flag 1, and the
// morph target's bounding sphere {0, 0, 0, 1e9} through the frame.
void Cpu::sub_1E9AF0() {
    enter(26);
    sp = addiu(sp, -416);
    sd(sp + 176, ra);
    sq(sp + 160, s8);
    sq(sp + 144, s7);
    sq(sp + 128, s6);
    sq(sp + 112, s5);
    sq(sp + 96, s4);
    sq(sp + 80, s3);
    sq(sp + 64, s2);
    sq(sp + 48, s1);
    sq(sp + 32, s0);
    swc1(F24, sp + 16);
    swc1(F23, sp + 12);
    swc1(F22, sp + 8);
    swc1(F21, sp + 4);
    swc1(F20, sp + 0);
    s5 = a0;
    s4 = a1;
    a0 = lw(a1 + 0);
    a1 = 26;
    jal(0x1e9b40u, gen::fn_geometryLock_00493370);
    v1 = lw(s5 + 4);
    v0 = andi(v1, 0x1);
    bool colours = v0 != 0;
    if (!colours) {
        charge(4);
        v0 = nor(v1, zero);
        v0 = andi(v0, 0x2);
        colours = v0 != 0;
    }
    if (colours) af_colours();
    charge(4);
    v0 = lw(s5 + 8);
    at = slti(v0, 2);
    if (at != 0) {
        af_short();
    } else {
        charge(4);
        v1 = lh(s5 + 72);
        v0 = 2;
        if (v1 == v0) {
            af_shape2();
        } else {
            charge(3);
            v0 = 1;
            if (v1 == v0) {
                af_shape1();
            } else {
                charge(2);
                if (v1 == 0) {
                    af_shape0();
                } else {
                    charge(2);
                }
            }
        }
    }
    charge(44);
    a0 = lw(s4 + 0);
    jal(0x1eb86cu, gen::fn_sub_4933D0_004933d0);
    a0 = lw(s4 + 0);
    v1 = lhu(a0 + 12);
    v1 = ori(v1, 0x1);
    sh(a0 + 12, v1);
    sw(sp + 272, zero);
    sw(sp + 276, zero);
    sw(sp + 280, zero);
    v1 = lui(0x3b9a);
    v1 = ori(v1, 0xca00);
    mtc1(v1, F0);
    cvt_s_w(F0, F0);
    swc1(F0, sp + 284);
    v1 = lw(s4 + 0);
    v1 = lw(v1 + 92);
    lwc1(F3, sp + 272);
    lwc1(F2, sp + 276);
    lwc1(F1, sp + 280);
    lwc1(F0, sp + 284);
    swc1(F3, v1 + 4);
    swc1(F2, v1 + 8);
    swc1(F1, v1 + 12);
    swc1(F0, v1 + 16);
    ra = ld(sp + 176);
    lq(s8, sp + 160);
    lq(s7, sp + 144);
    lq(s6, sp + 128);
    lq(s5, sp + 112);
    lq(s4, sp + 96);
    lq(s3, sp + 80);
    lq(s2, sp + 64);
    lq(s1, sp + 48);
    lq(s0, sp + 32);
    lwc1(F24, sp + 16);
    lwc1(F23, sp + 12);
    lwc1(F22, sp + 8);
    lwc1(F21, sp + 4);
    lwc1(F20, sp + 0);
    sp = addiu(sp, 416);
}

// sub_1E9AF0, the prelit colours (from L_1e9b68 to the flag-2 store).
void Cpu::af_colours() {
    charge(4);
    v1 = lh(s5 + 72);
    v0 = 2;
    if (v1 == v0) {  // shape 2: key 1 for both edges, key 0 for the middle row
        charge(55);
        v0 = lw(s4 + 0);
        s0 = lw(v0 + 48);
        mtc1(zero, F12);
        a0 = s5;
        a1 = 1;
        a2 = s0;
        jal_here(0x1e9fecu, &Cpu::sub_1ED0F0);
        mtc1(zero, F12);
        a0 = s5;
        a1 = 1;
        a2 = addiu(s0, 4);
        jal_here(0x1ea004u, &Cpu::sub_1ED0F0);
        v0 = lw(s5 + 0);
        v1 = lw(v0 + 12);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        s6 = addiu(v0, 6);
        v0 = lui(0x3f80);
        mtc1(v0, F12);
        v0 = addiu(s6, -3);
        v0 = sll(v0, 2);
        a2 = addu(s0, v0);
        a0 = s5;
        a1 = 1;
        jal_here(0x1ea03cu, &Cpu::sub_1ED0F0);
        v0 = lui(0x3f80);
        mtc1(v0, F12);
        v0 = addiu(s6, -2);
        v0 = sll(v0, 2);
        a2 = addu(s0, v0);
        a0 = s5;
        a1 = 1;
        jal_here(0x1ea060u, &Cpu::sub_1ED0F0);
        v0 = lw(s5 + 0);
        lwc1(F0, v0 + 12);
        cvt_s_w(F0, F0);
        v0 = lui(0x3f00);
        mtc1(v0, F1);
        add_s(F22, F1, F0);  // n + 0.5
        v0 = lui(0x3f80);
        mtc1(v0, F0);
        div_s(F21, F0, F22);
        s1 = addiu(s0, 12);
        div_s(F20, F1, F22);
        s2 = 0;
        for (;;) {
            charge(5);
            v0 = lw(s5 + 0);
            v0 = lw(v0 + 12);
            v0 = slt(s2, v0);
            if (v0 == 0) break;
            backedge();
            charge(17);
            a2 = s1;
            s1 = addiu(s1, 4);
            a0 = s5;
            a1 = 1;
            mov_s(F12, F20);
            jal_here(0x1ea0c4u, &Cpu::sub_1ED0F0);
            s7 = addiu(s1, 4);
            a0 = s5;
            a1 = 1;
            mov_s(F12, F20);
            a2 = s1;
            jal_here(0x1ea0e0u, &Cpu::sub_1ED0F0);
            s1 = addiu(s7, 4);
            s2 = addiu(s2, 1);
            add_s(F20, F20, F21);
        }
        charge(24);
        mtc1(zero, F12);
        a0 = s5;
        a1 = 0;
        a2 = addiu(s0, 8);
        jal_here(0x1ea118u, &Cpu::sub_1ED0F0);
        v0 = lui(0x3f80);
        mtc1(v0, F12);
        v0 = addiu(s6, -1);
        v0 = sll(v0, 2);
        a2 = addu(s0, v0);
        a0 = s5;
        a1 = 0;
        jal_here(0x1ea13cu, &Cpu::sub_1ED0F0);
        v0 = lui(0x3f80);
        mtc1(v0, F0);
        div_s(F21, F0, F22);
        mov_s(F20, F21);
        s0 = addiu(s0, 20);
        s1 = 0;
        for (;;) {
            charge(5);
            v0 = lw(s5 + 0);
            v0 = lw(v0 + 12);
            v0 = slt(s1, v0);
            if (v0 == 0) break;
            backedge();
            charge(9);
            a0 = s5;
            a1 = 0;
            mov_s(F12, F20);
            a2 = s0;
            jal_here(0x1ea178u, &Cpu::sub_1ED0F0);
            s1 = addiu(s1, 1);
            add_s(F20, F20, F21);
            s0 = addiu(s0, 12);
        }
    } else {
        charge(3);
        v0 = 1;
        if (v1 == v0) {  // shape 1: keys 0 / 1 on the edges, the middle row their average
            charge(97);
            v0 = lw(s4 + 0);
            s0 = lw(v0 + 48);
            mtc1(zero, F12);
            a0 = s5;
            a1 = 0;
            a2 = s0;
            jal_here(0x1e9d4cu, &Cpu::sub_1ED0F0);
            mtc1(zero, F12);
            a0 = s5;
            a1 = 1;
            a2 = addiu(s0, 4);
            jal_here(0x1e9d64u, &Cpu::sub_1ED0F0);
            for (unsigned k = 0; k < 4; ++k) {
                v1 = lbu(s0 + k);
                v0 = lbu(s0 + 4 + k);
                v0 = addu(v1, v0);
                v0 = sra(v0, 1);
                sb(s0 + 8 + k, v0);
            }
            v0 = lw(s5 + 0);
            v1 = lw(v0 + 12);
            v0 = sll(v1, 1);
            v0 = addu(v0, v1);
            s1 = addiu(v0, 6);  // vertex count
            v0 = lui(0x3f80);
            mtc1(v0, F12);
            v0 = addiu(s1, -3);
            v0 = sll(v0, 2);
            a2 = addu(s0, v0);
            a0 = s5;
            a1 = 0;
            jal_here(0x1e9decu, &Cpu::sub_1ED0F0);
            v0 = lui(0x3f80);
            mtc1(v0, F12);
            v0 = addiu(s1, -2);
            v0 = sll(v0, 2);
            a2 = addu(s0, v0);
            a0 = s5;
            a1 = 1;
            jal_here(0x1e9e10u, &Cpu::sub_1ED0F0);
            v0 = sll(s1, 2);
            a0 = addu(v0, s0);
            for (unsigned k = 0; k < 4; ++k) {
                v1 = lbu(a0 - 12 + k);
                v0 = lbu(a0 - 8 + k);
                v0 = addu(v1, v0);
                v0 = sra(v0, 1);
                sb(a0 - 4 + k, v0);
            }
            v0 = lw(s5 + 0);
            lwc1(F0, v0 + 12);
            cvt_s_w(F0, F0);
            v0 = lui(0x3f00);
            mtc1(v0, F2);
            add_s(F1, F2, F0);
            v0 = lui(0x3f80);
            mtc1(v0, F0);
            div_s(F20, F0, F1);
            s2 = addiu(s0, 12);
            div_s(F21, F2, F1);
            s1 = 0;
            for (;;) {
                charge(5);
                v0 = lw(s5 + 0);
                v0 = lw(v0 + 12);
                v0 = slt(s1, v0);
                if (v0 == 0) break;
                backedge();
                charge(17);
                a2 = s2;
                s2 = addiu(s2, 4);
                a0 = s5;
                a1 = 0;
                mov_s(F12, F21);
                jal_here(0x1e9eccu, &Cpu::sub_1ED0F0);
                s6 = addiu(s2, 4);
                a0 = s5;
                a1 = 1;
                mov_s(F12, F21);
                a2 = s2;
                jal_here(0x1e9ee8u, &Cpu::sub_1ED0F0);
                s2 = addiu(s6, 4);
                s1 = addiu(s1, 1);
                add_s(F21, F21, F20);
            }
            charge(4);
            v0 = addiu(s0, 20);
            v1 = 0;
            for (;;) {
                charge(5);
                a0 = lw(s5 + 0);
                a0 = lw(a0 + 12);
                a0 = slt(v1, a0);
                if (a0 == 0) break;
                backedge();
                charge(38);
                for (unsigned k = 0; k < 4; ++k) {
                    a1 = lbu(v0 - 8 + k);
                    a0 = lbu(v0 - 4 + k);
                    a1 = addu(a1, a0);
                    a0 = lbu(v0 + 4 + k);
                    a1 = addu(a0, a1);
                    a0 = lbu(v0 + 8 + k);
                    a0 = addu(a0, a1);
                    a0 = sra(a0, 2);
                    sb(v0 + k, a0);
                }
                v1 = addiu(v1, 1);
                v0 = addiu(v0, 12);
            }
            charge(2);
        } else {
            charge(2);
            if (v1 == 0) {  // shape 0: per rail from the keys
                charge(5);
                v0 = lw(s4 + 0);
                s0 = lw(v0 + 48);
                s1 = 0;
                for (;;) {
                    charge(5);
                    v0 = lw(s5 + 0);
                    v1 = lw(v0 + 12);
                    v0 = slt(s1, v1);
                    if (v0 == 0) break;
                    backedge();
                    charge(3);
                    v0 = addiu(v1, -1);
                    if (!bgtz(v0)) assert_after(0x1e9bc0u, 980);
                    charge(2);
                    if (s1 == 0) {
                        charge(15);
                        v0 = lw(s5 + 0);
                        v0 = lw(v0 + 12);
                        v0 = addiu(v0, -1);
                        mtc1(v0, F0);
                        cvt_s_w(F1, F0);
                        mtc1(s1, F0);
                        cvt_s_w(F0, F0);
                        div_s(F0, F0, F1);
                        swc1(F0, sp + 412);
                    } else {
                        charge(15);
                        v0 = lw(s5 + 0);
                        v0 = lw(v0 + 12);
                        v0 = addiu(v0, -1);
                        mtc1(v0, F0);
                        cvt_s_w(F2, F0);
                        mtc1(s1, F0);
                        cvt_s_w(F1, F0);
                        v0 = lui(0x3f00);
                        mtc1(v0, F0);
                        sub_s(F0, F1, F0);
                        div_s(F0, F0, F2);
                        swc1(F0, sp + 412);
                    }
                    charge(8);
                    a0 = s5;
                    a1 = 0;
                    lwc1(F12, sp + 412);
                    a2 = s0;
                    jal_here(0x1e9c58u, &Cpu::sub_1ED0F0);
                    s1 = addiu(s1, 1);
                    s0 = addiu(s0, 8);
                }
                charge(13);
                v0 = lui(0x3f80);
                mtc1(v0, F12);
                a0 = s5;
                a1 = 0;
                a2 = s0;
                jal_here(0x1e9c90u, &Cpu::sub_1ED0F0);
                v0 = lw(s4 + 0);
                v0 = lw(v0 + 48);
                s1 = addiu(v0, 4);
                s0 = 0;
                for (;;) {
                    charge(5);
                    v0 = lw(s5 + 0);
                    v1 = lw(v0 + 12);
                    v0 = slt(s0, v1);
                    if (v0 == 0) break;
                    backedge();
                    charge(3);
                    v0 = addiu(v1, -1);
                    if (!bgtz(v0)) assert_after(0x1e9cc8u, 991);
                    charge(18);
                    v0 = lw(s5 + 0);
                    v0 = lw(v0 + 12);
                    v0 = addiu(v0, -1);
                    mtc1(v0, F0);
                    cvt_s_w(F1, F0);
                    mtc1(s0, F0);
                    cvt_s_w(F0, F0);
                    div_s(F12, F0, F1);
                    swc1(F12, sp + 412);
                    a0 = s5;
                    a1 = 1;
                    a2 = s1;
                    jal_here(0x1e9d08u, &Cpu::sub_1ED0F0);
                    s0 = addiu(s0, 1);
                    s1 = addiu(s1, 8);
                }
                charge(2);
            } else {
                charge(2);
            }
        }
    }
    charge(3);
    v0 = lw(s5 + 4);
    v0 = ori(v0, 0x2);
    sw(s5 + 4, v0);
}

// sub_1E9AF0 with fewer than two samples: every vertex the trail uses is zeroed (shape 0: both rails over n + 1 rows
// of 24 bytes, K_Assert lines 1087 / 1097 when a row reaches the geometry's end; shapes 1 / 2: 3n + 6 vertices).
void Cpu::af_short() {
    charge(4);
    v1 = lh(s5 + 72);
    v0 = 2;
    if (v1 == v0) {
        charge(11);
        v0 = lw(s5 + 0);
        v1 = lw(v0 + 12);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v1 = addiu(v0, 6);
        v0 = lw(s4 + 0);
        v0 = lw(v0 + 92);
        a0 = lw(v0 + 20);
        a1 = 0;
        for (;;) {
            charge(3);
            v0 = slt(a1, v1);
            if (v0 == 0) break;
            backedge();
            charge(5);
            sw(a0 + 0, zero);
            sw(a0 + 4, zero);
            sw(a0 + 8, zero);
            a1 = addiu(a1, 1);
            a0 = addiu(a0, 12);
        }
        charge(2);
        return;
    }
    charge(3);
    v0 = 1;
    if (v1 == v0) {
        charge(11);
        v0 = lw(s5 + 0);
        v1 = lw(v0 + 12);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v1 = addiu(v0, 6);
        v0 = lw(s4 + 0);
        v0 = lw(v0 + 92);
        a0 = lw(v0 + 20);
        a1 = 0;
        for (;;) {
            charge(3);
            v0 = slt(a1, v1);
            if (v0 == 0) break;
            backedge();
            charge(5);
            sw(a0 + 0, zero);
            sw(a0 + 4, zero);
            sw(a0 + 8, zero);
            a1 = addiu(a1, 1);
            a0 = addiu(a0, 12);
        }
        charge(2);
        return;
    }
    charge(2);
    if (v1 != 0) {
        charge(2);
        return;
    }
    charge(11);
    v1 = lw(s4 + 0);
    v0 = lw(v1 + 92);
    s2 = lw(v0 + 20);
    v1 = lw(v1 + 20);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    s0 = addu(s2, v0);  // the vertex array's end
    s1 = 0;
    for (;;) {
        charge(6);
        v0 = lw(s5 + 0);
        v0 = lw(v0 + 12);
        v0 = addiu(v0, 1);
        v0 = slt(s1, v0);
        if (v0 == 0) break;
        backedge();
        charge(2);
        if (s0 == s2) assert_after(0x1ea228u, 1087);
        charge(5);
        sw(s2 + 0, zero);
        sw(s2 + 4, zero);
        sw(s2 + 8, zero);
        s1 = addiu(s1, 1);
        s2 = addiu(s2, 24);
    }
    charge(7);
    v0 = lw(s4 + 0);
    v0 = lw(v0 + 92);
    v0 = lw(v0 + 20);
    s1 = addiu(v0, 12);
    s2 = 0;
    for (;;) {
        charge(5);
        v0 = lw(s5 + 0);
        v0 = lw(v0 + 12);
        v0 = slt(s2, v0);
        if (v0 == 0) break;
        backedge();
        charge(2);
        if (s0 == s1) assert_after(0x1ea28cu, 1097);
        charge(5);
        sw(s1 + 0, zero);
        sw(s1 + 4, zero);
        sw(s1 + 8, zero);
        s2 = addiu(s2, 1);
        s1 = addiu(s1, 24);
    }
    charge(2);
}

// sub_1E9AF0, shape 0: the two rails as a strip, rail r's vertices at +12 r of 24-byte rows; row i at the arc
// position i / (n - 1) (rail 0 half a step on), the last row the newest sample itself (K_Assert lines 1155 / 1184 /
// 1201); +408 then holds 0 or the head for the next pass.
void Cpu::af_shape0() {
    charge(11);
    v1 = lw(s4 + 0);
    v0 = lw(v1 + 92);
    s6 = lw(v0 + 20);  // the vertices
    v1 = lw(v1 + 20);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    s8 = addu(s6, v0);  // their end
    s1 = 0;             // the rail
    for (;;) {
        charge(3);
        v0 = slti(s1, 2);
        if (v0 == 0) break;
        backedge();
        charge(8);
        v0 = sll(s1, 1);
        v0 = addu(v0, s1);
        v0 = sll(v0, 2);
        s3 = addu(s6, v0);
        s2 = si(-1);  // the cached segment
        v0 = 1;
        if (s1 == v0) {
            charge(4);
            v0 = lw(s5 + 0);
            v0 = lw(v0 + 12);
            v0 = addiu(v0, -1);
            sw(sp + 208, v0);
        } else {
            charge(2);
            if (s1 == 0) {
                charge(5);
                v0 = lw(s5 + 0);
                v0 = lw(v0 + 12);
                sw(sp + 208, v0);
            } else {
                charge(2);
            }
        }
        charge(8);
        s0 = 0;
        v0 = sll(s1, 2);
        v0 = addu(s5, v0);
        sq(sp + 192, v0);  // the ring + 4 r (its rail array at +16)
        v0 = sll(s1, 3);
        s7 = addu(s5, v0);  // the ring + 8 r (its handle arrays at +24 / +28)
        for (;;) {
            charge(4);
            v0 = lw(sp + 208);
            v0 = slt(s0, v0);
            if (v0 == 0) break;
            backedge();
            charge(5);
            v0 = lw(s5 + 0);
            v0 = lw(v0 + 12);
            v0 = addiu(v0, -1);
            if (!bgtz(v0)) assert_after(0x1ea458u, 1155);
            charge(2);
            if (s1 == 0) {
                charge(2);
                if (s0 == 0) {
                    charge(17);
                    v0 = lw(s5 + 0);
                    v0 = lw(v0 + 12);
                    v0 = addiu(v0, -1);
                    mtc1(v0, F0);
                    cvt_s_w(F1, F0);
                    mtc1(s0, F0);
                    cvt_s_w(F0, F0);
                    div_s(F12, F0, F1);
                    a0 = s5;
                    a1 = addiu(sp, 408);
                    a2 = addiu(sp, 412);
                    jal(0x1ea4a4u, gen::fn_sub_1E7F90_001e7f90);
                } else {
                    charge(21);
                    v0 = lw(s5 + 0);
                    v0 = lw(v0 + 12);
                    v0 = addiu(v0, -1);
                    mtc1(v0, F0);
                    cvt_s_w(F2, F0);
                    mtc1(s0, F0);
                    cvt_s_w(F1, F0);
                    v0 = lui(0x3f00);
                    mtc1(v0, F0);
                    sub_s(F0, F1, F0);
                    div_s(F12, F0, F2);
                    a0 = s5;
                    a1 = addiu(sp, 408);
                    a2 = addiu(sp, 412);
                    jal(0x1ea4f8u, gen::fn_sub_1E7F90_001e7f90);
                }
            } else {
                charge(15);
                v0 = lw(s5 + 0);
                v0 = lw(v0 + 12);
                v0 = addiu(v0, -1);
                mtc1(v0, F0);
                cvt_s_w(F1, F0);
                mtc1(s0, F0);
                cvt_s_w(F0, F0);
                div_s(F12, F0, F1);
                a0 = s5;
                a1 = addiu(sp, 408);
                a2 = addiu(sp, 412);
                jal(0x1ea53cu, gen::fn_sub_1E7F90_001e7f90);
            }
            charge(3);
            a0 = lw(sp + 408);
            if (a0 != s2) load_segment(s2, true, zero, s7);
            charge(7);
            v0 = lui(0x3f80);
            mtc1(v0, F1);
            lwc1(F0, sp + 412);
            sub_s(F20, F1, F0);
            v0 = sltu(s3, s8);
            if (v0 == 0) assert_after(0x1ea678u, 1184);
            charge(64);
            lwc1(F5, sp + 412);
            bezier3(s3, F5, F20, F4, F3, F2, F1, true);
            s0 = addiu(s0, 1);
            s3 = addiu(s3, 24);
        }
        charge(5);
        v1 = lw(s5 + 8);
        v0 = lw(s5 + 12);
        s0 = subu(v0, v1);
        if (!bgez(s0)) {
            charge(1);
            s0 = addu(s0, v1);
        }
        charge(3);
        v0 = sltu(s3, s8);
        if (v0 == 0) assert_after(0x1ea7c0u, 1201);
        charge(18);
        v0 = sll(s0, 1);
        v0 = addu(v0, s0);
        v1 = sll(v0, 2);
        lq(v0, sp + 192);
        v0 = lw(v0 + 16);
        v0 = addu(v0, v1);
        copy3(s3, v0);  // the last row: the newest sample
        v1 = lw(s5 + 8);
        v0 = lw(s5 + 0);
        v0 = lw(v0 + 8);
        at = slt(v1, v0);
        if (at != 0) {
            charge(3);
            sw(sp + 408, zero);
        } else {
            charge(2);
            v0 = lw(s5 + 12);
            sw(sp + 408, v0);
        }
        charge(1);
        s1 = addiu(s1, 1);
    }
    charge(2);
}

// sub_1E9AF0, shape 1: the ribbon's caps (the newest and the oldest sample: both rails and their midpoint), then per
// rail the rows from the arc sampler at 0.5 / (n + 0.5) + i / (n + 0.5) (36-byte rows, rails at +0 / +12 after the
// first cap), and the middle row smoothed.
void Cpu::af_shape1() {
    charge(11);
    v0 = lw(s5 + 0);
    v1 = lw(v0 + 12);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v1 = addiu(v0, 6);
    v0 = lw(s4 + 0);
    v0 = lw(v0 + 92);
    a0 = lw(v0 + 20);
    a1 = 0;
    for (;;) {
        charge(3);
        v0 = slt(a1, v1);
        if (v0 == 0) break;
        backedge();
        charge(5);
        sw(a0 + 0, zero);
        sw(a0 + 4, zero);
        sw(a0 + 8, zero);
        a1 = addiu(a1, 1);
        a0 = addiu(a0, 12);
    }
    charge(7);
    v0 = lw(s4 + 0);
    v0 = lw(v0 + 92);
    v0 = lw(v0 + 20);
    v1 = lw(s5 + 12);
    a0 = addiu(v1, -1);
    if (!bgez(a0)) {
        charge(2);
        v1 = lw(s5 + 8);
        a0 = addu(a0, v1);
    }
    charge(52);
    v1 = sll(a0, 1);
    v1 = addu(v1, a0);
    a0 = sll(v1, 2);
    v1 = lw(s5 + 16);
    v1 = addu(v1, a0);
    copy3(v0 + 0, v1);
    v1 = lw(s5 + 20);
    v1 = addu(v1, a0);
    copy3(v0 + 12, v1);
    sum3(v0 + 24, v0 + 0, v0 + 12, F1);
    v1 = lui(0x3f00);
    mtc1(v1, F1);
    scale3(v0 + 24, F1);
    v1 = lw(s5 + 0);
    a0 = lw(v1 + 12);
    v1 = sll(a0, 1);
    v1 = addu(v1, a0);
    a1 = addiu(v1, 6);
    a0 = lw(s5 + 8);
    v1 = lw(s5 + 12);
    a2 = subu(v1, a0);
    if (!bgez(a2)) {
        charge(1);
        a2 = addu(a2, a0);
    }
    charge(65);
    v1 = sll(a2, 1);
    v1 = addu(v1, a2);
    a0 = sll(v1, 2);
    v1 = sll(a1, 1);
    v1 = addu(v1, a1);
    v1 = sll(v1, 2);
    v1 = addu(v1, v0);  // the vertex array's end
    v0 = lw(s5 + 16);
    v0 = addu(v0, a0);
    copy3(v1 - 36, v0);
    v0 = lw(s5 + 20);
    v0 = addu(v0, a0);
    copy3(v1 - 24, v0);
    sum3(v1 - 12, v1 - 36, v1 - 24, F1);
    v0 = lui(0x3f00);
    mtc1(v0, F2);
    scale3(v1 - 12, F2);
    v0 = lw(s4 + 0);
    v0 = lw(v0 + 92);
    s0 = lw(v0 + 20);
    v0 = lw(s5 + 0);
    lwc1(F0, v0 + 12);
    cvt_s_w(F0, F0);
    add_s(F1, F2, F0);
    v0 = lui(0x3f80);
    mtc1(v0, F0);
    div_s(F21, F0, F1);  // the step
    s1 = 0;
    div_s(F22, F2, F1);  // the first position
    for (;;) {
        charge(3);
        v0 = slti(s1, 2);
        if (v0 == 0) break;
        backedge();
        charge(3);
        v0 = 1;
        if (s1 == v0) {
            charge(1);
            s3 = addiu(s0, 48);
        } else {
            charge(2);
            if (s1 == 0) {
                charge(3);
                s3 = addiu(s0, 36);
            } else {
                charge(2);
            }
        }
        charge(9);
        mov_s(F20, F22);
        s6 = si(-1);
        s2 = 0;
        v0 = sll(s1, 2);
        s8 = addu(s5, v0);
        v0 = sll(s1, 3);
        s7 = addu(s5, v0);
        for (;;) {
            charge(5);
            v0 = lw(s5 + 0);
            v0 = lw(v0 + 12);
            v0 = slt(s2, v0);
            if (v0 == 0) break;
            backedge();
            charge(9);
            a0 = s5;
            mov_s(F12, F20);
            a1 = addiu(sp, 408);
            a2 = addiu(sp, 412);
            jal(0x1eaae4u, gen::fn_sub_1E7F90_001e7f90);
            a0 = lw(sp + 408);
            if (a0 != s6) load_segment(s6, false, s8, s7);
            charge(69);
            lwc1(F6, sp + 412);
            v0 = lui(0x3f80);
            mtc1(v0, F0);
            sub_s(F1, F0, F6);
            bezier3(s3, F6, F1, F5, F4, F3, F2, true);
            add_s(F20, F20, F21);
            s2 = addiu(s2, 1);
            s3 = addiu(s3, 36);
        }
        charge(6);
        s3 = addiu(s0, 60);
        v1 = 0;
        v0 = lui(0x3e80);
        mtc1(v0, F1);  // 0.25
        for (;;) {
            charge(5);
            v0 = lw(s5 + 0);
            v0 = lw(v0 + 12);
            v0 = slt(v1, v0);
            if (v0 == 0) break;
            backedge();
            charge(47);
            smooth(s3);
            v1 = addiu(v1, 1);
            s3 = addiu(s3, 36);
        }
        charge(1);
        s1 = addiu(s1, 1);
    }
    charge(2);
}

// sub_1E9AF0, shape 2: the camera-facing ribbon around rail 0. Per row the arc sampler's point P (Bezier into the
// frame's sp+376) gets the two edge vertices P +- the side vector (billboard_dir / billboard_emit); the newest
// sample caps the end, the oldest the start (with the first row's point kept at sp+312), the middle rows the edge
// average, then the smoothing pass.
void Cpu::af_shape2() {
    charge(33);
    v1 = lw(s5 + 0);
    v0 = lui(0x4000);
    mtc1(v0, F1);
    lwc1(F0, v1 + 20);
    div_s(F24, F0, F1);  // the half width
    jal(0x1eae3cu, gen::fn_sub_198590_00198590);
    v0 = lw(v0 + 4);
    s1 = addiu(v0, 64);  // the camera frame's position
    v0 = lw(s4 + 0);
    v0 = lw(v0 + 92);
    s0 = lw(v0 + 20);
    v0 = lw(s5 + 0);
    lwc1(F0, v0 + 12);
    cvt_s_w(F0, F0);
    v0 = lui(0x3f00);
    mtc1(v0, F2);
    add_s(F1, F2, F0);
    v0 = lui(0x3f80);
    mtc1(v0, F0);
    div_s(F21, F0, F1);
    div_s(F20, F2, F1);
    s6 = si(-1);
    s2 = addiu(s0, 36);
    v0 = lw(s5 + 12);
    v1 = addiu(v0, -1);
    if (!bgez(v1)) {
        charge(2);
        v0 = lw(s5 + 8);
        v1 = addu(v1, v0);
    }
    charge(14);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v1 = sll(v0, 2);
    v0 = lw(s5 + 16);
    v0 = addu(v0, v1);
    copy3(sp + 360, v0);  // the previous point: the newest sample
    s3 = 0;
    for (;;) {
        charge(5);
        v0 = lw(s5 + 0);
        v1 = lw(v0 + 12);
        v0 = slt(s3, v1);
        if (v0 == 0) break;
        backedge();
        charge(9);
        a0 = s5;
        mov_s(F12, F20);
        a1 = addiu(sp, 408);
        a2 = addiu(sp, 412);
        jal(0x1eaef0u, gen::fn_sub_1E7F90_001e7f90);
        a0 = lw(sp + 408);
        if (a0 != s6) load_segment(s6, false, s5, s5);
        charge(66);
        lwc1(F2, sp + 412);
        v0 = lui(0x3f80);
        mtc1(v0, F0);
        sub_s(F1, F0, F2);
        bezier3(sp + 376, F2, F1, F6, F5, F4, F3, false);
        if (s3 == 0) {
            charge(4);
            v0 = ld(sp + 376);
            lwc1(F0, sp + 384);
            sd(sp + 312, v0);
            swc1(F0, sp + 320);
        }
        charge(62);
        billboard_dir(sp + 376, sp + 360, F23, F22, false, 0x1eb150u, 0x1eb188u, 0x1eb1d4u);
        charge(43);
        billboard_emit(sp + 376, s2);
        s2 = addiu(s2, 36);
        v0 = ld(sp + 376);
        lwc1(F0, sp + 384);
        sd(sp + 360, v0);
        swc1(F0, sp + 368);
        add_s(F20, F20, F21);
        s3 = addiu(s3, 1);
    }
    charge(13);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    s3 = addiu(v0, 6);  // vertex count
    v1 = addiu(s3, -3);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    s2 = addu(s0, v0);  // the end cap
    v1 = lw(s5 + 8);
    v0 = lw(s5 + 12);
    a0 = subu(v0, v1);
    if (!bgez(a0)) {
        charge(1);
        a0 = addu(a0, v1);
    }
    charge(73);
    v0 = sll(a0, 1);
    v0 = addu(v0, a0);
    v1 = sll(v0, 2);
    v0 = lw(s5 + 16);
    v0 = addu(v0, v1);
    copy3(sp + 376, v0);  // the oldest sample
    billboard_dir(sp + 376, sp + 360, F21, F20, false, 0x1eb37cu, 0x1eb3b4u, 0x1eb400u);
    charge(67);
    billboard_emit(sp + 376, s2);
    v0 = sll(s3, 1);
    v0 = addu(v0, s3);
    v0 = sll(v0, 2);
    v1 = addu(v0, s0);
    sum3(v1 - 12, v1 - 36, v1 - 24, F1);
    v0 = lui(0x3f00);
    mtc1(v0, F1);
    scale3(v1 - 12, F1);
    v0 = lw(s5 + 12);
    v1 = addiu(v0, -1);
    if (!bgez(v1)) {
        charge(2);
        v0 = lw(s5 + 8);
        v1 = addu(v1, v0);
    }
    charge(73);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v1 = sll(v0, 2);
    v0 = lw(s5 + 16);
    v0 = addu(v0, v1);
    copy3(sp + 296, v0);  // the newest sample
    billboard_dir(sp + 296, sp + 312, F21, F20, true, 0x1eb5c4u, 0x1eb5fcu, 0x1eb648u);
    charge(65);
    billboard_emit(sp + 296, s0);
    sum3(s0 + 24, s0 + 0, s0 + 12, F1);
    v0 = lui(0x3f00);
    mtc1(v0, F1);
    scale3(s0 + 24, F1);
    v1 = addiu(s0, 60);
    a0 = 0;
    v0 = lui(0x3e80);
    mtc1(v0, F1);
    for (;;) {
        charge(5);
        v0 = lw(s5 + 0);
        v0 = lw(v0 + 12);
        v0 = slt(a0, v0);
        if (v0 == 0) break;
        backedge();
        charge(47);
        smooth(v1);
        a0 = addiu(a0, 1);
        v1 = addiu(v1, 36);
    }
}

// =========================================================================================================
// Effect manager (0x320060-0x324158)
// =========================================================================================================

// sub_320060 [type table 0x69BB10 entry 2, slot 0]: the address of the record at 0x957260.
void Cpu::sub_320060() {
    enter(4);
    v0 = lui(0x95);
    v0 = addiu(v0, 29280);  // 0x957260
}

// nullsub_106 [type table entry 2, slot 3]: nothing.
void Cpu::nullsub_106() { enter(2); }

// The keyframe track walks of sub_320080 / sub_320380 / sub_3204A0 / sub_320640: once the track function of a slot
// returned its value ($v0), the slot's apply function (+12) runs on it and every element of the effect's element
// array (effect +80: +0 the element pointers, +4 the u16 count). All calls go through `jalr` with the original frame.

// sub_320080 [apply two effects' tracks to the first one's elements]: $a0 / $a1 effects whose element arrays
// (+80) must be the same, $f12..$f14 the time arguments. For each of the four track slots k of the type table
// 0x69BB10 (16-byte entries {f(t), f(t, u, v), f(t, &track, u), apply(value, element)}) with an apply function
// and a track in both effects (+12 + 16k nonzero): if the second effect's track is set, value = entry[1](f12, f13,
// f14), else value = entry[2](f12, &first effect +64, f14 in $f13); then apply(value, element) for every element.
void Cpu::sub_320080() {
    enter(22);
    sp = addiu(sp, -160);
    sd(sp + 144, ra);
    sq(sp + 128, s7);
    sq(sp + 112, s6);
    sq(sp + 96, s5);
    sq(sp + 80, s4);
    sq(sp + 64, s3);
    sq(sp + 48, s2);
    sq(sp + 32, s1);
    sq(sp + 16, s0);
    swc1(F22, sp + 8);
    swc1(F21, sp + 4);
    swc1(F20, sp + 0);
    s5 = a0;
    mov_s(F22, F12);
    s7 = a1;
    mov_s(F21, F13);
    mov_s(F20, F14);
    s1 = lw(a0 + 80);  // the element array
    v1 = lw(a1 + 80);
    if (s1 == v1) {
        charge(4);
        s0 = lhu(s1 + 4);  // element count
        s4 = 0;            // slot k
        for (;;) {
            charge(3);
            v1 = sltiu(s4, 4);
            if (v1 == 0) break;
            backedge();
            charge(7);
            a1 = sll(s4, 4);
            v1 = lui(0x6a);
            v1 = addiu(v1, -17648);  // 0x69BB10
            s2 = addu(v1, a1);       // the slot's entry
            v1 = lw(s2 + 12);
            if (v1 != 0) {
                charge(4);
                a0 = addu(s5, a1);
                v1 = lw(a0 + 12);
                if (v1 != 0) {
                    charge(4);
                    a1 = addu(s7, a1);
                    v0 = lw(a1 + 12);
                    if (v0 != 0) {
                        charge(10);
                        mov_s(F12, F22);
                        mov_s(F13, F21);
                        mov_s(F14, F20);
                        v0 = lw(s2 + 4);
                        jalr(0x320134u, v0);
                        s6 = v0;
                        s3 = 0;
                        for (;;) {
                            charge(3);
                            v1 = sltu(s3, s0);
                            if (v1 == 0) break;
                            backedge();
                            charge(9);
                            v1 = sll(s3, 2);
                            v0 = lw(s1 + 0);
                            v0 = addu(v0, v1);
                            a0 = s6;
                            a1 = lw(v0 + 0);
                            v0 = lw(s2 + 12);
                            jalr(0x320164u, v0);
                            s3 = addiu(s3, 1);
                        }
                        charge(2);
                    } else {
                        charge(10);
                        mov_s(F12, F22);
                        a1 = addiu(s5, 64);
                        mov_s(F13, F20);
                        v0 = lw(s2 + 8);
                        jalr(0x320194u, v0);
                        s6 = v0;
                        s3 = 0;
                        for (;;) {
                            charge(3);
                            v1 = sltu(s3, s0);
                            if (v1 == 0) break;
                            backedge();
                            charge(9);
                            v1 = sll(s3, 2);
                            v0 = lw(s1 + 0);
                            v0 = addu(v0, v1);
                            a0 = s6;
                            a1 = lw(v0 + 0);
                            v0 = lw(s2 + 12);
                            jalr(0x3201c4u, v0);
                            s3 = addiu(s3, 1);
                        }
                    }
                }
            }
            charge(1);
            s4 = addiu(s4, 1);
        }
    }
    charge(15);
    ra = ld(sp + 144);
    lq(s7, sp + 128);
    lq(s6, sp + 112);
    lq(s5, sp + 96);
    lq(s4, sp + 80);
    lq(s3, sp + 64);
    lq(s2, sp + 48);
    lq(s1, sp + 32);
    lq(s0, sp + 16);
    lwc1(F22, sp + 8);
    lwc1(F21, sp + 4);
    lwc1(F20, sp + 0);
    sp = addiu(sp, 160);
}

// sub_320380 [apply the tracks of a list of effects, one time argument]: $a0 the list head (+0 the first effect,
// effects linked through +84), $f12 the time. Per effect and per slot k with an apply function and a track:
// value = entry[0](f12), apply(value, element) for every element.
void Cpu::sub_320380() {
    enter(14);
    sp = addiu(sp, -144);
    sd(sp + 128, ra);
    sq(sp + 112, s6);
    sq(sp + 96, s5);
    sq(sp + 80, s4);
    sq(sp + 64, s3);
    sq(sp + 48, s2);
    sq(sp + 32, s1);
    sq(sp + 16, s0);
    swc1(F20, sp + 0);
    mov_s(F20, F12);
    s5 = lw(a0 + 0);
    for (;;) {
        charge(2);
        if (s5 == 0) break;
        backedge();
        charge(5);
        s0 = lw(s5 + 80);
        s6 = lhu(s0 + 4);
        s4 = 0;
        for (;;) {
            charge(3);
            v1 = sltiu(s4, 4);
            if (v1 == 0) break;
            backedge();
            charge(7);
            a0 = sll(s4, 4);
            v1 = lui(0x6a);
            v1 = addiu(v1, -17648);
            s1 = addu(v1, a0);
            v1 = lw(s1 + 12);
            if (v1 != 0) {
                charge(4);
                a0 = addu(s5, a0);
                v1 = lw(a0 + 12);
                if (v1 != 0) {
                    charge(8);
                    mov_s(F12, F20);
                    v0 = lw(s1 + 0);
                    jalr(0x320400u, v0);
                    s2 = v0;
                    s3 = 0;
                    for (;;) {
                        charge(3);
                        v1 = sltu(s3, s6);
                        if (v1 == 0) break;
                        backedge();
                        charge(9);
                        v1 = sll(s3, 2);
                        v0 = lw(s0 + 0);
                        v0 = addu(v0, v1);
                        a0 = s2;
                        a1 = lw(v0 + 0);
                        v0 = lw(s1 + 12);
                        jalr(0x320430u, v0);
                        s3 = addiu(s3, 1);
                    }
                }
            }
            charge(1);
            s4 = addiu(s4, 1);
        }
        charge(1);
        s5 = lw(s5 + 84);
    }
    charge(12);
    ra = ld(sp + 128);
    lq(s6, sp + 112);
    lq(s5, sp + 96);
    lq(s4, sp + 80);
    lq(s3, sp + 64);
    lq(s2, sp + 48);
    lq(s1, sp + 32);
    lq(s0, sp + 16);
    lwc1(F20, sp + 0);
    sp = addiu(sp, 144);
}

// sub_3204A0 [apply the tracks of a list of effects, three time arguments]: $a0 the list head, $f12..$f14. Per
// effect: the first effect of the list (from the head again) with the same element array -- found: sub_320080
// (this effect, that effect); else per slot value = entry[2](f12, &effect +64, f14 in $f13) applied to every element.
void Cpu::sub_3204A0() {
    enter(20);
    sp = addiu(sp, -160);
    sd(sp + 144, ra);
    sq(sp + 128, s7);
    sq(sp + 112, s6);
    sq(sp + 96, s5);
    sq(sp + 80, s4);
    sq(sp + 64, s3);
    sq(sp + 48, s2);
    sq(sp + 32, s1);
    sq(sp + 16, s0);
    swc1(F22, sp + 8);
    swc1(F21, sp + 4);
    swc1(F20, sp + 0);
    s5 = a0;
    mov_s(F22, F12);
    mov_s(F21, F13);
    mov_s(F20, F14);
    s4 = lw(a0 + 0);
    for (;;) {
        charge(2);
        if (s4 == 0) break;
        backedge();
        charge(4);
        s1 = lw(s4 + 80);
        a1 = lw(s5 + 0);
        bool found = false;
        for (;;) {
            charge(2);
            if (a1 == 0) break;
            backedge();
            charge(3);
            v1 = lw(a1 + 80);
            if (v1 == s1) {
                charge(2);
                found = true;
                break;
            }
            charge(1);
            a1 = lw(a1 + 84);
        }
        if (!found) {
            charge(1);
            a1 = 0;
        }
        charge(2);
        if (a1 != 0) {
            charge(8);
            a0 = s4;
            mov_s(F12, F22);
            mov_s(F13, F21);
            mov_s(F14, F20);
            jal_here(0x32053cu, &Cpu::sub_320080);
        } else {
            charge(4);
            s7 = lhu(s1 + 4);
            s3 = 0;
            for (;;) {
                charge(3);
                v1 = sltiu(s3, 4);
                if (v1 == 0) break;
                backedge();
                charge(7);
                a0 = sll(s3, 4);
                v1 = lui(0x6a);
                v1 = addiu(v1, -17648);
                s0 = addu(v1, a0);
                v1 = lw(s0 + 12);
                if (v1 != 0) {
                    charge(4);
                    a0 = addu(s4, a0);
                    v1 = lw(a0 + 12);
                    if (v1 != 0) {
                        charge(10);
                        mov_s(F12, F22);
                        a1 = addiu(s4, 64);
                        mov_s(F13, F20);
                        v0 = lw(s0 + 8);
                        jalr(0x320598u, v0);
                        s6 = v0;
                        s2 = 0;
                        for (;;) {
                            charge(3);
                            v1 = sltu(s2, s7);
                            if (v1 == 0) break;
                            backedge();
                            charge(9);
                            v1 = sll(s2, 2);
                            v0 = lw(s1 + 0);
                            v0 = addu(v0, v1);
                            a0 = s6;
                            a1 = lw(v0 + 0);
                            v0 = lw(s0 + 12);
                            jalr(0x3205c8u, v0);
                            s2 = addiu(s2, 1);
                        }
                    }
                }
                charge(1);
                s3 = addiu(s3, 1);
            }
        }
        charge(1);
        s4 = lw(s4 + 84);
    }
    charge(15);
    ra = ld(sp + 144);
    lq(s7, sp + 128);
    lq(s6, sp + 112);
    lq(s5, sp + 96);
    lq(s4, sp + 80);
    lq(s3, sp + 64);
    lq(s2, sp + 48);
    lq(s1, sp + 32);
    lq(s0, sp + 16);
    lwc1(F22, sp + 8);
    lwc1(F21, sp + 4);
    lwc1(F20, sp + 0);
    sp = addiu(sp, 160);
}

// sub_320640 [apply the tracks of a list of effects, two time arguments]: $a0 the list head, $f12 / $f13. Per
// effect and slot: value = entry[2](f12, &effect +64, f13), applied to every element.
void Cpu::sub_320640() {
    enter(16);
    sp = addiu(sp, -144);
    sd(sp + 128, ra);
    sq(sp + 112, s6);
    sq(sp + 96, s5);
    sq(sp + 80, s4);
    sq(sp + 64, s3);
    sq(sp + 48, s2);
    sq(sp + 32, s1);
    sq(sp + 16, s0);
    swc1(F21, sp + 4);
    swc1(F20, sp + 0);
    mov_s(F21, F12);
    mov_s(F20, F13);
    s5 = lw(a0 + 0);
    for (;;) {
        charge(2);
        if (s5 == 0) break;
        backedge();
        charge(5);
        s0 = lw(s5 + 80);
        s6 = lhu(s0 + 4);
        s4 = 0;
        for (;;) {
            charge(3);
            v1 = sltiu(s4, 4);
            if (v1 == 0) break;
            backedge();
            charge(7);
            a0 = sll(s4, 4);
            v1 = lui(0x6a);
            v1 = addiu(v1, -17648);
            s1 = addu(v1, a0);
            v1 = lw(s1 + 12);
            if (v1 != 0) {
                charge(4);
                a0 = addu(s5, a0);
                v1 = lw(a0 + 12);
                if (v1 != 0) {
                    charge(10);
                    mov_s(F12, F21);
                    a1 = addiu(s5, 64);
                    mov_s(F13, F20);
                    v0 = lw(s1 + 8);
                    jalr(0x3206d0u, v0);
                    s2 = v0;
                    s3 = 0;
                    for (;;) {
                        charge(3);
                        v1 = sltu(s3, s6);
                        if (v1 == 0) break;
                        backedge();
                        charge(9);
                        v1 = sll(s3, 2);
                        v0 = lw(s0 + 0);
                        v0 = addu(v0, v1);
                        a0 = s2;
                        a1 = lw(v0 + 0);
                        v0 = lw(s1 + 12);
                        jalr(0x320700u, v0);
                        s3 = addiu(s3, 1);
                    }
                }
            }
            charge(1);
            s4 = addiu(s4, 1);
        }
        charge(1);
        s5 = lw(s5 + 84);
    }
    charge(13);
    ra = ld(sp + 128);
    lq(s6, sp + 112);
    lq(s5, sp + 96);
    lq(s4, sp + 80);
    lq(s3, sp + 64);
    lq(s2, sp + 48);
    lq(s1, sp + 32);
    lq(s0, sp + 16);
    lwc1(F21, sp + 4);
    lwc1(F20, sp + 0);
    sp = addiu(sp, 144);
}

// sub_320770 [copy each effect's colour and vector to its elements]: $a0 the list head. For every effect (+84
// links) and every element of its array (+80): element +4..+7 = effect +64..+67 (RGBA bytes), element +12..+20 =
// effect +68..+76 (three floats).
void Cpu::sub_320770() {
    enter(3);
    t4 = lw(a0 + 0);
    for (;;) {
        charge(2);
        if (t4 == 0) break;
        backedge();
        charge(5);
        t2 = lw(t4 + 80);
        t1 = lhu(t2 + 4);
        t3 = 0;
        for (;;) {
            charge(3);
            v1 = sltu(t3, t1);
            if (v1 == 0) break;
            backedge();
            charge(22);
            t0 = sll(t3, 2);
            v1 = lw(t2 + 0);
            v1 = addu(v1, t0);
            a3 = lw(v1 + 0);  // the element
            a2 = lbu(t4 + 64);
            a1 = lbu(t4 + 65);
            a0 = lbu(t4 + 66);
            v1 = lbu(t4 + 67);
            sb(a3 + 4, a2);
            sb(a3 + 5, a1);
            sb(a3 + 6, a0);
            sb(a3 + 7, v1);
            v1 = lw(t2 + 0);
            v1 = addu(v1, t0);
            v1 = lw(v1 + 0);
            lwc1(F2, t4 + 68);
            lwc1(F1, t4 + 72);
            lwc1(F0, t4 + 76);
            swc1(F2, v1 + 12);
            swc1(F1, v1 + 16);
            swc1(F0, v1 + 20);
            t3 = addiu(t3, 1);
        }
        charge(1);
        t4 = lw(t4 + 84);
    }
    charge(2);
}

// sub_320810 [the longest track of a list]: $a0 the list head; $f0 = the largest track length (slot +4, a float)
// over the slots with a track (+12 nonzero) of every effect, starting from 0.0 (`c.le.s` keeps the first of equals).
void Cpu::sub_320810() {
    enter(4);
    mtc1(zero, F0);
    a1 = lw(a0 + 0);
    for (;;) {
        charge(2);
        if (a1 == 0) break;
        backedge();
        charge(3);
        a0 = 0;
        for (;;) {
            charge(3);
            v0 = sltiu(a0, 4);
            if (v0 == 0) break;
            backedge();
            charge(5);
            v0 = sll(a0, 4);
            v1 = addu(a1, v0);
            v0 = lw(v1 + 12);
            if (v0 != 0) {
                charge(4);
                lwc1(F1, v1 + 4);
                c_le_s(F1, F0);
                if (!bc1t()) {
                    charge(1);
                    mov_s(F0, F1);
                }
            }
            charge(1);
            a0 = addiu(a0, 1);
        }
        charge(1);
        a1 = lw(a1 + 84);
    }
    charge(2);
}

// sub_320BA0 [material callback: register the material when it carries the named string]: $a0 the material, $a1
// a record {+0 the list (sub_321070 appends), +4 the wanted string}. For every user-data array of the material whose
// name is the string at gp-25296 and every element of format 3 (string) equal to the wanted string: append the
// material to the list and return 0 (stop). Returns the material otherwise.
void Cpu::sub_320BA0() {
    enter(17);
    sp = addiu(sp, -128);
    sd(sp + 112, ra);
    sq(sp + 96, s6);
    sq(sp + 80, s5);
    sq(sp + 64, s4);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp + 0, s0);
    s4 = a0;
    s3 = a1;
    jal(0x320bccu, gen::fn_sub_48EE80_0048ee80);
    s5 = v0;
    s2 = 0;
    bool stop = false;
    for (;;) {
        charge(3);
        v0 = slt(s2, s5);
        if (v0 == 0) break;
        backedge();
        charge(14);
        a0 = s4;
        a1 = s2;
        jal(0x320becu, gen::fn_sub_48EED0_0048eed0);
        s0 = v0;
        a0 = s0;
        jal(0x320bfcu, gen::fn_name__C9type_info_0_0048ef10);
        a0 = v0;
        a1 = gpa(-25296);
        jal(0x320c0cu, gen::fn_strcmp_00524128);
        if (v0 == 0) {
            charge(7);
            a0 = s0;
            jal(0x320c20u, gen::fn_sub_48EF30_0048ef30);
            s6 = v0;
            s1 = 0;
            for (;;) {
                charge(3);
                v0 = slt(s1, s6);
                if (v0 == 0) break;
                backedge();
                charge(6);
                a0 = s0;
                jal(0x320c3cu, gen::fn_sub_48EF20_0048ef20);
                v1 = 3;
                if (v0 == v1) {
                    charge(10);
                    a0 = s0;
                    a1 = s1;
                    jal(0x320c58u, gen::fn_sub_48EF80_0048ef80);
                    a0 = lw(s3 + 4);
                    a1 = v0;
                    jal(0x320c68u, gen::fn_strcmp_00524128);
                    if (v0 == 0) {
                        charge(7);
                        a0 = lw(s3 + 0);
                        a1 = s4;
                        jal_here(0x320c80u, &Cpu::sub_321070);
                        v0 = 0;
                        stop = true;
                        break;
                    }
                }
                charge(1);
                s1 = addiu(s1, 1);
            }
            if (stop) break;
        }
        charge(1);
        s2 = addiu(s2, 1);
    }
    if (!stop) {
        charge(1);
        v0 = s4;
    }
    charge(11);
    ra = ld(sp + 112);
    lq(s6, sp + 96);
    lq(s5, sp + 80);
    lq(s4, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp + 0);
    sp = addiu(sp, 128);
}

// sub_320CF0 [atomic callback: collect the geometry's materials that carry the string]: $a0 the atomic, $a1 the
// record of sub_320BA0. For each material of the geometry (atomic +24: +32 the material pointers, +36 the count)
// until sub_320BA0 stops: then the geometry's flags (+8) get 0x40. Returns the atomic.
void Cpu::sub_320CF0() {
    enter(14);
    sp = addiu(sp, -96);
    sd(sp + 80, ra);
    sq(sp + 64, s4);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp + 0, s0);
    s4 = a0;
    s3 = a1;
    s1 = lw(a0 + 24);  // the geometry
    s0 = lw(s1 + 36);
    s2 = 0;
    for (;;) {
        charge(3);
        v0 = slt(s2, s0);
        if (v0 == 0) break;
        backedge();
        charge(9);
        v1 = sll(s2, 2);
        v0 = lw(s1 + 32);
        v0 = addu(v0, v1);
        a0 = lw(v0 + 0);
        a1 = s3;
        jal_here(0x320d3cu, &Cpu::sub_320BA0);
        if (v0 == 0) {
            charge(5);
            v0 = lw(s1 + 8);
            v0 = ori(v0, 0x40);
            sw(s1 + 8, v0);
            break;
        }
        charge(1);
        s2 = addiu(s2, 1);
    }
    charge(10);
    v0 = s4;
    ra = ld(sp + 80);
    lq(s4, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp + 0);
    sp = addiu(sp, 96);
}

// sub_320DA0 [collect a clump's tagged materials]: sub_4916D0(clump, sub_320CF0, record); returns the clump.
void Cpu::sub_320DA0() {
    enter(15);
    sp = addiu(sp, -32);
    sd(sp + 16, ra);
    sq(sp + 0, s0);
    s0 = a0;
    a2 = a1;
    a1 = lui(0x32);
    a1 = addiu(a1, 3312);  // sub_320CF0
    jal(0x320dbcu, gen::fn_sub_4916D0_004916d0);
    v0 = s0;
    ra = ld(sp + 16);
    lq(s0, sp + 0);
    sp = addiu(sp, 32);
}

// sub_320DE0 [atomic callback: count the materials that carry a string]: $a0 the atomic, $a1 a record {+0 the
// wanted string, +4 u16 count}. For every material of the geometry and every user-data array named as the string at
// gp-25296: the first string element equal to the wanted one adds 1 to the count. Returns the atomic.
void Cpu::sub_320DE0() {
    enter(18);
    sp = addiu(sp, -192);
    sd(sp + 144, ra);
    sq(sp + 128, s8);
    sq(sp + 112, s7);
    sq(sp + 96, s6);
    sq(sp + 80, s5);
    sq(sp + 64, s4);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp + 0, s0);
    s7 = a0;
    s4 = a1;
    s6 = lw(a0 + 24);  // the geometry
    s8 = lw(s6 + 36);
    s2 = 0;
    for (;;) {
        charge(3);
        v0 = slt(s2, s8);
        if (v0 == 0) break;
        backedge();
        charge(11);
        v1 = sll(s2, 2);
        v0 = lw(s6 + 32);
        v0 = addu(v0, v1);
        s5 = lw(v0 + 0);  // the material
        a0 = s5;
        jal(0x320e3cu, gen::fn_sub_48EE80_0048ee80);
        sq(sp + 176, v0);  // its array count (spilled whole)
        s1 = 0;
        for (;;) {
            charge(4);
            lq(v0, sp + 176);
            v0 = slt(s1, v0);
            if (v0 == 0) break;
            backedge();
            charge(14);
            a0 = s5;
            a1 = s1;
            jal(0x320e5cu, gen::fn_sub_48EED0_0048eed0);
            s3 = v0;
            a0 = s3;
            jal(0x320e6cu, gen::fn_name__C9type_info_0_0048ef10);
            a0 = v0;
            a1 = gpa(-25296);
            jal(0x320e7cu, gen::fn_strcmp_00524128);
            if (v0 == 0) {
                charge(7);
                a0 = s3;
                jal(0x320e90u, gen::fn_sub_48EF30_0048ef30);
                sq(sp + 160, v0);
                s0 = 0;
                for (;;) {
                    charge(4);
                    lq(v0, sp + 160);
                    v0 = slt(s0, v0);
                    if (v0 == 0) break;
                    backedge();
                    charge(6);
                    a0 = s3;
                    jal(0x320eacu, gen::fn_sub_48EF20_0048ef20);
                    v1 = 3;
                    if (v0 == v1) {
                        charge(10);
                        a0 = s3;
                        a1 = s0;
                        jal(0x320ec8u, gen::fn_sub_48EF80_0048ef80);
                        a0 = lw(s4 + 0);
                        a1 = v0;
                        jal(0x320ed8u, gen::fn_strcmp_00524128);
                        if (v0 == 0) {
                            charge(5);
                            v0 = lhu(s4 + 4);
                            v0 = addiu(v0, 1);
                            sh(s4 + 4, v0);
                            break;
                        }
                    }
                    charge(1);
                    s0 = addiu(s0, 1);
                }
            }
            charge(1);
            s1 = addiu(s1, 1);
        }
        charge(1);
        s2 = addiu(s2, 1);
    }
    charge(14);
    v0 = s7;
    ra = ld(sp + 144);
    lq(s8, sp + 128);
    lq(s7, sp + 112);
    lq(s6, sp + 96);
    lq(s5, sp + 80);
    lq(s4, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp + 0);
    sp = addiu(sp, 192);
}

// sub_320F70 [count a clump's materials that carry a string]: the record {string, 0} on the frame at sp+24,
// sub_4916D0(clump, sub_320DE0, record); returns the u16 count.
void Cpu::sub_320F70() {
    enter(14);
    sp = addiu(sp, -32);
    sd(sp + 0, ra);
    sw(sp + 24, a1);
    sh(sp + 28, zero);
    a1 = lui(0x32);
    a1 = addiu(a1, 3552);  // sub_320DE0
    a2 = addiu(sp, 24);
    jal(0x320f8cu, gen::fn_sub_4916D0_004916d0);
    v0 = lhu(sp + 28);
    ra = ld(sp + 0);
    sp = addiu(sp, 32);
}

// sub_321050 [reference count +1]: the u16 at +8; returns the object.
void Cpu::sub_321050() {
    enter(6);
    v0 = lhu(a0 + 8);
    v0 = addiu(v0, 1);
    sh(a0 + 8, v0);
    v0 = a0;
}

// sub_321070 [append to a pointer list]: list {+0 the array, +4 u16 count}: array[count++] = $a1.
void Cpu::sub_321070() {
    enter(10);
    v1 = lhu(a0 + 4);
    a2 = sll(v1, 2);
    v1 = lw(a0 + 0);
    v1 = addu(v1, a2);
    sw(v1 + 0, a1);
    v1 = lhu(a0 + 4);
    v1 = addiu(v1, 1);
    sh(a0 + 4, v1);
}

// sub_3210A0 [effect texture by id]: the word at 0x957A20 + 4 * (u16)id.
void Cpu::sub_3210A0() {
    enter(8);
    v0 = andi(a0, 0xffff);
    v1 = sll(v0, 2);
    v0 = lui(0x95);
    v0 = addiu(v0, 31264);  // 0x957A20
    v0 = addu(v0, v1);
    v0 = lw(v0 + 0);
}

// sub_3210C0 [texture from an image]: uttmxCreateRaster($a0 passed on), the texture of that raster (sub_4D0E40);
// its filter byte (+80, low 8 bits) = 2 and address bytes (bits 8..15) = 0x11. Returns the texture.
void Cpu::sub_3210C0() {
    enter(21);
    sp = addiu(sp, -16);
    sd(sp + 0, ra);
    jal(0x3210c8u, gen::fn_uttmxCreateRaster_0010e880);
    a0 = v0;
    jal(0x3210d4u, gen::fn_sub_4D0E40_004d0e40);
    a0 = lw(v0 + 80);
    v1 = si(-256);
    v1 = and_(a0, v1);
    a0 = ori(v1, 0x2);
    sw(v0 + 80, a0);
    v1 = lui(0xffff);
    v1 = ori(v1, 0xff);
    v1 = and_(a0, v1);
    v1 = ori(v1, 0x1100);
    sw(v0 + 80, v1);
    ra = ld(sp + 0);
    sp = addiu(sp, 16);
}

// sub_321120 / sub_321130 [the current layer bank]: the u16 at gp-25288, set / get.
void Cpu::sub_321120() {
    enter(3);
    sh(gpa(-25288), a0);
}
void Cpu::sub_321130() {
    enter(3);
    v0 = lhu(gpa(-25288));
}

// sub_321140 .. sub_3212E0 [push an object on a layer list]: $a0 the object, $a1 the (u16) layer. The list head
// is table[bank][layer] (bank = the u16 at gp-25288, 7 words per bank; sub_321180 / sub_3211D0 use max(bank, 5));
// object->link = head; head = object. Tables and link offsets per function in fx_layers.h.
void Cpu::link_bank(u32 table, s32 link, bool at_least_5) {
    if (at_least_5) {
        enter(4);
        v1 = lhu(gpa(-25288));
        at = slti(v1, 5);
        if (at != 0) {
            charge(1);
            v1 = 5;
        }
        charge(15);
        a3 = andi(v1, 0xffff);
        v1 = andi(a1, 0xffff);
        a2 = sll(v1, 2);
        v1 = sll(a3, 3);
        v1 = subu(v1, a3);
        a1 = sll(v1, 2);  // bank * 28
    } else {
        enter(15);
        v1 = andi(a1, 0xffff);
        a2 = sll(v1, 2);
        a1 = lhu(gpa(-25288));
        v1 = sll(a1, 3);
        v1 = subu(v1, a1);
        a1 = sll(v1, 2);
    }
    v1 = lui(0x95);
    v1 = addiu(v1, static_cast<s32>(table - 0x950000u));
    v1 = addu(v1, a1);
    a1 = addu(v1, a2);  // &head
    v1 = lw(a1 + 0);
    sw(a0 + link, v1);
    sw(a1 + 0, a0);
}

// sub_321320 [set the effect view matrix]: copy 64 bytes from $a0 to 0x9572E0 (eight double-word moves as two
// words each); the word at gp-18352 = 1 (matrix valid).
void Cpu::sub_321320() {
    enter(3);
    a3 = lui(0x95);
    a3 = addiu(a3, 29408);  // 0x9572E0
    a2 = 8;
    do {
        charge(9);
        a1 = lw(a0 + 0);
        v1 = lw(a0 + 4);
        a0 = addiu(a0, 8);
        a2 = addiu(a2, -1);
        sw(a3 + 0, a1);
        sw(a3 + 4, v1);
        a3 = addiu(a3, 8);
        if (!bgtz(a2)) break;
        backedge();
    } while (true);
    charge(4);
    v1 = 1;
    sw(gpa(-18352), v1);
}

// effMng_UpdateEffectProgramTask [effMng_UpdateEffectProgramTask, bands.sym]: the update of the kwlnTask "effect_program": the effect
// program and effect object steps (sub_350110, sub_347D60, EPL band); when the word at 0x9572D0 is set, the field
// camera gets the two 2-D vectors at 0x9572B0 / 0x9572C0 (sub_4944B0) and its frame the matrix at 0x957270
// (sub_4CB7F0, replace), and the word is cleared. Returns 0.
void Cpu::effMng_UpdateEffectProgramTask() {
    enter(10);
    sp = addiu(sp, -16);
    sd(sp + 0, ra);
    jal(0x321a68u, gen::fn_sub_350110_00350110);
    jal(0x321a70u, gen::fn_sub_347D60_00347d60);
    v0 = lui(0x95);
    v0 = lw(v0 + 29392);  // 0x9572D0
    if (v0 != 0) {
        charge(24);
        jal(0x321a88u, gen::fn_sub_198560_00198560);
        a0 = v0;
        a1 = lui(0x95);
        a1 = addiu(a1, 29360);  // 0x9572B0
        jal(0x321a9cu, gen::fn_sub_4944B0_004944b0);
        jal(0x321aa4u, gen::fn_sub_198580_00198580);
        a0 = v0;
        a1 = lui(0x95);
        a1 = addiu(a1, 29376);  // 0x9572C0
        jal(0x321ab8u, gen::fn_sub_4944B0_004944b0);
        jal(0x321ac0u, gen::fn_sub_198580_00198580);
        a0 = lw(v0 + 4);
        a1 = lui(0x95);
        a1 = addiu(a1, 29296);  // 0x957270
        a2 = 0;
        jal(0x321ad8u, gen::fn_sub_4CB7F0_004cb7f0);
        v0 = lui(0x95);
        sw(v0 + 29392, zero);
    }
    charge(5);
    v0 = 0;
    ra = ld(sp + 0);
    sp = addiu(sp, 16);
}

// effMng_UpdateEffect3dTask [effMng_UpdateEffect3dTask] / effMng_UpdateEffect2dTask [effMng_UpdateEffect2dTask] / sub_321FE0: the layer task
// updates -- sub_321360(bank 2 / 5 / 8) draws the bank; the first two return 0.
void Cpu::layer_task(u32 pc, u64 layer, bool zero_v0) {
    enter(zero_v0 ? 10 : 9);
    sp = addiu(sp, -16);
    sd(sp + 0, ra);
    a0 = layer;
    jal(pc, gen::fn_sub_321360_00321360);
    if (zero_v0) v0 = 0;
    ra = ld(sp + 0);
    sp = addiu(sp, 16);
}

// sub_321F10 [clear a bank of every layer list]: the seven heads of bank (u16)$a0 in each of the seven tables.
void Cpu::sub_321F10() {
    enter(28);
    a3 = 0;
    a0 = andi(a0, 0xffff);
    v1 = sll(a0, 3);
    v1 = subu(v1, a0);
    t1 = sll(v1, 2);  // bank * 28
    v1 = lui(0x95);
    v1 = addiu(v1, 31008);
    a2 = addu(v1, t1);
    v1 = lui(0x95);
    v1 = addiu(v1, 29472);
    a1 = addu(v1, t1);
    v1 = lui(0x95);
    v1 = addiu(v1, 30240);
    a0 = addu(v1, t1);
    v1 = lui(0x95);
    v1 = addiu(v1, 29984);
    v1 = addu(v1, t1);
    t0 = lui(0x95);
    t0 = addiu(t0, 29728);
    t4 = addu(t0, t1);
    t0 = lui(0x95);
    t0 = addiu(t0, 30752);
    t3 = addu(t0, t1);
    t0 = lui(0x95);
    t0 = addiu(t0, 30496);
    t2 = addu(t0, t1);
    for (;;) {
        charge(4);
        t0 = andi(a3, 0xffff);
        t0 = slti(t0, 7);
        if (t0 == 0) break;
        backedge();
        charge(18);
        t0 = andi(a3, 0xffff);
        t1 = sll(t0, 2);
        t0 = addu(a2, t1);
        sw(t0 + 0, zero);
        t0 = addu(a1, t1);
        sw(t0 + 0, zero);
        t0 = addu(a0, t1);
        sw(t0 + 0, zero);
        t0 = addu(v1, t1);
        sw(t0 + 0, zero);
        t0 = addu(t4, t1);
        sw(t0 + 0, zero);
        t0 = addu(t3, t1);
        sw(t0 + 0, zero);
        t0 = addu(t2, t1);
        sw(t0 + 0, zero);
        a3 = addiu(a3, 1);
        a3 = andi(a3, 0xffff);
    }
    charge(2);
}

// sub_3226B0 [start an animation of a sprite set]: $a0 the player {+0 the set, +4 flags, +8 the animation, +12
// the track count, +16 the 20-byte track states, +20 u16 running}, $a1 the animation index. The set {+0 the key
// base, +4 the 20-byte animation records {+0 key offset, +8 flags, +12 count, +16 flags}}. Flag 0x10000000: one
// track per entry of the animation's 24-byte key list (state = {0, the key's frame count (+18), the record, the
// keys}, then +4 = -(the entry's start delay)); else flags 0xC0: two tracks, this animation and the next; else one.
void Cpu::sub_3226B0() {
    enter(9);
    a3 = lw(a0 + 0);
    v1 = sll(a1, 2);
    v1 = addu(v1, a1);
    t2 = sll(v1, 2);  // index * 20
    v1 = lw(a3 + 4);
    a2 = addu(v1, t2);  // the animation record
    v1 = lw(a2 + 12);
    if (v1 == 0) {
        charge(2);
        return;
    }
    charge(5);
    v1 = lw(a2 + 16);
    t0 = lui(0x1000);
    v1 = and_(v1, t0);
    if (v1 != 0) {
        charge(10);
        sw(a0 + 4, t0);
        sw(a0 + 8, a1);
        v1 = lw(a2 + 12);
        sw(a0 + 12, v1);
        a1 = lw(a3 + 0);
        v1 = lw(a2 + 0);
        a1 = addu(a1, v1);  // the 24-byte entries
        t0 = 0;
        for (;;) {
            charge(4);
            v1 = lw(a2 + 12);
            v1 = sltu(t0, v1);
            if (v1 == 0) break;
            backedge();
            charge(29);
            v1 = sll(t0, 2);
            v1 = addu(v1, t0);
            v1 = sll(v1, 2);
            t1 = lw(a0 + 16);
            t5 = addu(t1, v1);  // track state i
            t1 = sll(t0, 1);
            t1 = addu(t1, t0);
            t1 = sll(t1, 3);
            t4 = addu(a1, t1);  // entry i
            t2 = lh(t4 + 0);
            t1 = sll(t2, 2);
            t1 = addu(t1, t2);
            t2 = sll(t1, 2);
            t1 = lw(a3 + 4);
            t3 = addu(t1, t2);  // its animation record
            t2 = lw(a3 + 0);
            t1 = lw(t3 + 0);
            t2 = addu(t2, t1);  // its keys
            sw(t5 + 4, zero);
            t1 = lh(t2 + 18);
            sw(t5 + 8, t1);
            sw(t5 + 12, t3);
            sw(t5 + 16, t2);
            t1 = lh(t4 + 2);
            t2 = negu(t1);
            t1 = lw(a0 + 16);
            v1 = addu(t1, v1);
            sw(v1 + 4, t2);
            t0 = addiu(t0, 1);
        }
        charge(2);
    } else {
        charge(4);
        a2 = lw(a2 + 8);
        v1 = andi(a2, 0xc0);
        if (v1 != 0) {
            charge(32);
            sw(a0 + 4, a2);
            sw(a0 + 8, a1);
            v1 = 2;
            sw(a0 + 12, v1);
            t1 = lw(a0 + 16);
            v1 = lw(a3 + 4);
            t0 = addu(v1, t2);
            a2 = lw(a3 + 0);
            v1 = lw(t0 + 0);
            a2 = addu(a2, v1);
            sw(t1 + 4, zero);
            v1 = lh(a2 + 18);
            sw(t1 + 8, v1);
            sw(t1 + 12, t0);
            sw(t1 + 16, a2);
            t0 = lw(a0 + 16);
            a1 = addiu(a1, 1);
            v1 = sll(a1, 2);
            v1 = addu(v1, a1);
            a1 = sll(v1, 2);
            v1 = lw(a3 + 4);
            a2 = addu(v1, a1);
            a1 = lw(a3 + 0);
            v1 = lw(a2 + 0);
            a1 = addu(a1, v1);
            sw(t0 + 24, zero);
            v1 = lh(a1 + 18);
            sw(t0 + 28, v1);
            sw(t0 + 32, a2);
            sw(t0 + 36, a1);
        } else {
            charge(15);
            sw(a0 + 4, zero);
            sw(a0 + 8, a1);
            v1 = 1;
            sw(a0 + 12, v1);
            t0 = lw(a0 + 16);
            v1 = lw(a3 + 4);
            a2 = addu(v1, t2);
            a1 = lw(a3 + 0);
            v1 = lw(a2 + 0);
            a1 = addu(a1, v1);
            sw(t0 + 4, zero);
            v1 = lh(a1 + 18);
            sw(t0 + 8, v1);
            sw(t0 + 12, a2);
            sw(t0 + 16, a1);
        }
    }
    charge(2);
    v1 = 1;
    sh(a0 + 20, v1);
    charge(2);
}

// sub_322AB0 [step one sprite track and fill its quad]: $a0 the player, $a1 the track state {+4 key, +8 frames
// left, +12 the animation record, +16 the 24-byte keys}, $a2 the quad record. Records flagged 0x10000000 are left
// alone. When the frames run out the key advances (past the end: flag 0x10 holds the last key and clears running
// (+20), else wraps to 0) and the frames reload from the key (+18). The quad: +44 the per-key word (record flag 1)
// or -1; +40 the blend mode (record flag 2 -> 2, 4 -> 3, else 1); the texture (key +16 -> the set's texture table
// +20) and its size (+12 / +16 as integers, converted); +16 key +20; +24..+36 the UV rectangle (key +8..+14 >> 4 over
// the texture size); +0..+12 the screen rectangle from the key's halves (+0, +2 position / 2, +4, +6 size).
void Cpu::sub_322AB0() {
    enter(7);
    v1 = lw(a0 + 0);
    a3 = lw(a1 + 12);
    t1 = lw(a3 + 16);
    t0 = lui(0x1000);
    t0 = and_(t1, t0);
    if (t0 == 0) {
        charge(3);
        t0 = lw(a1 + 8);
        if (bgtz(t0)) {
            charge(2);
            a0 = addiu(t0, -1);
            sw(a1 + 8, a0);
        } else {
            charge(7);
            t0 = lw(a1 + 4);
            t1 = addiu(t0, 1);
            sw(a1 + 4, t1);
            t0 = lw(a3 + 12);
            t0 = sltu(t1, t0);
            if (t0 == 0) {
                charge(4);
                t0 = lw(a3 + 16);
                t0 = andi(t0, 0x10);
                if (t0 != 0) {
                    charge(6);
                    sh(a0 + 20, zero);
                    a0 = lw(a3 + 12);
                    a0 = addiu(a0, -1);
                    sw(a1 + 4, a0);
                } else {
                    charge(1);
                    sw(a1 + 4, zero);
                }
            }
            charge(10);
            t1 = lw(a1 + 16);
            t0 = lw(a1 + 4);
            a0 = sll(t0, 1);
            a0 = addu(a0, t0);
            a0 = sll(a0, 3);
            a0 = addu(a0, t1);
            a0 = lh(a0 + 18);
            sw(a1 + 8, a0);
        }
        charge(10);
        t1 = lw(a1 + 4);
        a0 = sll(t1, 1);
        a0 = addu(a0, t1);
        t0 = sll(a0, 3);
        a0 = lw(a1 + 16);
        a0 = addu(a0, t0);  // the key
        a1 = lw(a3 + 16);
        a1 = andi(a1, 0x1);
        if (a1 != 0) {
            charge(8);
            t0 = lw(v1 + 0);
            a1 = lw(a3 + 4);
            t0 = addu(t0, a1);
            a1 = sll(t1, 2);
            a1 = addu(t0, a1);
            a1 = lw(a1 + 0);
        } else {
            charge(1);
            a1 = si(-1);
        }
        charge(15);
        sw(a2 + 44, a1);
        a1 = lh(a0 + 16);
        a1 = sll(a1, 2);
        v1 = lw(v1 + 20);
        v1 = addu(v1, a1);
        v1 = lw(v1 + 0);  // the texture
        a1 = lw(v1 + 0);  // its raster
        lwc1(F0, a1 + 12);
        cvt_s_w(F6, F0);  // width
        lwc1(F0, a1 + 16);
        cvt_s_w(F5, F0);  // height
        a3 = lw(a3 + 16);
        a1 = andi(a3, 0x2);
        if (a1 != 0) {
            charge(4);
            a1 = 2;
            sh(a2 + 40, a1);
        } else {
            charge(3);
            a1 = andi(a3, 0x4);
            if (a1 != 0) {
                charge(4);
                a1 = 3;
                sh(a2 + 40, a1);
            } else {
                charge(2);
                a1 = 1;
                sh(a2 + 40, a1);
            }
        }
        charge(60);
        lwc1(F0, a0 + 20);
        swc1(F0, a2 + 16);
        a1 = lh(a0 + 4);
        mtc1(a1, F0);
        cvt_s_w(F4, F0);
        a1 = lh(a0 + 6);
        mtc1(a1, F0);
        cvt_s_w(F3, F0);
        a1 = lh(a0 + 0);
        mtc1(a1, F0);
        cvt_s_w(F2, F0);
        a1 = lh(a0 + 2);
        mtc1(a1, F0);
        cvt_s_w(F1, F0);
        a1 = lh(a0 + 8);
        a1 = sra(a1, 4);
        mtc1(a1, F0);
        cvt_s_w(F0, F0);
        div_s(F0, F0, F6);
        swc1(F0, a2 + 24);
        a1 = lh(a0 + 10);
        a1 = sra(a1, 4);
        mtc1(a1, F0);
        cvt_s_w(F0, F0);
        div_s(F0, F0, F5);
        swc1(F0, a2 + 28);
        a1 = lh(a0 + 12);
        a1 = sra(a1, 4);
        mtc1(a1, F0);
        cvt_s_w(F0, F0);
        div_s(F0, F0, F6);
        swc1(F0, a2 + 32);
        a0 = lh(a0 + 14);
        a0 = sra(a0, 4);
        mtc1(a0, F0);
        cvt_s_w(F0, F0);
        div_s(F0, F0, F5);
        swc1(F0, a2 + 36);
        a0 = lui(0x4000);
        mtc1(a0, F0);  // 2.0
        div_s(F2, F2, F0);
        div_s(F1, F1, F0);
        sub_s(F0, F2, F4);
        swc1(F0, a2 + 0);
        sub_s(F0, F1, F3);
        swc1(F0, a2 + 4);
        swc1(F2, a2 + 8);
        swc1(F1, a2 + 12);
        swc1(F6, a2 + 48);
        swc1(F5, a2 + 52);
        sw(a2 + 20, v1);
    }
    charge(2);
}

// sub_322D10 [step a sprite's first track]: sub_322AB0(player, player +16 (the first state), quad $a1).
void Cpu::sub_322D10() {
    enter(10);
    sp = addiu(sp, -16);
    sd(sp + 0, ra);
    a2 = a1;
    a1 = lw(a0 + 16);
    jal_here(0x322d20u, &Cpu::sub_322AB0);
    ra = ld(sp + 0);
    sp = addiu(sp, 16);
}

// sub_322D40 [seek every track]: for each of the player's tracks: key = frame % (the record's key count, +12)
// (divu: HI/LO as the EE leaves them), frames left = 1.
void Cpu::sub_322D40() {
    enter(5);
    t0 = lw(a0 + 12);
    t1 = 0;
    a2 = 1;
    for (;;) {
        charge(3);
        v1 = slt(t1, t0);
        if (v1 == 0) break;
        backedge();
        charge(12);
        v1 = sll(t1, 2);
        v1 = addu(v1, t1);
        a3 = sll(v1, 2);
        v1 = lw(a0 + 16);
        a3 = addu(v1, a3);
        v1 = lw(a3 + 12);
        v1 = lw(v1 + 12);
        divu(a1, v1);
        mfhi(v1);
        sw(a3 + 4, v1);
        sw(a3 + 8, a2);
        t1 = addiu(t1, 1);
    }
    charge(2);
}

// sub_322DA0 [texture of a sprite set]: set->+20 [index].
void Cpu::sub_322DA0() {
    enter(7);
    v0 = lw(a0 + 0);
    v1 = sll(a1, 2);
    v0 = lw(v0 + 20);
    v0 = addu(v0, v1);
    v0 = lw(v0 + 0);
}

// sub_322FB0 [reference count +1]: the word at +28; returns the object.
void Cpu::sub_322FB0() {
    enter(6);
    v0 = lw(a0 + 28);
    v0 = addiu(v0, 1);
    sw(a0 + 28, v0);
    v0 = a0;
}

// sub_322FD0 [the frame of an image sequence at a time]: $a0 the sequence {+4 frame count, +8 flags (1 loop, 4 double
// size), +16 16-byte frame records {+0 duration}, +20 the textures, +24 total length}, $a1 the time, $a2 the output
// {+0 1.0, +4 1.0 or 2.0, +8 / +12 the texture size, +16 the texture}. One frame: frame 0. Looping: time % length;
// past the end without looping: the last frame; else the first frame whose running end reaches the time.
void Cpu::sub_322FD0() {
    enter(6);
    t1 = 0;
    t0 = si(-1);
    a3 = lw(a0 + 4);
    v1 = 1;
    if (a3 == v1) {
        charge(3);
        t0 = 0;
    } else {
        charge(4);
        v1 = lw(a0 + 8);
        v1 = andi(v1, 0x1);
        if (v1 != 0) {
            charge(5);
            v1 = lw(a0 + 24);
            divu(a1, v1);
            mfhi(t1);
        } else {
            charge(4);
            v1 = lw(a0 + 24);
            v1 = sltu(a1, v1);
            if (v1 == 0) {
                charge(3);
                t0 = addiu(a3, -1);
            } else {
                charge(1);
                t1 = a1;
            }
        }
        charge(3);
        v1 = si(-1);
        if (t0 == v1) {
            charge(5);
            t3 = lw(a0 + 16);
            a1 = 0;
            t2 = 0;
            for (;;) {
                charge(3);
                v1 = sltu(t2, a3);
                if (v1 == 0) break;
                backedge();
                charge(5);
                v1 = lw(t3 + 0);
                v1 = addu(a1, v1);
                at = sltu(v1, t1);
                if (at == 0) {
                    charge(3);
                    t0 = t2;
                    break;
                }
                charge(3);
                a1 = addiu(v1, 1);
                t2 = addiu(t2, 1);
                t3 = addiu(t3, 16);
            }
        }
    }
    charge(7);
    v1 = lui(0x3f80);
    mtc1(v1, F0);
    sw(a2 + 0, v1);
    v1 = lw(a0 + 8);
    v1 = andi(v1, 0x4);
    if (v1 != 0) {
        charge(2);
        v1 = lui(0x4000);
        mtc1(v1, F0);
    }
    charge(15);
    swc1(F0, a2 + 4);
    a1 = sll(t0, 2);
    v1 = lw(a0 + 20);
    v1 = addu(v1, a1);
    v1 = lw(v1 + 0);
    sw(a2 + 16, v1);
    v1 = lw(v1 + 0);
    lwc1(F0, v1 + 12);
    cvt_s_w(F0, F0);
    swc1(F0, a2 + 8);
    lwc1(F0, v1 + 16);
    cvt_s_w(F0, F0);
    swc1(F0, a2 + 12);
}

// sub_323240 / sub_3233A0 [effect mesh: a grid of triangles]. sub_323240(rows, index template, cols, flags):
// (rows + 1) * cols vertices, rows * (cols - 1) * 2 triangles, (cols - 1) * 6 template indices per row, rows `cols`
// vertices apart. sub_3233A0(rows, triangles per row, vertex stride, index template, flags in $t0): rows * stride
// vertices, rows * n triangles, n * 3 template indices per row. The mesh comes from sub_3230F0 (heap, recompiled);
// a triangle's indices are the template's offsets from its row's first vertex, and it gets the mesh's material
// (sub_493210 / sub_493230). The counts go through the EE's three-operand `mult` / `mult1` (HI/LO of both pipes as
// they leave them). Returns the mesh record.
void Cpu::grid_mesh(bool closed) {
    enter(closed ? 36 : 34);
    sp = addiu(sp, -208);
    sd(sp + 144, ra);
    sq(sp + 128, s8);
    sq(sp + 112, s7);
    sq(sp + 96, s6);
    sq(sp + 80, s5);
    sq(sp + 64, s4);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp + 0, s0);
    if (closed) {  // sub_323240(rows, template, cols, flags)
        s8 = a1;
        s7 = a2;
        a1 = andi(s7, 0xffff);
        v0 = addiu(a1, -1);
        v1 = sll(v0, 1);
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);  // (cols - 1) * 6
        sq(sp + 160, v0);
        s0 = andi(a0, 0xffff);
        v0 = addiu(s0, 1);
        mult(a0, v0, a1);
        mult1(a1, s0, v1);
        a2 = a3;
        jal(0x3232a0u, gen::fn_sub_3230F0_003230f0);
    } else {  // sub_3233A0(rows, cols, stride, template, flags)
        s7 = a2;
        s8 = a3;
        v1 = andi(a1, 0xffff);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);  // cols * 3
        sq(sp + 160, v0);
        s0 = andi(a0, 0xffff);
        v0 = andi(s7, 0xffff);
        mult(a0, s0, v0);
        mult1(a1, s0, v1);
        a2 = t0;
        jal(0x3233f8u, gen::fn_sub_3230F0_003230f0);
    }
    sw(sp + 204, v0);
    v1 = lw(v0 + 16);
    s5 = lw(v1 + 24);  // the geometry
    v0 = lw(v0 + 20);
    sw(sp + 176, v0);  // the material
    s4 = lw(s5 + 44);  // the triangles
    s1 = 0;
    s3 = 0;
    for (;;) {
        charge(3);
        v0 = slt(s3, s0);
        if (v0 == 0) break;
        backedge();
        charge(4);
        s2 = 0;
        s6 = andi(s1, 0xffff);  // the row's first vertex
        for (;;) {
            charge(4);
            lq(v0, sp + 160);
            v0 = slt(s2, v0);
            if (v0 == 0) break;
            backedge();
            charge(22);
            v0 = sll(s2, 1);
            v1 = addu(s8, v0);
            v0 = lhu(v1 + 0);
            v0 = addu(s6, v0);
            a2 = andi(v0, 0xffff);
            v0 = lhu(v1 + 2);
            v0 = addu(s6, v0);
            a3 = andi(v0, 0xffff);
            v0 = lhu(v1 + 4);
            v0 = addu(s6, v0);
            t0 = andi(v0, 0xffff);
            a0 = s5;
            a1 = s4;
            jal(closed ? 0x323314u : 0x32346cu, gen::fn_sub_493210_00493210);
            a0 = s5;
            a1 = s4;
            a2 = lw(sp + 176);
            jal(closed ? 0x323328u : 0x323480u, gen::fn_sub_493230_00493230);
            s4 = addiu(s4, 8);
            s2 = addiu(s2, 3);
        }
        charge(3);
        v0 = addu(s1, s7);
        s1 = andi(v0, 0xffff);
        s3 = addiu(s3, 1);
    }
    charge(14);
    v0 = lw(sp + 204);
    ra = ld(sp + 144);
    lq(s8, sp + 128);
    lq(s7, sp + 112);
    lq(s6, sp + 96);
    lq(s5, sp + 80);
    lq(s4, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp + 0);
    sp = addiu(sp, 208);
}

// sub_323640 [effect mesh: copy]: $a0 the source record {+0 u16 flags, +4 create flags, +8 / +10 s16 vertex /
// triangle counts, +16 the mesh, +20 the material}. Flag 2: a mesh of the same counts by sub_3234F0 that takes the
// source's first material texture (when set). Else a new mesh (sub_3230F0) whose triangles (vertex indices, the new
// material) copy the source's under the geometry lock (geometryLock / sub_4933D0), the material texture copied.
// Returns the new record.
void Cpu::sub_323640() {
    enter(15);
    sp = addiu(sp, -144);
    sd(sp + 128, ra);
    sq(sp + 112, s7);
    sq(sp + 96, s6);
    sq(sp + 80, s5);
    sq(sp + 64, s4);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp + 0, s0);
    s2 = a0;
    v0 = lhu(a0 + 0);
    v0 = andi(v0, 0x2);
    if (v0 != 0) {
        charge(12);
        a0 = lhu(s2 + 10);
        a1 = lw(s2 + 4);
        jal(0x323684u, gen::fn_sub_3234F0_003234f0);
        s1 = v0;
        v0 = lw(s2 + 16);
        v0 = lw(v0 + 24);
        v0 = lw(v0 + 32);
        v0 = lw(v0 + 0);
        a1 = lw(v0 + 0);  // the source's first material texture
        if (a1 != 0) {
            charge(8);
            v0 = lw(s1 + 16);
            v0 = lw(v0 + 24);
            v0 = lw(v0 + 32);
            a0 = lw(v0 + 0);
            jal(0x3236bcu, gen::fn_sub_494D50_00494d50);
        }
    } else {
        charge(15);
        a0 = lh(s2 + 8);
        a1 = lh(s2 + 10);
        a2 = lw(s2 + 4);
        jal(0x3236d8u, gen::fn_sub_3230F0_003230f0);
        s1 = v0;
        s0 = lw(v0 + 20);  // the new material
        v1 = lw(s2 + 16);
        s5 = lw(v1 + 24);  // the source geometry
        v0 = lw(v0 + 16);
        s7 = lw(v0 + 24);  // the new geometry
        v0 = lw(s2 + 20);
        a1 = lw(v0 + 0);
        if (a1 != 0) {
            charge(3);
            a0 = s0;
            jal(0x32370cu, gen::fn_sub_494D50_00494d50);
        }
        charge(9);
        a0 = s5;
        a1 = 1;
        jal(0x32371cu, gen::fn_geometryLock_00493370);
        s4 = lw(s5 + 44);
        s3 = lw(s7 + 44);
        s6 = 0;
        for (;;) {
            charge(4);
            v0 = lh(s2 + 10);
            v0 = slt(s6, v0);
            if (v0 == 0) break;
            backedge();
            charge(14);
            v0 = lhu(s4 + 0);
            sh(s3 + 0, v0);
            v0 = lhu(s4 + 2);
            sh(s3 + 2, v0);
            v0 = lhu(s4 + 4);
            sh(s3 + 4, v0);
            a0 = s7;
            a1 = s3;
            a2 = s0;
            jal(0x32375cu, gen::fn_sub_493230_00493230);
            s4 = addiu(s4, 8);
            s3 = addiu(s3, 8);
            s6 = addiu(s6, 1);
        }
        charge(3);
        a0 = s5;
        jal(0x323784u, gen::fn_sub_4933D0_004933d0);
    }
    charge(13);
    v0 = s1;
    ra = ld(sp + 128);
    lq(s7, sp + 112);
    lq(s6, sp + 96);
    lq(s5, sp + 80);
    lq(s4, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp + 0);
    sp = addiu(sp, 144);
}

// sub_323860 [push on the bank-relative list 0x957920]: sub_321140($a0, $a1).
void Cpu::sub_323860() {
    enter(8);
    sp = addiu(sp, -16);
    sd(sp + 0, ra);
    rt::jal(c, 0x323868u);
    link_bank(0x957920u, 24, false);
    ra = ld(sp + 0);
    sp = addiu(sp, 16);
}

// sub_323920 [build a matrix: rotation, uniform scale, translation]: $a0 the matrix, $a1 the translation (or 0),
// $a2 the rotation record (sub_3296A0) or 0 for identity (rwMATRIXTYPEORTHONORMAL | internal-identity flags 0x20003
// or-ed into +12), $f12 the scale (scaled by sub_4C33D0 with the vector on the frame unless 1.0).
void Cpu::sub_323920() {
    enter(10);
    sp = addiu(sp, -80);
    sd(sp + 48, ra);
    sq(sp + 32, s1);
    sq(sp + 16, s0);
    swc1(F20, sp + 0);
    s1 = a0;
    s0 = a1;
    mov_s(F20, F12);
    if (a2 != 0) {
        charge(5);
        a1 = a2;
        jal(0x32394cu, gen::fn_sub_3296A0_003296a0);
    } else {
        charge(18);
        v1 = lui(0x3f80);
        sw(s1 + 40, v1);
        sw(s1 + 20, v1);
        sw(s1 + 0, v1);
        sw(s1 + 16, zero);
        sw(s1 + 8, zero);
        sw(s1 + 4, zero);
        sw(s1 + 36, zero);
        sw(s1 + 32, zero);
        sw(s1 + 24, zero);
        sw(s1 + 56, zero);
        sw(s1 + 52, zero);
        sw(s1 + 48, zero);
        a0 = lw(s1 + 12);
        v1 = lui(0x2);
        v1 = ori(v1, 0x3);
        v1 = or_(a0, v1);
        sw(s1 + 12, v1);
    }
    charge(6);
    v1 = lui(0x3f80);
    mtc1(v1, F0);
    c_eq_s(F0, F20);
    if (!bc1t()) {
        charge(8);
        swc1(F20, sp + 72);
        swc1(F20, sp + 68);
        swc1(F20, sp + 64);
        a0 = s1;
        a1 = addiu(sp, 64);
        a2 = 2;
        jal(0x3239d4u, gen::fn_sub_4C33D0_004c33d0);
    }
    charge(2);
    if (s0 != 0) {
        charge(11);
        lwc1(F0, s0 + 0);
        swc1(F0, sp + 64);
        lwc1(F0, s0 + 4);
        swc1(F0, sp + 68);
        lwc1(F0, s0 + 8);
        swc1(F0, sp + 72);
        a0 = s1;
        a1 = addiu(sp, 64);
        a2 = 2;
        jal(0x323a08u, gen::fn_sub_4C35D0_004c35d0);
    }
    charge(7);
    ra = ld(sp + 48);
    lq(s1, sp + 32);
    lq(s0, sp + 16);
    lwc1(F20, sp + 0);
    sp = addiu(sp, 80);
}

// sub_323A30 [build a matrix: scale, rotation, translation]: $a0 the matrix, $a1 the translation (or 0), $a2 the
// rotation record (or 0), $a3 the scale vector (or 0). The scale matrix on the frame (sp+64; sub_4C33D0 replace,
// or identity), times the rotation (sub_3296A0 into sp+128, sub_4C2F30) or copied as 64 bytes; then translated.
void Cpu::sub_323A30() {
    enter(10);
    sp = addiu(sp, -208);
    sd(sp + 48, ra);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp + 0, s0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    if (a3 != 0) {
        charge(13);
        lwc1(F0, a3 + 0);
        swc1(F0, sp + 192);
        lwc1(F0, a3 + 4);
        swc1(F0, sp + 196);
        lwc1(F0, a3 + 8);
        swc1(F0, sp + 200);
        a0 = addiu(sp, 64);
        a1 = addiu(sp, 192);
        a2 = 0;
        jal(0x323a7cu, gen::fn_sub_4C33D0_004c33d0);
    } else {
        charge(18);
        v1 = lui(0x3f80);
        sw(sp + 104, v1);
        sw(sp + 84, v1);
        sw(sp + 64, v1);
        sw(sp + 80, zero);
        sw(sp + 72, zero);
        sw(sp + 68, zero);
        sw(sp + 100, zero);
        sw(sp + 96, zero);
        sw(sp + 88, zero);
        sw(sp + 120, zero);
        sw(sp + 116, zero);
        sw(sp + 112, zero);
        a0 = lw(sp + 76);
        v1 = lui(0x2);
        v1 = ori(v1, 0x3);
        v1 = or_(a0, v1);
        sw(sp + 76, v1);
    }
    charge(2);
    if (s0 != 0) {
        charge(11);
        a0 = addiu(sp, 128);
        a1 = s0;
        jal(0x323ae4u, gen::fn_sub_3296A0_003296a0);
        a0 = s2;
        a1 = addiu(sp, 64);
        a2 = addiu(sp, 128);
        jal(0x323af8u, gen::fn_sub_4C2F30_004c2f30);
    } else {
        charge(3);
        a3 = addiu(sp, 64);
        a1 = 8;
        a2 = s2;
        do {
            charge(9);
            a0 = lw(a3 + 0);
            v1 = lw(a3 + 4);
            a3 = addiu(a3, 8);
            a1 = addiu(a1, -1);
            sw(a2 + 0, a0);
            sw(a2 + 4, v1);
            a2 = addiu(a2, 8);
            if (!bgtz(a1)) break;
            backedge();
        } while (true);
    }
    charge(2);
    if (s1 != 0) {
        charge(11);
        lwc1(F0, s1 + 0);
        swc1(F0, sp + 192);
        lwc1(F0, s1 + 4);
        swc1(F0, sp + 196);
        lwc1(F0, s1 + 8);
        swc1(F0, sp + 200);
        a0 = s2;
        a1 = addiu(sp, 192);
        a2 = 2;
        jal(0x323b64u, gen::fn_sub_4C35D0_004c35d0);
    }
    charge(7);
    ra = ld(sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp + 0);
    sp = addiu(sp, 208);
}

// sub_323880 / sub_3238D0 [place an object's frame]: the matrix of sub_323920 / sub_323A30 ($a1.. passed on) on
// the frame at sp+32, then RwFrameTransform(object +12, matrix, replace).
void Cpu::sub_323880() {
    enter(17);
    sp = addiu(sp, -96);
    sd(sp + 16, ra);
    sq(sp + 0, s0);
    s0 = a0;
    a0 = addiu(sp, 32);
    jal_here(0x323894u, &Cpu::sub_323920);
    a0 = lw(s0 + 12);
    a1 = addiu(sp, 32);
    a2 = 0;
    jal(0x3238a8u, gen::fn_sub_4CB7F0_004cb7f0);
    ra = ld(sp + 16);
    lq(s0, sp + 0);
    sp = addiu(sp, 96);
}
void Cpu::sub_3238D0() {
    enter(17);
    sp = addiu(sp, -96);
    sd(sp + 16, ra);
    sq(sp + 0, s0);
    s0 = a0;
    a0 = addiu(sp, 32);
    jal_here(0x3238e4u, &Cpu::sub_323A30);
    a0 = lw(s0 + 12);
    a1 = addiu(sp, 32);
    a2 = 0;
    jal(0x3238f8u, gen::fn_sub_4CB7F0_004cb7f0);
    ra = ld(sp + 16);
    lq(s0, sp + 0);
    sp = addiu(sp, 96);
}

// sub_323B90 [replace a mesh's texture from an image]: texture = sub_3210C0(image); material (+20) gets it
// (sub_494D50, which takes a reference); the local reference is dropped (sub_4D0F00).
void Cpu::sub_323B90() {
    enter(22);
    sp = addiu(sp, -48);
    sd(sp + 32, ra);
    sq(sp + 16, s1);
    sq(sp + 0, s0);
    s1 = a0;
    a0 = a1;
    jal_here(0x323ba8u, &Cpu::sub_3210C0);
    s0 = v0;
    a0 = lw(s1 + 20);
    a1 = s0;
    jal(0x323bbcu, gen::fn_sub_494D50_00494d50);
    a0 = s0;
    jal(0x323bc8u, gen::fn_sub_4D0F00_004d0f00);
    ra = ld(sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp + 0);
    sp = addiu(sp, 48);
}

// sub_323BF0 [texture size of a mesh]: $a1 the output {+0 width, +4 height, +8 the texture}: the first material
// texture (record +20 -> +0); when set, its raster's +12 / +16.
void Cpu::sub_323BF0() {
    enter(5);
    v1 = lw(a0 + 20);
    v1 = lw(v1 + 0);
    sw(a1 + 8, v1);
    if (v1 != 0) {
        charge(5);
        a0 = lw(v1 + 0);
        v1 = lw(a0 + 12);
        sw(a1 + 0, v1);
        v1 = lw(a0 + 16);
        sw(a1 + 4, v1);
    }
    charge(2);
}

// sub_323E10 / sub_323FB0 [effect mesh: a band of grids, one material per band]: ($a0 bands, $a1 rows per band,
// $a2 / $a3 sizes, $t0 the template, $t1 the create flags; sub_323FB0 one more vertex row per band). Like
// grid_mesh with sub_323C20 (one material per band, +40 the material array); the band's material per triangle.
void Cpu::band_mesh(bool closed) {
    enter(closed ? 41 : 39);
    sp = addiu(sp, -240);
    sd(sp + 144, ra);
    sq(sp + 128, s8);
    sq(sp + 112, s7);
    sq(sp + 96, s6);
    sq(sp + 80, s5);
    sq(sp + 64, s4);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp + 0, s0);
    s2 = a0;
    if (!closed) {  // sub_323E10(bands, rows, cols, stride, template, flags)
        s8 = a3;
        sw(sp + 236, t0);
        v1 = andi(a2, 0xffff);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        sq(sp + 208, v0);
        s6 = andi(a1, 0xffff);
        v0 = andi(s8, 0xffff);
        mult(v0, s6, v0);
        a1 = andi(v0, 0xffff);
        mult1(v0, s6, v1);
        a2 = andi(v0, 0xffff);
        a3 = t1;
        jal(0x323e74u, gen::fn_sub_323C20_00323c20);
    } else {  // sub_323FB0(bands, rows, template, cols, flags)
        sw(sp + 236, a2);
        s5 = a3;
        a2 = andi(s5, 0xffff);
        v0 = addiu(a2, -1);
        v1 = sll(v0, 1);
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        sq(sp + 208, v0);
        s7 = andi(a1, 0xffff);
        v0 = addiu(s7, 1);
        mult(v0, v0, a2);
        a1 = andi(v0, 0xffff);
        mult1(v0, s7, v1);
        a2 = andi(v0, 0xffff);
        a3 = t0;
        jal(0x32401cu, gen::fn_sub_323C20_00323c20);
    }
    sw(sp + 232, v0);
    v1 = lw(v0 + 16);
    Gpr& geo = closed ? s4 : s5;
    Gpr& tri = closed ? s3 : s4;
    Gpr& row = closed ? s6 : s3;  // row counter within a band
    Gpr& first = closed ? s8 : s7;
    geo = lw(v1 + 24);
    v0 = lw(v0 + 40);
    sq(sp + 192, v0);  // the material array
    tri = lw(geo + 44);
    s0 = 0;
    s1 = 0;
    v0 = andi(s2, 0xffff);
    sq(sp + 176, v0);  // the band count
    for (;;) {
        charge(4);
        lq(v0, sp + 176);
        v0 = slt(s1, v0);
        if (v0 == 0) break;
        backedge();
        charge(7);
        row = 0;
        v1 = sll(s1, 2);
        lq(v0, sp + 192);
        v0 = addu(v0, v1);
        sq(sp + 160, v0);  // &materials[band]
        for (;;) {
            charge(3);
            v0 = slt(row, closed ? s7 : s6);
            if (v0 == 0) break;
            backedge();
            charge(4);
            s2 = 0;
            first = andi(s0, 0xffff);
            for (;;) {
                charge(4);
                lq(v0, sp + 208);
                v0 = slt(s2, v0);
                if (v0 == 0) break;
                backedge();
                charge(24);
                v1 = sll(s2, 1);
                v0 = lw(sp + 236);
                v1 = addu(v0, v1);
                v0 = lhu(v1 + 0);
                v0 = addu(first, v0);
                a2 = andi(v0, 0xffff);
                v0 = lhu(v1 + 2);
                v0 = addu(first, v0);
                a3 = andi(v0, 0xffff);
                v0 = lhu(v1 + 4);
                v0 = addu(first, v0);
                t0 = andi(v0, 0xffff);
                a0 = geo;
                a1 = tri;
                jal(closed ? 0x3240b8u : 0x323f10u, gen::fn_sub_493210_00493210);
                a0 = geo;
                a1 = tri;
                lq(v0, sp + 160);
                a2 = lw(v0 + 0);
                jal(closed ? 0x3240d0u : 0x323f28u, gen::fn_sub_493230_00493230);
                tri = addiu(tri, 8);
                s2 = addiu(s2, 3);
            }
            charge(3);
            v0 = addu(s0, closed ? s5 : s8);
            s0 = andi(v0, 0xffff);
            row = addiu(row, 1);
        }
        if (closed) {
            charge(3);
            v0 = addu(s0, s5);
            s0 = andi(v0, 0xffff);
        } else {
            charge(1);
        }
        s1 = addiu(s1, 1);
    }
    charge(14);
    v0 = lw(sp + 232);
    ra = ld(sp + 144);
    lq(s8, sp + 128);
    lq(s7, sp + 112);
    lq(s6, sp + 96);
    lq(s5, sp + 80);
    lq(s4, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp + 0);
    sp = addiu(sp, 240);
}

// --- the C++ entry points: the EE argument registers ($a0.. then $t0.., $f12..), the body, the result ----------
u64 sx(u32 v) { return core::sext32(v); }
u64 sxi(s32 v) { return static_cast<u64>(static_cast<s64>(v)); }
void args(EEContext& ctx, std::initializer_list<u64> a, std::initializer_list<float> f = {}) {
    unsigned r = GPR_A0;
    for (u64 v : a) core::set_gpr64(ctx, r++, v);
    unsigned fr = F12;
    for (float x : f) std::memcpy(&ctx.fpr[fr++], &x, 4);
}
u32 v0_of(const EEContext& ctx) { return core::gpr32(ctx, GPR_V0); }
float f0_of(const EEContext& ctx) {
    float f;
    std::memcpy(&f, &ctx.fpr[F0], 4);
    return f;
}

}  // namespace
}  // namespace fx

using fx::Cpu;
using fx::args;
using fx::sx;
using fx::sxi;
using fx::v0_of;

s32 sub_1E8330(EEContext& ctx, u32 ring, s32 k) {
    args(ctx, {sx(ring), sxi(k)});
    Cpu(ctx).sub_1E8330();
    return static_cast<s32>(v0_of(ctx));
}
void sub_1E8360(EEContext& ctx, u32 ring, s32 sample, s32 side, u32 out) {
    args(ctx, {sx(ring), sxi(sample), sxi(side), sx(out)});
    Cpu(ctx).sub_1E8360();
}
void sub_1E88F0(EEContext& ctx, u32 ring, s32 sample, u32 out) {
    args(ctx, {sx(ring), sxi(sample), sx(out)});
    Cpu(ctx).sub_1E88F0();
}
u32 sub_1E8E80(EEContext& ctx, u32 ring, u32 material) {
    args(ctx, {sx(ring), sx(material)});
    Cpu(ctx).sub_1E8E80();
    return v0_of(ctx);
}
void sub_1E9AF0(EEContext& ctx, u32 ring, u32 geometry_slot) {
    args(ctx, {sx(ring), sx(geometry_slot)});
    Cpu(ctx).sub_1E9AF0();
}
void sub_1EB920(EEContext& ctx, u32 ring, u32 rail0, u32 rail1) {
    args(ctx, {sx(ring), sx(rail0), sx(rail1)});
    Cpu(ctx).sub_1EB920();
}
void sub_1EBA50(EEContext& ctx, u32 state) {
    args(ctx, {sx(state)});
    Cpu(ctx).sub_1EBA50();
}
void sub_1EBA80(EEContext& ctx, u32 state) {
    args(ctx, {sx(state)});
    Cpu(ctx).sub_1EBA80();
}
void sub_1EBD80(EEContext& ctx, u32 ring, s32 sample) {
    args(ctx, {sx(ring), sxi(sample)});
    Cpu(ctx).sub_1EBD80();
}
float sub_1ECD90(EEContext& ctx, u32 ring, s32 sample, s32 rail) {
    args(ctx, {sx(ring), sxi(sample), sxi(rail)});
    Cpu(ctx).sub_1ECD90();
    return fx::f0_of(ctx);
}
float sub_1ECEC0(EEContext& ctx, u32 ring, s32 sample) {
    args(ctx, {sx(ring), sxi(sample)});
    Cpu(ctx).sub_1ECEC0();
    return fx::f0_of(ctx);
}
void sub_1ED080(EEContext& ctx, u32 ring, float duration) {
    args(ctx, {sx(ring)}, {duration});
    Cpu(ctx).sub_1ED080();
}
void sub_1ED0B0(EEContext& ctx, u32 ring) {
    args(ctx, {sx(ring)});
    Cpu(ctx).sub_1ED0B0();
}
void sub_1ED0D0(EEContext& ctx, u32 ring, u32 step) {
    args(ctx, {sx(ring), sx(step)});
    Cpu(ctx).sub_1ED0D0();
}
void sub_1ED0F0(EEContext& ctx, u32 ring, s32 key, u32 out, float t) {
    args(ctx, {sx(ring), sxi(key), sx(out)}, {t});
    Cpu(ctx).sub_1ED0F0();
}
void sub_1ED8A0(EEContext& ctx, u32 ring, u32 geometry) {
    args(ctx, {sx(ring), sx(geometry)});
    Cpu(ctx).sub_1ED8A0();
}
u32 sub_1ED9E0(EEContext& ctx, u32 keys) {
    args(ctx, {sx(keys)});
    Cpu(ctx).sub_1ED9E0();
    return v0_of(ctx);
}
u32 sub_1EDA00(EEContext& ctx, u32 pack, u32 colour) {
    args(ctx, {sx(pack), sx(colour)});
    Cpu(ctx).sub_1EDA00();
    return v0_of(ctx);
}
void sub_1EDA90(EEContext& ctx, u32 effect) {
    args(ctx, {sx(effect)});
    Cpu(ctx).sub_1EDA90();
}
void sub_1EDBE0(EEContext& ctx, u32 effect) {
    args(ctx, {sx(effect)});
    Cpu(ctx).sub_1EDBE0();
}
void sub_1EDED0(EEContext& ctx, u32 effect) {
    args(ctx, {sx(effect)});
    Cpu(ctx).sub_1EDED0();
}
void sub_1EE1D0(EEContext& ctx, u32 effect) {
    args(ctx, {sx(effect)});
    Cpu(ctx).sub_1EE1D0();
}
void nullsub_10(EEContext& ctx) { Cpu(ctx).nullsub_10(); }
void sub_1EE230(EEContext& ctx, u32 effect, u32 rgba) {
    args(ctx, {sx(effect), sx(rgba)});
    Cpu(ctx).sub_1EE230();
}
void sub_1EEE40(EEContext& ctx, u32 effect) {
    args(ctx, {sx(effect)});
    Cpu(ctx).sub_1EEE40();
}
void sub_1EEFC0(EEContext& ctx, u32 effect) {
    args(ctx, {sx(effect)});
    Cpu(ctx).sub_1EEFC0();
}
u32 sub_1EF000(EEContext& ctx, u32 effect) {
    args(ctx, {sx(effect)});
    Cpu(ctx).sub_1EF000();
    return v0_of(ctx);
}

u32 sub_320060(EEContext& ctx) {
    Cpu(ctx).sub_320060();
    return v0_of(ctx);
}
void nullsub_106(EEContext& ctx) { Cpu(ctx).nullsub_106(); }
void sub_320080(EEContext& ctx, u32 a, u32 b, float t, float u, float v) {
    args(ctx, {sx(a), sx(b)}, {t, u, v});
    Cpu(ctx).sub_320080();
}
void sub_320380(EEContext& ctx, u32 list, float t) {
    args(ctx, {sx(list)}, {t});
    Cpu(ctx).sub_320380();
}
void sub_3204A0(EEContext& ctx, u32 list, float t, float u, float v) {
    args(ctx, {sx(list)}, {t, u, v});
    Cpu(ctx).sub_3204A0();
}
void sub_320640(EEContext& ctx, u32 list, float t, float u) {
    args(ctx, {sx(list)}, {t, u});
    Cpu(ctx).sub_320640();
}
void sub_320770(EEContext& ctx, u32 list) {
    args(ctx, {sx(list)});
    Cpu(ctx).sub_320770();
}
float sub_320810(EEContext& ctx, u32 list) {
    args(ctx, {sx(list)});
    Cpu(ctx).sub_320810();
    return fx::f0_of(ctx);
}
u32 sub_320BA0(EEContext& ctx, u32 material, u32 record) {
    args(ctx, {sx(material), sx(record)});
    Cpu(ctx).sub_320BA0();
    return v0_of(ctx);
}
u32 sub_320CF0(EEContext& ctx, u32 atomic, u32 record) {
    args(ctx, {sx(atomic), sx(record)});
    Cpu(ctx).sub_320CF0();
    return v0_of(ctx);
}
u32 sub_320DA0(EEContext& ctx, u32 clump, u32 record) {
    args(ctx, {sx(clump), sx(record)});
    Cpu(ctx).sub_320DA0();
    return v0_of(ctx);
}
u32 sub_320DE0(EEContext& ctx, u32 atomic, u32 record) {
    args(ctx, {sx(atomic), sx(record)});
    Cpu(ctx).sub_320DE0();
    return v0_of(ctx);
}
u32 sub_320F70(EEContext& ctx, u32 clump, u32 name) {
    args(ctx, {sx(clump), sx(name)});
    Cpu(ctx).sub_320F70();
    return v0_of(ctx);
}
u32 sub_321050(EEContext& ctx, u32 object) {
    args(ctx, {sx(object)});
    Cpu(ctx).sub_321050();
    return v0_of(ctx);
}
void sub_321070(EEContext& ctx, u32 list, u32 item) {
    args(ctx, {sx(list), sx(item)});
    Cpu(ctx).sub_321070();
}
u32 sub_3210A0(EEContext& ctx, u32 id) {
    args(ctx, {sx(id)});
    Cpu(ctx).sub_3210A0();
    return v0_of(ctx);
}
u32 sub_3210C0(EEContext& ctx, u32 image) {
    args(ctx, {sx(image)});
    Cpu(ctx).sub_3210C0();
    return v0_of(ctx);
}
void sub_321120(EEContext& ctx, u32 bank) {
    args(ctx, {sx(bank)});
    Cpu(ctx).sub_321120();
}
u32 sub_321130(EEContext& ctx) {
    Cpu(ctx).sub_321130();
    return v0_of(ctx);
}
void sub_321140(EEContext& ctx, u32 object, u32 layer) {
    args(ctx, {sx(object), sx(layer)});
    Cpu(ctx).link_bank(0x957920u, 24, false);
}
void sub_321180(EEContext& ctx, u32 object, u32 layer) {
    args(ctx, {sx(object), sx(layer)});
    Cpu(ctx).link_bank(0x957820u, 44, true);
}
void sub_3211D0(EEContext& ctx, u32 object, u32 layer) {
    args(ctx, {sx(object), sx(layer)});
    Cpu(ctx).link_bank(0x957720u, 44, true);
}
void sub_321220(EEContext& ctx, u32 object, u32 layer) {
    args(ctx, {sx(object), sx(layer)});
    Cpu(ctx).link_bank(0x957620u, 100, false);
}
void sub_321260(EEContext& ctx, u32 object, u32 layer) {
    args(ctx, {sx(object), sx(layer)});
    Cpu(ctx).link_bank(0x957520u, 92, false);
}
void sub_3212A0(EEContext& ctx, u32 object, u32 layer) {
    args(ctx, {sx(object), sx(layer)});
    Cpu(ctx).link_bank(0x957420u, 108, false);
}
void sub_3212E0(EEContext& ctx, u32 object, u32 layer) {
    args(ctx, {sx(object), sx(layer)});
    Cpu(ctx).link_bank(0x957320u, 156, false);
}
void sub_321320(EEContext& ctx, u32 matrix) {
    args(ctx, {sx(matrix)});
    Cpu(ctx).sub_321320();
}
u32 effMng_UpdateEffectProgramTask(EEContext& ctx) {
    Cpu(ctx).effMng_UpdateEffectProgramTask();
    return v0_of(ctx);
}
u32 effMng_UpdateEffect3dTask(EEContext& ctx) {
    Cpu(ctx).layer_task(0x321cbcu, 2, true);
    return v0_of(ctx);
}
u32 effMng_UpdateEffect2dTask(EEContext& ctx) {
    Cpu(ctx).layer_task(0x321e2cu, 5, true);
    return v0_of(ctx);
}
void sub_321FE0(EEContext& ctx) { Cpu(ctx).layer_task(0x321fecu, 8, false); }
void sub_321F10(EEContext& ctx, u32 bank) {
    args(ctx, {sx(bank)});
    Cpu(ctx).sub_321F10();
}
void sub_3226B0(EEContext& ctx, u32 player, s32 animation) {
    args(ctx, {sx(player), sxi(animation)});
    Cpu(ctx).sub_3226B0();
}
void sub_322AB0(EEContext& ctx, u32 player, u32 track, u32 quad) {
    args(ctx, {sx(player), sx(track), sx(quad)});
    Cpu(ctx).sub_322AB0();
}
void sub_322D10(EEContext& ctx, u32 player, u32 quad) {
    args(ctx, {sx(player), sx(quad)});
    Cpu(ctx).sub_322D10();
}
void sub_322D40(EEContext& ctx, u32 player, u32 frame) {
    args(ctx, {sx(player), sx(frame)});
    Cpu(ctx).sub_322D40();
}
u32 sub_322DA0(EEContext& ctx, u32 player, s32 index) {
    args(ctx, {sx(player), sxi(index)});
    Cpu(ctx).sub_322DA0();
    return v0_of(ctx);
}
u32 sub_322FB0(EEContext& ctx, u32 object) {
    args(ctx, {sx(object)});
    Cpu(ctx).sub_322FB0();
    return v0_of(ctx);
}
void sub_322FD0(EEContext& ctx, u32 sequence, u32 time, u32 out) {
    args(ctx, {sx(sequence), sx(time), sx(out)});
    Cpu(ctx).sub_322FD0();
}
u32 sub_323240(EEContext& ctx, u32 rows, u32 indices, u32 cols, u32 flags) {
    args(ctx, {sx(rows), sx(indices), sx(cols), sx(flags)});
    Cpu(ctx).grid_mesh(true);
    return v0_of(ctx);
}
u32 sub_3233A0(EEContext& ctx, u32 rows, u32 per_row, u32 stride, u32 indices, u32 flags) {
    args(ctx, {sx(rows), sx(per_row), sx(stride), sx(indices), sx(flags)});
    Cpu(ctx).grid_mesh(false);
    return v0_of(ctx);
}
u32 sub_323640(EEContext& ctx, u32 source) {
    args(ctx, {sx(source)});
    Cpu(ctx).sub_323640();
    return v0_of(ctx);
}
void sub_323860(EEContext& ctx, u32 object, u32 layer) {
    args(ctx, {sx(object), sx(layer)});
    Cpu(ctx).sub_323860();
}
void sub_323880(EEContext& ctx, u32 object, u32 translation, u32 rotation, float scale) {
    args(ctx, {sx(object), sx(translation), sx(rotation)}, {scale});
    Cpu(ctx).sub_323880();
}
void sub_3238D0(EEContext& ctx, u32 object, u32 translation, u32 rotation, u32 scale) {
    args(ctx, {sx(object), sx(translation), sx(rotation), sx(scale)});
    Cpu(ctx).sub_3238D0();
}
void sub_323920(EEContext& ctx, u32 matrix, u32 translation, u32 rotation, float scale) {
    args(ctx, {sx(matrix), sx(translation), sx(rotation)}, {scale});
    Cpu(ctx).sub_323920();
}
void sub_323A30(EEContext& ctx, u32 matrix, u32 translation, u32 rotation, u32 scale) {
    args(ctx, {sx(matrix), sx(translation), sx(rotation), sx(scale)});
    Cpu(ctx).sub_323A30();
}
void sub_323B90(EEContext& ctx, u32 mesh, u32 image) {
    args(ctx, {sx(mesh), sx(image)});
    Cpu(ctx).sub_323B90();
}
void sub_323BF0(EEContext& ctx, u32 mesh, u32 out) {
    args(ctx, {sx(mesh), sx(out)});
    Cpu(ctx).sub_323BF0();
}
u32 sub_323E10(EEContext& ctx, u32 bands, u32 rows, u32 cols, u32 stride, u32 indices, u32 flags) {
    args(ctx, {sx(bands), sx(rows), sx(cols), sx(stride), sx(indices), sx(flags)});
    Cpu(ctx).band_mesh(false);
    return v0_of(ctx);
}
u32 sub_323FB0(EEContext& ctx, u32 bands, u32 rows, u32 indices, u32 cols, u32 flags) {
    args(ctx, {sx(bands), sx(rows), sx(indices), sx(cols), sx(flags)});
    Cpu(ctx).band_mesh(true);
    return v0_of(ctx);
}

}  // namespace p3fes::game

// --- the recompiled program's entry points (the bodies read their arguments from the registers) -----------
namespace p3fes::recomp_gen {
using Cpu = ::p3fes::game::fx::Cpu;

void fn_sub_1E8330_001e8330(p3fes::EEContext& ctx) { Cpu(ctx).sub_1E8330(); }
void fn_sub_1E8360_001e8360(p3fes::EEContext& ctx) { Cpu(ctx).sub_1E8360(); }
void fn_sub_1E88F0_001e88f0(p3fes::EEContext& ctx) { Cpu(ctx).sub_1E88F0(); }
void fn_sub_1E8E80_001e8e80(p3fes::EEContext& ctx) { Cpu(ctx).sub_1E8E80(); }
void fn_sub_1E9AF0_001e9af0(p3fes::EEContext& ctx) { Cpu(ctx).sub_1E9AF0(); }
void fn_sub_1EB920_001eb920(p3fes::EEContext& ctx) { Cpu(ctx).sub_1EB920(); }
void fn_sub_1EBA50_001eba50(p3fes::EEContext& ctx) { Cpu(ctx).sub_1EBA50(); }
void fn_sub_1EBA80_001eba80(p3fes::EEContext& ctx) { Cpu(ctx).sub_1EBA80(); }
void fn_sub_1EBD80_001ebd80(p3fes::EEContext& ctx) { Cpu(ctx).sub_1EBD80(); }
void fn_sub_1ECD90_001ecd90(p3fes::EEContext& ctx) { Cpu(ctx).sub_1ECD90(); }
void fn_sub_1ECEC0_001ecec0(p3fes::EEContext& ctx) { Cpu(ctx).sub_1ECEC0(); }
void fn_sub_1ED080_001ed080(p3fes::EEContext& ctx) { Cpu(ctx).sub_1ED080(); }
void fn_sub_1ED0B0_001ed0b0(p3fes::EEContext& ctx) { Cpu(ctx).sub_1ED0B0(); }
void fn_sub_1ED0D0_001ed0d0(p3fes::EEContext& ctx) { Cpu(ctx).sub_1ED0D0(); }
void fn_sub_1ED0F0_001ed0f0(p3fes::EEContext& ctx) { Cpu(ctx).sub_1ED0F0(); }
void fn_sub_1ED8A0_001ed8a0(p3fes::EEContext& ctx) { Cpu(ctx).sub_1ED8A0(); }
void fn_sub_1ED9E0_001ed9e0(p3fes::EEContext& ctx) { Cpu(ctx).sub_1ED9E0(); }
void fn_sub_1EDA00_001eda00(p3fes::EEContext& ctx) { Cpu(ctx).sub_1EDA00(); }
void fn_sub_1EDA90_001eda90(p3fes::EEContext& ctx) { Cpu(ctx).sub_1EDA90(); }
void fn_sub_1EDBE0_001edbe0(p3fes::EEContext& ctx) { Cpu(ctx).sub_1EDBE0(); }
void fn_sub_1EDED0_001eded0(p3fes::EEContext& ctx) { Cpu(ctx).sub_1EDED0(); }
void fn_sub_1EE1D0_001ee1d0(p3fes::EEContext& ctx) { Cpu(ctx).sub_1EE1D0(); }
void fn_nullsub_10_001ee220(p3fes::EEContext& ctx) { Cpu(ctx).nullsub_10(); }
void fn_sub_1EE230_001ee230(p3fes::EEContext& ctx) { Cpu(ctx).sub_1EE230(); }
void fn_sub_1EEE40_001eee40(p3fes::EEContext& ctx) { Cpu(ctx).sub_1EEE40(); }
void fn_sub_1EEFC0_001eefc0(p3fes::EEContext& ctx) { Cpu(ctx).sub_1EEFC0(); }
void fn_sub_1EF000_001ef000(p3fes::EEContext& ctx) { Cpu(ctx).sub_1EF000(); }

void fn_sub_320060_00320060(p3fes::EEContext& ctx) { Cpu(ctx).sub_320060(); }
void fn_nullsub_106_00320070(p3fes::EEContext& ctx) { Cpu(ctx).nullsub_106(); }
void fn_sub_320080_00320080(p3fes::EEContext& ctx) { Cpu(ctx).sub_320080(); }
void fn_sub_320380_00320380(p3fes::EEContext& ctx) { Cpu(ctx).sub_320380(); }
void fn_sub_3204A0_003204a0(p3fes::EEContext& ctx) { Cpu(ctx).sub_3204A0(); }
void fn_sub_320640_00320640(p3fes::EEContext& ctx) { Cpu(ctx).sub_320640(); }
void fn_sub_320770_00320770(p3fes::EEContext& ctx) { Cpu(ctx).sub_320770(); }
void fn_sub_320810_00320810(p3fes::EEContext& ctx) { Cpu(ctx).sub_320810(); }
void fn_sub_320BA0_00320ba0(p3fes::EEContext& ctx) { Cpu(ctx).sub_320BA0(); }
void fn_sub_320CF0_00320cf0(p3fes::EEContext& ctx) { Cpu(ctx).sub_320CF0(); }
void fn_sub_320DA0_00320da0(p3fes::EEContext& ctx) { Cpu(ctx).sub_320DA0(); }
void fn_sub_320DE0_00320de0(p3fes::EEContext& ctx) { Cpu(ctx).sub_320DE0(); }
void fn_sub_320F70_00320f70(p3fes::EEContext& ctx) { Cpu(ctx).sub_320F70(); }
void fn_sub_321050_00321050(p3fes::EEContext& ctx) { Cpu(ctx).sub_321050(); }
void fn_sub_321070_00321070(p3fes::EEContext& ctx) { Cpu(ctx).sub_321070(); }
void fn_sub_3210A0_003210a0(p3fes::EEContext& ctx) { Cpu(ctx).sub_3210A0(); }
void fn_sub_3210C0_003210c0(p3fes::EEContext& ctx) { Cpu(ctx).sub_3210C0(); }
void fn_sub_321120_00321120(p3fes::EEContext& ctx) { Cpu(ctx).sub_321120(); }
void fn_sub_321130_00321130(p3fes::EEContext& ctx) { Cpu(ctx).sub_321130(); }
void fn_sub_321140_00321140(p3fes::EEContext& ctx) { Cpu(ctx).link_bank(0x957920u, 24, false); }
void fn_sub_321180_00321180(p3fes::EEContext& ctx) { Cpu(ctx).link_bank(0x957820u, 44, true); }
void fn_sub_3211D0_003211d0(p3fes::EEContext& ctx) { Cpu(ctx).link_bank(0x957720u, 44, true); }
void fn_sub_321220_00321220(p3fes::EEContext& ctx) { Cpu(ctx).link_bank(0x957620u, 100, false); }
void fn_sub_321260_00321260(p3fes::EEContext& ctx) { Cpu(ctx).link_bank(0x957520u, 92, false); }
void fn_sub_3212A0_003212a0(p3fes::EEContext& ctx) { Cpu(ctx).link_bank(0x957420u, 108, false); }
void fn_sub_3212E0_003212e0(p3fes::EEContext& ctx) { Cpu(ctx).link_bank(0x957320u, 156, false); }
void fn_sub_321320_00321320(p3fes::EEContext& ctx) { Cpu(ctx).sub_321320(); }
void fn_effMng_UpdateEffectProgramTask_00321a60(p3fes::EEContext& ctx) { Cpu(ctx).effMng_UpdateEffectProgramTask(); }
void fn_effMng_UpdateEffect3dTask_00321cb0(p3fes::EEContext& ctx) { Cpu(ctx).layer_task(0x321cbcu, 2, true); }
void fn_effMng_UpdateEffect2dTask_00321e20(p3fes::EEContext& ctx) { Cpu(ctx).layer_task(0x321e2cu, 5, true); }
void fn_sub_321FE0_00321fe0(p3fes::EEContext& ctx) { Cpu(ctx).layer_task(0x321fecu, 8, false); }
void fn_sub_321F10_00321f10(p3fes::EEContext& ctx) { Cpu(ctx).sub_321F10(); }
void fn_sub_3226B0_003226b0(p3fes::EEContext& ctx) { Cpu(ctx).sub_3226B0(); }
void fn_sub_322AB0_00322ab0(p3fes::EEContext& ctx) { Cpu(ctx).sub_322AB0(); }
void fn_sub_322D10_00322d10(p3fes::EEContext& ctx) { Cpu(ctx).sub_322D10(); }
void fn_sub_322D40_00322d40(p3fes::EEContext& ctx) { Cpu(ctx).sub_322D40(); }
void fn_sub_322DA0_00322da0(p3fes::EEContext& ctx) { Cpu(ctx).sub_322DA0(); }
void fn_sub_322FB0_00322fb0(p3fes::EEContext& ctx) { Cpu(ctx).sub_322FB0(); }
void fn_sub_322FD0_00322fd0(p3fes::EEContext& ctx) { Cpu(ctx).sub_322FD0(); }
void fn_sub_323240_00323240(p3fes::EEContext& ctx) { Cpu(ctx).grid_mesh(true); }
void fn_sub_3233A0_003233a0(p3fes::EEContext& ctx) { Cpu(ctx).grid_mesh(false); }
void fn_sub_323640_00323640(p3fes::EEContext& ctx) { Cpu(ctx).sub_323640(); }
void fn_sub_323860_00323860(p3fes::EEContext& ctx) { Cpu(ctx).sub_323860(); }
void fn_sub_323880_00323880(p3fes::EEContext& ctx) { Cpu(ctx).sub_323880(); }
void fn_sub_3238D0_003238d0(p3fes::EEContext& ctx) { Cpu(ctx).sub_3238D0(); }
void fn_sub_323920_00323920(p3fes::EEContext& ctx) { Cpu(ctx).sub_323920(); }
void fn_sub_323A30_00323a30(p3fes::EEContext& ctx) { Cpu(ctx).sub_323A30(); }
void fn_sub_323B90_00323b90(p3fes::EEContext& ctx) { Cpu(ctx).sub_323B90(); }
void fn_sub_323BF0_00323bf0(p3fes::EEContext& ctx) { Cpu(ctx).sub_323BF0(); }
void fn_sub_323E10_00323e10(p3fes::EEContext& ctx) { Cpu(ctx).band_mesh(false); }
void fn_sub_323FB0_00323fb0(p3fes::EEContext& ctx) { Cpu(ctx).band_mesh(true); }

}  // namespace p3fes::recomp_gen

// =====================================================================================================================
// The functions wave 10 left out (heap, printf, file I/O; taken since the stand-ins, 2026-10-21): the after-effect
// allocators and builders, the effect-manager pools, mesh creators and task set-up, the after-effect render task's
// creation. p3fes_handgen bodies on the register view hg_cpu.h (faithful by construction); roles above each one.
// Every body keeps the recompiled body's registers, frame, spills, $ra links, cycle charges and check points.
// =====================================================================================================================

namespace p3fes::recomp_gen {
void fn_H_Cdvd_Destroy_00100ec0(p3fes::EEContext&);
void fn_H_Cdvd_ReadSync_001023a0(p3fes::EEContext&);
void fn_H_Cdvd_Request_00100d80(p3fes::EEContext&);
void fn_effAfter_CreateAfterEffectRenderTask_001eef20(p3fes::EEContext&);
void fn_effMng_CreateEffectProgramTasks_00322010(p3fes::EEContext&);
void fn_kwlnTaskCreate_00194b20(p3fes::EEContext&);
void fn_kwlnTaskInitEx_00194e10(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_1E7CE0_001e7ce0(p3fes::EEContext&);
void fn_sub_1E7DE0_001e7de0(p3fes::EEContext&);
void fn_sub_1E8E80_001e8e80(p3fes::EEContext&);
void fn_sub_1E9920_001e9920(p3fes::EEContext&);
void fn_sub_1E9A90_001e9a90(p3fes::EEContext&);
void fn_sub_1ED8A0_001ed8a0(p3fes::EEContext&);
void fn_sub_1EE2E0_001ee2e0(p3fes::EEContext&);
void fn_sub_1EEB90_001eeb90(p3fes::EEContext&);
void fn_sub_1EF340_001ef340(p3fes::EEContext&);
void fn_sub_320230_00320230(p3fes::EEContext&);
void fn_sub_320290_00320290(p3fes::EEContext&);
void fn_sub_320880_00320880(p3fes::EEContext&);
void fn_sub_320DA0_00320da0(p3fes::EEContext&);
void fn_sub_320F70_00320f70(p3fes::EEContext&);
void fn_sub_320FB0_00320fb0(p3fes::EEContext&);
void fn_sub_321010_00321010(p3fes::EEContext&);
void fn_sub_321050_00321050(p3fes::EEContext&);
void fn_sub_3210C0_003210c0(p3fes::EEContext&);
void fn_sub_322530_00322530(p3fes::EEContext&);
void fn_sub_3225D0_003225d0(p3fes::EEContext&);
void fn_sub_322660_00322660(p3fes::EEContext&);
void fn_sub_3226B0_003226b0(p3fes::EEContext&);
void fn_sub_322880_00322880(p3fes::EEContext&);
void fn_sub_322A20_00322a20(p3fes::EEContext&);
void fn_sub_322DC0_00322dc0(p3fes::EEContext&);
void fn_sub_322F20_00322f20(p3fes::EEContext&);
void fn_sub_3230F0_003230f0(p3fes::EEContext&);
void fn_sub_3234F0_003234f0(p3fes::EEContext&);
void fn_sub_3237C0_003237c0(p3fes::EEContext&);
void fn_sub_323C20_00323c20(p3fes::EEContext&);
void fn_sub_347D00_00347d00(p3fes::EEContext&);
void fn_sub_34BD10_0034bd10(p3fes::EEContext&);
void fn_sub_351C20_00351c20(p3fes::EEContext&);
void fn_sub_3580F0_003580f0(p3fes::EEContext&);
void fn_sub_474210_00474210(p3fes::EEContext&);
void fn_sub_474630_00474630(p3fes::EEContext&);
void fn_sub_491880_00491880(p3fes::EEContext&);
void fn_sub_4919B0_004919b0(p3fes::EEContext&);
void fn_sub_491A80_00491a80(p3fes::EEContext&);
void fn_sub_492D10_00492d10(p3fes::EEContext&);
void fn_sub_4933D0_004933d0(p3fes::EEContext&);
void fn_sub_493710_00493710(p3fes::EEContext&);
void fn_sub_493B60_00493b60(p3fes::EEContext&);
void fn_sub_494BE0_00494be0(p3fes::EEContext&);
void fn_sub_494CC0_00494cc0(p3fes::EEContext&);
void fn_sub_494D50_00494d50(p3fes::EEContext&);
void fn_sub_4C3880_004c3880(p3fes::EEContext&);
void fn_sub_4C38C0_004c38c0(p3fes::EEContext&);
void fn_sub_4C5250_004c5250(p3fes::EEContext&);
void fn_sub_4C5620_004c5620(p3fes::EEContext&);
void fn_sub_4CAF10_004caf10(p3fes::EEContext&);
void fn_sub_4CAF80_004caf80(p3fes::EEContext&);
void fn_sub_4D0F00_004d0f00(p3fes::EEContext&);
void fn_sub_4D1260_004d1260(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x001E9920 sub_1E9920 -- 356 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1E9920 [allocate a trail ring]: $a0 the 76-byte ring, $a1 its trail entry {+8 capacity, +12 segments, +16
// shape}. One RwMalloc block of 72 * (capacity + segments) bytes holds the rails +16 / +20 / +24 / +28 / +32 / +36
// / +48 (12 * capacity bytes apart); +40 / +44 two arc tables (sub_1E7CE0(capacity - 1, 64)), +52 a matrix
// (sub_4C38C0); +0 the entry, +4 / +8 / +12 cleared, +72 u16 the shape.
void sub_1E9920(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001e9920
    enter(ctx, 89);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a2 = 0;
    lw(v1, a1, 8);
    v0 = sll(v1, 1);
    a0 = addu(v0, v1);
    v0 = sll(a0, 3);
    v1 = addu(a2, v0);
    v0 = sll(a0, 4);
    a0 = addu(v1, v0);
    lw(v0, a1, 12);
    v1 = sll(v0, 1);
    v0 = sll(v0, 4);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    a0 = addu(a0, v0);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178: the RW malloc slot
    jalr(ctx, 0x1E997Cu, v0.u());
    sw(v0, s1, 16);
    lw(a0, s0, 8);
    v1 = sll(a0, 1);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    a0 = addu(v0, v1);
    sw(a0, s1, 20);
    lw(v1, s0, 8);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    a0 = addu(a0, v0);
    sw(a0, s1, 24);
    lw(v1, s0, 8);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    a0 = addu(a0, v0);
    sw(a0, s1, 28);
    lw(v1, s0, 8);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    a0 = addu(a0, v0);
    sw(a0, s1, 32);
    lw(v1, s0, 8);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    a0 = addu(a0, v0);
    sw(a0, s1, 36);
    lw(v1, s0, 8);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    v0 = addu(a0, v0);
    sw(v0, s1, 48);
    sw(zero, s1, 4);
    sw(s0, s1, 0);
    sw(zero, s1, 8);
    sw(zero, s1, 12);
    lw(v0, s0, 8);
    a0 = addiu(v0, -1);
    a1 = 64;
    jal(ctx, 0x1E9A34u, gen::fn_sub_1E7CE0_001e7ce0);
    sw(v0, s1, 40);
    lw(v0, s0, 8);
    a0 = addiu(v0, -1);
    a1 = 64;
    jal(ctx, 0x1E9A4Cu, gen::fn_sub_1E7CE0_001e7ce0);
    sw(v0, s1, 44);
    jal(ctx, 0x1E9A58u, gen::fn_sub_4C38C0_004c38c0);
    sw(v0, s1, 52);
    lw(v1, s0, 16);
    sh(v1, s1, 72);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001E9A90 sub_1E9A90 -- 92 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1E9A90 [free a trail ring]: the matrix (+52, sub_4C3880), the two arc tables (+40 / +44, sub_1E7DE0), the
// rails block (+16, RwFree).
void sub_1E9A90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001e9a90
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, 52);
    jal(ctx, 0x1E9AA4u, gen::fn_sub_4C3880_004c3880);
    lw(a0, s0, 40);
    jal(ctx, 0x1E9AB0u, gen::fn_sub_1E7DE0_001e7de0);
    lw(a0, s0, 44);
    jal(ctx, 0x1E9ABCu, gen::fn_sub_1E7DE0_001e7de0);
    lw(a0, s0, 16);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C: the RW free slot
    jalr(ctx, 0x1E9AD0u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001EE2E0 sub_1EE2E0 -- 2224 bytes; frame 0x1B0: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1EE2E0 [unpack an after-effect pack]: $a0 the raw pack {+0 type 100 / 101, +4 word, +8 u16 trails, +10 u16
// curves, +12 u16 colour sets}, then the 56-byte curves, the colour sets (8 bytes, 4 more, 16 colour bytes), the
// trails (24 bytes for type 100, 32 for 101) each followed by its data. One RwMalloc block: the 36-byte descriptor
// {+0 word, +4 / +6 / +8 u16 counts, +12 the 24-byte trails, +16 the 52-byte curves, +20 the 24-byte colour sets,
// +24 the {word, word} pairs, +28 the data pointers}, then the data copies (memcpy). A trail's curve / colour-set
// id becomes a pointer (an unknown id: the slot past the last); colour-set bit 0 takes the after effects' texture
// (0x7CE2D4). The asserts (sub_19D3F0, eff_afpack.c lines 433 / 445 / 459 / 561) mark the cases the format never
// has: extra colour-set blocks, other pack types.
void sub_1EE2E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x001ee2e0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1B0);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s1 = s0;
    s0 = addiu(s0, 16);
    a0 = 0;
    lhu(v1, s1, 10);
    for (;;) {
        // 0x001ee330
        charge(ctx, 3);
        v0 = slt(a0, v1);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001ee31c
        charge(ctx, 5);
        v0 = sll(a0, 2);
        v0 = addu(v0, sp);
        sw(s0, v0, 368);
        s0 = addiu(s0, 56);
        a0 = addiu(a0, 1);
    }
    // 0x001ee33c
    charge(ctx, 3);
    s3 = 0;
    for (;;) {
        // 0x001ee3d8
        charge(ctx, 4);
        lhu(v0, s1, 12);
        v0 = slt(s3, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001ee348
        charge(ctx, 9);
        v0 = sll(s3, 2);
        v0 = addu(v0, sp);
        v0 = addiu(v0, 304);
        sw(s0, v0, 0);
        s0 = addiu(s0, 8);
        lw(s2, v0, 0);
        lhu(v0, s2, 4);
        if (v0 == 0) {
            // 0x001ee374
            charge(ctx, 3);
            s0 = addiu(s0, 4);
        } else {
            // 0x001ee36c
            charge(ctx, 2);
            // 0x001ee380
            charge(ctx, 5);
            a0 = 0x680000;
            a0 = addiu(a0, 17672);  // "eff_afpack.c"
            a1 = 433;
            jal(ctx, 0x1EE38Cu, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x001ee394
        charge(ctx, 6);
        v0 = sll(s3, 2);
        v0 = addu(v0, sp);
        sw(s0, v0, 240);
        lhu(v0, s2, 6);
        if (v0 == 0) {
            // 0x001ee3b4
            charge(ctx, 3);
            s0 = addiu(s0, 16);
        } else {
            // 0x001ee3ac
            charge(ctx, 2);
            // 0x001ee3c0
            charge(ctx, 5);
            a0 = 0x680000;
            a0 = addiu(a0, 17672);  // "eff_afpack.c"
            a1 = 445;
            jal(ctx, 0x1EE3CCu, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x001ee3d4
        charge(ctx, 1);
        s3 = addiu(s3, 1);
    }
    // 0x001ee3e8
    charge(ctx, 3);
    s4 = 0;
    for (;;) {
        // 0x001ee4a4
        charge(ctx, 4);
        lhu(v0, s1, 8);
        v1 = slt(s4, v0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001ee3f4
        charge(ctx, 8);
        s3 = sll(s4, 2);
        v0 = addu(s3, sp);
        s2 = addiu(v0, 176);
        sw(s0, s2, 0);
        lw(v1, s1, 0);
        v0 = 101;
        if (v1 == v0) {
            // 0x001ee434
            charge(ctx, 3);
            s0 = addiu(s0, 32);
        } else {
            // 0x001ee414
            charge(ctx, 3);
            v0 = 100;
            if (v1 == v0) {
                // 0x001ee428
                charge(ctx, 3);
                s0 = addiu(s0, 24);
            } else {
                // 0x001ee420
                charge(ctx, 2);
                // 0x001ee440
                charge(ctx, 5);
                a0 = 0x680000;
                a0 = addiu(a0, 17672);  // "eff_afpack.c"
                a1 = 459;
                jal(ctx, 0x1EE44Cu, gen::fn_sub_19D3F0_0019d3f0);
            }
        }
        // 0x001ee454
        charge(ctx, 6);
        v0 = addu(s3, sp);
        sw(s0, v0, 112);
        lw(v1, s1, 0);
        v0 = 101;
        if (v1 == v0) {
            // 0x001ee494
            charge(ctx, 3);
            lw(v0, s2, 0);
            lw(v0, v0, 28);
            s0 = addu(s0, v0);
        } else {
            // 0x001ee46c
            charge(ctx, 3);
            v0 = 100;
            if (v1 == v0) {
                // 0x001ee480
                charge(ctx, 5);
                lw(v0, s2, 0);
                lw(v0, v0, 20);
                s0 = addu(s0, v0);
            } else {
                // 0x001ee478
                charge(ctx, 2);
            }
        }
        // 0x001ee4a0
        charge(ctx, 1);
        s4 = addiu(s4, 1);
    }
    // 0x001ee4b4
    charge(ctx, 25);
    a3 = 0;
    a0 = addiu(a3, 36);
    v1 = sll(v0, 1);
    v1 = addu(v1, v0);
    v1 = sll(v1, 3);
    a1 = addu(a0, v1);
    lhu(a0, s1, 10);
    v1 = sll(a0, 1);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    a1 = addu(a1, v1);
    lhu(a0, s1, 12);
    v1 = sll(a0, 1);
    v1 = addu(v1, a0);
    v1 = sll(v1, 3);
    a0 = addu(a1, v1);
    v1 = sll(v0, 2);
    a3 = addu(a0, v1);
    a2 = 0;
    a0 = 100;
    a1 = 101;
    for (;;) {
        // 0x001ee568
        charge(ctx, 3);
        v1 = slt(a2, v0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001ee518
        charge(ctx, 3);
        lw(v1, s1, 0);
        if (v1 == a1) {
            // 0x001ee550
            charge(ctx, 5);
            v1 = sll(a2, 2);
            v1 = addu(v1, sp);
            lw(v1, v1, 176);
            lw(v1, v1, 28);
            a3 = addu(a3, v1);
        } else {
            // 0x001ee524
            charge(ctx, 2);
            if (v1 == a0) {
                // 0x001ee534
                charge(ctx, 7);
                v1 = sll(a2, 2);
                v1 = addu(v1, sp);
                lw(v1, v1, 176);
                lw(v1, v1, 20);
                a3 = addu(a3, v1);
            } else {
                // 0x001ee52c
                charge(ctx, 2);
            }
        }
        // 0x001ee564
        charge(ctx, 1);
        a2 = addiu(a2, 1);
    }
    // 0x001ee574
    charge(ctx, 38);
    v0 = sll(v0, 3);
    a0 = addu(a3, v0);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178: the RW malloc slot
    jalr(ctx, 0x1EE588u, v0.u());
    s2 = v0;
    a1 = addiu(v0, 36);
    sw(a1, v0, 12);
    lhu(a0, s1, 8);
    v1 = sll(a0, 1);
    v1 = addu(v1, a0);
    v1 = sll(v1, 3);
    a1 = addu(a1, v1);
    sw(a1, v0, 16);
    lhu(a0, s1, 10);
    v1 = sll(a0, 1);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    a1 = addu(a1, v1);
    sw(a1, v0, 20);
    lhu(a0, s1, 12);
    v1 = sll(a0, 1);
    v1 = addu(v1, a0);
    v1 = sll(v1, 3);
    v1 = addu(a1, v1);
    sw(v1, v0, 28);
    lhu(v0, s1, 8);
    v0 = sll(v0, 2);
    v0 = addu(v1, v0);
    a3 = 0;
    a0 = 100;
    a1 = 101;
    for (;;) {
        // 0x001ee664
        charge(ctx, 4);
        lhu(v1, s1, 8);
        v1 = slt(a3, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001ee60c
        charge(ctx, 7);
        a2 = sll(a3, 2);
        lw(v1, s2, 28);
        v1 = addu(v1, a2);
        sw(v0, v1, 0);
        lw(v1, s1, 0);
        if (v1 == a1) {
            // 0x001ee650
            charge(ctx, 4);
            v1 = addu(a2, sp);
            lw(v1, v1, 176);
            lw(v1, v1, 28);
            v0 = addu(v0, v1);
        } else {
            // 0x001ee628
            charge(ctx, 2);
            if (v1 == a0) {
                // 0x001ee638
                charge(ctx, 6);
                v1 = addu(a2, sp);
                lw(v1, v1, 176);
                lw(v1, v1, 20);
                v0 = addu(v0, v1);
            } else {
                // 0x001ee630
                charge(ctx, 2);
            }
        }
        // 0x001ee660
        charge(ctx, 1);
        a3 = addiu(a3, 1);
    }
    // 0x001ee674
    charge(ctx, 12);
    sw(v0, s2, 24);
    lw(v0, s1, 4);
    sw(v0, s2, 0);
    lhu(v0, s1, 8);
    sh(v0, s2, 4);
    lhu(v0, s1, 10);
    sh(v0, s2, 6);
    lhu(v0, s1, 12);
    sh(v0, s2, 8);
    a0 = 0;
    for (;;) {
        // 0x001ee738
        charge(ctx, 4);
        lhu(v0, s1, 10);
        v0 = slt(a0, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001ee6a4
        charge(ctx, 37);
        v0 = sll(a0, 1);
        v0 = addu(v0, a0);
        v0 = sll(v0, 2);
        v0 = addu(v0, a0);
        v1 = sll(v0, 2);
        lw(v0, s2, 16);
        v1 = addu(v0, v1);
        v0 = sll(a0, 2);
        v0 = addu(v0, sp);
        lw(v0, v0, 368);
        lwc1(f0, v0, 4);
        swc1(f0, v1, 0);
        lwc1(f0, v0, 8);
        swc1(f0, v1, 4);
        lwc1(f0, v0, 12);
        swc1(f0, v1, 8);
        lwc1(f0, v0, 16);
        swc1(f0, v1, 12);
        lwc1(f0, v0, 20);
        swc1(f0, v1, 16);
        lwc1(f0, v0, 24);
        swc1(f0, v1, 20);
        lwc1(f0, v0, 28);
        swc1(f0, v1, 24);
        lwc1(f0, v0, 32);
        swc1(f0, v1, 28);
        lwc1(f0, v0, 36);
        swc1(f0, v1, 36);
        lwc1(f0, v0, 40);
        swc1(f0, v1, 32);
        lwc1(f0, v0, 44);
        swc1(f0, v1, 40);
        lwc1(f0, v0, 48);
        swc1(f0, v1, 44);
        lwc1(f0, v0, 52);
        swc1(f0, v1, 48);
        a0 = addiu(a0, 1);
    }
    // 0x001ee748
    charge(ctx, 3);
    s0 = 0;
    for (;;) {
        // 0x001ee830
        charge(ctx, 4);
        lhu(v0, s1, 12);
        v0 = slt(s0, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001ee754
        charge(ctx, 14);
        v0 = sll(s0, 1);
        v0 = addu(v0, s0);
        v1 = sll(v0, 3);
        lw(v0, s2, 20);
        v1 = addu(v0, v1);
        v0 = sll(s0, 2);
        v0 = addu(v0, sp);
        lw(a1, v0, 304);
        lw(v0, v0, 240);
        lhu(a0, a1, 2);
        sw(a0, v1, 0);
        a0 = a0 & 0x1;
        if (a0 == 0) {
            // 0x001ee79c
            charge(ctx, 1);
            sw(zero, v1, 4);
        } else {
            // 0x001ee78c
            charge(ctx, 4);
            lw(a0, gp, -18972);  // 0x7CE2D4: the after effects' texture
            sw(a0, v1, 4);
        }
        // 0x001ee7a0
        charge(ctx, 3);
        lhu(a0, a1, 6);
        if (a0 == 0) {
            // 0x001ee7b4
            charge(ctx, 3);
            a3 = 0;
            for (;;) {
                // 0x001ee804
                charge(ctx, 3);
                a0 = slti(a3, 4);
                if (a0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001ee7c0
                charge(ctx, 17);
                a0 = sll(a3, 2);
                a2 = addu(v0, a0);
                a0 = sra(a3, 1);
                a0 = sll(a0, 3);
                a1 = addu(v1, a0);
                a0 = a3 & 0x1;
                a0 = sll(a0, 2);
                a1 = addu(a1, a0);
                lbu(a0, a2, 0);
                sb(a0, a1, 8);
                lbu(a0, a2, 1);
                sb(a0, a1, 9);
                lbu(a0, a2, 2);
                sb(a0, a1, 10);
                lbu(a0, a2, 3);
                sb(a0, a1, 11);
                a3 = addiu(a3, 1);
            }
            // 0x001ee810
            charge(ctx, 2);
        } else {
            // 0x001ee7ac
            charge(ctx, 2);
            // 0x001ee818
            charge(ctx, 5);
            a0 = 0x680000;
            a0 = addiu(a0, 17672);  // "eff_afpack.c"
            a1 = 561;
            jal(ctx, 0x1EE824u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x001ee82c
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x001ee840
    charge(ctx, 3);
    s0 = 0;
    for (;;) {
        // 0x001eeb54
        charge(ctx, 4);
        lhu(v0, s1, 8);
        v0 = slt(s0, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001ee84c
        charge(ctx, 12);
        v0 = sll(s0, 1);
        v0 = addu(v0, s0);
        v1 = sll(v0, 3);
        lw(v0, s2, 12);
        v1 = addu(v0, v1);
        v0 = sll(s0, 2);
        v0 = addu(v0, sp);
        lw(v0, v0, 176);
        lw(a1, s1, 0);
        a0 = 101;
        if (a1 == a0) {
            // 0x001ee89c
            charge(ctx, 1);
            lhu(s5, v0, 2);
        } else {
            // 0x001ee87c
            charge(ctx, 3);
            a0 = 100;
            if (a1 == a0) {
                // 0x001ee890
                charge(ctx, 3);
                lhu(s5, v0, 2);
            } else {
                // 0x001ee888
                charge(ctx, 2);
            }
        }
        // 0x001ee8a0
        charge(ctx, 4);
        a2 = 0;
        lhu(a1, s1, 10);
        for (;;) {
            // 0x001ee8cc
            charge(ctx, 3);
            a0 = slt(a2, a1);
            if (a0 != 0) {
                backedge(ctx);
                // 0x001ee8b0
                charge(ctx, 6);
                a0 = sll(a2, 2);
                a0 = addu(a0, sp);
                lw(a0, a0, 368);
                lhu(a0, a0, 0);
                if (s5 != a0) {
                    // 0x001ee8c8
                    charge(ctx, 1);
                    a2 = addiu(a2, 1);
                    continue;
                }
            }
            break;
        }
        // 0x001ee8d8
        charge(ctx, 12);
        a0 = sll(a2, 1);
        a0 = addu(a0, a2);
        a0 = sll(a0, 2);
        a0 = addu(a0, a2);
        a1 = sll(a0, 2);
        lw(a0, s2, 16);
        a0 = addu(a0, a1);
        sw(a0, v1, 0);
        lw(a1, s1, 0);
        a0 = 101;
        if (a1 == a0) {
            // 0x001ee928
            charge(ctx, 1);
            lhu(s5, v0, 4);
        } else {
            // 0x001ee908
            charge(ctx, 3);
            a0 = 100;
            if (a1 == a0) {
                // 0x001ee91c
                charge(ctx, 3);
                lhu(s5, v0, 4);
            } else {
                // 0x001ee914
                charge(ctx, 2);
            }
        }
        // 0x001ee92c
        charge(ctx, 4);
        a2 = 0;
        lhu(a1, s1, 12);
        for (;;) {
            // 0x001ee958
            charge(ctx, 3);
            a0 = slt(a2, a1);
            if (a0 != 0) {
                backedge(ctx);
                // 0x001ee93c
                charge(ctx, 6);
                a0 = sll(a2, 2);
                a0 = addu(a0, sp);
                lw(a0, a0, 304);
                lhu(a0, a0, 0);
                if (s5 != a0) {
                    // 0x001ee954
                    charge(ctx, 1);
                    a2 = addiu(a2, 1);
                    continue;
                }
            }
            break;
        }
        // 0x001ee964
        charge(ctx, 10);
        a0 = sll(a2, 1);
        a0 = addu(a0, a2);
        a1 = sll(a0, 3);
        lw(a0, s2, 20);
        a0 = addu(a0, a1);
        sw(a0, v1, 4);
        lw(a1, s1, 0);
        a0 = 101;
        if (a1 == a0) {
            // 0x001ee9b0
            charge(ctx, 2);
            lhu(a0, v0, 16);
            sw(a0, v1, 8);
        } else {
            // 0x001ee98c
            charge(ctx, 3);
            a0 = 100;
            if (a1 == a0) {
                // 0x001ee9a0
                charge(ctx, 4);
                lhu(a0, v0, 16);
                sw(a0, v1, 8);
            } else {
                // 0x001ee998
                charge(ctx, 2);
            }
        }
        // 0x001ee9b8
        charge(ctx, 4);
        lw(a1, s1, 0);
        a0 = 101;
        if (a1 == a0) {
            // 0x001ee9ec
            charge(ctx, 2);
            lhu(a0, v0, 18);
            sw(a0, v1, 12);
        } else {
            // 0x001ee9c8
            charge(ctx, 3);
            a0 = 100;
            if (a1 == a0) {
                // 0x001ee9dc
                charge(ctx, 4);
                lhu(a0, v0, 18);
                sw(a0, v1, 12);
            } else {
                // 0x001ee9d4
                charge(ctx, 2);
            }
        }
        // 0x001ee9f4
        charge(ctx, 4);
        lw(a1, s1, 0);
        a0 = 101;
        if (a1 == a0) {
            // 0x001eea24
            charge(ctx, 2);
            lhu(a0, v0, 20);
            sw(a0, v1, 16);
        } else {
            // 0x001eea04
            charge(ctx, 3);
            a0 = 100;
            if (a1 == a0) {
                // 0x001eea18
                charge(ctx, 3);
                sw(zero, v1, 16);
            } else {
                // 0x001eea10
                charge(ctx, 2);
            }
        }
        // 0x001eea2c
        charge(ctx, 4);
        lw(a1, s1, 0);
        a0 = 101;
        if (a1 == a0) {
            // 0x001eea60
            charge(ctx, 2);
            lwc1(f0, v0, 24);
            swc1(f0, v1, 20);
        } else {
            // 0x001eea3c
            charge(ctx, 3);
            a0 = 100;
            if (a1 == a0) {
                // 0x001eea50
                charge(ctx, 4);
                a0 = 0x41200000;
                sw(a0, v1, 20);
            } else {
                // 0x001eea48
                charge(ctx, 2);
            }
        }
        // 0x001eea68
        charge(ctx, 4);
        lw(a0, s1, 0);
        v1 = 101;
        if (a0 == v1) {
            // 0x001eeab8
            charge(ctx, 9);
            a1 = sll(s0, 3);
            lw(a0, v0, 8);
            lw(v1, s2, 24);
            v1 = addu(v1, a1);
            sw(a0, v1, 0);
            lw(a0, v0, 12);
            lw(v1, s2, 24);
            v1 = addu(v1, a1);
            sw(a0, v1, 4);
        } else {
            // 0x001eea78
            charge(ctx, 3);
            v1 = 100;
            if (a0 == v1) {
                // 0x001eea8c
                charge(ctx, 11);
                a1 = sll(s0, 3);
                lw(a0, v0, 8);
                lw(v1, s2, 24);
                v1 = addu(v1, a1);
                sw(a0, v1, 0);
                lw(a0, v0, 12);
                lw(v1, s2, 24);
                v1 = addu(v1, a1);
                sw(a0, v1, 4);
            } else {
                // 0x001eea84
                charge(ctx, 2);
            }
        }
        // 0x001eeadc
        charge(ctx, 4);
        lw(a0, s1, 0);
        v1 = 101;
        if (a0 == v1) {
            // 0x001eeb2c
            charge(ctx, 9);
            a1 = sll(s0, 2);
            lw(v1, s2, 28);
            a0 = addu(v1, a1);
            v1 = addu(a1, sp);
            lw(a0, a0, 0);
            lw(a1, v1, 112);
            lw(a2, v0, 28);
            jal(ctx, 0x1EEB48u, gen::fn_memcpy_00521250);
        } else {
            // 0x001eeaec
            charge(ctx, 3);
            v1 = 100;
            if (a0 == v1) {
                // 0x001eeb00
                charge(ctx, 11);
                a1 = sll(s0, 2);
                lw(v1, s2, 28);
                a0 = addu(v1, a1);
                v1 = addu(a1, sp);
                lw(a0, a0, 0);
                lw(a1, v1, 112);
                lw(a2, v0, 20);
                jal(ctx, 0x1EEB1Cu, gen::fn_memcpy_00521250);
            } else {
                // 0x001eeaf8
                charge(ctx, 2);
            }
        }
        // 0x001eeb50
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x001eeb64
    charge(ctx, 11);
    v0 = s2;
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x1B0);
}

// 0x001EEB90 sub_1EEB90 -- 688 bytes; frame 0x80: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1EEB90 [create an after effect]: $a0 the unpacked descriptor. One RwMalloc block: the effect {+0 flags, +4
// the descriptor, +8 the 76-byte rings, +12 {atomic, material} per trail, +16 the 32-byte script states, +20 the
// 24-byte anchor pairs, +32 RGBA FF FF FF FE}. Per trail: the ring (sub_1E9920), a material (sub_494BE0) with the
// colour set's texture when its bit 0 is set (sub_494D50) and colour FF FF FF FE, the trail geometry (sub_1E8E80),
// an atomic (sub_491880) holding it (sub_4919B0) on a new frame (sub_4CAF10, sub_492D10), the geometry unlocked
// (sub_493B60), cleared (sub_1ED8A0) and its creation reference dropped (sub_4933D0). Returns the effect.
void sub_1EEB90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001eeb90
    enter(ctx, 61);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    v0 = 0;
    a1 = addiu(v0, 36);
    lh(a0, a0, 4);
    v1 = sll(a0, 3);
    v0 = addu(v1, a0);
    v0 = sll(v0, 1);
    v0 = addu(v0, a0);
    v0 = sll(v0, 2);
    v0 = addu(a1, v0);
    v1 = addu(v0, v1);
    v0 = sll(a0, 5);
    v1 = addu(v1, v0);
    v0 = sll(a0, 1);
    v0 = addu(v0, a0);
    v0 = sll(v0, 3);
    a0 = addu(v1, v0);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178: the RW malloc slot
    jalr(ctx, 0x1EEC00u, v0.u());
    s1 = v0;
    a1 = addiu(s1, 36);
    sw(a1, v0, 8);
    lh(a0, s2, 4);
    v1 = sll(a0, 3);
    v1 = addu(v1, a0);
    v1 = sll(v1, 1);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    a0 = addu(a1, v1);
    sw(a0, v0, 12);
    lh(v1, s2, 4);
    v1 = sll(v1, 3);
    a0 = addu(a0, v1);
    sw(a0, v0, 16);
    lh(v1, s2, 4);
    v1 = sll(v1, 5);
    v1 = addu(a0, v1);
    sw(v1, v0, 20);
    sw(zero, v0, 0);
    sw(s2, v0, 4);
    a0 = 255;
    sb(a0, v0, 32);
    sb(a0, v0, 33);
    sb(a0, v0, 34);
    v1 = 254;
    sb(v1, v0, 35);
    s0 = 0;
    lh(v0, s2, 4);
    if (i64(v0) > 0) {
        // 0x001eec84
        charge(ctx, 6);
        sb(a0, sp, 0x7C);
        sb(a0, sp, 0x7D);
        sb(a0, sp, 0x7E);
        sb(v1, sp, 0x7F);
        for (;;) {
            // 0x001eee04
            charge(ctx, 4);
            lh(v0, s2, 4);
            v0 = slt(s0, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001eec9c
            charge(ctx, 28);
            v0 = sll(s0, 3);
            v0 = addu(v0, s0);
            v0 = sll(v0, 1);
            v0 = addu(v0, s0);
            s4 = sll(v0, 2);
            lw(v0, s1, 8);
            a0 = addu(v0, s4);
            v0 = sll(s0, 1);
            v0 = addu(v0, s0);
            v1 = sll(v0, 3);
            lw(v0, s2, 12);
            a1 = addu(v0, v1);
            jal(ctx, 0x1EECCCu, gen::fn_sub_1E9920_001e9920);
            s3 = sll(s0, 3);
            jal(ctx, 0x1EECD8u, gen::fn_sub_494BE0_00494be0);
            lw(v1, s1, 12);
            v1 = addu(v1, s3);
            sw(v0, v1, 4);
            lw(v0, s1, 8);
            v0 = addu(v0, s4);
            lw(v0, v0, 0);
            lw(v1, v0, 4);
            lw(v0, v1, 0);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                // 0x001eed0c
                charge(ctx, 6);
                lw(v0, s1, 12);
                v0 = addu(v0, s3);
                lw(a0, v0, 4);
                lw(a1, v1, 4);
                jal(ctx, 0x1EED1Cu, gen::fn_sub_494D50_00494d50);
            }
            // 0x001eed24
            charge(ctx, 56);
            s4 = sll(s0, 3);
            lw(v0, s1, 12);
            v0 = addu(v0, s4);
            lw(a2, v0, 4);
            lbu(a1, sp, 0x7C);
            lbu(a0, sp, 0x7D);
            lbu(v1, sp, 0x7E);
            lbu(v0, sp, 0x7F);
            sb(a1, a2, 4);
            sb(a0, a2, 5);
            sb(v1, a2, 6);
            sb(v0, a2, 7);
            v0 = addu(s4, s0);
            v0 = sll(v0, 1);
            v0 = addu(v0, s0);
            s3 = sll(v0, 2);
            lw(v0, s1, 8);
            a0 = addu(v0, s3);
            lw(v0, s1, 12);
            v0 = addu(v0, s4);
            lw(a1, v0, 4);
            jal(ctx, 0x1EED78u, gen::fn_sub_1E8E80_001e8e80);
            s5 = v0;
            jal(ctx, 0x1EED84u, gen::fn_sub_491880_00491880);
            lw(v1, s1, 12);
            v1 = addu(v1, s4);
            sw(v0, v1, 0);
            lw(v0, s1, 12);
            v0 = addu(v0, s4);
            lw(a0, v0, 0);
            a1 = s5;
            a2 = 0;
            jal(ctx, 0x1EEDACu, gen::fn_sub_4919B0_004919b0);
            jal(ctx, 0x1EEDB4u, gen::fn_sub_4CAF10_004caf10);
            lw(v1, s1, 12);
            v1 = addu(v1, s4);
            lw(a0, v1, 0);
            a1 = v0;
            jal(ctx, 0x1EEDCCu, gen::fn_sub_492D10_00492d10);
            a0 = s5;
            jal(ctx, 0x1EEDD8u, gen::fn_sub_493B60_00493b60);
            lw(v0, s1, 8);
            a0 = addu(v0, s3);
            a1 = s5;
            jal(ctx, 0x1EEDECu, gen::fn_sub_1ED8A0_001ed8a0);
            a0 = s5;
            jal(ctx, 0x1EEDF8u, gen::fn_sub_4933D0_004933d0);
            s0 = addiu(s0, 1);
        }
    }
    // 0x001eee14 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    v0 = s1;
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x001EF340 sub_1EF340 -- 448 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1EF340 [destroy a model's after effects]: $a0 the model. Every live effect (list 0x7CE2CC head / 0x7CE2C8
// tail, +24 prev / +28 next) whose descriptor's +32 is the model is unlinked (asserts, eff_afpack.c 802 / 803, when
// the list is empty), its rings freed (sub_1E9A90), its frames (sub_4CAF80), atomics (sub_491A80) and materials
// (sub_494CC0) destroyed, then the effect and its descriptor freed.
void sub_1EF340(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001ef340
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    lw(s3, gp, -18980);  // 0x7CE2CC: the live list's head
    for (;;) {
        // 0x001ef4d0
        charge(ctx, 2);
        if (s3 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001ef370
        charge(ctx, 6);
        s2 = s3;
        lw(s3, s3, 28);
        lw(v1, s2, 4);
        lw(v1, v1, 32);
        if (v1 == s4) {
            // 0x001ef388
            charge(ctx, 3);
            lw(v0, gp, -18980);  // 0x7CE2CC: the live list's head
            if (v0 == 0) {
                // 0x001ef394
                charge(ctx, 5);
                a0 = 0x680000;
                a0 = addiu(a0, 17672);  // "eff_afpack.c"
                a1 = 802;
                jal(ctx, 0x1EF3A0u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x001ef3a8
            charge(ctx, 3);
            lw(v0, gp, -18984);  // 0x7CE2C8: the live list's tail
            if (v0 == 0) {
                // 0x001ef3b4
                charge(ctx, 5);
                a0 = 0x680000;
                a0 = addiu(a0, 17672);  // "eff_afpack.c"
                a1 = 803;
                jal(ctx, 0x1EF3C0u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x001ef3c8
            charge(ctx, 3);
            lw(v1, s2, 28);
            if (v1 != 0) {
                // 0x001ef3d4
                charge(ctx, 2);
                lw(v0, s2, 24);
                sw(v0, v1, 24);
            }
            // 0x001ef3dc
            charge(ctx, 3);
            lw(v1, s2, 24);
            if (v1 != 0) {
                // 0x001ef3e8
                charge(ctx, 2);
                lw(v0, s2, 28);
                sw(v0, v1, 28);
            }
            // 0x001ef3f0
            charge(ctx, 3);
            lw(v0, gp, -18984);  // 0x7CE2C8: the live list's tail
            if (s2 == v0) {
                // 0x001ef3fc
                charge(ctx, 2);
                lw(v0, s2, 24);
                sw(v0, gp, -18984);  // 0x7CE2C8: the live list's tail
            }
            // 0x001ef404
            charge(ctx, 3);
            lw(v0, gp, -18980);  // 0x7CE2CC: the live list's head
            if (s2 == v0) {
                // 0x001ef410
                charge(ctx, 2);
                lw(v0, s2, 28);
                sw(v0, gp, -18980);  // 0x7CE2CC: the live list's head
            }
            // 0x001ef418
            charge(ctx, 4);
            lw(s5, s2, 4);
            s1 = 0;
            for (;;) {
                // 0x001ef494
                charge(ctx, 5);
                lw(v0, s2, 4);
                lh(v0, v0, 4);
                v0 = slt(s1, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001ef428
                charge(ctx, 27);
                v0 = sll(s1, 3);
                v0 = addu(v0, s1);
                v0 = sll(v0, 1);
                v0 = addu(v0, s1);
                v1 = sll(v0, 2);
                lw(v0, s2, 8);
                a0 = addu(v0, v1);
                jal(ctx, 0x1EF444u, gen::fn_sub_1E9A90_001e9a90);
                s0 = sll(s1, 3);
                lw(v0, s2, 12);
                v0 = addu(v0, s0);
                lw(v0, v0, 0);
                lw(a0, v0, 4);
                jal(ctx, 0x1EF460u, gen::fn_sub_4CAF80_004caf80);
                lw(v0, s2, 12);
                v0 = addu(v0, s0);
                lw(a0, v0, 0);
                jal(ctx, 0x1EF474u, gen::fn_sub_491A80_00491a80);
                lw(v0, s2, 12);
                v0 = addu(v0, s0);
                lw(a0, v0, 4);
                jal(ctx, 0x1EF488u, gen::fn_sub_494CC0_00494cc0);
                s1 = addiu(s1, 1);
            }
            // 0x001ef4a8
            charge(ctx, 10);
            s0 = 0x960000;
            s0 = addiu(s0, 380);  // &0x96017C
            a0 = s2;
            lw(v0, s0, 0);  // 0x96017C: the RW free slot
            jalr(ctx, 0x1EF4B8u, v0.u());
            a0 = s5;
            lw(v0, s0, 0);  // 0x96017C: the RW free slot
            jalr(ctx, 0x1EF4C8u, v0.u());
        }
    }
    // 0x001ef4d8
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00320230 sub_320230 -- 88 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_320230 [new list head]: a 4-byte block (RwMalloc), zeroed (memset) and its word cleared.
void sub_320230(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00320230
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 4;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178: the RW malloc slot
    jalr(ctx, 0x32024Cu, v0.u());
    s0 = v0;
    a0 = s0;
    a1 = 0;
    a2 = 4;
    jal(ctx, 0x320264u, gen::fn_memset_00521408);
    sw(zero, s0, 0);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00320290 sub_320290 -- 228 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_320290 [free an image-sequence list]: $a0 the list head. Per node (+84 next): the four 16-byte slots' image
// data (+12) freed and the slots cleared, the record (+80) released (sub_321010), the node freed; then the head.
void sub_320290(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00320290
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    lw(s3, a0, 0);
    for (;;) {
        // 0x00320334
        charge(ctx, 2);
        if (s3 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003202bc
        charge(ctx, 4);
        lw(s2, s3, 84);
        s1 = 0;
        for (;;) {
            // 0x00320304
            charge(ctx, 3);
            v0 = sltiu(s1, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003202cc
            charge(ctx, 5);
            v0 = sll(s1, 4);
            s0 = addu(s3, v0);
            lw(a0, s0, 12);
            if (a0 != 0) {
                // 0x003202e0
                charge(ctx, 5);
                v0 = 0x960000;
                lw(v0, v0, 380);  // 0x96017C: the RW free slot
                jalr(ctx, 0x3202E8u, v0.u());
                sw(zero, s0, 12);
            }
            // 0x003202f4
            charge(ctx, 4);
            sw(zero, s0, 0);
            sw(zero, s0, 4);
            sw(zero, s0, 8);
            s1 = addiu(s1, 1);
        }
        // 0x00320310
        charge(ctx, 9);
        lw(a0, s3, 80);
        jal(ctx, 0x320314u, gen::fn_sub_321010_00321010);
        a0 = s3;
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C: the RW free slot
        jalr(ctx, 0x320328u, v0.u());
        s3 = s2;
    }
    // 0x0032033c
    charge(ctx, 14);
    a0 = s4;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C: the RW free slot
    jalr(ctx, 0x320348u, v0.u());
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00320880 sub_320880 -- 800 bytes; frame 0x120: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_320880 [read an image-sequence chunk]: $a0 the stream, $a1 the list head, $a2 the chunk id
// 0xF0F00080..0xF0F00083, $a3 the clump. Reads {width, height, depth, name length} (20 bytes, sub_4C5250) and the
// name (on the frame, or a heap block when it has 0x80 characters or more), builds the record of the clump's
// materials tagged with the name (sub_320F70 counts, sub_320FB0, sub_320DA0 collects), then finds the list node
// holding that record or makes one (88 bytes: four 16-byte slots, the first material's colour at +64 and surface
// properties at +68..+76, the record at +80 (sub_321050), linked first); the local reference is released
// (sub_321010). The chunk's slot (+0 / +16 / +32 / +48): free -> {width, height, depth, width * depth bytes read
// into a new block}; taken -> those bytes skipped (sub_4C5620). Returns 1. (An unknown chunk id picks no slot: $s1
// keeps the caller's value.)
void sub_320880(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x00320880
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x120);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    s4 = a1;
    s3 = a2;
    s2 = a3;
    a1 = addiu(sp, 0x100);
    a2 = 20;
    jal(ctx, 0x3208BCu, gen::fn_sub_4C5250_004c5250);
    lw(v0, sp, 0x10C);
    at = sltiu(v0, 128);
    if (at == 0) {
        // 0x003208e4
        charge(ctx, 8);
        a0 = addiu(v0, 1);
        a1 = 0x40000;
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178: the RW malloc slot
        jalr(ctx, 0x3208F4u, v0.u());
        s0 = v0;
        s6 = 1;
    } else {
        // 0x003208d4
        charge(ctx, 4);
        s0 = addiu(sp, 0x80);
        s6 = 0;
    }
    // 0x00320904
    charge(ctx, 23);
    lw(a2, sp, 0x10C);
    a0 = s5;
    a1 = s0;
    jal(ctx, 0x320910u, gen::fn_sub_4C5250_004c5250);
    lw(v0, sp, 0x10C);
    v0 = addu(s0, v0);
    sb(zero, v0, 0);
    a0 = s2;
    a1 = s0;
    jal(ctx, 0x32092Cu, gen::fn_sub_320F70_00320f70);
    a0 = v0 & 0xFFFF;
    jal(ctx, 0x320938u, gen::fn_sub_320FB0_00320fb0);
    sw(v0, sp, 0x118);
    sw(s0, sp, 0x11C);
    a0 = s2;
    a1 = addiu(sp, 0x118);
    jal(ctx, 0x320950u, gen::fn_sub_320DA0_00320da0);
    if (s6 != 0) {
        // 0x00320960
        charge(ctx, 5);
        a0 = s0;
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C: the RW free slot
        jalr(ctx, 0x32096Cu, v0.u());
    }
    // 0x00320974
    charge(ctx, 4);
    lw(s0, sp, 0x118);
    lw(s2, s4, 0);
    for (;;) {
        // 0x0032099c
        charge(ctx, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00320984
        charge(ctx, 3);
        lw(v0, s2, 80);
        if (v0 == s0) {
            goto L_00320990_7;
        }
        // 0x00320998
        charge(ctx, 1);
        lw(s2, s2, 84);
    }
    // 0x003209a4
    charge(ctx, 1);
    s2 = 0;
L_003209a8:
    charge(ctx, 2);
    if (s2 == 0) {
        // 0x003209b0
        charge(ctx, 15);
        a0 = 88;
        a1 = 0x40000;
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178: the RW malloc slot
        jalr(ctx, 0x3209C0u, v0.u());
        s2 = v0;
        a0 = s2;
        a1 = 0;
        a2 = 88;
        jal(ctx, 0x3209D8u, gen::fn_memset_00521408);
        v1 = 0;
        for (;;) {
            // 0x00320a08
            charge(ctx, 3);
            v0 = sltiu(v1, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003209ec
            charge(ctx, 7);
            v0 = sll(v1, 4);
            v0 = addu(s2, v0);
            sw(zero, v0, 0);
            sw(zero, v0, 4);
            sw(zero, v0, 8);
            sw(zero, v0, 12);
            v1 = addiu(v1, 1);
        }
        // 0x00320a14
        charge(ctx, 24);
        sw(zero, s2, 84);
        a0 = s0;
        jal(ctx, 0x320A1Cu, gen::fn_sub_321050_00321050);
        sw(v0, s2, 80);
        lw(v0, v0, 0);
        lw(a2, v0, 0);
        lbu(a1, a2, 4);
        lbu(a0, a2, 5);
        lbu(v1, a2, 6);
        lbu(v0, a2, 7);
        sb(a1, s2, 64);
        sb(a0, s2, 65);
        sb(v1, s2, 66);
        sb(v0, s2, 67);
        lwc1(f2, a2, 12);
        lwc1(f1, a2, 16);
        lwc1(f0, a2, 20);
        swc1(f2, s2, 68);
        swc1(f1, s2, 72);
        swc1(f0, s2, 76);
        lw(v0, s4, 0);
        if (v0 != 0) {
            // 0x00320a84
            charge(ctx, 2);
            sw(v0, s2, 84);
            sw(s2, s4, 0);
        } else {
            // 0x00320a74
            charge(ctx, 4);
            sw(zero, s2, 84);
            sw(s2, s4, 0);
        }
    }
    // 0x00320a8c
    charge(ctx, 7);
    lw(a0, sp, 0x118);
    jal(ctx, 0x320A90u, gen::fn_sub_321010_00321010);
    v1 = lui(0xF0F0);
    v0 = v1 | 0x83;
    if (s3 == v0) {
        // 0x00320af8
        charge(ctx, 1);
        s1 = addiu(s2, 48);
    } else {
        // 0x00320aa8
        charge(ctx, 3);
        v0 = v1 | 0x82;
        if (s3 == v0) {
            // 0x00320aec
            charge(ctx, 3);
            s1 = addiu(s2, 32);
        } else {
            // 0x00320ab4
            charge(ctx, 3);
            v0 = v1 | 0x81;
            if (s3 == v0) {
                // 0x00320ae0
                charge(ctx, 3);
                s1 = addiu(s2, 16);
            } else {
                // 0x00320ac0
                charge(ctx, 3);
                v0 = v1 | 0x80;
                if (s3 == v0) {
                    // 0x00320ad4
                    charge(ctx, 3);
                    s1 = s2;
                } else {
                    // 0x00320acc
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x00320afc
    charge(ctx, 6);
    lw(v1, sp, 0x100);
    lw(v0, sp, 0x108);
    mult(s0, v1, v0);
    lw(v0, s1, 12);
    if (v0 != 0) {
        // 0x00320b60
        charge(ctx, 4);
        a0 = s5;
        a1 = s0;
        jal(ctx, 0x320B68u, gen::fn_sub_4C5620_004c5620);
    } else {
        // 0x00320b14
        charge(ctx, 19);
        sw(v1, s1, 0);
        lwc1(f0, sp, 0x104);
        swc1(f0, s1, 4);
        lw(v0, sp, 0x108);
        sw(v0, s1, 8);
        a0 = s0;
        a1 = 0x40000;
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178: the RW malloc slot
        jalr(ctx, 0x320B38u, v0.u());
        sw(v0, s1, 12);
        a0 = s5;
        a1 = v0;
        a2 = s0;
        jal(ctx, 0x320B50u, gen::fn_sub_4C5250_004c5250);
    }
    // 0x00320b70 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    v0 = 1;
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x120);
    return;
L_00320990_7:
    charge(ctx, 2);
    goto L_003209a8;
}

// 0x00320FB0 sub_320FB0 -- 92 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_320FB0 [new tagged-material record]: $a0 n (u16): {+0 -> the n entries at +12, +4 u16 0 (entries used), +6
// u16 n, +8 u16 references = 1}.
void sub_320FB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00320fb0
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    v0 = s0 & 0xFFFF;
    v0 = sll(v0, 2);
    a0 = addiu(v0, 12);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178: the RW malloc slot
    jalr(ctx, 0x320FD8u, v0.u());
    v1 = addiu(v0, 12);
    sw(v1, v0, 0);
    sh(zero, v0, 4);
    v1 = 1;
    sh(v1, v0, 8);
    sh(s0, v0, 6);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00321010 sub_321010 -- 64 bytes; frame 0x10: ra sp+0x0
// sub_321010 [release a record]: references (+8, u16) - 1; at 0 the record is freed (RwFree).
void sub_321010(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00321010
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lhu(v1, a0, 8);
    v1 = addiu(v1, -1);
    sh(v1, a0, 8);
    lhu(v1, a0, 8);
    if (v1 == 0) {
        // 0x00321030
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C: the RW free slot
        jalr(ctx, 0x321038u, v0.u());
    }
    // 0x00321040 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00322010 effMng_CreateEffectProgramTasks -- 1312 bytes; frame 0x1A0: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// effMng_CreateEffectProgramTasks [start the effect manager] (kwlnInitMain): the seven layer tables
// 0x957320..0x957920 cleared (252 bytes each), effect/effpack.bin requested and read-synced (H_Cdvd), the 22
// effpack textures effect/be_0001..0022.tmx loaded by name (sub_4D1260; filter 2, addressing 0x11) into 0x957A20,
// the file released; sub_3580F0(0, 0x12345678); the camera block 0x9572B0.. and the view matrix 0x957270 from the
// two constant quaternions 0x69BCB0 / 0x69BCC0 (the 2/|q|^2 rotation through mula / madda), the view words
// 0x9572E0..0x957318, 0x9572EC |= 0x20003; sub_34BD10, sub_347D00, sub_351C20; then the tasks: effect_program
// (effMng_UpdateEffectProgramTask) and under it effect_back, effect_attach, effect_3d (effMng_UpdateEffect3dTask),
// effect_front, effect_custom, effect_2d (effMng_UpdateEffect2dTask), effect_bustup, effect_fade.
void effMng_CreateEffectProgramTasks(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12};
    // 0x00322010
    enter(ctx, 65);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1A0);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    v0 = 0x6A0000;
    lq(v0, v0, -17232);  // 0x69BCB0
    sq(v0, sp, 0x150);
    v0 = 0x6A0000;
    lq(v0, v0, -17216);  // 0x69BCC0
    sq(v0, sp, 0x140);
    a0 = 0x950000;
    a0 = addiu(a0, 31008);  // &0x957920
    a1 = 0;
    a2 = 252;
    jal(ctx, 0x32204Cu, gen::fn_memset_00521408);
    a0 = 0x950000;
    a0 = addiu(a0, 30752);  // &0x957820
    a1 = 0;
    a2 = 252;
    jal(ctx, 0x322064u, gen::fn_memset_00521408);
    a0 = 0x950000;
    a0 = addiu(a0, 30496);  // &0x957720
    a1 = 0;
    a2 = 252;
    jal(ctx, 0x32207Cu, gen::fn_memset_00521408);
    a0 = 0x950000;
    a0 = addiu(a0, 29472);  // &0x957320
    a1 = 0;
    a2 = 252;
    jal(ctx, 0x322094u, gen::fn_memset_00521408);
    a0 = 0x950000;
    a0 = addiu(a0, 30240);  // &0x957620
    a1 = 0;
    a2 = 252;
    jal(ctx, 0x3220ACu, gen::fn_memset_00521408);
    a0 = 0x950000;
    a0 = addiu(a0, 29984);  // &0x957520
    a1 = 0;
    a2 = 252;
    jal(ctx, 0x3220C4u, gen::fn_memset_00521408);
    a0 = 0x950000;
    a0 = addiu(a0, 29728);  // &0x957420
    a1 = 0;
    a2 = 252;
    jal(ctx, 0x3220DCu, gen::fn_memset_00521408);
    a0 = 0x6A0000;
    a0 = addiu(a0, -17584);  // "effect/effpack.bin"
    a1 = 1;
    jal(ctx, 0x3220F0u, gen::fn_H_Cdvd_Request_00100d80);
    s2 = v0;
    a0 = s2;
    jal(ctx, 0x322100u, gen::fn_H_Cdvd_ReadSync_001023a0);
    s1 = 0;
    for (;;) {
        // 0x00322184
        charge(ctx, 3);
        v0 = sltiu(s1, 22);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00322114
        charge(ctx, 28);
        a2 = addiu(s1, 1);
        a0 = addiu(sp, 0x40);
        a1 = 0x6A0000;
        a1 = addiu(a1, -17552);  // "effect/be_%04d.tmx"
        jal(ctx, 0x322124u, gen::fn_sprintf_00523ac8);
        v1 = sll(s1, 2);
        v0 = 0x950000;
        v0 = addiu(v0, 31264);  // &0x957A20
        s0 = addu(v0, v1);
        a0 = addiu(sp, 0x40);
        a1 = 0;
        jal(ctx, 0x322144u, gen::fn_sub_4D1260_004d1260);
        sw(v0, s0, 0);
        lw(a0, v0, 80);
        v1 = si(-256);
        v1 = a0 & v1;
        v1 = v1 | 0x2;
        sw(v1, v0, 80);
        lw(a0, s0, 0);
        lw(v1, a0, 80);
        v0 = lui(0xFFFF);
        v0 = v0 | 0xFF;
        v0 = v1 & v0;
        v0 = v0 | 0x1100;
        sw(v0, a0, 80);
        s1 = addiu(s1, 1);
    }
    // 0x00322190
    charge(ctx, 88);
    a0 = s2;
    jal(ctx, 0x322194u, gen::fn_H_Cdvd_Destroy_00100ec0);
    a0 = 0;
    v0 = 0x12340000;
    a1 = v0 | 0x5678;
    jal(ctx, 0x3221A8u, gen::fn_sub_3580F0_003580f0);
    v1 = 1;
    v0 = 0x950000;
    sw(v1, v0, 29392);  // 0x9572D0
    lwc1(f3, sp, 0x150);
    lwc1(f2, sp, 0x154);
    lwc1(f1, sp, 0x158);
    lwc1(f0, sp, 0x15C);
    v0 = 0x950000;
    swc1(f3, v0, 29360);  // 0x9572B0
    v0 = 0x950000;
    swc1(f2, v0, 29364);  // 0x9572B4
    v0 = 0x950000;
    swc1(f1, v0, 29368);  // 0x9572B8
    v0 = 0x950000;
    swc1(f0, v0, 29372);  // 0x9572BC
    v0 = 0x950000;
    swc1(f3, v0, 29376);  // 0x9572C0
    v0 = 0x950000;
    swc1(f2, v0, 29380);  // 0x9572C4
    v0 = 0x950000;
    swc1(f1, v0, 29384);  // 0x9572C8
    v0 = 0x950000;
    swc1(f0, v0, 29388);  // 0x9572CC
    lwc1(f4, sp, 0x144);
    lwc1(f12, sp, 0x148);
    lwc1(f3, sp, 0x14C);
    lwc1(f11, sp, 0x140);
    mula_s(f4, f4);
    madda_s(f11, f11);
    madda_s(f12, f12);
    madd_s(f1, f3, f3);
    v0 = 0x40000000;
    mtc1(v0, f0);
    div_s(f0, f0, f1);
    mul_s(f2, f11, f0);
    mul_s(f1, f4, f0);
    mul_s(f0, f12, f0);
    mul_s(f10, f2, f3);
    mul_s(f9, f1, f3);
    mul_s(f8, f0, f3);
    mul_s(f7, f11, f2);
    mul_s(f6, f4, f1);
    mul_s(f5, f12, f0);
    mul_s(f4, f4, f0);
    mul_s(f3, f12, f2);
    mul_s(f2, f11, f1);
    add_s(f0, f6, f5);
    v0 = 0x3F800000;
    mtc1(v0, f1);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x160);
    add_s(f0, f2, f8);
    swc1(f0, sp, 0x164);
    sub_s(f0, f3, f9);
    swc1(f0, sp, 0x168);
    sub_s(f0, f2, f8);
    swc1(f0, sp, 0x170);
    add_s(f0, f5, f7);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x174);
    add_s(f0, f4, f10);
    swc1(f0, sp, 0x178);
    add_s(f0, f3, f9);
    swc1(f0, sp, 0x180);
    sub_s(f0, f4, f10);
    swc1(f0, sp, 0x184);
    add_s(f0, f7, f6);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x188);
    sw(zero, sp, 0x190);
    sw(zero, sp, 0x194);
    sw(zero, sp, 0x198);
    v0 = 3;
    sw(v0, sp, 0x16C);
    a1 = addiu(sp, 0x160);
    a0 = 0x950000;
    a0 = addiu(a0, 29296);  // &0x957270
    v1 = 4;
    for (;;) {
        // 0x003222f0
        charge(ctx, 7);
        lq(v0, a1, 0);
        a1 = addiu(a1, 16);
        v1 = addiu(v1, -1);
        sq(v0, a0, 0);
        a0 = addiu(a0, 16);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0032230c
    charge(ctx, 137);
    sw(zero, gp, -18352);  // 0x7CE540
    v1 = 0x3F800000;
    v0 = 0x950000;
    sw(v1, v0, 29448);  // 0x957308
    v0 = 0x950000;
    sw(v1, v0, 29428);  // 0x9572F4
    v0 = 0x950000;
    sw(v1, v0, 29408);  // 0x9572E0
    v0 = 0x950000;
    sw(zero, v0, 29424);  // 0x9572F0
    v0 = 0x950000;
    sw(zero, v0, 29416);  // 0x9572E8
    v0 = 0x950000;
    sw(zero, v0, 29412);  // 0x9572E4
    v0 = 0x950000;
    sw(zero, v0, 29444);  // 0x957304
    v0 = 0x950000;
    sw(zero, v0, 29440);  // 0x957300
    v0 = 0x950000;
    sw(zero, v0, 29432);  // 0x9572F8
    v0 = 0x950000;
    sw(zero, v0, 29464);  // 0x957318
    v0 = 0x950000;
    sw(zero, v0, 29460);  // 0x957314
    v0 = 0x950000;
    sw(zero, v0, 29456);  // 0x957310
    v0 = 0x950000;
    lw(v1, v0, 29420);  // 0x9572EC
    v0 = 0x20000;
    v0 = v0 | 0x3;
    v1 = v1 | v0;
    v0 = 0x950000;
    sw(v1, v0, 29420);  // 0x9572EC
    jal(ctx, 0x322390u, gen::fn_sub_34BD10_0034bd10);
    jal(ctx, 0x322398u, gen::fn_sub_347D00_00347d00);
    jal(ctx, 0x3223A0u, gen::fn_sub_351C20_00351c20);
    a0 = 0;
    a1 = 0x6A0000;
    a1 = addiu(a1, -17384);  // "effect_program"
    a2 = 1034;
    a3 = 0x320000;
    a3 = addiu(a3, 6752);  // &effMng_UpdateEffectProgramTask
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x3223C8u, gen::fn_kwlnTaskCreate_00194b20);
    s0 = v0;
    a0 = s0;
    a1 = 0x6A0000;
    a1 = addiu(a1, -17368);  // "effect_back"
    a2 = 2083;
    a3 = 0x320000;
    a3 = addiu(a3, 6912);  // &sub_321B00
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x3223F4u, gen::fn_kwlnTaskCreate_00194b20);
    a0 = s0;
    a1 = 0x6A0000;
    a1 = addiu(a1, -17352);  // "effect_attach"
    a2 = 2095;
    a3 = 0x320000;
    a3 = addiu(a3, 7248);  // &sub_321C50
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x32241Cu, gen::fn_kwlnTaskCreate_00194b20);
    a0 = s0;
    a1 = 0x6A0000;
    a1 = addiu(a1, -17336);  // "effect_3d"
    a2 = 3133;
    a3 = 0x320000;
    a3 = addiu(a3, 7344);  // &effMng_UpdateEffect3dTask
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x322444u, gen::fn_kwlnTaskCreate_00194b20);
    a0 = s0;
    a1 = 0x6A0000;
    a1 = addiu(a1, -17320);  // "effect_front"
    a2 = 4182;
    a3 = 0x320000;
    a3 = addiu(a3, 7392);  // &sub_321CE0
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x32246Cu, gen::fn_kwlnTaskCreate_00194b20);
    a0 = s0;
    a1 = 0x6A0000;
    a1 = addiu(a1, -17304);  // "effect_custom"
    a2 = 4186;
    a3 = 0x320000;
    a3 = addiu(a3, 7488);  // &sub_321D40
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x322494u, gen::fn_kwlnTaskCreate_00194b20);
    a0 = s0;
    a1 = 0x6A0000;
    a1 = addiu(a1, -17288);  // "effect_2d"
    a2 = 5266;
    a3 = 0x320000;
    a3 = addiu(a3, 7712);  // &effMng_UpdateEffect2dTask
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x3224BCu, gen::fn_kwlnTaskCreate_00194b20);
    a0 = s0;
    a1 = 0x6A0000;
    a1 = addiu(a1, -17272);  // "effect_bustup"
    a2 = 6321;
    a3 = 0x320000;
    a3 = addiu(a3, 7760);  // &sub_321E50
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x3224E4u, gen::fn_kwlnTaskCreate_00194b20);
    a0 = s0;
    a1 = 0x6A0000;
    a1 = addiu(a1, -17256);  // "effect_fade"
    a2 = 7380;
    a3 = 0x320000;
    a3 = addiu(a3, 7856);  // &sub_321EB0
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x32250Cu, gen::fn_kwlnTaskCreate_00194b20);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x1A0);
}

// 0x00322530 sub_322530 -- 148 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_322530 [new sprite player]: $a0 the sprite file (0: none). The set (sub_322880), a player of 20 * mode + 24
// bytes {+0 the set, +16 the track states at +24, +20 u16 running = 1}, animation 0 started (sub_3226B0). Returns
// the player.
void sub_322530(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00322530
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0;
    if (a0 != 0) {
        // 0x0032254c
        charge(ctx, 3);
        jal(ctx, 0x32254Cu, gen::fn_sub_322880_00322880);
        s0 = v0;
    }
    // 0x00322558
    charge(ctx, 27);
    lw(v1, s0, 8);
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    a0 = addiu(v0, 24);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178: the RW malloc slot
    jalr(ctx, 0x322578u, v0.u());
    s1 = v0;
    sw(s0, v0, 0);
    v1 = addiu(s1, 24);
    sw(v1, v0, 16);
    a0 = s1;
    a1 = 0;
    jal(ctx, 0x322598u, gen::fn_sub_3226B0_003226b0);
    v0 = 1;
    sh(v0, s1, 20);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003225D0 sub_3225D0 -- 140 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_3225D0 [clone a sprite player]: as sub_322530 on the player's set, whose references (+16) go up by one.
void sub_3225D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003225d0
    enter(ctx, 35);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 0);
    lw(v0, s0, 16);
    v0 = addiu(v0, 1);
    sw(v0, s0, 16);
    lw(v1, s0, 8);
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    a0 = addiu(v0, 24);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178: the RW malloc slot
    jalr(ctx, 0x322610u, v0.u());
    s1 = v0;
    sw(s0, v0, 0);
    v1 = addiu(s1, 24);
    sw(v1, v0, 16);
    a0 = s1;
    a1 = 0;
    jal(ctx, 0x322630u, gen::fn_sub_3226B0_003226b0);
    v0 = 1;
    sh(v0, s1, 20);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00322660 sub_322660 -- 68 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_322660 [free a sprite player]: its set released (sub_322A20), the player freed.
void sub_322660(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00322660
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, 0);
    jal(ctx, 0x322674u, gen::fn_sub_322A20_00322a20);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C: the RW free slot
    jalr(ctx, 0x322688u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00322880 sub_322880 -- 404 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_322880 [build a sprite set]: $a0 the sprite file {+0 header size S, +4 animation count, the 20-byte
// animations, the 24-byte keys; at +S the image count and the image offsets}. One block of S + 28 + 4 * images
// bytes {+0 the header copy (at +28), +4 its animations (+36), +8 mode, +12 image count, +16 references = 1, +20
// the textures, +24 itself}; a texture per image (sub_3210C0). The texture pointers start at +36 + S, so the last 8
// bytes lie past the block (the allocator's rounding usually absorbs them). Mode: the count of the last animation
// with flag 0x10000000, else 2 for one with flags 0x40 / 0x80, else 1.
void sub_322880(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00322880
    enter(ctx, 40);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    lw(v1, a0, 0);
    v0 = addu(s4, v1);
    lw(s0, v0, 0);
    s2 = addiu(v0, 4);
    v1 = addiu(v1, 28);
    v0 = sll(s0, 2);
    a0 = addu(v1, v0);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178: the RW malloc slot
    jalr(ctx, 0x3228C8u, v0.u());
    s3 = v0;
    sw(s3, v0, 24);
    s1 = addiu(s3, 28);
    lw(a2, s4, 0);
    a0 = s1;
    a1 = s4;
    jal(ctx, 0x3228E8u, gen::fn_memcpy_00521250);
    sw(s1, s3, 0);
    v0 = addiu(s1, 8);
    sw(v0, s3, 4);
    sw(s0, s3, 12);
    lw(v0, s3, 0);
    v1 = addiu(v0, 8);
    lw(v0, v0, 0);
    v0 = addu(v1, v0);
    sw(v0, s3, 20);
    s1 = 0;
    for (;;) {
        // 0x00322948
        charge(ctx, 3);
        v0 = slt(s1, s0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00322920
        charge(ctx, 10);
        lw(v0, s2, 0);
        a0 = addu(s4, v0);
        jal(ctx, 0x322928u, gen::fn_sub_3210C0_003210c0);
        a0 = sll(s1, 2);
        lw(v1, s3, 20);
        v1 = addu(v1, a0);
        sw(v0, v1, 0);
        s2 = addiu(s2, 4);
        s1 = addiu(s1, 1);
    }
    // 0x00322954
    charge(ctx, 10);
    v0 = 1;
    sw(v0, s3, 16);
    sw(v0, s3, 8);
    lw(v0, s3, 0);
    lw(a2, v0, 4);
    a3 = 0;
    a1 = 0x10000000;
    v1 = 2;
    for (;;) {
        // 0x003229e0
        charge(ctx, 3);
        v0 = slt(a3, a2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0032297c
        charge(ctx, 9);
        v0 = sll(a3, 2);
        v0 = addu(v0, a3);
        a0 = sll(v0, 2);
        lw(v0, s3, 4);
        a0 = addu(v0, a0);
        lw(v0, a0, 16);
        v0 = v0 & a1;
        if (v0 == 0) {
            // 0x003229b0
            charge(ctx, 4);
            lw(a0, a0, 8);
            v0 = a0 & 0x40;
            if (v0 == 0) {
                // 0x003229cc
                charge(ctx, 3);
                v0 = a0 & 0x80;
                if (v0 != 0) {
                    // 0x003229d8
                    charge(ctx, 1);
                    sw(v1, s3, 8);
                }
            } else {
                // 0x003229c0
                charge(ctx, 3);
                sw(v1, s3, 8);
            }
        } else {
            // 0x003229a0
            charge(ctx, 4);
            lw(v0, a0, 12);
            sw(v0, s3, 8);
        }
        // 0x003229dc
        charge(ctx, 1);
        a3 = addiu(a3, 1);
    }
    // 0x003229ec
    charge(ctx, 10);
    v0 = s3;
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00322A20 sub_322A20 -- 140 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_322A20 [release a sprite set]: references (+16) - 1; at 0 its textures (+20, count +12) are destroyed
// (sub_4D0F00) and the block (+24) freed.
void sub_322A20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00322a20
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, a0, 16);
    v1 = addiu(v1, -1);
    sw(v1, a0, 16);
    if (v1 == 0) {
        // 0x00322a48
        charge(ctx, 3);
        s1 = 0;
        for (;;) {
            // 0x00322a70
            charge(ctx, 4);
            lw(v0, s0, 12);
            v0 = slt(s1, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00322a54
            charge(ctx, 7);
            v1 = sll(s1, 2);
            lw(v0, s0, 20);
            v0 = addu(v0, v1);
            lw(a0, v0, 0);
            jal(ctx, 0x322A64u, gen::fn_sub_4D0F00_004d0f00);
            s1 = addiu(s1, 1);
        }
        // 0x00322a80
        charge(ctx, 5);
        lw(a0, s0, 24);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C: the RW free slot
        jalr(ctx, 0x322A8Cu, v0.u());
    }
    // 0x00322a94 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00322DC0 sub_322DC0 -- 348 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_322DC0 [build an image sequence]: $a0 the file {+4 image count, then the 16-byte image records {+0 frames, +4
// size}, then the images}. One block of 20 * count + 40 bytes {+0 the 16-byte header, +16 the records copied, +20 a
// texture per image (sub_3210C0), +24 the frame total (frames + 1 summed), +28 references = 1, +32 -1, +36 itself}.
void sub_322DC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00322dc0
    enter(ctx, 37);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(s1, a0, 4);
    s0 = sll(s1, 4);
    v1 = addiu(s0, 40);
    v0 = sll(s1, 2);
    a0 = addu(v1, v0);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178: the RW malloc slot
    jalr(ctx, 0x322E00u, v0.u());
    s4 = v0;
    v1 = addiu(s4, 40);
    sw(v1, v0, 16);
    v1 = addu(v1, s0);
    sw(v1, v0, 20);
    sw(zero, v0, 28);
    v1 = si(-1);
    sw(v1, v0, 32);
    sw(s4, v0, 36);
    a0 = s4;
    a1 = s2;
    a2 = 16;
    jal(ctx, 0x322E38u, gen::fn_memcpy_00521250);
    s3 = addiu(s2, 16);
    s2 = addu(s3, s0);
    s0 = 0;
    for (;;) {
        // 0x00322e9c
        charge(ctx, 3);
        v0 = sltu(s0, s1);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00322e54
        charge(ctx, 18);
        v1 = sll(s0, 4);
        lw(v0, s4, 16);
        a0 = addu(v0, v1);
        a1 = s3;
        a2 = 16;
        jal(ctx, 0x322E68u, gen::fn_memcpy_00521250);
        a0 = s2;
        jal(ctx, 0x322E74u, gen::fn_sub_3210C0_003210c0);
        a0 = sll(s0, 2);
        lw(v1, s4, 20);
        v1 = addu(v1, a0);
        sw(v0, v1, 0);
        lw(v0, s3, 4);
        s2 = addu(s2, v0);
        s3 = addiu(s3, 16);
        s0 = addiu(s0, 1);
    }
    // 0x00322ea8
    charge(ctx, 5);
    v1 = 0;
    a2 = 0;
    lw(a1, s4, 4);
    for (;;) {
        // 0x00322ed8
        charge(ctx, 3);
        v0 = sltu(a2, a1);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00322ebc
        charge(ctx, 7);
        a0 = addiu(v1, 1);
        v1 = sll(a2, 4);
        lw(v0, s4, 16);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        v1 = addu(a0, v0);
        a2 = addiu(a2, 1);
    }
    // 0x00322ee4
    charge(ctx, 14);
    sw(v1, s4, 24);
    lw(v0, s4, 28);
    v0 = addiu(v0, 1);
    sw(v0, s4, 28);
    v0 = s4;
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00322F20 sub_322F20 -- 140 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_322F20 [release an image sequence]: references (+28) - 1; at 0 its textures (+20, count +4) are destroyed
// (sub_4D0F00) and the block (+36) freed.
void sub_322F20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00322f20
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, a0, 28);
    v1 = addiu(v1, -1);
    sw(v1, a0, 28);
    if (v1 == 0) {
        // 0x00322f48
        charge(ctx, 3);
        s1 = 0;
        for (;;) {
            // 0x00322f70
            charge(ctx, 4);
            lw(v0, s0, 4);
            v0 = sltu(s1, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00322f54
            charge(ctx, 7);
            v1 = sll(s1, 2);
            lw(v0, s0, 20);
            v0 = addu(v0, v1);
            lw(a0, v0, 0);
            jal(ctx, 0x322F64u, gen::fn_sub_4D0F00_004d0f00);
            s1 = addiu(s1, 1);
        }
        // 0x00322f80
        charge(ctx, 5);
        lw(a0, s0, 36);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C: the RW free slot
        jalr(ctx, 0x322F8Cu, v0.u());
    }
    // 0x00322f94 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003230F0 sub_3230F0 -- 332 bytes; frame 0xA0: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_3230F0 [effect mesh object]: $a0 vertices, $a1 triangles, $a2 the geometry flags. A 28-byte record {+0 u16 5,
// +4 flags, +8 / +10 u16 counts, +12 a frame (sub_4CAF10), +16 an atomic (sub_491880), +20 a material (sub_494BE0),
// +24 0}; the geometry (sub_493710) gets the bounding sphere {0, 0, 0, the radius at 0x7CAE54} in its morph target,
// goes on the atomic (sub_4919B0, the frame by sub_492D10) and is unlocked (sub_493B60).
void sub_3230F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x003230f0
    enter(ctx, 83);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s5 = a2;
    a0 = 28;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178: the RW malloc slot
    jalr(ctx, 0x323134u, v0.u());
    s2 = v0;
    jal(ctx, 0x323140u, gen::fn_sub_4CAF10_004caf10);
    s6 = v0;
    jal(ctx, 0x32314Cu, gen::fn_sub_491880_00491880);
    s0 = v0;
    jal(ctx, 0x323158u, gen::fn_sub_494BE0_00494be0);
    s7 = v0;
    a0 = s4;
    a1 = s3;
    a2 = s5;
    jal(ctx, 0x323170u, gen::fn_sub_493710_00493710);
    s1 = v0;
    a0 = s0;
    a1 = s6;
    jal(ctx, 0x323184u, gen::fn_sub_492D10_00492d10);
    sw(zero, sp, 0x90);
    sw(zero, sp, 0x94);
    sw(zero, sp, 0x98);
    lwc1(f0, gp, -32412);  // 0x7CAE54: the bounding radius
    swc1(f0, sp, 0x9C);
    lw(v0, s1, 92);
    lwc1(f3, sp, 0x90);
    lwc1(f2, sp, 0x94);
    lwc1(f1, sp, 0x98);
    lwc1(f0, sp, 0x9C);
    swc1(f3, v0, 4);
    swc1(f2, v0, 8);
    swc1(f1, v0, 12);
    swc1(f0, v0, 16);
    a0 = s0;
    a1 = s1;
    a2 = 0;
    jal(ctx, 0x3231D0u, gen::fn_sub_4919B0_004919b0);
    a0 = s1;
    jal(ctx, 0x3231DCu, gen::fn_sub_493B60_00493b60);
    v0 = 5;
    sh(v0, s2, 0);
    sw(s5, s2, 4);
    sh(s4, s2, 8);
    sh(s3, s2, 10);
    sw(s6, s2, 12);
    sw(s0, s2, 16);
    sw(s7, s2, 20);
    sw(zero, s2, 24);
    v0 = s2;
    ld(ra, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x003234F0 sub_3234F0 -- 332 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_3234F0 [effect model object]: $a0 count, $a1 flags. A 28-byte record {+0 u16 3, +4 flags, +8 u16 0, +10 u16
// count, +12 a frame, +16 the object of sub_474210(count, flags, 2), +20 / +24 0}; in the object's plugin data
// (offset 0x7CE770): +180 = 1, flag 0x80000 -> the 16 bytes at 0x69BE10 copied to +224 and +64 |= 0x80000; +64 |=
// 0x800000, +4 = 0.
void sub_3234F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003234f0
    enter(ctx, 44);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    a0 = 28;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178: the RW malloc slot
    jalr(ctx, 0x32351Cu, v0.u());
    s0 = v0;
    v1 = 3;
    sh(v1, v0, 0);
    sw(s1, v0, 4);
    sh(zero, v0, 8);
    sh(s2, v0, 10);
    sw(zero, v0, 20);
    sw(zero, v0, 24);
    a0 = s2 & 0xFFFF;
    a1 = s1;
    a2 = 2;
    jal(ctx, 0x323550u, gen::fn_sub_474210_00474210);
    sw(v0, s0, 16);
    jal(ctx, 0x32355Cu, gen::fn_sub_4CAF10_004caf10);
    sw(v0, s0, 12);
    lw(a0, s0, 16);
    a1 = v0;
    jal(ctx, 0x323570u, gen::fn_sub_492D10_00492d10);
    a0 = 1;
    lw(v1, s0, 16);
    lw(v0, gp, -17792);  // 0x7CE770: the object plugin offset
    v0 = addu(v1, v0);
    lw(v0, v0, 0);
    sw(a0, v0, 180);
    v0 = 0x80000;
    v0 = s1 & v0;
    if (v0 != 0) {
        // 0x003235a0
        charge(ctx, 18);
        lw(v1, s0, 16);
        lw(v0, gp, -17792);  // 0x7CE770: the object plugin offset
        v0 = addu(v1, v0);
        lw(v0, v0, 0);
        a0 = addiu(v0, 224);
        a1 = 0x6A0000;
        a1 = addiu(a1, -16880);  // &0x69BE10
        a2 = 16;
        jal(ctx, 0x3235C0u, gen::fn_memcpy_00521250);
        lw(v1, s0, 16);
        lw(v0, gp, -17792);  // 0x7CE770: the object plugin offset
        v0 = addu(v1, v0);
        lw(a0, v0, 0);
        lw(v1, a0, 64);
        v0 = 0x80000;
        v0 = v1 | v0;
        sw(v0, a0, 64);
    }
    // 0x003235e8 (the shared epilogue, written out on this path)
    charge(ctx, 21);
    lw(v1, s0, 16);
    lw(v0, gp, -17792);  // 0x7CE770: the object plugin offset
    v0 = addu(v1, v0);
    lw(a0, v0, 0);
    lw(v1, a0, 64);
    v0 = 0x800000;
    v0 = v1 | v0;
    sw(v0, a0, 64);
    lw(v1, s0, 16);
    lw(v0, gp, -17792);  // 0x7CE770: the object plugin offset
    v0 = addu(v1, v0);
    lw(v0, v0, 0);
    sw(zero, v0, 4);
    v0 = s0;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003237C0 sub_3237C0 -- 148 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_3237C0 [destroy an effect mesh object]: the atomic (+16: sub_474630 for flag 2, else sub_491A80), the frame
// (+12, sub_4CAF80), the material (+20, sub_494CC0), each when set; then the record freed.
void sub_3237C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003237c0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, 16);
    if (a0 != 0) {
        // 0x003237dc
        charge(ctx, 4);
        lhu(v0, s0, 0);
        v0 = v0 & 0x2;
        if (v0 == 0) {
            // 0x003237fc
            charge(ctx, 2);
            jal(ctx, 0x3237FCu, gen::fn_sub_491A80_00491a80);
        } else {
            // 0x003237ec
            charge(ctx, 4);
            jal(ctx, 0x3237ECu, gen::fn_sub_474630_00474630);
        }
    }
    // 0x00323804
    charge(ctx, 3);
    lw(a0, s0, 12);
    if (a0 != 0) {
        // 0x00323810
        charge(ctx, 2);
        jal(ctx, 0x323810u, gen::fn_sub_4CAF80_004caf80);
    }
    // 0x00323818
    charge(ctx, 3);
    lw(a0, s0, 20);
    if (a0 != 0) {
        // 0x00323824
        charge(ctx, 2);
        jal(ctx, 0x323824u, gen::fn_sub_494CC0_00494cc0);
    }
    // 0x0032382c
    charge(ctx, 10);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C: the RW free slot
    jalr(ctx, 0x323838u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00323C20 sub_323C20 -- 488 bytes; frame 0xF0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_323C20 [effect mesh object, a material per band]: $a0 bands, $a1 vertices, $a2 triangles, $a3 the geometry
// flags. 4 * bands + 44 bytes: as sub_3230F0 (+0 u16 5, +4 flags, +8 / +10 counts, +12 frame, +16 atomic, +20 / +24
// 0) plus {+28 u16 bands, +30 / +32 u16 the counts times the bands (mult / mult1, as compiled), +34..+37 0xFF, +40
// -> the band materials at +44 (sub_494BE0 each)}.
void sub_323C20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x00323c20
    enter(ctx, 47);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    s6 = a1;
    s7 = a2;
    fp = a3;
    s0 = s5 & 0xFFFF;
    v0 = sll(s0, 2);
    a0 = addiu(v0, 44);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178: the RW malloc slot
    jalr(ctx, 0x323C74u, v0.u());
    s4 = v0;
    jal(ctx, 0x323C80u, gen::fn_sub_4CAF10_004caf10);
    sw(v0, sp, 0xD0);
    jal(ctx, 0x323C8Cu, gen::fn_sub_491880_00491880);
    s2 = v0;
    v0 = s7 & 0xFFFF;
    mult(v0, v0, s0);
    sq(v0, sp, 0xC0);
    v0 = s6 & 0xFFFF;
    mult1(v0, v0, s0);
    sq(v0, sp, 0xB0);
    paddub(a0, v0, zero);
    lq(a1, sp, 0xC0);
    a2 = fp;
    jal(ctx, 0x323CBCu, gen::fn_sub_493710_00493710);
    s3 = v0;
    v0 = addiu(s4, 44);
    sq(v0, sp, 0xA0);
    s1 = 0;
    for (;;) {
        // 0x00323d00
        charge(ctx, 4);
        v0 = s1 & 0xFFFF;
        v0 = slt(v0, s0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00323cdc
        charge(ctx, 9);
        jal(ctx, 0x323CDCu, gen::fn_sub_494BE0_00494be0);
        v1 = s1 & 0xFFFF;
        a0 = sll(v1, 2);
        lq(v1, sp, 0xA0);
        v1 = addu(v1, a0);
        sw(v0, v1, 0);
        v0 = addiu(s1, 1);
        s1 = v0 & 0xFFFF;
    }
    // 0x00323d10
    charge(ctx, 62);
    a0 = s2;
    lw(a1, sp, 0xD0);
    jal(ctx, 0x323D18u, gen::fn_sub_492D10_00492d10);
    sw(zero, sp, 0xE0);
    sw(zero, sp, 0xE4);
    sw(zero, sp, 0xE8);
    lwc1(f0, gp, -32412);  // 0x7CAE54: the bounding radius
    swc1(f0, sp, 0xEC);
    lw(v0, s3, 92);
    lwc1(f3, sp, 0xE0);
    lwc1(f2, sp, 0xE4);
    lwc1(f1, sp, 0xE8);
    lwc1(f0, sp, 0xEC);
    swc1(f3, v0, 4);
    swc1(f2, v0, 8);
    swc1(f1, v0, 12);
    swc1(f0, v0, 16);
    a0 = s2;
    a1 = s3;
    a2 = 0;
    jal(ctx, 0x323D64u, gen::fn_sub_4919B0_004919b0);
    a0 = s3;
    jal(ctx, 0x323D70u, gen::fn_sub_493B60_00493b60);
    v0 = 5;
    sh(v0, s4, 0);
    sw(fp, s4, 4);
    sh(s6, s4, 8);
    sh(s7, s4, 10);
    lw(v0, sp, 0xD0);
    sw(v0, s4, 12);
    sw(s2, s4, 16);
    sw(zero, s4, 20);
    sw(zero, s4, 24);
    sh(s5, s4, 28);
    lq(v0, sp, 0xB0);
    sh(v0, s4, 30);
    lq(v0, sp, 0xC0);
    sh(v0, s4, 32);
    lq(v0, sp, 0xA0);
    sw(v0, s4, 40);
    v0 = 255;
    sb(v0, s4, 34);
    sb(v0, s4, 35);
    sb(v0, s4, 36);
    sb(v0, s4, 37);
    v0 = s4;
    ld(ra, sp, 0x90);
    lq(fp, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xF0);
}

// 0x001EEF20 effAfter_CreateAfterEffectRenderTask -- 160 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// effAfter_CreateAfterEffectRenderTask [start the after effects] (kwlnInitMain): effect/z0.tmx requested,
// read-synced, loaded by name (sub_4D1260) into 0x7CE2D4 and released; the live list cleared (0x7CE2C8 / 0x7CE2CC);
// the kwlnTask "after effect render" (update sub_1EF060, kwlnTaskInitEx) kept at 0x7CE2D0.
void effAfter_CreateAfterEffectRenderTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001eef20
    enter(ctx, 40);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0x680000;
    a0 = addiu(a0, 17688);  // "effect/z0.tmx"
    a1 = 0;
    jal(ctx, 0x1EEF38u, gen::fn_H_Cdvd_Request_00100d80);
    s0 = v0;
    a0 = s0;
    jal(ctx, 0x1EEF48u, gen::fn_H_Cdvd_ReadSync_001023a0);
    a0 = 0x680000;
    a0 = addiu(a0, 17688);  // "effect/z0.tmx"
    a1 = 0;
    jal(ctx, 0x1EEF5Cu, gen::fn_sub_4D1260_004d1260);
    sw(v0, gp, -18972);  // 0x7CE2D4: the after effects' texture
    a0 = s0;
    jal(ctx, 0x1EEF6Cu, gen::fn_H_Cdvd_Destroy_00100ec0);
    sw(zero, gp, -18980);  // 0x7CE2CC: the live list's head
    sw(zero, gp, -18984);  // 0x7CE2C8: the live list's tail
    a0 = 0x680000;
    a0 = addiu(a0, 17712);  // "after effect render"
    a1 = 4170;
    a2 = 1;
    a3 = 2;
    t0 = 0x1F0000;
    t0 = addiu(t0, -4000);  // &sub_1EF060
    t1 = 0;
    t2 = 0;
    jal(ctx, 0x1EEFA0u, gen::fn_kwlnTaskInitEx_00194e10);
    sw(v0, gp, -18976);  // 0x7CE2D0: the after-effect render task
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

}  // namespace p3fes::game
