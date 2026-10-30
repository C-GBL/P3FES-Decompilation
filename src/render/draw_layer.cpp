// The game-side draw layer (game/include/p3fes/game/draw_layer.h), hand-decompiled from SLUS_216.21
// (docs/ANALYSIS/22_rendering.md sections 1, 2.4 and 6). Phase 5: these replace the recompiled bodies listed in
// game/replaced.txt under "render_game"; tests/game/test_render_game.cpp runs each against its __recomp body.
//
// Two kinds of function live here. The camera passes are kwln task update callbacks (22_rendering.md section 1
// table): each opens or closes the main camera's update (RwCameraBeginUpdate / RwCameraEndUpdate, which emit the
// draw-environment packet and, on the first Begin of a frame, wait for the DMA queue), clears Z, and sets the
// pass's render states through the RenderWare device pointer RwRenderStateSet. The Im2D builders fill
// screen-space RwIm2DVertex records (z = the near screen z, recipZ = 1 / near plane, colour as floats 0..255)
// and draw them through the Im2D device pointers (section 6): the menu cursor, the three screen fades, the
// day HUD's moon, a debug rectangle and two battle panels.
//
// Virtual time per ADR-0013: block costs from recomp/generated (`ctx.cycles += N`), charged at the start of each
// block, before any call inside it, so every callee reaches its check point at the same virtual time;
// `guest::backedge` stands where the recompiled loop checks (these loops test first, so they check before every
// iteration, the first included).
//
// Register discipline. These frames are live on the guest stack while RenderWare runs below them (a snapshot can
// be taken while RwCameraBeginUpdate waits for the DMA queue), and RenderWare's own frames hold the s-registers
// and $ra these functions pass down. So, as in the kwln task kernel (task.h), every function writes its original
// prologue spills to the guest stack (draw::Frame, including the $f20..$f23 spills), keeps the s-registers and
// $f20.. holding what the original kept there at every call, gives $ra the link value of the original jal/jalr,
// and leaves every caller-saved register the original writes ($v0/$v1, $a0..$a3, $t0..$t2, $f0..$f6, HI/LO, the
// FCR31 flags of div.s) holding the original's value at every call and at the return. Vertex arrays on the stack
// stay on the guest stack at the original offsets: their unwritten words are whatever the previous callee left
// there, and RenderWare reads them.
//
// K_Assert (sub_19D3F0) is `jr $ra` in retail: a failed check continues, as in the original.
//
// Faithfulness audit (2026-10-21, tools/ours/audit): 9 of the 28 functions here are now p3fes_handgen's register-
// faithful bodies (their hand versions differed from the original: frame/spills 4, faults only 3, callee frames 2);
// each keeps the notes of its earlier hand version above it. The others are the hand-written versions this header
// describes.
#include "p3fes/game/draw_layer.h"

#include "p3fes/ee/core.h"
#include "p3fes/ee/fpu.h"
#include "p3fes/ee/hilo.h"
#include "p3fes/game/ui.h"
#include "p3fes/game/hg_cpu.h"

namespace p3fes::recomp_gen {
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);  // K_Assert(file, line)
void fn_sub_198590_00198590(p3fes::EEContext&);  // kwlnRootGetCamera: *(gp-19504)
void fn_sub_1985A0_001985a0(p3fes::EEContext&);  // kwlnRootGetClearColour: gp-19400
void fn_kwlnSetFlags_00198610(p3fes::EEContext&);  // kwlnSetFlags(mask, on)
void fn_kwlnTaskIsBandAEnabled_00195750(p3fes::EEContext&);  // kwlnTaskIsBandAEnabled
void fn_kwlnTaskDestroyWithHierarchy_00195020(p3fes::EEContext&);  // kwlnTaskDestroyWithHierarchy(task)
void fn_RwCameraEndUpdate_004c9d00(p3fes::EEContext&);  // RwCameraEndUpdate(camera)
void fn_RwCameraBeginUpdate_004c9d10(p3fes::EEContext&);  // RwCameraBeginUpdate(camera)
void fn_RwCameraClear_004c9e90(p3fes::EEContext&);  // RwCameraClear(camera, colour, flags)
void fn_sub_1A8910_001a8910(p3fes::EEContext&);  // the shadow node camera update (0x8668F0)
void fn_sub_27A3B0_0027a3b0(p3fes::EEContext&);  // the battle message draw (frFontDraw)
void fn_sub_321120_00321120(p3fes::EEContext&);  // battle effect pass(n)
void fn_sub_27F160_0027f160(p3fes::EEContext&);  // battle draw list(n)
void fn_sub_287400_00287400(p3fes::EEContext&);
void fn_sub_2BB3A0_002bb3a0(p3fes::EEContext&);  // battle effects + models
void fn_sub_2A48F0_002a48f0(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);  // datGetFlag(id)
void fn_sub_266E50_00266e50(p3fes::EEContext&);  // battle panel raster(n)
void fn_frFontCacheGlyph_003b0430(p3fes::EEContext&);    // frFontCacheGlyph(font, glyph) -> glyph node
void fn_fmGslReleaseEntry_003b4580(p3fes::EEContext&);   // fmGslReleaseEntry(entry)
void fn_memset_00521408(p3fes::EEContext&);
void fn_sub_196770_00196770(p3fes::EEContext&);  // save 18 render states (RwRenderStateGet into 0x847EB0)
void fn_dbgPrintDrawStrings_00104710(p3fes::EEContext&);  // debug overlay list (gp-20008)
void fn_dbgPrintDrawWindow_001053f0(p3fes::EEContext&);  // debug overlay list (gp-20016)
void fn_sub_105210_00105210(p3fes::EEContext&);  // debug string depth -> screen z ($f12 -> $f0)
void fn_sub_4C38C0_004c38c0(p3fes::EEContext&);  // RwMatrixCreate
void fn_sub_4C2FC0_004c2fc0(p3fes::EEContext&);  // RwMatrixRotateOneMinusCosineSine(m, axis, 1-cos $f12, sin $f13, op)
void fn_sub_4C6C20_004c6c20(p3fes::EEContext&);  // RwV3dTransformPoints(out, in, n, m)
void fn_sub_4C3880_004c3880(p3fes::EEContext&);  // RwMatrixDestroy
// This file's own entry points, called the way the original called them (jal).
void fn_H_MoonIcon_Draw_001875f0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {

using namespace draw;
using guest::backedge;
using guest::charge;
using kwln::gpvar;
using kwln::jal;
using kwln::jalr;
using kwln::lw;
using kwln::reg;
using kwln::reg64;
using kwln::setreg;
using kwln::setreg64;
using kwln::sw;
namespace gen = recomp_gen;
namespace fpu = ee::fpu;
namespace core = ee::core;

constexpr u32 kStrKwlnRootC = 0x6787D8u;  // "kwlnRoot.c"
constexpr u32 kStrKSpipeC = 0x6788C8u;    // "k_spipe.c"
constexpr u32 kFlagsPassOpen = 0x40000002u;  // kwlnSetFlags mask the Begin passes clear
constexpr u32 kFlagsPassFailed = 0x40000000u;

// The prologue `addiu sp, sp, -size; sd ra; sq sN; swc1 $f2x` and its epilogue (`ld`/`lq`/`lwc1` back from the
// guest stack, `addiu sp, sp, size`) on destruction.
class Frame {
public:
    Frame(EEContext& ctx, u32 size) noexcept : ctx_(ctx), size_(size) { rt::addiu(ctx_, GPR_SP, GPR_SP, -static_cast<s32>(size)); }
    ~Frame() {
        for (unsigned i = 0; i < n_; ++i) {
            const s32 off = static_cast<s32>(slot_[i].off);
            switch (slot_[i].kind) {
            case Kind::D: rt::ld(ctx_, slot_[i].r, GPR_SP, off); break;
            case Kind::Q: rt::lq(ctx_, slot_[i].r, GPR_SP, off); break;
            case Kind::F: ctx_.fpr[slot_[i].r] = guest::load<u32>(ctx_, sp() + slot_[i].off); break;
            }
        }
        rt::addiu(ctx_, GPR_SP, GPR_SP, static_cast<s32>(size_));
    }
    Frame(const Frame&) = delete;
    Frame& operator=(const Frame&) = delete;

    void sd(unsigned r, u32 off) noexcept { rt::sd(ctx_, r, GPR_SP, static_cast<s32>(off)); add(r, off, Kind::D); }
    void sq(unsigned r, u32 off) noexcept { rt::sq(ctx_, r, GPR_SP, static_cast<s32>(off)); add(r, off, Kind::Q); }
    void swc1(unsigned f, u32 off) noexcept { guest::store<u32>(ctx_, sp() + off, ctx_.fpr[f]); add(f, off, Kind::F); }
    u32 sp() const noexcept { return ee::core::gpr32(ctx_, GPR_SP); }
    u32 at(u32 off) const noexcept { return sp() + off; }

private:
    enum class Kind : u8 { D, Q, F };
    void add(unsigned r, u32 off, Kind k) noexcept { slot_[n_++] = {r, off, k}; }
    struct Slot {
        unsigned r;
        u32 off;
        Kind kind;
    };
    EEContext& ctx_;
    u32 size_;
    Slot slot_[16] = {};
    unsigned n_ = 0;
};

// `lw reg, va` into a register; returns the 32-bit value.
u32 lwr(EEContext& ctx, unsigned r, u32 va) {
    const u32 v = lw(ctx, va);
    setreg(ctx, r, v);
    return v;
}
// `lh reg, va`.
s16 lhr(EEContext& ctx, unsigned r, u32 va) {
    const s16 v = guest::load<s16>(ctx, va);
    setreg64(ctx, r, core::sext16(static_cast<u16>(v)));
    return v;
}
void sh(EEContext& ctx, u32 va, u32 v) { guest::store<u16>(ctx, va, static_cast<u16>(v)); }
u64 sext16(u64 v) { return core::sext16(static_cast<u16>(v)); }  // `dsll32 rd, rt, 16; dsra32 rd, rd, 16`
u32 fpr(const EEContext& ctx, unsigned f) { return ctx.fpr[f]; }
void setf(EEContext& ctx, unsigned f, u32 bits) { ctx.fpr[f] = bits; }
void swc1(EEContext& ctx, u32 va, unsigned f) { guest::store<u32>(ctx, va, ctx.fpr[f]); }
void lwc1(EEContext& ctx, unsigned f, u32 va) { ctx.fpr[f] = lw(ctx, va); }

// --- calls as the draw code makes them ---------------------------------------------------------------------
// `lw $v0, 0(pfn)` + `jalr $v0` at pc: a call through a RenderWare device pointer with the arguments already set.
void call_pfn(EEContext& ctx, u32 pc, u32 pfn) {
    const u32 fn = lwr(ctx, GPR_V0, pfn);
    jalr(ctx, pc, fn);
}
// RwRenderStateSet(state, value): `li $a0, state; li $a1, value; lw $v0, 0($sN); jalr $v0`.
void state_set(EEContext& ctx, u32 pc, u32 state, u64 value) {
    setreg(ctx, GPR_A0, state);
    setreg64(ctx, GPR_A1, value);
    call_pfn(ctx, pc, kPfnRenderStateSet);
}
// RwRenderStateGet(state, &out) with `out` a word of the caller's frame.
void state_get(EEContext& ctx, u32 pc, u32 state, u32 out_va) {
    setreg(ctx, GPR_A0, state);
    setreg(ctx, GPR_A1, out_va);
    call_pfn(ctx, pc, kPfnRenderStateGet);
}
// The main camera (sub_198590 = *(gp-19504)), jal at pc; leaves it in $v0.
u64 main_camera(EEContext& ctx, u32 pc) {
    jal(ctx, pc, gen::fn_sub_198590_00198590);
    return reg64(ctx, GPR_V0);
}
// RwCameraBeginUpdate(main camera): the getter, `move $a0, $v0`, jal; returns $v0 (the camera, 0 = failed).
u64 camera_begin(EEContext& ctx, u32 pc_get, u32 pc_begin) {
    setreg64(ctx, GPR_A0, main_camera(ctx, pc_get));
    jal(ctx, pc_begin, gen::fn_RwCameraBeginUpdate_004c9d10);
    return reg64(ctx, GPR_V0);
}
void camera_end(EEContext& ctx, u32 pc_get, u32 pc_end) {
    setreg64(ctx, GPR_A0, main_camera(ctx, pc_get));
    jal(ctx, pc_end, gen::fn_RwCameraEndUpdate_004c9d00);
}
// RwCameraClear(main camera, &clear colour, flags): the camera is kept in $s0 across the colour getter.
void camera_clear(EEContext& ctx, u32 pc_get, u32 pc_colour, u32 pc_clear, u32 flags) {
    setreg64(ctx, GPR_S0, main_camera(ctx, pc_get));
    jal(ctx, pc_colour, gen::fn_sub_1985A0_001985a0);
    setreg64(ctx, GPR_A0, reg64(ctx, GPR_S0));
    setreg64(ctx, GPR_A1, reg64(ctx, GPR_V0));
    setreg(ctx, GPR_A2, flags);
    jal(ctx, pc_clear, gen::fn_RwCameraClear_004c9e90);
}
void k_assert(EEContext& ctx, u32 pc, u32 file, u32 line) {
    setreg(ctx, GPR_A0, file);
    setreg(ctx, GPR_A1, line);
    jal(ctx, pc, gen::fn_sub_19D3F0_0019d3f0);
}
void kwln_set_flags(EEContext& ctx, u32 pc, u32 mask, u32 on) {
    setreg(ctx, GPR_A0, mask);
    setreg(ctx, GPR_A1, on);
    jal(ctx, pc, gen::fn_kwlnSetFlags_00198610);
}
// A Begin pass that failed: K_Assert(file, line), then kwlnSetFlags(0x40000000, 1) (`lui $a0, 0x4000`).
void begin_failed(EEContext& ctx, u32 pc_assert, u32 file, u32 line, u32 pc_flags) {
    k_assert(ctx, pc_assert, file, line);
    kwln_set_flags(ctx, pc_flags, kFlagsPassFailed, 1);
}
// A Begin pass that opened: kwlnSetFlags(0x40000002, 0) (`lui $v0, 0x4000; ori $a0, $v0, 2`), then
// kwlnSetFlags(second_mask, 1).
void begin_opened(EEContext& ctx, u32 pc_clear_flags, u32 pc_set_flags, u32 second_mask) {
    setreg(ctx, GPR_V0, kFlagsPassFailed);
    kwln_set_flags(ctx, pc_clear_flags, kFlagsPassOpen, 0);
    kwln_set_flags(ctx, pc_set_flags, second_mask, 1);
}
// rwRENDERSTATEFOGCOLOR from the kwlnRoot fog colour: (a << 24) | (r << 16) | (g << 8) | b, built in $v1 and $a1
// as the original does (each `sll` sign-extends its 32-bit result).
void state_set_fog_colour(EEContext& ctx, u32 pc) {
    const u32 a = guest::load<u8>(ctx, gpvar(ctx, kGpFogAlpha));
    const u32 r = guest::load<u8>(ctx, gpvar(ctx, kGpFogRed));
    const u32 g = guest::load<u8>(ctx, gpvar(ctx, kGpFogGreen));
    const u32 b = guest::load<u8>(ctx, gpvar(ctx, kGpFogBlue));
    const u64 argb = core::sext32(a << 24) | core::sext32(r << 16) | core::sext32(g << 8);
    setreg64(ctx, GPR_V1, argb);
    setreg64(ctx, GPR_A1, argb | b);
    setreg(ctx, GPR_A0, rwRENDERSTATEFOGCOLOR);
    call_pfn(ctx, pc, kPfnRenderStateSet);
}
// The fog states of an End pass when kwlnRoot's fog is on: FOGENABLE 1, FOGCOLOR, FOGTYPE linear. The flag test
// leaves `li $a1, 1` and the flag in $v0; the three calls keep the device pointer's address in $s0.
void end_pass_fog(EEContext& ctx, u32 pc_enable, u32 pc_colour, u32 pc_type) {
    setreg(ctx, GPR_S0, kPfnRenderStateSet);
    setreg(ctx, GPR_A0, rwRENDERSTATEFOGENABLE);
    call_pfn(ctx, pc_enable, kPfnRenderStateSet);  // $a1 = 1 from the flag test
    state_set_fog_colour(ctx, pc_colour);
    state_set(ctx, pc_type, rwRENDERSTATEFOGTYPE, 1);
}
// The common End pass (0x198D20 / 0x198FD0): fog states if enabled, then RwCameraEndUpdate.
u32 end_pass(EEContext& ctx, u32 pc_enable, u32 pc_colour, u32 pc_type, u32 pc_get, u32 pc_end) {
    guest::enter(ctx, 7);
    Frame f(ctx, 32);
    f.sd(GPR_RA, 16);
    f.sq(GPR_S0, 0);
    const u32 fog = lwr(ctx, GPR_V0, gpvar(ctx, kGpFogEnabled));
    setreg(ctx, GPR_A1, 1);
    if (fog == 1) {
        charge(ctx, 25);
        end_pass_fog(ctx, pc_enable, pc_colour, pc_type);
    }
    charge(ctx, 11);
    camera_end(ctx, pc_get, pc_end);
    setreg(ctx, GPR_V0, 0);
    return 0;
}

// 1 / camera->nearPlane into $fd: `lui $v1, 0x3f80; mtc1 $v1, $f1; lwc1 $f0, 128($v0); div.s $fd, $f1, $f0`.
void recip_near_plane(EEContext& ctx, u32 camera, unsigned fd) {
    setreg(ctx, GPR_V1, fpu::kOne);
    setf(ctx, 1, fpu::kOne);
    lwc1(ctx, 0, camera + kCameraNearPlane);
    fpu::div_s(ctx, fd, 1, 0);
}
// `lbu`, then `bltz` (never taken: a byte is non-negative) and `mtc1; cvt.s.w`: a colour byte as a float.
u32 byte_to_float(u32 byte) { return fpu::cvt_s_w(byte); }

}  // namespace

// =====================================================================================================================
// Camera passes
// =====================================================================================================================

// 0x198B20 "2D Draw End" (prio 5241): closes the 2D pass.
u32 kwlnRootUpdate2DDrawEndTask(EEContext& ctx) {
    guest::enter(ctx, 12);
    Frame f(ctx, 16);
    f.sd(GPR_RA, 0);
    camera_end(ctx, 0x198B28u, 0x198B34u);
    setreg(ctx, GPR_V0, 0);
    return 0;
}

// 0x198C10 [kwlnRootUpdate3DOn2DZClearTask] "3D on 2D Zclear" (prio 5243): RwCameraClear(main camera, &colour,
// rwCAMERACLEARZ) so the 3-D models drawn over the 2D layer (bust-ups, the menu's persona) start on an empty Z.
u32 kwlnRootUpdate3DOn2DZClearTask(EEContext& ctx) {
    guest::enter(ctx, 19);
    Frame f(ctx, 32);
    f.sd(GPR_RA, 16);
    f.sq(GPR_S0, 0);
    camera_clear(ctx, 0x198C1Cu, 0x198C28u, 0x198C3Cu, 2);
    setreg(ctx, GPR_V0, 0);
    return 0;
}

// 0x198C60 [kwlnRootUpdate3DOn2DDrawBeginTask] "3D on 2D Draw Begin" (prio 5245): RwCameraBeginUpdate, the kwln
// pass flags, Z test and Z write on.
u32 kwlnRootUpdate3DOn2DDrawBeginTask(EEContext& ctx) {
    guest::enter(ctx, 10);
    Frame f(ctx, 32);
    f.sd(GPR_RA, 16);
    f.sq(GPR_S0, 0);
    if (camera_begin(ctx, 0x198C6Cu, 0x198C78u) == 0) {
        charge(ctx, 9);
        begin_failed(ctx, 0x198CF0u, kStrKwlnRootC, 719, 0x198D00u);
    } else {
        charge(ctx, 23);
        begin_opened(ctx, 0x198C94u, 0x198CA4u, 2);
        setreg(ctx, GPR_S0, kPfnRenderStateSet);
        state_set(ctx, 0x198CC0u, rwRENDERSTATEZTESTENABLE, 1);
        state_set(ctx, 0x198CD4u, rwRENDERSTATEZWRITEENABLE, 1);
    }
    charge(ctx, 6);
    setreg(ctx, GPR_V0, 0);
    return 0;
}

// 0x198D20 [kwlnRootUpdate3DOn2DDrawEndTask] "3D on 2D Draw End" (prio 6320).
u32 kwlnRootUpdate3DOn2DDrawEndTask(EEContext& ctx) { return end_pass(ctx, 0x198D4Cu, 0x198D84u, 0x198D98u, 0x198DA0u, 0x198DACu); }

// 0x198E90 [kwlnRootUpdateEtcDrawBeginTask] "etc Draw Begin" (prio 6323): Z clear, BeginUpdate, Z test/write on,
// fog off -- the pass of the fades and the debug print.
u32 kwlnRootUpdateEtcDrawBeginTask(EEContext& ctx) {
    guest::enter(ctx, 20);
    Frame f(ctx, 32);
    f.sd(GPR_RA, 16);
    f.sq(GPR_S0, 0);
    camera_clear(ctx, 0x198E9Cu, 0x198EA8u, 0x198EBCu, 2);
    if (camera_begin(ctx, 0x198EC4u, 0x198ED0u) == 0) {
        charge(ctx, 9);
        begin_failed(ctx, 0x198F5Cu, kStrKwlnRootC, 839, 0x198F6Cu);
    } else {
        charge(ctx, 28);
        // kwlnSetFlags(0x40000002, 0), then kwlnSetFlags(1, 1) (`li $a0, 1; move $a1, $a0`).
        begin_opened(ctx, 0x198EECu, 0x198EFCu, 1);
        setreg(ctx, GPR_S0, kPfnRenderStateSet);
        state_set(ctx, 0x198F18u, rwRENDERSTATEZTESTENABLE, 1);
        state_set(ctx, 0x198F2Cu, rwRENDERSTATEZWRITEENABLE, 1);
        state_set(ctx, 0x198F40u, rwRENDERSTATEFOGENABLE, 0);
    }
    charge(ctx, 6);
    setreg(ctx, GPR_V0, 0);
    return 0;
}

// 0x198FD0 Draw End (prio 7379): the last pass of the frame before ShowRaster.
u32 kwlnRootUpdateDrawEndTask(EEContext& ctx) { return end_pass(ctx, 0x198FFCu, 0x199034u, 0x199048u, 0x199050u, 0x19905Cu); }

// 0x199520 [K_SPipe_Update3DDrwBeginTask] "3D Draw Begin" (prio 2098): opens the 3-D pass of the frame.
u32 K_SPipe_Update3DDrwBeginTask(EEContext& ctx) {
    guest::enter(ctx, 10);
    Frame f(ctx, 32);
    f.sd(GPR_RA, 16);
    f.sq(GPR_S0, 0);
    if (camera_begin(ctx, 0x19952Cu, 0x199538u) == 0) {
        charge(ctx, 9);
        begin_failed(ctx, 0x1995B8u, kStrKSpipeC, 385, 0x1995C8u);
    } else {
        charge(ctx, 25);
        begin_opened(ctx, 0x199554u, 0x199564u, 2);
        setreg(ctx, GPR_S0, kPfnRenderStateSet);
        state_set(ctx, 0x199580u, rwRENDERSTATEZTESTENABLE, 1);
        state_set(ctx, 0x199594u, rwRENDERSTATEZWRITEENABLE, 1);
        jal(ctx, 0x19959Cu, gen::fn_kwlnTaskIsBandAEnabled_00195750);  // kwlnTaskIsBandAEnabled(), result unused
    }
    charge(ctx, 6);
    setreg(ctx, GPR_V0, 0);
    return 0;
}

// 0x1995F0 [K_SPipe_Update3DDrwEndTask] "3D Draw End" (prio 4167): fog off then on with kwlnRoot's colour and
// linear type (always, unlike the root End passes), RwCameraEndUpdate, kwlnSetFlags(3, 0).
u32 K_SPipe_Update3DDrwEndTask(EEContext& ctx) {
    guest::enter(ctx, 49);
    Frame f(ctx, 32);
    f.sd(GPR_RA, 16);
    f.sq(GPR_S0, 0);
    setreg(ctx, GPR_S0, kPfnRenderStateSet);
    state_set(ctx, 0x199610u, rwRENDERSTATEFOGENABLE, 0);
    state_set(ctx, 0x199624u, rwRENDERSTATEFOGENABLE, 1);
    state_set_fog_colour(ctx, 0x19965Cu);
    state_set(ctx, 0x199670u, rwRENDERSTATEFOGTYPE, 1);
    camera_end(ctx, 0x199678u, 0x199684u);
    kwln_set_flags(ctx, 0x199694u, 3, 0);
    setreg(ctx, GPR_V0, 0);
    return 0;
}

// 0x199740 [kwlnRootUpdateShadowNodeCameraTask] "Shadow Node Camera" (prio 2069): clears the main camera's image
// and Z (rwCAMERACLEARIMAGE | rwCAMERACLEARZ) and updates the shadow node camera at 0x8668F0.
u32 kwlnRootUpdateShadowNodeCameraTask(EEContext& ctx) {
    guest::enter(ctx, 23);
    Frame f(ctx, 32);
    f.sd(GPR_RA, 16);
    f.sq(GPR_S0, 0);
    camera_clear(ctx, 0x19974Cu, 0x199758u, 0x19976Cu, 3);
    setreg(ctx, GPR_A0, 0x8668F0u);
    jal(ctx, 0x19977Cu, gen::fn_sub_1A8910_001a8910);
    setreg(ctx, GPR_V0, 0);
    return 0;
}

// 0x27B310 [btlDrawMessagePass] battle message pass: BeginUpdate, fog saved and turned off, the message
// (sub_27A3B0) when its work record's bit 0 is set, fog restored, EndUpdate.
u32 btlDrawMessagePass(EEContext& ctx) {
    guest::enter(ctx, 10);
    Frame f(ctx, 48);
    f.sd(GPR_RA, 16);
    f.sq(GPR_S0, 0);
    if (camera_begin(ctx, 0x27B31Cu, 0x27B328u) != 0) {
        charge(ctx, 16);
        const u32 saved_fog = f.at(44);
        state_get(ctx, 0x27B348u, rwRENDERSTATEFOGENABLE, saved_fog);
        setreg(ctx, GPR_S0, kPfnRenderStateSet);
        state_set(ctx, 0x27B364u, rwRENDERSTATEFOGENABLE, 0);
        if (lwr(ctx, GPR_V0, gpvar(ctx, -18708)) == 0) {  // the battle message work (0x7CE3DC)
            charge(ctx, 4);
            k_assert(ctx, 0x27B380u, gpvar(ctx, -26624), 61);
        }
        charge(ctx, 6);
        const u32 work = lwr(ctx, GPR_V0, gpvar(ctx, -18708));
        const u64 off = ~core::sext32(lw(ctx, work)) & 1;  // `nor; andi 1`: 1 = bit 0 clear
        setreg64(ctx, GPR_V0, off);
        if (off == 0) {
            charge(ctx, 2);
            jal(ctx, 0x27B3A0u, gen::fn_sub_27A3B0_0027a3b0);
        }
        charge(ctx, 10);
        state_set(ctx, 0x27B3B4u, rwRENDERSTATEFOGENABLE, core::sext32(lw(ctx, saved_fog)));
        camera_end(ctx, 0x27B3BCu, 0x27B3C8u);
    }
    charge(ctx, 6);
    setreg(ctx, GPR_V0, 0);
    return 0;
}

// 0x27CCF0 [btlUpdateDraw3DTask] "battle draw 3d" (prio 2081): BeginUpdate, effect pass 2, the battle draw list
// pass 2, then sub_287400, the effects and models (sub_2BB3A0), sub_2A48F0, EndUpdate.
u32 btlUpdateDraw3DTask(EEContext& ctx) {
    guest::enter(ctx, 9);
    Frame f(ctx, 16);
    f.sd(GPR_RA, 0);
    if (camera_begin(ctx, 0x27CCF8u, 0x27CD04u) != 0) {
        charge(ctx, 17);
        setreg(ctx, GPR_A0, 2);
        jal(ctx, 0x27CD18u, gen::fn_sub_321120_00321120);
        setreg(ctx, GPR_A0, 2);
        jal(ctx, 0x27CD24u, gen::fn_sub_27F160_0027f160);
        jal(ctx, 0x27CD2Cu, gen::fn_sub_287400_00287400);
        jal(ctx, 0x27CD34u, gen::fn_sub_2BB3A0_002bb3a0);
        jal(ctx, 0x27CD3Cu, gen::fn_sub_2A48F0_002a48f0);
        camera_end(ctx, 0x27CD44u, 0x27CD50u);
    }
    charge(ctx, 5);
    setreg(ctx, GPR_V0, 0);
    return 0;
}

// 0x00187BE0 H_MoonIcon_UpdateTask -- 524 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// 0x187BE0 [H_MoonIcon_UpdateTask] the HUD moon icon (camp/i_moon_00.spr): its own camera pass with fog off; work +0 state
// (0 init, 1 wait +4 frames, 2 fade in: alpha +8 += 20 up to 255 unless flag 5153, 3 fade out: alpha -= 20, the task
// ends (-1) below 0), +12 the rotation (+10 a frame), +16 the start angle. H_MoonIcon_Draw draws it.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: callee frames ($sp off / deeper stack)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void H_MoonIcon_UpdateTask(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::i64, hg::jal, hg::jalr, hg::ld, hg::lq, hg::lw, hg::sd,
          hg::si, hg::slti, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00187be0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, 60);
    jal(ctx, 0x187BF4u, gen::fn_sub_198590_00198590);
    a0 = v0;
    jal(ctx, 0x187C00u, gen::fn_RwCameraBeginUpdate_004c9d10);
    if (v0 != 0) {
        // 0x00187c1c
        charge(ctx, 17);
        a0 = 14;
        a1 = addiu(sp, 0x3C);
        v0 = 0x960000;
        lw(v0, v0, 148);  // pfn_RwRenderStateGet
        jalr(ctx, 0x187C2Cu, v0.u());
        s0 = 0x960000;
        s0 = addiu(s0, 144);  // &pfn_RwRenderStateSet
        a0 = 14;
        a1 = 0;
        lw(v0, s0, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x187C48u, v0.u());
        lw(a1, s1, 0);
        v0 = 3;
        if (a1 == v0) {
            // 0x00187d34
            charge(ctx, 23);
            lw(a0, s1, 16);
            lw(a1, s1, 12);
            lw(a2, s1, 8);
            jal(ctx, 0x187D40u, gen::fn_H_MoonIcon_Draw_001875f0);
            a0 = 14;
            lw(a1, sp, 0x3C);
            lw(v0, s0, 0);
            jalr(ctx, 0x187D54u, v0.u());
            jal(ctx, 0x187D5Cu, gen::fn_sub_198590_00198590);
            a0 = v0;
            jal(ctx, 0x187D68u, gen::fn_RwCameraEndUpdate_004c9d00);
            lw(v0, s1, 12);
            v0 = addiu(v0, 10);
            sw(v0, s1, 12);
            lw(v0, s1, 8);
            v0 = addiu(v0, -20);
            sw(v0, s1, 8);
            if (i64(v0) >= 0) {
                // 0x00187d9c
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x00187d90
                charge(ctx, 3);
                v0 = si(-1);
            }
            // 0x00187da0
            charge(ctx, 2);
        } else {
            // 0x00187c60
            charge(ctx, 3);
            a0 = 2;
            if (a1 == a0) {
                // 0x00187ccc
                charge(ctx, 5);
                a0 = 5153;
                jal(ctx, 0x187CD0u, gen::fn_datGetFlag_0016f190);
                if (v0 != 0) {
                    // 0x00187d28
                    charge(ctx, 3);
                    sw(zero, s1, 8);
                } else {
                    // 0x00187ce0
                    charge(ctx, 14);
                    lw(a0, s1, 16);
                    lw(a1, s1, 12);
                    lw(a2, s1, 8);
                    jal(ctx, 0x187CECu, gen::fn_H_MoonIcon_Draw_001875f0);
                    lw(v0, s1, 12);
                    v0 = addiu(v0, 10);
                    sw(v0, s1, 12);
                    lw(v0, s1, 8);
                    v0 = addiu(v0, 20);
                    sw(v0, s1, 8);
                    v0 = slti(v0, 255);
                    if (v0 == 0) {
                        // 0x00187d18
                        charge(ctx, 4);
                        v0 = 255;
                        sw(v0, s1, 8);
                    }
                }
            } else {
                // 0x00187c6c
                charge(ctx, 3);
                v1 = 1;
                if (a1 == v1) {
                    // 0x00187cac
                    charge(ctx, 5);
                    lw(v0, s1, 4);
                    v0 = addiu(v0, -1);
                    sw(v0, s1, 4);
                    if (i64(v0) < 0) {
                        // 0x00187cc0
                        charge(ctx, 3);
                        sw(a0, s1, 0);
                    }
                } else {
                    // 0x00187c78
                    charge(ctx, 2);
                    if (a1 == 0) {
                        // 0x00187c88
                        charge(ctx, 9);
                        sw(zero, s1, 8);
                        v0 = 10;
                        sw(v0, s1, 4);
                        v0 = 40;
                        sw(v0, s1, 16);
                        sw(zero, s1, 12);
                        sw(v1, s1, 0);
                    } else {
                        // 0x00187c80
                        charge(ctx, 2);
                    }
                }
            }
            // 0x00187da8
            charge(ctx, 11);
            a0 = 14;
            lw(a1, sp, 0x3C);
            lw(v0, s0, 0);
            jalr(ctx, 0x187DB4u, v0.u());
            jal(ctx, 0x187DBCu, gen::fn_sub_198590_00198590);
            a0 = v0;
            jal(ctx, 0x187DC8u, gen::fn_RwCameraEndUpdate_004c9d00);
            v0 = 0;
        }
    } else {
        // 0x00187c10
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00187dd4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// =====================================================================================================================
// Im2D builders
// =====================================================================================================================

// 0x00100230 H_Cursor_UpdateDrawTask -- 828 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// 0x100230 H_Cursor_UpdateDrawTask (the "H CURSOR Draw" task): the cursor's alpha-blended render states, then,
// while should_draw is set and the work is not finished (state 2 returns -1), refresh the four vertices from the
// setters' fields (z = near screen z - z_offset, colours from the RGBA bytes, a pos .. pos + (w, h) quad) and
// draw them as a triangle strip; state becomes 1 (built).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: callee frames ($sp off / deeper stack)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void H_Cursor_UpdateDrawTask(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::cvt_s_w, hg::div_s,
          hg::dsll32, hg::dsra32, hg::enter, hg::i64, hg::jal, hg::jalr, hg::lbu, hg::ld, hg::lh, hg::lq, hg::lw,
          hg::lwc1, hg::mtc1, hg::sd, hg::sh, hg::si, hg::sll, hg::slti, hg::sq, hg::srl, hg::sub_s, hg::swc1;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x00100230
    enter(ctx, 50);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, 60);
    s0 = 0x960000;
    s0 = addiu(s0, 144);  // &pfn_RwRenderStateSet
    a0 = 6;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x100258u, v0.u());
    a0 = 7;
    a1 = 2;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x10026Cu, v0.u());
    a0 = 8;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x100280u, v0.u());
    a0 = 10;
    a1 = 5;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x100294u, v0.u());
    a0 = 11;
    a1 = 9;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x1002A8u, v0.u());
    a0 = 9;
    a1 = 2;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x1002BCu, v0.u());
    a0 = 12;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x1002D0u, v0.u());
    a0 = 1;
    a1 = 0;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x1002E4u, v0.u());
    lw(v0, s1, 320);
    if (v0 != 0) {
        // 0x00100304
        charge(ctx, 4);
        lh(v1, s1, 272);
        v0 = 2;
        if (v1 == v0) {
            // 0x00100544
            charge(ctx, 3);
            v0 = si(-1);
        } else {
            // 0x00100314
            charge(ctx, 3);
            v0 = 1;
            if (v1 != v0) {
                // 0x00100320
                charge(ctx, 2);
                if (v1 == 0) {
                    goto L_00100330;
                }
                // 0x00100328
                charge(ctx, 2);
                goto L_00100550;
            }
        L_00100330:
            charge(ctx, 11);
            jal(ctx, 0x100330u, gen::fn_sub_198590_00198590);
            v1 = 0x3F800000;
            mtc1(v1, f1);
            lwc1(f0, v0, 128);
            div_s(f2, f1, f0);
            a3 = 0;
            v0 = 0x960000;
            for (;;) {
                // 0x00100494
                charge(ctx, 5);
                v1 = dsll32(a3, 16);
                v1 = dsra32(v1, 16);
                v1 = slti(v1, 4);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0010035c
                charge(ctx, 14);
                a0 = dsll32(a3, 16);
                a0 = dsra32(a0, 16);
                v1 = sll(a0, 6);
                a2 = addu(s1, v1);
                lwc1(f1, v0, 136);
                lwc1(f0, s1, 300);
                sub_s(f0, f1, f0);
                swc1(f0, a2, 8);
                swc1(f2, a2, 24);
                v1 = sll(a0, 2);
                a1 = addu(s1, v1);
                lbu(v1, a1, 304);
                if (i64(v1) < 0) {
                    // 0x001003a8
                    charge(ctx, 7);
                    a0 = srl(v1, 1);
                    v1 = v1 & 0x1;
                    a0 = a0 | v1;
                    mtc1(a0, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f0);
                } else {
                    // 0x00100394
                    charge(ctx, 5);
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                }
                // 0x001003c4
                charge(ctx, 4);
                swc1(f0, a2, 32);
                lbu(v1, a1, 305);
                if (i64(v1) < 0) {
                    // 0x001003e8
                    charge(ctx, 7);
                    a0 = srl(v1, 1);
                    v1 = v1 & 0x1;
                    a0 = a0 | v1;
                    mtc1(a0, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f0);
                } else {
                    // 0x001003d4
                    charge(ctx, 5);
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                }
                // 0x00100404
                charge(ctx, 4);
                swc1(f0, a2, 36);
                lbu(v1, a1, 306);
                if (i64(v1) < 0) {
                    // 0x00100428
                    charge(ctx, 7);
                    a0 = srl(v1, 1);
                    v1 = v1 & 0x1;
                    a0 = a0 | v1;
                    mtc1(a0, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f0);
                } else {
                    // 0x00100414
                    charge(ctx, 5);
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                }
                // 0x00100444
                charge(ctx, 4);
                swc1(f0, a2, 40);
                lbu(v1, a1, 307);
                if (i64(v1) < 0) {
                    // 0x00100468
                    charge(ctx, 7);
                    a0 = srl(v1, 1);
                    v1 = v1 & 0x1;
                    a0 = a0 | v1;
                    mtc1(a0, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f0);
                } else {
                    // 0x00100454
                    charge(ctx, 5);
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                }
                // 0x00100484
                charge(ctx, 4);
                swc1(f0, a2, 44);
                v1 = addiu(a3, 1);
                a3 = dsll32(v1, 16);
                a3 = dsra32(a3, 16);
            }
            // 0x001004a8
            charge(ctx, 39);
            lwc1(f0, s1, 276);
            swc1(f0, s1, 0);
            lwc1(f0, s1, 280);
            swc1(f0, s1, 4);
            lwc1(f1, s1, 276);
            lwc1(f0, s1, 292);
            cvt_s_w(f0, f0);
            add_s(f0, f1, f0);
            swc1(f0, s1, 64);
            lwc1(f0, s1, 280);
            swc1(f0, s1, 68);
            lwc1(f0, s1, 276);
            swc1(f0, s1, 128);
            lwc1(f1, s1, 280);
            lwc1(f0, s1, 296);
            cvt_s_w(f0, f0);
            add_s(f0, f1, f0);
            swc1(f0, s1, 132);
            lwc1(f1, s1, 276);
            lwc1(f0, s1, 292);
            cvt_s_w(f0, f0);
            add_s(f0, f1, f0);
            swc1(f0, s1, 192);
            lwc1(f1, s1, 280);
            lwc1(f0, s1, 296);
            cvt_s_w(f0, f0);
            add_s(f0, f1, f0);
            swc1(f0, s1, 196);
            a0 = 4;
            a1 = s1;
            a2 = a0;
            v0 = 0x960000;
            lw(v0, v0, 160);  // pfn_RwIm2DRenderPrimitive
            jalr(ctx, 0x10052Cu, v0.u());
            v0 = 1;
            sh(v0, s1, 272);
        L_00100550:
            charge(ctx, 1);
            v0 = 0;
        }
    } else {
        // 0x001002f8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00100554 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

namespace {

// The three screen fades share one body: the fade pass's render states (alpha blend, Gouraud, bilinear, vertex
// alpha), the fade state machine (kGpFadeState: 0 -> 2 counts up to the duration -> 3 held; 4 -> 5 counts down,
// clearing kGpFadeActive at 0; the variants with tasks destroy kGpFadeTaskA/B on 3 and 4), then a full-screen
// 640x448 triangle strip at near screen z - 100 with alpha = 255 * counter / duration and no texture.
struct FadeVariant {
    u32 pcs[7];           // the seven RwRenderStateSet jalrs
    bool kills_tasks;     // states 3 / 4 destroy the fade's task hierarchies (0x1075B0, 0x1081E0)
    u32 pc_kill[4];       // kwlnTaskDestroyWithHierarchy jals: state 3 A, B; state 4 A, B
    u32 pc_camera;        // the main camera getter
    u32 pc_raster;        // RwRenderStateSet(TEXTURERASTER, 0)
    u32 pc_draw;          // RwIm2DRenderPrimitive
};

void fade_state_machine(EEContext& ctx, const FadeVariant& fv) {
    const u32 state_va = gpvar(ctx, kGpFadeState), counter_va = gpvar(ctx, kGpFadeCounter);
    const u32 duration_va = gpvar(ctx, kGpFadeDuration);
    // The compare chain keeps the state in $a0 (0x1078A0, with `li $v1, 5`) or $v1 (the others, `li $v0, 5`).
    const unsigned rs = fv.kills_tasks ? GPR_V1 : GPR_A0;
    const unsigned rfive = fv.kills_tasks ? GPR_V0 : GPR_V1;
    const s16 state = lhr(ctx, rs, state_va);
    setreg(ctx, rfive, 5);
    const auto count_up = [&] {  // states 0 and 2
        charge(ctx, 8);
        const u64 c = sext16(guest::load<s16>(ctx, counter_va) + 1u);
        setreg64(ctx, GPR_V0, core::sext32(static_cast<u32>(guest::load<s16>(ctx, counter_va)) + 1u));
        sh(ctx, counter_va, static_cast<u32>(c));
        setreg64(ctx, GPR_V1, c);
        const s16 d = lhr(ctx, GPR_V0, duration_va);
        if (static_cast<s16>(c) == d) {
            charge(ctx, 4);
            setreg(ctx, GPR_V0, 3);
            sh(ctx, state_va, 3);
        }
    };
    const auto kill = [&](s32 task_off, u32 pc, u32 cost_kill) {
        const u32 t = lwr(ctx, GPR_A0, gpvar(ctx, task_off));
        if (t == 0) return false;
        charge(ctx, cost_kill);
        jal(ctx, pc, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
        sw(ctx, gpvar(ctx, task_off), 0);
        return true;
    };
    if (state == 5) {
        charge(ctx, 7);
        const u64 c = sext16(guest::load<s16>(ctx, counter_va) - 1u);
        sh(ctx, counter_va, static_cast<u32>(c));
        setreg64(ctx, GPR_V0, c);
        if (c == 0) {
            charge(ctx, 1);
            sw(ctx, gpvar(ctx, kGpFadeActive), 0);
        }
        return;
    }
    charge(ctx, 3);
    setreg(ctx, GPR_V0, 4);
    if (state == 4) {
        if (!fv.kills_tasks) {
            charge(ctx, 5);
            sh(ctx, counter_va, static_cast<u32>(lhr(ctx, GPR_V0, duration_va)));
            sh(ctx, state_va, 5);
            return;
        }
        charge(ctx, 3);
        kill(kGpFadeTaskA, fv.pc_kill[2], 3);
        charge(ctx, 3);
        kill(kGpFadeTaskB, fv.pc_kill[3], 3);
        charge(ctx, 6);
        sh(ctx, counter_va, static_cast<u32>(lhr(ctx, GPR_V0, duration_va)));
        setreg(ctx, GPR_V0, 5);
        sh(ctx, state_va, 5);
        return;
    }
    charge(ctx, 3);
    setreg(ctx, GPR_V0, 3);
    if (state == 3) {
        if (fv.kills_tasks) {
            charge(ctx, 5);
            sh(ctx, counter_va, static_cast<u32>(lhr(ctx, GPR_V0, duration_va)));
            kill(kGpFadeTaskA, fv.pc_kill[0], 3);
            charge(ctx, 3);
            kill(kGpFadeTaskB, fv.pc_kill[1], 5);
        }
        return;
    }
    charge(ctx, 3);
    setreg(ctx, GPR_V0, 2);
    if (state == 2) {
        count_up();
        return;
    }
    charge(ctx, 2);
    if (state == 0) {
        charge(ctx, 2);
        sh(ctx, state_va, 2);
        sh(ctx, counter_va, 0);
        count_up();
        return;
    }
    charge(ctx, 2);
}

// The fade's alpha: (s16)(255 * counter / duration) through the EE `div` (HI/LO as the original leaves them).
u64 fade_alpha(EEContext& ctx) {
    const s16 counter = guest::load<s16>(ctx, gpvar(ctx, kGpFadeCounter));
    const u32 x255 = (static_cast<u32>(static_cast<s32>(counter)) << 8) - static_cast<u32>(static_cast<s32>(counter));
    setreg(ctx, GPR_V1, x255);
    const s16 duration = guest::load<s16>(ctx, gpvar(ctx, kGpFadeDuration));
    ee::div(ctx, ee::kPipe0, x255, static_cast<u32>(static_cast<s32>(duration)));
    return sext16(ee::mflo(ctx));
}

// The quad's corners (the loop wrote z, recipZ and the colour) and the two calls.
void fade_draw(EEContext& ctx, const FadeVariant& fv, u32 verts) {
    charge(ctx, 27);
    constexpr u32 k640 = 0x44200000u, k448 = 0x43E00000u;
    sw(ctx, verts + 0 * kVtxSize + kVtxX, 0);
    sw(ctx, verts + 0 * kVtxSize + kVtxY, 0);
    sw(ctx, verts + 1 * kVtxSize + kVtxX, k640);
    sw(ctx, verts + 1 * kVtxSize + kVtxY, 0);
    sw(ctx, verts + 2 * kVtxSize + kVtxX, 0);
    sw(ctx, verts + 2 * kVtxSize + kVtxY, k448);
    sw(ctx, verts + 3 * kVtxSize + kVtxX, k640);
    sw(ctx, verts + 3 * kVtxSize + kVtxY, k448);
    setreg(ctx, GPR_V1, k640);
    state_set(ctx, fv.pc_raster, rwRENDERSTATETEXTURERASTER, 0);
    setreg(ctx, GPR_A0, rwPRIMTYPETRISTRIP);
    setreg(ctx, GPR_A1, verts);
    setreg(ctx, GPR_A2, 4);
    call_pfn(ctx, fv.pc_draw, kPfnIm2DRenderPrimitive);
}

void fade_prologue(EEContext& ctx, const FadeVariant& fv) {
    setreg(ctx, GPR_S0, kPfnRenderStateSet);
    state_set(ctx, fv.pcs[0], rwRENDERSTATEZTESTENABLE, 1);
    state_set(ctx, fv.pcs[1], rwRENDERSTATESHADEMODE, 2);
    state_set(ctx, fv.pcs[2], rwRENDERSTATEZWRITEENABLE, 1);
    state_set(ctx, fv.pcs[3], rwRENDERSTATESRCBLEND, 5);
    state_set(ctx, fv.pcs[4], rwRENDERSTATEDESTBLEND, 6);
    state_set(ctx, fv.pcs[5], rwRENDERSTATETEXTUREFILTER, 2);
    state_set(ctx, fv.pcs[6], rwRENDERSTATEVERTEXALPHAENABLE, 1);
    fade_state_machine(ctx, fv);
}

// The two single-colour fades: the colour words are float bit patterns kept in registers across the loop.
void fade_single_colour(EEContext& ctx, const FadeVariant& fv, bool white) {
    guest::enter(ctx, 44);
    Frame f(ctx, 288);
    f.sd(GPR_RA, 16);
    f.sq(GPR_S0, 0);
    const u32 verts = f.at(32);
    fade_prologue(ctx, fv);
    charge(ctx, white ? 27 : 29);
    recip_near_plane(ctx, static_cast<u32>(main_camera(ctx, fv.pc_camera)), 2);
    const u64 alpha = fade_alpha(ctx);
    // 0x1078A0 keeps alpha in $a0 and the counter in $a1; 0x1075B0 alpha in $a2, counter in $a3.
    const unsigned ralpha = white ? GPR_A0 : GPR_A2, ri = white ? GPR_A1 : GPR_A3;
    setreg64(ctx, ralpha, alpha);
    setreg(ctx, ri, 0);
    const u32 z = fpu::sub(lw(ctx, kIm2DNearScreenZ), 0x42C80000u);  // near screen z - 100
    setf(ctx, 1, z);
    u32 r, g, b;
    if (white) {
        r = g = b = 0x437F0000u;  // 255
        setreg(ctx, GPR_V1, r);
    } else {
        r = 0x41700000u, g = 0x41F80000u, b = 0x42200000u;  // (15, 31, 40)
        setreg(ctx, GPR_A1, r);
        setreg(ctx, GPR_A0, g);
        setreg(ctx, GPR_V1, b);
    }
    setf(ctx, 0, fpu::cvt_s_w(static_cast<u32>(alpha)));
    u32 i = 0;
    for (;; ++i) {
        charge(ctx, 5);
        setreg(ctx, GPR_V0, i < 4 ? 1 : 0);
        if (i >= 4) break;
        backedge(ctx);
        charge(ctx, 14);
        const u32 v = verts + i * kVtxSize;
        swc1(ctx, v + kVtxZ, 1);
        swc1(ctx, v + kVtxRecipZ, 2);
        sw(ctx, v + kVtxR, r);
        sw(ctx, v + kVtxG, g);
        sw(ctx, v + kVtxB, b);
        swc1(ctx, v + kVtxA, 0);
        setreg(ctx, ri, i + 1);
    }
    fade_draw(ctx, fv, verts);
}

constexpr FadeVariant kFadeBlue{{0x1075D0u, 0x1075E4u, 0x1075F8u, 0x10760Cu, 0x107620u, 0x107634u, 0x107648u},
                                true,
                                {0x1076E0u, 0x1076F8u, 0x107718u, 0x107730u},
                                0x107774u,
                                0x107868u,
                                0x107884u};
constexpr FadeVariant kFadeWhite{{0x1078C0u, 0x1078D4u, 0x1078E8u, 0x1078FCu, 0x107910u, 0x107924u, 0x107938u},
                                 false,
                                 {0, 0, 0, 0},
                                 0x1079F0u,
                                 0x107ADCu,
                                 0x107AF8u};
constexpr FadeVariant kFadeColour{{0x108200u, 0x108214u, 0x108228u, 0x10823Cu, 0x108250u, 0x108264u, 0x108278u},
                                  true,
                                  {0x108310u, 0x108328u, 0x108348u, 0x108360u},
                                  0x1083A4u,
                                  0x108534u,
                                  0x108550u};

}  // namespace

// 0x1075B0 [H_Fade_DrawBlue] the dark blue (15, 31, 40) fade.
void H_Fade_DrawBlue(EEContext& ctx) { fade_single_colour(ctx, kFadeBlue, false); }

// 0x1078A0 [H_Fade_DrawWhite] the white fade (states 3 / 4 without the task kills).
void H_Fade_DrawWhite(EEContext& ctx) { fade_single_colour(ctx, kFadeWhite, true); }

// 0x1081E0 [H_Fade_DrawColour] the fade in the colour bytes at $gp-19960 (red), -19964 (green), -19968 (blue).
void H_Fade_DrawColour(EEContext& ctx) {
    const FadeVariant& fv = kFadeColour;
    guest::enter(ctx, 44);
    Frame f(ctx, 288);
    f.sd(GPR_RA, 16);
    f.sq(GPR_S0, 0);
    const u32 verts = f.at(32);
    fade_prologue(ctx, fv);
    charge(ctx, 35);
    recip_near_plane(ctx, static_cast<u32>(main_camera(ctx, fv.pc_camera)), 6);
    const u64 alpha = fade_alpha(ctx);
    setreg64(ctx, GPR_A2, alpha);
    setreg(ctx, GPR_T2, 0);
    const u32 r = guest::load<u8>(ctx, gpvar(ctx, kGpFadeColourR));
    const u32 g = guest::load<u8>(ctx, gpvar(ctx, kGpFadeColourG));
    const u32 b = guest::load<u8>(ctx, gpvar(ctx, kGpFadeColourB));
    setreg(ctx, GPR_T1, r);
    setreg(ctx, GPR_T0, g);
    setreg(ctx, GPR_A3, b);
    setf(ctx, 1, lw(ctx, kIm2DNearScreenZ));
    setf(ctx, 0, 0x42C80000u);
    setf(ctx, 5, fpu::sub(fpr(ctx, 1), fpr(ctx, 0)));  // near screen z - 100
    setreg(ctx, GPR_A1, r & 1);  // the (never used) odd-byte halves of the unsigned-convert idiom
    setf(ctx, 4, r);
    setreg(ctx, GPR_A0, g & 1);
    setf(ctx, 3, g);
    setreg(ctx, GPR_V1, b & 1);
    setf(ctx, 2, b);
    setf(ctx, 0, fpu::cvt_s_w(static_cast<u32>(alpha)));
    u32 i = 0;
    for (;; ++i) {
        charge(ctx, 5);
        setreg(ctx, GPR_V0, i < 4 ? 1 : 0);
        if (i >= 4) break;
        backedge(ctx);
        charge(ctx, 9 + 3 + 3 + 3 + 3 + 3 + 5);
        const u32 v = verts + i * kVtxSize;
        setreg(ctx, GPR_A2, v);
        swc1(ctx, v + kVtxZ, 5);
        swc1(ctx, v + kVtxRecipZ, 6);
        setf(ctx, 1, byte_to_float(r));
        swc1(ctx, v + kVtxR, 1);
        setf(ctx, 1, byte_to_float(g));
        swc1(ctx, v + kVtxG, 1);
        setf(ctx, 1, byte_to_float(b));
        swc1(ctx, v + kVtxB, 1);
        swc1(ctx, v + kVtxA, 0);
        setreg(ctx, GPR_V0, i + 1);
        setreg(ctx, GPR_T2, i + 1);
    }
    fade_draw(ctx, fv, verts);
}

// 0x00126710 sub_126710 -- 656 bytes; frame 0x160: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// 0x126710 two textured strips 512 wide: (x, y) .. (x + 512, y + 1024) and, 80 below, (x, 80 + (y + 1024)) ..
// (x + 512, 80 + 1024 + (y + 1024)), the raster *raster_ref, alpha from $a2, z = near screen z - $f12. The packed
// {x, y} argument is spilled to the frame (`sd $a1, 88($sp)`) and read back as floats.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_126710(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::cvt_s_w, hg::div_s,
          hg::enter, hg::jal, hg::jalr, hg::ld, hg::lq, hg::lw, hg::lwc1, hg::mov_s, hg::mtc1, hg::sd, hg::sll,
          hg::slti, hg::sq, hg::sub_s, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x00126710
    enter(ctx, 71);  // entry check point + this block's cycles
    sp = addiu(sp, -0x160);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s2 = a0;
    sd(a1, sp, 0x58);
    mov_s(f22, f12);
    s1 = a2;
    lwc1(f20, sp, 0x5C);
    jal(ctx, 0x126744u, gen::fn_sub_198590_00198590);
    v1 = 0x3F800000;
    mtc1(v1, f1);
    lwc1(f0, v0, 128);
    div_s(f21, f1, f0);
    s0 = 0x960000;
    s0 = addiu(s0, 144);  // &pfn_RwRenderStateSet
    a0 = 6;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x126770u, v0.u());
    a0 = 7;
    a1 = 2;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x126784u, v0.u());
    a0 = 8;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x126798u, v0.u());
    a0 = 11;
    a1 = 6;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x1267ACu, v0.u());
    a0 = 10;
    a1 = 5;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x1267C0u, v0.u());
    a0 = 9;
    a1 = 2;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x1267D4u, v0.u());
    a0 = 12;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x1267E8u, v0.u());
    a0 = 2;
    a1 = 4;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x1267FCu, v0.u());
    a0 = 0;
    v1 = 0x437F0000;
    mtc1(s1, f0);
    cvt_s_w(f1, f0);
    v0 = 0x960000;
    lwc1(f0, v0, 136);  // g_rwIm2DNearScreenZ
    sub_s(f0, f0, f22);
    for (;;) {
        // 0x00126854
        charge(ctx, 3);
        v0 = slti(a0, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0012682c
        charge(ctx, 10);
        v0 = sll(a0, 6);
        v0 = addu(v0, sp);
        v0 = addiu(v0, 96);
        sw(v1, v0, 32);
        sw(v1, v0, 36);
        sw(v1, v0, 40);
        swc1(f1, v0, 44);
        swc1(f0, v0, 8);
        swc1(f21, v0, 24);
        a0 = addiu(a0, 1);
    }
    // 0x00126860
    charge(ctx, 80);
    lwc1(f1, sp, 0x58);
    swc1(f1, sp, 0x60);
    swc1(f20, sp, 0x64);
    v0 = 0x44000000;
    mtc1(v0, f0);
    add_s(f21, f0, f1);
    swc1(f21, sp, 0xA0);
    swc1(f20, sp, 0xA4);
    swc1(f1, sp, 0xE0);
    v0 = 0x44800000;
    mtc1(v0, f0);
    add_s(f20, f0, f20);
    swc1(f20, sp, 0xE4);
    swc1(f21, sp, 0x120);
    swc1(f20, sp, 0x124);
    sw(zero, sp, 0x70);
    sw(zero, sp, 0x74);
    v0 = 0x3F800000;
    sw(v0, sp, 0xB0);
    sw(zero, sp, 0xB4);
    sw(zero, sp, 0xF0);
    sw(v0, sp, 0xF4);
    sw(v0, sp, 0x130);
    sw(v0, sp, 0x134);
    s1 = 0x960000;
    s1 = addiu(s1, 144);  // &pfn_RwRenderStateSet
    a0 = 1;
    lw(a1, s2, 0);
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x1268DCu, v0.u());
    s0 = 0x960000;
    s0 = addiu(s0, 160);  // &pfn_RwIm2DRenderPrimitive
    a0 = 4;
    a1 = addiu(sp, 0x60);
    a2 = a0;
    lw(v0, s0, 0);  // pfn_RwIm2DRenderPrimitive
    jalr(ctx, 0x1268FCu, v0.u());
    lwc1(f2, sp, 0x58);
    swc1(f2, sp, 0x60);
    v0 = 0x42A00000;
    mtc1(v0, f1);
    add_s(f0, f1, f20);
    swc1(f0, sp, 0x64);
    swc1(f21, sp, 0xA0);
    swc1(f0, sp, 0xA4);
    swc1(f2, sp, 0xE0);
    v0 = 0x44800000;
    mtc1(v0, f0);
    add_s(f0, f0, f20);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xE4);
    swc1(f21, sp, 0x120);
    swc1(f0, sp, 0x124);
    a0 = 1;
    lw(a1, s2, 0);
    lw(v0, s1, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x126958u, v0.u());
    a0 = 4;
    a1 = addiu(sp, 0x60);
    a2 = a0;
    lw(v0, s0, 0);  // pfn_RwIm2DRenderPrimitive
    jalr(ctx, 0x126970u, v0.u());
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x160);
}

// 0x00395570 dbgDrawRect -- 600 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// 0x395570 [dbgDrawRect] when obj+1648 is set: a red (200, 80, 80, 245) 512x512 outline at (obj+1652, obj+1656),
// a closed polyline of five vertices in the static buffer 0x958AA0, then the request is cleared. The fifth
// vertex's recipZ is never written (the fourth's is written twice), as in the original.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void dbgDrawRect(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::charge, hg::cvt_s_w, hg::div_s, hg::enter, hg::jal, hg::jalr, hg::ld,
          hg::lq, hg::lw, hg::lwc1, hg::mtc1, hg::sd, hg::sq, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4};
    // 0x00395570
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(v1, a0, 1648);
    if (v1 != 0) {
        // 0x00395594
        charge(ctx, 134);
        lw(s1, s2, 1652);
        lw(s0, s2, 1656);
        jal(ctx, 0x39559Cu, gen::fn_sub_198590_00198590);
        v1 = 0x3F800000;
        mtc1(v1, f1);
        lwc1(f0, v0, 128);
        div_s(f4, f1, f0);
        mtc1(s1, f0);
        cvt_s_w(f3, f0);
        v0 = 0x960000;
        swc1(f3, v0, -30048);  // 0x958AA0
        mtc1(s0, f0);
        cvt_s_w(f2, f0);
        v0 = 0x960000;
        swc1(f2, v0, -30044);  // 0x958AA4
        v0 = 0x960000;
        v0 = addiu(v0, 136);  // &g_rwIm2DNearScreenZ
        lwc1(f1, v0, 0);  // g_rwIm2DNearScreenZ
        v0 = 0x960000;
        swc1(f1, v0, -30040);  // 0x958AA8
        a0 = 0x43480000;
        v0 = 0x960000;
        sw(a0, v0, -30016);  // 0x958AC0
        v1 = 0x42A00000;
        v0 = 0x960000;
        sw(v1, v0, -30012);  // 0x958AC4
        v0 = 0x960000;
        sw(v1, v0, -30008);  // 0x958AC8
        v0 = 0x43750000;
        a1 = 0x960000;
        sw(v0, a1, -30004);  // 0x958ACC
        a1 = 0x960000;
        swc1(f4, a1, -30024);  // 0x958AB8
        a1 = addiu(s1, 512);
        mtc1(a1, f0);
        cvt_s_w(f0, f0);
        a1 = 0x960000;
        swc1(f0, a1, -29984);  // 0x958AE0
        a1 = 0x960000;
        swc1(f2, a1, -29980);  // 0x958AE4
        a1 = 0x960000;
        swc1(f1, a1, -29976);  // 0x958AE8
        a1 = 0x960000;
        sw(a0, a1, -29952);  // 0x958B00
        a1 = 0x960000;
        sw(v1, a1, -29948);  // 0x958B04
        a1 = 0x960000;
        sw(v1, a1, -29944);  // 0x958B08
        a1 = 0x960000;
        sw(v0, a1, -29940);  // 0x958B0C
        a1 = 0x960000;
        swc1(f4, a1, -29960);  // 0x958AF8
        a1 = 0x960000;
        swc1(f0, a1, -29920);  // 0x958B20
        a1 = addiu(s0, 512);
        mtc1(a1, f0);
        cvt_s_w(f0, f0);
        a1 = 0x960000;
        swc1(f0, a1, -29916);  // 0x958B24
        a1 = 0x960000;
        swc1(f1, a1, -29912);  // 0x958B28
        a1 = 0x960000;
        sw(a0, a1, -29888);  // 0x958B40
        a1 = 0x960000;
        sw(v1, a1, -29884);  // 0x958B44
        a1 = 0x960000;
        sw(v1, a1, -29880);  // 0x958B48
        a1 = 0x960000;
        sw(v0, a1, -29876);  // 0x958B4C
        a1 = 0x960000;
        swc1(f4, a1, -29896);  // 0x958B38
        a1 = 0x960000;
        swc1(f3, a1, -29856);  // 0x958B60
        a1 = 0x960000;
        swc1(f0, a1, -29852);  // 0x958B64
        a1 = 0x960000;
        swc1(f1, a1, -29848);  // 0x958B68
        a1 = 0x960000;
        sw(a0, a1, -29824);  // 0x958B80
        a1 = 0x960000;
        sw(v1, a1, -29820);  // 0x958B84
        a1 = 0x960000;
        sw(v1, a1, -29816);  // 0x958B88
        a1 = 0x960000;
        sw(v0, a1, -29812);  // 0x958B8C
        a1 = 0x960000;
        swc1(f4, a1, -29832);  // 0x958B78
        a1 = 0x960000;
        swc1(f3, a1, -29792);  // 0x958BA0
        a1 = 0x960000;
        swc1(f2, a1, -29788);  // 0x958BA4
        a1 = 0x960000;
        swc1(f1, a1, -29784);  // 0x958BA8
        a1 = 0x960000;
        sw(a0, a1, -29760);  // 0x958BC0
        a0 = 0x960000;
        sw(v1, a0, -29756);  // 0x958BC4
        a0 = 0x960000;
        sw(v1, a0, -29752);  // 0x958BC8
        v1 = 0x960000;
        sw(v0, v1, -29748);  // 0x958BCC
        v0 = 0x960000;
        swc1(f4, v0, -29832);  // 0x958B78
        s0 = 0x960000;
        s0 = addiu(s0, 144);  // &pfn_RwRenderStateSet
        a0 = 1;
        a1 = 0;
        lw(v0, s0, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x395758u, v0.u());
        a0 = 7;
        a1 = 2;
        lw(v0, s0, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x39576Cu, v0.u());
        a0 = 12;
        a1 = 1;
        lw(v0, s0, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x395780u, v0.u());
        a0 = 2;
        a1 = 0x960000;
        a1 = addiu(a1, -30048);  // &0x958AA0
        a2 = 5;
        v0 = 0x960000;
        lw(v0, v0, 160);  // pfn_RwIm2DRenderPrimitive
        jalr(ctx, 0x3957A0u, v0.u());
        sw(zero, s2, 1648);
    }
    // 0x003957ac (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002699D0 drawIm2DIndexedTriList -- 64 bytes; frame 0x10: ra sp+0x0
// 0x2699D0 [drawIm2DIndexedTriList] RwIm2DRenderIndexedPrimitive(rwPRIMTYPETRILIST, m->verts, m->num_verts, m->indices, m->num_indices) of a
// record {+0 verts, +4 indices, +16 num_verts, +20 num_indices}.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void drawIm2DIndexedTriList(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::enter, hg::jalr, hg::ld, hg::lw, hg::sd;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002699d0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = a0;
    a0 = 3;
    lw(a1, v0, 0);
    lw(a2, v0, 16);
    lw(a3, v0, 4);
    lw(t0, v0, 20);
    v0 = 0x960000;
    lw(v0, v0, 164);  // 0x9600A4
    jalr(ctx, 0x2699F8u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x269F50 a battle panel (work *(gp-18752)): when bit 0 of work+0 is set, Z write and Z test off, bilinear filter,
// the raster sub_266E50(kind) for kind = work+4 (0 or 1), and the four vertices at work+16 as the triangles
// (0, 1, 2) and (0, 2, 3).
void sub_269F50(EEContext& ctx) {
    guest::enter(ctx, 7);
    Frame f(ctx, 48);
    f.sd(GPR_RA, 32);
    f.sq(GPR_S1, 16);
    f.sq(GPR_S0, 0);
    constexpr s32 kGpPanel = -18752;  // 0x7CE3B0
    if (lwr(ctx, GPR_V1, gpvar(ctx, kGpPanel)) == 0) {
        charge(ctx, 5);
        k_assert(ctx, 0x269F78u, 0x68ED10u, 44);
    }
    charge(ctx, 6);
    const u32 work = lwr(ctx, GPR_S0, gpvar(ctx, kGpPanel));
    const u64 off = ~core::sext32(lw(ctx, work)) & 1;
    setreg64(ctx, GPR_V1, off);
    if (off == 0) {
        charge(ctx, 21);
        setreg(ctx, GPR_S1, kPfnRenderStateSet);
        state_set(ctx, 0x269FACu, rwRENDERSTATEZWRITEENABLE, 0);
        state_set(ctx, 0x269FC0u, rwRENDERSTATEZTESTENABLE, 0);
        state_set(ctx, 0x269FD4u, rwRENDERSTATETEXTUREFILTER, 2);
        const u32 kind = lwr(ctx, GPR_V1, work + 4);
        setreg(ctx, GPR_A0, 1);
        static constexpr u32 kPcsKind0[4] = {0x26A000u, 0x26A014u, 0x26A03Cu, 0x26A05Cu};
        static constexpr u32 kPcsKind1[4] = {0x26A06Cu, 0x26A080u, 0x26A0A8u, 0x26A0C8u};
        bool draw = true;
        const u32* pcs = kPcsKind1;
        if (kind == 1) {
            charge(ctx, 25);
        } else {
            charge(ctx, 2);
            if (kind == 0) {
                charge(ctx, 28);
                setreg(ctx, GPR_A0, 0);
                pcs = kPcsKind0;
            } else {
                charge(ctx, 2);
                draw = false;
            }
        }
        if (draw) {
            jal(ctx, pcs[0], gen::fn_sub_266E50_00266e50);
            const u64 raster = reg64(ctx, GPR_V0);
            setreg(ctx, GPR_A0, rwRENDERSTATETEXTURERASTER);
            setreg64(ctx, GPR_A1, raster);
            call_pfn(ctx, pcs[1], kPfnRenderStateSet);
            setreg(ctx, GPR_S1, kPfnIm2DRenderTriangle);
            const auto triangle = [&](u32 pc, u32 i1, u32 i2) {
                setreg(ctx, GPR_A0, work + 16);
                setreg(ctx, GPR_A1, 4);
                setreg(ctx, GPR_A2, 0);
                setreg(ctx, GPR_A3, i1);
                setreg(ctx, GPR_T0, i2);
                call_pfn(ctx, pc, kPfnIm2DRenderTriangle);
            };
            triangle(pcs[2], 1, 2);
            triangle(pcs[3], 2, 3);
        }
    }
    charge(ctx, 6);
}

// 0x002BC9C0 btlDrawTexturedQuad -- 780 bytes; frame 0x150: ra sp+0x40, s1 sp+0x30 (sq), s0 sp+0x20 (sq), f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// 0x2BC9C0 [btlDrawTexturedQuad] a textured, coloured quad (x $f12, y $f13, w $f14, h $f15) with texture origin
// (u $f16, v $f17) in raster pixels: the raster ($a1, may be 0 = untextured, uv left as they were) gives the
// normalising width/height (+12/+16); the colour $a0 is packed (r << 24) | (g << 16) | (b << 8) | a; drawn as an
// indexed triangle list with the six indices at 0x696DA8, Z test/write off, alpha blend, bilinear.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void btlDrawTexturedQuad(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::cvt_s_w, hg::div_s,
          hg::enter, hg::i64, hg::jal, hg::jalr, hg::ld, hg::lq, hg::lw, hg::lwc1, hg::mov_s, hg::mtc1, hg::sd,
          hg::sll, hg::sltiu, hg::sq, hg::srl, hg::swc1;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16}, f17{ctx, 17}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25};
    // 0x002bc9c0
    enter(ctx, 44);  // entry check point + this block's cycles
    sp = addiu(sp, -0x150);
    sd(ra, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    mov_s(f25, f12);
    mov_s(f24, f13);
    mov_s(f23, f14);
    mov_s(f22, f15);
    mov_s(f21, f16);
    mov_s(f20, f17);
    s0 = a0;
    s1 = a1;
    jal(ctx, 0x2BCA08u, gen::fn_sub_198590_00198590);
    v1 = 0x3F800000;
    mtc1(v1, f1);
    lwc1(f0, v0, 128);
    div_s(f6, f1, f0);
    v0 = 0x960000;
    lwc1(f5, v0, 136);  // g_rwIm2DNearScreenZ
    v0 = srl(s0, 24);
    t3 = v0 & 0xFF;
    v0 = srl(s0, 16);
    t2 = v0 & 0xFF;
    v0 = srl(s0, 8);
    t1 = v0 & 0xFF;
    t0 = s0 & 0xFF;
    t4 = 0;
    a2 = t3 & 0x1;
    mtc1(t3, f4);
    a1 = t2 & 0x1;
    mtc1(t2, f3);
    a0 = t1 & 0x1;
    mtc1(t1, f2);
    v1 = t0 & 0x1;
    mtc1(t0, f1);
    for (;;) {
        // 0x002bcb48
        charge(ctx, 3);
        v0 = sltiu(t4, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002bca70
        charge(ctx, 6);
        v0 = sll(t4, 6);
        v0 = addu(v0, sp);
        a3 = addiu(v0, 80);
        swc1(f6, a3, 24);
        if (i64(t3) < 0) {
            // 0x002bca94
            charge(ctx, 6);
            v0 = srl(t3, 1);
            v0 = v0 | a2;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f0, f0);
        } else {
            // 0x002bca88
            charge(ctx, 3);
            cvt_s_w(f0, f4);
        }
        // 0x002bcaac
        charge(ctx, 3);
        swc1(f0, a3, 32);
        if (i64(t2) < 0) {
            // 0x002bcac4
            charge(ctx, 6);
            v0 = srl(t2, 1);
            v0 = v0 | a1;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f0, f0);
        } else {
            // 0x002bcab8
            charge(ctx, 3);
            cvt_s_w(f0, f3);
        }
        // 0x002bcadc
        charge(ctx, 3);
        swc1(f0, a3, 36);
        if (i64(t1) < 0) {
            // 0x002bcaf4
            charge(ctx, 6);
            v0 = srl(t1, 1);
            v0 = v0 | a0;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f0, f0);
        } else {
            // 0x002bcae8
            charge(ctx, 3);
            cvt_s_w(f0, f2);
        }
        // 0x002bcb0c
        charge(ctx, 3);
        swc1(f0, a3, 40);
        if (i64(t0) < 0) {
            // 0x002bcb24
            charge(ctx, 6);
            v0 = srl(t0, 1);
            v0 = v0 | v1;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f0, f0);
        } else {
            // 0x002bcb18
            charge(ctx, 3);
            cvt_s_w(f0, f1);
        }
        // 0x002bcb3c
        charge(ctx, 3);
        swc1(f0, a3, 44);
        swc1(f5, a3, 8);
        t4 = addiu(t4, 1);
    }
    // 0x002bcb54
    charge(ctx, 2);
    if (s1 != 0) {
        // 0x002bcb5c
        charge(ctx, 18);
        lwc1(f0, s1, 12);
        cvt_s_w(f3, f0);
        lwc1(f0, s1, 16);
        cvt_s_w(f1, f0);
        div_s(f0, f21, f3);
        swc1(f0, sp, 0x60);
        div_s(f2, f20, f1);
        swc1(f2, sp, 0x64);
        swc1(f0, sp, 0xA0);
        add_s(f0, f20, f22);
        div_s(f1, f0, f1);
        swc1(f1, sp, 0xA4);
        add_s(f0, f21, f23);
        div_s(f0, f0, f3);
        swc1(f0, sp, 0xE0);
        swc1(f1, sp, 0xE4);
        swc1(f0, sp, 0x120);
        swc1(f2, sp, 0x124);
    }
    // 0x002bcba4
    charge(ctx, 74);
    s0 = 0x960000;
    s0 = addiu(s0, 144);  // &pfn_RwRenderStateSet
    a0 = 6;
    a1 = 0;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x2BCBB8u, v0.u());
    a0 = 7;
    a1 = 2;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x2BCBCCu, v0.u());
    a0 = 8;
    a1 = 0;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x2BCBE0u, v0.u());
    a0 = 10;
    a1 = 5;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x2BCBF4u, v0.u());
    a0 = 11;
    a1 = 6;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x2BCC08u, v0.u());
    a0 = 9;
    a1 = 2;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x2BCC1Cu, v0.u());
    a0 = 12;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x2BCC30u, v0.u());
    a0 = 1;
    a1 = s1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x2BCC44u, v0.u());
    swc1(f25, sp, 0x50);
    swc1(f24, sp, 0x54);
    swc1(f25, sp, 0x90);
    add_s(f1, f24, f22);
    swc1(f1, sp, 0x94);
    add_s(f0, f25, f23);
    swc1(f0, sp, 0xD0);
    swc1(f1, sp, 0xD4);
    swc1(f0, sp, 0x110);
    swc1(f24, sp, 0x114);
    a0 = 3;
    a1 = addiu(sp, 0x50);
    a2 = 4;
    a3 = 0x690000;
    a3 = addiu(a3, 28072);  // &0x696DA8
    t0 = 6;
    v0 = 0x960000;
    lw(v0, v0, 164);  // 0x9600A4
    jalr(ctx, 0x2BCC94u, v0.u());
    ld(ra, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f25, sp, 0x14);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x150);
}

// 0x00422670 sub_422670 -- 804 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// 0x422670 [a cursor-style quad task] the H_Cursor draw with a 16-byte header: work +0 s8 state (0 / 1 build,
// 2 finished -> -1), +16 four vertices, +272 four RGBA byte quads, +296 / +300 int width / height, +304 z offset,
// +308 / +312 position, +318 s8 hidden (1 = draw nothing).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_422670(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::cvt_s_w, hg::div_s,
          hg::enter, hg::i64, hg::jal, hg::jalr, hg::lb, hg::lbu, hg::ld, hg::lq, hg::lw, hg::lwc1, hg::mtc1, hg::sb,
          hg::sd, hg::si, hg::sll, hg::slti, hg::sq, hg::srl, hg::sub_s, hg::swc1;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x00422670
    enter(ctx, 51);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, 60);
    s0 = 0x960000;
    s0 = addiu(s0, 144);  // &pfn_RwRenderStateSet
    a0 = 6;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x422698u, v0.u());
    a0 = 7;
    a1 = 2;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x4226ACu, v0.u());
    a0 = 8;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x4226C0u, v0.u());
    a0 = 10;
    a1 = 5;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x4226D4u, v0.u());
    a0 = 11;
    a1 = 6;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x4226E8u, v0.u());
    a0 = 9;
    a1 = 2;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x4226FCu, v0.u());
    a0 = 12;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x422710u, v0.u());
    a0 = 1;
    a1 = 0;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x422724u, v0.u());
    lb(v0, s1, 318);
    a0 = 1;
    if (v0 != a0) {
        // 0x00422748
        charge(ctx, 4);
        lb(v1, s1, 0);
        v0 = 2;
        if (v1 == v0) {
            // 0x0042296c
            charge(ctx, 3);
            v0 = si(-1);
        } else {
            // 0x00422758
            charge(ctx, 2);
            if (v1 != a0) {
                // 0x00422760
                charge(ctx, 2);
                if (v1 == 0) {
                    goto L_00422770;
                }
                // 0x00422768
                charge(ctx, 2);
                goto L_00422978;
            }
        L_00422770:
            charge(ctx, 11);
            jal(ctx, 0x422770u, gen::fn_sub_198590_00198590);
            v1 = 0x3F800000;
            mtc1(v1, f1);
            lwc1(f0, v0, 128);
            div_s(f2, f1, f0);
            a3 = 0;
            v0 = 0x960000;
            for (;;) {
                // 0x004228c4
                charge(ctx, 3);
                v1 = slti(a3, 4);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0042279c
                charge(ctx, 12);
                v1 = sll(a3, 6);
                a2 = addu(s1, v1);
                lwc1(f1, v0, 136);
                lwc1(f0, s1, 304);
                sub_s(f0, f1, f0);
                swc1(f0, a2, 24);
                swc1(f2, a2, 40);
                v1 = sll(a3, 2);
                a1 = addu(s1, v1);
                lbu(v1, a1, 272);
                if (i64(v1) < 0) {
                    // 0x004227e0
                    charge(ctx, 7);
                    a0 = srl(v1, 1);
                    v1 = v1 & 0x1;
                    a0 = a0 | v1;
                    mtc1(a0, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f0);
                } else {
                    // 0x004227cc
                    charge(ctx, 5);
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                }
                // 0x004227fc
                charge(ctx, 4);
                swc1(f0, a2, 48);
                lbu(v1, a1, 273);
                if (i64(v1) < 0) {
                    // 0x00422820
                    charge(ctx, 7);
                    a0 = srl(v1, 1);
                    v1 = v1 & 0x1;
                    a0 = a0 | v1;
                    mtc1(a0, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f0);
                } else {
                    // 0x0042280c
                    charge(ctx, 5);
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                }
                // 0x0042283c
                charge(ctx, 4);
                swc1(f0, a2, 52);
                lbu(v1, a1, 274);
                if (i64(v1) < 0) {
                    // 0x00422860
                    charge(ctx, 7);
                    a0 = srl(v1, 1);
                    v1 = v1 & 0x1;
                    a0 = a0 | v1;
                    mtc1(a0, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f0);
                } else {
                    // 0x0042284c
                    charge(ctx, 5);
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                }
                // 0x0042287c
                charge(ctx, 4);
                swc1(f0, a2, 56);
                lbu(v1, a1, 275);
                if (i64(v1) < 0) {
                    // 0x004228a0
                    charge(ctx, 7);
                    a0 = srl(v1, 1);
                    v1 = v1 & 0x1;
                    a0 = a0 | v1;
                    mtc1(a0, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f0);
                } else {
                    // 0x0042288c
                    charge(ctx, 5);
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                }
                // 0x004228bc
                charge(ctx, 2);
                swc1(f0, a2, 60);
                a3 = addiu(a3, 1);
            }
            // 0x004228d0
            charge(ctx, 39);
            lwc1(f0, s1, 308);
            swc1(f0, s1, 16);
            lwc1(f0, s1, 312);
            swc1(f0, s1, 20);
            lwc1(f1, s1, 308);
            lwc1(f0, s1, 296);
            cvt_s_w(f0, f0);
            add_s(f0, f1, f0);
            swc1(f0, s1, 80);
            lwc1(f0, s1, 312);
            swc1(f0, s1, 84);
            lwc1(f0, s1, 308);
            swc1(f0, s1, 144);
            lwc1(f1, s1, 312);
            lwc1(f0, s1, 300);
            cvt_s_w(f0, f0);
            add_s(f0, f1, f0);
            swc1(f0, s1, 148);
            lwc1(f1, s1, 308);
            lwc1(f0, s1, 296);
            cvt_s_w(f0, f0);
            add_s(f0, f1, f0);
            swc1(f0, s1, 208);
            lwc1(f1, s1, 312);
            lwc1(f0, s1, 300);
            cvt_s_w(f0, f0);
            add_s(f0, f1, f0);
            swc1(f0, s1, 212);
            a0 = 4;
            a1 = addiu(s1, 16);
            a2 = a0;
            v0 = 0x960000;
            lw(v0, v0, 160);  // pfn_RwIm2DRenderPrimitive
            jalr(ctx, 0x422954u, v0.u());
            v0 = 1;
            sb(v0, s1, 0);
        L_00422978:
            charge(ctx, 1);
            v0 = 0;
        }
    } else {
        // 0x0042273c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0042297c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001997E0 drawGradientQuad -- 1144 bytes; frame 0x110: ra sp+0x0
// 0x1997E0 [drawGradientQuad] a vertical-gradient quad: corners (x0 $f12, y0 $f13) .. (x1 $f14, y1 $f15) at z $f16
// with recipZ $f17, the top colour bytes at $a0 and the bottom ones at $a1 (RGBA), untextured state left as the
// caller set it; a triangle strip of the four vertices on the stack. Returns 1.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void drawGradientQuad(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::charge, hg::cvt_s_w, hg::enter, hg::i64, hg::jalr, hg::lbu,
          hg::ld, hg::lw, hg::mtc1, hg::sd, hg::srl, hg::swc1;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16}, f17{ctx, 17};
    // 0x001997e0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x110);
    sd(ra, sp, 0x0);
    swc1(f12, sp, 0x10);
    swc1(f13, sp, 0x14);
    swc1(f16, sp, 0x18);
    lbu(v0, a0, 0);
    if (i64(v0) < 0) {
        // 0x00199814
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x00199800
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x00199830
    charge(ctx, 4);
    swc1(f0, sp, 0x30);
    lbu(v0, a0, 1);
    if (i64(v0) < 0) {
        // 0x00199854
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x00199840
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x00199870
    charge(ctx, 4);
    swc1(f0, sp, 0x34);
    lbu(v0, a0, 2);
    if (i64(v0) < 0) {
        // 0x00199894
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x00199880
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x001998b0
    charge(ctx, 4);
    swc1(f0, sp, 0x38);
    lbu(v0, a0, 3);
    if (i64(v0) < 0) {
        // 0x001998d4
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x001998c0
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x001998f0
    charge(ctx, 8);
    swc1(f0, sp, 0x3C);
    swc1(f17, sp, 0x28);
    swc1(f12, sp, 0x50);
    swc1(f15, sp, 0x54);
    swc1(f16, sp, 0x58);
    lbu(v0, a1, 0);
    if (i64(v0) < 0) {
        // 0x00199924
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x00199910
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x00199940
    charge(ctx, 4);
    swc1(f0, sp, 0x70);
    lbu(v0, a1, 1);
    if (i64(v0) < 0) {
        // 0x00199964
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x00199950
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x00199980
    charge(ctx, 4);
    swc1(f0, sp, 0x74);
    lbu(v0, a1, 2);
    if (i64(v0) < 0) {
        // 0x001999a4
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x00199990
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x001999c0
    charge(ctx, 4);
    swc1(f0, sp, 0x78);
    lbu(v0, a1, 3);
    if (i64(v0) < 0) {
        // 0x001999e4
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x001999d0
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x00199a00
    charge(ctx, 8);
    swc1(f0, sp, 0x7C);
    swc1(f17, sp, 0x68);
    swc1(f14, sp, 0x90);
    swc1(f13, sp, 0x94);
    swc1(f16, sp, 0x98);
    lbu(v0, a0, 0);
    if (i64(v0) < 0) {
        // 0x00199a34
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x00199a20
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x00199a50
    charge(ctx, 4);
    swc1(f0, sp, 0xB0);
    lbu(v0, a0, 1);
    if (i64(v0) < 0) {
        // 0x00199a74
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x00199a60
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x00199a90
    charge(ctx, 4);
    swc1(f0, sp, 0xB4);
    lbu(v0, a0, 2);
    if (i64(v0) < 0) {
        // 0x00199ab4
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x00199aa0
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x00199ad0
    charge(ctx, 4);
    swc1(f0, sp, 0xB8);
    lbu(v0, a0, 3);
    if (i64(v0) < 0) {
        // 0x00199af4
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x00199ae0
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x00199b10
    charge(ctx, 8);
    swc1(f0, sp, 0xBC);
    swc1(f17, sp, 0xA8);
    swc1(f14, sp, 0xD0);
    swc1(f15, sp, 0xD4);
    swc1(f16, sp, 0xD8);
    lbu(v0, a1, 0);
    if (i64(v0) < 0) {
        // 0x00199b44
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x00199b30
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x00199b60
    charge(ctx, 4);
    swc1(f0, sp, 0xF0);
    lbu(v0, a1, 1);
    if (i64(v0) < 0) {
        // 0x00199b84
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x00199b70
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x00199ba0
    charge(ctx, 4);
    swc1(f0, sp, 0xF4);
    lbu(v0, a1, 2);
    if (i64(v0) < 0) {
        // 0x00199bc4
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x00199bb0
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x00199be0
    charge(ctx, 4);
    swc1(f0, sp, 0xF8);
    lbu(v0, a1, 3);
    if (i64(v0) < 0) {
        // 0x00199c04
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x00199bf0
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
    }
    // 0x00199c20
    charge(ctx, 14);
    swc1(f0, sp, 0xFC);
    swc1(f17, sp, 0xE8);
    a0 = 4;
    a1 = addiu(sp, 0x10);
    a2 = a0;
    v0 = 0x960000;
    lw(v0, v0, 160);  // pfn_RwIm2DRenderPrimitive
    jalr(ctx, 0x199C3Cu, v0.u());
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x110);
}

// 0x003B38F0 frFontRasterDrawGlyph -- 1124 bytes; frame 0x1C0: ra sp+0x70, s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// 0x3B38F0 frFontRasterDrawGlyph(x * 16, y * 8, font, code, w, h, rgba; $f12 z offset): one glyph of the text
// renderer as a textured quad. The glyph's raster slot (font+28 -> +12) is refreshed through frFontCacheGlyph
// when it holds another code (the old slot's use count drops; at 0 its GS entry is released and the raster count
// at 0x95AE10 decremented), the slot is marked used (bit 0), and, unless the colour's alpha byte is 0, the four
// vertices are built on the stack (positions (x, y) .. (x + w, y + h), uv from the static table 0x6A28D0) and drawn
// as a triangle strip with the slot's raster. The position table and the uv copy are local arrays (the inlined
// 32-byte clear and the 4 x 8-byte copy loops are kept, with their check points).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void frFontRasterDrawGlyph(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::cvt_s_w, hg::div_s,
          hg::enter, hg::i64, hg::jal, hg::jalr, hg::ld, hg::lh, hg::lhu, hg::lq, hg::lw, hg::lwc1, hg::mov_s,
          hg::mtc1, hg::sb, hg::sd, hg::sh, hg::si, hg::sll, hg::slti, hg::sq, hg::srl, hg::sub_s, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    // 0x003b38f0
    enter(ctx, 46);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1C0);
    sd(ra, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    mov_s(f23, f12);
    s2 = a2;
    s1 = a3;
    s5 = t0;
    s4 = t1;
    s0 = t2;
    mtc1(a0, f0);
    cvt_s_w(f1, f0);
    v0 = 0x41800000;
    mtc1(v0, f0);
    div_s(f22, f1, f0);
    mtc1(a1, f0);
    cvt_s_w(f1, f0);
    v0 = 0x41000000;
    mtc1(v0, f0);
    div_s(f21, f1, f0);
    jal(ctx, 0x3B397Cu, gen::fn_sub_198590_00198590);
    v1 = 0x3F800000;
    mtc1(v1, f1);
    lwc1(f0, v0, 128);
    div_s(f20, f1, f0);
    s3 = s0 & 0xFF;
    a2 = 0x6A0000;
    a2 = addiu(a2, 10448);  // &0x6A28D0
    a1 = addiu(sp, 0xA0);
    a0 = 4;
    for (;;) {
        // 0x003b39a8
        charge(ctx, 9);
        lw(v1, a2, 0);
        lw(v0, a2, 4);
        a2 = addiu(a2, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003b39cc
    charge(ctx, 4);
    v1 = addiu(sp, 0x80);
    v0 = 32;
    if (v1 != 0) {
        for (;;) {
            // 0x003b39dc
            charge(ctx, 7);
            sb(zero, v1, 0);
            v1 = addiu(v1, 1);
            v0 = addiu(v0, -1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x003b39f8
    charge(ctx, 4);
    swc1(f22, sp, 0x80);
    swc1(f21, sp, 0x84);
    if (i64(s5) < 0) {
        // 0x003b3a1c
        charge(ctx, 7);
        v1 = srl(s5, 1);
        v0 = s5 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x003b3a08
        charge(ctx, 5);
        mtc1(s5, f0);
        cvt_s_w(f0, f0);
    }
    // 0x003b3a38
    charge(ctx, 6);
    add_s(f1, f22, f0);
    swc1(f1, sp, 0x88);
    swc1(f21, sp, 0x8C);
    swc1(f22, sp, 0x90);
    if (i64(s4) < 0) {
        // 0x003b3a64
        charge(ctx, 7);
        v1 = srl(s4, 1);
        v0 = s4 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x003b3a50
        charge(ctx, 5);
        mtc1(s4, f0);
        cvt_s_w(f0, f0);
    }
    // 0x003b3a80
    charge(ctx, 7);
    add_s(f0, f21, f0);
    swc1(f0, sp, 0x94);
    swc1(f1, sp, 0x98);
    swc1(f0, sp, 0x9C);
    lw(v0, s2, 28);
    if (v0 == 0) {
        // 0x003b3a9c
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 10392);  // "frFontRaster.c"
        a1 = 153;
        jal(ctx, 0x3B3AA8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003b3ab0
    charge(ctx, 5);
    lw(v0, s2, 28);
    lw(s4, v0, 12);
    lh(v0, s4, 8);
    if (v0 != s1) {
        // 0x003b3ac4
        charge(ctx, 12);
        a0 = s2;
        lw(a1, s4, 4);
        jal(ctx, 0x3B3ACCu, gen::fn_frFontCacheGlyph_003b0430);
        s1 = v0;
        lw(v1, s2, 28);
        lhu(v0, v1, 4);
        v0 = addiu(v0, -1);
        sh(v0, v1, 4);
        lw(a1, s2, 28);
        if (a1 != 0) {
            // 0x003b3af4
            charge(ctx, 3);
            lhu(v0, a1, 4);
            if (v0 == 0) {
                // 0x003b3b00
                charge(ctx, 3);
                lw(a0, a1, 12);
                if (a0 != 0) {
                    // 0x003b3b0c
                    charge(ctx, 5);
                    lw(v1, a0, 0);
                    v0 = si(-2);
                    v0 = v1 & v0;
                    sw(v0, a0, 0);
                    sw(zero, a0, 16);
                }
                // 0x003b3b20
                charge(ctx, 8);
                lw(a0, a1, 8);
                jal(ctx, 0x3B3B24u, gen::fn_fmGslReleaseEntry_003b4580);
                v0 = 0x960000;
                lw(v0, v0, -20976);  // 0x95AE10
                v1 = addiu(v0, -1);
                v0 = 0x960000;
                sw(v1, v0, -20976);  // 0x95AE10
            }
        }
        // 0x003b3b40
        charge(ctx, 2);
        sw(s1, s2, 28);
        lw(s4, s1, 12);
    }
    // 0x003b3b48
    charge(ctx, 5);
    lw(v0, s4, 0);
    v0 = v0 | 0x1;
    sw(v0, s4, 0);
    if (s3 != 0) {
        // 0x003b3b68
        charge(ctx, 25);
        a0 = addiu(sp, 0xC0);
        a1 = 0;
        a2 = 256;
        jal(ctx, 0x3B3B74u, gen::fn_memset_00521408);
        v0 = 0x960000;
        lwc1(f0, v0, 136);  // g_rwIm2DNearScreenZ
        sub_s(f5, f0, f23);
        v0 = 0;
        a1 = srl(s0, 24);
        a0 = srl(s0, 16);
        v1 = srl(s0, 8);
        t2 = a1 & 0xFF;
        t1 = t2 & 0x1;
        mtc1(t2, f4);
        t0 = a0 & 0xFF;
        a3 = t0 & 0x1;
        mtc1(t0, f3);
        a2 = v1 & 0xFF;
        a1 = a2 & 0x1;
        mtc1(a2, f2);
        a0 = s3 & 0x1;
        mtc1(s3, f1);
        for (;;) {
            // 0x003b3cd8
            charge(ctx, 3);
            v1 = slti(v0, 4);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003b3bcc
            charge(ctx, 14);
            v1 = sll(v0, 6);
            v1 = addu(v1, sp);
            t4 = addiu(v1, 192);
            swc1(f5, t4, 8);
            swc1(f20, t4, 24);
            t3 = sll(v0, 3);
            v1 = addu(t3, sp);
            v1 = addiu(v1, 160);
            lwc1(f0, v1, 0);
            swc1(f0, t4, 16);
            lwc1(f0, v1, 4);
            swc1(f0, t4, 20);
            if (i64(t2) < 0) {
                // 0x003b3c10
                charge(ctx, 6);
                v1 = srl(t2, 1);
                v1 = v1 | t1;
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x003b3c04
                charge(ctx, 3);
                cvt_s_w(f0, f4);
            }
            // 0x003b3c28
            charge(ctx, 3);
            swc1(f0, t4, 32);
            if (i64(t0) < 0) {
                // 0x003b3c40
                charge(ctx, 6);
                v1 = srl(t0, 1);
                v1 = v1 | a3;
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x003b3c34
                charge(ctx, 3);
                cvt_s_w(f0, f3);
            }
            // 0x003b3c58
            charge(ctx, 3);
            swc1(f0, t4, 36);
            if (i64(a2) < 0) {
                // 0x003b3c70
                charge(ctx, 6);
                v1 = srl(a2, 1);
                v1 = v1 | a1;
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x003b3c64
                charge(ctx, 3);
                cvt_s_w(f0, f2);
            }
            // 0x003b3c88
            charge(ctx, 3);
            swc1(f0, t4, 40);
            if (i64(s3) < 0) {
                // 0x003b3ca0
                charge(ctx, 6);
                v1 = srl(s3, 1);
                v1 = v1 | a0;
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x003b3c94
                charge(ctx, 3);
                cvt_s_w(f0, f1);
            }
            // 0x003b3cb8
            charge(ctx, 8);
            swc1(f0, t4, 44);
            v1 = addu(t3, sp);
            v1 = addiu(v1, 128);
            lwc1(f0, v1, 0);
            swc1(f0, t4, 0);
            lwc1(f0, v1, 4);
            swc1(f0, t4, 4);
            v0 = addiu(v0, 1);
        }
        // 0x003b3ce4
        charge(ctx, 14);
        a0 = 1;
        lw(a1, s4, 20);
        v0 = 0x960000;
        lw(v0, v0, 144);  // pfn_RwRenderStateSet
        jalr(ctx, 0x3B3CF4u, v0.u());
        a0 = 4;
        a1 = addiu(sp, 0xC0);
        a2 = a0;
        v0 = 0x960000;
        lw(v0, v0, 160);  // pfn_RwIm2DRenderPrimitive
        jalr(ctx, 0x3B3D10u, v0.u());
        v0 = 0;
    } else {
        // 0x003b3b5c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b3d1c (the shared epilogue, written out on this path)
    charge(ctx, 14);
    ld(ra, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x1C0);
}

// 0x104420 [dbgPrintDrawScreen] the debug text screen: the 40 x 53 character grid at 0x7E1E30 drawn with the debug
// font raster (*(gp-20000), a 16 x 16 atlas of 12 x 11 cells for codes 32..), one textured white quad per non-space
// character at (12 col, 12 row) .. (12 col + 11, 12 row + 11); then the two debug overlays dbgPrintDrawStrings / dbgPrintDrawWindow.
// The render states are saved first (sub_196770).
void dbgPrintDrawScreen(EEContext& ctx) {
    guest::enter(ctx, 53);
    Frame f(ctx, 368);
    f.sd(GPR_RA, 64);
    f.sq(GPR_S2, 48);
    f.sq(GPR_S1, 32);
    f.sq(GPR_S0, 16);
    f.swc1(21, 4);
    f.swc1(20, 0);
    recip_near_plane(ctx, static_cast<u32>(main_camera(ctx, 0x10443Cu)), 20);
    setreg(ctx, GPR_S0, kPfnRenderStateSet);
    state_set(ctx, 0x104468u, rwRENDERSTATEZTESTENABLE, 1);
    state_set(ctx, 0x10447Cu, rwRENDERSTATESHADEMODE, 2);
    state_set(ctx, 0x104490u, rwRENDERSTATEZWRITEENABLE, 1);
    state_set(ctx, 0x1044A4u, rwRENDERSTATETEXTUREFILTER, 1);
    state_set(ctx, 0x1044B8u, rwRENDERSTATEVERTEXALPHAENABLE, 1);
    jal(ctx, 0x1044C0u, gen::fn_sub_196770_00196770);  // save the render states
    state_set(ctx, 0x1044D4u, rwRENDERSTATETEXTURERASTER, core::sext32(lw(ctx, gpvar(ctx, -20000))));
    const u32 verts = f.at(80);
    constexpr u32 k255 = 0x437F0000u;
    setreg(ctx, GPR_A0, 0);
    setreg(ctx, GPR_V1, k255);
    setf(ctx, 0, lw(ctx, kIm2DNearScreenZ));
    for (u32 i = 0;; ++i) {
        charge(ctx, 3);
        setreg(ctx, GPR_V0, i < 4 ? 1 : 0);
        if (i >= 4) break;
        backedge(ctx);
        charge(ctx, 10);
        const u32 v = verts + i * kVtxSize;
        setreg(ctx, GPR_V0, v);
        swc1(ctx, v + kVtxRecipZ, 20);
        for (u32 k = 0; k < 4; ++k) sw(ctx, v + kVtxR + 4 * k, k255);
        swc1(ctx, v + kVtxZ, 0);
        setreg(ctx, GPR_A0, i + 1);
    }
    charge(ctx, 3);
    const u32 uv = f.at(336);
    constexpr u32 k12 = 0x41400000u, k11 = 0x41300000u;
    for (u32 row = 0;; ++row) {
        charge(ctx, 3);
        setreg(ctx, GPR_S1, row);
        setreg(ctx, GPR_V0, row < 40 ? 1 : 0);
        if (row >= 40) break;
        backedge(ctx);
        charge(ctx, 18);
        setreg(ctx, GPR_S2, 0);
        ee::mult(ctx, ee::kPipe0, row, 53);
        setreg64(ctx, GPR_V1, ee::mflo(ctx));
        const u32 line = 0x7E1E30u + row * 53;
        setreg(ctx, GPR_S0, line);
        setreg(ctx, GPR_V0, k11);
        setf(ctx, 1, k12);
        setf(ctx, 0, fpu::cvt_s_w(row));
        fpu::mul_s(ctx, 21, 1, 0);  // top = 12 row
        setf(ctx, 0, k11);
        fpu::add_s(ctx, 20, 0, 21);  // bottom = 11 + 12 row
        for (u32 col = 0;; ++col) {
            charge(ctx, 3);
            setreg(ctx, GPR_S2, col);
            setreg(ctx, GPR_V0, col < 53 ? 1 : 0);
            if (col >= 53) break;
            backedge(ctx);
            charge(ctx, 5);
            const u32 ch = guest::load<u8>(ctx, line + col);
            setreg(ctx, GPR_V1, ch);
            setreg(ctx, GPR_V0, 32);
            if (ch != 32) {
                charge(ctx, 23);
                setf(ctx, 1, k12);
                setf(ctx, 0, fpu::cvt_s_w(col));
                fpu::mul_s(ctx, 1, 1, 0);  // left = 12 col
                swc1(ctx, verts + 0 * kVtxSize + kVtxX, 1);
                swc1(ctx, verts + 0 * kVtxSize + kVtxY, 21);
                setf(ctx, 0, k11);
                fpu::add_s(ctx, 0, 0, 1);  // right = 11 + 12 col
                swc1(ctx, verts + 1 * kVtxSize + kVtxX, 0);
                swc1(ctx, verts + 1 * kVtxSize + kVtxY, 21);
                swc1(ctx, verts + 2 * kVtxSize + kVtxX, 1);
                swc1(ctx, verts + 2 * kVtxSize + kVtxY, 20);
                swc1(ctx, verts + 3 * kVtxSize + kVtxX, 0);
                swc1(ctx, verts + 3 * kVtxSize + kVtxY, 20);
                const u32 glyph = ch - 32;  // the atlas cell: column glyph & 15, row (glyph & 0xFF) >> 4
                setreg(ctx, GPR_A0, glyph);
                charge(ctx, 28);
                constexpr u32 kCell = 0x3D800000u, kInset = 0x3D400000u;  // 1/16 and 0.75/16
                setf(ctx, 1, kCell);
                setf(ctx, 0, fpu::cvt_s_w(glyph & 15));
                fpu::mul_s(ctx, 3, 1, 0);  // u0
                swc1(ctx, uv + 0, 3);
                setf(ctx, 0, fpu::cvt_s_w((glyph & 0xFF) >> 4));
                fpu::mul_s(ctx, 2, 1, 0);  // v0
                swc1(ctx, uv + 4, 2);
                setreg(ctx, GPR_V0, kInset);
                setf(ctx, 0, kInset);
                fpu::add_s(ctx, 1, 0, 3);  // u1
                swc1(ctx, uv + 8, 1);
                swc1(ctx, uv + 12, 2);
                swc1(ctx, uv + 16, 3);
                fpu::add_s(ctx, 0, 0, 2);  // v1
                swc1(ctx, uv + 20, 0);
                swc1(ctx, uv + 24, 1);
                swc1(ctx, uv + 28, 0);
                setreg(ctx, GPR_V1, glyph & 15);
                setreg(ctx, GPR_A0, 0);
                for (u32 i = 0;; ++i) {
                    charge(ctx, 3);
                    setreg(ctx, GPR_V0, i < 4 ? 1 : 0);
                    if (i >= 4) break;
                    backedge(ctx);
                    charge(ctx, 11);
                    const u32 v = verts + i * kVtxSize;
                    setreg(ctx, GPR_V1, uv + 8 * i);
                    setreg(ctx, GPR_V0, v);
                    sw(ctx, v + kVtxU, lw(ctx, uv + 8 * i));
                    setf(ctx, 0, lw(ctx, uv + 8 * i + 4));
                    swc1(ctx, v + kVtxV, 0);
                    setreg(ctx, GPR_A0, i + 1);
                }
                charge(ctx, 7);
                setreg(ctx, GPR_A0, rwPRIMTYPETRISTRIP);
                setreg(ctx, GPR_A1, verts);
                setreg(ctx, GPR_A2, 4);
                call_pfn(ctx, 0x1046B4u, kPfnIm2DRenderPrimitive);
            }
            charge(ctx, 1);
        }
        charge(ctx, 1);
    }
    charge(ctx, 13);
    jal(ctx, 0x1046DCu, gen::fn_dbgPrintDrawStrings_00104710);
    jal(ctx, 0x1046E4u, gen::fn_dbgPrintDrawWindow_001053f0);
}

// 0x1053F0 [dbgPrintDrawWindow] the debug window, while *(gp-20016) is set: a grey (64, 64, 64, 128) 496 x 196
// panel at the 64-bit position pair *(gp-31328), then (s8)*(gp-20012) lines of the 256-byte text buffer 0x7E0A30
// (each up to 53 characters or its NUL) in the debug font at *(gp-31320) + (12 col, 12 row). The position pairs are
// copied to the frame with `ld`/`sd` (the text one once per character, as the original does).
void dbgPrintDrawWindow(EEContext& ctx) {
    guest::enter(ctx, 19);
    Frame f(ctx, 400);
    f.sd(GPR_RA, 80);
    f.sq(GPR_S3, 64);
    f.sq(GPR_S2, 48);
    f.sq(GPR_S1, 32);
    f.sq(GPR_S0, 16);
    f.swc1(21, 4);
    f.swc1(20, 0);
    recip_near_plane(ctx, static_cast<u32>(main_camera(ctx, 0x105410u)), 20);
    if (lwr(ctx, GPR_V1, gpvar(ctx, -20016)) != 0) {
        charge(ctx, 43);
        setreg(ctx, GPR_S0, kPfnRenderStateSet);
        state_set(ctx, 0x105450u, rwRENDERSTATEZTESTENABLE, 1);
        state_set(ctx, 0x105464u, rwRENDERSTATESHADEMODE, 2);
        state_set(ctx, 0x105478u, rwRENDERSTATEZWRITEENABLE, 1);
        state_set(ctx, 0x10548Cu, rwRENDERSTATETEXTUREFILTER, 1);
        state_set(ctx, 0x1054A0u, rwRENDERSTATEVERTEXALPHAENABLE, 1);
        const u32 panel_pos = f.at(392), text_pos = f.at(384);
        const u64 panel_xy = guest::load<u64>(ctx, gpvar(ctx, -31328));
        setreg64(ctx, GPR_V0, panel_xy);
        guest::store<u64>(ctx, panel_pos, panel_xy);
        jal(ctx, 0x1054B0u, gen::fn_sub_196770_00196770);  // save the render states
        state_set(ctx, 0x1054C4u, rwRENDERSTATETEXTURERASTER, 0);
        const u32 verts = f.at(96);
        // The panel's vertices: z, recipZ, colour (64, 64, 64, 128).
        constexpr u32 k64 = 0x42800000u, k128 = 0x43000000u, k255 = 0x437F0000u;
        setreg(ctx, GPR_A1, 0);
        setreg(ctx, GPR_A0, k64);
        setreg(ctx, GPR_V1, k128);
        setf(ctx, 0, lw(ctx, kIm2DNearScreenZ));
        for (u32 i = 0;; ++i) {
            charge(ctx, 3);
            setreg(ctx, GPR_V0, i < 4 ? 1 : 0);
            if (i >= 4) break;
            backedge(ctx);
            charge(ctx, 10);
            const u32 v = verts + i * kVtxSize;
            setreg(ctx, GPR_V0, v);
            swc1(ctx, v + kVtxRecipZ, 20);
            sw(ctx, v + kVtxR, k64);
            sw(ctx, v + kVtxG, k64);
            sw(ctx, v + kVtxB, k64);
            sw(ctx, v + kVtxA, k128);
            swc1(ctx, v + kVtxZ, 0);
            setreg(ctx, GPR_A1, i + 1);
        }
        charge(ctx, 44);
        // Corners (x, y), (16 + (480 + x), y), (x, 16 + (180 + y)), (16 + (480 + x), 16 + (180 + y)).
        lwc1(ctx, 4, panel_pos);
        swc1(ctx, verts + 0 * kVtxSize + kVtxX, 4);
        lwc1(ctx, 3, panel_pos + 4);
        swc1(ctx, verts + 0 * kVtxSize + kVtxY, 3);
        setf(ctx, 0, 0x43F00000u);
        fpu::add_s(ctx, 0, 0, 4);
        setf(ctx, 2, 0x41800000u);
        fpu::add_s(ctx, 1, 2, 0);
        swc1(ctx, verts + 1 * kVtxSize + kVtxX, 1);
        swc1(ctx, verts + 1 * kVtxSize + kVtxY, 3);
        swc1(ctx, verts + 2 * kVtxSize + kVtxX, 4);
        setreg(ctx, GPR_V0, 0x43340000u);
        setf(ctx, 0, 0x43340000u);
        fpu::add_s(ctx, 0, 0, 3);
        fpu::add_s(ctx, 0, 2, 0);
        swc1(ctx, verts + 2 * kVtxSize + kVtxY, 0);
        swc1(ctx, verts + 3 * kVtxSize + kVtxX, 1);
        swc1(ctx, verts + 3 * kVtxSize + kVtxY, 0);
        setreg(ctx, GPR_S1, kPfnIm2DRenderPrimitive);
        setreg(ctx, GPR_A0, rwPRIMTYPETRISTRIP);
        setreg(ctx, GPR_A1, verts);
        setreg(ctx, GPR_A2, 4);
        call_pfn(ctx, 0x105590u, kPfnIm2DRenderPrimitive);
        jal(ctx, 0x105598u, gen::fn_sub_196770_00196770);
        state_set(ctx, 0x1055ACu, rwRENDERSTATETEXTURERASTER, core::sext32(lw(ctx, gpvar(ctx, -20000))));
        // The text vertices: white.
        setreg(ctx, GPR_A1, 0);
        setreg(ctx, GPR_A0, k255);
        setf(ctx, 0, lw(ctx, kIm2DNearScreenZ));
        for (u32 i = 0;; ++i) {
            charge(ctx, 3);
            setreg(ctx, GPR_V1, i < 4 ? 1 : 0);
            if (i >= 4) break;
            backedge(ctx);
            charge(ctx, 10);
            const u32 v = verts + i * kVtxSize;
            setreg(ctx, GPR_V1, v);
            swc1(ctx, v + kVtxRecipZ, 20);
            for (u32 k = 0; k < 4; ++k) sw(ctx, v + kVtxR + 4 * k, k255);
            swc1(ctx, v + kVtxZ, 0);
            setreg(ctx, GPR_A1, i + 1);
        }
        charge(ctx, 3);
        const u32 uv = f.at(352);
        constexpr u32 k12 = 0x41400000u, k11 = 0x41300000u;
        for (u32 line = 0;; ++line) {
            charge(ctx, 4);
            setreg(ctx, GPR_S2, line);
            const s32 lines = guest::load<s8>(ctx, gpvar(ctx, -20012));
            const bool more = static_cast<s32>(line) < lines;
            setreg(ctx, GPR_V1, more ? 1 : 0);
            if (!more) break;
            backedge(ctx);
            charge(ctx, 17);
            setreg(ctx, GPR_A0, line << 8);
            const u32 text = 0x7E0A30u + (line << 8);
            setreg(ctx, GPR_S0, text);
            setreg(ctx, GPR_S3, 0);
            setreg(ctx, GPR_V1, k11);
            setf(ctx, 1, k12);
            setf(ctx, 0, fpu::cvt_s_w(line));
            fpu::mul_s(ctx, 21, 1, 0);  // 12 row
            setf(ctx, 0, k11);
            fpu::add_s(ctx, 20, 0, 21);  // 11 + 12 row
            for (u32 col = 0;; ++col) {
                charge(ctx, 3);
                setreg(ctx, GPR_S3, col);
                setreg(ctx, GPR_V1, col < 53 ? 1 : 0);
                if (col >= 53) break;
                backedge(ctx);
                charge(ctx, 6);
                const u64 text_xy = guest::load<u64>(ctx, gpvar(ctx, -31320));
                guest::store<u64>(ctx, text_pos, text_xy);
                setreg(ctx, GPR_V1, text + col);
                const u32 ch = guest::load<u8>(ctx, text + col);
                setreg(ctx, GPR_A0, ch);
                if (ch == 0) break;  // end of the line (L_1057C4)
                charge(ctx, 3);
                setreg(ctx, GPR_V1, 32);
                if (ch != 32) {
                    charge(ctx, 29);
                    setf(ctx, 1, k12);
                    setf(ctx, 0, fpu::cvt_s_w(col));
                    fpu::mul_s(ctx, 5, 1, 0);  // 12 col
                    lwc1(ctx, 1, text_pos);
                    fpu::add_s(ctx, 4, 5, 1);  // 12 col + x
                    swc1(ctx, verts + 0 * kVtxSize + kVtxX, 4);
                    lwc1(ctx, 3, text_pos + 4);
                    fpu::add_s(ctx, 2, 21, 3);  // 12 row + y
                    swc1(ctx, verts + 0 * kVtxSize + kVtxY, 2);
                    setf(ctx, 0, k11);
                    fpu::add_s(ctx, 0, 0, 5);
                    fpu::add_s(ctx, 1, 0, 1);  // (11 + 12 col) + x
                    swc1(ctx, verts + 1 * kVtxSize + kVtxX, 1);
                    swc1(ctx, verts + 1 * kVtxSize + kVtxY, 2);
                    swc1(ctx, verts + 2 * kVtxSize + kVtxX, 4);
                    fpu::add_s(ctx, 0, 20, 3);  // (11 + 12 row) + y
                    swc1(ctx, verts + 2 * kVtxSize + kVtxY, 0);
                    swc1(ctx, verts + 3 * kVtxSize + kVtxX, 1);
                    swc1(ctx, verts + 3 * kVtxSize + kVtxY, 0);
                    const u32 glyph = ch - 32;
                    setreg(ctx, GPR_A0, glyph);
                    charge(ctx, 28);
                    constexpr u32 kCell = 0x3D800000u, kInset = 0x3D400000u;
                    setf(ctx, 1, kCell);
                    setf(ctx, 0, fpu::cvt_s_w(glyph & 15));
                    fpu::mul_s(ctx, 3, 1, 0);
                    swc1(ctx, uv + 0, 3);
                    setf(ctx, 0, fpu::cvt_s_w((glyph & 0xFF) >> 4));
                    fpu::mul_s(ctx, 2, 1, 0);
                    swc1(ctx, uv + 4, 2);
                    setreg(ctx, GPR_V0, kInset);
                    setf(ctx, 0, kInset);
                    fpu::add_s(ctx, 1, 0, 3);
                    swc1(ctx, uv + 8, 1);
                    swc1(ctx, uv + 12, 2);
                    swc1(ctx, uv + 16, 3);
                    fpu::add_s(ctx, 0, 0, 2);
                    swc1(ctx, uv + 20, 0);
                    swc1(ctx, uv + 24, 1);
                    swc1(ctx, uv + 28, 0);
                    setreg(ctx, GPR_V1, glyph & 15);
                    setreg(ctx, GPR_A0, 0);
                    for (u32 i = 0;; ++i) {
                        charge(ctx, 3);
                        setreg(ctx, GPR_V0, i < 4 ? 1 : 0);
                        if (i >= 4) break;
                        backedge(ctx);
                        charge(ctx, 11);
                        const u32 v = verts + i * kVtxSize;
                        setreg(ctx, GPR_V1, uv + 8 * i);
                        setreg(ctx, GPR_V0, v);
                        sw(ctx, v + kVtxU, lw(ctx, uv + 8 * i));
                        setf(ctx, 0, lw(ctx, uv + 8 * i + 4));
                        swc1(ctx, v + kVtxV, 0);
                        setreg(ctx, GPR_A0, i + 1);
                    }
                    charge(ctx, 6);
                    setreg(ctx, GPR_A0, rwPRIMTYPETRISTRIP);
                    setreg(ctx, GPR_A1, verts);
                    setreg(ctx, GPR_A2, 4);
                    call_pfn(ctx, 0x1057ACu, kPfnIm2DRenderPrimitive);
                }
                charge(ctx, 1);
            }
            charge(ctx, 1);
        }
    }
    charge(ctx, 10);
}

// 0x104710 [dbgPrintDrawStrings] the debug string list at *(gp-20008): per node {+0 next, +4 x, +8 y, +12 depth,
// +16 char[256], +272 z offset, +276 rgba bytes} each character (signed; up to the NUL) as an 11 x 11 quad of the
// debug font at (x + 12 col, y). Depth 0 draws at near screen z - z offset; otherwise the z sub_105210(depth)
// returns. The atlas cell of a character uses C's signed % 16 and / 16 (bytes >= 0x80 give negative glyphs).
void dbgPrintDrawStrings(EEContext& ctx) {
    guest::enter(ctx, 30);
    Frame f(ctx, 352);
    f.sd(GPR_RA, 48);
    f.sq(GPR_S1, 32);
    f.sq(GPR_S0, 16);
    f.swc1(21, 4);
    f.swc1(20, 0);
    recip_near_plane(ctx, static_cast<u32>(main_camera(ctx, 0x104728u)), 21);
    main_camera(ctx, 0x10474Cu);  // three more getter calls, results unused
    main_camera(ctx, 0x104754u);
    main_camera(ctx, 0x10475Cu);
    u32 node = lwr(ctx, GPR_S1, gpvar(ctx, -20008));
    jal(ctx, 0x104768u, gen::fn_sub_196770_00196770);  // save the render states
    setreg(ctx, GPR_A0, rwRENDERSTATETEXTURERASTER);
    setreg(ctx, GPR_A1, lw(ctx, gpvar(ctx, -20000)));
    call_pfn(ctx, 0x104780u, kPfnRenderStateSet);
    const u32 verts = f.at(64), uv = f.at(320);
    constexpr u32 k12 = 0x41400000u, k11 = 0x41300000u, kCell = 0x3D800000u, kInset = 0x3D400000u;
    for (;;) {
        charge(ctx, 2);
        if (node == 0) break;
        charge(ctx, 10);
        main_camera(ctx, 0x104790u);
        main_camera(ctx, 0x104798u);
        lwc1(ctx, 12, node + 12);
        setf(ctx, 0, 0);
        fpu::c_eq_s(ctx, 0, 12);
        if (!fpu::condition(ctx)) {
            charge(ctx, 3);
            jal(ctx, 0x1047B8u, gen::fn_sub_105210_00105210);  // the depth's screen z
            setf(ctx, 20, fpr(ctx, 0));
        }
        charge(ctx, 3);
        u32 col = 0;
        for (;; ++col) {
            charge(ctx, 3);
            setreg(ctx, GPR_S0, col);
            setreg(ctx, GPR_V1, col < 256 ? 1 : 0);
            if (col >= 256) break;
            backedge(ctx);
            charge(ctx, 4);
            setreg(ctx, GPR_V1, node + col);
            const s8 ch = guest::load<s8>(ctx, node + col + 16);
            setreg64(ctx, GPR_A0, core::sext8(static_cast<u8>(ch)));
            if (ch == 0) break;
            charge(ctx, 3);
            setreg(ctx, GPR_V1, 32);
            if (ch != 32) {
                charge(ctx, 6);
                lwc1(ctx, 1, node + 12);
                setf(ctx, 0, 0);
                fpu::c_eq_s(ctx, 0, 1);
                const bool flat = fpu::condition(ctx);  // depth 0: the 2-D variant
                charge(ctx, 28);
                setf(ctx, 1, k12);
                setf(ctx, 0, fpu::cvt_s_w(col));
                fpu::mul_s(ctx, 1, 1, 0);
                lwc1(ctx, 0, node + 4);
                fpu::add_s(ctx, 3, 0, 1);  // x + 12 col
                swc1(ctx, verts + 0 * kVtxSize + kVtxX, 3);
                lwc1(ctx, 2, node + 8);
                swc1(ctx, verts + 0 * kVtxSize + kVtxY, 2);
                setf(ctx, 0, k11);
                fpu::add_s(ctx, 1, 0, 3);
                swc1(ctx, verts + 1 * kVtxSize + kVtxX, 1);
                swc1(ctx, verts + 1 * kVtxSize + kVtxY, 2);
                swc1(ctx, verts + 2 * kVtxSize + kVtxX, 3);
                fpu::add_s(ctx, 0, 0, 2);
                swc1(ctx, verts + 2 * kVtxSize + kVtxY, 0);
                swc1(ctx, verts + 3 * kVtxSize + kVtxX, 1);
                swc1(ctx, verts + 3 * kVtxSize + kVtxY, 0);
                const u32 minus32 = static_cast<u32>(static_cast<s32>(ch)) - 32;
                setreg(ctx, GPR_V0, minus32);
                const s32 glyph = static_cast<s8>(static_cast<u8>(minus32));
                setreg64(ctx, GPR_A0, core::sext8(static_cast<u8>(minus32)));
                s32 cell_col = glyph & 0xF;
                if (glyph < 0) {
                    charge(ctx, 2);
                    if (cell_col != 0) {
                        charge(ctx, 1);
                        cell_col -= 16;
                    }
                }
                setreg(ctx, GPR_V1, static_cast<u32>(cell_col));
                charge(ctx, 10);
                setf(ctx, 1, kCell);
                setf(ctx, 0, fpu::cvt_s_w(static_cast<u32>(cell_col)));
                fpu::mul_s(ctx, 3, 1, 0);  // u0
                swc1(ctx, uv + 0, 3);
                s32 cell_row = glyph >> 4;
                if (glyph < 0) {
                    charge(ctx, 2);
                    setreg(ctx, GPR_V0, static_cast<u32>(glyph + 15));
                    cell_row = (glyph + 15) >> 4;
                }
                setreg(ctx, GPR_V1, static_cast<u32>(cell_row));
                charge(ctx, flat ? 23 : 21);
                setf(ctx, 1, kCell);
                setf(ctx, 0, fpu::cvt_s_w(static_cast<u32>(cell_row)));
                fpu::mul_s(ctx, 2, 1, 0);  // v0
                swc1(ctx, uv + 4, 2);
                setf(ctx, 0, kInset);
                fpu::add_s(ctx, 1, 0, 3);  // u1
                swc1(ctx, uv + 8, 1);
                swc1(ctx, uv + 12, 2);
                swc1(ctx, uv + 16, 3);
                fpu::add_s(ctx, 0, 0, 2);  // v1
                swc1(ctx, uv + 20, 0);
                swc1(ctx, uv + 24, 1);
                swc1(ctx, uv + 28, 0);
                setreg(ctx, GPR_A1, 0);
                if (flat) {
                    setreg(ctx, GPR_V0, 0x960000u);
                    setf(ctx, 1, lw(ctx, kIm2DNearScreenZ));
                } else {
                    setreg(ctx, GPR_V0, kInset);
                }
                for (u32 i = 0;; ++i) {
                    charge(ctx, 3);
                    setreg(ctx, GPR_V0, i < 4 ? 1 : 0);
                    if (i >= 4) break;
                    backedge(ctx);
                    charge(ctx, flat ? 51 : 49);
                    const u32 v = verts + i * kVtxSize;
                    setreg(ctx, GPR_A0, v);
                    if (flat) {
                        setf(ctx, 0, fpu::sub(fpr(ctx, 1), lw(ctx, node + 272)));
                        swc1(ctx, v + kVtxZ, 0);
                    } else {
                        swc1(ctx, v + kVtxZ, 20);
                    }
                    for (u32 k = 0; k < 4; ++k) {
                        setf(ctx, 0, byte_to_float(guest::load<u8>(ctx, node + 276 + k)));
                        swc1(ctx, v + kVtxR + 4 * k, 0);
                    }
                    swc1(ctx, v + kVtxRecipZ, 21);
                    setreg(ctx, GPR_V0, uv + 8 * i);
                    sw(ctx, v + kVtxU, lw(ctx, uv + 8 * i));
                    setf(ctx, 0, lw(ctx, uv + 8 * i + 4));
                    swc1(ctx, v + kVtxV, 0);
                    setreg(ctx, GPR_A1, i + 1);
                }
                charge(ctx, flat ? 9 : 7);
                setreg(ctx, GPR_A0, rwPRIMTYPETRISTRIP);
                setreg(ctx, GPR_A1, verts);
                setreg(ctx, GPR_A2, 4);
                call_pfn(ctx, flat ? 0x104A68u : 0x104CCCu, kPfnIm2DRenderPrimitive);
            }
            charge(ctx, 1);
        }
        charge(ctx, 3);
        node = lwr(ctx, GPR_S1, node);
        backedge(ctx);
    }
    charge(ctx, 8);
}

namespace {
// The degree angle in an s-register wrapped into [-180, 180] one 360 step per pass (the compiled loop: cvt.s.w,
// c.le.s / c.lt.s against $f3 = 180 / $f1 = -180, the step in $f2 = 360, cvt.w.s back, `li $v1, 1` as the "changed"
// value), with its check point per pass.
void wrap_degrees(EEContext& ctx, unsigned sreg) {
    for (bool first = true;; first = false) {
        if (!first) backedge(ctx);
        charge(ctx, 8);
        setreg(ctx, GPR_A0, 0);
        fpu::set_fpr(ctx, 0, static_cast<u32>(reg(ctx, sreg)));
        fpu::cvt_s_w(ctx, 0, 0);
        fpu::c_le_s(ctx, 0, 3);
        const bool le180 = fpu::condition(ctx);
        if (le180) charge(ctx, 1);
        charge(ctx, 3);
        setreg(ctx, GPR_V0, le180 ? 1 : 0);  // after `xori 1`
        bool changed = false;
        if (!le180) {
            charge(ctx, 9);
            fpu::set_fpr(ctx, 0, static_cast<u32>(reg(ctx, sreg)));
            fpu::cvt_s_w(ctx, 0, 0);
            fpu::sub_s(ctx, 0, 0, 2);
            fpu::cvt_w_s(ctx, 0, 0);
            setreg64(ctx, sreg, fpu::mfc1(ctx, 0));
            changed = true;
        } else {
            charge(ctx, 6);
            fpu::set_fpr(ctx, 0, static_cast<u32>(reg(ctx, sreg)));
            fpu::cvt_s_w(ctx, 0, 0);
            fpu::c_lt_s(ctx, 0, 1);
            if (fpu::condition(ctx)) {
                charge(ctx, 4);
                fpu::add_s(ctx, 0, 0, 2);
                fpu::cvt_w_s(ctx, 0, 0);
                setreg64(ctx, sreg, fpu::mfc1(ctx, 0));
                changed = true;
            }
        }
        if (changed) setreg(ctx, GPR_A0, 1);
        charge(ctx, 2);
        if (!changed) break;
    }
}
// `lui $v0, 0x43b4; mtc1 $v0, $f2; li $v1, 1; lui $v0, 0xc334; mtc1 $v0, $f1; lui $v0, 0x4334; mtc1 $v0, $f3`.
void wrap_constants(EEContext& ctx) {
    setf(ctx, 2, 0x43B40000u);  // 360
    setreg(ctx, GPR_V1, 1);
    setf(ctx, 1, 0xC3340000u);  // -180
    setreg(ctx, GPR_V0, 0x43340000u);
    setf(ctx, 3, 0x43340000u);  // 180
}
void lwc1_gp(EEContext& ctx, unsigned f, s32 off) { lwc1(ctx, f, gpvar(ctx, off)); }
// The inlined cosf polynomial in x^2 ($fX), as compiled: Horner steps through ACC (adda $f2 = 0, madd), then
// rd = 1 - (0.5 x^2 - x^2 * p) with the coefficients of the kernel tables at gp-32316.. .
void cos_poly(EEContext& ctx, unsigned x2, unsigned rd) {
    lwc1_gp(ctx, 1, -32316);
    lwc1_gp(ctx, 0, -32312);
    setf(ctx, 2, 0);
    fpu::adda_s(ctx, 2, 0);
    fpu::madd_s(ctx, 1, 1, x2);
    for (s32 off : {-31732, -31728, -32300}) {
        lwc1_gp(ctx, 0, off);
        fpu::adda_s(ctx, 2, 0);
        fpu::madd_s(ctx, 1, x2, 1);
    }
    lwc1_gp(ctx, 0, -31724);
    fpu::adda_s(ctx, 2, 0);
    fpu::madd_s(ctx, 0, x2, 1);
    fpu::mul_s(ctx, 1, x2, 0);
    setreg(ctx, GPR_V0, 0x3F000000u);
    setf(ctx, 0, 0x3F000000u);
    fpu::mula_s(ctx, 0, x2);
    fpu::msub_s(ctx, 1, x2, 1);
    setreg(ctx, GPR_V0, fpu::kOne);
    setf(ctx, 0, fpu::kOne);
    fpu::sub_s(ctx, rd, 0, 1);
}
}  // namespace

// 0x1875F0 [H_MoonIcon_Draw] the HUD moon icon (H_MoonIcon_UpdateTask): a 30 x 44 quad (template (+-15, +-22, 0) on
// the stack) rotated by angle_x degrees about the axis at 0x5E42A8 (RwMatrixRotateOneMinusCosineSine with the
// inlined cos/sin polynomials, RwV3dTransformPoints), its x scaled by cos(angle_y) (the turn), drawn at (585, 406)
// in (14, 139, 236) with the given alpha.
void H_MoonIcon_Draw(EEContext& ctx, u64 angle_x, u64 angle_y, u64 alpha) {
    guest::enter(ctx, 85);
    Frame f(ctx, 448);
    f.sd(GPR_RA, 80);
    f.sq(GPR_S3, 64);
    f.sq(GPR_S2, 48);
    f.sq(GPR_S1, 32);
    f.sq(GPR_S0, 16);
    f.swc1(23, 12);
    f.swc1(22, 8);
    f.swc1(21, 4);
    f.swc1(20, 0);
    setreg64(ctx, GPR_S3, angle_x);
    setreg64(ctx, GPR_S2, angle_y);
    setreg64(ctx, GPR_S1, alpha);
    recip_near_plane(ctx, static_cast<u32>(main_camera(ctx, 0x187624u)), 21);
    setreg(ctx, GPR_S0, kPfnRenderStateSet);
    state_set(ctx, 0x187650u, rwRENDERSTATEZTESTENABLE, 1);
    state_set(ctx, 0x187664u, rwRENDERSTATESHADEMODE, 2);
    state_set(ctx, 0x187678u, rwRENDERSTATEZWRITEENABLE, 1);
    state_set(ctx, 0x18768Cu, rwRENDERSTATETEXTUREFILTER, 2);
    state_set(ctx, 0x1876A0u, rwRENDERSTATEVERTEXALPHAENABLE, 1);
    state_set(ctx, 0x1876B4u, rwRENDERSTATEDESTBLEND, 6);
    state_set(ctx, 0x1876C8u, rwRENDERSTATESRCBLEND, 5);
    state_set(ctx, 0x1876DCu, rwRENDERSTATETEXTUREADDRESS, 4);
    state_set(ctx, 0x1876F0u, rwRENDERSTATEFOGENABLE, 0);
    // The template quad at sp+400 and its working copy at sp+352 (4 x RwV3d).
    const u32 tmpl = f.at(400), pts = f.at(352);
    constexpr u32 kM15 = 0xC1700000u, kM22 = 0xC1B00000u, k15 = 0x41700000u, k22 = 0x41B00000u;
    const u32 t[12] = {kM15, kM22, 0, k15, kM22, 0, kM15, k22, 0, k15, k22, 0};
    for (u32 k = 0; k < 12; ++k) sw(ctx, tmpl + 4 * k, t[k]);
    setreg(ctx, GPR_V0, k22);
    setreg(ctx, GPR_V1, k15);
    setreg(ctx, GPR_A0, 0);
    for (u32 i = 0;; ++i) {
        charge(ctx, 3);
        setreg(ctx, GPR_V0, i < 4 ? 1 : 0);
        if (i >= 4) break;
        backedge(ctx);
        charge(ctx, 13);
        setreg(ctx, GPR_V1, tmpl + 12 * i);
        setreg(ctx, GPR_V0, pts + 12 * i);
        for (u32 k = 0; k < 3; ++k) {
            setf(ctx, 2 - k, lw(ctx, tmpl + 12 * i + 4 * k));
            sw(ctx, pts + 12 * i + 4 * k, fpr(ctx, 2 - k));
        }
        setreg(ctx, GPR_A0, i + 1);
    }
    charge(ctx, 7);
    wrap_constants(ctx);
    wrap_degrees(ctx, GPR_S3);
    // Rotation: x = angle_x * k / 180 (k at gp-32184), cos and sin by the inlined polynomials.
    charge(ctx, 88);
    fpu::set_fpr(ctx, 0, static_cast<u32>(reg(ctx, GPR_S3)));
    fpu::cvt_s_w(ctx, 1, 0);
    lwc1_gp(ctx, 0, -32184);
    fpu::mul_s(ctx, 1, 0, 1);
    setreg(ctx, GPR_V0, 0x43340000u);
    setf(ctx, 0, 0x43340000u);
    fpu::div_s(ctx, 22, 1, 0);
    fpu::mul_s(ctx, 20, 22, 22);
    cos_poly(ctx, 20, 23);
    jal(ctx, 0x1878BCu, gen::fn_sub_4C38C0_004c38c0);  // RwMatrixCreate
    const u64 matrix = reg64(ctx, GPR_V0);
    setreg(ctx, GPR_V1, fpu::kOne);
    setf(ctx, 0, fpu::kOne);
    fpu::sub_s(ctx, 12, 0, 23);  // 1 - cos
    lwc1_gp(ctx, 1, -31788);
    lwc1_gp(ctx, 0, -32696);
    setf(ctx, 2, 0);
    fpu::adda_s(ctx, 2, 0);
    fpu::madd_s(ctx, 1, 1, 20);
    for (s32 off : {-32488, -32688, -32684, -31784}) {
        lwc1_gp(ctx, 0, off);
        fpu::adda_s(ctx, 2, 0);
        fpu::madd_s(ctx, 1, 20, 1);
    }
    fpu::mul_s(ctx, 0, 20, 22);
    fpu::adda_s(ctx, 2, 22);
    fpu::madd_s(ctx, 13, 0, 1);  // sin
    setreg64(ctx, GPR_A0, matrix);
    setreg(ctx, GPR_A1, 0x5E42A8u);  // the rotation axis
    setreg(ctx, GPR_A2, 0);          // rwCOMBINEREPLACE
    jal(ctx, 0x187938u, gen::fn_sub_4C2FC0_004c2fc0);  // RwMatrixRotateOneMinusCosineSine
    setreg64(ctx, GPR_S3, reg64(ctx, GPR_V0));
    setreg(ctx, GPR_A0, pts);
    setreg(ctx, GPR_A1, tmpl);
    setreg(ctx, GPR_A2, 4);
    setreg64(ctx, GPR_A3, reg64(ctx, GPR_S3));
    jal(ctx, 0x187954u, gen::fn_sub_4C6C20_004c6c20);  // RwV3dTransformPoints(pts, tmpl, 4, matrix)
    setreg64(ctx, GPR_A0, reg64(ctx, GPR_S3));
    jal(ctx, 0x187960u, gen::fn_sub_4C3880_004c3880);  // RwMatrixDestroy
    wrap_constants(ctx);
    wrap_degrees(ctx, GPR_S2);
    // The turn: x *= cos(angle_y * k / 180).
    charge(ctx, 41);
    fpu::set_fpr(ctx, 0, static_cast<u32>(reg(ctx, GPR_S2)));
    fpu::cvt_s_w(ctx, 1, 0);
    lwc1_gp(ctx, 0, -32184);
    fpu::mul_s(ctx, 1, 0, 1);
    setreg(ctx, GPR_V0, 0x43340000u);
    setf(ctx, 0, 0x43340000u);
    fpu::div_s(ctx, 0, 1, 0);
    fpu::mul_s(ctx, 3, 0, 0);
    cos_poly(ctx, 3, 1);
    setreg(ctx, GPR_V1, 0);
    for (u32 i = 0;; ++i) {
        charge(ctx, 3);
        setreg(ctx, GPR_V0, i < 4 ? 1 : 0);
        if (i >= 4) break;
        backedge(ctx);
        charge(ctx, 9);
        const u32 p = pts + 12 * i;
        setreg(ctx, GPR_V0, p);
        lwc1(ctx, 0, p);
        fpu::mul_s(ctx, 0, 0, 1);
        swc1(ctx, p, 0);
        setreg(ctx, GPR_V1, i + 1);
    }
    charge(ctx, 17);
    const u32 verts = f.at(96);
    constexpr u32 kR = 0x41600000u, kG = 0x430B0000u, kB = 0x436C0000u;  // (14, 139, 236)
    setreg(ctx, GPR_A3, 0);
    setf(ctx, 4, lw(ctx, kIm2DNearScreenZ));
    setreg(ctx, GPR_A1, kR);
    setreg(ctx, GPR_A0, kG);
    setreg(ctx, GPR_V1, kB);
    setf(ctx, 0, static_cast<u32>(alpha));
    fpu::cvt_s_w(ctx, 3, 0);
    setf(ctx, 0, 585);
    fpu::cvt_s_w(ctx, 2, 0);
    setreg(ctx, GPR_V0, 0x43CB0000u);
    setf(ctx, 1, 0x43CB0000u);  // 406
    for (u32 i = 0;; ++i) {
        charge(ctx, 3);
        setreg(ctx, GPR_V0, i < 4 ? 1 : 0);
        if (i >= 4) break;
        backedge(ctx);
        charge(ctx, 21);
        const u32 v = verts + i * kVtxSize;
        setreg(ctx, GPR_A2, v);
        swc1(ctx, v + kVtxZ, 4);
        swc1(ctx, v + kVtxRecipZ, 21);
        sw(ctx, v + kVtxR, kR);
        sw(ctx, v + kVtxG, kG);
        sw(ctx, v + kVtxB, kB);
        swc1(ctx, v + kVtxA, 3);
        const u32 p = pts + 12 * i;
        setreg(ctx, GPR_V0, p);
        lwc1(ctx, 0, p);
        fpu::add_s(ctx, 0, 2, 0);  // 585 + x
        swc1(ctx, v + kVtxX, 0);
        lwc1(ctx, 0, p + 4);
        fpu::add_s(ctx, 0, 1, 0);  // 406 + y
        swc1(ctx, v + kVtxY, 0);
        setreg(ctx, GPR_A3, i + 1);
    }
    charge(ctx, 24);
    state_set(ctx, 0x187B8Cu, rwRENDERSTATETEXTURERASTER, 0);
    setreg(ctx, GPR_A0, rwPRIMTYPETRISTRIP);
    setreg(ctx, GPR_A1, verts);
    setreg(ctx, GPR_A2, 4);
    call_pfn(ctx, 0x187BA8u, kPfnIm2DRenderPrimitive);
}

}  // namespace p3fes::game

// =====================================================================================================================
// Entry points of the recompiled program
// =====================================================================================================================
namespace p3fes::recomp_gen {
using namespace p3fes::game;
void fn_kwlnRootUpdate2DDrawEndTask_00198b20(p3fes::EEContext& ctx) { kwlnRootUpdate2DDrawEndTask(ctx); }
void fn_kwlnRootUpdate3DOn2DZClearTask_00198c10(p3fes::EEContext& ctx) { kwlnRootUpdate3DOn2DZClearTask(ctx); }
void fn_kwlnRootUpdate3DOn2DDrawBeginTask_00198c60(p3fes::EEContext& ctx) { kwlnRootUpdate3DOn2DDrawBeginTask(ctx); }
void fn_kwlnRootUpdate3DOn2DDrawEndTask_00198d20(p3fes::EEContext& ctx) { kwlnRootUpdate3DOn2DDrawEndTask(ctx); }
void fn_kwlnRootUpdateEtcDrawBeginTask_00198e90(p3fes::EEContext& ctx) { kwlnRootUpdateEtcDrawBeginTask(ctx); }
void fn_kwlnRootUpdateDrawEndTask_00198fd0(p3fes::EEContext& ctx) { kwlnRootUpdateDrawEndTask(ctx); }
void fn_K_SPipe_Update3DDrwBeginTask_00199520(p3fes::EEContext& ctx) { K_SPipe_Update3DDrwBeginTask(ctx); }
void fn_K_SPipe_Update3DDrwEndTask_001995f0(p3fes::EEContext& ctx) { K_SPipe_Update3DDrwEndTask(ctx); }
void fn_kwlnRootUpdateShadowNodeCameraTask_00199740(p3fes::EEContext& ctx) { kwlnRootUpdateShadowNodeCameraTask(ctx); }
void fn_btlDrawMessagePass_0027b310(p3fes::EEContext& ctx) { btlDrawMessagePass(ctx); }
void fn_btlUpdateDraw3DTask_0027ccf0(p3fes::EEContext& ctx) { btlUpdateDraw3DTask(ctx); }
void fn_H_Fade_DrawBlue_001075b0(p3fes::EEContext& ctx) { H_Fade_DrawBlue(ctx); }
void fn_H_Fade_DrawWhite_001078a0(p3fes::EEContext& ctx) { H_Fade_DrawWhite(ctx); }
void fn_H_Fade_DrawColour_001081e0(p3fes::EEContext& ctx) { H_Fade_DrawColour(ctx); }
void fn_sub_269F50_00269f50(p3fes::EEContext& ctx) { sub_269F50(ctx); }
void fn_dbgPrintDrawScreen_00104420(p3fes::EEContext& ctx) { dbgPrintDrawScreen(ctx); }
void fn_dbgPrintDrawStrings_00104710(p3fes::EEContext& ctx) { dbgPrintDrawStrings(ctx); }
void fn_H_MoonIcon_Draw_001875f0(p3fes::EEContext& ctx) {
    H_MoonIcon_Draw(ctx, ee::core::gpr64(ctx, GPR_A0), ee::core::gpr64(ctx, GPR_A1), ee::core::gpr64(ctx, GPR_A2));
}
void fn_dbgPrintDrawWindow_001053f0(p3fes::EEContext& ctx) { dbgPrintDrawWindow(ctx); }
}  // namespace p3fes::recomp_gen
