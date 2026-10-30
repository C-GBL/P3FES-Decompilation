// The battle UI band 0x1EF500-0x26503C and the battle band's UI part 0x271230-0x27BBA0, third pass (slice battle_ui3):
// the module works of the result / panel / command-menu / shuffle files -- their init, flag and lookup accessors, the
// command-panel and result-panel sprite set-ups, the gc_model.c card geometry, the sfl_data.c tables -- hand-decompiled
// from SLUS_216.21 (docs/ANALYSIS/27_unmapped_bands.md section 3). The layouts and the names of the offsets are in
// game/include/p3fes/game/battle_ui3.h; tests/game/test_battle_ui3.cpp pairs every function with its recompiled body.
//
// Each body started as p3fes_handgen's output: register for register and block for block the recompiled body (frame,
// spills, $ra links, cycle charges, check points), on the register view of game/include/p3fes/game/hg_cpu.h. The
// readability pass on top names what the instructions already do -- the role of each function (proposed names in
// brackets), the $gp slots of the module works and their fields as constants of the same value -- without moving a
// load, store, call, charge or check point. The common shape of an accessor: `lw(v0, gp, kGpX)`; when 0, K_Assert(file,
// line) (`jr $ra` in retail: the body carries on and reads through the null work, as the original does); then the
// field.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/battle_ui3.h"

namespace p3fes::recomp_gen {
void fn_bpIfontDrawNumber_00238980(p3fes::EEContext&);
void fn_datCalcChkBadStatus_00300580(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_datSetFlag_0016f1f0(p3fes::EEContext&);
void fn_frFontChainCentreAt_003b1c90(p3fes::EEContext&);
void fn_frFontChainMoveTo_003b1c40(p3fes::EEContext&);
void fn_msgWinRequestMessage_003c7430(p3fes::EEContext&);
void fn_nullsub_11_0021c7e0(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_1F5810_001f5810(p3fes::EEContext&);
void fn_sub_1FE510_001fe510(p3fes::EEContext&);
void fn_sub_209C00_00209c00(p3fes::EEContext&);
void fn_sub_209D00_00209d00(p3fes::EEContext&);
void fn_sub_209DC0_00209dc0(p3fes::EEContext&);
void fn_sub_209DD0_00209dd0(p3fes::EEContext&);
void fn_sub_209E10_00209e10(p3fes::EEContext&);
void fn_sub_209E20_00209e20(p3fes::EEContext&);
void fn_sub_209E60_00209e60(p3fes::EEContext&);
void fn_sub_209E70_00209e70(p3fes::EEContext&);
void fn_sub_209EA0_00209ea0(p3fes::EEContext&);
void fn_sub_209F00_00209f00(p3fes::EEContext&);
void fn_sub_20A800_0020a800(p3fes::EEContext&);
void fn_sub_20C590_0020c590(p3fes::EEContext&);
void fn_sub_20C5F0_0020c5f0(p3fes::EEContext&);
void fn_sub_20C7B0_0020c7b0(p3fes::EEContext&);
void fn_sub_20CCC0_0020ccc0(p3fes::EEContext&);
void fn_sub_20CD50_0020cd50(p3fes::EEContext&);
void fn_sub_20CDA0_0020cda0(p3fes::EEContext&);
void fn_sub_20D7D0_0020d7d0(p3fes::EEContext&);
void fn_sub_20DFE0_0020dfe0(p3fes::EEContext&);
void fn_sub_20E4C0_0020e4c0(p3fes::EEContext&);
void fn_sub_20E510_0020e510(p3fes::EEContext&);
void fn_sub_20E590_0020e590(p3fes::EEContext&);
void fn_sub_20E690_0020e690(p3fes::EEContext&);
void fn_sub_20EC00_0020ec00(p3fes::EEContext&);
void fn_sub_20F720_0020f720(p3fes::EEContext&);
void fn_sub_20FC40_0020fc40(p3fes::EEContext&);
void fn_sub_20FC90_0020fc90(p3fes::EEContext&);
void fn_sub_20FD80_0020fd80(p3fes::EEContext&);
void fn_sub_215830_00215830(p3fes::EEContext&);
void fn_sub_215A50_00215a50(p3fes::EEContext&);
void fn_sub_219C90_00219c90(p3fes::EEContext&);
void fn_sub_21A3A0_0021a3a0(p3fes::EEContext&);
void fn_sub_21A410_0021a410(p3fes::EEContext&);
void fn_sub_21A480_0021a480(p3fes::EEContext&);
void fn_sub_21A590_0021a590(p3fes::EEContext&);
void fn_sub_21AC90_0021ac90(p3fes::EEContext&);
void fn_sub_21AE30_0021ae30(p3fes::EEContext&);
void fn_sub_21AF30_0021af30(p3fes::EEContext&);
void fn_sub_21AFE0_0021afe0(p3fes::EEContext&);
void fn_sub_21B150_0021b150(p3fes::EEContext&);
void fn_sub_21B1F0_0021b1f0(p3fes::EEContext&);
void fn_sub_21B2D0_0021b2d0(p3fes::EEContext&);
void fn_sub_21B3A0_0021b3a0(p3fes::EEContext&);
void fn_sub_21B420_0021b420(p3fes::EEContext&);
void fn_sub_21B670_0021b670(p3fes::EEContext&);
void fn_sub_21BAB0_0021bab0(p3fes::EEContext&);
void fn_sub_21BB00_0021bb00(p3fes::EEContext&);
void fn_sub_21BB50_0021bb50(p3fes::EEContext&);
void fn_sub_21C3F0_0021c3f0(p3fes::EEContext&);
void fn_sub_21C450_0021c450(p3fes::EEContext&);
void fn_sub_21C550_0021c550(p3fes::EEContext&);
void fn_sub_21C7F0_0021c7f0(p3fes::EEContext&);
void fn_sub_21C860_0021c860(p3fes::EEContext&);
void fn_sub_21C8B0_0021c8b0(p3fes::EEContext&);
void fn_sub_21C930_0021c930(p3fes::EEContext&);
void fn_sub_21CCA0_0021cca0(p3fes::EEContext&);
void fn_sub_21CCE0_0021cce0(p3fes::EEContext&);
void fn_sub_21D3B0_0021d3b0(p3fes::EEContext&);
void fn_sub_21D8E0_0021d8e0(p3fes::EEContext&);
void fn_sub_21D950_0021d950(p3fes::EEContext&);
void fn_sub_21E380_0021e380(p3fes::EEContext&);
void fn_sub_21EA00_0021ea00(p3fes::EEContext&);
void fn_sub_21EAC0_0021eac0(p3fes::EEContext&);
void fn_sub_2226F0_002226f0(p3fes::EEContext&);
void fn_sub_2227B0_002227b0(p3fes::EEContext&);
void fn_sub_222870_00222870(p3fes::EEContext&);
void fn_sub_222930_00222930(p3fes::EEContext&);
void fn_sub_222A60_00222a60(p3fes::EEContext&);
void fn_sub_222B90_00222b90(p3fes::EEContext&);
void fn_sub_222D60_00222d60(p3fes::EEContext&);
void fn_sub_222ED0_00222ed0(p3fes::EEContext&);
void fn_sub_222FA0_00222fa0(p3fes::EEContext&);
void fn_sub_2230E0_002230e0(p3fes::EEContext&);
void fn_sub_224660_00224660(p3fes::EEContext&);
void fn_sub_224860_00224860(p3fes::EEContext&);
void fn_sub_226320_00226320(p3fes::EEContext&);
void fn_sub_22B4E0_0022b4e0(p3fes::EEContext&);
void fn_sub_22B580_0022b580(p3fes::EEContext&);
void fn_sub_22BF60_0022bf60(p3fes::EEContext&);
void fn_sub_22C0E0_0022c0e0(p3fes::EEContext&);
void fn_sub_22C210_0022c210(p3fes::EEContext&);
void fn_sub_22E780_0022e780(p3fes::EEContext&);
void fn_sub_22E850_0022e850(p3fes::EEContext&);
void fn_sub_2337E0_002337e0(p3fes::EEContext&);
void fn_sub_233850_00233850(p3fes::EEContext&);
void fn_sub_233D70_00233d70(p3fes::EEContext&);
void fn_sub_234630_00234630(p3fes::EEContext&);
void fn_sub_239170_00239170(p3fes::EEContext&);
void fn_sub_23D7A0_0023d7a0(p3fes::EEContext&);
void fn_sub_23D7F0_0023d7f0(p3fes::EEContext&);
void fn_sub_245E00_00245e00(p3fes::EEContext&);
void fn_sub_245E50_00245e50(p3fes::EEContext&);
void fn_sub_249130_00249130(p3fes::EEContext&);
void fn_sub_249600_00249600(p3fes::EEContext&);
void fn_sub_249650_00249650(p3fes::EEContext&);
void fn_sub_249680_00249680(p3fes::EEContext&);
void fn_sub_24A180_0024a180(p3fes::EEContext&);
void fn_sub_24A7F0_0024a7f0(p3fes::EEContext&);
void fn_sub_24B8A0_0024b8a0(p3fes::EEContext&);
void fn_sub_24BA30_0024ba30(p3fes::EEContext&);
void fn_sub_24D110_0024d110(p3fes::EEContext&);
void fn_sub_24DA00_0024da00(p3fes::EEContext&);
void fn_sub_2519D0_002519d0(p3fes::EEContext&);
void fn_sub_251E10_00251e10(p3fes::EEContext&);
void fn_sub_251E80_00251e80(p3fes::EEContext&);
void fn_sub_253410_00253410(p3fes::EEContext&);
void fn_sub_254F20_00254f20(p3fes::EEContext&);
void fn_sub_25CDB0_0025cdb0(p3fes::EEContext&);
void fn_sub_25CE30_0025ce30(p3fes::EEContext&);
void fn_sub_25D760_0025d760(p3fes::EEContext&);
void fn_sub_25D7B0_0025d7b0(p3fes::EEContext&);
void fn_sub_25D800_0025d800(p3fes::EEContext&);
void fn_sub_25D850_0025d850(p3fes::EEContext&);
void fn_sub_260900_00260900(p3fes::EEContext&);
void fn_sub_260920_00260920(p3fes::EEContext&);
void fn_sub_260940_00260940(p3fes::EEContext&);
void fn_sub_260970_00260970(p3fes::EEContext&);
void fn_sub_2626E0_002626e0(p3fes::EEContext&);
void fn_sub_264CA0_00264ca0(p3fes::EEContext&);
void fn_sub_264D80_00264d80(p3fes::EEContext&);
void fn_sub_272330_00272330(p3fes::EEContext&);
void fn_sub_2737A0_002737a0(p3fes::EEContext&);
void fn_sub_273980_00273980(p3fes::EEContext&);
void fn_sub_273E10_00273e10(p3fes::EEContext&);
void fn_sub_274D40_00274d40(p3fes::EEContext&);
void fn_sub_274D90_00274d90(p3fes::EEContext&);
void fn_sub_274E10_00274e10(p3fes::EEContext&);
void fn_sub_274E90_00274e90(p3fes::EEContext&);
void fn_sub_275A70_00275a70(p3fes::EEContext&);
void fn_sub_275A90_00275a90(p3fes::EEContext&);
void fn_sub_275BC0_00275bc0(p3fes::EEContext&);
void fn_sub_2760F0_002760f0(p3fes::EEContext&);
void fn_sub_276870_00276870(p3fes::EEContext&);
void fn_sub_276910_00276910(p3fes::EEContext&);
void fn_sub_276CC0_00276cc0(p3fes::EEContext&);
void fn_sub_276D10_00276d10(p3fes::EEContext&);
void fn_sub_279450_00279450(p3fes::EEContext&);
void fn_sub_2794C0_002794c0(p3fes::EEContext&);
void fn_sub_279510_00279510(p3fes::EEContext&);
void fn_sub_279580_00279580(p3fes::EEContext&);
void fn_sub_2795F0_002795f0(p3fes::EEContext&);
void fn_sub_2796B0_002796b0(p3fes::EEContext&);
void fn_sub_279700_00279700(p3fes::EEContext&);
void fn_sub_279750_00279750(p3fes::EEContext&);
void fn_sub_2797A0_002797a0(p3fes::EEContext&);
void fn_sub_2797F0_002797f0(p3fes::EEContext&);
void fn_sub_279840_00279840(p3fes::EEContext&);
void fn_sub_279890_00279890(p3fes::EEContext&);
void fn_sub_2798F0_002798f0(p3fes::EEContext&);
void fn_sub_27B610_0027b610(p3fes::EEContext&);
void fn_sub_27B6C0_0027b6c0(p3fes::EEContext&);
void fn_sub_27BB50_0027bb50(p3fes::EEContext&);
void fn_sub_2C1CE0_002c1ce0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace bui3;

// 0x00209D00 sub_209D00 -- 64 bytes; frame 0x10: ra sp+0x0
// [sflData_GetTableA] sfl_data.c: $v0 = the shuffle data table 0x68CDE0 when sub_17D800() (the scenario mode:
// The Answer), else 0x68CA80. Callers: the card reward sub_1F7210, sub_1F9170.
void sub_209D00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00209d00
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x209D08u, gen::fn_sub_17D800_0017d800);
    if (v0 == 0) {
        // 0x00209d28
        charge(ctx, 2);
        v0 = 0x690000;
        v0 = addiu(v0, -13696);  // &0x68CA80
    } else {
        // 0x00209d18
        charge(ctx, 4);
        v0 = 0x690000;
        v0 = addiu(v0, -12832);  // &0x68CDE0
    }
    // 0x00209d30 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00209DC0 sub_209DC0 -- 16 bytes; leaf frame (no stack)
// [sflData_GetTableB] sfl_data.c: $v0 = the table 0x68D140.
void sub_209DC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00209dc0
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x690000;
    v0 = addiu(v0, -11968);  // &0x68D140
}

// 0x00209DD0 sub_209DD0 -- 64 bytes; frame 0x10: ra sp+0x0
// [sflData_GetTableC] sfl_data.c: $v0 = 0x68D910 when sub_17D800() (The Answer), else 0x68D8F0.
void sub_209DD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00209dd0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x209DD8u, gen::fn_sub_17D800_0017d800);
    if (v0 == 0) {
        // 0x00209df8
        charge(ctx, 2);
        v0 = 0x690000;
        v0 = addiu(v0, -10000);  // &0x68D8F0
    } else {
        // 0x00209de8
        charge(ctx, 4);
        v0 = 0x690000;
        v0 = addiu(v0, -9968);  // &0x68D910
    }
    // 0x00209e00 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00209E10 sub_209E10 -- 16 bytes; leaf frame (no stack)
// [sflData_GetTableD] sfl_data.c: $v0 = the table 0x68D930.
void sub_209E10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00209e10
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x690000;
    v0 = addiu(v0, -9936);  // &0x68D930
}

// 0x00209E20 sub_209E20 -- 64 bytes; frame 0x10: ra sp+0x0
// [sflData_GetTableE] sfl_data.c: $v0 = 0x68DE20 when sub_17D800() (The Answer), else 0x68DD20.
void sub_209E20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00209e20
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x209E28u, gen::fn_sub_17D800_0017d800);
    if (v0 == 0) {
        // 0x00209e48
        charge(ctx, 2);
        v0 = 0x690000;
        v0 = addiu(v0, -8928);  // &0x68DD20
    } else {
        // 0x00209e38
        charge(ctx, 4);
        v0 = 0x690000;
        v0 = addiu(v0, -8672);  // &0x68DE20
    }
    // 0x00209e50 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00209E60 sub_209E60 -- 16 bytes; leaf frame (no stack)
// [sflData_GetTableF] sfl_data.c: $v0 = the table 0x68DF20.
void sub_209E60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00209e60
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x690000;
    v0 = addiu(v0, -8416);  // &0x68DF20
}

// 0x00209E70 sub_209E70 -- 16 bytes; leaf frame (no stack)
// [sflData_GetTableG] sfl_data.c: $v0 = the table 0x68DF30.
void sub_209E70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00209e70
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x690000;
    v0 = addiu(v0, -8400);  // &0x68DF30
}

// 0x00209EA0 sub_209EA0 -- 88 bytes; leaf frame (no stack)
// [gcModel_InitHeader](model) gc_model.c: the common header of a card model -- flags, +16..+24, +32..+40, +56,
// +60 and the grid (+220) zero, +28 and the scale (+44..+52) 1.0f, the RGBA (+64..+67) 0xFF.
void sub_209EA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00209ea0
    enter(ctx, 22);  // entry check point + this block's cycles
    sw(zero, a0, kGcmFlags);
    sw(zero, a0, 56);
    sw(zero, a0, 32);
    sw(zero, a0, 36);
    sw(zero, a0, 40);
    v1 = 0x3F800000;
    sw(v1, a0, 28);
    sw(zero, a0, 16);
    sw(zero, a0, 20);
    sw(zero, a0, 24);
    sw(v1, a0, kGcmScale);
    sw(v1, a0, kGcmScale + 4);
    sw(v1, a0, kGcmScale + 8);
    sw(zero, a0, 60);
    v1 = 255;
    sb(v1, a0, kGcmColour);
    sb(v1, a0, kGcmColour + 1);
    sb(v1, a0, kGcmColour + 2);
    sb(v1, a0, kGcmColour + 3);
    sw(zero, a0, kGcmGrid);
}

// 0x0020C590 sub_20C590 -- 84 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [gcModel_SetCardId](model, u16 id) gc_model.c: asserts kind == 0 (line 1161), +372 = id (u16).
void sub_20C590(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0020c590
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v1, a0, kGcmKind);
    if (v1 != 0) {
        // 0x0020c5b4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -8032);  // "gc_model.c"
        a1 = 1161;
        jal(ctx, 0x20C5C0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0020c5c8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    sh(s0, s1, kGcmParamB);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0020C5F0 sub_20C5F0 -- 104 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [gcModel_SetParams](model, a, b) gc_model.c: asserts kind == 1 (line 1170), +368 = a, +372 = b.
void sub_20C5F0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0020c5f0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    lw(a0, a0, kGcmKind);
    v1 = 1;
    if (a0 != v1) {
        // 0x0020c620
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -8032);  // "gc_model.c"
        a1 = 1170;
        jal(ctx, 0x20C62Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0020c634 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    sw(s1, s2, kGcmParamA);
    sw(s0, s2, kGcmParamB);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0020C7B0 sub_20C7B0 -- 288 bytes; frame 0x40
// [gcModel_InitQuad](quad) gc_model.c: a white 4-vertex card quad: x +-3.0, y +-3.84 (0x7CB008 / 0x7CB00C), z 0,
// RGBA 0xFF, the uv corners.
void sub_20C7B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4};
    // 0x0020c7b0
    enter(ctx, 72);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v1 = 0x40400000;
    sw(v1, sp, 0x30);
    lwc1(f4, gp, kGpCardHalfH);  // 0x7CB008
    swc1(f4, sp, 0x34);
    sw(zero, sp, 0x38);
    lwc1(f2, sp, 0x30);
    lwc1(f1, sp, 0x34);
    lwc1(f0, sp, 0x38);
    swc1(f2, a0, 0);
    swc1(f1, a0, 4);
    swc1(f0, a0, 8);
    sw(v1, sp, 0x20);
    lwc1(f3, gp, kGpCardNegHalfH);  // 0x7CB00C
    swc1(f3, sp, 0x24);
    sw(zero, sp, 0x28);
    lwc1(f2, sp, 0x20);
    lwc1(f1, sp, 0x24);
    lwc1(f0, sp, 0x28);
    swc1(f2, a0, 36);
    swc1(f1, a0, 40);
    swc1(f0, a0, 44);
    v1 = lui(0xC040);
    sw(v1, sp, 0x10);
    swc1(f3, sp, 0x14);
    sw(zero, sp, 0x18);
    lwc1(f2, sp, 0x10);
    lwc1(f1, sp, 0x14);
    lwc1(f0, sp, 0x18);
    swc1(f2, a0, 72);
    swc1(f1, a0, 76);
    swc1(f0, a0, 80);
    sw(v1, sp, 0x0);
    swc1(f4, sp, 0x4);
    sw(zero, sp, 0x8);
    lwc1(f2, sp, 0x0);
    lwc1(f1, sp, 0x4);
    lwc1(f0, sp, 0x8);
    swc1(f2, a0, 108);
    swc1(f1, a0, 112);
    swc1(f0, a0, 116);
    v1 = 255;
    sb(v1, a0, 12);
    sb(v1, a0, 13);
    sb(v1, a0, 14);
    sb(v1, a0, 15);
    sb(v1, a0, 48);
    sb(v1, a0, 49);
    sb(v1, a0, 50);
    sb(v1, a0, 51);
    sb(v1, a0, 84);
    sb(v1, a0, 85);
    sb(v1, a0, 86);
    sb(v1, a0, 87);
    sb(v1, a0, 120);
    sb(v1, a0, 121);
    sb(v1, a0, 122);
    sb(v1, a0, 123);
    v1 = 0x3F7E0000;
    sw(v1, a0, 28);
    sw(v1, a0, 64);
    sw(zero, a0, 100);
    sw(zero, a0, 136);
    a1 = 0x3C000000;
    sw(a1, a0, 32);
    v1 = 0x3F230000;
    sw(v1, a0, 68);
    sw(v1, a0, 104);
    sw(a1, a0, 140);
    sp = addiu(sp, 0x40);
}

// 0x0020CCC0 sub_20CCC0 -- 136 bytes; leaf frame (no stack)
// [gcModel_SetQuadColour](quad, rgba*) gc_model.c: copies the 4 RGBA bytes into each of the 4 vertices (+12, +48,
// +84, +120).
void sub_20CCC0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0020ccc0
    enter(ctx, 34);  // entry check point + this block's cycles
    lbu(v1, a1, 0);
    sb(v1, a0, 12);
    lbu(v1, a1, 1);
    sb(v1, a0, 13);
    lbu(v1, a1, 2);
    sb(v1, a0, 14);
    lbu(v1, a1, 3);
    sb(v1, a0, 15);
    lbu(v1, a1, 0);
    sb(v1, a0, 48);
    lbu(v1, a1, 1);
    sb(v1, a0, 49);
    lbu(v1, a1, 2);
    sb(v1, a0, 50);
    lbu(v1, a1, 3);
    sb(v1, a0, 51);
    lbu(v1, a1, 0);
    sb(v1, a0, 84);
    lbu(v1, a1, 1);
    sb(v1, a0, 85);
    lbu(v1, a1, 2);
    sb(v1, a0, 86);
    lbu(v1, a1, 3);
    sb(v1, a0, 87);
    lbu(v1, a1, 0);
    sb(v1, a0, 120);
    lbu(v1, a1, 1);
    sb(v1, a0, 121);
    lbu(v1, a1, 2);
    sb(v1, a0, 122);
    lbu(v1, a1, 3);
    sb(v1, a0, 123);
}

// 0x0020CDA0 sub_20CDA0 -- 384 bytes; frame 0x20: ra sp+0x0
// [gcModel_BuildGrid](grid) gc_model.c: +0 = 0, +2464 / +2468 = 0.5f / 0.375f; then 9 rows of 36-byte vertices from
// +4: even rows 8 vertices at x = 0, 0.5, 1.5 .. 5.5, 6 (minus 3), odd rows 7 at x = 0..6 (minus 3); y = row * 0.96
// (0x7CB028) - 3.84 (0x7CB008), z 0. Asserts 68 vertices were written (line 1425).
void sub_20CDA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9};
    // 0x0020cda0
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    sw(zero, a0, 0);
    a1 = 0x3F000000;
    sw(a1, a0, 2464);
    v1 = 0x3EC00000;
    sw(v1, a0, 2468);
    t4 = addiu(a0, 4);
    t2 = 0;
    a2 = 7;
    t0 = 8;
    lwc1(f8, gp, kGpCardRowStep);  // 0x7CB028
    lwc1(f7, gp, kGpCardHalfH);  // 0x7CB008
    mtc1(a1, f4);
    v1 = 0x40C00000;
    mtc1(v1, f5);
    mtc1(zero, f6);
    v1 = 0x40400000;
    mtc1(v1, f3);
    for (;;) {
        // 0x0020ced0
        charge(ctx, 3);
        v1 = slti(t2, 9);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0020cdf4
        charge(ctx, 4);
        v1 = nor(t2, 0);
        t1 = v1 & 0x1;
        if (t1 == 0) {
            // 0x0020ce10
            charge(ctx, 1);
            a3 = a2;
        } else {
            // 0x0020ce04
            charge(ctx, 3);
            a3 = t0;
        }
        // 0x0020ce14
        charge(ctx, 9);
        t3 = 0;
        mtc1(t2, f0);
        cvt_s_w(f0, f0);
        mul_s(f0, f8, f0);
        sub_s(f9, f0, f7);
        a1 = addiu(a3, -1);
        for (;;) {
            // 0x0020cec0
            charge(ctx, 3);
            v1 = slt(t3, a3);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0020ce38
            charge(ctx, 2);
            if (t1 == 0) {
                // 0x0020ce84
                charge(ctx, 3);
                mtc1(t3, f0);
                cvt_s_w(f0, f0);
            } else {
                // 0x0020ce40
                charge(ctx, 2);
                if (t3 != 0) {
                    // 0x0020ce54
                    charge(ctx, 2);
                    if (t3 != a1) {
                        // 0x0020ce68
                        charge(ctx, 7);
                        v1 = addiu(t3, -1);
                        mtc1(v1, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f4, f0);
                    } else {
                        // 0x0020ce5c
                        charge(ctx, 3);
                        mov_s(f0, f5);
                    }
                } else {
                    // 0x0020ce48
                    charge(ctx, 3);
                    mov_s(f0, f6);
                }
            }
            // 0x0020ce90
            charge(ctx, 12);
            sub_s(f0, f0, f3);
            swc1(f0, sp, 0x10);
            swc1(f9, sp, 0x14);
            sw(zero, sp, 0x18);
            lwc1(f2, sp, 0x10);
            lwc1(f1, sp, 0x14);
            lwc1(f0, sp, 0x18);
            swc1(f2, t4, 0);
            swc1(f1, t4, 4);
            swc1(f0, t4, 8);
            t3 = addiu(t3, 1);
            t4 = addiu(t4, 36);
        }
        // 0x0020cecc
        charge(ctx, 1);
        t2 = addiu(t2, 1);
    }
    // 0x0020cedc
    charge(ctx, 8);
    v1 = addiu(a0, 4);
    a0 = subu(t4, v1);
    v1 = 36;
    div(a0, v1);
    mflo(a0);
    v1 = 68;
    if (a0 != v1) {
        // 0x0020cefc
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -8032);  // "gc_model.c"
        a1 = 1425;
        jal(ctx, 0x20CF08u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0020cf10 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0020D7D0 sub_20D7D0 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [sflRes_Register](work) sfl_res.c: asserts the slot is empty (line 108), work +0 = +4 = 0, slot = work.
void sub_20D7D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0020d7d0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, gp, kGpSflRes);  // 0x7CE2F0
    if (v1 != 0) {
        // 0x0020d7ec
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 108;
        jal(ctx, 0x20D7F8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0020d800 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    sw(zero, s0, 0);
    sw(zero, s0, 4);
    sw(s0, gp, kGpSflRes);  // 0x7CE2F0
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0020DFE0 sub_20DFE0 -- 68 bytes; frame 0x10: ra sp+0x0
// [sflRes_IsBusy] sfl_res.c: asserts the work (line 101), $v0 = flags & 1.
void sub_20DFE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0020dfe0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpSflRes);  // 0x7CE2F0
    if (v0 == 0) {
        // 0x0020dff4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 101;
        jal(ctx, 0x20E000u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0020e008 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpSflRes);  // 0x7CE2F0
    lw(v0, v0, kWkFlags);
    v0 = v0 & 0x1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0020E4C0 sub_20E4C0 -- 68 bytes; frame 0x10: ra sp+0x0
// [sflRes_Flag4] sfl_res.c: asserts the work (line 101), $v0 = flags & 4.
void sub_20E4C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0020e4c0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpSflRes);  // 0x7CE2F0
    if (v0 == 0) {
        // 0x0020e4d4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 101;
        jal(ctx, 0x20E4E0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0020e4e8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpSflRes);  // 0x7CE2F0
    lw(v0, v0, kWkFlags);
    v0 = v0 & 0x4;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0020E510 sub_20E510 -- 128 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [sflRes_GetGround](i) sfl_res.c: asserts the work and the ground files loaded (bit 1, line 439); $v0 = +20[i].
void sub_20E510(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0020e510
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, kGpSflRes);  // 0x7CE2F0
    if (v0 == 0) {
        // 0x0020e530
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 101;
        jal(ctx, 0x20E53Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0020e544
    charge(ctx, 5);
    lw(s0, gp, kGpSflRes);  // 0x7CE2F0
    lw(v0, s0, kWkLoaded);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // 0x0020e558
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 439;
        jal(ctx, 0x20E564u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0020e56c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = sll(s1, 2);
    v0 = addu(v0, s0);
    lw(v0, v0, kSrGround);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0020E590 sub_20E590 -- 128 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [sflRes_GetBase](i) sfl_res.c: asserts the work and the base files loaded (bit 0, line 446); $v0 = +8[i].
void sub_20E590(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0020e590
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, kGpSflRes);  // 0x7CE2F0
    if (v0 == 0) {
        // 0x0020e5b0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 101;
        jal(ctx, 0x20E5BCu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0020e5c4
    charge(ctx, 5);
    lw(s0, gp, kGpSflRes);  // 0x7CE2F0
    lw(v0, s0, kWkLoaded);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x0020e5d8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 446;
        jal(ctx, 0x20E5E4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0020e5ec (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = sll(s1, 2);
    v0 = addu(v0, s0);
    lw(v0, v0, kSrBase);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0020E690 sub_20E690 -- 128 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [sflRes_GetEffect](i) sfl_res.c: asserts the work and the effect files loaded (bit 2, line 460); $v0 = +64[i].
void sub_20E690(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0020e690
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, kGpSflRes);  // 0x7CE2F0
    if (v0 == 0) {
        // 0x0020e6b0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 101;
        jal(ctx, 0x20E6BCu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0020e6c4
    charge(ctx, 5);
    lw(s0, gp, kGpSflRes);  // 0x7CE2F0
    lw(v0, s0, kWkLoaded);
    v0 = v0 & 0x4;
    if (v0 == 0) {
        // 0x0020e6d8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 460;
        jal(ctx, 0x20E6E4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0020e6ec (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = sll(s1, 2);
    v0 = addu(v0, s0);
    lw(v0, v0, kSrEffect);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0020EC00 sub_20EC00 -- 68 bytes; frame 0x10: ra sp+0x0
// [sflRes_Flag10] sfl_res.c: asserts the work (line 101), $v0 = flags & 0x10.
void sub_20EC00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0020ec00
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpSflRes);  // 0x7CE2F0
    if (v0 == 0) {
        // 0x0020ec14
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7912);  // "sfl_res.c"
        a1 = 101;
        jal(ctx, 0x20EC20u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0020ec28 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpSflRes);  // 0x7CE2F0
    lw(v0, v0, kWkFlags);
    v0 = v0 & 0x10;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0020F720 sub_20F720 -- 168 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [bppMain_FindMember](u16 id) bpp_main.c: asserts the work (line 67); the first of the +23120 member records (5,776
// bytes from +16) whose u16 +4 equals id -> $v0 = the record; none: K_Assert (line 412), $v0 = 0.
void sub_20F720(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0020f720
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, gp, kGpBppMain);  // 0x7CE2F4
    if (v0 == 0) {
        // 0x0020f73c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7672);  // "bpp_main.c"
        a1 = 67;
        jal(ctx, 0x20F748u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0020f750
    charge(ctx, 7);
    lw(a3, gp, kGpBppMain);  // 0x7CE2F4
    t0 = 0;
    a2 = s0 & 0xFFFF;
    lw(a1, a3, kBppCount);
    a0 = 5776;
    for (;;) {
        // 0x0020f790
        charge(ctx, 3);
        v0 = slt(t0, a1);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0020f76c
        charge(ctx, 6);
        mult(v0, t0, a0);
        v1 = addu(a3, v0);
        v0 = addiu(v1, 16);
        lhu(v1, v1, kBppRecords + kBppRecId);
        if (v1 == a2) {
            goto L_0020f784_4;
        }
        // 0x0020f78c
        charge(ctx, 1);
        t0 = addiu(t0, 1);
    }
    // 0x0020f79c
    charge(ctx, 6);
    a0 = 0x690000;
    a0 = addiu(a0, -7672);  // "bpp_main.c"
    a1 = 412;
    jal(ctx, 0x20F7A8u, gen::fn_sub_19D3F0_0019d3f0);
    v0 = 0;
    // 0x0020f7b4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
    return;
L_0020f784_4:
    charge(ctx, 2);
    // 0x0020f7b4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0020FC40 sub_20FC40 -- 72 bytes; frame 0x10: ra sp+0x0
// [bppMain_SetFlag10] bpp_main.c: asserts the work (line 67), flags |= 0x10.
void sub_20FC40(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0020fc40
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBppMain);  // 0x7CE2F4
    if (v1 == 0) {
        // 0x0020fc54
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7672);  // "bpp_main.c"
        a1 = 67;
        jal(ctx, 0x20FC60u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0020fc68 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lw(a0, gp, kGpBppMain);  // 0x7CE2F4
    lw(v1, a0, kWkFlags);
    v1 = v1 | 0x10;
    sw(v1, a0, kWkFlags);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0020FC90 sub_20FC90 -- 76 bytes; frame 0x10: ra sp+0x0
// [bppMain_ClearFlag10] bpp_main.c: asserts the work (line 67), flags &= ~0x10.
void sub_20FC90(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0020fc90
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBppMain);  // 0x7CE2F4
    if (v1 == 0) {
        // 0x0020fca4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7672);  // "bpp_main.c"
        a1 = 67;
        jal(ctx, 0x20FCB0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0020fcb8 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(a1, gp, kGpBppMain);  // 0x7CE2F4
    lw(a0, a1, kWkFlags);
    v1 = si(-17);
    v1 = a0 & v1;
    sw(v1, a1, kWkFlags);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0020FD80 sub_20FD80 -- 72 bytes; frame 0x10: ra sp+0x0
// [bppMain_SetFlag40] bpp_main.c: asserts the work (line 67), flags |= 0x40.
void sub_20FD80(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0020fd80
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBppMain);  // 0x7CE2F4
    if (v1 == 0) {
        // 0x0020fd94
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7672);  // "bpp_main.c"
        a1 = 67;
        jal(ctx, 0x20FDA0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0020fda8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lw(a0, gp, kGpBppMain);  // 0x7CE2F4
    lw(v1, a0, kWkFlags);
    v1 = v1 | 0x40;
    sw(v1, a0, kWkFlags);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00215A50 sub_215A50 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [sflPsel_Register](work) sfl_psel.c: asserts the slot is empty (line 209), work +0 = +4 = 0, slot = work.
void sub_215A50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00215a50
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, gp, kGpSflPsel);  // 0x7CE2F8
    if (v1 != 0) {
        // 0x00215a6c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7640);  // "sfl_psel.c"
        a1 = 209;
        jal(ctx, 0x215A78u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00215a80 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    sw(zero, s0, 0);
    sw(zero, s0, 4);
    sw(s0, gp, kGpSflPsel);  // 0x7CE2F8
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00219C90 sub_219C90 -- 252 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [gcRes_Register](work) gc_res.c: asserts the slot is empty (line 149); clears the header words +0..+24, +68, +72,
// the flags of the 32 slots (+652, 292 bytes), of the 16 pairs (+76, 20 bytes) and of the 16 ids (+396, 16 bytes);
// slot = work.
void sub_219C90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00219c90
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, gp, kGpGcRes);  // 0x7CE2FC
    if (v1 != 0) {
        // 0x00219cac
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 149;
        jal(ctx, 0x219CB8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00219cc0
    charge(ctx, 12);
    sw(zero, s0, 0);
    sw(zero, s0, 20);
    sw(zero, s0, 24);
    sw(zero, s0, 12);
    sw(zero, s0, 16);
    sw(zero, s0, 4);
    sw(zero, s0, 8);
    sw(zero, s0, 68);
    sw(zero, s0, 72);
    a0 = 0;
    for (;;) {
        // 0x00219d10
        charge(ctx, 3);
        v1 = slti(a0, 32);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00219cf0
        charge(ctx, 8);
        v1 = sll(a0, 3);
        v1 = addu(v1, a0);
        v1 = sll(v1, 3);
        v1 = addu(v1, a0);
        v1 = sll(v1, 2);
        v1 = addu(s0, v1);
        sw(zero, v1, 652);
        a0 = addiu(a0, 1);
    }
    // 0x00219d1c
    charge(ctx, 3);
    a0 = 0;
    for (;;) {
        // 0x00219d40
        charge(ctx, 3);
        v1 = slti(a0, 16);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00219d28
        charge(ctx, 6);
        v1 = sll(a0, 2);
        v1 = addu(v1, a0);
        v1 = sll(v1, 2);
        v1 = addu(s0, v1);
        sw(zero, v1, 76);
        a0 = addiu(a0, 1);
    }
    // 0x00219d4c
    charge(ctx, 3);
    a0 = 0;
    for (;;) {
        // 0x00219d68
        charge(ctx, 3);
        v1 = slti(a0, 16);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00219d58
        charge(ctx, 4);
        v1 = sll(a0, 4);
        v1 = addu(s0, v1);
        sw(zero, v1, 396);
        a0 = addiu(a0, 1);
    }
    // 0x00219d74
    charge(ctx, 6);
    sw(s0, gp, kGpGcRes);  // 0x7CE2FC
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0021A3A0 sub_21A3A0 -- 108 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [gcRes_GetResA] gc_res.c: asserts the work (line 124) and +12 bit 0 (line 323); $v0 = +4.
void sub_21A3A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021a3a0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpGcRes);  // 0x7CE2FC
    if (v0 == 0) {
        // 0x0021a3b8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 124;
        jal(ctx, 0x21A3C4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021a3cc
    charge(ctx, 5);
    lw(s0, gp, kGpGcRes);  // 0x7CE2FC
    lw(v0, s0, kGrLoaded);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x0021a3e0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 323;
        jal(ctx, 0x21A3ECu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021a3f4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    lw(v0, s0, kGrResA);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0021A410 sub_21A410 -- 108 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [gcRes_GetResB] gc_res.c: asserts the work (line 124) and +12 bit 1 (line 331); $v0 = +8.
void sub_21A410(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021a410
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpGcRes);  // 0x7CE2FC
    if (v0 == 0) {
        // 0x0021a428
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 124;
        jal(ctx, 0x21A434u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021a43c
    charge(ctx, 5);
    lw(s0, gp, kGpGcRes);  // 0x7CE2FC
    lw(v0, s0, kGrLoaded);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // 0x0021a450
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 331;
        jal(ctx, 0x21A45Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021a464 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    lw(v0, s0, kGrResB);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0021A480 sub_21A480 -- 260 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [gcRes_GetPairValue](a, b) gc_res.c: the pair entry with keys (a, b) (no live-flag test), asserts one was found
// (line 346) and that it is loaded (flags bit 1, line 347); $v0 = its value (+88). Not found: index 16 is read.
void sub_21A480(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021a480
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    lw(v0, gp, kGpGcRes);  // 0x7CE2FC
    if (v0 == 0) {
        // 0x0021a4ac
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 124;
        jal(ctx, 0x21A4B8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021a4c0
    charge(ctx, 4);
    lw(s0, gp, kGpGcRes);  // 0x7CE2FC
    s1 = 0;
    for (;;) {
        // 0x0021a4fc
        charge(ctx, 3);
        v0 = slti(s1, 16);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0021a4d0
        charge(ctx, 7);
        v0 = sll(s1, 2);
        v0 = addu(v0, s1);
        v0 = sll(v0, 2);
        v1 = addu(s0, v0);
        lw(v0, v1, kPrKeyA);
        if (v0 == s3) {
            // 0x0021a4ec
            charge(ctx, 3);
            lw(v0, v1, kPrKeyB);
            if (v0 == s2) {
                break;
            }
            goto L_0021a4f8;
        }
    L_0021a4f8:
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x0021a508
    charge(ctx, 3);
    v0 = slti(s1, 16);
    if (v0 == 0) {
        // 0x0021a514
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 346;
        jal(ctx, 0x21A520u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021a528
    charge(ctx, 8);
    v0 = sll(s1, 2);
    v0 = addu(v0, s1);
    s1 = sll(v0, 2);
    v0 = addu(s1, s0);
    lw(v0, v0, kPrFlags);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // 0x0021a548
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 347;
        jal(ctx, 0x21A554u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021a55c (the shared epilogue, written out on this path)
    charge(ctx, 10);
    v0 = addu(s1, s0);
    lw(v0, v0, kPrValue);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0021A590 sub_21A590 -- 224 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [gcRes_GetIdValue](u16 id) gc_res.c: the id entry with that id (no live-flag test), asserts found (line 362) and
// loaded (bit 1, line 364); $v0 = its value (+404).
void sub_21A590(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021a590
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(v0, gp, kGpGcRes);  // 0x7CE2FC
    if (v0 == 0) {
        // 0x0021a5b4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 124;
        jal(ctx, 0x21A5C0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021a5c8
    charge(ctx, 5);
    lw(s0, gp, kGpGcRes);  // 0x7CE2FC
    s1 = 0;
    v1 = s2 & 0xFFFF;
    for (;;) {
        // 0x0021a5f4
        charge(ctx, 3);
        v0 = slti(s1, 16);
        if (v0 != 0) {
            backedge(ctx);
            // 0x0021a5dc
            charge(ctx, 5);
            v0 = sll(s1, 4);
            v0 = addu(s0, v0);
            lhu(v0, v0, kGiId);
            if (v0 != v1) {
                // 0x0021a5f0
                charge(ctx, 1);
                s1 = addiu(s1, 1);
                continue;
            }
        }
        break;
    }
    // 0x0021a600
    charge(ctx, 3);
    v0 = slti(s1, 16);
    if (v0 == 0) {
        // 0x0021a60c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 362;
        jal(ctx, 0x21A618u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021a620
    charge(ctx, 6);
    s1 = sll(s1, 4);
    v0 = addu(s1, s0);
    lw(v0, v0, kGiFlags);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // 0x0021a638
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 364;
        jal(ctx, 0x21A644u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021a64c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = addu(s1, s0);
    lw(v0, v0, kGiValue);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0021AC90 sub_21AC90 -- 176 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [gcRes_HasPair](a, b) gc_res.c: $v0 = 1 when a live (bit 0) pair entry has keys (a, b).
void sub_21AC90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021ac90
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v0, gp, kGpGcRes);  // 0x7CE2FC
    if (v0 == 0) {
        // 0x0021acb4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 124;
        jal(ctx, 0x21ACC0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021acc8
    charge(ctx, 4);
    lw(a0, gp, kGpGcRes);  // 0x7CE2FC
    a1 = 0;
    for (;;) {
        // 0x0021ad18
        charge(ctx, 3);
        v0 = slti(a1, 16);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0021acd8
        charge(ctx, 9);
        v0 = sll(a1, 2);
        v0 = addu(v0, a1);
        v0 = sll(v0, 2);
        v1 = addu(a0, v0);
        lw(v0, v1, kPrFlags);
        v0 = nor(v0, 0);
        v0 = v0 & 0x1;
        if (v0 == 0) {
            // 0x0021acfc
            charge(ctx, 3);
            lw(v0, v1, kPrKeyB);
            if (v0 == s0) {
                // 0x0021ad08
                charge(ctx, 3);
                lw(v0, v1, kPrKeyA);
                if (v0 == s1) {
                    break;
                }
            }
        }
        charge(ctx, 1);
        a1 = addiu(a1, 1);
    }
    // 0x0021ad24 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = slti(a1, 16);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0021AE30 sub_21AE30 -- 248 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [gcRes_RefPair](a, b) gc_res.c: the live pair entry (a, b), asserted found (line 610); its refs (+92) += 1.
void sub_21AE30(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021ae30
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    lw(v1, gp, kGpGcRes);  // 0x7CE2FC
    if (v1 == 0) {
        // 0x0021ae5c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 124;
        jal(ctx, 0x21AE68u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021ae70
    charge(ctx, 4);
    lw(s0, gp, kGpGcRes);  // 0x7CE2FC
    s1 = 0;
    for (;;) {
        // 0x0021aec0
        charge(ctx, 3);
        v1 = slti(s1, 16);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0021ae80
        charge(ctx, 9);
        v1 = sll(s1, 2);
        v1 = addu(v1, s1);
        v1 = sll(v1, 2);
        a0 = addu(s0, v1);
        lw(v1, a0, kPrFlags);
        v1 = nor(v1, 0);
        v1 = v1 & 0x1;
        if (v1 == 0) {
            // 0x0021aea4
            charge(ctx, 3);
            lw(v1, a0, kPrKeyB);
            if (v1 == s2) {
                // 0x0021aeb0
                charge(ctx, 3);
                lw(v1, a0, kPrKeyA);
                if (v1 == s3) {
                    break;
                }
            }
        }
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x0021aecc
    charge(ctx, 3);
    v1 = slti(s1, 16);
    if (v1 == 0) {
        // 0x0021aed8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 610;
        jal(ctx, 0x21AEE4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021aeec (the shared epilogue, written out on this path)
    charge(ctx, 15);
    v1 = sll(s1, 2);
    v1 = addu(v1, s1);
    v1 = sll(v1, 2);
    a0 = addu(s0, v1);
    lw(v1, a0, kPrRefs);
    v1 = addiu(v1, 1);
    sw(v1, a0, kPrRefs);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0021AF30 sub_21AF30 -- 168 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [gcRes_FreePairSlot] gc_res.c: $v0 = the index of the first pair entry without bit 0; 16 when full (line 634).
void sub_21AF30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021af30
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpGcRes);  // 0x7CE2FC
    if (v0 == 0) {
        // 0x0021af48
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 124;
        jal(ctx, 0x21AF54u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021af5c
    charge(ctx, 4);
    lw(v1, gp, kGpGcRes);  // 0x7CE2FC
    s0 = 0;
    for (;;) {
        // 0x0021af94
        charge(ctx, 3);
        v0 = slti(s0, 16);
        if (v0 != 0) {
            backedge(ctx);
            // 0x0021af6c
            charge(ctx, 9);
            v0 = sll(s0, 2);
            v0 = addu(v0, s0);
            v0 = sll(v0, 2);
            v0 = addu(v1, v0);
            lw(v0, v0, kPrFlags);
            v0 = nor(v0, 0);
            v0 = v0 & 0x1;
            if (v0 == 0) {
                // 0x0021af90
                charge(ctx, 1);
                s0 = addiu(s0, 1);
                continue;
            }
        }
        break;
    }
    // 0x0021afa0
    charge(ctx, 3);
    v0 = slti(s0, 16);
    if (v0 == 0) {
        // 0x0021afac
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 634;
        jal(ctx, 0x21AFB8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021afc0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0021AFE0 sub_21AFE0 -- 148 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [gcRes_HasId](u16 id) gc_res.c: $v0 = 1 when a live (bit 0) id entry has that id.
void sub_21AFE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021afe0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, gp, kGpGcRes);  // 0x7CE2FC
    if (v0 == 0) {
        // 0x0021affc
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 124;
        jal(ctx, 0x21B008u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021b010
    charge(ctx, 5);
    lw(a1, gp, kGpGcRes);  // 0x7CE2FC
    a2 = 0;
    a0 = s0 & 0xFFFF;
    for (;;) {
        // 0x0021b050
        charge(ctx, 3);
        v0 = slti(a2, 16);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0021b024
        charge(ctx, 7);
        v0 = sll(a2, 4);
        v1 = addu(a1, v0);
        lw(v0, v1, kGiFlags);
        v0 = nor(v0, 0);
        v0 = v0 & 0x1;
        if (v0 == 0) {
            // 0x0021b040
            charge(ctx, 3);
            lhu(v0, v1, kGiId);
            if (v0 == a0) {
                break;
            }
            goto L_0021b04c;
        }
    L_0021b04c:
        charge(ctx, 1);
        a2 = addiu(a2, 1);
    }
    // 0x0021b05c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = slti(a2, 16);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0021B150 sub_21B150 -- 160 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [gcRes_FreeIdSlot] gc_res.c: $v0 = the index of the first id entry without bit 0; 16 when full (line 687).
void sub_21B150(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021b150
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpGcRes);  // 0x7CE2FC
    if (v0 == 0) {
        // 0x0021b168
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 124;
        jal(ctx, 0x21B174u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021b17c
    charge(ctx, 4);
    lw(v1, gp, kGpGcRes);  // 0x7CE2FC
    s0 = 0;
    for (;;) {
        // 0x0021b1ac
        charge(ctx, 3);
        v0 = slti(s0, 16);
        if (v0 != 0) {
            backedge(ctx);
            // 0x0021b18c
            charge(ctx, 7);
            v0 = sll(s0, 4);
            v0 = addu(v1, v0);
            lw(v0, v0, kGiFlags);
            v0 = nor(v0, 0);
            v0 = v0 & 0x1;
            if (v0 == 0) {
                // 0x0021b1a8
                charge(ctx, 1);
                s0 = addiu(s0, 1);
                continue;
            }
        }
        break;
    }
    // 0x0021b1b8
    charge(ctx, 3);
    v0 = slti(s0, 16);
    if (v0 == 0) {
        // 0x0021b1c4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 687;
        jal(ctx, 0x21B1D0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021b1d8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0021B1F0 sub_21B1F0 -- 212 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [gcRes_RefId](u16 id) gc_res.c: the live id entry, asserted found (line 671); its refs (+408) += 1.
void sub_21B1F0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021b1f0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(v1, gp, kGpGcRes);  // 0x7CE2FC
    if (v1 == 0) {
        // 0x0021b214
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 124;
        jal(ctx, 0x21B220u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021b228
    charge(ctx, 5);
    lw(s0, gp, kGpGcRes);  // 0x7CE2FC
    s1 = 0;
    a1 = s2 & 0xFFFF;
    for (;;) {
        // 0x0021b268
        charge(ctx, 3);
        v1 = slti(s1, 16);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0021b23c
        charge(ctx, 7);
        v1 = sll(s1, 4);
        a0 = addu(s0, v1);
        lw(v1, a0, kGiFlags);
        v1 = nor(v1, 0);
        v1 = v1 & 0x1;
        if (v1 == 0) {
            // 0x0021b258
            charge(ctx, 3);
            lhu(v1, a0, kGiId);
            if (v1 == a1) {
                break;
            }
            goto L_0021b264;
        }
    L_0021b264:
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x0021b274
    charge(ctx, 3);
    v1 = slti(s1, 16);
    if (v1 == 0) {
        // 0x0021b280
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 671;
        jal(ctx, 0x21B28Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021b294 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    v1 = sll(s1, 4);
    a0 = addu(s0, v1);
    lw(v1, a0, kGiRefs);
    v1 = addiu(v1, 1);
    sw(v1, a0, kGiRefs);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0021B2D0 sub_21B2D0 -- 208 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [gcRes_FreeSlot] gc_res.c: $v0 = the first 292-byte slot (+652) without bit 0; asserts one (line 720).
void sub_21B2D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021b2d0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpGcRes);  // 0x7CE2FC
    if (v0 == 0) {
        // 0x0021b2ec
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 124;
        jal(ctx, 0x21B2F8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021b300
    charge(ctx, 4);
    lw(s0, gp, kGpGcRes);  // 0x7CE2FC
    s1 = 0;
    for (;;) {
        // 0x0021b340
        charge(ctx, 3);
        v0 = slti(s1, 32);
        if (v0 != 0) {
            backedge(ctx);
            // 0x0021b310
            charge(ctx, 11);
            v0 = sll(s1, 3);
            v0 = addu(v0, s1);
            v0 = sll(v0, 3);
            v0 = addu(v0, s1);
            v0 = sll(v0, 2);
            v0 = addu(s0, v0);
            lw(v0, v0, kGrSlots);
            v0 = nor(v0, 0);
            v0 = v0 & 0x1;
            if (v0 == 0) {
                // 0x0021b33c
                charge(ctx, 1);
                s1 = addiu(s1, 1);
                continue;
            }
        }
        break;
    }
    // 0x0021b34c
    charge(ctx, 3);
    v0 = slti(s1, 32);
    if (v0 == 0) {
        // 0x0021b358
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 720;
        jal(ctx, 0x21B364u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021b36c (the shared epilogue, written out on this path)
    charge(ctx, 13);
    v0 = sll(s1, 3);
    v0 = addu(v0, s1);
    v0 = sll(v0, 3);
    v0 = addu(v0, s1);
    v0 = sll(v0, 2);
    v0 = addu(s0, v0);
    v0 = addiu(v0, 652);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0021B3A0 sub_21B3A0 -- 128 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [gcRes_GetTableC](i) gc_res.c: asserts the work and +12 bit 2 (line 747); $v0 = +32[i].
void sub_21B3A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021b3a0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, kGpGcRes);  // 0x7CE2FC
    if (v0 == 0) {
        // 0x0021b3c0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 124;
        jal(ctx, 0x21B3CCu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021b3d4
    charge(ctx, 5);
    lw(s0, gp, kGpGcRes);  // 0x7CE2FC
    lw(v0, s0, kGrLoaded);
    v0 = v0 & 0x4;
    if (v0 == 0) {
        // 0x0021b3e8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 747;
        jal(ctx, 0x21B3F4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021b3fc (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = sll(s1, 2);
    v0 = addu(v0, s0);
    lw(v0, v0, kGrTableC);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0021B420 sub_21B420 -- 128 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [gcRes_GetTableD](i) gc_res.c: asserts the work and +12 bit 3 (line 755); $v0 = +60[i].
void sub_21B420(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021b420
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, kGpGcRes);  // 0x7CE2FC
    if (v0 == 0) {
        // 0x0021b440
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 124;
        jal(ctx, 0x21B44Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021b454
    charge(ctx, 5);
    lw(s0, gp, kGpGcRes);  // 0x7CE2FC
    lw(v0, s0, kGrLoaded);
    v0 = v0 & 0x8;
    if (v0 == 0) {
        // 0x0021b468
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7624);  // "gc_res.c"
        a1 = 755;
        jal(ctx, 0x21B474u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021b47c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = sll(s1, 2);
    v0 = addu(v0, s0);
    lw(v0, v0, kGrTableD);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0021B670 sub_21B670 -- 120 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bseMain_Start](v) bse_main.c: asserts the work (line 30); +4 = v; sub_1FE510(v) (the panel's 0x200 mode with
// +12, battle_panel.h); flags |= 1 then &= ~2.
void sub_21B670(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021b670
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, kGpBseMain);  // 0x7CE300
    if (v0 == 0) {
        // 0x0021b690
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7472);  // "bse_main.c"
        a1 = 30;
        jal(ctx, 0x21B69Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021b6a4
    charge(ctx, 17);
    lw(s0, gp, kGpBseMain);  // 0x7CE300
    sw(s1, s0, kBseArg);
    a0 = s1;
    jal(ctx, 0x21B6B0u, gen::fn_sub_1FE510_001fe510);
    lw(v1, s0, kWkFlags);
    a0 = v1 | 0x1;
    sw(a0, s0, kWkFlags);
    v1 = si(-3);
    v1 = a0 & v1;
    sw(v1, s0, kWkFlags);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0021BAB0 sub_21BAB0 -- 68 bytes; frame 0x10: ra sp+0x0
// [bpRes_IsLoaded] bp_res.c: asserts the work (line 89), $v0 = flags & 1.
void sub_21BAB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021bab0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBpRes);  // 0x7CE304
    if (v0 == 0) {
        // 0x0021bac4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7456);  // "bp_res.c"
        a1 = 89;
        jal(ctx, 0x21BAD0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021bad8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpBpRes);  // 0x7CE304
    lw(v0, v0, kBrFlags);
    v0 = v0 & 0x1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0021BB00 sub_21BB00 -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [bpRes_SetValue108](v) bp_res.c: asserts the work (line 89), +108 = v.
void sub_21BB00(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021bb00
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, gp, kGpBpRes);  // 0x7CE304
    if (v1 == 0) {
        // 0x0021bb1c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7456);  // "bp_res.c"
        a1 = 89;
        jal(ctx, 0x21BB28u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021bb30 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v1, gp, kGpBpRes);  // 0x7CE304
    sw(s0, v1, kBrValue108);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0021BB50 sub_21BB50 -- 12 bytes; leaf frame (no stack)
// Returns 0 ($v0 = 0; called by sub_1FEC30).
void sub_21BB50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0021bb50
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0021C3F0 sub_21C3F0 -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [bpRes_GetSet](i) bp_res.c: asserts the work (line 89); $v0 = the panel sprite set i (+16[i]). The drawers' most
// called leaf (91 callers).
void sub_21C3F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021c3f0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, gp, kGpBpRes);  // 0x7CE304
    if (v0 == 0) {
        // 0x0021c40c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7456);  // "bp_res.c"
        a1 = 89;
        jal(ctx, 0x21C418u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021c420 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(v1, gp, kGpBpRes);  // 0x7CE304
    v0 = sll(s0, 2);
    v0 = addu(v0, v1);
    lw(v0, v0, kBrSets);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0021C450 sub_21C450 -- 252 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bpRes_GetSetById](u16 id) bp_res.c: id 1 -> the set +36 (loaded bit 0 asserted, line 403); any other id: its
// index among the +68 ids of +72 (asserted found, line 414) -> +56[index].
void sub_21C450(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021c450
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, kGpBpRes);  // 0x7CE304
    if (v0 == 0) {
        // 0x0021c470
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7456);  // "bp_res.c"
        a1 = 89;
        jal(ctx, 0x21C47Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021c484
    charge(ctx, 5);
    lw(s0, gp, kGpBpRes);  // 0x7CE304
    a0 = s1 & 0xFFFF;
    v0 = 1;
    if (a0 == v0) {
        // 0x0021c4a0
        charge(ctx, 4);
        lw(v0, s0, kBrLoaded);
        v0 = v0 & 0x1;
        if (v0 == 0) {
            // 0x0021c4b0
            charge(ctx, 5);
            a0 = 0x690000;
            a0 = addiu(a0, -7456);  // "bp_res.c"
            a1 = 403;
            jal(ctx, 0x21C4BCu, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x0021c4c4
        charge(ctx, 3);
        lw(v0, s0, kBrSetOne);
    } else {
        // 0x0021c498
        charge(ctx, 2);
        // 0x0021c4d0
        charge(ctx, 4);
        s1 = 0;
        lw(v1, s0, kBrIdCount);
        for (;;) {
            // 0x0021c4f8
            charge(ctx, 3);
            v0 = slt(s1, v1);
            if (v0 != 0) {
                backedge(ctx);
                // 0x0021c4e0
                charge(ctx, 5);
                v0 = sll(s1, 2);
                v0 = addu(s0, v0);
                lw(v0, v0, kBrIds);
                if (v0 != a0) {
                    // 0x0021c4f4
                    charge(ctx, 1);
                    s1 = addiu(s1, 1);
                    continue;
                }
            }
            break;
        }
        // 0x0021c504
        charge(ctx, 4);
        lw(v0, s0, kBrIdCount);
        v0 = slt(s1, v0);
        if (v0 == 0) {
            // 0x0021c514
            charge(ctx, 5);
            a0 = 0x690000;
            a0 = addiu(a0, -7456);  // "bp_res.c"
            a1 = 414;
            jal(ctx, 0x21C520u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x0021c528
        charge(ctx, 3);
        v0 = sll(s1, 2);
        v0 = addu(v0, s0);
        lw(v0, v0, kBrIdSets);
    }
    // 0x0021c534 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0021C550 sub_21C550 -- 128 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bpRes_GetMore](i) bp_res.c: asserts the work and loaded bit 0 (line 425); $v0 = +96[i].
void sub_21C550(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021c550
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, kGpBpRes);  // 0x7CE304
    if (v0 == 0) {
        // 0x0021c570
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7456);  // "bp_res.c"
        a1 = 89;
        jal(ctx, 0x21C57Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021c584
    charge(ctx, 5);
    lw(s0, gp, kGpBpRes);  // 0x7CE304
    lw(v0, s0, kBrLoaded);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x0021c598
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7456);  // "bp_res.c"
        a1 = 425;
        jal(ctx, 0x21C5A4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021c5ac (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = sll(s1, 2);
    v0 = addu(v0, s0);
    lw(v0, v0, kBrMore);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0021C7E0 nullsub_11 -- 8 bytes; leaf frame (no stack)
// Empty (bpRoot_UpdateBattlePanelTask and sub_21BB60 call it).
void nullsub_11(EEContext& ctx) {
    using namespace hg;
    // 0x0021c7e0
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0021C860 sub_21C860 -- 68 bytes; frame 0x10: ra sp+0x0
// [bpRes_IsTutorialLoaded] bp_res.c: asserts the work (line 89), $v0 = flags & 4 (sub_21C7F0 sets it).
void sub_21C860(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021c860
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBpRes);  // 0x7CE304
    if (v0 == 0) {
        // 0x0021c874
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7456);  // "bp_res.c"
        a1 = 89;
        jal(ctx, 0x21C880u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021c888 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpBpRes);  // 0x7CE304
    lw(v0, v0, kBrFlags);
    v0 = v0 & 0x4;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0021C8B0 sub_21C8B0 -- 128 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bpRes_GetBlock](i) bp_res.c: asserts the work and loaded bit 8 (line 492); $v0 = +120[i].
void sub_21C8B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021c8b0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, kGpBpRes);  // 0x7CE304
    if (v0 == 0) {
        // 0x0021c8d0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7456);  // "bp_res.c"
        a1 = 89;
        jal(ctx, 0x21C8DCu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021c8e4
    charge(ctx, 5);
    lw(s0, gp, kGpBpRes);  // 0x7CE304
    lw(v0, s0, kBrLoaded);
    v0 = v0 & 0x100;
    if (v0 == 0) {
        // 0x0021c8f8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7456);  // "bp_res.c"
        a1 = 492;
        jal(ctx, 0x21C904u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021c90c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = sll(s1, 2);
    v0 = addu(v0, s0);
    lw(v0, v0, kBrBlocks);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0021C930 sub_21C930 -- 184 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bpRes_FreeBlocks] bp_res.c: asserts the work and loaded bit 8 (line 502); the three blocks +120[0..2] go to RwFree
// (the slot 0x96017C, a jalr), then loaded &= ~0x100.
void sub_21C930(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0021c930
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpBpRes);  // 0x7CE304
    if (v1 == 0) {
        // 0x0021c94c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7456);  // "bp_res.c"
        a1 = 89;
        jal(ctx, 0x21C958u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021c960
    charge(ctx, 5);
    lw(s0, gp, kGpBpRes);  // 0x7CE304
    lw(v1, s0, kBrLoaded);
    v1 = v1 & 0x100;
    if (v1 == 0) {
        // 0x0021c974
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7456);  // "bp_res.c"
        a1 = 502;
        jal(ctx, 0x21C980u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0021c988
    charge(ctx, 3);
    s1 = 0;
    for (;;) {
        // 0x0021c9b4
        charge(ctx, 3);
        v1 = slti(s1, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0021c994
        charge(ctx, 8);
        v0 = sll(s1, 2);
        v0 = addu(s0, v0);
        lw(a0, v0, kBrBlocks);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x21C9A8u, v0.u());
        s1 = addiu(s1, 1);
    }
    // 0x0021c9c0
    charge(ctx, 10);
    lw(a0, s0, kBrLoaded);
    v1 = si(-257);
    v1 = a0 & v1;
    sw(v1, s0, kBrLoaded);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002226F0 sub_2226F0 -- 192 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bcmPanel_MoveCursor1](cmd) bcm_panel.c: asserts the work (line 230); state = 1, prev = cur, cur = cmd, timer = 0;
// the two command quads (+4656 / +4912) take the pages cur / prev of panel set 0.
void sub_2226F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002226f0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308
    if (v0 == 0) {
        // 0x00222714
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x222720u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00222728
    charge(ctx, 34);
    lw(s1, gp, kGpBcmPanel);  // 0x7CE308
    a0 = 0;
    jal(ctx, 0x222730u, gen::fn_sub_21C3F0_0021c3f0);
    s2 = v0;
    v0 = 1;
    sw(v0, s1, kBcmState);
    lw(v0, s1, kBcmCur);
    sw(v0, s1, kBcmPrev);
    sw(s0, s1, kBcmCur);
    sw(zero, s1, kBcmTimer);
    a0 = s2;
    lw(a1, s1, kBcmCur);
    jal(ctx, 0x22275Cu, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s1, kBcmQuadCur);
    a1 = v0;
    jal(ctx, 0x22276Cu, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s2;
    lw(a1, s1, kBcmPrev);
    jal(ctx, 0x22277Cu, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s1, kBcmQuadPrev);
    a1 = v0;
    jal(ctx, 0x22278Cu, gen::fn_sub_21D3B0_0021d3b0);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002227B0 sub_2227B0 -- 192 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bcmPanel_MoveCursor2](cmd) bcm_panel.c: as sub_2226F0 with state 2.
void sub_2227B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002227b0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308
    if (v0 == 0) {
        // 0x002227d4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x2227E0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002227e8
    charge(ctx, 34);
    lw(s1, gp, kGpBcmPanel);  // 0x7CE308
    a0 = 0;
    jal(ctx, 0x2227F0u, gen::fn_sub_21C3F0_0021c3f0);
    s2 = v0;
    v0 = 2;
    sw(v0, s1, kBcmState);
    lw(v0, s1, kBcmCur);
    sw(v0, s1, kBcmPrev);
    sw(s0, s1, kBcmCur);
    sw(zero, s1, kBcmTimer);
    a0 = s2;
    lw(a1, s1, kBcmCur);
    jal(ctx, 0x22281Cu, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s1, kBcmQuadCur);
    a1 = v0;
    jal(ctx, 0x22282Cu, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s2;
    lw(a1, s1, kBcmPrev);
    jal(ctx, 0x22283Cu, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s1, kBcmQuadPrev);
    a1 = v0;
    jal(ctx, 0x22284Cu, gen::fn_sub_21D3B0_0021d3b0);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00222870 sub_222870 -- 180 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bcmPanel_ResetCursor] bcm_panel.c: as sub_2226F0 with state 8 and cur = 0.
void sub_222870(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00222870
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308
    if (v0 == 0) {
        // 0x0022288c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x222898u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002228a0
    charge(ctx, 33);
    lw(s0, gp, kGpBcmPanel);  // 0x7CE308
    a0 = 0;
    jal(ctx, 0x2228A8u, gen::fn_sub_21C3F0_0021c3f0);
    s1 = v0;
    v0 = 8;
    sw(v0, s0, kBcmState);
    lw(v0, s0, kBcmCur);
    sw(v0, s0, kBcmPrev);
    sw(zero, s0, kBcmCur);
    sw(zero, s0, kBcmTimer);
    a0 = s1;
    lw(a1, s0, kBcmCur);
    jal(ctx, 0x2228D4u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, kBcmQuadCur);
    a1 = v0;
    jal(ctx, 0x2228E4u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s1;
    lw(a1, s0, kBcmPrev);
    jal(ctx, 0x2228F4u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, kBcmQuadPrev);
    a1 = v0;
    jal(ctx, 0x222904u, gen::fn_sub_21D3B0_0021d3b0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00222B90 sub_222B90 -- 452 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bcmPanel_SetRows2] bcm_panel.c: asserts list bit 1 (line 1549); for each of the +24688 rows (1,296 bytes from
// +18016): its page 49 (row word 1) or 48 (word 0; other values keep the previous page), a 3-digit number
// (bpIfontDrawNumber) and page 43 of set 6; then the cursor quad (page +26868 + 32 of set 6) when +26872.
void sub_222B90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00222b90
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308
    if (v0 == 0) {
        // 0x00222bc0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x222BCCu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00222bd4
    charge(ctx, 14);
    lw(s1, gp, kGpBcmPanel);  // 0x7CE308
    a0 = 0;
    jal(ctx, 0x222BDCu, gen::fn_sub_21C3F0_0021c3f0);
    s5 = v0;
    s6 = addiu(s1, kBcmRows);
    a0 = 6;
    jal(ctx, 0x222BF0u, gen::fn_sub_21C3F0_0021c3f0);
    s2 = v0;
    lw(v1, s1, kBcmList);
    v1 = v1 & 0x2;
    if (v1 == 0) {
        // 0x00222c0c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 1549;
        jal(ctx, 0x222C18u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00222c20
    charge(ctx, 3);
    s3 = 0;
    for (;;) {
        // 0x00222ce4
        charge(ctx, 4);
        lw(v1, s1, kBcmRowCount);
        v1 = slt(s3, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00222c2c
        charge(ctx, 10);
        v0 = sll(s3, 3);
        v1 = addu(v0, s3);
        v0 = sll(v1, 3);
        v0 = addu(v1, v0);
        v0 = sll(v0, 4);
        s0 = addu(s6, v0);
        lw(v1, s0, 8);
        v0 = 1;
        if (v1 == v0) {
            // 0x00222c80
            charge(ctx, 5);
            a0 = s5;
            a1 = 49;
            jal(ctx, 0x222C88u, gen::fn_sub_21CCA0_0021cca0);
            s4 = v0;
        } else {
            // 0x00222c54
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x00222c64
                charge(ctx, 7);
                a0 = s5;
                a1 = 48;
                jal(ctx, 0x222C6Cu, gen::fn_sub_21CCA0_0021cca0);
                s4 = v0;
            } else {
                // 0x00222c5c
                charge(ctx, 2);
            }
        }
        // 0x00222c94
        charge(ctx, 20);
        a0 = addiu(s0, 16);
        a1 = s4;
        jal(ctx, 0x222C9Cu, gen::fn_sub_21D3B0_0021d3b0);
        a0 = addiu(s0, 272);
        a1 = 3;
        lw(a2, s0, 12);
        a3 = 1;
        jal(ctx, 0x222CB4u, gen::fn_bpIfontDrawNumber_00238980);
        a0 = s2;
        a1 = 43;
        jal(ctx, 0x222CC4u, gen::fn_sub_21CCA0_0021cca0);
        s4 = v0;
        a0 = addiu(s0, 1040);
        a1 = s4;
        jal(ctx, 0x222CD8u, gen::fn_sub_21D3B0_0021d3b0);
        s3 = addiu(s3, 1);
    }
    // 0x00222cf4
    charge(ctx, 3);
    lw(v1, s1, kBcmCursorOn);
    if (v1 != 0) {
        // 0x00222d00
        charge(ctx, 10);
        lw(v0, s1, kBcmCursorPage);
        a1 = addiu(v0, 32);
        a0 = s2;
        jal(ctx, 0x222D0Cu, gen::fn_sub_21CCA0_0021cca0);
        s4 = v0;
        a0 = addiu(s1, kBcmCursorQuad);
        a1 = s4;
        jal(ctx, 0x222D20u, gen::fn_sub_21D3B0_0021d3b0);
    }
    // 0x00222d28 (the shared epilogue, written out on this path)
    charge(ctx, 11);
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

// 0x00222D60 sub_222D60 -- 364 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bcmPanel_SetRows1] bcm_panel.c: asserts list bit 0 (line 1596); rows of 1,040 bytes: page 40, a 2-digit number,
// page 26 of set 6; then the cursor quad when +26872.
void sub_222D60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00222d60
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308
    if (v0 == 0) {
        // 0x00222d8c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x222D98u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00222da0
    charge(ctx, 14);
    lw(s1, gp, kGpBcmPanel);  // 0x7CE308
    a0 = 0;
    jal(ctx, 0x222DA8u, gen::fn_sub_21C3F0_0021c3f0);
    s4 = v0;
    a0 = 6;
    jal(ctx, 0x222DB8u, gen::fn_sub_21C3F0_0021c3f0);
    s3 = v0;
    s0 = addiu(s1, kBcmRows);
    lw(v1, s1, kBcmList);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        // 0x00222dd8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 1596;
        jal(ctx, 0x222DE4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00222dec
    charge(ctx, 3);
    s2 = 0;
    for (;;) {
        // 0x00222e64
        charge(ctx, 4);
        lw(v1, s1, kBcmRowCount);
        v1 = slt(s2, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00222df8
        charge(ctx, 27);
        v0 = sll(s2, 6);
        v0 = addu(v0, s2);
        v0 = sll(v0, 4);
        s5 = addu(s0, v0);
        a0 = s4;
        a1 = 40;
        jal(ctx, 0x222E10u, gen::fn_sub_21CCA0_0021cca0);
        a0 = addiu(s5, 16);
        a1 = v0;
        jal(ctx, 0x222E20u, gen::fn_sub_21D3B0_0021d3b0);
        a0 = addiu(s5, 272);
        a1 = 2;
        lw(a2, s5, 4);
        a3 = 1;
        jal(ctx, 0x222E38u, gen::fn_bpIfontDrawNumber_00238980);
        a0 = s3;
        a1 = 26;
        jal(ctx, 0x222E48u, gen::fn_sub_21CCA0_0021cca0);
        a0 = addiu(s5, 784);
        a1 = v0;
        jal(ctx, 0x222E58u, gen::fn_sub_21D3B0_0021d3b0);
        s2 = addiu(s2, 1);
    }
    // 0x00222e74
    charge(ctx, 3);
    lw(v1, s1, kBcmCursorOn);
    if (v1 != 0) {
        // 0x00222e80
        charge(ctx, 9);
        lw(v0, s1, kBcmCursorPage);
        a1 = addiu(v0, 32);
        a0 = s3;
        jal(ctx, 0x222E8Cu, gen::fn_sub_21CCA0_0021cca0);
        a0 = addiu(s1, kBcmCursorQuad);
        a1 = v0;
        jal(ctx, 0x222E9Cu, gen::fn_sub_21D3B0_0021d3b0);
    }
    // 0x00222ea4 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00222ED0 sub_222ED0 -- 196 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bcmPanel_CloseList] bcm_panel.c: flags |= 2, state 3, sub-list 0 (previous kept), sub timer 0, the command quads
// (pages cur and cur + 7).
void sub_222ED0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00222ed0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308
    if (v0 == 0) {
        // 0x00222eec
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x222EF8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00222f00
    charge(ctx, 37);
    lw(s0, gp, kGpBcmPanel);  // 0x7CE308
    a0 = 0;
    jal(ctx, 0x222F08u, gen::fn_sub_21C3F0_0021c3f0);
    s1 = v0;
    lw(v0, s0, kBcmFlags);
    v0 = v0 | 0x2;
    sw(v0, s0, kBcmFlags);
    v0 = 3;
    sw(v0, s0, kBcmState);
    lw(v0, s0, kBcmSub);
    sw(v0, s0, kBcmSubPrev);
    sw(zero, s0, kBcmSub);
    sw(zero, s0, kBcmSubTimer);
    a0 = s1;
    lw(a1, s0, kBcmCur);
    jal(ctx, 0x222F40u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, kBcmQuadCur);
    a1 = v0;
    jal(ctx, 0x222F50u, gen::fn_sub_21D3B0_0021d3b0);
    lw(v0, s0, kBcmCur);
    a1 = addiu(v0, 7);
    a0 = s1;
    jal(ctx, 0x222F64u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, kBcmQuadPrev);
    a1 = v0;
    jal(ctx, 0x222F74u, gen::fn_sub_21D3B0_0021d3b0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002230E0 sub_2230E0 -- 432 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bcmPanel_SetRows4] bcm_panel.c: asserts list bit 2 (line 1689); rows of 1,056 bytes: kind 1 -> four quads (pages
// 41, 41, 42, 42), kind 2 or 0 -> one quad (page 47), others nothing.
void sub_2230E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002230e0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308
    if (v0 == 0) {
        // 0x0022310c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x223118u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00223120
    charge(ctx, 10);
    lw(s4, gp, kGpBcmPanel);  // 0x7CE308
    a0 = 0;
    jal(ctx, 0x223128u, gen::fn_sub_21C3F0_0021c3f0);
    s1 = v0;
    s3 = addiu(s4, kBcmRows);
    lw(v1, s4, kBcmList);
    v1 = v1 & 0x4;
    if (v1 == 0) {
        // 0x00223148
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 1689;
        jal(ctx, 0x223154u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0022315c
    charge(ctx, 3);
    s0 = 0;
    for (;;) {
        // 0x00223258
        charge(ctx, 4);
        lw(v1, s4, kBcmRowCount);
        v1 = slt(s0, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00223168
        charge(ctx, 8);
        v1 = sll(s0, 5);
        v1 = addu(v1, s0);
        v1 = sll(v1, 5);
        s2 = addu(s3, v1);
        lw(a0, s2, 0);
        v1 = 1;
        if (a0 == v1) {
            // 0x002231cc
            charge(ctx, 3);
            s5 = 0;
            for (;;) {
                // 0x00223204
                charge(ctx, 3);
                v1 = slti(s5, 2);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002231d8
                charge(ctx, 11);
                a0 = s1;
                a1 = 41;
                jal(ctx, 0x2231E0u, gen::fn_sub_21CCA0_0021cca0);
                v1 = sll(s5, 8);
                v1 = addu(s2, v1);
                a0 = addiu(v1, 16);
                a1 = v0;
                jal(ctx, 0x2231F8u, gen::fn_sub_21D3B0_0021d3b0);
                s5 = addiu(s5, 1);
            }
            // 0x00223210
            charge(ctx, 3);
            s5 = 2;
            for (;;) {
                // 0x00223248
                charge(ctx, 3);
                v1 = slti(s5, 4);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0022321c
                charge(ctx, 11);
                a0 = s1;
                a1 = 42;
                jal(ctx, 0x223224u, gen::fn_sub_21CCA0_0021cca0);
                v1 = sll(s5, 8);
                v1 = addu(s2, v1);
                a0 = addiu(v1, 16);
                a1 = v0;
                jal(ctx, 0x22323Cu, gen::fn_sub_21D3B0_0021d3b0);
                s5 = addiu(s5, 1);
            }
        } else {
            // 0x00223188
            charge(ctx, 3);
            v1 = 2;
            if (a0 != v1) {
                // 0x00223194
                charge(ctx, 2);
                if (a0 == 0) {
                    goto L_002231a4;
                }
                // 0x0022319c
                charge(ctx, 2);
                goto L_00223254;
            }
        L_002231a4:
            charge(ctx, 10);
            a0 = s1;
            a1 = 47;
            jal(ctx, 0x2231ACu, gen::fn_sub_21CCA0_0021cca0);
            a0 = addiu(s2, 16);
            a1 = v0;
            jal(ctx, 0x2231BCu, gen::fn_sub_21D3B0_0021d3b0);
        }
    L_00223254:
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x00223268
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00224860 sub_224860 -- 216 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bcmPanel_SetRows8] bcm_panel.c: asserts list bit 3 (line 2190); a 2-digit number per row (784 bytes).
void sub_224860(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00224860
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308
    if (v0 == 0) {
        // 0x00224880
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x22488Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00224894
    charge(ctx, 9);
    lw(s1, gp, kGpBcmPanel);  // 0x7CE308
    a0 = 0;
    jal(ctx, 0x22489Cu, gen::fn_sub_21C3F0_0021c3f0);
    s0 = addiu(s1, kBcmRows);
    lw(v1, s1, kBcmList);
    v1 = v1 & 0x8;
    if (v1 == 0) {
        // 0x002248b8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 2190;
        jal(ctx, 0x2248C4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002248cc
    charge(ctx, 3);
    s2 = 0;
    for (;;) {
        // 0x0022490c
        charge(ctx, 4);
        lw(v1, s1, kBcmRowCount);
        v1 = slt(s2, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002248d8
        charge(ctx, 13);
        v0 = sll(s2, 3);
        v1 = subu(v0, s2);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v0 = sll(v0, 4);
        v0 = addu(s0, v0);
        a0 = addiu(v0, 256);
        a1 = 2;
        lw(a2, v0, 772);
        a3 = 1;
        jal(ctx, 0x224900u, gen::fn_bpIfontDrawNumber_00238980);
        s2 = addiu(s2, 1);
    }
    // 0x0022491c
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00226320 sub_226320 -- 684 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bcmPanel_SetFrame] bcm_panel.c: the frame quads from panel set 0: when +29200 is 0..2 the pages 30..33 and their
// mirrored copies (sub_21E380 modes 1, 1, 0, 0, 4); always pages 29, 38, 39, 38 (mode 2) and six rows of page 44 (512
// bytes apart, plain and mode 1).
void sub_226320(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00226320
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308
    if (v0 == 0) {
        // 0x00226344
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x226350u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00226358
    charge(ctx, 9);
    lw(s0, gp, kGpBcmPanel);  // 0x7CE308
    a0 = 0;
    jal(ctx, 0x226360u, gen::fn_sub_21C3F0_0021c3f0);
    s1 = v0;
    lw(v1, s0, kBcmFrameMode);
    v0 = 2;
    if (v1 != v0) {
        // 0x0022637c
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            goto L_00226398;
        }
        // 0x00226388
        charge(ctx, 2);
        if (v1 == 0) {
            goto L_00226398;
        }
        // 0x00226390
        charge(ctx, 2);
        goto L_002264cc;
    }
L_00226398:
    charge(ctx, 77);
    a0 = s1;
    a1 = 30;
    jal(ctx, 0x2263A0u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, 5424);
    a1 = v0;
    jal(ctx, 0x2263B0u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s1;
    a1 = 31;
    jal(ctx, 0x2263C0u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, 5680);
    a1 = v0;
    jal(ctx, 0x2263D0u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s1;
    a1 = 32;
    jal(ctx, 0x2263E0u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, 5936);
    a1 = v0;
    jal(ctx, 0x2263F0u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s1;
    a1 = 33;
    jal(ctx, 0x226400u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, 6192);
    a1 = v0;
    jal(ctx, 0x226410u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s1;
    a1 = 30;
    jal(ctx, 0x226420u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, 6448);
    a1 = v0;
    a2 = 1;
    jal(ctx, 0x226434u, gen::fn_sub_21E380_0021e380);
    a0 = s1;
    a1 = 31;
    jal(ctx, 0x226444u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, 6704);
    a1 = v0;
    a2 = 1;
    jal(ctx, 0x226458u, gen::fn_sub_21E380_0021e380);
    a0 = s1;
    a1 = 31;
    jal(ctx, 0x226468u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, 6960);
    a1 = v0;
    a2 = 0;
    jal(ctx, 0x22647Cu, gen::fn_sub_21E380_0021e380);
    a0 = s1;
    a1 = 33;
    jal(ctx, 0x22648Cu, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, 7216);
    a1 = v0;
    a2 = 0;
    jal(ctx, 0x2264A0u, gen::fn_sub_21E380_0021e380);
    a0 = s1;
    a1 = 31;
    jal(ctx, 0x2264B0u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, 7472);
    a1 = v0;
    a2 = 4;
    jal(ctx, 0x2264C4u, gen::fn_sub_21E380_0021e380);
L_002264cc:
    charge(ctx, 41);
    a0 = s1;
    a1 = 29;
    jal(ctx, 0x2264D4u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, 8496);
    a1 = v0;
    jal(ctx, 0x2264E4u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s1;
    a1 = 38;
    jal(ctx, 0x2264F4u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, 7728);
    a1 = v0;
    jal(ctx, 0x226504u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s1;
    a1 = 39;
    jal(ctx, 0x226514u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, 7984);
    a1 = v0;
    jal(ctx, 0x226524u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s1;
    a1 = 38;
    jal(ctx, 0x226534u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, 8240);
    a1 = v0;
    a2 = 2;
    jal(ctx, 0x226548u, gen::fn_sub_21E380_0021e380);
    a0 = s1;
    a1 = 44;
    jal(ctx, 0x226558u, gen::fn_sub_21CCA0_0021cca0);
    s2 = v0;
    s3 = 0;
    for (;;) {
        // 0x002265a0
        charge(ctx, 3);
        v1 = slti(s3, 6);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00226570
        charge(ctx, 12);
        v0 = sll(s3, 9);
        s1 = addu(s0, v0);
        a0 = addiu(s1, 8752);
        a1 = s2;
        jal(ctx, 0x226580u, gen::fn_sub_21D3B0_0021d3b0);
        a0 = addiu(s1, 9008);
        a1 = s2;
        a2 = 1;
        jal(ctx, 0x226594u, gen::fn_sub_21E380_0021e380);
        s3 = addiu(s3, 1);
    }
    // 0x002265ac
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0022B4E0 sub_22B4E0 -- 68 bytes; frame 0x10: ra sp+0x0
// [bcmPanel_IsListOpen] bcm_panel.c: asserts the work (line 230), $v0 = flags & 2.
void sub_22B4E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0022b4e0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308
    if (v0 == 0) {
        // 0x0022b4f4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x22B500u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0022b508 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308
    lw(v0, v0, kBcmFlags);
    v0 = v0 & 0x2;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0022B580 sub_22B580 -- 168 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bcmPanel_SetHeader] bcm_panel.c: pages 62, 63, 64 of set 0 into the quads +26096, +26352, +26608.
void sub_22B580(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0022b580
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308
    if (v0 == 0) {
        // 0x0022b5a0
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x22B5ACu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0022b5b4
    charge(ctx, 8);
    lw(s0, gp, kGpBcmPanel);  // 0x7CE308
    a0 = 0;
    jal(ctx, 0x22B5BCu, gen::fn_sub_21C3F0_0021c3f0);
    s2 = v0;
    s1 = 0;
    for (;;) {
        // 0x0022b600
        charge(ctx, 3);
        v1 = slti(s1, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0022b5d4
        charge(ctx, 11);
        a1 = addiu(s1, 62);
        a0 = s2;
        jal(ctx, 0x22B5DCu, gen::fn_sub_21CCA0_0021cca0);
        v1 = sll(s1, 8);
        v1 = addu(s0, v1);
        a0 = addiu(v1, 26096);
        a1 = v0;
        jal(ctx, 0x22B5F4u, gen::fn_sub_21D3B0_0021d3b0);
        s1 = addiu(s1, 1);
    }
    // 0x0022b60c
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0022C210 sub_22C210 -- 188 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bcmPanel_SetDetailFrame] bcm_panel.c: page 66 of set 0 into +27136 and (mode 1) +27392, page 67 into +27648.
void sub_22C210(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0022c210
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308
    if (v0 == 0) {
        // 0x0022c230
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x22C23Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0022c244
    charge(ctx, 34);
    lw(s0, gp, kGpBcmPanel);  // 0x7CE308
    a0 = 0;
    jal(ctx, 0x22C24Cu, gen::fn_sub_21C3F0_0021c3f0);
    s2 = v0;
    a0 = s2;
    a1 = 66;
    jal(ctx, 0x22C260u, gen::fn_sub_21CCA0_0021cca0);
    s1 = v0;
    a0 = addiu(s0, 27136);
    a1 = s1;
    jal(ctx, 0x22C274u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = addiu(s0, 27392);
    a1 = s1;
    a2 = 1;
    jal(ctx, 0x22C288u, gen::fn_sub_21E380_0021e380);
    a0 = s2;
    a1 = 67;
    jal(ctx, 0x22C298u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, 27648);
    a1 = v0;
    jal(ctx, 0x22C2A8u, gen::fn_sub_21D3B0_0021d3b0);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0022E850 sub_22E850 -- 176 bytes; frame 0x10: ra sp+0x0
// [bppPanel_IconPage](kind) bpp_panel.c: 1 -> 13, 2 -> 12, 3 -> 14, 4 -> 15, 5 -> 16; else K_Assert (line 1069), 0.
void sub_22E850(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0022e850
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = 5;
    if (a0 == v0) {
        // 0x0022e8cc
        charge(ctx, 3);
        v0 = 16;
    } else {
        // 0x0022e864
        charge(ctx, 3);
        v0 = 4;
        if (a0 == v0) {
            // 0x0022e8c0
            charge(ctx, 3);
            v0 = 15;
        } else {
            // 0x0022e870
            charge(ctx, 3);
            v0 = 3;
            if (a0 == v0) {
                // 0x0022e8b4
                charge(ctx, 3);
                v0 = 14;
            } else {
                // 0x0022e87c
                charge(ctx, 3);
                v0 = 2;
                if (a0 == v0) {
                    // 0x0022e8a8
                    charge(ctx, 3);
                    v0 = 12;
                } else {
                    // 0x0022e888
                    charge(ctx, 3);
                    v0 = 1;
                    if (a0 == v0) {
                        // 0x0022e89c
                        charge(ctx, 3);
                        v0 = 13;
                    } else {
                        // 0x0022e894
                        charge(ctx, 2);
                        // 0x0022e8d8
                        charge(ctx, 6);
                        a0 = 0x690000;
                        a0 = addiu(a0, -6512);  // "bpp_panel.c"
                        a1 = 1069;
                        jal(ctx, 0x22E8E4u, gen::fn_sub_19D3F0_0019d3f0);
                        v0 = 0;
                    }
                }
            }
        }
    }
    // 0x0022e8f0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002337E0 sub_2337E0 -- 100 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [bppPanel_Open](member) bpp_panel.c: asserts the member is not open (bit 4, line 2894); +2120 = 0, flags |= 0x40
// then |= 0x10.
void sub_2337E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002337e0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, a0, 0);
    v1 = nor(v1, 0);
    v1 = v1 & 0x10;
    if (v1 == 0) {
        // 0x00233804
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6512);  // "bpp_panel.c"
        a1 = 2894;
        jal(ctx, 0x233810u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00233818 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    sw(zero, s0, 2120);
    lw(v1, s0, 0);
    v1 = v1 | 0x40;
    sw(v1, s0, 0);
    v1 = v1 | 0x10;
    sw(v1, s0, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00233850 sub_233850 -- 116 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [bppPanel_Close](member) bpp_panel.c: asserts it is open (line 2904); flags &= ~0x40, +2120 = 0, |= 0x80, &= ~0x10.
void sub_233850(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00233850
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, a0, 0);
    v1 = v1 & 0x10;
    if (v1 == 0) {
        // 0x00233870
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6512);  // "bpp_panel.c"
        a1 = 2904;
        jal(ctx, 0x23387Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00233884 (the shared epilogue, written out on this path)
    charge(ctx, 16);
    lw(a0, s0, 0);
    v1 = si(-65);
    v1 = a0 & v1;
    sw(v1, s0, 0);
    sw(zero, s0, 2120);
    lw(v1, s0, 0);
    a0 = v1 | 0x80;
    sw(a0, s0, 0);
    v1 = si(-17);
    v1 = a0 & v1;
    sw(v1, s0, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0023D7A0 sub_23D7A0 -- 16 bytes; leaf frame (no stack)
// [sflPanel_Register](work) sfl_panel.c: +0 = 0, slot = work (no assert).
void sub_23D7A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, gp{ctx, 28};
    // 0x0023d7a0
    enter(ctx, 4);  // entry check point + this block's cycles
    sw(zero, a0, 0);
    sw(a0, gp, kGpSflPanel);  // 0x7CE318
}

// 0x0023D7F0 sub_23D7F0 -- 128 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [sflPanel_Start] sfl_panel.c: asserts the work (line 127); +4 = 3; asserts not started (bit 0, line 156); flags |= 1.
void sub_23D7F0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0023d7f0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpSflPanel);  // 0x7CE318
    if (v1 == 0) {
        // 0x0023d808
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6048);  // "sfl_panel.c"
        a1 = 127;
        jal(ctx, 0x23D814u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0023d81c
    charge(ctx, 8);
    lw(s0, gp, kGpSflPanel);  // 0x7CE318
    v1 = 3;
    sw(v1, s0, 4);
    lw(v1, s0, 0);
    v1 = nor(v1, 0);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        // 0x0023d83c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6048);  // "sfl_panel.c"
        a1 = 156;
        jal(ctx, 0x23D848u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0023d850 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lw(v1, s0, 0);
    v1 = v1 | 0x1;
    sw(v1, s0, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00245E00 sub_245E00 -- 72 bytes; frame 0x10: ra sp+0x0
// [bpcMain_SetFlag80] bpc_main.c: asserts the work (line 151), flags |= 0x80.
void sub_245E00(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00245e00
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBpcMain);  // 0x7CE320
    if (v1 == 0) {
        // 0x00245e14
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6016);  // "bpc_main.c"
        a1 = 151;
        jal(ctx, 0x245E20u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00245e28 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lw(a0, gp, kGpBpcMain);  // 0x7CE320
    lw(v1, a0, 0);
    v1 = v1 | 0x80;
    sw(v1, a0, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00245E50 sub_245E50 -- 76 bytes; frame 0x10: ra sp+0x0
// [bpcMain_ClearFlag80] bpc_main.c: asserts the work (line 151), flags &= ~0x80.
void sub_245E50(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00245e50
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBpcMain);  // 0x7CE320
    if (v1 == 0) {
        // 0x00245e64
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6016);  // "bpc_main.c"
        a1 = 151;
        jal(ctx, 0x245E70u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00245e78 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(a1, gp, kGpBpcMain);  // 0x7CE320
    lw(a0, a1, 0);
    v1 = si(-129);
    v1 = a0 & v1;
    sw(v1, a1, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00249130 sub_249130 -- 68 bytes; frame 0x10: ra sp+0x0
// [bpmMain_IsActive] bpm_main.c: asserts the work (line 61), $v0 = flags & 1.
void sub_249130(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00249130
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBpmMain);  // 0x7CE324
    if (v0 == 0) {
        // 0x00249144
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6000);  // "bpm_main.c"
        a1 = 61;
        jal(ctx, 0x249150u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00249158 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpBpmMain);  // 0x7CE324
    lw(v0, v0, 0);
    v0 = v0 & 0x1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00249600 sub_249600 -- 68 bytes; frame 0x10: ra sp+0x0
// [bpeMain_IsActive] bpe_main.c: asserts the work (line 55), $v0 = flags & 1.
void sub_249600(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00249600
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBpeMain);  // 0x7CE328
    if (v0 == 0) {
        // 0x00249614
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5984);  // "bpe_main.c"
        a1 = 55;
        jal(ctx, 0x249620u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00249628 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpBpeMain);  // 0x7CE328
    lw(v0, v0, 0);
    v0 = v0 & 0x1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00249650 sub_249650 -- 48 bytes; frame 0x10: ra sp+0x0
// [bpList_IsLocked](u16 id): $v0 = (datGetFlag(id + 4800) == 0). Caller sub_208010.
void sub_249650(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00249650
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = a0 & 0xFFFF;
    a0 = addiu(v0, 4800);
    jal(ctx, 0x249660u, gen::fn_datGetFlag_0016f190);
    v0 = sltu(0, v0);
    v0 = v0 ^ 0x1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00249680 sub_249680 -- 12 bytes; leaf frame (no stack)
// (obj) +1540 = 0 (the draw flag sub_24A180 tests). Caller sub_239170.
void sub_249680(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4};
    // 0x00249680
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(zero, a0, 1540);
}

// 0x0024A180 sub_24A180 -- 168 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// (obj) when +1540 bit 0: four RwRenderStateSet calls through the slot 0x960090 (9 -> 2, 20 -> 2, 6 -> 0, 8 -> 0),
// then the method +72 of the object at +1536 (jalr).
void sub_24A180(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0024a180
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, a0, 1540);
    v1 = nor(v1, 0);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        // 0x0024a1a8
        charge(ctx, 26);
        s1 = 0x960000;
        s1 = addiu(s1, 144);  // &pfn_RwRenderStateSet
        a0 = 9;
        a1 = 2;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x24A1BCu, v0.u());
        a0 = 20;
        a1 = 2;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x24A1D0u, v0.u());
        a0 = 6;
        a1 = 0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x24A1E4u, v0.u());
        a0 = 8;
        a1 = 0;
        lw(v0, s1, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x24A1F8u, v0.u());
        lw(a0, s0, 1536);
        lw(v0, a0, 72);
        jalr(ctx, 0x24A208u, v0.u());
    }
    // 0x0024a210 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0024D110 sub_24D110 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [sflCamera_Register](work) sfl_camera.c: asserts the slot is empty (line 66), +0 = +4 = 0, slot = work.
void sub_24D110(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0024d110
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, gp, kGpSflCamera);  // 0x7CE33C
    if (v1 != 0) {
        // 0x0024d12c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5744);  // "sfl_camera.c"
        a1 = 66;
        jal(ctx, 0x24D138u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0024d140 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    sw(zero, s0, 0);
    sw(zero, s0, 4);
    sw(s0, gp, kGpSflCamera);  // 0x7CE33C
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0024DA00 sub_24DA00 -- 20 bytes; leaf frame (no stack)
// [gcPose_Register](work): +0 = +4 = 0, slot 0x7CE340 = work (no assert).
void sub_24DA00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, gp{ctx, 28};
    // 0x0024da00
    enter(ctx, 5);  // entry check point + this block's cycles
    sw(zero, a0, 0);
    sw(zero, a0, 4);
    sw(a0, gp, kGpGcPose);  // 0x7CE340
}

// 0x002519D0 sub_2519D0 -- 68 bytes; frame 0x10: ra sp+0x0
// [bpTut_IsActive] bp_tut.c: asserts the work (line 57), $v0 = flags & 1.
void sub_2519D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002519d0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBpTut);  // 0x7CE344
    if (v0 == 0) {
        // 0x002519e4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5696);  // "bp_tut.c"
        a1 = 57;
        jal(ctx, 0x2519F0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002519f8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpBpTut);  // 0x7CE344
    lw(v0, v0, 0);
    v0 = v0 & 0x1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00251E10 sub_251E10 -- 108 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [bpTuta_Start] bp_tuta.c: asserts the work (line 49); datSetFlag(4870, 1); sub_21C7F0 (bp_res.c: request
// battle/panel/bp_tutorial.bin); +4 = 0; flags |= 1.
void sub_251E10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00251e10
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBpTuta);  // 0x7CE348
    if (v0 == 0) {
        // 0x00251e28
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5680);  // "bp_tuta.c"
        a1 = 49;
        jal(ctx, 0x251E34u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00251e3c
    charge(ctx, 16);
    lw(s0, gp, kGpBpTuta);  // 0x7CE348
    a0 = 4870;
    a1 = 1;
    jal(ctx, 0x251E48u, gen::fn_datSetFlag_0016f1f0);
    jal(ctx, 0x251E50u, gen::fn_sub_21C7F0_0021c7f0);
    sw(zero, s0, 4);
    lw(v1, s0, 0);
    v1 = v1 | 0x1;
    sw(v1, s0, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00251E80 sub_251E80 -- 68 bytes; frame 0x10: ra sp+0x0
// [bpTuta_IsActive] bp_tuta.c: asserts the work (line 49), $v0 = flags & 1.
void sub_251E80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00251e80
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBpTuta);  // 0x7CE348
    if (v0 == 0) {
        // 0x00251e94
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5680);  // "bp_tuta.c"
        a1 = 49;
        jal(ctx, 0x251EA0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00251ea8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpBpTuta);  // 0x7CE348
    lw(v0, v0, 0);
    v0 = v0 & 0x1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00253410 sub_253410 -- 192 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bpdMain_Start] bpd_main.c: asserts the work (line 37); page 76 of panel set 1 into the ten quads +32 + 288i;
// +2896 = 0; flags |= 2.
void sub_253410(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00253410
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBpdMain);  // 0x7CE350
    if (v0 == 0) {
        // 0x00253430
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5648);  // "bpd_main.c"
        a1 = 37;
        jal(ctx, 0x25343Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00253444
    charge(ctx, 12);
    lw(s0, gp, kGpBpdMain);  // 0x7CE350
    a0 = 1;
    jal(ctx, 0x25344Cu, gen::fn_sub_21C3F0_0021c3f0);
    a0 = v0;
    a1 = 76;
    jal(ctx, 0x25345Cu, gen::fn_sub_21CCA0_0021cca0);
    s2 = v0;
    s1 = 0;
    for (;;) {
        // 0x00253498
        charge(ctx, 3);
        v1 = slti(s1, 10);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00253474
        charge(ctx, 9);
        v0 = sll(s1, 3);
        v0 = addu(v0, s1);
        v0 = sll(v0, 5);
        v0 = addu(s0, v0);
        a0 = addiu(v0, 32);
        a1 = s2;
        jal(ctx, 0x25348Cu, gen::fn_sub_21D3B0_0021d3b0);
        s1 = addiu(s1, 1);
    }
    // 0x002534a4
    charge(ctx, 11);
    sw(zero, s0, 2896);
    lw(v1, s0, 0);
    v1 = v1 | 0x2;
    sw(v1, s0, 0);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0025CDB0 sub_25CDB0 -- 116 bytes; frame 0x10: ra sp+0x0
// [frFontChain_MoveLastTo](chain, x $f12, y $f13): the last node of the chain (links +36) goes to (int)(16x), (int)(8y)
// (frFontChainMoveTo); a 0 chain passes 0.
void sub_25CDB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f13{ctx, 13};
    // 0x0025cdb0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = 0;
    for (;;) {
        // 0x0025cdd4
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0025cdc4
        charge(ctx, 2);
        if (a0 != 0) {
            // 0x0025cdcc
            charge(ctx, 1);
            a2 = a0;
        }
        // 0x0025cdd0
        charge(ctx, 1);
        lw(a0, a0, 36);
    }
    // 0x0025cddc
    charge(ctx, 18);
    v0 = 0x41800000;
    mtc1(v0, f0);
    mul_s(f0, f0, f12);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    v0 = 0x41000000;
    mtc1(v0, f0);
    mul_s(f0, f0, f13);
    cvt_w_s(f0, f0);
    mfc1(a1, f0);
    jal(ctx, 0x25CE0Cu, gen::fn_frFontChainMoveTo_003b1c40);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0025CE30 sub_25CE30 -- 116 bytes; frame 0x10: ra sp+0x0
// [frFontChain_CentreLastAt](chain, x $f12, y $f13): as sub_25CDB0 with frFontChainCentreAt.
void sub_25CE30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f13{ctx, 13};
    // 0x0025ce30
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = 0;
    for (;;) {
        // 0x0025ce54
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0025ce44
        charge(ctx, 2);
        if (a0 != 0) {
            // 0x0025ce4c
            charge(ctx, 1);
            a2 = a0;
        }
        // 0x0025ce50
        charge(ctx, 1);
        lw(a0, a0, 36);
    }
    // 0x0025ce5c
    charge(ctx, 18);
    v0 = 0x41800000;
    mtc1(v0, f0);
    mul_s(f0, f0, f12);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    v0 = 0x41000000;
    mtc1(v0, f0);
    mul_s(f0, f0, f13);
    cvt_w_s(f0, f0);
    mfc1(a1, f0);
    jal(ctx, 0x25CE8Cu, gen::fn_frFontChainCentreAt_003b1c90);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0025D760 sub_25D760 -- 72 bytes; frame 0x10: ra sp+0x0
// [bpRush_SetFlag20] bp_rush.c: asserts the work (line 50), flags |= 0x20.
void sub_25D760(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0025d760
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBpRush);  // 0x7CE36C
    if (v1 == 0) {
        // 0x0025d774
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5144);  // "bp_rush.c"
        a1 = 50;
        jal(ctx, 0x25D780u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025d788 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lw(a0, gp, kGpBpRush);  // 0x7CE36C
    lw(v1, a0, 0);
    v1 = v1 | 0x20;
    sw(v1, a0, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0025D7B0 sub_25D7B0 -- 76 bytes; frame 0x10: ra sp+0x0
// [bpRush_ClearFlag20] bp_rush.c: asserts the work (line 50), flags &= ~0x20.
void sub_25D7B0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0025d7b0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBpRush);  // 0x7CE36C
    if (v1 == 0) {
        // 0x0025d7c4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5144);  // "bp_rush.c"
        a1 = 50;
        jal(ctx, 0x25D7D0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025d7d8 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(a1, gp, kGpBpRush);  // 0x7CE36C
    lw(a0, a1, 0);
    v1 = si(-33);
    v1 = a0 & v1;
    sw(v1, a1, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0025D800 sub_25D800 -- 72 bytes; frame 0x10: ra sp+0x0
// [bpRush_SetFlag40] bp_rush.c: asserts the work (line 50), flags |= 0x40.
void sub_25D800(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0025d800
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBpRush);  // 0x7CE36C
    if (v1 == 0) {
        // 0x0025d814
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5144);  // "bp_rush.c"
        a1 = 50;
        jal(ctx, 0x25D820u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025d828 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lw(a0, gp, kGpBpRush);  // 0x7CE36C
    lw(v1, a0, 0);
    v1 = v1 | 0x40;
    sw(v1, a0, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0025D850 sub_25D850 -- 76 bytes; frame 0x10: ra sp+0x0
// [bpRush_ClearFlag40] bp_rush.c: asserts the work (line 50), flags &= ~0x40.
void sub_25D850(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0025d850
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBpRush);  // 0x7CE36C
    if (v1 == 0) {
        // 0x0025d864
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5144);  // "bp_rush.c"
        a1 = 50;
        jal(ctx, 0x25D870u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025d878 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(a1, gp, kGpBpRush);  // 0x7CE36C
    lw(a0, a1, 0);
    v1 = si(-65);
    v1 = a0 & v1;
    sw(v1, a1, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00260900 sub_260900 -- 32 bytes; leaf frame (no stack)
// (obj, i): the 128-byte entry i of the table at obj+388: $v0 = entry+92 - entry+84 (a width).
void sub_260900(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00260900
    enter(ctx, 8);  // entry check point + this block's cycles
    v1 = sll(a1, 7);
    lw(v0, a0, 388);
    v0 = addu(v0, v1);
    lw(v1, v0, 92);
    lw(v0, v0, 84);
    v0 = subu(v1, v0);
}

// 0x00260920 sub_260920 -- 32 bytes; leaf frame (no stack)
// (obj, i): $v0 = entry+96 - entry+88 (a height) of the same entries.
void sub_260920(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00260920
    enter(ctx, 8);  // entry check point + this block's cycles
    v1 = sll(a1, 7);
    lw(v0, a0, 388);
    v0 = addu(v0, v1);
    lw(v1, v0, 96);
    lw(v0, v0, 88);
    v0 = subu(v1, v0);
}

// 0x00260940 sub_260940 -- 36 bytes; leaf frame (no stack)
// (obj, i): $v0 = obj+260[entry i's +20] (a word table indexed by the entry).
void sub_260940(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00260940
    enter(ctx, 9);  // entry check point + this block's cycles
    v1 = sll(a1, 7);
    lw(v0, a0, 388);
    v0 = addu(v0, v1);
    lw(v0, v0, 20);
    v0 = sll(v0, 2);
    v0 = addu(v0, a0);
    lw(v0, v0, 260);
}

// 0x00260970 sub_260970 -- 148 bytes; frame 0x40: ra sp+0x10, s0 sp+0x0 (sq)
// [FullQuad_Register](work): +0 = 0; the quad +784 gets the rect {0, 0, 640, 448}, depth 10 (sub_21EA00 /
// sub_21EAC0) and the colour (255, 255, 255, 0); slot 0x7CE378 = work.
void sub_260970(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x00260970
    enter(ctx, 37);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    sw(zero, a0, 0);
    sw(zero, sp, 0x20);
    sw(zero, sp, 0x24);
    v0 = 0x44200000;
    sw(v0, sp, 0x28);
    v0 = 0x43E00000;
    sw(v0, sp, 0x2C);
    a0 = addiu(s0, 784);
    a1 = addiu(sp, 0x20);
    jal(ctx, 0x2609A4u, gen::fn_sub_21D8E0_0021d8e0);
    a0 = 10;
    jal(ctx, 0x2609B0u, gen::fn_sub_21EA00_0021ea00);
    a0 = addiu(s0, 784);
    mov_s(f12, f0);
    jal(ctx, 0x2609C0u, gen::fn_sub_21EAC0_0021eac0);
    v0 = 255;
    sb(v0, sp, 0x3C);
    sb(v0, sp, 0x3D);
    sb(v0, sp, 0x3E);
    sb(zero, sp, 0x3F);
    a0 = addiu(s0, 784);
    a1 = addiu(sp, 0x3C);
    jal(ctx, 0x2609E4u, gen::fn_sub_21D950_0021d950);
    sw(s0, gp, kGpFullQuad);  // 0x7CE378
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002626E0 sub_2626E0 -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [brHero_Register](work) br_hero.c: asserts the slot is empty (line 89), +0 = 0, slot = work.
void sub_2626E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002626e0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, gp, kGpBrHero);  // 0x7CE37C
    if (v1 != 0) {
        // 0x002626fc
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5080);  // "br_hero.c"
        a1 = 89;
        jal(ctx, 0x262708u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00262710 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    sw(zero, s0, 0);
    sw(s0, gp, kGpBrHero);  // 0x7CE37C
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00264CA0 sub_264CA0 -- 216 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [brHero_StatPage](stat) br_hero.c: page of result set 1 (sub_233D70(1)) for stat 0..5: 11, 13, 12, 16, 14, 15 (the
// jump table 0x7B79B0); else K_Assert (line 1188) with the leftover $s1.
void sub_264CA0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00264ca0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    a0 = 1;
    jal(ctx, 0x264CBCu, gen::fn_sub_233D70_00233d70);
    s0 = v0;
    at = sltiu(s2, 6);
    if (at == 0) {
        // 0x00264d38
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5080);  // "br_hero.c"
        a1 = 1188;
        jal(ctx, 0x264D44u, gen::fn_sub_19D3F0_0019d3f0);
    } else {
        // 0x00264cd4
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 31152);  // &0x7B79B0
        v0 = sll(s2, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x264CF0u:  // table[0]
            // 0x00264cf0
            charge(ctx, 3);
            s1 = 11;
            break;
        case 0x264CFCu:  // table[1]
            // 0x00264cfc
            charge(ctx, 3);
            s1 = 13;
            break;
        case 0x264D08u:  // table[2]
            // 0x00264d08
            charge(ctx, 3);
            s1 = 12;
            break;
        case 0x264D14u:  // table[3]
            // 0x00264d14
            charge(ctx, 3);
            s1 = 16;
            break;
        case 0x264D20u:  // table[4]
            // 0x00264d20
            charge(ctx, 3);
            s1 = 14;
            break;
        case 0x264D2Cu:  // table[5]
            // 0x00264d2c
            charge(ctx, 3);
            s1 = 15;
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
    }
    // 0x00264d4c
    charge(ctx, 11);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x264D54u, gen::fn_sub_21CCA0_0021cca0);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00264D80 sub_264D80 -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [brPersona_Register](work) br_persona.c: asserts the slot is empty (line 45), +0 = 0, slot = work.
void sub_264D80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00264d80
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, gp, kGpBrPersona);  // 0x7CE380
    if (v1 != 0) {
        // 0x00264d9c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5064);  // "br_persona.c"
        a1 = 45;
        jal(ctx, 0x264DA8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00264db0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    sw(zero, s0, 0);
    sw(s0, gp, kGpBrPersona);  // 0x7CE380
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00272330 sub_272330 -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [brpSeq_Register](work) brp_seq.c: asserts the slot is empty (line 183), +0 = 0, slot = work.
void sub_272330(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00272330
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, gp, kGpBrpSeq);  // 0x7CE3C0
    if (v1 != 0) {
        // 0x0027234c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4728);  // "brp_seq.c"
        a1 = 183;
        jal(ctx, 0x272358u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00272360 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    sw(zero, s0, 0);
    sw(s0, gp, kGpBrpSeq);  // 0x7CE3C0
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002737A0 sub_2737A0 -- 84 bytes; frame 0x10: ra sp+0x0
// [brpSeq_DrawBirth] brp_seq.c: asserts the work (line 176); flags & 0x40 -> sub_24B8A0 (brp_birth.c).
void sub_2737A0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002737a0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBrpSeq);  // 0x7CE3C0
    if (v1 == 0) {
        // 0x002737b4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4728);  // "brp_seq.c"
        a1 = 176;
        jal(ctx, 0x2737C0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002737c8
    charge(ctx, 5);
    lw(v1, gp, kGpBrpSeq);  // 0x7CE3C0
    lw(v1, v1, kBsFlags);
    v1 = v1 & 0x40;
    if (v1 != 0) {
        // 0x002737dc
        charge(ctx, 2);
        jal(ctx, 0x2737DCu, gen::fn_sub_24B8A0_0024b8a0);
    }
    // 0x002737e4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00273980 sub_273980 -- 132 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [brpSeq_EndStep] brp_seq.c: asserts the work and flags bit 1 (line 936); +16 = 6; flags &= ~1.
void sub_273980(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00273980
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpBrpSeq);  // 0x7CE3C0
    if (v1 == 0) {
        // 0x00273998
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4728);  // "brp_seq.c"
        a1 = 176;
        jal(ctx, 0x2739A4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002739ac
    charge(ctx, 6);
    lw(s0, gp, kGpBrpSeq);  // 0x7CE3C0
    lw(v1, s0, kBsFlags);
    v1 = nor(v1, 0);
    v1 = v1 & 0x2;
    if (v1 == 0) {
        // 0x002739c4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4728);  // "brp_seq.c"
        a1 = 936;
        jal(ctx, 0x2739D0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002739d8 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    v1 = 6;
    sw(v1, s0, kBsStep);
    lw(a0, s0, kBsFlags);
    v1 = si(-2);
    v1 = a0 & v1;
    sw(v1, s0, kBsFlags);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00273E10 sub_273E10 -- 124 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [brpSeq_RequestMessage] brp_seq.c: asserts the work and +116 == 9 (line 1038); msgWinRequestMessage(3); +24 = 2.
void sub_273E10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00273e10
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBrpSeq);  // 0x7CE3C0
    if (v0 == 0) {
        // 0x00273e28
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4728);  // "brp_seq.c"
        a1 = 176;
        jal(ctx, 0x273E34u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00273e3c
    charge(ctx, 5);
    lw(s0, gp, kGpBrpSeq);  // 0x7CE3C0
    lw(v1, s0, kBsState);
    v0 = 9;
    if (v1 != v0) {
        // 0x00273e50
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4728);  // "brp_seq.c"
        a1 = 1038;
        jal(ctx, 0x273E5Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00273e64
    charge(ctx, 10);
    a0 = 3;
    jal(ctx, 0x273E68u, gen::fn_msgWinRequestMessage_003c7430);
    v1 = 2;
    sw(v1, s0, kBsMsgState);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00274D40 sub_274D40 -- 72 bytes; frame 0x10: ra sp+0x0
// [brpSeq_HasEntry] brp_seq.c: $v0 = (index +432 < count +448).
void sub_274D40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00274d40
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBrpSeq);  // 0x7CE3C0
    if (v0 == 0) {
        // 0x00274d54
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4728);  // "brp_seq.c"
        a1 = 176;
        jal(ctx, 0x274D60u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00274d68 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lw(v0, gp, kGpBrpSeq);  // 0x7CE3C0
    lw(v1, v0, kBsIndex);
    lw(v0, v0, kBsCount);
    v0 = slt(v1, v0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00274D90 sub_274D90 -- 124 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [brpSeq_EntryId] brp_seq.c: asserts index < count (line 1502); $v0 = the u16 id of entry index (+452 + 8i).
void sub_274D90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00274d90
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBrpSeq);  // 0x7CE3C0
    if (v0 == 0) {
        // 0x00274da8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4728);  // "brp_seq.c"
        a1 = 176;
        jal(ctx, 0x274DB4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00274dbc
    charge(ctx, 6);
    lw(s0, gp, kGpBrpSeq);  // 0x7CE3C0
    lw(v1, s0, kBsIndex);
    lw(v0, s0, kBsCount);
    v0 = slt(v1, v0);
    if (v0 == 0) {
        // 0x00274dd4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4728);  // "brp_seq.c"
        a1 = 1502;
        jal(ctx, 0x274DE0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00274de8 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(v0, s0, kBsIndex);
    v0 = sll(v0, 3);
    v0 = addu(v0, s0);
    lhu(v0, v0, kBsEntries);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00274E10 sub_274E10 -- 124 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [brpSeq_EntryValue] brp_seq.c: asserts index < count (line 1510); $v0 = the word +456 + 8 * index.
void sub_274E10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00274e10
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBrpSeq);  // 0x7CE3C0
    if (v0 == 0) {
        // 0x00274e28
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4728);  // "brp_seq.c"
        a1 = 176;
        jal(ctx, 0x274E34u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00274e3c
    charge(ctx, 6);
    lw(s0, gp, kGpBrpSeq);  // 0x7CE3C0
    lw(v1, s0, kBsIndex);
    lw(v0, s0, kBsCount);
    v0 = slt(v1, v0);
    if (v0 == 0) {
        // 0x00274e54
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4728);  // "brp_seq.c"
        a1 = 1510;
        jal(ctx, 0x274E60u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00274e68 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(v0, s0, kBsIndex);
    v0 = sll(v0, 3);
    v0 = addu(v0, s0);
    lw(v0, v0, kBsEntries + 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00274E90 sub_274E90 -- 100 bytes; frame 0x10: ra sp+0x0
// [brpSeq_EntriesAfter] brp_seq.c: $v0 = count - index - 1, at least 0.
void sub_274E90(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00274e90
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBrpSeq);  // 0x7CE3C0
    if (v0 == 0) {
        // 0x00274ea4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4728);  // "brp_seq.c"
        a1 = 176;
        jal(ctx, 0x274EB0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00274eb8
    charge(ctx, 7);
    lw(v0, gp, kGpBrpSeq);  // 0x7CE3C0
    lw(v1, v0, kBsCount);
    lw(v0, v0, kBsIndex);
    v0 = subu(v1, v0);
    at = slti(v0, 2);
    if (at == 0) {
        // 0x00274ee0
        charge(ctx, 1);
        v0 = addiu(v0, -1);
    } else {
        // 0x00274ed4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00274ee4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00275A70 sub_275A70 -- 16 bytes; leaf frame (no stack)
// [brLvpnl_Register](work) br_lvpnl.c: +0 = 0, slot = work (no assert).
void sub_275A70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00275a70
    enter(ctx, 4);  // entry check point + this block's cycles
    sw(zero, a0, 0);
    sw(a0, gp, kGpBrLvpnl);  // 0x7CE3C8
}

// 0x002760F0 sub_2760F0 -- 1764 bytes; frame 0x70: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [brLvpnl_Layout] br_lvpnl.c: places the six quads (rects from the pages' sizes) and fades them: the two banner quads
// fade in over 6 frames (mode 0) or are opaque (mode 1); the two text quads fade in over 3 frames after a 3-frame delay
// (mode 0) and out over 30, alpha = 255 * t through the float -> u8 conversion of cvt.w.s with the 2^31 adjustment;
// the bar quads (page 11) are opaque at x 0 and 650.
void sub_2760F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x002760f0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(v0, gp, kGpBrLvpnl);  // 0x7CE3C8
    if (v0 == 0) {
        // 0x00276118
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4336);  // "br_lvpnl.c"
        a1 = 59;
        jal(ctx, 0x276124u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027612c
    charge(ctx, 9);
    lw(s0, gp, kGpBrLvpnl);  // 0x7CE3C8
    a0 = 0;
    jal(ctx, 0x276134u, gen::fn_sub_234630_00234630);
    s1 = v0;
    lw(v1, s0, kLvFlags);
    v0 = v1 & 0x2;
    if (v0 == 0) {
        // 0x00276200
        charge(ctx, 3);
        v0 = v1 & 0x4;
        if (v0 == 0) {
            // 0x0027621c
            charge(ctx, 1);
            mtc1(zero, f22);
        } else {
            // 0x0027620c
            charge(ctx, 4);
            v0 = 0x3F800000;
            mtc1(v0, f22);
        }
    } else {
        // 0x00276150
        charge(ctx, 4);
        lw(v1, s0, kLvMode);
        v0 = 1;
        if (v1 == v0) {
            // 0x002761f0
            charge(ctx, 4);
            v0 = 0x3F800000;
            mtc1(v0, f22);
        } else {
            // 0x00276160
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x00276170
                charge(ctx, 3);
                lw(v0, s0, kLvFrame);
                if (i64(v0) >= 0) {
                    // 0x00276190
                    charge(ctx, 3);
                    at = slti(v0, 6);
                    if (at == 0) {
                        // 0x002761dc
                        charge(ctx, 5);
                        v0 = 0x3F800000;
                        mtc1(v0, f22);
                        mtc1(zero, f21);
                    } else {
                        // 0x0027619c
                        charge(ctx, 16);
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                        v0 = 0x40C00000;
                        mtc1(v0, f0);
                        div_s(f22, f1, f0);
                        v0 = 0x42C80000;
                        mtc1(v0, f1);
                        v0 = 0x3F800000;
                        mtc1(v0, f0);
                        sub_s(f0, f0, f22);
                        mul_s(f21, f1, f0);
                    }
                } else {
                    // 0x0027617c
                    charge(ctx, 5);
                    mtc1(zero, f22);
                    mov_s(f21, f22);
                }
            } else {
                // 0x00276168
                charge(ctx, 2);
            }
        }
    }
    // 0x00276220
    charge(ctx, 34);
    a0 = s1;
    a1 = 0;
    jal(ctx, 0x276228u, gen::fn_sub_21CCA0_0021cca0);
    v1 = 0x43000000;
    mtc1(v1, f0);
    add_s(f0, f0, f21);
    swc1(f0, sp, 0x40);
    sw(zero, sp, 0x44);
    lwc1(f0, v0, 12);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x48);
    lwc1(f0, v0, 16);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x4C);
    a0 = addiu(s0, 16);
    a1 = addiu(sp, 0x40);
    jal(ctx, 0x276268u, gen::fn_sub_21D8E0_0021d8e0);
    v0 = 255;
    sb(v0, sp, 0x6C);
    sb(v0, sp, 0x6D);
    sb(v0, sp, 0x6E);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f20, f0, f22);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f20);
    if (cond(ctx)) {
        // 0x002762c0
        charge(ctx, 6);
        sub_s(f0, f20, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x002762a8
        charge(ctx, 6);
        cvt_w_s(f0, f20);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x002762d8
    charge(ctx, 36);
    sb(v1, sp, 0x6F);
    a0 = addiu(s0, 16);
    a1 = addiu(sp, 0x6C);
    jal(ctx, 0x2762E4u, gen::fn_sub_21D950_0021d950);
    a0 = s1;
    a1 = 1;
    jal(ctx, 0x2762F4u, gen::fn_sub_21CCA0_0021cca0);
    v1 = 359;
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    add_s(f0, f0, f21);
    swc1(f0, sp, 0x40);
    sw(zero, sp, 0x44);
    lwc1(f0, v0, 12);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x48);
    lwc1(f0, v0, 16);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x4C);
    a0 = addiu(s0, 528);
    a1 = addiu(sp, 0x40);
    jal(ctx, 0x276338u, gen::fn_sub_21D8E0_0021d8e0);
    v0 = 255;
    sb(v0, sp, 0x6C);
    sb(v0, sp, 0x6D);
    sb(v0, sp, 0x6E);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f20);
    if (cond(ctx)) {
        // 0x00276380
        charge(ctx, 6);
        sub_s(f0, f20, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x00276368
        charge(ctx, 6);
        cvt_w_s(f0, f20);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x00276398
    charge(ctx, 9);
    sb(v1, sp, 0x6F);
    a0 = addiu(s0, 528);
    a1 = addiu(sp, 0x6C);
    jal(ctx, 0x2763A4u, gen::fn_sub_21D950_0021d950);
    lw(v0, s0, kLvFlags);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // 0x00276564
        charge(ctx, 1);
        mtc1(zero, f22);
    } else {
        // 0x002763bc
        charge(ctx, 4);
        lw(v1, s0, kLvMode);
        v0 = 1;
        if (v1 == v0) {
            // 0x002764a4
            charge(ctx, 3);
            lw(v0, s0, kLvFrame);
            if (i64(v0) >= 0) {
                // 0x002764bc
                charge(ctx, 3);
                at = slti(v0, 3);
                if (at == 0) {
                    // 0x002764f8
                    charge(ctx, 3);
                    at = slti(v0, 3);
                    if (at == 0) {
                        // 0x00276514
                        charge(ctx, 3);
                        at = slti(v0, 33);
                        if (at == 0) {
                            // 0x00276558
                            charge(ctx, 3);
                            mtc1(zero, f22);
                        } else {
                            // 0x00276520
                            charge(ctx, 14);
                            v0 = addiu(v0, -3);
                            mtc1(v0, f0);
                            cvt_s_w(f1, f0);
                            v0 = 0x41F00000;
                            mtc1(v0, f0);
                            div_s(f1, f1, f0);
                            v0 = 0x3F800000;
                            mtc1(v0, f0);
                            sub_s(f22, f0, f1);
                        }
                    } else {
                        // 0x00276504
                        charge(ctx, 4);
                        v0 = 0x3F800000;
                        mtc1(v0, f22);
                    }
                } else {
                    // 0x002764c8
                    charge(ctx, 12);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x40400000;
                    mtc1(v0, f0);
                    div_s(f22, f1, f0);
                }
            } else {
                // 0x002764b0
                charge(ctx, 3);
                mtc1(zero, f22);
            }
        } else {
            // 0x002763cc
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x002763dc
                charge(ctx, 4);
                lw(v0, s0, kLvFrame);
                at = slti(v0, 3);
                if (at == 0) {
                    // 0x002763f8
                    charge(ctx, 3);
                    at = slti(v0, 6);
                    if (at == 0) {
                        // 0x00276438
                        charge(ctx, 3);
                        at = slti(v0, 6);
                        if (at == 0) {
                            // 0x00276454
                            charge(ctx, 3);
                            at = slti(v0, 36);
                            if (at == 0) {
                                // 0x00276498
                                charge(ctx, 3);
                                mtc1(zero, f22);
                            } else {
                                // 0x00276460
                                charge(ctx, 14);
                                v0 = addiu(v0, -6);
                                mtc1(v0, f0);
                                cvt_s_w(f1, f0);
                                v0 = 0x41F00000;
                                mtc1(v0, f0);
                                div_s(f1, f1, f0);
                                v0 = 0x3F800000;
                                mtc1(v0, f0);
                                sub_s(f22, f0, f1);
                            }
                        } else {
                            // 0x00276444
                            charge(ctx, 4);
                            v0 = 0x3F800000;
                            mtc1(v0, f22);
                        }
                    } else {
                        // 0x00276404
                        charge(ctx, 13);
                        v0 = addiu(v0, -3);
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                        v0 = 0x40400000;
                        mtc1(v0, f0);
                        div_s(f22, f1, f0);
                    }
                } else {
                    // 0x002763ec
                    charge(ctx, 3);
                    mtc1(zero, f22);
                }
            } else {
                // 0x002763d4
                charge(ctx, 2);
            }
        }
    }
    // 0x00276568
    charge(ctx, 31);
    a0 = s1;
    a1 = 2;
    jal(ctx, 0x276570u, gen::fn_sub_21CCA0_0021cca0);
    v1 = 0x43000000;
    sw(v1, sp, 0x40);
    sw(zero, sp, 0x44);
    lwc1(f0, v0, 12);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x48);
    lwc1(f0, v0, 16);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x4C);
    a0 = addiu(s0, 272);
    a1 = addiu(sp, 0x40);
    jal(ctx, 0x2765A4u, gen::fn_sub_21D8E0_0021d8e0);
    v0 = 255;
    sb(v0, sp, 0x6C);
    sb(v0, sp, 0x6D);
    sb(v0, sp, 0x6E);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f20, f0, f22);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f20);
    if (cond(ctx)) {
        // 0x002765fc
        charge(ctx, 6);
        sub_s(f0, f20, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x002765e4
        charge(ctx, 6);
        cvt_w_s(f0, f20);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x00276614
    charge(ctx, 35);
    sb(v1, sp, 0x6F);
    a0 = addiu(s0, 272);
    a1 = addiu(sp, 0x6C);
    jal(ctx, 0x276620u, gen::fn_sub_21D950_0021d950);
    a0 = s1;
    a1 = 3;
    jal(ctx, 0x276630u, gen::fn_sub_21CCA0_0021cca0);
    v1 = 359;
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x40);
    sw(zero, sp, 0x44);
    lwc1(f0, v0, 12);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x48);
    lwc1(f0, v0, 16);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x4C);
    a0 = addiu(s0, 784);
    a1 = addiu(sp, 0x40);
    jal(ctx, 0x276670u, gen::fn_sub_21D8E0_0021d8e0);
    v0 = 255;
    sb(v0, sp, 0x6C);
    sb(v0, sp, 0x6D);
    sb(v0, sp, 0x6E);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f20);
    if (cond(ctx)) {
        // 0x002766b8
        charge(ctx, 6);
        sub_s(f0, f20, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x002766a0
        charge(ctx, 6);
        cvt_w_s(f0, f20);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x002766d0
    charge(ctx, 65);
    sb(v1, sp, 0x6F);
    a0 = addiu(s0, 784);
    a1 = addiu(sp, 0x6C);
    jal(ctx, 0x2766DCu, gen::fn_sub_21D950_0021d950);
    a0 = s1;
    a1 = 11;
    jal(ctx, 0x2766ECu, gen::fn_sub_21CCA0_0021cca0);
    s1 = v0;
    sw(zero, sp, 0x40);
    sw(zero, sp, 0x44);
    lwc1(f0, v0, 12);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x48);
    lwc1(f0, v0, 16);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x4C);
    a0 = addiu(s0, 1040);
    a1 = addiu(sp, 0x40);
    jal(ctx, 0x276720u, gen::fn_sub_21D8E0_0021d8e0);
    lwc1(f0, s1, 12);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x40);
    sw(zero, sp, 0x44);
    v0 = 650;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x48);
    lwc1(f0, s1, 16);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x4C);
    a0 = addiu(s0, 1296);
    a1 = addiu(sp, 0x40);
    jal(ctx, 0x276760u, gen::fn_sub_21D8E0_0021d8e0);
    v0 = 255;
    sb(v0, sp, 0x6C);
    sb(v0, sp, 0x6D);
    sb(v0, sp, 0x6E);
    sb(v0, sp, 0x6F);
    a0 = addiu(s0, 1040);
    a1 = addiu(sp, 0x6C);
    jal(ctx, 0x276784u, gen::fn_sub_21D950_0021d950);
    v0 = 255;
    sb(v0, sp, 0x6C);
    sb(v0, sp, 0x6D);
    sb(v0, sp, 0x6E);
    sb(v0, sp, 0x6F);
    a0 = addiu(s0, 1296);
    a1 = addiu(sp, 0x6C);
    jal(ctx, 0x2767A8u, gen::fn_sub_21D950_0021d950);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00276870 sub_276870 -- 72 bytes; frame 0x10: ra sp+0x0
// [brLvpnl_SetFlag8] br_lvpnl.c: asserts the work (line 59), flags |= 8.
void sub_276870(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00276870
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBrLvpnl);  // 0x7CE3C8
    if (v1 == 0) {
        // 0x00276884
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4336);  // "br_lvpnl.c"
        a1 = 59;
        jal(ctx, 0x276890u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00276898 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lw(a0, gp, kGpBrLvpnl);  // 0x7CE3C8
    lw(v1, a0, kLvFlags);
    v1 = v1 | 0x8;
    sw(v1, a0, kLvFlags);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00276910 sub_276910 -- 16 bytes; leaf frame (no stack)
// [brpPersona_Register](work) brp_persona.c: +0 = 0, slot = work (no assert).
void sub_276910(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00276910
    enter(ctx, 4);  // entry check point + this block's cycles
    sw(zero, a0, 0);
    sw(a0, gp, kGpBrpPersona);  // 0x7CE3CC
}

// 0x00276CC0 sub_276CC0 -- 68 bytes; frame 0x10: ra sp+0x0
// [brpPersona_Flag8] brp_persona.c: asserts the work (line 37), $v0 = flags & 8.
void sub_276CC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00276cc0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBrpPersona);  // 0x7CE3CC
    if (v0 == 0) {
        // 0x00276cd4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4320);  // "brp_persona.c"
        a1 = 37;
        jal(ctx, 0x276CE0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00276ce8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpBrpPersona);  // 0x7CE3CC
    lw(v0, v0, 0);
    v0 = v0 & 0x8;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00276D10 sub_276D10 -- 28 bytes; leaf frame (no stack)
// [brpParam_Register](work) brp_param.c: +0 = 0, +14128 / +14132 / +14136 = 0, slot = work (no assert).
void sub_276D10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00276d10
    enter(ctx, 7);  // entry check point + this block's cycles
    sw(zero, a0, 0);
    sw(zero, a0, 14128);
    sw(zero, a0, 14132);
    sw(zero, a0, 14136);
    sw(a0, gp, kGpBrpParam);  // 0x7CE3D0
}

// 0x00279450 sub_279450 -- 100 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [brpParam_SetNumber](n) brp_param.c: asserts the work (line 97); +14132 = n; n as 2 digits into +14160
// (bpIfontDrawNumber(.., 2, n, 2)).
void sub_279450(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00279450
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, gp, kGpBrpParam);  // 0x7CE3D0
    if (v0 == 0) {
        // 0x0027946c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4304);  // "brp_param.c"
        a1 = 97;
        jal(ctx, 0x279478u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00279480
    charge(ctx, 13);
    lw(v0, gp, kGpBrpParam);  // 0x7CE3D0
    sw(s0, v0, kBpNumber);
    a0 = addiu(v0, kBpDigits);
    a1 = 2;
    a2 = s0;
    a3 = a1;
    jal(ctx, 0x279498u, gen::fn_bpIfontDrawNumber_00238980);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002794C0 sub_2794C0 -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [brpParam_SetValue](v) brp_param.c: asserts the work (line 97), +14128 = v.
void sub_2794C0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002794c0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, gp, kGpBrpParam);  // 0x7CE3D0
    if (v1 == 0) {
        // 0x002794dc
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4304);  // "brp_param.c"
        a1 = 97;
        jal(ctx, 0x2794E8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002794f0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v1, gp, kGpBrpParam);  // 0x7CE3D0
    sw(s0, v1, kBpValue);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00279510 sub_279510 -- 112 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [brpParam_SetMemberA](member, v) brp_param.c: asserts the work (line 97), +2192 + 1824 * member = v.
void sub_279510(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00279510
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v1, gp, kGpBrpParam);  // 0x7CE3D0
    if (v1 == 0) {
        // 0x00279534
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4304);  // "brp_param.c"
        a1 = 97;
        jal(ctx, 0x279540u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00279548 (the shared epilogue, written out on this path)
    charge(ctx, 14);
    lw(a0, gp, kGpBrpParam);  // 0x7CE3D0
    v1 = sll(s1, 3);
    v1 = subu(v1, s1);
    v1 = sll(v1, 3);
    v1 = addu(v1, s1);
    v1 = sll(v1, 5);
    v1 = addu(v1, a0);
    sw(s0, v1, kBpMemA);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00279580 sub_279580 -- 112 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [brpParam_SetMemberB](member, v) brp_param.c: +2720 + 1824 * member = v.
void sub_279580(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00279580
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v1, gp, kGpBrpParam);  // 0x7CE3D0
    if (v1 == 0) {
        // 0x002795a4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4304);  // "brp_param.c"
        a1 = 97;
        jal(ctx, 0x2795B0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002795b8 (the shared epilogue, written out on this path)
    charge(ctx, 14);
    lw(a0, gp, kGpBrpParam);  // 0x7CE3D0
    v1 = sll(s1, 3);
    v1 = subu(v1, s1);
    v1 = sll(v1, 3);
    v1 = addu(v1, s1);
    v1 = sll(v1, 5);
    v1 = addu(v1, a0);
    sw(s0, v1, kBpMemB);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002795F0 sub_2795F0 -- 112 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [brpParam_SetMemberC](member, v) brp_param.c: +2724 + 1824 * member = v.
void sub_2795F0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002795f0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v1, gp, kGpBrpParam);  // 0x7CE3D0
    if (v1 == 0) {
        // 0x00279614
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4304);  // "brp_param.c"
        a1 = 97;
        jal(ctx, 0x279620u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00279628 (the shared epilogue, written out on this path)
    charge(ctx, 14);
    lw(a0, gp, kGpBrpParam);  // 0x7CE3D0
    v1 = sll(s1, 3);
    v1 = subu(v1, s1);
    v1 = sll(v1, 3);
    v1 = addu(v1, s1);
    v1 = sll(v1, 5);
    v1 = addu(v1, a0);
    sw(s0, v1, kBpMemC);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002796B0 sub_2796B0 -- 76 bytes; frame 0x10: ra sp+0x0
// [brpParam_StartA] brp_param.c: asserts the work (line 97); +14140 = 0; flags |= 4.
void sub_2796B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002796b0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBrpParam);  // 0x7CE3D0
    if (v1 == 0) {
        // 0x002796c4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4304);  // "brp_param.c"
        a1 = 97;
        jal(ctx, 0x2796D0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002796d8 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(a0, gp, kGpBrpParam);  // 0x7CE3D0
    sw(zero, a0, kBpTimerA);
    lw(v1, a0, kBpFlags);
    v1 = v1 | 0x4;
    sw(v1, a0, kBpFlags);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00279700 sub_279700 -- 68 bytes; frame 0x10: ra sp+0x0
// [brpParam_IsA] brp_param.c: asserts the work (line 97), $v0 = flags & 4.
void sub_279700(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00279700
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBrpParam);  // 0x7CE3D0
    if (v0 == 0) {
        // 0x00279714
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4304);  // "brp_param.c"
        a1 = 97;
        jal(ctx, 0x279720u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00279728 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpBrpParam);  // 0x7CE3D0
    lw(v0, v0, kBpFlags);
    v0 = v0 & 0x4;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00279750 sub_279750 -- 76 bytes; frame 0x10: ra sp+0x0
// [brpParam_StartB] brp_param.c: asserts the work (line 97); +14148 = 0; flags |= 0x10.
void sub_279750(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00279750
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBrpParam);  // 0x7CE3D0
    if (v1 == 0) {
        // 0x00279764
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4304);  // "brp_param.c"
        a1 = 97;
        jal(ctx, 0x279770u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00279778 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(a0, gp, kGpBrpParam);  // 0x7CE3D0
    sw(zero, a0, kBpTimerB);
    lw(v1, a0, kBpFlags);
    v1 = v1 | 0x10;
    sw(v1, a0, kBpFlags);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002797A0 sub_2797A0 -- 68 bytes; frame 0x10: ra sp+0x0
// [brpParam_IsB] brp_param.c: asserts the work (line 97), $v0 = flags & 0x10.
void sub_2797A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002797a0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBrpParam);  // 0x7CE3D0
    if (v0 == 0) {
        // 0x002797b4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4304);  // "brp_param.c"
        a1 = 97;
        jal(ctx, 0x2797C0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002797c8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, gp, kGpBrpParam);  // 0x7CE3D0
    lw(v0, v0, kBpFlags);
    v0 = v0 & 0x10;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002797F0 sub_2797F0 -- 72 bytes; frame 0x10: ra sp+0x0
// [brpParam_SetFlag20] brp_param.c: asserts the work (line 97), flags |= 0x20.
void sub_2797F0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002797f0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBrpParam);  // 0x7CE3D0
    if (v1 == 0) {
        // 0x00279804
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4304);  // "brp_param.c"
        a1 = 97;
        jal(ctx, 0x279810u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00279818 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lw(a0, gp, kGpBrpParam);  // 0x7CE3D0
    lw(v1, a0, kBpFlags);
    v1 = v1 | 0x20;
    sw(v1, a0, kBpFlags);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00279840 sub_279840 -- 76 bytes; frame 0x10: ra sp+0x0
// [brpParam_ClearFlag20] brp_param.c: asserts the work (line 97), flags &= ~0x20.
void sub_279840(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00279840
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBrpParam);  // 0x7CE3D0
    if (v1 == 0) {
        // 0x00279854
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4304);  // "brp_param.c"
        a1 = 97;
        jal(ctx, 0x279860u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00279868 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(a1, gp, kGpBrpParam);  // 0x7CE3D0
    lw(a0, a1, kBpFlags);
    v1 = si(-33);
    v1 = a0 & v1;
    sw(v1, a1, kBpFlags);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00279890 sub_279890 -- 92 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [brpParam_SetPair](a, b) brp_param.c: asserts the work (line 97); +15200 = a, +15204 = b.
void sub_279890(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00279890
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v1, gp, kGpBrpParam);  // 0x7CE3D0
    if (v1 == 0) {
        // 0x002798b4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4304);  // "brp_param.c"
        a1 = 97;
        jal(ctx, 0x2798C0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002798c8 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lw(v1, gp, kGpBrpParam);  // 0x7CE3D0
    sw(s1, v1, kBpPairA);
    sw(s0, v1, kBpPairB);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002798F0 sub_2798F0 -- 72 bytes; frame 0x10: ra sp+0x0
// [brpParam_SetFlag40] brp_param.c: asserts the work (line 97), flags |= 0x40.
void sub_2798F0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002798f0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBrpParam);  // 0x7CE3D0
    if (v1 == 0) {
        // 0x00279904
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4304);  // "brp_param.c"
        a1 = 97;
        jal(ctx, 0x279910u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00279918 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lw(a0, gp, kGpBrpParam);  // 0x7CE3D0
    lw(v1, a0, kBpFlags);
    v1 = v1 | 0x40;
    sw(v1, a0, kBpFlags);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0027B6C0 sub_27B6C0 -- 444 bytes; frame 0x50: ra sp+0x10, s0 sp+0x0 (sq)
// [bpSelect_Layout] bp_select.c: page 58 of panel set 2 at (+276, +280) with the page's size; alpha 255 * (1 - f / 20)
// when closing, 255 * f / 20 when opening (1.0 / 0.0 from frame 20 on).
void sub_27B6C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x0027b6c0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBpSelect);  // 0x7CE3E4
    if (v0 == 0) {
        // 0x0027b6d8
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4152);  // "bp_select.c"
        a1 = 39;
        jal(ctx, 0x27B6E4u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027b6ec
    charge(ctx, 26);
    lw(s0, gp, kGpBpSelect);  // 0x7CE3E4
    a0 = 2;
    jal(ctx, 0x27B6F4u, gen::fn_sub_21C3F0_0021c3f0);
    a0 = v0;
    a1 = 58;
    jal(ctx, 0x27B704u, gen::fn_sub_21CCA0_0021cca0);
    lwc1(f0, s0, kSelX);
    swc1(f0, sp, 0x20);
    lwc1(f0, s0, kSelY);
    swc1(f0, sp, 0x24);
    lwc1(f0, v0, 12);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x28);
    lwc1(f0, v0, 16);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x2C);
    a0 = addiu(s0, kSelQuad);
    a1 = addiu(sp, 0x20);
    jal(ctx, 0x27B73Cu, gen::fn_sub_21D8E0_0021d8e0);
    lw(v0, s0, kSelFlags);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // 0x0027b7a4
        charge(ctx, 4);
        lw(v0, s0, kSelFrame);
        at = slti(v0, 20);
        if (at == 0) {
            // 0x0027b7e4
            charge(ctx, 2);
            v0 = 0x3F800000;
            mtc1(v0, f1);
        } else {
            // 0x0027b7b4
            charge(ctx, 12);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x41A00000;
            mtc1(v0, f0);
            div_s(f1, f1, f0);
        }
    } else {
        // 0x0027b754
        charge(ctx, 4);
        lw(v0, s0, kSelFrame);
        at = slti(v0, 20);
        if (at == 0) {
            // 0x0027b798
            charge(ctx, 3);
            mtc1(zero, f1);
        } else {
            // 0x0027b764
            charge(ctx, 13);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x41A00000;
            mtc1(v0, f0);
            div_s(f1, f1, f0);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            sub_s(f1, f0, f1);
        }
    }
    // 0x0027b7ec
    charge(ctx, 14);
    v0 = 255;
    sb(v0, sp, 0x4C);
    sb(v0, sp, 0x4D);
    sb(v0, sp, 0x4E);
    v0 = 0x437F0000;
    mtc1(v0, f0);
    mul_s(f1, f0, f1);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x0027b83c
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFF;
    } else {
        // 0x0027b824
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFF;
    }
    // 0x0027b854
    charge(ctx, 10);
    sb(v1, sp, 0x4F);
    a0 = addiu(s0, kSelQuad);
    a1 = addiu(sp, 0x4C);
    jal(ctx, 0x27B860u, gen::fn_sub_21D950_0021d950);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0027BB50 sub_27BB50 -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [sflPersona_Register](work) sfl_persona.c: asserts the slot is empty (line 48), +0 = 0, slot = work.
void sub_27BB50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027bb50
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, gp, kGpSflPersona);  // 0x7CE3E8
    if (v1 != 0) {
        // 0x0027bb6c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4136);  // "sfl_persona.c"
        a1 = 48;
        jal(ctx, 0x27BB78u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027bb80 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    sw(zero, s0, 0);
    sw(s0, gp, kGpSflPersona);  // 0x7CE3E8
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002C1CE0 sub_2C1CE0 -- 152 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlCommand_CheckUsable](cmd) (the command calc of battle_fx.h's lists): $v0 = 0 when the btlUnit at cmd+48's
// DatUnit (+2604) has a bad status of the mask 0x80271 (datCalcChkBadStatus); else 1 when cmd's u16 +24 bit 7 is
// clear and the encounter (gEncountTbl, 28-byte records, by the u16 +8 of gBtl's setup +3004) has bit 0 set.
void sub_2C1CE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c1ce0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, a0, 48);
    lw(a0, v0, 2604);
    v0 = 0x80000;
    a1 = v0 | 0x271;
    jal(ctx, 0x2C1D00u, gen::fn_datCalcChkBadStatus_00300580);
    if (v0 == 0) {
        // 0x002c1d1c
        charge(ctx, 4);
        lhu(v0, s0, 24);
        v0 = v0 & 0x80;
        if (v0 == 0) {
            // 0x002c1d38
            charge(ctx, 11);
            lw(v0, gp, kGpBtl);  // 0x7CE3EC
            lw(v0, v0, 3004);
            lhu(v1, v0, 8);
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, gp, kGpEncountTbl);  // gEncountTbl
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            v0 = v0 & 0x1;
            v0 = sltu(0, v0);
        } else {
            // 0x002c1d2c
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x002c1d10
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x002c1d64 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001F5810 sub_1F5810 -- 212 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [sflRoot_IsIdle](task) sfl_root.c: asserts the root work (line 254); $v0 = 1 when the task work (+60)'s +4 has no
// 0x80, the root's +8 is not 1 and sflRes flag 1, sub_254F20(), sflRes flag 4 and flag 0x10 are all 0 (tested in
// that order; the first non-zero one returns 0).
void sub_1F5810(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001f5810
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, gp, kGpSflRoot);  // 0x7CE2DC
    if (v0 == 0) {
        // 0x001f582c
        charge(ctx, 5);
        a0 = 0x680000;
        a0 = addiu(a0, 17952);  // "sfl_root.c"
        a1 = 254;
        jal(ctx, 0x1F5838u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x001f5840
    charge(ctx, 6);
    lw(v1, gp, kGpSflRoot);  // 0x7CE2DC
    lw(v0, s0, 60);
    lw(v0, v0, 4);
    v0 = v0 & 0x80;
    if (v0 == 0) {
        // 0x001f5864
        charge(ctx, 4);
        lw(v1, v1, 8);
        v0 = 1;
        if (v1 != v0) {
            // 0x001f5880
            charge(ctx, 4);
            jal(ctx, 0x1F5880u, gen::fn_sub_20DFE0_0020dfe0);  // sflRes flag 1
            // the busy tests in order; the first non-zero one ends at "not idle" (0x1f58c0)
            if (v0 == 0) {
                // 0x001f5890
                charge(ctx, 4);
                jal(ctx, 0x1F5890u, gen::fn_sub_254F20_00254f20);
            }
            if (v0 == 0) {
                // 0x001f58a0
                charge(ctx, 4);
                jal(ctx, 0x1F58A0u, gen::fn_sub_20E4C0_0020e4c0);  // sflRes flag 4
            }
            if (v0 == 0) {
                // 0x001f58b0
                charge(ctx, 4);
                jal(ctx, 0x1F58B0u, gen::fn_sub_20EC00_0020ec00);  // sflRes flag 0x10
            }
            if (v0 == 0) {
                // 0x001f58cc: idle
                charge(ctx, 1);
                v0 = 1;
                // 0x001f58d0 (the shared epilogue, written out on this path)
                charge(ctx, 5);
                ld(ra, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x20);
                return;
            }
            // 0x001f58c0: not idle
            charge(ctx, 3);
            v0 = 0;
        } else {
            // 0x001f5874
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x001f5858
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001f58d0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00209C00 sub_209C00 -- 64 bytes; frame 0x10: ra sp+0x0
// Panel set 1's page 46 (sub_21C3F0(1), sub_21CCA0) handed to sub_21CCE0; $v0 is its result (a tail call).
void sub_209C00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00209c00
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 1;
    jal(ctx, 0x209C0Cu, gen::fn_sub_21C3F0_0021c3f0);
    a0 = v0;
    a1 = 46;
    jal(ctx, 0x209C1Cu, gen::fn_sub_21CCA0_0021cca0);
    a0 = v0;
    jal(ctx, 0x209C28u, gen::fn_sub_21CCE0_0021cce0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00209F00 sub_209F00 -- 2292 bytes; frame 0x260: ra sp+0x10, s0 sp+0x0 (sq)
// [gcModel_Init0](model) gc_model.c: sub_209EA0, kind (+4) = 0, the quad at +224 (sub_20C7B0), +368 = 0, then the
// card's other quads written out: positions from the f32 constants 0x7CB010 / 0x7CB014 (half width / height) and
// 0x7CB008 / 0x7CB00C (+-3.84), 36-byte vertices { xyz, RGBA, uv }, the uv corners as float bit patterns.
void sub_209F00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8};
    // 0x00209f00
    enter(ctx, 573);  // entry check point + this block's cycles
    sp = addiu(sp, -0x260);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x209F10u, gen::fn_sub_209EA0_00209ea0);
    sw(zero, s0, kGcmKind);
    a0 = addiu(s0, kGcmQuad0);
    jal(ctx, 0x209F20u, gen::fn_sub_20C7B0_0020c7b0);
    sw(zero, s0, kGcmParamA);
    lwc1(f5, gp, kGpCardHalfW);  // 0x7CB010
    swc1(f5, sp, 0x250);
    lwc1(f4, gp, kGpCardHalfH2);  // 0x7CB014
    swc1(f4, sp, 0x254);
    sw(zero, sp, 0x258);
    lwc1(f2, sp, 0x250);
    lwc1(f1, sp, 0x254);
    lwc1(f0, sp, 0x258);
    swc1(f2, s0, 376);
    swc1(f1, s0, 380);
    swc1(f0, s0, 384);
    neg_s(f3, f5);
    swc1(f3, sp, 0x240);
    swc1(f4, sp, 0x244);
    sw(zero, sp, 0x248);
    lwc1(f2, sp, 0x240);
    lwc1(f1, sp, 0x244);
    lwc1(f0, sp, 0x248);
    swc1(f2, s0, 412);
    swc1(f1, s0, 416);
    swc1(f0, s0, 420);
    swc1(f3, sp, 0x230);
    neg_s(f2, f4);
    swc1(f2, sp, 0x234);
    sw(zero, sp, 0x238);
    lwc1(f6, sp, 0x230);
    lwc1(f1, sp, 0x234);
    lwc1(f0, sp, 0x238);
    swc1(f6, s0, 448);
    swc1(f1, s0, 452);
    swc1(f0, s0, 456);
    swc1(f5, sp, 0x220);
    swc1(f2, sp, 0x224);
    sw(zero, sp, 0x228);
    lwc1(f6, sp, 0x220);
    lwc1(f1, sp, 0x224);
    lwc1(f0, sp, 0x228);
    swc1(f6, s0, 484);
    swc1(f1, s0, 488);
    swc1(f0, s0, 492);
    t3 = 255;
    sb(t3, s0, 388);
    sb(t3, s0, 389);
    sb(t3, s0, 390);
    sb(t3, s0, 391);
    sb(t3, s0, 424);
    sb(t3, s0, 425);
    sb(t3, s0, 426);
    sb(t3, s0, 427);
    sb(t3, s0, 460);
    sb(t3, s0, 461);
    sb(t3, s0, 462);
    sb(t3, s0, 463);
    sb(t3, s0, 496);
    sb(t3, s0, 497);
    sb(t3, s0, 498);
    sb(t3, s0, 499);
    t2 = 0x3F630000;
    sw(t2, s0, 404);
    t1 = 0x3DE80000;
    sw(t1, s0, 440);
    sw(t1, s0, 476);
    sw(t2, s0, 512);
    t0 = 0x3DB80000;
    sw(t0, s0, 408);
    sw(t0, s0, 444);
    a3 = 0x3F690000;
    sw(a3, s0, 480);
    sw(a3, s0, 516);
    a2 = 0x40400000;
    sw(a2, sp, 0x210);
    lwc1(f1, gp, kGpCardHalfH);  // 0x7CB008
    swc1(f1, sp, 0x214);
    sw(zero, sp, 0x218);
    lwc1(f7, sp, 0x210);
    lwc1(f6, sp, 0x214);
    lwc1(f0, sp, 0x218);
    swc1(f7, s0, 520);
    swc1(f6, s0, 524);
    swc1(f0, s0, 528);
    a1 = lui(0xC040);
    sw(a1, sp, 0x200);
    swc1(f1, sp, 0x204);
    sw(zero, sp, 0x208);
    lwc1(f7, sp, 0x200);
    lwc1(f6, sp, 0x204);
    lwc1(f0, sp, 0x208);
    swc1(f7, s0, 556);
    swc1(f6, s0, 560);
    swc1(f0, s0, 564);
    sw(a1, sp, 0x1F0);
    lwc1(f0, gp, kGpCardNegHalfH);  // 0x7CB00C
    swc1(f0, sp, 0x1F4);
    sw(zero, sp, 0x1F8);
    lwc1(f8, sp, 0x1F0);
    lwc1(f7, sp, 0x1F4);
    lwc1(f6, sp, 0x1F8);
    swc1(f8, s0, 592);
    swc1(f7, s0, 596);
    swc1(f6, s0, 600);
    sw(a2, sp, 0x1E0);
    swc1(f0, sp, 0x1E4);
    sw(zero, sp, 0x1E8);
    lwc1(f8, sp, 0x1E0);
    lwc1(f7, sp, 0x1E4);
    lwc1(f6, sp, 0x1E8);
    swc1(f8, s0, 628);
    swc1(f7, s0, 632);
    swc1(f6, s0, 636);
    sb(t3, s0, 532);
    sb(t3, s0, 533);
    sb(t3, s0, 534);
    sb(t3, s0, 535);
    sb(t3, s0, 568);
    sb(t3, s0, 569);
    sb(t3, s0, 570);
    sb(t3, s0, 571);
    sb(t3, s0, 604);
    sb(t3, s0, 605);
    sb(t3, s0, 606);
    sb(t3, s0, 607);
    sb(t3, s0, 640);
    sb(t3, s0, 641);
    sb(t3, s0, 642);
    sb(t3, s0, 643);
    a0 = 0x3F800000;
    sw(a0, s0, 548);
    sw(zero, s0, 584);
    sw(zero, s0, 620);
    sw(a0, s0, 656);
    sw(zero, s0, 552);
    sw(zero, s0, 588);
    sw(a0, s0, 624);
    sw(a0, s0, 660);
    swc1(f5, sp, 0x1D0);
    swc1(f4, sp, 0x1D4);
    sw(zero, sp, 0x1D8);
    lwc1(f8, sp, 0x1D0);
    lwc1(f7, sp, 0x1D4);
    lwc1(f6, sp, 0x1D8);
    swc1(f8, s0, 664);
    swc1(f7, s0, 668);
    swc1(f6, s0, 672);
    swc1(f3, sp, 0x1C0);
    swc1(f4, sp, 0x1C4);
    sw(zero, sp, 0x1C8);
    lwc1(f8, sp, 0x1C0);
    lwc1(f7, sp, 0x1C4);
    lwc1(f6, sp, 0x1C8);
    swc1(f8, s0, 700);
    swc1(f7, s0, 704);
    swc1(f6, s0, 708);
    swc1(f3, sp, 0x1B0);
    swc1(f2, sp, 0x1B4);
    sw(zero, sp, 0x1B8);
    lwc1(f8, sp, 0x1B0);
    lwc1(f7, sp, 0x1B4);
    lwc1(f6, sp, 0x1B8);
    swc1(f8, s0, 736);
    swc1(f7, s0, 740);
    swc1(f6, s0, 744);
    swc1(f5, sp, 0x1A0);
    swc1(f2, sp, 0x1A4);
    sw(zero, sp, 0x1A8);
    lwc1(f8, sp, 0x1A0);
    lwc1(f7, sp, 0x1A4);
    lwc1(f6, sp, 0x1A8);
    swc1(f8, s0, 772);
    swc1(f7, s0, 776);
    swc1(f6, s0, 780);
    sb(t3, s0, 676);
    sb(t3, s0, 677);
    sb(t3, s0, 678);
    v1 = 127;
    sb(v1, s0, 679);
    sb(t3, s0, 712);
    sb(t3, s0, 713);
    sb(t3, s0, 714);
    sb(v1, s0, 715);
    sb(t3, s0, 748);
    sb(t3, s0, 749);
    sb(t3, s0, 750);
    sb(v1, s0, 751);
    sb(t3, s0, 784);
    sb(t3, s0, 785);
    sb(t3, s0, 786);
    sb(v1, s0, 787);
    sw(a0, s0, 692);
    sw(zero, s0, 728);
    sw(zero, s0, 764);
    sw(a0, s0, 800);
    sw(zero, s0, 696);
    sw(zero, s0, 732);
    sw(a0, s0, 768);
    sw(a0, s0, 804);
    swc1(f5, sp, 0x190);
    swc1(f4, sp, 0x194);
    sw(zero, sp, 0x198);
    lwc1(f8, sp, 0x190);
    lwc1(f7, sp, 0x194);
    lwc1(f6, sp, 0x198);
    swc1(f8, s0, 808);
    swc1(f7, s0, 812);
    swc1(f6, s0, 816);
    swc1(f3, sp, 0x180);
    swc1(f4, sp, 0x184);
    sw(zero, sp, 0x188);
    lwc1(f8, sp, 0x180);
    lwc1(f7, sp, 0x184);
    lwc1(f6, sp, 0x188);
    swc1(f8, s0, 844);
    swc1(f7, s0, 848);
    swc1(f6, s0, 852);
    swc1(f3, sp, 0x170);
    swc1(f2, sp, 0x174);
    sw(zero, sp, 0x178);
    lwc1(f8, sp, 0x170);
    lwc1(f7, sp, 0x174);
    lwc1(f6, sp, 0x178);
    swc1(f8, s0, 880);
    swc1(f7, s0, 884);
    swc1(f6, s0, 888);
    swc1(f5, sp, 0x160);
    swc1(f2, sp, 0x164);
    sw(zero, sp, 0x168);
    lwc1(f8, sp, 0x160);
    lwc1(f7, sp, 0x164);
    lwc1(f6, sp, 0x168);
    swc1(f8, s0, 916);
    swc1(f7, s0, 920);
    swc1(f6, s0, 924);
    sb(t3, s0, 820);
    sb(t3, s0, 821);
    sb(t3, s0, 822);
    sb(v1, s0, 823);
    sb(t3, s0, 856);
    sb(t3, s0, 857);
    sb(t3, s0, 858);
    sb(v1, s0, 859);
    sb(t3, s0, 892);
    sb(t3, s0, 893);
    sb(t3, s0, 894);
    sb(v1, s0, 895);
    sb(t3, s0, 928);
    sb(t3, s0, 929);
    sb(t3, s0, 930);
    sb(v1, s0, 931);
    sw(a0, s0, 836);
    sw(zero, s0, 872);
    sw(zero, s0, 908);
    sw(a0, s0, 944);
    sw(zero, s0, 840);
    sw(zero, s0, 876);
    sw(a0, s0, 912);
    sw(a0, s0, 948);
    sw(a2, sp, 0x150);
    swc1(f1, sp, 0x154);
    sw(zero, sp, 0x158);
    lwc1(f8, sp, 0x150);
    lwc1(f7, sp, 0x154);
    lwc1(f6, sp, 0x158);
    swc1(f8, s0, 952);
    swc1(f7, s0, 956);
    swc1(f6, s0, 960);
    sw(a1, sp, 0x140);
    swc1(f1, sp, 0x144);
    sw(zero, sp, 0x148);
    lwc1(f8, sp, 0x140);
    lwc1(f7, sp, 0x144);
    lwc1(f6, sp, 0x148);
    swc1(f8, s0, 988);
    swc1(f7, s0, 992);
    swc1(f6, s0, 996);
    sw(a1, sp, 0x130);
    swc1(f0, sp, 0x134);
    sw(zero, sp, 0x138);
    lwc1(f8, sp, 0x130);
    lwc1(f7, sp, 0x134);
    lwc1(f6, sp, 0x138);
    swc1(f8, s0, 1024);
    swc1(f7, s0, 1028);
    swc1(f6, s0, 1032);
    sw(a2, sp, 0x120);
    swc1(f0, sp, 0x124);
    sw(zero, sp, 0x128);
    lwc1(f8, sp, 0x120);
    lwc1(f7, sp, 0x124);
    lwc1(f6, sp, 0x128);
    swc1(f8, s0, 1060);
    swc1(f7, s0, 1064);
    swc1(f6, s0, 1068);
    sb(t3, s0, 964);
    sb(t3, s0, 965);
    sb(t3, s0, 966);
    v1 = 153;
    sb(v1, s0, 967);
    sb(t3, s0, 1000);
    sb(t3, s0, 1001);
    sb(t3, s0, 1002);
    sb(v1, s0, 1003);
    sb(t3, s0, 1036);
    sb(t3, s0, 1037);
    sb(t3, s0, 1038);
    sb(v1, s0, 1039);
    sb(t3, s0, 1072);
    sb(t3, s0, 1073);
    sb(t3, s0, 1074);
    sb(v1, s0, 1075);
    sw(a0, s0, 980);
    sw(zero, s0, 1016);
    sw(zero, s0, 1052);
    sw(a0, s0, 1088);
    sw(zero, s0, 984);
    sw(zero, s0, 1020);
    sw(a0, s0, 1056);
    sw(a0, s0, 1092);
    swc1(f5, sp, 0x110);
    swc1(f4, sp, 0x114);
    sw(zero, sp, 0x118);
    lwc1(f8, sp, 0x110);
    lwc1(f7, sp, 0x114);
    lwc1(f6, sp, 0x118);
    swc1(f8, s0, 1096);
    swc1(f7, s0, 1100);
    swc1(f6, s0, 1104);
    swc1(f3, sp, 0x100);
    swc1(f4, sp, 0x104);
    sw(zero, sp, 0x108);
    lwc1(f8, sp, 0x100);
    lwc1(f7, sp, 0x104);
    lwc1(f6, sp, 0x108);
    swc1(f8, s0, 1132);
    swc1(f7, s0, 1136);
    swc1(f6, s0, 1140);
    swc1(f3, sp, 0xF0);
    swc1(f2, sp, 0xF4);
    sw(zero, sp, 0xF8);
    lwc1(f8, sp, 0xF0);
    lwc1(f7, sp, 0xF4);
    lwc1(f6, sp, 0xF8);
    swc1(f8, s0, 1168);
    swc1(f7, s0, 1172);
    swc1(f6, s0, 1176);
    swc1(f5, sp, 0xE0);
    swc1(f2, sp, 0xE4);
    sw(zero, sp, 0xE8);
    lwc1(f8, sp, 0xE0);
    lwc1(f7, sp, 0xE4);
    lwc1(f6, sp, 0xE8);
    swc1(f8, s0, 1204);
    swc1(f7, s0, 1208);
    swc1(f6, s0, 1212);
    sb(t3, s0, 1108);
    sb(t3, s0, 1109);
    sb(t3, s0, 1110);
    sb(t3, s0, 1111);
    sb(t3, s0, 1144);
    sb(t3, s0, 1145);
    sb(t3, s0, 1146);
    sb(t3, s0, 1147);
    sb(t3, s0, 1180);
    sb(t3, s0, 1181);
    sb(t3, s0, 1182);
    sb(t3, s0, 1183);
    sb(t3, s0, 1216);
    sb(t3, s0, 1217);
    sb(t3, s0, 1218);
    sb(t3, s0, 1219);
    sw(t2, s0, 1124);
    sw(t1, s0, 1160);
    sw(t1, s0, 1196);
    sw(t2, s0, 1232);
    sw(t0, s0, 1128);
    sw(t0, s0, 1164);
    sw(a3, s0, 1200);
    sw(a3, s0, 1236);
    swc1(f5, sp, 0xD0);
    swc1(f4, sp, 0xD4);
    sw(zero, sp, 0xD8);
    lwc1(f8, sp, 0xD0);
    lwc1(f7, sp, 0xD4);
    lwc1(f6, sp, 0xD8);
    swc1(f8, s0, 1240);
    swc1(f7, s0, 1244);
    swc1(f6, s0, 1248);
    swc1(f3, sp, 0xC0);
    swc1(f4, sp, 0xC4);
    sw(zero, sp, 0xC8);
    lwc1(f7, sp, 0xC0);
    lwc1(f6, sp, 0xC4);
    lwc1(f4, sp, 0xC8);
    swc1(f7, s0, 1276);
    swc1(f6, s0, 1280);
    swc1(f4, s0, 1284);
    swc1(f3, sp, 0xB0);
    swc1(f2, sp, 0xB4);
    sw(zero, sp, 0xB8);
    lwc1(f6, sp, 0xB0);
    lwc1(f4, sp, 0xB4);
    lwc1(f3, sp, 0xB8);
    swc1(f6, s0, 1312);
    swc1(f4, s0, 1316);
    swc1(f3, s0, 1320);
    swc1(f5, sp, 0xA0);
    swc1(f2, sp, 0xA4);
    sw(zero, sp, 0xA8);
    lwc1(f4, sp, 0xA0);
    lwc1(f3, sp, 0xA4);
    lwc1(f2, sp, 0xA8);
    swc1(f4, s0, 1348);
    swc1(f3, s0, 1352);
    swc1(f2, s0, 1356);
    sb(t3, s0, 1252);
    sb(t3, s0, 1253);
    sb(t3, s0, 1254);
    sb(t3, s0, 1255);
    sb(t3, s0, 1288);
    sb(t3, s0, 1289);
    sb(t3, s0, 1290);
    sb(t3, s0, 1291);
    sb(t3, s0, 1324);
    sb(t3, s0, 1325);
    sb(t3, s0, 1326);
    sb(t3, s0, 1327);
    sb(t3, s0, 1360);
    sb(t3, s0, 1361);
    sb(t3, s0, 1362);
    sb(t3, s0, 1363);
    sw(t2, s0, 1268);
    sw(t1, s0, 1304);
    sw(t1, s0, 1340);
    sw(t2, s0, 1376);
    sw(t0, s0, 1272);
    sw(t0, s0, 1308);
    sw(a3, s0, 1344);
    sw(a3, s0, 1380);
    sw(a2, sp, 0x90);
    swc1(f1, sp, 0x94);
    sw(zero, sp, 0x98);
    lwc1(f4, sp, 0x90);
    lwc1(f3, sp, 0x94);
    lwc1(f2, sp, 0x98);
    swc1(f4, s0, 76);
    swc1(f3, s0, 80);
    swc1(f2, s0, 84);
    sw(a1, sp, 0x80);
    swc1(f1, sp, 0x84);
    sw(zero, sp, 0x88);
    lwc1(f4, sp, 0x80);
    lwc1(f3, sp, 0x84);
    lwc1(f2, sp, 0x88);
    swc1(f4, s0, 112);
    swc1(f3, s0, 116);
    swc1(f2, s0, 120);
    sw(a1, sp, 0x70);
    swc1(f0, sp, 0x74);
    sw(zero, sp, 0x78);
    lwc1(f4, sp, 0x70);
    lwc1(f3, sp, 0x74);
    lwc1(f2, sp, 0x78);
    swc1(f4, s0, 148);
    swc1(f3, s0, 152);
    swc1(f2, s0, 156);
    sw(a2, sp, 0x60);
    swc1(f0, sp, 0x64);
    sw(zero, sp, 0x68);
    lwc1(f4, sp, 0x60);
    lwc1(f3, sp, 0x64);
    lwc1(f2, sp, 0x68);
    swc1(f4, s0, 184);
    swc1(f3, s0, 188);
    swc1(f2, s0, 192);
    sb(t3, s0, 88);
    sb(t3, s0, 89);
    sb(t3, s0, 90);
    v1 = 64;
    sb(v1, s0, 91);
    sb(t3, s0, 124);
    sb(t3, s0, 125);
    sb(t3, s0, 126);
    sb(v1, s0, 127);
    sb(t3, s0, 160);
    sb(t3, s0, 161);
    sb(t3, s0, 162);
    sb(v1, s0, 163);
    sb(t3, s0, 196);
    sb(t3, s0, 197);
    sb(t3, s0, 198);
    sb(v1, s0, 199);
    sw(a0, s0, 104);
    sw(zero, s0, 140);
    sw(zero, s0, 176);
    sw(a0, s0, 212);
    sw(zero, s0, 108);
    sw(zero, s0, 144);
    sw(a0, s0, 180);
    sw(a0, s0, 216);
    sw(a2, sp, 0x50);
    swc1(f1, sp, 0x54);
    sw(zero, sp, 0x58);
    lwc1(f4, sp, 0x50);
    lwc1(f3, sp, 0x54);
    lwc1(f2, sp, 0x58);
    swc1(f4, s0, 1384);
    swc1(f3, s0, 1388);
    swc1(f2, s0, 1392);
    sw(a1, sp, 0x40);
    swc1(f1, sp, 0x44);
    sw(zero, sp, 0x48);
    lwc1(f3, sp, 0x40);
    lwc1(f2, sp, 0x44);
    lwc1(f1, sp, 0x48);
    swc1(f3, s0, 1420);
    swc1(f2, s0, 1424);
    swc1(f1, s0, 1428);
    sw(a1, sp, 0x30);
    swc1(f0, sp, 0x34);
    sw(zero, sp, 0x38);
    lwc1(f3, sp, 0x30);
    lwc1(f2, sp, 0x34);
    lwc1(f1, sp, 0x38);
    swc1(f3, s0, 1456);
    swc1(f2, s0, 1460);
    swc1(f1, s0, 1464);
    sw(a2, sp, 0x20);
    swc1(f0, sp, 0x24);
    sw(zero, sp, 0x28);
    lwc1(f2, sp, 0x20);
    lwc1(f1, sp, 0x24);
    lwc1(f0, sp, 0x28);
    swc1(f2, s0, 1492);
    swc1(f1, s0, 1496);
    swc1(f0, s0, 1500);
    sb(t3, s0, 1396);
    sb(t3, s0, 1397);
    sb(t3, s0, 1398);
    sb(t3, s0, 1399);
    sb(t3, s0, 1432);
    sb(t3, s0, 1433);
    sb(t3, s0, 1434);
    sb(t3, s0, 1435);
    sb(t3, s0, 1468);
    sb(t3, s0, 1469);
    sb(t3, s0, 1470);
    sb(t3, s0, 1471);
    sb(t3, s0, 1504);
    sb(t3, s0, 1505);
    sb(t3, s0, 1506);
    sb(t3, s0, 1507);
    sw(a0, s0, 1412);
    sw(zero, s0, 1448);
    sw(zero, s0, 1484);
    sw(a0, s0, 1520);
    sw(zero, s0, 1416);
    sw(zero, s0, 1452);
    sw(a0, s0, 1488);
    sw(a0, s0, 1524);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x260);
}

// 0x0020A800 sub_20A800 -- 816 bytes; frame 0xE0: ra sp+0x10, s0 sp+0x0 (sq)
// [gcModel_Init1](model) gc_model.c: sub_209EA0, kind (+4) = 1, the quad at +224 (sub_20C7B0), +808 = 0, and its
// quads (+-3.0 wide, +-3.84 / 0x7CB024 high; one black quad at +664).
void sub_20A800(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4};
    // 0x0020a800
    enter(ctx, 204);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x20A810u, gen::fn_sub_209EA0_00209ea0);
    v0 = 1;
    sw(v0, s0, kGcmKind);
    a0 = addiu(s0, kGcmQuad0);
    jal(ctx, 0x20A824u, gen::fn_sub_20C7B0_0020c7b0);
    sw(zero, s0, 808);
    a3 = 0x40400000;
    sw(a3, sp, 0xD0);
    lwc1(f4, gp, kGpCardHalfH);  // 0x7CB008
    swc1(f4, sp, 0xD4);
    sw(zero, sp, 0xD8);
    lwc1(f2, sp, 0xD0);
    lwc1(f1, sp, 0xD4);
    lwc1(f0, sp, 0xD8);
    swc1(f2, s0, 376);
    swc1(f1, s0, 380);
    swc1(f0, s0, 384);
    a2 = lui(0xC040);
    sw(a2, sp, 0xC0);
    swc1(f4, sp, 0xC4);
    sw(zero, sp, 0xC8);
    lwc1(f2, sp, 0xC0);
    lwc1(f1, sp, 0xC4);
    lwc1(f0, sp, 0xC8);
    swc1(f2, s0, 412);
    swc1(f1, s0, 416);
    swc1(f0, s0, 420);
    sw(a2, sp, 0xB0);
    lwc1(f3, gp, kGpCardBackY);  // 0x7CB024
    swc1(f3, sp, 0xB4);
    sw(zero, sp, 0xB8);
    lwc1(f2, sp, 0xB0);
    lwc1(f1, sp, 0xB4);
    lwc1(f0, sp, 0xB8);
    swc1(f2, s0, 448);
    swc1(f1, s0, 452);
    swc1(f0, s0, 456);
    sw(a3, sp, 0xA0);
    swc1(f3, sp, 0xA4);
    sw(zero, sp, 0xA8);
    lwc1(f2, sp, 0xA0);
    lwc1(f1, sp, 0xA4);
    lwc1(f0, sp, 0xA8);
    swc1(f2, s0, 484);
    swc1(f1, s0, 488);
    swc1(f0, s0, 492);
    a1 = 255;
    sb(a1, s0, 388);
    sb(a1, s0, 389);
    sb(a1, s0, 390);
    sb(a1, s0, 391);
    sb(a1, s0, 424);
    sb(a1, s0, 425);
    sb(a1, s0, 426);
    sb(a1, s0, 427);
    sb(a1, s0, 460);
    sb(a1, s0, 461);
    sb(a1, s0, 462);
    sb(a1, s0, 463);
    sb(a1, s0, 496);
    sb(a1, s0, 497);
    sb(a1, s0, 498);
    sb(a1, s0, 499);
    a0 = 0x3F800000;
    sw(a0, s0, 404);
    sw(zero, s0, 440);
    sw(zero, s0, 476);
    sw(a0, s0, 512);
    sw(zero, s0, 408);
    sw(zero, s0, 444);
    v1 = 0x3F230000;
    sw(v1, s0, 480);
    sw(v1, s0, 516);
    sw(a3, sp, 0x90);
    swc1(f4, sp, 0x94);
    sw(zero, sp, 0x98);
    lwc1(f2, sp, 0x90);
    lwc1(f1, sp, 0x94);
    lwc1(f0, sp, 0x98);
    swc1(f2, s0, 520);
    swc1(f1, s0, 524);
    swc1(f0, s0, 528);
    sw(a2, sp, 0x80);
    swc1(f4, sp, 0x84);
    sw(zero, sp, 0x88);
    lwc1(f2, sp, 0x80);
    lwc1(f1, sp, 0x84);
    lwc1(f0, sp, 0x88);
    swc1(f2, s0, 556);
    swc1(f1, s0, 560);
    swc1(f0, s0, 564);
    sw(a2, sp, 0x70);
    swc1(f3, sp, 0x74);
    sw(zero, sp, 0x78);
    lwc1(f2, sp, 0x70);
    lwc1(f1, sp, 0x74);
    lwc1(f0, sp, 0x78);
    swc1(f2, s0, 592);
    swc1(f1, s0, 596);
    swc1(f0, s0, 600);
    sw(a3, sp, 0x60);
    swc1(f3, sp, 0x64);
    sw(zero, sp, 0x68);
    lwc1(f2, sp, 0x60);
    lwc1(f1, sp, 0x64);
    lwc1(f0, sp, 0x68);
    swc1(f2, s0, 628);
    swc1(f1, s0, 632);
    swc1(f0, s0, 636);
    sb(a1, s0, 532);
    sb(a1, s0, 533);
    sb(a1, s0, 534);
    sb(a1, s0, 535);
    sb(a1, s0, 568);
    sb(a1, s0, 569);
    sb(a1, s0, 570);
    sb(a1, s0, 571);
    sb(a1, s0, 604);
    sb(a1, s0, 605);
    sb(a1, s0, 606);
    sb(a1, s0, 607);
    sb(a1, s0, 640);
    sb(a1, s0, 641);
    sb(a1, s0, 642);
    sb(a1, s0, 643);
    sw(a0, s0, 548);
    sw(zero, s0, 584);
    sw(zero, s0, 620);
    sw(a0, s0, 656);
    sw(zero, s0, 552);
    sw(zero, s0, 588);
    sw(v1, s0, 624);
    sw(v1, s0, 660);
    sw(a3, sp, 0x50);
    sw(a3, sp, 0x54);
    sw(zero, sp, 0x58);
    lwc1(f2, sp, 0x50);
    lwc1(f1, sp, 0x54);
    lwc1(f0, sp, 0x58);
    swc1(f2, s0, 664);
    swc1(f1, s0, 668);
    swc1(f0, s0, 672);
    sw(a2, sp, 0x40);
    sw(a3, sp, 0x44);
    sw(zero, sp, 0x48);
    lwc1(f2, sp, 0x40);
    lwc1(f1, sp, 0x44);
    lwc1(f0, sp, 0x48);
    swc1(f2, s0, 700);
    swc1(f1, s0, 704);
    swc1(f0, s0, 708);
    sw(a2, sp, 0x30);
    sw(a2, sp, 0x34);
    sw(zero, sp, 0x38);
    lwc1(f2, sp, 0x30);
    lwc1(f1, sp, 0x34);
    lwc1(f0, sp, 0x38);
    swc1(f2, s0, 736);
    swc1(f1, s0, 740);
    swc1(f0, s0, 744);
    sw(a3, sp, 0x20);
    sw(a2, sp, 0x24);
    sw(zero, sp, 0x28);
    lwc1(f2, sp, 0x20);
    lwc1(f1, sp, 0x24);
    lwc1(f0, sp, 0x28);
    swc1(f2, s0, 772);
    swc1(f1, s0, 776);
    swc1(f0, s0, 780);
    sb(zero, s0, 676);
    sb(zero, s0, 677);
    sb(zero, s0, 678);
    sb(a1, s0, 679);
    sb(zero, s0, 712);
    sb(zero, s0, 713);
    sb(zero, s0, 714);
    sb(a1, s0, 715);
    sb(zero, s0, 748);
    sb(zero, s0, 749);
    sb(zero, s0, 750);
    sb(a1, s0, 751);
    sb(zero, s0, 784);
    sb(zero, s0, 785);
    sb(zero, s0, 786);
    sb(a1, s0, 787);
    sw(a0, s0, 692);
    sw(zero, s0, 728);
    sw(zero, s0, 764);
    sw(a0, s0, 800);
    sw(zero, s0, 696);
    sw(zero, s0, 732);
    sw(a0, s0, 768);
    sw(a0, s0, 804);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xE0);
}

// 0x0020CD50 sub_20CD50 -- 76 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [gcModel_SetGrid](model, grid) gc_model.c: builds the grid (sub_20CDA0), +220 = grid, flags |= 8.
void sub_20CD50(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0020cd50
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a0 = s0;
    jal(ctx, 0x20CD6Cu, gen::fn_sub_20CDA0_0020cda0);
    sw(s0, s1, kGcmGrid);
    lw(v1, s1, kGcmFlags);
    v1 = v1 | 0x8;
    sw(v1, s1, kGcmFlags);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00215830 sub_215830 -- 500 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bsaMain_GetKindPage](kind) bsa_main.c: the page record of panel sprite set 2 (sub_21C3F0(2)) for a skill / analyse
// kind: kinds 1..12 -> pages 10..21, 13..22 -> pages 0..9 (the inner jump table 0x7B7470 under the outer 0x7B74D0),
// 23 -> page 59; 0 and anything above 23: K_Assert (line 1912) and $v0 = 0. (The inner table's case 0, K_Assert line
// 1901 and the page of the leftover $s0, cannot be reached: the outer table sends only 1..22 there.)
void sub_215830(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00215830
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    a0 = 2;
    jal(ctx, 0x21584Cu, gen::fn_sub_21C3F0_0021c3f0);
    s1 = v0;
    at = sltiu(s2, 24);
    if (at != 0) {
        // 0x00215864
        charge(ctx, 7);
        v0 = 0x7B0000;
        v0 = addiu(v0, 29904);  // &0x7B74D0
        v1 = sll(s2, 2);
        v0 = addu(v1, v0);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x215880u:  // table[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22]
            // 0x00215880
            charge(ctx, 3);
            at = sltiu(s2, 23);
            if (at != 0) {
                // 0x0021588c
                charge(ctx, 6);
                v0 = 0x7B0000;
                v0 = addiu(v0, 29808);  // &0x7B7470
                v0 = addu(v1, v0);
                lw(v0, v0, 0);
                switch (v0.u()) {
                case 0x2158A4u:  // table[1]
                    // 0x002158a4
                    charge(ctx, 3);
                    s0 = 10;
                    break;
                case 0x2158B0u:  // table[2]
                    // 0x002158b0
                    charge(ctx, 3);
                    s0 = 11;
                    break;
                case 0x2158BCu:  // table[3]
                    // 0x002158bc
                    charge(ctx, 3);
                    s0 = 12;
                    break;
                case 0x2158C8u:  // table[4]
                    // 0x002158c8
                    charge(ctx, 3);
                    s0 = 13;
                    break;
                case 0x2158D4u:  // table[5]
                    // 0x002158d4
                    charge(ctx, 3);
                    s0 = 14;
                    break;
                case 0x2158E0u:  // table[6]
                    // 0x002158e0
                    charge(ctx, 3);
                    s0 = 15;
                    break;
                case 0x2158ECu:  // table[7]
                    // 0x002158ec
                    charge(ctx, 3);
                    s0 = 16;
                    break;
                case 0x2158F8u:  // table[8]
                    // 0x002158f8
                    charge(ctx, 3);
                    s0 = 17;
                    break;
                case 0x215904u:  // table[9]
                    // 0x00215904
                    charge(ctx, 3);
                    s0 = 18;
                    break;
                case 0x215910u:  // table[10]
                    // 0x00215910
                    charge(ctx, 3);
                    s0 = 19;
                    break;
                case 0x21591Cu:  // table[11]
                    // 0x0021591c
                    charge(ctx, 3);
                    s0 = 20;
                    break;
                case 0x215928u:  // table[12]
                    // 0x00215928
                    charge(ctx, 3);
                    s0 = 21;
                    break;
                case 0x215934u:  // table[13]
                    // 0x00215934
                    charge(ctx, 3);
                    s0 = 0;
                    break;
                case 0x215940u:  // table[14]
                    // 0x00215940
                    charge(ctx, 3);
                    s0 = 1;
                    break;
                case 0x21594Cu:  // table[15]
                    // 0x0021594c
                    charge(ctx, 3);
                    s0 = 2;
                    break;
                case 0x215958u:  // table[16]
                    // 0x00215958
                    charge(ctx, 3);
                    s0 = 3;
                    break;
                case 0x215964u:  // table[17]
                    // 0x00215964
                    charge(ctx, 3);
                    s0 = 4;
                    break;
                case 0x215970u:  // table[18]
                    // 0x00215970
                    charge(ctx, 3);
                    s0 = 5;
                    break;
                case 0x21597Cu:  // table[19]
                    // 0x0021597c
                    charge(ctx, 3);
                    s0 = 6;
                    break;
                case 0x215988u:  // table[20]
                    // 0x00215988
                    charge(ctx, 3);
                    s0 = 7;
                    break;
                case 0x215994u:  // table[21]
                    // 0x00215994
                    charge(ctx, 3);
                    s0 = 8;
                    break;
                case 0x2159A0u:  // table[22]
                    // 0x002159a0
                    charge(ctx, 3);
                    s0 = 9;
                    break;
                case 0x2159ACu:  // table[0]
                L_002159ac:
                    charge(ctx, 5);
                    a0 = 0x690000;
                    a0 = addiu(a0, -7656);  // "bsa_main.c"
                    a1 = 1901;
                    jal(ctx, 0x2159B8u, gen::fn_sub_19D3F0_0019d3f0);
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v0.u());
                    return;
                }
                goto L_002159c0;
            }
            goto L_002159ac;
        case 0x2159D8u:  // table[23]
            // 0x002159d8
            charge(ctx, 6);
            a0 = s1;
            a1 = 59;
            jal(ctx, 0x2159E0u, gen::fn_sub_21CCA0_0021cca0);
            break;
        case 0x2159F0u:  // table[0]
        L_002159f0:
            charge(ctx, 6);
            a0 = 0x690000;
            a0 = addiu(a0, -7656);  // "bsa_main.c"
            a1 = 1912;
            jal(ctx, 0x2159FCu, gen::fn_sub_19D3F0_0019d3f0);
            v0 = 0;
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x00215a08 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
    goto L_002159f0;
L_002159c0:
    charge(ctx, 6);
    a0 = s1;
    a1 = s0;
    jal(ctx, 0x2159C8u, gen::fn_sub_21CCA0_0021cca0);
    // 0x00215a08 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00222930 sub_222930 -- 304 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bcmPanel_OpenList1] bcm_panel.c: flags |= 2, list = 1, state 3, sub-list 1 (previous kept), the command quads (pages
// cur and cur + 7), the frame (sub_226320), the title quads (page 35, +16944 and +17200 mode 1), the rows (sub_222D60).
void sub_222930(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00222930
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308
    if (v0 == 0) {
        // 0x0022294c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x222958u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00222960
    charge(ctx, 64);
    lw(s0, gp, kGpBcmPanel);  // 0x7CE308
    a0 = 0;
    jal(ctx, 0x222968u, gen::fn_sub_21C3F0_0021c3f0);
    s1 = v0;
    lw(v0, s0, kBcmFlags);
    v0 = v0 | 0x2;
    sw(v0, s0, kBcmFlags);
    sw(zero, s0, kBcmList);
    v0 = 0;
    v0 = v0 | 0x1;
    sw(v0, s0, kBcmList);
    v0 = 3;
    sw(v0, s0, kBcmState);
    lw(v0, s0, kBcmSub);
    sw(v0, s0, kBcmSubPrev);
    v0 = 1;
    sw(v0, s0, kBcmSub);
    sw(zero, s0, kBcmSubTimer);
    sw(zero, s0, kBcmSubStep);
    a0 = s1;
    lw(a1, s0, kBcmCur);
    jal(ctx, 0x2229B8u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, kBcmQuadCur);
    a1 = v0;
    jal(ctx, 0x2229C8u, gen::fn_sub_21D3B0_0021d3b0);
    lw(v0, s0, kBcmCur);
    a1 = addiu(v0, 7);
    a0 = s1;
    jal(ctx, 0x2229DCu, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, kBcmQuadPrev);
    a1 = v0;
    jal(ctx, 0x2229ECu, gen::fn_sub_21D3B0_0021d3b0);
    jal(ctx, 0x2229F4u, gen::fn_sub_226320_00226320);
    a0 = s1;
    a1 = 35;
    jal(ctx, 0x222A04u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, kBcmTitle);
    a1 = v0;
    jal(ctx, 0x222A14u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s1;
    a1 = 35;
    jal(ctx, 0x222A24u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, kBcmTitle2);
    a1 = v0;
    a2 = 1;
    jal(ctx, 0x222A38u, gen::fn_sub_21E380_0021e380);
    jal(ctx, 0x222A40u, gen::fn_sub_222D60_00222d60);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00222A60 sub_222A60 -- 304 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bcmPanel_OpenList2] bcm_panel.c: as sub_222930 with list 2, sub-list 2 and the rows of sub_222B90.
void sub_222A60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00222a60
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308
    if (v0 == 0) {
        // 0x00222a7c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x222A88u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00222a90
    charge(ctx, 64);
    lw(s0, gp, kGpBcmPanel);  // 0x7CE308
    a0 = 0;
    jal(ctx, 0x222A98u, gen::fn_sub_21C3F0_0021c3f0);
    s1 = v0;
    lw(v0, s0, kBcmFlags);
    v0 = v0 | 0x2;
    sw(v0, s0, kBcmFlags);
    sw(zero, s0, kBcmList);
    v0 = 0;
    v0 = v0 | 0x2;
    sw(v0, s0, kBcmList);
    v0 = 3;
    sw(v0, s0, kBcmState);
    lw(v0, s0, kBcmSub);
    sw(v0, s0, kBcmSubPrev);
    v0 = 2;
    sw(v0, s0, kBcmSub);
    sw(zero, s0, kBcmSubTimer);
    sw(zero, s0, kBcmSubStep);
    a0 = s1;
    lw(a1, s0, kBcmCur);
    jal(ctx, 0x222AE8u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, kBcmQuadCur);
    a1 = v0;
    jal(ctx, 0x222AF8u, gen::fn_sub_21D3B0_0021d3b0);
    lw(v0, s0, kBcmCur);
    a1 = addiu(v0, 7);
    a0 = s1;
    jal(ctx, 0x222B0Cu, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, kBcmQuadPrev);
    a1 = v0;
    jal(ctx, 0x222B1Cu, gen::fn_sub_21D3B0_0021d3b0);
    jal(ctx, 0x222B24u, gen::fn_sub_226320_00226320);
    a0 = s1;
    a1 = 35;
    jal(ctx, 0x222B34u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, kBcmTitle);
    a1 = v0;
    jal(ctx, 0x222B44u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s1;
    a1 = 35;
    jal(ctx, 0x222B54u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, kBcmTitle2);
    a1 = v0;
    a2 = 1;
    jal(ctx, 0x222B68u, gen::fn_sub_21E380_0021e380);
    jal(ctx, 0x222B70u, gen::fn_sub_222B90_00222b90);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00222FA0 sub_222FA0 -- 312 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bcmPanel_OpenList4] bcm_panel.c: as sub_222930 with list 4, sub-list 3, +17992 = -1, +18008 = 0, title page 36 and
// the rows of sub_2230E0.
void sub_222FA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00222fa0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308
    if (v0 == 0) {
        // 0x00222fbc
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x222FC8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00222fd0
    charge(ctx, 66);
    lw(s0, gp, kGpBcmPanel);  // 0x7CE308
    a0 = 0;
    jal(ctx, 0x222FD8u, gen::fn_sub_21C3F0_0021c3f0);
    s1 = v0;
    lw(v0, s0, kBcmFlags);
    v0 = v0 | 0x2;
    sw(v0, s0, kBcmFlags);
    sw(zero, s0, kBcmList);
    v0 = 0;
    v0 = v0 | 0x4;
    sw(v0, s0, kBcmList);
    v1 = 3;
    sw(v1, s0, kBcmState);
    lw(v0, s0, kBcmSub);
    sw(v0, s0, kBcmSubPrev);
    sw(v1, s0, kBcmSub);
    sw(zero, s0, kBcmSubStep);
    v0 = si(-1);
    sw(v0, s0, kBcmSubSel);
    sw(zero, s0, kBcmSubTimer);
    sw(zero, s0, 18008);
    a0 = s1;
    lw(a1, s0, kBcmCur);
    jal(ctx, 0x223030u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, kBcmQuadCur);
    a1 = v0;
    jal(ctx, 0x223040u, gen::fn_sub_21D3B0_0021d3b0);
    lw(v0, s0, kBcmCur);
    a1 = addiu(v0, 7);
    a0 = s1;
    jal(ctx, 0x223054u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, kBcmQuadPrev);
    a1 = v0;
    jal(ctx, 0x223064u, gen::fn_sub_21D3B0_0021d3b0);
    jal(ctx, 0x22306Cu, gen::fn_sub_226320_00226320);
    a0 = s1;
    a1 = 36;
    jal(ctx, 0x22307Cu, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, kBcmTitle);
    a1 = v0;
    jal(ctx, 0x22308Cu, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s1;
    a1 = 36;
    jal(ctx, 0x22309Cu, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, kBcmTitle2);
    a1 = v0;
    a2 = 1;
    jal(ctx, 0x2230B0u, gen::fn_sub_21E380_0021e380);
    jal(ctx, 0x2230B8u, gen::fn_sub_2230E0_002230e0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00224660 sub_224660 -- 508 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bcmPanel_OpenList8] bcm_panel.c: list 8, sub-list 4, the frame first, the command and title quads (page 36), page 19
// of set 3 (+21936), page 75 of set 1 (+22192), page 68 for every row (784 bytes), then sub_224860.
void sub_224660(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00224660
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308
    if (v0 == 0) {
        // 0x00224688
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x224694u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0022469c
    charge(ctx, 83);
    lw(s1, gp, kGpBcmPanel);  // 0x7CE308
    a0 = 0;
    jal(ctx, 0x2246A4u, gen::fn_sub_21C3F0_0021c3f0);
    s4 = v0;
    a0 = 1;
    jal(ctx, 0x2246B4u, gen::fn_sub_21C3F0_0021c3f0);
    s3 = v0;
    a0 = 3;
    jal(ctx, 0x2246C4u, gen::fn_sub_21C3F0_0021c3f0);
    s2 = v0;
    s0 = addiu(s1, kBcmRows);
    lw(v0, s1, kBcmFlags);
    v0 = v0 | 0x2;
    sw(v0, s1, kBcmFlags);
    sw(zero, s1, kBcmList);
    v0 = 0;
    v0 = v0 | 0x8;
    sw(v0, s1, kBcmList);
    v0 = 3;
    sw(v0, s1, kBcmState);
    lw(v0, s1, kBcmSub);
    sw(v0, s1, kBcmSubPrev);
    v0 = 4;
    sw(v0, s1, kBcmSub);
    sw(zero, s1, kBcmSubTimer);
    jal(ctx, 0x22470Cu, gen::fn_sub_226320_00226320);
    a0 = s4;
    lw(a1, s1, kBcmCur);
    jal(ctx, 0x22471Cu, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s1, kBcmQuadCur);
    a1 = v0;
    jal(ctx, 0x22472Cu, gen::fn_sub_21D3B0_0021d3b0);
    lw(v0, s1, kBcmCur);
    a1 = addiu(v0, 7);
    a0 = s4;
    jal(ctx, 0x224740u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s1, kBcmQuadPrev);
    a1 = v0;
    jal(ctx, 0x224750u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s4;
    a1 = 36;
    jal(ctx, 0x224760u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s1, kBcmTitle);
    a1 = v0;
    jal(ctx, 0x224770u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s4;
    a1 = 36;
    jal(ctx, 0x224780u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s1, kBcmTitle2);
    a1 = v0;
    a2 = 1;
    jal(ctx, 0x224794u, gen::fn_sub_21E380_0021e380);
    a0 = s2;
    a1 = 19;
    jal(ctx, 0x2247A4u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, 3920);
    a1 = v0;
    jal(ctx, 0x2247B4u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s3;
    a1 = 75;
    jal(ctx, 0x2247C4u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, 4176);
    a1 = v0;
    jal(ctx, 0x2247D4u, gen::fn_sub_21D3B0_0021d3b0);
    s2 = 0;
    for (;;) {
        // 0x00224820
        charge(ctx, 4);
        lw(v0, s1, kBcmRowCount);
        v0 = slt(s2, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002247e8
        charge(ctx, 14);
        a0 = s4;
        a1 = 68;
        jal(ctx, 0x2247F0u, gen::fn_sub_21CCA0_0021cca0);
        v1 = sll(s2, 3);
        a0 = subu(v1, s2);
        v1 = sll(a0, 3);
        v1 = subu(v1, a0);
        v1 = sll(v1, 4);
        a0 = addu(s0, v1);
        a1 = v0;
        jal(ctx, 0x224814u, gen::fn_sub_21D3B0_0021d3b0);
        s2 = addiu(s2, 1);
    }
    // 0x00224830
    charge(ctx, 11);
    jal(ctx, 0x224830u, gen::fn_sub_224860_00224860);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0022BF60 sub_22BF60 -- 308 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bcmPanel_OpenDetail2] bcm_panel.c: the detail frame (sub_22C210), page 49 / 48 by +27912, a 3-digit number (+27916),
// page 43 of set 6; +17988 = 3.
void sub_22BF60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0022bf60
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308
    if (v0 == 0) {
        // 0x0022bf88
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x22BF94u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0022bf9c
    charge(ctx, 16);
    lw(s1, gp, kGpBcmPanel);  // 0x7CE308
    a0 = 0;
    jal(ctx, 0x22BFA4u, gen::fn_sub_21C3F0_0021c3f0);
    s4 = v0;
    a0 = 6;
    jal(ctx, 0x22BFB4u, gen::fn_sub_21C3F0_0021c3f0);
    s3 = v0;
    jal(ctx, 0x22BFC0u, gen::fn_sub_22C210_0022c210);
    s0 = addiu(s1, 27904);
    lw(v1, s1, kBcmDetailKind);
    v0 = 1;
    if (v1 == v0) {
        // 0x0022c008
        charge(ctx, 5);
        a0 = s4;
        a1 = 49;
        jal(ctx, 0x22C010u, gen::fn_sub_21CCA0_0021cca0);
        s2 = v0;
    } else {
        // 0x0022bfdc
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x0022bfec
            charge(ctx, 7);
            a0 = s4;
            a1 = 48;
            jal(ctx, 0x22BFF4u, gen::fn_sub_21CCA0_0021cca0);
            s2 = v0;
        } else {
            // 0x0022bfe4
            charge(ctx, 2);
        }
    }
    // 0x0022c01c
    charge(ctx, 30);
    a0 = addiu(s0, 16);
    a1 = s2;
    jal(ctx, 0x22C024u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = addiu(s0, 272);
    a1 = 3;
    lw(a2, s0, 12);
    a3 = 1;
    jal(ctx, 0x22C03Cu, gen::fn_bpIfontDrawNumber_00238980);
    a0 = s3;
    a1 = 43;
    jal(ctx, 0x22C04Cu, gen::fn_sub_21CCA0_0021cca0);
    s2 = v0;
    a0 = addiu(s0, 1040);
    a1 = s2;
    jal(ctx, 0x22C060u, gen::fn_sub_21D3B0_0021d3b0);
    v1 = 3;
    sw(v1, s1, kBcmSubStep);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0022C0E0 sub_22C0E0 -- 232 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bcmPanel_OpenDetail1] bcm_panel.c: the detail frame, page 40, a 2-digit number (+27908), page 26 of set 6;
// +17988 = 4.
void sub_22C0E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0022c0e0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBcmPanel);  // 0x7CE308
    if (v0 == 0) {
        // 0x0022c104
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -7296);  // "bcm_panel.c"
        a1 = 230;
        jal(ctx, 0x22C110u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0022c118
    charge(ctx, 44);
    lw(s1, gp, kGpBcmPanel);  // 0x7CE308
    a0 = 0;
    jal(ctx, 0x22C120u, gen::fn_sub_21C3F0_0021c3f0);
    s3 = v0;
    a0 = 6;
    jal(ctx, 0x22C130u, gen::fn_sub_21C3F0_0021c3f0);
    s2 = v0;
    jal(ctx, 0x22C13Cu, gen::fn_sub_22C210_0022c210);
    s0 = addiu(s1, 27904);
    a0 = s3;
    a1 = 40;
    jal(ctx, 0x22C150u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, 16);
    a1 = v0;
    jal(ctx, 0x22C160u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = addiu(s0, 272);
    a1 = 2;
    lw(a2, s0, 4);
    a3 = 1;
    jal(ctx, 0x22C178u, gen::fn_bpIfontDrawNumber_00238980);
    a0 = s2;
    a1 = 26;
    jal(ctx, 0x22C188u, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, 784);
    a1 = v0;
    jal(ctx, 0x22C198u, gen::fn_sub_21D3B0_0021d3b0);
    v1 = 4;
    sw(v1, s1, kBcmSubStep);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0022E780 sub_22E780 -- 196 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [bppPanel_SetIcon](member, kind) bpp_panel.c: +1320 = kind; kind 0 clears flag 2; kinds 1..5 put the page of
// sub_22E850(kind) of panel set 3 into the quad +1328 and set flag 2; others change nothing more (jump table 0x7B7790).
void sub_22E780(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0022e780
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s2 = a1;
    sw(s2, a0, 1320);
    a0 = 3;
    jal(ctx, 0x22E7A4u, gen::fn_sub_21C3F0_0021c3f0);
    s0 = v0;
    at = sltiu(s2, 6);
    if (at != 0) {
        // 0x0022e7bc
        charge(ctx, 7);
        a0 = 0x7B0000;
        a0 = addiu(a0, 30608);  // &0x7B7790
        v1 = sll(s2, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x22E7D8u:  // table[0]
            // 0x0022e7d8
            charge(ctx, 6);
            lw(a0, s1, 0);
            v1 = si(-3);
            v1 = a0 & v1;
            sw(v1, s1, 0);
            break;
        case 0x22E7F0u:  // table[1, 2, 3, 4, 5]
            // 0x0022e7f0
            charge(ctx, 14);
            lw(a0, s1, 1320);
            jal(ctx, 0x22E7F4u, gen::fn_sub_22E850_0022e850);
            a0 = s0;
            a1 = v0;
            jal(ctx, 0x22E804u, gen::fn_sub_21CCA0_0021cca0);
            a0 = addiu(s1, 1328);
            a1 = v0;
            jal(ctx, 0x22E814u, gen::fn_sub_21D3B0_0021d3b0);
            lw(v1, s1, 0);
            v1 = v1 | 0x2;
            sw(v1, s1, 0);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x0022e828 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00239170 sub_239170 -- 268 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [sflGround_Register](work) sfl_ground.c: asserts the slot is empty (line 144); +0 = +12 = 0; the index list at +33728
// for an 8 x 10 grid of quads (11 vertices per row): six u16 per quad {v, v+1, v+11, v+1, v+12, v+11}; the object at +34688 gets its
// +1540 = 0 (sub_249680); slot = work.
void sub_239170(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00239170
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, gp, kGpSflGround);  // 0x7CE314
    if (v0 != 0) {
        // 0x0023918c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -6224);  // "sfl_ground.c"
        a1 = 144;
        jal(ctx, 0x239198u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002391a0
    charge(ctx, 9);
    sw(zero, s0, 0);
    sw(zero, s0, 12);
    t1 = 0;
    t0 = 0;
    t2 = 0;
    at = 0x83C0;
    a3 = addu(s0, at);
    for (;;) {
        // 0x00239248
        charge(ctx, 3);
        v0 = slti(t2, 8);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002391c4
        charge(ctx, 3);
        t3 = 0;
        for (;;) {
            // 0x00239234
            charge(ctx, 3);
            v0 = slti(t3, 10);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002391d0
            charge(ctx, 25);
            v1 = sll(t1, 1);
            v0 = addu(a3, v1);
            sh(t0, v0, 0);
            a2 = addu(s0, v1);
            a1 = addiu(t0, 1);
            v0 = 0x10000;
            v0 = addu(a2, v0);
            sh(a1, v0, -31806);
            a0 = addiu(t0, 11);
            v0 = 0x10000;
            v0 = addu(a2, v0);
            sh(a0, v0, -31804);
            v0 = 0x10000;
            v0 = addu(a2, v0);
            sh(a1, v0, -31802);
            v1 = addiu(t0, 12);
            v0 = 0x10000;
            v0 = addu(a2, v0);
            sh(v1, v0, -31800);
            v0 = 0x10000;
            v0 = addu(a2, v0);
            sh(a0, v0, -31798);
            t1 = addiu(t1, 6);
            t0 = a1;
            t3 = addiu(t3, 1);
        }
        // 0x00239240
        charge(ctx, 2);
        t0 = addiu(t0, 1);
        t2 = addiu(t2, 1);
    }
    // 0x00239254
    charge(ctx, 10);
    at = 0x8780;
    a0 = addu(s0, at);
    jal(ctx, 0x23925Cu, gen::fn_sub_249680_00249680);
    sw(s0, gp, kGpSflGround);  // 0x7CE314
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0024A7F0 sub_24A7F0 -- 120 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [brpBirth_CreateWork] brp_birth.c: a 50,544-byte block from RwMalloc (the slot 0x960178, hint 0x40000); registers
// the gc_res work at +4052, the sfl_res work at +14128, the brp_res work at +14084 (sub_24BA30) and the sfl_ground work
// at +14272 inside it; +4 = +8 = 0; the brp_birth slot = block.
void sub_24A7F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0024a7f0
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0xC570;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x24A80Cu, v0.u());
    s0 = v0;
    a0 = addiu(s0, 4052);
    jal(ctx, 0x24A81Cu, gen::fn_sub_219C90_00219c90);
    a0 = addiu(s0, 14128);
    jal(ctx, 0x24A828u, gen::fn_sub_20D7D0_0020d7d0);
    a0 = addiu(s0, 14084);
    jal(ctx, 0x24A834u, gen::fn_sub_24BA30_0024ba30);
    a0 = addiu(s0, 14272);
    jal(ctx, 0x24A840u, gen::fn_sub_239170_00239170);
    sw(zero, s0, 4);
    sw(zero, s0, 8);
    sw(s0, gp, kGpBrpBirth);  // 0x7CE330
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00275A90 sub_275A90 -- 296 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [brLvpnl_Show] br_lvpnl.c: asserts the work (line 59); pages 0, 2, 1, 3, 11 of result set 0 (sub_234630(0)) into the
// six quads (page 11 twice, the second in mode 1); the layout (sub_2760F0); flags |= 1.
void sub_275A90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00275a90
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, kGpBrLvpnl);  // 0x7CE3C8
    if (v0 == 0) {
        // 0x00275aac
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4336);  // "br_lvpnl.c"
        a1 = 59;
        jal(ctx, 0x275AB8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00275ac0
    charge(ctx, 62);
    lw(s0, gp, kGpBrLvpnl);  // 0x7CE3C8
    a0 = 0;
    jal(ctx, 0x275AC8u, gen::fn_sub_234630_00234630);
    s1 = v0;
    a0 = s1;
    a1 = 0;
    jal(ctx, 0x275ADCu, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, 16);
    a1 = v0;
    jal(ctx, 0x275AECu, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s1;
    a1 = 2;
    jal(ctx, 0x275AFCu, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, 272);
    a1 = v0;
    jal(ctx, 0x275B0Cu, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s1;
    a1 = 1;
    jal(ctx, 0x275B1Cu, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, 528);
    a1 = v0;
    jal(ctx, 0x275B2Cu, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s1;
    a1 = 3;
    jal(ctx, 0x275B3Cu, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, 784);
    a1 = v0;
    jal(ctx, 0x275B4Cu, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s1;
    a1 = 11;
    jal(ctx, 0x275B5Cu, gen::fn_sub_21CCA0_0021cca0);
    s1 = v0;
    a0 = addiu(s0, 1040);
    a1 = s1;
    jal(ctx, 0x275B70u, gen::fn_sub_21D3B0_0021d3b0);
    a0 = addiu(s0, 1296);
    a1 = s1;
    a2 = 1;
    jal(ctx, 0x275B84u, gen::fn_sub_21E380_0021e380);
    jal(ctx, 0x275B8Cu, gen::fn_sub_2760F0_002760f0);
    lw(v1, s0, kLvFlags);
    v1 = v1 | 0x1;
    sw(v1, s0, kLvFlags);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00275BC0 sub_275BC0 -- 228 bytes; frame 0x10: ra sp+0x0
// [brLvpnl_Update] br_lvpnl.c: when shown (bit 0): while animating (bit 1) the frame counter runs to 36 (mode 0) or
// 33 (mode 1), then the animation bit clears; then the layout (sub_2760F0).
void sub_275BC0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00275bc0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBrLvpnl);  // 0x7CE3C8
    if (v1 == 0) {
        // 0x00275bd4
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4336);  // "br_lvpnl.c"
        a1 = 59;
        jal(ctx, 0x275BE0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00275be8
    charge(ctx, 6);
    lw(a1, gp, kGpBrLvpnl);  // 0x7CE3C8
    lw(a0, a1, kLvFlags);
    v1 = nor(a0, 0);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        // 0x00275c00
        charge(ctx, 3);
        v0 = a0 & 0x2;
        if (v0 != 0) {
            // 0x00275c0c
            charge(ctx, 4);
            lw(v1, a1, kLvMode);
            v0 = 1;
            if (v1 == v0) {
                // 0x00275c60
                charge(ctx, 4);
                lw(v0, a1, kLvFrame);
                at = slti(v0, 33);
                if (at == 0) {
                    // 0x00275c80
                    charge(ctx, 3);
                    v0 = si(-3);
                    v0 = a0 & v0;
                    sw(v0, a1, kLvFlags);
                } else {
                    // 0x00275c70
                    charge(ctx, 4);
                    v0 = addiu(v0, 1);
                    sw(v0, a1, kLvFrame);
                }
            } else {
                // 0x00275c1c
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x00275c2c
                    charge(ctx, 4);
                    lw(v0, a1, kLvFrame);
                    at = slti(v0, 36);
                    if (at == 0) {
                        // 0x00275c4c
                        charge(ctx, 5);
                        v0 = si(-3);
                        v0 = a0 & v0;
                        sw(v0, a1, kLvFlags);
                    } else {
                        // 0x00275c3c
                        charge(ctx, 4);
                        v0 = addiu(v0, 1);
                        sw(v0, a1, kLvFrame);
                    }
                } else {
                    // 0x00275c24
                    charge(ctx, 2);
                }
            }
        }
        // 0x00275c8c
        charge(ctx, 2);
        jal(ctx, 0x275C8Cu, gen::fn_sub_2760F0_002760f0);
    }
    // 0x00275c94 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0027B610 sub_27B610 -- 176 bytes; frame 0x10: ra sp+0x0
// [bpSelect_Update] bp_select.c: asserts the work (line 39); when active (bit 0): closing (bit 1) counts the fade to 20
// and then clears the active bit, opening counts it to 20; then the layout (sub_27B6C0).
void sub_27B610(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027b610
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBpSelect);  // 0x7CE3E4
    if (v1 == 0) {
        // 0x0027b624
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4152);  // "bp_select.c"
        a1 = 39;
        jal(ctx, 0x27B630u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0027b638
    charge(ctx, 6);
    lw(a1, gp, kGpBpSelect);  // 0x7CE3E4
    lw(a0, a1, kSelFlags);
    v1 = nor(a0, 0);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        // 0x0027b650
        charge(ctx, 3);
        v0 = a0 & 0x2;
        if (v0 == 0) {
            // 0x0027b690
            charge(ctx, 4);
            lw(v0, a1, kSelFrame);
            at = slti(v0, 20);
            if (at != 0) {
                // 0x0027b6a0
                charge(ctx, 2);
                v0 = addiu(v0, 1);
                sw(v0, a1, kSelFrame);
            }
        } else {
            // 0x0027b65c
            charge(ctx, 4);
            lw(v0, a1, kSelFrame);
            at = slti(v0, 20);
            if (at == 0) {
                // 0x0027b67c
                charge(ctx, 5);
                v0 = si(-2);
                v0 = a0 & v0;
                sw(v0, a1, kSelFlags);
            } else {
                // 0x0027b66c
                charge(ctx, 4);
                v0 = addiu(v0, 1);
                sw(v0, a1, kSelFrame);
            }
        }
        // 0x0027b6a8
        charge(ctx, 2);
        jal(ctx, 0x27B6A8u, gen::fn_sub_27B6C0_0027b6c0);
    }
    // 0x0027b6b0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

}  // namespace p3fes::game
