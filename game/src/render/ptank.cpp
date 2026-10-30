// RenderWare's particle tanks (RpPTank): the sprite writers, the tank callbacks and the draw path (ptank.h has the
// data flow; docs/ANALYSIS/22_rendering.md sections 2.4, 4 and 7).
//
// Cycle model (ADR-0013): every charge() below is one `ctx.cycles += N` block of the recompiled body in
// recomp/generated (fn_0042_*); backedge() sits wherever that body has a check point on a backward jump -- loops, and
// the backward `goto`s of the compiler's block layout, which the hand versions keep as explicit check points. A block
// that ends in a `jal` is charged in full before the call (the recompiler keeps the call inside its block).
//
// Registers: register-faithful (ptank.h). Each body runs on a Cpu view of the guest context: one variable per GPR
// (64-bit writes keep bits 64..127, as the EE does; lq / MMI results write all 128), the FPU / VU0 / HI-LO operations
// through the runtime's own instruction semantics, prologue spills and epilogue reloads on the guest stack. The loop
// shapes are the compiled ones (a loop that runs at least once tests at its bottom, with the branch delay slot's
// instruction executed on both paths); guest structure offsets are named in ptank.h and in the comments.
//
// Faithfulness audit (2026-10-21, tools/ours/audit): all 44 functions here are now p3fes_handgen's register-faithful
// bodies (the hand versions differed from the original: the hand version terminated the host on a random world 24,
// frame/spills 8, faults only 7, callee frames 5). Each keeps the notes of its earlier hand version above it; what
// this header says about how the bodies were written describes those earlier versions.
#include "p3fes/game/ptank.h"

#include "p3fes_recomp_rt.h"

#include <initializer_list>
#include "p3fes/game/hg_cpu.h"

namespace p3fes::recomp_gen {
void fn_sub_4933D0_004933d0(p3fes::EEContext&);  // RwResources: release an instanced resource entry
void fn_sub_476C20_00476c20(p3fes::EEContext&);  // RpPTank scratchpad streamer: copy (dst, src, bytes) (D9 / D8)
void fn_sub_476720_00476720(p3fes::EEContext&);  // RpPTank scratchpad streamer: 16-byte pattern fill (dst, bytes, pattern)
void fn_sub_476140_00476140(p3fes::EEContext&);  // RpPTank scratchpad streamer: word fill (dst, bytes, word)
void fn_sub_49E5A0_0049e5a0(p3fes::EEContext&);  // resEntry array (re)allocation (RwMalloc / RwFree)
void fn_sub_474A80_00474a80(p3fes::EEContext&);  // RpPTank: reset the tank's instance data
void fn_sub_4D5E90_004d5e90(p3fes::EEContext&);  // flush the open scratchpad half (D8 fromSPR) and wait for it
void fn_sub_4CB2F0_004cb2f0(p3fes::EEContext&);  // RwFrameGetLTM
void fn_geometryLock_00493370(p3fes::EEContext&);  // RpGeometry lock (geometry, mode)
void fn_sub_4749A0_004749a0(p3fes::EEContext&);  // RpPTank: the CLAMP word from the texture's address modes
void fn_sub_4748C0_004748c0(p3fes::EEContext&);  // (render_rw2) PTank texture: raster resident + TEX0 / TEX1
void fn__rwDMAOpenVIFPkt_004d59d0(p3fes::EEContext&);  // the DMA packet layer: open a VIF packet (type, qwords)
void fn_sub_49CAB0_0049cab0(p3fes::EEContext&);  // (render_mesh) material colour upload
void fn_ps2AllInstanceDmaChain_0049dc70(p3fes::EEContext&);  // PS2All: re-instance the mesh (pipe data)
void fn__rwDMAAddPURef_004d51c0(p3fes::EEContext&);  // the DMA packet layer: resource reference
void fn_sub_4C6BE0_004c6be0(p3fes::EEContext&);  // RwV3dTransformPoints-like: the bounding sphere by a matrix
void fn_sub_46C330_0046c330(p3fes::EEContext&);  // (render_rw2) VU1 record upload (src, n) -> src
void fn_RxPipelineExecute_004f2e70(p3fes::EEContext&);  // RxPipelineExecute(pipeline, data, 1)
void fn_memset_00521408(p3fes::EEContext&);      // libc memset
void fn_sinf_0052e878(p3fes::EEContext&);        // libm sinf($f12) -> $f0
void fn_cosf_0052e6d8(p3fes::EEContext&);        // libm cosf($f12) -> $f0
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

// 0x00486980 sub_486980 -- 344 bytes; leaf frame (no stack)
// sub_486980 [positions, constant size]: the corner offsets are computed once from the constant size (+112, +116)
// and kept in $f0..$f11 ((x, y, z) of corner 0..3); positions {+4 pointer, +8 stride}.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: the hand version terminated the host on a random world.
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_486980(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::lwc1,
          hg::mtc1, hg::mul_s, hg::neg_s, hg::slt, hg::sub_s, hg::swc1;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f13{ctx, 13};
    // 0x00486980
    enter(ctx, 40);  // entry check point + this block's cycles
    lwc1(f5, t0, 112);
    v1 = 0x3F000000;
    mtc1(v1, f6);
    lw(t3, t0, 4);
    lwc1(f2, a1, 8);
    lw(t1, t0, 8);
    lwc1(f1, t0, 116);
    lw(t2, a0, 0);
    lwc1(f3, a1, 4);
    at = slt(0, a3);
    lwc1(f4, a1, 0);
    t4 = 0;
    mul_s(f5, f6, f5);
    lw(t0, a0, 4);
    mul_s(f12, f2, f5);
    mul_s(f7, f3, f5);
    lwc1(f0, a2, 0);
    mul_s(f6, f6, f1);
    mul_s(f13, f4, f5);
    lwc1(f2, a2, 8);
    lwc1(f3, a2, 4);
    mul_s(f4, f0, f6);
    neg_s(f1, f13);
    mul_s(f8, f2, f6);
    mul_s(f5, f3, f6);
    neg_s(f2, f7);
    neg_s(f3, f12);
    sub_s(f0, f1, f4);
    add_s(f9, f1, f4);
    sub_s(f1, f2, f5);
    add_s(f10, f2, f5);
    sub_s(f2, f3, f8);
    add_s(f11, f3, f8);
    sub_s(f3, f13, f4);
    add_s(f6, f13, f4);
    sub_s(f4, f7, f5);
    add_s(f7, f7, f5);
    sub_s(f5, f12, f8);
    add_s(f8, f12, f8);
    if (at != 0) {
        for (;;) {
            // 0x00486a20
            charge(ctx, 44);
            lwc1(f12, t3, 0);
            a2 = addu(t2, t0);
            a1 = addu(a2, t0);
            t4 = addiu(t4, 1);
            a0 = addu(a1, t0);
            v1 = slt(t4, a3);
            add_s(f12, f12, f0);
            swc1(f12, t2, 0);
            lwc1(f12, t3, 4);
            add_s(f12, f12, f1);
            swc1(f12, t2, 4);
            lwc1(f12, t3, 8);
            add_s(f12, f12, f2);
            swc1(f12, t2, 8);
            lwc1(f12, t3, 0);
            t2 = addu(a0, t0);
            add_s(f12, f12, f3);
            swc1(f12, a2, 0);
            lwc1(f12, t3, 4);
            add_s(f12, f12, f4);
            swc1(f12, a2, 4);
            lwc1(f12, t3, 8);
            add_s(f12, f12, f5);
            swc1(f12, a2, 8);
            lwc1(f12, t3, 0);
            add_s(f12, f12, f6);
            swc1(f12, a1, 0);
            lwc1(f12, t3, 4);
            add_s(f12, f12, f7);
            swc1(f12, a1, 4);
            lwc1(f12, t3, 8);
            add_s(f12, f12, f8);
            swc1(f12, a1, 8);
            lwc1(f12, t3, 0);
            add_s(f12, f12, f9);
            swc1(f12, a0, 0);
            lwc1(f12, t3, 4);
            add_s(f12, f12, f10);
            swc1(f12, a0, 4);
            lwc1(f12, t3, 8);
            add_s(f12, f12, f11);
            t3 = addu(t3, t1);
            swc1(f12, a0, 8);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00486ad0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00486AE0 sub_486AE0 -- 416 bytes; leaf frame (no stack)
// sub_486AE0 [positions, constant size, pivot]: as sub_486980 with the size w = h = +112 and the pivot (+104, +108)
// added to every corner: pivot = px * right + py * up, through ACC.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: the hand version terminated the host on a random world.
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_486AE0(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::lwc1,
          hg::madd_s, hg::mtc1, hg::mul_s, hg::mula_s, hg::neg_s, hg::slt, hg::sub_s, hg::swc1;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15};
    // 0x00486ae0
    enter(ctx, 58);  // entry check point + this block's cycles
    lwc1(f0, t0, 112);
    v1 = 0x3F000000;
    mtc1(v1, f1);
    lw(t4, t0, 4);
    lwc1(f6, a2, 0);
    lw(t2, t0, 8);
    lwc1(f10, t0, 108);
    lw(t3, a0, 0);
    lwc1(f7, a1, 0);
    lw(t1, a0, 4);
    lwc1(f9, t0, 104);
    at = slt(0, a3);
    lwc1(f8, a2, 4);
    t5 = 0;
    lwc1(f3, a1, 8);
    mul_s(f2, f1, f0);
    mula_s(f10, f6);
    madd_s(f15, f9, f7);
    lwc1(f4, a2, 8);
    lwc1(f5, a1, 4);
    mula_s(f10, f8);
    mul_s(f7, f7, f2);
    madd_s(f1, f9, f5);
    mula_s(f10, f4);
    mul_s(f13, f3, f2);
    mul_s(f14, f5, f2);
    mul_s(f12, f4, f2);
    madd_s(f0, f9, f3);
    mul_s(f6, f6, f2);
    mul_s(f8, f8, f2);
    neg_s(f3, f7);
    sub_s(f2, f3, f6);
    add_s(f3, f3, f6);
    add_s(f9, f15, f3);
    neg_s(f4, f14);
    sub_s(f3, f4, f8);
    add_s(f4, f4, f8);
    add_s(f10, f1, f4);
    neg_s(f5, f13);
    sub_s(f4, f5, f12);
    add_s(f5, f5, f12);
    add_s(f11, f0, f5);
    sub_s(f5, f7, f6);
    add_s(f6, f7, f6);
    add_s(f7, f15, f6);
    sub_s(f6, f14, f8);
    add_s(f8, f14, f8);
    add_s(f3, f1, f3);
    add_s(f6, f1, f6);
    add_s(f8, f1, f8);
    sub_s(f1, f13, f12);
    add_s(f4, f0, f4);
    add_s(f12, f13, f12);
    add_s(f1, f0, f1);
    add_s(f2, f15, f2);
    add_s(f5, f15, f5);
    add_s(f0, f0, f12);
    if (at != 0) {
        for (;;) {
            // 0x00486bc8
            charge(ctx, 44);
            lwc1(f12, t4, 0);
            a2 = addu(t3, t1);
            a1 = addu(a2, t1);
            t5 = addiu(t5, 1);
            a0 = addu(a1, t1);
            v1 = slt(t5, a3);
            add_s(f12, f12, f2);
            swc1(f12, t3, 0);
            lwc1(f12, t4, 4);
            add_s(f12, f12, f3);
            swc1(f12, t3, 4);
            lwc1(f12, t4, 8);
            add_s(f12, f12, f4);
            swc1(f12, t3, 8);
            lwc1(f12, t4, 0);
            t3 = addu(a0, t1);
            add_s(f12, f12, f5);
            swc1(f12, a2, 0);
            lwc1(f12, t4, 4);
            add_s(f12, f12, f6);
            swc1(f12, a2, 4);
            lwc1(f12, t4, 8);
            add_s(f12, f12, f1);
            swc1(f12, a2, 8);
            lwc1(f12, t4, 0);
            add_s(f12, f12, f7);
            swc1(f12, a1, 0);
            lwc1(f12, t4, 4);
            add_s(f12, f12, f8);
            swc1(f12, a1, 4);
            lwc1(f12, t4, 8);
            add_s(f12, f12, f0);
            swc1(f12, a1, 8);
            lwc1(f12, t4, 0);
            add_s(f12, f12, f9);
            swc1(f12, a0, 0);
            lwc1(f12, t4, 4);
            add_s(f12, f12, f10);
            swc1(f12, a0, 4);
            lwc1(f12, t4, 8);
            add_s(f12, f12, f11);
            t4 = addu(t4, t2);
            swc1(f12, a0, 8);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00486c78 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00486EC0 sub_486EC0 -- 360 bytes; leaf frame (no stack)
// sub_486EC0 [positions, size per particle]: the corner offsets per particle from its size {+28 pointer, +32 stride}
// (w, h); the camera vectors are re-read every particle.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: the hand version terminated the host on a random world.
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_486EC0(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::lwc1,
          hg::mtc1, hg::mul_s, hg::neg_s, hg::slt, hg::sub_s, hg::swc1;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, t8{ctx, 24};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12};
    // 0x00486ec0
    enter(ctx, 9);  // entry check point + this block's cycles
    lw(t7, t0, 4);
    at = slt(0, a3);
    lw(t4, t0, 8);
    lw(t6, t0, 28);
    lw(t3, t0, 32);
    lw(t5, a0, 0);
    lw(t2, a0, 4);
    t8 = 0;
    if (at != 0) {
        // 0x00486ee4
        charge(ctx, 2);
        v1 = 0x3F000000;
        mtc1(v1, f2);
        for (;;) {
            // 0x00486eec
            charge(ctx, 76);
            lwc1(f6, t6, 0);
            t1 = addu(t5, t2);
            lwc1(f4, t6, 4);
            t0 = addu(t1, t2);
            t8 = addiu(t8, 1);
            a0 = addu(t0, t2);
            lwc1(f5, a1, 0);
            v1 = slt(t8, a3);
            lwc1(f1, a1, 4);
            lwc1(f0, a1, 8);
            mul_s(f6, f2, f6);
            t6 = addu(t6, t3);
            mul_s(f8, f2, f4);
            lwc1(f3, a2, 0);
            mul_s(f12, f5, f6);
            lwc1(f7, a2, 4);
            mul_s(f1, f1, f6);
            mul_s(f0, f0, f6);
            lwc1(f6, a2, 8);
            mul_s(f11, f3, f8);
            neg_s(f5, f12);
            sub_s(f3, f5, f11);
            lwc1(f4, t7, 0);
            mul_s(f9, f6, f8);
            add_s(f3, f4, f3);
            swc1(f3, t5, 0);
            mul_s(f10, f7, f8);
            neg_s(f4, f1);
            sub_s(f3, f4, f10);
            lwc1(f6, t7, 4);
            add_s(f5, f5, f11);
            add_s(f4, f4, f10);
            add_s(f3, f6, f3);
            swc1(f3, t5, 4);
            neg_s(f3, f0);
            sub_s(f6, f3, f9);
            lwc1(f7, t7, 8);
            add_s(f3, f3, f9);
            add_s(f6, f7, f6);
            swc1(f6, t5, 8);
            lwc1(f8, t7, 0);
            t5 = addu(a0, t2);
            sub_s(f7, f12, f11);
            add_s(f6, f12, f11);
            add_s(f7, f8, f7);
            swc1(f7, t1, 0);
            sub_s(f7, f1, f10);
            lwc1(f8, t7, 4);
            add_s(f1, f1, f10);
            add_s(f7, f8, f7);
            swc1(f7, t1, 4);
            sub_s(f7, f0, f9);
            lwc1(f8, t7, 8);
            add_s(f0, f0, f9);
            add_s(f7, f8, f7);
            swc1(f7, t1, 8);
            lwc1(f7, t7, 0);
            add_s(f6, f7, f6);
            swc1(f6, t0, 0);
            lwc1(f6, t7, 4);
            add_s(f1, f6, f1);
            swc1(f1, t0, 4);
            lwc1(f1, t7, 8);
            add_s(f0, f1, f0);
            swc1(f0, t0, 8);
            lwc1(f0, t7, 0);
            add_s(f0, f0, f5);
            swc1(f0, a0, 0);
            lwc1(f0, t7, 4);
            add_s(f0, f0, f4);
            swc1(f0, a0, 4);
            lwc1(f0, t7, 8);
            add_s(f0, f0, f3);
            t7 = addu(t7, t4);
            swc1(f0, a0, 8);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0048701c
        charge(ctx, 1);
    }
    // 0x00487020 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00487520 sub_487520 -- 464 bytes; leaf frame (no stack)
// sub_487520 [positions, size per particle, pivot]: as sub_486EC0, every corner also offset by the pivot
// px * right + py * up (computed once, $f6..$f8): vertex = (p + pivot) + corner.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: the hand version terminated the host on a random world.
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_487520(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::lwc1,
          hg::madd_s, hg::mtc1, hg::mul_s, hg::mula_s, hg::neg_s, hg::slt, hg::sub_s, hg::swc1;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, t8{ctx, 24};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x00487520
    enter(ctx, 23);  // entry check point + this block's cycles
    lwc1(f9, t0, 108);
    lw(t7, t0, 4);
    lwc1(f4, a2, 0);
    lw(t4, t0, 8);
    lwc1(f8, t0, 104);
    lw(t6, t0, 28);
    lwc1(f5, a1, 0);
    lw(t3, t0, 32);
    lwc1(f2, a2, 4);
    lw(t5, a0, 0);
    lwc1(f3, a1, 4);
    lw(t2, a0, 4);
    lwc1(f0, a2, 8);
    at = slt(0, a3);
    mula_s(f9, f4);
    t8 = 0;
    lwc1(f1, a1, 8);
    madd_s(f6, f8, f5);
    mula_s(f9, f2);
    madd_s(f7, f8, f3);
    mula_s(f9, f0);
    madd_s(f8, f8, f1);
    if (at != 0) {
        // 0x0048757c
        charge(ctx, 2);
        v1 = 0x3F000000;
        mtc1(v1, f5);
        for (;;) {
            // 0x00487584
            charge(ctx, 88);
            lwc1(f1, t6, 4);
            t1 = addu(t5, t2);
            lwc1(f9, t6, 0);
            t0 = addu(t1, t2);
            lwc1(f10, t7, 0);
            t8 = addiu(t8, 1);
            lwc1(f0, a2, 0);
            a0 = addu(t0, t2);
            lwc1(f4, a1, 0);
            v1 = slt(t8, a3);
            lwc1(f3, a1, 4);
            mul_s(f12, f5, f1);
            t6 = addu(t6, t3);
            mul_s(f9, f5, f9);
            lwc1(f2, a1, 8);
            mul_s(f14, f0, f12);
            mul_s(f4, f4, f9);
            lwc1(f1, a2, 4);
            lwc1(f0, a2, 8);
            mul_s(f3, f3, f9);
            mul_s(f2, f2, f9);
            neg_s(f11, f4);
            sub_s(f9, f11, f14);
            add_s(f10, f10, f6);
            add_s(f9, f10, f9);
            mul_s(f1, f1, f12);
            mul_s(f0, f0, f12);
            swc1(f9, t5, 0);
            lwc1(f12, t7, 4);
            neg_s(f10, f3);
            sub_s(f9, f10, f1);
            add_s(f12, f12, f7);
            add_s(f9, f12, f9);
            swc1(f9, t5, 4);
            lwc1(f13, t7, 8);
            neg_s(f9, f2);
            sub_s(f12, f9, f0);
            add_s(f13, f13, f8);
            add_s(f12, f13, f12);
            swc1(f12, t5, 8);
            lwc1(f13, t7, 0);
            t5 = addu(a0, t2);
            sub_s(f12, f4, f14);
            add_s(f10, f10, f1);
            add_s(f13, f13, f6);
            add_s(f12, f13, f12);
            swc1(f12, t1, 0);
            sub_s(f12, f3, f1);
            lwc1(f13, t7, 4);
            add_s(f1, f3, f1);
            add_s(f9, f9, f0);
            add_s(f3, f13, f7);
            add_s(f3, f3, f12);
            swc1(f3, t1, 4);
            sub_s(f3, f2, f0);
            lwc1(f12, t7, 8);
            add_s(f0, f2, f0);
            add_s(f4, f4, f14);
            add_s(f2, f12, f8);
            add_s(f2, f2, f3);
            swc1(f2, t1, 8);
            lwc1(f2, t7, 0);
            add_s(f11, f11, f14);
            add_s(f2, f2, f6);
            add_s(f2, f2, f4);
            swc1(f2, t0, 0);
            lwc1(f2, t7, 4);
            add_s(f2, f2, f7);
            add_s(f1, f2, f1);
            swc1(f1, t0, 4);
            lwc1(f1, t7, 8);
            add_s(f1, f1, f8);
            add_s(f0, f1, f0);
            swc1(f0, t0, 8);
            lwc1(f0, t7, 0);
            add_s(f0, f0, f6);
            add_s(f0, f0, f11);
            swc1(f0, a0, 0);
            lwc1(f0, t7, 4);
            add_s(f0, f0, f7);
            add_s(f0, f0, f10);
            swc1(f0, a0, 4);
            lwc1(f0, t7, 8);
            add_s(f0, f0, f8);
            t7 = addu(t7, t4);
            add_s(f0, f0, f9);
            swc1(f0, a0, 8);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004876e4
        charge(ctx, 1);
    }
    // 0x004876e8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00487990 sub_487990 -- 296 bytes; leaf frame (no stack)
// sub_487990 [matrix per particle]: each particle has a 64-byte matrix {+12 pointer, +16 stride} (rows right, up,
// at, pos); r = right/2, u = up/2 and v0 = pos + (r - u), v1 = pos - (r + u), v2 = pos - (r - u), v3 = pos + (r + u).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: the hand version terminated the host on a random world.
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_487990(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::lwc1,
          hg::mtc1, hg::mul_s, hg::slt, hg::sub_s, hg::swc1;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8};
    // 0x00487990
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(t4, a0, 0);
    at = slt(0, a3);
    lw(t2, a0, 4);
    lw(t3, t0, 12);
    lw(t1, t0, 16);
    t5 = 0;
    if (at != 0) {
        // 0x004879ac
        charge(ctx, 2);
        v1 = 0x3F000000;
        mtc1(v1, f0);
        for (;;) {
            // 0x004879b4
            charge(ctx, 63);
            lwc1(f6, t3, 0);
            a2 = addu(t4, t2);
            lwc1(f4, t3, 8);
            a1 = addu(a2, t2);
            lwc1(f3, t3, 16);
            t5 = addiu(t5, 1);
            lwc1(f5, t3, 4);
            t0 = addiu(t3, 48);
            lwc1(f2, t3, 20);
            a0 = addu(a1, t2);
            lwc1(f1, t3, 24);
            v1 = slt(t5, a3);
            mul_s(f6, f0, f6);
            mul_s(f3, f0, f3);
            t3 = addu(t3, t1);
            mul_s(f8, f0, f4);
            mul_s(f5, f0, f5);
            mul_s(f2, f0, f2);
            add_s(f7, f6, f3);
            sub_s(f4, f6, f3);
            mul_s(f1, f0, f1);
            add_s(f6, f5, f2);
            sub_s(f3, f5, f2);
            add_s(f5, f8, f1);
            sub_s(f2, f8, f1);
            lwc1(f1, t0, 0);
            add_s(f1, f1, f4);
            swc1(f1, t4, 0);
            lwc1(f1, t0, 4);
            add_s(f1, f1, f3);
            swc1(f1, t4, 4);
            lwc1(f1, t0, 8);
            add_s(f1, f1, f2);
            swc1(f1, t4, 8);
            lwc1(f1, t0, 0);
            t4 = addu(a0, t2);
            sub_s(f1, f1, f7);
            swc1(f1, a2, 0);
            lwc1(f1, t0, 4);
            sub_s(f1, f1, f6);
            swc1(f1, a2, 4);
            lwc1(f1, t0, 8);
            sub_s(f1, f1, f5);
            swc1(f1, a2, 8);
            lwc1(f1, t0, 0);
            sub_s(f1, f1, f4);
            swc1(f1, a1, 0);
            lwc1(f1, t0, 4);
            sub_s(f1, f1, f3);
            swc1(f1, a1, 4);
            lwc1(f1, t0, 8);
            sub_s(f1, f1, f2);
            swc1(f1, a1, 8);
            lwc1(f1, t0, 0);
            add_s(f1, f1, f7);
            swc1(f1, a0, 0);
            lwc1(f1, t0, 4);
            add_s(f1, f1, f6);
            swc1(f1, a0, 4);
            lwc1(f1, t0, 8);
            add_s(f1, f1, f5);
            swc1(f1, a0, 8);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00487ab0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00487AC0 sub_487AC0 -- 304 bytes; leaf frame (no stack)
// sub_487AC0 [matrix per particle, pivot]: as sub_487990, the centre moved by the pivot (+104, +108):
// c = pos + px * right + py * up (ACC chains), then the corners from c.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: the hand version terminated the host on a random world.
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_487AC0(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::add_s, hg::adda_s, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lw,
          hg::lwc1, hg::madd_s, hg::madda_s, hg::mtc1, hg::mul_s, hg::slt, hg::sub_s, hg::swc1;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16}, f17{ctx, 17};
    // 0x00487ac0
    enter(ctx, 9);  // entry check point + this block's cycles
    lwc1(f2, t0, 104);
    lw(t2, t0, 12);
    lwc1(f1, t0, 108);
    lw(t3, a0, 0);
    lw(t1, a0, 4);
    at = slt(0, a3);
    lw(t0, t0, 16);
    t4 = 0;
    if (at != 0) {
        // 0x00487ae4
        charge(ctx, 3);
        v1 = 0x3F000000;
        mtc1(v1, f0);
        mtc1(zero, f12);
        for (;;) {
            // 0x00487af0
            charge(ctx, 62);
            lwc1(f3, t2, 48);
            a2 = addu(t3, t1);
            lwc1(f6, t2, 16);
            a1 = addu(a2, t1);
            lwc1(f5, t2, 0);
            t4 = addiu(t4, 1);
            lwc1(f16, t2, 20);
            a0 = addu(a1, t1);
            lwc1(f10, t2, 4);
            v1 = slt(t4, a3);
            lwc1(f14, t2, 24);
            adda_s(f12, f3);
            lwc1(f9, t2, 8);
            sub_s(f3, f5, f6);
            mul_s(f8, f0, f3);
            add_s(f3, f10, f16);
            mul_s(f15, f0, f3);
            add_s(f3, f9, f14);
            mul_s(f13, f0, f3);
            sub_s(f3, f10, f16);
            mul_s(f7, f0, f3);
            add_s(f4, f5, f6);
            madda_s(f5, f2);
            mul_s(f17, f0, f4);
            sub_s(f3, f9, f14);
            madd_s(f11, f6, f1);
            mul_s(f6, f0, f3);
            lwc1(f5, t2, 52);
            lwc1(f4, t2, 56);
            add_s(f3, f11, f8);
            adda_s(f12, f5);
            madda_s(f10, f2);
            t2 = addu(t2, t0);
            madd_s(f10, f16, f1);
            adda_s(f12, f4);
            swc1(f3, t3, 0);
            add_s(f3, f10, f7);
            madda_s(f9, f2);
            madd_s(f9, f14, f1);
            swc1(f3, t3, 4);
            add_s(f3, f9, f6);
            swc1(f3, t3, 8);
            sub_s(f3, f11, f17);
            t3 = addu(a0, t1);
            swc1(f3, a2, 0);
            sub_s(f3, f10, f15);
            swc1(f3, a2, 4);
            sub_s(f3, f9, f13);
            swc1(f3, a2, 8);
            sub_s(f8, f11, f8);
            sub_s(f7, f10, f7);
            swc1(f8, a1, 0);
            sub_s(f6, f9, f6);
            swc1(f7, a1, 4);
            add_s(f5, f11, f17);
            swc1(f6, a1, 8);
            add_s(f4, f10, f15);
            swc1(f5, a0, 0);
            add_s(f3, f9, f13);
            swc1(f4, a0, 4);
            swc1(f3, a0, 8);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00487be8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00488260 sub_488260 -- 144 bytes; leaf frame (no stack)
// sub_488260 [UV rectangle per particle]: {+60 pointer, +64 stride} rectangles {u0, v0, u1, v1}; vertices (u0, v1),
// (u1, v1), (u1, v0), (u0, v0).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: the hand version terminated the host on a random world.
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_488260(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::lwc1, hg::slt,
          hg::swc1;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14};
    Fpr f0{ctx, 0};
    // 0x00488260
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(t5, a0, 0);
    at = slt(0, a1);
    lw(t2, a0, 4);
    lw(t4, a2, 60);
    lw(t1, a2, 64);
    t6 = 0;
    if (at != 0) {
        for (;;) {
            // 0x0048827c
            charge(ctx, 26);
            t3 = t4;
            t0 = addiu(t4, 8);
            lwc1(f0, t3, 0);
            a3 = addu(t5, t2);
            a2 = addu(a3, t2);
            t6 = addiu(t6, 1);
            a0 = addu(a2, t2);
            v1 = slt(t6, a1);
            t4 = addu(t4, t1);
            swc1(f0, t5, 0);
            lwc1(f0, t0, 4);
            swc1(f0, t5, 4);
            lwc1(f0, t0, 0);
            t5 = addu(a0, t2);
            swc1(f0, a3, 0);
            lwc1(f0, t0, 4);
            swc1(f0, a3, 4);
            lwc1(f0, t0, 0);
            swc1(f0, a2, 0);
            lwc1(f0, t3, 4);
            swc1(f0, a2, 4);
            lwc1(f0, t3, 0);
            swc1(f0, a0, 0);
            lwc1(f0, t3, 4);
            swc1(f0, a0, 4);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004882e4
        charge(ctx, 1);
    }
    // 0x004882e8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x004882F0 sub_4882F0 -- 152 bytes; leaf frame (no stack)
// sub_4882F0 [UV quad per particle].
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: the hand version terminated the host on a random world.
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_4882F0(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::lwc1, hg::slt,
          hg::swc1;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, t8{ctx, 24};
    Fpr f0{ctx, 0};
    // 0x004882f0
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(t7, a0, 0);
    at = slt(0, a1);
    lw(t4, a0, 4);
    lw(t6, a2, 68);
    lw(t3, a2, 72);
    t8 = 0;
    if (at != 0) {
        for (;;) {
            // 0x0048830c
            charge(ctx, 28);
            t5 = t6;
            a3 = addu(t7, t4);
            lwc1(f0, t5, 0);
            a2 = addu(a3, t4);
            t8 = addiu(t8, 1);
            t2 = addiu(t6, 8);
            t1 = addiu(t6, 16);
            t0 = addiu(t6, 24);
            a0 = addu(a2, t4);
            v1 = slt(t8, a1);
            t6 = addu(t6, t3);
            swc1(f0, t7, 0);
            lwc1(f0, t5, 4);
            swc1(f0, t7, 4);
            lwc1(f0, t2, 0);
            t7 = addu(a0, t4);
            swc1(f0, a3, 0);
            lwc1(f0, t2, 4);
            swc1(f0, a3, 4);
            lwc1(f0, t1, 0);
            swc1(f0, a2, 0);
            lwc1(f0, t1, 4);
            swc1(f0, a2, 4);
            lwc1(f0, t0, 0);
            swc1(f0, a0, 0);
            lwc1(f0, t0, 4);
            swc1(f0, a0, 4);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0048837c
        charge(ctx, 1);
    }
    // 0x00488380 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00488390 sub_488390 -- 128 bytes; leaf frame (no stack)
// sub_488390 [constant UV rectangle]: the rectangle at +144 {u0, v0, u1, v1}, laid out as sub_488260.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: the hand version terminated the host on a random world.
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_488390(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::lwc1, hg::slt,
          hg::swc1;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12};
    Fpr f0{ctx, 0};
    // 0x00488390
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(t3, a0, 0);
    at = slt(0, a1);
    lw(t0, a0, 4);
    t2 = addiu(a2, 144);
    t1 = addiu(a2, 152);
    t4 = 0;
    if (at != 0) {
        for (;;) {
            // 0x004883ac
            charge(ctx, 23);
            lwc1(f0, t2, 0);
            a3 = addu(t3, t0);
            a2 = addu(a3, t0);
            t4 = addiu(t4, 1);
            a0 = addu(a2, t0);
            v1 = slt(t4, a1);
            swc1(f0, t3, 0);
            lwc1(f0, t1, 4);
            swc1(f0, t3, 4);
            lwc1(f0, t1, 0);
            t3 = addu(a0, t0);
            swc1(f0, a3, 0);
            lwc1(f0, t1, 4);
            swc1(f0, a3, 4);
            lwc1(f0, t1, 0);
            swc1(f0, a2, 0);
            lwc1(f0, t2, 4);
            swc1(f0, a2, 4);
            lwc1(f0, t2, 0);
            swc1(f0, a0, 0);
            lwc1(f0, t2, 4);
            swc1(f0, a0, 4);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00488408 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00488410 sub_488410 -- 136 bytes; leaf frame (no stack)
// sub_488410 [constant UV quad]: vertex k = the pair at +144 + 8k.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: the hand version terminated the host on a random world.
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_488410(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::lwc1, hg::slt,
          hg::swc1;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14};
    Fpr f0{ctx, 0};
    // 0x00488410
    enter(ctx, 9);  // entry check point + this block's cycles
    lw(t5, a0, 0);
    at = slt(0, a1);
    lw(t1, a0, 4);
    t0 = addiu(a2, 144);
    t4 = addiu(a2, 152);
    t3 = addiu(a2, 160);
    t2 = addiu(a2, 168);
    t6 = 0;
    if (at != 0) {
        for (;;) {
            // 0x00488434
            charge(ctx, 23);
            lwc1(f0, t0, 0);
            a3 = addu(t5, t1);
            a2 = addu(a3, t1);
            t6 = addiu(t6, 1);
            a0 = addu(a2, t1);
            v1 = slt(t6, a1);
            swc1(f0, t5, 0);
            lwc1(f0, t0, 4);
            swc1(f0, t5, 4);
            lwc1(f0, t4, 0);
            t5 = addu(a0, t1);
            swc1(f0, a3, 0);
            lwc1(f0, t4, 4);
            swc1(f0, a3, 4);
            lwc1(f0, t3, 0);
            swc1(f0, a2, 0);
            lwc1(f0, t3, 4);
            swc1(f0, a2, 4);
            lwc1(f0, t2, 0);
            swc1(f0, a0, 0);
            lwc1(f0, t2, 4);
            swc1(f0, a0, 4);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00488490 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00487E80 sub_487E80 -- 104 bytes; leaf frame (no stack)
// sub_487E80 [vertex colours per particle].
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: the hand version terminated the host on a random world.
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_487E80(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::slt, hg::sw;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14};
    // 0x00487e80
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(t4, a0, 0);
    at = slt(0, a1);
    lw(t2, a0, 4);
    lw(t3, a2, 44);
    lw(t1, a2, 48);
    t6 = 0;
    if (at != 0) {
        for (;;) {
            // 0x00487e9c
            charge(ctx, 17);
            t5 = t3;
            t0 = addu(t4, t2);
            lw(a0, t5, 0);
            a3 = addu(t0, t2);
            t6 = addiu(t6, 1);
            a2 = addu(a3, t2);
            v1 = slt(t6, a1);
            t3 = addu(t3, t1);
            sw(a0, t4, 0);
            lw(a0, t5, 4);
            t4 = addu(a2, t2);
            sw(a0, t0, 0);
            lw(a0, t5, 8);
            sw(a0, a3, 0);
            lw(a0, t5, 12);
            sw(a0, a2, 0);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00487ee0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00487EF0 sub_487EF0 -- 440 bytes; leaf frame (no stack)
// sub_487EF0 [constant vertex colours]: vertex k of every particle gets the word at +128 + 4k (the stride, $a0, steps
// from vertex to vertex): eight particles per iteration while count is in 9..0x7FFFFFFE (64-bit signed compares),
// then one by one.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: the hand version terminated the host on a random world.
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_487EF0(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::slt, hg::slti, hg::sw;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12};
    // 0x00487ef0
    enter(ctx, 9);  // entry check point + this block's cycles
    lw(t4, a0, 0);
    at = slt(0, a1);
    lw(t1, a2, 128);
    lw(t0, a2, 132);
    lw(a3, a2, 136);
    lw(a0, a0, 4);
    lw(a2, a2, 140);
    t2 = 0;
    if (at != 0) {
        // 0x00487f14
        charge(ctx, 3);
        at = slti(a1, 9);
        v1 = addiu(a1, -8);
        if (at == 0) {
            // 0x00487f20
            charge(ctx, 3);
            at = slt(a1, 0);
            t3 = 0;
            if (at == 0) {
                // 0x00487f2c
                charge(ctx, 5);
                at = 0x7FFF0000;
                at = at | 0xFFFF;
                at = slt(a1, at);
                if (at != 0) {
                    // 0x00487f40
                    charge(ctx, 1);
                    t3 = 1;
                }
            }
            // 0x00487f44
            charge(ctx, 2);
            if (t3 != 0) {
                for (;;) {
                    // 0x00487f4c
                    charge(ctx, 68);
                    sw(t1, t4, 0);
                    t3 = addu(t4, a0);
                    sw(t0, t3, 0);
                    t2 = addiu(t2, 8);
                    t3 = addu(t3, a0);
                    sw(a3, t3, 0);
                    t3 = addu(t3, a0);
                    sw(a2, t3, 0);
                    t3 = addu(t3, a0);
                    sw(t1, t3, 0);
                    t3 = addu(t3, a0);
                    sw(t0, t3, 0);
                    t3 = addu(t3, a0);
                    sw(a3, t3, 0);
                    t3 = addu(t3, a0);
                    sw(a2, t3, 0);
                    t3 = addu(t3, a0);
                    sw(t1, t3, 0);
                    t3 = addu(t3, a0);
                    sw(t0, t3, 0);
                    t3 = addu(t3, a0);
                    sw(a3, t3, 0);
                    t3 = addu(t3, a0);
                    sw(a2, t3, 0);
                    t3 = addu(t3, a0);
                    sw(t1, t3, 0);
                    t3 = addu(t3, a0);
                    sw(t0, t3, 0);
                    t3 = addu(t3, a0);
                    sw(a3, t3, 0);
                    t3 = addu(t3, a0);
                    sw(a2, t3, 0);
                    t3 = addu(t3, a0);
                    sw(t1, t3, 0);
                    t3 = addu(t3, a0);
                    sw(t0, t3, 0);
                    t3 = addu(t3, a0);
                    sw(a3, t3, 0);
                    t3 = addu(t3, a0);
                    sw(a2, t3, 0);
                    t3 = addu(t3, a0);
                    sw(t1, t3, 0);
                    t3 = addu(t3, a0);
                    sw(t0, t3, 0);
                    t3 = addu(t3, a0);
                    sw(a3, t3, 0);
                    t3 = addu(t3, a0);
                    sw(a2, t3, 0);
                    t3 = addu(t3, a0);
                    sw(t1, t3, 0);
                    t3 = addu(t3, a0);
                    sw(t0, t3, 0);
                    t3 = addu(t3, a0);
                    sw(a3, t3, 0);
                    t3 = addu(t3, a0);
                    sw(a2, t3, 0);
                    t3 = addu(t3, a0);
                    sw(t1, t3, 0);
                    t3 = addu(t3, a0);
                    sw(t0, t3, 0);
                    t3 = addu(t3, a0);
                    sw(a3, t3, 0);
                    t3 = addu(t3, a0);
                    sw(a2, t3, 0);
                    t4 = addu(t3, a0);
                    t3 = slt(t2, v1);
                    if (t3 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0048805c
                charge(ctx, 1);
            }
        }
        // 0x00488060
        charge(ctx, 3);
        at = slt(t2, a1);
        if (at != 0) {
            for (;;) {
                // 0x0048806c
                charge(ctx, 12);
                sw(t1, t4, 0);
                v1 = addu(t4, a0);
                sw(t0, v1, 0);
                t2 = addiu(t2, 1);
                v1 = addu(v1, a0);
                sw(a3, v1, 0);
                v1 = addu(v1, a0);
                sw(a2, v1, 0);
                t4 = addu(v1, a0);
                v1 = slt(t2, a1);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0048809c
            charge(ctx, 1);
        }
    }
    // 0x004880a0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x004880B0 sub_4880B0 -- 424 bytes; leaf frame (no stack)
// sub_4880B0 [constant colour]: the colour word at +124 into every vertex (the stride steps), unrolled as
// sub_487EF0 (the unrolled loop's exit has no extra block here).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: the hand version terminated the host on a random world.
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_4880B0(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::slt, hg::slti, hg::sw;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x004880b0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(t1, a0, 0);
    at = slt(0, a1);
    lw(a2, a2, 124);
    lw(a0, a0, 4);
    a3 = 0;
    if (at != 0) {
        // 0x004880c8
        charge(ctx, 3);
        at = slti(a1, 9);
        v1 = addiu(a1, -8);
        if (at == 0) {
            // 0x004880d4
            charge(ctx, 3);
            at = slt(a1, 0);
            t0 = 0;
            if (at == 0) {
                // 0x004880e0
                charge(ctx, 5);
                at = 0x7FFF0000;
                at = at | 0xFFFF;
                at = slt(a1, at);
                if (at != 0) {
                    // 0x004880f4
                    charge(ctx, 1);
                    t0 = 1;
                }
            }
            // 0x004880f8
            charge(ctx, 2);
            if (t0 != 0) {
                for (;;) {
                    // 0x00488100
                    charge(ctx, 68);
                    sw(a2, t1, 0);
                    t0 = addu(t1, a0);
                    sw(a2, t0, 0);
                    a3 = addiu(a3, 8);
                    t0 = addu(t0, a0);
                    sw(a2, t0, 0);
                    t0 = addu(t0, a0);
                    sw(a2, t0, 0);
                    t0 = addu(t0, a0);
                    sw(a2, t0, 0);
                    t0 = addu(t0, a0);
                    sw(a2, t0, 0);
                    t0 = addu(t0, a0);
                    sw(a2, t0, 0);
                    t0 = addu(t0, a0);
                    sw(a2, t0, 0);
                    t0 = addu(t0, a0);
                    sw(a2, t0, 0);
                    t0 = addu(t0, a0);
                    sw(a2, t0, 0);
                    t0 = addu(t0, a0);
                    sw(a2, t0, 0);
                    t0 = addu(t0, a0);
                    sw(a2, t0, 0);
                    t0 = addu(t0, a0);
                    sw(a2, t0, 0);
                    t0 = addu(t0, a0);
                    sw(a2, t0, 0);
                    t0 = addu(t0, a0);
                    sw(a2, t0, 0);
                    t0 = addu(t0, a0);
                    sw(a2, t0, 0);
                    t0 = addu(t0, a0);
                    sw(a2, t0, 0);
                    t0 = addu(t0, a0);
                    sw(a2, t0, 0);
                    t0 = addu(t0, a0);
                    sw(a2, t0, 0);
                    t0 = addu(t0, a0);
                    sw(a2, t0, 0);
                    t0 = addu(t0, a0);
                    sw(a2, t0, 0);
                    t0 = addu(t0, a0);
                    sw(a2, t0, 0);
                    t0 = addu(t0, a0);
                    sw(a2, t0, 0);
                    t0 = addu(t0, a0);
                    sw(a2, t0, 0);
                    t0 = addu(t0, a0);
                    sw(a2, t0, 0);
                    t0 = addu(t0, a0);
                    sw(a2, t0, 0);
                    t0 = addu(t0, a0);
                    sw(a2, t0, 0);
                    t0 = addu(t0, a0);
                    sw(a2, t0, 0);
                    t0 = addu(t0, a0);
                    sw(a2, t0, 0);
                    t0 = addu(t0, a0);
                    sw(a2, t0, 0);
                    t0 = addu(t0, a0);
                    sw(a2, t0, 0);
                    t0 = addu(t0, a0);
                    sw(a2, t0, 0);
                    t1 = addu(t0, a0);
                    t0 = slt(a3, v1);
                    if (t0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
        // 0x00488210
        charge(ctx, 3);
        at = slt(a3, a1);
        if (at != 0) {
            for (;;) {
                // 0x0048821c
                charge(ctx, 12);
                sw(a2, t1, 0);
                v1 = addu(t1, a0);
                sw(a2, v1, 0);
                a3 = addiu(a3, 1);
                v1 = addu(v1, a0);
                sw(a2, v1, 0);
                v1 = addu(v1, a0);
                sw(a2, v1, 0);
                t1 = addu(v1, a0);
                v1 = slt(a3, a1);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0048824c
            charge(ctx, 1);
        }
    }
    // 0x00488250 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x004884A0 sub_4884A0 -- 168 bytes; leaf frame (no stack)
// The loop (sub_4884A0 and sub_486100 are two copies of one body): $t3 dst, $t1 vertex stride, $t2 source, $t0 its
// stride, $t4 the counter, $a1 the count.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: the hand version terminated the host on a random world.
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_4884A0(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::lwc1, hg::slt,
          hg::swc1;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12};
    Fpr f0{ctx, 0};
    // 0x004884a0
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(t3, a0, 0);
    at = slt(0, a1);
    lw(t1, a0, 4);
    lw(t2, a2, 20);
    lw(t0, a2, 24);
    t4 = 0;
    if (at != 0) {
        for (;;) {
            // 0x004884bc
            charge(ctx, 32);
            lwc1(f0, t2, 0);
            a3 = addu(t3, t1);
            a2 = addu(a3, t1);
            t4 = addiu(t4, 1);
            a0 = addu(a2, t1);
            v1 = slt(t4, a1);
            swc1(f0, t3, 0);
            lwc1(f0, t2, 4);
            swc1(f0, t3, 4);
            lwc1(f0, t2, 8);
            swc1(f0, t3, 8);
            lwc1(f0, t2, 0);
            t3 = addu(a0, t1);
            swc1(f0, a3, 0);
            lwc1(f0, t2, 4);
            swc1(f0, a3, 4);
            lwc1(f0, t2, 8);
            swc1(f0, a3, 8);
            lwc1(f0, t2, 0);
            swc1(f0, a2, 0);
            lwc1(f0, t2, 4);
            swc1(f0, a2, 4);
            lwc1(f0, t2, 8);
            swc1(f0, a2, 8);
            lwc1(f0, t2, 0);
            swc1(f0, a0, 0);
            lwc1(f0, t2, 4);
            swc1(f0, a0, 4);
            lwc1(f0, t2, 8);
            swc1(f0, a0, 8);
            t2 = addu(t2, t0);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0048853c
        charge(ctx, 1);
    }
    // 0x00488540 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00488B80 sub_488B80 -- 8 bytes; leaf frame (no stack)
// sub_488B80 [instance end]: releases the lock's resource entry (+24) through sub_4933D0, as a tail call ($ra stays the
// caller's).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_488B80(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::enter, hg::lw;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x00488b80
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(a0, a1, 24);
    gen::fn_sub_4933D0_004933d0(ctx);  // tail call
}

// 0x00486100 sub_486100 -- 168 bytes; leaf frame (no stack)
// The loop (sub_4884A0 and sub_486100 are two copies of one body): $t3 dst, $t1 vertex stride, $t2 source, $t0 its
// stride, $t4 the counter, $a1 the count.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: the hand version terminated the host on a random world.
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_486100(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::lwc1, hg::slt,
          hg::swc1;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12};
    Fpr f0{ctx, 0};
    // 0x00486100
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(t3, a0, 0);
    at = slt(0, a1);
    lw(t1, a0, 4);
    lw(t2, a2, 20);
    lw(t0, a2, 24);
    t4 = 0;
    if (at != 0) {
        for (;;) {
            // 0x0048611c
            charge(ctx, 32);
            lwc1(f0, t2, 0);
            a3 = addu(t3, t1);
            a2 = addu(a3, t1);
            t4 = addiu(t4, 1);
            a0 = addu(a2, t1);
            v1 = slt(t4, a1);
            swc1(f0, t3, 0);
            lwc1(f0, t2, 4);
            swc1(f0, t3, 4);
            lwc1(f0, t2, 8);
            swc1(f0, t3, 8);
            lwc1(f0, t2, 0);
            t3 = addu(a0, t1);
            swc1(f0, a3, 0);
            lwc1(f0, t2, 4);
            swc1(f0, a3, 4);
            lwc1(f0, t2, 8);
            swc1(f0, a3, 8);
            lwc1(f0, t2, 0);
            swc1(f0, a2, 0);
            lwc1(f0, t2, 4);
            swc1(f0, a2, 4);
            lwc1(f0, t2, 8);
            swc1(f0, a2, 8);
            lwc1(f0, t2, 0);
            swc1(f0, a0, 0);
            lwc1(f0, t2, 4);
            swc1(f0, a0, 4);
            lwc1(f0, t2, 8);
            swc1(f0, a0, 8);
            t2 = addu(t2, t0);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0048619c
        charge(ctx, 1);
    }
    // 0x004861a0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00485070 sub_485070 -- 156 bytes; frame 0x10: ra sp+0x0
// sub_485070 [vertex colours per particle]: {+44 pointer, +48 stride}.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: the hand version terminated the host on a random world.
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_485070(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lw, hg::mult,
          hg::sd, hg::sll, hg::slt, hg::sw;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00485070
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(t2, a0, 4);
    lw(t1, a2, 48);
    lw(t3, a2, 44);
    v1 = sll(t2, 2);
    lw(t4, a0, 0);
    if (t1 == v1) {
        // 0x004850e8
        charge(ctx, 7);
        mult(v0, a1, t2);
        a0 = t4;
        a2 = sll(v0, 2);
        a1 = t3;
        jal(ctx, 0x4850F4u, gen::fn_sub_476C20_00476c20);
        backedge(ctx);
    } else {
        // 0x00485090
        charge(ctx, 3);
        at = slt(0, a1);
        t6 = 0;
        if (at != 0) {
            for (;;) {
                // 0x0048509c
                charge(ctx, 17);
                t5 = t3;
                t0 = addu(t4, t2);
                lw(a0, t5, 0);
                a3 = addu(t0, t2);
                t6 = addiu(t6, 1);
                a2 = addu(a3, t2);
                v1 = slt(t6, a1);
                t3 = addu(t3, t1);
                sw(a0, t4, 0);
                lw(a0, t5, 4);
                t4 = addu(a2, t2);
                sw(a0, t0, 0);
                lw(a0, t5, 8);
                sw(a0, a3, 0);
                lw(a0, t5, 12);
                sw(a0, a2, 0);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
    }
    // 0x004850e0
    charge(ctx, 2);
    ld(ra, sp, 0x0);
    // 0x00485104
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x00485E20 sub_485E20 -- 204 bytes; frame 0x10: ra sp+0x0
// sub_485E20 [UV quad per particle]: {+68 pointer, +72 stride}.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: the hand version terminated the host on a random world.
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_485E20(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lw,
          hg::lwc1, hg::mult, hg::sd, hg::sll, hg::slt, hg::swc1;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, t8{ctx, 24}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x00485e20
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(t4, a0, 4);
    lw(t3, a2, 72);
    lw(t6, a2, 68);
    v1 = sll(t4, 2);
    lw(t7, a0, 0);
    if (t3 == v1) {
        // 0x00485ec8
        charge(ctx, 7);
        mult(v0, a1, t4);
        a0 = t7;
        a2 = sll(v0, 2);
        a1 = t6;
        jal(ctx, 0x485ED4u, gen::fn_sub_476C20_00476c20);
        backedge(ctx);
    } else {
        // 0x00485e40
        charge(ctx, 3);
        at = slt(0, a1);
        t8 = 0;
        if (at != 0) {
            for (;;) {
                // 0x00485e4c
                charge(ctx, 28);
                t5 = t6;
                a3 = addu(t7, t4);
                lwc1(f0, t5, 0);
                a2 = addu(a3, t4);
                t8 = addiu(t8, 1);
                t2 = addiu(t6, 8);
                t1 = addiu(t6, 16);
                t0 = addiu(t6, 24);
                a0 = addu(a2, t4);
                v1 = slt(t8, a1);
                t6 = addu(t6, t3);
                swc1(f0, t7, 0);
                lwc1(f0, t5, 4);
                swc1(f0, t7, 4);
                lwc1(f0, t2, 0);
                t7 = addu(a0, t4);
                swc1(f0, a3, 0);
                lwc1(f0, t2, 4);
                swc1(f0, a3, 4);
                lwc1(f0, t1, 0);
                swc1(f0, a2, 0);
                lwc1(f0, t1, 4);
                swc1(f0, a2, 4);
                lwc1(f0, t0, 0);
                swc1(f0, a0, 0);
                lwc1(f0, t0, 4);
                swc1(f0, a0, 4);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00485ebc
            charge(ctx, 1);
        }
    }
    // 0x00485ec0
    charge(ctx, 2);
    ld(ra, sp, 0x0);
    // 0x00485ee4
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x00486C80 sub_486C80 -- 568 bytes; frame 0xC0: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// sub_486C80 [positions, rotation, constant size]: w/2, h/2 (+112, +116) in $f22 / $f21; the corners as sub_486980.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_486C80(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::enter, hg::jal,
          hg::ld, hg::link, hg::lq, hg::lw, hg::lwc1, hg::madd_s, hg::mov_s, hg::mtc1, hg::mul_s, hg::mula_s,
          hg::neg_s, hg::sd, hg::slt, hg::sq, hg::sub_s, hg::swc1;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x00486c80
    enter(ctx, 33);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    v1 = 0x3F000000;
    sd(ra, sp, 0xA0);
    mtc1(v1, f2);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    s7 = a3;
    sq(s5, sp, 0x60);
    s6 = 0;
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    s1 = a1;
    swc1(f22, sp, 0x8);
    s0 = a2;
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lwc1(f1, t0, 112);
    lw(v1, t0, 56);
    lwc1(f0, t0, 116);
    lw(s5, t0, 4);
    lw(fp, t0, 8);
    lw(s4, t0, 52);
    lw(s3, a0, 0);
    lw(s2, a0, 4);
    mul_s(f22, f2, f1);
    sq(v1, sp, 0xB0);
    v1 = slt(0, s7);
    mul_s(f21, f2, f0);
    if (v1 != 0) {
        for (;;) {
            // 0x00486d0c
            charge(ctx, 91);
            link(ctx, 0x486D0Cu);  // $ra first: the delay slot below depends on it
            lwc1(f12, s4, 0);
            call(ctx, gen::fn_sinf_0052e878);
            lwc1(f12, s4, 0);
            mov_s(f20, f0);
            jal(ctx, 0x486D18u, gen::fn_cosf_0052e6d8);
            lwc1(f9, s0, 0);
            a2 = addu(s3, s2);
            lwc1(f2, s1, 0);
            a1 = addu(a2, s2);
            neg_s(f3, f20);
            lq(v1, sp, 0xB0);
            lwc1(f8, s0, 4);
            a0 = addu(a1, s2);
            lwc1(f7, s1, 4);
            s6 = addiu(s6, 1);
            lwc1(f5, s0, 8);
            mula_s(f3, f9);
            madd_s(f1, f0, f2);
            mul_s(f6, f1, f22);
            s4 = addu(s4, v1);
            v1 = slt(s6, s7);
            mula_s(f3, f8);
            madd_s(f1, f0, f7);
            lwc1(f4, s1, 8);
            mula_s(f3, f5);
            mul_s(f10, f1, f22);
            madd_s(f3, f0, f4);
            mula_s(f0, f9);
            madd_s(f2, f20, f2);
            mula_s(f0, f8);
            madd_s(f1, f20, f7);
            mula_s(f0, f5);
            mul_s(f7, f1, f21);
            madd_s(f0, f20, f4);
            mul_s(f5, f2, f21);
            mul_s(f8, f0, f21);
            neg_s(f2, f6);
            sub_s(f0, f2, f5);
            lwc1(f1, s5, 0);
            mul_s(f9, f3, f22);
            add_s(f0, f1, f0);
            swc1(f0, s3, 0);
            neg_s(f1, f10);
            sub_s(f0, f1, f7);
            lwc1(f3, s5, 4);
            add_s(f2, f2, f5);
            add_s(f1, f1, f7);
            add_s(f0, f3, f0);
            swc1(f0, s3, 4);
            neg_s(f0, f9);
            sub_s(f3, f0, f8);
            lwc1(f4, s5, 8);
            add_s(f0, f0, f8);
            add_s(f3, f4, f3);
            swc1(f3, s3, 8);
            sub_s(f3, f6, f5);
            s3 = addu(a0, s2);
            lwc1(f4, s5, 0);
            add_s(f5, f6, f5);
            add_s(f3, f4, f3);
            swc1(f3, a2, 0);
            lwc1(f6, s5, 4);
            sub_s(f3, f10, f7);
            add_s(f4, f10, f7);
            add_s(f3, f6, f3);
            swc1(f3, a2, 4);
            lwc1(f7, s5, 8);
            sub_s(f6, f9, f8);
            add_s(f3, f9, f8);
            add_s(f6, f7, f6);
            swc1(f6, a2, 8);
            lwc1(f6, s5, 0);
            add_s(f5, f6, f5);
            swc1(f5, a1, 0);
            lwc1(f5, s5, 4);
            add_s(f4, f5, f4);
            swc1(f4, a1, 4);
            lwc1(f4, s5, 8);
            add_s(f3, f4, f3);
            swc1(f3, a1, 8);
            lwc1(f3, s5, 0);
            add_s(f2, f3, f2);
            swc1(f2, a0, 0);
            lwc1(f2, s5, 4);
            add_s(f1, f2, f1);
            swc1(f1, a0, 4);
            lwc1(f1, s5, 8);
            add_s(f0, f1, f0);
            s5 = addu(s5, fp);
            swc1(f0, a0, 8);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00486e78
        charge(ctx, 2);
        backedge(ctx);
    }
    // 0x00486d04
    charge(ctx, 2);
    ld(ra, sp, 0xA0);
    // 0x00486e80
    charge(ctx, 14);
    lwc1(f22, sp, 0x8);
    lq(fp, sp, 0x90);
    lwc1(f21, sp, 0x4);
    lq(s7, sp, 0x80);
    lwc1(f20, sp, 0x0);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0xC0);
}

// 0x00487030 sub_487030 -- 580 bytes; frame 0xE0: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// sub_487030 [positions, rotation, size per particle {+28, +32}].
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_487030(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::enter, hg::jal,
          hg::ld, hg::link, hg::lq, hg::lw, hg::lwc1, hg::madd_s, hg::mov_s, hg::mtc1, hg::mul_s, hg::mula_s,
          hg::neg_s, hg::sd, hg::slt, hg::sq, hg::sub_s, hg::swc1;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f20{ctx, 20};
    // 0x00487030
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
    sd(ra, sp, 0xA0);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    fp = a3;
    sq(s6, sp, 0x70);
    s7 = 0;
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    s2 = a1;
    sq(s0, sp, 0x10);
    a1 = slt(0, fp);
    swc1(f20, sp, 0x0);
    s1 = a2;
    lw(v1, t0, 8);
    lw(s0, t0, 4);
    lw(s6, t0, 52);
    lw(s5, t0, 28);
    lw(s4, a0, 0);
    lw(s3, a0, 4);
    sq(v1, sp, 0xD0);
    lw(v1, t0, 56);
    sq(v1, sp, 0xC0);
    lw(v1, t0, 32);
    sq(v1, sp, 0xB0);
    if (a1 != 0) {
        for (;;) {
            // 0x004870ac
            charge(ctx, 100);
            link(ctx, 0x4870ACu);  // $ra first: the delay slot below depends on it
            lwc1(f12, s6, 0);
            call(ctx, gen::fn_sinf_0052e878);
            lwc1(f12, s6, 0);
            mov_s(f20, f0);
            jal(ctx, 0x4870B8u, gen::fn_cosf_0052e6d8);
            lwc1(f11, s1, 0);
            lq(v1, sp, 0xC0);
            lwc1(f8, s2, 0);
            a3 = addu(s4, s3);
            lwc1(f7, s1, 4);
            a2 = addu(a3, s3);
            lwc1(f6, s2, 4);
            s7 = addiu(s7, 1);
            lwc1(f4, s1, 8);
            a1 = addu(a2, s3);
            neg_s(f1, f20);
            a0 = slt(s7, fp);
            mula_s(f1, f11);
            s6 = addu(s6, v1);
            madd_s(f10, f0, f8);
            v1 = 0x3F000000;
            mula_s(f1, f7);
            madd_s(f9, f0, f6);
            mula_s(f1, f4);
            lwc1(f3, s2, 8);
            lwc1(f1, s5, 0);
            mtc1(v1, f5);
            lq(v1, sp, 0xB0);
            madd_s(f2, f0, f3);
            mula_s(f0, f11);
            madd_s(f11, f20, f8);
            mula_s(f0, f7);
            madd_s(f7, f20, f6);
            mula_s(f0, f4);
            mul_s(f0, f5, f1);
            mul_s(f6, f10, f0);
            mul_s(f10, f9, f0);
            mul_s(f9, f2, f0);
            lwc1(f2, s5, 4);
            madd_s(f8, f20, f3);
            lwc1(f3, s0, 0);
            neg_s(f4, f6);
            neg_s(f1, f10);
            neg_s(f0, f9);
            mul_s(f2, f5, f2);
            s5 = addu(s5, v1);
            lq(v1, sp, 0xD0);
            mul_s(f5, f11, f2);
            mul_s(f7, f7, f2);
            mul_s(f8, f8, f2);
            sub_s(f2, f4, f5);
            add_s(f2, f3, f2);
            swc1(f2, s4, 0);
            add_s(f2, f4, f5);
            sub_s(f3, f1, f7);
            lwc1(f4, s0, 4);
            add_s(f1, f1, f7);
            add_s(f3, f4, f3);
            swc1(f3, s4, 4);
            sub_s(f3, f0, f8);
            lwc1(f4, s0, 8);
            add_s(f0, f0, f8);
            add_s(f3, f4, f3);
            swc1(f3, s4, 8);
            sub_s(f3, f6, f5);
            s4 = addu(a1, s3);
            lwc1(f4, s0, 0);
            add_s(f5, f6, f5);
            add_s(f3, f4, f3);
            swc1(f3, a3, 0);
            lwc1(f6, s0, 4);
            sub_s(f3, f10, f7);
            add_s(f4, f10, f7);
            add_s(f3, f6, f3);
            swc1(f3, a3, 4);
            lwc1(f7, s0, 8);
            sub_s(f6, f9, f8);
            add_s(f3, f9, f8);
            add_s(f6, f7, f6);
            swc1(f6, a3, 8);
            lwc1(f6, s0, 0);
            add_s(f5, f6, f5);
            swc1(f5, a2, 0);
            lwc1(f5, s0, 4);
            add_s(f4, f5, f4);
            swc1(f4, a2, 4);
            lwc1(f4, s0, 8);
            add_s(f3, f4, f3);
            swc1(f3, a2, 8);
            lwc1(f3, s0, 0);
            add_s(f2, f3, f2);
            swc1(f2, a1, 0);
            lwc1(f2, s0, 4);
            add_s(f1, f2, f1);
            swc1(f1, a1, 4);
            lwc1(f1, s0, 8);
            add_s(f0, f1, f0);
            s0 = addu(s0, v1);
            swc1(f0, a1, 8);
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0048723c
        charge(ctx, 2);
        backedge(ctx);
    }
    // 0x004870a4
    charge(ctx, 2);
    ld(ra, sp, 0xA0);
    // 0x00487244
    charge(ctx, 12);
    lwc1(f20, sp, 0x0);
    lq(fp, sp, 0x90);
    lq(s7, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0xE0);
}

// 0x00487280 sub_487280 -- 660 bytes; frame 0xD0: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// sub_487280 [positions, rotation, constant size, pivot]: the pivot px * r' + py * u' (unscaled axes) is added to the
// position, then the corners.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_487280(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::enter, hg::jal,
          hg::ld, hg::link, hg::lq, hg::lw, hg::lwc1, hg::madd_s, hg::mov_s, hg::mtc1, hg::mul_s, hg::mula_s,
          hg::neg_s, hg::sd, hg::slt, hg::sq, hg::sub_s, hg::swc1;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x00487280
    enter(ctx, 35);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    v1 = 0x3F000000;
    sd(ra, sp, 0xA0);
    mtc1(v1, f2);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    fp = a3;
    sq(s6, sp, 0x70);
    s7 = t0;
    sq(s5, sp, 0x60);
    s6 = 0;
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    s1 = a1;
    swc1(f22, sp, 0x8);
    s0 = a2;
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(v1, t0, 8);
    lwc1(f1, t0, 112);
    lwc1(f0, t0, 116);
    lw(s5, t0, 4);
    lw(s4, t0, 52);
    lw(s3, a0, 0);
    lw(s2, a0, 4);
    sq(v1, sp, 0xC0);
    mul_s(f22, f2, f1);
    lw(v1, t0, 56);
    sq(v1, sp, 0xB0);
    v1 = slt(0, fp);
    mul_s(f21, f2, f0);
    if (v1 != 0) {
        for (;;) {
            // 0x00487314
            charge(ctx, 112);
            link(ctx, 0x487314u);  // $ra first: the delay slot below depends on it
            lwc1(f12, s4, 0);
            call(ctx, gen::fn_sinf_0052e878);
            lwc1(f12, s4, 0);
            mov_s(f20, f0);
            jal(ctx, 0x487320u, gen::fn_cosf_0052e6d8);
            lwc1(f7, s0, 0);
            lq(v1, sp, 0xB0);
            lwc1(f3, s1, 0);
            s6 = addiu(s6, 1);
            lwc1(f6, s0, 4);
            a2 = addu(s3, s2);
            lwc1(f1, s1, 4);
            a0 = slt(s6, fp);
            lwc1(f5, s0, 8);
            neg_s(f2, f20);
            mula_s(f2, f7);
            s4 = addu(s4, v1);
            madd_s(f10, f0, f3);
            v1 = addu(a2, s2);
            mula_s(f2, f6);
            a1 = addu(v1, s2);
            madd_s(f9, f0, f1);
            mula_s(f2, f5);
            lwc1(f4, s1, 8);
            lwc1(f2, s7, 108);
            mul_s(f14, f10, f22);
            madd_s(f8, f0, f4);
            mula_s(f0, f7);
            madd_s(f3, f20, f3);
            mula_s(f0, f6);
            madd_s(f1, f20, f1);
            mula_s(f0, f5);
            madd_s(f7, f20, f4);
            lwc1(f0, s7, 104);
            mula_s(f2, f3);
            mul_s(f13, f3, f21);
            madd_s(f6, f0, f10);
            mula_s(f2, f1);
            madd_s(f5, f0, f9);
            mula_s(f2, f7);
            madd_s(f4, f0, f8);
            mul_s(f2, f8, f22);
            mul_s(f3, f9, f22);
            lwc1(f8, s5, 0);
            mul_s(f0, f7, f21);
            neg_s(f9, f14);
            sub_s(f7, f9, f13);
            add_s(f8, f8, f6);
            add_s(f7, f8, f7);
            swc1(f7, s3, 0);
            lwc1(f10, s5, 4);
            mul_s(f1, f1, f21);
            neg_s(f8, f3);
            sub_s(f7, f8, f1);
            add_s(f10, f10, f5);
            add_s(f7, f10, f7);
            swc1(f7, s3, 4);
            lwc1(f11, s5, 8);
            neg_s(f7, f2);
            sub_s(f10, f7, f0);
            add_s(f11, f11, f4);
            add_s(f10, f11, f10);
            swc1(f10, s3, 8);
            lwc1(f12, s5, 0);
            s3 = addu(a1, s2);
            sub_s(f11, f14, f13);
            add_s(f8, f8, f1);
            add_s(f12, f12, f6);
            add_s(f11, f12, f11);
            swc1(f11, a2, 0);
            sub_s(f11, f3, f1);
            lwc1(f12, s5, 4);
            add_s(f1, f3, f1);
            add_s(f7, f7, f0);
            add_s(f3, f12, f5);
            add_s(f3, f3, f11);
            swc1(f3, a2, 4);
            sub_s(f3, f2, f0);
            lwc1(f11, s5, 8);
            add_s(f0, f2, f0);
            add_s(f10, f14, f13);
            add_s(f2, f11, f4);
            add_s(f2, f2, f3);
            swc1(f2, a2, 8);
            lwc1(f2, s5, 0);
            add_s(f9, f9, f13);
            add_s(f2, f2, f6);
            add_s(f2, f2, f10);
            swc1(f2, v1, 0);
            lwc1(f2, s5, 4);
            add_s(f2, f2, f5);
            add_s(f1, f2, f1);
            swc1(f1, v1, 4);
            lwc1(f1, s5, 8);
            add_s(f1, f1, f4);
            add_s(f0, f1, f0);
            swc1(f0, v1, 8);
            lwc1(f0, s5, 0);
            lq(v1, sp, 0xC0);
            add_s(f0, f0, f6);
            add_s(f0, f0, f9);
            swc1(f0, a1, 0);
            lwc1(f0, s5, 4);
            add_s(f0, f0, f5);
            add_s(f0, f0, f8);
            swc1(f0, a1, 4);
            lwc1(f0, s5, 8);
            add_s(f0, f0, f4);
            s5 = addu(s5, v1);
            add_s(f0, f0, f7);
            swc1(f0, a1, 8);
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004874d4
        charge(ctx, 2);
        backedge(ctx);
    }
    // 0x0048730c
    charge(ctx, 2);
    ld(ra, sp, 0xA0);
    // 0x004874dc
    charge(ctx, 14);
    lwc1(f22, sp, 0x8);
    lq(fp, sp, 0x90);
    lwc1(f21, sp, 0x4);
    lq(s7, sp, 0x80);
    lwc1(f20, sp, 0x0);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0xD0);
}

// 0x004876F0 sub_4876F0 -- 672 bytes; frame 0xF0: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// sub_4876F0 [positions, rotation, size per particle, pivot]: the count is spilled to sp + 236 and re-read every
// particle.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_4876F0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::enter, hg::jal,
          hg::ld, hg::link, hg::lq, hg::lw, hg::lwc1, hg::madd_s, hg::mov_s, hg::mtc1, hg::mul_s, hg::mula_s,
          hg::neg_s, hg::sd, hg::slt, hg::sq, hg::sub_s, hg::sw, hg::swc1;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f20{ctx, 20};
    // 0x004876f0
    enter(ctx, 31);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
    sd(ra, sp, 0xA0);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    fp = t0;
    sq(s6, sp, 0x70);
    s7 = 0;
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    s3 = a1;
    sq(s1, sp, 0x20);
    s2 = a2;
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    sw(a3, sp, 0xEC);
    lw(v1, t0, 8);
    lw(s1, t0, 4);
    lw(s0, t0, 52);
    lw(s6, t0, 28);
    lw(s5, a0, 0);
    lw(s4, a0, 4);
    sq(v1, sp, 0xD0);
    v1 = a3;
    a1 = slt(0, v1);
    lw(v1, t0, 56);
    sq(v1, sp, 0xC0);
    lw(v1, t0, 32);
    sq(v1, sp, 0xB0);
    if (a1 != 0) {
        for (;;) {
            // 0x00487774
            charge(ctx, 121);
            link(ctx, 0x487774u);  // $ra first: the delay slot below depends on it
            lwc1(f12, s0, 0);
            call(ctx, gen::fn_sinf_0052e878);
            lwc1(f12, s0, 0);
            mov_s(f20, f0);
            jal(ctx, 0x487780u, gen::fn_cosf_0052e6d8);
            lwc1(f9, s2, 0);
            lq(v1, sp, 0xC0);
            lwc1(f6, s3, 0);
            a3 = addu(s5, s4);
            lwc1(f5, s2, 4);
            a2 = addu(a3, s4);
            lwc1(f4, s3, 4);
            a1 = addu(a2, s4);
            lwc1(f2, s2, 8);
            s7 = addiu(s7, 1);
            neg_s(f7, f20);
            mula_s(f7, f9);
            s0 = addu(s0, v1);
            madd_s(f11, f0, f6);
            v1 = 0x3F000000;
            mula_s(f7, f5);
            madd_s(f13, f0, f4);
            mula_s(f7, f2);
            lwc1(f1, s3, 8);
            mtc1(v1, f3);
            lwc1(f8, fp, 0x6C);
            lw(v1, sp, 0xEC);
            lwc1(f7, fp, 0x68);
            madd_s(f15, f0, f1);
            mula_s(f0, f9);
            madd_s(f6, f20, f6);
            mula_s(f0, f5);
            a0 = slt(s7, v1);
            madd_s(f10, f20, f4);
            lq(v1, sp, 0xB0);
            mula_s(f0, f2);
            madd_s(f9, f20, f1);
            lwc1(f2, s6, 0);
            lwc1(f1, s6, 4);
            mula_s(f8, f6);
            madd_s(f4, f7, f11);
            lwc1(f0, s1, 0);
            mula_s(f8, f10);
            mul_s(f5, f3, f2);
            s6 = addu(s6, v1);
            lq(v1, sp, 0xD0);
            mul_s(f1, f3, f1);
            mul_s(f14, f11, f5);
            mul_s(f11, f6, f1);
            madd_s(f3, f7, f13);
            add_s(f6, f0, f4);
            mula_s(f8, f9);
            madd_s(f2, f7, f15);
            mul_s(f12, f10, f1);
            mul_s(f0, f9, f1);
            mul_s(f13, f13, f5);
            mul_s(f1, f15, f5);
            neg_s(f7, f14);
            sub_s(f5, f7, f11);
            add_s(f5, f6, f5);
            swc1(f5, s5, 0);
            lwc1(f8, s1, 4);
            neg_s(f6, f13);
            sub_s(f5, f6, f12);
            add_s(f8, f8, f3);
            add_s(f5, f8, f5);
            swc1(f5, s5, 4);
            lwc1(f9, s1, 8);
            neg_s(f5, f1);
            sub_s(f8, f5, f0);
            add_s(f9, f9, f2);
            add_s(f8, f9, f8);
            swc1(f8, s5, 8);
            lwc1(f10, s1, 0);
            s5 = addu(a1, s4);
            sub_s(f8, f14, f11);
            add_s(f7, f7, f11);
            add_s(f10, f10, f4);
            add_s(f8, f10, f8);
            swc1(f8, a3, 0);
            add_s(f9, f14, f11);
            lwc1(f11, s1, 4);
            sub_s(f10, f13, f12);
            add_s(f5, f5, f0);
            add_s(f11, f11, f3);
            add_s(f10, f11, f10);
            swc1(f10, a3, 4);
            sub_s(f10, f1, f0);
            lwc1(f11, s1, 8);
            add_s(f0, f1, f0);
            add_s(f8, f13, f12);
            add_s(f1, f11, f2);
            add_s(f1, f1, f10);
            swc1(f1, a3, 8);
            lwc1(f1, s1, 0);
            add_s(f6, f6, f12);
            add_s(f1, f1, f4);
            add_s(f1, f1, f9);
            swc1(f1, a2, 0);
            lwc1(f1, s1, 4);
            add_s(f1, f1, f3);
            add_s(f1, f1, f8);
            swc1(f1, a2, 4);
            lwc1(f1, s1, 8);
            add_s(f1, f1, f2);
            add_s(f0, f1, f0);
            swc1(f0, a2, 8);
            lwc1(f0, s1, 0);
            add_s(f0, f0, f4);
            add_s(f0, f0, f7);
            swc1(f0, a1, 0);
            lwc1(f0, s1, 4);
            add_s(f0, f0, f3);
            add_s(f0, f0, f6);
            swc1(f0, a1, 4);
            lwc1(f0, s1, 8);
            add_s(f0, f0, f2);
            s1 = addu(s1, v1);
            add_s(f0, f0, f5);
            swc1(f0, a1, 8);
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00487958
        charge(ctx, 2);
        backedge(ctx);
    }
    // 0x0048776c
    charge(ctx, 2);
    ld(ra, sp, 0xA0);
    // 0x00487960
    charge(ctx, 12);
    lwc1(f20, sp, 0x0);
    lq(fp, sp, 0x90);
    lq(s7, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0xF0);
}

// 0x00487BF0 sub_487BF0 -- 644 bytes; frame 0x120: fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_487BF0 [colour per particle]: the particle's colour word {+36 pointer, +40 stride} into its four vertices; eight
// particles per iteration while count is in 9..0x7FFFFFFE, then one by one. The unrolled body runs out of registers:
// the compiler spills vertex addresses, the source cursor, count - 8 and the loop test to its frame (sp + 144 ..
// sp + 272) and moves one 128-bit value with PADDUB $a2, $s7, $zero; all of it is kept.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: the hand version terminated the host on a random world.
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_487BF0(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lq, hg::lw, hg::paddub, hg::slt,
          hg::slti, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, fp{ctx, 30};
    // 0x00487bf0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x120);
    at = slt(0, a1);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, 0);
    lw(s3, a0, 4);
    lw(s4, a2, 36);
    lw(s2, a2, 40);
    s5 = 0;
    if (at != 0) {
        // 0x00487c34
        charge(ctx, 4);
        v1 = addiu(a1, -8);
        at = slti(a1, 9);
        sq(v1, sp, 0x110);
        if (at == 0) {
            // 0x00487c44
            charge(ctx, 3);
            at = slt(a1, 0);
            v1 = 0;
            if (at == 0) {
                // 0x00487c50
                charge(ctx, 5);
                at = 0x7FFF0000;
                at = at | 0xFFFF;
                at = slt(a1, at);
                if (at != 0) {
                    // 0x00487c64
                    charge(ctx, 1);
                    v1 = 1;
                }
            }
            // 0x00487c68
            charge(ctx, 2);
            if (v1 != 0) {
                for (;;) {
                    // 0x00487c70
                    charge(ctx, 102);
                    lw(t6, s4, 0);
                    t0 = addu(s1, s3);
                    a2 = addu(t0, s3);
                    t5 = addu(s4, s2);
                    a0 = addu(a2, s3);
                    a3 = addu(t5, s2);
                    s0 = addu(a3, s2);
                    t4 = addu(a0, s3);
                    t8 = addu(s0, s2);
                    t2 = addu(t4, s3);
                    t3 = addu(t8, s2);
                    t1 = addu(t2, s3);
                    sw(t6, s1, 0);
                    v1 = addu(t3, s2);
                    sw(t6, t0, 0);
                    s1 = addu(t1, s3);
                    sw(t6, a2, 0);
                    s5 = addiu(s5, 8);
                    sw(t6, a0, 0);
                    a2 = addu(s1, s3);
                    lw(t0, t5, 0);
                    a0 = addu(a2, s3);
                    sq(v1, sp, 0x100);
                    v1 = addu(a0, s3);
                    s6 = addu(v1, s3);
                    t9 = addu(s6, s3);
                    t7 = addu(t9, s3);
                    lq(t5, sp, 0x100);
                    t6 = addu(t7, s3);
                    sw(t0, t4, 0);
                    sw(t0, t2, 0);
                    sw(t0, t1, 0);
                    sw(t0, s1, 0);
                    lw(s1, a3, 0);
                    t5 = addu(t5, s2);
                    sq(t5, sp, 0xC0);
                    s4 = addu(t5, s2);
                    lq(t5, sp, 0x110);
                    sw(s1, a2, 0);
                    sw(s1, a0, 0);
                    sw(s1, v1, 0);
                    t5 = slt(s5, t5);
                    sw(s1, s6, 0);
                    sq(t5, sp, 0x90);
                    t5 = addu(t6, s3);
                    t4 = addu(t5, s3);
                    t2 = addu(t4, s3);
                    t1 = addu(t2, s3);
                    t0 = addu(t1, s3);
                    a3 = addu(t0, s3);
                    fp = addu(a3, s3);
                    s7 = addu(fp, s3);
                    sq(s7, sp, 0xF0);
                    s7 = addu(s7, s3);
                    sq(s7, sp, 0xE0);
                    s7 = addu(s7, s3);
                    sq(s7, sp, 0xD0);
                    s7 = addu(s7, s3);
                    paddub(a2, s7, zero);
                    sq(s7, sp, 0xB0);
                    lw(s7, s0, 0);
                    a2 = addu(a2, s3);
                    a0 = addu(a2, s3);
                    v1 = addu(a0, s3);
                    s6 = addu(v1, s3);
                    sw(s7, t9, 0);
                    s0 = addu(s6, s3);
                    sw(s7, t7, 0);
                    s1 = addu(s0, s3);
                    sw(s7, t6, 0);
                    sw(s7, t5, 0);
                    lw(t5, t8, 0);
                    sq(s1, sp, 0xA0);
                    sw(t5, t4, 0);
                    sw(t5, t2, 0);
                    sw(t5, t1, 0);
                    sw(t5, t0, 0);
                    lw(t0, t3, 0);
                    sw(t0, a3, 0);
                    lq(a3, sp, 0xF0);
                    sw(t0, fp, 0x0);
                    sw(t0, a3, 0);
                    lq(a3, sp, 0xE0);
                    sw(t0, a3, 0);
                    lq(a3, sp, 0x100);
                    lw(t0, a3, 0);
                    lq(a3, sp, 0xD0);
                    sw(t0, a3, 0);
                    lq(a3, sp, 0xB0);
                    sw(t0, a3, 0);
                    sw(t0, a2, 0);
                    sw(t0, a0, 0);
                    lq(a0, sp, 0xC0);
                    lw(a0, a0, 0);
                    sw(a0, v1, 0);
                    lq(v1, sp, 0xA0);
                    sw(a0, s6, 0);
                    sw(a0, s0, 0);
                    sw(a0, v1, 0);
                    lq(v1, sp, 0x90);
                    s1 = addu(s1, s3);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
        // 0x00487e08
        charge(ctx, 3);
        at = slt(s5, a1);
        if (at != 0) {
            for (;;) {
                // 0x00487e14
                charge(ctx, 13);
                lw(t0, s4, 0);
                a3 = addu(s1, s3);
                a2 = addu(a3, s3);
                s5 = addiu(s5, 1);
                a0 = addu(a2, s3);
                v1 = slt(s5, a1);
                sw(t0, s1, 0);
                s4 = addu(s4, s2);
                sw(t0, a3, 0);
                s1 = addu(a0, s3);
                sw(t0, a2, 0);
                sw(t0, a0, 0);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
    }
    // 0x00487e48 (the shared epilogue, written out on this path)
    charge(ctx, 11);
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
}

// 0x00477610 sub_477610 -- 512 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_477610 [positions]: $a0 the stream, $a3 the count, $t0 the component {+4 pointer, +8 stride}; 3 floats.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: the hand version terminated the host on a random world.
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_477610(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq,
          hg::lw, hg::lwc1, hg::mult, hg::sd, hg::slt, hg::slti, hg::sq, hg::swc1;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x00477610
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a1, t0, 4);
    lw(a2, t0, 8);
    lw(v1, a0, 4);
    lw(t0, a0, 0);
    if (a2 == v1) {
        // 0x004777d8
        charge(ctx, 5);
        mult(a2, a3, v1);
        a0 = t0;
        jal(ctx, 0x4777DCu, gen::fn_sub_476C20_00476c20);
        backedge(ctx);
    } else {
        // 0x00477648
        charge(ctx, 3);
        at = slt(0, a3);
        a0 = 0;
        if (at != 0) {
            // 0x00477654
            charge(ctx, 3);
            at = slti(a3, 9);
            s6 = addiu(a3, -8);
            if (at == 0) {
                // 0x00477660
                charge(ctx, 3);
                at = slt(a3, 0);
                t1 = 0;
                if (at == 0) {
                    // 0x0047766c
                    charge(ctx, 5);
                    at = 0x7FFF0000;
                    at = at | 0xFFFF;
                    at = slt(a3, at);
                    if (at != 0) {
                        // 0x00477680
                        charge(ctx, 1);
                        t1 = 1;
                    }
                }
                // 0x00477684
                charge(ctx, 2);
                if (t1 != 0) {
                    for (;;) {
                        // 0x0047768c
                        charge(ctx, 67);
                        lwc1(f0, a1, 0);
                        s4 = addu(a1, a2);
                        s5 = addu(t0, v1);
                        s2 = addu(s4, a2);
                        s3 = addu(s5, v1);
                        s0 = addu(s2, a2);
                        s1 = addu(s3, v1);
                        t8 = addu(s0, a2);
                        t9 = addu(s1, v1);
                        t6 = addu(t8, a2);
                        t7 = addu(t9, v1);
                        t4 = addu(t6, a2);
                        swc1(f0, t0, 0);
                        t5 = addu(t7, v1);
                        lwc1(f0, a1, 4);
                        a0 = addiu(a0, 8);
                        t2 = addu(t4, a2);
                        t3 = addu(t5, v1);
                        t1 = slt(a0, s6);
                        swc1(f0, t0, 4);
                        lwc1(f0, a1, 8);
                        swc1(f0, t0, 8);
                        a1 = addu(t2, a2);
                        lwc1(f0, s4, 0);
                        t0 = addu(t3, v1);
                        swc1(f0, s5, 0);
                        lwc1(f0, s4, 4);
                        swc1(f0, s5, 4);
                        lwc1(f0, s4, 8);
                        swc1(f0, s5, 8);
                        lwc1(f0, s2, 0);
                        swc1(f0, s3, 0);
                        lwc1(f0, s2, 4);
                        swc1(f0, s3, 4);
                        lwc1(f0, s2, 8);
                        swc1(f0, s3, 8);
                        lwc1(f0, s0, 0);
                        swc1(f0, s1, 0);
                        lwc1(f0, s0, 4);
                        swc1(f0, s1, 4);
                        lwc1(f0, s0, 8);
                        swc1(f0, s1, 8);
                        lwc1(f0, t8, 0);
                        swc1(f0, t9, 0);
                        lwc1(f0, t8, 4);
                        swc1(f0, t9, 4);
                        lwc1(f0, t8, 8);
                        swc1(f0, t9, 8);
                        lwc1(f0, t6, 0);
                        swc1(f0, t7, 0);
                        lwc1(f0, t6, 4);
                        swc1(f0, t7, 4);
                        lwc1(f0, t6, 8);
                        swc1(f0, t7, 8);
                        lwc1(f0, t4, 0);
                        swc1(f0, t5, 0);
                        lwc1(f0, t4, 4);
                        swc1(f0, t5, 4);
                        lwc1(f0, t4, 8);
                        swc1(f0, t5, 8);
                        lwc1(f0, t2, 0);
                        swc1(f0, t3, 0);
                        lwc1(f0, t2, 4);
                        swc1(f0, t3, 4);
                        lwc1(f0, t2, 8);
                        swc1(f0, t3, 8);
                        if (t1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
            }
            // 0x00477798
            charge(ctx, 3);
            at = slt(a0, a3);
            if (at != 0) {
                for (;;) {
                    // 0x004777a4
                    charge(ctx, 11);
                    lwc1(f0, a1, 0);
                    a0 = addiu(a0, 1);
                    t1 = slt(a0, a3);
                    swc1(f0, t0, 0);
                    lwc1(f0, a1, 4);
                    swc1(f0, t0, 4);
                    lwc1(f0, a1, 8);
                    swc1(f0, t0, 8);
                    a1 = addu(a1, a2);
                    t0 = addu(t0, v1);
                    if (t1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
    }
    // 0x004777d0
    charge(ctx, 2);
    ld(ra, sp, 0x70);
    // 0x004777ec
    charge(ctx, 9);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x00477A20 sub_477A20 -- 620 bytes; frame 0xC0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_477A20 [colours]: $a0 the stream, $a1 the count, $a2 the tank (colours {+36 pointer, +40 stride}), RGBA byte by
// byte; count - 8 and the loop test live in the frame (sp + 176, sp + 160).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: the hand version terminated the host on a random world.
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_477A20(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lq,
          hg::lw, hg::mult, hg::sb, hg::sd, hg::slt, hg::slti, hg::sq;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00477a20
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
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
    lw(v1, a0, 4);
    lw(s6, a2, 40);
    lw(a3, a2, 36);
    lw(t0, a0, 0);
    if (s6 == v1) {
        // 0x00477c48
        charge(ctx, 6);
        mult(a2, a1, v1);
        a0 = t0;
        a1 = a3;
        jal(ctx, 0x477C50u, gen::fn_sub_476C20_00476c20);
        backedge(ctx);
    } else {
        // 0x00477a60
        charge(ctx, 3);
        at = slt(0, a1);
        s7 = 0;
        if (at != 0) {
            // 0x00477a6c
            charge(ctx, 4);
            a0 = addiu(a1, -8);
            at = slti(a1, 9);
            sq(a0, sp, 0xB0);
            if (at == 0) {
                // 0x00477a7c
                charge(ctx, 3);
                at = slt(a1, 0);
                a0 = 0;
                if (at == 0) {
                    // 0x00477a88
                    charge(ctx, 5);
                    at = 0x7FFF0000;
                    at = at | 0xFFFF;
                    at = slt(a1, at);
                    if (at != 0) {
                        // 0x00477a9c
                        charge(ctx, 1);
                        a0 = 1;
                    }
                }
                // 0x00477aa0
                charge(ctx, 2);
                if (a0 != 0) {
                    for (;;) {
                        // 0x00477aa8
                        charge(ctx, 86);
                        lbu(s5, a3, 0);
                        s1 = addu(a3, s6);
                        lbu(s4, a3, 1);
                        t9 = addu(s1, s6);
                        lbu(s3, a3, 2);
                        s2 = addu(t0, v1);
                        lbu(fp, a3, 3);
                        s0 = addu(s2, v1);
                        t8 = addu(s0, v1);
                        t7 = addu(t9, s6);
                        t5 = addu(t7, s6);
                        t6 = addu(t8, v1);
                        t3 = addu(t5, s6);
                        t4 = addu(t6, v1);
                        t1 = addu(t3, s6);
                        t2 = addu(t4, v1);
                        a0 = addu(t1, s6);
                        s7 = addiu(s7, 8);
                        sb(s5, t0, 0);
                        a2 = addu(t2, v1);
                        sb(s4, t0, 1);
                        a3 = addu(a0, s6);
                        sb(s3, t0, 2);
                        lq(s3, sp, 0xB0);
                        sb(fp, t0, 3);
                        lbu(s5, s1, 0);
                        lbu(s4, s1, 1);
                        s3 = slt(s7, s3);
                        sq(s3, sp, 0xA0);
                        lbu(s3, s1, 2);
                        lbu(s1, s1, 3);
                        sb(s5, s2, 0);
                        sb(s4, s2, 1);
                        sb(s3, s2, 2);
                        sb(s1, s2, 3);
                        lbu(s4, t9, 0);
                        lbu(s3, t9, 1);
                        lbu(s2, t9, 2);
                        lbu(s1, t9, 3);
                        sb(s4, s0, 0);
                        sb(s3, s0, 1);
                        sb(s2, s0, 2);
                        sb(s1, s0, 3);
                        lbu(s2, t7, 0);
                        lbu(s1, t7, 1);
                        lbu(s0, t7, 2);
                        lbu(t7, t7, 3);
                        sb(s2, t8, 0);
                        sb(s1, t8, 1);
                        sb(s0, t8, 2);
                        sb(t7, t8, 3);
                        lbu(s1, t5, 0);
                        lbu(s0, t5, 1);
                        lbu(t7, t5, 2);
                        lbu(t5, t5, 3);
                        sb(s1, t6, 0);
                        sb(s0, t6, 1);
                        sb(t7, t6, 2);
                        sb(t5, t6, 3);
                        lbu(t7, t3, 0);
                        lbu(t6, t3, 1);
                        lbu(t5, t3, 2);
                        lbu(t3, t3, 3);
                        sb(t7, t4, 0);
                        sb(t6, t4, 1);
                        sb(t5, t4, 2);
                        sb(t3, t4, 3);
                        lbu(t5, t1, 0);
                        lbu(t4, t1, 1);
                        lbu(t3, t1, 2);
                        lbu(t1, t1, 3);
                        sb(t5, t2, 0);
                        sb(t4, t2, 1);
                        sb(t3, t2, 2);
                        sb(t1, t2, 3);
                        lbu(t3, a0, 0);
                        lbu(t2, a0, 1);
                        lbu(t1, a0, 2);
                        lbu(a0, a0, 3);
                        sb(t3, a2, 0);
                        sb(t2, a2, 1);
                        sb(t1, a2, 2);
                        sb(a0, a2, 3);
                        lq(a0, sp, 0xA0);
                        t0 = addu(a2, v1);
                        if (a0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
            }
            // 0x00477c00
            charge(ctx, 3);
            at = slt(s7, a1);
            if (at != 0) {
                for (;;) {
                    // 0x00477c0c
                    charge(ctx, 13);
                    lbu(t3, a3, 0);
                    s7 = addiu(s7, 1);
                    lbu(t2, a3, 1);
                    a0 = slt(s7, a1);
                    lbu(t1, a3, 2);
                    lbu(a2, a3, 3);
                    sb(t3, t0, 0);
                    a3 = addu(a3, s6);
                    sb(t2, t0, 1);
                    sb(t1, t0, 2);
                    sb(a2, t0, 3);
                    t0 = addu(t0, v1);
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
    }
    // 0x00477c40
    charge(ctx, 2);
    ld(ra, sp, 0x90);
    // 0x00477c60
    charge(ctx, 11);
    lq(fp, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xC0);
}

// 0x00477EB0 sub_477EB0 -- 588 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_477EB0 [UV rectangles]: $a0 the stream, $a1 the count, $a2 the tank (rectangles {+60 pointer, +64 stride}); 4
// floats per particle.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: the hand version terminated the host on a random world.
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_477EB0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq,
          hg::lw, hg::lwc1, hg::mult, hg::sd, hg::slt, hg::slti, hg::sq, hg::swc1;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x00477eb0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(t0, a0, 0);
    lw(v1, a2, 64);
    lw(a0, a0, 4);
    lw(a3, a2, 60);
    if (v1 == a0) {
        // 0x004780c0
        charge(ctx, 6);
        mult(a2, a1, a0);
        a0 = t0;
        a1 = a3;
        jal(ctx, 0x4780C8u, gen::fn_sub_476C20_00476c20);
        backedge(ctx);
    } else {
        // 0x00477ee8
        charge(ctx, 3);
        at = slt(0, a1);
        a2 = 0;
        if (at != 0) {
            // 0x00477ef4
            charge(ctx, 3);
            at = slti(a1, 9);
            s6 = addiu(a1, -8);
            if (at == 0) {
                // 0x00477f00
                charge(ctx, 3);
                at = slt(a1, 0);
                t1 = 0;
                if (at == 0) {
                    // 0x00477f0c
                    charge(ctx, 5);
                    at = 0x7FFF0000;
                    at = at | 0xFFFF;
                    at = slt(a1, at);
                    if (at != 0) {
                        // 0x00477f20
                        charge(ctx, 1);
                        t1 = 1;
                    }
                }
                // 0x00477f24
                charge(ctx, 2);
                if (t1 != 0) {
                    for (;;) {
                        // 0x00477f2c
                        charge(ctx, 83);
                        lwc1(f0, a3, 0);
                        s4 = addu(a3, v1);
                        s5 = addu(t0, a0);
                        s2 = addu(s4, v1);
                        s3 = addu(s5, a0);
                        s0 = addu(s2, v1);
                        s1 = addu(s3, a0);
                        t8 = addu(s0, v1);
                        t9 = addu(s1, a0);
                        t6 = addu(t8, v1);
                        t7 = addu(t9, a0);
                        t4 = addu(t6, v1);
                        swc1(f0, t0, 0);
                        t5 = addu(t7, a0);
                        lwc1(f0, a3, 4);
                        a2 = addiu(a2, 8);
                        t2 = addu(t4, v1);
                        t3 = addu(t5, a0);
                        t1 = slt(a2, s6);
                        swc1(f0, t0, 4);
                        lwc1(f0, a3, 8);
                        swc1(f0, t0, 8);
                        lwc1(f0, a3, 12);
                        swc1(f0, t0, 12);
                        a3 = addu(t2, v1);
                        lwc1(f0, s4, 0);
                        t0 = addu(t3, a0);
                        swc1(f0, s5, 0);
                        lwc1(f0, s4, 4);
                        swc1(f0, s5, 4);
                        lwc1(f0, s4, 8);
                        swc1(f0, s5, 8);
                        lwc1(f0, s4, 12);
                        swc1(f0, s5, 12);
                        lwc1(f0, s2, 0);
                        swc1(f0, s3, 0);
                        lwc1(f0, s2, 4);
                        swc1(f0, s3, 4);
                        lwc1(f0, s2, 8);
                        swc1(f0, s3, 8);
                        lwc1(f0, s2, 12);
                        swc1(f0, s3, 12);
                        lwc1(f0, s0, 0);
                        swc1(f0, s1, 0);
                        lwc1(f0, s0, 4);
                        swc1(f0, s1, 4);
                        lwc1(f0, s0, 8);
                        swc1(f0, s1, 8);
                        lwc1(f0, s0, 12);
                        swc1(f0, s1, 12);
                        lwc1(f0, t8, 0);
                        swc1(f0, t9, 0);
                        lwc1(f0, t8, 4);
                        swc1(f0, t9, 4);
                        lwc1(f0, t8, 8);
                        swc1(f0, t9, 8);
                        lwc1(f0, t8, 12);
                        swc1(f0, t9, 12);
                        lwc1(f0, t6, 0);
                        swc1(f0, t7, 0);
                        lwc1(f0, t6, 4);
                        swc1(f0, t7, 4);
                        lwc1(f0, t6, 8);
                        swc1(f0, t7, 8);
                        lwc1(f0, t6, 12);
                        swc1(f0, t7, 12);
                        lwc1(f0, t4, 0);
                        swc1(f0, t5, 0);
                        lwc1(f0, t4, 4);
                        swc1(f0, t5, 4);
                        lwc1(f0, t4, 8);
                        swc1(f0, t5, 8);
                        lwc1(f0, t4, 12);
                        swc1(f0, t5, 12);
                        lwc1(f0, t2, 0);
                        swc1(f0, t3, 0);
                        lwc1(f0, t2, 4);
                        swc1(f0, t3, 4);
                        lwc1(f0, t2, 8);
                        swc1(f0, t3, 8);
                        lwc1(f0, t2, 12);
                        swc1(f0, t3, 12);
                        if (t1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
            }
            // 0x00478078
            charge(ctx, 3);
            at = slt(a2, a1);
            if (at != 0) {
                for (;;) {
                    // 0x00478084
                    charge(ctx, 13);
                    lwc1(f0, a3, 0);
                    a2 = addiu(a2, 1);
                    t1 = slt(a2, a1);
                    swc1(f0, t0, 0);
                    lwc1(f0, a3, 4);
                    swc1(f0, t0, 4);
                    lwc1(f0, a3, 8);
                    swc1(f0, t0, 8);
                    lwc1(f0, a3, 12);
                    swc1(f0, t0, 12);
                    a3 = addu(a3, v1);
                    t0 = addu(t0, a0);
                    if (t1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
    }
    // 0x004780b8
    charge(ctx, 2);
    ld(ra, sp, 0x70);
    // 0x004780d8
    charge(ctx, 9);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x00478280 sub_478280 -- 440 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_478280 [sizes]: $a0 the stream, $a1 the count, $a2 the tank (sizes {+28 pointer, +32 stride}); (w, h) through
// $f1 / $f0; the eight-way loop's exit has one extra block here.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: the hand version terminated the host on a random world.
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_478280(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq,
          hg::lw, hg::lwc1, hg::mult, hg::sd, hg::slt, hg::slti, hg::sq, hg::swc1;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x00478280
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(t0, a0, 0);
    lw(v1, a2, 32);
    lw(a0, a0, 4);
    lw(a3, a2, 28);
    if (v1 == a0) {
        // 0x00478400
        charge(ctx, 6);
        mult(a2, a1, a0);
        a0 = t0;
        a1 = a3;
        jal(ctx, 0x478408u, gen::fn_sub_476C20_00476c20);
        backedge(ctx);
    } else {
        // 0x004782b4
        charge(ctx, 3);
        at = slt(0, a1);
        a2 = 0;
        if (at != 0) {
            // 0x004782c0
            charge(ctx, 3);
            at = slti(a1, 9);
            s5 = addiu(a1, -8);
            if (at == 0) {
                // 0x004782cc
                charge(ctx, 3);
                at = slt(a1, 0);
                t1 = 0;
                if (at == 0) {
                    // 0x004782d8
                    charge(ctx, 5);
                    at = 0x7FFF0000;
                    at = at | 0xFFFF;
                    at = slt(a1, at);
                    if (at != 0) {
                        // 0x004782ec
                        charge(ctx, 1);
                        t1 = 1;
                    }
                }
                // 0x004782f0
                charge(ctx, 2);
                if (t1 != 0) {
                    for (;;) {
                        // 0x004782f8
                        charge(ctx, 51);
                        lwc1(f1, a3, 0);
                        s4 = addu(t0, a0);
                        lwc1(f0, a3, 4);
                        s3 = addu(s4, a0);
                        s1 = addu(s3, a0);
                        a2 = addiu(a2, 8);
                        t9 = addu(s1, a0);
                        t1 = slt(a2, s5);
                        t7 = addu(t9, a0);
                        t5 = addu(t7, a0);
                        t3 = addu(t5, a0);
                        swc1(f1, t0, 0);
                        a3 = addu(a3, v1);
                        swc1(f0, t0, 4);
                        s2 = addu(a3, v1);
                        lwc1(f1, a3, 0);
                        s0 = addu(s2, v1);
                        lwc1(f0, a3, 4);
                        t8 = addu(s0, v1);
                        t6 = addu(t8, v1);
                        t0 = addu(t3, a0);
                        t4 = addu(t6, v1);
                        t2 = addu(t4, v1);
                        swc1(f1, s4, 0);
                        a3 = addu(t2, v1);
                        swc1(f0, s4, 4);
                        lwc1(f1, s2, 0);
                        lwc1(f0, s2, 4);
                        swc1(f1, s3, 0);
                        swc1(f0, s3, 4);
                        lwc1(f1, s0, 0);
                        lwc1(f0, s0, 4);
                        swc1(f1, s1, 0);
                        swc1(f0, s1, 4);
                        lwc1(f1, t8, 0);
                        lwc1(f0, t8, 4);
                        swc1(f1, t9, 0);
                        swc1(f0, t9, 4);
                        lwc1(f1, t6, 0);
                        lwc1(f0, t6, 4);
                        swc1(f1, t7, 0);
                        swc1(f0, t7, 4);
                        lwc1(f1, t4, 0);
                        lwc1(f0, t4, 4);
                        swc1(f1, t5, 0);
                        swc1(f0, t5, 4);
                        lwc1(f1, t2, 0);
                        lwc1(f0, t2, 4);
                        swc1(f1, t3, 0);
                        swc1(f0, t3, 4);
                        if (t1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004783c4
                    charge(ctx, 1);
                }
            }
            // 0x004783c8
            charge(ctx, 3);
            at = slt(a2, a1);
            if (at != 0) {
                for (;;) {
                    // 0x004783d4
                    charge(ctx, 9);
                    lwc1(f1, a3, 0);
                    a2 = addiu(a2, 1);
                    lwc1(f0, a3, 4);
                    t1 = slt(a2, a1);
                    swc1(f1, t0, 0);
                    a3 = addu(a3, v1);
                    swc1(f0, t0, 4);
                    t0 = addu(t0, a0);
                    if (t1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
    }
    // 0x004783f8
    charge(ctx, 2);
    ld(ra, sp, 0x60);
    // 0x00478418
    charge(ctx, 8);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00485110 sub_485110 -- 816 bytes; frame 0x180: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_485110 [constant vertex colours] / sub_485440 [constant colour] (3-D writers of sub_47BF80, four vertices a
// particle): $a0 the stream, $a1 the count, $a2 the tank.
// Vertex k of every particle gets the word at +128 + 4k (sub_485110) or +124 (sub_485440), re-read for every vertex;
// a stream of packed words (stride 4) is filled by the scratchpad streamers instead: sub_476720 with the 16-byte
// pattern copied to the frame (sp + 368) / sub_476140 with the word, count * 4 * 4 bytes. The eight-way loop keeps
// 15 vertex addresses and its test in the frame (sp + 160 .. sp + 352).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: the hand version terminated the host on a random world.
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_485110(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw,
          hg::mult, hg::sd, hg::sll, hg::slt, hg::slti, hg::sq, hg::sw;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00485110
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x180);
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
    lw(v1, a0, 0);
    lw(s6, a0, 4);
    a0 = 4;
    if (s6 == a0) {
        // 0x004853d8
        charge(ctx, 15);
        lw(v0, a2, 128);
        sw(v0, sp, 0x170);
        lw(v0, a2, 132);
        sw(v0, sp, 0x174);
        lw(v0, a2, 136);
        sw(v0, sp, 0x178);
        lw(v0, a2, 140);
        sw(v0, sp, 0x17C);
        mult(v0, a1, s6);
        a0 = v1;
        a2 = addiu(sp, 0x170);
        a1 = sll(v0, 2);
        jal(ctx, 0x485404u, gen::fn_sub_476720_00476720);
        backedge(ctx);
    } else {
        // 0x00485150
        charge(ctx, 3);
        at = slt(0, a1);
        s7 = 0;
        if (at != 0) {
            // 0x0048515c
            charge(ctx, 4);
            a0 = addiu(a1, -8);
            at = slti(a1, 9);
            sq(a0, sp, 0x160);
            if (at == 0) {
                // 0x0048516c
                charge(ctx, 3);
                at = slt(a1, 0);
                a0 = 0;
                if (at == 0) {
                    // 0x00485178
                    charge(ctx, 5);
                    at = 0x7FFF0000;
                    at = at | 0xFFFF;
                    at = slt(a1, at);
                    if (at != 0) {
                        // 0x0048518c
                        charge(ctx, 1);
                        a0 = 1;
                    }
                }
                // 0x00485190
                charge(ctx, 2);
                if (a0 != 0) {
                    for (;;) {
                        // 0x00485198
                        charge(ctx, 124);
                        lw(t2, a2, 128);
                        t1 = addu(v1, s6);
                        a3 = addu(t1, s6);
                        lq(t0, sp, 0x160);
                        a0 = addu(a3, s6);
                        s7 = addiu(s7, 8);
                        s5 = addu(a0, s6);
                        s4 = addu(s5, s6);
                        s3 = addu(s4, s6);
                        sw(t2, v1, 0);
                        s2 = addu(s3, s6);
                        lw(v1, a2, 132);
                        s1 = addu(s2, s6);
                        s0 = addu(s1, s6);
                        t0 = slt(s7, t0);
                        t9 = addu(s0, s6);
                        sq(t0, sp, 0xB0);
                        t8 = addu(t9, s6);
                        t7 = addu(t8, s6);
                        t6 = addu(t7, s6);
                        sw(v1, t1, 0);
                        t5 = addu(t6, s6);
                        lw(fp, a2, 136);
                        t4 = addu(t5, s6);
                        t3 = addu(t4, s6);
                        t2 = addu(t3, s6);
                        t1 = addu(t2, s6);
                        t0 = addu(t1, s6);
                        v1 = addu(t0, s6);
                        sw(fp, a3, 0);
                        sq(v1, sp, 0x140);
                        a3 = addu(v1, s6);
                        v1 = addu(a3, s6);
                        lw(fp, a2, 140);
                        sq(v1, sp, 0x130);
                        v1 = addu(v1, s6);
                        sq(v1, sp, 0x120);
                        v1 = addu(v1, s6);
                        sq(v1, sp, 0x110);
                        v1 = addu(v1, s6);
                        sw(fp, a0, 0);
                        sq(v1, sp, 0x100);
                        v1 = addu(v1, s6);
                        sq(v1, sp, 0xF0);
                        v1 = addu(v1, s6);
                        sq(v1, sp, 0xE0);
                        fp = addu(v1, s6);
                        lw(v1, a2, 128);
                        sq(v1, sp, 0x150);
                        lq(a0, sp, 0x150);
                        v1 = addu(fp, s6);
                        sq(v1, sp, 0xA0);
                        v1 = addu(v1, s6);
                        sq(v1, sp, 0xD0);
                        v1 = addu(v1, s6);
                        sq(v1, sp, 0xC0);
                        sw(a0, s5, 0);
                        lw(a0, a2, 132);
                        sw(a0, s4, 0);
                        lw(a0, a2, 136);
                        sw(a0, s3, 0);
                        lw(a0, a2, 140);
                        sw(a0, s2, 0);
                        lw(a0, a2, 128);
                        sw(a0, s1, 0);
                        lw(a0, a2, 132);
                        sw(a0, s0, 0);
                        lw(a0, a2, 136);
                        sw(a0, t9, 0);
                        lw(a0, a2, 140);
                        sw(a0, t8, 0);
                        lw(a0, a2, 128);
                        sw(a0, t7, 0);
                        lw(a0, a2, 132);
                        sw(a0, t6, 0);
                        lw(a0, a2, 136);
                        sw(a0, t5, 0);
                        lw(a0, a2, 140);
                        sw(a0, t4, 0);
                        lw(a0, a2, 128);
                        sw(a0, t3, 0);
                        lw(a0, a2, 132);
                        sw(a0, t2, 0);
                        lw(a0, a2, 136);
                        sw(a0, t1, 0);
                        lw(a0, a2, 140);
                        sw(a0, t0, 0);
                        lw(t0, a2, 128);
                        lq(a0, sp, 0x140);
                        sw(t0, a0, 0);
                        lw(a0, a2, 132);
                        sw(a0, a3, 0);
                        lw(a3, a2, 136);
                        lq(a0, sp, 0x130);
                        sw(a3, a0, 0);
                        lw(a3, a2, 140);
                        lq(a0, sp, 0x120);
                        sw(a3, a0, 0);
                        lw(a3, a2, 128);
                        lq(a0, sp, 0x110);
                        sw(a3, a0, 0);
                        lw(a3, a2, 132);
                        lq(a0, sp, 0x100);
                        sw(a3, a0, 0);
                        lw(a3, a2, 136);
                        lq(a0, sp, 0xF0);
                        sw(a3, a0, 0);
                        lw(a3, a2, 140);
                        lq(a0, sp, 0xE0);
                        sw(a3, a0, 0);
                        lw(a0, a2, 128);
                        sw(a0, fp, 0x0);
                        lw(a3, a2, 132);
                        lq(a0, sp, 0xA0);
                        sw(a3, a0, 0);
                        lw(a3, a2, 136);
                        lq(a0, sp, 0xD0);
                        sw(a3, a0, 0);
                        lw(a3, a2, 140);
                        lq(a0, sp, 0xC0);
                        sw(a3, a0, 0);
                        lq(a0, sp, 0xB0);
                        v1 = addu(v1, s6);
                        if (a0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
            }
            // 0x00485388
            charge(ctx, 3);
            at = slt(s7, a1);
            if (at != 0) {
                for (;;) {
                    // 0x00485394
                    charge(ctx, 15);
                    lw(a3, a2, 128);
                    t2 = addu(v1, s6);
                    t1 = addu(t2, s6);
                    s7 = addiu(s7, 1);
                    t0 = addu(t1, s6);
                    a0 = slt(s7, a1);
                    sw(a3, v1, 0);
                    lw(a3, a2, 132);
                    v1 = addu(t0, s6);
                    sw(a3, t2, 0);
                    lw(a3, a2, 136);
                    sw(a3, t1, 0);
                    lw(a3, a2, 140);
                    sw(a3, t0, 0);
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
    }
    // 0x004853d0
    charge(ctx, 2);
    ld(ra, sp, 0x90);
    // 0x00485414
    charge(ctx, 11);
    lq(fp, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x180);
}

// 0x00485440 sub_485440 -- 784 bytes; frame 0x170: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_485110 [constant vertex colours] / sub_485440 [constant colour] (3-D writers of sub_47BF80, four vertices a
// particle): $a0 the stream, $a1 the count, $a2 the tank.
// Vertex k of every particle gets the word at +128 + 4k (sub_485110) or +124 (sub_485440), re-read for every vertex;
// a stream of packed words (stride 4) is filled by the scratchpad streamers instead: sub_476720 with the 16-byte
// pattern copied to the frame (sp + 368) / sub_476140 with the word, count * 4 * 4 bytes. The eight-way loop keeps
// 15 vertex addresses and its test in the frame (sp + 160 .. sp + 352).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: the hand version terminated the host on a random world.
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_485440(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw,
          hg::mult, hg::sd, hg::sll, hg::slt, hg::slti, hg::sq, hg::sw;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00485440
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x170);
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
    lw(v1, a0, 0);
    lw(s6, a0, 4);
    a0 = 4;
    if (s6 == a0) {
        // 0x00485708
        charge(ctx, 7);
        mult(v0, a1, s6);
        lw(a2, a2, 124);
        a0 = v1;
        a1 = sll(v0, 2);
        jal(ctx, 0x485714u, gen::fn_sub_476140_00476140);
        backedge(ctx);
    } else {
        // 0x00485480
        charge(ctx, 3);
        at = slt(0, a1);
        s7 = 0;
        if (at != 0) {
            // 0x0048548c
            charge(ctx, 4);
            a0 = addiu(a1, -8);
            at = slti(a1, 9);
            sq(a0, sp, 0x160);
            if (at == 0) {
                // 0x0048549c
                charge(ctx, 3);
                at = slt(a1, 0);
                a0 = 0;
                if (at == 0) {
                    // 0x004854a8
                    charge(ctx, 5);
                    at = 0x7FFF0000;
                    at = at | 0xFFFF;
                    at = slt(a1, at);
                    if (at != 0) {
                        // 0x004854bc
                        charge(ctx, 1);
                        a0 = 1;
                    }
                }
                // 0x004854c0
                charge(ctx, 2);
                if (a0 != 0) {
                    for (;;) {
                        // 0x004854c8
                        charge(ctx, 124);
                        lw(t2, a2, 124);
                        t1 = addu(v1, s6);
                        a3 = addu(t1, s6);
                        lq(t0, sp, 0x160);
                        a0 = addu(a3, s6);
                        s7 = addiu(s7, 8);
                        s5 = addu(a0, s6);
                        s4 = addu(s5, s6);
                        s3 = addu(s4, s6);
                        sw(t2, v1, 0);
                        s2 = addu(s3, s6);
                        lw(v1, a2, 124);
                        s1 = addu(s2, s6);
                        s0 = addu(s1, s6);
                        t0 = slt(s7, t0);
                        t9 = addu(s0, s6);
                        sq(t0, sp, 0xB0);
                        t8 = addu(t9, s6);
                        t7 = addu(t8, s6);
                        t6 = addu(t7, s6);
                        sw(v1, t1, 0);
                        t5 = addu(t6, s6);
                        lw(fp, a2, 124);
                        t4 = addu(t5, s6);
                        t3 = addu(t4, s6);
                        t2 = addu(t3, s6);
                        t1 = addu(t2, s6);
                        t0 = addu(t1, s6);
                        v1 = addu(t0, s6);
                        sw(fp, a3, 0);
                        sq(v1, sp, 0x140);
                        a3 = addu(v1, s6);
                        v1 = addu(a3, s6);
                        lw(fp, a2, 124);
                        sq(v1, sp, 0x130);
                        v1 = addu(v1, s6);
                        sq(v1, sp, 0x120);
                        v1 = addu(v1, s6);
                        sq(v1, sp, 0x110);
                        v1 = addu(v1, s6);
                        sw(fp, a0, 0);
                        sq(v1, sp, 0x100);
                        v1 = addu(v1, s6);
                        sq(v1, sp, 0xF0);
                        v1 = addu(v1, s6);
                        sq(v1, sp, 0xE0);
                        fp = addu(v1, s6);
                        lw(v1, a2, 124);
                        sq(v1, sp, 0x150);
                        lq(a0, sp, 0x150);
                        v1 = addu(fp, s6);
                        sq(v1, sp, 0xA0);
                        v1 = addu(v1, s6);
                        sq(v1, sp, 0xD0);
                        v1 = addu(v1, s6);
                        sq(v1, sp, 0xC0);
                        sw(a0, s5, 0);
                        lw(a0, a2, 124);
                        sw(a0, s4, 0);
                        lw(a0, a2, 124);
                        sw(a0, s3, 0);
                        lw(a0, a2, 124);
                        sw(a0, s2, 0);
                        lw(a0, a2, 124);
                        sw(a0, s1, 0);
                        lw(a0, a2, 124);
                        sw(a0, s0, 0);
                        lw(a0, a2, 124);
                        sw(a0, t9, 0);
                        lw(a0, a2, 124);
                        sw(a0, t8, 0);
                        lw(a0, a2, 124);
                        sw(a0, t7, 0);
                        lw(a0, a2, 124);
                        sw(a0, t6, 0);
                        lw(a0, a2, 124);
                        sw(a0, t5, 0);
                        lw(a0, a2, 124);
                        sw(a0, t4, 0);
                        lw(a0, a2, 124);
                        sw(a0, t3, 0);
                        lw(a0, a2, 124);
                        sw(a0, t2, 0);
                        lw(a0, a2, 124);
                        sw(a0, t1, 0);
                        lw(a0, a2, 124);
                        sw(a0, t0, 0);
                        lw(t0, a2, 124);
                        lq(a0, sp, 0x140);
                        sw(t0, a0, 0);
                        lw(a0, a2, 124);
                        sw(a0, a3, 0);
                        lw(a3, a2, 124);
                        lq(a0, sp, 0x130);
                        sw(a3, a0, 0);
                        lw(a3, a2, 124);
                        lq(a0, sp, 0x120);
                        sw(a3, a0, 0);
                        lw(a3, a2, 124);
                        lq(a0, sp, 0x110);
                        sw(a3, a0, 0);
                        lw(a3, a2, 124);
                        lq(a0, sp, 0x100);
                        sw(a3, a0, 0);
                        lw(a3, a2, 124);
                        lq(a0, sp, 0xF0);
                        sw(a3, a0, 0);
                        lw(a3, a2, 124);
                        lq(a0, sp, 0xE0);
                        sw(a3, a0, 0);
                        lw(a0, a2, 124);
                        sw(a0, fp, 0x0);
                        lw(a3, a2, 124);
                        lq(a0, sp, 0xA0);
                        sw(a3, a0, 0);
                        lw(a3, a2, 124);
                        lq(a0, sp, 0xD0);
                        sw(a3, a0, 0);
                        lw(a3, a2, 124);
                        lq(a0, sp, 0xC0);
                        sw(a3, a0, 0);
                        lq(a0, sp, 0xB0);
                        v1 = addu(v1, s6);
                        if (a0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
            }
            // 0x004856b8
            charge(ctx, 3);
            at = slt(s7, a1);
            if (at != 0) {
                for (;;) {
                    // 0x004856c4
                    charge(ctx, 15);
                    lw(a3, a2, 124);
                    t2 = addu(v1, s6);
                    t1 = addu(t2, s6);
                    s7 = addiu(s7, 1);
                    t0 = addu(t1, s6);
                    a0 = slt(s7, a1);
                    sw(a3, v1, 0);
                    lw(a3, a2, 124);
                    v1 = addu(t0, s6);
                    sw(a3, t2, 0);
                    lw(a3, a2, 124);
                    sw(a3, t1, 0);
                    lw(a3, a2, 124);
                    sw(a3, t0, 0);
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
    }
    // 0x00485700
    charge(ctx, 2);
    ld(ra, sp, 0x90);
    // 0x00485724
    charge(ctx, 11);
    lq(fp, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x170);
}

// 0x00477150 sub_477150 -- 796 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_477150 [2-D lock, next buffer]: components +0 (16 bytes, record +320, always), +8 (4 bytes, +336; flags 2 or
// 0x2000), +4 (16 bytes, +348; flags 0x80 or 0x80000), +12 (8 bytes, +332; flags 4 or 0x4000) -- as sub_477470.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: callee frames ($sp off / deeper stack)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_477150(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd,
          hg::sll, hg::slt, hg::sltiu, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00477150
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    v1 = 1;
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a2;
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    lw(s0, a2, 76);
    lw(a0, s0, 224);
    s1 = t0;
    if (a0 == v1) {
        // 0x00477190
        charge(ctx, 8);
        lw(s4, s0, 228);
        v1 = addiu(s4, 1);
        sw(v1, s0, 228);
        lw(a0, s0, 228);
        lw(v1, s0, 232);
        at = slt(v1, a0);
        if (at != 0) {
            // 0x00477390
            charge(ctx, 2);
            sw(zero, s0, 228);
            backedge(ctx);
        }
        // 0x004771b0
        charge(ctx, 6);
        lw(a0, s2, 24);
        lw(v1, gp, -17504);  // 0x7CE890
        a0 = addu(a0, v1);
        lw(v1, a0, 0);
        a2 = 0;
        if (v1 != 0) {
            // 0x004771c8
            charge(ctx, 4);
            lw(a1, v1, 0);
            v1 = 1;
            if (a1 == v1) {
                // 0x004771d8
                charge(ctx, 1);
                a2 = v1;
            }
        }
        // 0x004771dc
        charge(ctx, 2);
        if (a2 == 0) {
            // 0x004771ec
            charge(ctx, 4);
            a1 = 1;
            jal(ctx, 0x4771ECu, gen::fn_sub_49E5A0_0049e5a0);
            a0 = v0;
            lw(v1, s0, 228);
        } else {
            // 0x004771e4
            charge(ctx, 2);
            lw(v1, s0, 228);
        }
        // 0x004771fc
        charge(ctx, 7);
        lw(a2, a0, 0);
        v1 = sll(v1, 2);
        v1 = addu(v1, s0);
        lw(a1, a2, 4);
        lw(v1, v1, 312);
        sw(v1, a2, 4);
        if (v1 != 0) {
            // 0x00477218
            charge(ctx, 7);
            lw(v1, a2, 4);
            a0 = addiu(a2, 4);
            sw(a0, v1, 16);
            lw(v1, s0, 228);
            v1 = sll(v1, 2);
            v1 = addu(v1, s0);
            sw(zero, v1, 312);
        }
        // 0x00477234
        charge(ctx, 5);
        v1 = sll(s4, 2);
        v1 = addu(v1, s0);
        sw(a1, v1, 312);
        a0 = addiu(v1, 312);
        if (a1 != 0) {
            // 0x00477248
            charge(ctx, 2);
            lw(v1, a0, 0);
            sw(a0, v1, 16);
        }
    }
    // 0x00477250
    charge(ctx, 4);
    v1 = 0x10000000;
    v1 = s1 & v1;
    lw(s4, s0, 228);
    if (v1 != 0) {
        // 0x00477398
        charge(ctx, 4);
        a0 = s5;
        jal(ctx, 0x477398u, gen::fn_sub_474A80_00474a80);
        lw(a0, s2, 24);
        backedge(ctx);
    } else {
        // 0x00477260
        charge(ctx, 1);
        lw(a0, s2, 24);
    }
    // 0x00477264
    charge(ctx, 5);
    lw(v1, gp, -17504);  // 0x7CE890
    a0 = addu(a0, v1);
    lw(v1, a0, 0);
    a2 = 0;
    if (v1 != 0) {
        // 0x00477278
        charge(ctx, 4);
        lw(a1, v1, 0);
        v1 = 1;
        if (a1 == v1) {
            // 0x00477288
            charge(ctx, 1);
            a2 = v1;
        }
    }
    // 0x0047728c
    charge(ctx, 2);
    if (a2 == 0) {
        // 0x0047729c
        charge(ctx, 4);
        a1 = 1;
        jal(ctx, 0x47729Cu, gen::fn_sub_49E5A0_0049e5a0);
        a0 = v0;
        lw(v1, a0, 0);
    } else {
        // 0x00477294
        charge(ctx, 2);
        lw(v1, a0, 0);
    }
    // 0x004772ac
    charge(ctx, 3);
    lw(v1, v1, 4);
    if (v1 == 0) {
        // 0x004773a8
        charge(ctx, 13);
        sw(zero, s3, 8);
        sw(zero, s3, 4);
        sw(zero, s3, 0);
        sw(zero, s3, 12);
        sw(zero, s3, 16);
        sw(zero, s3, 20);
        sw(zero, s3, 32);
        sw(zero, s3, 36);
        sw(zero, s3, 24);
        sw(zero, s3, 28);
        sw(zero, s3, 40);
        sw(zero, s3, 44);
        backedge(ctx);
    L_00477388:
        charge(ctx, 2);
        ld(ra, sp, 0x60);
    } else {
        // 0x004772b8
        charge(ctx, 7);
        jal(ctx, 0x4772B8u, gen::fn_sub_4D5E90_004d5e90);
        v1 = s1 & 0x2;
        v1 = v1 ^ 0x2;
        v1 = sltiu(v1, 1);
        if (v1 == 0) {
            // 0x004772d4
            charge(ctx, 3);
            v1 = s1 & 0x2000;
            v1 = v1 ^ 0x2000;
            v1 = sltiu(v1, 1);
        }
        // 0x004772e0
        charge(ctx, 6);
        sw(v1, s3, 8);
        v1 = s1 & 0x80;
        v1 = v1 ^ 0x80;
        v1 = sltiu(v1, 1);
        if (v1 == 0) {
            // 0x004772f8
            charge(ctx, 4);
            a0 = 0x80000;
            v1 = s1 & a0;
            v1 = v1 ^ a0;
            v1 = sltiu(v1, 1);
        }
        // 0x00477308
        charge(ctx, 8);
        sw(v1, s3, 4);
        v1 = 1;
        sw(v1, s3, 0);
        v1 = s1 & 0x4;
        v1 = v1 ^ 0x4;
        v1 = sltiu(v1, 1);
        if (v1 == 0) {
            // 0x00477328
            charge(ctx, 3);
            v1 = s1 & 0x4000;
            v1 = v1 ^ 0x4000;
            v1 = sltiu(v1, 1);
        }
        // 0x00477334
        charge(ctx, 4);
        sw(v1, s3, 12);
        lw(v1, s3, 0);
        if (v1 != 0) {
            // 0x004773dc
            charge(ctx, 9);
            a0 = sll(s4, 3);
            v1 = 16;
            a0 = addu(a0, s4);
            a0 = sll(a0, 2);
            a0 = addu(a0, s0);
            lw(a0, a0, 320);
            sw(a0, s3, 16);
            sw(v1, s3, 20);
            backedge(ctx);
        }
        // 0x00477344
        charge(ctx, 3);
        lw(v1, s3, 8);
        if (v1 != 0) {
            // 0x00477400
            charge(ctx, 9);
            a0 = sll(s4, 3);
            v1 = 4;
            a0 = addu(a0, s4);
            a0 = sll(a0, 2);
            a0 = addu(a0, s0);
            lw(a0, a0, 336);
            sw(a0, s3, 32);
            sw(v1, s3, 36);
            backedge(ctx);
        }
        // 0x00477350
        charge(ctx, 3);
        lw(v1, s3, 4);
        if (v1 != 0) {
            // 0x00477424
            charge(ctx, 9);
            a0 = sll(s4, 3);
            v1 = 16;
            a0 = addu(a0, s4);
            a0 = sll(a0, 2);
            a0 = addu(a0, s0);
            lw(a0, a0, 348);
            sw(a0, s3, 24);
            sw(v1, s3, 28);
            backedge(ctx);
        }
        // 0x0047735c
        charge(ctx, 3);
        lw(v1, s3, 12);
        if (v1 != 0) {
            // 0x00477368
            charge(ctx, 8);
            a0 = sll(s4, 3);
            v1 = 8;
            a0 = addu(a0, s4);
            a0 = sll(a0, 2);
            a0 = addu(a0, s0);
            lw(a0, a0, 332);
            sw(a0, s3, 40);
            sw(v1, s3, 44);
            goto L_00477388;
        }
        // 0x00477448
        charge(ctx, 1);
        ld(ra, sp, 0x60);
    }
    // 0x0047744c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00479170 sub_479170 -- 1056 bytes; frame 0xB0: ra sp+0xA0, s7 sp+0x90 (sq), s6 sp+0x80 (sq), s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// sub_479170 [3-D lock, next buffer]: the buffer ring, the instance test, the camera axes, the record.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: callee frames ($sp off / deeper stack)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_479170(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::enter, hg::jal, hg::ld,
          hg::link, hg::lq, hg::lui, hg::lw, hg::lwc1, hg::madd_s, hg::mov_s, hg::mula_s, hg::neg_s, hg::sd, hg::sll,
          hg::slt, hg::sltu, hg::sq, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26};
    // 0x00479170
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    v1 = 1;
    sd(ra, sp, 0xA0);
    sq(s7, sp, 0x90);
    sq(s6, sp, 0x80);
    s7 = a1;
    sq(s5, sp, 0x70);
    s6 = t0;
    sq(s4, sp, 0x60);
    sq(s3, sp, 0x50);
    s4 = a0;
    sq(s2, sp, 0x40);
    s3 = a2;
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    s1 = addiu(s4, 48);
    swc1(f26, sp, 0x18);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(s2, a2, 76);
    lw(a0, s2, 224);
    s0 = addiu(s4, 60);
    if (a0 == v1) {
        // 0x004791dc
        charge(ctx, 8);
        lw(s5, s2, 228);
        v1 = addiu(s5, 1);
        sw(v1, s2, 228);
        lw(a0, s2, 228);
        lw(v1, s2, 232);
        at = slt(v1, a0);
        if (at != 0) {
            // 0x004793f8
            charge(ctx, 2);
            sw(zero, s2, 228);
            backedge(ctx);
        }
        // 0x004791fc
        charge(ctx, 6);
        lw(a0, s7, 24);
        lw(v1, gp, -17504);  // 0x7CE890
        a0 = addu(a0, v1);
        lw(v1, a0, 0);
        a2 = 0;
        if (v1 != 0) {
            // 0x00479214
            charge(ctx, 4);
            lw(a1, v1, 0);
            v1 = 1;
            if (a1 == v1) {
                // 0x00479224
                charge(ctx, 1);
                a2 = v1;
            }
        }
        // 0x00479228
        charge(ctx, 2);
        if (a2 == 0) {
            // 0x00479238
            charge(ctx, 4);
            a1 = 1;
            jal(ctx, 0x479238u, gen::fn_sub_49E5A0_0049e5a0);
            a0 = v0;
            lw(v1, s2, 228);
        } else {
            // 0x00479230
            charge(ctx, 2);
            lw(v1, s2, 228);
        }
        // 0x00479248
        charge(ctx, 7);
        lw(a2, a0, 0);
        v1 = sll(v1, 2);
        v1 = addu(v1, s2);
        lw(a1, a2, 4);
        lw(v1, v1, 312);
        sw(v1, a2, 4);
        if (v1 != 0) {
            // 0x00479264
            charge(ctx, 7);
            lw(v1, a2, 4);
            a0 = addiu(a2, 4);
            sw(a0, v1, 16);
            lw(v1, s2, 228);
            v1 = sll(v1, 2);
            v1 = addu(v1, s2);
            sw(zero, v1, 312);
        }
        // 0x00479280
        charge(ctx, 5);
        v1 = sll(s5, 2);
        v1 = addu(v1, s2);
        sw(a1, v1, 312);
        a0 = addiu(v1, 312);
        if (a1 != 0) {
            // 0x00479294
            charge(ctx, 2);
            lw(v1, a0, 0);
            sw(a0, v1, 16);
        }
    }
    // 0x0047929c
    charge(ctx, 4);
    v1 = 0x10000000;
    v1 = s6 & v1;
    lw(s5, s2, 228);
    if (v1 != 0) {
        // 0x00479400
        charge(ctx, 4);
        a0 = s3;
        jal(ctx, 0x479400u, gen::fn_sub_474A80_00474a80);
        lw(a0, s7, 24);
        backedge(ctx);
    } else {
        // 0x004792ac
        charge(ctx, 1);
        lw(a0, s7, 24);
    }
    // 0x004792b0
    charge(ctx, 5);
    lw(v1, gp, -17504);  // 0x7CE890
    a0 = addu(a0, v1);
    lw(v1, a0, 0);
    a2 = 0;
    if (v1 != 0) {
        // 0x004792c4
        charge(ctx, 4);
        lw(a1, v1, 0);
        v1 = 1;
        if (a1 == v1) {
            // 0x004792d4
            charge(ctx, 1);
            a2 = v1;
        }
    }
    // 0x004792d8
    charge(ctx, 2);
    if (a2 == 0) {
        // 0x004792e8
        charge(ctx, 4);
        a1 = 1;
        jal(ctx, 0x4792E8u, gen::fn_sub_49E5A0_0049e5a0);
        a0 = v0;
        lw(v1, a0, 0);
    } else {
        // 0x004792e0
        charge(ctx, 2);
        lw(v1, a0, 0);
    }
    // 0x004792f8
    charge(ctx, 3);
    lw(v1, v1, 4);
    if (v1 == 0) {
        // 0x00479410
        charge(ctx, 13);
        sw(zero, s4, 8);
        sw(zero, s4, 4);
        sw(zero, s4, 0);
        sw(zero, s4, 12);
        sw(zero, s4, 16);
        sw(zero, s4, 20);
        sw(zero, s4, 32);
        sw(zero, s4, 36);
        sw(zero, s4, 24);
        sw(zero, s4, 28);
        sw(zero, s4, 40);
        sw(zero, s4, 44);
        backedge(ctx);
    L_004793f0:
        charge(ctx, 2);
        ld(ra, sp, 0xA0);
    } else {
        // 0x00479304
        charge(ctx, 9);
        v0 = 0x960000;
        lw(v0, v0, 112);  // 0x960070
        link(ctx, 0x47930Cu);  // $ra first: the delay slot below depends on it
        lw(a0, v0, 4);
        call(ctx, gen::fn_sub_4CB2F0_004cb2f0);
        lw(a1, s3, 88);
        v1 = 0x8000;
        a0 = a1 & 0x8000;
        if (a0 == v1) {
            // 0x00479444
            charge(ctx, 13);
            lwc1(f2, s3, 176);
            lwc1(f1, s3, 180);
            lwc1(f0, s3, 184);
            swc1(f2, s1, 0);
            swc1(f1, s1, 4);
            swc1(f0, s1, 8);
            lwc1(f2, s3, 192);
            lwc1(f1, s3, 196);
            lwc1(f0, s3, 200);
            swc1(f2, s0, 0);
            swc1(f1, s0, 4);
            swc1(f0, s0, 8);
            backedge(ctx);
        } else {
            // 0x00479328
            charge(ctx, 4);
            a0 = 0x20000;
            v1 = a1 & a0;
            if (v1 == a0) {
                // 0x00479478
                charge(ctx, 34);
                lwc1(f2, v0, 0);
                lwc1(f1, v0, 4);
                lwc1(f0, v0, 8);
                lwc1(f26, v0, 16);
                lwc1(f25, v0, 20);
                lwc1(f24, v0, 24);
                lwc1(f12, s3, 120);
                neg_s(f20, f2);
                neg_s(f21, f1);
                neg_s(f22, f0);
                jal(ctx, 0x47949Cu, gen::fn_sinf_0052e878);
                lwc1(f12, s3, 120);
                mov_s(f23, f0);
                jal(ctx, 0x4794A8u, gen::fn_cosf_0052e6d8);
                neg_s(f2, f23);
                mula_s(f2, f26);
                madd_s(f1, f0, f20);
                swc1(f1, s1, 0);
                mula_s(f2, f25);
                madd_s(f1, f0, f21);
                swc1(f1, s1, 4);
                mula_s(f2, f24);
                madd_s(f1, f0, f22);
                swc1(f1, s1, 8);
                mula_s(f0, f26);
                madd_s(f1, f23, f20);
                swc1(f1, s0, 0);
                mula_s(f0, f25);
                madd_s(f1, f23, f21);
                mula_s(f0, f24);
                madd_s(f0, f23, f22);
                swc1(f1, s0, 4);
                swc1(f0, s0, 8);
                backedge(ctx);
            } else {
                // 0x00479338
                charge(ctx, 15);
                lwc1(f0, v0, 0);
                neg_s(f0, f0);
                swc1(f0, s1, 0);
                lwc1(f0, v0, 4);
                neg_s(f0, f0);
                swc1(f0, s1, 4);
                lwc1(f0, v0, 8);
                neg_s(f0, f0);
                swc1(f0, s1, 8);
                lwc1(f0, v0, 16);
                swc1(f0, s0, 0);
                lwc1(f0, v0, 20);
                swc1(f0, s0, 4);
                lwc1(f0, v0, 24);
                swc1(f0, s0, 8);
            }
        }
        // 0x00479374
        charge(ctx, 17);
        jal(ctx, 0x479374u, gen::fn_sub_4D5E90_004d5e90);
        a0 = lui(0xFFFB);
        v1 = lui(0xFFE7);
        a0 = a0 | 0xDFBD;
        v1 = v1 | 0xFE7F;
        a0 = s6 & a0;
        v1 = s6 & v1;
        a1 = sltu(0, a0);
        a0 = sltu(0, v1);
        sw(a1, s4, 8);
        v1 = 1;
        sw(a0, s4, 4);
        sw(v1, s4, 0);
        lw(v1, s4, 0);
        if (v1 != 0) {
            // 0x00479500
            charge(ctx, 9);
            a0 = sll(s5, 3);
            v1 = 16;
            a0 = addu(a0, s5);
            a0 = sll(a0, 2);
            a0 = addu(a0, s2);
            lw(a0, a0, 320);
            sw(a0, s4, 16);
            sw(v1, s4, 20);
            backedge(ctx);
        }
        // 0x004793b8
        charge(ctx, 3);
        lw(v1, s4, 8);
        if (v1 != 0) {
            // 0x00479524
            charge(ctx, 9);
            a0 = sll(s5, 3);
            v1 = 4;
            a0 = addu(a0, s5);
            a0 = sll(a0, 2);
            a0 = addu(a0, s2);
            lw(a0, a0, 340);
            sw(a0, s4, 32);
            sw(v1, s4, 36);
            backedge(ctx);
        }
        // 0x004793c4
        charge(ctx, 3);
        lw(v1, s4, 4);
        if (v1 != 0) {
            // 0x004793d0
            charge(ctx, 8);
            a0 = sll(s5, 3);
            v1 = 8;
            a0 = addu(a0, s5);
            a0 = sll(a0, 2);
            a0 = addu(a0, s2);
            lw(a0, a0, 352);
            sw(a0, s4, 24);
            sw(v1, s4, 28);
            goto L_004793f0;
        }
        // 0x00479548
        charge(ctx, 1);
        ld(ra, sp, 0xA0);
    }
    // 0x0047954c (the shared epilogue, written out on this path)
    charge(ctx, 17);
    lwc1(f26, sp, 0x18);
    lq(s7, sp, 0x90);
    lwc1(f25, sp, 0x14);
    lq(s6, sp, 0x80);
    lwc1(f24, sp, 0x10);
    lq(s5, sp, 0x70);
    lwc1(f23, sp, 0xC);
    lq(s4, sp, 0x60);
    lwc1(f22, sp, 0x8);
    lq(s3, sp, 0x50);
    lwc1(f21, sp, 0x4);
    lq(s2, sp, 0x40);
    lwc1(f20, sp, 0x0);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    sp = addiu(sp, 0xB0);
}

// 0x00479590 sub_479590 -- 676 bytes; frame 0x90: ra sp+0x80, s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// sub_479590 [3-D lock]: the camera axes into lock +48 / +60, then the record.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: callee frames ($sp off / deeper stack)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_479590(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq,
          hg::lui, hg::lw, hg::lwc1, hg::madd_s, hg::mov_s, hg::mula_s, hg::neg_s, hg::sd, hg::sll, hg::sltu, hg::sq,
          hg::sw, hg::swc1;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26};
    // 0x00479590
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    v0 = 0x960000;
    sd(ra, sp, 0x80);
    sq(s5, sp, 0x70);
    sq(s4, sp, 0x60);
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    s3 = a0;
    sq(s1, sp, 0x30);
    s2 = a2;
    sq(s0, sp, 0x20);
    s1 = t0;
    swc1(f26, sp, 0x18);
    s5 = addiu(s3, 48);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(v0, v0, 112);  // 0x960070
    lw(s0, a2, 76);
    lw(a0, v0, 4);
    s4 = addiu(s3, 60);
    jal(ctx, 0x4795ECu, gen::fn_sub_4CB2F0_004cb2f0);
    lw(a1, s2, 88);
    v1 = 0x8000;
    a0 = a1 & 0x8000;
    if (a0 == v1) {
        // 0x004796d0
        charge(ctx, 13);
        lwc1(f2, s2, 176);
        lwc1(f1, s2, 180);
        lwc1(f0, s2, 184);
        swc1(f2, s5, 0);
        swc1(f1, s5, 4);
        swc1(f0, s5, 8);
        lwc1(f2, s2, 192);
        lwc1(f1, s2, 196);
        lwc1(f0, s2, 200);
        swc1(f2, s4, 0);
        swc1(f1, s4, 4);
        swc1(f0, s4, 8);
        backedge(ctx);
    } else {
        // 0x00479608
        charge(ctx, 4);
        a0 = 0x20000;
        v1 = a1 & a0;
        if (v1 == a0) {
            // 0x00479704
            charge(ctx, 34);
            lwc1(f2, v0, 0);
            lwc1(f1, v0, 4);
            lwc1(f0, v0, 8);
            lwc1(f26, v0, 16);
            lwc1(f25, v0, 20);
            lwc1(f24, v0, 24);
            lwc1(f12, s2, 120);
            neg_s(f20, f2);
            neg_s(f21, f1);
            neg_s(f22, f0);
            jal(ctx, 0x479728u, gen::fn_sinf_0052e878);
            lwc1(f12, s2, 120);
            mov_s(f23, f0);
            jal(ctx, 0x479734u, gen::fn_cosf_0052e6d8);
            neg_s(f2, f23);
            mula_s(f2, f26);
            madd_s(f1, f0, f20);
            swc1(f1, s5, 0);
            mula_s(f2, f25);
            madd_s(f1, f0, f21);
            swc1(f1, s5, 4);
            mula_s(f2, f24);
            madd_s(f1, f0, f22);
            swc1(f1, s5, 8);
            mula_s(f0, f26);
            madd_s(f1, f23, f20);
            swc1(f1, s4, 0);
            mula_s(f0, f25);
            madd_s(f1, f23, f21);
            mula_s(f0, f24);
            madd_s(f0, f23, f22);
            swc1(f1, s4, 4);
            swc1(f0, s4, 8);
            backedge(ctx);
        } else {
            // 0x00479618
            charge(ctx, 15);
            lwc1(f0, v0, 0);
            neg_s(f0, f0);
            swc1(f0, s5, 0);
            lwc1(f0, v0, 4);
            neg_s(f0, f0);
            swc1(f0, s5, 4);
            lwc1(f0, v0, 8);
            neg_s(f0, f0);
            swc1(f0, s5, 8);
            lwc1(f0, v0, 16);
            swc1(f0, s4, 0);
            lwc1(f0, v0, 20);
            swc1(f0, s4, 4);
            lwc1(f0, v0, 24);
            swc1(f0, s4, 8);
        }
    }
    // 0x00479654
    charge(ctx, 4);
    v0 = 0x10000000;
    v0 = s1 & v0;
    lw(s4, s0, 228);
    if (v0 != 0) {
        // 0x00479664
        charge(ctx, 2);
        a0 = s2;
        jal(ctx, 0x479664u, gen::fn_sub_474A80_00474a80);
    }
    // 0x0047966c
    charge(ctx, 17);
    jal(ctx, 0x47966Cu, gen::fn_sub_4D5E90_004d5e90);
    a0 = lui(0xFFFB);
    v1 = lui(0xFFE7);
    a0 = a0 | 0xDFBD;
    v1 = v1 | 0xFE7F;
    a0 = s1 & a0;
    v1 = s1 & v1;
    a1 = sltu(0, a0);
    a0 = sltu(0, v1);
    sw(a1, s3, 8);
    v1 = 1;
    sw(a0, s3, 4);
    sw(v1, s3, 0);
    lw(v1, s3, 0);
    if (v1 != 0) {
        // 0x0047978c
        charge(ctx, 9);
        a0 = sll(s4, 3);
        v1 = 16;
        a0 = addu(a0, s4);
        a0 = sll(a0, 2);
        a0 = addu(a0, s0);
        lw(a0, a0, 320);
        sw(a0, s3, 16);
        sw(v1, s3, 20);
        backedge(ctx);
    }
    // 0x004796b0
    charge(ctx, 3);
    lw(v1, s3, 8);
    if (v1 != 0) {
        // 0x004797b0
        charge(ctx, 9);
        a0 = sll(s4, 3);
        v1 = 4;
        a0 = addu(a0, s4);
        a0 = sll(a0, 2);
        a0 = addu(a0, s0);
        lw(a0, a0, 340);
        sw(a0, s3, 32);
        sw(v1, s3, 36);
        backedge(ctx);
    }
    // 0x004796bc
    charge(ctx, 3);
    lw(v1, s3, 4);
    if (v1 != 0) {
        // 0x004797d4
        charge(ctx, 9);
        a0 = sll(s4, 3);
        v1 = 8;
        a0 = addu(a0, s4);
        a0 = sll(a0, 2);
        a0 = addu(a0, s0);
        lw(a0, a0, 352);
        sw(a0, s3, 24);
        sw(v1, s3, 28);
        backedge(ctx);
    }
    // 0x004796c8
    charge(ctx, 2);
    ld(ra, sp, 0x80);
    // 0x004797f8
    charge(ctx, 15);
    lwc1(f26, sp, 0x18);
    lq(s5, sp, 0x70);
    lwc1(f25, sp, 0x14);
    lq(s4, sp, 0x60);
    lwc1(f24, sp, 0x10);
    lq(s3, sp, 0x50);
    lwc1(f23, sp, 0xC);
    lq(s2, sp, 0x40);
    lwc1(f22, sp, 0x8);
    lq(s1, sp, 0x30);
    lwc1(f21, sp, 0x4);
    lq(s0, sp, 0x20);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x00488550 sub_488550 -- 1580 bytes; frame 0xD0: ra sp+0xB0, fp sp+0xA0 (sq), s7 sp+0x90 (sq), s6 sp+0x80 (sq), s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// sub_488550 [3-D instance begin: lock the geometry]: $a0 the lock record, $a1 the atomic, $a2 the tank block, $a3 the
// first new vertex, $t0 the lock flags. Flag 0x800000: the geometry grew -- RpGeometry lock geometryLock(geometry, 2),
// then every vertex from $a3 to the tank's count (*(atomic + plugin offset)) gets the default normal (0x77DCB0, three
// floats, kept in the frame at sp + 192) in its 48-byte record of the morph target (+92 -> +20), eight per iteration
// while the bounds allow. Then the camera axes (lock +48 / +60), the components asked for -- +8 colours (flags 2,
// 0x2000, 0x40, 0x40000), +4 UVs (0x80, 0x100, 0x80000, 0x100000), +0 positions always, +12 normals (0x10) -- each
// locking its part of the geometry through geometryLock (2 / 8 / 16 / 4) and storing {pointer, stride}.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_488550(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::enter, hg::jal, hg::ld,
          hg::link, hg::lq, hg::lw, hg::lwc1, hg::madd_s, hg::mov_s, hg::mula_s, hg::neg_s, hg::sd, hg::sll, hg::slt,
          hg::slti, hg::sltiu, hg::sq, hg::subu, hg::sw, hg::swc1;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26};
    // 0x00488550
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    v1 = 0x800000;
    sd(ra, sp, 0xB0);
    sq(fp, sp, 0xA0);
    sq(s7, sp, 0x90);
    sq(s6, sp, 0x80);
    sq(s5, sp, 0x70);
    sq(s4, sp, 0x60);
    sq(s3, sp, 0x50);
    s4 = a0;
    sq(s2, sp, 0x40);
    s3 = a2;
    sq(s1, sp, 0x30);
    s2 = a3;
    sq(s0, sp, 0x20);
    s1 = t0;
    swc1(f26, sp, 0x18);
    v0 = s1 & v1;
    swc1(f25, sp, 0x14);
    s6 = addiu(s4, 48);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(s0, a1, 24);
    s7 = addiu(s4, 60);
    if (v0 == v1) {
        // 0x00488724
        charge(ctx, 20);
        v0 = 0x780000;
        lw(v1, gp, -17792);  // 0x7CE770
        lwc1(f2, v0, -9040);  // 0x77DCB0
        lw(fp, s0, 92);
        a0 = s0;
        v0 = 0x780000;
        lwc1(f1, v0, -9036);  // 0x77DCB4
        swc1(f2, sp, 0xC0);
        v0 = 0x780000;
        lwc1(f0, v0, -9032);  // 0x77DCB8
        swc1(f1, sp, 0xC4);
        v0 = addu(a1, v1);
        lw(v0, v0, 0);
        a1 = 2;
        lw(s5, v0, 0);
        link(ctx, 0x488760u);  // $ra first: the delay slot below depends on it
        swc1(f0, sp, 0xC8);
        call(ctx, gen::fn_geometryLock_00493370);
        at = slt(s2, s5);
        lw(a0, fp, 0x14);
        if (at == 0) {
            backedge(ctx);
        } else {
            // 0x00488774
            charge(ctx, 4);
            v0 = subu(s5, s2);
            at = slti(v0, 9);
            v1 = addiu(s5, -8);
            if (at == 0) {
                // 0x00488784
                charge(ctx, 4);
                at = slt(s5, s2);
                a1 = 0;
                v0 = 0;
                if (at == 0) {
                    // 0x00488794
                    charge(ctx, 5);
                    at = 0x7FFF0000;
                    at = at | 0xFFFF;
                    at = slt(s5, at);
                    if (at != 0) {
                        // 0x004887a8
                        charge(ctx, 2);
                        v0 = 1;
                    }
                }
                // 0x004889e8
                charge(ctx, 2);
                if (v0 == 0) {
                    backedge(ctx);
                } else {
                    // 0x004889f0
                    charge(ctx, 2);
                    at = 0x7FFF0000;
                    backedge(ctx);
                    // 0x004887b0
                    charge(ctx, 4);
                    at = at | 0xFFFF;
                    at = slt(s2, at);
                    if (at != 0) {
                        // 0x004887c0
                        charge(ctx, 1);
                        a1 = 1;
                    }
                }
                // 0x004887c4
                charge(ctx, 2);
                if (a1 != 0) {
                    // 0x004887cc
                    charge(ctx, 7);
                    lwc1(f2, sp, 0xC0);
                    v0 = sll(s2, 1);
                    lwc1(f1, sp, 0xC4);
                    v0 = addu(v0, s2);
                    lwc1(f0, sp, 0xC8);
                    v0 = sll(v0, 4);
                    a1 = addu(a0, v0);
                    for (;;) {
                        // 0x004887e8
                        charge(ctx, 100);
                        swc1(f2, a1, 0);
                        s2 = addiu(s2, 8);
                        swc1(f1, a1, 4);
                        v0 = slt(s2, v1);
                        swc1(f0, a1, 8);
                        swc1(f2, a1, 12);
                        swc1(f1, a1, 16);
                        swc1(f0, a1, 20);
                        swc1(f2, a1, 24);
                        swc1(f1, a1, 28);
                        swc1(f0, a1, 32);
                        swc1(f2, a1, 36);
                        swc1(f1, a1, 40);
                        swc1(f0, a1, 44);
                        swc1(f2, a1, 48);
                        swc1(f1, a1, 52);
                        swc1(f0, a1, 56);
                        swc1(f2, a1, 60);
                        swc1(f1, a1, 64);
                        swc1(f0, a1, 68);
                        swc1(f2, a1, 72);
                        swc1(f1, a1, 76);
                        swc1(f0, a1, 80);
                        swc1(f2, a1, 84);
                        swc1(f1, a1, 88);
                        swc1(f0, a1, 92);
                        swc1(f2, a1, 96);
                        swc1(f1, a1, 100);
                        swc1(f0, a1, 104);
                        swc1(f2, a1, 108);
                        swc1(f1, a1, 112);
                        swc1(f0, a1, 116);
                        swc1(f2, a1, 120);
                        swc1(f1, a1, 124);
                        swc1(f0, a1, 128);
                        swc1(f2, a1, 132);
                        swc1(f1, a1, 136);
                        swc1(f0, a1, 140);
                        swc1(f2, a1, 144);
                        swc1(f1, a1, 148);
                        swc1(f0, a1, 152);
                        swc1(f2, a1, 156);
                        swc1(f1, a1, 160);
                        swc1(f0, a1, 164);
                        swc1(f2, a1, 168);
                        swc1(f1, a1, 172);
                        swc1(f0, a1, 176);
                        swc1(f2, a1, 180);
                        swc1(f1, a1, 184);
                        swc1(f0, a1, 188);
                        swc1(f2, a1, 192);
                        swc1(f1, a1, 196);
                        swc1(f0, a1, 200);
                        swc1(f2, a1, 204);
                        swc1(f1, a1, 208);
                        swc1(f0, a1, 212);
                        swc1(f2, a1, 216);
                        swc1(f1, a1, 220);
                        swc1(f0, a1, 224);
                        swc1(f2, a1, 228);
                        swc1(f1, a1, 232);
                        swc1(f0, a1, 236);
                        swc1(f2, a1, 240);
                        swc1(f1, a1, 244);
                        swc1(f0, a1, 248);
                        swc1(f2, a1, 252);
                        swc1(f1, a1, 256);
                        swc1(f0, a1, 260);
                        swc1(f2, a1, 264);
                        swc1(f1, a1, 268);
                        swc1(f0, a1, 272);
                        swc1(f2, a1, 276);
                        swc1(f1, a1, 280);
                        swc1(f0, a1, 284);
                        swc1(f2, a1, 288);
                        swc1(f1, a1, 292);
                        swc1(f0, a1, 296);
                        swc1(f2, a1, 300);
                        swc1(f1, a1, 304);
                        swc1(f0, a1, 308);
                        swc1(f2, a1, 312);
                        swc1(f1, a1, 316);
                        swc1(f0, a1, 320);
                        swc1(f2, a1, 324);
                        swc1(f1, a1, 328);
                        swc1(f0, a1, 332);
                        swc1(f2, a1, 336);
                        swc1(f1, a1, 340);
                        swc1(f0, a1, 344);
                        swc1(f2, a1, 348);
                        swc1(f1, a1, 352);
                        swc1(f0, a1, 356);
                        swc1(f2, a1, 360);
                        swc1(f1, a1, 364);
                        swc1(f0, a1, 368);
                        swc1(f2, a1, 372);
                        swc1(f1, a1, 376);
                        swc1(f0, a1, 380);
                        a1 = addiu(a1, 384);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
            }
            // 0x00488978
            charge(ctx, 3);
            at = slt(s2, s5);
            if (at == 0) {
                backedge(ctx);
            } else {
                // 0x00488984
                charge(ctx, 7);
                lwc1(f2, sp, 0xC0);
                v0 = sll(s2, 1);
                lwc1(f1, sp, 0xC4);
                v0 = addu(v0, s2);
                lwc1(f0, sp, 0xC8);
                v0 = sll(v0, 4);
                v1 = addu(a0, v0);
                for (;;) {
                    // 0x004889a0
                    charge(ctx, 16);
                    swc1(f2, v1, 0);
                    s2 = addiu(s2, 1);
                    swc1(f1, v1, 4);
                    v0 = slt(s2, s5);
                    swc1(f0, v1, 8);
                    swc1(f2, v1, 12);
                    swc1(f1, v1, 16);
                    swc1(f0, v1, 20);
                    swc1(f2, v1, 24);
                    swc1(f1, v1, 28);
                    swc1(f0, v1, 32);
                    swc1(f2, v1, 36);
                    swc1(f1, v1, 40);
                    swc1(f0, v1, 44);
                    v1 = addiu(v1, 48);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004889e0
                charge(ctx, 2);
                backedge(ctx);
            }
        }
    }
    // 0x004885c0
    charge(ctx, 9);
    v0 = 0x960000;
    lw(v0, v0, 112);  // 0x960070
    link(ctx, 0x4885C8u);  // $ra first: the delay slot below depends on it
    lw(a0, v0, 4);
    call(ctx, gen::fn_sub_4CB2F0_004cb2f0);
    lw(a1, s3, 88);
    v1 = 0x8000;
    a0 = a1 & 0x8000;
    if (a0 == v1) {
        // 0x004889f8
        charge(ctx, 13);
        lwc1(f2, s3, 176);
        lwc1(f1, s3, 180);
        lwc1(f0, s3, 184);
        swc1(f2, s6, 0);
        swc1(f1, s6, 4);
        swc1(f0, s6, 8);
        lwc1(f2, s3, 192);
        lwc1(f1, s3, 196);
        lwc1(f0, s3, 200);
        swc1(f2, s7, 0);
        swc1(f1, s7, 4);
        swc1(f0, s7, 8);
        backedge(ctx);
    } else {
        // 0x004885e4
        charge(ctx, 4);
        a0 = 0x20000;
        v1 = a1 & a0;
        if (v1 == a0) {
            // 0x00488a2c
            charge(ctx, 34);
            lwc1(f2, v0, 0);
            lwc1(f1, v0, 4);
            lwc1(f0, v0, 8);
            lwc1(f26, v0, 16);
            lwc1(f25, v0, 20);
            lwc1(f24, v0, 24);
            lwc1(f12, s3, 120);
            neg_s(f20, f2);
            neg_s(f21, f1);
            neg_s(f22, f0);
            jal(ctx, 0x488A50u, gen::fn_sinf_0052e878);
            lwc1(f12, s3, 120);
            mov_s(f23, f0);
            jal(ctx, 0x488A5Cu, gen::fn_cosf_0052e6d8);
            neg_s(f2, f23);
            mula_s(f2, f26);
            madd_s(f1, f0, f20);
            swc1(f1, s6, 0);
            mula_s(f2, f25);
            madd_s(f1, f0, f21);
            swc1(f1, s6, 4);
            mula_s(f2, f24);
            madd_s(f1, f0, f22);
            swc1(f1, s6, 8);
            mula_s(f0, f26);
            madd_s(f1, f23, f20);
            swc1(f1, s7, 0);
            mula_s(f0, f25);
            madd_s(f1, f23, f21);
            mula_s(f0, f24);
            madd_s(f0, f23, f22);
            swc1(f1, s7, 4);
            swc1(f0, s7, 8);
            backedge(ctx);
        } else {
            // 0x004885f4
            charge(ctx, 15);
            lwc1(f0, v0, 0);
            neg_s(f0, f0);
            swc1(f0, s6, 0);
            lwc1(f0, v0, 4);
            neg_s(f0, f0);
            swc1(f0, s6, 4);
            lwc1(f0, v0, 8);
            neg_s(f0, f0);
            swc1(f0, s6, 8);
            lwc1(f0, v0, 16);
            swc1(f0, s7, 0);
            lwc1(f0, v0, 20);
            swc1(f0, s7, 4);
            lwc1(f0, v0, 24);
            swc1(f0, s7, 8);
        }
    }
    // 0x00488630
    charge(ctx, 5);
    v1 = s1 & 0x2;
    v1 = v1 ^ 0x2;
    v1 = sltiu(v1, 1);
    if (v1 == 0) {
        // 0x00488644
        charge(ctx, 3);
        v1 = s1 & 0x2000;
        v1 = v1 ^ 0x2000;
        v1 = sltiu(v1, 1);
    }
    // 0x00488650
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x00488658
        charge(ctx, 3);
        v1 = s1 & 0x40;
        v1 = v1 ^ 0x40;
        v1 = sltiu(v1, 1);
    }
    // 0x00488664
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x0048866c
        charge(ctx, 4);
        a0 = 0x40000;
        v1 = s1 & a0;
        v1 = v1 ^ a0;
        v1 = sltiu(v1, 1);
    }
    // 0x0048867c
    charge(ctx, 6);
    sw(v1, s4, 8);
    v1 = s1 & 0x80;
    v1 = v1 ^ 0x80;
    v1 = sltiu(v1, 1);
    if (v1 == 0) {
        // 0x00488694
        charge(ctx, 3);
        v1 = s1 & 0x100;
        v1 = v1 ^ 0x100;
        v1 = sltiu(v1, 1);
    }
    // 0x004886a0
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x004886a8
        charge(ctx, 4);
        a0 = 0x80000;
        v1 = s1 & a0;
        v1 = v1 ^ a0;
        v1 = sltiu(v1, 1);
    }
    // 0x004886b8
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x004886c0
        charge(ctx, 4);
        a0 = 0x100000;
        v1 = s1 & a0;
        v1 = v1 ^ a0;
        v1 = sltiu(v1, 1);
    }
    // 0x004886d0
    charge(ctx, 10);
    sw(v1, s4, 4);
    a0 = 1;
    v1 = s1 & 0x10;
    sw(a0, s4, 0);
    v1 = v1 ^ 0x10;
    v1 = sltiu(v1, 1);
    sw(v1, s4, 12);
    lw(v1, s4, 0);
    lw(s1, s0, 92);
    if (v1 != 0) {
        // 0x00488ab4
        charge(ctx, 8);
        a0 = s0;
        a1 = 2;
        jal(ctx, 0x488AB8u, gen::fn_geometryLock_00493370);
        lw(a0, s1, 20);
        v1 = 12;
        sw(a0, s4, 16);
        sw(v1, s4, 20);
        backedge(ctx);
    }
    // 0x004886f8
    charge(ctx, 3);
    lw(v1, s4, 8);
    if (v1 != 0) {
        // 0x00488ad4
        charge(ctx, 8);
        a0 = s0;
        a1 = 8;
        jal(ctx, 0x488AD8u, gen::fn_geometryLock_00493370);
        lw(a0, s0, 48);
        v1 = 4;
        sw(a0, s4, 32);
        sw(v1, s4, 36);
        backedge(ctx);
    }
    // 0x00488704
    charge(ctx, 3);
    lw(v1, s4, 4);
    if (v1 != 0) {
        // 0x00488af4
        charge(ctx, 8);
        a0 = s0;
        a1 = 16;
        jal(ctx, 0x488AF8u, gen::fn_geometryLock_00493370);
        lw(a0, s0, 52);
        v1 = 8;
        sw(a0, s4, 24);
        sw(v1, s4, 28);
        backedge(ctx);
    }
    // 0x00488710
    charge(ctx, 3);
    lw(v1, s4, 12);
    if (v1 != 0) {
        // 0x00488b14
        charge(ctx, 8);
        a0 = s0;
        a1 = 4;
        jal(ctx, 0x488B18u, gen::fn_geometryLock_00493370);
        lw(a0, s1, 24);
        v1 = 12;
        sw(a0, s4, 40);
        sw(v1, s4, 44);
        backedge(ctx);
    }
    // 0x0048871c
    charge(ctx, 2);
    ld(ra, sp, 0xB0);
    // 0x00488b34
    charge(ctx, 18);
    lwc1(f26, sp, 0x18);
    lq(fp, sp, 0xA0);
    lwc1(f25, sp, 0x14);
    lq(s7, sp, 0x90);
    lwc1(f24, sp, 0x10);
    lq(s6, sp, 0x80);
    lwc1(f23, sp, 0xC);
    lq(s5, sp, 0x70);
    lwc1(f22, sp, 0x8);
    lq(s4, sp, 0x60);
    lwc1(f21, sp, 0x4);
    lq(s3, sp, 0x50);
    lwc1(f20, sp, 0x0);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    sp = addiu(sp, 0xD0);
}

// 0x004866C0 sub_4866C0 -- 704 bytes; leaf frame (no stack)
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's.
void sub_4866C0(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28};
    // 0x004866c0
    enter(ctx, 11);  // entry check point + this block's cycles
    lw(a2, gp, -17792);  // 0x7CE770
    v1 = 0x490000;
    v1 = addiu(v1, -31408);  // &sub_488550
    a1 = 8;
    a0 = addu(a0, a2);
    lw(a0, a0, 0);
    sw(v1, a0, 36);
    lw(a3, a0, 168);
    a2 = a3 & 0x8;
    v1 = addiu(a0, 80);
    if (a2 != a1) {
        // 0x0048671c
        charge(ctx, 4);
        a2 = a3 & 0x8000;
        a1 = 0x8000;
        if (a2 != a1) {
            // 0x0048675c
            charge(ctx, 4);
            a2 = a3 & 0x20;
            a1 = 32;
            if (a2 != a1) {
                // 0x004867dc
                charge(ctx, 4);
                a2 = a3 & 0x4;
                a1 = 4;
                if (a2 != a1) {
                    // 0x0048681c
                    charge(ctx, 4);
                    a2 = 0x1000000;
                    a1 = a3 & a2;
                    if (a1 != a2) {
                        // 0x0048683c
                        charge(ctx, 3);
                        a1 = 0x480000;
                        a1 = addiu(a1, 27008);  // &sub_486980
                        sw(a1, a0, 40);
                    } else {
                        // 0x0048682c
                        charge(ctx, 4);
                        a1 = 0x480000;
                        a1 = addiu(a1, 27360);  // &sub_486AE0
                        sw(a1, a0, 40);
                    }
                } else {
                    // 0x004867ec
                    charge(ctx, 4);
                    a2 = 0x1000000;
                    a1 = a3 & a2;
                    if (a1 != a2) {
                        // 0x0048680c
                        charge(ctx, 4);
                        a1 = 0x480000;
                        a1 = addiu(a1, 28352);  // &sub_486EC0
                        sw(a1, a0, 40);
                    } else {
                        // 0x004867fc
                        charge(ctx, 4);
                        a1 = 0x480000;
                        a1 = addiu(a1, 29984);  // &sub_487520
                        sw(a1, a0, 40);
                    }
                }
            } else {
                // 0x0048676c
                charge(ctx, 4);
                a2 = a3 & 0x4;
                a1 = 4;
                if (a2 != a1) {
                    // 0x004867ac
                    charge(ctx, 4);
                    a2 = 0x1000000;
                    a1 = a3 & a2;
                    if (a1 != a2) {
                        // 0x004867cc
                        charge(ctx, 4);
                        a1 = 0x480000;
                        a1 = addiu(a1, 27776);  // &sub_486C80
                        sw(a1, a0, 40);
                    } else {
                        // 0x004867bc
                        charge(ctx, 4);
                        a1 = 0x480000;
                        a1 = addiu(a1, 29312);  // &sub_487280
                        sw(a1, a0, 40);
                    }
                } else {
                    // 0x0048677c
                    charge(ctx, 4);
                    a2 = 0x1000000;
                    a1 = a3 & a2;
                    if (a1 != a2) {
                        // 0x0048679c
                        charge(ctx, 4);
                        a1 = 0x480000;
                        a1 = addiu(a1, 28720);  // &sub_487030
                        sw(a1, a0, 40);
                    } else {
                        // 0x0048678c
                        charge(ctx, 4);
                        a1 = 0x480000;
                        a1 = addiu(a1, 30448);  // &sub_4876F0
                        sw(a1, a0, 40);
                    }
                }
            }
        } else {
            // 0x0048672c
            charge(ctx, 4);
            a2 = 0x1000000;
            a1 = a3 & a2;
            if (a1 != a2) {
                // 0x0048674c
                charge(ctx, 4);
                a1 = 0x480000;
                a1 = addiu(a1, 27008);  // &sub_486980
                sw(a1, a0, 40);
            } else {
                // 0x0048673c
                charge(ctx, 4);
                a1 = 0x480000;
                a1 = addiu(a1, 27360);  // &sub_486AE0
                sw(a1, a0, 40);
            }
        }
    } else {
        // 0x004866ec
        charge(ctx, 4);
        a2 = 0x1000000;
        a1 = a3 & a2;
        if (a1 != a2) {
            // 0x0048670c
            charge(ctx, 4);
            a1 = 0x480000;
            a1 = addiu(a1, 31120);  // &sub_487990
            sw(a1, a0, 40);
        } else {
            // 0x004866fc
            charge(ctx, 4);
            a1 = 0x480000;
            a1 = addiu(a1, 31424);  // &sub_487AC0
            sw(a1, a0, 40);
        }
    }
    // 0x00486848
    charge(ctx, 5);
    lw(a3, v1, 88);
    a1 = 128;
    a2 = a3 & 0x80;
    if (a2 == a1) {
        // 0x00486928
        charge(ctx, 4);
        a1 = 0x490000;
        a1 = addiu(a1, -32160);  // &sub_488260
        sw(a1, a0, 44);
        backedge(ctx);
    } else {
        // 0x0048685c
        charge(ctx, 4);
        a2 = a3 & 0x100;
        a1 = 256;
        if (a2 == a1) {
            // 0x00486938
            charge(ctx, 4);
            a1 = 0x490000;
            a1 = addiu(a1, -32016);  // &sub_4882F0
            sw(a1, a0, 44);
            backedge(ctx);
        } else {
            // 0x0048686c
            charge(ctx, 4);
            a2 = 0x80000;
            a1 = a3 & a2;
            if (a1 == a2) {
                // 0x00486948
                charge(ctx, 4);
                a1 = 0x490000;
                a1 = addiu(a1, -31856);  // &sub_488390
                sw(a1, a0, 44);
                backedge(ctx);
            } else {
                // 0x0048687c
                charge(ctx, 4);
                a2 = 0x100000;
                a1 = a3 & a2;
                if (a1 != a2) {
                    // 0x0048689c
                    charge(ctx, 1);
                    sw(zero, a0, 44);
                } else {
                    // 0x0048688c
                    charge(ctx, 4);
                    a1 = 0x490000;
                    a1 = addiu(a1, -31728);  // &sub_488410
                    sw(a1, a0, 44);
                }
            }
        }
    }
    // 0x004868a0
    charge(ctx, 5);
    lw(a3, v1, 88);
    a1 = 2;
    a2 = a3 & 0x2;
    if (a2 == a1) {
        // 0x00486958
        charge(ctx, 4);
        a1 = 0x480000;
        a1 = addiu(a1, 31728);  // &sub_487BF0
        sw(a1, a0, 48);
        backedge(ctx);
    } else {
        // 0x004868b4
        charge(ctx, 4);
        a2 = a3 & 0x40;
        a1 = 64;
        if (a2 == a1) {
            // 0x00486968
            charge(ctx, 4);
            a1 = 0x480000;
            a1 = addiu(a1, 32384);  // &sub_487E80
            sw(a1, a0, 48);
            backedge(ctx);
        } else {
            // 0x004868c4
            charge(ctx, 4);
            a2 = 0x40000;
            a1 = a3 & a2;
            if (a1 != a2) {
                // 0x004868e4
                charge(ctx, 3);
                a1 = 0x490000;
                a1 = addiu(a1, -32592);  // &sub_4880B0
                sw(a1, a0, 48);
            } else {
                // 0x004868d4
                charge(ctx, 4);
                a1 = 0x480000;
                a1 = addiu(a1, 32496);  // &sub_487EF0
                sw(a1, a0, 48);
            }
        }
    }
    // 0x004868f0
    charge(ctx, 5);
    lw(a1, v1, 88);
    v1 = 16;
    a1 = a1 & 0x10;
    if (a1 != v1) {
        // 0x00486914
        charge(ctx, 1);
        sw(zero, a0, 52);
    } else {
        // 0x00486904
        charge(ctx, 4);
        v1 = 0x490000;
        v1 = addiu(v1, -31584);  // &sub_4884A0
        sw(v1, a0, 52);
    }
    // 0x00486918
    charge(ctx, 4);
    v1 = 0x490000;
    v1 = addiu(v1, -29824);  // &sub_488B80
    sw(v1, a0, 56);
    // 0x00486978
    charge(ctx, 2);
}

// 0x0047BF80 sub_47BF80 -- 700 bytes; leaf frame (no stack)
// sub_485110 [constant vertex colours] / sub_485440 [constant colour] (3-D writers of sub_47BF80, four vertices a
// particle): $a0 the stream, $a1 the count, $a2 the tank.
// Vertex k of every particle gets the word at +128 + 4k (sub_485110) or +124 (sub_485440), re-read for every vertex;
// a stream of packed words (stride 4) is filled by the scratchpad streamers instead: sub_476720 with the 16-byte
// pattern copied to the frame (sp + 368) / sub_476140 with the word, count * 4 * 4 bytes. The eight-way loop keeps
// 15 vertex addresses and its test in the frame (sp + 160 .. sp + 352).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_47BF80(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28};
    // 0x0047bf80
    enter(ctx, 11);  // entry check point + this block's cycles
    lw(a2, gp, -17792);  // 0x7CE770
    v1 = 0x490000;
    v1 = addiu(v1, -31408);  // &sub_488550
    a1 = 8;
    a0 = addu(a0, a2);
    lw(a0, a0, 0);
    sw(v1, a0, 36);
    lw(a3, a0, 168);
    a2 = a3 & 0x8;
    v1 = addiu(a0, 80);
    if (a2 != a1) {
        // 0x0047bfdc
        charge(ctx, 4);
        a2 = a3 & 0x8000;
        a1 = 0x8000;
        if (a2 != a1) {
            // 0x0047c01c
            charge(ctx, 4);
            a2 = a3 & 0x20;
            a1 = 32;
            if (a2 != a1) {
                // 0x0047c09c
                charge(ctx, 4);
                a2 = a3 & 0x4;
                a1 = 4;
                if (a2 != a1) {
                    // 0x0047c0dc
                    charge(ctx, 4);
                    a2 = 0x1000000;
                    a1 = a3 & a2;
                    if (a1 != a2) {
                        // 0x0047c0fc
                        charge(ctx, 3);
                        a1 = 0x480000;
                        a1 = addiu(a1, -15808);  // &sub_47C240
                        sw(a1, a0, 40);
                    } else {
                        // 0x0047c0ec
                        charge(ctx, 4);
                        a1 = 0x480000;
                        a1 = addiu(a1, -14144);  // &sub_47C8C0
                        sw(a1, a0, 40);
                    }
                } else {
                    // 0x0047c0ac
                    charge(ctx, 4);
                    a2 = 0x1000000;
                    a1 = a3 & a2;
                    if (a1 != a2) {
                        // 0x0047c0cc
                        charge(ctx, 4);
                        a1 = 0x480000;
                        a1 = addiu(a1, -8656);  // &sub_47DE30
                        sw(a1, a0, 40);
                    } else {
                        // 0x0047c0bc
                        charge(ctx, 4);
                        a1 = 0x480000;
                        a1 = addiu(a1, 3120);  // &sub_480C30
                        sw(a1, a0, 40);
                    }
                }
            } else {
                // 0x0047c02c
                charge(ctx, 4);
                a2 = a3 & 0x4;
                a1 = 4;
                if (a2 != a1) {
                    // 0x0047c06c
                    charge(ctx, 4);
                    a2 = 0x1000000;
                    a1 = a3 & a2;
                    if (a1 != a2) {
                        // 0x0047c08c
                        charge(ctx, 4);
                        a1 = 0x480000;
                        a1 = addiu(a1, -12336);  // &sub_47CFD0
                        sw(a1, a0, 40);
                    } else {
                        // 0x0047c07c
                        charge(ctx, 4);
                        a1 = 0x480000;
                        a1 = addiu(a1, -1264);  // &sub_47FB10
                        sw(a1, a0, 40);
                    }
                } else {
                    // 0x0047c03c
                    charge(ctx, 4);
                    a2 = 0x1000000;
                    a1 = a3 & a2;
                    if (a1 != a2) {
                        // 0x0047c05c
                        charge(ctx, 4);
                        a1 = 0x480000;
                        a1 = addiu(a1, -5664);  // &sub_47E9E0
                        sw(a1, a0, 40);
                    } else {
                        // 0x0047c04c
                        charge(ctx, 4);
                        a1 = 0x480000;
                        a1 = addiu(a1, 6240);  // &sub_481860
                        sw(a1, a0, 40);
                    }
                }
            }
        } else {
            // 0x0047bfec
            charge(ctx, 4);
            a2 = 0x1000000;
            a1 = a3 & a2;
            if (a1 != a2) {
                // 0x0047c00c
                charge(ctx, 4);
                a1 = 0x480000;
                a1 = addiu(a1, -15808);  // &sub_47C240
                sw(a1, a0, 40);
            } else {
                // 0x0047bffc
                charge(ctx, 4);
                a1 = 0x480000;
                a1 = addiu(a1, -14144);  // &sub_47C8C0
                sw(a1, a0, 40);
            }
        }
    } else {
        // 0x0047bfac
        charge(ctx, 4);
        a2 = 0x1000000;
        a1 = a3 & a2;
        if (a1 != a2) {
            // 0x0047bfcc
            charge(ctx, 4);
            a1 = 0x480000;
            a1 = addiu(a1, 10832);  // &sub_482A50
            sw(a1, a0, 40);
        } else {
            // 0x0047bfbc
            charge(ctx, 4);
            a1 = 0x480000;
            a1 = addiu(a1, 12656);  // &sub_483170
            sw(a1, a0, 40);
        }
    }
    // 0x0047c108
    charge(ctx, 5);
    lw(a3, v1, 88);
    a1 = 128;
    a2 = a3 & 0x80;
    if (a2 == a1) {
        // 0x0047c1d4
        charge(ctx, 4);
        a1 = 0x480000;
        a1 = addiu(a1, 22352);  // &sub_485750
        sw(a1, a0, 44);
        backedge(ctx);
    } else {
        // 0x0047c11c
        charge(ctx, 4);
        a2 = a3 & 0x100;
        a1 = 256;
        if (a2 == a1) {
            // 0x0047c1e4
            charge(ctx, 4);
            a1 = 0x480000;
            a1 = addiu(a1, 24096);  // &sub_485E20
            sw(a1, a0, 44);
            backedge(ctx);
        } else {
            // 0x0047c12c
            charge(ctx, 4);
            a2 = 0x80000;
            a1 = a3 & a2;
            if (a1 == a2) {
                // 0x0047c1f4
                charge(ctx, 4);
                a1 = 0x480000;
                a1 = addiu(a1, 24304);  // &sub_485EF0
                sw(a1, a0, 44);
                backedge(ctx);
            } else {
                // 0x0047c13c
                charge(ctx, 4);
                a2 = 0x100000;
                a1 = a3 & a2;
                if (a1 != a2) {
                    // 0x0047c15c
                    charge(ctx, 1);
                    sw(zero, a0, 44);
                } else {
                    // 0x0047c14c
                    charge(ctx, 4);
                    a1 = 0x480000;
                    a1 = addiu(a1, 24560);  // &sub_485FF0
                    sw(a1, a0, 44);
                }
            }
        }
    }
    // 0x0047c160
    charge(ctx, 5);
    lw(a3, v1, 88);
    a1 = 2;
    a2 = a3 & 0x2;
    if (a2 == a1) {
        // 0x0047c204
        charge(ctx, 4);
        a1 = 0x480000;
        a1 = addiu(a1, 14560);  // &sub_4838E0
        sw(a1, a0, 48);
        backedge(ctx);
    } else {
        // 0x0047c174
        charge(ctx, 4);
        a2 = a3 & 0x40;
        a1 = 64;
        if (a2 == a1) {
            // 0x0047c214
            charge(ctx, 4);
            a1 = 0x480000;
            a1 = addiu(a1, 20592);  // &sub_485070
            sw(a1, a0, 48);
            backedge(ctx);
        } else {
            // 0x0047c184
            charge(ctx, 4);
            a2 = 0x40000;
            a1 = a3 & a2;
            if (a1 != a2) {
                // 0x0047c1a4
                charge(ctx, 3);
                a1 = 0x480000;
                a1 = addiu(a1, 21568);  // &sub_485440
                sw(a1, a0, 48);
            } else {
                // 0x0047c194
                charge(ctx, 4);
                a1 = 0x480000;
                a1 = addiu(a1, 20752);  // &sub_485110
                sw(a1, a0, 48);
            }
        }
    }
    // 0x0047c1b0
    charge(ctx, 5);
    lw(a1, v1, 88);
    v1 = 16;
    a1 = a1 & 0x10;
    if (a1 == v1) {
        // 0x0047c224
        charge(ctx, 4);
        v1 = 0x480000;
        v1 = addiu(v1, 24832);  // &sub_486100
        sw(v1, a0, 52);
        backedge(ctx);
    }
    // 0x0047c1c4
    charge(ctx, 4);
    v1 = 0x490000;
    v1 = addiu(v1, -29824);  // &sub_488B80
    sw(v1, a0, 56);
    // 0x0047c234
    charge(ctx, 2);
}

// 0x00478520 sub_478520 -- 1360 bytes; frame 0x100: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_478520 [2-D bridge] / sub_479900 [3-D bridge]: $a0 the PS2All pipe data (mesh.h `pd`: +4 the material pipeline's
// private data, +8 the atomic, +40 transType, +43 the VU1 code index, +48 the resEntry slot, +64 the texture, +68 the
// material colour). The vertex count (the particle count, x4 in 3-D) is split into batches of the pipeline's
// (+496 +8) size: s0 = ceil(count / batch); a stale instance (pipeline +220 == 1 and the cluster's counts differ)
// re-instances through ps2AllInstanceDmaChain first. The packet: CLAMP (sub_4749A0) and the texture (sub_4748C0) into the tank
// block, then a 12-qw VIF packet -- an UNPACK header, the viewport scale (-1/4 or -1/2 of the camera raster's width /
// height times the view window, at sp + 240 with the batch count and the last batch's size), the two clip-vector
// templates (0x965910 / 0x965920), the GIF tag (fog, texture and ABE bits; ABE when the tank's +180 is 1), A+D
// ALPHA_2 / CLAMP_2 / TEST_2 / TEX1_2 of the tank's pipeline record (+184 .. +208) and ZBUF_2 from the ZBUF_1 shadow;
// a second packet with the material colour (sub_49CAB0, scale 1/255 or 0x3B011B50 for a textured batch), the VU1 code
// index (+43 from transType bit 0 and the stale test), a DMA `call` of the
// program when it is not the resident one (gp-16888), and the DMA `ref` of the instanced clusters (reference counted
// under DI / EI, the first use -> _rwDMAAddPURef). Returns 1, or 0 when no packet could be opened.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_478520(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::cvt_s_w, hg::di, hg::divu,
          hg::dsll, hg::dsll32, hg::dsra32, hg::dsrl32, hg::ei, hg::enter, hg::jal, hg::lbu, hg::ld, hg::link,
          hg::lq, hg::lw, hg::lwc1, hg::lwu, hg::mfc0, hg::mflo, hg::mtc1, hg::mul_s, hg::mult, hg::neg_s,
          hg::pcpyld, hg::sb, hg::sd, hg::sll, hg::sq, hg::subu, hg::sw, hg::swc1, hg::sync;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f12{ctx, 12};
    // 0x00478520
    enter(ctx, 36);  // entry check point + this block's cycles
    sp = addiu(sp, -0x100);
    v0 = 0x960000;
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    fp = 0;
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    s6 = 0;
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s2, a0, 8);
    lw(v1, a0, 4);
    lw(s5, v0, 112);  // 0x960070
    lw(a0, gp, -17792);  // 0x7CE770
    v0 = addiu(v1, 496);
    lw(s7, s5, 96);
    sq(v0, sp, 0xD0);
    lw(v1, v1, 504);
    v0 = addu(s2, a0);
    lw(a0, v0, 0);
    lw(s1, a0, 4);
    v0 = addiu(v1, -1);
    lw(s3, a0, 156);
    v0 = addu(s1, v0);
    divu(v0, v1);
    lw(v1, s3, 220);
    mflo(s0);
    v0 = 1;
    sd(zero, sp, 0xE8);
    if (v1 == v0) {
        // 0x004785b0
        charge(ctx, 6);
        lw(v0, s4, 48);
        lw(v0, v0, 0);
        v1 = addiu(v0, 24);
        lw(v0, v0, 36);
        if (s1 == v0) {
            // 0x004785c8
            charge(ctx, 3);
            lw(v0, v1, 28);
            if (v0 != s0) {
                goto L_00478a10;
            }
            goto L_004785d4;
        }
    L_00478a10:
        charge(ctx, 6);
        sw(s1, v1, 12);
        a0 = s4;
        link(ctx, 0x478A18u);  // $ra first: the delay slot below depends on it
        sw(s0, v1, 28);
        call(ctx, gen::fn_ps2AllInstanceDmaChain_0049dc70);
        lw(a1, s4, 64);
        backedge(ctx);
        goto L_004785d8;
    }
L_004785d4:
    charge(ctx, 1);
    lw(a1, s4, 64);
L_004785d8:
    charge(ctx, 2);
    if (a1 != 0) {
        // 0x004785e0
        charge(ctx, 1);
        s6 = 1;
    }
    // 0x004785e4
    charge(ctx, 22);
    lw(v0, gp, -17792);  // 0x7CE770
    v0 = addu(s2, v0);
    lw(v0, v0, 0);
    a0 = addiu(v0, 80);
    jal(ctx, 0x4785F0u, gen::fn_sub_4749A0_004749a0);
    lw(v0, gp, -17792);  // 0x7CE770
    lw(a1, s4, 64);
    v0 = addu(s2, v0);
    lw(v0, v0, 0);
    a0 = addiu(v0, 80);
    jal(ctx, 0x478608u, gen::fn_sub_4748C0_004748c0);
    ld(v0, s3, 184);
    a0 = 0;
    a1 = 12;
    sq(v0, sp, 0xC0);
    ld(v0, s3, 200);
    sq(v0, sp, 0xB0);
    ld(v0, s3, 192);
    link(ctx, 0x47862Cu);  // $ra first: the delay slot below depends on it
    sq(v0, sp, 0xA0);
    call(ctx, gen::fn__rwDMAOpenVIFPkt_004d59d0);
    if (v0 == 0) {
        // 0x00478a28
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x0047863c
        charge(ctx, 54);
        v1 = 0x6C0A0000;
        v0 = 0x1000000;
        a0 = v1 | 0x3C6;
        v1 = v0 | 0x404;  // &0x1000404
        a0 = dsll32(a0, 0);
        v0 = 0x10000000;
        v1 = v1 | a0;
        v0 = v0 | 0xA;
        pcpyld(a1, v1, v0);
        sw(s0, sp, 0xF8);
        lw(v1, gp, -17148);  // 0x7CE9F4
        v0 = 0x3E800000;
        mtc1(v0, f2);
        a0 = addiu(s0, -1);
        sq(a1, v1, 0);
        lw(v0, gp, -17148);  // 0x7CE9F4
        v1 = addiu(v0, 16);
        sw(v1, gp, -17148);  // 0x7CE9F4
        lwc1(f1, s7, 16);
        lq(v0, sp, 0xD0);
        lwc1(f0, s5, 116);
        lwc1(f4, s7, 12);
        lwc1(f3, s5, 112);
        cvt_s_w(f1, f1);
        lw(v0, v0, 8);
        mul_s(f0, f1, f0);
        cvt_s_w(f1, f4);
        mul_s(f1, f1, f3);
        mul_s(f1, f2, f1);
        mul_s(f0, f2, f0);
        neg_s(f1, f1);
        neg_s(f0, f0);
        swc1(f1, sp, 0xF0);
        swc1(f0, sp, 0xF4);
        mult(a1, a0, v0);
        lw(a2, gp, -17148);  // 0x7CE9F4
        v1 = 0x960000;
        a1 = subu(s1, a1);
        v0 = 0x960000;
        sw(a1, sp, 0xFC);
        a0 = 1;
        lq(a1, sp, 0xF0);
        sq(a1, a2, 0);
        lq(v1, v1, 22800);  // 0x965910
        sq(v1, a2, 16);
        lq(v0, v0, 22816);  // 0x965920
        sq(v0, a2, 32);
        lw(v0, gp, -17148);  // 0x7CE9F4
        v1 = addiu(v0, 48);
        sw(v1, gp, -17148);  // 0x7CE9F4
        lbu(v0, s4, 40);
        v0 = v0 & 0x1;
        if (v0 == a0) {
            // 0x00478714
            charge(ctx, 1);
            fp = a0;
        }
        // 0x00478718
        charge(ctx, 7);
        lw(a0, gp, -17792);  // 0x7CE770
        v0 = 1;
        a0 = addu(s2, a0);
        lw(a0, a0, 0);
        lw(a0, a0, 180);
        if (a0 == v0) {
            // 0x00478734
            charge(ctx, 1);
            sd(v0, sp, 0xE8);
        }
        // 0x00478738
        charge(ctx, 79);
        ld(v0, sp, 0xE8);
        a2 = 0x40000;
        a2 = a2 | 0x2412;
        a0 = dsll(v0, 6);
        v0 = dsll(fp, 5);
        a0 = a0 | 0x200;
        a1 = a0 | v0;
        a0 = dsll(s6, 4);
        v0 = 0x50000000;
        a0 = a0 | a1;
        v0 = v0 | 0x4000;
        a0 = a0 | 0xE;
        a0 = dsll32(a0, 0);
        a0 = dsra32(a0, 0);
        a0 = sll(a0, 15);
        a0 = dsll32(a0, 0);
        a0 = dsrl32(a0, 0);
        v0 = a0 | v0;
        v0 = dsll32(v0, 0);
        pcpyld(v0, a2, v0);
        a1 = dsll32(v1, 0);
        a0 = 14;
        a1 = dsra32(a1, 0);
        sq(v0, a1, 0);
        v0 = 0x10000000;
        v1 = dsll32(v0, 0);
        v0 = 0x8005;
        v0 = v0 | v1;
        pcpyld(v0, a0, v0);
        sq(v0, a1, 16);
        v1 = 67;
        lq(v0, sp, 0xC0);
        pcpyld(v0, v1, v0);
        sq(v0, a1, 32);
        v1 = 9;
        lq(v0, sp, 0xA0);
        pcpyld(v0, v1, v0);
        sq(v0, a1, 48);
        v1 = 72;
        lq(v0, sp, 0xB0);
        pcpyld(v0, v1, v0);
        sq(v0, a1, 64);
        a0 = 21;
        lw(v0, gp, -17148);  // 0x7CE9F4
        v1 = addiu(v0, 80);
        sw(v1, gp, -17148);  // 0x7CE9F4
        ld(v0, s3, 208);
        pcpyld(v0, a0, v0);
        lw(a0, gp, -17148);  // 0x7CE9F4
        v1 = 79;
        sq(v0, a0, 0);
        ld(v0, gp, -17088);  // 0x7CEA30
        pcpyld(v0, v1, v0);
        sq(v0, a0, 16);
        a1 = 5;
        lw(v0, gp, -17148);  // 0x7CE9F4
        a0 = 0;
        v1 = addiu(v0, 32);
        link(ctx, 0x478820u);  // $ra first: the delay slot below depends on it
        sw(v1, gp, -17148);  // 0x7CE9F4
        call(ctx, gen::fn__rwDMAOpenVIFPkt_004d59d0);
        v0 = 0x10000000;
        v1 = 0;
        v0 = v0 | 0x2;
        pcpyld(a2, v1, v0);
        lw(a0, gp, -17148);  // 0x7CE9F4
        v1 = 0x6C010000;
        v0 = 0x1000000;
        v1 = v1 | 0x3FB;
        v0 = v0 | 0x404;  // &0x1000404
        v1 = dsll32(v1, 0);
        a1 = 0;
        v0 = v0 | v1;
        sq(a2, a0, 0);
        pcpyld(v0, v0, a1);
        sq(v0, a0, 16);
        lw(v0, gp, -17148);  // 0x7CE9F4
        v1 = addiu(v0, 32);
        sw(v1, gp, -17148);  // 0x7CE9F4
        if (s6 == 0) {
            // 0x00478888
            charge(ctx, 4);
            v0 = 0x3B800000;
            v0 = v0 | 0x8081;
            mtc1(v0, f12);
            a0 = addiu(s4, 68);
        } else {
            // 0x00478874
            charge(ctx, 5);
            v0 = 0x3B010000;
            v0 = v0 | 0x1B50;
            mtc1(v0, f12);
            a0 = addiu(s4, 68);
        }
        // 0x00478898
        charge(ctx, 6);
        jal(ctx, 0x478898u, gen::fn_sub_49CAB0_0049cab0);
        lw(v0, s3, 220);
        a0 = 1;
        if (v0 != a0) {
            // 0x004788b0
            charge(ctx, 7);
            lw(v0, gp, -17792);  // 0x7CE770
            v0 = addu(s2, v0);
            lw(v0, v0, 0);
            lw(v1, v0, 4);
            lw(v0, v0, 0);
            if (v1 == v0) {
                goto L_004788cc;
            }
            // 0x004788f0
            charge(ctx, 4);
            lbu(v0, s4, 40);
            v0 = v0 & 0x1;
            if (v0 != a0) {
                // 0x0047890c
                charge(ctx, 2);
                v0 = 3;
                sb(v0, s4, 43);
            } else {
                // 0x00478900
                charge(ctx, 3);
                v0 = 2;
                sb(v0, s4, 43);
            }
            goto L_00478914;
        }
    L_004788cc:
        charge(ctx, 5);
        lbu(v1, s4, 40);
        v0 = 1;
        v1 = v1 & 0x1;
        if (v1 != v0) {
            // 0x004788e8
            charge(ctx, 2);
            sb(v0, s4, 43);
        } else {
            // 0x004788e0
            charge(ctx, 2);
            sb(zero, s4, 43);
        }
    L_00478914:
        charge(ctx, 9);
        lw(v1, s4, 4);
        lbu(a0, s4, 43);
        lw(v0, gp, -16888);  // 0x7CEAF8
        lw(v1, v1, 24);
        a0 = sll(a0, 2);
        v1 = addu(v1, a0);
        lw(a0, v1, 0);
        if (v0 != a0) {
            // 0x00478938
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
        // 0x0047896c
        charge(ctx, 21);
        lw(a0, s4, 48);
        a2 = 0x2000000;
        lw(v1, s4, 4);
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
        for (;;) {
            // 0x004789c0
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
        // 0x004789dc
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
            // 0x00478a30
            charge(ctx, 4);
            jal(ctx, 0x478A30u, gen::fn__rwDMAAddPURef_004d51c0);
            backedge(ctx);
        }
        // 0x00478a08
        charge(ctx, 2);
        v0 = 1;
    }
    // 0x00478a40 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x100);
}

// 0x00479900 sub_479900 -- 1360 bytes; frame 0x100: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_478520 [2-D bridge] / sub_479900 [3-D bridge]: $a0 the PS2All pipe data (mesh.h `pd`: +4 the material pipeline's
// private data, +8 the atomic, +40 transType, +43 the VU1 code index, +48 the resEntry slot, +64 the texture, +68 the
// material colour). The vertex count (the particle count, x4 in 3-D) is split into batches of the pipeline's
// (+496 +8) size: s0 = ceil(count / batch); a stale instance (pipeline +220 == 1 and the cluster's counts differ)
// re-instances through ps2AllInstanceDmaChain first. The packet: CLAMP (sub_4749A0) and the texture (sub_4748C0) into the tank
// block, then a 12-qw VIF packet -- an UNPACK header, the viewport scale (-1/4 or -1/2 of the camera raster's width /
// height times the view window, at sp + 240 with the batch count and the last batch's size), the two clip-vector
// templates (0x965910 / 0x965920), the GIF tag (fog, texture and ABE bits; ABE when the tank's +180 is 1), A+D
// ALPHA_2 / CLAMP_2 / TEST_2 / TEX1_2 of the tank's pipeline record (+184 .. +208) and ZBUF_2 from the ZBUF_1 shadow;
// a second packet with the material colour (sub_49CAB0, scale 1/255 or 0x3B011B50 for a textured batch), the VU1 code
// index (+43 from transType bit 0 and the stale test), a DMA `call` of the
// program when it is not the resident one (gp-16888), and the DMA `ref` of the instanced clusters (reference counted
// under DI / EI, the first use -> _rwDMAAddPURef). Returns 1, or 0 when no packet could be opened.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_479900(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::cvt_s_w, hg::di, hg::divu,
          hg::dsll, hg::dsll32, hg::dsra32, hg::dsrl32, hg::ei, hg::enter, hg::jal, hg::lbu, hg::ld, hg::link,
          hg::lq, hg::lw, hg::lwc1, hg::lwu, hg::mfc0, hg::mflo, hg::mtc1, hg::mul_s, hg::mult, hg::neg_s,
          hg::pcpyld, hg::sb, hg::sd, hg::sll, hg::sq, hg::subu, hg::sw, hg::swc1, hg::sync;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f12{ctx, 12};
    // 0x00479900
    enter(ctx, 37);  // entry check point + this block's cycles
    sp = addiu(sp, -0x100);
    v0 = 0x960000;
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    fp = 0;
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    s6 = 0;
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s2, a0, 8);
    lw(v1, a0, 4);
    lw(s5, v0, 112);  // 0x960070
    lw(a0, gp, -17792);  // 0x7CE770
    v0 = addiu(v1, 496);
    lw(s7, s5, 96);
    sq(v0, sp, 0xD0);
    lw(v1, v1, 504);
    v0 = addu(s2, a0);
    lw(a0, v0, 0);
    lw(s3, a0, 156);
    v0 = addiu(v1, -1);
    lw(a0, a0, 4);
    s1 = sll(a0, 2);
    v0 = addu(s1, v0);
    divu(v0, v1);
    lw(v1, s3, 220);
    mflo(s0);
    v0 = 1;
    sd(zero, sp, 0xE8);
    if (v1 == v0) {
        // 0x00479994
        charge(ctx, 6);
        lw(v0, s4, 48);
        lw(v0, v0, 0);
        v1 = addiu(v0, 24);
        lw(v0, v0, 36);
        if (s1 == v0) {
            // 0x004799ac
            charge(ctx, 3);
            lw(v0, v1, 28);
            if (v0 != s0) {
                goto L_00479df0;
            }
            goto L_004799b8;
        }
    L_00479df0:
        charge(ctx, 6);
        sw(s1, v1, 12);
        a0 = s4;
        link(ctx, 0x479DF8u);  // $ra first: the delay slot below depends on it
        sw(s0, v1, 28);
        call(ctx, gen::fn_ps2AllInstanceDmaChain_0049dc70);
        lw(a1, s4, 64);
        backedge(ctx);
        goto L_004799bc;
    }
L_004799b8:
    charge(ctx, 1);
    lw(a1, s4, 64);
L_004799bc:
    charge(ctx, 2);
    if (a1 != 0) {
        // 0x004799c4
        charge(ctx, 1);
        s6 = 1;
    }
    // 0x004799c8
    charge(ctx, 22);
    lw(v0, gp, -17792);  // 0x7CE770
    v0 = addu(s2, v0);
    lw(v0, v0, 0);
    a0 = addiu(v0, 80);
    jal(ctx, 0x4799D4u, gen::fn_sub_4749A0_004749a0);
    lw(v0, gp, -17792);  // 0x7CE770
    lw(a1, s4, 64);
    v0 = addu(s2, v0);
    lw(v0, v0, 0);
    a0 = addiu(v0, 80);
    jal(ctx, 0x4799ECu, gen::fn_sub_4748C0_004748c0);
    ld(v0, s3, 184);
    a0 = 0;
    a1 = 12;
    sq(v0, sp, 0xC0);
    ld(v0, s3, 200);
    sq(v0, sp, 0xB0);
    ld(v0, s3, 192);
    link(ctx, 0x479A10u);  // $ra first: the delay slot below depends on it
    sq(v0, sp, 0xA0);
    call(ctx, gen::fn__rwDMAOpenVIFPkt_004d59d0);
    if (v0 == 0) {
        // 0x00479e08
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x00479a20
        charge(ctx, 54);
        v1 = 0x6C0A0000;
        v0 = 0x1000000;
        a0 = v1 | 0x3C6;
        v1 = v0 | 0x404;  // &0x1000404
        a0 = dsll32(a0, 0);
        v0 = 0x10000000;
        v1 = v1 | a0;
        v0 = v0 | 0xA;
        pcpyld(a1, v1, v0);
        sw(s0, sp, 0xF8);
        lw(v1, gp, -17148);  // 0x7CE9F4
        v0 = 0x3F000000;
        mtc1(v0, f2);
        a0 = addiu(s0, -1);
        sq(a1, v1, 0);
        lw(v0, gp, -17148);  // 0x7CE9F4
        v1 = addiu(v0, 16);
        sw(v1, gp, -17148);  // 0x7CE9F4
        lwc1(f1, s7, 16);
        lq(v0, sp, 0xD0);
        lwc1(f0, s5, 116);
        lwc1(f4, s7, 12);
        lwc1(f3, s5, 112);
        cvt_s_w(f1, f1);
        lw(v0, v0, 8);
        mul_s(f0, f1, f0);
        cvt_s_w(f1, f4);
        mul_s(f1, f1, f3);
        mul_s(f1, f2, f1);
        mul_s(f0, f2, f0);
        neg_s(f1, f1);
        neg_s(f0, f0);
        swc1(f1, sp, 0xF0);
        swc1(f0, sp, 0xF4);
        mult(a1, a0, v0);
        lw(a2, gp, -17148);  // 0x7CE9F4
        v1 = 0x960000;
        a1 = subu(s1, a1);
        v0 = 0x960000;
        sw(a1, sp, 0xFC);
        a0 = 1;
        lq(a1, sp, 0xF0);
        sq(a1, a2, 0);
        lq(v1, v1, 22800);  // 0x965910
        sq(v1, a2, 16);
        lq(v0, v0, 22816);  // 0x965920
        sq(v0, a2, 32);
        lw(v0, gp, -17148);  // 0x7CE9F4
        v1 = addiu(v0, 48);
        sw(v1, gp, -17148);  // 0x7CE9F4
        lbu(v0, s4, 40);
        v0 = v0 & 0x1;
        if (v0 == a0) {
            // 0x00479af8
            charge(ctx, 1);
            fp = a0;
        }
        // 0x00479afc
        charge(ctx, 7);
        lw(a0, gp, -17792);  // 0x7CE770
        v0 = 1;
        a0 = addu(s2, a0);
        lw(a0, a0, 0);
        lw(a0, a0, 180);
        if (a0 == v0) {
            // 0x00479b18
            charge(ctx, 1);
            sd(v0, sp, 0xE8);
        }
        // 0x00479b1c
        charge(ctx, 78);
        ld(v0, sp, 0xE8);
        a1 = 1042;
        a0 = dsll(v0, 6);
        v0 = dsll(fp, 5);
        a0 = a0 | 0x200;
        a0 = a0 | v0;
        v0 = dsll(s6, 4);
        a0 = v0 | a0;
        a0 = a0 | 0xC;
        v0 = 0x30000000;
        a0 = dsll32(a0, 0);
        v0 = v0 | 0x4000;
        a0 = dsra32(a0, 0);
        a0 = sll(a0, 15);
        a0 = dsll32(a0, 0);
        a0 = dsrl32(a0, 0);
        v0 = a0 | v0;
        v0 = dsll32(v0, 0);
        pcpyld(v0, a1, v0);
        a1 = dsll32(v1, 0);
        a0 = 14;
        a1 = dsra32(a1, 0);
        sq(v0, a1, 0);
        v0 = 0x10000000;
        v1 = dsll32(v0, 0);
        v0 = 0x8005;
        v0 = v0 | v1;
        pcpyld(v0, a0, v0);
        sq(v0, a1, 16);
        v1 = 67;
        lq(v0, sp, 0xC0);
        pcpyld(v0, v1, v0);
        sq(v0, a1, 32);
        v1 = 9;
        lq(v0, sp, 0xA0);
        pcpyld(v0, v1, v0);
        sq(v0, a1, 48);
        v1 = 72;
        lq(v0, sp, 0xB0);
        pcpyld(v0, v1, v0);
        sq(v0, a1, 64);
        a0 = 21;
        lw(v0, gp, -17148);  // 0x7CE9F4
        v1 = addiu(v0, 80);
        sw(v1, gp, -17148);  // 0x7CE9F4
        ld(v0, s3, 208);
        pcpyld(v0, a0, v0);
        lw(a0, gp, -17148);  // 0x7CE9F4
        v1 = 79;
        sq(v0, a0, 0);
        ld(v0, gp, -17088);  // 0x7CEA30
        pcpyld(v0, v1, v0);
        sq(v0, a0, 16);
        a1 = 5;
        lw(v0, gp, -17148);  // 0x7CE9F4
        a0 = 0;
        v1 = addiu(v0, 32);
        link(ctx, 0x479C00u);  // $ra first: the delay slot below depends on it
        sw(v1, gp, -17148);  // 0x7CE9F4
        call(ctx, gen::fn__rwDMAOpenVIFPkt_004d59d0);
        v0 = 0x10000000;
        v1 = 0;
        v0 = v0 | 0x2;
        pcpyld(a2, v1, v0);
        lw(a0, gp, -17148);  // 0x7CE9F4
        v1 = 0x6C010000;
        v0 = 0x1000000;
        v1 = v1 | 0x3FB;
        v0 = v0 | 0x404;  // &0x1000404
        v1 = dsll32(v1, 0);
        a1 = 0;
        v0 = v0 | v1;
        sq(a2, a0, 0);
        pcpyld(v0, v0, a1);
        sq(v0, a0, 16);
        lw(v0, gp, -17148);  // 0x7CE9F4
        v1 = addiu(v0, 32);
        sw(v1, gp, -17148);  // 0x7CE9F4
        if (s6 == 0) {
            // 0x00479c68
            charge(ctx, 4);
            v0 = 0x3B800000;
            v0 = v0 | 0x8081;
            mtc1(v0, f12);
            a0 = addiu(s4, 68);
        } else {
            // 0x00479c54
            charge(ctx, 5);
            v0 = 0x3B010000;
            v0 = v0 | 0x1B50;
            mtc1(v0, f12);
            a0 = addiu(s4, 68);
        }
        // 0x00479c78
        charge(ctx, 6);
        jal(ctx, 0x479C78u, gen::fn_sub_49CAB0_0049cab0);
        lw(v0, s3, 220);
        a0 = 1;
        if (v0 != a0) {
            // 0x00479c90
            charge(ctx, 7);
            lw(v0, gp, -17792);  // 0x7CE770
            v0 = addu(s2, v0);
            lw(v0, v0, 0);
            lw(v1, v0, 4);
            lw(v0, v0, 0);
            if (v1 == v0) {
                goto L_00479cac;
            }
            // 0x00479cd0
            charge(ctx, 4);
            lbu(v0, s4, 40);
            v0 = v0 & 0x1;
            if (v0 != a0) {
                // 0x00479cec
                charge(ctx, 2);
                v0 = 3;
                sb(v0, s4, 43);
            } else {
                // 0x00479ce0
                charge(ctx, 3);
                v0 = 2;
                sb(v0, s4, 43);
            }
            goto L_00479cf4;
        }
    L_00479cac:
        charge(ctx, 5);
        lbu(v1, s4, 40);
        v0 = 1;
        v1 = v1 & 0x1;
        if (v1 != v0) {
            // 0x00479cc8
            charge(ctx, 2);
            sb(v0, s4, 43);
        } else {
            // 0x00479cc0
            charge(ctx, 2);
            sb(zero, s4, 43);
        }
    L_00479cf4:
        charge(ctx, 9);
        lw(v1, s4, 4);
        lbu(a0, s4, 43);
        lw(v0, gp, -16888);  // 0x7CEAF8
        lw(v1, v1, 24);
        a0 = sll(a0, 2);
        v1 = addu(v1, a0);
        lw(a0, v1, 0);
        if (v0 != a0) {
            // 0x00479d18
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
        // 0x00479d4c
        charge(ctx, 21);
        lw(a0, s4, 48);
        a2 = 0x2000000;
        lw(v1, s4, 4);
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
        for (;;) {
            // 0x00479da0
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
        // 0x00479dbc
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
            // 0x00479e10
            charge(ctx, 4);
            jal(ctx, 0x479E10u, gen::fn__rwDMAAddPURef_004d51c0);
            backedge(ctx);
        }
        // 0x00479de8
        charge(ctx, 2);
        v0 = 1;
    }
    // 0x00479e20 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x100);
}

// 0x004861B0 sub_4861B0 -- 400 bytes; frame 0xB0: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4861B0 [run the instance callbacks]: $a0 the atomic, $a1 the instance data, $a2 the count, $a3 the flags (bits
// 0x1E8000: the count is the tank's own, *(*(atomic + plugin offset))). With the tank block's callbacks (+36 .. +56):
// the lock record lives on this frame (sp + 96, 72 bytes); +36 (instance begin) memsets it and fills it
// (record, atomic, data, count, flags) -- without it the record keeps whatever the stack held --, then every
// component the record asks for (+16 / +24 / +32 / +40 the {pointer, stride} of the position / UV / colour /
// second-component streams) goes to its writer +40 / +44 / +48 / +52 (stream, ...), and +56 (instance end) gets the
// record. Returns 1.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_4861B0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::jalr, hg::ld, hg::lq,
          hg::lw, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004861b0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    v0 = 0x1E0000;
    sd(ra, sp, 0x50);
    v0 = v0 | 0x8000;  // &0x1E8000
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    s2 = a3;
    sq(s1, sp, 0x10);
    v0 = s2 & v0;
    sq(s0, sp, 0x0);
    if (v0 == 0) {
        // 0x004861fc
        charge(ctx, 1);
        s0 = a2;
    } else {
        // 0x004861e8
        charge(ctx, 5);
        lw(v0, gp, -17792);  // 0x7CE770
        v0 = addu(s4, v0);
        lw(v0, v0, 0);
        lw(s0, v0, 0);
    }
    // 0x00486200
    charge(ctx, 6);
    lw(v0, gp, -17792);  // 0x7CE770
    v0 = addu(s4, v0);
    lw(s1, v0, 0);
    lw(v0, s1, 36);
    if (v0 != 0) {
        // 0x004862ec
        charge(ctx, 13);
        a0 = addiu(sp, 0x60);
        a1 = 0;
        a2 = 72;
        jal(ctx, 0x4862F4u, gen::fn_memset_00521408);
        lw(v0, s1, 36);
        a0 = addiu(sp, 0x60);
        a1 = s4;
        a2 = s3;
        a3 = s0;
        t0 = s2;
        jalr(ctx, 0x486310u, v0.u());
        lw(v1, s1, 40);
        backedge(ctx);
    } else {
        // 0x00486218
        charge(ctx, 1);
        lw(v1, s1, 40);
    }
    // 0x0048621c
    charge(ctx, 2);
    if (v1 != 0) {
        // 0x00486224
        charge(ctx, 4);
        a0 = addiu(sp, 0x70);
        lw(v0, a0, 0);
        if (v0 != 0) {
            // 0x00486234
            charge(ctx, 5);
            a1 = addiu(sp, 0x90);
            a2 = addiu(sp, 0x9C);
            a3 = s0;
            t0 = s3;
            jalr(ctx, 0x486240u, v1.u());
        }
    }
    // 0x00486248
    charge(ctx, 3);
    lw(v1, s1, 44);
    if (v1 != 0) {
        // 0x00486254
        charge(ctx, 4);
        a0 = addiu(sp, 0x78);
        lw(v0, a0, 0);
        if (v0 != 0) {
            // 0x00486264
            charge(ctx, 3);
            a1 = s0;
            a2 = s3;
            jalr(ctx, 0x486268u, v1.u());
        }
    }
    // 0x00486270
    charge(ctx, 3);
    lw(v1, s1, 48);
    if (v1 != 0) {
        // 0x0048627c
        charge(ctx, 4);
        a0 = addiu(sp, 0x80);
        lw(v0, a0, 0);
        if (v0 != 0) {
            // 0x0048628c
            charge(ctx, 3);
            a1 = s0;
            a2 = s3;
            jalr(ctx, 0x486290u, v1.u());
        }
    }
    // 0x00486298
    charge(ctx, 3);
    lw(v1, s1, 52);
    if (v1 != 0) {
        // 0x004862a4
        charge(ctx, 4);
        a0 = addiu(sp, 0x88);
        lw(v0, a0, 0);
        if (v0 != 0) {
            // 0x004862b4
            charge(ctx, 3);
            a1 = s0;
            a2 = s3;
            jalr(ctx, 0x4862B8u, v1.u());
        }
    }
    // 0x004862c0
    charge(ctx, 3);
    lw(v0, s1, 56);
    if (v0 != 0) {
        // 0x004862cc
        charge(ctx, 6);
        a1 = s4;
        a2 = s3;
        a3 = s0;
        t0 = s2;
        a0 = addiu(sp, 0x60);
        jalr(ctx, 0x4862DCu, v0.u());
    }
    // 0x004862e4
    charge(ctx, 2);
    v0 = 1;
    // 0x00486320
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xB0);
}

// 0x00474160 sub_474160 -- 164 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_474160 [tank atomic render callback]: $a0 the atomic. When the tank has particles (+4 > 0): the lock callback
// (+28: (?, tank + 80, count, tank +64)) with tank +64 cleared after it, the instance callback (+32: (atomic, tank +
// 80, count)) whose result decides the render, then the render callback (+16: (atomic)) unless the instance callback
// returned something other than 1. Returns the atomic.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_474160(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jalr, hg::ld, hg::lq, hg::lw, hg::sd, hg::slt,
          hg::sq, hg::sw;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00474160
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, -17792);  // 0x7CE770
    v0 = addu(s1, v0);
    lw(s2, v0, 0);
    lw(a2, s2, 4);
    at = slt(0, a2);
    s0 = 1;
    if (at != 0) {
        // 0x00474194
        charge(ctx, 3);
        lw(v0, s2, 28);
        if (v0 != 0) {
            // 0x004741a0
            charge(ctx, 4);
            lw(a3, s2, 64);
            a1 = addiu(s2, 80);
            jalr(ctx, 0x4741A4u, v0.u());
            sw(zero, s2, 64);
        }
        // 0x004741b0
        charge(ctx, 3);
        lw(v0, s2, 32);
        if (v0 != 0) {
            // 0x004741bc
            charge(ctx, 5);
            lw(a2, s2, 4);
            a0 = s1;
            a1 = addiu(s2, 80);
            jalr(ctx, 0x4741C4u, v0.u());
            s0 = v0;
        }
        // 0x004741d0
        charge(ctx, 3);
        v0 = 1;
        if (s0 == v0) {
            // 0x004741dc
            charge(ctx, 3);
            lw(v0, s2, 16);
            a0 = s1;
            jalr(ctx, 0x4741E0u, v0.u());
        }
    }
    // 0x004741e8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = s1;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00488B90 sub_488B90 -- 212 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_488B90 [3-D tank render with its blend states]: $a0 the atomic, $a1 the tank block. Saves render states 11 and 10
// (the source / destination blend, through RwRenderStateGet at 0x960094) to the frame; with blend modes (+100 != 0)
// sets +96 / +92 (RwRenderStateSet at 0x960090), runs the tank's render callback (+16 of the block behind the plugin
// offset) and restores the saved states. Returns 1 without blend modes, else 0.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_488B90(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jalr, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00488b90
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s1 = a1;
    s0 = 0x960000;
    a0 = 11;
    s0 = addiu(s0, 148);  // &pfn_RwRenderStateGet
    lw(v0, s0, 0);  // pfn_RwRenderStateGet
    a1 = addiu(sp, 0x48);
    jalr(ctx, 0x488BBCu, v0.u());
    lw(v0, s0, 0);  // pfn_RwRenderStateGet
    a0 = 10;
    a1 = addiu(sp, 0x4C);
    jalr(ctx, 0x488BCCu, v0.u());
    lw(v0, s1, 100);
    if (v0 != 0) {
        // 0x00488be8
        charge(ctx, 25);
        s0 = 0x960000;
        lw(a1, s1, 96);
        s0 = addiu(s0, 144);  // &pfn_RwRenderStateSet
        lw(v0, s0, 0);  // pfn_RwRenderStateSet
        a0 = 11;
        jalr(ctx, 0x488BF8u, v0.u());
        lw(a1, s1, 92);
        lw(v0, s0, 0);  // pfn_RwRenderStateSet
        a0 = 10;
        jalr(ctx, 0x488C08u, v0.u());
        lw(v0, gp, -17792);  // 0x7CE770
        v0 = addu(s2, v0);
        lw(v0, v0, 0);
        lw(v0, v0, 16);
        a0 = s2;
        jalr(ctx, 0x488C20u, v0.u());
        lw(a1, sp, 0x48);
        lw(v0, s0, 0);  // pfn_RwRenderStateSet
        a0 = 11;
        jalr(ctx, 0x488C30u, v0.u());
        lw(v0, s0, 0);  // pfn_RwRenderStateSet
        lw(a1, sp, 0x4C);
        a0 = 10;
        jalr(ctx, 0x488C40u, v0.u());
        v0 = 0;
    } else {
        // 0x00488be0
        charge(ctx, 2);
        v0 = 1;
    }
    // 0x00488c4c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00474A80 sub_474A80 -- 304 bytes; leaf frame (no stack)
// sub_474A80 [the tank's ALPHA word]: $a0 the tank data. Its blend modes (+92 source, +96 destination; values 0..8
// through the jump tables 0x7BC960 / 0x7BC930, else 2 / 3) index the 6 x 6 table of ALPHA words at 0x77B140; a
// valid word (not 0xFFFFFFFF) goes to the pipeline record (+76 -> +184), with FIX = 0x80 for source 1 / destination
// 1. Returns 1, or 0 for an invalid pair.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_474A80(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll, hg::dsll32, hg::enter, hg::lw, hg::lwu, hg::sd,
          hg::sll, hg::sltiu, hg::tail;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x00474a80
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, 92);
    at = sltiu(v1, 9);
    lw(v0, a0, 76);
    if (at != 0) {
        // 0x00474a90
        charge(ctx, 7);
        a1 = 0x7C0000;
        v1 = sll(v1, 2);
        a1 = addiu(a1, -13984);  // &0x7BC960
        v1 = addu(v1, a1);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x474AACu:  // table[1]
            // 0x00474aac
            charge(ctx, 2);
            t0 = 0;
            break;
        case 0x474AB4u:  // table[2]
            // 0x00474ab4
            charge(ctx, 2);
            t0 = 1;
            break;
        case 0x474ABCu:  // table[5]
            // 0x00474abc
            charge(ctx, 2);
            t0 = 2;
            break;
        case 0x474AC4u:  // table[6]
            // 0x00474ac4
            charge(ctx, 2);
            t0 = 3;
            break;
        case 0x474ACCu:  // table[7]
            // 0x00474acc
            charge(ctx, 2);
            t0 = 4;
            break;
        case 0x474AD4u:  // table[8]
            // 0x00474ad4
            charge(ctx, 2);
            t0 = 5;
            break;
        case 0x474ADCu:  // table[0, 3, 4]
        L_00474adc:
            charge(ctx, 1);
            t0 = 2;
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
        goto L_00474ae0;
    }
    goto L_00474adc;
L_00474ae0:
    charge(ctx, 4);
    lw(v1, a0, 96);
    at = sltiu(v1, 9);
    if (at != 0) {
        // 0x00474af0
        charge(ctx, 7);
        a0 = 0x7C0000;
        v1 = sll(v1, 2);
        a0 = addiu(a0, -14032);  // "<KG"
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x474B0Cu:  // table[1]
            // 0x00474b0c
            charge(ctx, 2);
            a3 = 0;
            break;
        case 0x474B14u:  // table[2]
            // 0x00474b14
            charge(ctx, 2);
            a3 = 1;
            break;
        case 0x474B1Cu:  // table[5]
            // 0x00474b1c
            charge(ctx, 2);
            a3 = 2;
            break;
        case 0x474B24u:  // table[6]
            // 0x00474b24
            charge(ctx, 2);
            a3 = 3;
            break;
        case 0x474B2Cu:  // table[7]
            // 0x00474b2c
            charge(ctx, 2);
            a3 = 4;
            break;
        case 0x474B34u:  // table[8]
            // 0x00474b34
            charge(ctx, 2);
            a3 = 5;
            break;
        case 0x474B3Cu:  // table[0, 3, 4]
        L_00474b3c:
            charge(ctx, 1);
            a3 = 3;
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
        goto L_00474b40;
    }
    goto L_00474b3c;
L_00474b40:
    charge(ctx, 14);
    v1 = sll(a3, 1);
    a1 = 0x780000;
    v1 = addu(v1, a3);
    a1 = addiu(a1, -20160);  // &0x77B140
    a2 = sll(v1, 3);
    a0 = sll(t0, 2);
    a1 = addu(a1, a2);
    v1 = 0xFFFF;
    a0 = addu(a0, a1);
    v1 = dsll(v1, 16);
    lwu(a0, a0, 0);
    v1 = v1 | 0xFFFF;
    if (a0 == v1) {
        // 0x00474ba4
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00474b78
        charge(ctx, 3);
        v1 = 1;
        if (t0 == v1) {
            // 0x00474b84
            charge(ctx, 2);
            if (a3 == v1) {
                // 0x00474b8c
                charge(ctx, 3);
                v1 = 128;
                v1 = dsll32(v1, 0);
                a0 = a0 | v1;
            }
        }
        // 0x00474b98
        charge(ctx, 3);
        sd(a0, v0, 184);
        v0 = 1;
    }
    // 0x00474ba8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x004749A0 sub_4749A0 -- 224 bytes; leaf frame (no stack)
// sub_4749A0 [CLAMP from the texture's address modes]: $a0 the tank data (+76 the pipeline record), $a1 the texture
// (+80 bits 8..11 U mode, 12..15 V mode: 1 wrap, 3 clamp; 2 / 4 rejected). The CLAMP word (0 to start: WMS in bits
// 0..1, WMT in 2..3) goes to the pipeline record +192. Returns 1 (also without a texture), 0 for a rejected mode.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_4749A0(EEContext& ctx) {
    using hg::Gpr, hg::charge, hg::enter, hg::lw, hg::pcpyld, hg::sd, hg::si, hg::srl;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x004749a0
    enter(ctx, 2);  // entry check point + this block's cycles
    a3 = 0;
    if (a1 != 0) {
        // 0x004749a8
        charge(ctx, 7);
        lw(a2, a0, 76);
        v0 = 4;
        lw(a0, a1, 80);
        v1 = a0 & 0xF00;
        v1 = srl(v1, 8);
        if (v1 != v0) {
            // 0x004749c4
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                goto L_00474a08;
            }
            // 0x004749d0
            charge(ctx, 3);
            v0 = 3;
            if (v1 == v0) {
                // 0x00474a00
                charge(ctx, 2);
                a3 = a3 | 0x1;
            L_00474a14:
                charge(ctx, 5);
                v1 = a0 & 0xF000;
                v0 = 4;
                v1 = srl(v1, 12);
                if (v1 != v0) {
                    // 0x00474a28
                    charge(ctx, 3);
                    v0 = 2;
                    if (v1 == v0) {
                        goto L_00474a74;
                    }
                    // 0x00474a34
                    charge(ctx, 3);
                    v0 = 3;
                    if (v1 == v0) {
                        // 0x00474a64
                        charge(ctx, 1);
                        a3 = a3 | 0x4;
                    L_00474a68:
                        charge(ctx, 1);
                        sd(a3, a2, 192);
                        goto L_00474a6c;
                    }
                    // 0x00474a40
                    charge(ctx, 3);
                    v0 = 1;
                    if (v1 == v0) {
                        // 0x00474a54
                        charge(ctx, 4);
                        v0 = si(-13);
                        pcpyld(v0, zero, v0);
                        a3 = a3 & v0;
                        goto L_00474a68;
                    }
                    // 0x00474a4c
                    charge(ctx, 2);
                    v0 = 0;
                    // 0x00474a78 (the shared epilogue, written out on this path)
                    charge(ctx, 2);
                    return;
                }
            L_00474a74:
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x004749dc
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    // 0x004749f0
                    charge(ctx, 4);
                    v0 = si(-4);
                    pcpyld(v0, zero, v0);
                    a3 = a3 & v0;
                    goto L_00474a14;
                }
                // 0x004749e8
                charge(ctx, 2);
                v0 = 0;
            L_00474a0c:
                charge(ctx, 2);
            }
            // 0x00474a78 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            return;
        }
    L_00474a08:
        charge(ctx, 1);
        v0 = 0;
        goto L_00474a0c;
    }
L_00474a6c:
    charge(ctx, 2);
    v0 = 1;
    // 0x00474a78 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0047B280 sub_47B280 -- 1232 bytes; frame 0xC0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_47B280 [tank as objects, coloured]: $a0 the atomic, $a1 the matrices (64 bytes each), $a2 their count, $a3 the
// colours (RGBA bytes, each channel / 255 into record +64 .. +76). Returns the atomic.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: callee frames ($sp off / deeper stack)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_47B280(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::addu, hg::backedge, hg::c_le_s, hg::c_lt_s, hg::charge,
          hg::cond, hg::cvt_s_w, hg::div_s, hg::dsll32, hg::dsra32, hg::enter, hg::i64, hg::jal, hg::lbu, hg::ld,
          hg::lq, hg::lw, hg::lwc1, hg::madd_s, hg::madda_s, hg::mov_s, hg::mtc1, hg::mul_s, hg::mula_s, hg::neg_s,
          hg::sd, hg::sll, hg::sltu, hg::sq, hg::sqrt_s, hg::srl, hg::sub_s, hg::sw, hg::swc1;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7};
    // 0x0047b280
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = 0x960000;
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a2;
    sq(s1, sp, 0x10);
    s5 = addiu(s5, -15200);  // &0x95C4A0
    sq(s0, sp, 0x0);
    if (s3 == 0) {
        // 0x0047b51c
        charge(ctx, 2);
        v0 = s4;
    } else {
        // 0x0047b2c0
        charge(ctx, 5);
        lw(fp, s4, 108);
        at = sltu(0, s3);
        s7 = 0;
        s2 = 0;
        if (at != 0) {
            // 0x0047b2d4
            charge(ctx, 3);
            at = sltu(0, s3);
            s6 = addiu(s4, 28);
            if (at != 0) {
                // 0x0047b2e0
                charge(ctx, 2);
                s1 = a1;
                s0 = a3;
                for (;;) {
                    // 0x0047b2e8
                    charge(ctx, 9);
                    a0 = addiu(sp, 0xA0);
                    a1 = s6;
                    a2 = s1;
                    jal(ctx, 0x47B2F0u, gen::fn_sub_4C6BE0_004c6be0);
                    lw(v1, s1, 12);
                    v0 = 3;
                    v1 = v1 & 0x3;
                    if (v1 == v0) {
                        // 0x0047b524
                        charge(ctx, 4);
                        lwc1(f0, s6, 12);
                        v0 = addiu(sp, 0xAC);
                        swc1(f0, v0, 0);
                        backedge(ctx);
                    } else {
                        // 0x0047b30c
                        charge(ctx, 21);
                        lwc1(f5, s1, 4);
                        lwc1(f4, s1, 0);
                        lwc1(f3, s1, 8);
                        lwc1(f2, s1, 20);
                        lwc1(f1, s1, 16);
                        lwc1(f0, s1, 24);
                        mula_s(f5, f5);
                        madda_s(f4, f4);
                        madd_s(f4, f3, f3);
                        mula_s(f2, f2);
                        madda_s(f1, f1);
                        madd_s(f3, f0, f0);
                        lwc1(f2, s1, 36);
                        lwc1(f1, s1, 32);
                        lwc1(f0, s1, 40);
                        mula_s(f2, f2);
                        madda_s(f1, f1);
                        madd_s(f1, f0, f0);
                        c_lt_s(f3, f1);
                        if (cond(ctx)) {
                            // 0x0047b368
                            charge(ctx, 1);
                            mov_s(f0, f1);
                        } else {
                            // 0x0047b360
                            charge(ctx, 2);
                            mov_s(f0, f3);
                        }
                        // 0x0047b36c
                        charge(ctx, 3);
                        c_lt_s(f4, f0);
                        if (cond(ctx)) {
                            // 0x0047b380
                            charge(ctx, 3);
                            c_lt_s(f3, f1);
                            if (cond(ctx)) {
                                // 0x0047b394
                                charge(ctx, 2);
                                mov_s(f3, f1);
                                mov_s(f4, f3);
                            } else {
                                // 0x0047b38c
                                charge(ctx, 2);
                                mov_s(f4, f3);
                            }
                            // 0x0047b39c
                            charge(ctx, 1);
                        } else {
                            // 0x0047b378
                            charge(ctx, 2);
                        }
                        // 0x0047b3a0
                        charge(ctx, 6);
                        sqrt_s(f1, f4);
                        v0 = addiu(sp, 0xAC);
                        lwc1(f0, s6, 12);
                        mul_s(f0, f0, f1);
                        swc1(f0, v0, 0);
                    }
                    // 0x0047b3b8
                    charge(ctx, 7);
                    v0 = 0x960000;
                    a0 = 6;
                    lw(v0, v0, 112);  // 0x960070
                    v1 = 2;
                    a1 = addiu(a0, -1);
                    a2 = addiu(v0, 148);
                    if (a0 != 0) {
                        // 0x0047b3d4
                        charge(ctx, 8);
                        v0 = addiu(sp, 0xA4);
                        a0 = 1;
                        lwc1(f7, v0, 0);
                        lwc1(f6, sp, 0xA0);
                        v0 = addiu(sp, 0xA8);
                        lwc1(f5, v0, 0);
                        v0 = addiu(sp, 0xAC);
                        lwc1(f4, v0, 0);
                        for (;;) {
                            // 0x0047b3f4
                            charge(ctx, 11);
                            lwc1(f1, a2, 4);
                            lwc1(f2, a2, 0);
                            lwc1(f3, a2, 8);
                            lwc1(f0, a2, 12);
                            mula_s(f7, f1);
                            madda_s(f6, f2);
                            madd_s(f1, f5, f3);
                            sub_s(f0, f1, f0);
                            c_le_s(f0, f4);
                            v0 = a0;
                            if (cond(ctx)) {
                                // 0x0047b420
                                charge(ctx, 1);
                                v0 = 0;
                            }
                            // 0x0047b424
                            charge(ctx, 3);
                            v0 = v0 ^ 0x1;
                            if (v0 == 0) {
                                goto L_0047b430_20;
                            }
                            // 0x0047b438
                            charge(ctx, 4);
                            v0 = a1;
                            a2 = addiu(a2, 20);
                            a1 = addiu(a1, -1);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x0047b448
                        charge(ctx, 2);
                        a0 = dsll32(v1, 0);
                        goto L_0047b538;
                    }
                L_0047b534:
                    charge(ctx, 1);
                    a0 = dsll32(v1, 0);
                L_0047b538:
                    charge(ctx, 4);
                    v0 = 2;
                    a0 = dsra32(a0, 0);
                    if (a0 != v0) {
                        backedge(ctx);
                    } else {
                        // 0x0047b548
                        charge(ctx, 2);
                        v0 = 0x960000;
                        backedge(ctx);
                        // 0x0047b450
                        charge(ctx, 7);
                        lw(a0, gp, -16972);  // 0x7CEAA4
                        lw(a1, v0, 112);
                        v0 = 6;
                        a0 = addu(a1, a0);
                        a2 = addiu(v0, -1);
                        a1 = addiu(a0, 96);
                        if (v0 != 0) {
                            // 0x0047b46c
                            charge(ctx, 9);
                            v0 = addiu(sp, 0xA4);
                            a0 = 1;
                            lwc1(f7, v0, 0);
                            lwc1(f6, sp, 0xA0);
                            v0 = addiu(sp, 0xA8);
                            lwc1(f5, v0, 0);
                            v0 = addiu(sp, 0xAC);
                            lwc1(f0, v0, 0);
                            neg_s(f4, f0);
                            for (;;) {
                                // 0x0047b490
                                charge(ctx, 11);
                                lwc1(f1, a1, 4);
                                lwc1(f2, a1, 0);
                                lwc1(f3, a1, 8);
                                lwc1(f0, a1, 12);
                                mula_s(f7, f1);
                                madda_s(f6, f2);
                                madd_s(f1, f5, f3);
                                sub_s(f0, f1, f0);
                                c_le_s(f0, f4);
                                v0 = a0;
                                if (cond(ctx)) {
                                    // 0x0047b4bc
                                    charge(ctx, 1);
                                    v0 = 0;
                                }
                                // 0x0047b4c0
                                charge(ctx, 3);
                                v0 = v0 ^ 0x1;
                                if (v0 == 0) {
                                    goto L_0047b4cc_28;
                                }
                                // 0x0047b4d4
                                charge(ctx, 4);
                                v0 = a2;
                                a1 = addiu(a1, 20);
                                a2 = addiu(a2, -1);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x0047b4e4
                            charge(ctx, 1);
                        }
                    }
                L_0047b4e8:
                    charge(ctx, 4);
                    t0 = dsll32(v1, 0);
                    t0 = dsra32(t0, 0);
                    if (t0 != 0) {
                        // 0x0047b550
                        charge(ctx, 7);
                        v0 = sll(s2, 2);
                        a1 = 8;
                        v0 = addu(v0, s2);
                        a3 = s1;
                        v0 = sll(v0, 4);
                        v0 = addu(s5, v0);
                        a2 = v0;
                        for (;;) {
                            // 0x0047b56c
                            charge(ctx, 8);
                            lw(a0, a3, 0);
                            a1 = addiu(a1, -1);
                            lw(v1, a3, 4);
                            sw(a0, a2, 0);
                            a3 = addiu(a3, 8);
                            sw(v1, a2, 4);
                            a2 = addiu(a2, 8);
                            if (i64(a1) <= 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x0047b58c
                        charge(ctx, 5);
                        v1 = t0 & 0x1;
                        sw(v1, v0, 60);
                        lbu(v1, s0, 0);
                        if (i64(v1) < 0) {
                            // 0x0047b5ac
                            charge(ctx, 7);
                            a0 = srl(v1, 1);
                            v1 = v1 & 0x1;
                            a0 = a0 | v1;
                            mtc1(a0, f0);
                            cvt_s_w(f1, f0);
                            add_s(f1, f1, f1);
                        } else {
                            // 0x0047b5a0
                            charge(ctx, 3);
                            mtc1(v1, f0);
                            cvt_s_w(f1, f0);
                        }
                        // 0x0047b5c8
                        charge(ctx, 9);
                        v1 = 0x437F0000;
                        mtc1(v1, f0);
                        div_s(f0, f1, f0);
                        swc1(f0, v0, 64);
                        lbu(v1, s0, 1);
                        if (i64(v1) < 0) {
                            // 0x0047b5f8
                            charge(ctx, 7);
                            a0 = srl(v1, 1);
                            v1 = v1 & 0x1;
                            a0 = a0 | v1;
                            mtc1(a0, f0);
                            cvt_s_w(f1, f0);
                            add_s(f1, f1, f1);
                        } else {
                            // 0x0047b5ec
                            charge(ctx, 3);
                            mtc1(v1, f0);
                            cvt_s_w(f1, f0);
                        }
                        // 0x0047b614
                        charge(ctx, 9);
                        v1 = 0x437F0000;
                        mtc1(v1, f0);
                        div_s(f0, f1, f0);
                        swc1(f0, v0, 68);
                        lbu(v1, s0, 2);
                        if (i64(v1) < 0) {
                            // 0x0047b644
                            charge(ctx, 7);
                            a0 = srl(v1, 1);
                            v1 = v1 & 0x1;
                            a0 = a0 | v1;
                            mtc1(a0, f0);
                            cvt_s_w(f1, f0);
                            add_s(f1, f1, f1);
                        } else {
                            // 0x0047b638
                            charge(ctx, 3);
                            mtc1(v1, f0);
                            cvt_s_w(f1, f0);
                        }
                        // 0x0047b660
                        charge(ctx, 9);
                        v1 = 0x437F0000;
                        mtc1(v1, f0);
                        div_s(f0, f1, f0);
                        swc1(f0, v0, 72);
                        lbu(v1, s0, 3);
                        if (i64(v1) < 0) {
                            // 0x0047b690
                            charge(ctx, 7);
                            a0 = srl(v1, 1);
                            v1 = v1 & 0x1;
                            a0 = a0 | v1;
                            mtc1(a0, f0);
                            cvt_s_w(f1, f0);
                            add_s(f1, f1, f1);
                        } else {
                            // 0x0047b684
                            charge(ctx, 3);
                            mtc1(v1, f0);
                            cvt_s_w(f1, f0);
                        }
                        // 0x0047b6ac
                        charge(ctx, 10);
                        v1 = 0x437F0000;
                        s2 = addiu(s2, 1);
                        mtc1(v1, f0);
                        div_s(f0, f1, f0);
                        v1 = 48;
                        swc1(f0, v0, 76);
                        if (s2 != v1) {
                            backedge(ctx);
                        } else {
                            // 0x0047b6d4
                            charge(ctx, 10);
                            a0 = s5;
                            a1 = s2;
                            jal(ctx, 0x47B6D8u, gen::fn_sub_46C330_0046c330);
                            s5 = v0;
                            a0 = fp;
                            a1 = s4;
                            a2 = 1;
                            jal(ctx, 0x47B6ECu, gen::fn_RxPipelineExecute_004f2e70);
                            s2 = 0;
                            backedge(ctx);
                        }
                    }
                    // 0x0047b4f8
                    charge(ctx, 5);
                    s7 = addiu(s7, 1);
                    s1 = addiu(s1, 64);
                    v0 = sltu(s7, s3);
                    s0 = addiu(s0, 4);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
        // 0x0047b50c
        charge(ctx, 2);
        if (s2 != 0) {
            // 0x0047b6fc
            charge(ctx, 9);
            a0 = s5;
            a1 = s2;
            jal(ctx, 0x47B700u, gen::fn_sub_46C330_0046c330);
            a0 = fp;
            a1 = s4;
            a2 = 1;
            jal(ctx, 0x47B710u, gen::fn_RxPipelineExecute_004f2e70);
            backedge(ctx);
        }
        // 0x0047b514
        charge(ctx, 2);
        v0 = s4;
    }
    // 0x0047b720 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xC0);
    return;
L_0047b430_20:
    charge(ctx, 2);
    v1 = 0;
    goto L_0047b534;
L_0047b4cc_28:
    charge(ctx, 2);
    v1 = 1;
    goto L_0047b4e8;
}

// 0x0047B750 sub_47B750 -- 1000 bytes; frame 0xC0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_47B750 [tank as objects, lit]: $a0 the atomic, $a1 the matrices, $a2 their count, $a3 a vector v (three floats)
// expressed in each matrix's axes into record +64 .. +72 (right . v, up . v, at . v through ACC). Returns the atomic.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: callee frames ($sp off / deeper stack)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_47B750(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::c_le_s, hg::c_lt_s, hg::charge, hg::cond,
          hg::dsll32, hg::dsra32, hg::enter, hg::i64, hg::jal, hg::ld, hg::lq, hg::lw, hg::lwc1, hg::madd_s,
          hg::madda_s, hg::mov_s, hg::mul_s, hg::mula_s, hg::neg_s, hg::sd, hg::sll, hg::sltu, hg::sq, hg::sqrt_s,
          hg::sub_s, hg::sw, hg::swc1;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10};
    // 0x0047b750
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    s7 = 0;
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a3;
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a2;
    sq(s1, sp, 0x10);
    s2 = 0x960000;
    sq(s0, sp, 0x0);
    at = sltu(0, s3);
    lw(fp, a0, 108);
    s2 = addiu(s2, -15200);  // &0x95C4A0
    s1 = 0;
    if (at != 0) {
        // 0x0047b7a4
        charge(ctx, 3);
        at = sltu(0, s3);
        s6 = addiu(s4, 28);
        if (at != 0) {
            // 0x0047b7b0
            charge(ctx, 1);
            s0 = a1;
            for (;;) {
                // 0x0047b7b4
                charge(ctx, 9);
                a0 = addiu(sp, 0xA0);
                a1 = s6;
                a2 = s0;
                jal(ctx, 0x47B7BCu, gen::fn_sub_4C6BE0_004c6be0);
                lw(v1, s0, 12);
                v0 = 3;
                v1 = v1 & 0x3;
                if (v1 == v0) {
                    // 0x0047b9e0
                    charge(ctx, 4);
                    lwc1(f0, s6, 12);
                    v0 = addiu(sp, 0xAC);
                    swc1(f0, v0, 0);
                    backedge(ctx);
                } else {
                    // 0x0047b7d8
                    charge(ctx, 21);
                    lwc1(f5, s0, 4);
                    lwc1(f4, s0, 0);
                    lwc1(f3, s0, 8);
                    lwc1(f2, s0, 20);
                    lwc1(f1, s0, 16);
                    lwc1(f0, s0, 24);
                    mula_s(f5, f5);
                    madda_s(f4, f4);
                    madd_s(f4, f3, f3);
                    mula_s(f2, f2);
                    madda_s(f1, f1);
                    madd_s(f3, f0, f0);
                    lwc1(f2, s0, 36);
                    lwc1(f1, s0, 32);
                    lwc1(f0, s0, 40);
                    mula_s(f2, f2);
                    madda_s(f1, f1);
                    madd_s(f1, f0, f0);
                    c_lt_s(f3, f1);
                    if (cond(ctx)) {
                        // 0x0047b834
                        charge(ctx, 1);
                        mov_s(f0, f1);
                    } else {
                        // 0x0047b82c
                        charge(ctx, 2);
                        mov_s(f0, f3);
                    }
                    // 0x0047b838
                    charge(ctx, 3);
                    c_lt_s(f4, f0);
                    if (cond(ctx)) {
                        // 0x0047b84c
                        charge(ctx, 3);
                        c_lt_s(f3, f1);
                        if (cond(ctx)) {
                            // 0x0047b860
                            charge(ctx, 2);
                            mov_s(f3, f1);
                            mov_s(f4, f3);
                        } else {
                            // 0x0047b858
                            charge(ctx, 2);
                            mov_s(f4, f3);
                        }
                        // 0x0047b868
                        charge(ctx, 1);
                    } else {
                        // 0x0047b844
                        charge(ctx, 2);
                    }
                    // 0x0047b86c
                    charge(ctx, 6);
                    sqrt_s(f1, f4);
                    v0 = addiu(sp, 0xAC);
                    lwc1(f0, s6, 12);
                    mul_s(f0, f0, f1);
                    swc1(f0, v0, 0);
                }
                // 0x0047b884
                charge(ctx, 7);
                v0 = 0x960000;
                a0 = 6;
                lw(v0, v0, 112);  // 0x960070
                v1 = 2;
                a1 = addiu(a0, -1);
                a2 = addiu(v0, 148);
                if (a0 != 0) {
                    // 0x0047b8a0
                    charge(ctx, 8);
                    v0 = addiu(sp, 0xA4);
                    a0 = 1;
                    lwc1(f7, v0, 0);
                    lwc1(f6, sp, 0xA0);
                    v0 = addiu(sp, 0xA8);
                    lwc1(f5, v0, 0);
                    v0 = addiu(sp, 0xAC);
                    lwc1(f4, v0, 0);
                    for (;;) {
                        // 0x0047b8c0
                        charge(ctx, 11);
                        lwc1(f1, a2, 4);
                        lwc1(f2, a2, 0);
                        lwc1(f3, a2, 8);
                        lwc1(f0, a2, 12);
                        mula_s(f7, f1);
                        madda_s(f6, f2);
                        madd_s(f1, f5, f3);
                        sub_s(f0, f1, f0);
                        c_le_s(f0, f4);
                        v0 = a0;
                        if (cond(ctx)) {
                            // 0x0047b8ec
                            charge(ctx, 1);
                            v0 = 0;
                        }
                        // 0x0047b8f0
                        charge(ctx, 3);
                        v0 = v0 ^ 0x1;
                        if (v0 == 0) {
                            goto L_0047b8fc_19;
                        }
                        // 0x0047b904
                        charge(ctx, 4);
                        v0 = a1;
                        a2 = addiu(a2, 20);
                        a1 = addiu(a1, -1);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047b914
                    charge(ctx, 2);
                    a0 = dsll32(v1, 0);
                    goto L_0047b9f4;
                }
            L_0047b9f0:
                charge(ctx, 1);
                a0 = dsll32(v1, 0);
            L_0047b9f4:
                charge(ctx, 4);
                v0 = 2;
                a0 = dsra32(a0, 0);
                if (a0 != v0) {
                    backedge(ctx);
                } else {
                    // 0x0047ba04
                    charge(ctx, 2);
                    v0 = 0x960000;
                    backedge(ctx);
                    // 0x0047b91c
                    charge(ctx, 7);
                    lw(a0, gp, -16972);  // 0x7CEAA4
                    lw(a1, v0, 112);
                    v0 = 6;
                    a0 = addu(a1, a0);
                    a2 = addiu(v0, -1);
                    a1 = addiu(a0, 96);
                    if (v0 != 0) {
                        // 0x0047b938
                        charge(ctx, 9);
                        v0 = addiu(sp, 0xA4);
                        a0 = 1;
                        lwc1(f7, v0, 0);
                        lwc1(f6, sp, 0xA0);
                        v0 = addiu(sp, 0xA8);
                        lwc1(f5, v0, 0);
                        v0 = addiu(sp, 0xAC);
                        lwc1(f0, v0, 0);
                        neg_s(f4, f0);
                        for (;;) {
                            // 0x0047b95c
                            charge(ctx, 11);
                            lwc1(f1, a1, 4);
                            lwc1(f2, a1, 0);
                            lwc1(f3, a1, 8);
                            lwc1(f0, a1, 12);
                            mula_s(f7, f1);
                            madda_s(f6, f2);
                            madd_s(f1, f5, f3);
                            sub_s(f0, f1, f0);
                            c_le_s(f0, f4);
                            v0 = a0;
                            if (cond(ctx)) {
                                // 0x0047b988
                                charge(ctx, 1);
                                v0 = 0;
                            }
                            // 0x0047b98c
                            charge(ctx, 3);
                            v0 = v0 ^ 0x1;
                            if (v0 == 0) {
                                goto L_0047b998_27;
                            }
                            // 0x0047b9a0
                            charge(ctx, 4);
                            v0 = a2;
                            a1 = addiu(a1, 20);
                            a2 = addiu(a2, -1);
                            if (v0 != 0) {
                                backedge(ctx);
                                continue;
                            }
                            break;
                        }
                    }
                }
            L_0047b9b0:
                charge(ctx, 4);
                t0 = dsll32(v1, 0);
                t0 = dsra32(t0, 0);
                if (t0 != 0) {
                    // 0x0047ba0c
                    charge(ctx, 7);
                    v0 = sll(s1, 2);
                    a0 = 8;
                    v0 = addu(v0, s1);
                    a2 = s0;
                    v0 = sll(v0, 4);
                    a3 = addu(s2, v0);
                    a1 = a3;
                    for (;;) {
                        // 0x0047ba28
                        charge(ctx, 8);
                        lw(v1, a2, 0);
                        a0 = addiu(a0, -1);
                        lw(v0, a2, 4);
                        sw(v1, a1, 0);
                        a2 = addiu(a2, 8);
                        sw(v0, a1, 4);
                        a1 = addiu(a1, 8);
                        if (i64(a0) <= 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0047ba48
                    charge(ctx, 29);
                    v0 = t0 & 0x1;
                    s1 = addiu(s1, 1);
                    sw(v0, a3, 60);
                    lwc1(f10, s5, 4);
                    v0 = 48;
                    lwc1(f5, a3, 20);
                    lwc1(f9, s5, 0);
                    lwc1(f6, a3, 16);
                    lwc1(f8, s5, 8);
                    lwc1(f7, a3, 24);
                    lwc1(f0, a3, 36);
                    mula_s(f5, f10);
                    lwc1(f3, a3, 32);
                    madda_s(f6, f9);
                    lwc1(f4, a3, 40);
                    madd_s(f5, f7, f8);
                    mula_s(f0, f10);
                    lwc1(f0, a3, 4);
                    madda_s(f3, f9);
                    lwc1(f1, a3, 0);
                    madd_s(f3, f4, f8);
                    lwc1(f2, a3, 8);
                    mula_s(f0, f10);
                    madda_s(f1, f9);
                    madd_s(f0, f2, f8);
                    swc1(f0, a3, 64);
                    swc1(f5, a3, 68);
                    swc1(f3, a3, 72);
                    if (s1 != v0) {
                        backedge(ctx);
                    } else {
                        // 0x0047babc
                        charge(ctx, 10);
                        a0 = s2;
                        a1 = s1;
                        jal(ctx, 0x47BAC0u, gen::fn_sub_46C330_0046c330);
                        s2 = v0;
                        a0 = fp;
                        a1 = s4;
                        a2 = 1;
                        jal(ctx, 0x47BAD4u, gen::fn_RxPipelineExecute_004f2e70);
                        s1 = 0;
                        backedge(ctx);
                    }
                }
                // 0x0047b9c0
                charge(ctx, 4);
                s7 = addiu(s7, 1);
                v0 = sltu(s7, s3);
                s0 = addiu(s0, 64);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
    }
    // 0x0047b9d0
    charge(ctx, 2);
    if (s1 != 0) {
        // 0x0047bae4
        charge(ctx, 9);
        a0 = s2;
        a1 = s1;
        jal(ctx, 0x47BAE8u, gen::fn_sub_46C330_0046c330);
        a0 = fp;
        a1 = s4;
        a2 = 1;
        jal(ctx, 0x47BAF8u, gen::fn_RxPipelineExecute_004f2e70);
        backedge(ctx);
    }
    // 0x0047b9d8
    charge(ctx, 2);
    v0 = s4;
    // 0x0047bb08
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
    sp = addiu(sp, 0xC0);
    return;
L_0047b8fc_19:
    charge(ctx, 2);
    v1 = 0;
    goto L_0047b9f0;
L_0047b998_27:
    charge(ctx, 2);
    v1 = 1;
    goto L_0047b9b0;
}

}  // namespace p3fes::game

// --- the recompiled program's entry points (the bodies read their arguments from the registers) -----------
