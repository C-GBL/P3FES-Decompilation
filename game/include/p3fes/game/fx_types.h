// Phase 5 slice fx_types: the effect system's table-dispatched effect-type handlers, the band 0x324160-0x34C160 of
// docs/ANALYSIS/27_unmapped_bands.md (section 6, "Effect-type handlers"). Not one of queue_bands.txt's slices: the
// band map's direct-call closure cannot follow the jalr tables, so the functions taken here were chosen by measuring
// which handlers the replay routes run (a temporary per-function call counter in the recompiled bodies, built once
// into a gate tree, never committed; the counts are in src/fx/fx_types.cpp and docs/INTEGRATION_LOG.md).
//
// Route coverage (the call counter, entries per route: M1 boot, dorm to vblank 4900, battle to vblank 6150): M1 runs 3
// functions of the band, dorm 30, battle 245 of 400. Of the 129 here battle runs 96 (the hottest: the keyframe curve
// sub_32A540 55,687 calls, the screen shake sub_347D60 8,371 -- also 7,755 on dorm and 5,520 on M1 --, the track value
// setter sub_3322D0 7,015, the screen-filter kinds sub_34B520 / sub_34B580 / sub_34B5C0 ~3,070 each), dorm 15, M1 3;
// the other 33 are the shared class-row defaults and dispatchers and other slots / twins of the classes that run.
//
// The dispatch (read from the instructions; names in brackets are proposals, not imported -- see
// symbols/deltas/fx_types.sym):
//
//   [effect class table] 0x69BE20: one row of 13 words per effect class (27 rows), indexed by the class number (the
//               u16 at effect +4; `row = 0x69BE20 + 52 * class`). Most rows hold the shared defaults sub_324630 /
//               sub_324640 / sub_324650 (return 0) / sub_324660 / sub_324670 in the slots a class does not override.
//               The base-class dispatchers sub_324930 .. sub_324AF0 load a slot of the effect's row and call it on the
//               effect's instance (effect +8), some only when the slot is non-null. Slot 0 makes the instance from the
//               effect record, slot 1 destroys it, slots 2 / 3 update / draw it.
//   [effect node] the node tree sub_324BD0 builds (EffectNode, fx_epl.h): position +64, rotation +80, first child
//               +140, next sibling +172, the child's key +144.
//   [track]     the animation track of the classes 1 / 2 (object +76 / +48): type rows of four words at 0x69C510.
//   [kind rows] the classes 9, 10, 12, 13, 16 delegate to per-kind rows (0x69C5D0 / 0x69C650: six words, 0x69C850 /
//               0x69C970: seven words); the screen filters (classes 4 / 5) to 0x69CB98 / 0x69CC58.
//   [shake]     the screen shake's gp-relative state: gp-18340 the active byte, gp-18332 / gp-18328 the amplitudes,
//               gp-18320 the camera, gp-18312 / gp-18308 the current offsets, gp-25256 the weight.
//
// Register contract (docs/PHASE5_AGENT_BRIEF.md, waves 6, 7 and 10): every check point can preempt the thread and the
// kernel then saves the whole register file in guest memory, callees spill what they receive and game code reads
// registers a callee left behind. So these bodies are register-faithful: at every check point, every call and every
// return each GPR (128 bits), HI/LO, FPR, ACC and FCR31 holds what the original holds there, and the prologues write
// the original spills (the 128-bit frame slots included); tools/ours/audit/audit_faithful.py checks it. The bodies
// work on the guest registers directly (the Cpu view below, one named variable per register, as core3.cpp /
// nm_message.cpp), with the data flow named in comments; the per-block virtual time follows the recompiled bodies
// (ADR-0013). Guest memory goes through the runtime's own load / store instructions (rt::lw .. rt::sq, base $zero,
// the address as the offset), so an access the original would fault on stops the run the same way.
#pragma once

#include "p3fes/ee/core.h"
#include "p3fes/game/guest.h"
#include "p3fes_recomp_rt.h"

namespace p3fes::game {

namespace fx::detail {

namespace core = ee::core;

// --- R5900 integer results (32-bit operations sign-extend into the 64-bit register) ----------------------
constexpr u64 sx(u32 v) { return core::sext32(v); }
constexpr u64 addu(u64 a, u64 b) { return core::add32(a, b); }
constexpr u64 addiu(u64 a, s32 i) { return core::add32i(a, i); }
constexpr u64 subu(u64 a, u64 b) { return core::sub32(a, b); }
constexpr u64 lui(u32 i) { return core::lui(i); }
constexpr u64 sll(u64 a, unsigned n) { return core::sll(a, n); }
constexpr u64 srl(u64 a, unsigned n) { return core::srl(a, n); }
constexpr u64 sra(u64 a, unsigned n) { return core::sra(a, n); }
constexpr u64 slt(u64 a, u64 b) { return core::slt(a, b); }
constexpr u64 sltu(u64 a, u64 b) { return core::sltu(a, b); }
constexpr u64 slti(u64 a, s32 i) { return core::slti(a, i); }
constexpr u64 sltiu(u64 a, s32 i) { return core::sltiu(a, i); }
constexpr u64 andi(u64 a, u32 i) { return core::andi(a, i); }
constexpr u64 ori(u64 a, u32 i) { return core::ori(a, i); }
constexpr s64 sgn(u64 v) { return static_cast<s64>(v); }  // a register as a signed 64-bit value
constexpr u32 w(u64 v) { return static_cast<u32>(v); }

// One GPR of the guest context. Reads go through volatile lvalues, and so does virtual time below (the wave-10 lesson
// of render_core3: MSVC 14.44 /O2 kept ctx.cycles in a host register across a call to a small helper that charges, and
// the helper's charges were lost). A volatile access is a compiler barrier under /volatile:ms and keeps every access
// real under clang-cl, so no guest state is cached across a helper or a call. A load is written `reg = lw(address)`:
// lw() names the access and the assignment performs it into that register, as the instruction does.
enum class LoadKind : u8 { lw, lh, lhu, lb, lbu, ld };
struct Load {
    u64 addr;
    LoadKind kind;
};
inline s32 off_of(u64 addr) { return static_cast<s32>(static_cast<u32>(addr)); }

struct Gpr {
    EEContext& c;
    const unsigned r;
    operator u64() const noexcept { return static_cast<const volatile u64&>(c.gpr[r].u64[0]); }
    Gpr& operator=(u64 v) noexcept {
        core::set_gpr64(c, r, v);
        return *this;
    }
    Gpr& operator=(const Gpr& o) noexcept { return *this = static_cast<u64>(o); }
    Gpr& operator=(const Load& l) {
        const s32 off = off_of(l.addr);
        switch (l.kind) {
        case LoadKind::lw: rt::lw(c, r, GPR_ZERO, off); break;
        case LoadKind::lh: rt::lh(c, r, GPR_ZERO, off); break;
        case LoadKind::lhu: rt::lhu(c, r, GPR_ZERO, off); break;
        case LoadKind::lb: rt::lb(c, r, GPR_ZERO, off); break;
        case LoadKind::lbu: rt::lbu(c, r, GPR_ZERO, off); break;
        case LoadKind::ld: rt::ld(c, r, GPR_ZERO, off); break;
        }
        return *this;
    }
};

// FPR numbers.
enum : unsigned {
    F0, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15,
    F16, F17, F18, F19, F20, F21, F22, F23, F24, F25, F26, F27, F28, F29, F30, F31
};

// The guest machine as the bodies see it (src/fx/fx_types.cpp derives the bodies from it).
class Cpu {
public:
    explicit Cpu(EEContext& ctx) noexcept : c(ctx) {}

    EEContext& c;
    Gpr zero{c, 0}, at{c, 1}, v0{c, 2}, v1{c, 3}, a0{c, 4}, a1{c, 5}, a2{c, 6}, a3{c, 7};
    Gpr t0{c, 8}, t1{c, 9}, t2{c, 10}, t3{c, 11}, t4{c, 12}, t5{c, 13}, t6{c, 14}, t7{c, 15};
    Gpr s0{c, 16}, s1{c, 17}, s2{c, 18}, s3{c, 19}, s4{c, 20}, s5{c, 21}, s6{c, 22}, s7{c, 23};
    Gpr t8{c, 24}, t9{c, 25}, gp{c, 28}, sp{c, 29}, fp{c, 30}, ra{c, 31};

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

    // loads / stores through the runtime's instructions (addresses are 32-bit; LQ / SQ force a quadword boundary)
    static Load lw(u64 a) noexcept { return {a, LoadKind::lw}; }
    static Load lh(u64 a) noexcept { return {a, LoadKind::lh}; }
    static Load lhu(u64 a) noexcept { return {a, LoadKind::lhu}; }
    static Load lb(u64 a) noexcept { return {a, LoadKind::lb}; }
    static Load lbu(u64 a) noexcept { return {a, LoadKind::lbu}; }
    static Load ld(u64 a) noexcept { return {a, LoadKind::ld}; }
    void lq(const Gpr& d, u64 a) { rt::lq(c, d.r, GPR_ZERO, off_of(a)); }
    void sw(u64 a, const Gpr& v) { rt::sw(c, v.r, GPR_ZERO, off_of(a)); }
    void sh(u64 a, const Gpr& v) { rt::sh(c, v.r, GPR_ZERO, off_of(a)); }
    void sb(u64 a, const Gpr& v) { rt::sb(c, v.r, GPR_ZERO, off_of(a)); }
    void sd(u64 a, const Gpr& v) { rt::sd(c, v.r, GPR_ZERO, off_of(a)); }
    void sq(u64 a, const Gpr& v) { rt::sq(c, v.r, GPR_ZERO, off_of(a)); }

    // FPU (the runtime's instruction semantics: EE singles, ACC, FCR31 flags)
    void lwc1(unsigned f, u64 a) { rt::lwc1(c, f, GPR_ZERO, off_of(a)); }
    void swc1(unsigned f, u64 a) { rt::swc1(c, f, GPR_ZERO, off_of(a)); }
    void mtc1(const Gpr& g, unsigned f) noexcept { rt::mtc1(c, g.r, f); }
    void mfc1(Gpr& g, unsigned f) noexcept { rt::mfc1(c, g.r, f); }
    void mov_s(unsigned d, unsigned s) noexcept { rt::mov_s(c, d, s); }
    void neg_s(unsigned d, unsigned s) noexcept { rt::neg_s(c, d, s); }
    void add_s(unsigned d, unsigned s, unsigned t) noexcept { rt::add_s(c, d, s, t); }
    void sub_s(unsigned d, unsigned s, unsigned t) noexcept { rt::sub_s(c, d, s, t); }
    void mul_s(unsigned d, unsigned s, unsigned t) noexcept { rt::mul_s(c, d, s, t); }
    void div_s(unsigned d, unsigned s, unsigned t) noexcept { rt::div_s(c, d, s, t); }
    void cvt_s_w(unsigned d, unsigned s) noexcept { rt::cvt_s_w(c, d, s); }
    void cvt_w_s(unsigned d, unsigned s) noexcept { rt::cvt_w_s(c, d, s); }
    void abs_s(unsigned d, unsigned s) noexcept { rt::abs_s(c, d, s); }
    void sqrt_s(unsigned d, unsigned t) noexcept { rt::sqrt_s(c, d, t); }
    void adda_s(unsigned s, unsigned t) noexcept { rt::adda_s(c, s, t); }
    void suba_s(unsigned s, unsigned t) noexcept { rt::suba_s(c, s, t); }
    void mula_s(unsigned s, unsigned t) noexcept { rt::mula_s(c, s, t); }
    void madda_s(unsigned s, unsigned t) noexcept { rt::madda_s(c, s, t); }
    void msuba_s(unsigned s, unsigned t) noexcept { rt::msuba_s(c, s, t); }
    void madd_s(unsigned d, unsigned s, unsigned t) noexcept { rt::madd_s(c, d, s, t); }
    void msub_s(unsigned d, unsigned s, unsigned t) noexcept { rt::msub_s(c, d, s, t); }
    void c_lt_s(unsigned s, unsigned t) noexcept { rt::c_lt_s(c, s, t); }
    void c_le_s(unsigned s, unsigned t) noexcept { rt::c_le_s(c, s, t); }
    void c_eq_s(unsigned s, unsigned t) noexcept { rt::c_eq_s(c, s, t); }
    bool cop1_cond() const noexcept { return rt::cop1_cond(c); }

    // VU0 macro mode (lqc2 / sqc2 of a vf register)
    void lqc2(unsigned vf, u64 a) { rt::lqc2(c, vf, GPR_ZERO, off_of(a)); }
    void sqc2(unsigned vf, u64 a) { rt::sqc2(c, vf, GPR_ZERO, off_of(a)); }

    // calls: `jal fn` at pc ($ra = pc + 8; a delay slot's instruction is written before the call) and `jalr target`
    // at pc (through the dispatch table; $ra = pc + 8)
    void jal(u32 pc, rt::Fn fn) {
        rt::jal(c, pc);
        fn(c);
    }
    void jalr(u32 pc, u32 target) {
        rt::jalr(c, GPR_RA, pc);
        rt::lookup_func(target)(c);
    }

    // the prologue / epilogue pair every non-leaf of the band uses: a frame of 16 * (n + 1) bytes, s0..s(n-1) spilled
    // in 128 bits at 16 * i, $ra at 16 * n (`addiu sp, -size; sd ra; sq s(n-1) .. sq s0` / `ld ra; lq ..; addiu sp`)
    void open_frame(unsigned n);
    void close_frame(unsigned n);
};

}  // namespace fx::detail

// --- the public entry points ----------------------------------------------------------------------------------------
// Each function keeps its symbols/functions.json name; the bracketed role is a proposal. They take their guest
// arguments as 64-bit register values ($a0..; floats in $f12 as the caller leaves them) and return $v0 (for the void
// ones, whatever the original left there). The recompiled program's entry points (fn_<name>_<addr8>) are defined in
// src/fx/fx_types.cpp.
// [fxLayerAttach] tail into the layer manager sub_321140
u64 sub_3243D0(EEContext& ctx, u64 a0, u64 a1, u64 a2, u64 a3);
// [fxSetModelMatrixB] matrix from sub_323A30 onto the model (+12)
u64 sub_3244C0(EEContext& ctx, u64 effect);
// [fxBlockA] the block at +16 (absolute when +24 is set, else record-relative)
u64 sub_3245B0(EEContext& ctx, u64 rec);
// [fxBlockB] the block at +32 (absolute when +40 is set, else record-relative)
u64 sub_3245F0(EEContext& ctx, u64 rec);
u64 sub_324630(EEContext& ctx);                          // [fxDefaultNop] empty class-row default
u64 sub_324640(EEContext& ctx);                          // [fxDefaultNop] empty class-row default
u64 sub_324650(EEContext& ctx);                          // [fxDefaultZero] class-row default, returns 0
u64 sub_324660(EEContext& ctx);                          // [fxDefaultNop] empty class-row default
u64 sub_324670(EEContext& ctx);                          // [fxDefaultNop] empty class-row default
u64 sub_324930(EEContext& ctx, u64 effect);              // [fxClassSlot7] class slot 7 on the instance when present
u64 sub_324990(EEContext& ctx, u64 effect);              // [fxClassSlot2] class slot 2 on the instance
u64 sub_3249E0(EEContext& ctx, u64 effect);              // [fxClassSlot3] class slot 3 on the instance
u64 sub_324A30(EEContext& ctx, u64 effect);              // [fxClassSlot8] class slot 8 on the instance when present
u64 sub_324A90(EEContext& ctx, u64 effect);              // [fxClassSlot10] class slot 10 on the instance when present
u64 sub_324AF0(EEContext& ctx, u64 effect);              // [fxClassSlot12] class slot 12 on the instance when present
// [fxNodeReset] the 128-byte effect-node header and its defaults
u64 sub_324B50(EEContext& ctx, u64 node);
u64 sub_326160(EEContext& ctx, u64 node, u64 out);       // [fxNodeGetPosition] *out = node +64
u64 sub_326170(EEContext& ctx, u64 node, u64 out);       // [fxNodeGetRotation] *out = node +80
u64 sub_326180(EEContext& ctx, u64 node);                // [fxNodeGetWord100] node +100
u64 sub_326190(EEContext& ctx, u64 dst, u64 src);        // [fxNodeCopyHeader] memcpy(dst, src, 144)
// [fxNodeFindChild] the child with key (+144) among +140 / +172, else 0
u64 sub_3261C0(EEContext& ctx, u64 node, u64 key);
u64 sub_326200(EEContext& ctx, u64 node, u64 index);     // [fxNodeChildAt] the child at a position, else 0
u64 sub_326240(EEContext& ctx, u64 node, u64 child);     // [fxNodeChildIndex] the position of a child, else 0
u64 sub_327220(EEContext& ctx, u64 obj);                 // [fxObjTrackRestart] restart of the track at +76
// [fxObj1Update] the track's update, then sub_327250(obj, 1.0f)
u64 sub_329350(EEContext& ctx, u64 obj);
u64 sub_3293A0(EEContext& ctx, u64 obj);                 // [fxObj1Draw] sub_3275D0(obj, 1.0f)
u64 sub_3293D0(EEContext& ctx, u64 obj);                 // [fxObj1UpdateDraw] sub_329350 then sub_3293A0
u64 sub_329430(EEContext& ctx, u64 obj, u64 src);        // [fxObjTrackSetValue] track +76 value 0 = *src
u64 sub_329460(EEContext& ctx, u64 obj, u64 src);        // [fxObjTrackSetValue2] track +76 value 1 = *src
u64 sub_329490(EEContext& ctx, u64 obj, u64 value);      // [fxObjSetWord4] +4 = value
u64 sub_3294A0(EEContext& ctx, u64 obj);                 // [fxObjTrackSetTime] +8 = $f12, the track's (+76) time setter
// [fxCameraPos] the scene camera's matrix row +32 as (x, y, z, 0)
u64 sub_329740(EEContext& ctx, u64 out);
// [fxCameraAt] the scene camera's matrix row +48 as (x, y, z, 0)
u64 sub_3297A0(EEContext& ctx, u64 out);
// [fxCurveEval] keyframe curve value at a frame, in $f0
u64 sub_32A540(EEContext& ctx, u64 curve, u64 frame, u64 duration);
u64 sub_3321D0(EEContext& ctx, u64 track);               // [fxTrackFreeKeys] RwFree(track +40)
u64 sub_332200(EEContext& ctx, u64 track);               // [fxTrackRestart] frame (+16) = 0
// [fxTrackUpdate] key slots reset on frame 0, the type's update (0x69C510), ++frame
u64 sub_332210(EEContext& ctx, u64 track);
u64 sub_3322B0(EEContext& ctx, u64 track, u64 out);      // [fxTrackGetValue] *out = value quadword 0
u64 sub_3322D0(EEContext& ctx, u64 track, u64 src);      // [fxTrackSetValue] value quadword 0 = *src
u64 sub_3322F0(EEContext& ctx, u64 track, u64 out);      // [fxTrackGetValue2] *out = value quadword 1
u64 sub_332310(EEContext& ctx, u64 track, u64 src);      // [fxTrackSetValue2] value quadword 1 = *src
u64 sub_332330(EEContext& ctx, u64 track);               // [fxTrackSetTime] the type's second word (0x69C514)
u64 sub_332B30(EEContext& ctx, u64 obj);                 // [fxObjTrackRestart] restart of the track at +48
u64 sub_333020(EEContext& ctx, u64 obj, u64 src);        // [fxObjTrackSetValue] track +48 value 0 = *src
u64 sub_333050(EEContext& ctx, u64 obj, u64 src);        // [fxObjTrackSetValue2] track +48 value 1 = *src
u64 sub_333080(EEContext& ctx, u64 obj, u64 value);      // [fxObjSetWord4Child] +4 = value, also on the child at +44
u64 sub_3330B0(EEContext& ctx, u64 obj);                 // [fxObjTrackSetTime] +8 = $f12, the track's (+48) time setter
u64 sub_3338B0(EEContext& ctx, u64 obj);                 // [fxObj2Destroy] sub_324310 on +16 and +20, RwFree(obj)
u64 sub_333900(EEContext& ctx, u64 obj, u64 index);      // [fxMaskClear] u16 mask[index] (+24) = 0
u64 sub_333920(EEContext& ctx, u64 obj, u64 index);      // [fxMaskSet] u16 mask[index] = 0xFFFF
u64 sub_333940(EEContext& ctx, u64 obj, u64 index);      // [fxMaskIsSet] mask[index] == 0xFFFF
u64 sub_3342C0(EEContext& ctx, u64 obj, u64 arg);        // [fxObj2AttachBoth] sub_3243D0 on +16 and +20
// [fxApplyTint] the tint bytes gp-18348.. into the material colour
u64 sub_337E10(EEContext& ctx, u64 obj);
u64 sub_337F80(EEContext& ctx, u64 obj);                 // [fxKindReleaseFree] sub_3237C0(+0), RwFree(obj)
// [fxApplyTint] the tint bytes gp-18348.. into the material colour
u64 sub_338CE0(EEContext& ctx, u64 obj);
u64 sub_338E50(EEContext& ctx, u64 obj);                 // [fxKindReleaseFree] sub_3237C0(+0), RwFree(obj)
// [kobj12Create] class 12 slot 0: sub_3393D0(u16 +12, fxBlockA)
u64 sub_3394F0(EEContext& ctx, u64 effect);
// [kobj12Destroy] kind destroy (+8) on the params (+60), RwFree(inst)
u64 sub_339530(EEContext& ctx, u64 inst);
u64 sub_3395A0(EEContext& ctx, u64 inst);                // [kobj12Clone] sub_3393D0(kind +56, params +64)
u64 sub_3395D0(EEContext& ctx, u64 inst);                // [kobj12Init] kind init (0x69C650), counter +52 = 0
u64 sub_339620(EEContext& ctx, u64 inst);                // [kobj12Update] kind update (+12), ++counter
u64 sub_339680(EEContext& ctx, u64 inst);                // [kobj12Draw] kind draw (+16) once counted
u64 sub_3396D0(EEContext& ctx, u64 inst);                // [kobj12UpdateDraw] update, ++counter, draw
u64 sub_339760(EEContext& ctx, u64 inst, u64 src);       // [kobj12SetQuad0] +0 = *src
u64 sub_339770(EEContext& ctx, u64 inst, u64 src);       // [kobj12SetQuad16] +16 = *src
u64 sub_339780(EEContext& ctx, u64 inst, u64 value);     // [kobj12SetWord48] +48 = value
u64 sub_339790(EEContext& ctx, u64 inst);                // [kobj12SetScale] +32..+40 = $f12
u64 sub_3397B0(EEContext& ctx, u64 inst, u64 src);       // [kobj12SetScale3] +32..+40 = src[0..2]
u64 sub_339950(EEContext& ctx, u64 block);               // [fxKindRelease] sub_3237C0(block +4), RwFree(block +8)
u64 sub_341FD0(EEContext& ctx, u64 effect);              // [kobj10Create] class 10 slot 0: instance, parameters, init
// [kobj10Destroy] kind destroy (+8) on the params (+60), RwFree(inst)
u64 sub_3420C0(EEContext& ctx, u64 inst);
u64 sub_342130(EEContext& ctx, u64 inst);                // [kobj10Clone] a new instance of the same kind and parameters
u64 sub_342280(EEContext& ctx, u64 inst);                // [kobj10Init] kind init (0x69C850), counter +52 = 0
u64 sub_3422D0(EEContext& ctx, u64 inst);                // [kobj10Update] kind update (+16), ++counter
u64 sub_342330(EEContext& ctx, u64 inst);                // [kobj10Draw] kind draw (+20) once counted
u64 sub_342380(EEContext& ctx, u64 inst);                // [kobj10UpdateDraw] update, ++counter, draw
u64 sub_342410(EEContext& ctx, u64 inst, u64 src);       // [kobj10SetQuad0] +0 = *src
u64 sub_342420(EEContext& ctx, u64 inst, u64 src);       // [kobj10SetQuad16] +16 = *src
u64 sub_342430(EEContext& ctx, u64 inst, u64 value);     // [kobj10SetWord48] +48 = value
u64 sub_342440(EEContext& ctx, u64 inst);                // [kobj10SetScale] +32..+40 = $f12
u64 sub_342460(EEContext& ctx, u64 inst, u64 src);       // [kobj10SetScale3] +32..+40 = src[0..2]
// [fxKindReleaseAtomic] sub_324310(params +4), RwFree(params +8)
u64 sub_342A40(EEContext& ctx, u64 inst);
u64 sub_345DB0(EEContext& ctx, u64 effect);              // [kobj16Create] class 16 slot 0: instance, parameters, init
u64 sub_345EA0(EEContext& ctx, u64 inst);                // [kobj16Destroy] kind destroy (+8), RwFree(inst)
u64 sub_345F00(EEContext& ctx, u64 inst);                // [kobj16Clone] a new instance of the same kind and parameters
u64 sub_345FA0(EEContext& ctx, u64 inst);                // [kobj16Init] kind init (0x69C970), counter +52 = 0
u64 sub_345FF0(EEContext& ctx, u64 inst);                // [kobj16Update] kind update (+16), ++counter
u64 sub_346050(EEContext& ctx, u64 inst);                // [kobj16Draw] kind draw (+20) once counted
u64 sub_3460A0(EEContext& ctx, u64 inst);                // [kobj16UpdateDraw] update, ++counter, draw
u64 sub_346130(EEContext& ctx, u64 inst, u64 src);       // [kobj16SetQuad0] +0 = *src
u64 sub_346140(EEContext& ctx, u64 inst, u64 src);       // [kobj16SetQuad16] +16 = *src
u64 sub_346150(EEContext& ctx, u64 inst, u64 value);     // [kobj16SetWord48] +48 = value
u64 sub_346160(EEContext& ctx, u64 inst);                // [kobj16SetScale] +32..+40 = $f12
u64 sub_346180(EEContext& ctx, u64 inst, u64 src);       // [kobj16SetScale3] +32..+40 = src[0..2]
u64 sub_346500(EEContext& ctx, u64 inst);                // [fxObj7Restart] counter +44 = 0
u64 sub_346510(EEContext& ctx, u64 inst);                // [fxObj7Count] ++counter +44
u64 sub_347130(EEContext& ctx, u64 inst, u64 src);       // [fxObj7SetQuad0] +0 = *src
u64 sub_347140(EEContext& ctx, u64 inst, u64 src);       // [fxObj7SetQuad16] +16 = *src
u64 sub_347150(EEContext& ctx, u64 inst, u64 value);     // [fxObj7SetWord36] +36 = value
u64 sub_347160(EEContext& ctx, u64 inst);                // [fxObj7SetFloat32] +32 = $f12
u64 sub_347300(EEContext& ctx, u64 obj);                 // [fxObj9Destroy] sub_324310(+88), RwFree(obj)
u64 sub_347380(EEContext& ctx, u64 inst);                // [fxObj9Restart] counter +16 = 0
u64 sub_347390(EEContext& ctx, u64 inst);                // [fxObj9Count] ++counter +16
u64 sub_347CE0(EEContext& ctx, u64 inst, u64 src);       // [fxObj9SetQuad0] +0 = *src
u64 sub_347CF0(EEContext& ctx, u64 inst, u64 value);     // [fxObj9SetWord20] +20 = value
u64 sub_347D00(EEContext& ctx);                          // [fxShakeInit] clears the shake state, takes the camera
u64 sub_347D60(EEContext& ctx);                          // [fxShakeUpdate] the per-frame camera shake
u64 sub_347F80(EEContext& ctx);                          // [fxShakeStop] camera back to 0x957A90
u64 sub_348100(EEContext& ctx, u64 inst);                // [fxObj21Restart] frame +0 = 0
// [fxShakeStart] weight and amplitudes of a screen shake, active byte = 1
u64 sub_348110(EEContext& ctx, u64 rec, u64 frame);
u64 sub_3482B0(EEContext& ctx, u64 inst);                // [fxObj21Update] sub_348110(inst + 4, frame), ++frame
u64 sub_3482F0(EEContext& ctx);                          // [fxObj21Nop] empty slot
u64 sub_348300(EEContext& ctx, u64 inst);                // [fxObj21UpdateDraw] sub_348110(inst + 4, frame), ++frame
u64 sub_34B510(EEContext& ctx, u64 inst);                // [fxFilterRestart] frame +28 = 0
u64 sub_34B520(EEContext& ctx, u64 inst);                // [fxFilterUpdate] kind update (0x69CB98), ++frame
u64 sub_34B580(EEContext& ctx, u64 inst);                // [fxFilterDraw] kind slot 1 (0x69CB9C)
u64 sub_34B5C0(EEContext& ctx, u64 inst);                // [fxFilterNotify] sub_321180 after the first frame
u64 sub_34B680(EEContext& ctx, u64 inst, u64 src);       // [fxFilterSetQuad] +0 = *src (128 bits)
u64 sub_34B690(EEContext& ctx, u64 inst, u64 value);     // [fxFilterSetWord] +16 = value
u64 sub_34B6A0(EEContext& ctx, u64 inst);                // [fxFilterSetFloat] +20 = $f12
u64 sub_34BA20(EEContext& ctx, u64 inst);                // [fxFilter2Restart] frame +28 = 0
u64 sub_34BA30(EEContext& ctx, u64 inst);                // [fxFilter2Update] kind update (0x69CC58), ++frame
u64 sub_34BA90(EEContext& ctx, u64 inst);                // [fxFilter2Draw] kind slot 1 (0x69CC5C)
u64 sub_34BAD0(EEContext& ctx, u64 inst);                // [fxFilter2Notify] sub_3211D0 after the first frame
u64 sub_34BB90(EEContext& ctx, u64 inst, u64 src);       // [fxFilter2SetQuad] +0 = *src (128 bits)
u64 sub_34BBA0(EEContext& ctx, u64 inst, u64 value);     // [fxFilter2SetWord] +16 = value
u64 sub_34BBB0(EEContext& ctx, u64 inst);                // [fxFilter2SetFloat] +20 = $f12
u64 sub_34BCF0(EEContext& ctx, u64 obj);                 // [fxRefInc] ++(+4), returns the object
// [fxScreenSizeInit] the raster and its size as floats at 0x957BA8..
u64 sub_34BD10(EEContext& ctx);

}  // namespace p3fes::game
