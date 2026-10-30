// The RenderWare sky driver's core and the 2D bridges (sky.h has the overview; docs/ANALYSIS/22_rendering.md
// sections 2.4, 3.2, 5.3, 5.4).
//
// Cycle model (ADR-0013): every charge() below is one `ctx.cycles += N` block of the recompiled body in
// recomp/generated (fn_0042_* / fn_0044_* / fn_0048_*), in the order the path executes them; a block that contains a
// `jal` is charged in full before the call. backedge() sits wherever that body has a check point on a backward
// jump: loops, and the backward `goto`s of the compiler's block layout (out-of-line blocks that jump back into the
// main line), which the hand versions keep as explicit check points.
//
// Registers: register-faithful (sky.h). The bodies run on sky::Cpu, one variable per guest register; a branch's delay
// slot is written before the `if` when it does not feed the condition. The jump tables of _rwSkySetRenderState and
// sub_4E3640 are read from guest memory as the originals do ($v0 / $a1 hold the target) and dispatched on that target.
//
// Faithfulness audit (2026-10-21, tools/ours/audit): 9 of the 11 functions here are now p3fes_handgen's register-
// faithful bodies (their hand versions differed from the original: faults only 5, callee frames 2, the hand version
// terminated the host on a random world 2); each keeps the notes of its earlier hand version above it. The others are
// the hand-written versions this header describes.
#include "p3fes/game/sky.h"
#include "p3fes/game/hg_cpu.h"

namespace p3fes::recomp_gen {
void fn__rwDMAOpenVIFPkt_004d59d0(p3fes::EEContext&);    // the DMA packet layer (DMAC registers)
void fn__rwDMAWaitQueue_004d53f0(p3fes::EEContext&);     // render_rw2
void fn__rwDMAAddPURef_004d51c0(p3fes::EEContext&);      // resource reference ring
void fn_sub_4D6250_004d6250(p3fes::EEContext&);          // image-upload queue entry (PATH3)
void fn_sub_4F0F30_004f0f30(p3fes::EEContext&);          // texture cache: speculative placement (render_mesh)
void fn_RpSkyTexCacheAccessRaster_004f1020(p3fes::EEContext&);  // texture cache access (render_mesh)
void fn_sub_4EFA00_004efa00(p3fes::EEContext&);          // texture cache: the upload allocator (DIntr / EIntr)
void fn_sub_4C1D10_004c1d10(p3fes::EEContext&);          // RwError code (render_rw)
void fn_sub_4C1C50_004c1c50(p3fes::EEContext&);          // RwError (render_rw)
void fn_sub_4C6970_004c6970(p3fes::EEContext&);          // normalise a vector (render_rw)
void fn_sub_4EEC20_004eec20(p3fes::EEContext&);          // the per-camera VU1 constants
void fn_sub_4F1B30_004f1b30(p3fes::EEContext&);          // (this file) the deferred cache-raster packet
void fn_sub_49CAB0_0049cab0(p3fes::EEContext&);          // material colour quadword (render_mesh)
void fn_sub_49CBD0_0049cbd0(p3fes::EEContext&);          // surface properties quadword (render_mesh)
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {
namespace gen = ::p3fes::recomp_gen;
}  // namespace

namespace sky {

// =========================================================================================================
// Texture cache and rasters
// =========================================================================================================

// sub_4F1B30 [deferred cache-raster packet]: the texture cache's current raster (0x77F224; mode 0x77F228 picks
// context 1 / 2) gets its TEX0 (the extension's +8/+12 words; a camera-texture raster, type 2, takes its TBP from this
// frame's FRAME_1 FBP), TEX1 (the shadow with the extension's LOD / MXL bits) and, when the cache is on, MIPTBP1 /
// MIPTBP2 with the raster's TBP added -- one 4-register A+D packet (5 qw). SkyCameraBeginUpdate runs it when
// $gp-16988 says an upload is owed.
void Cpu::raster_upload() {
    enter(9);
    sp = addiu(sp, -64);
    v1 = lui(0x78);
    sd(sp + 48, ra);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    s1 = lw(kTexCacheCurrent);
    if (s1 != 0) {
        charge(28);
        v1 = lw(gpw(kGpRasterExt));
        v0 = lui(0x78);
        s0 = lw(kTexCacheMode);
        a0 = lui(0x8000);
        a1 = 32;
        s2 = addu(s1, v1);  // the raster's sky extension
        jal(0x4F1B68u, gen::fn__rwDMAOpenVIFPkt_004d59d0);
        // GIF tag: NLOOP 4, EOP, A+D
        v1 = lui(0x1000);
        a1 = 14;
        a0 = dsll32(v1, 0);
        v1 = 0x8004;
        a0 = v1 | a0;
        v1 = lw(gpw(kGpSprWrite));
        pcpyld(a1, a1, a0);
        a0 = 2;
        sq(v1, a1);
        v1 = lw(gpw(kGpSprWrite));
        a1 = addiu(v1, 16);
        sw(gpw(kGpSprWrite), a1);
        // TEX0 = ext +8 | ext +12 << 32
        v1 = lbu(s1 + 32);
        t0 = lw(s2 + 8);
        a3 = lwu(s2 + 12);
        a2 = v1 & 0x7;  // raster type
        v1 = dsll32(t0, 0);
        v1 = dsrl32(v1, 0);
        a3 = dsll32(a3, 0);
        v1 = v1 | a3;
        if (a2 == a0) {
            // a camera texture: TBP = this frame's FBP * 32 + the extension's TBP
            charge(4);
            a0 = lw(gpw(kGpFrameCount));
            a0 = a0 & 0x1;
            if (a0 != 0) {
                charge(3);
                a0 = lui(0x96);
                a0 = ld(kFrame1B);
            } else {
                charge(2);
                a0 = lui(0x96);
                a0 = ld(kFrame1A);
            }
            charge(8);
            a0 = a0 & 0x1ff;
            a2 = t0 & 0x3fff;
            a3 = dsll(a0, 5);
            a0 = si(-16384);
            a2 = a2 + a3;
            pcpyld(a0, zero, a0);
            v1 = v1 & a0;
            v1 = v1 | a2;
        }
        charge(59);
        a2 = 7;  // TEX0_2
        a0 = 6;  // TEX0_1
        if (s0 == 0) a2 = a0;
        a1 = dsll32(a1, 0);
        a2 = dsll32(a2, 0);
        a1 = dsra32(a1, 0);
        a2 = dsra32(a2, 0);
        a0 = si(-4096);
        pcpyld(v1, a2, v1);
        sq(a1, v1);
        // TEX1: the shadow without LCM / MXL / L / K, then the extension's +20 (K, L) and +22 (MXL) fields
        v1 = 0xffe7;
        a1 = dsll32(a0, 0);
        v1 = dsll(v1, 16);
        t1 = lw(gpw(kGpSprWrite));
        v1 = v1 | 0xfde3;
        t0 = ld(gpw(kGpTex1));
        a3 = v1 | a1;
        a0 = 21;  // TEX1_2
        v1 = 20;  // TEX1_1
        if (s0 == 0) a0 = v1;
        a2 = dsll32(a0, 0);
        v1 = lui(0x78);
        a1 = addiu(t1, 16);
        a2 = dsra32(a2, 0);
        a0 = t0 & a3;
        sw(gpw(kGpSprWrite), a1);
        sd(gpw(kGpTex1), a0);
        a3 = lhu(s2 + 20);
        t1 = lbu(s2 + 22);
        a1 = ld(gpw(kGpTex1));
        a0 = lw(gpw(kGpSprWrite));
        t0 = a3 & 0xfff;
        a3 = sra(a3, 12);
        t0 = dsll32(t0, 0);
        a3 = a3 & 0x3;
        t1 = dsll32(t1, 0);
        t0 = dsra32(t0, 0);
        a3 = dsll32(a3, 0);
        a3 = dsra32(a3, 0);
        t1 = dsra32(t1, 0);
        t0 = dsll32(t0, 0);
        a3 = dsll(a3, 19);
        t0 = t1 | t0;
        a3 = a3 | t0;
        a1 = a1 | a3;
        pcpyld(a2, a2, a1);
        sd(gpw(kGpTex1), a1);
        sq(a0, a2);
        a0 = lw(kTexCacheActive);
        v1 = lw(gpw(kGpSprWrite));
        a1 = addiu(v1, 16);
        sw(gpw(kGpSprWrite), a1);
        // the TBP replicated into MIPTBP's three 14-bit fields (cache on) or nothing added (off)
        v1 = lw(s2 + 8);
        a3 = v1 & 0x3fff;
        v1 = dsll(a3, 20);
        a2 = dsll32(a3, 8);
        v1 = a3 | v1;
        v1 = a2 | v1;
        if (a0 != 0) {
            charge(34);
            t1 = lwu(s2 + 28);
            a3 = dsll32(a1, 0);
            t2 = lwu(s2 + 24);
            a2 = 53;  // MIPTBP1_2
            a0 = 52;  // MIPTBP1_1
            a1 = 55;  // MIPTBP2_2
            if (s0 == 0) a2 = a0;
            a3 = dsra32(a3, 0);
            a0 = 54;  // MIPTBP2_1
            t0 = dsll32(a2, 0);
            if (s0 == 0) a1 = a0;
            t0 = dsra32(t0, 0);
            a0 = dsll32(t1, 0);
            a2 = dsll32(a1, 0);
            a0 = t2 | a0;
            a2 = dsra32(a2, 0);
            a0 = a0 + v1;
            pcpyld(a0, t0, a0);
            sq(a3, a0);
            a0 = lw(gpw(kGpSprWrite));
            a1 = addiu(a0, 16);
            sw(gpw(kGpSprWrite), a1);
            a1 = lwu(s2 + 36);
            a3 = lwu(s2 + 32);
            a0 = lw(gpw(kGpSprWrite));
            a1 = dsll32(a1, 0);
            a1 = a3 | a1;
            v1 = a1 + v1;
            pcpyld(v1, a2, v1);
            sq(a0, v1);
            v1 = lw(gpw(kGpSprWrite));
            a1 = addiu(v1, 16);
            sw(gpw(kGpSprWrite), a1);
        } else {
            charge(31);
            a3 = lwu(s2 + 28);
            a1 = dsll32(a1, 0);
            t0 = lwu(s2 + 24);
            a0 = 53;
            v1 = 52;
            a1 = dsra32(a1, 0);
            if (s0 == 0) a0 = v1;
            a2 = dsll32(a0, 0);
            v1 = 54;
            a0 = 55;
            a2 = dsra32(a2, 0);
            if (s0 == 0) a0 = v1;
            v1 = dsll32(a3, 0);
            a0 = dsll32(a0, 0);
            v1 = t0 | v1;
            a0 = dsra32(a0, 0);
            pcpyld(v1, a2, v1);
            sq(a1, v1);
            v1 = lw(gpw(kGpSprWrite));
            a1 = addiu(v1, 16);
            sw(gpw(kGpSprWrite), a1);
            a1 = lwu(s2 + 36);
            a2 = lwu(s2 + 32);
            v1 = lw(gpw(kGpSprWrite));
            a1 = dsll32(a1, 0);
            a1 = a2 | a1;
            pcpyld(a0, a0, a1);
            sq(v1, a0);
            v1 = lw(gpw(kGpSprWrite));
            a1 = addiu(v1, 16);
            sw(gpw(kGpSprWrite), a1);
        }
    }
    charge(6);
    ra = ld(sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 64);
}

// =========================================================================================================
// The PDS 2D bridges and the Im3D bridge
// =========================================================================================================

// =========================================================================================================
// _rwSkySetRenderState: the render-state funnel
// =========================================================================================================

// The exits: every path ends in `v0 = 0 / 1` (or s0 for state 1), the $ra reload and the shared tail.
void Cpu::rs_tail() {
    charge(4);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 48);
}
void Cpu::rs_epilogue() {
    charge(1);
    ra = ld(sp + 32);
    rs_tail();
}
void Cpu::rs_ok() {
    charge(2);
    v0 = 1;
    rs_epilogue();
}
void Cpu::rs_fail() {
    charge(2);
    v0 = 0;
    rs_epilogue();
}

// The one-register A+D packet of a GS shadow: GIF tag NLOOP 1, EOP, A+D; {shadow, register}.
void Cpu::rs_ad_tail(s32 shadow, u32 reg) {
    a0 = lw(gpw(kGpSprWrite));
    v0 = lui(0x1000);
    v1 = dsll32(v0, 0);
    a1 = 14;
    v0 = 0x8001;
    v0 = v0 | v1;
    pcpyld(v0, a1, v0);
    v1 = reg;
    sq(a0, v0);
    v0 = ld(gpw(shadow));
    pcpyld(v0, v1, v0);
    sq(a0 + 16, v0);
    v0 = lw(gpw(kGpSprWrite));
    v0 = addiu(v0, 32);
    sw(gpw(kGpSprWrite), v0);
}
void Cpu::rs_ad_packet(u32 pc, s32 shadow, u32 reg) {
    a0 = lui(0x8000);
    a1 = 2;
    jal(pc, gen::fn__rwDMAOpenVIFPkt_004d59d0);  // _rwDMAOpenVIFPkt(0x80000000, 2)
    rs_ad_tail(shadow, reg);
}

// GS register numbers of the A+D packets.
namespace {
constexpr u32 kGsClamp1 = 8, kGsTex1 = 20, kGsFogCol = 61, kGsAlpha1 = 66, kGsTest1 = 71, kGsZbuf1 = 78;
}  // namespace

// _rwSkySetRenderState ($a0 = state, $a1 = value; RenderWare's device render-state entry): the states, as the
// compare chain tests them (13, 30, 29, 20, 16, 15, 14, 12, 11, 10, 9, 8, 7, 6, then 5 / 4 / 3 / 2 / 1 through
// $a2 / $a1 / $v1 / $v0 / $s0, values the handlers of states 1..2 use again):
//    1 texture raster      the raster made resident (sub_4F0F30, RpSkyTexCacheAccessRaster), TME on; its alpha
//                          (format nibble != 6) -> ABE (with the vertex alpha) and ATE, A+D TEST_1 when ATE flips
//    2 / 3 / 4 address     CLAMP_1 WMS + WMT / WMS / WMT: 1 repeat, 3 clamp (2 mirror and 4 border refused)
//    5                     value != 0 clears render flag 0x100 (FST)
//    6 Z test              TEST_1 ZTST: on 2 (GEQUAL), off 1 (ALWAYS), ZTE kept
//    7 shade mode          1 flat / 2 gouraud: render flag 0x08 (IIP)
//    8 Z write             ZBUF_1 ZMSK (and ZTST ALWAYS when the Z test is off), A+D ZBUF_1 + TEST_1
//    9 texture filter      TEX1_1 MMAG/MMIN from the jump table 0x7BCCC0
//   10 / 11 blend          ALPHA_1 = table 0x77EF80 [dest][src] (negative = unsupported); src = dest = 1 adds
//                          FIX 0x80
//   12 vertex alpha        ABE when the vertex alpha or the raster alpha is set
//   13                     refused
//   14 fog                 render flag 0x20 (FGE) and the camera fog bit
//   15 fog colour          FOGCOL (RGB swapped to BGR)
//   16 fog type            1 -> the fog table 0x965610; 2 / 3 refused
//   20 cull mode           camera flag 0x20 (off for 1 = none), the value kept at $gp-16964
//   29 alpha test function TEST_1 ATST from the jump table 0x7BCC30 (ATE cleared from AFAIL when ATE is on)
//   30 alpha test ref      TEST_1 AREF = value * 0.502 (0..255 -> 0..128)
// The shadows are written first; the GS sees them through the A+D packets (and the bridges' packets, which read
// the render flags). Result 1, or 0 for a refused value / state.
void Cpu::set_render_state() {
    enter(7);
    sp = addiu(sp, -48);
    v0 = 13;
    sd(sp + 32, ra);
    sq(sp + 16, s1);
    sq(sp, s0);
    s1 = a1;  // the value
    if (a0 == v0) {
        charge(1);
        v0 = 0;
        charge(2);
        rs_epilogue();
        return;
    }
    static constexpr struct {
        u32 state;
        unsigned reg;
    } kChain[] = {{30, GPR_V0}, {29, GPR_V0}, {20, GPR_V0}, {16, GPR_V0}, {15, GPR_V0}, {14, GPR_V0},
                  {12, GPR_V0}, {11, GPR_V0}, {10, GPR_V0}, {9, GPR_V0},  {8, GPR_V0},  {7, GPR_V0},
                  {6, GPR_V0},  {5, GPR_A2},  {4, GPR_A1},  {3, GPR_V1},  {2, GPR_V0},  {1, GPR_S0}};
    for (const auto& k : kChain) {
        charge(3);
        Gpr reg{c, k.reg};
        reg = k.state;
        if (a0 == reg) {
            if (k.state == 1) {
                rs_raster();
            } else {
                rs_dispatch(k.state);
            }
            return;
        }
    }
    charge(2);
    v0 = 0;
    charge(2);
    rs_epilogue();
}

// State 1: the texture raster.
void Cpu::rs_raster() {
    charge(2);
    sw(gpw(kGpRaster), s1);
    if (s1 == 0) {
        // no raster: TME off, no raster alpha (s0 = 1 stays the result)
        charge(7);
        a0 = ld(gpw(kGpRenderFlags));
        v1 = si(-17);
        sw(gpw(kGpRasterAlpha), zero);
        v0 = 0;
        v1 = a0 & v1;
        sd(gpw(kGpRenderFlags), v1);
        backedge();
    } else {
        charge(7);
        a0 = s1;
        jal(0x4D6C94u, gen::fn_sub_4F0F30_004f0f30);  // speculative cache placement
        a0 = lw(gpw(kGpRaster));
        a1 = 0;
        jal(0x4D6CA0u, gen::fn_RpSkyTexCacheAccessRaster_004f1020);  // RpSkyTexCacheAccessRaster(raster, 0)
        if (v0 == 0) {
            // not resident: no raster, TME off, result 0
            charge(9);
            a0 = ld(gpw(kGpRenderFlags));
            v1 = si(-17);
            sw(gpw(kGpRasterAlpha), zero);
            v0 = 0;
            sw(gpw(kGpRaster), zero);
            s0 = 0;
            v1 = a0 & v1;
            sd(gpw(kGpRenderFlags), v1);
            backedge();
        } else {
            charge(9);
            a0 = ld(gpw(kGpRenderFlags));
            v0 = 6;
            v1 = lw(gpw(kGpRaster));
            a0 = a0 | 0x10;  // TME on
            sd(gpw(kGpRenderFlags), a0);
            v1 = lbu(v1 + 35);
            v1 = v1 & 0xf;  // the pixel format nibble: 6 has no alpha
            if (v1 == v0) {
                charge(3);
                sw(gpw(kGpRasterAlpha), zero);
                v0 = 0;
            } else {
                charge(2);
                v0 = s0;
                charge(1);
                sw(gpw(kGpRasterAlpha), v0);
            }
        }
    }
    // ABE when the vertex alpha or the raster alpha ($v0) is set
    charge(3);
    v1 = lw(gpw(kGpVertexAlpha));
    if (v1 != 0 || (charge(4), v1 = dsll32(v0, 0), v1 = dsra32(v1, 0), v1 != 0)) {
        charge(4);
        v1 = ld(gpw(kGpRenderFlags));
        v1 = v1 | 0x40;
        sd(gpw(kGpRenderFlags), v1);
        backedge();
    } else {
        charge(4);
        a0 = ld(gpw(kGpRenderFlags));
        v1 = si(-65);
        v1 = a0 & v1;
        sd(gpw(kGpRenderFlags), v1);
    }
    // ATE follows the raster alpha; TEST_1 is sent when it changes
    charge(4);
    v0 = dsll32(v0, 0);
    v0 = dsra32(v0, 0);
    if (v0 != 0) {
        charge(4);
        v1 = ld(gpw(kGpTest1));
        v0 = v1 & 0x1;
        if (v0 == 0) {
            charge(21);
            v0 = v1 | 0x1;
            sd(gpw(kGpTest1), v0);
            rs_ad_packet(0x4D6D44u, kGpTest1, kGsTest1);
        }
    } else {
        charge(4);
        v1 = ld(gpw(kGpTest1));
        v0 = v1 & 0x1;
        if (v0 != 0) {
            charge(21);
            v0 = si(-2);
            v0 = v1 & v0;
            sd(gpw(kGpTest1), v0);
            rs_ad_packet(0x4D6DACu, kGpTest1, kGsTest1);
        }
    }
    charge(2);
    v0 = s0;
    rs_epilogue();
}

// States 2..30 (the chain has left the compared constant in its register: $a2 = 5, $a1 = 4, $v1 = 3, $v0 = 2 for
// the states it passed through).
void Cpu::rs_dispatch(u64 state) {
    switch (state) {
    case 2:  // texture address, both directions
        charge(2);
        if (s1 == a1 || (charge(2), s1 == v0)) {  // 4 border, 2 mirror
            charge(1);
            v0 = 0;
            charge(2);
            ra = ld(sp + 32);
            rs_tail();
            return;
        }
        charge(2);
        if (s1 == v1) {  // 3 clamp: WMS = WMT = 1
            charge(1);
            sd(gpw(kGpClamp1), a2);
        } else {
            charge(3);
            v0 = 1;
            if (s1 != v0) {
                charge(2);
                v0 = 0;
                charge(2);
                ra = ld(sp + 32);
                rs_tail();
                return;
            }
            charge(2);  // 1 repeat
            sd(gpw(kGpClamp1), zero);
        }
        charge(19);
        rs_ad_packet(0x4D6E34u, kGpClamp1, kGsClamp1);
        rs_ok();
        return;
    case 3:  // texture address U
    case 4:  // texture address V
    {
        const bool u = state == 3;
        charge(2);
        bool refused = s1 == a1;  // 4 border
        if (!refused) {
            charge(3);
            v0 = 2;
            refused = s1 == v0;  // 2 mirror
        }
        if (refused) {
            charge(1);
            v0 = 0;
            charge(2);
            rs_epilogue();
            return;
        }
        if (u) {
            charge(2);
        } else {
            charge(3);
            v0 = 3;
        }
        if (s1 == (u ? static_cast<u64>(v1) : static_cast<u64>(v0))) {  // 3 clamp
            charge(3);
            v0 = ld(gpw(kGpClamp1));
            v0 = v0 | (u ? 0x1 : 0x4);
            sd(gpw(kGpClamp1), v0);
        } else {
            charge(3);
            v0 = 1;
            if (s1 != v0) {
                charge(2);
                v0 = 0;
                charge(2);
                rs_epilogue();
                return;
            }
            charge(5);  // 1 repeat
            v1 = ld(gpw(kGpClamp1));
            v0 = si(u ? -4 : -13);
            v0 = v1 & v0;
            sd(gpw(kGpClamp1), v0);
        }
        charge(19);
        rs_ad_packet(u ? 0x4D6EDCu : 0x4D6F88u, kGpClamp1, kGsClamp1);
        rs_ok();
        return;
    }
    case 5:
        charge(2);
        if (s1 == 0) {
            rs_fail();
            return;
        }
        charge(5);
        v1 = ld(gpw(kGpRenderFlags));
        v0 = si(-257);
        v0 = v1 & v0;
        sd(gpw(kGpRenderFlags), v0);
        rs_ok();
        return;
    case 6:  // Z test: TEST_1 ZTST = 2 (on) / 1 (off)
        charge(2);
        if (s1 != 0) {
            charge(7);
            a0 = ld(gpw(kGpTest1));
            v0 = lui(0xfff8);
            v1 = v0 | 0xffff;
            v0 = lui(0x5);
            v1 = a0 & v1;
            v0 = v1 | v0;
            sd(gpw(kGpTest1), v0);
        } else {
            charge(8);
            a0 = ld(gpw(kGpTest1));
            v0 = lui(0xfff8);
            v1 = v0 | 0xffff;
            v0 = lui(0x3);
            v1 = a0 & v1;
            v0 = v1 | v0;
            sd(gpw(kGpTest1), v0);
            backedge();
        }
        charge(19);
        rs_ad_packet(0x4D7020u, kGpTest1, kGsTest1);
        rs_ok();
        return;
    case 7:  // shade mode
        charge(3);
        v0 = 1;
        if (s1 == v0) {  // flat
            charge(5);
            v1 = ld(gpw(kGpRenderFlags));
            v0 = si(-9);
            v0 = v1 & v0;
            sd(gpw(kGpRenderFlags), v0);
            backedge();
            rs_ok();
            return;
        }
        charge(3);
        v0 = 2;
        if (s1 == v0) {  // gouraud
            charge(4);
            v0 = ld(gpw(kGpRenderFlags));
            v0 = v0 | 0x8;
            sd(gpw(kGpRenderFlags), v0);
            backedge();
            rs_ok();
            return;
        }
        rs_fail();
        return;
    case 8:  // Z write: ZBUF_1 ZMSK; with the Z test off, ZTST ALWAYS
        charge(2);
        if (s1 != 0) {
            charge(13);
            v0 = si(-2);
            a2 = ld(gpw(kGpZbuf1));
            a1 = dsll32(v0, 0);
            a0 = ld(gpw(kGpTest1));
            v0 = 0xffff;
            v0 = dsll(v0, 16);
            v1 = v0 | 0xffff;
            v0 = lui(0x1);
            v1 = v1 | a1;
            v1 = a2 & v1;  // ZMSK off
            v0 = a0 & v0;  // ZTE
            sd(gpw(kGpZbuf1), v1);
            if (v0 == 0) {
                charge(7);
                v1 = lui(0xfff8);
                v0 = lui(0x3);
                v1 = v1 | 0xffff;
                v1 = a0 & v1;
                v0 = v1 | v0;
                sd(gpw(kGpTest1), v0);
            }
        } else {
            charge(5);
            v1 = ld(gpw(kGpZbuf1));
            v0 = 1;
            v0 = dsll32(v0, 0);
            v0 = v1 | v0;  // ZMSK on
            sd(gpw(kGpZbuf1), v0);
        }
        // A+D ZBUF_1 + TEST_1
        charge(23);
        a0 = lui(0x8000);
        a1 = 3;
        jal(0x4D70F8u, gen::fn__rwDMAOpenVIFPkt_004d59d0);
        a1 = lw(gpw(kGpSprWrite));
        v0 = lui(0x1000);
        v1 = dsll32(v0, 0);
        a0 = 14;
        v0 = 0x8002;
        v0 = v0 | v1;
        pcpyld(v0, a0, v0);
        a0 = kGsZbuf1;
        v1 = kGsTest1;
        sq(a1, v0);
        v0 = ld(gpw(kGpZbuf1));
        pcpyld(v0, a0, v0);
        sq(a1 + 16, v0);
        v0 = ld(gpw(kGpTest1));
        pcpyld(v0, v1, v0);
        sq(a1 + 32, v0);
        v0 = lw(gpw(kGpSprWrite));
        v0 = addiu(v0, 48);
        sw(gpw(kGpSprWrite), v0);
        rs_ok();
        return;
    case 9: {  // texture filter: TEX1_1 MMAG / MMIN (bits 5..8) through the jump table 0x7BCCC0
        charge(3);
        at = sltiu(s1, 7);
        if (at == 0) {
            rs_fail();
            return;
        }
        charge(7);
        v1 = lui(0x7c);
        v0 = sll(s1, 2);
        v1 = addiu(v1, -13120);
        v0 = addu(v0, v1);
        v0 = lw(v0);
        u32 bits;
        u64 cost;
        switch (v0.u()) {
        case 0x4D7178u: bits = 0x000; cost = 5; break;  // 1 nearest
        case 0x4D718Cu: bits = 0x060; cost = 6; break;  // 2 linear
        case 0x4D71A4u: bits = 0x080; cost = 6; break;  // 3 mip nearest
        case 0x4D71BCu: bits = 0x120; cost = 6; break;  // 4 mip linear
        case 0x4D71D4u: bits = 0x0C0; cost = 6; break;  // 5 linear mip nearest
        case 0x4D71ECu: bits = 0x160; cost = 5; break;  // 6 linear mip linear
        case 0x4D724Cu: rs_fail(); return;              // 0
        default: rt::lookup_func(v0.u())(c); return;
        }
        charge(cost);
        v1 = ld(gpw(kGpTex1));
        v0 = si(-481);
        v0 = v1 & v0;
        if (bits != 0) v0 = v0 | bits;
        sd(gpw(kGpTex1), v0);
        charge(19);
        rs_ad_packet(0x4D7204u, kGpTex1, kGsTex1);
        rs_ok();
        return;
    }
    case 10:  // source blend (the jump table 0x7BCC90: 1, 2, 5..8 -> 0..5)
    case 11:  // destination blend (0x7BCC60)
    {
        const bool src = state == 10;
        charge(3);
        at = sltiu(s1, 9);
        if (at == 0) {
            rs_fail();
            return;
        }
        charge(7);
        v1 = lui(0x7c);
        v0 = sll(s1, 2);
        v1 = addiu(v1, src ? -13168 : -13216);
        v0 = addu(v0, v1);
        v0 = lw(v0);
        static constexpr u32 kSrcTargets[6] = {0x4D727Cu, 0x4D7288u, 0x4D7294u, 0x4D72A0u, 0x4D72ACu, 0x4D72B8u};
        static constexpr u32 kDestTargets[6] = {0x4D7398u, 0x4D73A4u, 0x4D73B0u, 0x4D73BCu, 0x4D73C8u, 0x4D73D4u};
        const u32* targets = src ? kSrcTargets : kDestTargets;
        const u32 refused = src ? 0x4D7368u : 0x4D7484u;
        int mode = -1;
        for (int i = 0; i < 6; ++i)
            if (v0.u() == targets[i]) mode = i;
        if (mode < 0) {
            if (v0.u() == refused) {
                rs_fail();
            } else {
                rt::lookup_func(v0.u())(c);
            }
            return;
        }
        const s32 slot = src ? kGpSrcBlend : kGpDestBlend;
        if (mode == 0) {
            charge(3);
            sw(gpw(slot), zero);
            v0 = 0;
        } else {
            charge(mode == 5 ? 2 : 3);
            v0 = static_cast<u64>(mode);
            sw(gpw(slot), v0);
        }
        // ALPHA_1 = kAlphaTable[dest * 6 + src]
        charge(14);
        if (src) {
            a1 = lw(gpw(kGpDestBlend));
            a2 = dsll32(v0, 0);
            v1 = lui(0x78);
            a2 = dsra32(a2, 0);
            v1 = addiu(v1, -4224);
            v0 = sll(a2, 2);
            a0 = sll(a1, 1);
            a0 = addu(a0, a1);
            a0 = sll(a0, 3);
            v1 = addu(v1, a0);
            v0 = addu(v0, v1);
            v1 = lw(v0);
        } else {
            a0 = dsll32(v0, 0);
            a1 = lw(gpw(kGpSrcBlend));
            a0 = dsra32(a0, 0);
            v0 = lui(0x78);
            v1 = sll(a0, 1);
            v0 = addiu(v0, -4224);
            v1 = addu(v1, a0);
            v1 = sll(v1, 3);
            v1 = addu(v0, v1);
            v0 = sll(a1, 2);
            v0 = addu(v0, v1);
            v1 = lw(v0);
        }
        sd(gpw(kGpAlpha1), v1);
        if (ltz(v1)) {  // the combination is not supported
            rs_fail();
            return;
        }
        // src == dest == 1 (one / one): FIX = 0x80
        charge(3);
        v0 = 1;
        const bool first = src ? a2 == v0 : a1 == v0;
        if (first) {
            charge(2);
            const bool second = src ? a1 == v0 : a0 == v0;
            if (second) {
                charge(4);
                v0 = 128;
                v0 = dsll32(v0, 0);
                v0 = v1 | v0;
                sd(gpw(kGpAlpha1), v0);
            }
        }
        charge(19);
        rs_ad_packet(src ? 0x4D7320u : 0x4D743Cu, kGpAlpha1, kGsAlpha1);
        rs_ok();
        return;
    }
    case 12:  // vertex alpha
        charge(3);
        v0 = sltu(zero, s1);
        sw(gpw(kGpVertexAlpha), v0);
        if (v0 != 0 || (charge(3), v0 = lw(gpw(kGpRasterAlpha)), v0 != 0)) {
            charge(4);
            v0 = ld(gpw(kGpRenderFlags));
            v0 = v0 | 0x40;
            sd(gpw(kGpRenderFlags), v0);
            backedge();
        } else {
            charge(5);
            v1 = ld(gpw(kGpRenderFlags));
            v0 = si(-65);
            v0 = v1 & v0;
            sd(gpw(kGpRenderFlags), v0);
        }
        rs_ok();
        return;
    case 14:  // fog: render flag FGE and the camera's fog bit
        charge(2);
        if (s1 != 0) {
            charge(7);
            v1 = ld(gpw(kGpRenderFlags));
            v0 = lbu(gpw(kGpCamFlags));
            v1 = v1 | 0x20;
            v0 = v0 | 0x1;
            sd(gpw(kGpRenderFlags), v1);
            sb(gpw(kGpCamFlags), v0);
        } else {
            charge(8);
            v0 = lbu(gpw(kGpCamFlags));
            v1 = si(-33);
            a0 = ld(gpw(kGpRenderFlags));
            v0 = v0 & 0xfe;
            v1 = a0 & v1;
            sb(gpw(kGpCamFlags), v0);
            sd(gpw(kGpRenderFlags), v1);
        }
        rs_ok();
        return;
    case 15:  // fog colour: FOGCOL = the RGB bytes of the value as B, G, R
        charge(30);
        a0 = lui(0x8000);
        a1 = 2;
        jal(0x4D7500u, gen::fn__rwDMAOpenVIFPkt_004d59d0);
        v0 = lui(0xff);
        v1 = s1 & 0xff00;
        a0 = s1 & v0;
        a1 = 14;
        v0 = s1 & 0xff;
        a0 = srl(a0, 16);
        v0 = sll(v0, 16);
        v1 = a0 | v1;
        v1 = v0 | v1;
        a0 = dsll32(v1, 0);
        v0 = lui(0x1000);
        a0 = dsrl32(a0, 0);
        v1 = dsll32(v0, 0);
        sd(gpw(kGpFogCol), a0);
        v0 = 0x8001;
        a0 = lw(gpw(kGpSprWrite));
        v0 = v0 | v1;
        pcpyld(v0, a1, v0);
        v1 = kGsFogCol;
        sq(a0, v0);
        v0 = ld(gpw(kGpFogCol));
        pcpyld(v0, v1, v0);
        sq(a0 + 16, v0);
        v0 = lw(gpw(kGpSprWrite));
        v0 = addiu(v0, 32);
        sw(gpw(kGpSprWrite), v0);
        rs_ok();
        return;
    case 16:  // fog type: 1 -> the fog table
        charge(3);
        v0 = 3;
        if (s1 != v0) {
            charge(3);
            v0 = 2;
            if (s1 != v0) {
                charge(3);
                v0 = 1;
                if (s1 == v0) {
                    charge(4);
                    v0 = lui(0x96);
                    v0 = addiu(v0, 22032);
                    sw(gpw(kGpFogTable), v0);
                    backedge();
                    rs_ok();
                    return;
                }
            }
        }
        rs_fail();
        return;
    case 20:  // cull mode: camera flag 0x20 unless 1 (none)
        charge(3);
        v0 = 1;
        if (s1 == v0) {
            charge(5);
            v1 = lbu(gpw(kGpCamFlags));
            v0 = si(-33);
            v0 = v1 & v0;
            sb(gpw(kGpCamFlags), v0);
        } else {
            charge(3);
            v0 = lbu(gpw(kGpCamFlags));
            v0 = v0 | 0x20;
            sb(gpw(kGpCamFlags), v0);
        }
        charge(2);
        sw(gpw(kGpCamProjection), s1);
        rs_ok();
        return;
    case 29: {  // alpha test function: TEST_1 ATST (bits 1..3) | ATE through the jump table 0x7BCC30
        charge(3);
        at = sltiu(s1, 9);
        if (at == 0) {
            rs_fail();
            return;
        }
        charge(7);
        v1 = lui(0x7c);
        v0 = sll(s1, 2);
        v1 = addiu(v1, -13264);
        v0 = addu(v0, v1);
        v0 = lw(v0);
        u32 bits;
        u64 cost = 6;
        switch (v0.u()) {
        case 0x4D75FCu: bits = 0x1; break;  // 1 never
        case 0x4D7614u: bits = 0x5; break;  // 2 less
        case 0x4D762Cu: bits = 0x9; break;  // 3 equal
        case 0x4D7644u: bits = 0x7; break;  // 4 less or equal
        case 0x4D765Cu: bits = 0xD; break;  // 5 greater
        case 0x4D7674u: bits = 0xF; break;  // 6 not equal
        case 0x4D768Cu: bits = 0xB; break;  // 7 greater or equal
        case 0x4D76A4u: bits = 0x2; cost = 5; break;  // 8 always (ATE off)
        case 0x4D7720u: rs_fail(); return;  // 0
        default: rt::lookup_func(v0.u())(c); return;
        }
        charge(cost);
        v1 = ld(gpw(kGpTest1));
        v0 = si(-16);
        v0 = v1 & v0;
        v0 = v0 | bits;
        sd(gpw(kGpTest1), v0);
        charge(4);
        v1 = ld(gpw(kGpTest1));
        v0 = v1 & 0x1;
        if (v0 != 0) {  // ATE on: AFAIL = KEEP
            charge(3);
            v0 = si(-12289);
            v0 = v1 & v0;
            sd(gpw(kGpTest1), v0);
        }
        charge(19);
        rs_ad_packet(0x4D76D8u, kGpTest1, kGsTest1);
        rs_ok();
        return;
    }
    case 30:  // alpha test reference: AREF = (int)(value * 0x3F008088) << 4
        charge(35);
        mtc1(s1, F0);
        v0 = lui(0x3f00);
        v0 = v0 | 0x8088;
        a2 = ld(gpw(kGpTest1));
        cvt_s_w(F1, F0);
        v1 = si(-4081);
        a0 = lui(0x8000);
        a1 = 2;
        v1 = a2 & v1;
        mtc1(v0, F0);
        mul_s(F0, F0, F1);
        cvt_w_s(F0, F0);
        mfc1(v0, F0);
        v0 = sll(v0, 4);
        v0 = v1 | v0;
        sd(gpw(kGpTest1), v0);
        jal(0x4D776Cu, gen::fn__rwDMAOpenVIFPkt_004d59d0);
        rs_ad_tail(kGpTest1, kGsTest1);
        rs_ok();
        return;
    default:
        return;  // not reached: the chain only dispatches the states above
    }
}

// =========================================================================================================
// The camera
// =========================================================================================================

}  // namespace sky

namespace {
// The argument registers of a host call (sign-extended 32-bit values; whole registers where the original compares
// them whole); only the registers the function takes are written.
void arg(EEContext& ctx, unsigned r, u64 v) { sky::core::set_gpr64(ctx, r, v); }
u32 v0_of(const EEContext& ctx) { return sky::core::gpr32(ctx, GPR_V0); }
}  // namespace

u32 _rwSkySetRenderState(EEContext& ctx, u64 state, u64 value) {
    arg(ctx, GPR_A0, state);
    arg(ctx, GPR_A1, value);
    sky::Cpu(ctx).set_render_state();
    return v0_of(ctx);
}

// 0x004D84C0 SkyCameraBeginUpdate -- 2484 bytes; frame 0x60: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// SkyCameraBeginUpdate ($a1 = camera; RW's device camera-begin): refuses a frame raster larger than the driver's
// maximum (RwError 0x80000010, result 0); waits in _rwDMAWaitQueue (the queue throttle; $gp-17096 marks that the
// frame's first BeginUpdate has run); FRAME_1 = the camera raster's extension (+8: FBP / FBW / PSM fields) or, for
// a frame-buffer raster (type != 5), this frame's draw buffer; runs the owed cache-raster packet (sub_4F1B30); then
// the draw environment, one 10-qw A+D packet: XYOFFSET_1/2 (field-parity half line when interlaced; the raster's
// centre at 2048), SCISSOR_1/2 (the raster rectangle), TEST_1/2, DTHE (on below 24 bpp), FRAME_1/2. Then the per-camera
// VU1 constants (sub_4EEC20) and the frustum (cam_frustum). 1 on success.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: callee frames ($sp off / deeper stack)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void SkyCameraBeginUpdate(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::cvt_s_w,
          hg::daddiu, hg::di, hg::div_s, hg::dsll, hg::dsll32, hg::dsra32, hg::dsrl32, hg::ei, hg::enter, hg::i64,
          hg::jal, hg::lbu, hg::ld, hg::lh, hg::link, hg::lq, hg::lui, hg::lw, hg::lwc1, hg::madd_s, hg::madda_s,
          hg::mfc0, hg::msub_s, hg::mtc1, hg::mul_s, hg::mula_s, hg::pcpyld, hg::sb, hg::sd, hg::sll, hg::slt,
          hg::sltiu, hg::sq, hg::sra, hg::srl, hg::sub_s, hg::sw, hg::swc1, hg::sync;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x004d84c0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    s2 = a1;
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(a0, a1, 96);
    lw(v0, gp, -16972);  // 0x7CEAA4
    lw(a1, gp, -17120);  // 0x7CEA10
    s1 = addu(s2, v0);
    lw(v1, a0, 12);
    lw(v0, a1, 0);
    at = slt(v0, v1);
    if (at == 0) {
        // 0x004d8508
        charge(ctx, 5);
        lw(v1, a0, 16);
        lw(v0, a1, 4);
        at = slt(v0, v1);
        if (at != 0) {
            goto L_004d851c;
        }
        // 0x004d8544
        charge(ctx, 5);
        jal(ctx, 0x4D8544u, gen::fn__rwDMAWaitQueue_004d53f0);
        lw(v0, gp, -17096);  // 0x7CEA28
        if (v0 == 0) {
            // 0x004d8dc4
            charge(ctx, 3);
            v0 = 1;
            sw(v0, gp, -17096);  // 0x7CEA28
            backedge(ctx);
        }
        // 0x004d8558
        charge(ctx, 6);
        lw(a0, s2, 96);
        v0 = 5;
        lbu(v1, a0, 32);
        v1 = v1 & 0x7;
        if (v1 != v0) {
            // 0x004d8dd8
            charge(ctx, 4);
            lw(v0, gp, -17016);  // g_skyFrameCount
            v0 = v0 & 0x1;
            if (v0 == 0) {
                // 0x004d8df8
                charge(ctx, 4);
                v0 = 0x960000;
                ld(v0, v0, 19296);  // rwDMAFlipData+0x1D0
                sd(v0, gp, -17080);  // 0x7CEA38
                backedge(ctx);
            } else {
                // 0x004d8de8
                charge(ctx, 4);
                v0 = 0x960000;
                ld(v0, v0, 18928);  // rwDMAFlipData+0x60
                sd(v0, gp, -17080);  // 0x7CEA38
                backedge(ctx);
            }
        L_004d85c0:
            charge(ctx, 3);
            lw(v0, gp, -16988);  // 0x7CEA94
            if (v0 != 0) {
                // 0x004d8e08
                charge(ctx, 4);
                jal(ctx, 0x4D8E08u, gen::fn_sub_4F1B30_004f1b30);
                sw(zero, gp, -16988);  // 0x7CEA94
                backedge(ctx);
            }
            // 0x004d85cc
            charge(ctx, 20);
            a0 = lui(0x8000);
            a1 = 10;
            jal(ctx, 0x4D85D0u, gen::fn__rwDMAOpenVIFPkt_004d59d0);
            v0 = 0x10000000;
            a0 = 14;
            v1 = dsll32(v0, 0);
            v0 = 0x8009;
            v1 = v0 | v1;
            lw(v0, gp, -17148);  // 0x7CE9F4
            pcpyld(a0, a0, v1);
            v1 = 5;
            sq(a0, v0, 0);
            lw(v0, gp, -17148);  // 0x7CE9F4
            v0 = addiu(v0, 16);
            sw(v0, gp, -17148);  // 0x7CE9F4
            lw(a0, s2, 96);
            lbu(a0, a0, 32);
            a0 = a0 & 0x7;
            if (a0 == v1) {
                // 0x004d8e18
                charge(ctx, 2);
                sd(zero, gp, -17064);  // 0x7CEA48
                backedge(ctx);
            } else {
                // 0x004d861c
                charge(ctx, 3);
                lbu(v1, gp, -17240);  // g_rwDMAFsaaEnabled
                if (v1 == 0) {
                    // 0x004d8e20
                    charge(ctx, 2);
                    sd(zero, gp, -17064);  // 0x7CEA48
                    backedge(ctx);
                } else {
                    // 0x004d8628
                    charge(ctx, 1);
                    v1 = 0x10000;
                    for (;;) {
                        // 0x004d862c
                        charge(ctx, 7);
                        di(ctx);
                        sync(ctx, 16);
                        mfc0(a0, 12);
                        a0 = a0 & v1;
                        if (a0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004d8648
                    charge(ctx, 10);
                    lbu(a1, gp, -17244);  // 0x7CE994
                    lbu(a0, gp, -17248);  // 0x7CE990
                    lbu(v1, gp, -17220);  // g_rwDMAFlipPending
                    a0 = a0 & 0x1;
                    a0 = a1 ^ a0;
                    v1 = v1 ^ a0;
                    v1 = dsll32(v1, 0);
                    v1 = dsra32(v1, 0);
                    sd(v1, gp, -17064);  // 0x7CEA48
                    ei(ctx);
                }
            }
            // 0x004d8670
            charge(ctx, 6);
            lw(a1, s2, 96);
            v1 = 5;
            lbu(a0, a1, 32);
            a0 = a0 & 0x7;
            if (a0 != v1) {
                // 0x004d8e28
                charge(ctx, 10);
                ld(a1, gp, -17064);  // 0x7CEA48
                ld(a0, gp, -17008);  // 0x7CEA80
                ld(v1, gp, -17000);  // 0x7CEA88
                a1 = dsll32(a1, 3);
                a0 = dsll(a0, 4);
                a0 = a1 | a0;
                v1 = dsll32(v1, 4);
                v1 = v1 | a0;
                sd(v1, gp, -17064);  // 0x7CEA48
                backedge(ctx);
            } else {
                // 0x004d8688
                charge(ctx, 19);
                lw(a3, a1, 0);
                a2 = 2048;
                ld(v1, gp, -17064);  // 0x7CEA48
                lw(a1, a3, 12);
                a0 = dsll32(v1, 3);
                lw(v1, a3, 16);
                a1 = sra(a1, 1);
                a1 = dsll32(a1, 0);
                v1 = sra(v1, 1);
                a1 = dsra32(a1, 0);
                v1 = dsll32(v1, 0);
                a1 = a2 - a1;
                v1 = dsra32(v1, 0);
                a1 = dsll(a1, 4);
                v1 = a2 - v1;
                a0 = a0 | a1;
                v1 = dsll32(v1, 4);
                v1 = v1 | a0;
                sd(v1, gp, -17064);  // 0x7CEA48
            }
            // 0x004d86d4
            charge(ctx, 53);
            ld(t1, gp, -17064);  // 0x7CEA48
            a3 = dsll32(v0, 0);
            t2 = 24;
            v0 = 25;
            a3 = dsra32(a3, 0);
            t0 = 64;
            a2 = 65;
            a1 = 71;
            v1 = 72;
            pcpyld(t2, t2, t1);
            pcpyld(v0, v0, t1);
            sq(t2, a3, 0);
            sq(v0, a3, 16);
            lw(v0, gp, -17148);  // 0x7CE9F4
            v0 = addiu(v0, 32);
            sw(v0, gp, -17148);  // 0x7CE9F4
            lw(v0, s2, 96);
            lw(a3, gp, -17148);  // 0x7CE9F4
            lh(t5, v0, 30);
            lh(t4, v0, 28);
            lw(t3, v0, 12);
            t1 = t5 & 0x7FF;
            t2 = t4 & 0x7FF;
            t1 = dsll32(t1, 0);
            lw(v0, v0, 16);
            t3 = addu(t3, t4);
            t3 = addiu(t3, -1);
            t3 = sll(t3, 16);
            t2 = t2 | t3;
            t1 = t1 | t2;
            v0 = addu(v0, t5);
            v0 = dsll32(v0, 0);
            v0 = dsra32(v0, 0);
            v0 = daddiu(v0, -1);
            v0 = dsll32(v0, 16);
            v0 = t1 | v0;
            pcpyld(t0, t0, v0);
            pcpyld(v0, a2, v0);
            sq(t0, a3, 0);
            sq(v0, a3, 16);
            ld(v0, gp, -17072);  // 0x7CEA40
            pcpyld(a1, a1, v0);
            pcpyld(v0, v1, v0);
            sq(a1, a3, 32);
            sq(v0, a3, 48);
            lw(v0, gp, -17148);  // 0x7CE9F4
            v0 = addiu(v0, 64);
            sw(v0, gp, -17148);  // 0x7CE9F4
            lw(v1, s2, 96);
            lw(v1, v1, 20);
            at = sltiu(v1, 24);
            a0 = 69;
            if (at == 0) {
                // 0x004d87b0
                charge(ctx, 1);
                v1 = 0;
            } else {
                // 0x004d87a8
                charge(ctx, 2);
                v1 = 1;
            }
            // 0x004d87b4
            charge(ctx, 375);
            a2 = dsll32(v0, 0);
            pcpyld(a0, a0, v1);
            a2 = dsra32(a2, 0);
            v1 = 76;
            sq(a0, a2, 0);
            v0 = 77;
            ld(a1, gp, -17080);  // 0x7CEA38
            a0 = s2;
            pcpyld(v1, v1, a1);
            pcpyld(v0, v0, a1);
            sq(v1, a2, 16);
            sq(v0, a2, 32);
            lw(v0, gp, -17148);  // 0x7CE9F4
            v0 = addiu(v0, 48);
            link(ctx, 0x4D87ECu);  // $ra first: the delay slot below depends on it
            sw(v0, gp, -17148);  // 0x7CE9F4
            call(ctx, gen::fn_sub_4EEC20_004eec20);
            lw(a2, s2, 96);
            v1 = 0x3F800000;
            mtc1(v1, f7);
            v0 = 0x44FF0000;
            a0 = v0 | 0xFDFF;
            s0 = addiu(s1, 96);
            mtc1(a0, f12);
            v0 = 0x3F000000;
            mtc1(v0, f5);
            a0 = addiu(s0, 40);
            lw(v1, a2, 16);
            lwc1(f11, s2, 316);
            lw(v0, a2, 12);
            lwc1(f2, s2, 304);
            lwc1(f8, s2, 324);
            a1 = a0;
            lwc1(f0, s2, 312);
            lwc1(f10, s2, 320);
            lwc1(f1, s2, 308);
            v1 = sra(v1, 1);
            mtc1(v1, f4);
            v0 = sra(v0, 1);
            mtc1(v0, f3);
            cvt_s_w(f9, f4);
            sub_s(f4, f2, f11);
            sub_s(f2, f0, f8);
            sub_s(f0, f12, f9);
            div_s(f0, f0, f9);
            cvt_s_w(f6, f3);
            sub_s(f3, f1, f10);
            sub_s(f1, f0, f7);
            sub_s(f0, f12, f6);
            div_s(f0, f0, f6);
            mul_s(f1, f1, f5);
            sub_s(f0, f0, f7);
            mul_s(f0, f0, f5);
            mul_s(f6, f3, f1);
            lwc1(f5, s2, 328);
            lwc1(f3, s2, 336);
            mul_s(f7, f4, f1);
            sub_s(f5, f5, f11);
            mul_s(f9, f2, f1);
            lwc1(f4, s2, 332);
            sub_s(f3, f3, f8);
            mul_s(f5, f5, f0);
            add_s(f8, f7, f5);
            lwc1(f2, s2, 292);
            sub_s(f4, f4, f10);
            mul_s(f4, f4, f0);
            add_s(f2, f2, f8);
            sub_s(f5, f7, f5);
            swc1(f2, s1, 0);
            add_s(f7, f6, f4);
            lwc1(f2, s2, 296);
            mul_s(f3, f3, f0);
            add_s(f2, f2, f7);
            sub_s(f4, f6, f4);
            swc1(f2, s1, 4);
            add_s(f6, f9, f3);
            lwc1(f2, s2, 300);
            sub_s(f3, f9, f3);
            add_s(f2, f2, f6);
            swc1(f2, s1, 8);
            lwc1(f2, s2, 304);
            add_s(f2, f2, f5);
            swc1(f2, s1, 12);
            lwc1(f2, s2, 308);
            add_s(f2, f2, f4);
            swc1(f2, s1, 16);
            lwc1(f2, s2, 312);
            add_s(f2, f2, f3);
            swc1(f2, s1, 20);
            lwc1(f2, s2, 316);
            sub_s(f2, f2, f8);
            swc1(f2, s1, 24);
            lwc1(f2, s2, 320);
            sub_s(f2, f2, f7);
            swc1(f2, s1, 28);
            lwc1(f2, s2, 324);
            sub_s(f2, f2, f6);
            swc1(f2, s1, 32);
            lwc1(f2, s2, 328);
            sub_s(f2, f2, f5);
            swc1(f2, s1, 36);
            lwc1(f2, s2, 332);
            sub_s(f2, f2, f4);
            swc1(f2, s1, 40);
            lwc1(f2, s2, 336);
            sub_s(f2, f2, f3);
            swc1(f2, s1, 44);
            lwc1(f10, s2, 364);
            lwc1(f5, s2, 352);
            lwc1(f8, s2, 372);
            lwc1(f3, s2, 360);
            lwc1(f9, s2, 368);
            lwc1(f4, s2, 356);
            lwc1(f2, s2, 376);
            sub_s(f7, f5, f10);
            sub_s(f5, f3, f8);
            sub_s(f6, f4, f9);
            mul_s(f3, f7, f1);
            sub_s(f4, f2, f10);
            mul_s(f7, f5, f1);
            mul_s(f2, f6, f1);
            mul_s(f1, f4, f0);
            lwc1(f5, s2, 380);
            add_s(f6, f3, f1);
            lwc1(f4, s2, 384);
            sub_s(f5, f5, f9);
            sub_s(f3, f3, f1);
            mul_s(f1, f5, f0);
            sub_s(f4, f4, f8);
            add_s(f5, f2, f1);
            mul_s(f0, f4, f0);
            sub_s(f2, f2, f1);
            add_s(f4, f7, f0);
            sub_s(f1, f7, f0);
            lwc1(f0, s2, 340);
            add_s(f0, f0, f6);
            swc1(f0, s1, 48);
            lwc1(f0, s2, 344);
            add_s(f0, f0, f5);
            swc1(f0, s1, 52);
            lwc1(f0, s2, 348);
            add_s(f0, f0, f4);
            swc1(f0, s1, 56);
            lwc1(f0, s2, 352);
            add_s(f0, f0, f3);
            swc1(f0, s1, 60);
            lwc1(f0, s2, 356);
            add_s(f0, f0, f2);
            swc1(f0, s1, 64);
            lwc1(f0, s2, 360);
            add_s(f0, f0, f1);
            swc1(f0, s1, 68);
            lwc1(f0, s2, 364);
            sub_s(f0, f0, f6);
            swc1(f0, s1, 72);
            lwc1(f0, s2, 368);
            sub_s(f0, f0, f5);
            swc1(f0, s1, 76);
            lwc1(f0, s2, 372);
            sub_s(f0, f0, f4);
            swc1(f0, s1, 80);
            lwc1(f0, s2, 376);
            sub_s(f0, f0, f3);
            swc1(f0, s1, 84);
            lwc1(f0, s2, 380);
            sub_s(f0, f0, f2);
            swc1(f0, s1, 88);
            lwc1(f0, s2, 384);
            sub_s(f0, f0, f1);
            swc1(f0, s1, 92);
            lwc1(f3, s2, 148);
            lwc1(f2, s2, 152);
            lwc1(f1, s2, 156);
            lwc1(f0, s2, 160);
            swc1(f3, s1, 96);
            swc1(f2, s1, 100);
            swc1(f1, s1, 104);
            swc1(f0, s1, 108);
            lwc1(f0, s2, 164);
            swc1(f0, s1, 112);
            lwc1(f3, s2, 168);
            lwc1(f2, s2, 172);
            lwc1(f1, s2, 176);
            lwc1(f0, s2, 180);
            swc1(f3, s1, 116);
            swc1(f2, s1, 120);
            swc1(f1, s1, 124);
            swc1(f0, s1, 128);
            lwc1(f0, s2, 184);
            swc1(f0, s1, 132);
            lwc1(f6, s1, 60);
            lwc1(f3, s1, 12);
            lwc1(f4, s1, 68);
            lwc1(f1, s1, 20);
            lwc1(f0, s1, 72);
            lwc1(f5, s1, 64);
            lwc1(f2, s1, 16);
            sub_s(f20, f3, f6);
            sub_s(f22, f1, f4);
            sub_s(f3, f0, f6);
            lwc1(f1, s1, 76);
            sub_s(f21, f2, f5);
            lwc1(f0, s1, 80);
            sub_s(f2, f1, f5);
            sub_s(f1, f0, f4);
            mula_s(f21, f1);
            msub_s(f0, f22, f2);
            swc1(f0, s1, 136);
            mula_s(f22, f3);
            msub_s(f0, f20, f1);
            swc1(f0, s1, 140);
            mula_s(f20, f2);
            msub_s(f0, f21, f3);
            link(ctx, 0x4D8B04u);  // $ra first: the delay slot below depends on it
            swc1(f0, s1, 144);
            call(ctx, gen::fn_sub_4C6970_004c6970);
            lwc1(f1, s1, 16);
            a0 = addiu(s0, 60);
            lwc1(f0, s0, 44);
            a1 = a0;
            lwc1(f3, s1, 12);
            lwc1(f2, s0, 40);
            lwc1(f5, s1, 20);
            lwc1(f4, s0, 48);
            mula_s(f1, f0);
            madda_s(f3, f2);
            madd_s(f0, f5, f4);
            swc1(f0, s0, 52);
            lw(v0, s0, 40);
            v0 = sra(v0, 31);
            v0 = addiu(v0, 1);
            sb(v0, s0, 56);
            lw(v0, s0, 44);
            v0 = sra(v0, 31);
            v0 = addiu(v0, 1);
            sb(v0, s0, 57);
            lw(v0, s0, 48);
            v0 = sra(v0, 31);
            v0 = addiu(v0, 1);
            sb(v0, s0, 58);
            lwc1(f3, s1, 52);
            lwc1(f2, s1, 64);
            lwc1(f1, s1, 56);
            lwc1(f0, s1, 68);
            lwc1(f5, s1, 48);
            lwc1(f4, s1, 60);
            sub_s(f2, f3, f2);
            sub_s(f1, f1, f0);
            mula_s(f2, f22);
            msub_s(f0, f1, f21);
            sub_s(f4, f5, f4);
            mula_s(f1, f20);
            msub_s(f1, f4, f22);
            swc1(f0, s0, 60);
            mula_s(f4, f21);
            msub_s(f0, f2, f20);
            swc1(f1, s0, 64);
            link(ctx, 0x4D8BB0u);  // $ra first: the delay slot below depends on it
            swc1(f0, s0, 68);
            call(ctx, gen::fn_sub_4C6970_004c6970);
            lwc1(f1, s1, 16);
            a0 = addiu(s0, 80);
            lwc1(f0, s0, 64);
            a1 = a0;
            lwc1(f3, s1, 12);
            lwc1(f2, s0, 60);
            lwc1(f5, s1, 20);
            lwc1(f4, s0, 68);
            mula_s(f1, f0);
            madda_s(f3, f2);
            madd_s(f0, f5, f4);
            swc1(f0, s0, 72);
            lw(v0, s0, 60);
            v0 = sra(v0, 31);
            v0 = addiu(v0, 1);
            sb(v0, s0, 76);
            lw(v0, s0, 64);
            v0 = sra(v0, 31);
            v0 = addiu(v0, 1);
            sb(v0, s0, 77);
            lw(v0, s0, 68);
            v0 = sra(v0, 31);
            v0 = addiu(v0, 1);
            sb(v0, s0, 78);
            lwc1(f6, s1, 84);
            lwc1(f3, s1, 36);
            lwc1(f4, s1, 92);
            lwc1(f1, s1, 44);
            lwc1(f0, s1, 48);
            lwc1(f5, s1, 88);
            lwc1(f2, s1, 40);
            sub_s(f20, f3, f6);
            sub_s(f22, f1, f4);
            sub_s(f3, f0, f6);
            lwc1(f1, s1, 52);
            sub_s(f21, f2, f5);
            lwc1(f0, s1, 56);
            sub_s(f2, f1, f5);
            sub_s(f1, f0, f4);
            mula_s(f21, f1);
            msub_s(f0, f22, f2);
            swc1(f0, s0, 80);
            mula_s(f22, f3);
            msub_s(f0, f20, f1);
            swc1(f0, s0, 84);
            mula_s(f20, f2);
            msub_s(f0, f21, f3);
            link(ctx, 0x4D8C74u);  // $ra first: the delay slot below depends on it
            swc1(f0, s0, 88);
            call(ctx, gen::fn_sub_4C6970_004c6970);
            lwc1(f1, s1, 40);
            a0 = addiu(s0, 100);
            lwc1(f0, s0, 84);
            a1 = a0;
            lwc1(f3, s1, 36);
            lwc1(f2, s0, 80);
            lwc1(f5, s1, 44);
            lwc1(f4, s0, 88);
            mula_s(f1, f0);
            madda_s(f3, f2);
            madd_s(f0, f5, f4);
            swc1(f0, s0, 92);
            lw(v0, s0, 80);
            v0 = sra(v0, 31);
            v0 = addiu(v0, 1);
            sb(v0, s0, 96);
            lw(v0, s0, 84);
            v0 = sra(v0, 31);
            v0 = addiu(v0, 1);
            sb(v0, s0, 97);
            lw(v0, s0, 88);
            v0 = sra(v0, 31);
            v0 = addiu(v0, 1);
            sb(v0, s0, 98);
            lwc1(f3, s1, 76);
            lwc1(f2, s1, 88);
            lwc1(f1, s1, 80);
            lwc1(f0, s1, 92);
            lwc1(f5, s1, 72);
            lwc1(f4, s1, 84);
            sub_s(f2, f3, f2);
            sub_s(f1, f1, f0);
            mula_s(f2, f22);
            msub_s(f0, f1, f21);
            sub_s(f4, f5, f4);
            mula_s(f1, f20);
            msub_s(f1, f4, f22);
            swc1(f0, s0, 100);
            mula_s(f4, f21);
            msub_s(f0, f2, f20);
            swc1(f1, s0, 104);
            link(ctx, 0x4D8D20u);  // $ra first: the delay slot below depends on it
            swc1(f0, s0, 108);
            call(ctx, gen::fn_sub_4C6970_004c6970);
            lwc1(f1, s1, 40);
            a1 = 0x960000;
            lwc1(f0, s0, 104);
            a2 = addiu(s2, 32);
            lwc1(f3, s1, 36);
            a1 = addiu(a1, 21296);  // &0x965330
            lwc1(f2, s0, 100);
            a0 = 8;
            lwc1(f5, s1, 44);
            lwc1(f4, s0, 108);
            mula_s(f1, f0);
            madda_s(f3, f2);
            madd_s(f0, f5, f4);
            swc1(f0, s0, 112);
            lw(v0, s0, 100);
            v0 = sra(v0, 31);
            v0 = addiu(v0, 1);
            sb(v0, s0, 116);
            lw(v0, s0, 104);
            v0 = sra(v0, 31);
            v0 = addiu(v0, 1);
            sb(v0, s0, 117);
            lw(v0, s0, 108);
            v0 = sra(v0, 31);
            v0 = addiu(v0, 1);
            sb(v0, s0, 118);
            for (;;) {
                // 0x004d8d90
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
            // 0x004d8db0
            charge(ctx, 5);
            lw(v1, gp, -16984);  // 0x7CEA98
            v0 = 1;
            v1 = addiu(v1, 1);
            sw(v1, gp, -16984);  // 0x7CEA98
        } else {
            // 0x004d8570
            charge(ctx, 6);
            lw(v1, a0, 0);
            lw(v0, gp, -16968);  // 0x7CEAA8
            v1 = addu(v1, v0);
            lbu(v0, v1, 23);
            if (v0 != 0) {
                // 0x004d8588
                charge(ctx, 14);
                lw(a2, v1, 8);
                v0 = 0x3F000000;
                v1 = 0x3F0000;
                a0 = sll(a2, 2);
                a1 = srl(a2, 5);
                v1 = a0 & v1;
                a0 = a1 & 0x1FF;
                a0 = a0 | v1;
                v1 = sll(a2, 4);
                v0 = v1 & v0;
                v0 = v0 | a0;
                v0 = dsll32(v0, 0);
                v0 = dsrl32(v0, 0);
                sd(v0, gp, -17080);  // 0x7CEA38
                goto L_004d85c0;
            }
            // 0x004d8dd0
            charge(ctx, 2);
            v0 = 0;
        }
        // 0x004d8e50 (the shared epilogue, written out on this path)
        charge(ctx, 9);
        ld(ra, sp, 0x40);
        lwc1(f22, sp, 0x8);
        lq(s2, sp, 0x30);
        lwc1(f21, sp, 0x4);
        lq(s1, sp, 0x20);
        lwc1(f20, sp, 0x0);
        lq(s0, sp, 0x10);
        sp = addiu(sp, 0x60);
        return;
    }
L_004d851c:
    charge(ctx, 10);
    v1 = 1;
    v0 = lui(0x8000);
    sw(v1, sp, 0x58);
    a0 = v0 | 0x10;
    jal(ctx, 0x4D8528u, gen::fn_sub_4C1D10_004c1d10);
    sw(v0, sp, 0x5C);
    a0 = addiu(sp, 0x58);
    jal(ctx, 0x4D8534u, gen::fn_sub_4C1C50_004c1c50);
    v0 = 0;
    // 0x004d8e50 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x40);
    lwc1(f22, sp, 0x8);
    lq(s2, sp, 0x30);
    lwc1(f21, sp, 0x4);
    lq(s1, sp, 0x20);
    lwc1(f20, sp, 0x0);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x60);
}

// 0x004D8F40 sub_4D8F40 -- 1312 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4D8F40 [SkyCameraClear] ($a0 = camera, $a1 = RGBA bytes, $a2 = flags: 1 colour, 2 Z): waits in
// _rwDMAWaitQueue; FRAME_1 as SkyCameraBeginUpdate picks it; one packet of 3 qw per 32-pixel strip + 12: FRAME_1
// with FBMSK 0 (colour) or all ones, ZBUF_1 with ZMSK off (Z) or on, DTHE (below 24 bpp), TEST_1 (ZTE, ZTST
// ALWAYS), XYOFFSET 0, SCISSOR the whole space, PRIM sprite; per strip XYZ2 (x, y0) / RGBAQ (colour, alpha halved
// to the GS's 0x80 scale; 0 without the colour flag) / XYZ2 (x + 32 clipped to the raster, y1); then FRAME_1 /
// ZBUF_1 restored from the shadows and XYOFFSET with this field's half line. 1, or 0 for a camera texture that is
// not resident.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: the hand version terminated the host on a random world.
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_4D8F40(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::cvt_s_w, hg::cvt_w_s,
          hg::daddiu, hg::di, hg::dsll, hg::dsll32, hg::dsra32, hg::dsrl32, hg::ei, hg::enter, hg::i64, hg::jal,
          hg::lbu, hg::ld, hg::lh, hg::lq, hg::lui, hg::lw, hg::mfc0, hg::mfc1, hg::mtc1, hg::mul_s, hg::pcpyld,
          hg::sd, hg::si, hg::sll, hg::slt, hg::sltiu, hg::sq, hg::sra, hg::srl, hg::subu, hg::sw, hg::sync;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x004d8f40
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a2;
    sq(s0, sp, 0x0);
    s1 = a1;
    s0 = a0;
    jal(ctx, 0x4D8F60u, gen::fn__rwDMAWaitQueue_004d53f0);
    lw(a0, s0, 96);
    v0 = 5;
    lbu(v1, a0, 32);
    v1 = v1 & 0x7;
    if (v1 != v0) {
        // 0x004d940c
        charge(ctx, 4);
        lw(v0, gp, -17016);  // g_skyFrameCount
        v0 = v0 & 0x1;
        if (v0 == 0) {
            // 0x004d942c
            charge(ctx, 4);
            v0 = 0x960000;
            ld(v0, v0, 19296);  // rwDMAFlipData+0x1D0
            sd(v0, gp, -17080);  // 0x7CEA38
            backedge(ctx);
        } else {
            // 0x004d941c
            charge(ctx, 4);
            v0 = 0x960000;
            ld(v0, v0, 18928);  // rwDMAFlipData+0x60
            sd(v0, gp, -17080);  // 0x7CEA38
            backedge(ctx);
        }
    L_004d8fd0:
        charge(ctx, 31);
        lw(v0, s0, 96);
        v1 = si(-32);
        a0 = lui(0x8000);
        lh(a2, v0, 28);
        lw(a1, v0, 12);
        a1 = addu(a1, a2);
        v0 = a2 & v1;
        a1 = addiu(a1, 31);
        v1 = a1 & v1;
        v0 = subu(v1, v0);
        s3 = sra(v0, 5);
        v0 = sll(s3, 1);
        v0 = addu(v0, s3);
        a1 = addiu(v0, 12);
        jal(ctx, 0x4D9004u, gen::fn__rwDMAOpenVIFPkt_004d59d0);
        a0 = dsll32(s3, 0);
        v0 = 0x10000000;
        a0 = dsra32(a0, 0);
        v1 = dsll32(v0, 0);
        v0 = dsll(a0, 1);
        lw(a1, gp, -17148);  // 0x7CE9F4
        a0 = v0 + a0;
        v0 = 0x8000;
        v0 = v0 | v1;
        v1 = daddiu(a0, 11);
        v1 = v1 | v0;
        a0 = s2 & 0x1;
        v0 = 14;
        pcpyld(v0, v0, v1);
        sq(v0, a1, 0);
        if (a0 == 0) {
            // 0x004d907c
            charge(ctx, 11);
            ld(a2, gp, -17080);  // 0x7CEA38
            v0 = si(-1);
            v0 = dsll32(v0, 0);
            v1 = 76;
            pcpyld(v0, zero, v0);
            v0 = a2 | v0;
            pcpyld(v0, v1, v0);
            sq(v0, a1, 16);
            lw(v0, gp, -17148);  // 0x7CE9F4
            t0 = addiu(v0, 32);
            sw(t0, gp, -17148);  // 0x7CE9F4
        } else {
            // 0x004d904c
            charge(ctx, 12);
            ld(a2, gp, -17080);  // 0x7CEA38
            v0 = 0xFFFF;
            v0 = dsll(v0, 16);
            v1 = 76;
            v0 = v0 | 0xFFFF;
            v0 = a2 & v0;
            pcpyld(v0, v1, v0);
            sq(v0, a1, 16);
            lw(v0, gp, -17148);  // 0x7CE9F4
            t0 = addiu(v0, 32);
            sw(t0, gp, -17148);  // 0x7CE9F4
        }
        // 0x004d90a8
        charge(ctx, 3);
        v0 = s2 & 0x2;
        if (v0 == 0) {
            // 0x004d90fc
            charge(ctx, 12);
            ld(a1, gp, -17088);  // 0x7CEA30
            v1 = 1;
            v1 = dsll32(v1, 0);
            v0 = dsll32(t0, 0);
            a3 = 78;
            v0 = dsra32(v0, 0);
            v1 = a1 | v1;
            pcpyld(v1, a3, v1);
            sq(v1, v0, 0);
            lw(v0, gp, -17148);  // 0x7CE9F4
            t0 = addiu(v0, 16);
            sw(t0, gp, -17148);  // 0x7CE9F4
        } else {
            // 0x004d90b4
            charge(ctx, 18);
            ld(a1, gp, -17088);  // 0x7CEA30
            v1 = si(-2);
            v0 = 0xFFFF;
            a3 = dsll32(v1, 0);
            v0 = dsll(v0, 16);
            t1 = 78;
            v1 = v0 | 0xFFFF;
            v1 = v1 | a3;
            v0 = dsll32(t0, 0);
            pcpyld(v1, zero, v1);
            v1 = a1 & v1;
            v0 = dsra32(v0, 0);
            pcpyld(v1, t1, v1);
            sq(v1, v0, 0);
            lw(v0, gp, -17148);  // 0x7CE9F4
            t0 = addiu(v0, 16);
            sw(t0, gp, -17148);  // 0x7CE9F4
        }
        // 0x004d912c
        charge(ctx, 5);
        lw(v0, s0, 96);
        lw(v0, v0, 20);
        at = sltiu(v0, 24);
        v1 = 69;
        if (at == 0) {
            // 0x004d9148
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x004d9140
            charge(ctx, 2);
            v0 = 1;
        }
        // 0x004d914c
        charge(ctx, 38);
        t4 = dsll32(t0, 0);
        t2 = 71;
        pcpyld(v0, v1, v0);
        t4 = dsra32(t4, 0);
        v1 = 0;
        sq(v0, t4, 0);
        t0 = 0x30000;
        v0 = lui(0xFFFA);
        ld(t3, gp, -17072);  // 0x7CEA40
        v0 = v0 | 0xBFFE;
        a3 = 64;
        pcpyld(t1, zero, v0);
        v0 = 24;
        t5 = 0;
        pcpyld(t6, v0, v1);
        v1 = 0x7FFF0000;
        t1 = t3 & t1;
        v0 = dsll32(v1, 0);
        t0 = t1 | t0;
        v0 = v1 | v0;
        pcpyld(t0, t2, t0);
        pcpyld(v1, a3, v0);
        sq(t0, t4, 16);
        sq(t6, t4, 32);
        v0 = 6;
        pcpyld(v0, t5, v0);
        sq(v1, t4, 48);
        sq(v0, t4, 64);
        lw(v0, gp, -17148);  // 0x7CE9F4
        t0 = addiu(v0, 80);
        sw(t0, gp, -17148);  // 0x7CE9F4
        lw(t4, s0, 96);
        lh(a3, t4, 28);
        lw(v0, t4, 12);
        t1 = addu(v0, a3);
        at = slt(a3, t1);
        if (at != 0) {
            // 0x004d91e4
            charge(ctx, 4);
            at = slt(a3, t1);
            v1 = 5;
            v0 = 1;
            if (at != 0) {
                // 0x004d91f4
                charge(ctx, 4);
                t1 = 0x3F000000;
                t3 = si(-32);
                t1 = t1 | 0x8312;
                mtc1(t1, f1);
                for (;;) {
                    // 0x004d9204
                    charge(ctx, 12);
                    lh(t2, t4, 30);
                    t0 = dsll32(t0, 0);
                    t1 = sll(a3, 4);
                    t0 = dsra32(t0, 0);
                    t2 = sll(t2, 20);
                    t1 = t2 | t1;
                    pcpyld(t1, v1, t1);
                    sq(t1, t0, 0);
                    lw(t0, gp, -17148);  // 0x7CE9F4
                    t0 = addiu(t0, 16);
                    sw(t0, gp, -17148);  // 0x7CE9F4
                    if (a0 == 0) {
                        // 0x004d92a8
                        charge(ctx, 1);
                        t1 = 0;
                    } else {
                        // 0x004d9234
                        charge(ctx, 3);
                        lbu(t1, s1, 3);
                        if (i64(t1) < 0) {
                            // 0x004d924c
                            charge(ctx, 7);
                            t2 = srl(t1, 1);
                            t1 = t1 & 0x1;
                            t2 = t2 | t1;
                            mtc1(t2, f0);
                            cvt_s_w(f0, f0);
                            add_s(f0, f0, f0);
                        } else {
                            // 0x004d9240
                            charge(ctx, 3);
                            mtc1(t1, f0);
                            cvt_s_w(f0, f0);
                        }
                        // 0x004d9268
                        charge(ctx, 16);
                        mul_s(f0, f1, f0);
                        lbu(t4, s1, 2);
                        lbu(t2, s1, 1);
                        lbu(t1, s1, 0);
                        cvt_w_s(f0, f0);
                        t4 = sll(t4, 16);
                        t2 = sll(t2, 8);
                        mfc1(t5, f0);
                        t5 = sll(t5, 24);
                        t4 = t5 | t4;
                        t2 = t2 | t4;
                        t1 = t1 | t2;
                        t1 = dsll32(t1, 0);
                        t1 = dsrl32(t1, 0);
                    }
                    // 0x004d92ac
                    charge(ctx, 36);
                    t0 = dsll32(t0, 0);
                    pcpyld(t2, v0, t1);
                    t0 = dsra32(t0, 0);
                    t1 = addiu(a3, 32);
                    sq(t2, t0, 0);
                    lw(t0, gp, -17148);  // 0x7CE9F4
                    t0 = addiu(t0, 16);
                    sw(t0, gp, -17148);  // 0x7CE9F4
                    lw(t2, s0, 96);
                    lh(t6, t2, 28);
                    lw(t5, t2, 12);
                    lh(t4, t2, 30);
                    t5 = addu(t5, t6);
                    lw(t2, t2, 16);
                    at = slt(t5, t1);
                    if (at == 0) t5 = t1;
                    t2 = addu(t2, t4);
                    t2 = sll(t2, 20);
                    t1 = sll(t5, 4);
                    t0 = dsll32(t0, 0);
                    t1 = t2 | t1;
                    a3 = addiu(a3, 32);
                    t0 = dsra32(t0, 0);
                    a3 = a3 & t3;
                    pcpyld(t1, v1, t1);
                    sq(t1, t0, 0);
                    lw(t0, gp, -17148);  // 0x7CE9F4
                    t0 = addiu(t0, 16);
                    sw(t0, gp, -17148);  // 0x7CE9F4
                    lw(t4, s0, 96);
                    lh(t2, t4, 28);
                    lw(t1, t4, 12);
                    t1 = addu(t1, t2);
                    t1 = slt(a3, t1);
                    if (t1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
        // 0x004d933c
        charge(ctx, 11);
        v1 = dsll32(t0, 0);
        v0 = 76;
        v1 = dsra32(v1, 0);
        pcpyld(v0, v0, a2);
        sq(v0, v1, 0);
        v0 = 78;
        pcpyld(v0, v0, a1);
        sq(v0, v1, 16);
        lbu(v0, gp, -17240);  // g_rwDMAFsaaEnabled
        if (v0 == 0) {
            // 0x004d943c
            charge(ctx, 2);
            v0 = 0;
            backedge(ctx);
        } else {
            // 0x004d9368
            charge(ctx, 1);
            v0 = 0x10000;
            for (;;) {
                // 0x004d936c
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
            // 0x004d9388
            charge(ctx, 9);
            lbu(a0, gp, -17244);  // 0x7CE994
            lbu(v1, gp, -17248);  // 0x7CE990
            lbu(v0, gp, -17220);  // g_rwDMAFlipPending
            v1 = v1 & 0x1;
            v1 = a0 ^ v1;
            v0 = v0 ^ v1;
            v0 = dsll32(v0, 0);
            v0 = dsra32(v0, 0);
            ei(ctx);
        }
        // 0x004d93ac
        charge(ctx, 22);
        ld(t0, gp, -17064);  // 0x7CEA48
        a2 = dsll32(v0, 3);
        v0 = 0xFFFF;
        v1 = si(-9);
        v0 = dsll(v0, 16);
        lw(a0, gp, -17148);  // 0x7CE9F4
        v1 = dsll32(v1, 0);
        v0 = v0 | 0xFFFF;
        a3 = v0 | v1;
        a1 = 24;
        v1 = 25;
        v0 = 1;
        a3 = t0 & a3;
        a2 = a3 | a2;
        pcpyld(a1, a1, a2);
        pcpyld(v1, v1, a2);
        sq(a1, a0, 32);
        sq(v1, a0, 48);
        lw(v1, gp, -17148);  // 0x7CE9F4
        t0 = addiu(v1, 64);
        sw(t0, gp, -17148);  // 0x7CE9F4
    } else {
        // 0x004d8f80
        charge(ctx, 6);
        lw(v1, a0, 0);
        lw(v0, gp, -16968);  // 0x7CEAA8
        v1 = addu(v1, v0);
        lbu(v0, v1, 23);
        if (v0 != 0) {
            // 0x004d8f98
            charge(ctx, 14);
            lw(a2, v1, 8);
            v0 = 0x3F000000;
            v1 = 0x3F0000;
            a0 = sll(a2, 2);
            a1 = srl(a2, 5);
            v1 = a0 & v1;
            a0 = a1 & 0x1FF;
            a0 = a0 | v1;
            v1 = sll(a2, 4);
            v0 = v1 & v0;
            v0 = v0 | a0;
            v0 = dsll32(v0, 0);
            v0 = dsrl32(v0, 0);
            sd(v0, gp, -17080);  // 0x7CEA38
            goto L_004d8fd0;
        }
        // 0x004d9404
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004d9444 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x004E3640 sub_4E3640 -- 2036 bytes; frame 0xC0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4E3640 [raster mip-map chain on the GS] ($a0 = raster): for a raster with mip levels (ext +22 >> 2), one packet
// that renders level n + 1 from level n with bilinear sprites, for every level: TEXFLUSH-free set-up (TEX1_1 LCM /
// MXL, TEST_1 ZTST ALWAYS, ZBUF_1 masked, PRIM sprite textured), then per level: TEX0_1 of level n (TBP from the
// extension's MIPTBP words +24..+39 through the jump table 0x7BCF40; level 0 keeps TEX0), FRAME_1 of level n + 1
// (0x7BCF20: its TBP / 32 as FBP, the width, PSM), the PSM-dependent pixel offset of the destination (PSMT8 /
// PSMT4 swizzle steps), XYOFFSET, then the destination in 64-pixel-wide sprite columns (UV in 32-pixel steps of the
// source). TEST_1 / ZBUF_1 / CLAMP_1 restored from the shadows at the end, and a texture-cache upload marked owed
// ($gp-16988). s3 counts the extra packet quadwords of the levels wider than 64 pixels.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: the hand version terminated the host on a random world.
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_4E3640(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::dsll, hg::dsll32, hg::dsra32, hg::dsrl,
          hg::dsrl32, hg::enter, hg::i64, hg::jal, hg::lbu, hg::ld, hg::lq, hg::lui, hg::lw, hg::lwu, hg::pcpyld,
          hg::sd, hg::si, hg::sll, hg::slt, hg::sltiu, hg::sltu, hg::sq, hg::sra, hg::srl, hg::sw, hg::tail;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004e3640
    enter(ctx, 18);  // entry check point + this block's cycles
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
    s2 = a0;
    sq(s0, sp, 0x0);
    lw(v1, gp, -16968);  // 0x7CEAA8
    s1 = addu(s2, v1);
    lbu(v1, s1, 22);
    a1 = sra(v1, 2);
    if (a1 != 0) {
        // 0x004e3688
        charge(ctx, 9);
        lw(v0, s1, 8);
        s3 = 0;
        lw(a2, s2, 12);
        a3 = a1;
        a0 = v0 & 0x3FFF;
        v0 = dsll(a0, 20);
        v1 = dsll32(a0, 8);
        v0 = a0 | v0;
        s0 = v1 | v0;
        for (;;) {
            // 0x004e36ac
            charge(ctx, 4);
            v0 = sltu(0, a3);
            v0 = v0 ^ 0x1;
            if (v0 == 0) {
                // 0x004e36bc
                charge(ctx, 3);
                at = sltiu(a2, 65);
                if (at == 0) {
                    // 0x004e36c8
                    charge(ctx, 7);
                    v0 = srl(a2, 6);
                    a3 = addiu(a3, -1);
                    v0 = addiu(v0, -1);
                    a2 = srl(a2, 1);
                    v0 = sll(v0, 2);
                    s3 = addu(s3, v0);
                    backedge(ctx);
                    continue;
                }
            }
            break;
        }
        // 0x004e36f0
        charge(ctx, 57);
        v1 = addiu(a1, 1);
        a0 = lui(0x8000);
        v0 = sll(v1, 3);
        v0 = addu(v0, v1);
        a1 = addu(v0, s3);
        jal(ctx, 0x4E3700u, gen::fn__rwDMAOpenVIFPkt_004d59d0);
        lbu(a1, s1, 22);
        v1 = 0x108B0000;
        a0 = v1 | 0x4000;
        lw(t1, gp, -17148);  // 0x7CE9F4
        v1 = 0x8000;
        a0 = dsll32(a0, 0);
        t3 = v1 | a0;
        t2 = 14;
        a0 = 20;
        v1 = 96;
        pcpyld(v1, a0, v1);
        a2 = sra(a1, 2);
        t0 = 71;
        a1 = sll(a2, 3);
        a0 = 0x30000;
        a1 = addu(a1, a2);
        a2 = addiu(a1, 8);
        a1 = 1;
        a3 = dsll32(a1, 0);
        a1 = addu(s3, a2);
        t4 = dsll32(a1, 0);
        a2 = 78;
        t4 = dsra32(t4, 0);
        a1 = 8;
        t3 = t4 | t3;
        pcpyld(t2, t2, t3);
        sq(t2, t1, 0);
        sq(v1, t1, 16);
        pcpyld(t2, t0, a0);
        sq(t2, t1, 32);
        v1 = 5;
        ld(t4, gp, -17088);  // 0x7CEA30
        pcpyld(t0, a1, v1);
        v1 = 24;
        a1 = 0;
        pcpyld(a1, v1, a1);
        v1 = t4 | a3;
        pcpyld(v1, a2, v1);
        sq(v1, t1, 48);
        sq(t0, t1, 64);
        sq(a1, t1, 80);
        lw(v1, gp, -17148);  // 0x7CE9F4
        v1 = addiu(v1, 96);
        sw(v1, gp, -17148);  // 0x7CE9F4
        lbu(a1, s1, 22);
        lw(t7, s2, 12);
        lw(s5, s2, 16);
        a3 = sra(a1, 2);
        at = slt(0, a3);
        t8 = 0;
        if (at != 0) {
            // 0x004e37d4
            charge(ctx, 5);
            at = slt(0, a3);
            a2 = 63;
            t0 = 0;
            a1 = 0x10000;
            if (at != 0) {
                // 0x004e37e8
                charge(ctx, 21);
                a3 = a0 | 0xF000;
                a0 = 76;
                pcpyld(s3, a0, a1);
                a0 = lui(0xFFF0);
                a1 = si(-2);
                pcpyld(t3, zero, a0);
                a0 = 0xAC00;
                a1 = dsll32(a1, 0);
                a0 = dsll(a0, 16);
                a0 = a0 | a1;
                sq(a0, sp, 0xB0);
                pcpyld(s4, a2, t0);
                a0 = 0xF000;
                a2 = si(-1);
                a0 = dsll(a0, 16);
                t0 = a0 | a1;
                a1 = dsll32(a2, 0);
                a0 = 0x34000000;
                a2 = 0x78000000;
                t1 = a0 | a1;
                t2 = a2 | a1;
                for (;;) {
                    // 0x004e383c
                    charge(ctx, 11);
                    lw(a2, s1, 12);
                    a0 = si(-25);
                    lwu(a1, s1, 8);
                    at = sltiu(t8, 6);
                    a0 = a2 & a0;
                    a0 = a0 | 0x8;
                    a0 = dsll32(a0, 0);
                    a0 = dsrl32(a0, 0);
                    a0 = dsll32(a0, 0);
                    a0 = a1 | a0;
                    if (at != 0) {
                        // 0x004e3868
                        charge(ctx, 7);
                        a1 = 0x7C0000;
                        a2 = sll(t8, 2);
                        a1 = addiu(a1, -12480);  // "P9N"
                        a1 = addu(a2, a1);
                        lw(a1, a1, 0);
                        switch (a1.u()) {
                        case 0x4E3884u:  // table[1]
                            // 0x004e3884
                            charge(ctx, 9);
                            lwu(a2, s1, 24);
                            a1 = a0 & t3;
                            a0 = a2 + s0;
                            a0 = dsll32(a0, 12);
                            a0 = dsrl32(a0, 12);
                            a1 = a1 | a0;
                            a0 = lui(0xBC00);
                            a0 = a1 + a0;
                            break;
                        case 0x4E38A8u:  // table[2]
                            // 0x004e38a8
                            charge(ctx, 12);
                            a1 = a0 & t3;
                            lwu(a2, s1, 24);
                            lwu(a0, s1, 28);
                            a0 = dsll32(a0, 0);
                            a0 = a2 | a0;
                            a0 = a0 + s0;
                            a0 = dsrl(a0, 20);
                            a0 = dsll32(a0, 12);
                            a0 = dsrl32(a0, 12);
                            a0 = a1 | a0;
                            a0 = a0 + t2;
                            break;
                        case 0x4E38D8u:  // table[3]
                            // 0x004e38d8
                            charge(ctx, 10);
                            lwu(a2, s1, 28);
                            a1 = a0 & t3;
                            a0 = dsll32(a2, 0);
                            a0 = a0 + s0;
                            a0 = dsrl32(a0, 8);
                            a0 = dsll32(a0, 12);
                            a0 = dsrl32(a0, 12);
                            a0 = a1 | a0;
                            a0 = a0 + t1;
                            break;
                        case 0x4E3900u:  // table[4]
                            // 0x004e3900
                            charge(ctx, 8);
                            lwu(a2, s1, 32);
                            a1 = a0 & t3;
                            a0 = a2 + s0;
                            a0 = dsll32(a0, 12);
                            a0 = dsrl32(a0, 12);
                            a0 = a1 | a0;
                            a0 = a0 + t0;
                            break;
                        case 0x4E3920u:  // table[5]
                            // 0x004e3920
                            charge(ctx, 12);
                            a1 = a0 & t3;
                            lwu(a2, s1, 32);
                            lwu(a0, s1, 36);
                            a0 = dsll32(a0, 0);
                            a0 = a2 | a0;
                            a0 = a0 + s0;
                            a0 = dsrl(a0, 20);
                            a0 = dsll32(a0, 12);
                            a0 = dsrl32(a0, 12);
                            a1 = a1 | a0;
                            lq(a0, sp, 0xB0);
                            a0 = a1 + a0;
                            break;
                        case 0x4E3950u:  // table[0]
                            break;
                        default:  // not one of the table's targets: the dispatch table, as the recompiled body
                            tail(ctx, a1.u());
                            return;
                        }
                    }
                    // 0x004e3950
                    charge(ctx, 13);
                    a1 = 6;
                    v1 = dsll32(v1, 0);
                    pcpyld(a2, a1, a0);
                    v1 = dsra32(v1, 0);
                    a1 = 0x3F00000;
                    sq(a2, v1, 0);
                    a0 = a0 & a1;
                    lw(v1, gp, -17148);  // 0x7CE9F4
                    at = sltiu(t8, 6);
                    a0 = dsll(a0, 4);
                    v1 = addiu(v1, 16);
                    sw(v1, gp, -17148);  // 0x7CE9F4
                    if (at == 0) {
                        // 0x004e3af0
                        charge(ctx, 1);
                        a1 = 0;
                    } else {
                        // 0x004e3984
                        charge(ctx, 7);
                        a1 = 0x7C0000;
                        a2 = sll(t8, 2);
                        a1 = addiu(a1, -12512);  // &0x7BCF20
                        a1 = addu(a2, a1);
                        lw(a1, a1, 0);
                        switch (a1.u()) {
                        case 0x4E39A0u:  // table[0]
                            // 0x004e39a0
                            charge(ctx, 12);
                            lwu(a1, s1, 24);
                            t5 = a1 + s0;
                            a2 = dsll(t5, 2);
                            a1 = dsrl(t5, 5);
                            a2 = a2 & a3;
                            a1 = a1 & 0x1FF;
                            a2 = a2 | a1;
                            a1 = t5 & 0x1F;
                            a0 = a0 | a2;
                            a1 = dsll32(a1, 0);
                            a1 = dsra32(a1, 0);
                            break;
                        case 0x4E39D0u:  // table[1]
                            // 0x004e39d0
                            charge(ctx, 16);
                            lwu(a1, s1, 28);
                            lwu(a2, s1, 24);
                            a1 = dsll32(a1, 0);
                            a1 = a2 | a1;
                            t5 = a1 + s0;
                            a2 = dsrl(t5, 18);
                            a1 = dsrl(t5, 25);
                            a2 = a2 & a3;
                            a1 = a1 & 0x1FF;
                            a2 = a2 | a1;
                            a1 = dsrl(t5, 20);
                            a0 = a0 | a2;
                            a1 = a1 & 0x1F;
                            a1 = dsll32(a1, 0);
                            a1 = dsra32(a1, 0);
                            break;
                        case 0x4E3A10u:  // table[2]
                            // 0x004e3a10
                            charge(ctx, 14);
                            lwu(a1, s1, 28);
                            a1 = dsll32(a1, 0);
                            t5 = a1 + s0;
                            a2 = dsrl32(t5, 6);
                            a1 = dsrl32(t5, 13);
                            a2 = a2 & a3;
                            a1 = a1 & 0x1FF;
                            a2 = a2 | a1;
                            a1 = dsrl32(t5, 8);
                            a0 = a0 | a2;
                            a1 = a1 & 0x1F;
                            a1 = dsll32(a1, 0);
                            a1 = dsra32(a1, 0);
                            break;
                        case 0x4E3A48u:  // table[3]
                            // 0x004e3a48
                            charge(ctx, 12);
                            lwu(a1, s1, 32);
                            t5 = a1 + s0;
                            a2 = dsll(t5, 2);
                            a1 = dsrl(t5, 5);
                            a2 = a2 & a3;
                            a1 = a1 & 0x1FF;
                            a2 = a2 | a1;
                            a1 = t5 & 0x1F;
                            a0 = a0 | a2;
                            a1 = dsll32(a1, 0);
                            a1 = dsra32(a1, 0);
                            break;
                        case 0x4E3A78u:  // table[4]
                            // 0x004e3a78
                            charge(ctx, 16);
                            lwu(a1, s1, 36);
                            lwu(a2, s1, 32);
                            a1 = dsll32(a1, 0);
                            a1 = a2 | a1;
                            t5 = a1 + s0;
                            a2 = dsrl(t5, 18);
                            a1 = dsrl(t5, 25);
                            a2 = a2 & a3;
                            a1 = a1 & 0x1FF;
                            a2 = a2 | a1;
                            a1 = dsrl(t5, 20);
                            a0 = a0 | a2;
                            a1 = a1 & 0x1F;
                            a1 = dsll32(a1, 0);
                            a1 = dsra32(a1, 0);
                            break;
                        case 0x4E3AB8u:  // table[5]
                            // 0x004e3ab8
                            charge(ctx, 14);
                            lwu(a1, s1, 36);
                            a1 = dsll32(a1, 0);
                            t5 = a1 + s0;
                            a2 = dsrl32(t5, 6);
                            a1 = dsrl32(t5, 13);
                            a2 = a2 & a3;
                            a1 = a1 & 0x1FF;
                            a2 = a2 | a1;
                            a1 = dsrl32(t5, 8);
                            a0 = a0 | a2;
                            a1 = a1 & 0x1F;
                            a1 = dsll32(a1, 0);
                            a1 = dsra32(a1, 0);
                            break;
                        default:  // not one of the table's targets: the dispatch table, as the recompiled body
                            tail(ctx, a1.u());
                            return;
                        }
                    }
                    // 0x004e3af4
                    charge(ctx, 10);
                    v1 = dsll32(v1, 0);
                    t5 = dsrl(a0, 24);
                    a2 = 76;
                    v1 = dsra32(v1, 0);
                    pcpyld(a0, a2, a0);
                    sq(a0, v1, 0);
                    a2 = t5 & 0x3F;
                    a0 = 10;
                    if (a2 == a0) {
                        // 0x004e3ba0
                        charge(ctx, 18);
                        a0 = si(-32);
                        t5 = a1 & a0;
                        a0 = a1 & 0x1;
                        a2 = sll(a0, 2);
                        a0 = a1 & 0x2;
                        a2 = t5 | a2;
                        a0 = sra(a0, 1);
                        t5 = a0 | a2;
                        a0 = a1 & 0x4;
                        a2 = a1 & 0x8;
                        a0 = sll(a0, 2);
                        t5 = a0 | t5;
                        a0 = a1 & 0x10;
                        a1 = a2 | t5;
                        a0 = sra(a0, 3);
                        a2 = a0 | a1;
                        a0 = sra(a2, 2);
                        if (i64(a2) < 0) {
                            // 0x004e3be8
                            charge(ctx, 2);
                            a0 = addiu(a2, 3);
                            a0 = sra(a0, 2);
                        }
                        // 0x004e3bf0
                        charge(ctx, 3);
                        a1 = sll(a0, 3);
                        a0 = a2 & 0x3;
                        if (i64(a2) < 0) {
                            // 0x004e3bfc
                            charge(ctx, 2);
                            if (a0 != 0) {
                                // 0x004e3c04
                                charge(ctx, 1);
                                a0 = addiu(a0, -4);
                            }
                        }
                        // 0x004e3c08
                        charge(ctx, 2);
                        t5 = sll(a0, 4);
                    } else {
                        // 0x004e3b1c
                        charge(ctx, 3);
                        a0 = 1;
                        if (a2 != a0) {
                            // 0x004e3b28
                            charge(ctx, 2);
                            if (a2 == 0) {
                                goto L_004e3b38;
                            }
                            // 0x004e3b30
                            charge(ctx, 2);
                            a1 = 0;
                            // 0x004e3c10
                            charge(ctx, 1);
                            t5 = 0;
                            goto L_004e3c14;
                        }
                    L_004e3b38:
                        charge(ctx, 16);
                        a0 = si(-31);
                        t5 = a1 & 0x2;
                        a2 = a1 & a0;
                        t5 = sll(t5, 2);
                        a0 = a1 & 0x4;
                        a2 = t5 | a2;
                        a0 = sra(a0, 1);
                        t5 = a0 | a2;
                        a0 = a1 & 0x8;
                        a2 = sll(a0, 1);
                        a0 = a1 & 0x10;
                        a1 = a2 | t5;
                        a0 = sra(a0, 2);
                        a2 = a0 | a1;
                        a0 = sra(a2, 3);
                        if (i64(a2) < 0) {
                            // 0x004e3b78
                            charge(ctx, 2);
                            a0 = addiu(a2, 7);
                            a0 = sra(a0, 3);
                        }
                        // 0x004e3b80
                        charge(ctx, 3);
                        a1 = sll(a0, 3);
                        a0 = a2 & 0x7;
                        if (i64(a2) < 0) {
                            // 0x004e3b8c
                            charge(ctx, 2);
                            if (a0 != 0) {
                                // 0x004e3b94
                                charge(ctx, 1);
                                a0 = addiu(a0, -8);
                            }
                        }
                        // 0x004e3b98
                        charge(ctx, 2);
                        t5 = sll(a0, 3);
                    }
                L_004e3c14:
                    charge(ctx, 29);
                    s2 = srl(t7, 1);
                    t6 = dsll32(t5, 0);
                    a2 = addu(t5, s2);
                    a0 = srl(s5, 1);
                    a2 = addiu(a2, -1);
                    t6 = dsra32(t6, 0);
                    s6 = dsll32(a2, 0);
                    a0 = addu(a1, a0);
                    s6 = dsrl32(s6, 0);
                    a2 = dsll32(a1, 0);
                    s6 = dsll(s6, 16);
                    a2 = dsra32(a2, 0);
                    s6 = t6 | s6;
                    a2 = dsll32(a2, 0);
                    t6 = addiu(a0, -1);
                    a2 = a2 | s6;
                    t6 = dsll32(t6, 0);
                    at = sltu(0, t7);
                    t6 = dsrl32(t6, 0);
                    s6 = dsll32(t6, 16);
                    s6 = a2 | s6;
                    t6 = 0;
                    a2 = 64;
                    pcpyld(a2, a2, s6);
                    sq(a2, v1, 16);
                    lw(v1, gp, -17148);  // 0x7CE9F4
                    v1 = addiu(v1, 32);
                    sw(v1, gp, -17148);  // 0x7CE9F4
                    if (at != 0) {
                        // 0x004e3c88
                        charge(ctx, 3);
                        at = sltu(0, t7);
                        if (at != 0) {
                            // 0x004e3c94
                            charge(ctx, 6);
                            a0 = sll(a0, 20);
                            s7 = sll(a1, 20);
                            sq(a0, sp, 0xA0);
                            t9 = 0;
                            a0 = addiu(s5, 1);
                            fp = sll(a0, 20);
                            for (;;) {
                                // 0x004e3cac
                                charge(ctx, 21);
                                a1 = dsll32(v1, 0);
                                a0 = addu(t5, t9);
                                v1 = addiu(t6, 1);
                                a1 = dsra32(a1, 0);
                                a2 = sll(v1, 4);
                                at = sltiu(t7, 64);
                                v1 = 0x100000;
                                a2 = a2 | v1;
                                v1 = sll(a0, 4);
                                a2 = dsll32(a2, 0);
                                s6 = s7 | v1;
                                a2 = dsrl32(a2, 0);
                                v1 = 3;
                                pcpyld(v1, v1, a2);
                                sq(v1, a1, 0);
                                a2 = dsll32(s6, 0);
                                a2 = dsrl32(a2, 0);
                                v1 = 5;
                                pcpyld(v1, v1, a2);
                                sq(v1, a1, 16);
                                if (at == 0) {
                                    // 0x004e3d08
                                    charge(ctx, 1);
                                    v1 = 64;
                                } else {
                                    // 0x004e3d00
                                    charge(ctx, 2);
                                    v1 = t7;
                                }
                                // 0x004e3d0c
                                charge(ctx, 11);
                                v1 = addiu(v1, 1);
                                at = sltiu(s2, 64);
                                v1 = addu(t6, v1);
                                v1 = sll(v1, 4);
                                v1 = fp | v1;
                                a2 = dsll32(v1, 0);
                                a2 = dsrl32(a2, 0);
                                v1 = 3;
                                pcpyld(v1, v1, a2);
                                sq(v1, a1, 32);
                                if (at == 0) {
                                    // 0x004e3d40
                                    charge(ctx, 1);
                                    v1 = 32;
                                } else {
                                    // 0x004e3d38
                                    charge(ctx, 2);
                                    v1 = s2;
                                }
                                // 0x004e3d44
                                charge(ctx, 16);
                                v1 = addu(a0, v1);
                                t6 = addiu(t6, 64);
                                a0 = sll(v1, 4);
                                t9 = addiu(t9, 32);
                                lq(v1, sp, 0xA0);
                                v1 = v1 | a0;
                                a2 = dsll32(v1, 0);
                                a0 = sltu(t6, t7);
                                a2 = dsrl32(a2, 0);
                                v1 = 5;
                                pcpyld(v1, v1, a2);
                                sq(v1, a1, 48);
                                lw(v1, gp, -17148);  // 0x7CE9F4
                                v1 = addiu(v1, 64);
                                sw(v1, gp, -17148);  // 0x7CE9F4
                                if (a0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                        }
                    }
                    // 0x004e3d84
                    charge(ctx, 14);
                    v1 = dsll32(v1, 0);
                    t8 = addiu(t8, 1);
                    v1 = dsra32(v1, 0);
                    t7 = srl(t7, 1);
                    sq(s4, v1, 0);
                    sq(s3, v1, 16);
                    lw(v1, gp, -17148);  // 0x7CE9F4
                    v1 = addiu(v1, 32);
                    sw(v1, gp, -17148);  // 0x7CE9F4
                    lbu(a0, s1, 22);
                    a0 = sra(a0, 2);
                    a0 = slt(t8, a0);
                    s5 = srl(s5, 1);
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
        // 0x004e3dbc
        charge(ctx, 19);
        ld(a2, gp, -17072);  // 0x7CEA40
        a1 = dsll32(v1, 0);
        a0 = 1;
        v1 = 78;
        sw(a0, gp, -16988);  // 0x7CEA94
        pcpyld(a3, v1, t4);
        a0 = 71;
        a1 = dsra32(a1, 0);
        v1 = 8;
        pcpyld(a0, a0, a2);
        sq(a0, a1, 0);
        sq(a3, a1, 16);
        ld(a0, gp, -17048);  // 0x7CEA58
        pcpyld(v1, v1, a0);
        sq(v1, a1, 32);
        lw(v1, gp, -17148);  // 0x7CE9F4
        v1 = addiu(v1, 48);
        sw(v1, gp, -17148);  // 0x7CE9F4
        backedge(ctx);
    }
    // 0x004e36e8
    charge(ctx, 2);
    ld(ra, sp, 0x90);
    // 0x004e3e08
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

// 0x004F0C70 sub_4F0C70 -- 704 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4F0C70 [texture-cache PATH3 upload] ($a0 = raster): a raster with a cache slot (ext +88), the "uploadable" flag
// (raster +33 bit 6) and ext +54 bit 0 gets its image queued through sub_4D6250 (PATH3): the raster's 4-qw GIF
// header (BITBLTBUF with the slot's GS address patched in at bits 32.., ext +44 the image size) and its 80-byte
// TRXPOS / TRXREG / TRXDIR block, then the pixels by quadword groups of 4 (or 2 for a < 64-byte tail), closed with a
// DIRECT tag. When it is the cache's current raster, a TEXFLUSH + TEX0 A+D packet re-binds it. 1 when queued.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_4F0C70(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::dsll, hg::dsll32, hg::dsra32, hg::dsrl32,
          hg::enter, hg::jal, hg::lbu, hg::ld, hg::lq, hg::lui, hg::lw, hg::lwu, hg::pcpyld, hg::sd, hg::si, hg::sll,
          hg::sltiu, hg::sq, hg::srl, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f0c70
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    lw(v0, gp, -16968);  // 0x7CEAA8
    s1 = addu(s2, v0);
    lw(v0, s1, 88);
    if (v0 == 0) {
        // 0x004f0cc4
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004f0c9c
        charge(ctx, 4);
        lbu(v0, s2, 33);
        v0 = v0 & 0x40;
        if (v0 == 0) {
            // 0x004f0f14
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x004f0cac
            charge(ctx, 4);
            lbu(v0, s1, 54);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                // 0x004f0ccc
                charge(ctx, 48);
                lw(a1, s2, 36);
                v1 = 8;
                lw(v0, s1, 44);
                a0 = 0;
                lw(a2, a1, 0);
                a3 = addiu(a1, 16);
                v0 = srl(v0, 4);
                a1 = addu(v1, v0);
                v0 = addiu(a2, -1);
                v0 = sll(v0, 6);
                s0 = addu(a3, v0);
                jal(ctx, 0x4F0CF4u, gen::fn_sub_4D6250_004d6250);
                lw(v0, s1, 88);
                a0 = si(-64);
                lw(a2, gp, -17152);  // 0x7CE9F0
                lq(v1, s0, 0);
                lw(a1, v0, 4);
                sq(v1, a2, 0);
                a0 = a1 & a0;
                lq(v1, s0, 16);
                a0 = dsll32(a0, 0);
                a0 = dsrl32(a0, 0);
                a1 = dsll(a0, 26);
                sq(v1, a2, 16);
                ld(a0, s0, 32);
                ld(v1, s0, 40);
                a0 = a0 + a1;
                pcpyld(v1, v1, a0);
                sq(v1, a2, 32);
                lq(v1, s0, 48);
                sq(v1, a2, 48);
                lw(a1, s0, 52);
                lw(v1, s1, 44);
                lq(a0, a1, 0);
                a3 = addiu(v1, -80);
                v1 = sltiu(a3, 64);
                sq(a0, a2, 64);
                lq(a0, a1, 16);
                sq(a0, a2, 80);
                lq(a0, a1, 32);
                sq(a0, a2, 96);
                lq(a0, a1, 48);
                sq(a0, a2, 112);
                lq(a0, a1, 64);
                sq(a0, a2, 128);
                lw(t0, s2, 8);
                v0 = addiu(a2, 144);
                if (v1 != 0) {
                    // 0x004f0efc
                    charge(ctx, 6);
                    lq(a0, t0, 16);
                    lq(v1, t0, 0);
                    sq(v1, v0, 0);
                    sq(a0, v0, 16);
                    v0 = addiu(v0, 32);
                    backedge(ctx);
                } else {
                    // 0x004f0d8c
                    charge(ctx, 2);
                    if (a3 != 0) {
                        for (;;) {
                            // 0x004f0d94
                            charge(ctx, 12);
                            lq(a2, t0, 0);
                            a3 = addiu(a3, -64);
                            lq(a1, t0, 16);
                            lq(a0, t0, 32);
                            lq(v1, t0, 48);
                            sq(a2, v0, 0);
                            t0 = addiu(t0, 64);
                            sq(a1, v0, 16);
                            sq(a0, v0, 32);
                            sq(v1, v0, 48);
                            v0 = addiu(v0, 64);
                            if (a3 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004f0dc4
                        charge(ctx, 1);
                    }
                }
                // 0x004f0dc8
                charge(ctx, 23);
                v1 = 0x50000000;
                a0 = v1 | 0x2;
                v1 = 0x10000000;
                a1 = dsll32(a0, 0);
                a0 = v1 | 0x2;
                pcpyld(a0, a1, a0);
                sq(a0, v0, 0);
                a1 = 14;
                a0 = dsll32(v1, 0);
                v1 = 0x8001;
                a0 = v1 | a0;
                pcpyld(a0, a1, a0);
                sq(a0, v0, 16);
                v1 = 127;
                a0 = 0;
                pcpyld(v1, v1, a0);
                sq(v1, v0, 32);
                v0 = addiu(v0, 48);
                sw(v0, gp, -17152);  // 0x7CE9F0
                v0 = 0x780000;
                lw(v0, v0, -3548);  // 0x77F224
                if (v0 == s2) {
                    // 0x004f0e24
                    charge(ctx, 4);
                    v0 = 0x780000;
                    lw(v0, v0, -3544);  // 0x77F228
                    lw(a1, s1, 88);
                    if (v0 == 0) {
                        // 0x004f0e40
                        charge(ctx, 2);
                        v0 = 0x780000;
                        lw(a0, v0, -3540);  // 0x77F22C
                    } else {
                        // 0x004f0e34
                        charge(ctx, 3);
                        v0 = 0x780000;
                        lw(a0, v0, -3536);  // 0x77F230
                    }
                    // 0x004f0e48
                    charge(ctx, 8);
                    v0 = 0x780000;
                    v1 = sll(a0, 1);
                    lw(v0, v0, -3564);  // 0x77F214
                    v1 = addu(v1, a0);
                    v1 = sll(v1, 2);
                    v0 = addu(v0, v1);
                    if (a1 == v0) {
                        // 0x004f0e68
                        charge(ctx, 35);
                        a0 = lui(0x8000);
                        a1 = 3;
                        jal(ctx, 0x4F0E6Cu, gen::fn__rwDMAOpenVIFPkt_004d59d0);
                        v0 = 0x10000000;
                        lw(a1, gp, -17148);  // 0x7CE9F4
                        v1 = dsll32(v0, 0);
                        a0 = 14;
                        v0 = 0x8002;
                        v0 = v0 | v1;
                        pcpyld(a3, a0, v0);
                        v0 = 63;
                        v1 = 0;
                        pcpyld(a2, v0, v1);
                        sq(a3, a1, 0);
                        sq(a2, a1, 16);
                        v0 = 0x780000;
                        lw(v0, v0, -3544);  // 0x77F228
                        a0 = 7;
                        lw(a1, gp, -17148);  // 0x7CE9F4
                        v1 = 6;
                        if (v0 == 0) a0 = v1;
                        v0 = addiu(a1, 32);
                        v1 = dsll32(a0, 0);
                        sw(v0, gp, -17148);  // 0x7CE9F4
                        v1 = dsra32(v1, 0);
                        lwu(a0, s1, 12);
                        lwu(a1, s1, 8);
                        lw(v0, gp, -17148);  // 0x7CE9F4
                        a0 = dsll32(a0, 0);
                        a0 = a1 | a0;
                        pcpyld(v1, v1, a0);
                        sq(v1, v0, 0);
                        lw(v0, gp, -17148);  // 0x7CE9F4
                        v0 = addiu(v0, 16);
                        sw(v0, gp, -17148);  // 0x7CE9F4
                    }
                }
                // 0x004f0ef4
                charge(ctx, 2);
                v0 = 1;
            } else {
                // 0x004f0cbc
                charge(ctx, 2);
                v0 = 0;
            }
        }
    }
    // 0x004f0f18 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}
void sub_4F1B30(EEContext& ctx) { sky::Cpu(ctx).raster_upload(); }
// 0x004F1780 sub_4F1780 -- 936 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_4F1780 [texture-cache placement] ($a0 = raster, $a1 = 0 release / non-zero place): with the cache on, a raster
// whose parent's extension (ext +23) says "resident" is released (mode 0: its slot cleared, the next-free index
// pulled back while the slots below it are empty) or kept (mode 1); a raster that is not resident is placed in the
// next free slot (at most the slot count; it must fit between the slot's GS address and the cache top, else 0):
// the slots the eviction hand passes over are cleared, the raster's slot gets {raster, address, size}, the upload
// allocator sub_4EFA00 runs for rasters with pixels that are not "locked" (type bit 7), and TEX0's TBP / CBP fields
// (ext +8 bits 0..13, ext +12 bits 5..18) are patched from the slot address. 1 when resident afterwards.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: callee frames ($sp off / deeper stack)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_4F1780(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::dsll, hg::dsll32, hg::dsra32, hg::enter,
          hg::jal, hg::lbu, hg::ld, hg::lq, hg::lui, hg::lw, hg::mfhi, hg::mult, hg::sb, hg::sd, hg::si, hg::sll,
          hg::sltiu, hg::sltu, hg::sq, hg::sra, hg::srl, hg::subu, hg::sw;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f1780
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x780000;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a2, a0, 0);
    lw(v1, gp, -16968);  // 0x7CEAA8
    lw(v0, v0, -3584);  // 0x77F200
    s0 = addu(a2, v1);
    if (v0 != 0) {
        // 0x004f17a4
        charge(ctx, 2);
        if (a1 != 0) {
            // 0x004f1870
            charge(ctx, 3);
            lbu(v0, s0, 23);
            if (v0 != 0) {
                backedge(ctx);
                goto L_004f17ac;
            }
            // 0x004f187c
            charge(ctx, 5);
            v0 = 0x780000;
            lw(a1, v0, -3568);  // 0x77F210
            at = sltiu(a1, 7);
            if (at != 0) {
                // 0x004f1af0
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x004f1890
                charge(ctx, 14);
                v0 = 0x780000;
                v1 = sll(a1, 1);
                lw(a2, v0, -3564);  // 0x77F214
                v1 = addu(v1, a1);
                a1 = sll(v1, 2);
                v0 = 0x780000;
                a1 = addu(a1, a2);
                lw(v1, v0, -3560);  // 0x77F218
                lw(a1, a1, 4);
                lw(v0, s0, 48);
                v1 = subu(a1, v1);
                v0 = sltu(v1, v0);
                if (v0 != 0) {
                    // 0x004f1af8
                    charge(ctx, 2);
                    v0 = 0;
                } else {
                    // 0x004f18c8
                    charge(ctx, 5);
                    v0 = 0x780000;
                    v1 = si(-1);
                    lw(v0, v0, -3580);  // 0x77F204
                    if (v0 != v1) {
                        // 0x004f18dc
                        charge(ctx, 10);
                        v0 = 0x780000;
                        t0 = 0x780000;
                        lw(v0, v0, -3576);  // 0x77F208
                        a3 = 0x780000;
                        v1 = 0x780000;
                        a2 = 0x780000;
                        t1 = 0x780000;
                        a1 = 0x780000;
                        t2 = 0x780000;
                        v0 = addiu(v0, -1);
                        for (;;) {
                            // 0x004f1904
                            charge(ctx, 4);
                            lw(t3, t2, -3568);
                            v0 = addiu(v0, 1);
                            if (v0 == t3) {
                                // 0x004f1914
                                charge(ctx, 1);
                                v0 = 0;
                            }
                            // 0x004f1918
                            charge(ctx, 8);
                            t3 = sll(v0, 1);
                            t4 = addu(t3, v0);
                            lw(t3, t1, -3564);
                            t5 = sll(t4, 2);
                            t3 = addu(t3, t5);
                            lw(t4, t3, 0);
                            if (t4 != 0) {
                                // 0x004f1938
                                charge(ctx, 9);
                                lw(t3, gp, -16968);  // 0x7CEAA8
                                t3 = addu(t4, t3);
                                sw(zero, t3, 88);
                                lw(t4, t0, -3564);
                                lw(t3, a3, -3548);
                                t4 = addu(t4, t5);
                                lw(t4, t4, 0);
                                if (t4 == t3) {
                                    // 0x004f1b00
                                    charge(ctx, 2);
                                    sw(zero, v1, -3548);
                                    backedge(ctx);
                                } else {
                                    // 0x004f195c
                                    charge(ctx, 1);
                                }
                                // 0x004f1960
                                charge(ctx, 4);
                                lw(t3, a2, -3564);
                                t3 = addu(t3, t5);
                                sw(zero, t3, 0);
                            }
                            // 0x004f1970
                            charge(ctx, 3);
                            lw(t3, a1, -3580);
                            if (v0 == t3) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004f197c
                        charge(ctx, 1);
                    }
                    // 0x004f1980
                    charge(ctx, 20);
                    a1 = si(-1);
                    v1 = 0x780000;
                    v0 = 0x780000;
                    sw(a1, v1, -3580);  // 0x77F204
                    sw(a1, v0, -3576);  // 0x77F208
                    v1 = 0x780000;
                    v0 = 0x780000;
                    lw(v1, v1, -3568);  // 0x77F210
                    lw(a2, v0, -3564);  // 0x77F214
                    a1 = 0x780000;
                    v1 = addiu(v1, -1);
                    v0 = sll(v1, 1);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    a2 = addu(a2, v0);
                    sw(a0, a2, 0);
                    lw(a3, a1, -3568);  // 0x77F210
                    lw(a1, gp, -20228);  // 0x7CDDEC
                    if (a3 != a1) {
                        // 0x004f19e8
                        charge(ctx, 7);
                        a2 = sll(a3, 1);
                        a1 = 0x780000;
                        a2 = addu(a2, a3);
                        lw(a3, a1, -3564);  // 0x77F214
                        a1 = sll(a2, 2);
                        a1 = addu(a1, a3);
                        lw(t3, a1, 4);
                    } else {
                        // 0x004f19d0
                        charge(ctx, 6);
                        a2 = 0x780000;
                        a1 = 0x780000;
                        lw(a2, a2, -3560);  // 0x77F218
                        lw(a1, a1, -3556);  // 0x77F21C
                        t3 = addu(a2, a1);
                    }
                    // 0x004f1a04
                    charge(ctx, 23);
                    a1 = 0x780000;
                    lw(t2, s0, 48);
                    lw(t1, a1, -3564);  // 0x77F214
                    a3 = 0x780000;
                    a2 = 0x780000;
                    t0 = 1;
                    t2 = subu(t3, t2);
                    t1 = addu(v0, t1);
                    a1 = 0x780000;
                    sw(t2, t1, 4);
                    lw(a3, a3, -3564);  // 0x77F214
                    lw(t1, s0, 48);
                    a3 = addu(v0, a3);
                    sw(t1, a3, 8);
                    lw(a2, a2, -3564);  // 0x77F214
                    a2 = addu(a2, v0);
                    sw(a2, s0, 88);
                    sw(v1, a1, -3568);  // 0x77F210
                    sb(t0, s0, 23);
                    lbu(v1, a0, 32);
                    v1 = v1 & 0x80;
                    if (v1 == 0) {
                        // 0x004f1a60
                        charge(ctx, 3);
                        lw(v1, a0, 4);
                        if (v1 != 0) {
                            // 0x004f1a6c
                            charge(ctx, 6);
                            v1 = 0x780000;
                            lw(v1, v1, -3564);  // 0x77F214
                            v0 = addu(v0, v1);
                            lw(a1, v0, 4);
                            a2 = 0;
                            jal(ctx, 0x4F1A7Cu, gen::fn_sub_4EFA00_004efa00);
                        }
                    }
                    // 0x004f1a84
                    charge(ctx, 27);
                    lw(a1, s0, 88);
                    v0 = lui(0xFFF8);
                    lw(a0, s0, 8);
                    v1 = si(-16384);
                    v0 = v0 | 0x1F;
                    lw(a1, a1, 4);
                    v1 = a0 & v1;
                    sw(v1, s0, 8);
                    a1 = srl(a1, 6);
                    lw(v1, s0, 8);
                    a0 = a1 & 0x3FFF;
                    v1 = v1 | a0;
                    sw(v1, s0, 8);
                    lw(a0, s0, 16);
                    lw(v1, s0, 12);
                    a0 = addu(a1, a0);
                    v1 = v1 & v0;
                    v0 = a0 & 0x3FFF;
                    sw(v1, s0, 12);
                    v0 = v0 & 0x3FFF;
                    v1 = dsll(v0, 5);
                    lw(v0, s0, 12);
                    v1 = dsll32(v1, 0);
                    v1 = dsra32(v1, 0);
                    v0 = v0 | v1;
                    sw(v0, s0, 12);
                    backedge(ctx);
                L_004f1868:
                    charge(ctx, 2);
                    v0 = 1;
                }
            }
            // 0x004f1b18 (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(ra, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x20);
            return;
        }
    L_004f17ac:
        charge(ctx, 2);
        if (a1 == 0) {
            // 0x004f17b4
            charge(ctx, 3);
            lbu(v0, s0, 23);
            if (v0 != 0) {
                // 0x004f17c0
                charge(ctx, 18);
                sb(zero, s0, 23);
                v0 = 0x780000;
                lw(v1, v0, -3564);  // 0x77F214
                lw(a2, s0, 88);
                v0 = 0x2AAA0000;
                v0 = v0 | 0xAAAB;
                v1 = subu(a2, v1);
                mult(zero, v0, v1);
                a1 = srl(v1, 31);
                mfhi(v1);
                sw(zero, a2, 0);
                sw(zero, s0, 88);
                v0 = 0x780000;
                lw(v0, v0, -3548);  // 0x77F224
                v1 = sra(v1, 1);
                v1 = addu(v1, a1);
                if (v0 == a0) {
                    // 0x004f1b08
                    charge(ctx, 3);
                    v0 = 0x780000;
                    sw(zero, v0, -3548);  // 0x77F224
                    backedge(ctx);
                }
                // 0x004f1808
                charge(ctx, 4);
                v0 = 0x780000;
                lw(v0, v0, -3568);  // 0x77F210
                if (v1 == v0) {
                    // 0x004f1818
                    charge(ctx, 5);
                    v1 = 0x780000;
                    lw(a3, gp, -20228);  // 0x7CDDEC
                    lw(a1, v1, -3564);  // 0x77F214
                    v0 = 0x780000;
                    v1 = 0x780000;
                    for (;;) {
                        // 0x004f182c
                        charge(ctx, 4);
                        lw(a2, v1, -3568);
                        at = sltu(a2, a3);
                        if (at != 0) {
                            // 0x004f183c
                            charge(ctx, 7);
                            a0 = sll(a2, 1);
                            a0 = addu(a0, a2);
                            a0 = sll(a0, 2);
                            a0 = addu(a1, a0);
                            lw(a0, a0, 0);
                            if (a0 == 0) {
                                // 0x004f1858
                                charge(ctx, 3);
                                a0 = addiu(a2, 1);
                                sw(a0, v0, -3568);
                                backedge(ctx);
                                continue;
                            }
                        }
                        break;
                    }
                }
            }
        }
        goto L_004f1868;
    }
    // 0x004f1b14
    charge(ctx, 1);
    v0 = 0;
    // 0x004f1b18 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0046FDD0 sub_46FDD0 -- 1060 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's.
void sub_46FDD0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::di, hg::dsll, hg::dsll32,
          hg::dsra32, hg::dsrl32, hg::ei, hg::enter, hg::jal, hg::lbu, hg::ld, hg::link, hg::lq, hg::lui, hg::lw,
          hg::lwc1, hg::lwu, hg::mfc0, hg::mtc1, hg::pcpyld, hg::sb, hg::sd, hg::si, hg::sll, hg::sltu, hg::sq,
          hg::sw, hg::sync;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x0046fdd0
    enter(ctx, 38);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 13;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 0;
    jal(ctx, 0x46FDE4u, gen::fn__rwDMAOpenVIFPkt_004d59d0);
    v0 = 0x10000000;
    v1 = 0;
    v0 = v0 | 0xA;
    pcpyld(a3, v1, v0);
    lw(a1, gp, -17148);  // 0x7CE9F4
    v0 = 0x6C010000;
    a0 = 254;
    v1 = v0 | 0x3FA;
    a2 = 0;
    v0 = 0x1000000;
    v1 = dsll32(v1, 0);
    v0 = v0 | 0x404;  // &0x1000404
    v0 = v0 | v1;
    sq(a3, a1, 0);
    lw(v1, gp, -17148);  // 0x7CE9F4
    v1 = addiu(v1, 16);
    sw(v1, gp, -17148);  // 0x7CE9F4
    sb(a0, s0, 71);
    pcpyld(v1, v0, a2);
    lw(v0, gp, -17148);  // 0x7CE9F4
    sq(v1, v0, 0);
    lw(v1, gp, -17148);  // 0x7CE9F4
    lw(v0, gp, -16952);  // 0x7CEAB8
    v1 = addiu(v1, 16);
    sw(v1, gp, -17148);  // 0x7CE9F4
    lbu(a0, s0, 71);
    a0 = a0 ^ 0xFF;
    a0 = sltu(0, a0);
    v0 = a0 | v0;
    sw(a0, gp, -16956);  // 0x7CEAB4
    if (v0 == 0) {
        // 0x0046fe78
        charge(ctx, 4);
        ld(a0, gp, -20272);  // 0x7CDDC0
        v0 = si(-65);
        v0 = a0 & v0;
        sd(v0, gp, -20272);  // 0x7CDDC0
    } else {
        // 0x0046fe68
        charge(ctx, 4);
        ld(v0, gp, -20272);  // 0x7CDDC0
        v0 = v0 | 0x40;
        sd(v0, gp, -20272);  // 0x7CDDC0
    }
    // 0x0046fe88
    charge(ctx, 43);
    v0 = 0x960000;
    a0 = lui(0xFC00);
    ld(a3, v0, 22688);  // 0x9658A0
    ld(a1, gp, -20272);  // 0x7CDDC0
    v0 = a0 | 0x7FFF;
    lbu(a0, s0, 41);
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
        // 0x0046ff48
        charge(ctx, 4);
        v0 = 0x3B800000;
        v0 = v0 | 0x8081;
        mtc1(v0, f12);
        a0 = addiu(s0, 68);
    } else {
        // 0x0046ff34
        charge(ctx, 5);
        v0 = 0x3B010000;
        v0 = v0 | 0x1B50;
        mtc1(v0, f12);
        a0 = addiu(s0, 68);
    }
    // 0x0046ff58
    charge(ctx, 33);
    jal(ctx, 0x46FF58u, gen::fn_sub_49CAB0_0049cab0);
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
    lwc1(f12, s0, 28);
    link(ctx, 0x46FF98u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 60);
    call(ctx, gen::fn_sub_49CBD0_0049cbd0);
    lbu(a0, s0, 40);
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
        // 0x0046ffdc
        charge(ctx, 3);
        v1 = v0 & 0x4;
        if (v1 != 0) {
            goto L_0046ffe8;
        }
    L_00470000:
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
        goto L_0047002c;
    }
L_0046ffe8:
    charge(ctx, 3);
    lw(v1, gp, -20232);  // 0x7CDDE8
    if (v1 != 0) {
        // 0x0046fff4
        charge(ctx, 3);
        v1 = v0 & 0x4;
        if (v1 == 0) {
            goto L_0047019c;
        }
        goto L_00470000;
    }
L_0047019c:
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
L_0047002c:
    charge(ctx, 5);
    lw(a2, gp, -16964);  // 0x7CEAAC
    a1 = 3;
    sw(zero, gp, -16884);  // 0x7CEAFC
    a0 = 0;
    if (a2 == a1) {
        // 0x004701c8
        charge(ctx, 3);
        a0 = 32;
        sw(a0, gp, -16884);  // 0x7CEAFC
        backedge(ctx);
    }
    // 0x00470040
    charge(ctx, 29);
    lwu(a1, gp, -16880);  // 0x7CEB00
    a0 = dsll32(a0, 0);
    v0 = dsll32(v0, 0);
    a0 = dsrl32(a0, 0);
    v0 = dsrl32(v0, 0);
    a1 = dsll32(a1, 0);
    a0 = a1 | a0;
    pcpyld(a0, a0, v0);
    v1 = dsll32(v1, 0);
    v0 = 0x960000;
    v1 = dsra32(v1, 0);
    sq(a0, v1, 0);
    lw(v1, gp, -17148);  // 0x7CE9F4
    lw(v0, v0, -4220);  // 0x95EF84
    v1 = addiu(v1, 16);
    sw(v1, gp, -17148);  // 0x7CE9F4
    lw(v0, v0, 20);
    v0 = v0 ^ 0x1;
    v0 = sltu(0, v0);
    sb(v0, s0, 43);
    lw(v1, s0, 4);
    lbu(a0, s0, 43);
    lw(v0, gp, -16888);  // 0x7CEAF8
    lw(v1, v1, 24);
    a0 = sll(a0, 2);
    v1 = addu(v1, a0);
    lw(a0, v1, 0);
    if (v0 != a0) {
        // 0x004700b4
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
    // 0x004700e8
    charge(ctx, 25);
    lw(v1, s0, 48);
    a0 = 1;
    a2 = 0x2000000;
    a1 = 0x3000000;
    v0 = 0x50000000;
    lw(v1, v1, 0);
    sw(a0, v1, 28);
    lw(a0, s0, 48);
    lw(v1, s0, 4);
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
        // 0x0047014c
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
    // 0x00470168
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
        // 0x004701d4
        charge(ctx, 4);
        jal(ctx, 0x4701D4u, gen::fn__rwDMAAddPURef_004d51c0);
        backedge(ctx);
    }
    // 0x00470194
    charge(ctx, 2);
    v0 = 1;
    // 0x004701e4
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004709E0 RpPDS_G3_2DFont_PS2AllBridgeCallBack -- 1060 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's.
void RpPDS_G3_2DFont_PS2AllBridgeCallBack(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::di, hg::dsll, hg::dsll32,
          hg::dsra32, hg::dsrl32, hg::ei, hg::enter, hg::jal, hg::lbu, hg::ld, hg::link, hg::lq, hg::lui, hg::lw,
          hg::lwc1, hg::lwu, hg::mfc0, hg::mtc1, hg::pcpyld, hg::sb, hg::sd, hg::si, hg::sll, hg::sltu, hg::sq,
          hg::sw, hg::sync;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x004709e0
    enter(ctx, 38);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 13;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 0;
    jal(ctx, 0x4709F4u, gen::fn__rwDMAOpenVIFPkt_004d59d0);
    v0 = 0x10000000;
    v1 = 0;
    v0 = v0 | 0xA;
    pcpyld(a3, v1, v0);
    lw(a1, gp, -17148);  // 0x7CE9F4
    v0 = 0x6C010000;
    a0 = 254;
    v1 = v0 | 0x3FA;
    a2 = 0;
    v0 = 0x1000000;
    v1 = dsll32(v1, 0);
    v0 = v0 | 0x404;  // &0x1000404
    v0 = v0 | v1;
    sq(a3, a1, 0);
    lw(v1, gp, -17148);  // 0x7CE9F4
    v1 = addiu(v1, 16);
    sw(v1, gp, -17148);  // 0x7CE9F4
    sb(a0, s0, 71);
    pcpyld(v1, v0, a2);
    lw(v0, gp, -17148);  // 0x7CE9F4
    sq(v1, v0, 0);
    lw(v1, gp, -17148);  // 0x7CE9F4
    lw(v0, gp, -16952);  // 0x7CEAB8
    v1 = addiu(v1, 16);
    sw(v1, gp, -17148);  // 0x7CE9F4
    lbu(a0, s0, 71);
    a0 = a0 ^ 0xFF;
    a0 = sltu(0, a0);
    v0 = a0 | v0;
    sw(a0, gp, -16956);  // 0x7CEAB4
    if (v0 == 0) {
        // 0x00470a88
        charge(ctx, 4);
        ld(a0, gp, -20272);  // 0x7CDDC0
        v0 = si(-65);
        v0 = a0 & v0;
        sd(v0, gp, -20272);  // 0x7CDDC0
    } else {
        // 0x00470a78
        charge(ctx, 4);
        ld(v0, gp, -20272);  // 0x7CDDC0
        v0 = v0 | 0x40;
        sd(v0, gp, -20272);  // 0x7CDDC0
    }
    // 0x00470a98
    charge(ctx, 43);
    v0 = 0x960000;
    a0 = lui(0xFC00);
    ld(a3, v0, 22688);  // 0x9658A0
    ld(a1, gp, -20272);  // 0x7CDDC0
    v0 = a0 | 0x7FFF;
    lbu(a0, s0, 41);
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
        // 0x00470b58
        charge(ctx, 4);
        v0 = 0x3B800000;
        v0 = v0 | 0x8081;
        mtc1(v0, f12);
        a0 = addiu(s0, 68);
    } else {
        // 0x00470b44
        charge(ctx, 5);
        v0 = 0x3B010000;
        v0 = v0 | 0x1B50;
        mtc1(v0, f12);
        a0 = addiu(s0, 68);
    }
    // 0x00470b68
    charge(ctx, 33);
    jal(ctx, 0x470B68u, gen::fn_sub_49CAB0_0049cab0);
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
    lwc1(f12, s0, 28);
    link(ctx, 0x470BA8u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 60);
    call(ctx, gen::fn_sub_49CBD0_0049cbd0);
    lbu(a0, s0, 40);
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
        // 0x00470bec
        charge(ctx, 3);
        v1 = v0 & 0x4;
        if (v1 != 0) {
            goto L_00470bf8;
        }
    L_00470c10:
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
        goto L_00470c3c;
    }
L_00470bf8:
    charge(ctx, 3);
    lw(v1, gp, -20232);  // 0x7CDDE8
    if (v1 != 0) {
        // 0x00470c04
        charge(ctx, 3);
        v1 = v0 & 0x4;
        if (v1 == 0) {
            goto L_00470dac;
        }
        goto L_00470c10;
    }
L_00470dac:
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
L_00470c3c:
    charge(ctx, 5);
    lw(a2, gp, -16964);  // 0x7CEAAC
    a1 = 3;
    sw(zero, gp, -16884);  // 0x7CEAFC
    a0 = 0;
    if (a2 == a1) {
        // 0x00470dd8
        charge(ctx, 3);
        a0 = 32;
        sw(a0, gp, -16884);  // 0x7CEAFC
        backedge(ctx);
    }
    // 0x00470c50
    charge(ctx, 29);
    lwu(a1, gp, -16880);  // 0x7CEB00
    a0 = dsll32(a0, 0);
    v0 = dsll32(v0, 0);
    a0 = dsrl32(a0, 0);
    v0 = dsrl32(v0, 0);
    a1 = dsll32(a1, 0);
    a0 = a1 | a0;
    pcpyld(a0, a0, v0);
    v1 = dsll32(v1, 0);
    v0 = 0x960000;
    v1 = dsra32(v1, 0);
    sq(a0, v1, 0);
    lw(v1, gp, -17148);  // 0x7CE9F4
    lw(v0, v0, -4220);  // 0x95EF84
    v1 = addiu(v1, 16);
    sw(v1, gp, -17148);  // 0x7CE9F4
    lw(v0, v0, 20);
    v0 = v0 ^ 0x1;
    v0 = sltu(0, v0);
    sb(v0, s0, 43);
    lw(v1, s0, 4);
    lbu(a0, s0, 43);
    lw(v0, gp, -16888);  // 0x7CEAF8
    lw(v1, v1, 24);
    a0 = sll(a0, 2);
    v1 = addu(v1, a0);
    lw(a0, v1, 0);
    if (v0 != a0) {
        // 0x00470cc4
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
    // 0x00470cf8
    charge(ctx, 25);
    lw(v1, s0, 48);
    a0 = 1;
    a2 = 0x2000000;
    a1 = 0x3000000;
    v0 = 0x50000000;
    lw(v1, v1, 0);
    sw(a0, v1, 28);
    lw(a0, s0, 48);
    lw(v1, s0, 4);
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
        // 0x00470d5c
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
    // 0x00470d78
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
        // 0x00470de4
        charge(ctx, 4);
        jal(ctx, 0x470DE4u, gen::fn__rwDMAAddPURef_004d51c0);
        backedge(ctx);
    }
    // 0x00470da4
    charge(ctx, 2);
    v0 = 1;
    // 0x00470df4
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00471470 sub_471470 -- 1060 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's.
void sub_471470(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::di, hg::dsll, hg::dsll32,
          hg::dsra32, hg::dsrl32, hg::ei, hg::enter, hg::jal, hg::lbu, hg::ld, hg::link, hg::lq, hg::lui, hg::lw,
          hg::lwc1, hg::lwu, hg::mfc0, hg::mtc1, hg::pcpyld, hg::sb, hg::sd, hg::si, hg::sll, hg::sltu, hg::sq,
          hg::sw, hg::sync;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00471470
    enter(ctx, 38);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 13;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 0;
    jal(ctx, 0x471484u, gen::fn__rwDMAOpenVIFPkt_004d59d0);
    v0 = 0x10000000;
    v1 = 0;
    v0 = v0 | 0xA;
    pcpyld(a3, v1, v0);
    lw(a1, gp, -17148);  // 0x7CE9F4
    v0 = 0x6C010000;
    a0 = 254;
    v1 = v0 | 0x3FA;
    a2 = 0;
    v0 = 0x1000000;
    v1 = dsll32(v1, 0);
    v0 = v0 | 0x404;  // &0x1000404
    v0 = v0 | v1;
    sq(a3, a1, 0);
    lw(v1, gp, -17148);  // 0x7CE9F4
    v1 = addiu(v1, 16);
    sw(v1, gp, -17148);  // 0x7CE9F4
    sb(a0, s0, 71);
    pcpyld(v1, v0, a2);
    lw(v0, gp, -17148);  // 0x7CE9F4
    sq(v1, v0, 0);
    lw(v1, gp, -17148);  // 0x7CE9F4
    lw(v0, gp, -16952);  // 0x7CEAB8
    v1 = addiu(v1, 16);
    sw(v1, gp, -17148);  // 0x7CE9F4
    lbu(a0, s0, 71);
    a0 = a0 ^ 0xFF;
    a0 = sltu(0, a0);
    v0 = a0 | v0;
    sw(a0, gp, -16956);  // 0x7CEAB4
    if (v0 == 0) {
        // 0x00471518
        charge(ctx, 4);
        ld(a0, gp, -20272);  // 0x7CDDC0
        v0 = si(-65);
        v0 = a0 & v0;
        sd(v0, gp, -20272);  // 0x7CDDC0
    } else {
        // 0x00471508
        charge(ctx, 4);
        ld(v0, gp, -20272);  // 0x7CDDC0
        v0 = v0 | 0x40;
        sd(v0, gp, -20272);  // 0x7CDDC0
    }
    // 0x00471528
    charge(ctx, 43);
    v0 = 0x960000;
    a0 = lui(0xFC00);
    ld(a3, v0, 22688);  // 0x9658A0
    ld(a1, gp, -20272);  // 0x7CDDC0
    v0 = a0 | 0x7FFF;
    lbu(a0, s0, 41);
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
        // 0x004715e8
        charge(ctx, 4);
        v0 = 0x3B800000;
        v0 = v0 | 0x8081;
        mtc1(v0, f12);
        a0 = addiu(s0, 68);
    } else {
        // 0x004715d4
        charge(ctx, 5);
        v0 = 0x3B010000;
        v0 = v0 | 0x1B50;
        mtc1(v0, f12);
        a0 = addiu(s0, 68);
    }
    // 0x004715f8
    charge(ctx, 33);
    jal(ctx, 0x4715F8u, gen::fn_sub_49CAB0_0049cab0);
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
    lwc1(f12, s0, 28);
    link(ctx, 0x471638u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 60);
    call(ctx, gen::fn_sub_49CBD0_0049cbd0);
    lbu(a0, s0, 40);
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
        // 0x0047167c
        charge(ctx, 3);
        v1 = v0 & 0x4;
        if (v1 != 0) {
            goto L_00471688;
        }
    L_004716a0:
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
        goto L_004716cc;
    }
L_00471688:
    charge(ctx, 3);
    lw(v1, gp, -20232);  // 0x7CDDE8
    if (v1 != 0) {
        // 0x00471694
        charge(ctx, 3);
        v1 = v0 & 0x4;
        if (v1 == 0) {
            goto L_0047183c;
        }
        goto L_004716a0;
    }
L_0047183c:
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
L_004716cc:
    charge(ctx, 5);
    lw(a2, gp, -16964);  // 0x7CEAAC
    a1 = 3;
    sw(zero, gp, -16884);  // 0x7CEAFC
    a0 = 0;
    if (a2 == a1) {
        // 0x00471868
        charge(ctx, 3);
        a0 = 32;
        sw(a0, gp, -16884);  // 0x7CEAFC
        backedge(ctx);
    }
    // 0x004716e0
    charge(ctx, 29);
    lwu(a1, gp, -16880);  // 0x7CEB00
    a0 = dsll32(a0, 0);
    v0 = dsll32(v0, 0);
    a0 = dsrl32(a0, 0);
    v0 = dsrl32(v0, 0);
    a1 = dsll32(a1, 0);
    a0 = a1 | a0;
    pcpyld(a0, a0, v0);
    v1 = dsll32(v1, 0);
    v0 = 0x960000;
    v1 = dsra32(v1, 0);
    sq(a0, v1, 0);
    lw(v1, gp, -17148);  // 0x7CE9F4
    lw(v0, v0, -4220);  // 0x95EF84
    v1 = addiu(v1, 16);
    sw(v1, gp, -17148);  // 0x7CE9F4
    lw(v0, v0, 20);
    v0 = v0 ^ 0x1;
    v0 = sltu(0, v0);
    sb(v0, s0, 43);
    lw(v1, s0, 4);
    lbu(a0, s0, 43);
    lw(v0, gp, -16888);  // 0x7CEAF8
    lw(v1, v1, 24);
    a0 = sll(a0, 2);
    v1 = addu(v1, a0);
    lw(a0, v1, 0);
    if (v0 != a0) {
        // 0x00471754
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
    // 0x00471788
    charge(ctx, 25);
    lw(v1, s0, 48);
    a0 = 1;
    a2 = 0x2000000;
    a1 = 0x3000000;
    v0 = 0x50000000;
    lw(v1, v1, 0);
    sw(a0, v1, 28);
    lw(a0, s0, 48);
    lw(v1, s0, 4);
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
        // 0x004717ec
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
    // 0x00471808
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
        // 0x00471874
        charge(ctx, 4);
        jal(ctx, 0x471874u, gen::fn__rwDMAAddPURef_004d51c0);
        backedge(ctx);
    }
    // 0x00471834
    charge(ctx, 2);
    v0 = 1;
    // 0x00471884
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004A2790 sub_4A2790 -- 1040 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's.
void sub_4A2790(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::di, hg::dsll, hg::dsll32,
          hg::dsra32, hg::dsrl32, hg::ei, hg::enter, hg::jal, hg::lbu, hg::ld, hg::link, hg::lq, hg::lui, hg::lw,
          hg::lwc1, hg::lwu, hg::mfc0, hg::mtc1, hg::pcpyld, hg::sb, hg::sd, hg::si, hg::sll, hg::sltu, hg::sq,
          hg::sra, hg::sw, hg::sync;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x004a2790
    enter(ctx, 32);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 13;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 0;
    jal(ctx, 0x4A27A4u, gen::fn__rwDMAOpenVIFPkt_004d59d0);
    v0 = 0x10000000;
    v1 = 0;
    v0 = v0 | 0xA;
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
    lbu(a0, s0, 71);
    a0 = a0 ^ 0xFF;
    a0 = sltu(0, a0);
    v0 = a0 | v0;
    sw(a0, gp, -16956);  // 0x7CEAB4
    if (v0 == 0) {
        // 0x004a2820
        charge(ctx, 4);
        ld(a0, gp, -20272);  // 0x7CDDC0
        v0 = si(-65);
        v0 = a0 & v0;
        sd(v0, gp, -20272);  // 0x7CDDC0
    } else {
        // 0x004a2810
        charge(ctx, 4);
        ld(v0, gp, -20272);  // 0x7CDDC0
        v0 = v0 | 0x40;
        sd(v0, gp, -20272);  // 0x7CDDC0
    }
    // 0x004a2830
    charge(ctx, 43);
    v0 = 0x960000;
    a0 = lui(0xFC00);
    ld(a3, v0, 22688);  // 0x9658A0
    ld(a1, gp, -20272);  // 0x7CDDC0
    v0 = a0 | 0x7FFF;
    lbu(a0, s0, 41);
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
        // 0x004a28f0
        charge(ctx, 4);
        v0 = 0x3B800000;
        v0 = v0 | 0x8081;
        mtc1(v0, f12);
        a0 = addiu(s0, 68);
    } else {
        // 0x004a28dc
        charge(ctx, 5);
        v0 = 0x3B010000;
        v0 = v0 | 0x1B50;
        mtc1(v0, f12);
        a0 = addiu(s0, 68);
    }
    // 0x004a2900
    charge(ctx, 33);
    jal(ctx, 0x4A2900u, gen::fn_sub_49CAB0_0049cab0);
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
    lwc1(f12, s0, 28);
    link(ctx, 0x4A2940u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 60);
    call(ctx, gen::fn_sub_49CBD0_0049cbd0);
    lbu(a0, s0, 40);
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
        // 0x004a2984
        charge(ctx, 3);
        v1 = v0 & 0x4;
        if (v1 != 0) {
            goto L_004a2990;
        }
    L_004a29a8:
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
        goto L_004a29d4;
    }
L_004a2990:
    charge(ctx, 3);
    lw(v1, gp, -20232);  // 0x7CDDE8
    if (v1 != 0) {
        // 0x004a299c
        charge(ctx, 3);
        v1 = v0 & 0x4;
        if (v1 == 0) {
            goto L_004a2b48;
        }
        goto L_004a29a8;
    }
L_004a2b48:
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
L_004a29d4:
    charge(ctx, 5);
    lw(a2, gp, -16964);  // 0x7CEAAC
    a1 = 3;
    sw(zero, gp, -16884);  // 0x7CEAFC
    a0 = 0;
    if (a2 == a1) {
        // 0x004a2b74
        charge(ctx, 3);
        a0 = 32;
        sw(a0, gp, -16884);  // 0x7CEAFC
        backedge(ctx);
    }
    // 0x004a29e8
    charge(ctx, 30);
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
    if (v0 != a0) {
        // 0x004a2a60
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
    // 0x004a2a94
    charge(ctx, 25);
    lw(v1, s0, 48);
    a0 = 1;
    a2 = 0x2000000;
    a1 = 0x3000000;
    v0 = 0x50000000;
    lw(v1, v1, 0);
    sw(a0, v1, 28);
    lw(a0, s0, 48);
    lw(v1, s0, 4);
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
        // 0x004a2af8
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
    // 0x004a2b14
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
        // 0x004a2b80
        charge(ctx, 4);
        jal(ctx, 0x4A2B80u, gen::fn__rwDMAAddPURef_004d51c0);
        backedge(ctx);
    }
    // 0x004a2b40
    charge(ctx, 2);
    v0 = 1;
    // 0x004a2b90
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

}  // namespace p3fes::game

// --- the recompiled program's entry points (the bodies read their arguments from the registers) ---------------
namespace p3fes::recomp_gen {
namespace sky = ::p3fes::game::sky;

void fn__rwSkySetRenderState_004d6b90(p3fes::EEContext& ctx) { sky::Cpu(ctx).set_render_state(); }
void fn_sub_4F1B30_004f1b30(p3fes::EEContext& ctx) { sky::Cpu(ctx).raster_upload(); }

}  // namespace p3fes::recomp_gen
