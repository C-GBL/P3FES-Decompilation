// The game-side draw layer, second pass (render_game2.h has the groups and the data each function works on;
// docs/ANALYSIS/22_rendering.md sections 1, 2, 6 and 7.3). Phase 5: these replace the recompiled bodies listed in
// game/replaced.txt under "render_game2"; tests/game/test_render_game2.cpp runs each against its __recomp body.
//
// Cycle model (ADR-0013): every charge() below is one `ctx.cycles += N` block of the recompiled body in
// recomp/generated, charged at the start of the block -- a block that contains `jal`s is charged in full before the
// first call (the recompiler keeps calls inside their block), so every callee reaches its check point at the same
// virtual time; backedge() sits where that body has a check point on a backward jump.
//
// Registers: register-faithful (render_game2.h). Each body runs on the Cpu view of the guest context: one variable
// per GPR (64-bit writes keep bits 64..127, as the EE does; lq / MMI results write all 128), the FPU and HI/LO
// operations through the runtime's own instruction semantics, prologue spills and epilogue reloads on the guest
// stack. A branch's delay-slot instruction is written once before the `if` when it executes on both paths.
#include "p3fes/game/render_game2.h"

namespace p3fes::recomp_gen {
void fn__rwDMAOpenVIFPkt_004d59d0(p3fes::EEContext&);  // the DMA packet layer: open / extend a VIF packet (DMAC: kept recompiled)
void fn_RpSkyRenderStateSet_004d7f60(p3fes::EEContext&);  // the sky render-state funnel (render_sky)
void fn_sub_4D81B0_004d81b0(p3fes::EEContext&);  // RpSkyRenderStateGet (render_rw)
void fn_RwCameraClear_004c9e90(p3fes::EEContext&);  // (render_core3)
void fn_RwCameraBeginUpdate_004c9d10(p3fes::EEContext&);  // (render_core3)
void fn_RwCameraEndUpdate_004c9d00(p3fes::EEContext&);  // (render_core3)
void fn_sub_198590_00198590(p3fes::EEContext&);  // kwlnRootGetCamera: *(gp-19504)
void fn_sub_1985A0_001985a0(p3fes::EEContext&);  // kwlnRootGetClearColour: gp-19400
void fn_kwlnSetFlags_00198610(p3fes::EEContext&);  // kwlnSetFlags(mask, on) (kwln_task)
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);  // K_Assert(file, line): `jr $ra` in retail
void fn_sub_1120C0_001120c0(p3fes::EEContext&);  // the sprite file manager's per-frame update
void fn_sprSpriteDrawAll_001125d0(p3fes::EEContext&);  // every queued sprite
void fn_sub_348340_00348340(p3fes::EEContext&);  // screen quad vertices (returns 0 = nothing to draw)
void fn_sub_348760_00348760(p3fes::EEContext&);  // screen quad vertices
void fn_sub_348950_00348950(p3fes::EEContext&);  // screen quad vertices
void fn_sub_348BD0_00348bd0(p3fes::EEContext&);  // screen quad vertices
void fn_sub_359380_00359380(p3fes::EEContext&);  // the frame axes (left recompiled: battle_camera_6 stands it in)
void fn_sub_359B40_00359b40(p3fes::EEContext&);  // a debug cylinder / circle (Im3D lines)
void fn_sub_318B60_00318b60(p3fes::EEContext&);  // a model's root frame LTM
void fn_dds3GetProcessWorkData_0035ae10(p3fes::EEContext&);  // (script_vm2)
void fn_dbgDrawRect_00395570(p3fes::EEContext&);  // (render_game)
void fn_sub_395810_00395810(p3fes::EEContext&);
void fn_sub_386E50_00386e50(p3fes::EEContext&);
void fn_sub_395950_00395950(p3fes::EEContext&);
void fn_atomicGetWorldBoundingSphere_004912b0(p3fes::EEContext&);  // [RpAtomicGetWorldBoundingSphere]
void fn_sub_4C9DF0_004c9df0(p3fes::EEContext&);  // [RwCameraFrustumTestSphere] (render_rw)
void fn_sub_4932C0_004932c0(p3fes::EEContext&);  // [RpGeometryForAllMaterials]
void fn_sub_4CB7F0_004cb7f0(p3fes::EEContext&);  // [RwFrameTransform] (render_core3)
void fn_sub_1A7910_001a7910(p3fes::EEContext&);  // a node's colour block onto its atomic's materials
void fn_sub_1A8920_001a8920(p3fes::EEContext&);  // the sorted translucent queue: append a node
void fn_sub_1A88E0_001a88e0(p3fes::EEContext&);  // a whole clump through its atomics' callbacks
void fn_sub_3164C0_003164c0(p3fes::EEContext&);  // the model's fade colour onto its clump
void fn_qsort_005225f8(p3fes::EEContext&);  // libc qsort
void fn_sub_4F1ED0_004f1ed0(p3fes::EEContext&);  // [RwIm3DTransform] (render_core3)
void fn_sub_4F22B0_004f22b0(p3fes::EEContext&);  // [RwIm3DRenderLine]
void fn_sub_4C6BE0_004c6be0(p3fes::EEContext&);  // [RwV3dTransformPoints] (render_core3)
void fn_sub_4C31B0_004c31b0(p3fes::EEContext&);  // [RwMatrixRotate]
void fn_cosf_0052e6d8(p3fes::EEContext&);  // libm
void fn_sinf_0052e878(p3fes::EEContext&);  // libm
void fn_sub_198540_00198540(p3fes::EEContext&);  // the field world (gp-19492 -> world)
void fn_sub_198560_00198560(p3fes::EEContext&);  // kwlnRoot ambient light
void fn_sub_198570_00198570(p3fes::EEContext&);  // kwlnRoot directional light
void fn_sub_198580_00198580(p3fes::EEContext&);  // kwlnRoot second light
void fn_sub_19FD40_0019fd40(p3fes::EEContext&);  // the field ambient colour (field_lo)
void fn_sub_19FD70_0019fd70(p3fes::EEContext&);  // the field directional colour (field_lo)
void fn_sub_19FDA0_0019fda0(p3fes::EEContext&);  // the field directional matrix (field_lo)
void fn_sub_4944B0_004944b0(p3fes::EEContext&);  // [RpLightSetColor]
void fn_sub_49C480_0049c480(p3fes::EEContext&);  // [RpWorldAddLight]
void fn_sub_49C3D0_0049c3d0(p3fes::EEContext&);  // [RpWorldRemoveLight]
void fn_sub_3B5D50_003b5d50(p3fes::EEContext&);  // the field resource list of a kind
void fn_sub_1A7660_001a7660(p3fes::EEContext&);  // a model lists predicate (opaque)
void fn_sub_1A76E0_001a76e0(p3fes::EEContext&);  // a model lists predicate (translucent)
void fn_sub_317A20_00317a20(p3fes::EEContext&);  // the model draw
void fn_sub_319230_00319230(p3fes::EEContext&);
void fn_sub_34FD30_0034fd30(p3fes::EEContext&);
void fn_sub_34FD70_0034fd70(p3fes::EEContext&);
void fn_K_FldSrc_DrawFieldTrans_001b4720(p3fes::EEContext&);  // the translucent field pass
void fn_clndGetCurrentMonth_0017d920(p3fes::EEContext&);  // (menu_ui)
void fn_clndGetCurrentDay_0017da40(p3fes::EEContext&);  // (menu_ui)
void fn_datGetTime_0016ef30(p3fes::EEContext&);  // (menu_ui)
void fn_sprAddFile_00112370(p3fes::EEContext&);
void fn_sprFileIsReady_00111f30(p3fes::EEContext&);  // (ui2)
void fn_sub_187EC0_00187ec0(p3fes::EEContext&);  // the calendar draw
void fn_sub_1A4600_001a4600(p3fes::EEContext&);  // the camera far plane ($f0)
void fn_sub_1A4580_001a4580(p3fes::EEContext&);  // set the camera far plane ($f12)
void fn_sub_20AC90_0020ac90(p3fes::EEContext&);
void fn_sub_20B250_0020b250(p3fes::EEContext&);  // a model through Im3D
void fn_sub_41BF80_0041bf80(p3fes::EEContext&);  // a line object
void fn_sub_317730_00317730(p3fes::EEContext&);  // the model pre-update
void fn_sub_313CA0_00313ca0(p3fes::EEContext&);  // the material animation
void fn_sub_4916D0_004916d0(p3fes::EEContext&);  // [RpClumpForAllAtomics]
void fn_sub_31DD40_0031dd40(p3fes::EEContext&);  // a shadow / effect colour
void fn_sub_31DC80_0031dc80(p3fes::EEContext&);  // a shadow / effect draw by kind
void fn_sub_31E240_0031e240(p3fes::EEContext&);
void fn_sub_31E1E0_0031e1e0(p3fes::EEContext&);
void fn_sub_319770_00319770(p3fes::EEContext&);  // is child slot i visible
void fn_sub_318AD0_00318ad0(p3fes::EEContext&);  // set a model colour
void fn_sub_3151D0_003151d0(p3fes::EEContext&);  // the outline
void fn_sub_320640_00320640(p3fes::EEContext&);
void fn_sub_321FE0_00321fe0(p3fes::EEContext&);
void fn_sub_49C1B0_0049c1b0(p3fes::EEContext&);  // [RpWorldRemoveCamera]
void fn_sub_49C160_0049c160(p3fes::EEContext&);  // [RpWorldAddCamera]
void fn_RpWorldRender_0049a250(p3fes::EEContext&);
void fn_sub_3B54C0_003b54c0(p3fes::EEContext&);  // the field resource of a model id
void fn_memset_00521408(p3fes::EEContext&);  // libc
void fn_sub_318B00_00318b00(p3fes::EEContext&);  // a model's colour block
void fn_sub_318ED0_00318ed0(p3fes::EEContext&);  // a model's effect anchor (0 = none)
void fn_sub_34FDF0_0034fdf0(p3fes::EEContext&);  // place an effect
void fn_sub_3B0F50_003b0f50(p3fes::EEContext&);  // a glyph's animation offset
void fn_frFontRasterDrawGlyph_003b38f0(p3fes::EEContext&);  // (render_game)
void fn_sub_10A500_0010a500(p3fes::EEContext&);  // a pad trigger test
void fn_sub_21C3F0_0021c3f0(p3fes::EEContext&);  // the battle-panel sprite page
void fn_sub_21CCA0_0021cca0(p3fes::EEContext&);  // a sprite of a page
void fn_sub_21CCE0_0021cce0(p3fes::EEContext&);  // a sprite's raster
void fn_sub_20E590_0020e590(p3fes::EEContext&);
void fn_sub_20E610_0020e610(p3fes::EEContext&);
void fn_sub_252340_00252340(p3fes::EEContext&);
void fn_sub_40D610_0040d610(p3fes::EEContext&);
void fn_sub_40E420_0040e420(p3fes::EEContext&);
void fn_sub_4E3630_004e3630(p3fes::EEContext&);  // the frame-buffer raster
void fn_sub_4D1840_004d1840(p3fes::EEContext&);  // [_rwObjectHasFrameSetFrame]
void fn_sub_4CAF80_004caf80(p3fes::EEContext&);  // [RwFrameDestroy]
void fn_sub_4CDE90_004cde90(p3fes::EEContext&);  // [RwRasterDestroy]
void fn_sub_4CA030_004ca030(p3fes::EEContext&);  // [RwCameraDestroy]
void fn_sub_4F1780_004f1780(p3fes::EEContext&);  // the texture cache: (un)cache a raster
void fn_sub_4CA090_004ca090(p3fes::EEContext&);  // [RwCameraCreate]
void fn_sub_4CAF10_004caf10(p3fes::EEContext&);  // [RwFrameCreate]
void fn_sub_4CE0F0_004ce0f0(p3fes::EEContext&);  // [RwRasterCreate]
void fn_sub_4C9F00_004c9f00(p3fes::EEContext&);
void fn_sub_4C2F30_004c2f30(p3fes::EEContext&);  // [RwMatrixMultiply] (render_rw)
void fn_sub_4F2150_004f2150(p3fes::EEContext&);  // [RwIm3DRenderPrimitive] (render_core3)
void fn_sub_4F1F80_004f1f80(p3fes::EEContext&);  // [RwIm3DEnd] (render_rw)
void fn_sub_4C38C0_004c38c0(p3fes::EEContext&);  // [RwMatrixCreate]
void fn_sub_4C3880_004c3880(p3fes::EEContext&);  // [RwMatrixDestroy]
void fn_sub_4F1FD0_004f1fd0(p3fes::EEContext&);  // [RwIm3DRenderIndexedPrimitive] (render_core3)
// This file's own entry points, called the way the original called them (jal).
void fn_sub_358460_00358460(p3fes::EEContext&);
void fn_sub_351940_00351940(p3fes::EEContext&);
void fn_sub_351290_00351290(p3fes::EEContext&);
void fn_sub_351510_00351510(p3fes::EEContext&);
void fn_sub_315C20_00315c20(p3fes::EEContext&);
void fn_sub_19DE80_0019de80(p3fes::EEContext&);
void fn_sub_19DB10_0019db10(p3fes::EEContext&);
void fn_sub_1A8B10_001a8b10(p3fes::EEContext&);
void fn_sub_359110_00359110(p3fes::EEContext&);
void fn_sub_359560_00359560(p3fes::EEContext&);
void fn_sub_1A7B50_001a7b50(p3fes::EEContext&);
void fn_sub_1A7FC0_001a7fc0(p3fes::EEContext&);
void fn_sub_1A8140_001a8140(p3fes::EEContext&);
void fn_sub_3294D0_003294d0(p3fes::EEContext&);
void fn_sub_329550_00329550(p3fes::EEContext&);
void fn_sub_3295C0_003295c0(p3fes::EEContext&);
void fn_sub_329630_00329630(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace rg2 {

namespace gen = ::p3fes::recomp_gen;

constexpr u32 kQuadIndices = 0x69CB80u;    // u16[6] {0, 1, 2, ...}: the two triangles of a 4-vertex screen quad
constexpr u32 kScreenRaster = 0x957BA8u;   // the raster the screen effects sample (the captured frame)
constexpr u32 kStrKwlnRootC = 0x6787D8u;   // "kwlnRoot.c"
constexpr s32 kGpSprWritePtr = -17148;     // RW's scratchpad packet write pointer (22_rendering.md section 5.1)
constexpr s32 kGpFrame1Shadow = -17080;    // RW's FRAME_1 shadow (64-bit GS register value)
constexpr s32 kGpClamp1Shadow = -17048;    // RW's CLAMP_1 shadow
constexpr u32 kGsFrame1 = 0x4C, kGsClamp1 = 0x08;  // GS register numbers in the A+D data
constexpr u32 rwPRIMTYPETRILIST = 3;

// =========================================================================================================
// [mask] the game's own VIF packets
// =========================================================================================================

// The packet head the four share: _rwDMAOpenVIFPkt(0x80000000, 2 qw) (jal at pc), then the GIF tag
// {NLOOP 1 | EOP, NREG 1; REGS = A+D (0xE)} built in $v1 and stored at the scratchpad write pointer, read into `out`.
void Cpu::vif_ad_head(u32 pc) {
    a0 = lui(0x8000);
    a1 = 2;
    jal(pc, gen::fn__rwDMAOpenVIFPkt_004d59d0);
    a1 = 14;
    v1 = lui(0x1000);
    a0 = dsll32(v1, 0);
    v1 = 0x8001;
    v1 = v1 | a0;
    pcpyld(v1, a1, v1);
}

// sub_3294D0: FRAME_1 = RW's FRAME_1 shadow with FBMSK = 0x00FFFFFF (colour writes masked: the following draws
// only write alpha).
void Cpu::sub_3294D0() {
    enter(29);
    sp = addiu(sp, -16);
    sd(sp, ra);
    vif_ad_head(0x3294E0u);
    lw(a2, gp + kGpSprWritePtr);
    sq(a2, v1);
    a1 = kGsFrame1;
    ld(a0, gp + kGpFrame1Shadow);
    v1 = lui(0xFF);
    v1 = v1 | 0xFFFF;
    v1 = dsll32(v1, 0);
    v1 = a0 | v1;
    pcpyld(v1, a1, v1);
    sq(a2 + 16, v1);
    lw(v1, gp + kGpSprWritePtr);
    v1 = addiu(v1, 32);
    sw(gp + kGpSprWritePtr, v1);
    ld(ra, sp);
    sp = addiu(sp, 16);
}

// sub_329550: FRAME_1 = RW's shadow again (the mask off).
void Cpu::sub_329550() {
    enter(25);
    sp = addiu(sp, -16);
    sd(sp, ra);
    vif_ad_head(0x329560u);
    lw(a1, gp + kGpSprWritePtr);
    sq(a1, v1);
    a0 = kGsFrame1;
    ld(v1, gp + kGpFrame1Shadow);
    pcpyld(v1, a0, v1);
    sq(a1 + 16, v1);
    lw(v1, gp + kGpSprWritePtr);
    v1 = addiu(v1, 32);
    sw(gp + kGpSprWritePtr, v1);
    ld(ra, sp);
    sp = addiu(sp, 16);
}

// sub_3295C0: CLAMP_1 = the 64-bit $a0 (the callers pass REGION_CLAMP over the 640 x 448 screen).
void Cpu::sub_3295C0() {
    enter(27);
    sp = addiu(sp, -32);
    sd(sp + 16, ra);
    sq(sp, s0);
    s0 = a0;
    vif_ad_head(0x3295D8u);
    lw(a0, gp + kGpSprWritePtr);
    sq(a0, v1);
    v1 = kGsClamp1;
    pcpyld(v1, v1, s0);
    sq(a0 + 16, v1);
    lw(v1, gp + kGpSprWritePtr);
    v1 = addiu(v1, 32);
    sw(gp + kGpSprWritePtr, v1);
    ld(ra, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 32);
}

// sub_329630: CLAMP_1 = RW's shadow again.
void Cpu::sub_329630() {
    enter(25);
    sp = addiu(sp, -16);
    sd(sp, ra);
    vif_ad_head(0x329640u);
    lw(a1, gp + kGpSprWritePtr);
    sq(a1, v1);
    a0 = kGsClamp1;
    ld(v1, gp + kGpClamp1Shadow);
    pcpyld(v1, a0, v1);
    sq(a1 + 16, v1);
    lw(v1, gp + kGpSprWritePtr);
    v1 = addiu(v1, 32);
    sw(gp + kGpSprWritePtr, v1);
    ld(ra, sp);
    sp = addiu(sp, 16);
}

// =========================================================================================================
// [screen] the full-screen effect callbacks of the 0x348000 band
// =========================================================================================================

// RwRenderStateSet(TEXTURERASTER, $a1) through the device pointer (jalr at pc_raster), then
// RpSkyRenderStateSet(3, 0x31001) (jal at pc_state).
void Cpu::im2d_state_raster(u32 pc_raster, u32 pc_state) {
    call_pfn(pc_raster, kPfnRenderStateSet);
    a0 = 3;
    v0 = lui(0x3);
    a1 = v0 | 0x1001;
    jal(pc_state, gen::fn_RpSkyRenderStateSet_004d7f60);
}

// RwIm2DRenderIndexedPrimitive(TRILIST, sp + verts, 4, the quad indices, 6) through the device pointer.
void Cpu::im2d_indexed_quad(u32 pc, s32 verts) {
    a0 = rwPRIMTYPETRILIST;
    a1 = addiu(sp, verts);
    a2 = 4;
    a3 = addiu(lui(0x6A), -13440);  // kQuadIndices
    t0 = 6;
    call_pfn(pc, kPfnIm2DRenderIndexedPrimitive);
}

// sub_3295C0(CLAMP_1 = REGION_CLAMP, u 0..639, v 0..447): `(1788 << 32) | 0x9FC00A` built in $v0 / $v1 / $a0.
void Cpu::clamp_to_screen(u32 pc) {
    v0 = 1788;
    v1 = dsll32(v0, 0);
    v0 = lui(0x9F);
    v0 = v0 | 0xC00A;
    a0 = v0 | v1;
    jal(pc, gen::fn_sub_3295C0_003295c0);
}

// sub_34ADA0: when the effect's params (+36) have byte +195 > 0, a 4-vertex quad from sub_348BD0(params + 192)
// drawn untextured.
void Cpu::sub_34ADA0() {
    enter(7);
    sp = addiu(sp, -272);
    sd(sp, ra);
    lw(v1, a0 + 36);
    a0 = addiu(v1, 192);
    lbu(v1, v1 + 195);
    if (sgn(v1) > 0) {
        charge(24);
        a1 = addiu(sp, 16);
        jal(0x34ADC0u, gen::fn_sub_348BD0_00348bd0);
        a0 = 1;
        a1 = 0;
        im2d_state_raster(0x34ADD8u, 0x34ADECu);
        im2d_indexed_quad(0x34AE14u, 16);
    }
    charge(4);
    ld(ra, sp);
    sp = addiu(sp, 272);
}

// sub_34A800: the same quad from sub_348950, textured with the captured screen raster and clamped to the screen.
void Cpu::sub_34A800() {
    enter(7);
    sp = addiu(sp, -272);
    sd(sp, ra);
    lw(v1, a0 + 36);
    a0 = addiu(v1, 192);
    lbu(v1, v1 + 195);
    if (sgn(v1) > 0) {
        charge(34);
        a1 = addiu(sp, 16);
        jal(0x34A820u, gen::fn_sub_348950_00348950);
        a0 = 1;
        lw(a1, kScreenRaster);
        im2d_state_raster(0x34A83Cu, 0x34A850u);
        clamp_to_screen(0x34A86Cu);
        im2d_indexed_quad(0x34A894u, 16);
        jal(0x34A89Cu, gen::fn_sub_329630_00329630);
    }
    charge(4);
    ld(ra, sp);
    sp = addiu(sp, 272);
}

// sub_349A30: as sub_34A800 with the vertices of sub_348340, which returns 0 when there is nothing to draw.
void Cpu::sub_349A30() {
    enter(7);
    sp = addiu(sp, -272);
    sd(sp, ra);
    lw(v1, a0 + 36);
    a0 = addiu(v1, 192);
    lbu(v1, v1 + 195);
    if (sgn(v1) > 0) {
        charge(5);
        a1 = addiu(sp, 16);
        jal(0x349A50u, gen::fn_sub_348340_00348340);
        if (v0 != 0) {
            charge(31);
            a0 = 1;
            lw(a1, kScreenRaster);
            im2d_state_raster(0x349A74u, 0x349A88u);
            clamp_to_screen(0x349AA4u);
            im2d_indexed_quad(0x349ACCu, 16);
            jal(0x349AD4u, gen::fn_sub_329630_00329630);
        }
    }
    charge(4);
    ld(ra, sp);
    sp = addiu(sp, 272);
}

// The two-layer screen pass shared (instruction for instruction, 0xFA4 bytes apart) by sub_348DA0 and sub_349D30,
// from the render-state save to the restore. $s2 = the params block, $s0 = the address of the first layer's raster;
// `base` = the pc of the first call. Layer 1: the first raster, colour writes masked (sub_3294D0) and alpha test
// state 2 = 68, the quad of sub_348760(params + 4); layer 2 (when sub_348340(params + 4) has a quad): the captured
// screen raster, clamped, alpha test state 2 = saved | 0x10. State 2 is restored at the end.
void Cpu::layer_pass(u32 base, u32 tail_cost) {
    a0 = 2;
    a1 = addiu(sp, 588);
    jal(base, gen::fn_sub_4D81B0_004d81b0);  // RpSkyRenderStateGet(2, &saved)
    s1 = addiu(lui(0x96), 144);              // &RwRenderStateSet
    a0 = 1;
    lw(a1, s0);
    lw(v0, s1);
    jalr(base + 0x1C, v0.u());  // RwRenderStateSet(TEXTURERASTER, *raster_ref)
    jal(base + 0x24, gen::fn_sub_3294D0_003294d0);
    a0 = 2;
    a1 = 68;
    jal(base + 0x34, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 3;
    v0 = lui(0x3);
    a1 = v0 | 0x1001;
    jal(base + 0x48, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = addiu(s2, 4);
    a1 = addiu(sp, 320);
    jal(base + 0x58, gen::fn_sub_348760_00348760);
    s0 = addiu(lui(0x96), 164);  // &RwIm2DRenderIndexedPrimitive
    a0 = rwPRIMTYPETRILIST;
    a1 = addiu(sp, 320);
    a2 = 4;
    a3 = addiu(lui(0x6A), -13440);
    t0 = 6;
    lw(v0, s0);
    jalr(base + 0x84, v0.u());
    jal(base + 0x8C, gen::fn_sub_329550_00329550);
    lw(v0, sp + 588);
    a1 = v0 | 0x10;
    a0 = 2;
    jal(base + 0xA0, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = addiu(s2, 4);
    a1 = addiu(sp, 64);
    jal(base + 0xB0, gen::fn_sub_348340_00348340);
    if (v0 != 0) {
        charge(29);
        a0 = 1;
        lw(a1, kScreenRaster);
        lw(v0, s1);
        jalr(base + 0xD0, v0.u());
        a0 = 3;
        v0 = lui(0x3);
        a1 = v0 | 0x1001;
        jal(base + 0xE4, gen::fn_RpSkyRenderStateSet_004d7f60);
        clamp_to_screen(base + 0x100);
        a0 = rwPRIMTYPETRILIST;
        a1 = addiu(sp, 64);
        a2 = 4;
        a3 = addiu(lui(0x6A), -13440);
        t0 = 6;
        lw(v0, s0);
        jalr(base + 0x124, v0.u());
        jal(base + 0x12C, gen::fn_sub_329630_00329630);
    }
    charge(tail_cost);
    a0 = 2;
    lw(a1, sp + 588);
    jal(base + 0x13C, gen::fn_RpSkyRenderStateSet_004d7f60);
}

// sub_348DA0(params, raster_ref): the two-layer pass on the caller's params ($a0) and first raster (*$a1).
void Cpu::sub_348DA0() {
    enter(57);
    sp = addiu(sp, -592);
    sd(sp + 48, ra);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    s2 = a0;
    s0 = a1;
    layer_pass(0x348DC4u, 11);
    ld(ra, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 592);
}

// sub_349D30(obj): the two-layer pass when params byte +199 > 0; params = obj +36 (+192), raster ref = obj+40 -> +8.
void Cpu::sub_349D30() {
    enter(10);
    sp = addiu(sp, -592);
    sd(sp + 48, ra);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    lw(v1, a0 + 36);
    s2 = addiu(v1, 192);
    lbu(v1, v1 + 199);
    if (sgn(v1) > 0) {
        charge(52);
        lw(v0, a0 + 40);
        lw(s0, v0 + 8);
        layer_pass(0x349D68u, 4);
    }
    charge(7);
    ld(ra, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 592);
}

// sub_34B010(obj): when params byte +207 > 0: layer 1 = the obj's raster (obj+40 -> +8), colour writes masked,
// alpha test 68, the quad of sub_348BD0(params + 12) with its UVs reset to the unit square; layer 2 = the same quad
// untextured with alpha test saved | 0x10; state 2 restored.
void Cpu::sub_34B010() {
    enter(10);
    sp = addiu(sp, -592);
    sd(sp + 48, ra);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    lw(v1, a0 + 36);
    s2 = addiu(v1, 192);
    lbu(v1, v1 + 207);
    if (sgn(v1) > 0) {
        charge(82);
        lw(v0, a0 + 40);
        lw(s0, v0 + 8);
        a0 = 2;
        a1 = addiu(sp, 588);
        jal(0x34B048u, gen::fn_sub_4D81B0_004d81b0);
        s1 = addiu(lui(0x96), 144);
        a0 = 1;
        lw(a1, s0);
        lw(v0, s1);
        jalr(0x34B064u, v0.u());
        jal(0x34B06Cu, gen::fn_sub_3294D0_003294d0);
        a0 = 2;
        a1 = 68;
        jal(0x34B07Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 3;
        v0 = lui(0x3);
        a1 = v0 | 0x1001;
        jal(0x34B090u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = addiu(s2, 12);
        a1 = addiu(sp, 320);
        jal(0x34B0A0u, gen::fn_sub_348BD0_00348bd0);
        // u, v of the four vertices (64 bytes apart from sp + 320; u at +16): (0,0) (0,1) (1,1) (1,0)
        sw(sp + 336, zero);
        sw(sp + 340, zero);
        sw(sp + 400, zero);
        v0 = lui(0x3F80);
        sw(sp + 404, v0);
        sw(sp + 464, v0);
        sw(sp + 468, v0);
        sw(sp + 528, v0);
        sw(sp + 532, zero);
        s0 = addiu(lui(0x96), 164);
        a0 = rwPRIMTYPETRILIST;
        a1 = addiu(sp, 320);
        a2 = 4;
        a3 = addiu(lui(0x6A), -13440);
        t0 = 6;
        lw(v0, s0);
        jalr(0x34B0F0u, v0.u());
        jal(0x34B0F8u, gen::fn_sub_329550_00329550);
        lw(v0, sp + 588);
        a1 = v0 | 0x10;
        a0 = 2;
        jal(0x34B10Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = addiu(s2, 12);
        a1 = addiu(sp, 64);
        jal(0x34B11Cu, gen::fn_sub_348BD0_00348bd0);
        a0 = 1;
        a1 = 0;
        lw(v0, s1);
        jalr(0x34B130u, v0.u());
        a0 = 3;
        v0 = lui(0x3);
        a1 = v0 | 0x1001;
        jal(0x34B144u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = rwPRIMTYPETRILIST;
        a1 = addiu(sp, 64);
        a2 = 4;
        a3 = addiu(lui(0x6A), -13440);
        t0 = 6;
        lw(v0, s0);
        jalr(0x34B168u, v0.u());
        a0 = 2;
        lw(a1, sp + 588);
        jal(0x34B178u, gen::fn_RpSkyRenderStateSet_004d7f60);
    }
    charge(7);
    ld(ra, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 592);
}

// =========================================================================================================
// [pass] camera passes
// =========================================================================================================

// The main camera (sub_198590 = *(gp-19504)), jal at pc; it stays in $v0.
void Cpu::camera_get(u32 pc) { jal(pc, gen::fn_sub_198590_00198590); }
// RwCameraBeginUpdate(main camera): the getter, `move $a0, $v0`, the jal; $v0 = the camera, 0 = failed.
void Cpu::camera_begin(u32 pc_get, u32 pc_begin) {
    camera_get(pc_get);
    a0 = v0;
    jal(pc_begin, gen::fn_RwCameraBeginUpdate_004c9d10);
}
void Cpu::camera_end(u32 pc_get, u32 pc_end) {
    camera_get(pc_get);
    a0 = v0;
    jal(pc_end, gen::fn_RwCameraEndUpdate_004c9d00);
}

// 0x1989E0 kwlnRootUpdate2DDrawBeginTask "2D Draw Begin" (prio 4196): RwCameraClear(main camera, &colour, Z only),
// BeginUpdate; opened: kwln flags (0x40000002 off, 1 on), Z test / Z write on, sky states 2 = 68 and 3 = 0x717FB, fog
// off, the sprite file manager (sub_1120C0) and every queued sprite (sprSpriteDrawAll); failed: K_Assert(393) and
// kwln flag 0x40000000.
void Cpu::kwlnRootUpdate2DDrawBeginTask() {
    enter(20);
    sp = addiu(sp, -32);
    sd(sp + 16, ra);
    sq(sp, s0);
    camera_get(0x1989ECu);
    s0 = v0;
    jal(0x1989F8u, gen::fn_sub_1985A0_001985a0);
    a0 = s0;
    a1 = v0;
    a2 = 2;  // rwCAMERACLEARZ
    jal(0x198A0Cu, gen::fn_RwCameraClear_004c9e90);
    camera_begin(0x198A14u, 0x198A20u);
    if (v0 != 0) {
        charge(41);
        v0 = lui(0x4000);
        a0 = v0 | 2;
        a1 = 0;
        jal(0x198A3Cu, gen::fn_kwlnSetFlags_00198610);
        a0 = 1;
        a1 = a0;
        jal(0x198A4Cu, gen::fn_kwlnSetFlags_00198610);
        s0 = addiu(lui(0x96), 144);
        a0 = 6;  // rwRENDERSTATEZTESTENABLE
        a1 = 1;
        lw(v0, s0);
        jalr(0x198A68u, v0.u());
        a0 = 8;  // rwRENDERSTATEZWRITEENABLE
        a1 = 1;
        lw(v0, s0);
        jalr(0x198A7Cu, v0.u());
        a0 = 2;
        a1 = 68;
        jal(0x198A8Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 3;
        v0 = lui(0x7);
        a1 = v0 | 0x17FB;
        jal(0x198AA0u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 14;  // rwRENDERSTATEFOGENABLE
        a1 = 0;
        lw(v0, s0);
        jalr(0x198AB4u, v0.u());
        jal(0x198ABCu, gen::fn_sub_1120C0_001120c0);
        jal(0x198AC4u, gen::fn_sprSpriteDrawAll_001125d0);
    } else {
        charge(9);
        a0 = addiu(lui(0x68), -30760);  // kStrKwlnRootC
        a1 = 393;
        jal(0x198AE0u, gen::fn_sub_19D3F0_0019d3f0);
        a0 = lui(0x4000);
        a1 = 1;
        jal(0x198AF0u, gen::fn_kwlnSetFlags_00198610);
    }
    charge(6);
    v0 = 0;
    ld(ra, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 32);
}

// sub_1A4C10: a debug-shape pass over the task's work (+60): sub_359380(work, 1) with $f12 = 60.0 and
// sub_359B40(work + 48, work + 68, 1) with $f12 = 20.0 between BeginUpdate / EndUpdate.
void Cpu::sub_1A4C10() {
    enter(11);
    sp = addiu(sp, -32);
    sd(sp + 16, ra);
    sq(sp, s0);
    lw(s0, a0 + 60);
    camera_begin(0x1A4C20u, 0x1A4C2Cu);
    if (v0 != 0) {
        charge(18);
        v0 = lui(0x4270);  // 60.0f
        mtc1(v0, F12);
        a0 = s0;
        a1 = 1;
        jal(0x1A4C4Cu, gen::fn_sub_359380_00359380);
        v0 = lui(0x41A0);  // 20.0f
        mtc1(v0, F12);
        a0 = addiu(s0, 48);
        a1 = addiu(s0, 68);
        a2 = 1;
        jal(0x1A4C68u, gen::fn_sub_359B40_00359b40);
        camera_end(0x1A4C70u, 0x1A4C7Cu);
    }
    charge(6);
    v0 = 0;
    ld(ra, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 32);
}

// sub_1AE290: the collision-cylinder debug pass. work = task+60, the controller = (task+76)+60 (radius +32 kept in
// $f20); the 12-byte position on the stack is cleared, then taken from the frame of controller+16 (sub_318B60: its
// LTM, position at +48) when set; copied twice (the compiler's struct copies), the height word gp-27352 appended;
// when work+0 is set: y += radius, and sub_359B40(&pos, &height, 1) with $f12 = radius inside a camera pass.
void Cpu::sub_1AE290() {
    enter(12);
    sp = addiu(sp, -96);
    sd(sp + 32, ra);
    sq(sp + 16, s0);
    swc1(F20, sp);
    lw(s0, a0 + 60);
    lw(v0, a0 + 76);
    lw(a0, v0 + 60);
    lwc1(F20, a0 + 32);
    v1 = addiu(sp, 48);
    v0 = 12;
    if (v1 != 0) {
        for (;;) {  // memset(sp + 48, 0, 12), byte by byte
            charge(7);
            sb(v1, zero);
            v1 = addiu(v1, 1);
            v0 = addiu(v0, -1);
            if (v0 == 0) break;
            backedge();
        }
    }
    charge(3);
    lw(a0, a0 + 16);
    if (a0 != 0) {
        charge(8);
        jal(0x1AE2E8u, gen::fn_sub_318B60_00318b60);
        lwc1(F2, v0 + 48);
        lwc1(F1, v0 + 52);
        lwc1(F0, v0 + 56);
        swc1(F2, sp + 48);
        swc1(F1, sp + 52);
        swc1(F0, sp + 56);
    }
    charge(13);
    ld(v0, sp + 48);
    lwc1(F0, sp + 56);
    sd(sp + 64, v0);
    swc1(F0, sp + 72);
    ld(v0, sp + 64);
    lwc1(F0, sp + 72);
    sd(sp + 80, v0);
    swc1(F0, sp + 88);
    lwc1(F0, gp - 27352);
    swc1(F0, sp + 92);
    lw(v0, s0);
    if (v0 == 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(10);
        lwc1(F0, sp + 84);
        add_s(F0, F0, F20);
        swc1(F0, sp + 84);
        camera_begin(0x1AE354u, 0x1AE360u);
        if (v0 != 0) {
            charge(11);
            a0 = addiu(sp, 80);
            mov_s(F12, F20);
            a1 = addiu(sp, 92);
            a2 = 1;
            jal(0x1AE380u, gen::fn_sub_359B40_00359b40);
            camera_end(0x1AE388u, 0x1AE394u);
        }
        charge(1);
        v0 = 0;
    }
    charge(6);
    ld(ra, sp + 32);
    lq(s0, sp + 16);
    lwc1(F20, sp);
    sp = addiu(sp, 96);
}

// sub_3962C0: the debug-object pass of a dds3 process (task+76): its work (dds3GetProcessWorkData; none: return 0);
// inside a camera pass: dbgDrawRect(work), sub_395810(work), sub_386E50 once when work+1660 == 1, a white-ish
// (20, 20, 255, 255) sub_359B40(work + 1668, colour) with $f12 = work+1680 once when work+1664 == 1, sub_395950(work).
void Cpu::sub_3962C0() {
    enter(9);
    sp = addiu(sp, -48);
    sd(sp + 16, ra);
    sq(sp, s0);
    lw(a0, a0 + 76);
    jal(0x3962D0u, gen::fn_dds3GetProcessWorkData_0035ae10);
    s0 = v0;
    if (s0 == 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(7);
        camera_begin(0x3962F0u, 0x3962FCu);
        if (v0 != 0) {
            charge(10);
            a0 = s0;
            jal(0x396310u, gen::fn_dbgDrawRect_00395570);
            a0 = s0;
            jal(0x39631Cu, gen::fn_sub_395810_00395810);
            lw(v1, s0 + 1660);
            v0 = 1;
            if (v1 == v0) {
                charge(3);
                jal(0x396334u, gen::fn_sub_386E50_00386e50);
                sw(s0 + 1660, zero);
            }
            charge(4);
            lw(v0, s0 + 1664);
            a2 = 1;
            if (v0 == a2) {
                charge(12);
                v0 = 20;
                sb(sp + 44, v0);
                sb(sp + 45, v0);
                v0 = 255;
                sb(sp + 46, v0);
                sb(sp + 47, v0);
                a0 = addiu(s0, 1668);
                lwc1(F12, s0 + 1680);
                a1 = addiu(sp, 44);
                jal(0x396374u, gen::fn_sub_359B40_00359b40);
                sw(s0 + 1664, zero);
            }
            charge(8);
            a0 = s0;
            jal(0x396384u, gen::fn_sub_395950_00395950);
            camera_end(0x39638Cu, 0x396398u);
        }
        charge(1);
        v0 = 0;
    }
    charge(5);
    ld(ra, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 48);
}


// =========================================================================================================
// [cull] the model's atomic lists (22_rendering.md section 2.2; c7 culling)
// =========================================================================================================
//
// A model (the sub_317A20 record, +224) keeps its atomics in linked lists of 44-byte nodes: +0 the RpAtomic, +4 1 =
// fog off around it, +8 a translucency kind, +12 the colour block sub_1A7910 applies, +24 the alpha (float), +28 the
// blend kind, +40 the next node. Lists by offset: +8 / +20 / +24 / +28 the opaque passes (sub_1A7B50), +32 the
// opaque-only filter (sub_1A7FC0), +12 / +16 / +20 / +36 / +40 the translucent passes (sub_1A8140). Every atomic is
// drawn through its render callback (atomic +72, i.e. +0x48: AtomicDefaultRenderCallBack) after the frustum test of its
// world bounding sphere (atomicGetWorldBoundingSphere) against the current camera (0x960070 = RWSRCGLOBAL(curCamera)), each list gated by
// its own enable word (gp-27404 .. gp-27372).

// The list walk the compiler laid out with its test first: 2 cycles per test, a check point before every node, the
// body, then 1 cycle for `node = node->next` (+40). The body returns early for the compiled `goto next`.
template <class Body> void Cpu::walk_nodes(Gpr& node, Body body) {
    for (;;) {
        charge(2);
        if (node == 0) return;
        backedge();
        body();
        charge(1);
        lw(node, node + 40);
    }
}

// The frustum test of the node's atomic: atomicGetWorldBoundingSphere(atomic) -> its world sphere (jal at pc), sub_4C9DF0(curCamera,
// sphere) (jal at pc + 0x14); true when the sphere is not outside.
bool Cpu::atomic_visible(const Gpr& node, u32 pc) {
    charge(10);
    lw(a0, node);
    jal(pc, gen::fn_atomicGetWorldBoundingSphere_004912b0);
    v1 = lui(0x96);
    lw(a0, v1 + 112);
    a1 = v0;
    jal(pc + 0x14, gen::fn_sub_4C9DF0_004c9df0);
    return v0 != 0;
}
// node+4 == 1: RwRenderStateSet(FOGENABLE, 0) before the atomic ($x = the flag, $y = 1 as the compiler chose them).
void Cpu::fog_off_if_flagged(const Gpr& node, Gpr& x, Gpr& y, u32 pc) {
    charge(4);
    lw(x, node + 4);
    y = 1;
    if (x == y) {
        charge(6);
        a0 = 14;
        a1 = 0;
        call_pfn(pc, kPfnRenderStateSet);
    }
}
// The list's enable word == 1: the atomic's render callback (atomic +72) through jalr at pc.
void Cpu::render_if_enabled(s32 gp_flag, const Gpr& node, Gpr& x, Gpr& y, u32 pc) {
    charge(4);
    lw(x, gp + gp_flag);
    y = 1;
    if (x == y) render_atomic(node, pc);
}
void Cpu::render_atomic(const Gpr& node, u32 pc) {
    charge(4);
    lw(a0, node);
    lw(v0, a0 + 72);
    jalr(pc, v0.u());
}
// node+4 == 1: RwRenderStateSet(FOGENABLE, 1) after it ($a1 = 1 is the compare operand).
void Cpu::fog_on_if_flagged(const Gpr& node, Gpr& x, u32 pc) {
    charge(4);
    lw(x, node + 4);
    a1 = 1;
    if (x == a1) {
        charge(5);
        a0 = 14;
        call_pfn(pc, kPfnRenderStateSet);
    }
}
// mode == 1: Z test on, Z write `zwrite` (jalrs at pc and pc + 0x14, the device pointer's address in `base`); the
// compare loads $a1 = 1 first.
void Cpu::ztest_states(const Gpr& mode, Gpr& base, u32 pc, u32 zwrite) {
    charge(3);
    a1 = 1;
    if (mode == a1) {
        charge(11);
        base = addiu(lui(0x96), 144);
        a0 = 6;
        lw(v0, base);
        jalr(pc, v0.u());
        a0 = 8;
        a1 = zwrite;
        lw(v0, base);
        jalr(pc + 0x14, v0.u());
    }
}
// RpSkyRenderStateSet(2, ref) and RpSkyRenderStateSet(3, 0x70000 | lo) (jals at pc and pc + 0x14): the alpha-test
// reference and the sky blend / test word of the pass.
void Cpu::sky_states(u32 pc, u32 ref, u32 lo) {
    a0 = 2;
    a1 = ref;
    jal(pc, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 3;
    v0 = lui(0x7);
    a1 = v0 | lo;
    jal(pc + 0x14, gen::fn_RpSkyRenderStateSet_004d7f60);
}
// The opaque test of a node: *sp+slot = 0, sub_4932C0(geometry = atomic +24, the per-material callback 0x1A74B0,
// sp + slot) sets it when a material is translucent (jal at pc). False when the atomic has no geometry; $x / $y as the
// compiler chose them.
bool Cpu::geometry_scan(const Gpr& node, Gpr& x, s32 slot, u32 pc) {
    charge(5);
    sw(sp + slot, zero);
    lw(x, node);
    lw(a0, x + 24);
    if (a0 == 0) return false;
    charge(8);
    a1 = addiu(lui(0x1A), 29872);
    a2 = addiu(sp, slot);
    jal(pc, gen::fn_sub_4932C0_004932c0);
    return true;
}

// sub_1A7B50(model lists, mode): the opaque passes. mode == 1 brackets each Z state group with Z test / write.
//   +8:  blend 0x717FB, enable gp-27404;
//   +20: the colour-blocked atomics (sub_1A7910(atomic, node + 12) first), drawn only when a material is translucent
//        (the 0x1A74B0 scan) and the node alpha >= 1.0, enable gp-27404;
//   +24: Z write off when mode == 1, blend 0x717FB, enable gp-27388;
//   +28: Z write on, blend 0x715FB, enable gp-27384.
void Cpu::sub_1A7B50() {
    enter(10);
    sp = addiu(sp, -96);
    sd(sp + 64, ra);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    s2 = a0;
    s1 = a1;
    if (s2 != 0) {
        ztest_states(s1, s0, 0x1A7B94u, 1);
        charge(12);
        sky_states(0x1A7BB8u, 68, 0x17FB);
        lw(s0, s2 + 8);
        walk_nodes(s0, [&] {
            if (!atomic_visible(s0, 0x1A7BE4u)) return;
            fog_off_if_flagged(s0, v1, v0, 0x1A7C28u);
            render_if_enabled(-27404, s0, v1, v0, 0x1A7C48u);
            fog_on_if_flagged(s0, v0, 0x1A7C6Cu);
        });
        charge(3);
        lw(s0, s2 + 20);
        walk_nodes(s0, [&] {
            charge(5);
            sw(sp + 92, zero);
            lw(a0, s0);
            lw(s3, a0 + 24);
            if (s3 == 0) return;
            charge(16);
            a1 = addiu(s0, 12);
            jal(0x1A7CA4u, gen::fn_sub_1A7910_001a7910);
            a0 = s3;
            a1 = addiu(lui(0x1A), 29872);
            a2 = addiu(sp, 92);
            jal(0x1A7CBCu, gen::fn_sub_4932C0_004932c0);
            lwc1(F1, s0 + 24);
            v0 = lui(0x3F80);
            mtc1(v0, F0);
            c_lt_s(F1, F0);
            if (cop1_cond()) return;  // alpha < 1.0
            charge(4);
            lw(v1, sp + 92);
            v0 = 1;
            if (v1 != v0) return;
            if (!atomic_visible(s0, 0x1A7CF4u)) return;
            fog_off_if_flagged(s0, v1, v0, 0x1A7D38u);
            render_if_enabled(-27404, s0, v1, v0, 0x1A7D58u);
            fog_on_if_flagged(s0, v0, 0x1A7D7Cu);
        });
        ztest_states(s1, s0, 0x1A7DACu, 0);
        charge(12);
        sky_states(0x1A7DD0u, 68, 0x17FB);
        lw(s0, s2 + 24);
        walk_nodes(s0, [&] {
            if (!atomic_visible(s0, 0x1A7DFCu)) return;
            fog_off_if_flagged(s0, v1, v0, 0x1A7E40u);
            render_if_enabled(-27388, s0, v1, v0, 0x1A7E60u);
            fog_on_if_flagged(s0, v0, 0x1A7E84u);
        });
        ztest_states(s1, s0, 0x1A7EB4u, 1);
        charge(12);
        sky_states(0x1A7ED8u, 68, 0x15FB);
        lw(s0, s2 + 28);
        walk_nodes(s0, [&] {
            if (!atomic_visible(s0, 0x1A7F04u)) return;
            fog_off_if_flagged(s0, a0, v1, 0x1A7F48u);
            render_if_enabled(-27384, s0, a0, v1, 0x1A7F68u);
            fog_on_if_flagged(s0, v1, 0x1A7F8Cu);
        });
    }
    charge(8);
    ld(ra, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 96);
}

// sub_1A7FC0(model lists, mode): the +32 list, only the atomics whose materials are all opaque (the 0x1A74B0 scan
// leaves its word 0); blend 0x717FB, enable gp-27380. mode == 1: Z test on, Z write off first.
void Cpu::sub_1A7FC0() {
    enter(7);
    sp = addiu(sp, -64);
    sd(sp + 32, ra);
    sq(sp + 16, s1);
    sq(sp, s0);
    s0 = a0;
    if (s0 != 0) {
        charge(3);
        v0 = 1;
        if (a1 == v0) {
            charge(12);
            s1 = addiu(lui(0x96), 144);
            a0 = 6;
            a1 = v0;
            lw(v0, s1);
            jalr(0x1A7FFCu, v0.u());
            a0 = 8;
            a1 = 0;
            lw(v0, s1);
            jalr(0x1A8010u, v0.u());
        }
        charge(12);
        sky_states(0x1A8020u, 68, 0x17FB);
        lw(s0, s0 + 32);
        walk_nodes(s0, [&] {
            if (!geometry_scan(s0, v1, 60, 0x1A8068u)) return;
            lw(v1, sp + 60);
            if (v1 != 0) return;
            if (!atomic_visible(s0, 0x1A8080u)) return;
            fog_off_if_flagged(s0, a0, v1, 0x1A80C4u);
            render_if_enabled(-27380, s0, a0, v1, 0x1A80E4u);
            fog_on_if_flagged(s0, v1, 0x1A8108u);
        });
    }
    charge(6);
    ld(ra, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 64);
}

// A translucent node whose alpha (+24) is strictly between 0 and 1 and whose kind (+8) is 1 goes to the sorted
// translucent queue (sub_1A8920(0x8668F0, node)) instead of being drawn now; `y` holds 1 (the kind compare operand)
// and `x` the kind, as the compiler chose them. Returns true when it was queued or rejected by the enable word,
// false when the node is to be drawn directly (the caller's L_render path).
bool Cpu::queue_translucent(const Gpr& node, Gpr& x, Gpr& y, s32 gp_flag, u32 pc) {
    charge(4);
    lw(x, node + 8);
    y = 1;
    if (x != y) return false;
    charge(7);
    lwc1(F1, node + 24);
    x = lui(0x3F80);
    mtc1(x, F0);
    c_lt_s(F1, F0);
    if (!cop1_cond()) return false;  // alpha >= 1
    charge(5);
    mtc1(zero, F0);
    c_le_s(F1, F0);
    if (cop1_cond()) return false;  // alpha <= 0
    charge(3);
    lw(x, gp + gp_flag);
    if (x != y) return true;
    charge(7);
    a0 = addiu(lui(0x86), 26864);  // the translucent queue 0x8668F0
    a1 = node;
    jal(pc, gen::fn_sub_1A8920_001a8920);
    return true;
}

// sub_1A8140(model lists, mode): the translucent passes.
//   +12: blend 0x715FB (Z test / write on when mode == 1), enable gp-27400;
//   +16: blend 0x707FD when gp-19352 == 1, else 0x735FB, enable gp-27396;
//   +20: Z write off, blend 0x717FB, the atomics with a translucent material (kind 0 or alpha == 1.0: drawn when
//        gp-27392 == 1);
//   +40: Z write off, alpha ref 66, blend 0x71801: kind-1 nodes with 0 < alpha < 1 queued (gp-27372), others drawn;
//   +36: alpha ref 72, blend 0x71801: the same with gp-27376;
//   +20 again: the kind-1 translucent nodes queued when gp-27392 == 1.
void Cpu::sub_1A8140() {
    enter(9);
    sp = addiu(sp, -80);
    sd(sp + 48, ra);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    s0 = a0;
    s2 = a1;
    if (s0 != 0) {
        ztest_states(s2, s1, 0x1A8180u, 1);
        charge(12);
        sky_states(0x1A81A4u, 68, 0x15FB);
        lw(s1, s0 + 12);
        walk_nodes(s1, [&] {
            if (!atomic_visible(s1, 0x1A81D0u)) return;
            fog_off_if_flagged(s1, v1, v0, 0x1A8214u);
            render_if_enabled(-27400, s1, v1, v0, 0x1A8234u);
            fog_on_if_flagged(s1, v0, 0x1A8258u);
        });
        charge(4);
        lw(v1, gp - 19352);
        v0 = 1;
        if (v1 == v0) {
            charge(11);
            sky_states(0x1A8284u, 68, 0x07FD);
        } else {
            charge(9);
            sky_states(0x1A82B0u, 68, 0x35FB);
        }
        charge(3);
        lw(s1, s0 + 16);
        walk_nodes(s1, [&] {
            if (!atomic_visible(s1, 0x1A82DCu)) return;
            fog_off_if_flagged(s1, v1, v0, 0x1A8320u);
            render_if_enabled(-27396, s1, v1, v0, 0x1A8340u);
            fog_on_if_flagged(s1, v0, 0x1A8364u);
        });
        ztest_states(s2, s1, 0x1A8394u, 0);
        charge(12);
        sky_states(0x1A83B8u, 68, 0x17FB);
        lw(s1, s0 + 20);
        walk_nodes(s1, [&] {
            if (!geometry_scan(s1, v0, 76, 0x1A8400u)) return;
            lw(v0, sp + 76);
            if (v0 != 0) return;
            if (!atomic_visible(s1, 0x1A8418u)) return;
            fog_off_if_flagged(s1, v1, v0, 0x1A845Cu);
            charge(3);
            lw(v0, s1 + 8);
            bool draw = true;
            if (v0 != 0) {
                charge(7);
                lwc1(F1, s1 + 24);
                v0 = lui(0x3F80);
                mtc1(v0, F0);
                c_eq_s(F0, F1);
                draw = cop1_cond();  // alpha == 1.0
            }
            if (draw) render_if_enabled(-27392, s1, v1, v0, 0x1A84A4u);
            fog_on_if_flagged(s1, v0, 0x1A84C8u);
        });
        ztest_states(s2, s1, 0x1A84F8u, 0);
        charge(12);
        sky_states(0x1A851Cu, 66, 0x1801);
        lw(s1, s0 + 40);
        walk_nodes(s1, [&] {
            if (!atomic_visible(s1, 0x1A8548u)) return;
            fog_off_if_flagged(s1, v1, v0, 0x1A858Cu);
            if (!queue_translucent(s1, v0, v1, -27372, 0x1A85ECu)) render_if_enabled(-27372, s1, v1, v0, 0x1A8614u);
            fog_on_if_flagged(s1, v0, 0x1A8638u);
        });
        charge(12);
        sky_states(0x1A8654u, 72, 0x1801);
        lw(s1, s0 + 36);
        walk_nodes(s1, [&] {
            if (!atomic_visible(s1, 0x1A8680u)) return;
            fog_off_if_flagged(s1, a0, v1, 0x1A86C4u);
            if (!queue_translucent(s1, v1, a0, -27376, 0x1A8724u)) render_if_enabled(-27376, s1, a0, v1, 0x1A874Cu);
            fog_on_if_flagged(s1, v1, 0x1A8770u);
        });
        charge(3);
        lw(s0, s0 + 20);
        walk_nodes(s0, [&] {
            charge(4);
            lw(v1, s0 + 8);
            a0 = 1;
            if (v1 != a0) return;
            charge(3);
            lw(v1, gp - 27392);
            if (v1 != a0) return;
            charge(7);
            lwc1(F1, s0 + 24);
            v1 = lui(0x3F80);
            mtc1(v1, F0);
            c_lt_s(F1, F0);
            if (!cop1_cond()) return;
            charge(5);
            mtc1(zero, F0);
            c_le_s(F1, F0);
            if (cop1_cond()) return;
            charge(5);
            a0 = addiu(lui(0x86), 26864);
            a1 = s0;
            jal(0x1A87E8u, gen::fn_sub_1A8920_001a8920);
        });
    }
    charge(7);
    ld(ra, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 80);
}

// sub_1A8B10(queue): the sorted translucent queue ({count, node[count] of 44 bytes}, e.g. 0x8668F0): qsort by the
// comparator 0x1A89C0, then back to front: the frustum test, fog off per node, sub_1A7910 (colour block); 0 < alpha
// < 1: Z test / write on, alpha ref 68, blend 0x72001, the callback when the blend kind (+28) is 2; Z write off, the
// blend of the kind (3: ref 72 / 0x71801, 4: ref 66 / 0x71801, 2: ref 68 / 0x717FB, others unchanged), the callback
// again; fog on.
void Cpu::sub_1A8B10() {
    enter(18);
    sp = addiu(sp, -80);
    sd(sp + 64, ra);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    s2 = a0;
    lw(a1, a0);
    a0 = addiu(s2, 4);
    a2 = 44;
    a3 = addiu(lui(0x1B), -30272);  // the comparator 0x1A89C0
    jal(0x1A8B40u, gen::fn_qsort_005225f8);
    lw(v1, s2);
    s1 = addiu(v1, -1);
    for (;;) {
        charge(2);
        if (sgn(s1) < 0) break;
        backedge();
        charge(17);
        v0 = sll(s1, 2);
        v0 = addu(v0, s1);
        v0 = sll(v0, 1);
        v0 = addu(v0, s1);
        v0 = sll(v0, 2);
        v0 = addu(s2, v0);  // queue + 44 * i
        s0 = addiu(v0, 4);
        lw(a0, v0 + 4);
        jal(0x1A8B78u, gen::fn_atomicGetWorldBoundingSphere_004912b0);
        v1 = lui(0x96);
        lw(a0, v1 + 112);
        a1 = v0;
        jal(0x1A8B8Cu, gen::fn_sub_4C9DF0_004c9df0);
        if (v0 != 0) {
            charge(4);
            lw(v1, s0 + 4);
            v0 = 1;
            if (v1 == v0) {
                charge(6);
                a0 = 14;
                a1 = 0;
                call_pfn(0x1A8BBCu, kPfnRenderStateSet);
            }
            charge(11);
            lw(a0, s0);
            a1 = addiu(s0, 12);
            jal(0x1A8BCCu, gen::fn_sub_1A7910_001a7910);
            lwc1(F1, s0 + 24);
            v1 = lui(0x3F80);
            mtc1(v1, F0);
            c_lt_s(F1, F0);
            bool partial = false;
            if (cop1_cond()) {
                charge(5);
                mtc1(zero, F0);
                c_le_s(F1, F0);
                partial = !cop1_cond();
            }
            if (partial) {
                charge(25);
                s3 = addiu(lui(0x96), 144);
                a0 = 6;
                a1 = 1;
                lw(v0, s3);
                jalr(0x1A8C18u, v0.u());
                a0 = 8;
                a1 = 1;
                lw(v0, s3);
                jalr(0x1A8C2Cu, v0.u());
                sky_states(0x1A8C3Cu, 68, 0x2001);
                lw(v1, s0 + 28);
                v0 = 2;
                if (v1 == v0) render_atomic(s0, 0x1A8C70u);
                charge(16);
                s3 = addiu(lui(0x96), 144);
                a0 = 6;
                a1 = 1;
                lw(v0, s3);
                jalr(0x1A8C8Cu, v0.u());
                a0 = 8;
                a1 = 0;
                lw(v0, s3);
                jalr(0x1A8CA0u, v0.u());
                lw(v1, s0 + 28);
                v0 = 3;
                if (v1 == v0) {
                    charge(9);
                    sky_states(0x1A8D34u, 72, 0x1801);
                } else {
                    charge(3);
                    v0 = 4;
                    if (v1 == v0) {
                        charge(11);
                        sky_states(0x1A8D08u, 66, 0x1801);
                    } else {
                        charge(3);
                        a0 = 2;
                        if (v1 == a0) {
                            charge(10);
                            a1 = 68;
                            jal(0x1A8CDCu, gen::fn_RpSkyRenderStateSet_004d7f60);
                            a0 = 3;
                            v0 = lui(0x7);
                            a1 = v0 | 0x17FB;
                            jal(0x1A8CF0u, gen::fn_RpSkyRenderStateSet_004d7f60);
                        } else {
                            charge(2);
                        }
                    }
                }
                render_atomic(s0, 0x1A8D58u);
            }
            fog_on_if_flagged(s0, v1, 0x1A8D7Cu);
        }
        charge(1);
        s1 = addiu(s1, -1);
    }
    charge(8);
    ld(ra, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 80);
}

// sub_315C20(model): the model's atomic passes with the model's own render states. Flags +216: 0x400 = the model is
// faded (sub_3164C0(+220) first; blend 0x7000F, or by the alpha byte +211: 0x704FD when >= 201, else 0x7008D, when 0x200
// is clear), 0x200 = drawn whole, 0x800 = with its own states (+228 / +232) whole. Alpha ref 100, Z test on, fog saved
// and off; no lists (+224) or flag 0x200: sub_1A88E0(+220) draws the clump; else every atomic of list +8 in the
// frustum. Then fog restored, and the second half: whole (sub_1A88E0) with the model's states and Z write off, or the
// three list passes sub_1A7B50 / sub_1A7FC0 / sub_1A8140(lists, 0).
void Cpu::sub_315C20() {
    enter(11);
    sp = addiu(sp, -96);
    sd(sp + 64, ra);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    s1 = a0;
    lhu(v0, a0 + 216);
    v0 = v0 & 0x400;
    if (v0 != 0) {
        charge(3);
        lw(a0, s1 + 220);
        jal(0x315C50u, gen::fn_sub_3164C0_003164c0);
    }
    charge(8);
    a0 = 2;
    a1 = 100;
    jal(0x315C60u, gen::fn_RpSkyRenderStateSet_004d7f60);
    lhu(v1, s1 + 216);
    v0 = v1 & 0x200;
    bool plain = true;
    if (v0 != 0) {
        charge(3);
        v0 = v1 & 0x400;
        plain = v0 != 0;
    }
    if (plain) {
        charge(7);
        a0 = 3;
        v0 = lui(0x7);
        a1 = v0 | 0xF;
        jal(0x315C90u, gen::fn_RpSkyRenderStateSet_004d7f60);
    } else {
        charge(4);
        lbu(v0, s1 + 211);
        at = slti(v0, 201);
        if (at == 0) {
            charge(7);
            a0 = 3;
            v0 = lui(0x7);
            a1 = v0 | 0x4FD;
            jal(0x315CBCu, gen::fn_RpSkyRenderStateSet_004d7f60);
        } else {
            charge(5);
            a0 = 3;
            v0 = lui(0x7);
            a1 = v0 | 0x8D;
            jal(0x315CD8u, gen::fn_RpSkyRenderStateSet_004d7f60);
        }
    }
    charge(21);
    s0 = addiu(lui(0x96), 144);
    a0 = 6;
    a1 = 1;
    lw(v0, s0);
    jalr(0x315CF4u, v0.u());
    a0 = 14;
    a1 = addiu(sp, 92);
    call_pfn(0x315D0Cu, kPfnRenderStateGet);  // the fog state into sp + 92
    a0 = 14;
    a1 = 0;
    lw(v0, s0);
    jalr(0x315D20u, v0.u());
    lw(v1, s1 + 224);
    bool whole = true;
    if (v1 != 0) {
        charge(4);
        lhu(v0, s1 + 216);
        v0 = v0 & 0x200;
        whole = v0 != 0;
    }
    if (whole) {
        charge(5);
        lw(a0, s1 + 220);
        jal(0x315D48u, gen::fn_sub_1A88E0_001a88e0);
    } else {
        charge(5);
        v0 = lui(0x96);
        lw(s2, v0 + 112);  // the current camera
        lw(s3, v1 + 8);
        for (;;) {
            charge(2);
            if (s3 == 0) break;
            backedge();
            charge(9);
            lw(a0, s3);
            jal(0x315D70u, gen::fn_atomicGetWorldBoundingSphere_004912b0);
            a0 = s2;
            a1 = v0;
            jal(0x315D80u, gen::fn_sub_4C9DF0_004c9df0);
            if (v0 != 0) render_atomic(s3, 0x315D98u);
            charge(1);
            lw(s3, s3 + 40);
        }
    }
    charge(8);
    a0 = 14;
    lw(a1, sp + 92);
    lw(v0, s0);
    jalr(0x315DB8u, v0.u());
    lw(v0, s1 + 224);
    bool own = true;
    if (v0 != 0) {
        charge(4);
        lhu(v0, s1 + 216);
        v0 = v0 & 0x800;
        own = v0 != 0;
    }
    charge(25);
    if (own) {
        a0 = 2;
        lw(a1, s1 + 228);
        jal(0x315DE4u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 3;
        lw(a1, s1 + 232);
        jal(0x315DF4u, gen::fn_RpSkyRenderStateSet_004d7f60);
        s0 = addiu(lui(0x96), 144);
        a0 = 6;
        a1 = 1;
        lw(v0, s0);
        jalr(0x315E10u, v0.u());
        a0 = 8;
        a1 = 0;
        lw(v0, s0);
        jalr(0x315E24u, v0.u());
        lw(a0, s1 + 220);
        jal(0x315E30u, gen::fn_sub_1A88E0_001a88e0);
    } else {
        s0 = addiu(lui(0x96), 144);
        a0 = 6;
        a1 = 1;
        lw(v0, s0);
        jalr(0x315E54u, v0.u());
        a0 = 8;
        a1 = 0;
        lw(v0, s0);
        jalr(0x315E68u, v0.u());
        lw(s0, s1 + 224);
        a0 = s0;
        a1 = 0;
        jal(0x315E7Cu, gen::fn_sub_1A7B50_001a7b50);
        a0 = s0;
        a1 = 0;
        jal(0x315E8Cu, gen::fn_sub_1A7FC0_001a7fc0);
        a0 = s0;
        a1 = 0;
        jal(0x315E9Cu, gen::fn_sub_1A8140_001a8140);
    }
    charge(8);
    ld(ra, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 96);
}

// sub_1A50F0(task): a single-atomic task (work +60: +0 enabled, +4 a model whose root LTM, sub_318B60, is copied (64
// bytes, 8 words a step) and set as the atomic's frame transform (sub_4CB7F0, replace), +8 -> +20 the atomic): inside a
// camera pass, gouraud, Z test on / write off, vertex alpha on, alpha ref 68, blend 0x717FB, the atomic's callback when
// its sphere is in the frustum.
void Cpu::sub_1A50F0() {
    enter(8);
    sp = addiu(sp, -112);
    sd(sp + 32, ra);
    sq(sp + 16, s1);
    sq(sp, s0);
    lw(s0, a0 + 60);
    lw(v0, s0);
    if (v0 == 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(3);
        lw(a0, s0 + 4);
        if (a0 != 0) {
            charge(4);
            jal(0x1A5128u, gen::fn_sub_318B60_00318b60);
            a2 = addiu(sp, 48);
            a1 = 8;
            for (;;) {  // the 64-byte matrix, two words a step
                charge(9);
                lw(a0, v0);
                lw(v1, v0 + 4);
                v0 = addiu(v0, 8);
                a1 = addiu(a1, -1);
                sw(a2, a0);
                sw(a2 + 4, v1);
                a2 = addiu(a2, 8);
                if (sgn(a1) <= 0) break;
                backedge();
            }
            charge(7);
            lw(v0, s0 + 8);
            lw(v0, v0 + 20);
            lw(a0, v0 + 4);
            a1 = addiu(sp, 48);
            a2 = 0;
            jal(0x1A5170u, gen::fn_sub_4CB7F0_004cb7f0);
        }
        charge(7);
        camera_begin(0x1A5178u, 0x1A5184u);
        if (v0 != 0) {
            charge(42);
            s1 = addiu(lui(0x96), 144);
            a0 = 7;  // rwRENDERSTATESHADEMODE
            a1 = 2;  // gouraud
            lw(v0, s1);
            jalr(0x1A51A8u, v0.u());
            a0 = 6;
            a1 = 1;
            lw(v0, s1);
            jalr(0x1A51BCu, v0.u());
            a0 = 8;
            a1 = 0;
            lw(v0, s1);
            jalr(0x1A51D0u, v0.u());
            a0 = 12;  // rwRENDERSTATEVERTEXALPHAENABLE
            a1 = 1;
            lw(v0, s1);
            jalr(0x1A51E4u, v0.u());
            sky_states(0x1A51F4u, 68, 0x17FB);
            lw(v0, s0 + 8);
            lw(a0, v0 + 20);
            jal(0x1A5218u, gen::fn_atomicGetWorldBoundingSphere_004912b0);
            v1 = lui(0x96);
            lw(a0, v1 + 112);
            a1 = v0;
            jal(0x1A522Cu, gen::fn_sub_4C9DF0_004c9df0);
            if (v0 != 0) {
                charge(5);
                lw(v0, s0 + 8);
                lw(a0, v0 + 20);
                lw(v0, a0 + 72);
                jalr(0x1A5248u, v0.u());
            }
            charge(5);
            camera_end(0x1A5250u, 0x1A525Cu);
        }
        charge(1);
        v0 = 0;
    }
    charge(6);
    ld(ra, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 112);
}


// =========================================================================================================
// [shape] debug shapes: Im3D lines and a projected Im2D circle (collision / camera / effect debug views)
// =========================================================================================================
//
// The five share a render-state bracket: when their `save` argument is set, the six states of the table 0x69CE60
// ({state, value} x 6) are read into the frame (RwRenderStateGet) and set to the table's values, then texture off,
// alpha ref 72 and blend 0x71801 (sub_358460: 68 / 0x717FB); at the end the saved values are set back.

// Save and set the six states (counter / entry registers as the compiler chose them; jalrs at pc_get, pc_get + 0x18),
// then the texture / alpha / blend states (jalr at pc_tex, jals at pc_tex + 0x10 / + 0x24).
void Cpu::states_push(Gpr& i, Gpr& entry, s32 slot, u32 pc_get, u32 pc_tex, u32 ref, u32 lo) {
    charge(3);
    i = 0;
    for (;;) {
        charge(3);
        v0 = sltiu(i, 6);
        if (v0 == 0) break;
        backedge();
        charge(19);
        v1 = sll(i, 3);
        v0 = addiu(lui(0x6A), -12704);  // the state table 0x69CE60
        entry = addu(v0, v1);
        v0 = sll(i, 2);
        v0 = addu(v0, sp);
        lw(a0, entry);
        a1 = addiu(v0, slot);
        call_pfn(pc_get, kPfnRenderStateGet);
        lw(a0, entry);
        lw(a1, entry + 4);
        call_pfn(pc_get + 0x18, kPfnRenderStateSet);
        i = addiu(i, 1);
    }
    charge(15);
    a0 = 1;
    a1 = 0;
    call_pfn(pc_tex, kPfnRenderStateSet);
    a0 = 2;
    a1 = ref;
    jal(pc_tex + 0x10, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 3;
    v0 = lui(0x7);
    a1 = v0 | lo;
    jal(pc_tex + 0x24, gen::fn_RpSkyRenderStateSet_004d7f60);
}
// Set the six saved values back ($s0 the counter, $v1 / $v0 the scratch, jalr at pc).
void Cpu::states_pop(s32 slot, u32 pc) {
    charge(3);
    s0 = 0;
    for (;;) {
        charge(3);
        v1 = sltiu(s0, 6);
        if (v1 == 0) break;
        backedge();
        charge(13);
        v1 = sll(s0, 3);
        v0 = addiu(lui(0x6A), -12704);
        v1 = addu(v0, v1);
        v0 = sll(s0, 2);
        v0 = addu(v0, sp);
        lw(a0, v1);
        lw(a1, v0 + slot);
        call_pfn(pc, kPfnRenderStateSet);
        s0 = addiu(s0, 1);
    }
}
// The identity RwMatrix at sp + m (right / up / at / pos, the flags word +12 |= rwMATRIXTYPEORTHONORMAL | 0x20000 over
// whatever the frame held there).
void Cpu::identity_matrix(s32 m) {
    v0 = lui(0x3F80);
    sw(sp + m + 40, v0);
    sw(sp + m + 20, v0);
    sw(sp + m, v0);
    sw(sp + m + 16, zero);
    sw(sp + m + 8, zero);
    sw(sp + m + 4, zero);
    sw(sp + m + 36, zero);
    sw(sp + m + 32, zero);
    sw(sp + m + 24, zero);
    sw(sp + m + 56, zero);
    sw(sp + m + 52, zero);
    sw(sp + m + 48, zero);
    lw(v1, sp + m + 12);
    v0 = lui(0x2);
    v0 = v0 | 3;
    v0 = v1 | v0;
    sw(sp + m + 12, v0);
}
// A colour byte as a float (`lbu` then the unsigned-convert idiom; the negative branch is never taken for a byte):
// v0 = the byte; F0 = the float. `next` is the cost of the block that stores it.
void Cpu::byte_to_f0() {
    if (sgn(v0) < 0) {
        charge(7);
        v1 = srl(v0, 1);
        v0 = v0 & 1;
        v1 = v1 | v0;
        mtc1(v1, F0);
        cvt_s_w(F0, F0);
        add_s(F0, F0, F0);
    } else {
        charge(5);
        mtc1(v0, F0);
        cvt_s_w(F0, F0);
    }
}

// sub_359110(a, b, colour, save): one Im3D line from *a to *b (two 36-byte RwIm3DVertex at sp + 208 / + 244, the
// RwRGBA bytes copied to +12 of each) through RwIm3DTransform(verts, 2, identity, 2) and RwIm3DRenderLine(0, 1).
void Cpu::sub_359110() {
    enter(14);
    sp = addiu(sp, -320);
    sd(sp + 96, ra);
    sq(sp + 80, s5);
    sq(sp + 64, s4);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    s5 = a0;
    s4 = a1;
    s3 = a2;
    s2 = a3;
    if (s2 != 0) states_push(s1, s0, 112, 0x35917Cu, 0x3591BCu);
    charge(70);
    identity_matrix(144);
    lwc1(F0, s5);
    swc1(F0, sp + 304);
    lwc1(F0, s5 + 4);
    swc1(F0, sp + 308);
    lwc1(F0, s5 + 8);
    swc1(F0, sp + 312);
    a0 = addiu(sp, 208);
    ld(v0, sp + 304);
    lwc1(F0, sp + 312);
    sd(sp + 208, v0);
    swc1(F0, sp + 216);
    lwc1(F0, s4);
    swc1(F0, sp + 288);
    lwc1(F0, s4 + 4);
    swc1(F0, sp + 292);
    lwc1(F0, s4 + 8);
    swc1(F0, sp + 296);
    lwc1(F2, sp + 288);
    lwc1(F1, sp + 292);
    lwc1(F0, sp + 296);
    swc1(F2, sp + 244);
    swc1(F1, sp + 248);
    swc1(F0, sp + 252);
    for (s32 vtx : {220, 256}) {  // the RwRGBA of each vertex, byte by byte
        v1 = addiu(sp, vtx);
        for (u32 k = 0; k < 4; ++k) {
            lbu(v0, s3 + k);
            sb(v1 + k, v0);
        }
    }
    a1 = 2;
    a2 = addiu(sp, 144);
    a3 = a1;
    jal(0x3592E0u, gen::fn_sub_4F1ED0_004f1ed0);  // RwIm3DTransform
    a0 = 0;
    a1 = 1;
    jal(0x3592F0u, gen::fn_sub_4F22B0_004f22b0);  // RwIm3DRenderLine(0, 1)
    if (s2 != 0) states_pop(112, 0x359334u);
    charge(10);
    ld(ra, sp + 96);
    lq(s5, sp + 80);
    lq(s4, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 320);
}

// sub_359560(centre, colour, matrix, save) with $f12 = the radius: a circle of 20 segments around *centre in the
// plane of `matrix` (identity when null), each point transformed into camera space (camera +32) and projected to the
// 640 x 448 screen with the near / far planes (camera +128 / +132) and the Im2D near / far screen z (0x960088 /
// 0x96008C); drawn as one 21-vertex Im2D polyline. Culled by its bounding sphere first.
void Cpu::sub_359560() {
    enter(32);
    sp = addiu(sp, -1632);
    sd(sp + 112, ra);
    sq(sp + 96, s4);
    sq(sp + 80, s3);
    sq(sp + 64, s2);
    sq(sp + 48, s1);
    sq(sp + 32, s0);
    swc1(F25, sp + 20);
    swc1(F24, sp + 16);
    swc1(F23, sp + 12);
    swc1(F22, sp + 8);
    swc1(F21, sp + 4);
    swc1(F20, sp);
    s4 = a0;
    mov_s(F25, F12);
    s1 = a1;
    s2 = a2;
    s0 = a3;
    swc1(F25, sp + 140);
    lwc1(F0, a0);
    swc1(F0, sp + 128);
    lwc1(F0, a0 + 4);
    swc1(F0, sp + 132);
    lwc1(F0, a0 + 8);
    swc1(F0, sp + 136);
    v0 = lui(0x96);
    lw(a0, v0 + 112);
    a1 = addiu(sp, 128);
    jal(0x3595D0u, gen::fn_sub_4C9DF0_004c9df0);
    if (v0 != 0) {
        charge(15);
        v0 = lui(0x96);
        lwc1(F23, v0 + 140);
        v0 = lui(0x96);
        lwc1(F20, v0 + 136);
        camera_get(0x3595F0u);
        lwc1(F21, v0 + 132);
        camera_get(0x3595FCu);
        lwc1(F22, v0 + 128);
        camera_get(0x359608u);
        s3 = addiu(v0, 32);
        if (s2 != 0) {
            charge(2);
            a1 = addiu(sp, 144);
            a0 = 8;
            for (;;) {  // the 64-byte plane matrix, two words a step
                charge(9);
                lw(v1, s2);
                lw(v0, s2 + 4);
                s2 = addiu(s2, 8);
                a0 = addiu(a0, -1);
                sw(a1, v1);
                sw(a1 + 4, v0);
                a1 = addiu(a1, 8);
                if (sgn(a0) <= 0) break;
                backedge();
            }
            charge(2);
        } else {
            charge(18);
            identity_matrix(144);
        }
        charge(8);
        lwc1(F2, s4);
        lwc1(F1, s4 + 4);
        lwc1(F0, s4 + 8);
        swc1(F2, sp + 192);
        swc1(F1, sp + 196);
        swc1(F0, sp + 200);
        if (s0 != 0) states_push(s4, s2, 208, 0x3596ECu, 0x35972Cu);
        charge(12);
        s4 = addiu(sp, 240);  // the Im2D vertices
        mtc1(zero, F24);
        sw(sp + 1620, zero);
        s2 = 0;
        sub_s(F1, F20, F23);
        sub_s(F0, F22, F21);
        div_s(F20, F1, F0);  // (z far - z near) / (far - near)
        const auto colour = [&](u64 last_cost) {
            for (u32 k = 0; k < 4; ++k) {
                lbu(v0, s1 + k);
                byte_to_f0();
                charge(k == 3 ? last_cost : 4);
                swc1(F0, s4 + 32 + 4 * k);
            }
        };
        for (;;) {
            charge(3);
            v0 = sltiu(s2, 20);
            if (v0 == 0) break;
            backedge();
            charge(55);
            mov_s(F12, F24);
            jal(0x35978Cu, gen::fn_cosf_0052e6d8);
            mul_s(F0, F25, F0);
            swc1(F0, sp + 1616);
            mov_s(F12, F24);
            jal(0x3597A0u, gen::fn_sinf_0052e878);
            mul_s(F0, F25, F0);
            swc1(F0, sp + 1624);
            a0 = addiu(sp, 1600);
            a1 = addiu(sp, 1616);
            a2 = addiu(sp, 144);
            jal(0x3597BCu, gen::fn_sub_4C6BE0_004c6be0);
            a0 = addiu(sp, 1584);
            a1 = addiu(sp, 1600);
            a2 = s3;
            jal(0x3597D0u, gen::fn_sub_4C6BE0_004c6be0);
            // project: x' = 640 x / z, y' = 448 y / z, screen z = near z + (far / z - near) * scale ... recipZ = 1 / z'
            lwc1(F4, sp + 1592);
            div_s(F2, F22, F4);
            sub_s(F0, F4, F21);
            mul_s(F1, F0, F20);
            mtc1(zero, F0);
            adda_s(F0, F23);
            madd_s(F3, F2, F1);
            lwc1(F0, sp + 1584);
            div_s(F1, F0, F4);
            v0 = lui(0x4420);  // 640.0
            mtc1(v0, F0);
            mul_s(F2, F0, F1);
            swc1(F2, sp + 1584);
            lwc1(F0, sp + 1588);
            div_s(F1, F0, F4);
            v0 = lui(0x43E0);  // 448.0
            mtc1(v0, F0);
            mul_s(F0, F0, F1);
            swc1(F0, sp + 1588);
            swc1(F2, s4);
            swc1(F0, s4 + 4);
            swc1(F3, s4 + 8);
            v0 = lui(0x3F80);
            mtc1(v0, F0);
            div_s(F0, F0, F3);
            swc1(F0, s4 + 24);
            colour(5);
            s4 = addiu(s4, 64);
            lwc1(F0, gp - 32240);  // the angle step
            add_s(F24, F24, F0);
            s2 = addiu(s2, 1);
        }
        charge(11);  // the closing vertex = the first
        lwc1(F0, sp + 240);
        swc1(F0, s4);
        lwc1(F0, sp + 244);
        swc1(F0, s4 + 4);
        lwc1(F0, sp + 248);
        swc1(F0, s4 + 8);
        lwc1(F0, sp + 264);
        swc1(F0, s4 + 24);
        colour(10);
        a0 = 2;  // rwPRIMTYPEPOLYLINE
        a1 = addiu(sp, 240);
        a2 = 21;
        call_pfn(0x359AA8u, kPfnIm2DRenderPrimitive);
        if (s0 != 0) states_pop(208, 0x359AECu);
    }
    charge(15);
    ld(ra, sp + 112);
    lq(s4, sp + 96);
    lq(s3, sp + 80);
    lq(s2, sp + 64);
    lq(s1, sp + 48);
    lq(s0, sp + 32);
    lwc1(F25, sp + 20);
    lwc1(F24, sp + 16);
    lwc1(F23, sp + 12);
    lwc1(F22, sp + 8);
    lwc1(F21, sp + 4);
    lwc1(F20, sp);
    sp = addiu(sp, 1632);
}

// sub_359B40(centre, colour, save) with $f12 = the radius: a wire sphere -- 9 circles stacked along y (their
// radius-scaled offsets cos / sin of the angle step gp-32240), then the matrix rotated 90 degrees about the axis
// 0x69CEC8 (sub_4C31B0) and 9 circles stacked along z; sub_359560 draws each.
void Cpu::sub_359B40() {
    enter(34);
    sp = addiu(sp, -256);
    sd(sp + 96, ra);
    sq(sp + 80, s4);
    sq(sp + 64, s3);
    sq(sp + 48, s2);
    sq(sp + 32, s1);
    sq(sp + 16, s0);
    swc1(F22, sp + 8);
    swc1(F21, sp + 4);
    swc1(F20, sp);
    s4 = a0;
    mov_s(F20, F12);
    s3 = a1;
    s2 = a2;
    v0 = lui(0x6A);
    ld(v1, v0 - 12600);  // the rotation axis 0x69CEC8
    v0 = lui(0x6A);
    lwc1(F0, v0 - 12592);
    sd(sp + 224, v1);
    swc1(F0, sp + 232);
    swc1(F20, sp + 124);
    lwc1(F0, a0);
    swc1(F0, sp + 112);
    lwc1(F0, a0 + 4);
    swc1(F0, sp + 116);
    lwc1(F0, a0 + 8);
    swc1(F0, sp + 120);
    v0 = lui(0x96);
    lw(a0, v0 + 112);
    a1 = addiu(sp, 112);
    jal(0x359BB8u, gen::fn_sub_4C9DF0_004c9df0);
    if (v0 != 0) {
        charge(2);
        if (s2 != 0) states_push(s1, s0, 128, 0x359C04u, 0x359C44u);
        charge(22);
        v0 = lui(0x3F80);
        sw(sp + 200, v0);
        sw(sp + 180, v0);
        sw(sp + 160, v0);
        mtc1(zero, F21);
        sw(sp + 176, zero);
        sw(sp + 168, zero);
        sw(sp + 164, zero);
        sw(sp + 196, zero);
        sw(sp + 192, zero);
        sw(sp + 184, zero);
        sw(sp + 216, zero);
        sw(sp + 212, zero);
        sw(sp + 208, zero);
        lw(v1, sp + 172);
        v0 = lui(0x2);
        v0 = v0 | 3;
        v0 = v1 | v0;
        sw(sp + 172, v0);
        s0 = 0;
        for (;;) {
            charge(3);
            v0 = sltiu(s0, 9);
            if (v0 == 0) break;
            backedge();
            charge(24);
            lwc1(F0, gp - 32240);
            add_s(F21, F21, F0);
            mov_s(F12, F21);
            jal(0x359CD4u, gen::fn_cosf_0052e6d8);
            mul_s(F22, F20, F0);
            mov_s(F12, F21);
            jal(0x359CE4u, gen::fn_sinf_0052e878);
            mul_s(F12, F20, F0);
            lwc1(F0, s4);
            swc1(F0, sp + 240);
            lwc1(F0, s4 + 4);
            add_s(F0, F0, F22);
            swc1(F0, sp + 244);
            lwc1(F0, s4 + 8);
            swc1(F0, sp + 248);
            a0 = addiu(sp, 240);
            a1 = s3;
            a2 = addiu(sp, 160);
            a3 = 0;
            jal(0x359D1Cu, gen::fn_sub_359560_00359560);
            s0 = addiu(s0, 1);
        }
        charge(11);
        v0 = lui(0x42B4);  // 90.0
        mtc1(v0, F12);
        a0 = addiu(sp, 160);
        a1 = addiu(sp, 224);
        a2 = 2;
        jal(0x359D48u, gen::fn_sub_4C31B0_004c31b0);  // RwMatrixRotate(m, axis, 90, rwCOMBINEPOSTCONCAT)
        mtc1(zero, F22);
        s0 = 0;
        for (;;) {
            charge(3);
            v1 = sltiu(s0, 9);
            if (v1 == 0) break;
            backedge();
            charge(24);
            lwc1(F0, gp - 32240);
            add_s(F22, F22, F0);
            mov_s(F12, F22);
            jal(0x359D6Cu, gen::fn_cosf_0052e6d8);
            mul_s(F21, F20, F0);
            mov_s(F12, F22);
            jal(0x359D7Cu, gen::fn_sinf_0052e878);
            mul_s(F12, F20, F0);
            lwc1(F0, s4);
            swc1(F0, sp + 240);
            lwc1(F0, s4 + 4);
            swc1(F0, sp + 244);
            lwc1(F0, s4 + 8);
            add_s(F0, F0, F21);
            swc1(F0, sp + 248);
            a0 = addiu(sp, 240);
            a1 = s3;
            a2 = addiu(sp, 160);
            a3 = 0;
            jal(0x359DB4u, gen::fn_sub_359560_00359560);
            s0 = addiu(s0, 1);
        }
        charge(2);
        if (s2 != 0) states_pop(128, 0x359E08u);
    }
    charge(12);
    ld(ra, sp + 96);
    lq(s4, sp + 80);
    lq(s3, sp + 64);
    lq(s2, sp + 48);
    lq(s1, sp + 32);
    lq(s0, sp + 16);
    lwc1(F22, sp + 8);
    lwc1(F21, sp + 4);
    lwc1(F20, sp);
    sp = addiu(sp, 256);
}

// sub_359E50(centre, colour, save) with $f12 = the radius, $f13 = the height: a wire cylinder centred on *centre --
// 8 rings (sub_359560) from y - h/2 in steps of h/7, 10 vertical lines and 5 pairs of cap chords (sub_359110).
void Cpu::sub_359E50() {
    enter(20);
    sp = addiu(sp, -224);
    sd(sp + 112, ra);
    sq(sp + 96, s4);
    sq(sp + 80, s3);
    sq(sp + 64, s2);
    sq(sp + 48, s1);
    sq(sp + 32, s0);
    swc1(F24, sp + 16);
    swc1(F23, sp + 12);
    swc1(F22, sp + 8);
    swc1(F21, sp + 4);
    swc1(F20, sp);
    s2 = a0;
    mov_s(F24, F12);
    mov_s(F23, F13);
    s1 = a1;
    s0 = a2;
    c_le_s(F24, F23);
    if (cop1_cond()) {  // the bounding radius: max(radius, height)
        charge(1);
        mov_s(F0, F23);
    } else {
        charge(3);
        mov_s(F0, F24);
    }
    charge(14);
    swc1(F0, sp + 140);
    lwc1(F0, s2);
    swc1(F0, sp + 128);
    lwc1(F0, s2 + 4);
    swc1(F0, sp + 132);
    lwc1(F0, s2 + 8);
    swc1(F0, sp + 136);
    v0 = lui(0x96);
    lw(a0, v0 + 112);
    a1 = addiu(sp, 128);
    jal(0x359ED8u, gen::fn_sub_4C9DF0_004c9df0);
    if (v0 != 0) {
        charge(2);
        if (s0 != 0) states_push(s4, s3, 144, 0x359F24u, 0x359F64u);
        charge(18);
        v1 = lui(0x40E0);  // 7.0
        mtc1(v1, F0);
        div_s(F21, F23, F0);
        lwc1(F0, s2);
        swc1(F0, sp + 208);
        v1 = lui(0x3F00);  // 0.5
        mtc1(v1, F0);
        mul_s(F20, F0, F23);
        lwc1(F0, s2 + 4);
        sub_s(F0, F0, F20);
        swc1(F0, sp + 212);
        lwc1(F0, s2 + 8);
        swc1(F0, sp + 216);
        s3 = 0;
        for (;;) {
            charge(3);
            v1 = sltiu(s3, 8);
            if (v1 == 0) break;
            backedge();
            charge(11);
            a0 = addiu(sp, 208);
            mov_s(F12, F24);
            a1 = s1;
            a2 = 0;
            a3 = 0;
            jal(0x359FECu, gen::fn_sub_359560_00359560);
            lwc1(F0, sp + 212);
            add_s(F0, F0, F21);
            swc1(F0, sp + 212);
            s3 = addiu(s3, 1);
        }
        charge(9);
        mtc1(zero, F22);
        s3 = 0;
        neg_s(F1, F23);
        v1 = lui(0x3F00);
        mtc1(v1, F0);
        mul_s(F21, F0, F1);  // -h/2
        for (;;) {  // the vertical lines
            charge(3);
            v1 = sltiu(s3, 10);
            if (v1 == 0) break;
            backedge();
            charge(38);
            mov_s(F12, F22);
            jal(0x35A038u, gen::fn_cosf_0052e6d8);
            mul_s(F0, F24, F0);
            swc1(F0, sp + 176);
            swc1(F21, sp + 180);
            mov_s(F12, F22);
            jal(0x35A050u, gen::fn_sinf_0052e878);
            mul_s(F4, F24, F0);
            swc1(F4, sp + 184);
            lwc1(F1, sp + 176);
            swc1(F1, sp + 188);
            swc1(F20, sp + 192);
            swc1(F4, sp + 196);
            lwc1(F0, s2);
            add_s(F3, F1, F0);
            swc1(F3, sp + 176);
            lwc1(F2, s2 + 4);
            lwc1(F0, sp + 180);
            add_s(F0, F0, F2);
            swc1(F0, sp + 180);
            lwc1(F0, s2 + 8);
            add_s(F1, F4, F0);
            swc1(F1, sp + 184);
            swc1(F3, sp + 188);
            add_s(F0, F20, F2);
            swc1(F0, sp + 192);
            swc1(F1, sp + 196);
            a0 = addiu(sp, 176);
            a1 = addiu(sp, 188);
            a2 = s1;
            a3 = 0;
            jal(0x35A0B8u, gen::fn_sub_359110_00359110);
            lwc1(F0, gp - 31720);
            add_s(F22, F22, F0);
            s3 = addiu(s3, 1);
        }
        charge(4);
        mtc1(zero, F20);
        s3 = 0;
        for (;;) {  // the cap chords, bottom and top
            charge(3);
            v1 = sltiu(s3, 5);
            if (v1 == 0) break;
            backedge();
            charge(65);
            mov_s(F12, F20);
            jal(0x35A0ECu, gen::fn_cosf_0052e6d8);
            mul_s(F0, F24, F0);
            swc1(F0, sp + 176);
            swc1(F21, sp + 180);
            mov_s(F12, F20);
            jal(0x35A104u, gen::fn_sinf_0052e878);
            mul_s(F0, F24, F0);
            swc1(F0, sp + 184);
            lwc1(F0, gp - 32184);
            add_s(F22, F0, F20);
            mov_s(F12, F22);
            jal(0x35A120u, gen::fn_cosf_0052e6d8);
            mul_s(F0, F24, F0);
            swc1(F0, sp + 188);
            swc1(F21, sp + 192);
            mov_s(F12, F22);
            jal(0x35A138u, gen::fn_sinf_0052e878);
            mul_s(F4, F24, F0);
            swc1(F4, sp + 196);
            lwc1(F0, sp + 176);
            lwc1(F3, s2);
            add_s(F0, F0, F3);
            swc1(F0, sp + 176);
            lwc1(F2, s2 + 4);
            lwc1(F0, sp + 180);
            add_s(F0, F0, F2);
            swc1(F0, sp + 180);
            lwc1(F1, s2 + 8);
            lwc1(F0, sp + 184);
            add_s(F0, F0, F1);
            swc1(F0, sp + 184);
            lwc1(F0, sp + 188);
            add_s(F0, F0, F3);
            swc1(F0, sp + 188);
            lwc1(F0, sp + 192);
            add_s(F0, F0, F2);
            swc1(F0, sp + 192);
            add_s(F0, F4, F1);
            swc1(F0, sp + 196);
            a0 = addiu(sp, 176);
            a1 = addiu(sp, 188);
            a2 = s1;
            a3 = 0;
            jal(0x35A1A8u, gen::fn_sub_359110_00359110);
            lwc1(F0, sp + 180);
            add_s(F0, F0, F23);
            swc1(F0, sp + 180);
            lwc1(F0, sp + 192);
            add_s(F0, F0, F23);
            swc1(F0, sp + 192);
            a0 = addiu(sp, 176);
            a1 = addiu(sp, 188);
            a2 = s1;
            a3 = 0;
            jal(0x35A1D8u, gen::fn_sub_359110_00359110);
            lwc1(F0, gp - 31720);
            add_s(F20, F20, F0);
            s3 = addiu(s3, 1);
        }
        charge(2);
        if (s0 != 0) states_pop(144, 0x35A234u);
    }
    charge(14);
    ld(ra, sp + 112);
    lq(s4, sp + 96);
    lq(s3, sp + 80);
    lq(s2, sp + 64);
    lq(s1, sp + 48);
    lq(s0, sp + 32);
    lwc1(F24, sp + 16);
    lwc1(F23, sp + 12);
    lwc1(F22, sp + 8);
    lwc1(F21, sp + 4);
    lwc1(F20, sp);
    sp = addiu(sp, 224);
}


// =========================================================================================================
// [field] the field's model passes (22_rendering.md section 1: "draw opaque field obj", the NPC / character passes)
// =========================================================================================================
//
// The field lights: kwlnRoot's ambient light (sub_198560), main directional light (sub_198570) and second light
// (sub_198580) and the field world (sub_198540(gp-19492)). A pass saves the lights' colours (+24, an RwRGBAReal) and
// the directional light's frame matrix (frame +16, 64 bytes) into its frame, sets the field's own (sub_19FD40 /
// sub_19FD70 colours, sub_19FDA0 matrix: RpLightSetColor = sub_4944B0, RwFrameTransform = sub_4CB7F0 replace), adds
// the second light to the world (sub_49C480), draws, and undoes it all (sub_49C3D0).

// A light's colour (+24 .. +36) into sp + slot: the getter at pc.
void Cpu::light_colour_save(u32 pc, rt::Fn getter, s32 slot) {
    jal(pc, getter);
    lwc1(F3, v0 + 24);
    lwc1(F2, v0 + 28);
    lwc1(F1, v0 + 32);
    lwc1(F0, v0 + 36);
    swc1(F3, sp + slot);
    swc1(F2, sp + slot + 4);
    swc1(F1, sp + slot + 8);
    swc1(F0, sp + slot + 12);
}
// A light's frame matrix (frame +16, 64 bytes, two words a step) into sp + slot: the getter at pc.
void Cpu::light_frame_save(u32 pc, rt::Fn getter, s32 slot) {
    jal(pc, getter);
    lw(v0, v0 + 4);
    a2 = addiu(v0, 16);
    a1 = addiu(sp, slot);
    a0 = 8;
    for (;;) {
        charge(9);
        lw(v1, a2);
        lw(v0, a2 + 4);
        a2 = addiu(a2, 8);
        a0 = addiu(a0, -1);
        sw(a1, v1);
        sw(a1 + 4, v0);
        a1 = addiu(a1, 8);
        if (sgn(a0) <= 0) break;
        backedge();
    }
}
// RpLightSetColor(getter(), base + off): the getter at pc, sub_4944B0 at pc + 0x10.
void Cpu::light_colour_set(u32 pc, rt::Fn getter, const Gpr& base, s32 off) {
    jal(pc, getter);
    a0 = v0;
    a1 = addiu(base, off);
    jal(pc + 0x10, gen::fn_sub_4944B0_004944b0);
}
// RwFrameTransform(getter()->frame, base + off, replace): the getter at pc, sub_4CB7F0 at pc + 0x14.
void Cpu::light_frame_set(u32 pc, rt::Fn getter, const Gpr& base, s32 off) {
    jal(pc, getter);
    lw(a0, v0 + 4);
    a1 = addiu(base, off);
    a2 = 0;
    jal(pc + 0x14, gen::fn_sub_4CB7F0_004cb7f0);
}
// The field's lights on: ambient = sub_19FD40(), directional = sub_19FD70(), its frame = sub_19FDA0() (9 jals from pc).
void Cpu::field_lights_on(u32 pc) {
    jal(pc, gen::fn_sub_198560_00198560);
    s0 = v0;
    jal(pc + 0x0C, gen::fn_sub_19FD40_0019fd40);
    a0 = s0;
    a1 = v0;
    jal(pc + 0x1C, gen::fn_sub_4944B0_004944b0);
    jal(pc + 0x24, gen::fn_sub_198570_00198570);
    s0 = v0;
    jal(pc + 0x30, gen::fn_sub_19FD70_0019fd70);
    a0 = s0;
    a1 = v0;
    jal(pc + 0x40, gen::fn_sub_4944B0_004944b0);
    jal(pc + 0x48, gen::fn_sub_198570_00198570);
    s0 = v0;
    jal(pc + 0x54, gen::fn_sub_19FDA0_0019fda0);
    lw(a0, s0 + 4);
    a1 = v0;
    a2 = 0;
    jal(pc + 0x68, gen::fn_sub_4CB7F0_004cb7f0);
}
// fn(field world, second light): sub_49C480 adds it, sub_49C3D0 removes it (jals at pc, + 0x0C, + 0x1C).
void Cpu::world_light(u32 pc, rt::Fn fn) {
    lw(a0, gp - 19492);
    jal(pc, gen::fn_sub_198540_00198540);
    s0 = v0;
    jal(pc + 0x0C, gen::fn_sub_198580_00198580);
    a0 = s0;
    a1 = v0;
    jal(pc + 0x1C, fn);
}
// The saved ambient / directional colours and the directional frame back (6 jals from pc).
void Cpu::field_lights_restore(u32 pc, s32 amb, s32 dir, s32 mat) {
    light_colour_set(pc, gen::fn_sub_198560_00198560, sp, amb);
    light_colour_set(pc + 0x18, gen::fn_sub_198570_00198570, sp, dir);
    light_frame_set(pc + 0x30, gen::fn_sub_198570_00198570, sp, mat);
}
// The directional light's flags byte (+2) = 3 (s0 = 3, sub_198570 at pc, then once more at pc + 0x0C).
void Cpu::dir_light_flags(u32 pc) {
    s0 = 3;
    jal(pc, gen::fn_sub_198570_00198570);
    sb(v0 + 2, s0);
    jal(pc + 0x0C, gen::fn_sub_198570_00198570);
}
// kwlnRoot's fog for a pass: FOGENABLE on ($a1 = 1 from the compare), FOGCOLOR = (a << 24 | r << 16 | g << 8 | b)
// of gp-19468 / -19480 / -19476 / -19472, FOGTYPE linear; the device pointer's address in $s0 (jalrs at pc, + 0x38,
// + 0x4C).
void Cpu::root_fog_on(u32 pc) {
    s0 = addiu(lui(0x96), 144);
    a0 = 14;
    lw(v0, s0);
    jalr(pc, v0.u());
    lbu(v0, gp - 19468);
    v1 = sll(v0, 24);
    lbu(v0, gp - 19480);
    v0 = sll(v0, 16);
    v1 = v1 | v0;
    lbu(v0, gp - 19476);
    v0 = sll(v0, 8);
    v1 = v0 | v1;
    lbu(v0, gp - 19472);
    a1 = v0 | v1;
    a0 = 15;
    lw(v0, s0);
    jalr(pc + 0x38, v0.u());
    a0 = 16;
    a1 = 1;
    lw(v0, s0);
    jalr(pc + 0x4C, v0.u());
}

// sub_19D530 "draw trans field sort" (prio 4183): when the sorted translucent queue (0x8668F0) is not empty, the
// field lights on, the second light in the world, sub_1A8B10(queue) inside a camera pass, all undone.
void Cpu::sub_19D530() {
    enter(7);
    sp = addiu(sp, -128);
    sd(sp + 16, ra);
    sq(sp, s0);
    v0 = lui(0x86);
    lw(v0, v0 + 26864);
    if (v0 == 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(26);
        light_colour_save(0x19D558u, gen::fn_sub_198560_00198560, 112);
        light_colour_save(0x19D580u, gen::fn_sub_198570_00198570, 96);
        light_frame_save(0x19D5A8u, gen::fn_sub_198570_00198570, 32);
        charge(51);
        field_lights_on(0x19D5E4u);
        dir_light_flags(0x19D658u);
        world_light(0x19D670u, gen::fn_sub_49C480_0049c480);
        camera_begin(0x19D694u, 0x19D6A0u);
        if (v0 != 0) {
            charge(9);
            a0 = addiu(lui(0x86), 26864);
            jal(0x19D6B8u, gen::fn_sub_1A8B10_001a8b10);
            camera_end(0x19D6C0u, 0x19D6CCu);
        }
        charge(36);
        world_light(0x19D6D8u, gen::fn_sub_49C3D0_0049c3d0);
        field_lights_restore(0x19D6FCu, 112, 96, 32);
        dir_light_flags(0x19D74Cu);
        v0 = 0;
    }
    charge(5);
    ld(ra, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 128);
}

// The NPC passes sub_19DB10 / sub_19DE80 (one body, 0x370 bytes apart): field-resource list 10 (sub_3B5D50) walked
// with the lights on when list 12 exists; for each resource with flag 2 whose model's lists pass the predicate
// (sub_1A7660 opaque / sub_1A76E0 translucent == 1), the model draw sub_317A20 (and its second clump +300 when flag
// 0x20000000); kwlnRoot's fog when enabled; a failed BeginUpdate asserts (k_scenedraw.c line `line`).
void Cpu::npc_pass(u32 delta, rt::Fn predicate, u32 line) {
    const auto pc = [delta](u32 x) { return x + delta; };
    enter(38);
    sp = addiu(sp, -144);
    sd(sp + 32, ra);
    sq(sp + 16, s1);
    sq(sp, s0);
    a0 = 10;
    jal(pc(0x19DB24u), gen::fn_sub_3B5D50_003b5d50);
    s1 = v0;
    a0 = 12;
    jal(pc(0x19DB34u), gen::fn_sub_3B5D50_003b5d50);
    s0 = v0;
    light_colour_save(pc(0x19DB40u), gen::fn_sub_198560_00198560, 128);
    light_colour_save(pc(0x19DB68u), gen::fn_sub_198570_00198570, 112);
    light_frame_save(pc(0x19DB90u), gen::fn_sub_198570_00198570, 48);
    charge(2);
    if (s0 == 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(45);
        world_light(pc(0x19DBE4u), gen::fn_sub_49C480_0049c480);
        field_lights_on(pc(0x19DC08u));
        camera_begin(pc(0x19DC78u), pc(0x19DC84u));
        if (v0 != 0) {
            charge(4);
            lw(v0, gp - 19484);
            a1 = 1;
            if (v0 == a1) {
                charge(27);
                root_fog_on(pc(0x19DCB4u));
            }
            for (;;) {
                charge(2);
                if (s1 == 0) break;
                backedge();
                charge(4);
                lw(v0, s1 + 40);
                v0 = v0 & 2;
                if (v0 != 0) {
                    charge(7);
                    lw(v0, s1 + 260);
                    lw(a0, v0 + 224);
                    jal(pc(0x19DD28u), predicate);
                    v1 = 1;
                    if (v0 == v1) {
                        charge(6);
                        lw(a0, s1 + 260);
                        jal(pc(0x19DD40u), gen::fn_sub_317A20_00317a20);
                        lw(a0, s1 + 300);
                        if (a0 != 0) {
                            charge(5);
                            lw(v1, s1 + 40);
                            v0 = lui(0x2000);
                            v0 = v1 & v0;
                            if (v0 != 0) {
                                charge(2);
                                jal(pc(0x19DD68u), gen::fn_sub_317A20_00317a20);
                            }
                        }
                    }
                }
                charge(1);
                lw(s1, s1 + 248);
            }
            charge(7);
            camera_end(pc(0x19DD7Cu), pc(0x19DD88u));
        } else {
            charge(5);
            a0 = addiu(lui(0x68), -30328);  // "k_scenedraw.c"
            a1 = line;
            jal(pc(0x19DDA4u), gen::fn_sub_19D3F0_0019d3f0);
        }
        charge(30);
        world_light(pc(0x19DDB0u), gen::fn_sub_49C3D0_0049c3d0);
        field_lights_restore(pc(0x19DDD4u), 128, 112, 48);
        v0 = 0;
    }
    charge(6);
    ld(ra, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 144);
}
void Cpu::sub_19DB10() { npc_pass(0, gen::fn_sub_1A7660_001a7660, 337); }
void Cpu::sub_19DE80() { npc_pass(0x370, gen::fn_sub_1A76E0_001a76e0, 408); }

// sub_19F470 "draw persona model" (prio 4168): field-resource list 2 (sub_3B5D50); for each resource with flag 2 and
// not 0x10000: its own lights (ambient +284, second +300, directional +384, the second's frame +320, the
// directional's +400), sub_319230(model +280, 3) and the model draw inside a camera pass; then the saved lights.
void Cpu::sub_19F470() {
    enter(33);
    sp = addiu(sp, -208);
    sd(sp + 16, ra);
    sq(sp, s0);
    a0 = 2;
    jal(0x19F480u, gen::fn_sub_3B5D50_003b5d50);
    s0 = v0;
    light_colour_save(0x19F48Cu, gen::fn_sub_198560_00198560, 192);
    light_colour_save(0x19F4B4u, gen::fn_sub_198570_00198570, 176);
    light_frame_save(0x19F4DCu, gen::fn_sub_198570_00198570, 112);
    charge(16);
    light_colour_save(0x19F518u, gen::fn_sub_198580_00198580, 96);
    light_frame_save(0x19F540u, gen::fn_sub_198580_00198580, 32);
    charge(2);
    for (;;) {
        charge(2);
        if (s0 == 0) break;
        backedge();
        charge(4);
        lw(v1, s0 + 40);
        v0 = v1 & 2;
        if (v0 != 0) {
            charge(4);
            v0 = lui(0x1);
            v0 = v1 & v0;
            if (v0 == 0) {
                charge(39);
                light_colour_set(0x19F5A4u, gen::fn_sub_198560_00198560, s0, 284);
                light_colour_set(0x19F5BCu, gen::fn_sub_198580_00198580, s0, 300);
                light_colour_set(0x19F5D4u, gen::fn_sub_198570_00198570, s0, 384);
                light_frame_set(0x19F5ECu, gen::fn_sub_198580_00198580, s0, 320);
                light_frame_set(0x19F608u, gen::fn_sub_198570_00198570, s0, 400);
                camera_begin(0x19F624u, 0x19F630u);
                if (v0 != 0) {
                    charge(14);
                    lw(a0, s0 + 280);
                    a1 = 3;
                    jal(0x19F648u, gen::fn_sub_319230_00319230);
                    lw(a0, s0 + 280);
                    jal(0x19F654u, gen::fn_sub_317A20_00317a20);
                    camera_end(0x19F65Cu, 0x19F668u);
                } else {
                    charge(5);
                    a0 = addiu(lui(0x68), -30328);
                    a1 = 875;
                    jal(0x19F684u, gen::fn_sub_19D3F0_0019d3f0);
                }
            }
        }
        charge(1);
        lw(s0, s0 + 248);
    }
    charge(38);
    light_colour_set(0x19F698u, gen::fn_sub_198560_00198560, sp, 192);
    light_colour_set(0x19F6B0u, gen::fn_sub_198580_00198580, sp, 96);
    light_colour_set(0x19F6C8u, gen::fn_sub_198570_00198570, sp, 176);
    light_frame_set(0x19F6E0u, gen::fn_sub_198580_00198580, sp, 32);
    light_frame_set(0x19F6FCu, gen::fn_sub_198570_00198570, sp, 112);
    v0 = 0;
    ld(ra, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 208);
}

// 0x19D780 K_SceneDraw_UpdateDrwOpcFldObjTask "draw opaque field obj" (prio 2071): with field-resource list 12: the
// lights on, list 10's opaque models (flag 2, sub_1A7660(model lists) == 0) through sub_317A20 (+ second clump),
// the lights restored; list 11's effects (sub_34FD30 / sub_34FD70(.., 3)); on the dungeon floors (*(gp-22448) >= 200)
// list 12's translucent field parts K_FldSrc_DrawFieldTrans(camera, res +352) and the NPC passes sub_19DE80 /
// sub_19DB10.
void Cpu::K_SceneDraw_UpdateDrwOpcFldObjTask() {
    enter(45);
    sp = addiu(sp, -176);
    sd(sp + 64, ra);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    s3 = a0;
    a0 = 10;
    jal(0x19D7A0u, gen::fn_sub_3B5D50_003b5d50);
    s2 = v0;
    a0 = 11;
    jal(0x19D7B0u, gen::fn_sub_3B5D50_003b5d50);
    s1 = v0;
    a0 = 12;
    jal(0x19D7C0u, gen::fn_sub_3B5D50_003b5d50);
    s0 = v0;
    light_colour_save(0x19D7CCu, gen::fn_sub_198560_00198560, 160);
    light_colour_save(0x19D7F4u, gen::fn_sub_198570_00198570, 144);
    light_frame_save(0x19D81Cu, gen::fn_sub_198570_00198570, 80);
    charge(2);
    if (s0 == 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(45);
        world_light(0x19D870u, gen::fn_sub_49C480_0049c480);
        field_lights_on(0x19D894u);
        camera_begin(0x19D904u, 0x19D910u);
        if (v0 != 0) {
            charge(2);
            for (;;) {
                charge(2);
                if (s2 == 0) break;
                backedge();
                charge(4);
                lw(v0, s2 + 40);
                v0 = v0 & 2;
                if (v0 != 0) {
                    charge(6);
                    lw(v0, s2 + 260);
                    lw(a0, v0 + 224);
                    jal(0x19D940u, gen::fn_sub_1A7660_001a7660);
                    if (v0 == 0) {
                        charge(6);
                        lw(a0, s2 + 260);
                        jal(0x19D954u, gen::fn_sub_317A20_00317a20);
                        lw(a0, s2 + 300);
                        if (a0 != 0) {
                            charge(5);
                            lw(v1, s2 + 40);
                            v0 = lui(0x2000);
                            v0 = v1 & v0;
                            if (v0 != 0) {
                                charge(2);
                                jal(0x19D97Cu, gen::fn_sub_317A20_00317a20);
                            }
                        }
                    }
                }
                charge(1);
                lw(s2, s2 + 248);
            }
            charge(7);
            camera_end(0x19D990u, 0x19D99Cu);
        } else {
            charge(5);
            a0 = addiu(lui(0x68), -30328);
            a1 = 256;
            jal(0x19D9B8u, gen::fn_sub_19D3F0_0019d3f0);
        }
        charge(31);
        world_light(0x19D9C4u, gen::fn_sub_49C3D0_0049c3d0);
        field_lights_restore(0x19D9E8u, 160, 144, 80);
        for (;;) {
            charge(2);
            if (s1 == 0) break;
            backedge();
            charge(4);
            lw(v0, s1 + 40);
            v0 = v0 & 2;
            if (v0 != 0) {
                charge(7);
                lw(a0, s1 + 260);
                jal(0x19DA50u, gen::fn_sub_34FD30_0034fd30);
                lw(a0, s1 + 260);
                a1 = 3;
                jal(0x19DA60u, gen::fn_sub_34FD70_0034fd70);
            }
            charge(1);
            lw(s1, s1 + 248);
        }
        charge(5);
        lw(v0, gp - 22448);
        lw(v0, v0);
        v0 = slti(v0, 200);
        if (v0 == 0) {
            charge(6);
            a0 = 12;
            jal(0x19DA8Cu, gen::fn_sub_3B5D50_003b5d50);
            s0 = v0;
            for (;;) {
                charge(2);
                if (s0 == 0) break;
                backedge();
                charge(4);
                lw(v0, s0 + 40);
                v0 = v0 & 2;
                if (v0 != 0) {
                    charge(6);
                    camera_get(0x19DAB0u);
                    a0 = v0;
                    lw(a1, s0 + 352);
                    jal(0x19DAC0u, gen::fn_K_FldSrc_DrawFieldTrans_001b4720);
                }
                charge(1);
                lw(s0, s0 + 248);
            }
            charge(6);
            a0 = s3;
            jal(0x19DAD8u, gen::fn_sub_19DE80_0019de80);
            a0 = s3;
            jal(0x19DAE4u, gen::fn_sub_19DB10_0019db10);
        }
        charge(1);
        v0 = 0;
    }
    charge(8);
    ld(ra, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 176);
}

// sub_188250: the HUD calendar task (work +60: +0 state, +4 month, +8 day, +12 time, +16 the sprite file of
// 0x5E4190): 0 add the sprite file, 1 wait until it is ready, 2 (each frame) the current month / day / time and,
// inside a camera pass with fog off (saved / restored), the calendar draw sub_187EC0(task, month, day, time).
void Cpu::sub_188250() {
    enter(11);
    sp = addiu(sp, -80);
    sd(sp + 48, ra);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    s1 = a0;
    lw(s0, a0 + 60);
    lw(v1, s0);
    v0 = 2;
    if (v1 == v0) {
        charge(18);
        sw(gp - 19704, zero);
        jal(0x1882E8u, gen::fn_clndGetCurrentMonth_0017d920);
        sw(s0 + 4, v0);
        jal(0x1882F4u, gen::fn_clndGetCurrentDay_0017da40);
        sw(s0 + 8, v0);
        jal(0x188300u, gen::fn_datGetTime_0016ef30);
        v0 = v0 & 0xFF;
        sw(s0 + 12, v0);
        camera_begin(0x188310u, 0x18831Cu);
        if (v0 == 0) {
            charge(3);
            v0 = 0;
            charge(7);
            ld(ra, sp + 48);
            lq(s2, sp + 32);
            lq(s1, sp + 16);
            lq(s0, sp);
            sp = addiu(sp, 80);
            return;
        }
        charge(29);
        a0 = 14;
        a1 = addiu(sp, 76);
        call_pfn(0x188348u, kPfnRenderStateGet);
        s2 = addiu(lui(0x96), 144);
        a0 = 14;
        a1 = 0;
        lw(v0, s2);
        jalr(0x188364u, v0.u());
        a0 = s1;
        lw(a1, s0 + 4);
        lw(a2, s0 + 8);
        lw(a3, s0 + 12);
        jal(0x18837Cu, gen::fn_sub_187EC0_00187ec0);
        a0 = 14;
        lw(a1, sp + 76);
        lw(v0, s2);
        jalr(0x188390u, v0.u());
        camera_end(0x188398u, 0x1883A4u);
    } else {
        charge(3);
        v0 = 1;
        if (v1 == v0) {
            charge(6);
            lw(a0, s0 + 16);
            jal(0x1882C0u, gen::fn_sprFileIsReady_00111f30);
            v1 = 1;
            if (v0 == v1) {
                charge(4);
                v0 = 2;
                sw(s0, v0);
            }
        } else {
            charge(2);
            if (v1 == 0) {
                charge(9);
                a0 = addiu(lui(0x5E), 16784);  // the calendar sprite file 0x5E4190
                jal(0x1882A0u, gen::fn_sprAddFile_00112370);
                sw(s0 + 16, v0);
                v0 = 1;
                sw(s0, v0);
            } else {
                charge(2);
            }
        }
    }
    charge(1);
    v0 = 0;
    charge(7);
    ld(ra, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 80);
}

// sub_41BAF0: an event 3-D pass over the task's object list (task +60 -> +0 -> +12, linked by +16; object +20 the
// record: s16 +0 flags (0x10 and 0x1), s8 +2 the kind: 3 model (sub_317A20), 6 Im3D model (sub_20AC90 + sub_20B250),
// 2 line object (sub_41BF80), +8 the data), with the camera's far plane set to 30.0 for the pass and restored
// (sub_1A4600 reads it, sub_1A4580 sets it) and the kwln pass flags.
void Cpu::sub_41BAF0() {
    enter(26);
    sp = addiu(sp, -64);
    sd(sp + 48, ra);
    sq(sp + 32, s1);
    sq(sp + 16, s0);
    swc1(F20, sp);
    s0 = a0;
    camera_get(0x41BB08u);
    a0 = v0;
    jal(0x41BB14u, gen::fn_sub_1A4600_001a4600);
    mov_s(F20, F0);
    camera_get(0x41BB20u);
    v1 = lui(0x41F0);  // 30.0
    mtc1(v1, F12);
    a0 = v0;
    jal(0x41BB34u, gen::fn_sub_1A4580_001a4580);
    camera_begin(0x41BB3Cu, 0x41BB48u);
    if (v0 == 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(14);
        v0 = lui(0x4000);
        a0 = v0 | 2;
        a1 = 0;
        jal(0x41BB70u, gen::fn_kwlnSetFlags_00198610);
        a0 = 2;
        a1 = 1;
        jal(0x41BB80u, gen::fn_kwlnSetFlags_00198610);
        lw(v0, s0 + 60);
        lw(v0, v0);
        lw(s1, v0 + 12);
        for (;;) {
            charge(2);
            if (s1 == 0) break;
            backedge();
            charge(5);
            lw(s0, s1 + 20);
            lh(v1, s0);
            v0 = v1 & 0x10;
            if (v0 != 0) {
                charge(3);
                v0 = v1 & 1;
                if (v0 != 0) {
                    charge(4);
                    lb(v1, s0 + 2);
                    v0 = 2;
                    if (v1 == v0) {
                        charge(3);
                        lw(a0, s0 + 8);
                        jal(0x41BC24u, gen::fn_sub_41BF80_0041bf80);
                    } else {
                        charge(3);
                        v0 = 6;
                        if (v1 == v0) {
                            charge(8);
                            lw(a0, s0 + 8);
                            jal(0x41BC04u, gen::fn_sub_20AC90_0020ac90);
                            lw(a0, s0 + 8);
                            jal(0x41BC10u, gen::fn_sub_20B250_0020b250);
                        } else {
                            charge(3);
                            v0 = 3;
                            if (v1 == v0) {
                                charge(5);
                                lw(a0, s0 + 8);
                                jal(0x41BBF0u, gen::fn_sub_317A20_00317a20);
                            } else {
                                charge(2);
                            }
                        }
                    }
                }
            }
            charge(1);
            lw(s1, s1 + 16);
        }
        charge(12);
        camera_get(0x41BC38u);
        a0 = v0;
        mov_s(F12, F20);
        jal(0x41BC48u, gen::fn_sub_1A4580_001a4580);
        camera_end(0x41BC50u, 0x41BC5Cu);
        v0 = 0;
    }
    charge(7);
    ld(ra, sp + 48);
    lq(s1, sp + 32);
    lq(s0, sp + 16);
    lwc1(F20, sp);
    sp = addiu(sp, 64);
}


// =========================================================================================================
// [model] the model draw (22_rendering.md section 2.2; 18 callers, every field / battle model every frame)
// =========================================================================================================

// A colour byte in $v0 as a float: the unsigned-convert idiom (the negative branch never runs for a byte); the
// integer goes through `ftmp`, the result lands in `fdst`.
void Cpu::u8_to_float(unsigned ftmp, unsigned fdst) {
    if (sgn(v0) < 0) {
        charge(7);
        v1 = srl(v0, 1);
        v0 = v0 & 1;
        v1 = v1 | v0;
        mtc1(v1, ftmp);
        cvt_s_w(fdst, ftmp);
        add_s(fdst, fdst, fdst);
    } else {
        charge(5);
        mtc1(v0, ftmp);
        cvt_s_w(fdst, ftmp);
    }
}

// sub_317A20(model): the model draw. The model record (0x420 bytes): +128 position, +208 RGBA colour, +212 kind,
// +216 flags (0x1000 visible, 0x4 skip the pre-update sub_317730, 0x2 hidden, 0x8 / 0x10 / 0x100 Z test / Z write /
// fog, 0x40 cull mode 3 (else 2), 0x20 alpha-faded, 0x18 the list passes with Z states, 0x80 no colour override,
// 0x8000 the shadow is suppressed, 0x1 the outline), +220 the clump, +224 the atomic lists, +228 / +232 the whole
// clump's sky states, +236 / +860 the material animation (sub_313CA0), +284 four attachments of 156 bytes (their
// +0 holds a sub-model: +4 colour, +24 / +36 effect lists), +948 five 12-byte child slots (+952 the child model),
// +1012 the shadow (+1048 its kind, +1050 .. +1053 its colour), +864 / +860 the outline data.
// Visible and shown: Z test / Z write / fog / cull states, the material animation, the per-atomic colour pass
// (sub_4916D0 with sub_315F50), then the whole clump (sub_1A88E0 with its sky states) or the list passes
// (sub_1A7B50 / sub_1A7FC0 / sub_1A8140 with or without Z states) or, when alpha-faded, sub_315C20; the shadow with
// the model x shadow colour; the attachments' colours and effects; the visible children drawn recursively with the
// model's colour and fade; finally the outline passes and the type-8 shadow finish sub_321FE0.
void Cpu::sub_317A20() {
    enter(11);
    sp = addiu(sp, -112);
    sd(sp + 64, ra);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    s1 = a0;
    lhu(a1, a0 + 216);
    v1 = a1 & 0x1000;
    if (v1 == 0) {
        charge(8);
        ld(ra, sp + 64);
        lq(s3, sp + 48);
        lq(s2, sp + 32);
        lq(s1, sp + 16);
        lq(s0, sp);
        sp = addiu(sp, 112);
        return;
    }
    charge(4);
    s0 = 0;  // 1 once something was drawn (the type-8 shadow finish needs it)
    v1 = a1 & 0x4;
    if (v1 == 0) {
        charge(2);
        jal(0x317A5Cu, gen::fn_sub_317730_00317730);
    }
    charge(4);
    lhu(a0, s1 + 216);
    v1 = a0 & 0x2;
    bool shown = false;
    if (v1 == 0) {
        charge(3);
        lbu(v1, s1 + 211);
        shown = sgn(v1) > 0;
    }
    if (shown) {
        charge(26);
        v0 = a0 & 0x8;
        a1 = sltu(zero, v0);
        s2 = addiu(lui(0x96), 144);
        a0 = 6;  // Z test
        lw(v0, s2);
        jalr(0x317A98u, v0.u());
        lhu(v0, s1 + 216);
        v0 = v0 & 0x10;
        a1 = sltu(zero, v0);
        a0 = 8;  // Z write
        lw(v0, s2);
        jalr(0x317AB4u, v0.u());
        lhu(v0, s1 + 216);
        v0 = v0 & 0x100;
        a1 = sltu(zero, v0);
        a0 = 14;  // fog
        lw(v0, s2);
        jalr(0x317AD0u, v0.u());
        lhu(v0, s1 + 216);
        v0 = v0 & 0x40;
        if (v0 == 0) {
            charge(1);
            a1 = 2;
        } else {
            charge(3);
            a1 = 3;
        }
        charge(21);
        a0 = 20;  // rwRENDERSTATECULLMODE
        lw(v0, s2);
        jalr(0x317B00u, v0.u());
        a0 = addiu(s1, 860);
        a1 = addiu(s1, 236);
        jal(0x317B10u, gen::fn_sub_313CA0_00313ca0);
        lw(a0, s1 + 220);
        v0 = addiu(s1, 208);
        sw(sp + 88, v0);  // {&colour, u16 0}: the per-atomic colour callback's data
        sh(sp + 92, zero);
        a1 = addiu(lui(0x31), 24400);  // sub_315F50
        a2 = addiu(sp, 88);
        jal(0x317B34u, gen::fn_sub_4916D0_004916d0);
        lhu(a0, s1 + 216);
        v0 = a0 & 0x20;
        bool faded = false;
        if (v0 != 0) {
            charge(4);
            lbu(v1, s1 + 211);
            v0 = 255;
            faded = v1 != v0;
        }
        if (faded) {
            charge(3);
            a0 = s1;
            jal(0x317C20u, gen::fn_sub_315C20_00315c20);
        } else {
            charge(3);
            lw(s2, s1 + 224);
            if (s2 == 0) {
                charge(13);
                a0 = 2;
                lw(a1, s1 + 228);
                jal(0x317B70u, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = 3;
                lw(a1, s1 + 232);
                jal(0x317B80u, gen::fn_RpSkyRenderStateSet_004d7f60);
                lw(a0, s1 + 220);
                jal(0x317B8Cu, gen::fn_sub_1A88E0_001a88e0);
            } else {
                charge(4);
                v1 = a0 & 0x18;
                v0 = 24;
                charge(14);
                const u32 mode = v1 == v0 ? 1u : 0u;  // Z test and Z write: the passes set their Z states
                const u32 base = mode ? 0x317BB4u : 0x317BECu;
                a0 = s2;
                a1 = mode;
                jal(base, gen::fn_sub_1A7B50_001a7b50);
                a0 = s2;
                a1 = mode;
                jal(base + 0x10, gen::fn_sub_1A7FC0_001a7fc0);
                a0 = s2;
                a1 = mode;
                jal(base + 0x20, gen::fn_sub_1A8140_001a8140);
            }
        }
        // the shadow (+1012)
        charge(3);
        lw(v1, s1 + 1012);
        if (v1 != 0) {
            charge(5);
            s2 = 1;
            lhu(v1, s1 + 216);
            v1 = v1 & 0x8000;
            if (v1 != 0) {  // suppressed unless some atomic is visible (sub_316360 clears the word)
                charge(10);
                lw(a0, s1 + 220);
                sw(sp + 104, s2);
                a1 = addiu(lui(0x31), 25440);  // sub_316360
                a2 = addiu(sp, 104);
                jal(0x317C5Cu, gen::fn_sub_4916D0_004916d0);
                lw(v1, sp + 104);
                if (v1 != 0) {
                    charge(1);
                    s2 = 0;
                }
            }
            charge(2);
            if (s2 != 0) {
                charge(4);
                lhu(v0, s1 + 216);
                v0 = v0 & 0x80;
                if (v0 == 0) {
                    // shadow colour = model colour x shadow colour (each / 255, gp-32232), rounded to bytes
                    charge(3);
                    lbu(v0, s1 + 208);
                    u8_to_float(F0, F1);
                    charge(5);
                    lwc1(F0, gp - 32232);
                    mul_s(F2, F0, F1);
                    lbu(v0, s1 + 209);
                    u8_to_float(F0, F1);
                    charge(5);
                    lwc1(F0, gp - 32232);
                    mul_s(F1, F0, F1);
                    lbu(v0, s1 + 210);
                    u8_to_float(F0, F3);
                    charge(5);
                    lwc1(F0, gp - 32232);
                    mul_s(F0, F0, F3);
                    lbu(v0, s1 + 211);
                    u8_to_float(F3, F4);
                    charge(5);
                    lwc1(F3, gp - 32232);
                    mul_s(F5, F3, F4);
                    lbu(v0, s1 + 1050);
                    u8_to_float(F3, F4);
                    charge(6);
                    lwc1(F3, gp - 32232);
                    mul_s(F3, F3, F4);
                    mul_s(F2, F2, F3);
                    lbu(v0, s1 + 1051);
                    u8_to_float(F3, F4);
                    charge(6);
                    lwc1(F3, gp - 32232);
                    mul_s(F3, F3, F4);
                    mul_s(F1, F1, F3);
                    lbu(v0, s1 + 1052);
                    u8_to_float(F3, F4);
                    charge(6);
                    lwc1(F3, gp - 32232);
                    mul_s(F3, F3, F4);
                    mul_s(F0, F0, F3);
                    lbu(v0, s1 + 1053);
                    u8_to_float(F3, F4);
                    charge(40);
                    lwc1(F3, gp - 32232);
                    mul_s(F3, F3, F4);
                    mul_s(F6, F5, F3);
                    v0 = lui(0x437F);  // 255.0
                    mtc1(v0, F5);
                    v0 = lui(0x3F00);  // 0.5
                    mtc1(v0, F4);
                    mtc1(zero, F3);
                    const unsigned src[4] = {F2, F1, F0, F6};
                    const unsigned dst[4] = {F2, F1, F0, F0};
                    for (u32 k = 0; k < 4; ++k) {  // byte = (int)(0 + 0.5 + 255 * c)
                        adda_s(F3, F4);
                        madd_s(dst[k], F5, src[k]);
                        cvt_w_s(dst[k], dst[k]);
                        mfc1(v0, dst[k]);
                        sb(sp + 108 + k, v0);
                    }
                    lw(a0, s1 + 1012);
                    a1 = addiu(sp, 108);
                    jal(0x317F3Cu, gen::fn_sub_31DD40_0031dd40);
                    lbu(v1, sp + 111);
                    if (sgn(v1) > 0) {
                        charge(6);
                        lw(a0, s1 + 1012);
                        lhu(a1, s1 + 1048);
                        jal(0x317F58u, gen::fn_sub_31DC80_0031dc80);
                    }
                } else {
                    charge(4);
                    lw(a0, s1 + 1012);
                    lhu(a1, s1 + 1048);
                    jal(0x317F70u, gen::fn_sub_31DC80_0031dc80);
                }
                charge(1);
                s0 = 1;
            }
        }
        // the four attachments (+284, 156 bytes each)
        charge(3);
        s2 = 0;
        for (;;) {
            charge(4);
            v1 = s2 & 0xFFFF;
            v1 = slti(v1, 4);
            if (v1 == 0) break;
            backedge();
            charge(11);
            a0 = s2 & 0xFFFF;
            v1 = sll(a0, 2);
            v1 = addu(v1, a0);
            v1 = sll(v1, 3);
            v1 = subu(v1, a0);
            v1 = sll(v1, 2);
            v1 = addu(s1, v1);  // model + 156 * i
            t0 = addiu(v1, 284);
            lw(v1, v1 + 284);
            if (v1 != 0) {
                charge(10);
                lwc1(F2, s1 + 128);
                lwc1(F1, s1 + 132);
                lwc1(F0, s1 + 136);
                swc1(F2, v1 + 8);
                swc1(F1, v1 + 12);
                swc1(F0, v1 + 16);
                lhu(v1, s1 + 216);
                v1 = v1 & 0x80;
                if (v1 == 0) {
                    charge(9);
                    lw(a3, t0);
                    lbu(a2, s1 + 208);
                    lbu(a1, s1 + 209);
                    lbu(a0, s1 + 210);
                    lbu(v1, s1 + 211);
                    sb(a3 + 4, a2);
                    sb(a3 + 5, a1);
                    sb(a3 + 6, a0);
                    sb(a3 + 7, v1);
                }
                charge(5);
                lhu(s3, s1 + 1048);
                lw(s0, t0);
                lw(a0, s0 + 24);
                if (a0 != 0) {
                    charge(7);
                    a1 = addiu(s0, 4);
                    jal(0x318018u, gen::fn_sub_31DD40_0031dd40);
                    lw(a0, s0 + 24);
                    a1 = s3;
                    jal(0x318028u, gen::fn_sub_31DC80_0031dc80);
                }
                charge(3);
                lw(a0, s0 + 36);
                if (a0 != 0) {
                    charge(6);
                    a1 = addiu(s0, 4);
                    jal(0x318040u, gen::fn_sub_31E240_0031e240);
                    lw(a0, s0 + 36);
                    jal(0x31804Cu, gen::fn_sub_31E1E0_0031e1e0);
                }
                charge(1);
                s0 = 1;
            }
            charge(2);
            v1 = addiu(s2, 1);
            s2 = v1 & 0xFFFF;
        }
        // the five children (+948, 12 bytes each: +0 bit 0 present, +4 the model)
        charge(3);
        s3 = 0;
        for (;;) {
            charge(4);
            v1 = s3 & 0xFFFF;
            v1 = slti(v1, 5);
            if (v1 == 0) break;
            backedge();
            charge(9);
            a0 = s3 & 0xFFFF;
            v1 = sll(a0, 1);
            v1 = addu(v1, a0);
            v1 = sll(v1, 2);
            a0 = addu(s1, v1);
            lbu(v1, a0 + 948);
            v1 = v1 & 1;
            if (v1 != 0) {
                charge(4);
                s2 = addiu(a0, 952);
                lw(v1, a0 + 952);
                if (v1 != 0) {
                    charge(6);
                    a0 = s1;
                    a1 = s3;
                    jal(0x3180B8u, gen::fn_sub_319770_00319770);
                    if (v0 != 0) {
                        charge(12);
                        lw(v0, s2);
                        lw(a0, v0 + 220);
                        v0 = 1;
                        sw(sp + 100, v0);
                        a1 = addiu(lui(0x31), 25440);  // sub_316360: clears the word when an atomic is visible
                        a2 = addiu(sp, 100);
                        jal(0x3180E4u, gen::fn_sub_4916D0_004916d0);
                        lw(v1, sp + 100);
                        if (v1 == 0) {
                            charge(8);
                            lw(a0, s2);
                            a1 = addiu(s1, 208);
                            jal(0x318100u, gen::fn_sub_318AD0_00318ad0);  // the child takes the model's colour
                            lhu(v0, s1 + 216);
                            v0 = v0 & 0x20;
                            if (v0 == 0) {
                                charge(6);
                                lw(v1, s2);
                                lhu(v0, v1 + 216);
                                v0 = v0 & 0xFFDF;
                                sh(v1 + 216, v0);
                            } else {
                                charge(4);
                                lw(v1, s2);
                                lhu(v0, v1 + 216);
                                v0 = v0 | 0x20;
                                sh(v1 + 216, v0);
                            }
                            charge(3);
                            lw(a0, s2);
                            jal(0x318144u, gen::fn_sub_317A20_00317a20);
                        }
                    }
                }
            }
            charge(2);
            v1 = addiu(s3, 1);
            s3 = v1 & 0xFFFF;
        }
    }
    // the outline passes
    charge(4);
    lhu(a0, s1 + 216);
    v1 = a0 & 0x2;
    if (v1 == 0) {
        charge(3);
        v1 = a0 & 0x1;
        if (v1 != 0) {
            charge(3);
            a0 = s1;
            jal(0x318184u, gen::fn_sub_3151D0_003151d0);
        }
        charge(4);
        lhu(a0, s1 + 212);
        v1 = 5;
        bool outline = false;
        if (a0 != v1) {
            charge(4);
            lhu(v1, s1 + 216);
            v1 = v1 & 0x8000;
            if (v1 == 0) {
                charge(3);
                lbu(v1, s1 + 211);
                outline = sgn(v1) > 0;
            }
        }
        if (outline) {
            charge(3);
            lw(v1, s1 + 860);
            if (v1 != 0) {
                charge(3);
                lw(a0, s1 + 864);
                if (a0 != 0) {
                    charge(5);
                    mtc1(zero, F12);
                    v0 = lui(0x3F80);
                    mtc1(v0, F13);
                    jal(0x3181DCu, gen::fn_sub_320640_00320640);
                }
            }
            charge(3);
            s2 = 0;
            for (;;) {
                charge(4);
                v1 = s2 & 0xFFFF;
                v1 = slti(v1, 5);
                if (v1 == 0) break;
                backedge();
                charge(9);
                a0 = s2 & 0xFFFF;
                v1 = sll(a0, 1);
                v1 = addu(v1, a0);
                v1 = sll(v1, 2);
                a0 = addu(s1, v1);
                lbu(v1, a0 + 948);
                v1 = v1 & 1;
                if (v1 != 0) {
                    charge(4);
                    s3 = addiu(a0, 952);
                    lw(v1, a0 + 952);
                    if (v1 != 0) {
                        charge(6);
                        a0 = s1;
                        a1 = s2;
                        jal(0x31822Cu, gen::fn_sub_319770_00319770);
                        if (v0 != 0) {
                            charge(5);
                            lw(v1, s3);
                            a0 = addiu(v1, 860);
                            lw(v1, v1 + 860);
                            if (v1 != 0) {
                                charge(3);
                                lw(a0, a0 + 4);
                                if (a0 != 0) {
                                    charge(5);
                                    mtc1(zero, F12);
                                    v0 = lui(0x3F80);
                                    mtc1(v0, F13);
                                    jal(0x318268u, gen::fn_sub_320640_00320640);
                                }
                            }
                        }
                    }
                }
                charge(2);
                v1 = addiu(s2, 1);
                s2 = v1 & 0xFFFF;
            }
        }
    }
    charge(3);
    v1 = 1;
    if (s0 == v1) {
        charge(4);
        lhu(v1, s1 + 1048);
        a0 = 8;
        if (v1 == a0) {
            charge(2);
            jal(0x3182A4u, gen::fn_sub_321FE0_00321fe0);
        }
    }
    charge(8);
    ld(ra, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 112);
}


// =========================================================================================================
// [fldsrc] the field world passes (22_rendering.md section 2.3)
// =========================================================================================================
//
// The field resource ($s1): +0 flags (bit 0 the world is drawn, 0x80000000 / 0x40000000 = use sub-world +12 / +16
// instead of +8), +20 the count of extra parts, +152 their atomic lists (or +24.. their clumps). With bit 0 the main
// camera ($s2) moves from the root world into the field's world for the pass (sub_49C1B0 remove, sub_49C160 add) and
// kwlnRoot's ambient and directional lights move with it.

// The save of the lights, the field's own on, the directional flags (k_fldsrc.c's shared prologue; pcs from `b`).
void Cpu::fldsrc_lights_prologue(u32 b) {
    light_colour_save(b, gen::fn_sub_198560_00198560, 144);
    light_colour_save(b + 0x28, gen::fn_sub_198570_00198570, 128);
    light_frame_save(b + 0x50, gen::fn_sub_198570_00198570, 64);
}
// The shared epilogue: the saved lights back, the directional flags, kwlnSetFlags(3, 0).
void Cpu::fldsrc_lights_epilogue(u32 b) {
    field_lights_restore(b, 144, 128, 64);
    dir_light_flags(b + 0x50);
    a0 = s0;
    a1 = 0;
    jal(b + 0x6C, gen::fn_kwlnSetFlags_00198610);
}
// fn(world at res + off, light) for the ambient then the directional light (jals at pc, + 0x10, + 0x18, + 0x28).
void Cpu::world_pair_lights(u32 pc, s32 off, rt::Fn fn) {
    jal(pc, gen::fn_sub_198560_00198560);
    lw(a0, s1 + off);
    a1 = v0;
    jal(pc + 0x10, fn);
    jal(pc + 0x18, gen::fn_sub_198570_00198570);
    lw(a0, s1 + off);
    a1 = v0;
    jal(pc + 0x28, fn);
}
// fn(the root world, light) for the ambient then the directional light (jals at pc .. pc + 0x44).
void Cpu::root_world_lights(u32 pc, rt::Fn fn) {
    lw(a0, gp - 19492);
    jal(pc, gen::fn_sub_198540_00198540);
    s0 = v0;
    jal(pc + 0x0C, gen::fn_sub_198560_00198560);
    a0 = s0;
    a1 = v0;
    jal(pc + 0x1C, fn);
    lw(a0, gp - 19492);
    jal(pc + 0x28, gen::fn_sub_198540_00198540);
    s0 = v0;
    jal(pc + 0x34, gen::fn_sub_198570_00198570);
    a0 = s0;
    a1 = v0;
    jal(pc + 0x44, fn);
}
// The opened pass: kwln flags (0x40000002 off, 2 on), Z test and Z write on (the device pointer in $s0).
void Cpu::fldsrc_pass_states(u32 pc) {
    v0 = lui(0x4000);
    a0 = v0 | 2;
    a1 = 0;
    jal(pc, gen::fn_kwlnSetFlags_00198610);
    a0 = 2;
    a1 = 1;
    jal(pc + 0x10, gen::fn_kwlnSetFlags_00198610);
    s0 = addiu(lui(0x96), 144);
    a0 = 6;
    a1 = 1;
    lw(v0, s0);
    jalr(pc + 0x2C, v0.u());
    a0 = 8;
    a1 = 1;
    lw(v0, s0);
    jalr(pc + 0x40, v0.u());
}
// Which world the resource's flags pick ($v1 = flags; the compiler's `lui 0x8000` / `lui 0x4000` tests in $v0): 12
// (sub-world +12), 16 (+16) or 8 (the main one). Charges the second test (4) when the first fails.
s32 Cpu::fldsrc_world_slot() {
    v0 = lui(0x8000);
    v0 = v1 & v0;
    if (v0 != 0) return 12;
    charge(4);
    v0 = lui(0x4000);
    v0 = v1 & v0;
    return v0 != 0 ? 16 : 8;
}

// 0x1B3E50 K_FldSrc_DrawFieldOpaque(camera, res): the opaque field world. Alpha ref 68, blend 0x717FB, the field
// lights; bit 0: the camera into the field world and the lights out of the root world into it; inside the camera
// pass (Z on, kwlnRoot fog when enabled) RpWorldRender of the chosen world; else the res's atomics (+12 lists through
// sub_1A7B50(.., 1), or the clumps +8 / +16 through sub_1A88E0); the extra parts (+152 lists, or +24.. clumps);
// everything moved back, the lights restored.
void Cpu::K_FldSrc_DrawFieldOpaque() {
    enter(42);
    sp = addiu(sp, -160);
    sd(sp + 48, ra);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    s2 = a0;
    s1 = a1;
    sky_states(0x1B3E74u, 68, 0x17FB);
    fldsrc_lights_prologue(0x1B3E90u);
    charge(38);
    field_lights_on(0x1B3F1Cu);
    dir_light_flags(0x1B3F90u);
    lw(v0, s1);
    v0 = v0 & 1;
    if (v0 != 0) {
        charge(12);
        lw(a0, gp - 19492);
        jal(0x1B3FB8u, gen::fn_sub_198540_00198540);
        a0 = v0;
        a1 = s2;
        jal(0x1B3FC8u, gen::fn_sub_49C1B0_0049c1b0);  // the camera out of the root world
        lw(v1, s1);
        const s32 slot = fldsrc_world_slot();
        if (slot == 12) {
            charge(6);
            lw(a0, s1 + 12);
            a1 = s2;
            jal(0x1B3FECu, gen::fn_sub_49C160_0049c160);
        } else if (slot == 16) {
            charge(3);
            lw(a0, s1 + 16);
            if (a0 != 0) {
                charge(5);
                a1 = s2;
                jal(0x1B401Cu, gen::fn_sub_49C160_0049c160);
            }
        } else {
            charge(4);
            lw(a0, s1 + 8);
            a1 = s2;
            jal(0x1B4034u, gen::fn_sub_49C160_0049c160);
        }
        charge(25);
        root_world_lights(0x1B4040u, gen::fn_sub_49C480_0049c480);
        lw(v1, s1);
        const s32 lslot = fldsrc_world_slot();
        charge(14);
        world_pair_lights(lslot == 12 ? 0x1B40A0u : lslot == 16 ? 0x1B40E8u : 0x1B4120u, lslot, gen::fn_sub_49C3D0_0049c3d0);
    } else {
        charge(10);
        world_light(0x1B415Cu, gen::fn_sub_49C480_0049c480);
    }
    charge(4);
    lw(v0, s1);
    v0 = v0 & 1;
    if (v0 != 0) {
        charge(3);
        lw(v0, s1 + 8);
        if (v0 != 0) {
            charge(5);
            a0 = s2;
            jal(0x1B41A0u, gen::fn_RwCameraBeginUpdate_004c9d10);
            if (v0 != 0) {
                charge(25);
                fldsrc_pass_states(0x1B41BCu);
                lw(v0, gp - 19484);
                a1 = 1;
                if (v0 == a1) {
                    charge(23);
                    root_fog_on(0x1B421Cu);
                }
                charge(5);
                lw(v1, s1);
                const s32 slot = fldsrc_world_slot();
                charge(5);
                lw(a0, s1 + slot);
                jal(slot == 12 ? 0x1B4288u : slot == 16 ? 0x1B42ACu : 0x1B42C0u, gen::fn_RpWorldRender_0049a250);
            } else {
                charge(7);
                a0 = addiu(lui(0x68), -29192);  // "k_fldsrc.c"
                a1 = 1923;
                jal(0x1B42DCu, gen::fn_sub_19D3F0_0019d3f0);
            }
        }
    } else {
        charge(5);
        a0 = s2;
        jal(0x1B42F0u, gen::fn_RwCameraBeginUpdate_004c9d10);
        if (v0 != 0) {
            charge(25);
            fldsrc_pass_states(0x1B430Cu);
            lw(v0, gp - 19484);
            a1 = 1;
            if (v0 == a1) {
                charge(23);
                root_fog_on(0x1B436Cu);
            }
            charge(5);
            lw(v1, s1);
            v0 = lui(0x8000);
            v0 = v1 & v0;
            if (v0 != 0) {
                charge(3);
                lw(a0, s1 + 12);
                if (a0 != 0) {
                    charge(5);
                    a1 = 1;
                    jal(0x1B43E4u, gen::fn_sub_1A7B50_001a7b50);
                } else {
                    charge(5);
                    lw(a0, s1 + 8);
                    jal(0x1B43F8u, gen::fn_sub_1A88E0_001a88e0);
                }
            } else {
                charge(4);
                v0 = lui(0x4000);
                v0 = v1 & v0;
                if (v0 != 0) {
                    charge(5);
                    lw(a0, s1 + 16);
                    jal(0x1B441Cu, gen::fn_sub_1A88E0_001a88e0);
                }
            }
        } else {
            charge(5);
            a0 = addiu(lui(0x68), -29192);
            a1 = 1956;
            jal(0x1B4438u, gen::fn_sub_19D3F0_0019d3f0);
        }
    }
    charge(5);
    lw(v1, s1);
    v0 = lui(0xC000);
    v0 = v1 & v0;
    if (v0 == 0) {  // the extra parts
        charge(3);
        s0 = 0;
        for (;;) {
            charge(4);
            lw(v0, s1 + 20);
            v0 = sltu(s0, v0);
            if (v0 == 0) break;
            backedge();
            charge(5);
            v0 = sll(s0, 2);
            v0 = addu(s1, v0);
            lw(a0, v0 + 152);
            if (a0 != 0) {
                charge(5);
                a1 = 1;
                jal(0x1B4478u, gen::fn_sub_1A7B50_001a7b50);
            } else {
                charge(3);
                lw(a0, v0 + 24);
                jal(0x1B448Cu, gen::fn_sub_1A88E0_001a88e0);
            }
            charge(1);
            s0 = addiu(s0, 1);
        }
    }
    charge(7);
    a0 = s2;
    jal(0x1B44ACu, gen::fn_RwCameraEndUpdate_004c9d00);
    lw(v1, s1);
    v0 = v1 & 1;
    if (v0 != 0) {
        charge(4);
        v0 = lui(0x8000);
        v0 = v1 & v0;
        if (v0 != 0) {
            charge(14);
            world_pair_lights(0x1B44D4u, 12, gen::fn_sub_49C480_0049c480);
        } else {
            charge(4);
            v0 = lui(0x4000);
            v0 = v1 & v0;
            if (v0 != 0) {
                charge(14);
                world_pair_lights(0x1B451Cu, 16, gen::fn_sub_49C480_0049c480);
            } else {
                charge(12);
                world_pair_lights(0x1B4554u, 8, gen::fn_sub_49C480_0049c480);
            }
        }
        charge(25);
        root_world_lights(0x1B4588u, gen::fn_sub_49C3D0_0049c3d0);
        lw(v1, s1);
        const s32 slot = fldsrc_world_slot();
        charge(slot == 12 ? 6 : slot == 16 ? 6 : 4);
        lw(a0, s1 + slot);
        a1 = s2;
        jal(slot == 12 ? 0x1B45F0u : slot == 16 ? 0x1B4618u : 0x1B4630u, gen::fn_sub_49C1B0_0049c1b0);
        charge(9);
        lw(a0, gp - 19492);
        jal(0x1B463Cu, gen::fn_sub_198540_00198540);
        a0 = v0;
        a1 = s2;
        jal(0x1B464Cu, gen::fn_sub_49C160_0049c160);  // the camera back into the root world
    } else {
        charge(10);
        world_light(0x1B4660u, gen::fn_sub_49C3D0_0049c3d0);
    }
    charge(36);
    fldsrc_lights_epilogue(0x1B4684u);
    ld(ra, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 160);
}

// 0x1B4720 K_FldSrc_DrawFieldTrans(camera, res): the translucent field pass. The same camera / light moves as the
// opaque pass; inside the camera pass (bit 0 clear) the res's translucent atomics (+12 lists through
// sub_1A8140(.., 1), or the clump +16); the extra parts' lists through sub_1A8140.
void Cpu::K_FldSrc_DrawFieldTrans() {
    enter(33);
    sp = addiu(sp, -160);
    sd(sp + 48, ra);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    s2 = a0;
    s1 = a1;
    fldsrc_lights_prologue(0x1B473Cu);
    charge(38);
    field_lights_on(0x1B47C8u);
    dir_light_flags(0x1B483Cu);
    lw(v0, s1);
    v0 = v0 & 1;
    if (v0 != 0) {
        charge(12);
        lw(a0, gp - 19492);
        jal(0x1B4864u, gen::fn_sub_198540_00198540);
        a0 = v0;
        a1 = s2;
        jal(0x1B4874u, gen::fn_sub_49C1B0_0049c1b0);
        lw(v1, s1);
        const s32 slot = fldsrc_world_slot();
        charge(slot == 8 ? 4 : 6);
        lw(a0, s1 + slot);
        a1 = s2;
        jal(slot == 12 ? 0x1B4898u : slot == 16 ? 0x1B48C0u : 0x1B48D8u, gen::fn_sub_49C160_0049c160);
        charge(25);
        root_world_lights(0x1B48E4u, gen::fn_sub_49C480_0049c480);
        lw(v1, s1);
        const s32 lslot = fldsrc_world_slot();
        charge(14);
        world_pair_lights(lslot == 12 ? 0x1B4944u : lslot == 16 ? 0x1B498Cu : 0x1B49C4u, lslot, gen::fn_sub_49C3D0_0049c3d0);
    } else {
        charge(10);
        world_light(0x1B4A00u, gen::fn_sub_49C480_0049c480);
    }
    charge(4);
    lw(v0, s1);
    v0 = v0 & 1;
    if (v0 != 0) {
        charge(5);
        a0 = s2;
        jal(0x1B4A38u, gen::fn_RwCameraBeginUpdate_004c9d10);
        if (v0 == 0) {
            charge(7);
            a0 = addiu(lui(0x68), -29192);
            a1 = 2093;
            jal(0x1B4A54u, gen::fn_sub_19D3F0_0019d3f0);
        }
    } else {
        charge(5);
        a0 = s2;
        jal(0x1B4A68u, gen::fn_RwCameraBeginUpdate_004c9d10);
        if (v0 != 0) {
            charge(26);
            fldsrc_pass_states(0x1B4A84u);
            lw(v1, s1);
            v0 = lui(0x8000);
            v0 = v1 & v0;
            if (v0 != 0) {
                charge(3);
                lw(a0, s1 + 12);
                if (a0 != 0) {
                    charge(5);
                    a1 = 1;
                    jal(0x1B4AF0u, gen::fn_sub_1A8140_001a8140);
                }
            } else {
                charge(4);
                v0 = lui(0x4000);
                v0 = v1 & v0;
                if (v0 != 0) {
                    charge(3);
                    lw(a0, s1 + 16);
                    if (a0 != 0) {
                        charge(4);
                        jal(0x1B4B1Cu, gen::fn_sub_1A88E0_001a88e0);
                    }
                }
            }
        } else {
            charge(5);
            a0 = addiu(lui(0x68), -29192);
            a1 = 2118;
            jal(0x1B4B38u, gen::fn_sub_19D3F0_0019d3f0);
        }
    }
    charge(5);
    lw(v1, s1);
    v0 = lui(0xC000);
    v0 = v1 & v0;
    if (v0 == 0) {
        charge(3);
        s0 = 0;
        for (;;) {
            charge(4);
            lw(v0, s1 + 20);
            v0 = sltu(s0, v0);
            if (v0 == 0) break;
            backedge();
            charge(5);
            v0 = sll(s0, 2);
            v0 = addu(s1, v0);
            lw(a0, v0 + 152);
            if (a0 != 0) {
                charge(3);
                a1 = 1;
                jal(0x1B4B78u, gen::fn_sub_1A8140_001a8140);
            }
            charge(1);
            s0 = addiu(s0, 1);
        }
    }
    charge(7);
    a0 = s2;
    jal(0x1B4B98u, gen::fn_RwCameraEndUpdate_004c9d00);
    lw(v1, s1);
    v0 = v1 & 1;
    if (v0 != 0) {
        charge(4);
        v0 = lui(0x8000);
        v0 = v1 & v0;
        if (v0 != 0) {
            charge(14);
            world_pair_lights(0x1B4BC0u, 12, gen::fn_sub_49C480_0049c480);
        } else {
            charge(4);
            v0 = lui(0x4000);
            v0 = v1 & v0;
            if (v0 != 0) {
                charge(14);
                world_pair_lights(0x1B4C08u, 16, gen::fn_sub_49C480_0049c480);
            } else {
                charge(12);
                world_pair_lights(0x1B4C40u, 8, gen::fn_sub_49C480_0049c480);
            }
        }
        charge(25);
        root_world_lights(0x1B4C74u, gen::fn_sub_49C3D0_0049c3d0);
        lw(v1, s1);
        const s32 slot = fldsrc_world_slot();
        charge(slot == 8 ? 4 : 6);
        lw(a0, s1 + slot);
        a1 = s2;
        jal(slot == 12 ? 0x1B4CDCu : slot == 16 ? 0x1B4D04u : 0x1B4D1Cu, gen::fn_sub_49C1B0_0049c1b0);
        charge(9);
        lw(a0, gp - 19492);
        jal(0x1B4D28u, gen::fn_sub_198540_00198540);
        a0 = v0;
        a1 = s2;
        jal(0x1B4D38u, gen::fn_sub_49C160_0049c160);
    } else {
        charge(10);
        world_light(0x1B4D4Cu, gen::fn_sub_49C3D0_0049c3d0);
    }
    charge(36);
    fldsrc_lights_epilogue(0x1B4D70u);
    ld(ra, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 160);
}


// =========================================================================================================
// [battle] the battle front pass and the full-screen quads (22_rendering.md section 1: "battle draw 3d front")
// =========================================================================================================

// A byte-sized integer in `src` as a float in `fdst` (through `ftmp`): the unsigned-convert idiom with the
// compiler's temporaries `hi` / `lo` (the negative branch never runs: the values are bytes).
void Cpu::u2f(Gpr& src, Gpr& hi, Gpr& lo, unsigned ftmp, unsigned fdst) {
    if (sgn(src) < 0) {
        charge(7);
        hi = srl(src, 1);
        lo = src & 1;
        hi = hi | lo;
        mtc1(hi, ftmp);
        cvt_s_w(fdst, ftmp);
        add_s(fdst, fdst, fdst);
    } else {
        charge(5);
        mtc1(src, ftmp);
        cvt_s_w(fdst, ftmp);
    }
}

// sub_358460(colour, save): a full-screen RwIm2DVertex strip (0,0)-(640,448) at the near screen z (0x960088),
// recipZ = 1 / near plane, in the RwRGBA *colour; `save` brackets the six states of 0x69CE60 (alpha ref 68,
// blend 0x717FB). The battle front pass uses it to clear the alpha of the masked area.
void Cpu::sub_358460() {
    enter(11);
    sp = addiu(sp, -384);
    sd(sp + 80, ra);
    sq(sp + 64, s3);
    sq(sp + 48, s2);
    sq(sp + 32, s1);
    sq(sp + 16, s0);
    swc1(F20, sp);
    s3 = a0;
    s2 = a1;
    if (s2 != 0) states_push(s1, s0, 96, 0x3584C0u, 0x358500u, 68, 0x17FB);
    charge(14);
    v0 = lui(0x96);
    lwc1(F20, v0 + 136);  // the near screen z
    camera_get(0x358534u);
    v1 = lui(0x3F80);
    mtc1(v1, F1);
    lwc1(F0, v0 + 128);
    div_s(F0, F1, F0);  // recipZ
    struct Corner {
        s32 at;
        u32 x, y;  // the float bits of x / y (0 = 0.0)
        u64 colour_tail;  // the cost of the block that stores the last colour float (the next corner's set-up)
    };
    const Corner corners[4] = {{128, 0, 0, 9}, {192, 0, 0x43E00000u, 9}, {256, 0x44200000u, 0, 10}, {320, 0x44200000u, 0x43E00000u, 11}};
    sw(sp + 128, zero);
    sw(sp + 132, zero);
    swc1(F20, sp + 136);
    for (u32 ci = 0; ci < 4; ++ci) {
        const Corner& k = corners[ci];
        for (u32 i = 0; i < 4; ++i) {
            lbu(v0, s3 + i);
            u8_to_float(F1, F1);
            charge(i == 3 ? k.colour_tail : 4);
            swc1(F1, sp + k.at + 32 + 4 * i);
        }
        swc1(F0, sp + k.at + 24);
        if (ci == 3) break;
        const Corner& n = corners[ci + 1];
        // the next corner's position (the compiler's order: x, y as `lui` words or zero, then z)
        if (n.x == 0) {
            sw(sp + n.at, zero);
            v0 = lui(n.y >> 16);
            sw(sp + n.at + 4, v0);
        } else if (n.y == 0) {
            v0 = lui(n.x >> 16);
            sw(sp + n.at, v0);
            sw(sp + n.at + 4, zero);
        } else {
            v0 = lui(n.x >> 16);
            sw(sp + n.at, v0);
            v0 = lui(n.y >> 16);
            sw(sp + n.at + 4, v0);
        }
        swc1(F20, sp + n.at + 8);
    }
    a0 = 4;  // rwPRIMTYPETRISTRIP
    a1 = addiu(sp, 128);
    a2 = a0;
    call_pfn(0x3589B0u, kPfnIm2DRenderPrimitive);
    if (s2 != 0) states_pop(96, 0x3589F4u);
    charge(9);
    ld(ra, sp + 80);
    lq(s3, sp + 64);
    lq(s2, sp + 48);
    lq(s1, sp + 32);
    lq(s0, sp + 16);
    lwc1(F20, sp);
    sp = addiu(sp, 384);
}

// sub_29E4B0: the battle screen flash (the battle work gp-18692: +564 .. +576 the RGBA as 0..1 floats; drawn when
// the alpha is > 0): a full-screen Im2D strip in that colour (each channel rounded: (int)(0 + 0.5 + 255 c) & 0xFF),
// vertex alpha on, fog / texture / Z off, gouraud, alpha ref 72, blend 0x71801.
void Cpu::sub_29E4B0() {
    enter(10);
    sp = addiu(sp, -352);
    sd(sp + 16, ra);
    sq(sp, s0);
    lw(v1, gp - 18692);
    lwc1(F1, v1 + 576);
    mtc1(zero, F0);
    c_le_s(F1, F0);
    if (!cop1_cond()) {
        charge(88);
        sky_states(0x29E4E0u, 72, 0x1801);
        s0 = addiu(lui(0x96), 144);
        const u32 states[6][3] = {{12, 1, 0x29E510u}, {14, 0, 0x29E524u}, {1, 0, 0x29E538u},
                                  {6, 0, 0x29E54Cu}, {8, 0, 0x29E560u}, {7, 2, 0x29E574u}};
        for (const auto& st : states) {
            a0 = st[0];
            a1 = st[1];
            lw(v0, s0);
            jalr(st[2], v0.u());
        }
        lw(a2, gp - 18692);
        lwc1(F0, a2 + 564);
        v0 = lui(0x437F);  // 255.0
        mtc1(v0, F3);
        v0 = lui(0x3F00);  // 0.5
        mtc1(v0, F2);
        mtc1(zero, F1);
        Gpr* const chan[4] = {&a1, &a0, &v1, &v0};
        for (u32 k = 0; k < 4; ++k) {
            if (k) lwc1(F0, a2 + 564 + 4 * k);
            adda_s(F1, F2);
            madd_s(F0, F3, F0);
            cvt_w_s(F0, F0);
            mfc1(v0, F0);
            *chan[k] = v0 & 0xFF;
        }
        sw(sp + 32, zero);  // the corners (0,0) (0,448) (640,0) (640,448)
        sw(sp + 36, zero);
        sw(sp + 96, zero);
        a3 = lui(0x43E0);
        sw(sp + 100, a3);
        a2 = lui(0x4420);
        sw(sp + 160, a2);
        sw(sp + 164, zero);
        sw(sp + 224, a2);
        sw(sp + 228, a3);
        for (u32 ci = 0; ci < 4; ++ci) {
            for (u32 k = 0; k < 4; ++k) {
                // the temporaries of the (never taken) negative branch: $a3 / $a2, the last corner's the next register
                Gpr& hi = ci < 3 ? a3 : (k == 0 ? a2 : *chan[k - 1]);
                Gpr& lo = ci < 3 ? a2 : *chan[k];
                u2f(*chan[k], hi, lo, F0, F0);
                charge(ci == 3 && k == 3 ? 8 : 3);
                swc1(F0, sp + 64 + 64 * ci + 4 * k);
            }
        }
        a0 = 4;  // rwPRIMTYPETRISTRIP
        a1 = addiu(sp, 32);
        a2 = a0;
        call_pfn(0x29EA04u, kPfnIm2DRenderPrimitive);
    }
    charge(5);
    ld(ra, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 352);
}

// sub_2891E0: the battle front pass ("battle draw 3d front" via sub_321120(3)): the units of both sides (gBtl +340 +
// 8 * side, linked by +2608) with flag 0x800 and a model id (+2546) whose field resource (sub_3B54C0) is not hidden
// are collected on the stack and sorted (qsort, comparator 0x2890A0); with the lights saved and the battle's own
// (resource list 4: +256 / +272 colours, +288 the second light's frame), back to front: the unit's directional light
// (+400, frame +416), and inside a camera pass the model sub_317A20 with its shadow kind set to 3 (sub_319230) --
// before the first one the masked alpha clear: sky states, gouraud, no fog / Z / texture, filter, vertex alpha,
// FRAME_1 masked (sub_3294D0), a black full-screen quad (sub_358460), the mask off (sub_329550).
void Cpu::sub_2891E0() {
    enter(10);
    sp = addiu(sp, -320);
    sd(sp + 64, ra);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    s1 = 0;  // the number of units collected at sp + 256
    s0 = 0;  // the side
    for (;;) {
        charge(3);
        v1 = slti(s0, 2);
        if (v1 == 0) break;
        backedge();
        charge(6);
        a0 = sll(s0, 3);
        lw(v1, gp - 18692);
        v1 = addu(v1, a0);
        lw(s2, v1 + 340);
        for (;;) {
            charge(2);
            if (s2 == 0) break;
            backedge();
            charge(4);
            lw(v1, s2 + 156);
            v1 = v1 & 0x800;
            if (v1 != 0) {
                charge(3);
                lhu(a1, s2 + 2546);
                if (a1 != 0) {
                    charge(8);
                    lw(v0, gp - 22448);
                    lw(a0, v0 + 8);
                    jal(0x289244u, gen::fn_sub_3B54C0_003b54c0);  // the unit's field resource
                    lw(v1, v0 + 40);
                    v1 = v1 & 2;
                    if (v1 == 0) {
                        charge(4);
                        v1 = sll(s1, 2);
                        v1 = addu(v1, sp);
                        sw(v1 + 256, v0);
                        s1 = addiu(s1, 1);
                    }
                }
            }
            charge(1);
            lw(s2, s2 + 2608);
        }
        charge(1);
        s0 = addiu(s0, 1);
    }
    charge(2);
    if (s1 != 0) {
        charge(27);
        s0 = 1;  // the alpha clear still to do
        light_colour_save(0x289294u, gen::fn_sub_198560_00198560, 240);
        light_colour_save(0x2892BCu, gen::fn_sub_198570_00198570, 224);
        light_frame_save(0x2892E4u, gen::fn_sub_198570_00198570, 144);
        charge(16);
        light_colour_save(0x289320u, gen::fn_sub_198580_00198580, 208);
        light_frame_save(0x289348u, gen::fn_sub_198580_00198580, 80);
        charge(33);
        a0 = addiu(sp, 256);
        a1 = s1;
        a2 = 4;
        a3 = addiu(lui(0x29), -28512);  // the comparator 0x2890A0
        jal(0x289398u, gen::fn_qsort_005225f8);
        a0 = 4;
        jal(0x2893A4u, gen::fn_sub_3B5D50_003b5d50);
        s2 = v0;
        light_colour_set(0x2893B0u, gen::fn_sub_198560_00198560, s2, 256);
        light_colour_set(0x2893C8u, gen::fn_sub_198580_00198580, s2, 272);
        light_frame_set(0x2893E0u, gen::fn_sub_198580_00198580, s2, 288);
        s2 = addiu(s1, -1);
        for (;;) {
            charge(2);
            if (sgn(s2) < 0) break;
            backedge();
            charge(23);
            v0 = sll(s2, 2);
            v0 = addu(v0, sp);
            lw(s1, v0 + 256);
            light_colour_set(0x289414u, gen::fn_sub_198570_00198570, s1, 400);
            light_frame_set(0x28942Cu, gen::fn_sub_198570_00198570, s1, 416);
            camera_begin(0x289448u, 0x289454u);
            if (v0 != 0) {
                charge(2);
                if (s0 != 0) {
                    charge(60);
                    sky_states(0x289474u, 68, 0x17FB);
                    s0 = addiu(lui(0x96), 144);
                    const u32 states[7][3] = {{7, 2, 0x2894A4u}, {14, 0, 0x2894B8u}, {6, 0, 0x2894CCu}, {8, 0, 0x2894E0u},
                                              {9, 2, 0x2894F4u}, {12, 1, 0x289508u}, {1, 0, 0x28951Cu}};
                    for (const auto& st : states) {
                        a0 = st[0];
                        a1 = st[1];
                        lw(v0, s0);
                        jalr(st[2], v0.u());
                    }
                    jal(0x289524u, gen::fn_sub_3294D0_003294d0);
                    sb(sp + 316, zero);
                    sb(sp + 317, zero);
                    sb(sp + 318, zero);
                    v0 = 255;
                    sb(sp + 319, v0);
                    a0 = addiu(sp, 316);
                    a1 = 0;
                    jal(0x289548u, gen::fn_sub_358460_00358460);
                    jal(0x289550u, gen::fn_sub_329550_00329550);
                    s0 = 0;
                }
                charge(17);
                lw(a0, s1 + 296);
                lhu(s3, a0 + 1048);
                a1 = 3;
                jal(0x289568u, gen::fn_sub_319230_00319230);
                lw(a0, s1 + 296);
                jal(0x289574u, gen::fn_sub_317A20_00317a20);
                lw(a0, s1 + 296);
                a1 = s3;
                jal(0x289584u, gen::fn_sub_319230_00319230);
                camera_end(0x28958Cu, 0x289598u);
            }
            charge(1);
            s2 = addiu(s2, -1);
        }
        charge(32);
        light_colour_set(0x2895ACu, gen::fn_sub_198560_00198560, sp, 240);
        light_colour_set(0x2895C4u, gen::fn_sub_198580_00198580, sp, 208);
        light_colour_set(0x2895DCu, gen::fn_sub_198570_00198570, sp, 224);
        light_frame_set(0x2895F4u, gen::fn_sub_198580_00198580, sp, 80);
        light_frame_set(0x289610u, gen::fn_sub_198570_00198570, sp, 144);
    }
    charge(8);
    ld(ra, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 320);
}


// sub_19EF80 "draw trans NPC sort" (prio 4183): field-resource list 3's NPCs whose model (sub_318B00) is not fully
// opaque (alpha byte < 255) collected on the stack (64 at most, the 256-byte array cleared first), sorted by distance
// (qsort, comparator 0x19EE40) when the scene asks for it (scene +28 == 1), and drawn back to front: their lights (flag
// 0x80000000: the NPC's own +300 / +316 / +400 colours and +336 / +416 frames; else the list-5 resource's +256 /
// +272 / +352 and +288 / +368), the model and its three attached effects (+256.. : sub_318ED0 their anchor, else the
// model's position raised by 175.0; sub_34FDF0 placed there, sub_34FD70(.., 5)) inside a camera pass.
void Cpu::sub_19EF80() {
    enter(41);
    sp = addiu(sp, -544);
    sd(sp + 80, ra);
    sq(sp + 64, s4);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    a0 = 3;
    jal(0x19EFA0u, gen::fn_sub_3B5D50_003b5d50);
    s1 = v0;
    a0 = 5;
    jal(0x19EFB0u, gen::fn_sub_3B5D50_003b5d50);
    s3 = v0;
    light_colour_save(0x19EFBCu, gen::fn_sub_198560_00198560, 512);
    light_colour_save(0x19EFE4u, gen::fn_sub_198570_00198570, 496);
    light_frame_save(0x19F00Cu, gen::fn_sub_198570_00198570, 432);
    charge(16);
    light_colour_save(0x19F048u, gen::fn_sub_198580_00198580, 416);
    light_frame_save(0x19F070u, gen::fn_sub_198580_00198580, 352);
    charge(8);
    a0 = addiu(sp, 96);
    a1 = 0;
    a2 = 256;
    jal(0x19F0B8u, gen::fn_memset_00521408);
    s0 = 0;
    for (;;) {
        charge(2);
        if (s1 == 0) break;
        backedge();
        charge(7);
        lw(a0, s1 + 296);
        jal(0x19F0D0u, gen::fn_sub_318B00_00318b00);
        lbu(v0, v0 + 3);
        at = slti(v0, 255);
        if (at != 0) {
            charge(4);
            v0 = sll(s0, 2);
            v0 = addu(v0, sp);
            sw(v0 + 96, s1);
            s0 = addiu(s0, 1);
        }
        charge(1);
        lw(s1, s1 + 248);
    }
    charge(5);
    lw(v0, gp - 22448);
    lw(v1, v0 + 28);
    v0 = 1;
    if (v1 == v0) {
        charge(7);
        a0 = addiu(sp, 96);
        a1 = s0;
        a2 = 4;
        a3 = addiu(lui(0x1A), -4544);  // the comparator 0x19EE40
        jal(0x19F12Cu, gen::fn_qsort_005225f8);
    }
    charge(3);
    s0 = addiu(s0, -1);
    for (;;) {
        charge(2);
        if (sgn(s0) < 0) break;
        backedge();
        charge(8);
        v0 = sll(s0, 2);
        v0 = addu(v0, sp);
        s2 = addiu(v0, 96);
        lw(s1, s2);
        lw(v1, s1 + 40);
        v0 = v1 & 2;
        if (v0 != 0) {
            charge(4);
            v0 = lui(0x8000);
            v0 = v1 & v0;
            if (v0 != 0) {  // the NPC's own lights
                charge(38);
                jal(0x19F170u, gen::fn_sub_198560_00198560);
                a0 = v0;
                a1 = addiu(s1, 300);
                jal(0x19F180u, gen::fn_sub_4944B0_004944b0);
                const struct {
                    u32 pc;
                    rt::Fn getter;
                    s32 off;
                    bool frame;
                } sets[4] = {{0x19F188u, gen::fn_sub_198580_00198580, 316, false},
                             {0x19F1A4u, gen::fn_sub_198570_00198570, 400, false},
                             {0x19F1C0u, gen::fn_sub_198580_00198580, 336, true},
                             {0x19F1E0u, gen::fn_sub_198570_00198570, 416, true}};
                for (const auto& st : sets) {  // the NPC reloaded from its slot each time
                    jal(st.pc, st.getter);
                    lw(v1, s2);
                    if (st.frame) {
                        lw(a0, v0 + 4);
                        a1 = addiu(v1, st.off);
                        a2 = 0;
                        jal(st.pc + 0x18, gen::fn_sub_4CB7F0_004cb7f0);
                    } else {
                        a0 = v0;
                        a1 = addiu(v1, st.off);
                        jal(st.pc + 0x14, gen::fn_sub_4944B0_004944b0);
                    }
                }
            } else {
                charge(32);
                light_colour_set(0x19F208u, gen::fn_sub_198560_00198560, s3, 256);
                light_colour_set(0x19F220u, gen::fn_sub_198580_00198580, s3, 272);
                light_colour_set(0x19F238u, gen::fn_sub_198570_00198570, s3, 352);
                light_frame_set(0x19F250u, gen::fn_sub_198580_00198580, s3, 288);
                light_frame_set(0x19F26Cu, gen::fn_sub_198570_00198570, s3, 368);
            }
            charge(7);
            camera_begin(0x19F288u, 0x19F294u);
            if (v0 != 0) {
                charge(10);
                v0 = sll(s0, 2);
                v0 = addu(v0, sp);
                s2 = addiu(v0, 96);
                lw(v0, s2);
                lw(a0, v0 + 296);
                jal(0x19F2B8u, gen::fn_sub_317A20_00317a20);
                s4 = 0;
                for (;;) {
                    charge(3);
                    v0 = slti(s4, 3);
                    if (v0 == 0) break;
                    backedge();
                    charge(6);
                    lw(v1, s2);
                    v0 = sll(s4, 2);
                    v0 = addu(v1, v0);
                    lw(v0, v0 + 256);
                    if (v0 != 0) {
                        charge(7);
                        lw(a0, v1 + 296);
                        a1 = 2;
                        a2 = addiu(sp, 528);
                        jal(0x19F2F0u, gen::fn_sub_318ED0_00318ed0);  // the effect anchor, 0 = none
                        if (v0 == 0) {
                            charge(16);
                            lw(v0, s2);
                            lw(a0, v0 + 296);
                            jal(0x19F308u, gen::fn_sub_318B60_00318b60);
                            lwc1(F2, v0 + 48);
                            lwc1(F1, v0 + 52);
                            lwc1(F0, v0 + 56);
                            swc1(F2, sp + 528);
                            swc1(F1, sp + 532);
                            swc1(F0, sp + 536);
                            lwc1(F1, sp + 532);
                            v0 = lui(0x432F);  // 175.0
                            mtc1(v0, F0);
                            add_s(F0, F1, F0);
                            swc1(F0, sp + 532);
                        }
                        charge(13);
                        s1 = sll(s4, 2);
                        lw(v0, s2);
                        v0 = addu(v0, s1);
                        lw(a0, v0 + 256);
                        a1 = addiu(sp, 528);
                        jal(0x19F354u, gen::fn_sub_34FDF0_0034fdf0);
                        lw(v0, s2);
                        v0 = addu(v0, s1);
                        lw(a0, v0 + 256);
                        a1 = 5;
                        jal(0x19F36Cu, gen::fn_sub_34FD70_0034fd70);
                    }
                    charge(1);
                    s4 = addiu(s4, 1);
                }
                charge(7);
                camera_end(0x19F384u, 0x19F390u);
            } else {
                charge(5);
                a0 = addiu(lui(0x68), -30328);
                a1 = 821;
                jal(0x19F3ACu, gen::fn_sub_19D3F0_0019d3f0);
            }
        }
        charge(1);
        s0 = addiu(s0, -1);
    }
    charge(42);
    light_colour_set(0x19F3C0u, gen::fn_sub_198560_00198560, sp, 512);
    light_colour_set(0x19F3D8u, gen::fn_sub_198580_00198580, sp, 416);
    light_colour_set(0x19F3F0u, gen::fn_sub_198570_00198570, sp, 496);
    light_frame_set(0x19F408u, gen::fn_sub_198580_00198580, sp, 352);
    light_frame_set(0x19F424u, gen::fn_sub_198570_00198570, sp, 432);
    v0 = 0;
    ld(ra, sp + 80);
    lq(s4, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 544);
}


// =========================================================================================================
// [font] the text draw (20_menu_ui.md section 5: frFont; every message window, menu and battle text)
// =========================================================================================================

// A text line's wait tags (the line's +60 counter: -1 = waiting for the confirm pad, > 0 frames to wait): decrement
// a positive counter and stop the draw from counting as finished ($s0 = 0); the compiler's tail cost differs per site.
void Cpu::font_wait_tick(u64 tail) {
    charge(4);
    lw(v1, s4 + 60);
    v0 = static_cast<u64>(-1);
    if (v1 == v0) return;
    charge(2);
    if (sgn(v1) <= 0) return;
    charge(tail);
    v0 = addiu(v1, -1);
    sw(s4 + 60, v0);
    s0 = 0;
}

// 0x3B1360 frFontDraw(text, mode): draws a laid-out text (+44 the first line: +4 / +8 the pen x / y in 1/16 px,
// +3 the s8 glyph spacing, +20 the z offset, +24 the line width, +28 the glyph nodes, +40 the next line, +48 the
// line's end tag, +60 its wait counter, +64 a continuation) glyph by glyph through frFontRasterDrawGlyph; mode 0
// (the low byte of $a1, as s8) first animates each glyph (sub_3B0F50). Unless the font states are locked (flag 0x40
// of gp-22512) the Im2D states are set first: Z test on, gouraud, linear filter, vertex alpha, blend src alpha /
// inv src alpha, clamp, fog off, alpha ref 68, blend 0x5100D. Returns the summed line widths, or 0 while a glyph is
// still fading in or a wait tag holds (gp-18108 > 0 counts down instead).
void Cpu::frFontDraw() {
    enter(18);
    sp = addiu(sp, -144);
    sd(sp + 128, ra);
    sq(sp + 112, s7);
    sq(sp + 96, s6);
    sq(sp + 80, s5);
    sq(sp + 64, s4);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    s4 = a0;
    s3 = a1;
    s2 = 0;  // the width
    s0 = 1;  // finished: every glyph opaque and no wait pending
    lh(v0, gp - 22512);
    v0 = v0 & 0x40;
    if (v0 == 0) {
        charge(51);
        s1 = addiu(lui(0x96), 144);
        const struct {
            u32 state;
            int value;  // -1: $s0 (1)
            u32 pc;
        } states[8] = {{6, -1, 0x3B13BCu}, {7, 2, 0x3B13D0u}, {9, 2, 0x3B13E4u}, {12, -1, 0x3B13F8u},
                       {10, 5, 0x3B140Cu}, {11, 6, 0x3B1420u}, {2, 4, 0x3B1434u}, {14, 0, 0x3B1448u}};
        for (const auto& st : states) {
            a0 = st.state;
            if (st.value < 0)
                a1 = s0;
            else
                a1 = static_cast<u64>(st.value);
            lw(v0, s1);
            jalr(st.pc, v0.u());
        }
        a0 = 2;
        a1 = 68;
        jal(0x3B1458u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 3;
        v0 = lui(0x5);
        a1 = v0 | 0x100D;
        jal(0x3B146Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
    }
    charge(2);
    if (s4 == 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(5);
        lw(s4, s4 + 44);
        s5 = dsll32(s3, 24);
        s5 = dsra32(s5, 24);  // the mode byte, signed
        for (;;) {  // the lines
            charge(2);
            if (s4 == 0) break;
            backedge();
            charge(6);
            lw(s1, s4 + 4);
            lw(s6, s4 + 8);
            lb(s7, s4 + 3);
            lw(s3, s4 + 28);
            for (;;) {  // the glyphs
                charge(2);
                if (s3 == 0) break;
                backedge();
                charge(2);
                if (s5 == 0) {
                    charge(8);
                    lbu(a2, s4);
                    a0 = s4;
                    a1 = s3;
                    lbu(a3, s4 + 2);
                    jal(0x3B14CCu, gen::fn_sub_3B0F50_003b0f50);  // the glyph's animation offset in $v0
                } else {
                    charge(1);
                    v0 = 0;
                }
                charge(16);
                lw(v1, s3 + 4);
                v1 = addu(s1, v1);
                a0 = addu(v0, v1);
                lw(v0, s3 + 8);
                a1 = addu(s6, v0);
                lbu(a3, s3 + 20);
                lbu(t0, s3 + 24);
                lbu(t1, s3 + 25);
                lwc1(F12, s4 + 20);
                a2 = s3;
                lw(t2, s3 + 16);
                jal(0x3B150Cu, gen::fn_frFontRasterDrawGlyph_003b38f0);
                lbu(v0, s3 + 16);  // the glyph alpha
                if (v0 != 0) {
                    charge(3);
                    lhu(v0, s3 + 2);
                    v0 = addiu(v0, 1);
                    sh(s3 + 2, v0);
                }
                charge(4);
                lbu(v0, s3 + 16);
                at = sltiu(v0, 255);
                if (at != 0) {
                    charge(1);
                    s0 = 0;
                }
                charge(5);
                lw(v0, s3 + 12);
                v0 = addu(v0, s7);
                v0 = sll(v0, 4);
                s1 = addu(s1, v0);
                lw(s3, s3 + 40);
            }
            charge(3);
            lw(v0, s4 + 40);
            if (v0 == 0) {  // the last line: its end tag
                charge(3);
                lw(v0, s4 + 64);
                if (v0 == 0) {
                    charge(4);
                    lw(v1, s4 + 48);
                    v0 = 0xF247;
                    if (v1 == v0) {
                        charge(5);
                        a0 = 2;
                        jal(0x3B1654u, gen::fn_sub_10A500_0010a500);
                        if (v0 != 0) {
                            charge(3);
                            s0 = 0;
                        } else {
                            font_wait_tick(3);
                        }
                    } else {
                        charge(3);
                        v0 = 0xF246;
                        if (v1 == v0) {
                            font_wait_tick(5);
                        } else {
                            charge(3);
                            v0 = 0xF215;
                            if (v1 == v0) {
                                charge(5);
                                a0 = 2;
                                jal(0x3B15DCu, gen::fn_sub_10A500_0010a500);
                                if (v0 != 0) {
                                    charge(3);
                                    s0 = 0;
                                } else {
                                    font_wait_tick(5);
                                }
                            } else {
                                charge(3);
                                v0 = 0xF214;
                                if (v1 == v0) {
                                    charge(2);
                                    if (s0 != 0) {
                                        charge(3);
                                        lw(v0, s4 + 60);
                                        if (sgn(v0) > 0) {
                                            charge(5);
                                            v0 = addiu(v0, -1);
                                            sw(s4 + 60, v0);
                                            s0 = 0;
                                        }
                                    }
                                } else {
                                    charge(2);
                                }
                            }
                        }
                    }
                }
            }
            charge(3);
            lw(v0, s4 + 24);
            s2 = addu(s2, v0);
            lw(s4, s4 + 40);
        }
        charge(3);
        lw(v0, gp - 18108);
        if (sgn(v0) > 0) {
            charge(5);
            v0 = addiu(v0, -1);
            sw(gp - 18108, v0);
            v0 = 0;
        } else {
            charge(4);
            v0 = dsll32(s0, 24);
            v0 = dsra32(v0, 24);
            if (v0 == 0) {
                charge(1);
                s2 = 0;
            }
            charge(1);
            v0 = s2;
        }
    }
    charge(12);
    ld(ra, sp + 128);
    lq(s7, sp + 112);
    lq(s6, sp + 96);
    lq(s5, sp + 80);
    lq(s4, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 144);
}


// =========================================================================================================
// [rect] the menu rectangles (one body compiled four times: plain / textured x alpha ref 68 / 72)
// =========================================================================================================

// sub_113A30 / sub_113D80 / sub_1140D0 / sub_114AF0 (rgba, w, h[, &raster]) with $f12 = the depth offset, $f13 / $f14
// = x / y: a w x h RwIm2DVertex strip at (x, y) in the colour 0xRRGGBBAA, z = the near screen z - offset, recipZ =
// 1 / near plane; Z test on, gouraud, Z write on, filter (nearest / linear for the textured ones), vertex alpha, blend
// inv src alpha / src alpha, clamp, alpha ref 68 / blend 0x717FB or 72 / 0x71801; the textured ones map the unit square and set
// the raster *$a3, the plain ones clear it. `start` = the function's address (the pcs of the calls follow from it).
void Cpu::menu_rect(u32 start, u32 ref, u32 blend_lo, bool textured) {
    const s32 frame = textured ? 448 : 432;
    const s32 q = textured ? 16 : 0;  // the stack layout moves by one 16-byte slot
    const auto pc = [&](u32 plain, u32 tex) { return start + (textured ? tex : plain); };
    enter(textured ? 120 : 118);
    sp = addiu(sp, -frame);
    sd(sp + 128 + q, ra);
    if (textured) sq(sp + 128, s7);
    sq(sp + 112, s6);
    sq(sp + 96, s5);
    sq(sp + 80, s4);
    sq(sp + 64, s3);
    sq(sp + 48, s2);
    sq(sp + 32, s1);
    sq(sp + 16, s0);
    swc1(F23, sp + 12);
    swc1(F22, sp + 8);
    swc1(F21, sp + 4);
    swc1(F20, sp);
    mov_s(F21, F12);  // the depth offset
    s0 = a0;
    mov_s(F23, F13);  // x
    mov_s(F22, F14);  // y
    s5 = a1;
    s6 = a2;
    if (textured) s7 = a3;
    camera_get(pc(0x4C, 0x54));
    v1 = lui(0x3F80);
    mtc1(v1, F1);
    lwc1(F0, v0 + 128);
    div_s(F20, F1, F0);  // recipZ
    v0 = lui(0xFF00);
    v0 = s0 & v0;
    v0 = srl(v0, 24);
    s4 = v0 & 0xFF;  // red
    v0 = lui(0xFF);
    v0 = s0 & v0;
    v0 = srl(v0, 16);
    s3 = v0 & 0xFF;  // green
    v0 = s0 & 0xFF00;
    v0 = srl(v0, 8);
    s2 = v0 & 0xFF;  // blue
    s1 = s0 & 0xFF;  // alpha
    s0 = addiu(lui(0x96), 144);
    const u32 states[8][2] = {{6, 1}, {7, 2}, {8, 1}, {9, textured ? 2u : 1u}, {12, 1}, {11, 6}, {10, 5}, {2, 4}};
    for (u32 k = 0; k < 8; ++k) {
        a0 = states[k][0];
        a1 = states[k][1];
        lw(v0, s0);
        jalr(pc(0xA8, 0xB0) + 0x14 * k, v0.u());
    }
    a0 = 2;
    a1 = ref;
    jal(pc(0x144, 0x14C), gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 3;
    v0 = lui(0x7);
    a1 = v0 | blend_lo;
    jal(pc(0x158, 0x160), gen::fn_RpSkyRenderStateSet_004d7f60);
    // the corners {x, y} at sp + 144 (+q): (x, y) (x + w, y) (x, y + h) (x + w, y + h)
    const s32 cb = 144 + q;
    swc1(F23, sp + cb);
    swc1(F22, sp + cb + 4);
    mtc1(s5, F0);
    cvt_s_w(F0, F0);
    add_s(F1, F23, F0);
    swc1(F1, sp + cb + 24);
    mtc1(s6, F0);
    cvt_s_w(F0, F0);
    add_s(F0, F22, F0);
    swc1(F0, sp + cb + 28);
    swc1(F1, sp + cb + 8);
    swc1(F22, sp + cb + 12);
    swc1(F23, sp + cb + 16);
    swc1(F0, sp + cb + 20);
    t0 = 0;
    v0 = lui(0x96);
    lwc1(F0, v0 + 136);
    sub_s(F5, F0, F21);  // z
    a2 = s4 & 1;  // the unsigned-convert idiom's low bits and integer views of the four channels
    mtc1(s4, F4);
    a1 = s3 & 1;
    mtc1(s3, F3);
    a0 = s2 & 1;
    mtc1(s2, F2);
    v1 = s1 & 1;
    mtc1(s1, F1);
    Gpr* const chan[4] = {&s4, &s3, &s2, &s1};
    Gpr* const low[4] = {&a2, &a1, &a0, &v1};
    const unsigned fchan[4] = {F4, F3, F2, F1};
    const s32 vtx = 176 + q;
    for (;;) {
        charge(3);
        v0 = slti(t0, 4);
        if (v0 == 0) break;
        backedge();
        charge(7);
        v0 = sll(t0, 6);
        v0 = addu(v0, sp);
        a3 = addiu(v0, vtx);
        swc1(F5, a3 + 8);
        swc1(F20, a3 + 24);
        for (u32 k = 0; k < 4; ++k) {
            if (sgn(*chan[k]) < 0) {  // never: the channels are bytes
                charge(6);
                v0 = srl(*chan[k], 1);
                v0 = v0 | *low[k];
                mtc1(v0, F0);
                cvt_s_w(F0, F0);
                add_s(F0, F0, F0);
            } else {
                charge(3);
                cvt_s_w(F0, fchan[k]);
            }
            charge(k == 3 ? 9 : 3);
            swc1(F0, a3 + 32 + 4 * k);
        }
        v0 = sll(t0, 3);
        v0 = addu(v0, sp);
        v0 = addiu(v0, cb);
        lwc1(F0, v0);
        swc1(F0, a3);
        lwc1(F0, v0 + 4);
        swc1(F0, a3 + 4);
        t0 = addiu(t0, 1);
    }
    if (textured) {
        charge(37);
        sw(sp + 208, zero);  // u, v: (0,0) (1,0) (0,1) (1,1)
        sw(sp + 212, zero);
        v0 = lui(0x3F80);
        sw(sp + 272, v0);
        sw(sp + 276, zero);
        sw(sp + 336, zero);
        sw(sp + 340, v0);
        sw(sp + 400, v0);
        sw(sp + 404, v0);
        a0 = 1;
        lw(a1, s7);
    } else {
        charge(27);
        a0 = 1;
        a1 = 0;
    }
    lw(v0, s0);
    jalr(pc(0x2E4, 0x310), v0.u());  // RwRenderStateSet(TEXTURERASTER, ..)
    a0 = 4;  // rwPRIMTYPETRISTRIP
    a1 = addiu(sp, vtx);
    a2 = a0;
    call_pfn(pc(0x300, 0x32C), kPfnIm2DRenderPrimitive);
    ld(ra, sp + 128 + q);
    if (textured) lq(s7, sp + 128);
    lq(s6, sp + 112);
    lq(s5, sp + 96);
    lq(s4, sp + 80);
    lq(s3, sp + 64);
    lq(s2, sp + 48);
    lq(s1, sp + 32);
    lq(s0, sp + 16);
    lwc1(F23, sp + 12);
    lwc1(F22, sp + 8);
    lwc1(F21, sp + 4);
    lwc1(F20, sp);
    sp = addiu(sp, frame);
}
void Cpu::sub_113A30() { menu_rect(0x113A30u, 68, 0x17FB, false); }
void Cpu::sub_113D80() { menu_rect(0x113D80u, 72, 0x1801, false); }
void Cpu::sub_1140D0() { menu_rect(0x1140D0u, 68, 0x17FB, true); }
void Cpu::sub_114AF0() { menu_rect(0x114AF0u, 72, 0x1801, true); }


// =========================================================================================================
// [quad] small Im2D panels
// =========================================================================================================

// The Im2D states the panels share: (state, value) pairs through RwRenderStateSet held in $s0, jalrs 0x14 apart.
void Cpu::im2d_states(const u32 (*states)[2], u32 n, u32 pc) {
    s0 = addiu(lui(0x96), 144);
    for (u32 k = 0; k < n; ++k) {
        a0 = states[k][0];
        a1 = states[k][1];
        lw(v0, s0);
        jalr(pc + 0x14 * k, v0.u());
    }
}

// sub_3B4B40(points, colours, point_idx, colour_idx): a gouraud quad (an Im2D fan) in the static vertex buffer
// 0x95AEC0: corner i at points[point_idx[i]] ({x in 1/16 px, y in 1/8 px}, 8 bytes) in colours[colour_idx[i]] (4 ints
// 0..255); texture off, gouraud, vertex alpha, blend src alpha / inv src alpha... (states 10 = 3, 11 = 6), alpha ref
// 68, blend 0x717FB.
void Cpu::sub_3B4B40() {
    enter(23);
    sp = addiu(sp, -80);
    sd(sp + 64, ra);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    s0 = a3;
    camera_get(0x3B4B68u);
    v1 = lui(0x3F80);
    mtc1(v1, F1);
    lwc1(F0, v0 + 128);
    div_s(F2, F1, F0);  // recipZ
    a3 = 0;
    a0 = addiu(lui(0x96), -20800);  // the vertex buffer 0x95AEC0
    v0 = lui(0x96);
    lwc1(F1, v0 + 136);  // the near screen z
    for (;;) {
        charge(3);
        v0 = slti(a3, 4);
        if (v0 == 0) break;
        backedge();
        charge(37);
        lbu(v0, s1);
        v0 = sll(v0, 3);
        a2 = addu(s3, v0);  // the point
        lbu(v0, s0);
        v0 = sll(v0, 4);
        a1 = addu(s2, v0);  // the colour
        v0 = sll(a3, 6);
        v1 = addu(a0, v0);  // the vertex
        lw(v0, a2);
        v0 = sra(v0, 4);
        mtc1(v0, F0);
        cvt_s_w(F0, F0);
        swc1(F0, v1);
        lw(v0, a2 + 4);
        v0 = sra(v0, 3);
        mtc1(v0, F0);
        cvt_s_w(F0, F0);
        swc1(F0, v1 + 4);
        swc1(F1, v1 + 8);
        for (u32 k = 0; k < 4; ++k) {
            lwc1(F0, a1 + 4 * k);
            cvt_s_w(F0, F0);
            swc1(F0, v1 + 32 + 4 * k);
        }
        swc1(F2, v1 + 24);
        a3 = addiu(a3, 1);
        s1 = addiu(s1, 1);
        s0 = addiu(s0, 1);
    }
    charge(52);
    static const u32 kStates[5][2] = {{1, 0}, {7, 2}, {12, 1}, {10, 3}, {11, 6}};
    im2d_states(kStates, 5, 0x3B4C50u);
    sky_states(0x3B4CB0u, 68, 0x17FB);
    a0 = 5;  // rwPRIMTYPETRIFAN
    a1 = addiu(lui(0x96), -20800);
    a2 = 4;
    call_pfn(0x3B4CE4u, kPfnIm2DRenderPrimitive);
    ld(ra, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 80);
}

// sub_139DC0 with $f12 = the depth offset: a black triangle in the lower right corner of the screen ((319, 448),
// (640, 448), (640, 328)), untextured.
void Cpu::sub_139DC0() {
    enter(86);
    sp = addiu(sp, -288);
    sd(sp + 32, ra);
    sq(sp + 16, s0);
    swc1(F21, sp + 4);
    swc1(F20, sp);
    mov_s(F21, F12);
    camera_get(0x139DD8u);
    v1 = lui(0x3F80);
    mtc1(v1, F1);
    lwc1(F0, v0 + 128);
    div_s(F20, F1, F0);
    static const u32 kStates[8][2] = {{6, 1}, {7, 2}, {8, 1}, {9, 1}, {12, 1}, {11, 6}, {10, 5}, {2, 4}};
    im2d_states(kStates, 8, 0x139E04u);
    sky_states(0x139EA0u, 68, 0x17FB);
    v0 = 319;
    mtc1(v0, F0);
    cvt_s_w(F0, F0);
    swc1(F0, sp + 64);
    a0 = lui(0x43E0);  // 448.0
    sw(sp + 68, a0);
    v1 = lui(0x4420);  // 640.0
    sw(sp + 72, v1);
    v0 = lui(0x43A4);  // 328.0
    sw(sp + 76, v0);
    sw(sp + 80, v1);
    sw(sp + 84, a0);
    a0 = 0;
    v0 = lui(0x96);
    lwc1(F1, v0 + 136);
    v0 = lui(0x3F80);
    mtc1(v0, F0);
    sub_s(F0, F21, F0);
    sub_s(F1, F1, F0);  // z = near z - (offset - 1)
    for (;;) {
        charge(3);
        v0 = slti(a0, 3);
        if (v0 == 0) break;
        backedge();
        charge(17);
        v0 = sll(a0, 6);
        v0 = addu(v0, sp);
        v1 = addiu(v0, 96);
        swc1(F1, v1 + 8);
        swc1(F20, v1 + 24);
        sw(v1 + 32, zero);
        sw(v1 + 36, zero);
        sw(v1 + 40, zero);
        sw(v1 + 44, zero);
        v0 = sll(a0, 3);
        v0 = addu(v0, sp);
        v0 = addiu(v0, 64);
        lwc1(F0, v0);
        swc1(F0, v1);
        lwc1(F0, v0 + 4);
        swc1(F0, v1 + 4);
        a0 = addiu(a0, 1);
    }
    charge(19);
    a0 = 1;
    a1 = 0;
    lw(v0, s0);
    jalr(0x139F74u, v0.u());
    a0 = 4;
    a1 = addiu(sp, 96);
    a2 = 3;
    call_pfn(0x139F90u, kPfnIm2DRenderPrimitive);
    ld(ra, sp + 32);
    lq(s0, sp + 16);
    lwc1(F21, sp + 4);
    lwc1(F20, sp);
    sp = addiu(sp, 288);
}


// =========================================================================================================
// [panel] battle / result screen panels drawn as quads of two Im2D triangles
// =========================================================================================================

// RwIm2DRenderTriangle(verts, 4, 0, 1, 2) and (verts, 4, 0, 2, 3) through the device pointer whose address
// `base` holds (jalrs at pc and pc + 0x20): one 4-vertex quad. `verts` = `reg` + off.
void Cpu::quad_triangles(const Gpr& reg, s32 off, Gpr& base, u32 pc) {
    for (u32 k = 0; k < 2; ++k) {
        a0 = addiu(reg, off);
        a1 = 4;
        a2 = 0;
        a3 = 1 + k;
        t0 = 2 + k;
        lw(v0, base);
        jalr(pc + 0x20 * k, v0.u());
    }
}
// The panel's work pointer (gp + slot), asserting (the file string, line) when it is null -- the assertion returns
// in retail and the panel draws from address 0.
void Cpu::panel_work_check(s32 slot, u32 file, u32 line, u32 pc) {
    lw(v0, gp + slot);
    if (v0 == 0) {
        charge(5);
        a0 = file;
        a1 = line;
        jal(pc, gen::fn_sub_19D3F0_0019d3f0);
    }
}
// RwRenderStateSet(TEXTURERASTER, sub_21CCE0(sub_21CCA0($a0 = page, id))): a battle-panel sprite raster (the page in
// $a0 from the caller), the raster jalr at pc.
void Cpu::panel_raster(u32 id, u32 pc_cca0, u32 pc_raster, bool via_s0) {
    a1 = id;
    jal(pc_cca0, gen::fn_sub_21CCA0_0021cca0);
    a0 = v0;
    jal(pc_cca0 + 0x0C, gen::fn_sub_21CCE0_0021cce0);
    a0 = 1;
    a1 = v0;
    if (via_s0)
        lw(v0, s0);
    else
        lw(v0, addiu(lui(0x96), 144));
    jalr(pc_raster, v0.u());
}

// sub_2720C0: a result-screen panel (work gp-18740): Z write / test off, linear filter, blend 0x717FB, alpha ref 68,
// no texture, the 4-vertex quad at work +16.
void Cpu::sub_2720C0() {
    enter(7);
    sp = addiu(sp, -48);
    sd(sp + 32, ra);
    sq(sp + 16, s1);
    sq(sp, s0);
    panel_work_check(-18740, w(addiu(lui(0x69), -4800)), 31, 0x2720E8u);
    charge(56);
    lw(s0, gp - 18740);
    s1 = addiu(lui(0x96), 144);
    const u32 states[3][3] = {{8, 0, 0x272108u}, {6, 0, 0x27211Cu}, {9, 2, 0x272130u}};
    for (const auto& st : states) {
        a0 = st[0];
        a1 = st[1];
        lw(v0, s1);
        jalr(st[2], v0.u());
    }
    a0 = 3;
    v0 = lui(0x7);
    a1 = v0 | 0x17FB;
    jal(0x272144u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 2;
    a1 = 68;
    jal(0x272154u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 1;
    a1 = 0;
    lw(v0, s1);
    jalr(0x272168u, v0.u());
    s1 = addiu(lui(0x96), 156);  // &RwIm2DRenderTriangle
    quad_triangles(s0, 16, s1, 0x272190u);
    ld(ra, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 48);
}

// sub_2532B0: a panel of N quads (work gp-18848: +0 flags -- drawn when bits 0 and 1 are both set --, +2896 the count,
// the quads 288 bytes apart from +16, vertices at +16 of each) with the battle-panel raster 76 of page 1.
void Cpu::sub_2532B0() {
    enter(9);
    sp = addiu(sp, -80);
    sd(sp + 64, ra);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    panel_work_check(-18848, w(addiu(lui(0x69), -5648)), 37, 0x2532E0u);
    charge(10);
    lw(s0, gp - 18848);
    a0 = 1;
    jal(0x2532F0u, gen::fn_sub_21C3F0_0021c3f0);
    a0 = v0;
    lw(v1, s0);
    a1 = nor_(v1, zero);
    v1 = a1 & 2;
    bool draw = false;
    if (v1 == 0) {
        charge(3);
        v1 = a1 & 1;
        draw = v1 == 0;
    }
    if (draw) {
        charge(24);
        panel_raster(76, 0x253320u, 0x253344u, false);
        a0 = 3;
        v0 = lui(0x7);
        a1 = v0 | 0x17FB;
        jal(0x253358u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(0x253368u, gen::fn_RpSkyRenderStateSet_004d7f60);
        s1 = 0;
        for (;;) {
            charge(4);
            lw(v1, s0 + 2896);
            v1 = slt(s1, v1);
            if (v1 == 0) break;
            backedge();
            charge(24);
            v0 = sll(s1, 3);
            v0 = addu(v0, s1);
            v0 = sll(v0, 5);
            v0 = addu(s0, v0);  // work + 288 * i
            s3 = addiu(v0, 16);
            s2 = addiu(lui(0x96), 156);
            quad_triangles(s3, 16, s2, 0x2533B0u);
            s1 = addiu(s1, 1);
        }
    }
    charge(8);
    ld(ra, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 80);
}

// sub_22C5A0: three quads (work gp-18920 +27136 / +27392 / +27648) with the battle-panel raster 66 of page 0.
void Cpu::sub_22C5A0() {
    enter(7);
    sp = addiu(sp, -48);
    sd(sp + 32, ra);
    sq(sp + 16, s1);
    sq(sp, s0);
    panel_work_check(-18920, w(addiu(lui(0x69), -7296)), 230, 0x22C5C8u);
    charge(82);
    lw(s1, gp - 18920);
    a0 = 0;
    jal(0x22C5D8u, gen::fn_sub_21C3F0_0021c3f0);
    a0 = v0;
    panel_raster(66, 0x22C5E8u, 0x22C60Cu, false);
    a0 = 3;
    v0 = lui(0x7);
    a1 = v0 | 0x17FB;
    jal(0x22C620u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 2;
    a1 = 68;
    jal(0x22C630u, gen::fn_RpSkyRenderStateSet_004d7f60);
    s0 = addiu(lui(0x96), 156);
    quad_triangles(s1, 27136, s0, 0x22C658u);
    quad_triangles(s1, 27392, s0, 0x22C698u);
    quad_triangles(s1, 27648, s0, 0x22C6D8u);
    ld(ra, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 48);
}

// sub_27B880: a battle panel quad (work gp-18700: drawn when bit 0 of +0 is set; vertices at +16) with linear filter,
// cull mode 2, Z write / test off, the battle-panel raster 58 of page 2.
void Cpu::sub_27B880() {
    enter(8);
    sp = addiu(sp, -64);
    sd(sp + 48, ra);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    panel_work_check(-18700, w(addiu(lui(0x69), -4152)), 39, 0x27B8ACu);
    charge(10);
    lw(s1, gp - 18700);
    a0 = 2;
    jal(0x27B8BCu, gen::fn_sub_21C3F0_0021c3f0);
    s2 = v0;
    lw(v1, s1);
    v1 = nor_(v1, zero);
    v1 = v1 & 1;
    if (v1 == 0) {
        charge(61);
        s0 = addiu(lui(0x96), 144);
        const u32 states[4][3] = {{9, 2, 0x27B8F0u}, {20, 2, 0x27B904u}, {8, 0, 0x27B918u}, {6, 0, 0x27B92Cu}};
        for (const auto& st : states) {
            a0 = st[0];
            a1 = st[1];
            lw(v0, s0);
            jalr(st[2], v0.u());
        }
        a0 = s2;
        panel_raster(58, 0x27B93Cu, 0x27B95Cu, true);
        a0 = 3;
        v0 = lui(0x7);
        a1 = v0 | 0x17FB;
        jal(0x27B970u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(0x27B980u, gen::fn_RpSkyRenderStateSet_004d7f60);
        s0 = addiu(lui(0x96), 156);
        quad_triangles(s1, 16, s0, 0x27B9A8u);
    }
    charge(7);
    ld(ra, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 64);
}

// sub_23C8C0(verts): two quads (verts, verts + 256) with the sprite raster of sub_20E590(1): linear filter, cull 2,
// no Z, blend 0x71801, alpha ref 72.
void Cpu::sub_23C8C0() {
    enter(84);
    sp = addiu(sp, -48);
    sd(sp + 32, ra);
    sq(sp + 16, s1);
    sq(sp, s0);
    s1 = a0;
    static const u32 kStates[4][2] = {{9, 2}, {20, 2}, {8, 0}, {6, 0}};
    im2d_states(kStates, 4, 0x23C8E8u);
    a0 = 3;
    v0 = lui(0x7);
    a1 = v0 | 0x1801;
    jal(0x23C938u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 2;
    a1 = 72;
    jal(0x23C948u, gen::fn_RpSkyRenderStateSet_004d7f60);
    a0 = 1;
    jal(0x23C954u, gen::fn_sub_20E590_0020e590);
    a0 = 1;
    a1 = v0;
    lw(v0, s0);
    jalr(0x23C968u, v0.u());
    s0 = addiu(lui(0x96), 156);
    quad_triangles(s1, 0, s0, 0x23C990u);
    quad_triangles(s1, 256, s0, 0x23C9D0u);
    ld(ra, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 48);
}

// sub_411EE0(?, work): five text glyph slots of the work's +12 records (20 bytes: s16 +4 / +6 position in 1/16 px,
// s16 +12 the glyph (0 = empty)) drawn through sub_40E420 with the colours of the table 0x6B0050 (copied to the
// stack); the fourth slot first draws a backing panel (sub_40D610(258, 29, 128, 2, 0, 1), Z write on / test off,
// blend 0x3200D, then Z write off / test on, blend 0x7000D). Alpha ref 68 and blend 0x717FB at the end.
void Cpu::sub_411EE0() {
    enter(11);
    sp = addiu(sp, -112);
    sd(sp + 64, ra);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    lw(s2, a1 + 12);
    a1 = addiu(lui(0x6B), 80);  // the colours 0x6B0050
    a0 = addiu(sp, 80);
    v1 = 5;
    for (;;) {
        charge(7);
        lw(v0, a1);
        a1 = addiu(a1, 4);
        v1 = addiu(v1, -1);
        sw(a0, v0);
        a0 = addiu(a0, 4);
        if (sgn(v1) <= 0) break;
        backedge();
    }
    charge(3);
    s3 = 0;
    for (;;) {
        charge(3);
        v0 = slti(s3, 5);
        if (v0 == 0) break;
        backedge();
        charge(7);
        v0 = sll(s3, 2);
        v0 = addu(v0, s3);
        v0 = sll(v0, 2);
        s1 = addu(s2, v0);  // the slot (20 bytes)
        lh(v0, s1 + 12);
        if (v0 != 0) {
            charge(3);
            v0 = 3;
            if (s3 == v0) {
                charge(41);
                s0 = addiu(lui(0x96), 144);
                a0 = 8;
                a1 = 1;
                lw(v0, s0);
                jalr(0x411F70u, v0.u());
                a0 = 6;
                a1 = 0;
                lw(v0, s0);
                jalr(0x411F84u, v0.u());
                a0 = 3;
                v0 = lui(0x3);
                a1 = v0 | 0x200D;
                jal(0x411F98u, gen::fn_RpSkyRenderStateSet_004d7f60);
                mtc1(zero, F12);
                a0 = 258;
                a1 = 29;
                a2 = 128;
                a3 = 2;
                t0 = 0;
                t1 = 1;
                jal(0x411FBCu, gen::fn_sub_40D610_0040d610);
                a0 = 8;
                a1 = 0;
                lw(v0, s0);
                jalr(0x411FD0u, v0.u());
                a0 = 6;
                a1 = 1;
                lw(v0, s0);
                jalr(0x411FE4u, v0.u());
                a0 = 3;
                v0 = lui(0x7);
                a1 = v0 | 0xD;
                jal(0x411FF8u, gen::fn_RpSkyRenderStateSet_004d7f60);
            }
            charge(18);
            lh(v0, s1 + 4);
            a0 = sra(v0, 4);
            lh(v0, s1 + 6);
            a1 = sra(v0, 4);
            v0 = lui(0x3F80);
            mtc1(v0, F12);
            lbu(a2, s1 + 12);
            v0 = sll(s3, 2);
            v0 = addu(v0, sp);
            lw(a3, v0 + 80);
            mtc1(zero, F13);
            t0 = 0;
            t1 = 0;
            t2 = 0;
            lwc1(F14, gp - 32248);
            mov_s(F15, F14);
            jal(0x412040u, gen::fn_sub_40E420_0040e420);
        }
        charge(1);
        s3 = addiu(s3, 1);
    }
    charge(18);
    sky_states(0x412060u, 68, 0x17FB);
    v0 = 0;
    ld(ra, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 112);
}


// sub_25BBF0: three pairs of quads (work gp-18828, drawn when bit 0 of +0 is set: pair i at +16 + 256 i and +784 +
// 256 i) each with the sprite raster of sub_20E610(i); the sky states are set twice (0x717FB / 68, then 0x71801 / 72).
void Cpu::sub_25BBF0() {
    enter(11);
    sp = addiu(sp, -112);
    sd(sp + 96, ra);
    sq(sp + 80, s5);
    sq(sp + 64, s4);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    lw(v1, gp - 18828);
    if (v1 == 0) {
        charge(5);
        a0 = addiu(lui(0x69), -5176);
        a1 = 43;
        jal(0x25BC28u, gen::fn_sub_19D3F0_0019d3f0);
    }
    charge(6);
    lw(s3, gp - 18828);
    lw(v1, s3);
    v1 = nor_(v1, zero);
    v1 = v1 & 1;
    if (v1 == 0) {
        charge(43);
        s2 = addiu(lui(0x96), 144);
        const u32 states[4][3] = {{9, 2, 0x25BC5Cu}, {20, 2, 0x25BC70u}, {8, 0, 0x25BC84u}, {6, 0, 0x25BC98u}};
        for (const auto& st : states) {
            a0 = st[0];
            a1 = st[1];
            lw(v0, s2);
            jalr(st[2], v0.u());
        }
        a0 = 3;
        v0 = lui(0x7);
        a1 = v0 | 0x17FB;
        jal(0x25BCACu, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 68;
        jal(0x25BCBCu, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 3;
        v0 = lui(0x7);
        a1 = v0 | 0x1801;
        jal(0x25BCD0u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 72;
        jal(0x25BCE0u, gen::fn_RpSkyRenderStateSet_004d7f60);
        s5 = 0;
        for (;;) {
            charge(3);
            v1 = slti(s5, 3);
            if (v1 == 0) break;
            backedge();
            charge(47);
            a0 = s5;
            jal(0x25BCF8u, gen::fn_sub_20E610_0020e610);
            a0 = 1;
            a1 = v0;
            lw(v0, s2);
            jalr(0x25BD0Cu, v0.u());
            v0 = sll(s5, 8);
            s1 = addu(s3, v0);
            s4 = addiu(s1, 16);
            s0 = addiu(lui(0x96), 156);
            quad_triangles(s4, 0, s0, 0x25BD40u);
            s1 = addiu(s1, 784);
            quad_triangles(s1, 0, s0, 0x25BD84u);
            s5 = addiu(s5, 1);
        }
    }
    charge(10);
    ld(ra, sp + 96);
    lq(s5, sp + 80);
    lq(s4, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 112);
}

// sub_2520F0: three quads (work gp-18852 +16 / +272 / +528, drawn when bit 0 of +0 is set; bit 1 first runs
// sub_252340) with the battle-panel raster 57 (+8 == 0) or 58 (+8 == 1) of page 1; blend 0x71801, alpha ref 72.
void Cpu::sub_2520F0() {
    enter(9);
    sp = addiu(sp, -80);
    sd(sp + 64, ra);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    panel_work_check(-18852, w(addiu(lui(0x69), -5664)), 54, 0x252120u);
    charge(10);
    lw(s1, gp - 18852);
    a0 = 1;
    jal(0x252130u, gen::fn_sub_21C3F0_0021c3f0);
    s3 = v0;
    lw(a0, s1);
    v1 = nor_(a0, zero);
    v1 = v1 & 1;
    if (v1 == 0) {
        charge(3);
        v0 = a0 & 2;
        if (v0 != 0) {
            charge(2);
            jal(0x25215Cu, gen::fn_sub_252340_00252340);
        }
        charge(26);
        s0 = addiu(lui(0x96), 144);
        const u32 states[4][3] = {{9, 2, 0x252178u}, {20, 2, 0x25218Cu}, {8, 0, 0x2521A0u}, {6, 0, 0x2521B4u}};
        for (const auto& st : states) {
            a0 = st[0];
            a1 = st[1];
            lw(v0, s0);
            jalr(st[2], v0.u());
        }
        lw(v1, s1 + 8);
        v0 = 1;
        if (v1 == v0) {
            charge(5);
            a0 = s3;
            a1 = 58;
            jal(0x252200u, gen::fn_sub_21CCA0_0021cca0);
            s2 = v0;
        } else {
            charge(2);
            if (v1 == 0) {
                charge(7);
                a0 = s3;
                a1 = 57;
                jal(0x2521E4u, gen::fn_sub_21CCA0_0021cca0);
                s2 = v0;
            } else {
                charge(2);  // (any other value keeps the caller's $s2)
            }
        }
        charge(67);
        a0 = s2;
        jal(0x252210u, gen::fn_sub_21CCE0_0021cce0);
        a0 = 1;
        a1 = v0;
        lw(v0, s0);
        jalr(0x252224u, v0.u());
        a0 = 3;
        v0 = lui(0x7);
        a1 = v0 | 0x1801;
        jal(0x252238u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 2;
        a1 = 72;
        jal(0x252248u, gen::fn_RpSkyRenderStateSet_004d7f60);
        s0 = addiu(lui(0x96), 156);
        quad_triangles(s1, 16, s0, 0x252270u);
        quad_triangles(s1, 272, s0, 0x2522B0u);
        quad_triangles(s1, 528, s0, 0x2522F0u);
    }
    charge(8);
    ld(ra, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 80);
}


// =========================================================================================================
// [capture] the screen-capture fade task (work: +0 state, +2 the duration, +4 the frame, +8 the 512 x 256 raster,
// +12 its camera)
// =========================================================================================================

// sub_351290(work): renders the frame buffer raster (sub_4E3630) into the capture camera (+12) as a 512 x 256 copy:
// two Im2D strips side by side (u scaled by 640 / raster width, v by 448 / raster height), alpha ref 8228, blend
// 0x717FB, fog / Z off, linear filter, vertex alpha, clamp. Returns 1, or 0 when the camera's BeginUpdate fails.
void Cpu::sub_351290() {
    enter(13);
    sp = addiu(sp, -336);
    sd(sp + 64, ra);
    sq(sp + 48, s2);
    sq(sp + 32, s1);
    sq(sp + 16, s0);
    swc1(F21, sp + 4);
    swc1(F20, sp);
    s2 = a0;
    lw(a0, a0 + 12);
    jal(0x3512B4u, gen::fn_RwCameraBeginUpdate_004c9d10);
    if (v0 == 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(133);
        jal(0x3512D0u, gen::fn_sub_4E3630_004e3630);  // the frame-buffer raster
        s1 = v0;
        lwc1(F0, v0 + 12);
        cvt_s_w(F1, F0);
        v1 = lui(0x4420);
        mtc1(v1, F0);
        div_s(F21, F0, F1);  // 640 / width
        lwc1(F0, v0 + 16);
        cvt_s_w(F1, F0);
        v0 = lui(0x43E0);
        mtc1(v0, F0);
        div_s(F20, F0, F1);  // 448 / height
        a0 = 2;
        a1 = 8228;
        jal(0x351318u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 3;
        v0 = lui(0x7);
        a1 = v0 | 0x17FB;
        jal(0x35132Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
        capture_states(0x351348u, s1);
        v0 = lui(0x96);
        lwc1(F2, v0 + 140);  // the far screen z
        lw(v1, s2 + 12);
        v0 = lui(0x3F80);
        mtc1(v0, F1);
        lwc1(F0, v1 + 132);
        div_s(F0, F1, F0);  // recipZ = 1 / far plane
        // four vertices at sp + 80 .. 320: (0,0) (0,256) (512,0) (512,256), white, uv (0,0) (0,v) (u,0) (u,v)
        sw(sp + 80, zero);
        sw(sp + 84, zero);
        swc1(F2, sp + 88);
        a0 = lui(0x437F);  // 255.0
        sw(sp + 112, a0);
        sw(sp + 116, a0);
        sw(sp + 120, a0);
        sw(sp + 124, a0);
        swc1(F0, sp + 104);
        sw(sp + 96, zero);
        sw(sp + 100, zero);
        sw(sp + 144, zero);
        v1 = lui(0x4380);  // 256.0
        sw(sp + 148, v1);
        swc1(F2, sp + 152);
        sw(sp + 176, a0);
        sw(sp + 180, a0);
        sw(sp + 184, a0);
        sw(sp + 188, a0);
        swc1(F0, sp + 168);
        sw(sp + 160, zero);
        swc1(F20, sp + 164);
        v0 = lui(0x4400);  // 512.0
        sw(sp + 208, v0);
        sw(sp + 212, zero);
        swc1(F2, sp + 216);
        sw(sp + 240, a0);
        sw(sp + 244, a0);
        sw(sp + 248, a0);
        sw(sp + 252, a0);
        swc1(F0, sp + 232);
        swc1(F21, sp + 224);
        sw(sp + 228, zero);
        sw(sp + 272, v0);
        sw(sp + 276, v1);
        swc1(F2, sp + 280);
        sw(sp + 304, a0);
        sw(sp + 308, a0);
        sw(sp + 312, a0);
        sw(sp + 316, a0);
        swc1(F0, sp + 296);
        swc1(F21, sp + 288);
        swc1(F20, sp + 292);
        a0 = 4;  // rwPRIMTYPETRISTRIP
        a1 = addiu(sp, 80);
        a2 = a0;
        call_pfn(0x3514B8u, kPfnIm2DRenderPrimitive);
        a0 = 1;
        a1 = 0;
        lw(v0, s0);
        jalr(0x3514CCu, v0.u());
        lw(a0, s2 + 12);
        jal(0x3514D8u, gen::fn_RwCameraEndUpdate_004c9d00);
        v0 = 1;
    }
    charge(9);
    ld(ra, sp + 64);
    lq(s2, sp + 48);
    lq(s1, sp + 32);
    lq(s0, sp + 16);
    lwc1(F21, sp + 4);
    lwc1(F20, sp);
    sp = addiu(sp, 336);
}

// The capture states: fog / Z test / Z write off, linear filter, vertex alpha, the raster `raster`, clamp (states 3
// and 4 = 3); the device pointer in $s0, jalrs 0x14 apart from pc.
void Cpu::capture_states(u32 pc, const Gpr& raster) {
    s0 = addiu(lui(0x96), 144);
    const u32 states[5][2] = {{14, 0}, {6, 0}, {8, 0}, {9, 2}, {12, 1}};
    u32 k = 0;
    for (const auto& st : states) {
        a0 = st[0];
        a1 = st[1];
        lw(v0, s0);
        jalr(pc + 0x14 * k++, v0.u());
    }
    a0 = 1;
    a1 = raster;
    lw(v0, s0);
    jalr(pc + 0x14 * k++, v0.u());
    a0 = 3;
    a1 = a0;
    lw(v0, s0);
    jalr(pc + 0x14 * k++, v0.u());
    a0 = 4;
    a1 = 3;
    lw(v0, s0);
    jalr(pc + 0x14 * k, v0.u());
}

// sub_351510(work): the captured frame over the screen, fading out: alpha = 255 * (1 - frame / duration) (the float
// to unsigned conversion of the compiler, & 0xFF), a full-screen strip with the capture raster (camera +96).
void Cpu::sub_351510() {
    enter(14);
    sp = addiu(sp, -336);
    sd(sp + 64, ra);
    sq(sp + 48, s2);
    sq(sp + 32, s1);
    sq(sp + 16, s0);
    swc1(F20, sp);
    s0 = a0;
    camera_begin(0x35152Cu, 0x351538u);
    if (v0 != 0) {
        charge(3);
        lhu(v0, s0 + 4);
        u8_to_float(F0, F1);
        charge(3);
        lhu(v0, s0 + 2);
        u8_to_float(F0, F0);
        charge(17);
        div_s(F1, F1, F0);
        v0 = lui(0x3F80);
        mtc1(v0, F0);
        sub_s(F1, F0, F1);
        v0 = lui(0x437F);
        mtc1(v0, F0);
        mul_s(F1, F0, F1);
        v0 = lui(0x4F00);  // 2^31: the unsigned conversion
        mtc1(v0, F0);
        c_le_s(F0, F1);
        if (cop1_cond()) {
            charge(6);
            sub_s(F0, F1, F0);
            cvt_w_s(F0, F0);
            mfc1(v1, F0);
            v0 = lui(0x8000);
            v1 = v1 | v0;
            v1 = v1 & 0xFF;
        } else {
            charge(6);
            cvt_w_s(F0, F1);
            mfc1(v1, F0);
            v1 = v1 & 0xFF;
        }
        charge(71);
        s1 = v1 & 0xFF;  // the alpha
        lw(v0, s0 + 12);
        lw(s2, v0 + 96);  // the capture raster
        sky_states(0x351648u, 68, 0x17FB);
        capture_states(0x351678u, s2);
        v0 = lui(0x96);
        lwc1(F20, v0 + 140);
        camera_get(0x351714u);
        v1 = lui(0x3F80);
        mtc1(v1, F1);
        lwc1(F0, v0 + 132);
        div_s(F1, F1, F0);
        sw(sp + 80, zero);
        sw(sp + 84, zero);
        swc1(F20, sp + 88);
        v0 = lui(0x437F);
        sw(sp + 112, v0);
        sw(sp + 116, v0);
        sw(sp + 120, v0);
        u2f(s1, v1, v0, F0, F0);
        charge(14);
        swc1(F0, sp + 124);
        swc1(F1, sp + 104);
        sw(sp + 96, zero);
        sw(sp + 100, zero);
        sw(sp + 144, zero);
        v0 = lui(0x43E0);
        sw(sp + 148, v0);
        swc1(F20, sp + 152);
        v0 = lui(0x437F);
        sw(sp + 176, v0);
        sw(sp + 180, v0);
        sw(sp + 184, v0);
        u2f(s1, v1, v0, F0, F0);
        charge(15);
        swc1(F0, sp + 188);
        swc1(F1, sp + 168);
        sw(sp + 160, zero);
        v0 = lui(0x3F80);
        sw(sp + 164, v0);
        v0 = lui(0x4420);
        sw(sp + 208, v0);
        sw(sp + 212, zero);
        swc1(F20, sp + 216);
        v0 = lui(0x437F);
        sw(sp + 240, v0);
        sw(sp + 244, v0);
        sw(sp + 248, v0);
        u2f(s1, v1, v0, F0, F0);
        charge(16);
        swc1(F0, sp + 252);
        swc1(F1, sp + 232);
        v0 = lui(0x3F80);
        sw(sp + 224, v0);
        sw(sp + 228, zero);
        v0 = lui(0x4420);
        sw(sp + 272, v0);
        v0 = lui(0x43E0);
        sw(sp + 276, v0);
        swc1(F20, sp + 280);
        v0 = lui(0x437F);
        sw(sp + 304, v0);
        sw(sp + 308, v0);
        sw(sp + 312, v0);
        u2f(s1, v1, v0, F0, F0);
        charge(22);
        swc1(F0, sp + 316);
        swc1(F1, sp + 296);
        v0 = lui(0x3F80);
        sw(sp + 288, v0);
        sw(sp + 292, v0);
        a0 = 4;
        a1 = addiu(sp, 80);
        a2 = a0;
        call_pfn(0x3518ECu, kPfnIm2DRenderPrimitive);
        a0 = 1;
        a1 = 0;
        lw(v0, s0);
        jalr(0x351900u, v0.u());
        camera_end(0x351908u, 0x351914u);
    }
    charge(8);
    ld(ra, sp + 64);
    lq(s2, sp + 48);
    lq(s1, sp + 32);
    lq(s0, sp + 16);
    lwc1(F20, sp);
    sp = addiu(sp, 336);
}

// sub_351940(work): releases the capture camera (+12: its frame detached and destroyed, its z raster (+100) and its
// raster (+96) unlinked, the camera destroyed) and the capture raster (+8: uncached from the texture cache, destroyed).
void Cpu::sub_351940() {
    enter(8);
    sp = addiu(sp, -48);
    sd(sp + 32, ra);
    sq(sp + 16, s1);
    sq(sp, s0);
    s0 = a0;
    lw(a0, a0 + 12);
    if (a0 != 0) {
        charge(3);
        lw(s1, a0 + 4);
        if (s1 != 0) {
            charge(6);
            a1 = 0;
            jal(0x351970u, gen::fn_sub_4D1840_004d1840);
            a0 = s1;
            jal(0x35197Cu, gen::fn_sub_4CAF80_004caf80);
        }
        charge(5);
        lw(v1, s0 + 12);
        v0 = addiu(v1, 100);
        lw(a0, v1 + 100);
        if (a0 != 0) {
            charge(3);
            sw(v0, zero);
            jal(0x35199Cu, gen::fn_sub_4CDE90_004cde90);
        }
        charge(5);
        lw(v0, s0 + 12);
        v1 = addiu(v0, 96);
        lw(v0, v0 + 96);
        if (v0 != 0) {
            charge(1);
            sw(v1, zero);
        }
        charge(4);
        lw(a0, s0 + 12);
        jal(0x3519C0u, gen::fn_sub_4CA030_004ca030);
        sw(s0 + 12, zero);
    }
    charge(3);
    lw(a0, s0 + 8);
    if (a0 != 0) {
        charge(7);
        a1 = 0;
        jal(0x3519DCu, gen::fn_sub_4F1780_004f1780);
        lw(a0, s0 + 8);
        jal(0x3519E8u, gen::fn_sub_4CDE90_004cde90);
        sw(s0 + 8, zero);
    }
    charge(6);
    ld(ra, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 48);
}

// sub_351A10(task): the capture fade's states (work = task +60, +0): 1 create the camera (sub_4CA090), its frame
// (sub_4CAF10 + sub_4D1840) and the 512 x 256 raster (sub_4CE0F0(512, 256, 16, 389), cached, the camera's raster and
// frame buffer set), then 2 capture (sub_351290; a failure keeps the state), 3 draw the fade (sub_351510) frame by
// frame until +4 reaches the duration +2, 4 release (sub_351940) and back to 0. Returns 0.
void Cpu::sub_351A10() {
    enter(8);
    sp = addiu(sp, -32);
    sd(sp + 16, ra);
    sq(sp, s0);
    lw(s0, a0 + 60);
    lbu(v1, s0);
    v0 = 4;
    const auto epilogue = [&] {
        charge(5);
        ld(ra, sp + 16);
        lq(s0, sp);
        sp = addiu(sp, 32);
    };
    const auto fail = [&] {
        charge(3);
        v0 = 0;
        epilogue();
    };
    int stage = 0;  // 1 / 2 / 3: where the state's code starts (they fall through into each other)
    if (v1 == v0) {
        charge(4);
        a0 = s0;
        jal(0x351B8Cu, gen::fn_sub_351940_00351940);
        sb(s0, zero);
    } else {
        charge(3);
        v0 = 3;
        if (v1 == v0) {
            stage = 3;
        } else {
            charge(3);
            v0 = 2;
            if (v1 == v0) {
                stage = 2;
            } else {
                charge(3);
                v0 = 1;
                if (v1 == v0) {
                    stage = 1;
                } else {
                    charge(2);
                    if (v1 == 0) return fail();
                    charge(2);
                }
            }
        }
    }
    if (stage == 1) {
        charge(5);
        jal(0x351A70u, gen::fn_sub_4CA090_004ca090);  // [RwCameraCreate]
        sw(s0 + 12, v0);
        if (v0 == 0) return fail();
        charge(10);
        jal(0x351A90u, gen::fn_sub_4CAF10_004caf10);  // [RwFrameCreate]
        lw(a0, s0 + 12);
        a1 = v0;
        jal(0x351AA0u, gen::fn_sub_4D1840_004d1840);  // [_rwObjectHasFrameSetFrame]
        lw(v0, s0 + 12);
        lw(v0, v0 + 4);
        if (v0 == 0) return fail();
        charge(9);
        a0 = 512;
        a1 = 256;
        a2 = 16;
        a3 = 389;
        jal(0x351AD4u, gen::fn_sub_4CE0F0_004ce0f0);  // [RwRasterCreate]
        sw(s0 + 8, v0);
        if (v0 == 0) return fail();
        charge(12);
        a0 = v0;
        a1 = 1;
        jal(0x351AFCu, gen::fn_sub_4F1780_004f1780);
        lw(a0, s0 + 12);
        a1 = 2;
        jal(0x351B0Cu, gen::fn_sub_4C9F00_004c9f00);
        lw(v1, s0 + 8);
        lw(v0, s0 + 12);
        sw(v0 + 96, v1);
        sh(s0 + 4, zero);
        stage = 2;
    }
    if (stage == 2) {
        charge(5);
        a0 = s0;
        jal(0x351B28u, gen::fn_sub_351290_00351290);
        if (v0 == 0) return fail();
        charge(2);
        v0 = 3;
        sb(s0, v0);
        stage = 3;
    }
    if (stage == 3) {
        charge(11);
        a0 = s0;
        jal(0x351B50u, gen::fn_sub_351510_00351510);
        lhu(v0, s0 + 4);
        v0 = addiu(v0, 1);
        sh(s0 + 4, v0);
        v1 = v0 & 0xFFFF;
        lhu(v0, s0 + 2);
        v0 = slt(v1, v0);
        if (v0 == 0) {
            charge(4);
            v0 = 4;
            sb(s0, v0);
        }
    }
    charge(1);
    v0 = 0;
    epilogue();
}


// =========================================================================================================
// [im3d] event line objects and the Im3D model
// =========================================================================================================

// 64 bytes from $a2 to $a1, two words a step ($a0 = 8 counts down; $v1 / $v0 the scratch).
void Cpu::copy_matrix_words() {
    for (;;) {
        charge(9);
        lw(v1, a2);
        lw(v0, a2 + 4);
        a2 = addiu(a2, 8);
        a0 = addiu(a0, -1);
        sw(a1, v1);
        sw(a1 + 4, v0);
        a1 = addiu(a1, 8);
        if (sgn(a0) <= 0) break;
        backedge();
    }
}

// sub_41BF80(obj): an event line object (+0 flags (bit 0: the matrix +16 is camera-relative, multiplied by the main
// camera's frame LTM), +4 the Im3D vertices, +8 their count, +12 -> the raster, +16 the matrix): linear filter, cull 2,
// no Z, no fog, vertex alpha, gouraud, blend 5 / 6, the raster, alpha ref 72, blend 0x71801; RwIm3DTransform(verts,
// n, matrix, 1) then RwIm3DRenderPrimitive(line list) and RwIm3DEnd.
void Cpu::sub_41BF80() {
    enter(71);
    sp = addiu(sp, -112);
    sd(sp + 32, ra);
    sq(sp + 16, s1);
    sq(sp, s0);
    s1 = a0;
    static const u32 kStates[9][2] = {{9, 2}, {20, 2}, {8, 0}, {6, 0}, {14, 0}, {12, 1}, {7, 2}, {10, 5}, {11, 6}};
    im2d_states(kStates, 9, 0x41BFA8u);
    lw(v0, s1 + 12);
    a0 = 1;
    lw(a1, v0);
    lw(v0, s0);
    jalr(0x41C060u, v0.u());
    sky_states(0x41C070u, 72, 0x1801);
    lw(v0, s1);
    v0 = v0 & 1;
    if (v0 != 0) {
        charge(10);
        camera_get(0x41C09Cu);
        lw(v0, v0 + 4);
        a2 = addiu(v0, 16);  // the camera frame's matrix
        a0 = addiu(sp, 48);
        lw(a1, s1 + 16);
        jal(0x41C0B4u, gen::fn_sub_4C2F30_004c2f30);  // [RwMatrixMultiply]
    } else {
        charge(3);
        lw(a2, s1 + 16);
        a1 = addiu(sp, 48);
        a0 = 8;
        copy_matrix_words();
    }
    charge(8);
    lhu(a1, s1 + 8);
    lw(a0, s1 + 4);
    a2 = addiu(sp, 48);
    a3 = 1;
    jal(0x41C104u, gen::fn_sub_4F1ED0_004f1ed0);  // [RwIm3DTransform]
    if (v0 != 0) {
        charge(5);
        a0 = 4;  // rwPRIMTYPETRISTRIP
        jal(0x41C118u, gen::fn_sub_4F2150_004f2150);  // [RwIm3DRenderPrimitive]
        jal(0x41C120u, gen::fn_sub_4F1F80_004f1f80);  // [RwIm3DEnd]
    }
    charge(6);
    ld(ra, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 112);
}

// sub_20D500(obj, matrix): an Im3D mesh (obj +4: 68 vertices) through the shared index list 0x875A90 (312 indices,
// a tri list): with obj bit 0 the matrix is copied into a new RwMatrix and turned 180 degrees about the axis
// 0x68E108 (RwMatrixRotate), destroyed afterwards; the texture cleared.
void Cpu::sub_20D500() {
    enter(17);
    sp = addiu(sp, -80);
    sd(sp + 48, ra);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    s2 = a0;
    s1 = a1;
    v0 = lui(0x69);
    ld(v1, v0 - 7928);  // the axis 0x68E108
    v0 = lui(0x69);
    lwc1(F0, v0 - 7920);
    sd(sp + 64, v1);
    swc1(F0, sp + 72);
    lw(v0, a0);
    v0 = v0 & 1;
    if (v0 != 0) {
        charge(5);
        jal(0x20D544u, gen::fn_sub_4C38C0_004c38c0);  // [RwMatrixCreate]
        s0 = v0;
        a0 = 8;
        a1 = s0;
        for (;;) {
            charge(9);
            lw(v1, s1);
            lw(v0, s1 + 4);
            s1 = addiu(s1, 8);
            a0 = addiu(a0, -1);
            sw(a1, v1);
            sw(a1 + 4, v0);
            a1 = addiu(a1, 8);
            if (sgn(a0) <= 0) break;
            backedge();
        }
        charge(9);
        v0 = lui(0x4334);  // 180.0
        mtc1(v0, F12);
        a0 = s0;
        a1 = addiu(sp, 64);
        a2 = 1;
        jal(0x20D590u, gen::fn_sub_4C31B0_004c31b0);  // [RwMatrixRotate](m, axis, 180, pre-concat)
    } else {
        charge(1);
        s0 = s1;
    }
    charge(24);
    a0 = addiu(s2, 4);
    a1 = 68;
    a2 = s0;
    a3 = 3;
    jal(0x20D5B4u, gen::fn_sub_4F1ED0_004f1ed0);
    a0 = 1;
    a1 = 0;
    call_pfn(0x20D5CCu, kPfnRenderStateSet);
    a0 = 3;
    a1 = addiu(lui(0x87), 23184);  // the index list 0x875A90
    a2 = 312;
    jal(0x20D5E4u, gen::fn_sub_4F1FD0_004f1fd0);  // [RwIm3DRenderIndexedPrimitive]
    jal(0x20D5ECu, gen::fn_sub_4F1F80_004f1f80);
    lw(v1, s2);
    v1 = v1 & 1;
    if (v1 != 0) {
        charge(3);
        a0 = s0;
        jal(0x20D608u, gen::fn_sub_4C3880_004c3880);  // [RwMatrixDestroy]
    }
    charge(7);
    ld(ra, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 80);
}

}  // namespace rg2

// --- the public entry points: arguments into $a0.., the body, $v0 ---
namespace {
inline void set(EEContext& ctx, unsigned r, u64 v) { ee::core::set_gpr64(ctx, r, v); }
inline u64 v0(const EEContext& ctx) { return ee::core::gpr64(ctx, GPR_V0); }
}  // namespace

void sub_3294D0(EEContext& ctx) { rg2::Cpu(ctx).sub_3294D0(); }
void sub_329550(EEContext& ctx) { rg2::Cpu(ctx).sub_329550(); }
void sub_3295C0(EEContext& ctx, u64 clamp) {
    set(ctx, GPR_A0, clamp);
    rg2::Cpu(ctx).sub_3295C0();
}
void sub_329630(EEContext& ctx) { rg2::Cpu(ctx).sub_329630(); }
void sub_34ADA0(EEContext& ctx, u64 obj) {
    set(ctx, GPR_A0, obj);
    rg2::Cpu(ctx).sub_34ADA0();
}
void sub_34A800(EEContext& ctx, u64 obj) {
    set(ctx, GPR_A0, obj);
    rg2::Cpu(ctx).sub_34A800();
}
void sub_349A30(EEContext& ctx, u64 obj) {
    set(ctx, GPR_A0, obj);
    rg2::Cpu(ctx).sub_349A30();
}
void sub_348DA0(EEContext& ctx, u64 params, u64 raster_ref) {
    set(ctx, GPR_A0, params);
    set(ctx, GPR_A1, raster_ref);
    rg2::Cpu(ctx).sub_348DA0();
}
void sub_34B010(EEContext& ctx, u64 obj) {
    set(ctx, GPR_A0, obj);
    rg2::Cpu(ctx).sub_34B010();
}
void sub_349D30(EEContext& ctx, u64 obj) {
    set(ctx, GPR_A0, obj);
    rg2::Cpu(ctx).sub_349D30();
}
u64 kwlnRootUpdate2DDrawBeginTask(EEContext& ctx, u64 task) {
    set(ctx, GPR_A0, task);
    rg2::Cpu(ctx).kwlnRootUpdate2DDrawBeginTask();
    return v0(ctx);
}
u64 sub_1A4C10(EEContext& ctx, u64 task) {
    set(ctx, GPR_A0, task);
    rg2::Cpu(ctx).sub_1A4C10();
    return v0(ctx);
}
u64 sub_1AE290(EEContext& ctx, u64 task) {
    set(ctx, GPR_A0, task);
    rg2::Cpu(ctx).sub_1AE290();
    return v0(ctx);
}
u64 sub_3962C0(EEContext& ctx, u64 task) {
    set(ctx, GPR_A0, task);
    rg2::Cpu(ctx).sub_3962C0();
    return v0(ctx);
}

void sub_1A7B50(EEContext& ctx, u64 lists, u64 mode) {
    set(ctx, GPR_A0, lists);
    set(ctx, GPR_A1, mode);
    rg2::Cpu(ctx).sub_1A7B50();
}
void sub_1A7FC0(EEContext& ctx, u64 lists, u64 mode) {
    set(ctx, GPR_A0, lists);
    set(ctx, GPR_A1, mode);
    rg2::Cpu(ctx).sub_1A7FC0();
}
void sub_1A8140(EEContext& ctx, u64 lists, u64 mode) {
    set(ctx, GPR_A0, lists);
    set(ctx, GPR_A1, mode);
    rg2::Cpu(ctx).sub_1A8140();
}
void sub_1A8B10(EEContext& ctx, u64 queue) {
    set(ctx, GPR_A0, queue);
    rg2::Cpu(ctx).sub_1A8B10();
}
void sub_315C20(EEContext& ctx, u64 model) {
    set(ctx, GPR_A0, model);
    rg2::Cpu(ctx).sub_315C20();
}
u64 sub_1A50F0(EEContext& ctx, u64 task) {
    set(ctx, GPR_A0, task);
    rg2::Cpu(ctx).sub_1A50F0();
    return v0(ctx);
}

void sub_359110(EEContext& ctx, u64 a, u64 b, u64 colour, u64 save) {
    set(ctx, GPR_A0, a);
    set(ctx, GPR_A1, b);
    set(ctx, GPR_A2, colour);
    set(ctx, GPR_A3, save);
    rg2::Cpu(ctx).sub_359110();
}
void sub_359560(EEContext& ctx, u64 centre, u64 colour, u64 matrix, u64 save, u32 radius_bits) {
    set(ctx, GPR_A0, centre);
    set(ctx, GPR_A1, colour);
    set(ctx, GPR_A2, matrix);
    set(ctx, GPR_A3, save);
    ctx.fpr[12] = radius_bits;
    rg2::Cpu(ctx).sub_359560();
}
void sub_359B40(EEContext& ctx, u64 centre, u64 colour, u64 save, u32 radius_bits) {
    set(ctx, GPR_A0, centre);
    set(ctx, GPR_A1, colour);
    set(ctx, GPR_A2, save);
    ctx.fpr[12] = radius_bits;
    rg2::Cpu(ctx).sub_359B40();
}
void sub_359E50(EEContext& ctx, u64 centre, u64 colour, u64 save, u32 radius_bits, u32 height_bits) {
    set(ctx, GPR_A0, centre);
    set(ctx, GPR_A1, colour);
    set(ctx, GPR_A2, save);
    ctx.fpr[12] = radius_bits;
    ctx.fpr[13] = height_bits;
    rg2::Cpu(ctx).sub_359E50();
}

u64 sub_19D530(EEContext& ctx, u64 task) {
    set(ctx, GPR_A0, task);
    rg2::Cpu(ctx).sub_19D530();
    return v0(ctx);
}
u64 sub_19DB10(EEContext& ctx, u64 task) {
    set(ctx, GPR_A0, task);
    rg2::Cpu(ctx).sub_19DB10();
    return v0(ctx);
}
u64 sub_19DE80(EEContext& ctx, u64 task) {
    set(ctx, GPR_A0, task);
    rg2::Cpu(ctx).sub_19DE80();
    return v0(ctx);
}
u64 sub_19F470(EEContext& ctx, u64 task) {
    set(ctx, GPR_A0, task);
    rg2::Cpu(ctx).sub_19F470();
    return v0(ctx);
}
u64 K_SceneDraw_UpdateDrwOpcFldObjTask(EEContext& ctx, u64 task) {
    set(ctx, GPR_A0, task);
    rg2::Cpu(ctx).K_SceneDraw_UpdateDrwOpcFldObjTask();
    return v0(ctx);
}
u64 sub_188250(EEContext& ctx, u64 task) {
    set(ctx, GPR_A0, task);
    rg2::Cpu(ctx).sub_188250();
    return v0(ctx);
}
u64 sub_41BAF0(EEContext& ctx, u64 task) {
    set(ctx, GPR_A0, task);
    rg2::Cpu(ctx).sub_41BAF0();
    return v0(ctx);
}

void sub_317A20(EEContext& ctx, u64 model) {
    set(ctx, GPR_A0, model);
    rg2::Cpu(ctx).sub_317A20();
}

u64 K_FldSrc_DrawFieldOpaque(EEContext& ctx, u64 camera, u64 res) {
    set(ctx, GPR_A0, camera);
    set(ctx, GPR_A1, res);
    rg2::Cpu(ctx).K_FldSrc_DrawFieldOpaque();
    return v0(ctx);
}
u64 K_FldSrc_DrawFieldTrans(EEContext& ctx, u64 camera, u64 res) {
    set(ctx, GPR_A0, camera);
    set(ctx, GPR_A1, res);
    rg2::Cpu(ctx).K_FldSrc_DrawFieldTrans();
    return v0(ctx);
}

void sub_358460(EEContext& ctx, u64 colour, u64 save) {
    set(ctx, GPR_A0, colour);
    set(ctx, GPR_A1, save);
    rg2::Cpu(ctx).sub_358460();
}
void sub_29E4B0(EEContext& ctx) {
    rg2::Cpu(ctx).sub_29E4B0();
}
void sub_2891E0(EEContext& ctx) {
    rg2::Cpu(ctx).sub_2891E0();
}
u64 sub_19EF80(EEContext& ctx, u64 task) {
    set(ctx, GPR_A0, task);
    rg2::Cpu(ctx).sub_19EF80();
    return v0(ctx);
}
u64 frFontDraw(EEContext& ctx, u64 text, u64 mode) {
    set(ctx, GPR_A0, text);
    set(ctx, GPR_A1, mode);
    rg2::Cpu(ctx).frFontDraw();
    return v0(ctx);
}
void sub_113A30(EEContext& ctx, u64 rgba, u64 w, u64 h, u32 depth_bits, u32 x_bits, u32 y_bits) {
    set(ctx, GPR_A0, rgba);
    set(ctx, GPR_A1, w);
    set(ctx, GPR_A2, h);
    ctx.fpr[12] = depth_bits;
    ctx.fpr[13] = x_bits;
    ctx.fpr[14] = y_bits;
    rg2::Cpu(ctx).sub_113A30();
}
void sub_113D80(EEContext& ctx, u64 rgba, u64 w, u64 h, u32 depth_bits, u32 x_bits, u32 y_bits) {
    set(ctx, GPR_A0, rgba);
    set(ctx, GPR_A1, w);
    set(ctx, GPR_A2, h);
    ctx.fpr[12] = depth_bits;
    ctx.fpr[13] = x_bits;
    ctx.fpr[14] = y_bits;
    rg2::Cpu(ctx).sub_113D80();
}
void sub_1140D0(EEContext& ctx, u64 rgba, u64 w, u64 h, u64 raster_ref, u32 depth_bits, u32 x_bits, u32 y_bits) {
    set(ctx, GPR_A0, rgba);
    set(ctx, GPR_A1, w);
    set(ctx, GPR_A2, h);
    set(ctx, GPR_A3, raster_ref);
    ctx.fpr[12] = depth_bits;
    ctx.fpr[13] = x_bits;
    ctx.fpr[14] = y_bits;
    rg2::Cpu(ctx).sub_1140D0();
}
void sub_114AF0(EEContext& ctx, u64 rgba, u64 w, u64 h, u64 raster_ref, u32 depth_bits, u32 x_bits, u32 y_bits) {
    set(ctx, GPR_A0, rgba);
    set(ctx, GPR_A1, w);
    set(ctx, GPR_A2, h);
    set(ctx, GPR_A3, raster_ref);
    ctx.fpr[12] = depth_bits;
    ctx.fpr[13] = x_bits;
    ctx.fpr[14] = y_bits;
    rg2::Cpu(ctx).sub_114AF0();
}
void sub_3B4B40(EEContext& ctx, u64 points, u64 colours, u64 point_idx, u64 colour_idx) {
    set(ctx, GPR_A0, points);
    set(ctx, GPR_A1, colours);
    set(ctx, GPR_A2, point_idx);
    set(ctx, GPR_A3, colour_idx);
    rg2::Cpu(ctx).sub_3B4B40();
}
void sub_139DC0(EEContext& ctx, u32 depth_bits) {
    ctx.fpr[12] = depth_bits;
    rg2::Cpu(ctx).sub_139DC0();
}
void sub_2720C0(EEContext& ctx) {
    rg2::Cpu(ctx).sub_2720C0();
}
void sub_2532B0(EEContext& ctx) {
    rg2::Cpu(ctx).sub_2532B0();
}
void sub_22C5A0(EEContext& ctx) {
    rg2::Cpu(ctx).sub_22C5A0();
}
void sub_27B880(EEContext& ctx) {
    rg2::Cpu(ctx).sub_27B880();
}
void sub_25BBF0(EEContext& ctx) {
    rg2::Cpu(ctx).sub_25BBF0();
}
void sub_2520F0(EEContext& ctx) {
    rg2::Cpu(ctx).sub_2520F0();
}
void sub_23C8C0(EEContext& ctx, u64 verts) {
    set(ctx, GPR_A0, verts);
    rg2::Cpu(ctx).sub_23C8C0();
}
u64 sub_411EE0(EEContext& ctx, u64 unused, u64 work) {
    set(ctx, GPR_A0, unused);
    set(ctx, GPR_A1, work);
    rg2::Cpu(ctx).sub_411EE0();
    return v0(ctx);
}
u64 sub_351290(EEContext& ctx, u64 work) {
    set(ctx, GPR_A0, work);
    rg2::Cpu(ctx).sub_351290();
    return v0(ctx);
}
void sub_351510(EEContext& ctx, u64 work) {
    set(ctx, GPR_A0, work);
    rg2::Cpu(ctx).sub_351510();
}
void sub_351940(EEContext& ctx, u64 work) {
    set(ctx, GPR_A0, work);
    rg2::Cpu(ctx).sub_351940();
}
u64 sub_351A10(EEContext& ctx, u64 task) {
    set(ctx, GPR_A0, task);
    rg2::Cpu(ctx).sub_351A10();
    return v0(ctx);
}
void sub_41BF80(EEContext& ctx, u64 obj) {
    set(ctx, GPR_A0, obj);
    rg2::Cpu(ctx).sub_41BF80();
}
void sub_20D500(EEContext& ctx, u64 obj, u64 matrix) {
    set(ctx, GPR_A0, obj);
    set(ctx, GPR_A1, matrix);
    rg2::Cpu(ctx).sub_20D500();
}

}  // namespace p3fes::game

// --- the recompiled program's entry points (the bodies read their arguments from the registers) ---
namespace p3fes::recomp_gen {
namespace pg = ::p3fes::game;

void fn_sub_3294D0_003294d0(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_3294D0(); }
void fn_sub_329550_00329550(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_329550(); }
void fn_sub_3295C0_003295c0(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_3295C0(); }
void fn_sub_329630_00329630(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_329630(); }
void fn_sub_34ADA0_0034ada0(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_34ADA0(); }
void fn_sub_34A800_0034a800(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_34A800(); }
void fn_sub_349A30_00349a30(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_349A30(); }
void fn_sub_348DA0_00348da0(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_348DA0(); }
void fn_sub_34B010_0034b010(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_34B010(); }
void fn_sub_349D30_00349d30(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_349D30(); }
void fn_kwlnRootUpdate2DDrawBeginTask_001989e0(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).kwlnRootUpdate2DDrawBeginTask(); }
void fn_sub_1A4C10_001a4c10(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_1A4C10(); }
void fn_sub_1AE290_001ae290(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_1AE290(); }
void fn_sub_3962C0_003962c0(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_3962C0(); }
void fn_sub_1A7B50_001a7b50(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_1A7B50(); }
void fn_sub_1A7FC0_001a7fc0(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_1A7FC0(); }
void fn_sub_1A8140_001a8140(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_1A8140(); }
void fn_sub_1A8B10_001a8b10(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_1A8B10(); }
void fn_sub_315C20_00315c20(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_315C20(); }
void fn_sub_1A50F0_001a50f0(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_1A50F0(); }
void fn_sub_359110_00359110(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_359110(); }
void fn_sub_359560_00359560(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_359560(); }
void fn_sub_359B40_00359b40(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_359B40(); }
void fn_sub_359E50_00359e50(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_359E50(); }
void fn_sub_19D530_0019d530(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_19D530(); }
void fn_sub_19DB10_0019db10(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_19DB10(); }
void fn_sub_19DE80_0019de80(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_19DE80(); }
void fn_sub_19F470_0019f470(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_19F470(); }
void fn_K_SceneDraw_UpdateDrwOpcFldObjTask_0019d780(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).K_SceneDraw_UpdateDrwOpcFldObjTask(); }
void fn_sub_188250_00188250(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_188250(); }
void fn_sub_41BAF0_0041baf0(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_41BAF0(); }
void fn_sub_317A20_00317a20(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_317A20(); }
void fn_K_FldSrc_DrawFieldOpaque_001b3e50(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).K_FldSrc_DrawFieldOpaque(); }
void fn_K_FldSrc_DrawFieldTrans_001b4720(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).K_FldSrc_DrawFieldTrans(); }
void fn_sub_358460_00358460(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_358460(); }
void fn_sub_29E4B0_0029e4b0(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_29E4B0(); }
void fn_sub_2891E0_002891e0(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_2891E0(); }
void fn_sub_19EF80_0019ef80(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_19EF80(); }
void fn_frFontDraw_003b1360(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).frFontDraw(); }
void fn_sub_113A30_00113a30(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_113A30(); }
void fn_sub_113D80_00113d80(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_113D80(); }
void fn_sub_1140D0_001140d0(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_1140D0(); }
void fn_sub_114AF0_00114af0(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_114AF0(); }
void fn_sub_3B4B40_003b4b40(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_3B4B40(); }
void fn_sub_139DC0_00139dc0(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_139DC0(); }
void fn_sub_2720C0_002720c0(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_2720C0(); }
void fn_sub_2532B0_002532b0(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_2532B0(); }
void fn_sub_22C5A0_0022c5a0(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_22C5A0(); }
void fn_sub_27B880_0027b880(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_27B880(); }
void fn_sub_23C8C0_0023c8c0(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_23C8C0(); }
void fn_sub_411EE0_00411ee0(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_411EE0(); }
void fn_sub_25BBF0_0025bbf0(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_25BBF0(); }
void fn_sub_2520F0_002520f0(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_2520F0(); }
void fn_sub_351290_00351290(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_351290(); }
void fn_sub_351510_00351510(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_351510(); }
void fn_sub_351940_00351940(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_351940(); }
void fn_sub_351A10_00351a10(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_351A10(); }
void fn_sub_41BF80_0041bf80(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_41BF80(); }
void fn_sub_20D500_0020d500(p3fes::EEContext& ctx) { pg::rg2::Cpu(ctx).sub_20D500(); }
}  // namespace p3fes::recomp_gen
