// The EPL effect-object player API, 0x34C160-0x350034 (fx_epl.h has the four object kinds, their function rows in
// the table 0x69C368 and the record layouts; docs/ANALYSIS/27_unmapped_bands.md section 6).
//
// Cycle model (ADR-0013): every charge() below is one `ctx.cycles += N` block of the recompiled body in
// recomp/generated; backedge() sits wherever that body has a check point on a backward jump (the loops here all test
// first: the test block is charged, then the check point, then the body). A block that ends in a `jal` is charged in
// full before the call, and the recompiler keeps going through `jal`s inside one block: one charge can cover several
// calls (sub_34C390 charges 90 before its first call and makes seven more in the same block), so the charges sit
// before the first call of their block, never between calls.
//
// Registers: register-faithful (fx_epl.h). Each body runs on a Cpu view of the guest context: one variable per GPR
// (64-bit writes keep bits 64..127, as the EE does; lq results write all 128), the FPU, VU0 macro-mode, MMI and
// HI/LO operations through the runtime's own instruction semantics, prologue spills and epilogue reloads on the
// guest stack. A branch's delay slot is a nop everywhere in this band.
//
// Faithfulness audit (2026-10-21, tools/ours/audit): 36 of the 60 functions here are p3fes_handgen's register-
// faithful bodies (their hand versions differed from the original: faults only 25, callee frames 9, frame/spills 2);
// the others are the hand-written versions this header describes (the Cpu methods; the earlier hand versions of the
// 36 also stay there as Cpu members that other members call). The 36 were made readable on 2026-10-22 (slice
// read_misc): the role notes of the earlier hand versions, the object / particle / system record offsets of fx_epl.h
// by name (k1 .. k4, rec3 / rec4, psys / sysrec, model, geom; the anonymous namespace before them), the float
// literals as mview::flt, the $gp float constants and callback addresses by name, block roles, and no goto left.
// Every guest statement, frame, link, cycle charge and check point is the generated body's, in its order on every
// path.
#include "p3fes/game/fx_epl.h"

#include "p3fes_recomp_rt.h"
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/misc_view.h"

namespace p3fes::recomp_gen {
// this slice (the callers below reach them through their entry points, as the recompiled callers do)
void fn_sub_34C9B0_0034c9b0(p3fes::EEContext&);  // kind 2 copy-from (RW heap; kept recompiled)
void fn_sub_34C670_0034c670(p3fes::EEContext&);  // kind 2 create (RW heap; kept recompiled)
void fn_sub_34CC00_0034cc00(p3fes::EEContext&);  // this slice
void fn_sub_34CF30_0034cf30(p3fes::EEContext&);  // this slice
void fn_sub_34D150_0034d150(p3fes::EEContext&);  // this slice
void fn_sub_34DB30_0034db30(p3fes::EEContext&);  // this slice
void fn_sub_34EAE0_0034eae0(p3fes::EEContext&);  // kind 4: draw one particle (rendering queue)
void fn_sub_34F6B0_0034f6b0(p3fes::EEContext&);  // this slice
void fn_sub_34F910_0034f910(p3fes::EEContext&);  // this slice
// the effect manager (0x320060-0x32415C) and the effect-node layer
void fn_sub_3210A0_003210a0(p3fes::EEContext&);  // the manager's resource slot (a0 = index): a pointer to a raster word
void fn_sub_3210C0_003210c0(p3fes::EEContext&);  // the manager's texture lookup by name
void fn_sub_321120_00321120(p3fes::EEContext&);  // select the draw layer
void fn_sub_321220_00321220(p3fes::EEContext&);  // queue a kind-3 object on a layer
void fn_sub_3212A0_003212a0(p3fes::EEContext&);  // queue a kind-4 object on a layer
void fn_sub_3212E0_003212e0(p3fes::EEContext&);  // queue a kind-1 object on a layer
void fn_sub_324BD0_00324bd0(p3fes::EEContext&);  // node: create
void fn_sub_3252A0_003252a0(p3fes::EEContext&);  // node: draw
void fn_sub_325500_00325500(p3fes::EEContext&);  // node: draw (layer variant)
void fn_sub_3257A0_003257a0(p3fes::EEContext&);  // node: (layer variant 2)
void fn_sub_3257E0_003257e0(p3fes::EEContext&);  // node: destroy
void fn_sub_325920_00325920(p3fes::EEContext&);  // node: (0x325920)
void fn_sub_325B80_00325b80(p3fes::EEContext&);  // node: release the children (kind table +28)
void fn_sub_325C10_00325c10(p3fes::EEContext&);  // node: position (vec4)
void fn_sub_325D60_00325d60(p3fes::EEContext&);  // node: rotation (vec4)
void fn_sub_325E40_00325e40(p3fes::EEContext&);  // node: scale ($f12)
void fn_sub_326030_00326030(p3fes::EEContext&);  // node: colour (RGBA word)
void fn_sub_326160_00326160(p3fes::EEContext&);  // node: position out (+64)
void fn_sub_326170_00326170(p3fes::EEContext&);  // node: rotation out (+80)
void fn_sub_3296A0_003296a0(p3fes::EEContext&);  // rotation matrix of Euler angles
void fn_sub_329ED0_00329ed0(p3fes::EEContext&);  // rotation (vec4 in $vf10) of a matrix
void fn_sub_32A120_0032a120(p3fes::EEContext&);  // colour track sample (age, lifetime) -> RGBA word
void fn_sub_32A540_0032a540(p3fes::EEContext&);  // scalar track sample -> $f0
void fn_sub_332200_00332200(p3fes::EEContext&);  // particle system: reset
void fn_sub_332210_00332210(p3fes::EEContext&);  // particle system: step
void fn_sub_3322B0_003322b0(p3fes::EEContext&);  // particle system: position out
void fn_sub_3322D0_003322d0(p3fes::EEContext&);  // particle system: position
void fn_sub_3322F0_003322f0(p3fes::EEContext&);  // particle system: rotation out
void fn_sub_332310_00332310(p3fes::EEContext&);  // particle system: rotation
void fn_sub_332330_00332330(p3fes::EEContext&);  // particle system: scale
void fn_sub_357E30_00357e30(p3fes::EEContext&);  // VU0: rotation matrix of $vf10 into $vf28..$vf31
void fn_sub_357EA0_00357ea0(p3fes::EEContext&);  // VU0: rotation of Euler angles $f12..$f14 into $vf10
void fn_sub_357FD0_00357fd0(p3fes::EEContext&);  // effMiscRand: an integer
void fn_sub_358030_00358030(p3fes::EEContext&);  // a float in [0, 1)
void fn_sub_358A30_00358a30(p3fes::EEContext&);  // debug: a coloured gizmo
void fn_sub_359380_00359380(p3fes::EEContext&);  // debug: frame axes
// the model layer
void fn_sub_316E00_00316e00(p3fes::EEContext&);  // model: create (ids a0 / a1)
void fn_sub_3174E0_003174e0(p3fes::EEContext&);  // model: destroy
void fn_sub_317730_00317730(p3fes::EEContext&);  // model: frame update
void fn_sub_317A20_00317a20(p3fes::EEContext&);  // model: draw
void fn_sub_3182D0_003182d0(p3fes::EEContext&);  // model: start an animation
void fn_sub_3185B0_003185b0(p3fes::EEContext&);  // model: has animation a1
void fn_sub_318770_00318770(p3fes::EEContext&);  // model: set the animation time
void fn_sub_3189F0_003189f0(p3fes::EEContext&);  // model: animation speed ($f12) of track a1
void fn_sub_318A30_00318a30(p3fes::EEContext&);  // model: translate (RwMatrixTranslate)
void fn_sub_318A70_00318a70(p3fes::EEContext&);  // model: transform (RwMatrixTransform)
void fn_sub_318A90_00318a90(p3fes::EEContext&);  // model: scale (RwMatrixScale, kept at +128)
void fn_sub_318AD0_00318ad0(p3fes::EEContext&);  // model: colour (+208)
void fn_sub_318B10_00318b10(p3fes::EEContext&);  // model: identity matrix
void fn_sub_318D10_00318d10(p3fes::EEContext&);  // model: frame a1's matrix, 0 when absent
// RenderWare
void fn_sub_1A14C0_001a14c0(p3fes::EEContext&);  // texture dictionary release (the loader's tail)
void fn_sub_4916D0_004916d0(p3fes::EEContext&);  // RpClumpForAllAtomics-like
void fn_sub_491CC0_00491cc0(p3fes::EEContext&);  // RpClumpClone-like
void fn_sub_491EA0_00491ea0(p3fes::EEContext&);  // RpClumpDestroy-like
void fn_sub_4920A0_004920a0(p3fes::EEContext&);  // RpClumpStreamRead-like (chunk 0x10)
void fn_sub_4C1970_004c1970(p3fes::EEContext&);  // RwStreamReadChunkHeaderInfo-like
void fn_sub_4C5620_004c5620(p3fes::EEContext&);  // RwStreamSkip-like
void fn_sub_4C5780_004c5780(p3fes::EEContext&);  // RwStreamClose-like
void fn_sub_4C58A0_004c58a0(p3fes::EEContext&);  // RwStreamOpen-like
void fn_sub_4C8680_004c8680(p3fes::EEContext&);  // RwTexDictionaryStreamRead-like (chunk 0x16)
void fn_sub_4D0D10_004d0d10(p3fes::EEContext&);  // texture dictionary: (after the walk)
void fn_sub_4D0DC0_004d0dc0(p3fes::EEContext&);  // RwTexDictionaryForAllTextures-like
void fn_memcpy_00521250(p3fes::EEContext&);      // libc memcpy
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace epl {
namespace detail {

namespace core = ee::core;
namespace gen = ::p3fes::recomp_gen;

// --- R5900 integer results (32-bit operations sign-extend into the 64-bit register) ----------------------
constexpr u64 si(s32 v) { return static_cast<u64>(static_cast<s64>(v)); }  // a negative immediate
constexpr s64 sgn(u64 v) { return static_cast<s64>(v); }                  // a register as a signed 64-bit value
constexpr u64 addu(u64 a, u64 b) { return core::add32(a, b); }
constexpr u64 addiu(u64 a, s32 i) { return core::add32i(a, i); }
constexpr u64 subu(u64 a, u64 b) { return core::sub32(a, b); }
constexpr u64 lui(u32 i) { return core::lui(i); }
constexpr u64 sll(u64 a, unsigned n) { return core::sll(a, n); }
constexpr u64 slt(u64 a, u64 b) { return core::slt(a, b); }
constexpr u64 sltu(u64 a, u64 b) { return core::sltu(a, b); }
constexpr u32 w(u64 v) { return static_cast<u32>(v); }

// One GPR of the guest context. Reads go through volatile lvalues, and so does virtual time below (the wave-10
// lesson of core3.cpp: MSVC /O2 was seen keeping ctx.cycles in a host register across a call to a small non-inlined
// helper that charges; a volatile access is a compiler barrier, so no guest state is cached across a helper).
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

// FPR numbers, VU0 registers and field masks.
enum : unsigned { F0 = 0, F1 = 1, F2 = 2, F3 = 3, F12 = 12, F13 = 13, F14 = 14, F20 = 20, F21 = 21 };
enum : unsigned { VF0 = 0, VF2 = 2, VF10 = 10, VF11 = 11, VF12 = 12, VF28 = 28, VF29 = 29, VF30 = 30, VF31 = 31 };
enum : unsigned { W = 1, X = 8, XYZ = 14, XYZW = 15 };  // dest field masks
enum : unsigned { BX = 0, BY = 1, BZ = 2, BW = 3 };      // broadcast fields
constexpr unsigned kQ = 22;                              // the VU0 control register Q (cfc2 $vi22)

// The guest machine as the bodies see it.
class Cpu {
public:
    explicit Cpu(EEContext& ctx) noexcept : c(ctx) {}

    EEContext& c;
    Gpr zero{c, 0}, at{c, 1}, v0{c, 2}, v1{c, 3}, a0{c, 4}, a1{c, 5}, a2{c, 6}, a3{c, 7};
    Gpr t0{c, 8}, t1{c, 9}, t2{c, 10}, t3{c, 11};
    Gpr s0{c, 16}, s1{c, 17}, s2{c, 18}, s3{c, 19}, s4{c, 20}, s5{c, 21};
    Gpr gp{c, 28}, sp{c, 29}, ra{c, 31};

    // virtual time (enter / backedge are not noexcept: a check point's fatal event must unwind through the bodies)
    void enter(u64 n) {
        rt::check_events(c);
        charge(n);
    }
    void charge(u64 n) noexcept {
        volatile u64& t = c.cycles;
        t = t + n;
    }
    void backedge() { rt::check_events(c); }

    // loads / stores (addresses are 32-bit; LQ / SQ force a quadword boundary)
    u64 lw(u64 a) const noexcept { return core::sext32(guest::load<u32>(c, w(a))); }
    u64 lhu(u64 a) const noexcept { return guest::load<u16>(c, w(a)); }
    u64 lbu(u64 a) const noexcept { return guest::load<u8>(c, w(a)); }
    u64 lb(u64 a) const noexcept { return core::sext8(guest::load<u8>(c, w(a))); }
    u64 ld(u64 a) const noexcept { return guest::load<u64>(c, w(a)); }
    void lq(Gpr& d, u64 a) noexcept { core::set_gpr128(c, d.r, guest::load<u128>(c, w(a) & ~15u)); }
    void sw(u64 a, u64 v) noexcept { guest::store<u32>(c, w(a), w(v)); }
    void sh(u64 a, u64 v) noexcept { guest::store<u16>(c, w(a), static_cast<u16>(v)); }
    void sb(u64 a, u64 v) noexcept { guest::store<u8>(c, w(a), static_cast<u8>(v)); }
    void sd(u64 a, u64 v) noexcept { guest::store<u64>(c, w(a), v); }
    void sq(u64 a, const Gpr& v) noexcept { guest::store<u128>(c, w(a) & ~15u, c.gpr[v.r]); }

    // FPU (the runtime's instruction semantics: EE singles, ACC, FCR31 flags); memory operands as (base, offset)
    void lwc1(unsigned f, const Gpr& b, s32 off) { rt::lwc1(c, f, b.r, off); }
    void swc1(unsigned f, const Gpr& b, s32 off) { rt::swc1(c, f, b.r, off); }
    void mtc1(const Gpr& g, unsigned f) noexcept { rt::mtc1(c, g.r, f); }
    void mfc1(Gpr& g, unsigned f) noexcept { rt::mfc1(c, g.r, f); }
    void mov_s(unsigned d, unsigned s) noexcept { rt::mov_s(c, d, s); }
    void cvt_s_w(unsigned d, unsigned s) noexcept { rt::cvt_s_w(c, d, s); }
    void add_s(unsigned d, unsigned s, unsigned t) noexcept { rt::add_s(c, d, s, t); }
    void sub_s(unsigned d, unsigned s, unsigned t) noexcept { rt::sub_s(c, d, s, t); }
    void mul_s(unsigned d, unsigned s, unsigned t) noexcept { rt::mul_s(c, d, s, t); }
    void div_s(unsigned d, unsigned s, unsigned t) noexcept { rt::div_s(c, d, s, t); }
    void adda_s(unsigned s, unsigned t) noexcept { rt::adda_s(c, s, t); }
    void madd_s(unsigned d, unsigned s, unsigned t) noexcept { rt::madd_s(c, d, s, t); }
    void c_eq_s(unsigned s, unsigned t) noexcept { rt::c_eq_s(c, s, t); }
    bool cop1_cond() const noexcept { return rt::cop1_cond(c); }

    // HI/LO and MMI
    void div(const Gpr& s, const Gpr& t) noexcept { rt::div(c, s.r, t.r); }
    void divu(const Gpr& s, const Gpr& t) noexcept { rt::divu(c, s.r, t.r); }
    void mflo(Gpr& d) noexcept { rt::mflo(c, d.r); }
    void mfhi(Gpr& d) noexcept { rt::mfhi(c, d.r); }
    void pextlb(Gpr& d, const Gpr& s, const Gpr& t) noexcept { rt::pextlb(c, d.r, s.r, t.r); }
    void pextlh(Gpr& d, const Gpr& s, const Gpr& t) noexcept { rt::pextlh(c, d.r, s.r, t.r); }
    void ppach(Gpr& d, const Gpr& s, const Gpr& t) noexcept { rt::ppach(c, d.r, s.r, t.r); }
    void ppacb(Gpr& d, const Gpr& s, const Gpr& t) noexcept { rt::ppacb(c, d.r, s.r, t.r); }

    // VU0 macro mode
    void lqc2(unsigned vf, const Gpr& b, s32 off) { rt::lqc2(c, vf, b.r, off); }
    void sqc2(unsigned vf, const Gpr& b, s32 off) { rt::sqc2(c, vf, b.r, off); }
    void qmtc2(const Gpr& g, unsigned vf) { rt::qmtc2(c, g.r, vf, false); }
    void qmfc2(Gpr& g, unsigned vf) { rt::qmfc2(c, g.r, vf, false); }
    void cfc2(Gpr& g, unsigned vi) { rt::cfc2(c, g.r, vi, false); }

    // calls: `jal fn` at pc ($ra = pc + 8; the delay slot is a nop), `jalr target` at pc (through the dispatch table)
    void jal(u32 pc, rt::Fn fn) {
        rt::jal(c, pc);
        fn(c);
    }
    void jalr(u32 pc, u32 target) {
        rt::jalr(c, GPR_RA, pc);
        rt::lookup_func(target)(c);
    }

    // --- shared sequences (named after what they compute; the instructions are the compiler's) ---
    // An RGBA word at sp + slot, unpacked into the four lanes of $vf<vf> as floats 0..255: `tmp` = sp + slot, then
    // the word, zero-extended byte -> halfword -> word (PEXTLB / PEXTLH against $zero), QMTC2, VITOF0.
    void rgba_to_vf(Gpr& tmp, s32 slot, unsigned vf) {
        tmp = addiu(sp, slot);
        tmp = lw(tmp);
        pextlb(tmp, zero, tmp);
        pextlh(tmp, zero, tmp);
        qmtc2(tmp, vf);
        rt::vitof0(c, XYZW, vf, vf);
    }
    // $vf<vf> *= the float in GPR `g` (QMTC2 into $vf2, VMULx).
    void vf_scale_gpr(const Gpr& g, unsigned vf) {
        qmtc2(g, VF2);
        rt::vmul_bc(c, XYZW, vf, vf, VF2, BX);
    }
    // $vf<vf> *= $f<f> through `tmp` (MFC1, then as above).
    void vf_scale_fpr(Gpr& tmp, unsigned f, unsigned vf) {
        mfc1(tmp, f);
        vf_scale_gpr(tmp, vf);
    }
    // The lanes of $vf<vf> back to an RGBA word in `g` (VFTOI0, QMFC2, PPACH / PPACB against $zero).
    void vf_to_rgba(Gpr& g, unsigned vf) {
        rt::vftoi0(c, XYZW, vf, vf);
        qmfc2(g, vf);
        ppach(g, zero, g);
        ppacb(g, zero, g);
    }
    // a0 = 0, then $f0 = sub_358030() (a random float in [0, 1)), the jal at pc.
    void rand01(u32 pc) {
        a0 = 0;
        jal(pc, gen::fn_sub_358030_00358030);
    }
    // $f<d> = (1 - $f<k>) + $f<k> * $f0: a random factor around 1 with spread k ($f1 / $f2 as the compiler's
    // temporaries, `tmp` holds 1.0).
    void spread(Gpr& tmp, unsigned d, unsigned k) {
        tmp = lui(0x3F80);
        mtc1(tmp, F1);
        sub_s(F2, F1, k);
        mtc1(zero, F1);
        adda_s(F1, F2);
        madd_s(d, k, F0);
    }
    // $f1 = 0.5 + 0.5 * $f0 (v0 holds 0.5).
    void half_plus_half() {
        v0 = lui(0x3F00);
        mtc1(v0, F2);
        mtc1(zero, F1);
        adda_s(F1, F2);
        madd_s(F1, F2, F0);
    }
    // $f1 = gp[-32544] + gp[-32628] * $f0 ($f2 / $f3 the constants).
    void gp_affine() {
        lwc1(F3, gp, -32628);
        lwc1(F2, gp, -32544);
        mtc1(zero, F1);
        adda_s(F1, F2);
        madd_s(F1, F3, F0);
    }
    void kind4_emit(Gpr& obj, Gpr& rec, u32 pc);
    void kind1_age_step(Gpr& obj, Gpr& life, Gpr& age);
    void model_place(Gpr& obj, s32 model, s32 matrix, s32 vec, u32 pc);

    // --- the bodies (fx_epl.h documents each; named as the functions they are) ---
    void sub_34C250();
    void sub_34C320();
    void sub_34C350();
    void sub_34C390();
    void sub_34C5A0();
    void sub_34C5D0();
    void sub_34C630();
    void sub_34C640();
    void sub_34C650();
    void sub_34C660();
    void sub_34C940();
    void sub_34CB60();
    void sub_34CC00();
    void sub_34CF30();
    void sub_34D050();
    void sub_34D090();
    void sub_34D0A0();
    void sub_34D0B0();
    void sub_34D0C0();
    void sub_34D0D0();
    void sub_34D130();
    void sub_34D150();
    void sub_34D3A0();
    void sub_34D810();
    void sub_34D990();
    void sub_34DB00();
    void sub_34DB30();
    void sub_34E390();
    void sub_34E3D0();
    void sub_34E420();
    void sub_34E450();
    void sub_34E480();
    void sub_34E490();
    void sub_34E7C0();
    void sub_34E800();
    void sub_34E910();
    void sub_34E940();
    void sub_34F6B0();
    void sub_34F910();
    void sub_34FB40();
    void sub_34FB70();
    void sub_34FBA0();
    void sub_34FBE0();
    void sub_34FC30();
    void sub_34FC60();
    void sub_34FC90();
    void sub_34FCA0();
    void sub_34FCD0();
    void sub_34FCF0();
    void sub_34FD10();
    void sub_34FD30();
    void sub_34FD50();
    void sub_34FD70();
    void sub_34FDB0();
    void sub_34FDF0();
    void sub_34FE30();
    void sub_34FE80();
    void sub_34FF70();
    void sub_34FF90();
    void sub_34FFC0();

    // the one-call shapes shared by many slots
    void leaf_frame_call(s32 cost, u32 pc, rt::Fn fn);                    // sp -= 16, ra spilled, one call
    void field_call(s32 cost, s32 field, u32 pc, rt::Fn fn);              // a0 = obj[field], one call
    void field_call_if(s32 field, u32 pc, rt::Fn fn);                     // the same when obj[field] != 0
    void layer_queue(s32 field, u32 pc, rt::Fn fn);                       // fn(obj, system[+32][+84])
    void step_then_queue(s32 field, u32 step_pc, rt::Fn step, u32 pc, rt::Fn fn);
    void keep_a0_call2(u32 pc1, rt::Fn f1, u32 pc2, rt::Fn f2);           // s0 = a0; f1(a1); f2(s0)
};

// =========================================================================================================
// Shared shapes
// =========================================================================================================

// `addiu sp, sp, -16; sd ra, 0(sp); <cost - 8 more instructions>; jal fn; ld ra; addiu sp, 16`: the whole body is
// one block of `cost`; used by the wrappers whose arguments pass through unchanged.
void Cpu::leaf_frame_call(s32 cost, u32 pc, rt::Fn fn) {
    enter(static_cast<u64>(cost));
    sp = addiu(sp, -16);
    sd(sp, ra);
    jal(pc, fn);
    ra = ld(sp);
    sp = addiu(sp, 16);
}

// a0 = obj[field] (the object's particle system), then one call: the slots 8 / 9 of kinds 3 and 4.
void Cpu::field_call(s32 cost, s32 field, u32 pc, rt::Fn fn) {
    enter(static_cast<u64>(cost));
    sp = addiu(sp, -16);
    sd(sp, ra);
    a0 = lw(a0 + field);
    jal(pc, fn);
    ra = ld(sp);
    sp = addiu(sp, 16);
}

// The same when obj[field] is not null (the reset slots: sub_332200(system)).
void Cpu::field_call_if(s32 field, u32 pc, rt::Fn fn) {
    enter(5);
    sp = addiu(sp, -16);
    sd(sp, ra);
    a0 = lw(a0 + field);
    if (a0 != 0) {
        charge(2);
        jal(pc, fn);
    }
    charge(4);
    ra = ld(sp);
    sp = addiu(sp, 16);
}

// The draw requests of kinds 3 and 4: when the system obj[field] exists, fn(obj, system->owner(+32)->layer(+84)).
void Cpu::layer_queue(s32 field, u32 pc, rt::Fn fn) {
    enter(5);
    sp = addiu(sp, -16);
    sd(sp, ra);
    v1 = lw(a0 + field);
    if (v1 != 0) {
        charge(4);
        v0 = lw(v1 + 32);
        a1 = lhu(v0 + 84);
        jal(pc, fn);
    }
    charge(4);
    ra = ld(sp);
    sp = addiu(sp, 16);
}

// The update slots of kinds 3 and 4: step(obj), then the draw request as above (obj kept in s0).
void Cpu::step_then_queue(s32 field, u32 step_pc, rt::Fn step, u32 pc, rt::Fn fn) {
    enter(9);
    sp = addiu(sp, -32);
    sd(sp + 16, ra);
    sq(sp, s0);
    s0 = a0;
    jal(step_pc, step);
    v1 = lw(s0 + field);
    if (v1 != 0) {
        charge(5);
        v0 = lw(v1 + 32);
        a1 = lhu(v0 + 84);
        a0 = s0;
        jal(pc, fn);
    }
    charge(5);
    ra = ld(sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 32);
}

// `s0 = a0; f1(a1); f2(s0)` in a 32-byte frame (one block of 15).
void Cpu::keep_a0_call2(u32 pc1, rt::Fn f1, u32 pc2, rt::Fn f2) {
    enter(15);
    sp = addiu(sp, -32);
    sd(sp + 16, ra);
    sq(sp, s0);
    s0 = a0;
    a0 = a1;
    jal(pc1, f1);
    a0 = s0;
    jal(pc2, f2);
    ra = ld(sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 32);
}

// =========================================================================================================
// Kind 1: the model object
// =========================================================================================================

// sub_34C250 [slot 6: copy from another object] (a0 dst, a1 src): destroys dst's model (+148) when it has one,
// creates a model with src's ids (src->model +212 / +214, flags 0), resets its matrix, starts animation 0 at speed
// 1.0 when the model has one, clears model flag 2 (+216) and stores it in dst.
void Cpu::sub_34C250() {
    enter(9);
    sp = addiu(sp, -48);
    sd(sp + 32, ra);
    sq(sp + 16, s1);
    sq(sp, s0);
    s0 = a0;  // dst
    s1 = a1;  // src
    a0 = lw(a0 + 148);
    if (a0 != 0) {
        charge(2);
        jal(0x34C274u, gen::fn_sub_3174E0_003174e0);
    }
    charge(16);
    v0 = lw(s1 + 148);
    a0 = lhu(v0 + 212);
    a1 = lhu(v0 + 214);
    a2 = 0;
    jal(0x34C28Cu, gen::fn_sub_316E00_00316e00);
    s1 = v0;  // the new model
    a0 = s1;
    jal(0x34C29Cu, gen::fn_sub_318B10_00318b10);
    a0 = s1;
    a1 = 0;
    jal(0x34C2ACu, gen::fn_sub_3185B0_003185b0);
    if (v0 != 0) {
        charge(13);
        a0 = s1;
        a1 = 0;
        a2 = 0;
        a3 = 0;
        t0 = 0;
        jal(0x34C2D0u, gen::fn_sub_3182D0_003182d0);
        v0 = lui(0x3F80);  // 1.0
        mtc1(v0, F12);
        a0 = s1;
        a1 = 0;
        jal(0x34C2E8u, gen::fn_sub_3189F0_003189f0);
    }
    charge(10);
    v1 = lhu(s1 + 216);
    v1 = v1 & 0xFFFDu;
    sh(s1 + 216, v1);
    sw(s0 + 148, s1);
    ra = ld(sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 48);
}

// sub_34C320 [slot 7: reset]: the model's track 0 back to time 0.0 (sub_318770(model, 0) with $f12 = 0).
void Cpu::sub_34C320() {
    enter(11);
    sp = addiu(sp, -16);
    sd(sp, ra);
    mtc1(zero, F12);
    a0 = lw(a0 + 148);
    a1 = 0;
    jal(0x34C334u, gen::fn_sub_318770_00318770);
    ra = ld(sp);
    sp = addiu(sp, 16);
}

// The age step of kinds 1 (sub_34C350 / sub_34C5D0): unless the object has a lifetime (+140) that its age (+152)
// already exceeds, the animation advance (+36) becomes 1.0 and the age grows by one. `life` / `age` are the
// registers the compiler used (a1 / v1, v1 / v0).
void Cpu::kind1_age_step(Gpr& obj, Gpr& life, Gpr& age) {
    life = lw(obj + 140);
    age = lw(obj + 152);
    at = sltu(life, age);
    bool expired = false;
    if (at != 0) {
        charge(2);
        expired = life != 0;
    }
    if (!expired) {
        charge(5);
        age = lui(0x3F80);
        sw(obj + 36, age);
        age = lw(obj + 152);
        age = addiu(age, 1);
        sw(obj + 152, age);
    }
}

// sub_34C350 [slot 2: step].
void Cpu::sub_34C350() {
    enter(5);
    kind1_age_step(a0, a1, v1);
    charge(2);
}

// sub_34C390 [draw] (called by the layer task sub_321360): while alive, the model's colour = base colour (+40) x the
// colour track sampled at (age, lifetime) (sub_32A120 on +44 / +80), both as floats scaled by gp[-32232], x 255 back
// to bytes; the scale track (+96) / 10 x scale (+32) on all three axes, the rotation matrix of the Euler angles +16,
// the position +0; model flags 0x18 set or cleared by the additive byte +144; the animation advanced by +36 (then
// zeroed) and the model drawn (sub_317A20).
void Cpu::sub_34C390() {
    enter(12);
    sp = addiu(sp, -176);
    sd(sp + 64, ra);
    sq(sp + 48, s2);
    sq(sp + 32, s1);
    sq(sp + 16, s0);
    swc1(F20, sp, 0);
    s2 = a0;
    s1 = lw(a0 + 152);  // age
    s0 = lw(a0 + 140);  // lifetime
    at = sltu(s0, s1);
    bool expired = false;
    if (at != 0) {
        charge(2);
        expired = s0 != 0;
    }
    if (!expired) {
        charge(90);
        a0 = addiu(s2, 44);
        a1 = addiu(s2, 80);
        a2 = s1;
        a3 = s0;
        jal(0x34C3D8u, gen::fn_sub_32A120_0032a120);
        v1 = v0;  // the track colour
        v0 = lw(s2 + 40);
        sw(sp + 168, v0);
        lwc1(F0, gp, -32232);  // the byte -> unit scale
        rgba_to_vf(v0, 168, VF10);
        vf_scale_fpr(v0, F0, VF10);
        rt::vmove(c, XYZW, VF11, VF10);
        sw(sp + 164, v1);
        rgba_to_vf(v0, 164, VF10);
        vf_scale_fpr(v0, F0, VF10);
        rt::vmul(c, XYZW, VF10, VF10, VF11);
        v0 = lui(0x437F);  // 255.0
        vf_scale_gpr(v0, VF10);
        vf_to_rgba(v0, VF10);
        sw(sp + 160, v0);
        v0 = lw(sp + 160);
        sw(sp + 172, v0);
        a0 = lw(s2 + 148);
        a1 = addiu(sp, 172);
        jal(0x34C47Cu, gen::fn_sub_318AD0_00318ad0);
        a0 = addiu(s2, 96);
        a1 = s1;
        a2 = s0;
        jal(0x34C490u, gen::fn_sub_32A540_0032a540);
        v0 = lui(0x4120);  // 10.0
        mtc1(v0, F1);
        div_s(F20, F0, F1);
        a0 = addiu(sp, 80);
        a1 = addiu(s2, 16);
        jal(0x34C4B4u, gen::fn_sub_3296A0_003296a0);
        a0 = lw(s2 + 148);
        a1 = addiu(sp, 80);
        a2 = 0;
        jal(0x34C4C8u, gen::fn_sub_318A70_00318a70);
        lwc1(F0, s2, 32);
        mul_s(F0, F0, F20);
        swc1(F0, sp, 152);
        swc1(F0, sp, 148);
        swc1(F0, sp, 144);
        a0 = lw(s2 + 148);
        a1 = addiu(sp, 144);
        a2 = 2;
        jal(0x34C4F0u, gen::fn_sub_318A90_00318a90);
        lwc1(F0, s2, 0);
        swc1(F0, sp, 144);
        lwc1(F0, s2, 4);
        swc1(F0, sp, 148);
        lwc1(F0, s2, 8);
        swc1(F0, sp, 152);
        a0 = lw(s2 + 148);
        a1 = addiu(sp, 144);
        a2 = 2;
        jal(0x34C51Cu, gen::fn_sub_318A30_00318a30);
        v0 = lbu(s2 + 144);
        if (v0 != 0) {
            charge(6);
            v1 = lw(s2 + 148);
            v0 = lhu(v1 + 216);
            v0 = v0 | 0x18u;
            sh(v1 + 216, v0);
        } else {
            charge(4);
            v1 = lw(s2 + 148);
            v0 = lhu(v1 + 216);
            v0 = v0 & 0xFFE7u;
            sh(v1 + 216, v0);
        }
        charge(9);
        a0 = lw(s2 + 148);
        a1 = 0;
        lwc1(F12, s2, 36);
        jal(0x34C564u, gen::fn_sub_3189F0_003189f0);
        a0 = lw(s2 + 148);
        jal(0x34C570u, gen::fn_sub_317A20_00317a20);
        sw(s2 + 36, zero);
    }
    charge(8);
    ra = ld(sp + 64);
    lq(s2, sp + 48);
    lq(s1, sp + 32);
    lq(s0, sp + 16);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 176);
}

// sub_34C5A0 [slot 3]: queue the object on its draw layer: sub_3212E0(obj, obj->layer +84).
void Cpu::sub_34C5A0() {
    enter(9);
    sp = addiu(sp, -16);
    sd(sp, ra);
    a1 = lhu(a0 + 84);
    jal(0x34C5ACu, gen::fn_sub_3212E0_003212e0);
    ra = ld(sp);
    sp = addiu(sp, 16);
}

// sub_34C5D0 [slot 1: update]: the age step, then the draw request.
void Cpu::sub_34C5D0() {
    enter(7);
    sp = addiu(sp, -16);
    sd(sp, ra);
    kind1_age_step(a0, v1, v0);
    charge(7);
    a1 = lhu(a0 + 84);
    jal(0x34C60Cu, gen::fn_sub_3212E0_003212e0);
    ra = ld(sp);
    sp = addiu(sp, 16);
}

// sub_34C630 / sub_34C640 [slots 8 / 9] (and kind 2's sub_34D090 / sub_34D0A0): the 16 bytes at a1 into +0 / +16.
void Cpu::sub_34C630() {
    enter(4);
    lq(v0, a1);
    sq(a0, v0);
}
void Cpu::sub_34C640() {
    enter(4);
    lq(v0, a1);
    sq(a0 + 16, v0);
}
// sub_34C650 [slot 12]: colour word +40.
void Cpu::sub_34C650() {
    enter(3);
    sw(a0 + 40, a1);
}
// sub_34C660 [slot 10] (and kind 2's sub_34D0C0): scale +32 = $f12.
void Cpu::sub_34C660() {
    enter(3);
    swc1(F12, a0, 32);
}

// =========================================================================================================
// Kind 2: the node-carrying model
// =========================================================================================================

// sub_34C940 [slot 5: clone]: a new kind-2 object (sub_34C670(0), RW heap), the 104 bytes from +48 copied, then the
// copy-from slot sub_34C9B0(new, obj); returns the new object.
void Cpu::sub_34C940() {
    enter(25);
    sp = addiu(sp, -48);
    sd(sp + 32, ra);
    sq(sp + 16, s1);
    sq(sp, s0);
    s1 = a0;
    a0 = 0;
    jal(0x34C958u, gen::fn_sub_34C670_0034c670);
    s0 = v0;
    a0 = addiu(s0, 48);
    a1 = addiu(s1, 48);
    a2 = 104;
    jal(0x34C970u, gen::fn_memcpy_00521250);
    a0 = s0;
    a1 = s1;
    jal(0x34C980u, gen::fn_sub_34C9B0_0034c9b0);
    v0 = s0;
    ra = ld(sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 48);
}

// sub_34CB60 [slot 7: reset]: when the nodes are live (+156), release every frame's node (sub_325B80 over the +40
// pointers at +152); then the model's track 0 back to time 0 and the age (+44) to 0.
void Cpu::sub_34CB60() {
    enter(10);
    sp = addiu(sp, -80);
    sd(sp + 64, ra);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    s3 = a0;
    v0 = lw(a0 + 156);
    if (v0 != 0) {
        charge(5);
        s0 = lw(s3 + 40);   // frames
        s2 = lw(s3 + 152);  // node pointers
        s1 = 0;
        for (;;) {
            charge(3);
            v0 = sltu(s1, s0);
            if (v0 == 0) break;
            backedge();
            charge(5);
            a0 = lw(s2);
            jal(0x34CBA0u, gen::fn_sub_325B80_00325b80);
            s2 = addiu(s2, 4);
            s1 = addiu(s1, 1);
        }
    }
    charge(14);
    mtc1(zero, F12);
    a0 = lw(s3 + 160);
    a1 = 0;
    jal(0x34CBC8u, gen::fn_sub_318770_00318770);
    sw(s3 + 44, zero);
    ra = ld(sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 80);
}

// The model transform of kinds 1 / 2: the rotation matrix of the Euler angles obj+16 at sp + matrix
// (sub_3296A0), RwMatrixTransform-like (sub_318A70, combine 0), RwMatrixScale-like by obj+32 on three axes
// (sub_318A90, combine 2), RwMatrixTranslate-like by obj+0 (sub_318A30, combine 2); the model is obj[model], the
// vec3 scratch at sp + vec. Only kind 2 (sub_34CC00) uses this straight; the jal pcs follow from `pc` (the first).
void Cpu::model_place(Gpr& obj, s32 model, s32 matrix, s32 vec, u32 pc) {
    a0 = addiu(sp, matrix);
    a1 = addiu(obj, 16);
    jal(pc, gen::fn_sub_3296A0_003296a0);
    a0 = lw(obj + model);
    a1 = addiu(sp, matrix);
    a2 = 0;
    jal(pc + 0x14, gen::fn_sub_318A70_00318a70);
    lwc1(F0, obj, 32);
    swc1(F0, sp, vec + 8);
    swc1(F0, sp, vec + 4);
    swc1(F0, sp, vec);
    a0 = lw(obj + model);
    a1 = addiu(sp, vec);
    a2 = 2;
    jal(pc + 0x38, gen::fn_sub_318A90_00318a90);
    lwc1(F0, obj, 0);
    swc1(F0, sp, vec);
    lwc1(F0, obj, 4);
    swc1(F0, sp, vec + 4);
    lwc1(F0, obj, 8);
    swc1(F0, sp, vec + 8);
    a0 = lw(obj + model);
    a1 = addiu(sp, vec);
    a2 = 2;
    jal(pc + 0x64, gen::fn_sub_318A30_00318a30);
}

// sub_34CC00 [slot 2: step]: while alive (age +44 < lifetime +144, or lifetime 0): place the model (+160), advance
// its animation by +148 and update its frames (sub_317730); when the nodes are live (+156): the colour = colour
// (+36) x the track colour (+48 / +84) as floats scaled by gp[-32420], x 255; the node scale = scale track (+100) /
// 10 x scale (+32); then for each frame (+40) whose matrix the model has (sub_318D10 into sp+192): the frame's node
// (+152 array) gets the frame position, the frame's rotation (sub_329ED0 of the matrix rows, w = 0), the scale and
// colour, and is drawn (sub_3252A0). The age grows by one either way.
void Cpu::sub_34CC00() {
    enter(18);
    sp = addiu(sp, -320);
    sd(sp + 112, ra);
    sq(sp + 96, s5);
    sq(sp + 80, s4);
    sq(sp + 64, s3);
    sq(sp + 48, s2);
    sq(sp + 32, s1);
    sq(sp + 16, s0);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    s3 = a0;
    s1 = lw(a0 + 44);   // age
    s0 = lw(a0 + 144);  // lifetime
    s4 = lw(a0 + 40);   // frames
    s2 = lw(a0 + 152);  // node pointers
    v1 = slt(s1, s0);
    bool expired = false;
    if (v1 == 0) {
        charge(2);
        expired = s0 != 0;
    }
    if (!expired) {
        charge(40);
        model_place(s3, 160, 192, 296, 0x34CC58u);
        a0 = lw(s3 + 160);
        a1 = 0;
        lwc1(F12, s3, 148);
        jal(0x34CCD0u, gen::fn_sub_3189F0_003189f0);
        a0 = lw(s3 + 160);
        jal(0x34CCDCu, gen::fn_sub_317730_00317730);
        v1 = lw(s3 + 156);
        if (v1 != 0) {
            charge(57);
            a0 = addiu(s3, 48);
            a1 = addiu(s3, 84);
            a2 = s1;
            a3 = s0;
            jal(0x34CD00u, gen::fn_sub_32A120_0032a120);
            v1 = v0;  // the track colour
            v0 = lw(s3 + 36);
            sw(sp + 316, v0);
            lwc1(F0, gp, -32420);
            rgba_to_vf(v0, 316, VF10);
            vf_scale_fpr(v0, F0, VF10);
            rt::vmove(c, XYZW, VF11, VF10);
            sw(sp + 312, v1);
            rgba_to_vf(v0, 312, VF10);
            vf_scale_fpr(v0, F0, VF10);
            rt::vmul(c, XYZW, VF10, VF10, VF11);
            v0 = lui(0x437F);  // 255.0
            vf_scale_gpr(v0, VF10);
            vf_to_rgba(v0, VF10);
            sw(sp + 308, v0);
            s5 = lw(sp + 308);  // the node colour
            a0 = addiu(s3, 100);
            a1 = s1;
            a2 = s0;
            jal(0x34CDA4u, gen::fn_sub_32A540_0032a540);
            v1 = lui(0x4120);  // 10.0
            mtc1(v1, F1);
            div_s(F1, F0, F1);
            lwc1(F0, s3, 32);
            mul_s(F21, F1, F0);  // the node scale
            s0 = 0;              // frame index
            mtc1(zero, F20);     // 0.0 (the w lanes)
            for (;;) {
                charge(3);
                v1 = sltu(s0, s4);
                if (v1 == 0) break;
                backedge();
                charge(7);
                a0 = lw(s3 + 160);
                a1 = s0;
                a2 = addiu(sp, 192);
                jal(0x34CDE0u, gen::fn_sub_318D10_00318d10);
                if (v0 != 0) {
                    charge(58);
                    // position: the matrix's pos row (sp+240), w = 0
                    lwc1(F0, sp, 240);
                    swc1(F0, sp, 272);
                    lwc1(F0, sp, 244);
                    swc1(F0, sp, 276);
                    lwc1(F0, sp, 248);
                    swc1(F0, sp, 280);
                    swc1(F20, sp, 284);
                    a0 = lw(s2);
                    a1 = addiu(sp, 272);
                    jal(0x34CE14u, gen::fn_sub_325C10_00325c10);
                    // rotation: the four rows with w = 0 at sp+128, sub_329ED0 -> $vf10
                    for (s32 row = 0; row < 4; ++row) {
                        lwc1(F0, sp, 192 + 16 * row);
                        swc1(F0, sp, 128 + 16 * row);
                        lwc1(F0, sp, 196 + 16 * row);
                        swc1(F0, sp, 132 + 16 * row);
                        lwc1(F0, sp, 200 + 16 * row);
                        swc1(F0, sp, 136 + 16 * row);
                        swc1(F20, sp, 140 + 16 * row);
                    }
                    a0 = addiu(sp, 128);
                    jal(0x34CE90u, gen::fn_sub_329ED0_00329ed0);
                    a1 = addiu(sp, 256);
                    sqc2(VF10, a1, 0);
                    a0 = lw(s2);
                    jal(0x34CEA4u, gen::fn_sub_325D60_00325d60);
                    a0 = lw(s2);
                    mov_s(F12, F21);
                    jal(0x34CEB4u, gen::fn_sub_325E40_00325e40);
                    a0 = lw(s2);
                    a1 = s5;
                    jal(0x34CEC4u, gen::fn_sub_326030_00326030);
                    a0 = lw(s2);
                    jal(0x34CED0u, gen::fn_sub_3252A0_003252a0);
                }
                charge(2);
                s0 = addiu(s0, 1);
                s2 = addiu(s2, 4);
            }
        }
    }
    charge(15);
    v1 = lw(s3 + 44);
    v1 = addiu(v1, 1);
    sw(s3 + 44, v1);
    ra = ld(sp + 112);
    lq(s5, sp + 96);
    lq(s4, sp + 80);
    lq(s3, sp + 64);
    lq(s2, sp + 48);
    lq(s1, sp + 32);
    lq(s0, sp + 16);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 320);
}

// sub_34CF30 [slot 3: draw]: with the nodes off (+156 = 0), a debug gizmo per frame the model has (sub_358A30 in
// yellow 255,255,0,255 of size 4.0 at sp+112, frame axes sub_359380 of length 30.0); with the nodes on and while
// alive, each frame's node drawn on its layer (sub_325500).
void Cpu::sub_34CF30() {
    enter(9);
    sp = addiu(sp, -144);
    sd(sp + 48, ra);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    s1 = a0;
    v1 = lw(a0 + 156);
    if (v1 == 0) {
        charge(8);
        v1 = 255;
        sb(sp + 140, v1);
        sb(sp + 141, v1);
        sb(sp + 142, zero);
        sb(sp + 143, v1);
        s0 = 0;
        for (;;) {
            charge(4);
            v1 = lw(s1 + 40);
            v1 = sltu(s0, v1);
            if (v1 == 0) break;
            backedge();
            charge(7);
            a0 = lw(s1 + 160);
            a1 = s0;
            a2 = addiu(sp, 64);
            jal(0x34CF80u, gen::fn_sub_318D10_00318d10);
            if (v0 != 0) {
                charge(13);
                v0 = lui(0x4080);  // 4.0
                mtc1(v0, F12);
                a0 = addiu(sp, 112);
                a1 = addiu(sp, 140);
                a2 = 1;
                jal(0x34CFA4u, gen::fn_sub_358A30_00358a30);
                v0 = lui(0x41F0);  // 30.0
                mtc1(v0, F12);
                a0 = addiu(sp, 64);
                a1 = 1;
                jal(0x34CFBCu, gen::fn_sub_359380_00359380);
            }
            charge(1);
            s0 = addiu(s0, 1);
        }
        charge(2);
    } else {
        charge(7);
        a0 = lw(s1 + 144);  // lifetime
        s2 = lw(s1 + 40);   // frames
        s0 = lw(s1 + 152);  // node pointers
        v1 = lw(s1 + 44);   // age
        v1 = slt(v1, a0);
        bool expired = false;
        if (v1 == 0) {
            charge(2);
            expired = a0 != 0;
        }
        if (!expired) {
            charge(3);
            s1 = 0;
            for (;;) {
                charge(3);
                v1 = sltu(s1, s2);
                if (v1 == 0) break;
                backedge();
                charge(5);
                a0 = lw(s0);
                jal(0x34D014u, gen::fn_sub_325500_00325500);
                s0 = addiu(s0, 4);
                s1 = addiu(s1, 1);
            }
        }
    }
    charge(7);
    ra = ld(sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 144);
}

// sub_34D050 [slot 1: update]: step, then draw (s0 keeps the object).
void Cpu::sub_34D050() {
    enter(14);
    sp = addiu(sp, -32);
    sd(sp + 16, ra);
    sq(sp, s0);
    s0 = a0;
    jal(0x34D060u, gen::fn_sub_34CC00_0034cc00);
    a0 = s0;
    jal(0x34D06Cu, gen::fn_sub_34CF30_0034cf30);
    ra = ld(sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 32);
}

void Cpu::sub_34D090() { sub_34C630(); }
void Cpu::sub_34D0A0() { sub_34C640(); }
// sub_34D0B0 [slot 12]: colour word +36.
void Cpu::sub_34D0B0() {
    enter(3);
    sw(a0 + 36, a1);
}
void Cpu::sub_34D0C0() { sub_34C660(); }

// =========================================================================================================
// Kind 3: the clump particle system
// =========================================================================================================

// sub_34D0D0 [RpClumpForAllAtomics callback] (a0 atomic, a1 RGBA bytes): every material of the atomic's geometry
// (+24; material pointers +32, count +36) gets the colour (material +4..+7). Returns the atomic.
void Cpu::sub_34D0D0() {
    enter(5);
    t2 = lw(a0 + 24);  // geometry
    t1 = lw(t2 + 36);  // material count
    t3 = 0;
    for (;;) {
        charge(3);
        v0 = slt(t3, t1);
        if (v0 == 0) break;
        backedge();
        charge(13);
        v1 = sll(t3, 2);
        v0 = lw(t2 + 32);
        v0 = addu(v0, v1);
        t0 = lw(v0);  // material
        a3 = lbu(a1);
        a2 = lbu(a1 + 1);
        v1 = lbu(a1 + 2);
        v0 = lbu(a1 + 3);
        sb(t0 + 4, a3);
        sb(t0 + 5, a2);
        sb(t0 + 6, v1);
        sb(t0 + 7, v0);
        t3 = addiu(t3, 1);
    }
    charge(3);
    v0 = a0;
}

// sub_34D130 [RpClumpForAllAtomics callback]: the atomic's geometry flags (+8) |= 0x40 (material colours modulate).
// Returns the atomic.
void Cpu::sub_34D130() {
    enter(7);
    v1 = lw(a0 + 24);
    v0 = lw(v1 + 8);
    v0 = v0 | 0x40u;
    sw(v1 + 8, v0);
    v0 = a0;
}

// sub_34D150 [emit one particle] (a0 the object's emitter parameters, a1 its 24-byte record): the direction (+0..+8)
// is the fixed one (+20..+28) when +16 is 0, else three random lanes 2 * (rand - 0.5); normalised on VU0 (rsqrt of
// the squared length), or (0, 1, 0) when its length is 0. Speed (+16) = +36 x spread(+40), spin (+12) = rand x
// gp[-32416]; the colour phase (+20): mode +52 = 2 -> (record index) % 6, 1 -> effMiscRand % 6, else -1.
void Cpu::sub_34D150() {
    enter(10);
    sp = addiu(sp, -80);
    sd(sp + 48, ra);
    sq(sp + 32, s1);
    sq(sp + 16, s0);
    swc1(F20, sp, 0);
    s1 = a0;  // parameters
    s0 = a1;  // record
    v0 = lbu(a0 + 16);
    if (v0 == 0) {
        charge(8);
        lwc1(F0, s1, 20);
        swc1(F0, sp, 64);
        lwc1(F0, s1, 24);
        swc1(F0, sp, 68);
        lwc1(F0, s1, 28);
        swc1(F0, sp, 72);
    } else {
        charge(36);
        for (s32 lane = 0; lane < 3; ++lane) {
            rand01(0x34D19Cu + 0x30u * static_cast<u32>(lane));
            v0 = lui(0x3F00);  // 0.5
            mtc1(v0, F1);
            sub_s(F1, F0, F1);
            v0 = lui(0x4000);  // 2.0
            mtc1(v0, F0);
            mul_s(F0, F0, F1);
            swc1(F0, sp, 64 + 4 * lane);
        }
    }
    charge(14);
    v1 = addiu(sp, 64);
    lqc2(VF10, v1, 0);
    rt::vmul(c, XYZ, VF2, VF10, VF10);
    rt::vadd_bc(c, X, VF2, VF2, VF2, BY);
    rt::vadd_bc(c, X, VF2, VF2, VF2, BZ);
    rt::vsqrt(c, VF2, BX);
    rt::vwaitq(c);
    cfc2(v0, kQ);  // the length
    mtc1(v0, F1);
    mtc1(zero, F0);
    c_eq_s(F0, F1);
    if (cop1_cond()) {
        charge(4);
        swc1(F0, s0, 0);
        v0 = lui(0x3F80);
        sw(s0 + 4, v0);
        swc1(F0, s0, 8);
    } else {
        charge(16);
        rt::vmul(c, XYZ, VF2, VF10, VF10);
        rt::vmula_bc(c, W, VF0, VF2, BX);
        rt::vmadda_bc(c, W, VF0, VF2, BY);
        rt::vmadd_bc(c, W, VF2, VF0, VF2, BZ);
        rt::vrsqrt(c, VF0, BW, VF2, BW);
        rt::vwaitq(c);
        rt::vmulq(c, XYZ, VF10, VF10);
        sqc2(VF10, v1, 0);
        lwc1(F0, sp, 64);
        swc1(F0, s0, 0);
        lwc1(F0, sp, 68);
        swc1(F0, s0, 4);
        lwc1(F0, sp, 72);
        swc1(F0, s0, 8);
    }
    charge(25);
    lwc1(F20, s1, 40);
    rand01(0x34D2B8u);
    spread(v0, F1, F20);
    lwc1(F0, s1, 36);
    mul_s(F0, F0, F1);
    swc1(F0, s0, 16);
    rand01(0x34D2F0u);
    lwc1(F1, gp, -32416);
    mul_s(F0, F1, F0);
    swc1(F0, s0, 12);
    a0 = lw(s1 + 52);  // colour phase mode
    v1 = 2;
    if (a0 == v1) {
        charge(11);
        v1 = lw(s1 + 92);  // the record array
        a0 = subu(s0, v1);
        v1 = 24;
        divu(a0, v1);
        mflo(a0);
        v1 = 6;
        divu(a0, v1);
        mfhi(v1);
        sb(s0 + 20, v1);
    } else {
        charge(3);
        v1 = 1;
        if (a0 == v1) {
            charge(9);
            a0 = 0;
            jal(0x34D32Cu, gen::fn_sub_357FD0_00357fd0);
            v1 = 6;
            divu(v0, v1);
            mfhi(v1);
            sb(s0 + 20, v1);
        } else {
            charge(2);
            charge(2);
            v1 = si(-1);
            sb(s0 + 20, v1);
        }
    }
    charge(7);
    ra = ld(sp + 48);
    lq(s1, sp + 32);
    lq(s0, sp + 16);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 80);
}

// sub_34D3A0 [the colour of a record at `time`] (a0 parameters, a1 record, a2 time; $vf10 in and out, a 16-byte
// frame for the word -> vector moves): six colour keys at +60; the key length is +56 / 6 frames. With a positive key
// length the colour lerps from key (phase + time / len) % 6 to the next one by (time % len) / len; otherwise it is
// key `phase`. Keys are scaled by gp[-32232]; $vf10 is multiplied by the colour.
void Cpu::sub_34D3A0() {
    enter(7);
    sp = addiu(sp, -16);
    v0 = lw(a0 + 56);
    t0 = 6;
    div(v0, t0);
    mflo(a3);  // the key length
    if (sgn(a3) <= 0) {
        charge(16);
        v0 = lb(a1 + 20);
        v0 = sll(v0, 2);
        v0 = addu(v0, a0);
        v0 = lw(v0 + 60);
        sw(sp + 4, v0);
        v1 = lw(gp - 32232);
        rgba_to_vf(v0, 4, VF11);
        vf_scale_gpr(v1, VF11);
        rt::vmul(c, XYZW, VF10, VF10, VF11);
    } else {
        charge(65);
        rt::vmove(c, XYZW, VF12, VF10);
        div(a2, a3);
        mflo(v1);  // time / len
        div(a2, a3);
        mfhi(v0);  // time % len
        mtc1(v0, F0);
        cvt_s_w(F1, F0);
        mtc1(a3, F0);
        cvt_s_w(F0, F0);
        div_s(F1, F1, F0);  // t
        v0 = lb(a1 + 20);
        v0 = addu(v0, v1);
        div(v0, t0);
        mfhi(v1);  // key k
        v0 = addiu(v1, 1);
        div(v0, t0);
        mfhi(v0);  // key k + 1
        v0 = sll(v0, 2);
        v0 = addu(v0, a0);
        v0 = lw(v0 + 60);
        sw(sp + 12, v0);
        lwc1(F0, gp, -32232);
        rgba_to_vf(v0, 12, VF11);
        vf_scale_fpr(v0, F0, VF11);
        v0 = sll(v1, 2);
        v0 = addu(v0, a0);
        v0 = lw(v0 + 60);
        sw(sp + 8, v0);
        rgba_to_vf(v0, 8, VF10);
        vf_scale_fpr(v1, F0, VF10);
        v1 = lui(0x3F80);
        mtc1(v1, F0);
        sub_s(F0, F0, F1);  // 1 - t
        vf_scale_fpr(v1, F0, VF10);
        vf_scale_fpr(v1, F1, VF11);
        rt::vadd(c, XYZW, VF10, VF10, VF11);
        rt::vmove(c, XYZW, VF11, VF12);
        rt::vmul(c, XYZW, VF10, VF10, VF11);
    }
    charge(3);
    sp = addiu(sp, 16);
}

// sub_34D810 [slot 6: copy] (a0 dst, a1 src): when src's kind word (+12) is 3, dst's clump (+84) is destroyed (when
// it has one) and replaced by a clone of src's, whose atomics get the modulate flag (sub_4916D0(clone, sub_34D130,
// 0)); the kind word is copied either way.
void Cpu::sub_34D810() {
    enter(10);
    sp = addiu(sp, -48);
    sd(sp + 32, ra);
    sq(sp + 16, s1);
    sq(sp, s0);
    s1 = a0;
    s0 = a1;
    a0 = lhu(a1 + 12);
    v1 = 3;
    if (a0 == v1) {
        charge(3);
        a0 = lw(s1 + 84);
        if (a0 != 0) {
            charge(2);
            jal(0x34D84Cu, gen::fn_sub_491EA0_00491ea0);
        }
        charge(10);
        a0 = lw(s0 + 84);
        jal(0x34D858u, gen::fn_sub_491CC0_00491cc0);
        sw(s1 + 84, v0);
        a0 = v0;
        a1 = lui(0x35);
        a1 = addiu(a1, -11984);  // sub_34D130
        a2 = 0;
        jal(0x34D874u, gen::fn_sub_4916D0_004916d0);
    } else {
        charge(2);
    }
    charge(8);
    v1 = lhu(s0 + 12);
    sh(s1 + 12, v1);
    ra = ld(sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 48);
}

// sub_34D990 [load the clump of a memory stream] (a0 object, a1 data, a2 size): opens a memory stream over {data,
// size} (sub_4C58A0(3, 1, sp+112)) and walks its chunk headers (sub_4C1970 into sp+80: type, length): the first
// chunk 0x10 is read as the clump, the first 0x16 as a texture dictionary (walked with sub_1A13B0 collecting into
// sp+124, then released by sub_4D0D10), any other chunk is skipped; a type 0 ends the walk. After the close, the
// collected texture (sp+124) goes through sub_1A14C0; the clump is stored at +84 and its atomics get the modulate
// flag.
void Cpu::sub_34D990() {
    enter(20);
    sp = addiu(sp, -128);
    sd(sp + 64, ra);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    s3 = a0;
    s1 = 0;  // the clump
    s0 = 0;  // the texture dictionary
    sw(sp + 124, zero);
    sw(sp + 112, a1);
    sw(sp + 116, a2);
    a0 = 3;
    a1 = 1;
    a2 = addiu(sp, 112);
    jal(0x34D9CCu, gen::fn_sub_4C58A0_004c58a0);
    s2 = v0;  // the stream
    for (;;) {
        charge(6);
        a0 = s2;
        a1 = addiu(sp, 80);
        jal(0x34DA88u, gen::fn_sub_4C1970_004c1970);
        if (v0 == 0) break;
        backedge();
        charge(3);
        v1 = lw(sp + 80);  // chunk type
        if (v1 == 0) break;
        charge(3);
        v0 = 16;
        if (v1 == v0) {
            charge(2);
            if (s1 != 0) continue;
            charge(6);
            a0 = s2;
            jal(0x34DA5Cu, gen::fn_sub_4920A0_004920a0);
            s1 = v0;
            continue;
        }
        charge(3);
        v0 = 22;
        if (v1 == v0) {
            charge(2);
            if (s0 != 0) continue;
            charge(15);
            a0 = s2;
            jal(0x34DA18u, gen::fn_sub_4C8680_004c8680);
            s0 = v0;
            a0 = s0;
            a1 = lui(0x1A);
            a1 = addiu(a1, 5040);  // sub_1A13B0
            a2 = addiu(sp, 124);
            jal(0x34DA34u, gen::fn_sub_4D0DC0_004d0dc0);
            a0 = s0;
            jal(0x34DA40u, gen::fn_sub_4D0D10_004d0d10);
            continue;
        }
        charge(2);
        charge(4);
        a0 = s2;
        a1 = lw(sp + 84);  // chunk length
        jal(0x34DA78u, gen::fn_sub_4C5620_004c5620);
    }
    charge(7);
    a0 = s2;
    a1 = addiu(sp, 112);
    jal(0x34DAA0u, gen::fn_sub_4C5780_004c5780);
    a0 = lw(sp + 124);
    if (a0 != 0) {
        charge(2);
        jal(0x34DAB4u, gen::fn_sub_1A14C0_001a14c0);
    }
    charge(15);
    sw(s3 + 84, s1);
    a0 = s1;
    a1 = lui(0x35);
    a1 = addiu(a1, -11984);  // sub_34D130
    a2 = 0;
    jal(0x34DAD0u, gen::fn_sub_4916D0_004916d0);
    ra = ld(sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 128);
}

// sub_34DB00 [slot 7: reset]: sub_332200(system +88) when there is one.
void Cpu::sub_34DB00() { field_call_if(88, 0x34DB14u, gen::fn_sub_332200_00332200); }

// sub_34DB30 [slot 2: step]: steps the system (+88, sub_332210); when it has particles (count +8, records +24 of 32
// bytes, a non-null +16) and the object's kind word (+12) is 3, every particle whose system record +16 is 0 (just
// born) is emitted into its 24-byte record (+92 array) by sub_34D150.
void Cpu::sub_34DB30() {
    enter(15);
    sp = addiu(sp, -96);
    sd(sp + 80, ra);
    sq(sp + 64, s4);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    s3 = a0;
    a0 = lw(a0 + 88);
    jal(0x34DB54u, gen::fn_sub_332210_00332210);
    a0 = lw(s3 + 88);
    s0 = lw(a0 + 8);  // particle count
    if (s0 != 0) {
        charge(3);
        v1 = lw(a0 + 16);
        if (v1 != 0) {
            charge(6);
            s2 = lw(a0 + 24);  // system records
            s1 = lw(s3 + 92);  // object records
            a0 = lhu(s3 + 12);
            v1 = 3;
            if (a0 == v1) {
                charge(3);
                s4 = 0;
                for (;;) {
                    charge(3);
                    v1 = slt(s4, s0);
                    if (v1 == 0) break;
                    backedge();
                    charge(3);
                    v1 = lw(s2 + 16);
                    if (v1 == 0) {
                        charge(4);
                        a0 = s3;
                        a1 = s1;
                        jal(0x34DBB8u, gen::fn_sub_34D150_0034d150);
                    }
                    charge(3);
                    s4 = addiu(s4, 1);
                    s2 = addiu(s2, 32);
                    s1 = addiu(s1, 24);
                }
            } else {
                charge(2);
            }
        }
    }
    charge(9);
    ra = ld(sp + 80);
    lq(s4, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 96);
}

// sub_34E390 [slot 3]: queue on the system's layer (sub_321220).
void Cpu::sub_34E390() { layer_queue(88, 0x34E3ACu, gen::fn_sub_321220_00321220); }
// sub_34E3D0 [slot 1: update]: step (sub_34DB30), then queue.
void Cpu::sub_34E3D0() {
    step_then_queue(88, 0x34E3E0u, gen::fn_sub_34DB30_0034db30, 0x34E400u, gen::fn_sub_321220_00321220);
}
// sub_34E420 / sub_34E450 [slots 8 / 9]: the system's position / rotation.
void Cpu::sub_34E420() { field_call(9, 88, 0x34E42Cu, gen::fn_sub_3322D0_003322d0); }
void Cpu::sub_34E450() { field_call(9, 88, 0x34E45Cu, gen::fn_sub_332310_00332310); }
// sub_34E480 [slot 12] (and kind 4's sub_34FC90): colour word +4.
void Cpu::sub_34E480() {
    enter(3);
    sw(a0 + 4, a1);
}
// sub_34E490 [slot 10]: scale +8 = $f12, and the system's scale.
void Cpu::sub_34E490() {
    enter(10);
    sp = addiu(sp, -16);
    sd(sp, ra);
    swc1(F12, a0, 8);
    a0 = lw(a0 + 88);
    jal(0x34E4A0u, gen::fn_sub_332330_00332330);
    ra = ld(sp);
    sp = addiu(sp, 16);
}

// =========================================================================================================
// Kind 4: the textured particle system
// =========================================================================================================

// sub_34E7C0 (a0 object, a1 name): texture +96 = sub_3210C0(name).
void Cpu::sub_34E7C0() {
    enter(13);
    sp = addiu(sp, -32);
    sd(sp + 16, ra);
    sq(sp, s0);
    s0 = a0;
    a0 = a1;
    jal(0x34E7D4u, gen::fn_sub_3210C0_003210c0);
    sw(s0 + 96, v0);
    ra = ld(sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 32);
}

// sub_34E800 [slot 6: copy]: dst shares src's texture (+96), whose reference count (+84) grows by one.
void Cpu::sub_34E800() {
    enter(7);
    a1 = lw(a1 + 96);
    sw(a0 + 96, a1);
    v1 = lw(a1 + 84);
    v1 = addiu(v1, 1);
    sw(a1 + 84, v1);
}

// sub_34E910 [slot 7: reset]: sub_332200(system +92) when there is one.
void Cpu::sub_34E910() { field_call_if(92, 0x34E924u, gen::fn_sub_332200_00332200); }

// The emission of one kind-4 particle into its 28-byte record (sub_34E940's body and sub_34F6B0's loop, the same
// instructions; `pc` is the first jal, the others follow at the compiler's distances). With f20 = spread(+12):
//   +0 / +12 = rand x gp[-32416] (two phases), +4 / +16 = (0.5 + 0.5 rand) x +24 (their speeds),
//   +8 / +20 = (gp[-32544] + gp[-32628] rand) x +16 / +20 x f20 (two sizes), +24 = spread(+36).
void Cpu::kind4_emit(Gpr& obj, Gpr& rec, u32 pc) {
    lwc1(F20, obj, 12);
    rand01(pc);
    spread(v0, F20, F20);
    rand01(pc + 0x2C);
    lwc1(F1, gp, -32416);
    mul_s(F0, F1, F0);
    swc1(F0, rec, 0);
    rand01(pc + 0x44);
    lwc1(F1, gp, -32416);
    mul_s(F0, F1, F0);
    swc1(F0, rec, 12);
    rand01(pc + 0x5C);
    half_plus_half();
    lwc1(F0, obj, 24);
    mul_s(F0, F0, F1);
    swc1(F0, rec, 4);
    rand01(pc + 0x8C);
    half_plus_half();
    lwc1(F0, obj, 24);
    mul_s(F0, F0, F1);
    swc1(F0, rec, 16);
    rand01(pc + 0xBC);
    gp_affine();
    lwc1(F0, obj, 16);
    mul_s(F0, F0, F1);
    mul_s(F0, F20, F0);
    swc1(F0, rec, 8);
    rand01(pc + 0xF0);
    gp_affine();
    lwc1(F0, obj, 20);
    mul_s(F0, F0, F1);
    mul_s(F0, F20, F0);
    swc1(F0, rec, 20);
    lwc1(F20, obj, 36);
    rand01(pc + 0x128);
    spread(v1, F0, F20);
    swc1(F0, rec, 24);
}

// sub_34E940 [emit one particle] (a0 object, a1 record): kind4_emit, one block.
void Cpu::sub_34E940() {
    enter(101);
    sp = addiu(sp, -64);
    sd(sp + 48, ra);
    sq(sp + 32, s1);
    sq(sp + 16, s0);
    swc1(F20, sp, 0);
    s1 = a0;
    s0 = a1;
    kind4_emit(s1, s0, 0x34E964u);
    ra = ld(sp + 48);
    lq(s1, sp + 32);
    lq(s0, sp + 16);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 64);
}

// sub_34F6B0 [slot 2: step]: steps the system (+92, sub_332210); when it has particles (count +8, records +24, a
// non-null +16): the scroll positions +84 / +88 advance by +28 / +32, then for every particle (system record of 32
// bytes, object record of 28 at +100): emitted when its system record +16 is 0 (kind4_emit), and while that word is
// not negative the two phases advance by their speeds (+0 += +4, +12 += +16).
void Cpu::sub_34F6B0() {
    enter(16);
    sp = addiu(sp, -112);
    sd(sp + 96, ra);
    sq(sp + 80, s4);
    sq(sp + 64, s3);
    sq(sp + 48, s2);
    sq(sp + 32, s1);
    sq(sp + 16, s0);
    swc1(F20, sp, 0);
    s4 = a0;
    a0 = lw(a0 + 92);
    jal(0x34F6D8u, gen::fn_sub_332210_00332210);
    a0 = lw(s4 + 92);
    s0 = lw(a0 + 8);  // particle count
    if (s0 != 0) {
        charge(3);
        v1 = lw(a0 + 16);
        if (v1 != 0) {
            charge(13);
            s3 = lw(a0 + 24);   // system records
            s2 = lw(s4 + 100);  // object records
            lwc1(F1, s4, 28);
            lwc1(F0, s4, 84);
            add_s(F0, F0, F1);
            swc1(F0, s4, 84);
            lwc1(F1, s4, 32);
            lwc1(F0, s4, 88);
            add_s(F0, F0, F1);
            swc1(F0, s4, 88);
            s1 = 0;
            for (;;) {
                charge(3);
                v1 = slt(s1, s0);
                if (v1 == 0) break;
                backedge();
                charge(3);
                v1 = lw(s3 + 16);
                if (v1 == 0) {
                    charge(87);
                    kind4_emit(s4, s2, 0x34F744u);
                }
                charge(3);
                v1 = lw(s3 + 16);
                if (sgn(v1) >= 0) {
                    charge(8);
                    lwc1(F1, s2, 4);
                    lwc1(F0, s2, 0);
                    add_s(F0, F0, F1);
                    swc1(F0, s2, 0);
                    lwc1(F1, s2, 16);
                    lwc1(F0, s2, 12);
                    add_s(F0, F0, F1);
                    swc1(F0, s2, 12);
                }
                charge(3);
                s1 = addiu(s1, 1);
                s3 = addiu(s3, 32);
                s2 = addiu(s2, 28);
            }
        }
    }
    charge(10);
    ra = ld(sp + 96);
    lq(s4, sp + 80);
    lq(s3, sp + 64);
    lq(s2, sp + 48);
    lq(s1, sp + 32);
    lq(s0, sp + 16);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 112);
}

// sub_34F910 [draw the particles] (a0 object, a1 mode): when the system (+92) has particles: the manager's slot 21
// (sub_3210A0) gives the raster; mode byte 1 binds it (the RW engine's render-state set 0x960090 with state 1, a
// `jalr`); the raster size (+12 / +16 as floats) at sp+240, the colour (+4) as floats x gp[-32232] at sp+224. With
// system flag bit 0 clear each live particle (system record +16 not negative) is drawn at its own position
// (sub_34EAE0); with it set, the positions are transformed by the system's matrix (rotation sub_3322F0 -> VU0
// matrix sub_357E30, position sub_3322B0 as row 3) first, into sp+208.
void Cpu::sub_34F910() {
    enter(14);
    sp = addiu(sp, -256);
    sd(sp + 96, ra);
    sq(sp + 80, s5);
    sq(sp + 64, s4);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    s4 = a0;
    s3 = a1;  // mode
    a0 = lw(a0 + 92);
    s0 = lw(a0 + 8);  // particle count
    if (s0 != 0) {
        charge(3);
        v1 = lw(a0 + 16);
        if (v1 != 0) {
            charge(10);
            s2 = lw(a0 + 24);   // system records
            s1 = lw(s4 + 100);  // object records
            a0 = 21;
            jal(0x34F960u, gen::fn_sub_3210A0_003210a0);
            s5 = lw(v0);  // the raster
            v0 = s3 & 0xFFu;
            a0 = 1;
            if (v0 == a0) {
                charge(5);
                a1 = s5;
                v0 = lui(0x96);
                v0 = lw(v0 + 144);  // RwRenderStateSet-like (0x960090)
                jalr(0x34F988u, w(v0));
            }
            charge(25);
            lwc1(F0, s5, 12);
            cvt_s_w(F0, F0);
            swc1(F0, sp, 240);
            lwc1(F0, s5, 16);
            cvt_s_w(F0, F0);
            swc1(F0, sp, 244);
            v0 = lw(s4 + 4);
            sw(sp + 252, v0);
            v1 = lw(gp - 32232);
            rgba_to_vf(v0, 252, VF10);
            vf_scale_gpr(v1, VF10);
            v1 = addiu(sp, 224);
            sqc2(VF10, v1, 0);
            a0 = lw(s4 + 92);
            v1 = lw(a0 + 12);
            v1 = v1 & 1u;
            if (v1 == 0) {
                charge(3);
                s5 = 0;
                for (;;) {
                    charge(3);
                    v1 = slt(s5, s0);
                    if (v1 == 0) break;
                    backedge();
                    charge(3);
                    v1 = lw(s2 + 16);
                    if (sgn(v1) >= 0) {
                        charge(9);
                        a0 = s4;
                        a1 = s1;
                        a2 = s2;
                        a3 = s2;  // the position: the system record itself
                        t0 = addiu(sp, 224);
                        t1 = addiu(sp, 240);
                        t2 = s3;
                        jal(0x34FA28u, gen::fn_sub_34EAE0_0034eae0);
                    }
                    charge(3);
                    s5 = addiu(s5, 1);
                    s2 = addiu(s2, 32);
                    s1 = addiu(s1, 28);
                }
                charge(2);
            } else {
                charge(21);
                a1 = addiu(sp, 176);
                jal(0x34FA54u, gen::fn_sub_3322F0_003322f0);
                a0 = lw(s4 + 92);
                a1 = addiu(sp, 192);
                jal(0x34FA64u, gen::fn_sub_3322B0_003322b0);
                v0 = addiu(sp, 176);
                lqc2(VF10, v0, 0);
                jal(0x34FA74u, gen::fn_sub_357E30_00357e30);
                v1 = addiu(sp, 192);
                lqc2(VF31, v1, 0);
                v1 = addiu(sp, 112);
                sqc2(VF28, v1, 0);
                sqc2(VF29, v1, 16);
                sqc2(VF30, v1, 32);
                sqc2(VF31, v1, 48);
                s5 = 0;
                for (;;) {
                    charge(3);
                    v1 = slt(s5, s0);
                    if (v1 == 0) break;
                    backedge();
                    charge(3);
                    v1 = lw(s2 + 16);
                    if (sgn(v1) >= 0) {
                        charge(20);
                        v0 = addiu(sp, 112);
                        lqc2(VF28, v0, 0);
                        lqc2(VF29, v0, 16);
                        lqc2(VF30, v0, 32);
                        lqc2(VF31, v0, 48);
                        lqc2(VF10, s2, 0);
                        rt::vmula_bc(c, XYZW, VF28, VF10, BX);
                        rt::vmadda_bc(c, XYZW, VF29, VF10, BY);
                        rt::vmadda_bc(c, XYZW, VF30, VF10, BZ);
                        rt::vmadd_bc(c, XYZW, VF10, VF31, VF0, BW);
                        a3 = addiu(sp, 208);
                        sqc2(VF10, a3, 0);
                        a0 = s4;
                        a1 = s1;
                        a2 = s2;
                        t0 = addiu(sp, 224);
                        t1 = addiu(sp, 240);
                        t2 = s3;
                        jal(0x34FAF8u, gen::fn_sub_34EAE0_0034eae0);
                    }
                    charge(3);
                    s5 = addiu(s5, 1);
                    s2 = addiu(s2, 32);
                    s1 = addiu(s1, 28);
                }
            }
        }
    }
    charge(10);
    ra = ld(sp + 96);
    lq(s5, sp + 80);
    lq(s4, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 256);
}

// sub_34FB40 / sub_34FB70 [draw, mode 0 / 1].
void Cpu::sub_34FB40() {
    enter(9);
    sp = addiu(sp, -16);
    sd(sp, ra);
    a1 = 0;
    jal(0x34FB4Cu, gen::fn_sub_34F910_0034f910);
    ra = ld(sp);
    sp = addiu(sp, 16);
}
void Cpu::sub_34FB70() {
    enter(9);
    sp = addiu(sp, -16);
    sd(sp, ra);
    a1 = 1;
    jal(0x34FB7Cu, gen::fn_sub_34F910_0034f910);
    ra = ld(sp);
    sp = addiu(sp, 16);
}

// sub_34FBA0 [slot 3]: queue on the system's layer (sub_3212A0); sub_34FBE0 [slot 1]: step, then queue.
void Cpu::sub_34FBA0() { layer_queue(92, 0x34FBBCu, gen::fn_sub_3212A0_003212a0); }
void Cpu::sub_34FBE0() {
    step_then_queue(92, 0x34FBF0u, gen::fn_sub_34F6B0_0034f6b0, 0x34FC10u, gen::fn_sub_3212A0_003212a0);
}
// sub_34FC30 / sub_34FC60 [slots 8 / 9]: the system's position / rotation.
void Cpu::sub_34FC30() { field_call(9, 92, 0x34FC3Cu, gen::fn_sub_3322D0_003322d0); }
void Cpu::sub_34FC60() { field_call(9, 92, 0x34FC6Cu, gen::fn_sub_332310_00332310); }
void Cpu::sub_34FC90() { sub_34E480(); }
// sub_34FCA0 [slot 10]: scale +8 = $f12, and the system's scale.
void Cpu::sub_34FCA0() {
    enter(10);
    sp = addiu(sp, -16);
    sd(sp, ra);
    swc1(F12, a0, 8);
    a0 = lw(a0 + 92);
    jal(0x34FCB0u, gen::fn_sub_332330_00332330);
    ra = ld(sp);
    sp = addiu(sp, 16);
}

// =========================================================================================================
// [nodes] the effect-node wrappers (the API the game code calls: sub_107B20 and the field / event / result code)
// =========================================================================================================

void Cpu::sub_34FCD0() { leaf_frame_call(8, 0x34FCD8u, gen::fn_sub_324BD0_00324bd0); }
void Cpu::sub_34FCF0() { leaf_frame_call(8, 0x34FCF8u, gen::fn_sub_3257E0_003257e0); }
void Cpu::sub_34FD10() { leaf_frame_call(8, 0x34FD18u, gen::fn_sub_325B80_00325b80); }
void Cpu::sub_34FD30() { leaf_frame_call(8, 0x34FD38u, gen::fn_sub_3252A0_003252a0); }
void Cpu::sub_34FD50() { leaf_frame_call(8, 0x34FD58u, gen::fn_sub_325920_00325920); }
void Cpu::sub_34FD70() {
    keep_a0_call2(0x34FD84u, gen::fn_sub_321120_00321120, 0x34FD90u, gen::fn_sub_325500_00325500);
}
void Cpu::sub_34FDB0() {
    keep_a0_call2(0x34FDC4u, gen::fn_sub_321120_00321120, 0x34FDD0u, gen::fn_sub_3257A0_003257a0);
}

// sub_34FDF0 [position from a vec3]: the three floats at a1 with w = 0 at sp+16, sub_325C10(node, sp+16).
void Cpu::sub_34FDF0() {
    enter(16);
    sp = addiu(sp, -32);
    sd(sp, ra);
    lwc1(F0, a1, 0);
    swc1(F0, sp, 16);
    lwc1(F0, a1, 4);
    swc1(F0, sp, 20);
    lwc1(F0, a1, 8);
    swc1(F0, sp, 24);
    sw(sp + 28, zero);
    a1 = addiu(sp, 16);
    jal(0x34FE18u, gen::fn_sub_325C10_00325c10);
    ra = ld(sp);
    sp = addiu(sp, 32);
}

// sub_34FE30 [rotation from Euler angles]: $f12..$f14 x gp[-32220] (degrees -> radians, inf), the rotation of
// sub_357EA0 ($vf10) at sp+32, sub_325D60(node, sp+32).
void Cpu::sub_34FE30() {
    enter(20);
    sp = addiu(sp, -48);
    sd(sp + 16, ra);
    sq(sp, s0);
    s0 = a0;
    lwc1(F0, gp, -32220);
    mul_s(F12, F0, F12);
    mul_s(F13, F0, F13);
    mul_s(F14, F0, F14);
    jal(0x34FE50u, gen::fn_sub_357EA0_00357ea0);
    a1 = addiu(sp, 32);
    sqc2(VF10, a1, 0);
    a0 = s0;
    jal(0x34FE64u, gen::fn_sub_325D60_00325d60);
    ra = ld(sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 48);
}

// sub_34FE80 [position and rotation from an RwMatrix] (a0 node, a1 matrix): the position row (+48) with w = 0 at
// sp+48 -> sub_325C10; the four rows with w = 0 at sp+80 -> sub_329ED0 -> $vf10 at sp+64 -> sub_325D60.
void Cpu::sub_34FE80() {
    enter(58);
    sp = addiu(sp, -144);
    sd(sp + 32, ra);
    sq(sp + 16, s1);
    sq(sp, s0);
    s1 = a0;
    s0 = a1;
    lwc1(F0, a1, 48);
    swc1(F0, sp, 48);
    lwc1(F0, a1, 52);
    swc1(F0, sp, 52);
    lwc1(F0, a1, 56);
    swc1(F0, sp, 56);
    sw(sp + 60, zero);
    a1 = addiu(sp, 48);
    jal(0x34FEB8u, gen::fn_sub_325C10_00325c10);
    for (s32 row = 0; row < 4; ++row) {
        lwc1(F0, s0, 16 * row);
        swc1(F0, sp, 80 + 16 * row);
        lwc1(F0, s0, 16 * row + 4);
        swc1(F0, sp, 84 + 16 * row);
        lwc1(F0, s0, 16 * row + 8);
        swc1(F0, sp, 88 + 16 * row);
        sw(sp + 92 + 16 * row, zero);
    }
    a0 = addiu(sp, 80);
    jal(0x34FF34u, gen::fn_sub_329ED0_00329ed0);
    a1 = addiu(sp, 64);
    sqc2(VF10, a1, 0);
    a0 = s1;
    jal(0x34FF48u, gen::fn_sub_325D60_00325d60);
    ra = ld(sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 144);
}

void Cpu::sub_34FF70() { leaf_frame_call(8, 0x34FF78u, gen::fn_sub_325E40_00325e40); }

// sub_34FF90 [colour from *rgba]: sub_326030(node, *a1).
void Cpu::sub_34FF90() {
    enter(9);
    sp = addiu(sp, -16);
    sd(sp, ra);
    a1 = lw(a1);
    jal(0x34FF9Cu, gen::fn_sub_326030_00326030);
    ra = ld(sp);
    sp = addiu(sp, 16);
}

// sub_34FFC0 [node -> matrix] (a0 node, a1 matrix): the node's rotation (+80 via sub_326170) as a rotation matrix
// into the matrix (sub_3296A0), its position (+64 via sub_326160) into the position row.
void Cpu::sub_34FFC0() {
    enter(29);
    sp = addiu(sp, -80);
    sd(sp + 32, ra);
    sq(sp + 16, s1);
    sq(sp, s0);
    s1 = a0;
    s0 = a1;
    a1 = addiu(sp, 64);
    jal(0x34FFDCu, gen::fn_sub_326170_00326170);
    a0 = s0;
    a1 = addiu(sp, 64);
    jal(0x34FFECu, gen::fn_sub_3296A0_003296a0);
    a0 = s1;
    a1 = addiu(sp, 48);
    jal(0x34FFFCu, gen::fn_sub_326160_00326160);
    lwc1(F0, sp, 48);
    swc1(F0, s0, 48);
    lwc1(F0, sp, 52);
    swc1(F0, s0, 52);
    lwc1(F0, sp, 56);
    swc1(F0, s0, 56);
    ra = ld(sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 80);
}

// The typed entry: arguments into $a0.., the body, $v0 back.
template <typename... A>
u64 run(EEContext& ctx, void (Cpu::*body)(), A... args) {
    const u64 in[] = {static_cast<u64>(args)...};
    for (unsigned i = 0; i < sizeof...(A); ++i) core::set_gpr64(ctx, GPR_A0 + i, in[i]);
    (Cpu(ctx).*body)();
    return core::gpr64(ctx, GPR_V0);
}

}  // namespace detail
}  // namespace epl

using epl::detail::Cpu;
using epl::detail::run;

// --- named immediates of the register-level (p3fes_handgen) bodies below ------------------------------------------
// The record offsets fx_epl.h documents for the four object kinds, as the load / store immediates, plus the records
// the bodies reach through them. Each name comes from the instructions that use it (and the notes of the earlier hand
// versions); the slot names of the rows are fx_epl.h's proposals.
namespace {
// kind 1, the model object (row 0x69C368)
namespace k1 {
inline constexpr s32 kPos = 0, kRot = 16, kScale = 32, kAdvance = 36, kColour = 40;
inline constexpr s32 kColourTrack = 44, kColourTrack2 = 80;  // the two arguments of the colour track sample sub_32A120
inline constexpr s32 kLayer = 84;                            // u16: the draw layer
inline constexpr s32 kScaleTrack = 96;                       // the scale track (sub_32A540)
inline constexpr s32 kLifetime = 140, kAdditive = 144, kModel = 148, kAge = 152;
}  // namespace k1
// kind 2, the node-carrying model (row 0x69C39C)
namespace k2 {
inline constexpr s32 kPos = 0, kRot = 16, kScale = 32, kColour = 36, kFrames = 40, kAge = 44;
inline constexpr s32 kColourTrack = 48, kColourTrack2 = 84, kScaleTrack = 100;
inline constexpr s32 kLifetime = 144, kAdvance = 148, kNodes = 152, kNodeMode = 156, kModel = 160;
}  // namespace k2
// kind 3, the clump particle system (row 0x69C3D0): its emitter parameters live in the object
namespace k3 {
inline constexpr s32 kColour = 4, kKindWord = 12;  // u16 kind word: 3 = emit (+8: the scale)
inline constexpr s32 kRandomDir = 16, kDir = 20;                        // u8 flag; the fixed direction (3 floats)
inline constexpr s32 kSpeed = 36, kSpread = 40, kPhaseMode = 52;        // phase mode 2 = index % 6, 1 = random % 6
inline constexpr s32 kKeyLength = 56, kKeys = 60;                       // the six colour keys (RGBA words)
inline constexpr s32 kClump = 84, kSystem = 88, kRecords = 92;
}  // namespace k3
// kind 4, the textured particle system (row 0x69C404)
namespace k4 {
inline constexpr s32 kColour = 4, kSpread = 12, kSizeA = 16, kSizeB = 20, kPhaseSpeed = 24;  // (+8: the scale)
inline constexpr s32 kScrollSpeedU = 28, kScrollSpeedV = 32, kSpread2 = 36, kScrollU = 84, kScrollV = 88;
inline constexpr s32 kSystem = 92, kTexture = 96, kRecords = 100;
}  // namespace k4
// a kind-3 particle record (24 bytes) and a kind-4 one (28 bytes)
namespace rec3 {
inline constexpr s32 kDir = 0, kSpin = 12, kSpeed = 16, kPhase = 20, kSize = 24;
}  // namespace rec3
namespace rec4 {
inline constexpr s32 kPhaseA = 0, kSpeedA = 4, kSizeA = 8, kPhaseB = 12, kSpeedB = 16, kSizeB = 20, kFactor = 24;
inline constexpr s32 kSize = 28;
}  // namespace rec4
// the particle system of the 0x3322xx layer and its 32-byte per-particle records
namespace psys {
inline constexpr s32 kCount = 8, kFlags = 12, kLive = 16, kRecords = 24, kOwner = 32;  // flags bit 0: own matrix
}  // namespace psys
namespace sysrec {
inline constexpr s32 kState = 16, kSize = 32;  // 0 = just born, negative = dead
}  // namespace sysrec
inline constexpr s32 kOwnerLayer = 84;           // the owner's u16 draw layer
// the model layer's record (sub_316E00)
namespace model {
inline constexpr s32 kId0 = 212, kId1 = 214, kFlags = 216;  // u16 ids; u16 flags (2, 0x18 additive)
}  // namespace model
// RenderWare: atomic -> geometry -> materials, textures, rasters
inline constexpr s32 kAtomicGeometry = 24;
namespace geom {
inline constexpr s32 kFlags = 8, kMaterials = 32, kMaterialCount = 36;  // flags 0x40: modulate material colours
}  // namespace geom
inline constexpr s32 kMaterialColour = 4;   // RGBA bytes
inline constexpr s32 kTextureRefCount = 84;
inline constexpr s32 kRasterWidth = 12, kRasterHeight = 16;
inline constexpr u32 kRwRenderStateSet = 0x960090u;  // the RW engine's render-state-set function pointer
inline constexpr s32 kRasterSlot = 21;               // sub_3210A0: the manager's resource slot of the particle raster
inline constexpr s32 kColourKeys = 6;
inline constexpr s32 kChunkClump = 0x10, kChunkTexDict = 0x16;  // RW stream chunk types
inline constexpr u32 kFnModulateAtomic = 0x34D130u;  // sub_34D130, the RpClumpForAllAtomics callback
inline constexpr u32 kFnCollectTexture = 0x1A13B0u;  // sub_1A13B0, the texture-dictionary walk callback
// $gp-relative float constants
inline constexpr s32 kGpColourUnit = -32232;   // 0x7CAF08: byte -> unit colour scale (kinds 1, 3, 4)
inline constexpr s32 kGpColourUnit2 = -32420;  // 0x7CAE4C: the same for kind 2
inline constexpr s32 kGpPhaseRange = -32416;   // 0x7CAE50: random phase / spin range
inline constexpr s32 kGpSizeBase = -32544;     // 0x7CADD0: kind-4 size = base + range * rand
inline constexpr s32 kGpSizeRange = -32628;    // 0x7CAD7C
}  // namespace

// 0x0034C250 sub_34C250 -- 200 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_34C250 [slot 6: copy from another object] (a0 dst, a1 src): destroys dst's model (+148) when it has one,
// creates a model with src's ids (src->model +212 / +214, flags 0), resets its matrix, starts animation 0 at speed
// 1.0 when the model has one, clears model flag 2 (+216) and stores it in dst.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34C250(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lq, hg::lw, hg::mtc1,
          hg::sd, hg::sh, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x0034c250
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s1 = a1;
    lw(a0, a0, k1::kModel);  // dst->model
    if (a0 != 0) {
        // 0x0034c274
        charge(ctx, 2);
        jal(ctx, 0x34C274u, gen::fn_sub_3174E0_003174e0);
    }
    // 0x0034c27c
    charge(ctx, 16);
    lw(v0, s1, k1::kModel);  // src->model
    lhu(a0, v0, model::kId0);
    lhu(a1, v0, model::kId1);
    a2 = 0;
    jal(ctx, 0x34C28Cu, gen::fn_sub_316E00_00316e00);
    s1 = v0;
    a0 = s1;
    jal(ctx, 0x34C29Cu, gen::fn_sub_318B10_00318b10);
    a0 = s1;
    a1 = 0;
    jal(ctx, 0x34C2ACu, gen::fn_sub_3185B0_003185b0);
    if (v0 != 0) {
        // 0x0034c2bc
        charge(ctx, 13);
        a0 = s1;
        a1 = 0;
        a2 = 0;
        a3 = 0;
        t0 = 0;
        jal(ctx, 0x34C2D0u, gen::fn_sub_3182D0_003182d0);
        v0 = mview::flt(1.0f);
        mtc1(v0, f12);
        a0 = s1;
        a1 = 0;
        jal(ctx, 0x34C2E8u, gen::fn_sub_3189F0_003189f0);
    }
    // 0x0034c2f0 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    lhu(v1, s1, model::kFlags);
    v1 = v1 & 0xFFFD;  // clear model flag 2
    sh(v1, s1, model::kFlags);
    sw(s1, s0, k1::kModel);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34C250(EEContext& ctx, u64 dst, u64 src) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(dst));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(src));
    sub_34C250(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x0034C320 sub_34C320 -- 44 bytes; frame 0x10: ra sp+0x0
// sub_34C320 [slot 7: reset]: the model's track 0 back to time 0.0 (sub_318770(model, 0) with $f12 = 0).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34C320(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lw, hg::mtc1, hg::sd;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x0034c320
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    mtc1(zero, f12);
    lw(a0, a0, k1::kModel);
    a1 = 0;
    jal(ctx, 0x34C334u, gen::fn_sub_318770_00318770);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34C320(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(obj));
    sub_34C320(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x0034C350 sub_34C350 -- 56 bytes; leaf frame (no stack)
// sub_34C350 [slot 2: step].
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34C350(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::lw, hg::sltu, hg::sw;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0034c350
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(a1, a0, k1::kLifetime);
    lw(v1, a0, k1::kAge);
    at = sltu(a1, v1);
    if (at != 0) {
        // 0x0034c364: past its lifetime: a lifetime 0 lives forever
        charge(ctx, 2);
        if (a1 != 0) {
            // 0x0034c380 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            return;
        }
    }
    // 0x0034c36c: alive: advance = 1.0, age + 1
    charge(ctx, 5);
    v1 = mview::flt(1.0f);
    sw(v1, a0, k1::kAdvance);
    lw(v1, a0, k1::kAge);
    v1 = addiu(v1, 1);
    sw(v1, a0, k1::kAge);
    // 0x0034c380 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34C350(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(obj));
    sub_34C350(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x0034C390 sub_34C390 -- 524 bytes; frame 0xB0: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// sub_34C390 [draw] (called by the layer task sub_321360): while alive, the model's colour = base colour (+40) x the
// colour track sampled at (age, lifetime) (sub_32A120 on +44 / +80), both as floats scaled by gp[-32232], x 255 back
// to bytes; the scale track (+96) / 10 x scale (+32) on all three axes, the rotation matrix of the Euler angles +16,
// the position +0; model flags 0x18 set or cleared by the additive byte +144; the animation advanced by +36 (then
// zeroed) and the model drawn (sub_317A20).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34C390(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::Vf, hg::addiu, hg::charge, hg::div_s, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lhu,
          hg::lq, hg::lw, hg::lwc1, hg::mfc1, hg::mtc1, hg::mul_s, hg::pextlb, hg::pextlh, hg::ppacb, hg::ppach,
          hg::qmfc2, hg::qmtc2, hg::sd, hg::sh, hg::sltu, hg::sq, hg::sw, hg::swc1, hg::vftoi0, hg::vitof0,
          hg::vmove, hg::vmul, hg::vmul_bc;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, lifetime{ctx, 16}, age{ctx, 17}, obj{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20};
    Vf vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x0034c390
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x40);
    sq(obj, sp, 0x30);
    sq(age, sp, 0x20);
    sq(lifetime, sp, 0x10);
    swc1(f20, sp, 0x0);
    obj = a0;
    lw(age, a0, k1::kAge);
    lw(lifetime, a0, k1::kLifetime);
    at = sltu(lifetime, age);
    if (at != 0) {
        // 0x0034c3c0: past its lifetime: a lifetime 0 lives forever
        charge(ctx, 2);
        if (lifetime != 0) {
            // 0x0034c57c (the shared epilogue, written out on this path)
            charge(ctx, 8);
            ld(ra, sp, 0x40);
            lq(obj, sp, 0x30);
            lq(age, sp, 0x20);
            lq(lifetime, sp, 0x10);
            lwc1(f20, sp, 0x0);
            sp = addiu(sp, 0xB0);
            return;
        }
    }
    // 0x0034c3c8: colour = base x track (as floats, x 255 back to bytes); scale; rotation; position; flags; draw
    charge(ctx, 90);
    a0 = addiu(obj, k1::kColourTrack);
    a1 = addiu(obj, k1::kColourTrack2);
    a2 = age;
    a3 = lifetime;
    jal(ctx, 0x34C3D8u, gen::fn_sub_32A120_0032a120);
    v1 = v0;
    lw(v0, obj, k1::kColour);
    sw(v0, sp, 0xA8);
    v0 = addiu(sp, 0xA8);
    lwc1(f0, gp, kGpColourUnit);
    lw(v0, v0, 0);
    pextlb(v0, zero, v0);
    pextlh(v0, zero, v0);
    qmtc2(v0, vf10, false);  // qmtc2
    vitof0(0xF, vf10, vf10);  // vitof0.xyzw
    mfc1(v0, f0);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vmove(0xF, vf11, vf10);  // vmove.xyzw
    sw(v1, sp, 0xA4);
    v0 = addiu(sp, 0xA4);
    lw(v0, v0, 0);
    pextlb(v0, zero, v0);
    pextlh(v0, zero, v0);
    qmtc2(v0, vf10, false);  // qmtc2
    vitof0(0xF, vf10, vf10);  // vitof0.xyzw
    mfc1(v0, f0);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
    v0 = mview::flt(255.0f);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
    qmfc2(v0, vf10, false);  // qmfc2
    ppach(v0, zero, v0);
    ppacb(v0, zero, v0);
    sw(v0, sp, 0xA0);
    lw(v0, sp, 0xA0);
    sw(v0, sp, 0xAC);
    lw(a0, obj, k1::kModel);
    a1 = addiu(sp, 0xAC);
    jal(ctx, 0x34C47Cu, gen::fn_sub_318AD0_00318ad0);
    a0 = addiu(obj, k1::kScaleTrack);
    a1 = age;
    a2 = lifetime;
    jal(ctx, 0x34C490u, gen::fn_sub_32A540_0032a540);
    v0 = mview::flt(10.0f);
    mtc1(v0, f1);
    div_s(f20, f0, f1);
    a0 = addiu(sp, 0x50);
    a1 = addiu(obj, k1::kRot);
    jal(ctx, 0x34C4B4u, gen::fn_sub_3296A0_003296a0);
    lw(a0, obj, k1::kModel);
    a1 = addiu(sp, 0x50);
    a2 = 0;
    jal(ctx, 0x34C4C8u, gen::fn_sub_318A70_00318a70);
    lwc1(f0, obj, k1::kScale);
    mul_s(f0, f0, f20);
    swc1(f0, sp, 0x98);
    swc1(f0, sp, 0x94);
    swc1(f0, sp, 0x90);
    lw(a0, obj, k1::kModel);
    a1 = addiu(sp, 0x90);
    a2 = 2;
    jal(ctx, 0x34C4F0u, gen::fn_sub_318A90_00318a90);
    lwc1(f0, obj, k1::kPos);
    swc1(f0, sp, 0x90);
    lwc1(f0, obj, k1::kPos + 4);
    swc1(f0, sp, 0x94);
    lwc1(f0, obj, k1::kPos + 8);
    swc1(f0, sp, 0x98);
    lw(a0, obj, k1::kModel);
    a1 = addiu(sp, 0x90);
    a2 = 2;
    jal(ctx, 0x34C51Cu, gen::fn_sub_318A30_00318a30);
    lbu(v0, obj, k1::kAdditive);
    if (v0 == 0) {
        // 0x0034c548
        charge(ctx, 4);
        lw(v1, obj, k1::kModel);
        lhu(v0, v1, model::kFlags);
        v0 = v0 & 0xFFE7;
        sh(v0, v1, model::kFlags);
    } else {
        // 0x0034c530
        charge(ctx, 6);
        lw(v1, obj, k1::kModel);
        lhu(v0, v1, model::kFlags);
        v0 = v0 | 0x18;
        sh(v0, v1, model::kFlags);
    }
    // 0x0034c558
    charge(ctx, 9);
    lw(a0, obj, k1::kModel);
    a1 = 0;
    lwc1(f12, obj, k1::kAdvance);
    jal(ctx, 0x34C564u, gen::fn_sub_3189F0_003189f0);
    lw(a0, obj, k1::kModel);
    jal(ctx, 0x34C570u, gen::fn_sub_317A20_00317a20);
    sw(zero, obj, k1::kAdvance);
    // 0x0034c57c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(obj, sp, 0x30);
    lq(age, sp, 0x20);
    lq(lifetime, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xB0);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34C390(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(obj));
    sub_34C390(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x0034C5A0 sub_34C5A0 -- 36 bytes; frame 0x10: ra sp+0x0
// sub_34C5A0 [slot 3]: queue the object on its draw layer: sub_3212E0(obj, obj->layer +84).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34C5A0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lhu, hg::sd;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034c5a0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lhu(a1, a0, k1::kLayer);
    jal(ctx, 0x34C5ACu, gen::fn_sub_3212E0_003212e0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34C5A0(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(obj));
    sub_34C5A0(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x0034C5D0 sub_34C5D0 -- 84 bytes; frame 0x10: ra sp+0x0
// sub_34C5D0 [slot 1: update]: the age step, then the draw request.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34C5D0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lw, hg::sd, hg::sltu, hg::sw;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034c5d0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a0, k1::kLifetime);
    lw(v0, a0, k1::kAge);
    at = sltu(v1, v0);
    bool alive = true;
    if (at != 0) {
        // 0x0034c5ec: past its lifetime: a lifetime 0 lives forever
        charge(ctx, 2);
        alive = v1 == 0;
    }
    if (alive) {
        // 0x0034c5f4: the step (sub_34C350 inlined): advance = 1.0, age + 1
        charge(ctx, 5);
        v0 = mview::flt(1.0f);
        sw(v0, a0, k1::kAdvance);
        lw(v0, a0, k1::kAge);
        v0 = addiu(v0, 1);
        sw(v0, a0, k1::kAge);
    }
    // 0x0034c608: queue on the draw layer
    charge(ctx, 7);
    lhu(a1, a0, k1::kLayer);
    jal(ctx, 0x34C60Cu, gen::fn_sub_3212E0_003212e0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34C5D0(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(obj));
    sub_34C5D0(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x0034C630 sub_34C630 -- 16 bytes; leaf frame (no stack)
// sub_34C630 / sub_34C640 [slots 8 / 9] (and kind 2's sub_34D090 / sub_34D0A0): the 16 bytes at a1 into +0 / +16.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34C630(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lq, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0034c630
    enter(ctx, 4);  // entry check point + this block's cycles
    lq(v0, a1, 0);
    sq(v0, a0, k1::kPos);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34C630(EEContext& ctx, u64 obj, u64 v) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(obj));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(v));
    sub_34C630(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x0034C640 sub_34C640 -- 16 bytes; leaf frame (no stack)
// sub_34C630 / sub_34C640 [slots 8 / 9] (and kind 2's sub_34D090 / sub_34D0A0): the 16 bytes at a1 into +0 / +16.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34C640(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lq, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0034c640
    enter(ctx, 4);  // entry check point + this block's cycles
    lq(v0, a1, 0);
    sq(v0, a0, k1::kRot);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34C640(EEContext& ctx, u64 obj, u64 v) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(obj));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(v));
    sub_34C640(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x0034C650 sub_34C650 -- 12 bytes; leaf frame (no stack)
// sub_34C650 [slot 12]: colour word +40.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34C650(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::sw;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x0034c650
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(a1, a0, k1::kColour);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34C650(EEContext& ctx, u64 obj, u64 rgba) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(obj));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(rgba));
    sub_34C650(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}
u64 sub_34C660(EEContext& ctx, u64 obj) { return run(ctx, &Cpu::sub_34C660, obj); }
u64 sub_34C940(EEContext& ctx, u64 obj) { return run(ctx, &Cpu::sub_34C940, obj); }
// 0x0034CB60 sub_34CB60 -- 148 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_34CB60 [slot 7: reset]: when the nodes are live (+156), release every frame's node (sub_325B80 over the +40
// pointers at +152); then the model's track 0 back to time 0 and the age (+44) to 0.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34CB60(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw,
          hg::mtc1, hg::sd, hg::sltu, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, frames{ctx, 16}, i{ctx, 17}, node{ctx, 18}, obj{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x0034cb60
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(obj, sp, 0x30);
    sq(node, sp, 0x20);
    sq(i, sp, 0x10);
    sq(frames, sp, 0x0);
    obj = a0;
    lw(v0, a0, k2::kNodeMode);
    if (v0 != 0) {
        // 0x0034cb88
        charge(ctx, 5);
        lw(frames, obj, k2::kFrames);
        lw(node, obj, k2::kNodes);
        i = 0;
        for (;;) {
            // 0x0034cbb0
            charge(ctx, 3);
            v0 = sltu(i, frames);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0034cb9c
            charge(ctx, 5);
            lw(a0, node, 0);
            jal(ctx, 0x34CBA0u, gen::fn_sub_325B80_00325b80);
            node = addiu(node, 4);
            i = addiu(i, 1);
        }
    }
    // 0x0034cbbc
    charge(ctx, 14);
    mtc1(zero, f12);
    lw(a0, obj, k2::kModel);
    a1 = 0;
    jal(ctx, 0x34CBC8u, gen::fn_sub_318770_00318770);
    sw(zero, obj, k2::kAge);
    ld(ra, sp, 0x40);
    lq(obj, sp, 0x30);
    lq(node, sp, 0x20);
    lq(i, sp, 0x10);
    lq(frames, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34CB60(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(obj));
    sub_34CB60(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x0034CC00 sub_34CC00 -- 808 bytes; frame 0x140: ra sp+0x70, s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// sub_34CC00 [slot 2: step]: while alive (age +44 < lifetime +144, or lifetime 0): place the model (+160), advance
// its animation by +148 and update its frames (sub_317730); when the nodes are live (+156): the colour = colour
// (+36) x the track colour (+48 / +84) as floats scaled by gp[-32420], x 255; the node scale = scale track (+100) /
// 10 x scale (+32); then for each frame (+40) whose matrix the model has (sub_318D10 into sp+192): the frame's node
// (+152 array) gets the frame position, the frame's rotation (sub_329ED0 of the matrix rows, w = 0), the scale and
// colour, and is drawn (sub_3252A0). The age grows by one either way.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34CC00(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::Vf, hg::addiu, hg::backedge, hg::charge, hg::div_s, hg::enter, hg::jal, hg::ld,
          hg::lq, hg::lw, hg::lwc1, hg::mfc1, hg::mov_s, hg::mtc1, hg::mul_s, hg::pextlb, hg::pextlh, hg::ppacb,
          hg::ppach, hg::qmfc2, hg::qmtc2, hg::sd, hg::slt, hg::sltu, hg::sq, hg::sqc2, hg::sw, hg::swc1, hg::vftoi0,
          hg::vitof0, hg::vmove, hg::vmul, hg::vmul_bc;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, age{ctx, 17}, node{ctx, 18}, obj{ctx, 19}, frames{ctx, 20}, colour{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21};
    Vf vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x0034cc00
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x140);
    sd(ra, sp, 0x70);
    sq(colour, sp, 0x60);
    sq(frames, sp, 0x50);
    sq(obj, sp, 0x40);
    sq(node, sp, 0x30);
    sq(age, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    obj = a0;
    lw(age, a0, k2::kAge);
    lw(s0, a0, k2::kLifetime);
    lw(frames, a0, k2::kFrames);
    lw(node, a0, k2::kNodes);
    v1 = slt(age, s0);
    if (v1 == 0) {
        // 0x0034cc48: past its lifetime: a lifetime 0 lives forever (the age still grows)
        charge(ctx, 2);
        if (s0 != 0) {
            // 0x0034ceec (the shared epilogue, written out on this path)
            charge(ctx, 15);
            lw(v1, obj, k2::kAge);
            v1 = addiu(v1, 1);
            sw(v1, obj, k2::kAge);
            ld(ra, sp, 0x70);
            lq(colour, sp, 0x60);
            lq(frames, sp, 0x50);
            lq(obj, sp, 0x40);
            lq(node, sp, 0x30);
            lq(age, sp, 0x20);
            lq(s0, sp, 0x10);
            lwc1(f21, sp, 0x4);
            lwc1(f20, sp, 0x0);
            sp = addiu(sp, 0x140);
            return;
        }
    }
    // 0x0034cc50: place the model (rotation, scale, position), advance and update its frames
    charge(ctx, 40);
    a0 = addiu(sp, 0xC0);
    a1 = addiu(obj, k2::kRot);
    jal(ctx, 0x34CC58u, gen::fn_sub_3296A0_003296a0);
    lw(a0, obj, k2::kModel);
    a1 = addiu(sp, 0xC0);
    a2 = 0;
    jal(ctx, 0x34CC6Cu, gen::fn_sub_318A70_00318a70);
    lwc1(f0, obj, k2::kScale);
    swc1(f0, sp, 0x130);
    swc1(f0, sp, 0x12C);
    swc1(f0, sp, 0x128);
    lw(a0, obj, k2::kModel);
    a1 = addiu(sp, 0x128);
    a2 = 2;
    jal(ctx, 0x34CC90u, gen::fn_sub_318A90_00318a90);
    lwc1(f0, obj, k2::kPos);
    swc1(f0, sp, 0x128);
    lwc1(f0, obj, k2::kPos + 4);
    swc1(f0, sp, 0x12C);
    lwc1(f0, obj, k2::kPos + 8);
    swc1(f0, sp, 0x130);
    lw(a0, obj, k2::kModel);
    a1 = addiu(sp, 0x128);
    a2 = 2;
    jal(ctx, 0x34CCBCu, gen::fn_sub_318A30_00318a30);
    lw(a0, obj, k2::kModel);
    a1 = 0;
    lwc1(f12, obj, k2::kAdvance);
    jal(ctx, 0x34CCD0u, gen::fn_sub_3189F0_003189f0);
    lw(a0, obj, k2::kModel);
    jal(ctx, 0x34CCDCu, gen::fn_sub_317730_00317730);
    lw(v1, obj, k2::kNodeMode);
    if (v1 != 0) {
        // 0x0034ccf0
        charge(ctx, 57);
        a0 = addiu(obj, k2::kColourTrack);
        a1 = addiu(obj, k2::kColourTrack2);
        a2 = age;
        a3 = s0;
        jal(ctx, 0x34CD00u, gen::fn_sub_32A120_0032a120);
        v1 = v0;
        lw(v0, obj, k2::kColour);
        sw(v0, sp, 0x13C);
        v0 = addiu(sp, 0x13C);
        lwc1(f0, gp, kGpColourUnit2);
        lw(v0, v0, 0);
        pextlb(v0, zero, v0);
        pextlh(v0, zero, v0);
        qmtc2(v0, vf10, false);  // qmtc2
        vitof0(0xF, vf10, vf10);  // vitof0.xyzw
        mfc1(v0, f0);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        vmove(0xF, vf11, vf10);  // vmove.xyzw
        sw(v1, sp, 0x138);
        v0 = addiu(sp, 0x138);
        lw(v0, v0, 0);
        pextlb(v0, zero, v0);
        pextlh(v0, zero, v0);
        qmtc2(v0, vf10, false);  // qmtc2
        vitof0(0xF, vf10, vf10);  // vitof0.xyzw
        mfc1(v0, f0);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
        v0 = mview::flt(255.0f);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
        qmfc2(v0, vf10, false);  // qmfc2
        ppach(v0, zero, v0);
        ppacb(v0, zero, v0);
        sw(v0, sp, 0x134);
        lw(colour, sp, 0x134);
        a0 = addiu(obj, k2::kScaleTrack);
        a1 = age;
        a2 = s0;
        jal(ctx, 0x34CDA4u, gen::fn_sub_32A540_0032a540);
        v1 = mview::flt(10.0f);
        mtc1(v1, f1);
        div_s(f1, f0, f1);
        lwc1(f0, obj, k2::kScale);
        mul_s(f21, f1, f0);
        s0 = 0;
        mtc1(zero, f20);
        for (;;) {
            // 0x0034cee0
            charge(ctx, 3);
            v1 = sltu(s0, frames);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0034cdd4
            charge(ctx, 7);
            lw(a0, obj, k2::kModel);
            a1 = s0;
            a2 = addiu(sp, 0xC0);
            jal(ctx, 0x34CDE0u, gen::fn_sub_318D10_00318d10);
            if (v0 != 0) {
                // 0x0034cdf0
                charge(ctx, 58);
                lwc1(f0, sp, 0xF0);
                swc1(f0, sp, 0x110);
                lwc1(f0, sp, 0xF4);
                swc1(f0, sp, 0x114);
                lwc1(f0, sp, 0xF8);
                swc1(f0, sp, 0x118);
                swc1(f20, sp, 0x11C);
                lw(a0, node, 0);
                a1 = addiu(sp, 0x110);
                jal(ctx, 0x34CE14u, gen::fn_sub_325C10_00325c10);
                lwc1(f0, sp, 0xC0);
                swc1(f0, sp, 0x80);
                lwc1(f0, sp, 0xC4);
                swc1(f0, sp, 0x84);
                lwc1(f0, sp, 0xC8);
                swc1(f0, sp, 0x88);
                swc1(f20, sp, 0x8C);
                lwc1(f0, sp, 0xD0);
                swc1(f0, sp, 0x90);
                lwc1(f0, sp, 0xD4);
                swc1(f0, sp, 0x94);
                lwc1(f0, sp, 0xD8);
                swc1(f0, sp, 0x98);
                swc1(f20, sp, 0x9C);
                lwc1(f0, sp, 0xE0);
                swc1(f0, sp, 0xA0);
                lwc1(f0, sp, 0xE4);
                swc1(f0, sp, 0xA4);
                lwc1(f0, sp, 0xE8);
                swc1(f0, sp, 0xA8);
                swc1(f20, sp, 0xAC);
                lwc1(f0, sp, 0xF0);
                swc1(f0, sp, 0xB0);
                lwc1(f0, sp, 0xF4);
                swc1(f0, sp, 0xB4);
                lwc1(f0, sp, 0xF8);
                swc1(f0, sp, 0xB8);
                swc1(f20, sp, 0xBC);
                a0 = addiu(sp, 0x80);
                jal(ctx, 0x34CE90u, gen::fn_sub_329ED0_00329ed0);
                a1 = addiu(sp, 0x100);
                sqc2(vf10, a1, 0);
                lw(a0, node, 0);
                jal(ctx, 0x34CEA4u, gen::fn_sub_325D60_00325d60);
                lw(a0, node, 0);
                mov_s(f12, f21);
                jal(ctx, 0x34CEB4u, gen::fn_sub_325E40_00325e40);
                lw(a0, node, 0);
                a1 = colour;
                jal(ctx, 0x34CEC4u, gen::fn_sub_326030_00326030);
                lw(a0, node, 0);
                jal(ctx, 0x34CED0u, gen::fn_sub_3252A0_003252a0);
            }
            // 0x0034ced8
            charge(ctx, 2);
            s0 = addiu(s0, 1);
            node = addiu(node, 4);
        }
    }
    // 0x0034ceec (the shared epilogue, written out on this path)
    charge(ctx, 15);
    lw(v1, obj, k2::kAge);
    v1 = addiu(v1, 1);
    sw(v1, obj, k2::kAge);
    ld(ra, sp, 0x70);
    lq(colour, sp, 0x60);
    lq(frames, sp, 0x50);
    lq(obj, sp, 0x40);
    lq(node, sp, 0x30);
    lq(age, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x140);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34CC00(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(obj));
    sub_34CC00(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x0034CF30 sub_34CF30 -- 284 bytes; frame 0x90: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_34CF30 [slot 3: draw]: with the nodes off (+156 = 0), a debug gizmo per frame the model has (sub_358A30 in
// yellow 255,255,0,255 of size 4.0 at sp+112, frame axes sub_359380 of length 30.0); with the nodes on and while
// alive, each frame's node drawn on its layer (sub_325500).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34CF30(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw,
          hg::mtc1, hg::sb, hg::sd, hg::slt, hg::sltu, hg::sq;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x0034cf30
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v1, a0, k2::kNodeMode);
    if (v1 != 0) {
        // 0x0034cfe0
        charge(ctx, 7);
        lw(a0, s1, k2::kLifetime);
        lw(s2, s1, k2::kFrames);
        lw(s0, s1, k2::kNodes);
        lw(v1, s1, k2::kAge);
        v1 = slt(v1, a0);
        if (v1 == 0) {
            // 0x0034cffc: past its lifetime: a lifetime 0 lives forever
            charge(ctx, 2);
            if (a0 != 0) {
                // 0x0034d030 (the shared epilogue, written out on this path)
                charge(ctx, 7);
                ld(ra, sp, 0x30);
                lq(s2, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x90);
                return;
            }
        }
        // 0x0034d004: draw each frame's node on its layer
        charge(ctx, 3);
        s1 = 0;
        for (;;) {
            // 0x0034d024
            charge(ctx, 3);
            v1 = sltu(s1, s2);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0034d010
            charge(ctx, 5);
            lw(a0, s0, 0);
            jal(ctx, 0x34D014u, gen::fn_sub_325500_00325500);
            s0 = addiu(s0, 4);
            s1 = addiu(s1, 1);
        }
    } else {
        // 0x0034cf54
        charge(ctx, 8);
        v1 = 255;
        sb(v1, sp, 0x8C);
        sb(v1, sp, 0x8D);
        sb(zero, sp, 0x8E);
        sb(v1, sp, 0x8F);
        s0 = 0;
        for (;;) {
            // 0x0034cfc8
            charge(ctx, 4);
            lw(v1, s1, k2::kFrames);
            v1 = sltu(s0, v1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0034cf74
            charge(ctx, 7);
            lw(a0, s1, k2::kModel);
            a1 = s0;
            a2 = addiu(sp, 0x40);
            jal(ctx, 0x34CF80u, gen::fn_sub_318D10_00318d10);
            if (v0 != 0) {
                // 0x0034cf90
                charge(ctx, 13);
                v0 = mview::flt(4.0f);
                mtc1(v0, f12);
                a0 = addiu(sp, 0x70);
                a1 = addiu(sp, 0x8C);
                a2 = 1;
                jal(ctx, 0x34CFA4u, gen::fn_sub_358A30_00358a30);
                v0 = mview::flt(30.0f);
                mtc1(v0, f12);
                a0 = addiu(sp, 0x40);
                a1 = 1;
                jal(ctx, 0x34CFBCu, gen::fn_sub_359380_00359380);
            }
            // 0x0034cfc4
            charge(ctx, 1);
            s0 = addiu(s0, 1);
        }
        // 0x0034cfd8
        charge(ctx, 2);
    }
    // 0x0034d030 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34CF30(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(obj));
    sub_34CF30(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}
u64 sub_34D050(EEContext& ctx, u64 obj) { return run(ctx, &Cpu::sub_34D050, obj); }
// 0x0034D090 sub_34D090 -- 16 bytes; leaf frame (no stack)
// sub_34C630 / sub_34C640 [slots 8 / 9] (and kind 2's sub_34D090 / sub_34D0A0): the 16 bytes at a1 into +0 / +16.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34D090(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lq, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0034d090
    enter(ctx, 4);  // entry check point + this block's cycles
    lq(v0, a1, 0);
    sq(v0, a0, k2::kPos);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34D090(EEContext& ctx, u64 obj, u64 v) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(obj));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(v));
    sub_34D090(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x0034D0A0 sub_34D0A0 -- 16 bytes; leaf frame (no stack)
// sub_34C630 / sub_34C640 [slots 8 / 9] (and kind 2's sub_34D090 / sub_34D0A0): the 16 bytes at a1 into +0 / +16.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34D0A0(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lq, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0034d0a0
    enter(ctx, 4);  // entry check point + this block's cycles
    lq(v0, a1, 0);
    sq(v0, a0, k2::kRot);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34D0A0(EEContext& ctx, u64 obj, u64 v) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(obj));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(v));
    sub_34D0A0(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x0034D0B0 sub_34D0B0 -- 12 bytes; leaf frame (no stack)
// sub_34D0B0 [slot 12]: colour word +36.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34D0B0(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::sw;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x0034d0b0
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(a1, a0, k2::kColour);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34D0B0(EEContext& ctx, u64 obj, u64 rgba) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(obj));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(rgba));
    sub_34D0B0(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}
u64 sub_34D0C0(EEContext& ctx, u64 obj) { return run(ctx, &Cpu::sub_34D0C0, obj); }
// 0x0034D0D0 sub_34D0D0 -- 96 bytes; leaf frame (no stack)
// sub_34D0D0 [RpClumpForAllAtomics callback] (a0 atomic, a1 RGBA bytes): every material of the atomic's geometry
// (+24; material pointers +32, count +36) gets the colour (material +4..+7). Returns the atomic.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34D0D0(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lbu, hg::lw, hg::sb, hg::sll,
          hg::slt;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, material{ctx, 8}, count{ctx, 9}, geometry{ctx, 10}, i{ctx, 11};
    // 0x0034d0d0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(geometry, a0, kAtomicGeometry);
    lw(count, geometry, geom::kMaterialCount);
    i = 0;
    for (;;) {
        // 0x0034d118
        charge(ctx, 3);
        v0 = slt(i, count);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0034d0e4
        charge(ctx, 13);
        v1 = sll(i, 2);
        lw(v0, geometry, geom::kMaterials);
        v0 = addu(v0, v1);
        lw(material, v0, 0);
        lbu(a3, a1, 0);
        lbu(a2, a1, 1);
        lbu(v1, a1, 2);
        lbu(v0, a1, 3);
        sb(a3, material, kMaterialColour);
        sb(a2, material, kMaterialColour + 1);
        sb(v1, material, kMaterialColour + 2);
        sb(v0, material, kMaterialColour + 3);
        i = addiu(i, 1);
    }
    // 0x0034d124
    charge(ctx, 3);
    v0 = a0;
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34D0D0(EEContext& ctx, u64 atomic, u64 rgba) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(atomic));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(rgba));
    sub_34D0D0(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x0034D130 sub_34D130 -- 28 bytes; leaf frame (no stack)
// sub_34D130 [RpClumpForAllAtomics callback]: the atomic's geometry flags (+8) |= 0x40 (material colours modulate).
// Returns the atomic.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34D130(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0034d130
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(v1, a0, kAtomicGeometry);
    lw(v0, v1, geom::kFlags);
    v0 = v0 | 0x40;
    sw(v0, v1, geom::kFlags);
    v0 = a0;
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34D130(EEContext& ctx, u64 atomic) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(atomic));
    sub_34D130(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x0034D150 sub_34D150 -- 588 bytes; frame 0x50: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// sub_34D150 [emit one particle] (a0 the object's emitter parameters, a1 its 24-byte record): the direction (+0..+8)
// is the fixed one (+20..+28) when +16 is 0, else three random lanes 2 * (rand - 0.5); normalised on VU0 (rsqrt of
// the squared length), or (0, 1, 0) when its length is 0. Speed (+16) = +36 x spread(+40), spin (+12) = rand x
// gp[-32416]; the colour phase (+20): mode +52 = 2 -> (record index) % 6, 1 -> effMiscRand % 6, else -1.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34D150(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::Vf, hg::adda_s, hg::addiu, hg::c_eq_s, hg::cfc2, hg::charge, hg::cond, hg::divu,
          hg::enter, hg::jal, hg::lbu, hg::ld, hg::lq, hg::lqc2, hg::lw, hg::lwc1, hg::madd_s, hg::mfhi, hg::mflo,
          hg::mtc1, hg::mul_s, hg::sb, hg::sd, hg::si, hg::sq, hg::sqc2, hg::sub_s, hg::subu, hg::sw, hg::swc1,
          hg::vadd_bc, hg::vmadd_bc, hg::vmadda_bc, hg::vmul, hg::vmula_bc, hg::vmulq, hg::vrsqrt, hg::vsqrt,
          hg::vwaitq;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, rec{ctx, 16}, obj{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f20{ctx, 20};
    Vf vf0{ctx, 0}, vf2{ctx, 2}, vf10{ctx, 10};
    // 0x0034d150
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(obj, sp, 0x20);
    sq(rec, sp, 0x10);
    swc1(f20, sp, 0x0);
    obj = a0;
    rec = a1;
    lbu(v0, a0, k3::kRandomDir);
    if (v0 != 0) {
        // 0x0034d198
        charge(ctx, 36);
        a0 = 0;
        jal(ctx, 0x34D19Cu, gen::fn_sub_358030_00358030);
        v0 = mview::flt(0.5f);
        mtc1(v0, f1);
        sub_s(f1, f0, f1);
        v0 = mview::flt(2.0f);
        mtc1(v0, f0);
        mul_s(f0, f0, f1);
        swc1(f0, sp, 0x40);
        a0 = 0;
        jal(ctx, 0x34D1CCu, gen::fn_sub_358030_00358030);
        v0 = mview::flt(0.5f);
        mtc1(v0, f1);
        sub_s(f1, f0, f1);
        v0 = mview::flt(2.0f);
        mtc1(v0, f0);
        mul_s(f0, f0, f1);
        swc1(f0, sp, 0x44);
        a0 = 0;
        jal(ctx, 0x34D1FCu, gen::fn_sub_358030_00358030);
        v0 = mview::flt(0.5f);
        mtc1(v0, f1);
        sub_s(f1, f0, f1);
        v0 = mview::flt(2.0f);
        mtc1(v0, f0);
        mul_s(f0, f0, f1);
        swc1(f0, sp, 0x48);
    } else {
        // 0x0034d178
        charge(ctx, 8);
        lwc1(f0, obj, k3::kDir);
        swc1(f0, sp, 0x40);
        lwc1(f0, obj, k3::kDir + 4);
        swc1(f0, sp, 0x44);
        lwc1(f0, obj, k3::kDir + 8);
        swc1(f0, sp, 0x48);
    }
    // 0x0034d228
    charge(ctx, 14);
    v1 = addiu(sp, 0x40);
    lqc2(vf10, v1, 0);
    vmul(0xE, vf2, vf10, vf10);  // vmul.xyz
    vadd_bc(0x8, vf2, vf2, vf2, 1);  // vaddy.x
    vadd_bc(0x8, vf2, vf2, vf2, 2);  // vaddz.x
    vsqrt(vf2, 0);  // vsqrt
    vwaitq(ctx);
    cfc2(v0, 22, false);  // cfc2
    mtc1(v0, f1);
    mtc1(zero, f0);
    c_eq_s(f0, f1);
    if (cond(ctx)) {
        // 0x0034d2a0
        charge(ctx, 4);
        swc1(f0, rec, rec3::kDir);
        v0 = mview::flt(1.0f);
        sw(v0, rec, rec3::kDir + 4);
        swc1(f0, rec, rec3::kDir + 8);
    } else {
        // 0x0034d260
        charge(ctx, 16);
        vmul(0xE, vf2, vf10, vf10);  // vmul.xyz
        vmula_bc(0x1, vf0, vf2, 0);  // vmulax.w
        vmadda_bc(0x1, vf0, vf2, 1);  // vmadday.w
        vmadd_bc(0x1, vf2, vf0, vf2, 2);  // vmaddz.w
        vrsqrt(vf0, 3, vf2, 3);  // vrsqrt
        vwaitq(ctx);
        vmulq(0xE, vf10, vf10);  // vmulq.xyz
        sqc2(vf10, v1, 0);
        lwc1(f0, sp, 0x40);
        swc1(f0, rec, rec3::kDir);
        lwc1(f0, sp, 0x44);
        swc1(f0, rec, rec3::kDir + 4);
        lwc1(f0, sp, 0x48);
        swc1(f0, rec, rec3::kDir + 8);
    }
    // 0x0034d2b0
    charge(ctx, 25);
    lwc1(f20, obj, k3::kSpread);
    a0 = 0;
    jal(ctx, 0x34D2B8u, gen::fn_sub_358030_00358030);
    v0 = mview::flt(1.0f);
    mtc1(v0, f1);
    sub_s(f2, f1, f20);
    mtc1(zero, f1);
    adda_s(f1, f2);
    madd_s(f1, f20, f0);
    lwc1(f0, obj, k3::kSpeed);
    mul_s(f0, f0, f1);
    swc1(f0, rec, rec3::kSpeed);
    a0 = 0;
    jal(ctx, 0x34D2F0u, gen::fn_sub_358030_00358030);
    lwc1(f1, gp, kGpPhaseRange);
    mul_s(f0, f1, f0);
    swc1(f0, rec, rec3::kSpin);
    lw(a0, obj, k3::kPhaseMode);
    v1 = 2;
    if (a0 == v1) {
        // 0x0034d34c
        charge(ctx, 11);
        lw(v1, obj, k3::kRecords);
        a0 = subu(rec, v1);
        v1 = rec3::kSize;
        divu(a0, v1);
        mflo(a0);
        v1 = kColourKeys;
        divu(a0, v1);
        mfhi(v1);
        sb(v1, rec, rec3::kPhase);
    } else {
        // 0x0034d314
        charge(ctx, 3);
        v1 = 1;
        if (a0 == v1) {
            // 0x0034d328
            charge(ctx, 9);
            a0 = 0;
            jal(ctx, 0x34D32Cu, gen::fn_sub_357FD0_00357fd0);
            v1 = kColourKeys;
            divu(v0, v1);
            mfhi(v1);
            sb(v1, rec, rec3::kPhase);
        } else {
            // 0x0034d320
            charge(ctx, 2);
            // 0x0034d378
            charge(ctx, 2);
            v1 = si(-1);
            sb(v1, rec, rec3::kPhase);
        }
    }
    // 0x0034d380 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(obj, sp, 0x20);
    lq(rec, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34D150(EEContext& ctx, u64 obj, u64 rec) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(obj));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(rec));
    sub_34D150(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x0034D3A0 sub_34D3A0 -- 364 bytes; frame 0x10
// sub_34D3A0 [the colour of a record at `time`] (a0 parameters, a1 record, a2 time; $vf10 in and out, a 16-byte
// frame for the word -> vector moves): six colour keys at +60; the key length is +56 / 6 frames. With a positive key
// length the colour lerps from key (phase + time / len) % 6 to the next one by (time % len) / len; otherwise it is
// key `phase`. Keys are scaled by gp[-32232]; $vf10 is multiplied by the colour.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34D3A0(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::Vf, hg::addiu, hg::addu, hg::charge, hg::cvt_s_w, hg::div, hg::div_s, hg::enter,
          hg::i64, hg::lb, hg::lw, hg::lwc1, hg::mfc1, hg::mfhi, hg::mflo, hg::mtc1, hg::pextlb, hg::pextlh,
          hg::qmtc2, hg::sll, hg::sub_s, hg::sw, hg::vadd, hg::vitof0, hg::vmove, hg::vmul, hg::vmul_bc;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    Vf vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11}, vf12{ctx, 12};
    // 0x0034d3a0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    lw(v0, a0, k3::kKeyLength);
    t0 = kColourKeys;
    div(v0, t0);
    mflo(a3);
    if (i64(a3) <= 0) {
        // 0x0034d4c0
        charge(ctx, 16);
        lb(v0, a1, rec3::kPhase);
        v0 = sll(v0, 2);
        v0 = addu(v0, a0);
        lw(v0, v0, k3::kKeys);
        sw(v0, sp, 0x4);
        v0 = addiu(sp, 0x4);
        lw(v1, gp, kGpColourUnit);
        lw(v0, v0, 0);
        pextlb(v0, zero, v0);
        pextlh(v0, zero, v0);
        qmtc2(v0, vf11, false);  // qmtc2
        vitof0(0xF, vf11, vf11);  // vitof0.xyzw
        qmtc2(v1, vf2, false);  // qmtc2
        vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
        vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
    } else {
        // 0x0034d3bc
        charge(ctx, 65);
        vmove(0xF, vf12, vf10);  // vmove.xyzw
        div(a2, a3);
        mflo(v1);
        div(a2, a3);
        mfhi(v0);
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        mtc1(a3, f0);
        cvt_s_w(f0, f0);
        div_s(f1, f1, f0);
        lb(v0, a1, rec3::kPhase);
        v0 = addu(v0, v1);
        div(v0, t0);
        mfhi(v1);
        v0 = addiu(v1, 1);
        div(v0, t0);
        mfhi(v0);
        v0 = sll(v0, 2);
        v0 = addu(v0, a0);
        lw(v0, v0, k3::kKeys);
        sw(v0, sp, 0xC);
        v0 = addiu(sp, 0xC);
        lwc1(f0, gp, kGpColourUnit);
        lw(v0, v0, 0);
        pextlb(v0, zero, v0);
        pextlh(v0, zero, v0);
        qmtc2(v0, vf11, false);  // qmtc2
        vitof0(0xF, vf11, vf11);  // vitof0.xyzw
        mfc1(v0, f0);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
        v0 = sll(v1, 2);
        v0 = addu(v0, a0);
        lw(v0, v0, k3::kKeys);
        sw(v0, sp, 0x8);
        v0 = addiu(sp, 0x8);
        lw(v0, v0, 0);
        pextlb(v0, zero, v0);
        pextlh(v0, zero, v0);
        qmtc2(v0, vf10, false);  // qmtc2
        vitof0(0xF, vf10, vf10);  // vitof0.xyzw
        mfc1(v1, f0);
        qmtc2(v1, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        v1 = mview::flt(1.0f);
        mtc1(v1, f0);
        sub_s(f0, f0, f1);
        mfc1(v1, f0);
        qmtc2(v1, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        mfc1(v1, f1);
        qmtc2(v1, vf2, false);  // qmtc2
        vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
        vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
        vmove(0xF, vf11, vf12);  // vmove.xyzw
        vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
    }
    // 0x0034d500 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    sp = addiu(sp, 0x10);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34D3A0(EEContext& ctx, u64 obj, u64 rec, u64 time) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(obj));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(rec));
    ee::core::set_gpr64(ctx, GPR_A2, static_cast<u64>(time));
    sub_34D3A0(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x0034D810 sub_34D810 -- 140 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_34D810 [slot 6: copy] (a0 dst, a1 src): when src's kind word (+12) is 3, dst's clump (+84) is destroyed (when
// it has one) and replaced by a clone of src's, whose atomics get the modulate flag (sub_4916D0(clone, sub_34D130,
// 0)); the kind word is copied either way.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34D810(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lq, hg::lw, hg::sd, hg::sh,
          hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, src{ctx, 16}, dst{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034d810
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(dst, sp, 0x10);
    sq(src, sp, 0x0);
    dst = a0;
    src = a1;
    lhu(a0, a1, k3::kKindWord);
    v1 = 3;
    if (a0 == v1) {
        // 0x0034d840
        charge(ctx, 3);
        lw(a0, dst, k3::kClump);
        if (a0 != 0) {
            // 0x0034d84c
            charge(ctx, 2);
            jal(ctx, 0x34D84Cu, gen::fn_sub_491EA0_00491ea0);
        }
        // 0x0034d854
        charge(ctx, 10);
        lw(a0, src, k3::kClump);
        jal(ctx, 0x34D858u, gen::fn_sub_491CC0_00491cc0);
        sw(v0, dst, k3::kClump);
        a0 = v0;
        mview::la(a1, kFnModulateAtomic);  // &sub_34D130
        a2 = 0;
        jal(ctx, 0x34D874u, gen::fn_sub_4916D0_004916d0);
    } else {
        // 0x0034d838
        charge(ctx, 2);
    }
    // 0x0034d87c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lhu(v1, src, k3::kKindWord);
    sh(v1, dst, k3::kKindWord);
    ld(ra, sp, 0x20);
    lq(dst, sp, 0x10);
    lq(src, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34D810(EEContext& ctx, u64 dst, u64 src) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(dst));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(src));
    sub_34D810(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x0034D990 sub_34D990 -- 360 bytes; frame 0x80: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_34D990 [load the clump of a memory stream] (a0 object, a1 data, a2 size): opens a memory stream over {data,
// size} (sub_4C58A0(3, 1, sp+112)) and walks its chunk headers (sub_4C1970 into sp+80: type, length): the first
// chunk 0x10 is read as the clump, the first 0x16 as a texture dictionary (walked with sub_1A13B0 collecting into
// sp+124, then released by sub_4D0D10), any other chunk is skipped; a type 0 ends the walk. After the close, the
// collected texture (sp+124) goes through sub_1A14C0; the clump is stored at +84 and its atomics get the modulate
// flag.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34D990(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq,
          hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, texdict{ctx, 16}, clump{ctx, 17}, stream{ctx, 18}, obj{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034d990
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x40);
    sq(obj, sp, 0x30);
    sq(stream, sp, 0x20);
    sq(clump, sp, 0x10);
    sq(texdict, sp, 0x0);
    obj = a0;
    clump = 0;
    texdict = 0;
    sw(zero, sp, 0x7C);
    sw(a1, sp, 0x70);
    sw(a2, sp, 0x74);
    a0 = 3;
    a1 = 1;
    a2 = addiu(sp, 0x70);
    jal(ctx, 0x34D9CCu, gen::fn_sub_4C58A0_004c58a0);
    stream = v0;
    for (;;) {
        // 0x0034da80
        charge(ctx, 6);
        a0 = stream;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x34DA88u, gen::fn_sub_4C1970_004c1970);
        if (v0 != 0) {
            backedge(ctx);
            // 0x0034d9e0
            charge(ctx, 3);
            lw(v1, sp, 0x50);
            if (v1 != 0) {
                // 0x0034d9ec
                charge(ctx, 3);
                v0 = kChunkClump;
                if (v1 == v0) {
                    // 0x0034da50
                    charge(ctx, 2);
                    if (clump == 0) {
                        // 0x0034da58
                        charge(ctx, 6);
                        a0 = stream;
                        jal(ctx, 0x34DA5Cu, gen::fn_sub_4920A0_004920a0);
                        clump = v0;
                    }
                } else {
                    // 0x0034d9f8
                    charge(ctx, 3);
                    v0 = kChunkTexDict;
                    if (v1 == v0) {
                        // 0x0034da0c
                        charge(ctx, 2);
                        if (texdict == 0) {
                            // 0x0034da14
                            charge(ctx, 15);
                            a0 = stream;
                            jal(ctx, 0x34DA18u, gen::fn_sub_4C8680_004c8680);
                            texdict = v0;
                            a0 = texdict;
                            mview::la(a1, kFnCollectTexture);  // &sub_1A13B0
                            a2 = addiu(sp, 0x7C);
                            jal(ctx, 0x34DA34u, gen::fn_sub_4D0DC0_004d0dc0);
                            a0 = texdict;
                            jal(ctx, 0x34DA40u, gen::fn_sub_4D0D10_004d0d10);
                        }
                    } else {
                        // 0x0034da04
                        charge(ctx, 2);
                        // 0x0034da70
                        charge(ctx, 4);
                        a0 = stream;
                        lw(a1, sp, 0x54);
                        jal(ctx, 0x34DA78u, gen::fn_sub_4C5620_004c5620);
                    }
                }
                continue;
            }
        }
        break;
    }
    // 0x0034da98
    charge(ctx, 7);
    a0 = stream;
    a1 = addiu(sp, 0x70);
    jal(ctx, 0x34DAA0u, gen::fn_sub_4C5780_004c5780);
    lw(a0, sp, 0x7C);
    if (a0 != 0) {
        // 0x0034dab4
        charge(ctx, 2);
        jal(ctx, 0x34DAB4u, gen::fn_sub_1A14C0_001a14c0);
    }
    // 0x0034dabc
    charge(ctx, 15);
    sw(clump, obj, k3::kClump);
    a0 = clump;
    mview::la(a1, kFnModulateAtomic);  // &sub_34D130
    a2 = 0;
    jal(ctx, 0x34DAD0u, gen::fn_sub_4916D0_004916d0);
    ld(ra, sp, 0x40);
    lq(obj, sp, 0x30);
    lq(stream, sp, 0x20);
    lq(clump, sp, 0x10);
    lq(texdict, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34D990(EEContext& ctx, u64 obj, u64 data, u64 size) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(obj));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(data));
    ee::core::set_gpr64(ctx, GPR_A2, static_cast<u64>(size));
    sub_34D990(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x0034DB00 sub_34DB00 -- 44 bytes; frame 0x10: ra sp+0x0
// sub_34DB00 [slot 7: reset]: sub_332200(system +88) when there is one.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34DB00(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lw, hg::sd;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034db00
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, k3::kSystem);
    if (a0 != 0) {
        // 0x0034db14
        charge(ctx, 2);
        jal(ctx, 0x34DB14u, gen::fn_sub_332200_00332200);
    }
    // 0x0034db1c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34DB00(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(obj));
    sub_34DB00(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x0034DB30 sub_34DB30 -- 204 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_34DB30 [slot 2: step]: steps the system (+88, sub_332210); when it has particles (count +8, records +24 of 32
// bytes, a non-null +16) and the object's kind word (+12) is 3, every particle whose system record +16 is 0 (just
// born) is emitted into its 24-byte record (+92 array) by sub_34D150.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34DB30(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lq, hg::lw, hg::sd,
          hg::slt, hg::sq;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, count{ctx, 16}, rec{ctx, 17}, sysrec{ctx, 18}, obj{ctx, 19}, i{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034db30
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(i, sp, 0x40);
    sq(obj, sp, 0x30);
    sq(sysrec, sp, 0x20);
    sq(rec, sp, 0x10);
    sq(count, sp, 0x0);
    obj = a0;
    lw(a0, a0, k3::kSystem);
    jal(ctx, 0x34DB54u, gen::fn_sub_332210_00332210);
    lw(a0, obj, k3::kSystem);
    lw(count, a0, psys::kCount);
    if (count != 0) {
        // 0x0034db6c
        charge(ctx, 3);
        lw(v1, a0, psys::kLive);
        if (v1 != 0) {
            // 0x0034db78
            charge(ctx, 6);
            lw(sysrec, a0, psys::kRecords);
            lw(rec, obj, k3::kRecords);
            lhu(a0, obj, k3::kKindWord);
            v1 = 3;
            if (a0 == v1) {
                // 0x0034db98
                charge(ctx, 3);
                i = 0;
                for (;;) {
                    // 0x0034dbcc
                    charge(ctx, 3);
                    v1 = slt(i, count);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0034dba4
                    charge(ctx, 3);
                    lw(v1, sysrec, sysrec::kState);
                    if (v1 == 0) {
                        // 0x0034dbb0
                        charge(ctx, 4);
                        a0 = obj;
                        a1 = rec;
                        jal(ctx, 0x34DBB8u, gen::fn_sub_34D150_0034d150);
                    }
                    // 0x0034dbc0
                    charge(ctx, 3);
                    i = addiu(i, 1);
                    sysrec = addiu(sysrec, sysrec::kSize);
                    rec = addiu(rec, rec3::kSize);
                }
            } else {
                // 0x0034db90
                charge(ctx, 2);
            }
        }
    }
    // 0x0034dbd8 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(i, sp, 0x40);
    lq(obj, sp, 0x30);
    lq(sysrec, sp, 0x20);
    lq(rec, sp, 0x10);
    lq(count, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34DB30(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(obj));
    sub_34DB30(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x0034E390 sub_34E390 -- 52 bytes; frame 0x10: ra sp+0x0
// sub_34E390 [slot 3]: queue on the system's layer (sub_321220).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34E390(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lw, hg::sd;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034e390
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a0, k3::kSystem);
    if (v1 != 0) {
        // 0x0034e3a4
        charge(ctx, 4);
        lw(v0, v1, psys::kOwner);
        lhu(a1, v0, kOwnerLayer);
        jal(ctx, 0x34E3ACu, gen::fn_sub_321220_00321220);
    }
    // 0x0034e3b4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34E390(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(obj));
    sub_34E390(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}
u64 sub_34E3D0(EEContext& ctx, u64 obj) { return run(ctx, &Cpu::sub_34E3D0, obj); }
// 0x0034E420 sub_34E420 -- 36 bytes; frame 0x10: ra sp+0x0
// sub_34E420 / sub_34E450 [slots 8 / 9]: the system's position / rotation.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34E420(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lw, hg::sd;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034e420
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, k3::kSystem);
    jal(ctx, 0x34E42Cu, gen::fn_sub_3322D0_003322d0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34E420(EEContext& ctx, u64 obj, u64 v) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(obj));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(v));
    sub_34E420(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x0034E450 sub_34E450 -- 36 bytes; frame 0x10: ra sp+0x0
// sub_34E420 / sub_34E450 [slots 8 / 9]: the system's position / rotation.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34E450(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lw, hg::sd;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034e450
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, k3::kSystem);
    jal(ctx, 0x34E45Cu, gen::fn_sub_332310_00332310);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34E450(EEContext& ctx, u64 obj, u64 v) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(obj));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(v));
    sub_34E450(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x0034E480 sub_34E480 -- 12 bytes; leaf frame (no stack)
// sub_34E480 [slot 12] (and kind 4's sub_34FC90): colour word +4.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34E480(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::sw;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x0034e480
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(a1, a0, k3::kColour);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34E480(EEContext& ctx, u64 obj, u64 rgba) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(obj));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(rgba));
    sub_34E480(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}
u64 sub_34E490(EEContext& ctx, u64 obj) { return run(ctx, &Cpu::sub_34E490, obj); }
u64 sub_34E7C0(EEContext& ctx, u64 obj, u64 name) { return run(ctx, &Cpu::sub_34E7C0, obj, name); }
// 0x0034E800 sub_34E800 -- 28 bytes; leaf frame (no stack)
// sub_34E800 [slot 6: copy]: dst shares src's texture (+96), whose reference count (+84) grows by one.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34E800(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::enter, hg::lw, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0034e800
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(a1, a1, k4::kTexture);  // src->texture
    sw(a1, a0, k4::kTexture);
    lw(v1, a1, kTextureRefCount);
    v1 = addiu(v1, 1);
    sw(v1, a1, kTextureRefCount);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34E800(EEContext& ctx, u64 dst, u64 src) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(dst));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(src));
    sub_34E800(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x0034E910 sub_34E910 -- 44 bytes; frame 0x10: ra sp+0x0
// sub_34E910 [slot 7: reset]: sub_332200(system +92) when there is one.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34E910(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lw, hg::sd;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034e910
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, k4::kSystem);
    if (a0 != 0) {
        // 0x0034e924
        charge(ctx, 2);
        jal(ctx, 0x34E924u, gen::fn_sub_332200_00332200);
    }
    // 0x0034e92c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34E910(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(obj));
    sub_34E910(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}
u64 sub_34E940(EEContext& ctx, u64 obj, u64 rec) { return run(ctx, &Cpu::sub_34E940, obj, rec); }
// 0x0034F6B0 sub_34F6B0 -- 596 bytes; frame 0x70: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// sub_34F6B0 [slot 2: step]: steps the system (+92, sub_332210); when it has particles (count +8, records +24, a
// non-null +16): the scroll positions +84 / +88 advance by +28 / +32, then for every particle (system record of 32
// bytes, object record of 28 at +100): emitted when its system record +16 is 0 (kind4_emit), and while that word is
// not negative the two phases advance by their speeds (+0 += +4, +12 += +16).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34F6B0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::adda_s, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::i64, hg::jal,
          hg::ld, hg::lq, hg::lw, hg::lwc1, hg::madd_s, hg::mtc1, hg::mul_s, hg::sd, hg::slt, hg::sq, hg::sub_s,
          hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, count{ctx, 16}, i{ctx, 17}, rec{ctx, 18}, sysrec{ctx, 19}, obj{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f20{ctx, 20};
    // 0x0034f6b0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(obj, sp, 0x50);
    sq(sysrec, sp, 0x40);
    sq(rec, sp, 0x30);
    sq(i, sp, 0x20);
    sq(count, sp, 0x10);
    swc1(f20, sp, 0x0);
    obj = a0;
    lw(a0, a0, k4::kSystem);
    jal(ctx, 0x34F6D8u, gen::fn_sub_332210_00332210);
    lw(a0, obj, k4::kSystem);
    lw(count, a0, psys::kCount);
    if (count != 0) {
        // 0x0034f6f0
        charge(ctx, 3);
        lw(v1, a0, psys::kLive);
        if (v1 != 0) {
            // 0x0034f6fc
            charge(ctx, 13);
            lw(sysrec, a0, psys::kRecords);
            lw(rec, obj, k4::kRecords);
            lwc1(f1, obj, k4::kScrollSpeedU);
            lwc1(f0, obj, k4::kScrollU);
            add_s(f0, f0, f1);
            swc1(f0, obj, k4::kScrollU);
            lwc1(f1, obj, k4::kScrollSpeedV);
            lwc1(f0, obj, k4::kScrollV);
            add_s(f0, f0, f1);
            swc1(f0, obj, k4::kScrollV);
            i = 0;
            for (;;) {
                // 0x0034f8d0
                charge(ctx, 3);
                v1 = slt(i, count);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0034f730
                charge(ctx, 3);
                lw(v1, sysrec, sysrec::kState);
                if (v1 == 0) {
                    // 0x0034f73c
                    charge(ctx, 87);
                    lwc1(f20, obj, k4::kSpread);
                    a0 = 0;
                    jal(ctx, 0x34F744u, gen::fn_sub_358030_00358030);
                    v0 = mview::flt(1.0f);
                    mtc1(v0, f1);
                    sub_s(f2, f1, f20);
                    mtc1(zero, f1);
                    adda_s(f1, f2);
                    madd_s(f20, f20, f0);
                    a0 = 0;
                    jal(ctx, 0x34F770u, gen::fn_sub_358030_00358030);
                    lwc1(f1, gp, kGpPhaseRange);
                    mul_s(f0, f1, f0);
                    swc1(f0, rec, rec4::kPhaseA);
                    a0 = 0;
                    jal(ctx, 0x34F788u, gen::fn_sub_358030_00358030);
                    lwc1(f1, gp, kGpPhaseRange);
                    mul_s(f0, f1, f0);
                    swc1(f0, rec, rec4::kPhaseB);
                    a0 = 0;
                    jal(ctx, 0x34F7A0u, gen::fn_sub_358030_00358030);
                    v0 = mview::flt(0.5f);
                    mtc1(v0, f2);
                    mtc1(zero, f1);
                    adda_s(f1, f2);
                    madd_s(f1, f2, f0);
                    lwc1(f0, obj, k4::kPhaseSpeed);
                    mul_s(f0, f0, f1);
                    swc1(f0, rec, rec4::kSpeedA);
                    a0 = 0;
                    jal(ctx, 0x34F7D0u, gen::fn_sub_358030_00358030);
                    v0 = mview::flt(0.5f);
                    mtc1(v0, f2);
                    mtc1(zero, f1);
                    adda_s(f1, f2);
                    madd_s(f1, f2, f0);
                    lwc1(f0, obj, k4::kPhaseSpeed);
                    mul_s(f0, f0, f1);
                    swc1(f0, rec, rec4::kSpeedB);
                    a0 = 0;
                    jal(ctx, 0x34F800u, gen::fn_sub_358030_00358030);
                    lwc1(f3, gp, kGpSizeRange);
                    lwc1(f2, gp, kGpSizeBase);
                    mtc1(zero, f1);
                    adda_s(f1, f2);
                    madd_s(f1, f3, f0);
                    lwc1(f0, obj, k4::kSizeA);
                    mul_s(f0, f0, f1);
                    mul_s(f0, f20, f0);
                    swc1(f0, rec, rec4::kSizeA);
                    a0 = 0;
                    jal(ctx, 0x34F834u, gen::fn_sub_358030_00358030);
                    lwc1(f3, gp, kGpSizeRange);
                    lwc1(f2, gp, kGpSizeBase);
                    mtc1(zero, f1);
                    adda_s(f1, f2);
                    madd_s(f1, f3, f0);
                    lwc1(f0, obj, k4::kSizeB);
                    mul_s(f0, f0, f1);
                    mul_s(f0, f20, f0);
                    swc1(f0, rec, rec4::kSizeB);
                    lwc1(f20, obj, k4::kSpread2);
                    a0 = 0;
                    jal(ctx, 0x34F86Cu, gen::fn_sub_358030_00358030);
                    v1 = mview::flt(1.0f);
                    mtc1(v1, f1);
                    sub_s(f2, f1, f20);
                    mtc1(zero, f1);
                    adda_s(f1, f2);
                    madd_s(f0, f20, f0);
                    swc1(f0, rec, rec4::kFactor);
                }
                // 0x0034f898
                charge(ctx, 3);
                lw(v1, sysrec, sysrec::kState);
                if (i64(v1) >= 0) {
                    // 0x0034f8a4
                    charge(ctx, 8);
                    lwc1(f1, rec, rec4::kSpeedA);
                    lwc1(f0, rec, rec4::kPhaseA);
                    add_s(f0, f0, f1);
                    swc1(f0, rec, rec4::kPhaseA);
                    lwc1(f1, rec, rec4::kSpeedB);
                    lwc1(f0, rec, rec4::kPhaseB);
                    add_s(f0, f0, f1);
                    swc1(f0, rec, rec4::kPhaseB);
                }
                // 0x0034f8c4
                charge(ctx, 3);
                i = addiu(i, 1);
                sysrec = addiu(sysrec, sysrec::kSize);
                rec = addiu(rec, rec4::kSize);
            }
        }
    }
    // 0x0034f8dc (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(obj, sp, 0x50);
    lq(sysrec, sp, 0x40);
    lq(rec, sp, 0x30);
    lq(i, sp, 0x20);
    lq(count, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34F6B0(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(obj));
    sub_34F6B0(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x0034F910 sub_34F910 -- 560 bytes; frame 0x100: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_34F910 [draw the particles] (a0 object, a1 mode): when the system (+92) has particles: the manager's slot 21
// (sub_3210A0) gives the raster; mode byte 1 binds it (the RW engine's render-state set 0x960090 with state 1, a
// `jalr`); the raster size (+12 / +16 as floats) at sp+240, the colour (+4) as floats x gp[-32232] at sp+224. With
// system flag bit 0 clear each live particle (system record +16 not negative) is drawn at its own position
// (sub_34EAE0); with it set, the positions are transformed by the system's matrix (rotation sub_3322F0 -> VU0
// matrix sub_357E30, position sub_3322B0 as row 3) first, into sp+208.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34F910(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::Vf, hg::addiu, hg::backedge, hg::charge, hg::cvt_s_w, hg::enter, hg::i64, hg::jal,
          hg::jalr, hg::ld, hg::lq, hg::lqc2, hg::lw, hg::lwc1, hg::pextlb, hg::pextlh, hg::qmtc2, hg::sd, hg::slt,
          hg::sq, hg::sqc2, hg::sw, hg::swc1, hg::vitof0, hg::vmadd_bc, hg::vmadda_bc, hg::vmul_bc, hg::vmula_bc;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, count{ctx, 16}, rec{ctx, 17}, sysrec{ctx, 18}, mode{ctx, 19}, obj{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    Vf vf0{ctx, 0}, vf2{ctx, 2}, vf10{ctx, 10}, vf28{ctx, 28}, vf29{ctx, 29}, vf30{ctx, 30}, vf31{ctx, 31};
    // 0x0034f910
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x100);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(obj, sp, 0x40);
    sq(mode, sp, 0x30);
    sq(sysrec, sp, 0x20);
    sq(rec, sp, 0x10);
    sq(count, sp, 0x0);
    obj = a0;
    mode = a1;
    lw(a0, a0, k4::kSystem);
    lw(count, a0, psys::kCount);
    if (count != 0) {
        // 0x0034f948
        charge(ctx, 3);
        lw(v1, a0, psys::kLive);
        if (v1 != 0) {
            // 0x0034f954
            charge(ctx, 10);
            lw(sysrec, a0, psys::kRecords);
            lw(rec, obj, k4::kRecords);
            a0 = kRasterSlot;
            jal(ctx, 0x34F960u, gen::fn_sub_3210A0_003210a0);
            lw(s5, v0, 0);
            v0 = mode & 0xFF;
            a0 = 1;
            if (v0 == a0) {
                // 0x0034f97c
                charge(ctx, 5);
                a1 = s5;
                v0 = mview::hi(kRwRenderStateSet);
                lw(v0, v0, mview::lo(kRwRenderStateSet));  // pfn_RwRenderStateSet
                jalr(ctx, 0x34F988u, v0.u());
            }
            // 0x0034f990
            charge(ctx, 25);
            lwc1(f0, s5, kRasterWidth);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xF0);
            lwc1(f0, s5, kRasterHeight);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xF4);
            lw(v0, obj, k4::kColour);
            sw(v0, sp, 0xFC);
            v0 = addiu(sp, 0xFC);
            lw(v1, gp, kGpColourUnit);
            lw(v0, v0, 0);
            pextlb(v0, zero, v0);
            pextlh(v0, zero, v0);
            qmtc2(v0, vf10, false);  // qmtc2
            vitof0(0xF, vf10, vf10);  // vitof0.xyzw
            qmtc2(v1, vf2, false);  // qmtc2
            vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
            v1 = addiu(sp, 0xE0);
            sqc2(vf10, v1, 0);
            lw(a0, obj, k4::kSystem);
            lw(v1, a0, psys::kFlags);
            v1 = v1 & 0x1;
            if (v1 != 0) {
                // 0x0034fa50
                charge(ctx, 21);
                a1 = addiu(sp, 0xB0);
                jal(ctx, 0x34FA54u, gen::fn_sub_3322F0_003322f0);
                lw(a0, obj, k4::kSystem);
                a1 = addiu(sp, 0xC0);
                jal(ctx, 0x34FA64u, gen::fn_sub_3322B0_003322b0);
                v0 = addiu(sp, 0xB0);
                lqc2(vf10, v0, 0);
                jal(ctx, 0x34FA74u, gen::fn_sub_357E30_00357e30);
                v1 = addiu(sp, 0xC0);
                lqc2(vf31, v1, 0);
                v1 = addiu(sp, 0x70);
                sqc2(vf28, v1, 0);
                sqc2(vf29, v1, 16);
                sqc2(vf30, v1, 32);
                sqc2(vf31, v1, 48);
                s5 = 0;
                for (;;) {
                    // 0x0034fb0c
                    charge(ctx, 3);
                    v1 = slt(s5, count);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0034faa4
                    charge(ctx, 3);
                    lw(v1, sysrec, sysrec::kState);
                    if (i64(v1) >= 0) {
                        // 0x0034fab0
                        charge(ctx, 20);
                        v0 = addiu(sp, 0x70);
                        lqc2(vf28, v0, 0);
                        lqc2(vf29, v0, 16);
                        lqc2(vf30, v0, 32);
                        lqc2(vf31, v0, 48);
                        lqc2(vf10, sysrec, 0);
                        vmula_bc(0xF, vf28, vf10, 0);  // vmulax.xyzw
                        vmadda_bc(0xF, vf29, vf10, 1);  // vmadday.xyzw
                        vmadda_bc(0xF, vf30, vf10, 2);  // vmaddaz.xyzw
                        vmadd_bc(0xF, vf10, vf31, vf0, 3);  // vmaddw.xyzw
                        a3 = addiu(sp, 0xD0);
                        sqc2(vf10, a3, 0);
                        a0 = obj;
                        a1 = rec;
                        a2 = sysrec;
                        t0 = addiu(sp, 0xE0);
                        t1 = addiu(sp, 0xF0);
                        t2 = mode;
                        jal(ctx, 0x34FAF8u, gen::fn_sub_34EAE0_0034eae0);
                    }
                    // 0x0034fb00
                    charge(ctx, 3);
                    s5 = addiu(s5, 1);
                    sysrec = addiu(sysrec, sysrec::kSize);
                    rec = addiu(rec, rec4::kSize);
                }
            } else {
                // 0x0034f9f4
                charge(ctx, 3);
                s5 = 0;
                for (;;) {
                    // 0x0034fa3c
                    charge(ctx, 3);
                    v1 = slt(s5, count);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0034fa00
                    charge(ctx, 3);
                    lw(v1, sysrec, sysrec::kState);
                    if (i64(v1) >= 0) {
                        // 0x0034fa0c
                        charge(ctx, 9);
                        a0 = obj;
                        a1 = rec;
                        a2 = sysrec;
                        a3 = sysrec;
                        t0 = addiu(sp, 0xE0);
                        t1 = addiu(sp, 0xF0);
                        t2 = mode;
                        jal(ctx, 0x34FA28u, gen::fn_sub_34EAE0_0034eae0);
                    }
                    // 0x0034fa30
                    charge(ctx, 3);
                    s5 = addiu(s5, 1);
                    sysrec = addiu(sysrec, sysrec::kSize);
                    rec = addiu(rec, rec4::kSize);
                }
                // 0x0034fa48
                charge(ctx, 2);
            }
        }
    }
    // 0x0034fb18 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(obj, sp, 0x40);
    lq(mode, sp, 0x30);
    lq(sysrec, sp, 0x20);
    lq(rec, sp, 0x10);
    lq(count, sp, 0x0);
    sp = addiu(sp, 0x100);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34F910(EEContext& ctx, u64 obj, u64 mode) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(obj));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(mode));
    sub_34F910(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}
u64 sub_34FB40(EEContext& ctx, u64 obj) { return run(ctx, &Cpu::sub_34FB40, obj); }
u64 sub_34FB70(EEContext& ctx, u64 obj) { return run(ctx, &Cpu::sub_34FB70, obj); }
// 0x0034FBA0 sub_34FBA0 -- 52 bytes; frame 0x10: ra sp+0x0
// sub_34FBA0 [slot 3]: queue on the system's layer (sub_3212A0); sub_34FBE0 [slot 1]: step, then queue.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34FBA0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lw, hg::sd;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034fba0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a0, k4::kSystem);
    if (v1 != 0) {
        // 0x0034fbb4
        charge(ctx, 4);
        lw(v0, v1, psys::kOwner);
        lhu(a1, v0, kOwnerLayer);
        jal(ctx, 0x34FBBCu, gen::fn_sub_3212A0_003212a0);
    }
    // 0x0034fbc4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34FBA0(EEContext& ctx, u64 obj) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(obj));
    sub_34FBA0(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}
u64 sub_34FBE0(EEContext& ctx, u64 obj) { return run(ctx, &Cpu::sub_34FBE0, obj); }
// 0x0034FC30 sub_34FC30 -- 36 bytes; frame 0x10: ra sp+0x0
// sub_34FC30 / sub_34FC60 [slots 8 / 9]: the system's position / rotation.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34FC30(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lw, hg::sd;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034fc30
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, k4::kSystem);
    jal(ctx, 0x34FC3Cu, gen::fn_sub_3322D0_003322d0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34FC30(EEContext& ctx, u64 obj, u64 v) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(obj));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(v));
    sub_34FC30(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x0034FC60 sub_34FC60 -- 36 bytes; frame 0x10: ra sp+0x0
// sub_34FC30 / sub_34FC60 [slots 8 / 9]: the system's position / rotation.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34FC60(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lw, hg::sd;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034fc60
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, k4::kSystem);
    jal(ctx, 0x34FC6Cu, gen::fn_sub_332310_00332310);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34FC60(EEContext& ctx, u64 obj, u64 v) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(obj));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(v));
    sub_34FC60(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x0034FC90 sub_34FC90 -- 12 bytes; leaf frame (no stack)
// sub_34E480 [slot 12] (and kind 4's sub_34FC90): colour word +4.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34FC90(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::sw;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x0034fc90
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(a1, a0, k4::kColour);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34FC90(EEContext& ctx, u64 obj, u64 rgba) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(obj));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(rgba));
    sub_34FC90(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}
u64 sub_34FCA0(EEContext& ctx, u64 obj) { return run(ctx, &Cpu::sub_34FCA0, obj); }
u64 sub_34FCD0(EEContext& ctx, u64 a0, u64 a1, u64 a2, u64 a3) { return run(ctx, &Cpu::sub_34FCD0, a0, a1, a2, a3); }
u64 sub_34FCF0(EEContext& ctx, u64 node) { return run(ctx, &Cpu::sub_34FCF0, node); }
u64 sub_34FD10(EEContext& ctx, u64 node) { return run(ctx, &Cpu::sub_34FD10, node); }
u64 sub_34FD30(EEContext& ctx, u64 node) { return run(ctx, &Cpu::sub_34FD30, node); }
u64 sub_34FD50(EEContext& ctx, u64 node) { return run(ctx, &Cpu::sub_34FD50, node); }
u64 sub_34FD70(EEContext& ctx, u64 node, u64 layer) { return run(ctx, &Cpu::sub_34FD70, node, layer); }
u64 sub_34FDB0(EEContext& ctx, u64 node, u64 layer) { return run(ctx, &Cpu::sub_34FDB0, node, layer); }
u64 sub_34FDF0(EEContext& ctx, u64 node, u64 pos) { return run(ctx, &Cpu::sub_34FDF0, node, pos); }
u64 sub_34FE30(EEContext& ctx, u64 node) { return run(ctx, &Cpu::sub_34FE30, node); }
u64 sub_34FE80(EEContext& ctx, u64 node, u64 matrix) { return run(ctx, &Cpu::sub_34FE80, node, matrix); }
u64 sub_34FF70(EEContext& ctx, u64 node) { return run(ctx, &Cpu::sub_34FF70, node); }
// 0x0034FF90 sub_34FF90 -- 36 bytes; frame 0x10: ra sp+0x0
// sub_34FF90 [colour from *rgba]: sub_326030(node, *a1).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_34FF90(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lw, hg::sd;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034ff90
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a1, a1, 0);
    jal(ctx, 0x34FF9Cu, gen::fn_sub_326030_00326030);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_34FF90(EEContext& ctx, u64 node, u64 rgba) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(node));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(rgba));
    sub_34FF90(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}
u64 sub_34FFC0(EEContext& ctx, u64 node, u64 matrix) { return run(ctx, &Cpu::sub_34FFC0, node, matrix); }

}  // namespace p3fes::game

// --- the recompiled program's entry points (the bodies read their arguments from the registers) -----------
namespace p3fes::recomp_gen {
using ::p3fes::game::epl::detail::Cpu;

#define P3FES_EPL_ENTRY(name, addr) \
    void fn_##name##_##addr(p3fes::EEContext& ctx) { Cpu(ctx).name(); }
P3FES_EPL_ENTRY(sub_34C660, 0034c660)
P3FES_EPL_ENTRY(sub_34C940, 0034c940)
P3FES_EPL_ENTRY(sub_34D050, 0034d050)
P3FES_EPL_ENTRY(sub_34D0C0, 0034d0c0)
P3FES_EPL_ENTRY(sub_34E3D0, 0034e3d0)
P3FES_EPL_ENTRY(sub_34E490, 0034e490)
P3FES_EPL_ENTRY(sub_34E7C0, 0034e7c0)
P3FES_EPL_ENTRY(sub_34E940, 0034e940)
P3FES_EPL_ENTRY(sub_34FB40, 0034fb40)
P3FES_EPL_ENTRY(sub_34FB70, 0034fb70)
P3FES_EPL_ENTRY(sub_34FBE0, 0034fbe0)
P3FES_EPL_ENTRY(sub_34FCA0, 0034fca0)
P3FES_EPL_ENTRY(sub_34FCD0, 0034fcd0)
P3FES_EPL_ENTRY(sub_34FCF0, 0034fcf0)
P3FES_EPL_ENTRY(sub_34FD10, 0034fd10)
P3FES_EPL_ENTRY(sub_34FD30, 0034fd30)
P3FES_EPL_ENTRY(sub_34FD50, 0034fd50)
P3FES_EPL_ENTRY(sub_34FD70, 0034fd70)
P3FES_EPL_ENTRY(sub_34FDB0, 0034fdb0)
P3FES_EPL_ENTRY(sub_34FDF0, 0034fdf0)
P3FES_EPL_ENTRY(sub_34FE30, 0034fe30)
P3FES_EPL_ENTRY(sub_34FE80, 0034fe80)
P3FES_EPL_ENTRY(sub_34FF70, 0034ff70)
P3FES_EPL_ENTRY(sub_34FFC0, 0034ffc0)
#undef P3FES_EPL_ENTRY

}  // namespace p3fes::recomp_gen
