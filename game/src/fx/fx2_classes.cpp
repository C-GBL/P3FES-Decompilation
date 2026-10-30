// The effect system, second pass (slice fx2): the sprite effect class 7, the lens flare class 9, the shake object
// class 21, the screen filters (classes 4 / 5: instance slots, the kinds of the tables 0x69CB90 / 0x69CC50, the Im2D
// quad and cell helpers), the effect-model helpers and the constructors / destructors / clones of fx_epl's four EPL
// kinds (rows 0x69C368..0x69C404). Records: fx2.h (namespace fx2).
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

// 0x003461A0 sub_3461A0 -- 432 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Effect class 7, slot 0 [fxSpriteCreate] ($a0 = the effect record, or 0 for a bare instance (the clone); returns the
// instance). A cleared 212-byte block: position / rotation 0, scale 1.0, colour -1. With a record: a one-quad mesh
// (sub_3233A0(1, 2, 4, layout 0x69BDC8, 76)) whose four vertex colours are white, the effect kind, the 152-byte block
// A copy (+48) and, by block B's type: 7 an image sequence (sub_322DC0 -> +204), 4 a manager texture by index
// (sub_3210A0 -> RwFrame op sub_494D50 on the mesh frame), 2 a sprite player (sub_322530 -> +208), 1 a frame list
// texture (sub_323B90).
void sub_3461A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Vf vf0{ctx, 0};
    // 0x003461a0
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = 212;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x3461C4u, v0.u());
    s0 = v0;
    a0 = s0;
    a1 = 0;
    a2 = 212;
    jal(ctx, 0x3461DCu, gen::fn_memset_00521408);
    sqc2(vf0, s0, kC7Pos);
    sqc2(vf0, s0, kC7Rot);
    v0 = si(-1);
    sw(v0, s0, kC7Colour);
    v0 = 0x3F800000;
    sw(v0, s0, kC7Scale);
    if (s1 != 0) {
        // 0x00346210: a record: the quad mesh, white vertices, block A
        charge(ctx, 32);
        a0 = 1;
        a1 = 2;
        a2 = 4;
        a3 = 0x6A0000;
        a3 = addiu(a3, -16952);  // &0x69BDC8
        t0 = 76;
        jal(ctx, 0x346228u, gen::fn_sub_3233A0_003233a0);
        sw(v0, s0, kC7Mesh);
        lw(v0, v0, 16);
        lw(v0, v0, 24);
        lw(v1, v0, 48);
        v0 = si(-1);
        sw(v0, v1, 0);
        sw(v0, v1, 4);
        sw(v0, v1, 8);
        sw(v0, v1, 12);
        lhu(v0, s1, kEfKind);
        sw(v0, s0, kC7Kind);
        a0 = s1;
        jal(ctx, 0x346260u, gen::fn_sub_3245B0_003245b0);
        a0 = addiu(s0, 48);
        a1 = v0;
        a2 = 152;
        jal(ctx, 0x346274u, gen::fn_memcpy_00521250);
        a0 = s1;
        jal(ctx, 0x346280u, gen::fn_sub_3245F0_003245f0);
        if (v0 != 0) {
            // 0x00346290: block B: by its type
            charge(ctx, 4);
            lhu(a0, s1, kEfBlockBType);
            v1 = 7;
            if (a0 == v1) {
                // 0x00346324: type 7: image sequence
                charge(ctx, 4);
                a0 = v0;
                jal(ctx, 0x346328u, gen::fn_sub_322DC0_00322dc0);
                sw(v0, s0, kC7ImageSeq);
            } else {
                // 0x003462a0
                charge(ctx, 3);
                v1 = 4;
                if (a0 == v1) {
                    // 0x003462fc: type 4: manager texture
                    charge(ctx, 10);
                    lhu(a0, v0, 0);
                    jal(ctx, 0x346300u, gen::fn_sub_3210A0_003210a0);
                    lw(v1, s0, kC7Mesh);
                    lw(a0, v1, 20);
                    a1 = v0;
                    jal(ctx, 0x346314u, gen::fn_sub_494D50_00494d50);
                } else {
                    // 0x003462ac
                    charge(ctx, 3);
                    v1 = 2;
                    if (a0 == v1) {
                        // 0x003462e4: type 2: sprite player
                        charge(ctx, 6);
                        a0 = v0;
                        jal(ctx, 0x3462E8u, gen::fn_sub_322530_00322530);
                        sw(v0, s0, kC7Player);
                    } else {
                        // 0x003462b8
                        charge(ctx, 3);
                        v1 = 1;
                        if (a0 == v1) {
                            // 0x003462cc: type 1: frame list texture
                            charge(ctx, 6);
                            lw(a0, s0, kC7Mesh);
                            a1 = v0;
                            jal(ctx, 0x3462D4u, gen::fn_sub_323B90_00323b90);
                        } else {
                            // 0x003462c4
                            charge(ctx, 2);
                        }
                    }
                }
            }
        }
        // 0x00346334
        charge(ctx, 1);
        v0 = s0;
    } else {
        // 0x00346204
        charge(ctx, 3);
        v0 = s0;
    }
    // 0x00346338 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00346350 sub_346350 -- 108 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Effect class 7, slot 4 [fxSpriteDestroy] ($a0 = the instance): releases the image sequence (+204, sub_322F20) and
// the sprite player (+208, sub_322660) when present, destroys the quad mesh (sub_3237C0) and frees the instance.
void sub_346350(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00346350
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, 204);
    if (a0 != 0) {
        // 0x0034636c
        charge(ctx, 2);
        jal(ctx, 0x34636Cu, gen::fn_sub_322F20_00322f20);
    }
    // 0x00346374
    charge(ctx, 3);
    lw(a0, s0, kC7Player);
    if (a0 != 0) {
        // 0x00346380
        charge(ctx, 2);
        jal(ctx, 0x346380u, gen::fn_sub_322660_00322660);
    }
    // 0x00346388
    charge(ctx, 13);
    lw(a0, s0, kC7Mesh);
    jal(ctx, 0x34638Cu, gen::fn_sub_3237C0_003237c0);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x3463A0u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003463C0 sub_3463C0 -- 148 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Effect class 7, slot 5 [fxSpriteClone] ($a0 = the source; returns the copy): a bare instance (sub_3461A0(0)), the
// mesh duplicated (sub_323640) with white vertex colours, the 152-byte definition copied and the animation shared by
// sub_346460.
void sub_3463C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003463c0
    enter(ctx, 37);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = 0;
    jal(ctx, 0x3463D8u, gen::fn_sub_3461A0_003461a0);
    s0 = v0;
    lw(a0, s1, kC7Mesh);
    jal(ctx, 0x3463E8u, gen::fn_sub_323640_00323640);
    sw(v0, s0, kC7Mesh);
    lw(v0, v0, 16);
    lw(v0, v0, 24);
    lw(v1, v0, 48);
    v0 = si(-1);
    sw(v0, v1, 0);
    sw(v0, v1, 4);
    sw(v0, v1, 8);
    sw(v0, v1, 12);
    a0 = addiu(s0, 48);
    a1 = addiu(s1, 48);
    a2 = 152;
    jal(ctx, 0x346420u, gen::fn_memcpy_00521250);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x346430u, gen::fn_sub_346460_00346460);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00346460 sub_346460 -- 152 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Effect class 7, slot 6 [fxSpriteCopyAnim] ($a0 = the destination, $a1 = the source): a source sprite player (+208)
// replaces the destination's (released by sub_322660) with a copy (sub_3225D0); else a source image sequence (+204)
// replaces the destination's (sub_322F20) with a copy (sub_322FB0).
void sub_346460(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00346460
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v1, a1, 208);
    if (v1 == 0) {
        // 0x003464b0
        charge(ctx, 3);
        lw(v1, s0, kC7ImageSeq);
        if (v1 != 0) {
            // 0x003464bc
            charge(ctx, 3);
            lw(a0, s1, kC7ImageSeq);
            if (a0 != 0) {
                // 0x003464c8
                charge(ctx, 2);
                jal(ctx, 0x3464C8u, gen::fn_sub_322F20_00322f20);
            }
            // 0x003464d0
            charge(ctx, 4);
            lw(a0, s0, kC7ImageSeq);
            jal(ctx, 0x3464D4u, gen::fn_sub_322FB0_00322fb0);
            sw(v0, s1, kC7ImageSeq);
        }
    } else {
        // 0x00346484
        charge(ctx, 3);
        lw(a0, s1, kC7Player);
        if (a0 != 0) {
            // 0x00346490
            charge(ctx, 2);
            jal(ctx, 0x346490u, gen::fn_sub_322660_00322660);
        }
        // 0x00346498
        charge(ctx, 6);
        lw(a0, s0, kC7Player);
        jal(ctx, 0x34649Cu, gen::fn_sub_3225D0_003225d0);
        sw(v0, s1, kC7Player);
    }
    // 0x003464e0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00346530 sub_346530 -- 3024 bytes; frame 0x120: ra sp+0x60, s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Effect class 7, slot 3 [fxSpriteDraw] ($a0 = the instance; slot 1 sub_347100 counts the frame first). Past the
// duration (+188) the sprite stops, or restarts at frame 0 with the loop flag (+116). Each frame: the mesh takes the
// instance position / rotation (sub_323880); colour = instance colour x the colour track (sub_32A120) on VU0 (alpha
// 255 -> 254 trick); size = the size curve (sub_32A540 on +100) x base size (+192), angle = the rotation curve
// (+144); the animation frame comes from the sprite player (sub_322D40 step, sub_322D10 its cell: texture coordinates
// in 1/16 units) or the image sequence (sub_322FD0, its raster -> sub_494D50 / sub_323BF0); the four quad vertices
// are rebuilt rotated by the angle (cosf / sinf) in the locked geometry; the mesh is queued on the layer
// (sub_323860).
void sub_346530(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25};
    Vf vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x00346530
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x120);
    sd(ra, sp, 0x60);
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s3 = a0;
    lw(s0, a0, 188);
    lw(s2, a0, 44);
    lw(s1, a0, 200);
    if (s2 != 0) {
        // 0x00346578: frame > 0: past the duration?
        charge(ctx, 3);
        v1 = slt(s2, s0);
        if (v1 == 0) {
            // 0x00346584
            charge(ctx, 2);
            if (i64(s0) <= 0) {
                goto L_003465b0;
            }
            // 0x0034658c: past it: the loop flag restarts at frame 0, else stop
            charge(ctx, 3);
            lbu(v1, s3, kC7Loop);
            if (v1 != 0) {
                // 0x00346598
                charge(ctx, 4);
                sw(zero, s3, kC7Frame);
                s2 = 0;
                goto L_003465b0;
            }
            // 0x003465a8
            charge(ctx, 2);
            // 0x003470c8 (the shared epilogue, written out on this path)
            charge(ctx, 14);
            ld(ra, sp, 0x60);
            lq(s3, sp, 0x50);
            lq(s2, sp, 0x40);
            lq(s1, sp, 0x30);
            lq(s0, sp, 0x20);
            lwc1(f25, sp, 0x14);
            lwc1(f24, sp, 0x10);
            lwc1(f23, sp, 0xC);
            lwc1(f22, sp, 0x8);
            lwc1(f21, sp, 0x4);
            lwc1(f20, sp, 0x0);
            sp = addiu(sp, 0x120);
            return;
        }
    L_003465b0:  // place the mesh; colour = instance colour x the colour track (VU0)
        charge(ctx, 53);
        a0 = s1;
        a1 = s3;
        a2 = addiu(s3, 16);
        lwc1(f12, s3, kC7Scale);
        jal(ctx, 0x3465C0u, gen::fn_sub_323880_00323880);
        a0 = addiu(s3, 48);
        a1 = addiu(s3, 84);
        a2 = s2;
        a3 = s0;
        jal(ctx, 0x3465D8u, gen::fn_sub_32A120_0032a120);
        v1 = v0;
        lw(v0, s3, kC7Colour);
        sw(v0, sp, 0x118);
        v0 = addiu(sp, 0x118);
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
        sw(v1, sp, 0x114);
        v0 = addiu(sp, 0x114);
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
        sw(v0, sp, 0x110);
        lw(v0, sp, 0x110);
        sw(v0, sp, 0x11C);
        lbu(v0, sp, 0x11F);
        a3 = 255;
        if (v0 == a3) {
            // 0x003466b0
            charge(ctx, 12);
            v0 = 254;
            sb(v0, sp, 0x11F);
            lw(a2, s1, 20);
            lbu(a1, sp, 0x11C);
            lbu(a0, sp, 0x11D);
            lbu(v1, sp, 0x11E);
            lbu(v0, sp, 0x11F);
            sb(a1, a2, 4);
            sb(a0, a2, 5);
            sb(v1, a2, 6);
            sb(v0, a2, 7);
            sb(a3, sp, 0x11F);
        } else {
            // 0x00346684
            charge(ctx, 11);
            lw(a2, s1, 20);
            lbu(a1, sp, 0x11C);
            lbu(a0, sp, 0x11D);
            lbu(v1, sp, 0x11E);
            lbu(v0, sp, 0x11F);
            sb(a1, a2, 4);
            sb(a0, a2, 5);
            sb(v1, a2, 6);
            sb(v0, a2, 7);
        }
        // 0x003466e0: size = size curve x base size, angle = rotation curve
        charge(ctx, 16);
        a0 = addiu(s3, 100);
        a1 = s2;
        a2 = s0;
        jal(ctx, 0x3466ECu, gen::fn_sub_32A540_0032a540);
        lwc1(f1, s3, kC7Size);
        mul_s(f20, f0, f1);
        a0 = addiu(s3, 144);
        a1 = s2;
        a2 = s0;
        jal(ctx, 0x346708u, gen::fn_sub_32A540_0032a540);
        mov_s(f21, f0);
        lw(a0, s3, kC7Player);
        if (a0 == 0) {
            // 0x00346aa8: an image sequence: its raster for this frame (sub_322FD0)
            charge(ctx, 3);
            lw(a0, s3, kC7ImageSeq);
            if (a0 == 0) {
                // 0x00346c08
                charge(ctx, 38);
                a0 = s1;
                a1 = addiu(sp, 0x100);
                jal(ctx, 0x346C10u, gen::fn_sub_323BF0_00323bf0);
                lw(a1, sp, 0x100);
                v0 = sll(a1, 4);
                lw(a0, sp, 0x104);
                v1 = sll(a0, 4);
                sh(zero, sp, 0x88);
                sh(zero, sp, 0x8A);
                sh(v0, sp, 0x8C);
                sh(zero, sp, 0x8E);
                sh(v0, sp, 0x90);
                sh(v1, sp, 0x92);
                sh(zero, sp, 0x94);
                sh(v1, sp, 0x96);
                sw(zero, sp, 0x70);
                sw(zero, sp, 0x74);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                v0 = 0x42000000;
                mtc1(v0, f2);
                div_s(f0, f0, f2);
                v0 = 0x41800000;
                mtc1(v0, f1);
                div_s(f0, f0, f1);
                swc1(f0, sp, 0x78);
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                div_s(f0, f0, f2);
                div_s(f0, f0, f1);
                swc1(f0, sp, 0x7C);
                sw(a1, sp, 0x80);
                sw(a0, sp, 0x84);
            } else {
                // 0x00346ab4
                charge(ctx, 53);
                a1 = s2;
                a2 = addiu(sp, 0xA0);
                jal(ctx, 0x346ABCu, gen::fn_sub_322FD0_00322fd0);
                lwc1(f4, sp, 0xA8);
                v0 = 0x41800000;
                mtc1(v0, f3);
                mul_s(f0, f3, f4);
                cvt_w_s(f1, f0);
                mfc1(v1, f1);
                lwc1(f5, sp, 0xAC);
                mul_s(f0, f3, f5);
                cvt_w_s(f2, f0);
                mfc1(v0, f2);
                sh(zero, sp, 0x88);
                sh(zero, sp, 0x8A);
                sh(v1, sp, 0x8C);
                sh(zero, sp, 0x8E);
                sh(v1, sp, 0x90);
                sh(v0, sp, 0x92);
                sh(zero, sp, 0x94);
                sh(v0, sp, 0x96);
                cvt_s_w(f1, f1);
                lwc1(f0, sp, 0xA0);
                mul_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(v0, f0);
                cvt_s_w(f1, f2);
                lwc1(f0, sp, 0xA4);
                mul_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                sw(zero, sp, 0x70);
                sw(zero, sp, 0x74);
                v0 = sra(v0, 5);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                div_s(f0, f0, f3);
                swc1(f0, sp, 0x78);
                v0 = sra(v1, 5);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                div_s(f0, f0, f3);
                swc1(f0, sp, 0x7C);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f4);
                if (cond(ctx)) {
                    // 0x00346b98
                    charge(ctx, 5);
                    sub_s(f0, f4, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                } else {
                    // 0x00346b88
                    charge(ctx, 4);
                    cvt_w_s(f0, f4);
                    mfc1(v1, f0);
                }
                // 0x00346bac
                charge(ctx, 7);
                sw(v1, sp, 0x80);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f5);
                if (cond(ctx)) {
                    // 0x00346bd8
                    charge(ctx, 5);
                    sub_s(f0, f5, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                } else {
                    // 0x00346bc8
                    charge(ctx, 4);
                    cvt_w_s(f0, f5);
                    mfc1(v1, f0);
                }
                // 0x00346bec
                charge(ctx, 7);
                sw(v1, sp, 0x84);
                lw(a0, s1, 20);
                lw(a1, sp, 0xB0);
                jal(ctx, 0x346BF8u, gen::fn_sub_494D50_00494d50);
            }
        } else {
            // 0x00346720: a sprite player: step it and take its cell, texture coordinates in 1/16 units
            charge(ctx, 22);
            a1 = s2;
            jal(ctx, 0x346724u, gen::fn_sub_322D40_00322d40);
            lw(a0, s3, kC7Player);
            a1 = addiu(sp, 0xC0);
            jal(ctx, 0x346734u, gen::fn_sub_322D10_00322d10);
            lwc1(f1, sp, 0xF0);
            v0 = 0x41800000;
            mtc1(v0, f2);
            mul_s(f3, f2, f1);
            lwc1(f0, sp, 0xF4);
            mul_s(f6, f2, f0);
            lwc1(f2, sp, 0xD8);
            mul_s(f4, f2, f3);
            v0 = 0x4F000000;
            mtc1(v0, f2);
            c_le_s(f2, f4);
            if (cond(ctx)) {
                // 0x00346790
                charge(ctx, 6);
                sub_s(f2, f4, f2);
                cvt_w_s(f2, f2);
                mfc1(v1, f2);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFFFF;
            } else {
                // 0x00346778
                charge(ctx, 6);
                cvt_w_s(f2, f4);
                mfc1(v1, f2);
                v1 = v1 & 0xFFFF;
            }
            // 0x003467a8
            charge(ctx, 9);
            sh(v1, sp, 0x88);
            lwc1(f2, sp, 0xDC);
            mul_s(f5, f2, f6);
            v0 = 0x4F000000;
            mtc1(v0, f2);
            c_le_s(f2, f5);
            if (cond(ctx)) {
                // 0x003467e4
                charge(ctx, 6);
                sub_s(f2, f5, f2);
                cvt_w_s(f2, f2);
                mfc1(v1, f2);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFFFF;
            } else {
                // 0x003467cc
                charge(ctx, 6);
                cvt_w_s(f2, f5);
                mfc1(v1, f2);
                v1 = v1 & 0xFFFF;
            }
            // 0x003467fc
            charge(ctx, 9);
            sh(v1, sp, 0x8A);
            lwc1(f2, sp, 0xE0);
            mul_s(f3, f2, f3);
            v0 = 0x4F000000;
            mtc1(v0, f2);
            c_le_s(f2, f3);
            if (cond(ctx)) {
                // 0x00346838
                charge(ctx, 6);
                sub_s(f2, f3, f2);
                cvt_w_s(f2, f2);
                mfc1(v1, f2);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFFFF;
            } else {
                // 0x00346820
                charge(ctx, 6);
                cvt_w_s(f2, f3);
                mfc1(v1, f2);
                v1 = v1 & 0xFFFF;
            }
            // 0x00346850
            charge(ctx, 7);
            sh(v1, sp, 0x8C);
            v0 = 0x4F000000;
            mtc1(v0, f2);
            c_le_s(f2, f5);
            if (cond(ctx)) {
                // 0x00346884
                charge(ctx, 6);
                sub_s(f2, f5, f2);
                cvt_w_s(f2, f2);
                mfc1(v1, f2);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFFFF;
            } else {
                // 0x0034686c
                charge(ctx, 6);
                cvt_w_s(f2, f5);
                mfc1(v1, f2);
                v1 = v1 & 0xFFFF;
            }
            // 0x0034689c
            charge(ctx, 7);
            sh(v1, sp, 0x8E);
            v0 = 0x4F000000;
            mtc1(v0, f2);
            c_le_s(f2, f3);
            if (cond(ctx)) {
                // 0x003468d0
                charge(ctx, 6);
                sub_s(f2, f3, f2);
                cvt_w_s(f2, f2);
                mfc1(v1, f2);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFFFF;
            } else {
                // 0x003468b8
                charge(ctx, 6);
                cvt_w_s(f2, f3);
                mfc1(v1, f2);
                v1 = v1 & 0xFFFF;
            }
            // 0x003468e8
            charge(ctx, 9);
            sh(v1, sp, 0x90);
            lwc1(f2, sp, 0xE4);
            mul_s(f3, f2, f6);
            v0 = 0x4F000000;
            mtc1(v0, f2);
            c_le_s(f2, f3);
            if (cond(ctx)) {
                // 0x00346924
                charge(ctx, 6);
                sub_s(f2, f3, f2);
                cvt_w_s(f2, f2);
                mfc1(v1, f2);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFFFF;
            } else {
                // 0x0034690c
                charge(ctx, 6);
                cvt_w_s(f2, f3);
                mfc1(v1, f2);
                v1 = v1 & 0xFFFF;
            }
            // 0x0034693c
            charge(ctx, 7);
            sh(v1, sp, 0x92);
            v0 = 0x4F000000;
            mtc1(v0, f2);
            c_le_s(f2, f4);
            if (cond(ctx)) {
                // 0x00346970
                charge(ctx, 6);
                sub_s(f2, f4, f2);
                cvt_w_s(f2, f2);
                mfc1(v1, f2);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFFFF;
            } else {
                // 0x00346958
                charge(ctx, 6);
                cvt_w_s(f2, f4);
                mfc1(v1, f2);
                v1 = v1 & 0xFFFF;
            }
            // 0x00346988
            charge(ctx, 7);
            sh(v1, sp, 0x94);
            v0 = 0x4F000000;
            mtc1(v0, f2);
            c_le_s(f2, f3);
            if (cond(ctx)) {
                // 0x003469bc
                charge(ctx, 6);
                sub_s(f2, f3, f2);
                cvt_w_s(f2, f2);
                mfc1(v1, f2);
                v0 = lui(0x8000);
                v1 = v1 | v0;
                v1 = v1 & 0xFFFF;
            } else {
                // 0x003469a4
                charge(ctx, 6);
                cvt_w_s(f2, f3);
                mfc1(v1, f2);
                v1 = v1 & 0xFFFF;
            }
            // 0x003469d4
            charge(ctx, 19);
            sh(v1, sp, 0x96);
            lwc1(f2, sp, 0xC0);
            swc1(f2, sp, 0x70);
            lwc1(f2, sp, 0xC4);
            swc1(f2, sp, 0x74);
            v0 = 0x41800000;
            mtc1(v0, f3);
            lwc1(f2, sp, 0xC8);
            div_s(f2, f2, f3);
            swc1(f2, sp, 0x78);
            lwc1(f2, sp, 0xCC);
            div_s(f2, f2, f3);
            swc1(f2, sp, 0x7C);
            v0 = 0x4F000000;
            mtc1(v0, f2);
            c_le_s(f2, f1);
            if (cond(ctx)) {
                // 0x00346a30
                charge(ctx, 5);
                sub_s(f1, f1, f2);
                cvt_w_s(f1, f1);
                mfc1(v1, f1);
                v0 = lui(0x8000);
                v1 = v1 | v0;
            } else {
                // 0x00346a20
                charge(ctx, 4);
                cvt_w_s(f1, f1);
                mfc1(v1, f1);
            }
            // 0x00346a44
            charge(ctx, 7);
            sw(v1, sp, 0x80);
            v0 = 0x4F000000;
            mtc1(v0, f1);
            c_le_s(f1, f0);
            if (cond(ctx)) {
                // 0x00346a70
                charge(ctx, 5);
                sub_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v0 = lui(0x8000);
                v1 = v1 | v0;
            } else {
                // 0x00346a60
                charge(ctx, 4);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
            }
            // 0x00346a84
            charge(ctx, 9);
            sw(v1, sp, 0x84);
            lwc1(f0, sp, 0xD0);
            add_s(f21, f21, f0);
            lw(a0, s1, 20);
            lw(a1, sp, 0xD4);
            jal(ctx, 0x346A98u, gen::fn_sub_494D50_00494d50);
        }
        // 0x00346ca0: lock the geometry, the four corners rotated by the angle
        charge(ctx, 63);
        lw(v0, s1, 16);
        lw(a0, v0, 24);
        a1 = 4082;
        jal(ctx, 0x346CACu, gen::fn_geometryLock_00493370);
        lw(v0, s1, 16);
        lw(v1, v0, 24);
        lw(v0, v1, 92);
        lw(s2, v0, 20);
        lw(s0, v1, 52);
        lwc1(f0, sp, 0x70);
        mul_s(f23, f0, f20);
        lwc1(f0, sp, 0x74);
        mul_s(f22, f0, f20);
        lwc1(f0, sp, 0x78);
        mul_s(f25, f0, f20);
        lwc1(f0, sp, 0x7C);
        mul_s(f24, f0, f20);
        mov_s(f12, f21);
        jal(ctx, 0x346CECu, gen::fn_cosf_0052e6d8);
        mov_s(f20, f0);
        mov_s(f12, f21);
        jal(ctx, 0x346CFCu, gen::fn_sinf_0052e878);
        add_s(f8, f23, f25);
        add_s(f2, f22, f24);
        mul_s(f4, f2, f0);
        mul_s(f7, f8, f20);
        sub_s(f1, f7, f4);
        swc1(f1, s2, 0);
        mtc1(zero, f6);
        sw(zero, s2, 4);
        mul_s(f3, f2, f20);
        adda_s(f6, f3);
        madd_s(f1, f8, f0);
        swc1(f1, s2, 8);
        sub_s(f2, f23, f25);
        mul_s(f5, f2, f20);
        sub_s(f1, f5, f4);
        swc1(f1, s2, 12);
        sw(zero, s2, 16);
        mul_s(f4, f2, f0);
        add_s(f1, f4, f3);
        swc1(f1, s2, 20);
        sub_s(f2, f22, f24);
        mul_s(f3, f2, f0);
        sub_s(f1, f5, f3);
        swc1(f1, s2, 36);
        sw(zero, s2, 40);
        mul_s(f2, f2, f20);
        add_s(f1, f4, f2);
        swc1(f1, s2, 44);
        sub_s(f1, f7, f3);
        swc1(f1, s2, 24);
        sw(zero, s2, 28);
        adda_s(f6, f2);
        madd_s(f0, f8, f0);
        swc1(f0, s2, 32);
        lw(v0, sp, 0x80);
        v0 = sll(v0, 4);
        if (i64(v0) < 0) {
            // 0x00346db0: corner vertices and their texture coordinates
            charge(ctx, 7);
            v1 = srl(v0, 1);
            v0 = v0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f0);
            cvt_s_w(f1, f0);
            add_s(f1, f1, f1);
        } else {
            // 0x00346d9c
            charge(ctx, 5);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
        }
        // 0x00346dcc
        charge(ctx, 9);
        v0 = 0x3F800000;
        mtc1(v0, f0);
        div_s(f1, f0, f1);
        lw(v0, sp, 0x84);
        v0 = sll(v0, 4);
        if (i64(v0) < 0) {
            // 0x00346e04
            charge(ctx, 7);
            v1 = srl(v0, 1);
            v0 = v0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f0);
            cvt_s_w(f2, f0);
            add_s(f2, f2, f2);
        } else {
            // 0x00346df0
            charge(ctx, 5);
            mtc1(v0, f0);
            cvt_s_w(f2, f0);
        }
        // 0x00346e20
        charge(ctx, 9);
        v0 = 0x3F800000;
        mtc1(v0, f0);
        div_s(f0, f0, f2);
        lhu(v0, sp, 0x88);
        if (i64(v0) < 0) {
            // 0x00346e58
            charge(ctx, 7);
            v1 = srl(v0, 1);
            v0 = v0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f2);
            cvt_s_w(f2, f2);
            add_s(f2, f2, f2);
        } else {
            // 0x00346e44
            charge(ctx, 5);
            mtc1(v0, f2);
            cvt_s_w(f2, f2);
        }
        // 0x00346e74
        charge(ctx, 5);
        mul_s(f2, f2, f1);
        swc1(f2, s0, 8);
        lhu(v0, sp, 0x8A);
        if (i64(v0) < 0) {
            // 0x00346e9c
            charge(ctx, 7);
            v1 = srl(v0, 1);
            v0 = v0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f2);
            cvt_s_w(f2, f2);
            add_s(f2, f2, f2);
        } else {
            // 0x00346e88
            charge(ctx, 5);
            mtc1(v0, f2);
            cvt_s_w(f2, f2);
        }
        // 0x00346eb8
        charge(ctx, 5);
        mul_s(f2, f2, f0);
        swc1(f2, s0, 12);
        lhu(v0, sp, 0x8C);
        if (i64(v0) < 0) {
            // 0x00346ee0
            charge(ctx, 7);
            v1 = srl(v0, 1);
            v0 = v0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f2);
            cvt_s_w(f2, f2);
            add_s(f2, f2, f2);
        } else {
            // 0x00346ecc
            charge(ctx, 5);
            mtc1(v0, f2);
            cvt_s_w(f2, f2);
        }
        // 0x00346efc
        charge(ctx, 5);
        mul_s(f2, f2, f1);
        swc1(f2, s0, 0);
        lhu(v0, sp, 0x8E);
        if (i64(v0) < 0) {
            // 0x00346f24
            charge(ctx, 7);
            v1 = srl(v0, 1);
            v0 = v0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f2);
            cvt_s_w(f2, f2);
            add_s(f2, f2, f2);
        } else {
            // 0x00346f10
            charge(ctx, 5);
            mtc1(v0, f2);
            cvt_s_w(f2, f2);
        }
        // 0x00346f40
        charge(ctx, 5);
        mul_s(f2, f2, f0);
        swc1(f2, s0, 4);
        lhu(v0, sp, 0x94);
        if (i64(v0) < 0) {
            // 0x00346f68
            charge(ctx, 7);
            v1 = srl(v0, 1);
            v0 = v0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f2);
            cvt_s_w(f2, f2);
            add_s(f2, f2, f2);
        } else {
            // 0x00346f54
            charge(ctx, 5);
            mtc1(v0, f2);
            cvt_s_w(f2, f2);
        }
        // 0x00346f84
        charge(ctx, 5);
        mul_s(f2, f2, f1);
        swc1(f2, s0, 24);
        lhu(v0, sp, 0x96);
        if (i64(v0) < 0) {
            // 0x00346fac
            charge(ctx, 7);
            v1 = srl(v0, 1);
            v0 = v0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f2);
            cvt_s_w(f2, f2);
            add_s(f2, f2, f2);
        } else {
            // 0x00346f98
            charge(ctx, 5);
            mtc1(v0, f2);
            cvt_s_w(f2, f2);
        }
        // 0x00346fc8
        charge(ctx, 5);
        mul_s(f2, f2, f0);
        swc1(f2, s0, 28);
        lhu(v0, sp, 0x90);
        if (i64(v0) < 0) {
            // 0x00346ff0
            charge(ctx, 7);
            v1 = srl(v0, 1);
            v0 = v0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f2);
            cvt_s_w(f2, f2);
            add_s(f2, f2, f2);
        } else {
            // 0x00346fdc
            charge(ctx, 5);
            mtc1(v0, f2);
            cvt_s_w(f2, f2);
        }
        // 0x0034700c
        charge(ctx, 5);
        mul_s(f1, f2, f1);
        swc1(f1, s0, 16);
        lhu(v0, sp, 0x92);
        if (i64(v0) < 0) {
            // 0x00347034
            charge(ctx, 7);
            v1 = srl(v0, 1);
            v0 = v0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f1);
            cvt_s_w(f1, f1);
            add_s(f1, f1, f1);
        } else {
            // 0x00347020
            charge(ctx, 5);
            mtc1(v0, f1);
            cvt_s_w(f1, f1);
        }
        // 0x00347050
        charge(ctx, 12);
        mul_s(f0, f1, f0);
        swc1(f0, s0, 20);
        lw(s2, s3, kC7Mesh);
        lw(v0, s2, 16);
        lw(s0, v0, 24);
        a0 = s0;
        jal(ctx, 0x347068u, gen::fn_sub_4933D0_004933d0);
        lhu(v0, s2, 0);
        v0 = v0 & 0x4;
        if (v0 != 0) {
            // 0x00347080
            charge(ctx, 3);
            lhu(v0, s0, 12);
            v0 = v0 | 0x1;
            sh(v0, s0, 12);
        }
        // 0x0034708c
        charge(ctx, 3);
        lbu(v0, s3, 196);
        if (v0 == 0) {
            // 0x003470ac
            charge(ctx, 3);
            lhu(v0, s1, 0);
            v0 = v0 & 0xFFFE;
            sh(v0, s1, 0);
        } else {
            // 0x00347098
            charge(ctx, 5);
            lhu(v0, s1, 0);
            v0 = v0 | 0x1;
            sh(v0, s1, 0);
        }
        // 0x003470b8
        charge(ctx, 4);
        lhu(a1, s3, 88);
        a0 = s1;
        jal(ctx, 0x3470C0u, gen::fn_sub_323860_00323860);
    }
    // 0x003470c8 (the shared epilogue, written out on this path)
    charge(ctx, 14);
    ld(ra, sp, 0x60);
    lq(s3, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f25, sp, 0x14);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x120);
}

// 0x00347100 sub_347100 -- 44 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Effect class 7, slot 1 [fxSpriteUpdate] ($a0 = the instance): ++frame (+44), then tail-calls sub_346530
// [fxSpriteDraw] (a `j`: no frame, $ra unchanged).
void sub_347100(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00347100
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, kC7Frame);
    v0 = addiu(v0, 1);
    sw(v0, a0, kC7Frame);
    jal(ctx, 0x347114u, gen::fn_sub_346530_00346530);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00347170 sub_347170 -- 340 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Creates a class-9 instance [fxFlareCreate] ($a0 = the 64-byte definition; returns it): a cleared 92-byte block,
// position 0, the definition copied to +24, a 13-quad mesh (sub_323E10(13, 4, 2, 4, layout 0x69BDC8, 76)) with flags
// 1 and 4 cleared, its 52 vertex colours white (geometry locked for prelight, then unlocked; re-instance when
// flagged).
void sub_347170(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Vf vf0{ctx, 0};
    // 0x00347170
    enter(ctx, 55);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = 92;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x347198u, v0.u());
    s0 = v0;
    a0 = s0;
    a1 = 0;
    a2 = 92;
    jal(ctx, 0x3471B0u, gen::fn_memset_00521408);
    sqc2(vf0, s0, kC9Pos);
    a0 = addiu(s0, 24);
    a1 = s1;
    a2 = 64;
    jal(ctx, 0x3471C8u, gen::fn_memcpy_00521250);
    a0 = 13;
    a1 = 4;
    a2 = 2;
    a3 = a1;
    t0 = 0x6A0000;
    t0 = addiu(t0, -16952);  // &0x69BDC8
    t1 = 76;
    jal(ctx, 0x3471ECu, gen::fn_sub_323E10_00323e10);
    sw(v0, s0, kC9Mesh);
    lhu(v1, v0, 0);
    v1 = v1 & 0xFFFE;
    sh(v1, v0, 0);
    lw(v1, s0, kC9Mesh);
    lhu(v0, v1, 0);
    v0 = v0 & 0xFFFB;
    sh(v0, v1, 0);
    lw(v0, s0, kC9Mesh);
    lw(v0, v0, 16);
    lw(a0, v0, 24);
    a1 = 8;
    jal(ctx, 0x347224u, gen::fn_geometryLock_00493370);
    lw(v0, s0, kC9Mesh);
    lw(v0, v0, 16);
    lw(v0, v0, 24);
    lw(a1, v0, 48);
    a0 = 0;
    v1 = si(-1);
    for (;;) {
        // 0x00347264
        charge(ctx, 3);
        v0 = sltiu(a0, 52);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0034724c
        charge(ctx, 6);
        sw(v1, a1, 0);
        sw(v1, a1, 4);
        sw(v1, a1, 8);
        sw(v1, a1, 12);
        a1 = addiu(a1, 16);
        a0 = addiu(a0, 1);
    }
    // 0x00347270
    charge(ctx, 10);
    lw(s2, s0, kC9Mesh);
    lw(v0, s2, 16);
    lw(s1, v0, 24);
    a0 = s1;
    jal(ctx, 0x347280u, gen::fn_sub_4933D0_004933d0);
    lhu(v0, s2, 0);
    v0 = v0 & 0x4;
    if (v0 != 0) {
        // 0x00347298
        charge(ctx, 3);
        lhu(v0, s1, 12);
        v0 = v0 | 0x1;
        sh(v0, s1, 12);
    }
    // 0x003472a4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = s0;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003472D0 sub_3472D0 -- 44 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Effect class 9, slot 0 [fxFlareNew] ($a0 = the effect record): sub_347170 on block A (sub_3245B0).
void sub_3472D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003472d0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x3472D8u, gen::fn_sub_3245B0_003245b0);
    a0 = v0;
    jal(ctx, 0x3472E4u, gen::fn_sub_347170_00347170);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00347350 sub_347350 -- 36 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Effect class 9, slot 5 [fxFlareClone] ($a0 = the source): sub_347170 on its definition copy (+24).
void sub_347350(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00347350
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = addiu(a0, 24);
    jal(ctx, 0x34735Cu, gen::fn_sub_347170_00347170);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003473B0 sub_3473B0 -- 2292 bytes; frame 0xF0: ra sp+0xA0, s7 sp+0x90 (sq), s6 sp+0x80 (sq), s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Effect class 9, slot 3 [fxFlareDraw] ($a0 = the instance). The light position is projected to the screen
// (sub_329A60; nothing when off screen); within the duration (+80) the intensity falls with the distance from the
// screen centre (320, 224) over the half diagonal sqrt(152576) and is scaled by +76; colour = the colour track
// (sub_32A120) x instance colour on VU0. The geometry is locked (vertices, prelight, texcoords) and each of the 13
// elements of the style (+84: rows of 13 x 16 bytes at 0x69C9E0 {position along the light-centre axis, size, u8
// texture index, RGBA}) gets its texture (sub_3210A0 -> sub_494D50), its size from the intensity, its colour, a
// screen-space quad at its point on the axis and full texture coordinates; elements with a zero colour are collapsed.
// Unlock, the camera frame matrix (sub_198590 / sub_4CB2F0 / sub_4CB7F0) and the queue on the 2D layer (sub_321120 /
// sub_321130, sub_3243D0).
void sub_3473B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25};
    Vf vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x003473b0: project the light position (sub_329A60); off screen: nothing
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
    sd(ra, sp, 0xA0);
    sq(s7, sp, 0x90);
    sq(s6, sp, 0x80);
    sq(s5, sp, 0x70);
    sq(s4, sp, 0x60);
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s4 = a0;
    lqc2(vf10, s4, kC9Pos);
    jal(ctx, 0x3473F8u, gen::fn_sub_329A60_00329a60);
    if (v0 != 0) {
        // 0x00347408: on screen: offsets from the centre (320, 224), the duration
        charge(ctx, 15);
        v1 = addiu(sp, 0xC0);
        sqc2(vf10, v1, 0);
        v1 = 0x43A00000;
        mtc1(v1, f21);
        lwc1(f0, sp, 0xC0);
        sub_s(f23, f0, f21);
        v1 = 0x43600000;
        mtc1(v1, f20);
        lwc1(f0, sp, 0xC4);
        sub_s(f22, f0, f20);
        lw(a3, s4, 80);
        lw(a2, s4, kC9Frame);
        lw(s2, s4, kC9Mesh);
        if (i64(a3) > 0) {
            // 0x00347444
            charge(ctx, 3);
            at = slt(a2, a3);
            if (at != 0) {
                goto L_00347450;
            }
            // 0x00347c5c (the shared epilogue, written out on this path)
            charge(ctx, 18);
            ld(ra, sp, 0xA0);
            lq(s7, sp, 0x90);
            lq(s6, sp, 0x80);
            lq(s5, sp, 0x70);
            lq(s4, sp, 0x60);
            lq(s3, sp, 0x50);
            lq(s2, sp, 0x40);
            lq(s1, sp, 0x30);
            lq(s0, sp, 0x20);
            lwc1(f25, sp, 0x14);
            lwc1(f24, sp, 0x10);
            lwc1(f23, sp, 0xC);
            lwc1(f22, sp, 0x8);
            lwc1(f21, sp, 0x4);
            lwc1(f20, sp, 0x0);
            sp = addiu(sp, 0xF0);
            return;
        }
    L_00347450:
        charge(ctx, 9);
        mula_s(f22, f22);
        mtc1(zero, f0);
        madd_s(f1, f23, f23);
        sqrt_s(f25, f1);
        c_le_s(f25, f0);
        if (!cond(ctx)) {
            // 0x00347474: intensity from the distance to the centre; colour track x instance colour; lock the geometry
            charge(ctx, 62);
            v0 = 0x48150000;
            mtc1(v0, f0);
            sqrt_s(f1, f0);
            sub_s(f0, f1, f25);
            div_s(f1, f0, f1);
            lwc1(f0, s4, 76);
            mul_s(f24, f1, f0);
            a0 = addiu(s4, 24);
            a1 = addiu(s4, 60);
            jal(ctx, 0x34749Cu, gen::fn_sub_32A120_0032a120);
            sw(v0, sp, 0xE8);
            v0 = addiu(sp, 0xE8);
            lwc1(f0, gp, -32420);  // 0x7CAE4C
            lw(v0, v0, 0);
            pextlb(v0, zero, v0);
            pextlh(v0, zero, v0);
            qmtc2(v0, vf11, false);  // qmtc2
            vitof0(0xF, vf11, vf11);  // vitof0.xyzw
            mfc1(v0, f0);
            qmtc2(v0, vf2, false);  // qmtc2
            vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
            lw(v0, s4, kC9Colour);
            sw(v0, sp, 0xE4);
            v0 = addiu(sp, 0xE4);
            lw(v0, v0, 0);
            pextlb(v0, zero, v0);
            pextlh(v0, zero, v0);
            qmtc2(v0, vf10, false);  // qmtc2
            vitof0(0xF, vf10, vf10);  // vitof0.xyzw
            mfc1(v0, f0);
            qmtc2(v0, vf2, false);  // qmtc2
            vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
            vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
            v0 = addiu(sp, 0xB0);
            sqc2(vf10, v0, 0);
            lw(v0, s2, 16);
            lw(a0, v0, 24);
            a1 = 4082;
            jal(ctx, 0x34751Cu, gen::fn_geometryLock_00493370);
            lw(v0, s2, 16);
            lw(v1, v0, 24);
            lw(v0, v1, 92);
            lw(s1, v0, 20);
            s5 = s1;
            lw(s0, v1, 52);
            lbu(v1, s4, 84);
            v0 = sll(v1, 1);
            v0 = addu(v0, v1);
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            v1 = sll(v0, 4);
            v0 = 0x6A0000;
            v0 = addiu(v0, -13856);  // &0x69C9E0
            s3 = addu(v0, v1);
            s6 = 0;
            for (;;) {
                // 0x00347acc: for each of the 13 elements
                charge(ctx, 3);
                v0 = sltiu(s6, 13);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0034756c
                charge(ctx, 5);
                lw(v1, s3, 12);
                v0 = lui(0xFF00);
                v0 = v1 & v0;
                if (v0 != 0) {
                    // 0x003476c8: a visible element: its texture, size, colour and quad
                    charge(ctx, 47);
                    lbu(a0, s3, 8);
                    jal(ctx, 0x3476CCu, gen::fn_sub_3210A0_003210a0);
                    v1 = s6 & 0xFFFF;
                    s7 = sll(v1, 2);
                    lw(v1, s2, 40);
                    v1 = addu(v1, s7);
                    lw(a0, v1, 0);
                    a1 = v0;
                    jal(ctx, 0x3476ECu, gen::fn_sub_494D50_00494d50);
                    lwc1(f0, s3, 0);
                    mul_s(f2, f23, f0);
                    mul_s(f1, f22, f0);
                    add_s(f0, f21, f2);
                    cvt_w_s(f0, f0);
                    mfc1(a1, f0);
                    add_s(f0, f20, f1);
                    cvt_w_s(f0, f0);
                    mfc1(a0, f0);
                    mula_s(f1, f1);
                    madd_s(f0, f2, f2);
                    sqrt_s(f0, f0);
                    div_s(f0, f0, f25);
                    mul_s(f2, f0, f24);
                    v0 = 0x43000000;
                    mtc1(v0, f1);
                    lwc1(f0, s3, 4);
                    mul_s(f0, f1, f0);
                    mul_s(f1, f0, f2);
                    v0 = 0x3F000000;
                    mtc1(v0, f0);
                    mul_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    sqrt_s(f1, f2);
                    v0 = 0x437F0000;
                    mtc1(v0, f0);
                    mul_s(f1, f0, f1);
                    v0 = 0x4F000000;
                    mtc1(v0, f0);
                    c_le_s(f0, f1);
                    if (cond(ctx)) {
                        // 0x00347794
                        charge(ctx, 5);
                        sub_s(f0, f1, f0);
                        cvt_w_s(f0, f0);
                        mfc1(a2, f0);
                        v0 = lui(0x8000);
                        a2 = a2 | v0;
                    } else {
                        // 0x00347784
                        charge(ctx, 4);
                        cvt_w_s(f0, f1);
                        mfc1(a2, f0);
                    }
                    // 0x003477a8
                    charge(ctx, 46);
                    a2 = sll(a2, 24);
                    v0 = 0xFF0000;
                    v0 = v0 | 0xFFFF;  // &0xFFFFFF
                    v0 = a2 | v0;
                    sw(v0, sp, 0xE0);
                    v0 = addiu(sp, 0xE0);
                    lwc1(f0, gp, -32420);  // 0x7CAE4C
                    lw(v0, v0, 0);
                    pextlb(v0, zero, v0);
                    pextlh(v0, zero, v0);
                    qmtc2(v0, vf11, false);  // qmtc2
                    vitof0(0xF, vf11, vf11);  // vitof0.xyzw
                    mfc1(v0, f0);
                    qmtc2(v0, vf2, false);  // qmtc2
                    vmul_bc(0xF, vf11, vf11, vf2, 0);  // vmulx.xyzw
                    lw(v0, s3, 12);
                    sw(v0, sp, 0xDC);
                    v0 = addiu(sp, 0xDC);
                    lw(v0, v0, 0);
                    pextlb(v0, zero, v0);
                    pextlh(v0, zero, v0);
                    qmtc2(v0, vf10, false);  // qmtc2
                    vitof0(0xF, vf10, vf10);  // vitof0.xyzw
                    mfc1(v0, f0);
                    qmtc2(v0, vf2, false);  // qmtc2
                    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                    vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
                    v0 = addiu(sp, 0xB0);
                    lqc2(vf11, v0, 0);
                    vmul(0xF, vf10, vf10, vf11);  // vmul.xyzw
                    v0 = 0x437F0000;
                    qmtc2(v0, vf2, false);  // qmtc2
                    vmul_bc(0xF, vf10, vf10, vf2, 0);  // vmulx.xyzw
                    vftoi0(0xF, vf10, vf10);  // vftoi0.xyzw
                    qmfc2(v0, vf10, false);  // qmfc2
                    ppach(v0, zero, v0);
                    ppacb(v0, zero, v0);
                    sw(v0, sp, 0xD8);
                    lw(v0, sp, 0xD8);
                    sw(v0, sp, 0xEC);
                    lbu(v0, sp, 0xEF);
                    t2 = 255;
                    if (v0 == t2) {
                        // 0x00347894
                        charge(ctx, 14);
                        v0 = 254;
                        sb(v0, sp, 0xEF);
                        lw(v0, s2, 40);
                        v0 = addu(v0, s7);
                        lw(t1, v0, 0);
                        lbu(t0, sp, 0xEC);
                        lbu(a3, sp, 0xED);
                        lbu(a2, sp, 0xEE);
                        lbu(v0, sp, 0xEF);
                        sb(t0, t1, 4);
                        sb(a3, t1, 5);
                        sb(a2, t1, 6);
                        sb(v0, t1, 7);
                        sb(t2, sp, 0xEF);
                    } else {
                        // 0x00347860
                        charge(ctx, 13);
                        lw(v0, s2, 40);
                        v0 = addu(v0, s7);
                        lw(t1, v0, 0);
                        lbu(t0, sp, 0xEC);
                        lbu(a3, sp, 0xED);
                        lbu(a2, sp, 0xEE);
                        lbu(v0, sp, 0xEF);
                        sb(t0, t1, 4);
                        sb(a3, t1, 5);
                        sb(a2, t1, 6);
                        sb(v0, t1, 7);
                    }
                    // 0x003478cc
                    charge(ctx, 126);
                    sw(zero, s0, 0);
                    sw(zero, s0, 4);
                    a2 = 0x3F700000;
                    sw(a2, s0, 8);
                    sw(zero, s0, 12);
                    sw(zero, s0, 16);
                    sw(a2, s0, 20);
                    sw(a2, s0, 24);
                    sw(a2, s0, 28);
                    v0 = sra(v1, 1);
                    v1 = addiu(v0, -1);
                    v0 = subu(a1, v1);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    swc1(f1, s1, 0);
                    v0 = subu(a0, v1);
                    mtc1(v0, f0);
                    cvt_s_w(f4, f0);
                    swc1(f4, s1, 4);
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                    lwc1(f2, s1, 0);
                    add_s(f2, f2, f0);
                    swc1(f2, s1, 12);
                    lwc1(f2, s1, 4);
                    swc1(f2, s1, 16);
                    lwc1(f2, s1, 0);
                    swc1(f2, s1, 24);
                    lwc1(f2, s1, 4);
                    add_s(f2, f2, f0);
                    swc1(f2, s1, 28);
                    lwc1(f2, s1, 0);
                    add_s(f2, f2, f0);
                    swc1(f2, s1, 36);
                    lwc1(f2, s1, 4);
                    add_s(f2, f2, f0);
                    swc1(f2, s1, 40);
                    sw(a2, s0, 32);
                    sw(zero, s0, 36);
                    sw(zero, s0, 40);
                    sw(zero, s0, 44);
                    sw(a2, s0, 48);
                    sw(a2, s0, 52);
                    sw(zero, s0, 56);
                    sw(a2, s0, 60);
                    mtc1(a1, f2);
                    cvt_s_w(f3, f2);
                    swc1(f3, s1, 48);
                    swc1(f4, s1, 52);
                    lwc1(f2, s1, 48);
                    add_s(f2, f2, f0);
                    swc1(f2, s1, 60);
                    lwc1(f2, s1, 52);
                    swc1(f2, s1, 64);
                    lwc1(f2, s1, 48);
                    swc1(f2, s1, 72);
                    lwc1(f2, s1, 52);
                    add_s(f2, f2, f0);
                    swc1(f2, s1, 76);
                    lwc1(f2, s1, 48);
                    add_s(f2, f2, f0);
                    swc1(f2, s1, 84);
                    lwc1(f2, s1, 52);
                    add_s(f2, f2, f0);
                    swc1(f2, s1, 88);
                    sw(zero, s0, 64);
                    sw(a2, s0, 68);
                    sw(a2, s0, 72);
                    sw(a2, s0, 76);
                    sw(zero, s0, 80);
                    sw(zero, s0, 84);
                    sw(a2, s0, 88);
                    sw(zero, s0, 92);
                    swc1(f1, s1, 96);
                    mtc1(a0, f1);
                    cvt_s_w(f2, f1);
                    swc1(f2, s1, 100);
                    lwc1(f1, s1, 96);
                    add_s(f1, f1, f0);
                    swc1(f1, s1, 108);
                    lwc1(f1, s1, 100);
                    swc1(f1, s1, 112);
                    lwc1(f1, s1, 96);
                    swc1(f1, s1, 120);
                    lwc1(f1, s1, 100);
                    add_s(f1, f1, f0);
                    swc1(f1, s1, 124);
                    lwc1(f1, s1, 96);
                    add_s(f1, f1, f0);
                    swc1(f1, s1, 132);
                    lwc1(f1, s1, 100);
                    add_s(f1, f1, f0);
                    swc1(f1, s1, 136);
                    sw(a2, s0, 96);
                    sw(a2, s0, 100);
                    sw(zero, s0, 104);
                    sw(a2, s0, 108);
                    sw(a2, s0, 112);
                    sw(zero, s0, 116);
                    sw(zero, s0, 120);
                    sw(zero, s0, 124);
                    swc1(f3, s1, 144);
                    swc1(f2, s1, 148);
                    lwc1(f1, s1, 144);
                    add_s(f1, f1, f0);
                    swc1(f1, s1, 156);
                    lwc1(f1, s1, 148);
                    swc1(f1, s1, 160);
                    lwc1(f1, s1, 144);
                    swc1(f1, s1, 168);
                    lwc1(f1, s1, 148);
                    add_s(f1, f1, f0);
                    swc1(f1, s1, 172);
                    lwc1(f1, s1, 144);
                    add_s(f1, f1, f0);
                    swc1(f1, s1, 180);
                    lwc1(f1, s1, 148);
                    add_s(f0, f1, f0);
                    swc1(f0, s1, 184);
                    s1 = addiu(s1, 192);
                    s0 = addiu(s0, 128);
                } else {
                    // 0x00347580: a zero colour: collapse its quad
                    charge(ctx, 16);
                    s0 = addiu(s0, 128);
                    t7 = 0;
                    t5 = 0x950000;
                    t4 = 0x950000;
                    t3 = 0x950000;
                    t2 = 0x950000;
                    t1 = 0x950000;
                    t0 = 0x950000;
                    a3 = 0x950000;
                    a2 = 0x950000;
                    a1 = 0x950000;
                    a0 = 0x950000;
                    v1 = 0x950000;
                    v0 = 0x950000;
                    for (;;) {
                        // 0x00347628
                        charge(ctx, 3);
                        t6 = sltiu(t7, 4);
                        if (t6 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x003475c0
                        charge(ctx, 26);
                        lwc1(f2, t5, 31376);
                        lwc1(f1, t4, 31380);
                        lwc1(f0, t3, 31384);
                        swc1(f2, s1, 0);
                        swc1(f1, s1, 4);
                        swc1(f0, s1, 8);
                        lwc1(f2, t2, 31376);
                        lwc1(f1, t1, 31380);
                        lwc1(f0, t0, 31384);
                        swc1(f2, s1, 12);
                        swc1(f1, s1, 16);
                        swc1(f0, s1, 20);
                        lwc1(f2, a3, 31376);
                        lwc1(f1, a2, 31380);
                        lwc1(f0, a1, 31384);
                        swc1(f2, s1, 24);
                        swc1(f1, s1, 28);
                        swc1(f0, s1, 32);
                        lwc1(f2, a0, 31376);
                        lwc1(f1, v1, 31380);
                        lwc1(f0, v0, 31384);
                        swc1(f2, s1, 36);
                        swc1(f1, s1, 40);
                        swc1(f0, s1, 44);
                        s1 = addiu(s1, 48);
                        t7 = addiu(t7, 1);
                    }
                    // 0x00347634
                    charge(ctx, 4);
                    lbu(v0, gp, -18345);  // 0x7CE547
                    a3 = 255;
                    if (v0 == a3) {
                        // 0x00347680
                        charge(ctx, 18);
                        v0 = 254;
                        sb(v0, gp, -18345);  // 0x7CE547
                        v0 = s6 & 0xFFFF;
                        v1 = sll(v0, 2);
                        lw(v0, s2, 40);
                        v0 = addu(v0, v1);
                        lw(a2, v0, 0);
                        lbu(a1, gp, -18348);  // 0x7CE544
                        lbu(a0, gp, -18347);  // 0x7CE545
                        lbu(v1, gp, -18346);  // 0x7CE546
                        lbu(v0, gp, -18345);  // 0x7CE547
                        sb(a1, a2, 4);
                        sb(a0, a2, 5);
                        sb(v1, a2, 6);
                        sb(v0, a2, 7);
                        sb(a3, gp, -18345);  // 0x7CE547
                    } else {
                        // 0x00347644
                        charge(ctx, 15);
                        v0 = s6 & 0xFFFF;
                        v1 = sll(v0, 2);
                        lw(v0, s2, 40);
                        v0 = addu(v0, v1);
                        lw(a2, v0, 0);
                        lbu(a1, gp, -18348);  // 0x7CE544
                        lbu(a0, gp, -18347);  // 0x7CE545
                        lbu(v1, gp, -18346);  // 0x7CE546
                        lbu(v0, gp, -18345);  // 0x7CE547
                        sb(a1, a2, 4);
                        sb(a0, a2, 5);
                        sb(v1, a2, 6);
                        sb(v0, a2, 7);
                    }
                }
                // 0x00347ac4
                charge(ctx, 2);
                s6 = addiu(s6, 1);
                s3 = addiu(s3, 16);
            }
            // 0x00347ad8: the camera frame
            charge(ctx, 44);
            jal(ctx, 0x347AD8u, gen::fn_sub_198590_00198590);
            s0 = addiu(v0, 104);
            jal(ctx, 0x347AE4u, gen::fn_sub_198590_00198590);
            lwc1(f20, v0, 128);
            jal(ctx, 0x347AF0u, gen::fn_sub_198590_00198590);
            lwc1(f3, v0, 132);
            sub_s(f2, f3, f20);
            v0 = lui(0xC37F);
            mtc1(v0, f1);
            v0 = lui(0xFFFF);
            v0 = v0 | 0x1;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            mula_s(f0, f3);
            msub_s(f1, f1, f2);
            mul_s(f0, f0, f20);
            mul_s(f0, f0, f3);
            div_s(f2, f0, f1);
            lwc1(f0, s0, 0);
            mul_s(f0, f0, f2);
            v0 = 0x40000000;
            mtc1(v0, f1);
            mul_s(f6, f1, f0);
            lwc1(f0, s0, 4);
            mul_s(f0, f0, f2);
            mul_s(f5, f1, f0);
            v1 = 0;
            v0 = 0x3F800000;
            mtc1(v0, f0);
            add_s(f4, f0, f2);
            v0 = 0x44200000;
            mtc1(v0, f3);
            v0 = 0x3F000000;
            mtc1(v0, f2);
            v0 = 0x43E00000;
            mtc1(v0, f1);
            for (;;) {
                // 0x00347bc4
                charge(ctx, 3);
                v0 = sltiu(v1, 208);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00347b88
                charge(ctx, 15);
                lwc1(f0, s5, 0);
                neg_s(f0, f0);
                div_s(f0, f0, f3);
                add_s(f0, f2, f0);
                mul_s(f0, f0, f6);
                swc1(f0, s5, 0);
                lwc1(f0, s5, 4);
                neg_s(f0, f0);
                div_s(f0, f0, f1);
                add_s(f0, f2, f0);
                mul_s(f0, f0, f5);
                swc1(f0, s5, 4);
                swc1(f4, s5, 8);
                s5 = addiu(s5, 12);
                v1 = addiu(v1, 1);
            }
            // 0x00347bd0: unlock the geometry
            charge(ctx, 9);
            lw(v0, s2, 16);
            lw(s0, v0, 24);
            a0 = s0;
            jal(ctx, 0x347BDCu, gen::fn_sub_4933D0_004933d0);
            lhu(v0, s2, 0);
            v0 = v0 & 0x4;
            if (v0 != 0) {
                // 0x00347bf4
                charge(ctx, 3);
                lhu(v0, s0, 12);
                v0 = v0 | 0x1;
                sh(v0, s0, 12);
            }
            // 0x00347c00: the camera frame matrix onto the mesh, queue on the 2D layer
            charge(ctx, 23);
            jal(ctx, 0x347C00u, gen::fn_sub_198590_00198590);
            lw(a0, v0, 4);
            jal(ctx, 0x347C0Cu, gen::fn_sub_4CB2F0_004cb2f0);
            lw(a0, s2, 12);
            a1 = v0;
            a2 = 0;
            jal(ctx, 0x347C20u, gen::fn_sub_4CB7F0_004cb7f0);
            jal(ctx, 0x347C28u, gen::fn_sub_321130_00321130);
            s0 = v0 & 0xFFFF;
            a0 = 5;
            jal(ctx, 0x347C38u, gen::fn_sub_321120_00321120);
            lhu(a1, s4, 64);
            a0 = s2;
            jal(ctx, 0x347C48u, gen::fn_sub_3243D0_003243d0);
            a0 = s0;
            jal(ctx, 0x347C54u, gen::fn_sub_321120_00321120);
        }
    }
    // 0x00347c5c (the shared epilogue, written out on this path)
    charge(ctx, 18);
    ld(ra, sp, 0xA0);
    lq(s7, sp, 0x90);
    lq(s6, sp, 0x80);
    lq(s5, sp, 0x70);
    lq(s4, sp, 0x60);
    lq(s3, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f25, sp, 0x14);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xF0);
}

// 0x00347CB0 sub_347CB0 -- 44 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Effect class 9, slot 1 [fxFlareUpdate] ($a0 = the instance): ++frame (+16), then tail-calls sub_3473B0.
void sub_347CB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00347cb0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, kC9Frame);
    v0 = addiu(v0, 1);
    sw(v0, a0, kC9Frame);
    jal(ctx, 0x347CC4u, gen::fn_sub_3473B0_003473b0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00347FC0 sub_347FC0 -- 108 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Effect class 21, slot 0 [fxShakeObjCreate] ($a0 = the effect record; returns the instance): a 20-byte block, frame
// (+0) = 0, the shake record of block A copied to +4 (length, fade-in, fade-out, strength: fx_types' sub_348110).
void sub_347FC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00347fc0
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x347FD0u, gen::fn_sub_3245B0_003245b0);
    s1 = v0;
    a0 = 20;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x347FECu, v0.u());
    s0 = v0;
    sw(zero, v0, 0);
    a0 = addiu(s0, 4);
    a1 = s1;
    a2 = 16;
    jal(ctx, 0x348008u, gen::fn_memcpy_00521250);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00348030 sub_348030 -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Effect class 21, slot 4 [fxShakeObjDestroy] ($a0 = the instance): the shake camera's frame (gp-18384) goes back to
// 0x957A90 (sub_4CB750 [frame dirty-list mark]), the shake active byte (gp-18340) is cleared and the instance freed.
void sub_348030(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00348030
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, gp, -18320);  // 0x7CE560
    a1 = 0x950000;
    a1 = addiu(a1, 31376);  // &0x957A90
    a2 = 0;
    jal(ctx, 0x348050u, gen::fn_sub_4CB750_004cb750);
    sb(zero, gp, -18340);  // 0x7CE54C
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x348068u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00348090 sub_348090 -- 100 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Effect class 21, slot 5 [fxShakeObjClone] ($a0 = the source; returns the copy): a 20-byte block, frame 0, the
// source's record (+4) copied.
void sub_348090(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00348090
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = 20;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x3480B4u, v0.u());
    s0 = v0;
    sw(zero, v0, 0);
    a0 = addiu(s0, 4);
    a1 = addiu(s1, 4);
    a2 = 16;
    jal(ctx, 0x3480D0u, gen::fn_memcpy_00521250);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00348340 sub_348340 -- 1044 bytes; frame 0x90: ra sp+0x80, s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Builds a textured screen quad [fltQuadUvRotated] ($a0 = the filter output: RGBA, angle +8, scale +12, centre +16 /
// +20, rectangle +24..+36; $a1 = the vertices; returns 1, or 0 when the rectangle is off screen (beyond 640 x 448) or
// its texture span is empty or 7 or more): the four Im2D vertices of a screen quad ($a1 = 4 x 64 bytes): every vertex
// gets z = the near screen z (0x960088), rhw = 1 / the camera's far plane (sub_198590 -> +128) and the RGBA bytes of
// $a0 +0..+3 as floats; the corners from the rectangle (+24..+36); the texture coordinates are the rectangle's screen
// position over the screen size (0x957BAC / 0x957BB0) around the centre, scaled, and rotated by the angle (cosf /
// sinf) when it is not 0. Called for every filter quad (sub_348DA0, sub_349A30, sub_349D30).
void sub_348340(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26};
    // 0x00348340
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x80);
    sq(s5, sp, 0x70);
    sq(s4, sp, 0x60);
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f26, sp, 0x18);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s5 = a0;
    s4 = a1;
    lwc1(f1, a0, 24);
    v0 = 0x44200000;
    mtc1(v0, f0);
    c_le_s(f1, f0);
    if (cond(ctx)) {
        // 0x003483a0
        charge(ctx, 7);
        lwc1(f1, s5, 28);
        v0 = 0x43E00000;
        mtc1(v0, f0);
        c_le_s(f1, f0);
        if (!cond(ctx)) {
            goto L_003483e4;
        }
        // 0x003483bc
        charge(ctx, 6);
        lwc1(f0, s5, 32);
        mtc1(zero, f1);
        c_lt_s(f0, f1);
        if (cond(ctx)) {
            goto L_003483e4;
        }
        // 0x003483d4
        charge(ctx, 4);
        lwc1(f0, s5, 36);
        c_lt_s(f0, f1);
        if (cond(ctx)) {
            goto L_003483e4;
        }
        // 0x003483f0
        charge(ctx, 23);
        lbu(s3, s5, 0);
        lbu(s2, s5, 1);
        lbu(s1, s5, 2);
        lbu(s0, s5, 3);
        jal(ctx, 0x348400u, gen::fn_sub_198590_00198590);
        v1 = 0x3F800000;
        mtc1(v1, f1);
        lwc1(f0, v0, 128);
        div_s(f6, f1, f0);
        v0 = 0x960000;
        lwc1(f5, v0, 136);  // g_rwIm2DNearScreenZ
        t0 = 0;
        a2 = s3 & 0x1;
        mtc1(s3, f4);
        a1 = s2 & 0x1;
        mtc1(s2, f3);
        a0 = s1 & 0x1;
        mtc1(s1, f2);
        v1 = s0 & 0x1;
        mtc1(s0, f1);
        for (;;) {
            // 0x00348520
            charge(ctx, 3);
            v0 = sltiu(t0, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0034844c
            charge(ctx, 5);
            v0 = sll(t0, 6);
            a3 = addu(s4, v0);
            swc1(f6, a3, 24);
            if (i64(s3) < 0) {
                // 0x0034846c
                charge(ctx, 6);
                v0 = srl(s3, 1);
                v0 = v0 | a2;
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x00348460
                charge(ctx, 3);
                cvt_s_w(f0, f4);
            }
            // 0x00348484
            charge(ctx, 3);
            swc1(f0, a3, 32);
            if (i64(s2) < 0) {
                // 0x0034849c
                charge(ctx, 6);
                v0 = srl(s2, 1);
                v0 = v0 | a1;
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x00348490
                charge(ctx, 3);
                cvt_s_w(f0, f3);
            }
            // 0x003484b4
            charge(ctx, 3);
            swc1(f0, a3, 36);
            if (i64(s1) < 0) {
                // 0x003484cc
                charge(ctx, 6);
                v0 = srl(s1, 1);
                v0 = v0 | a0;
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x003484c0
                charge(ctx, 3);
                cvt_s_w(f0, f2);
            }
            // 0x003484e4
            charge(ctx, 3);
            swc1(f0, a3, 40);
            if (i64(s0) < 0) {
                // 0x003484fc
                charge(ctx, 6);
                v0 = srl(s0, 1);
                v0 = v0 | v1;
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x003484f0
                charge(ctx, 3);
                cvt_s_w(f0, f1);
            }
            // 0x00348514
            charge(ctx, 3);
            swc1(f0, a3, 44);
            swc1(f5, a3, 8);
            t0 = addiu(t0, 1);
        }
        // 0x0034852c
        charge(ctx, 34);
        v0 = 0x950000;
        lwc1(f2, v0, 31660);  // 0x957BAC
        lwc1(f0, s5, 16);
        div_s(f26, f0, f2);
        v0 = 0x950000;
        lwc1(f1, v0, 31664);  // 0x957BB0
        lwc1(f0, s5, 20);
        div_s(f25, f0, f1);
        lwc1(f6, s5, 12);
        lwc1(f5, s5, 24);
        div_s(f4, f5, f2);
        lwc1(f0, s5, 28);
        div_s(f3, f0, f1);
        lwc1(f0, s5, 32);
        div_s(f2, f0, f2);
        lwc1(f0, s5, 36);
        div_s(f1, f0, f1);
        sub_s(f0, f4, f26);
        mul_s(f24, f6, f0);
        sub_s(f0, f3, f25);
        mul_s(f23, f6, f0);
        sub_s(f0, f2, f26);
        mul_s(f22, f6, f0);
        sub_s(f0, f1, f25);
        mul_s(f21, f6, f0);
        sub_s(f0, f24, f22);
        abs_s(f3, f0);
        sub_s(f0, f23, f21);
        abs_s(f2, f0);
        mtc1(zero, f1);
        c_le_s(f3, f1);
        if (!cond(ctx)) {
            // 0x003485b4
            charge(ctx, 3);
            c_le_s(f2, f1);
            if (cond(ctx)) {
                goto L_003485e4;
            }
            // 0x003485c0
            charge(ctx, 6);
            v0 = 0x40E00000;
            mtc1(v0, f0);
            c_lt_s(f3, f0);
            if (!cond(ctx)) {
                goto L_003485e4;
            }
            // 0x003485d8
            charge(ctx, 3);
            c_lt_s(f2, f0);
            if (!cond(ctx)) {
                goto L_003485e4;
            }
            // 0x003485f0
            charge(ctx, 19);
            swc1(f5, s4, 0);
            lwc1(f0, s5, 28);
            swc1(f0, s4, 4);
            lwc1(f0, s5, 24);
            swc1(f0, s4, 64);
            lwc1(f0, s5, 36);
            swc1(f0, s4, 68);
            lwc1(f0, s5, 32);
            swc1(f0, s4, 128);
            lwc1(f0, s5, 36);
            swc1(f0, s4, 132);
            lwc1(f0, s5, 32);
            swc1(f0, s4, 192);
            lwc1(f0, s5, 28);
            swc1(f0, s4, 196);
            lwc1(f12, s5, 8);
            c_eq_s(f1, f12);
            if (!cond(ctx)) {
                // 0x00348674
                charge(ctx, 38);
                jal(ctx, 0x348674u, gen::fn_cosf_0052e6d8);
                mov_s(f20, f0);
                lwc1(f12, s5, 8);
                jal(ctx, 0x348684u, gen::fn_sinf_0052e878);
                mul_s(f6, f23, f0);
                mul_s(f3, f24, f20);
                sub_s(f1, f3, f6);
                add_s(f1, f26, f1);
                swc1(f1, s4, 16);
                mul_s(f5, f23, f20);
                mul_s(f2, f24, f0);
                add_s(f1, f2, f5);
                add_s(f1, f25, f1);
                swc1(f1, s4, 20);
                mul_s(f4, f21, f0);
                sub_s(f1, f3, f4);
                add_s(f1, f26, f1);
                swc1(f1, s4, 80);
                mul_s(f3, f21, f20);
                add_s(f1, f2, f3);
                add_s(f1, f25, f1);
                swc1(f1, s4, 84);
                mul_s(f2, f22, f20);
                sub_s(f1, f2, f4);
                add_s(f1, f26, f1);
                swc1(f1, s4, 144);
                mul_s(f1, f22, f0);
                add_s(f0, f1, f3);
                add_s(f0, f25, f0);
                swc1(f0, s4, 148);
                sub_s(f0, f2, f6);
                add_s(f0, f26, f0);
                swc1(f0, s4, 208);
                add_s(f0, f1, f5);
                add_s(f0, f25, f0);
                swc1(f0, s4, 212);
            } else {
                // 0x0034863c
                charge(ctx, 14);
                add_s(f3, f24, f26);
                add_s(f2, f22, f26);
                add_s(f1, f23, f25);
                add_s(f0, f21, f25);
                swc1(f3, s4, 16);
                swc1(f1, s4, 20);
                swc1(f3, s4, 80);
                swc1(f0, s4, 84);
                swc1(f2, s4, 144);
                swc1(f0, s4, 148);
                swc1(f2, s4, 208);
                swc1(f1, s4, 212);
            }
            // 0x0034870c
            charge(ctx, 1);
            v0 = 1;
            // 0x00348710 (the shared epilogue, written out on this path)
            charge(ctx, 17);
            ld(ra, sp, 0x80);
            lq(s5, sp, 0x70);
            lq(s4, sp, 0x60);
            lq(s3, sp, 0x50);
            lq(s2, sp, 0x40);
            lq(s1, sp, 0x30);
            lq(s0, sp, 0x20);
            lwc1(f26, sp, 0x18);
            lwc1(f25, sp, 0x14);
            lwc1(f24, sp, 0x10);
            lwc1(f23, sp, 0xC);
            lwc1(f22, sp, 0x8);
            lwc1(f21, sp, 0x4);
            lwc1(f20, sp, 0x0);
            sp = addiu(sp, 0x90);
            return;
        }
    L_003485e4:
        charge(ctx, 3);
        v0 = 0;
        // 0x00348710 (the shared epilogue, written out on this path)
        charge(ctx, 17);
        ld(ra, sp, 0x80);
        lq(s5, sp, 0x70);
        lq(s4, sp, 0x60);
        lq(s3, sp, 0x50);
        lq(s2, sp, 0x40);
        lq(s1, sp, 0x30);
        lq(s0, sp, 0x20);
        lwc1(f26, sp, 0x18);
        lwc1(f25, sp, 0x14);
        lwc1(f24, sp, 0x10);
        lwc1(f23, sp, 0xC);
        lwc1(f22, sp, 0x8);
        lwc1(f21, sp, 0x4);
        lwc1(f20, sp, 0x0);
        sp = addiu(sp, 0x90);
        return;
    }
L_003483e4:
    charge(ctx, 3);
    v0 = 0;
    // 0x00348710 (the shared epilogue, written out on this path)
    charge(ctx, 17);
    ld(ra, sp, 0x80);
    lq(s5, sp, 0x70);
    lq(s4, sp, 0x60);
    lq(s3, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f26, sp, 0x18);
    lwc1(f25, sp, 0x14);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x00348760 sub_348760 -- 496 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Builds a textured screen quad [fltQuadUvFull] ($a0 = the filter output, $a1 = the vertices): the four Im2D vertices
// of a screen quad ($a1 = 4 x 64 bytes): every vertex gets z = the near screen z (0x960088), rhw = 1 / the camera's
// far plane (sub_198590 -> +128) and the RGBA bytes of $a0 +0..+3 as floats; the corners from the rectangle at $a0
// +24..+36 and the texture coordinates (0, 0) .. (1, 1).
void sub_348760(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6};
    // 0x00348760
    enter(ctx, 33);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    s4 = a1;
    lbu(s3, a0, 0);
    lbu(s2, a0, 1);
    lbu(s1, a0, 2);
    lbu(s0, a0, 3);
    jal(ctx, 0x348798u, gen::fn_sub_198590_00198590);
    v1 = 0x3F800000;
    mtc1(v1, f1);
    lwc1(f0, v0, 128);
    div_s(f6, f1, f0);
    v1 = 0x960000;
    lwc1(f5, v1, 136);  // g_rwIm2DNearScreenZ
    t1 = 0;
    a3 = s3 & 0x1;
    mtc1(s3, f4);
    a2 = s2 & 0x1;
    mtc1(s2, f3);
    a1 = s1 & 0x1;
    mtc1(s1, f2);
    a0 = s0 & 0x1;
    mtc1(s0, f1);
    for (;;) {
        // 0x003488b8
        charge(ctx, 3);
        v1 = sltiu(t1, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003487e4
        charge(ctx, 5);
        v1 = sll(t1, 6);
        t0 = addu(s4, v1);
        swc1(f6, t0, 24);
        if (i64(s3) < 0) {
            // 0x00348804
            charge(ctx, 6);
            v1 = srl(s3, 1);
            v1 = v1 | a3;
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f0, f0);
        } else {
            // 0x003487f8
            charge(ctx, 3);
            cvt_s_w(f0, f4);
        }
        // 0x0034881c
        charge(ctx, 3);
        swc1(f0, t0, 32);
        if (i64(s2) < 0) {
            // 0x00348834
            charge(ctx, 6);
            v1 = srl(s2, 1);
            v1 = v1 | a2;
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f0, f0);
        } else {
            // 0x00348828
            charge(ctx, 3);
            cvt_s_w(f0, f3);
        }
        // 0x0034884c
        charge(ctx, 3);
        swc1(f0, t0, 36);
        if (i64(s1) < 0) {
            // 0x00348864
            charge(ctx, 6);
            v1 = srl(s1, 1);
            v1 = v1 | a1;
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f0, f0);
        } else {
            // 0x00348858
            charge(ctx, 3);
            cvt_s_w(f0, f2);
        }
        // 0x0034887c
        charge(ctx, 3);
        swc1(f0, t0, 40);
        if (i64(s0) < 0) {
            // 0x00348894
            charge(ctx, 6);
            v1 = srl(s0, 1);
            v1 = v1 | a0;
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f0, f0);
        } else {
            // 0x00348888
            charge(ctx, 3);
            cvt_s_w(f0, f1);
        }
        // 0x003488ac
        charge(ctx, 3);
        swc1(f0, t0, 44);
        swc1(f5, t0, 8);
        t1 = addiu(t1, 1);
    }
    // 0x003488c4
    charge(ctx, 35);
    lwc1(f0, s5, 24);
    swc1(f0, s4, 0);
    lwc1(f0, s5, 28);
    swc1(f0, s4, 4);
    lwc1(f0, s5, 24);
    swc1(f0, s4, 64);
    lwc1(f0, s5, 36);
    swc1(f0, s4, 68);
    lwc1(f0, s5, 32);
    swc1(f0, s4, 128);
    lwc1(f0, s5, 36);
    swc1(f0, s4, 132);
    lwc1(f0, s5, 32);
    swc1(f0, s4, 192);
    lwc1(f0, s5, 28);
    swc1(f0, s4, 196);
    sw(zero, s4, 16);
    sw(zero, s4, 20);
    sw(zero, s4, 80);
    v1 = 0x3F800000;
    sw(v1, s4, 84);
    sw(v1, s4, 144);
    sw(v1, s4, 148);
    sw(v1, s4, 208);
    sw(zero, s4, 212);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00348BD0 sub_348BD0 -- 460 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Builds an untextured screen quad [fltQuadPlain] ($a0 = the class-5 filter output: RGBA, rectangle +8..+20; $a1 =
// the vertices): the four Im2D vertices of a screen quad ($a1 = 4 x 64 bytes): every vertex gets z = the near screen
// z (0x960088), rhw = 1 / the camera's far plane (sub_198590 -> +128) and the RGBA bytes of $a0 +0..+3 as floats; the
// corners from the rectangle. Called by the class-5 draws sub_34ADA0 / sub_34B010.
void sub_348BD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6};
    // 0x00348bd0
    enter(ctx, 33);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    s4 = a1;
    lbu(s3, a0, 0);
    lbu(s2, a0, 1);
    lbu(s1, a0, 2);
    lbu(s0, a0, 3);
    jal(ctx, 0x348C08u, gen::fn_sub_198590_00198590);
    v1 = 0x3F800000;
    mtc1(v1, f1);
    lwc1(f0, v0, 128);
    div_s(f6, f1, f0);
    v1 = 0x960000;
    lwc1(f5, v1, 136);  // g_rwIm2DNearScreenZ
    t1 = 0;
    a3 = s3 & 0x1;
    mtc1(s3, f4);
    a2 = s2 & 0x1;
    mtc1(s2, f3);
    a1 = s1 & 0x1;
    mtc1(s1, f2);
    a0 = s0 & 0x1;
    mtc1(s0, f1);
    for (;;) {
        // 0x00348d28
        charge(ctx, 3);
        v1 = sltiu(t1, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00348c54
        charge(ctx, 5);
        v1 = sll(t1, 6);
        t0 = addu(s4, v1);
        swc1(f6, t0, 24);
        if (i64(s3) < 0) {
            // 0x00348c74
            charge(ctx, 6);
            v1 = srl(s3, 1);
            v1 = v1 | a3;
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f0, f0);
        } else {
            // 0x00348c68
            charge(ctx, 3);
            cvt_s_w(f0, f4);
        }
        // 0x00348c8c
        charge(ctx, 3);
        swc1(f0, t0, 32);
        if (i64(s2) < 0) {
            // 0x00348ca4
            charge(ctx, 6);
            v1 = srl(s2, 1);
            v1 = v1 | a2;
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f0, f0);
        } else {
            // 0x00348c98
            charge(ctx, 3);
            cvt_s_w(f0, f3);
        }
        // 0x00348cbc
        charge(ctx, 3);
        swc1(f0, t0, 36);
        if (i64(s1) < 0) {
            // 0x00348cd4
            charge(ctx, 6);
            v1 = srl(s1, 1);
            v1 = v1 | a1;
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f0, f0);
        } else {
            // 0x00348cc8
            charge(ctx, 3);
            cvt_s_w(f0, f2);
        }
        // 0x00348cec
        charge(ctx, 3);
        swc1(f0, t0, 40);
        if (i64(s0) < 0) {
            // 0x00348d04
            charge(ctx, 6);
            v1 = srl(s0, 1);
            v1 = v1 | a0;
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f0, f0);
        } else {
            // 0x00348cf8
            charge(ctx, 3);
            cvt_s_w(f0, f1);
        }
        // 0x00348d1c
        charge(ctx, 3);
        swc1(f0, t0, 44);
        swc1(f5, t0, 8);
        t1 = addiu(t1, 1);
    }
    // 0x00348d34
    charge(ctx, 26);
    lwc1(f0, s5, 8);
    swc1(f0, s4, 0);
    lwc1(f0, s5, 12);
    swc1(f0, s4, 4);
    lwc1(f0, s5, 8);
    swc1(f0, s4, 64);
    lwc1(f0, s5, 20);
    swc1(f0, s4, 68);
    lwc1(f0, s5, 16);
    swc1(f0, s4, 128);
    lwc1(f0, s5, 20);
    swc1(f0, s4, 132);
    lwc1(f0, s5, 16);
    swc1(f0, s4, 192);
    lwc1(f0, s5, 12);
    swc1(f0, s4, 196);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00348F30 sub_348F30 -- 344 bytes; frame 0x50: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Respawns one sparkle cell of filter kind 3 [fltCellRespawn3] ($a0 = the kind output (+192), $a1 = the 52-byte
// cell): a random delay (sub_357FD0 mod (+4 + 1)), phase -pi (0x7CAEAC), the colour and texture rectangle from the
// output, a position within the output's spread around its centre (sub_358030) and its square rectangle of half size
// +40 / 2.
void sub_348F30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x00348f30
    enter(ctx, 86);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s2 = a0;
    s1 = a1;
    a0 = 0;
    jal(ctx, 0x348F5Cu, gen::fn_sub_357FD0_00357fd0);
    lw(v1, s2, 4);
    v1 = addiu(v1, 1);
    divu(v0, v1);
    mfhi(v0);
    sw(v0, s1, 0);
    lwc1(f0, gp, -32324);  // 0x7CAEAC
    swc1(f0, s1, 4);
    s0 = addiu(s1, 8);
    lw(v0, s2, 16);
    sw(v0, s1, 16);
    lwc1(f0, s2, 20);
    swc1(f0, s1, 20);
    lw(v0, s2, 12);
    sw(v0, s1, 12);
    lwc1(f0, s2, 40);
    cvt_s_w(f1, f0);
    v0 = 0x3F000000;
    mtc1(v0, f0);
    mul_s(f20, f0, f1);
    lwc1(f21, s2, 36);
    a0 = 0;
    jal(ctx, 0x348FBCu, gen::fn_sub_358030_00358030);
    v0 = 0x3F000000;
    mtc1(v0, f1);
    sub_s(f1, f0, f1);
    v0 = 0x40000000;
    mtc1(v0, f0);
    mul_s(f2, f0, f1);
    lwc1(f1, s2, 28);
    mtc1(zero, f0);
    adda_s(f0, f1);
    madd_s(f22, f21, f2);
    a0 = 0;
    jal(ctx, 0x348FFCu, gen::fn_sub_358030_00358030);
    v1 = 0x3F000000;
    mtc1(v1, f1);
    sub_s(f1, f0, f1);
    v1 = 0x40000000;
    mtc1(v1, f0);
    mul_s(f2, f0, f1);
    lwc1(f1, s2, 32);
    mtc1(zero, f0);
    adda_s(f0, f1);
    madd_s(f1, f21, f2);
    swc1(f22, s0, 20);
    swc1(f1, s0, 24);
    sub_s(f0, f22, f20);
    swc1(f0, s0, 28);
    sub_s(f0, f1, f20);
    swc1(f0, s0, 32);
    add_s(f0, f22, f20);
    swc1(f0, s0, 36);
    add_s(f0, f1, f20);
    swc1(f0, s0, 40);
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00349260 sub_349260 -- 496 bytes; frame 0x50: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Respawns one cell of filter kind 7 [fltCellRespawn7] ($a0 = the kind output, $a1 = the 52-byte cell): as sub_348F30
// but the position is random over the screen (810 x 650 minus the cell size) and offset by the output's centre with a
// random angle (cosf / sinf).
void sub_349260(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    // 0x00349260
    enter(ctx, 124);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s2 = a0;
    s1 = a1;
    a0 = 0;
    jal(ctx, 0x349290u, gen::fn_sub_357FD0_00357fd0);
    lw(v1, s2, 4);
    v1 = addiu(v1, 1);
    divu(v0, v1);
    mfhi(v0);
    sw(v0, s1, 0);
    lwc1(f0, gp, -32324);  // 0x7CAEAC
    swc1(f0, s1, 4);
    s0 = addiu(s1, 8);
    lw(v0, s2, 16);
    sw(v0, s1, 16);
    lwc1(f0, s2, 20);
    swc1(f0, s1, 20);
    lw(v0, s2, 12);
    sw(v0, s1, 12);
    lwc1(f0, s2, 40);
    cvt_s_w(f1, f0);
    v0 = 0x3F000000;
    mtc1(v0, f0);
    mul_s(f20, f0, f1);
    a0 = 0;
    jal(ctx, 0x3492ECu, gen::fn_sub_358030_00358030);
    v0 = 0x3F000000;
    mtc1(v0, f1);
    sub_s(f1, f0, f1);
    v0 = 0x40000000;
    mtc1(v0, f0);
    mul_s(f1, f0, f1);
    lwc1(f0, gp, -32408);  // 0x7CAE58
    mul_s(f22, f0, f1);
    lwc1(f21, s2, 48);
    a0 = 0;
    jal(ctx, 0x349324u, gen::fn_sub_358030_00358030);
    v0 = 810;
    mtc1(v0, f1);
    cvt_s_w(f1, f1);
    sub_s(f1, f1, f20);
    sub_s(f2, f1, f21);
    mtc1(zero, f1);
    adda_s(f1, f21);
    madd_s(f1, f2, f0);
    v0 = 0x3F000000;
    mtc1(v0, f0);
    mul_s(f21, f0, f1);
    lwc1(f23, s2, 44);
    a0 = 0;
    jal(ctx, 0x34936Cu, gen::fn_sub_358030_00358030);
    v0 = 650;
    mtc1(v0, f1);
    cvt_s_w(f1, f1);
    sub_s(f1, f1, f20);
    sub_s(f2, f1, f23);
    mtc1(zero, f1);
    adda_s(f1, f23);
    madd_s(f1, f2, f0);
    v0 = 0x3F000000;
    mtc1(v0, f0);
    mula_s(f0, f1);
    lwc1(f1, gp, -32604);  // 0x7CAD94
    mul_s(f0, f1, f20);
    add_s(f21, f21, f0);
    madd_s(f23, f1, f20);
    mov_s(f12, f22);
    jal(ctx, 0x3493C0u, gen::fn_cosf_0052e6d8);
    lwc1(f2, s2, 28);
    mtc1(zero, f1);
    adda_s(f1, f2);
    madd_s(f21, f21, f0);
    mov_s(f12, f22);
    jal(ctx, 0x3493E0u, gen::fn_sinf_0052e878);
    lwc1(f2, s2, 32);
    mtc1(zero, f1);
    adda_s(f1, f2);
    madd_s(f1, f23, f0);
    swc1(f21, s0, 20);
    swc1(f1, s0, 24);
    sub_s(f0, f21, f20);
    swc1(f0, s0, 28);
    sub_s(f0, f1, f20);
    swc1(f0, s0, 32);
    add_s(f0, f21, f20);
    swc1(f0, s0, 36);
    add_s(f0, f1, f20);
    swc1(f0, s0, 40);
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00349450 sub_349450 -- 456 bytes; frame 0x70: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Updates the cells of filter kind 7 [fltCellsUpdate7] ($a0 = the kind output (+0 the cell count, +12 the colour, +24
// pulse depth, +8 phase step), $a1 = the cells, 52 bytes each): a waiting cell counts down with alpha 0; an active
// one respawns when its phase passes pi (0x7CAE58) (sub_349260), its scale pulses with sinf of the phase and its
// alpha is the colour's alpha x (1 - |sin|) in double precision (fptodp / fabs / dpsub / dpmul / dptofp: the
// compiler's soft-double calls), then the phase advances.
void sub_349450(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20};
    // 0x00349450
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s3 = a0;
    s2 = a1;
    lw(s0, a0, 0);
    lw(v1, a0, 12);
    sw(v1, sp, 0x6C);
    lbu(v1, sp, 0x6F);
    if (i64(v1) < 0) {
        // 0x003494a0
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f20, f0);
        add_s(f20, f20, f20);
    } else {
        // 0x0034948c
        charge(ctx, 5);
        mtc1(v1, f0);
        cvt_s_w(f20, f0);
    }
    // 0x003494bc
    charge(ctx, 3);
    s1 = 0;
    for (;;) {
        // 0x003495e8
        charge(ctx, 3);
        v1 = slt(s1, s0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003494c8
        charge(ctx, 3);
        lw(v1, s2, 0);
        if (v1 != 0) {
            // 0x003495d0
            charge(ctx, 4);
            sb(zero, s2, 15);
            lw(v1, s2, 0);
            v1 = addiu(v1, -1);
            sw(v1, s2, 0);
        } else {
            // 0x003494d4
            charge(ctx, 5);
            lwc1(f1, s2, 4);
            lwc1(f0, gp, -32408);  // 0x7CAE58
            c_le_s(f1, f0);
            if (!cond(ctx)) {
                // 0x003494e8
                charge(ctx, 4);
                a0 = s3;
                a1 = s2;
                jal(ctx, 0x3494F0u, gen::fn_sub_349260_00349260);
            }
            // 0x003494f8
            charge(ctx, 35);
            lwc1(f12, s2, 4);
            jal(ctx, 0x3494FCu, gen::fn_sinf_0052e878);
            lwc1(f3, s3, 24);
            v0 = 0x3F800000;
            mtc1(v0, f2);
            mtc1(zero, f1);
            adda_s(f1, f2);
            madd_s(f0, f3, f0);
            swc1(f0, s2, 24);
            lwc1(f12, s2, 4);
            jal(ctx, 0x349528u, gen::fn_fptodp_00530da0);
            a0 = v0;
            jal(ctx, 0x349534u, gen::fn_fabs_0052e118);
            ld(a0, gp, -32752);  // 0x7CAD00
            a1 = v0;
            jal(ctx, 0x349544u, gen::fn_dpsub_005311c8);
            ld(a0, gp, -32744);  // 0x7CAD08
            a1 = v0;
            jal(ctx, 0x349554u, gen::fn_dpmul_00531230);
            a0 = v0;
            jal(ctx, 0x349560u, gen::fn_dptofp_005318a0);
            mul_s(f1, f20, f0);
            v1 = 0x4F000000;
            mtc1(v1, f0);
            c_le_s(f0, f1);
            if (cond(ctx)) {
                // 0x0034959c
                charge(ctx, 6);
                sub_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(a0, f0);
                v1 = lui(0x8000);
                a0 = a0 | v1;
                a0 = a0 & 0xFF;
            } else {
                // 0x00349584
                charge(ctx, 6);
                cvt_w_s(f0, f1);
                mfc1(a0, f0);
                a0 = a0 & 0xFF;
            }
            // 0x003495b4
            charge(ctx, 7);
            sb(a0, s2, 15);
            lwc1(f1, s3, 8);
            lwc1(f0, s2, 4);
            add_s(f0, f0, f1);
            swc1(f0, s2, 4);
        }
        // 0x003495e0
        charge(ctx, 2);
        s2 = addiu(s2, 52);
        s1 = addiu(s1, 1);
    }
    // 0x003495f4
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00349870 sub_349870 -- 440 bytes; frame 0x70: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Screen-filter class 4, kind 1, update [flt4Kind1Update] ($a0 = the filter instance): the frame runs from 0 to the
// duration (+184; 0 holds frame 0); past it the output alpha is cleared. On frame 0 the output rectangle is the whole
// screen (centre 320, 224; 0, 0 .. 640, 448) and the layer word is copied; each frame the colour = filter colour x
// the colour track (sub_32A120) on VU0 into +192, the scale = 1 + k x curve A and the angle = k x curve B
// (sub_32A540, k = 0.01 at 0x7CADA0: the curves are in percent).
void sub_349870(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    Vf vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x00349870
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    lw(s3, a0, 36);
    s0 = addiu(s3, 192);
    lw(s2, s3, kFpDuration);
    if (s2 != 0) {
        // 0x003498b0
        charge(ctx, 1);
        lw(s1, s4, kFltFrame);
    } else {
        // 0x003498a4
        charge(ctx, 3);
        s1 = 0;
    }
    // 0x003498b4
    charge(ctx, 2);
    if (s1 == 0) {
        // 0x003498bc
        charge(ctx, 12);
        v1 = 0x43A00000;
        sw(v1, s0, 16);
        v1 = 0x43600000;
        sw(v1, s0, 20);
        sw(zero, s0, 24);
        sw(zero, s0, 28);
        v1 = 0x44200000;
        sw(v1, s0, 32);
        v1 = 0x43E00000;
        sw(v1, s0, 36);
        lw(v1, s3, kFpLayer);
        sw(v1, s0, 4);
    }
    // 0x003498ec
    charge(ctx, 3);
    v1 = slt(s2, s1);
    if (v1 != 0) {
        // 0x00349a00
        charge(ctx, 1);
        sb(zero, s0, 3);
    } else {
        // 0x003498f8
        charge(ctx, 66);
        a0 = s3;
        a1 = addiu(s3, 36);
        a2 = s1;
        a3 = s2;
        jal(ctx, 0x349908u, gen::fn_sub_32A120_0032a120);
        v1 = v0;
        lw(v0, s4, kFltColour);
        sw(v0, sp, 0x6C);
        v0 = addiu(sp, 0x6C);
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
        sw(v1, sp, 0x68);
        v0 = addiu(sp, 0x68);
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
        sw(v0, sp, 0x64);
        lw(v0, sp, 0x64);
        sw(v0, s0, 0);
        a0 = addiu(s3, 52);
        a1 = s1;
        a2 = s2;
        jal(ctx, 0x3499B0u, gen::fn_sub_32A540_0032a540);
        lwc1(f3, gp, -32592);  // 0x7CADA0
        v0 = 0x3F800000;
        mtc1(v0, f2);
        mtc1(zero, f1);
        adda_s(f1, f2);
        madd_s(f0, f3, f0);
        swc1(f0, s0, 12);
        a0 = addiu(s3, 96);
        a1 = s1;
        a2 = s2;
        jal(ctx, 0x3499E4u, gen::fn_sub_32A540_0032a540);
        lwc1(f1, gp, -32592);  // 0x7CADA0
        mul_s(f0, f1, f0);
        swc1(f0, s0, 8);
    }
    // 0x00349a04 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00349AF0 sub_349AF0 -- 564 bytes; frame 0x80: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Screen-filter class 4, kind 2, update [flt4Kind2Update] ($a0 = the filter instance): the frame runs from 0 to the
// duration (+184; 0 holds frame 0); past it the output alpha is cleared. The size curve (+140) gives the half size;
// the rectangle is centred on the screen centre (centred flag +188) or on the effect position projected by sub_329BA0
// (which also returns the size); colour = filter colour x the colour track (VU0) into +196; scale and angle from
// curves A / B; the layer word copied.
void sub_349AF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12};
    Vf vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x00349af0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    lw(s3, a0, 36);
    s0 = addiu(s3, 192);
    lw(s1, s3, kFpDuration);
    if (s1 != 0) {
        // 0x00349b30
        charge(ctx, 1);
        lw(s2, s4, kFltFrame);
    } else {
        // 0x00349b24
        charge(ctx, 3);
        s2 = 0;
    }
    // 0x00349b34
    charge(ctx, 3);
    v1 = slt(s1, s2);
    if (v1 != 0) {
        // 0x00349cfc
        charge(ctx, 1);
        sb(zero, s0, 7);
    } else {
        // 0x00349b40
        charge(ctx, 8);
        a0 = addiu(s3, 140);
        a1 = s2;
        a2 = s1;
        jal(ctx, 0x349B4Cu, gen::fn_sub_32A540_0032a540);
        lbu(v0, s3, kFpCentred);
        if (v0 == 0) {
            // 0x00349ba0
            charge(ctx, 19);
            lwc1(f1, s4, kFltScale);
            mul_s(f12, f0, f1);
            lqc2(vf10, s4, 0);
            jal(ctx, 0x349BACu, gen::fn_sub_329BA0_00329ba0);
            v0 = addiu(sp, 0x60);
            sqc2(vf10, v0, 0);
            lwc1(f3, sp, 0x60);
            swc1(f3, s0, 20);
            lwc1(f2, sp, 0x64);
            swc1(f2, s0, 24);
            sub_s(f1, f3, f0);
            swc1(f1, s0, 28);
            sub_s(f1, f2, f0);
            swc1(f1, s0, 32);
            add_s(f1, f3, f0);
            swc1(f1, s0, 36);
            add_s(f0, f2, f0);
            swc1(f0, s0, 40);
        } else {
            // 0x00349b60
            charge(ctx, 16);
            v0 = 0x43A00000;
            mtc1(v0, f3);
            sw(v0, s0, 20);
            v0 = 0x43600000;
            mtc1(v0, f2);
            sw(v0, s0, 24);
            sub_s(f1, f3, f0);
            swc1(f1, s0, 28);
            sub_s(f1, f2, f0);
            swc1(f1, s0, 32);
            add_s(f1, f3, f0);
            swc1(f1, s0, 36);
            add_s(f0, f2, f0);
            swc1(f0, s0, 40);
        }
        // 0x00349bec
        charge(ctx, 68);
        a0 = s3;
        a1 = addiu(s3, 36);
        a2 = s2;
        a3 = s1;
        jal(ctx, 0x349BFCu, gen::fn_sub_32A120_0032a120);
        v1 = v0;
        lw(v0, s4, kFltColour);
        sw(v0, sp, 0x7C);
        v0 = addiu(sp, 0x7C);
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
        sw(v1, sp, 0x78);
        v0 = addiu(sp, 0x78);
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
        sw(v0, sp, 0x74);
        lw(v0, sp, 0x74);
        sw(v0, s0, 4);
        a0 = addiu(s3, 52);
        a1 = s2;
        a2 = s1;
        jal(ctx, 0x349CA4u, gen::fn_sub_32A540_0032a540);
        lwc1(f3, gp, -32592);  // 0x7CADA0
        v0 = 0x3F800000;
        mtc1(v0, f2);
        mtc1(zero, f1);
        adda_s(f1, f2);
        madd_s(f0, f3, f0);
        swc1(f0, s0, 16);
        a0 = addiu(s3, 96);
        a1 = s2;
        a2 = s1;
        jal(ctx, 0x349CD8u, gen::fn_sub_32A540_0032a540);
        lwc1(f1, gp, -32592);  // 0x7CADA0
        mul_s(f0, f1, f0);
        swc1(f0, s0, 12);
        lw(v1, s3, kFpLayer);
        sw(v1, s0, 8);
    }
    // 0x00349d00 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x00349ED0 sub_349ED0 -- 196 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Screen-filter class 4, kind 3, create [flt4Kind3Create] ($a0 = the kind parameters; returns the cells): RwMalloc of
// 52 x the cell count (+192); every cell is respawned (sub_348F30) and its phase set to pi + 1 (0x7CAEB0).
void sub_349ED0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x00349ed0
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = addiu(a0, 192);
    lw(s0, a0, 192);
    v0 = sll(s0, 1);
    v0 = addu(v0, s0);
    v0 = sll(v0, 2);
    v0 = addu(v0, s0);
    a0 = sll(v0, 2);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x349F14u, v0.u());
    s2 = v0;
    s3 = 0;
    for (;;) {
        // 0x00349f60
        charge(ctx, 3);
        v0 = slt(s3, s0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00349f2c
        charge(ctx, 13);
        v0 = sll(s3, 1);
        v0 = addu(v0, s3);
        v0 = sll(v0, 2);
        v0 = addu(v0, s3);
        v0 = sll(v0, 2);
        s4 = addu(s2, v0);
        a0 = s1;
        a1 = s4;
        jal(ctx, 0x349F4Cu, gen::fn_sub_348F30_00348f30);
        lwc1(f0, gp, -32320);  // 0x7CAEB0
        swc1(f0, s4, 4);
        s3 = addiu(s3, 1);
    }
    // 0x00349f6c
    charge(ctx, 10);
    v0 = s2;
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00349FA0 sub_349FA0 -- 40 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Screen-filter class 4, kind 3, destroy [flt4Kind3Destroy] ($a0 = the cells): RwFree (0x96017C, a tail call).
void sub_349FA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00349fa0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x349FB0u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0034A1D0 sub_34A1D0 -- 172 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Screen-filter class 4, kind 3, draw [flt4Kind3Draw] ($a0 = the filter instance): with a non-zero output alpha,
// every cell that is not waiting and has alpha (+15) is drawn with the texture of the reference (+40 -> +8) by
// sub_348DA0 (the textured quad draw).
void sub_34A1D0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034a1d0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, 32);
    lw(v1, a0, 36);
    a2 = addiu(v1, 192);
    lw(a1, v1, 204);
    v1 = lui(0xFF00);
    v1 = a1 & v1;
    if (v1 != 0) {
        // 0x0034a208
        charge(ctx, 6);
        lw(v1, a0, 40);
        lw(s0, v1, 8);
        lw(s2, a2, 0);
        s3 = 0;
        for (;;) {
            // 0x0034a250
            charge(ctx, 3);
            v1 = slt(s3, s2);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0034a220
            charge(ctx, 3);
            lw(v1, s1, 0);
            if (v1 == 0) {
                // 0x0034a22c
                charge(ctx, 3);
                lbu(v1, s1, 15);
                if (i64(v1) > 0) {
                    // 0x0034a238
                    charge(ctx, 4);
                    a0 = addiu(s1, 8);
                    a1 = s0;
                    jal(ctx, 0x34A240u, gen::fn_sub_348DA0_00348da0);
                }
            }
            // 0x0034a248
            charge(ctx, 2);
            s1 = addiu(s1, 52);
            s3 = addiu(s3, 1);
        }
    }
    // 0x0034a25c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0034A280 sub_34A280 -- 192 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Screen-filter class 4, kind 4, create [flt4Kind4Create] ($a0 = the kind parameters; returns the cells): RwMalloc of
// 52 x the cell count (+192); each cell starts at phase -(+200 x i) (staggered), position 0, its texture rectangle
// +208 / +212.
void sub_34A280(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x0034a280
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, 192);
    v0 = sll(s0, 1);
    v0 = addu(v0, s0);
    v0 = sll(v0, 2);
    v0 = addu(v0, s0);
    a0 = sll(v0, 2);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x34A2B8u, v0.u());
    a1 = 0;
    for (;;) {
        // 0x0034a31c
        charge(ctx, 3);
        v1 = slt(a1, s0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0034a2cc
        charge(ctx, 20);
        v1 = sll(a1, 1);
        v1 = addu(v1, a1);
        v1 = sll(v1, 2);
        v1 = addu(v1, a1);
        v1 = sll(v1, 2);
        a0 = addu(v0, v1);
        sw(zero, a0, 4);
        sw(zero, a0, 0);
        lw(v1, s1, 208);
        sw(v1, a0, 16);
        lwc1(f0, s1, 212);
        swc1(f0, a0, 20);
        mtc1(a1, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, s1, 200);
        mul_s(f0, f0, f1);
        neg_s(f0, f0);
        swc1(f0, a0, 0);
        a1 = addiu(a1, 1);
    }
    // 0x0034a328
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0034A340 sub_34A340 -- 40 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Screen-filter class 4, kind 4, destroy [flt4Kind4Destroy] ($a0 = the cells): RwFree (a tail call).
void sub_34A340(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034a340
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x34A350u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0034A590 sub_34A590 -- 184 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Screen-filter class 4, kind 4, draw [flt4Kind4Draw] ($a0 = the filter instance): with a non-zero output alpha,
// every cell whose phase has started (>= 0) and has alpha is drawn by sub_348DA0 with the reference's texture.
void sub_34A590(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x0034a590
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, 32);
    lw(v1, a0, 36);
    a2 = addiu(v1, 192);
    lw(a1, v1, 204);
    v1 = lui(0xFF00);
    v1 = a1 & v1;
    if (v1 != 0) {
        // 0x0034a5c8
        charge(ctx, 6);
        lw(v1, a0, 40);
        lw(s0, v1, 8);
        lw(s2, a2, 0);
        s3 = 0;
        for (;;) {
            // 0x0034a61c
            charge(ctx, 3);
            v1 = slt(s3, s2);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0034a5e0
            charge(ctx, 6);
            lwc1(f1, s1, 0);
            mtc1(zero, f0);
            c_lt_s(f1, f0);
            if (!cond(ctx)) {
                // 0x0034a5f8
                charge(ctx, 3);
                lbu(v1, s1, 15);
                if (i64(v1) > 0) {
                    // 0x0034a604
                    charge(ctx, 4);
                    a0 = addiu(s1, 8);
                    a1 = s0;
                    jal(ctx, 0x34A60Cu, gen::fn_sub_348DA0_00348da0);
                }
            }
            // 0x0034a614
            charge(ctx, 2);
            s1 = addiu(s1, 52);
            s3 = addiu(s3, 1);
        }
    }
    // 0x0034a628 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0034A8C0 sub_34A8C0 -- 196 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Screen-filter class 4, kind 7, create [flt4Kind7Create] ($a0 = the kind parameters; returns the cells): as
// sub_349ED0 with the kind-7 respawn sub_349260.
void sub_34A8C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x0034a8c0
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = addiu(a0, 192);
    lw(s0, a0, 192);
    v0 = sll(s0, 1);
    v0 = addu(v0, s0);
    v0 = sll(v0, 2);
    v0 = addu(v0, s0);
    a0 = sll(v0, 2);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x34A904u, v0.u());
    s2 = v0;
    s3 = 0;
    for (;;) {
        // 0x0034a950
        charge(ctx, 3);
        v0 = slt(s3, s0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0034a91c
        charge(ctx, 13);
        v0 = sll(s3, 1);
        v0 = addu(v0, s3);
        v0 = sll(v0, 2);
        v0 = addu(v0, s3);
        v0 = sll(v0, 2);
        s4 = addu(s2, v0);
        a0 = s1;
        a1 = s4;
        jal(ctx, 0x34A93Cu, gen::fn_sub_349260_00349260);
        lwc1(f0, gp, -32320);  // 0x7CAEB0
        swc1(f0, s4, 4);
        s3 = addiu(s3, 1);
    }
    // 0x0034a95c
    charge(ctx, 10);
    v0 = s2;
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0034A990 sub_34A990 -- 40 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Screen-filter class 4, kind 7, destroy [flt4Kind7Destroy] ($a0 = the cells): RwFree (a tail call).
void sub_34A990(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034a990
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x34A9A0u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0034A9C0 sub_34A9C0 -- 508 bytes; frame 0x90: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Screen-filter class 4, kind 7, update [flt4Kind7Update] ($a0 = the filter instance): the frame runs from 0 to the
// duration (+184; 0 holds frame 0); past it the output alpha is cleared. The size curve and the centre (screen centre
// or sub_329BA0), colour = filter colour x the colour track on VU0, scale / angle from curves A / B, the layer word;
// then the cells run (sub_349450).
void sub_34A9C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    Vf vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x0034a9c0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    lw(s5, a0, 32);
    lw(s3, a0, 36);
    s2 = addiu(s3, 192);
    lw(s0, s3, 184);
    if (s0 != 0) {
        // 0x0034aa08
        charge(ctx, 1);
        lw(s1, s4, 28);
    } else {
        // 0x0034a9fc
        charge(ctx, 3);
        s1 = 0;
    }
    // 0x0034aa0c
    charge(ctx, 3);
    v1 = slt(s0, s1);
    if (v1 != 0) {
        // 0x0034ab90
        charge(ctx, 1);
        sw(zero, s2, 12);
    } else {
        // 0x0034aa18
        charge(ctx, 8);
        a0 = addiu(s3, 140);
        a1 = s1;
        a2 = s0;
        jal(ctx, 0x34AA24u, gen::fn_sub_32A540_0032a540);
        lbu(v0, s3, 188);
        if (v0 == 0) {
            // 0x0034aa54
            charge(ctx, 12);
            lwc1(f1, s4, 20);
            mul_s(f12, f0, f1);
            lqc2(vf10, s4, 0);
            jal(ctx, 0x34AA60u, gen::fn_sub_329BA0_00329ba0);
            swc1(f0, s2, 36);
            v0 = addiu(sp, 0x70);
            sqc2(vf10, v0, 0);
            lwc1(f0, sp, 0x70);
            swc1(f0, s2, 28);
            lwc1(f0, sp, 0x74);
            swc1(f0, s2, 32);
        } else {
            // 0x0034aa38
            charge(ctx, 7);
            v0 = 0x43A00000;
            sw(v0, s2, 28);
            v0 = 0x43600000;
            sw(v0, s2, 32);
            swc1(f0, s2, 36);
        }
        // 0x0034aa84
        charge(ctx, 67);
        a0 = s3;
        a1 = addiu(s3, 36);
        a2 = s1;
        a3 = s0;
        jal(ctx, 0x34AA94u, gen::fn_sub_32A120_0032a120);
        v1 = v0;
        lw(v0, s4, 16);
        sw(v0, sp, 0x8C);
        v0 = addiu(sp, 0x8C);
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
        sw(v1, sp, 0x88);
        v0 = addiu(sp, 0x88);
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
        sw(v0, sp, 0x84);
        lw(v0, sp, 0x84);
        sw(v0, s2, 12);
        a0 = addiu(s3, 52);
        a1 = s1;
        a2 = s0;
        jal(ctx, 0x34AB3Cu, gen::fn_sub_32A540_0032a540);
        lwc1(f1, gp, -32592);  // 0x7CADA0
        mul_s(f0, f1, f0);
        swc1(f0, s2, 24);
        a0 = addiu(s3, 96);
        a1 = s1;
        a2 = s0;
        jal(ctx, 0x34AB5Cu, gen::fn_sub_32A540_0032a540);
        lwc1(f1, gp, -32592);  // 0x7CADA0
        mul_s(f0, f1, f0);
        swc1(f0, s2, 20);
        lw(v0, s3, 40);
        sw(v0, s2, 16);
        a0 = s2;
        a1 = s5;
        jal(ctx, 0x34AB80u, gen::fn_sub_349450_00349450);
    }
    // 0x0034ab94 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x0034ABC0 sub_34ABC0 -- 172 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Screen-filter class 4, kind 7, draw [flt4Kind7Draw] ($a0 = the filter instance): as sub_34A1D0 (cells not waiting,
// with alpha, drawn by sub_348DA0 with the reference's texture).
void sub_34ABC0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034abc0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, 32);
    lw(v1, a0, 36);
    a2 = addiu(v1, 192);
    lw(a1, v1, 204);
    v1 = lui(0xFF00);
    v1 = a1 & v1;
    if (v1 != 0) {
        // 0x0034abf8
        charge(ctx, 6);
        lw(v1, a0, 40);
        lw(s0, v1, 8);
        lw(s2, a2, 0);
        s3 = 0;
        for (;;) {
            // 0x0034ac40
            charge(ctx, 3);
            v1 = slt(s3, s2);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0034ac10
            charge(ctx, 3);
            lw(v1, s1, 0);
            if (v1 == 0) {
                // 0x0034ac1c
                charge(ctx, 3);
                lbu(v1, s1, 15);
                if (i64(v1) > 0) {
                    // 0x0034ac28
                    charge(ctx, 4);
                    a0 = addiu(s1, 8);
                    a1 = s0;
                    jal(ctx, 0x34AC30u, gen::fn_sub_348DA0_00348da0);
                }
            }
            // 0x0034ac38
            charge(ctx, 2);
            s1 = addiu(s1, 52);
            s3 = addiu(s3, 1);
        }
    }
    // 0x0034ac4c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0034AC70 sub_34AC70 -- 304 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Screen-filter class 5, kind 1, update [flt5Kind1Update] ($a0 = the filter instance): the frame runs from 0 to the
// duration (+184; 0 holds frame 0); past it the output alpha is cleared. On frame 0 the rectangle is the whole screen
// (0, 0 .. 640, 448) and the layer word copied; each frame the colour = filter colour x the colour track (sub_32A120)
// on VU0 into +192.
void sub_34AC70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    Vf vf2{ctx, 2}, vf10{ctx, 10}, vf11{ctx, 11};
    // 0x0034ac70
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(a0, a0, 36);
    s0 = addiu(a0, 192);
    lw(a3, a0, 184);
    if (a3 != 0) {
        // 0x0034aca4
        charge(ctx, 1);
        lw(a2, s1, 28);
    } else {
        // 0x0034ac98
        charge(ctx, 3);
        a2 = 0;
    }
    // 0x0034aca8
    charge(ctx, 2);
    if (a2 == 0) {
        // 0x0034acb0
        charge(ctx, 8);
        sw(zero, s0, 8);
        sw(zero, s0, 12);
        v1 = 0x44200000;
        sw(v1, s0, 16);
        v1 = 0x43E00000;
        sw(v1, s0, 20);
        lw(v1, a0, 40);
        sw(v1, s0, 4);
    }
    // 0x0034acd0
    charge(ctx, 3);
    v1 = slt(a3, a2);
    if (v1 != 0) {
        // 0x0034ad84
        charge(ctx, 1);
        sb(zero, s0, 3);
    } else {
        // 0x0034acdc
        charge(ctx, 42);
        a1 = addiu(a0, 36);
        jal(ctx, 0x34ACE0u, gen::fn_sub_32A120_0032a120);
        v1 = v0;
        lw(v0, s1, 16);
        sw(v0, sp, 0x3C);
        v0 = addiu(sp, 0x3C);
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
        sw(v1, sp, 0x38);
        v0 = addiu(sp, 0x38);
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
        sw(v1, sp, 0x34);
        lw(v1, sp, 0x34);
        sw(v1, s0, 0);
    }
    // 0x0034ad88 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0034B1A0 sub_34B1A0 -- 380 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Screen-filter class 4, slot 0 [fltCreate4] ($a0 = the effect record; returns the instance; block A from sub_3245B0,
// the kind +12): a cleared block of 48 + the kind's parameter size (row +20): kind, colour -1, scale 1.0, frame and
// texture 0, the vector +0 cleared, the parameters copied to +48 (+36); the row's create (+0, jalr) makes the kind
// object (+32) when the kind has one (with the parameters); when block B is present and the kind uses a texture (row
// +16) the texture reference comes from sub_34BBC0 with block B's type (+28).
void sub_34B1A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    Vf vf0{ctx, 0};
    // 0x0034b1a0
    enter(ctx, 59);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    jal(ctx, 0x34B1C8u, gen::fn_sub_3245B0_003245b0);
    s4 = v0;
    lhu(s0, s5, 12);
    s6 = 48;
    v0 = sll(s0, 1);
    v0 = addu(v0, s0);
    v1 = sll(v0, 3);
    v0 = 0x6A0000;
    v0 = addiu(v0, -13404);  // &0x69CBA4
    v0 = addu(v0, v1);
    lw(s2, v0, 0);
    s1 = addiu(s2, 48);
    a0 = s1;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x34B20Cu, v0.u());
    s3 = v0;
    a0 = s3;
    a1 = 0;
    a2 = s1;
    jal(ctx, 0x34B224u, gen::fn_memset_00521408);
    sw(s0, s3, kFltKind);
    v0 = si(-1);
    sw(v0, s3, kFltColour);
    v0 = 0x3F800000;
    sw(v0, s3, kFltScale);
    sw(zero, s3, kFltTexRef);
    sw(zero, s3, 44);
    sqc2(vf0, s3, 0);
    a0 = addu(s3, s6);
    sw(a0, s3, kFltParams);
    a1 = s4;
    a2 = s2;
    jal(ctx, 0x34B25Cu, gen::fn_memcpy_00521250);
    v1 = s0 & 0xFFFF;
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v1 = sll(v0, 3);
    v0 = 0x6A0000;
    v0 = addiu(v0, -13424);  // &0x69CB90
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    if (v0 != 0) {
        // 0x0034b28c
        charge(ctx, 4);
        lw(a0, s3, kFltParams);
        jalr(ctx, 0x34B290u, v0.u());
        sw(v0, s3, kFltObj);
    }
    // 0x0034b29c
    charge(ctx, 5);
    a0 = s5;
    jal(ctx, 0x34B2A0u, gen::fn_sub_3245F0_003245f0);
    if (v0 != 0) {
        // 0x0034b2b0
        charge(ctx, 10);
        lw(a0, s3, kFltKind);
        v1 = sll(a0, 1);
        v1 = addu(v1, a0);
        a0 = sll(v1, 3);
        v1 = 0x6A0000;
        v1 = addiu(v1, -13408);  // &0x69CBA0
        v1 = addu(v1, a0);
        lb(v1, v1, 0);
        if (v1 != 0) {
            // 0x0034b2d8
            charge(ctx, 5);
            a0 = v0;
            lhu(a1, s5, 28);
            jal(ctx, 0x34B2E0u, gen::fn_sub_34BBC0_0034bbc0);
            sw(v0, s3, kFltTexRef);
        }
    }
    // 0x0034b2ec (the shared epilogue, written out on this path)
    charge(ctx, 12);
    v0 = s3;
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

// 0x0034B320 sub_34B320 -- 128 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Screen-filter class 4, slot 4 [fltDestroy4] ($a0 = the instance): the kind's destroy (row +4) on the kind object
// when there is one, the texture reference released (sub_34BC80), the instance freed.
void sub_34B320(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034b320
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, 32);
    if (a0 != 0) {
        // 0x0034b33c
        charge(ctx, 10);
        lw(v1, s0, kFltKind);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v1 = sll(v0, 3);
        v0 = 0x6A0000;
        v0 = addiu(v0, -13420);  // &0x69CB94
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        jalr(ctx, 0x34B35Cu, v0.u());
    }
    // 0x0034b364
    charge(ctx, 3);
    lw(a0, s0, kFltTexRef);
    if (a0 != 0) {
        // 0x0034b370
        charge(ctx, 2);
        jal(ctx, 0x34B370u, gen::fn_sub_34BC80_0034bc80);
    }
    // 0x0034b378
    charge(ctx, 10);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x34B384u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0034B3A0 sub_34B3A0 -- 356 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Screen-filter class 4, slot 5 [fltClone4] ($a0 = the source; returns the copy): a cleared block of 48 + the kind's
// parameter size (row +20): kind, colour -1, scale 1.0, frame and texture 0, the vector +0 cleared, the parameters
// copied to +48 (+36); the row's create (+0, jalr) makes the kind object (+32) when the kind has one (from the
// source's kind and parameters); a source texture reference is shared (sub_34BCF0 [fxRefInc]).
void sub_34B3A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    Vf vf0{ctx, 0};
    // 0x0034b3a0
    enter(ctx, 57);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    lw(s4, a0, 36);
    lhu(s0, a0, 24);
    s6 = 48;
    v0 = sll(s0, 1);
    v0 = addu(v0, s0);
    v1 = sll(v0, 3);
    v0 = 0x6A0000;
    v0 = addiu(v0, -13404);  // &0x69CBA4
    v0 = addu(v0, v1);
    lw(s2, v0, 0);
    s1 = addiu(s2, 48);
    a0 = s1;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x34B404u, v0.u());
    s3 = v0;
    a0 = s3;
    a1 = 0;
    a2 = s1;
    jal(ctx, 0x34B41Cu, gen::fn_memset_00521408);
    sw(s0, s3, kFltKind);
    v0 = si(-1);
    sw(v0, s3, kFltColour);
    v0 = 0x3F800000;
    sw(v0, s3, kFltScale);
    sw(zero, s3, kFltTexRef);
    sw(zero, s3, 44);
    sqc2(vf0, s3, 0);
    a0 = addu(s3, s6);
    sw(a0, s3, kFltParams);
    a1 = s4;
    a2 = s2;
    jal(ctx, 0x34B454u, gen::fn_memcpy_00521250);
    v1 = s0 & 0xFFFF;
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v1 = sll(v0, 3);
    v0 = 0x6A0000;
    v0 = addiu(v0, -13424);  // &0x69CB90
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    if (v0 != 0) {
        // 0x0034b484
        charge(ctx, 4);
        lw(a0, s3, kFltParams);
        jalr(ctx, 0x34B488u, v0.u());
        sw(v0, s3, kFltObj);
    }
    // 0x0034b494
    charge(ctx, 3);
    lw(a0, s5, 40);
    if (a0 != 0) {
        // 0x0034b4a0
        charge(ctx, 10);
        lw(v1, s3, kFltKind);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v1 = sll(v0, 3);
        v0 = 0x6A0000;
        v0 = addiu(v0, -13408);  // &0x69CBA0
        v0 = addu(v0, v1);
        lb(v0, v0, 0);
        if (v0 != 0) {
            // 0x0034b4c8
            charge(ctx, 3);
            jal(ctx, 0x34B4C8u, gen::fn_sub_34BCF0_0034bcf0);
            sw(v0, s3, kFltTexRef);
        }
    }
    // 0x0034b4d4 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    v0 = s3;
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

// 0x0034B600 sub_34B600 -- 116 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Screen-filter class 4, slot 1 [fltUpdate4] ($a0 = the instance): the kind's update (row +8), ++frame (+28), and
// from the first frame on the instance is queued on the filter layer of the parameters' word +40 (sub_321180).
void sub_34B600(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034b600
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, a0, 24);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v1 = sll(v0, 3);
    v0 = 0x6A0000;
    v0 = addiu(v0, -13416);  // &0x69CB98
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    jalr(ctx, 0x34B630u, v0.u());
    lw(v1, s0, kFltFrame);
    v1 = addiu(v1, 1);
    sw(v1, s0, kFltFrame);
    if (i64(v1) > 0) {
        // 0x0034b64c
        charge(ctx, 5);
        lw(v0, s0, kFltParams);
        lhu(a1, v0, 40);
        a0 = s0;
        jal(ctx, 0x34B658u, gen::fn_sub_321180_00321180);
    }
    // 0x0034b660 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0034B6B0 sub_34B6B0 -- 380 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Screen-filter class 5, slot 0 [fltCreate5]: as sub_34B1A0 with the class-5 kind table 0x69CC50; the row's create
// receives block A itself.
void sub_34B6B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    Vf vf0{ctx, 0};
    // 0x0034b6b0
    enter(ctx, 59);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    jal(ctx, 0x34B6D8u, gen::fn_sub_3245B0_003245b0);
    s4 = v0;
    lhu(s0, s5, 12);
    s6 = 48;
    v0 = sll(s0, 1);
    v0 = addu(v0, s0);
    v1 = sll(v0, 3);
    v0 = 0x6A0000;
    v0 = addiu(v0, -13212);  // &0x69CC64
    v0 = addu(v0, v1);
    lw(s2, v0, 0);
    s1 = addiu(s2, 48);
    a0 = s1;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x34B71Cu, v0.u());
    s3 = v0;
    a0 = s3;
    a1 = 0;
    a2 = s1;
    jal(ctx, 0x34B734u, gen::fn_memset_00521408);
    sw(s0, s3, kFltKind);
    v0 = si(-1);
    sw(v0, s3, kFltColour);
    v0 = 0x3F800000;
    sw(v0, s3, kFltScale);
    sw(zero, s3, kFltTexRef);
    sw(zero, s3, 44);
    sqc2(vf0, s3, 0);
    a0 = addu(s3, s6);
    sw(a0, s3, kFltParams);
    a1 = s4;
    a2 = s2;
    jal(ctx, 0x34B76Cu, gen::fn_memcpy_00521250);
    v1 = s0 & 0xFFFF;
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v1 = sll(v0, 3);
    v0 = 0x6A0000;
    v0 = addiu(v0, -13232);  // &0x69CC50
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    if (v0 != 0) {
        // 0x0034b79c
        charge(ctx, 4);
        a0 = s4;
        jalr(ctx, 0x34B7A0u, v0.u());
        sw(v0, s3, kFltObj);
    }
    // 0x0034b7ac
    charge(ctx, 5);
    a0 = s5;
    jal(ctx, 0x34B7B0u, gen::fn_sub_3245F0_003245f0);
    if (v0 != 0) {
        // 0x0034b7c0
        charge(ctx, 10);
        lw(a0, s3, kFltKind);
        v1 = sll(a0, 1);
        v1 = addu(v1, a0);
        a0 = sll(v1, 3);
        v1 = 0x6A0000;
        v1 = addiu(v1, -13216);  // &0x69CC60
        v1 = addu(v1, a0);
        lb(v1, v1, 0);
        if (v1 != 0) {
            // 0x0034b7e8
            charge(ctx, 5);
            a0 = v0;
            lhu(a1, s5, 28);
            jal(ctx, 0x34B7F0u, gen::fn_sub_34BBC0_0034bbc0);
            sw(v0, s3, kFltTexRef);
        }
    }
    // 0x0034b7fc (the shared epilogue, written out on this path)
    charge(ctx, 12);
    v0 = s3;
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

// 0x0034B830 sub_34B830 -- 128 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Screen-filter class 5, slot 4 [fltDestroy5]: as sub_34B320 with the table 0x69CC50.
void sub_34B830(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034b830
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, 32);
    if (a0 != 0) {
        // 0x0034b84c
        charge(ctx, 10);
        lw(v1, s0, kFltKind);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v1 = sll(v0, 3);
        v0 = 0x6A0000;
        v0 = addiu(v0, -13228);  // &0x69CC54
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        jalr(ctx, 0x34B86Cu, v0.u());
    }
    // 0x0034b874
    charge(ctx, 3);
    lw(a0, s0, kFltTexRef);
    if (a0 != 0) {
        // 0x0034b880
        charge(ctx, 2);
        jal(ctx, 0x34B880u, gen::fn_sub_34BC80_0034bc80);
    }
    // 0x0034b888
    charge(ctx, 10);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x34B894u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0034B8B0 sub_34B8B0 -- 356 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Screen-filter class 5, slot 5 [fltClone5]: as sub_34B3A0 with the table 0x69CC50 (the row's create receives the
// source's parameters pointer).
void sub_34B8B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    Vf vf0{ctx, 0};
    // 0x0034b8b0
    enter(ctx, 57);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    lw(s4, a0, 36);
    lhu(s0, a0, 24);
    s6 = 48;
    v0 = sll(s0, 1);
    v0 = addu(v0, s0);
    v1 = sll(v0, 3);
    v0 = 0x6A0000;
    v0 = addiu(v0, -13212);  // &0x69CC64
    v0 = addu(v0, v1);
    lw(s2, v0, 0);
    s1 = addiu(s2, 48);
    a0 = s1;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x34B914u, v0.u());
    s3 = v0;
    a0 = s3;
    a1 = 0;
    a2 = s1;
    jal(ctx, 0x34B92Cu, gen::fn_memset_00521408);
    sw(s0, s3, kFltKind);
    v0 = si(-1);
    sw(v0, s3, kFltColour);
    v0 = 0x3F800000;
    sw(v0, s3, kFltScale);
    sw(zero, s3, kFltTexRef);
    sw(zero, s3, 44);
    sqc2(vf0, s3, 0);
    a0 = addu(s3, s6);
    sw(a0, s3, kFltParams);
    a1 = s4;
    a2 = s2;
    jal(ctx, 0x34B964u, gen::fn_memcpy_00521250);
    v1 = s0 & 0xFFFF;
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v1 = sll(v0, 3);
    v0 = 0x6A0000;
    v0 = addiu(v0, -13232);  // &0x69CC50
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    if (v0 != 0) {
        // 0x0034b994
        charge(ctx, 4);
        a0 = s4;
        jalr(ctx, 0x34B998u, v0.u());
        sw(v0, s3, kFltObj);
    }
    // 0x0034b9a4
    charge(ctx, 3);
    lw(a0, s5, 40);
    if (a0 != 0) {
        // 0x0034b9b0
        charge(ctx, 10);
        lw(v1, s3, kFltKind);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v1 = sll(v0, 3);
        v0 = 0x6A0000;
        v0 = addiu(v0, -13216);  // &0x69CC60
        v0 = addu(v0, v1);
        lb(v0, v0, 0);
        if (v0 != 0) {
            // 0x0034b9d8
            charge(ctx, 3);
            jal(ctx, 0x34B9D8u, gen::fn_sub_34BCF0_0034bcf0);
            sw(v0, s3, kFltTexRef);
        }
    }
    // 0x0034b9e4 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    v0 = s3;
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

// 0x0034BB10 sub_34BB10 -- 116 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Screen-filter class 5, slot 1 [fltUpdate5]: as sub_34B600 with the table 0x69CC50 and the layer queue sub_3211D0.
void sub_34BB10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034bb10
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, a0, 24);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v1 = sll(v0, 3);
    v0 = 0x6A0000;
    v0 = addiu(v0, -13224);  // &0x69CC58
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    jalr(ctx, 0x34BB40u, v0.u());
    lw(v1, s0, kFltFrame);
    v1 = addiu(v1, 1);
    sw(v1, s0, kFltFrame);
    if (i64(v1) > 0) {
        // 0x0034bb5c
        charge(ctx, 5);
        lw(v0, s0, kFltParams);
        lhu(a1, v0, 40);
        a0 = s0;
        jal(ctx, 0x34BB68u, gen::fn_sub_3211D0_003211d0);
    }
    // 0x0034bb70 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0034BBC0 sub_34BBC0 -- 192 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Creates a texture reference [fltTexRefCreate] ($a0 = block B, $a1 = its type; returns the 12-byte reference): type,
// count 1 and the texture: type 4 the manager's texture of the u16 index (sub_3210A0), type 1 a texture by name
// (sub_3210C0); other types leave it 0.
void sub_34BBC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034bbc0
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s2 = a1;
    a0 = 12;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x34BBECu, v0.u());
    s1 = v0;
    a0 = s1;
    a1 = 0;
    a2 = 12;
    jal(ctx, 0x34BC04u, gen::fn_memset_00521408);
    a0 = s2 & 0xFFFF;
    sw(a0, s1, 0);
    v1 = 1;
    sw(v1, s1, 4);
    v0 = 4;
    if (a0 == v0) {
        // 0x0034bc50
        charge(ctx, 4);
        lhu(a0, s0, 0);
        jal(ctx, 0x34BC54u, gen::fn_sub_3210A0_003210a0);
        sw(v0, s1, 8);
    } else {
        // 0x0034bc28
        charge(ctx, 2);
        if (a0 == v1) {
            // 0x0034bc38
            charge(ctx, 6);
            a0 = s0;
            jal(ctx, 0x34BC3Cu, gen::fn_sub_3210C0_003210c0);
            sw(v0, s1, 8);
        } else {
            // 0x0034bc30
            charge(ctx, 2);
        }
    }
    // 0x0034bc60 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = s1;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0034BC80 sub_34BC80 -- 104 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Releases a texture reference [fltTexRefRelease] ($a0 = the reference): --count; at 0 the texture is destroyed
// (RwTextureDestroy sub_4D0F00) unless it is a manager texture (type 4) and the reference freed.
void sub_34BC80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034bc80
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, a0, 4);
    v1 = addiu(v1, -1);
    sw(v1, a0, 4);
    if (v1 == 0) {
        // 0x0034bca4
        charge(ctx, 4);
        lw(v1, s0, 0);
        v0 = 4;
        if (v1 != v0) {
            // 0x0034bcb4
            charge(ctx, 3);
            lw(a0, s0, 8);
            jal(ctx, 0x34BCB8u, gen::fn_sub_4D0F00_004d0f00);
        }
        // 0x0034bcc0
        charge(ctx, 5);
        a0 = s0;
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x34BCCCu, v0.u());
    }
    // 0x0034bcd4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0034BD60 sub_34BD60 -- 132 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Resets a model's animation [eplModelReset] ($a0 = the model): sub_318B10 (frame update), and when the model has
// animation 0 (sub_3185B0) it is started at time 0 (sub_3182D0(model, 0, 0, 0, 0)) and applied (sub_3189F0); the flag
// bit 2 of +216 is cleared.
void sub_34BD60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x0034bd60
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x34BD70u, gen::fn_sub_318B10_00318b10);
    a0 = s0;
    a1 = 0;
    jal(ctx, 0x34BD80u, gen::fn_sub_3185B0_003185b0);
    if (v0 != 0) {
        // 0x0034bd90
        charge(ctx, 13);
        a0 = s0;
        a1 = 0;
        a2 = 0;
        a3 = 0;
        t0 = 0;
        jal(ctx, 0x34BDA4u, gen::fn_sub_3182D0_003182d0);
        v0 = 0x3F800000;
        mtc1(v0, f12);
        a0 = s0;
        a1 = 0;
        jal(ctx, 0x34BDBCu, gen::fn_sub_3189F0_003189f0);
    }
    // 0x0034bdc4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lhu(v1, s0, 216);
    v1 = v1 & 0xFFFD;
    sh(v1, s0, 216);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0034BDF0 sub_34BDF0 -- 244 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Creates an effect model [eplModelCreate] ($a0 / $a1 = the model data and size; returns the model): the first free
// id of group 6 from the counter gp-18368 (sub_316910 says taken), the model made by sub_316BD0(6, id, data, size,
// 1), then reset as sub_34BD60 does and the counter advanced. Callers: sub_34C670 and the other EPL players
// (sub_352E10, sub_355DD0, ...).
void sub_34BDF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x0034bdf0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    for (;;) {
        // 0x0034be1c
        charge(ctx, 7);
        a0 = 6;
        lhu(a1, gp, -18304);  // 0x7CE570
        a2 = 0;
        jal(ctx, 0x34BE28u, gen::fn_sub_316910_00316910);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0034be10
        charge(ctx, 3);
        lhu(v0, gp, -18304);  // 0x7CE570
        v0 = addiu(v0, 1);
        sh(v0, gp, -18304);  // 0x7CE570
    }
    // 0x0034be38
    charge(ctx, 17);
    a0 = 6;
    lhu(a1, gp, -18304);  // 0x7CE570
    a2 = s1;
    a3 = s0;
    t0 = 1;
    jal(ctx, 0x34BE4Cu, gen::fn_sub_316BD0_00316bd0);
    s0 = v0;
    a0 = s0;
    jal(ctx, 0x34BE5Cu, gen::fn_sub_318B10_00318b10);
    a0 = s0;
    a1 = 0;
    jal(ctx, 0x34BE6Cu, gen::fn_sub_3185B0_003185b0);
    if (v0 != 0) {
        // 0x0034be7c
        charge(ctx, 13);
        a0 = s0;
        a1 = 0;
        a2 = 0;
        a3 = 0;
        t0 = 0;
        jal(ctx, 0x34BE90u, gen::fn_sub_3182D0_003182d0);
        v0 = 0x3F800000;
        mtc1(v0, f12);
        a0 = s0;
        a1 = 0;
        jal(ctx, 0x34BEA8u, gen::fn_sub_3189F0_003189f0);
    }
    // 0x0034beb0 (the shared epilogue, written out on this path)
    charge(ctx, 13);
    lhu(v0, s0, 216);
    v0 = v0 & 0xFFFD;
    sh(v0, s0, 216);
    lhu(v0, gp, -18304);  // 0x7CE570
    v0 = addiu(v0, 1);
    sh(v0, gp, -18304);  // 0x7CE570
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0034BEF0 sub_34BEF0 -- 32 bytes; frame 0x10: ra sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Destroys an effect model [eplModelDestroy] ($a0 = the model): a tail call of sub_3174E0.
void sub_34BEF0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0034bef0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x34BEF8u, gen::fn_sub_3174E0_003174e0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0034BF10 sub_34BF10 -- 164 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Creates a model like another [eplModelCopy] ($a0 = the source model; returns the new one): sub_316E00 with the
// source's ids (+212, +214) and flag 1, then reset as sub_34BD60 does.
void sub_34BF10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x0034bf10
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    v0 = a0;
    lhu(a0, a0, 212);
    lhu(a1, v0, 214);
    a2 = 1;
    jal(ctx, 0x34BF2Cu, gen::fn_sub_316E00_00316e00);
    s0 = v0;
    a0 = s0;
    jal(ctx, 0x34BF3Cu, gen::fn_sub_318B10_00318b10);
    a0 = s0;
    a1 = 0;
    jal(ctx, 0x34BF4Cu, gen::fn_sub_3185B0_003185b0);
    if (v0 != 0) {
        // 0x0034bf5c
        charge(ctx, 13);
        a0 = s0;
        a1 = 0;
        a2 = 0;
        a3 = 0;
        t0 = 0;
        jal(ctx, 0x34BF70u, gen::fn_sub_3182D0_003182d0);
        v0 = 0x3F800000;
        mtc1(v0, f12);
        a0 = s0;
        a1 = 0;
        jal(ctx, 0x34BF88u, gen::fn_sub_3189F0_003189f0);
    }
    // 0x0034bf90 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lhu(v0, s0, 216);
    v0 = v0 & 0xFFFD;
    sh(v0, s0, 216);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0034BFC0 sub_34BFC0 -- 404 bytes; frame 0x50: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Effect class 26 = fx_epl's kind 1 (EPL row 0x69C368), slot 0 [eplModelObjCreate] ($a0 = the effect record, or 0;
// returns the object): a cleared 160-byte block, age 0, colour -1, scale 1.0, position / rotation 0; with a record
// the 104-byte block A copy (+44) and, when block B exists, a model of group 6 made from it (the body of sub_34BDF0
// inline, with the record's +36 as the size) into +148.
void sub_34BFC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f20{ctx, 20};
    Vf vf0{ctx, 0};
    // 0x0034bfc0
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s2 = a0;
    a0 = 160;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x34BFECu, v0.u());
    s1 = v0;
    a0 = s1;
    a1 = 0;
    a2 = 160;
    jal(ctx, 0x34C004u, gen::fn_memset_00521408);
    sw(zero, s1, kE1Age);
    v0 = si(-1);
    sw(v0, s1, kE1Colour);
    v0 = 0x3F800000;
    mtc1(v0, f20);
    sw(v0, s1, kE1Scale);
    sqc2(vf0, s1, 0);
    sqc2(vf0, s1, 16);
    if (s2 != 0) {
        // 0x0034c034
        charge(ctx, 14);
        a0 = s2;
        jal(ctx, 0x34C038u, gen::fn_sub_3245B0_003245b0);
        a0 = addiu(s1, 44);
        a1 = v0;
        a2 = 104;
        jal(ctx, 0x34C04Cu, gen::fn_memcpy_00521250);
        a0 = s2;
        jal(ctx, 0x34C058u, gen::fn_sub_3245F0_003245f0);
        s0 = v0;
        if (s0 != 0) {
            // 0x0034c06c
            charge(ctx, 3);
            lw(s2, s2, 36);
            for (;;) {
                // 0x0034c084
                charge(ctx, 7);
                a0 = 6;
                lhu(a1, gp, -18304);  // 0x7CE570
                a2 = 0;
                jal(ctx, 0x34C090u, gen::fn_sub_316910_00316910);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0034c078
                charge(ctx, 3);
                lhu(v0, gp, -18304);  // 0x7CE570
                v0 = addiu(v0, 1);
                sh(v0, gp, -18304);  // 0x7CE570
            }
            // 0x0034c0a0
            charge(ctx, 17);
            a0 = 6;
            lhu(a1, gp, -18304);  // 0x7CE570
            a2 = s0;
            a3 = s2;
            t0 = 1;
            jal(ctx, 0x34C0B4u, gen::fn_sub_316BD0_00316bd0);
            s0 = v0;
            a0 = s0;
            jal(ctx, 0x34C0C4u, gen::fn_sub_318B10_00318b10);
            a0 = s0;
            a1 = 0;
            jal(ctx, 0x34C0D4u, gen::fn_sub_3185B0_003185b0);
            if (v0 != 0) {
                // 0x0034c0e4
                charge(ctx, 12);
                a0 = s0;
                a1 = 0;
                a2 = 0;
                a3 = 0;
                t0 = 0;
                jal(ctx, 0x34C0F8u, gen::fn_sub_3182D0_003182d0);
                a0 = s0;
                a1 = 0;
                mov_s(f12, f20);
                jal(ctx, 0x34C10Cu, gen::fn_sub_3189F0_003189f0);
            }
            // 0x0034c114
            charge(ctx, 7);
            lhu(v0, s0, 216);
            v0 = v0 & 0xFFFD;
            sh(v0, s0, 216);
            lhu(v0, gp, -18304);  // 0x7CE570
            v0 = addiu(v0, 1);
            sh(v0, gp, -18304);  // 0x7CE570
            sw(s0, s1, kE1Model);
        }
    }
    // 0x0034c130 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = s1;
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0034C160 sub_34C160 -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// EPL kind 1, slot 4 [eplModelObjDestroy] ($a0 = the object): the model (+148) destroyed (sub_3174E0) and the object
// freed.
void sub_34C160(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034c160
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, 148);
    if (a0 != 0) {
        // 0x0034c17c
        charge(ctx, 2);
        jal(ctx, 0x34C17Cu, gen::fn_sub_3174E0_003174e0);
    }
    // 0x0034c184
    charge(ctx, 10);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x34C190u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0034C1B0 sub_34C1B0 -- 160 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// EPL kind 1, slot 5 [eplModelObjClone] ($a0 = the source; returns the copy): a cleared 160-byte block as in
// sub_34BFC0, the 104-byte definition copied and the model made like the source's (sub_34C250, fx_epl's copy).
void sub_34C1B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Vf vf0{ctx, 0};
    // 0x0034c1b0
    enter(ctx, 40);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = 160;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x34C1D4u, v0.u());
    s0 = v0;
    a0 = s0;
    a1 = 0;
    a2 = 160;
    jal(ctx, 0x34C1ECu, gen::fn_memset_00521408);
    sw(zero, s0, kE1Age);
    v0 = si(-1);
    sw(v0, s0, kE1Colour);
    v0 = 0x3F800000;
    sw(v0, s0, kE1Scale);
    sqc2(vf0, s0, 0);
    sqc2(vf0, s0, 16);
    a0 = addiu(s0, 44);
    a1 = addiu(s1, 44);
    a2 = 104;
    jal(ctx, 0x34C21Cu, gen::fn_memcpy_00521250);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x34C22Cu, gen::fn_sub_34C250_0034c250);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0034C670 sub_34C670 -- 540 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// fx_epl's kind 2 (EPL row 0x69C39C), slot 0 [eplNodeModelCreate] ($a0 = the effect record, or 0; returns the
// object): a cleared 164-byte block, colour -1, scale 1.0. With a record: block A holds the definition (copied to +48
// when the effect kind is 0, then the model data starts 112 bytes in); the model (sub_34BDF0), its animation 0
// started (looping when the lifetime +144 is 0), its frame count (sub_318FC0) into +40; with block B an effect node
// per frame: the first created from block B (sub_324BD0), the others cloned from it (sub_325920).
void sub_34C670(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Vf vf0{ctx, 0};
    // 0x0034c670
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s0 = 0x960000;
    s0 = addiu(s0, 376);  // &0x960178
    a0 = 164;
    a1 = 0x40000;
    lw(v0, s0, 0);  // 0x960178
    jalr(ctx, 0x34C6A4u, v0.u());
    s1 = v0;
    a0 = s1;
    a1 = 0;
    a2 = 164;
    jal(ctx, 0x34C6BCu, gen::fn_memset_00521408);
    v0 = si(-1);
    sw(v0, s1, kE2Colour);
    v0 = 0x3F800000;
    sw(v0, s1, kE2Scale);
    sqc2(vf0, s1, 0);
    sqc2(vf0, s1, 16);
    if (s2 != 0) {
        // 0x0034c6f0
        charge(ctx, 7);
        a0 = s2;
        jal(ctx, 0x34C6F4u, gen::fn_sub_3245B0_003245b0);
        s3 = v0;
        lhu(v0, s2, 12);
        if (v0 == 0) {
            // 0x0034c714
            charge(ctx, 8);
            s4 = 112;
            a0 = addiu(s1, 48);
            a1 = s3;
            a2 = 104;
            jal(ctx, 0x34C724u, gen::fn_memcpy_00521250);
        } else {
            // 0x0034c70c
            charge(ctx, 2);
            // 0x0034c734
            charge(ctx, 1);
            s4 = 0;
        }
        // 0x0034c738
        charge(ctx, 12);
        a0 = addu(s3, s4);
        lw(v0, s2, 20);
        a1 = subu(v0, s4);
        jal(ctx, 0x34C744u, gen::fn_sub_34BDF0_0034bdf0);
        sw(v0, s1, kE2Model);
        a0 = v0;
        a1 = 0;
        jal(ctx, 0x34C758u, gen::fn_sub_3185B0_003185b0);
        if (v0 != 0) {
            // 0x0034c768
            charge(ctx, 3);
            lw(v0, s1, kE2Lifetime);
            if (v0 == 0) {
                // 0x0034c798
                charge(ctx, 7);
                lw(a0, s1, kE2Model);
                a1 = 0;
                a2 = 0;
                a3 = 0;
                t0 = 1;
                jal(ctx, 0x34C7ACu, gen::fn_sub_3182D0_003182d0);
            } else {
                // 0x0034c774
                charge(ctx, 9);
                lw(a0, s1, kE2Model);
                a1 = 0;
                a2 = 0;
                a3 = 0;
                t0 = 0;
                jal(ctx, 0x34C788u, gen::fn_sub_3182D0_003182d0);
            }
        }
        // 0x0034c7b4
        charge(ctx, 6);
        lw(a0, s1, kE2Model);
        jal(ctx, 0x34C7B8u, gen::fn_sub_318FC0_00318fc0);
        sw(v0, s1, kE2Frames);
        if (v0 != 0) {
            // 0x0034c7d8
            charge(ctx, 6);
            a0 = s2;
            jal(ctx, 0x34C7DCu, gen::fn_sub_3245F0_003245f0);
            s2 = v0;
            if (s2 != 0) {
                // 0x0034c7f0
                charge(ctx, 16);
                lw(v0, s1, kE2Frames);
                a0 = sll(v0, 2);
                a1 = 0x40000;
                lw(v0, s0, 0);
                jalr(ctx, 0x34C800u, v0.u());
                sw(v0, s1, kE2NodeBlock);
                sw(v0, s1, kE2Nodes);
                a0 = s2;
                jal(ctx, 0x34C814u, gen::fn_sub_324BD0_00324bd0);
                lw(v1, s1, kE2Nodes);
                sw(v0, v1, 0);
                s0 = 1;
                for (;;) {
                    // 0x0034c854
                    charge(ctx, 4);
                    lw(v0, s1, kE2Frames);
                    v0 = sltu(s0, v0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0034c830
                    charge(ctx, 9);
                    lw(v0, s1, kE2Nodes);
                    lw(a0, v0, 0);
                    jal(ctx, 0x34C838u, gen::fn_sub_325920_00325920);
                    a0 = sll(s0, 2);
                    lw(v1, s1, kE2Nodes);
                    v1 = addu(v1, a0);
                    sw(v0, v1, 0);
                    s0 = addiu(s0, 1);
                }
            }
            // 0x0034c864
            charge(ctx, 1);
            v0 = s1;
        } else {
            // 0x0034c7cc
            charge(ctx, 3);
            v0 = s1;
        }
    } else {
        // 0x0034c6e4
        charge(ctx, 3);
        v0 = s1;
    }
    // 0x0034c868 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0034C890 sub_34C890 -- 172 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// EPL kind 2, slot 4 [eplNodeModelDestroy] ($a0 = the object): the model destroyed (sub_34BEF0), every frame's node
// destroyed (sub_3257E0) and the node block freed, then the object.
void sub_34C890(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034c890
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, 160);
    if (a0 != 0) {
        // 0x0034c8b0
        charge(ctx, 2);
        jal(ctx, 0x34C8B0u, gen::fn_sub_34BEF0_0034bef0);
    }
    // 0x0034c8b8
    charge(ctx, 3);
    lw(v0, s0, kE2NodeBlock);
    if (v0 != 0) {
        // 0x0034c8c4
        charge(ctx, 3);
        s1 = 0;
        for (;;) {
            // 0x0034c8ec
            charge(ctx, 4);
            lw(v0, s0, kE2Frames);
            v0 = sltu(s1, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0034c8d0
            charge(ctx, 7);
            v1 = sll(s1, 2);
            lw(v0, s0, kE2Nodes);
            v0 = addu(v0, v1);
            lw(a0, v0, 0);
            jal(ctx, 0x34C8E0u, gen::fn_sub_3257E0_003257e0);
            s1 = addiu(s1, 1);
        }
        // 0x0034c8fc
        charge(ctx, 5);
        lw(a0, s0, kE2NodeBlock);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x34C908u, v0.u());
    }
    // 0x0034c910
    charge(ctx, 11);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x34C91Cu, v0.u());
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0034C9B0 sub_34C9B0 -- 432 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// EPL kind 2, slot 6 [eplNodeModelCopy] ($a0 = the destination, $a1 = the source): the destination's model replaced
// by one of the source model's file (sub_316E00 with +212 / +214, reset by sub_34BD60, animation 0 looping unless a
// lifetime), the frame count refreshed; when the source has nodes the destination's old nodes are destroyed and one
// clone of the source's first node made per frame (sub_325920).
void sub_34C9B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034c9b0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    lw(a0, a0, 160);
    if (a0 != 0) {
        // 0x0034c9d8
        charge(ctx, 2);
        jal(ctx, 0x34C9D8u, gen::fn_sub_34BEF0_0034bef0);
    }
    // 0x0034c9e0
    charge(ctx, 16);
    lw(v0, s1, 160);
    lhu(a0, v0, 212);
    lhu(a1, v0, 214);
    a2 = 0;
    jal(ctx, 0x34C9F0u, gen::fn_sub_316E00_00316e00);
    sw(v0, s2, 160);
    a0 = v0;
    jal(ctx, 0x34CA00u, gen::fn_sub_34BD60_0034bd60);
    lw(a0, s2, 160);
    a1 = 0;
    jal(ctx, 0x34CA10u, gen::fn_sub_3185B0_003185b0);
    if (v0 != 0) {
        // 0x0034ca20
        charge(ctx, 3);
        lw(v0, s2, 144);
        if (v0 == 0) {
            // 0x0034ca50
            charge(ctx, 7);
            lw(a0, s2, 160);
            a1 = 0;
            a2 = 0;
            a3 = 0;
            t0 = 1;
            jal(ctx, 0x34CA64u, gen::fn_sub_3182D0_003182d0);
        } else {
            // 0x0034ca2c
            charge(ctx, 9);
            lw(a0, s2, 160);
            a1 = 0;
            a2 = 0;
            a3 = 0;
            t0 = 0;
            jal(ctx, 0x34CA40u, gen::fn_sub_3182D0_003182d0);
        }
    }
    // 0x0034ca6c
    charge(ctx, 7);
    lw(a0, s2, 160);
    jal(ctx, 0x34CA70u, gen::fn_sub_318FC0_00318fc0);
    sw(v0, s2, 40);
    lw(v1, s1, 156);
    if (v1 != 0) {
        // 0x0034ca88
        charge(ctx, 3);
        lw(v0, s2, 156);
        if (v0 != 0) {
            // 0x0034ca94
            charge(ctx, 3);
            s0 = 0;
            for (;;) {
                // 0x0034cabc
                charge(ctx, 4);
                lw(v0, s2, 40);
                v0 = sltu(s0, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0034caa0
                charge(ctx, 7);
                v1 = sll(s0, 2);
                lw(v0, s2, 152);
                v0 = addu(v0, v1);
                lw(a0, v0, 0);
                jal(ctx, 0x34CAB0u, gen::fn_sub_3257E0_003257e0);
                s0 = addiu(s0, 1);
            }
            // 0x0034cacc
            charge(ctx, 5);
            lw(a0, s2, 156);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C
            jalr(ctx, 0x34CAD8u, v0.u());
        }
        // 0x0034cae0
        charge(ctx, 12);
        lw(v0, s2, 40);
        a0 = sll(v0, 2);
        a1 = 0x40000;
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178
        jalr(ctx, 0x34CAF4u, v0.u());
        sw(v0, s2, 156);
        sw(v0, s2, 152);
        s0 = 0;
        for (;;) {
            // 0x0034cb34
            charge(ctx, 4);
            lw(v1, s2, 40);
            v1 = sltu(s0, v1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0034cb10
            charge(ctx, 9);
            lw(v0, s1, 152);
            lw(a0, v0, 0);
            jal(ctx, 0x34CB18u, gen::fn_sub_325920_00325920);
            a0 = sll(s0, 2);
            lw(v1, s2, 152);
            v1 = addu(v1, a0);
            sw(v0, v1, 0);
            s0 = addiu(s0, 1);
        }
    }
    // 0x0034cb44 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0034D510 sub_34D510 -- 340 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// fx_epl's kind 3 (EPL row 0x69C3D0), slot 0 [eplClumpPsysCreate] ($a0 = the effect record; returns the object): from
// block A (its particle parameters at +68): count = (lifetime +100, else life +252) x rate +104, at most 100; a
// cleared 104-byte object (colour -1, scale 1.0, the 68-byte head copy at +16); the particle system and records
// (sub_34D8A0 with the effect kind); with slots and a block B of type 3 the clump loaded from it (sub_34D990 with the
// record's +36 as its size); the block-B type into +12.
void sub_34D510(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034d510
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    jal(ctx, 0x34D52Cu, gen::fn_sub_3245B0_003245b0);
    s1 = v0;
    lw(v1, v0, 100);
    if (v1 != 0) {
        // 0x0034d558
        charge(ctx, 2);
        lw(v0, s1, 104);
        mult(s3, v1, v0);
    } else {
        // 0x0034d544
        charge(ctx, 5);
        lw(v1, s1, 252);
        lw(v0, s1, 104);
        mult(s3, v1, v0);
    }
    // 0x0034d560
    charge(ctx, 3);
    at = sltiu(s3, 101);
    if (at == 0) {
        // 0x0034d56c
        charge(ctx, 1);
        s3 = 100;
    }
    // 0x0034d570
    charge(ctx, 31);
    a0 = 104;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x34D580u, v0.u());
    s0 = v0;
    a0 = s0;
    a1 = 0;
    a2 = 104;
    jal(ctx, 0x34D598u, gen::fn_memset_00521408);
    sw(s3, s0, kE3Count);
    v0 = si(-1);
    sw(v0, s0, kE3Colour);
    v0 = 0x3F800000;
    sw(v0, s0, kE3Scale);
    a0 = addiu(s0, 16);
    a1 = s1;
    a2 = 68;
    jal(ctx, 0x34D5C0u, gen::fn_memcpy_00521250);
    lhu(a1, s2, 12);
    a0 = s0;
    a2 = addiu(s1, 68);
    jal(ctx, 0x34D5D4u, gen::fn_sub_34D8A0_0034d8a0);
    lw(v0, s0, kE3Psys);
    lw(v0, v0, 8);
    if (v0 != 0) {
        // 0x0034d5f8
        charge(ctx, 5);
        a0 = s2;
        jal(ctx, 0x34D5FCu, gen::fn_sub_3245F0_003245f0);
        if (v0 != 0) {
            // 0x0034d60c
            charge(ctx, 4);
            lhu(a0, s2, 28);
            v1 = 3;
            if (a0 == v1) {
                // 0x0034d624
                charge(ctx, 5);
                lw(a2, s2, 36);
                a0 = s0;
                a1 = v0;
                jal(ctx, 0x34D630u, gen::fn_sub_34D990_0034d990);
            } else {
                // 0x0034d61c
                charge(ctx, 2);
            }
            // 0x0034d638
            charge(ctx, 2);
            lhu(v0, s2, 28);
            sh(v0, s0, kE3BlockBType);
        }
        // 0x0034d640
        charge(ctx, 1);
        v0 = s0;
    } else {
        // 0x0034d5ec
        charge(ctx, 3);
        v0 = s0;
    }
    // 0x0034d644 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0034D670 sub_34D670 -- 124 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// EPL kind 3, slot 4 [eplClumpPsysDestroy] ($a0 = the object): the particle system (sub_3321D0), the record block
// (RwFree) and the clump (RpClumpDestroy sub_491EA0) when present, then the object.
void sub_34D670(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034d670
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, 88);
    if (a0 != 0) {
        // 0x0034d68c
        charge(ctx, 2);
        jal(ctx, 0x34D68Cu, gen::fn_sub_3321D0_003321d0);
    }
    // 0x0034d694
    charge(ctx, 3);
    lw(a0, s0, kE3RecordBlock);
    if (a0 != 0) {
        // 0x0034d6a0
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x34D6A8u, v0.u());
    }
    // 0x0034d6b0
    charge(ctx, 3);
    lw(a0, s0, kE3Clump);
    if (a0 != 0) {
        // 0x0034d6bc
        charge(ctx, 2);
        jal(ctx, 0x34D6BCu, gen::fn_sub_491EA0_00491ea0);
    }
    // 0x0034d6c4
    charge(ctx, 10);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x34D6D0u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0034D6F0 sub_34D6F0 -- 284 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// EPL kind 3, slot 5 [eplClumpPsysClone] ($a0 = the source; returns the copy): the count from the source system's
// base parameters, a new 104-byte object with the head copied, the particle system and records (sub_34D8A0) and, with
// slots, the clump cloned (sub_34D810).
void sub_34D6F0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034d6f0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(v0, a0, 88);
    lw(s1, v0, 36);
    lw(v1, s1, 32);
    if (v1 != 0) {
        // 0x0034d734
        charge(ctx, 2);
        lw(v0, s1, 36);
        mult(s3, v1, v0);
    } else {
        // 0x0034d720
        charge(ctx, 5);
        lw(v1, s1, 184);
        lw(v0, s1, 36);
        mult(s3, v1, v0);
    }
    // 0x0034d73c
    charge(ctx, 3);
    at = sltiu(s3, 101);
    if (at == 0) {
        // 0x0034d748
        charge(ctx, 1);
        s3 = 100;
    }
    // 0x0034d74c
    charge(ctx, 32);
    a0 = 104;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x34D75Cu, v0.u());
    s0 = v0;
    a0 = s0;
    a1 = 0;
    a2 = 104;
    jal(ctx, 0x34D774u, gen::fn_memset_00521408);
    sw(s3, s0, kE3Count);
    v0 = si(-1);
    sw(v0, s0, kE3Colour);
    v0 = 0x3F800000;
    sw(v0, s0, kE3Scale);
    a0 = addiu(s0, 16);
    a1 = addiu(s2, 16);
    a2 = 68;
    jal(ctx, 0x34D79Cu, gen::fn_memcpy_00521250);
    lw(v0, s2, 88);
    lhu(a1, v0, 0);
    a0 = s0;
    a2 = s1;
    jal(ctx, 0x34D7B4u, gen::fn_sub_34D8A0_0034d8a0);
    lw(v0, s0, kE3Psys);
    lw(v0, v0, 8);
    if (v0 != 0) {
        // 0x0034d7d8
        charge(ctx, 5);
        a0 = s0;
        a1 = s2;
        jal(ctx, 0x34D7E0u, gen::fn_sub_34D810_0034d810);
        v0 = s0;
    } else {
        // 0x0034d7cc
        charge(ctx, 3);
        v0 = s0;
    }
    // 0x0034d7ec (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0034D8A0 sub_34D8A0 -- 240 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Sets up the particles of an EPL kind-3 object [eplClumpPsysSetSystem] ($a0 = the object, $a1 = the type, $a2 = the
// parameters): replaces the particle system (sub_3321D0, then sub_332070 with the object's count), replaces the
// record block (RwFree / RwMalloc of 24 x slots) and emits every record (sub_34D150).
void sub_34D8A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034d8a0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s2 = a1;
    s0 = a2;
    lw(a0, a0, 88);
    if (a0 != 0) {
        // 0x0034d8d0
        charge(ctx, 2);
        jal(ctx, 0x34D8D0u, gen::fn_sub_3321D0_003321d0);
    }
    // 0x0034d8d8
    charge(ctx, 9);
    a0 = s2 & 0xFFFF;
    lw(a1, s1, 0);
    a2 = s0;
    jal(ctx, 0x34D8E4u, gen::fn_sub_332070_00332070);
    sw(v0, s1, 88);
    lw(a0, s1, 96);
    if (a0 != 0) {
        // 0x0034d8fc
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x34D904u, v0.u());
    }
    // 0x0034d90c
    charge(ctx, 16);
    lw(v0, s1, 88);
    lw(s0, v0, 8);
    v0 = sll(s0, 1);
    v0 = addu(v0, s0);
    a0 = sll(v0, 3);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x34D92Cu, v0.u());
    sw(v0, s1, 96);
    s3 = v0;
    sw(s3, s1, 92);
    s2 = 0;
    for (;;) {
        // 0x0034d964
        charge(ctx, 3);
        v1 = sltu(s2, s0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0034d94c
        charge(ctx, 6);
        a0 = s1;
        a1 = s3;
        jal(ctx, 0x34D954u, gen::fn_sub_34D150_0034d150);
        s2 = addiu(s2, 1);
        s3 = addiu(s3, 24);
    }
    // 0x0034d970
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0034E4C0 sub_34E4C0 -- 336 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// fx_epl's kind 4 (EPL row 0x69C404), slot 0 [eplTexPsysCreate] ($a0 = the effect record; returns the object): from
// block A (particle parameters at +72): count = (lifetime +104, else life +256) x rate +108, at most 100; a cleared
// 112-byte object (colour -1, scale 1.0, scroll 0, the 72-byte head at +12); the particle system and records
// (sub_34E820); with slots and a block B of type 1 the texture by name (sub_34E7C0).
void sub_34E4C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034e4c0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    jal(ctx, 0x34E4DCu, gen::fn_sub_3245B0_003245b0);
    s1 = v0;
    lw(v1, v0, 104);
    if (v1 != 0) {
        // 0x0034e508
        charge(ctx, 2);
        lw(v0, s1, 108);
        mult(s3, v1, v0);
    } else {
        // 0x0034e4f4
        charge(ctx, 5);
        lw(v1, s1, 256);
        lw(v0, s1, 108);
        mult(s3, v1, v0);
    }
    // 0x0034e510
    charge(ctx, 3);
    at = sltiu(s3, 101);
    if (at == 0) {
        // 0x0034e51c
        charge(ctx, 1);
        s3 = 100;
    }
    // 0x0034e520
    charge(ctx, 33);
    a0 = 112;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x34E530u, v0.u());
    s0 = v0;
    a0 = s0;
    a1 = 0;
    a2 = 112;
    jal(ctx, 0x34E548u, gen::fn_memset_00521408);
    sw(s3, s0, kE4Count);
    v0 = si(-1);
    sw(v0, s0, kE4Colour);
    v0 = 0x3F800000;
    sw(v0, s0, kE4Scale);
    sw(zero, s0, kE4ScrollU);
    sw(zero, s0, kE4ScrollV);
    a0 = addiu(s0, 12);
    a1 = s1;
    a2 = 72;
    jal(ctx, 0x34E578u, gen::fn_memcpy_00521250);
    lhu(a1, s2, 12);
    a0 = s0;
    a2 = addiu(s1, 72);
    jal(ctx, 0x34E58Cu, gen::fn_sub_34E820_0034e820);
    lw(v0, s0, kE4Psys);
    lw(v0, v0, 8);
    if (v0 != 0) {
        // 0x0034e5b0
        charge(ctx, 5);
        a0 = s2;
        jal(ctx, 0x34E5B4u, gen::fn_sub_3245F0_003245f0);
        if (v0 != 0) {
            // 0x0034e5c4
            charge(ctx, 4);
            lhu(a0, s2, 28);
            v1 = 1;
            if (a0 == v1) {
                // 0x0034e5dc
                charge(ctx, 4);
                a0 = s0;
                a1 = v0;
                jal(ctx, 0x34E5E4u, gen::fn_sub_34E7C0_0034e7c0);
            } else {
                // 0x0034e5d4
                charge(ctx, 2);
            }
        }
        // 0x0034e5ec
        charge(ctx, 1);
        v0 = s0;
    } else {
        // 0x0034e5a4
        charge(ctx, 3);
        v0 = s0;
    }
    // 0x0034e5f0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0034E610 sub_34E610 -- 124 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// EPL kind 4, slot 4 [eplTexPsysDestroy] ($a0 = the object): the texture (RwTextureDestroy sub_4D0F00), the particle
// system (sub_3321D0) and the record block (RwFree) when present, then the object.
void sub_34E610(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034e610
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, 96);
    if (a0 != 0) {
        // 0x0034e62c
        charge(ctx, 2);
        jal(ctx, 0x34E62Cu, gen::fn_sub_4D0F00_004d0f00);
    }
    // 0x0034e634
    charge(ctx, 3);
    lw(a0, s0, kE4Psys);
    if (a0 != 0) {
        // 0x0034e640
        charge(ctx, 2);
        jal(ctx, 0x34E640u, gen::fn_sub_3321D0_003321d0);
    }
    // 0x0034e648
    charge(ctx, 3);
    lw(a0, s0, kE4RecordBlock);
    if (a0 != 0) {
        // 0x0034e654
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x34E65Cu, v0.u());
    }
    // 0x0034e664
    charge(ctx, 10);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x34E670u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0034E690 sub_34E690 -- 292 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// EPL kind 4, slot 5 [eplTexPsysClone] ($a0 = the source; returns the copy): the count from the source system's base
// parameters, a new 112-byte object (scroll 0, the head copied), the particles (sub_34E820) and, with slots, the
// texture shared (sub_34E800).
void sub_34E690(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034e690
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(v0, a0, 92);
    lw(s1, v0, 36);
    lw(v1, s1, 32);
    if (v1 != 0) {
        // 0x0034e6d4
        charge(ctx, 2);
        lw(v0, s1, 36);
        mult(s3, v1, v0);
    } else {
        // 0x0034e6c0
        charge(ctx, 5);
        lw(v1, s1, 184);
        lw(v0, s1, 36);
        mult(s3, v1, v0);
    }
    // 0x0034e6dc
    charge(ctx, 3);
    at = sltiu(s3, 101);
    if (at == 0) {
        // 0x0034e6e8
        charge(ctx, 1);
        s3 = 100;
    }
    // 0x0034e6ec
    charge(ctx, 34);
    a0 = 112;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x34E6FCu, v0.u());
    s0 = v0;
    a0 = s0;
    a1 = 0;
    a2 = 112;
    jal(ctx, 0x34E714u, gen::fn_memset_00521408);
    sw(s3, s0, kE4Count);
    v0 = si(-1);
    sw(v0, s0, kE4Colour);
    v0 = 0x3F800000;
    sw(v0, s0, kE4Scale);
    sw(zero, s0, kE4ScrollU);
    sw(zero, s0, kE4ScrollV);
    a0 = addiu(s0, 12);
    a1 = addiu(s2, 12);
    a2 = 72;
    jal(ctx, 0x34E744u, gen::fn_memcpy_00521250);
    lw(v0, s2, 92);
    lhu(a1, v0, 0);
    a0 = s0;
    a2 = s1;
    jal(ctx, 0x34E75Cu, gen::fn_sub_34E820_0034e820);
    lw(v0, s0, kE4Psys);
    lw(v0, v0, 8);
    if (v0 != 0) {
        // 0x0034e780
        charge(ctx, 5);
        a0 = s0;
        a1 = s2;
        jal(ctx, 0x34E788u, gen::fn_sub_34E800_0034e800);
        v0 = s0;
    } else {
        // 0x0034e774
        charge(ctx, 3);
        v0 = s0;
    }
    // 0x0034e794 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0034E820 sub_34E820 -- 240 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Generated by p3fes_handgen: register for register and block for block as the recompiled body (frame, spills, $ra
// links, cycle charges and check points); the slice's job is the names, structure, comments and typed views.
// Sets up the particles of an EPL kind-4 object [eplTexPsysSetSystem] ($a0 = the object, $a1 = the type, $a2 = the
// parameters): replaces the particle system (sub_332070 with the object's count), replaces the record block (28 x
// slots) and emits every record (sub_34E940).
void sub_34E820(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0034e820
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s2 = a1;
    s0 = a2;
    lw(a0, a0, 92);
    if (a0 != 0) {
        // 0x0034e850
        charge(ctx, 2);
        jal(ctx, 0x34E850u, gen::fn_sub_3321D0_003321d0);
    }
    // 0x0034e858
    charge(ctx, 9);
    a0 = s2 & 0xFFFF;
    lw(a1, s1, 0);
    a2 = s0;
    jal(ctx, 0x34E864u, gen::fn_sub_332070_00332070);
    sw(v0, s1, 92);
    lw(a0, s1, 104);
    if (a0 != 0) {
        // 0x0034e87c
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x34E884u, v0.u());
    }
    // 0x0034e88c
    charge(ctx, 16);
    lw(v0, s1, 92);
    lw(s0, v0, 8);
    v0 = sll(s0, 3);
    v0 = subu(v0, s0);
    a0 = sll(v0, 2);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x34E8ACu, v0.u());
    sw(v0, s1, 104);
    s3 = v0;
    sw(s3, s1, 100);
    s2 = 0;
    for (;;) {
        // 0x0034e8e4
        charge(ctx, 3);
        v1 = sltu(s2, s0);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0034e8cc
        charge(ctx, 6);
        a0 = s1;
        a1 = s3;
        jal(ctx, 0x34E8D4u, gen::fn_sub_34E940_0034e940);
        s2 = addiu(s2, 1);
        s3 = addiu(s3, 28);
    }
    // 0x0034e8f0
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

}  // namespace p3fes::game
