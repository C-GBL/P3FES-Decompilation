// The effect system, second pass (slice fx2): the spark kinds 1, 2, 4, 5, 6 and 8 of effect class 10 (kind rows
// 0x69C850 + 28 * kind: init, create, destroy, clone, update, draw) and the class-10 instance allocator sub_341F10.
// Records: fx2.h (namespace fx2).
// The bodies are p3fes_handgen's (hg_cpu.h): register for register and block for block as the recompiled bodies; the
// readability pass adds roles, block comments and named offsets and changes no statement (see fx2_psys.cpp). Names in
// [brackets] are proposals (ADR-0009).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/fx2.h"

namespace p3fes::recomp_gen {
void fn_cosf_0052e6d8(p3fes::EEContext&);
void fn_dpmul_00531230(p3fes::EEContext&);
void fn_dpsub_005311c8(p3fes::EEContext&);
void fn_dptofp_005318a0(p3fes::EEContext&);
void fn_fabs_0052e118(p3fes::EEContext&);
void fn_fptodp_00530da0(p3fes::EEContext&);
void fn_geometryLock_00493370(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_sinf_0052e878(p3fes::EEContext&);
void fn_sub_198590_00198590(p3fes::EEContext&);
void fn_sub_316910_00316910(p3fes::EEContext&);
void fn_sub_316BD0_00316bd0(p3fes::EEContext&);
void fn_sub_316E00_00316e00(p3fes::EEContext&);
void fn_sub_3174E0_003174e0(p3fes::EEContext&);
void fn_sub_3182D0_003182d0(p3fes::EEContext&);
void fn_sub_3185B0_003185b0(p3fes::EEContext&);
void fn_sub_3189F0_003189f0(p3fes::EEContext&);
void fn_sub_318B10_00318b10(p3fes::EEContext&);
void fn_sub_318FC0_00318fc0(p3fes::EEContext&);
void fn_sub_3210A0_003210a0(p3fes::EEContext&);
void fn_sub_3210C0_003210c0(p3fes::EEContext&);
void fn_sub_321120_00321120(p3fes::EEContext&);
void fn_sub_321130_00321130(p3fes::EEContext&);
void fn_sub_321180_00321180(p3fes::EEContext&);
void fn_sub_3211D0_003211d0(p3fes::EEContext&);
void fn_sub_322530_00322530(p3fes::EEContext&);
void fn_sub_3225D0_003225d0(p3fes::EEContext&);
void fn_sub_322660_00322660(p3fes::EEContext&);
void fn_sub_322D10_00322d10(p3fes::EEContext&);
void fn_sub_322D40_00322d40(p3fes::EEContext&);
void fn_sub_322DC0_00322dc0(p3fes::EEContext&);
void fn_sub_322F20_00322f20(p3fes::EEContext&);
void fn_sub_322FB0_00322fb0(p3fes::EEContext&);
void fn_sub_322FD0_00322fd0(p3fes::EEContext&);
void fn_sub_323240_00323240(p3fes::EEContext&);
void fn_sub_3233A0_003233a0(p3fes::EEContext&);
void fn_sub_323640_00323640(p3fes::EEContext&);
void fn_sub_3237C0_003237c0(p3fes::EEContext&);
void fn_sub_323860_00323860(p3fes::EEContext&);
void fn_sub_323880_00323880(p3fes::EEContext&);
void fn_sub_3238D0_003238d0(p3fes::EEContext&);
void fn_sub_323B90_00323b90(p3fes::EEContext&);
void fn_sub_323BF0_00323bf0(p3fes::EEContext&);
void fn_sub_323E10_00323e10(p3fes::EEContext&);
void fn_sub_323FB0_00323fb0(p3fes::EEContext&);
void fn_sub_324160_00324160(p3fes::EEContext&);
void fn_sub_324310_00324310(p3fes::EEContext&);
void fn_sub_3243D0_003243d0(p3fes::EEContext&);
void fn_sub_324470_00324470(p3fes::EEContext&);
void fn_sub_3244C0_003244c0(p3fes::EEContext&);
void fn_sub_3245B0_003245b0(p3fes::EEContext&);
void fn_sub_3245F0_003245f0(p3fes::EEContext&);
void fn_sub_324BD0_00324bd0(p3fes::EEContext&);
void fn_sub_3257E0_003257e0(p3fes::EEContext&);
void fn_sub_325920_00325920(p3fes::EEContext&);
void fn_sub_326490_00326490(p3fes::EEContext&);
void fn_sub_326740_00326740(p3fes::EEContext&);
void fn_sub_3269E0_003269e0(p3fes::EEContext&);
void fn_sub_326CF0_00326cf0(p3fes::EEContext&);
void fn_sub_326DB0_00326db0(p3fes::EEContext&);
void fn_sub_326E50_00326e50(p3fes::EEContext&);
void fn_sub_326F00_00326f00(p3fes::EEContext&);
void fn_sub_326F60_00326f60(p3fes::EEContext&);
void fn_sub_327090_00327090(p3fes::EEContext&);
void fn_sub_3271C0_003271c0(p3fes::EEContext&);
void fn_sub_327250_00327250(p3fes::EEContext&);
void fn_sub_3275D0_003275d0(p3fes::EEContext&);
void fn_sub_329490_00329490(p3fes::EEContext&);
void fn_sub_329740_00329740(p3fes::EEContext&);
void fn_sub_329890_00329890(p3fes::EEContext&);
void fn_sub_329A60_00329a60(p3fes::EEContext&);
void fn_sub_329BA0_00329ba0(p3fes::EEContext&);
void fn_sub_32A120_0032a120(p3fes::EEContext&);
void fn_sub_32A540_0032a540(p3fes::EEContext&);
void fn_sub_32A770_0032a770(p3fes::EEContext&);
void fn_sub_32A890_0032a890(p3fes::EEContext&);
void fn_sub_330100_00330100(p3fes::EEContext&);
void fn_sub_330190_00330190(p3fes::EEContext&);
void fn_sub_330BB0_00330bb0(p3fes::EEContext&);
void fn_sub_330C40_00330c40(p3fes::EEContext&);
void fn_sub_3315D0_003315d0(p3fes::EEContext&);
void fn_sub_331FD0_00331fd0(p3fes::EEContext&);
void fn_sub_332070_00332070(p3fes::EEContext&);
void fn_sub_3321D0_003321d0(p3fes::EEContext&);
void fn_sub_332210_00332210(p3fes::EEContext&);
void fn_sub_3322B0_003322b0(p3fes::EEContext&);
void fn_sub_3322F0_003322f0(p3fes::EEContext&);
void fn_sub_332370_00332370(p3fes::EEContext&);
void fn_sub_332470_00332470(p3fes::EEContext&);
void fn_sub_3325D0_003325d0(p3fes::EEContext&);
void fn_sub_332700_00332700(p3fes::EEContext&);
void fn_sub_332780_00332780(p3fes::EEContext&);
void fn_sub_332880_00332880(p3fes::EEContext&);
void fn_sub_332990_00332990(p3fes::EEContext&);
void fn_sub_332A30_00332a30(p3fes::EEContext&);
void fn_sub_332AC0_00332ac0(p3fes::EEContext&);
void fn_sub_332B60_00332b60(p3fes::EEContext&);
void fn_sub_332E10_00332e10(p3fes::EEContext&);
void fn_sub_332F10_00332f10(p3fes::EEContext&);
void fn_sub_3330E0_003330e0(p3fes::EEContext&);
void fn_sub_333300_00333300(p3fes::EEContext&);
void fn_sub_333420_00333420(p3fes::EEContext&);
void fn_sub_3338B0_003338b0(p3fes::EEContext&);
void fn_sub_333900_00333900(p3fes::EEContext&);
void fn_sub_333920_00333920(p3fes::EEContext&);
void fn_sub_333940_00333940(p3fes::EEContext&);
void fn_sub_333970_00333970(p3fes::EEContext&);
void fn_sub_3341C0_003341c0(p3fes::EEContext&);
void fn_sub_334220_00334220(p3fes::EEContext&);
void fn_sub_3342C0_003342c0(p3fes::EEContext&);
void fn_sub_337A60_00337a60(p3fes::EEContext&);
void fn_sub_337B70_00337b70(p3fes::EEContext&);
void fn_sub_337BB0_00337bb0(p3fes::EEContext&);
void fn_sub_337C10_00337c10(p3fes::EEContext&);
void fn_sub_337C40_00337c40(p3fes::EEContext&);
void fn_sub_337C90_00337c90(p3fes::EEContext&);
void fn_sub_337CF0_00337cf0(p3fes::EEContext&);
void fn_sub_337D40_00337d40(p3fes::EEContext&);
void fn_sub_337DD0_00337dd0(p3fes::EEContext&);
void fn_sub_337DE0_00337de0(p3fes::EEContext&);
void fn_sub_337DF0_00337df0(p3fes::EEContext&);
void fn_sub_337E00_00337e00(p3fes::EEContext&);
void fn_sub_337E90_00337e90(p3fes::EEContext&);
void fn_sub_337FD0_00337fd0(p3fes::EEContext&);
void fn_sub_338360_00338360(p3fes::EEContext&);
void fn_sub_338EA0_00338ea0(p3fes::EEContext&);
void fn_sub_339200_00339200(p3fes::EEContext&);
void fn_sub_3393D0_003393d0(p3fes::EEContext&);
void fn_sub_3397D0_003397d0(p3fes::EEContext&);
void fn_sub_3398C0_003398c0(p3fes::EEContext&);
void fn_sub_3399A0_003399a0(p3fes::EEContext&);
void fn_sub_33A220_0033a220(p3fes::EEContext&);
void fn_sub_33A3E0_0033a3e0(p3fes::EEContext&);
void fn_sub_33A4D0_0033a4d0(p3fes::EEContext&);
void fn_sub_33A560_0033a560(p3fes::EEContext&);
void fn_sub_33A5B0_0033a5b0(p3fes::EEContext&);
void fn_sub_33AF10_0033af10(p3fes::EEContext&);
void fn_sub_33BDA0_0033bda0(p3fes::EEContext&);
void fn_sub_33BE90_0033be90(p3fes::EEContext&);
void fn_sub_33BFA0_0033bfa0(p3fes::EEContext&);
void fn_sub_33C0A0_0033c0a0(p3fes::EEContext&);
void fn_sub_33C150_0033c150(p3fes::EEContext&);
void fn_sub_33C1A0_0033c1a0(p3fes::EEContext&);
void fn_sub_33C960_0033c960(p3fes::EEContext&);
void fn_sub_33CB20_0033cb20(p3fes::EEContext&);
void fn_sub_33CC10_0033cc10(p3fes::EEContext&);
void fn_sub_33CD20_0033cd20(p3fes::EEContext&);
void fn_sub_33CE10_0033ce10(p3fes::EEContext&);
void fn_sub_33CEB0_0033ceb0(p3fes::EEContext&);
void fn_sub_33CF00_0033cf00(p3fes::EEContext&);
void fn_sub_33D6D0_0033d6d0(p3fes::EEContext&);
void fn_sub_33D890_0033d890(p3fes::EEContext&);
void fn_sub_33D980_0033d980(p3fes::EEContext&);
void fn_sub_33DA90_0033da90(p3fes::EEContext&);
void fn_sub_33DB80_0033db80(p3fes::EEContext&);
void fn_sub_33DC20_0033dc20(p3fes::EEContext&);
void fn_sub_33DC70_0033dc70(p3fes::EEContext&);
void fn_sub_33E540_0033e540(p3fes::EEContext&);
void fn_sub_33F4A0_0033f4a0(p3fes::EEContext&);
void fn_sub_33F590_0033f590(p3fes::EEContext&);
void fn_sub_33F6A0_0033f6a0(p3fes::EEContext&);
void fn_sub_33F780_0033f780(p3fes::EEContext&);
void fn_sub_33F810_0033f810(p3fes::EEContext&);
void fn_sub_33F860_0033f860(p3fes::EEContext&);
void fn_sub_340100_00340100(p3fes::EEContext&);
void fn_sub_341F10_00341f10(p3fes::EEContext&);
void fn_sub_342480_00342480(p3fes::EEContext&);
void fn_sub_342550_00342550(p3fes::EEContext&);
void fn_sub_342990_00342990(p3fes::EEContext&);
void fn_sub_342A90_00342a90(p3fes::EEContext&);
void fn_sub_343410_00343410(p3fes::EEContext&);
void fn_sub_343790_00343790(p3fes::EEContext&);
void fn_sub_343860_00343860(p3fes::EEContext&);
void fn_sub_343C60_00343c60(p3fes::EEContext&);
void fn_sub_343D10_00343d10(p3fes::EEContext&);
void fn_sub_343D60_00343d60(p3fes::EEContext&);
void fn_sub_344720_00344720(p3fes::EEContext&);
void fn_sub_345CF0_00345cf0(p3fes::EEContext&);
void fn_sub_3461A0_003461a0(p3fes::EEContext&);
void fn_sub_346350_00346350(p3fes::EEContext&);
void fn_sub_3463C0_003463c0(p3fes::EEContext&);
void fn_sub_346460_00346460(p3fes::EEContext&);
void fn_sub_346530_00346530(p3fes::EEContext&);
void fn_sub_347100_00347100(p3fes::EEContext&);
void fn_sub_347170_00347170(p3fes::EEContext&);
void fn_sub_3472D0_003472d0(p3fes::EEContext&);
void fn_sub_347350_00347350(p3fes::EEContext&);
void fn_sub_3473B0_003473b0(p3fes::EEContext&);
void fn_sub_347CB0_00347cb0(p3fes::EEContext&);
void fn_sub_347FC0_00347fc0(p3fes::EEContext&);
void fn_sub_348030_00348030(p3fes::EEContext&);
void fn_sub_348090_00348090(p3fes::EEContext&);
void fn_sub_348340_00348340(p3fes::EEContext&);
void fn_sub_348760_00348760(p3fes::EEContext&);
void fn_sub_348BD0_00348bd0(p3fes::EEContext&);
void fn_sub_348DA0_00348da0(p3fes::EEContext&);
void fn_sub_348F30_00348f30(p3fes::EEContext&);
void fn_sub_349260_00349260(p3fes::EEContext&);
void fn_sub_349450_00349450(p3fes::EEContext&);
void fn_sub_349870_00349870(p3fes::EEContext&);
void fn_sub_349AF0_00349af0(p3fes::EEContext&);
void fn_sub_349ED0_00349ed0(p3fes::EEContext&);
void fn_sub_349FA0_00349fa0(p3fes::EEContext&);
void fn_sub_34A1D0_0034a1d0(p3fes::EEContext&);
void fn_sub_34A280_0034a280(p3fes::EEContext&);
void fn_sub_34A340_0034a340(p3fes::EEContext&);
void fn_sub_34A590_0034a590(p3fes::EEContext&);
void fn_sub_34A8C0_0034a8c0(p3fes::EEContext&);
void fn_sub_34A990_0034a990(p3fes::EEContext&);
void fn_sub_34A9C0_0034a9c0(p3fes::EEContext&);
void fn_sub_34ABC0_0034abc0(p3fes::EEContext&);
void fn_sub_34AC70_0034ac70(p3fes::EEContext&);
void fn_sub_34B1A0_0034b1a0(p3fes::EEContext&);
void fn_sub_34B320_0034b320(p3fes::EEContext&);
void fn_sub_34B3A0_0034b3a0(p3fes::EEContext&);
void fn_sub_34B600_0034b600(p3fes::EEContext&);
void fn_sub_34B6B0_0034b6b0(p3fes::EEContext&);
void fn_sub_34B830_0034b830(p3fes::EEContext&);
void fn_sub_34B8B0_0034b8b0(p3fes::EEContext&);
void fn_sub_34BB10_0034bb10(p3fes::EEContext&);
void fn_sub_34BBC0_0034bbc0(p3fes::EEContext&);
void fn_sub_34BC80_0034bc80(p3fes::EEContext&);
void fn_sub_34BCF0_0034bcf0(p3fes::EEContext&);
void fn_sub_34BD60_0034bd60(p3fes::EEContext&);
void fn_sub_34BDF0_0034bdf0(p3fes::EEContext&);
void fn_sub_34BEF0_0034bef0(p3fes::EEContext&);
void fn_sub_34BF10_0034bf10(p3fes::EEContext&);
void fn_sub_34BFC0_0034bfc0(p3fes::EEContext&);
void fn_sub_34C160_0034c160(p3fes::EEContext&);
void fn_sub_34C1B0_0034c1b0(p3fes::EEContext&);
void fn_sub_34C250_0034c250(p3fes::EEContext&);
void fn_sub_34C670_0034c670(p3fes::EEContext&);
void fn_sub_34C890_0034c890(p3fes::EEContext&);
void fn_sub_34C9B0_0034c9b0(p3fes::EEContext&);
void fn_sub_34D150_0034d150(p3fes::EEContext&);
void fn_sub_34D510_0034d510(p3fes::EEContext&);
void fn_sub_34D670_0034d670(p3fes::EEContext&);
void fn_sub_34D6F0_0034d6f0(p3fes::EEContext&);
void fn_sub_34D810_0034d810(p3fes::EEContext&);
void fn_sub_34D8A0_0034d8a0(p3fes::EEContext&);
void fn_sub_34D990_0034d990(p3fes::EEContext&);
void fn_sub_34E4C0_0034e4c0(p3fes::EEContext&);
void fn_sub_34E610_0034e610(p3fes::EEContext&);
void fn_sub_34E690_0034e690(p3fes::EEContext&);
void fn_sub_34E7C0_0034e7c0(p3fes::EEContext&);
void fn_sub_34E800_0034e800(p3fes::EEContext&);
void fn_sub_34E820_0034e820(p3fes::EEContext&);
void fn_sub_34E940_0034e940(p3fes::EEContext&);
void fn_sub_357E30_00357e30(p3fes::EEContext&);
void fn_sub_357FD0_00357fd0(p3fes::EEContext&);
void fn_sub_358030_00358030(p3fes::EEContext&);
void fn_sub_491EA0_00491ea0(p3fes::EEContext&);
void fn_sub_4933D0_004933d0(p3fes::EEContext&);
void fn_sub_494D50_00494d50(p3fes::EEContext&);
void fn_sub_4CB2F0_004cb2f0(p3fes::EEContext&);
void fn_sub_4CB750_004cb750(p3fes::EEContext&);
void fn_sub_4CB7F0_004cb7f0(p3fes::EEContext&);
void fn_sub_4D0F00_004d0f00(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace fx2;  // the named record offsets (fx2.h)

// 0x003397D0 sub_3397D0 -- 232 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 1, slot 0 [k10Streak1Init] ($a0 = the instance): locks the mesh geometry (vertices), clears all its
// vertices (12 bytes x vertex count), unlocks (re-instance when flagged) and marks every record free (word 0 = -1;
// records of 24 bytes).
void sub_3397D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003397d0
    enter(ctx, 36);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, 60);
    lw(s3, v0, 0);
    lw(s2, v0, 4);
    lw(v0, a0, 64);
    lw(s1, v0, 56);
    lw(v0, s2, 16);
    lw(a0, v0, 24);
    a1 = 2;
    jal(ctx, 0x339808u, gen::fn_geometryLock_00493370);
    lw(v0, s2, 16);
    lw(v0, v0, 24);
    lw(v0, v0, 92);
    lw(a0, v0, 20);
    lh(v1, s2, 8);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    a2 = sll(v0, 2);
    a1 = 0;
    jal(ctx, 0x339834u, gen::fn_memset_00521408);
    lw(v0, s2, 16);
    lw(s0, v0, 24);
    a0 = s0;
    jal(ctx, 0x339848u, gen::fn_sub_4933D0_004933d0);
    lhu(v1, s2, 0);
    v1 = v1 & 0x4;
    if (v1 != 0) {
        // 0x00339860
        charge(ctx, 3);
        lhu(v1, s0, 12);
        v1 = v1 | 0x1;
        sh(v1, s0, 12);
    }
    // 0x0033986c
    charge(ctx, 4);
    a1 = 0;
    a0 = si(-1);
    for (;;) {
        // 0x00339888
        charge(ctx, 4);
        v1 = slt(a1, s1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0033987c
        charge(ctx, 3);
        sw(a0, s3, 0);
        s3 = addiu(s3, 24);
        a1 = addiu(a1, 1);
    }
    // 0x00339898
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003398C0 sub_3398C0 -- 136 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 1, slot 1 [k10Streak1Create] ($a0 = the kind parameters; returns the kind object): one RwMalloc
// block of 16 + 24 x count bytes (+0 the records at +16, +8 the block) and its mesh +4 (sub_3233A0: count 3 x 5,
// layout 0x69BD60, vertex size 72).
void sub_3398C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003398c0
    enter(ctx, 34);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 56);
    v0 = sll(s0, 1);
    v0 = addu(v0, s0);
    v0 = sll(v0, 3);
    a0 = addiu(v0, 16);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x3398F0u, v0.u());
    s1 = v0;
    v1 = addiu(v0, 16);
    sw(v1, v0, 0);
    sw(v0, v0, 8);
    a0 = s0 & 0xFFFF;
    a1 = 3;
    a2 = 5;
    a3 = 0x6A0000;
    a3 = addiu(a3, -17056);  // &0x69BD60
    t0 = 72;
    jal(ctx, 0x339920u, gen::fn_sub_3233A0_003233a0);
    sw(v0, s1, 4);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003399A0 sub_3399A0 -- 2164 bytes; frame 0x190: ra sp+0xC0, fp sp+0xB0 (sq), s7 sp+0xA0 (sq), s6 sp+0x90 (sq), s5 sp+0x80 (sq), s4 sp+0x70 (sq), s3 sp+0x60 (sq), s2 sp+0x50 (sq), s1 sp+0x40 (sq), s0 sp+0x30 (sq), f28 sp+0x20, f27 sp+0x1C, f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 1, slot 4 [k10Streak1Update] ($a0 = the instance): within the lifetime. The particle life (+76) with
// its fade-in / fade-out fractions (+68 / +72, reversed by a kind flag) gives the alpha ramp; unless the once flag
// (+85) holds the emission after frame 0, the re-emission period is +80. The mesh is locked (vertices + prelight) and
// each record runs: a free one is (re-)emitted with random values from the parameters' ranges (sub_358030 = random
// float, sub_357FD0 = random int: angle, length +116 x (1 - +120 rand), speed +108 / +112, width +96 / +100 with
// +104) and a random start age; a live one ages, its colour is blended from colour A (+88) to colour B (+92) with the
// alpha ramp, and its three-vertex streak rows are rebuilt (cosf / sinf of its angle, VU0 scaling) into the mesh
// vertices; then the mesh is unlocked (re-instance when flagged).
void sub_3399A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26}, f27{ctx, 27}, f28{ctx, 28};
    Vf vf0{ctx, 0}, vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11}, vf12{ctx, 12};
    // 0x003399a0
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x190);
    sd(ra, sp, 0xC0);
    sq(fp, sp, 0xB0);
    sq(s7, sp, 0xA0);
    sq(s6, sp, 0x90);
    sq(s5, sp, 0x80);
    sq(s4, sp, 0x70);
    sq(s3, sp, 0x60);
    sq(s2, sp, 0x50);
    sq(s1, sp, 0x40);
    sq(s0, sp, 0x30);
    swc1(f28, sp, 0x20);
    swc1(f27, sp, 0x1C);
    swc1(f26, sp, 0x18);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(s1, a0, 64);
    lw(v1, s1, kSpLifetime);
    lw(a1, a0, 52);
    at = sltu(v1, a1);
    if (at != 0) {
        // 0x00339a08
        charge(ctx, 2);
        if (v1 == 0) {
            goto L_00339a10;
        }
        // 0x0033a1bc (the shared epilogue, written out on this path)
        charge(ctx, 22);
        ld(ra, sp, 0xC0);
        lq(fp, sp, 0xB0);
        lq(s7, sp, 0xA0);
        lq(s6, sp, 0x90);
        lq(s5, sp, 0x80);
        lq(s4, sp, 0x70);
        lq(s3, sp, 0x60);
        lq(s2, sp, 0x50);
        lq(s1, sp, 0x40);
        lq(s0, sp, 0x30);
        lwc1(f28, sp, 0x20);
        lwc1(f27, sp, 0x1C);
        lwc1(f26, sp, 0x18);
        lwc1(f25, sp, 0x14);
        lwc1(f24, sp, 0x10);
        lwc1(f23, sp, 0xC);
        lwc1(f22, sp, 0x8);
        lwc1(f21, sp, 0x4);
        lwc1(f20, sp, 0x0);
        sp = addiu(sp, 0x190);
        return;
    }
L_00339a10:
    charge(ctx, 8);
    lw(v1, a0, 60);
    lw(s4, v1, 0);
    lw(fp, v1, 4);
    lw(v1, s1, kSpCount);
    sq(v1, sp, 0x100);
    lw(s0, s1, kSpLife);
    if (s0 != 0) {
        // 0x00339a30
        charge(ctx, 3);
        lbu(v0, s1, kSpOnce);
        if (v0 != 0) {
            // 0x00339a3c
            charge(ctx, 2);
            if (a1 != 0) {
                goto L_00339a58;
            }
            // 0x00339a44
            charge(ctx, 5);
            v0 = 1;
            sw(v0, sp, 0x110);
            paddub(s7, v1, zero);
            goto L_00339a60;
        }
    L_00339a58:
        charge(ctx, 2);
        sw(zero, sp, 0x110);
        lw(s7, s1, kSpRespawn);
    L_00339a60:
        charge(ctx, 79);
        lw(v0, fp, 0x10);
        lw(a0, v0, 24);
        a1 = 10;
        jal(ctx, 0x339A6Cu, gen::fn_geometryLock_00493370);
        lw(v0, fp, 0x10);
        lw(v1, v0, 24);
        lw(v0, v1, 92);
        lw(s3, v0, 20);
        lw(s2, v1, 48);
        mtc1(zero, f23);
        sw(zero, sp, 0x154);
        sw(zero, sp, 0x15C);
        v0 = 0xFF0000;
        v1 = v0 | 0xFFFF;  // &0xFFFFFF
        lw(v0, s1, kSpColourA);
        v0 = dsll32(v0, 8);
        v0 = dsrl32(v0, 8);
        sw(v0, sp, 0x18C);
        v0 = addiu(sp, 0x18C);
        lwc1(f0, gp, -32420);  // 0x7CAE4C
        lw(v0, v0, 0);
        pextlb(v0, zero, v0);
        pextlh(v0, zero, v0);
        qmtc2(v0, vf10, false);  // qmtc2
        vitof0(0xF, vf10, vf10);  // vitof0.xyzw
        mfc1(v0, f0);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        v0 = addiu(sp, 0x170);
        sqc2(vf10, v0, 0);
        lw(v0, s1, kSpColourB);
        v0 = v0 & v1;
        sw(v0, sp, 0x188);
        v0 = addiu(sp, 0x188);
        lw(v0, v0, 0);
        pextlb(v0, zero, v0);
        pextlh(v0, zero, v0);
        qmtc2(v0, vf10, false);  // qmtc2
        vitof0(0xF, vf10, vf10);  // vitof0.xyzw
        mfc1(v0, f0);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        v0 = addiu(sp, 0x160);
        sqc2(vf10, v0, 0);
        mtc1(s0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, s1, kSpFadeIn);
        mul_s(f0, f0, f1);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        sq(v0, sp, 0xF0);
        lwc1(f0, s1, kSpFadeOut);
        mul_s(f0, f0, f1);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        sq(v0, sp, 0xE0);
        lwc1(f27, s1, 124);
        lbu(v0, s1, kSpMode);
        sq(v0, sp, 0xD0);
        s6 = 0;
        lwc1(f26, gp, -32352);  // 0x7CAE90
        v0 = 0x3F800000;
        mtc1(v0, f25);
        v0 = lui(0xBF80);
        mtc1(v0, f24);
        v0 = 0x3F000000;
        mtc1(v0, f22);
        v0 = 0x437F0000;
        mtc1(v0, f21);
        v0 = 0x43000000;
        mtc1(v0, f20);
        for (;;) {
            // 0x0033a17c
            charge(ctx, 4);
            lq(v0, sp, 0x100);
            v0 = slt(s6, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00339b9c
            charge(ctx, 4);
            lw(s5, s4, 0);
            v0 = si(-2);
            if (s5 != v0) {
                // 0x00339bac
                charge(ctx, 3);
                v0 = si(-1);
                if (s5 != v0) {
                    // 0x00339cd0
                    charge(ctx, 3);
                    v0 = slt(s5, s0);
                    if (v0 != 0) {
                        // 0x00339d48
                        charge(ctx, 7);
                        mtc1(s5, f0);
                        cvt_s_w(f3, f0);
                        lwc1(f2, s4, 4);
                        c_le_s(f2, f23);
                        if (cond(ctx)) {
                            // 0x00339d84
                            charge(ctx, 6);
                            mul_s(f1, f27, f3);
                            mtc1(zero, f0);
                            adda_s(f0, f2);
                            msub_s(f0, f22, f1);
                            mul_s(f28, f3, f0);
                        } else {
                            // 0x00339d64
                            charge(ctx, 8);
                            mul_s(f1, f27, f3);
                            mtc1(zero, f0);
                            adda_s(f0, f2);
                            madd_s(f0, f22, f1);
                            mul_s(f28, f3, f0);
                        }
                        // 0x00339d9c
                        charge(ctx, 119);
                        lwc1(f0, s4, 8);
                        add_s(f28, f28, f0);
                        v0 = 0x6A0000;
                        v0 = addiu(v0, -15200);  // &0x69C4A0
                        lqc2(vf10, v0, 0);  // 0x69C4A0
                        vmove(0xF, vf11, vf10);  // vmove.xyzw
                        lw(v0, s4, 12);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        v0 = addiu(sp, 0x140);
                        sqc2(vf10, v0, 0);
                        vmove(0xF, vf10, vf11);  // vmove.xyzw
                        lw(v0, s4, 16);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        lw(v0, s4, 20);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
                        v0 = addiu(sp, 0x130);
                        sqc2(vf10, v0, 0);
                        v0 = addiu(sp, 0x120);
                        sqc2(vf11, v0, 0);
                        mov_s(f12, f28);
                        jal(ctx, 0x339E04u, gen::fn_cosf_0052e6d8);
                        swc1(f0, sp, 0x150);
                        mov_s(f12, f28);
                        jal(ctx, 0x339E14u, gen::fn_sinf_0052e878);
                        swc1(f0, sp, 0x158);
                        v0 = addiu(sp, 0x150);
                        lqc2(vf10, v0, 0);
                        vmove(0xF, vf12, vf10);  // vmove.xyzw
                        qmfc2(v0, vf10, false);  // qmfc2
                        mtc1(v0, f1);
                        qmfc2(v0, vf10, false);  // qmfc2
                        pexew(v0, v0);
                        mtc1(v0, f0);
                        mfc1(v0, f0);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vadd_bc(0x8, vf10, vf0, vf2, 0);  // vaddx.x
                        neg_s(f0, f1);
                        mfc1(v0, f0);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vadd_bc(0x2, vf10, vf0, vf2, 0);  // vaddx.z
                        vmove(0xF, vf11, vf10);  // vmove.xyzw
                        v1 = addiu(sp, 0x130);
                        lqc2(vf10, v1, 0);
                        vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
                        sqc2(vf10, v1, 0);
                        a0 = addiu(sp, 0x120);
                        lqc2(vf10, a0, 0);
                        vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
                        sqc2(vf10, a0, 0);
                        vmove(0xF, vf10, vf12);  // vmove.xyzw
                        v0 = addiu(sp, 0x140);
                        lqc2(vf11, v0, 0);
                        vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
                        vmove(0xF, vf12, vf10);  // vmove.xyzw
                        lqc2(vf10, v1, 0);
                        vmove(0xF, vf11, vf10);  // vmove.xyzw
                        v1 = 0x6A0000;
                        v1 = addiu(v1, -15152);  // &0x69C4D0
                        sqc2(vf10, v1, 0);  // 0x69C4D0
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15152);  // 0x69C4D0
                        swc1(f0, s3, 24);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15148);  // 0x69C4D4
                        swc1(f0, s3, 28);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15144);  // 0x69C4D8
                        swc1(f0, s3, 32);
                        vsub(0xE, vf11, vf0, vf11);  // vsub.xyz
                        sqc2(vf11, v1, 0);  // 0x69C4D0
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15152);  // 0x69C4D0
                        swc1(f0, s3, 48);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15148);  // 0x69C4D4
                        swc1(f0, s3, 52);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15144);  // 0x69C4D8
                        swc1(f0, s3, 56);
                        lqc2(vf10, a0, 0);
                        vmove(0xF, vf11, vf10);  // vmove.xyzw
                        vadd(0xF, vf10, vf10, vf12);  // vadd.xyzw
                        vsub(0xE, vf11, vf0, vf11);  // vsub.xyz
                        sqc2(vf10, v1, 0);  // 0x69C4D0
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15152);  // 0x69C4D0
                        swc1(f0, s3, 0);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15148);  // 0x69C4D4
                        swc1(f0, s3, 4);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15144);  // 0x69C4D8
                        swc1(f0, s3, 8);
                        vadd(0xF, vf11, vf11, vf12);  // vadd.xyzw
                        sqc2(vf11, v1, 0);  // 0x69C4D0
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15152);  // 0x69C4D0
                        swc1(f0, s3, 12);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15148);  // 0x69C4D4
                        swc1(f0, s3, 16);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15144);  // 0x69C4D8
                        swc1(f0, s3, 20);
                        lq(v0, sp, 0xF0);
                        at = slt(s5, v0);
                        if (at == 0) {
                            // 0x00339fa8
                            charge(ctx, 4);
                            lq(v0, sp, 0xE0);
                            at = slt(v0, s5);
                            if (at == 0) {
                                // 0x00339ff4
                                charge(ctx, 1);
                                mov_s(f0, f25);
                            } else {
                                // 0x00339fb8
                                charge(ctx, 15);
                                v0 = subu(s0, s5);
                                mtc1(v0, f0);
                                cvt_s_w(f1, f0);
                                lq(v0, sp, 0xE0);
                                v0 = subu(s0, v0);
                                mtc1(v0, f0);
                                cvt_s_w(f0, f0);
                                div_s(f0, f1, f0);
                            }
                        } else {
                            // 0x00339f78
                            charge(ctx, 12);
                            mtc1(s5, f0);
                            cvt_s_w(f1, f0);
                            mtc1(v0, f0);
                            cvt_s_w(f0, f0);
                            div_s(f0, f1, f0);
                        }
                        // 0x00339ff8
                        charge(ctx, 45);
                        v0 = 0x6A0000;
                        v0 = addiu(v0, -15200);  // &0x69C4A0
                        lqc2(vf11, v0, 0);  // 0x69C4A0
                        mfc1(v0, f0);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
                        v0 = addiu(sp, 0x160);
                        lqc2(vf10, v0, 0);
                        vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
                        mfc1(v0, f21);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
                        qmfc2(v0, vf10, false);  // qmfc2
                        ppach(v0, zero, v0);
                        ppacb(v0, zero, v0);
                        sw(v0, sp, 0x180);
                        lw(v0, sp, 0x180);
                        sw(v0, s2, 0);
                        lbu(a1, s2, 0);
                        lbu(a0, s2, 1);
                        lbu(v1, s2, 2);
                        lbu(v0, s2, 3);
                        sb(a1, s2, 4);
                        sb(a0, s2, 5);
                        sb(v1, s2, 6);
                        sb(v0, s2, 7);
                        v0 = addiu(sp, 0x170);
                        lqc2(vf10, v0, 0);
                        vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
                        mfc1(v0, f21);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
                        qmfc2(v0, vf10, false);  // qmfc2
                        ppach(v0, zero, v0);
                        ppacb(v0, zero, v0);
                        sw(v0, sp, 0x184);
                        lw(v1, sp, 0x184);
                        v0 = s6 & 0x1;
                        if (v0 == 0) {
                            // 0x0033a10c
                            charge(ctx, 10);
                            v0 = 0x40000000;
                            v0 = v1 | v0;
                            sw(v0, s2, 12);
                            mul_s(f1, f21, f0);
                            v0 = 0x4F000000;
                            mtc1(v0, f0);
                            c_le_s(f0, f1);
                            if (cond(ctx)) {
                                // 0x0033a144
                                charge(ctx, 5);
                                sub_s(f0, f1, f0);
                                cvt_w_s(f0, f0);
                                mfc1(v1, f0);
                                v0 = lui(0x8000);
                                v1 = v1 | v0;
                            } else {
                                // 0x0033a134
                                charge(ctx, 4);
                                cvt_w_s(f0, f1);
                                mfc1(v1, f0);
                            }
                            // 0x0033a158
                            charge(ctx, 3);
                            v0 = sll(v1, 24);
                            sw(v0, s2, 8);
                            sw(v0, s2, 16);
                        } else {
                            // 0x0033a0ac
                            charge(ctx, 10);
                            v0 = lui(0xFF00);
                            v0 = v1 | v0;
                            sw(v0, s2, 12);
                            mul_s(f1, f20, f0);
                            v0 = 0x4F000000;
                            mtc1(v0, f0);
                            c_le_s(f0, f1);
                            if (cond(ctx)) {
                                // 0x0033a0e4
                                charge(ctx, 5);
                                sub_s(f0, f1, f0);
                                cvt_w_s(f0, f0);
                                mfc1(v1, f0);
                                v0 = lui(0x8000);
                                v1 = v1 | v0;
                            } else {
                                // 0x0033a0d4
                                charge(ctx, 4);
                                cvt_w_s(f0, f1);
                                mfc1(v1, f0);
                            }
                            // 0x0033a0f8
                            charge(ctx, 5);
                            v0 = sll(v1, 24);
                            sw(v0, s2, 8);
                            sw(v0, s2, 16);
                        }
                        // 0x0033a164
                        charge(ctx, 2);
                        v0 = addiu(s5, 1);
                        sw(v0, s4, 0);
                    } else {
                        // 0x00339cdc
                        charge(ctx, 3);
                        v1 = 0;
                        for (;;) {
                            // 0x00339d14
                            charge(ctx, 3);
                            v0 = slti(v1, 5);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x00339ce8
                            charge(ctx, 11);
                            v0 = sll(v1, 1);
                            v0 = addu(v0, v1);
                            v0 = sll(v0, 2);
                            v0 = addu(s3, v0);
                            swc1(f23, v0, 0);
                            swc1(f23, v0, 4);
                            swc1(f23, v0, 8);
                            v0 = sll(v1, 2);
                            v0 = addu(s2, v0);
                            sw(zero, v0, 0);
                            v1 = addiu(v1, 1);
                        }
                        // 0x00339d20
                        charge(ctx, 3);
                        lq(v0, sp, 0xD0);
                        if (v0 == 0) {
                            // 0x00339d38
                            charge(ctx, 1);
                            v0 = si(-2);
                        } else {
                            // 0x00339d2c
                            charge(ctx, 3);
                            v0 = si(-1);
                        }
                        // 0x00339d3c
                        charge(ctx, 3);
                        sw(v0, s4, 0);
                    }
                } else {
                    // 0x00339bb8
                    charge(ctx, 2);
                    if (s7 != 0) {
                        // 0x00339bc0
                        charge(ctx, 23);
                        a0 = 0;
                        jal(ctx, 0x339BC4u, gen::fn_sub_358030_00358030);
                        mul_s(f0, f26, f0);
                        swc1(f0, s4, 8);
                        lwc1(f28, s1, 120);
                        a0 = 0;
                        jal(ctx, 0x339BDCu, gen::fn_sub_358030_00358030);
                        sub_s(f2, f25, f28);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f28, f0);
                        lwc1(f0, s1, 116);
                        mul_s(f0, f0, f1);
                        swc1(f0, s4, 4);
                        a0 = 0;
                        jal(ctx, 0x339C08u, gen::fn_sub_357FD0_00357fd0);
                        v0 = v0 & 0x1;
                        if (v0 != 0) {
                            // 0x00339c1c
                            charge(ctx, 3);
                            lwc1(f0, s4, 4);
                            mul_s(f0, f0, f24);
                            swc1(f0, s4, 4);
                        }
                        // 0x00339c28
                        charge(ctx, 30);
                        lwc1(f28, s1, 112);
                        a0 = 0;
                        jal(ctx, 0x339C30u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f25, f28);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f28, f0);
                        lwc1(f0, s1, 108);
                        mul_s(f0, f0, f1);
                        swc1(f0, s4, 12);
                        lwc1(f28, s1, 104);
                        a0 = 0;
                        jal(ctx, 0x339C60u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f25, f28);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f28, f0);
                        lwc1(f0, s1, 96);
                        mul_s(f0, f0, f1);
                        swc1(f0, s4, 16);
                        lwc1(f0, s1, 100);
                        mul_s(f0, f0, f1);
                        swc1(f0, s4, 20);
                        lw(v0, sp, 0x110);
                        if (v0 == 0) {
                            // 0x00339cc0
                            charge(ctx, 1);
                            sw(zero, s4, 0);
                        } else {
                            // 0x00339ca0
                            charge(ctx, 8);
                            a0 = 0;
                            jal(ctx, 0x339CA4u, gen::fn_sub_357FD0_00357fd0);
                            divu(v0, s0);
                            mfhi(v0);
                            sw(v0, s4, 0);
                        }
                        // 0x00339cc4
                        charge(ctx, 3);
                        s7 = addiu(s7, -1);
                    }
                }
            }
            // 0x0033a16c
            charge(ctx, 4);
            s6 = addiu(s6, 1);
            s4 = addiu(s4, 24);
            s3 = addiu(s3, 60);
            s2 = addiu(s2, 20);
        }
        // 0x0033a18c
        charge(ctx, 9);
        lw(v0, fp, 0x10);
        lw(s0, v0, 24);
        a0 = s0;
        jal(ctx, 0x33A198u, gen::fn_sub_4933D0_004933d0);
        lhu(v1, fp, 0x0);
        v1 = v1 & 0x4;
        if (v1 != 0) {
            // 0x0033a1b0
            charge(ctx, 3);
            lhu(v1, s0, 12);
            v1 = v1 | 0x1;
            sh(v1, s0, 12);
        }
    }
    // 0x0033a1bc (the shared epilogue, written out on this path)
    charge(ctx, 22);
    ld(ra, sp, 0xC0);
    lq(fp, sp, 0xB0);
    lq(s7, sp, 0xA0);
    lq(s6, sp, 0x90);
    lq(s5, sp, 0x80);
    lq(s4, sp, 0x70);
    lq(s3, sp, 0x60);
    lq(s2, sp, 0x50);
    lq(s1, sp, 0x40);
    lq(s0, sp, 0x30);
    lwc1(f28, sp, 0x20);
    lwc1(f27, sp, 0x1C);
    lwc1(f26, sp, 0x18);
    lwc1(f25, sp, 0x14);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x190);
}

// 0x0033A220 sub_33A220 -- 448 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 1, slot 5 [k10Streak1Draw] ($a0 = the instance): within the lifetime (+52 of the parameters vs the
// frame +52), colour = instance colour (+48) x the colour track at the frame (sub_32A120 on +36), on VU0 (bytes ->
// floats / 255, multiply, x 255, back to bytes) into the mesh's material colour (alpha 255 written as 254 and
// restored); the mesh is placed at the instance position / rotation / scale (sub_3238D0), its additive bit follows
// +86 and it is queued on the layer +40 (sub_323860). Every class-10 kind's draw is this body.
void sub_33A220(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    Vf vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x0033a220
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(v1, a0, 60);
    lw(s1, a0, 64);
    lw(s0, v1, 4);
    lw(a2, a0, 52);
    lw(a3, s1, kSpLifetime);
    at = sltu(a3, a2);
    if (at != 0) {
        // 0x0033a258
        charge(ctx, 2);
        if (a3 == 0) {
            goto L_0033a260;
        }
        // 0x0033a3c4 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_0033a260:
    charge(ctx, 45);
    a0 = s1;
    a1 = addiu(s1, 36);
    jal(ctx, 0x33A268u, gen::fn_sub_32A120_0032a120);
    v1 = v0;
    lw(v0, s2, 48);
    sw(v0, sp, 0x48);
    v0 = addiu(sp, 0x48);
    lwc1(f0, gp, -32420);  // 0x7CAE4C
    lw(v0, v0, 0);
    pextlb(v0, zero, v0);
    pextlh(v0, zero, v0);
    qmtc2(v0, vf10, false);  // qmtc2
    vitof0(0xF, vf10, vf10);  // vitof0.xyzw
    mfc1(v0, f0);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vmove(0xF, vf11, vf10);  // vmove.xyzw
    sw(v1, sp, 0x44);
    v0 = addiu(sp, 0x44);
    lw(v0, v0, 0);
    pextlb(v0, zero, v0);
    pextlh(v0, zero, v0);
    qmtc2(v0, vf10, false);  // qmtc2
    vitof0(0xF, vf10, vf10);  // vitof0.xyzw
    mfc1(v0, f0);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
    v0 = 0x437F0000;
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
    qmfc2(v0, vf10, false);  // qmfc2
    ppach(v0, zero, v0);
    ppacb(v0, zero, v0);
    sw(v0, sp, 0x40);
    lw(v0, sp, 0x40);
    sw(v0, sp, 0x4C);
    lbu(v0, sp, 0x4F);
    a3 = 255;
    if (v0 == a3) {
        // 0x0033a340
        charge(ctx, 12);
        v0 = 254;
        sb(v0, sp, 0x4F);
        lw(a2, s0, 20);
        lbu(a1, sp, 0x4C);
        lbu(a0, sp, 0x4D);
        lbu(v1, sp, 0x4E);
        lbu(v0, sp, 0x4F);
        sb(a1, a2, 4);
        sb(a0, a2, 5);
        sb(v1, a2, 6);
        sb(v0, a2, 7);
        sb(a3, sp, 0x4F);
    } else {
        // 0x0033a314
        charge(ctx, 11);
        lw(a2, s0, 20);
        lbu(a1, sp, 0x4C);
        lbu(a0, sp, 0x4D);
        lbu(v1, sp, 0x4E);
        lbu(v0, sp, 0x4F);
        sb(a1, a2, 4);
        sb(a0, a2, 5);
        sb(v1, a2, 6);
        sb(v0, a2, 7);
    }
    // 0x0033a370
    charge(ctx, 9);
    a0 = s0;
    a1 = s2;
    a2 = addiu(s2, 16);
    a3 = addiu(s2, 32);
    jal(ctx, 0x33A380u, gen::fn_sub_3238D0_003238d0);
    lbu(v0, s1, kSpAdditive);
    if (v0 == 0) {
        // 0x0033a3a8
        charge(ctx, 3);
        lhu(v0, s0, 0);
        v0 = v0 & 0xFFFE;
        sh(v0, s0, 0);
    } else {
        // 0x0033a394
        charge(ctx, 5);
        lhu(v0, s0, 0);
        v0 = v0 | 0x1;
        sh(v0, s0, 0);
    }
    // 0x0033a3b4
    charge(ctx, 4);
    lhu(a1, s1, kSpLayer);
    a0 = s0;
    jal(ctx, 0x33A3BCu, gen::fn_sub_323860_00323860);
    // 0x0033a3c4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0033A3E0 sub_33A3E0 -- 232 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 2, slot 0 [k10Streak2Init] ($a0 = the instance): locks the mesh geometry (vertices), clears all its
// vertices (12 bytes x vertex count), unlocks (re-instance when flagged) and marks every record free (word 0 = -1;
// records of 28 bytes).
void sub_33A3E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0033a3e0
    enter(ctx, 36);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, 60);
    lw(s3, v0, 0);
    lw(s2, v0, 4);
    lw(v0, a0, 64);
    lw(s1, v0, 56);
    lw(v0, s2, 16);
    lw(a0, v0, 24);
    a1 = 2;
    jal(ctx, 0x33A418u, gen::fn_geometryLock_00493370);
    lw(v0, s2, 16);
    lw(v0, v0, 24);
    lw(v0, v0, 92);
    lw(a0, v0, 20);
    lh(v1, s2, 8);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    a2 = sll(v0, 2);
    a1 = 0;
    jal(ctx, 0x33A444u, gen::fn_memset_00521408);
    lw(v0, s2, 16);
    lw(s0, v0, 24);
    a0 = s0;
    jal(ctx, 0x33A458u, gen::fn_sub_4933D0_004933d0);
    lhu(v1, s2, 0);
    v1 = v1 & 0x4;
    if (v1 != 0) {
        // 0x0033a470
        charge(ctx, 3);
        lhu(v1, s0, 12);
        v1 = v1 | 0x1;
        sh(v1, s0, 12);
    }
    // 0x0033a47c
    charge(ctx, 4);
    a1 = 0;
    a0 = si(-1);
    for (;;) {
        // 0x0033a498
        charge(ctx, 4);
        v1 = slt(a1, s1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0033a48c
        charge(ctx, 3);
        sw(a0, s3, 0);
        s3 = addiu(s3, 28);
        a1 = addiu(a1, 1);
    }
    // 0x0033a4a8
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0033A4D0 sub_33A4D0 -- 136 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 2, slot 1 [k10Streak2Create] ($a0 = the kind parameters; returns the kind object): one RwMalloc
// block of 16 + 28 x count bytes (+0 the records at +16, +8 the block) and its mesh +4 (sub_3233A0: count 12 x 13,
// layout 0x69BD80, vertex size 72).
void sub_33A4D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0033a4d0
    enter(ctx, 34);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 56);
    v0 = sll(s0, 3);
    v0 = subu(v0, s0);
    v0 = sll(v0, 2);
    a0 = addiu(v0, 16);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x33A500u, v0.u());
    s1 = v0;
    v1 = addiu(v0, 16);
    sw(v1, v0, 0);
    sw(v0, v0, 8);
    a0 = s0 & 0xFFFF;
    a1 = 12;
    a2 = 13;
    a3 = 0x6A0000;
    a3 = addiu(a3, -17024);  // &0x69BD80
    t0 = 72;
    jal(ctx, 0x33A530u, gen::fn_sub_3233A0_003233a0);
    sw(v0, s1, 4);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0033A560 sub_33A560 -- 68 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 2, slot 2 [k10Streak2Destroy] ($a0 = the kind object): destroys the mesh (+4, sub_3237C0
// [fxMeshDestroy]) and frees the block (+8, RwFree 0x96017C).
void sub_33A560(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0033a560
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, kKoMesh);
    jal(ctx, 0x33A574u, gen::fn_sub_3237C0_003237c0);
    lw(a0, s0, 8);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x33A588u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0033A5B0 sub_33A5B0 -- 2392 bytes; frame 0x1B0: ra sp+0xB0, fp sp+0xA0 (sq), s7 sp+0x90 (sq), s6 sp+0x80 (sq), s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f27 sp+0x1C, f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 2, slot 4 [k10Streak2Update] ($a0 = the instance): within the lifetime. The particle life (+76) with
// its fade-in / fade-out fractions (+68 / +72, reversed by a kind flag) gives the alpha ramp; unless the once flag
// (+85) holds the emission after frame 0, the re-emission period is +80. The mesh is locked (vertices + prelight) and
// each record runs: a free one is (re-)emitted with random values from the parameters' ranges (sub_358030 = random
// float, sub_357FD0 = random int: angles, speeds +108 / +116 / +124 with their randomness, width +96 with +104; the
// fade fractions swap with the flag +136) and a random start age; a live one ages, its colour is blended from colour
// A (+88) to colour B (+92) with the alpha ramp, and its twelve-segment streaks are rebuilt (cosf / sinf of its
// angle, VU0 scaling) into the mesh vertices; then the mesh is unlocked (re-instance when flagged).
void sub_33A5B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26}, f27{ctx, 27};
    Vf vf0{ctx, 0}, vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11}, vf12{ctx, 12};
    // 0x0033a5b0
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1B0);
    sd(ra, sp, 0xB0);
    sq(fp, sp, 0xA0);
    sq(s7, sp, 0x90);
    sq(s6, sp, 0x80);
    sq(s5, sp, 0x70);
    sq(s4, sp, 0x60);
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f27, sp, 0x1C);
    swc1(f26, sp, 0x18);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(s1, a0, 64);
    lw(v1, s1, kSpLifetime);
    lw(a1, a0, 52);
    at = sltu(v1, a1);
    if (at != 0) {
        // 0x0033a614
        charge(ctx, 2);
        if (v1 == 0) {
            goto L_0033a61c;
        }
        // 0x0033aeb4 (the shared epilogue, written out on this path)
        charge(ctx, 21);
        ld(ra, sp, 0xB0);
        lq(fp, sp, 0xA0);
        lq(s7, sp, 0x90);
        lq(s6, sp, 0x80);
        lq(s5, sp, 0x70);
        lq(s4, sp, 0x60);
        lq(s3, sp, 0x50);
        lq(s2, sp, 0x40);
        lq(s1, sp, 0x30);
        lq(s0, sp, 0x20);
        lwc1(f27, sp, 0x1C);
        lwc1(f26, sp, 0x18);
        lwc1(f25, sp, 0x14);
        lwc1(f24, sp, 0x10);
        lwc1(f23, sp, 0xC);
        lwc1(f22, sp, 0x8);
        lwc1(f21, sp, 0x4);
        lwc1(f20, sp, 0x0);
        sp = addiu(sp, 0x1B0);
        return;
    }
L_0033a61c:
    charge(ctx, 8);
    lw(v1, a0, 60);
    lw(s4, v1, 0);
    lw(s7, v1, 4);
    lw(v1, s1, kSpCount);
    sw(v1, sp, 0x110);
    lw(s0, s1, kSpLife);
    if (s0 != 0) {
        // 0x0033a63c
        charge(ctx, 3);
        lbu(v0, s1, 136);
        if (v0 == 0) {
            // 0x0033a6ac
            charge(ctx, 19);
            sw(zero, sp, 0xEC);
            sw(s0, sp, 0xE8);
            v0 = 1;
            sw(v0, sp, 0xD0);
            mtc1(s0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, s1, kSpFadeIn);
            mul_s(f0, f0, f1);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            sw(v0, sp, 0x100);
            lwc1(f0, s1, kSpFadeOut);
            mul_s(f0, f0, f1);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            sw(v0, sp, 0xF0);
        } else {
            // 0x0033a648
            charge(ctx, 25);
            sw(s0, sp, 0xEC);
            sw(zero, sp, 0xE8);
            v0 = si(-1);
            sw(v0, sp, 0xD0);
            v0 = 0x3F800000;
            mtc1(v0, f3);
            lwc1(f0, s1, kSpFadeOut);
            sub_s(f2, f3, f0);
            mtc1(s0, f0);
            cvt_s_w(f1, f0);
            mul_s(f0, f2, f1);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            sw(v0, sp, 0x100);
            lwc1(f0, s1, kSpFadeIn);
            sub_s(f0, f3, f0);
            mul_s(f0, f0, f1);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            sw(v0, sp, 0xF0);
        }
        // 0x0033a6f8
        charge(ctx, 3);
        lbu(v0, s1, kSpOnce);
        if (v0 != 0) {
            // 0x0033a704
            charge(ctx, 2);
            if (a1 != 0) {
                goto L_0033a720;
            }
            // 0x0033a70c
            charge(ctx, 5);
            v0 = 1;
            sw(v0, sp, 0x120);
            lw(s6, sp, 0x110);
            goto L_0033a728;
        }
    L_0033a720:
        charge(ctx, 2);
        sw(zero, sp, 0x120);
        lw(s6, s1, kSpRespawn);
    L_0033a728:
        charge(ctx, 60);
        lw(v0, s7, 16);
        lw(a0, v0, 24);
        a1 = 10;
        jal(ctx, 0x33A734u, gen::fn_geometryLock_00493370);
        lw(v0, s7, 16);
        lw(v1, v0, 24);
        lw(v0, v1, 92);
        lw(s3, v0, 20);
        lw(s2, v1, 48);
        mtc1(zero, f23);
        sw(zero, sp, 0x164);
        sw(zero, sp, 0x16C);
        v0 = 0xFF0000;
        v1 = v0 | 0xFFFF;  // &0xFFFFFF
        lw(v0, s1, kSpColourA);
        v0 = dsll32(v0, 8);
        v0 = dsrl32(v0, 8);
        sw(v0, sp, 0x1AC);
        v0 = addiu(sp, 0x1AC);
        lwc1(f0, gp, -32420);  // 0x7CAE4C
        lw(v0, v0, 0);
        pextlb(v0, zero, v0);
        pextlh(v0, zero, v0);
        qmtc2(v0, vf10, false);  // qmtc2
        vitof0(0xF, vf10, vf10);  // vitof0.xyzw
        mfc1(v0, f0);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        v0 = addiu(sp, 0x190);
        sqc2(vf10, v0, 0);
        lw(v0, s1, kSpColourB);
        v0 = v0 & v1;
        sw(v0, sp, 0x1A8);
        v0 = addiu(sp, 0x1A8);
        lw(v0, v0, 0);
        pextlb(v0, zero, v0);
        pextlh(v0, zero, v0);
        qmtc2(v0, vf10, false);  // qmtc2
        vitof0(0xF, vf10, vf10);  // vitof0.xyzw
        mfc1(v0, f0);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        v0 = addiu(sp, 0x180);
        sqc2(vf10, v0, 0);
        lwc1(f27, s1, 132);
        lbu(v0, s1, kSpMode);
        sq(v0, sp, 0xC0);
        fp = 0;
        lwc1(f25, gp, -32352);  // 0x7CAE90
        v0 = 0x3F800000;
        mtc1(v0, f24);
        v0 = 0x3F000000;
        mtc1(v0, f22);
        v0 = 0x437F0000;
        mtc1(v0, f21);
        for (;;) {
            // 0x0033ae74
            charge(ctx, 4);
            lw(v0, sp, 0x110);
            v0 = slt(fp, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0033a818
            charge(ctx, 4);
            lw(s5, s4, 0);
            v0 = si(-2);
            if (s5 != v0) {
                // 0x0033a828
                charge(ctx, 3);
                v0 = si(-1);
                if (s5 != v0) {
                    // 0x0033a978
                    charge(ctx, 3);
                    lw(v0, sp, 0xE8);
                    if (s5 != v0) {
                        // 0x0033a9f0
                        charge(ctx, 7);
                        mtc1(s5, f0);
                        cvt_s_w(f3, f0);
                        lwc1(f20, s4, 8);
                        c_lt_s(f27, f23);
                        if (cond(ctx)) {
                            // 0x0033aa0c
                            charge(ctx, 9);
                            lwc1(f0, s4, 4);
                            neg_s(f1, f0);
                            mul_s(f0, f22, f27);
                            div_s(f0, f1, f0);
                            mul_s(f0, f22, f0);
                            c_le_s(f3, f0);
                            if (!cond(ctx)) {
                                // 0x0033aa30
                                charge(ctx, 1);
                                mov_s(f3, f0);
                            }
                        }
                        // 0x0033aa34
                        charge(ctx, 93);
                        mul_s(f2, f27, f3);
                        lwc1(f1, s4, 4);
                        mtc1(zero, f0);
                        adda_s(f0, f1);
                        madd_s(f0, f22, f2);
                        mul_s(f1, f3, f0);
                        lwc1(f0, s4, 20);
                        add_s(f26, f1, f0);
                        v0 = 0x6A0000;
                        v0 = addiu(v0, -15200);  // &0x69C4A0
                        lqc2(vf10, v0, 0);  // 0x69C4A0
                        lw(v0, s4, 24);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        v0 = addiu(sp, 0x150);
                        sqc2(vf10, v0, 0);
                        mov_s(f12, f20);
                        jal(ctx, 0x33AA80u, gen::fn_cosf_0052e6d8);
                        swc1(f0, sp, 0x160);
                        mov_s(f12, f20);
                        jal(ctx, 0x33AA90u, gen::fn_sinf_0052e878);
                        swc1(f0, sp, 0x168);
                        v0 = addiu(sp, 0x160);
                        lqc2(vf10, v0, 0);
                        vmove(0xF, vf12, vf10);  // vmove.xyzw
                        lw(v0, s4, 12);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        vmove(0xF, vf11, vf12);  // vmove.xyzw
                        a2 = addiu(sp, 0x130);
                        sqc2(vf10, a2, 0);
                        lw(v0, s4, 16);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
                        v0 = addiu(sp, 0x140);
                        sqc2(vf11, v0, 0);
                        vmove(0xF, vf10, vf12);  // vmove.xyzw
                        mfc1(v0, f26);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        v0 = addiu(sp, 0x170);
                        sqc2(vf10, v0, 0);
                        vmove(0xF, vf2, vf10);  // vmove.xyzw
                        vmove(0xF, vf10, vf12);  // vmove.xyzw
                        vmove(0xF, vf12, vf2);  // vmove.xyzw
                        qmfc2(v0, vf10, false);  // qmfc2
                        mtc1(v0, f1);
                        qmfc2(v0, vf10, false);  // qmfc2
                        pexew(v0, v0);
                        mtc1(v0, f0);
                        mfc1(v0, f0);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vadd_bc(0x8, vf10, vf0, vf2, 0);  // vaddx.x
                        neg_s(f0, f1);
                        mfc1(v0, f0);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vadd_bc(0x2, vf10, vf0, vf2, 0);  // vaddx.z
                        a1 = addiu(sp, 0x150);
                        lqc2(vf11, a1, 0);
                        vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
                        sqc2(vf10, a1, 0);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, -15152);  // &0x69C4D0
                        sqc2(vf12, a0, 0);  // 0x69C4D0
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15152);  // 0x69C4D0
                        swc1(f0, s3, 0);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15148);  // 0x69C4D4
                        swc1(f0, s3, 4);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15144);  // 0x69C4D8
                        swc1(f0, s3, 8);
                        a3 = 0;
                        v1 = 0x6A0000;
                        v1 = addiu(v1, -14608);  // &0x69C6F0
                        v0 = 0x6A0000;
                        v0 = addiu(v0, -14672);  // &0x69C6B0
                        t2 = 0x6A0000;
                        t1 = 0x6A0000;
                        t0 = 0x6A0000;
                        for (;;) {
                            // 0x0033ac14
                            charge(ctx, 3);
                            t3 = slti(a3, 6);
                            if (t3 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x0033aba8
                            charge(ctx, 27);
                            lqc2(vf10, a2, 0);
                            t4 = sll(a3, 2);
                            t3 = addu(v1, t4);
                            lw(t3, t3, 0);
                            qmtc2(t3, vf2, false);  // qmtc2
                            vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                            vadd(0xF, vf10, vf10, vf12);  // vadd.xyzw
                            lqc2(vf11, a1, 0);
                            t3 = addu(v0, t4);
                            lw(t3, t3, 0);
                            qmtc2(t3, vf2, false);  // qmtc2
                            vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
                            vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
                            sqc2(vf10, a0, 0);
                            t3 = sll(a3, 1);
                            t3 = addu(t3, a3);
                            t3 = sll(t3, 2);
                            t3 = addu(s3, t3);
                            lwc1(f0, t2, -15152);
                            swc1(f0, t3, 12);
                            lwc1(f0, t1, -15148);
                            swc1(f0, t3, 16);
                            lwc1(f0, t0, -15144);
                            swc1(f0, t3, 20);
                            a3 = addiu(a3, 1);
                        }
                        // 0x0033ac20
                        charge(ctx, 14);
                        a2 = 6;
                        a1 = addiu(sp, 0x140);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, -14608);  // &0x69C6F0
                        v1 = addiu(sp, 0x150);
                        v0 = 0x6A0000;
                        v0 = addiu(v0, -14672);  // &0x69C6B0
                        t3 = 0x6A0000;
                        t3 = addiu(t3, -15152);  // &0x69C4D0
                        t1 = 0x6A0000;
                        t0 = 0x6A0000;
                        a3 = 0x6A0000;
                        for (;;) {
                            // 0x0033acc4
                            charge(ctx, 3);
                            t2 = slti(a2, 12);
                            if (t2 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x0033ac58
                            charge(ctx, 27);
                            lqc2(vf10, a1, 0);
                            t4 = sll(a2, 2);
                            t2 = addu(a0, t4);
                            lw(t2, t2, 0);
                            qmtc2(t2, vf2, false);  // qmtc2
                            vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                            vadd(0xF, vf10, vf10, vf12);  // vadd.xyzw
                            lqc2(vf11, v1, 0);
                            t2 = addu(v0, t4);
                            lw(t2, t2, 0);
                            qmtc2(t2, vf2, false);  // qmtc2
                            vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
                            vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
                            sqc2(vf10, t3, 0);
                            t2 = sll(a2, 1);
                            t2 = addu(t2, a2);
                            t2 = sll(t2, 2);
                            t2 = addu(s3, t2);
                            lwc1(f0, t1, -15152);
                            swc1(f0, t2, 12);
                            lwc1(f0, t0, -15148);
                            swc1(f0, t2, 16);
                            lwc1(f0, a3, -15144);
                            swc1(f0, t2, 20);
                            a2 = addiu(a2, 1);
                        }
                        // 0x0033acd0
                        charge(ctx, 4);
                        lw(v0, sp, 0x100);
                        at = slt(s5, v0);
                        if (at == 0) {
                            // 0x0033ad10
                            charge(ctx, 4);
                            lw(v0, sp, 0xF0);
                            at = slt(v0, s5);
                            if (at == 0) {
                                // 0x0033ad5c
                                charge(ctx, 1);
                                mov_s(f0, f24);
                            } else {
                                // 0x0033ad20
                                charge(ctx, 15);
                                v0 = subu(s0, s5);
                                mtc1(v0, f0);
                                cvt_s_w(f1, f0);
                                lw(v0, sp, 0xF0);
                                v0 = subu(s0, v0);
                                mtc1(v0, f0);
                                cvt_s_w(f0, f0);
                                div_s(f0, f1, f0);
                            }
                        } else {
                            // 0x0033ace0
                            charge(ctx, 12);
                            mtc1(s5, f0);
                            cvt_s_w(f1, f0);
                            mtc1(v0, f0);
                            cvt_s_w(f0, f0);
                            div_s(f0, f1, f0);
                        }
                        // 0x0033ad60
                        charge(ctx, 23);
                        v0 = 0x6A0000;
                        v0 = addiu(v0, -15200);  // &0x69C4A0
                        lqc2(vf11, v0, 0);  // 0x69C4A0
                        mfc1(v0, f0);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
                        v0 = addiu(sp, 0x180);
                        lqc2(vf10, v0, 0);
                        vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
                        mfc1(v0, f21);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
                        qmfc2(v0, vf10, false);  // qmfc2
                        ppach(v0, zero, v0);
                        ppacb(v0, zero, v0);
                        sw(v0, sp, 0x1A4);
                        lw(v1, sp, 0x1A4);
                        a0 = 1;
                        for (;;) {
                            // 0x0033adcc
                            charge(ctx, 3);
                            at = slti(a0, 13);
                            if (at == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x0033adbc
                            charge(ctx, 4);
                            v0 = sll(a0, 2);
                            v0 = addu(s2, v0);
                            sw(v1, v0, 0);
                            a0 = addiu(a0, 1);
                        }
                        // 0x0033add8
                        charge(ctx, 20);
                        v0 = addiu(sp, 0x190);
                        lqc2(vf10, v0, 0);
                        vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
                        mfc1(v0, f21);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
                        qmfc2(v0, vf10, false);  // qmfc2
                        ppach(v0, zero, v0);
                        ppacb(v0, zero, v0);
                        sw(v0, sp, 0x1A0);
                        lw(a0, sp, 0x1A0);
                        mul_s(f1, f21, f0);
                        v0 = 0x4F000000;
                        mtc1(v0, f0);
                        c_le_s(f0, f1);
                        if (cond(ctx)) {
                            // 0x0033ae38
                            charge(ctx, 5);
                            sub_s(f0, f1, f0);
                            cvt_w_s(f0, f0);
                            mfc1(v1, f0);
                            v0 = lui(0x8000);
                            v1 = v1 | v0;
                        } else {
                            // 0x0033ae28
                            charge(ctx, 4);
                            cvt_w_s(f0, f1);
                            mfc1(v1, f0);
                        }
                        // 0x0033ae4c
                        charge(ctx, 6);
                        v0 = sll(v1, 24);
                        v0 = a0 | v0;
                        sw(v0, s2, 0);
                        lw(v0, sp, 0xD0);
                        v0 = addu(s5, v0);
                        sw(v0, s4, 0);
                    } else {
                        // 0x0033a984
                        charge(ctx, 3);
                        v1 = 0;
                        for (;;) {
                            // 0x0033a9bc
                            charge(ctx, 3);
                            v0 = slti(v1, 13);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x0033a990
                            charge(ctx, 11);
                            v0 = sll(v1, 1);
                            v0 = addu(v0, v1);
                            v0 = sll(v0, 2);
                            v0 = addu(s3, v0);
                            swc1(f23, v0, 0);
                            swc1(f23, v0, 4);
                            swc1(f23, v0, 8);
                            v0 = sll(v1, 2);
                            v0 = addu(s2, v0);
                            sw(zero, v0, 0);
                            v1 = addiu(v1, 1);
                        }
                        // 0x0033a9c8
                        charge(ctx, 3);
                        lq(v0, sp, 0xC0);
                        if (v0 == 0) {
                            // 0x0033a9e0
                            charge(ctx, 1);
                            v0 = si(-2);
                        } else {
                            // 0x0033a9d4
                            charge(ctx, 3);
                            v0 = si(-1);
                        }
                        // 0x0033a9e4
                        charge(ctx, 3);
                        sw(v0, s4, 0);
                    }
                } else {
                    // 0x0033a834
                    charge(ctx, 2);
                    if (s6 != 0) {
                        // 0x0033a83c
                        charge(ctx, 66);
                        a0 = 0;
                        jal(ctx, 0x33A840u, gen::fn_sub_358030_00358030);
                        mul_s(f0, f25, f0);
                        swc1(f0, s4, 8);
                        lwc1(f26, s1, 112);
                        sub_s(f20, f24, f26);
                        a0 = 0;
                        jal(ctx, 0x33A85Cu, gen::fn_sub_358030_00358030);
                        mtc1(zero, f1);
                        adda_s(f1, f20);
                        madd_s(f1, f26, f0);
                        lwc1(f0, s1, 108);
                        mul_s(f0, f0, f1);
                        swc1(f0, s4, 12);
                        a0 = 0;
                        jal(ctx, 0x33A884u, gen::fn_sub_358030_00358030);
                        mtc1(zero, f1);
                        adda_s(f1, f20);
                        madd_s(f1, f26, f0);
                        lwc1(f0, s1, 108);
                        mul_s(f0, f0, f1);
                        swc1(f0, s4, 16);
                        lwc1(f20, s1, 120);
                        a0 = 0;
                        jal(ctx, 0x33A8B0u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f24, f20);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f20, f0);
                        lwc1(f0, s1, 116);
                        mul_s(f0, f0, f1);
                        swc1(f0, s4, 20);
                        lwc1(f20, s1, 128);
                        a0 = 0;
                        jal(ctx, 0x33A8E0u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f24, f20);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f20, f0);
                        lwc1(f0, s1, 124);
                        mul_s(f0, f0, f1);
                        swc1(f0, s4, 4);
                        lwc1(f20, s1, 104);
                        a0 = 0;
                        jal(ctx, 0x33A910u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f24, f20);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f20, f0);
                        lwc1(f0, s1, 96);
                        mul_s(f0, f0, f1);
                        swc1(f0, s4, 24);
                        lw(v0, sp, 0x120);
                        if (v0 == 0) {
                            // 0x0033a964
                            charge(ctx, 2);
                            lw(v0, sp, 0xEC);
                            sw(v0, s4, 0);
                        } else {
                            // 0x0033a944
                            charge(ctx, 8);
                            a0 = 0;
                            jal(ctx, 0x33A948u, gen::fn_sub_357FD0_00357fd0);
                            divu(v0, s0);
                            mfhi(v0);
                            sw(v0, s4, 0);
                        }
                        // 0x0033a96c
                        charge(ctx, 3);
                        s6 = addiu(s6, -1);
                    }
                }
            }
            // 0x0033ae64
            charge(ctx, 4);
            fp = addiu(fp, 0x1);
            s4 = addiu(s4, 28);
            s3 = addiu(s3, 156);
            s2 = addiu(s2, 52);
        }
        // 0x0033ae84
        charge(ctx, 9);
        lw(v0, s7, 16);
        lw(s0, v0, 24);
        a0 = s0;
        jal(ctx, 0x33AE90u, gen::fn_sub_4933D0_004933d0);
        lhu(v1, s7, 0);
        v1 = v1 & 0x4;
        if (v1 != 0) {
            // 0x0033aea8
            charge(ctx, 3);
            lhu(v1, s0, 12);
            v1 = v1 | 0x1;
            sh(v1, s0, 12);
        }
    }
    // 0x0033aeb4 (the shared epilogue, written out on this path)
    charge(ctx, 21);
    ld(ra, sp, 0xB0);
    lq(fp, sp, 0xA0);
    lq(s7, sp, 0x90);
    lq(s6, sp, 0x80);
    lq(s5, sp, 0x70);
    lq(s4, sp, 0x60);
    lq(s3, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f27, sp, 0x1C);
    lwc1(f26, sp, 0x18);
    lwc1(f25, sp, 0x14);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x1B0);
}

// 0x0033AF10 sub_33AF10 -- 448 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 2, slot 5 [k10Streak2Draw] ($a0 = the instance): within the lifetime (+52 of the parameters vs the
// frame +52), colour = instance colour (+48) x the colour track at the frame (sub_32A120 on +36), on VU0 (bytes ->
// floats / 255, multiply, x 255, back to bytes) into the mesh's material colour (alpha 255 written as 254 and
// restored); the mesh is placed at the instance position / rotation / scale (sub_3238D0), its additive bit follows
// +86 and it is queued on the layer +40 (sub_323860). Every class-10 kind's draw is this body.
void sub_33AF10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    Vf vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x0033af10
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(v1, a0, 60);
    lw(s1, a0, 64);
    lw(s0, v1, 4);
    lw(a2, a0, 52);
    lw(a3, s1, kSpLifetime);
    at = sltu(a3, a2);
    if (at != 0) {
        // 0x0033af48
        charge(ctx, 2);
        if (a3 == 0) {
            goto L_0033af50;
        }
        // 0x0033b0b4 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_0033af50:
    charge(ctx, 45);
    a0 = s1;
    a1 = addiu(s1, 36);
    jal(ctx, 0x33AF58u, gen::fn_sub_32A120_0032a120);
    v1 = v0;
    lw(v0, s2, 48);
    sw(v0, sp, 0x48);
    v0 = addiu(sp, 0x48);
    lwc1(f0, gp, -32420);  // 0x7CAE4C
    lw(v0, v0, 0);
    pextlb(v0, zero, v0);
    pextlh(v0, zero, v0);
    qmtc2(v0, vf10, false);  // qmtc2
    vitof0(0xF, vf10, vf10);  // vitof0.xyzw
    mfc1(v0, f0);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vmove(0xF, vf11, vf10);  // vmove.xyzw
    sw(v1, sp, 0x44);
    v0 = addiu(sp, 0x44);
    lw(v0, v0, 0);
    pextlb(v0, zero, v0);
    pextlh(v0, zero, v0);
    qmtc2(v0, vf10, false);  // qmtc2
    vitof0(0xF, vf10, vf10);  // vitof0.xyzw
    mfc1(v0, f0);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
    v0 = 0x437F0000;
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
    qmfc2(v0, vf10, false);  // qmfc2
    ppach(v0, zero, v0);
    ppacb(v0, zero, v0);
    sw(v0, sp, 0x40);
    lw(v0, sp, 0x40);
    sw(v0, sp, 0x4C);
    lbu(v0, sp, 0x4F);
    a3 = 255;
    if (v0 == a3) {
        // 0x0033b030
        charge(ctx, 12);
        v0 = 254;
        sb(v0, sp, 0x4F);
        lw(a2, s0, 20);
        lbu(a1, sp, 0x4C);
        lbu(a0, sp, 0x4D);
        lbu(v1, sp, 0x4E);
        lbu(v0, sp, 0x4F);
        sb(a1, a2, 4);
        sb(a0, a2, 5);
        sb(v1, a2, 6);
        sb(v0, a2, 7);
        sb(a3, sp, 0x4F);
    } else {
        // 0x0033b004
        charge(ctx, 11);
        lw(a2, s0, 20);
        lbu(a1, sp, 0x4C);
        lbu(a0, sp, 0x4D);
        lbu(v1, sp, 0x4E);
        lbu(v0, sp, 0x4F);
        sb(a1, a2, 4);
        sb(a0, a2, 5);
        sb(v1, a2, 6);
        sb(v0, a2, 7);
    }
    // 0x0033b060
    charge(ctx, 9);
    a0 = s0;
    a1 = s2;
    a2 = addiu(s2, 16);
    a3 = addiu(s2, 32);
    jal(ctx, 0x33B070u, gen::fn_sub_3238D0_003238d0);
    lbu(v0, s1, kSpAdditive);
    if (v0 == 0) {
        // 0x0033b098
        charge(ctx, 3);
        lhu(v0, s0, 0);
        v0 = v0 & 0xFFFE;
        sh(v0, s0, 0);
    } else {
        // 0x0033b084
        charge(ctx, 5);
        lhu(v0, s0, 0);
        v0 = v0 | 0x1;
        sh(v0, s0, 0);
    }
    // 0x0033b0a4
    charge(ctx, 4);
    lhu(a1, s1, kSpLayer);
    a0 = s0;
    jal(ctx, 0x33B0ACu, gen::fn_sub_323860_00323860);
    // 0x0033b0b4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0033BDA0 sub_33BDA0 -- 232 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 4, slot 0 [k10Sprite4Init] ($a0 = the instance): locks the mesh geometry (vertices), clears all its
// vertices (12 bytes x vertex count), unlocks (re-instance when flagged) and marks every record free (word 0 = -1;
// records of 24 bytes).
void sub_33BDA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0033bda0
    enter(ctx, 36);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, 60);
    lw(s3, v0, 0);
    lw(s2, v0, 4);
    lw(v0, a0, 64);
    lw(s1, v0, 56);
    lw(v0, s2, 16);
    lw(a0, v0, 24);
    a1 = 2;
    jal(ctx, 0x33BDD8u, gen::fn_geometryLock_00493370);
    lw(v0, s2, 16);
    lw(v0, v0, 24);
    lw(v0, v0, 92);
    lw(a0, v0, 20);
    lh(v1, s2, 8);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    a2 = sll(v0, 2);
    a1 = 0;
    jal(ctx, 0x33BE04u, gen::fn_memset_00521408);
    lw(v0, s2, 16);
    lw(s0, v0, 24);
    a0 = s0;
    jal(ctx, 0x33BE18u, gen::fn_sub_4933D0_004933d0);
    lhu(v1, s2, 0);
    v1 = v1 & 0x4;
    if (v1 != 0) {
        // 0x0033be30
        charge(ctx, 3);
        lhu(v1, s0, 12);
        v1 = v1 | 0x1;
        sh(v1, s0, 12);
    }
    // 0x0033be3c
    charge(ctx, 4);
    a1 = 0;
    a0 = si(-1);
    for (;;) {
        // 0x0033be58
        charge(ctx, 4);
        v1 = slt(a1, s1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0033be4c
        charge(ctx, 3);
        sw(a0, s3, 0);
        s3 = addiu(s3, 24);
        a1 = addiu(a1, 1);
    }
    // 0x0033be68
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0033BE90 sub_33BE90 -- 272 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 4 [k10Sprite4TexCoords] ($a0 = the kind object, $a1 = the kind parameters): locks the texture
// coordinates (rwGEOMETRYLOCK texcoords 0xFF0) and gives every particle quad its four (u, v): the even ones the left
// half, the odd ones the right half of the texture (u 0 / 0.5 / 1), v 0..1; unlocks, re-instance when flagged.
void sub_33BE90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0033be90
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a1, 56);
    if (s0 != 0) {
        // 0x0033beb0
        charge(ctx, 15);
        lw(v0, s1, 4);
        lw(v0, v0, 16);
        lw(a0, v0, 24);
        a1 = 4080;
        jal(ctx, 0x33BEC0u, gen::fn_geometryLock_00493370);
        lw(v0, s1, 4);
        lw(v0, v0, 16);
        lw(v0, v0, 24);
        lw(a1, v0, 52);
        a2 = 0;
        a0 = 0x3F000000;
        v1 = 0x3F800000;
        for (;;) {
            // 0x0033bf48
            charge(ctx, 3);
            v0 = sltu(a2, s0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0033beec
            charge(ctx, 3);
            v0 = a2 & 0x1;
            if (v0 == 0) {
                // 0x0033bf20
                charge(ctx, 8);
                sw(a0, a1, 0);
                sw(zero, a1, 4);
                sw(v1, a1, 8);
                sw(zero, a1, 12);
                sw(a0, a1, 16);
                sw(v1, a1, 20);
                sw(v1, a1, 24);
                sw(v1, a1, 28);
            } else {
                // 0x0033bef8
                charge(ctx, 10);
                sw(zero, a1, 0);
                sw(zero, a1, 4);
                sw(a0, a1, 8);
                sw(zero, a1, 12);
                sw(zero, a1, 16);
                sw(v1, a1, 20);
                sw(a0, a1, 24);
                sw(v1, a1, 28);
            }
            // 0x0033bf40
            charge(ctx, 2);
            a2 = addiu(a2, 1);
            a1 = addiu(a1, 32);
        }
        // 0x0033bf54
        charge(ctx, 10);
        lw(s1, s1, 4);
        lw(v0, s1, 16);
        lw(s0, v0, 24);
        a0 = s0;
        jal(ctx, 0x33BF64u, gen::fn_sub_4933D0_004933d0);
        lhu(v1, s1, 0);
        v1 = v1 & 0x4;
        if (v1 != 0) {
            // 0x0033bf7c
            charge(ctx, 3);
            lhu(v1, s0, 12);
            v1 = v1 | 0x1;
            sh(v1, s0, 12);
        }
    }
    // 0x0033bf88 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0033BFA0 sub_33BFA0 -- 252 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 4, slot 1 [k10Sprite4Create] ($a0 = the kind parameters, $a1 = block B (a frame list) or 0; returns
// the kind object): one RwMalloc block of 16 + 24 x count bytes, a quad mesh (sub_3233A0: count quads, 2 x 4, layout
// 0x69BDC8, vertex size 76) (the frame step +112 raised to 1); textured from block B (sub_323B90) or else with the
// manager's texture 18 (sub_3210A0 -> RwFrame op sub_494D50); the texture coordinates by sub_33BE90.
void sub_33BFA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0033bfa0
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    lw(v1, a0, 56);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v0 = sll(v0, 3);
    a0 = addiu(v0, 16);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x33BFDCu, v0.u());
    s0 = v0;
    v1 = addiu(v0, 16);
    sw(v1, v0, 0);
    sw(v0, v0, 8);
    lw(v0, s2, 112);
    if (v0 == 0) {
        // 0x0033c000
        charge(ctx, 2);
        v0 = 1;
        sw(v0, s2, 112);
    }
    // 0x0033c008
    charge(ctx, 11);
    lhu(a0, s2, 56);
    a1 = 2;
    a2 = 4;
    a3 = 0x6A0000;
    a3 = addiu(a3, -16952);  // &0x69BDC8
    t0 = 76;
    jal(ctx, 0x33C020u, gen::fn_sub_3233A0_003233a0);
    sw(v0, s0, 4);
    if (s1 != 0) {
        // 0x0033c05c
        charge(ctx, 4);
        lw(a0, s0, 4);
        a1 = s1;
        jal(ctx, 0x33C064u, gen::fn_sub_323B90_00323b90);
    } else {
        // 0x0033c034
        charge(ctx, 10);
        a0 = 18;
        jal(ctx, 0x33C038u, gen::fn_sub_3210A0_003210a0);
        lw(v1, s0, 4);
        lw(a0, v1, 20);
        a1 = v0;
        jal(ctx, 0x33C04Cu, gen::fn_sub_494D50_00494d50);
    }
    // 0x0033c06c
    charge(ctx, 12);
    a0 = s0;
    a1 = s2;
    jal(ctx, 0x33C074u, gen::fn_sub_33BE90_0033be90);
    v0 = s0;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0033C0A0 sub_33C0A0 -- 168 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 4, slot 3 [k10Sprite4Clone] ($a0 = the instance; returns a new kind object): a copy of the kind
// object for a clone: the same block size (frame step +112 raised to 1), the mesh duplicated (sub_323640 of the old
// object's mesh) and the texture coordinates by sub_33BE90.
void sub_33C0A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0033c0a0
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    lw(s1, a0, 64);
    lw(v1, s1, 56);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v0 = sll(v0, 3);
    a0 = addiu(v0, 16);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x33C0DCu, v0.u());
    s2 = v0;
    v1 = addiu(v0, 16);
    sw(v1, v0, 0);
    sw(v0, v0, 8);
    lw(v0, s1, 112);
    if (v0 == 0) {
        // 0x0033c100
        charge(ctx, 2);
        v0 = 1;
        sw(v0, s1, 112);
    }
    // 0x0033c108
    charge(ctx, 16);
    lw(a0, s0, 4);
    jal(ctx, 0x33C10Cu, gen::fn_sub_323640_00323640);
    sw(v0, s2, 4);
    a0 = s2;
    a1 = s1;
    jal(ctx, 0x33C120u, gen::fn_sub_33BE90_0033be90);
    v0 = s2;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0033C150 sub_33C150 -- 68 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 4, slot 2 [k10Sprite4Destroy] ($a0 = the kind object): destroys the mesh (+4, sub_3237C0
// [fxMeshDestroy]) and frees the block (+8, RwFree 0x96017C).
void sub_33C150(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0033c150
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, kKoMesh);
    jal(ctx, 0x33C164u, gen::fn_sub_3237C0_003237c0);
    lw(a0, s0, 8);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x33C178u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0033C1A0 sub_33C1A0 -- 1976 bytes; frame 0x180: ra sp+0xB0, fp sp+0xA0 (sq), s7 sp+0x90 (sq), s6 sp+0x80 (sq), s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f27 sp+0x1C, f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 4, slot 4 [k10Sprite4Update] ($a0 = the instance): within the lifetime. The particle life (+76) with
// its fade-in / fade-out fractions (+68 / +72, reversed by a kind flag) gives the alpha ramp; unless the once flag
// (+85) holds the emission after frame 0, the re-emission period is +80. The mesh is locked (vertices + prelight) and
// each record runs: a free one is (re-)emitted with random values from the parameters' ranges (sub_358030 = random
// float, sub_357FD0 = random int: angle, speed +116 with its randomness and sign, the frame step +112, size +96 /
// +104) and a random start age; a live one ages, its colour is blended from colour A (+88) to colour B (+92) with the
// alpha ramp, and its camera-facing quads are rebuilt (cosf / sinf of its angle, VU0 scaling) into the mesh vertices;
// then the mesh is unlocked (re-instance when flagged).
void sub_33C1A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26}, f27{ctx, 27};
    Vf vf0{ctx, 0}, vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11}, vf12{ctx, 12};
    // 0x0033c1a0
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x180);
    sd(ra, sp, 0xB0);
    sq(fp, sp, 0xA0);
    sq(s7, sp, 0x90);
    sq(s6, sp, 0x80);
    sq(s5, sp, 0x70);
    sq(s4, sp, 0x60);
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f27, sp, 0x1C);
    swc1(f26, sp, 0x18);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(s1, a0, 64);
    lw(v1, s1, kSpLifetime);
    lw(a1, a0, 52);
    at = sltu(v1, a1);
    if (at != 0) {
        // 0x0033c204
        charge(ctx, 2);
        if (v1 == 0) {
            goto L_0033c20c;
        }
        // 0x0033c904 (the shared epilogue, written out on this path)
        charge(ctx, 21);
        ld(ra, sp, 0xB0);
        lq(fp, sp, 0xA0);
        lq(s7, sp, 0x90);
        lq(s6, sp, 0x80);
        lq(s5, sp, 0x70);
        lq(s4, sp, 0x60);
        lq(s3, sp, 0x50);
        lq(s2, sp, 0x40);
        lq(s1, sp, 0x30);
        lq(s0, sp, 0x20);
        lwc1(f27, sp, 0x1C);
        lwc1(f26, sp, 0x18);
        lwc1(f25, sp, 0x14);
        lwc1(f24, sp, 0x10);
        lwc1(f23, sp, 0xC);
        lwc1(f22, sp, 0x8);
        lwc1(f21, sp, 0x4);
        lwc1(f20, sp, 0x0);
        sp = addiu(sp, 0x180);
        return;
    }
L_0033c20c:
    charge(ctx, 8);
    lw(v1, a0, 60);
    lw(s4, v1, 0);
    lw(s7, v1, 4);
    lw(v1, s1, kSpCount);
    sq(v1, sp, 0x100);
    lw(s0, s1, kSpLife);
    if (s0 != 0) {
        // 0x0033c22c
        charge(ctx, 3);
        lbu(v0, s1, kSpOnce);
        if (v0 != 0) {
            // 0x0033c238
            charge(ctx, 2);
            if (a1 != 0) {
                goto L_0033c254;
            }
            // 0x0033c240
            charge(ctx, 5);
            v0 = 1;
            sw(v0, sp, 0x110);
            paddub(s6, v1, zero);
            goto L_0033c25c;
        }
    L_0033c254:
        charge(ctx, 2);
        sw(zero, sp, 0x110);
        lw(s6, s1, kSpRespawn);
    L_0033c25c:
        charge(ctx, 74);
        lw(v0, s7, 16);
        lw(a0, v0, 24);
        a1 = 10;
        jal(ctx, 0x33C268u, gen::fn_geometryLock_00493370);
        lw(v0, s7, 16);
        lw(v1, v0, 24);
        lw(v0, v1, 92);
        lw(s3, v0, 20);
        lw(s2, v1, 48);
        mtc1(zero, f22);
        sw(zero, sp, 0x144);
        sw(zero, sp, 0x14C);
        lw(v0, s1, kSpColourA);
        sw(v0, sp, 0x17C);
        v0 = addiu(sp, 0x17C);
        lwc1(f0, gp, -32420);  // 0x7CAE4C
        lw(v0, v0, 0);
        pextlb(v0, zero, v0);
        pextlh(v0, zero, v0);
        qmtc2(v0, vf10, false);  // qmtc2
        vitof0(0xF, vf10, vf10);  // vitof0.xyzw
        mfc1(v0, f0);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        v0 = addiu(sp, 0x160);
        sqc2(vf10, v0, 0);
        lw(v0, s1, kSpColourB);
        sw(v0, sp, 0x178);
        v0 = addiu(sp, 0x178);
        lw(v0, v0, 0);
        pextlb(v0, zero, v0);
        pextlh(v0, zero, v0);
        qmtc2(v0, vf10, false);  // qmtc2
        vitof0(0xF, vf10, vf10);  // vitof0.xyzw
        mfc1(v0, f0);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        v0 = addiu(sp, 0x150);
        sqc2(vf10, v0, 0);
        mtc1(s0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, s1, kSpFadeIn);
        mul_s(f0, f0, f1);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        sq(v0, sp, 0xF0);
        lwc1(f0, s1, kSpFadeOut);
        mul_s(f0, f0, f1);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        sq(v0, sp, 0xE0);
        lwc1(f26, s1, 124);
        lw(v0, s1, 112);
        sq(v0, sp, 0xD0);
        lbu(v0, s1, kSpMode);
        sq(v0, sp, 0xC0);
        fp = 0;
        lwc1(f25, gp, -32352);  // 0x7CAE90
        v0 = 0x3F800000;
        mtc1(v0, f24);
        v0 = lui(0xBF80);
        mtc1(v0, f23);
        v0 = 0x3F000000;
        mtc1(v0, f21);
        v0 = 0x437F0000;
        mtc1(v0, f20);
        for (;;) {
            // 0x0033c8c4
            charge(ctx, 4);
            lq(v0, sp, 0x100);
            v0 = slt(fp, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0033c384
            charge(ctx, 4);
            lw(s5, s4, 0);
            v0 = si(-2);
            if (s5 != v0) {
                // 0x0033c394
                charge(ctx, 3);
                v0 = si(-1);
                if (s5 != v0) {
                    // 0x0033c4f8
                    charge(ctx, 3);
                    v0 = slt(s5, s0);
                    if (v0 != 0) {
                        // 0x0033c570
                        charge(ctx, 7);
                        mtc1(s5, f0);
                        cvt_s_w(f3, f0);
                        lwc1(f2, s4, 4);
                        c_le_s(f2, f22);
                        if (cond(ctx)) {
                            // 0x0033c5ac
                            charge(ctx, 6);
                            mul_s(f1, f26, f3);
                            mtc1(zero, f0);
                            adda_s(f0, f2);
                            msub_s(f0, f21, f1);
                            mul_s(f27, f3, f0);
                        } else {
                            // 0x0033c58c
                            charge(ctx, 8);
                            mul_s(f1, f26, f3);
                            mtc1(zero, f0);
                            adda_s(f0, f2);
                            madd_s(f0, f21, f1);
                            mul_s(f27, f3, f0);
                        }
                        // 0x0033c5c4
                        charge(ctx, 6);
                        lwc1(f0, s4, 8);
                        add_s(f27, f27, f0);
                        lq(v0, sp, 0xD0);
                        at = slt(s5, v0);
                        if (at != 0) {
                            // 0x0033c5dc
                            charge(ctx, 4);
                            lwc1(f1, s4, 16);
                            lwc1(f0, s4, 12);
                            add_s(f0, f0, f1);
                            swc1(f0, s4, 12);
                        }
                        // 0x0033c5ec
                        charge(ctx, 107);
                        v0 = 0x6A0000;
                        v0 = addiu(v0, -15200);  // &0x69C4A0
                        lqc2(vf10, v0, 0);  // 0x69C4A0
                        vmove(0xF, vf11, vf10);  // vmove.xyzw
                        lw(v0, s4, 12);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        v0 = addiu(sp, 0x130);
                        sqc2(vf10, v0, 0);
                        vmove(0xF, vf10, vf11);  // vmove.xyzw
                        lw(v0, s4, 20);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        v0 = addiu(sp, 0x120);
                        sqc2(vf10, v0, 0);
                        mov_s(f12, f27);
                        jal(ctx, 0x33C634u, gen::fn_cosf_0052e6d8);
                        swc1(f0, sp, 0x140);
                        mov_s(f12, f27);
                        jal(ctx, 0x33C644u, gen::fn_sinf_0052e878);
                        swc1(f0, sp, 0x148);
                        v0 = addiu(sp, 0x140);
                        lqc2(vf10, v0, 0);
                        vmove(0xF, vf12, vf10);  // vmove.xyzw
                        qmfc2(v0, vf10, false);  // qmfc2
                        mtc1(v0, f1);
                        qmfc2(v0, vf10, false);  // qmfc2
                        pexew(v0, v0);
                        mtc1(v0, f0);
                        mfc1(v0, f0);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vadd_bc(0x8, vf10, vf0, vf2, 0);  // vaddx.x
                        neg_s(f0, f1);
                        mfc1(v0, f0);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vadd_bc(0x2, vf10, vf0, vf2, 0);  // vaddx.z
                        vmove(0xF, vf11, vf10);  // vmove.xyzw
                        a0 = addiu(sp, 0x120);
                        lqc2(vf10, a0, 0);
                        vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
                        sqc2(vf10, a0, 0);
                        vmove(0xF, vf10, vf12);  // vmove.xyzw
                        v0 = addiu(sp, 0x130);
                        lqc2(vf11, v0, 0);
                        vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
                        vmove(0xF, vf12, vf10);  // vmove.xyzw
                        lqc2(vf10, a0, 0);
                        vmove(0xF, vf11, vf10);  // vmove.xyzw
                        v1 = 0x6A0000;
                        v1 = addiu(v1, -15152);  // &0x69C4D0
                        sqc2(vf10, v1, 0);  // 0x69C4D0
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15152);  // 0x69C4D0
                        swc1(f0, s3, 24);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15148);  // 0x69C4D4
                        swc1(f0, s3, 28);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15144);  // 0x69C4D8
                        swc1(f0, s3, 32);
                        vsub(0xE, vf11, vf0, vf11);  // vsub.xyz
                        sqc2(vf11, v1, 0);  // 0x69C4D0
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15152);  // 0x69C4D0
                        swc1(f0, s3, 36);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15148);  // 0x69C4D4
                        swc1(f0, s3, 40);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15144);  // 0x69C4D8
                        swc1(f0, s3, 44);
                        lqc2(vf10, a0, 0);
                        vmove(0xF, vf11, vf10);  // vmove.xyzw
                        vadd(0xF, vf10, vf10, vf12);  // vadd.xyzw
                        vsub(0xE, vf11, vf0, vf11);  // vsub.xyz
                        sqc2(vf10, v1, 0);  // 0x69C4D0
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15152);  // 0x69C4D0
                        swc1(f0, s3, 0);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15148);  // 0x69C4D4
                        swc1(f0, s3, 4);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15144);  // 0x69C4D8
                        swc1(f0, s3, 8);
                        vadd(0xF, vf11, vf11, vf12);  // vadd.xyzw
                        sqc2(vf11, v1, 0);  // 0x69C4D0
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15152);  // 0x69C4D0
                        swc1(f0, s3, 12);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15148);  // 0x69C4D4
                        swc1(f0, s3, 16);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15144);  // 0x69C4D8
                        swc1(f0, s3, 20);
                        lq(v0, sp, 0xF0);
                        at = slt(s5, v0);
                        if (at == 0) {
                            // 0x0033c7c8
                            charge(ctx, 4);
                            lq(v0, sp, 0xE0);
                            at = slt(v0, s5);
                            if (at == 0) {
                                // 0x0033c814
                                charge(ctx, 1);
                                mov_s(f0, f24);
                            } else {
                                // 0x0033c7d8
                                charge(ctx, 15);
                                v0 = subu(s0, s5);
                                mtc1(v0, f0);
                                cvt_s_w(f1, f0);
                                lq(v0, sp, 0xE0);
                                v0 = subu(s0, v0);
                                mtc1(v0, f0);
                                cvt_s_w(f0, f0);
                                div_s(f0, f1, f0);
                            }
                        } else {
                            // 0x0033c798
                            charge(ctx, 12);
                            mtc1(s5, f0);
                            cvt_s_w(f1, f0);
                            mtc1(v0, f0);
                            cvt_s_w(f0, f0);
                            div_s(f0, f1, f0);
                        }
                        // 0x0033c818
                        charge(ctx, 39);
                        v0 = 0x6A0000;
                        v0 = addiu(v0, -15200);  // &0x69C4A0
                        lqc2(vf11, v0, 0);  // 0x69C4A0
                        mfc1(v0, f0);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
                        v0 = addiu(sp, 0x150);
                        lqc2(vf10, v0, 0);
                        vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
                        mfc1(v0, f20);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
                        qmfc2(v0, vf10, false);  // qmfc2
                        ppach(v0, zero, v0);
                        ppacb(v0, zero, v0);
                        sw(v0, sp, 0x174);
                        lw(v0, sp, 0x174);
                        sw(v0, s2, 0);
                        sw(v0, s2, 4);
                        v0 = addiu(sp, 0x160);
                        lqc2(vf10, v0, 0);
                        vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
                        mfc1(v0, f20);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
                        qmfc2(v0, vf10, false);  // qmfc2
                        ppach(v0, zero, v0);
                        ppacb(v0, zero, v0);
                        sw(v0, sp, 0x170);
                        lw(v0, sp, 0x170);
                        sw(v0, s2, 8);
                        sw(v0, s2, 12);
                        v0 = addiu(s5, 1);
                        sw(v0, s4, 0);
                    } else {
                        // 0x0033c504
                        charge(ctx, 3);
                        v1 = 0;
                        for (;;) {
                            // 0x0033c53c
                            charge(ctx, 3);
                            v0 = slti(v1, 4);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x0033c510
                            charge(ctx, 11);
                            v0 = sll(v1, 1);
                            v0 = addu(v0, v1);
                            v0 = sll(v0, 2);
                            v0 = addu(s3, v0);
                            swc1(f22, v0, 0);
                            swc1(f22, v0, 4);
                            swc1(f22, v0, 8);
                            v0 = sll(v1, 2);
                            v0 = addu(s2, v0);
                            sw(zero, v0, 0);
                            v1 = addiu(v1, 1);
                        }
                        // 0x0033c548
                        charge(ctx, 3);
                        lq(v0, sp, 0xC0);
                        if (v0 == 0) {
                            // 0x0033c560
                            charge(ctx, 1);
                            v0 = si(-2);
                        } else {
                            // 0x0033c554
                            charge(ctx, 3);
                            v0 = si(-1);
                        }
                        // 0x0033c564
                        charge(ctx, 3);
                        sw(v0, s4, 0);
                    }
                } else {
                    // 0x0033c3a0
                    charge(ctx, 2);
                    if (s6 != 0) {
                        // 0x0033c3a8
                        charge(ctx, 23);
                        a0 = 0;
                        jal(ctx, 0x33C3ACu, gen::fn_sub_358030_00358030);
                        mul_s(f0, f25, f0);
                        swc1(f0, s4, 8);
                        lwc1(f27, s1, 120);
                        a0 = 0;
                        jal(ctx, 0x33C3C4u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f24, f27);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f27, f0);
                        lwc1(f0, s1, 116);
                        mul_s(f0, f0, f1);
                        swc1(f0, s4, 4);
                        a0 = 0;
                        jal(ctx, 0x33C3F0u, gen::fn_sub_357FD0_00357fd0);
                        v0 = v0 & 0x1;
                        if (v0 != 0) {
                            // 0x0033c404
                            charge(ctx, 3);
                            lwc1(f0, s4, 4);
                            mul_s(f0, f0, f23);
                            swc1(f0, s4, 4);
                        }
                        // 0x0033c410
                        charge(ctx, 33);
                        swc1(f22, s4, 12);
                        lwc1(f27, s1, 108);
                        a0 = 0;
                        jal(ctx, 0x33C41Cu, gen::fn_sub_358030_00358030);
                        sub_s(f2, f24, f27);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f27, f0);
                        lwc1(f0, s1, 104);
                        mul_s(f1, f0, f1);
                        lq(v0, sp, 0xD0);
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        div_s(f0, f1, f0);
                        swc1(f0, s4, 16);
                        lwc1(f27, s1, 100);
                        a0 = 0;
                        jal(ctx, 0x33C460u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f24, f27);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f27, f0);
                        lwc1(f0, s1, 96);
                        mul_s(f0, f0, f1);
                        swc1(f0, s4, 20);
                        lw(v0, sp, 0x110);
                        if (v0 == 0) {
                            // 0x0033c4e8
                            charge(ctx, 1);
                            sw(zero, s4, 0);
                        } else {
                            // 0x0033c494
                            charge(ctx, 21);
                            a0 = 0;
                            jal(ctx, 0x33C498u, gen::fn_sub_357FD0_00357fd0);
                            divu(v0, s0);
                            mfhi(v1);
                            sw(v1, s4, 0);
                            lwc1(f3, s4, 16);
                            lq(v0, sp, 0xD0);
                            div(v1, v0);
                            mfhi(v0);
                            mtc1(v0, f0);
                            cvt_s_w(f2, f0);
                            lwc1(f1, s4, 12);
                            mtc1(zero, f0);
                            adda_s(f0, f1);
                            madd_s(f0, f3, f2);
                            swc1(f0, s4, 12);
                        }
                        // 0x0033c4ec
                        charge(ctx, 3);
                        s6 = addiu(s6, -1);
                    }
                }
            }
            // 0x0033c8b4
            charge(ctx, 4);
            fp = addiu(fp, 0x1);
            s4 = addiu(s4, 24);
            s3 = addiu(s3, 48);
            s2 = addiu(s2, 16);
        }
        // 0x0033c8d4
        charge(ctx, 9);
        lw(v0, s7, 16);
        lw(s0, v0, 24);
        a0 = s0;
        jal(ctx, 0x33C8E0u, gen::fn_sub_4933D0_004933d0);
        lhu(v1, s7, 0);
        v1 = v1 & 0x4;
        if (v1 != 0) {
            // 0x0033c8f8
            charge(ctx, 3);
            lhu(v1, s0, 12);
            v1 = v1 | 0x1;
            sh(v1, s0, 12);
        }
    }
    // 0x0033c904 (the shared epilogue, written out on this path)
    charge(ctx, 21);
    ld(ra, sp, 0xB0);
    lq(fp, sp, 0xA0);
    lq(s7, sp, 0x90);
    lq(s6, sp, 0x80);
    lq(s5, sp, 0x70);
    lq(s4, sp, 0x60);
    lq(s3, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f27, sp, 0x1C);
    lwc1(f26, sp, 0x18);
    lwc1(f25, sp, 0x14);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x180);
}

// 0x0033C960 sub_33C960 -- 448 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 4, slot 5 [k10Sprite4Draw] ($a0 = the instance): within the lifetime (+52 of the parameters vs the
// frame +52), colour = instance colour (+48) x the colour track at the frame (sub_32A120 on +36), on VU0 (bytes ->
// floats / 255, multiply, x 255, back to bytes) into the mesh's material colour (alpha 255 written as 254 and
// restored); the mesh is placed at the instance position / rotation / scale (sub_3238D0), its additive bit follows
// +86 and it is queued on the layer +40 (sub_323860). Every class-10 kind's draw is this body.
void sub_33C960(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    Vf vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x0033c960
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(v1, a0, 60);
    lw(s1, a0, 64);
    lw(s0, v1, 4);
    lw(a2, a0, 52);
    lw(a3, s1, kSpLifetime);
    at = sltu(a3, a2);
    if (at != 0) {
        // 0x0033c998
        charge(ctx, 2);
        if (a3 == 0) {
            goto L_0033c9a0;
        }
        // 0x0033cb04 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_0033c9a0:
    charge(ctx, 45);
    a0 = s1;
    a1 = addiu(s1, 36);
    jal(ctx, 0x33C9A8u, gen::fn_sub_32A120_0032a120);
    v1 = v0;
    lw(v0, s2, 48);
    sw(v0, sp, 0x48);
    v0 = addiu(sp, 0x48);
    lwc1(f0, gp, -32420);  // 0x7CAE4C
    lw(v0, v0, 0);
    pextlb(v0, zero, v0);
    pextlh(v0, zero, v0);
    qmtc2(v0, vf10, false);  // qmtc2
    vitof0(0xF, vf10, vf10);  // vitof0.xyzw
    mfc1(v0, f0);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vmove(0xF, vf11, vf10);  // vmove.xyzw
    sw(v1, sp, 0x44);
    v0 = addiu(sp, 0x44);
    lw(v0, v0, 0);
    pextlb(v0, zero, v0);
    pextlh(v0, zero, v0);
    qmtc2(v0, vf10, false);  // qmtc2
    vitof0(0xF, vf10, vf10);  // vitof0.xyzw
    mfc1(v0, f0);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
    v0 = 0x437F0000;
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
    qmfc2(v0, vf10, false);  // qmfc2
    ppach(v0, zero, v0);
    ppacb(v0, zero, v0);
    sw(v0, sp, 0x40);
    lw(v0, sp, 0x40);
    sw(v0, sp, 0x4C);
    lbu(v0, sp, 0x4F);
    a3 = 255;
    if (v0 == a3) {
        // 0x0033ca80
        charge(ctx, 12);
        v0 = 254;
        sb(v0, sp, 0x4F);
        lw(a2, s0, 20);
        lbu(a1, sp, 0x4C);
        lbu(a0, sp, 0x4D);
        lbu(v1, sp, 0x4E);
        lbu(v0, sp, 0x4F);
        sb(a1, a2, 4);
        sb(a0, a2, 5);
        sb(v1, a2, 6);
        sb(v0, a2, 7);
        sb(a3, sp, 0x4F);
    } else {
        // 0x0033ca54
        charge(ctx, 11);
        lw(a2, s0, 20);
        lbu(a1, sp, 0x4C);
        lbu(a0, sp, 0x4D);
        lbu(v1, sp, 0x4E);
        lbu(v0, sp, 0x4F);
        sb(a1, a2, 4);
        sb(a0, a2, 5);
        sb(v1, a2, 6);
        sb(v0, a2, 7);
    }
    // 0x0033cab0
    charge(ctx, 9);
    a0 = s0;
    a1 = s2;
    a2 = addiu(s2, 16);
    a3 = addiu(s2, 32);
    jal(ctx, 0x33CAC0u, gen::fn_sub_3238D0_003238d0);
    lbu(v0, s1, kSpAdditive);
    if (v0 == 0) {
        // 0x0033cae8
        charge(ctx, 3);
        lhu(v0, s0, 0);
        v0 = v0 & 0xFFFE;
        sh(v0, s0, 0);
    } else {
        // 0x0033cad4
        charge(ctx, 5);
        lhu(v0, s0, 0);
        v0 = v0 | 0x1;
        sh(v0, s0, 0);
    }
    // 0x0033caf4
    charge(ctx, 4);
    lhu(a1, s1, kSpLayer);
    a0 = s0;
    jal(ctx, 0x33CAFCu, gen::fn_sub_323860_00323860);
    // 0x0033cb04 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0033CB20 sub_33CB20 -- 232 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 5, slot 0 [k10Sprite5Init] ($a0 = the instance): locks the mesh geometry (vertices), clears all its
// vertices (12 bytes x vertex count), unlocks (re-instance when flagged) and marks every record free (word 0 = -1;
// records of 24 bytes).
void sub_33CB20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0033cb20
    enter(ctx, 36);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, 60);
    lw(s3, v0, 0);
    lw(s2, v0, 4);
    lw(v0, a0, 64);
    lw(s1, v0, 56);
    lw(v0, s2, 16);
    lw(a0, v0, 24);
    a1 = 2;
    jal(ctx, 0x33CB58u, gen::fn_geometryLock_00493370);
    lw(v0, s2, 16);
    lw(v0, v0, 24);
    lw(v0, v0, 92);
    lw(a0, v0, 20);
    lh(v1, s2, 8);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    a2 = sll(v0, 2);
    a1 = 0;
    jal(ctx, 0x33CB84u, gen::fn_memset_00521408);
    lw(v0, s2, 16);
    lw(s0, v0, 24);
    a0 = s0;
    jal(ctx, 0x33CB98u, gen::fn_sub_4933D0_004933d0);
    lhu(v1, s2, 0);
    v1 = v1 & 0x4;
    if (v1 != 0) {
        // 0x0033cbb0
        charge(ctx, 3);
        lhu(v1, s0, 12);
        v1 = v1 | 0x1;
        sh(v1, s0, 12);
    }
    // 0x0033cbbc
    charge(ctx, 4);
    a1 = 0;
    a0 = si(-1);
    for (;;) {
        // 0x0033cbd8
        charge(ctx, 4);
        v1 = slt(a1, s1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0033cbcc
        charge(ctx, 3);
        sw(a0, s3, 0);
        s3 = addiu(s3, 24);
        a1 = addiu(a1, 1);
    }
    // 0x0033cbe8
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0033CC10 sub_33CC10 -- 272 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 5 [k10Sprite5TexCoords] ($a0 = the kind object, $a1 = the kind parameters): locks the texture
// coordinates (rwGEOMETRYLOCK texcoords 0xFF0) and gives every particle quad its four (u, v): the even ones the left
// half, the odd ones the right half of the texture (u 0 / 0.5 / 1), v 0..1; unlocks, re-instance when flagged. (Same
// body as sub_33BE90.)
void sub_33CC10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0033cc10
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a1, 56);
    if (s0 != 0) {
        // 0x0033cc30
        charge(ctx, 15);
        lw(v0, s1, 4);
        lw(v0, v0, 16);
        lw(a0, v0, 24);
        a1 = 4080;
        jal(ctx, 0x33CC40u, gen::fn_geometryLock_00493370);
        lw(v0, s1, 4);
        lw(v0, v0, 16);
        lw(v0, v0, 24);
        lw(a1, v0, 52);
        a2 = 0;
        a0 = 0x3F000000;
        v1 = 0x3F800000;
        for (;;) {
            // 0x0033ccc8
            charge(ctx, 3);
            v0 = sltu(a2, s0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0033cc6c
            charge(ctx, 3);
            v0 = a2 & 0x1;
            if (v0 == 0) {
                // 0x0033cca0
                charge(ctx, 8);
                sw(a0, a1, 0);
                sw(zero, a1, 4);
                sw(v1, a1, 8);
                sw(zero, a1, 12);
                sw(a0, a1, 16);
                sw(v1, a1, 20);
                sw(v1, a1, 24);
                sw(v1, a1, 28);
            } else {
                // 0x0033cc78
                charge(ctx, 10);
                sw(zero, a1, 0);
                sw(zero, a1, 4);
                sw(a0, a1, 8);
                sw(zero, a1, 12);
                sw(zero, a1, 16);
                sw(v1, a1, 20);
                sw(a0, a1, 24);
                sw(v1, a1, 28);
            }
            // 0x0033ccc0
            charge(ctx, 2);
            a2 = addiu(a2, 1);
            a1 = addiu(a1, 32);
        }
        // 0x0033ccd4
        charge(ctx, 10);
        lw(s1, s1, 4);
        lw(v0, s1, 16);
        lw(s0, v0, 24);
        a0 = s0;
        jal(ctx, 0x33CCE4u, gen::fn_sub_4933D0_004933d0);
        lhu(v1, s1, 0);
        v1 = v1 & 0x4;
        if (v1 != 0) {
            // 0x0033ccfc
            charge(ctx, 3);
            lhu(v1, s0, 12);
            v1 = v1 | 0x1;
            sh(v1, s0, 12);
        }
    }
    // 0x0033cd08 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0033CD20 sub_33CD20 -- 232 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 5, slot 1 [k10Sprite5Create] ($a0 = the kind parameters, $a1 = block B (a frame list) or 0; returns
// the kind object): one RwMalloc block of 16 + 24 x count bytes, a quad mesh (sub_3233A0: count quads, 2 x 4, layout
// 0x69BDC8, vertex size 76); textured from block B (sub_323B90) or else with the manager's texture 19 (sub_3210A0 ->
// RwFrame op sub_494D50); the texture coordinates by sub_33CC10.
void sub_33CD20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0033cd20
    enter(ctx, 32);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v1, a0, 56);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v0 = sll(v0, 3);
    a0 = addiu(v0, 16);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x33CD5Cu, v0.u());
    s2 = v0;
    v1 = addiu(v0, 16);
    sw(v1, v0, 0);
    sw(v0, v0, 8);
    lhu(a0, s1, 56);
    a1 = 2;
    a2 = 4;
    a3 = 0x6A0000;
    a3 = addiu(a3, -16952);  // &0x69BDC8
    t0 = 76;
    jal(ctx, 0x33CD8Cu, gen::fn_sub_3233A0_003233a0);
    sw(v0, s2, 4);
    if (s0 != 0) {
        // 0x0033cdc8
        charge(ctx, 4);
        lw(a0, s2, 4);
        a1 = s0;
        jal(ctx, 0x33CDD0u, gen::fn_sub_323B90_00323b90);
    } else {
        // 0x0033cda0
        charge(ctx, 10);
        a0 = 19;
        jal(ctx, 0x33CDA4u, gen::fn_sub_3210A0_003210a0);
        lw(v1, s2, 4);
        lw(a0, v1, 20);
        a1 = v0;
        jal(ctx, 0x33CDB8u, gen::fn_sub_494D50_00494d50);
    }
    // 0x0033cdd8
    charge(ctx, 12);
    a0 = s2;
    a1 = s1;
    jal(ctx, 0x33CDE0u, gen::fn_sub_33CC10_0033cc10);
    v0 = s2;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0033CE10 sub_33CE10 -- 148 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 5, slot 3 [k10Sprite5Clone] ($a0 = the instance; returns a new kind object): a copy of the kind
// object for a clone: the same block size, the mesh duplicated (sub_323640 of the old object's mesh) and the texture
// coordinates by sub_33CC10.
void sub_33CE10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0033ce10
    enter(ctx, 37);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    lw(s1, a0, 64);
    lw(v1, s1, 56);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v0 = sll(v0, 3);
    a0 = addiu(v0, 16);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x33CE4Cu, v0.u());
    s2 = v0;
    v1 = addiu(v0, 16);
    sw(v1, v0, 0);
    sw(v0, v0, 8);
    lw(a0, s0, 4);
    jal(ctx, 0x33CE68u, gen::fn_sub_323640_00323640);
    sw(v0, s2, 4);
    a0 = s2;
    a1 = s1;
    jal(ctx, 0x33CE7Cu, gen::fn_sub_33CC10_0033cc10);
    v0 = s2;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0033CEB0 sub_33CEB0 -- 68 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 5, slot 2 [k10Sprite5Destroy] ($a0 = the kind object): destroys the mesh (+4, sub_3237C0
// [fxMeshDestroy]) and frees the block (+8, RwFree 0x96017C).
void sub_33CEB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0033ceb0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, kKoMesh);
    jal(ctx, 0x33CEC4u, gen::fn_sub_3237C0_003237c0);
    lw(a0, s0, 8);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x33CED8u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0033CF00 sub_33CF00 -- 2000 bytes; frame 0x190: ra sp+0xB0, fp sp+0xA0 (sq), s7 sp+0x90 (sq), s6 sp+0x80 (sq), s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f27 sp+0x1C, f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 5, slot 4 [k10Sprite5Update] ($a0 = the instance): within the lifetime. The particle life (+76) with
// its fade-in / fade-out fractions (+68 / +72, reversed by a kind flag) gives the alpha ramp; unless the once flag
// (+85) holds the emission after frame 0, the re-emission period is +80. The mesh is locked (vertices + prelight) and
// each record runs: a free one is (re-)emitted with random values from the parameters' ranges (sub_358030 = random
// float, sub_357FD0 = random int: angle, speeds +104 / +112 / +120 with their randomness, size +96; the fade
// fractions swap with the flag +132) and a random start age; a live one ages, its colour is blended from colour A
// (+88) to colour B (+92) with the alpha ramp, and its camera-facing quads are rebuilt (cosf / sinf of its angle, VU0
// scaling) into the mesh vertices; then the mesh is unlocked (re-instance when flagged).
void sub_33CF00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26}, f27{ctx, 27};
    Vf vf0{ctx, 0}, vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11}, vf12{ctx, 12};
    // 0x0033cf00
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x190);
    sd(ra, sp, 0xB0);
    sq(fp, sp, 0xA0);
    sq(s7, sp, 0x90);
    sq(s6, sp, 0x80);
    sq(s5, sp, 0x70);
    sq(s4, sp, 0x60);
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f27, sp, 0x1C);
    swc1(f26, sp, 0x18);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(s1, a0, 64);
    lw(v1, s1, kSpLifetime);
    lw(a1, a0, 52);
    at = sltu(v1, a1);
    if (at != 0) {
        // 0x0033cf64
        charge(ctx, 2);
        if (v1 == 0) {
            goto L_0033cf6c;
        }
        // 0x0033d67c (the shared epilogue, written out on this path)
        charge(ctx, 21);
        ld(ra, sp, 0xB0);
        lq(fp, sp, 0xA0);
        lq(s7, sp, 0x90);
        lq(s6, sp, 0x80);
        lq(s5, sp, 0x70);
        lq(s4, sp, 0x60);
        lq(s3, sp, 0x50);
        lq(s2, sp, 0x40);
        lq(s1, sp, 0x30);
        lq(s0, sp, 0x20);
        lwc1(f27, sp, 0x1C);
        lwc1(f26, sp, 0x18);
        lwc1(f25, sp, 0x14);
        lwc1(f24, sp, 0x10);
        lwc1(f23, sp, 0xC);
        lwc1(f22, sp, 0x8);
        lwc1(f21, sp, 0x4);
        lwc1(f20, sp, 0x0);
        sp = addiu(sp, 0x190);
        return;
    }
L_0033cf6c:
    charge(ctx, 8);
    lw(v1, a0, 60);
    lw(s4, v1, 0);
    lw(s7, v1, 4);
    lw(v1, s1, kSpCount);
    sw(v1, sp, 0x110);
    lw(s0, s1, kSpLife);
    if (s0 != 0) {
        // 0x0033cf8c
        charge(ctx, 3);
        lbu(v0, s1, 132);
        if (v0 == 0) {
            // 0x0033cffc
            charge(ctx, 19);
            sw(zero, sp, 0xEC);
            sw(s0, sp, 0xE8);
            v0 = 1;
            sw(v0, sp, 0xD0);
            mtc1(s0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, s1, kSpFadeIn);
            mul_s(f0, f0, f1);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            sw(v0, sp, 0x100);
            lwc1(f0, s1, kSpFadeOut);
            mul_s(f0, f0, f1);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            sw(v0, sp, 0xF0);
        } else {
            // 0x0033cf98
            charge(ctx, 25);
            sw(s0, sp, 0xEC);
            sw(zero, sp, 0xE8);
            v0 = si(-1);
            sw(v0, sp, 0xD0);
            v0 = 0x3F800000;
            mtc1(v0, f3);
            lwc1(f0, s1, kSpFadeOut);
            sub_s(f2, f3, f0);
            mtc1(s0, f0);
            cvt_s_w(f1, f0);
            mul_s(f0, f2, f1);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            sw(v0, sp, 0x100);
            lwc1(f0, s1, kSpFadeIn);
            sub_s(f0, f3, f0);
            mul_s(f0, f0, f1);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            sw(v0, sp, 0xF0);
        }
        // 0x0033d048
        charge(ctx, 3);
        lbu(v0, s1, kSpOnce);
        if (v0 != 0) {
            // 0x0033d054
            charge(ctx, 2);
            if (a1 != 0) {
                goto L_0033d070;
            }
            // 0x0033d05c
            charge(ctx, 5);
            v0 = 1;
            sw(v0, sp, 0x120);
            lw(s6, sp, 0x110);
            goto L_0033d078;
        }
    L_0033d070:
        charge(ctx, 2);
        sw(zero, sp, 0x120);
        lw(s6, s1, kSpRespawn);
    L_0033d078:
        charge(ctx, 55);
        lw(v0, s7, 16);
        lw(a0, v0, 24);
        a1 = 10;
        jal(ctx, 0x33D084u, gen::fn_geometryLock_00493370);
        lw(v0, s7, 16);
        lw(v1, v0, 24);
        lw(v0, v1, 92);
        lw(s3, v0, 20);
        lw(s2, v1, 48);
        mtc1(zero, f22);
        sw(zero, sp, 0x154);
        sw(zero, sp, 0x15C);
        lw(v0, s1, kSpColourA);
        sw(v0, sp, 0x18C);
        v0 = addiu(sp, 0x18C);
        lwc1(f0, gp, -32420);  // 0x7CAE4C
        lw(v0, v0, 0);
        pextlb(v0, zero, v0);
        pextlh(v0, zero, v0);
        qmtc2(v0, vf10, false);  // qmtc2
        vitof0(0xF, vf10, vf10);  // vitof0.xyzw
        mfc1(v0, f0);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        v0 = addiu(sp, 0x170);
        sqc2(vf10, v0, 0);
        lw(v0, s1, kSpColourB);
        sw(v0, sp, 0x188);
        v0 = addiu(sp, 0x188);
        lw(v0, v0, 0);
        pextlb(v0, zero, v0);
        pextlh(v0, zero, v0);
        qmtc2(v0, vf10, false);  // qmtc2
        vitof0(0xF, vf10, vf10);  // vitof0.xyzw
        mfc1(v0, f0);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        v0 = addiu(sp, 0x160);
        sqc2(vf10, v0, 0);
        lwc1(f26, s1, 128);
        lbu(v0, s1, kSpMode);
        sq(v0, sp, 0xC0);
        fp = 0;
        lwc1(f24, gp, -32352);  // 0x7CAE90
        v0 = 0x3F800000;
        mtc1(v0, f23);
        v0 = 0x3F000000;
        mtc1(v0, f21);
        v0 = 0x437F0000;
        mtc1(v0, f20);
        for (;;) {
            // 0x0033d63c
            charge(ctx, 4);
            lw(v0, sp, 0x110);
            v0 = slt(fp, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0033d154
            charge(ctx, 4);
            lw(s5, s4, 0);
            v0 = si(-2);
            if (s5 != v0) {
                // 0x0033d164
                charge(ctx, 3);
                v0 = si(-1);
                if (s5 != v0) {
                    // 0x0033d28c
                    charge(ctx, 3);
                    lw(v0, sp, 0xE8);
                    if (s5 != v0) {
                        // 0x0033d304
                        charge(ctx, 7);
                        mtc1(s5, f0);
                        cvt_s_w(f3, f0);
                        lwc1(f25, s4, 8);
                        c_lt_s(f26, f22);
                        if (cond(ctx)) {
                            // 0x0033d320
                            charge(ctx, 9);
                            lwc1(f0, s4, 4);
                            neg_s(f1, f0);
                            mul_s(f0, f21, f26);
                            div_s(f0, f1, f0);
                            mul_s(f0, f21, f0);
                            c_le_s(f3, f0);
                            if (!cond(ctx)) {
                                // 0x0033d344
                                charge(ctx, 1);
                                mov_s(f3, f0);
                            }
                        }
                        // 0x0033d348
                        charge(ctx, 113);
                        mul_s(f2, f26, f3);
                        lwc1(f1, s4, 4);
                        mtc1(zero, f0);
                        adda_s(f0, f1);
                        madd_s(f0, f21, f2);
                        mul_s(f1, f3, f0);
                        lwc1(f0, s4, 16);
                        add_s(f27, f1, f0);
                        mov_s(f12, f25);
                        jal(ctx, 0x33D370u, gen::fn_cosf_0052e6d8);
                        swc1(f0, sp, 0x150);
                        mov_s(f12, f25);
                        jal(ctx, 0x33D380u, gen::fn_sinf_0052e878);
                        swc1(f0, sp, 0x158);
                        v0 = addiu(sp, 0x150);
                        lqc2(vf10, v0, 0);
                        vmove(0xF, vf11, vf10);  // vmove.xyzw
                        lw(v0, s4, 12);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        a1 = addiu(sp, 0x130);
                        sqc2(vf10, a1, 0);
                        vmove(0xF, vf10, vf11);  // vmove.xyzw
                        mfc1(v0, f27);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        vmove(0xF, vf12, vf10);  // vmove.xyzw
                        vmove(0xF, vf10, vf11);  // vmove.xyzw
                        qmfc2(v0, vf10, false);  // qmfc2
                        mtc1(v0, f1);
                        qmfc2(v0, vf10, false);  // qmfc2
                        pexew(v0, v0);
                        mtc1(v0, f0);
                        mfc1(v0, f0);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vadd_bc(0x8, vf10, vf0, vf2, 0);  // vaddx.x
                        neg_s(f0, f1);
                        mfc1(v0, f0);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vadd_bc(0x2, vf10, vf0, vf2, 0);  // vaddx.z
                        lw(v0, s4, 20);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        a0 = addiu(sp, 0x140);
                        sqc2(vf10, a0, 0);
                        lqc2(vf10, a1, 0);
                        vadd(0xF, vf10, vf10, vf12);  // vadd.xyzw
                        lqc2(vf11, a0, 0);
                        vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
                        v1 = 0x6A0000;
                        v1 = addiu(v1, -15152);  // &0x69C4D0
                        sqc2(vf10, v1, 0);  // 0x69C4D0
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15152);  // 0x69C4D0
                        swc1(f0, s3, 0);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15148);  // 0x69C4D4
                        swc1(f0, s3, 4);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15144);  // 0x69C4D8
                        swc1(f0, s3, 8);
                        vsub(0xF, vf10, vf10, vf11);  // vsub.xyzw
                        vsub(0xF, vf10, vf10, vf11);  // vsub.xyzw
                        sqc2(vf10, v1, 0);  // 0x69C4D0
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15152);  // 0x69C4D0
                        swc1(f0, s3, 12);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15148);  // 0x69C4D4
                        swc1(f0, s3, 16);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15144);  // 0x69C4D8
                        swc1(f0, s3, 20);
                        lqc2(vf10, a1, 0);
                        vsub(0xE, vf10, vf0, vf10);  // vsub.xyz
                        vadd(0xF, vf10, vf10, vf12);  // vadd.xyzw
                        lqc2(vf11, a0, 0);
                        vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
                        sqc2(vf10, v1, 0);  // 0x69C4D0
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15152);  // 0x69C4D0
                        swc1(f0, s3, 24);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15148);  // 0x69C4D4
                        swc1(f0, s3, 28);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15144);  // 0x69C4D8
                        swc1(f0, s3, 32);
                        vsub(0xF, vf10, vf10, vf11);  // vsub.xyzw
                        vsub(0xF, vf10, vf10, vf11);  // vsub.xyzw
                        sqc2(vf10, v1, 0);  // 0x69C4D0
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15152);  // 0x69C4D0
                        swc1(f0, s3, 36);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15148);  // 0x69C4D4
                        swc1(f0, s3, 40);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15144);  // 0x69C4D8
                        swc1(f0, s3, 44);
                        lw(v0, sp, 0x100);
                        at = slt(s5, v0);
                        if (at == 0) {
                            // 0x0033d53c
                            charge(ctx, 4);
                            lw(v0, sp, 0xF0);
                            at = slt(v0, s5);
                            if (at == 0) {
                                // 0x0033d588
                                charge(ctx, 1);
                                mov_s(f0, f23);
                            } else {
                                // 0x0033d54c
                                charge(ctx, 15);
                                v0 = subu(s0, s5);
                                mtc1(v0, f0);
                                cvt_s_w(f1, f0);
                                lw(v0, sp, 0xF0);
                                v0 = subu(s0, v0);
                                mtc1(v0, f0);
                                cvt_s_w(f0, f0);
                                div_s(f0, f1, f0);
                            }
                        } else {
                            // 0x0033d50c
                            charge(ctx, 12);
                            mtc1(s5, f0);
                            cvt_s_w(f1, f0);
                            mtc1(v0, f0);
                            cvt_s_w(f0, f0);
                            div_s(f0, f1, f0);
                        }
                        // 0x0033d58c
                        charge(ctx, 40);
                        v0 = 0x6A0000;
                        v0 = addiu(v0, -15200);  // &0x69C4A0
                        lqc2(vf11, v0, 0);  // 0x69C4A0
                        mfc1(v0, f0);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
                        v0 = addiu(sp, 0x160);
                        lqc2(vf10, v0, 0);
                        vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
                        mfc1(v0, f20);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
                        qmfc2(v0, vf10, false);  // qmfc2
                        ppach(v0, zero, v0);
                        ppacb(v0, zero, v0);
                        sw(v0, sp, 0x184);
                        lw(v0, sp, 0x184);
                        sw(v0, s2, 0);
                        sw(v0, s2, 4);
                        v0 = addiu(sp, 0x170);
                        lqc2(vf10, v0, 0);
                        vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
                        mfc1(v0, f20);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
                        qmfc2(v0, vf10, false);  // qmfc2
                        ppach(v0, zero, v0);
                        ppacb(v0, zero, v0);
                        sw(v0, sp, 0x180);
                        lw(v0, sp, 0x180);
                        sw(v0, s2, 8);
                        sw(v0, s2, 12);
                        lw(v0, sp, 0xD0);
                        v0 = addu(s5, v0);
                        sw(v0, s4, 0);
                    } else {
                        // 0x0033d298
                        charge(ctx, 3);
                        v1 = 0;
                        for (;;) {
                            // 0x0033d2d0
                            charge(ctx, 3);
                            v0 = slti(v1, 4);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x0033d2a4
                            charge(ctx, 11);
                            v0 = sll(v1, 1);
                            v0 = addu(v0, v1);
                            v0 = sll(v0, 2);
                            v0 = addu(s3, v0);
                            swc1(f22, v0, 0);
                            swc1(f22, v0, 4);
                            swc1(f22, v0, 8);
                            v0 = sll(v1, 2);
                            v0 = addu(s2, v0);
                            sw(zero, v0, 0);
                            v1 = addiu(v1, 1);
                        }
                        // 0x0033d2dc
                        charge(ctx, 3);
                        lq(v0, sp, 0xC0);
                        if (v0 == 0) {
                            // 0x0033d2f4
                            charge(ctx, 1);
                            v0 = si(-2);
                        } else {
                            // 0x0033d2e8
                            charge(ctx, 3);
                            v0 = si(-1);
                        }
                        // 0x0033d2f8
                        charge(ctx, 3);
                        sw(v0, s4, 0);
                    }
                } else {
                    // 0x0033d170
                    charge(ctx, 2);
                    if (s6 != 0) {
                        // 0x0033d178
                        charge(ctx, 56);
                        a0 = 0;
                        jal(ctx, 0x33D17Cu, gen::fn_sub_358030_00358030);
                        mul_s(f0, f24, f0);
                        swc1(f0, s4, 8);
                        lwc1(f25, s1, 108);
                        a0 = 0;
                        jal(ctx, 0x33D194u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f23, f25);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f25, f0);
                        lwc1(f0, s1, 104);
                        mul_s(f0, f0, f1);
                        swc1(f0, s4, 12);
                        lwc1(f25, s1, 116);
                        a0 = 0;
                        jal(ctx, 0x33D1C4u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f23, f25);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f25, f0);
                        lwc1(f0, s1, 112);
                        mul_s(f0, f0, f1);
                        swc1(f0, s4, 16);
                        lwc1(f25, s1, 124);
                        a0 = 0;
                        jal(ctx, 0x33D1F4u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f23, f25);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f25, f0);
                        lwc1(f0, s1, 120);
                        mul_s(f0, f0, f1);
                        swc1(f0, s4, 4);
                        lwc1(f25, s1, 100);
                        a0 = 0;
                        jal(ctx, 0x33D224u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f23, f25);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f25, f0);
                        lwc1(f0, s1, 96);
                        mul_s(f0, f0, f1);
                        swc1(f0, s4, 20);
                        lw(v0, sp, 0x120);
                        if (v0 == 0) {
                            // 0x0033d278
                            charge(ctx, 2);
                            lw(v0, sp, 0xEC);
                            sw(v0, s4, 0);
                        } else {
                            // 0x0033d258
                            charge(ctx, 8);
                            a0 = 0;
                            jal(ctx, 0x33D25Cu, gen::fn_sub_357FD0_00357fd0);
                            divu(v0, s0);
                            mfhi(v0);
                            sw(v0, s4, 0);
                        }
                        // 0x0033d280
                        charge(ctx, 3);
                        s6 = addiu(s6, -1);
                    }
                }
            }
            // 0x0033d62c
            charge(ctx, 4);
            fp = addiu(fp, 0x1);
            s4 = addiu(s4, 24);
            s3 = addiu(s3, 48);
            s2 = addiu(s2, 16);
        }
        // 0x0033d64c
        charge(ctx, 9);
        lw(v0, s7, 16);
        lw(s0, v0, 24);
        a0 = s0;
        jal(ctx, 0x33D658u, gen::fn_sub_4933D0_004933d0);
        lhu(v1, s7, 0);
        v1 = v1 & 0x4;
        if (v1 != 0) {
            // 0x0033d670
            charge(ctx, 3);
            lhu(v1, s0, 12);
            v1 = v1 | 0x1;
            sh(v1, s0, 12);
        }
    }
    // 0x0033d67c (the shared epilogue, written out on this path)
    charge(ctx, 21);
    ld(ra, sp, 0xB0);
    lq(fp, sp, 0xA0);
    lq(s7, sp, 0x90);
    lq(s6, sp, 0x80);
    lq(s5, sp, 0x70);
    lq(s4, sp, 0x60);
    lq(s3, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f27, sp, 0x1C);
    lwc1(f26, sp, 0x18);
    lwc1(f25, sp, 0x14);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x190);
}

// 0x0033D6D0 sub_33D6D0 -- 448 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 5, slot 5 [k10Sprite5Draw] ($a0 = the instance): within the lifetime (+52 of the parameters vs the
// frame +52), colour = instance colour (+48) x the colour track at the frame (sub_32A120 on +36), on VU0 (bytes ->
// floats / 255, multiply, x 255, back to bytes) into the mesh's material colour (alpha 255 written as 254 and
// restored); the mesh is placed at the instance position / rotation / scale (sub_3238D0), its additive bit follows
// +86 and it is queued on the layer +40 (sub_323860). Every class-10 kind's draw is this body.
void sub_33D6D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    Vf vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x0033d6d0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(v1, a0, 60);
    lw(s1, a0, 64);
    lw(s0, v1, 4);
    lw(a2, a0, 52);
    lw(a3, s1, kSpLifetime);
    at = sltu(a3, a2);
    if (at != 0) {
        // 0x0033d708
        charge(ctx, 2);
        if (a3 == 0) {
            goto L_0033d710;
        }
        // 0x0033d874 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_0033d710:
    charge(ctx, 45);
    a0 = s1;
    a1 = addiu(s1, 36);
    jal(ctx, 0x33D718u, gen::fn_sub_32A120_0032a120);
    v1 = v0;
    lw(v0, s2, 48);
    sw(v0, sp, 0x48);
    v0 = addiu(sp, 0x48);
    lwc1(f0, gp, -32420);  // 0x7CAE4C
    lw(v0, v0, 0);
    pextlb(v0, zero, v0);
    pextlh(v0, zero, v0);
    qmtc2(v0, vf10, false);  // qmtc2
    vitof0(0xF, vf10, vf10);  // vitof0.xyzw
    mfc1(v0, f0);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vmove(0xF, vf11, vf10);  // vmove.xyzw
    sw(v1, sp, 0x44);
    v0 = addiu(sp, 0x44);
    lw(v0, v0, 0);
    pextlb(v0, zero, v0);
    pextlh(v0, zero, v0);
    qmtc2(v0, vf10, false);  // qmtc2
    vitof0(0xF, vf10, vf10);  // vitof0.xyzw
    mfc1(v0, f0);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
    v0 = 0x437F0000;
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
    qmfc2(v0, vf10, false);  // qmfc2
    ppach(v0, zero, v0);
    ppacb(v0, zero, v0);
    sw(v0, sp, 0x40);
    lw(v0, sp, 0x40);
    sw(v0, sp, 0x4C);
    lbu(v0, sp, 0x4F);
    a3 = 255;
    if (v0 == a3) {
        // 0x0033d7f0
        charge(ctx, 12);
        v0 = 254;
        sb(v0, sp, 0x4F);
        lw(a2, s0, 20);
        lbu(a1, sp, 0x4C);
        lbu(a0, sp, 0x4D);
        lbu(v1, sp, 0x4E);
        lbu(v0, sp, 0x4F);
        sb(a1, a2, 4);
        sb(a0, a2, 5);
        sb(v1, a2, 6);
        sb(v0, a2, 7);
        sb(a3, sp, 0x4F);
    } else {
        // 0x0033d7c4
        charge(ctx, 11);
        lw(a2, s0, 20);
        lbu(a1, sp, 0x4C);
        lbu(a0, sp, 0x4D);
        lbu(v1, sp, 0x4E);
        lbu(v0, sp, 0x4F);
        sb(a1, a2, 4);
        sb(a0, a2, 5);
        sb(v1, a2, 6);
        sb(v0, a2, 7);
    }
    // 0x0033d820
    charge(ctx, 9);
    a0 = s0;
    a1 = s2;
    a2 = addiu(s2, 16);
    a3 = addiu(s2, 32);
    jal(ctx, 0x33D830u, gen::fn_sub_3238D0_003238d0);
    lbu(v0, s1, kSpAdditive);
    if (v0 == 0) {
        // 0x0033d858
        charge(ctx, 3);
        lhu(v0, s0, 0);
        v0 = v0 & 0xFFFE;
        sh(v0, s0, 0);
    } else {
        // 0x0033d844
        charge(ctx, 5);
        lhu(v0, s0, 0);
        v0 = v0 | 0x1;
        sh(v0, s0, 0);
    }
    // 0x0033d864
    charge(ctx, 4);
    lhu(a1, s1, kSpLayer);
    a0 = s0;
    jal(ctx, 0x33D86Cu, gen::fn_sub_323860_00323860);
    // 0x0033d874 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0033D890 sub_33D890 -- 232 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 6, slot 0 [k10Sprite6Init] ($a0 = the instance): locks the mesh geometry (vertices), clears all its
// vertices (12 bytes x vertex count), unlocks (re-instance when flagged) and marks every record free (word 0 = -1;
// records of 36 bytes).
void sub_33D890(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0033d890
    enter(ctx, 36);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, 60);
    lw(s3, v0, 0);
    lw(s2, v0, 4);
    lw(v0, a0, 64);
    lw(s1, v0, 56);
    lw(v0, s2, 16);
    lw(a0, v0, 24);
    a1 = 2;
    jal(ctx, 0x33D8C8u, gen::fn_geometryLock_00493370);
    lw(v0, s2, 16);
    lw(v0, v0, 24);
    lw(v0, v0, 92);
    lw(a0, v0, 20);
    lh(v1, s2, 8);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    a2 = sll(v0, 2);
    a1 = 0;
    jal(ctx, 0x33D8F4u, gen::fn_memset_00521408);
    lw(v0, s2, 16);
    lw(s0, v0, 24);
    a0 = s0;
    jal(ctx, 0x33D908u, gen::fn_sub_4933D0_004933d0);
    lhu(v1, s2, 0);
    v1 = v1 & 0x4;
    if (v1 != 0) {
        // 0x0033d920
        charge(ctx, 3);
        lhu(v1, s0, 12);
        v1 = v1 | 0x1;
        sh(v1, s0, 12);
    }
    // 0x0033d92c
    charge(ctx, 4);
    a1 = 0;
    a0 = si(-1);
    for (;;) {
        // 0x0033d948
        charge(ctx, 4);
        v1 = slt(a1, s1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0033d93c
        charge(ctx, 3);
        sw(a0, s3, 0);
        s3 = addiu(s3, 40);
        a1 = addiu(a1, 1);
    }
    // 0x0033d958
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0033D980 sub_33D980 -- 272 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 6 [k10Sprite6TexCoords] ($a0 = the kind object, $a1 = the kind parameters): locks the texture
// coordinates (rwGEOMETRYLOCK texcoords 0xFF0) and gives every particle quad its four (u, v): the even ones the left
// half, the odd ones the right half of the texture (u 0 / 0.5 / 1), v 0..1; unlocks, re-instance when flagged. (Same
// body as sub_33BE90.)
void sub_33D980(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0033d980
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a1, 56);
    if (s0 != 0) {
        // 0x0033d9a0
        charge(ctx, 15);
        lw(v0, s1, 4);
        lw(v0, v0, 16);
        lw(a0, v0, 24);
        a1 = 4080;
        jal(ctx, 0x33D9B0u, gen::fn_geometryLock_00493370);
        lw(v0, s1, 4);
        lw(v0, v0, 16);
        lw(v0, v0, 24);
        lw(a1, v0, 52);
        a2 = 0;
        a0 = 0x3F000000;
        v1 = 0x3F800000;
        for (;;) {
            // 0x0033da38
            charge(ctx, 3);
            v0 = sltu(a2, s0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0033d9dc
            charge(ctx, 3);
            v0 = a2 & 0x1;
            if (v0 == 0) {
                // 0x0033da10
                charge(ctx, 8);
                sw(a0, a1, 0);
                sw(zero, a1, 4);
                sw(v1, a1, 8);
                sw(zero, a1, 12);
                sw(a0, a1, 16);
                sw(v1, a1, 20);
                sw(v1, a1, 24);
                sw(v1, a1, 28);
            } else {
                // 0x0033d9e8
                charge(ctx, 10);
                sw(zero, a1, 0);
                sw(zero, a1, 4);
                sw(a0, a1, 8);
                sw(zero, a1, 12);
                sw(zero, a1, 16);
                sw(v1, a1, 20);
                sw(a0, a1, 24);
                sw(v1, a1, 28);
            }
            // 0x0033da30
            charge(ctx, 2);
            a2 = addiu(a2, 1);
            a1 = addiu(a1, 32);
        }
        // 0x0033da44
        charge(ctx, 10);
        lw(s1, s1, 4);
        lw(v0, s1, 16);
        lw(s0, v0, 24);
        a0 = s0;
        jal(ctx, 0x33DA54u, gen::fn_sub_4933D0_004933d0);
        lhu(v1, s1, 0);
        v1 = v1 & 0x4;
        if (v1 != 0) {
            // 0x0033da6c
            charge(ctx, 3);
            lhu(v1, s0, 12);
            v1 = v1 | 0x1;
            sh(v1, s0, 12);
        }
    }
    // 0x0033da78 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0033DA90 sub_33DA90 -- 232 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 6, slot 1 [k10Sprite6Create] ($a0 = the kind parameters, $a1 = block B (a frame list) or 0; returns
// the kind object): one RwMalloc block of 16 + 36 x count bytes, a quad mesh (sub_3233A0: count quads, 2 x 4, layout
// 0x69BDC8, vertex size 76); textured from block B (sub_323B90) or else with the manager's texture 19 (sub_3210A0 ->
// RwFrame op sub_494D50); the texture coordinates by sub_33D980.
void sub_33DA90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0033da90
    enter(ctx, 32);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v1, a0, 56);
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 3);
    a0 = addiu(v0, 16);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x33DACCu, v0.u());
    s2 = v0;
    v1 = addiu(v0, 16);
    sw(v1, v0, 0);
    sw(v0, v0, 8);
    lhu(a0, s1, 56);
    a1 = 2;
    a2 = 4;
    a3 = 0x6A0000;
    a3 = addiu(a3, -16952);  // &0x69BDC8
    t0 = 76;
    jal(ctx, 0x33DAFCu, gen::fn_sub_3233A0_003233a0);
    sw(v0, s2, 4);
    if (s0 != 0) {
        // 0x0033db38
        charge(ctx, 4);
        lw(a0, s2, 4);
        a1 = s0;
        jal(ctx, 0x33DB40u, gen::fn_sub_323B90_00323b90);
    } else {
        // 0x0033db10
        charge(ctx, 10);
        a0 = 18;
        jal(ctx, 0x33DB14u, gen::fn_sub_3210A0_003210a0);
        lw(v1, s2, 4);
        lw(a0, v1, 20);
        a1 = v0;
        jal(ctx, 0x33DB28u, gen::fn_sub_494D50_00494d50);
    }
    // 0x0033db48
    charge(ctx, 12);
    a0 = s2;
    a1 = s1;
    jal(ctx, 0x33DB50u, gen::fn_sub_33D980_0033d980);
    v0 = s2;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0033DB80 sub_33DB80 -- 148 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 6, slot 3 [k10Sprite6Clone] ($a0 = the instance; returns a new kind object): a copy of the kind
// object for a clone: the same block size, the mesh duplicated (sub_323640 of the old object's mesh) and the texture
// coordinates by sub_33D980.
void sub_33DB80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0033db80
    enter(ctx, 37);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    lw(s1, a0, 64);
    lw(v1, s1, 56);
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 3);
    a0 = addiu(v0, 16);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x33DBBCu, v0.u());
    s2 = v0;
    v1 = addiu(v0, 16);
    sw(v1, v0, 0);
    sw(v0, v0, 8);
    lw(a0, s0, 4);
    jal(ctx, 0x33DBD8u, gen::fn_sub_323640_00323640);
    sw(v0, s2, 4);
    a0 = s2;
    a1 = s1;
    jal(ctx, 0x33DBECu, gen::fn_sub_33D980_0033d980);
    v0 = s2;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0033DC20 sub_33DC20 -- 68 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 6, slot 2 [k10Sprite6Destroy] ($a0 = the kind object): destroys the mesh (+4, sub_3237C0
// [fxMeshDestroy]) and frees the block (+8, RwFree 0x96017C).
void sub_33DC20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0033dc20
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, kKoMesh);
    jal(ctx, 0x33DC34u, gen::fn_sub_3237C0_003237c0);
    lw(a0, s0, 8);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x33DC48u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0033DC70 sub_33DC70 -- 2256 bytes; frame 0x180: ra sp+0xC0, fp sp+0xB0 (sq), s7 sp+0xA0 (sq), s6 sp+0x90 (sq), s5 sp+0x80 (sq), s4 sp+0x70 (sq), s3 sp+0x60 (sq), s2 sp+0x50 (sq), s1 sp+0x40 (sq), s0 sp+0x30 (sq), f29 sp+0x24, f28 sp+0x20, f27 sp+0x1C, f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 6, slot 4 [k10Sprite6Update] ($a0 = the instance): within the lifetime. The particle life (+76) with
// its fade-in / fade-out fractions (+68 / +72, reversed by a kind flag) gives the alpha ramp; unless the once flag
// (+85) holds the emission after frame 0, the re-emission period is +80. The mesh is locked (vertices + prelight) and
// each record runs: a free one is (re-)emitted with random values from the parameters' ranges (sub_358030 = random
// float, sub_357FD0 = random int: angle, start / end speed +104..+116 and start / end size +120..+132 with per-frame
// steps over the life, +140..) and a random start age; a live one ages, its colour is blended from colour A (+88) to
// colour B (+92) with the alpha ramp, and its camera-facing quads are rebuilt (cosf / sinf of its angle, VU0 scaling)
// into the mesh vertices; then the mesh is unlocked (re-instance when flagged).
void sub_33DC70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26}, f27{ctx, 27}, f28{ctx, 28}, f29{ctx, 29};
    Vf vf0{ctx, 0}, vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11}, vf12{ctx, 12};
    // 0x0033dc70
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x180);
    sd(ra, sp, 0xC0);
    sq(fp, sp, 0xB0);
    sq(s7, sp, 0xA0);
    sq(s6, sp, 0x90);
    sq(s5, sp, 0x80);
    sq(s4, sp, 0x70);
    sq(s3, sp, 0x60);
    sq(s2, sp, 0x50);
    sq(s1, sp, 0x40);
    sq(s0, sp, 0x30);
    swc1(f29, sp, 0x24);
    swc1(f28, sp, 0x20);
    swc1(f27, sp, 0x1C);
    swc1(f26, sp, 0x18);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(s1, a0, 64);
    lw(v1, s1, kSpLifetime);
    lw(a1, a0, 52);
    at = sltu(v1, a1);
    if (at != 0) {
        // 0x0033dcdc
        charge(ctx, 2);
        if (v1 == 0) {
            goto L_0033dce4;
        }
        // 0x0033e4e4 (the shared epilogue, written out on this path)
        charge(ctx, 23);
        ld(ra, sp, 0xC0);
        lq(fp, sp, 0xB0);
        lq(s7, sp, 0xA0);
        lq(s6, sp, 0x90);
        lq(s5, sp, 0x80);
        lq(s4, sp, 0x70);
        lq(s3, sp, 0x60);
        lq(s2, sp, 0x50);
        lq(s1, sp, 0x40);
        lq(s0, sp, 0x30);
        lwc1(f29, sp, 0x24);
        lwc1(f28, sp, 0x20);
        lwc1(f27, sp, 0x1C);
        lwc1(f26, sp, 0x18);
        lwc1(f25, sp, 0x14);
        lwc1(f24, sp, 0x10);
        lwc1(f23, sp, 0xC);
        lwc1(f22, sp, 0x8);
        lwc1(f21, sp, 0x4);
        lwc1(f20, sp, 0x0);
        sp = addiu(sp, 0x180);
        return;
    }
L_0033dce4:
    charge(ctx, 8);
    lw(v1, a0, 60);
    lw(s4, v1, 0);
    lw(s7, v1, 4);
    lw(v1, s1, kSpCount);
    sq(v1, sp, 0x100);
    lw(s0, s1, kSpLife);
    if (s0 != 0) {
        // 0x0033dd04
        charge(ctx, 3);
        lbu(v0, s1, kSpOnce);
        if (v0 != 0) {
            // 0x0033dd10
            charge(ctx, 2);
            if (a1 != 0) {
                goto L_0033dd2c;
            }
            // 0x0033dd18
            charge(ctx, 5);
            v0 = 1;
            sw(v0, sp, 0x110);
            paddub(s6, v1, zero);
            goto L_0033dd34;
        }
    L_0033dd2c:
        charge(ctx, 2);
        sw(zero, sp, 0x110);
        lw(s6, s1, kSpRespawn);
    L_0033dd34:
        charge(ctx, 70);
        lw(v0, s7, 16);
        lw(a0, v0, 24);
        a1 = 10;
        jal(ctx, 0x33DD40u, gen::fn_geometryLock_00493370);
        lw(v0, s7, 16);
        lw(v1, v0, 24);
        lw(v0, v1, 92);
        lw(s3, v0, 20);
        lw(s2, v1, 48);
        mtc1(zero, f23);
        sw(zero, sp, 0x144);
        sw(zero, sp, 0x14C);
        lw(v0, s1, kSpColourA);
        sw(v0, sp, 0x17C);
        v0 = addiu(sp, 0x17C);
        lwc1(f0, gp, -32420);  // 0x7CAE4C
        lw(v0, v0, 0);
        pextlb(v0, zero, v0);
        pextlh(v0, zero, v0);
        qmtc2(v0, vf10, false);  // qmtc2
        vitof0(0xF, vf10, vf10);  // vitof0.xyzw
        mfc1(v0, f0);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        v0 = addiu(sp, 0x160);
        sqc2(vf10, v0, 0);
        lw(v0, s1, kSpColourB);
        sw(v0, sp, 0x178);
        v0 = addiu(sp, 0x178);
        lw(v0, v0, 0);
        pextlb(v0, zero, v0);
        pextlh(v0, zero, v0);
        qmtc2(v0, vf10, false);  // qmtc2
        vitof0(0xF, vf10, vf10);  // vitof0.xyzw
        mfc1(v0, f0);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        v0 = addiu(sp, 0x150);
        sqc2(vf10, v0, 0);
        mtc1(s0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, s1, kSpFadeIn);
        mul_s(f0, f0, f1);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        sq(v0, sp, 0xF0);
        lwc1(f0, s1, kSpFadeOut);
        mul_s(f0, f0, f1);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        sq(v0, sp, 0xE0);
        lwc1(f27, s1, 160);
        lbu(v0, s1, kSpMode);
        sq(v0, sp, 0xD0);
        fp = 0;
        lwc1(f25, gp, -32352);  // 0x7CAE90
        v0 = 0x3F800000;
        mtc1(v0, f24);
        v0 = 0x3F000000;
        mtc1(v0, f22);
        v0 = 0x437F0000;
        mtc1(v0, f21);
        for (;;) {
            // 0x0033e4a4
            charge(ctx, 4);
            lq(v0, sp, 0x100);
            v0 = slt(fp, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0033de4c
            charge(ctx, 4);
            lw(s5, s4, 0);
            v0 = si(-2);
            if (s5 != v0) {
                // 0x0033de5c
                charge(ctx, 3);
                v0 = si(-1);
                if (s5 != v0) {
                    // 0x0033e104
                    charge(ctx, 3);
                    v0 = slt(s5, s0);
                    if (v0 != 0) {
                        // 0x0033e17c
                        charge(ctx, 127);
                        mtc1(s5, f0);
                        cvt_s_w(f3, f0);
                        mul_s(f2, f27, f3);
                        lwc1(f1, s4, 8);
                        mtc1(zero, f0);
                        adda_s(f0, f1);
                        madd_s(f0, f22, f2);
                        mul_s(f1, f3, f0);
                        lwc1(f0, s4, 4);
                        add_s(f29, f1, f0);
                        lwc1(f26, s4, 28);
                        lwc1(f28, s4, 20);
                        mov_s(f12, f29);
                        jal(ctx, 0x33E1B8u, gen::fn_cosf_0052e6d8);
                        mov_s(f20, f0);
                        mov_s(f12, f29);
                        jal(ctx, 0x33E1C8u, gen::fn_sinf_0052e878);
                        mul_s(f1, f20, f28);
                        swc1(f1, sp, 0x140);
                        mul_s(f1, f0, f28);
                        swc1(f1, sp, 0x148);
                        mul_s(f1, f20, f26);
                        swc1(f1, sp, 0x130);
                        sub_s(f1, f24, f26);
                        swc1(f1, sp, 0x134);
                        mul_s(f1, f0, f26);
                        swc1(f1, sp, 0x138);
                        v0 = addiu(sp, 0x130);
                        lqc2(vf10, v0, 0);
                        vmul(0xE, vf2, vf10, vf10);  // vmul.xyz
                        vmula_bc(0x1, vf0, vf2, 0);  // vmulax.w
                        vmadda_bc(0x1, vf0, vf2, 1);  // vmadday.w
                        vmadd_bc(0x1, vf2, vf0, vf2, 2);  // vmaddz.w
                        vrsqrt(vf0, 3, vf2, 3);  // vrsqrt
                        vwaitq(ctx);
                        vmulq(0xE, vf10, vf10);  // vmulq.xyz
                        vmove(0xF, vf12, vf10);  // vmove.xyzw
                        swc1(f0, sp, 0x130);
                        swc1(f23, sp, 0x134);
                        neg_s(f0, f20);
                        swc1(f0, sp, 0x138);
                        lqc2(vf10, v0, 0);
                        lw(v0, s4, 36);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        a1 = addiu(sp, 0x120);
                        sqc2(vf10, a1, 0);
                        a0 = addiu(sp, 0x140);
                        lqc2(vf10, a0, 0);
                        lqc2(vf11, a1, 0);
                        vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
                        v1 = 0x6A0000;
                        v1 = addiu(v1, -15152);  // &0x69C4D0
                        sqc2(vf10, v1, 0);  // 0x69C4D0
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15152);  // 0x69C4D0
                        swc1(f0, s3, 24);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15148);  // 0x69C4D4
                        swc1(f0, s3, 28);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15144);  // 0x69C4D8
                        swc1(f0, s3, 32);
                        vsub(0xF, vf10, vf10, vf11);  // vsub.xyzw
                        vsub(0xF, vf10, vf10, vf11);  // vsub.xyzw
                        sqc2(vf10, v1, 0);  // 0x69C4D0
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15152);  // 0x69C4D0
                        swc1(f0, s3, 36);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15148);  // 0x69C4D4
                        swc1(f0, s3, 40);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15144);  // 0x69C4D8
                        swc1(f0, s3, 44);
                        vmove(0xF, vf11, vf12);  // vmove.xyzw
                        lw(v0, s4, 12);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
                        lqc2(vf10, a0, 0);
                        vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
                        lqc2(vf11, a1, 0);
                        vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
                        sqc2(vf10, v1, 0);  // 0x69C4D0
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15152);  // 0x69C4D0
                        swc1(f0, s3, 0);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15148);  // 0x69C4D4
                        swc1(f0, s3, 4);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15144);  // 0x69C4D8
                        swc1(f0, s3, 8);
                        vsub(0xF, vf10, vf10, vf11);  // vsub.xyzw
                        vsub(0xF, vf10, vf10, vf11);  // vsub.xyzw
                        sqc2(vf10, v1, 0);  // 0x69C4D0
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15152);  // 0x69C4D0
                        swc1(f0, s3, 12);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15148);  // 0x69C4D4
                        swc1(f0, s3, 16);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15144);  // 0x69C4D8
                        swc1(f0, s3, 20);
                        lwc1(f1, s4, 16);
                        lwc1(f0, s4, 12);
                        add_s(f0, f0, f1);
                        swc1(f0, s4, 12);
                        lwc1(f1, s4, 32);
                        lwc1(f0, s4, 28);
                        add_s(f0, f0, f1);
                        swc1(f0, s4, 28);
                        lwc1(f1, s4, 24);
                        lwc1(f0, s4, 20);
                        add_s(f0, f0, f1);
                        swc1(f0, s4, 20);
                        lq(v0, sp, 0xF0);
                        at = slt(s5, v0);
                        if (at == 0) {
                            // 0x0033e3a8
                            charge(ctx, 4);
                            lq(v0, sp, 0xE0);
                            at = slt(v0, s5);
                            if (at == 0) {
                                // 0x0033e3f4
                                charge(ctx, 1);
                                mov_s(f0, f24);
                            } else {
                                // 0x0033e3b8
                                charge(ctx, 15);
                                v0 = subu(s0, s5);
                                mtc1(v0, f0);
                                cvt_s_w(f1, f0);
                                lq(v0, sp, 0xE0);
                                v0 = subu(s0, v0);
                                mtc1(v0, f0);
                                cvt_s_w(f0, f0);
                                div_s(f0, f1, f0);
                            }
                        } else {
                            // 0x0033e378
                            charge(ctx, 12);
                            mtc1(s5, f0);
                            cvt_s_w(f1, f0);
                            mtc1(v0, f0);
                            cvt_s_w(f0, f0);
                            div_s(f0, f1, f0);
                        }
                        // 0x0033e3f8
                        charge(ctx, 39);
                        v0 = 0x6A0000;
                        v0 = addiu(v0, -15200);  // &0x69C4A0
                        lqc2(vf11, v0, 0);  // 0x69C4A0
                        mfc1(v0, f0);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
                        v0 = addiu(sp, 0x150);
                        lqc2(vf10, v0, 0);
                        vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
                        mfc1(v0, f21);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
                        qmfc2(v0, vf10, false);  // qmfc2
                        ppach(v0, zero, v0);
                        ppacb(v0, zero, v0);
                        sw(v0, sp, 0x174);
                        lw(v0, sp, 0x174);
                        sw(v0, s2, 0);
                        sw(v0, s2, 4);
                        v0 = addiu(sp, 0x160);
                        lqc2(vf10, v0, 0);
                        vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
                        mfc1(v0, f21);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
                        qmfc2(v0, vf10, false);  // qmfc2
                        ppach(v0, zero, v0);
                        ppacb(v0, zero, v0);
                        sw(v0, sp, 0x170);
                        lw(v0, sp, 0x170);
                        sw(v0, s2, 8);
                        sw(v0, s2, 12);
                        v0 = addiu(s5, 1);
                        sw(v0, s4, 0);
                    } else {
                        // 0x0033e110
                        charge(ctx, 3);
                        v1 = 0;
                        for (;;) {
                            // 0x0033e148
                            charge(ctx, 3);
                            v0 = slti(v1, 4);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x0033e11c
                            charge(ctx, 11);
                            v0 = sll(v1, 1);
                            v0 = addu(v0, v1);
                            v0 = sll(v0, 2);
                            v0 = addu(s3, v0);
                            swc1(f23, v0, 0);
                            swc1(f23, v0, 4);
                            swc1(f23, v0, 8);
                            v0 = sll(v1, 2);
                            v0 = addu(s2, v0);
                            sw(zero, v0, 0);
                            v1 = addiu(v1, 1);
                        }
                        // 0x0033e154
                        charge(ctx, 3);
                        lq(v0, sp, 0xD0);
                        if (v0 == 0) {
                            // 0x0033e16c
                            charge(ctx, 1);
                            v0 = si(-2);
                        } else {
                            // 0x0033e160
                            charge(ctx, 3);
                            v0 = si(-1);
                        }
                        // 0x0033e170
                        charge(ctx, 3);
                        sw(v0, s4, 0);
                    }
                } else {
                    // 0x0033de68
                    charge(ctx, 2);
                    if (s6 != 0) {
                        // 0x0033de70
                        charge(ctx, 119);
                        a0 = 0;
                        jal(ctx, 0x33DE74u, gen::fn_sub_358030_00358030);
                        mul_s(f0, f25, f0);
                        swc1(f0, s4, 4);
                        lwc1(f20, s1, 108);
                        a0 = 0;
                        jal(ctx, 0x33DE8Cu, gen::fn_sub_358030_00358030);
                        sub_s(f2, f24, f20);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f20, f0);
                        lwc1(f0, s1, 104);
                        mul_s(f20, f0, f1);
                        lwc1(f26, s1, 116);
                        a0 = 0;
                        jal(ctx, 0x33DEB8u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f24, f26);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f26, f0);
                        lwc1(f0, s1, 112);
                        mul_s(f0, f0, f1);
                        swc1(f20, s4, 12);
                        sub_s(f1, f0, f20);
                        mtc1(s0, f0);
                        cvt_s_w(f0, f0);
                        div_s(f0, f1, f0);
                        swc1(f0, s4, 16);
                        lwc1(f20, s1, 124);
                        a0 = 0;
                        jal(ctx, 0x33DF00u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f24, f20);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f20, f0);
                        lwc1(f0, s1, 120);
                        mul_s(f20, f0, f1);
                        lwc1(f26, s1, 132);
                        a0 = 0;
                        jal(ctx, 0x33DF2Cu, gen::fn_sub_358030_00358030);
                        sub_s(f2, f24, f26);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f26, f0);
                        lwc1(f0, s1, 128);
                        mul_s(f0, f0, f1);
                        swc1(f20, s4, 20);
                        sub_s(f1, f0, f20);
                        mtc1(s0, f0);
                        cvt_s_w(f0, f0);
                        div_s(f0, f1, f0);
                        swc1(f0, s4, 24);
                        lwc1(f20, s1, 140);
                        a0 = 0;
                        jal(ctx, 0x33DF74u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f24, f20);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f20, f0);
                        lwc1(f0, s1, 136);
                        mul_s(f20, f0, f1);
                        lwc1(f26, s1, 148);
                        a0 = 0;
                        jal(ctx, 0x33DFA0u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f24, f26);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f26, f0);
                        lwc1(f0, s1, 144);
                        mul_s(f0, f0, f1);
                        swc1(f20, s4, 28);
                        sub_s(f1, f0, f20);
                        mtc1(s0, f0);
                        cvt_s_w(f0, f0);
                        div_s(f0, f1, f0);
                        swc1(f0, s4, 32);
                        lwc1(f20, s1, 100);
                        a0 = 0;
                        jal(ctx, 0x33DFE8u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f24, f20);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f20, f0);
                        lwc1(f0, s1, 96);
                        mul_s(f0, f0, f1);
                        swc1(f0, s4, 36);
                        lwc1(f20, s1, 156);
                        a0 = 0;
                        jal(ctx, 0x33E018u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f24, f20);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f20, f0);
                        lwc1(f0, s1, 152);
                        mul_s(f0, f0, f1);
                        swc1(f0, s4, 8);
                        lw(v0, sp, 0x110);
                        if (v0 == 0) {
                            // 0x0033e0f4
                            charge(ctx, 1);
                            sw(zero, s4, 0);
                        } else {
                            // 0x0033e04c
                            charge(ctx, 7);
                            a0 = 0;
                            jal(ctx, 0x33E050u, gen::fn_sub_357FD0_00357fd0);
                            divu(v0, s0);
                            mfhi(v0);
                            if (i64(v0) < 0) {
                                // 0x0033e07c
                                charge(ctx, 7);
                                v1 = srl(v0, 1);
                                v0 = v0 & 0x1;
                                v1 = v1 | v0;
                                mtc1(v1, f0);
                                cvt_s_w(f3, f0);
                                add_s(f3, f3, f3);
                            } else {
                                // 0x0033e068
                                charge(ctx, 5);
                                mtc1(v0, f0);
                                cvt_s_w(f3, f0);
                            }
                            // 0x0033e098
                            charge(ctx, 23);
                            lwc1(f1, s4, 16);
                            lwc1(f0, s4, 12);
                            mtc1(zero, f2);
                            adda_s(f2, f0);
                            madd_s(f0, f1, f3);
                            swc1(f0, s4, 12);
                            lwc1(f1, s4, 24);
                            lwc1(f0, s4, 20);
                            adda_s(f2, f0);
                            madd_s(f0, f1, f3);
                            swc1(f0, s4, 20);
                            lwc1(f1, s4, 32);
                            lwc1(f0, s4, 28);
                            adda_s(f2, f0);
                            madd_s(f0, f1, f3);
                            swc1(f0, s4, 28);
                            cvt_w_s(f0, f3);
                            mfc1(v0, f0);
                            sw(v0, s4, 0);
                        }
                        // 0x0033e0f8
                        charge(ctx, 3);
                        s6 = addiu(s6, -1);
                    }
                }
            }
            // 0x0033e494
            charge(ctx, 4);
            fp = addiu(fp, 0x1);
            s4 = addiu(s4, 40);
            s3 = addiu(s3, 48);
            s2 = addiu(s2, 16);
        }
        // 0x0033e4b4
        charge(ctx, 9);
        lw(v0, s7, 16);
        lw(s0, v0, 24);
        a0 = s0;
        jal(ctx, 0x33E4C0u, gen::fn_sub_4933D0_004933d0);
        lhu(v1, s7, 0);
        v1 = v1 & 0x4;
        if (v1 != 0) {
            // 0x0033e4d8
            charge(ctx, 3);
            lhu(v1, s0, 12);
            v1 = v1 | 0x1;
            sh(v1, s0, 12);
        }
    }
    // 0x0033e4e4 (the shared epilogue, written out on this path)
    charge(ctx, 23);
    ld(ra, sp, 0xC0);
    lq(fp, sp, 0xB0);
    lq(s7, sp, 0xA0);
    lq(s6, sp, 0x90);
    lq(s5, sp, 0x80);
    lq(s4, sp, 0x70);
    lq(s3, sp, 0x60);
    lq(s2, sp, 0x50);
    lq(s1, sp, 0x40);
    lq(s0, sp, 0x30);
    lwc1(f29, sp, 0x24);
    lwc1(f28, sp, 0x20);
    lwc1(f27, sp, 0x1C);
    lwc1(f26, sp, 0x18);
    lwc1(f25, sp, 0x14);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x180);
}

// 0x0033E540 sub_33E540 -- 448 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 6, slot 5 [k10Sprite6Draw] ($a0 = the instance): within the lifetime (+52 of the parameters vs the
// frame +52), colour = instance colour (+48) x the colour track at the frame (sub_32A120 on +36), on VU0 (bytes ->
// floats / 255, multiply, x 255, back to bytes) into the mesh's material colour (alpha 255 written as 254 and
// restored); the mesh is placed at the instance position / rotation / scale (sub_3238D0), its additive bit follows
// +86 and it is queued on the layer +40 (sub_323860). Every class-10 kind's draw is this body.
void sub_33E540(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    Vf vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x0033e540
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(v1, a0, 60);
    lw(s1, a0, 64);
    lw(s0, v1, 4);
    lw(a2, a0, 52);
    lw(a3, s1, kSpLifetime);
    at = sltu(a3, a2);
    if (at != 0) {
        // 0x0033e578
        charge(ctx, 2);
        if (a3 == 0) {
            goto L_0033e580;
        }
        // 0x0033e6e4 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_0033e580:
    charge(ctx, 45);
    a0 = s1;
    a1 = addiu(s1, 36);
    jal(ctx, 0x33E588u, gen::fn_sub_32A120_0032a120);
    v1 = v0;
    lw(v0, s2, 48);
    sw(v0, sp, 0x48);
    v0 = addiu(sp, 0x48);
    lwc1(f0, gp, -32420);  // 0x7CAE4C
    lw(v0, v0, 0);
    pextlb(v0, zero, v0);
    pextlh(v0, zero, v0);
    qmtc2(v0, vf10, false);  // qmtc2
    vitof0(0xF, vf10, vf10);  // vitof0.xyzw
    mfc1(v0, f0);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vmove(0xF, vf11, vf10);  // vmove.xyzw
    sw(v1, sp, 0x44);
    v0 = addiu(sp, 0x44);
    lw(v0, v0, 0);
    pextlb(v0, zero, v0);
    pextlh(v0, zero, v0);
    qmtc2(v0, vf10, false);  // qmtc2
    vitof0(0xF, vf10, vf10);  // vitof0.xyzw
    mfc1(v0, f0);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
    v0 = 0x437F0000;
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
    qmfc2(v0, vf10, false);  // qmfc2
    ppach(v0, zero, v0);
    ppacb(v0, zero, v0);
    sw(v0, sp, 0x40);
    lw(v0, sp, 0x40);
    sw(v0, sp, 0x4C);
    lbu(v0, sp, 0x4F);
    a3 = 255;
    if (v0 == a3) {
        // 0x0033e660
        charge(ctx, 12);
        v0 = 254;
        sb(v0, sp, 0x4F);
        lw(a2, s0, 20);
        lbu(a1, sp, 0x4C);
        lbu(a0, sp, 0x4D);
        lbu(v1, sp, 0x4E);
        lbu(v0, sp, 0x4F);
        sb(a1, a2, 4);
        sb(a0, a2, 5);
        sb(v1, a2, 6);
        sb(v0, a2, 7);
        sb(a3, sp, 0x4F);
    } else {
        // 0x0033e634
        charge(ctx, 11);
        lw(a2, s0, 20);
        lbu(a1, sp, 0x4C);
        lbu(a0, sp, 0x4D);
        lbu(v1, sp, 0x4E);
        lbu(v0, sp, 0x4F);
        sb(a1, a2, 4);
        sb(a0, a2, 5);
        sb(v1, a2, 6);
        sb(v0, a2, 7);
    }
    // 0x0033e690
    charge(ctx, 9);
    a0 = s0;
    a1 = s2;
    a2 = addiu(s2, 16);
    a3 = addiu(s2, 32);
    jal(ctx, 0x33E6A0u, gen::fn_sub_3238D0_003238d0);
    lbu(v0, s1, kSpAdditive);
    if (v0 == 0) {
        // 0x0033e6c8
        charge(ctx, 3);
        lhu(v0, s0, 0);
        v0 = v0 & 0xFFFE;
        sh(v0, s0, 0);
    } else {
        // 0x0033e6b4
        charge(ctx, 5);
        lhu(v0, s0, 0);
        v0 = v0 | 0x1;
        sh(v0, s0, 0);
    }
    // 0x0033e6d4
    charge(ctx, 4);
    lhu(a1, s1, kSpLayer);
    a0 = s0;
    jal(ctx, 0x33E6DCu, gen::fn_sub_323860_00323860);
    // 0x0033e6e4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0033F4A0 sub_33F4A0 -- 232 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 8, slot 0 [k10Sprite8Init] ($a0 = the instance): locks the mesh geometry (vertices), clears all its
// vertices (12 bytes x vertex count), unlocks (re-instance when flagged) and marks every record free (word 0 = -1;
// records of 32 bytes).
void sub_33F4A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0033f4a0
    enter(ctx, 36);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, 60);
    lw(s3, v0, 0);
    lw(s2, v0, 4);
    lw(v0, a0, 64);
    lw(s1, v0, 56);
    lw(v0, s2, 16);
    lw(a0, v0, 24);
    a1 = 2;
    jal(ctx, 0x33F4D8u, gen::fn_geometryLock_00493370);
    lw(v0, s2, 16);
    lw(v0, v0, 24);
    lw(v0, v0, 92);
    lw(a0, v0, 20);
    lh(v1, s2, 8);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    a2 = sll(v0, 2);
    a1 = 0;
    jal(ctx, 0x33F504u, gen::fn_memset_00521408);
    lw(v0, s2, 16);
    lw(s0, v0, 24);
    a0 = s0;
    jal(ctx, 0x33F518u, gen::fn_sub_4933D0_004933d0);
    lhu(v1, s2, 0);
    v1 = v1 & 0x4;
    if (v1 != 0) {
        // 0x0033f530
        charge(ctx, 3);
        lhu(v1, s0, 12);
        v1 = v1 | 0x1;
        sh(v1, s0, 12);
    }
    // 0x0033f53c
    charge(ctx, 4);
    a1 = 0;
    a0 = si(-1);
    for (;;) {
        // 0x0033f558
        charge(ctx, 4);
        v1 = slt(a1, s1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0033f54c
        charge(ctx, 3);
        sw(a0, s3, 0);
        s3 = addiu(s3, 32);
        a1 = addiu(a1, 1);
    }
    // 0x0033f568
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0033F590 sub_33F590 -- 272 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 8 [k10Sprite8TexCoords] ($a0 = the kind object, $a1 = the kind parameters): locks the texture
// coordinates (rwGEOMETRYLOCK texcoords 0xFF0) and gives every particle quad its four (u, v): the even ones the left
// half, the odd ones the right half of the texture (u 0 / 0.5 / 1), v 0..1; unlocks, re-instance when flagged. (Same
// body as sub_33BE90.)
void sub_33F590(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0033f590
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a1, 56);
    if (s0 != 0) {
        // 0x0033f5b0
        charge(ctx, 15);
        lw(v0, s1, 4);
        lw(v0, v0, 16);
        lw(a0, v0, 24);
        a1 = 4080;
        jal(ctx, 0x33F5C0u, gen::fn_geometryLock_00493370);
        lw(v0, s1, 4);
        lw(v0, v0, 16);
        lw(v0, v0, 24);
        lw(a1, v0, 52);
        a2 = 0;
        a0 = 0x3F000000;
        v1 = 0x3F800000;
        for (;;) {
            // 0x0033f648
            charge(ctx, 3);
            v0 = sltu(a2, s0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0033f5ec
            charge(ctx, 3);
            v0 = a2 & 0x1;
            if (v0 == 0) {
                // 0x0033f620
                charge(ctx, 8);
                sw(a0, a1, 0);
                sw(zero, a1, 4);
                sw(v1, a1, 8);
                sw(zero, a1, 12);
                sw(a0, a1, 16);
                sw(v1, a1, 20);
                sw(v1, a1, 24);
                sw(v1, a1, 28);
            } else {
                // 0x0033f5f8
                charge(ctx, 10);
                sw(zero, a1, 0);
                sw(zero, a1, 4);
                sw(a0, a1, 8);
                sw(zero, a1, 12);
                sw(zero, a1, 16);
                sw(v1, a1, 20);
                sw(a0, a1, 24);
                sw(v1, a1, 28);
            }
            // 0x0033f640
            charge(ctx, 2);
            a2 = addiu(a2, 1);
            a1 = addiu(a1, 32);
        }
        // 0x0033f654
        charge(ctx, 10);
        lw(s1, s1, 4);
        lw(v0, s1, 16);
        lw(s0, v0, 24);
        a0 = s0;
        jal(ctx, 0x33F664u, gen::fn_sub_4933D0_004933d0);
        lhu(v1, s1, 0);
        v1 = v1 & 0x4;
        if (v1 != 0) {
            // 0x0033f67c
            charge(ctx, 3);
            lhu(v1, s0, 12);
            v1 = v1 | 0x1;
            sh(v1, s0, 12);
        }
    }
    // 0x0033f688 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0033F6A0 sub_33F6A0 -- 224 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 8, slot 1 [k10Sprite8Create] ($a0 = the kind parameters, $a1 = block B (a frame list) or 0; returns
// the kind object): one RwMalloc block of 16 + 32 x count bytes, a quad mesh (sub_3233A0: count quads, 2 x 4, layout
// 0x69BDC8, vertex size 76); textured from block B (sub_323B90) or else with the manager's texture 19 (sub_3210A0 ->
// RwFrame op sub_494D50); the texture coordinates by sub_33F590.
void sub_33F6A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0033f6a0
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v0, a0, 56);
    v0 = sll(v0, 5);
    a0 = addiu(v0, 16);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x33F6D4u, v0.u());
    s2 = v0;
    v1 = addiu(v0, 16);
    sw(v1, v0, 0);
    sw(v0, v0, 8);
    lhu(a0, s1, 56);
    a1 = 2;
    a2 = 4;
    a3 = 0x6A0000;
    a3 = addiu(a3, -16952);  // &0x69BDC8
    t0 = 76;
    jal(ctx, 0x33F704u, gen::fn_sub_3233A0_003233a0);
    sw(v0, s2, 4);
    if (s0 != 0) {
        // 0x0033f740
        charge(ctx, 4);
        lw(a0, s2, 4);
        a1 = s0;
        jal(ctx, 0x33F748u, gen::fn_sub_323B90_00323b90);
    } else {
        // 0x0033f718
        charge(ctx, 10);
        a0 = 19;
        jal(ctx, 0x33F71Cu, gen::fn_sub_3210A0_003210a0);
        lw(v1, s2, 4);
        lw(a0, v1, 20);
        a1 = v0;
        jal(ctx, 0x33F730u, gen::fn_sub_494D50_00494d50);
    }
    // 0x0033f750
    charge(ctx, 12);
    a0 = s2;
    a1 = s1;
    jal(ctx, 0x33F758u, gen::fn_sub_33F590_0033f590);
    v0 = s2;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0033F780 sub_33F780 -- 140 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 8, slot 3 [k10Sprite8Clone] ($a0 = the instance; returns a new kind object): a copy of the kind
// object for a clone: the same block size, the mesh duplicated (sub_323640 of the old object's mesh) and the texture
// coordinates by sub_33F590.
void sub_33F780(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0033f780
    enter(ctx, 35);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, 60);
    lw(s0, a0, 64);
    lw(v0, s0, 56);
    v0 = sll(v0, 5);
    a0 = addiu(v0, 16);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x33F7B4u, v0.u());
    s2 = v0;
    v1 = addiu(v0, 16);
    sw(v1, v0, 0);
    sw(v0, v0, 8);
    lw(a0, s1, 4);
    jal(ctx, 0x33F7D0u, gen::fn_sub_323640_00323640);
    sw(v0, s2, 4);
    a0 = s2;
    a1 = s0;
    jal(ctx, 0x33F7E4u, gen::fn_sub_33F590_0033f590);
    v0 = s2;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0033F810 sub_33F810 -- 68 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 8, slot 2 [k10Sprite8Destroy] ($a0 = the kind object): destroys the mesh (+4, sub_3237C0
// [fxMeshDestroy]) and frees the block (+8, RwFree 0x96017C).
void sub_33F810(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0033f810
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, kKoMesh);
    jal(ctx, 0x33F824u, gen::fn_sub_3237C0_003237c0);
    lw(a0, s0, 8);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x33F838u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0033F860 sub_33F860 -- 2204 bytes; frame 0x1A0: ra sp+0xC0, fp sp+0xB0 (sq), s7 sp+0xA0 (sq), s6 sp+0x90 (sq), s5 sp+0x80 (sq), s4 sp+0x70 (sq), s3 sp+0x60 (sq), s2 sp+0x50 (sq), s1 sp+0x40 (sq), s0 sp+0x30 (sq), f30 sp+0x28, f29 sp+0x24, f28 sp+0x20, f27 sp+0x1C, f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 8, slot 4 [k10Sprite8Update] ($a0 = the instance): within the lifetime. The particle life (+76) with
// its fade-in / fade-out fractions (+68 / +72, reversed by a kind flag) gives the alpha ramp; unless the once flag
// (+85) holds the emission after frame 0, the re-emission period is +80. The mesh is locked (vertices + prelight) and
// each record runs: a free one is (re-)emitted with random values from the parameters' ranges (sub_358030 = random
// float, sub_357FD0 = random int: angle, speeds +104..+120 and +136 with their randomness, size +96 with +100; the
// fade fractions swap with the flag +148) and a random start age; a live one ages, its colour is blended from colour
// A (+88) to colour B (+92) with the alpha ramp, and its camera-facing quads are rebuilt (cosf / sinf of its angle,
// VU0 scaling) into the mesh vertices; then the mesh is unlocked (re-instance when flagged).
void sub_33F860(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26}, f27{ctx, 27}, f28{ctx, 28}, f29{ctx, 29}, f30{ctx, 30};
    Vf vf0{ctx, 0}, vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11}, vf12{ctx, 12};
    // 0x0033f860
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1A0);
    sd(ra, sp, 0xC0);
    sq(fp, sp, 0xB0);
    sq(s7, sp, 0xA0);
    sq(s6, sp, 0x90);
    sq(s5, sp, 0x80);
    sq(s4, sp, 0x70);
    sq(s3, sp, 0x60);
    sq(s2, sp, 0x50);
    sq(s1, sp, 0x40);
    sq(s0, sp, 0x30);
    swc1(f30, sp, 0x28);
    swc1(f29, sp, 0x24);
    swc1(f28, sp, 0x20);
    swc1(f27, sp, 0x1C);
    swc1(f26, sp, 0x18);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(s1, a0, 64);
    lw(v1, s1, kSpLifetime);
    lw(a1, a0, 52);
    at = sltu(v1, a1);
    if (at != 0) {
        // 0x0033f8d0
        charge(ctx, 2);
        if (v1 == 0) {
            goto L_0033f8d8;
        }
        // 0x0034009c (the shared epilogue, written out on this path)
        charge(ctx, 24);
        ld(ra, sp, 0xC0);
        lq(fp, sp, 0xB0);
        lq(s7, sp, 0xA0);
        lq(s6, sp, 0x90);
        lq(s5, sp, 0x80);
        lq(s4, sp, 0x70);
        lq(s3, sp, 0x60);
        lq(s2, sp, 0x50);
        lq(s1, sp, 0x40);
        lq(s0, sp, 0x30);
        lwc1(f30, sp, 0x28);
        lwc1(f29, sp, 0x24);
        lwc1(f28, sp, 0x20);
        lwc1(f27, sp, 0x1C);
        lwc1(f26, sp, 0x18);
        lwc1(f25, sp, 0x14);
        lwc1(f24, sp, 0x10);
        lwc1(f23, sp, 0xC);
        lwc1(f22, sp, 0x8);
        lwc1(f21, sp, 0x4);
        lwc1(f20, sp, 0x0);
        sp = addiu(sp, 0x1A0);
        return;
    }
L_0033f8d8:
    charge(ctx, 8);
    lw(v1, a0, 60);
    lw(s4, v1, 0);
    lw(s7, v1, 4);
    lw(v1, s1, kSpCount);
    sw(v1, sp, 0x120);
    lw(s0, s1, kSpLife);
    if (s0 != 0) {
        // 0x0033f8f8
        charge(ctx, 3);
        lbu(v0, s1, 148);
        if (v0 == 0) {
            // 0x0033f968
            charge(ctx, 19);
            sw(zero, sp, 0xFC);
            sw(s0, sp, 0xF8);
            v0 = 1;
            sw(v0, sp, 0xE0);
            mtc1(s0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, s1, kSpFadeIn);
            mul_s(f0, f0, f1);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            sw(v0, sp, 0x110);
            lwc1(f0, s1, kSpFadeOut);
            mul_s(f0, f0, f1);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            sw(v0, sp, 0x100);
        } else {
            // 0x0033f904
            charge(ctx, 25);
            sw(s0, sp, 0xFC);
            sw(zero, sp, 0xF8);
            v0 = si(-1);
            sw(v0, sp, 0xE0);
            v0 = 0x3F800000;
            mtc1(v0, f3);
            lwc1(f0, s1, kSpFadeOut);
            sub_s(f2, f3, f0);
            mtc1(s0, f0);
            cvt_s_w(f1, f0);
            mul_s(f0, f2, f1);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            sw(v0, sp, 0x110);
            lwc1(f0, s1, kSpFadeIn);
            sub_s(f0, f3, f0);
            mul_s(f0, f0, f1);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            sw(v0, sp, 0x100);
        }
        // 0x0033f9b4
        charge(ctx, 3);
        lbu(v0, s1, kSpOnce);
        if (v0 != 0) {
            // 0x0033f9c0
            charge(ctx, 2);
            if (a1 != 0) {
                goto L_0033f9dc;
            }
            // 0x0033f9c8
            charge(ctx, 5);
            v0 = 1;
            sw(v0, sp, 0x130);
            lw(s6, sp, 0x120);
            goto L_0033f9e4;
        }
    L_0033f9dc:
        charge(ctx, 2);
        sw(zero, sp, 0x130);
        lw(s6, s1, kSpRespawn);
    L_0033f9e4:
        charge(ctx, 55);
        lw(v0, s7, 16);
        lw(a0, v0, 24);
        a1 = 10;
        jal(ctx, 0x33F9F0u, gen::fn_geometryLock_00493370);
        lw(v0, s7, 16);
        lw(v1, v0, 24);
        lw(v0, v1, 92);
        lw(s3, v0, 20);
        lw(s2, v1, 48);
        mtc1(zero, f24);
        sw(zero, sp, 0x164);
        sw(zero, sp, 0x16C);
        lw(v0, s1, kSpColourA);
        sw(v0, sp, 0x19C);
        v0 = addiu(sp, 0x19C);
        lwc1(f0, gp, -32420);  // 0x7CAE4C
        lw(v0, v0, 0);
        pextlb(v0, zero, v0);
        pextlh(v0, zero, v0);
        qmtc2(v0, vf10, false);  // qmtc2
        vitof0(0xF, vf10, vf10);  // vitof0.xyzw
        mfc1(v0, f0);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        v0 = addiu(sp, 0x180);
        sqc2(vf10, v0, 0);
        lw(v0, s1, kSpColourB);
        sw(v0, sp, 0x198);
        v0 = addiu(sp, 0x198);
        lw(v0, v0, 0);
        pextlb(v0, zero, v0);
        pextlh(v0, zero, v0);
        qmtc2(v0, vf10, false);  // qmtc2
        vitof0(0xF, vf10, vf10);  // vitof0.xyzw
        mfc1(v0, f0);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
        v0 = addiu(sp, 0x170);
        sqc2(vf10, v0, 0);
        lwc1(f30, s1, 144);
        lbu(v0, s1, kSpMode);
        sq(v0, sp, 0xD0);
        fp = 0;
        lwc1(f26, gp, -32352);  // 0x7CAE90
        v0 = 0x3F800000;
        mtc1(v0, f25);
        v0 = 0x3F000000;
        mtc1(v0, f23);
        v0 = 0x437F0000;
        mtc1(v0, f22);
        for (;;) {
            // 0x0034005c
            charge(ctx, 4);
            lw(v0, sp, 0x120);
            v0 = slt(fp, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0033fac0
            charge(ctx, 4);
            lw(s5, s4, 0);
            v0 = si(-2);
            if (s5 != v0) {
                // 0x0033fad0
                charge(ctx, 3);
                v0 = si(-1);
                if (s5 != v0) {
                    // 0x0033fc6c
                    charge(ctx, 3);
                    lw(v0, sp, 0xF8);
                    if (s5 != v0) {
                        // 0x0033fce4
                        charge(ctx, 7);
                        mtc1(s5, f0);
                        cvt_s_w(f3, f0);
                        lwc1(f28, s4, 8);
                        c_lt_s(f30, f24);
                        if (cond(ctx)) {
                            // 0x0033fd00
                            charge(ctx, 9);
                            lwc1(f0, s4, 4);
                            neg_s(f1, f0);
                            mul_s(f0, f23, f30);
                            div_s(f0, f1, f0);
                            mul_s(f0, f23, f0);
                            c_le_s(f3, f0);
                            if (!cond(ctx)) {
                                // 0x0033fd24
                                charge(ctx, 1);
                                mov_s(f3, f0);
                            }
                        }
                        // 0x0033fd28
                        charge(ctx, 129);
                        mul_s(f1, f30, f3);
                        lwc1(f0, s4, 4);
                        mtc1(zero, f2);
                        adda_s(f2, f0);
                        madd_s(f0, f23, f1);
                        mul_s(f29, f3, f0);
                        lwc1(f1, s4, 20);
                        lwc1(f0, s4, 16);
                        adda_s(f2, f0);
                        madd_s(f21, f1, f3);
                        lwc1(f27, s4, 24);
                        mov_s(f12, f28);
                        jal(ctx, 0x33FD5Cu, gen::fn_cosf_0052e6d8);
                        mov_s(f20, f0);
                        mov_s(f12, f28);
                        jal(ctx, 0x33FD6Cu, gen::fn_sinf_0052e878);
                        mul_s(f1, f20, f27);
                        swc1(f1, sp, 0x160);
                        sub_s(f1, f25, f27);
                        swc1(f1, sp, 0x164);
                        mul_s(f1, f0, f27);
                        swc1(f1, sp, 0x168);
                        v1 = addiu(sp, 0x160);
                        lqc2(vf10, v1, 0);
                        vmove(0xF, vf11, vf10);  // vmove.xyzw
                        lw(v0, s4, 12);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        a1 = addiu(sp, 0x140);
                        sqc2(vf10, a1, 0);
                        vmove(0xF, vf10, vf11);  // vmove.xyzw
                        mfc1(v0, f29);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        sqc2(vf10, v1, 0);
                        lwc1(f1, sp, 0x160);
                        mtc1(zero, f2);
                        adda_s(f2, f1);
                        madd_s(f1, f20, f21);
                        swc1(f1, sp, 0x160);
                        lwc1(f1, sp, 0x168);
                        adda_s(f2, f1);
                        madd_s(f1, f0, f21);
                        swc1(f1, sp, 0x168);
                        mfc1(v0, f0);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vadd_bc(0x8, vf10, vf0, vf2, 0);  // vaddx.x
                        mfc1(v0, f24);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vadd_bc(0x4, vf10, vf0, vf2, 0);  // vaddx.y
                        neg_s(f0, f20);
                        mfc1(v0, f0);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vadd_bc(0x2, vf10, vf0, vf2, 0);  // vaddx.z
                        lw(v0, s4, 28);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        a0 = addiu(sp, 0x150);
                        sqc2(vf10, a0, 0);
                        lqc2(vf12, v1, 0);
                        lqc2(vf10, a1, 0);
                        vadd(0xF, vf10, vf10, vf12);  // vadd.xyzw
                        lqc2(vf11, a0, 0);
                        vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
                        v1 = 0x6A0000;
                        v1 = addiu(v1, -15152);  // &0x69C4D0
                        sqc2(vf10, v1, 0);  // 0x69C4D0
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15152);  // 0x69C4D0
                        swc1(f0, s3, 0);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15148);  // 0x69C4D4
                        swc1(f0, s3, 4);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15144);  // 0x69C4D8
                        swc1(f0, s3, 8);
                        vsub(0xF, vf10, vf10, vf11);  // vsub.xyzw
                        vsub(0xF, vf10, vf10, vf11);  // vsub.xyzw
                        sqc2(vf10, v1, 0);  // 0x69C4D0
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15152);  // 0x69C4D0
                        swc1(f0, s3, 12);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15148);  // 0x69C4D4
                        swc1(f0, s3, 16);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15144);  // 0x69C4D8
                        swc1(f0, s3, 20);
                        lqc2(vf10, a1, 0);
                        vsub(0xE, vf10, vf0, vf10);  // vsub.xyz
                        vadd(0xF, vf10, vf10, vf12);  // vadd.xyzw
                        lqc2(vf11, a0, 0);
                        vadd(0xF, vf10, vf10, vf11);  // vadd.xyzw
                        sqc2(vf10, v1, 0);  // 0x69C4D0
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15152);  // 0x69C4D0
                        swc1(f0, s3, 24);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15148);  // 0x69C4D4
                        swc1(f0, s3, 28);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15144);  // 0x69C4D8
                        swc1(f0, s3, 32);
                        vsub(0xF, vf10, vf10, vf11);  // vsub.xyzw
                        vsub(0xF, vf10, vf10, vf11);  // vsub.xyzw
                        sqc2(vf10, v1, 0);  // 0x69C4D0
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15152);  // 0x69C4D0
                        swc1(f0, s3, 36);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15148);  // 0x69C4D4
                        swc1(f0, s3, 40);
                        v0 = 0x6A0000;
                        lwc1(f0, v0, -15144);  // 0x69C4D8
                        swc1(f0, s3, 44);
                        lw(v0, sp, 0x110);
                        at = slt(s5, v0);
                        if (at == 0) {
                            // 0x0033ff5c
                            charge(ctx, 4);
                            lw(v0, sp, 0x100);
                            at = slt(v0, s5);
                            if (at == 0) {
                                // 0x0033ffa8
                                charge(ctx, 1);
                                mov_s(f0, f25);
                            } else {
                                // 0x0033ff6c
                                charge(ctx, 15);
                                v0 = subu(s0, s5);
                                mtc1(v0, f0);
                                cvt_s_w(f1, f0);
                                lw(v0, sp, 0x100);
                                v0 = subu(s0, v0);
                                mtc1(v0, f0);
                                cvt_s_w(f0, f0);
                                div_s(f0, f1, f0);
                            }
                        } else {
                            // 0x0033ff2c
                            charge(ctx, 12);
                            mtc1(s5, f0);
                            cvt_s_w(f1, f0);
                            mtc1(v0, f0);
                            cvt_s_w(f0, f0);
                            div_s(f0, f1, f0);
                        }
                        // 0x0033ffac
                        charge(ctx, 40);
                        v0 = 0x6A0000;
                        v0 = addiu(v0, -15200);  // &0x69C4A0
                        lqc2(vf11, v0, 0);  // 0x69C4A0
                        mfc1(v0, f0);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
                        v0 = addiu(sp, 0x170);
                        lqc2(vf10, v0, 0);
                        vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
                        mfc1(v0, f22);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
                        qmfc2(v0, vf10, false);  // qmfc2
                        ppach(v0, zero, v0);
                        ppacb(v0, zero, v0);
                        sw(v0, sp, 0x194);
                        lw(v0, sp, 0x194);
                        sw(v0, s2, 0);
                        sw(v0, s2, 4);
                        v0 = addiu(sp, 0x180);
                        lqc2(vf10, v0, 0);
                        vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
                        mfc1(v0, f22);
                        qmtc2(v0, vf2, false);  // qmtc2
                        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                        vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
                        qmfc2(v0, vf10, false);  // qmfc2
                        ppach(v0, zero, v0);
                        ppacb(v0, zero, v0);
                        sw(v0, sp, 0x190);
                        lw(v0, sp, 0x190);
                        sw(v0, s2, 8);
                        sw(v0, s2, 12);
                        lw(v0, sp, 0xE0);
                        v0 = addu(s5, v0);
                        sw(v0, s4, 0);
                    } else {
                        // 0x0033fc78
                        charge(ctx, 3);
                        v1 = 0;
                        for (;;) {
                            // 0x0033fcb0
                            charge(ctx, 3);
                            v0 = slti(v1, 4);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x0033fc84
                            charge(ctx, 11);
                            v0 = sll(v1, 1);
                            v0 = addu(v0, v1);
                            v0 = sll(v0, 2);
                            v0 = addu(s3, v0);
                            swc1(f24, v0, 0);
                            swc1(f24, v0, 4);
                            swc1(f24, v0, 8);
                            v0 = sll(v1, 2);
                            v0 = addu(s2, v0);
                            sw(zero, v0, 0);
                            v1 = addiu(v1, 1);
                        }
                        // 0x0033fcbc
                        charge(ctx, 3);
                        lq(v0, sp, 0xD0);
                        if (v0 == 0) {
                            // 0x0033fcd4
                            charge(ctx, 1);
                            v0 = si(-2);
                        } else {
                            // 0x0033fcc8
                            charge(ctx, 3);
                            v0 = si(-1);
                        }
                        // 0x0033fcd8
                        charge(ctx, 3);
                        sw(v0, s4, 0);
                    }
                } else {
                    // 0x0033fadc
                    charge(ctx, 2);
                    if (s6 != 0) {
                        // 0x0033fae4
                        charge(ctx, 85);
                        a0 = 0;
                        jal(ctx, 0x33FAE8u, gen::fn_sub_358030_00358030);
                        mul_s(f0, f26, f0);
                        swc1(f0, s4, 8);
                        lwc1(f20, s1, 108);
                        a0 = 0;
                        jal(ctx, 0x33FB00u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f25, f20);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f20, f0);
                        lwc1(f0, s1, 104);
                        mul_s(f0, f0, f1);
                        swc1(f0, s4, 12);
                        lwc1(f20, s1, 116);
                        a0 = 0;
                        jal(ctx, 0x33FB30u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f25, f20);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f20, f0);
                        lwc1(f0, s1, 112);
                        mul_s(f20, f0, f1);
                        lwc1(f21, s1, 124);
                        a0 = 0;
                        jal(ctx, 0x33FB5Cu, gen::fn_sub_358030_00358030);
                        sub_s(f2, f25, f21);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f21, f0);
                        lwc1(f0, s1, 120);
                        mul_s(f0, f0, f1);
                        swc1(f20, s4, 16);
                        sub_s(f1, f0, f20);
                        mtc1(s0, f0);
                        cvt_s_w(f0, f0);
                        div_s(f0, f1, f0);
                        swc1(f0, s4, 20);
                        lwc1(f20, s1, 140);
                        a0 = 0;
                        jal(ctx, 0x33FBA4u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f25, f20);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f20, f0);
                        lwc1(f0, s1, 136);
                        mul_s(f0, f0, f1);
                        swc1(f0, s4, 4);
                        lwc1(f20, s1, 100);
                        a0 = 0;
                        jal(ctx, 0x33FBD4u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f25, f20);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f20, f0);
                        lwc1(f0, s1, 96);
                        mul_s(f0, f0, f1);
                        swc1(f0, s4, 28);
                        lwc1(f20, s1, 132);
                        a0 = 0;
                        jal(ctx, 0x33FC04u, gen::fn_sub_358030_00358030);
                        sub_s(f2, f25, f20);
                        mtc1(zero, f1);
                        adda_s(f1, f2);
                        madd_s(f1, f20, f0);
                        lwc1(f0, s1, 128);
                        mul_s(f0, f0, f1);
                        swc1(f0, s4, 24);
                        lw(v0, sp, 0x130);
                        if (v0 == 0) {
                            // 0x0033fc58
                            charge(ctx, 2);
                            lw(v0, sp, 0xFC);
                            sw(v0, s4, 0);
                        } else {
                            // 0x0033fc38
                            charge(ctx, 8);
                            a0 = 0;
                            jal(ctx, 0x33FC3Cu, gen::fn_sub_357FD0_00357fd0);
                            divu(v0, s0);
                            mfhi(v0);
                            sw(v0, s4, 0);
                        }
                        // 0x0033fc60
                        charge(ctx, 3);
                        s6 = addiu(s6, -1);
                    }
                }
            }
            // 0x0034004c
            charge(ctx, 4);
            fp = addiu(fp, 0x1);
            s4 = addiu(s4, 32);
            s3 = addiu(s3, 48);
            s2 = addiu(s2, 16);
        }
        // 0x0034006c
        charge(ctx, 9);
        lw(v0, s7, 16);
        lw(s0, v0, 24);
        a0 = s0;
        jal(ctx, 0x340078u, gen::fn_sub_4933D0_004933d0);
        lhu(v1, s7, 0);
        v1 = v1 & 0x4;
        if (v1 != 0) {
            // 0x00340090
            charge(ctx, 3);
            lhu(v1, s0, 12);
            v1 = v1 | 0x1;
            sh(v1, s0, 12);
        }
    }
    // 0x0034009c (the shared epilogue, written out on this path)
    charge(ctx, 24);
    ld(ra, sp, 0xC0);
    lq(fp, sp, 0xB0);
    lq(s7, sp, 0xA0);
    lq(s6, sp, 0x90);
    lq(s5, sp, 0x80);
    lq(s4, sp, 0x70);
    lq(s3, sp, 0x60);
    lq(s2, sp, 0x50);
    lq(s1, sp, 0x40);
    lq(s0, sp, 0x30);
    lwc1(f30, sp, 0x28);
    lwc1(f29, sp, 0x24);
    lwc1(f28, sp, 0x20);
    lwc1(f27, sp, 0x1C);
    lwc1(f26, sp, 0x18);
    lwc1(f25, sp, 0x14);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x1A0);
}

// 0x00340100 sub_340100 -- 448 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 10, kind 8, slot 5 [k10Sprite8Draw] ($a0 = the instance): within the lifetime (+52 of the parameters vs the
// frame +52), colour = instance colour (+48) x the colour track at the frame (sub_32A120 on +36), on VU0 (bytes ->
// floats / 255, multiply, x 255, back to bytes) into the mesh's material colour (alpha 255 written as 254 and
// restored); the mesh is placed at the instance position / rotation / scale (sub_3238D0), its additive bit follows
// +86 and it is queued on the layer +40 (sub_323860). Every class-10 kind's draw is this body.
void sub_340100(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    Vf vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x00340100
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(v1, a0, 60);
    lw(s1, a0, 64);
    lw(s0, v1, 4);
    lw(a2, a0, 52);
    lw(a3, s1, kSpLifetime);
    at = sltu(a3, a2);
    if (at != 0) {
        // 0x00340138
        charge(ctx, 2);
        if (a3 == 0) {
            goto L_00340140;
        }
        // 0x003402a4 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_00340140:
    charge(ctx, 45);
    a0 = s1;
    a1 = addiu(s1, 36);
    jal(ctx, 0x340148u, gen::fn_sub_32A120_0032a120);
    v1 = v0;
    lw(v0, s2, 48);
    sw(v0, sp, 0x48);
    v0 = addiu(sp, 0x48);
    lwc1(f0, gp, -32420);  // 0x7CAE4C
    lw(v0, v0, 0);
    pextlb(v0, zero, v0);
    pextlh(v0, zero, v0);
    qmtc2(v0, vf10, false);  // qmtc2
    vitof0(0xF, vf10, vf10);  // vitof0.xyzw
    mfc1(v0, f0);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vmove(0xF, vf11, vf10);  // vmove.xyzw
    sw(v1, sp, 0x44);
    v0 = addiu(sp, 0x44);
    lw(v0, v0, 0);
    pextlb(v0, zero, v0);
    pextlh(v0, zero, v0);
    qmtc2(v0, vf10, false);  // qmtc2
    vitof0(0xF, vf10, vf10);  // vitof0.xyzw
    mfc1(v0, f0);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
    v0 = 0x437F0000;
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
    qmfc2(v0, vf10, false);  // qmfc2
    ppach(v0, zero, v0);
    ppacb(v0, zero, v0);
    sw(v0, sp, 0x40);
    lw(v0, sp, 0x40);
    sw(v0, sp, 0x4C);
    lbu(v0, sp, 0x4F);
    a3 = 255;
    if (v0 == a3) {
        // 0x00340220
        charge(ctx, 12);
        v0 = 254;
        sb(v0, sp, 0x4F);
        lw(a2, s0, 20);
        lbu(a1, sp, 0x4C);
        lbu(a0, sp, 0x4D);
        lbu(v1, sp, 0x4E);
        lbu(v0, sp, 0x4F);
        sb(a1, a2, 4);
        sb(a0, a2, 5);
        sb(v1, a2, 6);
        sb(v0, a2, 7);
        sb(a3, sp, 0x4F);
    } else {
        // 0x003401f4
        charge(ctx, 11);
        lw(a2, s0, 20);
        lbu(a1, sp, 0x4C);
        lbu(a0, sp, 0x4D);
        lbu(v1, sp, 0x4E);
        lbu(v0, sp, 0x4F);
        sb(a1, a2, 4);
        sb(a0, a2, 5);
        sb(v1, a2, 6);
        sb(v0, a2, 7);
    }
    // 0x00340250
    charge(ctx, 9);
    a0 = s0;
    a1 = s2;
    a2 = addiu(s2, 16);
    a3 = addiu(s2, 32);
    jal(ctx, 0x340260u, gen::fn_sub_3238D0_003238d0);
    lbu(v0, s1, kSpAdditive);
    if (v0 == 0) {
        // 0x00340288
        charge(ctx, 3);
        lhu(v0, s0, 0);
        v0 = v0 & 0xFFFE;
        sh(v0, s0, 0);
    } else {
        // 0x00340274
        charge(ctx, 5);
        lhu(v0, s0, 0);
        v0 = v0 | 0x1;
        sh(v0, s0, 0);
    }
    // 0x00340294
    charge(ctx, 4);
    lhu(a1, s1, kSpLayer);
    a0 = s0;
    jal(ctx, 0x34029Cu, gen::fn_sub_323860_00323860);
    // 0x003402a4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00341F10 sub_341F10 -- 192 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Creates a class-10 instance [kobj10Alloc] ($a0 = the kind, $a1 = the kind parameters; returns it; fx_types'
// sub_341FD0 / sub_342130 call it): one RwMalloc block of 80 bytes + the kind's parameter size (row +24 of 0x69C850):
// frame 0, kind, colour -1, scale (1, 1, 1, 1), position / rotation cleared, the parameters copied to +80 (+64 points
// there). Unlike sub_3393D0 it runs no kind slot: the class's create (fx_types) does.
void sub_341F10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Vf vf0{ctx, 0};
    // 0x00341f10
    enter(ctx, 48);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a1;
    s0 = a0 & 0xFFFF;
    v0 = sll(s0, 3);
    v0 = subu(v0, s0);
    v1 = sll(v0, 2);
    v0 = 0x6A0000;
    v0 = addiu(v0, -14232);  // &0x69C868
    v0 = addu(v0, v1);
    lw(s1, v0, 0);
    a0 = addiu(s1, 80);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x341F5Cu, v0.u());
    s2 = v0;
    v1 = addiu(s2, 80);
    sw(v1, v0, 64);
    sw(zero, v0, 52);
    sw(s0, v0, 56);
    v1 = si(-1);
    sw(v1, v0, 48);
    v0 = 0x6A0000;
    v0 = addiu(v0, -15200);  // &0x69C4A0
    lq(v0, v0, 0);  // 0x69C4A0
    sq(v0, s2, kC12Scale);
    sqc2(vf0, s2, kC12Pos);
    sqc2(vf0, s2, kC12Rot);
    lw(a0, s2, kC12Params);
    a1 = s3;
    a2 = s1;
    jal(ctx, 0x341FA4u, gen::fn_memcpy_00521250);
    v0 = s2;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

}  // namespace p3fes::game
