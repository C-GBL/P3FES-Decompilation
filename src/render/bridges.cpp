// The PDS material bridges of the MatFX plugin and the partitioned skin set-up callback (bridges.h has the table and
// the data flow; docs/ANALYSIS/22_rendering.md section 3).
//
// Cycle model (ADR-0013): every charge() below is one `ctx.cycles += N` block of the recompiled body in
// recomp/generated (fn_0042_*); backedge() sits wherever that body has a check point on a backward jump: loops, and
// the backward `goto`s of the compiler's block layout (the out-of-line blocks placed after the function's main path
// that jump back into it), which the hand versions keep as explicit check points where they are inlined.
//
// Registers: register-faithful (bridges.h). Each body runs on a Cpu view of the guest context, as in mesh.cpp: one
// variable per GPR (64-bit writes keep bits 64..127, as the EE does; lq / MMI results write all 128), the FPU / MMI /
// COP0 operations through the runtime's own instruction semantics, prologue spills and epilogue reloads on the guest
// stack. A branch's delay slot is written before the branch when it does not feed the condition (it executes on both
// paths). Guest structure offsets are the mesh.h names (pd:: = the RxPS2AllPipeData) and the bridges.h ones.
//
// Faithfulness audit (2026-10-21, tools/ours/audit): all 7 functions here are now p3fes_handgen's register-faithful
// bodies (the hand versions differed from the original: frame/spills 5, callee frames 2). Each keeps the notes of its
// earlier hand version above it; what this header says about how the bodies were written describes those earlier
// versions.
#include "p3fes/game/bridges.h"

#include "p3fes/game/mesh.h"
#include "p3fes_recomp_rt.h"
#include "p3fes/game/hg_cpu.h"

namespace p3fes::recomp_gen {
void fn__rwDMAOpenVIFPkt_004d59d0(p3fes::EEContext&);  // the DMA packet layer (DMAC registers)
void fn__rwDMAAddPURef_004d51c0(p3fes::EEContext&);    // _rwDMAAddPURef
void fn_matfxEffectMatrix_0046b060(p3fes::EEContext&);        // MatFX: the effect frame's 3x4 matrix (camera space)
void fn_sub_4F0F30_004f0f30(p3fes::EEContext&);        // texture cache: speculative placement (mesh.cpp)
void fn_RpSkyTexCacheAccessRaster_004f1020(p3fes::EEContext&);  // texture cache access (mesh.cpp)
void fn_sub_4F1E20_004f1e20(p3fes::EEContext&);        // raster TEX0 halves (mesh.cpp)
void fn_sub_4F1E40_004f1e40(p3fes::EEContext&);        // raster TEX1 (mesh.cpp)
void fn_sub_49CA50_0049ca50(p3fes::EEContext&);        // TEX1 filter shadow (mesh.cpp)
void fn_sub_49CAB0_0049cab0(p3fes::EEContext&);        // material colour quadword (mesh.cpp)
void fn_sub_49CBD0_0049cbd0(p3fes::EEContext&);        // surface properties quadword (mesh.cpp)
void fn_sub_49E5A0_0049e5a0(p3fes::EEContext&);        // resEntry array (re)allocation (RwMalloc/RwFree)
void fn_sub_4CB2F0_004cb2f0(p3fes::EEContext&);        // RwFrameGetLTM
void fn_sub_4C2F30_004c2f30(p3fes::EEContext&);        // matrix product (render_rw)
void fn_sub_4C32A0_004c32a0(p3fes::EEContext&);        // matrix inverse (render_rw)
void fn_atomicGetWorldBoundingSphere_004912b0(p3fes::EEContext&);        // atomic world bounding sphere
void fn_worldForAllLights_00499c20(p3fes::EEContext&);        // world: for all lights (callback, data)
void fn_sub_4A0430_004a0430(p3fes::EEContext&);        // light callback (mesh.cpp)
void fn__rpSkinMatrixUpdating_0046b510(p3fes::EEContext&);  // the bone palette (mesh.cpp)
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {

namespace core = ee::core;
namespace gen = ::p3fes::recomp_gen;
using namespace mesh;
using namespace bridges;

const EffectObserver* g_effect_observer = nullptr;

// --- the draw records (host-only reads after the guest state is complete: no guest effect) -------------------
// The bodies below are p3fes_handgen's (register-faithful since the 2026-10-21 audit); they capture, where the original
// has them in registers, the packet positions and the program / resEntry the records need, and report at the end of the
// success path exactly as the earlier hand versions did.
struct Pass {
    u32 colour_at = 0, surface_at = 0;  // where sub_49CAB0 / sub_49CBD0 wrote their quadwords
    u32 program = 0;
    bool uploaded = false;
    u32 res_entry = 0, vif_offset = 0;
};
u32 rd32(const EEContext& c, u32 va) { return guest::load<u32>(c, va); }
u64 rd64(const EEContext& c, u32 va) { return guest::load<u64>(c, va); }
u32 rd8(const EEContext& c, u32 va) { return guest::load<u8>(c, va); }
u32 gp_word(const EEContext& c, s32 off) { return static_cast<u32>(c.gpr[GPR_GP].u64[0]) + static_cast<u32>(off); }
u32 write_ptr(const EEContext& c) { return rd32(c, gp_word(c, kGpSprWrite)); }
// the MatFX extension of the PipeData's material
u32 matfx_ext(const EEContext& c, u32 pipe) {
    const u32 material = rd32(c, rd32(c, pipe + pd::kMesh) + 8);
    return rd32(c, material + rd32(c, gp_word(c, kGpMatFxExt)));
}

// The stock bridge's record (mesh::MeshDraw, filled as RpMeshPS2AllBridgeCallBack fills it).
void report_mesh(EEContext& c, u32 pipe, const Pass& p) {
    const DrawObserver* obs = draw_observer();
    if (!obs || !obs->mesh) return;
    MeshDraw draw;
    draw.atomic = rd32(c, pipe + pd::kObject);
    draw.mesh = rd32(c, pipe + pd::kMesh);
    draw.material = draw.mesh ? rd32(c, draw.mesh + 8) : 0;
    draw.texture = rd32(c, pipe + pd::kTexture);
    draw.raster = draw.texture ? rd32(c, draw.texture) : 0;
    if (draw.raster) {
        const u32 ext = draw.raster + rd32(c, gp_word(c, kGpRasterExt));
        draw.tex0 = rd32(c, ext + 8) | (static_cast<u64>(rd32(c, ext + 12)) << 32);
    }
    draw.tex1 = rd64(c, gp_word(c, kGpTex1));
    draw.clamp = rd64(c, gp_word(c, kGpClamp));
    draw.test = rd64(c, gp_word(c, kGpTest));
    draw.gif_tag_lo = rd64(c, kTplGifTag);
    draw.gif_tag_hi = rd64(c, kTplGifTag + 8);
    draw.trans_type = static_cast<u8>(rd8(c, pipe + pd::kTransType));
    draw.prim_type = static_cast<u8>(rd8(c, pipe + pd::kPrimType));
    draw.vu1_code_index = static_cast<u8>(rd8(c, pipe + pd::kVu1CodeIndex));
    draw.vu1_program = p.program;
    draw.program_uploaded = p.uploaded;
    for (u32 i = 0; i < 4; ++i) {
        draw.colour[i] = rd32(c, p.colour_at + 4 * i);
        draw.surface[i] = rd32(c, p.surface_at + 4 * i);
    }
    draw.res_entry = p.res_entry;
    draw.res_data = p.res_entry ? rd32(c, p.res_entry + 32) : 0;
    draw.vif_offset = p.vif_offset;
    obs->mesh(c, draw);
}

void report_effect(EEContext& c, Effect e, u32 pipe, u32 texture2, u32 extra_at, u32 extra_qw, u32 closing_at, u32 closing_qw) {
    if (!g_effect_observer || !g_effect_observer->effect) return;
    EffectDraw d;
    d.effect = e;
    d.pipe_data = pipe;
    d.texture2 = texture2;
    d.raster2 = texture2 ? rd32(c, texture2) : 0;
    d.extra_at = extra_at;
    d.extra_qw = extra_qw;
    d.closing_at = closing_at;
    d.closing_qw = closing_qw;
    g_effect_observer->effect(c, d);
}

}  // namespace

// 0x0046C5B0 matfxBridgeBumpMap -- 2012 bytes; frame 0x90: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// matfxBridgeBumpMap [MatFX bump-map bridge] ($a0 = PipeData). Effect slot 0: +0 the bump light's frame (0 = the camera's),
// +4 the bump texture, +12 coefficient, +16 inverse bump width. Frame 144: s0..s2, $ra at +48, the 3x4 bump matrix
// at sp+64 (matfxEffectMatrix(frame, sp+64, PipeData) copies 64 bytes), coefficient x inverse width at sp+140.
//   1. matfxEffectMatrix; when the camera's far plane (camera +132) differs from the cached gp-20924: cache it and
//      gp-20928 = 1 / (far - near) (camera +128).
//   2. The texture: the bump texture, else the material's (material +0); it REPLACES the PipeData's texture (pd
//      +64), then the stock texture state (placement, TME, the raster, TEX1 / CLAMP shadows, ATE).
//   3. _rwDMAOpenVIFPkt(0, 33): DMA cnt 26 whose first quadword is STCYCL 1,1 / UNPACK V4-32 x10 to VU1 0x3BC:
//      {scale, 0, 1/(far-near), far}, two A+D blocks for the bump passes (GIF tag NLOOP 2 + ALPHA_1 = 2 | 128 << 32
//      ((0 - Cs) * As + Cs) / TEST_1 = the shadow & 0x70000 (its alpha-test fields only); GIF tag + ALPHA_1 = 72 |
//      128 << 32 (Cs * As + Cd) / TEST_1), the three matrix rows; then the stock packet (GIF tag, colour, surface,
//      clip, A+D, program, resEntry call).
//   4. After the resEntry's reference: _rwDMAOpenVIFPkt(0, 4) with DIRECT 3: GIF tag NLOOP 2 (A+D), ALPHA_1 and
//      TEST_1 restored from the driver's shadows (gp-17032 / gp-17072).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void matfxBridgeBumpMap(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::c_eq_s, hg::call, hg::charge, hg::cond, hg::di,
          hg::div_s, hg::dsll, hg::dsll32, hg::dsra32, hg::dsrl32, hg::ei, hg::enter, hg::jal, hg::lbu, hg::ld,
          hg::link, hg::lq, hg::lui, hg::lw, hg::lwc1, hg::lwu, hg::mfc0, hg::mtc1, hg::mul_s, hg::pcpyld, hg::ppacw,
          hg::sb, hg::sd, hg::si, hg::sll, hg::sltiu, hg::sltu, hg::sq, hg::sra, hg::srl, hg::sub_s, hg::sw,
          hg::swc1, hg::sync;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 extra_at = 0, closing_at = 0;  // draw records (host-only): where the effect's packets went
    Pass pass;
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12};
    // 0x0046c5b0
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x30);
    a1 = addiu(sp, 0x40);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, 44);
    s0 = a0;
    lw(v0, gp, -17848);  // 0x7CE738
    a2 = s0;
    lw(s1, v1, 8);
    v0 = addu(s1, v0);
    lw(v0, v0, 0);
    lwc1(f1, v0, 12);
    lw(s2, v0, 4);
    lwc1(f0, v0, 16);
    lw(a0, v0, 0);
    mul_s(f0, f1, f0);
    link(ctx, 0x46C5F8u);  // $ra first: the delay slot below depends on it
    swc1(f0, sp, 0x8C);
    call(ctx, gen::fn_matfxEffectMatrix_0046b060);
    v0 = 0x960000;
    lw(v0, v0, 112);  // 0x960070
    lwc1(f0, gp, -20924);  // 0x7CDB34
    lwc1(f2, v0, 132);
    c_eq_s(f2, f0);
    if (!cond(ctx)) {
        // 0x0046c61c
        charge(ctx, 8);
        lwc1(f1, v0, 128);
        swc1(f2, gp, -20924);  // 0x7CDB34
        sub_s(f1, f2, f1);
        v0 = 0x3F800000;
        mtc1(v0, f0);
        div_s(f0, f0, f1);
        swc1(f0, gp, -20928);  // 0x7CDB30
    }
    // 0x0046c63c
    charge(ctx, 2);
    if (s2 == 0) {
        // 0x0046cc98
        charge(ctx, 2);
        lw(s2, s1, 0);
        backedge(ctx);
    }
    // 0x0046c644
    charge(ctx, 2);
    if (s2 != 0) {
        // 0x0046c64c
        charge(ctx, 2);
        link(ctx, 0x46C64Cu);  // $ra first: the delay slot below depends on it
        lw(a0, s2, 0);
        call(ctx, gen::fn_sub_4F0F30_004f0f30);
    }
    // 0x0046c654
    charge(ctx, 4);
    sw(s2, s0, 64);
    lw(s1, s0, 64);
    s2 = 0;
    if (s1 != 0) {
        // 0x0046c664
        charge(ctx, 1);
        lw(s2, s1, 0);
    }
    // 0x0046c668
    charge(ctx, 3);
    sw(zero, gp, -16952);  // 0x7CEAB8
    v0 = 0;
    if (s2 != 0) {
        // 0x0046c674
        charge(ctx, 11);
        lbu(v1, s2, 35);
        v0 = dsll32(v0, 0);
        v0 = dsra32(v0, 0);
        v1 = v1 & 0xF;
        a0 = v1 ^ 0x1;
        v1 = v1 ^ 0x5;
        a0 = sltiu(a0, 1);
        v1 = sltiu(v1, 1);
        v1 = a0 | v1;
        v0 = v0 | v1;
        sw(v0, gp, -16952);  // 0x7CEAB8
    }
    // 0x0046c6a0
    charge(ctx, 3);
    lw(v0, gp, -16948);  // 0x7CEABC
    if (s2 != v0) {
        // 0x0046c6ac
        charge(ctx, 2);
        if (s2 == 0) {
            // 0x0046cca0
            charge(ctx, 5);
            ld(v1, gp, -20272);  // 0x7CDDC0
            v0 = si(-17);
            v0 = v1 & v0;
            sd(v0, gp, -20272);  // 0x7CDDC0
            backedge(ctx);
        } else {
            // 0x0046c6b4
            charge(ctx, 6);
            ld(v0, gp, -20272);  // 0x7CDDC0
            a0 = s2;
            a1 = 0;
            v0 = v0 | 0x10;
            link(ctx, 0x46C6C4u);  // $ra first: the delay slot below depends on it
            sd(v0, gp, -20272);  // 0x7CDDC0
            call(ctx, gen::fn_RpSkyTexCacheAccessRaster_004f1020);
        }
        // 0x0046c6cc
        charge(ctx, 2);
        sw(s2, gp, -16948);  // 0x7CEABC
        if (s1 != 0) {
            // 0x0046c6d4
            charge(ctx, 9);
            link(ctx, 0x46C6D4u);  // $ra first: the delay slot below depends on it
            lbu(a0, s1, 80);
            call(ctx, gen::fn_sub_49CA50_0049ca50);
            sd(zero, gp, -17048);  // 0x7CEA58
            v0 = 3;
            lw(v1, s1, 80);
            v1 = v1 & 0xF00;
            v1 = srl(v1, 8);
            if (v1 == v0) {
                // 0x0046ccb4
                charge(ctx, 4);
                ld(v0, gp, -17048);  // 0x7CEA58
                v0 = v0 | 0x1;
                sd(v0, gp, -17048);  // 0x7CEA58
                backedge(ctx);
            }
            // 0x0046c6f8
            charge(ctx, 6);
            lw(v1, s1, 80);
            v0 = 3;
            v1 = v1 & 0xF000;
            v1 = srl(v1, 12);
            if (v1 == v0) {
                // 0x0046c710
                charge(ctx, 4);
                ld(v0, gp, -17048);  // 0x7CEA58
                v0 = v0 | 0x4;
                sd(v0, gp, -17048);  // 0x7CEA58
            }
        }
    }
    // 0x0046ccc4
    charge(ctx, 3);
    lw(v0, gp, -16952);  // 0x7CEAB8
    if (v0 == 0) {
        backedge(ctx);
        // 0x0046c72c
        charge(ctx, 4);
        ld(v1, gp, -17072);  // 0x7CEA40
        v0 = si(-2);
        v0 = v1 & v0;
        sd(v0, gp, -17072);  // 0x7CEA40
    } else {
        // 0x0046ccd0
        charge(ctx, 2);
        ld(v0, gp, -17072);  // 0x7CEA40
        backedge(ctx);
        // 0x0046c720
        charge(ctx, 3);
        v0 = v0 | 0x1;
        sd(v0, gp, -17072);  // 0x7CEA40
    }
    // 0x0046c73c
    charge(ctx, 79);
    a0 = 0;
    a1 = 33;
    jal(ctx, 0x46C740u, gen::fn__rwDMAOpenVIFPkt_004d59d0);
    v0 = 0x10000000;
    lwu(a3, gp, -20924);  // 0x7CDB34
    a0 = 0;
    v1 = v0 | 0x1A;
    pcpyld(t1, a0, v1);
    lw(t0, gp, -17148);  // 0x7CE9F4
    extra_at = t0.u();  // the effect's extra quadwords start here
    a2 = dsll32(v0, 0);
    v1 = 0x6C0A0000;
    v0 = 0x1000000;
    a0 = v1 | 0x3BC;
    v1 = v0 | 0x101;  // &0x1000101
    lwu(a1, gp, -20928);  // 0x7CDB30
    ppacw(t2, a0, v1);
    sq(t1, t0, 0);
    a0 = v0 | 0x404;  // &0x1000404
    t1 = 0;
    t0 = 0;
    lwu(v1, sp, 0x8C);
    ppacw(t0, t1, t0);
    lw(v0, gp, -17148);  // 0x7CE9F4
    ppacw(t0, t2, t0);
    a3 = dsll32(a3, 0);
    sq(t0, v0, 16);
    a1 = a3 | a1;
    t3 = 66;
    pcpyld(v1, a1, v1);
    a3 = addiu(v0, 16);
    sq(v1, v0, 32);
    a1 = addiu(a3, 176);
    v1 = 0x8002;
    s1 = v1 | a2;
    a3 = 14;
    pcpyld(v1, a3, s1);
    a2 = 128;
    sq(v1, v0, 48);
    a3 = dsll32(a2, 0);
    t0 = 0x70000;
    a2 = 2;
    t2 = 71;
    a2 = a2 | a3;
    pcpyld(a2, t3, a2);
    sq(a2, v0, 64);
    a2 = 72;
    ld(t1, gp, -17072);  // 0x7CEA40
    a3 = a2 | a3;
    a2 = 0x6C010000;
    a2 = a2 | 0x3FA;
    a2 = dsll32(a2, 0);
    a0 = a0 | a2;
    a2 = t1 & t0;
    pcpyld(a2, t2, a2);
    sq(a2, v0, 80);
    pcpyld(t3, t3, a3);
    sq(v1, v0, 96);
    a3 = 0;
    sq(t3, v0, 112);
    pcpyld(a0, a0, a3);
    sq(a2, v0, 128);
    lq(v1, sp, 0x40);
    sq(v1, v0, 144);
    lq(v1, sp, 0x50);
    sq(v1, v0, 160);
    lq(v1, sp, 0x60);
    sq(v1, v0, 176);
    sw(a1, gp, -17148);  // 0x7CE9F4
    sq(a0, v0, 192);
    lw(v1, gp, -17148);  // 0x7CE9F4
    lw(v0, gp, -16952);  // 0x7CEAB8
    a1 = addiu(v1, 16);
    sw(a1, gp, -17148);  // 0x7CE9F4
    lbu(v1, s0, 71);
    v1 = v1 ^ 0xFF;
    v1 = sltu(0, v1);
    v0 = v1 | v0;
    sw(v1, gp, -16956);  // 0x7CEAB4
    if (v0 == 0) {
        // 0x0046c888
        charge(ctx, 4);
        ld(v1, gp, -20272);  // 0x7CDDC0
        v0 = si(-65);
        v0 = v1 & v0;
        sd(v0, gp, -20272);  // 0x7CDDC0
    } else {
        // 0x0046c878
        charge(ctx, 4);
        ld(v0, gp, -20272);  // 0x7CDDC0
        v0 = v0 | 0x40;
        sd(v0, gp, -20272);  // 0x7CDDC0
    }
    // 0x0046c898
    charge(ctx, 43);
    v0 = 0x960000;
    lbu(a3, s0, 41);
    ld(a0, v0, 22688);  // 0x9658A0
    v1 = lui(0xFC00);
    a1 = dsll32(a1, 0);
    ld(t0, gp, -20272);  // 0x7CDDC0
    a1 = dsra32(a1, 0);
    a3 = dsll32(a3, 0);
    v0 = v1 | 0x7FFF;
    a3 = dsra32(a3, 0);
    v1 = dsll32(v0, 0);
    a3 = t0 | a3;
    v0 = 0xFFFF;
    v0 = dsll(v0, 16);
    v0 = v0 | 0xFFFF;
    v1 = v0 | v1;
    pcpyld(v1, zero, v1);
    t1 = a0 & v1;
    v0 = 0x960000;
    v1 = 0x6C010000;
    ld(a2, v0, 22696);  // 0x9658A8
    a0 = v1 | 0x3FB;
    v1 = 0x1000000;
    a0 = dsll32(a0, 0);
    v1 = v1 | 0x404;  // &0x1000404
    a0 = v1 | a0;
    v1 = dsll32(a3, 0);
    v1 = dsra32(v1, 0);
    v0 = 0x960000;
    a3 = v1 & 0x7FF;
    a3 = dsll32(a3, 15);
    v1 = t0 & 0x10;
    a3 = t1 | a3;
    t0 = 0;
    pcpyld(a2, a2, a3);
    sq(a2, v0, 22688);  // 0x9658A0
    pcpyld(a0, a0, t0);
    sq(a2, a1, 0);
    sq(a0, a1, 16);
    lw(v0, gp, -17148);  // 0x7CE9F4
    a1 = addiu(v0, 32);
    sw(a1, gp, -17148);  // 0x7CE9F4
    if (v1 == 0) {
        // 0x0046c958
        charge(ctx, 4);
        v0 = 0x3B800000;
        v0 = v0 | 0x8081;
        mtc1(v0, f12);
        a0 = addiu(s0, 68);
    } else {
        // 0x0046c944
        charge(ctx, 5);
        v0 = 0x3B010000;
        v0 = v0 | 0x1B50;
        mtc1(v0, f12);
        a0 = addiu(s0, 68);
    }
    // 0x0046c968
    charge(ctx, 32);
    pass.colour_at = write_ptr(ctx);
    jal(ctx, 0x46C968u, gen::fn_sub_49CAB0_0049cab0);
    v1 = 0x6C010000;
    v0 = 0x1000000;
    v1 = v1 | 0x3FC;
    v0 = v0 | 0x404;  // &0x1000404
    v1 = dsll32(v1, 0);
    a0 = 0;
    v1 = v0 | v1;
    lw(v0, gp, -17148);  // 0x7CE9F4
    pcpyld(v1, v1, a0);
    sq(v1, v0, 0);
    lw(v0, gp, -17148);  // 0x7CE9F4
    a1 = addiu(v0, 16);
    sw(a1, gp, -17148);  // 0x7CE9F4
    lwc1(f12, s0, 28);
    pass.surface_at = write_ptr(ctx);
    link(ctx, 0x46C9A8u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 60);
    call(ctx, gen::fn_sub_49CBD0_0049cbd0);
    v0 = 0x6C030000;
    lbu(a0, s0, 40);
    v1 = v0 | 0x3FD;
    v0 = 0x1000000;
    v1 = dsll32(v1, 0);
    v0 = v0 | 0x404;  // &0x1000404
    v0 = v0 | v1;
    v1 = 0;
    pcpyld(a1, v0, v1);
    lw(v1, gp, -17148);  // 0x7CE9F4
    sq(a1, v1, 0);
    lw(v1, gp, -16876);  // 0x7CEB04
    v0 = a0 & 0x7;
    if (v1 != 0) {
        // 0x0046c9e8
        charge(ctx, 3);
        v1 = v0 & 0x4;
        if (v1 != 0) {
            goto L_0046c9f4;
        }
    L_0046ca0c:
        charge(ctx, 11);
        a0 = 0x960000;
        lw(a1, gp, -17148);  // 0x7CE9F4
        lq(a0, a0, 22832);  // 0x965930
        v1 = 0x960000;
        v0 = v0 | 0x8;
        sq(a0, a1, 16);
        lq(v1, v1, 22848);  // 0x965940
        sq(v1, a1, 32);
        lw(v1, gp, -17148);  // 0x7CE9F4
        a1 = addiu(v1, 48);
        sw(a1, gp, -17148);  // 0x7CE9F4
        goto L_0046ca38;
    }
L_0046c9f4:
    charge(ctx, 3);
    lw(v1, gp, -20232);  // 0x7CDDE8
    if (v1 != 0) {
        // 0x0046ca00
        charge(ctx, 3);
        v1 = v0 & 0x4;
        if (v1 == 0) {
            goto L_0046ccd8;
        }
        goto L_0046ca0c;
    }
L_0046ccd8:
    charge(ctx, 11);
    v1 = 0x960000;
    lw(a1, gp, -17148);  // 0x7CE9F4
    lq(a0, v1, 22800);  // 0x965910
    v1 = 0x960000;
    sq(a0, a1, 16);
    lq(v1, v1, 22816);  // 0x965920
    sq(v1, a1, 32);
    lw(v1, gp, -17148);  // 0x7CE9F4
    a1 = addiu(v1, 48);
    sw(a1, gp, -17148);  // 0x7CE9F4
    backedge(ctx);
L_0046ca38:
    charge(ctx, 5);
    lw(a2, gp, -16964);  // 0x7CEAAC
    a0 = 3;
    sw(zero, gp, -16884);  // 0x7CEAFC
    v1 = 0;
    if (a2 == a0) {
        // 0x0046cd04
        charge(ctx, 3);
        v1 = 32;
        sw(v1, gp, -16884);  // 0x7CEAFC
        backedge(ctx);
    }
    // 0x0046ca4c
    charge(ctx, 17);
    lwu(a2, gp, -16880);  // 0x7CEB00
    a0 = dsll32(v1, 0);
    v1 = dsll32(v0, 0);
    a0 = dsrl32(a0, 0);
    v0 = dsll32(a1, 0);
    v1 = dsrl32(v1, 0);
    v0 = dsra32(v0, 0);
    a1 = dsll32(a2, 0);
    a0 = a1 | a0;
    pcpyld(v1, a0, v1);
    sq(v1, v0, 0);
    lw(v0, gp, -17148);  // 0x7CE9F4
    a1 = addiu(v0, 16);
    sw(a1, gp, -17148);  // 0x7CE9F4
    lw(v0, s0, 64);
    if (v0 == 0) {
        // 0x0046cd10
        charge(ctx, 25);
        a1 = dsll32(a1, 0);
        v0 = 0x50000000;
        a1 = dsra32(a1, 0);
        v0 = v0 | 0x2;
        sq(zero, a1, 0);
        v0 = dsll32(v0, 0);
        v1 = 0;
        sq(zero, a1, 16);
        pcpyld(v0, v0, v1);
        sq(v0, a1, 32);
        a0 = 14;
        v0 = 0x10000000;
        v1 = dsll32(v0, 0);
        v0 = 0x8001;
        v1 = v0 | v1;
        pcpyld(v1, a0, v1);
        sq(v1, a1, 48);
        v0 = 71;
        ld(v1, gp, -17072);  // 0x7CEA40
        pcpyld(v0, v0, v1);
        sq(v0, a1, 64);
        lw(v0, gp, -17148);  // 0x7CE9F4
        a1 = addiu(v0, 80);
        sw(a1, gp, -17148);  // 0x7CE9F4
        backedge(ctx);
    } else {
        // 0x0046ca90
        charge(ctx, 30);
        v0 = 0x50000000;
        a2 = dsll32(a1, 0);
        v0 = v0 | 0x4;
        v1 = 0;
        v0 = dsll32(v0, 0);
        a2 = dsra32(a2, 0);
        pcpyld(v0, v0, v1);
        sq(v0, a2, 0);
        a1 = 14;
        v0 = 0x10000000;
        a0 = 71;
        v1 = dsll32(v0, 0);
        v0 = 0x8003;
        v0 = v0 | v1;
        pcpyld(v0, a1, v0);
        sq(v0, a2, 16);
        v1 = 20;
        ld(a1, gp, -17072);  // 0x7CEA40
        v0 = 8;
        pcpyld(a0, a0, a1);
        sq(a0, a2, 32);
        ld(a0, gp, -17040);  // 0x7CEA60
        pcpyld(v1, v1, a0);
        sq(v1, a2, 48);
        ld(v1, gp, -17048);  // 0x7CEA58
        pcpyld(v0, v0, v1);
        sq(v0, a2, 64);
        lw(v0, gp, -17148);  // 0x7CE9F4
        a1 = addiu(v0, 80);
        sw(a1, gp, -17148);  // 0x7CE9F4
    }
    // 0x0046cb08
    charge(ctx, 16);
    lbu(v0, s0, 40);
    v1 = v0 & 0x20;
    v0 = v0 & 0x18;
    v1 = sra(v1, 5);
    v0 = sra(v0, 2);
    v0 = v1 | v0;
    sb(v0, s0, 43);
    lw(v1, s0, 4);
    lbu(a0, s0, 43);
    lw(v0, gp, -16888);  // 0x7CEAF8
    lw(v1, v1, 24);
    a0 = sll(a0, 2);
    v1 = addu(v1, a0);
    lw(a0, v1, 0);
    pass.program = a0.u();
    pass.uploaded = v0 != a0;
    if (v0 != a0) {
        // 0x0046cb48
        charge(ctx, 13);
        v0 = dsll32(a0, 0);
        a1 = 0;
        v0 = dsrl32(v0, 0);
        v1 = dsll32(v0, 0);
        v0 = 0x50000000;
        v1 = v1 | v0;
        lw(v0, gp, -17148);  // 0x7CE9F4
        pcpyld(v1, a1, v1);
        sq(v1, v0, 0);
        lw(v0, gp, -17148);  // 0x7CE9F4
        sw(a0, gp, -16888);  // 0x7CEAF8
        a1 = addiu(v0, 16);
        sw(a1, gp, -17148);  // 0x7CE9F4
    }
    // 0x0046cb7c
    charge(ctx, 21);
    lw(a2, s0, 48);
    t0 = 0x2000000;
    lw(a0, s0, 4);
    a3 = 0x3000000;
    lw(v1, gp, -17148);  // 0x7CE9F4
    a1 = 0x50000000;
    v0 = 0x10000;
    lw(a2, a2, 0);
    lw(t1, a0, 20);
    a0 = addiu(a2, 24);
    t0 = t1 | t0;
    lwu(a2, a2, 32);
    t0 = dsll32(t0, 0);
    a3 = t0 | a3;
    a2 = dsll32(a2, 0);
    a1 = a2 | a1;
    pcpyld(a1, a3, a1);
    sq(a1, v1, 0);
    lw(v1, gp, -17148);  // 0x7CE9F4
    a1 = addiu(v1, 16);
    sw(a1, gp, -17148);  // 0x7CE9F4
    pass.res_entry = a2.u();
    pass.vif_offset = t1.u();
    for (;;) {
        // 0x0046cbd0
        charge(ctx, 7);
        di(ctx);
        sync(ctx, 16);
        mfc0(v1, 12);
        v1 = v1 & v0;
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0046cbec
    charge(ctx, 11);
    lw(v0, a0, 0);
    v0 = addiu(v0, 1);
    sw(v0, a0, 0);
    ei(ctx);
    v0 = 1;
    lw(v1, a0, 4);
    v1 = addiu(v1, 1);
    sw(v1, a0, 4);
    lw(v1, a0, 4);
    if (v1 == v0) {
        // 0x0046cc18
        charge(ctx, 2);
        jal(ctx, 0x46CC18u, gen::fn__rwDMAAddPURef_004d51c0);
    }
    // 0x0046cc20
    charge(ctx, 30);
    a0 = 0;
    a1 = 4;
    jal(ctx, 0x46CC24u, gen::fn__rwDMAOpenVIFPkt_004d59d0);
    v0 = 0x50000000;
    v1 = 0;
    v0 = v0 | 0x3;
    a0 = 0;
    ppacw(t0, v0, v1);
    lw(a2, gp, -17148);  // 0x7CE9F4
    closing_at = a2.u();  // the closing packet
    v0 = 14;
    v1 = 0x10000000;
    pcpyld(a3, v0, s1);
    v0 = v1 | 0x3;
    a1 = 66;
    ppacw(v0, a0, v0);
    ppacw(v0, t0, v0);
    sq(v0, a2, 0);
    a0 = 71;
    sq(a3, a2, 16);
    v0 = 1;
    ld(v1, gp, -17032);  // 0x7CEA68
    pcpyld(v1, a1, v1);
    sq(v1, a2, 32);
    ld(v1, gp, -17072);  // 0x7CEA40
    pcpyld(v1, a0, v1);
    sq(v1, a2, 48);
    lw(v1, gp, -17148);  // 0x7CE9F4
    a1 = addiu(v1, 64);
    sw(a1, gp, -17148);  // 0x7CE9F4
    report_mesh(ctx, s0.u(), pass);
    report_effect(ctx, Effect::BumpMap, s0.u(), rd32(ctx, s0.u() + pd::kTexture), extra_at, 12, closing_at, 4);
    // 0x0046cd74
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x0046CD90 matfxBridgeEnvMap -- 2396 bytes; frame 0xF0: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// matfxBridgeEnvMap [MatFX environment-map bridge] ($a0 = PipeData). Effect slot 0: +0 the environment frame (0 = the
// camera's), +4 the environment texture, +8 coefficient, +40 ALPHA_2, +48 FOGCOL, +56 TEST_2 bits. Frame 240:
// s0..s7, $ra at +128; the environment matrix at sp+144 (matfxEffectMatrix(frame, sp+144, PipeData), 64 bytes), the
// environment texture's TEX0 halves at sp+208 / sp+212 and TEX1 at sp+224, the base texture's TEX0 at sp+216 /
// sp+220, the coefficient at sp+236. s4 = PipeData, s1 = the base texture, s3 = the environment texture, s0 =
// ALPHA_2, s5 = FOGCOL (used as given: no 0x01000000 test here), s6 = TEST_2, s7 = ZBUF_1, s2 = CLAMP_2 bits.
// The texture placement and GS state are dual_bridge's (matfxBridgeDual) with these registers; the register block
// (_rwDMAOpenVIFPkt(0, 40), DMA cnt 34) is STCYCL 1,1 / UNPACK V4-32 x11 to VU1 0x3BC: the second pass's vertex
// GIF tag (PRIM 0x258 | prim | FGE), the two A+D kick blocks (TEX0_1 / FOGCOL of the base pass, TEX0_2 / FOGCOL
// of the environment pass), the matrix rows 0 and 1, row 2 with the coefficient in w, and the constant quadword
// 0x6B5150; then DIRECT 6 with ALPHA_2 / CLAMP_2 / TEST_2 / TEX1_2 / ZBUF_2, then the stock packet. The closing
// packet restores FOGCOL.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void matfxBridgeEnvMap(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::di, hg::dsll, hg::dsll32,
          hg::dsra32, hg::dsrl32, hg::ei, hg::enter, hg::jal, hg::lbu, hg::ld, hg::link, hg::lq, hg::lui, hg::lw,
          hg::lwc1, hg::lwu, hg::mfc0, hg::mtc1, hg::pcpyld, hg::ppacw, hg::sb, hg::sd, hg::si, hg::sll, hg::slti,
          hg::sltu, hg::sq, hg::sra, hg::srl, hg::sw, hg::swc1, hg::sync;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 extra_at = 0, closing_at = 0;  // draw records (host-only): where the effect's packets went
    Pass pass;
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x0046cd90
    enter(ctx, 38);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
    v0 = 0x70000;
    sd(ra, sp, 0x80);
    a1 = addiu(sp, 0x90);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    a2 = s4;
    sq(s1, sp, 0x10);
    s2 = 0;
    sq(s0, sp, 0x0);
    lw(a3, a0, 44);
    ld(v1, gp, -17072);  // 0x7CEA40
    ld(s7, gp, -17088);  // 0x7CEA30
    lw(a3, a3, 8);
    lw(a0, gp, -17848);  // 0x7CE738
    v1 = v1 & v0;
    lw(s1, a3, 0);
    v0 = addu(a3, a0);
    lw(v0, v0, 0);
    lwc1(f0, v0, 8);
    lw(s3, v0, 4);
    lw(a0, v0, 0);
    ld(s0, v0, 40);
    ld(s5, v0, 48);
    swc1(f0, sp, 0xEC);
    ld(v0, v0, 56);
    s6 = v1 | v0;
    link(ctx, 0x46CE10u);  // $ra first: the delay slot below depends on it
    sd(zero, sp, 0xE0);
    call(ctx, gen::fn_matfxEffectMatrix_0046b060);
    sd(zero, sp, 0xD8);
    sd(zero, sp, 0xD0);
    sw(zero, gp, -16952);  // 0x7CEAB8
    if (s1 != 0) {
        // 0x0046ce28
        charge(ctx, 8);
        link(ctx, 0x46CE28u);  // $ra first: the delay slot below depends on it
        lw(a0, s1, 0);
        call(ctx, gen::fn_sub_4F0F30_004f0f30);
        lw(v1, s1, 0);
        v0 = 6;
        lbu(v1, v1, 35);
        v1 = v1 & 0xF;
        if (v1 != v0) {
            // 0x0046ce48
            charge(ctx, 2);
            v0 = 1;
            sw(v0, gp, -16952);  // 0x7CEAB8
        }
    }
    // 0x0046ce50
    charge(ctx, 2);
    if (s3 != 0) {
        // 0x0046ce58
        charge(ctx, 5);
        link(ctx, 0x46CE58u);  // $ra first: the delay slot below depends on it
        lw(a0, s3, 0);
        call(ctx, gen::fn_sub_4F0F30_004f0f30);
        lw(a0, s3, 0);
        a1 = 1;
        jal(ctx, 0x46CE64u, gen::fn_RpSkyTexCacheAccessRaster_004f1020);
    }
    // 0x0046ce6c
    charge(ctx, 2);
    if (s1 != 0) {
        // 0x0046ce74
        charge(ctx, 3);
        lw(a0, s1, 0);
        a1 = 0;
        jal(ctx, 0x46CE78u, gen::fn_RpSkyTexCacheAccessRaster_004f1020);
    }
    // 0x0046ce80
    charge(ctx, 2);
    if (s3 != 0) {
        // 0x0046ce88
        charge(ctx, 6);
        lw(a0, s3, 0);
        lw(v0, gp, -16968);  // 0x7CEAA8
        v0 = addu(a0, v0);
        lw(v0, v0, 88);
        if (v0 == 0) {
            // 0x0046cea0
            charge(ctx, 2);
            a1 = 1;
            jal(ctx, 0x46CEA0u, gen::fn_RpSkyTexCacheAccessRaster_004f1020);
        }
    }
    // 0x0046cea8
    charge(ctx, 2);
    if (s1 != 0) {
        // 0x0046ceb0
        charge(ctx, 6);
        lw(a0, s1, 0);
        lw(v0, gp, -16968);  // 0x7CEAA8
        v0 = addu(a0, v0);
        lw(v0, v0, 88);
        if (v0 == 0) {
            // 0x0046cec8
            charge(ctx, 2);
            a1 = 0;
            jal(ctx, 0x46CEC8u, gen::fn_RpSkyTexCacheAccessRaster_004f1020);
        }
    }
    // 0x0046ced0
    charge(ctx, 2);
    if (s1 == 0) {
        // 0x0046d41c
        charge(ctx, 6);
        ld(v1, gp, -20272);  // 0x7CDDC0
        v0 = si(-17);
        sw(zero, gp, -16948);  // 0x7CEABC
        v0 = v1 & v0;
        sd(v0, gp, -20272);  // 0x7CDDC0
        backedge(ctx);
    } else {
        // 0x0046ced8
        charge(ctx, 20);
        ld(v0, gp, -20272);  // 0x7CDDC0
        a1 = addiu(sp, 0xDC);
        v0 = v0 | 0x10;
        sd(v0, gp, -20272);  // 0x7CDDC0
        lw(v0, s1, 0);
        sw(v0, gp, -16948);  // 0x7CEABC
        lw(a0, s1, 0);
        a2 = addiu(sp, 0xD8);
        jal(ctx, 0x46CEF4u, gen::fn_sub_4F1E20_004f1e20);
        lbu(a2, s1, 80);
        lw(a0, s1, 0);
        a1 = addiu(gp, -17040);  // &0x7CEA60
        jal(ctx, 0x46CF04u, gen::fn_sub_4F1E40_004f1e40);
        sd(zero, gp, -17048);  // 0x7CEA58
        v0 = 3;
        lw(v1, s1, 80);
        v1 = v1 & 0xF00;
        v1 = srl(v1, 8);
        if (v1 == v0) {
            // 0x0046d40c
            charge(ctx, 4);
            ld(v0, gp, -17048);  // 0x7CEA58
            v0 = v0 | 0x1;
            sd(v0, gp, -17048);  // 0x7CEA58
            backedge(ctx);
        }
        // 0x0046cf28
        charge(ctx, 6);
        lw(v1, s1, 80);
        v0 = 3;
        v1 = v1 & 0xF000;
        v1 = srl(v1, 12);
        if (v1 == v0) {
            // 0x0046cf40
            charge(ctx, 3);
            ld(v0, gp, -17048);  // 0x7CEA58
            v0 = v0 | 0x4;
            sd(v0, gp, -17048);  // 0x7CEA58
        }
    }
    // 0x0046cf4c
    charge(ctx, 4);
    ld(v0, gp, -17072);  // 0x7CEA40
    v0 = v0 | 0x1;
    sd(v0, gp, -17072);  // 0x7CEA40
    if (s3 != 0) {
        // 0x0046cf5c
        charge(ctx, 14);
        lw(a0, s3, 0);
        a1 = addiu(sp, 0xD4);
        a2 = addiu(sp, 0xD0);
        jal(ctx, 0x46CF64u, gen::fn_sub_4F1E20_004f1e20);
        lbu(a2, s3, 80);
        lw(a0, s3, 0);
        a1 = addiu(sp, 0xE0);
        jal(ctx, 0x46CF74u, gen::fn_sub_4F1E40_004f1e40);
        lw(a0, s3, 80);
        v0 = 3;
        v1 = a0 & 0xF00;
        v1 = srl(v1, 8);
        s2 = 0;
        if (v1 == v0) {
            // 0x0046cf94
            charge(ctx, 1);
            s2 = s2 | 0x1;
        }
        // 0x0046cf98
        charge(ctx, 5);
        v1 = a0 & 0xF000;
        v0 = 3;
        v1 = srl(v1, 12);
        if (v1 == v0) {
            // 0x0046cfac
            charge(ctx, 1);
            s2 = s2 | 0x4;
        }
    }
    // 0x0046cfb0
    charge(ctx, 2);
    if (s1 != 0) {
        // 0x0046cfb8
        charge(ctx, 5);
        lw(v0, s1, 0);
        lw(v0, v0, 20);
        at = slti(v0, 9);
        if (at != 0) {
            // 0x0046cfcc
            charge(ctx, 2);
            if (s3 != 0) {
                // 0x0046cfd4
                charge(ctx, 5);
                lw(v0, s3, 0);
                lw(v0, v0, 20);
                at = slti(v0, 9);
                if (at != 0) {
                    // 0x0046cfe8
                    charge(ctx, 3);
                    v0 = si(-1);
                    sw(v0, gp, -16948);  // 0x7CEABC
                }
            }
        }
    }
    // 0x0046d434
    charge(ctx, 122);
    a0 = 0;
    a1 = 40;
    jal(ctx, 0x46D438u, gen::fn__rwDMAOpenVIFPkt_004d59d0);
    v0 = 0x10000000;
    t4 = 0x6B0000;
    a1 = 0;
    v1 = v0 | 0x22;
    a0 = dsll32(v0, 0);
    lw(a2, gp, -17148);  // 0x7CE9F4
    extra_at = a2.u();  // the effect's extra quadwords start here
    pcpyld(t0, a1, v1);
    ld(t4, t4, 20816);  // 0x6B5150
    v0 = 0x6C0B0000;
    v1 = 0x1000000;
    a1 = v0 | 0x3BC;
    t2 = v1 | 0x404;  // &0x1000404
    v0 = v1 | 0x101;  // &0x1000101
    t8 = 0;
    ppacw(a3, a1, v0);
    sq(t0, a2, 0);
    lw(a2, gp, -17148);  // 0x7CE9F4
    lwu(v0, sp, 0xEC);
    a1 = 0;
    v1 = 0;
    t9 = 0x8005;
    ppacw(t0, a1, v1);
    t6 = dsll32(v0, 0);
    a1 = 14;
    v0 = addiu(a2, 16);
    s3 = 6;
    ppacw(v1, a3, t0);
    sw(v0, gp, -17148);  // 0x7CE9F4
    t1 = addiu(v0, 304);
    sq(v1, a2, 16);
    v0 = 0x8002;
    v1 = 61;
    a3 = v0 | a0;
    t7 = 1042;
    pcpyld(a3, a1, a3);
    pcpyld(t3, v1, s5);
    sq(a3, a2, 32);
    sq(t3, a2, 48);
    v0 = 7;
    ld(s5, sp, 0xD0);
    t3 = 0x30000000;
    s1 = t3 | 0x4000;
    t3 = 0x6B0000;
    ld(t5, t3, 20824);  // 0x6B5158
    pcpyld(v0, v0, s5);
    sq(v0, a2, 64);
    sq(a3, a2, 80);
    ld(v0, gp, -17056);  // 0x7CEA50
    t3 = 0x50000000;
    t3 = t3 | 0x6;
    ppacw(t3, t3, t8);
    pcpyld(v1, v1, v0);
    sq(v1, a2, 96);
    v0 = t9 | a0;
    ld(v1, sp, 0xD8);
    pcpyld(t4, t5, t4);
    pcpyld(t5, a1, v0);
    ppacw(a3, t3, t0);
    pcpyld(v1, s3, v1);
    a0 = 67;
    v0 = 9;
    pcpyld(t3, a0, s0);
    sq(v1, a2, 112);
    pcpyld(t0, v0, s2);
    lbu(s0, s4, 41);
    a0 = 72;
    v1 = 79;
    pcpyld(a1, a0, s6);
    lbu(s2, s4, 40);
    pcpyld(a0, v1, s7);
    v1 = 0x6C010000;
    v0 = 21;
    v1 = v1 | 0x3FA;
    s3 = 0;
    v1 = dsll32(v1, 0);
    v1 = t2 | v1;
    t2 = s2 & 0x1;
    t2 = dsll32(t2, 0);
    t2 = dsra32(t2, 0);
    t2 = dsll(t2, 5);
    t2 = t2 | 0x258;
    t2 = t2 | s0;
    t2 = dsll(t2, 15);
    t2 = t2 | s1;
    t2 = dsll32(t2, 0);
    pcpyld(t2, t7, t2);
    sq(t2, a2, 128);
    pcpyld(v1, v1, s3);
    lq(t2, sp, 0x90);
    sq(t2, a2, 144);
    lq(t2, sp, 0xA0);
    sq(t2, a2, 160);
    lwu(t7, sp, 0xB8);
    ld(t2, sp, 0xB0);
    t6 = t6 | t7;
    pcpyld(t2, t6, t2);
    sq(t2, a2, 176);
    sq(t4, a2, 192);
    sq(a3, a2, 208);
    sq(t5, a2, 224);
    sq(t3, a2, 240);
    sq(t0, a2, 256);
    sq(a1, a2, 272);
    ld(a1, sp, 0xE0);
    pcpyld(v0, v0, a1);
    sq(v0, a2, 288);
    sq(a0, a2, 304);
    sw(t1, gp, -17148);  // 0x7CE9F4
    sq(v1, a2, 320);
    lw(v1, gp, -17148);  // 0x7CE9F4
    lw(v0, gp, -16952);  // 0x7CEAB8
    t1 = addiu(v1, 16);
    sw(t1, gp, -17148);  // 0x7CE9F4
    lbu(v1, s4, 71);
    v1 = v1 ^ 0xFF;
    v1 = sltu(0, v1);
    v0 = v1 | v0;
    sw(v1, gp, -16956);  // 0x7CEAB4
    if (v0 == 0) {
        backedge(ctx);
        // 0x0046d000
        charge(ctx, 4);
        ld(v1, gp, -20272);  // 0x7CDDC0
        v0 = si(-65);
        v0 = v1 & v0;
        sd(v0, gp, -20272);  // 0x7CDDC0
    } else {
        // 0x0046d61c
        charge(ctx, 2);
        ld(v0, gp, -20272);  // 0x7CDDC0
        backedge(ctx);
        // 0x0046cff4
        charge(ctx, 3);
        v0 = v0 | 0x40;
        sd(v0, gp, -20272);  // 0x7CDDC0
    }
    // 0x0046d010
    charge(ctx, 43);
    v0 = 0x960000;
    lbu(a3, s4, 41);
    ld(a0, v0, 22688);  // 0x9658A0
    v1 = lui(0xFC00);
    a1 = dsll32(t1, 0);
    ld(t0, gp, -20272);  // 0x7CDDC0
    a1 = dsra32(a1, 0);
    a3 = dsll32(a3, 0);
    v0 = v1 | 0x7FFF;
    a3 = dsra32(a3, 0);
    v1 = dsll32(v0, 0);
    a3 = t0 | a3;
    v0 = 0xFFFF;
    v0 = dsll(v0, 16);
    v0 = v0 | 0xFFFF;
    v1 = v0 | v1;
    pcpyld(v1, zero, v1);
    t2 = a0 & v1;
    v0 = 0x960000;
    v1 = 0x6C010000;
    ld(a2, v0, 22696);  // 0x9658A8
    a0 = v1 | 0x3FB;
    v1 = 0x1000000;
    a0 = dsll32(a0, 0);
    v1 = v1 | 0x404;  // &0x1000404
    a0 = v1 | a0;
    v1 = dsll32(a3, 0);
    v1 = dsra32(v1, 0);
    v0 = 0x960000;
    a3 = v1 & 0x7FF;
    a3 = dsll32(a3, 15);
    v1 = t0 & 0x10;
    a3 = t2 | a3;
    t0 = 0;
    pcpyld(a2, a2, a3);
    sq(a2, v0, 22688);  // 0x9658A0
    pcpyld(a0, a0, t0);
    sq(a2, a1, 0);
    sq(a0, a1, 16);
    lw(v0, gp, -17148);  // 0x7CE9F4
    t1 = addiu(v0, 32);
    sw(t1, gp, -17148);  // 0x7CE9F4
    if (v1 == 0) {
        // 0x0046d0d0
        charge(ctx, 4);
        v0 = 0x3B800000;
        v0 = v0 | 0x8081;
        mtc1(v0, f12);
        a0 = addiu(s4, 68);
    } else {
        // 0x0046d0bc
        charge(ctx, 5);
        v0 = 0x3B010000;
        v0 = v0 | 0x1B50;
        mtc1(v0, f12);
        a0 = addiu(s4, 68);
    }
    // 0x0046d0e0
    charge(ctx, 32);
    pass.colour_at = write_ptr(ctx);
    jal(ctx, 0x46D0E0u, gen::fn_sub_49CAB0_0049cab0);
    v1 = 0x6C010000;
    v0 = 0x1000000;
    v1 = v1 | 0x3FC;
    v0 = v0 | 0x404;  // &0x1000404
    v1 = dsll32(v1, 0);
    a0 = 0;
    v1 = v0 | v1;
    lw(v0, gp, -17148);  // 0x7CE9F4
    pcpyld(v1, v1, a0);
    sq(v1, v0, 0);
    lw(v0, gp, -17148);  // 0x7CE9F4
    t1 = addiu(v0, 16);
    sw(t1, gp, -17148);  // 0x7CE9F4
    lwc1(f12, s4, 28);
    pass.surface_at = write_ptr(ctx);
    link(ctx, 0x46D120u);  // $ra first: the delay slot below depends on it
    lw(a0, s4, 60);
    call(ctx, gen::fn_sub_49CBD0_0049cbd0);
    v0 = 0x6C030000;
    lbu(a0, s4, 40);
    v1 = v0 | 0x3FD;
    v0 = 0x1000000;
    v1 = dsll32(v1, 0);
    v0 = v0 | 0x404;  // &0x1000404
    v0 = v0 | v1;
    v1 = 0;
    pcpyld(a1, v0, v1);
    lw(v1, gp, -17148);  // 0x7CE9F4
    sq(a1, v1, 0);
    lw(v1, gp, -16876);  // 0x7CEB04
    v0 = a0 & 0x7;
    if (v1 != 0) {
        // 0x0046d160
        charge(ctx, 3);
        v1 = v0 & 0x4;
        if (v1 != 0) {
            goto L_0046d16c;
        }
    L_0046d184:
        charge(ctx, 11);
        a0 = 0x960000;
        lw(a1, gp, -17148);  // 0x7CE9F4
        lq(a0, a0, 22832);  // 0x965930
        v1 = 0x960000;
        v0 = v0 | 0x8;
        sq(a0, a1, 16);
        lq(v1, v1, 22848);  // 0x965940
        sq(v1, a1, 32);
        lw(v1, gp, -17148);  // 0x7CE9F4
        t1 = addiu(v1, 48);
        sw(t1, gp, -17148);  // 0x7CE9F4
        goto L_0046d1b0;
    }
L_0046d16c:
    charge(ctx, 3);
    lw(v1, gp, -20232);  // 0x7CDDE8
    if (v1 != 0) {
        // 0x0046d178
        charge(ctx, 3);
        v1 = v0 & 0x4;
        if (v1 == 0) {
            goto L_0046d624;
        }
        goto L_0046d184;
    }
L_0046d624:
    charge(ctx, 11);
    v1 = 0x960000;
    lw(a1, gp, -17148);  // 0x7CE9F4
    lq(a0, v1, 22800);  // 0x965910
    v1 = 0x960000;
    sq(a0, a1, 16);
    lq(v1, v1, 22816);  // 0x965920
    sq(v1, a1, 32);
    lw(v1, gp, -17148);  // 0x7CE9F4
    t1 = addiu(v1, 48);
    sw(t1, gp, -17148);  // 0x7CE9F4
    backedge(ctx);
L_0046d1b0:
    charge(ctx, 5);
    lw(a1, gp, -16964);  // 0x7CEAAC
    a0 = 3;
    sw(zero, gp, -16884);  // 0x7CEAFC
    v1 = 0;
    if (a1 == a0) {
        // 0x0046d650
        charge(ctx, 3);
        v1 = 32;
        sw(v1, gp, -16884);  // 0x7CEAFC
        backedge(ctx);
    }
    // 0x0046d1c4
    charge(ctx, 17);
    lwu(a1, gp, -16880);  // 0x7CEB00
    a0 = dsll32(v1, 0);
    v1 = dsll32(v0, 0);
    a0 = dsrl32(a0, 0);
    v0 = dsll32(t1, 0);
    v1 = dsrl32(v1, 0);
    v0 = dsra32(v0, 0);
    a1 = dsll32(a1, 0);
    a0 = a1 | a0;
    pcpyld(v1, a0, v1);
    sq(v1, v0, 0);
    lw(v0, gp, -17148);  // 0x7CE9F4
    t1 = addiu(v0, 16);
    sw(t1, gp, -17148);  // 0x7CE9F4
    lw(v0, s4, 64);
    if (v0 == 0) {
        // 0x0046d65c
        charge(ctx, 25);
        a1 = dsll32(t1, 0);
        v0 = 0x50000000;
        a1 = dsra32(a1, 0);
        v0 = v0 | 0x2;
        sq(zero, a1, 0);
        v0 = dsll32(v0, 0);
        v1 = 0;
        sq(zero, a1, 16);
        pcpyld(v0, v0, v1);
        sq(v0, a1, 32);
        a0 = 14;
        v0 = 0x10000000;
        v1 = dsll32(v0, 0);
        v0 = 0x8001;
        v1 = v0 | v1;
        pcpyld(v1, a0, v1);
        sq(v1, a1, 48);
        v0 = 71;
        ld(v1, gp, -17072);  // 0x7CEA40
        pcpyld(v0, v0, v1);
        sq(v0, a1, 64);
        lw(v0, gp, -17148);  // 0x7CE9F4
        t1 = addiu(v0, 80);
        sw(t1, gp, -17148);  // 0x7CE9F4
        backedge(ctx);
    } else {
        // 0x0046d208
        charge(ctx, 30);
        v0 = 0x50000000;
        a2 = dsll32(t1, 0);
        v0 = v0 | 0x4;
        v1 = 0;
        v0 = dsll32(v0, 0);
        a2 = dsra32(a2, 0);
        pcpyld(v0, v0, v1);
        sq(v0, a2, 0);
        a1 = 14;
        v0 = 0x10000000;
        a0 = 71;
        v1 = dsll32(v0, 0);
        v0 = 0x8003;
        v0 = v0 | v1;
        pcpyld(v0, a1, v0);
        sq(v0, a2, 16);
        v1 = 20;
        ld(a1, gp, -17072);  // 0x7CEA40
        v0 = 8;
        pcpyld(a0, a0, a1);
        sq(a0, a2, 32);
        ld(a0, gp, -17040);  // 0x7CEA60
        pcpyld(v1, v1, a0);
        sq(v1, a2, 48);
        ld(v1, gp, -17048);  // 0x7CEA58
        pcpyld(v0, v0, v1);
        sq(v0, a2, 64);
        lw(v0, gp, -17148);  // 0x7CE9F4
        t1 = addiu(v0, 80);
        sw(t1, gp, -17148);  // 0x7CE9F4
    }
    // 0x0046d280
    charge(ctx, 16);
    lbu(v0, s4, 40);
    v1 = v0 & 0x20;
    v0 = v0 & 0x18;
    v1 = sra(v1, 5);
    v0 = sra(v0, 2);
    v0 = v1 | v0;
    sb(v0, s4, 43);
    lw(v1, s4, 4);
    lbu(a0, s4, 43);
    lw(v0, gp, -16888);  // 0x7CEAF8
    lw(v1, v1, 24);
    a0 = sll(a0, 2);
    v1 = addu(v1, a0);
    lw(a0, v1, 0);
    pass.program = a0.u();
    pass.uploaded = v0 != a0;
    if (v0 != a0) {
        // 0x0046d2c0
        charge(ctx, 13);
        v0 = dsll32(a0, 0);
        a1 = 0;
        v0 = dsrl32(v0, 0);
        v1 = dsll32(v0, 0);
        v0 = 0x50000000;
        v1 = v1 | v0;
        lw(v0, gp, -17148);  // 0x7CE9F4
        pcpyld(v1, a1, v1);
        sq(v1, v0, 0);
        lw(v0, gp, -17148);  // 0x7CE9F4
        sw(a0, gp, -16888);  // 0x7CEAF8
        t1 = addiu(v0, 16);
        sw(t1, gp, -17148);  // 0x7CE9F4
    }
    // 0x0046d2f4
    charge(ctx, 21);
    lw(a2, s4, 48);
    t0 = 0x2000000;
    lw(a0, s4, 4);
    a3 = 0x3000000;
    lw(v1, gp, -17148);  // 0x7CE9F4
    a1 = 0x50000000;
    v0 = 0x10000;
    lw(a2, a2, 0);
    lw(t1, a0, 20);
    a0 = addiu(a2, 24);
    t0 = t1 | t0;
    lwu(a2, a2, 32);
    t0 = dsll32(t0, 0);
    a3 = t0 | a3;
    a2 = dsll32(a2, 0);
    a1 = a2 | a1;
    pcpyld(a1, a3, a1);
    sq(a1, v1, 0);
    lw(v1, gp, -17148);  // 0x7CE9F4
    t1 = addiu(v1, 16);
    sw(t1, gp, -17148);  // 0x7CE9F4
    pass.res_entry = a2.u();
    pass.vif_offset = t1.u();
    for (;;) {
        // 0x0046d348
        charge(ctx, 7);
        di(ctx);
        sync(ctx, 16);
        mfc0(v1, 12);
        v1 = v1 & v0;
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0046d364
    charge(ctx, 11);
    lw(v0, a0, 0);
    v0 = addiu(v0, 1);
    sw(v0, a0, 0);
    ei(ctx);
    v0 = 1;
    lw(v1, a0, 4);
    v1 = addiu(v1, 1);
    sw(v1, a0, 4);
    lw(v1, a0, 4);
    if (v1 == v0) {
        // 0x0046d390
        charge(ctx, 2);
        jal(ctx, 0x46D390u, gen::fn__rwDMAAddPURef_004d51c0);
    }
    // 0x0046d398
    charge(ctx, 29);
    a0 = 0;
    a1 = 3;
    jal(ctx, 0x46D39Cu, gen::fn__rwDMAOpenVIFPkt_004d59d0);
    v0 = 0x50000000;
    v1 = 0;
    v0 = v0 | 0x2;
    a3 = 0;
    ppacw(t0, v0, v1);
    lw(a2, gp, -17148);  // 0x7CE9F4
    closing_at = a2.u();  // the closing packet
    v0 = 0x10000000;
    a1 = 14;
    a0 = v0 | 0x2;
    v1 = dsll32(v0, 0);
    ppacw(v0, a3, a0);
    ppacw(v0, t0, v0);
    sq(v0, a2, 0);
    a0 = 61;
    v0 = 0x8001;
    v0 = v0 | v1;
    pcpyld(v0, a1, v0);
    sq(v0, a2, 16);
    ld(v1, gp, -17056);  // 0x7CEA50
    v0 = 1;
    pcpyld(v1, a0, v1);
    sq(v1, a2, 32);
    lw(v1, gp, -17148);  // 0x7CE9F4
    t1 = addiu(v1, 48);
    sw(t1, gp, -17148);  // 0x7CE9F4
    report_mesh(ctx, s4.u(), pass);
    report_effect(ctx, Effect::EnvMap, s4.u(), rd32(ctx, matfx_ext(ctx, s4.u()) + 4), extra_at, 20, closing_at, 3);
    // 0x0046d6c0
    charge(ctx, 11);
    ld(ra, sp, 0x80);
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

// 0x0046D6F0 matfxBridgeBumpEnvMap -- 2680 bytes; frame 0x140: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// matfxBridgeBumpEnvMap [MatFX bump + environment-map bridge] ($a0 = PipeData). Slot 0 (bump): +0 frame, +4 texture (0 = the
// material's), +12 coefficient, +16 inverse width; slot 1 (environment): +64 frame, +68 texture, +72 coefficient,
// +104 ALPHA_2, +112 FOGCOL (used as given), +120 TEST_2 bits. Frame 320: s0..s8, $ra at +144; the environment
// matrix at sp+160 and the bump matrix at sp+224 (two matfxEffectMatrix calls), the environment texture's TEX0 halves at
// sp+288 / sp+292 and TEX1 at sp+304, the base (bump) texture's TEX0 at sp+296 / sp+300, the bump scale at sp+312,
// the environment coefficient at sp+316. s4 = PipeData, s3 = the base texture, s2 = the environment texture, s0 =
// the environment frame, s5 = ALPHA_2, s6 = FOGCOL, s7 = TEST_2, s8 = ZBUF_1, s1 = CLAMP_2 bits. Its own camera
// cache words: gp-20916 (far) / gp-20920 (1 / (far - near)).
// The texture placement and GS state are dual_bridge's with these registers (the PipeData's texture is not
// replaced here). The register block (_rwDMAOpenVIFPkt(0, 51), DMA cnt 43) is STCYCL 1,1 / UNPACK V4-32 x20 to VU1
// 0x3BC: {scale, 0, 1/(far-near), far}, the bump passes' A+D blocks (GIF tag NLOOP 4: ALPHA_1 2 | 128 << 32,
// TEST_1 alpha-test bits, FOGCOL = the driver's, TEX0_1 of the base; GIF tag NLOOP 2: ALPHA_1 72 | 128 << 32,
// TEST_1), the bump matrix rows, the environment pass's A+D block (FOGCOL = the effect's, TEX0_2), its vertex GIF
// tag, the environment matrix rows (row 2 with the coefficient in w) and the constant quadword 0x6B5160; then
// DIRECT 6 (ALPHA_2 / CLAMP_2 / TEST_2 / TEX1_2 / ZBUF_2) and the stock packet. The closing packet (DIRECT 4)
// restores ALPHA_1, TEST_1 and FOGCOL from the shadows.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void matfxBridgeBumpEnvMap(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::c_eq_s, hg::call, hg::charge, hg::cond, hg::di,
          hg::div_s, hg::dsll, hg::dsll32, hg::dsra32, hg::dsrl32, hg::ei, hg::enter, hg::jal, hg::lbu, hg::ld,
          hg::link, hg::lq, hg::lui, hg::lw, hg::lwc1, hg::lwu, hg::mfc0, hg::mtc1, hg::mul_s, hg::pcpyld, hg::ppacw,
          hg::sb, hg::sd, hg::si, hg::sll, hg::slti, hg::sltu, hg::sq, hg::sra, hg::srl, hg::sub_s, hg::sw, hg::swc1,
          hg::sync;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    u32 extra_at = 0, closing_at = 0;  // draw records (host-only): where the effect's packets went
    Pass pass;
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12};
    // 0x0046d6f0
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x140);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, 44);
    lw(v0, gp, -17848);  // 0x7CE738
    lw(v1, v1, 8);
    v0 = addu(v1, v0);
    lw(v0, v0, 0);
    lwc1(f1, v0, 12);
    lw(s3, v0, 4);
    lwc1(f0, v0, 16);
    lw(a0, v0, 0);
    mul_s(f0, f1, f0);
    swc1(f0, sp, 0x138);
    if (s3 == 0) {
        // 0x0046ddf4
        charge(ctx, 2);
        lw(s3, v1, 0);
        backedge(ctx);
    }
    // 0x0046d750
    charge(ctx, 28);
    lwc1(f0, v0, 72);
    lw(s2, v0, 68);
    lw(s0, v0, 64);
    v1 = 0x70000;
    ld(s5, v0, 104);
    a1 = addiu(sp, 0xE0);
    ld(s6, v0, 112);
    a2 = s4;
    ld(a3, gp, -17072);  // 0x7CEA40
    s1 = 0;
    ld(fp, gp, -17088);  // 0x7CEA30
    swc1(f0, sp, 0x13C);
    ld(v0, v0, 120);
    v1 = a3 & v1;
    s7 = v1 | v0;
    link(ctx, 0x46D78Cu);  // $ra first: the delay slot below depends on it
    sd(zero, sp, 0x130);
    call(ctx, gen::fn_matfxEffectMatrix_0046b060);
    a0 = s0;
    a1 = addiu(sp, 0xA0);
    a2 = s4;
    jal(ctx, 0x46D79Cu, gen::fn_matfxEffectMatrix_0046b060);
    v0 = 0x960000;
    lw(v0, v0, 112);  // 0x960070
    lwc1(f0, gp, -20916);  // 0x7CDB3C
    lwc1(f2, v0, 132);
    c_eq_s(f2, f0);
    if (!cond(ctx)) {
        // 0x0046d7c0
        charge(ctx, 8);
        lwc1(f1, v0, 128);
        swc1(f2, gp, -20916);  // 0x7CDB3C
        sub_s(f1, f2, f1);
        v0 = 0x3F800000;
        mtc1(v0, f0);
        div_s(f0, f0, f1);
        swc1(f0, gp, -20920);  // 0x7CDB38
    }
    // 0x0046d7e0
    charge(ctx, 4);
    sd(zero, sp, 0x128);
    sd(zero, sp, 0x120);
    sw(zero, gp, -16952);  // 0x7CEAB8
    if (s3 != 0) {
        // 0x0046d7f0
        charge(ctx, 8);
        link(ctx, 0x46D7F0u);  // $ra first: the delay slot below depends on it
        lw(a0, s3, 0);
        call(ctx, gen::fn_sub_4F0F30_004f0f30);
        lw(v1, s3, 0);
        v0 = 6;
        lbu(v1, v1, 35);
        v1 = v1 & 0xF;
        if (v1 != v0) {
            // 0x0046d810
            charge(ctx, 2);
            v0 = 1;
            sw(v0, gp, -16952);  // 0x7CEAB8
        }
    }
    // 0x0046d818
    charge(ctx, 2);
    if (s2 != 0) {
        // 0x0046d820
        charge(ctx, 5);
        link(ctx, 0x46D820u);  // $ra first: the delay slot below depends on it
        lw(a0, s2, 0);
        call(ctx, gen::fn_sub_4F0F30_004f0f30);
        lw(a0, s2, 0);
        a1 = 1;
        jal(ctx, 0x46D82Cu, gen::fn_RpSkyTexCacheAccessRaster_004f1020);
    }
    // 0x0046d834
    charge(ctx, 2);
    if (s3 != 0) {
        // 0x0046d83c
        charge(ctx, 3);
        lw(a0, s3, 0);
        a1 = 0;
        jal(ctx, 0x46D840u, gen::fn_RpSkyTexCacheAccessRaster_004f1020);
    }
    // 0x0046d848
    charge(ctx, 2);
    if (s2 != 0) {
        // 0x0046d850
        charge(ctx, 6);
        lw(a0, s2, 0);
        lw(v0, gp, -16968);  // 0x7CEAA8
        v0 = addu(a0, v0);
        lw(v0, v0, 88);
        if (v0 == 0) {
            // 0x0046d868
            charge(ctx, 2);
            a1 = 1;
            jal(ctx, 0x46D868u, gen::fn_RpSkyTexCacheAccessRaster_004f1020);
        }
    }
    // 0x0046d870
    charge(ctx, 2);
    if (s3 != 0) {
        // 0x0046d878
        charge(ctx, 6);
        lw(a0, s3, 0);
        lw(v0, gp, -16968);  // 0x7CEAA8
        v0 = addu(a0, v0);
        lw(v0, v0, 88);
        if (v0 == 0) {
            // 0x0046d890
            charge(ctx, 2);
            a1 = 0;
            jal(ctx, 0x46D890u, gen::fn_RpSkyTexCacheAccessRaster_004f1020);
        }
    }
    // 0x0046d898
    charge(ctx, 2);
    if (s3 == 0) {
        // 0x0046de0c
        charge(ctx, 6);
        ld(v1, gp, -20272);  // 0x7CDDC0
        v0 = si(-17);
        sw(zero, gp, -16948);  // 0x7CEABC
        v0 = v1 & v0;
        sd(v0, gp, -20272);  // 0x7CDDC0
        backedge(ctx);
    } else {
        // 0x0046d8a0
        charge(ctx, 20);
        ld(v0, gp, -20272);  // 0x7CDDC0
        a1 = addiu(sp, 0x12C);
        v0 = v0 | 0x10;
        sd(v0, gp, -20272);  // 0x7CDDC0
        lw(v0, s3, 0);
        sw(v0, gp, -16948);  // 0x7CEABC
        lw(a0, s3, 0);
        a2 = addiu(sp, 0x128);
        jal(ctx, 0x46D8BCu, gen::fn_sub_4F1E20_004f1e20);
        lbu(a2, s3, 80);
        lw(a0, s3, 0);
        a1 = addiu(gp, -17040);  // &0x7CEA60
        jal(ctx, 0x46D8CCu, gen::fn_sub_4F1E40_004f1e40);
        sd(zero, gp, -17048);  // 0x7CEA58
        v0 = 3;
        lw(v1, s3, 80);
        v1 = v1 & 0xF00;
        v1 = srl(v1, 8);
        if (v1 == v0) {
            // 0x0046ddfc
            charge(ctx, 4);
            ld(v0, gp, -17048);  // 0x7CEA58
            v0 = v0 | 0x1;
            sd(v0, gp, -17048);  // 0x7CEA58
            backedge(ctx);
        }
        // 0x0046d8f0
        charge(ctx, 6);
        lw(v1, s3, 80);
        v0 = 3;
        v1 = v1 & 0xF000;
        v1 = srl(v1, 12);
        if (v1 == v0) {
            // 0x0046d908
            charge(ctx, 3);
            ld(v0, gp, -17048);  // 0x7CEA58
            v0 = v0 | 0x4;
            sd(v0, gp, -17048);  // 0x7CEA58
        }
    }
    // 0x0046d914
    charge(ctx, 4);
    ld(v0, gp, -17072);  // 0x7CEA40
    v0 = v0 | 0x1;
    sd(v0, gp, -17072);  // 0x7CEA40
    if (s2 != 0) {
        // 0x0046d924
        charge(ctx, 14);
        lw(a0, s2, 0);
        a1 = addiu(sp, 0x124);
        a2 = addiu(sp, 0x120);
        jal(ctx, 0x46D92Cu, gen::fn_sub_4F1E20_004f1e20);
        lbu(a2, s2, 80);
        lw(a0, s2, 0);
        a1 = addiu(sp, 0x130);
        jal(ctx, 0x46D93Cu, gen::fn_sub_4F1E40_004f1e40);
        lw(a0, s2, 80);
        v0 = 3;
        v1 = a0 & 0xF00;
        v1 = srl(v1, 8);
        s1 = 0;
        if (v1 == v0) {
            // 0x0046d95c
            charge(ctx, 1);
            s1 = s1 | 0x1;
        }
        // 0x0046d960
        charge(ctx, 5);
        v1 = a0 & 0xF000;
        v0 = 3;
        v1 = srl(v1, 12);
        if (v1 == v0) {
            // 0x0046d974
            charge(ctx, 1);
            s1 = s1 | 0x4;
        }
    }
    // 0x0046d978
    charge(ctx, 2);
    if (s3 != 0) {
        // 0x0046d980
        charge(ctx, 5);
        lw(v0, s3, 0);
        lw(v0, v0, 20);
        at = slti(v0, 9);
        if (at != 0) {
            // 0x0046d994
            charge(ctx, 2);
            if (s2 != 0) {
                // 0x0046d99c
                charge(ctx, 5);
                lw(v0, s2, 0);
                lw(v0, v0, 20);
                at = slti(v0, 9);
                if (at != 0) {
                    // 0x0046d9b0
                    charge(ctx, 3);
                    v0 = si(-1);
                    sw(v0, gp, -16948);  // 0x7CEABC
                }
            }
        }
    }
    // 0x0046de24
    charge(ctx, 156);
    a0 = 0;
    a1 = 51;
    jal(ctx, 0x46DE28u, gen::fn__rwDMAOpenVIFPkt_004d59d0);
    lw(t0, gp, -17148);  // 0x7CE9F4
    extra_at = t0.u();  // the effect's extra quadwords start here
    v0 = 0x10000000;
    lwu(a2, gp, -20916);  // 0x7CDB3C
    a1 = 0;
    a0 = v0 | 0x2B;
    v1 = dsll32(v0, 0);
    pcpyld(t2, a1, a0);
    lwu(a3, sp, 0x138);
    a0 = 0x6C140000;
    v0 = 0x1000000;
    a1 = a0 | 0x3BC;
    t4 = v0 | 0x404;  // &0x1000404
    a0 = v0 | 0x101;  // &0x1000101
    sq(t2, t0, 0);
    t0 = 0;
    v0 = 0;
    ppacw(t2, t0, v0);
    ppacw(t1, a1, a0);
    lwu(v0, sp, 0x13C);
    lwu(a0, gp, -20920);  // 0x7CDB38
    ppacw(t0, t1, t2);
    lw(a1, gp, -17148);  // 0x7CE9F4
    a2 = dsll32(a2, 0);
    s0 = dsll32(v0, 0);
    s2 = 66;
    t1 = 0x70000;
    v0 = a2 | a0;
    t5 = 72;
    a0 = addiu(a1, 16);
    t7 = 71;
    sw(a0, gp, -17148);  // 0x7CE9F4
    pcpyld(v0, v0, a3);
    sq(t0, a1, 16);
    t3 = addiu(a0, 448);
    sq(v0, a1, 32);
    t0 = 0x8002;
    v0 = 0x8004;
    a0 = 14;
    a2 = v0 | v1;
    t0 = t0 | v1;
    v0 = 128;
    t8 = 6;
    a3 = dsll32(v0, 0);
    t9 = 7;
    v0 = 2;
    v0 = v0 | a3;
    pcpyld(a2, a0, a2);
    sq(a2, a1, 48);
    pcpyld(v0, s2, v0);
    sq(v0, a1, 64);
    a3 = t5 | a3;
    ld(t6, gp, -17072);  // 0x7CEA40
    v0 = 61;
    pcpyld(a2, v0, s6);
    pcpyld(s6, t5, s7);
    t5 = 0x6B0000;
    s7 = 0;
    pcpyld(a3, s2, a3);
    pcpyld(t0, a0, t0);
    t1 = t6 & t1;
    pcpyld(t1, t7, t1);
    ld(t7, t5, 20840);  // 0x6B5168
    t6 = 0x30000000;
    sq(t1, a1, 80);
    s2 = t6 | 0x4000;
    ld(s3, gp, -17056);  // 0x7CEA50
    t5 = 0x6B0000;
    ld(t6, t5, 20832);  // 0x6B5160
    pcpyld(v0, v0, s3);
    sq(v0, a1, 96);
    v0 = 0x8005;
    v0 = v0 | v1;
    pcpyld(a0, a0, v0);
    t5 = 0x50000000;
    v1 = 9;
    t5 = t5 | 0x6;
    ppacw(t5, t5, s7);
    ppacw(t5, t5, t2);
    ld(t2, sp, 0x128);
    pcpyld(t6, t7, t6);
    t7 = 67;
    pcpyld(v0, t7, s5);
    pcpyld(t7, v1, s1);
    v1 = 21;
    s1 = 0;
    pcpyld(t2, t8, t2);
    sq(t2, a1, 112);
    sq(t0, a1, 128);
    sq(a3, a1, 144);
    sq(t1, a1, 160);
    lq(a3, sp, 0xE0);
    t1 = 79;
    pcpyld(t2, t1, fp);
    t1 = 0x6C010000;
    t1 = t1 | 0x3FA;
    t1 = dsll32(t1, 0);
    t1 = t4 | t1;
    sq(a3, a1, 176);
    pcpyld(t1, t1, s1);
    lq(a3, sp, 0xF0);
    sq(a3, a1, 192);
    lq(a3, sp, 0x100);
    sq(a3, a1, 208);
    sq(t0, a1, 224);
    sq(a2, a1, 240);
    ld(a2, sp, 0x120);
    pcpyld(a2, t9, a2);
    sq(a2, a1, 256);
    lbu(a3, s4, 40);
    lbu(a2, s4, 41);
    a3 = a3 & 0x1;
    a3 = dsll32(a3, 0);
    a3 = dsra32(a3, 0);
    a3 = dsll(a3, 5);
    a3 = a3 | 0x258;
    a2 = a3 | a2;
    a2 = dsll(a2, 15);
    a2 = a2 | s2;
    a3 = dsll32(a2, 0);
    a2 = 1042;
    pcpyld(a2, a2, a3);
    sq(a2, a1, 272);
    lq(a2, sp, 0xA0);
    sq(a2, a1, 288);
    lq(a2, sp, 0xB0);
    sq(a2, a1, 304);
    lwu(a3, sp, 0xC8);
    ld(a2, sp, 0xC0);
    a3 = s0 | a3;
    pcpyld(a2, a3, a2);
    sq(a2, a1, 320);
    sq(t6, a1, 336);
    sq(t5, a1, 352);
    sq(a0, a1, 368);
    sq(v0, a1, 384);
    sq(t7, a1, 400);
    sq(s6, a1, 416);
    ld(v0, sp, 0x130);
    pcpyld(v0, v1, v0);
    sq(v0, a1, 432);
    sq(t2, a1, 448);
    sw(t3, gp, -17148);  // 0x7CE9F4
    sq(t1, a1, 464);
    lw(v1, gp, -17148);  // 0x7CE9F4
    lw(v0, gp, -16952);  // 0x7CEAB8
    t3 = addiu(v1, 16);
    sw(t3, gp, -17148);  // 0x7CE9F4
    lbu(v1, s4, 71);
    v1 = v1 ^ 0xFF;
    v1 = sltu(0, v1);
    v0 = v1 | v0;
    sw(v1, gp, -16956);  // 0x7CEAB4
    if (v0 == 0) {
        backedge(ctx);
        // 0x0046d9c8
        charge(ctx, 4);
        ld(v1, gp, -20272);  // 0x7CDDC0
        v0 = si(-65);
        v0 = v1 & v0;
        sd(v0, gp, -20272);  // 0x7CDDC0
    } else {
        // 0x0046e094
        charge(ctx, 2);
        ld(v0, gp, -20272);  // 0x7CDDC0
        backedge(ctx);
        // 0x0046d9bc
        charge(ctx, 3);
        v0 = v0 | 0x40;
        sd(v0, gp, -20272);  // 0x7CDDC0
    }
    // 0x0046d9d8
    charge(ctx, 43);
    v0 = 0x960000;
    lbu(a3, s4, 41);
    ld(a0, v0, 22688);  // 0x9658A0
    v1 = lui(0xFC00);
    a1 = dsll32(t3, 0);
    ld(t0, gp, -20272);  // 0x7CDDC0
    a1 = dsra32(a1, 0);
    a3 = dsll32(a3, 0);
    v0 = v1 | 0x7FFF;
    a3 = dsra32(a3, 0);
    v1 = dsll32(v0, 0);
    a3 = t0 | a3;
    v0 = 0xFFFF;
    v0 = dsll(v0, 16);
    v0 = v0 | 0xFFFF;
    v1 = v0 | v1;
    pcpyld(v1, zero, v1);
    t1 = a0 & v1;
    v0 = 0x960000;
    v1 = 0x6C010000;
    ld(a2, v0, 22696);  // 0x9658A8
    a0 = v1 | 0x3FB;
    v1 = 0x1000000;
    a0 = dsll32(a0, 0);
    v1 = v1 | 0x404;  // &0x1000404
    a0 = v1 | a0;
    v1 = dsll32(a3, 0);
    v1 = dsra32(v1, 0);
    v0 = 0x960000;
    a3 = v1 & 0x7FF;
    a3 = dsll32(a3, 15);
    v1 = t0 & 0x10;
    a3 = t1 | a3;
    t0 = 0;
    pcpyld(a2, a2, a3);
    sq(a2, v0, 22688);  // 0x9658A0
    pcpyld(a0, a0, t0);
    sq(a2, a1, 0);
    sq(a0, a1, 16);
    lw(v0, gp, -17148);  // 0x7CE9F4
    t3 = addiu(v0, 32);
    sw(t3, gp, -17148);  // 0x7CE9F4
    if (v1 == 0) {
        // 0x0046da98
        charge(ctx, 4);
        v0 = 0x3B800000;
        v0 = v0 | 0x8081;
        mtc1(v0, f12);
        a0 = addiu(s4, 68);
    } else {
        // 0x0046da84
        charge(ctx, 5);
        v0 = 0x3B010000;
        v0 = v0 | 0x1B50;
        mtc1(v0, f12);
        a0 = addiu(s4, 68);
    }
    // 0x0046daa8
    charge(ctx, 32);
    pass.colour_at = write_ptr(ctx);
    jal(ctx, 0x46DAA8u, gen::fn_sub_49CAB0_0049cab0);
    v1 = 0x6C010000;
    v0 = 0x1000000;
    v1 = v1 | 0x3FC;
    v0 = v0 | 0x404;  // &0x1000404
    v1 = dsll32(v1, 0);
    a0 = 0;
    v1 = v0 | v1;
    lw(v0, gp, -17148);  // 0x7CE9F4
    pcpyld(v1, v1, a0);
    sq(v1, v0, 0);
    lw(v0, gp, -17148);  // 0x7CE9F4
    t3 = addiu(v0, 16);
    sw(t3, gp, -17148);  // 0x7CE9F4
    lwc1(f12, s4, 28);
    pass.surface_at = write_ptr(ctx);
    link(ctx, 0x46DAE8u);  // $ra first: the delay slot below depends on it
    lw(a0, s4, 60);
    call(ctx, gen::fn_sub_49CBD0_0049cbd0);
    v0 = 0x6C030000;
    lbu(a0, s4, 40);
    v1 = v0 | 0x3FD;
    v0 = 0x1000000;
    v1 = dsll32(v1, 0);
    v0 = v0 | 0x404;  // &0x1000404
    v0 = v0 | v1;
    v1 = 0;
    pcpyld(a1, v0, v1);
    lw(v1, gp, -17148);  // 0x7CE9F4
    sq(a1, v1, 0);
    lw(v1, gp, -16876);  // 0x7CEB04
    v0 = a0 & 0x7;
    if (v1 != 0) {
        // 0x0046db28
        charge(ctx, 3);
        v1 = v0 & 0x4;
        if (v1 != 0) {
            goto L_0046db34;
        }
    L_0046db4c:
        charge(ctx, 11);
        a0 = 0x960000;
        lw(a1, gp, -17148);  // 0x7CE9F4
        lq(a0, a0, 22832);  // 0x965930
        v1 = 0x960000;
        v0 = v0 | 0x8;
        sq(a0, a1, 16);
        lq(v1, v1, 22848);  // 0x965940
        sq(v1, a1, 32);
        lw(v1, gp, -17148);  // 0x7CE9F4
        t3 = addiu(v1, 48);
        sw(t3, gp, -17148);  // 0x7CE9F4
        goto L_0046db78;
    }
L_0046db34:
    charge(ctx, 3);
    lw(v1, gp, -20232);  // 0x7CDDE8
    if (v1 != 0) {
        // 0x0046db40
        charge(ctx, 3);
        v1 = v0 & 0x4;
        if (v1 == 0) {
            goto L_0046e09c;
        }
        goto L_0046db4c;
    }
L_0046e09c:
    charge(ctx, 11);
    v1 = 0x960000;
    lw(a1, gp, -17148);  // 0x7CE9F4
    lq(a0, v1, 22800);  // 0x965910
    v1 = 0x960000;
    sq(a0, a1, 16);
    lq(v1, v1, 22816);  // 0x965920
    sq(v1, a1, 32);
    lw(v1, gp, -17148);  // 0x7CE9F4
    t3 = addiu(v1, 48);
    sw(t3, gp, -17148);  // 0x7CE9F4
    backedge(ctx);
L_0046db78:
    charge(ctx, 5);
    lw(a1, gp, -16964);  // 0x7CEAAC
    a0 = 3;
    sw(zero, gp, -16884);  // 0x7CEAFC
    v1 = 0;
    if (a1 == a0) {
        // 0x0046e0c8
        charge(ctx, 3);
        v1 = 32;
        sw(v1, gp, -16884);  // 0x7CEAFC
        backedge(ctx);
    }
    // 0x0046db8c
    charge(ctx, 17);
    lwu(a1, gp, -16880);  // 0x7CEB00
    a0 = dsll32(v1, 0);
    v1 = dsll32(v0, 0);
    a0 = dsrl32(a0, 0);
    v0 = dsll32(t3, 0);
    v1 = dsrl32(v1, 0);
    v0 = dsra32(v0, 0);
    a1 = dsll32(a1, 0);
    a0 = a1 | a0;
    pcpyld(v1, a0, v1);
    sq(v1, v0, 0);
    lw(v0, gp, -17148);  // 0x7CE9F4
    t3 = addiu(v0, 16);
    sw(t3, gp, -17148);  // 0x7CE9F4
    lw(v0, s4, 64);
    if (v0 == 0) {
        // 0x0046e0d4
        charge(ctx, 25);
        a1 = dsll32(t3, 0);
        v0 = 0x50000000;
        a1 = dsra32(a1, 0);
        v0 = v0 | 0x2;
        sq(zero, a1, 0);
        v0 = dsll32(v0, 0);
        v1 = 0;
        sq(zero, a1, 16);
        pcpyld(v0, v0, v1);
        sq(v0, a1, 32);
        a0 = 14;
        v0 = 0x10000000;
        v1 = dsll32(v0, 0);
        v0 = 0x8001;
        v1 = v0 | v1;
        pcpyld(v1, a0, v1);
        sq(v1, a1, 48);
        v0 = 71;
        ld(v1, gp, -17072);  // 0x7CEA40
        pcpyld(v0, v0, v1);
        sq(v0, a1, 64);
        lw(v0, gp, -17148);  // 0x7CE9F4
        t3 = addiu(v0, 80);
        sw(t3, gp, -17148);  // 0x7CE9F4
        backedge(ctx);
    } else {
        // 0x0046dbd0
        charge(ctx, 30);
        v0 = 0x50000000;
        a2 = dsll32(t3, 0);
        v0 = v0 | 0x4;
        v1 = 0;
        v0 = dsll32(v0, 0);
        a2 = dsra32(a2, 0);
        pcpyld(v0, v0, v1);
        sq(v0, a2, 0);
        a1 = 14;
        v0 = 0x10000000;
        a0 = 71;
        v1 = dsll32(v0, 0);
        v0 = 0x8003;
        v0 = v0 | v1;
        pcpyld(v0, a1, v0);
        sq(v0, a2, 16);
        v1 = 20;
        ld(a1, gp, -17072);  // 0x7CEA40
        v0 = 8;
        pcpyld(a0, a0, a1);
        sq(a0, a2, 32);
        ld(a0, gp, -17040);  // 0x7CEA60
        pcpyld(v1, v1, a0);
        sq(v1, a2, 48);
        ld(v1, gp, -17048);  // 0x7CEA58
        pcpyld(v0, v0, v1);
        sq(v0, a2, 64);
        lw(v0, gp, -17148);  // 0x7CE9F4
        t3 = addiu(v0, 80);
        sw(t3, gp, -17148);  // 0x7CE9F4
    }
    // 0x0046dc48
    charge(ctx, 16);
    lbu(v0, s4, 40);
    v1 = v0 & 0x20;
    v0 = v0 & 0x18;
    v1 = sra(v1, 5);
    v0 = sra(v0, 2);
    v0 = v1 | v0;
    sb(v0, s4, 43);
    lw(v1, s4, 4);
    lbu(a0, s4, 43);
    lw(v0, gp, -16888);  // 0x7CEAF8
    lw(v1, v1, 24);
    a0 = sll(a0, 2);
    v1 = addu(v1, a0);
    lw(a0, v1, 0);
    pass.program = a0.u();
    pass.uploaded = v0 != a0;
    if (v0 != a0) {
        // 0x0046dc88
        charge(ctx, 13);
        v0 = dsll32(a0, 0);
        a1 = 0;
        v0 = dsrl32(v0, 0);
        v1 = dsll32(v0, 0);
        v0 = 0x50000000;
        v1 = v1 | v0;
        lw(v0, gp, -17148);  // 0x7CE9F4
        pcpyld(v1, a1, v1);
        sq(v1, v0, 0);
        lw(v0, gp, -17148);  // 0x7CE9F4
        sw(a0, gp, -16888);  // 0x7CEAF8
        t3 = addiu(v0, 16);
        sw(t3, gp, -17148);  // 0x7CE9F4
    }
    // 0x0046dcbc
    charge(ctx, 21);
    lw(a2, s4, 48);
    t0 = 0x2000000;
    lw(a0, s4, 4);
    a3 = 0x3000000;
    lw(v1, gp, -17148);  // 0x7CE9F4
    a1 = 0x50000000;
    v0 = 0x10000;
    lw(a2, a2, 0);
    lw(t1, a0, 20);
    a0 = addiu(a2, 24);
    t0 = t1 | t0;
    lwu(a2, a2, 32);
    t0 = dsll32(t0, 0);
    a3 = t0 | a3;
    a2 = dsll32(a2, 0);
    a1 = a2 | a1;
    pcpyld(a1, a3, a1);
    sq(a1, v1, 0);
    lw(v1, gp, -17148);  // 0x7CE9F4
    t3 = addiu(v1, 16);
    sw(t3, gp, -17148);  // 0x7CE9F4
    pass.res_entry = a2.u();
    pass.vif_offset = t1.u();
    for (;;) {
        // 0x0046dd10
        charge(ctx, 7);
        di(ctx);
        sync(ctx, 16);
        mfc0(v1, 12);
        v1 = v1 & v0;
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0046dd2c
    charge(ctx, 11);
    lw(v0, a0, 0);
    v0 = addiu(v0, 1);
    sw(v0, a0, 0);
    ei(ctx);
    v0 = 1;
    lw(v1, a0, 4);
    v1 = addiu(v1, 1);
    sw(v1, a0, 4);
    lw(v1, a0, 4);
    if (v1 == v0) {
        // 0x0046dd58
        charge(ctx, 2);
        jal(ctx, 0x46DD58u, gen::fn__rwDMAAddPURef_004d51c0);
    }
    // 0x0046dd60
    charge(ctx, 37);
    a0 = 0;
    a1 = 5;
    jal(ctx, 0x46DD64u, gen::fn__rwDMAOpenVIFPkt_004d59d0);
    v0 = 0x50000000;
    v1 = 0;
    v0 = v0 | 0x4;
    a2 = 0;
    ppacw(t0, v0, v1);
    lw(a3, gp, -17148);  // 0x7CE9F4
    closing_at = a3.u();  // the closing packet
    v0 = 0x10000000;
    a0 = 14;
    a1 = v0 | 0x4;
    v1 = dsll32(v0, 0);
    ppacw(v0, a2, a1);
    ppacw(v0, t0, v0);
    sq(v0, a3, 0);
    a2 = 66;
    v0 = 0x8003;
    a1 = 71;
    v0 = v0 | v1;
    pcpyld(v0, a0, v0);
    sq(v0, a3, 16);
    a0 = 61;
    ld(v1, gp, -17032);  // 0x7CEA68
    v0 = 1;
    pcpyld(v1, a2, v1);
    sq(v1, a3, 32);
    ld(v1, gp, -17072);  // 0x7CEA40
    pcpyld(v1, a1, v1);
    sq(v1, a3, 48);
    ld(v1, gp, -17056);  // 0x7CEA50
    pcpyld(v1, a0, v1);
    sq(v1, a3, 64);
    lw(v1, gp, -17148);  // 0x7CE9F4
    t3 = addiu(v1, 80);
    sw(t3, gp, -17148);  // 0x7CE9F4
    report_mesh(ctx, s4.u(), pass);
    report_effect(ctx, Effect::BumpEnvMap, s4.u(), rd32(ctx, matfx_ext(ctx, s4.u()) + 68), extra_at, 29, closing_at, 5);
    // 0x0046e138
    charge(ctx, 12);
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
    sp = addiu(sp, 0x140);
}

// 0x0046E170 matfxBridgeDual -- 2312 bytes; frame 0xB0: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// matfxBridgeDual [MatFX dual-texture bridge] ($a0 = PipeData). Effect slot 0: +0 the second texture, +40 ALPHA_2 data,
// +48 FOGCOL data (0x01000000: the driver's FOGCOL shadow gp-17056), +56 TEST_2 bits. Frame 176: s0..s7, $ra at
// +128; the second texture's TEX1 at sp+168 and TEX0 halves at sp+152 / sp+156, the base texture's TEX0 at sp+160 /
// sp+164. s4 = PipeData, s0 = the base texture (material +0), s3 = the second texture, s1 = FOGCOL, s5 = ALPHA_2,
// s6 = TEST_2 (= TEST_1 & 0x70000 | slot +56), s7 = ZBUF_1, s2 = the second texture's CLAMP_2 bits.
//   1. Placement: sub_4F0F30 for both rasters; the raster-alpha flag is set unless the base raster's format nibble
//      is 6; RpSkyTexCacheAccessRaster(second, 1) then (base, 0), and again for each whose extension has no cache
//      slot (ext +88) yet.
//   2. Base texture: TME on, the last raster, its TEX0 halves (sub_4F1E20) and TEX1 (sub_4F1E40 into the TEX1_1
//      shadow), CLAMP_1 from the address modes; none: TME off, last raster 0. ATE is forced on. Second texture: its
//      TEX0 / TEX1 into the frame and its CLAMP bits. Both rasters narrower than 2^9 (raster +20 < 9): the last
//      raster becomes -1 (the next bridge re-sends TEX0).
//   3. _rwDMAOpenVIFPkt(0, 36): DMA cnt 30. STCYCL 1,1 / UNPACK V4-32 x7 to VU1 0x3BC: the second pass's vertex
//      GIF tag (PRE, PRIM = 0x258 | prim | FGE from trans-type bit 0: Gouraud, textured, blended, context 2; NREG
//      3, REGS ST / RGBAQ / XYZF2) and two A+D blocks for the kicks (TEX0_1 = the base raster's with FOGCOL = the
//      driver's; TEX0_2 = the second raster's with FOGCOL = the effect's); then DIRECT 6: A+D ALPHA_2 / CLAMP_2 /
//      TEST_2 / TEX1_2 / ZBUF_2; then the stock packet with the base texture.
//   4. After the resEntry's reference: _rwDMAOpenVIFPkt(0, 3), DIRECT 2: FOGCOL restored from the shadow.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: callee frames ($sp off / deeper stack)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void matfxBridgeDual(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::di, hg::dsll, hg::dsll32,
          hg::dsra32, hg::dsrl32, hg::ei, hg::enter, hg::jal, hg::lbu, hg::ld, hg::link, hg::lq, hg::lui, hg::lw,
          hg::lwc1, hg::lwu, hg::mfc0, hg::mtc1, hg::pcpyld, hg::ppacw, hg::sb, hg::sd, hg::si, hg::sll, hg::slti,
          hg::sltu, hg::sq, hg::sra, hg::srl, hg::sw, hg::sync;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 extra_at = 0, closing_at = 0;  // draw records (host-only): where the effect's packets went
    Pass pass;
    Fpr f12{ctx, 12};
    // 0x0046e170
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    v0 = 0x1000000;
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, a0, 44);
    lw(v1, gp, -17848);  // 0x7CE738
    lw(a0, a0, 8);
    v1 = addu(a0, v1);
    lw(s0, a0, 0);
    lw(v1, v1, 0);
    ld(s1, v1, 48);
    lw(s3, v1, 0);
    ld(s5, v1, 40);
    s2 = 0;
    if (s1 == v0) {
        // 0x0046e1cc
        charge(ctx, 1);
        ld(s1, gp, -17056);  // 0x7CEA50
    }
    // 0x0046e1d0
    charge(ctx, 11);
    ld(v0, v1, 56);
    ld(a0, gp, -17072);  // 0x7CEA40
    ld(s7, gp, -17088);  // 0x7CEA30
    v1 = 0x70000;
    sd(zero, sp, 0xA8);
    v1 = a0 & v1;
    sd(zero, sp, 0xA0);
    s6 = v1 | v0;
    sd(zero, sp, 0x98);
    sw(zero, gp, -16952);  // 0x7CEAB8
    if (s0 != 0) {
        // 0x0046e1fc
        charge(ctx, 8);
        link(ctx, 0x46E1FCu);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 0);
        call(ctx, gen::fn_sub_4F0F30_004f0f30);
        lw(v1, s0, 0);
        v0 = 6;
        lbu(v1, v1, 35);
        v1 = v1 & 0xF;
        if (v1 != v0) {
            // 0x0046e21c
            charge(ctx, 2);
            v0 = 1;
            sw(v0, gp, -16952);  // 0x7CEAB8
        }
    }
    // 0x0046e224
    charge(ctx, 2);
    if (s3 != 0) {
        // 0x0046e22c
        charge(ctx, 5);
        link(ctx, 0x46E22Cu);  // $ra first: the delay slot below depends on it
        lw(a0, s3, 0);
        call(ctx, gen::fn_sub_4F0F30_004f0f30);
        lw(a0, s3, 0);
        a1 = 1;
        jal(ctx, 0x46E238u, gen::fn_RpSkyTexCacheAccessRaster_004f1020);
    }
    // 0x0046e240
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x0046e248
        charge(ctx, 3);
        lw(a0, s0, 0);
        a1 = 0;
        jal(ctx, 0x46E24Cu, gen::fn_RpSkyTexCacheAccessRaster_004f1020);
    }
    // 0x0046e254
    charge(ctx, 2);
    if (s3 != 0) {
        // 0x0046e25c
        charge(ctx, 6);
        lw(a0, s3, 0);
        lw(v0, gp, -16968);  // 0x7CEAA8
        v0 = addu(a0, v0);
        lw(v0, v0, 88);
        if (v0 == 0) {
            // 0x0046e274
            charge(ctx, 2);
            a1 = 1;
            jal(ctx, 0x46E274u, gen::fn_RpSkyTexCacheAccessRaster_004f1020);
        }
    }
    // 0x0046e27c
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x0046e284
        charge(ctx, 6);
        lw(a0, s0, 0);
        lw(v0, gp, -16968);  // 0x7CEAA8
        v0 = addu(a0, v0);
        lw(v0, v0, 88);
        if (v0 == 0) {
            // 0x0046e29c
            charge(ctx, 2);
            a1 = 0;
            jal(ctx, 0x46E29Cu, gen::fn_RpSkyTexCacheAccessRaster_004f1020);
        }
    }
    // 0x0046e2a4
    charge(ctx, 2);
    if (s0 == 0) {
        // 0x0046e7f0
        charge(ctx, 6);
        ld(v1, gp, -20272);  // 0x7CDDC0
        v0 = si(-17);
        sw(zero, gp, -16948);  // 0x7CEABC
        v0 = v1 & v0;
        sd(v0, gp, -20272);  // 0x7CDDC0
        backedge(ctx);
    } else {
        // 0x0046e2ac
        charge(ctx, 20);
        ld(v0, gp, -20272);  // 0x7CDDC0
        a1 = addiu(sp, 0xA4);
        v0 = v0 | 0x10;
        sd(v0, gp, -20272);  // 0x7CDDC0
        lw(v0, s0, 0);
        sw(v0, gp, -16948);  // 0x7CEABC
        lw(a0, s0, 0);
        a2 = addiu(sp, 0xA0);
        jal(ctx, 0x46E2C8u, gen::fn_sub_4F1E20_004f1e20);
        lbu(a2, s0, 80);
        lw(a0, s0, 0);
        a1 = addiu(gp, -17040);  // &0x7CEA60
        jal(ctx, 0x46E2D8u, gen::fn_sub_4F1E40_004f1e40);
        sd(zero, gp, -17048);  // 0x7CEA58
        v0 = 3;
        lw(v1, s0, 80);
        v1 = v1 & 0xF00;
        v1 = srl(v1, 8);
        if (v1 == v0) {
            // 0x0046e7e0
            charge(ctx, 4);
            ld(v0, gp, -17048);  // 0x7CEA58
            v0 = v0 | 0x1;
            sd(v0, gp, -17048);  // 0x7CEA58
            backedge(ctx);
        }
        // 0x0046e2fc
        charge(ctx, 6);
        lw(v1, s0, 80);
        v0 = 3;
        v1 = v1 & 0xF000;
        v1 = srl(v1, 12);
        if (v1 == v0) {
            // 0x0046e314
            charge(ctx, 3);
            ld(v0, gp, -17048);  // 0x7CEA58
            v0 = v0 | 0x4;
            sd(v0, gp, -17048);  // 0x7CEA58
        }
    }
    // 0x0046e320
    charge(ctx, 4);
    ld(v0, gp, -17072);  // 0x7CEA40
    v0 = v0 | 0x1;
    sd(v0, gp, -17072);  // 0x7CEA40
    if (s3 != 0) {
        // 0x0046e330
        charge(ctx, 14);
        lw(a0, s3, 0);
        a1 = addiu(sp, 0x9C);
        a2 = addiu(sp, 0x98);
        jal(ctx, 0x46E338u, gen::fn_sub_4F1E20_004f1e20);
        lbu(a2, s3, 80);
        lw(a0, s3, 0);
        a1 = addiu(sp, 0xA8);
        jal(ctx, 0x46E348u, gen::fn_sub_4F1E40_004f1e40);
        lw(a0, s3, 80);
        v0 = 3;
        v1 = a0 & 0xF00;
        v1 = srl(v1, 8);
        s2 = 0;
        if (v1 == v0) {
            // 0x0046e368
            charge(ctx, 1);
            s2 = s2 | 0x1;
        }
        // 0x0046e36c
        charge(ctx, 5);
        v1 = a0 & 0xF000;
        v0 = 3;
        v1 = srl(v1, 12);
        if (v1 == v0) {
            // 0x0046e380
            charge(ctx, 1);
            s2 = s2 | 0x4;
        }
    }
    // 0x0046e384
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x0046e38c
        charge(ctx, 5);
        lw(v0, s0, 0);
        lw(v0, v0, 20);
        at = slti(v0, 9);
        if (at != 0) {
            // 0x0046e3a0
            charge(ctx, 2);
            if (s3 != 0) {
                // 0x0046e3a8
                charge(ctx, 5);
                lw(v0, s3, 0);
                lw(v0, v0, 20);
                at = slti(v0, 9);
                if (at != 0) {
                    // 0x0046e3bc
                    charge(ctx, 3);
                    v0 = si(-1);
                    sw(v0, gp, -16948);  // 0x7CEABC
                }
            }
        }
    }
    // 0x0046e808
    charge(ctx, 104);
    a0 = 0;
    a1 = 36;
    jal(ctx, 0x46E80Cu, gen::fn__rwDMAOpenVIFPkt_004d59d0);
    v0 = 0x10000000;
    a0 = 0;
    v1 = v0 | 0x1E;
    t6 = dsll32(v0, 0);
    pcpyld(a3, a0, v1);
    lw(a1, gp, -17148);  // 0x7CE9F4
    extra_at = a1.u();  // the effect's extra quadwords start here
    v1 = 0x6C070000;
    v0 = 0x1000000;
    a0 = v1 | 0x3BC;
    t0 = v0 | 0x404;  // &0x1000404
    v1 = v0 | 0x101;  // &0x1000101
    t7 = 14;
    ppacw(a2, a0, v1);
    sq(a3, a1, 0);
    a0 = 0;
    v0 = 0;
    ppacw(a0, a0, v0);
    lw(v1, gp, -17148);  // 0x7CE9F4
    ppacw(a2, a2, a0);
    a1 = addiu(v1, 16);
    t4 = 61;
    sw(a1, gp, -17148);  // 0x7CE9F4
    a3 = addiu(a1, 240);
    sq(a2, v1, 16);
    a1 = 0x30000000;
    lbu(t2, s4, 40);
    s0 = a1 | 0x4000;
    a1 = 0x8002;
    s3 = 0;
    a1 = a1 | t6;
    lbu(t1, s4, 41);
    pcpyld(a2, t7, a1);
    pcpyld(a1, t4, s1);
    v0 = 1042;
    t5 = 6;
    t2 = t2 & 0x1;
    t3 = 7;
    s1 = dsll32(t2, 0);
    t2 = 0x50000000;
    s1 = dsra32(s1, 0);
    t2 = t2 | 0x6;
    s1 = dsll(s1, 5);
    ppacw(t2, t2, s3);
    s1 = s1 | 0x258;
    s1 = s1 | t1;
    ppacw(a0, t2, a0);
    t1 = 0x8005;
    t2 = t1 | t6;
    t1 = dsll(s1, 15);
    t6 = t1 | s0;
    s1 = 0x6C010000;
    pcpyld(s0, t7, t2);
    t1 = 67;
    t2 = dsll32(t6, 0);
    pcpyld(t7, t1, s5);
    pcpyld(v0, v0, t2);
    sq(v0, v1, 32);
    t1 = 9;
    pcpyld(t6, t1, s2);
    sq(a2, v1, 48);
    ld(s2, sp, 0xA0);
    s1 = s1 | 0x3FA;
    s1 = dsll32(s1, 0);
    v0 = 72;
    t0 = t0 | s1;
    t1 = 79;
    pcpyld(t2, v0, s6);
    v0 = 21;
    pcpyld(t1, t1, s7);
    pcpyld(t5, t5, s2);
    sq(t5, v1, 64);
    pcpyld(t5, t0, s3);
    ld(t0, gp, -17056);  // 0x7CEA50
    pcpyld(t0, t4, t0);
    sq(t0, v1, 80);
    sq(a2, v1, 96);
    ld(a2, sp, 0x98);
    pcpyld(a2, t3, a2);
    sq(a2, v1, 112);
    sq(a1, v1, 128);
    sq(a0, v1, 144);
    sq(s0, v1, 160);
    sq(t7, v1, 176);
    sq(t6, v1, 192);
    sq(t2, v1, 208);
    ld(a0, sp, 0xA8);
    pcpyld(v0, v0, a0);
    sq(v0, v1, 224);
    sq(t1, v1, 240);
    sw(a3, gp, -17148);  // 0x7CE9F4
    sq(t5, v1, 256);
    lw(v1, gp, -17148);  // 0x7CE9F4
    lw(v0, gp, -16952);  // 0x7CEAB8
    a3 = addiu(v1, 16);
    sw(a3, gp, -17148);  // 0x7CE9F4
    lbu(v1, s4, 71);
    v1 = v1 ^ 0xFF;
    v1 = sltu(0, v1);
    v0 = v1 | v0;
    sw(v1, gp, -16956);  // 0x7CEAB4
    if (v0 == 0) {
        backedge(ctx);
        // 0x0046e3d4
        charge(ctx, 4);
        ld(v1, gp, -20272);  // 0x7CDDC0
        v0 = si(-65);
        v0 = v1 & v0;
        sd(v0, gp, -20272);  // 0x7CDDC0
    } else {
        // 0x0046e9a8
        charge(ctx, 2);
        ld(v0, gp, -20272);  // 0x7CDDC0
        backedge(ctx);
        // 0x0046e3c8
        charge(ctx, 3);
        v0 = v0 | 0x40;
        sd(v0, gp, -20272);  // 0x7CDDC0
    }
    // 0x0046e3e4
    charge(ctx, 43);
    v0 = 0x960000;
    a1 = dsll32(a3, 0);
    ld(a0, v0, 22688);  // 0x9658A0
    v1 = lui(0xFC00);
    lbu(t0, s4, 41);
    a1 = dsra32(a1, 0);
    ld(t1, gp, -20272);  // 0x7CDDC0
    v0 = v1 | 0x7FFF;
    v1 = dsll32(v0, 0);
    a3 = dsll32(t0, 0);
    v0 = 0xFFFF;
    a3 = dsra32(a3, 0);
    v0 = dsll(v0, 16);
    a3 = t1 | a3;
    v0 = v0 | 0xFFFF;
    t0 = 0;
    v1 = v0 | v1;
    pcpyld(v1, zero, v1);
    t2 = a0 & v1;
    v0 = 0x960000;
    v1 = 0x6C010000;
    ld(a2, v0, 22696);  // 0x9658A8
    a0 = v1 | 0x3FB;
    v1 = 0x1000000;
    a0 = dsll32(a0, 0);
    v1 = v1 | 0x404;  // &0x1000404
    a0 = v1 | a0;
    v1 = dsll32(a3, 0);
    v1 = dsra32(v1, 0);
    v0 = 0x960000;
    a3 = v1 & 0x7FF;
    a3 = dsll32(a3, 15);
    v1 = t1 & 0x10;
    a3 = t2 | a3;
    pcpyld(a2, a2, a3);
    sq(a2, v0, 22688);  // 0x9658A0
    pcpyld(a0, a0, t0);
    sq(a2, a1, 0);
    sq(a0, a1, 16);
    lw(v0, gp, -17148);  // 0x7CE9F4
    a3 = addiu(v0, 32);
    sw(a3, gp, -17148);  // 0x7CE9F4
    if (v1 == 0) {
        // 0x0046e4a4
        charge(ctx, 4);
        v0 = 0x3B800000;
        v0 = v0 | 0x8081;
        mtc1(v0, f12);
        a0 = addiu(s4, 68);
    } else {
        // 0x0046e490
        charge(ctx, 5);
        v0 = 0x3B010000;
        v0 = v0 | 0x1B50;
        mtc1(v0, f12);
        a0 = addiu(s4, 68);
    }
    // 0x0046e4b4
    charge(ctx, 32);
    pass.colour_at = write_ptr(ctx);
    jal(ctx, 0x46E4B4u, gen::fn_sub_49CAB0_0049cab0);
    v1 = 0x6C010000;
    v0 = 0x1000000;
    v1 = v1 | 0x3FC;
    v0 = v0 | 0x404;  // &0x1000404
    v1 = dsll32(v1, 0);
    a0 = 0;
    v1 = v0 | v1;
    lw(v0, gp, -17148);  // 0x7CE9F4
    pcpyld(v1, v1, a0);
    sq(v1, v0, 0);
    lw(v0, gp, -17148);  // 0x7CE9F4
    a3 = addiu(v0, 16);
    sw(a3, gp, -17148);  // 0x7CE9F4
    lwc1(f12, s4, 28);
    pass.surface_at = write_ptr(ctx);
    link(ctx, 0x46E4F4u);  // $ra first: the delay slot below depends on it
    lw(a0, s4, 60);
    call(ctx, gen::fn_sub_49CBD0_0049cbd0);
    v0 = 0x6C030000;
    lbu(a0, s4, 40);
    v1 = v0 | 0x3FD;
    v0 = 0x1000000;
    v1 = dsll32(v1, 0);
    v0 = v0 | 0x404;  // &0x1000404
    v0 = v0 | v1;
    v1 = 0;
    pcpyld(a1, v0, v1);
    lw(v1, gp, -17148);  // 0x7CE9F4
    sq(a1, v1, 0);
    lw(v1, gp, -16876);  // 0x7CEB04
    v0 = a0 & 0x7;
    if (v1 != 0) {
        // 0x0046e534
        charge(ctx, 3);
        v1 = v0 & 0x4;
        if (v1 != 0) {
            goto L_0046e540;
        }
    L_0046e558:
        charge(ctx, 11);
        a0 = 0x960000;
        lw(a1, gp, -17148);  // 0x7CE9F4
        lq(a0, a0, 22832);  // 0x965930
        v1 = 0x960000;
        v0 = v0 | 0x8;
        sq(a0, a1, 16);
        lq(v1, v1, 22848);  // 0x965940
        sq(v1, a1, 32);
        lw(v1, gp, -17148);  // 0x7CE9F4
        a3 = addiu(v1, 48);
        sw(a3, gp, -17148);  // 0x7CE9F4
        goto L_0046e584;
    }
L_0046e540:
    charge(ctx, 3);
    lw(v1, gp, -20232);  // 0x7CDDE8
    if (v1 != 0) {
        // 0x0046e54c
        charge(ctx, 3);
        v1 = v0 & 0x4;
        if (v1 == 0) {
            goto L_0046e9b0;
        }
        goto L_0046e558;
    }
L_0046e9b0:
    charge(ctx, 11);
    v1 = 0x960000;
    lw(a1, gp, -17148);  // 0x7CE9F4
    lq(a0, v1, 22800);  // 0x965910
    v1 = 0x960000;
    sq(a0, a1, 16);
    lq(v1, v1, 22816);  // 0x965920
    sq(v1, a1, 32);
    lw(v1, gp, -17148);  // 0x7CE9F4
    a3 = addiu(v1, 48);
    sw(a3, gp, -17148);  // 0x7CE9F4
    backedge(ctx);
L_0046e584:
    charge(ctx, 5);
    lw(a1, gp, -16964);  // 0x7CEAAC
    a0 = 3;
    sw(zero, gp, -16884);  // 0x7CEAFC
    v1 = 0;
    if (a1 == a0) {
        // 0x0046e9dc
        charge(ctx, 3);
        v1 = 32;
        sw(v1, gp, -16884);  // 0x7CEAFC
        backedge(ctx);
    }
    // 0x0046e598
    charge(ctx, 17);
    lwu(a1, gp, -16880);  // 0x7CEB00
    a0 = dsll32(v1, 0);
    v1 = dsll32(v0, 0);
    a0 = dsrl32(a0, 0);
    v0 = dsll32(a3, 0);
    v1 = dsrl32(v1, 0);
    v0 = dsra32(v0, 0);
    a1 = dsll32(a1, 0);
    a0 = a1 | a0;
    pcpyld(v1, a0, v1);
    sq(v1, v0, 0);
    lw(v0, gp, -17148);  // 0x7CE9F4
    a3 = addiu(v0, 16);
    sw(a3, gp, -17148);  // 0x7CE9F4
    lw(v0, s4, 64);
    if (v0 == 0) {
        // 0x0046e9e8
        charge(ctx, 25);
        a1 = dsll32(a3, 0);
        v0 = 0x50000000;
        a1 = dsra32(a1, 0);
        v0 = v0 | 0x2;
        sq(zero, a1, 0);
        v0 = dsll32(v0, 0);
        v1 = 0;
        sq(zero, a1, 16);
        pcpyld(v0, v0, v1);
        sq(v0, a1, 32);
        a0 = 14;
        v0 = 0x10000000;
        v1 = dsll32(v0, 0);
        v0 = 0x8001;
        v1 = v0 | v1;
        pcpyld(v1, a0, v1);
        sq(v1, a1, 48);
        v0 = 71;
        ld(v1, gp, -17072);  // 0x7CEA40
        pcpyld(v0, v0, v1);
        sq(v0, a1, 64);
        lw(v0, gp, -17148);  // 0x7CE9F4
        a3 = addiu(v0, 80);
        sw(a3, gp, -17148);  // 0x7CE9F4
        backedge(ctx);
    } else {
        // 0x0046e5dc
        charge(ctx, 30);
        v0 = 0x50000000;
        a2 = dsll32(a3, 0);
        v0 = v0 | 0x4;
        v1 = 0;
        v0 = dsll32(v0, 0);
        a2 = dsra32(a2, 0);
        pcpyld(v0, v0, v1);
        sq(v0, a2, 0);
        a1 = 14;
        v0 = 0x10000000;
        a0 = 71;
        v1 = dsll32(v0, 0);
        v0 = 0x8003;
        v0 = v0 | v1;
        pcpyld(v0, a1, v0);
        sq(v0, a2, 16);
        v1 = 20;
        ld(a1, gp, -17072);  // 0x7CEA40
        v0 = 8;
        pcpyld(a0, a0, a1);
        sq(a0, a2, 32);
        ld(a0, gp, -17040);  // 0x7CEA60
        pcpyld(v1, v1, a0);
        sq(v1, a2, 48);
        ld(v1, gp, -17048);  // 0x7CEA58
        pcpyld(v0, v0, v1);
        sq(v0, a2, 64);
        lw(v0, gp, -17148);  // 0x7CE9F4
        a3 = addiu(v0, 80);
        sw(a3, gp, -17148);  // 0x7CE9F4
    }
    // 0x0046e654
    charge(ctx, 16);
    lbu(v0, s4, 40);
    v1 = v0 & 0x20;
    v0 = v0 & 0x18;
    v1 = sra(v1, 5);
    v0 = sra(v0, 2);
    v0 = v1 | v0;
    sb(v0, s4, 43);
    lw(v1, s4, 4);
    lbu(a0, s4, 43);
    lw(v0, gp, -16888);  // 0x7CEAF8
    lw(v1, v1, 24);
    a0 = sll(a0, 2);
    v1 = addu(v1, a0);
    lw(a0, v1, 0);
    pass.program = a0.u();
    pass.uploaded = v0 != a0;
    if (v0 != a0) {
        // 0x0046e694
        charge(ctx, 13);
        v0 = dsll32(a0, 0);
        a1 = 0;
        v0 = dsrl32(v0, 0);
        v1 = dsll32(v0, 0);
        v0 = 0x50000000;
        v1 = v1 | v0;
        lw(v0, gp, -17148);  // 0x7CE9F4
        pcpyld(v1, a1, v1);
        sq(v1, v0, 0);
        lw(v0, gp, -17148);  // 0x7CE9F4
        sw(a0, gp, -16888);  // 0x7CEAF8
        a3 = addiu(v0, 16);
        sw(a3, gp, -17148);  // 0x7CE9F4
    }
    // 0x0046e6c8
    charge(ctx, 21);
    lw(a2, s4, 48);
    t0 = 0x2000000;
    lw(a0, s4, 4);
    a3 = 0x3000000;
    lw(v1, gp, -17148);  // 0x7CE9F4
    a1 = 0x50000000;
    v0 = 0x10000;
    lw(a2, a2, 0);
    lw(t1, a0, 20);
    a0 = addiu(a2, 24);
    t0 = t1 | t0;
    lwu(a2, a2, 32);
    t0 = dsll32(t0, 0);
    a3 = t0 | a3;
    a2 = dsll32(a2, 0);
    a1 = a2 | a1;
    pcpyld(a1, a3, a1);
    sq(a1, v1, 0);
    lw(v1, gp, -17148);  // 0x7CE9F4
    a3 = addiu(v1, 16);
    sw(a3, gp, -17148);  // 0x7CE9F4
    pass.res_entry = a2.u();
    pass.vif_offset = t1.u();
    for (;;) {
        // 0x0046e71c
        charge(ctx, 7);
        di(ctx);
        sync(ctx, 16);
        mfc0(v1, 12);
        v1 = v1 & v0;
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0046e738
    charge(ctx, 11);
    lw(v0, a0, 0);
    v0 = addiu(v0, 1);
    sw(v0, a0, 0);
    ei(ctx);
    v0 = 1;
    lw(v1, a0, 4);
    v1 = addiu(v1, 1);
    sw(v1, a0, 4);
    lw(v1, a0, 4);
    if (v1 == v0) {
        // 0x0046e764
        charge(ctx, 2);
        jal(ctx, 0x46E764u, gen::fn__rwDMAAddPURef_004d51c0);
    }
    // 0x0046e76c
    charge(ctx, 29);
    a0 = 0;
    a1 = 3;
    jal(ctx, 0x46E770u, gen::fn__rwDMAOpenVIFPkt_004d59d0);
    v0 = 0x50000000;
    v1 = 0;
    v0 = v0 | 0x2;
    a3 = 0;
    ppacw(t0, v0, v1);
    lw(a2, gp, -17148);  // 0x7CE9F4
    closing_at = a2.u();  // the closing packet
    v0 = 0x10000000;
    a1 = 14;
    a0 = v0 | 0x2;
    v1 = dsll32(v0, 0);
    ppacw(v0, a3, a0);
    ppacw(v0, t0, v0);
    sq(v0, a2, 0);
    a0 = 61;
    v0 = 0x8001;
    v0 = v0 | v1;
    pcpyld(v0, a1, v0);
    sq(v0, a2, 16);
    ld(v1, gp, -17056);  // 0x7CEA50
    v0 = 1;
    pcpyld(v1, a0, v1);
    sq(v1, a2, 32);
    lw(v1, gp, -17148);  // 0x7CE9F4
    a3 = addiu(v1, 48);
    sw(a3, gp, -17148);  // 0x7CE9F4
    report_mesh(ctx, s4.u(), pass);
    report_effect(ctx, Effect::Dual, s4.u(), rd32(ctx, matfx_ext(ctx, s4.u())), extra_at, 16, closing_at, 3);
    // 0x0046ea4c
    charge(ctx, 11);
    ld(ra, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xB0);
}

// 0x00472270 matfxBridgeUvTransform -- 1792 bytes; frame 0x90: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// matfxBridgeUvTransform [MatFX UV-transform bridge] ($a0 = PipeData): the stock bridge (RpMeshPS2AllBridgeCallBack, mesh.cpp)
// with one extra packet before the GIF tag: _rwDMAOpenVIFPkt(0, 4), then a DMA cnt 3 tag whose VIF words are STCYCL
// 4,4 / UNPACK V4-32 x3 to VU1 0x3BC, and rows 0, 1 and 3 of the effect's UV matrix (effect slot +0), the low 64
// bits of each row ({x, y}) in a quadword's low half. A missing
// matrix becomes the identity built in the frame at sp+80 (an RwMatrix: right / up / at 1.0 on the diagonal, flags
// | 0x20003). Frame 144: s0..s3, $ra at +64; s3 = PipeData, s2 = the matrix, s0 = texture, s1 = raster.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void matfxBridgeUvTransform(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::di, hg::dsll, hg::dsll32,
          hg::dsra32, hg::dsrl32, hg::ei, hg::enter, hg::jal, hg::lbu, hg::ld, hg::link, hg::lq, hg::lui, hg::lw,
          hg::lwc1, hg::lwu, hg::mfc0, hg::mtc1, hg::pcpyld, hg::sb, hg::sd, hg::si, hg::sll, hg::sltiu, hg::sltu,
          hg::sq, hg::sra, hg::srl, hg::sw, hg::sync;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 extra_at = 0;  // the draw record (host-only): where the effect's packet went
    Pass pass;
    Fpr f12{ctx, 12};
    // 0x00472270
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, 44);
    lw(v0, gp, -17848);  // 0x7CE738
    lw(v1, v1, 8);
    v0 = addu(v1, v0);
    lw(v0, v0, 0);
    lw(s2, v0, 0);
    s3 = a0;
    if (s2 == 0) {
        // 0x00472820
        charge(ctx, 20);
        v1 = 0x3F800000;
        v0 = 0x20000;
        sw(v1, sp, 0x78);
        v0 = v0 | 0x3;
        sw(v1, sp, 0x64);
        s2 = addiu(sp, 0x50);
        sw(v1, sp, 0x50);
        lw(v1, sp, 0x5C);
        sw(zero, sp, 0x60);
        sw(zero, sp, 0x58);
        sw(zero, sp, 0x54);
        sw(zero, sp, 0x74);
        sw(zero, sp, 0x70);
        v0 = v1 | v0;
        sw(zero, sp, 0x68);
        sw(zero, sp, 0x88);
        sw(zero, sp, 0x84);
        sw(zero, sp, 0x80);
        sw(v0, sp, 0x5C);
        backedge(ctx);
    }
    // 0x004722a8
    charge(ctx, 3);
    lw(v0, s3, 64);
    if (v0 != 0) {
        // 0x004722b4
        charge(ctx, 2);
        link(ctx, 0x4722B4u);  // $ra first: the delay slot below depends on it
        lw(a0, v0, 0);
        call(ctx, gen::fn_sub_4F0F30_004f0f30);
    }
    // 0x004722bc
    charge(ctx, 3);
    lw(s0, s3, 64);
    s1 = 0;
    if (s0 != 0) {
        // 0x004722c8
        charge(ctx, 1);
        lw(s1, s0, 0);
    }
    // 0x004722cc
    charge(ctx, 3);
    sw(zero, gp, -16952);  // 0x7CEAB8
    v0 = 0;
    if (s1 != 0) {
        // 0x004722d8
        charge(ctx, 11);
        lbu(v1, s1, 35);
        v0 = dsll32(v0, 0);
        v0 = dsra32(v0, 0);
        v1 = v1 & 0xF;
        a0 = v1 ^ 0x1;
        v1 = v1 ^ 0x5;
        a0 = sltiu(a0, 1);
        v1 = sltiu(v1, 1);
        v1 = a0 | v1;
        v0 = v0 | v1;
        sw(v0, gp, -16952);  // 0x7CEAB8
    }
    // 0x00472304
    charge(ctx, 3);
    lw(v0, gp, -16948);  // 0x7CEABC
    if (s1 != v0) {
        // 0x00472310
        charge(ctx, 2);
        if (s1 == 0) {
            // 0x00472870
            charge(ctx, 5);
            ld(v1, gp, -20272);  // 0x7CDDC0
            v0 = si(-17);
            v0 = v1 & v0;
            sd(v0, gp, -20272);  // 0x7CDDC0
            backedge(ctx);
        } else {
            // 0x00472318
            charge(ctx, 6);
            ld(v0, gp, -20272);  // 0x7CDDC0
            a0 = s1;
            a1 = 0;
            v0 = v0 | 0x10;
            link(ctx, 0x472328u);  // $ra first: the delay slot below depends on it
            sd(v0, gp, -20272);  // 0x7CDDC0
            call(ctx, gen::fn_RpSkyTexCacheAccessRaster_004f1020);
        }
        // 0x00472330
        charge(ctx, 2);
        sw(s1, gp, -16948);  // 0x7CEABC
        if (s0 != 0) {
            // 0x00472338
            charge(ctx, 9);
            link(ctx, 0x472338u);  // $ra first: the delay slot below depends on it
            lbu(a0, s0, 80);
            call(ctx, gen::fn_sub_49CA50_0049ca50);
            sd(zero, gp, -17048);  // 0x7CEA58
            v0 = 3;
            lw(v1, s0, 80);
            v1 = v1 & 0xF00;
            v1 = srl(v1, 8);
            if (v1 == v0) {
                // 0x00472884
                charge(ctx, 4);
                ld(v0, gp, -17048);  // 0x7CEA58
                v0 = v0 | 0x1;
                sd(v0, gp, -17048);  // 0x7CEA58
                backedge(ctx);
            }
            // 0x0047235c
            charge(ctx, 6);
            lw(v1, s0, 80);
            v0 = 3;
            v1 = v1 & 0xF000;
            v1 = srl(v1, 12);
            if (v1 == v0) {
                // 0x00472374
                charge(ctx, 4);
                ld(v0, gp, -17048);  // 0x7CEA58
                v0 = v0 | 0x4;
                sd(v0, gp, -17048);  // 0x7CEA58
            }
        }
    }
    // 0x00472894
    charge(ctx, 3);
    lw(v0, gp, -16952);  // 0x7CEAB8
    if (v0 == 0) {
        backedge(ctx);
        // 0x00472390
        charge(ctx, 4);
        ld(v1, gp, -17072);  // 0x7CEA40
        v0 = si(-2);
        v0 = v1 & v0;
        sd(v0, gp, -17072);  // 0x7CEA40
    } else {
        // 0x004728a0
        charge(ctx, 2);
        ld(v0, gp, -17072);  // 0x7CEA40
        backedge(ctx);
        // 0x00472384
        charge(ctx, 3);
        v0 = v0 | 0x1;
        sd(v0, gp, -17072);  // 0x7CEA40
    }
    // 0x004723a0
    charge(ctx, 53);
    a0 = 0;
    a1 = 4;
    jal(ctx, 0x4723A4u, gen::fn__rwDMAOpenVIFPkt_004d59d0);
    v1 = 0x6C030000;
    v0 = 0x1000000;
    a0 = v1 | 0x3BC;
    v1 = v0 | 0x404;  // &0x1000404
    a0 = dsll32(a0, 0);
    v0 = 0x10000000;
    v1 = v1 | a0;
    v0 = v0 | 0x3;
    pcpyld(v0, v1, v0);
    lw(v1, gp, -17148);  // 0x7CE9F4
    extra_at = v1.u();  // the effect's extra quadwords start here
    a0 = 0;
    sq(v0, v1, 0);
    ld(v0, s2, 0);
    pcpyld(v0, a0, v0);
    sq(v0, v1, 16);
    ld(v0, s2, 16);
    pcpyld(v0, a0, v0);
    sq(v0, v1, 32);
    ld(v0, s2, 48);
    pcpyld(v0, a0, v0);
    sq(v0, v1, 48);
    a1 = 18;
    v1 = addiu(v1, 64);
    link(ctx, 0x472408u);  // $ra first: the delay slot below depends on it
    sw(v1, gp, -17148);  // 0x7CE9F4
    call(ctx, gen::fn__rwDMAOpenVIFPkt_004d59d0);
    v0 = 0x10000000;
    v1 = 0;
    v0 = v0 | 0xF;
    pcpyld(a2, v1, v0);
    lw(a0, gp, -17148);  // 0x7CE9F4
    v1 = 0x6C010000;
    v0 = 0x1000000;
    v1 = v1 | 0x3FA;
    v0 = v0 | 0x404;  // &0x1000404
    v1 = dsll32(v1, 0);
    a1 = 0;
    v0 = v0 | v1;
    sq(a2, a0, 0);
    pcpyld(v0, v0, a1);
    sq(v0, a0, 16);
    lw(v1, gp, -17148);  // 0x7CE9F4
    lw(v0, gp, -16952);  // 0x7CEAB8
    v1 = addiu(v1, 32);
    sw(v1, gp, -17148);  // 0x7CE9F4
    lbu(a0, s3, 71);
    a0 = a0 ^ 0xFF;
    a0 = sltu(0, a0);
    v0 = a0 | v0;
    sw(a0, gp, -16956);  // 0x7CEAB4
    if (v0 == 0) {
        // 0x00472484
        charge(ctx, 4);
        ld(a0, gp, -20272);  // 0x7CDDC0
        v0 = si(-65);
        v0 = a0 & v0;
        sd(v0, gp, -20272);  // 0x7CDDC0
    } else {
        // 0x00472474
        charge(ctx, 4);
        ld(v0, gp, -20272);  // 0x7CDDC0
        v0 = v0 | 0x40;
        sd(v0, gp, -20272);  // 0x7CDDC0
    }
    // 0x00472494
    charge(ctx, 43);
    v0 = 0x960000;
    a0 = lui(0xFC00);
    ld(a3, v0, 22688);  // 0x9658A0
    ld(a1, gp, -20272);  // 0x7CDDC0
    v0 = a0 | 0x7FFF;
    lbu(a0, s3, 41);
    a2 = dsll32(v0, 0);
    v0 = 0xFFFF;
    v0 = dsll(v0, 16);
    v0 = v0 | 0xFFFF;
    a2 = v0 | a2;
    v0 = 0x960000;
    a0 = dsll32(a0, 0);
    ld(v0, v0, 22696);  // 0x9658A8
    a0 = dsra32(a0, 0);
    a0 = a1 | a0;
    a0 = dsll32(a0, 0);
    a0 = dsra32(a0, 0);
    pcpyld(a2, zero, a2);
    a0 = a0 & 0x7FF;
    a2 = a3 & a2;
    a0 = dsll32(a0, 15);
    a0 = a2 | a0;
    pcpyld(a2, v0, a0);
    v0 = 0x960000;
    a0 = dsll32(v1, 0);
    sq(a2, v0, 22688);  // 0x9658A0
    a0 = dsra32(a0, 0);
    v0 = 0x6C010000;
    sq(a2, a0, 0);
    v0 = v0 | 0x3FB;
    a2 = 0;
    v1 = dsll32(v0, 0);
    v0 = 0x1000000;
    v0 = v0 | 0x404;  // &0x1000404
    v0 = v0 | v1;
    pcpyld(v0, v0, a2);
    sq(v0, a0, 16);
    lw(v1, gp, -17148);  // 0x7CE9F4
    v0 = a1 & 0x10;
    v1 = addiu(v1, 32);
    sw(v1, gp, -17148);  // 0x7CE9F4
    if (v0 == 0) {
        // 0x00472554
        charge(ctx, 4);
        v0 = 0x3B800000;
        v0 = v0 | 0x8081;
        mtc1(v0, f12);
        a0 = addiu(s3, 68);
    } else {
        // 0x00472540
        charge(ctx, 5);
        v0 = 0x3B010000;
        v0 = v0 | 0x1B50;
        mtc1(v0, f12);
        a0 = addiu(s3, 68);
    }
    // 0x00472564
    charge(ctx, 33);
    pass.colour_at = write_ptr(ctx);
    jal(ctx, 0x472564u, gen::fn_sub_49CAB0_0049cab0);
    v1 = 0x6C010000;
    v0 = 0x1000000;
    v1 = v1 | 0x3FC;
    v0 = v0 | 0x404;  // &0x1000404
    v1 = dsll32(v1, 0);
    a0 = 0;
    v0 = v0 | v1;
    pcpyld(v1, v0, a0);
    lw(v0, gp, -17148);  // 0x7CE9F4
    sq(v1, v0, 0);
    lw(v0, gp, -17148);  // 0x7CE9F4
    v1 = addiu(v0, 16);
    sw(v1, gp, -17148);  // 0x7CE9F4
    lwc1(f12, s3, 28);
    pass.surface_at = write_ptr(ctx);
    link(ctx, 0x4725A4u);  // $ra first: the delay slot below depends on it
    lw(a0, s3, 60);
    call(ctx, gen::fn_sub_49CBD0_0049cbd0);
    lbu(a0, s3, 40);
    v0 = 0x6C030000;
    v1 = v0 | 0x3FD;
    a1 = 0;
    v0 = 0x1000000;
    v1 = dsll32(v1, 0);
    v0 = v0 | 0x404;  // &0x1000404
    v1 = v0 | v1;
    v0 = a0 & 0x7;
    pcpyld(a0, v1, a1);
    lw(v1, gp, -17148);  // 0x7CE9F4
    sq(a0, v1, 0);
    lw(v1, gp, -16876);  // 0x7CEB04
    if (v1 != 0) {
        // 0x004725e8
        charge(ctx, 3);
        v1 = v0 & 0x4;
        if (v1 != 0) {
            goto L_004725f4;
        }
    L_0047260c:
        charge(ctx, 11);
        a0 = 0x960000;
        lw(a1, gp, -17148);  // 0x7CE9F4
        lq(a0, a0, 22832);  // 0x965930
        v1 = 0x960000;
        v0 = v0 | 0x8;
        sq(a0, a1, 16);
        lq(v1, v1, 22848);  // 0x965940
        sq(v1, a1, 32);
        lw(v1, gp, -17148);  // 0x7CE9F4
        v1 = addiu(v1, 48);
        sw(v1, gp, -17148);  // 0x7CE9F4
        goto L_00472638;
    }
L_004725f4:
    charge(ctx, 3);
    lw(v1, gp, -20232);  // 0x7CDDE8
    if (v1 != 0) {
        // 0x00472600
        charge(ctx, 3);
        v1 = v0 & 0x4;
        if (v1 == 0) {
            goto L_004728a8;
        }
        goto L_0047260c;
    }
L_004728a8:
    charge(ctx, 11);
    v1 = 0x960000;
    lw(a1, gp, -17148);  // 0x7CE9F4
    lq(a0, v1, 22800);  // 0x965910
    v1 = 0x960000;
    sq(a0, a1, 16);
    lq(v1, v1, 22816);  // 0x965920
    sq(v1, a1, 32);
    lw(v1, gp, -17148);  // 0x7CE9F4
    v1 = addiu(v1, 48);
    sw(v1, gp, -17148);  // 0x7CE9F4
    backedge(ctx);
L_00472638:
    charge(ctx, 5);
    lw(a2, gp, -16964);  // 0x7CEAAC
    a1 = 3;
    sw(zero, gp, -16884);  // 0x7CEAFC
    a0 = 0;
    if (a2 == a1) {
        // 0x004728d4
        charge(ctx, 3);
        a0 = 32;
        sw(a0, gp, -16884);  // 0x7CEAFC
        backedge(ctx);
    }
    // 0x0047264c
    charge(ctx, 17);
    lwu(a1, gp, -16880);  // 0x7CEB00
    a0 = dsll32(a0, 0);
    v0 = dsll32(v0, 0);
    a0 = dsrl32(a0, 0);
    v0 = dsrl32(v0, 0);
    a1 = dsll32(a1, 0);
    a0 = a1 | a0;
    pcpyld(a0, a0, v0);
    v0 = dsll32(v1, 0);
    v0 = dsra32(v0, 0);
    sq(a0, v0, 0);
    lw(v0, gp, -17148);  // 0x7CE9F4
    v1 = addiu(v0, 16);
    sw(v1, gp, -17148);  // 0x7CE9F4
    lw(v0, s3, 64);
    if (v0 == 0) {
        // 0x004728e0
        charge(ctx, 25);
        a1 = dsll32(v1, 0);
        v0 = 0x50000000;
        a1 = dsra32(a1, 0);
        v0 = v0 | 0x2;
        sq(zero, a1, 0);
        v0 = dsll32(v0, 0);
        v1 = 0;
        sq(zero, a1, 16);
        pcpyld(v0, v0, v1);
        sq(v0, a1, 32);
        a0 = 14;
        v0 = 0x10000000;
        v1 = dsll32(v0, 0);
        v0 = 0x8001;
        v1 = v0 | v1;
        pcpyld(v1, a0, v1);
        sq(v1, a1, 48);
        v0 = 71;
        ld(v1, gp, -17072);  // 0x7CEA40
        pcpyld(v0, v0, v1);
        sq(v0, a1, 64);
        lw(v0, gp, -17148);  // 0x7CE9F4
        v1 = addiu(v0, 80);
        sw(v1, gp, -17148);  // 0x7CE9F4
        backedge(ctx);
    } else {
        // 0x00472690
        charge(ctx, 30);
        v0 = 0x50000000;
        a0 = 0;
        v0 = v0 | 0x4;
        v0 = dsll32(v0, 0);
        pcpyld(v0, v0, a0);
        a1 = dsll32(v1, 0);
        a0 = 14;
        a1 = dsra32(a1, 0);
        sq(v0, a1, 0);
        v0 = 0x10000000;
        v1 = dsll32(v0, 0);
        v0 = 0x8003;
        v0 = v0 | v1;
        pcpyld(v0, a0, v0);
        sq(v0, a1, 16);
        ld(v1, gp, -17072);  // 0x7CEA40
        v0 = 71;
        pcpyld(v0, v0, v1);
        sq(v0, a1, 32);
        ld(v1, gp, -17040);  // 0x7CEA60
        v0 = 20;
        pcpyld(v0, v0, v1);
        sq(v0, a1, 48);
        ld(v1, gp, -17048);  // 0x7CEA58
        v0 = 8;
        pcpyld(v0, v0, v1);
        sq(v0, a1, 64);
        lw(v0, gp, -17148);  // 0x7CE9F4
        v1 = addiu(v0, 80);
        sw(v1, gp, -17148);  // 0x7CE9F4
    }
    // 0x00472708
    charge(ctx, 16);
    lbu(v0, s3, 40);
    v1 = v0 & 0x20;
    v0 = v0 & 0x18;
    v1 = sra(v1, 5);
    v0 = sra(v0, 2);
    v0 = v1 | v0;
    sb(v0, s3, 43);
    lw(v1, s3, 4);
    lbu(a0, s3, 43);
    lw(v0, gp, -16888);  // 0x7CEAF8
    lw(v1, v1, 24);
    a0 = sll(a0, 2);
    v1 = addu(v1, a0);
    lw(a0, v1, 0);
    pass.program = a0.u();
    pass.uploaded = v0 != a0;
    if (v0 != a0) {
        // 0x00472748
        charge(ctx, 13);
        v0 = dsll32(a0, 0);
        a1 = 0;
        v0 = dsrl32(v0, 0);
        v1 = dsll32(v0, 0);
        v0 = 0x50000000;
        v0 = v1 | v0;
        pcpyld(v1, a1, v0);
        lw(v0, gp, -17148);  // 0x7CE9F4
        sq(v1, v0, 0);
        lw(v0, gp, -17148);  // 0x7CE9F4
        sw(a0, gp, -16888);  // 0x7CEAF8
        v1 = addiu(v0, 16);
        sw(v1, gp, -17148);  // 0x7CE9F4
    }
    // 0x0047277c
    charge(ctx, 21);
    lw(a0, s3, 48);
    a2 = 0x2000000;
    lw(v1, s3, 4);
    a1 = 0x3000000;
    v0 = 0x50000000;
    lw(t0, a0, 0);
    lw(a3, v1, 20);
    a0 = addiu(t0, 24);
    lwu(v1, t0, 32);
    a2 = a3 | a2;
    a2 = dsll32(a2, 0);
    a1 = a2 | a1;
    v1 = dsll32(v1, 0);
    v0 = v1 | v0;
    pcpyld(a1, a1, v0);
    lw(v1, gp, -17148);  // 0x7CE9F4
    v0 = 0x10000;
    sq(a1, v1, 0);
    lw(v1, gp, -17148);  // 0x7CE9F4
    v1 = addiu(v1, 16);
    sw(v1, gp, -17148);  // 0x7CE9F4
    pass.res_entry = t0.u();
    pass.vif_offset = a3.u();
    for (;;) {
        // 0x004727d0
        charge(ctx, 7);
        di(ctx);
        sync(ctx, 16);
        mfc0(v1, 12);
        v1 = v1 & v0;
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004727ec
    charge(ctx, 11);
    lw(v0, a0, 0);
    v0 = addiu(v0, 1);
    sw(v0, a0, 0);
    ei(ctx);
    v0 = 1;
    lw(v1, a0, 4);
    v1 = addiu(v1, 1);
    sw(v1, a0, 4);
    lw(v1, a0, 4);
    if (v1 == v0) {
        // 0x00472944
        charge(ctx, 4);
        jal(ctx, 0x472944u, gen::fn__rwDMAAddPURef_004d51c0);
        backedge(ctx);
    }
    // 0x00472818
    charge(ctx, 2);
    v0 = 1;
    report_mesh(ctx, s3.u(), pass);
    report_effect(ctx, Effect::UvTransform, s3.u(), 0, extra_at, 4, 0, 0);
    // 0x00472954
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x00472970 matfxBridgeDualUvTransform -- 2508 bytes; frame 0x110: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// matfxBridgeDualUvTransform [MatFX dual-texture + UV-transform bridge] ($a0 = PipeData). Effect slot 0 (UV transform): +0 / +4 the
// two UV matrices; slot 1 (dual): +64 the second texture, +104 ALPHA_2, +112 FOGCOL (0x01000000: the driver's),
// +120 TEST_2 bits. Frame 272: s0..s8, $ra at +144; ZBUF_1 kept as a quadword at sp+160, the identity matrix at
// sp+176 for a missing UV matrix (either or both point there), the second texture's TEX0 halves at sp+248 / sp+252
// and TEX1 at sp+264, the base texture's TEX0 at sp+256 / sp+260. s4 = PipeData, s0 = the base texture, s3 = the
// second texture, s2 / s1 = the UV matrices, s6 = FOGCOL, s7 = ALPHA_2, s8 = TEST_2, s5 = CLAMP_2 bits.
// The texture placement and GS state are dual_bridge's; the register block (_rwDMAOpenVIFPkt(0, 39), DMA cnt 33)
// is STCYCL 1,1 / UNPACK V4-32 x10 to VU1 0x3BC: the vertex GIF tag of the second pass, the two A+D kick blocks,
// and three quadwords pairing the rows 0, 1, 3 of the two UV matrices ({x, y} of the first in the low half, of the
// second in the high half); then DIRECT 6 (ALPHA_2 / CLAMP_2 / TEST_2 / TEX1_2 / ZBUF_2) and the stock packet.
// The closing packet restores FOGCOL.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void matfxBridgeDualUvTransform(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::di, hg::dsll, hg::dsll32,
          hg::dsra32, hg::dsrl32, hg::ei, hg::enter, hg::jal, hg::lbu, hg::ld, hg::link, hg::lq, hg::lui, hg::lw,
          hg::lwc1, hg::lwu, hg::mfc0, hg::mtc1, hg::pcpyld, hg::ppacw, hg::sb, hg::sd, hg::si, hg::sll, hg::slti,
          hg::sltu, hg::sq, hg::sra, hg::srl, hg::sw, hg::sync;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    u32 extra_at = 0, closing_at = 0;  // draw records (host-only): where the effect's packets went
    Pass pass;
    Fpr f12{ctx, 12};
    // 0x00472970
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x110);
    v0 = 0x1000000;
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, a0, 44);
    lw(v1, gp, -17848);  // 0x7CE738
    lw(a0, a0, 8);
    v1 = addu(a0, v1);
    lw(s0, a0, 0);
    lw(a2, v1, 0);
    ld(s6, a2, 112);
    lw(s3, a2, 64);
    ld(s7, a2, 104);
    s5 = 0;
    if (s6 == v0) {
        // 0x004729d0
        charge(ctx, 1);
        ld(s6, gp, -17056);  // 0x7CEA50
    }
    // 0x004729d4
    charge(ctx, 11);
    ld(v1, a2, 120);
    a0 = 0x70000;
    ld(v0, gp, -17088);  // 0x7CEA30
    ld(a1, gp, -17072);  // 0x7CEA40
    sd(zero, sp, 0x108);
    lw(s2, a2, 0);
    lw(s1, a2, 4);
    sq(v0, sp, 0xA0);
    v0 = a1 & a0;
    fp = v0 | v1;
    if (s2 != 0) {
        // 0x00472a00
        charge(ctx, 2);
        if (s1 == 0) {
            goto L_00472ffc;
        }
        goto L_00472a08;
    }
L_00472ffc:
    charge(ctx, 2);
    if (s2 == 0) {
        // 0x00473058
        charge(ctx, 2);
        s2 = addiu(sp, 0xB0);
        backedge(ctx);
    }
    // 0x00473004
    charge(ctx, 2);
    if (s1 == 0) {
        // 0x00473060
        charge(ctx, 2);
        s1 = addiu(sp, 0xB0);
        backedge(ctx);
    }
    // 0x0047300c
    charge(ctx, 19);
    v1 = 0x3F800000;
    v0 = 0x20000;
    sw(v1, sp, 0xD8);
    v0 = v0 | 0x3;
    sw(v1, sp, 0xC4);
    sw(v1, sp, 0xB0);
    lw(v1, sp, 0xBC);
    sw(zero, sp, 0xC0);
    sw(zero, sp, 0xB8);
    sw(zero, sp, 0xB4);
    sw(zero, sp, 0xD4);
    sw(zero, sp, 0xD0);
    v0 = v1 | v0;
    sw(zero, sp, 0xC8);
    sw(zero, sp, 0xE8);
    sw(zero, sp, 0xE4);
    sw(zero, sp, 0xE0);
    sw(v0, sp, 0xBC);
    backedge(ctx);
L_00472a08:
    charge(ctx, 4);
    sd(zero, sp, 0x100);
    sd(zero, sp, 0xF8);
    sw(zero, gp, -16952);  // 0x7CEAB8
    if (s0 != 0) {
        // 0x00472a18
        charge(ctx, 8);
        link(ctx, 0x472A18u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 0);
        call(ctx, gen::fn_sub_4F0F30_004f0f30);
        lw(v1, s0, 0);
        v0 = 6;
        lbu(v1, v1, 35);
        v1 = v1 & 0xF;
        if (v1 != v0) {
            // 0x00472a38
            charge(ctx, 2);
            v0 = 1;
            sw(v0, gp, -16952);  // 0x7CEAB8
        }
    }
    // 0x00472a40
    charge(ctx, 2);
    if (s3 != 0) {
        // 0x00472a48
        charge(ctx, 5);
        link(ctx, 0x472A48u);  // $ra first: the delay slot below depends on it
        lw(a0, s3, 0);
        call(ctx, gen::fn_sub_4F0F30_004f0f30);
        lw(a0, s3, 0);
        a1 = 1;
        jal(ctx, 0x472A54u, gen::fn_RpSkyTexCacheAccessRaster_004f1020);
    }
    // 0x00472a5c
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x00472a64
        charge(ctx, 3);
        lw(a0, s0, 0);
        a1 = 0;
        jal(ctx, 0x472A68u, gen::fn_RpSkyTexCacheAccessRaster_004f1020);
    }
    // 0x00472a70
    charge(ctx, 2);
    if (s3 != 0) {
        // 0x00472a78
        charge(ctx, 6);
        lw(a0, s3, 0);
        lw(v0, gp, -16968);  // 0x7CEAA8
        v0 = addu(a0, v0);
        lw(v0, v0, 88);
        if (v0 == 0) {
            // 0x00472a90
            charge(ctx, 2);
            a1 = 1;
            jal(ctx, 0x472A90u, gen::fn_RpSkyTexCacheAccessRaster_004f1020);
        }
    }
    // 0x00472a98
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x00472aa0
        charge(ctx, 6);
        lw(a0, s0, 0);
        lw(v0, gp, -16968);  // 0x7CEAA8
        v0 = addu(a0, v0);
        lw(v0, v0, 88);
        if (v0 == 0) {
            // 0x00472ab8
            charge(ctx, 2);
            a1 = 0;
            jal(ctx, 0x472AB8u, gen::fn_RpSkyTexCacheAccessRaster_004f1020);
        }
    }
    // 0x00472ac0
    charge(ctx, 2);
    if (s0 == 0) {
        // 0x00473078
        charge(ctx, 6);
        ld(v1, gp, -20272);  // 0x7CDDC0
        v0 = si(-17);
        sw(zero, gp, -16948);  // 0x7CEABC
        v0 = v1 & v0;
        sd(v0, gp, -20272);  // 0x7CDDC0
        backedge(ctx);
    } else {
        // 0x00472ac8
        charge(ctx, 20);
        ld(v0, gp, -20272);  // 0x7CDDC0
        a1 = addiu(sp, 0x104);
        v0 = v0 | 0x10;
        sd(v0, gp, -20272);  // 0x7CDDC0
        lw(v0, s0, 0);
        sw(v0, gp, -16948);  // 0x7CEABC
        lw(a0, s0, 0);
        a2 = addiu(sp, 0x100);
        jal(ctx, 0x472AE4u, gen::fn_sub_4F1E20_004f1e20);
        lbu(a2, s0, 80);
        lw(a0, s0, 0);
        a1 = addiu(gp, -17040);  // &0x7CEA60
        jal(ctx, 0x472AF4u, gen::fn_sub_4F1E40_004f1e40);
        sd(zero, gp, -17048);  // 0x7CEA58
        v0 = 3;
        lw(v1, s0, 80);
        v1 = v1 & 0xF00;
        v1 = srl(v1, 8);
        if (v1 == v0) {
            // 0x00473068
            charge(ctx, 4);
            ld(v0, gp, -17048);  // 0x7CEA58
            v0 = v0 | 0x1;
            sd(v0, gp, -17048);  // 0x7CEA58
            backedge(ctx);
        }
        // 0x00472b18
        charge(ctx, 6);
        lw(v1, s0, 80);
        v0 = 3;
        v1 = v1 & 0xF000;
        v1 = srl(v1, 12);
        if (v1 == v0) {
            // 0x00472b30
            charge(ctx, 3);
            ld(v0, gp, -17048);  // 0x7CEA58
            v0 = v0 | 0x4;
            sd(v0, gp, -17048);  // 0x7CEA58
        }
    }
    // 0x00472b3c
    charge(ctx, 4);
    ld(v0, gp, -17072);  // 0x7CEA40
    v0 = v0 | 0x1;
    sd(v0, gp, -17072);  // 0x7CEA40
    if (s3 != 0) {
        // 0x00472b4c
        charge(ctx, 14);
        lw(a0, s3, 0);
        a1 = addiu(sp, 0xFC);
        a2 = addiu(sp, 0xF8);
        jal(ctx, 0x472B54u, gen::fn_sub_4F1E20_004f1e20);
        lbu(a2, s3, 80);
        lw(a0, s3, 0);
        a1 = addiu(sp, 0x108);
        jal(ctx, 0x472B64u, gen::fn_sub_4F1E40_004f1e40);
        lw(a0, s3, 80);
        v0 = 3;
        v1 = a0 & 0xF00;
        v1 = srl(v1, 8);
        s5 = 0;
        if (v1 == v0) {
            // 0x00472b84
            charge(ctx, 1);
            s5 = s5 | 0x1;
        }
        // 0x00472b88
        charge(ctx, 5);
        v1 = a0 & 0xF000;
        v0 = 3;
        v1 = srl(v1, 12);
        if (v1 == v0) {
            // 0x00472b9c
            charge(ctx, 1);
            s5 = s5 | 0x4;
        }
    }
    // 0x00472ba0
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x00472ba8
        charge(ctx, 5);
        lw(v0, s0, 0);
        lw(v0, v0, 20);
        at = slti(v0, 9);
        if (at != 0) {
            // 0x00472bbc
            charge(ctx, 2);
            if (s3 != 0) {
                // 0x00472bc4
                charge(ctx, 5);
                lw(v0, s3, 0);
                lw(v0, v0, 20);
                at = slti(v0, 9);
                if (at != 0) {
                    // 0x00472bd8
                    charge(ctx, 3);
                    v0 = si(-1);
                    sw(v0, gp, -16948);  // 0x7CEABC
                }
            }
        }
    }
    // 0x00473090
    charge(ctx, 118);
    a0 = 0;
    a1 = 39;
    jal(ctx, 0x473094u, gen::fn__rwDMAOpenVIFPkt_004d59d0);
    v0 = 0x10000000;
    a0 = 0;
    v1 = v0 | 0x21;
    t4 = dsll32(v0, 0);
    pcpyld(a3, a0, v1);
    lw(a1, gp, -17148);  // 0x7CE9F4
    extra_at = a1.u();  // the effect's extra quadwords start here
    v1 = 0x6C0A0000;
    v0 = 0x1000000;
    a0 = v1 | 0x3BC;
    t5 = 14;
    v1 = v0 | 0x101;  // &0x1000101
    t2 = 61;
    ppacw(a2, a0, v1);
    sq(a3, a1, 0);
    a3 = v0 | 0x404;  // &0x1000404
    a0 = 0;
    v1 = 0;
    lw(v0, gp, -17148);  // 0x7CE9F4
    ppacw(a1, a0, v1);
    ppacw(a2, a2, a1);
    a0 = addiu(v0, 16);
    v1 = 0x30000000;
    sw(a0, gp, -17148);  // 0x7CE9F4
    t7 = v1 | 0x4000;
    sq(a2, v0, 16);
    v1 = 0x8002;
    lbu(t0, s4, 40);
    a2 = addiu(a0, 288);
    v1 = v1 | t4;
    lbu(s0, s4, 41);
    pcpyld(a0, t5, v1);
    pcpyld(v1, t2, s6);
    s6 = 0;
    t6 = 1042;
    t3 = 6;
    t1 = 7;
    t0 = t0 & 0x1;
    s3 = dsll32(t0, 0);
    t0 = 0x50000000;
    s3 = dsra32(s3, 0);
    t0 = t0 | 0x6;
    s3 = dsll(s3, 5);
    ppacw(t0, t0, s6);
    s3 = s3 | 0x258;
    s6 = 0x6C010000;
    s0 = s3 | s0;
    s6 = s6 | 0x3FA;
    ppacw(a1, t0, a1);
    t0 = dsll(s0, 15);
    s3 = 0x8005;
    t7 = t0 | t7;
    t4 = s3 | t4;
    t7 = dsll32(t7, 0);
    t0 = 67;
    pcpyld(t6, t6, t7);
    sq(t6, v0, 32);
    pcpyld(t4, t5, t4);
    sq(a0, v0, 48);
    t5 = 9;
    ld(t6, sp, 0x100);
    pcpyld(s5, t5, s5);
    t5 = 72;
    s6 = dsll32(s6, 0);
    pcpyld(s3, t5, fp);
    lq(t7, sp, 0xA0);
    s0 = 79;
    t5 = 21;
    pcpyld(t0, t0, s7);
    a3 = a3 | s6;
    pcpyld(t3, t3, t6);
    sq(t3, v0, 64);
    ld(t3, gp, -17056);  // 0x7CEA50
    pcpyld(s0, s0, t7);
    t7 = 0;
    pcpyld(a3, a3, t7);
    pcpyld(t2, t2, t3);
    sq(t2, v0, 80);
    sq(a0, v0, 96);
    ld(a0, sp, 0xF8);
    pcpyld(a0, t1, a0);
    sq(a0, v0, 112);
    sq(v1, v0, 128);
    ld(a0, s2, 0);
    ld(v1, s1, 0);
    pcpyld(v1, v1, a0);
    sq(v1, v0, 144);
    ld(a0, s1, 16);
    ld(v1, s2, 16);
    pcpyld(v1, a0, v1);
    sq(v1, v0, 160);
    ld(a0, s1, 48);
    ld(v1, s2, 48);
    pcpyld(v1, a0, v1);
    sq(v1, v0, 176);
    sq(a1, v0, 192);
    sq(t4, v0, 208);
    sq(t0, v0, 224);
    sq(s5, v0, 240);
    sq(s3, v0, 256);
    ld(v1, sp, 0x108);
    pcpyld(v1, t5, v1);
    sq(v1, v0, 272);
    sq(s0, v0, 288);
    sw(a2, gp, -17148);  // 0x7CE9F4
    sq(a3, v0, 304);
    lw(v1, gp, -17148);  // 0x7CE9F4
    lw(v0, gp, -16952);  // 0x7CEAB8
    a2 = addiu(v1, 16);
    sw(a2, gp, -17148);  // 0x7CE9F4
    lbu(v1, s4, 71);
    v1 = v1 ^ 0xFF;
    v1 = sltu(0, v1);
    v0 = v1 | v0;
    sw(v1, gp, -16956);  // 0x7CEAB4
    if (v0 == 0) {
        backedge(ctx);
        // 0x00472bf0
        charge(ctx, 4);
        ld(v1, gp, -20272);  // 0x7CDDC0
        v0 = si(-65);
        v0 = v1 & v0;
        sd(v0, gp, -20272);  // 0x7CDDC0
    } else {
        // 0x00473268
        charge(ctx, 2);
        ld(v0, gp, -20272);  // 0x7CDDC0
        backedge(ctx);
        // 0x00472be4
        charge(ctx, 3);
        v0 = v0 | 0x40;
        sd(v0, gp, -20272);  // 0x7CDDC0
    }
    // 0x00472c00
    charge(ctx, 43);
    v0 = 0x960000;
    a1 = dsll32(a2, 0);
    ld(a0, v0, 22688);  // 0x9658A0
    v1 = lui(0xFC00);
    lbu(t0, s4, 41);
    a1 = dsra32(a1, 0);
    ld(t1, gp, -20272);  // 0x7CDDC0
    v0 = v1 | 0x7FFF;
    v1 = dsll32(v0, 0);
    a2 = dsll32(t0, 0);
    v0 = 0xFFFF;
    a2 = dsra32(a2, 0);
    v0 = dsll(v0, 16);
    a2 = t1 | a2;
    v0 = v0 | 0xFFFF;
    t0 = 0;
    v1 = v0 | v1;
    pcpyld(v1, zero, v1);
    t2 = a0 & v1;
    v0 = 0x960000;
    v1 = 0x6C010000;
    ld(a3, v0, 22696);  // 0x9658A8
    a0 = v1 | 0x3FB;
    v1 = 0x1000000;
    a0 = dsll32(a0, 0);
    v1 = v1 | 0x404;  // &0x1000404
    a0 = v1 | a0;
    v1 = dsll32(a2, 0);
    v1 = dsra32(v1, 0);
    v0 = 0x960000;
    a2 = v1 & 0x7FF;
    a2 = dsll32(a2, 15);
    v1 = t1 & 0x10;
    a2 = t2 | a2;
    pcpyld(a2, a3, a2);
    sq(a2, v0, 22688);  // 0x9658A0
    pcpyld(a0, a0, t0);
    sq(a2, a1, 0);
    sq(a0, a1, 16);
    lw(v0, gp, -17148);  // 0x7CE9F4
    a2 = addiu(v0, 32);
    sw(a2, gp, -17148);  // 0x7CE9F4
    if (v1 == 0) {
        // 0x00472cc0
        charge(ctx, 4);
        v0 = 0x3B800000;
        v0 = v0 | 0x8081;
        mtc1(v0, f12);
        a0 = addiu(s4, 68);
    } else {
        // 0x00472cac
        charge(ctx, 5);
        v0 = 0x3B010000;
        v0 = v0 | 0x1B50;
        mtc1(v0, f12);
        a0 = addiu(s4, 68);
    }
    // 0x00472cd0
    charge(ctx, 32);
    pass.colour_at = write_ptr(ctx);
    jal(ctx, 0x472CD0u, gen::fn_sub_49CAB0_0049cab0);
    v1 = 0x6C010000;
    v0 = 0x1000000;
    v1 = v1 | 0x3FC;
    v0 = v0 | 0x404;  // &0x1000404
    v1 = dsll32(v1, 0);
    a0 = 0;
    v1 = v0 | v1;
    lw(v0, gp, -17148);  // 0x7CE9F4
    pcpyld(v1, v1, a0);
    sq(v1, v0, 0);
    lw(v0, gp, -17148);  // 0x7CE9F4
    a2 = addiu(v0, 16);
    sw(a2, gp, -17148);  // 0x7CE9F4
    lwc1(f12, s4, 28);
    pass.surface_at = write_ptr(ctx);
    link(ctx, 0x472D10u);  // $ra first: the delay slot below depends on it
    lw(a0, s4, 60);
    call(ctx, gen::fn_sub_49CBD0_0049cbd0);
    v0 = 0x6C030000;
    lbu(a0, s4, 40);
    v1 = v0 | 0x3FD;
    v0 = 0x1000000;
    v1 = dsll32(v1, 0);
    v0 = v0 | 0x404;  // &0x1000404
    v0 = v0 | v1;
    v1 = 0;
    pcpyld(a1, v0, v1);
    lw(v1, gp, -17148);  // 0x7CE9F4
    sq(a1, v1, 0);
    lw(v1, gp, -16876);  // 0x7CEB04
    v0 = a0 & 0x7;
    if (v1 != 0) {
        // 0x00472d50
        charge(ctx, 3);
        v1 = v0 & 0x4;
        if (v1 != 0) {
            goto L_00472d5c;
        }
    L_00472d74:
        charge(ctx, 11);
        a0 = 0x960000;
        lw(a1, gp, -17148);  // 0x7CE9F4
        lq(a0, a0, 22832);  // 0x965930
        v1 = 0x960000;
        v0 = v0 | 0x8;
        sq(a0, a1, 16);
        lq(v1, v1, 22848);  // 0x965940
        sq(v1, a1, 32);
        lw(v1, gp, -17148);  // 0x7CE9F4
        a2 = addiu(v1, 48);
        sw(a2, gp, -17148);  // 0x7CE9F4
        goto L_00472da0;
    }
L_00472d5c:
    charge(ctx, 3);
    lw(v1, gp, -20232);  // 0x7CDDE8
    if (v1 != 0) {
        // 0x00472d68
        charge(ctx, 3);
        v1 = v0 & 0x4;
        if (v1 == 0) {
            goto L_00473270;
        }
        goto L_00472d74;
    }
L_00473270:
    charge(ctx, 11);
    v1 = 0x960000;
    lw(a1, gp, -17148);  // 0x7CE9F4
    lq(a0, v1, 22800);  // 0x965910
    v1 = 0x960000;
    sq(a0, a1, 16);
    lq(v1, v1, 22816);  // 0x965920
    sq(v1, a1, 32);
    lw(v1, gp, -17148);  // 0x7CE9F4
    a2 = addiu(v1, 48);
    sw(a2, gp, -17148);  // 0x7CE9F4
    backedge(ctx);
L_00472da0:
    charge(ctx, 5);
    lw(a1, gp, -16964);  // 0x7CEAAC
    a0 = 3;
    sw(zero, gp, -16884);  // 0x7CEAFC
    v1 = 0;
    if (a1 == a0) {
        // 0x0047329c
        charge(ctx, 3);
        v1 = 32;
        sw(v1, gp, -16884);  // 0x7CEAFC
        backedge(ctx);
    }
    // 0x00472db4
    charge(ctx, 17);
    lwu(a1, gp, -16880);  // 0x7CEB00
    a0 = dsll32(v1, 0);
    v1 = dsll32(v0, 0);
    a0 = dsrl32(a0, 0);
    v0 = dsll32(a2, 0);
    v1 = dsrl32(v1, 0);
    v0 = dsra32(v0, 0);
    a1 = dsll32(a1, 0);
    a0 = a1 | a0;
    pcpyld(v1, a0, v1);
    sq(v1, v0, 0);
    lw(v0, gp, -17148);  // 0x7CE9F4
    a2 = addiu(v0, 16);
    sw(a2, gp, -17148);  // 0x7CE9F4
    lw(v0, s4, 64);
    if (v0 == 0) {
        // 0x004732a8
        charge(ctx, 25);
        a1 = dsll32(a2, 0);
        v0 = 0x50000000;
        a1 = dsra32(a1, 0);
        v0 = v0 | 0x2;
        sq(zero, a1, 0);
        v0 = dsll32(v0, 0);
        v1 = 0;
        sq(zero, a1, 16);
        pcpyld(v0, v0, v1);
        sq(v0, a1, 32);
        a0 = 14;
        v0 = 0x10000000;
        v1 = dsll32(v0, 0);
        v0 = 0x8001;
        v1 = v0 | v1;
        pcpyld(v1, a0, v1);
        sq(v1, a1, 48);
        v0 = 71;
        ld(v1, gp, -17072);  // 0x7CEA40
        pcpyld(v0, v0, v1);
        sq(v0, a1, 64);
        lw(v0, gp, -17148);  // 0x7CE9F4
        a2 = addiu(v0, 80);
        sw(a2, gp, -17148);  // 0x7CE9F4
        backedge(ctx);
    } else {
        // 0x00472df8
        charge(ctx, 30);
        v0 = 0x50000000;
        a2 = dsll32(a2, 0);
        v0 = v0 | 0x4;
        v1 = 0;
        v0 = dsll32(v0, 0);
        a2 = dsra32(a2, 0);
        pcpyld(v0, v0, v1);
        sq(v0, a2, 0);
        a1 = 14;
        v0 = 0x10000000;
        a0 = 71;
        v1 = dsll32(v0, 0);
        v0 = 0x8003;
        v0 = v0 | v1;
        pcpyld(v0, a1, v0);
        sq(v0, a2, 16);
        v1 = 20;
        ld(a1, gp, -17072);  // 0x7CEA40
        v0 = 8;
        pcpyld(a0, a0, a1);
        sq(a0, a2, 32);
        ld(a0, gp, -17040);  // 0x7CEA60
        pcpyld(v1, v1, a0);
        sq(v1, a2, 48);
        ld(v1, gp, -17048);  // 0x7CEA58
        pcpyld(v0, v0, v1);
        sq(v0, a2, 64);
        lw(v0, gp, -17148);  // 0x7CE9F4
        a2 = addiu(v0, 80);
        sw(a2, gp, -17148);  // 0x7CE9F4
    }
    // 0x00472e70
    charge(ctx, 16);
    lbu(v0, s4, 40);
    v1 = v0 & 0x20;
    v0 = v0 & 0x18;
    v1 = sra(v1, 5);
    v0 = sra(v0, 2);
    v0 = v1 | v0;
    sb(v0, s4, 43);
    lw(v1, s4, 4);
    lbu(a0, s4, 43);
    lw(v0, gp, -16888);  // 0x7CEAF8
    lw(v1, v1, 24);
    a0 = sll(a0, 2);
    v1 = addu(v1, a0);
    lw(a0, v1, 0);
    pass.program = a0.u();
    pass.uploaded = v0 != a0;
    if (v0 != a0) {
        // 0x00472eb0
        charge(ctx, 13);
        v0 = dsll32(a0, 0);
        a1 = 0;
        v0 = dsrl32(v0, 0);
        v1 = dsll32(v0, 0);
        v0 = 0x50000000;
        v1 = v1 | v0;
        lw(v0, gp, -17148);  // 0x7CE9F4
        pcpyld(v1, a1, v1);
        sq(v1, v0, 0);
        lw(v0, gp, -17148);  // 0x7CE9F4
        sw(a0, gp, -16888);  // 0x7CEAF8
        a2 = addiu(v0, 16);
        sw(a2, gp, -17148);  // 0x7CE9F4
    }
    // 0x00472ee4
    charge(ctx, 21);
    lw(a2, s4, 48);
    t0 = 0x2000000;
    lw(a0, s4, 4);
    a3 = 0x3000000;
    lw(v1, gp, -17148);  // 0x7CE9F4
    a1 = 0x50000000;
    v0 = 0x10000;
    lw(a2, a2, 0);
    lw(t1, a0, 20);
    a0 = addiu(a2, 24);
    t0 = t1 | t0;
    lwu(a2, a2, 32);
    t0 = dsll32(t0, 0);
    a3 = t0 | a3;
    a2 = dsll32(a2, 0);
    a1 = a2 | a1;
    pcpyld(a1, a3, a1);
    sq(a1, v1, 0);
    lw(v1, gp, -17148);  // 0x7CE9F4
    a2 = addiu(v1, 16);
    sw(a2, gp, -17148);  // 0x7CE9F4
    pass.res_entry = a2.u();
    pass.vif_offset = t1.u();
    for (;;) {
        // 0x00472f38
        charge(ctx, 7);
        di(ctx);
        sync(ctx, 16);
        mfc0(v1, 12);
        v1 = v1 & v0;
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00472f54
    charge(ctx, 11);
    lw(v0, a0, 0);
    v0 = addiu(v0, 1);
    sw(v0, a0, 0);
    ei(ctx);
    v0 = 1;
    lw(v1, a0, 4);
    v1 = addiu(v1, 1);
    sw(v1, a0, 4);
    lw(v1, a0, 4);
    if (v1 == v0) {
        // 0x00472f80
        charge(ctx, 2);
        jal(ctx, 0x472F80u, gen::fn__rwDMAAddPURef_004d51c0);
    }
    // 0x00472f88
    charge(ctx, 29);
    a0 = 0;
    a1 = 3;
    jal(ctx, 0x472F8Cu, gen::fn__rwDMAOpenVIFPkt_004d59d0);
    v0 = 0x50000000;
    v1 = 0;
    v0 = v0 | 0x2;
    a3 = 0;
    ppacw(t0, v0, v1);
    lw(a2, gp, -17148);  // 0x7CE9F4
    closing_at = a2.u();  // the closing packet
    v0 = 0x10000000;
    a1 = 14;
    a0 = v0 | 0x2;
    v1 = dsll32(v0, 0);
    ppacw(v0, a3, a0);
    ppacw(v0, t0, v0);
    sq(v0, a2, 0);
    a0 = 61;
    v0 = 0x8001;
    v0 = v0 | v1;
    pcpyld(v0, a1, v0);
    sq(v0, a2, 16);
    ld(v1, gp, -17056);  // 0x7CEA50
    v0 = 1;
    pcpyld(v1, a0, v1);
    sq(v1, a2, 32);
    lw(v1, gp, -17148);  // 0x7CE9F4
    a2 = addiu(v1, 48);
    sw(a2, gp, -17148);  // 0x7CE9F4
    report_mesh(ctx, s4.u(), pass);
    report_effect(ctx, Effect::DualUvTransform, s4.u(), rd32(ctx, matfx_ext(ctx, s4.u()) + 64), extra_at, 19, closing_at, 3);
    // 0x0047330c
    charge(ctx, 12);
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
    sp = addiu(sp, 0x110);
}

// 0x004718A0 skinSplitObjectSetupCB -- 2184 bytes; frame 0x120: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// skinSplitObjectSetupCB [skin object set-up callback, partitioned skins] ($a0 = PipeData, $a1 = the matrix reference): the
// body of sub_46EB90 (mesh.cpp skin_setup: the resEntry array, the morph interpolator, sub_4A0480 inlined, the object
// matrix = LTM x the camera's view, the frustum test of the bounding sphere, prim / transType inlined, the lighting
// hook 0x95DE34 or sub_4A06C0 inlined, _rpSkinMatrixUpdating) with a different palette step: a skin with partitions
// (skin +48 != 0) only records them for the per-mesh wrappers (0x95DE38 = skin + 44; the wrappers sub_472130 ..
// sub_473380 call the partitioned upload sub_46B8E0); otherwise the whole palette is uploaded (cnt 4 x bones +
// STCYCL 1,1 / UNPACK V4-32 to VU1 0x2BC, eight matrices per iteration then one) and 0x95DE38 is cleared. Frame
// 288: s0..s8, $ra at +144, the skin at sp+160, the light frame record at sp+176 (inverse LTM at sp+192, scale /
// inverse scale at sp+256 / sp+260). Returns 1, 0 for a geometry without meshes.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: callee frames ($sp off / deeper stack)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void skinSplitObjectSetupCB(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::addu, hg::backedge, hg::c_le_s, hg::c_lt_s, hg::call,
          hg::charge, hg::cond, hg::div_s, hg::dsll32, hg::dsra32, hg::dsrl32, hg::enter, hg::i64, hg::jal, hg::jalr,
          hg::lbu, hg::ld, hg::lh, hg::lhu, hg::link, hg::lq, hg::lw, hg::lwc1, hg::madd_s, hg::madda_s, hg::mtc1,
          hg::mul_s, hg::mula_s, hg::neg_s, hg::ppacw, hg::sb, hg::sd, hg::sh, hg::si, hg::sll, hg::slti, hg::sltiu,
          hg::sltu, hg::sq, hg::sqrt_s, hg::srl, hg::sub_s, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7};
    // 0x004718a0
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x120);
    v0 = 0x960000;
    sd(ra, sp, 0x90);
    a2 = 1;
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(fp, a0, 8);
    s0 = a1;
    lw(v1, v0, -8680);  // 0x95DE18
    lw(v0, fp, 0x18);
    v1 = addu(v0, v1);
    lw(a1, v0, 84);
    lw(v1, v1, 0);
    lw(s7, v1, 0);
    sw(v1, sp, 0xA0);
    sw(a1, a0, 12);
    lw(v1, v0, 24);
    s1 = a0;
    if (v1 != a2) {
        // 0x00471b68
        charge(ctx, 5);
        lw(v1, gp, -17508);  // 0x7CE88C
        a0 = addu(fp, v1);
        lw(v1, a0, 0);
        a3 = 0;
        if (v1 != 0) {
            // 0x00471b7c
            charge(ctx, 5);
            lw(a1, v0, 84);
            lw(v1, v1, 0);
            lhu(a1, a1, 4);
            if (a1 == v1) {
                // 0x00471b90
                charge(ctx, 1);
                a3 = a2;
            }
        }
        // 0x00471b94
        charge(ctx, 2);
        if (a3 == 0) {
            // 0x00471ba4
            charge(ctx, 5);
            lw(v0, v0, 84);
            link(ctx, 0x471BA8u);  // $ra first: the delay slot below depends on it
            lhu(a1, v0, 4);
            call(ctx, gen::fn_sub_49E5A0_0049e5a0);
            a0 = v0;
            lw(v0, a0, 0);
        } else {
            // 0x00471b9c
            charge(ctx, 2);
            lw(v0, a0, 0);
        }
        // 0x00471bb8
        charge(ctx, 2);
        sw(v0, s1, 16);
        backedge(ctx);
    } else {
        // 0x00471908
        charge(ctx, 5);
        lw(v1, gp, -17504);  // 0x7CE890
        a0 = addu(v0, v1);
        lw(v1, a0, 0);
        a3 = 0;
        if (v1 != 0) {
            // 0x0047191c
            charge(ctx, 5);
            lw(a1, v0, 84);
            lw(v1, v1, 0);
            lhu(a1, a1, 4);
            if (a1 == v1) {
                // 0x00471930
                charge(ctx, 1);
                a3 = a2;
            }
        }
        // 0x00471934
        charge(ctx, 2);
        if (a3 == 0) {
            // 0x00471944
            charge(ctx, 5);
            lw(v0, v0, 84);
            link(ctx, 0x471948u);  // $ra first: the delay slot below depends on it
            lhu(a1, v0, 4);
            call(ctx, gen::fn_sub_49E5A0_0049e5a0);
            a0 = v0;
            lw(v0, a0, 0);
        } else {
            // 0x0047193c
            charge(ctx, 2);
            lw(v0, a0, 0);
        }
        // 0x00471958
        charge(ctx, 1);
        sw(v0, s1, 16);
    }
    // 0x0047195c
    charge(ctx, 4);
    lw(v0, s1, 12);
    lhu(v0, v0, 4);
    if (i64(v0) <= 0) {
        // 0x00471bc0
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x0047196c
        charge(ctx, 7);
        lw(v0, fp, 0x18);
        lw(v0, v0, 24);
        sw(v0, s1, 32);
        lw(v0, s1, 32);
        at = slti(v0, 2);
        if (at == 0) {
            // 0x00471bc8
            charge(ctx, 5);
            lwc1(f1, fp, 0x58);
            lwc1(f0, fp, 0x5C);
            mul_s(f0, f1, f0);
            swc1(f0, s1, 28);
            backedge(ctx);
        }
        // 0x00471988
        charge(ctx, 6);
        lw(v0, fp, 0x18);
        v1 = 0x1000000;
        lw(a0, v0, 8);
        v1 = a0 & v1;
        if (v1 == 0) {
            // 0x00471bdc
            charge(ctx, 18);
            lw(a2, s1, 12);
            v1 = a0 & 0x9F;
            lbu(a0, v0, 24);
            v1 = v1 & 0xFF;
            a1 = sll(v1, 16);
            v1 = si(-2);
            lhu(a2, a2, 6);
            a0 = sll(a0, 24);
            a1 = a2 | a1;
            a0 = a0 | a1;
            sw(a0, s1, 24);
            lw(a0, s1, 20);
            v1 = a0 & v1;
            sw(v1, s1, 20);
            lw(v1, s1, 16);
            lw(v1, v1, 4);
            if (v1 == 0) {
                backedge(ctx);
            } else {
                // 0x00471c24
                charge(ctx, 5);
                lw(t0, v1, 40);
                a0 = addiu(v1, 24);
                lw(a3, s1, 24);
                v1 = addiu(fp, 0x4C);
                if (a3 != t0) {
                    // 0x00471c38
                    charge(ctx, 6);
                    a2 = srl(a3, 16);
                    a1 = srl(t0, 16);
                    a2 = a2 & 0xFF;
                    a1 = a1 & 0xFF;
                    if (a2 == a1) {
                        // 0x00471c50
                        charge(ctx, 6);
                        a2 = srl(a3, 24);
                        a1 = srl(t0, 24);
                        a2 = a2 & 0xFF;
                        a1 = a1 & 0xFF;
                        if (a2 != a1) {
                            goto L_00471c78;
                        }
                        // 0x00471c68
                        charge(ctx, 4);
                        lw(a1, s1, 20);
                        a1 = a1 | 0x4;
                        sw(a1, s1, 20);
                        goto L_00471c84;
                    }
                L_00471c78:
                    charge(ctx, 3);
                    lw(a1, s1, 20);
                    a1 = a1 | 0x8;
                    sw(a1, s1, 20);
                }
            L_00471c84:
                charge(ctx, 3);
                lhu(a1, v0, 12);
                if (a1 != 0) {
                    // 0x00471c90
                    charge(ctx, 3);
                    a1 = a1 & 0x1;
                    if (a1 == 0) {
                        // 0x00471cac
                        charge(ctx, 8);
                        lw(a1, s1, 20);
                        a1 = a1 | 0x2;
                        sw(a1, s1, 20);
                        lhu(a1, v0, 12);
                        lw(v0, s1, 20);
                        a1 = sll(a1, 3);
                        v0 = v0 | a1;
                        sw(v0, s1, 20);
                    } else {
                        // 0x00471c9c
                        charge(ctx, 4);
                        lw(v0, s1, 20);
                        v0 = v0 | 0x8;
                        sw(v0, s1, 20);
                    }
                }
                // 0x00471ccc
                charge(ctx, 4);
                lw(v0, v1, 0);
                v0 = v0 & 0x1;
                if (v0 == 0) {
                    backedge(ctx);
                } else {
                    // 0x00471cdc
                    charge(ctx, 4);
                    lw(a1, a0, 40);
                    lh(v0, v1, 6);
                    if (a1 == v0) {
                        // 0x00471cec
                        charge(ctx, 4);
                        lw(a0, a0, 36);
                        lh(v0, v1, 4);
                        if (a0 != v0) {
                            goto L_00471cfc;
                        }
                        backedge(ctx);
                        goto L_004719a0;
                    }
                L_00471cfc:
                    charge(ctx, 4);
                    lw(v0, s1, 20);
                    v0 = v0 | 0x4;
                    sw(v0, s1, 20);
                    backedge(ctx);
                }
            }
        }
    L_004719a0:
        charge(ctx, 26);
        lw(a0, fp, 0x18);
        v1 = si(-2);
        v0 = 0x960000;
        sh(zero, a0, 12);
        lw(a0, fp, 0x4C);
        v1 = a0 & v1;
        sw(v1, fp, 0x4C);
        lw(v0, v0, 112);  // 0x960070
        lw(a0, fp, 0x4);
        s2 = addiu(v0, 32);
        jal(ctx, 0x4719C4u, gen::fn_sub_4CB2F0_004cb2f0);
        lw(a0, s0, 0);
        a1 = v0;
        a2 = s2;
        jal(ctx, 0x4719D4u, gen::fn_sub_4C2F30_004c2f30);
        a0 = fp;
        s0 = 2;
        jal(ctx, 0x4719E0u, gen::fn_atomicGetWorldBoundingSphere_004912b0);
        v1 = 0x960000;
        lw(a0, gp, -16972);  // 0x7CEAA4
        lw(a1, v1, 112);  // 0x960070
        v1 = 6;
        a0 = addu(a1, a0);
        a2 = addiu(v1, -1);
        a0 = addiu(a0, 96);
        if (v1 != 0) {
            // 0x00471a08
            charge(ctx, 6);
            lwc1(f0, v0, 12);
            v1 = 1;
            lwc1(f7, v0, 4);
            lwc1(f6, v0, 0);
            lwc1(f5, v0, 8);
            neg_s(f4, f0);
            for (;;) {
                // 0x00471a20
                charge(ctx, 11);
                lwc1(f1, a0, 4);
                lwc1(f2, a0, 0);
                lwc1(f3, a0, 8);
                lwc1(f0, a0, 12);
                mula_s(f7, f1);
                madda_s(f6, f2);
                madd_s(f1, f5, f3);
                sub_s(f0, f1, f0);
                c_le_s(f0, f4);
                v0 = v1;
                if (cond(ctx)) {
                    // 0x00471a4c
                    charge(ctx, 1);
                    v0 = 0;
                }
                // 0x00471a50
                charge(ctx, 3);
                v0 = v0 ^ 0x1;
                if (v0 == 0) {
                    goto L_00471a5c_16;
                }
                // 0x00471a64
                charge(ctx, 4);
                v0 = a2;
                a0 = addiu(a0, 20);
                a2 = addiu(a2, -1);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00471a74
            charge(ctx, 1);
        }
    L_00471a78:
        charge(ctx, 7);
        lw(v1, s1, 12);
        v0 = dsll32(s0, 0);
        a2 = 1;
        lw(a3, v1, 0);
        v1 = a3 & 0x1;
        v0 = dsra32(v0, 0);
        if (v1 == a2) {
            // 0x00471d0c
            charge(ctx, 5);
            v1 = 4;
            sb(v1, s1, 41);
            lbu(v1, gp, -16892);  // 0x7CEAF4
            sb(v1, s1, 40);
            backedge(ctx);
        } else {
            // 0x00471a94
            charge(ctx, 3);
            v1 = a3 & 0xFF;
            if (v1 != 0) {
                // 0x00471aa0
                charge(ctx, 4);
                v1 = a3 & 0x2;
                a1 = 2;
                if (v1 == a1) {
                    goto L_00471d20;
                }
                // 0x00471ab0
                charge(ctx, 4);
                a0 = a3 & 0x10;
                v1 = 16;
                if (a0 == v1) {
                    // 0x00471d38
                    charge(ctx, 5);
                    v1 = 4;
                    sb(v1, s1, 41);
                    lbu(v1, gp, -16892);  // 0x7CEAF4
                    sb(v1, s1, 40);
                    backedge(ctx);
                } else {
                    // 0x00471ac0
                    charge(ctx, 4);
                    a0 = a3 & 0x8;
                    v1 = 8;
                    if (a0 != v1) {
                        // 0x00471ae4
                        charge(ctx, 4);
                        sb(a2, s1, 41);
                        lbu(v1, gp, -16892);  // 0x7CEAF4
                        v1 = v1 | 0x14;
                        sb(v1, s1, 40);
                    } else {
                        // 0x00471ad0
                        charge(ctx, 5);
                        sb(a1, s1, 41);
                        lbu(v1, gp, -16892);  // 0x7CEAF4
                        v1 = v1 | 0x10;
                        sb(v1, s1, 40);
                    }
                }
                goto L_00471af4;
            }
        L_00471d20:
            charge(ctx, 6);
            v1 = 3;
            sb(v1, s1, 41);
            lbu(v1, gp, -16892);  // 0x7CEAF4
            v1 = v1 | 0x4;
            sb(v1, s1, 40);
            backedge(ctx);
        }
    L_00471af4:
        charge(ctx, 3);
        v1 = 2;
        if (v0 != v1) {
            // 0x00471d4c
            charge(ctx, 4);
            lbu(v0, s1, 40);
            v0 = v0 | 0x2;
            sb(v0, s1, 40);
            backedge(ctx);
        }
        // 0x00471b00
        charge(ctx, 9);
        lw(v1, fp, 0x18);
        v0 = 0x960000;
        lw(v1, v1, 8);
        v1 = v1 & 0x40;
        v1 = sltu(0, v1);
        sb(v1, s1, 42);
        lw(v0, v0, -8652);  // 0x95DE34
        if (v0 != 0) {
            // 0x00471b24
            charge(ctx, 3);
            lw(a1, s1, 8);
            a0 = 1;
            jalr(ctx, 0x471B28u, v0.u());
            goto L_00471b30;
        }
        // 0x00471d5c
        charge(ctx, 6);
        lw(s4, s1, 8);
        lw(s1, s4, 24);
        lw(v0, s1, 8);
        v0 = v0 & 0x20;
        if (v0 == 0) {
            backedge(ctx);
        L_00471b30:
            charge(ctx, 1);
            lw(a1, sp, 0xA0);
        } else {
            // 0x00471d74
            charge(ctx, 16);
            s5 = 0x960000;
            s5 = addiu(s5, 122);  // &0x96007A
            lhu(v0, s5, 0);  // 0x96007A
            v0 = addiu(v0, 1);
            sh(v0, s5, 0);  // 0x96007A
            link(ctx, 0x471D88u);  // $ra first: the delay slot below depends on it
            lw(a0, s4, 4);
            call(ctx, gen::fn_sub_4CB2F0_004cb2f0);
            s0 = v0;
            a0 = addiu(sp, 0xC0);
            a1 = s0;
            jal(ctx, 0x471D98u, gen::fn_sub_4C32A0_004c32a0);
            lw(v1, s0, 12);
            v0 = 3;
            v1 = v1 & 0x3;
            if (v1 != v0) {
                // 0x00471dc4
                charge(ctx, 12);
                lwc1(f3, sp, 0xE4);
                lwc1(f2, sp, 0xE0);
                lwc1(f0, sp, 0xE8);
                mtc1(zero, f1);
                mula_s(f3, f3);
                madda_s(f2, f2);
                madd_s(f0, f0, f0);
                sqrt_s(f2, f0);
                c_le_s(f2, f1);
                swc1(f2, sp, 0x100);
                if (!cond(ctx)) {
                    // 0x00471df4
                    charge(ctx, 7);
                    v0 = 0x3F800000;
                    mtc1(v0, f0);
                    div_s(f2, f0, f2);
                }
                // 0x00471e10
                charge(ctx, 1);
                swc1(f2, sp, 0x104);
            } else {
                // 0x00471db4
                charge(ctx, 4);
                v0 = 0x3F800000;
                sw(v0, sp, 0x100);
                sw(v0, sp, 0x104);
            }
            // 0x00471e14
            charge(ctx, 14);
            lw(v1, s1, 84);
            a0 = 0x4A0000;
            a0 = addiu(a0, 1072);  // &sub_4A0430
            a1 = addiu(sp, 0xB0);
            lw(v0, v1, 12);
            v0 = addu(v0, v1);
            lw(v0, v0, 24);
            v0 = addiu(v0, 12);
            link(ctx, 0x471E34u);  // $ra first: the delay slot below depends on it
            sw(v0, sp, 0xB0);
            call(ctx, gen::fn_worldForAllLights_00499c20);
            lw(s3, s4, 100);
            s6 = addiu(s4, 100);
            if (s3 == s6) {
                backedge(ctx);
                goto L_00471b30;
            }
            for (;;) {
                // 0x00471e4c
                charge(ctx, 5);
                lw(v0, s3, 8);
                lw(s2, v0, 64);
                s1 = addiu(v0, 64);
                if (s2 != s1) {
                    for (;;) {
                        // 0x00471e60
                        charge(ctx, 3);
                        lw(a1, s2, 8);
                        if (a1 != 0) {
                            // 0x00471e6c
                            charge(ctx, 4);
                            lhu(a0, s5, 0);
                            lhu(v0, a1, 60);
                            v1 = addiu(a1, 60);
                            if (v0 != a0) {
                                // 0x00471e7c
                                charge(ctx, 4);
                                lbu(v0, a1, 2);
                                v0 = v0 & 0x1;
                                if (v0 != 0) {
                                    // 0x00471e8c
                                    charge(ctx, 27);
                                    sh(a0, v1, 0);
                                    lw(v0, s2, 8);
                                    link(ctx, 0x471E94u);  // $ra first: the delay slot below depends on it
                                    lw(a0, v0, 4);
                                    call(ctx, gen::fn_sub_4CB2F0_004cb2f0);
                                    s0 = addiu(v0, 48);
                                    a0 = s4;
                                    jal(ctx, 0x471EA0u, gen::fn_atomicGetWorldBoundingSphere_004912b0);
                                    lwc1(f4, v0, 4);
                                    lw(a0, s2, 8);
                                    lwc1(f3, s0, 4);
                                    lwc1(f6, v0, 0);
                                    lwc1(f5, s0, 0);
                                    lwc1(f0, s0, 8);
                                    lwc1(f1, v0, 8);
                                    lwc1(f2, v0, 12);
                                    sub_s(f3, f4, f3);
                                    sub_s(f5, f6, f5);
                                    mula_s(f3, f3);
                                    sub_s(f0, f1, f0);
                                    madda_s(f5, f5);
                                    madd_s(f1, f0, f0);
                                    lwc1(f0, a0, 20);
                                    add_s(f0, f2, f0);
                                    mul_s(f0, f0, f0);
                                    c_lt_s(f1, f0);
                                    if (cond(ctx)) {
                                        // 0x00471ef8
                                        charge(ctx, 2);
                                        a1 = addiu(sp, 0xB0);
                                        jal(ctx, 0x471EF8u, gen::fn_sub_4A0430_004a0430);
                                    }
                                }
                            }
                        }
                        // 0x00471f00
                        charge(ctx, 3);
                        lw(s2, s2, 0);
                        if (s2 == s1) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x00471f0c
                    charge(ctx, 1);
                }
                // 0x00471f10
                charge(ctx, 3);
                lw(s3, s3, 0);
                if (s3 == s6) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00471f1c
            charge(ctx, 2);
            lw(a1, sp, 0xA0);
            backedge(ctx);
        }
        // 0x00471b34
        charge(ctx, 7);
        a0 = fp;
        jal(ctx, 0x471B34u, gen::fn__rpSkinMatrixUpdating_0046b510);
        s0 = v0;
        lw(v0, sp, 0xA0);
        lw(v0, v0, 48);
        if (v0 == 0) {
            // 0x00471f24
            charge(ctx, 25);
            s1 = sll(s7, 2);
            a0 = 0;
            a1 = addiu(s1, 2);
            jal(ctx, 0x471F2Cu, gen::fn__rwDMAOpenVIFPkt_004d59d0);
            v0 = s1 & 0xFF;
            a0 = 0x6C000000;
            a1 = sll(v0, 16);
            a0 = a0 | 0x2BC;
            v0 = 0x1000000;
            a0 = a1 | a0;
            v0 = v0 | 0x101;  // &0x1000101
            v1 = dsll32(s1, 0);
            ppacw(a3, a0, v0);
            lw(a2, gp, -17148);  // 0x7CE9F4
            v1 = dsrl32(v1, 0);
            v0 = 0x10000000;
            v0 = v1 | v0;
            a1 = 0;
            ppacw(v0, a1, v0);
            ppacw(v0, a3, v0);
            at = sltu(0, s7);
            a0 = addiu(a2, 16);
            v1 = 0;
            sq(v0, a2, 0);
            if (at != 0) {
                // 0x00471f88
                charge(ctx, 3);
                at = sltiu(s7, 9);
                v0 = addiu(s7, -8);
                if (at == 0) {
                    for (;;) {
                        // 0x00471f94
                        charge(ctx, 69);
                        lq(t1, s0, 16);
                        v1 = addiu(v1, 8);
                        lq(t0, s0, 32);
                        a1 = sltu(v1, v0);
                        lq(a3, s0, 48);
                        lq(a2, s0, 0);
                        sq(a2, a0, 0);
                        sq(t1, a0, 16);
                        sq(t0, a0, 32);
                        sq(a3, a0, 48);
                        lq(t1, s0, 80);
                        lq(t0, s0, 96);
                        lq(a3, s0, 112);
                        lq(a2, s0, 64);
                        sq(a2, a0, 64);
                        sq(t1, a0, 80);
                        sq(t0, a0, 96);
                        sq(a3, a0, 112);
                        lq(t1, s0, 144);
                        lq(t0, s0, 160);
                        lq(a3, s0, 176);
                        lq(a2, s0, 128);
                        sq(a2, a0, 128);
                        sq(t1, a0, 144);
                        sq(t0, a0, 160);
                        sq(a3, a0, 176);
                        lq(t1, s0, 208);
                        lq(t0, s0, 224);
                        lq(a3, s0, 240);
                        lq(a2, s0, 192);
                        sq(a2, a0, 192);
                        sq(t1, a0, 208);
                        sq(t0, a0, 224);
                        sq(a3, a0, 240);
                        lq(t1, s0, 272);
                        lq(t0, s0, 288);
                        lq(a3, s0, 304);
                        lq(a2, s0, 256);
                        sq(a2, a0, 256);
                        sq(t1, a0, 272);
                        sq(t0, a0, 288);
                        sq(a3, a0, 304);
                        lq(t1, s0, 336);
                        lq(t0, s0, 352);
                        lq(a3, s0, 368);
                        lq(a2, s0, 320);
                        sq(a2, a0, 320);
                        sq(t1, a0, 336);
                        sq(t0, a0, 352);
                        sq(a3, a0, 368);
                        lq(t1, s0, 400);
                        lq(t0, s0, 416);
                        lq(a3, s0, 432);
                        lq(a2, s0, 384);
                        sq(a2, a0, 384);
                        sq(t1, a0, 400);
                        sq(t0, a0, 416);
                        sq(a3, a0, 432);
                        lq(t1, s0, 464);
                        lq(t0, s0, 480);
                        lq(a3, s0, 496);
                        lq(a2, s0, 448);
                        sq(a2, a0, 448);
                        s0 = addiu(s0, 512);
                        sq(t1, a0, 464);
                        sq(t0, a0, 480);
                        sq(a3, a0, 496);
                        a0 = addiu(a0, 512);
                        if (a1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x004720a8
                charge(ctx, 3);
                at = sltu(v1, s7);
                if (at != 0) {
                    for (;;) {
                        // 0x004720b4
                        charge(ctx, 13);
                        lq(t0, s0, 16);
                        v1 = addiu(v1, 1);
                        lq(a3, s0, 32);
                        v0 = sltu(v1, s7);
                        lq(a2, s0, 48);
                        lq(a1, s0, 0);
                        sq(a1, a0, 0);
                        s0 = addiu(s0, 64);
                        sq(t0, a0, 16);
                        sq(a3, a0, 32);
                        sq(a2, a0, 48);
                        a0 = addiu(a0, 64);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
            }
            // 0x004720e8
            charge(ctx, 4);
            v0 = 0x960000;
            sw(a0, gp, -17148);  // 0x7CE9F4
            sw(zero, v0, -8648);  // 0x95DE38
            // the draw record (host-only): the whole palette went to VU1 0x2BC
            if (const DrawObserver* obs = draw_observer(); obs && obs->skin)
                obs->skin(ctx, SkinPalette{rd32(ctx, 0x0095DE1Cu), s7.u()});
            backedge(ctx);
        } else {
            // 0x00471b50
            charge(ctx, 4);
            lw(v0, sp, 0xA0);
            v1 = addiu(v0, 44);
            v0 = 0x960000;
            sw(v1, v0, -8648);  // 0x95DE38
        }
        // 0x00471b60
        charge(ctx, 2);
        v0 = 1;
    }
    // 0x004720f8 (the shared epilogue, written out on this path)
    charge(ctx, 12);
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
    sp = addiu(sp, 0x120);
    return;
L_00471a5c_16:
    charge(ctx, 2);
    s0 = 1;
    goto L_00471a78;
}

// The MatFX effect observer (bridges.h; tests): the regenerated bridges no longer report through it.
void bridges::set_effect_observer(const EffectObserver* observer) noexcept { g_effect_observer = observer; }

}  // namespace p3fes::game

// --- the recompiled program's entry points -----------------------------------------------------------------------
