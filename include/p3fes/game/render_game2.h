// Phase 5 slice render_game2: the game-side draw layer, second pass (docs/ANALYSIS/22_rendering.md sections 1, 2, 6
// and 7.3; the `[game]` rows of docs/ANALYSIS/queue_rendering.txt that render_game left). Hand-decompiled from
// SLUS_216.21 into game/src/render/render_game2.cpp; tests/game/test_render_game2.cpp pairs every function with its
// recompiled body.
//
// What is here, by group (each declaration below names the role; `sub_*` keep their symbols/functions.json name, a
// bracketed name is a proposal, not imported):
//   [mask]    the four raw VIF packets the game builds itself through _rwDMAOpenVIFPkt (22_rendering.md section 2.1):
//             FRAME_1 with the colour channels masked and back, CLAMP_1 set and back.
//   [screen]  the full-screen effect callbacks of the 0x348000 band (one 272- or 592-byte frame holding a 4-vertex
//             RwIm2DVertex strip, the alpha / frame-mask packets around an indexed tri-list of the shared index table
//             0x69CB80).  (A+D data: FRAME_1 = GS register 0x4C, CLAMP_1 = 0x08.)
//   [pass]    kwln draw tasks that open and close a camera pass: the 2D pass "2D Draw Begin", the debug-shape passes,
//             the field passes over the model draw sub_317A20 and the culled atomic lists.
//   [cull]    the model draw's atomic lists (22_rendering.md section 2.2, hot class c7): per atomic the world bounding
//             sphere against the camera frustum, fog off / on per node, the list's enable word, the atomic's render
//             callback (+0x48) through jalr; the translucent ones sorted and drawn back to front.
// Everything below RenderWare's API (RwCameraBegin/EndUpdate, RpSkyRenderStateSet, the device pointers 0x960090 ..
// 0x9600A4, _rwDMAOpenVIFPkt) is called exactly where the original calls it: still-recompiled callees through their
// generated entry points (`jal`), the device pointers through the dispatch table (`jalr`) with the original `$ra`.
//
// Register contract (docs/PHASE5_AGENT_BRIEF.md waves 6, 7 and 10): every check point can preempt the thread and the
// kernel then saves the whole register file in guest memory, the RenderWare callees spill what they receive and game
// code reads what a callee leaves behind. So these bodies are register-faithful: at every check point, call and
// return each GPR (128 bits), HI/LO, FPR, ACC and FCR31 holds what the original holds there, and the prologues write
// the original spills (128-bit `sq` slots included). They run on the Cpu view below (one named variable per guest
// register, as core3.cpp); reads of the guest registers and of the cycle counter go through volatile accesses (the
// wave-10 lesson: MSVC /O2 kept ctx.cycles in a host register across a call to a small charging helper).
#pragma once

#include "p3fes/ee/core.h"
#include "p3fes/game/guest.h"
#include "p3fes_recomp_rt.h"

#include <cstring>

namespace p3fes::game {

// --- [mask] the game's own VIF packets (each: _rwDMAOpenVIFPkt(0x80000000, 2), then one cnt tag + an A+D pair) ---
void sub_3294D0(EEContext& ctx);          // [FRAME_1 = RW's shadow | FBMSK 0x00FFFFFF]: only alpha is written
void sub_329550(EEContext& ctx);          // [FRAME_1 = RW's shadow (gp-17080)]: the mask off
void sub_3295C0(EEContext& ctx, u64 clamp);  // [CLAMP_1 = the 64-bit $a0]
void sub_329630(EEContext& ctx);          // [CLAMP_1 = RW's shadow (gp-17048)]

// --- [screen] the full-screen effect callbacks of the 0x348000 band ($a0 = the effect object; +36 its params) ---
void sub_34ADA0(EEContext& ctx, u64 obj);  // [screen quad (params +195 > 0): vertices sub_348BD0, untextured]
void sub_34A800(EEContext& ctx, u64 obj);  // [screen quad (params +195): vertices sub_348950, the 0x957BA8 raster, frame mask]
void sub_349A30(EEContext& ctx, u64 obj);  // [screen quad (params +195): vertices sub_348340 when it returns non-zero]
void sub_348DA0(EEContext& ctx, u64 params, u64 raster_ref);  // [two-layer screen pass: sub_348760 + sub_348340 quads, alpha tests]
void sub_34B010(EEContext& ctx, u64 obj);  // [two-layer screen pass (params +207): sub_348BD0 quads, the first with UVs reset]
void sub_349D30(EEContext& ctx, u64 obj);  // [two-layer screen pass (params +199): sub_348760 + sub_348340 quads]

// --- [pass] camera passes (kwln task callbacks: $a0 = the task, 0 returned = keep running) ---
u64 kwlnRootUpdate2DDrawBeginTask(EEContext& ctx, u64 task);  // 0x1989E0 "2D Draw Begin" (prio 4196): Z clear, BeginUpdate, Im2D states, sprites
u64 sub_1A4C10(EEContext& ctx, u64 task);  // [a debug-shape pass: sub_359380(work, 1) at 60.0, sub_359B40(work + 48, work + 68, 1) at 20.0]
u64 sub_1AE290(EEContext& ctx, u64 task);  // [the collision-cylinder debug pass: position of the target's frame, sub_359B40]
u64 sub_3962C0(EEContext& ctx, u64 task);  // [the dds3 debug-object pass: dbgDrawRect, sub_395810, one-shot sub_386E50 / sub_359B40, sub_395950]
u64 sub_1A50F0(EEContext& ctx, u64 task);  // [a single-atomic task: frame from a model's root LTM, culled, drawn in its own pass]

// --- [cull] the model's atomic lists (c7: per atomic per frame; render_game2.cpp documents the 44-byte nodes) ---
void sub_1A7B50(EEContext& ctx, u64 lists, u64 mode);  // [the opaque passes: lists +8 / +20 / +24 / +28] (22_rendering.md 2.2)
void sub_1A7FC0(EEContext& ctx, u64 lists, u64 mode);  // [the all-opaque-materials pass: list +32]
void sub_1A8140(EEContext& ctx, u64 lists, u64 mode);  // [the translucent passes: +12 / +16 / +20 / +40 / +36, kind-1 alphas queued]
void sub_1A8B10(EEContext& ctx, u64 queue);  // [the sorted translucent queue: qsort, back to front, per-kind blend]
void sub_315C20(EEContext& ctx, u64 model);  // [a model's atomic passes with its own states (flags +216: fade, whole, own states)]

// --- [shape] debug shapes (Im3D lines, a projected Im2D circle; `save` brackets the six states of 0x69CE60) ---
void sub_359110(EEContext& ctx, u64 a, u64 b, u64 colour, u64 save);  // [one Im3D line a -> b in an RwRGBA]
void sub_359560(EEContext& ctx, u64 centre, u64 colour, u64 matrix, u64 save, u32 radius_bits);  // [a 20-segment circle, projected]
void sub_359B40(EEContext& ctx, u64 centre, u64 colour, u64 save, u32 radius_bits);  // [a wire sphere of 2 x 9 circles]
void sub_359E50(EEContext& ctx, u64 centre, u64 colour, u64 save, u32 radius_bits, u32 height_bits);  // [a wire cylinder]

// --- [field] the field's model passes (kwln draw tasks: $a0 = the task, 0 returned) ---
u64 sub_19D530(EEContext& ctx, u64 task);  // "draw trans field sort" (prio 4183): the sorted translucent queue with the field lights
u64 sub_19DB10(EEContext& ctx, u64 task);  // [the opaque NPC pass: list 10 through sub_317A20 when sub_1A7660 == 1]
u64 sub_19DE80(EEContext& ctx, u64 task);  // [the translucent NPC pass: the same with sub_1A76E0]
u64 sub_19F470(EEContext& ctx, u64 task);  // "draw persona model" (prio 4168): list 2 with each resource's own lights
u64 K_SceneDraw_UpdateDrwOpcFldObjTask(EEContext& ctx, u64 task);  // 0x19D780 "draw opaque field obj" (prio 2071)
u64 sub_188250(EEContext& ctx, u64 task);  // [the HUD calendar task: sprite file, then sub_187EC0 in a fog-off pass]
u64 sub_41BAF0(EEContext& ctx, u64 task);  // [an event 3-D pass over the task's objects: models, Im3D models, line objects]

// --- [model] the model draw ---
void sub_317A20(EEContext& ctx, u64 model);  // [the model draw: states, material animation, the atomic passes, shadow, attachments, children, outline]

// --- [fldsrc] the field world passes ($a0 = the camera, $a1 = the field resource) ---
u64 K_FldSrc_DrawFieldOpaque(EEContext& ctx, u64 camera, u64 res);  // 0x1B3E50 the opaque field world (RpWorldRender or the res's atomics)
u64 K_FldSrc_DrawFieldTrans(EEContext& ctx, u64 camera, u64 res);  // 0x1B4720 the translucent field parts

// --- [battle] the battle front pass and full-screen quads ---
void sub_358460(EEContext& ctx, u64 colour, u64 save);  // [a full-screen Im2D strip in an RwRGBA (the alpha clear of the front pass)]
void sub_29E4B0(EEContext& ctx);  // [the battle screen flash: gBtl +564..+576]
void sub_2891E0(EEContext& ctx);  // [the battle front pass: the units' models sorted, the masked alpha clear]
u64 sub_19EF80(EEContext& ctx, u64 task);  // "draw trans NPC sort" (prio 4183): the translucent NPCs back to front

// --- [font] the text draw ---
u64 frFontDraw(EEContext& ctx, u64 text, u64 mode);  // 0x3B1360 a laid-out text, glyph by glyph; returns the width (0 while fading / waiting)

// --- [rect] menu rectangles ($f12 depth offset, $f13 / $f14 x / y) and [quad] small panels ---
void sub_113A30(EEContext& ctx, u64 rgba, u64 w, u64 h, u32 depth_bits, u32 x_bits, u32 y_bits);  // [plain, alpha ref 68]
void sub_113D80(EEContext& ctx, u64 rgba, u64 w, u64 h, u32 depth_bits, u32 x_bits, u32 y_bits);  // [plain, alpha ref 72]
void sub_1140D0(EEContext& ctx, u64 rgba, u64 w, u64 h, u64 raster_ref, u32 depth_bits, u32 x_bits, u32 y_bits);  // [textured, 68]
void sub_114AF0(EEContext& ctx, u64 rgba, u64 w, u64 h, u64 raster_ref, u32 depth_bits, u32 x_bits, u32 y_bits);  // [textured, 72]
void sub_3B4B40(EEContext& ctx, u64 points, u64 colours, u64 point_idx, u64 colour_idx);  // [a gouraud quad (fan) in 0x95AEC0]
void sub_139DC0(EEContext& ctx, u32 depth_bits);  // [a black triangle in the lower right corner]

// --- [panel] battle / result panels (quads of two Im2D triangles) ---
void sub_2720C0(EEContext& ctx);  // [the gp-18740 panel quad]
void sub_2532B0(EEContext& ctx);  // [the gp-18848 panel's N quads, raster 76]
void sub_22C5A0(EEContext& ctx);  // [the gp-18920 panel's three quads, raster 66]
void sub_27B880(EEContext& ctx);  // [the gp-18700 panel quad, raster 58]
void sub_23C8C0(EEContext& ctx, u64 verts);  // [two quads with the sprite of sub_20E590(1)]
u64 sub_411EE0(EEContext& ctx, u64 unused, u64 work);  // [five glyph slots (sub_40E420), a backing panel for the fourth]
void sub_25BBF0(EEContext& ctx);  // [the gp-18828 panel's three quad pairs]
void sub_2520F0(EEContext& ctx);  // [the gp-18852 panel's three quads, raster 57 / 58]

// --- [capture] the screen-capture fade task ---
u64 sub_351290(EEContext& ctx, u64 work);  // [copy the frame buffer into the 512 x 256 capture raster]
void sub_351510(EEContext& ctx, u64 work);  // [the captured frame over the screen, alpha fading out]
void sub_351940(EEContext& ctx, u64 work);  // [release the capture camera and raster]
u64 sub_351A10(EEContext& ctx, u64 task);  // [the capture fade's state machine: create, capture, fade, release]

// --- [im3d] event line objects ---
void sub_41BF80(EEContext& ctx, u64 obj);  // [an Im3D line object, camera-relative or not]
void sub_20D500(EEContext& ctx, u64 obj, u64 matrix);  // [an indexed Im3D mesh, optionally turned 180 degrees]

// --- the second half (game/src/render/render_game2_hg.cpp): started from p3fes_handgen's register-faithful bodies,
// register ABI (arguments in $a0.., the result in $v0); the roles are documented above each body there ---
void sub_1059B0(EEContext& ctx);  // [the bust-up portrait task: list file -> texture -> draw, blinking eyes / mouth]
void sub_107B20(EEContext& ctx);  // [a camp fade layer: the cached effect file, its effect objects and the panel]
void sub_1071F0(EEContext& ctx);  // [the camp fade .anm sprites of one of four fade kinds]
void sub_111610(EEContext& ctx);  // [the MAESTRO stream: open the file, find its chunk, render into a sub-camera]
void sub_1127D0(EEContext& ctx);  // [a sprite: four RwIm2DVertex, flips, rotation, scale, colour, the raster states]
void sub_114450(EEContext& ctx);  // [a nine-slice menu window from three rasters]
void sub_114E70(EEContext& ctx);  // [a menu bar from repeated raster strips]
void sub_115350(EEContext& ctx);  // [a menu frame with a gradient body]
void sub_124FD0(EEContext& ctx);  // [a numbered sprite label: sprintf the name, the sprite and its digits]
void sub_199D90(EEContext& ctx);  // [a kwln Im3D draw task: the transformed line list]
void sub_19A420(EEContext& ctx);  // [a kwln Im3D draw task in a frame's space]
void sub_19AB80(EEContext& ctx);  // [the field grid debug lines around the player's cell]
void sub_19BCF0(EEContext& ctx);  // [a kwln root task's destroy: its camera, rasters and frame]
void sub_2095A0(EEContext& ctx);  // [a battle-panel sprite group (baus_main.c)]
void sub_2496E0(EEContext& ctx);  // [Shuffle Time's particle tank: 128 particles in a random cube]
void sub_249C10(EEContext& ctx);  // [the particle tank's per-frame update and draw]

namespace rg2 {

namespace core = ee::core;

// --- R5900 integer results (32-bit operations sign-extend into the 64-bit register) ---
constexpr u64 sx(u32 v) { return core::sext32(v); }
constexpr s64 sgn(u64 v) { return static_cast<s64>(v); }
constexpr u64 addu(u64 a, u64 b) { return core::add32(a, b); }
constexpr u64 addiu(u64 a, s32 i) { return core::add32i(a, i); }
constexpr u64 daddiu(u64 a, s32 i) { return core::add64i(a, i); }
constexpr u64 subu(u64 a, u64 b) { return core::sub32(a, b); }
constexpr u64 lui(u32 i) { return core::lui(i); }
constexpr u64 sll(u64 a, unsigned n) { return core::sll(a, n); }
constexpr u64 srl(u64 a, unsigned n) { return core::srl(a, n); }
constexpr u64 sra(u64 a, unsigned n) { return core::sra(a, n); }
constexpr u64 dsll(u64 a, unsigned n) { return core::dsll(a, n); }
constexpr u64 dsrl(u64 a, unsigned n) { return core::dsrl(a, n); }
constexpr u64 dsra(u64 a, unsigned n) { return core::dsra(a, n); }
constexpr u64 dsll32(u64 a, unsigned n) { return core::dsll32(a, n); }
constexpr u64 dsrl32(u64 a, unsigned n) { return core::dsrl32(a, n); }
constexpr u64 dsra32(u64 a, unsigned n) { return core::dsra32(a, n); }
constexpr u64 nor_(u64 a, u64 b) { return ~(a | b); }
constexpr u64 slt(u64 a, u64 b) { return core::slt(a, b); }
constexpr u64 sltu(u64 a, u64 b) { return core::sltu(a, b); }
constexpr u64 slti(u64 a, s32 i) { return core::slti(a, i); }
constexpr u64 sltiu(u64 a, s32 i) { return core::sltiu(a, i); }
constexpr u32 w(u64 v) { return static_cast<u32>(v); }

// One GPR of the guest context; reads and writes go through volatile lvalues (a compiler barrier: nothing of the
// guest state is cached in host registers across a helper or a call).
struct Gpr {
    EEContext& c;
    const unsigned r;
    operator u64() const noexcept { return static_cast<const volatile u64&>(c.gpr[r].u64[0]); }
    u32 u() const noexcept { return static_cast<const volatile u32&>(c.gpr[r].u32[0]); }
    Gpr& operator=(u64 v) noexcept {
        if (r != 0) static_cast<volatile u64&>(c.gpr[r].u64[0]) = v;
        return *this;
    }
    Gpr& operator=(const Gpr& o) noexcept { return *this = static_cast<u64>(o); }
};

// FPR numbers.
enum : unsigned {
    F0, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15,
    F16, F17, F18, F19, F20, F21, F22, F23, F24, F25, F26, F27, F28, F29, F30, F31
};

// The RenderWare device pointers the draw code calls (symbols/p3fes.sym).
constexpr u32 kPfnRenderStateSet = 0x960090u;             // RwRenderStateSet(state, value)
constexpr u32 kPfnRenderStateGet = 0x960094u;             // RwRenderStateGet(state, &value)
constexpr u32 kPfnIm2DRenderTriangle = 0x96009Cu;         // RwIm2DRenderTriangle(verts, n, i0, i1, i2)
constexpr u32 kPfnIm2DRenderPrimitive = 0x9600A0u;        // RwIm2DRenderPrimitive(prim, verts, n)
constexpr u32 kPfnIm2DRenderIndexedPrimitive = 0x9600A4u; // RwIm2DRenderIndexedPrimitive(prim, verts, n, idx, ni)

// The guest machine as the bodies see it.
class Cpu {
public:
    explicit Cpu(EEContext& ctx) noexcept : c(ctx) {}

    EEContext& c;
    Gpr zero{c, 0}, at{c, 1}, v0{c, 2}, v1{c, 3}, a0{c, 4}, a1{c, 5}, a2{c, 6}, a3{c, 7};
    Gpr t0{c, 8}, t1{c, 9}, t2{c, 10}, t3{c, 11}, t4{c, 12}, t5{c, 13}, t6{c, 14}, t7{c, 15};
    Gpr s0{c, 16}, s1{c, 17}, s2{c, 18}, s3{c, 19}, s4{c, 20}, s5{c, 21}, s6{c, 22}, s7{c, 23};
    Gpr t8{c, 24}, t9{c, 25}, gp{c, 28}, sp{c, 29}, fp{c, 30}, ra{c, 31};

    // virtual time (ADR-0013): enter = the entry check point + the first block, charge = one block, backedge = the
    // loop check point; enter / backedge are not noexcept (a check point's fatal event must unwind)
    void enter(u64 n) {
        rt::check_events(c);
        charge(n);
    }
    void charge(u64 n) noexcept {
        volatile u64& t = c.cycles;
        t = t + n;
    }
    void backedge() { rt::check_events(c); }

    // loads / stores: the runtime's own instructions with base $zero and the 32-bit address as the offset
    // (`lw(v0, a)` = `lw $v0, a($zero)`), so an unaligned or unmapped address, the BIOS window and the hardware
    // windows (bus + check point) behave exactly as in the recompiled body (brief, wave-10 lesson; the 2026-10-21
    // faithfulness audit found the first version, on guest::load / store, reading through pointers the original
    // faults on). Not noexcept: a fault is a fatal event that unwinds.
    static s32 off(u64 a) noexcept { return static_cast<s32>(w(a)); }
    void lw(Gpr& d, u64 a) { rt::lw(c, d.r, GPR_ZERO, off(a)); }
    void lwu(Gpr& d, u64 a) { rt::lwu(c, d.r, GPR_ZERO, off(a)); }
    void lh(Gpr& d, u64 a) { rt::lh(c, d.r, GPR_ZERO, off(a)); }
    void lhu(Gpr& d, u64 a) { rt::lhu(c, d.r, GPR_ZERO, off(a)); }
    void lb(Gpr& d, u64 a) { rt::lb(c, d.r, GPR_ZERO, off(a)); }
    void lbu(Gpr& d, u64 a) { rt::lbu(c, d.r, GPR_ZERO, off(a)); }
    void ld(Gpr& d, u64 a) { rt::ld(c, d.r, GPR_ZERO, off(a)); }
    void lq(Gpr& d, u64 a) { rt::lq(c, d.r, GPR_ZERO, off(a)); }
    // stores take the value (a register or what the original's source register holds): the fast path of rt's
    // store, else its slow path with the same address and width
    template <class T, rt::detail::StoreKind K> void store(u64 a, u64 v) {
        const u32 va = w(a);
        if (u8* p = rt::detail::fast_ptr(c, va, sizeof(T))) {
            const T x = static_cast<T>(v);
            std::memcpy(p, &x, sizeof(T));
            return;
        }
        u128 q{};
        q.u64[0] = v;
        rt::detail::store_slow(c, va, q, K);
    }
    void sw(u64 a, u64 v) { store<u32, rt::detail::StoreKind::sw>(a, v); }
    void sh(u64 a, u64 v) { store<u16, rt::detail::StoreKind::sh>(a, v); }
    void sb(u64 a, u64 v) { store<u8, rt::detail::StoreKind::sb>(a, v); }
    void sd(u64 a, u64 v) { store<u64, rt::detail::StoreKind::sd>(a, v); }
    void sq(u64 a, const Gpr& v) { rt::sq(c, v.r, GPR_ZERO, off(a)); }

    // FPU (the runtime's instruction semantics: EE singles, ACC, FCR31 flags)
    u32 f(unsigned r) const noexcept { return static_cast<const volatile u32&>(c.fpr[r]); }
    void setf(unsigned r, u32 bits) noexcept { static_cast<volatile u32&>(c.fpr[r]) = bits; }
    void lwc1(unsigned r, u64 a) { rt::lwc1(c, r, GPR_ZERO, off(a)); }
    void swc1(unsigned r, u64 a) { rt::swc1(c, r, GPR_ZERO, off(a)); }
    void mtc1(const Gpr& g, unsigned r) noexcept { rt::mtc1(c, g.r, r); }
    void mfc1(Gpr& g, unsigned r) noexcept { rt::mfc1(c, g.r, r); }
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
    void suba_s(unsigned s, unsigned t) noexcept { rt::suba_s(c, s, t); }
    void mula_s(unsigned s, unsigned t) noexcept { rt::mula_s(c, s, t); }
    void madda_s(unsigned s, unsigned t) noexcept { rt::madda_s(c, s, t); }
    void msuba_s(unsigned s, unsigned t) noexcept { rt::msuba_s(c, s, t); }
    void madd_s(unsigned d, unsigned s, unsigned t) noexcept { rt::madd_s(c, d, s, t); }
    void msub_s(unsigned d, unsigned s, unsigned t) noexcept { rt::msub_s(c, d, s, t); }
    void c_eq_s(unsigned s, unsigned t) noexcept { rt::c_eq_s(c, s, t); }
    void c_lt_s(unsigned s, unsigned t) noexcept { rt::c_lt_s(c, s, t); }
    void c_le_s(unsigned s, unsigned t) noexcept { rt::c_le_s(c, s, t); }
    bool cop1_cond() const noexcept { return rt::cop1_cond(c); }

    // HI/LO and MMI (all 128 bits of the destination)
    void mult(Gpr& d, const Gpr& s, const Gpr& t) noexcept { rt::mult(c, d.r, s.r, t.r); }
    void multu(Gpr& d, const Gpr& s, const Gpr& t) noexcept { rt::multu(c, d.r, s.r, t.r); }
    void div(const Gpr& s, const Gpr& t) noexcept { rt::div(c, s.r, t.r); }
    void divu(const Gpr& s, const Gpr& t) noexcept { rt::divu(c, s.r, t.r); }
    void mflo(Gpr& d) noexcept { rt::mflo(c, d.r); }
    void mfhi(Gpr& d) noexcept { rt::mfhi(c, d.r); }
    void pcpyld(Gpr& d, const Gpr& s, const Gpr& t) noexcept { rt::pcpyld(c, d.r, s.r, t.r); }
    void pextlw(Gpr& d, const Gpr& s, const Gpr& t) noexcept { rt::pextlw(c, d.r, s.r, t.r); }

    // calls: `jal fn` at pc ($ra = pc + 8; the delay slot's instruction is written before the call), `jalr target`
    // at pc (through the dispatch table), a static tail call (`j fn`)
    void jal(u32 pc, rt::Fn fn) {
        rt::jal(c, pc);
        fn(c);
    }
    void jalr(u32 pc, u32 target) {
        rt::jalr(c, GPR_RA, pc);
        rt::lookup_func(target)(c);
    }
    void tailcall(rt::Fn fn) { fn(c); }
    // `lw $v0, pfn; jalr $v0` (`lui $v0, 0x96; lw $v0, lo($v0)` when the address is not kept in a register)
    void call_pfn(u32 pc, u32 pfn) {
        lw(v0, pfn);
        jalr(pc, v0.u());
    }

    // --- the bodies (render_game2.h documents each; named as the functions they are) ---
    // [mask]
    void vif_ad_head(u32 pc);
    void sub_3294D0();
    void sub_329550();
    void sub_3295C0();
    void sub_329630();
    // [screen]
    void im2d_state_raster(u32 pc_raster, u32 pc_state);
    void im2d_indexed_quad(u32 pc, s32 verts);
    void clamp_to_screen(u32 pc);
    void sub_34ADA0();
    void sub_34A800();
    void sub_349A30();
    void sub_348DA0();
    void layer_pass(u32 base, u32 tail_cost);
    void sub_34B010();
    void sub_349D30();
    // [pass]
    void camera_get(u32 pc);
    void camera_begin(u32 pc_get, u32 pc_begin);
    void camera_end(u32 pc_get, u32 pc_end);
    void kwlnRootUpdate2DDrawBeginTask();
    void sub_1A4C10();
    void sub_1AE290();
    void sub_3962C0();
    void sub_1A50F0();
    // [cull]
    template <class Body> void walk_nodes(Gpr& node, Body body);
    bool atomic_visible(const Gpr& node, u32 pc);
    void fog_off_if_flagged(const Gpr& node, Gpr& x, Gpr& y, u32 pc);
    void render_if_enabled(s32 gp_flag, const Gpr& node, Gpr& x, Gpr& y, u32 pc);
    void render_atomic(const Gpr& node, u32 pc);
    void fog_on_if_flagged(const Gpr& node, Gpr& x, u32 pc);
    void ztest_states(const Gpr& mode, Gpr& base, u32 pc, u32 zwrite);
    void sky_states(u32 pc, u32 ref, u32 lo);
    bool geometry_scan(const Gpr& node, Gpr& x, s32 slot, u32 pc);
    bool queue_translucent(const Gpr& node, Gpr& x, Gpr& y, s32 gp_flag, u32 pc);
    void sub_1A7B50();
    void sub_1A7FC0();
    void sub_1A8140();
    void sub_1A8B10();
    void sub_315C20();
    // [shape]
    void states_push(Gpr& i, Gpr& entry, s32 slot, u32 pc_get, u32 pc_tex, u32 ref = 72, u32 lo = 0x1801);
    void states_pop(s32 slot, u32 pc);
    void identity_matrix(s32 m);
    void byte_to_f0();
    void sub_359110();
    void sub_359560();
    void sub_359B40();
    void sub_359E50();
    // [field]
    void light_colour_save(u32 pc, rt::Fn getter, s32 slot);
    void light_frame_save(u32 pc, rt::Fn getter, s32 slot);
    void light_colour_set(u32 pc, rt::Fn getter, const Gpr& base, s32 off);
    void light_frame_set(u32 pc, rt::Fn getter, const Gpr& base, s32 off);
    void field_lights_on(u32 pc);
    void world_light(u32 pc, rt::Fn fn);
    void field_lights_restore(u32 pc, s32 amb, s32 dir, s32 mat);
    void dir_light_flags(u32 pc);
    void root_fog_on(u32 pc);
    void npc_pass(u32 delta, rt::Fn predicate, u32 line);
    void sub_19D530();
    void sub_19DB10();
    void sub_19DE80();
    void sub_19F470();
    void K_SceneDraw_UpdateDrwOpcFldObjTask();
    void sub_188250();
    void sub_41BAF0();
    // [model]
    void u8_to_float(unsigned ftmp, unsigned fdst);
    void sub_317A20();
    // [fldsrc]
    void fldsrc_lights_prologue(u32 b);
    void fldsrc_lights_epilogue(u32 b);
    void world_pair_lights(u32 pc, s32 off, rt::Fn fn);
    void root_world_lights(u32 pc, rt::Fn fn);
    void fldsrc_pass_states(u32 pc);
    s32 fldsrc_world_slot();
    void K_FldSrc_DrawFieldOpaque();
    void K_FldSrc_DrawFieldTrans();
    // [battle]
    void u2f(Gpr& src, Gpr& hi, Gpr& lo, unsigned ftmp, unsigned fdst);
    void sub_358460();
    void sub_29E4B0();
    void sub_2891E0();
    void sub_19EF80();
    // [font]
    void font_wait_tick(u64 tail);
    void frFontDraw();
    // [rect] / [quad]
    void menu_rect(u32 start, u32 ref, u32 blend_lo, bool textured);
    void sub_113A30();
    void sub_113D80();
    void sub_1140D0();
    void sub_114AF0();
    void im2d_states(const u32 (*states)[2], u32 n, u32 pc);
    void sub_3B4B40();
    void sub_139DC0();
    // [panel]
    void quad_triangles(const Gpr& reg, s32 off, Gpr& base, u32 pc);
    void panel_work_check(s32 slot, u32 file, u32 line, u32 pc);
    void panel_raster(u32 id, u32 pc_cca0, u32 pc_raster, bool via_s0);
    void sub_2720C0();
    void sub_2532B0();
    void sub_22C5A0();
    void sub_27B880();
    void sub_23C8C0();
    void sub_411EE0();
    void sub_25BBF0();
    void sub_2520F0();
    // [capture]
    void capture_states(u32 pc, const Gpr& raster);
    void sub_351290();
    void sub_351510();
    void sub_351940();
    void sub_351A10();
    // [im3d]
    void copy_matrix_words();
    void sub_41BF80();
    void sub_20D500();
};

}  // namespace rg2

}  // namespace p3fes::game
