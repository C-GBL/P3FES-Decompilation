// The effect system, second pass (slice fx2): effect class 13 (its instance constructor and every class slot over the
// kind rows 0x69C5D0) and the ring kinds 1 / 3 of class 12 (kind rows 0x69C650: ring and cone meshes, their per-frame
// vertices and draws), with the class-12 instance constructor. Records: fx2.h (namespace fx2).
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

// 0x00337A60 sub_337A60 -- 272 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Creates a class-13 instance [kobj13Create] ($a0 = the kind (u16), $a1 = the kind parameters; returns it). One
// RwMalloc block of 64 bytes + the kind's parameter size (row +20): frame 0, kind, colour -1, scale 1.0, position and
// rotation cleared (vf0), the parameters copied to +64 (+52 points there); then the kind object comes from the row's
// create (+4, jalr with the parameters) into +48 and the row's init (+0) runs on the instance. Both jalr keep the
// original frame and $ra.
void sub_337A60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Vf vf0{ctx, 0};
    // 0x00337a60
    enter(ctx, 68);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s0 = s4 & 0xFFFF;
    v0 = sll(s0, 1);
    v0 = addu(v0, s0);
    v1 = sll(v0, 3);
    v0 = 0x6A0000;
    v0 = addiu(v0, -14876);  // &0x69C5E4
    v0 = addu(v0, v1);
    lw(s1, v0, 0);
    a0 = addiu(s1, 64);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x337AB4u, v0.u());
    s2 = v0;
    v1 = addiu(s2, 64);
    sw(v1, v0, 52);
    sw(zero, v0, 40);
    sw(s0, v0, 44);
    v1 = si(-1);
    sw(v1, v0, 36);
    v1 = 0x3F800000;
    sw(v1, v0, 32);
    sqc2(vf0, s2, kC13Pos);
    sqc2(vf0, s2, kC13Rot);
    lw(a0, v0, 52);
    a1 = s3;
    a2 = s1;
    jal(ctx, 0x337AF4u, gen::fn_memcpy_00521250);
    v1 = s0;
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    s0 = sll(v0, 3);
    a0 = s3;
    v0 = 0x6A0000;
    v0 = addiu(v0, -14892);  // &0x69C5D4
    v0 = addu(v0, s0);
    lw(v0, v0, 0);
    jalr(ctx, 0x337B20u, v0.u());
    sw(v0, s2, kC13Obj);
    a0 = s2;
    v0 = 0x6A0000;
    v0 = addiu(v0, -14896);  // &0x69C5D0
    v0 = addu(v0, s0);
    lw(v0, v0, 0);
    jalr(ctx, 0x337B40u, v0.u());
    v0 = s2;
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00337B70 sub_337B70 -- 60 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Effect class 13, slot 0 [kobj13New] ($a0 = the instance): sub_337A60 with the effect's kind (+12) and block A
// (sub_3245B0).
void sub_337B70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00337b70
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x337B80u, gen::fn_sub_3245B0_003245b0);
    lhu(a0, s0, kEfKind);
    a1 = v0;
    jal(ctx, 0x337B90u, gen::fn_sub_337A60_00337a60);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00337BB0 sub_337BB0 -- 96 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Effect class 13, slot 4 [kobj13Destroy] ($a0 = the instance): the kind's destroy (row +8, jalr) on the instance,
// then RwFree (0x96017C) of the instance.
void sub_337BB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00337bb0
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, a0, kC13Kind);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v1 = sll(v0, 3);
    v0 = 0x6A0000;
    v0 = addiu(v0, -14888);  // &0x69C5D8
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    jalr(ctx, 0x337BE0u, v0.u());
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x337BF4u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00337C10 sub_337C10 -- 44 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Effect class 13, slot 5 [kobj13Clone] ($a0 = the instance): returns sub_337A60(kind +44, parameters +52).
void sub_337C10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00337c10
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = a0;
    lhu(a0, a0, kC13Kind);
    lw(a1, v0, kC13Params);
    jal(ctx, 0x337C24u, gen::fn_sub_337A60_00337a60);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00337C40 sub_337C40 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Effect class 13, slot 7 [kobj13Restart] ($a0 = the instance): the kind's init (row +0) on the instance, then the
// frame counter (+40) = 0.
void sub_337C40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00337c40
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, a0, 44);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v1 = sll(v0, 3);
    v0 = 0x6A0000;
    v0 = addiu(v0, -14896);  // &0x69C5D0
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    jalr(ctx, 0x337C70u, v0.u());
    sw(zero, s0, kC13Frame);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00337C90 sub_337C90 -- 88 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Effect class 13, slot 2 [kobj13Step] ($a0 = the instance): the kind's update (row +12) on the instance, then
// ++frame (+40).
void sub_337C90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00337c90
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, a0, kC13Kind);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v1 = sll(v0, 3);
    v0 = 0x6A0000;
    v0 = addiu(v0, -14884);  // &0x69C5DC
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    jalr(ctx, 0x337CC0u, v0.u());
    lw(v1, s0, kC13Frame);
    v1 = addiu(v1, 1);
    sw(v1, s0, kC13Frame);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00337CF0 sub_337CF0 -- 76 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Effect class 13, slot 3 [kobj13Draw] ($a0 = the instance): the kind's draw (row +16) when the frame counter (+40)
// is positive.
void sub_337CF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00337cf0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a0, kC13Frame);
    if (i64(v1) > 0) {
        // 0x00337d04: frame > 0: the kind draw
        charge(ctx, 10);
        lw(v1, a0, kC13Kind);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v1 = sll(v0, 3);
        v0 = 0x6A0000;
        v0 = addiu(v0, -14880);  // &0x69C5E0
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        jalr(ctx, 0x337D24u, v0.u());
    }
    // 0x00337d2c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00337D40 sub_337D40 -- 140 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Effect class 13, slot 1 [kobj13Update] ($a0 = the instance): the kind's update, ++frame (+40), and the kind's draw
// when the new frame count is positive.
void sub_337D40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00337d40
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, a0, 44);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v1 = sll(v0, 3);
    v0 = 0x6A0000;
    v0 = addiu(v0, -14884);  // &0x69C5DC
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    jalr(ctx, 0x337D70u, v0.u());
    lw(v1, s0, kC13Frame);
    v1 = addiu(v1, 1);
    sw(v1, s0, kC13Frame);
    if (i64(v1) > 0) {
        // 0x00337d8c: frame > 0: the kind draw
        charge(ctx, 11);
        a0 = s0;
        lw(v1, s0, kC13Kind);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v1 = sll(v0, 3);
        v0 = 0x6A0000;
        v0 = addiu(v0, -14880);  // &0x69C5E0
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        jalr(ctx, 0x337DB0u, v0.u());
    }
    // 0x00337db8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00337DD0 sub_337DD0 -- 16 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Effect class 13, slot 8 [kobj13SetPos] ($a0 = the instance): the position quadword +0 = *$a1 (lq / sq: $v0 keeps
// the copied quadword).
void sub_337DD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00337dd0
    enter(ctx, 4);  // entry check point + this block's cycles
    lq(v0, a1, 0);
    sq(v0, a0, kC13Pos);
}

// 0x00337DE0 sub_337DE0 -- 16 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Effect class 13, slot 9 [kobj13SetRot] ($a0 = the instance): the rotation quadword +16 = *$a1.
void sub_337DE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00337de0
    enter(ctx, 4);  // entry check point + this block's cycles
    lq(v0, a1, 0);
    sq(v0, a0, kC13Rot);
}

// 0x00337DF0 sub_337DF0 -- 12 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Effect class 13, slot 12 [kobj13SetColour] ($a0 = the instance): the RGBA word +36 = $a1.
void sub_337DF0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x00337df0
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(a1, a0, kC13Colour);
}

// 0x00337E00 sub_337E00 -- 12 bytes; leaf frame (no stack)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Effect class 13, slot 10 [kobj13SetScale] ($a0 = the instance): the scale +32 = $f12.
void sub_337E00(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4};
    Fpr f12{ctx, 12};
    // 0x00337e00
    enter(ctx, 3);  // entry check point + this block's cycles
    swc1(f12, a0, kC13Scale);
}

// 0x00337E90 sub_337E90 -- 228 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 12, kind 1, slot 1 [kobj12Ring1Create] ($a0 = the kind parameters; returns the kind object). A 4-byte object
// holding a ring mesh (sub_323240, layout 0x69BCF0, 4 vertices a segment, vertex size 72) of the segment count (+56,
// raised to 3); every segment's four prelight colours are inner, middle, middle, outer (+68 / +72 / +76).
void sub_337E90(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00337e90
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = 4;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x337EB4u, v0.u());
    s0 = v0;
    lw(v0, s1, kRpSegments);
    at = sltiu(v0, 3);
    if (at != 0) {
        // 0x00337ed0: fewer than 3 segments: 3
        charge(ctx, 2);
        v0 = 3;
        sw(v0, s1, kRpSegments);
    }
    // 0x00337ed8
    charge(ctx, 12);
    lhu(a0, s1, kRpSegments);
    a1 = 0x6A0000;
    a1 = addiu(a1, -17168);  // &0x69BCF0
    a2 = 4;
    a3 = 72;
    jal(ctx, 0x337EECu, gen::fn_sub_323240_00323240);
    sw(v0, s0, 0);
    lh(v1, v0, 8);
    a2 = sra(v1, 2);
    if (i64(v1) < 0) {
        // 0x00337f08
        charge(ctx, 2);
        v1 = addiu(v1, 3);
        a2 = sra(v1, 2);
    }
    // 0x00337f10: for each segment: colours A, B, B, C
    charge(ctx, 9);
    lw(v0, v0, 16);
    lw(v0, v0, 24);
    lw(a3, v0, 48);
    lw(a1, s1, kRpColourA);
    lw(a0, s1, kRpColourB);
    lw(v1, s1, kRpColourC);
    t0 = 0;
    for (;;) {
        // 0x00337f4c
        charge(ctx, 3);
        v0 = sltu(t0, a2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00337f34
        charge(ctx, 6);
        sw(a1, a3, 0);
        sw(a0, a3, 4);
        sw(a0, a3, 8);
        sw(v1, a3, 12);
        t0 = addiu(t0, 1);
        a3 = addiu(a3, 16);
    }
    // 0x00337f58
    charge(ctx, 7);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00337FD0 sub_337FD0 -- 900 bytes; frame 0xA0: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 12, kind 1, slot 3 [kobj12Ring1Update] ($a0 = the instance): nothing past the lifetime (+52, 0 = forever).
// The ring radius at frame t: start radius +64 + t * (|speed| + accel * t / 2), with t clamped at the turning point
// when the acceleration is negative; t counts down from the lifetime when the reverse flag is set (speed +96,
// acceleration +100, reverse +104). The ring geometry is locked (vertices) and for each segment angle (cosf / sinf of
// the step 2 pi (0x7CAE90) / segments) the four vertices are written at the radii r, r + width0, + width1, + width2
// (+80 / +84 / +88) in the y = 0 plane (VU0 scaling of the unit direction); unlock, re-instance when flagged.
void sub_337FD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    Vf vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x00337fd0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(v1, a0, 60);
    lw(s2, a0, 64);
    lw(s1, v1, 0);
    lw(a0, a0, 52);
    lw(v1, s2, kRpLifetime);
    at = slt(v1, a0);
    if (at != 0) {
        // 0x00338014
        charge(ctx, 2);
        if (v1 == 0) {
            goto L_0033801c;
        }
        // 0x00338328 (the shared epilogue, written out on this path)
        charge(ctx, 11);
        ld(ra, sp, 0x50);
        lq(s3, sp, 0x40);
        lq(s2, sp, 0x30);
        lq(s1, sp, 0x20);
        lq(s0, sp, 0x10);
        lwc1(f22, sp, 0x8);
        lwc1(f21, sp, 0x4);
        lwc1(f20, sp, 0x0);
        sp = addiu(sp, 0xA0);
        return;
    }
L_0033801c:  // within the lifetime: t (reversed with +104)
    charge(ctx, 3);
    lbu(v0, s2, 104);
    if (v0 == 0) {
        // 0x00338040
        charge(ctx, 3);
        mtc1(a0, f0);
        cvt_s_w(f5, f0);
    } else {
        // 0x00338028
        charge(ctx, 6);
        v0 = subu(v1, a0);
        mtc1(v0, f0);
        cvt_s_w(f5, f0);
    }
    // 0x0033804c
    charge(ctx, 8);
    lwc1(f0, s2, 96);
    abs_s(f3, f0);
    lwc1(f4, s2, 100);
    mtc1(zero, f0);
    c_lt_s(f4, f0);
    if (cond(ctx)) {
        // 0x0033806c: negative acceleration: clamp t at the turning point
        charge(ctx, 11);
        v0 = 0x3F000000;
        mtc1(v0, f2);
        neg_s(f1, f3);
        mul_s(f0, f2, f4);
        div_s(f0, f1, f0);
        mul_s(f0, f2, f0);
        c_le_s(f5, f0);
        if (!cond(ctx)) {
            // 0x00338098
            charge(ctx, 1);
            mov_s(f5, f0);
        }
    }
    // 0x0033809c
    charge(ctx, 14);
    mul_s(f2, f4, f5);
    v0 = 0x3F000000;
    mtc1(v0, f1);
    mtc1(zero, f0);
    adda_s(f0, f3);
    madd_s(f0, f1, f2);
    mul_s(f1, f5, f0);
    lwc1(f0, s2, kRpRadius);
    add_s(f22, f1, f0);
    lh(v0, s1, 8);
    s0 = sra(v0, 2);
    if (i64(v0) < 0) {
        // 0x003380d4
        charge(ctx, 2);
        v0 = addiu(v0, 3);
        s0 = sra(v0, 2);
    }
    // 0x003380dc: lock the ring geometry, the four radii
    charge(ctx, 13);
    lw(v0, s1, 16);
    lw(a0, v0, 24);
    a1 = 2;
    jal(ctx, 0x3380E8u, gen::fn_geometryLock_00493370);
    lw(v0, s1, 16);
    lw(v0, v0, 24);
    lw(v0, v0, 92);
    lw(s3, v0, 20);
    mtc1(zero, f21);
    lw(v0, s2, kRpSegments);
    if (i64(v0) < 0) {
        // 0x00338124
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f1, f0);
        add_s(f1, f1, f1);
    } else {
        // 0x00338110
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
    }
    // 0x00338140: for each segment
    charge(ctx, 38);
    lwc1(f0, gp, -32352);  // 0x7CAE90
    div_s(f20, f0, f1);
    sw(zero, sp, 0x94);
    v0 = 0x3F800000;
    sw(v0, sp, 0x9C);
    lwc1(f0, s2, kRpWidth0);
    add_s(f2, f0, f22);
    lwc1(f0, s2, kRpWidth1);
    add_s(f1, f2, f0);
    lwc1(f0, s2, kRpWidth2);
    add_s(f0, f1, f0);
    v0 = 0x6A0000;
    v0 = addiu(v0, -15200);  // &0x69C4A0
    lqc2(vf10, v0, 0);  // 0x69C4A0
    vmove(0xF, vf11, vf10);  // vmove.xyzw
    mfc1(v0, f2);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    v0 = addiu(sp, 0x80);
    sqc2(vf10, v0, 0);
    vmove(0xF, vf10, vf11);  // vmove.xyzw
    mfc1(v0, f1);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    mfc1(v0, f0);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
    v0 = addiu(sp, 0x70);
    sqc2(vf10, v0, 0);
    v0 = addiu(sp, 0x60);
    sqc2(vf11, v0, 0);
    s2 = 0;
    for (;;) {
        // 0x003382ec
        charge(ctx, 3);
        v0 = sltu(s2, s0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003381d8
        charge(ctx, 69);
        mov_s(f12, f21);
        jal(ctx, 0x3381DCu, gen::fn_cosf_0052e6d8);
        swc1(f0, sp, 0x90);
        mov_s(f12, f21);
        jal(ctx, 0x3381ECu, gen::fn_sinf_0052e878);
        swc1(f0, sp, 0x98);
        v0 = addiu(sp, 0x90);
        lqc2(vf10, v0, 0);
        vmove(0xF, vf11, vf10);  // vmove.xyzw
        mfc1(v0, f22);
        qmtc2(v0, vf2, false);  // qmtc2
        vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
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
        v0 = addiu(sp, 0x80);
        lqc2(vf10, v0, 0);
        vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
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
        v0 = addiu(sp, 0x70);
        lqc2(vf10, v0, 0);
        vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
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
        v0 = addiu(sp, 0x60);
        lqc2(vf10, v0, 0);
        vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
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
        add_s(f21, f21, f20);
        s2 = addiu(s2, 1);
        s3 = addiu(s3, 48);
    }
    // 0x003382f8: unlock
    charge(ctx, 9);
    lw(v0, s1, 16);
    lw(s0, v0, 24);
    a0 = s0;
    jal(ctx, 0x338304u, gen::fn_sub_4933D0_004933d0);
    lhu(v1, s1, 0);
    v1 = v1 & 0x4;
    if (v1 != 0) {
        // 0x0033831c
        charge(ctx, 3);
        lhu(v1, s0, 12);
        v1 = v1 | 0x1;
        sh(v1, s0, 12);
    }
    // 0x00338328 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x00338360 sub_338360 -- 464 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 12, kind 1, slot 4 [kobj12Ring1Draw] ($a0 = the instance; also kind 3's draw sub_339200, byte for byte):
// within the lifetime, colour = instance colour (+48) x the colour track at the frame (sub_32A120 on +36) on VU0
// (bytes -> floats / 255, multiply, x 255, back to bytes); it becomes the ring's material colour (alpha 255 written
// as 254 and restored); when its alpha is not 0 the mesh is placed at the instance position / rotation / scale
// (sub_3238D0), its additive bit follows +60 and it is queued on the layer +40 (sub_323860).
void sub_338360(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    Vf vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x00338360
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(v1, a0, 60);
    lw(s1, a0, 64);
    lw(s0, v1, 0);
    lw(a2, a0, 52);
    lw(a3, s1, kRpLifetime);
    at = sltu(a3, a2);
    if (at != 0) {
        // 0x00338398: within the lifetime: colour x colour track (VU0)
        charge(ctx, 2);
        if (a3 == 0) {
            goto L_003383a0;
        }
        // 0x00338514 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_003383a0:
    charge(ctx, 45);
    a0 = s1;
    a1 = addiu(s1, 36);
    jal(ctx, 0x3383A8u, gen::fn_sub_32A120_0032a120);
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
    mfc1(v1, f0);
    qmtc2(v1, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
    v1 = 0x437F0000;
    qmtc2(v1, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
    qmfc2(v1, vf10, false);  // qmfc2
    ppach(v1, zero, v1);
    ppacb(v1, zero, v1);
    sw(v1, sp, 0x40);
    lw(v1, sp, 0x40);
    sw(v1, sp, 0x4C);
    lbu(v1, sp, 0x4F);
    t0 = 255;
    if (v1 == t0) {
        // 0x00338480
        charge(ctx, 12);
        v1 = 254;
        sb(v1, sp, 0x4F);
        lw(a3, s0, 20);
        lbu(a2, sp, 0x4C);
        lbu(a1, sp, 0x4D);
        lbu(a0, sp, 0x4E);
        lbu(v1, sp, 0x4F);
        sb(a2, a3, 4);
        sb(a1, a3, 5);
        sb(a0, a3, 6);
        sb(v1, a3, 7);
        sb(t0, sp, 0x4F);
    } else {
        // 0x00338454
        charge(ctx, 11);
        lw(a3, s0, 20);
        lbu(a2, sp, 0x4C);
        lbu(a1, sp, 0x4D);
        lbu(a0, sp, 0x4E);
        lbu(v1, sp, 0x4F);
        sb(a2, a3, 4);
        sb(a1, a3, 5);
        sb(a0, a3, 6);
        sb(v1, a3, 7);
    }
    // 0x003384b0
    charge(ctx, 4);
    lw(v1, s0, 20);
    lbu(v1, v1, 7);
    if (v1 != 0) {
        // 0x003384c0: alpha != 0: place the mesh
        charge(ctx, 9);
        a0 = s0;
        a1 = s2;
        a2 = addiu(s2, 16);
        a3 = addiu(s2, 32);
        jal(ctx, 0x3384D0u, gen::fn_sub_3238D0_003238d0);
        lbu(v0, s1, kRpAdditive);
        if (v0 == 0) {
            // 0x003384f8
            charge(ctx, 3);
            lhu(v0, s0, 0);
            v0 = v0 & 0xFFFE;
            sh(v0, s0, 0);
        } else {
            // 0x003384e4
            charge(ctx, 5);
            lhu(v0, s0, 0);
            v0 = v0 | 0x1;
            sh(v0, s0, 0);
        }
        // 0x00338504: queue on the draw layer
        charge(ctx, 4);
        lhu(a1, s1, kRpLayer);
        a0 = s0;
        jal(ctx, 0x33850Cu, gen::fn_sub_323860_00323860);
    }
    // 0x00338514 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00338EA0 sub_338EA0 -- 864 bytes; frame 0xA0: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 12, kind 3, slot 3 [kobj12Ring3Update]: as sub_337FD0 (speed +92, acceleration +96, reverse +100) but every
// segment's first vertex stays at the centre (0, 0, 0) and the three others are at the widths +80 / +84 / +88 from
// it, so the mesh is a fan / cone.
void sub_338EA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    Vf vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x00338ea0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(v1, a0, 60);
    lw(s2, a0, 64);
    lw(s1, v1, 0);
    lw(a0, a0, 52);
    lw(v1, s2, kRpLifetime);
    at = slt(v1, a0);
    if (at != 0) {
        // 0x00338ee8
        charge(ctx, 2);
        if (v1 == 0) {
            goto L_00338ef0;
        }
        // 0x003391d0 (the shared epilogue, written out on this path)
        charge(ctx, 12);
        ld(ra, sp, 0x50);
        lq(s3, sp, 0x40);
        lq(s2, sp, 0x30);
        lq(s1, sp, 0x20);
        lq(s0, sp, 0x10);
        lwc1(f23, sp, 0xC);
        lwc1(f22, sp, 0x8);
        lwc1(f21, sp, 0x4);
        lwc1(f20, sp, 0x0);
        sp = addiu(sp, 0xA0);
        return;
    }
L_00338ef0:
    charge(ctx, 3);
    lbu(v0, s2, 100);
    if (v0 == 0) {
        // 0x00338f14
        charge(ctx, 3);
        mtc1(a0, f0);
        cvt_s_w(f5, f0);
    } else {
        // 0x00338efc
        charge(ctx, 6);
        v0 = subu(v1, a0);
        mtc1(v0, f0);
        cvt_s_w(f5, f0);
    }
    // 0x00338f20
    charge(ctx, 8);
    lwc1(f0, s2, 92);
    abs_s(f3, f0);
    lwc1(f4, s2, 96);
    mtc1(zero, f0);
    c_lt_s(f4, f0);
    if (cond(ctx)) {
        // 0x00338f40
        charge(ctx, 11);
        v0 = 0x3F000000;
        mtc1(v0, f2);
        neg_s(f1, f3);
        mul_s(f0, f2, f4);
        div_s(f0, f1, f0);
        mul_s(f0, f2, f0);
        c_le_s(f5, f0);
        if (!cond(ctx)) {
            // 0x00338f6c
            charge(ctx, 1);
            mov_s(f5, f0);
        }
    }
    // 0x00338f70
    charge(ctx, 14);
    mul_s(f2, f4, f5);
    v0 = 0x3F000000;
    mtc1(v0, f1);
    mtc1(zero, f0);
    adda_s(f0, f3);
    madd_s(f0, f1, f2);
    mul_s(f1, f5, f0);
    lwc1(f0, s2, kRpRadius);
    add_s(f23, f1, f0);
    lh(v0, s1, 8);
    s0 = sra(v0, 2);
    if (i64(v0) < 0) {
        // 0x00338fa8
        charge(ctx, 2);
        v0 = addiu(v0, 3);
        s0 = sra(v0, 2);
    }
    // 0x00338fb0: lock the geometry, the radii
    charge(ctx, 13);
    lw(v0, s1, 16);
    lw(a0, v0, 24);
    a1 = 2;
    jal(ctx, 0x338FBCu, gen::fn_geometryLock_00493370);
    lw(v0, s1, 16);
    lw(v0, v0, 24);
    lw(v0, v0, 92);
    lw(s3, v0, 20);
    mtc1(zero, f22);
    lw(v0, s2, kRpSegments);
    if (i64(v0) < 0) {
        // 0x00338ff8
        charge(ctx, 7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f1, f0);
        add_s(f1, f1, f1);
    } else {
        // 0x00338fe4
        charge(ctx, 5);
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
    }
    // 0x00339014: for each segment
    charge(ctx, 39);
    lwc1(f0, gp, -32352);  // 0x7CAE90
    div_s(f21, f0, f1);
    mtc1(zero, f20);
    sw(zero, sp, 0x94);
    v0 = 0x3F800000;
    sw(v0, sp, 0x9C);
    lwc1(f0, s2, kRpWidth0);
    add_s(f2, f0, f23);
    lwc1(f0, s2, kRpWidth1);
    add_s(f1, f2, f0);
    lwc1(f0, s2, kRpWidth2);
    add_s(f0, f1, f0);
    v0 = 0x6A0000;
    v0 = addiu(v0, -15200);  // &0x69C4A0
    lqc2(vf10, v0, 0);  // 0x69C4A0
    vmove(0xF, vf11, vf10);  // vmove.xyzw
    mfc1(v0, f2);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    v0 = addiu(sp, 0x80);
    sqc2(vf10, v0, 0);
    vmove(0xF, vf10, vf11);  // vmove.xyzw
    mfc1(v0, f1);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    mfc1(v0, f0);
    qmtc2(v0, vf2, false);  // qmtc2
    vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
    v0 = addiu(sp, 0x70);
    sqc2(vf10, v0, 0);
    v0 = addiu(sp, 0x60);
    sqc2(vf11, v0, 0);
    s2 = 0;
    for (;;) {
        // 0x00339194
        charge(ctx, 3);
        v0 = sltu(s2, s0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003390b0
        charge(ctx, 57);
        mov_s(f12, f22);
        jal(ctx, 0x3390B4u, gen::fn_cosf_0052e6d8);
        swc1(f0, sp, 0x90);
        mov_s(f12, f22);
        jal(ctx, 0x3390C4u, gen::fn_sinf_0052e878);
        swc1(f0, sp, 0x98);
        swc1(f20, s3, 0);
        swc1(f20, s3, 4);
        swc1(f20, s3, 8);
        v0 = addiu(sp, 0x90);
        lqc2(vf11, v0, 0);
        v0 = addiu(sp, 0x80);
        lqc2(vf10, v0, 0);
        vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
        v1 = 0x6A0000;
        v1 = addiu(v1, -15152);  // &0x69C4D0
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
        v0 = addiu(sp, 0x70);
        lqc2(vf10, v0, 0);
        vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
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
        v0 = addiu(sp, 0x60);
        lqc2(vf10, v0, 0);
        vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
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
        add_s(f22, f22, f21);
        s2 = addiu(s2, 1);
        s3 = addiu(s3, 48);
    }
    // 0x003391a0: unlock
    charge(ctx, 9);
    lw(v0, s1, 16);
    lw(s0, v0, 24);
    a0 = s0;
    jal(ctx, 0x3391ACu, gen::fn_sub_4933D0_004933d0);
    lhu(v1, s1, 0);
    v1 = v1 & 0x4;
    if (v1 != 0) {
        // 0x003391c4
        charge(ctx, 3);
        lhu(v1, s0, 12);
        v1 = v1 | 0x1;
        sh(v1, s0, 12);
    }
    // 0x003391d0 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x00339200 sub_339200 -- 464 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Class 12, kind 3, slot 4 [kobj12Ring3Draw]: the same body as sub_338360 [kobj12Ring1Draw].
void sub_339200(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    Vf vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x00339200
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(v1, a0, 60);
    lw(s1, a0, 64);
    lw(s0, v1, 0);
    lw(a2, a0, 52);
    lw(a3, s1, kRpLifetime);
    at = sltu(a3, a2);
    if (at != 0) {
        // 0x00339238: within the lifetime: colour x colour track (VU0)
        charge(ctx, 2);
        if (a3 == 0) {
            goto L_00339240;
        }
        // 0x003393b4 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_00339240:
    charge(ctx, 45);
    a0 = s1;
    a1 = addiu(s1, 36);
    jal(ctx, 0x339248u, gen::fn_sub_32A120_0032a120);
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
    mfc1(v1, f0);
    qmtc2(v1, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
    v1 = 0x437F0000;
    qmtc2(v1, vf2, false);  // qmtc2
    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
    vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
    qmfc2(v1, vf10, false);  // qmfc2
    ppach(v1, zero, v1);
    ppacb(v1, zero, v1);
    sw(v1, sp, 0x40);
    lw(v1, sp, 0x40);
    sw(v1, sp, 0x4C);
    lbu(v1, sp, 0x4F);
    t0 = 255;
    if (v1 == t0) {
        // 0x00339320
        charge(ctx, 12);
        v1 = 254;
        sb(v1, sp, 0x4F);
        lw(a3, s0, 20);
        lbu(a2, sp, 0x4C);
        lbu(a1, sp, 0x4D);
        lbu(a0, sp, 0x4E);
        lbu(v1, sp, 0x4F);
        sb(a2, a3, 4);
        sb(a1, a3, 5);
        sb(a0, a3, 6);
        sb(v1, a3, 7);
        sb(t0, sp, 0x4F);
    } else {
        // 0x003392f4
        charge(ctx, 11);
        lw(a3, s0, 20);
        lbu(a2, sp, 0x4C);
        lbu(a1, sp, 0x4D);
        lbu(a0, sp, 0x4E);
        lbu(v1, sp, 0x4F);
        sb(a2, a3, 4);
        sb(a1, a3, 5);
        sb(a0, a3, 6);
        sb(v1, a3, 7);
    }
    // 0x00339350
    charge(ctx, 4);
    lw(v1, s0, 20);
    lbu(v1, v1, 7);
    if (v1 != 0) {
        // 0x00339360: alpha != 0: place the mesh
        charge(ctx, 9);
        a0 = s0;
        a1 = s2;
        a2 = addiu(s2, 16);
        a3 = addiu(s2, 32);
        jal(ctx, 0x339370u, gen::fn_sub_3238D0_003238d0);
        lbu(v0, s1, kRpAdditive);
        if (v0 == 0) {
            // 0x00339398
            charge(ctx, 3);
            lhu(v0, s0, 0);
            v0 = v0 & 0xFFFE;
            sh(v0, s0, 0);
        } else {
            // 0x00339384
            charge(ctx, 5);
            lhu(v0, s0, 0);
            v0 = v0 | 0x1;
            sh(v0, s0, 0);
        }
        // 0x003393a4: queue on the draw layer
        charge(ctx, 4);
        lhu(a1, s1, kRpLayer);
        a0 = s0;
        jal(ctx, 0x3393ACu, gen::fn_sub_323860_00323860);
    }
    // 0x003393b4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003393D0 sub_3393D0 -- 280 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Creates a class-12 instance [kobj12Create] ($a0 = the kind, $a1 = the kind parameters; returns it; fx_types'
// sub_3394F0 / sub_3395A0 call it). One RwMalloc block of 80 bytes + the kind's parameter size (row +20): frame 0,
// kind, colour -1, scale (1, 1, 1, 1), position / rotation cleared, parameters copied to +80; the kind object from
// the row's create (+4) into +60, then the row's init (+0) on the instance.
void sub_3393D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Vf vf0{ctx, 0};
    // 0x003393d0
    enter(ctx, 70);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s0 = s4 & 0xFFFF;
    v0 = sll(s0, 1);
    v0 = addu(v0, s0);
    v1 = sll(v0, 3);
    v0 = 0x6A0000;
    v0 = addiu(v0, -14748);  // &0x69C664
    v0 = addu(v0, v1);
    lw(s1, v0, 0);
    a0 = addiu(s1, 80);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x339424u, v0.u());
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
    jal(ctx, 0x33946Cu, gen::fn_memcpy_00521250);
    v1 = s0;
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    s0 = sll(v0, 3);
    a0 = s3;
    v0 = 0x6A0000;
    v0 = addiu(v0, -14764);  // &0x69C654
    v0 = addu(v0, s0);
    lw(v0, v0, 0);
    jalr(ctx, 0x339498u, v0.u());
    sw(v0, s2, kC12Obj);
    a0 = s2;
    v0 = 0x6A0000;
    v0 = addiu(v0, -14768);  // &0x69C650
    v0 = addu(v0, s0);
    lw(v0, v0, 0);
    jalr(ctx, 0x3394B8u, v0.u());
    v0 = s2;
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

}  // namespace p3fes::game
