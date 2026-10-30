// Slice render_rw6: RenderWare, sixth pass -- the collision intersection tests, Rt2d, the RtFS manager, the sList
// helpers, the PS2AllMat node set-up and the engine's device requests (the group overview and the record layouts are in
// game/include/p3fes/game/render_rw6.h). Every body started as p3fes_handgen's output and keeps the recompiled body's
// registers, frame, spills, $ra links, cycle charges and check points statement for statement
// (game/include/p3fes/game/hg_cpu.h); what was added is the role of each function, the role of its main blocks, the
// names of the record offsets (rw4:: / rw5:: / rw6::) and the labels of the RW globals. sub_* keep their
// symbols/functions.json names; proposed names are in brackets (symbols/deltas/render_rw6.sym).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/render_rw6.h"

namespace p3fes::recomp_gen {
void fn_RpPDSGetPipe_0046a890(p3fes::EEContext&);
void fn_RwEngineSetVideoMode_004ca600(p3fes::EEContext&);
void fn_RxPipelineNodePS2AllMatSetVU1CodeArray_004a3db0(p3fes::EEContext&);
void fn__rwDeviceSystemRequest_004ca3e0(p3fes::EEContext&);
void fn_j__rwSListGetEntry_004b2c70(p3fes::EEContext&);
void fn_name__C9type_info_1_004c21d0(p3fes::EEContext&);
void fn_rt2dPS2PipeOpen_004b1100(p3fes::EEContext&);
void fn_sceLibgcc32GetErxEntries_0_004a3f10(p3fes::EEContext&);
void fn_sceLibgcc32GetErxEntries_1_004c0060(p3fes::EEContext&);
void fn_sub_45F930_0045f930(p3fes::EEContext&);
void fn_sub_4606B0_004606b0(p3fes::EEContext&);
void fn_sub_460EC0_00460ec0(p3fes::EEContext&);
void fn_sub_461900_00461900(p3fes::EEContext&);
void fn_sub_461D00_00461d00(p3fes::EEContext&);
void fn_sub_461EA0_00461ea0(p3fes::EEContext&);
void fn_sub_462BB0_00462bb0(p3fes::EEContext&);
void fn_sub_463490_00463490(p3fes::EEContext&);
void fn_sub_463B20_00463b20(p3fes::EEContext&);
void fn_sub_463F20_00463f20(p3fes::EEContext&);
void fn_sub_492C30_00492c30(p3fes::EEContext&);
void fn_sub_492CC0_00492cc0(p3fes::EEContext&);
void fn_sub_493C50_00493c50(p3fes::EEContext&);
void fn_sub_499250_00499250(p3fes::EEContext&);
void fn_sub_4992B0_004992b0(p3fes::EEContext&);
void fn_sub_49C560_0049c560(p3fes::EEContext&);
void fn_sub_49C5C0_0049c5c0(p3fes::EEContext&);
void fn_sub_49C620_0049c620(p3fes::EEContext&);
void fn_sub_49E5A0_0049e5a0(p3fes::EEContext&);
void fn_sub_4A38F0_004a38f0(p3fes::EEContext&);
void fn_sub_4A3A80_004a3a80(p3fes::EEContext&);
void fn_sub_4A3C10_004a3c10(p3fes::EEContext&);
void fn_sub_4A3D70_004a3d70(p3fes::EEContext&);
void fn_sub_4A3E30_004a3e30(p3fes::EEContext&);
void fn_sub_4A4D50_004a4d50(p3fes::EEContext&);
void fn_sub_4A4DA0_004a4da0(p3fes::EEContext&);
void fn_sub_4A4E40_004a4e40(p3fes::EEContext&);
void fn_sub_4A4EF0_004a4ef0(p3fes::EEContext&);
void fn_sub_4A4F90_004a4f90(p3fes::EEContext&);
void fn_sub_4A5080_004a5080(p3fes::EEContext&);
void fn_sub_4A5100_004a5100(p3fes::EEContext&);
void fn_sub_4A5200_004a5200(p3fes::EEContext&);
void fn_sub_4A5210_004a5210(p3fes::EEContext&);
void fn_sub_4A5290_004a5290(p3fes::EEContext&);
void fn_sub_4A52A0_004a52a0(p3fes::EEContext&);
void fn_sub_4A5320_004a5320(p3fes::EEContext&);
void fn_sub_4A5330_004a5330(p3fes::EEContext&);
void fn_sub_4A53B0_004a53b0(p3fes::EEContext&);
void fn_sub_4A5400_004a5400(p3fes::EEContext&);
void fn_sub_4A5540_004a5540(p3fes::EEContext&);
void fn_sub_4AA540_004aa540(p3fes::EEContext&);
void fn_sub_4AA620_004aa620(p3fes::EEContext&);
void fn_sub_4AA6C0_004aa6c0(p3fes::EEContext&);
void fn_sub_4AADA0_004aada0(p3fes::EEContext&);
void fn_sub_4AAE00_004aae00(p3fes::EEContext&);
void fn_sub_4AB0E0_004ab0e0(p3fes::EEContext&);
void fn_sub_4AB170_004ab170(p3fes::EEContext&);
void fn_sub_4AB1B0_004ab1b0(p3fes::EEContext&);
void fn_sub_4AB2C0_004ab2c0(p3fes::EEContext&);
void fn_sub_4AB410_004ab410(p3fes::EEContext&);
void fn_sub_4ABD50_004abd50(p3fes::EEContext&);
void fn_sub_4AC020_004ac020(p3fes::EEContext&);
void fn_sub_4AC120_004ac120(p3fes::EEContext&);
void fn_sub_4AC390_004ac390(p3fes::EEContext&);
void fn_sub_4AC7F0_004ac7f0(p3fes::EEContext&);
void fn_sub_4AC860_004ac860(p3fes::EEContext&);
void fn_sub_4ACCC0_004accc0(p3fes::EEContext&);
void fn_sub_4ACE60_004ace60(p3fes::EEContext&);
void fn_sub_4AD6A0_004ad6a0(p3fes::EEContext&);
void fn_sub_4ADB50_004adb50(p3fes::EEContext&);
void fn_sub_4ADB80_004adb80(p3fes::EEContext&);
void fn_sub_4ADC70_004adc70(p3fes::EEContext&);
void fn_sub_4ADCA0_004adca0(p3fes::EEContext&);
void fn_sub_4ADDB0_004addb0(p3fes::EEContext&);
void fn_sub_4ADFD0_004adfd0(p3fes::EEContext&);
void fn_sub_4AE010_004ae010(p3fes::EEContext&);
void fn_sub_4AE020_004ae020(p3fes::EEContext&);
void fn_sub_4AE1D0_004ae1d0(p3fes::EEContext&);
void fn_sub_4AE1E0_004ae1e0(p3fes::EEContext&);
void fn_sub_4AE1F0_004ae1f0(p3fes::EEContext&);
void fn_sub_4AE8F0_004ae8f0(p3fes::EEContext&);
void fn_sub_4AE900_004ae900(p3fes::EEContext&);
void fn_sub_4AEB60_004aeb60(p3fes::EEContext&);
void fn_sub_4AEF50_004aef50(p3fes::EEContext&);
void fn_sub_4B0360_004b0360(p3fes::EEContext&);
void fn_sub_4B0430_004b0430(p3fes::EEContext&);
void fn_sub_4B0560_004b0560(p3fes::EEContext&);
void fn_sub_4B08C0_004b08c0(p3fes::EEContext&);
void fn_sub_4B0DF0_004b0df0(p3fes::EEContext&);
void fn_sub_4B1050_004b1050(p3fes::EEContext&);
void fn_sub_4B1090_004b1090(p3fes::EEContext&);
void fn_sub_4B11A0_004b11a0(p3fes::EEContext&);
void fn_sub_4B11F0_004b11f0(p3fes::EEContext&);
void fn_sub_4B1240_004b1240(p3fes::EEContext&);
void fn_sub_4B1990_004b1990(p3fes::EEContext&);
void fn_sub_4B1A30_004b1a30(p3fes::EEContext&);
void fn_sub_4B1A40_004b1a40(p3fes::EEContext&);
void fn_sub_4B1A80_004b1a80(p3fes::EEContext&);
void fn_sub_4B1AE0_004b1ae0(p3fes::EEContext&);
void fn_sub_4B1B00_004b1b00(p3fes::EEContext&);
void fn_sub_4B1B60_004b1b60(p3fes::EEContext&);
void fn_sub_4B1B90_004b1b90(p3fes::EEContext&);
void fn_sub_4B1C80_004b1c80(p3fes::EEContext&);
void fn_sub_4B2A90_004b2a90(p3fes::EEContext&);
void fn_sub_4B2B40_004b2b40(p3fes::EEContext&);
void fn_sub_4B2BA0_004b2ba0(p3fes::EEContext&);
void fn_sub_4B2BD0_004b2bd0(p3fes::EEContext&);
void fn_sub_4B2E70_004b2e70(p3fes::EEContext&);
void fn_sub_4B3030_004b3030(p3fes::EEContext&);
void fn_sub_4B30A0_004b30a0(p3fes::EEContext&);
void fn_sub_4B3100_004b3100(p3fes::EEContext&);
void fn_sub_4B3490_004b3490(p3fes::EEContext&);
void fn_sub_4B34D0_004b34d0(p3fes::EEContext&);
void fn_sub_4B34E0_004b34e0(p3fes::EEContext&);
void fn_sub_4B3610_004b3610(p3fes::EEContext&);
void fn_sub_4B3700_004b3700(p3fes::EEContext&);
void fn_sub_4B3720_004b3720(p3fes::EEContext&);
void fn_sub_4B3790_004b3790(p3fes::EEContext&);
void fn_sub_4B39F0_004b39f0(p3fes::EEContext&);
void fn_sub_4B3DE0_004b3de0(p3fes::EEContext&);
void fn_sub_4B3F50_004b3f50(p3fes::EEContext&);
void fn_sub_4B4090_004b4090(p3fes::EEContext&);
void fn_sub_4B40F0_004b40f0(p3fes::EEContext&);
void fn_sub_4B41B0_004b41b0(p3fes::EEContext&);
void fn_sub_4B4720_004b4720(p3fes::EEContext&);
void fn_sub_4B4810_004b4810(p3fes::EEContext&);
void fn_sub_4B4A60_004b4a60(p3fes::EEContext&);
void fn_sub_4B4A70_004b4a70(p3fes::EEContext&);
void fn_sub_4B4BA0_004b4ba0(p3fes::EEContext&);
void fn_sub_4B59B0_004b59b0(p3fes::EEContext&);
void fn_sub_4B6000_004b6000(p3fes::EEContext&);
void fn_sub_4B6190_004b6190(p3fes::EEContext&);
void fn_sub_4B6270_004b6270(p3fes::EEContext&);
void fn_sub_4B62A0_004b62a0(p3fes::EEContext&);
void fn_sub_4B6350_004b6350(p3fes::EEContext&);
void fn_sub_4B6500_004b6500(p3fes::EEContext&);
void fn_sub_4BAE00_004bae00(p3fes::EEContext&);
void fn_sub_4BB5D0_004bb5d0(p3fes::EEContext&);
void fn_sub_4BF6E0_004bf6e0(p3fes::EEContext&);
void fn_sub_4BF7E0_004bf7e0(p3fes::EEContext&);
void fn_sub_4BF9E0_004bf9e0(p3fes::EEContext&);
void fn_sub_4BFA10_004bfa10(p3fes::EEContext&);
void fn_sub_4BFA70_004bfa70(p3fes::EEContext&);
void fn_sub_4BFB20_004bfb20(p3fes::EEContext&);
void fn_sub_4BFC20_004bfc20(p3fes::EEContext&);
void fn_sub_4BFC80_004bfc80(p3fes::EEContext&);
void fn_sub_4BFD50_004bfd50(p3fes::EEContext&);
void fn_sub_4BFDE0_004bfde0(p3fes::EEContext&);
void fn_sub_4C0070_004c0070(p3fes::EEContext&);
void fn_sub_4C0230_004c0230(p3fes::EEContext&);
void fn_sub_4C03D0_004c03d0(p3fes::EEContext&);
void fn_sub_4C0420_004c0420(p3fes::EEContext&);
void fn_sub_4C0470_004c0470(p3fes::EEContext&);
void fn_sub_4C06B0_004c06b0(p3fes::EEContext&);
void fn_sub_4C0830_004c0830(p3fes::EEContext&);
void fn_sub_4C0870_004c0870(p3fes::EEContext&);
void fn_sub_4C0880_004c0880(p3fes::EEContext&);
void fn_sub_4C0F60_004c0f60(p3fes::EEContext&);
void fn_sub_4C0FD0_004c0fd0(p3fes::EEContext&);
void fn_sub_4C1600_004c1600(p3fes::EEContext&);
void fn_sub_4C19F0_004c19f0(p3fes::EEContext&);
void fn_sub_4C1BC0_004c1bc0(p3fes::EEContext&);
void fn_sub_4C1BE0_004c1be0(p3fes::EEContext&);
void fn_sub_4C1C00_004c1c00(p3fes::EEContext&);
void fn_sub_4C1C30_004c1c30(p3fes::EEContext&);
void fn_sub_4C1C50_004c1c50(p3fes::EEContext&);
void fn_sub_4C1CD0_004c1cd0(p3fes::EEContext&);
void fn_sub_4C1D10_004c1d10(p3fes::EEContext&);
void fn_sub_4C1E60_004c1e60(p3fes::EEContext&);
void fn_sub_4C1E70_004c1e70(p3fes::EEContext&);
void fn_sub_4C1F70_004c1f70(p3fes::EEContext&);
void fn_sub_4C2080_004c2080(p3fes::EEContext&);
void fn_sub_4C2090_004c2090(p3fes::EEContext&);
void fn_sub_4C20B0_004c20b0(p3fes::EEContext&);
void fn_sub_4C2120_004c2120(p3fes::EEContext&);
void fn_sub_4C2130_004c2130(p3fes::EEContext&);
void fn_sub_4C21B0_004c21b0(p3fes::EEContext&);
void fn_sub_4C21E0_004c21e0(p3fes::EEContext&);
void fn_sub_4C32A0_004c32a0(p3fes::EEContext&);
void fn_sub_4C33D0_004c33d0(p3fes::EEContext&);
void fn_sub_4C35D0_004c35d0(p3fes::EEContext&);
void fn_sub_4C3880_004c3880(p3fes::EEContext&);
void fn_sub_4C38C0_004c38c0(p3fes::EEContext&);
void fn_sub_4C3B60_004c3b60(p3fes::EEContext&);
void fn_sub_4C3C30_004c3c30(p3fes::EEContext&);
void fn_sub_4C5250_004c5250(p3fes::EEContext&);
void fn_sub_4C61B0_004c61b0(p3fes::EEContext&);
void fn_sub_4C6B20_004c6b20(p3fes::EEContext&);
void fn_sub_4C6BE0_004c6be0(p3fes::EEContext&);
void fn_sub_4C6C20_004c6c20(p3fes::EEContext&);
void fn_sub_4CA380_004ca380(p3fes::EEContext&);
void fn_sub_4CA3A0_004ca3a0(p3fes::EEContext&);
void fn_sub_4CA510_004ca510(p3fes::EEContext&);
void fn_sub_4CA520_004ca520(p3fes::EEContext&);
void fn_sub_4CA550_004ca550(p3fes::EEContext&);
void fn_sub_4CA560_004ca560(p3fes::EEContext&);
void fn_sub_4CA5B0_004ca5b0(p3fes::EEContext&);
void fn_sub_4CB2F0_004cb2f0(p3fes::EEContext&);
void fn_sub_4D0F00_004d0f00(p3fes::EEContext&);
void fn_sub_4F3EC0_004f3ec0(p3fes::EEContext&);
void fn_sub_4F3F70_004f3f70(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

using namespace rw4;
using namespace rw5;
using namespace rw6;

namespace gen = ::p3fes::recomp_gen;

// sub_45F930 [collWorldLineIntersections] -- the line test of RpCollisionWorldForAllIntersections: every triangle the line crosses
// ($a0 = the world, $a1 = the intersection (rw6::isect line), $a2 = the callback, $a3 = the data) The line's start, its
// delta and the reciprocals, and a tolerance per axis (1e-6 of the larger |start| / |end| coordinate); the world's BSP
// walked with an explicit stack of {node, entry t, exit t}: a plane keeps the side(s) the line's [t0, t1] reaches
// (the far side pushed, both intervals clipped at the plane bounds +- the tolerance); each sector with a collision
// block (sector + gp 0x7CE72C) has its tree walked the same way, and each leaf triangle (through the triangle map)
// gets the front-face line / triangle test (det > 1e-8, the edge conditions within 1e-5 of det). A hit fills the
// collision triangle on the stack (unit normal, first vertex, index, vertex pointers) and calls the callback with
// the distance t in $f12 (0 stops). Sectors without a collision block are not tested.
// 0x0045F930 sub_45F930 -- 3448 bytes; frame 0x620: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
void sub_45F930(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16}, f17{ctx, 17}, f18{ctx, 18}, f19{ctx, 19}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0045f930: the line: start, delta, reciprocal deltas (0 for a zero delta)
    enter(ctx, 42);  // entry check point + this block's cycles
    sp = addiu(sp, -0x620);
    sd(ra, sp, 0xA0);
    v1 = addiu(sp, 0x2EC);
    sq(fp, sp, 0x90);
    mtc1(zero, f0);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    sw(a2, sp, 0xD8);
    swc1(f21, sp, 0x4);
    sw(a3, sp, 0xD4);
    swc1(f20, sp, 0x0);
    sw(a1, sp, 0xDC);
    lwc1(f3, a1, 0);
    lwc1(f2, a1, 4);
    lwc1(f1, a1, 8);
    swc1(f3, sp, 0x2E0);
    swc1(f2, sp, 0x2E4);
    swc1(f1, sp, 0x2E8);
    lwc1(f2, a1, 12);
    lwc1(f1, a1, 0);
    sub_s(f1, f2, f1);
    swc1(f1, v1, 0);
    lwc1(f1, v1, 0);
    lwc1(f3, a1, 16);
    lwc1(f2, a1, 4);
    v1 = addiu(sp, 0x2F0);
    c_eq_s(f0, f1);
    sub_s(f2, f3, f2);
    swc1(f2, v1, 0);
    lwc1(f3, a1, 20);
    v1 = addiu(sp, 0x2F4);
    lwc1(f2, a1, 8);
    sub_s(f2, f3, f2);
    swc1(f2, v1, 0);
    if (!cond(ctx)) {
        // 0x0045f9d8
        charge(ctx, 7);
        v1 = 0x3F800000;
        mtc1(v1, f0);
        div_s(f0, f0, f1);
    }
    // 0x0045f9f4
    charge(ctx, 9);
    v1 = addiu(sp, 0x2F0);
    s7 = addiu(sp, 0x2F8);
    lwc1(f1, v1, 0);
    swc1(f0, s7, 0);
    mtc1(zero, f0);
    c_eq_s(f0, f1);
    if (!cond(ctx)) {
        // 0x0045fa18
        charge(ctx, 7);
        v1 = 0x3F800000;
        mtc1(v1, f0);
        div_s(f0, f0, f1);
    }
    // 0x0045fa34
    charge(ctx, 9);
    v1 = addiu(sp, 0x2FC);
    swc1(f0, v1, 0);
    v1 = addiu(sp, 0x2F4);
    lwc1(f1, v1, 0);
    mtc1(zero, f0);
    c_eq_s(f0, f1);
    if (!cond(ctx)) {
        // 0x0045fa58
        charge(ctx, 7);
        v1 = 0x3F800000;
        mtc1(v1, f0);
        div_s(f0, f0, f1);
    }
    // 0x0045fa74: the per-axis tolerance: 1e-6 x max(|start|, |end|) on each axis
    charge(ctx, 8);
    v1 = addiu(sp, 0x300);
    swc1(f0, v1, 0);
    lw(v1, sp, 0xDC);
    mtc1(zero, f0);
    lwc1(f2, v1, 12);
    c_lt_s(f2, f0);
    if (cond(ctx)) {
        // 0x0045fa9c
        charge(ctx, 1);
        neg_s(f3, f2);
    } else {
        // 0x0045fa94
        charge(ctx, 2);
        mov_s(f3, f2);
    }
    // 0x0045faa0
    charge(ctx, 6);
    lw(v1, sp, 0xDC);
    mtc1(zero, f0);
    lwc1(f1, v1, 0);
    c_lt_s(f1, f0);
    if (cond(ctx)) {
        // 0x0045fac0
        charge(ctx, 1);
        neg_s(f0, f1);
    } else {
        // 0x0045fab8
        charge(ctx, 2);
        mov_s(f0, f1);
    }
    // 0x0045fac4
    charge(ctx, 3);
    c_lt_s(f0, f3);
    if (cond(ctx)) {
        // 0x0045faf8
        charge(ctx, 5);
        mtc1(zero, f0);
        c_lt_s(f2, f0);
        if (cond(ctx)) {
            // 0x0045fb14
            charge(ctx, 2);
            neg_s(f2, f2);
            mov_s(f1, f2);
        } else {
            // 0x0045fb0c
            charge(ctx, 2);
            mov_s(f1, f2);
        }
        // 0x0045fb1c
        charge(ctx, 1);
        v1 = addiu(sp, 0x304);
    } else {
        // 0x0045fad0
        charge(ctx, 5);
        mtc1(zero, f0);
        c_lt_s(f1, f0);
        if (cond(ctx)) {
            // 0x0045faec
            charge(ctx, 1);
            neg_s(f1, f1);
        } else {
            // 0x0045fae4
            charge(ctx, 2);
        }
        // 0x0045faf0
        charge(ctx, 2);
        v1 = addiu(sp, 0x304);
    }
    // 0x0045fb20
    charge(ctx, 7);
    swc1(f1, v1, 0);
    lw(v1, sp, 0xDC);
    mtc1(zero, f0);
    lwc1(f2, v1, 16);
    c_lt_s(f2, f0);
    if (cond(ctx)) {
        // 0x0045fb44
        charge(ctx, 1);
        neg_s(f3, f2);
    } else {
        // 0x0045fb3c
        charge(ctx, 2);
        mov_s(f3, f2);
    }
    // 0x0045fb48
    charge(ctx, 6);
    lw(v1, sp, 0xDC);
    mtc1(zero, f0);
    lwc1(f1, v1, 4);
    c_lt_s(f1, f0);
    if (cond(ctx)) {
        // 0x0045fb68
        charge(ctx, 1);
        neg_s(f0, f1);
    } else {
        // 0x0045fb60
        charge(ctx, 2);
        mov_s(f0, f1);
    }
    // 0x0045fb6c
    charge(ctx, 3);
    c_lt_s(f0, f3);
    if (cond(ctx)) {
        // 0x0045fba0
        charge(ctx, 5);
        mtc1(zero, f0);
        c_lt_s(f2, f0);
        if (cond(ctx)) {
            // 0x0045fbbc
            charge(ctx, 2);
            neg_s(f2, f2);
            mov_s(f1, f2);
        } else {
            // 0x0045fbb4
            charge(ctx, 2);
            mov_s(f1, f2);
        }
        // 0x0045fbc4
        charge(ctx, 1);
        v1 = addiu(sp, 0x308);
    } else {
        // 0x0045fb78
        charge(ctx, 5);
        mtc1(zero, f0);
        c_lt_s(f1, f0);
        if (cond(ctx)) {
            // 0x0045fb94
            charge(ctx, 1);
            neg_s(f1, f1);
        } else {
            // 0x0045fb8c
            charge(ctx, 2);
        }
        // 0x0045fb98
        charge(ctx, 2);
        v1 = addiu(sp, 0x308);
    }
    // 0x0045fbc8
    charge(ctx, 7);
    swc1(f1, v1, 0);
    lw(v1, sp, 0xDC);
    mtc1(zero, f0);
    lwc1(f1, v1, 20);
    c_lt_s(f1, f0);
    if (cond(ctx)) {
        // 0x0045fbec
        charge(ctx, 1);
        neg_s(f2, f1);
    } else {
        // 0x0045fbe4
        charge(ctx, 2);
        mov_s(f2, f1);
    }
    // 0x0045fbf0
    charge(ctx, 6);
    lw(v1, sp, 0xDC);
    mtc1(zero, f0);
    lwc1(f3, v1, 8);
    c_lt_s(f3, f0);
    if (cond(ctx)) {
        // 0x0045fc10
        charge(ctx, 1);
        neg_s(f0, f3);
    } else {
        // 0x0045fc08
        charge(ctx, 2);
        mov_s(f0, f3);
    }
    // 0x0045fc14
    charge(ctx, 3);
    c_lt_s(f0, f2);
    if (cond(ctx)) {
        // 0x0045fc48
        charge(ctx, 5);
        mtc1(zero, f0);
        c_lt_s(f1, f0);
        if (cond(ctx)) {
            // 0x0045fc64
            charge(ctx, 2);
            neg_s(f1, f1);
            mov_s(f3, f1);
        } else {
            // 0x0045fc5c
            charge(ctx, 2);
            mov_s(f3, f1);
        }
        // 0x0045fc6c
        charge(ctx, 1);
        v1 = 0x35860000;
    } else {
        // 0x0045fc20
        charge(ctx, 5);
        mtc1(zero, f0);
        c_lt_s(f3, f0);
        if (cond(ctx)) {
            // 0x0045fc3c
            charge(ctx, 1);
            neg_s(f3, f3);
        } else {
            // 0x0045fc34
            charge(ctx, 2);
        }
        // 0x0045fc40
        charge(ctx, 2);
        v1 = 0x35860000;
    }
    // 0x0045fc70: the BSP stack {node, t0, t1} (12 bytes) with the root and [0, 1]
    charge(ctx, 28);
    a2 = addiu(sp, 0x31C);
    v1 = v1 | 0x37BD;
    a3 = 0x3F800000;
    mtc1(v1, f2);
    s1 = addiu(sp, 0x61C);
    v1 = addiu(sp, 0x304);
    lwc1(f1, v1, 0);
    mul_s(f0, f3, f2);
    v1 = addiu(sp, 0x310);
    v1 = sltu(v1, a2);
    v1 = v1 ^ 0x1;
    a1 = v1 ^ 0x1;
    v1 = addiu(sp, 0x30C);
    swc1(f0, v1, 0);
    mul_s(f0, f1, f2);
    v1 = addiu(sp, 0x304);
    swc1(f0, v1, 0);
    v1 = addiu(sp, 0x308);
    lwc1(f0, v1, 0);
    mul_s(f0, f0, f2);
    swc1(f0, v1, 0);
    lw(a0, a0, 28);
    v1 = addiu(sp, 0x310);
    sw(a0, v1, 0);
    sw(a3, sp, 0x318);
    sw(a2, s1, 0);
    sw(zero, sp, 0x314);
    if (a1 != 0) {
        // 0x0045fce0
        charge(ctx, 3);
        fp = addiu(sp, 0x12C);
        s0 = addiu(sp, 0x2D8);
        s6 = addiu(sp, 0xEC);
        for (;;) {
            // 0x0045fcec: pop a node
            charge(ctx, 7);
            lw(v1, s1, 0);
            a2 = addiu(v1, -12);
            sw(a2, s1, 0);
            lw(s4, v1, -12);
            lw(v1, s4, 0);
            if (i64(v1) >= 0) {
                // 0x0045fd08
                charge(ctx, 1);
                mtc1(zero, f3);
                for (;;) {
                    // 0x0045fd0c: a plane: the side(s) the line's [t0, t1] reaches (the far side pushed with its clipped interval)
                    charge(ctx, 21);
                    lw(a1, s4, 0);
                    v1 = addiu(sp, 0x2EC);
                    lwc1(f4, a2, 8);
                    lwc1(f1, s4, 20);
                    lwc1(f0, s4, 16);
                    lwc1(f2, a2, 4);
                    a0 = addu(v1, a1);
                    v1 = addu(a1, sp);
                    lwc1(f6, v1, 736);
                    lwc1(f7, a0, 0);
                    v1 = addiu(sp, 0x304);
                    v1 = addu(v1, a1);
                    lwc1(f5, v1, 0);
                    adda_s(f3, f6);
                    madd_s(f4, f4, f7);
                    adda_s(f3, f6);
                    c_le_s(f7, f3);
                    sub_s(f6, f1, f5);
                    add_s(f5, f0, f5);
                    madd_s(f8, f2, f7);
                    if (cond(ctx)) {
                        // 0x0045fdf0
                        charge(ctx, 3);
                        c_lt_s(f5, f4);
                        if (cond(ctx)) {
                            // 0x00460470
                            charge(ctx, 3);
                            lw(v1, s4, 12);
                            sw(v1, a2, 0);
                            backedge(ctx);
                        } else {
                            // 0x0045fdfc
                            charge(ctx, 3);
                            c_le_s(f6, f8);
                            if (!cond(ctx)) {
                                // 0x00460480
                                charge(ctx, 3);
                                lw(v1, s4, 8);
                                sw(v1, a2, 0);
                                backedge(ctx);
                            } else {
                                // 0x0045fe08
                                charge(ctx, 17);
                                lw(v1, s1, 0);
                                c_le_s(f6, f4);
                                v1 = addiu(v1, 12);
                                sw(v1, s1, 0);
                                lw(a1, s4, 0);
                                lw(a0, s4, 12);
                                lw(v1, s1, 0);
                                a1 = addu(s7, a1);
                                lwc1(f2, a1, 0);
                                sw(a0, v1, 0);
                                lw(v1, s1, 0);
                                lwc1(f0, v1, -8);
                                swc1(f0, v1, 4);
                                lw(v1, s1, 0);
                                lwc1(f0, v1, -4);
                                swc1(f0, v1, 8);
                                if (!cond(ctx)) {
                                    // 0x00460490
                                    charge(ctx, 7);
                                    lw(v1, s1, 0);
                                    sub_s(f1, f6, f4);
                                    lwc1(f0, v1, 8);
                                    adda_s(f3, f0);
                                    madd_s(f0, f2, f1);
                                    swc1(f0, v1, 8);
                                    backedge(ctx);
                                } else {
                                    // 0x0045fe4c
                                    charge(ctx, 1);
                                }
                                // 0x0045fe50
                                charge(ctx, 5);
                                lw(a0, s4, 8);
                                lw(v1, s1, 0);
                                c_lt_s(f5, f8);
                                sw(a0, v1, -12);
                                if (cond(ctx)) {
                                    // 0x0045fe64
                                    charge(ctx, 7);
                                    lw(v1, s1, 0);
                                    sub_s(f1, f5, f8);
                                    lwc1(f0, v1, -8);
                                    adda_s(f3, f0);
                                    madd_s(f0, f2, f1);
                                    swc1(f0, v1, -8);
                                }
                            }
                        }
                    } else {
                        // 0x0045fd60
                        charge(ctx, 3);
                        c_le_s(f6, f4);
                        if (!cond(ctx)) {
                            // 0x00460430
                            charge(ctx, 3);
                            lw(v1, s4, 8);
                            sw(v1, a2, 0);
                            backedge(ctx);
                        } else {
                            // 0x0045fd6c
                            charge(ctx, 3);
                            c_lt_s(f5, f8);
                            if (cond(ctx)) {
                                // 0x00460440
                                charge(ctx, 3);
                                lw(v1, s4, 12);
                                sw(v1, a2, 0);
                                backedge(ctx);
                            } else {
                                // 0x0045fd78
                                charge(ctx, 17);
                                lw(v1, s1, 0);
                                c_lt_s(f5, f4);
                                v1 = addiu(v1, 12);
                                sw(v1, s1, 0);
                                lw(a1, s4, 0);
                                lw(a0, s4, 8);
                                lw(v1, s1, 0);
                                a1 = addu(s7, a1);
                                lwc1(f2, a1, 0);
                                sw(a0, v1, 0);
                                lw(v1, s1, 0);
                                lwc1(f0, v1, -8);
                                swc1(f0, v1, 4);
                                lw(v1, s1, 0);
                                lwc1(f0, v1, -4);
                                swc1(f0, v1, 8);
                                if (cond(ctx)) {
                                    // 0x00460450
                                    charge(ctx, 7);
                                    lw(v1, s1, 0);
                                    sub_s(f1, f5, f4);
                                    lwc1(f0, v1, 8);
                                    adda_s(f3, f0);
                                    madd_s(f0, f2, f1);
                                    swc1(f0, v1, 8);
                                    backedge(ctx);
                                } else {
                                    // 0x0045fdbc
                                    charge(ctx, 1);
                                }
                                // 0x0045fdc0
                                charge(ctx, 5);
                                lw(a0, s4, 12);
                                lw(v1, s1, 0);
                                c_le_s(f6, f8);
                                sw(a0, v1, -12);
                                if (!cond(ctx)) {
                                    // 0x0045fdd4
                                    charge(ctx, 7);
                                    lw(v1, s1, 0);
                                    sub_s(f1, f6, f8);
                                    lwc1(f0, v1, -8);
                                    adda_s(f3, f0);
                                    madd_s(f0, f2, f1);
                                    swc1(f0, v1, -8);
                                }
                            }
                        }
                    }
                    // 0x0045fe80
                    charge(ctx, 5);
                    lw(a2, s1, 0);
                    lw(s4, a2, 0);
                    lw(v1, s4, 0);
                    if (i64(v1) < 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0045fe94: a sector: its collision block (none: skipped)
                charge(ctx, 1);
            }
            // 0x0045fe98
            charge(ctx, 5);
            lw(v1, gp, -17860);  // 0x7CE72C (the collision sector extension offset)
            v1 = addu(s4, v1);
            lw(s3, v1, 0);
            if (s3 != 0) {
                // 0x0045feac
                charge(ctx, 13);
                lw(v1, s4, 4);
                a0 = 255;
                sq(v1, sp, 0xC0);
                lw(v1, s4, 8);
                sq(v1, sp, 0xB0);
                v1 = addiu(sp, 0x145);
                sw(s3, sp, 0x110);
                sb(a0, v1, 0);
                v1 = addiu(sp, 0x146);
                sh(zero, v1, 0);
                lhu(v1, s3, coll::kNumSplits);
                if (v1 == 0) {
                    // 0x004604b0
                    charge(ctx, 4);
                    lhu(a0, s3, coll::kNumTriangles);
                    v1 = addiu(sp, 0x145);
                    sb(a0, v1, 0);
                    backedge(ctx);
                }
                // 0x0045fee0: the collision tree's stack {child entry, t0, t1} with the root entry (built on the stack)
                charge(ctx, 63);
                a0 = addiu(sp, 0x144);
                v1 = addiu(sp, 0x14C);
                sw(a0, v1, 0);
                a1 = addiu(sp, 0x158);
                v1 = addiu(sp, 0x2E4);
                lw(a0, s1, 0);
                lwc1(f4, v1, 0);
                lwc1(f5, sp, 0x2E0);
                v1 = addiu(sp, 0x2E8);
                lwc1(f3, v1, 0);
                v1 = addiu(sp, 0x2EC);
                lwc1(f2, v1, 0);
                v1 = addiu(sp, 0x2F0);
                lwc1(f1, v1, 0);
                v1 = addiu(sp, 0x14C);
                v1 = sltu(v1, a1);
                a1 = addiu(sp, 0x2F4);
                v1 = v1 ^ 0x1;
                lwc1(f0, a1, 0);
                v1 = v1 ^ 0x1;
                a1 = addiu(sp, 0x118);
                swc1(f4, a1, 0);
                a1 = addiu(sp, 0x114);
                swc1(f5, a1, 0);
                a1 = addiu(sp, 0x11C);
                swc1(f3, a1, 0);
                a1 = addiu(sp, 0x120);
                swc1(f2, a1, 0);
                a1 = addiu(sp, 0x124);
                swc1(f1, a1, 0);
                a1 = addiu(sp, 0x128);
                swc1(f0, a1, 0);
                a1 = addiu(sp, 0x2FC);
                lwc1(f4, a1, 0);
                lwc1(f5, s7, 0);
                a1 = addiu(sp, 0x300);
                lwc1(f3, a1, 0);
                swc1(f5, fp, 0x0);
                a1 = addiu(sp, 0x304);
                lwc1(f2, a1, 0);
                a1 = addiu(sp, 0x308);
                lwc1(f1, a1, 0);
                a1 = addiu(sp, 0x30C);
                lwc1(f0, a1, 0);
                a1 = addiu(sp, 0x130);
                swc1(f4, a1, 0);
                a1 = addiu(sp, 0x134);
                swc1(f3, a1, 0);
                a1 = addiu(sp, 0x138);
                swc1(f2, a1, 0);
                a1 = addiu(sp, 0x13C);
                swc1(f1, a1, 0);
                a1 = addiu(sp, 0x140);
                swc1(f0, a1, 0);
                lwc1(f0, a0, 4);
                a1 = addiu(sp, 0x150);
                swc1(f0, a1, 0);
                lwc1(f0, a0, 8);
                a0 = addiu(sp, 0x154);
                swc1(f0, a0, 0);
                a0 = addiu(sp, 0x158);
                sw(a0, s0, 0);
                if (v1 == 0) {
                    goto L_0046040c;
                }
                for (;;) {
                    // 0x0045ffdc: pop a child entry
                    charge(ctx, 8);
                    lw(v1, s0, 0);
                    a0 = 255;
                    a1 = addiu(v1, -12);
                    sw(a1, s0, 0);
                    lw(a2, v1, -12);
                    lbu(v1, a2, 1);
                    if (v1 == a0) {
                        // 0x0045fffc
                        charge(ctx, 1);
                        mtc1(zero, f3);
                        for (;;) {
                            // 0x00460000: a split: the side(s) the line reaches, as for a plane
                            charge(ctx, 28);
                            lw(v1, sp, 0x110);
                            lwc1(f4, a1, 8);
                            lhu(a2, a2, 2);
                            lwc1(f2, a1, 4);
                            lw(v1, v1, 32);
                            a2 = sll(a2, 4);
                            v1 = addu(v1, a2);
                            lbu(a2, v1, 0);
                            lwc1(f1, v1, 12);
                            lwc1(f0, v1, 4);
                            t1 = a2 & 0xC;
                            a2 = addiu(sp, 0x120);
                            t0 = addu(a2, t1);
                            a2 = addiu(sp, 0x114);
                            a3 = addu(a2, t1);
                            a2 = addiu(sp, 0x138);
                            a2 = addu(a2, t1);
                            lwc1(f5, a2, 0);
                            lwc1(f6, a3, 0);
                            lwc1(f7, t0, 0);
                            sub_s(f8, f1, f5);
                            adda_s(f3, f6);
                            madd_s(f1, f4, f7);
                            adda_s(f3, f6);
                            add_s(f5, f0, f5);
                            c_le_s(f7, f3);
                            madd_s(f4, f2, f7);
                            if (cond(ctx)) {
                                // 0x004600f8
                                charge(ctx, 3);
                                c_lt_s(f5, f1);
                                if (cond(ctx)) {
                                    // 0x004604f8
                                    charge(ctx, 3);
                                    v1 = addiu(v1, 8);
                                    sw(v1, a1, 0);
                                    backedge(ctx);
                                } else {
                                    // 0x00460104
                                    charge(ctx, 3);
                                    c_le_s(f8, f4);
                                    if (!cond(ctx)) {
                                        // 0x00460508
                                        charge(ctx, 2);
                                        sw(v1, a1, 0);
                                        backedge(ctx);
                                    } else {
                                        // 0x00460110
                                        charge(ctx, 16);
                                        lw(a3, s0, 0);
                                        a1 = addu(fp, t1);
                                        a2 = addiu(v1, 8);
                                        c_le_s(f8, f1);
                                        a3 = addiu(a3, 12);
                                        sw(a3, s0, 0);
                                        lwc1(f2, a1, 0);
                                        lw(a1, s0, 0);
                                        sw(a2, a1, 0);
                                        lw(a1, s0, 0);
                                        lwc1(f0, a1, -8);
                                        swc1(f0, a1, 4);
                                        lw(a1, s0, 0);
                                        lwc1(f0, a1, -4);
                                        swc1(f0, a1, 8);
                                        if (!cond(ctx)) {
                                            // 0x00460510
                                            charge(ctx, 7);
                                            lw(a1, s0, 0);
                                            sub_s(f1, f8, f1);
                                            lwc1(f0, a1, 8);
                                            adda_s(f3, f0);
                                            madd_s(f0, f2, f1);
                                            swc1(f0, a1, 8);
                                            backedge(ctx);
                                        }
                                        // 0x00460150
                                        charge(ctx, 4);
                                        lw(a1, s0, 0);
                                        c_lt_s(f5, f4);
                                        sw(v1, a1, -12);
                                        if (cond(ctx)) {
                                            // 0x00460160
                                            charge(ctx, 6);
                                            lw(v1, s0, 0);
                                            sub_s(f1, f5, f4);
                                            lwc1(f0, v1, -8);
                                            adda_s(f3, f0);
                                            madd_s(f0, f2, f1);
                                            swc1(f0, v1, -8);
                                        }
                                    }
                                }
                            } else {
                                // 0x00460070
                                charge(ctx, 3);
                                c_le_s(f8, f1);
                                if (!cond(ctx)) {
                                    // 0x004604c0
                                    charge(ctx, 2);
                                    sw(v1, a1, 0);
                                    backedge(ctx);
                                } else {
                                    // 0x0046007c
                                    charge(ctx, 3);
                                    c_lt_s(f5, f4);
                                    if (cond(ctx)) {
                                        // 0x004604c8
                                        charge(ctx, 3);
                                        v1 = addiu(v1, 8);
                                        sw(v1, a1, 0);
                                        backedge(ctx);
                                    } else {
                                        // 0x00460088
                                        charge(ctx, 15);
                                        lw(a2, s0, 0);
                                        a1 = addu(fp, t1);
                                        c_lt_s(f5, f1);
                                        a2 = addiu(a2, 12);
                                        sw(a2, s0, 0);
                                        lwc1(f2, a1, 0);
                                        lw(a1, s0, 0);
                                        sw(v1, a1, 0);
                                        lw(a1, s0, 0);
                                        lwc1(f0, a1, -8);
                                        swc1(f0, a1, 4);
                                        lw(a1, s0, 0);
                                        lwc1(f0, a1, -4);
                                        swc1(f0, a1, 8);
                                        if (cond(ctx)) {
                                            // 0x004604d8
                                            charge(ctx, 7);
                                            lw(a1, s0, 0);
                                            sub_s(f1, f5, f1);
                                            lwc1(f0, a1, 8);
                                            adda_s(f3, f0);
                                            madd_s(f0, f2, f1);
                                            swc1(f0, a1, 8);
                                            backedge(ctx);
                                        } else {
                                            // 0x004600c4
                                            charge(ctx, 1);
                                        }
                                        // 0x004600c8
                                        charge(ctx, 5);
                                        a1 = addiu(v1, 8);
                                        lw(v1, s0, 0);
                                        c_le_s(f8, f4);
                                        sw(a1, v1, -12);
                                        if (!cond(ctx)) {
                                            // 0x004600dc
                                            charge(ctx, 7);
                                            lw(v1, s0, 0);
                                            sub_s(f1, f8, f4);
                                            lwc1(f0, v1, -8);
                                            adda_s(f3, f0);
                                            madd_s(f0, f2, f1);
                                            swc1(f0, v1, -8);
                                        }
                                    }
                                }
                            }
                            // 0x00460178
                            charge(ctx, 5);
                            lw(a1, s0, 0);
                            lw(a2, a1, 0);
                            lbu(v1, a2, 1);
                            if (v1 != a0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x0046018c: a leaf: its triangles [first, first + count)
                        charge(ctx, 1);
                    }
                    // 0x00460190
                    charge(ctx, 7);
                    lw(a0, a1, 0);
                    v1 = v1 & 0xFF;
                    lhu(s2, a0, 2);
                    s5 = addu(s2, v1);
                    at = slt(s2, s5);
                    if (at != 0) {
                        for (;;) {
                            // 0x004601ac: each triangle (through the triangle map when there is one)
                            charge(ctx, 3);
                            lw(a0, s3, coll::kTriMap);
                            if (a0 == 0) {
                                // 0x004601cc
                                charge(ctx, 1);
                                v1 = s2;
                            } else {
                                // 0x004601b8
                                charge(ctx, 5);
                                v1 = s2 & 0xFFFF;
                                v1 = sll(v1, 1);
                                v1 = addu(a0, v1);
                                lhu(v1, v1, 0);
                            }
                            // 0x004601d0: the line / triangle test: front faces only (det > 1e-8), the edge conditions within 1e-5 of det
                            charge(ctx, 57);
                            a2 = v1 & 0xFFFF;
                            v1 = 0x322B0000;
                            a0 = sll(a2, 3);
                            v1 = v1 | 0xCC77;
                            mtc1(v1, f1);
                            lq(v1, sp, 0xC0);
                            a3 = addu(v1, a0);
                            v1 = addiu(sp, 0x2F4);
                            lhu(a1, a3, 0);
                            lwc1(f8, v1, 0);
                            lhu(a0, a3, 2);
                            lhu(t0, a3, 4);
                            v1 = addiu(sp, 0x2F0);
                            lwc1(f7, v1, 0);
                            v1 = addiu(sp, 0x2EC);
                            lwc1(f6, v1, 0);
                            v1 = sll(a1, 1);
                            a1 = addu(v1, a1);
                            v1 = sll(a0, 1);
                            a1 = sll(a1, 2);
                            a0 = addu(v1, a0);
                            lq(v1, sp, 0xB0);
                            a0 = sll(a0, 2);
                            a1 = addu(v1, a1);
                            a0 = addu(v1, a0);
                            v1 = sll(t0, 1);
                            v1 = addu(v1, t0);
                            t0 = sll(v1, 2);
                            lq(v1, sp, 0xB0);
                            lwc1(f11, a1, 0);
                            lwc1(f4, a0, 0);
                            lwc1(f9, a1, 8);
                            lwc1(f2, a0, 8);
                            lwc1(f10, a1, 4);
                            lwc1(f3, a0, 4);
                            v1 = addu(v1, t0);
                            lwc1(f0, v1, 0);
                            sub_s(f18, f4, f11);
                            sub_s(f21, f2, f9);
                            sub_s(f15, f0, f11);
                            lwc1(f0, v1, 8);
                            lwc1(f2, v1, 4);
                            sub_s(f19, f3, f10);
                            sub_s(f17, f0, f9);
                            sub_s(f16, f2, f10);
                            mula_s(f7, f17);
                            msub_s(f12, f8, f16);
                            mula_s(f8, f15);
                            msub_s(f13, f6, f17);
                            mula_s(f6, f16);
                            msub_s(f14, f7, f15);
                            mula_s(f19, f13);
                            madda_s(f18, f12);
                            madd_s(f0, f21, f14);
                            c_le_s(f0, f1);
                            a3 = 1;
                            if (cond(ctx)) {
                                // 0x004602b4
                                charge(ctx, 1);
                                a3 = 0;
                            }
                            // 0x004602b8
                            charge(ctx, 2);
                            if (a3 != 0) {
                                // 0x004602c0
                                charge(ctx, 20);
                                a3 = addiu(sp, 0x2E4);
                                lwc1(f2, a3, 0);
                                neg_s(f4, f0);
                                lwc1(f3, sp, 0x2E0);
                                a3 = 0x37270000;
                                t0 = a3 | 0xC5AC;
                                mtc1(t0, f5);
                                a3 = 1;
                                mul_s(f22, f5, f4);
                                t0 = addiu(sp, 0x2E8);
                                sub_s(f5, f2, f10);
                                lwc1(f1, t0, 0);
                                sub_s(f4, f3, f11);
                                mula_s(f5, f13);
                                sub_s(f1, f1, f9);
                                madda_s(f4, f12);
                                madd_s(f9, f1, f14);
                                c_lt_s(f9, f22);
                                sub_s(f10, f0, f22);
                                if (cond(ctx)) {
                                    // 0x00460310
                                    charge(ctx, 1);
                                    a3 = 0;
                                }
                                // 0x00460314
                                charge(ctx, 2);
                                if (a3 != 0) {
                                    // 0x0046031c
                                    charge(ctx, 3);
                                    c_le_s(f9, f10);
                                    a3 = 1;
                                    if (!cond(ctx)) {
                                        // 0x00460328
                                        charge(ctx, 1);
                                        a3 = 0;
                                    }
                                }
                                // 0x0046032c
                                charge(ctx, 2);
                                if (a3 != 0) {
                                    // 0x00460334
                                    charge(ctx, 12);
                                    mula_s(f5, f21);
                                    msub_s(f2, f1, f19);
                                    mula_s(f1, f18);
                                    msub_s(f3, f4, f21);
                                    mula_s(f4, f19);
                                    msub_s(f4, f5, f18);
                                    mula_s(f7, f3);
                                    madda_s(f6, f2);
                                    madd_s(f1, f8, f4);
                                    c_lt_s(f1, f22);
                                    a3 = 1;
                                    if (cond(ctx)) {
                                        // 0x00460364
                                        charge(ctx, 1);
                                        a3 = 0;
                                    }
                                    // 0x00460368
                                    charge(ctx, 2);
                                    if (a3 != 0) {
                                        // 0x00460370
                                        charge(ctx, 4);
                                        add_s(f1, f9, f1);
                                        c_le_s(f1, f10);
                                        a3 = 1;
                                        if (!cond(ctx)) {
                                            // 0x00460380
                                            charge(ctx, 1);
                                            a3 = 0;
                                        }
                                    }
                                    // 0x00460384
                                    charge(ctx, 2);
                                    if (a3 != 0) {
                                        // 0x0046038c
                                        charge(ctx, 6);
                                        mula_s(f16, f3);
                                        madda_s(f15, f2);
                                        madd_s(f20, f17, f4);
                                        c_lt_s(f20, f22);
                                        a3 = 1;
                                        if (cond(ctx)) {
                                            // 0x004603a4
                                            charge(ctx, 1);
                                            a3 = 0;
                                        }
                                        // 0x004603a8
                                        charge(ctx, 2);
                                        if (a3 != 0) {
                                            // 0x004603b0
                                            charge(ctx, 3);
                                            c_le_s(f20, f10);
                                            a3 = 1;
                                            if (!cond(ctx)) {
                                                // 0x004603bc
                                                charge(ctx, 1);
                                                a3 = 0;
                                            }
                                        }
                                        // 0x004603c0
                                        charge(ctx, 2);
                                        if (a3 != 0) {
                                            // 0x004603c8
                                            charge(ctx, 3);
                                            div_s(f20, f20, f0);
                                        }
                                    }
                                }
                            }
                            // 0x004603d4: a hit: the collision triangle (normal, first vertex, index, vertex pointers)
                            charge(ctx, 2);
                            if (a3 != 0) {
                                // 0x00460530
                                charge(ctx, 50);
                                v0 = addiu(sp, 0xF8);
                                lwc1(f3, a1, 0);
                                lwc1(f1, a1, 4);
                                lwc1(f0, a1, 8);
                                mtc1(zero, f2);
                                sw(a2, v0, 0);
                                swc1(f3, s6, 0);
                                v0 = addiu(sp, 0xFC);
                                sw(a1, v0, 0);
                                swc1(f1, s6, 4);
                                v0 = addiu(sp, 0x100);
                                sw(a0, v0, 0);
                                swc1(f0, s6, 8);
                                v0 = addiu(sp, 0x104);
                                sw(v1, v0, 0);
                                lwc1(f6, a1, 0);
                                v0 = addiu(sp, 0xE4);
                                lwc1(f5, a0, 0);
                                lwc1(f0, v1, 0);
                                lwc1(f3, a1, 8);
                                lwc1(f1, a0, 8);
                                lwc1(f8, a1, 4);
                                lwc1(f4, a0, 4);
                                sub_s(f9, f5, f6);
                                sub_s(f5, f0, f6);
                                sub_s(f6, f1, f3);
                                lwc1(f0, v1, 8);
                                lwc1(f1, v1, 4);
                                sub_s(f7, f4, f8);
                                sub_s(f0, f0, f3);
                                sub_s(f4, f1, f8);
                                mula_s(f7, f0);
                                msub_s(f3, f6, f4);
                                mula_s(f6, f5);
                                msub_s(f1, f9, f0);
                                mula_s(f9, f4);
                                msub_s(f0, f7, f5);
                                swc1(f1, v0, 0);
                                mula_s(f1, f1);
                                v0 = addiu(sp, 0xE8);
                                madda_s(f3, f3);
                                swc1(f0, v0, 0);
                                swc1(f3, sp, 0xE0);
                                madd_s(f0, f0, f0);
                                sqrt_s(f3, f0);
                                c_le_s(f3, f2);
                                if (!cond(ctx)) {
                                    // 0x004605f8
                                    charge(ctx, 7);
                                    v0 = 0x3F800000;
                                    mtc1(v0, f0);
                                    div_s(f3, f0, f3);
                                }
                                // 0x00460614: the callback (a0 = the intersection, a1 = the sector, a2 = the collision triangle, $f12 = the distance, a3 = the data); 0 ends the walk
                                charge(ctx, 22);
                                v0 = addiu(sp, 0xE4);
                                lw(a0, sp, 0xDC);
                                lwc1(f1, v0, 0);
                                lw(a3, sp, 0xD4);
                                lwc1(f2, sp, 0xE0);
                                a1 = s4;
                                mov_s(f12, f20);
                                a2 = addiu(sp, 0xE0);
                                v0 = addiu(sp, 0xE8);
                                lwc1(f0, v0, 0);
                                mul_s(f2, f2, f3);
                                mul_s(f1, f1, f3);
                                v0 = addiu(sp, 0xE4);
                                swc1(f1, v0, 0);
                                mul_s(f0, f0, f3);
                                v0 = addiu(sp, 0xE8);
                                swc1(f0, v0, 0);
                                lw(v0, sp, 0xD8);
                                jt = v0.u();  // the target, read before the delay slot
                                link(ctx, 0x46065Cu);  // $ra = the return address
                                swc1(f2, sp, 0xE0);
                                call_ptr(ctx, jt);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                                goto L_004603dc;
                            }
                        L_004603dc:
                            charge(ctx, 5);
                            v1 = addiu(s2, 1);
                            s2 = v1 & 0xFFFF;
                            v1 = slt(s2, s5);
                            if (v1 == 0) {
                                goto L_004603f0;
                            }
                            backedge(ctx);
                        }
                        break;
                    }
                L_004603f0:
                    charge(ctx, 7);
                    lw(a0, s0, 0);
                    v1 = addiu(sp, 0x14C);
                    v1 = sltu(v1, a0);
                    v1 = v1 ^ 0x1;
                    v1 = v1 ^ 0x1;
                    if (v1 == 0) {
                        goto L_0046040c;
                    }
                    backedge(ctx);
                }
                break;
            }
        L_0046040c:
            charge(ctx, 7);
            lw(a0, s1, 0);
            v1 = addiu(sp, 0x310);
            v1 = sltu(v1, a0);
            v1 = v1 ^ 0x1;
            v1 = v1 ^ 0x1;
            if (v1 == 0) {
                goto L_00460428_119;
            }
            backedge(ctx);
        }
    }
    // 0x0046066c
    charge(ctx, 1);
    ld(ra, sp, 0xA0);
    // 0x00460670 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x620);
    return;
L_00460428_119:
    charge(ctx, 2);
    ld(ra, sp, 0xA0);
    // 0x00460670 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x620);
}


// sub_4606B0 [collWorldBoxIntersections] -- the box test of RpCollisionWorldForAllIntersections: every triangle that overlaps the box
// ($a0 = the world, $a1 = the intersection (rw6::isect box: maximum, minimum), $a2 = the callback, $a3 = the data)
// The BSP walked with an explicit stack: a plane keeps the side(s) the box reaches; a sector's collision block is
// skipped unless its box overlaps; then its tree is walked with the box's six inside / outside bits per child (a
// subtree entirely inside the box takes its whole triangle range untested); each candidate gets the box / triangle
// test (sub_4BB5D0); a hit fills the collision triangle (unit normal, first vertex, index, vertex pointers) and calls
// the callback with the distance 0 in $f12 (0 stops).
// 0x004606B0 sub_4606B0 -- 2052 bytes; frame 0x3A0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4606B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f12{ctx, 12};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004606b0: the box and the BSP stack with the root
    enter(ctx, 37);  // entry check point + this block's cycles
    sp = addiu(sp, -0x3A0);
    sd(ra, sp, 0x90);
    v1 = addiu(sp, 0x298);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = addiu(sp, 0x39C);
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lwc1(f3, a1, 0);
    sw(a3, sp, 0xF8);
    lwc1(f2, a1, 4);
    a3 = addiu(sp, 0x29C);
    lwc1(f1, a1, 8);
    v1 = sltu(v1, a3);
    lwc1(f0, a1, 12);
    sw(a2, sp, 0xFC);
    v1 = v1 ^ 0x1;
    a2 = v1 ^ 0x1;
    v1 = addiu(sp, 0x298);
    swc1(f3, sp, 0x280);
    swc1(f2, sp, 0x284);
    swc1(f1, sp, 0x288);
    swc1(f0, sp, 0x28C);
    lwc1(f1, a1, 16);
    lwc1(f0, a1, 20);
    swc1(f1, sp, 0x290);
    swc1(f0, sp, 0x294);
    lw(a0, a0, 28);
    sw(a0, v1, 0);
    sw(a3, s5, 0);
    if (a2 != 0) {
        // 0x00460744
        charge(ctx, 1);
        s0 = addiu(sp, 0x274);
        for (;;) {
            // 0x00460748: pop a node
            charge(ctx, 7);
            lw(v1, s5, 0);
            a0 = addiu(v1, -4);
            sw(a0, s5, 0);
            lw(s3, v1, -4);
            lw(v1, s3, 0);
            if (i64(v1) >= 0) {
                for (;;) {
                    // 0x00460764: a plane: the side(s) the box reaches (the far side pushed)
                    charge(ctx, 7);
                    lw(v1, s3, 0);
                    lwc1(f0, s3, 20);
                    v1 = addu(v1, sp);
                    lwc1(f1, v1, 640);
                    c_le_s(f0, f1);
                    if (cond(ctx)) {
                        // 0x00460790
                        charge(ctx, 10);
                        lw(v1, s3, 12);
                        sw(v1, a0, 0);
                        lw(a0, s3, 0);
                        v1 = addiu(sp, 0x28C);
                        lwc1(f0, s3, 16);
                        v1 = addu(v1, a0);
                        lwc1(f1, v1, 0);
                        c_lt_s(f0, f1);
                        if (!cond(ctx)) {
                            // 0x004607b8
                            charge(ctx, 6);
                            lw(v1, s5, 0);
                            v1 = addiu(v1, 4);
                            sw(v1, s5, 0);
                            lw(a0, s3, 8);
                            lw(v1, s5, 0);
                            sw(a0, v1, 0);
                        }
                    } else {
                        // 0x00460780
                        charge(ctx, 3);
                        lw(v1, s3, 8);
                        sw(v1, a0, 0);
                    }
                    // 0x004607d0
                    charge(ctx, 5);
                    lw(a0, s5, 0);
                    lw(s3, a0, 0);
                    lw(v1, s3, 0);
                    if (i64(v1) < 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004607e4
                charge(ctx, 1);
            }
            // 0x004607e8: a sector: its collision block (none: skipped)
            charge(ctx, 5);
            lw(v1, gp, -17860);  // 0x7CE72C (the collision sector extension offset)
            v1 = addu(s3, v1);
            lw(s2, v1, 0);
            if (s2 != 0) {
                // 0x004607fc: skip the block unless its box overlaps the query box
                charge(ctx, 8);
                lw(v1, s3, 4);
                lwc1(f1, s2, coll::kBoxInf);
                lwc1(f0, s4, 0);
                sq(v1, sp, 0xD0);
                lw(v1, s3, 8);
                c_le_s(f1, f0);
                sq(v1, sp, 0xC0);
                if (cond(ctx)) {
                    // 0x0046081c
                    charge(ctx, 5);
                    lwc1(f1, s2, 20);
                    lwc1(f0, s4, 4);
                    c_le_s(f1, f0);
                    if (!cond(ctx)) {
                        goto L_00460d98;
                    }
                    // 0x00460830
                    charge(ctx, 5);
                    lwc1(f1, s2, 24);
                    lwc1(f0, s4, 8);
                    c_le_s(f1, f0);
                    if (!cond(ctx)) {
                        goto L_00460d98;
                    }
                    // 0x00460844
                    charge(ctx, 5);
                    lwc1(f1, s2, coll::kBoxSup);
                    lwc1(f0, s4, 12);
                    c_lt_s(f1, f0);
                    if (cond(ctx)) {
                        goto L_00460d98;
                    }
                    // 0x00460858
                    charge(ctx, 5);
                    lwc1(f1, s2, 8);
                    lwc1(f0, s4, 16);
                    c_lt_s(f1, f0);
                    if (cond(ctx)) {
                        goto L_00460d98;
                    }
                    // 0x0046086c
                    charge(ctx, 5);
                    lwc1(f1, s2, 12);
                    lwc1(f0, s4, 20);
                    c_lt_s(f1, f0);
                    if (cond(ctx)) {
                        goto L_00460d98;
                    }
                    // 0x00460880: the collision tree's root entry
                    charge(ctx, 9);
                    a0 = 255;
                    v1 = addiu(sp, 0x165);
                    sb(a0, v1, 0);
                    v1 = addiu(sp, 0x166);
                    sw(s2, sp, 0x130);
                    sh(zero, v1, 0);
                    lhu(v1, s2, coll::kNumSplits);
                    if (v1 == 0) {
                        // 0x00460d88
                        charge(ctx, 4);
                        lhu(a0, s2, coll::kNumTriangles);
                        v1 = addiu(sp, 0x165);
                        sb(a0, v1, 0);
                        backedge(ctx);
                    }
                    // 0x004608a4: the six bits: which faces of the block's box the query box crosses
                    charge(ctx, 35);
                    lwc1(f3, s4, 0);
                    v1 = addiu(sp, 0x134);
                    lwc1(f2, s4, 4);
                    a0 = addiu(sp, 0x164);
                    lwc1(f1, s4, 8);
                    lwc1(f0, s4, 12);
                    swc1(f3, v1, 0);
                    swc1(f2, v1, 4);
                    swc1(f1, v1, 8);
                    swc1(f0, v1, 12);
                    lwc1(f1, s4, 16);
                    lwc1(f0, s4, 20);
                    swc1(f1, v1, 16);
                    swc1(f0, v1, 20);
                    lwc1(f3, s4, 0);
                    v1 = addiu(sp, 0x14C);
                    lwc1(f2, s4, 4);
                    lwc1(f1, s4, 8);
                    lwc1(f0, s4, 12);
                    swc1(f3, v1, 0);
                    swc1(f2, v1, 4);
                    swc1(f1, v1, 8);
                    swc1(f0, v1, 12);
                    lwc1(f1, s4, 16);
                    lwc1(f0, s4, 20);
                    swc1(f1, v1, 16);
                    v1 = addiu(sp, 0x16C);
                    sw(a0, v1, 0);
                    v1 = addiu(sp, 0x14C);
                    swc1(f0, v1, 20);
                    lwc1(f1, s2, 20);
                    lwc1(f0, s4, 16);
                    c_lt_s(f1, f0);
                    if (!cond(ctx)) {
                        // 0x00460938
                        charge(ctx, 1);
                        a0 = 0;
                    } else {
                        // 0x00460930
                        charge(ctx, 2);
                        a0 = 4;
                    }
                    // 0x0046093c
                    charge(ctx, 5);
                    lwc1(f1, s2, coll::kBoxInf);
                    lwc1(f0, s4, 12);
                    c_lt_s(f1, f0);
                    v1 = 1;
                    if (!cond(ctx)) {
                        // 0x00460950
                        charge(ctx, 1);
                        v1 = 0;
                    }
                    // 0x00460954
                    charge(ctx, 5);
                    lwc1(f1, s2, 24);
                    lwc1(f0, s4, 20);
                    c_lt_s(f1, f0);
                    if (!cond(ctx)) {
                        // 0x00460970
                        charge(ctx, 1);
                        t0 = 0;
                    } else {
                        // 0x00460968
                        charge(ctx, 2);
                        t0 = 16;
                    }
                    // 0x00460974
                    charge(ctx, 5);
                    lwc1(f1, s2, coll::kBoxSup);
                    lwc1(f0, s4, 0);
                    c_le_s(f1, f0);
                    if (cond(ctx)) {
                        // 0x00460990
                        charge(ctx, 1);
                        a3 = 0;
                    } else {
                        // 0x00460988
                        charge(ctx, 2);
                        a3 = 2;
                    }
                    // 0x00460994
                    charge(ctx, 5);
                    lwc1(f1, s2, 8);
                    lwc1(f0, s4, 4);
                    c_le_s(f1, f0);
                    if (cond(ctx)) {
                        // 0x004609b0
                        charge(ctx, 1);
                        a2 = 0;
                    } else {
                        // 0x004609a8
                        charge(ctx, 2);
                        a2 = 8;
                    }
                    // 0x004609b4
                    charge(ctx, 5);
                    lwc1(f1, s2, 12);
                    lwc1(f0, s4, 8);
                    c_le_s(f1, f0);
                    if (cond(ctx)) {
                        // 0x004609d0
                        charge(ctx, 1);
                        a1 = 0;
                    } else {
                        // 0x004609c8
                        charge(ctx, 2);
                        a1 = 32;
                    }
                    // 0x004609d4
                    charge(ctx, 9);
                    a0 = v1 | a0;
                    v1 = addiu(sp, 0x174);
                    sw(v1, s0, 0);
                    v1 = t0 | a0;
                    v1 = a3 | v1;
                    v1 = a2 | v1;
                    a0 = a1 | v1;
                    v1 = addiu(sp, 0x170);
                    sw(a0, v1, 0);
                    goto L_004609f8;
                }
            L_00460d98:
                charge(ctx, 3);
                v1 = addiu(sp, 0x16C);
                sw(v1, s0, 0);
                backedge(ctx);
            L_004609f8:
                charge(ctx, 7);
                lw(a0, s0, 0);
                v1 = addiu(sp, 0x16C);
                v1 = sltu(v1, a0);
                v1 = v1 ^ 0x1;
                v1 = v1 ^ 0x1;
                if (v1 == 0) {
                    goto L_00460d64;
                }
                for (;;) {
                    // 0x00460a14: pop a child entry; descend the splits the box reaches
                    charge(ctx, 6);
                    lw(v1, s0, 0);
                    t2 = 2;
                    a2 = 255;
                    v1 = addiu(v1, -8);
                    sw(v1, s0, 0);
                    v1 = 1;
                    for (;;) {
                        // 0x00460a2c
                        charge(ctx, 5);
                        lw(a3, s0, 0);
                        lw(a1, a3, 0);
                        lbu(a0, a1, 1);
                        if (a0 != a2) {
                            break;
                        }
                        // 0x00460a54
                        charge(ctx, 3);
                        lw(a0, a3, 4);
                        if (a0 == 0) {
                            goto L_00460da4;
                        }
                        // 0x00460a60
                        charge(ctx, 14);
                        lw(a0, sp, 0x130);
                        t0 = addiu(sp, 0x134);
                        lhu(a1, a1, 2);
                        lw(a0, a0, 32);
                        a1 = sll(a1, 4);
                        a1 = addu(a0, a1);
                        lbu(a0, a1, 0);
                        lwc1(f1, a1, 12);
                        a0 = a0 & 0xC;
                        t0 = addu(t0, a0);
                        lwc1(f0, t0, 0);
                        c_le_s(f1, f0);
                        if (cond(ctx)) {
                            // 0x00460aa0
                            charge(ctx, 9);
                            t0 = addiu(a1, 8);
                            sw(t0, a3, 0);
                            a3 = addiu(sp, 0x140);
                            a3 = addu(a3, a0);
                            lwc1(f0, a3, 0);
                            lwc1(f1, a1, 4);
                            c_lt_s(f1, f0);
                            if (cond(ctx)) {
                                backedge(ctx);
                            } else {
                                // 0x00460ac4
                                charge(ctx, 14);
                                lw(t1, s0, 0);
                                a3 = addiu(sp, 0x14C);
                                a3 = addu(a3, a0);
                                t0 = addiu(t1, 8);
                                sw(t0, s0, 0);
                                sw(a1, t1, 8);
                                lw(t1, s0, 0);
                                lw(t0, t1, -4);
                                sw(t0, t1, 4);
                                lwc1(f0, a3, 0);
                                lwc1(f1, a1, 4);
                                c_le_s(f1, f0);
                                if (cond(ctx)) {
                                    // 0x00460e3c
                                    charge(ctx, 8);
                                    lw(t0, s0, 0);
                                    a3 = srl(a0, 1);
                                    a3 = sllv(t2, a3);
                                    t1 = nor(a3, 0);
                                    lw(a3, t0, 4);
                                    a3 = a3 & t1;
                                    sw(a3, t0, 4);
                                    backedge(ctx);
                                } else {
                                    // 0x00460afc
                                    charge(ctx, 1);
                                }
                                // 0x00460b00
                                charge(ctx, 7);
                                a3 = addiu(sp, 0x158);
                                a3 = addu(a3, a0);
                                lwc1(f1, a1, 12);
                                lwc1(f0, a3, 0);
                                c_lt_s(f1, f0);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                } else {
                                    // 0x00460b1c
                                    charge(ctx, 8);
                                    lw(a1, s0, 0);
                                    a0 = srl(a0, 1);
                                    a0 = sllv(v1, a0);
                                    a3 = nor(a0, 0);
                                    lw(a0, a1, -4);
                                    a0 = a0 & a3;
                                    sw(a0, a1, -4);
                                    backedge(ctx);
                                }
                            }
                        } else {
                            // 0x00460a98
                            charge(ctx, 2);
                            sw(a1, a3, 0);
                            backedge(ctx);
                        }
                    }
                    // 0x00460a40: a leaf: its triangles [first, first + count)
                    charge(ctx, 5);
                    lw(v1, a3, 4);
                    a0 = a0 & 0xFFFF;
                    lhu(a1, a1, 2);
                    sw(v1, sp, 0xE0);
                L_00460b40:
                    charge(ctx, 6);
                    s1 = a1 & 0xFFFF;
                    v1 = a0 & 0xFFFF;
                    s7 = addu(s1, v1);
                    at = slt(s1, s7);
                    if (at != 0) {
                        for (;;) {
                            // 0x00460b58: each triangle (through the triangle map when there is one)
                            charge(ctx, 3);
                            lw(v1, s2, coll::kTriMap);
                            if (v1 == 0) {
                                // 0x00460b78
                                charge(ctx, 1);
                                v0 = s1;
                            } else {
                                // 0x00460b64
                                charge(ctx, 5);
                                v0 = s1 & 0xFFFF;
                                v0 = sll(v0, 1);
                                v0 = addu(v1, v0);
                                lhu(v0, v0, 0);
                            }
                            // 0x00460b7c
                            charge(ctx, 26);
                            v0 = v0 & 0xFFFF;
                            sq(v0, sp, 0xB0);
                            v1 = sll(v0, 3);
                            lq(v0, sp, 0xD0);
                            v0 = addu(v0, v1);
                            lhu(a1, v0, 0);
                            lhu(a0, v0, 2);
                            lhu(v1, v0, 4);
                            v0 = sll(a1, 1);
                            a1 = addu(v0, a1);
                            v0 = sll(a0, 1);
                            a1 = sll(a1, 2);
                            a0 = addu(v0, a0);
                            lq(v0, sp, 0xC0);
                            a0 = sll(a0, 2);
                            s6 = addu(v0, a1);
                            fp = addu(v0, a0);
                            v0 = sll(v1, 1);
                            v0 = addu(v0, v1);
                            v1 = sll(v0, 2);
                            lq(v0, sp, 0xC0);
                            v0 = addu(v0, v1);
                            sq(v0, sp, 0xA0);
                            lw(v0, sp, 0xE0);
                            if (v0 == 0) {
                                // 0x00460be4
                                charge(ctx, 1);
                                lwc1(f3, s6, 0);
                                goto L_00460be8;
                            }
                            // 0x00460e60: the box / triangle test (sub_4BB5D0)
                            charge(ctx, 7);
                            lq(a3, sp, 0xA0);
                            a0 = s4;
                            a1 = s6;
                            a2 = fp;
                            jal(ctx, 0x460E6Cu, gen::fn_sub_4BB5D0_004bb5d0);
                            if (v0 == 0) {
                                backedge(ctx);
                            L_00460d34:
                                charge(ctx, 5);
                                v1 = addiu(s1, 1);
                                s1 = v1 & 0xFFFF;
                                v1 = slt(s1, s7);
                                if (v1 == 0) {
                                    goto L_00460d48;
                                }
                                backedge(ctx);
                                continue;
                            }
                            // 0x00460e7c: a hit: the collision triangle; the normal normalised
                            charge(ctx, 2);
                            lwc1(f3, s6, 0);
                            backedge(ctx);
                        L_00460be8:
                            charge(ctx, 54);
                            lq(v1, sp, 0xB0);
                            lwc1(f1, s6, 4);
                            v0 = addiu(sp, 0x118);
                            lwc1(f0, s6, 8);
                            mtc1(zero, f2);
                            sw(v1, v0, 0);
                            v0 = addiu(sp, 0x10C);
                            lq(v1, sp, 0xA0);
                            swc1(f3, v0, 0);
                            swc1(f1, v0, 4);
                            v0 = addiu(sp, 0x11C);
                            sw(s6, v0, 0);
                            v0 = addiu(sp, 0x10C);
                            swc1(f0, v0, 8);
                            v0 = addiu(sp, 0x120);
                            sw(fp, v0, 0);
                            v0 = addiu(sp, 0x124);
                            sw(v1, v0, 0);
                            paddub(v0, v1, zero);
                            lwc1(f6, s6, 0);
                            lwc1(f5, fp, 0x0);
                            lwc1(f0, v0, 0);
                            lwc1(f3, s6, 8);
                            lwc1(f1, fp, 0x8);
                            lwc1(f8, s6, 4);
                            lwc1(f4, fp, 0x4);
                            sub_s(f9, f5, f6);
                            sub_s(f5, f0, f6);
                            sub_s(f6, f1, f3);
                            lwc1(f0, v0, 8);
                            lwc1(f1, v0, 4);
                            sub_s(f7, f4, f8);
                            sub_s(f0, f0, f3);
                            v0 = addiu(sp, 0x104);
                            sub_s(f4, f1, f8);
                            mula_s(f7, f0);
                            msub_s(f3, f6, f4);
                            mula_s(f6, f5);
                            msub_s(f1, f9, f0);
                            mula_s(f9, f4);
                            msub_s(f0, f7, f5);
                            swc1(f1, v0, 0);
                            mula_s(f1, f1);
                            v0 = addiu(sp, 0x108);
                            madda_s(f3, f3);
                            swc1(f0, v0, 0);
                            swc1(f3, sp, 0x100);
                            madd_s(f0, f0, f0);
                            sqrt_s(f3, f0);
                            c_le_s(f3, f2);
                            if (!cond(ctx)) {
                                // 0x00460cc0
                                charge(ctx, 7);
                                v0 = 0x3F800000;
                                mtc1(v0, f0);
                                div_s(f3, f0, f3);
                            }
                            // 0x00460cdc: the callback (a0 = the intersection, a1 = the sector, a2 = the collision triangle, $f12 = the distance, a3 = the data); 0 ends the walk
                            charge(ctx, 22);
                            v0 = addiu(sp, 0x104);
                            lw(a3, sp, 0xF8);
                            lwc1(f1, v0, 0);
                            a0 = s4;
                            lwc1(f2, sp, 0x100);
                            a1 = s3;
                            mtc1(zero, f12);
                            a2 = addiu(sp, 0x100);
                            v0 = addiu(sp, 0x108);
                            lwc1(f0, v0, 0);
                            mul_s(f2, f2, f3);
                            mul_s(f1, f1, f3);
                            v0 = addiu(sp, 0x104);
                            swc1(f1, v0, 0);
                            mul_s(f0, f0, f3);
                            v0 = addiu(sp, 0x108);
                            swc1(f0, v0, 0);
                            lw(v0, sp, 0xFC);
                            jt = v0.u();  // the target, read before the delay slot
                            link(ctx, 0x460D24u);  // $ra = the return address
                            swc1(f2, sp, 0x100);
                            call_ptr(ctx, jt);
                            if (v0 == 0) {
                                break;
                            }
                            goto L_00460d34;
                        }
                        break;
                    }
                L_00460d48:
                    charge(ctx, 7);
                    lw(a0, s0, 0);
                    v1 = addiu(sp, 0x16C);
                    v1 = sltu(v1, a0);
                    v1 = v1 ^ 0x1;
                    v1 = v1 ^ 0x1;
                    if (v1 == 0) {
                        goto L_00460d64;
                    }
                    backedge(ctx);
                }
                break;
            }
        L_00460d64:
            charge(ctx, 7);
            lw(a0, s5, 0);
            v1 = addiu(sp, 0x298);
            v1 = sltu(v1, a0);
            v1 = v1 ^ 0x1;
            v1 = v1 ^ 0x1;
            if (v1 == 0) {
                goto L_00460d80_59;
            }
            backedge(ctx);
        }
    }
    // 0x00460e84
    charge(ctx, 1);
    ld(ra, sp, 0x90);
    // 0x00460e88 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x3A0);
    return;
L_00460d80_59:
    charge(ctx, 2);
    ld(ra, sp, 0x90);
    // 0x00460e88 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x3A0);
    return;
L_00460da4:
    charge(ctx, 8);
    lw(t0, sp, 0x130);
    lhu(v1, a1, 2);
    lw(a3, t0, 32);
    v1 = sll(v1, 4);
    a1 = addu(a3, v1);
    lbu(v1, a1, 1);
    t1 = a1;
    if (v1 == a2) {
        // 0x00460dc4: a subtree inside the box: its whole triangle range (the leftmost to the rightmost leaf), untested
        charge(ctx, 1);
        v1 = 255;
        for (;;) {
            // 0x00460dc8
            charge(ctx, 7);
            lhu(a0, t1, 2);
            a0 = sll(a0, 4);
            t1 = addu(a3, a0);
            lbu(a0, t1, 1);
            if (a0 != v1) {
                break;
            }
            backedge(ctx);
        }
        // 0x00460de4
        charge(ctx, 1);
    }
    // 0x00460de8
    charge(ctx, 5);
    lbu(a2, a1, 9);
    a3 = addiu(a1, 8);
    a1 = 255;
    if (a2 == a1) {
        // 0x00460dfc
        charge(ctx, 1);
        lw(a0, t0, 32);
        for (;;) {
            // 0x00460e00
            charge(ctx, 7);
            lhu(v1, a3, 2);
            v1 = sll(v1, 4);
            v1 = addu(a0, v1);
            lbu(a2, v1, 9);
            a3 = addiu(v1, 8);
            if (a2 != a1) {
                break;
            }
            backedge(ctx);
        }
        // 0x00460e1c
        charge(ctx, 1);
    }
    // 0x00460e20
    charge(ctx, 7);
    lhu(v1, a3, 2);
    lhu(a1, t1, 2);
    sw(zero, sp, 0xE0);
    v1 = addu(v1, a2);
    v1 = subu(v1, a1);
    a0 = v1 & 0xFFFF;
    backedge(ctx);
    goto L_00460b40;
}


// sub_460EC0 [collWorldSphereIntersections] -- the sphere test of RpCollisionWorldForAllIntersections: every triangle within the sphere
// ($a0 = the world, $a1 = the sphere (centre, radius), $a2 = the intersection, $a3 = the callback, $t0 = the data;
// the atomic case passes the atomic's world bounding sphere) The sphere's box down the BSP (explicit stack); a
// sector's collision block is skipped when the centre's squared distance to its box exceeds r^2; then its tree is
// walked with the sphere box's six inside / outside bits per child: a subtree whose box lies inside the sphere's box
// takes its whole triangle range with the plane distance as the distance; other leaf triangles get the sphere /
// triangle test (sub_4BAE00). A hit: the collision triangle (unit normal, first vertex, index, vertex pointers) and
// the callback with the distance / radius in $f12 (0 stops).
// 0x00460EC0 sub_460EC0 -- 2616 bytes; frame 0x410: ra sp+0xC0, fp sp+0xB0 (sq), s7 sp+0xA0 (sq), s6 sp+0x90 (sq), s5 sp+0x80 (sq), s4 sp+0x70 (sq), s3 sp+0x60 (sq), s2 sp+0x50 (sq), s1 sp+0x40 (sq), s0 sp+0x30 (sq), f30 sp+0x28, f29 sp+0x24, f28 sp+0x20, f27 sp+0x1C, f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0, f26 sp+0x2C0, f25 sp+0x2C4, f29 sp+0x2B4, f28 sp+0x2B8
void sub_460EC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26}, f27{ctx, 27}, f28{ctx, 28}, f29{ctx, 29}, f30{ctx, 30};
    // 0x00460ec0: the sphere's box (centre +- radius), 1 / radius, the BSP stack with the root
    enter(ctx, 105);  // entry check point + this block's cycles
    sp = addiu(sp, -0x410);
    v1 = 0x3F800000;
    sd(ra, sp, 0xC0);
    lwc1(f1, a1, 4);
    sq(fp, sp, 0xB0);
    lwc1(f0, a1, 8);
    sq(s7, sp, 0xA0);
    t3 = addiu(sp, 0x3DC);
    sq(s6, sp, 0x90);
    mtc1(v1, f4);
    sq(s5, sp, 0x80);
    lwc1(f5, a1, 12);
    sq(s4, sp, 0x70);
    v1 = 0x3F110000;
    sq(s3, sp, 0x60);
    v1 = v1 | 0xEB85;
    sq(s2, sp, 0x50);
    mtc1(v1, f2);
    sq(s1, sp, 0x40);
    lwc1(f3, a1, 0);
    sq(s0, sp, 0x30);
    t6 = addiu(sp, 0x404);
    swc1(f30, sp, 0x28);
    s0 = addiu(sp, 0x3FC);
    div_s(f30, f4, f5);
    sw(a2, sp, 0x12C);
    sw(a3, sp, 0x128);
    t4 = addiu(sp, 0x3F8);
    sw(t0, sp, 0x124);
    t7 = addiu(sp, 0x400);
    t5 = addiu(sp, 0x3F4);
    a2 = addiu(sp, 0x2CC);
    v1 = addiu(sp, 0x2C8);
    t2 = addiu(sp, 0x3E0);
    v1 = sltu(v1, a2);
    t1 = addiu(sp, 0x3E4);
    t0 = addiu(sp, 0x3D4);
    a3 = addiu(sp, 0x3D8);
    s6 = a1;
    v1 = v1 ^ 0x1;
    a1 = v1 ^ 0x1;
    s5 = addiu(sp, 0x3CC);
    v1 = addiu(sp, 0x2BC);
    swc1(f29, sp, 0x24);
    swc1(f28, sp, 0x20);
    swc1(f27, sp, 0x1C);
    swc1(f26, sp, 0x18);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    mul_s(f4, f2, f5);
    swc1(f1, s0, 4);
    lwc1(f2, t7, 0);
    sub_s(f27, f3, f5);
    swc1(f20, sp, 0x0);
    sub_s(f26, f2, f5);
    swc1(f0, t3, 8);
    sub_s(f22, f3, f4);
    lwc1(f2, t1, 0);
    swc1(f27, v1, 0);
    swc1(f1, sp, 0x3F4);
    v1 = addiu(sp, 0x2C8);
    swc1(f0, sp, 0x3F8);
    swc1(f1, sp, 0x3D4);
    swc1(f0, sp, 0x3D8);
    swc1(f0, s0, 8);
    add_s(f0, f3, f5);
    swc1(f1, t3, 4);
    lwc1(f1, t6, 0);
    sub_s(f20, f2, f4);
    swc1(f0, sp, 0x3F0);
    sub_s(f25, f1, f5);
    swc1(f0, sp, 0x2B0);
    lwc1(f0, t4, 0);
    lwc1(f1, t5, 0);
    swc1(f26, sp, 0x2C0);
    swc1(f25, sp, 0x2C4);
    swc1(f27, s0, 0);
    swc1(f26, t7, 0);
    add_s(f28, f0, f5);
    add_s(f29, f1, f5);
    add_s(f0, f3, f4);
    swc1(f0, sp, 0x3D0);
    lwc1(f3, t2, 0);
    lwc1(f1, t0, 0);
    lwc1(f0, a3, 0);
    swc1(f29, sp, 0x2B4);
    swc1(f28, sp, 0x2B8);
    lw(a0, a0, 28);
    swc1(f25, t6, 0);
    sub_s(f21, f3, f4);
    add_s(f24, f1, f4);
    sw(a0, v1, 0);
    sw(a2, s5, 0);
    add_s(f23, f0, f4);
    swc1(f22, t3, 0);
    swc1(f29, t5, 0);
    swc1(f28, t4, 0);
    swc1(f21, t2, 0);
    swc1(f20, t1, 0);
    swc1(f24, t0, 0);
    swc1(f23, a3, 0);
    if (a1 != 0) {
        // 0x00461064
        charge(ctx, 1);
        s1 = addiu(sp, 0x2A4);
        for (;;) {
            // 0x00461068: pop a node
            charge(ctx, 7);
            lw(v1, s5, 0);
            a0 = addiu(v1, -4);
            sw(a0, s5, 0);
            lw(s4, v1, -4);
            lw(v1, s4, 0);
            if (i64(v1) >= 0) {
                for (;;) {
                    // 0x00461084: a plane: the side(s) the sphere's box reaches (the far side pushed)
                    charge(ctx, 7);
                    lw(v1, s4, 0);
                    lwc1(f0, s4, 20);
                    v1 = addu(v1, sp);
                    lwc1(f1, v1, 688);
                    c_le_s(f0, f1);
                    if (cond(ctx)) {
                        // 0x004610b0
                        charge(ctx, 10);
                        lw(v1, s4, 12);
                        sw(v1, a0, 0);
                        lw(a0, s4, 0);
                        v1 = addiu(sp, 0x2BC);
                        lwc1(f0, s4, 16);
                        v1 = addu(v1, a0);
                        lwc1(f1, v1, 0);
                        c_lt_s(f0, f1);
                        if (!cond(ctx)) {
                            // 0x004610d8
                            charge(ctx, 6);
                            lw(v1, s5, 0);
                            v1 = addiu(v1, 4);
                            sw(v1, s5, 0);
                            lw(a0, s4, 8);
                            lw(v1, s5, 0);
                            sw(a0, v1, 0);
                        }
                    } else {
                        // 0x004610a0
                        charge(ctx, 3);
                        lw(v1, s4, 8);
                        sw(v1, a0, 0);
                    }
                    // 0x004610f0
                    charge(ctx, 5);
                    lw(a0, s5, 0);
                    lw(s4, a0, 0);
                    lw(v1, s4, 0);
                    if (i64(v1) < 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00461104
                charge(ctx, 1);
            }
            // 0x00461108: a sector: its collision block (none: skipped)
            charge(ctx, 5);
            lw(v1, gp, -17860);  // 0x7CE72C (the collision sector extension offset)
            v1 = addu(s4, v1);
            lw(s3, v1, 0);
            if (s3 != 0) {
                // 0x0046111c: the squared distance from the centre to the block's box
                charge(ctx, 5);
                lwc1(f4, s3, coll::kBoxInf);
                lwc1(f1, s6, 0);
                c_lt_s(f1, f4);
                if (!cond(ctx)) {
                    // 0x00461138
                    charge(ctx, 4);
                    lwc1(f0, s3, coll::kBoxSup);
                    c_le_s(f1, f0);
                    if (cond(ctx)) {
                        // 0x00461150
                        charge(ctx, 1);
                        mtc1(zero, f0);
                    } else {
                        // 0x00461148
                        charge(ctx, 2);
                        sub_s(f0, f1, f0);
                    }
                } else {
                    // 0x00461130
                    charge(ctx, 2);
                    sub_s(f0, f4, f1);
                }
                // 0x00461154
                charge(ctx, 5);
                lwc1(f3, s3, 20);
                lwc1(f1, s6, 4);
                c_lt_s(f1, f3);
                mul_s(f6, f0, f0);
                if (!cond(ctx)) {
                    // 0x00461170
                    charge(ctx, 4);
                    lwc1(f0, s3, 8);
                    c_le_s(f1, f0);
                    if (cond(ctx)) {
                        // 0x00461188
                        charge(ctx, 1);
                        mtc1(zero, f0);
                    } else {
                        // 0x00461180
                        charge(ctx, 2);
                        sub_s(f0, f1, f0);
                    }
                } else {
                    // 0x00461168
                    charge(ctx, 2);
                    sub_s(f0, f3, f1);
                }
                // 0x0046118c
                charge(ctx, 8);
                lwc1(f2, s3, 24);
                lwc1(f1, s6, 8);
                mtc1(zero, f5);
                adda_s(f5, f6);
                c_lt_s(f1, f2);
                madd_s(f6, f0, f0);
                if (!cond(ctx)) {
                    // 0x004611b4
                    charge(ctx, 4);
                    lwc1(f0, s3, 12);
                    c_le_s(f1, f0);
                    if (!cond(ctx)) {
                        // 0x004611c4
                        charge(ctx, 2);
                        sub_s(f5, f1, f0);
                    }
                } else {
                    // 0x004611ac
                    charge(ctx, 2);
                    sub_s(f5, f2, f1);
                }
                // 0x004611cc
                charge(ctx, 9);
                lwc1(f0, s6, 12);
                mtc1(zero, f1);
                adda_s(f1, f6);
                madd_s(f1, f5, f5);
                mul_s(f0, f0, f0);
                c_le_s(f1, f0);
                if (!cond(ctx)) {
                    goto L_00461778;
                }
                // 0x004611f0: within the radius: the sector's triangles / vertices; is the block's box inside the sphere's box
                charge(ctx, 7);
                lw(v1, s4, 4);
                lwc1(f0, sp, 0x3F0);
                sq(v1, sp, 0x100);
                c_le_s(f4, f0);
                lw(v1, s4, 8);
                sq(v1, sp, 0xF0);
                if (cond(ctx)) {
                    // 0x0046120c
                    charge(ctx, 3);
                    c_le_s(f3, f29);
                    if (!cond(ctx)) {
                        goto L_004617ac;
                    }
                    // 0x00461218
                    charge(ctx, 3);
                    c_le_s(f2, f28);
                    if (!cond(ctx)) {
                        goto L_004617ac;
                    }
                    // 0x00461224
                    charge(ctx, 4);
                    lwc1(f0, s3, coll::kBoxSup);
                    c_lt_s(f0, f27);
                    if (cond(ctx)) {
                        goto L_004617ac;
                    }
                    // 0x00461234
                    charge(ctx, 4);
                    lwc1(f0, s3, 8);
                    c_lt_s(f0, f26);
                    if (cond(ctx)) {
                        goto L_004617ac;
                    }
                    // 0x00461244
                    charge(ctx, 4);
                    lwc1(f0, s3, 12);
                    c_lt_s(f0, f25);
                    if (cond(ctx)) {
                        goto L_004617ac;
                    }
                    // 0x00461254: the collision tree's root entry
                    charge(ctx, 9);
                    a0 = 255;
                    v1 = addiu(sp, 0x195);
                    sb(a0, v1, 0);
                    v1 = addiu(sp, 0x196);
                    sw(s3, sp, 0x160);
                    sh(zero, v1, 0);
                    lhu(v1, s3, coll::kNumSplits);
                    if (v1 == 0) {
                        // 0x0046179c
                        charge(ctx, 4);
                        lhu(a0, s3, coll::kNumTriangles);
                        v1 = addiu(sp, 0x195);
                        sb(a0, v1, 0);
                        backedge(ctx);
                    }
                    // 0x00461278: the six bits: which faces of the block's box the sphere's box crosses
                    charge(ctx, 33);
                    v1 = addiu(sp, 0x168);
                    a0 = addiu(sp, 0x194);
                    swc1(f29, v1, 0);
                    v1 = addiu(sp, 0x19C);
                    sw(a0, v1, 0);
                    lwc1(f1, sp, 0x3F0);
                    v1 = addiu(sp, 0x16C);
                    swc1(f28, v1, 0);
                    v1 = addiu(sp, 0x170);
                    swc1(f27, v1, 0);
                    v1 = addiu(sp, 0x174);
                    swc1(f26, v1, 0);
                    v1 = addiu(sp, 0x178);
                    swc1(f25, v1, 0);
                    v1 = addiu(sp, 0x180);
                    swc1(f24, v1, 0);
                    v1 = addiu(sp, 0x184);
                    swc1(f23, v1, 0);
                    v1 = addiu(sp, 0x164);
                    swc1(f1, v1, 0);
                    lwc1(f0, sp, 0x3D0);
                    v1 = addiu(sp, 0x17C);
                    swc1(f0, v1, 0);
                    v1 = addiu(sp, 0x188);
                    swc1(f22, v1, 0);
                    v1 = addiu(sp, 0x18C);
                    swc1(f21, v1, 0);
                    v1 = addiu(sp, 0x190);
                    swc1(f20, v1, 0);
                    lwc1(f0, s3, 20);
                    c_lt_s(f0, f21);
                    if (!cond(ctx)) {
                        // 0x00461304
                        charge(ctx, 1);
                        a0 = 0;
                    } else {
                        // 0x004612fc
                        charge(ctx, 2);
                        a0 = 4;
                    }
                    // 0x00461308
                    charge(ctx, 4);
                    lwc1(f0, s3, coll::kBoxInf);
                    c_lt_s(f0, f22);
                    v1 = 1;
                    if (!cond(ctx)) {
                        // 0x00461318
                        charge(ctx, 1);
                        v1 = 0;
                    }
                    // 0x0046131c
                    charge(ctx, 4);
                    lwc1(f0, s3, 24);
                    c_lt_s(f0, f20);
                    if (!cond(ctx)) {
                        // 0x00461334
                        charge(ctx, 1);
                        t0 = 0;
                    } else {
                        // 0x0046132c
                        charge(ctx, 2);
                        t0 = 16;
                    }
                    // 0x00461338
                    charge(ctx, 5);
                    lwc1(f1, s3, coll::kBoxSup);
                    lwc1(f0, sp, 0x3D0);
                    c_le_s(f1, f0);
                    if (cond(ctx)) {
                        // 0x00461354
                        charge(ctx, 1);
                        a3 = 0;
                    } else {
                        // 0x0046134c
                        charge(ctx, 2);
                        a3 = 2;
                    }
                    // 0x00461358
                    charge(ctx, 4);
                    lwc1(f0, s3, 8);
                    c_le_s(f0, f24);
                    if (cond(ctx)) {
                        // 0x00461370
                        charge(ctx, 1);
                        a2 = 0;
                    } else {
                        // 0x00461368
                        charge(ctx, 2);
                        a2 = 8;
                    }
                    // 0x00461374
                    charge(ctx, 4);
                    lwc1(f0, s3, 12);
                    c_le_s(f0, f23);
                    if (cond(ctx)) {
                        // 0x0046138c
                        charge(ctx, 1);
                        a1 = 0;
                    } else {
                        // 0x00461384
                        charge(ctx, 2);
                        a1 = 32;
                    }
                    // 0x00461390
                    charge(ctx, 9);
                    a0 = v1 | a0;
                    v1 = addiu(sp, 0x1A4);
                    sw(v1, s1, 0);
                    v1 = t0 | a0;
                    v1 = a3 | v1;
                    v1 = a2 | v1;
                    a0 = a1 | v1;
                    v1 = addiu(sp, 0x1A0);
                    sw(a0, v1, 0);
                    goto L_004613b4;
                }
            L_004617ac:
                charge(ctx, 3);
                v1 = addiu(sp, 0x19C);
                sw(v1, s1, 0);
                backedge(ctx);
            L_004613b4:
                charge(ctx, 7);
                lw(a0, s1, 0);
                v1 = addiu(sp, 0x19C);
                v1 = sltu(v1, a0);
                v1 = v1 ^ 0x1;
                v1 = v1 ^ 0x1;
                if (v1 == 0) {
                    goto L_00461778;
                }
                for (;;) {
                    // 0x004613d0: pop a child entry; descend the splits the sphere's box reaches
                    charge(ctx, 6);
                    lw(v1, s1, 0);
                    t2 = 2;
                    a2 = 255;
                    v1 = addiu(v1, -8);
                    sw(v1, s1, 0);
                    v1 = 1;
                    for (;;) {
                        // 0x004613e8
                        charge(ctx, 5);
                        lw(a3, s1, 0);
                        lw(a1, a3, 0);
                        lbu(a0, a1, 1);
                        if (a0 != a2) {
                            break;
                        }
                        // 0x00461410
                        charge(ctx, 3);
                        lw(a0, a3, 4);
                        if (a0 == 0) {
                            goto L_004617b8;
                        }
                        // 0x0046141c
                        charge(ctx, 14);
                        lw(a0, sp, 0x160);
                        t0 = addiu(sp, 0x164);
                        lhu(a1, a1, 2);
                        lw(a0, a0, 32);
                        a1 = sll(a1, 4);
                        a1 = addu(a0, a1);
                        lbu(a0, a1, 0);
                        lwc1(f1, a1, 12);
                        a0 = a0 & 0xC;
                        t0 = addu(t0, a0);
                        lwc1(f0, t0, 0);
                        c_le_s(f1, f0);
                        if (cond(ctx)) {
                            // 0x00461460
                            charge(ctx, 9);
                            t0 = addiu(a1, 8);
                            sw(t0, a3, 0);
                            a3 = addiu(sp, 0x170);
                            a3 = addu(a3, a0);
                            lwc1(f0, a3, 0);
                            lwc1(f1, a1, 4);
                            c_lt_s(f1, f0);
                            if (cond(ctx)) {
                                backedge(ctx);
                            } else {
                                // 0x00461484
                                charge(ctx, 14);
                                lw(t1, s1, 0);
                                a3 = addiu(sp, 0x17C);
                                a3 = addu(a3, a0);
                                t0 = addiu(t1, 8);
                                sw(t0, s1, 0);
                                sw(a1, t1, 8);
                                lw(t1, s1, 0);
                                lw(t0, t1, -4);
                                sw(t0, t1, 4);
                                lwc1(f0, a3, 0);
                                lwc1(f1, a1, 4);
                                c_le_s(f1, f0);
                                if (cond(ctx)) {
                                    // 0x0046184c
                                    charge(ctx, 8);
                                    lw(t0, s1, 0);
                                    a3 = srl(a0, 1);
                                    a3 = sllv(t2, a3);
                                    t1 = nor(a3, 0);
                                    lw(a3, t0, 4);
                                    a3 = a3 & t1;
                                    sw(a3, t0, 4);
                                    backedge(ctx);
                                } else {
                                    // 0x004614bc
                                    charge(ctx, 1);
                                }
                                // 0x004614c0
                                charge(ctx, 7);
                                a3 = addiu(sp, 0x188);
                                a3 = addu(a3, a0);
                                lwc1(f1, a1, 12);
                                lwc1(f0, a3, 0);
                                c_lt_s(f1, f0);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                } else {
                                    // 0x004614dc
                                    charge(ctx, 8);
                                    lw(a1, s1, 0);
                                    a0 = srl(a0, 1);
                                    a0 = sllv(v1, a0);
                                    a3 = nor(a0, 0);
                                    lw(a0, a1, -4);
                                    a0 = a0 & a3;
                                    sw(a0, a1, -4);
                                    backedge(ctx);
                                }
                            }
                        } else {
                            // 0x00461454
                            charge(ctx, 2);
                            sw(a1, a3, 0);
                            backedge(ctx);
                        }
                    }
                    // 0x004613fc: a leaf: its triangles [first, first + count)
                    charge(ctx, 5);
                    lw(v1, a3, 4);
                    a0 = a0 & 0xFFFF;
                    lhu(a1, a1, 2);
                    sw(v1, sp, 0x110);
                L_00461500:
                    charge(ctx, 6);
                    s2 = a1 & 0xFFFF;
                    v1 = a0 & 0xFFFF;
                    s7 = addu(s2, v1);
                    at = slt(s2, s7);
                    if (at != 0) {
                        for (;;) {
                            // 0x00461518: each triangle (through the triangle map when there is one)
                            charge(ctx, 3);
                            lw(v1, s3, coll::kTriMap);
                            if (v1 == 0) {
                                // 0x00461538
                                charge(ctx, 1);
                                v0 = s2;
                            } else {
                                // 0x00461524
                                charge(ctx, 5);
                                v0 = s2 & 0xFFFF;
                                v0 = sll(v0, 1);
                                v0 = addu(v1, v0);
                                lhu(v0, v0, 0);
                            }
                            // 0x0046153c
                            charge(ctx, 26);
                            v0 = v0 & 0xFFFF;
                            sq(v0, sp, 0xE0);
                            v1 = sll(v0, 3);
                            lq(v0, sp, 0x100);
                            v0 = addu(v0, v1);
                            lhu(a1, v0, 0);
                            lhu(a0, v0, 2);
                            lhu(v1, v0, 4);
                            v0 = sll(a1, 1);
                            a1 = addu(v0, a1);
                            v0 = sll(a0, 1);
                            a1 = sll(a1, 2);
                            a0 = addu(v0, a0);
                            lq(v0, sp, 0xF0);
                            a0 = sll(a0, 2);
                            s0 = addu(v0, a1);
                            fp = addu(v0, a0);
                            v0 = sll(v1, 1);
                            v0 = addu(v0, v1);
                            v1 = sll(v0, 2);
                            lq(v0, sp, 0xF0);
                            v0 = addu(v0, v1);
                            sq(v0, sp, 0xD0);
                            lw(v0, sp, 0x110);
                            if (v0 != 0) {
                                // 0x00461870: the sphere / triangle test (sub_4BAE00) -> the normal and the distance
                                charge(ctx, 9);
                                lq(a3, sp, 0xD0);
                                a0 = s6;
                                a1 = s0;
                                a2 = fp;
                                t0 = addiu(sp, 0x130);
                                t1 = addiu(sp, 0x40C);
                                jal(ctx, 0x461884u, gen::fn_sub_4BAE00_004bae00);
                                if (v0 == 0) {
                                    backedge(ctx);
                                L_00461748:
                                    charge(ctx, 5);
                                    v1 = addiu(s2, 1);
                                    s2 = v1 & 0xFFFF;
                                    v1 = slt(s2, s7);
                                    if (v1 == 0) {
                                        goto L_0046175c;
                                    }
                                    backedge(ctx);
                                    continue;
                                }
                                // 0x00461894
                                charge(ctx, 2);
                                lwc1(f0, sp, 0x40C);
                                backedge(ctx);
                            L_004616d0:
                                charge(ctx, 30);
                                lq(v1, sp, 0xE0);
                                v0 = addiu(sp, 0x148);
                                lw(a0, sp, 0x12C);
                                lw(a3, sp, 0x124);
                                a1 = s4;
                                mul_s(f0, f0, f30);
                                swc1(f0, sp, 0x40C);
                                lwc1(f2, s0, 0);
                                lwc1(f1, s0, 4);
                                lwc1(f0, s0, 8);
                                lwc1(f12, sp, 0x40C);
                                sw(v1, v0, 0);
                                v0 = addiu(sp, 0x13C);
                                lq(v1, sp, 0xD0);
                                swc1(f2, v0, 0);
                                v0 = addiu(sp, 0x14C);
                                sw(s0, v0, 0);
                                v0 = addiu(sp, 0x13C);
                                swc1(f1, v0, 4);
                                v0 = addiu(sp, 0x150);
                                sw(fp, v0, 0);
                                v0 = addiu(sp, 0x13C);
                                swc1(f0, v0, 8);
                                v0 = addiu(sp, 0x154);
                                sw(v1, v0, 0);
                                lw(v0, sp, 0x128);
                                a2 = addiu(sp, 0x130);
                                jalr(ctx, 0x461738u, v0.u());
                                if (v0 == 0) {
                                    break;
                                }
                                goto L_00461748;
                            }
                            // 0x004615a4: inside the sphere's box: the unit face normal and the plane distance directly
                            charge(ctx, 38);
                            lq(v0, sp, 0xD0);
                            lwc1(f6, s0, 0);
                            lwc1(f5, fp, 0x0);
                            lwc1(f3, s0, 8);
                            lwc1(f1, fp, 0x8);
                            lwc1(f4, s0, 4);
                            lwc1(f2, fp, 0x4);
                            lwc1(f0, v0, 0);
                            sub_s(f8, f5, f6);
                            sub_s(f7, f2, f4);
                            sub_s(f5, f0, f6);
                            sub_s(f6, f1, f3);
                            lwc1(f0, v0, 8);
                            lwc1(f1, v0, 4);
                            mtc1(zero, f2);
                            sub_s(f0, f0, f3);
                            v0 = addiu(sp, 0x134);
                            sub_s(f4, f1, f4);
                            mula_s(f7, f0);
                            msub_s(f3, f6, f4);
                            mula_s(f6, f5);
                            msub_s(f1, f8, f0);
                            mula_s(f8, f4);
                            msub_s(f0, f7, f5);
                            swc1(f1, v0, 0);
                            mula_s(f1, f1);
                            v0 = addiu(sp, 0x138);
                            madda_s(f3, f3);
                            swc1(f0, v0, 0);
                            madd_s(f0, f0, f0);
                            sqrt_s(f5, f0);
                            swc1(f3, sp, 0x130);
                            c_le_s(f5, f2);
                            if (!cond(ctx)) {
                                // 0x0046163c
                                charge(ctx, 7);
                                v0 = 0x3F800000;
                                mtc1(v0, f0);
                                div_s(f5, f0, f5);
                            }
                            // 0x00461658
                            charge(ctx, 30);
                            v0 = addiu(sp, 0x134);
                            lwc1(f1, v0, 0);
                            lwc1(f3, sp, 0x130);
                            lwc1(f2, s6, 4);
                            lwc1(f4, s6, 0);
                            lwc1(f7, s6, 8);
                            v0 = addiu(sp, 0x138);
                            lwc1(f0, v0, 0);
                            mul_s(f8, f3, f5);
                            mul_s(f1, f1, f5);
                            v0 = addiu(sp, 0x134);
                            swc1(f1, v0, 0);
                            mul_s(f0, f0, f5);
                            v0 = addiu(sp, 0x138);
                            swc1(f0, v0, 0);
                            swc1(f8, sp, 0x130);
                            lwc1(f5, v0, 0);
                            lwc1(f1, s0, 4);
                            lwc1(f3, s0, 0);
                            lwc1(f6, s0, 8);
                            v0 = addiu(sp, 0x134);
                            lwc1(f0, v0, 0);
                            sub_s(f1, f2, f1);
                            sub_s(f3, f4, f3);
                            mula_s(f1, f0);
                            sub_s(f6, f7, f6);
                            madda_s(f3, f8);
                            madd_s(f0, f6, f5);
                            swc1(f0, sp, 0x40C);
                            lwc1(f0, sp, 0x40C);
                            goto L_004616d0;
                        }
                        break;
                    }
                L_0046175c:
                    charge(ctx, 7);
                    lw(a0, s1, 0);
                    v1 = addiu(sp, 0x19C);
                    v1 = sltu(v1, a0);
                    v1 = v1 ^ 0x1;
                    v1 = v1 ^ 0x1;
                    if (v1 == 0) {
                        goto L_00461778;
                    }
                    backedge(ctx);
                }
                break;
            }
        L_00461778:
            charge(ctx, 7);
            lw(a0, s5, 0);
            v1 = addiu(sp, 0x2C8);
            v1 = sltu(v1, a0);
            v1 = v1 ^ 0x1;
            v1 = v1 ^ 0x1;
            if (v1 == 0) {
                goto L_00461794_74;
            }
            backedge(ctx);
        }
    }
    // 0x0046189c
    charge(ctx, 1);
    ld(ra, sp, 0xC0);
    // 0x004618a0 (the shared epilogue, written out on this path)
    charge(ctx, 22);
    lwc1(f30, sp, 0x28);
    lq(fp, sp, 0xB0);
    lwc1(f29, sp, 0x24);
    lq(s7, sp, 0xA0);
    lwc1(f28, sp, 0x20);
    lq(s6, sp, 0x90);
    lwc1(f27, sp, 0x1C);
    lq(s5, sp, 0x80);
    lwc1(f26, sp, 0x18);
    lq(s4, sp, 0x70);
    lwc1(f25, sp, 0x14);
    lq(s3, sp, 0x60);
    lwc1(f24, sp, 0x10);
    lq(s2, sp, 0x50);
    lwc1(f23, sp, 0xC);
    lq(s1, sp, 0x40);
    lwc1(f22, sp, 0x8);
    lq(s0, sp, 0x30);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x410);
    return;
L_00461794_74:
    charge(ctx, 2);
    ld(ra, sp, 0xC0);
    // 0x004618a0 (the shared epilogue, written out on this path)
    charge(ctx, 22);
    lwc1(f30, sp, 0x28);
    lq(fp, sp, 0xB0);
    lwc1(f29, sp, 0x24);
    lq(s7, sp, 0xA0);
    lwc1(f28, sp, 0x20);
    lq(s6, sp, 0x90);
    lwc1(f27, sp, 0x1C);
    lq(s5, sp, 0x80);
    lwc1(f26, sp, 0x18);
    lq(s4, sp, 0x70);
    lwc1(f25, sp, 0x14);
    lq(s3, sp, 0x60);
    lwc1(f24, sp, 0x10);
    lq(s2, sp, 0x50);
    lwc1(f23, sp, 0xC);
    lq(s1, sp, 0x40);
    lwc1(f22, sp, 0x8);
    lq(s0, sp, 0x30);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x410);
    return;
L_004617b8:
    charge(ctx, 8);
    lw(t0, sp, 0x160);
    lhu(v1, a1, 2);
    lw(a3, t0, 32);
    v1 = sll(v1, 4);
    a1 = addu(a3, v1);
    lbu(v1, a1, 1);
    t1 = a1;
    if (v1 == a2) {
        // 0x004617d8: a subtree inside the sphere's box: its whole triangle range (the leftmost to the rightmost leaf)
        charge(ctx, 1);
        v1 = 255;
        for (;;) {
            // 0x004617dc
            charge(ctx, 7);
            lhu(a0, t1, 2);
            a0 = sll(a0, 4);
            t1 = addu(a3, a0);
            lbu(a0, t1, 1);
            if (a0 != v1) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004617f8
    charge(ctx, 5);
    lbu(a2, a1, 9);
    a3 = addiu(a1, 8);
    a1 = 255;
    if (a2 == a1) {
        // 0x0046180c
        charge(ctx, 1);
        lw(a0, t0, 32);
        for (;;) {
            // 0x00461810
            charge(ctx, 7);
            lhu(v1, a3, 2);
            v1 = sll(v1, 4);
            v1 = addu(a0, v1);
            lbu(a2, v1, 9);
            a3 = addiu(v1, 8);
            if (a2 != a1) {
                break;
            }
            backedge(ctx);
        }
        // 0x0046182c
        charge(ctx, 1);
    }
    // 0x00461830
    charge(ctx, 7);
    lhu(v1, a3, 2);
    lhu(a1, t1, 2);
    sw(zero, sp, 0x110);
    v1 = addu(v1, a2);
    v1 = subu(v1, a1);
    a0 = v1 & 0xFFFF;
    backedge(ctx);
    goto L_00461500;
}


// sub_461900 [collGeometryLineAllTriangles] -- a line against every triangle of a one-morph-target geometry (no collision tree)
// ($a0 = the geometry, $a1 = the line in its space, $a2 = the intersection, $a3 = the callback, $t0 = the data)
// The front-face line / triangle test of sub_45F930 on each triangle (the first morph target's vertices); a hit fills
// the collision triangle and calls the callback with the distance t in $f12 (0 stops).
// 0x00461900 sub_461900 -- 1012 bytes; frame 0xF0: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
void sub_461900(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16}, f17{ctx, 17}, f18{ctx, 18}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00461900: the line's delta, the triangles and the first morph target's vertices
    enter(ctx, 36);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
    sd(ra, sp, 0xA0);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    fp = a2;
    sq(s6, sp, 0x70);
    s7 = a0;
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    s5 = a1;
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    s3 = 0;
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f23, sp, 0xC);
    sw(a3, sp, 0xBC);
    swc1(f22, sp, 0x8);
    sw(t0, sp, 0xB8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(a2, a0, geo::kMorphTargets);
    lwc1(f5, a1, 12);
    lwc1(f4, a1, 0);
    lw(v1, a0, geo::kNumTriangles);
    lwc1(f3, a1, 16);
    lw(s4, a0, geo::kTriangles);
    lwc1(f2, a1, 4);
    lwc1(f1, a1, 20);
    lwc1(f0, a1, 8);
    lw(s0, a2, 20);
    sub_s(f20, f5, f4);
    at = slt(0, v1);
    sub_s(f21, f3, f2);
    sub_s(f22, f1, f0);
    if (at != 0) {
        // 0x00461990
        charge(ctx, 3);
        s6 = addiu(sp, 0xCC);
        s2 = addiu(sp, 0xC4);
        s1 = addiu(sp, 0xC8);
        for (;;) {
            // 0x0046199c: each triangle: the front-face line / triangle test (det > 1e-8, edges within 1e-5 of det)
            charge(ctx, 45);
            lhu(a2, s4, 0);
            v1 = 0x322B0000;
            v1 = v1 | 0xCC77;
            lhu(a0, s4, 2);
            mtc1(v1, f1);
            lhu(a3, s4, 4);
            v1 = sll(a2, 1);
            a2 = addu(v1, a2);
            v1 = sll(a0, 1);
            v1 = addu(v1, a0);
            a0 = sll(a2, 2);
            v1 = sll(v1, 2);
            a2 = sll(a3, 1);
            a0 = addu(s0, a0);
            a2 = addu(a2, a3);
            v1 = addu(s0, v1);
            a2 = sll(a2, 2);
            a3 = addu(s0, a2);
            lwc1(f7, a0, 0);
            lwc1(f0, a3, 0);
            lwc1(f5, a0, 8);
            lwc1(f2, v1, 8);
            lwc1(f4, v1, 0);
            lwc1(f6, a0, 4);
            lwc1(f3, v1, 4);
            sub_s(f11, f0, f7);
            sub_s(f16, f2, f5);
            lwc1(f0, a3, 8);
            lwc1(f2, a3, 4);
            sub_s(f15, f3, f6);
            sub_s(f13, f0, f5);
            sub_s(f12, f2, f6);
            mula_s(f21, f13);
            msub_s(f8, f22, f12);
            mula_s(f22, f11);
            msub_s(f9, f20, f13);
            mula_s(f20, f12);
            msub_s(f10, f21, f11);
            sub_s(f14, f4, f7);
            mula_s(f15, f9);
            madda_s(f14, f8);
            madd_s(f0, f16, f10);
            c_le_s(f0, f1);
            a1 = 1;
            if (cond(ctx)) {
                // 0x00461a50
                charge(ctx, 1);
                a1 = 0;
            }
            // 0x00461a54
            charge(ctx, 2);
            if (a1 != 0) {
                // 0x00461a5c
                charge(ctx, 18);
                a2 = 0x37270000;
                a1 = 1;
                a2 = a2 | 0xC5AC;
                mtc1(a2, f2);
                neg_s(f1, f0);
                mul_s(f18, f2, f1);
                lwc1(f2, s5, 4);
                lwc1(f3, s5, 0);
                lwc1(f1, s5, 8);
                sub_s(f6, f2, f6);
                sub_s(f4, f3, f7);
                mula_s(f6, f9);
                sub_s(f1, f1, f5);
                madda_s(f4, f8);
                madd_s(f5, f1, f10);
                c_lt_s(f5, f18);
                sub_s(f17, f0, f18);
                if (cond(ctx)) {
                    // 0x00461aa4
                    charge(ctx, 1);
                    a1 = 0;
                }
                // 0x00461aa8
                charge(ctx, 2);
                if (a1 != 0) {
                    // 0x00461ab0
                    charge(ctx, 3);
                    c_le_s(f5, f17);
                    a1 = 1;
                    if (!cond(ctx)) {
                        // 0x00461abc
                        charge(ctx, 1);
                        a1 = 0;
                    }
                }
                // 0x00461ac0
                charge(ctx, 2);
                if (a1 != 0) {
                    // 0x00461ac8
                    charge(ctx, 12);
                    mula_s(f6, f16);
                    msub_s(f2, f1, f15);
                    mula_s(f1, f14);
                    msub_s(f3, f4, f16);
                    mula_s(f4, f15);
                    msub_s(f4, f6, f14);
                    mula_s(f21, f3);
                    madda_s(f20, f2);
                    madd_s(f1, f22, f4);
                    c_lt_s(f1, f18);
                    a1 = 1;
                    if (cond(ctx)) {
                        // 0x00461af8
                        charge(ctx, 1);
                        a1 = 0;
                    }
                    // 0x00461afc
                    charge(ctx, 2);
                    if (a1 != 0) {
                        // 0x00461b04
                        charge(ctx, 4);
                        add_s(f1, f5, f1);
                        c_le_s(f1, f17);
                        a1 = 1;
                        if (!cond(ctx)) {
                            // 0x00461b14
                            charge(ctx, 1);
                            a1 = 0;
                        }
                    }
                    // 0x00461b18
                    charge(ctx, 2);
                    if (a1 != 0) {
                        // 0x00461b20
                        charge(ctx, 6);
                        mula_s(f12, f3);
                        madda_s(f11, f2);
                        madd_s(f23, f13, f4);
                        c_lt_s(f23, f18);
                        a1 = 1;
                        if (cond(ctx)) {
                            // 0x00461b38
                            charge(ctx, 1);
                            a1 = 0;
                        }
                        // 0x00461b3c
                        charge(ctx, 2);
                        if (a1 != 0) {
                            // 0x00461b44
                            charge(ctx, 3);
                            c_le_s(f23, f17);
                            a1 = 1;
                            if (!cond(ctx)) {
                                // 0x00461b50
                                charge(ctx, 1);
                                a1 = 0;
                            }
                        }
                        // 0x00461b54
                        charge(ctx, 2);
                        if (a1 != 0) {
                            // 0x00461b5c
                            charge(ctx, 3);
                            div_s(f23, f23, f0);
                        }
                    }
                }
            }
            // 0x00461b68
            charge(ctx, 2);
            if (a1 != 0) {
                // 0x00461b90: a hit: the collision triangle (normal, first vertex, index, vertex pointers)
                charge(ctx, 48);
                lwc1(f3, a0, 0);
                v0 = addiu(sp, 0xD8);
                lwc1(f1, a0, 4);
                lwc1(f0, a0, 8);
                mtc1(zero, f2);
                sw(s3, v0, 0);
                swc1(f3, s6, 0);
                v0 = addiu(sp, 0xDC);
                sw(a0, v0, 0);
                swc1(f1, s6, 4);
                v0 = addiu(sp, 0xE0);
                sw(v1, v0, 0);
                swc1(f0, s6, 8);
                v0 = addiu(sp, 0xE4);
                sw(a3, v0, 0);
                lwc1(f6, a0, 0);
                lwc1(f5, v1, 0);
                lwc1(f0, a3, 0);
                lwc1(f3, a0, 8);
                lwc1(f1, v1, 8);
                lwc1(f8, a0, 4);
                lwc1(f4, v1, 4);
                sub_s(f9, f5, f6);
                sub_s(f5, f0, f6);
                sub_s(f6, f1, f3);
                lwc1(f0, a3, 8);
                lwc1(f1, a3, 4);
                sub_s(f7, f4, f8);
                sub_s(f0, f0, f3);
                sub_s(f4, f1, f8);
                mula_s(f7, f0);
                msub_s(f3, f6, f4);
                mula_s(f6, f5);
                msub_s(f1, f9, f0);
                mula_s(f9, f4);
                msub_s(f0, f7, f5);
                mula_s(f1, f1);
                madda_s(f3, f3);
                swc1(f0, s1, 0);
                swc1(f3, sp, 0xC0);
                madd_s(f0, f0, f0);
                sqrt_s(f3, f0);
                swc1(f1, s2, 0);
                c_le_s(f3, f2);
                if (!cond(ctx)) {
                    // 0x00461c50
                    charge(ctx, 8);
                    v0 = 0x3F800000;
                    mtc1(v0, f0);
                    div_s(f3, f0, f3);
                }
                // 0x00461c70: the callback (a0 = the intersection, a1 = the collision triangle, $f12 = the distance, a2 = the data); 0 ends the walk
                charge(ctx, 17);
                lw(a2, sp, 0xB8);
                lwc1(f2, sp, 0xC0);
                lw(v0, sp, 0xBC);
                lwc1(f1, s2, 0);
                a0 = fp;
                lwc1(f0, s1, 0);
                a1 = addiu(sp, 0xC0);
                mov_s(f12, f23);
                mul_s(f2, f2, f3);
                mul_s(f1, f1, f3);
                mul_s(f0, f0, f3);
                swc1(f2, sp, 0xC0);
                swc1(f1, s2, 0);
                jt = v0.u();  // the target, read before the delay slot
                link(ctx, 0x461CA4u);  // $ra = the return address
                swc1(f0, s1, 0);
                call_ptr(ctx, jt);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                goto L_00461b70;
            }
        L_00461b70:
            charge(ctx, 5);
            lw(v1, s7, 16);
            s3 = addiu(s3, 1);
            v1 = slt(s3, v1);
            s4 = addiu(s4, 8);
            if (v1 == 0) {
                goto L_00461b84_26;
            }
            backedge(ctx);
        }
        // 0x00461cb4
        charge(ctx, 1);
        ld(ra, sp, 0xA0);
        // 0x00461cb8 (the shared epilogue, written out on this path)
        charge(ctx, 15);
        lwc1(f23, sp, 0xC);
        lq(fp, sp, 0x90);
        lwc1(f22, sp, 0x8);
        lq(s7, sp, 0x80);
        lwc1(f21, sp, 0x4);
        lq(s6, sp, 0x70);
        lwc1(f20, sp, 0x0);
        lq(s5, sp, 0x60);
        lq(s4, sp, 0x50);
        lq(s3, sp, 0x40);
        lq(s2, sp, 0x30);
        lq(s1, sp, 0x20);
        lq(s0, sp, 0x10);
        sp = addiu(sp, 0xF0);
        return;
    }
L_00461b88:
    charge(ctx, 2);
    ld(ra, sp, 0xA0);
    // 0x00461cb8 (the shared epilogue, written out on this path)
    charge(ctx, 15);
    lwc1(f23, sp, 0xC);
    lq(fp, sp, 0x90);
    lwc1(f22, sp, 0x8);
    lq(s7, sp, 0x80);
    lwc1(f21, sp, 0x4);
    lq(s6, sp, 0x70);
    lwc1(f20, sp, 0x0);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0xF0);
    return;
L_00461b84_26:
    charge(ctx, 1);
    goto L_00461b88;
}


// sub_461D00 [collGeometrySphereAllTriangles] -- a sphere against every triangle of a one-morph-target geometry (no collision tree)
// ($a0 = the geometry, $a1 = the sphere, $a2 = the intersection, $a3 = the callback, $t0 = the data) sub_4BAE00 on
// each triangle (the first morph target's vertices); a hit: the collision triangle and the callback with the distance
// / radius in $f12 (0 stops).
// 0x00461D00 sub_461D00 -- 404 bytes; frame 0xF0: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
void sub_461D00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00461d00: 1 / radius, the triangles and the first morph target's vertices
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
    v1 = 0x3F800000;
    sd(ra, sp, 0xA0);
    lwc1(f0, a1, 12);
    sq(fp, sp, 0x90);
    mtc1(v1, f1);
    sq(s7, sp, 0x80);
    fp = a1;
    sq(s6, sp, 0x70);
    s7 = a0;
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    s4 = 0;
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    sw(a2, sp, 0xBC);
    div_s(f20, f1, f0);
    lw(a1, a0, geo::kMorphTargets);
    lw(v1, a0, geo::kNumTriangles);
    sw(a3, sp, 0xB8);
    sw(t0, sp, 0xB4);
    lw(s5, a0, geo::kTriangles);
    v1 = slt(0, v1);
    lw(s3, a1, 20);
    if (v1 != 0) {
        // 0x00461d7c
        charge(ctx, 1);
        s6 = addiu(sp, 0xCC);
        for (;;) {
            // 0x00461d80: each triangle: the sphere / triangle test (sub_4BAE00)
            charge(ctx, 24);
            lhu(a2, s5, 0);
            a0 = fp;
            lhu(a1, s5, 2);
            t0 = addiu(sp, 0xC0);
            lhu(v1, s5, 4);
            t1 = addiu(sp, 0xEC);
            v0 = sll(a2, 1);
            a2 = addu(v0, a2);
            v0 = sll(a1, 1);
            v0 = addu(v0, a1);
            v0 = sll(v0, 2);
            a1 = sll(a2, 2);
            s1 = addu(s3, v0);
            s2 = addu(s3, a1);
            v0 = sll(v1, 1);
            a1 = s2;
            v0 = addu(v0, v1);
            a2 = s1;
            v0 = sll(v0, 2);
            s0 = addu(s3, v0);
            a3 = s0;
            jal(ctx, 0x461DD0u, gen::fn_sub_4BAE00_004bae00);
            if (v0 != 0) {
                // 0x00461dfc: a hit: the collision triangle; the callback (a0 = the intersection, a1 = the collision triangle, $f12 = the distance, a2 = the data); 0 ends the walk
                charge(ctx, 25);
                lwc1(f0, sp, 0xEC);
                v0 = addiu(sp, 0xDC);
                lw(a0, sp, 0xBC);
                a1 = addiu(sp, 0xC0);
                lw(a2, sp, 0xB4);
                mul_s(f0, f0, f20);
                swc1(f0, sp, 0xEC);
                lwc1(f2, s2, 0);
                lwc1(f1, s2, 4);
                lwc1(f0, s2, 8);
                lwc1(f12, sp, 0xEC);
                sw(s2, v0, 0);
                swc1(f2, s6, 0);
                v0 = addiu(sp, 0xE0);
                sw(s1, v0, 0);
                swc1(f1, s6, 4);
                v0 = addiu(sp, 0xE4);
                sw(s0, v0, 0);
                v0 = addiu(sp, 0xD8);
                sw(s4, v0, 0);
                lw(v0, sp, 0xB8);
                jt = v0.u();  // the target, read before the delay slot
                link(ctx, 0x461E50u);  // $ra = the return address
                swc1(f0, s6, 8);
                call_ptr(ctx, jt);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                goto L_00461de0;
            }
        L_00461de0:
            charge(ctx, 5);
            lw(v1, s7, 16);
            s4 = addiu(s4, 1);
            v1 = slt(s4, v1);
            s5 = addiu(s5, 8);
            if (v1 == 0) {
                goto L_00461df4_5;
            }
            backedge(ctx);
        }
        // 0x00461e60
        charge(ctx, 1);
        ld(ra, sp, 0xA0);
        // 0x00461e64 (the shared epilogue, written out on this path)
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
        return;
    }
L_00461d74:
    charge(ctx, 2);
    ld(ra, sp, 0xA0);
    // 0x00461e64 (the shared epilogue, written out on this path)
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
    return;
L_00461df4_5:
    charge(ctx, 2);
    backedge(ctx);
    goto L_00461d74;
}


// sub_461EA0 [collGeometryLineIntersections] -- a line against a one-morph-target geometry: its collision tree, or every triangle
// ($a0 = the geometry, $a1 = the line in its space, $a2 = the intersection, $a3 = the callback, $t0 = the data) The
// geometry's collision block (geometry + gp 0x7CE728) walked like a sector's in sub_45F930 (an explicit stack of
// {child entry, t0, t1}, the line's interval per split), each leaf triangle with the front-face line / triangle test;
// without a block, sub_461900 tests every triangle.
// 0x00461EA0 sub_461EA0 -- 3344 bytes; frame 0x2E0: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
void sub_461EA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16}, f17{ctx, 17}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00461ea0
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x2E0);
    sd(ra, sp, 0xA0);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f23, sp, 0xC);
    s0 = a1;
    swc1(f22, sp, 0x8);
    sw(a2, sp, 0xDC);
    swc1(f21, sp, 0x4);
    sw(a3, sp, 0xD8);
    swc1(f20, sp, 0x0);
    lw(v1, gp, -17864);  // 0x7CE728
    v1 = addu(a0, v1);
    lw(s5, v1, 0);
    sw(t0, sp, 0xD4);
    if (s5 == 0) {
        // 0x00462b60: no collision block: every triangle (sub_461900)
        charge(ctx, 4);
        jal(ctx, 0x462B60u, gen::fn_sub_461900_00461900);
        backedge(ctx);
    L_004628cc:
        charge(ctx, 2);
        ld(ra, sp, 0xA0);
    } else {
        // 0x00461efc
        charge(ctx, 21);
        lw(v1, a0, 44);
        lwc1(f5, s0, 12);
        lw(a2, a0, 92);
        lwc1(f4, s0, 0);
        lwc1(f3, s0, 16);
        a1 = addiu(sp, 0x145);
        lwc1(f2, s0, 4);
        lwc1(f1, s0, 20);
        lwc1(f0, s0, 8);
        sq(v1, sp, 0xB0);
        lw(v1, a2, 20);
        a0 = 255;
        sub_s(f20, f5, f4);
        sub_s(f21, f3, f2);
        sq(v1, sp, 0xC0);
        sb(a0, a1, 0);
        sw(s5, sp, 0x110);
        sh(zero, sp, 0x146);
        lhu(v1, s5, coll::kNumSplits);
        sub_s(f22, f1, f0);
        if (v1 == 0) {
            // 0x004628d4: the collision tree's root entry (built on the stack)
            charge(ctx, 3);
            lhu(v1, s5, coll::kNumTriangles);
            sb(v1, a1, 0);
            backedge(ctx);
        }
        // 0x00461f50
        charge(ctx, 26);
        lwc1(f3, s0, 0);
        s7 = addiu(sp, 0x114);
        lwc1(f2, s0, 4);
        v1 = addiu(sp, 0x120);
        lwc1(f1, s0, 8);
        a1 = addiu(sp, 0x124);
        mtc1(zero, f0);
        a0 = addiu(sp, 0x128);
        swc1(f3, s7, 0);
        swc1(f2, s7, 4);
        swc1(f1, s7, 8);
        lwc1(f2, s0, 12);
        lwc1(f1, s0, 0);
        sub_s(f1, f2, f1);
        swc1(f1, v1, 0);
        lwc1(f3, s0, 16);
        lwc1(f2, s0, 4);
        lwc1(f1, v1, 0);
        sub_s(f2, f3, f2);
        swc1(f2, a1, 0);
        lwc1(f3, s0, 20);
        lwc1(f2, s0, 8);
        c_eq_s(f0, f1);
        sub_s(f2, f3, f2);
        swc1(f2, a0, 0);
        if (!cond(ctx)) {
            // 0x00461fb8
            charge(ctx, 7);
            v1 = 0x3F800000;
            mtc1(v1, f0);
            div_s(f0, f0, f1);
        }
        // 0x00461fd4
        charge(ctx, 8);
        lwc1(f1, a1, 0);
        s6 = addiu(sp, 0x12C);
        swc1(f0, s6, 0);
        mtc1(zero, f0);
        c_eq_s(f0, f1);
        if (!cond(ctx)) {
            // 0x00461ff4
            charge(ctx, 7);
            v1 = 0x3F800000;
            mtc1(v1, f0);
            div_s(f0, f0, f1);
        }
        // 0x00462010
        charge(ctx, 8);
        lwc1(f1, a0, 0);
        t1 = addiu(sp, 0x130);
        swc1(f0, t1, 0);
        mtc1(zero, f0);
        c_eq_s(f0, f1);
        if (!cond(ctx)) {
            // 0x00462030
            charge(ctx, 7);
            v1 = 0x3F800000;
            mtc1(v1, f0);
            div_s(f0, f0, f1);
        }
        // 0x0046204c
        charge(ctx, 8);
        t0 = addiu(sp, 0x134);
        swc1(f0, t0, 0);
        lwc1(f2, s0, 12);
        mtc1(zero, f0);
        c_lt_s(f2, f0);
        if (cond(ctx)) {
            // 0x00462074
            charge(ctx, 1);
            neg_s(f3, f2);
        } else {
            // 0x0046206c
            charge(ctx, 2);
            mov_s(f3, f2);
        }
        // 0x00462078
        charge(ctx, 6);
        lwc1(f1, s0, 0);
        mtc1(zero, f0);
        c_lt_s(f1, f0);
        if (cond(ctx)) {
            // 0x00462098
            charge(ctx, 1);
            neg_s(f0, f1);
        } else {
            // 0x00462090
            charge(ctx, 2);
            mov_s(f0, f1);
        }
        // 0x0046209c
        charge(ctx, 3);
        c_lt_s(f0, f3);
        if (cond(ctx)) {
            // 0x004620d0
            charge(ctx, 5);
            mtc1(zero, f0);
            c_lt_s(f2, f0);
            if (cond(ctx)) {
                // 0x004620ec
                charge(ctx, 2);
                neg_s(f2, f2);
                mov_s(f1, f2);
            } else {
                // 0x004620e4
                charge(ctx, 2);
                mov_s(f1, f2);
            }
            // 0x004620f4
            charge(ctx, 1);
            fp = addiu(sp, 0x138);
        } else {
            // 0x004620a8
            charge(ctx, 5);
            mtc1(zero, f0);
            c_lt_s(f1, f0);
            if (cond(ctx)) {
                // 0x004620c4
                charge(ctx, 1);
                neg_s(f1, f1);
            } else {
                // 0x004620bc
                charge(ctx, 2);
            }
            // 0x004620c8
            charge(ctx, 2);
            fp = addiu(sp, 0x138);
        }
        // 0x004620f8
        charge(ctx, 7);
        swc1(f1, fp, 0x0);
        lwc1(f2, s0, 16);
        mtc1(zero, f0);
        c_lt_s(f2, f0);
        if (cond(ctx)) {
            // 0x0046211c
            charge(ctx, 1);
            neg_s(f3, f2);
        } else {
            // 0x00462114
            charge(ctx, 2);
            mov_s(f3, f2);
        }
        // 0x00462120
        charge(ctx, 6);
        lwc1(f1, s0, 4);
        mtc1(zero, f0);
        c_lt_s(f1, f0);
        if (cond(ctx)) {
            // 0x00462140
            charge(ctx, 1);
            neg_s(f0, f1);
        } else {
            // 0x00462138
            charge(ctx, 2);
            mov_s(f0, f1);
        }
        // 0x00462144
        charge(ctx, 3);
        c_lt_s(f0, f3);
        if (cond(ctx)) {
            // 0x00462178
            charge(ctx, 5);
            mtc1(zero, f0);
            c_lt_s(f2, f0);
            if (cond(ctx)) {
                // 0x00462194
                charge(ctx, 2);
                neg_s(f2, f2);
                mov_s(f1, f2);
            } else {
                // 0x0046218c
                charge(ctx, 2);
                mov_s(f1, f2);
            }
            // 0x0046219c
            charge(ctx, 1);
            a3 = addiu(sp, 0x13C);
        } else {
            // 0x00462150
            charge(ctx, 5);
            mtc1(zero, f0);
            c_lt_s(f1, f0);
            if (cond(ctx)) {
                // 0x0046216c
                charge(ctx, 1);
                neg_s(f1, f1);
            } else {
                // 0x00462164
                charge(ctx, 2);
            }
            // 0x00462170
            charge(ctx, 2);
            a3 = addiu(sp, 0x13C);
        }
        // 0x004621a0
        charge(ctx, 7);
        swc1(f1, a3, 0);
        lwc1(f2, s0, 20);
        mtc1(zero, f0);
        c_lt_s(f2, f0);
        if (cond(ctx)) {
            // 0x004621c4
            charge(ctx, 1);
            neg_s(f3, f2);
        } else {
            // 0x004621bc
            charge(ctx, 2);
            mov_s(f3, f2);
        }
        // 0x004621c8
        charge(ctx, 6);
        lwc1(f1, s0, 8);
        mtc1(zero, f0);
        c_lt_s(f1, f0);
        if (cond(ctx)) {
            // 0x004621e8
            charge(ctx, 1);
            neg_s(f0, f1);
        } else {
            // 0x004621e0
            charge(ctx, 2);
            mov_s(f0, f1);
        }
        // 0x004621ec
        charge(ctx, 3);
        c_lt_s(f0, f3);
        if (cond(ctx)) {
            // 0x00462220
            charge(ctx, 5);
            mtc1(zero, f0);
            c_lt_s(f2, f0);
            if (cond(ctx)) {
                // 0x0046223c
                charge(ctx, 2);
                neg_s(f2, f2);
                mov_s(f1, f2);
            } else {
                // 0x00462234
                charge(ctx, 2);
                mov_s(f1, f2);
            }
            // 0x00462244
            charge(ctx, 1);
            v1 = 0x35860000;
        } else {
            // 0x004621f8
            charge(ctx, 5);
            mtc1(zero, f0);
            c_lt_s(f1, f0);
            if (cond(ctx)) {
                // 0x00462214
                charge(ctx, 1);
                neg_s(f1, f1);
            } else {
                // 0x0046220c
                charge(ctx, 2);
            }
            // 0x00462218
            charge(ctx, 2);
            v1 = 0x35860000;
        }
        // 0x00462248
        charge(ctx, 38);
        a1 = addiu(sp, 0x150);
        v1 = v1 | 0x37BD;
        a0 = addiu(sp, 0x144);
        mtc1(v1, f2);
        a2 = addiu(sp, 0x140);
        lwc1(f0, fp, 0x0);
        s3 = addiu(sp, 0x2D8);
        mul_s(f8, f1, f2);
        v1 = addiu(sp, 0x14C);
        sw(a0, v1, 0);
        a0 = addiu(sp, 0x154);
        v1 = 0x3F800000;
        sw(v1, a0, 0);
        v1 = addiu(sp, 0x158);
        sw(zero, a1, 0);
        lwc1(f1, a3, 0);
        sw(v1, s3, 0);
        mul_s(f10, f0, f2);
        mul_s(f9, f1, f2);
        lwc1(f4, s6, 0);
        mtc1(zero, f0);
        swc1(f8, a2, 0);
        swc1(f10, fp, 0x0);
        swc1(f9, a3, 0);
        lwc1(f6, s5, 20);
        c_eq_s(f0, f4);
        lwc1(f5, s5, coll::kBoxInf);
        lwc1(f1, s5, 12);
        lwc1(f0, s5, 8);
        sub_s(f6, f6, f9);
        lwc1(f3, s5, 24);
        add_s(f9, f0, f9);
        lwc1(f2, s5, coll::kBoxSup);
        sub_s(f7, f5, f10);
        sub_s(f0, f3, f8);
        add_s(f5, f2, f10);
        add_s(f1, f1, f8);
        if (cond(ctx)) {
            // 0x004628e0
            charge(ctx, 4);
            lwc1(f2, s7, 0);
            c_lt_s(f2, f7);
            v1 = 0;
            if (cond(ctx)) {
                backedge(ctx);
            } else {
                // 0x004628f0
                charge(ctx, 3);
                c_le_s(f2, f5);
                if (!cond(ctx)) {
                    backedge(ctx);
                } else {
                    // 0x004628fc
                    charge(ctx, 3);
                    v1 = 1;
                    backedge(ctx);
                }
            }
        } else {
            // 0x004622e0
            charge(ctx, 8);
            lwc1(f2, s7, 0);
            sub_s(f3, f7, f2);
            mul_s(f3, f4, f3);
            sub_s(f2, f5, f2);
            mul_s(f4, f4, f2);
            c_lt_s(f4, f3);
            mov_s(f5, f3);
            if (cond(ctx)) {
                // 0x00462300
                charge(ctx, 3);
                mov_s(f5, f4);
                mov_s(f4, f3);
            }
            // 0x00462908
            charge(ctx, 4);
            lwc1(f3, a1, 0);
            c_le_s(f3, f4);
            v1 = 0;
            if (!cond(ctx)) {
                backedge(ctx);
            } else {
                // 0x00462918
                charge(ctx, 2);
                lwc1(f2, a0, 0);
                backedge(ctx);
                // 0x00462310
                charge(ctx, 3);
                c_lt_s(f2, f5);
                if (!cond(ctx)) {
                    // 0x0046231c
                    charge(ctx, 1);
                    v1 = 1;
                }
            }
            // 0x00462320
            charge(ctx, 2);
            if (v1 != 0) {
                // 0x00462328
                charge(ctx, 3);
                c_lt_s(f3, f5);
                if (cond(ctx)) {
                    // 0x0046233c
                    charge(ctx, 2);
                    mov_s(f3, f5);
                    lwc1(f2, a0, 0);
                } else {
                    // 0x00462334
                    charge(ctx, 2);
                    lwc1(f2, a0, 0);
                }
                // 0x00462344
                charge(ctx, 3);
                c_le_s(f2, f4);
                swc1(f3, a1, 0);
                if (!cond(ctx)) {
                    // 0x00462358
                    charge(ctx, 2);
                    mov_s(f2, f4);
                    swc1(f2, a0, 0);
                } else {
                    // 0x00462350
                    charge(ctx, 2);
                    swc1(f2, a0, 0);
                }
            }
        }
        // 0x00462360
        charge(ctx, 2);
        if (v1 != 0) {
            // 0x00462368
            charge(ctx, 6);
            lwc1(f4, t1, 0);
            mtc1(zero, f2);
            c_eq_s(f2, f4);
            if (cond(ctx)) {
                // 0x00462920
                charge(ctx, 4);
                lwc1(f2, sp, 0x118);
                c_lt_s(f2, f6);
                v1 = 0;
                if (cond(ctx)) {
                    backedge(ctx);
                } else {
                    // 0x00462930
                    charge(ctx, 3);
                    c_le_s(f2, f9);
                    if (!cond(ctx)) {
                        backedge(ctx);
                    } else {
                        // 0x0046293c
                        charge(ctx, 3);
                        v1 = 1;
                        backedge(ctx);
                    }
                }
            } else {
                // 0x00462380
                charge(ctx, 8);
                lwc1(f2, sp, 0x118);
                sub_s(f3, f6, f2);
                mul_s(f3, f4, f3);
                sub_s(f2, f9, f2);
                mul_s(f4, f4, f2);
                c_lt_s(f4, f3);
                mov_s(f5, f3);
                if (cond(ctx)) {
                    // 0x004623a0
                    charge(ctx, 3);
                    mov_s(f5, f4);
                    mov_s(f4, f3);
                }
                // 0x00462948
                charge(ctx, 4);
                lwc1(f3, a1, 0);
                c_le_s(f3, f4);
                v1 = 0;
                if (!cond(ctx)) {
                    backedge(ctx);
                } else {
                    // 0x00462958
                    charge(ctx, 2);
                    lwc1(f2, a0, 0);
                    backedge(ctx);
                    // 0x004623b0
                    charge(ctx, 3);
                    c_lt_s(f2, f5);
                    if (!cond(ctx)) {
                        // 0x004623bc
                        charge(ctx, 1);
                        v1 = 1;
                    }
                }
                // 0x004623c0
                charge(ctx, 2);
                if (v1 != 0) {
                    // 0x004623c8
                    charge(ctx, 3);
                    c_lt_s(f3, f5);
                    if (cond(ctx)) {
                        // 0x004623dc
                        charge(ctx, 2);
                        mov_s(f3, f5);
                        lwc1(f2, a0, 0);
                    } else {
                        // 0x004623d4
                        charge(ctx, 2);
                        lwc1(f2, a0, 0);
                    }
                    // 0x004623e4
                    charge(ctx, 3);
                    c_le_s(f2, f4);
                    swc1(f3, a1, 0);
                    if (!cond(ctx)) {
                        // 0x004623f8
                        charge(ctx, 2);
                        mov_s(f2, f4);
                        swc1(f2, a0, 0);
                    } else {
                        // 0x004623f0
                        charge(ctx, 2);
                        swc1(f2, a0, 0);
                    }
                }
            }
            // 0x00462400
            charge(ctx, 2);
            if (v1 != 0) {
                // 0x00462408
                charge(ctx, 6);
                lwc1(f4, t0, 0);
                mtc1(zero, f2);
                c_eq_s(f2, f4);
                if (cond(ctx)) {
                    // 0x00462960
                    charge(ctx, 4);
                    lwc1(f2, sp, 0x11C);
                    c_lt_s(f2, f0);
                    v1 = 0;
                    if (cond(ctx)) {
                        backedge(ctx);
                    } else {
                        // 0x00462970
                        charge(ctx, 3);
                        c_le_s(f2, f1);
                        if (!cond(ctx)) {
                            backedge(ctx);
                        } else {
                            // 0x0046297c
                            charge(ctx, 3);
                            v1 = 1;
                            backedge(ctx);
                        }
                    }
                } else {
                    // 0x00462420
                    charge(ctx, 8);
                    lwc1(f3, sp, 0x11C);
                    sub_s(f2, f0, f3);
                    sub_s(f0, f1, f3);
                    mul_s(f1, f4, f2);
                    mul_s(f2, f4, f0);
                    c_lt_s(f2, f1);
                    mov_s(f3, f1);
                    if (cond(ctx)) {
                        // 0x00462440
                        charge(ctx, 3);
                        mov_s(f3, f2);
                        mov_s(f2, f1);
                    }
                    // 0x00462988
                    charge(ctx, 4);
                    lwc1(f1, a1, 0);
                    c_le_s(f1, f2);
                    v1 = 0;
                    if (!cond(ctx)) {
                        backedge(ctx);
                    } else {
                        // 0x00462998
                        charge(ctx, 2);
                        lwc1(f0, a0, 0);
                        backedge(ctx);
                        // 0x00462450
                        charge(ctx, 3);
                        c_lt_s(f0, f3);
                        if (!cond(ctx)) {
                            // 0x0046245c
                            charge(ctx, 1);
                            v1 = 1;
                        }
                    }
                    // 0x00462460
                    charge(ctx, 2);
                    if (v1 != 0) {
                        // 0x00462468
                        charge(ctx, 3);
                        c_lt_s(f1, f3);
                        if (cond(ctx)) {
                            // 0x0046247c
                            charge(ctx, 2);
                            mov_s(f1, f3);
                            lwc1(f0, a0, 0);
                        } else {
                            // 0x00462474
                            charge(ctx, 2);
                            lwc1(f0, a0, 0);
                        }
                        // 0x00462484
                        charge(ctx, 3);
                        c_le_s(f0, f2);
                        swc1(f1, a1, 0);
                        if (!cond(ctx)) {
                            // 0x00462498
                            charge(ctx, 2);
                            mov_s(f0, f2);
                            swc1(f0, a0, 0);
                        } else {
                            // 0x00462490
                            charge(ctx, 2);
                            swc1(f0, a0, 0);
                        }
                    }
                }
            }
        }
        // 0x004624a0
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x004629a0
            charge(ctx, 3);
            v1 = addiu(sp, 0x14C);
            sw(v1, s3, 0);
            backedge(ctx);
        }
        // 0x004624a8
        charge(ctx, 7);
        lw(a0, s3, 0);
        v1 = addiu(sp, 0x14C);
        v1 = sltu(v1, a0);
        v1 = v1 ^ 0x1;
        v1 = v1 ^ 0x1;
        if (v1 != 0) {
            // 0x004624c4: pop a child entry; a split: the side(s) the line's interval reaches
            charge(ctx, 1);
            s2 = addiu(sp, 0xEC);
            for (;;) {
                // 0x004624c8
                charge(ctx, 8);
                lw(v1, s3, 0);
                a0 = 255;
                a1 = addiu(v1, -12);
                sw(a1, s3, 0);
                lw(a2, v1, -12);
                lbu(v1, a2, 1);
                if (v1 == a0) {
                    // 0x004624e8
                    charge(ctx, 1);
                    mtc1(zero, f3);
                    for (;;) {
                        // 0x004624ec
                        charge(ctx, 26);
                        lw(v1, sp, 0x110);
                        lwc1(f4, a1, 8);
                        lhu(a2, a2, 2);
                        lwc1(f2, a1, 4);
                        lw(v1, v1, 32);
                        a2 = sll(a2, 4);
                        v1 = addu(v1, a2);
                        lbu(a2, v1, 0);
                        lwc1(f1, v1, 12);
                        lwc1(f0, v1, 4);
                        t0 = a2 & 0xC;
                        a2 = addiu(sp, 0x120);
                        a3 = addu(s7, t0);
                        a2 = addu(a2, t0);
                        lwc1(f7, a2, 0);
                        lwc1(f6, a3, 0);
                        a2 = addu(fp, t0);
                        lwc1(f5, a2, 0);
                        adda_s(f3, f6);
                        c_le_s(f7, f3);
                        sub_s(f8, f1, f5);
                        add_s(f5, f0, f5);
                        madd_s(f1, f4, f7);
                        adda_s(f3, f6);
                        madd_s(f4, f2, f7);
                        if (cond(ctx)) {
                            // 0x004625d8
                            charge(ctx, 3);
                            c_lt_s(f5, f1);
                            if (cond(ctx)) {
                                // 0x004629e8
                                charge(ctx, 3);
                                v1 = addiu(v1, 8);
                                sw(v1, a1, 0);
                                backedge(ctx);
                            } else {
                                // 0x004625e4
                                charge(ctx, 3);
                                c_le_s(f8, f4);
                                if (!cond(ctx)) {
                                    // 0x004629f8
                                    charge(ctx, 2);
                                    sw(v1, a1, 0);
                                    backedge(ctx);
                                } else {
                                    // 0x004625f0
                                    charge(ctx, 16);
                                    lw(a3, s3, 0);
                                    a1 = addu(s6, t0);
                                    a2 = addiu(v1, 8);
                                    c_le_s(f8, f1);
                                    a3 = addiu(a3, 12);
                                    sw(a3, s3, 0);
                                    lwc1(f2, a1, 0);
                                    lw(a1, s3, 0);
                                    sw(a2, a1, 0);
                                    lw(a1, s3, 0);
                                    lwc1(f0, a1, -8);
                                    swc1(f0, a1, 4);
                                    lw(a1, s3, 0);
                                    lwc1(f0, a1, -4);
                                    swc1(f0, a1, 8);
                                    if (!cond(ctx)) {
                                        // 0x00462a00
                                        charge(ctx, 7);
                                        lw(a1, s3, 0);
                                        sub_s(f1, f8, f1);
                                        lwc1(f0, a1, 8);
                                        adda_s(f3, f0);
                                        madd_s(f0, f2, f1);
                                        swc1(f0, a1, 8);
                                        backedge(ctx);
                                    }
                                    // 0x00462630
                                    charge(ctx, 4);
                                    lw(a1, s3, 0);
                                    c_lt_s(f5, f4);
                                    sw(v1, a1, -12);
                                    if (cond(ctx)) {
                                        // 0x00462640
                                        charge(ctx, 6);
                                        lw(v1, s3, 0);
                                        sub_s(f1, f5, f4);
                                        lwc1(f0, v1, -8);
                                        adda_s(f3, f0);
                                        madd_s(f0, f2, f1);
                                        swc1(f0, v1, -8);
                                    }
                                }
                            }
                        } else {
                            // 0x00462554
                            charge(ctx, 3);
                            c_le_s(f8, f1);
                            if (!cond(ctx)) {
                                // 0x004629ac
                                charge(ctx, 2);
                                sw(v1, a1, 0);
                                backedge(ctx);
                            } else {
                                // 0x00462560
                                charge(ctx, 3);
                                c_lt_s(f5, f4);
                                if (cond(ctx)) {
                                    // 0x004629b8
                                    charge(ctx, 3);
                                    v1 = addiu(v1, 8);
                                    sw(v1, a1, 0);
                                    backedge(ctx);
                                } else {
                                    // 0x0046256c
                                    charge(ctx, 15);
                                    lw(a2, s3, 0);
                                    a1 = addu(s6, t0);
                                    c_lt_s(f5, f1);
                                    a2 = addiu(a2, 12);
                                    sw(a2, s3, 0);
                                    lwc1(f2, a1, 0);
                                    lw(a1, s3, 0);
                                    sw(v1, a1, 0);
                                    lw(a1, s3, 0);
                                    lwc1(f0, a1, -8);
                                    swc1(f0, a1, 4);
                                    lw(a1, s3, 0);
                                    lwc1(f0, a1, -4);
                                    swc1(f0, a1, 8);
                                    if (cond(ctx)) {
                                        // 0x004629c8
                                        charge(ctx, 7);
                                        lw(a1, s3, 0);
                                        sub_s(f1, f5, f1);
                                        lwc1(f0, a1, 8);
                                        adda_s(f3, f0);
                                        madd_s(f0, f2, f1);
                                        swc1(f0, a1, 8);
                                        backedge(ctx);
                                    }
                                    // 0x004625a8
                                    charge(ctx, 5);
                                    a1 = addiu(v1, 8);
                                    lw(v1, s3, 0);
                                    c_le_s(f8, f4);
                                    sw(a1, v1, -12);
                                    if (!cond(ctx)) {
                                        // 0x004625bc
                                        charge(ctx, 7);
                                        lw(v1, s3, 0);
                                        sub_s(f1, f8, f4);
                                        lwc1(f0, v1, -8);
                                        adda_s(f3, f0);
                                        madd_s(f0, f2, f1);
                                        swc1(f0, v1, -8);
                                    }
                                }
                            }
                        }
                        // 0x00462658
                        charge(ctx, 5);
                        lw(a1, s3, 0);
                        lw(a2, a1, 0);
                        lbu(v1, a2, 1);
                        if (v1 != a0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0046266c
                    charge(ctx, 1);
                }
                // 0x00462670
                charge(ctx, 7);
                lw(a0, a1, 0);
                v1 = v1 & 0xFF;
                lhu(s4, a0, 2);
                s1 = addu(s4, v1);
                at = slt(s4, s1);
                if (at != 0) {
                    for (;;) {
                        // 0x0046268c: a leaf triangle (through the triangle map when there is one): the line / triangle test
                        charge(ctx, 3);
                        lw(a0, s5, coll::kTriMap);
                        if (a0 == 0) {
                            // 0x004626ac
                            charge(ctx, 1);
                            v1 = s4;
                        } else {
                            // 0x00462698
                            charge(ctx, 5);
                            v1 = s4 & 0xFFFF;
                            v1 = sll(v1, 1);
                            v1 = addu(a0, v1);
                            lhu(v1, v1, 0);
                        }
                        // 0x004626b0
                        charge(ctx, 51);
                        a0 = v1 & 0xFFFF;
                        v1 = 0x322B0000;
                        a1 = sll(a0, 3);
                        a2 = v1 | 0xCC77;
                        lq(v1, sp, 0xB0);
                        mtc1(a2, f1);
                        v1 = addu(v1, a1);
                        lhu(a3, v1, 0);
                        lhu(a2, v1, 2);
                        lhu(t0, v1, 4);
                        v1 = sll(a3, 1);
                        t1 = addu(v1, a3);
                        v1 = sll(a2, 1);
                        a3 = addu(v1, a2);
                        lq(v1, sp, 0xC0);
                        a2 = sll(t1, 2);
                        a3 = sll(a3, 2);
                        a2 = addu(v1, a2);
                        v1 = addu(v1, a3);
                        a3 = sll(t0, 1);
                        a3 = addu(a3, t0);
                        t0 = sll(a3, 2);
                        lq(a3, sp, 0xC0);
                        lwc1(f7, a2, 0);
                        lwc1(f4, v1, 0);
                        lwc1(f5, a2, 8);
                        lwc1(f2, v1, 8);
                        lwc1(f6, a2, 4);
                        lwc1(f3, v1, 4);
                        t0 = addu(a3, t0);
                        lwc1(f0, t0, 0);
                        sub_s(f14, f4, f7);
                        sub_s(f16, f2, f5);
                        sub_s(f11, f0, f7);
                        lwc1(f0, t0, 8);
                        lwc1(f2, t0, 4);
                        sub_s(f15, f3, f6);
                        sub_s(f13, f0, f5);
                        sub_s(f12, f2, f6);
                        mula_s(f21, f13);
                        msub_s(f8, f22, f12);
                        mula_s(f22, f11);
                        msub_s(f9, f20, f13);
                        mula_s(f20, f12);
                        msub_s(f10, f21, f11);
                        mula_s(f15, f9);
                        madda_s(f14, f8);
                        madd_s(f0, f16, f10);
                        c_le_s(f0, f1);
                        a1 = 1;
                        if (cond(ctx)) {
                            // 0x0046277c
                            charge(ctx, 1);
                            a1 = 0;
                        }
                        // 0x00462780
                        charge(ctx, 2);
                        if (a1 != 0) {
                            // 0x00462788
                            charge(ctx, 18);
                            a1 = 0x37270000;
                            a3 = a1 | 0xC5AC;
                            lwc1(f1, s0, 0);
                            a1 = 1;
                            mtc1(a3, f3);
                            neg_s(f2, f0);
                            mul_s(f17, f3, f2);
                            sub_s(f4, f1, f7);
                            lwc1(f2, s0, 4);
                            lwc1(f1, s0, 8);
                            sub_s(f6, f2, f6);
                            mula_s(f6, f9);
                            sub_s(f1, f1, f5);
                            madda_s(f4, f8);
                            madd_s(f5, f1, f10);
                            c_lt_s(f5, f17);
                            sub_s(f7, f0, f17);
                            if (cond(ctx)) {
                                // 0x004627d0
                                charge(ctx, 1);
                                a1 = 0;
                            }
                            // 0x004627d4
                            charge(ctx, 2);
                            if (a1 != 0) {
                                // 0x004627dc
                                charge(ctx, 3);
                                c_le_s(f5, f7);
                                a1 = 1;
                                if (!cond(ctx)) {
                                    // 0x004627e8
                                    charge(ctx, 1);
                                    a1 = 0;
                                }
                            }
                            // 0x004627ec
                            charge(ctx, 2);
                            if (a1 != 0) {
                                // 0x004627f4
                                charge(ctx, 12);
                                mula_s(f6, f16);
                                msub_s(f2, f1, f15);
                                mula_s(f1, f14);
                                msub_s(f3, f4, f16);
                                mula_s(f4, f15);
                                msub_s(f4, f6, f14);
                                mula_s(f21, f3);
                                madda_s(f20, f2);
                                madd_s(f1, f22, f4);
                                c_lt_s(f1, f17);
                                a1 = 1;
                                if (cond(ctx)) {
                                    // 0x00462824
                                    charge(ctx, 1);
                                    a1 = 0;
                                }
                                // 0x00462828
                                charge(ctx, 2);
                                if (a1 != 0) {
                                    // 0x00462830
                                    charge(ctx, 4);
                                    add_s(f1, f5, f1);
                                    c_le_s(f1, f7);
                                    a1 = 1;
                                    if (!cond(ctx)) {
                                        // 0x00462840
                                        charge(ctx, 1);
                                        a1 = 0;
                                    }
                                }
                                // 0x00462844
                                charge(ctx, 2);
                                if (a1 != 0) {
                                    // 0x0046284c
                                    charge(ctx, 6);
                                    mula_s(f12, f3);
                                    madda_s(f11, f2);
                                    madd_s(f23, f13, f4);
                                    c_lt_s(f23, f17);
                                    a1 = 1;
                                    if (cond(ctx)) {
                                        // 0x00462864
                                        charge(ctx, 1);
                                        a1 = 0;
                                    }
                                    // 0x00462868
                                    charge(ctx, 2);
                                    if (a1 != 0) {
                                        // 0x00462870
                                        charge(ctx, 3);
                                        c_le_s(f23, f7);
                                        a1 = 1;
                                        if (!cond(ctx)) {
                                            // 0x0046287c
                                            charge(ctx, 1);
                                            a1 = 0;
                                        }
                                    }
                                    // 0x00462880
                                    charge(ctx, 2);
                                    if (a1 != 0) {
                                        // 0x00462888
                                        charge(ctx, 3);
                                        div_s(f23, f23, f0);
                                    }
                                }
                            }
                        }
                        // 0x00462894
                        charge(ctx, 2);
                        if (a1 != 0) {
                            // 0x00462a20
                            charge(ctx, 50);
                            v0 = addiu(sp, 0xF8);
                            lwc1(f3, a2, 0);
                            lwc1(f1, a2, 4);
                            lwc1(f0, a2, 8);
                            mtc1(zero, f2);
                            sw(a0, v0, 0);
                            swc1(f3, s2, 0);
                            v0 = addiu(sp, 0xFC);
                            sw(a2, v0, 0);
                            swc1(f1, s2, 4);
                            v0 = addiu(sp, 0x100);
                            sw(v1, v0, 0);
                            swc1(f0, s2, 8);
                            v0 = addiu(sp, 0x104);
                            sw(t0, v0, 0);
                            lwc1(f6, a2, 0);
                            v0 = addiu(sp, 0xE4);
                            lwc1(f5, v1, 0);
                            lwc1(f0, t0, 0);
                            lwc1(f3, a2, 8);
                            lwc1(f1, v1, 8);
                            lwc1(f8, a2, 4);
                            lwc1(f4, v1, 4);
                            sub_s(f9, f5, f6);
                            sub_s(f5, f0, f6);
                            sub_s(f6, f1, f3);
                            lwc1(f0, t0, 8);
                            lwc1(f1, t0, 4);
                            sub_s(f7, f4, f8);
                            sub_s(f0, f0, f3);
                            sub_s(f4, f1, f8);
                            mula_s(f7, f0);
                            msub_s(f3, f6, f4);
                            mula_s(f6, f5);
                            msub_s(f1, f9, f0);
                            mula_s(f9, f4);
                            msub_s(f0, f7, f5);
                            swc1(f1, v0, 0);
                            mula_s(f1, f1);
                            v0 = addiu(sp, 0xE8);
                            madda_s(f3, f3);
                            swc1(f0, v0, 0);
                            swc1(f3, sp, 0xE0);
                            madd_s(f0, f0, f0);
                            sqrt_s(f3, f0);
                            c_le_s(f3, f2);
                            if (!cond(ctx)) {
                                // 0x00462ae8
                                charge(ctx, 7);
                                v0 = 0x3F800000;
                                mtc1(v0, f0);
                                div_s(f3, f0, f3);
                            }
                            // 0x00462b04
                            charge(ctx, 21);
                            v0 = addiu(sp, 0xE4);
                            lw(a0, sp, 0xDC);
                            lwc1(f1, v0, 0);
                            lw(a2, sp, 0xD4);
                            lwc1(f2, sp, 0xE0);
                            a1 = addiu(sp, 0xE0);
                            mov_s(f12, f23);
                            v0 = addiu(sp, 0xE8);
                            lwc1(f0, v0, 0);
                            mul_s(f2, f2, f3);
                            mul_s(f1, f1, f3);
                            v0 = addiu(sp, 0xE4);
                            swc1(f1, v0, 0);
                            mul_s(f0, f0, f3);
                            v0 = addiu(sp, 0xE8);
                            swc1(f0, v0, 0);
                            lw(v0, sp, 0xD8);
                            jt = v0.u();  // the target, read before the delay slot
                            link(ctx, 0x462B48u);  // $ra = the return address
                            swc1(f2, sp, 0xE0);
                            call_ptr(ctx, jt);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            goto L_0046289c;
                        }
                    L_0046289c:
                        charge(ctx, 5);
                        v1 = addiu(s4, 1);
                        s4 = v1 & 0xFFFF;
                        v1 = slt(s4, s1);
                        if (v1 == 0) {
                            goto L_004628b0;
                        }
                        backedge(ctx);
                    }
                    break;
                }
            L_004628b0:
                charge(ctx, 7);
                lw(a0, s3, 0);
                v1 = addiu(sp, 0x14C);
                v1 = sltu(v1, a0);
                v1 = v1 ^ 0x1;
                v1 = v1 ^ 0x1;
                if (v1 == 0) {
                    goto L_004628cc;
                }
                backedge(ctx);
            }
            // 0x00462b58
            charge(ctx, 2);
        }
        // 0x00462b70
        charge(ctx, 1);
        ld(ra, sp, 0xA0);
    }
    // 0x00462b74 (the shared epilogue, written out on this path)
    charge(ctx, 15);
    lwc1(f23, sp, 0xC);
    lq(fp, sp, 0x90);
    lwc1(f22, sp, 0x8);
    lq(s7, sp, 0x80);
    lwc1(f21, sp, 0x4);
    lq(s6, sp, 0x70);
    lwc1(f20, sp, 0x0);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x2E0);
}


// sub_462BB0 [collGeometrySphereIntersections] -- a sphere against a one-morph-target geometry: its collision tree, or every triangle
// ($a0 = the geometry, $a1 = the sphere in its space, $a2 = the intersection, $a3 = the callback, $t0 = the data) The
// geometry's collision block walked like a sector's in sub_460EC0 (the sphere box's inside / outside bits per child; a
// subtree inside the sphere's box taken whole with the plane distance), other leaf triangles with sub_4BAE00; without
// a block, sub_461D00 tests every triangle.
// 0x00462BB0 sub_462BB0 -- 2264 bytes; frame 0x2D0: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
void sub_462BB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20};
    // 0x00462bb0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x2D0);
    sd(ra, sp, 0xA0);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s0 = a1;
    lw(v1, gp, -17864);  // 0x7CE728
    sw(a2, sp, 0xFC);
    sw(a3, sp, 0xF8);
    v1 = addu(a0, v1);
    lw(s5, v1, 0);
    sw(t0, sp, 0xF4);
    if (s5 == 0) {
        // 0x00463444: no collision block: every triangle (sub_461D00)
        charge(ctx, 4);
        jal(ctx, 0x463444u, gen::fn_sub_461D00_00461d00);
        backedge(ctx);
    L_00463338:
        charge(ctx, 2);
        ld(ra, sp, 0xA0);
    } else {
        // 0x00462c00
        charge(ctx, 5);
        lwc1(f5, s5, coll::kBoxInf);
        lwc1(f1, s0, 0);
        c_lt_s(f1, f5);
        if (!cond(ctx)) {
            // 0x00462c1c
            charge(ctx, 4);
            lwc1(f0, s5, coll::kBoxSup);
            c_le_s(f1, f0);
            if (cond(ctx)) {
                // 0x00462c34
                charge(ctx, 1);
                mtc1(zero, f0);
            } else {
                // 0x00462c2c
                charge(ctx, 2);
                sub_s(f0, f1, f0);
            }
        } else {
            // 0x00462c14
            charge(ctx, 2);
            sub_s(f0, f5, f1);
        }
        // 0x00462c38
        charge(ctx, 5);
        lwc1(f4, s5, 20);
        lwc1(f1, s0, 4);
        c_lt_s(f1, f4);
        mul_s(f6, f0, f0);
        if (!cond(ctx)) {
            // 0x00462c54
            charge(ctx, 4);
            lwc1(f0, s5, 8);
            c_le_s(f1, f0);
            if (cond(ctx)) {
                // 0x00462c6c
                charge(ctx, 1);
                mtc1(zero, f0);
            } else {
                // 0x00462c64
                charge(ctx, 2);
                sub_s(f0, f1, f0);
            }
        } else {
            // 0x00462c4c
            charge(ctx, 2);
            sub_s(f0, f4, f1);
        }
        // 0x00462c70
        charge(ctx, 8);
        lwc1(f3, s5, 24);
        lwc1(f1, s0, 8);
        mtc1(zero, f2);
        adda_s(f2, f6);
        c_lt_s(f1, f3);
        madd_s(f6, f0, f0);
        if (!cond(ctx)) {
            // 0x00462c98
            charge(ctx, 4);
            lwc1(f0, s5, 12);
            c_le_s(f1, f0);
            if (!cond(ctx)) {
                // 0x00462ca8
                charge(ctx, 2);
                sub_s(f2, f1, f0);
            }
        } else {
            // 0x00462c90
            charge(ctx, 2);
            sub_s(f2, f3, f1);
        }
        // 0x00462cb0
        charge(ctx, 9);
        lwc1(f0, s0, 12);
        mtc1(zero, f1);
        adda_s(f1, f6);
        madd_s(f2, f2, f2);
        mul_s(f1, f0, f0);
        c_le_s(f2, f1);
        if (cond(ctx)) {
            // 0x00462cd4
            charge(ctx, 77);
            a1 = 0x3F800000;
            v1 = 0x3F110000;
            mtc1(a1, f2);
            v1 = v1 | 0xEB85;
            mtc1(v1, f1);
            t2 = addiu(sp, 0x28C);
            div_s(f20, f2, f0);
            lw(a1, a0, 92);
            lw(v1, a0, 44);
            t0 = addiu(sp, 0x294);
            a2 = addiu(sp, 0x288);
            t7 = addiu(sp, 0x2AC);
            t6 = addiu(sp, 0x2B0);
            t5 = addiu(sp, 0x2B4);
            t4 = addiu(sp, 0x2A4);
            t3 = addiu(sp, 0x2A8);
            t1 = addiu(sp, 0x290);
            a3 = addiu(sp, 0x284);
            sq(v1, sp, 0xC0);
            lw(v1, a1, 20);
            sq(v1, sp, 0xD0);
            lwc1(f6, s0, 0);
            lwc1(f2, s0, 4);
            mul_s(f14, f1, f0);
            swc1(f6, sp, 0x2C0);
            swc1(f2, sp, 0x2C4);
            ld(v1, sp, 0x2C0);
            lwc1(f1, s0, 8);
            sd(v1, sp, 0x280);
            swc1(f1, t2, 8);
            sd(v1, sp, 0x2A0);
            lwc1(f9, sp, 0x284);
            lwc1(f11, sp, 0x2A0);
            swc1(f1, sp, 0x288);
            lwc1(f12, sp, 0x2A4);
            swc1(f1, sp, 0x2A8);
            lwc1(f10, sp, 0x280);
            swc1(f9, t2, 4);
            add_s(f9, f11, f0);
            c_le_s(f5, f9);
            sub_s(f5, f10, f14);
            lwc1(f8, t0, 0);
            swc1(f5, t2, 0);
            lwc1(f7, sp, 0x280);
            lwc1(f6, a2, 0);
            lwc1(f2, t3, 0);
            lwc1(f13, sp, 0x2A0);
            sub_s(f5, f8, f14);
            swc1(f12, t7, 4);
            swc1(f5, t0, 0);
            add_s(f5, f7, f14);
            swc1(f5, sp, 0x280);
            add_s(f5, f6, f14);
            lwc1(f8, t6, 0);
            lwc1(f7, t4, 0);
            swc1(f5, a2, 0);
            lwc1(f6, t1, 0);
            add_s(f2, f2, f0);
            sub_s(f12, f13, f0);
            sub_s(f8, f8, f0);
            add_s(f7, f7, f0);
            sub_s(f6, f6, f14);
            swc1(f1, sp, 0x2C8);
            swc1(f1, t7, 8);
            lwc1(f1, t5, 0);
            lwc1(f5, a3, 0);
            swc1(f2, t3, 0);
            swc1(f12, t7, 0);
            swc1(f9, sp, 0x2A0);
            swc1(f8, t6, 0);
            sub_s(f1, f1, f0);
            add_s(f0, f5, f14);
            swc1(f1, t5, 0);
            swc1(f7, t4, 0);
            swc1(f6, t1, 0);
            swc1(f0, a3, 0);
            if (cond(ctx)) {
                // 0x00462e08
                charge(ctx, 3);
                c_le_s(f4, f7);
                if (!cond(ctx)) {
                    goto L_0046334c;
                }
                // 0x00462e14
                charge(ctx, 3);
                c_le_s(f3, f2);
                if (!cond(ctx)) {
                    goto L_0046334c;
                }
                // 0x00462e20
                charge(ctx, 4);
                lwc1(f0, s5, coll::kBoxSup);
                c_lt_s(f0, f12);
                if (cond(ctx)) {
                    goto L_0046334c;
                }
                // 0x00462e30
                charge(ctx, 4);
                lwc1(f0, s5, 8);
                c_lt_s(f0, f8);
                if (cond(ctx)) {
                    goto L_0046334c;
                }
                // 0x00462e40
                charge(ctx, 4);
                lwc1(f0, s5, 12);
                c_lt_s(f0, f1);
                if (cond(ctx)) {
                    goto L_0046334c;
                }
                // 0x00462e50: the collision tree's root entry (built on the stack)
                charge(ctx, 8);
                a0 = addiu(sp, 0x165);
                v1 = 255;
                sw(s5, sp, 0x130);
                sh(zero, sp, 0x166);
                sb(v1, a0, 0);
                lhu(v1, s5, coll::kNumSplits);
                if (v1 == 0) {
                    // 0x00463340
                    charge(ctx, 3);
                    lhu(v1, s5, coll::kNumTriangles);
                    sb(v1, a0, 0);
                    backedge(ctx);
                }
                // 0x00462e70
                charge(ctx, 26);
                lwc1(f0, sp, 0x2A0);
                v1 = addiu(sp, 0x16C);
                swc1(f2, sp, 0x13C);
                a0 = addiu(sp, 0x164);
                swc1(f1, sp, 0x148);
                sw(a0, v1, 0);
                lwc1(f4, a3, 0);
                lwc1(f3, a2, 0);
                lwc1(f5, t2, 0);
                swc1(f0, sp, 0x134);
                lwc1(f2, t1, 0);
                lwc1(f1, t0, 0);
                lwc1(f0, sp, 0x280);
                swc1(f7, sp, 0x138);
                swc1(f12, sp, 0x140);
                swc1(f8, sp, 0x144);
                swc1(f4, sp, 0x150);
                swc1(f3, sp, 0x154);
                swc1(f5, sp, 0x158);
                swc1(f2, sp, 0x15C);
                swc1(f1, sp, 0x160);
                swc1(f0, sp, 0x14C);
                lwc1(f0, s5, 20);
                c_lt_s(f0, f2);
                sw(v1, sp, 0xE0);
                if (!cond(ctx)) {
                    // 0x00462ee0
                    charge(ctx, 1);
                    t0 = 0;
                } else {
                    // 0x00462ed8
                    charge(ctx, 2);
                    t0 = 4;
                }
                // 0x00462ee4
                charge(ctx, 4);
                lwc1(f0, s5, coll::kBoxInf);
                c_lt_s(f0, f5);
                v1 = 1;
                if (!cond(ctx)) {
                    // 0x00462ef4
                    charge(ctx, 1);
                    v1 = 0;
                }
                // 0x00462ef8
                charge(ctx, 4);
                lwc1(f0, s5, 24);
                c_lt_s(f0, f1);
                if (!cond(ctx)) {
                    // 0x00462f10
                    charge(ctx, 1);
                    a0 = 0;
                } else {
                    // 0x00462f08
                    charge(ctx, 2);
                    a0 = 16;
                }
                // 0x00462f14
                charge(ctx, 5);
                lwc1(f1, s5, coll::kBoxSup);
                lwc1(f0, sp, 0x280);
                c_le_s(f1, f0);
                if (cond(ctx)) {
                    // 0x00462f30
                    charge(ctx, 1);
                    a3 = 0;
                } else {
                    // 0x00462f28
                    charge(ctx, 2);
                    a3 = 2;
                }
                // 0x00462f34
                charge(ctx, 4);
                lwc1(f0, s5, 8);
                c_le_s(f0, f4);
                if (cond(ctx)) {
                    // 0x00462f4c
                    charge(ctx, 1);
                    a2 = 0;
                } else {
                    // 0x00462f44
                    charge(ctx, 2);
                    a2 = 8;
                }
                // 0x00462f50
                charge(ctx, 4);
                lwc1(f0, s5, 12);
                c_le_s(f0, f3);
                if (cond(ctx)) {
                    // 0x00462f68
                    charge(ctx, 1);
                    a1 = 0;
                } else {
                    // 0x00462f60
                    charge(ctx, 2);
                    a1 = 32;
                }
                // 0x00462f6c
                charge(ctx, 9);
                v1 = v1 | t0;
                s3 = addiu(sp, 0x274);
                a0 = a0 | v1;
                v1 = addiu(sp, 0x174);
                a0 = a3 | a0;
                sw(v1, s3, 0);
                v1 = a2 | a0;
                v1 = a1 | v1;
                sw(v1, sp, 0x170);
                goto L_00462f90;
            }
        L_0046334c:
            charge(ctx, 5);
            v1 = addiu(sp, 0x16C);
            s3 = addiu(sp, 0x274);
            sw(v1, sp, 0xE0);
            sw(v1, s3, 0);
            backedge(ctx);
        L_00462f90:
            charge(ctx, 7);
            lw(a0, s3, 0);
            lw(v1, sp, 0xE0);
            v1 = sltu(v1, a0);
            v1 = v1 ^ 0x1;
            v1 = v1 ^ 0x1;
            if (v1 == 0) {
                goto L_00463454;
            }
            for (;;) {
                // 0x00462fac
                charge(ctx, 6);
                lw(v1, s3, 0);
                t2 = 2;
                a2 = 255;
                v1 = addiu(v1, -8);
                sw(v1, s3, 0);
                v1 = 1;
                for (;;) {
                    // 0x00462fc4
                    charge(ctx, 5);
                    lw(t0, s3, 0);
                    lw(a1, t0, 0);
                    lbu(a0, a1, 1);
                    if (a0 != a2) {
                        break;
                    }
                    // 0x00462fe8: a split: the side(s) the sphere's box reaches
                    charge(ctx, 3);
                    lw(a0, t0, 4);
                    if (a0 == 0) {
                        goto L_00463360;
                    }
                    // 0x00462ff4
                    charge(ctx, 14);
                    lw(a0, sp, 0x130);
                    a3 = addiu(sp, 0x134);
                    lhu(a1, a1, 2);
                    lw(a0, a0, 32);
                    a1 = sll(a1, 4);
                    a1 = addu(a0, a1);
                    lbu(a0, a1, 0);
                    lwc1(f1, a1, 12);
                    a0 = a0 & 0xC;
                    a3 = addu(a3, a0);
                    lwc1(f0, a3, 0);
                    c_le_s(f1, f0);
                    if (cond(ctx)) {
                        // 0x00463038
                        charge(ctx, 9);
                        a3 = addiu(a1, 8);
                        sw(a3, t0, 0);
                        a3 = addiu(sp, 0x140);
                        a3 = addu(a3, a0);
                        lwc1(f0, a3, 0);
                        lwc1(f1, a1, 4);
                        c_lt_s(f1, f0);
                        if (cond(ctx)) {
                            backedge(ctx);
                        } else {
                            // 0x0046305c
                            charge(ctx, 14);
                            lw(t1, s3, 0);
                            a3 = addiu(sp, 0x14C);
                            a3 = addu(a3, a0);
                            t0 = addiu(t1, 8);
                            sw(t0, s3, 0);
                            sw(a1, t1, 8);
                            lw(t1, s3, 0);
                            lw(t0, t1, -4);
                            sw(t0, t1, 4);
                            lwc1(f0, a3, 0);
                            lwc1(f1, a1, 4);
                            c_le_s(f1, f0);
                            if (cond(ctx)) {
                                // 0x004633f4
                                charge(ctx, 8);
                                lw(t0, s3, 0);
                                a3 = srl(a0, 1);
                                a3 = sllv(t2, a3);
                                t1 = nor(a3, 0);
                                lw(a3, t0, 4);
                                a3 = a3 & t1;
                                sw(a3, t0, 4);
                                backedge(ctx);
                            } else {
                                // 0x00463094
                                charge(ctx, 1);
                            }
                            // 0x00463098
                            charge(ctx, 7);
                            a3 = addiu(sp, 0x158);
                            a3 = addu(a3, a0);
                            lwc1(f1, a1, 12);
                            lwc1(f0, a3, 0);
                            c_lt_s(f1, f0);
                            if (cond(ctx)) {
                                backedge(ctx);
                            } else {
                                // 0x004630b4
                                charge(ctx, 8);
                                lw(a1, s3, 0);
                                a0 = srl(a0, 1);
                                a0 = sllv(v1, a0);
                                a3 = nor(a0, 0);
                                lw(a0, a1, -4);
                                a0 = a0 & a3;
                                sw(a0, a1, -4);
                                backedge(ctx);
                            }
                        }
                    } else {
                        // 0x0046302c
                        charge(ctx, 2);
                        sw(a1, t0, 0);
                        backedge(ctx);
                    }
                }
                // 0x00462fd8
                charge(ctx, 4);
                lhu(a1, a1, 2);
                lw(fp, t0, 4);
                v1 = a0 & 0xFFFF;
            L_004630d8:
                charge(ctx, 6);
                s4 = a1 & 0xFFFF;
                v1 = v1 & 0xFFFF;
                s2 = addu(s4, v1);
                at = slt(s4, s2);
                if (at != 0) {
                    for (;;) {
                        // 0x004630f0: a leaf triangle (through the triangle map when there is one)
                        charge(ctx, 3);
                        lw(v1, s5, coll::kTriMap);
                        if (v1 == 0) {
                            // 0x00463110
                            charge(ctx, 1);
                            v0 = s4;
                        } else {
                            // 0x004630fc
                            charge(ctx, 5);
                            v0 = s4 & 0xFFFF;
                            v0 = sll(v0, 1);
                            v0 = addu(v1, v0);
                            lhu(v0, v0, 0);
                        }
                        // 0x00463114
                        charge(ctx, 23);
                        v0 = v0 & 0xFFFF;
                        sq(v0, sp, 0xB0);
                        v1 = sll(v0, 3);
                        lq(v0, sp, 0xC0);
                        v0 = addu(v0, v1);
                        lhu(a1, v0, 0);
                        lhu(a0, v0, 2);
                        lhu(v1, v0, 4);
                        v0 = sll(a1, 1);
                        a1 = addu(v0, a1);
                        v0 = sll(a0, 1);
                        a1 = sll(a1, 2);
                        a0 = addu(v0, a0);
                        lq(v0, sp, 0xD0);
                        a0 = sll(a0, 2);
                        s1 = addu(v0, a1);
                        s6 = addu(v0, a0);
                        v0 = sll(v1, 1);
                        v0 = addu(v0, v1);
                        v1 = sll(v0, 2);
                        lq(v0, sp, 0xD0);
                        s7 = addu(v0, v1);
                        if (fp != 0) {
                            // 0x00463418
                            charge(ctx, 9);
                            a0 = s0;
                            a1 = s1;
                            a2 = s6;
                            a3 = s7;
                            t0 = addiu(sp, 0x100);
                            t1 = addiu(sp, 0x2CC);
                            jal(ctx, 0x46342Cu, gen::fn_sub_4BAE00_004bae00);
                            if (v0 == 0) {
                                backedge(ctx);
                            L_00463308:
                                charge(ctx, 5);
                                v1 = addiu(s4, 1);
                                s4 = v1 & 0xFFFF;
                                v1 = slt(s4, s2);
                                if (v1 == 0) {
                                    goto L_0046331c;
                                }
                                backedge(ctx);
                                continue;
                            }
                            // 0x0046343c
                            charge(ctx, 2);
                            lwc1(f0, sp, 0x2CC);
                            backedge(ctx);
                        L_00463298:
                            charge(ctx, 28);
                            lq(v1, sp, 0xB0);
                            v0 = addiu(sp, 0x118);
                            lw(a0, sp, 0xFC);
                            lw(a2, sp, 0xF4);
                            mul_s(f0, f0, f20);
                            swc1(f0, sp, 0x2CC);
                            lwc1(f2, s1, 0);
                            lwc1(f1, s1, 4);
                            lwc1(f0, s1, 8);
                            lwc1(f12, sp, 0x2CC);
                            sw(v1, v0, 0);
                            v0 = addiu(sp, 0x10C);
                            swc1(f2, v0, 0);
                            v0 = addiu(sp, 0x11C);
                            sw(s1, v0, 0);
                            v0 = addiu(sp, 0x10C);
                            swc1(f1, v0, 4);
                            v0 = addiu(sp, 0x120);
                            sw(s6, v0, 0);
                            v0 = addiu(sp, 0x10C);
                            swc1(f0, v0, 8);
                            v0 = addiu(sp, 0x124);
                            sw(s7, v0, 0);
                            lw(v0, sp, 0xF8);
                            a1 = addiu(sp, 0x100);
                            jalr(ctx, 0x4632F8u, v0.u());
                            if (v0 == 0) {
                                break;
                            }
                            goto L_00463308;
                        }
                        // 0x00463170
                        charge(ctx, 37);
                        lwc1(f6, s1, 0);
                        v0 = addiu(sp, 0x104);
                        lwc1(f5, s6, 0);
                        lwc1(f0, s7, 0);
                        lwc1(f3, s1, 8);
                        lwc1(f1, s6, 8);
                        lwc1(f4, s1, 4);
                        lwc1(f2, s6, 4);
                        sub_s(f8, f5, f6);
                        sub_s(f5, f0, f6);
                        sub_s(f6, f1, f3);
                        lwc1(f0, s7, 8);
                        sub_s(f7, f2, f4);
                        lwc1(f1, s7, 4);
                        sub_s(f0, f0, f3);
                        mula_s(f7, f0);
                        sub_s(f4, f1, f4);
                        msub_s(f3, f6, f4);
                        mula_s(f6, f5);
                        msub_s(f1, f8, f0);
                        mula_s(f8, f4);
                        msub_s(f0, f7, f5);
                        swc1(f1, v0, 0);
                        mula_s(f1, f1);
                        v0 = addiu(sp, 0x108);
                        madda_s(f3, f3);
                        swc1(f0, v0, 0);
                        madd_s(f0, f0, f0);
                        sqrt_s(f5, f0);
                        mtc1(zero, f2);
                        swc1(f3, sp, 0x100);
                        c_le_s(f5, f2);
                        if (!cond(ctx)) {
                            // 0x00463204
                            charge(ctx, 7);
                            v0 = 0x3F800000;
                            mtc1(v0, f0);
                            div_s(f5, f0, f5);
                        }
                        // 0x00463220
                        charge(ctx, 30);
                        v0 = addiu(sp, 0x104);
                        lwc1(f1, v0, 0);
                        lwc1(f3, sp, 0x100);
                        lwc1(f2, s0, 4);
                        lwc1(f4, s0, 0);
                        lwc1(f7, s0, 8);
                        v0 = addiu(sp, 0x108);
                        lwc1(f0, v0, 0);
                        mul_s(f8, f3, f5);
                        mul_s(f1, f1, f5);
                        v0 = addiu(sp, 0x104);
                        swc1(f1, v0, 0);
                        mul_s(f0, f0, f5);
                        v0 = addiu(sp, 0x108);
                        swc1(f0, v0, 0);
                        swc1(f8, sp, 0x100);
                        lwc1(f5, v0, 0);
                        lwc1(f1, s1, 4);
                        lwc1(f3, s1, 0);
                        lwc1(f6, s1, 8);
                        v0 = addiu(sp, 0x104);
                        lwc1(f0, v0, 0);
                        sub_s(f1, f2, f1);
                        sub_s(f3, f4, f3);
                        mula_s(f1, f0);
                        sub_s(f6, f7, f6);
                        madda_s(f3, f8);
                        madd_s(f0, f6, f5);
                        swc1(f0, sp, 0x2CC);
                        lwc1(f0, sp, 0x2CC);
                        goto L_00463298;
                    }
                    break;
                }
            L_0046331c:
                charge(ctx, 7);
                lw(a0, s3, 0);
                lw(v1, sp, 0xE0);
                v1 = sltu(v1, a0);
                v1 = v1 ^ 0x1;
                v1 = v1 ^ 0x1;
                if (v1 == 0) {
                    goto L_00463338;
                }
                backedge(ctx);
            }
            goto L_00463454;
        }
    L_00463454:
        charge(ctx, 1);
        ld(ra, sp, 0xA0);
    }
    // 0x00463458 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x2D0);
    return;
L_00463360:
    charge(ctx, 8);
    lw(t0, sp, 0x130);
    lhu(v1, a1, 2);
    lw(a3, t0, 32);
    v1 = sll(v1, 4);
    a1 = addu(a3, v1);
    lbu(v1, a1, 1);
    t1 = a1;
    if (v1 == a2) {
        // 0x00463380: a subtree inside the sphere's box: its whole triangle range
        charge(ctx, 1);
        v1 = 255;
        for (;;) {
            // 0x00463384
            charge(ctx, 7);
            lhu(a0, t1, 2);
            a0 = sll(a0, 4);
            t1 = addu(a3, a0);
            lbu(a0, t1, 1);
            if (a0 != v1) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004633a0
    charge(ctx, 5);
    lbu(a2, a1, 9);
    a3 = addiu(a1, 8);
    a1 = 255;
    if (a2 == a1) {
        // 0x004633b4
        charge(ctx, 1);
        lw(a0, t0, 32);
        for (;;) {
            // 0x004633b8
            charge(ctx, 7);
            lhu(v1, a3, 2);
            v1 = sll(v1, 4);
            v1 = addu(a0, v1);
            lbu(a2, v1, 9);
            a3 = addiu(v1, 8);
            if (a2 != a1) {
                break;
            }
            backedge(ctx);
        }
        // 0x004633d4
        charge(ctx, 1);
    }
    // 0x004633d8
    charge(ctx, 7);
    lhu(v1, a3, 2);
    lhu(a1, t1, 2);
    fp = 0;
    v1 = addu(v1, a2);
    v1 = subu(v1, a1);
    v1 = v1 & 0xFFFF;
    backedge(ctx);
    goto L_004630d8;
}


// sub_463490 [collMorphLineIntersections] -- a line against a geometry blended between two morph targets (the atomic's interpolator)
// ($a0 = the geometry, $a1 = the interpolator (rw6::interp, atomic + 76), $a2 = the line, $a3 = the intersection,
// $t0 = the callback, $t1 = the data) The start / end morph targets' vertices; each triangle's vertices blended by
// recipTime x position (the start target's own vertices when both are the same), then the front-face line / triangle
// test; a hit fills the collision triangle (pointing at the blended copies on the stack) and calls the callback.
// 0x00463490 sub_463490 -- 1668 bytes; frame 0x120: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
void sub_463490(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16}, f17{ctx, 17}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00463490
    enter(ctx, 60);  // entry check point + this block's cycles
    sp = addiu(sp, -0x120);
    sd(ra, sp, 0xA0);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    s5 = a2;
    sq(s3, sp, 0x40);
    s4 = 0;
    sq(s2, sp, 0x30);
    s3 = addiu(sp, 0xF0);
    sq(s1, sp, 0x20);
    s2 = addiu(sp, 0xFC);
    sq(s0, sp, 0x10);
    s1 = addiu(sp, 0x108);
    swc1(f23, sp, 0xC);
    sw(a3, sp, 0xB8);
    swc1(f22, sp, 0x8);
    sw(t0, sp, 0xB4);
    swc1(f21, sp, 0x4);
    sw(t1, sp, 0xB0);
    swc1(f20, sp, 0x0);
    sw(a0, sp, 0xBC);
    lh(a3, a1, 4);
    lwc1(f5, a2, 12);
    lwc1(f4, a2, 0);
    lw(t0, a0, 92);
    lwc1(f3, a2, 16);
    lwc1(f2, a2, 4);
    lwc1(f1, a2, 20);
    lwc1(f0, a2, 8);
    v1 = sll(a3, 3);
    v1 = subu(v1, a3);
    v1 = sll(v1, 2);
    v1 = addu(v1, t0);
    sub_s(f20, f5, f4);
    lw(a2, v1, 20);
    sub_s(f22, f1, f0);
    v1 = addiu(sp, 0x114);
    sw(a2, v1, 0);
    lh(a2, a1, 6);
    lw(a3, a0, 92);
    v1 = sll(a2, 3);
    v1 = subu(v1, a2);
    v1 = sll(v1, 2);
    v1 = addu(v1, a3);
    lw(a2, v1, 20);
    v1 = addiu(sp, 0x118);
    sw(a2, v1, 0);
    lwc1(f1, a1, 12);
    v1 = addiu(sp, 0x11C);
    lwc1(f0, a1, 16);
    mul_s(f0, f1, f0);
    swc1(f0, v1, 0);
    lw(v1, a0, 16);
    lw(s0, a0, 44);
    at = slt(0, v1);
    sub_s(f21, f3, f2);
    if (at != 0) {
        // 0x00463580: each triangle: the same morph target -> its vertices; else the three blended vertices
        charge(ctx, 3);
        s6 = addiu(sp, 0xF4);
        s7 = addiu(sp, 0x100);
        fp = addiu(sp, 0x10C);
        for (;;) {
            // 0x0046358c
            charge(ctx, 6);
            v1 = addiu(sp, 0x118);
            lw(a0, v1, 0);
            v1 = addiu(sp, 0x114);
            lw(v1, v1, 0);
            if (v1 == a0) {
                // 0x00463948
                charge(ctx, 16);
                lhu(a3, s0, 0);
                lhu(a2, s0, 2);
                lhu(a1, s0, 4);
                a0 = sll(a3, 1);
                a3 = addu(a0, a3);
                a0 = sll(a2, 1);
                a0 = addu(a0, a2);
                a0 = sll(a0, 2);
                a2 = sll(a3, 2);
                s2 = addu(v1, a0);
                s3 = addu(v1, a2);
                a0 = sll(a1, 1);
                a0 = addu(a0, a1);
                a0 = sll(a0, 2);
                s1 = addu(v1, a0);
                backedge(ctx);
            } else {
                // 0x004635a4
                charge(ctx, 123);
                a1 = addiu(sp, 0x11C);
                lhu(a2, s0, 0);
                lwc1(f0, a1, 0);
                a1 = sll(a2, 1);
                a1 = addu(a1, a2);
                a1 = sll(a1, 2);
                a2 = addu(v1, a1);
                a1 = addu(a0, a1);
                lwc1(f2, a1, 0);
                lwc1(f1, a2, 0);
                sub_s(f1, f2, f1);
                swc1(f1, sp, 0xF0);
                lwc1(f1, sp, 0xF0);
                lwc1(f3, a1, 4);
                lwc1(f2, a2, 4);
                mul_s(f4, f1, f0);
                sub_s(f1, f3, f2);
                swc1(f1, s6, 0);
                lwc1(f1, s6, 0);
                lwc1(f3, a1, 8);
                lwc1(f2, a2, 8);
                mul_s(f1, f1, f0);
                a1 = addiu(sp, 0xF8);
                sub_s(f2, f3, f2);
                swc1(f1, s6, 0);
                mul_s(f1, f2, f0);
                swc1(f1, a1, 0);
                swc1(f4, sp, 0xF0);
                lwc1(f3, a2, 0);
                lwc1(f2, s6, 0);
                lwc1(f1, a1, 0);
                add_s(f3, f4, f3);
                swc1(f3, sp, 0xF0);
                lwc1(f3, a2, 4);
                add_s(f2, f2, f3);
                swc1(f2, s6, 0);
                lwc1(f2, a2, 8);
                add_s(f1, f1, f2);
                swc1(f1, a1, 0);
                lhu(a2, s0, 2);
                a1 = sll(a2, 1);
                a1 = addu(a1, a2);
                a1 = sll(a1, 2);
                a3 = addu(v1, a1);
                a2 = addu(a0, a1);
                lwc1(f2, a2, 0);
                a1 = addiu(sp, 0xFC);
                lwc1(f1, a3, 0);
                sub_s(f1, f2, f1);
                swc1(f1, a1, 0);
                lwc1(f1, a1, 0);
                lwc1(f3, a2, 4);
                lwc1(f2, a3, 4);
                mul_s(f4, f1, f0);
                a1 = addiu(sp, 0x104);
                sub_s(f2, f3, f2);
                swc1(f2, s7, 0);
                lwc1(f1, s7, 0);
                lwc1(f3, a2, 8);
                lwc1(f2, a3, 8);
                mul_s(f1, f1, f0);
                sub_s(f2, f3, f2);
                swc1(f1, s7, 0);
                mul_s(f1, f2, f0);
                swc1(f1, a1, 0);
                a1 = addiu(sp, 0xFC);
                swc1(f4, a1, 0);
                lwc1(f3, a3, 0);
                a1 = addiu(sp, 0x104);
                lwc1(f1, a1, 0);
                lwc1(f2, s7, 0);
                add_s(f3, f4, f3);
                a1 = addiu(sp, 0xFC);
                swc1(f3, a1, 0);
                lwc1(f3, a3, 4);
                a1 = addiu(sp, 0x104);
                add_s(f2, f2, f3);
                swc1(f2, s7, 0);
                lwc1(f2, a3, 8);
                add_s(f1, f1, f2);
                swc1(f1, a1, 0);
                lhu(a2, s0, 4);
                a1 = sll(a2, 1);
                a1 = addu(a1, a2);
                a2 = sll(a1, 2);
                a1 = addu(v1, a2);
                a0 = addu(a0, a2);
                lwc1(f2, a0, 0);
                v1 = addiu(sp, 0x108);
                lwc1(f1, a1, 0);
                sub_s(f1, f2, f1);
                swc1(f1, v1, 0);
                lwc1(f1, v1, 0);
                lwc1(f3, a0, 4);
                lwc1(f2, a1, 4);
                v1 = addiu(sp, 0x110);
                sub_s(f2, f3, f2);
                swc1(f2, fp, 0x0);
                mul_s(f3, f1, f0);
                lwc1(f1, fp, 0x0);
                lwc1(f4, a0, 8);
                lwc1(f2, a1, 8);
                mul_s(f1, f1, f0);
                sub_s(f2, f4, f2);
                mul_s(f0, f2, f0);
                swc1(f0, v1, 0);
                v1 = addiu(sp, 0x108);
                swc1(f1, fp, 0x0);
                swc1(f3, v1, 0);
                lwc1(f2, a1, 0);
                v1 = addiu(sp, 0x110);
                lwc1(f0, v1, 0);
                lwc1(f1, fp, 0x0);
                add_s(f2, f3, f2);
                v1 = addiu(sp, 0x108);
                swc1(f2, v1, 0);
                lwc1(f2, a1, 4);
                v1 = addiu(sp, 0x110);
                add_s(f1, f1, f2);
                swc1(f1, fp, 0x0);
                lwc1(f1, a1, 8);
                add_s(f0, f0, f1);
                swc1(f0, v1, 0);
            }
            // 0x00463790
            charge(ctx, 30);
            v1 = 0x322B0000;
            lwc1(f7, s3, 0);
            v1 = v1 | 0xCC77;
            lwc1(f0, s1, 0);
            lwc1(f5, s3, 8);
            lwc1(f2, s2, 8);
            lwc1(f4, s2, 0);
            lwc1(f6, s3, 4);
            lwc1(f3, s2, 4);
            sub_s(f11, f0, f7);
            sub_s(f16, f2, f5);
            lwc1(f0, s1, 8);
            lwc1(f2, s1, 4);
            sub_s(f15, f3, f6);
            sub_s(f13, f0, f5);
            sub_s(f12, f2, f6);
            mula_s(f21, f13);
            msub_s(f8, f22, f12);
            mula_s(f22, f11);
            msub_s(f9, f20, f13);
            mula_s(f20, f12);
            msub_s(f10, f21, f11);
            sub_s(f14, f4, f7);
            mula_s(f15, f9);
            madda_s(f14, f8);
            mtc1(v1, f1);
            madd_s(f0, f16, f10);
            c_le_s(f0, f1);
            a0 = 1;
            if (cond(ctx)) {
                // 0x00463808
                charge(ctx, 1);
                a0 = 0;
            }
            // 0x0046380c
            charge(ctx, 2);
            if (a0 != 0) {
                // 0x00463814
                charge(ctx, 18);
                v1 = 0x37270000;
                a0 = 1;
                v1 = v1 | 0xC5AC;
                lwc1(f1, s5, 0);
                mtc1(v1, f3);
                neg_s(f2, f0);
                mul_s(f17, f3, f2);
                sub_s(f4, f1, f7);
                lwc1(f2, s5, 4);
                lwc1(f1, s5, 8);
                sub_s(f6, f2, f6);
                mula_s(f6, f9);
                sub_s(f1, f1, f5);
                madda_s(f4, f8);
                madd_s(f5, f1, f10);
                c_lt_s(f5, f17);
                sub_s(f7, f0, f17);
                if (cond(ctx)) {
                    // 0x0046385c
                    charge(ctx, 1);
                    a0 = 0;
                }
                // 0x00463860
                charge(ctx, 2);
                if (a0 != 0) {
                    // 0x00463868
                    charge(ctx, 3);
                    c_le_s(f5, f7);
                    a0 = 1;
                    if (!cond(ctx)) {
                        // 0x00463874
                        charge(ctx, 1);
                        a0 = 0;
                    }
                }
                // 0x00463878
                charge(ctx, 2);
                if (a0 != 0) {
                    // 0x00463880
                    charge(ctx, 12);
                    mula_s(f6, f16);
                    msub_s(f2, f1, f15);
                    mula_s(f1, f14);
                    msub_s(f3, f4, f16);
                    mula_s(f4, f15);
                    msub_s(f4, f6, f14);
                    mula_s(f21, f3);
                    madda_s(f20, f2);
                    madd_s(f1, f22, f4);
                    c_lt_s(f1, f17);
                    a0 = 1;
                    if (cond(ctx)) {
                        // 0x004638b0
                        charge(ctx, 1);
                        a0 = 0;
                    }
                    // 0x004638b4
                    charge(ctx, 2);
                    if (a0 != 0) {
                        // 0x004638bc
                        charge(ctx, 4);
                        add_s(f1, f5, f1);
                        c_le_s(f1, f7);
                        a0 = 1;
                        if (!cond(ctx)) {
                            // 0x004638cc
                            charge(ctx, 1);
                            a0 = 0;
                        }
                    }
                    // 0x004638d0
                    charge(ctx, 2);
                    if (a0 != 0) {
                        // 0x004638d8
                        charge(ctx, 6);
                        mula_s(f12, f3);
                        madda_s(f11, f2);
                        madd_s(f23, f13, f4);
                        c_lt_s(f23, f17);
                        a0 = 1;
                        if (cond(ctx)) {
                            // 0x004638f0
                            charge(ctx, 1);
                            a0 = 0;
                        }
                        // 0x004638f4
                        charge(ctx, 2);
                        if (a0 != 0) {
                            // 0x004638fc
                            charge(ctx, 3);
                            c_le_s(f23, f7);
                            a0 = 1;
                            if (!cond(ctx)) {
                                // 0x00463908
                                charge(ctx, 1);
                                a0 = 0;
                            }
                        }
                        // 0x0046390c
                        charge(ctx, 2);
                        if (a0 != 0) {
                            // 0x00463914
                            charge(ctx, 3);
                            div_s(f23, f23, f0);
                        }
                    }
                }
            }
            // 0x00463920
            charge(ctx, 2);
            if (a0 != 0) {
                // 0x00463988
                charge(ctx, 54);
                v0 = addiu(sp, 0xCC);
                lwc1(f3, s3, 0);
                lwc1(f1, s3, 4);
                lwc1(f0, s3, 8);
                mtc1(zero, f2);
                swc1(f3, v0, 0);
                v0 = addiu(sp, 0xD8);
                sw(s4, v0, 0);
                v0 = addiu(sp, 0xCC);
                swc1(f1, v0, 4);
                v0 = addiu(sp, 0xDC);
                sw(s3, v0, 0);
                v0 = addiu(sp, 0xCC);
                swc1(f0, v0, 8);
                v0 = addiu(sp, 0xE0);
                sw(s2, v0, 0);
                v0 = addiu(sp, 0xE4);
                sw(s1, v0, 0);
                lwc1(f6, s3, 0);
                v0 = addiu(sp, 0xC4);
                lwc1(f5, s2, 0);
                lwc1(f0, s1, 0);
                lwc1(f3, s3, 8);
                lwc1(f1, s2, 8);
                lwc1(f8, s3, 4);
                lwc1(f4, s2, 4);
                sub_s(f9, f5, f6);
                sub_s(f5, f0, f6);
                sub_s(f6, f1, f3);
                lwc1(f0, s1, 8);
                lwc1(f1, s1, 4);
                sub_s(f7, f4, f8);
                sub_s(f0, f0, f3);
                sub_s(f4, f1, f8);
                mula_s(f7, f0);
                msub_s(f3, f6, f4);
                mula_s(f6, f5);
                msub_s(f1, f9, f0);
                mula_s(f9, f4);
                msub_s(f0, f7, f5);
                swc1(f1, v0, 0);
                mula_s(f1, f1);
                v0 = addiu(sp, 0xC8);
                madda_s(f3, f3);
                swc1(f0, v0, 0);
                swc1(f3, sp, 0xC0);
                madd_s(f0, f0, f0);
                sqrt_s(f3, f0);
                c_le_s(f3, f2);
                if (!cond(ctx)) {
                    // 0x00463a60
                    charge(ctx, 8);
                    v0 = 0x3F800000;
                    mtc1(v0, f0);
                    div_s(f3, f0, f3);
                }
                // 0x00463a80
                charge(ctx, 21);
                v0 = addiu(sp, 0xC4);
                lwc1(f1, v0, 0);
                lw(a0, sp, 0xB8);
                lwc1(f2, sp, 0xC0);
                lw(a2, sp, 0xB0);
                mov_s(f12, f23);
                a1 = addiu(sp, 0xC0);
                v0 = addiu(sp, 0xC8);
                lwc1(f0, v0, 0);
                mul_s(f2, f2, f3);
                mul_s(f1, f1, f3);
                v0 = addiu(sp, 0xC4);
                swc1(f1, v0, 0);
                mul_s(f0, f0, f3);
                v0 = addiu(sp, 0xC8);
                swc1(f0, v0, 0);
                lw(v0, sp, 0xB4);
                jt = v0.u();  // the target, read before the delay slot
                link(ctx, 0x463AC4u);  // $ra = the return address
                swc1(f2, sp, 0xC0);
                call_ptr(ctx, jt);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                goto L_00463928;
            }
        L_00463928:
            charge(ctx, 6);
            lw(v1, sp, 0xBC);
            s4 = addiu(s4, 1);
            lw(v1, v1, 16);
            v1 = slt(s4, v1);
            s0 = addiu(s0, 8);
            if (v1 == 0) {
                goto L_00463940;
            }
            backedge(ctx);
        }
        // 0x00463ad4
        charge(ctx, 1);
        ld(ra, sp, 0xA0);
        // 0x00463ad8 (the shared epilogue, written out on this path)
        charge(ctx, 15);
        lwc1(f23, sp, 0xC);
        lq(fp, sp, 0x90);
        lwc1(f22, sp, 0x8);
        lq(s7, sp, 0x80);
        lwc1(f21, sp, 0x4);
        lq(s6, sp, 0x70);
        lwc1(f20, sp, 0x0);
        lq(s5, sp, 0x60);
        lq(s4, sp, 0x50);
        lq(s3, sp, 0x40);
        lq(s2, sp, 0x30);
        lq(s1, sp, 0x20);
        lq(s0, sp, 0x10);
        sp = addiu(sp, 0x120);
        return;
    }
L_00463940:
    charge(ctx, 2);
    ld(ra, sp, 0xA0);
    // 0x00463ad8 (the shared epilogue, written out on this path)
    charge(ctx, 15);
    lwc1(f23, sp, 0xC);
    lq(fp, sp, 0x90);
    lwc1(f22, sp, 0x8);
    lq(s7, sp, 0x80);
    lwc1(f21, sp, 0x4);
    lq(s6, sp, 0x70);
    lwc1(f20, sp, 0x0);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x120);
}


// sub_463B20 [collMorphSphereIntersections] -- a sphere against a geometry blended between two morph targets (the atomic's interpolator)
// ($a0 = the geometry, $a1 = the interpolator (atomic + 76), $a2 = the sphere, $a3 = the intersection, $t0 = the
// callback, $t1 = the data) Each triangle's vertices blended by recipTime x position (or the start target's own),
// then sub_4BAE00; a hit: the collision triangle (pointing at the blended copies) and the callback with the distance
// / radius in $f12 (0 stops).
// 0x00463B20 sub_463B20 -- 1016 bytes; frame 0x140: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
void sub_463B20(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f12{ctx, 12}, f20{ctx, 20};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00463b20: 1 / radius, the start / end targets' vertices, the blend factor (recipTime x position)
    enter(ctx, 53);  // entry check point + this block's cycles
    sp = addiu(sp, -0x140);
    v1 = 0x3F800000;
    sd(ra, sp, 0xA0);
    mtc1(v1, f1);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    fp = addiu(sp, 0x10C);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    s5 = addiu(sp, 0x100);
    sq(s3, sp, 0x40);
    s4 = fp;
    sq(s2, sp, 0x30);
    s3 = addiu(sp, 0x118);
    sq(s1, sp, 0x20);
    s2 = 0;
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    sw(a3, sp, 0xC4);
    lwc1(f0, a2, 12);
    sw(a2, sp, 0xC8);
    lw(a3, a0, 92);
    sw(t0, sp, 0xC0);
    sw(t1, sp, 0xBC);
    lh(a2, a1, 4);
    div_s(f20, f1, f0);
    v1 = sll(a2, 3);
    v1 = subu(v1, a2);
    v1 = sll(v1, 2);
    v1 = addu(v1, a3);
    lw(a2, v1, 20);
    v1 = addiu(sp, 0x124);
    sw(a2, v1, 0);
    lh(a2, a1, 6);
    lw(a3, a0, 92);
    v1 = sll(a2, 3);
    v1 = subu(v1, a2);
    v1 = sll(v1, 2);
    v1 = addu(v1, a3);
    lw(a2, v1, 20);
    v1 = addiu(sp, 0x128);
    sw(a2, v1, 0);
    lwc1(f1, a1, 12);
    v1 = addiu(sp, 0x12C);
    lwc1(f0, a1, 16);
    mul_s(f0, f1, f0);
    swc1(f0, v1, 0);
    lw(v1, a0, 16);
    lw(s1, a0, 44);
    at = slt(0, v1);
    sw(a0, sp, 0xCC);
    if (at != 0) {
        // 0x00463bf4
        charge(ctx, 3);
        s0 = addiu(sp, 0x104);
        s6 = addiu(sp, 0x110);
        s7 = addiu(sp, 0x11C);
        for (;;) {
            // 0x00463c00: each triangle: the same morph target -> its own vertices
            charge(ctx, 6);
            v0 = addiu(sp, 0x128);
            lw(v1, v0, 0);
            v0 = addiu(sp, 0x124);
            lw(v0, v0, 0);
            if (v0 == v1) {
                // 0x00463e38
                charge(ctx, 16);
                lhu(a2, s1, 0);
                lhu(a1, s1, 2);
                lhu(a0, s1, 4);
                v1 = sll(a2, 1);
                a2 = addu(v1, a2);
                v1 = sll(a1, 1);
                v1 = addu(v1, a1);
                v1 = sll(v1, 2);
                a1 = sll(a2, 2);
                s4 = addu(v0, v1);
                s5 = addu(v0, a1);
                v1 = sll(a0, 1);
                v1 = addu(v1, a0);
                v1 = sll(v1, 2);
                s3 = addu(v0, v1);
                backedge(ctx);
            } else {
                // 0x00463c18: else the three vertices blended on the stack
                charge(ctx, 118);
                a0 = addiu(sp, 0x12C);
                lhu(a1, s1, 0);
                lwc1(f0, a0, 0);
                a0 = sll(a1, 1);
                a0 = addu(a0, a1);
                a0 = sll(a0, 2);
                a1 = addu(v0, a0);
                a0 = addu(v1, a0);
                lwc1(f2, a0, 0);
                lwc1(f1, a1, 0);
                sub_s(f1, f2, f1);
                swc1(f1, sp, 0x100);
                lwc1(f1, sp, 0x100);
                lwc1(f3, a0, 4);
                lwc1(f2, a1, 4);
                mul_s(f4, f1, f0);
                sub_s(f1, f3, f2);
                swc1(f1, s0, 0);
                lwc1(f1, s0, 0);
                lwc1(f3, a0, 8);
                lwc1(f2, a1, 8);
                mul_s(f1, f1, f0);
                a0 = addiu(sp, 0x108);
                sub_s(f2, f3, f2);
                swc1(f1, s0, 0);
                mul_s(f1, f2, f0);
                swc1(f1, a0, 0);
                swc1(f4, sp, 0x100);
                lwc1(f3, a1, 0);
                lwc1(f2, s0, 0);
                lwc1(f1, a0, 0);
                add_s(f3, f4, f3);
                swc1(f3, sp, 0x100);
                lwc1(f3, a1, 4);
                add_s(f2, f2, f3);
                swc1(f2, s0, 0);
                lwc1(f2, a1, 8);
                add_s(f1, f1, f2);
                swc1(f1, a0, 0);
                lhu(a1, s1, 2);
                a0 = sll(a1, 1);
                a0 = addu(a0, a1);
                a0 = sll(a0, 2);
                a1 = addu(v0, a0);
                a0 = addu(v1, a0);
                lwc1(f2, a0, 0);
                lwc1(f1, a1, 0);
                sub_s(f1, f2, f1);
                swc1(f1, fp, 0x0);
                lwc1(f1, fp, 0x0);
                lwc1(f3, a0, 4);
                lwc1(f2, a1, 4);
                mul_s(f4, f1, f0);
                sub_s(f2, f3, f2);
                swc1(f2, s6, 0);
                lwc1(f1, s6, 0);
                lwc1(f3, a0, 8);
                lwc1(f2, a1, 8);
                mul_s(f1, f1, f0);
                a0 = addiu(sp, 0x114);
                sub_s(f2, f3, f2);
                swc1(f1, s6, 0);
                mul_s(f1, f2, f0);
                swc1(f1, a0, 0);
                swc1(f4, fp, 0x0);
                lwc1(f3, a1, 0);
                lwc1(f2, s6, 0);
                lwc1(f1, a0, 0);
                add_s(f3, f4, f3);
                swc1(f3, fp, 0x0);
                lwc1(f3, a1, 4);
                add_s(f2, f2, f3);
                swc1(f2, s6, 0);
                lwc1(f2, a1, 8);
                add_s(f1, f1, f2);
                swc1(f1, a0, 0);
                lhu(a1, s1, 4);
                a0 = sll(a1, 1);
                a0 = addu(a0, a1);
                a1 = sll(a0, 2);
                a0 = addu(v0, a1);
                v1 = addu(v1, a1);
                lwc1(f2, v1, 0);
                v0 = addiu(sp, 0x118);
                lwc1(f1, a0, 0);
                sub_s(f1, f2, f1);
                swc1(f1, v0, 0);
                lwc1(f1, v0, 0);
                lwc1(f3, v1, 4);
                lwc1(f2, a0, 4);
                v0 = addiu(sp, 0x120);
                sub_s(f2, f3, f2);
                swc1(f2, s7, 0);
                mul_s(f3, f1, f0);
                lwc1(f1, s7, 0);
                lwc1(f4, v1, 8);
                lwc1(f2, a0, 8);
                mul_s(f1, f1, f0);
                sub_s(f2, f4, f2);
                mul_s(f0, f2, f0);
                swc1(f0, v0, 0);
                v0 = addiu(sp, 0x118);
                swc1(f1, s7, 0);
                swc1(f3, v0, 0);
                lwc1(f2, a0, 0);
                v0 = addiu(sp, 0x120);
                lwc1(f0, v0, 0);
                lwc1(f1, s7, 0);
                add_s(f2, f3, f2);
                v0 = addiu(sp, 0x118);
                swc1(f2, v0, 0);
                lwc1(f2, a0, 4);
                v0 = addiu(sp, 0x120);
                add_s(f1, f1, f2);
                swc1(f1, s7, 0);
                lwc1(f1, a0, 8);
                add_s(f0, f0, f1);
                swc1(f0, v0, 0);
            }
            // 0x00463df0: the sphere / triangle test (sub_4BAE00)
            charge(ctx, 9);
            lw(a0, sp, 0xC8);
            a1 = s5;
            a2 = s4;
            a3 = s3;
            t0 = addiu(sp, 0xD0);
            t1 = addiu(sp, 0x13C);
            jal(ctx, 0x463E04u, gen::fn_sub_4BAE00_004bae00);
            if (v0 == 0) {
                // 0x00463e14
                charge(ctx, 1);
                goto L_00463e18;
            }
            // 0x00463e78: a hit: the collision triangle; the callback (a0 = the intersection, a1 = the collision triangle, $f12 = the distance, a2 = the data); 0 ends the walk
            charge(ctx, 27);
            v0 = addiu(sp, 0xE8);
            lwc1(f3, s5, 0);
            lw(a0, sp, 0xC4);
            lwc1(f2, s5, 4);
            lw(a2, sp, 0xBC);
            lwc1(f1, s5, 8);
            a1 = addiu(sp, 0xD0);
            lwc1(f0, sp, 0x13C);
            sw(s2, v0, 0);
            v0 = addiu(sp, 0xEC);
            sw(s5, v0, 0);
            mul_s(f12, f0, f20);
            v0 = addiu(sp, 0xDC);
            swc1(f3, v0, 0);
            v0 = addiu(sp, 0xF0);
            sw(s4, v0, 0);
            v0 = addiu(sp, 0xDC);
            swc1(f2, v0, 4);
            v0 = addiu(sp, 0xF4);
            sw(s3, v0, 0);
            v0 = addiu(sp, 0xDC);
            swc1(f1, v0, 8);
            lw(v0, sp, 0xC0);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x463ED4u);  // $ra = the return address
            swc1(f12, sp, 0x13C);
            call_ptr(ctx, jt);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        L_00463e18:
            charge(ctx, 6);
            lw(v1, sp, 0xCC);
            s2 = addiu(s2, 1);
            lw(v1, v1, 16);
            v1 = slt(s2, v1);
            s1 = addiu(s1, 8);
            if (v1 == 0) {
                goto L_00463e30;
            }
            backedge(ctx);
        }
        // 0x00463ee4
        charge(ctx, 1);
        ld(ra, sp, 0xA0);
        // 0x00463ee8 (the shared epilogue, written out on this path)
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
        sp = addiu(sp, 0x140);
        return;
    }
L_00463e30:
    charge(ctx, 2);
    ld(ra, sp, 0xA0);
    // 0x00463ee8 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x140);
}


// sub_463F20 [collAtomicSphereIntersections] -- an atomic's sphere test: the sphere into the atomic's space, then its geometry's test
// ($a0 = the atomic, $a1 = the sphere, $a2 = the intersection, $a3 = the callback, $t0 = the data) The frame's LTM
// (sub_4CB2F0) inverted (sub_4C32A0); the centre transformed (sub_4C6C20) and the radius scaled by the length of the
// transformed axis; one morph target -> sub_462BB0, more -> sub_463B20 with the interpolator at atomic + 76.
// 0x00463F20 sub_463F20 -- 248 bytes; frame 0xC0: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_463F20(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x00463f20
    enter(ctx, 38);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a1;
    sq(s3, sp, 0x30);
    s4 = a2;
    sq(s2, sp, 0x20);
    s3 = a3;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, 24);
    s0 = a0;
    lw(a0, a0, 4);
    s2 = t0;
    jal(ctx, 0x463F58u, gen::fn_sub_4CB2F0_004cb2f0);
    a1 = v0;
    a0 = addiu(sp, 0x70);
    jal(ctx, 0x463F64u, gen::fn_sub_4C32A0_004c32a0);
    a0 = addiu(sp, 0xB0);
    a1 = s5;
    a2 = 1;
    a3 = addiu(sp, 0x70);
    jal(ctx, 0x463F78u, gen::fn_sub_4C6C20_004c6c20);
    lwc1(f3, sp, 0x94);
    lwc1(f2, sp, 0x90);
    lwc1(f1, sp, 0x98);
    lwc1(f0, s5, 12);
    mula_s(f3, f3);
    madda_s(f2, f2);
    madd_s(f1, f1, f1);
    sqrt_s(f1, f1);
    mul_s(f0, f1, f0);
    swc1(f0, sp, 0xBC);
    lw(v0, s1, 24);
    at = slti(v0, 2);
    if (at != 0) {
        // 0x00463fdc: one morph target: sub_462BB0 (the collision tree or every triangle)
        charge(ctx, 7);
        a0 = s1;
        a2 = s4;
        a3 = s3;
        t0 = s2;
        a1 = addiu(sp, 0xB0);
        jal(ctx, 0x463FECu, gen::fn_sub_462BB0_00462bb0);
        ld(ra, sp, 0x60);
    } else {
        // 0x00463fb8: two or more: sub_463B20 with the interpolator at atomic + 76
        charge(ctx, 9);
        a0 = s1;
        a1 = addiu(s0, 76);
        a3 = s4;
        t0 = s3;
        t1 = s2;
        a2 = addiu(sp, 0xB0);
        jal(ctx, 0x463FCCu, gen::fn_sub_463B20_00463b20);
        ld(ra, sp, 0x60);
    }
    // 0x00463ff8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xC0);
}


// sub_4A38F0 [ps2AllMatSetTriListBatch] -- the PS2AllMat node's tri-list batch: kind 3
// ($a0 = the node, $a1 = the stride, $a2 = the vertices per batch (>= 3), $a3 = the triangles per batch) Fails (0) without a node, with a non-positive count, or when the node's initialisation data already has another primitive kind; creates the 64-byte data on first use (cleared, stride 4, batch 69 x 4) and stores the batch sizes, the stride and the kind. Returns the node.
// Batch size = stride x 3 x triangles; batch words = vertices x stride (mult1).
// 0x004A38F0 sub_4A38F0 -- 392 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4A38F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004a38f0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    s1 = a2;
    s0 = a3;
    if (s3 == 0) {
        // 0x004a3940
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004a391c
        charge(ctx, 2);
        if (i64(s2) <= 0) {
            // 0x004a3948
            charge(ctx, 2);
            v0 = 0;
        } else {
            // 0x004a3924
            charge(ctx, 3);
            v0 = slti(s1, 3);
            if (v0 != 0) {
                // 0x004a3950
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x004a3930
                charge(ctx, 2);
                if (i64(s0) > 0) {
                    // 0x004a3958: the existing data must not have the tri-strip / point kinds (bits 0x1C)
                    charge(ctx, 4);
                    jal(ctx, 0x4A3958u, gen::fn_sub_4F3F70_004f3f70);
                    if (v0 != 0) {
                        // 0x004a3968
                        charge(ctx, 4);
                        lw(v1, v0, allmatinit::kPrimFlags);
                        v1 = v1 & 0x1C;
                        if (v1 == 0) {
                            goto L_004a3980;
                        }
                        // 0x004a3978
                        charge(ctx, 2);
                        v0 = 0;
                        // 0x004a3a5c (the shared epilogue, written out on this path)
                        charge(ctx, 7);
                        ld(ra, sp, 0x40);
                        lq(s3, sp, 0x30);
                        lq(s2, sp, 0x20);
                        lq(s1, sp, 0x10);
                        lq(s0, sp, 0x0);
                        sp = addiu(sp, 0x50);
                        return;
                    }
                L_004a3980:
                    charge(ctx, 2);
                    if (v0 != 0) {
                        // 0x004a3988
                        charge(ctx, 1);
                        v1 = sll(s0, 1);
                        goto L_004a398c;
                    }
                    // 0x004a39b4: first use: create the 64-byte data (sub_4F3EC0) and its defaults
                    charge(ctx, 5);
                    a0 = s3;
                    a1 = 64;
                    jal(ctx, 0x4A39B8u, gen::fn_sub_4F3EC0_004f3ec0);
                    if (v0 == 0) {
                        // 0x004a3a44
                        charge(ctx, 2);
                        a1 = 0;
                        backedge(ctx);
                    } else {
                        // 0x004a39c8
                        charge(ctx, 2);
                        a1 = 0;
                        a0 = v0;
                        for (;;) {
                            // 0x004a39d0
                            charge(ctx, 9);
                            sw(zero, a0, 0);
                            a1 = addiu(a1, 5);
                            sw(zero, a0, 4);
                            v1 = sltiu(a1, 10);
                            sw(zero, a0, 8);
                            sw(zero, a0, 12);
                            sw(zero, a0, 16);
                            a0 = addiu(a0, 20);
                            if (v1 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004a39f4
                        charge(ctx, 16);
                        sw(zero, v0, allmatinit::kPrimFlags);
                        v1 = 4;
                        sw(v1, v0, allmatinit::kStride);
                        a1 = 1;
                        lw(a0, v0, allmatinit::kStride);
                        v1 = sll(a0, 4);
                        v1 = addu(v1, a0);
                        v1 = sll(v1, 2);
                        v1 = addu(v1, a0);
                        sw(v1, v0, allmatinit::kBatchSize);
                        lw(a0, v0, allmatinit::kStride);
                        v1 = sll(a0, 4);
                        v1 = addu(v1, a0);
                        v1 = sll(v1, 2);
                        v1 = addu(v1, a0);
                        sw(v1, v0, allmatinit::kBatchWords);
                    }
                    // 0x004a3a34
                    charge(ctx, 2);
                    if (a1 != 0) {
                        // 0x004a3a4c
                        charge(ctx, 4);
                        a0 = s3;
                        jal(ctx, 0x4A3A4Cu, gen::fn_sub_4F3F70_004f3f70);
                        v1 = sll(s0, 1);
                        backedge(ctx);
                    L_004a398c:
                        charge(ctx, 10);
                        v1 = addu(v1, s0);
                        mult(v1, s2, v1);
                        sw(v1, v0, allmatinit::kBatchSize);
                        mult1(v1, s1, s2);
                        sw(v1, v0, allmatinit::kBatchWords);
                        v1 = 3;
                        sw(s2, v0, allmatinit::kStride);
                        sw(v1, v0, allmatinit::kPrimFlags);
                        v0 = s3;
                    } else {
                        // 0x004a3a3c
                        charge(ctx, 2);
                        v0 = 0;
                    }
                } else {
                    // 0x004a3938
                    charge(ctx, 2);
                    v0 = 0;
                }
            }
        }
    }
    // 0x004a3a5c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}


// sub_4A3A80 [ps2AllMatSetTriStripBatch] -- the PS2AllMat node's tri-strip batch: kind 12
// ($a0 = the node, $a1 = the stride, $a2 = the vertices per batch (>= 2), $a3 = the strip length) Fails (0) without a node, with a non-positive count, or when the node's initialisation data already has another primitive kind; creates the 64-byte data on first use (cleared, stride 4, batch 69 x 4) and stores the batch sizes, the stride and the kind. Returns the node.
// Batch size = stride x 2 x length; batch words = vertices x stride.
// 0x004A3A80 sub_4A3A80 -- 388 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4A3A80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004a3a80
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    s1 = a2;
    s0 = a3;
    if (s3 == 0) {
        // 0x004a3ad0
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004a3aac
        charge(ctx, 2);
        if (i64(s2) <= 0) {
            // 0x004a3ad8
            charge(ctx, 2);
            v0 = 0;
        } else {
            // 0x004a3ab4
            charge(ctx, 3);
            v0 = slti(s1, 2);
            if (v0 != 0) {
                // 0x004a3ae0
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x004a3ac0
                charge(ctx, 2);
                if (i64(s0) > 0) {
                    // 0x004a3ae8
                    charge(ctx, 4);
                    jal(ctx, 0x4A3AE8u, gen::fn_sub_4F3F70_004f3f70);
                    if (v0 != 0) {
                        // 0x004a3af8
                        charge(ctx, 4);
                        lw(v1, v0, allmatinit::kPrimFlags);
                        v1 = v1 & 0x13;
                        if (v1 == 0) {
                            goto L_004a3b10;
                        }
                        // 0x004a3b08
                        charge(ctx, 2);
                        v0 = 0;
                        // 0x004a3be8 (the shared epilogue, written out on this path)
                        charge(ctx, 7);
                        ld(ra, sp, 0x40);
                        lq(s3, sp, 0x30);
                        lq(s2, sp, 0x20);
                        lq(s1, sp, 0x10);
                        lq(s0, sp, 0x0);
                        sp = addiu(sp, 0x50);
                        return;
                    }
                L_004a3b10:
                    charge(ctx, 2);
                    if (v0 != 0) {
                        // 0x004a3b18
                        charge(ctx, 1);
                        v1 = sll(s0, 1);
                        goto L_004a3b1c;
                    }
                    // 0x004a3b40
                    charge(ctx, 5);
                    a0 = s3;
                    a1 = 64;
                    jal(ctx, 0x4A3B44u, gen::fn_sub_4F3EC0_004f3ec0);
                    if (v0 == 0) {
                        // 0x004a3bd0
                        charge(ctx, 2);
                        a1 = 0;
                        backedge(ctx);
                    } else {
                        // 0x004a3b54
                        charge(ctx, 2);
                        a1 = 0;
                        a0 = v0;
                        for (;;) {
                            // 0x004a3b5c
                            charge(ctx, 9);
                            sw(zero, a0, 0);
                            a1 = addiu(a1, 5);
                            sw(zero, a0, 4);
                            v1 = sltiu(a1, 10);
                            sw(zero, a0, 8);
                            sw(zero, a0, 12);
                            sw(zero, a0, 16);
                            a0 = addiu(a0, 20);
                            if (v1 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004a3b80
                        charge(ctx, 16);
                        sw(zero, v0, allmatinit::kPrimFlags);
                        v1 = 4;
                        sw(v1, v0, allmatinit::kStride);
                        a1 = 1;
                        lw(a0, v0, allmatinit::kStride);
                        v1 = sll(a0, 4);
                        v1 = addu(v1, a0);
                        v1 = sll(v1, 2);
                        v1 = addu(v1, a0);
                        sw(v1, v0, allmatinit::kBatchSize);
                        lw(a0, v0, allmatinit::kStride);
                        v1 = sll(a0, 4);
                        v1 = addu(v1, a0);
                        v1 = sll(v1, 2);
                        v1 = addu(v1, a0);
                        sw(v1, v0, allmatinit::kBatchWords);
                    }
                    // 0x004a3bc0
                    charge(ctx, 2);
                    if (a1 != 0) {
                        // 0x004a3bd8
                        charge(ctx, 4);
                        a0 = s3;
                        jal(ctx, 0x4A3BD8u, gen::fn_sub_4F3F70_004f3f70);
                        v1 = sll(s0, 1);
                        backedge(ctx);
                    L_004a3b1c:
                        charge(ctx, 9);
                        mult(v1, s2, v1);
                        sw(v1, v0, allmatinit::kBatchSize);
                        mult1(v1, s1, s2);
                        sw(v1, v0, allmatinit::kBatchWords);
                        v1 = 12;
                        sw(s2, v0, allmatinit::kStride);
                        sw(v1, v0, allmatinit::kPrimFlags);
                        v0 = s3;
                    } else {
                        // 0x004a3bc8
                        charge(ctx, 2);
                        v0 = 0;
                    }
                } else {
                    // 0x004a3ac8
                    charge(ctx, 2);
                    v0 = 0;
                }
            }
        }
    }
    // 0x004a3be8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}


// sub_4A3C10 [ps2AllMatSetPointBatch] -- the PS2AllMat node's point / line batch: kind 16
// ($a0 = the node, $a1 = the stride, $a2 = the vertices per batch) Fails (0) without a node, with a non-positive count, or when the node's initialisation data already has another primitive kind; creates the 64-byte data on first use (cleared, stride 4, batch 69 x 4) and stores the batch sizes, the stride and the kind. Returns the node.
// Batch size = stride x vertices.
// 0x004A3C10 sub_4A3C10 -- 344 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4A3C10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004a3c10
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s1 = a1;
    s0 = a2;
    if (s2 == 0) {
        // 0x004a3c4c
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004a3c34
        charge(ctx, 2);
        if (i64(s1) <= 0) {
            // 0x004a3c54
            charge(ctx, 2);
            v0 = 0;
        } else {
            // 0x004a3c3c
            charge(ctx, 2);
            if (i64(s0) > 0) {
                // 0x004a3c5c
                charge(ctx, 4);
                jal(ctx, 0x4A3C5Cu, gen::fn_sub_4F3F70_004f3f70);
                if (v0 != 0) {
                    // 0x004a3c6c
                    charge(ctx, 4);
                    lw(v1, v0, allmatinit::kPrimFlags);
                    v1 = v1 & 0xF;
                    if (v1 == 0) {
                        goto L_004a3c84;
                    }
                    // 0x004a3c7c
                    charge(ctx, 2);
                    v0 = 0;
                    // 0x004a3d50 (the shared epilogue, written out on this path)
                    charge(ctx, 6);
                    ld(ra, sp, 0x30);
                    lq(s2, sp, 0x20);
                    lq(s1, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0x40);
                    return;
                }
            L_004a3c84:
                charge(ctx, 2);
                if (v0 != 0) {
                    // 0x004a3c8c
                    charge(ctx, 1);
                    mult(a0, s0, s1);
                    goto L_004a3c90;
                }
                // 0x004a3ca8
                charge(ctx, 5);
                a0 = s2;
                a1 = 64;
                jal(ctx, 0x4A3CACu, gen::fn_sub_4F3EC0_004f3ec0);
                if (v0 == 0) {
                    // 0x004a3d38
                    charge(ctx, 2);
                    a1 = 0;
                    backedge(ctx);
                } else {
                    // 0x004a3cbc
                    charge(ctx, 2);
                    a1 = 0;
                    a0 = v0;
                    for (;;) {
                        // 0x004a3cc4
                        charge(ctx, 9);
                        sw(zero, a0, 0);
                        a1 = addiu(a1, 5);
                        sw(zero, a0, 4);
                        v1 = sltiu(a1, 10);
                        sw(zero, a0, 8);
                        sw(zero, a0, 12);
                        sw(zero, a0, 16);
                        a0 = addiu(a0, 20);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004a3ce8
                    charge(ctx, 16);
                    sw(zero, v0, allmatinit::kPrimFlags);
                    v1 = 4;
                    sw(v1, v0, allmatinit::kStride);
                    a1 = 1;
                    lw(a0, v0, allmatinit::kStride);
                    v1 = sll(a0, 4);
                    v1 = addu(v1, a0);
                    v1 = sll(v1, 2);
                    v1 = addu(v1, a0);
                    sw(v1, v0, allmatinit::kBatchSize);
                    lw(a0, v0, allmatinit::kStride);
                    v1 = sll(a0, 4);
                    v1 = addu(v1, a0);
                    v1 = sll(v1, 2);
                    v1 = addu(v1, a0);
                    sw(v1, v0, allmatinit::kBatchWords);
                }
                // 0x004a3d28
                charge(ctx, 2);
                if (a1 != 0) {
                    // 0x004a3d40
                    charge(ctx, 4);
                    a0 = s2;
                    jal(ctx, 0x4A3D40u, gen::fn_sub_4F3F70_004f3f70);
                    mult(a0, s0, s1);
                    backedge(ctx);
                L_004a3c90:
                    charge(ctx, 6);
                    v1 = 16;
                    sw(a0, v0, allmatinit::kBatchSize);
                    sw(s1, v0, allmatinit::kStride);
                    sw(v1, v0, allmatinit::kPrimFlags);
                    v0 = s2;
                } else {
                    // 0x004a3d30
                    charge(ctx, 2);
                    v0 = 0;
                }
            } else {
                // 0x004a3c44
                charge(ctx, 2);
                v0 = 0;
            }
        }
    }
    // 0x004a3d50 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_4A3D70 [ps2AllMatSetVifOffset] -- stores $a1 in the PS2AllMat node's private data (+20); the node, or 0 without node / data
// 0x004A3D70 sub_4A3D70 -- 52 bytes; leaf frame (no stack)
void sub_4A3D70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x004a3d70
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 == 0) {
        // 0x004a3d90
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004a3d78
        charge(ctx, 3);
        lw(v0, a0, pnode::kPrivateData);
        if (v0 == 0) {
            // 0x004a3d98
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x004a3d84
            charge(ctx, 3);
            sw(a1, v0, allmatpriv::kVifOffset);
            v0 = a0;
        }
    }
    // 0x004a3d9c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// RxPipelineNodePS2AllMatSetVU1CodeArray -- the node's VU1 code array and length (0: the default 0x77F130, 32 entries)
// The node, or 0 without node / private data, or for an array with a zero length.
// 0x004A3DB0 RxPipelineNodePS2AllMatSetVU1CodeArray -- 116 bytes; leaf frame (no stack)
void RxPipelineNodePS2AllMatSetVU1CodeArray(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x004a3db0
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 == 0) {
        // 0x004a3ddc
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004a3db8
        charge(ctx, 3);
        lw(a3, a0, pnode::kPrivateData);
        if (a3 == 0) {
            // 0x004a3de4
            charge(ctx, 2);
            v0 = 0;
        } else {
            // 0x004a3dc4
            charge(ctx, 2);
            if (a1 == 0) {
                // 0x004a3e00
                charge(ctx, 7);
                v0 = 0x780000;
                v1 = 32;
                v0 = addiu(v0, -3792);  // &0x77F130 (the default PS2AllMat VU1 code array (32 entries))
                sw(v0, a3, allmatpriv::kVU1Code);
                lw(v0, a0, pnode::kPrivateData);
                sw(v1, v0, allmatpriv::kVU1CodeCount);
                backedge(ctx);
            L_004a3df8:
                charge(ctx, 2);
                v0 = a0;
            } else {
                // 0x004a3dcc
                charge(ctx, 2);
                if (a2 != 0) {
                    // 0x004a3dec
                    charge(ctx, 3);
                    sw(a1, a3, allmatpriv::kVU1Code);
                    lw(v0, a0, pnode::kPrivateData);
                    sw(a2, v0, allmatpriv::kVU1CodeCount);
                    goto L_004a3df8;
                }
                // 0x004a3dd4
                charge(ctx, 2);
                v0 = 0;
            }
        }
    }
    // 0x004a3e1c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_4A3E30 [ps2AllMatSetCallBack] -- sets one of the PS2AllMat node's five callbacks ($a1 = 1..5; types 2..4 refuse 0)
// The node, or 0 without node / private data, for another type, or a refused 0.
// 0x004A3E30 sub_4A3E30 -- 224 bytes; leaf frame (no stack)
void sub_4A3E30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x004a3e30
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 == 0) {
        // 0x004a3ee4
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004a3e38
        charge(ctx, 3);
        lw(v1, a0, pnode::kPrivateData);
        if (v1 == 0) {
            // 0x004a3eec
            charge(ctx, 2);
            v0 = 0;
        } else {
            // 0x004a3e44
            charge(ctx, 3);
            v0 = 5;
            if (a1 == v0) {
                // 0x004a3ed0
                charge(ctx, 3);
                sw(a2, v1, allmatpriv::kCallBack5);
                v0 = a0;
            } else {
                // 0x004a3e50
                charge(ctx, 3);
                v0 = 4;
                if (a1 == v0) {
                    // 0x004a3ebc
                    charge(ctx, 2);
                    if (a2 == 0) {
                        // 0x004a3f04
                        charge(ctx, 1);
                        v0 = 0;
                    } else {
                        // 0x004a3ec4
                        charge(ctx, 3);
                        sw(a2, v1, allmatpriv::kCallBack4);
                        v0 = a0;
                    }
                } else {
                    // 0x004a3e5c
                    charge(ctx, 3);
                    v0 = 3;
                    if (a1 == v0) {
                        // 0x004a3ea8
                        charge(ctx, 2);
                        if (a2 == 0) {
                            // 0x004a3efc
                            charge(ctx, 2);
                            v0 = 0;
                        } else {
                            // 0x004a3eb0
                            charge(ctx, 3);
                            sw(a2, v1, allmatpriv::kCallBack3);
                            v0 = a0;
                        }
                    } else {
                        // 0x004a3e68
                        charge(ctx, 3);
                        v0 = 2;
                        if (a1 == v0) {
                            // 0x004a3e94
                            charge(ctx, 2);
                            if (a2 == 0) {
                                // 0x004a3ef4
                                charge(ctx, 2);
                                v0 = 0;
                            } else {
                                // 0x004a3e9c
                                charge(ctx, 3);
                                sw(a2, v1, allmatpriv::kCallBack2);
                                v0 = a0;
                            }
                        } else {
                            // 0x004a3e74
                            charge(ctx, 3);
                            v0 = 1;
                            if (a1 == v0) {
                                // 0x004a3e88
                                charge(ctx, 3);
                                sw(a2, v1, allmatpriv::kCallBack1);
                                v0 = a0;
                            } else {
                                // 0x004a3e80
                                charge(ctx, 2);
                                v0 = 0;
                                // 0x004a3edc
                                charge(ctx, 2);
                            }
                        }
                    }
                }
            }
        }
    }
    // 0x004a3f08 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sceLibgcc32GetErxEntries_0 -- returns the address 0x77E1E0 (the PS2AllMat node definition the pipe builders lock)
// 0x004A3F10 sceLibgcc32GetErxEntries_0 -- 12 bytes; leaf frame (no stack)
void sceLibgcc32GetErxEntries_0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x004a3f10
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x780000;
    v0 = addiu(v0, -7712);  // &0x77E1E0
}


// sub_4A4D50 [pipeIdConstructor] -- the PS2 pipeline-id extension constructor: clears the word at object + offset; the object
// 0x004A4D50 sub_4A4D50 -- 16 bytes; leaf frame (no stack)
void sub_4A4D50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x004a4d50
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = addu(a0, a1);
    sw(zero, v0, 0);
    v0 = a0;
}


// sub_4A4DA0 [geometryPipeIdAlways] -- the geometry's PS2 pipeline-id stream-always callback
// Without a record at +84 the extension is cleared; else it looks up the pipeline of the id read from the stream (the object's +84 / +120 record's u16 at +4) unless the extension already holds a pipeline with that id (sub_49E5A0), and stores it in the extension; 0 when none is found, else the object.
// 0x004A4DA0 sub_4A4DA0 -- 152 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4A4DA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004a4da0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a1, a0, 84);
    s0 = a0;
    if (a1 == 0) {
        // 0x004a4e18
        charge(ctx, 4);
        lw(v0, gp, -17504);  // 0x7CE890 (the PS2 pipeline-id extension offset of geometries)
        v0 = addu(s0, v0);
        sw(zero, v0, 0);
        backedge(ctx);
    L_004a4e10:
        charge(ctx, 2);
        v0 = s0;
    } else {
        // 0x004a4db8
        charge(ctx, 5);
        lw(v0, gp, -17504);  // 0x7CE890 (the PS2 pipeline-id extension offset of geometries)
        a0 = addu(s0, v0);
        lw(v0, a0, 0);
        a2 = 0;
        if (v0 != 0) {
            // 0x004a4dcc
            charge(ctx, 4);
            lw(v0, v0, 0);
            lhu(v1, a1, 4);
            if (v1 == v0) {
                // 0x004a4ddc
                charge(ctx, 1);
                a2 = 1;
            }
        }
        // 0x004a4de0
        charge(ctx, 2);
        if (a2 == 0) {
            // 0x004a4df0
            charge(ctx, 4);
            link(ctx, 0x4A4DF0u);  // $ra first: the delay slot below depends on it
            lhu(a1, a1, 4);
            call(ctx, gen::fn_sub_49E5A0_0049e5a0);
            a0 = v0;
            lw(v0, a0, 0);
        } else {
            // 0x004a4de8
            charge(ctx, 2);
            lw(v0, a0, 0);
        }
        // 0x004a4e00
        charge(ctx, 2);
        if (v0 != 0) {
            goto L_004a4e10;
        }
        // 0x004a4e08
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004a4e28 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4A4E40 [atomicPipeIdAlways] -- the atomic's PS2 pipeline-id stream-always callback (through its geometry)
// Without a geometry record at +84, or with fewer than two morph targets, the extension is cleared; else it looks up the pipeline of the id read from the stream (the object's +84 / +120 record's u16 at +4) unless the extension already holds a pipeline with that id (sub_49E5A0), and stores it in the extension; 0 when none is found, else the object.
// 0x004A4E40 sub_4A4E40 -- 172 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4A4E40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004a4e40
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, 24);
    lw(a1, v0, 84);
    s0 = a0;
    if (a1 != 0) {
        // 0x004a4e5c
        charge(ctx, 4);
        lw(v0, v0, 24);
        at = slti(v0, 2);
        if (at != 0) {
            goto L_004a4ecc;
        }
        // 0x004a4e6c
        charge(ctx, 5);
        lw(v0, gp, -17508);  // 0x7CE88C (the PS2 pipeline-id extension offset of atomics)
        a0 = addu(s0, v0);
        lw(v0, a0, 0);
        a2 = 0;
        if (v0 != 0) {
            // 0x004a4e80
            charge(ctx, 4);
            lw(v0, v0, 0);
            lhu(v1, a1, 4);
            if (v1 == v0) {
                // 0x004a4e90
                charge(ctx, 1);
                a2 = 1;
            }
        }
        // 0x004a4e94
        charge(ctx, 2);
        if (a2 == 0) {
            // 0x004a4ea4
            charge(ctx, 4);
            link(ctx, 0x4A4EA4u);  // $ra first: the delay slot below depends on it
            lhu(a1, a1, 4);
            call(ctx, gen::fn_sub_49E5A0_0049e5a0);
            a0 = v0;
            lw(v0, a0, 0);
        } else {
            // 0x004a4e9c
            charge(ctx, 2);
            lw(v0, a0, 0);
        }
        // 0x004a4eb4
        charge(ctx, 2);
        if (v0 != 0) {
        L_004a4ec4:
            charge(ctx, 2);
            v0 = s0;
        } else {
            // 0x004a4ebc
            charge(ctx, 2);
            v0 = 0;
        }
        // 0x004a4edc (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
L_004a4ecc:
    charge(ctx, 4);
    lw(v0, gp, -17508);  // 0x7CE88C (the PS2 pipeline-id extension offset of atomics)
    v0 = addu(s0, v0);
    sw(zero, v0, 0);
    backedge(ctx);
    goto L_004a4ec4;
}


// sub_4A4EF0 [sectorPipeIdAlways] -- the world sector's PS2 pipeline-id stream-always callback (its record at +120)
// Without a record the extension is cleared; else it looks up the pipeline of the id read from the stream (the object's +84 / +120 record's u16 at +4) unless the extension already holds a pipeline with that id (sub_49E5A0), and stores it in the extension; 0 when none is found, else the object.
// 0x004A4EF0 sub_4A4EF0 -- 152 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4A4EF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004a4ef0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a1, a0, 120);
    s0 = a0;
    if (a1 == 0) {
        // 0x004a4f68
        charge(ctx, 4);
        lw(v0, gp, -17512);  // 0x7CE888 (the PS2 pipeline-id extension offset of world sectors)
        v0 = addu(s0, v0);
        sw(zero, v0, 0);
        backedge(ctx);
    L_004a4f60:
        charge(ctx, 2);
        v0 = s0;
    } else {
        // 0x004a4f08
        charge(ctx, 5);
        lw(v0, gp, -17512);  // 0x7CE888 (the PS2 pipeline-id extension offset of world sectors)
        a0 = addu(s0, v0);
        lw(v0, a0, 0);
        a2 = 0;
        if (v0 != 0) {
            // 0x004a4f1c
            charge(ctx, 4);
            lw(v0, v0, 0);
            lhu(v1, a1, 4);
            if (v1 == v0) {
                // 0x004a4f2c
                charge(ctx, 1);
                a2 = 1;
            }
        }
        // 0x004a4f30
        charge(ctx, 2);
        if (a2 == 0) {
            // 0x004a4f40
            charge(ctx, 4);
            link(ctx, 0x4A4F40u);  // $ra first: the delay slot below depends on it
            lhu(a1, a1, 4);
            call(ctx, gen::fn_sub_49E5A0_0049e5a0);
            a0 = v0;
            lw(v0, a0, 0);
        } else {
            // 0x004a4f38
            charge(ctx, 2);
            lw(v0, a0, 0);
        }
        // 0x004a4f50
        charge(ctx, 2);
        if (v0 != 0) {
            goto L_004a4f60;
        }
        // 0x004a4f58
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004a4f78 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4A4F90 [atomicPipeIdRights] -- the atomic's rights callback: 1 when its geometry's / its own pipeline can be found
// One morph target: the geometry's extension (gp 0x7CE890); else the atomic's (gp 0x7CE88C); 1 without a record.
// 0x004A4F90 sub_4A4F90 -- 232 bytes; frame 0x10: ra sp+0x0
void sub_4A4F90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004a4f90
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a0, 24);
    lw(a2, v1, 84);
    if (a2 != 0) {
        // 0x004a4fa8
        charge(ctx, 4);
        lw(v0, v1, 24);
        a1 = 1;
        if (v0 != a1) {
            // 0x004a5018
            charge(ctx, 5);
            lw(v0, gp, -17508);  // 0x7CE88C (the PS2 pipeline-id extension offset of atomics)
            a0 = addu(a0, v0);
            lw(v0, a0, 0);
            a3 = 0;
            if (v0 != 0) {
                // 0x004a502c
                charge(ctx, 4);
                lw(v0, v0, 0);
                lhu(v1, a2, 4);
                if (v1 == v0) {
                    // 0x004a503c
                    charge(ctx, 1);
                    a3 = a1;
                }
            }
            // 0x004a5040
            charge(ctx, 2);
            if (a3 == 0) {
                // 0x004a5050
                charge(ctx, 4);
                link(ctx, 0x4A5050u);  // $ra first: the delay slot below depends on it
                lhu(a1, a2, 4);
                call(ctx, gen::fn_sub_49E5A0_0049e5a0);
                a0 = v0;
                lw(v0, a0, 0);
            } else {
                // 0x004a5048
                charge(ctx, 2);
                lw(v0, a0, 0);
            }
            // 0x004a5060
            charge(ctx, 2);
            if (v0 != 0) {
                backedge(ctx);
                goto L_004a5010;
            }
            // 0x004a5068
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x004a4fb8
            charge(ctx, 5);
            lw(v0, gp, -17504);  // 0x7CE890 (the PS2 pipeline-id extension offset of geometries)
            a0 = addu(v1, v0);
            lw(v0, a0, 0);
            a3 = 0;
            if (v0 != 0) {
                // 0x004a4fcc
                charge(ctx, 4);
                lw(v0, v0, 0);
                lhu(v1, a2, 4);
                if (v1 == v0) {
                    // 0x004a4fdc
                    charge(ctx, 1);
                    a3 = a1;
                }
            }
            // 0x004a4fe0
            charge(ctx, 2);
            if (a3 == 0) {
                // 0x004a4ff0
                charge(ctx, 4);
                link(ctx, 0x4A4FF0u);  // $ra first: the delay slot below depends on it
                lhu(a1, a2, 4);
                call(ctx, gen::fn_sub_49E5A0_0049e5a0);
                a0 = v0;
                lw(v0, a0, 0);
            } else {
                // 0x004a4fe8
                charge(ctx, 2);
                lw(v0, a0, 0);
            }
            // 0x004a5000
            charge(ctx, 2);
            if (v0 != 0) {
                goto L_004a5010;
            }
            // 0x004a5008
            charge(ctx, 2);
            v0 = 0;
        }
        // 0x004a506c (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
L_004a5010:
    charge(ctx, 2);
    v0 = 1;
    // 0x004a506c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}


// sub_4A5080 [sectorPipeIdRights] -- the world sector's rights callback: 1 when its pipeline can be found (1 without a record)
// 0x004A5080 sub_4A5080 -- 124 bytes; frame 0x10: ra sp+0x0
void sub_4A5080(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004a5080
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a1, a0, 120);
    if (a1 != 0) {
        // 0x004a5094
        charge(ctx, 5);
        lw(v0, gp, -17512);  // 0x7CE888 (the PS2 pipeline-id extension offset of world sectors)
        a0 = addu(a0, v0);
        lw(v0, a0, 0);
        a2 = 0;
        if (v0 != 0) {
            // 0x004a50a8
            charge(ctx, 4);
            lw(v0, v0, 0);
            lhu(v1, a1, 4);
            if (v1 == v0) {
                // 0x004a50b8
                charge(ctx, 1);
                a2 = 1;
            }
        }
        // 0x004a50bc
        charge(ctx, 2);
        if (a2 == 0) {
            // 0x004a50cc
            charge(ctx, 4);
            link(ctx, 0x4A50CCu);  // $ra first: the delay slot below depends on it
            lhu(a1, a1, 4);
            call(ctx, gen::fn_sub_49E5A0_0049e5a0);
            a0 = v0;
            lw(v0, a0, 0);
        } else {
            // 0x004a50c4
            charge(ctx, 2);
            lw(v0, a0, 0);
        }
        // 0x004a50dc
        charge(ctx, 2);
        if (v0 != 0) {
            goto L_004a50ec;
        }
        // 0x004a50e4
        charge(ctx, 2);
        v0 = 0;
        // 0x004a50f0 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
L_004a50ec:
    charge(ctx, 1);
    v0 = 1;
    // 0x004a50f0 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}


// sub_4A5100 [pipeIdPluginAttach] -- registers the 4-byte PS2 pipeline-id extension (plugin 0x50F) on geometries, atomics, world sectors
// Each with the constructor sub_4A4D50, the copy sub_4A4D60 and its always callback; the atomic and world-sector
// rights callbacks; 1 when every offset and result is non-negative.
// 0x004A5100 sub_4A5100 -- 244 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4A5100(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004a5100
    enter(ctx, 54);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    a2 = 0x4A0000;
    sd(ra, sp, 0x20);
    a3 = 0x4A0000;
    sq(s1, sp, 0x10);
    t0 = 0x4A0000;
    sq(s0, sp, 0x0);
    a0 = 4;
    a1 = 1295;
    a2 = addiu(a2, 19792);  // &sub_4A4D50
    a3 = addiu(a3, 19808);  // &sub_4A4D60
    t0 = addiu(t0, 19872);  // &sub_4A4DA0
    s0 = 0;
    s1 = 0;
    jal(ctx, 0x4A5134u, gen::fn_sub_493C50_00493c50);
    a2 = 0x4A0000;
    a3 = 0x4A0000;
    t0 = 0x4A0000;
    sw(v0, gp, -17504);  // 0x7CE890 (the PS2 pipeline-id extension offset of geometries)
    a0 = 4;
    a1 = 1295;
    a2 = addiu(a2, 19792);  // &sub_4A4D50
    a3 = addiu(a3, 19808);  // &sub_4A4D60
    t0 = addiu(t0, 20032);  // &sub_4A4E40
    jal(ctx, 0x4A515Cu, gen::fn_sub_492C30_00492c30);
    a2 = 0x4A0000;
    a3 = 0x4A0000;
    t0 = 0x4A0000;
    sw(v0, gp, -17508);  // 0x7CE88C (the PS2 pipeline-id extension offset of atomics)
    a0 = 4;
    a1 = 1295;
    a2 = addiu(a2, 19792);  // &sub_4A4D50
    a3 = addiu(a3, 19808);  // &sub_4A4D60
    t0 = addiu(t0, 20208);  // &sub_4A4EF0
    jal(ctx, 0x4A5184u, gen::fn_sub_499250_00499250);
    a1 = 0x4A0000;
    sw(v0, gp, -17512);  // 0x7CE888 (the PS2 pipeline-id extension offset of world sectors)
    a0 = 1295;
    a1 = addiu(a1, 20368);  // &sub_4A4F90
    jal(ctx, 0x4A5198u, gen::fn_sub_492CC0_00492cc0);
    a1 = 0x4A0000;
    s1 = s1 | v0;
    a0 = 1295;
    a1 = addiu(a1, 20608);  // &sub_4A5080
    jal(ctx, 0x4A51ACu, gen::fn_sub_4992B0_004992b0);
    a1 = s1 | v0;
    lw(a0, gp, -17504);  // 0x7CE890 (the PS2 pipeline-id extension offset of geometries)
    lw(v1, gp, -17508);  // 0x7CE88C (the PS2 pipeline-id extension offset of atomics)
    lw(v0, gp, -17512);  // 0x7CE888 (the PS2 pipeline-id extension offset of world sectors)
    v1 = a0 | v1;
    v0 = v0 | v1;
    v0 = a1 | v0;
    if (i64(v0) >= 0) {
        // 0x004a51d8
        charge(ctx, 1);
        s0 = 1;
    }
    // 0x004a51dc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_4A5200 [pdsMaterialPipeReset] -- restores the default material pipeline (sub_49C620(0))
// 0x004A5200 sub_4A5200 -- 8 bytes; leaf frame (no stack)
void sub_4A5200(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4};
    // 0x004a5200
    enter(ctx, 2);  // entry check point + this block's cycles
    a0 = 0;
    gen::fn_sub_49C620_0049c620(ctx);  // tail call
}


// sub_4A5210 [pdsMaterialPipeOpen] -- the default material pipeline: RpPDSGetPipe(0x1001), made the default (sub_49C620)
// Not found: the built-in default and error 0x80000006 'PS2 material pipes'. Returns 1.
// 0x004A5210 sub_4A5210 -- 120 bytes; frame 0x20: ra sp+0x0
void sub_4A5210(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004a5210
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    a0 = 4097;
    jal(ctx, 0x4A5218u, gen::fn_RpPDSGetPipe_0046a890);
    lw(a0, gp, -16840);  // 0x7CEB28 (the default-pipeline module offset)
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v1 = addu(v1, a0);
    sw(v0, v1, pipemod::kDefMaterial);
    if (v0 == 0) {
        // 0x004a5248
        charge(ctx, 13);
        a0 = 0;
        jal(ctx, 0x4A5248u, gen::fn_sub_49C620_0049c620);
        v1 = 2;
        v0 = lui(0x8000);
        a1 = 0x780000;
        sw(v1, sp, 0x18);
        a0 = v0 | 0x6;
        a1 = addiu(a1, -7424);  // "PS2 material pipes"
        jal(ctx, 0x4A5264u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x1C);
        a0 = addiu(sp, 0x18);
        jal(ctx, 0x4A5270u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 1;
    } else {
        // 0x004a5238
        charge(ctx, 4);
        a0 = v0;
        jal(ctx, 0x4A5238u, gen::fn_sub_49C620_0049c620);
        v0 = 1;
    }
    // 0x004a527c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4A5290 [pdsSectorPipeReset] -- restores the default world-sector pipeline (sub_49C560(0))
// 0x004A5290 sub_4A5290 -- 8 bytes; leaf frame (no stack)
void sub_4A5290(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4};
    // 0x004a5290
    enter(ctx, 2);  // entry check point + this block's cycles
    a0 = 0;
    gen::fn_sub_49C560_0049c560(ctx);  // tail call
}


// sub_4A52A0 [pdsSectorPipeOpen] -- the default world-sector pipeline: RpPDSGetPipe(0x1003), made the default (sub_49C560)
// Not found: the built-in default and error 0x80000006 'PS2 sector pipes'. Returns 1.
// 0x004A52A0 sub_4A52A0 -- 120 bytes; frame 0x20: ra sp+0x0
void sub_4A52A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004a52a0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    a0 = 4099;
    jal(ctx, 0x4A52A8u, gen::fn_RpPDSGetPipe_0046a890);
    lw(a0, gp, -16840);  // 0x7CEB28 (the default-pipeline module offset)
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v1 = addu(v1, a0);
    sw(v0, v1, pipemod::kDefSector);
    if (v0 == 0) {
        // 0x004a52d8
        charge(ctx, 13);
        a0 = 0;
        jal(ctx, 0x4A52D8u, gen::fn_sub_49C560_0049c560);
        v1 = 2;
        v0 = lui(0x8000);
        a1 = 0x780000;
        sw(v1, sp, 0x18);
        a0 = v0 | 0x6;
        a1 = addiu(a1, -7392);  // "PS2 sector pipes"
        jal(ctx, 0x4A52F4u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x1C);
        a0 = addiu(sp, 0x18);
        jal(ctx, 0x4A5300u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 1;
    } else {
        // 0x004a52c8
        charge(ctx, 4);
        a0 = v0;
        jal(ctx, 0x4A52C8u, gen::fn_sub_49C560_0049c560);
        v0 = 1;
    }
    // 0x004a530c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4A5320 [pdsAtomicPipeReset] -- restores the default atomic pipeline (sub_49C5C0(0))
// 0x004A5320 sub_4A5320 -- 8 bytes; leaf frame (no stack)
void sub_4A5320(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4};
    // 0x004a5320
    enter(ctx, 2);  // entry check point + this block's cycles
    a0 = 0;
    gen::fn_sub_49C5C0_0049c5c0(ctx);  // tail call
}


// sub_4A5330 [pdsAtomicPipeOpen] -- the default atomic pipeline: RpPDSGetPipe(0x1002), made the default (sub_49C5C0)
// Not found: the built-in default and error 0x80000006. Returns 1.
// 0x004A5330 sub_4A5330 -- 120 bytes; frame 0x20: ra sp+0x0
void sub_4A5330(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004a5330
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    a0 = 4098;
    jal(ctx, 0x4A5338u, gen::fn_RpPDSGetPipe_0046a890);
    lw(a0, gp, -16840);  // 0x7CEB28 (the default-pipeline module offset)
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v1 = addu(v1, a0);
    sw(v0, v1, pipemod::kDefAtomic);
    if (v0 == 0) {
        // 0x004a5368
        charge(ctx, 13);
        a0 = 0;
        jal(ctx, 0x4A5368u, gen::fn_sub_49C5C0_0049c5c0);
        v1 = 2;
        v0 = lui(0x8000);
        a1 = 0x780000;
        sw(v1, sp, 0x18);
        a0 = v0 | 0x6;
        a1 = addiu(a1, -7360);  // "PS2 stomic pipes"
        jal(ctx, 0x4A5384u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x1C);
        a0 = addiu(sp, 0x18);
        jal(ctx, 0x4A5390u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 1;
    } else {
        // 0x004a5358
        charge(ctx, 4);
        a0 = v0;
        jal(ctx, 0x4A5358u, gen::fn_sub_49C5C0_0049c5c0);
        v0 = 1;
    }
    // 0x004a539c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4A53B0 [rt2dBrushClose] -- destroys the brush free list (sub_4C3C30) and frees the 9,216-byte buffer
// 0x004A53B0 sub_4A53B0 -- 68 bytes; frame 0x10: ra sp+0x0
void sub_4A53B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004a53b0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x960000;
    sd(ra, sp, 0x0);
    link(ctx, 0x4A53BCu);  // $ra first: the delay slot below depends on it
    lw(a0, v0, -4768);  // 0x95ED60 (Rt2d: the 120-byte brush free list)
    call(ctx, gen::fn_sub_4C3C30_004c3c30);
    v0 = 0x960000;
    v1 = 0x960000;
    sw(zero, v0, -4768);  // 0x95ED60 (Rt2d: the 120-byte brush free list)
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x4A53D8u);  // $ra = the return address
    lw(a0, v1, -4764);  // 0x95ED64 (Rt2d: a 9,216-byte buffer)
    call_ptr(ctx, jt);
    v1 = 0x960000;
    sw(zero, v1, -4764);  // 0x95ED64 (Rt2d: a 9,216-byte buffer)
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}


// sub_4A5400 [rt2dBrushOpen] -- allocates the 9,216-byte buffer and creates the 120-byte brush free list (static block 0x95E7D0)
// 0x004A5400 sub_4A5400 -- 100 bytes; frame 0x10: ra sp+0x0
void sub_4A5400(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004a5400
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 0x40000;
    sd(ra, sp, 0x0);
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
    a0 = 9216;
    a1 = v1 | 0x190;
    jalr(ctx, 0x4A5418u, v0.u());
    lw(a1, gp, -20620);  // 0x7CDC64
    v1 = 0x960000;
    lw(a3, gp, -20616);  // 0x7CDC68
    t0 = 0x960000;
    sw(v0, v1, -4764);  // 0x95ED64 (Rt2d: a 9,216-byte buffer)
    a0 = 120;
    v0 = 0x40000;
    a2 = 16;
    t0 = addiu(t0, -6192);  // &0x95E7D0
    t1 = v0 | 0x1A2;
    jal(ctx, 0x4A5444u, gen::fn_sub_4C3B60_004c3b60);
    v1 = 0x960000;
    sw(v0, v1, -4768);  // 0x95ED60 (Rt2d: the 120-byte brush free list)
    ld(ra, sp, 0x0);
    v0 = 1;
    sp = addiu(sp, 0x10);
}


// sub_4A5540 [rt2dBrushRelease] -- drops a brush reference (+116); at 0 its texture (+104, sub_4D0F00) and the record are freed
// Returns 1 when it was freed, else 0.
// 0x004A5540 sub_4A5540 -- 104 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4A5540(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004a5540
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, 116);
    s0 = a0;
    v0 = addiu(v0, -1);
    sw(v0, a0, 116);
    if (i64(v0) <= 0) {
        // 0x004a5568
        charge(ctx, 3);
        lw(a0, s0, 104);
        if (a0 != 0) {
            // 0x004a5574
            charge(ctx, 2);
            jal(ctx, 0x4A5574u, gen::fn_sub_4D0F00_004d0f00);
        }
        // 0x004a557c
        charge(ctx, 7);
        v0 = 0x960000;
        lw(a0, v0, -4768);  // 0x95ED60 (Rt2d: the 120-byte brush free list)
        v0 = 0x960000;
        lw(v0, v0, 396);  // 0x96018C (free-list free slot)
        a1 = s0;
        jalr(ctx, 0x4A558Cu, v0.u());
        v0 = 1;
    } else {
        // 0x004a5560
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004a5598 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4AA540 [rt2dGetWord84] -- returns the toolkit word at 0x95EF84
// 0x004AA540 sub_4AA540 -- 12 bytes; leaf frame (no stack)
void sub_4AA540(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x004aa540
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x960000;
    lw(v0, v0, -4220);  // 0x95EF84 (Rt2d: a toolkit word (0 at the open))
}


// sub_4AA620 [rt2dCTMClose] -- destroys the 32 CTM stack matrices (sub_4C3880), resets the top, frees the scratch block
// 0x004AA620 sub_4AA620 -- 148 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4AA620(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004aa620
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = 0;
    s0 = 0x960000;
    s0 = addiu(s0, -6048);  // &0x95E860 (Rt2d: the 256-entry u16 index table (0..255))
    for (;;) {
        // 0x004aa63c
        charge(ctx, 3);
        lw(a0, s0, 1424);
        if (a0 != 0) {
            // 0x004aa648
            charge(ctx, 4);
            jal(ctx, 0x4AA648u, gen::fn_sub_4C3880_004c3880);
            sw(zero, s0, 1424);
        }
        // 0x004aa658
        charge(ctx, 4);
        s1 = addiu(s1, 1);
        v1 = slti(s1, 32);
        s0 = addiu(s0, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004aa668
    charge(ctx, 6);
    a0 = 0x960000;
    v1 = 0x960000;
    sw(zero, a0, -4496);  // 0x95EE70 (Rt2d: the CTM stack top)
    lw(a0, v1, -2692);  // 0x95F57C (Rt2d: a scratch block)
    if (a0 != 0) {
        // 0x004aa680
        charge(ctx, 8);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        jalr(ctx, 0x4AA688u, v0.u());
        a0 = 0x960000;
        v1 = 0x960000;
        sw(zero, a0, -2692);  // 0x95F57C (Rt2d: a scratch block)
        sw(zero, v1, -2688);  // 0x95F580 (Rt2d: its size)
    }
    // 0x004aa6a0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_4AA6C0 [rt2dCTMOpen] -- the CTM stack at open: an identity matrix on top, the toolkit defaults, the 0..255 index table
// The first stack matrix created (sub_4C38C0) and made the identity (flags 0x20003); the defaults (1.0, 0.5, 7, ...),
// the 256-entry u16 table 0..255, the other stack slots cleared. Returns 1.
// 0x004AA6C0 sub_4AA6C0 -- 928 bytes; frame 0x150: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4AA6C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004aa6c0
    enter(ctx, 167);  // entry check point + this block's cycles
    sp = addiu(sp, -0x150);
    v0 = 0x960000;
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
    link(ctx, 0x4AA6F0u);  // $ra first: the delay slot below depends on it
    sw(zero, v0, -4496);  // 0x95EE70 (Rt2d: the CTM stack top)
    call(ctx, gen::fn_sub_4C38C0_004c38c0);
    a0 = 0x960000;
    a2 = 0x20000;
    sw(v0, a0, -4624);  // 0x95EDF0 (Rt2d: the CTM stack (matrix pointers))
    s5 = a2 | 0x3;
    v0 = 0x960000;
    v1 = 0x3F800000;
    lw(a1, v0, -4496);  // 0x95EE70 (Rt2d: the CTM stack top)
    a0 = 0x960000;
    s4 = 0x960000;
    s3 = 0x960000;
    s2 = 0x960000;
    s1 = 0x960000;
    s0 = 0x960000;
    t9 = 0x960000;
    t8 = 0x960000;
    t7 = 0x960000;
    t6 = 0x960000;
    t5 = 0x960000;
    v0 = 0x960000;
    a1 = sll(a1, 2);
    v0 = addiu(v0, -4624);  // &0x95EDF0 (Rt2d: the CTM stack (matrix pointers))
    t4 = 0x960000;
    a1 = addu(v0, a1);
    t3 = 0x960000;
    lw(a1, a1, 0);
    a3 = 0x960000;
    t1 = 0x960000;
    a2 = 0x960000;
    s7 = 0x960000;
    fp = 0x960000;
    t2 = 0x960000;
    t0 = 0x960000;
    sw(v1, a1, 40);
    lw(a0, a0, -4496);  // 0x95EE70 (Rt2d: the CTM stack top)
    a1 = 0x960000;
    sq(a1, sp, 0x140);
    a1 = 0x960000;
    sq(a1, sp, 0x130);
    a1 = 0x960000;
    sq(a1, sp, 0x120);
    a0 = sll(a0, 2);
    a1 = 0x960000;
    s6 = addu(v0, a0);
    sq(a1, sp, 0x110);
    lw(s6, s6, 0);
    a1 = 0x960000;
    sq(a1, sp, 0x100);
    a0 = 0x960000;
    a1 = 0x960000;
    a0 = addiu(a0, -6048);  // &0x95E860 (Rt2d: the 256-entry u16 index table (0..255))
    sq(a1, sp, 0xF0);
    a1 = 0x960000;
    sq(a1, sp, 0xE0);
    sw(v1, s6, 20);
    a1 = 0x960000;
    lw(s4, s4, -4496);  // 0x95EE70 (Rt2d: the CTM stack top)
    sq(a1, sp, 0xD0);
    a1 = 0x960000;
    sq(a1, sp, 0xC0);
    a1 = 0x960000;
    sq(a1, sp, 0xB0);
    s4 = sll(s4, 2);
    a1 = 0x960000;
    s4 = addu(v0, s4);
    sq(a1, sp, 0xA0);
    lw(s4, s4, 0);
    a1 = 0;
    sw(v1, s4, 0);
    lw(s3, s3, -4496);  // 0x95EE70 (Rt2d: the CTM stack top)
    s3 = sll(s3, 2);
    s3 = addu(v0, s3);
    lw(s3, s3, 0);
    sw(zero, s3, 16);
    lw(s2, s2, -4496);  // 0x95EE70 (Rt2d: the CTM stack top)
    s2 = sll(s2, 2);
    s2 = addu(v0, s2);
    lw(s2, s2, 0);
    sw(zero, s2, 8);
    lw(s1, s1, -4496);  // 0x95EE70 (Rt2d: the CTM stack top)
    s1 = sll(s1, 2);
    s1 = addu(v0, s1);
    lw(s1, s1, 0);
    sw(zero, s1, 4);
    lw(s0, s0, -4496);  // 0x95EE70 (Rt2d: the CTM stack top)
    s0 = sll(s0, 2);
    s0 = addu(v0, s0);
    lw(s0, s0, 0);
    sw(zero, s0, 36);
    lw(s0, t9, -4496);  // 0x95EE70 (Rt2d: the CTM stack top)
    s0 = sll(s0, 2);
    s0 = addu(v0, s0);
    lw(s0, s0, 0);
    sw(zero, s0, 32);
    lw(s0, t8, -4496);  // 0x95EE70 (Rt2d: the CTM stack top)
    s0 = sll(s0, 2);
    s0 = addu(v0, s0);
    lw(s0, s0, 0);
    sw(zero, s0, 24);
    lw(t7, t7, -4496);  // 0x95EE70 (Rt2d: the CTM stack top)
    t7 = sll(t7, 2);
    t7 = addu(v0, t7);
    lw(t7, t7, 0);
    sw(zero, t7, 56);
    lw(t6, t6, -4496);  // 0x95EE70 (Rt2d: the CTM stack top)
    t6 = sll(t6, 2);
    t6 = addu(v0, t6);
    lw(t6, t6, 0);
    sw(zero, t6, 52);
    lw(t5, t5, -4496);  // 0x95EE70 (Rt2d: the CTM stack top)
    t5 = sll(t5, 2);
    t5 = addu(v0, t5);
    lw(t5, t5, 0);
    sw(zero, t5, 48);
    lw(t4, t4, -4496);  // 0x95EE70 (Rt2d: the CTM stack top)
    t4 = sll(t4, 2);
    v0 = addu(v0, t4);
    lw(t4, v0, 0);
    lw(v0, t4, 12);
    v0 = v0 | s5;
    sw(v0, t4, 12);
    v0 = 0x3F000000;
    sw(v1, t1, -4264);  // 0x95EF58
    sw(v0, t3, -4260);  // 0x95EF5C
    v0 = 7;
    sw(v1, a2, -4648);  // 0x95EDD8
    sw(v0, a3, -4248);  // 0x95EF68
    lq(v0, sp, 0x140);
    sw(v1, s7, -4668);  // 0x95EDC4
    sw(v1, fp, -0x1250);
    sw(zero, t2, -4252);  // 0x95EF64 (Rt2d: a CTM-derived cache flag)
    sw(zero, t0, -4272);  // 0x95EF50 (Rt2d: a CTM-derived cache flag)
    sw(zero, v0, -4672);
    lq(v0, sp, 0x130);
    sw(zero, v0, -4680);
    lq(v0, sp, 0x120);
    sw(zero, v0, -4684);
    lq(v0, sp, 0x110);
    sw(zero, v0, -4652);
    lq(v0, sp, 0x100);
    sw(zero, v0, -4656);
    lq(v0, sp, 0xF0);
    sw(zero, v0, -4664);
    lq(v0, sp, 0xE0);
    sw(zero, v0, -4632);
    lq(v0, sp, 0xD0);
    sw(zero, v0, -4636);
    lq(v0, sp, 0xC0);
    sw(zero, v0, -4640);
    lq(v0, sp, 0xB0);
    lw(v0, v0, -4676);
    v1 = v0 | s5;
    lq(v0, sp, 0xA0);
    sw(v1, v0, -4676);
    for (;;) {
        // 0x004aa95c
        charge(ctx, 19);
        sh(a1, a0, 0);
        v0 = addiu(a1, 1);
        sh(v0, a0, 2);
        v0 = addiu(a1, 2);
        sh(v0, a0, 4);
        v0 = addiu(a1, 3);
        sh(v0, a0, 6);
        v0 = addiu(a1, 4);
        sh(v0, a0, 8);
        v0 = addiu(a1, 5);
        sh(v0, a0, 10);
        v0 = addiu(a1, 6);
        sh(v0, a0, 12);
        v0 = addiu(a1, 7);
        sh(v0, a0, 14);
        a1 = addiu(a1, 8);
        v0 = slti(a1, 256);
        a0 = addiu(a0, 16);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004aa9a8
    charge(ctx, 3);
    a0 = 0x960000;
    v1 = 1;
    a0 = addiu(a0, -6044);  // &0x95E864
    for (;;) {
        // 0x004aa9b4
        charge(ctx, 10);
        sw(zero, a0, 1424);
        v1 = addiu(v1, 6);
        sw(zero, a0, 1428);
        v0 = slti(v1, 26);
        sw(zero, a0, 1432);
        sw(zero, a0, 1436);
        sw(zero, a0, 1440);
        sw(zero, a0, 1444);
        a0 = addiu(a0, 24);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004aa9dc
    charge(ctx, 33);
    v0 = 0x960000;
    v1 = sll(v1, 2);
    v0 = addiu(v0, -4624);  // &0x95EDF0 (Rt2d: the CTM stack (matrix pointers))
    v1 = addu(v0, v1);
    sw(zero, v1, 0);
    v0 = 0x960000;
    sw(zero, v0, -4220);  // 0x95EF84 (Rt2d: a toolkit word (0 at the open))
    v1 = 0x960000;
    v0 = 0x960000;
    sw(zero, v1, -4240);  // 0x95EF70
    sw(zero, v0, -4236);  // 0x95EF74
    v1 = 0x3F800000;
    v0 = 0x960000;
    sw(v1, v0, -4232);  // 0x95EF78
    v0 = 0x960000;
    sw(v1, v0, -4228);  // 0x95EF7C
    v0 = 0x960000;
    sw(zero, v0, -2692);  // 0x95F57C (Rt2d: a scratch block)
    v0 = 0x960000;
    sw(zero, v0, -2688);  // 0x95F580 (Rt2d: its size)
    ld(ra, sp, 0x90);
    v0 = 1;
    lq(fp, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x150);
}


// sub_4AADA0 [Rt2dCTMScale] -- scales the current transformation by ($f12, $f13, 1) (RwMatrixScale, post-concatenated); 1
// Clears the two CTM-derived cache flags.
// 0x004AADA0 sub_4AADA0 -- 96 bytes; frame 0x20: ra sp+0x0
void sub_4AADA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13};
    // 0x004aada0
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x3F800000;
    sd(ra, sp, 0x0);
    a1 = addiu(sp, 0x10);
    sw(v0, sp, 0x18);
    swc1(f12, sp, 0x10);
    v0 = 0x960000;
    a2 = 1;
    lw(v1, v0, -4496);  // 0x95EE70 (Rt2d: the CTM stack top)
    v0 = 0x960000;
    v1 = sll(v1, 2);
    v0 = addiu(v0, -4624);  // &0x95EDF0 (Rt2d: the CTM stack (matrix pointers))
    v0 = addu(v0, v1);
    lw(a0, v0, 0);
    link(ctx, 0x4AADD8u);  // $ra first: the delay slot below depends on it
    swc1(f13, sp, 0x14);
    call(ctx, gen::fn_sub_4C33D0_004c33d0);
    v0 = 0x960000;
    v1 = 0x960000;
    sw(zero, v0, -4272);  // 0x95EF50 (Rt2d: a CTM-derived cache flag)
    sw(zero, v1, -4252);  // 0x95EF64 (Rt2d: a CTM-derived cache flag)
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4AAE00 [Rt2dCTMTranslate] -- translates the current transformation by ($f12, $f13, 0) (RwMatrixTranslate); 1
// Clears the two CTM-derived cache flags.
// 0x004AAE00 sub_4AAE00 -- 92 bytes; frame 0x20: ra sp+0x0
void sub_4AAE00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13};
    // 0x004aae00
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x0);
    a1 = addiu(sp, 0x10);
    lw(v1, v0, -4496);  // 0x95EE70 (Rt2d: the CTM stack top)
    swc1(f12, sp, 0x10);
    swc1(f13, sp, 0x14);
    a2 = 1;
    v0 = 0x960000;
    v1 = sll(v1, 2);
    v0 = addiu(v0, -4624);  // &0x95EDF0 (Rt2d: the CTM stack (matrix pointers))
    v0 = addu(v0, v1);
    lw(a0, v0, 0);
    link(ctx, 0x4AAE34u);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0x18);
    call(ctx, gen::fn_sub_4C35D0_004c35d0);
    v0 = 0x960000;
    v1 = 0x960000;
    sw(zero, v0, -4272);  // 0x95EF50 (Rt2d: a CTM-derived cache flag)
    sw(zero, v1, -4252);  // 0x95EF64 (Rt2d: a CTM-derived cache flag)
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4AB170 [rt2dPathReset] -- empties a path's segment sList and marks it flat (+12 = 1, +8 = 0)
// 0x004AB170 sub_4AB170 -- 52 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4AB170(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ab170
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    link(ctx, 0x4AB180u);  // $ra first: the delay slot below depends on it
    lw(a0, a0, 0);
    call(ctx, gen::fn_sub_4C1E60_004c1e60);
    sw(zero, s0, path2d::kWord8);
    v1 = 1;
    sw(v1, s0, path2d::kFlat);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4AB1B0 [Rt2dPathEmpty] -- empties a path: its sub-paths destroyed (sub_4AC390), its segments emptied, itself current
// 0x004AB1B0 sub_4AB1B0 -- 72 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4AB1B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ab1b0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    link(ctx, 0x4AB1C0u);  // $ra first: the delay slot below depends on it
    lw(a0, a0, 20);
    call(ctx, gen::fn_sub_4AC390_004ac390);
    sw(zero, s0, path2d::kNext);
    link(ctx, 0x4AB1CCu);  // $ra first: the delay slot below depends on it
    lw(a0, s0, path2d::kSegments);
    call(ctx, gen::fn_sub_4C1E60_004c1e60);
    sw(zero, s0, path2d::kWord8);
    v0 = 1;
    sw(v0, s0, path2d::kFlat);
    sw(s0, s0, path2d::kCurrent);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4AB2C0 [Rt2dPathLineto] -- appends a line segment to ($f12, $f13): its unit normal, the running length, the mitre
// The new 24-byte segment (sub_4C1E70 on the current sub-path's sList): type 1, the point, the unit normal of the
// segment from the previous point, the length so far; the previous point's normal becomes the mitre of the two (or
// the new normal when the sub-path had fewer than two points). Returns the path.
// 0x004AB2C0 sub_4AB2C0 -- 324 bytes; frame 0x40: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
void sub_4AB2C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20}, f21{ctx, 21};
    // 0x004ab2c0
    enter(ctx, 35);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    s0 = a0;
    swc1(f20, sp, 0x0);
    lw(v0, a0, 24);
    mov_s(f21, f12);
    lw(a0, v0, 0);
    mov_s(f20, f13);
    jal(ctx, 0x4AB2E8u, gen::fn_sub_4C2120_004c2120);
    lw(v1, s0, path2d::kCurrent);
    s1 = v0;
    v0 = 0x30000;
    lw(a0, v1, 0);
    a1 = v0 | 0x190;
    jal(ctx, 0x4AB300u, gen::fn_sub_4C1E70_004c1e70);
    v1 = 1;
    sw(v1, v0, 0);
    mtc1(zero, f0);
    swc1(f21, v0, seg2d::kX);
    swc1(f20, v0, seg2d::kY);
    lwc1(f1, v0, -20);
    lwc1(f2, v0, -16);
    sub_s(f3, f1, f21);
    sub_s(f2, f20, f2);
    mula_s(f3, f3);
    madd_s(f1, f2, f2);
    sqrt_s(f4, f1);
    c_le_s(f4, f0);
    if (cond(ctx)) {
        // 0x004ab36c
        charge(ctx, 1);
        mov_s(f0, f4);
    } else {
        // 0x004ab34c
        charge(ctx, 8);
        v1 = 0x3F800000;
        mtc1(v1, f0);
        div_s(f0, f0, f4);
    }
    // 0x004ab370
    charge(ctx, 9);
    mul_s(f1, f2, f0);
    at = slti(s1, 2);
    mul_s(f0, f3, f0);
    swc1(f1, v0, seg2d::kNormalX);
    swc1(f0, v0, seg2d::kNormalY);
    lwc1(f0, v0, -4);
    add_s(f0, f0, f4);
    swc1(f0, v0, seg2d::kDistance);
    if (at != 0) {
        // 0x004ab3d4
        charge(ctx, 4);
        lwc1(f1, v0, seg2d::kNormalX);
        lwc1(f0, v0, seg2d::kNormalY);
        swc1(f1, v0, -12);
        swc1(f0, v0, -8);
    } else {
        // 0x004ab394
        charge(ctx, 16);
        lwc1(f5, v0, -12);
        v1 = 0x3F800000;
        lwc1(f2, v0, seg2d::kNormalX);
        lwc1(f3, v0, -8);
        lwc1(f1, v0, seg2d::kNormalY);
        mtc1(v1, f0);
        add_s(f4, f5, f2);
        add_s(f2, f3, f1);
        mula_s(f3, f2);
        madd_s(f1, f5, f4);
        div_s(f0, f0, f1);
        mul_s(f1, f4, f0);
        mul_s(f0, f2, f0);
        swc1(f1, v0, -12);
        swc1(f0, v0, -8);
    }
    // 0x004ab3e4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = s0;
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lwc1(f21, sp, 0x4);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_4AB410 [Rt2dPathCurveto] -- appends a cubic curve: three type-2 control points ($f12..$f17), each with normal and length
// As the line segment for each point (sub_4C1F70 takes three entries); the current sub-path is marked not flat.
// Returns the path.
// 0x004AB410 sub_4AB410 -- 652 bytes; frame 0x50: ra sp+0x40, s1 sp+0x30 (sq), s0 sp+0x20 (sq), f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
void sub_4AB410(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16}, f17{ctx, 17}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25};
    // 0x004ab410
    enter(ctx, 44);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f25, sp, 0x14);
    s0 = a0;
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(v0, a0, 24);
    mov_s(f25, f12);
    mov_s(f24, f13);
    mov_s(f23, f14);
    mov_s(f22, f15);
    mov_s(f21, f16);
    lw(a0, v0, 0);
    mov_s(f20, f17);
    jal(ctx, 0x4AB458u, gen::fn_sub_4C2120_004c2120);
    lw(v1, s0, path2d::kCurrent);
    s1 = v0;
    v0 = 0x30000;
    a1 = 3;
    lw(a0, v1, 0);
    a2 = v0 | 0x190;
    jal(ctx, 0x4AB474u, gen::fn_sub_4C1F70_004c1f70);
    v1 = 2;
    sw(v1, v0, 0);
    mtc1(zero, f0);
    swc1(f25, v0, seg2d::kX);
    swc1(f24, v0, seg2d::kY);
    lwc1(f1, v0, -20);
    lwc1(f2, v0, -16);
    sub_s(f3, f1, f25);
    sub_s(f2, f24, f2);
    mula_s(f3, f3);
    madd_s(f1, f2, f2);
    sqrt_s(f4, f1);
    c_le_s(f4, f0);
    if (cond(ctx)) {
        // 0x004ab4e0
        charge(ctx, 1);
        mov_s(f0, f4);
    } else {
        // 0x004ab4c0
        charge(ctx, 8);
        v1 = 0x3F800000;
        mtc1(v1, f0);
        div_s(f0, f0, f4);
    }
    // 0x004ab4e4
    charge(ctx, 9);
    mul_s(f1, f2, f0);
    at = slti(s1, 2);
    mul_s(f0, f3, f0);
    swc1(f1, v0, seg2d::kNormalX);
    swc1(f0, v0, seg2d::kNormalY);
    lwc1(f0, v0, -4);
    add_s(f0, f0, f4);
    swc1(f0, v0, seg2d::kDistance);
    if (at != 0) {
        // 0x004ab548
        charge(ctx, 4);
        lwc1(f1, v0, seg2d::kNormalX);
        lwc1(f0, v0, seg2d::kNormalY);
        swc1(f1, v0, -12);
        swc1(f0, v0, -8);
    } else {
        // 0x004ab508
        charge(ctx, 16);
        lwc1(f5, v0, -12);
        v1 = 0x3F800000;
        lwc1(f2, v0, seg2d::kNormalX);
        lwc1(f3, v0, -8);
        lwc1(f1, v0, seg2d::kNormalY);
        mtc1(v1, f0);
        add_s(f4, f5, f2);
        add_s(f2, f3, f1);
        mula_s(f3, f2);
        madd_s(f1, f5, f4);
        div_s(f0, f0, f1);
        mul_s(f1, f4, f0);
        mul_s(f0, f2, f0);
        swc1(f1, v0, -12);
        swc1(f0, v0, -8);
    }
    // 0x004ab558
    charge(ctx, 17);
    v1 = 2;
    sw(v1, v0, 24);
    mtc1(zero, f0);
    swc1(f23, v0, 28);
    swc1(f22, v0, 32);
    lwc1(f1, v0, seg2d::kX);
    lwc1(f2, v0, seg2d::kY);
    sub_s(f3, f1, f23);
    sub_s(f2, f22, f2);
    mula_s(f3, f3);
    madd_s(f1, f2, f2);
    sqrt_s(f4, f1);
    c_le_s(f4, f0);
    if (cond(ctx)) {
        // 0x004ab5bc
        charge(ctx, 1);
        mov_s(f0, f4);
    } else {
        // 0x004ab59c
        charge(ctx, 8);
        v1 = 0x3F800000;
        mtc1(v1, f0);
        div_s(f0, f0, f4);
    }
    // 0x004ab5c0
    charge(ctx, 25);
    mul_s(f1, f2, f0);
    v1 = 2;
    mul_s(f0, f3, f0);
    swc1(f1, v0, 36);
    swc1(f0, v0, 40);
    lwc1(f1, v0, seg2d::kDistance);
    mtc1(zero, f0);
    add_s(f1, f1, f4);
    swc1(f1, v0, 44);
    sw(v1, v0, 48);
    swc1(f21, v0, 52);
    swc1(f20, v0, 56);
    lwc1(f1, v0, 28);
    lwc1(f2, v0, 32);
    sub_s(f3, f1, f21);
    sub_s(f2, f20, f2);
    mula_s(f3, f3);
    madd_s(f1, f2, f2);
    sqrt_s(f4, f1);
    c_le_s(f4, f0);
    if (cond(ctx)) {
        // 0x004ab644
        charge(ctx, 1);
        mov_s(f0, f4);
    } else {
        // 0x004ab624
        charge(ctx, 8);
        v1 = 0x3F800000;
        mtc1(v1, f0);
        div_s(f0, f0, f4);
    }
    // 0x004ab648 (the shared epilogue, written out on this path)
    charge(ctx, 21);
    mul_s(f1, f2, f0);
    mul_s(f0, f3, f0);
    swc1(f1, v0, 60);
    swc1(f0, v0, 64);
    lwc1(f0, v0, 44);
    add_s(f0, f0, f4);
    swc1(f0, v0, 68);
    lw(v1, s0, path2d::kCurrent);
    v0 = s0;
    sw(zero, v1, 12);
    ld(ra, sp, 0x40);
    lwc1(f25, sp, 0x14);
    lq(s1, sp, 0x30);
    lwc1(f24, sp, 0x10);
    lq(s0, sp, 0x20);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x50);
}


// sub_4AC120 [rt2dPathGetBBox] -- the bounding box of a path and its sub-paths: {x, y, width, height} in $a1
// Starts at the first point; a flat sub-path adds its points (sub_4AC020), a curved one is flattened into the scratch
// path first (sub_4ABD50). Returns the path.
// 0x004AC120 sub_4AC120 -- 276 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4AC120(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x004ac120
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = si(-1);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    lw(v1, a0, 4);
    s1 = a1;
    if (v1 != v0) {
        // 0x004ac15c
        charge(ctx, 2);
        lw(v0, s2, 0);
        lwc1(f0, v0, 4);
    } else {
        // 0x004ac14c
        charge(ctx, 4);
        link(ctx, 0x4AC14Cu);  // $ra first: the delay slot below depends on it
        lw(a0, s2, 0);
        call(ctx, gen::fn_sub_4C2090_004c2090);
        lwc1(f0, v0, 4);
    }
    // 0x004ac164
    charge(ctx, 7);
    s0 = s2;
    swc1(f0, s1, 8);
    swc1(f0, s1, 0);
    lwc1(f0, v0, 8);
    swc1(f0, s1, 12);
    swc1(f0, s1, 4);
    if (s2 != 0) {
        for (;;) {
            // 0x004ac180
            charge(ctx, 3);
            lw(v0, s0, 12);
            if (v0 == 0) {
                // 0x004ac1d0
                charge(ctx, 18);
                v0 = 0x960000;
                lw(s3, v0, -4728);  // 0x95ED88 (Rt2d: the scratch path (flattening))
                link(ctx, 0x4AC1D8u);  // $ra first: the delay slot below depends on it
                lw(a0, s3, 20);
                call(ctx, gen::fn_sub_4AC390_004ac390);
                a0 = s3;
                link(ctx, 0x4AC1E4u);  // $ra first: the delay slot below depends on it
                sw(zero, s3, 20);
                call(ctx, gen::fn_sub_4AB170_004ab170);
                sw(s3, s3, 24);
                v0 = 0x960000;
                lw(s3, v0, -4728);  // 0x95ED88 (Rt2d: the scratch path (flattening))
                a1 = s0;
                a0 = s3;
                jal(ctx, 0x4AC1FCu, gen::fn_sub_4ABD50_004abd50);
                a0 = s3;
                a1 = s1;
                jal(ctx, 0x4AC208u, gen::fn_sub_4AC020_004ac020);
                backedge(ctx);
            } else {
                // 0x004ac18c
                charge(ctx, 3);
                a0 = s0;
                a1 = s1;
                jal(ctx, 0x4AC190u, gen::fn_sub_4AC020_004ac020);
            }
            // 0x004ac198
            charge(ctx, 3);
            lw(s0, s0, 20);
            if (s0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004ac1a4
        charge(ctx, 1);
    }
    // 0x004ac1a8
    charge(ctx, 10);
    v0 = s2;
    lwc1(f1, s1, 8);
    lwc1(f0, s1, 0);
    sub_s(f0, f1, f0);
    swc1(f0, s1, 8);
    lwc1(f1, s1, 4);
    lwc1(f0, s1, 12);
    sub_s(f0, f0, f1);
    swc1(f0, s1, 12);
    // 0x004ac218
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}


// sub_4AC7F0 [rt2dPathClose3] -- destroys the scratch path's three-deep chain (sub_4AB0E0 / sub_4AC390) and its free list
// 0x004AC7F0 sub_4AC7F0 -- 104 bytes; frame 0x10: ra sp+0x0
void sub_4AC7F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ac7f0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x960000;
    sd(ra, sp, 0x0);
    lw(a0, v0, -4728);  // 0x95ED88 (Rt2d: the scratch path (flattening))
    if (a0 != 0) {
        // 0x004ac808
        charge(ctx, 4);
        jal(ctx, 0x4AC808u, gen::fn_sub_4AB0E0_004ab0e0);
        if (v0 != 0) {
            // 0x004ac818
            charge(ctx, 4);
            a0 = v0;
            jal(ctx, 0x4AC818u, gen::fn_sub_4AB0E0_004ab0e0);
            if (v0 != 0) {
                // 0x004ac828
                charge(ctx, 4);
                a0 = v0;
                jal(ctx, 0x4AC828u, gen::fn_sub_4AB0E0_004ab0e0);
                a0 = v0;
                jal(ctx, 0x4AC830u, gen::fn_sub_4AC390_004ac390);
            }
        }
    }
    // 0x004ac838
    charge(ctx, 8);
    v0 = 0x960000;
    link(ctx, 0x4AC83Cu);  // $ra first: the delay slot below depends on it
    lw(a0, v0, -4732);  // 0x95ED84 (Rt2d: a free list (closed by sub_4AC7F0))
    call(ctx, gen::fn_sub_4C3C30_004c3c30);
    v1 = 0x960000;
    sw(zero, v1, -4732);  // 0x95ED84 (Rt2d: a free list (closed by sub_4AC7F0))
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}


// sub_4AC860 [rt2dSetFreeListParams] -- stores the toolkit's free-list block parameters (0x7CDCC4 / 0x7CDCC8)
// 0x004AC860 sub_4AC860 -- 12 bytes; leaf frame (no stack)
void sub_4AC860(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x004ac860
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(a0, gp, -20524);  // 0x7CDCC4
    sw(a1, gp, -20520);  // 0x7CDCC8
}


// sub_4ACCC0 [rt2dPathPointInside] -- even-odd point-in-path test of a flattened path: 1 when ($a0) lies inside
// Counts the edges whose y range contains the point (half-open) and whose crossing lies right of it; odd -> 1.
// 0x004ACCC0 sub_4ACCC0 -- 416 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4ACCC0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6};
    // 0x004accc0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    v0 = si(-1);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a1, 4);
    s0 = 0;
    if (v1 != v0) {
        // 0x004acd08
        charge(ctx, 2);
        lw(v0, s4, 0);
        s3 = v0;
    } else {
        // 0x004accf8
        charge(ctx, 4);
        link(ctx, 0x4ACCF8u);  // $ra first: the delay slot below depends on it
        lw(a0, s4, 0);
        call(ctx, gen::fn_sub_4C2090_004c2090);
        s3 = v0;
    }
    // 0x004acd10
    charge(ctx, 2);
    s2 = v0;
    s1 = 0;
    for (;;) {
        // 0x004acd18
        charge(ctx, 4);
        lw(v0, s4, 4);
        v1 = si(-1);
        if (v0 == v1) {
            // 0x004acd30
            charge(ctx, 3);
            link(ctx, 0x4ACD30u);  // $ra first: the delay slot below depends on it
            lw(a0, s4, 0);
            call(ctx, gen::fn_sub_4C2120_004c2120);
            v0 = addiu(v0, -1);
        } else {
            // 0x004acd28
            charge(ctx, 2);
            v0 = addiu(v0, -1);
        }
        // 0x004acd3c
        charge(ctx, 3);
        at = slt(s1, v0);
        if (at == 0) {
            break;
        }
        // 0x004acd48
        charge(ctx, 6);
        s2 = addiu(s2, 24);
        lwc1(f6, s2, 8);
        lwc1(f1, s3, 8);
        c_le_s(f1, f6);
        if (!cond(ctx)) {
            // 0x004acd68
            charge(ctx, 1);
            mov_s(f0, f6);
        } else {
            // 0x004acd60
            charge(ctx, 2);
            mov_s(f0, f1);
        }
        // 0x004acd6c
        charge(ctx, 4);
        lwc1(f2, s5, 4);
        c_le_s(f2, f0);
        if (!cond(ctx)) {
            // 0x004acd7c
            charge(ctx, 3);
            c_lt_s(f1, f6);
            if (cond(ctx)) {
                // 0x004acd90
                charge(ctx, 1);
                mov_s(f0, f6);
            } else {
                // 0x004acd88
                charge(ctx, 2);
                mov_s(f0, f1);
            }
            // 0x004acd94
            charge(ctx, 3);
            c_le_s(f2, f0);
            if (cond(ctx)) {
                // 0x004acda0
                charge(ctx, 5);
                lwc1(f4, s2, 4);
                lwc1(f5, s3, 4);
                c_lt_s(f5, f4);
                if (cond(ctx)) {
                    // 0x004acdbc
                    charge(ctx, 1);
                    mov_s(f0, f4);
                } else {
                    // 0x004acdb4
                    charge(ctx, 2);
                    mov_s(f0, f5);
                }
                // 0x004acdc0
                charge(ctx, 4);
                lwc1(f3, s5, 0);
                c_le_s(f3, f0);
                if (cond(ctx)) {
                    // 0x004acdd0
                    charge(ctx, 3);
                    c_eq_s(f1, f6);
                    if (!cond(ctx)) {
                        // 0x004acddc
                        charge(ctx, 10);
                        sub_s(f2, f2, f1);
                        sub_s(f0, f6, f1);
                        sub_s(f1, f4, f5);
                        mul_s(f1, f2, f1);
                        div_s(f0, f1, f0);
                        c_eq_s(f5, f4);
                        add_s(f0, f5, f0);
                        if (!cond(ctx)) {
                            // 0x004ace04
                            charge(ctx, 3);
                            c_le_s(f3, f0);
                            if (cond(ctx)) {
                                goto L_004ace1c;
                            }
                            goto L_004ace10;
                        }
                    L_004ace1c:
                        charge(ctx, 2);
                        s0 = addiu(s0, 1);
                        backedge(ctx);
                    }
                }
            }
        }
    L_004ace10:
        charge(ctx, 3);
        s3 = addiu(s3, 24);
        s1 = addiu(s1, 1);
        backedge(ctx);
    }
    // 0x004ace24
    charge(ctx, 2);
    v0 = s0 & 0x1;
    if (i64(s0) < 0) {
        // 0x004ace2c
        charge(ctx, 2);
        if (v0 != 0) {
            // 0x004ace34
            charge(ctx, 1);
            v0 = addiu(v0, -2);
        }
    }
    // 0x004ace38 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    v0 = sltu(0, v0);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}


// sub_4ACE60 [rt2dPathPointInsideThunk] -- the point-in-path test (a tail call to sub_4ACCC0)
// 0x004ACE60 sub_4ACE60 -- 8 bytes; leaf frame (no stack)
void sub_4ACE60(EEContext& ctx) {
    using namespace hg;
    // 0x004ace60
    enter(ctx, 2);  // entry check point + this block's cycles
    gen::fn_sub_4ACCC0_004accc0(ctx);  // tail call
}


// sub_4AD6A0 [rt2dShapeNodeDestroy] -- frees a shape node's path (+176, RwFree) and releases its brush (+180); the brush's result
// 0x004AD6A0 sub_4AD6A0 -- 96 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4AD6A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ad6a0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(a0, a0, 176);
    s0 = 1;
    if (a0 != 0) {
        // 0x004ad6c0
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        jalr(ctx, 0x4AD6C8u, v0.u());
    }
    // 0x004ad6d0
    charge(ctx, 3);
    lw(a0, s1, 180);
    if (a0 != 0) {
        // 0x004ad6dc
        charge(ctx, 3);
        jal(ctx, 0x4AD6DCu, gen::fn_sub_4A5540_004a5540);
        s0 = v0;
    }
    // 0x004ad6e8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_4ADB50 [rt2dShapeNodeClose] -- destroys the 272-byte shape-node free list
// 0x004ADB50 sub_4ADB50 -- 40 bytes; frame 0x10: ra sp+0x0
void sub_4ADB50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004adb50
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x960000;
    sd(ra, sp, 0x0);
    link(ctx, 0x4ADB5Cu);  // $ra first: the delay slot below depends on it
    lw(a0, v0, -4724);  // 0x95ED8C (Rt2d: the 272-byte shape-node free list)
    call(ctx, gen::fn_sub_4C3C30_004c3c30);
    v1 = 0x960000;
    sw(zero, v1, -4724);  // 0x95ED8C (Rt2d: the 272-byte shape-node free list)
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}


// sub_4ADB80 [rt2dShapeNodeOpen] -- creates the 272-byte shape-node free list (static block 0x95F9C0); 1
// 0x004ADB80 sub_4ADB80 -- 68 bytes; frame 0x10: ra sp+0x0
void sub_4ADB80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004adb80
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t0 = 0x960000;
    sd(ra, sp, 0x0);
    v0 = 0x40000;
    lw(a1, gp, -20512);  // 0x7CDCD0
    a0 = 272;
    lw(a3, gp, -20508);  // 0x7CDCD4
    a2 = 16;
    t0 = addiu(t0, -1600);  // &0x95F9C0
    t1 = v0 | 0x1A3;
    jal(ctx, 0x4ADBA4u, gen::fn_sub_4C3B60_004c3b60);
    v1 = 0x960000;
    sw(v0, v1, -4724);  // 0x95ED8C (Rt2d: the 272-byte shape-node free list)
    ld(ra, sp, 0x0);
    v0 = 1;
    sp = addiu(sp, 0x10);
}


// sub_4ADC70 [rt2dShapeNodeFree] -- returns a shape node to its free list
// 0x004ADC70 sub_4ADC70 -- 28 bytes; leaf frame (no stack)
void sub_4ADC70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x004adc70
    enter(ctx, 7);  // entry check point + this block's cycles
    v0 = 0x960000;
    a1 = a0;
    v1 = 0x960000;
    lw(v0, v0, 396);  // 0x96018C (free-list free slot)
    lw(a0, v1, -4724);  // 0x95ED8C (Rt2d: the 272-byte shape-node free list)
    tail(ctx, v0.u());  // jr: the target's entry point
}


// sub_4ADCA0 [rt2dShapeNodeAlloc] -- takes a shape node from its free list (0x30193)
// 0x004ADCA0 sub_4ADCA0 -- 32 bytes; leaf frame (no stack)
void sub_4ADCA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x004adca0
    enter(ctx, 8);  // entry check point + this block's cycles
    v0 = 0x960000;
    lw(a0, v0, -4724);  // 0x95ED8C (Rt2d: the 272-byte shape-node free list)
    v0 = 0x30000;
    a1 = v0 | 0x1A3;
    v0 = 0x960000;
    lw(v0, v0, 392);  // 0x960188 (free-list alloc slot)
    tail(ctx, v0.u());  // jr: the target's entry point
}


// sub_4ADDB0 [rt2dObjectStreamReadHeader] -- reads an object's 44-byte header: id, flags, colour block, then the child chunk
// Reads 44 bytes (sub_4C5250); finds chunk 13 (sub_4C1600) and reads the matrix into object +16 (sub_4C19F0); the
// header's words go to +0 / +4 and its eight floats to +144..+172; the type becomes 6. Returns the object or 0.
// 0x004ADDB0 sub_4ADDB0 -- 220 bytes; frame 0x60: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4ADDB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x004addb0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    a2 = 44;
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a0 = s0;
    a1 = addiu(sp, 0x30);
    jal(ctx, 0x4ADDD0u, gen::fn_sub_4C5250_004c5250);
    v1 = 44;
    if (v0 == v1) {
        // 0x004addec
        charge(ctx, 7);
        a0 = s0;
        a1 = 13;
        a2 = 0;
        a3 = 0;
        jal(ctx, 0x4ADDF8u, gen::fn_sub_4C1600_004c1600);
        if (v0 != 0) {
            // 0x004ade10
            charge(ctx, 26);
            a0 = s0;
            a1 = addiu(s1, 16);
            jal(ctx, 0x4ADE14u, gen::fn_sub_4C19F0_004c19f0);
            lw(a0, sp, 0x34);
            v1 = 6;
            v0 = s1;
            sw(a0, s1, 0);
            lw(a0, sp, 0x38);
            sw(a0, s1, 4);
            lwc1(f3, sp, 0x3C);
            lwc1(f2, sp, 0x40);
            lwc1(f1, sp, 0x44);
            lwc1(f0, sp, 0x48);
            swc1(f3, s1, 144);
            swc1(f2, s1, 148);
            swc1(f1, s1, 152);
            swc1(f0, s1, 156);
            lwc1(f3, sp, 0x4C);
            lwc1(f2, sp, 0x50);
            lwc1(f1, sp, 0x54);
            lwc1(f0, sp, 0x58);
            swc1(f3, s1, 160);
            swc1(f2, s1, 164);
            swc1(f1, s1, 168);
            swc1(f0, s1, 172);
            sw(v1, s1, 8);
        } else {
            // 0x004ade08
            charge(ctx, 2);
            v0 = 0;
        }
    } else {
        // 0x004adde4
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004ade78 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}


// sub_4ADFD0 [rt2dObjectSetVisible] -- sets (1) or clears bit 2 of an object's flags (+8); the object
// 0x004ADFD0 sub_4ADFD0 -- 52 bytes; leaf frame (no stack)
void sub_4ADFD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x004adfd0
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 1;
    if (a1 != v0) {
        // 0x004adfec
        charge(ctx, 4);
        lw(v1, a0, 8);
        v0 = si(-5);
        v0 = v1 & v0;
        sw(v0, a0, 8);
    } else {
        // 0x004adfdc
        charge(ctx, 4);
        lw(v0, a0, 8);
        v0 = v0 | 0x4;
        sw(v0, a0, 8);
    }
    // 0x004adffc (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = a0;
}


// sub_4AE010 [rt2dObjectIsVisible] -- bit 2 of an object's flags
// 0x004AE010 sub_4AE010 -- 12 bytes; leaf frame (no stack)
void sub_4AE010(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x004ae010
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, 8);
    v0 = v0 & 0x4;
}


// sub_4AE020 [rt2dObjectSetColourMult] -- copies 64 bytes into object +16 and sets flag bit 1; the object
// 0x004AE020 sub_4AE020 -- 60 bytes; leaf frame (no stack)
void sub_4AE020(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x004ae020
    enter(ctx, 2);  // entry check point + this block's cycles
    a3 = addiu(a0, 16);
    a2 = 8;
    for (;;) {
        // 0x004ae028
        charge(ctx, 8);
        lw(v1, a1, 0);
        a2 = addiu(a2, -1);
        lw(v0, a1, 4);
        sw(v1, a3, 0);
        a1 = addiu(a1, 8);
        sw(v0, a3, 4);
        a3 = addiu(a3, 8);
        if (i64(a2) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004ae048
    charge(ctx, 5);
    lw(v1, a0, 8);
    v0 = a0;
    v1 = v1 | 0x2;
    sw(v1, a0, 8);
}


// sub_4AE1D0 [rt2dObjectSetId] -- object +4 = $a1; the object
// 0x004AE1D0 sub_4AE1D0 -- 12 bytes; leaf frame (no stack)
void sub_4AE1D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x004ae1d0
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(a1, a0, 4);
    v0 = a0;
}


// sub_4AE1E0 [rt2dShapeGetPath] -- destroys a shape's path (sub_4AC390 on +176) -- the tail of the shape destroy
// 0x004AE1E0 sub_4AE1E0 -- 8 bytes; leaf frame (no stack)
void sub_4AE1E0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4};
    // 0x004ae1e0
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(a0, a0, 176);
    gen::fn_sub_4AC390_004ac390(ctx);  // tail call
}


// sub_4AE1F0 [rt2dShapePickPoint] -- a visible shape's point test: the point through the shape's matrix (+208), then the path test
// 0 when the shape is hidden (flag bit 2 clear).
// 0x004AE1F0 sub_4AE1F0 -- 120 bytes; frame 0x50: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4AE1F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x004ae1f0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 4;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, 8);
    v1 = v1 & 0x4;
    s0 = a0;
    if (v1 == v0) {
        // 0x004ae218
        charge(ctx, 16);
        lwc1(f0, a1, 0);
        a0 = addiu(sp, 0x28);
        a2 = addiu(s0, 208);
        swc1(f0, sp, 0x38);
        lwc1(f0, a1, 4);
        swc1(f0, sp, 0x3C);
        a1 = addiu(sp, 0x38);
        link(ctx, 0x4AE234u);  // $ra first: the delay slot below depends on it
        sw(zero, sp, 0x40);
        call(ctx, gen::fn_sub_4C6BE0_004c6be0);
        lwc1(f1, sp, 0x28);
        lwc1(f0, sp, 0x2C);
        swc1(f1, sp, 0x48);
        swc1(f0, sp, 0x4C);
        lw(a1, s0, 176);
        a0 = addiu(sp, 0x48);
        jal(ctx, 0x4AE250u, gen::fn_sub_4ACE60_004ace60);
    } else {
        // 0x004ae210
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004ae258 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}


// sub_4AE8F0 [rt2dSceneGetChildCount] -- a scene's child count (+180)
// 0x004AE8F0 sub_4AE8F0 -- 8 bytes; leaf frame (no stack)
void sub_4AE8F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x004ae8f0
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 180);
}


// sub_4AE900 [rt2dSceneGetChild] -- a scene's child $a1: the sList entry (sub_4C21B0 on +176), dereferenced when flag bit 0 is set
// 0x004AE900 sub_4AE900 -- 64 bytes; frame 0x10: ra sp+0x0
void sub_4AE900(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ae900
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 1;
    sd(ra, sp, 0x0);
    lw(v1, a0, 8);
    v1 = v1 & 0x1;
    if (v1 != v0) {
        // 0x004ae92c
        charge(ctx, 2);
        link(ctx, 0x4AE92Cu);  // $ra first: the delay slot below depends on it
        lw(a0, a0, 176);
        call(ctx, gen::fn_sub_4C21B0_004c21b0);
    } else {
        // 0x004ae91c
        charge(ctx, 4);
        link(ctx, 0x4AE91Cu);  // $ra first: the delay slot below depends on it
        lw(a0, a0, 176);
        call(ctx, gen::fn_sub_4C21B0_004c21b0);
        lw(v0, v0, 0);
    }
    // 0x004ae934 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}


// sub_4AEB60 [rt2dSceneForAllChildren] -- calls $a1(child, scene, $a2) on each 272-byte child of a scene; the scene
// 0x004AEB60 sub_4AEB60 -- 140 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4AEB60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004aeb60
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    lw(a0, a0, 176);
    s1 = a2;
    jal(ctx, 0x4AEB88u, gen::fn_sub_4C2090_004c2090);
    lw(a0, s3, 180);
    v1 = sll(a0, 4);
    v1 = addu(v1, a0);
    v1 = sll(v1, 4);
    s4 = addu(v0, v1);
    s0 = v0;
    if (v0 != s4) {
        for (;;) {
            // 0x004aebac
            charge(ctx, 7);
            a0 = s0;
            a1 = s3;
            a2 = s1;
            jalr(ctx, 0x4AEBB4u, s2.u());
            s0 = addiu(s0, 272);
            if (s0 == s4) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004aebc8 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = s3;
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}


// sub_4AEF50 [rt2dSceneSetDirty] -- scene +188 = 1; the scene
// 0x004AEF50 sub_4AEF50 -- 16 bytes; leaf frame (no stack)
void sub_4AEF50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x004aef50
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 1;
    sw(v0, a0, 188);
    v0 = a0;
}


// sub_4B0360 [rt2dPolygonDestroy] -- frees a polygon: its vertex ring (8-byte records back to their free list), its point array, itself
// Returns 1.
// 0x004B0360 sub_4B0360 -- 208 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B0360(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b0360
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    if (s3 != 0) {
        // 0x004b0380
        charge(ctx, 4);
        sw(zero, s3, 0);
        lw(s1, s3, 4);
        if (s1 != 0) {
            // 0x004b0390
            charge(ctx, 3);
            s0 = 0x960000;
            a1 = s1;
            s0 = addiu(s0, 396);  // &0x96018C (free-list free slot)
            for (;;) {
                // 0x004b039c
                charge(ctx, 2);
                lw(s2, a1, 0);
                if (a1 != 0) {
                    // 0x004b03a4
                    charge(ctx, 9);
                    sw(zero, a1, 0);
                    v0 = si(-1);
                    sw(v0, a1, 4);
                    v0 = 0x960000;
                    lw(a0, v0, -4716);  // 0x95ED94 (Rt2d: the 8-byte polygon-vertex free list)
                    lw(v0, s0, 0);
                    jalr(ctx, 0x4B03BCu, v0.u());
                }
                // 0x004b03c8
                charge(ctx, 2);
                a1 = s2;
                if (s2 == s1) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004b03d0
        charge(ctx, 3);
        lw(a0, s3, 16);
        if (a0 != 0) {
            // 0x004b03dc
            charge(ctx, 4);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C (RwFree slot)
            jalr(ctx, 0x4B03E4u, v0.u());
        }
        // 0x004b03ec
        charge(ctx, 9);
        sw(zero, s3, 4);
        v1 = 0x960000;
        sw(zero, s3, 16);
        v0 = 0x960000;
        sw(zero, s3, 12);
        lw(a0, v1, -4712);  // 0x95ED98 (Rt2d: the 20-byte polygon free list)
        lw(v0, v0, 396);  // 0x96018C (free-list free slot)
        a1 = s3;
        jalr(ctx, 0x4B0408u, v0.u());
    }
    // 0x004b0410 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    v0 = 1;
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}


// sub_4B0430 [rt2dPolygonCornerSide] -- the side of a polygon corner: 1 left, 2 right, 4 collinear (the cross product's sign)
// ($a0 = the polygon, $a1..$a3 = three vertex records; the points from the polygon's array)
// 0x004B0430 sub_4B0430 -- 304 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B0430(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6};
    // 0x004b0430
    enter(ctx, 60);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    s1 = a2;
    lw(a1, a0, 16);
    s0 = addiu(sp, 0x5C);
    lw(v1, a3, 4);
    lw(v0, a2, 4);
    a1 = addiu(a1, 4);
    v1 = sll(v1, 3);
    v0 = sll(v0, 3);
    v1 = addu(a1, v1);
    v0 = addu(a1, v0);
    lwc1(f1, v1, 0);
    lwc1(f0, v0, 0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x58);
    lw(v1, a2, 4);
    lw(v0, a3, 4);
    lw(a0, a0, 16);
    v1 = sll(v1, 3);
    v0 = sll(v0, 3);
    v1 = addu(a0, v1);
    v0 = addu(a0, v0);
    lwc1(f1, v1, 0);
    a0 = addiu(sp, 0x58);
    lwc1(f0, v0, 0);
    a1 = a0;
    sub_s(f0, f1, f0);
    link(ctx, 0x4B04B8u);  // $ra first: the delay slot below depends on it
    swc1(f0, s0, 0);
    call(ctx, gen::fn_sub_4C6B20_004c6b20);
    lw(v1, s2, 4);
    lwc1(f1, s0, 0);
    lw(a1, s3, 16);
    lwc1(f4, sp, 0x58);
    lw(v0, s1, 4);
    mtc1(zero, f0);
    a3 = sll(v1, 3);
    a0 = addu(a1, a3);
    a2 = addiu(a1, 4);
    v1 = sll(v0, 3);
    a1 = addu(a1, v1);
    v0 = addu(a2, a3);
    v1 = addu(a2, v1);
    lwc1(f3, v1, 0);
    lwc1(f2, v0, 0);
    lwc1(f6, a1, 0);
    lwc1(f5, a0, 0);
    sub_s(f2, f3, f2);
    sub_s(f5, f6, f5);
    mula_s(f2, f1);
    madd_s(f1, f5, f4);
    c_le_s(f1, f0);
    if (!cond(ctx)) {
        // 0x004b0540
        charge(ctx, 2);
        v0 = 1;
        backedge(ctx);
    } else {
        // 0x004b0520
        charge(ctx, 3);
        c_lt_s(f1, f0);
        if (!cond(ctx)) {
            // 0x004b0534
            charge(ctx, 1);
            v0 = 4;
        } else {
            // 0x004b052c
            charge(ctx, 2);
            v0 = 2;
        }
    }
    // 0x004b0538
    charge(ctx, 2);
    ld(ra, sp, 0x40);
    // 0x004b0548
    charge(ctx, 6);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}


// sub_4B0560 [rt2dPolygonPointInTriangle] -- classifies a vertex against a triangle of three others: 8 inside, 4 on an edge, 16 outside
// 0x004B0560 sub_4B0560 -- 860 bytes; frame 0xA0: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B0560(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6};
    // 0x004b0560
    enter(ctx, 65);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    s3 = a2;
    sq(s1, sp, 0x10);
    s2 = a3;
    sq(s0, sp, 0x0);
    s1 = t0;
    lw(a1, a0, 16);
    s0 = addiu(sp, 0x9C);
    lw(v1, a3, 4);
    lw(v0, a2, 4);
    a1 = addiu(a1, 4);
    v1 = sll(v1, 3);
    v0 = sll(v0, 3);
    v1 = addu(a1, v1);
    v0 = addu(a1, v0);
    lwc1(f1, v1, 0);
    lwc1(f0, v0, 0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x98);
    lw(v1, a2, 4);
    lw(v0, a3, 4);
    lw(a0, a0, 16);
    v1 = sll(v1, 3);
    v0 = sll(v0, 3);
    v1 = addu(a0, v1);
    v0 = addu(a0, v0);
    lwc1(f1, v1, 0);
    a0 = addiu(sp, 0x98);
    lwc1(f0, v0, 0);
    a1 = a0;
    sub_s(f0, f1, f0);
    link(ctx, 0x4B05FCu);  // $ra first: the delay slot below depends on it
    swc1(f0, s0, 0);
    call(ctx, gen::fn_sub_4C6B20_004c6b20);
    lw(v1, s4, 4);
    lwc1(f1, s0, 0);
    lw(a2, s5, 16);
    lwc1(f4, sp, 0x98);
    lw(v0, s3, 4);
    mtc1(zero, f0);
    a3 = sll(v1, 3);
    v1 = addu(a2, a3);
    a1 = addiu(a2, 4);
    lwc1(f5, v1, 0);
    a0 = sll(v0, 3);
    v0 = addu(a1, a3);
    lwc1(f2, v0, 0);
    v1 = addu(a1, a0);
    a0 = addu(a2, a0);
    lwc1(f3, v1, 0);
    lwc1(f6, a0, 0);
    sub_s(f2, f3, f2);
    sub_s(f5, f6, f5);
    mula_s(f2, f1);
    madd_s(f1, f5, f4);
    c_le_s(f1, f0);
    if (!cond(ctx)) {
        // 0x004b0878
        charge(ctx, 2);
        s0 = 1;
        backedge(ctx);
    } else {
        // 0x004b0664
        charge(ctx, 3);
        c_lt_s(f1, f0);
        if (!cond(ctx)) {
            // 0x004b0678
            charge(ctx, 1);
            s0 = 4;
        } else {
            // 0x004b0670
            charge(ctx, 2);
            s0 = 2;
        }
    }
    // 0x004b067c
    charge(ctx, 50);
    lw(v1, s1, 4);
    a0 = addiu(sp, 0x90);
    lw(v0, s2, 4);
    a2 = addiu(a2, 4);
    s6 = addiu(sp, 0x94);
    a1 = a0;
    v1 = sll(v1, 3);
    v0 = sll(v0, 3);
    v1 = addu(a2, v1);
    v0 = addu(a2, v0);
    lwc1(f1, v1, 0);
    lwc1(f0, v0, 0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x90);
    lw(v1, s2, 4);
    lw(v0, s1, 4);
    lw(a2, s5, 16);
    v1 = sll(v1, 3);
    v0 = sll(v0, 3);
    v1 = addu(a2, v1);
    v0 = addu(a2, v0);
    lwc1(f1, v1, 0);
    lwc1(f0, v0, 0);
    sub_s(f0, f1, f0);
    link(ctx, 0x4B06DCu);  // $ra first: the delay slot below depends on it
    swc1(f0, s6, 0);
    call(ctx, gen::fn_sub_4C6B20_004c6b20);
    lw(v0, s2, 4);
    lwc1(f1, s6, 0);
    lw(a1, s5, 16);
    lwc1(f4, sp, 0x90);
    lw(a0, s4, 4);
    mtc1(zero, f0);
    v1 = sll(v0, 3);
    v0 = addu(a1, v1);
    lwc1(f6, v0, 0);
    a2 = sll(a0, 3);
    a0 = addiu(a1, 4);
    v0 = addu(a0, v1);
    lwc1(f3, v0, 0);
    v1 = addu(a1, a2);
    lwc1(f5, v1, 0);
    v0 = addu(a0, a2);
    lwc1(f2, v0, 0);
    sub_s(f5, f6, f5);
    sub_s(f2, f3, f2);
    mula_s(f2, f1);
    madd_s(f1, f5, f4);
    c_le_s(f1, f0);
    if (!cond(ctx)) {
        // 0x004b0880
        charge(ctx, 2);
        s2 = 1;
        backedge(ctx);
    } else {
        // 0x004b0744
        charge(ctx, 3);
        c_lt_s(f1, f0);
        if (!cond(ctx)) {
            // 0x004b0758
            charge(ctx, 1);
            s2 = 4;
        } else {
            // 0x004b0750
            charge(ctx, 2);
            s2 = 2;
        }
    }
    // 0x004b075c
    charge(ctx, 50);
    lw(v1, s3, 4);
    a2 = addiu(a1, 4);
    lw(v0, s1, 4);
    a0 = addiu(sp, 0x88);
    s6 = addiu(sp, 0x8C);
    a1 = a0;
    v1 = sll(v1, 3);
    v0 = sll(v0, 3);
    v1 = addu(a2, v1);
    v0 = addu(a2, v0);
    lwc1(f1, v1, 0);
    lwc1(f0, v0, 0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x88);
    lw(v0, s3, 4);
    lw(v1, s1, 4);
    lw(a2, s5, 16);
    v0 = sll(v0, 3);
    v1 = sll(v1, 3);
    v0 = addu(a2, v0);
    v1 = addu(a2, v1);
    lwc1(f1, v1, 0);
    lwc1(f0, v0, 0);
    sub_s(f0, f1, f0);
    link(ctx, 0x4B07BCu);  // $ra first: the delay slot below depends on it
    swc1(f0, s6, 0);
    call(ctx, gen::fn_sub_4C6B20_004c6b20);
    lw(v1, s4, 4);
    lwc1(f1, s6, 0);
    lw(a1, s5, 16);
    lwc1(f4, sp, 0x88);
    lw(v0, s1, 4);
    mtc1(zero, f0);
    a3 = sll(v1, 3);
    a0 = addu(a1, a3);
    a2 = addiu(a1, 4);
    v1 = sll(v0, 3);
    a1 = addu(a1, v1);
    v0 = addu(a2, a3);
    v1 = addu(a2, v1);
    lwc1(f3, v1, 0);
    lwc1(f2, v0, 0);
    lwc1(f6, a1, 0);
    lwc1(f5, a0, 0);
    sub_s(f2, f3, f2);
    sub_s(f5, f6, f5);
    mula_s(f2, f1);
    madd_s(f1, f5, f4);
    c_le_s(f1, f0);
    if (!cond(ctx)) {
        // 0x004b0888
        charge(ctx, 2);
        a0 = 1;
        backedge(ctx);
    } else {
        // 0x004b0824
        charge(ctx, 3);
        c_lt_s(f1, f0);
        if (!cond(ctx)) {
            // 0x004b0838
            charge(ctx, 1);
            a0 = 4;
        } else {
            // 0x004b0830
            charge(ctx, 2);
            a0 = 2;
        }
    }
    // 0x004b083c
    charge(ctx, 5);
    v1 = s0 & s2;
    v0 = 1;
    v1 = a0 & v1;
    if (v1 == v0) {
        // 0x004b0890
        charge(ctx, 2);
        v0 = 8;
        backedge(ctx);
    } else {
        // 0x004b0850
        charge(ctx, 5);
        v0 = s0 | s2;
        v0 = a0 | v0;
        v0 = v0 & 0x4;
        if (v0 == 0) {
            // 0x004b086c
            charge(ctx, 1);
            v0 = 16;
        } else {
            // 0x004b0864
            charge(ctx, 2);
            v0 = 4;
        }
    }
    // 0x004b0870
    charge(ctx, 2);
    ld(ra, sp, 0x70);
    // 0x004b0898
    charge(ctx, 9);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}


// sub_4B08C0 [rt2dPolygonSplit] -- splits a polygon's vertex ring between two vertices into two polygons (the diagonal duplicated)
// The new polygon gets one part, the old keeps the other; counts, the point array and the parent shared. Returns the
// new polygon (or 0).
// 0x004B08C0 sub_4B08C0 -- 584 bytes; frame 0xB0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B08C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004b08c0
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    v0 = 0x960000;
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    fp = 0;
    sq(s6, sp, 0x60);
    s7 = 0;
    sq(s5, sp, 0x50);
    s6 = 0x960000;
    sq(s4, sp, 0x40);
    s5 = a1;
    sq(s3, sp, 0x30);
    s6 = addiu(s6, 392);  // &0x960188 (free-list alloc slot)
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    sw(a0, sp, 0xAC);
    lw(a0, v0, -4712);  // 0x95ED98 (Rt2d: the 20-byte polygon free list)
    v0 = 0x30000;
    a1 = v0 | 0x190;
    lw(v0, s6, 0);  // 0x960188 (free-list alloc slot)
    s4 = a2;
    jalr(ctx, 0x4B0918u, v0.u());
    sw(v0, sp, 0xA8);
    if (v0 != 0) {
        // 0x004b0928
        charge(ctx, 4);
        sw(zero, v0, 0);
        sw(zero, v0, 4);
        sw(zero, v0, 16);
        sw(zero, v0, 12);
    }
    // 0x004b0938
    charge(ctx, 3);
    lw(v0, sp, 0xA8);
    if (v0 != 0) {
        // 0x004b0944
        charge(ctx, 5);
        lw(v0, sp, 0xAC);
        s3 = 0;
        lw(s1, v0, 4);
        s2 = 0;
        if (s1 != s5) {
            for (;;) {
                // 0x004b0958
                charge(ctx, 7);
                lw(s1, s1, 0);
                if (s1 == s5) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004b0974
            charge(ctx, 1);
        }
        // 0x004b0978
        charge(ctx, 2);
        if (s1 != s4) {
            for (;;) {
                // 0x004b0980
                charge(ctx, 2);
                lw(v1, s1, 0);
                if (s3 == 0) {
                    // 0x004b0ab4
                    charge(ctx, 2);
                    sw(s1, s1, 0);
                    backedge(ctx);
                } else {
                    // 0x004b0988
                    charge(ctx, 4);
                    lw(v0, s3, 0);
                    sw(v0, s1, 0);
                    sw(s1, s3, 0);
                }
                // 0x004b0998
                charge(ctx, 4);
                s3 = s1;
                s1 = v1;
                s7 = addiu(s7, 1);
                if (v1 == s4) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004b09a8
        charge(ctx, 10);
        v0 = 0x960000;
        lw(a0, v0, -4716);  // 0x95ED94 (Rt2d: the 8-byte polygon-vertex free list)
        v0 = 0x30000;
        a1 = v0 | 0x190;
        lw(v0, s6, 0);
        jalr(ctx, 0x4B09BCu, v0.u());
        s0 = v0;
        if (s0 != 0) {
            // 0x004b09d0
            charge(ctx, 3);
            sw(zero, s0, 0);
            v0 = si(-1);
            sw(v0, s0, 4);
        }
        // 0x004b09dc
        charge(ctx, 3);
        lw(v0, s4, 4);
        sw(v0, s0, 4);
        if (s3 == 0) {
            // 0x004b0ac0
            charge(ctx, 2);
            sw(s0, s0, 0);
            backedge(ctx);
        } else {
            // 0x004b09e8
            charge(ctx, 3);
            lw(v0, s3, 0);
            sw(v0, s0, 0);
            sw(s0, s3, 0);
        }
        // 0x004b09f4
        charge(ctx, 2);
        if (s1 != s5) {
            for (;;) {
                // 0x004b09fc
                charge(ctx, 2);
                lw(v1, s1, 0);
                if (s2 == 0) {
                    // 0x004b0ac8
                    charge(ctx, 2);
                    sw(s1, s1, 0);
                    backedge(ctx);
                } else {
                    // 0x004b0a04
                    charge(ctx, 3);
                    lw(v0, s2, 0);
                    sw(v0, s1, 0);
                    sw(s1, s2, 0);
                }
                // 0x004b0a10
                charge(ctx, 4);
                s2 = s1;
                s1 = v1;
                fp = addiu(fp, 0x1);
                if (v1 == s5) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004b0a20
        charge(ctx, 8);
        v0 = 0x960000;
        lw(v1, s6, 0);
        a1 = 0x30000;
        lw(a0, v0, -4716);  // 0x95ED94 (Rt2d: the 8-byte polygon-vertex free list)
        a1 = a1 | 0x190;
        jalr(ctx, 0x4B0A30u, v1.u());
        if (v0 != 0) {
            // 0x004b0a40
            charge(ctx, 3);
            sw(zero, v0, 0);
            v1 = si(-1);
            sw(v1, v0, 4);
        }
        // 0x004b0a4c
        charge(ctx, 3);
        lw(v1, s5, 4);
        sw(v1, v0, 4);
        if (s2 == 0) {
            // 0x004b0ad0
            charge(ctx, 2);
            sw(v0, v0, 0);
            backedge(ctx);
        } else {
            // 0x004b0a58
            charge(ctx, 3);
            lw(v1, s2, 0);
            sw(v1, v0, 0);
            sw(v0, s2, 0);
        }
        // 0x004b0a64
        charge(ctx, 18);
        lw(v1, sp, 0xAC);
        a0 = addiu(s7, 1);
        sw(s0, v1, 4);
        lw(v1, sp, 0xA8);
        sw(v0, v1, 4);
        lw(v0, sp, 0xAC);
        v1 = addiu(fp, 0x1);
        sw(a0, v0, 12);
        lw(v0, sp, 0xA8);
        sw(v1, v0, 12);
        lw(v0, sp, 0xAC);
        lw(v1, v0, 16);
        lw(v0, sp, 0xA8);
        sw(v1, v0, 16);
        lw(v0, sp, 0xAC);
        lw(v1, v0, 8);
        lw(v0, sp, 0xA8);
        sw(v1, v0, 8);
    }
    // 0x004b0aac
    charge(ctx, 2);
    lw(v0, sp, 0xA8);
    // 0x004b0ad8
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
    sp = addiu(sp, 0xB0);
}


// sub_4B0DF0 [rt2dPolygonCreate] -- a polygon from a flattened path: its points copied (8 bytes each) and a ring of vertex records
// The last point (the closing duplicate) dropped. Returns the polygon (0 when the allocation fails).
// 0x004B0DF0 sub_4B0DF0 -- 424 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B0DF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x004b0df0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    v0 = si(-1);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, 4);
    s0 = a0;
    if (v1 != v0) {
        // 0x004b0e34
        charge(ctx, 2);
        lw(v0, s0, 0);
        s5 = v0;
    } else {
        // 0x004b0e24
        charge(ctx, 4);
        link(ctx, 0x4B0E24u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 0);
        call(ctx, gen::fn_sub_4C2090_004c2090);
        s5 = v0;
    }
    // 0x004b0e3c
    charge(ctx, 4);
    v1 = si(-1);
    lw(v0, s0, 4);
    if (v0 == v1) {
        // 0x004b0e4c
        charge(ctx, 2);
        link(ctx, 0x4B0E4Cu);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 0);
        call(ctx, gen::fn_sub_4C2120_004c2120);
    }
    // 0x004b0e54
    charge(ctx, 12);
    s0 = addiu(v0, -1);
    s6 = 0x960000;
    v0 = 0x960000;
    v1 = 0x30000;
    lw(a0, v0, -4712);  // 0x95ED98 (Rt2d: the 20-byte polygon free list)
    s6 = addiu(s6, 392);  // &0x960188 (free-list alloc slot)
    lw(v0, s6, 0);  // 0x960188 (free-list alloc slot)
    a1 = v1 | 0x190;
    jalr(ctx, 0x4B0E70u, v0.u());
    s2 = v0;
    if (s2 != 0) {
        // 0x004b0e84
        charge(ctx, 4);
        sw(zero, s2, 0);
        sw(zero, s2, 4);
        sw(zero, s2, 16);
        sw(zero, s2, 12);
    }
    // 0x004b0e94
    charge(ctx, 2);
    if (s2 != 0) {
        // 0x004b0e9c
        charge(ctx, 10);
        v0 = 0x30000;
        a1 = v0 | 0x190;
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
        a0 = sll(s0, 3);
        jalr(ctx, 0x4B0EACu, v0.u());
        sw(v0, s2, 16);
        lw(v0, s2, 16);
        if (v0 != 0) {
            // 0x004b0ec4
            charge(ctx, 4);
            v0 = slt(0, s0);
            s3 = 0;
            s4 = 0;
            if (v0 != 0) {
                // 0x004b0ee4
                charge(ctx, 1);
                s1 = 0;
                for (;;) {
                    // 0x004b0ee8
                    charge(ctx, 8);
                    v0 = 0x960000;
                    v1 = 0x30000;
                    lw(a0, v0, -4716);  // 0x95ED94 (Rt2d: the 8-byte polygon-vertex free list)
                    lw(v0, s6, 0);
                    a1 = v1 | 0x190;
                    jalr(ctx, 0x4B0EF8u, v0.u());
                    if (v0 != 0) {
                        // 0x004b0f08
                        charge(ctx, 4);
                        sw(zero, v0, 0);
                        v1 = si(-1);
                        sw(v1, v0, 4);
                    }
                    // 0x004b0f18
                    charge(ctx, 8);
                    sw(s4, v0, 4);
                    lw(v1, s2, 16);
                    lwc1(f1, s5, 4);
                    lwc1(f0, s5, 8);
                    v1 = addu(v1, s1);
                    swc1(f1, v1, 0);
                    swc1(f0, v1, 4);
                    if (s3 == 0) {
                        // 0x004b0f68
                        charge(ctx, 2);
                        sw(v0, v0, 0);
                        backedge(ctx);
                    } else {
                        // 0x004b0f38
                        charge(ctx, 4);
                        lw(v1, s3, 0);
                        sw(v1, v0, 0);
                        sw(v0, s3, 0);
                    }
                    // 0x004b0f48
                    charge(ctx, 6);
                    s3 = v0;
                    s4 = addiu(s4, 1);
                    s5 = addiu(s5, 24);
                    v0 = slt(s4, s0);
                    s1 = addiu(s1, 8);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004b0f60
                charge(ctx, 2);
                sw(s3, s2, 4);
                backedge(ctx);
            } else {
                // 0x004b0ed4
                charge(ctx, 1);
                sw(s3, s2, 4);
            }
            // 0x004b0ed8
            charge(ctx, 1);
            sw(s0, s2, 12);
        }
    }
    // 0x004b0edc
    charge(ctx, 2);
    v0 = s2;
    // 0x004b0f70
    charge(ctx, 10);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}


// sub_4B1050 [rt2dPolygonClose] -- destroys the two polygon free lists
// 0x004B1050 sub_4B1050 -- 60 bytes; frame 0x10: ra sp+0x0
void sub_4B1050(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b1050
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x960000;
    sd(ra, sp, 0x0);
    link(ctx, 0x4B105Cu);  // $ra first: the delay slot below depends on it
    lw(a0, v0, -4716);  // 0x95ED94 (Rt2d: the 8-byte polygon-vertex free list)
    call(ctx, gen::fn_sub_4C3C30_004c3c30);
    v0 = 0x960000;
    link(ctx, 0x4B1068u);  // $ra first: the delay slot below depends on it
    lw(a0, v0, -4712);  // 0x95ED98 (Rt2d: the 20-byte polygon free list)
    call(ctx, gen::fn_sub_4C3C30_004c3c30);
    a0 = 0x960000;
    v1 = 0x960000;
    sw(zero, a0, -4716);  // 0x95ED94 (Rt2d: the 8-byte polygon-vertex free list)
    sw(zero, v1, -4712);  // 0x95ED98 (Rt2d: the 20-byte polygon free list)
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}


// sub_4B1090 [rt2dPolygonOpen] -- creates the 8-byte vertex and 20-byte polygon free lists (static blocks); 1
// 0x004B1090 sub_4B1090 -- 112 bytes; frame 0x10: ra sp+0x0
void sub_4B1090(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b1090
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t0 = 0x960000;
    sd(ra, sp, 0x0);
    v0 = 0x40000;
    lw(a1, gp, -20496);  // 0x7CDCE0
    a0 = 8;
    lw(a3, gp, -20492);  // 0x7CDCE4
    a2 = 4;
    t0 = addiu(t0, -1552);  // &0x95F9F0
    t1 = v0 | 0x190;
    jal(ctx, 0x4B10B4u, gen::fn_sub_4C3B60_004c3b60);
    lw(a1, gp, -20504);  // 0x7CDCD8
    v1 = 0x960000;
    lw(a3, gp, -20500);  // 0x7CDCDC
    t0 = 0x960000;
    sw(v0, v1, -4716);  // 0x95ED94 (Rt2d: the 8-byte polygon-vertex free list)
    a0 = 20;
    v0 = 0x40000;
    a2 = 4;
    t0 = addiu(t0, -1504);  // &0x95FA20
    t1 = v0 | 0x190;
    jal(ctx, 0x4B10E0u, gen::fn_sub_4C3B60_004c3b60);
    v1 = 0x960000;
    sw(v0, v1, -4712);  // 0x95ED98 (Rt2d: the 20-byte polygon free list)
    ld(ra, sp, 0x0);
    v0 = 1;
    sp = addiu(sp, 0x10);
}


// rt2dPS2PipeOpen -- the toolkit's 2-D pipelines: RpPDSGetPipe(0x1001A) font, (0x1001E) stroke, (0x1001C) fill, two slots each; 1
// 0x004B1100 rt2dPS2PipeOpen -- 160 bytes; frame 0x10: ra sp+0x0
void rt2dPS2PipeOpen(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b1100
    enter(ctx, 40);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x960000;
    sd(ra, sp, 0x0);
    sw(zero, v0, -4044);  // 0x95F034
    v0 = 0x960000;
    sw(zero, v0, -4040);  // 0x95F038
    v0 = 0x10000;
    a0 = v0 | 0x1A;
    jal(ctx, 0x4B111Cu, gen::fn_RpPDSGetPipe_0046a890);
    v1 = 0x960000;
    a0 = 0x10000;
    sw(v0, v1, -4036);  // 0x95F03C
    a0 = a0 | 0x1A;
    jal(ctx, 0x4B1130u, gen::fn_RpPDSGetPipe_0046a890);
    v1 = 0x960000;
    a0 = 0x10000;
    sw(v0, v1, -4032);  // 0x95F040
    a0 = a0 | 0x1E;
    jal(ctx, 0x4B1144u, gen::fn_RpPDSGetPipe_0046a890);
    v1 = 0x960000;
    a0 = 0x10000;
    sw(v0, v1, -4020);  // 0x95F04C
    a0 = a0 | 0x1E;
    jal(ctx, 0x4B1158u, gen::fn_RpPDSGetPipe_0046a890);
    v1 = 0x960000;
    a0 = 0x10000;
    sw(v0, v1, -4016);  // 0x95F050
    a0 = a0 | 0x1C;
    jal(ctx, 0x4B116Cu, gen::fn_RpPDSGetPipe_0046a890);
    v1 = 0x960000;
    a0 = 0x10000;
    sw(v0, v1, -4028);  // 0x95F044
    a0 = a0 | 0x1C;
    jal(ctx, 0x4B1180u, gen::fn_RpPDSGetPipe_0046a890);
    v1 = 0x960000;
    sw(v0, v1, -4024);  // 0x95F048
    ld(ra, sp, 0x0);
    v0 = 1;
    sp = addiu(sp, 0x10);
}


// sub_4B11A0 [rt2dPS2PipeClose] -- clears the eight 2-D pipeline slots
// 0x004B11A0 sub_4B11A0 -- 68 bytes; leaf frame (no stack)
void sub_4B11A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3};
    // 0x004b11a0
    enter(ctx, 17);  // entry check point + this block's cycles
    v1 = 0x960000;
    sw(zero, v1, -4044);  // 0x95F034
    v1 = 0x960000;
    sw(zero, v1, -4040);  // 0x95F038
    v1 = 0x960000;
    sw(zero, v1, -4036);  // 0x95F03C
    v1 = 0x960000;
    sw(zero, v1, -4032);  // 0x95F040
    v1 = 0x960000;
    sw(zero, v1, -4020);  // 0x95F04C
    v1 = 0x960000;
    sw(zero, v1, -4016);  // 0x95F050
    v1 = 0x960000;
    sw(zero, v1, -4028);  // 0x95F044
    v1 = 0x960000;
    sw(zero, v1, -4024);  // 0x95F048
}


// sub_4B11F0 [rt2dListDestroyCB] -- a list-walk callback: destroys one record (sub_4B1C80) and folds the success into *$a3
// 0x004B11F0 sub_4B11F0 -- 80 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B11F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b11f0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a2;
    s0 = a3;
    a0 = s1;
    jal(ctx, 0x4B1208u, gen::fn_sub_4B1C80_004b1c80);
    v0 = sltu(0, v0);
    if (v0 != 0) {
        // 0x004b121c
        charge(ctx, 2);
        lw(v0, s0, 0);
        v0 = sltu(0, v0);
    }
    // 0x004b1224 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    sw(v0, s0, 0);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_4B1240 [rt2dListDestroy] -- destroys every record of a list (sub_4B1990 with sub_4B11F0), then the sList; the list
// 0x004B1240 sub_4B1240 -- 76 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4B1240(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b1240
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    a2 = a1;
    sd(ra, sp, 0x10);
    a1 = 0x4B0000;
    sq(s0, sp, 0x0);
    v0 = 1;
    s0 = a0;
    sw(v0, sp, 0x2C);
    a1 = addiu(a1, 4592);  // &sub_4B11F0
    a3 = addiu(sp, 0x2C);
    jal(ctx, 0x4B1264u, gen::fn_sub_4B1990_004b1990);
    link(ctx, 0x4B126Cu);  // $ra first: the delay slot below depends on it
    lw(a0, s0, 0);
    call(ctx, gen::fn_sub_4C20B0_004c20b0);
    sw(zero, s0, 0);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_4B1990 [rt2dListForAll] -- calls $a1(list, $a2, record, $a3) on each record of a list's 8-byte sList entries; the list
// 0x004B1990 sub_4B1990 -- 160 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B1990(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x004b1990
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    s3 = a2;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, a0, 0);
    s2 = a3;
    jal(ctx, 0x4B19C0u, gen::fn_sub_4C2090_004c2090);
    lw(a0, s5, 0);
    s1 = v0;
    jal(ctx, 0x4B19CCu, gen::fn_sub_4C2120_004c2120);
    v0 = sll(v0, 3);
    s0 = addu(s1, v0);
    if (s1 != s0) {
        for (;;) {
            // 0x004b19e4
            charge(ctx, 9);
            lw(a2, s1, 4);
            lwc1(f12, s1, 0);
            a0 = s5;
            a1 = s3;
            a3 = s2;
            jalr(ctx, 0x4B19F4u, s4.u());
            s1 = addiu(s1, 8);
            if (s1 == s0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004b1a08 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    v0 = s5;
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}


// sub_4B1A30 [rt2dListGetCount] -- the entry count of a list's sList
// 0x004B1A30 sub_4B1A30 -- 8 bytes; leaf frame (no stack)
void sub_4B1A30(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4};
    // 0x004b1a30
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(a0, a0, 0);
    gen::fn_sub_4C2120_004c2120(ctx);  // tail call
}


// sub_4B1A40 [rt2dListGetRecord] -- the record of entry $a1 (its second word)
// 0x004B1A40 sub_4B1A40 -- 32 bytes; frame 0x10: ra sp+0x0
void sub_4B1A40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b1a40
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    link(ctx, 0x4B1A48u);  // $ra first: the delay slot below depends on it
    lw(a0, a0, 0);
    call(ctx, gen::fn_sub_4C21B0_004c21b0);
    ld(ra, sp, 0x0);
    lw(v0, v0, 4);
    sp = addiu(sp, 0x10);
}


// sub_4B1A80 [rt2dListGetCursorIndex] -- the index of the list's cursor (+16) in its sList, or -1 without a cursor
// 0x004B1A80 sub_4B1A80 -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4B1A80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b1a80
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, 16);
    s0 = a0;
    if (v0 == 0) {
        // 0x004b1ac0
        charge(ctx, 1);
        v0 = si(-1);
    L_004b1ac4:
        charge(ctx, 1);
        ld(ra, sp, 0x10);
    } else {
        // 0x004b1a98
        charge(ctx, 6);
        link(ctx, 0x4B1A98u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 0);
        call(ctx, gen::fn_sub_4C2090_004c2090);
        lw(v1, s0, 16);
        v1 = subu(v1, v0);
        v0 = sra(v1, 3);
        if (i64(v1) >= 0) {
            goto L_004b1ac4;
        }
        // 0x004b1ab0
        charge(ctx, 4);
        v0 = addiu(v1, 7);
        v0 = sra(v0, 3);
        ld(ra, sp, 0x10);
    }
    // 0x004b1ac8 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4B1AE0 [rt2dListGetCursorTime] -- the float at the cursor (+16), or 0
// 0x004B1AE0 sub_4B1AE0 -- 32 bytes; leaf frame (no stack)
void sub_4B1AE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4};
    Fpr f0{ctx, 0};
    // 0x004b1ae0
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, 16);
    if (v0 == 0) {
        // 0x004b1af4
        charge(ctx, 1);
        mtc1(zero, f0);
    } else {
        // 0x004b1aec
        charge(ctx, 2);
        lwc1(f0, v0, 0);
    }
    // 0x004b1af8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_4B1B00 [rt2dListGetNextIndex] -- the index of the next pointer (+20) in the sList, or the count without one
// 0x004B1B00 sub_4B1B00 -- 88 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4B1B00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b1b00
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, 20);
    s0 = a0;
    if (v0 == 0) {
        // 0x004b1b40
        charge(ctx, 2);
        link(ctx, 0x4B1B40u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 0);
        call(ctx, gen::fn_sub_4C2120_004c2120);
    L_004b1b48:
        charge(ctx, 1);
        ld(ra, sp, 0x10);
    } else {
        // 0x004b1b18
        charge(ctx, 6);
        link(ctx, 0x4B1B18u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 0);
        call(ctx, gen::fn_sub_4C2090_004c2090);
        lw(v1, s0, 20);
        v1 = subu(v1, v0);
        v0 = sra(v1, 3);
        if (i64(v1) >= 0) {
            goto L_004b1b48;
        }
        // 0x004b1b30
        charge(ctx, 4);
        v0 = addiu(v1, 7);
        v0 = sra(v0, 3);
        ld(ra, sp, 0x10);
    }
    // 0x004b1b4c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4B1B60 [rt2dListGetNextTime] -- the float at the next pointer (+20), else at the end pointer (+24)
// 0x004B1B60 sub_4B1B60 -- 36 bytes; leaf frame (no stack)
void sub_4B1B60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    Fpr f0{ctx, 0};
    // 0x004b1b60
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, 20);
    if (v0 == 0) {
        // 0x004b1b74
        charge(ctx, 2);
        lw(v0, a0, 24);
        lwc1(f0, v0, 0);
    } else {
        // 0x004b1b6c
        charge(ctx, 2);
        lwc1(f0, v0, 0);
    }
    // 0x004b1b7c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_4B1B90 [rt2dListIsLooping] -- bit 1 of the list's flags (+12)
// 0x004B1B90 sub_4B1B90 -- 16 bytes; leaf frame (no stack)
void sub_4B1B90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x004b1b90
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, 12);
    v0 = v0 & 0x2;
    v0 = sltu(0, v0);
}


// sub_4B1C80 [rt2dRecordDestroy] -- destroys a 12-byte record: its data (an sList when +4, else RwFree) and the record; 1 for a record
// 0x004B1C80 sub_4B1C80 -- 124 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B1C80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004b1c80
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = sltu(0, s1);
    if (s0 != 0) {
        // 0x004b1ca0
        charge(ctx, 3);
        lw(v0, s1, 4);
        if (v0 == 0) {
            // 0x004b1cbc
            charge(ctx, 4);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C (RwFree slot)
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x4B1CC4u);  // $ra = the return address
            lw(a0, s1, 8);
            call_ptr(ctx, jt);
        } else {
            // 0x004b1cac
            charge(ctx, 4);
            link(ctx, 0x4B1CACu);  // $ra first: the delay slot below depends on it
            lw(a0, s1, 8);
            call(ctx, gen::fn_sub_4C20B0_004c20b0);
        }
        // 0x004b1ccc
        charge(ctx, 6);
        v0 = 0x960000;
        a0 = 0x960000;
        lw(v0, v0, 396);  // 0x96018C (free-list free slot)
        a1 = s1;
        a0 = addiu(a0, -1204);  // &0x95FB4C (Rt2d: the 12-byte list-record free list)
        jalr(ctx, 0x4B1CDCu, v0.u());
    }
    // 0x004b1ce4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_4B2A90 [rt2dListAppendCB] -- a walk callback: appends $a0 to the sList $a2 (sub_4C1E70); returns $a0
// 0x004B2A90 sub_4B2A90 -- 56 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4B2A90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b2a90
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x30000;
    sd(ra, sp, 0x10);
    a1 = v0 | 0x1A9;
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = a2;
    jal(ctx, 0x4B2AA8u, gen::fn_sub_4C1E70_004c1e70);
    sw(s0, v0, 0);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4B2B40 [rt2dPropsEmpty] -- destroys the two sLists of a property set (+4, +12) and clears it; the set
// 0x004B2B40 sub_4B2B40 -- 88 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4B2B40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b2b40
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    sw(zero, a0, 0);
    s0 = a0;
    lw(a0, a0, 4);
    if (a0 != 0) {
        // 0x004b2b60
        charge(ctx, 2);
        jal(ctx, 0x4B2B60u, gen::fn_sub_4C20B0_004c20b0);
    }
    // 0x004b2b68
    charge(ctx, 4);
    sw(zero, s0, 4);
    lw(a0, s0, 12);
    if (a0 != 0) {
        // 0x004b2b78
        charge(ctx, 2);
        jal(ctx, 0x4B2B78u, gen::fn_sub_4C20B0_004c20b0);
    }
    // 0x004b2b80 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    sw(zero, s0, 12);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4B2BA0 [rt2dGetEntry0] -- the first word of sList entry $a1 of +4
// 0x004B2BA0 sub_4B2BA0 -- 32 bytes; frame 0x10: ra sp+0x0
void sub_4B2BA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b2ba0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    link(ctx, 0x4B2BA8u);  // $ra first: the delay slot below depends on it
    lw(a0, a0, 4);
    call(ctx, gen::fn_sub_4C21B0_004c21b0);
    ld(ra, sp, 0x0);
    lw(v0, v0, 0);
    sp = addiu(sp, 0x10);
}


// sub_4B2BD0 [rt2dSListDestroy1] -- destroys an sList (sub_4C20B0); 1
// 0x004B2BD0 sub_4B2BD0 -- 32 bytes; frame 0x10: ra sp+0x0
void sub_4B2BD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b2bd0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x4B2BD8u, gen::fn_sub_4C20B0_004c20b0);
    ld(ra, sp, 0x0);
    v0 = 1;
    sp = addiu(sp, 0x10);
}


// j__rwSListGetEntry -- the sList entry getter (a tail call to sub_4C21B0)
// 0x004B2C70 j__rwSListGetEntry -- 8 bytes; leaf frame (no stack)
void j__rwSListGetEntry(EEContext& ctx) {
    using namespace hg;
    // 0x004b2c70
    enter(ctx, 2);  // entry check point + this block's cycles
    gen::fn_sub_4C21B0_004c21b0(ctx);  // tail call
}


// sub_4B2E70 [rt2dMessageListDestroy] -- resets every 16-byte record of the message sList (+12) and destroys it; the owner
// 0x004B2E70 sub_4B2E70 -- 148 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B2E70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b2e70
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(a0, a0, 12);
    if (a0 != 0) {
        // 0x004b2e90
        charge(ctx, 5);
        jal(ctx, 0x4B2E90u, gen::fn_sub_4C2120_004c2120);
        s0 = v0;
        if (i64(s0) > 0) {
            // 0x004b2ea4
            charge(ctx, 6);
            link(ctx, 0x4B2EA4u);  // $ra first: the delay slot below depends on it
            lw(a0, s1, 12);
            call(ctx, gen::fn_sub_4C2090_004c2090);
            v1 = sll(s0, 4);
            a0 = addu(v0, v1);
            if (v0 != a0) {
                // 0x004b2ebc
                charge(ctx, 1);
                v1 = si(-1);
                for (;;) {
                    // 0x004b2ec0
                    charge(ctx, 7);
                    sw(zero, v0, 0);
                    sw(v1, v0, 4);
                    sw(zero, v0, 8);
                    sw(zero, v0, 12);
                    v0 = addiu(v0, 16);
                    if (v0 == a0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004b2edc
                charge(ctx, 1);
            }
        }
        // 0x004b2ee0
        charge(ctx, 3);
        link(ctx, 0x4B2EE0u);  // $ra first: the delay slot below depends on it
        lw(a0, s1, 12);
        call(ctx, gen::fn_sub_4C20B0_004c20b0);
        sw(zero, s1, 12);
    }
    // 0x004b2eec (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_4B3030 [rt2dMessageGet] -- the 16-byte record $a1 of the message sList (+12), or 0 out of range
// 0x004B3030 sub_4B3030 -- 112 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B3030(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b3030
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s1 = a1;
    lw(a0, a0, 12);
    s0 = 0;
    if (a0 != 0) {
        // 0x004b3058
        charge(ctx, 4);
        jal(ctx, 0x4B3058u, gen::fn_sub_4C2120_004c2120);
        if (i64(v0) > 0) {
            // 0x004b3068
            charge(ctx, 3);
            at = slt(s1, v0);
            if (at != 0) {
                // 0x004b3074
                charge(ctx, 4);
                link(ctx, 0x4B3074u);  // $ra first: the delay slot below depends on it
                lw(a0, s2, 12);
                call(ctx, gen::fn_sub_4C2090_004c2090);
                v1 = sll(s1, 4);
                s0 = addu(v0, v1);
            }
        }
    }
    // 0x004b3084 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = s0;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_4B30A0 [rt2dStateInitA] -- a state record: -1, -1, 0, 0, then 32 words of -1
// 0x004B30A0 sub_4B30A0 -- 84 bytes; leaf frame (no stack)
void sub_4B30A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x004b30a0
    enter(ctx, 7);  // entry check point + this block's cycles
    v1 = si(-1);
    a2 = 0;
    sw(v1, a0, 0);
    a1 = a0;
    sw(v1, a0, 4);
    sw(zero, a0, 8);
    sw(zero, a0, 12);
    for (;;) {
        // 0x004b30bc
        charge(ctx, 12);
        sw(v1, a1, 16);
        a2 = addiu(a2, 8);
        sw(v1, a1, 20);
        v0 = slti(a2, 32);
        sw(v1, a1, 24);
        sw(v1, a1, 28);
        sw(v1, a1, 32);
        sw(v1, a1, 36);
        sw(v1, a1, 40);
        sw(v1, a1, 44);
        a1 = addiu(a1, 32);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004b30ec
    charge(ctx, 2);
    v0 = a0;
}


// sub_4B3100 [rt2dStateInitB] -- a state record: -1, -1, 0, 0, then 32 words of -1 (a copy of sub_4B30A0)
// 0x004B3100 sub_4B3100 -- 84 bytes; leaf frame (no stack)
void sub_4B3100(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x004b3100
    enter(ctx, 7);  // entry check point + this block's cycles
    v1 = si(-1);
    a2 = 0;
    sw(v1, a0, 0);
    a1 = a0;
    sw(v1, a0, 4);
    sw(zero, a0, 8);
    sw(zero, a0, 12);
    for (;;) {
        // 0x004b311c
        charge(ctx, 12);
        sw(v1, a1, 16);
        a2 = addiu(a2, 8);
        sw(v1, a1, 20);
        v0 = slti(a2, 32);
        sw(v1, a1, 24);
        sw(v1, a1, 28);
        sw(v1, a1, 32);
        sw(v1, a1, 36);
        sw(v1, a1, 40);
        sw(v1, a1, 44);
        a1 = addiu(a1, 32);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004b314c
    charge(ctx, 2);
    v0 = a0;
}


// sub_4B3490 [rt2dLabelsDestroy] -- destroys the label sList (+16) when there is one; the owner
// 0x004B3490 sub_4B3490 -- 60 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4B3490(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b3490
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, 16);
    if (a0 != 0) {
        // 0x004b34ac
        charge(ctx, 3);
        jal(ctx, 0x4B34ACu, gen::fn_sub_4C20B0_004c20b0);
        sw(zero, s0, 16);
    }
    // 0x004b34b8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4B34D0 [rt2dLabelGet] -- the label entry $a1 (sub_4C21B0 on +16)
// 0x004B34D0 sub_4B34D0 -- 8 bytes; leaf frame (no stack)
void sub_4B34D0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4};
    // 0x004b34d0
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(a0, a0, 16);
    gen::fn_sub_4C21B0_004c21b0(ctx);  // tail call
}


// sub_4B34E0 [rt2dButtonTableInit] -- fills a 64-word button transition table with its constants; returns the end (+480)
// 0x004B34E0 sub_4B34E0 -- 296 bytes; leaf frame (no stack)
void sub_4B34E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11};
    // 0x004b34e0
    enter(ctx, 74);  // entry check point + this block's cycles
    sw(zero, a0, 0);
    t3 = 1;
    sw(t3, a0, 4);
    t2 = 16;
    sw(zero, a0, 8);
    t1 = 1024;
    sw(zero, a0, 12);
    t0 = 2560;
    sw(zero, a0, 16);
    a3 = 32;
    sw(t3, a0, 20);
    a2 = 64;
    sw(zero, a0, 24);
    a1 = 4352;
    sw(zero, a0, 28);
    v1 = 128;
    sw(t2, a0, 32);
    v0 = addiu(a0, 480);
    sw(zero, a0, 36);
    sw(zero, a0, 40);
    sw(t3, a0, 44);
    sw(zero, a0, 48);
    sw(zero, a0, 52);
    sw(t3, a0, 56);
    sw(zero, a0, 60);
    sw(t1, a0, 64);
    sw(t3, a0, 68);
    sw(zero, a0, 72);
    sw(zero, a0, 76);
    sw(zero, a0, 80);
    sw(t3, a0, 84);
    sw(zero, a0, 88);
    sw(zero, a0, 92);
    sw(zero, a0, 96);
    sw(zero, a0, 100);
    sw(zero, a0, 104);
    sw(t3, a0, 108);
    sw(t0, a0, 112);
    sw(zero, a0, 116);
    sw(t3, a0, 120);
    sw(zero, a0, 124);
    sw(a3, a0, 128);
    sw(t3, a0, 132);
    sw(zero, a0, 136);
    sw(zero, a0, 140);
    sw(zero, a0, 144);
    sw(zero, a0, 148);
    sw(zero, a0, 152);
    sw(t3, a0, 156);
    sw(zero, a0, 160);
    sw(zero, a0, 164);
    sw(zero, a0, 168);
    sw(t3, a0, 172);
    sw(a2, a0, 176);
    sw(zero, a0, 180);
    sw(t3, a0, 184);
    sw(zero, a0, 188);
    sw(zero, a0, 192);
    sw(t3, a0, 196);
    sw(zero, a0, 200);
    sw(zero, a0, 204);
    sw(a1, a0, 208);
    sw(t3, a0, 212);
    sw(zero, a0, 216);
    sw(zero, a0, 220);
    sw(v1, a0, 224);
    sw(zero, a0, 228);
    sw(zero, a0, 232);
    sw(t3, a0, 236);
    sw(zero, a0, 240);
    sw(zero, a0, 244);
    sw(t3, a0, 248);
    sw(zero, a0, 252);
}


// sub_4B3610 [rt2dButtonSetState] -- a button's state: the sub-objects by the flags (+8 bits 0..3) made visible or hidden
// Bit 0: the button object; bit 1: its first child shown; bits 2 / 3: the next children hidden. Returns the button.
// 0x004B3610 sub_4B3610 -- 228 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B3610(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b3610
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, 8);
    v0 = v0 & 0x1;
    s2 = a0;
    if (v0 != 0) {
        // 0x004b363c
        charge(ctx, 8);
        a0 = a1;
        link(ctx, 0x4B3640u);  // $ra first: the delay slot below depends on it
        lw(a1, s2, 4);
        call(ctx, gen::fn_sub_4AE900_004ae900);
        s0 = v0;
        lw(v0, s2, 8);
        v0 = v0 & 0x2;
        s1 = 1;
        if (v0 != 0) {
            // 0x004b369c
            charge(ctx, 8);
            a0 = s0;
            a1 = s1;
            jal(ctx, 0x4B36A0u, gen::fn_sub_4AE900_004ae900);
            a0 = v0;
            a1 = s1;
            jal(ctx, 0x4B36ACu, gen::fn_sub_4ADFD0_004adfd0);
            s1 = addiu(s1, 1);
            backedge(ctx);
        }
        // 0x004b365c
        charge(ctx, 4);
        lw(v0, s2, 8);
        v0 = v0 & 0x4;
        if (v0 != 0) {
            // 0x004b36bc
            charge(ctx, 8);
            a0 = s0;
            a1 = s1;
            jal(ctx, 0x4B36C0u, gen::fn_sub_4AE900_004ae900);
            a0 = v0;
            a1 = 0;
            jal(ctx, 0x4B36CCu, gen::fn_sub_4ADFD0_004adfd0);
            s1 = addiu(s1, 1);
            backedge(ctx);
        }
        // 0x004b366c
        charge(ctx, 4);
        lw(v0, s2, 8);
        v0 = v0 & 0x8;
        if (v0 == 0) {
            backedge(ctx);
        } else {
            // 0x004b367c
            charge(ctx, 8);
            a0 = s0;
            a1 = s1;
            jal(ctx, 0x4B3680u, gen::fn_sub_4AE900_004ae900);
            a0 = v0;
            a1 = 0;
            jal(ctx, 0x4B368Cu, gen::fn_sub_4ADFD0_004adfd0);
            backedge(ctx);
        }
    }
    // 0x004b3634
    charge(ctx, 2);
    v0 = s2;
    // 0x004b36dc
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_4B3700 [rt2dNullCallBack] -- a default callback: returns 0
// 0x004B3700 sub_4B3700 -- 8 bytes; leaf frame (no stack)
void sub_4B3700(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x004b3700
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}


// sub_4B3720 [rt2dPassCallBack] -- a default callback: returns its second argument
// 0x004B3720 sub_4B3720 -- 8 bytes; leaf frame (no stack)
void sub_4B3720(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5};
    // 0x004b3720
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = a1;
}


// sub_4B3790 [rt2dFrameListsDestroy] -- destroys the maestro's index sList (+24) and resets / destroys its 16-byte frame sList (+20)
// 0x004B3790 sub_4B3790 -- 360 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B3790(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b3790
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    lw(a0, a0, 24);
    if (a0 != 0) {
        // 0x004b37b4
        charge(ctx, 2);
        jal(ctx, 0x4B37B4u, gen::fn_sub_4C20B0_004c20b0);
    }
    // 0x004b37bc
    charge(ctx, 4);
    sw(zero, s2, 24);
    lw(s1, s2, 20);
    if (s1 != 0) {
        // 0x004b37cc
        charge(ctx, 5);
        a0 = s1;
        jal(ctx, 0x4B37CCu, gen::fn_sub_4C2120_004c2120);
        s0 = v0;
        if (i64(s0) > 0) {
            // 0x004b37e0
            charge(ctx, 5);
            a0 = s1;
            jal(ctx, 0x4B37E0u, gen::fn_sub_4C2090_004c2090);
            at = slt(0, s0);
            a2 = 0;
            if (at != 0) {
                // 0x004b37f4
                charge(ctx, 3);
                at = slti(s0, 9);
                a1 = addiu(s0, -8);
                if (at == 0) {
                    // 0x004b3800
                    charge(ctx, 3);
                    at = slt(s0, 0);
                    v1 = 0;
                    if (at == 0) {
                        // 0x004b380c
                        charge(ctx, 5);
                        at = 0x7FFF0000;
                        at = at | 0xFFFF;
                        at = slt(s0, at);
                        if (at != 0) {
                            // 0x004b3820
                            charge(ctx, 1);
                            v1 = 1;
                        }
                    }
                    // 0x004b3824
                    charge(ctx, 2);
                    if (v1 != 0) {
                        // 0x004b382c
                        charge(ctx, 1);
                        a0 = si(-1);
                        for (;;) {
                            // 0x004b3830
                            charge(ctx, 28);
                            sw(zero, v0, 0);
                            a2 = addiu(a2, 8);
                            sw(a0, v0, 4);
                            v1 = slt(a2, a1);
                            sw(zero, v0, 8);
                            sw(zero, v0, 16);
                            sw(a0, v0, 20);
                            sw(zero, v0, 24);
                            sw(zero, v0, 32);
                            sw(a0, v0, 36);
                            sw(zero, v0, 40);
                            sw(zero, v0, 48);
                            sw(a0, v0, 52);
                            sw(zero, v0, 56);
                            sw(zero, v0, 64);
                            sw(a0, v0, 68);
                            sw(zero, v0, 72);
                            sw(zero, v0, 80);
                            sw(a0, v0, 84);
                            sw(zero, v0, 88);
                            sw(zero, v0, 96);
                            sw(a0, v0, 100);
                            sw(zero, v0, 104);
                            sw(zero, v0, 112);
                            sw(a0, v0, 116);
                            sw(zero, v0, 120);
                            v0 = addiu(v0, 128);
                            if (v1 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                    }
                }
                // 0x004b38a0
                charge(ctx, 3);
                at = slt(a2, s0);
                if (at != 0) {
                    // 0x004b38ac
                    charge(ctx, 1);
                    a0 = si(-1);
                    for (;;) {
                        // 0x004b38b0
                        charge(ctx, 7);
                        sw(zero, v0, 0);
                        a2 = addiu(a2, 1);
                        sw(a0, v0, 4);
                        v1 = slt(a2, s0);
                        sw(zero, v0, 8);
                        v0 = addiu(v0, 16);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004b38cc
                    charge(ctx, 1);
                }
            }
        }
        // 0x004b38d0
        charge(ctx, 2);
        a0 = s1;
        jal(ctx, 0x4B38D0u, gen::fn_sub_4C20B0_004c20b0);
    }
    // 0x004b38d8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    sw(zero, s2, 20);
    v0 = s2;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_4B39F0 [rt2dMaestroQueueActions] -- queues the actions of frame $a1: the run of non-zero entries from its index (sub_4B3F50)
// Returns the maestro, or 0 when the queue is full.
// 0x004B39F0 sub_4B39F0 -- 200 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B39F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b39f0
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, 24);
    s1 = a1;
    jal(ctx, 0x4B3A10u, gen::fn_sub_4C2090_004c2090);
    v1 = sll(s1, 2);
    lw(a0, s0, 20);
    v0 = addu(v0, v1);
    lw(s1, v0, 0);
    a1 = s1;
    jal(ctx, 0x4B3A28u, gen::fn_sub_4C21B0_004c21b0);
    s3 = addiu(s1, 1);
    s1 = v0;
    lw(v0, v0, 0);
    s2 = 0;
    if (v0 != 0) {
        for (;;) {
            // 0x004b3a54
            charge(ctx, 7);
            lw(a0, s0, 20);
            a1 = s3;
            s2 = addiu(s2, 1);
            jal(ctx, 0x4B3A5Cu, gen::fn_sub_4C21B0_004c21b0);
            lw(v0, v0, 0);
            s3 = addiu(s3, 1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004b3a70
        charge(ctx, 2);
        backedge(ctx);
    }
    // 0x004b3a44
    charge(ctx, 2);
    if (i64(s2) > 0) {
        // 0x004b3a78
        charge(ctx, 8);
        lw(a1, s0, 32);
        a2 = s1;
        lw(t0, s0, 68);
        a3 = s2;
        a0 = s0;
        jal(ctx, 0x4B3A88u, gen::fn_sub_4B3F50_004b3f50);
        if (v0 != 0) {
            backedge(ctx);
            goto L_004b3a4c;
        }
        // 0x004b3a98
        charge(ctx, 1);
        v0 = 0;
        // 0x004b3a9c (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_004b3a4c:
    charge(ctx, 2);
    v0 = s0;
    // 0x004b3a9c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}


// sub_4B3DE0 [rt2dMaestroResolveTarget] -- an action's target frame: relative / absolute / via a nested scene's offset (sub_4B4A60)
// Writes it to *$a3; returns the action.
// 0x004B3DE0 sub_4B3DE0 -- 364 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B3DE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b3de0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    s1 = a2;
    lw(v0, a1, 4);
    s0 = a3;
    if (i64(v0) < 0) {
        // 0x004b3eb0
        charge(ctx, 3);
        lw(v1, s2, 8);
        if (i64(v1) > 0) {
            // 0x004b3ed8
            charge(ctx, 5);
            s4 = addiu(v1, -1);
            a1 = s1;
            jal(ctx, 0x4B3EDCu, gen::fn_sub_4B4A60_004b4a60);
            if (i64(s4) > 0) {
                for (;;) {
                    // 0x004b3efc
                    charge(ctx, 7);
                    lw(a1, v0, 52);
                    a0 = s3;
                    jal(ctx, 0x4B3F00u, gen::fn_sub_4B4A60_004b4a60);
                    s4 = addiu(s4, -1);
                    if (i64(s4) <= 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004b3f18
                charge(ctx, 2);
                lw(v1, v0, 52);
                backedge(ctx);
            } else {
                // 0x004b3eec
                charge(ctx, 1);
                lw(v1, v0, 52);
            }
            // 0x004b3ef0
            charge(ctx, 3);
            lw(v0, s2, 12);
            s1 = addu(v1, v0);
            backedge(ctx);
        } else {
            // 0x004b3ebc
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x004b3f20
                charge(ctx, 3);
                lw(v0, s2, 12);
                s1 = addu(s1, v0);
                backedge(ctx);
            } else {
                // 0x004b3ec4
                charge(ctx, 3);
                v0 = si(-1);
                if (v1 != v0) {
                    backedge(ctx);
                } else {
                    // 0x004b3ed0
                    charge(ctx, 2);
                    lw(s1, s2, 12);
                    backedge(ctx);
                }
            }
        }
    } else {
        // 0x004b3e14
        charge(ctx, 3);
        lw(v1, s2, 8);
        if (i64(v1) > 0) {
            // 0x004b3e4c
            charge(ctx, 5);
            s4 = addiu(v1, -1);
            a1 = s1;
            jal(ctx, 0x4B3E50u, gen::fn_sub_4B4A60_004b4a60);
            s1 = v0;
            if (i64(s4) > 0) {
                for (;;) {
                    // 0x004b3e60
                    charge(ctx, 7);
                    lw(a1, s1, 52);
                    a0 = s3;
                    jal(ctx, 0x4B3E64u, gen::fn_sub_4B4A60_004b4a60);
                    s4 = addiu(s4, -1);
                    s1 = v0;
                    if (i64(s4) <= 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004b3e7c
                charge(ctx, 1);
            }
            // 0x004b3e80
            charge(ctx, 7);
            lw(a1, s2, 12);
            a0 = s3;
            jal(ctx, 0x4B3E84u, gen::fn_sub_4B3030_004b3030);
            lw(v1, v0, 8);
            lw(v0, s1, 52);
            s1 = addu(v0, v1);
            backedge(ctx);
        } else {
            // 0x004b3e20
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x004b3e9c
                charge(ctx, 5);
                link(ctx, 0x4B3E9Cu);  // $ra first: the delay slot below depends on it
                lw(a1, s2, 12);
                call(ctx, gen::fn_sub_4B3030_004b3030);
                lw(v0, v0, 8);
                s1 = addu(s1, v0);
                backedge(ctx);
            } else {
                // 0x004b3e28
                charge(ctx, 3);
                v0 = si(-1);
                if (v1 == v0) {
                    // 0x004b3e34
                    charge(ctx, 3);
                    link(ctx, 0x4B3E34u);  // $ra first: the delay slot below depends on it
                    lw(a1, s2, 12);
                    call(ctx, gen::fn_sub_4B3030_004b3030);
                    lw(s1, v0, 8);
                }
            }
        }
    }
    // 0x004b3e40
    charge(ctx, 3);
    sw(s1, s0, 0);
    v0 = s2;
    // 0x004b3f2c
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}


// sub_4B3F50 [rt2dMaestroPushActions] -- copies $a3 16-byte actions into the queue ($a1), resolving jumps (type 12) and targets
// 0 when they do not fit (count + n > capacity), else the queue.
// 0x004B3F50 sub_4B3F50 -- 316 bytes; frame 0x90: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B3F50(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x004b3f50
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    s6 = t0;
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a3;
    sq(s0, sp, 0x0);
    lw(a0, a1, 8);
    lw(v0, a1, 12);
    v1 = addu(a0, s2);
    at = sltu(v0, v1);
    s3 = a2;
    if (at != 0) {
        // 0x004b4024
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004b3f9c
        charge(ctx, 7);
        lw(v0, s4, 0);
        v1 = sll(a0, 4);
        at = slt(0, s2);
        s1 = 0;
        s0 = addu(v0, v1);
        sw(s6, sp, 0x8C);
        if (at != 0) {
            for (;;) {
                // 0x004b3fb8
                charge(ctx, 4);
                lw(v1, s3, 0);
                v0 = 12;
                if (v1 == v0) {
                    // 0x004b402c
                    charge(ctx, 7);
                    a0 = s5;
                    a1 = s3;
                    a2 = s6;
                    a3 = addiu(sp, 0x8C);
                    jal(ctx, 0x4B4038u, gen::fn_sub_4B3DE0_004b3de0);
                    if (v0 == 0) {
                        goto L_004b4048_10;
                    }
                    backedge(ctx);
                L_004b400c:
                    charge(ctx, 4);
                    s1 = addiu(s1, 1);
                    v0 = slt(s1, s2);
                    s3 = addiu(s3, 16);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    continue;
                }
                // 0x004b3fc8
                charge(ctx, 14);
                lwc1(f3, s3, 0);
                lwc1(f2, s3, 4);
                lwc1(f1, s3, 8);
                lwc1(f0, s3, 12);
                swc1(f3, s0, 0);
                swc1(f2, s0, 4);
                swc1(f1, s0, 8);
                swc1(f0, s0, 12);
                lw(v0, s4, 8);
                v0 = addiu(v0, 1);
                sw(v0, s4, 8);
                lw(a1, s0, 4);
                if (i64(a1) >= 0) {
                    // 0x004b4050
                    charge(ctx, 5);
                    a0 = s5;
                    jal(ctx, 0x4B4050u, gen::fn_sub_4B3030_004b3030);
                    lw(v0, v0, 8);
                    sw(v0, s0, 4);
                    backedge(ctx);
                } else {
                    // 0x004b4000
                    charge(ctx, 2);
                    lw(v0, sp, 0x8C);
                    sw(v0, s0, 4);
                }
                // 0x004b4008
                charge(ctx, 1);
                s0 = addiu(s0, 16);
                goto L_004b400c;
            }
        }
        // 0x004b401c
        charge(ctx, 2);
        v0 = s4;
    }
    // 0x004b4064 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
    return;
L_004b4048_10:
    charge(ctx, 2);
    v0 = 0;
    // 0x004b4064 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}


// sub_4B4090 [rt2dQueuePop] -- the next 16-byte entry of a queue, or 0; an exhausted queue is reset
// 0x004B4090 sub_4B4090 -- 92 bytes; leaf frame (no stack)
void sub_4B4090(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x004b4090
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, 8);
    if (v0 == 0) {
        // 0x004b40d0
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004b409c
        charge(ctx, 11);
        lw(v1, a0, 4);
        lw(v0, a0, 0);
        a1 = sll(v1, 4);
        v1 = addiu(v1, 1);
        v0 = addu(v0, a1);
        sw(v1, a0, 4);
        lw(a1, a0, 4);
        lw(v1, a0, 8);
        at = slt(a1, v1);
        if (at == 0) {
            // 0x004b40d8
            charge(ctx, 3);
            sw(zero, a0, 4);
            sw(zero, a0, 8);
            backedge(ctx);
        }
        // 0x004b40c8
        charge(ctx, 2);
    }
    // 0x004b40e4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_4B40F0 [rt2dQueueCreate] -- a queue record (16-byte free list) with an entry array of the configured size; stored at +32
// Returns the owner, or 0 when an allocation fails.
// 0x004B40F0 sub_4B40F0 -- 192 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B40F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b40f0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x30000;
    sd(ra, sp, 0x20);
    a1 = v0 | 0x1A9;
    sq(s1, sp, 0x10);
    v0 = 0x960000;
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, v0, 392);  // 0x960188 (free-list alloc slot)
    a0 = 0x960000;
    a0 = addiu(a0, -1276);  // &0x95FB04 (Rt2d: the 16-byte list-record free list)
    jalr(ctx, 0x4B4118u, v0.u());
    s0 = v0;
    if (v0 == 0) {
        // 0x004b4174
        charge(ctx, 2);
        s0 = 0;
        backedge(ctx);
    } else {
        // 0x004b4128
        charge(ctx, 11);
        v0 = 0x30000;
        lw(v1, gp, -20488);  // 0x7CDCE8
        a1 = v0 | 0x1A9;
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
        a0 = sll(v1, 4);
        jalr(ctx, 0x4B413Cu, v0.u());
        sw(v0, s0, 0);
        lw(v0, s0, 0);
        if (v0 != 0) {
            // 0x004b417c
            charge(ctx, 6);
            sw(zero, s0, 4);
            v1 = s0;
            sw(zero, s0, 8);
            lw(v0, gp, -20488);  // 0x7CDCE8
            sw(v0, s0, 12);
            backedge(ctx);
        } else {
            // 0x004b4154
            charge(ctx, 1);
            v1 = 0;
        }
        // 0x004b4158
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x004b4194
            charge(ctx, 2);
            s0 = 0;
            backedge(ctx);
        }
    }
    // 0x004b4160
    charge(ctx, 2);
    sw(s0, s1, 32);
    if (s0 == 0) {
        // 0x004b4168
        charge(ctx, 1);
        s1 = 0;
    }
    // 0x004b416c
    charge(ctx, 2);
    v0 = s1;
    // 0x004b419c
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_4B41B0 [rt2dQueueDestroy] -- frees the owner's queue (+32): its array and the record; the owner
// 0x004B41B0 sub_4B41B0 -- 116 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B41B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b41b0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 32);
    s1 = a0;
    if (s0 != 0) {
        // 0x004b41cc
        charge(ctx, 5);
        sw(zero, s0, 4);
        sw(zero, s0, 8);
        lw(a0, s0, 0);
        if (a0 != 0) {
            // 0x004b41e0
            charge(ctx, 4);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C (RwFree slot)
            jalr(ctx, 0x4B41E8u, v0.u());
        }
        // 0x004b41f0
        charge(ctx, 6);
        v0 = 0x960000;
        a0 = 0x960000;
        lw(v0, v0, 396);  // 0x96018C (free-list free slot)
        a1 = s0;
        a0 = addiu(a0, -1276);  // &0x95FB04 (Rt2d: the 16-byte list-record free list)
        jalr(ctx, 0x4B4200u, v0.u());
    }
    // 0x004b4208 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    sw(zero, s1, 32);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_4B4720 [rt2dAnimDestroyCB] -- a maestro walk callback: destroys an animation entry's lists and resets it; returns $a0
// 0x004B4720 sub_4B4720 -- 108 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B4720(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b4720
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a0 = addiu(s0, 4);
    a1 = addiu(s0, 32);
    jal(ctx, 0x4B473Cu, gen::fn_sub_4B1240_004b1240);
    sw(zero, s0, 0);
    v0 = si(-1);
    sw(v0, s0, 52);
    sw(v0, s0, 56);
    lw(a0, s0, 48);
    if (a0 != 0) {
        // 0x004b4760
        charge(ctx, 2);
        jal(ctx, 0x4B4760u, gen::fn_sub_4B6190_004b6190);
    }
    // 0x004b4768
    charge(ctx, 9);
    a0 = addiu(s0, 32);
    jal(ctx, 0x4B4768u, gen::fn_sub_4B2B40_004b2b40);
    sw(zero, s0, 48);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_4B4810 [rt2dMaestroAnimsDestroy] -- destroys every animation of the maestro (sub_4B4BA0 with sub_4B4720) and their sList
// 0x004B4810 sub_4B4810 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4B4810(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b4810
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, 8);
    s0 = a0;
    if (v0 != 0) {
        // 0x004b4830
        charge(ctx, 8);
        a1 = 0x4B0000;
        a2 = 0;
        a1 = addiu(a1, 18208);  // &sub_4B4720
        jal(ctx, 0x4B4838u, gen::fn_sub_4B4BA0_004b4ba0);
        link(ctx, 0x4B4840u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 8);
        call(ctx, gen::fn_sub_4C20B0_004c20b0);
        sw(zero, s0, 8);
        backedge(ctx);
    }
    // 0x004b4828
    charge(ctx, 2);
    v0 = s0;
    // 0x004b4850
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4B4A60 [rt2dMaestroGetAnim] -- the animation entry $a1 (sub_4C21B0 on +8)
// 0x004B4A60 sub_4B4A60 -- 8 bytes; leaf frame (no stack)
void sub_4B4A60(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4};
    // 0x004b4a60
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(a0, a0, 8);
    gen::fn_sub_4C21B0_004c21b0(ctx);  // tail call
}


// sub_4B4A70 [rt2dMaestroForAllVisibleAnims] -- calls $a1 on each 60-byte animation whose scene is visible (marking bit 2)
// The current index at +68 during the walk (-1 after); 0 when a callback does not return the maestro.
// 0x004B4A70 sub_4B4A70 -- 304 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B4A70(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004b4a70
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    s6 = a2;
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, a0, 8);
    s4 = a1;
    jal(ctx, 0x4B4AA0u, gen::fn_sub_4C2120_004c2120);
    s0 = v0;
    if (i64(s0) > 0) {
        // 0x004b4ac4
        charge(ctx, 6);
        link(ctx, 0x4B4AC4u);  // $ra first: the delay slot below depends on it
        lw(a0, s5, 8);
        call(ctx, gen::fn_sub_4C2090_004c2090);
        at = slt(0, s0);
        s3 = v0;
        s2 = 0;
        if (at == 0) {
            backedge(ctx);
            goto L_004b4ab4;
        }
        for (;;) {
            // 0x004b4adc
            charge(ctx, 4);
            lw(a1, s3, 52);
            v0 = si(-1);
            s1 = 1;
            if (a1 != v0) {
                // 0x004b4b20
                charge(ctx, 6);
                link(ctx, 0x4B4B20u);  // $ra first: the delay slot below depends on it
                lw(a0, s5, 8);
                call(ctx, gen::fn_sub_4C21B0_004c21b0);
                lw(v0, v0, 0);
                v0 = v0 | 0x4;
                if (v0 != 0) {
                    backedge(ctx);
                } else {
                    // 0x004b4b38
                    charge(ctx, 2);
                    s1 = 0;
                    backedge(ctx);
                }
            } else {
                // 0x004b4aec
                charge(ctx, 1);
            }
            // 0x004b4af0
            charge(ctx, 2);
            sw(s2, s5, 68);
            if (s1 != 0) {
                // 0x004b4b40
                charge(ctx, 4);
                link(ctx, 0x4B4B40u);  // $ra first: the delay slot below depends on it
                lw(a0, s3, 32);
                call(ctx, gen::fn_sub_4AE010_004ae010);
                if (v0 == 0) {
                    backedge(ctx);
                    goto L_004b4af8;
                }
                // 0x004b4b50
                charge(ctx, 9);
                lw(v0, s3, 0);
                a0 = s5;
                a1 = s3;
                a2 = s6;
                v0 = v0 | 0x4;
                jt = s4.u();  // the target, read before the delay slot
                link(ctx, 0x4B4B64u);  // $ra = the return address
                sw(v0, s3, 0);
                call_ptr(ctx, jt);
                if (v0 != s5) {
                    break;
                }
                backedge(ctx);
            L_004b4b08:
                charge(ctx, 4);
                s2 = addiu(s2, 1);
                v0 = slt(s2, s0);
                s3 = addiu(s3, 60);
                if (v0 == 0) {
                    goto L_004b4b18_9;
                }
                backedge(ctx);
                continue;
            }
        L_004b4af8:
            charge(ctx, 4);
            lw(v1, s3, 0);
            v0 = si(-5);
            v0 = v1 & v0;
            sw(v0, s3, 0);
            goto L_004b4b08;
        }
        // 0x004b4b74
        charge(ctx, 1);
        v0 = 0;
        // 0x004b4b78 (the shared epilogue, written out on this path)
        charge(ctx, 10);
        ld(ra, sp, 0x70);
        lq(s6, sp, 0x60);
        lq(s5, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x80);
        return;
    }
L_004b4ab4:
    charge(ctx, 1);
    v1 = si(-1);
L_004b4ab8:
    charge(ctx, 3);
    v0 = s5;
    sw(v1, s5, 68);
    // 0x004b4b78 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
    return;
L_004b4b18_9:
    charge(ctx, 2);
    v1 = si(-1);
    backedge(ctx);
    goto L_004b4ab8;
}


// sub_4B4BA0 [rt2dMaestroForAllAnims] -- calls $a1(maestro, anim, $a2) on each 60-byte animation; 0 when one does not return the maestro
// The current index at +68 during the walk (-1 after).
// 0x004B4BA0 sub_4B4BA0 -- 200 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B4BA0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004b4ba0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, a0, 8);
    s3 = a2;
    jal(ctx, 0x4B4BCCu, gen::fn_sub_4C2120_004c2120);
    s0 = v0;
    if (i64(s0) > 0) {
        // 0x004b4bf0
        charge(ctx, 6);
        link(ctx, 0x4B4BF0u);  // $ra first: the delay slot below depends on it
        lw(a0, s5, 8);
        call(ctx, gen::fn_sub_4C2090_004c2090);
        at = slt(0, s0);
        s2 = v0;
        s1 = 0;
        if (at == 0) {
            backedge(ctx);
            goto L_004b4be0;
        }
        for (;;) {
            // 0x004b4c08
            charge(ctx, 7);
            a0 = s5;
            a1 = s2;
            a2 = s3;
            jt = s4.u();  // the target, read before the delay slot
            link(ctx, 0x4B4C14u);  // $ra = the return address
            sw(s1, s5, 68);
            call_ptr(ctx, jt);
            if (v0 != s5) {
                goto L_004b4c24_5;
            }
            // 0x004b4c2c
            charge(ctx, 4);
            s1 = addiu(s1, 1);
            v0 = slt(s1, s0);
            s2 = addiu(s2, 60);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004b4c3c
        charge(ctx, 2);
        v1 = si(-1);
        backedge(ctx);
    L_004b4be4:
        charge(ctx, 3);
        v0 = s5;
        sw(v1, s5, 68);
        // 0x004b4c44 (the shared epilogue, written out on this path)
        charge(ctx, 9);
        ld(ra, sp, 0x60);
        lq(s5, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x70);
        return;
    }
L_004b4be0:
    charge(ctx, 1);
    v1 = si(-1);
    goto L_004b4be4;
L_004b4c24_5:
    charge(ctx, 2);
    v0 = 0;
    // 0x004b4c44 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}


// sub_4B59B0 [rt2dMaestroTriggerButton] -- a button message: finds the button in the animation's props and queues its transition
// The state's action index from the transition table (sub_4B34D0); the target frame's actions queued (sub_4B39F0)
// with the animation index swapped in at +68. Returns the message, or 0 for a negative button.
// 0x004B59B0 sub_4B59B0 -- 416 bytes; frame 0xB0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B59B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004b59b0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    s6 = a1;
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a1, a1, 4);
    s5 = a0;
    jal(ctx, 0x4B59E4u, gen::fn_sub_4B4A60_004b4a60);
    lw(s1, s6, 8);
    s2 = v0;
    if (i64(s1) >= 0) {
        // 0x004b5a00
        charge(ctx, 14);
        a0 = addiu(s2, 4);
        jal(ctx, 0x4B5A00u, gen::fn_sub_4B1A80_004b1a80);
        lw(a0, s2, 48);
        s3 = v0;
        a1 = s3;
        jal(ctx, 0x4B5A10u, gen::fn_sub_4B6000_004b6000);
        lw(a0, v0, 8);
        fp = v0;
        s7 = si(-1);
        jal(ctx, 0x4B5A20u, gen::fn_sub_4C2120_004c2120);
        s0 = v0;
        v0 = slt(0, s0);
        s4 = 0;
        if (v0 != 0) {
            for (;;) {
                // 0x004b5a48
                charge(ctx, 9);
                lw(a1, s2, 48);
                a0 = s5;
                a2 = s3;
                a3 = s4;
                t0 = addiu(sp, 0xAC);
                jal(ctx, 0x4B5A58u, gen::fn_sub_4B62A0_004b62a0);
                lw(v0, sp, 0xAC);
                if (v0 == s1) {
                    goto L_004b5a6c_6;
                }
                // 0x004b5a74
                charge(ctx, 4);
                s4 = addiu(s4, 1);
                v0 = slt(s4, s0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004b5a84
            charge(ctx, 2);
            backedge(ctx);
        }
    L_004b5a38:
        charge(ctx, 2);
        if (i64(s7) >= 0) {
            // 0x004b5a8c
            charge(ctx, 11);
            lw(a0, fp, 0x8);
            a1 = s7;
            jal(ctx, 0x4B5A90u, gen::fn_sub_4C21B0_004c21b0);
            lw(a1, v0, 0);
            lw(s0, s6, 12);
            a0 = s5;
            jal(ctx, 0x4B5AA0u, gen::fn_sub_4B34D0_004b34d0);
            lw(a0, v0, 8);
            v1 = a0 & s0;
            if (v1 == 0) {
                backedge(ctx);
            } else {
                // 0x004b5ab8
                charge(ctx, 3);
                a0 = srl(a0, 4);
                a1 = si(-1);
                if (s0 != 0) {
                    for (;;) {
                        // 0x004b5ac4
                        charge(ctx, 3);
                        v1 = a0 & 0x1;
                        if (v1 != 0) {
                            // 0x004b5ad0
                            charge(ctx, 2);
                            a1 = addiu(a1, 1);
                        }
                        // 0x004b5ad8
                        charge(ctx, 4);
                        s0 = srl(s0, 1);
                        a0 = srl(a0, 1);
                        if (s0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x004b5ae8
                charge(ctx, 6);
                v1 = sll(a1, 2);
                v0 = addu(v1, v0);
                v1 = addiu(v0, 16);
                lw(v0, v0, 16);
                if (i64(v0) < 0) {
                    backedge(ctx);
                } else {
                    // 0x004b5b00
                    charge(ctx, 8);
                    lw(s0, s5, 68);
                    lw(v0, s6, 4);
                    sw(v0, s5, 68);
                    lw(a1, v1, 0);
                    a0 = s5;
                    jal(ctx, 0x4B5B10u, gen::fn_sub_4B39F0_004b39f0);
                    sw(s0, s5, 68);
                    backedge(ctx);
                }
            }
        }
        // 0x004b5a40
        charge(ctx, 2);
        v0 = s6;
    } else {
        // 0x004b59f8
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004b5b20 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xB0);
    return;
L_004b5a6c_6:
    charge(ctx, 2);
    s7 = s4;
    backedge(ctx);
    goto L_004b5a38;
}


// sub_4B6000 [rt2dPropsGet] -- the 16-byte prop record $a1 of a props set, or 0 without an sList
// 0x004B6000 sub_4B6000 -- 64 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4B6000(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b6000
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, a0, 0);
    s0 = a1;
    if (a0 == 0) {
        // 0x004b602c
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004b6018
        charge(ctx, 5);
        jal(ctx, 0x4B6018u, gen::fn_sub_4C2090_004c2090);
        v1 = sll(s0, 4);
        v0 = addu(v0, v1);
    }
    // 0x004b6030 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4B6190 [rt2dPropsDestroy] -- destroys a props set: each record's sList, the array, then the record (8-byte free list); 1
// 0x004B6190 sub_4B6190 -- 224 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B6190(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b6190
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, a0, 0);
    if (a0 != 0) {
        // 0x004b61b8
        charge(ctx, 7);
        jal(ctx, 0x4B61B8u, gen::fn_sub_4C2120_004c2120);
        lw(a0, s3, 0);
        s0 = v0;
        jal(ctx, 0x4B61C4u, gen::fn_sub_4C2090_004c2090);
        s1 = v0;
        if (i64(s0) > 0) {
            // 0x004b61d4
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x004b61dc
                charge(ctx, 3);
                at = slt(0, s0);
                s2 = 0;
                if (at != 0) {
                    for (;;) {
                        // 0x004b61e8
                        charge(ctx, 3);
                        lw(a0, s1, 8);
                        if (a0 != 0) {
                            // 0x004b61f4
                            charge(ctx, 3);
                            jal(ctx, 0x4B61F4u, gen::fn_sub_4C20B0_004c20b0);
                        }
                        // 0x004b6200
                        charge(ctx, 9);
                        sw(zero, s1, 8);
                        v1 = si(-1);
                        s2 = addiu(s2, 1);
                        sw(v1, s1, 0);
                        v0 = slt(s2, s0);
                        sw(v1, s1, 4);
                        sw(v1, s1, 12);
                        s1 = addiu(s1, 16);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004b6224
                    charge(ctx, 1);
                }
            }
        }
        // 0x004b6228
        charge(ctx, 3);
        link(ctx, 0x4B6228u);  // $ra first: the delay slot below depends on it
        lw(a0, s3, 0);
        call(ctx, gen::fn_sub_4C20B0_004c20b0);
        sw(zero, s3, 0);
    }
    // 0x004b6234
    charge(ctx, 15);
    sw(zero, s3, 4);
    v0 = 0x960000;
    lw(v0, v0, 396);  // 0x96018C (free-list free slot)
    a0 = 0x960000;
    a1 = s3;
    a0 = addiu(a0, -1132);  // &0x95FB94 (Rt2d: the 8-byte list-record free list)
    jalr(ctx, 0x4B6248u, v0.u());
    ld(ra, sp, 0x40);
    v0 = 1;
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}


// sub_4B6270 [rt2dClearFlag0] -- clears bit 0 of +4; the record
// 0x004B6270 sub_4B6270 -- 48 bytes; leaf frame (no stack)
void sub_4B6270(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x004b6270
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, 4);
    v0 = v1 & 0x1;
    if (v0 != 0) {
        // 0x004b6288
        charge(ctx, 4);
        v0 = si(-2);
        v0 = v1 & v0;
        sw(v0, a0, 4);
        backedge(ctx);
    }
    // 0x004b6280
    charge(ctx, 2);
    v0 = a0;
    // 0x004b6298
    charge(ctx, 2);
}


// sub_4B62A0 [rt2dPropsLookup] -- prop $a3 of record $a2 in props $a1, through the label table (+16): its value to *$t0
// Returns the props, or 0 when an entry is missing.
// 0x004B62A0 sub_4B62A0 -- 164 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B62A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b62a0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    s1 = a3;
    lw(a0, a1, 0);
    s0 = t0;
    a1 = a2;
    jal(ctx, 0x4B62CCu, gen::fn_sub_4C21B0_004c21b0);
    if (v0 == 0) {
        // 0x004b6314
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004b62dc
        charge(ctx, 5);
        lw(a0, v0, 8);
        a1 = s1;
        jal(ctx, 0x4B62E0u, gen::fn_sub_4C21B0_004c21b0);
        if (v0 == 0) {
            // 0x004b631c
            charge(ctx, 2);
            v0 = 0;
        } else {
            // 0x004b62f0
            charge(ctx, 5);
            lw(a1, v0, 0);
            link(ctx, 0x4B62F4u);  // $ra first: the delay slot below depends on it
            lw(a0, s3, 16);
            call(ctx, gen::fn_sub_4C21B0_004c21b0);
            if (v0 == 0) {
                // 0x004b6324
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x004b6304
                charge(ctx, 4);
                lw(v0, v0, 0);
                sw(v0, s0, 0);
                v0 = s2;
            }
        }
    }
    // 0x004b6328 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}


// sub_4B6350 [rt2dAnimOpen] -- creates the animation / maestro free lists (11 static free lists) and sets the open flag
// 0x004B6350 sub_4B6350 -- 424 bytes; frame 0x10: ra sp+0x0
void sub_4B6350(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b6350
    enter(ctx, 106);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t0 = 0x960000;
    sd(ra, sp, 0x0);
    v0 = 0x40000;
    lw(a1, gp, -20484);  // 0x7CDCEC
    a0 = 28;
    lw(a3, gp, -20480);  // 0x7CDCF0
    a2 = 4;
    t0 = addiu(t0, -1456);  // &0x95FA50
    t1 = v0 | 0x1A9;
    jal(ctx, 0x4B6374u, gen::fn_sub_4C3B60_004c3b60);
    lw(a1, gp, -20484);  // 0x7CDCEC
    t0 = 0x960000;
    lw(a3, gp, -20480);  // 0x7CDCF0
    v0 = 0x40000;
    a0 = 144;
    a2 = 4;
    t0 = addiu(t0, -1420);  // &0x95FA74
    t1 = v0 | 0x1A9;
    jal(ctx, 0x4B6398u, gen::fn_sub_4C3B60_004c3b60);
    lw(a1, gp, -20484);  // 0x7CDCEC
    t0 = 0x960000;
    lw(a3, gp, -20480);  // 0x7CDCF0
    v0 = 0x40000;
    a0 = 344;
    a2 = 4;
    t0 = addiu(t0, -1384);  // &0x95FA98
    t1 = v0 | 0x1B1;
    jal(ctx, 0x4B63BCu, gen::fn_sub_4C3B60_004c3b60);
    lw(a1, gp, -20484);  // 0x7CDCEC
    t0 = 0x960000;
    lw(a3, gp, -20480);  // 0x7CDCF0
    v0 = 0x40000;
    a0 = 16;
    a2 = 4;
    t0 = addiu(t0, -1348);  // &0x95FABC
    t1 = v0 | 0x1A9;
    jal(ctx, 0x4B63E0u, gen::fn_sub_4C3B60_004c3b60);
    lw(a1, gp, -20484);  // 0x7CDCEC
    t0 = 0x960000;
    lw(a3, gp, -20480);  // 0x7CDCF0
    v0 = 0x40000;
    a0 = 16;
    a2 = 4;
    t0 = addiu(t0, -1312);  // &0x95FAE0
    t1 = v0 | 0x1A9;
    jal(ctx, 0x4B6404u, gen::fn_sub_4C3B60_004c3b60);
    lw(a1, gp, -20484);  // 0x7CDCEC
    t0 = 0x960000;
    lw(a3, gp, -20480);  // 0x7CDCF0
    v0 = 0x40000;
    a0 = 16;
    a2 = 4;
    t0 = addiu(t0, -1276);  // &0x95FB04 (Rt2d: the 16-byte list-record free list)
    t1 = v0 | 0x1A9;
    jal(ctx, 0x4B6428u, gen::fn_sub_4C3B60_004c3b60);
    lw(a1, gp, -20484);  // 0x7CDCEC
    t0 = 0x960000;
    lw(a3, gp, -20480);  // 0x7CDCF0
    v0 = 0x40000;
    a0 = 160;
    a2 = 4;
    t0 = addiu(t0, -1240);  // &0x95FB28
    t1 = v0 | 0x1A9;
    jal(ctx, 0x4B644Cu, gen::fn_sub_4C3B60_004c3b60);
    lw(a1, gp, -20484);  // 0x7CDCEC
    t0 = 0x960000;
    lw(a3, gp, -20480);  // 0x7CDCF0
    v0 = 0x40000;
    a0 = 12;
    a2 = 4;
    t0 = addiu(t0, -1204);  // &0x95FB4C (Rt2d: the 12-byte list-record free list)
    t1 = v0 | 0x1B0;
    jal(ctx, 0x4B6470u, gen::fn_sub_4C3B60_004c3b60);
    lw(a1, gp, -20484);  // 0x7CDCEC
    t0 = 0x960000;
    lw(a3, gp, -20480);  // 0x7CDCF0
    v0 = 0x40000;
    a0 = 16;
    a2 = 4;
    t0 = addiu(t0, -1168);  // &0x95FB70
    t1 = v0 | 0x1A9;
    jal(ctx, 0x4B6494u, gen::fn_sub_4C3B60_004c3b60);
    lw(a1, gp, -20484);  // 0x7CDCEC
    t0 = 0x960000;
    lw(a3, gp, -20480);  // 0x7CDCF0
    v0 = 0x40000;
    a0 = 8;
    a2 = 4;
    t0 = addiu(t0, -1132);  // &0x95FB94 (Rt2d: the 8-byte list-record free list)
    t1 = v0 | 0x1A9;
    jal(ctx, 0x4B64B8u, gen::fn_sub_4C3B60_004c3b60);
    lw(a1, gp, -20484);  // 0x7CDCEC
    t0 = 0x960000;
    lw(a3, gp, -20480);  // 0x7CDCF0
    v0 = 0x40000;
    a0 = 16;
    a2 = 4;
    t0 = addiu(t0, -1096);  // &0x95FBB8
    t1 = v0 | 0x1A9;
    jal(ctx, 0x4B64DCu, gen::fn_sub_4C3B60_004c3b60);
    v1 = 1;
    sw(v1, gp, -17496);  // 0x7CE898
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}


// sub_4B6500 [rt2dAnimClose] -- destroys the animation / maestro free lists
// 0x004B6500 sub_4B6500 -- 152 bytes; frame 0x10: ra sp+0x0
void sub_4B6500(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b6500
    enter(ctx, 38);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 0x960000;
    sd(ra, sp, 0x0);
    a0 = addiu(a0, -1456);  // &0x95FA50
    jal(ctx, 0x4B650Cu, gen::fn_sub_4C3C30_004c3c30);
    a0 = 0x960000;
    a0 = addiu(a0, -1420);  // &0x95FA74
    jal(ctx, 0x4B6518u, gen::fn_sub_4C3C30_004c3c30);
    a0 = 0x960000;
    a0 = addiu(a0, -1384);  // &0x95FA98
    jal(ctx, 0x4B6524u, gen::fn_sub_4C3C30_004c3c30);
    a0 = 0x960000;
    a0 = addiu(a0, -1348);  // &0x95FABC
    jal(ctx, 0x4B6530u, gen::fn_sub_4C3C30_004c3c30);
    a0 = 0x960000;
    a0 = addiu(a0, -1312);  // &0x95FAE0
    jal(ctx, 0x4B653Cu, gen::fn_sub_4C3C30_004c3c30);
    a0 = 0x960000;
    a0 = addiu(a0, -1276);  // &0x95FB04 (Rt2d: the 16-byte list-record free list)
    jal(ctx, 0x4B6548u, gen::fn_sub_4C3C30_004c3c30);
    a0 = 0x960000;
    a0 = addiu(a0, -1240);  // &0x95FB28
    jal(ctx, 0x4B6554u, gen::fn_sub_4C3C30_004c3c30);
    a0 = 0x960000;
    a0 = addiu(a0, -1204);  // &0x95FB4C (Rt2d: the 12-byte list-record free list)
    jal(ctx, 0x4B6560u, gen::fn_sub_4C3C30_004c3c30);
    a0 = 0x960000;
    a0 = addiu(a0, -1168);  // &0x95FB70
    jal(ctx, 0x4B656Cu, gen::fn_sub_4C3C30_004c3c30);
    a0 = 0x960000;
    a0 = addiu(a0, -1132);  // &0x95FB94 (Rt2d: the 8-byte list-record free list)
    jal(ctx, 0x4B6578u, gen::fn_sub_4C3C30_004c3c30);
    a0 = 0x960000;
    a0 = addiu(a0, -1096);  // &0x95FBB8
    jal(ctx, 0x4B6584u, gen::fn_sub_4C3C30_004c3c30);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}


// sub_4BAE00 [sphereTriangleTest] -- sphere / triangle: 1 when any point of the triangle lies within the sphere; the normal and distance
// ($a0 = the sphere {centre, radius}, $a1..$a3 = the vertices, $t0 = the unit normal out, $t1 = the distance out)
// Three quick rejects (all vertices beyond the radius on one side of an axis); the face normal (normalised; a
// degenerate triangle: 0); the plane distance must lie within [-r, r] (stored, negated); then 1 when a vertex lies
// within the radius, else the closest edge / the edge projections decide (0 when the centre's projection falls
// outside every edge band). The R5900 ACC (mula / madda / msub) arithmetic of the original is kept as is.
// 0x004BAE00 sub_4BAE00 -- 1988 bytes; frame 0x80
void sub_4BAE00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, t8{ctx, 24}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16};
    // 0x004bae00
    enter(ctx, 46);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    lwc1(f3, a1, 0);
    t5 = addiu(sp, 0x2C);
    lwc1(f7, a0, 0);
    t4 = addiu(sp, 0x30);
    lwc1(f0, a2, 0);
    v1 = addiu(sp, 0xC);
    lwc1(f2, a1, 4);
    t3 = addiu(sp, 0x1C);
    lwc1(f6, a0, 4);
    t2 = addiu(sp, 0x20);
    lwc1(f4, a2, 4);
    v0 = addiu(sp, 0x10);
    lwc1(f1, a1, 8);
    sub_s(f3, f3, f7);
    swc1(f3, sp, 0x28);
    lwc1(f5, a0, 8);
    lw(t6, sp, 0x28);
    sub_s(f2, f2, f6);
    sub_s(f0, f0, f7);
    t7 = sra(t6, 31);
    swc1(f0, sp, 0x18);
    swc1(f2, t5, 0);
    lw(t6, sp, 0x18);
    sub_s(f1, f1, f5);
    lwc1(f2, a3, 0);
    swc1(f1, t4, 0);
    t6 = sra(t6, 31);
    lwc1(f1, a3, 4);
    t7 = addu(t7, t6);
    lwc1(f0, a3, 8);
    sub_s(f4, f4, f6);
    sub_s(f2, f2, f7);
    sub_s(f1, f1, f6);
    swc1(f2, sp, 0x8);
    lw(t6, sp, 0x8);
    sub_s(f0, f0, f5);
    lwc1(f3, a2, 8);
    swc1(f1, v1, 0);
    t6 = sra(t6, 31);
    t7 = addu(t6, t7);
    swc1(f4, t3, 0);
    swc1(f0, v0, 0);
    sub_s(f1, f3, f5);
    swc1(f1, t2, 0);
    if (t7 == 0) {
        // 0x004bb4ac
        charge(ctx, 17);
        lwc1(f3, a0, 12);
        lwc1(f2, sp, 0x28);
        lwc1(f1, sp, 0x18);
        lwc1(f0, sp, 0x8);
        sub_s(f2, f2, f3);
        sub_s(f1, f1, f3);
        sub_s(f0, f0, f3);
        swc1(f2, sp, 0x7C);
        swc1(f1, sp, 0x78);
        lw(t8, sp, 0x7C);
        lw(t7, sp, 0x78);
        swc1(f0, sp, 0x74);
        lw(t6, sp, 0x74);
        t7 = t8 | t7;
        t6 = t6 | t7;
        if (i64(t6) < 0) {
            backedge(ctx);
        L_004baf10:
            charge(ctx, 10);
            lw(t8, t5, 0);
            lw(t7, t3, 0);
            lw(t6, v1, 0);
            t8 = sra(t8, 31);
            t7 = sra(t7, 31);
            t7 = addu(t8, t7);
            t6 = sra(t6, 31);
            t7 = addu(t6, t7);
            if (t7 == 0) {
                // 0x004bb4f8
                charge(ctx, 17);
                lwc1(f2, t5, 0);
                lwc1(f3, a0, 12);
                lwc1(f1, t3, 0);
                lwc1(f0, v1, 0);
                sub_s(f2, f2, f3);
                sub_s(f1, f1, f3);
                sub_s(f0, f0, f3);
                swc1(f2, sp, 0x64);
                swc1(f1, sp, 0x60);
                lw(t8, sp, 0x64);
                lw(t7, sp, 0x60);
                swc1(f0, sp, 0x5C);
                lw(t6, sp, 0x5C);
                t7 = t8 | t7;
                t6 = t6 | t7;
                if (i64(t6) < 0) {
                    backedge(ctx);
                L_004baf90:
                    charge(ctx, 10);
                    lw(t8, t4, 0);
                    lw(t7, t2, 0);
                    lw(t6, v0, 0);
                    t8 = sra(t8, 31);
                    t7 = sra(t7, 31);
                    t7 = addu(t8, t7);
                    t6 = sra(t6, 31);
                    t7 = addu(t6, t7);
                    if (t7 == 0) {
                        // 0x004bb544
                        charge(ctx, 17);
                        lwc1(f2, t4, 0);
                        lwc1(f3, a0, 12);
                        lwc1(f1, t2, 0);
                        lwc1(f0, v0, 0);
                        sub_s(f2, f2, f3);
                        sub_s(f1, f1, f3);
                        sub_s(f0, f0, f3);
                        swc1(f2, sp, 0x4C);
                        swc1(f1, sp, 0x48);
                        lw(t8, sp, 0x4C);
                        lw(t7, sp, 0x48);
                        swc1(f0, sp, 0x44);
                        lw(t6, sp, 0x44);
                        t7 = t8 | t7;
                        t6 = t6 | t7;
                        if (i64(t6) < 0) {
                            backedge(ctx);
                        L_004bb010:
                            charge(ctx, 35);
                            lwc1(f4, a1, 0);
                            lwc1(f3, a2, 0);
                            lwc1(f6, a1, 8);
                            lwc1(f1, a2, 8);
                            lwc1(f0, a3, 0);
                            lwc1(f8, a1, 4);
                            lwc1(f2, a2, 4);
                            sub_s(f9, f3, f4);
                            sub_s(f5, f1, f6);
                            sub_s(f4, f0, f4);
                            lwc1(f1, a3, 4);
                            sub_s(f7, f2, f8);
                            lwc1(f0, a3, 8);
                            sub_s(f2, f1, f8);
                            mtc1(zero, f3);
                            sub_s(f1, f0, f6);
                            mula_s(f7, f1);
                            msub_s(f0, f5, f2);
                            mula_s(f5, f4);
                            msub_s(f1, f9, f1);
                            swc1(f0, t0, 0);
                            mula_s(f9, f2);
                            msub_s(f0, f7, f4);
                            swc1(f1, t0, 4);
                            swc1(f0, t0, 8);
                            lwc1(f1, t0, 4);
                            lwc1(f0, t0, 0);
                            lwc1(f2, t0, 8);
                            mul_s(f1, f1, f1);
                            mul_s(f0, f0, f0);
                            adda_s(f0, f1);
                            madd_s(f0, f2, f2);
                            c_le_s(f0, f3);
                            if (cond(ctx)) {
                                // 0x004bb590
                                charge(ctx, 2);
                                v0 = 0;
                            } else {
                                // 0x004bb09c
                                charge(ctx, 8);
                                sqrt_s(f4, f0);
                                c_le_s(f4, f3);
                                if (!cond(ctx)) {
                                    // 0x004bb0bc
                                    charge(ctx, 7);
                                    a1 = 0x3F800000;
                                    mtc1(a1, f0);
                                    div_s(f4, f0, f4);
                                }
                                // 0x004bb0d8
                                charge(ctx, 23);
                                lwc1(f3, t0, 0);
                                lwc1(f2, a0, 12);
                                lwc1(f6, t5, 0);
                                lwc1(f9, sp, 0x28);
                                lwc1(f5, t4, 0);
                                mtc1(zero, f0);
                                mul_s(f3, f3, f4);
                                swc1(f3, t0, 0);
                                lwc1(f3, t0, 4);
                                neg_s(f1, f2);
                                mul_s(f3, f3, f4);
                                swc1(f3, t0, 4);
                                lwc1(f3, t0, 8);
                                mul_s(f7, f3, f4);
                                swc1(f7, t0, 8);
                                lwc1(f3, t0, 4);
                                lwc1(f4, t0, 0);
                                mula_s(f6, f3);
                                madda_s(f9, f4);
                                madd_s(f3, f5, f7);
                                c_lt_s(f3, f1);
                                if (!cond(ctx)) {
                                    // 0x004bb134
                                    charge(ctx, 3);
                                    c_le_s(f3, f2);
                                    if (!cond(ctx)) {
                                        goto L_004bb598;
                                    }
                                    // 0x004bb140
                                    charge(ctx, 11);
                                    neg_s(f1, f3);
                                    swc1(f1, t1, 0);
                                    mul_s(f1, f6, f6);
                                    adda_s(f0, f1);
                                    madd_s(f1, f9, f9);
                                    adda_s(f0, f1);
                                    mul_s(f10, f2, f2);
                                    madd_s(f14, f5, f5);
                                    c_le_s(f14, f10);
                                    if (cond(ctx)) {
                                        // 0x004bb5a0
                                        charge(ctx, 2);
                                        v0 = 1;
                                    } else {
                                        // 0x004bb16c
                                        charge(ctx, 11);
                                        lwc1(f4, t3, 0);
                                        lwc1(f8, sp, 0x18);
                                        lwc1(f3, t2, 0);
                                        mul_s(f1, f4, f4);
                                        adda_s(f0, f1);
                                        madd_s(f1, f8, f8);
                                        adda_s(f0, f1);
                                        madd_s(f13, f3, f3);
                                        c_le_s(f13, f10);
                                        if (cond(ctx)) {
                                            // 0x004bb5a8
                                            charge(ctx, 2);
                                            v0 = 1;
                                        } else {
                                            // 0x004bb198
                                            charge(ctx, 11);
                                            lwc1(f2, v1, 0);
                                            lwc1(f7, sp, 0x8);
                                            lwc1(f1, v0, 0);
                                            mul_s(f11, f2, f2);
                                            adda_s(f0, f11);
                                            madd_s(f11, f7, f7);
                                            adda_s(f0, f11);
                                            madd_s(f12, f1, f1);
                                            c_le_s(f12, f10);
                                            if (cond(ctx)) {
                                                // 0x004bb5b0
                                                charge(ctx, 2);
                                                v0 = 1;
                                            } else {
                                                // 0x004bb1c4
                                                charge(ctx, 3);
                                                c_lt_s(f14, f13);
                                                if (!cond(ctx)) {
                                                    // 0x004bb26c
                                                    charge(ctx, 3);
                                                    c_lt_s(f12, f13);
                                                    if (!cond(ctx)) {
                                                        // 0x004bb2c0
                                                        charge(ctx, 8);
                                                        mul_s(f11, f4, f6);
                                                        adda_s(f0, f11);
                                                        madd_s(f11, f8, f9);
                                                        adda_s(f0, f11);
                                                        madd_s(f11, f3, f5);
                                                        c_le_s(f11, f13);
                                                        if (cond(ctx)) {
                                                        L_004bb308:
                                                            charge(ctx, 25);
                                                            lwc1(f16, sp, 0x28);
                                                            sub_s(f15, f4, f6);
                                                            sub_s(f12, f3, f5);
                                                            sub_s(f13, f8, f16);
                                                            mula_s(f15, f6);
                                                            madda_s(f13, f16);
                                                            madd_s(f11, f12, f5);
                                                            mula_s(f15, f15);
                                                            madda_s(f13, f13);
                                                            madd_s(f0, f12, f12);
                                                            div_s(f11, f11, f0);
                                                            mtc1(zero, f14);
                                                            adda_s(f14, f16);
                                                            msub_s(f13, f13, f11);
                                                            adda_s(f14, f6);
                                                            msub_s(f0, f15, f11);
                                                            adda_s(f14, f5);
                                                            msub_s(f12, f12, f11);
                                                            mula_s(f0, f0);
                                                            madda_s(f13, f13);
                                                            madd_s(f11, f12, f12);
                                                            c_le_s(f11, f10);
                                                            if (!cond(ctx)) {
                                                                // 0x004bb36c
                                                                charge(ctx, 8);
                                                                mul_s(f0, f0, f2);
                                                                adda_s(f14, f0);
                                                                madd_s(f0, f13, f7);
                                                                adda_s(f14, f0);
                                                                madd_s(f0, f12, f1);
                                                                c_lt_s(f11, f0);
                                                                if (!cond(ctx)) {
                                                                    goto L_004bb394;
                                                                }
                                                                // 0x004bb38c
                                                                charge(ctx, 2);
                                                                v0 = 0;
                                                                // 0x004bb5bc (the shared epilogue, written out on this path)
                                                                charge(ctx, 2);
                                                                sp = addiu(sp, 0x80);
                                                                return;
                                                            }
                                                        L_004bb394:
                                                            charge(ctx, 25);
                                                            lwc1(f15, sp, 0x18);
                                                            sub_s(f14, f2, f4);
                                                            sub_s(f11, f1, f3);
                                                            sub_s(f12, f7, f15);
                                                            mula_s(f14, f4);
                                                            madda_s(f12, f15);
                                                            madd_s(f7, f11, f3);
                                                            mula_s(f14, f14);
                                                            madda_s(f12, f12);
                                                            madd_s(f0, f11, f11);
                                                            div_s(f7, f7, f0);
                                                            mtc1(zero, f13);
                                                            adda_s(f13, f15);
                                                            msub_s(f12, f12, f7);
                                                            adda_s(f13, f4);
                                                            msub_s(f0, f14, f7);
                                                            adda_s(f13, f3);
                                                            msub_s(f11, f11, f7);
                                                            mula_s(f0, f0);
                                                            madda_s(f12, f12);
                                                            madd_s(f7, f11, f11);
                                                            c_le_s(f7, f10);
                                                            if (!cond(ctx)) {
                                                                // 0x004bb3f8
                                                                charge(ctx, 8);
                                                                mul_s(f0, f0, f6);
                                                                adda_s(f13, f0);
                                                                madd_s(f0, f12, f9);
                                                                adda_s(f13, f0);
                                                                madd_s(f0, f11, f5);
                                                                c_lt_s(f7, f0);
                                                                if (!cond(ctx)) {
                                                                    goto L_004bb420;
                                                                }
                                                                // 0x004bb418
                                                                charge(ctx, 2);
                                                                v0 = 0;
                                                                // 0x004bb5bc (the shared epilogue, written out on this path)
                                                                charge(ctx, 2);
                                                                sp = addiu(sp, 0x80);
                                                                return;
                                                            }
                                                        L_004bb420:
                                                            charge(ctx, 25);
                                                            lwc1(f13, sp, 0x8);
                                                            sub_s(f12, f6, f2);
                                                            sub_s(f11, f5, f1);
                                                            sub_s(f9, f9, f13);
                                                            mula_s(f12, f2);
                                                            madda_s(f9, f13);
                                                            madd_s(f5, f11, f1);
                                                            mula_s(f12, f12);
                                                            madda_s(f9, f9);
                                                            madd_s(f0, f11, f11);
                                                            div_s(f6, f5, f0);
                                                            mtc1(zero, f7);
                                                            adda_s(f7, f13);
                                                            msub_s(f5, f9, f6);
                                                            adda_s(f7, f2);
                                                            msub_s(f0, f12, f6);
                                                            adda_s(f7, f1);
                                                            msub_s(f2, f11, f6);
                                                            mula_s(f0, f0);
                                                            madda_s(f5, f5);
                                                            madd_s(f1, f2, f2);
                                                            c_le_s(f1, f10);
                                                            if (!cond(ctx)) {
                                                                // 0x004bb484
                                                                charge(ctx, 8);
                                                                mul_s(f0, f0, f4);
                                                                adda_s(f7, f0);
                                                                madd_s(f0, f5, f8);
                                                                adda_s(f7, f0);
                                                                madd_s(f0, f2, f3);
                                                                c_lt_s(f1, f0);
                                                                if (!cond(ctx)) {
                                                                    goto L_004bb5b8;
                                                                }
                                                                // 0x004bb4a4
                                                                charge(ctx, 2);
                                                                v0 = 0;
                                                                // 0x004bb5bc (the shared epilogue, written out on this path)
                                                                charge(ctx, 2);
                                                                sp = addiu(sp, 0x80);
                                                                return;
                                                            }
                                                        L_004bb5b8:
                                                            charge(ctx, 1);
                                                            v0 = 1;
                                                        } else {
                                                            // 0x004bb2e0
                                                            charge(ctx, 8);
                                                            mul_s(f11, f4, f2);
                                                            adda_s(f0, f11);
                                                            madd_s(f11, f8, f7);
                                                            adda_s(f0, f11);
                                                            madd_s(f0, f3, f1);
                                                            c_le_s(f0, f13);
                                                            if (cond(ctx)) {
                                                                goto L_004bb308;
                                                            }
                                                            // 0x004bb300
                                                            charge(ctx, 2);
                                                            v0 = 0;
                                                        }
                                                    } else {
                                                        // 0x004bb278
                                                        charge(ctx, 8);
                                                        mul_s(f11, f2, f6);
                                                        adda_s(f0, f11);
                                                        madd_s(f11, f7, f9);
                                                        adda_s(f0, f11);
                                                        madd_s(f11, f1, f5);
                                                        c_le_s(f11, f12);
                                                        if (cond(ctx)) {
                                                            goto L_004bb308;
                                                        }
                                                        // 0x004bb298
                                                        charge(ctx, 8);
                                                        mul_s(f11, f2, f4);
                                                        adda_s(f0, f11);
                                                        madd_s(f11, f7, f8);
                                                        adda_s(f0, f11);
                                                        madd_s(f0, f1, f3);
                                                        c_le_s(f0, f12);
                                                        if (cond(ctx)) {
                                                            goto L_004bb308;
                                                        }
                                                        // 0x004bb2b8
                                                        charge(ctx, 2);
                                                        v0 = 0;
                                                    }
                                                } else {
                                                    // 0x004bb1d0
                                                    charge(ctx, 3);
                                                    c_lt_s(f12, f14);
                                                    if (!cond(ctx)) {
                                                        // 0x004bb224
                                                        charge(ctx, 8);
                                                        mul_s(f11, f6, f4);
                                                        adda_s(f0, f11);
                                                        madd_s(f11, f9, f8);
                                                        adda_s(f0, f11);
                                                        madd_s(f11, f5, f3);
                                                        c_le_s(f11, f14);
                                                        if (cond(ctx)) {
                                                            goto L_004bb308;
                                                        }
                                                        // 0x004bb244
                                                        charge(ctx, 8);
                                                        mul_s(f11, f6, f2);
                                                        adda_s(f0, f11);
                                                        madd_s(f11, f9, f7);
                                                        adda_s(f0, f11);
                                                        madd_s(f0, f5, f1);
                                                        c_le_s(f0, f14);
                                                        if (cond(ctx)) {
                                                            goto L_004bb308;
                                                        }
                                                        // 0x004bb264
                                                        charge(ctx, 2);
                                                        v0 = 0;
                                                    } else {
                                                        // 0x004bb1dc
                                                        charge(ctx, 8);
                                                        mul_s(f11, f2, f6);
                                                        adda_s(f0, f11);
                                                        madd_s(f11, f7, f9);
                                                        adda_s(f0, f11);
                                                        madd_s(f11, f1, f5);
                                                        c_le_s(f11, f12);
                                                        if (cond(ctx)) {
                                                            goto L_004bb308;
                                                        }
                                                        // 0x004bb1fc
                                                        charge(ctx, 8);
                                                        mul_s(f11, f2, f4);
                                                        adda_s(f0, f11);
                                                        madd_s(f11, f7, f8);
                                                        adda_s(f0, f11);
                                                        madd_s(f0, f1, f3);
                                                        c_le_s(f0, f12);
                                                        if (cond(ctx)) {
                                                            goto L_004bb308;
                                                        }
                                                        // 0x004bb21c
                                                        charge(ctx, 2);
                                                        v0 = 0;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    // 0x004bb5bc (the shared epilogue, written out on this path)
                                    charge(ctx, 2);
                                    sp = addiu(sp, 0x80);
                                    return;
                                }
                            L_004bb598:
                                charge(ctx, 2);
                                v0 = 0;
                            }
                        } else {
                            // 0x004bb588
                            charge(ctx, 2);
                            v0 = 0;
                        }
                    } else {
                        // 0x004bafb8
                        charge(ctx, 3);
                        t6 = si(-3);
                        if (t7 != t6) {
                            goto L_004bb010;
                        }
                        // 0x004bafc4
                        charge(ctx, 17);
                        lwc1(f2, t4, 0);
                        lwc1(f3, a0, 12);
                        lwc1(f1, t2, 0);
                        lwc1(f0, v0, 0);
                        add_s(f2, f2, f3);
                        add_s(f1, f1, f3);
                        add_s(f0, f0, f3);
                        swc1(f2, sp, 0x40);
                        swc1(f1, sp, 0x3C);
                        lw(t8, sp, 0x40);
                        lw(t7, sp, 0x3C);
                        swc1(f0, sp, 0x38);
                        lw(t6, sp, 0x38);
                        t7 = t8 & t7;
                        t6 = t6 & t7;
                        if (i64(t6) >= 0) {
                            goto L_004bb010;
                        }
                        // 0x004bb008
                        charge(ctx, 2);
                        v0 = 0;
                    }
                } else {
                    // 0x004bb53c
                    charge(ctx, 2);
                    v0 = 0;
                }
            } else {
                // 0x004baf38
                charge(ctx, 3);
                t6 = si(-3);
                if (t7 != t6) {
                    goto L_004baf90;
                }
                // 0x004baf44
                charge(ctx, 17);
                lwc1(f2, t5, 0);
                lwc1(f3, a0, 12);
                lwc1(f1, t3, 0);
                lwc1(f0, v1, 0);
                add_s(f2, f2, f3);
                add_s(f1, f1, f3);
                add_s(f0, f0, f3);
                swc1(f2, sp, 0x58);
                swc1(f1, sp, 0x54);
                lw(t8, sp, 0x58);
                lw(t7, sp, 0x54);
                swc1(f0, sp, 0x50);
                lw(t6, sp, 0x50);
                t7 = t8 & t7;
                t6 = t6 & t7;
                if (i64(t6) >= 0) {
                    goto L_004baf90;
                }
                // 0x004baf88
                charge(ctx, 2);
                v0 = 0;
            }
        } else {
            // 0x004bb4f0
            charge(ctx, 2);
            v0 = 0;
        }
    } else {
        // 0x004baeb8
        charge(ctx, 3);
        t6 = si(-3);
        if (t7 != t6) {
            goto L_004baf10;
        }
        // 0x004baec4
        charge(ctx, 17);
        lwc1(f3, a0, 12);
        lwc1(f2, sp, 0x28);
        lwc1(f1, sp, 0x18);
        lwc1(f0, sp, 0x8);
        add_s(f2, f2, f3);
        add_s(f1, f1, f3);
        add_s(f0, f0, f3);
        swc1(f2, sp, 0x70);
        swc1(f1, sp, 0x6C);
        lw(t8, sp, 0x70);
        lw(t7, sp, 0x6C);
        swc1(f0, sp, 0x68);
        lw(t6, sp, 0x68);
        t7 = t8 & t7;
        t6 = t6 & t7;
        if (i64(t6) >= 0) {
            goto L_004baf10;
        }
        // 0x004baf08
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004bb5bc (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x80);
}


// sub_4BB5D0 [boxTriangleTest] -- box / triangle overlap: 1 when the triangle and the box intersect (separating axes)
// ($a0 = the box {maximum, minimum}, $a1..$a3 = the vertices) The box's centre and half extents; the triangle's
// vertices relative to the centre; the three box axes, the face normal and the nine edge-cross-axis directions as
// separating-axis candidates: 0 at the first that separates them, else 1.
// 0x004BB5D0 sub_4BB5D0 -- 4692 bytes; frame 0x20: f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
void sub_4BB5D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16}, f17{ctx, 17}, f18{ctx, 18}, f19{ctx, 19}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x004bb5d0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    lwc1(f11, a0, 4);
    lwc1(f4, a1, 4);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    c_le_s(f4, f11);
    swc1(f20, sp, 0x0);
    if (cond(ctx)) {
        // 0x004bb5f8
        charge(ctx, 4);
        lwc1(f0, a0, 16);
        c_lt_s(f4, f0);
        if (!cond(ctx)) {
            // 0x004bb610
            charge(ctx, 1);
            t0 = 0;
        } else {
            // 0x004bb608
            charge(ctx, 2);
            t0 = 8;
        }
    } else {
        // 0x004bb5f0
        charge(ctx, 2);
        t0 = 4;
    }
    // 0x004bb614
    charge(ctx, 5);
    lwc1(f10, a0, 0);
    lwc1(f5, a1, 0);
    c_le_s(f5, f10);
    if (cond(ctx)) {
        // 0x004bb630
        charge(ctx, 4);
        lwc1(f0, a0, 12);
        c_lt_s(f5, f0);
        if (!cond(ctx)) {
            // 0x004bb648
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x004bb640
            charge(ctx, 2);
            v0 = 2;
        }
    } else {
        // 0x004bb628
        charge(ctx, 2);
        v0 = 1;
    }
    // 0x004bb64c
    charge(ctx, 5);
    lwc1(f9, a0, 8);
    lwc1(f3, a1, 8);
    c_le_s(f3, f9);
    if (cond(ctx)) {
        // 0x004bb668
        charge(ctx, 4);
        lwc1(f0, a0, 20);
        c_lt_s(f3, f0);
        if (!cond(ctx)) {
            // 0x004bb680
            charge(ctx, 1);
            v1 = 0;
        } else {
            // 0x004bb678
            charge(ctx, 2);
            v1 = 32;
        }
    } else {
        // 0x004bb660
        charge(ctx, 2);
        v1 = 16;
    }
    // 0x004bb684
    charge(ctx, 4);
    v0 = v0 | t0;
    v1 = v1 | v0;
    if (v1 == 0) {
        // 0x004bbb88
        charge(ctx, 2);
        v0 = 1;
    } else {
        // 0x004bb694
        charge(ctx, 4);
        lwc1(f1, a2, 4);
        c_le_s(f1, f11);
        if (cond(ctx)) {
            // 0x004bb6ac
            charge(ctx, 4);
            lwc1(f0, a0, 16);
            c_lt_s(f1, f0);
            if (!cond(ctx)) {
                // 0x004bb6c4
                charge(ctx, 1);
                t0 = 0;
            } else {
                // 0x004bb6bc
                charge(ctx, 2);
                t0 = 8;
            }
        } else {
            // 0x004bb6a4
            charge(ctx, 2);
            t0 = 4;
        }
        // 0x004bb6c8
        charge(ctx, 4);
        lwc1(f2, a2, 0);
        c_le_s(f2, f10);
        if (cond(ctx)) {
            // 0x004bb6e0
            charge(ctx, 4);
            lwc1(f0, a0, 12);
            c_lt_s(f2, f0);
            if (!cond(ctx)) {
                // 0x004bb6f8
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x004bb6f0
                charge(ctx, 2);
                v0 = 2;
            }
        } else {
            // 0x004bb6d8
            charge(ctx, 2);
            v0 = 1;
        }
        // 0x004bb6fc
        charge(ctx, 4);
        lwc1(f0, a2, 8);
        c_le_s(f0, f9);
        if (cond(ctx)) {
            // 0x004bb714
            charge(ctx, 4);
            lwc1(f6, a0, 20);
            c_lt_s(f0, f6);
            if (!cond(ctx)) {
                // 0x004bb72c
                charge(ctx, 1);
                a2 = 0;
            } else {
                // 0x004bb724
                charge(ctx, 2);
                a2 = 32;
            }
        } else {
            // 0x004bb70c
            charge(ctx, 2);
            a2 = 16;
        }
        // 0x004bb730
        charge(ctx, 4);
        v0 = v0 | t0;
        v0 = a2 | v0;
        if (v0 == 0) {
            // 0x004bbb90
            charge(ctx, 2);
            v0 = 1;
        } else {
            // 0x004bb740
            charge(ctx, 4);
            lwc1(f8, a3, 4);
            c_le_s(f8, f11);
            if (cond(ctx)) {
                // 0x004bb758
                charge(ctx, 4);
                lwc1(f6, a0, 16);
                c_lt_s(f8, f6);
                if (!cond(ctx)) {
                    // 0x004bb770
                    charge(ctx, 1);
                    t0 = 0;
                } else {
                    // 0x004bb768
                    charge(ctx, 2);
                    t0 = 8;
                }
            } else {
                // 0x004bb750
                charge(ctx, 2);
                t0 = 4;
            }
            // 0x004bb774
            charge(ctx, 4);
            lwc1(f7, a3, 0);
            c_le_s(f7, f10);
            if (cond(ctx)) {
                // 0x004bb78c
                charge(ctx, 4);
                lwc1(f6, a0, 12);
                c_lt_s(f7, f6);
                if (!cond(ctx)) {
                    // 0x004bb7a4
                    charge(ctx, 1);
                    a2 = 0;
                } else {
                    // 0x004bb79c
                    charge(ctx, 2);
                    a2 = 2;
                }
            } else {
                // 0x004bb784
                charge(ctx, 2);
                a2 = 1;
            }
            // 0x004bb7a8
            charge(ctx, 4);
            lwc1(f6, a3, 8);
            c_le_s(f6, f9);
            if (cond(ctx)) {
                // 0x004bb7c0
                charge(ctx, 4);
                lwc1(f12, a0, 20);
                c_lt_s(f6, f12);
                if (!cond(ctx)) {
                    // 0x004bb7d8
                    charge(ctx, 1);
                    a3 = 0;
                } else {
                    // 0x004bb7d0
                    charge(ctx, 2);
                    a3 = 32;
                }
            } else {
                // 0x004bb7b8
                charge(ctx, 2);
                a3 = 16;
            }
            // 0x004bb7dc
            charge(ctx, 4);
            a2 = a2 | t0;
            t0 = a3 | a2;
            if (t0 == 0) {
                // 0x004bbb98
                charge(ctx, 2);
                v0 = 1;
            } else {
                // 0x004bb7ec
                charge(ctx, 4);
                a3 = v1 & v0;
                a2 = t0 & a3;
                if (a2 != 0) {
                    // 0x004bbba0
                    charge(ctx, 2);
                    v0 = 0;
                } else {
                    // 0x004bb7fc
                    charge(ctx, 2);
                    if (a3 == 0) {
                        // 0x004bb804
                        charge(ctx, 15);
                        lwc1(f14, a0, 16);
                        a3 = v1 ^ v0;
                        lwc1(f13, a0, 20);
                        a2 = a3 & 0x1;
                        lwc1(f15, a0, 12);
                        sub_s(f18, f2, f5);
                        sub_s(f16, f4, f14);
                        sub_s(f17, f3, f13);
                        sub_s(f19, f1, f4);
                        sub_s(f20, f0, f3);
                        sub_s(f12, f5, f10);
                        sub_s(f15, f5, f15);
                        sub_s(f13, f4, f11);
                        sub_s(f14, f3, f9);
                        if (a2 != 0) {
                            // 0x004bbba8
                            charge(ctx, 5);
                            mtc1(zero, f21);
                            c_lt_s(f18, f21);
                            mul_s(f22, f12, f19);
                            if (!cond(ctx)) {
                                // 0x004bbc08
                                charge(ctx, 4);
                                mul_s(f21, f13, f18);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb840;
                                }
                                // 0x004bbc18
                                charge(ctx, 4);
                                mul_s(f21, f16, f18);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb840;
                                }
                                // 0x004bbc28
                                charge(ctx, 5);
                                mul_s(f22, f12, f20);
                                mul_s(f21, f14, f18);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb840;
                                }
                                // 0x004bbc3c
                                charge(ctx, 4);
                                mul_s(f21, f17, f18);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb840;
                                }
                                // 0x004bbc4c
                                charge(ctx, 2);
                                v0 = 1;
                            } else {
                                // 0x004bbbbc
                                charge(ctx, 4);
                                mul_s(f21, f13, f18);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb840;
                                }
                                // 0x004bbbcc
                                charge(ctx, 4);
                                mul_s(f21, f16, f18);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb840;
                                }
                                // 0x004bbbdc
                                charge(ctx, 5);
                                mul_s(f22, f12, f20);
                                mul_s(f21, f14, f18);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb840;
                                }
                                // 0x004bbbf0
                                charge(ctx, 4);
                                mul_s(f21, f17, f18);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb840;
                                }
                                // 0x004bbc00
                                charge(ctx, 2);
                                v0 = 1;
                            }
                            // 0x004bc810 (the shared epilogue, written out on this path)
                            charge(ctx, 5);
                            lwc1(f22, sp, 0x8);
                            lwc1(f21, sp, 0x4);
                            lwc1(f20, sp, 0x0);
                            sp = addiu(sp, 0x20);
                            return;
                        }
                    L_004bb840:
                        charge(ctx, 3);
                        a2 = a3 & 0x2;
                        if (a2 != 0) {
                            // 0x004bbc54
                            charge(ctx, 5);
                            mtc1(zero, f21);
                            c_lt_s(f18, f21);
                            mul_s(f22, f15, f19);
                            if (!cond(ctx)) {
                                // 0x004bbcb4
                                charge(ctx, 4);
                                mul_s(f21, f13, f18);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb84c;
                                }
                                // 0x004bbcc4
                                charge(ctx, 4);
                                mul_s(f21, f16, f18);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb84c;
                                }
                                // 0x004bbcd4
                                charge(ctx, 5);
                                mul_s(f22, f15, f20);
                                mul_s(f21, f14, f18);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb84c;
                                }
                                // 0x004bbce8
                                charge(ctx, 4);
                                mul_s(f21, f17, f18);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb84c;
                                }
                                // 0x004bbcf8
                                charge(ctx, 2);
                                v0 = 1;
                            } else {
                                // 0x004bbc68
                                charge(ctx, 4);
                                mul_s(f21, f13, f18);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb84c;
                                }
                                // 0x004bbc78
                                charge(ctx, 4);
                                mul_s(f21, f16, f18);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb84c;
                                }
                                // 0x004bbc88
                                charge(ctx, 5);
                                mul_s(f22, f15, f20);
                                mul_s(f21, f14, f18);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb84c;
                                }
                                // 0x004bbc9c
                                charge(ctx, 4);
                                mul_s(f21, f17, f18);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb84c;
                                }
                                // 0x004bbcac
                                charge(ctx, 2);
                                v0 = 1;
                            }
                            // 0x004bc810 (the shared epilogue, written out on this path)
                            charge(ctx, 5);
                            lwc1(f22, sp, 0x8);
                            lwc1(f21, sp, 0x4);
                            lwc1(f20, sp, 0x0);
                            sp = addiu(sp, 0x20);
                            return;
                        }
                    L_004bb84c:
                        charge(ctx, 3);
                        a2 = a3 & 0x4;
                        if (a2 != 0) {
                            // 0x004bbd00
                            charge(ctx, 5);
                            mtc1(zero, f21);
                            c_lt_s(f19, f21);
                            mul_s(f22, f13, f20);
                            if (!cond(ctx)) {
                                // 0x004bbd60
                                charge(ctx, 4);
                                mul_s(f21, f14, f19);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb858;
                                }
                                // 0x004bbd70
                                charge(ctx, 4);
                                mul_s(f21, f17, f19);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb858;
                                }
                                // 0x004bbd80
                                charge(ctx, 5);
                                mul_s(f22, f13, f18);
                                mul_s(f21, f12, f19);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb858;
                                }
                                // 0x004bbd94
                                charge(ctx, 4);
                                mul_s(f21, f15, f19);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb858;
                                }
                                // 0x004bbda4
                                charge(ctx, 2);
                                v0 = 1;
                            } else {
                                // 0x004bbd14
                                charge(ctx, 4);
                                mul_s(f21, f14, f19);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb858;
                                }
                                // 0x004bbd24
                                charge(ctx, 4);
                                mul_s(f21, f17, f19);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb858;
                                }
                                // 0x004bbd34
                                charge(ctx, 5);
                                mul_s(f22, f13, f18);
                                mul_s(f21, f12, f19);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb858;
                                }
                                // 0x004bbd48
                                charge(ctx, 4);
                                mul_s(f21, f15, f19);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb858;
                                }
                                // 0x004bbd58
                                charge(ctx, 2);
                                v0 = 1;
                            }
                            // 0x004bc810 (the shared epilogue, written out on this path)
                            charge(ctx, 5);
                            lwc1(f22, sp, 0x8);
                            lwc1(f21, sp, 0x4);
                            lwc1(f20, sp, 0x0);
                            sp = addiu(sp, 0x20);
                            return;
                        }
                    L_004bb858:
                        charge(ctx, 3);
                        a2 = a3 & 0x8;
                        if (a2 != 0) {
                            // 0x004bbdac
                            charge(ctx, 5);
                            mtc1(zero, f21);
                            c_lt_s(f19, f21);
                            mul_s(f22, f16, f20);
                            if (!cond(ctx)) {
                                // 0x004bbe0c
                                charge(ctx, 4);
                                mul_s(f21, f14, f19);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb864;
                                }
                                // 0x004bbe1c
                                charge(ctx, 4);
                                mul_s(f21, f17, f19);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb864;
                                }
                                // 0x004bbe2c
                                charge(ctx, 5);
                                mul_s(f22, f16, f18);
                                mul_s(f21, f12, f19);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb864;
                                }
                                // 0x004bbe40
                                charge(ctx, 4);
                                mul_s(f21, f15, f19);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb864;
                                }
                                // 0x004bbe50
                                charge(ctx, 2);
                                v0 = 1;
                            } else {
                                // 0x004bbdc0
                                charge(ctx, 4);
                                mul_s(f21, f14, f19);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb864;
                                }
                                // 0x004bbdd0
                                charge(ctx, 4);
                                mul_s(f21, f17, f19);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb864;
                                }
                                // 0x004bbde0
                                charge(ctx, 5);
                                mul_s(f22, f16, f18);
                                mul_s(f21, f12, f19);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb864;
                                }
                                // 0x004bbdf4
                                charge(ctx, 4);
                                mul_s(f21, f15, f19);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb864;
                                }
                                // 0x004bbe04
                                charge(ctx, 2);
                                v0 = 1;
                            }
                            // 0x004bc810 (the shared epilogue, written out on this path)
                            charge(ctx, 5);
                            lwc1(f22, sp, 0x8);
                            lwc1(f21, sp, 0x4);
                            lwc1(f20, sp, 0x0);
                            sp = addiu(sp, 0x20);
                            return;
                        }
                    L_004bb864:
                        charge(ctx, 3);
                        a2 = a3 & 0x10;
                        if (a2 != 0) {
                            // 0x004bbe58
                            charge(ctx, 5);
                            mtc1(zero, f21);
                            c_lt_s(f20, f21);
                            mul_s(f22, f14, f18);
                            if (!cond(ctx)) {
                                // 0x004bbeb8
                                charge(ctx, 4);
                                mul_s(f21, f12, f20);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb870;
                                }
                                // 0x004bbec8
                                charge(ctx, 4);
                                mul_s(f21, f15, f20);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb870;
                                }
                                // 0x004bbed8
                                charge(ctx, 5);
                                mul_s(f21, f14, f19);
                                mul_s(f14, f13, f20);
                                c_le_s(f21, f14);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb870;
                                }
                                // 0x004bbeec
                                charge(ctx, 4);
                                mul_s(f14, f16, f20);
                                c_lt_s(f21, f14);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb870;
                                }
                                // 0x004bbefc
                                charge(ctx, 2);
                                v0 = 1;
                            } else {
                                // 0x004bbe6c
                                charge(ctx, 4);
                                mul_s(f21, f12, f20);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb870;
                                }
                                // 0x004bbe7c
                                charge(ctx, 4);
                                mul_s(f21, f15, f20);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb870;
                                }
                                // 0x004bbe8c
                                charge(ctx, 5);
                                mul_s(f21, f14, f19);
                                mul_s(f14, f13, f20);
                                c_lt_s(f21, f14);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb870;
                                }
                                // 0x004bbea0
                                charge(ctx, 4);
                                mul_s(f14, f16, f20);
                                c_le_s(f21, f14);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb870;
                                }
                                // 0x004bbeb0
                                charge(ctx, 2);
                                v0 = 1;
                            }
                            // 0x004bc810 (the shared epilogue, written out on this path)
                            charge(ctx, 5);
                            lwc1(f22, sp, 0x8);
                            lwc1(f21, sp, 0x4);
                            lwc1(f20, sp, 0x0);
                            sp = addiu(sp, 0x20);
                            return;
                        }
                    L_004bb870:
                        charge(ctx, 3);
                        a2 = a3 & 0x20;
                        if (a2 == 0) {
                            goto L_004bb928;
                        }
                        // 0x004bb87c
                        charge(ctx, 5);
                        mtc1(zero, f14);
                        c_lt_s(f20, f14);
                        mul_s(f18, f17, f18);
                        if (!cond(ctx)) {
                            // 0x004bb8dc
                            charge(ctx, 4);
                            mul_s(f12, f12, f20);
                            c_le_s(f18, f12);
                            if (cond(ctx)) {
                                goto L_004bb928;
                            }
                            // 0x004bb8ec
                            charge(ctx, 4);
                            mul_s(f12, f15, f20);
                            c_lt_s(f18, f12);
                            if (!cond(ctx)) {
                                goto L_004bb928;
                            }
                            // 0x004bb8fc
                            charge(ctx, 5);
                            mul_s(f14, f17, f19);
                            mul_s(f12, f13, f20);
                            c_le_s(f14, f12);
                            if (cond(ctx)) {
                                goto L_004bb928;
                            }
                            // 0x004bb910
                            charge(ctx, 4);
                            mul_s(f12, f16, f20);
                            c_lt_s(f14, f12);
                            if (!cond(ctx)) {
                                goto L_004bb928;
                            }
                            // 0x004bb920
                            charge(ctx, 2);
                            v0 = 1;
                        } else {
                            // 0x004bb890
                            charge(ctx, 4);
                            mul_s(f12, f12, f20);
                            c_lt_s(f18, f12);
                            if (!cond(ctx)) {
                                goto L_004bb928;
                            }
                            // 0x004bb8a0
                            charge(ctx, 4);
                            mul_s(f12, f15, f20);
                            c_le_s(f18, f12);
                            if (cond(ctx)) {
                                goto L_004bb928;
                            }
                            // 0x004bb8b0
                            charge(ctx, 5);
                            mul_s(f14, f17, f19);
                            mul_s(f12, f13, f20);
                            c_lt_s(f14, f12);
                            if (!cond(ctx)) {
                                goto L_004bb928;
                            }
                            // 0x004bb8c4
                            charge(ctx, 4);
                            mul_s(f12, f16, f20);
                            c_le_s(f14, f12);
                            if (cond(ctx)) {
                                goto L_004bb928;
                            }
                            // 0x004bb8d4
                            charge(ctx, 2);
                            v0 = 1;
                        }
                        // 0x004bc810 (the shared epilogue, written out on this path)
                        charge(ctx, 5);
                        lwc1(f22, sp, 0x8);
                        lwc1(f21, sp, 0x4);
                        lwc1(f20, sp, 0x0);
                        sp = addiu(sp, 0x20);
                        return;
                    }
                L_004bb928:
                    charge(ctx, 3);
                    a2 = v1 & t0;
                    if (a2 == 0) {
                        // 0x004bb934
                        charge(ctx, 15);
                        lwc1(f14, a0, 16);
                        a2 = v1 ^ t0;
                        lwc1(f13, a0, 20);
                        v1 = a2 & 0x1;
                        lwc1(f15, a0, 12);
                        sub_s(f18, f7, f5);
                        sub_s(f16, f4, f14);
                        sub_s(f17, f3, f13);
                        sub_s(f19, f8, f4);
                        sub_s(f20, f6, f3);
                        sub_s(f12, f5, f10);
                        sub_s(f15, f5, f15);
                        sub_s(f13, f4, f11);
                        sub_s(f14, f3, f9);
                        if (v1 != 0) {
                            // 0x004bbf04
                            charge(ctx, 5);
                            mtc1(zero, f21);
                            c_lt_s(f18, f21);
                            mul_s(f22, f12, f19);
                            if (!cond(ctx)) {
                                // 0x004bbf64
                                charge(ctx, 4);
                                mul_s(f21, f13, f18);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb970;
                                }
                                // 0x004bbf74
                                charge(ctx, 4);
                                mul_s(f21, f16, f18);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb970;
                                }
                                // 0x004bbf84
                                charge(ctx, 5);
                                mul_s(f22, f12, f20);
                                mul_s(f21, f14, f18);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb970;
                                }
                                // 0x004bbf98
                                charge(ctx, 4);
                                mul_s(f21, f17, f18);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb970;
                                }
                                // 0x004bbfa8
                                charge(ctx, 2);
                                v0 = 1;
                            } else {
                                // 0x004bbf18
                                charge(ctx, 4);
                                mul_s(f21, f13, f18);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb970;
                                }
                                // 0x004bbf28
                                charge(ctx, 4);
                                mul_s(f21, f16, f18);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb970;
                                }
                                // 0x004bbf38
                                charge(ctx, 5);
                                mul_s(f22, f12, f20);
                                mul_s(f21, f14, f18);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb970;
                                }
                                // 0x004bbf4c
                                charge(ctx, 4);
                                mul_s(f21, f17, f18);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb970;
                                }
                                // 0x004bbf5c
                                charge(ctx, 2);
                                v0 = 1;
                            }
                            // 0x004bc810 (the shared epilogue, written out on this path)
                            charge(ctx, 5);
                            lwc1(f22, sp, 0x8);
                            lwc1(f21, sp, 0x4);
                            lwc1(f20, sp, 0x0);
                            sp = addiu(sp, 0x20);
                            return;
                        }
                    L_004bb970:
                        charge(ctx, 3);
                        v1 = a2 & 0x2;
                        if (v1 != 0) {
                            // 0x004bbfb0
                            charge(ctx, 5);
                            mtc1(zero, f21);
                            c_lt_s(f18, f21);
                            mul_s(f22, f15, f19);
                            if (!cond(ctx)) {
                                // 0x004bc010
                                charge(ctx, 4);
                                mul_s(f21, f13, f18);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb97c;
                                }
                                // 0x004bc020
                                charge(ctx, 4);
                                mul_s(f21, f16, f18);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb97c;
                                }
                                // 0x004bc030
                                charge(ctx, 5);
                                mul_s(f22, f15, f20);
                                mul_s(f21, f14, f18);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb97c;
                                }
                                // 0x004bc044
                                charge(ctx, 4);
                                mul_s(f21, f17, f18);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb97c;
                                }
                                // 0x004bc054
                                charge(ctx, 2);
                                v0 = 1;
                            } else {
                                // 0x004bbfc4
                                charge(ctx, 4);
                                mul_s(f21, f13, f18);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb97c;
                                }
                                // 0x004bbfd4
                                charge(ctx, 4);
                                mul_s(f21, f16, f18);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb97c;
                                }
                                // 0x004bbfe4
                                charge(ctx, 5);
                                mul_s(f22, f15, f20);
                                mul_s(f21, f14, f18);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb97c;
                                }
                                // 0x004bbff8
                                charge(ctx, 4);
                                mul_s(f21, f17, f18);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb97c;
                                }
                                // 0x004bc008
                                charge(ctx, 2);
                                v0 = 1;
                            }
                            // 0x004bc810 (the shared epilogue, written out on this path)
                            charge(ctx, 5);
                            lwc1(f22, sp, 0x8);
                            lwc1(f21, sp, 0x4);
                            lwc1(f20, sp, 0x0);
                            sp = addiu(sp, 0x20);
                            return;
                        }
                    L_004bb97c:
                        charge(ctx, 3);
                        v1 = a2 & 0x4;
                        if (v1 != 0) {
                            // 0x004bc05c
                            charge(ctx, 5);
                            mtc1(zero, f21);
                            c_lt_s(f19, f21);
                            mul_s(f22, f13, f20);
                            if (!cond(ctx)) {
                                // 0x004bc0bc
                                charge(ctx, 4);
                                mul_s(f21, f14, f19);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb988;
                                }
                                // 0x004bc0cc
                                charge(ctx, 4);
                                mul_s(f21, f17, f19);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb988;
                                }
                                // 0x004bc0dc
                                charge(ctx, 5);
                                mul_s(f22, f13, f18);
                                mul_s(f21, f12, f19);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb988;
                                }
                                // 0x004bc0f0
                                charge(ctx, 4);
                                mul_s(f21, f15, f19);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb988;
                                }
                                // 0x004bc100
                                charge(ctx, 2);
                                v0 = 1;
                            } else {
                                // 0x004bc070
                                charge(ctx, 4);
                                mul_s(f21, f14, f19);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb988;
                                }
                                // 0x004bc080
                                charge(ctx, 4);
                                mul_s(f21, f17, f19);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb988;
                                }
                                // 0x004bc090
                                charge(ctx, 5);
                                mul_s(f22, f13, f18);
                                mul_s(f21, f12, f19);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb988;
                                }
                                // 0x004bc0a4
                                charge(ctx, 4);
                                mul_s(f21, f15, f19);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb988;
                                }
                                // 0x004bc0b4
                                charge(ctx, 2);
                                v0 = 1;
                            }
                            // 0x004bc810 (the shared epilogue, written out on this path)
                            charge(ctx, 5);
                            lwc1(f22, sp, 0x8);
                            lwc1(f21, sp, 0x4);
                            lwc1(f20, sp, 0x0);
                            sp = addiu(sp, 0x20);
                            return;
                        }
                    L_004bb988:
                        charge(ctx, 3);
                        v1 = a2 & 0x8;
                        if (v1 != 0) {
                            // 0x004bc108
                            charge(ctx, 5);
                            mtc1(zero, f21);
                            c_lt_s(f19, f21);
                            mul_s(f22, f16, f20);
                            if (!cond(ctx)) {
                                // 0x004bc168
                                charge(ctx, 4);
                                mul_s(f21, f14, f19);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb994;
                                }
                                // 0x004bc178
                                charge(ctx, 4);
                                mul_s(f21, f17, f19);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb994;
                                }
                                // 0x004bc188
                                charge(ctx, 5);
                                mul_s(f22, f16, f18);
                                mul_s(f21, f12, f19);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb994;
                                }
                                // 0x004bc19c
                                charge(ctx, 4);
                                mul_s(f21, f15, f19);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb994;
                                }
                                // 0x004bc1ac
                                charge(ctx, 2);
                                v0 = 1;
                            } else {
                                // 0x004bc11c
                                charge(ctx, 4);
                                mul_s(f21, f14, f19);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb994;
                                }
                                // 0x004bc12c
                                charge(ctx, 4);
                                mul_s(f21, f17, f19);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb994;
                                }
                                // 0x004bc13c
                                charge(ctx, 5);
                                mul_s(f22, f16, f18);
                                mul_s(f21, f12, f19);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb994;
                                }
                                // 0x004bc150
                                charge(ctx, 4);
                                mul_s(f21, f15, f19);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb994;
                                }
                                // 0x004bc160
                                charge(ctx, 2);
                                v0 = 1;
                            }
                            // 0x004bc810 (the shared epilogue, written out on this path)
                            charge(ctx, 5);
                            lwc1(f22, sp, 0x8);
                            lwc1(f21, sp, 0x4);
                            lwc1(f20, sp, 0x0);
                            sp = addiu(sp, 0x20);
                            return;
                        }
                    L_004bb994:
                        charge(ctx, 3);
                        v1 = a2 & 0x10;
                        if (v1 != 0) {
                            // 0x004bc1b4
                            charge(ctx, 5);
                            mtc1(zero, f21);
                            c_lt_s(f20, f21);
                            mul_s(f22, f14, f18);
                            if (!cond(ctx)) {
                                // 0x004bc214
                                charge(ctx, 4);
                                mul_s(f21, f12, f20);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb9a0;
                                }
                                // 0x004bc224
                                charge(ctx, 4);
                                mul_s(f21, f15, f20);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb9a0;
                                }
                                // 0x004bc234
                                charge(ctx, 5);
                                mul_s(f21, f14, f19);
                                mul_s(f14, f13, f20);
                                c_le_s(f21, f14);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb9a0;
                                }
                                // 0x004bc248
                                charge(ctx, 4);
                                mul_s(f14, f16, f20);
                                c_lt_s(f21, f14);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb9a0;
                                }
                                // 0x004bc258
                                charge(ctx, 2);
                                v0 = 1;
                            } else {
                                // 0x004bc1c8
                                charge(ctx, 4);
                                mul_s(f21, f12, f20);
                                c_lt_s(f22, f21);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb9a0;
                                }
                                // 0x004bc1d8
                                charge(ctx, 4);
                                mul_s(f21, f15, f20);
                                c_le_s(f22, f21);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb9a0;
                                }
                                // 0x004bc1e8
                                charge(ctx, 5);
                                mul_s(f21, f14, f19);
                                mul_s(f14, f13, f20);
                                c_lt_s(f21, f14);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb9a0;
                                }
                                // 0x004bc1fc
                                charge(ctx, 4);
                                mul_s(f14, f16, f20);
                                c_le_s(f21, f14);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bb9a0;
                                }
                                // 0x004bc20c
                                charge(ctx, 2);
                                v0 = 1;
                            }
                            // 0x004bc810 (the shared epilogue, written out on this path)
                            charge(ctx, 5);
                            lwc1(f22, sp, 0x8);
                            lwc1(f21, sp, 0x4);
                            lwc1(f20, sp, 0x0);
                            sp = addiu(sp, 0x20);
                            return;
                        }
                    L_004bb9a0:
                        charge(ctx, 3);
                        v1 = a2 & 0x20;
                        if (v1 == 0) {
                            goto L_004bba58;
                        }
                        // 0x004bb9ac
                        charge(ctx, 5);
                        mtc1(zero, f14);
                        c_lt_s(f20, f14);
                        mul_s(f18, f17, f18);
                        if (!cond(ctx)) {
                            // 0x004bba0c
                            charge(ctx, 4);
                            mul_s(f12, f12, f20);
                            c_le_s(f18, f12);
                            if (cond(ctx)) {
                                goto L_004bba58;
                            }
                            // 0x004bba1c
                            charge(ctx, 4);
                            mul_s(f12, f15, f20);
                            c_lt_s(f18, f12);
                            if (!cond(ctx)) {
                                goto L_004bba58;
                            }
                            // 0x004bba2c
                            charge(ctx, 5);
                            mul_s(f14, f17, f19);
                            mul_s(f12, f13, f20);
                            c_le_s(f14, f12);
                            if (cond(ctx)) {
                                goto L_004bba58;
                            }
                            // 0x004bba40
                            charge(ctx, 4);
                            mul_s(f12, f16, f20);
                            c_lt_s(f14, f12);
                            if (!cond(ctx)) {
                                goto L_004bba58;
                            }
                            // 0x004bba50
                            charge(ctx, 2);
                            v0 = 1;
                        } else {
                            // 0x004bb9c0
                            charge(ctx, 4);
                            mul_s(f12, f12, f20);
                            c_lt_s(f18, f12);
                            if (!cond(ctx)) {
                                goto L_004bba58;
                            }
                            // 0x004bb9d0
                            charge(ctx, 4);
                            mul_s(f12, f15, f20);
                            c_le_s(f18, f12);
                            if (cond(ctx)) {
                                goto L_004bba58;
                            }
                            // 0x004bb9e0
                            charge(ctx, 5);
                            mul_s(f14, f17, f19);
                            mul_s(f12, f13, f20);
                            c_lt_s(f14, f12);
                            if (!cond(ctx)) {
                                goto L_004bba58;
                            }
                            // 0x004bb9f4
                            charge(ctx, 4);
                            mul_s(f12, f16, f20);
                            c_le_s(f14, f12);
                            if (cond(ctx)) {
                                goto L_004bba58;
                            }
                            // 0x004bba04
                            charge(ctx, 2);
                            v0 = 1;
                        }
                        // 0x004bc810 (the shared epilogue, written out on this path)
                        charge(ctx, 5);
                        lwc1(f22, sp, 0x8);
                        lwc1(f21, sp, 0x4);
                        lwc1(f20, sp, 0x0);
                        sp = addiu(sp, 0x20);
                        return;
                    }
                L_004bba58:
                    charge(ctx, 3);
                    v1 = v0 & t0;
                    if (v1 == 0) {
                        // 0x004bba64
                        charge(ctx, 15);
                        lwc1(f12, a0, 12);
                        v1 = v0 ^ t0;
                        lwc1(f13, a0, 16);
                        v0 = v1 & 0x1;
                        lwc1(f14, a0, 20);
                        sub_s(f10, f2, f10);
                        sub_s(f11, f1, f11);
                        sub_s(f9, f0, f9);
                        sub_s(f15, f7, f2);
                        sub_s(f16, f8, f1);
                        sub_s(f17, f6, f0);
                        sub_s(f12, f2, f12);
                        sub_s(f13, f1, f13);
                        sub_s(f14, f0, f14);
                        if (v0 != 0) {
                            // 0x004bc260
                            charge(ctx, 5);
                            mtc1(zero, f18);
                            c_lt_s(f15, f18);
                            mul_s(f19, f10, f16);
                            if (!cond(ctx)) {
                                // 0x004bc2c0
                                charge(ctx, 4);
                                mul_s(f18, f11, f15);
                                c_le_s(f19, f18);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbaa0;
                                }
                                // 0x004bc2d0
                                charge(ctx, 4);
                                mul_s(f18, f13, f15);
                                c_lt_s(f19, f18);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbaa0;
                                }
                                // 0x004bc2e0
                                charge(ctx, 5);
                                mul_s(f19, f10, f17);
                                mul_s(f18, f9, f15);
                                c_le_s(f19, f18);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbaa0;
                                }
                                // 0x004bc2f4
                                charge(ctx, 4);
                                mul_s(f18, f14, f15);
                                c_lt_s(f19, f18);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbaa0;
                                }
                                // 0x004bc304
                                charge(ctx, 2);
                                v0 = 1;
                            } else {
                                // 0x004bc274
                                charge(ctx, 4);
                                mul_s(f18, f11, f15);
                                c_lt_s(f19, f18);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbaa0;
                                }
                                // 0x004bc284
                                charge(ctx, 4);
                                mul_s(f18, f13, f15);
                                c_le_s(f19, f18);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbaa0;
                                }
                                // 0x004bc294
                                charge(ctx, 5);
                                mul_s(f19, f10, f17);
                                mul_s(f18, f9, f15);
                                c_lt_s(f19, f18);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbaa0;
                                }
                                // 0x004bc2a8
                                charge(ctx, 4);
                                mul_s(f18, f14, f15);
                                c_le_s(f19, f18);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbaa0;
                                }
                                // 0x004bc2b8
                                charge(ctx, 2);
                                v0 = 1;
                            }
                            // 0x004bc810 (the shared epilogue, written out on this path)
                            charge(ctx, 5);
                            lwc1(f22, sp, 0x8);
                            lwc1(f21, sp, 0x4);
                            lwc1(f20, sp, 0x0);
                            sp = addiu(sp, 0x20);
                            return;
                        }
                    L_004bbaa0:
                        charge(ctx, 3);
                        v0 = v1 & 0x2;
                        if (v0 != 0) {
                            // 0x004bc30c
                            charge(ctx, 5);
                            mtc1(zero, f18);
                            c_lt_s(f15, f18);
                            mul_s(f19, f12, f16);
                            if (!cond(ctx)) {
                                // 0x004bc36c
                                charge(ctx, 4);
                                mul_s(f18, f11, f15);
                                c_le_s(f19, f18);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbaac;
                                }
                                // 0x004bc37c
                                charge(ctx, 4);
                                mul_s(f18, f13, f15);
                                c_lt_s(f19, f18);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbaac;
                                }
                                // 0x004bc38c
                                charge(ctx, 5);
                                mul_s(f19, f12, f17);
                                mul_s(f18, f9, f15);
                                c_le_s(f19, f18);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbaac;
                                }
                                // 0x004bc3a0
                                charge(ctx, 4);
                                mul_s(f18, f14, f15);
                                c_lt_s(f19, f18);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbaac;
                                }
                                // 0x004bc3b0
                                charge(ctx, 2);
                                v0 = 1;
                            } else {
                                // 0x004bc320
                                charge(ctx, 4);
                                mul_s(f18, f11, f15);
                                c_lt_s(f19, f18);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbaac;
                                }
                                // 0x004bc330
                                charge(ctx, 4);
                                mul_s(f18, f13, f15);
                                c_le_s(f19, f18);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbaac;
                                }
                                // 0x004bc340
                                charge(ctx, 5);
                                mul_s(f19, f12, f17);
                                mul_s(f18, f9, f15);
                                c_lt_s(f19, f18);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbaac;
                                }
                                // 0x004bc354
                                charge(ctx, 4);
                                mul_s(f18, f14, f15);
                                c_le_s(f19, f18);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbaac;
                                }
                                // 0x004bc364
                                charge(ctx, 2);
                                v0 = 1;
                            }
                            // 0x004bc810 (the shared epilogue, written out on this path)
                            charge(ctx, 5);
                            lwc1(f22, sp, 0x8);
                            lwc1(f21, sp, 0x4);
                            lwc1(f20, sp, 0x0);
                            sp = addiu(sp, 0x20);
                            return;
                        }
                    L_004bbaac:
                        charge(ctx, 3);
                        v0 = v1 & 0x4;
                        if (v0 != 0) {
                            // 0x004bc3b8
                            charge(ctx, 5);
                            mtc1(zero, f18);
                            c_lt_s(f16, f18);
                            mul_s(f19, f11, f17);
                            if (!cond(ctx)) {
                                // 0x004bc418
                                charge(ctx, 4);
                                mul_s(f18, f9, f16);
                                c_le_s(f19, f18);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbab8;
                                }
                                // 0x004bc428
                                charge(ctx, 4);
                                mul_s(f18, f14, f16);
                                c_lt_s(f19, f18);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbab8;
                                }
                                // 0x004bc438
                                charge(ctx, 5);
                                mul_s(f19, f11, f15);
                                mul_s(f18, f10, f16);
                                c_le_s(f19, f18);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbab8;
                                }
                                // 0x004bc44c
                                charge(ctx, 4);
                                mul_s(f18, f12, f16);
                                c_lt_s(f19, f18);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbab8;
                                }
                                // 0x004bc45c
                                charge(ctx, 2);
                                v0 = 1;
                            } else {
                                // 0x004bc3cc
                                charge(ctx, 4);
                                mul_s(f18, f9, f16);
                                c_lt_s(f19, f18);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbab8;
                                }
                                // 0x004bc3dc
                                charge(ctx, 4);
                                mul_s(f18, f14, f16);
                                c_le_s(f19, f18);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbab8;
                                }
                                // 0x004bc3ec
                                charge(ctx, 5);
                                mul_s(f19, f11, f15);
                                mul_s(f18, f10, f16);
                                c_lt_s(f19, f18);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbab8;
                                }
                                // 0x004bc400
                                charge(ctx, 4);
                                mul_s(f18, f12, f16);
                                c_le_s(f19, f18);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbab8;
                                }
                                // 0x004bc410
                                charge(ctx, 2);
                                v0 = 1;
                            }
                            // 0x004bc810 (the shared epilogue, written out on this path)
                            charge(ctx, 5);
                            lwc1(f22, sp, 0x8);
                            lwc1(f21, sp, 0x4);
                            lwc1(f20, sp, 0x0);
                            sp = addiu(sp, 0x20);
                            return;
                        }
                    L_004bbab8:
                        charge(ctx, 3);
                        v0 = v1 & 0x8;
                        if (v0 != 0) {
                            // 0x004bc464
                            charge(ctx, 5);
                            mtc1(zero, f18);
                            c_lt_s(f16, f18);
                            mul_s(f19, f13, f17);
                            if (!cond(ctx)) {
                                // 0x004bc4c4
                                charge(ctx, 4);
                                mul_s(f18, f9, f16);
                                c_le_s(f19, f18);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbac4;
                                }
                                // 0x004bc4d4
                                charge(ctx, 4);
                                mul_s(f18, f14, f16);
                                c_lt_s(f19, f18);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbac4;
                                }
                                // 0x004bc4e4
                                charge(ctx, 5);
                                mul_s(f19, f13, f15);
                                mul_s(f18, f10, f16);
                                c_le_s(f19, f18);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbac4;
                                }
                                // 0x004bc4f8
                                charge(ctx, 4);
                                mul_s(f18, f12, f16);
                                c_lt_s(f19, f18);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbac4;
                                }
                                // 0x004bc508
                                charge(ctx, 2);
                                v0 = 1;
                            } else {
                                // 0x004bc478
                                charge(ctx, 4);
                                mul_s(f18, f9, f16);
                                c_lt_s(f19, f18);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbac4;
                                }
                                // 0x004bc488
                                charge(ctx, 4);
                                mul_s(f18, f14, f16);
                                c_le_s(f19, f18);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbac4;
                                }
                                // 0x004bc498
                                charge(ctx, 5);
                                mul_s(f19, f13, f15);
                                mul_s(f18, f10, f16);
                                c_lt_s(f19, f18);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbac4;
                                }
                                // 0x004bc4ac
                                charge(ctx, 4);
                                mul_s(f18, f12, f16);
                                c_le_s(f19, f18);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbac4;
                                }
                                // 0x004bc4bc
                                charge(ctx, 2);
                                v0 = 1;
                            }
                            // 0x004bc810 (the shared epilogue, written out on this path)
                            charge(ctx, 5);
                            lwc1(f22, sp, 0x8);
                            lwc1(f21, sp, 0x4);
                            lwc1(f20, sp, 0x0);
                            sp = addiu(sp, 0x20);
                            return;
                        }
                    L_004bbac4:
                        charge(ctx, 3);
                        v0 = v1 & 0x10;
                        if (v0 != 0) {
                            // 0x004bc510
                            charge(ctx, 5);
                            mtc1(zero, f18);
                            c_lt_s(f17, f18);
                            mul_s(f19, f9, f15);
                            if (!cond(ctx)) {
                                // 0x004bc570
                                charge(ctx, 4);
                                mul_s(f18, f10, f17);
                                c_le_s(f19, f18);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbad0;
                                }
                                // 0x004bc580
                                charge(ctx, 4);
                                mul_s(f18, f12, f17);
                                c_lt_s(f19, f18);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbad0;
                                }
                                // 0x004bc590
                                charge(ctx, 5);
                                mul_s(f18, f9, f16);
                                mul_s(f9, f11, f17);
                                c_le_s(f18, f9);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbad0;
                                }
                                // 0x004bc5a4
                                charge(ctx, 4);
                                mul_s(f9, f13, f17);
                                c_lt_s(f18, f9);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbad0;
                                }
                                // 0x004bc5b4
                                charge(ctx, 2);
                                v0 = 1;
                            } else {
                                // 0x004bc524
                                charge(ctx, 4);
                                mul_s(f18, f10, f17);
                                c_lt_s(f19, f18);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbad0;
                                }
                                // 0x004bc534
                                charge(ctx, 4);
                                mul_s(f18, f12, f17);
                                c_le_s(f19, f18);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbad0;
                                }
                                // 0x004bc544
                                charge(ctx, 5);
                                mul_s(f18, f9, f16);
                                mul_s(f9, f11, f17);
                                c_lt_s(f18, f9);
                                if (!cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbad0;
                                }
                                // 0x004bc558
                                charge(ctx, 4);
                                mul_s(f9, f13, f17);
                                c_le_s(f18, f9);
                                if (cond(ctx)) {
                                    backedge(ctx);
                                    goto L_004bbad0;
                                }
                                // 0x004bc568
                                charge(ctx, 2);
                                v0 = 1;
                            }
                            // 0x004bc810 (the shared epilogue, written out on this path)
                            charge(ctx, 5);
                            lwc1(f22, sp, 0x8);
                            lwc1(f21, sp, 0x4);
                            lwc1(f20, sp, 0x0);
                            sp = addiu(sp, 0x20);
                            return;
                        }
                    L_004bbad0:
                        charge(ctx, 3);
                        v0 = v1 & 0x20;
                        if (v0 == 0) {
                            goto L_004bc5bc;
                        }
                        // 0x004bbadc
                        charge(ctx, 5);
                        mtc1(zero, f9);
                        c_lt_s(f17, f9);
                        mul_s(f15, f14, f15);
                        if (!cond(ctx)) {
                            // 0x004bbb3c
                            charge(ctx, 4);
                            mul_s(f9, f10, f17);
                            c_le_s(f15, f9);
                            if (cond(ctx)) {
                                goto L_004bc5bc;
                            }
                            // 0x004bbb4c
                            charge(ctx, 4);
                            mul_s(f9, f12, f17);
                            c_lt_s(f15, f9);
                            if (!cond(ctx)) {
                                goto L_004bc5bc;
                            }
                            // 0x004bbb5c
                            charge(ctx, 5);
                            mul_s(f10, f14, f16);
                            mul_s(f9, f11, f17);
                            c_le_s(f10, f9);
                            if (cond(ctx)) {
                                goto L_004bc5bc;
                            }
                            // 0x004bbb70
                            charge(ctx, 4);
                            mul_s(f9, f13, f17);
                            c_lt_s(f10, f9);
                            if (!cond(ctx)) {
                                goto L_004bc5bc;
                            }
                            // 0x004bbb80
                            charge(ctx, 2);
                            v0 = 1;
                        } else {
                            // 0x004bbaf0
                            charge(ctx, 4);
                            mul_s(f9, f10, f17);
                            c_lt_s(f15, f9);
                            if (!cond(ctx)) {
                                goto L_004bc5bc;
                            }
                            // 0x004bbb00
                            charge(ctx, 4);
                            mul_s(f9, f12, f17);
                            c_le_s(f15, f9);
                            if (cond(ctx)) {
                                goto L_004bc5bc;
                            }
                            // 0x004bbb10
                            charge(ctx, 5);
                            mul_s(f10, f14, f16);
                            mul_s(f9, f11, f17);
                            c_lt_s(f10, f9);
                            if (!cond(ctx)) {
                                goto L_004bc5bc;
                            }
                            // 0x004bbb24
                            charge(ctx, 4);
                            mul_s(f9, f13, f17);
                            c_le_s(f10, f9);
                            if (cond(ctx)) {
                                goto L_004bc5bc;
                            }
                            // 0x004bbb34
                            charge(ctx, 2);
                            v0 = 1;
                        }
                        // 0x004bc810 (the shared epilogue, written out on this path)
                        charge(ctx, 5);
                        lwc1(f22, sp, 0x8);
                        lwc1(f21, sp, 0x4);
                        lwc1(f20, sp, 0x0);
                        sp = addiu(sp, 0x20);
                        return;
                    }
                L_004bc5bc:
                    charge(ctx, 26);
                    sub_s(f10, f1, f4);
                    a3 = addiu(sp, 0x14);
                    a2 = addiu(sp, 0x18);
                    sub_s(f6, f6, f3);
                    sub_s(f9, f2, f5);
                    sub_s(f8, f8, f4);
                    sub_s(f11, f0, f3);
                    mula_s(f10, f6);
                    msub_s(f0, f11, f8);
                    sub_s(f7, f7, f5);
                    swc1(f0, sp, 0x10);
                    mula_s(f11, f7);
                    lw(v1, sp, 0x10);
                    msub_s(f0, f9, f6);
                    swc1(f0, a3, 0);
                    mula_s(f9, f8);
                    lw(v0, a3, 0);
                    msub_s(f0, f10, f7);
                    swc1(f0, a2, 0);
                    lwc1(f2, a0, 12);
                    lwc1(f1, a0, 0);
                    lwc1(f0, a1, 0);
                    v0 = v1 ^ v0;
                    sub_s(f4, f1, f2);
                    sub_s(f2, f2, f0);
                    if (i64(v0) < 0) {
                        // 0x004bc7e0
                        charge(ctx, 6);
                        lwc1(f3, a0, 4);
                        lwc1(f1, a0, 16);
                        lwc1(f0, a1, 4);
                        sub_s(f5, f1, f3);
                        sub_s(f3, f3, f0);
                        backedge(ctx);
                    } else {
                        // 0x004bc624
                        charge(ctx, 5);
                        lwc1(f3, a0, 16);
                        lwc1(f1, a0, 4);
                        lwc1(f0, a1, 4);
                        sub_s(f5, f1, f3);
                        sub_s(f3, f3, f0);
                    }
                    // 0x004bc638
                    charge(ctx, 4);
                    lw(v0, a2, 0);
                    v0 = v1 ^ v0;
                    if (i64(v0) < 0) {
                        // 0x004bc7f8
                        charge(ctx, 6);
                        lwc1(f0, a1, 8);
                        lwc1(f12, a0, 8);
                        lwc1(f1, a0, 20);
                        sub_s(f15, f12, f0);
                        sub_s(f16, f1, f12);
                        backedge(ctx);
                    } else {
                        // 0x004bc648
                        charge(ctx, 5);
                        lwc1(f0, a1, 8);
                        lwc1(f12, a0, 20);
                        lwc1(f1, a0, 8);
                        sub_s(f15, f12, f0);
                        sub_s(f16, f1, f12);
                    }
                    // 0x004bc65c
                    charge(ctx, 13);
                    lwc1(f14, a3, 0);
                    lwc1(f12, sp, 0x10);
                    lwc1(f13, a2, 0);
                    mtc1(zero, f1);
                    mula_s(f5, f14);
                    madda_s(f4, f12);
                    madd_s(f0, f16, f13);
                    neg_s(f0, f0);
                    mula_s(f3, f14);
                    madda_s(f2, f12);
                    c_lt_s(f0, f1);
                    madd_s(f12, f15, f13);
                    if (!cond(ctx)) {
                        // 0x004bc734
                        charge(ctx, 3);
                        c_lt_s(f1, f12);
                        if (!cond(ctx)) {
                        L_004bc7d8:
                            charge(ctx, 2);
                            v0 = 0;
                        } else {
                            // 0x004bc740
                            charge(ctx, 3);
                            c_lt_s(f12, f0);
                            if (!cond(ctx)) {
                                goto L_004bc7d8;
                            }
                            // 0x004bc74c
                            charge(ctx, 17);
                            mul_s(f12, f3, f16);
                            adda_s(f1, f12);
                            mul_s(f12, f15, f4);
                            msub_s(f13, f15, f5);
                            adda_s(f1, f12);
                            msub_s(f12, f2, f16);
                            mul_s(f2, f2, f5);
                            adda_s(f1, f2);
                            mul_s(f2, f8, f12);
                            msub_s(f4, f3, f4);
                            adda_s(f1, f2);
                            madd_s(f2, f7, f13);
                            adda_s(f1, f2);
                            madd_s(f3, f6, f4);
                            c_lt_s(f1, f3);
                            if (!cond(ctx)) {
                                goto L_004bc7d8;
                            }
                            // 0x004bc790
                            charge(ctx, 3);
                            c_lt_s(f3, f0);
                            if (!cond(ctx)) {
                                goto L_004bc7d8;
                            }
                            // 0x004bc79c
                            charge(ctx, 9);
                            mul_s(f2, f10, f12);
                            adda_s(f1, f2);
                            madd_s(f2, f9, f13);
                            adda_s(f1, f2);
                            madd_s(f2, f11, f4);
                            neg_s(f2, f2);
                            c_lt_s(f1, f2);
                            if (!cond(ctx)) {
                                goto L_004bc7d8;
                            }
                            // 0x004bc7c0
                            charge(ctx, 4);
                            add_s(f1, f3, f2);
                            c_lt_s(f1, f0);
                            if (!cond(ctx)) {
                                goto L_004bc7d8;
                            }
                            // 0x004bc7d0
                            charge(ctx, 2);
                            v0 = 1;
                        }
                    } else {
                        // 0x004bc690
                        charge(ctx, 3);
                        c_le_s(f1, f12);
                        if (cond(ctx)) {
                            goto L_004bc7d8;
                        }
                        // 0x004bc69c
                        charge(ctx, 3);
                        c_le_s(f12, f0);
                        if (cond(ctx)) {
                            goto L_004bc7d8;
                        }
                        // 0x004bc6a8
                        charge(ctx, 17);
                        mul_s(f12, f3, f16);
                        adda_s(f1, f12);
                        mul_s(f12, f15, f4);
                        msub_s(f13, f15, f5);
                        adda_s(f1, f12);
                        msub_s(f12, f2, f16);
                        mul_s(f2, f2, f5);
                        adda_s(f1, f2);
                        mul_s(f2, f8, f12);
                        msub_s(f4, f3, f4);
                        adda_s(f1, f2);
                        madd_s(f2, f7, f13);
                        adda_s(f1, f2);
                        madd_s(f3, f6, f4);
                        c_le_s(f1, f3);
                        if (cond(ctx)) {
                            goto L_004bc7d8;
                        }
                        // 0x004bc6ec
                        charge(ctx, 3);
                        c_le_s(f3, f0);
                        if (cond(ctx)) {
                            goto L_004bc7d8;
                        }
                        // 0x004bc6f8
                        charge(ctx, 9);
                        mul_s(f2, f10, f12);
                        adda_s(f1, f2);
                        madd_s(f2, f9, f13);
                        adda_s(f1, f2);
                        madd_s(f2, f11, f4);
                        neg_s(f2, f2);
                        c_le_s(f1, f2);
                        if (cond(ctx)) {
                            goto L_004bc7d8;
                        }
                        // 0x004bc71c
                        charge(ctx, 4);
                        add_s(f1, f3, f2);
                        c_le_s(f1, f0);
                        if (cond(ctx)) {
                            goto L_004bc7d8;
                        }
                        // 0x004bc72c
                        charge(ctx, 2);
                        v0 = 1;
                    }
                }
            }
        }
    }
    // 0x004bc810 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4BF6E0 [rtfsFileSystemInit] -- initialises a file system: its name, its files, its device name; 1 or an error code
// ($a0 = the file system, $a1 = the file count, $a2 = the name, $a3 = the device) 2 when the manager is full, 6 when
// the name is taken (sub_4BFDE0); the name copied to +80; each file (from +20) marked idle; the device stored
// (sub_4BFA70); status 2.
// 0x004BF6E0 sub_4BF6E0 -- 252 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4BF6E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004bf6e0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    s1 = a3;
    s0 = a2;
    jal(ctx, 0x4BF704u, gen::fn_sub_4BFC20_004bfc20);
    if (v0 == 0) {
        // 0x004bf714
        charge(ctx, 2);
        v0 = 2;
        goto L_004bf7c0;
    }
    // 0x004bf71c
    charge(ctx, 4);
    a0 = s0;
    jal(ctx, 0x4BF71Cu, gen::fn_sub_4BFDE0_004bfde0);
    if (v0 != 0) {
        // 0x004bf72c
        charge(ctx, 2);
        v0 = 6;
        goto L_004bf7c0;
    }
    // 0x004bf734
    charge(ctx, 10);
    v0 = 0x960000;
    a1 = s0;
    lw(v0, v0, 316);  // 0x96013C (the engine's strcpy slot)
    a0 = addiu(s3, 80);
    jalr(ctx, 0x4BF740u, v0.u());
    sw(s2, s3, rtfs::kMaxFiles);
    at = slt(0, s2);
    s0 = 0;
    sw(zero, s3, rtfs::kWord16);
    if (at != 0) {
        for (;;) {
            // 0x004bf75c
            charge(ctx, 11);
            lw(v0, s3, rtfs::kGetFile);
            a0 = s3;
            a1 = s0;
            jalr(ctx, 0x4BF764u, v0.u());
            v1 = 1;
            s0 = addiu(s0, 1);
            sw(v1, v0, 56);
            lw(a0, s3, rtfs::kWord16);
            v1 = slt(s0, s2);
            sw(a0, v0, 48);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004bf788
    charge(ctx, 7);
    a1 = s1;
    a0 = s3;
    link(ctx, 0x4BF790u);  // $ra first: the delay slot below depends on it
    sw(zero, s3, rtfs::kDevice);
    call(ctx, gen::fn_sub_4BFA70_004bfa70);
    v1 = 1;
    if (v0 == v1) {
        // 0x004bf7ac
        charge(ctx, 5);
        v0 = v1;
        v1 = 2;
        sw(v1, s3, rtfs::kStatus);
        sw(zero, s3, rtfs::kRegister);
        sw(zero, s3, rtfs::kUnregister);
    L_004bf7c0:
        charge(ctx, 1);
        ld(ra, sp, 0x40);
    } else {
        // 0x004bf7a4
        charge(ctx, 2);
        ld(ra, sp, 0x40);
    }
    // 0x004bf7c4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}


// sub_4BF7E0 [rtfsSkipDevicePrefix] -- a path after its 'device:' prefix (the first ':' + 1), or the path itself
// 0x004BF7E0 sub_4BF7E0 -- 148 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4BF7E0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004bf7e0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s0 = 0x960000;
    s0 = addiu(s0, 356);  // &0x960164 (the engine's strlen slot)
    lw(v0, s0, 0);  // 0x960164 (the engine's strlen slot)
    s1 = 0;
    jalr(ctx, 0x4BF804u, v0.u());
    at = slt(0, v0);
    if (at != 0) {
        for (;;) {
            // 0x004bf818
            charge(ctx, 5);
            v1 = addu(s2, s1);
            v0 = 58;
            lb(v1, v1, 0);
            if (v1 == v0) {
                goto L_004bf82c_2;
            }
            // 0x004bf838
            charge(ctx, 7);
            lw(v0, s0, 0);
            a0 = s2;
            s1 = addiu(s1, 1);
            jalr(ctx, 0x4BF840u, v0.u());
            v0 = slt(s1, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004bf854
        charge(ctx, 1);
    }
    // 0x004bf858 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = s2;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_004bf82c_2:
    charge(ctx, 3);
    v0 = addiu(s1, 1);
    s2 = addu(s2, v0);
    // 0x004bf858 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = s2;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_4BF9E0 [rtfsFileEof] -- a file's end-of-file test: position -1 or position >= length
// 0x004BF9E0 sub_4BF9E0 -- 44 bytes; leaf frame (no stack)
void sub_4BF9E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x004bf9e0
    enter(ctx, 4);  // entry check point + this block's cycles
    ld(v1, a0, rtfile::kPosition);
    v0 = si(-1);
    if (v1 != v0) {
        // 0x004bf9f8
        charge(ctx, 3);
        ld(v0, a0, rtfile::kLength);
        v0 = slt(v1, v0);
        v0 = v0 ^ 0x1;
    } else {
        // 0x004bf9f0
        charge(ctx, 2);
        v0 = 1;
    }
    // 0x004bfa04 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_4BFA10 [rtfsNotify] -- calls the file system's register (1) or unregister (2) callback with its name
// 0x004BFA10 sub_4BFA10 -- 96 bytes; frame 0x10: ra sp+0x0
void sub_4BFA10(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004bfa10
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 2;
    sd(ra, sp, 0x0);
    if (a1 == v1) {
        // 0x004bfa50
        charge(ctx, 3);
        lw(v1, a0, rtfs::kUnregister);
        if (v1 != 0) {
            // 0x004bfa5c
            charge(ctx, 2);
            a0 = addiu(a0, 80);
            jalr(ctx, 0x4BFA5Cu, v1.u());
        }
    L_004bfa64:
        charge(ctx, 1);
        ld(ra, sp, 0x0);
    } else {
        // 0x004bfa20
        charge(ctx, 3);
        v1 = 1;
        if (a1 == v1) {
            // 0x004bfa34
            charge(ctx, 3);
            lw(v1, a0, rtfs::kRegister);
            if (v1 != 0) {
                // 0x004bfa40
                charge(ctx, 4);
                a0 = addiu(a0, 80);
                jalr(ctx, 0x4BFA40u, v1.u());
            }
            goto L_004bfa64;
        }
        // 0x004bfa2c
        charge(ctx, 2);
        ld(ra, sp, 0x0);
    }
    // 0x004bfa68 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}


// sub_4BFA70 [rtfsSetDevice] -- a file system's device name: 7 when the device is taken (sub_4C0070), else a heap copy; 1
// 0x004BFA70 sub_4BFA70 -- 168 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4BFA70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004bfa70
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a0 = s0;
    jal(ctx, 0x4BFA88u, gen::fn_sub_4C0070_004c0070);
    if (v0 == 0) {
        // 0x004bfaa0
        charge(ctx, 3);
        lw(a0, s1, rtfs::kDevice);
        if (a0 != 0) {
            // 0x004bfaac
            charge(ctx, 4);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C (RwFree slot)
            jalr(ctx, 0x4BFAB4u, v0.u());
        }
        // 0x004bfabc
        charge(ctx, 18);
        v0 = 0x960000;
        lw(v0, v0, 356);  // 0x960164 (the engine's strlen slot)
        a0 = s0;
        jalr(ctx, 0x4BFAC4u, v0.u());
        a0 = addiu(v0, 1);
        v0 = 0x40000;
        a1 = v0 | 0x1BE;
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
        jalr(ctx, 0x4BFAE0u, v0.u());
        sw(v0, s1, rtfs::kDevice);
        v0 = 0x960000;
        lw(a0, s1, rtfs::kDevice);
        lw(v0, v0, 316);  // 0x96013C (the engine's strcpy slot)
        a1 = s0;
        jalr(ctx, 0x4BFAF8u, v0.u());
        v0 = 1;
    } else {
        // 0x004bfa98
        charge(ctx, 2);
        v0 = 7;
    }
    // 0x004bfb04 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// sub_4BFB20 [rtfsFileComplete] -- ends a file operation: idle again, and the completion callback with the result or position
// 0x004BFB20 sub_4BFB20 -- 132 bytes; frame 0x10: ra sp+0x0
void sub_4BFB20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004bfb20
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x004bfb2c
        charge(ctx, 3);
        lw(v1, a0, rtfile::kOwnerWord);
        if (v1 == 0) {
            goto L_004bfb98;
        }
        // 0x004bfb38
        charge(ctx, 4);
        lw(a3, a0, rtfile::kState);
        v1 = 1;
        if (a3 != v1) {
            // 0x004bfb48
            charge(ctx, 3);
            lw(v1, a0, rtfile::kCallBack);
            if (v1 == 0) {
                goto L_004bfb8c;
            }
            // 0x004bfb54
            charge(ctx, 3);
            v0 = 4;
            if (a3 != v0) {
                // 0x004bfb68
                charge(ctx, 1);
                lw(a1, a0, rtfile::kResult);
            } else {
                // 0x004bfb60
                charge(ctx, 2);
                lw(a1, a0, rtfile::kPosition);
            }
            // 0x004bfb6c
            charge(ctx, 6);
            v0 = 1;
            sw(v0, a0, rtfile::kState);
            lw(t0, a0, rtfile::kCallBackData);
            lw(v0, a0, rtfile::kCallBack);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x4BFB7Cu);  // $ra = the return address
            lw(a2, a0, rtfile::kStatus);
            call_ptr(ctx, jt);
            goto L_004bfb84;
        }
    L_004bfb8c:
        charge(ctx, 3);
        v1 = 1;
        sw(v1, a0, rtfile::kState);
        backedge(ctx);
    L_004bfb84:
        charge(ctx, 2);
        ld(ra, sp, 0x0);
        // 0x004bfb9c (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
L_004bfb98:
    charge(ctx, 1);
    ld(ra, sp, 0x0);
    // 0x004bfb9c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}


// sub_4BFC20 [rtfsHasRoom] -- 1 when another file system can be registered; else the error callback (5) and 0
// 0x004BFC20 sub_4BFC20 -- 96 bytes; frame 0x10: ra sp+0x0
void sub_4BFC20(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004bfc20
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x960000;
    sd(ra, sp, 0x0);
    lw(v1, v0, -236);  // 0x95FF14 (the RtFS maximum file-system count)
    if (i64(v1) > 0) {
        // 0x004bfc38
        charge(ctx, 6);
        v0 = 0x960000;
        lw(v0, v0, -232);  // 0x95FF18 (the RtFS registered count)
        v0 = addiu(v0, 1);
        at = slt(v1, v0);
        if (at == 0) {
            goto L_004bfc70;
        }
        // 0x004bfc50
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, -220);  // 0x95FF24 (the RtFS error callback)
        if (v0 != 0) {
            // 0x004bfc60
            charge(ctx, 2);
            a0 = 5;
            jalr(ctx, 0x4BFC60u, v0.u());
        }
        // 0x004bfc68
        charge(ctx, 2);
        v0 = 0;
        // 0x004bfc74 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
L_004bfc70:
    charge(ctx, 1);
    v0 = 1;
    // 0x004bfc74 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}


// sub_4BFC80 [RtFSManagerRegister] -- registers a file system: room and a free name required; its register callback; pushed on the list
// Returns 1, or 0.
// 0x004BFC80 sub_4BFC80 -- 200 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4BFC80(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004bfc80
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, v0, -236);  // 0x95FF14 (the RtFS maximum file-system count)
    s0 = a0;
    if (i64(v1) > 0) {
        // 0x004bfc9c
        charge(ctx, 6);
        v0 = 0x960000;
        lw(v0, v0, -232);  // 0x95FF18 (the RtFS registered count)
        v0 = addiu(v0, 1);
        at = slt(v1, v0);
        if (at == 0) {
            goto L_004bfce0;
        }
        // 0x004bfcb4
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, -220);  // 0x95FF24 (the RtFS error callback)
        if (v0 != 0) {
            // 0x004bfcc4
            charge(ctx, 2);
            a0 = 5;
            jalr(ctx, 0x4BFCC4u, v0.u());
        }
        // 0x004bfccc
        charge(ctx, 1);
        v0 = 0;
        goto L_004bfcd0;
    }
L_004bfce0:
    charge(ctx, 2);
    v0 = 1;
    backedge(ctx);
L_004bfcd0:
    charge(ctx, 2);
    if (v0 != 0) {
        // 0x004bfce8
        charge(ctx, 4);
        a0 = addiu(s0, 80);
        jal(ctx, 0x4BFCE8u, gen::fn_sub_4BFD50_004bfd50);
        if (v0 == 0) {
            // 0x004bfd00
            charge(ctx, 14);
            a0 = s0;
            a1 = 1;
            jal(ctx, 0x4BFD04u, gen::fn_sub_4BFA10_004bfa10);
            v0 = 0x960000;
            a0 = 0x960000;
            lw(a2, v0, -240);  // 0x95FF10 (the RtFS list of registered file systems)
            a1 = 0x960000;
            v1 = 0x960000;
            sw(a2, s0, rtfs::kNext);
            v0 = 1;
            lw(a0, a0, -232);  // 0x95FF18 (the RtFS registered count)
            sw(s0, a1, -240);  // 0x95FF10 (the RtFS list of registered file systems)
            a0 = addiu(a0, 1);
            sw(a0, v1, -232);  // 0x95FF18 (the RtFS registered count)
        } else {
            // 0x004bfcf8
            charge(ctx, 2);
            v0 = 0;
        }
    } else {
        // 0x004bfcd8
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004bfd38 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4BFD50 [RtFSManagerGetFileSystemFromName] -- the registered file system with that name (strcmp), else the error callback (6) and 0
// 0x004BFD50 sub_4BFD50 -- 140 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4BFD50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004bfd50
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 0x960000;
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, v0, -240);  // 0x95FF10 (the RtFS list of registered file systems)
    s2 = a0;
    if (s1 != 0) {
        // 0x004bfd74
        charge(ctx, 2);
        s0 = 0x960000;
        s0 = addiu(s0, 344);  // &0x960158 (the engine's strcmp slot)
        for (;;) {
            // 0x004bfd7c
            charge(ctx, 6);
            lw(v0, s0, 0);
            a0 = addiu(s1, 80);
            a1 = s2;
            jalr(ctx, 0x4BFD84u, v0.u());
            if (v0 == 0) {
                goto L_004bfd94_3;
            }
            // 0x004bfd9c
            charge(ctx, 3);
            lw(s1, s1, rtfs::kNext);
            if (s1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004bfda8
    charge(ctx, 4);
    v0 = 0x960000;
    lw(v0, v0, -220);  // 0x95FF24 (the RtFS error callback)
    if (v0 != 0) {
        // 0x004bfdb8
        charge(ctx, 2);
        a0 = 6;
        jalr(ctx, 0x4BFDB8u, v0.u());
    }
    // 0x004bfdc0
    charge(ctx, 1);
    v0 = 0;
    // 0x004bfdc4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_004bfd94_3:
    charge(ctx, 2);
    v0 = s1;
    // 0x004bfdc4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_4BFDE0 [rtfsNameTaken] -- 1 (and the error callback 7) when a file system of that name is registered
// 0x004BFDE0 sub_4BFDE0 -- 184 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4BFDE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004bfde0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 0x960000;
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, v0, -240);  // 0x95FF10 (the RtFS list of registered file systems)
    s2 = a0;
    if (s1 != 0) {
        // 0x004bfe04
        charge(ctx, 2);
        s0 = 0x960000;
        s0 = addiu(s0, 344);  // &0x960158 (the engine's strcmp slot)
        for (;;) {
            // 0x004bfe0c
            charge(ctx, 6);
            lw(v0, s0, 0);
            a0 = addiu(s1, 80);
            a1 = s2;
            jalr(ctx, 0x4BFE14u, v0.u());
            if (v0 == 0) {
                goto L_004bfe24_3;
            }
            // 0x004bfe2c
            charge(ctx, 3);
            lw(s1, s1, 0);
            if (s1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004bfe38
    charge(ctx, 4);
    v0 = 0x960000;
    lw(v0, v0, -220);  // 0x95FF24 (the RtFS error callback)
    if (v0 != 0) {
        // 0x004bfe48
        charge(ctx, 2);
        a0 = 6;
        jalr(ctx, 0x4BFE48u, v0.u());
    }
    // 0x004bfe50
    charge(ctx, 1);
    s1 = 0;
L_004bfe54:
    charge(ctx, 2);
    if (s1 == 0) {
        // 0x004bfe7c
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004bfe5c
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, -220);  // 0x95FF24 (the RtFS error callback)
        if (v0 != 0) {
            // 0x004bfe6c
            charge(ctx, 2);
            a0 = 7;
            jalr(ctx, 0x4BFE6Cu, v0.u());
        }
        // 0x004bfe74
        charge(ctx, 2);
        v0 = 1;
    }
    // 0x004bfe80 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_004bfe24_3:
    charge(ctx, 2);
    goto L_004bfe54;
}


// sceLibgcc32GetErxEntries_1 -- returns the address of the RtFS list (0x95FF10)
// 0x004C0060 sceLibgcc32GetErxEntries_1 -- 12 bytes; leaf frame (no stack)
void sceLibgcc32GetErxEntries_1(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x004c0060
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x960000;
    v0 = addiu(v0, -240);  // &0x95FF10 (the RtFS list of registered file systems)
}


// sub_4C0070 [rtfsFindDevice] -- the registered file system whose device name matches (case-insensitive), or 0
// 0x004C0070 sub_4C0070 -- 116 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C0070(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c0070
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 0x960000;
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, v0, -240);  // 0x95FF10 (the RtFS list of registered file systems)
    s2 = a0;
    if (s1 != 0) {
        // 0x004c0094
        charge(ctx, 2);
        s0 = 0x960000;
        s0 = addiu(s0, 352);  // &0x960160 (the engine's case-insensitive compare slot)
        for (;;) {
            // 0x004c009c
            charge(ctx, 6);
            lw(a1, s1, rtfs::kDevice);
            lw(v0, s0, 0);
            a0 = s2;
            jalr(ctx, 0x4C00A4u, v0.u());
            if (v0 == 0) {
                goto L_004c00b4_3;
            }
            // 0x004c00bc
            charge(ctx, 3);
            lw(s1, s1, rtfs::kNext);
            if (s1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004c00c8
    charge(ctx, 1);
    v0 = 0;
    // 0x004c00cc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_004c00b4_3:
    charge(ctx, 2);
    v0 = s1;
    // 0x004c00cc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_4C0230 [rtfsSetCallBack] -- stores the manager's callback word (gp 0x7CE8BC)
// 0x004C0230 sub_4C0230 -- 8 bytes; leaf frame (no stack)
void sub_4C0230(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, gp{ctx, 28};
    // 0x004c0230
    enter(ctx, 2);  // entry check point + this block's cycles
    sw(a0, gp, -17460);  // 0x7CE8BC (the RtFS manager's callback word)
}


// sub_4C03D0 [rtfsFread] -- fread through RtFS: the file system's read (fs +48) of size x count bytes, / size
// ($a0 = the buffer, $a1 = the size, $a2 = the count, $a3 = the file)
// 0x004C03D0 sub_4C03D0 -- 72 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C03D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c03d0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = a0;
    sd(ra, sp, 0x10);
    a0 = a3;
    sq(s0, sp, 0x0);
    s0 = a1;
    mult(a2, s0, a2);
    a1 = v0;
    lw(v0, a3, rtfile::kFs);
    lw(v0, v0, rtfs::kFileRead);
    jalr(ctx, 0x4C03F8u, v0.u());
    divu(v0, s0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    mflo(v0);
    sp = addiu(sp, 0x20);
}


// sub_4C0420 [rtfsFwrite] -- fwrite through RtFS: the file system's write (fs +52) of size x count bytes, / size
// 0x004C0420 sub_4C0420 -- 72 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C0420(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c0420
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = a0;
    sd(ra, sp, 0x10);
    a0 = a3;
    sq(s0, sp, 0x0);
    s0 = a1;
    mult(a2, s0, a2);
    a1 = v0;
    lw(v0, a3, rtfile::kFs);
    lw(v0, v0, rtfs::kFileWrite);
    jalr(ctx, 0x4C0448u, v0.u());
    divu(v0, s0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    mflo(v0);
    sp = addiu(sp, 0x20);
}


// sub_4C0470 [rtfsFseek] -- fseek through RtFS: whence 0 / 1 / 2 -> the seek operation (fs +56) with mode 1 / 2 / 3; 0, or -1
// A file with a completion callback is marked busy (state 4, status 3) first.
// 0x004C0470 sub_4C0470 -- 212 bytes; frame 0x40: ra sp+0x0
void sub_4C0470(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c0470
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x0);
    lw(v1, a0, rtfile::kFs);
    lw(v0, a0, rtfile::kOwnerWord);
    t0 = addiu(v1, 40);
    if (v0 != 0) {
        // 0x004c0524
        charge(ctx, 5);
        v1 = 4;
        v0 = 3;
        sw(v1, a0, rtfile::kState);
        sw(v0, a0, rtfile::kStatus);
        backedge(ctx);
    }
    // 0x004c0488
    charge(ctx, 2);
    if (a2 == 0) {
        // 0x004c04f4
        charge(ctx, 7);
        lw(v0, t0, 16);
        a2 = dsll32(a1, 0);
        a1 = a0;
        a2 = dsra32(a2, 0);
        a0 = addiu(sp, 0x10);
        a3 = 1;
        jalr(ctx, 0x4C0508u, v0.u());
    L_004c0510:
        charge(ctx, 1);
        v0 = 0;
    L_004c0514:
        charge(ctx, 2);
        ld(ra, sp, 0x0);
    } else {
        // 0x004c0490
        charge(ctx, 3);
        a3 = 2;
        if (a2 == a3) {
            // 0x004c04d0
            charge(ctx, 9);
            lw(v0, t0, 16);
            a2 = dsll32(a1, 0);
            a1 = a0;
            a2 = dsra32(a2, 0);
            a0 = addiu(sp, 0x20);
            a3 = 3;
            jalr(ctx, 0x4C04E4u, v0.u());
            goto L_004c0510;
        }
        // 0x004c049c
        charge(ctx, 3);
        v0 = 1;
        if (a2 == v0) {
            // 0x004c04b0
            charge(ctx, 8);
            lw(v0, t0, 16);
            a2 = dsll32(a1, 0);
            a1 = a0;
            a2 = dsra32(a2, 0);
            a0 = addiu(sp, 0x30);
            jalr(ctx, 0x4C04C0u, v0.u());
            v0 = 0;
            goto L_004c0514;
        }
        // 0x004c04a8
        charge(ctx, 2);
        v0 = si(-1);
        // 0x004c051c
        charge(ctx, 2);
        // 0x004c0538
        charge(ctx, 1);
        ld(ra, sp, 0x0);
    }
    // 0x004c053c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x40);
}


// sub_4C06B0 [rtfsFeof] -- feof through RtFS: the file system's end-of-file operation (fs +68)
// 0x004C06B0 sub_4C06B0 -- 16 bytes; leaf frame (no stack)
void sub_4C06B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x004c06b0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, rtfile::kFs);
    lw(v0, v0, rtfs::kFileEof);
    tail(ctx, v0.u());  // jr: the target's entry point
}


// sub_4C0830 [rtfsGenericGetFile] -- the generic file system's file $a1 (112-byte records at +88), or 0 out of range
// 0x004C0830 sub_4C0830 -- 52 bytes; leaf frame (no stack)
void sub_4C0830(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x004c0830
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, rtfs::kMaxFiles);
    at = sltu(a1, v0);
    if (at == 0) {
        // 0x004c0858
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004c0840
        charge(ctx, 6);
        lw(v0, a0, rtfs::kFiles);
        v1 = sll(a1, 3);
        v1 = subu(v1, a1);
        v1 = sll(v1, 4);
        v0 = addu(v0, v1);
    }
    // 0x004c085c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_4C0870 [rtfsGenericGetDevice] -- the generic file system's device name ('host:')
// 0x004C0870 sub_4C0870 -- 8 bytes; leaf frame (no stack)
void sub_4C0870(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, gp{ctx, 28};
    // 0x004c0870
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = addiu(gp, -20424);  // "host:"
}


// sub_4C0880 [rtfsGenericClose] -- frees the generic file system's file array (+88)
// 0x004C0880 sub_4C0880 -- 20 bytes; leaf frame (no stack)
void sub_4C0880(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x004c0880
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x960000;
    lw(a0, a0, rtfs::kFiles);
    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
    tail(ctx, v0.u());  // jr: the target's entry point
}


// sub_4C0F60 [rtfsGenericSync] -- file status = 1; returns 1
// 0x004C0F60 sub_4C0F60 -- 12 bytes; leaf frame (no stack)
void sub_4C0F60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x004c0f60
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 1;
    sw(v0, a0, rtfile::kStatus);
}


// sub_4C0FD0 [rtfsGenericCreate] -- creates a generic ('host:') file system: 92-byte record, its operations, $a0 files with buffers
// ($a0 = files, $a1 = the buffer area, $a2 = the buffer size, $a3 = the device, $t0 = the name) 0 when the name is
// taken; the operations table (+20..+76); the 112-byte file records (RwCalloc) each owned by it with its slice of
// the buffer area; then the init (sub_4BF6E0); a failed init frees both. Returns the file system.
// 0x004C0FD0 sub_4C0FD0 -- 760 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C0FD0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004c0fd0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    s3 = a2;
    sq(s1, sp, 0x10);
    s2 = a3;
    s1 = t0;
    sq(s0, sp, 0x0);
    a0 = s1;
    jal(ctx, 0x4C1004u, gen::fn_sub_4BFD50_004bfd50);
    if (v0 == 0) {
        // 0x004c101c
        charge(ctx, 58);
        v0 = 0x40000;
        a1 = v0 | 0x1BE;
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
        a0 = 92;
        jalr(ctx, 0x4C102Cu, v0.u());
        v1 = 0x4C0000;
        s0 = v0;
        v1 = addiu(v1, 2096);  // &sub_4C0830
        a0 = s5;
        sw(v1, v0, rtfs::kGetFile);
        v1 = 0x4C0000;
        v1 = addiu(v1, 2176);  // &sub_4C0880
        sw(v1, v0, rtfs::kClose);
        v1 = 0x4C0000;
        v1 = addiu(v1, 2160);  // &sub_4C0870
        sw(v1, v0, rtfs::kGetHandle);
        v1 = 0x4C0000;
        v1 = addiu(v1, 2208);  // &sub_4C08A0
        sw(v1, v0, rtfs::kFileOps);
        v1 = 0x4C0000;
        v1 = addiu(v1, 2672);  // &sub_4C0A70
        sw(v1, v0, 44);
        v1 = 0x4C0000;
        v1 = addiu(v1, 2688);  // &sub_4C0A80
        sw(v1, v0, rtfs::kFileRead);
        v1 = 0x4C0000;
        v1 = addiu(v1, 3152);  // &sub_4C0C50
        sw(v1, v0, rtfs::kFileWrite);
        v1 = 0x4C0000;
        v1 = addiu(v1, 3312);  // &sub_4C0CF0
        sw(v1, v0, 56);
        v1 = 0x4C0000;
        v1 = addiu(v1, 3696);  // &sub_4C0E70
        sw(v1, v0, 60);
        v1 = 0x4C0000;
        v1 = addiu(v1, 3936);  // &sub_4C0F60
        sw(v1, v0, 64);
        v1 = 0x4C0000;
        v1 = addiu(v1, -1568);  // &sub_4BF9E0
        sw(v1, v0, rtfs::kFileEof);
        v1 = 0x4C0000;
        v1 = addiu(v1, 3952);  // &sub_4C0F70
        sw(v1, v0, 72);
        v1 = 0x4C0000;
        v1 = addiu(v1, 4032);  // &sub_4C0FC0
        sw(v1, v0, 76);
        v0 = 0x40000;
        a2 = v0 | 0x1BE;
        v0 = 0x960000;
        lw(v0, v0, 388);  // 0x960184 (RwCalloc slot)
        a1 = 112;
        jalr(ctx, 0x4C10E8u, v0.u());
        sw(v0, s0, rtfs::kFiles);
        at = slt(0, s5);
        lw(t4, s0, rtfs::kFiles);
        t5 = 0;
        if (at != 0) {
            // 0x004c1104
            charge(ctx, 3);
            at = slti(s5, 9);
            t1 = addiu(s5, -8);
            if (at == 0) {
                // 0x004c1110
                charge(ctx, 3);
                at = slt(s5, 0);
                v0 = 0;
                if (at == 0) {
                    // 0x004c111c
                    charge(ctx, 5);
                    at = 0x7FFF0000;
                    at = at | 0xFFFF;
                    at = slt(s5, at);
                    if (at != 0) {
                        // 0x004c1130
                        charge(ctx, 1);
                        v0 = 1;
                    }
                }
                // 0x004c1134
                charge(ctx, 2);
                if (v0 != 0) {
                    // 0x004c113c
                    charge(ctx, 9);
                    a3 = sll(s3, 1);
                    t0 = sll(s3, 3);
                    a2 = addu(a3, s3);
                    a1 = sll(s3, 2);
                    t3 = t4;
                    t2 = 0;
                    a0 = addu(a1, s3);
                    v1 = sll(a2, 1);
                    v0 = subu(t0, s3);
                    for (;;) {
                        // 0x004c1160
                        charge(ctx, 44);
                        sw(s0, t3, rtfile::kFs);
                        t6 = addu(s4, t2);
                        sw(t6, t3, rtfile::kBuffer);
                        t5 = addiu(t5, 8);
                        t6 = addu(t2, s3);
                        sw(s3, t3, rtfile::kBufferSize);
                        t7 = addu(s4, t6);
                        sw(s0, t3, 192);
                        sw(t7, t3, 216);
                        t6 = addu(t2, a3);
                        sw(s3, t3, 220);
                        t7 = addu(s4, t6);
                        sw(s0, t3, 304);
                        t6 = addu(t2, a2);
                        sw(t7, t3, 328);
                        t8 = addu(s4, t6);
                        sw(s3, t3, 332);
                        t6 = addu(t2, a1);
                        sw(s0, t3, 416);
                        t7 = addu(s4, t6);
                        sw(t8, t3, 440);
                        t6 = addu(t2, a0);
                        sw(s3, t3, 444);
                        t9 = addu(s4, t6);
                        sw(s0, t3, 528);
                        t6 = addu(t2, v1);
                        sw(t7, t3, 552);
                        t8 = addu(s4, t6);
                        sw(s3, t3, 556);
                        t6 = addu(t2, v0);
                        sw(s0, t3, 640);
                        t7 = addu(s4, t6);
                        sw(t9, t3, 664);
                        t6 = slt(t5, t1);
                        sw(s3, t3, 668);
                        t2 = addu(t2, t0);
                        sw(s0, t3, 752);
                        sw(t8, t3, 776);
                        sw(s3, t3, 780);
                        sw(s0, t3, 864);
                        sw(t7, t3, 888);
                        sw(s3, t3, 892);
                        t3 = addiu(t3, 896);
                        if (t6 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
            }
            // 0x004c1210
            charge(ctx, 3);
            at = slt(t5, s5);
            if (at != 0) {
                // 0x004c121c
                charge(ctx, 5);
                v0 = sll(t5, 3);
                v0 = subu(v0, t5);
                v0 = sll(v0, 4);
                a0 = addu(t4, v0);
                mult(v1, t5, s3);
                for (;;) {
                    // 0x004c1230
                    charge(ctx, 9);
                    v0 = addu(s4, v1);
                    sw(s0, a0, 80);
                    sw(v0, a0, 104);
                    t5 = addiu(t5, 1);
                    sw(s3, a0, 108);
                    v0 = slt(t5, s5);
                    v1 = addu(v1, s3);
                    a0 = addiu(a0, 112);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004c1254
                charge(ctx, 1);
            }
        }
        // 0x004c1258
        charge(ctx, 8);
        a1 = s5;
        a2 = s1;
        a3 = s2;
        a0 = s0;
        jal(ctx, 0x4C1264u, gen::fn_sub_4BF6E0_004bf6e0);
        v1 = 1;
        if (v0 != v1) {
            // 0x004c1280
            charge(ctx, 9);
            s1 = 0x960000;
            s1 = addiu(s1, 380);  // &0x96017C (RwFree slot)
            lw(v0, s1, 0);  // 0x96017C (RwFree slot)
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x4C128Cu);  // $ra = the return address
            lw(a0, s0, rtfs::kFiles);
            call_ptr(ctx, jt);
            lw(v0, s1, 0);  // 0x96017C (RwFree slot)
            a0 = s0;
            jalr(ctx, 0x4C1298u, v0.u());
            v0 = 0;
        } else {
            // 0x004c1278
            charge(ctx, 2);
            v0 = s0;
        }
    } else {
        // 0x004c1014
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004c12a4 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}


// sub_4C1BC0 [moduleOpenCount] -- counts a module open (gp 0x7CE8CC); returns $a0
// 0x004C1BC0 sub_4C1BC0 -- 20 bytes; leaf frame (no stack)
void sub_4C1BC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x004c1bc0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, gp, -17444);  // 0x7CE8CC (a module's open count)
    v0 = a0;
    v1 = addiu(v1, 1);
    sw(v1, gp, -17444);  // 0x7CE8CC (a module's open count)
}


// sub_4C1BE0 [moduleCloseCount] -- counts the module's close; returns $a0
// 0x004C1BE0 sub_4C1BE0 -- 20 bytes; leaf frame (no stack)
void sub_4C1BE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x004c1be0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, gp, -17444);  // 0x7CE8CC (a module's open count)
    v0 = a0;
    v1 = addiu(v1, -1);
    sw(v1, gp, -17444);  // 0x7CE8CC (a module's open count)
}


// sub_4C1C00 [errorModuleOpen] -- the error module's open: its offset, the error cleared {0, 0x80000000}, counted; returns $a0
// 0x004C1C00 sub_4C1C00 -- 48 bytes; leaf frame (no stack)
void sub_4C1C00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x004c1c00
    enter(ctx, 12);  // entry check point + this block's cycles
    v1 = 0x960000;
    v0 = a0;
    v1 = addiu(v1, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    sw(a1, gp, -17440);  // 0x7CE8D0 (the error module offset)
    a0 = addu(v1, a1);
    lw(a1, gp, -17436);  // 0x7CE8D4 (the error module's open count)
    v1 = lui(0x8000);
    sw(zero, a0, 0);
    sw(v1, a0, 4);
    v1 = addiu(a1, 1);
    sw(v1, gp, -17436);  // 0x7CE8D4 (the error module's open count)
}


// sub_4C1C30 [errorModuleClose] -- the error module's close: counts down; returns $a0
// 0x004C1C30 sub_4C1C30 -- 20 bytes; leaf frame (no stack)
void sub_4C1C30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x004c1c30
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v1, gp, -17436);  // 0x7CE8D4 (the error module's open count)
    v0 = a0;
    v1 = addiu(v1, -1);
    sw(v1, gp, -17436);  // 0x7CE8D4 (the error module's open count)
}


// sub_4C1CD0 [RwErrorGet] -- copies the last error {plugin, code} to $a0 and clears it to {0, 0x80000000}; returns $a0
// 0x004C1CD0 sub_4C1CD0 -- 60 bytes; leaf frame (no stack)
void sub_4C1CD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x004c1cd0
    enter(ctx, 15);  // entry check point + this block's cycles
    lw(a1, gp, -17440);  // 0x7CE8D0 (the error module offset)
    a2 = 0x960000;
    a2 = addiu(a2, 112);  // &0x960070 (the RW engine instance; + a module offset = that module's data)
    v0 = a0;
    v1 = lui(0x8000);
    a1 = addu(a2, a1);
    lwc1(f1, a1, 0);
    lwc1(f0, a1, 4);
    swc1(f1, a0, 0);
    swc1(f0, a0, 4);
    lw(a0, gp, -17440);  // 0x7CE8D0 (the error module offset)
    a0 = addu(a2, a0);
    sw(zero, a0, 0);
    sw(v1, a0, 4);
}


// sub_4C1F70 [slistGetNewEntries] -- reserves n entries at an sList's end: grows it by n + a quarter when full (RwRealloc)
// Returns the first new entry; when the reallocation fails, error 0x80000013 with the size and 0.
// 0x004C1F70 sub_4C1F70 -- 264 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C1F70(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004c1f70
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, slist::kCount);
    s0 = a1;
    lw(v1, a0, slist::kCapacity);
    v0 = addu(v0, s0);
    at = slt(v0, v1);
    s1 = a0;
    if (at == 0) {
        // 0x004c1fbc: full: RwRealloc(data, entry size x (capacity + capacity / 4 + n))
        charge(ctx, 2);
        a0 = sra(v1, 2);
        if (i64(v1) < 0) {
            // 0x004c1fc4
            charge(ctx, 2);
            v0 = addiu(v1, 3);
            a0 = sra(v0, 2);
        }
        // 0x004c1fcc
        charge(ctx, 10);
        lw(v0, s1, slist::kEntrySize);
        v1 = addu(v1, s0);
        v1 = addu(a0, v1);
        mult(a1, v0, v1);
        v0 = 0x960000;
        lw(v0, v0, 384);  // 0x960180 (RwRealloc slot)
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x4C1FE4u);  // $ra = the return address
        lw(a0, s1, slist::kData);
        call_ptr(ctx, jt);
        if (v0 != 0) {
            // 0x004c1ff4
            charge(ctx, 4);
            sw(v0, s1, slist::kData);
            lw(a0, s1, slist::kCapacity);
            v1 = sra(a0, 2);
            if (i64(a0) < 0) {
                // 0x004c2004
                charge(ctx, 2);
                v0 = addiu(a0, 3);
                v1 = sra(v0, 2);
            }
            // 0x004c200c
            charge(ctx, 4);
            v0 = addu(a0, s0);
            v0 = addu(v1, v0);
            sw(v0, s1, slist::kCapacity);
            backedge(ctx);
            goto L_004c1f9c;
        }
        // 0x004c201c: out of memory: error 0x80000013, 0
        charge(ctx, 5);
        v0 = 1;
        sw(v0, sp, 0x38);
        lw(v1, s1, slist::kCapacity);
        a0 = sra(v1, 2);
        if (i64(v1) < 0) {
            // 0x004c2030
            charge(ctx, 2);
            v0 = addiu(v1, 3);
            a0 = sra(v0, 2);
        }
        // 0x004c2038
        charge(ctx, 11);
        lw(v0, s1, slist::kEntrySize);
        v1 = addu(v1, s0);
        v1 = addu(a0, v1);
        mult(a1, v0, v1);
        v0 = lui(0x8000);
        a0 = v0 | 0x13;
        jal(ctx, 0x4C204Cu, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x3C);
        a0 = addiu(sp, 0x38);
        jal(ctx, 0x4C2058u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
        // 0x004c2064 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_004c1f9c:
    charge(ctx, 8);
    lw(v1, s1, slist::kCount);
    lw(v0, s1, slist::kEntrySize);
    mult(a0, v1, v0);
    v0 = addu(v1, s0);
    lw(v1, s1, slist::kData);
    sw(v0, s1, slist::kCount);
    v0 = addu(v1, a0);
    // 0x004c2064 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_4C2080 [slistDropEntries] -- count -= n
// 0x004C2080 sub_4C2080 -- 16 bytes; leaf frame (no stack)
void sub_4C2080(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x004c2080
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, slist::kCount);
    v1 = subu(v1, a1);
    sw(v1, a0, slist::kCount);
}


// sub_4C20B0 [slistDestroy] -- frees an sList's data (when it has data and a capacity) and the sList; 1
// 0x004C20B0 sub_4C20B0 -- 100 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C20B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c20b0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, slist::kData);
    if (a0 != 0) {
        // 0x004c20cc
        charge(ctx, 3);
        lw(v0, s0, slist::kCapacity);
        if (v0 != 0) {
            // 0x004c20d8
            charge(ctx, 6);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C (RwFree slot)
            jalr(ctx, 0x4C20E0u, v0.u());
            sw(zero, s0, slist::kData);
            sw(zero, s0, slist::kCapacity);
        }
    }
    // 0x004c20f0
    charge(ctx, 9);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
    a0 = s0;
    jalr(ctx, 0x4C20F8u, v0.u());
    ld(ra, sp, 0x10);
    v0 = 1;
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4C2130 [slistToArray] -- frees the sList record and returns its data (0, data freed too, when the count is 0)
// 0x004C2130 sub_4C2130 -- 116 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C2130(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c2130
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, a0, slist::kCount);
    s0 = 0;
    if (v0 != 0) {
        // 0x004c2188
        charge(ctx, 2);
        lw(s0, s1, slist::kData);
        backedge(ctx);
    } else {
        // 0x004c2150
        charge(ctx, 3);
        lw(a0, s1, slist::kData);
        if (a0 != 0) {
            // 0x004c215c
            charge(ctx, 5);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C (RwFree slot)
            jalr(ctx, 0x4C2164u, v0.u());
            sw(zero, s1, slist::kData);
        }
    }
    // 0x004c2170
    charge(ctx, 6);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
    a0 = s1;
    jalr(ctx, 0x4C2178u, v0.u());
    v0 = s0;
    // 0x004c2190
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}


// name__C9type_info_1 -- an sList's data (its first word)
// 0x004C21D0 name__C9type_info_1 -- 8 bytes; leaf frame (no stack)
void name__C9type_info_1(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x004c21d0
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, slist::kData);
}


// sub_4C21E0 [slistGetEnd] -- an sList's end: data + entry size x count
// 0x004C21E0 sub_4C21E0 -- 24 bytes; leaf frame (no stack)
void sub_4C21E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x004c21e0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v1, a0, slist::kEntrySize);
    lw(v0, a0, slist::kCount);
    mult(v1, v1, v0);
    lw(v0, a0, slist::kData);
    v0 = addu(v0, v1);
}


// sub_4CA380 [rwMallocSizeOf] -- RwMalloc(*$a0) (a tail call): a memory callback
// 0x004CA380 sub_4CA380 -- 20 bytes; leaf frame (no stack)
void sub_4CA380(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x004ca380
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x960000;
    lw(a0, a0, 0);
    lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
    tail(ctx, v0.u());  // jr: the target's entry point
}


// sub_4CA3A0 [rwFreeArg1] -- RwFree($a1); returns $a0: a memory callback
// 0x004CA3A0 sub_4CA3A0 -- 52 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4CA3A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ca3a0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, v0, 380);  // 0x96017C (RwFree slot)
    s0 = a0;
    a0 = a1;
    jalr(ctx, 0x4CA3B8u, v0.u());
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// _rwDeviceSystemRequest -- a request to the device's system function, with the standard answers when it declines
// ($a0 = the device, $a1 = the request, $a2 = out, $a3 = in, $t0 = the number) Declined requests 13..18 get the
// single-sub-system answers: 13 one sub-system, 14 sub-system 0's name 'Only rendering sub system', 15 the current
// sub-system 0, 16 setting sub-system 0, 17 / 18 accepted; anything else declined: error 24 with the request. Returns
// the result.
// 0x004CA3E0 _rwDeviceSystemRequest -- 288 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void _rwDeviceSystemRequest(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ca3e0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    s2 = a2;
    sq(s0, sp, 0x0);
    s1 = t0;
    lw(v0, a0, devreq::kSystem);
    a2 = a3;
    a1 = s2;
    a3 = s1;
    a0 = s3;
    jalr(ctx, 0x4CA414u, v0.u());
    s0 = v0;
    if (s0 == 0) {
        // 0x004ca428: declined: the standard answers of requests 13..18 (the jump table at 0x7BCBF0)
        charge(ctx, 4);
        v0 = addiu(s3, -13);
        at = sltiu(v0, 6);
        if (at != 0) {
            // 0x004ca438
            charge(ctx, 7);
            v1 = 0x7C0000;
            v0 = sll(v0, 2);
            v1 = addiu(v1, -13328);  // &0x7BCBF0 (the jump table of the standard answers)
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x4CA454u:  // table[4, 5]
                // 0x004ca454
                charge(ctx, 2);
                s0 = 1;
                break;
            case 0x4CA45Cu:  // table[0]
                // 0x004ca45c
                charge(ctx, 3);
                s0 = 1;
                sw(s0, s2, 0);
                break;
            case 0x4CA468u:  // table[1]
                // 0x004ca468
                charge(ctx, 4);
                s0 = s1;
                s0 = sltiu(s0, 1);
                if (s0 != 0) {
                    // 0x004ca478
                    charge(ctx, 8);
                    v0 = 0x960000;
                    a1 = 0x780000;
                    lw(v0, v0, 316);  // 0x96013C (the engine's strcpy slot)
                    a0 = s2;
                    a1 = addiu(a1, -6576);  // "Only rendering sub system"
                    jalr(ctx, 0x4CA488u, v0.u());
                }
                break;
            case 0x4CA498u:  // table[2]
                // 0x004ca498
                charge(ctx, 3);
                sw(zero, s2, 0);
                s0 = 1;
                break;
            case 0x4CA4A4u:  // table[3]
                // 0x004ca4a4
                charge(ctx, 2);
                s0 = s1;
                s0 = sltiu(s0, 1);
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
        }
    }
    // 0x004ca4ac
    charge(ctx, 2);
    if (s0 == 0) {
        // 0x004ca4bc: still declined: error 24 with the request
        charge(ctx, 10);
        v0 = 1;
        a1 = s3;
        sw(v0, sp, 0x58);
        a0 = 24;
        jal(ctx, 0x4CA4C8u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x5C);
        a0 = addiu(sp, 0x58);
        jal(ctx, 0x4CA4D4u, gen::fn_sub_4C1C50_004c1c50);
        backedge(ctx);
    }
    // 0x004ca4b4
    charge(ctx, 2);
    v0 = s0;
    // 0x004ca4e4
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}


// sub_4CA510 [RwEngineGetVersion] -- returns the library version 0x37002
// 0x004CA510 sub_4CA510 -- 12 bytes; leaf frame (no stack)
void sub_4CA510(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x004ca510
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x30000;
    v0 = v0 | 0x7002;
}


// sub_4CA520 [RwEngineRegisterPlugin] -- registers an engine plugin (sub_4C61B0 on the engine registry 0x77E630, no copy callback)
// 0x004CA520 sub_4CA520 -- 40 bytes; leaf frame (no stack)
void sub_4CA520(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x004ca520
    enter(ctx, 10);  // entry check point + this block's cycles
    v1 = a1;
    v0 = a2;
    a1 = a0;
    t0 = a3;
    a0 = 0x780000;
    a2 = v1;
    a0 = addiu(a0, -6608);  // &0x77E630 (the engine plugin registry)
    a3 = v0;
    t1 = 0;
    gen::fn_sub_4C61B0_004c61b0(ctx);  // tail call
}


// sub_4CA550 [RwEngineGetPluginOffset] -- the offset of an engine plugin's data, -1 when it is not registered
// (the registries' shared lookup tail at 0x4C6170)
// 0x004CA550 sub_4CA550 -- 76 bytes, 2 chunks; leaf frame (no stack)
void sub_4CA550(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x004ca550
    enter(ctx, 4);  // entry check point + this block's cycles
    a1 = a0;
    a0 = 0x780000;
    a0 = addiu(a0, -6608);  // &0x77E630 (the engine plugin registry)
    backedge(ctx);
    // 0x004c6170
    charge(ctx, 3);
    lw(v1, a0, plugreg::kFirst);
    if (v1 != 0) {
        for (;;) {
            // 0x004c617c
            charge(ctx, 3);
            lw(v0, v1, plugentry::kPluginId);
            if (v0 == a1) {
                goto L_004c6188_3;
            }
            // 0x004c6190
            charge(ctx, 3);
            lw(v1, v1, plugentry::kNext);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004c619c
        charge(ctx, 1);
    }
    // 0x004c61a0
    charge(ctx, 1);
    v0 = si(-1);
    // 0x004c61a4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_004c6188_3:
    charge(ctx, 2);
    lw(v0, v1, plugentry::kOffset);
    // 0x004c61a4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}


// sub_4CA560 [RwEngineGetVideoModeInfo] -- the device's mode info for mode $a1 into $a0 (request 6); $a0, or 0
// 0x004CA560 sub_4CA560 -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4CA560(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ca560
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t0 = a1;
    sd(ra, sp, 0x10);
    a1 = 6;
    sq(s0, sp, 0x0);
    a3 = 0;
    s0 = a0;
    a0 = 0x960000;
    a2 = s0;
    a0 = addiu(a0, 128);  // &0x960080 (the engine's device: +4 its system function)
    jal(ctx, 0x4CA584u, gen::fn__rwDeviceSystemRequest_004ca3e0);
    if (v0 == 0) {
        // 0x004ca594
        charge(ctx, 1);
        s0 = 0;
    }
    // 0x004ca598 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// sub_4CA5B0 [RwEngineGetCurrentVideoMode] -- the device's current video mode (request 10), or -1
// 0x004CA5B0 sub_4CA5B0 -- 68 bytes; frame 0x20: ra sp+0x0
void sub_4CA5B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ca5b0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a0 = 0x960000;
    sd(ra, sp, 0x0);
    a0 = addiu(a0, 128);  // &0x960080 (the engine's device: +4 its system function)
    a1 = 10;
    a2 = addiu(sp, 0x1C);
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x4CA5CCu, gen::fn__rwDeviceSystemRequest_004ca3e0);
    if (v0 == 0) {
        // 0x004ca5e4
        charge(ctx, 1);
        v0 = si(-1);
    } else {
        // 0x004ca5dc
        charge(ctx, 2);
        lw(v0, sp, 0x1C);
    }
    // 0x004ca5e8 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}


// RwEngineSetVideoMode -- selects video mode $a0 (request 7); 1 or 0
// 0x004CA600 RwEngineSetVideoMode -- 52 bytes; frame 0x10: ra sp+0x0
void RwEngineSetVideoMode(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ca600
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t0 = a0;
    a0 = 0x960000;
    sd(ra, sp, 0x0);
    a0 = addiu(a0, 128);  // &0x960080 (the engine's device: +4 its system function)
    a1 = 7;
    a2 = 0;
    a3 = 0;
    jal(ctx, 0x4CA61Cu, gen::fn__rwDeviceSystemRequest_004ca3e0);
    ld(ra, sp, 0x0);
    v0 = sltu(0, v0);
    sp = addiu(sp, 0x10);
}


// sub_4F3EC0 [RxPipelineNodeCreateInitData] -- a pipeline node's initialisation data: the old block freed, a new one of $a1 bytes
// Stores it at node +32 and its size at +36 and returns it; error 0x80000013 (out of memory) and 0 when the allocation fails.
// 0x004F3EC0 sub_4F3EC0 -- 168 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4F3EC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f3ec0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(a0, a0, 32);
    s0 = a1;
    if (a0 != 0) {
        // 0x004f3ee0: free the old initialisation data
        charge(ctx, 6);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C (RwFree slot)
        jalr(ctx, 0x4F3EE8u, v0.u());
        sw(zero, s1, pnode::kInitData);
        sw(zero, s1, pnode::kInitDataSize);
    }
    // 0x004f3ef8: RwMalloc(size, 0x30409)
    charge(ctx, 10);
    v0 = 0x30000;
    a1 = v0 | 0x409;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178 (RwMalloc slot)
    a0 = s0;
    jalr(ctx, 0x4F3F08u, v0.u());
    sw(v0, s1, pnode::kInitData);
    lw(v0, s1, pnode::kInitData);
    if (v0 == 0) {
        // 0x004f3f2c: out of memory: error 0x80000013, 0
        charge(ctx, 10);
        v0 = 1;
        a1 = s0;
        sw(v0, sp, 0x38);
        v0 = lui(0x8000);
        a0 = v0 | 0x13;
        jal(ctx, 0x4F3F3Cu, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x3C);
        a0 = addiu(sp, 0x38);
        jal(ctx, 0x4F3F48u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    } else {
        // 0x004f3f20
        charge(ctx, 3);
        sw(s0, s1, pnode::kInitDataSize);
        lw(v0, s1, pnode::kInitData);
    }
    // 0x004f3f54 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}


// sub_4F3F70 [RxPipelineNodeGetInitData] -- a pipeline node's initialisation data (node +32)
// 0x004F3F70 sub_4F3F70 -- 8 bytes; leaf frame (no stack)
void sub_4F3F70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x004f3f70
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, pnode::kInitData);
}


}  // namespace p3fes::game
