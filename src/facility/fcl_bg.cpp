// Slice fcl, part 2 of 3 (game/include/p3fes/game/fcl.h): the facility background element handlers of
// fclShopBGManager.c (0x40CA00-0x417158) that the shops slice left recompiled -- curtains, slides, spotlights,
// sparkles, orbits, fades, the part lists and their sprite sub-handlers, the status / date panels -- plus the fan
// drawer sub_40DCC0 and two number-draw wrappers. A handler is called with the background manager ($a0, shops.h
// "background manager"), the element's list node ($a1: node data +12 = the element's own area, fcl::kBgNodeArea) and
// an event ($a2: 0 for a plain frame, else a record whose s16 +6 is the event id); it returns 0 while it moves, 1 when
// idle and 2 when it has finished (the manager drops it). The sprite sub-handlers get ($a0 manager, $a1 node, $a2 x,
// $a3 y, $t0 0, $t1 alpha) and draw through sub_40E3C0 / sub_40E3F0 (shops: fclSpriteDraw / fclSpriteDrawEx).
// Reached on the shop route (the shops slice's first-call probe).
//
// The bodies are p3fes_handgen's (hg_cpu.h), statement for statement as the recompiled body; this pass adds roles
// (names in [brackets] are proposals, ADR-0009) and named offsets (fcl.h). The repeated stack-table copies and the
// float -> u8 conversions (the 2^31 bias test of cvt.w.s) are the original's.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/fcl.h"

namespace p3fes::recomp_gen {
void fn_RpSkyRenderStateSet_004d7f60(p3fes::EEContext&);
void fn_clndGetDaysSinceStartFromDate_0017d8b0(p3fes::EEContext&);
void fn_clndGetWeekDay_0017dae0(p3fes::EEContext&);
void fn_cosf_0052e6d8(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_nmListFindByKey_003c4b50(p3fes::EEContext&);
void fn_nullsub_67_0040d400(p3fes::EEContext&);
void fn_sinf_0052e878(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_sub_3E0680_003e0680(p3fes::EEContext&);
void fn_sub_3E6D70_003e6d70(p3fes::EEContext&);
void fn_sub_40D3B0_0040d3b0(p3fes::EEContext&);
void fn_sub_40D5B0_0040d5b0(p3fes::EEContext&);
void fn_sub_40D5E0_0040d5e0(p3fes::EEContext&);
void fn_sub_40DCC0_0040dcc0(p3fes::EEContext&);
void fn_sub_40E3C0_0040e3c0(p3fes::EEContext&);
void fn_sub_40E3F0_0040e3f0(p3fes::EEContext&);
void fn_sub_40EB50_0040eb50(p3fes::EEContext&);
void fn_sub_40EBC0_0040ebc0(p3fes::EEContext&);
void fn_sub_40EC20_0040ec20(p3fes::EEContext&);
void fn_sub_40F030_0040f030(p3fes::EEContext&);
void fn_sub_40F430_0040f430(p3fes::EEContext&);
void fn_sub_40F5D0_0040f5d0(p3fes::EEContext&);
void fn_sub_40FAB0_0040fab0(p3fes::EEContext&);
void fn_sub_40FB90_0040fb90(p3fes::EEContext&);
void fn_sub_4101B0_004101b0(p3fes::EEContext&);
void fn_sub_4105E0_004105e0(p3fes::EEContext&);
void fn_sub_410A10_00410a10(p3fes::EEContext&);
void fn_sub_4110E0_004110e0(p3fes::EEContext&);
void fn_sub_4113F0_004113f0(p3fes::EEContext&);
void fn_sub_411710_00411710(p3fes::EEContext&);
void fn_sub_411790_00411790(p3fes::EEContext&);
void fn_sub_4120A0_004120a0(p3fes::EEContext&);
void fn_sub_412610_00412610(p3fes::EEContext&);
void fn_sub_412AF0_00412af0(p3fes::EEContext&);
void fn_sub_412BC0_00412bc0(p3fes::EEContext&);
void fn_sub_413010_00413010(p3fes::EEContext&);
void fn_sub_4131A0_004131a0(p3fes::EEContext&);
void fn_sub_413680_00413680(p3fes::EEContext&);
void fn_sub_4138E0_004138e0(p3fes::EEContext&);
void fn_sub_413B10_00413b10(p3fes::EEContext&);
void fn_sub_414100_00414100(p3fes::EEContext&);
void fn_sub_4141E0_004141e0(p3fes::EEContext&);
void fn_sub_414280_00414280(p3fes::EEContext&);
void fn_sub_414320_00414320(p3fes::EEContext&);
void fn_sub_414500_00414500(p3fes::EEContext&);
void fn_sub_4145F0_004145f0(p3fes::EEContext&);
void fn_sub_4146B0_004146b0(p3fes::EEContext&);
void fn_sub_4148B0_004148b0(p3fes::EEContext&);
void fn_sub_414950_00414950(p3fes::EEContext&);
void fn_sub_4149F0_004149f0(p3fes::EEContext&);
void fn_sub_414AD0_00414ad0(p3fes::EEContext&);
void fn_sub_414BD0_00414bd0(p3fes::EEContext&);
void fn_sub_414C70_00414c70(p3fes::EEContext&);
void fn_sub_414D70_00414d70(p3fes::EEContext&);
void fn_sub_414E10_00414e10(p3fes::EEContext&);
void fn_sub_414FE0_00414fe0(p3fes::EEContext&);
void fn_sub_4154E0_004154e0(p3fes::EEContext&);
void fn_sub_415650_00415650(p3fes::EEContext&);
void fn_sub_4157C0_004157c0(p3fes::EEContext&);
void fn_sub_415880_00415880(p3fes::EEContext&);
void fn_sub_415A70_00415a70(p3fes::EEContext&);
void fn_sub_415B30_00415b30(p3fes::EEContext&);
void fn_sub_415B70_00415b70(p3fes::EEContext&);
void fn_sub_415C30_00415c30(p3fes::EEContext&);
void fn_sub_4167D0_004167d0(p3fes::EEContext&);
void fn_sub_416D20_00416d20(p3fes::EEContext&);
void fn_sub_417030_00417030(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace fcl;  // the named record offsets (fcl.h)

// 0x0040D3B0 sub_40D3B0 -- 76 bytes; frame 0x30: ra sp+0x0
// [fclBgForEachDraw] ($a0, $a1, $a2 s16, $a3 the background manager) Calls the element-set walker sub_3E0680 on the
// set of manager +36 -> +68 -> +8 with the per-element draw sub_40CC30 and an on-stack argument block {a0, a1, a2,
// manager, 0}.
void sub_40D3B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040d3b0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x0);
    lw(v0, a3, 36);
    lw(v0, v0, 68);
    sw(a0, sp, 0x10);
    sw(a1, sp, 0x14);
    sh(a2, sp, 0x18);
    sw(a3, sp, 0x1C);
    sw(zero, sp, 0x20);
    lw(a0, v0, 8);
    a1 = 0x410000;
    a1 = addiu(a1, -13264);  // &sub_40CC30
    a2 = addiu(sp, 0x10);
    jal(ctx, 0x40D3E4u, gen::fn_sub_3E0680_003e0680);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0040D400 nullsub_67 -- 8 bytes; leaf frame (no stack)
// [fclBgNop] An empty handler (jr $ra) in the background handler tables.
void nullsub_67(EEContext& ctx) {
    using namespace hg;
    // 0x0040d400
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0040D5B0 sub_40D5B0 -- 36 bytes; frame 0x10: ra sp+0x0
// [fclDrawNumberTail] Tail call of sub_40D5E0 with the caller's arguments. Caller: sub_3ABB10.
void sub_40D5B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x0040d5b0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    mtc1(zero, f12);
    jal(ctx, 0x40D5BCu, gen::fn_sub_40D5E0_0040d5e0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0040DCC0 sub_40DCC0 -- 1588 bytes; frame 0x180: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [fclDrawFan] ($a0 / $a1 centre, $a2 / $a3 / $t0 three radii, $t1 RGBA, $t3 0 = set the render states, $f12 depth,
// $f13..$f15 three angles) Draws one RwIm2D triangle (three vertices on the radii at the angles, colour $t1, z = near
// screen z - $f12); with $t3 == 0 first sets the sky render states (RpSkyRenderStateSet 2 / 3) and the RW states 6, 8,
// 7, 9, 12, 14, 20, 1. Ends with RwRenderStateSet(1, 0). Caller: the memory-card UI's sub_420DA0.
void sub_40DCC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x0040dcc0
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x180);
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
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s0 = a0;
    s5 = a1;
    mov_s(f20, f12);
    s7 = a2;
    fp = a3;
    sw(t0, sp, 0xBC);
    s1 = t1;
    s6 = t2;
    if (t3 == 0) {
        // 0x0040dd20
        charge(ctx, 51);
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x40DD28u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x40DD3Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
        s2 = 0x960000;
        s2 = addiu(s2, 144);  // &pfn_RwRenderStateSet
        a0 = 6;
        a1 = 1;
        lw(v0, s2, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x40DD58u, v0.u());
        a0 = 8;
        a1 = 1;
        lw(v0, s2, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x40DD6Cu, v0.u());
        a0 = 7;
        a1 = 2;
        lw(v0, s2, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x40DD80u, v0.u());
        a0 = 9;
        a1 = 2;
        lw(v0, s2, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x40DD94u, v0.u());
        a0 = 12;
        a1 = 1;
        lw(v0, s2, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x40DDA8u, v0.u());
        a0 = 14;
        a1 = 0;
        lw(v0, s2, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x40DDBCu, v0.u());
        a0 = 20;
        a1 = 2;
        lw(v0, s2, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x40DDD0u, v0.u());
        a0 = 1;
        a1 = 0;
        lw(v0, s2, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x40DDE4u, v0.u());
    }
    // 0x0040ddec
    charge(ctx, 45);
    v0 = srl(s1, 24);
    s4 = v0 & 0xFF;
    v0 = srl(s1, 16);
    s3 = v0 & 0xFF;
    v0 = srl(s1, 8);
    s2 = v0 & 0xFF;
    s1 = s1 & 0xFF;
    v0 = 0x960000;
    lwc1(f0, v0, 136);  // g_rwIm2DNearScreenZ
    sub_s(f20, f0, f20);
    mtc1(s6, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, gp, -32220);  // 0x7CAF14
    mul_s(f1, f0, f1);
    lwc1(f0, gp, -32496);  // 0x7CAE00
    add_s(f21, f0, f1);
    mov_s(f12, f21);
    jal(ctx, 0x40DE34u, gen::fn_cosf_0052e6d8);
    mtc1(s7, f1);
    cvt_s_w(f1, f1);
    mul_s(f22, f1, f0);
    mov_s(f12, f21);
    jal(ctx, 0x40DE50u, gen::fn_sinf_0052e878);
    v0 = subu(0, s7);
    mtc1(v0, f1);
    cvt_s_w(f1, f1);
    mul_s(f1, f1, f0);
    mtc1(s0, f0);
    cvt_s_w(f0, f0);
    add_s(f0, f0, f22);
    swc1(f0, sp, 0xC0);
    mtc1(s5, f0);
    cvt_s_w(f0, f0);
    add_s(f0, f0, f1);
    swc1(f0, sp, 0xC4);
    swc1(f20, sp, 0xC8);
    if (i64(s4) < 0) {
        // 0x0040deb4
        charge(ctx, 7);
        v1 = srl(s4, 1);
        v0 = s4 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0040dea0
        charge(ctx, 5);
        mtc1(s4, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0040ded0
    charge(ctx, 3);
    swc1(f0, sp, 0xE0);
    if (i64(s3) < 0) {
        // 0x0040def0
        charge(ctx, 7);
        v1 = srl(s3, 1);
        v0 = s3 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0040dedc
        charge(ctx, 5);
        mtc1(s3, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0040df0c
    charge(ctx, 3);
    swc1(f0, sp, 0xE4);
    if (i64(s2) < 0) {
        // 0x0040df2c
        charge(ctx, 7);
        v1 = srl(s2, 1);
        v0 = s2 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0040df18
        charge(ctx, 5);
        mtc1(s2, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0040df48
    charge(ctx, 3);
    swc1(f0, sp, 0xE8);
    if (i64(s1) < 0) {
        // 0x0040df68
        charge(ctx, 7);
        v1 = srl(s1, 1);
        v0 = s1 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0040df54
        charge(ctx, 5);
        mtc1(s1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0040df84
    charge(ctx, 37);
    swc1(f0, sp, 0xEC);
    v0 = addiu(s6, 120);
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, gp, -32220);  // 0x7CAF14
    mul_s(f1, f0, f1);
    lwc1(f0, gp, -32496);  // 0x7CAE00
    add_s(f22, f0, f1);
    mov_s(f12, f22);
    jal(ctx, 0x40DFACu, gen::fn_cosf_0052e6d8);
    mtc1(fp, f1);
    cvt_s_w(f1, f1);
    mul_s(f21, f1, f0);
    mov_s(f12, f22);
    jal(ctx, 0x40DFC8u, gen::fn_sinf_0052e878);
    v0 = subu(0, fp);
    mtc1(v0, f1);
    cvt_s_w(f1, f1);
    mul_s(f1, f1, f0);
    mtc1(s0, f0);
    cvt_s_w(f0, f0);
    add_s(f0, f0, f21);
    swc1(f0, sp, 0x100);
    mtc1(s5, f0);
    cvt_s_w(f0, f0);
    add_s(f0, f0, f1);
    swc1(f0, sp, 0x104);
    swc1(f20, sp, 0x108);
    if (i64(s4) < 0) {
        // 0x0040e02c
        charge(ctx, 7);
        v1 = srl(s4, 1);
        v0 = s4 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0040e018
        charge(ctx, 5);
        mtc1(s4, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0040e048
    charge(ctx, 3);
    swc1(f0, sp, 0x120);
    if (i64(s3) < 0) {
        // 0x0040e068
        charge(ctx, 7);
        v1 = srl(s3, 1);
        v0 = s3 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0040e054
        charge(ctx, 5);
        mtc1(s3, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0040e084
    charge(ctx, 3);
    swc1(f0, sp, 0x124);
    if (i64(s2) < 0) {
        // 0x0040e0a4
        charge(ctx, 7);
        v1 = srl(s2, 1);
        v0 = s2 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0040e090
        charge(ctx, 5);
        mtc1(s2, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0040e0c0
    charge(ctx, 3);
    swc1(f0, sp, 0x128);
    if (i64(s1) < 0) {
        // 0x0040e0e0
        charge(ctx, 7);
        v1 = srl(s1, 1);
        v0 = s1 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0040e0cc
        charge(ctx, 5);
        mtc1(s1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0040e0fc
    charge(ctx, 39);
    swc1(f0, sp, 0x12C);
    v0 = addiu(s6, -120);
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, gp, -32220);  // 0x7CAF14
    mul_s(f1, f0, f1);
    lwc1(f0, gp, -32496);  // 0x7CAE00
    add_s(f22, f0, f1);
    mov_s(f12, f22);
    jal(ctx, 0x40E124u, gen::fn_cosf_0052e6d8);
    lw(v0, sp, 0xBC);
    mtc1(v0, f1);
    cvt_s_w(f1, f1);
    mul_s(f21, f1, f0);
    mov_s(f12, f22);
    jal(ctx, 0x40E144u, gen::fn_sinf_0052e878);
    lw(v0, sp, 0xBC);
    v0 = subu(0, v0);
    mtc1(v0, f1);
    cvt_s_w(f1, f1);
    mul_s(f1, f1, f0);
    mtc1(s0, f0);
    cvt_s_w(f0, f0);
    add_s(f0, f0, f21);
    swc1(f0, sp, 0x140);
    mtc1(s5, f0);
    cvt_s_w(f0, f0);
    add_s(f0, f0, f1);
    swc1(f0, sp, 0x144);
    swc1(f20, sp, 0x148);
    if (i64(s4) < 0) {
        // 0x0040e1ac
        charge(ctx, 7);
        v1 = srl(s4, 1);
        v0 = s4 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0040e198
        charge(ctx, 5);
        mtc1(s4, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0040e1c8
    charge(ctx, 3);
    swc1(f0, sp, 0x160);
    if (i64(s3) < 0) {
        // 0x0040e1e8
        charge(ctx, 7);
        v1 = srl(s3, 1);
        v0 = s3 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0040e1d4
        charge(ctx, 5);
        mtc1(s3, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0040e204
    charge(ctx, 3);
    swc1(f0, sp, 0x164);
    if (i64(s2) < 0) {
        // 0x0040e224
        charge(ctx, 7);
        v1 = srl(s2, 1);
        v0 = s2 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0040e210
        charge(ctx, 5);
        mtc1(s2, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0040e240
    charge(ctx, 3);
    swc1(f0, sp, 0x168);
    if (i64(s1) < 0) {
        // 0x0040e260
        charge(ctx, 7);
        v1 = srl(s1, 1);
        v0 = s1 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x0040e24c
        charge(ctx, 5);
        mtc1(s1, f0);
        cvt_s_w(f0, f0);
    }
    // 0x0040e27c
    charge(ctx, 30);
    swc1(f0, sp, 0x16C);
    a0 = 3;
    a1 = addiu(sp, 0xC0);
    a2 = a0;
    v0 = 0x960000;
    lw(v0, v0, 160);  // pfn_RwIm2DRenderPrimitive
    jalr(ctx, 0x40E294u, v0.u());
    a0 = 1;
    a1 = 0;
    v0 = 0x960000;
    lw(v0, v0, 144);  // pfn_RwRenderStateSet
    jalr(ctx, 0x40E2ACu, v0.u());
    ld(ra, sp, 0xA0);
    lq(fp, sp, 0x90);
    lq(s7, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x180);
}

// 0x0040EBC0 sub_40EBC0 -- 96 bytes; frame 0x30: ra sp+0x0
// [fclDrawDigitsCentred] Copies the 5-entry offset table 0x6AF980 to the stack and calls sub_40EC20 with the offset
// for size class $a3 and the glyph callback sub_40EEF0 (the other arguments passed through). Callers: sub_405F70,
// sub_4064E0, sub_406AA0.
void sub_40EBC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a3{ctx, 7}, t2{ctx, 10}, t3{ctx, 11}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040ebc0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x0);
    t3 = 0x6B0000;
    t3 = addiu(t3, -1664);  // &0x6AF980
    t2 = addiu(sp, 0x10);
    v1 = 5;
    for (;;) {
        // 0x0040ebd8
        charge(ctx, 7);
        lw(v0, t3, 0);
        t3 = addiu(t3, 4);
        v1 = addiu(v1, -1);
        sw(v0, t2, 0);
        t2 = addiu(t2, 4);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0040ebf4
    charge(ctx, 11);
    v0 = sll(a3, 2);
    v0 = addu(v0, sp);
    lw(t2, v0, 16);
    t3 = 0x410000;
    t3 = addiu(t3, -4368);  // &sub_40EEF0
    jal(ctx, 0x40EC08u, gen::fn_sub_40EC20_0040ec20);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0040F030 sub_40F030 -- 1016 bytes; frame 0x60: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgCurtain] A background element handler (manager $a0, node $a1: area +12, event $a2): two panels of 20 bytes
// {flags, x, y, x0, -, alpha, alpha max, timer, step}. Event 1 resets them (x 320, the per-shop-type y / alpha table
// 0x6AF9C0 by manager +28, slide-in flag 1); event 4 starts the slide-out (flags 2 | 8). Each frame (only while the
// shop sequence's step check sub_3E6D70 passes) slides them by 5/2 px per frame from x0 and fades alpha over 10
// frames; returns 2 when both are closed (+40 = 1), 1 while idle, 2 when the step check fails.
void sub_40F030(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040f030
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s2 = a2;
    lw(s0, a1, kBgNodeArea);
    a2 = 0x6B0000;
    a2 = addiu(a2, -1600);  // &0x6AF9C0
    a1 = addiu(sp, 0x40);
    a0 = 6;
    for (;;) {
        // 0x0040f060: the per-shop-type table 0x6AF9C0 to the stack
        charge(ctx, 9);
        lh(v1, a2, 0);
        lh(v0, a2, 2);
        a2 = addiu(a2, 4);
        a0 = addiu(a0, -1);
        sh(v1, a1, 0);
        sh(v0, a1, 2);
        a1 = addiu(a1, 4);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0040f084: the shop step check (sub_3E6D70)
    charge(ctx, 4);
    jal(ctx, 0x40F084u, gen::fn_sub_3E6D70_003e6d70);
    if (v0 != 0) {
        // 0x0040f0a0
        charge(ctx, 2);
        if (s2 != 0) {
            // 0x0040f0a8: an event
            charge(ctx, 4);
            lh(v1, s2, kBgEventId);
            v0 = 4;
            if (v1 == v0) {
                // 0x0040f194: event 4: slide both panels out
                charge(ctx, 10);
                lw(v0, s0, 0);
                v0 = v0 | 0x2;
                sw(v0, s0, 0);
                v0 = v0 | 0x8;
                sw(v0, s0, 0);
                lw(v0, s0, 20);
                v0 = v0 | 0x2;
                sw(v0, s0, 20);
                v0 = v0 | 0x8;
                sw(v0, s0, 20);
            } else {
                // 0x0040f0b8
                charge(ctx, 3);
                v0 = 2;
                if (v1 != v0) {
                    // 0x0040f0c4
                    charge(ctx, 3);
                    v0 = 1;
                    if (v1 == v0) {
                        // 0x0040f0d8: event 1: reset and slide in
                        charge(ctx, 47);
                        a0 = s0;
                        a1 = 0;
                        a2 = 40;
                        jal(ctx, 0x40F0E4u, gen::fn_memset_00521408);
                        v0 = 320;
                        sh(v0, s0, 8);
                        sh(v0, s0, 4);
                        lw(v0, s1, kBgMgrShopType);
                        v0 = sll(v0, 3);
                        v0 = addu(v0, sp);
                        lh(v0, v0, 64);
                        sh(v0, s0, 6);
                        lw(v0, s1, kBgMgrShopType);
                        v0 = sll(v0, 3);
                        v0 = addu(v0, sp);
                        lh(v0, v0, 66);
                        sh(v0, s0, 14);
                        lw(v0, s0, 0);
                        v0 = v0 | 0x1;
                        sw(v0, s0, 0);
                        v1 = si(-9);
                        v0 = v0 & v1;
                        sw(v0, s0, 0);
                        v0 = 640;
                        sh(v0, s0, 28);
                        sh(v0, s0, 24);
                        lw(v0, s1, kBgMgrShopType);
                        v0 = sll(v0, 3);
                        v0 = addu(v0, sp);
                        lh(v0, v0, 64);
                        sh(v0, s0, 26);
                        v0 = 48;
                        sh(v0, s0, 36);
                        lw(v0, s1, kBgMgrShopType);
                        v0 = sll(v0, 3);
                        v0 = addu(v0, sp);
                        lh(v0, v0, 66);
                        sh(v0, s0, 34);
                        lw(v0, s0, 20);
                        v0 = v0 | 0x4;
                        sw(v0, s0, 20);
                        v0 = v0 & v1;
                        sw(v0, s0, 20);
                        sw(zero, s0, 40);
                    } else {
                        // 0x0040f0d0
                        charge(ctx, 2);
                    }
                }
            }
        }
        // 0x0040f1bc: finished / idle?
        charge(ctx, 4);
        lw(v1, s0, 40);
        v0 = 2;
        if (v1 != v0) {
            // 0x0040f1cc
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                goto L_0040f408;
            }
            // 0x0040f1d8
            charge(ctx, 2);
            if (v1 != 0) {
                // 0x0040f1e0
                charge(ctx, 2);
                goto L_0040f408;
            }
            // 0x0040f1e8: per frame: each of the two panels
            charge(ctx, 9);
            a3 = 0;
            t0 = 0;
            t2 = si(-3);
            v1 = 10;
            v0 = si(-2);
            a1 = si(-5);
            a0 = 640;
            for (;;) {
                // 0x0040f3dc
                charge(ctx, 3);
                a2 = slti(t0, 2);
                if (a2 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0040f20c
                charge(ctx, 8);
                a2 = sll(t0, 2);
                a2 = addu(a2, t0);
                a2 = sll(a2, 2);
                a2 = addu(s0, a2);
                lw(t3, a2, 0);
                t1 = t3 & 0x4;
                if (t1 == 0) {
                    // 0x0040f288: open: slide by 5/2 px per frame
                    charge(ctx, 7);
                    lh(t1, a2, 16);
                    t1 = addiu(t1, 1);
                    sh(t1, a2, 16);
                    lh(t1, a2, 4);
                    at = slti(t1, 101);
                    if (at != 0) {
                        // 0x0040f2a4
                        charge(ctx, 4);
                        lw(t3, a2, 0);
                        t1 = t3 & 0x2;
                        if (t1 == 0) {
                            // 0x0040f2b4
                            charge(ctx, 2);
                            t1 = t3 | 0x2;
                            sw(t1, a2, 0);
                        }
                    }
                    // 0x0040f2bc
                    charge(ctx, 6);
                    lh(t3, a2, 16);
                    t1 = sll(t3, 2);
                    t1 = addu(t1, t3);
                    t3 = sra(t1, 1);
                    if (i64(t1) < 0) {
                        // 0x0040f2d4
                        charge(ctx, 2);
                        t1 = addiu(t1, 1);
                        t3 = sra(t1, 1);
                    }
                    // 0x0040f2dc
                    charge(ctx, 7);
                    lh(t1, a2, 8);
                    t1 = subu(t1, t3);
                    sh(t1, a2, 4);
                    lw(t3, a2, 0);
                    t1 = t3 & 0x1;
                    if (t1 == 0) {
                        // 0x0040f358
                        charge(ctx, 3);
                        t1 = t3 & 0x2;
                        if (t1 != 0) {
                            // 0x0040f364: fading out
                            charge(ctx, 17);
                            lh(t1, a2, 18);
                            t1 = addiu(t1, 1);
                            sh(t1, a2, 18);
                            lh(t3, a2, 14);
                            t1 = dsll32(t1, 16);
                            t1 = dsra32(t1, 16);
                            mult(t1, t3, t1);
                            div(t1, v1);
                            mflo(t1);
                            t1 = subu(t3, t1);
                            sh(t1, a2, 12);
                            lh(t1, a2, 18);
                            t1 = slti(t1, 10);
                            if (t1 == 0) {
                                // 0x0040f3a8
                                charge(ctx, 12);
                                lw(t1, a2, 0);
                                t1 = t1 & t2;
                                sw(t1, a2, 0);
                                t1 = t1 | 0x4;
                                sw(t1, a2, 0);
                                sh(zero, a2, 12);
                                sh(zero, a2, 18);
                                lw(t1, s1, kBgMgrShopType);
                                t1 = sll(t1, 3);
                                t1 = addu(t1, sp);
                                lh(t1, t1, 68);
                                sh(t1, a2, 16);
                            }
                        }
                    } else {
                        // 0x0040f2f8: fading in
                        charge(ctx, 16);
                        lh(t1, a2, 18);
                        t1 = addiu(t1, 1);
                        sh(t1, a2, 18);
                        lh(t3, a2, 14);
                        t1 = dsll32(t1, 16);
                        t1 = dsra32(t1, 16);
                        mult(t1, t3, t1);
                        div(t1, v1);
                        mflo(t1);
                        sh(t1, a2, 12);
                        lh(t1, a2, 18);
                        t1 = slti(t1, 10);
                        if (t1 == 0) {
                            // 0x0040f338
                            charge(ctx, 8);
                            lw(t1, a2, 0);
                            t1 = t1 & v0;
                            sw(t1, a2, 0);
                            lh(t1, a2, 14);
                            sh(t1, a2, 12);
                            sh(zero, a2, 18);
                        }
                    }
                } else {
                    // 0x0040f22c
                    charge(ctx, 3);
                    t1 = t3 & 0x8;
                    if (t1 == 0) {
                        // 0x0040f244: closed: count the wait down, then reopen
                        charge(ctx, 7);
                        lh(t1, a2, 16);
                        t1 = addiu(t1, -1);
                        sh(t1, a2, 16);
                        t1 = dsll32(t1, 16);
                        t1 = dsra32(t1, 16);
                        if (i64(t1) <= 0) {
                            // 0x0040f260
                            charge(ctx, 10);
                            sh(zero, a2, 16);
                            lw(t1, a2, 0);
                            t1 = t1 & a1;
                            sw(t1, a2, 0);
                            t1 = t1 | 0x1;
                            sw(t1, a2, 0);
                            sh(a0, a2, 8);
                            sh(a0, a2, 4);
                        }
                    } else {
                        // 0x0040f238
                        charge(ctx, 3);
                        a3 = addiu(a3, 1);
                    }
                }
                // 0x0040f3d8
                charge(ctx, 1);
                t0 = addiu(t0, 1);
            }
            // 0x0040f3e8: both closed: finished (+40 = 1)
            charge(ctx, 3);
            v0 = slti(a3, 2);
            if (v0 != 0) {
                goto L_0040f408;
            }
            // 0x0040f3f4
            charge(ctx, 5);
            v0 = 1;
            sw(v0, s0, 40);
            v0 = 2;
            // 0x0040f40c (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(ra, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x60);
            return;
        }
    L_0040f408:
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x0040f094: step check failed
        charge(ctx, 3);
        v0 = 2;
    }
    // 0x0040f40c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0040F430 sub_40F430 -- 416 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgCurtainDraw] Draws the two curtain panels (sprite 86..89 for shop type 2, else the per-type sprite of
// 0x6AF9D8) at their positions and alpha (sub_40E3C0). Returns 0, or 2 when the step check sub_3E6D70 fails.
void sub_40F430(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12};
    // 0x0040f430
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(s0, a1, kBgNodeArea);
    v0 = 0x6B0000;
    lwc1(f2, v0, -1576);  // 0x6AF9D8
    v0 = 0x6B0000;
    lwc1(f1, v0, -1572);  // 0x6AF9DC
    v0 = 0x6B0000;
    lwc1(f0, v0, -1568);  // 0x6AF9E0
    swc1(f2, sp, 0x40);
    swc1(f1, sp, 0x44);
    swc1(f0, sp, 0x48);
    jal(ctx, 0x40F470u, gen::fn_sub_3E6D70_003e6d70);
    if (v0 != 0) {
        // 0x0040f48c
        charge(ctx, 4);
        lw(v1, s2, 28);
        v0 = 2;
        if (v1 == v0) {
            // 0x0040f4a4
            charge(ctx, 3);
            s1 = 0;
            for (;;) {
                // 0x0040f544
                charge(ctx, 3);
                v0 = slti(s1, 2);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0040f4b0
                charge(ctx, 37);
                v0 = sll(s1, 2);
                v0 = addu(v0, s1);
                v0 = sll(v0, 2);
                s2 = addu(s0, v0);
                lh(a0, s2, 4);
                lh(a1, s2, 6);
                mtc1(zero, f12);
                lbu(a2, s2, 12);
                a3 = 86;
                t0 = 0;
                jal(ctx, 0x40F4D8u, gen::fn_sub_40E3C0_0040e3c0);
                lh(a0, s2, 4);
                lh(a1, s2, 6);
                mtc1(zero, f12);
                lbu(a2, s2, 12);
                a3 = 87;
                t0 = 0;
                jal(ctx, 0x40F4F8u, gen::fn_sub_40E3C0_0040e3c0);
                lh(a0, s2, 4);
                lh(a1, s2, 6);
                mtc1(zero, f12);
                lbu(a2, s2, 12);
                a3 = 88;
                t0 = 0;
                jal(ctx, 0x40F518u, gen::fn_sub_40E3C0_0040e3c0);
                lh(a0, s2, 4);
                lh(a1, s2, 6);
                mtc1(zero, f12);
                lbu(a2, s2, 12);
                a3 = 89;
                t0 = 0;
                jal(ctx, 0x40F538u, gen::fn_sub_40E3C0_0040e3c0);
                s1 = addiu(s1, 1);
            }
            // 0x0040f550
            charge(ctx, 2);
        } else {
            // 0x0040f49c
            charge(ctx, 2);
            // 0x0040f558
            charge(ctx, 3);
            s1 = 0;
            for (;;) {
                // 0x0040f5a4
                charge(ctx, 3);
                v0 = slti(s1, 2);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0040f564
                charge(ctx, 16);
                v0 = sll(s1, 2);
                v0 = addu(v0, s1);
                v0 = sll(v0, 2);
                v0 = addu(s0, v0);
                lh(a0, v0, 4);
                lh(a1, v0, 6);
                mtc1(zero, f12);
                lbu(a2, v0, 12);
                lw(v0, s2, 28);
                v0 = sll(v0, 2);
                v0 = addu(v0, sp);
                lw(a3, v0, 64);
                t0 = 0;
                jal(ctx, 0x40F598u, gen::fn_sub_40E3C0_0040e3c0);
                s1 = addiu(s1, 1);
            }
        }
        // 0x0040f5b0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0040f480
        charge(ctx, 3);
        v0 = 2;
    }
    // 0x0040f5b4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0040F5D0 sub_40F5D0 -- 1236 bytes; frame 0x120: ra sp+0x10, s0 sp+0x0 (sq)
// [fclBgSlide5] A background element handler: five 12-byte keys {s16 x, y, alpha, start frame; f32 scale}. Event 1
// loads the in-keys (table 0x6AF9F0), event 4 the out-keys (0x6AFA70, state 2). Each frame interpolates every key
// linearly from its start frame over its duration toward the target keys (+60 bytes later in the table); in state 0
// when all five are done the state becomes 1 (returns 0), in state 2 it returns 2 when done; 1 while idle.
void sub_40F5D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x0040f5d0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x120);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a1, kBgNodeArea);
    a3 = 0x6B0000;
    a3 = addiu(a3, -1552);  // &0x6AF9F0
    a1 = addiu(sp, 0xA0);
    a0 = 15;
    for (;;) {
        // 0x0040f5f0
        charge(ctx, 9);
        lw(v1, a3, 0);
        lw(v0, a3, 4);
        a3 = addiu(a3, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0040f614
    charge(ctx, 4);
    a3 = 0x6B0000;
    a3 = addiu(a3, -1424);  // &0x6AFA70
    a1 = addiu(sp, 0x20);
    a0 = 15;
    for (;;) {
        // 0x0040f624
        charge(ctx, 9);
        lw(v1, a3, 0);
        lw(v0, a3, 4);
        a3 = addiu(a3, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0040f648
    charge(ctx, 2);
    if (a2 != 0) {
        // 0x0040f650
        charge(ctx, 4);
        lh(v1, a2, kBgEventId);
        v0 = 4;
        if (v1 == v0) {
            // 0x0040f6a4
            charge(ctx, 8);
            a0 = s0;
            a1 = addiu(sp, 0x20);
            a2 = 60;
            jal(ctx, 0x40F6B0u, gen::fn_memcpy_00521250);
            v0 = 2;
            sh(v0, s0, 60);
            sh(zero, s0, 62);
        } else {
            // 0x0040f660
            charge(ctx, 3);
            v0 = 2;
            if (v1 != v0) {
                // 0x0040f66c
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    // 0x0040f680
                    charge(ctx, 9);
                    a0 = s0;
                    a1 = addiu(sp, 0xA0);
                    a2 = 60;
                    jal(ctx, 0x40F68Cu, gen::fn_memcpy_00521250);
                    sh(zero, s0, 60);
                    sh(zero, s0, 62);
                } else {
                    // 0x0040f678
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x0040f6c4
    charge(ctx, 4);
    lh(v1, s0, 60);
    v0 = 2;
    if (v1 == v0) {
        // 0x0040f8b8
        charge(ctx, 7);
        lh(v0, s0, 62);
        v0 = addiu(v0, 1);
        sh(v0, s0, 62);
        a3 = 0;
        a2 = 0;
        for (;;) {
            // 0x0040fa50
            charge(ctx, 3);
            v0 = slti(a2, 5);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0040f8d4
            charge(ctx, 9);
            v0 = sll(a2, 1);
            v0 = addu(v0, a2);
            t0 = sll(v0, 2);
            a1 = addu(s0, t0);
            lh(a0, a1, 6);
            lh(v1, s0, 62);
            v0 = slt(v1, a0);
            if (v0 == 0) {
                // 0x0040f8f8
                charge(ctx, 8);
                a0 = subu(v1, a0);
                v0 = addu(t0, sp);
                v1 = addiu(v0, 32);
                v0 = addiu(v1, 66);
                lh(t2, v1, 66);
                at = slt(t2, a0);
                if (at != 0) {
                    // 0x0040fa48
                    charge(ctx, 1);
                    a3 = addiu(a3, 1);
                } else {
                    // 0x0040f918
                    charge(ctx, 76);
                    lh(t1, v1, 0);
                    lh(t0, v1, 60);
                    t0 = subu(t0, t1);
                    mult(t0, a0, t0);
                    mtc1(t0, f0);
                    cvt_s_w(f1, f0);
                    mtc1(t2, f0);
                    cvt_s_w(f0, f0);
                    div_s(f1, f1, f0);
                    mtc1(t1, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(t0, f0);
                    sh(t0, a1, 0);
                    lh(t1, v1, 2);
                    lh(t0, v1, 62);
                    t0 = subu(t0, t1);
                    mult1(t0, a0, t0);
                    mtc1(t0, f0);
                    cvt_s_w(f1, f0);
                    lh(t0, v0, 0);
                    mtc1(t0, f0);
                    cvt_s_w(f0, f0);
                    div_s(f1, f1, f0);
                    mtc1(t1, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(t0, f0);
                    sh(t0, a1, 2);
                    lh(t1, v1, 4);
                    lh(t0, v1, 64);
                    t0 = subu(t0, t1);
                    mult(t0, a0, t0);
                    mtc1(t0, f0);
                    cvt_s_w(f1, f0);
                    lh(t0, v0, 0);
                    mtc1(t0, f0);
                    cvt_s_w(f0, f0);
                    div_s(f1, f1, f0);
                    mtc1(t1, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(t0, f0);
                    sh(t0, a1, 4);
                    lwc1(f2, v1, 8);
                    lwc1(f0, v1, 68);
                    sub_s(f1, f0, f2);
                    mtc1(a0, f0);
                    cvt_s_w(f0, f0);
                    mul_s(f1, f0, f1);
                    lh(v0, v0, 0);
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    div_s(f0, f1, f0);
                    add_s(f0, f2, f0);
                    swc1(f0, a1, 8);
                }
            }
            // 0x0040fa4c
            charge(ctx, 1);
            a2 = addiu(a2, 1);
        }
        // 0x0040fa5c
        charge(ctx, 3);
        v0 = slti(a3, 5);
        if (v0 != 0) {
            // 0x0040fa80
            charge(ctx, 3);
            v0 = 0;
        } else {
            // 0x0040fa68
            charge(ctx, 6);
            v0 = 1;
            sh(v0, s0, 60);
            sh(zero, s0, 62);
            v0 = 2;
        }
    } else {
        // 0x0040f6d4
        charge(ctx, 3);
        v0 = 1;
        if (v1 != v0) {
            // 0x0040f6e0
            charge(ctx, 2);
            if (v1 != 0) {
                // 0x0040f6e8
                charge(ctx, 2);
                goto L_0040fa8c;
            }
            // 0x0040f6f0
            charge(ctx, 7);
            lh(v0, s0, 62);
            v0 = addiu(v0, 1);
            sh(v0, s0, 62);
            a2 = 0;
            a3 = 0;
            for (;;) {
                // 0x0040f888
                charge(ctx, 3);
                v0 = slti(a3, 5);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0040f70c
                charge(ctx, 9);
                v0 = sll(a3, 1);
                v0 = addu(v0, a3);
                t0 = sll(v0, 2);
                a1 = addu(s0, t0);
                lh(a0, a1, 6);
                lh(v1, s0, 62);
                v0 = slt(v1, a0);
                if (v0 == 0) {
                    // 0x0040f730
                    charge(ctx, 8);
                    a0 = subu(v1, a0);
                    v0 = addu(t0, sp);
                    v1 = addiu(v0, 160);
                    v0 = addiu(v1, 66);
                    lh(t2, v1, 66);
                    at = slt(t2, a0);
                    if (at != 0) {
                        // 0x0040f880
                        charge(ctx, 1);
                        a2 = addiu(a2, 1);
                    } else {
                        // 0x0040f750
                        charge(ctx, 76);
                        lh(t1, v1, 0);
                        lh(t0, v1, 60);
                        t0 = subu(t0, t1);
                        mult(t0, a0, t0);
                        mtc1(t0, f0);
                        cvt_s_w(f1, f0);
                        mtc1(t2, f0);
                        cvt_s_w(f0, f0);
                        div_s(f1, f1, f0);
                        mtc1(t1, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f0, f1);
                        cvt_w_s(f0, f0);
                        mfc1(t0, f0);
                        sh(t0, a1, 0);
                        lh(t1, v1, 2);
                        lh(t0, v1, 62);
                        t0 = subu(t0, t1);
                        mult1(t0, a0, t0);
                        mtc1(t0, f0);
                        cvt_s_w(f1, f0);
                        lh(t0, v0, 0);
                        mtc1(t0, f0);
                        cvt_s_w(f0, f0);
                        div_s(f1, f1, f0);
                        mtc1(t1, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f0, f1);
                        cvt_w_s(f0, f0);
                        mfc1(t0, f0);
                        sh(t0, a1, 2);
                        lh(t1, v1, 4);
                        lh(t0, v1, 64);
                        t0 = subu(t0, t1);
                        mult(t0, a0, t0);
                        mtc1(t0, f0);
                        cvt_s_w(f1, f0);
                        lh(t0, v0, 0);
                        mtc1(t0, f0);
                        cvt_s_w(f0, f0);
                        div_s(f1, f1, f0);
                        mtc1(t1, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f0, f1);
                        cvt_w_s(f0, f0);
                        mfc1(t0, f0);
                        sh(t0, a1, 4);
                        lwc1(f2, v1, 8);
                        lwc1(f0, v1, 68);
                        sub_s(f1, f0, f2);
                        mtc1(a0, f0);
                        cvt_s_w(f0, f0);
                        mul_s(f1, f0, f1);
                        lh(v0, v0, 0);
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        div_s(f0, f1, f0);
                        add_s(f0, f2, f0);
                        swc1(f0, a1, 8);
                    }
                }
                // 0x0040f884
                charge(ctx, 1);
                a3 = addiu(a3, 1);
            }
            // 0x0040f894
            charge(ctx, 3);
            v0 = slti(a2, 5);
            if (v0 == 0) {
                // 0x0040f8a0
                charge(ctx, 3);
                v0 = 1;
                sh(v0, s0, 60);
                sh(zero, s0, 62);
            }
            // 0x0040f8ac
            charge(ctx, 3);
            v0 = 0;
            // 0x0040fa90 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(ra, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x120);
            return;
        }
    L_0040fa8c:
        charge(ctx, 1);
        v0 = 1;
    }
    // 0x0040fa90 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x120);
}

// 0x0040FAB0 sub_40FAB0 -- 216 bytes; frame 0x50: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgDraw8] Draws the sprites 90..97 at the positions of the keys picked by the index table 0x6AFAF0 (offset 16 /
// 13, alpha from the key) with sub_40E3F0. Returns 0.
void sub_40FAB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15};
    // 0x0040fab0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a1, kBgNodeArea);
    a2 = 0x6B0000;
    a2 = addiu(a2, -1296);  // &0x6AFAF0
    a1 = addiu(sp, 0x30);
    a0 = 4;
    for (;;) {
        // 0x0040fad4
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
    // 0x0040faf8
    charge(ctx, 3);
    s1 = 0;
    for (;;) {
        // 0x0040fb60
        charge(ctx, 3);
        v0 = slti(s1, 8);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0040fb04
        charge(ctx, 23);
        v0 = sll(s1, 2);
        v0 = addu(v0, sp);
        lw(v1, v0, 48);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        v1 = addu(s0, v0);
        lwc1(f14, v1, 8);
        lh(v0, v1, 0);
        a0 = addiu(v0, 16);
        lh(v0, v1, 2);
        a1 = addiu(v0, 13);
        mtc1(zero, f12);
        lbu(a2, v1, 4);
        a3 = addiu(s1, 90);
        t0 = 0;
        t1 = 0;
        t2 = 0;
        mov_s(f13, f12);
        mov_s(f15, f14);
        jal(ctx, 0x40FB54u, gen::fn_sub_40E3F0_0040e3f0);
        s1 = addiu(s1, 1);
    }
    // 0x0040fb6c
    charge(ctx, 7);
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0040FB90 sub_40FB90 -- 1556 bytes; frame 0xA0: ra sp+0x10, s0 sp+0x0 (sq)
// [fclBgPulseA] A background element handler with a 7-case event switch (jump table 0x7BBF40): 4 fades out (state 2),
// 5..7 load one of three 16-byte key sets (table 0x6AFB10) and restart; per frame: state 0 moves along the keys, then
// state 1 loops a 600-frame rotation (+22 = 0..65535, direction by flag 1), state 2 shrinks over 10 frames. Returns 0
// while moving, 1 while looping, 2 when the fade-out ends.
void sub_40FB90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x0040fb90
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a1, kBgNodeArea);
    a3 = 0x6B0000;
    a3 = addiu(a3, -1264);  // &0x6AFB10
    a1 = addiu(sp, 0x20);
    a0 = 16;
    for (;;) {
        // 0x0040fbb0
        charge(ctx, 9);
        lw(v1, a3, 0);
        lw(v0, a3, 4);
        a3 = addiu(a3, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0040fbd4
    charge(ctx, 2);
    if (a2 == 0) {
        // 0x0040fcf4
        charge(ctx, 4);
        lh(v1, s0, 24);
        v0 = 2;
        if (v1 == v0) {
            // 0x004100d8
            charge(ctx, 35);
            lh(v1, s0, 26);
            v1 = addiu(v1, 1);
            sh(v1, s0, 26);
            v1 = dsll32(v1, 16);
            v1 = dsra32(v1, 16);
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            lwc1(f2, s0, 16);
            mul_s(f0, f2, f0);
            v1 = 0x41200000;
            mtc1(v1, f1);
            div_s(f0, f0, f1);
            sub_s(f0, f2, f0);
            swc1(f0, s0, 16);
            lh(a0, s0, 12);
            lh(v1, s0, 26);
            mult(v1, a0, v1);
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            div_s(f1, f0, f1);
            mtc1(a0, f0);
            cvt_s_w(f0, f0);
            sub_s(f0, f0, f1);
            cvt_w_s(f0, f0);
            mfc1(v1, f0);
            sh(v1, s0, 12);
            lh(v1, s0, 26);
            v1 = slti(v1, 10);
            if (v1 != 0) {
                // 0x00410180
                charge(ctx, 3);
                v0 = 0;
            } else {
                // 0x00410164
                charge(ctx, 7);
                lw(a0, s0, 0);
                v1 = si(-3);
                v1 = a0 & v1;
                sw(v1, s0, 0);
                sh(zero, s0, 26);
            }
        } else {
            // 0x0040fd04
            charge(ctx, 3);
            t0 = 1;
            if (v1 == t0) {
                // 0x0040ff98
                charge(ctx, 8);
                lh(v0, s0, 26);
                v0 = addiu(v0, 1);
                sh(v0, s0, 26);
                v0 = dsll32(v0, 16);
                v0 = dsra32(v0, 16);
                v0 = slti(v0, 600);
                if (v0 == 0) {
                    // 0x0040ffb8
                    charge(ctx, 1);
                    sh(zero, s0, 26);
                }
                // 0x0040ffbc
                charge(ctx, 4);
                lw(v0, s0, 0);
                v0 = v0 & 0x1;
                if (v0 == 0) {
                    // 0x00410048
                    charge(ctx, 21);
                    lh(v1, s0, 26);
                    v0 = sll(v1, 16);
                    v0 = subu(v0, v1);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x44160000;
                    mtc1(v0, f0);
                    div_s(f1, f1, f0);
                    v0 = 0xFFFF;
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    sub_s(f1, f0, f1);
                    v0 = 0x4F000000;
                    mtc1(v0, f0);
                    c_le_s(f0, f1);
                    if (cond(ctx)) {
                        // 0x004100b4
                        charge(ctx, 6);
                        sub_s(f0, f1, f0);
                        cvt_w_s(f0, f0);
                        mfc1(v1, f0);
                        v0 = lui(0x8000);
                        v1 = v1 | v0;
                        v1 = v1 & 0xFFFF;
                    } else {
                        // 0x0041009c
                        charge(ctx, 6);
                        cvt_w_s(f0, f1);
                        mfc1(v1, f0);
                        v1 = v1 & 0xFFFF;
                    }
                    // 0x004100cc
                    charge(ctx, 3);
                    sh(v1, s0, 22);
                } else {
                    // 0x0040ffcc
                    charge(ctx, 16);
                    lh(v1, s0, 26);
                    v0 = sll(v1, 16);
                    v0 = subu(v0, v1);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x44160000;
                    mtc1(v0, f0);
                    div_s(f1, f1, f0);
                    v0 = 0x4F000000;
                    mtc1(v0, f0);
                    c_le_s(f0, f1);
                    if (cond(ctx)) {
                        // 0x00410024
                        charge(ctx, 6);
                        sub_s(f0, f1, f0);
                        cvt_w_s(f0, f0);
                        mfc1(v1, f0);
                        v0 = lui(0x8000);
                        v1 = v1 | v0;
                        v1 = v1 & 0xFFFF;
                    } else {
                        // 0x0041000c
                        charge(ctx, 6);
                        cvt_w_s(f0, f1);
                        mfc1(v1, f0);
                        v1 = v1 & 0xFFFF;
                    }
                    // 0x0041003c
                    charge(ctx, 3);
                    sh(v1, s0, 22);
                }
            L_0041018c:
                charge(ctx, 1);
                v0 = 1;
            } else {
                // 0x0040fd10
                charge(ctx, 2);
                if (v1 != 0) {
                    // 0x0040fd18
                    charge(ctx, 2);
                    goto L_0041018c;
                }
                // 0x0040fd20
                charge(ctx, 12);
                lh(v0, s0, 26);
                v0 = addiu(v0, 1);
                sh(v0, s0, 26);
                a2 = 0;
                lw(a3, s0, 4);
                a1 = addiu(s0, 8);
                lh(a0, s0, 14);
                v1 = dsll32(v0, 16);
                v1 = dsra32(v1, 16);
                v0 = slt(v1, a0);
                if (v0 == 0) {
                    // 0x0040fd50
                    charge(ctx, 8);
                    a0 = subu(v1, a0);
                    v0 = sll(a3, 4);
                    v1 = addu(v0, sp);
                    v0 = addiu(v1, 102);
                    lh(a3, v0, 0);
                    at = slt(a3, a0);
                    if (at != 0) {
                        // 0x0040fec0
                        charge(ctx, 1);
                        a2 = t0;
                    } else {
                        // 0x0040fd70
                        charge(ctx, 84);
                        lw(a3, s0, 0);
                        a3 = a3 | 0x2;
                        sw(a3, s0, 0);
                        a3 = addiu(v1, 32);
                        lh(t0, a3, 0);
                        lh(a3, v1, 96);
                        a3 = subu(a3, t0);
                        mult(a3, a0, a3);
                        mtc1(a3, f0);
                        cvt_s_w(f1, f0);
                        lh(a3, v0, 0);
                        mtc1(a3, f0);
                        cvt_s_w(f0, f0);
                        div_s(f1, f1, f0);
                        mtc1(t0, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f0, f1);
                        cvt_w_s(f0, f0);
                        mfc1(a3, f0);
                        sh(a3, a1, 0);
                        a3 = addiu(v1, 34);
                        lh(t0, a3, 0);
                        lh(a3, v1, 98);
                        a3 = subu(a3, t0);
                        mult1(a3, a0, a3);
                        mtc1(a3, f0);
                        cvt_s_w(f1, f0);
                        lh(a3, v0, 0);
                        mtc1(a3, f0);
                        cvt_s_w(f0, f0);
                        div_s(f1, f1, f0);
                        mtc1(t0, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f0, f1);
                        cvt_w_s(f0, f0);
                        mfc1(a3, f0);
                        sh(a3, a1, 2);
                        a3 = addiu(v1, 36);
                        lh(t0, a3, 0);
                        lh(a3, v1, 100);
                        a3 = subu(a3, t0);
                        mult(a3, a0, a3);
                        mtc1(a3, f0);
                        cvt_s_w(f1, f0);
                        lh(a3, v0, 0);
                        mtc1(a3, f0);
                        cvt_s_w(f0, f0);
                        div_s(f1, f1, f0);
                        mtc1(t0, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f0, f1);
                        cvt_w_s(f0, f0);
                        mfc1(a3, f0);
                        sh(a3, a1, 4);
                        a3 = addiu(v1, 40);
                        lwc1(f2, a3, 0);
                        lwc1(f0, v1, 104);
                        sub_s(f1, f0, f2);
                        mtc1(a0, f0);
                        cvt_s_w(f0, f0);
                        mul_s(f1, f0, f1);
                        lh(v0, v0, 0);
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        div_s(f0, f1, f0);
                        add_s(f0, f2, f0);
                        swc1(f0, a1, 8);
                    }
                }
                // 0x0040fec4
                charge(ctx, 2);
                if (a2 != 0) {
                    // 0x0040fecc
                    charge(ctx, 6);
                    v0 = 1;
                    sh(v0, s0, 24);
                    lw(v0, s0, 0);
                    v0 = v0 & 0x1;
                    if (v0 == 0) {
                        // 0x0040ff34
                        charge(ctx, 22);
                        lhu(v1, s0, 22);
                        v0 = sll(v1, 4);
                        v1 = subu(v0, v1);
                        v0 = sll(v1, 2);
                        v0 = addu(v1, v0);
                        v0 = sll(v0, 3);
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                        v0 = 0xFFFF;
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        div_s(f1, f1, f0);
                        v0 = 0x44160000;
                        mtc1(v0, f0);
                        sub_s(f0, f0, f1);
                        cvt_w_s(f0, f0);
                        mfc1(v0, f0);
                        sh(v0, s0, 26);
                    } else {
                        // 0x0040fee4
                        charge(ctx, 20);
                        lhu(v1, s0, 22);
                        v0 = sll(v1, 4);
                        v1 = subu(v0, v1);
                        v0 = sll(v1, 2);
                        v0 = addu(v1, v0);
                        v0 = sll(v0, 3);
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                        v0 = 0xFFFF;
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        div_s(f0, f1, f0);
                        cvt_w_s(f0, f0);
                        mfc1(v0, f0);
                        sh(v0, s0, 26);
                    }
                }
                // 0x0040ff8c
                charge(ctx, 3);
                v0 = 0;
            }
        }
    } else {
        // 0x0040fbdc
        charge(ctx, 4);
        lh(v0, a2, kBgEventId);
        at = sltiu(v0, 9);
        if (at != 0) {
            // 0x0040fbec
            charge(ctx, 7);
            v1 = 0x7C0000;
            v1 = addiu(v1, -16576);  // &0x7BBF40
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x40FC08u:  // table[4]
                // 0x0040fc08
                charge(ctx, 8);
                lw(v0, s0, 0);
                v0 = v0 | 0x1;
                sw(v0, s0, 0);
                v0 = 2;
                sh(v0, s0, 24);
                sh(zero, s0, 26);
                break;
            case 0x40FC28u:  // table[5]
                // 0x0040fc28
                charge(ctx, 16);
                a0 = addiu(s0, 8);
                a1 = addiu(sp, 0x20);
                a2 = 16;
                jal(ctx, 0x40FC34u, gen::fn_memcpy_00521250);
                lw(v1, s0, 0);
                v0 = si(-3);
                v0 = v1 & v0;
                sw(v0, s0, 0);
                v0 = v0 | 0x1;
                sw(v0, s0, 0);
                sw(zero, s0, 4);
                sh(zero, s0, 24);
                sh(zero, s0, 26);
                break;
            case 0x40FC68u:  // table[6]
                // 0x0040fc68
                charge(ctx, 17);
                a0 = addiu(s0, 8);
                a1 = addiu(sp, 0x30);
                a2 = 16;
                jal(ctx, 0x40FC74u, gen::fn_memcpy_00521250);
                lw(v1, s0, 0);
                v0 = si(-3);
                v0 = v1 & v0;
                sw(v0, s0, 0);
                v0 = v0 | 0x1;
                sw(v0, s0, 0);
                v0 = 1;
                sw(v0, s0, 4);
                sh(zero, s0, 24);
                sh(zero, s0, 26);
                break;
            case 0x40FCACu:  // table[7]
                // 0x0040fcac
                charge(ctx, 15);
                a0 = addiu(s0, 8);
                a1 = addiu(sp, 0x40);
                a2 = 16;
                jal(ctx, 0x40FCB8u, gen::fn_memcpy_00521250);
                lw(v1, s0, 0);
                v0 = si(-3);
                v0 = v1 & v0;
                sw(v0, s0, 0);
                v0 = v0 | 0x1;
                sw(v0, s0, 0);
                v0 = 2;
                sw(v0, s0, 4);
                sh(zero, s0, 24);
                sh(zero, s0, 26);
                break;
            case 0x40FCE8u:  // table[0, 1, 2, 3, 8]
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
        }
        // 0x0040fce8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00410190 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x004101B0 sub_4101B0 -- 1064 bytes; frame 0x90: ra sp+0x80, s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// [fclBgPulseDraw] When visible (flag 2): draws sprites 86..89 as a 2 x 2 quad around (x, y) scaled by +16 (252 x 233
// at scale 1) with alpha +12 (sub_40E3F0). Returns 0.
void sub_4101B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f20{ctx, 20}, f21{ctx, 21};
    // 0x004101b0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(s0, a1, kBgNodeArea);
    lw(v0, s0, 0);
    v0 = v0 & 0x2;
    if (v0 != 0) {
        // 0x004101fc
        charge(ctx, 27);
        lh(s4, s0, 8);
        lh(s3, s0, 10);
        lwc1(f20, s0, 16);
        v0 = 0x437C0000;
        mtc1(v0, f0);
        mul_s(f0, f0, f20);
        cvt_w_s(f0, f0);
        mfc1(s2, f0);
        v0 = 0x43690000;
        mtc1(v0, f0);
        mul_s(f0, f0, f20);
        cvt_w_s(f0, f0);
        mfc1(s1, f0);
        lh(v0, s0, 12);
        mtc1(v0, f0);
        cvt_s_w(f21, f0);
        s6 = subu(s3, s1);
        s5 = subu(s4, s2);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f21);
        if (cond(ctx)) {
            // 0x00410280
            charge(ctx, 6);
            sub_s(f0, f21, f0);
            cvt_w_s(f0, f0);
            mfc1(a2, f0);
            v0 = lui(0x8000);
            a2 = a2 | v0;
            a2 = a2 & 0xFF;
        } else {
            // 0x00410268
            charge(ctx, 6);
            cvt_w_s(f0, f21);
            mfc1(a2, f0);
            a2 = a2 & 0xFF;
        }
        // 0x00410298
        charge(ctx, 3);
        lhu(v0, s0, 22);
        if (i64(v0) < 0) {
            // 0x004102b8
            charge(ctx, 7);
            v1 = srl(v0, 1);
            v0 = v0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f0);
            cvt_s_w(f1, f0);
            add_s(f1, f1, f1);
        } else {
            // 0x004102a4
            charge(ctx, 5);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
        }
        // 0x004102d4
        charge(ctx, 26);
        lwc1(f0, gp, -32264);  // 0x7CAEE8
        mul_s(f1, f0, f1);
        v0 = 0xFFFF;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        div_s(f1, f1, f0);
        lwc1(f0, gp, -32560);  // 0x7CADC0
        mul_s(f13, f0, f1);
        mtc1(zero, f12);
        a0 = s5;
        a1 = s6;
        a3 = 86;
        t0 = 0;
        t1 = s2;
        t2 = s1;
        mov_s(f14, f20);
        mov_s(f15, f20);
        jal(ctx, 0x41031Cu, gen::fn_sub_40E3F0_0040e3f0);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f21);
        if (cond(ctx)) {
            // 0x00410354
            charge(ctx, 6);
            sub_s(f0, f21, f0);
            cvt_w_s(f0, f0);
            mfc1(a2, f0);
            v0 = lui(0x8000);
            a2 = a2 | v0;
            a2 = a2 & 0xFF;
        } else {
            // 0x0041033c
            charge(ctx, 6);
            cvt_w_s(f0, f21);
            mfc1(a2, f0);
            a2 = a2 & 0xFF;
        }
        // 0x0041036c
        charge(ctx, 3);
        lhu(v0, s0, 22);
        if (i64(v0) < 0) {
            // 0x0041038c
            charge(ctx, 7);
            v1 = srl(v0, 1);
            v0 = v0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f0);
            cvt_s_w(f1, f0);
            add_s(f1, f1, f1);
        } else {
            // 0x00410378
            charge(ctx, 5);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
        }
        // 0x004103a8
        charge(ctx, 26);
        lwc1(f0, gp, -32264);  // 0x7CAEE8
        mul_s(f1, f0, f1);
        v0 = 0xFFFF;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        div_s(f1, f1, f0);
        lwc1(f0, gp, -32560);  // 0x7CADC0
        mul_s(f13, f0, f1);
        mtc1(zero, f12);
        a0 = s5;
        a1 = s3;
        a3 = 87;
        t0 = 0;
        t1 = s2;
        t2 = 0;
        mov_s(f14, f20);
        mov_s(f15, f20);
        jal(ctx, 0x4103F0u, gen::fn_sub_40E3F0_0040e3f0);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f21);
        if (cond(ctx)) {
            // 0x00410428
            charge(ctx, 6);
            sub_s(f0, f21, f0);
            cvt_w_s(f0, f0);
            mfc1(a2, f0);
            v0 = lui(0x8000);
            a2 = a2 | v0;
            a2 = a2 & 0xFF;
        } else {
            // 0x00410410
            charge(ctx, 6);
            cvt_w_s(f0, f21);
            mfc1(a2, f0);
            a2 = a2 & 0xFF;
        }
        // 0x00410440
        charge(ctx, 3);
        lhu(v0, s0, 22);
        if (i64(v0) < 0) {
            // 0x00410460
            charge(ctx, 7);
            v1 = srl(v0, 1);
            v0 = v0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f0);
            cvt_s_w(f1, f0);
            add_s(f1, f1, f1);
        } else {
            // 0x0041044c
            charge(ctx, 5);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
        }
        // 0x0041047c
        charge(ctx, 26);
        lwc1(f0, gp, -32264);  // 0x7CAEE8
        mul_s(f1, f0, f1);
        v0 = 0xFFFF;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        div_s(f1, f1, f0);
        lwc1(f0, gp, -32560);  // 0x7CADC0
        mul_s(f13, f0, f1);
        mtc1(zero, f12);
        a0 = s4;
        a1 = s6;
        a3 = 88;
        t0 = 0;
        t1 = 0;
        t2 = s1;
        mov_s(f14, f20);
        mov_s(f15, f20);
        jal(ctx, 0x4104C4u, gen::fn_sub_40E3F0_0040e3f0);
        v0 = 0x4F000000;
        mtc1(v0, f0);
        c_le_s(f0, f21);
        if (cond(ctx)) {
            // 0x004104fc
            charge(ctx, 6);
            sub_s(f0, f21, f0);
            cvt_w_s(f0, f0);
            mfc1(a2, f0);
            v0 = lui(0x8000);
            a2 = a2 | v0;
            a2 = a2 & 0xFF;
        } else {
            // 0x004104e4
            charge(ctx, 6);
            cvt_w_s(f0, f21);
            mfc1(a2, f0);
            a2 = a2 & 0xFF;
        }
        // 0x00410514
        charge(ctx, 3);
        lhu(v0, s0, 22);
        if (i64(v0) < 0) {
            // 0x00410534
            charge(ctx, 7);
            v1 = srl(v0, 1);
            v0 = v0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f0);
            cvt_s_w(f1, f0);
            add_s(f1, f1, f1);
        } else {
            // 0x00410520
            charge(ctx, 5);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
        }
        // 0x00410550
        charge(ctx, 21);
        lwc1(f0, gp, -32264);  // 0x7CAEE8
        mul_s(f1, f0, f1);
        v0 = 0xFFFF;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        div_s(f1, f1, f0);
        lwc1(f0, gp, -32560);  // 0x7CADC0
        mul_s(f13, f0, f1);
        mtc1(zero, f12);
        a0 = s4;
        a1 = s3;
        a3 = 89;
        t0 = 0;
        t1 = 0;
        t2 = 0;
        mov_s(f14, f20);
        mov_s(f15, f20);
        jal(ctx, 0x410598u, gen::fn_sub_40E3F0_0040e3f0);
        v0 = 0;
    } else {
        // 0x004101f0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x004105a4 (the shared epilogue, written out on this path)
    charge(ctx, 13);
    ld(ra, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x004105E0 sub_4105E0 -- 1064 bytes; frame 0x90: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgSpotlight] A background element handler: event 1 loads key set 0, 5 / 6 key sets 1 / 2 (table 0x6AFB90) and
// copy the loop phase from the scene's key-4 element (nmListFindByKey), 4 fades out (state 3). Per frame: states 0 / 1
// move along the keys (1 -> returns 2 at the end, 0 -> starts the 1200-frame loop, state 2), state 2 counts the loop
// phase (+18), state 3 fades alpha 255 -> 0 over 10 frames and returns 2.
void sub_4105E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x004105e0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a2;
    lw(s0, a1, kBgNodeArea);
    a3 = 0x6B0000;
    a3 = addiu(a3, -1136);  // &0x6AFB90
    a2 = addiu(sp, 0x40);
    a1 = 9;
    for (;;) {
        // 0x0041060c
        charge(ctx, 9);
        lw(v1, a3, 0);
        lw(v0, a3, 4);
        a3 = addiu(a3, 8);
        a1 = addiu(a1, -1);
        sw(v1, a2, 0);
        sw(v0, a2, 4);
        a2 = addiu(a2, 8);
        if (i64(a1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00410630
    charge(ctx, 2);
    if (s1 == 0) {
        // 0x00410734
        charge(ctx, 4);
        lh(v1, s0, 12);
        v0 = 3;
        if (v1 == v0) {
            // 0x00410970
            charge(ctx, 26);
            lh(v0, s0, 14);
            v0 = addiu(v0, 1);
            sh(v0, s0, 14);
            v1 = dsll32(v0, 16);
            v1 = dsra32(v1, 16);
            v0 = sll(v1, 8);
            v0 = subu(v0, v1);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x41200000;
            mtc1(v0, f0);
            div_s(f1, f1, f0);
            v0 = 0x437F0000;
            mtc1(v0, f0);
            sub_s(f0, f0, f1);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            sh(v0, s0, 4);
            lh(v0, s0, 14);
            v0 = slti(v0, 10);
            if (v0 != 0) {
            L_004109e8:
                charge(ctx, 1);
                v0 = 1;
            } else {
                // 0x004109d8
                charge(ctx, 4);
                sh(zero, s0, 14);
                v0 = 2;
            }
        } else {
            // 0x00410744
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                // 0x00410944
                charge(ctx, 8);
                lh(v0, s0, 14);
                v0 = addiu(v0, 1);
                sh(v0, s0, 14);
                sh(v0, s0, 18);
                lh(v0, s0, 14);
                v0 = slti(v0, 1200);
                if (v0 == 0) {
                    // 0x00410964
                    charge(ctx, 3);
                    sh(zero, s0, 14);
                }
                goto L_004109e8;
            }
            // 0x00410750
            charge(ctx, 3);
            v0 = 1;
            if (v1 != v0) {
                // 0x0041075c
                charge(ctx, 2);
                if (v1 == 0) {
                    goto L_0041076c;
                }
                // 0x00410764
                charge(ctx, 2);
                goto L_004109e8;
            }
        L_0041076c:
            charge(ctx, 11);
            lh(v0, s0, 14);
            v0 = addiu(v0, 1);
            sh(v0, s0, 14);
            a1 = 0;
            lh(a2, s0, 16);
            lh(a0, s0, 6);
            v1 = dsll32(v0, 16);
            v1 = dsra32(v1, 16);
            v0 = slt(v1, a0);
            if (v0 == 0) {
                // 0x00410798
                charge(ctx, 10);
                a0 = subu(v1, a0);
                v0 = sll(a2, 1);
                v0 = addu(v0, a2);
                v0 = sll(v0, 2);
                v1 = addu(v0, sp);
                v0 = addiu(v1, 106);
                lh(t0, v0, 0);
                at = slt(t0, a0);
                if (at != 0) {
                    // 0x00410900
                    charge(ctx, 1);
                    a1 = addiu(a1, 1);
                } else {
                    // 0x004107c0
                    charge(ctx, 80);
                    a2 = addiu(v1, 64);
                    lh(a3, a2, 0);
                    lh(a2, v1, 100);
                    a2 = subu(a2, a3);
                    mult(a2, a0, a2);
                    mtc1(a2, f0);
                    cvt_s_w(f1, f0);
                    mtc1(t0, f0);
                    cvt_s_w(f0, f0);
                    div_s(f1, f1, f0);
                    mtc1(a3, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(a2, f0);
                    sh(a2, s0, 0);
                    a2 = addiu(v1, 66);
                    lh(a3, a2, 0);
                    lh(a2, v1, 102);
                    a2 = subu(a2, a3);
                    mult1(a2, a0, a2);
                    mtc1(a2, f0);
                    cvt_s_w(f1, f0);
                    lh(a2, v0, 0);
                    mtc1(a2, f0);
                    cvt_s_w(f0, f0);
                    div_s(f1, f1, f0);
                    mtc1(a3, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(a2, f0);
                    sh(a2, s0, 2);
                    a2 = addiu(v1, 68);
                    lh(a3, a2, 0);
                    lh(a2, v1, 104);
                    a2 = subu(a2, a3);
                    mult(a2, a0, a2);
                    mtc1(a2, f0);
                    cvt_s_w(f1, f0);
                    lh(a2, v0, 0);
                    mtc1(a2, f0);
                    cvt_s_w(f0, f0);
                    div_s(f1, f1, f0);
                    mtc1(a3, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(a2, f0);
                    sh(a2, s0, 4);
                    a2 = addiu(v1, 72);
                    lwc1(f2, a2, 0);
                    lwc1(f0, v1, 108);
                    sub_s(f1, f0, f2);
                    mtc1(a0, f0);
                    cvt_s_w(f0, f0);
                    mul_s(f1, f0, f1);
                    lh(v0, v0, 0);
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    div_s(f0, f1, f0);
                    add_s(f0, f2, f0);
                    swc1(f0, s0, 8);
                }
            }
            // 0x00410904
            charge(ctx, 2);
            if (a1 != 0) {
                // 0x0041090c
                charge(ctx, 4);
                lh(v1, s0, 12);
                v0 = 1;
                if (v1 != v0) {
                    // 0x00410928
                    charge(ctx, 4);
                    v0 = 2;
                    sh(v0, s0, 12);
                    lh(v0, s0, 18);
                    sh(v0, s0, 14);
                    goto L_00410938;
                }
                // 0x0041091c
                charge(ctx, 3);
                v0 = 2;
                // 0x004109ec (the shared epilogue, written out on this path)
                charge(ctx, 7);
                ld(ra, sp, 0x30);
                lq(s2, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x90);
                return;
            }
        L_00410938:
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x00410638
        charge(ctx, 4);
        lh(v1, s1, kBgEventId);
        v0 = 6;
        if (v1 != v0) {
            // 0x00410648
            charge(ctx, 3);
            v0 = 5;
            if (v1 == v0) {
                goto L_004106bc;
            }
            // 0x00410654
            charge(ctx, 3);
            v0 = 4;
            if (v1 == v0) {
                // 0x004106a8
                charge(ctx, 5);
                v0 = 3;
                sh(v0, s0, 12);
                sh(zero, s0, 14);
            } else {
                // 0x00410660
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    // 0x00410680
                    charge(ctx, 10);
                    a0 = s0;
                    a1 = addiu(sp, 0x40);
                    a2 = 12;
                    jal(ctx, 0x41068Cu, gen::fn_memcpy_00521250);
                    sh(zero, s0, 12);
                    sh(zero, s0, 14);
                    sh(zero, s0, 16);
                } else {
                    // 0x0041066c
                    charge(ctx, 3);
                    v0 = 2;
                    if (v1 != v0) {
                        // 0x00410678
                        charge(ctx, 2);
                    }
                }
            }
            goto L_00410728;
        }
    L_004106bc:
        charge(ctx, 7);
        lw(a0, a0, 8);
        a1 = addiu(a0, 4);
        a2 = 4;
        jal(ctx, 0x4106C8u, gen::fn_nmListFindByKey_003c4b50);
        if (v0 != 0) {
            // 0x004106d8
            charge(ctx, 1);
            lw(s2, v0, 20);
        }
        // 0x004106dc
        charge(ctx, 16);
        lh(v0, s1, kBgEventId);
        s1 = addiu(v0, -4);
        v0 = sll(s1, 1);
        v0 = addu(v0, s1);
        v0 = sll(v0, 2);
        v0 = addu(v0, sp);
        a0 = s0;
        a1 = addiu(v0, 64);
        a2 = 12;
        jal(ctx, 0x410700u, gen::fn_memcpy_00521250);
        sh(zero, s0, 12);
        sh(zero, s0, 14);
        sh(s1, s0, 16);
        if (s2 != 0) {
            // 0x0041071c
            charge(ctx, 3);
            lw(v0, s2, 12);
            lh(v0, v0, 18);
            sh(v0, s0, 18);
        }
    L_00410728:
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x004109ec (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x00410A10 sub_410A10 -- 792 bytes; frame 0x60: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [fclBgSpotlightDraw] Draws sprite 85 four times centred on (x, y) at scale +8 (251 x 249 at scale 1) with alpha +4
// (sub_40E3F0). Returns 0.
void sub_410A10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x00410a10
    enter(ctx, 61);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(v1, a1, kBgNodeArea);
    lwc1(f21, v1, 8);
    v0 = 0x437C0000;
    mtc1(v0, f0);
    mul_s(f1, f0, f21);
    lh(v0, v1, 0);
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    sub_s(f0, f0, f1);
    cvt_w_s(f0, f0);
    mfc1(s3, f0);
    lh(v0, v1, 2);
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    sub_s(f0, f0, f1);
    cvt_w_s(f0, f0);
    mfc1(s2, f0);
    v0 = 0x437B0000;
    mtc1(v0, f0);
    mul_s(f0, f0, f21);
    cvt_w_s(f0, f0);
    mfc1(s1, f0);
    v0 = 0x43790000;
    mtc1(v0, f0);
    mul_s(f0, f0, f21);
    cvt_w_s(f0, f0);
    mfc1(s0, f0);
    lh(v0, v1, 4);
    mtc1(v0, f0);
    cvt_s_w(f22, f0);
    lh(v0, v1, 18);
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, gp, -32264);  // 0x7CAEE8
    mul_s(f1, f0, f1);
    v0 = 0x44960000;
    mtc1(v0, f0);
    div_s(f20, f1, f0);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f22);
    if (cond(ctx)) {
        // 0x00410b1c
        charge(ctx, 6);
        sub_s(f0, f22, f0);
        cvt_w_s(f0, f0);
        mfc1(a2, f0);
        v0 = lui(0x8000);
        a2 = a2 | v0;
        a2 = a2 & 0xFF;
    } else {
        // 0x00410b04
        charge(ctx, 6);
        cvt_w_s(f0, f22);
        mfc1(a2, f0);
        a2 = a2 & 0xFF;
    }
    // 0x00410b34
    charge(ctx, 20);
    mtc1(zero, f12);
    neg_s(f1, f20);
    lwc1(f0, gp, -32560);  // 0x7CADC0
    mul_s(f13, f0, f1);
    a0 = s3;
    a1 = s2;
    a3 = 85;
    t0 = 0;
    t1 = s1;
    t2 = s0;
    mov_s(f14, f21);
    mov_s(f15, f21);
    jal(ctx, 0x410B64u, gen::fn_sub_40E3F0_0040e3f0);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f22);
    if (cond(ctx)) {
        // 0x00410b9c
        charge(ctx, 6);
        sub_s(f0, f22, f0);
        cvt_w_s(f0, f0);
        mfc1(a2, f0);
        v0 = lui(0x8000);
        a2 = a2 | v0;
        a2 = a2 & 0xFF;
    } else {
        // 0x00410b84
        charge(ctx, 6);
        cvt_w_s(f0, f22);
        mfc1(a2, f0);
        a2 = a2 & 0xFF;
    }
    // 0x00410bb4
    charge(ctx, 21);
    mtc1(zero, f12);
    lwc1(f0, gp, -32496);  // 0x7CAE00
    sub_s(f1, f0, f20);
    lwc1(f0, gp, -32560);  // 0x7CADC0
    mul_s(f13, f0, f1);
    a0 = s3;
    a1 = s2;
    a3 = 85;
    t0 = 0;
    t1 = s1;
    t2 = s0;
    mov_s(f14, f21);
    mov_s(f15, f21);
    jal(ctx, 0x410BE8u, gen::fn_sub_40E3F0_0040e3f0);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f22);
    if (cond(ctx)) {
        // 0x00410c20
        charge(ctx, 6);
        sub_s(f0, f22, f0);
        cvt_w_s(f0, f0);
        mfc1(a2, f0);
        v0 = lui(0x8000);
        a2 = a2 | v0;
        a2 = a2 & 0xFF;
    } else {
        // 0x00410c08
        charge(ctx, 6);
        cvt_w_s(f0, f22);
        mfc1(a2, f0);
        a2 = a2 & 0xFF;
    }
    // 0x00410c38
    charge(ctx, 21);
    mtc1(zero, f12);
    lwc1(f0, gp, -32260);  // 0x7CAEEC
    sub_s(f1, f0, f20);
    lwc1(f0, gp, -32560);  // 0x7CADC0
    mul_s(f13, f0, f1);
    a0 = s3;
    a1 = s2;
    a3 = 85;
    t0 = 0;
    t1 = s1;
    t2 = s0;
    mov_s(f14, f21);
    mov_s(f15, f21);
    jal(ctx, 0x410C6Cu, gen::fn_sub_40E3F0_0040e3f0);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f22);
    if (cond(ctx)) {
        // 0x00410ca4
        charge(ctx, 6);
        sub_s(f0, f22, f0);
        cvt_w_s(f0, f0);
        mfc1(a2, f0);
        v0 = lui(0x8000);
        a2 = a2 | v0;
        a2 = a2 & 0xFF;
    } else {
        // 0x00410c8c
        charge(ctx, 6);
        cvt_w_s(f0, f22);
        mfc1(a2, f0);
        a2 = a2 & 0xFF;
    }
    // 0x00410cbc
    charge(ctx, 27);
    mtc1(zero, f12);
    lwc1(f0, gp, -32408);  // 0x7CAE58
    sub_s(f1, f0, f20);
    lwc1(f0, gp, -32560);  // 0x7CADC0
    mul_s(f13, f0, f1);
    a0 = s3;
    a1 = s2;
    a3 = 85;
    t0 = 0;
    t1 = s1;
    t2 = s0;
    mov_s(f14, f21);
    mov_s(f15, f21);
    jal(ctx, 0x410CF0u, gen::fn_sub_40E3F0_0040e3f0);
    v0 = 0;
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x004110E0 sub_4110E0 -- 12 bytes; leaf frame (no stack)
// [fclBgReturn0] Returns 0 (a no-op handler in 19 table slots).
void sub_4110E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x004110e0
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x004113F0 sub_4113F0 -- 792 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclBgPanels4] A background element handler: four 20-byte panels as in sub_40F030; event 1 resets them (alpha max
// 255, slide-in), 4 slides them out; per frame they slide and fade (closed panels wait 126 frames, then -100
// restarts); returns 2 when all four are closed (+80 = 1), else 1.
void sub_4113F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004113f0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a1, kBgNodeArea);
    if (a2 != 0) {
        // 0x00411408
        charge(ctx, 4);
        lh(v1, a2, kBgEventId);
        v0 = 4;
        if (v1 == v0) {
            // 0x004114c0
            charge(ctx, 20);
            lw(v0, s0, 0);
            v0 = v0 | 0x2;
            sw(v0, s0, 0);
            v0 = v0 | 0x8;
            sw(v0, s0, 0);
            lw(v0, s0, 20);
            v0 = v0 | 0x2;
            sw(v0, s0, 20);
            v0 = v0 | 0x8;
            sw(v0, s0, 20);
            lw(v0, s0, 40);
            v0 = v0 | 0x2;
            sw(v0, s0, 40);
            v0 = v0 | 0x8;
            sw(v0, s0, 40);
            lw(v0, s0, 60);
            v0 = v0 | 0x2;
            sw(v0, s0, 60);
            v0 = v0 | 0x8;
            sw(v0, s0, 60);
        } else {
            // 0x00411418
            charge(ctx, 3);
            v0 = 2;
            if (v1 != v0) {
                // 0x00411424
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    // 0x00411438
                    charge(ctx, 34);
                    a0 = s0;
                    a1 = 0;
                    a2 = 80;
                    jal(ctx, 0x411444u, gen::fn_memset_00521408);
                    a0 = 255;
                    sh(a0, s0, 14);
                    lw(v0, s0, 0);
                    v0 = v0 | 0x1;
                    sw(v0, s0, 0);
                    v1 = si(-9);
                    v0 = v0 & v1;
                    sw(v0, s0, 0);
                    sh(a0, s0, 34);
                    lw(v0, s0, 20);
                    v0 = v0 | 0x1;
                    sw(v0, s0, 20);
                    v0 = v0 & v1;
                    sw(v0, s0, 20);
                    sh(a0, s0, 54);
                    lw(v0, s0, 40);
                    v0 = v0 | 0x1;
                    sw(v0, s0, 40);
                    v0 = v0 & v1;
                    sw(v0, s0, 40);
                    sh(a0, s0, 74);
                    lw(v0, s0, 60);
                    v0 = v0 | 0x1;
                    sw(v0, s0, 60);
                    v0 = v0 & v1;
                    sw(v0, s0, 60);
                    sh(zero, s0, 80);
                } else {
                    // 0x00411430
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x00411510
    charge(ctx, 4);
    lh(v1, s0, 80);
    v0 = 2;
    if (v1 != v0) {
        // 0x00411520
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            goto L_004116f0;
        }
        // 0x0041152c
        charge(ctx, 2);
        if (v1 != 0) {
            // 0x00411534
            charge(ctx, 2);
            goto L_004116f0;
        }
        // 0x0041153c
        charge(ctx, 13);
        lh(v0, s0, 82);
        v0 = addiu(v0, 1);
        sh(v0, s0, 82);
        a3 = 0;
        t0 = 0;
        t3 = si(-3);
        t1 = 126;
        v1 = 10;
        v0 = si(-2);
        a1 = si(-100);
        a0 = si(-5);
        for (;;) {
            // 0x004116c4
            charge(ctx, 3);
            a2 = slti(t0, 4);
            if (a2 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00411570
            charge(ctx, 8);
            a2 = sll(t0, 2);
            a2 = addu(a2, t0);
            a2 = sll(a2, 2);
            a2 = addu(s0, a2);
            lw(t4, a2, 0);
            t2 = t4 & 0x4;
            if (t2 == 0) {
                // 0x004115e4
                charge(ctx, 3);
                t2 = t4 & 0x1;
                if (t2 == 0) {
                    // 0x00411650
                    charge(ctx, 3);
                    t2 = t4 & 0x2;
                    if (t2 != 0) {
                        // 0x0041165c
                        charge(ctx, 17);
                        lh(t2, a2, 18);
                        t2 = addiu(t2, 1);
                        sh(t2, a2, 18);
                        lh(t4, a2, 14);
                        t2 = dsll32(t2, 16);
                        t2 = dsra32(t2, 16);
                        mult(t2, t4, t2);
                        div(t2, v1);
                        mflo(t2);
                        t2 = subu(t4, t2);
                        sh(t2, a2, 12);
                        lh(t2, a2, 18);
                        t2 = slti(t2, 10);
                        if (t2 == 0) {
                            // 0x004116a0
                            charge(ctx, 8);
                            lw(t2, a2, 0);
                            t2 = t2 & t3;
                            sw(t2, a2, 0);
                            t2 = t2 | 0x4;
                            sw(t2, a2, 0);
                            sh(zero, a2, 12);
                            sh(zero, a2, 18);
                            sh(t1, a2, 16);
                        }
                    }
                } else {
                    // 0x004115f0
                    charge(ctx, 16);
                    lh(t2, a2, 18);
                    t2 = addiu(t2, 1);
                    sh(t2, a2, 18);
                    lh(t4, a2, 14);
                    t2 = dsll32(t2, 16);
                    t2 = dsra32(t2, 16);
                    mult(t2, t4, t2);
                    div(t2, v1);
                    mflo(t2);
                    sh(t2, a2, 12);
                    lh(t2, a2, 18);
                    t2 = slti(t2, 10);
                    if (t2 == 0) {
                        // 0x00411630
                        charge(ctx, 8);
                        lw(t2, a2, 0);
                        t2 = t2 & v0;
                        sw(t2, a2, 0);
                        lh(t2, a2, 14);
                        sh(t2, a2, 12);
                        sh(zero, a2, 18);
                    }
                }
            } else {
                // 0x00411590
                charge(ctx, 3);
                t2 = t4 & 0x8;
                if (t2 == 0) {
                    // 0x004115a8
                    charge(ctx, 7);
                    lh(t2, a2, 16);
                    t2 = addiu(t2, -1);
                    sh(t2, a2, 16);
                    t2 = dsll32(t2, 16);
                    t2 = dsra32(t2, 16);
                    if (i64(t2) <= 0) {
                        // 0x004115c4
                        charge(ctx, 8);
                        sh(a1, a2, 16);
                        lw(t2, a2, 0);
                        t2 = t2 & a0;
                        sw(t2, a2, 0);
                        t2 = t2 | 0x1;
                        sw(t2, a2, 0);
                    }
                } else {
                    // 0x0041159c
                    charge(ctx, 3);
                    a3 = addiu(a3, 1);
                }
            }
            // 0x004116c0
            charge(ctx, 1);
            t0 = addiu(t0, 1);
        }
        // 0x004116d0
        charge(ctx, 3);
        v0 = slti(a3, 4);
        if (v0 != 0) {
            goto L_004116f0;
        }
        // 0x004116dc
        charge(ctx, 5);
        v0 = 1;
        sh(v0, s0, 80);
        v0 = 2;
        // 0x004116f4 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
L_004116f0:
    charge(ctx, 1);
    v0 = 1;
    // 0x004116f4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00411710 sub_411710 -- 124 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgPanels4Draw] Draws the four panels with sprites 97..100 (sub_40E3C0). Returns 0.
void sub_411710(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00411710
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a1, kBgNodeArea);
    s1 = 0;
    for (;;) {
        // 0x00411764
        charge(ctx, 3);
        v0 = slti(s1, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00411730
        charge(ctx, 13);
        v0 = sll(s1, 2);
        v0 = addu(v0, s1);
        v0 = sll(v0, 2);
        v0 = addu(s0, v0);
        lh(a0, v0, 4);
        lh(a1, v0, 6);
        mtc1(zero, f12);
        lbu(a2, v0, 12);
        a3 = addiu(s1, 97);
        t0 = 0;
        jal(ctx, 0x411758u, gen::fn_sub_40E3C0_0040e3c0);
        s1 = addiu(s1, 1);
    }
    // 0x00411770
    charge(ctx, 7);
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00411790 sub_411790 -- 1864 bytes; frame 0x90: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgSparkles] A background element handler with five 20-byte sparkles: events 5 / 6 / 7 load three layouts
// (positions in 1/16 px, the drift table 0x6B0020), 10 / 11 / 12 stop groups of them; per frame each sparkle drifts by
// (255 - alpha) * 64 * dir / 255, fades in over 10 frames, pulses out over 14 frames with a sine and waits 25 frames;
// returns 2 when all are stopped (+100 = 1), else 1.
void sub_411790(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12};
    // 0x00411790
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a1, kBgNodeArea);
    a3 = 0x6B0000;
    a3 = addiu(a3, 32);  // &0x6B0020
    a1 = addiu(sp, 0x60);
    a0 = 5;
    for (;;) {
        // 0x004117c0
        charge(ctx, 9);
        lw(v1, a3, 0);
        lw(v0, a3, 4);
        a3 = addiu(a3, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004117e4
    charge(ctx, 2);
    if (a2 != 0) {
        // 0x004117ec
        charge(ctx, 4);
        lh(v1, a2, kBgEventId);
        v0 = 12;
        if (v1 == v0) {
            // 0x00411b78
            charge(ctx, 10);
            lw(v0, s0, 60);
            v0 = v0 | 0x2;
            sw(v0, s0, 60);
            v0 = v0 | 0x8;
            sw(v0, s0, 60);
            lw(v0, s0, 80);
            v0 = v0 | 0x2;
            sw(v0, s0, 80);
            v0 = v0 | 0x8;
            sw(v0, s0, 80);
        } else {
            // 0x004117fc
            charge(ctx, 3);
            v0 = 7;
            if (v1 == v0) {
                // 0x00411a90
                charge(ctx, 58);
                sh(zero, s0, 100);
                sh(zero, s0, 102);
                a0 = s0;
                a1 = 0;
                a2 = 100;
                jal(ctx, 0x411AA4u, gen::fn_memset_00521408);
                lw(v0, s0, 0);
                v1 = v0 | 0x4;
                sw(v1, s0, 0);
                v0 = si(-9);
                v1 = v1 & v0;
                sw(v1, s0, 0);
                lw(v1, s0, 20);
                v1 = v1 | 0x4;
                sw(v1, s0, 20);
                v1 = v1 & v0;
                sw(v1, s0, 20);
                lw(v1, s0, 40);
                v1 = v1 | 0x4;
                sw(v1, s0, 40);
                v1 = v1 & v0;
                sw(v1, s0, 40);
                v1 = 6560;
                sh(v1, s0, 68);
                sh(v1, s0, 64);
                v1 = 672;
                sh(v1, s0, 70);
                sh(v1, s0, 66);
                a0 = 255;
                sh(a0, s0, 74);
                v1 = 2;
                sh(v1, s0, 76);
                lw(v1, s0, 60);
                v1 = v1 | 0x4;
                sw(v1, s0, 60);
                v1 = v1 | 0x1;
                sw(v1, s0, 60);
                v1 = v1 & v0;
                sw(v1, s0, 60);
                v1 = 1856;
                sh(v1, s0, 88);
                sh(v1, s0, 84);
                v1 = 5936;
                sh(v1, s0, 90);
                sh(v1, s0, 86);
                sh(a0, s0, 94);
                v1 = 6;
                sh(v1, s0, 96);
                lw(v1, s0, 80);
                v1 = v1 | 0x4;
                sw(v1, s0, 80);
                v1 = v1 | 0x1;
                sw(v1, s0, 80);
                v0 = v1 & v0;
                sw(v0, s0, 80);
            } else {
                // 0x00411808
                charge(ctx, 3);
                v0 = 11;
                if (v1 == v0) {
                    // 0x00411a60
                    charge(ctx, 12);
                    lw(v0, s0, 60);
                    v0 = v0 | 0x2;
                    sw(v0, s0, 60);
                    v0 = v0 | 0x8;
                    sw(v0, s0, 60);
                    lw(v0, s0, 80);
                    v0 = v0 | 0x2;
                    sw(v0, s0, 80);
                    v0 = v0 | 0x8;
                    sw(v0, s0, 80);
                } else {
                    // 0x00411814
                    charge(ctx, 3);
                    v0 = 6;
                    if (v1 == v0) {
                        // 0x00411978
                        charge(ctx, 58);
                        sh(zero, s0, 100);
                        sh(zero, s0, 102);
                        a0 = s0;
                        a1 = 0;
                        a2 = 100;
                        jal(ctx, 0x41198Cu, gen::fn_memset_00521408);
                        lw(v0, s0, 0);
                        v1 = v0 | 0x4;
                        sw(v1, s0, 0);
                        v0 = si(-9);
                        v1 = v1 & v0;
                        sw(v1, s0, 0);
                        lw(v1, s0, 20);
                        v1 = v1 | 0x4;
                        sw(v1, s0, 20);
                        v1 = v1 & v0;
                        sw(v1, s0, 20);
                        lw(v1, s0, 40);
                        v1 = v1 | 0x4;
                        sw(v1, s0, 40);
                        v1 = v1 & v0;
                        sw(v1, s0, 40);
                        v1 = 6880;
                        sh(v1, s0, 68);
                        sh(v1, s0, 64);
                        v1 = 624;
                        sh(v1, s0, 70);
                        sh(v1, s0, 66);
                        a0 = 255;
                        sh(a0, s0, 74);
                        v1 = 2;
                        sh(v1, s0, 76);
                        lw(v1, s0, 60);
                        v1 = v1 | 0x4;
                        sw(v1, s0, 60);
                        v1 = v1 | 0x1;
                        sw(v1, s0, 60);
                        v1 = v1 & v0;
                        sw(v1, s0, 60);
                        v1 = 1856;
                        sh(v1, s0, 88);
                        sh(v1, s0, 84);
                        v1 = 5872;
                        sh(v1, s0, 90);
                        sh(v1, s0, 86);
                        sh(a0, s0, 94);
                        v1 = 6;
                        sh(v1, s0, 96);
                        lw(v1, s0, 80);
                        v1 = v1 | 0x4;
                        sw(v1, s0, 80);
                        v1 = v1 | 0x1;
                        sw(v1, s0, 80);
                        v0 = v1 & v0;
                        sw(v0, s0, 80);
                    } else {
                        // 0x00411820
                        charge(ctx, 3);
                        v0 = 10;
                        if (v1 == v0) {
                            // 0x00411934
                            charge(ctx, 17);
                            lw(v0, s0, 0);
                            v0 = v0 | 0x2;
                            sw(v0, s0, 0);
                            v0 = v0 | 0x8;
                            sw(v0, s0, 0);
                            lw(v0, s0, 20);
                            v0 = v0 | 0x2;
                            sw(v0, s0, 20);
                            v0 = v0 | 0x8;
                            sw(v0, s0, 20);
                            lw(v0, s0, 40);
                            v0 = v0 | 0x2;
                            sw(v0, s0, 40);
                            v0 = v0 | 0x8;
                            sw(v0, s0, 40);
                        } else {
                            // 0x0041182c
                            charge(ctx, 3);
                            v0 = 5;
                            if (v1 == v0) {
                                // 0x0041184c
                                charge(ctx, 58);
                                sh(zero, s0, 100);
                                sh(zero, s0, 102);
                                a0 = s0;
                                a1 = 0;
                                a2 = 100;
                                jal(ctx, 0x411860u, gen::fn_memset_00521408);
                                v0 = 7152;
                                sh(v0, s0, 8);
                                sh(v0, s0, 4);
                                v0 = 976;
                                sh(v0, s0, 10);
                                sh(v0, s0, 6);
                                a0 = 255;
                                sh(a0, s0, 14);
                                v0 = 2;
                                sh(v0, s0, 16);
                                lw(v0, s0, 0);
                                v0 = v0 | 0x4;
                                sw(v0, s0, 0);
                                v0 = v0 | 0x1;
                                sw(v0, s0, 0);
                                v1 = si(-9);
                                v0 = v0 & v1;
                                sw(v0, s0, 0);
                                v0 = 2832;
                                sh(v0, s0, 28);
                                sh(v0, s0, 24);
                                v0 = 784;
                                sh(v0, s0, 30);
                                sh(v0, s0, 26);
                                sh(a0, s0, 34);
                                v0 = 6;
                                sh(v0, s0, 36);
                                lw(v0, s0, 20);
                                v0 = v0 | 0x4;
                                sw(v0, s0, 20);
                                v0 = v0 | 0x1;
                                sw(v0, s0, 20);
                                v0 = v0 & v1;
                                sw(v0, s0, 20);
                                v0 = 8160;
                                sh(v0, s0, 48);
                                sh(v0, s0, 44);
                                v0 = 4064;
                                sh(v0, s0, 50);
                                sh(v0, s0, 46);
                                sh(a0, s0, 54);
                                sh(zero, s0, 56);
                                lw(v0, s0, 40);
                                v0 = v0 | 0x4;
                                sw(v0, s0, 40);
                                v0 = v0 | 0x1;
                                sw(v0, s0, 40);
                                v0 = v0 & v1;
                                sw(v0, s0, 40);
                            } else {
                                // 0x00411838
                                charge(ctx, 3);
                                v0 = 2;
                                if (v1 != v0) {
                                    // 0x00411844
                                    charge(ctx, 2);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // 0x00411ba0
    charge(ctx, 4);
    lh(v1, s0, 100);
    v0 = 2;
    if (v1 != v0) {
        // 0x00411bb0
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            goto L_00411eb0;
        }
        // 0x00411bbc
        charge(ctx, 2);
        if (v1 != 0) {
            // 0x00411bc4
            charge(ctx, 2);
            goto L_00411eb0;
        }
        // 0x00411bcc
        charge(ctx, 4);
        s3 = 0;
        s4 = 0;
        for (;;) {
            // 0x00411e84
            charge(ctx, 3);
            v0 = slti(s4, 5);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00411bdc
            charge(ctx, 8);
            v0 = sll(s4, 2);
            v0 = addu(v0, s4);
            v0 = sll(v0, 2);
            s2 = addu(s0, v0);
            lw(v1, s2, 0);
            v0 = v1 & 0x4;
            if (v0 == 0) {
                // 0x00411c64
                charge(ctx, 8);
                lh(v0, s2, 16);
                v0 = addiu(v0, 1);
                sh(v0, s2, 16);
                v0 = dsll32(v0, 16);
                v0 = dsra32(v0, 16);
                v0 = slti(v0, 80);
                if (v0 == 0) {
                    // 0x00411c84
                    charge(ctx, 4);
                    lw(v1, s2, 0);
                    v0 = v1 & 0x2;
                    if (v0 == 0) {
                        // 0x00411c94
                        charge(ctx, 2);
                        v0 = v1 | 0x2;
                        sw(v0, s2, 0);
                    }
                }
                // 0x00411c9c
                charge(ctx, 49);
                v0 = sll(s4, 3);
                v0 = addu(v0, sp);
                a0 = addiu(v0, 96);
                lh(v0, s2, 12);
                v1 = 255;
                v0 = subu(v1, v0);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x42800000;
                mtc1(v0, f3);
                lwc1(f0, a0, 0);
                mul_s(f0, f3, f0);
                mul_s(f0, f1, f0);
                v0 = 0x437F0000;
                mtc1(v0, f2);
                div_s(f1, f0, f2);
                lh(v0, s2, 4);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(v0, f0);
                sh(v0, s2, 4);
                lh(v0, s2, 12);
                v0 = subu(v1, v0);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, a0, 4);
                mul_s(f0, f3, f0);
                mul_s(f0, f1, f0);
                div_s(f1, f0, f2);
                lh(v0, s2, 6);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(v0, f0);
                sh(v0, s2, 6);
                lw(v1, s2, 0);
                v0 = v1 & 0x1;
                if (v0 == 0) {
                    // 0x00411dc0
                    charge(ctx, 3);
                    v0 = v1 & 0x2;
                    if (v0 != 0) {
                        // 0x00411dcc
                        charge(ctx, 35);
                        lh(v0, s2, 18);
                        v0 = addiu(v0, 1);
                        sh(v0, s2, 18);
                        lh(s1, s2, 14);
                        v0 = dsll32(v0, 16);
                        v0 = dsra32(v0, 16);
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                        lwc1(f0, gp, -32496);  // 0x7CAE00
                        mul_s(f1, f0, f1);
                        v0 = 0x41600000;
                        mtc1(v0, f0);
                        div_s(f12, f1, f0);
                        jal(ctx, 0x411E14u, gen::fn_sinf_0052e878);
                        mtc1(s1, f1);
                        cvt_s_w(f2, f1);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        msub_s(f0, f2, f0);
                        cvt_w_s(f0, f0);
                        mfc1(v0, f0);
                        sh(v0, s2, 12);
                        lh(v0, s2, 18);
                        v0 = slti(v0, 14);
                        if (v0 == 0) {
                            // 0x00411e58
                            charge(ctx, 10);
                            lw(v1, s2, 0);
                            v0 = si(-3);
                            v0 = v1 & v0;
                            sw(v0, s2, 0);
                            v0 = v0 | 0x4;
                            sw(v0, s2, 0);
                            sh(zero, s2, 12);
                            sh(zero, s2, 18);
                            v0 = 25;
                            sh(v0, s2, 16);
                        }
                    }
                } else {
                    // 0x00411d60
                    charge(ctx, 15);
                    lh(v0, s2, 18);
                    v0 = addiu(v0, 1);
                    sh(v0, s2, 18);
                    lh(v1, s2, 14);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                    mult(v1, v1, v0);
                    v0 = 10;
                    div(v1, v0);
                    mflo(v0);
                    sh(v0, s2, 12);
                    lh(v0, s2, 18);
                    v0 = slti(v0, 10);
                    if (v0 == 0) {
                        // 0x00411d9c
                        charge(ctx, 9);
                        lw(v1, s2, 0);
                        v0 = si(-2);
                        v0 = v1 & v0;
                        sw(v0, s2, 0);
                        lh(v0, s2, 14);
                        sh(v0, s2, 12);
                        sh(zero, s2, 18);
                    }
                }
            } else {
                // 0x00411bfc
                charge(ctx, 3);
                v0 = v1 & 0x8;
                if (v0 == 0) {
                    // 0x00411c14
                    charge(ctx, 7);
                    lh(v0, s2, 16);
                    v0 = addiu(v0, -1);
                    sh(v0, s2, 16);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                    if (i64(v0) <= 0) {
                        // 0x00411c30
                        charge(ctx, 13);
                        sh(zero, s2, 16);
                        lw(v1, s2, 0);
                        v0 = si(-5);
                        v0 = v1 & v0;
                        sw(v0, s2, 0);
                        v0 = v0 | 0x1;
                        sw(v0, s2, 0);
                        lh(v0, s2, 8);
                        sh(v0, s2, 4);
                        lh(v0, s2, 10);
                        sh(v0, s2, 6);
                    }
                } else {
                    // 0x00411c08
                    charge(ctx, 3);
                    s3 = addiu(s3, 1);
                }
            }
            // 0x00411e80
            charge(ctx, 1);
            s4 = addiu(s4, 1);
        }
        // 0x00411e90
        charge(ctx, 3);
        v0 = slti(s3, 5);
        if (v0 != 0) {
            goto L_00411eb0;
        }
        // 0x00411e9c
        charge(ctx, 5);
        v0 = 1;
        sh(v0, s0, 100);
        v0 = 2;
        // 0x00411eb4 (the shared epilogue, written out on this path)
        charge(ctx, 9);
        ld(ra, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x90);
        return;
    }
L_00411eb0:
    charge(ctx, 1);
    v0 = 1;
    // 0x00411eb4 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x004120A0 sub_4120A0 -- 1236 bytes; frame 0x120: ra sp+0x10, s0 sp+0x0 (sq)
// [fclBgSlide5B] As sub_40F5D0 with the key tables 0x6B0450 (in) / 0x6B04D0 (out).
void sub_4120A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x004120a0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x120);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a1, kBgNodeArea);
    a3 = 0x6B0000;
    a3 = addiu(a3, 1104);  // &0x6B0450
    a1 = addiu(sp, 0xA0);
    a0 = 15;
    for (;;) {
        // 0x004120c0
        charge(ctx, 9);
        lw(v1, a3, 0);
        lw(v0, a3, 4);
        a3 = addiu(a3, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004120e4
    charge(ctx, 4);
    a3 = 0x6B0000;
    a3 = addiu(a3, 1232);  // &0x6B04D0
    a1 = addiu(sp, 0x20);
    a0 = 15;
    for (;;) {
        // 0x004120f4
        charge(ctx, 9);
        lw(v1, a3, 0);
        lw(v0, a3, 4);
        a3 = addiu(a3, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00412118
    charge(ctx, 2);
    if (a2 != 0) {
        // 0x00412120
        charge(ctx, 4);
        lh(v1, a2, kBgEventId);
        v0 = 4;
        if (v1 == v0) {
            // 0x00412174
            charge(ctx, 8);
            a0 = s0;
            a1 = addiu(sp, 0x20);
            a2 = 60;
            jal(ctx, 0x412180u, gen::fn_memcpy_00521250);
            v0 = 2;
            sh(v0, s0, 60);
            sh(zero, s0, 62);
        } else {
            // 0x00412130
            charge(ctx, 3);
            v0 = 2;
            if (v1 != v0) {
                // 0x0041213c
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    // 0x00412150
                    charge(ctx, 9);
                    a0 = s0;
                    a1 = addiu(sp, 0xA0);
                    a2 = 60;
                    jal(ctx, 0x41215Cu, gen::fn_memcpy_00521250);
                    sh(zero, s0, 60);
                    sh(zero, s0, 62);
                } else {
                    // 0x00412148
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x00412194
    charge(ctx, 4);
    lh(v1, s0, 60);
    v0 = 2;
    if (v1 == v0) {
        // 0x00412388
        charge(ctx, 7);
        lh(v0, s0, 62);
        v0 = addiu(v0, 1);
        sh(v0, s0, 62);
        a3 = 0;
        a2 = 0;
        for (;;) {
            // 0x00412520
            charge(ctx, 3);
            v0 = slti(a2, 5);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x004123a4
            charge(ctx, 9);
            v0 = sll(a2, 1);
            v0 = addu(v0, a2);
            t0 = sll(v0, 2);
            a1 = addu(s0, t0);
            lh(a0, a1, 6);
            lh(v1, s0, 62);
            v0 = slt(v1, a0);
            if (v0 == 0) {
                // 0x004123c8
                charge(ctx, 8);
                a0 = subu(v1, a0);
                v0 = addu(t0, sp);
                v1 = addiu(v0, 32);
                v0 = addiu(v1, 66);
                lh(t2, v1, 66);
                at = slt(t2, a0);
                if (at != 0) {
                    // 0x00412518
                    charge(ctx, 1);
                    a3 = addiu(a3, 1);
                } else {
                    // 0x004123e8
                    charge(ctx, 76);
                    lh(t1, v1, 0);
                    lh(t0, v1, 60);
                    t0 = subu(t0, t1);
                    mult(t0, a0, t0);
                    mtc1(t0, f0);
                    cvt_s_w(f1, f0);
                    mtc1(t2, f0);
                    cvt_s_w(f0, f0);
                    div_s(f1, f1, f0);
                    mtc1(t1, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(t0, f0);
                    sh(t0, a1, 0);
                    lh(t1, v1, 2);
                    lh(t0, v1, 62);
                    t0 = subu(t0, t1);
                    mult1(t0, a0, t0);
                    mtc1(t0, f0);
                    cvt_s_w(f1, f0);
                    lh(t0, v0, 0);
                    mtc1(t0, f0);
                    cvt_s_w(f0, f0);
                    div_s(f1, f1, f0);
                    mtc1(t1, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(t0, f0);
                    sh(t0, a1, 2);
                    lh(t1, v1, 4);
                    lh(t0, v1, 64);
                    t0 = subu(t0, t1);
                    mult(t0, a0, t0);
                    mtc1(t0, f0);
                    cvt_s_w(f1, f0);
                    lh(t0, v0, 0);
                    mtc1(t0, f0);
                    cvt_s_w(f0, f0);
                    div_s(f1, f1, f0);
                    mtc1(t1, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(t0, f0);
                    sh(t0, a1, 4);
                    lwc1(f2, v1, 8);
                    lwc1(f0, v1, 68);
                    sub_s(f1, f0, f2);
                    mtc1(a0, f0);
                    cvt_s_w(f0, f0);
                    mul_s(f1, f0, f1);
                    lh(v0, v0, 0);
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    div_s(f0, f1, f0);
                    add_s(f0, f2, f0);
                    swc1(f0, a1, 8);
                }
            }
            // 0x0041251c
            charge(ctx, 1);
            a2 = addiu(a2, 1);
        }
        // 0x0041252c
        charge(ctx, 3);
        v0 = slti(a3, 5);
        if (v0 != 0) {
            // 0x00412550
            charge(ctx, 3);
            v0 = 0;
        } else {
            // 0x00412538
            charge(ctx, 6);
            v0 = 1;
            sh(v0, s0, 60);
            sh(zero, s0, 62);
            v0 = 2;
        }
    } else {
        // 0x004121a4
        charge(ctx, 3);
        v0 = 1;
        if (v1 != v0) {
            // 0x004121b0
            charge(ctx, 2);
            if (v1 != 0) {
                // 0x004121b8
                charge(ctx, 2);
                goto L_0041255c;
            }
            // 0x004121c0
            charge(ctx, 7);
            lh(v0, s0, 62);
            v0 = addiu(v0, 1);
            sh(v0, s0, 62);
            a2 = 0;
            a3 = 0;
            for (;;) {
                // 0x00412358
                charge(ctx, 3);
                v0 = slti(a3, 5);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x004121dc
                charge(ctx, 9);
                v0 = sll(a3, 1);
                v0 = addu(v0, a3);
                t0 = sll(v0, 2);
                a1 = addu(s0, t0);
                lh(a0, a1, 6);
                lh(v1, s0, 62);
                v0 = slt(v1, a0);
                if (v0 == 0) {
                    // 0x00412200
                    charge(ctx, 8);
                    a0 = subu(v1, a0);
                    v0 = addu(t0, sp);
                    v1 = addiu(v0, 160);
                    v0 = addiu(v1, 66);
                    lh(t2, v1, 66);
                    at = slt(t2, a0);
                    if (at != 0) {
                        // 0x00412350
                        charge(ctx, 1);
                        a2 = addiu(a2, 1);
                    } else {
                        // 0x00412220
                        charge(ctx, 76);
                        lh(t1, v1, 0);
                        lh(t0, v1, 60);
                        t0 = subu(t0, t1);
                        mult(t0, a0, t0);
                        mtc1(t0, f0);
                        cvt_s_w(f1, f0);
                        mtc1(t2, f0);
                        cvt_s_w(f0, f0);
                        div_s(f1, f1, f0);
                        mtc1(t1, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f0, f1);
                        cvt_w_s(f0, f0);
                        mfc1(t0, f0);
                        sh(t0, a1, 0);
                        lh(t1, v1, 2);
                        lh(t0, v1, 62);
                        t0 = subu(t0, t1);
                        mult1(t0, a0, t0);
                        mtc1(t0, f0);
                        cvt_s_w(f1, f0);
                        lh(t0, v0, 0);
                        mtc1(t0, f0);
                        cvt_s_w(f0, f0);
                        div_s(f1, f1, f0);
                        mtc1(t1, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f0, f1);
                        cvt_w_s(f0, f0);
                        mfc1(t0, f0);
                        sh(t0, a1, 2);
                        lh(t1, v1, 4);
                        lh(t0, v1, 64);
                        t0 = subu(t0, t1);
                        mult(t0, a0, t0);
                        mtc1(t0, f0);
                        cvt_s_w(f1, f0);
                        lh(t0, v0, 0);
                        mtc1(t0, f0);
                        cvt_s_w(f0, f0);
                        div_s(f1, f1, f0);
                        mtc1(t1, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f0, f1);
                        cvt_w_s(f0, f0);
                        mfc1(t0, f0);
                        sh(t0, a1, 4);
                        lwc1(f2, v1, 8);
                        lwc1(f0, v1, 68);
                        sub_s(f1, f0, f2);
                        mtc1(a0, f0);
                        cvt_s_w(f0, f0);
                        mul_s(f1, f0, f1);
                        lh(v0, v0, 0);
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        div_s(f0, f1, f0);
                        add_s(f0, f2, f0);
                        swc1(f0, a1, 8);
                    }
                }
                // 0x00412354
                charge(ctx, 1);
                a3 = addiu(a3, 1);
            }
            // 0x00412364
            charge(ctx, 3);
            v0 = slti(a2, 5);
            if (v0 == 0) {
                // 0x00412370
                charge(ctx, 3);
                v0 = 1;
                sh(v0, s0, 60);
                sh(zero, s0, 62);
            }
            // 0x0041237c
            charge(ctx, 3);
            v0 = 0;
            // 0x00412560 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(ra, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x120);
            return;
        }
    L_0041255c:
        charge(ctx, 1);
        v0 = 1;
    }
    // 0x00412560 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x120);
}

// 0x00412610 sub_412610 -- 1236 bytes; frame 0xE0: ra sp+0x10, s0 sp+0x0 (sq)
// [fclBgSlide4] As sub_40F5D0 with four keys (48 bytes; tables 0x6B0A00 / 0x6B0A60, state +48).
void sub_412610(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x00412610
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a1, kBgNodeArea);
    a3 = 0x6B0000;
    a3 = addiu(a3, 2560);  // &0x6B0A00
    a1 = addiu(sp, 0x80);
    a0 = 12;
    for (;;) {
        // 0x00412630
        charge(ctx, 9);
        lw(v1, a3, 0);
        lw(v0, a3, 4);
        a3 = addiu(a3, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00412654
    charge(ctx, 4);
    a3 = 0x6B0000;
    a3 = addiu(a3, 2656);  // &0x6B0A60
    a1 = addiu(sp, 0x20);
    a0 = 12;
    for (;;) {
        // 0x00412664
        charge(ctx, 9);
        lw(v1, a3, 0);
        lw(v0, a3, 4);
        a3 = addiu(a3, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00412688
    charge(ctx, 2);
    if (a2 != 0) {
        // 0x00412690
        charge(ctx, 4);
        lh(v1, a2, kBgEventId);
        v0 = 4;
        if (v1 == v0) {
            // 0x004126e4
            charge(ctx, 8);
            a0 = s0;
            a1 = addiu(sp, 0x20);
            a2 = 48;
            jal(ctx, 0x4126F0u, gen::fn_memcpy_00521250);
            v0 = 2;
            sh(v0, s0, 48);
            sh(zero, s0, 50);
        } else {
            // 0x004126a0
            charge(ctx, 3);
            v0 = 2;
            if (v1 != v0) {
                // 0x004126ac
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    // 0x004126c0
                    charge(ctx, 9);
                    a0 = s0;
                    a1 = addiu(sp, 0x80);
                    a2 = 48;
                    jal(ctx, 0x4126CCu, gen::fn_memcpy_00521250);
                    sh(zero, s0, 48);
                    sh(zero, s0, 50);
                } else {
                    // 0x004126b8
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x00412704
    charge(ctx, 4);
    lh(v1, s0, 48);
    v0 = 2;
    if (v1 == v0) {
        // 0x004128f8
        charge(ctx, 7);
        lh(v0, s0, 50);
        v0 = addiu(v0, 1);
        sh(v0, s0, 50);
        a3 = 0;
        a2 = 0;
        for (;;) {
            // 0x00412a90
            charge(ctx, 3);
            v0 = slti(a2, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00412914
            charge(ctx, 9);
            v0 = sll(a2, 1);
            v0 = addu(v0, a2);
            t0 = sll(v0, 2);
            a1 = addu(s0, t0);
            lh(a0, a1, 6);
            lh(v1, s0, 50);
            v0 = slt(v1, a0);
            if (v0 == 0) {
                // 0x00412938
                charge(ctx, 8);
                a0 = subu(v1, a0);
                v0 = addu(t0, sp);
                v1 = addiu(v0, 32);
                v0 = addiu(v1, 54);
                lh(t2, v1, 54);
                at = slt(t2, a0);
                if (at != 0) {
                    // 0x00412a88
                    charge(ctx, 1);
                    a3 = addiu(a3, 1);
                } else {
                    // 0x00412958
                    charge(ctx, 76);
                    lh(t1, v1, 0);
                    lh(t0, v1, 48);
                    t0 = subu(t0, t1);
                    mult(t0, a0, t0);
                    mtc1(t0, f0);
                    cvt_s_w(f1, f0);
                    mtc1(t2, f0);
                    cvt_s_w(f0, f0);
                    div_s(f1, f1, f0);
                    mtc1(t1, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(t0, f0);
                    sh(t0, a1, 0);
                    lh(t1, v1, 2);
                    lh(t0, v1, 50);
                    t0 = subu(t0, t1);
                    mult1(t0, a0, t0);
                    mtc1(t0, f0);
                    cvt_s_w(f1, f0);
                    lh(t0, v0, 0);
                    mtc1(t0, f0);
                    cvt_s_w(f0, f0);
                    div_s(f1, f1, f0);
                    mtc1(t1, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(t0, f0);
                    sh(t0, a1, 2);
                    lh(t1, v1, 4);
                    lh(t0, v1, 52);
                    t0 = subu(t0, t1);
                    mult(t0, a0, t0);
                    mtc1(t0, f0);
                    cvt_s_w(f1, f0);
                    lh(t0, v0, 0);
                    mtc1(t0, f0);
                    cvt_s_w(f0, f0);
                    div_s(f1, f1, f0);
                    mtc1(t1, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(t0, f0);
                    sh(t0, a1, 4);
                    lwc1(f2, v1, 8);
                    lwc1(f0, v1, 56);
                    sub_s(f1, f0, f2);
                    mtc1(a0, f0);
                    cvt_s_w(f0, f0);
                    mul_s(f1, f0, f1);
                    lh(v0, v0, 0);
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    div_s(f0, f1, f0);
                    add_s(f0, f2, f0);
                    swc1(f0, a1, 8);
                }
            }
            // 0x00412a8c
            charge(ctx, 1);
            a2 = addiu(a2, 1);
        }
        // 0x00412a9c
        charge(ctx, 3);
        v0 = slti(a3, 4);
        if (v0 != 0) {
            // 0x00412ac0
            charge(ctx, 3);
            v0 = 0;
        } else {
            // 0x00412aa8
            charge(ctx, 6);
            v0 = 1;
            sh(v0, s0, 48);
            sh(zero, s0, 50);
            v0 = 2;
        }
    } else {
        // 0x00412714
        charge(ctx, 3);
        v0 = 1;
        if (v1 != v0) {
            // 0x00412720
            charge(ctx, 2);
            if (v1 != 0) {
                // 0x00412728
                charge(ctx, 2);
                goto L_00412acc;
            }
            // 0x00412730
            charge(ctx, 7);
            lh(v0, s0, 50);
            v0 = addiu(v0, 1);
            sh(v0, s0, 50);
            a2 = 0;
            a3 = 0;
            for (;;) {
                // 0x004128c8
                charge(ctx, 3);
                v0 = slti(a3, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0041274c
                charge(ctx, 9);
                v0 = sll(a3, 1);
                v0 = addu(v0, a3);
                t0 = sll(v0, 2);
                a1 = addu(s0, t0);
                lh(a0, a1, 6);
                lh(v1, s0, 50);
                v0 = slt(v1, a0);
                if (v0 == 0) {
                    // 0x00412770
                    charge(ctx, 8);
                    a0 = subu(v1, a0);
                    v0 = addu(t0, sp);
                    v1 = addiu(v0, 128);
                    v0 = addiu(v1, 54);
                    lh(t2, v1, 54);
                    at = slt(t2, a0);
                    if (at != 0) {
                        // 0x004128c0
                        charge(ctx, 1);
                        a2 = addiu(a2, 1);
                    } else {
                        // 0x00412790
                        charge(ctx, 76);
                        lh(t1, v1, 0);
                        lh(t0, v1, 48);
                        t0 = subu(t0, t1);
                        mult(t0, a0, t0);
                        mtc1(t0, f0);
                        cvt_s_w(f1, f0);
                        mtc1(t2, f0);
                        cvt_s_w(f0, f0);
                        div_s(f1, f1, f0);
                        mtc1(t1, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f0, f1);
                        cvt_w_s(f0, f0);
                        mfc1(t0, f0);
                        sh(t0, a1, 0);
                        lh(t1, v1, 2);
                        lh(t0, v1, 50);
                        t0 = subu(t0, t1);
                        mult1(t0, a0, t0);
                        mtc1(t0, f0);
                        cvt_s_w(f1, f0);
                        lh(t0, v0, 0);
                        mtc1(t0, f0);
                        cvt_s_w(f0, f0);
                        div_s(f1, f1, f0);
                        mtc1(t1, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f0, f1);
                        cvt_w_s(f0, f0);
                        mfc1(t0, f0);
                        sh(t0, a1, 2);
                        lh(t1, v1, 4);
                        lh(t0, v1, 52);
                        t0 = subu(t0, t1);
                        mult(t0, a0, t0);
                        mtc1(t0, f0);
                        cvt_s_w(f1, f0);
                        lh(t0, v0, 0);
                        mtc1(t0, f0);
                        cvt_s_w(f0, f0);
                        div_s(f1, f1, f0);
                        mtc1(t1, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f0, f1);
                        cvt_w_s(f0, f0);
                        mfc1(t0, f0);
                        sh(t0, a1, 4);
                        lwc1(f2, v1, 8);
                        lwc1(f0, v1, 56);
                        sub_s(f1, f0, f2);
                        mtc1(a0, f0);
                        cvt_s_w(f0, f0);
                        mul_s(f1, f0, f1);
                        lh(v0, v0, 0);
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        div_s(f0, f1, f0);
                        add_s(f0, f2, f0);
                        swc1(f0, a1, 8);
                    }
                }
                // 0x004128c4
                charge(ctx, 1);
                a3 = addiu(a3, 1);
            }
            // 0x004128d4
            charge(ctx, 3);
            v0 = slti(a2, 4);
            if (v0 == 0) {
                // 0x004128e0
                charge(ctx, 3);
                v0 = 1;
                sh(v0, s0, 48);
                sh(zero, s0, 50);
            }
            // 0x004128ec
            charge(ctx, 3);
            v0 = 0;
            // 0x00412ad0 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(ra, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0xE0);
            return;
        }
    L_00412acc:
        charge(ctx, 1);
        v0 = 1;
    }
    // 0x00412ad0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xE0);
}

// 0x00412AF0 sub_412AF0 -- 200 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgDraw4] Draws four sprites (ids from the float-encoded table 0x6B0AC0) at the four keys' positions and alpha
// (sub_40E3F0). Returns 0.
void sub_412AF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15};
    // 0x00412af0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a1, kBgNodeArea);
    v0 = 0x6B0000;
    lwc1(f3, v0, 2752);  // 0x6B0AC0
    v0 = 0x6B0000;
    lwc1(f2, v0, 2756);  // 0x6B0AC4
    v0 = 0x6B0000;
    lwc1(f1, v0, 2760);  // 0x6B0AC8
    v0 = 0x6B0000;
    lwc1(f0, v0, 2764);  // 0x6B0ACC
    swc1(f3, sp, 0x30);
    swc1(f2, sp, 0x34);
    swc1(f1, sp, 0x38);
    swc1(f0, sp, 0x3C);
    s1 = 0;
    for (;;) {
        // 0x00412b90
        charge(ctx, 3);
        v0 = slti(s1, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00412b40
        charge(ctx, 20);
        v0 = sll(s1, 1);
        v0 = addu(v0, s1);
        v0 = sll(v0, 2);
        v0 = addu(s0, v0);
        lwc1(f14, v0, 8);
        lh(a0, v0, 0);
        lh(a1, v0, 2);
        mtc1(zero, f12);
        lbu(a2, v0, 4);
        v0 = sll(s1, 2);
        v0 = addu(v0, sp);
        lw(a3, v0, 48);
        t0 = 0;
        t1 = 0;
        t2 = 0;
        mov_s(f13, f12);
        mov_s(f15, f14);
        jal(ctx, 0x412B84u, gen::fn_sub_40E3F0_0040e3f0);
        s1 = addiu(s1, 1);
    }
    // 0x00412b9c
    charge(ctx, 7);
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00412BC0 sub_412BC0 -- 1092 bytes; frame 0x330: ra sp+0x10, s0 sp+0x0 (sq)
// [fclBgOrbit] A background element handler: events 1 / 4 / 5 / 10 pick one of four key sets (two tables, 0x6B0AD0 and
// 0x6B0CB0, in / out halves; +124 = the set) and copy its keys; state 0 moves the keys toward the set's second half,
// then state 1 spins their angle (+8 += step, wrapped by 2 pi 0x7CAE00). Returns 2 when an odd set (an "out" move)
// finishes, 1 while spinning, else 0.
void sub_412BC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x00412bc0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x330);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a1, kBgNodeArea);
    t0 = 0x6B0000;
    t0 = addiu(t0, 2768);  // &0x6B0AD0
    a3 = addiu(sp, 0x150);
    a1 = 60;
    for (;;) {
        // 0x00412be0
        charge(ctx, 9);
        lw(a0, t0, 0);
        lw(v1, t0, 4);
        t0 = addiu(t0, 8);
        a1 = addiu(a1, -1);
        sw(a0, a3, 0);
        sw(v1, a3, 4);
        a3 = addiu(a3, 8);
        if (i64(a1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00412c04
    charge(ctx, 4);
    t0 = 0x6B0000;
    t0 = addiu(t0, 3248);  // &0x6B0CB0
    a3 = addiu(sp, 0x30);
    a1 = 36;
    for (;;) {
        // 0x00412c14
        charge(ctx, 9);
        lw(a0, t0, 0);
        lw(v1, t0, 4);
        t0 = addiu(t0, 8);
        a1 = addiu(a1, -1);
        sw(a0, a3, 0);
        sw(v1, a3, 4);
        a3 = addiu(a3, 8);
        if (i64(a1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00412c38
    charge(ctx, 18);
    v1 = 0x6B0000;
    lwc1(f3, v1, 3536);  // 0x6B0DD0
    v1 = 0x6B0000;
    lwc1(f2, v1, 3540);  // 0x6B0DD4
    v1 = 0x6B0000;
    lwc1(f1, v1, 3544);  // 0x6B0DD8
    v1 = 0x6B0000;
    lwc1(f0, v1, 3548);  // 0x6B0DDC
    swc1(f3, sp, 0x20);
    swc1(f2, sp, 0x24);
    swc1(f1, sp, 0x28);
    swc1(f0, sp, 0x2C);
    v1 = addiu(sp, 0x150);
    sw(v1, sp, 0x20);
    v1 = addiu(sp, 0x30);
    sw(v1, sp, 0x28);
    if (a2 != 0) {
        // 0x00412c80
        charge(ctx, 4);
        lh(a0, a2, kBgEventId);
        v1 = 10;
        if (a0 == v1) {
            // 0x00412ce0
            charge(ctx, 1);
            v0 = 3;
        } else {
            // 0x00412c90
            charge(ctx, 3);
            v1 = 5;
            if (a0 == v1) {
                // 0x00412cd4
                charge(ctx, 3);
                v0 = 2;
            } else {
                // 0x00412c9c
                charge(ctx, 3);
                v1 = 4;
                if (a0 == v1) {
                    // 0x00412cc8
                    charge(ctx, 3);
                    v0 = 1;
                } else {
                    // 0x00412ca8
                    charge(ctx, 3);
                    v1 = 1;
                    if (a0 == v1) {
                        // 0x00412cbc
                        charge(ctx, 3);
                        v0 = 0;
                    } else {
                        // 0x00412cb4
                        charge(ctx, 2);
                    }
                }
            }
        }
        // 0x00412ce4
        charge(ctx, 23);
        sw(v0, s0, 124);
        v1 = sra(v0, 1);
        v1 = sll(v1, 3);
        v1 = addu(v1, sp);
        v1 = addiu(v1, 32);
        lw(a1, v1, 0);
        lw(v1, v1, 4);
        a0 = srl(v1, 2);
        v0 = v0 & 0x1;
        v0 = sll(v0, 1);
        mult(v1, v0, a0);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        a1 = addu(a1, v0);
        v0 = sll(a0, 1);
        v0 = addu(v0, a0);
        a2 = sll(v0, 2);
        a0 = s0;
        jal(ctx, 0x412D30u, gen::fn_memcpy_00521250);
        sh(zero, s0, 120);
        sh(zero, s0, 122);
    }
    // 0x00412d40
    charge(ctx, 5);
    lw(a2, s0, 124);
    lh(v1, s0, 120);
    v0 = 1;
    if (v1 == v0) {
        // 0x00412f54
        charge(ctx, 20);
        v0 = sra(a2, 1);
        v0 = sll(v0, 3);
        v0 = addu(v0, sp);
        v0 = addiu(v0, 32);
        lw(a0, v0, 0);
        lw(v0, v0, 4);
        a1 = srl(v0, 2);
        a3 = 0;
        v0 = a2 & 0x1;
        v0 = sll(v0, 1);
        v0 = addiu(v0, 1);
        mult(v1, v0, a1);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        a0 = addu(a0, v0);
        lwc1(f1, gp, -32496);  // 0x7CAE00
        mtc1(zero, f2);
        for (;;) {
            // 0x00412fe0
            charge(ctx, 3);
            v0 = slt(a3, a1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00412fa4
            charge(ctx, 12);
            v0 = sll(a3, 1);
            v0 = addu(v0, a3);
            v0 = sll(v0, 2);
            v1 = addu(s0, v0);
            v0 = addu(a0, v0);
            lwc1(f3, v0, 8);
            lwc1(f0, v1, 8);
            add_s(f0, f0, f3);
            swc1(f0, v1, 8);
            c_lt_s(f0, f2);
            if (cond(ctx)) {
                // 0x00412fd4
                charge(ctx, 2);
                add_s(f0, f0, f1);
                swc1(f0, v1, 8);
            }
            // 0x00412fdc
            charge(ctx, 1);
            a3 = addiu(a3, 1);
        }
    L_00412fec:
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x00412d54
        charge(ctx, 2);
        if (v1 != 0) {
            // 0x00412d5c
            charge(ctx, 2);
            goto L_00412fec;
        }
        // 0x00412d64
        charge(ctx, 27);
        v0 = sra(a2, 1);
        v0 = sll(v0, 3);
        v0 = addu(v0, sp);
        v0 = addiu(v0, 32);
        lw(a1, v0, 0);
        lw(v0, v0, 4);
        t1 = srl(v0, 2);
        lh(v0, s0, 122);
        v0 = addiu(v0, 1);
        sh(v0, s0, 122);
        t2 = 0;
        t3 = 0;
        t0 = a2 & 0x1;
        a0 = sll(t0, 1);
        v0 = addiu(a0, 1);
        mult(v1, v0, t1);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        a3 = addu(a1, v0);
        mult1(v1, a0, t1);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        a2 = addu(a1, v0);
        for (;;) {
            // 0x00412f10
            charge(ctx, 3);
            v0 = slt(t3, t1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00412dd0
            charge(ctx, 9);
            v0 = sll(t3, 1);
            v0 = addu(v0, t3);
            t4 = sll(v0, 2);
            a1 = addu(s0, t4);
            lh(a0, a1, 6);
            lh(v1, s0, 122);
            v0 = slt(v1, a0);
            if (v0 == 0) {
                // 0x00412df4
                charge(ctx, 7);
                a0 = subu(v1, a0);
                v1 = addu(a3, t4);
                v0 = addiu(v1, 6);
                lh(t7, v1, 6);
                at = slt(t7, a0);
                if (at != 0) {
                    // 0x00412f08
                    charge(ctx, 1);
                    t2 = addiu(t2, 1);
                } else {
                    // 0x00412e10
                    charge(ctx, 62);
                    t6 = addu(a2, t4);
                    lh(t5, t6, 0);
                    lh(t4, v1, 0);
                    t4 = subu(t4, t5);
                    mult(t4, a0, t4);
                    mtc1(t4, f0);
                    cvt_s_w(f1, f0);
                    mtc1(t7, f0);
                    cvt_s_w(f0, f0);
                    div_s(f1, f1, f0);
                    mtc1(t5, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(t4, f0);
                    sh(t4, a1, 0);
                    lh(t5, t6, 2);
                    lh(t4, v1, 2);
                    t4 = subu(t4, t5);
                    mult1(t4, a0, t4);
                    mtc1(t4, f0);
                    cvt_s_w(f1, f0);
                    lh(t4, v0, 0);
                    mtc1(t4, f0);
                    cvt_s_w(f0, f0);
                    div_s(f1, f1, f0);
                    mtc1(t5, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(t4, f0);
                    sh(t4, a1, 2);
                    lh(t4, t6, 4);
                    lh(v1, v1, 4);
                    v1 = subu(v1, t4);
                    mult(v1, a0, v1);
                    mtc1(v1, f0);
                    cvt_s_w(f1, f0);
                    lh(v0, v0, 0);
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    div_s(f1, f1, f0);
                    mtc1(t4, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(v0, f0);
                    sh(v0, a1, 4);
                }
            }
            // 0x00412f0c
            charge(ctx, 1);
            t3 = addiu(t3, 1);
        }
        // 0x00412f1c
        charge(ctx, 3);
        v0 = slt(t2, t1);
        if (v0 == 0) {
            // 0x00412f28
            charge(ctx, 5);
            v0 = 1;
            sh(v0, s0, 120);
            sh(zero, s0, 122);
            if (t0 == 0) {
                goto L_00412f48;
            }
            // 0x00412f3c
            charge(ctx, 3);
            v0 = 2;
            // 0x00412ff0 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(ra, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x330);
            return;
        }
    L_00412f48:
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00412ff0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x330);
}

// 0x00413010 sub_413010 -- 400 bytes; frame 0xE0: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgOrbitDraw] Draws the orbit's keys with the sprite / offset table of its set (0x6B0DE0 or 0x6B0E30 by +124 / 2;
// sub_40E3F0, half-size scale). Returns 0.
void sub_413010(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15};
    // 0x00413010
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s2, a1, kBgNodeArea);
    a2 = 0x6B0000;
    a2 = addiu(a2, 3552);  // &0x6B0DE0
    a1 = addiu(sp, 0x90);
    a0 = 20;
    for (;;) {
        // 0x0041303c
        charge(ctx, 9);
        lh(v1, a2, 0);
        lh(v0, a2, 2);
        a2 = addiu(a2, 4);
        a0 = addiu(a0, -1);
        sh(v1, a1, 0);
        sh(v0, a1, 2);
        a1 = addiu(a1, 4);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00413060
    charge(ctx, 4);
    a2 = 0x6B0000;
    a2 = addiu(a2, 3632);  // &0x6B0E30
    a1 = addiu(sp, 0x60);
    a0 = 12;
    for (;;) {
        // 0x00413070
        charge(ctx, 9);
        lh(v1, a2, 0);
        lh(v0, a2, 2);
        a2 = addiu(a2, 4);
        a0 = addiu(a0, -1);
        sh(v1, a1, 0);
        sh(v0, a1, 2);
        a1 = addiu(a1, 4);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00413094
    charge(ctx, 25);
    v0 = 0x6B0000;
    lwc1(f3, v0, 3680);  // 0x6B0E60
    v0 = 0x6B0000;
    lwc1(f2, v0, 3684);  // 0x6B0E64
    v0 = 0x6B0000;
    lwc1(f1, v0, 3688);  // 0x6B0E68
    v0 = 0x6B0000;
    lwc1(f0, v0, 3692);  // 0x6B0E6C
    swc1(f3, sp, 0x50);
    swc1(f2, sp, 0x54);
    swc1(f1, sp, 0x58);
    swc1(f0, sp, 0x5C);
    v0 = addiu(sp, 0x90);
    sw(v0, sp, 0x50);
    v0 = addiu(sp, 0x60);
    sw(v0, sp, 0x58);
    lw(v0, s2, 124);
    v0 = sra(v0, 1);
    v0 = sll(v0, 3);
    v0 = addu(v0, sp);
    lw(s1, v0, 80);
    lw(s0, v0, 84);
    s3 = 0;
    for (;;) {
        // 0x00413170
        charge(ctx, 3);
        v0 = slt(s3, s0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x004130f8
        charge(ctx, 30);
        v0 = sll(s3, 1);
        v0 = addu(v0, s3);
        v0 = sll(v0, 2);
        t0 = addu(s2, v0);
        v0 = sll(s3, 3);
        a3 = addu(s1, v0);
        lh(a1, a3, 4);
        t1 = sra(a1, 1);
        lh(v1, t0, 0);
        lh(v0, a3, 0);
        v0 = addu(v1, v0);
        a0 = subu(v0, a1);
        lh(v1, t0, 2);
        lh(v0, a3, 2);
        v0 = addu(v1, v0);
        a1 = subu(v0, a1);
        mtc1(zero, f12);
        lbu(a2, t0, 4);
        lh(a3, a3, 6);
        lwc1(f1, gp, -32560);  // 0x7CADC0
        lwc1(f0, t0, 8);
        mul_s(f13, f1, f0);
        v0 = 0x3F800000;
        mtc1(v0, f14);
        t0 = 0;
        t2 = t1;
        mov_s(f15, f14);
        jal(ctx, 0x413164u, gen::fn_sub_40E3F0_0040e3f0);
        s3 = addiu(s3, 1);
    }
    // 0x0041317c
    charge(ctx, 9);
    v0 = 0;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xE0);
}

// 0x004131A0 sub_4131A0 -- 1236 bytes; frame 0xC0: ra sp+0x10, s0 sp+0x0 (sq)
// [fclBgSlide3] As sub_40F5D0 with three keys (36 bytes; tables 0x6B10E0 / 0x6B1130, state +36).
void sub_4131A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x004131a0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a1, kBgNodeArea);
    a3 = 0x6B0000;
    a3 = addiu(a3, 4320);  // &0x6B10E0
    a1 = addiu(sp, 0x70);
    a0 = 9;
    for (;;) {
        // 0x004131c0
        charge(ctx, 9);
        lw(v1, a3, 0);
        lw(v0, a3, 4);
        a3 = addiu(a3, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004131e4
    charge(ctx, 4);
    a3 = 0x6B0000;
    a3 = addiu(a3, 4400);  // &0x6B1130
    a1 = addiu(sp, 0x20);
    a0 = 9;
    for (;;) {
        // 0x004131f4
        charge(ctx, 9);
        lw(v1, a3, 0);
        lw(v0, a3, 4);
        a3 = addiu(a3, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00413218
    charge(ctx, 2);
    if (a2 != 0) {
        // 0x00413220
        charge(ctx, 4);
        lh(v1, a2, kBgEventId);
        v0 = 4;
        if (v1 == v0) {
            // 0x00413274
            charge(ctx, 8);
            a0 = s0;
            a1 = addiu(sp, 0x20);
            a2 = 36;
            jal(ctx, 0x413280u, gen::fn_memcpy_00521250);
            v0 = 2;
            sh(v0, s0, 36);
            sh(zero, s0, 38);
        } else {
            // 0x00413230
            charge(ctx, 3);
            v0 = 2;
            if (v1 != v0) {
                // 0x0041323c
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    // 0x00413250
                    charge(ctx, 9);
                    a0 = s0;
                    a1 = addiu(sp, 0x70);
                    a2 = 36;
                    jal(ctx, 0x41325Cu, gen::fn_memcpy_00521250);
                    sh(zero, s0, 36);
                    sh(zero, s0, 38);
                } else {
                    // 0x00413248
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x00413294
    charge(ctx, 4);
    lh(v1, s0, 36);
    v0 = 2;
    if (v1 == v0) {
        // 0x00413488
        charge(ctx, 7);
        lh(v0, s0, 38);
        v0 = addiu(v0, 1);
        sh(v0, s0, 38);
        a3 = 0;
        a2 = 0;
        for (;;) {
            // 0x00413620
            charge(ctx, 3);
            v0 = slti(a2, 3);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x004134a4
            charge(ctx, 9);
            v0 = sll(a2, 1);
            v0 = addu(v0, a2);
            t0 = sll(v0, 2);
            a1 = addu(s0, t0);
            lh(a0, a1, 6);
            lh(v1, s0, 38);
            v0 = slt(v1, a0);
            if (v0 == 0) {
                // 0x004134c8
                charge(ctx, 8);
                a0 = subu(v1, a0);
                v0 = addu(t0, sp);
                v1 = addiu(v0, 32);
                v0 = addiu(v1, 42);
                lh(t2, v1, 42);
                at = slt(t2, a0);
                if (at != 0) {
                    // 0x00413618
                    charge(ctx, 1);
                    a3 = addiu(a3, 1);
                } else {
                    // 0x004134e8
                    charge(ctx, 76);
                    lh(t1, v1, 0);
                    lh(t0, v1, 36);
                    t0 = subu(t0, t1);
                    mult(t0, a0, t0);
                    mtc1(t0, f0);
                    cvt_s_w(f1, f0);
                    mtc1(t2, f0);
                    cvt_s_w(f0, f0);
                    div_s(f1, f1, f0);
                    mtc1(t1, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(t0, f0);
                    sh(t0, a1, 0);
                    lh(t1, v1, 2);
                    lh(t0, v1, 38);
                    t0 = subu(t0, t1);
                    mult1(t0, a0, t0);
                    mtc1(t0, f0);
                    cvt_s_w(f1, f0);
                    lh(t0, v0, 0);
                    mtc1(t0, f0);
                    cvt_s_w(f0, f0);
                    div_s(f1, f1, f0);
                    mtc1(t1, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(t0, f0);
                    sh(t0, a1, 2);
                    lh(t1, v1, 4);
                    lh(t0, v1, 40);
                    t0 = subu(t0, t1);
                    mult(t0, a0, t0);
                    mtc1(t0, f0);
                    cvt_s_w(f1, f0);
                    lh(t0, v0, 0);
                    mtc1(t0, f0);
                    cvt_s_w(f0, f0);
                    div_s(f1, f1, f0);
                    mtc1(t1, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(t0, f0);
                    sh(t0, a1, 4);
                    lwc1(f2, v1, 8);
                    lwc1(f0, v1, 44);
                    sub_s(f1, f0, f2);
                    mtc1(a0, f0);
                    cvt_s_w(f0, f0);
                    mul_s(f1, f0, f1);
                    lh(v0, v0, 0);
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    div_s(f0, f1, f0);
                    add_s(f0, f2, f0);
                    swc1(f0, a1, 8);
                }
            }
            // 0x0041361c
            charge(ctx, 1);
            a2 = addiu(a2, 1);
        }
        // 0x0041362c
        charge(ctx, 3);
        v0 = slti(a3, 3);
        if (v0 != 0) {
            // 0x00413650
            charge(ctx, 3);
            v0 = 0;
        } else {
            // 0x00413638
            charge(ctx, 6);
            v0 = 1;
            sh(v0, s0, 36);
            sh(zero, s0, 38);
            v0 = 2;
        }
    } else {
        // 0x004132a4
        charge(ctx, 3);
        v0 = 1;
        if (v1 != v0) {
            // 0x004132b0
            charge(ctx, 2);
            if (v1 != 0) {
                // 0x004132b8
                charge(ctx, 2);
                goto L_0041365c;
            }
            // 0x004132c0
            charge(ctx, 7);
            lh(v0, s0, 38);
            v0 = addiu(v0, 1);
            sh(v0, s0, 38);
            a2 = 0;
            a3 = 0;
            for (;;) {
                // 0x00413458
                charge(ctx, 3);
                v0 = slti(a3, 3);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x004132dc
                charge(ctx, 9);
                v0 = sll(a3, 1);
                v0 = addu(v0, a3);
                t0 = sll(v0, 2);
                a1 = addu(s0, t0);
                lh(a0, a1, 6);
                lh(v1, s0, 38);
                v0 = slt(v1, a0);
                if (v0 == 0) {
                    // 0x00413300
                    charge(ctx, 8);
                    a0 = subu(v1, a0);
                    v0 = addu(t0, sp);
                    v1 = addiu(v0, 112);
                    v0 = addiu(v1, 42);
                    lh(t2, v1, 42);
                    at = slt(t2, a0);
                    if (at != 0) {
                        // 0x00413450
                        charge(ctx, 1);
                        a2 = addiu(a2, 1);
                    } else {
                        // 0x00413320
                        charge(ctx, 76);
                        lh(t1, v1, 0);
                        lh(t0, v1, 36);
                        t0 = subu(t0, t1);
                        mult(t0, a0, t0);
                        mtc1(t0, f0);
                        cvt_s_w(f1, f0);
                        mtc1(t2, f0);
                        cvt_s_w(f0, f0);
                        div_s(f1, f1, f0);
                        mtc1(t1, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f0, f1);
                        cvt_w_s(f0, f0);
                        mfc1(t0, f0);
                        sh(t0, a1, 0);
                        lh(t1, v1, 2);
                        lh(t0, v1, 38);
                        t0 = subu(t0, t1);
                        mult1(t0, a0, t0);
                        mtc1(t0, f0);
                        cvt_s_w(f1, f0);
                        lh(t0, v0, 0);
                        mtc1(t0, f0);
                        cvt_s_w(f0, f0);
                        div_s(f1, f1, f0);
                        mtc1(t1, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f0, f1);
                        cvt_w_s(f0, f0);
                        mfc1(t0, f0);
                        sh(t0, a1, 2);
                        lh(t1, v1, 4);
                        lh(t0, v1, 40);
                        t0 = subu(t0, t1);
                        mult(t0, a0, t0);
                        mtc1(t0, f0);
                        cvt_s_w(f1, f0);
                        lh(t0, v0, 0);
                        mtc1(t0, f0);
                        cvt_s_w(f0, f0);
                        div_s(f1, f1, f0);
                        mtc1(t1, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f0, f1);
                        cvt_w_s(f0, f0);
                        mfc1(t0, f0);
                        sh(t0, a1, 4);
                        lwc1(f2, v1, 8);
                        lwc1(f0, v1, 44);
                        sub_s(f1, f0, f2);
                        mtc1(a0, f0);
                        cvt_s_w(f0, f0);
                        mul_s(f1, f0, f1);
                        lh(v0, v0, 0);
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        div_s(f0, f1, f0);
                        add_s(f0, f2, f0);
                        swc1(f0, a1, 8);
                    }
                }
                // 0x00413454
                charge(ctx, 1);
                a3 = addiu(a3, 1);
            }
            // 0x00413464
            charge(ctx, 3);
            v0 = slti(a2, 3);
            if (v0 == 0) {
                // 0x00413470
                charge(ctx, 3);
                v0 = 1;
                sh(v0, s0, 36);
                sh(zero, s0, 38);
            }
            // 0x0041347c
            charge(ctx, 3);
            v0 = 0;
            // 0x00413660 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(ra, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0xC0);
            return;
        }
    L_0041365c:
        charge(ctx, 1);
        v0 = 1;
    }
    // 0x00413660 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xC0);
}

// 0x00413680 sub_413680 -- 596 bytes; frame 0x90: ra sp+0x70, s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [fclBgSlide3Draw] Draws the three keys: keys 0 / 1 rotated by their angle (cosf / sinf, sub_40E3C0), key 2 straight
// (sub_40E3F0), two sprites each from table 0x6B1178. Returns 0.
void sub_413680(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x00413680
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(s5, a1, kBgNodeArea);
    a2 = 0x6B0000;
    a2 = addiu(a2, 4472);  // &0x6B1178
    a1 = addiu(sp, 0x80);
    a0 = 3;
    for (;;) {
        // 0x004136c0
        charge(ctx, 9);
        lh(v1, a2, 0);
        lh(v0, a2, 2);
        a2 = addiu(a2, 4);
        a0 = addiu(a0, -1);
        sh(v1, a1, 0);
        sh(v0, a1, 2);
        a1 = addiu(a1, 4);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004136e4
    charge(ctx, 3);
    s4 = 0;
    for (;;) {
        // 0x00413890
        charge(ctx, 3);
        v0 = slti(s4, 3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x004136f0
        charge(ctx, 7);
        v1 = sll(s4, 1);
        v0 = addu(v1, s4);
        v0 = sll(v0, 2);
        s1 = addu(s5, v0);
        at = slti(s4, 2);
        if (at == 0) {
            // 0x0041381c
            charge(ctx, 28);
            lwc1(f14, s1, 8);
            v0 = addu(v1, sp);
            s0 = addiu(v0, 128);
            lh(a0, s1, 0);
            lh(a1, s1, 2);
            mtc1(zero, f12);
            lbu(a2, s1, 4);
            lh(a3, s0, 0);
            t0 = 0;
            t1 = 0;
            t2 = 0;
            mov_s(f13, f12);
            mov_s(f15, f14);
            jal(ctx, 0x413850u, gen::fn_sub_40E3F0_0040e3f0);
            lwc1(f14, s1, 8);
            lh(a0, s1, 0);
            lh(a1, s1, 2);
            mtc1(zero, f12);
            lbu(a2, s1, 4);
            lh(a3, s0, 6);
            t0 = 0;
            t1 = 0;
            t2 = 0;
            mov_s(f13, f12);
            mov_s(f15, f14);
            jal(ctx, 0x413884u, gen::fn_sub_40E3F0_0040e3f0);
        } else {
            // 0x0041370c
            charge(ctx, 68);
            lwc1(f1, gp, -32252);  // 0x7CAEF4
            lwc1(f0, s1, 8);
            mul_s(f20, f1, f0);
            lh(s0, s1, 0);
            mov_s(f12, f20);
            jal(ctx, 0x413720u, gen::fn_cosf_0052e6d8);
            mov_s(f22, f0);
            mtc1(s0, f0);
            cvt_s_w(f21, f0);
            mov_s(f12, f20);
            jal(ctx, 0x41373Cu, gen::fn_sinf_0052e878);
            lh(v0, s1, 2);
            mtc1(v0, f1);
            cvt_s_w(f1, f1);
            mula_s(f1, f0);
            madd_s(f1, f21, f22);
            mtc1(s0, f0);
            cvt_s_w(f0, f0);
            sub_s(f0, f0, f1);
            cvt_w_s(f0, f0);
            mfc1(s3, f0);
            mov_s(f12, f20);
            jal(ctx, 0x413778u, gen::fn_sinf_0052e878);
            mov_s(f22, f0);
            lh(v0, s1, 0);
            v0 = subu(0, v0);
            mtc1(v0, f0);
            cvt_s_w(f21, f0);
            mov_s(f12, f20);
            jal(ctx, 0x41379Cu, gen::fn_cosf_0052e6d8);
            lh(v0, s1, 2);
            mtc1(v0, f1);
            cvt_s_w(f1, f1);
            mula_s(f1, f0);
            mtc1(zero, f12);
            madd_s(f0, f21, f22);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(s2, f0);
            v0 = sll(s4, 1);
            v0 = addu(v0, sp);
            s0 = addiu(v0, 128);
            lbu(a2, s1, 4);
            lh(a3, s0, 0);
            a0 = s3;
            a1 = s2;
            t0 = 0;
            jal(ctx, 0x4137ECu, gen::fn_sub_40E3C0_0040e3c0);
            mtc1(zero, f12);
            lbu(a2, s1, 4);
            lh(a3, s0, 6);
            a0 = s3;
            a1 = s2;
            t0 = 0;
            jal(ctx, 0x41380Cu, gen::fn_sub_40E3C0_0040e3c0);
        }
        // 0x0041388c
        charge(ctx, 1);
        s4 = addiu(s4, 1);
    }
    // 0x0041389c
    charge(ctx, 14);
    v0 = 0;
    ld(ra, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x004138E0 sub_4138E0 -- 548 bytes; frame 0x10
// [fclBgFade] A background element handler (area {s16 state, s16 timer, f32 value, s16 alpha, s16 set}): event 5 fades
// in over 8 frames (value from 0x7CDA08 [set], alpha 0 -> 255), 10 fades out over 6 frames (alpha 255 -> 0, state 2).
// Returns 0 while fading in, 2 when the fade-out ends, 1 while idle; event 2 is ignored.
void sub_4138E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x004138e0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    lw(v1, a1, kBgNodeArea);
    lwc1(f1, gp, -21224);  // 0x7CDA08
    lwc1(f0, gp, -21220);  // 0x7CDA0C
    swc1(f1, sp, 0x8);
    swc1(f0, sp, 0xC);
    if (a2 != 0) {
        // 0x00413900: an event
        charge(ctx, 4);
        lh(a1, a2, kBgEventId);
        a0 = 2;
        if (a1 != a0) {
            // 0x00413910
            charge(ctx, 3);
            v0 = 10;
            if (a1 == v0) {
                // 0x00413950: event 10: fade out (state 2)
                charge(ctx, 7);
                sh(zero, v1, 10);
                lwc1(f0, sp, 0xC);
                swc1(f0, v1, 4);
                v0 = 255;
                sh(v0, v1, 8);
                sh(a0, v1, 0);
                sh(zero, v1, 2);
            } else {
                // 0x0041391c
                charge(ctx, 3);
                v0 = 5;
                if (a1 == v0) {
                    // 0x00413930: event 5: fade in
                    charge(ctx, 8);
                    sh(zero, v1, 10);
                    lwc1(f0, sp, 0x8);
                    swc1(f0, v1, 4);
                    sh(zero, v1, 8);
                    sh(zero, v1, 0);
                    sh(zero, v1, 2);
                } else {
                    // 0x00413928
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x0041396c: per frame
    charge(ctx, 4);
    lh(a0, v1, 0);
    v0 = 2;
    if (a0 == v0) {
        // 0x00413a38: fading out: alpha 255 -> 0 over 6 frames
        charge(ctx, 39);
        lh(a0, v1, 2);
        a0 = addiu(a0, 1);
        sh(a0, v1, 2);
        a2 = dsll32(a0, 16);
        a2 = dsra32(a2, 16);
        lh(a0, v1, 10);
        a0 = sll(a0, 3);
        a1 = addu(a0, sp);
        a0 = addiu(a1, 8);
        lwc1(f2, a0, 0);
        lwc1(f0, a1, 12);
        sub_s(f1, f0, f2);
        mtc1(a2, f0);
        cvt_s_w(f0, f0);
        mul_s(f0, f0, f1);
        a0 = 0x40C00000;
        mtc1(a0, f1);
        div_s(f0, f0, f1);
        add_s(f0, f2, f0);
        swc1(f0, v1, 4);
        a0 = sll(a2, 8);
        a0 = subu(a2, a0);
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        div_s(f1, f0, f1);
        a0 = 0x437F0000;
        mtc1(a0, f0);
        add_s(f0, f0, f1);
        cvt_w_s(f0, f0);
        mfc1(a0, f0);
        sh(a0, v1, 8);
        a0 = slti(a2, 6);
        if (a0 != 0) {
            // 0x00413ae8
            charge(ctx, 3);
            v0 = 0;
        } else {
            // 0x00413ad4: faded out: state 1, returns 2
            charge(ctx, 5);
            a0 = 1;
            sh(a0, v1, 0);
            sh(zero, v1, 2);
        }
    } else {
        // 0x0041397c
        charge(ctx, 3);
        a2 = 1;
        if (a0 != a2) {
            // 0x00413988
            charge(ctx, 2);
            if (a0 != 0) {
                // 0x00413990
                charge(ctx, 2);
                goto L_00413af4;
            }
            // 0x00413998: fading in: alpha 0 -> 255 over 8 frames
            charge(ctx, 35);
            lh(v0, v1, 2);
            v0 = addiu(v0, 1);
            sh(v0, v1, 2);
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            lh(v0, v1, 10);
            v0 = sll(v0, 3);
            a0 = addu(v0, sp);
            v0 = addiu(a0, 8);
            lwc1(f2, v0, 0);
            lwc1(f0, a0, 12);
            sub_s(f1, f0, f2);
            mtc1(a1, f0);
            cvt_s_w(f0, f0);
            mul_s(f0, f0, f1);
            v0 = 0x41000000;
            mtc1(v0, f1);
            div_s(f0, f0, f1);
            add_s(f0, f2, f0);
            swc1(f0, v1, 4);
            v0 = sll(a1, 8);
            v0 = subu(v0, a1);
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            div_s(f0, f0, f1);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            sh(v0, v1, 8);
            v0 = slti(a1, 8);
            if (v0 == 0) {
                // 0x00413a24
                charge(ctx, 2);
                sh(a2, v1, 0);
                sh(zero, v1, 2);
            }
            // 0x00413a2c
            charge(ctx, 3);
            v0 = 0;
            // 0x00413af8 (the shared epilogue, written out on this path)
            charge(ctx, 3);
            sp = addiu(sp, 0x10);
            return;
        }
    L_00413af4:
        charge(ctx, 1);
        v0 = 1;
    }
    // 0x00413af8 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    sp = addiu(sp, 0x10);
}

// 0x00413B10 sub_413B10 -- 96 bytes; frame 0x10: ra sp+0x0
// [fclBgFadeDraw] Draws sprite 104 full screen (116 x 125 scale) with the fade's alpha (+8) through sub_40E3F0.
// Returns 0.
void sub_413B10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15};
    // 0x00413b10
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a1, kBgNodeArea);
    mtc1(zero, f12);
    lbu(a2, v0, 8);
    lwc1(f1, gp, -32560);  // 0x7CADC0
    lwc1(f0, v0, 4);
    mul_s(f13, f1, f0);
    v0 = 0x3F800000;
    mtc1(v0, f14);
    a0 = 0;
    a1 = 0;
    a3 = 104;
    t0 = 0;
    t1 = 116;
    t2 = 125;
    mov_s(f15, f14);
    jal(ctx, 0x413B54u, gen::fn_sub_40E3F0_0040e3f0);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00414100 sub_414100 -- 220 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgPart414100] A sub-handler of the dispatchers sub_414E10 / sub_415C30 / sub_417030 ($a2 x, $a3 y, $t1 alpha):
// sprites 35, 36, 37, 39, 41 at (x - 6, y - 10) (sub_40E3C0).
void sub_414100(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00414100
    enter(ctx, 55);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a2;
    s1 = a3;
    s0 = t1;
    a0 = addiu(s2, -6);
    a1 = addiu(s1, -10);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    a3 = 35;
    t0 = 0;
    jal(ctx, 0x414138u, gen::fn_sub_40E3C0_0040e3c0);
    a0 = addiu(s2, -6);
    a1 = addiu(s1, -10);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    a3 = 36;
    t0 = 0;
    jal(ctx, 0x414158u, gen::fn_sub_40E3C0_0040e3c0);
    a0 = addiu(s2, -6);
    a1 = addiu(s1, -10);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    a3 = 37;
    t0 = 0;
    jal(ctx, 0x414178u, gen::fn_sub_40E3C0_0040e3c0);
    a0 = addiu(s2, -6);
    a1 = addiu(s1, -10);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    a3 = 39;
    t0 = 0;
    jal(ctx, 0x414198u, gen::fn_sub_40E3C0_0040e3c0);
    a0 = addiu(s2, -6);
    a1 = addiu(s1, -10);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    a3 = 41;
    t0 = 0;
    jal(ctx, 0x4141B8u, gen::fn_sub_40E3C0_0040e3c0);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x004141E0 sub_4141E0 -- 152 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgPart4141E0] Sub-handler: sprites 129, 130 at (x, y).
void sub_4141E0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x004141e0
    enter(ctx, 38);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a2;
    s2 = a3;
    s1 = t0;
    s0 = t1;
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a2 = s0 & 0xFF;
    a0 = s3;
    a1 = s2;
    a3 = 129;
    t0 = 0;
    jal(ctx, 0x414228u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a2 = s0 & 0xFF;
    a0 = s3;
    a1 = s2;
    a3 = 130;
    t0 = 0;
    jal(ctx, 0x414250u, gen::fn_sub_40E3C0_0040e3c0);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00414280 sub_414280 -- 152 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgPart414280] Sub-handler: sprites 47, 48 at (x + 249, y + 298).
void sub_414280(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x00414280
    enter(ctx, 38);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a2;
    s2 = a3;
    s1 = t0;
    s0 = t1;
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s3, 249);
    a1 = addiu(s2, 298);
    a2 = s0 & 0xFF;
    a3 = 47;
    t0 = 0;
    jal(ctx, 0x4142C8u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s3, 249);
    a1 = addiu(s2, 298);
    a2 = s0 & 0xFF;
    a3 = 48;
    t0 = 0;
    jal(ctx, 0x4142F0u, gen::fn_sub_40E3C0_0040e3c0);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00414320 sub_414320 -- 476 bytes; frame 0x60: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [fclBgPart414320] Sub-handler: sprites 146, 141 at (x + 32, y + 101), then 142 / 143 with alpha * the factor
// 0x7CADA4, then 144, 145.
void sub_414320(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20};
    // 0x00414320
    enter(ctx, 45);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s3 = a2;
    s2 = a3;
    s1 = t0;
    s0 = t1;
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s3, 32);
    a1 = addiu(s2, 101);
    a2 = s0 & 0xFF;
    a3 = 146;
    t0 = 0;
    jal(ctx, 0x41436Cu, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s3, 32);
    a1 = addiu(s2, 101);
    a2 = s0 & 0xFF;
    a3 = 141;
    t0 = 0;
    jal(ctx, 0x414394u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, gp, -32588);  // 0x7CADA4
    mul_s(f20, f0, f1);
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f20);
    if (cond(ctx)) {
        // 0x004143ec
        charge(ctx, 6);
        sub_s(f0, f20, f0);
        cvt_w_s(f0, f0);
        mfc1(a2, f0);
        v0 = lui(0x8000);
        a2 = a2 | v0;
        a2 = a2 & 0xFF;
    } else {
        // 0x004143d4
        charge(ctx, 6);
        cvt_w_s(f0, f20);
        mfc1(a2, f0);
        a2 = a2 & 0xFF;
    }
    // 0x00414404
    charge(ctx, 15);
    a0 = addiu(s3, 32);
    a1 = addiu(s2, 101);
    a3 = 142;
    t0 = 0;
    jal(ctx, 0x414414u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f20);
    if (cond(ctx)) {
        // 0x00414458
        charge(ctx, 6);
        sub_s(f0, f20, f0);
        cvt_w_s(f0, f0);
        mfc1(a2, f0);
        v0 = lui(0x8000);
        a2 = a2 | v0;
        a2 = a2 & 0xFF;
    } else {
        // 0x00414440
        charge(ctx, 6);
        cvt_w_s(f0, f20);
        mfc1(a2, f0);
        a2 = a2 & 0xFF;
    }
    // 0x00414470
    charge(ctx, 35);
    a0 = addiu(s3, 32);
    a1 = addiu(s2, 101);
    a3 = 143;
    t0 = 0;
    jal(ctx, 0x414480u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s3, 32);
    a1 = addiu(s2, 101);
    a2 = s0 & 0xFF;
    a3 = 144;
    t0 = 0;
    jal(ctx, 0x4144A8u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s3, 32);
    a1 = addiu(s2, 101);
    a2 = s0 & 0xFF;
    a3 = 145;
    t0 = 0;
    jal(ctx, 0x4144D0u, gen::fn_sub_40E3C0_0040e3c0);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00414500 sub_414500 -- 232 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgPart414500] Sub-handler: sprites 153..156 at (x + 376, y + 92).
void sub_414500(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x00414500
    enter(ctx, 58);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a2;
    s2 = a3;
    s1 = t0;
    s0 = t1;
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s3, 376);
    a1 = addiu(s2, 92);
    a2 = s0 & 0xFF;
    a3 = 153;
    t0 = 0;
    jal(ctx, 0x414548u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s3, 376);
    a1 = addiu(s2, 92);
    a2 = s0 & 0xFF;
    a3 = 154;
    t0 = 0;
    jal(ctx, 0x414570u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s3, 376);
    a1 = addiu(s2, 92);
    a2 = s0 & 0xFF;
    a3 = 155;
    t0 = 0;
    jal(ctx, 0x414598u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s3, 376);
    a1 = addiu(s2, 92);
    a2 = s0 & 0xFF;
    a3 = 156;
    t0 = 0;
    jal(ctx, 0x4145C0u, gen::fn_sub_40E3C0_0040e3c0);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x004145F0 sub_4145F0 -- 192 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgPart4145F0] Sub-handler: sprites 147..149 at (x - 12, y - 14).
void sub_4145F0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x004145f0
    enter(ctx, 48);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a2;
    s2 = a3;
    s1 = t0;
    s0 = t1;
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s3, -12);
    a1 = addiu(s2, -14);
    a2 = s0 & 0xFF;
    a3 = 147;
    t0 = 0;
    jal(ctx, 0x414638u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s3, -12);
    a1 = addiu(s2, -14);
    a2 = s0 & 0xFF;
    a3 = 148;
    t0 = 0;
    jal(ctx, 0x414660u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s3, -12);
    a1 = addiu(s2, -14);
    a2 = s0 & 0xFF;
    a3 = 149;
    t0 = 0;
    jal(ctx, 0x414688u, gen::fn_sub_40E3C0_0040e3c0);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x004146B0 sub_4146B0 -- 192 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgPart4146B0] Sub-handler: sprites 150..152 at (x + 248, y - 1).
void sub_4146B0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x004146b0
    enter(ctx, 48);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a2;
    s2 = a3;
    s1 = t0;
    s0 = t1;
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s3, 248);
    a1 = addiu(s2, -1);
    a2 = s0 & 0xFF;
    a3 = 150;
    t0 = 0;
    jal(ctx, 0x4146F8u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s3, 248);
    a1 = addiu(s2, -1);
    a2 = s0 & 0xFF;
    a3 = 151;
    t0 = 0;
    jal(ctx, 0x414720u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s3, 248);
    a1 = addiu(s2, -1);
    a2 = s0 & 0xFF;
    a3 = 152;
    t0 = 0;
    jal(ctx, 0x414748u, gen::fn_sub_40E3C0_0040e3c0);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x004148B0 sub_4148B0 -- 152 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgPart4148B0] Sub-handler: sprites 45, 46 at (x + 249, y + 285).
void sub_4148B0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x004148b0
    enter(ctx, 38);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a2;
    s2 = a3;
    s1 = t0;
    s0 = t1;
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s3, 249);
    a1 = addiu(s2, 285);
    a2 = s0 & 0xFF;
    a3 = 45;
    t0 = 0;
    jal(ctx, 0x4148F8u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s3, 249);
    a1 = addiu(s2, 285);
    a2 = s0 & 0xFF;
    a3 = 46;
    t0 = 0;
    jal(ctx, 0x414920u, gen::fn_sub_40E3C0_0040e3c0);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00414950 sub_414950 -- 152 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgPart414950] Sub-handler: sprites 43, 44 at (x + 249, y + 303).
void sub_414950(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x00414950
    enter(ctx, 38);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a2;
    s2 = a3;
    s1 = t0;
    s0 = t1;
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s3, 249);
    a1 = addiu(s2, 303);
    a2 = s0 & 0xFF;
    a3 = 43;
    t0 = 0;
    jal(ctx, 0x414998u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s3, 249);
    a1 = addiu(s2, 303);
    a2 = s0 & 0xFF;
    a3 = 44;
    t0 = 0;
    jal(ctx, 0x4149C0u, gen::fn_sub_40E3C0_0040e3c0);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x004149F0 sub_4149F0 -- 220 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgPart4149F0] Sub-handler: sprites 35, 36, 38, 40, 41 at (x - 6, y - 10).
void sub_4149F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x004149f0
    enter(ctx, 55);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a2;
    s1 = a3;
    s0 = t1;
    a0 = addiu(s2, -6);
    a1 = addiu(s1, -10);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    a3 = 35;
    t0 = 0;
    jal(ctx, 0x414A28u, gen::fn_sub_40E3C0_0040e3c0);
    a0 = addiu(s2, -6);
    a1 = addiu(s1, -10);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    a3 = 36;
    t0 = 0;
    jal(ctx, 0x414A48u, gen::fn_sub_40E3C0_0040e3c0);
    a0 = addiu(s2, -6);
    a1 = addiu(s1, -10);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    a3 = 38;
    t0 = 0;
    jal(ctx, 0x414A68u, gen::fn_sub_40E3C0_0040e3c0);
    a0 = addiu(s2, -6);
    a1 = addiu(s1, -10);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    a3 = 40;
    t0 = 0;
    jal(ctx, 0x414A88u, gen::fn_sub_40E3C0_0040e3c0);
    a0 = addiu(s2, -6);
    a1 = addiu(s1, -10);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    a3 = 41;
    t0 = 0;
    jal(ctx, 0x414AA8u, gen::fn_sub_40E3C0_0040e3c0);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00414AD0 sub_414AD0 -- 252 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgPart414AD0] Sub-handler: sprites 35, 36, 37, 39, 41, 215 at (x - 6, y - 10).
void sub_414AD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00414ad0
    enter(ctx, 63);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a2;
    s1 = a3;
    s0 = t1;
    a0 = addiu(s2, -6);
    a1 = addiu(s1, -10);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    a3 = 35;
    t0 = 0;
    jal(ctx, 0x414B08u, gen::fn_sub_40E3C0_0040e3c0);
    a0 = addiu(s2, -6);
    a1 = addiu(s1, -10);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    a3 = 36;
    t0 = 0;
    jal(ctx, 0x414B28u, gen::fn_sub_40E3C0_0040e3c0);
    a0 = addiu(s2, -6);
    a1 = addiu(s1, -10);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    a3 = 37;
    t0 = 0;
    jal(ctx, 0x414B48u, gen::fn_sub_40E3C0_0040e3c0);
    a0 = addiu(s2, -6);
    a1 = addiu(s1, -10);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    a3 = 39;
    t0 = 0;
    jal(ctx, 0x414B68u, gen::fn_sub_40E3C0_0040e3c0);
    a0 = addiu(s2, -6);
    a1 = addiu(s1, -10);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    a3 = 41;
    t0 = 0;
    jal(ctx, 0x414B88u, gen::fn_sub_40E3C0_0040e3c0);
    a0 = addiu(s2, -6);
    a1 = addiu(s1, -10);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    a3 = 215;
    t0 = 0;
    jal(ctx, 0x414BA8u, gen::fn_sub_40E3C0_0040e3c0);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00414BD0 sub_414BD0 -- 152 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgPart414BD0] Sub-handler: sprites 43, 44 at (x + 290, y + 222).
void sub_414BD0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x00414bd0
    enter(ctx, 38);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a2;
    s2 = a3;
    s1 = t0;
    s0 = t1;
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s3, 290);
    a1 = addiu(s2, 222);
    a2 = s0 & 0xFF;
    a3 = 43;
    t0 = 0;
    jal(ctx, 0x414C18u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s3, 290);
    a1 = addiu(s2, 222);
    a2 = s0 & 0xFF;
    a3 = 44;
    t0 = 0;
    jal(ctx, 0x414C40u, gen::fn_sub_40E3C0_0040e3c0);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00414C70 sub_414C70 -- 252 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgPart414C70] Sub-handler: sprites 35, 36, 37, 39, 42, 215 at (x - 6, y - 10).
void sub_414C70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00414c70
    enter(ctx, 63);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a2;
    s1 = a3;
    s0 = t1;
    a0 = addiu(s2, -6);
    a1 = addiu(s1, -10);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    a3 = 35;
    t0 = 0;
    jal(ctx, 0x414CA8u, gen::fn_sub_40E3C0_0040e3c0);
    a0 = addiu(s2, -6);
    a1 = addiu(s1, -10);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    a3 = 36;
    t0 = 0;
    jal(ctx, 0x414CC8u, gen::fn_sub_40E3C0_0040e3c0);
    a0 = addiu(s2, -6);
    a1 = addiu(s1, -10);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    a3 = 37;
    t0 = 0;
    jal(ctx, 0x414CE8u, gen::fn_sub_40E3C0_0040e3c0);
    a0 = addiu(s2, -6);
    a1 = addiu(s1, -10);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    a3 = 39;
    t0 = 0;
    jal(ctx, 0x414D08u, gen::fn_sub_40E3C0_0040e3c0);
    a0 = addiu(s2, -6);
    a1 = addiu(s1, -10);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    a3 = 42;
    t0 = 0;
    jal(ctx, 0x414D28u, gen::fn_sub_40E3C0_0040e3c0);
    a0 = addiu(s2, -6);
    a1 = addiu(s1, -10);
    mtc1(zero, f12);
    a2 = s0 & 0xFF;
    a3 = 215;
    t0 = 0;
    jal(ctx, 0x414D48u, gen::fn_sub_40E3C0_0040e3c0);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00414D70 sub_414D70 -- 152 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgPart414D70] Sub-handler: sprites 43, 44 at (x + 290, y + 222) (a second copy of sub_414BD0).
void sub_414D70(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x00414d70
    enter(ctx, 38);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a2;
    s2 = a3;
    s1 = t0;
    s0 = t1;
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s3, 290);
    a1 = addiu(s2, 222);
    a2 = s0 & 0xFF;
    a3 = 43;
    t0 = 0;
    jal(ctx, 0x414DB8u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s3, 290);
    a1 = addiu(s2, 222);
    a2 = s0 & 0xFF;
    a3 = 44;
    t0 = 0;
    jal(ctx, 0x414DE0u, gen::fn_sub_40E3C0_0040e3c0);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00414E10 sub_414E10 -- 456 bytes; frame 0xE0: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgPartsDispatchA] Draws a background element's parts: picks the part list of its set (+152 / 2) from the
// on-stack table built from 0x6B14C0 (lists 0x6B1490.., 0x6B14A0, the single-entry lists 0x7CDA10..0x7CDA24) and calls
// each part (jalr) with (manager, node, x, y, 0, alpha) of key i (12-byte keys). Returns 0.
void sub_414E10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x00414e10
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(s4, a1, kBgNodeArea);
    v0 = 0x6B0000;
    lwc1(f2, v0, 5264);  // 0x6B1490
    v0 = 0x6B0000;
    lwc1(f1, v0, 5268);  // 0x6B1494
    v0 = 0x6B0000;
    lwc1(f0, v0, 5272);  // 0x6B1498
    swc1(f2, sp, 0xC8);
    swc1(f1, sp, 0xCC);
    swc1(f0, sp, 0xD0);
    a2 = 0x6B0000;
    a2 = addiu(a2, 5280);  // " CA"
    a1 = addiu(sp, 0xA0);
    a0 = 3;
    for (;;) {
        // 0x00414e70
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
    // 0x00414e94
    charge(ctx, 16);
    lwc1(f0, gp, -21216);  // 0x7CDA10
    swc1(f0, sp, 0xDC);
    lwc1(f0, gp, -21212);  // 0x7CDA14
    swc1(f0, sp, 0xD8);
    lwc1(f1, gp, -21208);  // 0x7CDA18
    lwc1(f0, gp, -21204);  // 0x7CDA1C
    swc1(f1, sp, 0xC0);
    swc1(f0, sp, 0xC4);
    lwc1(f1, gp, -21200);  // 0x7CDA20
    lwc1(f0, gp, -21196);  // 0x7CDA24
    swc1(f1, sp, 0xB8);
    swc1(f0, sp, 0xBC);
    a2 = 0x6B0000;
    a2 = addiu(a2, 5312);  // &0x6B14C0
    a1 = addiu(sp, 0x70);
    a0 = 6;
    for (;;) {
        // 0x00414ed4
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
    // 0x00414ef8
    charge(ctx, 21);
    v0 = addiu(sp, 0xC8);
    sw(v0, sp, 0x70);
    v0 = addiu(sp, 0xA0);
    sw(v0, sp, 0x78);
    v0 = addiu(sp, 0xDC);
    sw(v0, sp, 0x80);
    v0 = addiu(sp, 0xD8);
    sw(v0, sp, 0x88);
    v0 = addiu(sp, 0xC0);
    sw(v0, sp, 0x90);
    v0 = addiu(sp, 0xB8);
    sw(v0, sp, 0x98);
    lw(v0, s4, 152);
    v0 = sra(v0, 1);
    v0 = sll(v0, 3);
    v0 = addu(v0, sp);
    lw(s3, v0, 112);
    lw(s2, v0, 116);
    s5 = 0;
    for (;;) {
        // 0x00414fa0
        charge(ctx, 3);
        v0 = slt(s5, s2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00414f4c
        charge(ctx, 21);
        v0 = sll(s5, 1);
        v0 = addu(v0, s5);
        v0 = sll(v0, 2);
        v0 = addu(s4, v0);
        lwc1(f13, v0, 8);
        lh(a2, v0, 0);
        lh(a3, v0, 2);
        lh(t1, v0, 4);
        mtc1(zero, f12);
        a0 = s1;
        a1 = s0;
        t0 = 0;
        t2 = 0;
        t3 = 0;
        mov_s(f14, f13);
        v0 = sll(s5, 2);
        v0 = addu(s3, v0);
        lw(v0, v0, 0);
        jalr(ctx, 0x414F94u, v0.u());
        s5 = addiu(s5, 1);
    }
    // 0x00414fac
    charge(ctx, 11);
    v0 = 0;
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xE0);
}

// 0x00414FE0 sub_414FE0 -- 1280 bytes; frame 0x200: ra sp+0x10, s0 sp+0x0 (sq)
// [fclBgPartsMove] A background element handler: events 5..14 pick one of ten key sets (+152 = 0, 2, 4, 6, 8 for 5..9
// and 1, 3, .. 9 for 10..14 -- the "out" halves; jump table 0x7BC050) from five tables (0x6B14F0 .. 0x6B1640) and copy
// their keys; then moves the keys toward the set's second half. Returns 2 when an out move finishes, 1 when idle, else
// 0.
void sub_414FE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x00414fe0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x200);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a1, kBgNodeArea);
    a3 = 0x6B0000;
    a3 = addiu(a3, 5360);  // &0x6B14F0
    a1 = addiu(sp, 0x1D0);
    a0 = 6;
    for (;;) {
        // 0x00415000
        charge(ctx, 9);
        lw(v1, a3, 0);
        lw(v0, a3, 4);
        a3 = addiu(a3, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00415024
    charge(ctx, 4);
    a3 = 0x6B0000;
    a3 = addiu(a3, 5408);  // &0x6B1520
    a1 = addiu(sp, 0x170);
    a0 = 12;
    for (;;) {
        // 0x00415034
        charge(ctx, 9);
        lw(v1, a3, 0);
        lw(v0, a3, 4);
        a3 = addiu(a3, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00415058
    charge(ctx, 4);
    a3 = 0x6B0000;
    a3 = addiu(a3, 5504);  // &0x6B1580
    a1 = addiu(sp, 0xE0);
    a0 = 18;
    for (;;) {
        // 0x00415068
        charge(ctx, 9);
        lw(v1, a3, 0);
        lw(v0, a3, 4);
        a3 = addiu(a3, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0041508c
    charge(ctx, 4);
    a3 = 0x6B0000;
    a3 = addiu(a3, 5648);  // &0x6B1610
    a1 = addiu(sp, 0xB0);
    a0 = 6;
    for (;;) {
        // 0x0041509c
        charge(ctx, 9);
        lw(v1, a3, 0);
        lw(v0, a3, 4);
        a3 = addiu(a3, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004150c0
    charge(ctx, 4);
    a3 = 0x6B0000;
    a3 = addiu(a3, 5696);  // &0x6B1640
    a1 = addiu(sp, 0x50);
    a0 = 12;
    for (;;) {
        // 0x004150d0
        charge(ctx, 9);
        lw(v1, a3, 0);
        lw(v0, a3, 4);
        a3 = addiu(a3, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004150f4
    charge(ctx, 4);
    a3 = 0x6B0000;
    a3 = addiu(a3, 5792);  // &0x6B16A0
    a1 = addiu(sp, 0x20);
    a0 = 5;
    for (;;) {
        // 0x00415104
        charge(ctx, 9);
        lw(v1, a3, 0);
        lw(v0, a3, 4);
        a3 = addiu(a3, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00415128
    charge(ctx, 12);
    v0 = addiu(sp, 0x1D0);
    sw(v0, sp, 0x20);
    v0 = addiu(sp, 0x170);
    sw(v0, sp, 0x28);
    v0 = addiu(sp, 0xE0);
    sw(v0, sp, 0x30);
    v0 = addiu(sp, 0xB0);
    sw(v0, sp, 0x38);
    v0 = addiu(sp, 0x50);
    sw(v0, sp, 0x40);
    if (a2 != 0) {
        // 0x00415158
        charge(ctx, 7);
        sh(zero, s0, 148);
        sh(zero, s0, 150);
        lh(v0, a2, kBgEventId);
        v0 = addiu(v0, -5);
        at = sltiu(v0, 10);
        if (at != 0) {
            // 0x00415174
            charge(ctx, 7);
            v1 = 0x7C0000;
            v1 = addiu(v1, -16304);  // &0x7BC050
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x415190u:  // table[0]
                // 0x00415190
                charge(ctx, 3);
                sw(zero, s0, 152);
                break;
            case 0x41519Cu:  // table[5]
                // 0x0041519c
                charge(ctx, 4);
                v0 = 1;
                sw(v0, s0, 152);
                break;
            case 0x4151ACu:  // table[1]
                // 0x004151ac
                charge(ctx, 4);
                v0 = 2;
                sw(v0, s0, 152);
                break;
            case 0x4151BCu:  // table[6]
                // 0x004151bc
                charge(ctx, 4);
                v0 = 3;
                sw(v0, s0, 152);
                break;
            case 0x4151CCu:  // table[2]
                // 0x004151cc
                charge(ctx, 4);
                v0 = 4;
                sw(v0, s0, 152);
                break;
            case 0x4151DCu:  // table[7]
                // 0x004151dc
                charge(ctx, 4);
                v0 = 5;
                sw(v0, s0, 152);
                break;
            case 0x4151ECu:  // table[3]
                // 0x004151ec
                charge(ctx, 4);
                v0 = 6;
                sw(v0, s0, 152);
                break;
            case 0x4151FCu:  // table[8]
                // 0x004151fc
                charge(ctx, 4);
                v0 = 7;
                sw(v0, s0, 152);
                break;
            case 0x41520Cu:  // table[4]
                // 0x0041520c
                charge(ctx, 4);
                v0 = 8;
                sw(v0, s0, 152);
                break;
            case 0x41521Cu:  // table[9]
                // 0x0041521c
                charge(ctx, 2);
                v0 = 9;
                sw(v0, s0, 152);
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
        }
        // 0x00415224
        charge(ctx, 21);
        lw(v1, s0, 152);
        v0 = sra(v1, 1);
        v0 = sll(v0, 3);
        v0 = addu(v0, sp);
        v0 = addiu(v0, 32);
        lw(a1, v0, 0);
        lw(v0, v0, 4);
        a0 = srl(v0, 2);
        v0 = v1 & 0x1;
        v0 = sll(v0, 1);
        mult(v1, v0, a0);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        a1 = addu(a1, v0);
        v0 = sll(a0, 1);
        v0 = addu(v0, a0);
        a2 = sll(v0, 2);
        a0 = s0;
        jal(ctx, 0x415270u, gen::fn_memcpy_00521250);
    }
    // 0x00415278
    charge(ctx, 5);
    lw(a0, s0, 152);
    lh(v1, s0, 148);
    v0 = 1;
    if (v1 != v0) {
        // 0x0041528c
        charge(ctx, 2);
        if (v1 != 0) {
            // 0x00415294
            charge(ctx, 2);
            goto L_004154c8;
        }
        // 0x0041529c
        charge(ctx, 27);
        v0 = sra(a0, 1);
        v0 = sll(v0, 3);
        v0 = addu(v0, sp);
        v0 = addiu(v0, 32);
        lw(a1, v0, 0);
        lw(v0, v0, 4);
        t2 = srl(v0, 2);
        lh(v0, s0, 150);
        v0 = addiu(v0, 1);
        sh(v0, s0, 150);
        t3 = 0;
        t4 = 0;
        t1 = a0 & 0x1;
        a0 = sll(t1, 1);
        v0 = addiu(a0, 1);
        mult(v1, v0, t2);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        t0 = addu(a1, v0);
        mult1(v1, a0, t2);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        a3 = addu(a1, v0);
        for (;;) {
            // 0x00415484
            charge(ctx, 3);
            v0 = slt(t4, t2);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00415308
            charge(ctx, 9);
            v0 = sll(t4, 1);
            v0 = addu(v0, t4);
            t5 = sll(v0, 2);
            a2 = addu(s0, t5);
            lh(a0, a2, kBgEventId);
            lh(v1, s0, 150);
            v0 = slt(v1, a0);
            if (v0 == 0) {
                // 0x0041532c
                charge(ctx, 7);
                a1 = subu(v1, a0);
                a0 = addu(t0, t5);
                v1 = addiu(a0, 6);
                lh(t7, a0, 6);
                at = slt(t7, a1);
                if (at != 0) {
                    // 0x0041547c
                    charge(ctx, 1);
                    t3 = addiu(t3, 1);
                } else {
                    // 0x00415348
                    charge(ctx, 77);
                    v0 = addu(a3, t5);
                    lh(t6, v0, 0);
                    lh(t5, a0, 0);
                    t5 = subu(t5, t6);
                    mult(t5, a1, t5);
                    mtc1(t5, f0);
                    cvt_s_w(f1, f0);
                    mtc1(t7, f0);
                    cvt_s_w(f0, f0);
                    div_s(f1, f1, f0);
                    mtc1(t6, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(t5, f0);
                    sh(t5, a2, 0);
                    lh(t6, v0, 2);
                    lh(t5, a0, 2);
                    t5 = subu(t5, t6);
                    mult1(t5, a1, t5);
                    mtc1(t5, f0);
                    cvt_s_w(f1, f0);
                    lh(t5, v1, 0);
                    mtc1(t5, f0);
                    cvt_s_w(f0, f0);
                    div_s(f1, f1, f0);
                    mtc1(t6, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(t5, f0);
                    sh(t5, a2, 2);
                    lh(t6, v0, 4);
                    lh(t5, a0, 4);
                    t5 = subu(t5, t6);
                    mult(t5, a1, t5);
                    mtc1(t5, f0);
                    cvt_s_w(f1, f0);
                    lh(t5, v1, 0);
                    mtc1(t5, f0);
                    cvt_s_w(f0, f0);
                    div_s(f1, f1, f0);
                    mtc1(t6, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(t5, f0);
                    sh(t5, a2, 4);
                    lwc1(f2, v0, 8);
                    lwc1(f0, a0, 8);
                    sub_s(f1, f0, f2);
                    mtc1(a1, f0);
                    cvt_s_w(f0, f0);
                    mul_s(f1, f0, f1);
                    lh(v0, v1, 0);
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    div_s(f0, f1, f0);
                    add_s(f0, f2, f0);
                    swc1(f0, a2, 8);
                }
            }
            // 0x00415480
            charge(ctx, 1);
            t4 = addiu(t4, 1);
        }
        // 0x00415490
        charge(ctx, 3);
        v0 = slt(t3, t2);
        if (v0 == 0) {
            // 0x0041549c
            charge(ctx, 5);
            v0 = 1;
            sh(v0, s0, 148);
            sh(zero, s0, 150);
            if (t1 == 0) {
                goto L_004154bc;
            }
            // 0x004154b0
            charge(ctx, 3);
            v0 = 2;
            // 0x004154cc (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(ra, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x200);
            return;
        }
    L_004154bc:
        charge(ctx, 3);
        v0 = 0;
        // 0x004154cc (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x200);
        return;
    }
L_004154c8:
    charge(ctx, 1);
    v0 = 1;
    // 0x004154cc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x200);
}

// 0x004154E0 sub_4154E0 -- 356 bytes; frame 0x50: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [fclBgPart4154E0] Sub-handler: sprites 90 at (x, y) and 91 at (x, y + 216), half alpha (sub_40E3F0).
void sub_4154E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f20{ctx, 20};
    // 0x004154e0
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s2 = a2;
    s1 = a3;
    s0 = t0;
    v0 = 0x3F000000;
    mtc1(v0, f1);
    mtc1(t1, f0);
    cvt_s_w(f0, f0);
    mul_s(f20, f1, f0);
    mtc1(s0, f0);
    cvt_s_w(f12, f0);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f20);
    if (cond(ctx)) {
        // 0x00415558
        charge(ctx, 6);
        sub_s(f0, f20, f0);
        cvt_w_s(f0, f0);
        mfc1(a2, f0);
        v0 = lui(0x8000);
        a2 = a2 | v0;
        a2 = a2 & 0xFF;
    } else {
        // 0x00415540
        charge(ctx, 6);
        cvt_w_s(f0, f20);
        mfc1(a2, f0);
        a2 = a2 & 0xFF;
    }
    // 0x00415570
    charge(ctx, 21);
    mtc1(zero, f13);
    v0 = 0x40200000;
    mtc1(v0, f14);
    a0 = s2;
    a1 = s1;
    a3 = 90;
    t0 = 0;
    t1 = 0;
    t2 = 0;
    mov_s(f15, f14);
    jal(ctx, 0x415598u, gen::fn_sub_40E3F0_0040e3f0);
    mtc1(s0, f0);
    cvt_s_w(f12, f0);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f20);
    if (cond(ctx)) {
        // 0x004155dc
        charge(ctx, 6);
        sub_s(f0, f20, f0);
        cvt_w_s(f0, f0);
        mfc1(a2, f0);
        v0 = lui(0x8000);
        a2 = a2 | v0;
        a2 = a2 & 0xFF;
    } else {
        // 0x004155c4
        charge(ctx, 6);
        cvt_w_s(f0, f20);
        mfc1(a2, f0);
        a2 = a2 & 0xFF;
    }
    // 0x004155f4
    charge(ctx, 20);
    a1 = addiu(s1, 216);
    mtc1(zero, f13);
    v0 = 0x40200000;
    mtc1(v0, f14);
    a0 = s2;
    a3 = 91;
    t0 = 0;
    t1 = 0;
    t2 = 0;
    mov_s(f15, f14);
    jal(ctx, 0x41561Cu, gen::fn_sub_40E3F0_0040e3f0);
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00415650 sub_415650 -- 356 bytes; frame 0x50: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [fclBgPart415650] Sub-handler: sprites 92 at (x, y) and 93 at (x, y + 406), half alpha.
void sub_415650(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f20{ctx, 20};
    // 0x00415650
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s2 = a2;
    s1 = a3;
    s0 = t0;
    v0 = 0x3F000000;
    mtc1(v0, f1);
    mtc1(t1, f0);
    cvt_s_w(f0, f0);
    mul_s(f20, f1, f0);
    mtc1(s0, f0);
    cvt_s_w(f12, f0);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f20);
    if (cond(ctx)) {
        // 0x004156c8
        charge(ctx, 6);
        sub_s(f0, f20, f0);
        cvt_w_s(f0, f0);
        mfc1(a2, f0);
        v0 = lui(0x8000);
        a2 = a2 | v0;
        a2 = a2 & 0xFF;
    } else {
        // 0x004156b0
        charge(ctx, 6);
        cvt_w_s(f0, f20);
        mfc1(a2, f0);
        a2 = a2 & 0xFF;
    }
    // 0x004156e0
    charge(ctx, 21);
    mtc1(zero, f13);
    v0 = 0x40200000;
    mtc1(v0, f14);
    a0 = s2;
    a1 = s1;
    a3 = 92;
    t0 = 0;
    t1 = 0;
    t2 = 0;
    mov_s(f15, f14);
    jal(ctx, 0x415708u, gen::fn_sub_40E3F0_0040e3f0);
    mtc1(s0, f0);
    cvt_s_w(f12, f0);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f20);
    if (cond(ctx)) {
        // 0x0041574c
        charge(ctx, 6);
        sub_s(f0, f20, f0);
        cvt_w_s(f0, f0);
        mfc1(a2, f0);
        v0 = lui(0x8000);
        a2 = a2 | v0;
        a2 = a2 & 0xFF;
    } else {
        // 0x00415734
        charge(ctx, 6);
        cvt_w_s(f0, f20);
        mfc1(a2, f0);
        a2 = a2 & 0xFF;
    }
    // 0x00415764
    charge(ctx, 20);
    a1 = addiu(s1, 406);
    mtc1(zero, f13);
    v0 = 0x40200000;
    mtc1(v0, f14);
    a0 = s2;
    a3 = 93;
    t0 = 0;
    t1 = 0;
    t2 = 0;
    mov_s(f15, f14);
    jal(ctx, 0x41578Cu, gen::fn_sub_40E3F0_0040e3f0);
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x004157C0 sub_4157C0 -- 192 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgPart4157C0] Sub-handler: sprites 94 at (x + 44, y + 100), 95 at (x - 20, y + 50), 96 at (x - 26, y + 184).
void sub_4157C0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x004157c0
    enter(ctx, 48);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a2;
    s2 = a3;
    s1 = t0;
    s0 = t1;
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s3, 44);
    a1 = addiu(s2, 100);
    a2 = s0 & 0xFF;
    a3 = 94;
    t0 = 0;
    jal(ctx, 0x415808u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s3, -20);
    a1 = addiu(s2, 50);
    a2 = s0 & 0xFF;
    a3 = 95;
    t0 = 0;
    jal(ctx, 0x415830u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s3, -26);
    a1 = addiu(s2, 184);
    a2 = s0 & 0xFF;
    a3 = 96;
    t0 = 0;
    jal(ctx, 0x415858u, gen::fn_sub_40E3C0_0040e3c0);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00415880 sub_415880 -- 488 bytes; frame 0x50: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [fclBgPart415880] Sub-handler: sprites 97 at (x, y), 98 at (x, y + 306), 99 at (x, y + 407), half alpha.
void sub_415880(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f20{ctx, 20};
    // 0x00415880
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s2 = a2;
    s1 = a3;
    s0 = t0;
    v0 = 0x3F000000;
    mtc1(v0, f1);
    mtc1(t1, f0);
    cvt_s_w(f0, f0);
    mul_s(f20, f1, f0);
    mtc1(s0, f0);
    cvt_s_w(f12, f0);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f20);
    if (cond(ctx)) {
        // 0x004158f8
        charge(ctx, 6);
        sub_s(f0, f20, f0);
        cvt_w_s(f0, f0);
        mfc1(a2, f0);
        v0 = lui(0x8000);
        a2 = a2 | v0;
        a2 = a2 & 0xFF;
    } else {
        // 0x004158e0
        charge(ctx, 6);
        cvt_w_s(f0, f20);
        mfc1(a2, f0);
        a2 = a2 & 0xFF;
    }
    // 0x00415910
    charge(ctx, 21);
    mtc1(zero, f13);
    v0 = 0x40200000;
    mtc1(v0, f14);
    a0 = s2;
    a1 = s1;
    a3 = 97;
    t0 = 0;
    t1 = 0;
    t2 = 0;
    mov_s(f15, f14);
    jal(ctx, 0x415938u, gen::fn_sub_40E3F0_0040e3f0);
    mtc1(s0, f0);
    cvt_s_w(f12, f0);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f20);
    if (cond(ctx)) {
        // 0x0041597c
        charge(ctx, 6);
        sub_s(f0, f20, f0);
        cvt_w_s(f0, f0);
        mfc1(a2, f0);
        v0 = lui(0x8000);
        a2 = a2 | v0;
        a2 = a2 & 0xFF;
    } else {
        // 0x00415964
        charge(ctx, 6);
        cvt_w_s(f0, f20);
        mfc1(a2, f0);
        a2 = a2 & 0xFF;
    }
    // 0x00415994
    charge(ctx, 21);
    a1 = addiu(s1, 306);
    mtc1(zero, f13);
    v0 = 0x40200000;
    mtc1(v0, f14);
    a0 = s2;
    a3 = 98;
    t0 = 0;
    t1 = 0;
    t2 = 0;
    mov_s(f15, f14);
    jal(ctx, 0x4159BCu, gen::fn_sub_40E3F0_0040e3f0);
    mtc1(s0, f0);
    cvt_s_w(f12, f0);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f20);
    if (cond(ctx)) {
        // 0x00415a00
        charge(ctx, 6);
        sub_s(f0, f20, f0);
        cvt_w_s(f0, f0);
        mfc1(a2, f0);
        v0 = lui(0x8000);
        a2 = a2 | v0;
        a2 = a2 & 0xFF;
    } else {
        // 0x004159e8
        charge(ctx, 6);
        cvt_w_s(f0, f20);
        mfc1(a2, f0);
        a2 = a2 & 0xFF;
    }
    // 0x00415a18
    charge(ctx, 20);
    a1 = addiu(s1, 407);
    mtc1(zero, f13);
    v0 = 0x40200000;
    mtc1(v0, f14);
    a0 = s2;
    a3 = 99;
    t0 = 0;
    t1 = 0;
    t2 = 0;
    mov_s(f15, f14);
    jal(ctx, 0x415A40u, gen::fn_sub_40E3F0_0040e3f0);
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00415A70 sub_415A70 -- 192 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgPart415A70] Sub-handler: sprites 101 at (x + 91, y + 49), 102 at (x - 20, y + 47), 103 at (x - 38, y + 149).
void sub_415A70(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x00415a70
    enter(ctx, 48);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a2;
    s2 = a3;
    s1 = t0;
    s0 = t1;
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s3, 91);
    a1 = addiu(s2, 49);
    a2 = s0 & 0xFF;
    a3 = 101;
    t0 = 0;
    jal(ctx, 0x415AB8u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s3, -20);
    a1 = addiu(s2, 47);
    a2 = s0 & 0xFF;
    a3 = 102;
    t0 = 0;
    jal(ctx, 0x415AE0u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s3, -38);
    a1 = addiu(s2, 149);
    a2 = s0 & 0xFF;
    a3 = 103;
    t0 = 0;
    jal(ctx, 0x415B08u, gen::fn_sub_40E3C0_0040e3c0);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00415B30 sub_415B30 -- 64 bytes; frame 0x10: ra sp+0x0
// [fclBgPart415B30] Sub-handler: sprite 100 at (x + 401, y + 150).
void sub_415B30(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x00415b30
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    mtc1(t0, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(a2, 401);
    a1 = addiu(a3, 150);
    a2 = t1 & 0xFF;
    a3 = 100;
    t0 = 0;
    jal(ctx, 0x415B58u, gen::fn_sub_40E3C0_0040e3c0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00415B70 sub_415B70 -- 192 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgPart415B70] Sub-handler: sprites 105..107 at (x + 352, y + 92).
void sub_415B70(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x00415b70
    enter(ctx, 48);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a2;
    s2 = a3;
    s1 = t0;
    s0 = t1;
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s3, 352);
    a1 = addiu(s2, 92);
    a2 = s0 & 0xFF;
    a3 = 105;
    t0 = 0;
    jal(ctx, 0x415BB8u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s3, 352);
    a1 = addiu(s2, 92);
    a2 = s0 & 0xFF;
    a3 = 106;
    t0 = 0;
    jal(ctx, 0x415BE0u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s1, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s3, 352);
    a1 = addiu(s2, 92);
    a2 = s0 & 0xFF;
    a3 = 107;
    t0 = 0;
    jal(ctx, 0x415C08u, gen::fn_sub_40E3C0_0040e3c0);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00415C30 sub_415C30 -- 396 bytes; frame 0xC0: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgPartsDispatchB] As sub_414E10 with the part lists of 0x6B16E0 (0x7CDA28, 0x7CDA30.., 0x6B16C8.., 0x7CDA38,
// 0x7CDA40..).
void sub_415C30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x00415c30
    enter(ctx, 36);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(s4, a1, kBgNodeArea);
    lwc1(f0, gp, -21192);  // 0x7CDA28
    swc1(f0, sp, 0xBC);
    lwc1(f1, gp, -21184);  // 0x7CDA30
    lwc1(f0, gp, -21180);  // 0x7CDA34
    swc1(f1, sp, 0xB0);
    swc1(f0, sp, 0xB4);
    v0 = 0x6B0000;
    lwc1(f2, v0, 5832);  // 0x6B16C8
    v0 = 0x6B0000;
    lwc1(f1, v0, 5836);  // 0x6B16CC
    v0 = 0x6B0000;
    lwc1(f0, v0, 5840);  // 0x6B16D0
    swc1(f2, sp, 0xA0);
    swc1(f1, sp, 0xA4);
    swc1(f0, sp, 0xA8);
    lwc1(f0, gp, -21176);  // 0x7CDA38
    swc1(f0, sp, 0xB8);
    lwc1(f1, gp, -21168);  // 0x7CDA40
    lwc1(f0, gp, -21164);  // 0x7CDA44
    swc1(f1, sp, 0x98);
    swc1(f0, sp, 0x9C);
    a2 = 0x6B0000;
    a2 = addiu(a2, 5856);  // &0x6B16E0
    a1 = addiu(sp, 0x70);
    a0 = 5;
    for (;;) {
        // 0x00415cc0
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
    // 0x00415ce4
    charge(ctx, 19);
    v0 = addiu(sp, 0xBC);
    sw(v0, sp, 0x70);
    v0 = addiu(sp, 0xB0);
    sw(v0, sp, 0x78);
    v0 = addiu(sp, 0xA0);
    sw(v0, sp, 0x80);
    v0 = addiu(sp, 0xB8);
    sw(v0, sp, 0x88);
    v0 = addiu(sp, 0x98);
    sw(v0, sp, 0x90);
    lw(v0, s4, 152);
    v0 = sra(v0, 1);
    v0 = sll(v0, 3);
    v0 = addu(v0, sp);
    lw(s3, v0, 112);
    lw(s2, v0, 116);
    s5 = 0;
    for (;;) {
        // 0x00415d84
        charge(ctx, 3);
        v0 = slt(s5, s2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00415d30
        charge(ctx, 21);
        v0 = sll(s5, 1);
        v0 = addu(v0, s5);
        v0 = sll(v0, 2);
        v0 = addu(s4, v0);
        lwc1(f13, v0, 8);
        lh(a2, v0, 0);
        lh(a3, v0, 2);
        lh(t1, v0, 4);
        mtc1(zero, f12);
        a0 = s1;
        a1 = s0;
        t0 = 0;
        t2 = 0;
        t3 = 0;
        mov_s(f14, f13);
        v0 = sll(s5, 2);
        v0 = addu(s3, v0);
        lw(v0, v0, 0);
        jalr(ctx, 0x415D78u, v0.u());
        s5 = addiu(s5, 1);
    }
    // 0x00415d90
    charge(ctx, 11);
    v0 = 0;
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xC0);
}

// 0x004167D0 sub_4167D0 -- 956 bytes; frame 0xA0: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgPartStatus] Sub-handler: the status panel -- sprites 177..183 at (x + 381, y + 151..207) and the four numbers
// of the two 80-byte records at area +80 / +160 (their s16 +16 / +18, "%d" 0x7CDA50 through sprintf, drawn by
// sub_40EB50 at the offsets 0x7CDA58 / 0x7CDA5C), sprite 183 instead of the first record's numbers when its +4 is 13,
// and sprite 5 frame (area +160 +4) at (x + 493, y + 159).
void sub_4167D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x004167d0
    enter(ctx, 99);  // entry check point + this block's cycles
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
    s4 = a2;
    s3 = a3;
    s2 = t0;
    s1 = t1;
    lw(a2, a1, kBgNodeArea);
    lh(a1, gp, -21144);  // 0x7CDA58
    lh(a0, gp, -21142);  // 0x7CDA5A
    lh(v1, gp, -21140);  // 0x7CDA5C
    lh(v0, gp, -21138);  // 0x7CDA5E
    sh(a1, sp, 0x98);
    sh(a0, sp, 0x9A);
    sh(v1, sp, 0x9C);
    sh(v0, sp, 0x9E);
    s0 = addiu(a2, 80);
    s5 = addiu(a2, 160);
    mtc1(s2, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s4, 381);
    a1 = addiu(s3, 151);
    a2 = s1 & 0xFF;
    a3 = 177;
    t0 = 0;
    jal(ctx, 0x416854u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s2, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s4, 381);
    a1 = addiu(s3, 151);
    a2 = s1 & 0xFF;
    a3 = 178;
    t0 = 0;
    jal(ctx, 0x41687Cu, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s2, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s4, 381);
    a1 = addiu(s3, 151);
    a2 = s1 & 0xFF;
    a3 = 181;
    t0 = 0;
    jal(ctx, 0x4168A4u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s2, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s4, 493);
    a1 = addiu(s3, 159);
    a2 = s1 & 0xFF;
    lbu(t0, s5, 4);
    a3 = 5;
    jal(ctx, 0x4168CCu, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s2, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s4, 381);
    a1 = addiu(s3, 151);
    a2 = s1 & 0xFF;
    a3 = 179;
    t0 = 0;
    jal(ctx, 0x4168F4u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s2, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s4, 381);
    a1 = addiu(s3, 151);
    a2 = s1 & 0xFF;
    a3 = 180;
    t0 = 0;
    jal(ctx, 0x41691Cu, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s2, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s4, 381);
    a1 = addiu(s3, 179);
    a2 = s1 & 0xFF;
    a3 = 181;
    t0 = 0;
    jal(ctx, 0x416944u, gen::fn_sub_40E3C0_0040e3c0);
    lbu(v1, s0, 4);
    v0 = 13;
    if (v1 == v0) {
        // 0x004169ac
        charge(ctx, 10);
        mtc1(s2, f0);
        cvt_s_w(f12, f0);
        a0 = addiu(s4, 381);
        a1 = addiu(s3, 179);
        a2 = s1 & 0xFF;
        a3 = 183;
        t0 = 0;
        jal(ctx, 0x4169CCu, gen::fn_sub_40E3C0_0040e3c0);
    } else {
        // 0x0041695c
        charge(ctx, 20);
        lh(a2, s0, 16);
        a0 = addiu(sp, 0x90);
        a1 = addiu(gp, -21152);  // "%d"
        jal(ctx, 0x416968u, gen::fn_sprintf_00523ac8);
        v1 = addiu(s4, 381);
        lh(v0, sp, 0x98);
        a0 = addu(v1, v0);
        v1 = addiu(s3, 179);
        lh(v0, sp, 0x9A);
        a1 = addu(v1, v0);
        mtc1(zero, f12);
        a2 = s1 & 0xFF;
        a3 = 1;
        t0 = addiu(sp, 0x90);
        t1 = 2;
        jal(ctx, 0x41699Cu, gen::fn_sub_40EB50_0040eb50);
    }
    // 0x004169d4
    charge(ctx, 43);
    mtc1(s2, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s4, 381);
    a1 = addiu(s3, 179);
    a2 = s1 & 0xFF;
    a3 = 182;
    t0 = 0;
    jal(ctx, 0x4169F4u, gen::fn_sub_40E3C0_0040e3c0);
    lh(a2, s5, 16);
    a0 = addiu(sp, 0x90);
    a1 = addiu(gp, -21152);  // "%d"
    jal(ctx, 0x416A08u, gen::fn_sprintf_00523ac8);
    lh(s7, sp, 0x9E);
    lh(v1, sp, 0x9C);
    v0 = addiu(s4, 381);
    s6 = addu(v0, v1);
    v0 = addiu(s3, 179);
    a1 = addu(v0, s7);
    mtc1(zero, f12);
    a2 = s1 & 0xFF;
    a0 = s6;
    a3 = 1;
    t0 = addiu(sp, 0x90);
    t1 = 2;
    jal(ctx, 0x416A40u, gen::fn_sub_40EB50_0040eb50);
    mtc1(s2, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s4, 381);
    a1 = addiu(s3, 207);
    a2 = s1 & 0xFF;
    a3 = 181;
    t0 = 0;
    jal(ctx, 0x416A68u, gen::fn_sub_40E3C0_0040e3c0);
    lbu(v1, s0, 4);
    v0 = 13;
    if (v1 == v0) {
        // 0x00416ad0
        charge(ctx, 10);
        mtc1(s2, f0);
        cvt_s_w(f12, f0);
        a0 = addiu(s4, 381);
        a1 = addiu(s3, 207);
        a2 = s1 & 0xFF;
        a3 = 183;
        t0 = 0;
        jal(ctx, 0x416AF0u, gen::fn_sub_40E3C0_0040e3c0);
    } else {
        // 0x00416a80
        charge(ctx, 20);
        lh(a2, s0, 18);
        a0 = addiu(sp, 0x90);
        a1 = addiu(gp, -21152);  // "%d"
        jal(ctx, 0x416A8Cu, gen::fn_sprintf_00523ac8);
        v1 = addiu(s4, 381);
        lh(v0, sp, 0x98);
        a0 = addu(v1, v0);
        v1 = addiu(s3, 207);
        lh(v0, sp, 0x9A);
        a1 = addu(v1, v0);
        mtc1(zero, f12);
        a2 = s1 & 0xFF;
        a3 = 1;
        t0 = addiu(sp, 0x90);
        t1 = 2;
        jal(ctx, 0x416AC0u, gen::fn_sub_40EB50_0040eb50);
    }
    // 0x00416af8
    charge(ctx, 37);
    mtc1(s2, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s4, 381);
    a1 = addiu(s3, 207);
    a2 = s1 & 0xFF;
    a3 = 182;
    t0 = 0;
    jal(ctx, 0x416B18u, gen::fn_sub_40E3C0_0040e3c0);
    lh(a2, s5, 18);
    a0 = addiu(sp, 0x90);
    a1 = addiu(gp, -21152);  // "%d"
    jal(ctx, 0x416B2Cu, gen::fn_sprintf_00523ac8);
    v0 = addiu(s3, 207);
    a1 = addu(v0, s7);
    mtc1(zero, f12);
    a2 = s1 & 0xFF;
    a0 = s6;
    a3 = 1;
    t0 = addiu(sp, 0x90);
    t1 = 2;
    jal(ctx, 0x416B54u, gen::fn_sub_40EB50_0040eb50);
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

// 0x00416D20 sub_416D20 -- 780 bytes; frame 0x70: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [fclBgPartDate] Sub-handler: the date panel -- sprites 186..192 at (x - 7, y + 71), the month (area +188 +2) and day
// (+3) as one or two digits (sprites 6 / 7) and the weekday sprite 8 frame
// (clndGetWeekDay(clndGetDaysSinceStartFromDate(month, day)) + 6) % 7.
void sub_416D20(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f20{ctx, 20};
    // 0x00416d20
    enter(ctx, 88);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s4 = a2;
    s3 = a3;
    s2 = t0;
    s1 = t1;
    lw(v0, a1, kBgNodeArea);
    s0 = addiu(v0, 188);
    mtc1(s2, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s4, -7);
    a1 = addiu(s3, 71);
    a2 = s1 & 0xFF;
    a3 = 186;
    t0 = 0;
    jal(ctx, 0x416D78u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s2, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s4, -7);
    a1 = addiu(s3, 71);
    a2 = s1 & 0xFF;
    a3 = 187;
    t0 = 0;
    jal(ctx, 0x416DA0u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s2, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s4, -7);
    a1 = addiu(s3, 71);
    a2 = s1 & 0xFF;
    a3 = 188;
    t0 = 0;
    jal(ctx, 0x416DC8u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s2, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s4, -7);
    a1 = addiu(s3, 71);
    a2 = s1 & 0xFF;
    a3 = 189;
    t0 = 0;
    jal(ctx, 0x416DF0u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s2, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s4, -7);
    a1 = addiu(s3, 71);
    a2 = s1 & 0xFF;
    a3 = 190;
    t0 = 0;
    jal(ctx, 0x416E18u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s2, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s4, -7);
    a1 = addiu(s3, 71);
    a2 = s1 & 0xFF;
    a3 = 191;
    t0 = 0;
    jal(ctx, 0x416E40u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(s2, f0);
    cvt_s_w(f12, f0);
    a0 = addiu(s4, -7);
    a1 = addiu(s3, 71);
    a2 = s1 & 0xFF;
    a3 = 192;
    t0 = 0;
    jal(ctx, 0x416E68u, gen::fn_sub_40E3C0_0040e3c0);
    lb(t0, s0, 2);
    at = slti(t0, 10);
    if (at == 0) {
        // 0x00416eac
        charge(ctx, 25);
        mtc1(s2, f0);
        cvt_s_w(f12, f0);
        a0 = addiu(s4, 12);
        a1 = addiu(s3, 156);
        a2 = s1 & 0xFF;
        v0 = 10;
        div(t0, v0);
        mflo(t0);
        a3 = 6;
        jal(ctx, 0x416ED4u, gen::fn_sub_40E3C0_0040e3c0);
        mtc1(s2, f0);
        cvt_s_w(f12, f0);
        a0 = addiu(s4, 33);
        a1 = addiu(s3, 156);
        a2 = s1 & 0xFF;
        lb(v1, s0, 2);
        v0 = 10;
        div(v1, v0);
        mfhi(t0);
        a3 = 6;
        jal(ctx, 0x416F08u, gen::fn_sub_40E3C0_0040e3c0);
    } else {
        // 0x00416e80
        charge(ctx, 11);
        mtc1(s2, f0);
        cvt_s_w(f12, f0);
        a0 = addiu(s4, 29);
        a1 = addiu(s3, 156);
        a2 = s1 & 0xFF;
        a3 = 6;
        jal(ctx, 0x416E9Cu, gen::fn_sub_40E3C0_0040e3c0);
    }
    // 0x00416f10
    charge(ctx, 4);
    lb(t0, s0, 3);
    at = slti(t0, 10);
    if (at == 0) {
        // 0x00416f4c
        charge(ctx, 25);
        mtc1(s2, f0);
        cvt_s_w(f12, f0);
        a0 = addiu(s4, 80);
        a1 = addiu(s3, 159);
        a2 = s1 & 0xFF;
        v0 = 10;
        div(t0, v0);
        mflo(t0);
        a3 = 7;
        jal(ctx, 0x416F74u, gen::fn_sub_40E3C0_0040e3c0);
        mtc1(s2, f0);
        cvt_s_w(f12, f0);
        a0 = addiu(s4, 106);
        a1 = addiu(s3, 159);
        a2 = s1 & 0xFF;
        lb(v1, s0, 3);
        v0 = 10;
        div(v1, v0);
        mfhi(t0);
        a3 = 7;
        jal(ctx, 0x416FA8u, gen::fn_sub_40E3C0_0040e3c0);
    } else {
        // 0x00416f20
        charge(ctx, 11);
        mtc1(s2, f0);
        cvt_s_w(f12, f0);
        a0 = addiu(s4, 95);
        a1 = addiu(s3, 159);
        a2 = s1 & 0xFF;
        a3 = 7;
        jal(ctx, 0x416F3Cu, gen::fn_sub_40E3C0_0040e3c0);
    }
    // 0x00416fb0
    charge(ctx, 31);
    mtc1(s2, f0);
    cvt_s_w(f20, f0);
    lb(a0, s0, 2);
    lb(a1, s0, 3);
    jal(ctx, 0x416FC4u, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);
    a0 = v0;
    jal(ctx, 0x416FD0u, gen::fn_clndGetWeekDay_0017dae0);
    v1 = addiu(v0, 6);
    v0 = 7;
    div(v1, v0);
    mfhi(t0);
    a0 = addiu(s4, 107);
    a1 = addiu(s3, 185);
    a2 = s1 & 0xFF;
    mov_s(f12, f20);
    a3 = 8;
    jal(ctx, 0x416FFCu, gen::fn_sub_40E3C0_0040e3c0);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00417030 sub_417030 -- 296 bytes; frame 0x90: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgPartsDispatchC] As sub_414E10 for the part lists of 0x6B1830 / 0x7CDA60, picked by area +76 / 2.
void sub_417030(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x00417030
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(s4, a1, kBgNodeArea);
    a2 = 0x6B0000;
    a2 = addiu(a2, 6192);  // "@bA"
    a1 = addiu(sp, 0x70);
    a0 = 3;
    for (;;) {
        // 0x0041706c
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
    // 0x00417090
    charge(ctx, 15);
    lwc1(f1, gp, -21136);  // 0x7CDA60
    lwc1(f0, gp, -21132);  // 0x7CDA64
    swc1(f1, sp, 0x88);
    swc1(f0, sp, 0x8C);
    v0 = addiu(sp, 0x70);
    sw(v0, sp, 0x88);
    lw(v0, s4, 76);
    v0 = sra(v0, 1);
    v0 = sll(v0, 3);
    v0 = addu(v0, sp);
    lw(s3, v0, 136);
    lw(s2, v0, 140);
    s5 = 0;
    for (;;) {
        // 0x00417120
        charge(ctx, 3);
        v0 = slt(s5, s2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x004170cc
        charge(ctx, 21);
        v0 = sll(s5, 1);
        v0 = addu(v0, s5);
        v0 = sll(v0, 2);
        v0 = addu(s4, v0);
        lwc1(f13, v0, 8);
        lh(a2, v0, 0);
        lh(a3, v0, 2);
        lh(t1, v0, 4);
        mtc1(zero, f12);
        a0 = s1;
        a1 = s0;
        t0 = 0;
        t2 = 0;
        t3 = 0;
        mov_s(f14, f13);
        v0 = sll(s5, 2);
        v0 = addu(s3, v0);
        lw(v0, v0, 0);
        jalr(ctx, 0x417114u, v0.u());
        s5 = addiu(s5, 1);
    }
    // 0x0041712c
    charge(ctx, 11);
    v0 = 0;
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

}  // namespace p3fes::game
